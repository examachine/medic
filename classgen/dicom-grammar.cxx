
/*  A Bison parser, made from \Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	NL	257
#define	LP	258
#define	RP	259
#define	COM	260
#define	DASH	261
#define	SLASH	262
#define	OR	263
#define	BS	264
#define	EOFT	265
#define	UIDS	266
#define	TAGS	267
#define	MODULES	268
#define	IODS	269
#define	MODULE	270
#define	ENUM	271
#define	ENDENUM	272
#define	IODT	273
#define	MUTEX	274
#define	NONE	275
#define	MESSAGES	276
#define	MESSAGE	277
#define	L_INT	278
#define	ID	279

#line 10 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"

#define YYDEBUG 1
#include "General.hxx"
#include "Parser.hxx"
#include "dicom.hxx"

int yyerror(char *s);

Parser parser("dcg v2.1");


#line 25 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
typedef union {
	int		integer;
	string		*id;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		123
#define	YYFLAG		-32768
#define	YYNTBASE	26

#define YYTRANSLATE(x) ((unsigned)(x) <= 279 ? yytranslate[x] : 78)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     8,    10,    11,    16,    24,    25,
    26,    31,    32,    33,    42,    43,    49,    51,    54,    56,
    60,    63,    65,    66,    67,    68,    76,    78,    80,    84,
    88,    90,    92,    96,   100,   105,   107,   108,   109,   115,
   118,   120,   121,   122,   123,   131,   132,   136,   137,   138,
   139,   147,   150,   151,   153,   154,   159,   160,   161,   166,
   169,   171,   172,   173,   180,   183,   184,   188,   191,   192,
   193,   194,   201,   204,   206,   207,   208,   209
};

static const short yyrhs[] = {    27,
     0,    30,     0,    45,     0,    61,     0,    69,     0,     0,
    12,     3,    28,    29,     0,    29,    25,     3,    25,     3,
    25,     3,     0,     0,     0,    13,     3,    31,    32,     0,
     0,     0,    32,    35,     3,    33,    25,     3,    34,    38,
     0,     0,     4,    36,     6,    37,     5,     0,    24,     0,
    24,    25,     0,    24,     0,    24,     7,    24,     0,    38,
    39,     0,    39,     0,     0,     0,     0,    40,    41,    43,
     3,    42,    44,     3,     0,    21,     0,    25,     0,    25,
     8,    25,     0,    25,    10,    25,     0,    25,     0,    24,
     0,    24,     7,    24,     0,    24,     7,    25,     0,    24,
     7,    24,    25,     0,    21,     0,     0,     0,    14,     3,
    46,    47,    48,     0,    48,    49,     0,    49,     0,     0,
     0,     0,    16,    50,    25,     3,    51,    52,    53,     0,
     0,    53,    54,    55,     0,     0,     0,     0,    58,    35,
    56,    59,     3,    57,    60,     0,    58,     8,     0,     0,
    25,     0,     0,    17,     3,    18,     3,     0,     0,     0,
    15,     3,    62,    63,     0,    63,    64,     0,    64,     0,
     0,     0,    65,    19,    25,     3,    66,    67,     0,    67,
    68,     0,     0,    25,    25,     3,     0,    20,     3,     0,
     0,     0,     0,    22,     3,    70,    71,    72,    73,     0,
    73,    74,     0,    74,     0,     0,     0,     0,    23,    75,
    25,     3,    76,    77,    53,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    56,    58,    59,    60,    61,    64,    68,    72,    75,    78,
    82,    85,    89,    92,    92,    95,    99,   101,   105,   107,
   112,   114,   117,   119,   120,   122,   126,   128,   130,   134,
   141,   143,   144,   145,   146,   147,   150,   154,   157,   160,
   163,   166,   167,   168,   171,   173,   177,   178,   181,   184,
   187,   189,   191,   194,   196,   199,   203,   206,   211,   213,
   216,   219,   221,   224,   226,   228,   231,   235,   240,   243,
   245,   248,   251,   254,   257,   258,   259,   261
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","NL","LP",
"RP","COM","DASH","SLASH","OR","BS","EOFT","UIDS","TAGS","MODULES","IODS","MODULE",
"ENUM","ENDENUM","IODT","MUTEX","NONE","MESSAGES","MESSAGE","L_INT","ID","dicom",
"uids","@1","uid_list","tags","@2","tag_list","@3","@4","tag","tag_group","tag_element",
"vrvmlist","vrvmitem","@5","@6","@7","vr","vm","modules","@8","@9","module_list",
"module","@10","@11","@12","attribute_list","@13","attribute","@14","@15","nesting",
"attr_type","optional_enum","iods","@16","iod_list","iod","@17","@18","iod_components",
"iod_component","messages","@19","@20","@21","message_list","message","@22",
"@23","@24", NULL
};
#endif

static const short yyr1[] = {     0,
    26,    26,    26,    26,    26,    28,    27,    29,    29,    31,
    30,    33,    34,    32,    32,    35,    36,    36,    37,    37,
    38,    38,    40,    41,    42,    39,    43,    43,    43,    43,
    44,    44,    44,    44,    44,    44,    46,    47,    45,    48,
    48,    50,    51,    52,    49,    54,    53,    53,    56,    57,
    55,    58,    58,    59,    59,    60,    60,    62,    61,    63,
    63,    65,    66,    64,    67,    67,    68,    68,    70,    71,
    72,    69,    73,    73,    75,    76,    77,    74
};

static const short yyr2[] = {     0,
     1,     1,     1,     1,     1,     0,     4,     7,     0,     0,
     4,     0,     0,     8,     0,     5,     1,     2,     1,     3,
     2,     1,     0,     0,     0,     7,     1,     1,     3,     3,
     1,     1,     3,     3,     4,     1,     0,     0,     5,     2,
     1,     0,     0,     0,     7,     0,     3,     0,     0,     0,
     7,     2,     0,     1,     0,     4,     0,     0,     4,     2,
     1,     0,     0,     6,     2,     0,     3,     2,     0,     0,
     0,     6,     2,     1,     0,     0,     0,     7
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
     6,    10,    37,    58,    69,     9,    15,    38,    62,    70,
     7,    11,     0,    59,    61,     0,    71,     0,     0,     0,
    42,    39,    41,    60,     0,     0,     0,    17,     0,    12,
     0,    40,     0,    75,    72,    74,     0,    18,     0,     0,
     0,    63,     0,    73,     0,    19,     0,     0,    43,    66,
     0,     0,     0,    16,    13,    44,    64,    76,     8,    20,
    23,    48,     0,     0,    65,    77,    14,    22,    24,    45,
    68,     0,    48,    21,     0,    53,    67,    46,    27,    28,
     0,    47,     0,     0,     0,    25,    52,    49,    29,    30,
     0,    55,    36,    32,    31,     0,    54,     0,     0,    26,
    50,    33,    34,    57,    35,     0,    51,     0,     0,    56,
     0,     0,     0
};

static const short yydefgoto[] = {   121,
     6,    16,    21,     7,    17,    22,    50,    71,    30,    39,
    57,    77,    78,    79,    85,   101,    91,   106,     8,    18,
    23,    32,    33,    41,    66,    72,    80,    86,    92,   102,
   114,    93,   108,   117,     9,    19,    24,    25,    26,    60,
    67,    75,    10,    20,    27,    36,    45,    46,    53,    76,
    83
};

static const short yypact[] = {   -11,
     4,    19,    21,    24,    25,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     5,    27,    16,    10,-32768,    14,-32768,    31,    12,    32,
-32768,    16,-32768,-32768,    15,    18,    17,    20,    33,-32768,
    22,-32768,    34,-32768,    18,-32768,    35,-32768,    26,    23,
    40,-32768,    28,-32768,    29,    37,    41,    46,-32768,-32768,
    48,    49,    36,-32768,-32768,-32768,   -15,-32768,-32768,-32768,
-32768,-32768,    52,    38,-32768,-32768,    -7,-32768,-32768,    11,
-32768,    53,-32768,-32768,    -5,-32768,-32768,     0,-32768,    -2,
    54,-32768,    13,    39,    42,-32768,-32768,-32768,-32768,-32768,
   -12,    43,-32768,    51,-32768,    56,-32768,    58,     1,-32768,
-32768,    44,-32768,    45,-32768,    62,-32768,    55,    63,-32768,
    70,    71,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -21,-32768,
-32768,-32768,    -3,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    47,-32768,-32768,-32768,    -8,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    57,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    50,-32768,-32768,
-32768
};


#define	YYLAST		95


static const short yytable[] = {   -78,
     1,     2,     3,     4,    73,    94,    11,    95,   103,    74,
     5,   104,   105,   -23,   -46,    89,    29,   -23,   -46,    90,
    97,    12,   -78,    13,   112,   113,    14,    15,   -62,    28,
    29,    31,    35,    37,    40,    38,    52,    55,    49,    43,
    44,    47,    59,    63,    48,    64,    51,    58,    65,    56,
    68,    69,    61,    62,    81,    87,    96,   109,   110,    70,
   111,   116,    82,    99,   118,   120,   100,   107,   115,   122,
   123,    98,   119,    84,    88,     0,     0,     0,    42,     0,
    34,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    54
};

static const short yycheck[] = {     0,
    12,    13,    14,    15,    20,     8,     3,    10,    21,    25,
    22,    24,    25,    21,     4,    21,     4,    25,     8,    25,
     8,     3,    23,     3,    24,    25,     3,     3,    19,    25,
     4,    16,    19,     3,     3,    24,     3,     3,     6,    25,
    23,    25,     3,     7,    25,     5,    25,    25,     3,    24,
     3,     3,    25,    25,     3,     3,     3,     7,     3,    24,
     3,    17,    25,    25,     3,     3,    25,    25,    25,     0,
     0,    93,    18,    77,    83,    -1,    -1,    -1,    32,    -1,
    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    45
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 6:
#line 66 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ cout << "Reading UID's " << endl; ;
    break;}
case 7:
#line 68 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ cout << parser.number_of_uids << " UIDs read" << endl;
	  parser.no_punct=1; ;
    break;}
case 8:
#line 74 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_uid(yyvsp[-5].id, yyvsp[-3].id, yyvsp[-1].id); ;
    break;}
case 10:
#line 80 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{  cout << "Reading tag dictionary" << endl; ;
    break;}
case 11:
#line 82 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ cout << parser.number_of_tags << " tags read" << endl; ;
    break;}
case 12:
#line 88 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.no_punct=0; parser.strip_punct=1; ;
    break;}
case 13:
#line 90 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tid(*yyvsp[-1].id); delete yyvsp[-1].id; ;
    break;}
case 15:
#line 92 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ ;
    break;}
case 16:
#line 97 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ ;
    break;}
case 17:
#line 100 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tg(yyvsp[0].integer, 0); ;
    break;}
case 18:
#line 102 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tg(yyvsp[-1].integer, 1); delete yyvsp[0].id; ;
    break;}
case 19:
#line 106 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_te(yyvsp[0].integer, yyvsp[0].integer); ;
    break;}
case 20:
#line 108 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_te(yyvsp[-2].integer, yyvsp[0].integer); ;
    break;}
case 23:
#line 118 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.no_punct=0; parser.strip_punct=0; ;
    break;}
case 24:
#line 119 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.short_id=1; ;
    break;}
case 25:
#line 121 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.no_punct=1; parser.short_id=0; ;
    break;}
case 26:
#line 123 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tagdef(); ;
    break;}
case 27:
#line 127 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tvr(string("")); ;
    break;}
case 28:
#line 129 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tvr(*yyvsp[0].id); delete yyvsp[0].id; ;
    break;}
case 29:
#line 131 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tvr(*yyvsp[-2].id); delete yyvsp[-2].id;
	  parser.warn("Attribute " + parser.current_td.name +
			" has conditional VR ");;
    break;}
case 30:
#line 136 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tvr(*yyvsp[0].id); delete yyvsp[-2].id; delete yyvsp[0].id; /* I'll do template specialization */
	  parser.warn("Attribute " + parser.current_td.name +
	  " has conditional VR "); ;
    break;}
