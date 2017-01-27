echo Generating bison LALR grammar
bison --defines dicom.grm --output-file=dicomtab.c
echo Generating flex lexical analyzer
flex -odicomfl.cxx dicom.fl
echo Renaming
del dicomtab.cxx
ren DICOMTAB.C dicomtab.cxx

