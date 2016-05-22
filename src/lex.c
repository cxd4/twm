/*
 * lexcal analyzer for Internationalized window manager       
 *
 * X11R5 Internationalized Window Manger                     
 * lex.c ver.1.0  Tue Sep 17 10:36:18 JST 1991              
 */
                                                          
/* Copyright 1991 by OMRON Corporation                      
 *
 *      Author: Takashi Inoue    OMRON Corporation
 *                               takashi@ari.ncl.omron.co.jp
 */

#include <stdio.h>
#include <X11/wchar.h>
#include "gram.h"
#include "parse.h"

#define KEY_MAX 200
#define DEC 10

#undef feof()
#define unput(c)        twmUnput(c)
#define input()         (*twmInputFunc)()
#define output(c)       TwmOutput(c)
#define feof()          (1)

static int ptr = 0;
static wchar_t yytext[KEY_MAX];

int yylineno = 1;

extern char *ProgramName;
extern int ParseError;

extern wchar_t getnext();
extern unsigned char *convert_wctoct();

int yylex()
{
    wchar_t retchar;
    int token;
    unsigned char *keyword;

    ptr = 0;
    while ((retchar = input()) != 0) {
	if (retchar == _atowc('\n') || retchar == _atowc('\t') ||
	    retchar == _atowc(' ')) { /* [\n\t ] */
	    ;
	} else if (_iswalpha(retchar) || retchar == _atowc('.') ||
	    retchar == _atowc('\\')) { /* [a-zA-Z\.]+ */
	    do {
		retchar = getnext(retchar);
	    } while (_iswalpha(retchar) || retchar == _atowc('.') ||
		     retchar == _atowc('\\'));
	    backch(retchar);
	    keyword = convert_wctoct(yytext);
	    token = parse_keyword(keyword, &yylval.num);
	    if (token == ERRORTOKEN) {
		twmrc_error_prefix();
		fprintf(stderr,
			"ignoring unknown keyword:  %s\n",
			yytext);
		ParseError = 1;
	    } else {
		return (token);
	    }
	} else if (_iswdigit(retchar)) { /* {number} -> [0-9]+ */
	    do {
		retchar = getnext(retchar);
	    } while (_iswdigit(retchar));
	    backch(retchar);
	    keyword = convert_wctoct(yytext);
	    (void)sscanf(keyword, "%d", &yylval.num);
	    return(NUMBER);
	} else if (retchar == _atowc('#')) { /* \#[^\n]*\n */
	    do {
		retchar = getnext(retchar);
	    } while (retchar != _atowc('\n'));
	    ptr = 0;
	    ;
	} else if (retchar == _atowc('"')) {
				/* {string} -> \"(^"]|\\.)*\" */
	    do {
		retchar = getnext(retchar);
	    } while (retchar != _atowc('"'));
	    yytext[ptr++] = retchar;
	    yytext[ptr] = _atowc('\0');
	    yylval.wc_ptr = yytext;
	    return (WC_STRING);
	} else if (retchar == _atowc('{')) { /* "{" */
	    return (LB);
	} else if (retchar == _atowc('}')) { /* "}" */
	    return (RB);
	} else if (retchar == _atowc('(')) { /* "(" */
	    return (LP);
	} else if (retchar == _atowc(')')) { /* ")" */
	    return (RP);
	} else if (retchar == _atowc('=')) { /* "=" */
	    return (EQUALS);
	} else if (retchar == _atowc(':')) { /* ":" */
	    return (COLON);
	} else if (retchar == _atowc('+')) { /* "+" */
	    return (PLUS);
	} else if (retchar == _atowc('-')) { /* "-" */
	    return (MINUS);
	} else if (retchar == _atowc('|')) { /* "|" */
	    return (OR);
	} else if (retchar == _atowc('!')) { /* "!" */
	    yylval.num = F_EXEC;
	    return (FSKEYWORD);
	} else if (retchar == _atowc('^')) { /* "^" */
	    yylval.num = F_CUT;
	    return (FSKEYWORD);
	}
    }
}

wchar_t getnext(retchar)
wchar_t retchar;
{
    yytext[ptr++] = retchar;
    return (input());
}

void backch(retchar)
wchar_t retchar;
{
    yytext[ptr] = _atowc('\0');
    if (retchar != _atowc('\n') && retchar != _atowc('\t') && 
	retchar != _atowc(' ')) 
	unput(retchar);
}

