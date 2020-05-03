#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MathParser.h"


//#define MY_DEBUG 1
#pragma package(smart_init)
#ifndef M_E
# define M_E		2.7182818284590452354
#endif
#ifndef M_PI
# define M_PI		3.14159265358979323846
#endif

const double DblErR = -1.68736462823243E308;
const double DblNiN = -1.68376462823243E308;

//Error messages

static char eBrackets [] = "#括号不配对!";
static char eSyntax   [] = "#语法错误!";
static char eInternal [] = "#内部错误!";
static char eExtraOp  [] = "#过度操作,堆栈溢出!";
static char eInfinity [] = "#除零溢出!";
static char eInvArg   [] = "#参数非法!";
static char eUnknFunc [] = "# %s - 不可知函数或变量!";
static char eExtrnFunc[] = "#外部函数错误!";
static char eLogicErr [] = "#逻辑表达式错误!";
static char eCalcErr  [] = "#计算错误!";
static char eUnexpEnd [] = "#Unexpected end of script!";
static char eExpVarRet[] = "#Variable name or return expected!";
static char eExpAssign[] = "#Assignment expected!";
static char eValSizErr[] = "#值太大，无法操作!";
static char eInvPrmCnt[] = "#函数参数数量调用不符合要求!";

static char StdSymbols[] = "+-/*^~()<>%$,?:=&|;";

static char func_names[] =
    "ATAN\000COS\000SIN\000TAN\000ABS\000"
    "EXP\000LN\000LG\000SQRT\000FRAC\000"
    "TRUNC\000FLOOR\000CEIL\000ASIN\000"
    "ACOS\000SGN\000NEG\000E\000PI\000";
/* Indexes of some functions in func_names[] array */
#define FUNC_E		17
#define FUNC_PI		18

static double _neg_(double);
static double _frac_(double);
static double _trunc_(double);
static double _sgn_(double);

typedef double (*dfd)(double);
static dfd func_addresses[]= {
    &atan, &cos, &sin, &tan, &fabs,
    &exp, &log, &log10, &sqrt, &_frac_,
    &_trunc_, &floor, &ceil, &asin,
    &acos, &_sgn_, &_neg_, NULL, NULL };

inline void TypeTableAddChars( hqCharType *CharTypeTable, char *Symbols,
			hqCharType CharType )
{
    while (*Symbols)
	CharTypeTable[ (uchar) *Symbols++] = CharType;
}



// TMathParser implementation

//static members

const char TMathParser::OpPriorities[TMathParser::OP_FUNC_MULTIARG+1] = {
		5, 5, 5,    2, 2, 2, 2, 2,    -1, -1,   0,
		3, 3,    4, 4, 4, 4,
		5, 5, 5, 5,    2, 2, 2,   1, 2, 0, 2,
		-1, 6, 6 };

TStrMap TMathParser::IntFunctions;

char TMathParser::errbuf[256];

const TMathParser::Operation TMathParser::BrOp = {OP_OBR};

const TMathParser::Operation TMathParser::NegOp = { OP_FUNC_ONEARG, (void*)&_neg_, 0};

int TMathParser::initializations_performed = 0;

int TMathParser::refCounter = 0;

static  hqCharType MathCharTypeTable[256];
static  TMathSymTable MathSymTable;

void CreateCharTypeTable(void)
{
   InitCharTypeTable( MathCharTypeTable,
                     CH_LETTER | CH_DIGIT | CH_SEPARAT | CH_QUOTE );
   TypeTableAddChars( MathCharTypeTable, StdSymbols, CH_SYMBOL );

}
#pragma startup CreateCharTypeTable 80

TMathParser::TMathParser(TZCalculator* Calculate, char *MoreLetters){
    if (refCounter++ == 0) {
	 if (MoreLetters)
	    TypeTableAddChars( MathCharTypeTable, MoreLetters, CH_LETTER );
	 // init function maps
	 IntFunctions.CreateFromChain( sizeof(void*),
						(char*)func_names,
						func_addresses );
	 initializations_performed = 1;

    }
    FCalculate=Calculate;
    Lexer.NoIntegers = 1;
    Lexer.SymTable = &MathSymTable;
    Lexer.CharTypeTable = MathCharTypeTable;
    Lexer.cssn = 8;
    Lexer.ComEnd = "*/";
}

TMathParser::~TMathParser(){}

