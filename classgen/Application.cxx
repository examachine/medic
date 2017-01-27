/*
** C++ source for Application
**
** eXa/bRoNx
**
*/

#include "General.hxx"
#include "Parser.hxx"
#include "dicom.hxx"

int main(int argc, char *argv[])
{
  string uid_dict_filename;
  string tag_dict_filename;
  string mod_dict_filename;
  string ciod_dict_filename;
  string niod_dict_filename;
  string msg_dict_filename;
  string tag_dict_filename_2;
  string mod_dict_filename_2;

  if (argc != 10) {
    cerr << "Wrong number of arguments" << endl;
    cerr << argc-1 << "given" << endl;
    exit(0);
  }
  else {
    // better argument parsing next time :)
    uid_dict_filename = argv[1];
    tag_dict_filename = argv[2];
    mod_dict_filename = argv[3];
    ciod_dict_filename = argv[4];
    niod_dict_filename = argv[5];
    msg_dict_filename = argv[6];
    tag_dict_filename_2 = argv[7];
    mod_dict_filename_2 = argv[8];
  }

  if ( string(argv[9]) == string("vc5") ) {
    parser.platform = Parser::vc5;
  }
  else if ( string(argv[9]) == string("gxx")  ) {
    parser.platform = Parser::gxx;
  }
  else
    // error
    cerr << "Platform not recognized, " << 
      "gxx and vc5 are valid at the time being\n";
  yydebug = 0;

  // do parsing for real
  cout << "Class generator invoked for ";
  if (parser.platform == Parser::gxx) cout << "g++";
  if (parser.platform == Parser::vc5) cout << "Visual C++ 5.0"; 
  cout << endl << endl;

  // Parse definitions

  parser.parse(uid_dict_filename);
  parser.parse(tag_dict_filename);
  parser.parse(mod_dict_filename);
  parser.parse(ciod_dict_filename);
  parser.parse(niod_dict_filename);
  parser.parse(msg_dict_filename);
  parser.parsing_secondary = true;
  parser.parse(tag_dict_filename_2);
  parser.parse(mod_dict_filename_2);

  // Generate code
  parser.generate();

  cout << endl << "Code generation complete.\n" <<
    parser.total_number_of_lines << " lines processed." << endl;
  cout << parser.warnings << " warnings, " << parser.errors << " errors encountered." << endl;

  return 0;
}
