/*
**
** Implementation file for module
**
**
**
** exa
**
*/

#include "KernelInterface.hxx"

UI Application_Context_Item::
	 default_application_context_name("1.2.840.10008.3.1.1.1");

// encode item header... precondition: buffer encoded
void Item_Base::encode(DStream& ds, DStreamBuffer& buffer)
{
	PDU_TS::encode_binary(ds, item_type);
	reserved = 0;
	PDU_TS::encode_binary(ds, reserved);
	item_length = buffer.length();
	PDU_TS::encode_binary(ds, item_length);
	// send out buffer
	buffer.transfer(ds);
}

// postcondition: buffer ready to decode
void Item_Base::decode(DStream& ds, DStreamBuffer& buffer)
{
	PDU_TS::decode_binary(ds, item_type);
	PDU_TS::decode_binary(ds, reserved);
	PDU_TS::decode_binary(ds, item_length); // these many bytes to decode
	// load buffer
	buffer.load(ds, item_length);
}

void PDU_Header::decode(DStream& ds)
{
	PDU_TS::decode_binary(ds, pdu_type);
	PDU_TS::decode_binary(ds, reserved);
	PDU_TS::decode_binary(ds, pdu_length); // these many bytes to decode
}

void PDU_Header::encode(DStream& ds)
{
	PDU_TS::encode_binary(ds, pdu_type);
	PDU_TS::encode_binary(ds, reserved);
	PDU_TS::encode_binary(ds, pdu_length); // these many bytes to encode
}

void Item_Header::decode(DStream& ds)
{
	PDU_TS::decode_binary(ds, item_type);
	PDU_TS::decode_binary(ds, reserved);
	PDU_TS::decode_binary(ds, item_length); // these many bytes to decode
}

void Item_Header::encode(DStream& ds)
{
	PDU_TS::encode_binary(ds, item_type);
	PDU_TS::encode_binary(ds, reserved);
	PDU_TS::encode_binary(ds, item_length); // these many bytes to encode
}