case 31:
#line 142 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tvm( VM(0,0,2) ); delete yyvsp[0].id; parser.warn("Obsolete VM=n"); ;
    break;}
case 32:
#line 143 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.add_tvm( VM(yyvsp[0].integer,yyvsp[0].integer,0) ); ;
    break;}
case 33:
#line 144 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_tvm( VM(yyvsp[-2].integer,yyvsp[0].integer,1) ); ;
    break;}
case 34:
#line 145 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.add_tvm( VM(0,0,2) ); delete yyvsp[0].id; ;
    break;}
case 35:
#line 146 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.add_tvm( VM(0,0,3) ); delete yyvsp[0].id; ;
    break;}
case 36:
#line 147 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{  parser.add_tvm( VM(0,0,0) ); ;
    break;}
case 37:
#line 152 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{  cout << "Parsing modules" << endl; ;
    break;}
case 38:
#line 154 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.init_gen(); ;
    break;}
case 42:
#line 167 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.expect_id=1;;
    break;}
case 43:
#line 167 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.expect_id=0;;
    break;}
case 44:
#line 168 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.begin_module(yyvsp[-2].id); ;
    break;}
case 46:
#line 175 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.prev_depth = parser.nest_depth; ;
    break;}
case 47:
#line 177 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_attr(); ;
    break;}