char* TMathParser::PrepareFormula()
{
    int BrCnt = 0;
    char *SS = Lexer.GetCurrentPos();

	while ( *SS ) {
	if (*SS=='(')
		++BrCnt;
	else if (*SS==')' && --BrCnt<0)
	    goto brkerr;
	++SS;
    }
    if (BrCnt != 0)
brkerr:	return eBrackets;

    OpTop = 0;
    ValTop = -1;
    OpStack[0].OperType = OP_OBR;
    ObrDist = 2;
    return NULL;
}

char* TMathParser::Parse(const char *Formula, Variant *result )
{
    if (!Formula || !*Formula) {
	*result = 0.0;
	return NULL;
    }

//    script = *Formula == '#' && *(Formula+1) == '!'
//		     && MathCharTypeTable[ (uchar)*(Formula+2) ] == CH_SEPARAT;
//
//    if ( script )	Formula += 3;

    Lexer.SetParseString( Formula );

    return ParseFormula(result);
}

char* TMathParser::ParseFormula( Variant *result ){
    char *ErrorMsg;
    hqTokenType ToTi;
    hqTokenType preToTi=MTOK_NONE;
    int presymbol= -1;

    if ( (ErrorMsg = PrepareFormula()) != NULL )
	return ErrorMsg;

    ToTi = Lexer.GetNextToken();
    for (;;) {
	--ObrDist;
	switch (ToTi) {
	    case MTOK_ERROR:
		return eSyntax;
	    case MTOK_FINAL:
formulaend:	if ( (ErrorMsg = CalcToObr()) != NULL )
		    return ErrorMsg;
		goto getout;
	    case MTOK_FLOAT:
                if(preToTi==MTOK_SYMBOL&&presymbol==OP_CBR)
                   return eSyntax;                               //校验不了连续的操作数f()var 或var1..varn
		ValStack[++ValTop] = Lexer.ExtValue;
		break;
	    case MTOK_SYMBOL:
                presymbol=Lexer.IntValue;
		switch ( Lexer.IntValue ) {
		    case OP_OBR:	// (
			OpStack[++OpTop] = BrOp;
			ObrDist = 2;
			break;
		    case OP_CBR:	// )
			if ( (ErrorMsg = CalcToObr()) != NULL )
			    return ErrorMsg;
			break;
		    case OP_COMMA: {	// ,
			Operation *pOp;
			if ( (ErrorMsg = CalcToObr()) != NULL )
			    return ErrorMsg;
			if ( (pOp = &OpStack[OpTop])->OperType
			     == OP_FUNC_MULTIARG ) {
			    OpStack[++OpTop] = BrOp;
			    ObrDist = 2;
			} else
			    return eSyntax;
			break;
		        }
		    default: {
			Operation Op;
			Op.OperType = (OperType_t) Lexer.IntValue;
			switch (Op.OperType) {
			    case OP_FORMULAEND:
//				if (script)
//				    goto formulaend;
//				else
				    return eSyntax;
			    case OP_ADD:
				if (ObrDist >= 1)
				    goto next_tok;
				break;
			    case OP_SUB:
				if (ObrDist >= 1) {
				    OpStack[++OpTop] = NegOp;
				    goto next_tok;
				}
				break;
			    case OP_LOGIC:
			    case OP_LOGIC_SEP:
				ObrDist = 2;
			    default:
				break;
			}
			while ( OpPriorities[ Op.OperType ]
				<=
				OpPriorities[ OpStack[OpTop].OperType ] ) {
			    if ( (ErrorMsg = Calc()) != NULL )
				return ErrorMsg;
			}
			OpStack[++OpTop] = Op;
			break;
		    }
		}
		break;
	    case MTOK_NAME: {
		Operation Op;
		double *value, dblval;
		void **func;
		int funcnum, i, namelen = Lexer.NameLen;

		char *SS = Lexer.Name;
		for (i = namelen; i>0; --i)
		    *SS++ = Win1251UpcaseTbl[ (int)*SS ];

		funcnum = IntFunctions.IndexOf(Lexer.Name,Lexer.NameLen,(void**) &func );
		if ( funcnum >= 0 ) {               //内部已定义函数
		    Op.Func = *func;
		    switch ( funcnum ) {
			case FUNC_E:
			    ValStack[++ValTop] = M_E;
			    break;
			case FUNC_PI:
			    ValStack[++ValTop] = M_PI;
			    break;
			default:// Internal function
			    Op.OperType = OP_FUNC_ONEARG;
             		    strncpy( Op.FunctName, Lexer.Name, Lexer.NameLen );
                            Op.FunctName[Lexer.NameLen]='\0';
			    OpStack[++OpTop] = Op;
		    }
		}
                else if(FCalculate)
                {
                    char VarOrFunctName[VarNameLen];
                    strncpy(VarOrFunctName,Lexer.Name,Lexer.NameLen);
                    VarOrFunctName[ Lexer.NameLen ] = '\0';
                    if (FCalculate->IsExtFunction(VarOrFunctName)>-1)   //是外部函数
                    {
                        Op.Func = NULL;
                        Op.OperType = OP_FUNC_MULTIARG;
                        strncpy( Op.FunctName, Lexer.Name, Lexer.NameLen );
                        Op.FunctName[Lexer.NameLen]='\0';
                        Op.PrevValTop = ValTop;
                        OpStack[++OpTop] = Op;
                    }
                    else  //是变量
                       ValStack[++ValTop] = FCalculate->GetVarValue(VarOrFunctName);

	        }
               else
               {
                char buf[256];
                strncpy( buf, Lexer.Name, Lexer.NameLen );
                buf[ Lexer.NameLen ] = '\0';
                sprintf( errbuf, eUnknFunc, buf );
                return errbuf;
               }
        	break;
	    }
	    case MTOK_STRING: {
                char strPar[VarNameLen];
                strncpy(strPar,Lexer.Name,Lexer.NameLen);
                strPar[ Lexer.NameLen ] = '\0';
                ValStack[++ValTop] = strPar;
		break;
	    }
	    default:
		return eSyntax;
	}
next_tok:
    preToTi=ToTi;
    ToTi = Lexer.GetNextToken();
    } // forever

getout:
    if (OpTop != -1 || ValTop != 0)
	return eInternal;

    *result = ValStack[0];
    return NULL;
}

