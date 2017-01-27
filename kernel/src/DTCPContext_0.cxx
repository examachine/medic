/*
**
** Implementation file for module
**
**
**
** exa
**
*/

#include <KernelInterface.hxx>
#include <Messages.hxx>
#include <SOPClasses.hxx>
#include "ClientSocket.h"
#include "ServerSocket.h"

//CODE: timeouts
//CODE: advanced exception handling

DTCPContext::DTCPContext(Mode m) {
  switch (m) {
  case client:
    state = idle;
    message_id = 0;
    break;
  case server:
    state = awaiting_associate_rq;
    break;
  default:
    throw DException("Invalid DTCPContext mode");
  }

}

void DTCPContext::associate(const string & calledAE,
			    Association_Type association_type)
{
  // check from the address book
  try {

    if (state!=idle)
      throw DException("DTCPContext: protocol violation");

    // establish connection
    //begin_client_thread(calledAE); // check it out might burn
    called_ae = calledAE;

		
    AE tmp = AE(calledAE);
    if (dicom_app.address_book.find(tmp)==dicom_app.address_book.end())
      throw DException(string("AE ") + calledAE + " unknown");

    socket = new ClientSocket;
#ifdef _MSC_VER
    // CODE: portable sockets!
    //socket->Create();
    socket->m_pCallingThread = AfxGetThread();
    socket->m_fPDUHeader = true;
    if (!socket->connect( dicom_app.address_book[tmp].address.c_str(),
			  dicom_app.address_book[tmp].port ))
      throw DException(string("Unable to connect to AE ") + calledAE);
#endif
		
    // send association request

    DTCPStream out(*socket, DStream::output);
    out.begin_write(associate_rq_type);
    Associate_RQ_PDU rq;  // rq first
    rq.protocol_version = 1;
    rq.called_ae_title = calledAE;
    rq.calling_ae_title = *dicom_app.ae_title;

    // presentation contexts
		
    switch (association_type) {
    case normal: {
      SOPs::iterator s1 = dicom_app.sops.begin(),
	s2 = dicom_app.sops.end();
      int pc_id = 1;
      for (; s1!=s2; s1++) {
	const UI& abstract_syntax = s1->first;
	SOP* sop = s1->second;
	const list<UI> & ts = sop->list_ts();
	list<UI>::const_iterator t1 = ts.begin(), t2 = ts.end();
	RQ_Presentation_Context_Item p_item;
	p_item.abstract_syntax_sub_item.abstract_syntax_name = abstract_syntax;
	p_item.presentation_context_ID = pc_id;
	as_id_map[abstract_syntax] = pc_id;
	for (;t1!=t2;t1++) {
	  Transfer_Syntax_Sub_Item & ts_subitem = *p_item.transfer_syntax_sub_items.insert(p_item.transfer_syntax_sub_items.end());
	  ts_subitem.transfer_syntax_name = *t1;
	}
	rq.presentation_context_items.push_back(p_item);
	pc_id+=2;
      }
    }
      break;
    case verification: {
      RQ_Presentation_Context_Item p_item;
      const UI& abstract_syntax = VerificationSOPClass::UID;
      p_item.abstract_syntax_sub_item.abstract_syntax_name = abstract_syntax;
      p_item.presentation_context_ID = 1;
      as_id_map[abstract_syntax] = 1;
      Transfer_Syntax_Sub_Item & ts_subitem = *p_item.transfer_syntax_sub_items.insert(p_item.transfer_syntax_sub_items.end());
      ts_subitem.transfer_syntax_name = ImplicitVRLittleEndian::UID;
      rq.presentation_context_items.push_back(p_item);
    }
      break;
    }

    // user information item
    rq.user_information_item.maximum_length_sub_item.avail = true;
    rq.user_information_item.maximum_length_sub_item.maximum_length_received = 
      TCP_PDATA::default_max_pdv_list_size;
    rq.user_information_item.implementation_class_uid_sub_item.avail = true;
    rq.user_information_item.implementation_class_uid_sub_item.implementation_class_uid =
      dicom_app.implementation_uid;
    rq.user_information_item.implementation_version_name_sub_item.avail = true;
    rq.user_information_item.implementation_version_name_sub_item.implementation_version_name =
      *dicom_app.implementation_version_name;

    rq.encode(out);

    out.end_write();

    state = awaiting_associate_ac;

    // receive association acknowledgement
    DTCPStream in(*socket, DStream::input);
    PDUType pt2 = in.begin_read();
    switch (pt2) {
    case associate_ac_type: {
      Associate_AC_PDU ac_pdu;
      ac_pdu.decode(in);
      in.end_read();
      if (! (ac_pdu.protocol_version & 0x1) )
	throw DException ("Client: Invalid protocol version");

      // extract presentation context
      // presentation context items
      // transfer to internal data structure
      list<AC_Presentation_Context_Item>::iterator p1 = ac_pdu.presentation_context_items.begin(),
	p2 = ac_pdu.presentation_context_items.end();
      for (; p1!=p2; p1++) {
	// convert the class/metaclass UID.
	UI& transfer_syntax = p1->transfer_syntax_sub_item.transfer_syntax_name;
	id_ts_map[p1->presentation_context_ID] = transfer_syntax;
      }

      state = association_established;

      dgn(string("Client: DICOM Association with ") + calledAE + " established");
    } break;
    case associate_rj_type: {
      state = idle;
      dgn(string("Client: DICOM Association with ") + calledAE + " rejected");
    } break;
    default:
      throw DException("Client: Protocol Violation");
    }
  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while associating");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while associating");
  }
