#if !defined(_SYMTABLE_H_INCLUDED_)
#define _SYMTABLE_H_INCLUDED_

class TSymTable{
public:
	typedef struct {
		char Sym[4];
		char Len;
		char Index;
		char More;
	} SymbolRec;
	virtual ~TSymTable();

	void PrepareSymbols( char *symbols );
	int FindSymbol( char *str, int *nchars );
protected:
	TSymTable(){};
private:
	SymbolRec* table[256];
};

class TMathSymTable: public TSymTable{
public:
	TMathSymTable();
	virtual ~TMathSymTable(){};
};


#endif // !defined(_SYMTABLE_H_INCLUDED_)
