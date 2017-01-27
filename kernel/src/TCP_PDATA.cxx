/*
**
** Implementation file for TCP_PDATA module
**
**
**
** exa
**
*/

#include "KernelInterface.hxx"

// The implementation uses DTCPStream internally
// That's why redundant buffer transfers take
// place, however it's all safe this way.

TCP_PDATA::TCP_PDATA(CustomSocket &soc, OpenMode _mode,
		int p_c_id, int n)
: DStream(_mode), socket(soc),
  presentation_context_id(p_c_id),
	max_pdv_list_size(n),
	pdata_type(nodata),
	last_pdv(false)
{
}


// start P-DATA from an already open TCP stream
// NOTE: works only for input streams at present
TCP_PDATA::TCP_PDATA(DTCPStream &tcp_stream, int p_c_id, int n)
: DStream(tcp_stream.openMode), socket(tcp_stream.socket),
  presentation_context_id(p_c_id),
	max_pdv_list_size(n),
	last_pdv(false)
{
	switch (tcp_stream.openMode) {
		case DStream::input: {
			pdata_type = inherit_stream;
			inherited_stream = &tcp_stream; // mustn't fall out of scope!
			break;
												 }
		case DStream::output: {
			pdata_type = inherit_stream;
			inherited_stream = &tcp_stream; // mustn't fall out of scope!
			break;
													}
	}
}

TCP_PDATA::~TCP_PDATA()
{
}

// Send a filled P-DATA-TF PDU
int TCP_PDATA::send_pdata_tf()
{
	DTCPStream out(socket, DStream::output);
	out.begin_write(p_data_tf_type);
	p_data_tf.encode(out);
	out.end_write();
	p_data_tf.pdv_items.clear();
	return 0; // KLUDGE
}

// Consume another P-DATA-TF
int TCP_PDATA::receive_pdata_tf()
{
	p_data_tf.pdv_items.clear();
	if (pdata_type != inherit_stream) {
		DTCPStream in(socket, DStream::input);
		if (in.begin_read() != p_data_tf_type)
			throw DPDATA_Exception("Expecting P-DATA-TF PDU, got other...");
		p_data_tf.decode(in);
		in.end_read();
		return in.input_size;
	}
	else {
		inherited_stream->continue_read(0);
		p_data_tf.decode(*inherited_stream);
		inherited_stream->end_read();
		return inherited_stream->input_size;
	}
}

void TCP_PDATA::send_next_pdv()
{
	if ( (pdata_type!=nodata) && (pdata_type!=inherit_stream) ) {
		// CODE: use iterators below...
		int msg_length = &*current_msg_data - &current_pdv->message_fragment.front();
		current_pdv->message_fragment.resize(msg_length);
	}

	if ( (remaining_bytes == 0) || (pdata_type == nodata) ||
		   (pdata_type == end_data) ) {
		if (pdata_type != nodata)
			send_pdata_tf();
		if (pdata_type != end_data) {
			remaining_bytes = max_pdv_list_size;
		}
	}

	current_pdv = p_data_tf.pdv_items.insert(p_data_tf.pdv_items.end());
	current_pdv->presentation_context_id = presentation_context_id;
	if (pdata_type==command_set)
		current_pdv->message_header = 0x1;
	else
		if (pdata_type==data_set)
			current_pdv->message_header = 0x0;
	remaining_bytes -= 6;
	current_pdv->message_fragment.resize(remaining_bytes);
	current_msg_data = current_pdv->message_fragment.begin();
}

void TCP_PDATA::receive_next_pdv()
{
	if (last_pdv)
		return;
	if ( (current_pdv==--p_data_tf.pdv_items.end()) ||
		   (pdata_type == nodata) || (pdata_type == inherit_stream) ) {
		int input_size = receive_pdata_tf();
		remaining_bytes = input_size-6;
		current_pdv = p_data_tf.pdv_items.begin();
	} else {
		current_pdv++;
		remaining_bytes -= 6;
	}
	if (presentation_context_id == -1)
		presentation_context_id = current_pdv->presentation_context_id;
	else
		if (presentation_context_id != current_pdv->presentation_context_id)
			throw DPDATA_Exception("Presentation Context ID mismatch");
	
	set_length += current_pdv->message_fragment.size();

	if (current_pdv->message_header & 0x2)  {
		last_pdv = true;
		mod_input_size(set_length);
	}
	current_msg_data = current_pdv->message_fragment.begin();
}

