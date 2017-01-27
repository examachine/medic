/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef DTCPContext_Interface
#define DTCPContext_Interface 1

#include "General.hxx"
#include "SOP.hxx"
#include "TransferSyntaxes.hxx"
class CustomSocket;
class ClientSocket;
class ServerSocket;
class DTCPStream;
class TCP_PDATA;

#include "Messages.hxx"
#include "PrintManagement.hxx"


/*struct Presentation_Context
{
	int id;
	UI transfer_syntax;
};

typedef map<int, Presentation_Context> Presentation_Context_Map;
*/

typedef map<UI, int> AS_ID_Map;

typedef map<int, UI> ID_TS_Map;

class DTCPContext {
public:

  enum Mode {
    client, server
  };

  enum State {
    idle, awaiting_associate_rq, awaiting_associate_ac, association_established,
    processing_command,
    awaiting_release_rp, awaiting_disconnect
  };

  typedef ExplicitVRBigEndian PDU_TS;    // PDU Transfer Syntax
  typedef ImplicitVRLittleEndian CMD_TS; // Command Transfer Syntax

  enum Association_Type { normal, verification };

  //DTCPContext();

  DTCPContext(Mode);

  // client methods

  void associate(const string & calledAE, Association_Type a_type = normal);

#ifdef _MSC_VER
  void associate(CString& calledAE, Association_Type t) {
    associate( (LPCSTR) calledAE, t);
  }
#endif // _MSC_VER

  void release();

  void cecho();

  list<SOP*> cfind(SOP& query_identifier); // returns a list of identifiers

  list<DPtr> cget(SOP& query_identifier); // returns a list of persistent pointers

  void cget(const list<UI>& instance_uids);

  void cstore(SOP& sop);

  NCreateRSPMsg ncreate(SOP& sop);

  NSetRSPMsg nset(DPtr& ptr, SOP& sop);

  NActionRSPMsg naction(DPtr& ptr, unsigned short action_type);

  // server methods

  void serve(ServerSocket &);

  void serve_associate(DTCPStream &);

  void serve_release(DTCPStream &);

  void serve_cecho(TCP_PDATA &);

  DPtr serve_cstore(TCP_PDATA &);

#ifdef MEDIC_ARCHIVE
  void serve_cfind(TCP_PDATA &);

  void serve_cget(TCP_PDATA &);
#endif

  void serve_ncreate(TCP_PDATA &);

  void serve_nset(TCP_PDATA &);

  void serve_naction(TCP_PDATA &);
	
  void dgn(const string & s);

protected:
	
  enum Info_Model { patient_root, study_root, patient_study_only };
  enum QR_Level { patient, study, series, image };

  CustomSocket* socket;
	
  AE called_ae;
	
  unsigned short gen_message_id () { return message_id++; }
  unsigned short message_id;

  State state;

  AS_ID_Map as_id_map;

  ID_TS_Map id_ts_map;

  User_Information_Item user_information;
	
  PrintServer print_server;
};

#endif
