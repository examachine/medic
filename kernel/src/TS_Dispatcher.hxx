#ifndef TS_Dispatcher
#define TS_Dispatcher_1


//#pragma message ("SOP_TSs start")

#include "SOP.hxx"

template <class Codable>
//class SOP_TSs : public map<UI, typename Codable::AbstractCoder* > // BUG: cannot! VC bug
class SOP_TSs // : public map<UI, Abstract_Coder*>
{
public:
  //typedef typename Codable::AbstractCoder *Abstract_Coder_Ptr; // VC crashes here!!
  typedef typename Codable::AbstractCoder Abstract_Coder;
  typedef map<UI,Abstract_Coder*> Coder_Map;

//#pragma message ("SOP_TSs constructor")

  list<UI> transfer_syntaxes;
  vector<typename Codable::AbstractCoder *> coders;

  SOP_TSs() {
  }

  void init_class() {
    transfer_syntaxes.push_back(ImplicitVRLittleEndian::UID);
    transfer_syntaxes.push_back(ExplicitVRLittleEndian::UID);
    transfer_syntaxes.push_back(ExplicitVRBigEndian::UID);
    transfer_syntaxes.push_back(JPEGBaseLineP1::UID);
    transfer_syntaxes.push_back(JPEGExtendedP4::UID);
    transfer_syntaxes.push_back(JPEGLosslessNHFOP14::UID);
    coders.push_back(new typename Codable::Coder<ImplicitVRLittleEndian>);
    coders.push_back(new typename Codable::Coder<ExplicitVRLittleEndian>);
    coders.push_back(new typename Codable::Coder<ExplicitVRBigEndian>);
    coders.push_back(new typename Codable::Coder<JPEGBaseLineP1>);
    coders.push_back(new typename Codable::Coder<JPEGExtendedP4>);
    coders.push_back(new typename Codable::Coder<JPEGLosslessNHFOP14>);
    coder_map.insert(Coder_Map::value_type(ImplicitVRLittleEndian::UID, coders[0]));
    coder_map.insert(Coder_Map::value_type(ExplicitVRLittleEndian::UID, coders[1]));
    coder_map.insert(Coder_Map::value_type(ExplicitVRBigEndian::UID, coders[2]));
    coder_map.insert(Coder_Map::value_type(JPEGBaseLineP1::UID, coders[3]));
    coder_map.insert(Coder_Map::value_type(JPEGExtendedP4::UID, coders[4]));
    coder_map.insert(Coder_Map::value_type(JPEGLosslessNHFOP14::UID, coders[5]));
    /*
      pair<iterator, bool> insertion;
      insertion = insert(value_type(ImplicitVRLittleEndian::UID, coders[0]));
    */
  }

  bool check_class(UI id) {
    return ( coder_map.find(id) != coder_map.end() );
  }

  const list<UI> & list_ts() {
    return transfer_syntaxes;
  }
  
  void decode(DStream & d, SOP & _a, UI ts_uid) throw( DException ) {
    if (check_class(ts_uid)) {
      Codable & a = dynamic_cast< Codable & >(_a);
      coder_map[ts_uid]->decode(d, a);
    }
    else
      unknown_ts();
  }

  void encode(DStream & d, SOP & _a, UI ts_uid) throw( DException ) {
    if (check_class(ts_uid)) {
      Codable & a = dynamic_cast< Codable & >(_a);
      coder_map[ts_uid]->encode(d, a);
    }
    else
      unknown_ts();
  }

  static void unknown_ts() throw( DException ) {
    throw DException("Transfer Syntax not recognized");
  }

  Abstract_Coder* operator[](const UI &ui) {
    return coder_map[ui];
  }

private:
  Coder_Map coder_map;
};

//#pragma message("SOP_TSs end class")
/*
class TransferSyntaxDispatcher
{
  TransferSyntaxDispatcher() {

  }
};

class TransferSyntaxes : public map< UI, TransferSyntaxDispatcher >
{
public:
  void init_class();
  bool check_class(UI id) {
	return ( find(id) != end() );
  }
  
  void template <class Codable> decode(DStream& d, SOP & _a, UI ts_uid) {
	if (check_class(ts_uid)) {
	  Codable & a = dynamic_cast< Codable & >(_a);
	  // we have the SOP class, now access its coder class and have an instance of it
	  //Coder<
	}
	else
	  unknown_ts();
  }

  static void unknown_ts() throw( DException ) {
	throw DException("Transfer Syntax not recognized");
  }
};

*/

//		void operator() (DStream & d, SOP & _a, UI ts_uid) throw( DException ) {
//			Codable & a = dynamic_cast< Codable & >(_a);

#endif
