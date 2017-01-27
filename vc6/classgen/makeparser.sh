echo Generating bison LALR grammar
bison --defines dicom-grammar.hxx --output-file=dicom-grammar.cxx
echo Generating flex lexical analyzer
flex -odicom.cxx dicom.lxx
echo Renaming
#rm dicomtab.cxx
#mv DICOMTAB.C dicomtab.cxx

