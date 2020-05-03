//////////////////////////////////////////////////////////////////////

#include "SymTable.h"
#include <string.h>
#include <stdlib.h>
#pragma package(smart_init)

static char MathSymbols[] =
    "\033\002" "<<" ">>" "**" "<>" ">=" "<=" "&&" "||" "/*" ":="
    "\033\001" "(+-*/%$^~&|=><?:),;";

TSymTable::~TSymTable(){
	for(int i = 0; i < 256 ; i++){
		free(table[ i ]);
	}
}

void TSymTable::PrepareSymbols( char *symbols ){
    int i = 0, nchars = 1;
    memset( table, 0, 256 * sizeof(SymbolRec*) );
    while (*symbols) {
	if (*symbols=='\033') {
	    nchars = *++symbols;
	    ++symbols;
	} else {
	    SymbolRec **RecList = &table [*symbols];
	    SymbolRec *Rec = *RecList;
	    int count = 0;
	    while ( Rec ) {
		++count;
		if ( Rec->More )
		    ++Rec;
		else
		    break;
	    }
	    if ( Rec ) {
			*RecList = (SymbolRec*)
				realloc( *RecList, (count+1)*sizeof(SymbolRec) );
			Rec = *RecList + count;
			(Rec-1)->More = 1;
	    } else {
			SymbolRec* R = (SymbolRec*) malloc( sizeof(SymbolRec) );
			*RecList=R;
			Rec = *RecList;
	    }
	    strncpy( Rec->Sym, symbols, 4 );
	    Rec->Len = (char) nchars;
	    Rec->Index = (char) i;
	    Rec->More = 0;
	    symbols += nchars;
	    ++i;
	}
    }
}

int TSymTable::FindSymbol( char *str, int *nchars )
{
    SymbolRec *Rec = table[ (int)*str ];
    while ( Rec ) {
	if ( (Rec->Len == 1 && Rec->Sym[0] == str[0])
	     ||
	     (Rec->Len == 2 && Rec->Sym[0] == str[0] && Rec->Sym[1] == str[1])
	     ||
	     (Rec->Len == 3 && Rec->Sym[0] == str[0] && Rec->Sym[1] == str[1]
	      && Rec->Sym[2] == str[2])
	   ) {
	    *nchars = Rec->Len;
	    return Rec->Index;
	}
	Rec = ( Rec->More ) ? Rec + 1 : NULL;
    }
    return -1;
}

TMathSymTable::TMathSymTable(){
	PrepareSymbols(MathSymbols);
}
