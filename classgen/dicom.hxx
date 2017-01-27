/*
**
** Interface of lexical and syntax analyzers
**
*/

#ifndef dicom_h
#define dicom_h

#include "General.hxx"

extern int yylex();
extern FILE *yyin;
extern char* yytext;

extern Parser parser;
extern int yyparse();
extern int yydebug;

#endif
