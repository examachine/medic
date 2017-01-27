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

#ifdef MEDIC_ARCHIVE
#include <CFindQuery.hxx>
#include <CGetQuery.hxx>
#endif // MEDIC_ARCHIVE

#include "ClientSocket.h"
#include "ServerSocket.h"

//CODE: timeouts
//CODE: advanced exception handling

void DTCPContext::serve(ServerSocket& _socket)
{
  // start the dicom services
  // this routine is called from CServerSocket
  // which has effectively handled the initial communication
  // through a CServerThread
	
  // we have received a packet, let's see what it is

  socket = &_socket;
  // we gotta check the input PDU
  DTCPStream in(_socket, DStream::input);
  PDUType pdu_type = in.begin_read();

  if (state!=idle)
    if (pdu_type == a_release_rq_type) {
      serve_release(in);
      return;
    }

  switch (state) {
  case idle:
    throw DException("DTCPContext server: invalid packet");
    break;
  case awaiting_associate_rq:
    if (pdu_type == associate_rq_type) {
      serve_associate(in);
    }
    else
      throw DException("DTCPContext server: Protocol Violation");
    break;
  case association_established:
    if (pdu_type == p_data_tf_type) {
      // decode 
      //DTCPStream in(*socket, DStream::input);
      //in.begin_read();
      TCP_PDATA pdata(in);
      pdata.begin_read(TCP_PDATA::command_set);
      // CODE: P-DATA service

      // parse till we can figure out type of command...
      // KLUDGE: a bit of kludge since PDV might be really small ;)
      Attribute command_attr(Tag(0x0000,0x0100), "CommandField", "US", VM(VM::single), false);
      US::Coder<CMD_TS> coder;
      US command_field;
      coder.decode_mandatory(pdata, command_field, command_attr);
      TCP_PDATA pdata_service(in);
      pdata_service.begin_read(TCP_PDATA::command_set);
      try {
	switch (*command_field) {
	case 0x0001: serve_cstore(pdata_service); break;
#ifdef MEDIC_ARCHIVE
	  // CODE: viewing station doesn't support c-get or c-find
	case 0x0010: serve_cget(pdata_service); break;
	case 0x0020: serve_cfind(pdata_service); break;
#endif MEDIC_ARCHIVE
	case 0x0030: serve_cecho(pdata_service); break;
	case 0x0120: serve_nset(pdata_service); break;
	case 0x0130: serve_naction(pdata_service); break;
	case 0x0140: serve_ncreate(pdata_service); break;
	}
      }
      catch (DException e) {
	state = processing_command;
      }
    }
    else
      throw DException("DTCPContext server: Protocol Violation");
    break;
  case processing_command:
    //something faulty must have happened
    state = idle;
    throw DException("DTCPContext server: Unable to process PDU in faulty state ");
    break;
  default:
    throw DException("DTCPContext server: internal error, invalid state");
    break;
  }
}

