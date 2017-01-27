/*
** Interface file for TCP_PDATA module
**
**
**
** exa
**
*/

#ifndef TCP_PDATA_Interface
#define TCP_PDATA_Interface 1


// encapsulates P-DATA services for a client TCP stream
class TCP_PDATA : public DStream
{
public:
  enum { default_max_pdv_list_size = 0x4000 };

  enum PDATA_Type { nodata, inherit_stream, command_set, data_set, end_data };

  TCP_PDATA(CustomSocket &, OpenMode _mode,
	    int p_c_id = -1, int n = default_max_pdv_list_size);
  TCP_PDATA(DTCPStream &, int p_c_id = -1, int n = default_max_pdv_list_size);
  ~TCP_PDATA();

  void begin_read(PDATA_Type);
  void read (char* buffer, int len);
  void end_read();

  void begin_write(PDATA_Type);
  void write (char* buffer, int len);
  void end_write();

public:
  //protected:
  CustomSocket & socket;
  P_DATA_TF_PDU p_data_tf;
  int max_pdv_list_size;
  int presentation_context_id;
  PDATA_Type pdata_type;
  bool last_pdv;

  DTCPStream* inherited_stream;

  // current PDV
  list<PDV_Item>::iterator current_pdv;
  vector<char>::iterator current_msg_data;
  int	remaining_bytes;
  int set_length;

  int send_pdata_tf();
  int receive_pdata_tf();
  void send_next_pdv();
  void receive_next_pdv();
  void write_first_groups_length(); // called after first group is finished
};

class DPDATA_Exception : public DException {
public:
  DPDATA_Exception() : DException("PDATA Protocol Violation") {}
  DPDATA_Exception(string s) : DException("PDATA: " + s) {}
};

#endif