#endif _MSC_VER
}

void DTCPContext::release()
{
  try {

    if (state==idle)
      throw DException("DTCPContext: protocol violation");

    // send release request
    DTCPStream out(*socket, DStream::output);
    out.begin_write(a_release_rq_type);
    A_RELEASE_RQ_PDU rq_pdu;
    rq_pdu.reserved = 0x00000000;
    rq_pdu.encode(out);
    out.end_write();

    // await release response
    DTCPStream in(*socket, DStream::input);
    PDUType pt2 = in.begin_read();
    A_RELEASE_RP_PDU rp_pdu;
    rp_pdu.decode(in);
    in.end_read();
    dgn(string("Client: DICOM Association with ") + *called_ae + " released");
    state = idle;
  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error releasing association");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error releasing association");
  }
#endif
}

void DTCPContext::cecho()
{
  const UI& class_uid = VerificationSOPClass::UID;
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    if (as_id_map.find(class_uid) == as_id_map.end())
      throw DException("Abstract Syntax not negotiated");

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    CEchoRQMsg rq_msg;

    rq_msg.modAffectedSOPClassUID( class_uid );
    rq_msg.modCommandField( 0x0030 ); // C-ECHO
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modDataSetType( 0x0101 ); // null

    CEchoRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);

    out.end_write();

    // check message
    //DTCPStream in(*socket, DStream::input);
    TCP_PDATA in(*socket, DStream::input, as_id_map[class_uid]);
    in.begin_read(TCP_PDATA::command_set);
    //PDUType pt = in.begin_read();
    //switch (pt) {
    //case p_data_tf_type: {
    CEchoRSPMsg rsp_msg;
    CEchoRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.decode(in, rsp_msg);
    in.end_read();
    dgn(string("Client: C-ECHO complete"));
    //								 } break;
    //default:
    //	throw DException("Client: Protocol Violation");
    //}

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while C-ECHO");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while C-ECHO");
  }
#endif
}

void DTCPContext::cstore(SOP& sop)
{
  // Initiate the P-DATA service
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // construct C-STORE RQ Message

    AbstractSOPCommonMod& sopcommon = dynamic_cast<AbstractSOPCommonMod&>(sop);
    const UI& class_uid = sopcommon.selSOPClassUID();
    const UI& instance_uid = sopcommon.selSOPInstanceUID();
    int presentation_context_id = as_id_map[class_uid];
    if (id_ts_map.find(presentation_context_id)==id_ts_map.end())
      throw DException("DTCPContext: no appropriate TS");
    const UI& ts_uid = id_ts_map[presentation_context_id];

    TCP_PDATA out(*socket, DStream::output, presentation_context_id);
    out.begin_write(TCP_PDATA::command_set);
    CStoreRQMsg rq_msg;

    rq_msg.modAffectedSOPClassUID( class_uid );
    rq_msg.modCommandField( 0x0001 ); // C-STORE
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modPriority( 0x0002 ); // medium
    rq_msg.modDataSetType( 0xffff ); // not null
    rq_msg.modAffectedSOPInstanceUID( instance_uid );

    CStoreRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // encode object
    out.begin_write(TCP_PDATA::data_set);
    sop.encode(out, ts_uid);

    out.end_write();

    // check message
    DTCPStream in_stream(*socket, DStream::input);
    PDUType pdu_type = in_stream.begin_read();
    switch (pdu_type) {
    case p_data_tf_type: {
      TCP_PDATA in_pdata(in_stream);
      in_pdata.begin_read(TCP_PDATA::command_set);
      CStoreRSPMsg rsp_msg;
      CStoreRSPMsg::Coder<CMD_TS> rsp_coder;
      rsp_coder.decode(in_pdata, rsp_msg);
      in_pdata.end_read();
      dgn(string("Client: C-STORE complete"));
    } break;
    default:
      throw DException("Client: Protocol Violation");
    }

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while C-STORE");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while C-STORE");
  }
