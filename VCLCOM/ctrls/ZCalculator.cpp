//---------------------------------------------------------------------------
/*
最新更改
2004-07-5
3、修正了函数后紧跟常量不报错的漏洞，如：SZQS(var1,var2)100是不符合语法的
2、替换计算内核 ，采用分析树处理表达式，边解析边计算，函数里的参数可以为表达式
1、新增属性 int MaxIteration 迭代深度限制，默认50级，超出报表达式有错
2004-4-15
TsdCalculate计算器的应用
属性：
 1--UserFunctionName  用户自定义函数名，默认SZQS（已废弃，可以任意增加自定义函数个数）
 2--MaxVarNum  用户自定义函数最大参数个数,默认3(已废弃，参数个数无限制)
事件：
 1--OnFunction 当遇到函数时触发事件，(系统保留函数CELLS(int col,row)，ZB(...)和SZQS(...));
     当该事件发生时，将返回函数名、参数列表和函数的返回值地址；用户需要实现各自的外部函数；
 2--OnVar  当遇到变量是触发事件
    当该事件发生时，将返回变量名和返回值地址
方法：
	void __fastcall SetVarValue(String VarName, Variant Value);//系统变量名和它的值
	用户可以往系统增加自定义变量
	Variant __fastcall GetVarValue(String VarName); //处理变量
	取用户自定义变量的值，如果找不到，则触发OnVar事件
	Variant __fastcall GetFunctionValue(String FuncName,Variant Args); //处理函数值
        取函数返回值，将触发OnFunction事件
        int __fastcall AddExtFunction(String FunctName);   //增加自定义函数,返回插入位置，
                                                                //函数名在列表中将以大写存储
        程序员可以调用该方法增加自己自定义函数，当然程序员要自己在OnFunction中检测并实现自定义
        函数的返回值
        void __fastcall DeleteExtFunction(String FunctName);//删除自定义函数
        void __fastcall ClearExtFunction(); //清除自定义函数列表(为了兼容以前版本，构建还会保留三个函数SZQS，ZB和CELLS）
        int __fastcall IsExtFunction(String FunctName);//自定义函数和它的标志值（列表中的位置Index）
        其中保留函数SZQS(Index=0),CELLS(Index=1),ZB(Index=2)

*/
#include <vcl.h>
#pragma hdrstop

#include "ZCalculator.h"
#include "Lexer.h"
#include "CPLexer.h"
#include "tokstr.h"
#include "MathParser.h"
#pragma package(smart_init)
#define OPND 'D'
#define OPTR 'R'
#define  CONTINUE_READ_NEXT_NOTATION 'C'
#define  STOP_READ_NEXT_NOTATION     'S'
//注意：符号'变量'中不能包含'+-*/()[]#=%'
//运算符号只能为'+-*/()%'
#define MAX_EXP_LEN       65535
#define	MAX_NOTATION_NUM  1000	/* 一个表达式中的最大算符个数 */
#define MAX_NOTATION_LEN  30		/* 表达式中一个算符的最大字串长度 */
typedef struct  VarStack {					/* 表达式计算堆栈 */
	Variant OpdStack[MAX_NOTATION_NUM];	/* 操作数堆栈 */
	char 	OpStack[MAX_NOTATION_NUM];	/* 运算符堆栈 */
	int     OpdStackTop,		/* 操作数堆栈顶指针 */
        	OpStackTop; 		/* 运算符堆栈顶指针 */
} ExpressionCalculateStack;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TZCalculator *)
{
        new TZCalculator(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZCalculator::TZCalculator(TComponent* Owner)
        : TComponent(Owner)
{
    FVarLists.clear();
    FMaxVarNum=3;
    FUserFunctionName="szqs";
    FMaxIteration=50;
    FIterationCycle=0;
    ExtFunctionList=new TStringList();
    ClearExtFunction();
}
//---------------------------------------------------------------------------
namespace Zcalculator
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TZCalculator)};
                 RegisterComponents("ZAdditional", classes, 0);
        }
}
//---------------------------------------------------------------------------
Variant __fastcall TZCalculator::GetVarValue(String VarName)
{
  Variant Result=NULL;
  TVarLists::iterator p=FVarLists.find(VarName.UpperCase());
 if (p != FVarLists.end())
    Result= p->second;
  else if(FOnVar)
  {
      FIterationCycle++;
      if(FIterationCycle>FMaxIteration)
        {
          FIterationCycle=0;
           throw Exception("计算表达式已超过系统所允许的递归调用"+IntToStr(FMaxIteration)+"层，可能公式有误");
        }

      FOnVar(this,VarName,Result);

      FIterationCycle--;
  }
  return Result;
}
//---------------------------------------------------------------------------
Variant __fastcall TZCalculator::GetFunctionValue(String FuncName,Variant Args)
{
  Variant Result=NULL;
  if(FuncName=="IF")
  {
    int ivarCount=0;
    if(!Args.IsEmpty())
    {
       ivarCount=Args.ArrayHighBound()-Args.ArrayLowBound()+1;//返回变量个数
    }
    if(ivarCount!=3)
      throw Exception("IF表达式必须有3个参数");
    bool bvar = Args.GetElement(0);
    String svar = "";
    if(bvar)
    {
      svar=Args.GetElement(1);
      Result = Args.GetElement(1);
    }
    else
    {
      svar=Args.GetElement(2);
      Result = Args.GetElement(2);
    }
    if(svar.Trim().IsEmpty())
      Result = 0;
  }
  else
  {
    if(FOnFunction)
    {
      FIterationCycle++;
      if(FIterationCycle>FMaxIteration)
        {
          FIterationCycle=0;
           throw Exception("计算表达式已超过系统所允许的递归调用"+IntToStr(FMaxIteration)+"层，可能公式有误");
        }

      FOnFunction(this,FuncName,Args,Result);

      FIterationCycle--;
    }
  }
  return Result;
}
//---------------------------------------------------------------------------
void __fastcall TZCalculator::SetVarValue(String VarName, Variant Value)
{
  TVarLists::iterator p=FVarLists.find(VarName.UpperCase());
  if (p != FVarLists.end())
      p->second=Value;
   else
     FVarLists.insert(TVarLists::value_type(VarName.UpperCase().c_str(),Value));
}
//---------------------------------------------------------------------------
void __fastcall TZCalculator::SetMaxVarNum(int value)
{
        if(FMaxVarNum != value) {
         if(value<0)
            FMaxVarNum=0;
          else
           FMaxVarNum = value;
        }
}
int __fastcall TZCalculator::AddExtFunction(String FunctName)
{
        int findex=IsExtFunction(FunctName);
        if(findex==-1)
          return ExtFunctionList->Add(FunctName.Trim().UpperCase());
        else
          return findex;
}

