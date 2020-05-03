#ifndef _MATHPARSER_H_INCLUDED_
#define _MATHPARSER_H_INCLUDED_
/*
/////////////////////////////////////////////////////////////////////////////
*/
#include "StrMap.h"
#include "MathLexer.h"
#include "ZCalculator.h"
#include <system.hpp>
#define MAX_STACK_SIZE 64

extern const double DblErR;
extern const double DblNiN;
const int FunctNameLen=20;
const int VarNameLen=20;
typedef double (*OneArgFunc) ( double arg );
//typedef char* (*MultiArgUserFunc) ( int paramcnt, Variant *args,
//				 char *Name,double *result );

class PACKAGE TMathParser{
public:
	    TMathParser( TZCalculator* Calculate=NULL, char *MoreLetters=NULL );
            char* Parse( const char *Formula, Variant *result);
            ~TMathParser();
private:
	typedef enum {
		// Binary
		OP_SHL, OP_SHR, OP_POW,
		OP_LOGIC_NEQ, OP_LOGIC_GEQ, OP_LOGIC_LEQ,
		OP_LOGIC_AND, OP_LOGIC_OR, // Logical
		OP_COMSTART, OP_ASSIGN, // For internal needs
		OP_OBR, // Special
		OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_UNK, // Arithmetic
		OP_XOR, OP_NOT, OP_AND, OP_OR, // Bitwise
		OP_EQU, OP_GREATER, OP_LESS,
		OP_LOGIC, OP_LOGIC_SEP, OP_CBR, OP_COMMA, // Logical
		OP_FORMULAEND, // For script
		OP_FUNC_ONEARG, OP_FUNC_MULTIARG // Special
	} OperType_t;
	static const char OpPriorities[OP_FUNC_MULTIARG+1];
	typedef struct {
		OperType_t	OperType;
		void       *Func;
		char	PrevValTop;
                char    FunctName[FunctNameLen];
	} Operation;
	static const Operation BrOp;
	static const Operation NegOp;
        Operation OpStack[MAX_STACK_SIZE];
        Variant	 ValStack[MAX_STACK_SIZE]; /*double*/
        int	OpTop, ValTop;
        int	ObrDist;
	static int refCounter;
        TMathLexer Lexer;
	static TStrMap IntFunctions;
	static char errbuf[256];
	static int initializations_performed;
		TZCalculator* FCalculate;
	char* ParseFormula(Variant *result);
	char* PrepareFormula();
	char* Calc();
	char* CalcToObr();
};

#endif //_MATHPARSER_H_INCLUDED_