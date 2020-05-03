#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "MathLexer.h"

//#define MY_DEBUG 1

#ifdef MY_DEBUG
#include <stdio.h>
#endif
#pragma package(smart_init)
/* Uppercase translation table for the Win1251 charset */
const char Win1251UpcaseTbl[] =
    "\000\001\002\003\004\005\006\007\010\011\012\013\014\015\016\017"
    "\020\021\022\023\024\025\026\027\030\031\032\033\034\035\036\037"
    " !\042#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~\177"
    "\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217"
    "\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237"
    "\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257"
    "\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277"
    "\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317"
    "\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337"
    "\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317"
    "\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337";

// initializations

void InitCharTypeTable( hqCharType *CharTypeTable, int CharTypes )
{
    int ch;
#ifdef MY_DEBUG
    printf( "CharTypeTable = 0x%X; CharTypes = %d\n", (unsigned)CharTypeTable,
	    CharTypes );
#endif
    memset( CharTypeTable, CH_UNKNOWN, 256 * sizeof(hqCharType) );

    CharTypeTable[0] = CH_FINAL;

    if (CharTypes & CH_SEPARAT) {
	CharTypeTable[' '] = CH_SEPARAT;
	CharTypeTable[9]  = CH_SEPARAT;
	CharTypeTable[13]  = CH_SEPARAT;
	CharTypeTable[10]  = CH_SEPARAT;
    }

    if (CharTypes & CH_QUOTE) {
	CharTypeTable['"']  = CH_QUOTE;
    }

    if (CharTypes & CH_LETTER) {
	for (ch='A'; ch<='Z'; ch++)
	    CharTypeTable[ch] = CH_LETTER;
	for (ch='a'; ch<='z'; ch++)
	    CharTypeTable[ch] = CH_LETTER;
	CharTypeTable['_'] = CH_LETTER;
    }

    if (CharTypes & CH_DIGIT) {
	for (ch='0'; ch<='9'; ch++)
	    CharTypeTable[ch] = CH_DIGIT;
    }
}

// TMathLexer implementation

#define CHARTYPEPP CharTypeTable[ (uchar) *++(SS) ]
#define CHARTYPE CharTypeTable[ (uchar) *SS ]

int TMathLexer::SetParseString(const char *str )
{
    PrevTokenType = MTOK_NONE;
    if ( !str || !*str )
	return 0;

	if(str_)
		free(str_);
	str_ = (char *)malloc(strlen(str)+1);
    strcpy(str_, str);
	SS = str_;
    CharType = CHARTYPE;
    return 1;
}

hqTokenType TMathLexer::GetNextToken()
{
    hqTokenType result = MTOK_ERROR;

next_token:

    while ( CharType == CH_SEPARAT )
	CharType = CHARTYPEPP;
	
    switch ( CharType ) {
	case CH_FINAL:
	    result = MTOK_FINAL;
	    break;
	case CH_LETTER:
	    Name = SS;
	    do {
		CharType = CHARTYPEPP;
	    } while (CharType <= CH_DIGIT);
	    NameLen = SS - Name;
	    result = MTOK_NAME;
	    break;
	case CH_DIGIT: {
	    char *NewSS;
	    if ( *SS == '0' && *(SS+1) == 'x' ) {
	    	IntValue = strtol( SS, &NewSS, 16 );
                if ( SS != NewSS ) {
		    SS = NewSS;
		    if (NoIntegers) {
			ExtValue = IntValue;
			result = MTOK_FLOAT;
		    } else
			result = MTOK_INT;
		    CharType = CHARTYPE;
                }
                break;
	    }
	    ExtValue = strtod( SS, &NewSS );
	    if ( SS != NewSS ) {;
		SS = NewSS;
		if ( !NoIntegers
		    && ExtValue<=INT_MAX
		    && ExtValue>=INT_MAX
		    && (double)( IntValue = (uchar) ExtValue )
			== ExtValue ) {
		    result = MTOK_INT;
		} else
		    result = MTOK_FLOAT;
		CharType = CHARTYPE;
	    }
	    break;
	}
	case CH_SYMBOL: {
	    int nchars;
	    int i = SymTable->FindSymbol( SS, &nchars );
	    if (i >= 0) {
		SS += nchars;
		if (i == cssn) {
		    char comend = *ComEnd;
		    char comendpp = *(ComEnd+1);
		    while ( *SS ) {
			if ( *SS == comend
			     &&
			     ( comendpp == '\0' || *(SS+1) == comendpp )
			   ) {
			    ++SS;
			    if (comendpp != '\0')
				++SS;
			    CharType = CHARTYPE;
			    goto next_token;
			}
			++SS;
		    }
		    break;
		}
		CharType = CHARTYPE;
		IntValue = i;
		result = MTOK_SYMBOL;
	    }
	    break;
	}
	case CH_QUOTE:
	    Name = ++(SS);
	    while ( CharTypeTable[ (uchar)*SS ] != CH_QUOTE
		    && *(SS) != '\0' )
		++SS;
	    if ( CHARTYPE == CH_QUOTE ) {
		NameLen = SS - Name;
		++SS;
		CharType = CHARTYPE;
		result = MTOK_STRING;
	    }
	    break;
	default:
	    break;
    }
    return PrevTokenType = result;
}

char* TMathLexer::GetCurrentPos()
{
    return SS;
}