void DTCPContext::serve_associate(DTCPStream & in)
{
  // process association request
  dgn("server: assocation request received");
  //DTCPStream in(*socket, DStream::input);
  //in.continue_read(0);
  Associate_RQ_PDU rq_pdu;
  rq_pdu.decode(in);
  in.end_read();
	
  // test header
  bool valid = (rq_pdu.protocol_version & 0x1) &&
    (AE(rq_pdu.called_ae_title) == dicom_app.ae_title);
  if (!valid) {
    // send association rejection
    DTCPStream out(*socket, DStream::output);
    out.begin_write(associate_rj_type);
    Associate_RJ_PDU reject_pdu;
    reject_pdu.reserved1 = 0;
    reject_pdu.result = 1; //permanent
    reject_pdu.source = 3; // UL service-provider
    reject_pdu.reason = 1; // no-reason
    reject_pdu.encode(out);
    out.end_write();
    // start ARTIM timer and wait for the connection to close
    throw DException("DTCPContext server: cannot establish association");
  }

  Associate_AC_PDU ac_pdu(rq_pdu);

  // application context item
  // we offer only one application context
  ac_pdu.application_context_item.application_context_name =
    Application_Context_Item::default_application_context_name;

  // presentation context items
  // issue the first TS that matches
  list<RQ_Presentation_Context_Item>::iterator p1 = rq_pdu.presentation_context_items.begin(),
    p2 = rq_pdu.presentation_context_items.end();
  for (; p1!=p2; p1++) {
    // do we have the class/metaclass UID?
    UI& abstract_syntax = p1->abstract_syntax_sub_item.abstract_syntax_name;
    if ( dicom_app.sops.check_class(abstract_syntax) ) {
      // great, find the first TS that matches
      bool found = false;
      list<Transfer_Syntax_Sub_Item>::iterator t1 = p1->transfer_syntax_sub_items.begin(),
	t2 = p1->transfer_syntax_sub_items.end();
      while ( (!found) && (t1!=t2) ) {
	if ( dicom_app.sops[abstract_syntax]->check_ts(t1->transfer_syntax_name) ) {
	  found = true;
	  AC_Presentation_Context_Item p_item;
	  int pc_id = p1->presentation_context_ID;
	  p_item.presentation_context_ID = pc_id;
	  p_item.result_reason = 0;
	  p_item.transfer_syntax_sub_item.transfer_syntax_name = t1->transfer_syntax_name;
	  ac_pdu.presentation_context_items.push_back(p_item);
	  // update internal structure as well
	  as_id_map[abstract_syntax] = pc_id;
	  id_ts_map[pc_id] = t1->transfer_syntax_name;
	  /*Presentation_Context & p_con = presentation_context_map[abstract_syntax];
	    p_con.id = p1->presentation_context_ID;
	    p_con.transfer_syntax = t1->transfer_syntax_name;*/
	}
	t1++;
      }
    }
  }

  // user information item
  user_information = rq_pdu.user_information_item;
  ac_pdu.user_information_item.maximum_length_sub_item.avail = true;
  ac_pdu.user_information_item.maximum_length_sub_item.maximum_length_received = 
    TCP_PDATA::default_max_pdv_list_size;
  ac_pdu.user_information_item.implementation_class_uid_sub_item.avail = true;
  ac_pdu.user_information_item.implementation_class_uid_sub_item.implementation_class_uid =
    dicom_app.implementation_uid;
  ac_pdu.user_information_item.implementation_version_name_sub_item.avail = true;
  ac_pdu.user_information_item.implementation_version_name_sub_item.implementation_version_name =
    *dicom_app.implementation_version_name;

  // send association acknowledgement
  DTCPStream out(*socket, DStream::output);
  out.begin_write(associate_ac_type);
  ac_pdu.encode(out);
  out.end_write();
  state = association_established;
}

void DTCPContext::serve_release(DTCPStream & in)
{
  //DTCPStream in(*socket, DStream::input);
  //in.continue_read(0);
  A_RELEASE_RQ_PDU rq_pdu;
  rq_pdu.decode(in);
  in.end_read();

  DTCPStream out(*socket, DStream::output);
  out.begin_write(a_release_rp_type);
  A_RELEASE_RP_PDU rp_pdu;
  rp_pdu.reserved = 0x00000000;
  rp_pdu.encode(out);
  out.end_write();
}

void DTCPContext::serve_cecho(TCP_PDATA & in)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    //DTCPStream in(*socket, DStream::input);
    //in.continue_read(0);
    CEchoRQMsg rq_msg;

    CEchoRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);

    const UI& class_uid = rq_msg.selAffectedSOPClassUID();

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    dicom_app.report("server: C-ECHO completed");

    in.end_read();

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);
    CEchoRSPMsg rsp_msg;
    rsp_msg.modCommandField( 0x8030 ); // C-ECHO
    rsp_msg.modAffectedSOPClassUID( rq_msg.selAffectedSOPClassUID() );
    rsp_msg.modDataSetType( 0x0101 ); // null
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modStatus( 0 ); // success
    CEchoRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);

    // fix group length
    //out.write_first_groups_length();
    out.end_write();
  }
  catch (DException e) {
    e.why();
    //throw e;
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    //throw DException("error: serve_cecho");
  }
#endif // _MSC_VER
}