#endif
}

// takes an Information Model SOP Instance as input
// returns a list of Identifiers
list<SOP*> DTCPContext::cfind(SOP& query_identifier)
{
  Info_Model info_model;
  QR_Level qr_level;

  // these will be the same type with the query_identifier
  list<SOP*> resulting_identifiers;

  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // construct C-FIND RQ Message

    const UI& class_uid = query_identifier.sel_class_id();
    int presentation_context_id = as_id_map[class_uid];
    if (id_ts_map.find(presentation_context_id)==id_ts_map.end())
      throw DException("DTCPContext: no appropriate TS");
    const UI& ts_uid = id_ts_map[presentation_context_id];

    TCP_PDATA out(*socket, DStream::output, presentation_context_id);
    out.begin_write(TCP_PDATA::command_set);
    CFindRQMsg rq_msg;

    rq_msg.modAffectedSOPClassUID( class_uid );
    rq_msg.modCommandField( 0x0020 ); // C-FIND
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modPriority( 0x0002 ); // medium
    rq_msg.modDataSetType( 0xffff ); // not null

    CFindRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // check our information model and query/retrieve level
    if ( typeid(query_identifier).before(typeid(PatientRootQRInfoModelFIND&)) ) {
      info_model = patient_root;
      PatientRootQRInfoModelFIND& identifier =
	dynamic_cast<PatientRootQRInfoModelFIND&>(query_identifier);
      if (*identifier.selQueryRetrieveLevel()=="PATIENT")
	qr_level = patient;
      else if (*identifier.selQueryRetrieveLevel()=="STUDY")
	qr_level = study;
      else if (*identifier.selQueryRetrieveLevel()=="SERIES")
	qr_level = series;
      else if (*identifier.selQueryRetrieveLevel()=="IMAGE")
	qr_level = image;
      else
	throw DException("Invalid Query/Retrieve Level");
    }
    else /*if typeid(query_identifier).before(typeid(StudyRootQRInfoModelFIND&)) {
	   info_model = patient_root;
	   }*/
      throw DException("Information Model Unavailable");


    // encode object
    out.begin_write(TCP_PDATA::data_set);
    query_identifier.encode(out, ts_uid);

    out.end_write();


    // check messages, note that we expect multiple messages

    bool last_message_processed = false;

    while (!last_message_processed) {
      // we gotta check the input PDU
      DTCPStream in_stream(*socket, DStream::input);
      PDUType pdu_type = in_stream.begin_read();
      switch (pdu_type) {
      case p_data_tf_type: {
	TCP_PDATA in_pdata(in_stream);
	in_pdata.begin_read(TCP_PDATA::command_set);
	CFindRSPMsg rsp_msg;
	CFindRSPMsg::Coder<CMD_TS> rsp_coder;
	rsp_coder.decode(in_pdata, rsp_msg);

	// check if last message
	int status = *rsp_msg.selStatus();
	if (status==0) // success
	  last_message_processed = true;
	else if ( (status==0xff00) || (status=0xff01) ) {
	  // decode identifier

	  SOP& matched_identifier = query_identifier.gen(false); // transient object

	  // fill in attributes
	  in_pdata.begin_read(TCP_PDATA::data_set);
	  matched_identifier.decode(in_pdata, ts_uid);

	  switch (info_model) {
	  case patient_root: {					
	    // add to our list
	    resulting_identifiers.push_back(&matched_identifier);
	  } break;
	  }
	}
	else
	  throw DException("Client: C-FIND failed");

	in_pdata.end_read();
      } break;
      default:
	throw DException("Client: Protocol Violation");
      }
    } // end while
    dgn(string("Client: C-FIND complete"));

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while C-FIND");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while C-FIND");
  }
#endif
  return resulting_identifiers;
}