void __fastcall TZCalculator::DeleteExtFunction(String FunctName)
{
        int findex=IsExtFunction(FunctName);
        if(findex>-1)
           ExtFunctionList->Delete(findex);
}

void __fastcall TZCalculator::ClearExtFunction()
{
   ExtFunctionList->Clear();
   ExtFunctionList->Add("SZQS");
   ExtFunctionList->Add("CELLS");
   ExtFunctionList->Add("ZB");
   ExtFunctionList->Add("SUM");   
   ExtFunctionList->Add("IF");   
}

int __fastcall TZCalculator::IsExtFunction(String FunctName)
{
       return ExtFunctionList->IndexOf(FunctName.Trim().UpperCase());
}

__fastcall TZCalculator::~TZCalculator()
{
    if(ExtFunctionList)
    {
       ExtFunctionList->Clear();
       delete ExtFunctionList;
    }
}
//---------------------------------------------------------------------------

char  opstr[] = "+-*/()#"; //定义操作符 公式中'%'='/100'进行处理
int  priortable[7][7] =    //优先级
  /*  +  -   *   /   (  )  #  */
  {1, 1, -1, -1, -1, 1, 1,
   1, 1, -1, -1, -1, 1, 1,
   1, 1, 1, 1, -1, 1, 1,
   1, 1, 1, 1, -1, 1, 1,
   -1, -1, -1, -1, -1, 0, 'I',
   1, 1, 1, 1, 'I', 1, 1,
   -1, -1, -1, -1, -1, 'I', 0,
  };
