/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef PDU_Interface
#define PDU_Interface 1

#include "General.hxx"
#include "DStreamBuffer.hxx"
#include "TransferSyntaxes.hxx"

struct Item_Base {
  typedef ExplicitVRBigEndian PDU_TS;
  char item_type;
  char reserved;
  short item_length;
  void encode(DStream& ds, DStreamBuffer& buffer);
  void decode(DStream& ds, DStreamBuffer& buffer);
};

class PDU_Header {
public:
  typedef ExplicitVRBigEndian PDU_TS;
 
	char pdu_type;
  char reserved;
  unsigned long pdu_length;

  void decode(DStream& ds);
  void encode(DStream& ds);
};

template <char pdu_type> class PDU_Base
{
public:

  typedef ExplicitVRBigEndian PDU_TS;    // PDU Transfer Syntax
  typedef ImplicitVRLittleEndian CMD_TS; // Command Transfer Syntax

  typedef PDU_Base<pdu_type> Self;
  unsigned long pdu_length;

  // encode item header... precondition: buffer encoded
  void encode(DStream& ds, DStreamBuffer& buffer)
  {
    PDU_Header header;
    header.pdu_type = pdu_type;
    pdu_length = buffer.length();
	  header.pdu_length = pdu_length;
    header.encode(ds);
	  // send out buffer
	  buffer.transfer(ds);
  }

  // postcondition: buffer ready to decode
  void decode(DStream& ds, DStreamBuffer& buffer)
  {
    PDU_Header header;
    header.decode(ds);
    pdu_length = header.pdu_length;
	  // load buffer
	  buffer.load(ds, pdu_length);
  }

  // returns true if item is decoded
  bool check_and_decode(DStream& ds, DStreamBuffer& buffer, PDU_Header& header)
  {
    if (header.pdu_type == pdu_type) {
      pdu_length = header.pdu_length;
      buffer.load(ds, pdu_length);
      return true;
    }
    else
      return false;
  }
};

  struct Item_Header
  {
    typedef ExplicitVRBigEndian PDU_TS;    // PDU Transfer Syntax

    char item_type;
    char reserved;
	  unsigned short item_length;

    void decode(DStream& ds);
    void encode(DStream& ds);
  };

template <char item_type> class PDU_Item_Base
{
public:
  typedef ExplicitVRBigEndian PDU_TS;    // PDU Transfer Syntax
  typedef ImplicitVRLittleEndian CMD_TS; // Command Transfer Syntax

  typedef PDU_Item_Base<item_type> Self;
  unsigned short item_length;

  // encode item header... precondition: buffer encoded
  void encode(DStream& ds, DStreamBuffer& buffer)
  {
    Item_Header header;
    header.item_type = item_type;
    item_length = buffer.length();
	  header.item_length = item_length;
    header.encode(ds);
	  // send out buffer
	  buffer.transfer(ds);
  }

  // postcondition: buffer ready to decode
  void decode(DStream& ds, DStreamBuffer& buffer)
  {
    Item_Header header;
    header.decode(ds);
    item_length = header.item_length;
	  // load buffer
	  buffer.load(ds, item_length);
  }

  // returns true if item is decoded
  bool check_and_decode(DStream& ds, DStreamBuffer& buffer, Item_Header& header)
  {
    if (header.item_type == item_type) {
      item_length = header.item_length;
      buffer.load(ds, item_length);
      return true;
    }
    else
      return false;
  }

  void ignore_sub_item(DStream& ds, Item_Header& header)
	{
		DStreamBuffer dummy(DStream::input);
		dummy.load(ds, header.item_length);
	}

	//friend bool operator==(Self& a, Self& b);
  // bool operator==(Self& s) { return false; }
};

template<char _c> bool operator==(PDU_Item_Base <_c> a, PDU_Item_Base <_c> b)
  { return false; }


class Application_Context_Item : PDU_Item_Base< application_context_item_type >
{
public:
  typedef PDU_Item_Base< application_context_item_type > Base;

  static UI default_application_context_name;
		
  UI application_context_name;

	Application_Context_Item();
	
  void encode(DStream& ds);
		
  void decode(DStream& ds);
};

  class Abstract_Syntax_Sub_Item : PDU_Item_Base< abstract_syntax_item_type >
  {
  public:
    typedef PDU_Item_Base< abstract_syntax_item_type > Base;
	  UI abstract_syntax_name;
		
	  void encode(DStream& ds);
		
	  void decode(DStream& ds);
  };

  class Transfer_Syntax_Sub_Item : PDU_Item_Base< transfer_syntax_item_type >
  {
  public:
    typedef PDU_Item_Base< transfer_syntax_item_type > Base;
	  UI transfer_syntax_name;
		
	  void encode(DStream& ds);
		void do_decode(DStream& ds, DStreamBuffer& buffer);
		void decode(DStream& ds);
		bool check_and_decode(DStream& ds, Item_Header& header);
  };

  inline bool operator ==(Transfer_Syntax_Sub_Item a, Transfer_Syntax_Sub_Item b) { return false; }
  inline bool operator !=(const Transfer_Syntax_Sub_Item a, const Transfer_Syntax_Sub_Item& b) { return false; }
  inline bool operator >(const Transfer_Syntax_Sub_Item a, const Transfer_Syntax_Sub_Item& b) { return false; }
  inline bool operator <(const Transfer_Syntax_Sub_Item a, const Transfer_Syntax_Sub_Item& b) { return false; }

class RQ_Presentation_Context_Item : PDU_Item_Base< rq_presentation_context_item_type >
{
public:
  typedef PDU_Item_Base< rq_presentation_context_item_type > Base;
  char presentation_context_ID;
  char reserved1;
  char reserved2;
  char reserved3;
  Abstract_Syntax_Sub_Item abstract_syntax_sub_item;
  list<Transfer_Syntax_Sub_Item> transfer_syntax_sub_items;