Application_Context_Item::Application_Context_Item()
: application_context_name(default_application_context_name)
{}

	void Application_Context_Item::encode(DStream& ds)
  {
	  DStreamBuffer buffer(DStream::output);
	  string & tmp = application_context_name.rep();
	  PDU_TS::encode_string(buffer, tmp, tmp.size());
	  Base::encode(ds, buffer);
  }
		
	void Application_Context_Item::decode(DStream& ds)
  {
	  DStreamBuffer buffer(DStream::input);
	  Base::decode(ds, buffer);
	  string tmp;
	  PDU_TS::decode_string(buffer, tmp, item_length);
	  application_context_name = tmp;
  }

	
		void Abstract_Syntax_Sub_Item::encode(DStream& ds)
		{
			DStreamBuffer buffer(DStream::output);
			string & tmp = abstract_syntax_name.rep();
			PDU_TS::encode_string(buffer, tmp, tmp.size());
			Base::encode(ds, buffer);
		}
		
		void Abstract_Syntax_Sub_Item::decode(DStream& ds)
		{
			DStreamBuffer buffer(DStream::input);
			Base::decode(ds, buffer);
			string tmp;
			PDU_TS::decode_string(buffer, tmp, item_length);
			abstract_syntax_name = tmp;
		}
		
		void Transfer_Syntax_Sub_Item::encode(DStream& ds)
	  {
	    DStreamBuffer buffer(DStream::output);
	    string & tmp = transfer_syntax_name.rep();
	    PDU_TS::encode_string(buffer, tmp, tmp.size());
	    Base::encode(ds, buffer);
	  }
		
		void Transfer_Syntax_Sub_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	  {
	    string tmp;
	    PDU_TS::decode_string(buffer, tmp, item_length);
	    transfer_syntax_name = tmp;
	  }

		void Transfer_Syntax_Sub_Item::decode(DStream& ds)
	  {
	    DStreamBuffer buffer(DStream::input);
	    Base::decode(ds, buffer);
			do_decode(ds, buffer);
		}

		bool Transfer_Syntax_Sub_Item::check_and_decode(DStream& ds, Item_Header& header)
		{
			DStreamBuffer buffer(DStream::input);
			if (Base::check_and_decode(ds, buffer, header)) {
				do_decode(ds, buffer);
				return true;
			}
			else
				return false;
		}

  void RQ_Presentation_Context_Item::encode(DStream& ds)
  {
	  DStreamBuffer buffer(DStream::output);
	  PDU_TS::encode_binary(buffer, presentation_context_ID);
	  PDU_TS::encode_binary(buffer, reserved1);
	  PDU_TS::encode_binary(buffer, reserved2);
	  PDU_TS::encode_binary(buffer, reserved3);
	  abstract_syntax_sub_item.encode(buffer);
	  list<Transfer_Syntax_Sub_Item>::iterator i = transfer_syntax_sub_items.begin(),
	    j = transfer_syntax_sub_items.end();
	  for (; i!=j; i++)
	    i->encode(buffer);
	  Base::encode(ds, buffer);
  }
	
	void RQ_Presentation_Context_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		PDU_TS::decode_binary(buffer, presentation_context_ID);
		PDU_TS::decode_binary(buffer, reserved1);
		PDU_TS::decode_binary(buffer, reserved2);
		PDU_TS::decode_binary(buffer, reserved3);
		abstract_syntax_sub_item.decode(buffer);
		transfer_syntax_sub_items.clear();
		while (buffer.position < item_length) {
			Transfer_Syntax_Sub_Item ts_sub_item;
			ts_sub_item.decode(buffer);
			transfer_syntax_sub_items.push_back(ts_sub_item);
		}
	}

	void RQ_Presentation_Context_Item::decode(DStream& ds)
	{
		DStreamBuffer buffer(DStream::input);
		Base::decode(ds, buffer);
		do_decode(ds, buffer);
	}

	bool RQ_Presentation_Context_Item::check_and_decode(DStream& ds, Item_Header& header)
	{
		DStreamBuffer buffer(DStream::input);
		if (Base::check_and_decode(ds, buffer, header)) {
			do_decode(ds, buffer);
			return true;
		}
		else
			return false;
	}

  void AC_Presentation_Context_Item::encode(DStream& ds)
  {
		char reserved1, reserved2;
		reserved1 = reserved2 = 0;
	  DStreamBuffer buffer(DStream::output);
	  PDU_TS::encode_binary(buffer, presentation_context_ID);
	  PDU_TS::encode_binary(buffer, reserved1);
	  PDU_TS::encode_binary(buffer, result_reason);
	  PDU_TS::encode_binary(buffer, reserved2);
	  transfer_syntax_sub_item.encode(buffer);
	  Base::encode(ds, buffer);
  }
	
	void AC_Presentation_Context_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		PDU_TS::decode_binary(buffer, presentation_context_ID);
		PDU_TS::decode_binary(buffer, reserved1);
		PDU_TS::decode_binary(buffer, result_reason);
		PDU_TS::decode_binary(buffer, reserved2);
		transfer_syntax_sub_item.decode(buffer);
	}

	void AC_Presentation_Context_Item::decode(DStream& ds)
	{
		DStreamBuffer buffer(DStream::input);
		Base::decode(ds, buffer);
		do_decode(ds, buffer);
	}

	bool AC_Presentation_Context_Item::check_and_decode(DStream& ds, Item_Header& header)
	{
		DStreamBuffer buffer(DStream::input);
		if (Base::check_and_decode(ds, buffer, header)) {
			do_decode(ds, buffer);
			return true;
		}
		else
			return false;
	}

	Maximum_Length_Sub_Item::Maximum_Length_Sub_Item()
		: avail() {}

  void Maximum_Length_Sub_Item::encode(DStream& ds)
  {
		if (avail) {
			DStreamBuffer buffer(DStream::output);
			PDU_TS::encode_binary(buffer, maximum_length_received);
			Base::encode(ds, buffer);
		}
	}
		
	void Maximum_Length_Sub_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		PDU_TS::decode_binary(buffer, maximum_length_received);
		avail = true;
	}

	void Maximum_Length_Sub_Item::decode(DStream& ds)
	{
		DStreamBuffer buffer(DStream::input);
		Base::decode(ds, buffer);
		do_decode(ds, buffer);
	}

	// CODE: Make into a virtual function
	bool Maximum_Length_Sub_Item::check_and_decode(DStream& ds, Item_Header& header)
	{
		DStreamBuffer buffer(DStream::input);
		if (Base::check_and_decode(ds, buffer, header)) {
			do_decode(ds, buffer);
			return true;
		}
		else
			return false;
	}

	Implementation_Class_UID_Sub_Item::Implementation_Class_UID_Sub_Item()
		: avail() {}

  void Implementation_Class_UID_Sub_Item::encode(DStream& ds)
  {
		if (avail) {
			DStreamBuffer buffer(DStream::output);
		  string & tmp = implementation_class_uid.rep();
			PDU_TS::encode_string(buffer, tmp, tmp.size());
			Base::encode(ds, buffer);
		}
	}
		
	void Implementation_Class_UID_Sub_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		string tmp;
		PDU_TS::decode_string(buffer, tmp, item_length);
		implementation_class_uid = tmp;
		avail = true;
	}

	void Implementation_Class_UID_Sub_Item::decode(DStream& ds)
	{
		DStreamBuffer buffer(DStream::input);
		Base::decode(ds, buffer);
		do_decode(ds, buffer);
	}

	// CODE: do that with virtual functions
	bool Implementation_Class_UID_Sub_Item::check_and_decode(DStream& ds, Item_Header& header)
	{
		DStreamBuffer buffer(DStream::input);
		if (Base::check_and_decode(ds, buffer, header)) {
			do_decode(ds, buffer);
			return true;
		}
		else
			return false;
	}

	Implementation_Version_Name_Sub_Item::Implementation_Version_Name_Sub_Item()
		: avail() {}

  void Implementation_Version_Name_Sub_Item::encode(DStream& ds)
  {
		if (avail) {
			DStreamBuffer buffer(DStream::output);
			string& str = implementation_version_name;
			PDU_TS::encode_string(buffer, str, str.size());
			Base::encode(ds, buffer);
		}
	}
		
	void Implementation_Version_Name_Sub_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		string tmp;
		PDU_TS::decode_string(buffer, tmp, item_length);
		implementation_version_name = tmp;
		avail = true;
	}

	void Implementation_Version_Name_Sub_Item::decode(DStream& ds)
	{
		DStreamBuffer buffer(DStream::input);
		Base::decode(ds, buffer);
		do_decode(ds, buffer);
	}

	// CODE: do that with virtual functions
	bool Implementation_Version_Name_Sub_Item::check_and_decode(DStream& ds, Item_Header& header)
	{
		DStreamBuffer buffer(DStream::input);
		if (Base::check_and_decode(ds, buffer, header)) {
			do_decode(ds, buffer);
			return true;
		}
		else
			return false;
	}

  void User_Information_Item::encode(DStream& ds)
  {
	  DStreamBuffer buffer(DStream::output);
		if (maximum_length_sub_item.avail)
			maximum_length_sub_item.encode(buffer);
		if (implementation_class_uid_sub_item.avail)
			implementation_class_uid_sub_item.encode(buffer);
		if (implementation_version_name_sub_item.avail)
			implementation_version_name_sub_item.encode(buffer);
		Base::encode(ds, buffer);
  }
		
	void User_Information_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		while (buffer.position < item_length) {
			Item_Header header;
			header.decode(buffer);
			if (! (    maximum_length_sub_item.check_and_decode(buffer, header)
							|| implementation_class_uid_sub_item.check_and_decode(buffer, header)
							|| implementation_version_name_sub_item.check_and_decode(buffer, header)
						 ) )
						 ignore_sub_item(buffer, header);
		}
	}

	void User_Information_Item::decode(DStream& ds)
	{
		DStreamBuffer buffer(DStream::input);
		Base::decode(ds, buffer);
		do_decode(ds, buffer);
	}

	bool User_Information_Item::check_and_decode(DStream& ds, Item_Header& header)
	{
		DStreamBuffer buffer(DStream::input);
		if (Base::check_and_decode(ds, buffer, header)) {
			do_decode(ds, buffer);
			return true;
		}
		else
			return false;
	}

	Associate_RQ_PDU::Associate_RQ_PDU() 
	: reserved1(0)
	{
		reserved2.append(32, '\0');
	}

	void Associate_RQ_PDU::encode(DStream& ds)
	{
		PDU_TS::encode_binary(ds, protocol_version);
		PDU_TS::encode_binary(ds, reserved1);
		called_ae_title.append(16-called_ae_title.size(), ' ');
		PDU_TS::encode_string(ds, called_ae_title, 16);
		calling_ae_title.append(16-calling_ae_title.size(), ' ');
		PDU_TS::encode_string(ds, calling_ae_title, 16);
		PDU_TS::encode_string(ds, reserved2, 32);
		application_context_item.encode(ds);
		list<RQ_Presentation_Context_Item>::iterator i = presentation_context_items.begin(),
			j = presentation_context_items.end();
		for (; i!=j; i++)
			i->encode(ds);
		user_information_item.encode(ds);
	}

	void Associate_RQ_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		PDU_TS::decode_binary(ds, protocol_version);
		PDU_TS::decode_binary(ds, reserved1);
		PDU_TS::decode_string(ds, called_ae_title, 16);
		PDU_TS::decode_string(ds, calling_ae_title, 16);
		PDU_TS::decode_string(ds, reserved2, 32);
		application_context_item.decode(ds);
		presentation_context_items.clear();
		while (ds.position < pdu_length) {
			RQ_Presentation_Context_Item pc_item;
			Item_Header header;
			header.decode(ds);
			if ( pc_item.check_and_decode(ds, header) )
				presentation_context_items.push_back(pc_item);
			else
				user_information_item.check_and_decode(ds, header);
		}
	}

	Associate_AC_PDU::Associate_AC_PDU(Associate_RQ_PDU& rq)
	: reserved1(0),
	  reserved2(rq.called_ae_title),
		reserved3(rq.calling_ae_title),
		reserved4(rq.reserved2),
		protocol_version(0x1)
	{}

	void Associate_AC_PDU::encode(DStream& ds)
	{
		PDU_TS::encode_binary(ds, protocol_version);
		PDU_TS::encode_binary(ds, reserved1);
		PDU_TS::encode_string(ds, reserved2, 16);
		PDU_TS::encode_string(ds, reserved3, 16);
		PDU_TS::encode_string(ds, reserved4, 32);
		application_context_item.encode(ds);
	  list<AC_Presentation_Context_Item>::iterator i = presentation_context_items.begin(),
	    j = presentation_context_items.end();
	  for (; i!=j; i++)
	    i->encode(ds);
		user_information_item.encode(ds);
	}
	void Associate_AC_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		PDU_TS::decode_binary(ds, protocol_version);
		PDU_TS::decode_binary(ds, reserved1);
		PDU_TS::decode_string(ds, reserved2, 16);
		PDU_TS::decode_string(ds, reserved3, 16);
		PDU_TS::decode_string(ds, reserved4, 32);
		application_context_item.decode(ds);
		presentation_context_items.clear();
		while (ds.position < pdu_length) {
			AC_Presentation_Context_Item pc_item;
			Item_Header header;
			header.decode(ds);
			if ( pc_item.check_and_decode(ds, header) )
				presentation_context_items.push_back(pc_item);
			else
				user_information_item.check_and_decode(ds, header);
		}
	}

	Associate_RJ_PDU::Associate_RJ_PDU()
		: reserved1(0) {}

	void Associate_RJ_PDU::encode(DStream& ds)
	{
		PDU_TS::encode_binary(ds, reserved1);
		PDU_TS::encode_binary(ds, result);
		PDU_TS::encode_binary(ds, source);
		PDU_TS::encode_binary(ds, reason);
	}
	void Associate_RJ_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		PDU_TS::decode_binary(ds, reserved1);
		PDU_TS::decode_binary(ds, result);
		PDU_TS::decode_binary(ds, source);
		PDU_TS::decode_binary(ds, reason);
	}

	void PDV_Item::encode(DStream& ds)
	{
		int message_length = message_fragment.size();
		item_length = message_length + 2;
		PDU_TS::encode_binary(ds, item_length);
		PDU_TS::encode_binary(ds, presentation_context_id);
		PDU_TS::encode_binary(ds, message_header);
		PDU_TS::encode_byte_array(ds, &message_fragment.front(), message_length);
	}

	void PDV_Item::do_decode(DStream& ds, DStreamBuffer& buffer)
	{
		// obsolete
	}
	void PDV_Item::decode(DStream& ds)
	{
		PDU_TS::decode_binary(ds, item_length);
		PDU_TS::decode_binary(ds, presentation_context_id);
		PDU_TS::decode_binary(ds, message_header);
		int message_length = item_length-2;
		message_fragment.resize(message_length);
		PDU_TS::decode_byte_array(ds, &message_fragment.front(), message_length);
	}

	bool PDV_Item::check_and_decode(DStream& ds, int item_length)
	{
		// obsolete
		return (item_length >= 2);
	}

	void P_DATA_TF_PDU::encode(DStream& ds)
	{
		list<PDV_Item>::iterator i = pdv_items.begin(), j = pdv_items.end();
		for (; i!=j ; i++)
			i->encode(ds);
	}
	void P_DATA_TF_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		pdv_items.clear();
		while (ds.position < pdu_length) {
			list<PDV_Item>::iterator i = pdv_items.insert(pdv_items.end());
			i->decode(ds);
		}
	}

	void A_RELEASE_RQ_PDU::encode(DStream& ds)
	{
		PDU_TS::encode_binary(ds, reserved);
	}
	void A_RELEASE_RQ_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		PDU_TS::decode_binary(ds, reserved);
	}

	void A_RELEASE_RP_PDU::encode(DStream& ds)
	{
		PDU_TS::encode_binary(ds, reserved);
	}
	void A_RELEASE_RP_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		PDU_TS::decode_binary(ds, reserved);
	}

	void A_ABORT_PDU::encode(DStream& ds)
	{
		PDU_TS::encode_binary(ds, reserved1);
		PDU_TS::encode_binary(ds, reserved2);
		PDU_TS::encode_binary(ds, source);
	}
	void A_ABORT_PDU::decode(DStream& ds)
	{
		pdu_length = ds.input_size;

		PDU_TS::decode_binary(ds, reserved1);
		PDU_TS::decode_binary(ds, reserved2);
		PDU_TS::decode_binary(ds, source);
	}