DPtr DTCPContext::serve_cstore(TCP_PDATA & in)
{
  // Serve the P-DATA service
  try {
    //return;
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // analyze C-STORE RQ Message
    //DTCPStream in(*socket, DStream::input);
    //in.continue_read(0);
    CStoreRQMsg rq_msg;

    CStoreRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);
		
    if (*rq_msg.selCommandField() != 0x0001)
      throw DException("DTCPContext: protocol violation");

    const UI& class_uid = rq_msg.selAffectedSOPClassUID();
    const UI& instance_uid = rq_msg.selAffectedSOPInstanceUID();

    int presentation_context_id = as_id_map[class_uid];

    // obtain TS from presentation context
    if (id_ts_map.find(presentation_context_id)==id_ts_map.end())
      throw DException("DTCPContext: no appropriate TS");
    const UI& ts_uid = id_ts_map[presentation_context_id];

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // Archive C-STORE
    DPtr sop_instance;
    if (dicom_app.role == DApplication::archive_application) {
      DFileContext sta_file( dicom_app.sop_filename(instance_uid) );
      // dump Tag buffer
      int position = in.sel_unbuffered_position();
      SOP & sop = dicom_app.sops[class_uid]->gen(instance_uid);
			
      // decode object
      in.begin_read(TCP_PDATA::data_set);
      sop.decode(in, ts_uid);
			
      sta_file.write( sop );
      // dump binary DICOM image
      // stack image information
      sop_instance = sop.ptr();
#ifdef MEDIC_PACS
      dicom_app.image_stacker.stack(sop_instance);
#endif
    }
    else {
      // Viewing Station C-STORE
      SOP & sop = dicom_app.sops[class_uid]->gen();
      //AbstractSOPCommonMod& sopcommon = dynamic_cast<AbstractSOPCommonMod&>(sop);
      // decode object
			
      in.begin_read(TCP_PDATA::data_set);
      sop.decode(in, ts_uid);
			
      // KLUDGE we normally rely on storagemanager::sync
      DFileContext boo_file( dicom_app.sop_filename(instance_uid) );
      // dump Tag buffer
      boo_file.write( sop );
      sop_instance = sop.ptr();
      // dump binary DICOM image
      //END KLUDGE
    }	

    in.end_read();

    // Send C-STORE-RSP message
    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);
    CStoreRSPMsg rsp_msg;
    rsp_msg.modCommandField( 0x8001 ); // C-STORE
    rsp_msg.modAffectedSOPClassUID( rq_msg.selAffectedSOPClassUID() );
    rsp_msg.modAffectedSOPInstanceUID( rq_msg.selAffectedSOPInstanceUID() );
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modDataSetType( 0x0101 ); // Null
    rsp_msg.modStatus( 0 ); // Success
    CStoreRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);

    // fix group length
    //out.write_first_groups_length();
    out.end_write();

    dicom_app.report("server: C-STORE completed");

    return sop_instance;
  }
  catch (DException e) {
    e.why();
    //throw e;
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
  }
#endif
  return DPtr::Null;
}

// C-FIND and C-GET services only available when configured as dcl-archive

#ifdef MEDIC_ARCHIVE