case 49:
#line 183 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.expect_id = 1; ;
    break;}
case 50:
#line 185 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.expect_id = 0; ;
    break;}
case 52:
#line 190 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.nest_depth++; ;
    break;}
case 53:
#line 191 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.nest_depth=0; ;
    break;}
case 54:
#line 195 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.set_ctype(*yyvsp[0].id); delete yyvsp[0].id; ;
    break;}
case 55:
#line 196 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.set_ctype("4"); ;
    break;}
case 58:
#line 208 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ cout << "Parsing IOD definitions" << endl; ;
    break;}
case 62:
#line 220 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.no_punct = 0; parser.short_id = 1; ;
    break;}
case 63:
#line 222 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.begin_iod(yyvsp[-1].id); ;
    break;}
case 67:
#line 233 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.add_module(yyvsp[-1].id, yyvsp[-2].id); ;
    break;}
case 68:
#line 237 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.current_mutex++; ;
    break;}
case 69:
#line 242 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.no_punct=1; parser.short_id=0; parser.strip_punct=0; ;
    break;}
case 70:
#line 243 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{  cout << "Parsing message definitions" << endl; ;
    break;}
case 71:
#line 245 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.init_gen(); ;
    break;}
case 75:
#line 258 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.expect_id=1;;
    break;}
case 76:
#line 258 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{parser.expect_id=0;;
    break;}
case 77:
#line 259 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"
{ parser.begin_message(yyvsp[-2].id); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 265 "\Stuff\dev\Acqu\medic\classgen/dicom-grammar.yxx"


int yyerror(char *s)
{
  parser.error(s + string(", was reading token: ") + string(yytext));
  return 1;
}