char* TMathParser::Calc()
{
    Variant Res;
    Variant ValR;
    Operation Op = OpStack[OpTop--];

    // multi-argument external or internal fucntion
    if ( Op.OperType == OP_FUNC_MULTIARG ) {
	int paramcnt = ValTop - Op.PrevValTop;
	char *ErrorMsg;
#ifdef MY_DEBUG
	printf( "ValTop = %d, OpTop = %d, PrevValTop = %d\n",
		ValTop, OpTop, Op.PrevValTop );
#endif
	ValTop = Op.PrevValTop;
        Res=0;
        if(FCalculate&&FCalculate->OnFunction)
        {
         Variant varArg=VarArrayCreate(OPENARRAY(int, (0, paramcnt-1)), varVariant);
         for(int c=0;c<paramcnt;c++)
             varArg.PutElement(ValStack[ValTop+c+1],c);
          Res=FCalculate->GetFunctionValue(Op.FunctName,varArg);
          varArg.Clear();
        }
	ValStack[++ValTop] = Res;
#ifdef MY_DEBUG
	printf("ValTop = %d, OpTop = %d\n", ValTop, OpTop );
#endif
	return NULL;
    }

    if (Op.OperType==OP_LOGIC)
	return NULL; 

    // get right arg
    if (ValTop<0)
	return eExtraOp;
    ValR = ValStack[ValTop--];

    // one arg operations
    if (Op.OperType==OP_NOT) {
	if ((double)ValR >= INT_MIN && (double)ValR <= INT_MAX)
	    Res = ~((int) ValR);
	else
	    return eValSizErr;
    } else if (Op.OperType==OP_FUNC_ONEARG) {
	Res = (*(OneArgFunc)Op.Func)( ValR );
    } else {
	// get left arg
        Variant ValL;
	if (ValTop<0)
	    return eExtraOp;
	ValL = ValStack[ValTop--];
	switch (Op.OperType) {
        	    // Arithmetic
	    case OP_ADD:
		Res = (double)ValL + (double)ValR;		break;
	    case OP_SUB:
		Res = (double)ValL - (double)ValR;		break;
	    case OP_MUL:
		Res = (double)ValL * (double)ValR;		break;
	    case OP_DIV:
		if (ValR == 0.0)
		    return eInfinity;
		Res =(double)ValL /(double)ValR;
		break;
//we don't need other operation
/*
	    // Binary
	    case OP_SHL:
		if ((double)ValL >= INT_MIN && (double)ValL <= INT_MAX && (double)ValR >= INT_MIN && (double)ValR <= INT_MAX)
		    Res = (int) ValL << (int) ValR;
		else
		    return eValSizErr;
		break;
	    case OP_SHR:
		if ((double)ValL >= INT_MIN && ((double)ValL <= INT_MAX) && ((double)ValR >= INT_MIN) && ((double)ValR <= INT_MAX))
		    Res = (int) ValL >> (int) ValR;
		else
		    return eValSizErr;
		break;
	    case OP_POW:
		Res = pow( ValL, ValR );	break;
*/

	    // Logical
	    case OP_LOGIC_NEQ:
		Res = (ValL != ValR);		break;
	    case OP_LOGIC_GEQ:
		Res = (ValL >= ValR);		break;
	    case OP_LOGIC_LEQ:
		Res = (ValL <= ValR);		break;
	    case OP_LOGIC_AND:
		Res = ((double)ValL&&(double)ValR);	break;
	    case OP_LOGIC_OR:
		Res = ((double)ValL||(double)ValR);	break;
/*
	    // Arithmetic
	    case OP_ADD:
		Res = ValL + ValR;		break;
	    case OP_SUB:
		Res = ValL - ValR;		break;
	    case OP_MUL:
		Res = ValL * ValR;		break;
	    case OP_DIV:
		if (ValR == 0.0)
		    return eInfinity;
		Res =(double)ValL /(double)ValR;
		break;
	    case OP_MOD:
		Res = fmod(ValL, ValR);	break;
	    case OP_UNK:
		if (ValL<=0)
		    Res = 0.0;
		else if (ValR==0.0)
		    return eInfinity;
		else
		    Res = ceil(ValL / ValR);
		break;
*/
	    // Bitwise
	    case OP_XOR:
		if ((double)ValL >= INT_MIN && (double)ValL <= INT_MAX && (double)ValR >= INT_MIN && (double)ValR <= INT_MAX)
			Res = (int) ValL ^ (int) ValR;
		else
			return eValSizErr;
		break;
	    case OP_AND:
		if ((double)ValL >= INT_MIN && (double)ValL <= INT_MAX && (double)ValR >= INT_MIN && (double)ValR <= INT_MAX)
			Res = (int) ValL & (int) ValR;
		else
			return eValSizErr;
		break;
	    case OP_OR:
		if ((double)ValL >= INT_MIN && (double)ValL <= INT_MAX && (double)ValR >= INT_MIN && (double)ValR <= INT_MAX)
			Res = (int) ValL | (int) ValR;
		else
			return eValSizErr;
		break;
	    // Logical
	    case OP_EQU:
		Res = (ValL == ValR);		break;
	    case OP_GREATER:
		Res = (ValL > ValR);		break;
	    case OP_LESS:
		Res = (ValL < ValR);		break;
	    case OP_LOGIC_SEP: {
		// needs three arguments
		double ValLL;
		if (OpTop < 0
		    || OpStack[OpTop--].OperType != OP_LOGIC)
		    return eLogicErr;
		ValLL = ValStack[ ValTop-- ];
		Res = ValLL ? ValL : ValR;
		break;
	    }

	    default:
		return eInternal;
	}
    }
    ValStack[++ValTop] = Res;
    return NULL;
}