void DTCPContext::serve_cfind(TCP_PDATA & in)
{
  Info_Model info_model;
  QR_Level qr_level;
  // Serve the P-DATA service
  try {

    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // analyze C-FIND-RQ Message
    CFindRQMsg rq_msg;

    CFindRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);
		
    if (*rq_msg.selCommandField() != 0x0020)
      throw DException("DTCPContext: protocol violation");

    const UI& class_uid = rq_msg.selAffectedSOPClassUID();

    int presentation_context_id = as_id_map[class_uid];

    // obtain TS from presentation context
    if (id_ts_map.find(presentation_context_id)==id_ts_map.end())
      throw DException("DTCPContext: no appropriate TS");
    const UI& ts_uid = id_ts_map[presentation_context_id];

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // decode Identifier

    SOP & query_identifier = dicom_app.sops[class_uid]->gen();

    in.begin_read(TCP_PDATA::data_set);
    query_identifier.decode(in, ts_uid);

    in.end_read();

    // DB Query
    CFind_Query query_obj;
    // check our information model and query/retrieve level
    if ( typeid(query_identifier).before(typeid(PatientRootQRInfoModelFIND&)) ) {
      info_model = patient_root;
      //PatientRootQRInfoModelFIND identifier = dynamic_cast<PatientRootQRInfoModelFIND&>(query_identifier);
      PatientRootQRInfoModelFIND& identifier = (PatientRootQRInfoModelFIND&)(query_identifier);
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
      query_obj.SetInfoModel(identifier);
      query_obj.fetch();
    }
    else /*if typeid(query_identifier).before(typeid(StudyRootQRInfoModelFIND&)) {
	   info_model = patient_root;
	   }*/
      throw DException("Information Model Unavailable");

    dicom_app.report("Query Complete");

    /*
      Have a look at CFind, CGet and Hierarchical queries


      CGet_Query is used just the same way
      i.e.

      CGet_Query query_obj;
      query_obj.SetInfoModel(dynamic_cast<PatientRootQRInfoModelGET&>(sop));
      found_uids=query_obj.fetch();
      -umut
    */			

    // tha's img4.dcm
    //found_uids.push_back(UI("1.2.392.200036.9116.2.7.1625654375.19970915.184113003"));

    // let's begin processing the query
    list<Patient_Info>::iterator pa0 = query_obj.patient_info_list.begin(),
      pa1 = query_obj.patient_info_list.end();
    list<Study_Info>::iterator st0 = query_obj.study_info_list.begin(),
      st1 = query_obj.study_info_list.end();
    list<Series_Info>::iterator se0 = query_obj.series_info_list.begin(),
      se1 = query_obj.series_info_list.end();
    list<Image_Info>::iterator im0 = query_obj.image_info_list.begin(),
      im1 = query_obj.image_info_list.end();

    bool data_processed = false;
    while (!data_processed) {
      TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
      out.begin_write(TCP_PDATA::command_set);
      CFindRSPMsg rsp_msg;
      rsp_msg.modCommandField( 0x8020 ); // C-FIND
      rsp_msg.modAffectedSOPClassUID( rq_msg.selAffectedSOPClassUID() );
      rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
      rsp_msg.modDataSetType( 0xffff ); // Not Null
      rsp_msg.modStatus( 0xff00 ); // Pending
      CFindRSPMsg::Coder<CMD_TS> rsp_coder;
      rsp_coder.encode(out, rsp_msg);
      out.begin_write(TCP_PDATA::data_set);
      SOP& matched_identifier = query_identifier.gen(false);
      if (info_model==patient_root) {
	PatientRootQRInfoModelFIND& query =(PatientRootQRInfoModelFIND&)query_identifier;
	PatientRootQRInfoModelFIND& matched =(PatientRootQRInfoModelFIND&)matched_identifier;
	switch (qr_level) {
	case patient:
	  // select from Patient Set
	  matched.modPatientID(pa0->patient_id);
	  //if (query.avlPatientsName())
	  matched.modPatientsName( PN(pa0->patient_name+"^"+pa0->patient_surname) );
	  data_processed = (++pa0 == pa1);
	  break;
	case study:
	  // select from Study Set
	  dicom_app.report("found study_instance_uid: " + st0->study_instance_uid);
	  matched.modStudyInstanceUID(UIv());
	  matched.refStudyInstanceUID().push_back( st0->study_instance_uid );
	  //if (query.avlStudyDate())
	  matched.modStudyDate( rangeDA(rangeDA::single, DA(/*st0->study_date*/) ) ); //CODE: study time
	  //if (query.avlStudyTime())
	  matched.modStudyTime( rangeTM() ); //CODE: study date has problems
	  //if (query.avlAccessionNumber())
	  matched.modAccessionNumber( st0->accession_number );
	  //if (query.avlStudyID())
	  matched.modStudyID( st0->accession_number );
	  data_processed = (++st0 == st1);
	  break;
	case series:
	  // select from Series Set
	  dicom_app.report("found series_instance_uid: " + se0->series_instance_uid);
	  matched.modSeriesInstanceUID(UIv());
	  matched.refSeriesInstanceUID().push_back( se0->series_instance_uid );
	  //if (query.avlModality())
	  matched.modModality( se0->modality );
	  //if (query.avlSeriesNumber())
	  matched.modSeriesNumber( se0->series_number );
	  data_processed = (++se0 == se1);
	  break;
	case image:
	  // select from Image Set
	  matched.modSOPInstanceUID(UIv());
	  matched.refSOPInstanceUID().push_back( im0->sop_instance_uid );
	  //if (query.avlImageNumber())
	  matched.modImageNumber( im0->image_number );
	  data_processed = (++im0 == im1);
	  break;
	}
      }
      matched_identifier.encode(out, ts_uid);
      out.end_write();
    }

    // Send C-FIND-RSP indicating successful completion
    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    CFindRSPMsg rsp_msg;
    rsp_msg.modCommandField( 0x8020 ); // C-FIND
    rsp_msg.modAffectedSOPClassUID( rq_msg.selAffectedSOPClassUID() );
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modDataSetType( 0x0101 ); // Null
    rsp_msg.modStatus( 0 ); // Success
    CFindRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);
    out.end_write();

    // that's it, we're outta here

    dicom_app.report("server: C-FIND completed");
  }
  catch (DException e) {
    e.why();
  }
  catch (CException e) {
    e.ReportError();
  }	
}

