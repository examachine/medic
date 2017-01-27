typedef union {
	int		integer;
	string		*id;
} YYSTYPE;
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


extern YYSTYPE yylval;