char* TMathParser::CalcToObr()
{
    while ( OpStack[OpTop].OperType != OP_OBR ) {
	char *ErrorMsg;
	if ( (ErrorMsg = Calc()) != NULL )
	    return ErrorMsg;
    }
    --OpTop;
    return NULL;
}

/* misc functions */

static double _frac_( double x )
{
    double y;
    return modf(x, &y);
}

static double _trunc_( double x )
{
    return (x >= 0.0) ? floor(x) : ceil(x);
}

static double _sgn_( double x )
{
    return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

static double _neg_( double x )
{
    return -x;
}

/* "Advanced" round function; second argument - sharpness */
static char* _round_( int paramcnt, double *args, double *result )
{
    int i, sharpness;
    double x, coef;

    if (paramcnt == 1)
	sharpness = 0;
    else if (paramcnt == 2)
	sharpness = (int) args[1];
    else
	return eInvPrmCnt;

    x = args[0];
    if (sharpness < 0) {
	coef = 0.1;
        sharpness = -sharpness;
    } else
	coef = 10;

    for (i = 0; i < sharpness; i++)
	x *= coef;

    x = (x + ( (x >= 0) ? 0.5 : -0.5 ) );
    if (x >= 0.0)
	x = floor(x);
    else
	x = ceil(x);

    for (i = 0; i < sharpness; i++)
	x /= coef;

    *result = x;

    return NULL;
}