// start PDATA input service
void TCP_PDATA::begin_read(PDATA_Type type)
{
	switch (type) {
		case command_set: {
			switch (pdata_type) {
			case nodata:
			case inherit_stream:
				set_length = 0;
				position = 0;
				receive_next_pdv();
				pdata_type = command_set;
				break;
			default:
				throw DPDATA_Exception();
			}
			if (!current_pdv->message_header & 0x1)
				throw DPDATA_Exception("Expecting Command Set, got Data Set");
			break;
									}
		case data_set: {
			if (pdata_type!=command_set)
				throw DPDATA_Exception();
			pdata_type = data_set;
			set_length = 0;
			position = 0;
			mod_input_size(0x7fffffff);
			invalidate_tag();
			last_pdv = false;
			receive_next_pdv();
			if (current_pdv->message_header & 0x1)
				throw DPDATA_Exception("Expecting Data Set, got Command Set");
			break;
									 }
	};
}

void TCP_PDATA::read (char* buffer, int len)
{
	if (len < remaining_bytes) {
		remaining_bytes -= len;
		memcpy(buffer, &*current_msg_data, len);
		current_msg_data += len;
	} else {
		// read remaining bytes first
		memcpy(buffer, &*current_msg_data, remaining_bytes);

		int read_bytes = remaining_bytes;
		current_msg_data += read_bytes;

		remaining_bytes = 0; // read all User Data up to this pdv

		// read the rest
		int rests_length = len - read_bytes;
		if (rests_length > 0) {
			// we need to get a new pdv item
			receive_next_pdv();
			read(buffer + read_bytes, rests_length);
		}
	}
	DStreamBase::read(buffer, len);
}

void TCP_PDATA::end_read ()
{
	// essentially no`thing
}

void TCP_PDATA::begin_write(PDATA_Type type)
{
	switch (type) {
		case command_set: {
			if (pdata_type!=nodata)
				throw DPDATA_Exception();
			send_next_pdv();
			pdata_type = command_set;
			current_pdv->message_header = 0x1;
			break;
									}
		case data_set: {
			if (pdata_type!=command_set)
				throw DPDATA_Exception();
			// finish writing command_set
			// KLUDGE :: blows up if command set exceeds first PDV
			write_first_groups_length();
			pdata_type = data_set;
			current_pdv->message_header = 0x3;
			send_next_pdv();
			current_pdv->message_header = 0x0;
			break;
							 }
	};
}


void TCP_PDATA::write (char* buffer, int len)
{
	if (len < remaining_bytes) {
		remaining_bytes -= len;
		memcpy(&*current_msg_data, buffer, len);
		current_msg_data += len;
	} else {
		// send remaining bytes first
		memcpy(&*current_msg_data, buffer, remaining_bytes);

		int written_bytes = remaining_bytes;
		current_msg_data += written_bytes;

		remaining_bytes = 0; // filled User Data

	  // we need to send the pdv item
		send_next_pdv();

		// write remaining
		int rests_length = len - written_bytes;
		if (rests_length > 0) {
			write( buffer + written_bytes, rests_length); 
		}
	}
	DStreamBase::write(buffer, len);
}


void TCP_PDATA::end_write()
{
	if (pdata_type==command_set)
		// KLUDGE :: blows up if command set exceeds first PDV
		write_first_groups_length();
	pdata_type = end_data;
	current_pdv->message_header |= 0x2;
	send_next_pdv();
}

// KLUDGE KLUDGE : works when command set fits in the first PDV of first PDU
// used to patch the buffer for finding command element's group length
void TCP_PDATA::write_first_groups_length ()
{
	enum { offset = 8 };

	vector<char> & command = p_data_tf.pdv_items.front().message_fragment;

	int cmd_length = &*current_msg_data - &current_pdv->message_fragment.front();

	char *modify = (&command.front()) + offset;

	memcpy(modify, &cmd_length, 4); // Little Endian
}