void DTCPContext::serve_cget(TCP_PDATA & in)
{
  Info_Model info_model;
  QR_Level qr_level;
  // Serve the P-DATA service
  try {

    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    // analyze C-GET-RQ Message
    CGetRQMsg rq_msg;

    CGetRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);
		
    if (*rq_msg.selCommandField() != 0x0010)
      throw DException("DTCPContext: protocol violation");

    const UI& class_uid = rq_msg.selAffectedSOPClassUID();

    int presentation_context_id = as_id_map[class_uid];

    // obtain TS from presentation context
    if (id_ts_map.find(presentation_context_id)==id_ts_map.end())
      throw DException("DTCPContext: no appropriate TS");
    const UI& ts_uid = id_ts_map[presentation_context_id];

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // decode Identifier

    SOP & query_identifier = dicom_app.sops[class_uid]->gen();

    in.begin_read(TCP_PDATA::data_set);
    query_identifier.decode(in, ts_uid);

    in.end_read();

    // begin DB query
    CGet_Query query_obj;
    // check our information model and query/retrieve level
    if ( typeid(query_identifier).before(typeid(PatientRootQRInfoModelGET&)) ) {
      info_model = patient_root;
      //PatientRootQRInfoModelGET identifier = dynamic_cast<PatientRootQRInfoModelGET&>(query_identifier);
      //PatientRootQRInfoModelGET* identifier = dynamic_cast<PatientRootQRInfoModelGET*>(&query_identifier);
      PatientRootQRInfoModelGET& identifier = (PatientRootQRInfoModelGET&)(query_identifier);
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
      // DB Query
      query_obj.SetInfoModel(identifier);
      query_obj.fetch();
    }
    else /*if typeid(query_identifier).before(typeid(StudyRootQRInfoModelGET&)) {
	   info_model = patient_root;
	   }*/
      throw DException("Information Model Unavailable");
		
	
    // tha's img4.dcm
    //found_uids.push_back(UI("1.2.392.200036.9116.2.7.1625654375.19970915.184113003"));

    // perform C-STORE sub-operations, send no pending messages, not required anyways
    int number_of_remaining_suboperations = query_obj.image_info_list.size();
    int number_of_successful_suboperations = 0;
    int number_of_failed_suboperations = 0;
    int number_of_warning_suboperations = 0;
    // we retrieve at the image level, true for Patient Root and Study Root
    list<Image_Info>::iterator im0 = query_obj.image_info_list.begin(),
      im1 = query_obj.image_info_list.end();
    for (;im0!=im1; im0++) {
      // that's for sending a pending response, we won't get into that
      /*
	TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
	out.begin_write(TCP_PDATA::command_set);
	CGetRSPMsg rsp_msg;
	rsp_msg.modCommandField( 0x8010 ); // C-GET
	rsp_msg.modAffectedSOPClassUID( rq_msg.selAffectedSOPClassUID() );
	rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
	rsp_msg.modDataSetType( 0xffff ); // Not Null
	rsp_msg.modStatus( 0xff00 ); // Pending
	CGetRSPMsg::Coder<CMD_TS> rsp_coder;
	rsp_coder.encode(out, rsp_msg);
	out.begin_write(TCP_PDATA::data_set);
      */
      SOP& matched_identifier = query_identifier.gen(false);
      if (info_model==patient_root) {
	PatientRootQRInfoModelGET& query =(PatientRootQRInfoModelGET&)query_identifier;
	PatientRootQRInfoModelGET& matched =(PatientRootQRInfoModelGET&)matched_identifier;
	// simply C-STORE images then

	//CODE: send the DICOM stream read from disk directly if possible
	DFileContext dicom_file(dicom_app.sop_filename(im0->sop_instance_uid));
	SOP& image = dicom_file.read();
	cstore(image);
      }
      /*
	matched_identifier.encode(out, ts_uid);
	out.end_write();
      */
    }

    // Send C-GET-RSP indicating successful completion
    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    CGetRSPMsg rsp_msg;
    rsp_msg.modCommandField( 0x8010 ); // C-GET
    rsp_msg.modAffectedSOPClassUID( rq_msg.selAffectedSOPClassUID() );
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modDataSetType( 0x0101 ); // Null
    rsp_msg.modStatus( 0 ); // Success
    CGetRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);
    out.end_write();

    // that's it, we're outta here

    dicom_app.report("server: C-GET completed");
  }
  catch (DException e) {
    e.why();
  }
  catch (CException e) {
    e.ReportError();
  }	
}