  void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, Item_Header& header);

};

  inline bool operator ==(RQ_Presentation_Context_Item a, RQ_Presentation_Context_Item b) { return false; }
  inline bool operator !=(const RQ_Presentation_Context_Item a, const RQ_Presentation_Context_Item& b) { return false; }
  inline bool operator >(const RQ_Presentation_Context_Item a, const RQ_Presentation_Context_Item& b) { return false; }
  inline bool operator <(const RQ_Presentation_Context_Item a, const RQ_Presentation_Context_Item& b) { return false; }

class AC_Presentation_Context_Item : PDU_Item_Base< ac_presentation_context_item_type >
{
public:
  typedef PDU_Item_Base< ac_presentation_context_item_type > Base;
  char presentation_context_ID;
  char reserved1;
  char result_reason;
  char reserved2;
  Transfer_Syntax_Sub_Item transfer_syntax_sub_item;

  void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, Item_Header& header);

};

  inline bool operator ==(AC_Presentation_Context_Item a, AC_Presentation_Context_Item b) { return false; }
  inline bool operator !=(const AC_Presentation_Context_Item a, const AC_Presentation_Context_Item& b) { return false; }
  inline bool operator >(const AC_Presentation_Context_Item a, const AC_Presentation_Context_Item& b) { return false; }
  inline bool operator <(const AC_Presentation_Context_Item a, const AC_Presentation_Context_Item& b) { return false; }

class Maximum_Length_Sub_Item : PDU_Item_Base< maximum_length_subitem_type >
{
public:
  typedef PDU_Item_Base< maximum_length_subitem_type > Base;
	bool avail;
	unsigned long maximum_length_received;

	Maximum_Length_Sub_Item();
  void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, Item_Header& header);
};

class Implementation_Class_UID_Sub_Item : PDU_Item_Base< implementation_class_uid_subitem_type >
{
public:
  typedef PDU_Item_Base< implementation_class_uid_subitem_type > Base;
	bool avail;
	UI implementation_class_uid;

	Implementation_Class_UID_Sub_Item();
  void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, Item_Header& header);
};

// CODE: these make a class of Sub Item's, so might be organized as a generic class
class Implementation_Version_Name_Sub_Item : PDU_Item_Base< implementation_version_name_subitem_type >
{
public:
  typedef PDU_Item_Base< implementation_version_name_subitem_type > Base;
	bool avail;
	string implementation_version_name;

	Implementation_Version_Name_Sub_Item();
  void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, Item_Header& header);
};

class User_Information_Item : PDU_Item_Base< user_information_item_type >
{
public:
  typedef PDU_Item_Base< user_information_item_type > Base;

	Maximum_Length_Sub_Item maximum_length_sub_item;
	Implementation_Class_UID_Sub_Item implementation_class_uid_sub_item;
	Implementation_Version_Name_Sub_Item implementation_version_name_sub_item;

  void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, Item_Header& header);
};

class Associate_RQ_PDU : public PDU_Base<associate_rq_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	short protocol_version;
	short reserved1;
	string called_ae_title;
	string calling_ae_title;
	string reserved2;
	Application_Context_Item application_context_item;
	list< RQ_Presentation_Context_Item > presentation_context_items;
	User_Information_Item user_information_item;

	Associate_RQ_PDU();
	void encode(DStream& ds);
	void decode(DStream& ds);
};

class Associate_AC_PDU : public PDU_Base<associate_ac_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	short protocol_version;
	short reserved1;
	string reserved2;
	string reserved3;
	string reserved4;
	Application_Context_Item application_context_item;
	list< AC_Presentation_Context_Item > presentation_context_items;
	User_Information_Item user_information_item;

	Associate_AC_PDU() {}
	Associate_AC_PDU(Associate_RQ_PDU& rq);
	void encode(DStream& ds);
	void decode(DStream& ds);
};

class Associate_RJ_PDU : public PDU_Base<associate_rj_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	char reserved1;
	char result;
	char source;
	char reason;

	Associate_RJ_PDU();
	void encode(DStream& ds);
	void decode(DStream& ds);
};

class PDV_Item
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	long item_length;
	char presentation_context_id;
	char message_header;
	vector<char> message_fragment;

	void encode(DStream& ds);
	void do_decode(DStream& ds, DStreamBuffer& buffer);
	void decode(DStream& ds);
	bool check_and_decode(DStream& ds, int item_length);
};

  inline bool operator ==(PDV_Item a, PDV_Item b) { return false; }
  inline bool operator !=(const PDV_Item a, const PDV_Item& b) { return false; }
  inline bool operator >(const PDV_Item a, const PDV_Item& b) { return false; }
  inline bool operator <(const PDV_Item a, const PDV_Item& b) { return false; }

class P_DATA_TF_PDU : public PDU_Base<p_data_tf_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	list<PDV_Item> pdv_items;

	void encode(DStream& ds);
	void decode(DStream& ds);
};

class A_RELEASE_RQ_PDU : public PDU_Base<a_release_rq_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	long reserved;

	void encode(DStream& ds);
	void decode(DStream& ds);

};

class A_RELEASE_RP_PDU : public PDU_Base<a_release_rp_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	long reserved;

	void encode(DStream& ds);
	void decode(DStream& ds);

};

class A_ABORT_PDU : PDU_Base<a_abort_type>
{
public:
	typedef ExplicitVRBigEndian PDU_TS;

	char reserved1;
	char reserved2;
	char source;

	void encode(DStream& ds);
	void decode(DStream& ds);
};

#endif