// retrieves the SOP instances which are the result
// of the query inicated by the Information Model SOP Instance parameter
// returns a list of SOP Instances which have been successfully retrieved.
list<DPtr> DTCPContext::cget(SOP& query_identifier)
{
  Info_Model info_model;
  QR_Level qr_level;

  list<DPtr> retrieved_objects;

  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // construct C-GET RQ Message

    const UI& class_uid = query_identifier.sel_class_id();
    int presentation_context_id = as_id_map[class_uid];
    if (id_ts_map.find(presentation_context_id)==id_ts_map.end())
      throw DException("DTCPContext: no appropriate TS");
    const UI& ts_uid = id_ts_map[presentation_context_id];

    TCP_PDATA out(*socket, DStream::output, presentation_context_id);
    out.begin_write(TCP_PDATA::command_set);
    CGetRQMsg rq_msg;

    rq_msg.modAffectedSOPClassUID( class_uid );
    rq_msg.modCommandField( 0x0010 ); // C-GET
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modPriority( 0x0002 ); // medium
    rq_msg.modDataSetType( 0xffff ); // not null

    CGetRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // check our information model and query/retrieve level
    if ( typeid(query_identifier).before(typeid(PatientRootQRInfoModelGET&)) ) {
      info_model = patient_root;
      PatientRootQRInfoModelGET& identifier =
	dynamic_cast<PatientRootQRInfoModelGET&>(query_identifier);
      if (*identifier.selQueryRetrieveLevel()=="PATIENT")
	qr_level = patient;
      else if (*identifier.selQueryRetrieveLevel()=="STUDY")
	qr_level = study;
      else if (*identifier.selQueryRetrieveLevel()=="SERIES")
	qr_level = series;
      else if (*identifier.selQueryRetrieveLevel()=="IMAGE")
	qr_level = image;
      else
	throw DException("Invalid Query/Retrieve Level");
    }
    else /*if typeid(query_identifier).before(typeid(StudyRootQRInfoModelGET&)) {
	   info_model = patient_root;
	   }*/
      throw DException("Information Model Unavailable");


    // encode object
    out.begin_write(TCP_PDATA::data_set);
    query_identifier.encode(out, ts_uid);

    out.end_write();

    // check messages, note that we expect multiple messages

    bool last_message_processed = false;

    while (!last_message_processed) {
      // we gotta check the input PDU
      DTCPStream in_stream(*socket, DStream::input);
      PDUType pdu_type = in_stream.begin_read();
      switch (pdu_type) {
      case p_data_tf_type: {
	TCP_PDATA pdata(in_stream);
	pdata.begin_read(TCP_PDATA::command_set);
	// parse till we can figure out type of command...
	// KLUDGE: a bit of kludge since PDV might be really small ;)
	Attribute command_attr(Tag(0x0000,0x0100), "CommandField", "US", VM(VM::single), false);
	US::Coder<CMD_TS> coder;
	US command_field;
	coder.decode_mandatory(pdata, command_field, command_attr);
	// CODE: is this exhaustive?
	// check the input P-DATA it could either be a C-STORE-RQ or C-GET-RSP
	TCP_PDATA in_pdata(in_stream);
	in_pdata.begin_read(TCP_PDATA::command_set);
	if (command_field==0x8010) {
	  CGetRSPMsg rsp_msg;
	  CGetRSPMsg::Coder<CMD_TS> rsp_coder;
	  rsp_coder.decode(in_pdata, rsp_msg);
					
	  // check if last message
	  int status = *rsp_msg.selStatus();
	  if (status==0) // success
	    last_message_processed = true;
	  else if (status==0xff00) {
	    // decode identifier
	    SOP& matched_identifier = query_identifier.gen(false); // transient object
	    // fill in attributes
	    in_pdata.begin_read(TCP_PDATA::data_set);
	    matched_identifier.decode(in_pdata, ts_uid);
	    switch (info_model) {
	    case patient_root: {					
	      // so it's patient root
	    } break;
	    }
	  }
	  in_pdata.end_read();
	}
	else if (command_field==0x0001) {
	  // that's a C-STORE request please serve it ;)
	  retrieved_objects.push_back(serve_cstore(in_pdata));
	}
	else
	  throw DException("Client: C-GET failed");

      } break;
      default:
	throw DException("Client: Protocol Violation");
      }
    } // end while
    dgn(string("Client: C-GET complete"));

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while C-GET");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while C-GET");
  }
#endif
  return retrieved_objects;
}

// obsolete
// wrapper for cget, retrieves indicated image SOP's
void DTCPContext::cget(const list<UI>& instance_uids) {
  // single query such as: 'all patients,studies,series and these images' is *impossible*
  /*
    PatientRootQRInfoModelGET identifier;
    identifier.modQueryRetrieveLevel("IMAGE");
    identifier.modPatientsName("AD2");
    list<SOP*> matched_identifiers;
    matched_identifiers = context.cget(identifier);	
  */
}