//---------------------------------------------------------------------------
char __fastcall GetTypeOfNotation (char *notation)
{
  int i;

  if (notation[0] == '\0')
    return NULL;

  for (i = 0; opstr[i] != '\0'; i++)
    if (notation[0] == opstr[i])
      return OPTR;

  return OPND;
}
//---------------------------------------------------------------------------
int __fastcall CompareOpPrior (char op2, char op1)
{
  char  i, j;
  for (i = 0; opstr[i] != '\0'; i++)
    if (op1 == opstr[i])
      break;

  for (j = 0; opstr[j] != '\0'; j++)
    if (op2 == opstr[j])
      break;

  return priortable[i][j];
}
//---------------------------------------------------------------------------
void __fastcall push (char type, char op, Variant opnd,
		  ExpressionCalculateStack * s)
{

  if (type == OPND)
    s->OpdStack[s->OpdStackTop++] = opnd;
  else
    s->OpStack[s->OpStackTop++] = op;
}
//---------------------------------------------------------------------------
double __fastcall pop (char type, ExpressionCalculateStack * s,TZCalculator *FCalculate)
{
  if (type == OPND)
    {
      bool  bIsDigit = true;
      String   VarName;
      if(s->OpdStackTop==0)//"栈已空"
         throw Exception("公式不合法");
      String retVal= s->OpdStack[--s->OpdStackTop];
      for (int i = 1; i <= retVal.Length (); i++)
	{
	  if (!(isdigit (retVal[i])||retVal[i]=='.'||retVal[i]=='-')) //zy.2003.06.17添加判断”||retVal[i]=='-'“否则不能处理负数。
	    {
	      bIsDigit = false;
	      break;
	    }
	}
      if (bIsDigit)
	return retVal.ToDouble ();
       else
	{
          if((retVal[1]=='\"')||retVal[retVal.Length()]=='\"')
             throw Exception("暂时无法处理字符串计算:"+retVal);
          else
          {
           return   (double)FCalculate->GetVarValue(retVal);
          }
	}
    }
  else
    return (double) (s->OpStack[--s->OpStackTop]);
}
//---------------------------------------------------------------------------
double __fastcall calculate (double opnd1, char op, double opnd2)
{

  switch (op)
    {
    case '+':
      return opnd1 + opnd2;
    case '-':
      return opnd1 - opnd2;
    case '*':
      return opnd1 * opnd2;
    case '/':
      if (opnd2 != 0.0)
	return opnd1 / opnd2;
      else
	throw Exception("出现除零情况");
    }
  return 0.0;
}
//---------------------------------------------------------------------------
void __fastcall GetNextNotation (char *notation, char *exp,int &index)
{
  int  j, type, lasttype;

  lasttype = GetTypeOfNotation (exp + index);
  for (j = 0; exp[index] != '\0'; j++, index++)
    {
//     if(j>18)
//      throw Exception("变量超过了系统允许的长度18位");
      if (exp[index] == ' ')
	continue;
      notation[j] = exp[index];
      type = GetTypeOfNotation (notation + j);
      if (type == OPTR && lasttype == OPTR)
	{
	  index++, j++;
	  break;
	}
      if (type == OPTR && lasttype == OPND)
	break;

      lasttype = type;
    }

  notation[j] = NULL;
  if (notation[0] == '#') // 结束符，则index=0;
    index = 0;
}
//---------------------------------------------------------------------------

Variant __fastcall CalculateFmla(TZCalculator *FCalculate,String strFormula)
{
//     String myexp=strFormula.UpperCase();
	 AnsiString myexp=strFormula;
     if(myexp.Trim().IsEmpty()||myexp[1]!='=') //公式非法
       return 0.0;
     if(myexp.Length()<=1)
          throw Exception("表达式非法,只有一个'='");
       //处理百分号%
     TReplaceFlags Flags;
     Flags<<rfReplaceAll<<rfIgnoreCase;
     myexp=myexp.SubString(2,myexp.Length()-1);//去除'='
     myexp=StringReplace(myexp,"%","/100",Flags);
     //去除空格
	  AnsiString newexp="";
      for(int l=1;l<=myexp.Length();l++)
	  {
         if(myexp[l]!=' '&&myexp[l]!='\n'&&myexp[l]!='\r')
            newexp+=myexp[l];
      }
     Variant Result;
	 TMathParser mp(FCalculate);
	 char *ErrMsg = mp.Parse( newexp.c_str(), &Result );
     if(ErrMsg!=NULL)
        throw Exception(ErrMsg);
	 return Result;
}

String __fastcall RepFmlaWithPeriod(String strFormula,String ReseWord,String iPeriod)
{
        String Formula=strFormula;
		if(Formula.Trim().IsEmpty())
           return Formula;
		String newexp="";
        for(int l=1;l<=Formula.Length();l++)
        {
           if(strFormula[l]!=' '&&strFormula[l]!='\n'&&Formula[l]!='\r')
              newexp+=Formula[l];
        }
        Formula=newexp;
		TToken tok;
        TTokenString tokenString;
        TStringIStream *StrStream=new TStringIStream(newexp);
        TCPPScan Scan (StrStream,tokenString);
        newexp="";
         while (true)
          {
             tok = Scan.NextToken ();
              if (tok.type == TOK_EOF) break;
              if(tok.type==TOK_ID)
              {
                if(UpperCase(tok.text)==ReseWord.Trim().UpperCase())
                    tok.text=iPeriod;
              }
               newexp+=tok.text;
          }
        Formula=newexp;
        return Formula;                      
}


