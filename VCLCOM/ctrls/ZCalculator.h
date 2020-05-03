//---------------------------------------------------------------------------

#ifndef ZCalculatorH
#define ZCalculatorH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <map>
#include <vector>
using namespace std;
typedef map<String,Variant,less<String> > TVarLists;//系统变量和他的值记录集
typedef void __fastcall (__closure *TFunctionEvent)(TObject* Sender, String FuncName,Variant &Args, Variant &Result);
typedef void __fastcall (__closure *TVariantEvent)(TObject* Sender, String VarName, Variant &Result);
//---------------------------------------------------------------------------
typedef struct FormulaItem  //节点
{
  bool  bIsCac;       //已计算过标示
  bool  bIsFormula;   //是否是计算公式
  Variant varValue;     // 最终值
  String strFormual; //计算公式
}TFormulaItem;
typedef vector<TFormulaItem*> TFormulaItems; //动态数组
typedef vector<TFormulaItems*> TFormulaItemArry; //动态数组
//TFormulaItemArry[row][col]-->TFormulaItem;
//---------------------------------------------------------------------------
class PACKAGE TZCalculator : public TComponent
{
private:
        TVarLists FVarLists;
        TFunctionEvent FOnFunction;
        TVariantEvent FOnVar;
        String FUserFunctionName;
        int FMaxVarNum;
        int FMaxIteration;
        int FIterationCycle;
        TStringList *ExtFunctionList;
        void __fastcall SetMaxVarNum(int value);
protected:
public:
        __fastcall TZCalculator(TComponent* Owner);
        __fastcall virtual ~TZCalculator();
        Variant __fastcall GetVarValue(String VarName); //获取某变量的值
        Variant __fastcall GetFunctionValue(String FuncName,Variant Args); //获取某函数的值
        void __fastcall SetVarValue(String VarName, Variant Value);  //增加系统变量和他的值
        int __fastcall AddExtFunction(String FunctName);       //增加用户自定义函数
        void __fastcall DeleteExtFunction(String FunctName);   //删除用户自定义函数
        void __fastcall ClearExtFunction();                        //清除所有自定义函数
        int __fastcall IsExtFunction(String FunctName);       //返回自定义函数在列表中的位置
__published:
        __property TFunctionEvent OnFunction  = { read=FOnFunction, write=FOnFunction };//当遇函数时触发
        __property TVariantEvent OnVar  = { read=FOnVar, write=FOnVar };//当遇变量时触发
        __property String UserFunctionName  = { read=FUserFunctionName, write=FUserFunctionName }; //自定义函数
        __property int MaxVarNum  = { read=FMaxVarNum, write=SetMaxVarNum }; //最大变量个数
        __property int MaxIteration  = { read=FMaxIteration, write=FMaxIteration }; //最大迭代层级,超出报错
};
Variant __fastcall PACKAGE CalculateFmla(TZCalculator *FCalculate,String strFormula); //计算表达式并返回值
String __fastcall PACKAGE RepFmlaWithPeriod(String strFormula,String ReseWord,String iPeriod);//返回替换的字符串
//---------------------------------------------------------------------------
#endif