// create a normalized SOP instance with given class (instance_id giving not supported)
NCreateRSPMsg DTCPContext::ncreate(SOP& sop)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);

    NCreateRQMsg rq_msg;
    rq_msg.modAffectedSOPClassUID( sop.sel_class_id() );
    rq_msg.modCommandField( 0x0140 ); // N-CREATE
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modDataSetType( 0x0102 ); // not null

    // check validity of SOP class
    if (dicom_app.sops.find(sop.sel_class_id()) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    const UI& class_uid = sop.sel_class_id();
    const UI& ts_uid = ImplicitVRLittleEndian::UID; // KLUDGE fetch ts from pres. context

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);

    NCreateRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);
    // fix group length
    //out.write_first_groups_length();


    // encode object
    sop.encode(out, ts_uid);

    out.end_write();

    // check message
    TCP_PDATA in(*socket, DStream::input, as_id_map[class_uid]);
    in.begin_read(TCP_PDATA::command_set);
    //DTCPStream in(*socket, DStream::input);
    //PDUType pt = in.begin_read();
    //switch (pt) {
    //case p_data_tf_type: {
    NCreateRSPMsg rsp_msg;
    NCreateRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.decode(in, rsp_msg);
    in.end_read();
    dgn(string("Client: N-CREATE complete"));
    return rsp_msg;
    //								 } break;
    //default:
    //	throw DException("Client: Protocol Violation");
    //}

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while N-CREATE");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while N-CREATE");
  }
#endif
  return NCreateRSPMsg();
}

// create a normalized SOP instance with given class (instance_id giving not supported)
NSetRSPMsg DTCPContext::nset(DPtr& ptr, SOP& sop)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);

    NSetRQMsg rq_msg;
    rq_msg.modRequestedSOPClassUID( ptr.class_id );
    rq_msg.modRequestedSOPInstanceUID( ptr.instance_id );
    rq_msg.modCommandField( 0x0120 ); // N-SET
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modDataSetType( 0xffff ); // not null

    // check validity of SOP class
    if (dicom_app.sops.find(ptr.class_id) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    const UI& class_uid = ptr.class_id;
    const UI& ts_uid = ImplicitVRLittleEndian::UID; // KLUDGE fetch ts from pres. context

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);

    NSetRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);
    // fix group length
    //out.write_first_groups_length();


    // encode object
    sop.encode(out, ts_uid);

    out.end_write();

    // check message
    TCP_PDATA in(*socket, DStream::input, as_id_map[class_uid]);
    in.begin_read(TCP_PDATA::command_set);
    //DTCPStream in(*socket, DStream::input);
    //PDUType pt = in.begin_read();
    //switch (pt) {
    //case p_data_tf_type: {
    NSetRSPMsg rsp_msg;
	
    NSetRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.decode(in, rsp_msg);
    in.end_read();
    dgn(string("Client: N-SET complete"));
    return rsp_msg;
    //								 } break;
    //default:
    //	throw DException("Client: Protocol Violation");
    //}

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while N-SET");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while N-SET");
  }
#endif
  return NSetRSPMsg();
}

NActionRSPMsg DTCPContext::naction(DPtr& ptr, unsigned short action_type)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    const UI& class_uid = ptr.class_id;

    NActionRQMsg rq_msg;
    rq_msg.modRequestedSOPClassUID( ptr.class_id );
    rq_msg.modRequestedSOPInstanceUID( ptr.instance_id );
    rq_msg.modCommandField( 0x0130 ); // N-Action
    rq_msg.modMessageID( gen_message_id() );
    rq_msg.modActionTypeID(action_type);
    rq_msg.modDataSetType( 0xffff ); // not null

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);

    NActionRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.encode(out, rq_msg);
    // fix group length
    //out.write_first_groups_length();

    // check validity of SOP class
    if (dicom_app.sops.find(ptr.class_id) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    const UI& ts_uid = ImplicitVRLittleEndian::UID; // KLUDGE fetch ts from pres. context

    out.end_write();

    // check message
    TCP_PDATA in(*socket, DStream::input, as_id_map[class_uid]);
    in.begin_read(TCP_PDATA::command_set);
    //DTCPStream in(*socket, DStream::input);
    //PDUType pt = in.begin_read();
    //switch (pt) {
    //case p_data_tf_type: {
    NActionRSPMsg rsp_msg;
	
    NActionRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.decode(in, rsp_msg);
    in.end_read();
    dgn(string("Client: N-ACTION complete"));
    return rsp_msg;
    //								 } break;
    //default:
    //	throw DException("Client: Protocol Violation");
    //}

  }
  catch (DException e) {
    e.why();
    throw DException("DTCPContext: error while N-ACTION");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DTCPContext: error while N-ACTION");
  }
#endif
  return NActionRSPMsg();
}