#endif // MEDIC_ARCHIVE

void DTCPContext::serve_ncreate(TCP_PDATA & in)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    //DTCPStream in(*socket, DStream::input);
    //in.continue_read(0);
    NCreateRQMsg rq_msg;

    NCreateRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);

    const UI& class_uid = rq_msg.selAffectedSOPClassUID();
    const UI& instance_uid = dicom_app.storage_manager.gen_instance_uid();

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // obtain TS from presentation context
    const UI& ts_uid = ImplicitVRLittleEndian::UID;
    SOP & sop = dicom_app.sops[class_uid]->gen(instance_uid);
    sop.decode(in, ts_uid);
    in.end_read();

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);
    NCreateRSPMsg rsp_msg;
    rsp_msg.modAffectedSOPInstanceUID( class_uid );
    rsp_msg.modAffectedSOPInstanceUID( instance_uid );
    rsp_msg.modCommandField( 0x8140 );
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modDataSetType(0x1010);
    rsp_msg.modStatus(0);
    NCreateRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);

    // fix group length
    //out.write_first_groups_length();
    out.end_write();

    dicom_app.report("server: N-CREATE complete");
  }
  catch (DException e) {
    e.why();
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
  }
#endif _MSC_VER
}

void DTCPContext::serve_nset(TCP_PDATA & in)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    //DTCPStream in(*socket, DStream::input);
    //in.continue_read(0);
    NSetRQMsg rq_msg;

    NSetRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);

    const UI& class_uid = rq_msg.selRequestedSOPClassUID();
    const UI& instance_uid = rq_msg.selRequestedSOPInstanceUID();

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // obtain TS from presentation context
    const UI& ts_uid = ImplicitVRLittleEndian::UID;
    SOP & sop = dicom_app.sops[class_uid]->gen();
    sop.decode(in, ts_uid);

    DPtr ptr(class_uid, instance_uid);
    SOP & requested_sop = *ptr;
    requested_sop.set(sop);

    in.end_read();

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);
    NSetRSPMsg rsp_msg;
    rsp_msg.modCommandField( 0x8120 ); // C-ECHO
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modDataSetType(0x1010);
    rsp_msg.modStatus(0);
    NSetRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);

    // fix group length
    //out.write_first_groups_length();
    out.end_write();

    dicom_app.report("server: N-SET complete");
  }
  catch (DException e) {
    e.why();
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
  }
#endif // _ MSC_VER
}

void DTCPContext::serve_naction(TCP_PDATA & in)
{
  try {
    if (state != association_established)
      throw DException("DTCPContext: protocol violation");
		
    //DTCPStream in(*socket, DStream::input);
    //in.continue_read(0);
    NActionRQMsg rq_msg;

    NActionRQMsg::Coder<CMD_TS> rq_coder;
    rq_coder.decode(in, rq_msg);

    const UI& class_uid = rq_msg.selRequestedSOPClassUID();
    const UI& instance_uid = rq_msg.selRequestedSOPInstanceUID();

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // obtain TS from presentation context
    const UI& ts_uid = ImplicitVRLittleEndian::UID;
    in.end_read();

    if (print_server.own_service(class_uid))
      print_server.serve_naction( DPtr(class_uid, instance_uid), *rq_msg.selActionTypeID());

    TCP_PDATA out(*socket, DStream::output, as_id_map[class_uid]);
    out.begin_write(TCP_PDATA::command_set);
    //DTCPStream out(*socket, DStream::output);
    //out.begin_write(p_data_tf_type);
    NActionRSPMsg rsp_msg;
    rsp_msg.modCommandField( 0x8130 ); // N-ACTION
    rsp_msg.modMessageIDBeingRespondedTo( rq_msg.selMessageID() );
    rsp_msg.modDataSetType(0x1010);
    rsp_msg.modStatus(0);
    NActionRSPMsg::Coder<CMD_TS> rsp_coder;
    rsp_coder.encode(out, rsp_msg);

    // fix group length
    //out.write_first_groups_length();
    out.end_write();

    dicom_app.report("server: N-ACTION complete");
  }
  catch (DException e) {
    e.why();
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
  } 
#endif
}

void DTCPContext::dgn(const string & s)
{
  dicom_app.report("DTCPContext:" + s);
}
