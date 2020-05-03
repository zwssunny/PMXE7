// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'atPascal.pas' rev: 28.00 (Windows)

#ifndef AtpascalHPP
#define AtpascalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.TypInfo.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <atParser.hpp>	// Pascal unit
#include <atScript.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <System.Character.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Atpascal
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TatPascalScripter;
typedef void __fastcall (__closure *TUserProc)(TatPascalScripter* AScripter);

class PASCALIMPLEMENTATION TatPascalScripter : public Atscript::TatCustomScripter
{
	typedef Atscript::TatCustomScripter inherited;
	
private:
	void __fastcall DeleteCascadeUserProcs(void);
	
protected:
	virtual void __fastcall DefineInternalClasses(void);
	
public:
	__fastcall virtual TatPascalScripter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TatPascalScripter(void);
	Atscript::TGenericProc __fastcall UserProc(TUserProc AProc);
	
__published:
	__property SourceCode;
	__property Compiled;
	__property SaveCompiledCode;
	__property EventSupport = {default=1};
	__property EventSetMode = {default=0};
	__property EventUnsetMode = {default=0};
	__property OnDebugHook;
	__property OnExecHook;
	__property OnCompileError;
	__property OnRuntimeError;
	__property OnExecuteEvent;
	__property OnSettingEvent;
	__property OnSetEvent;
	__property OnUnsettingEvent;
	__property ShortBooleanEval;
	__property LibOptions;
	__property CallExecHookEvent;
	__property OnUnknownElement;
	__property OnBreakpointStop;
};


class DELPHICLASS TatPascalRefactor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatPascalRefactor : public Atscript::TatScriptRefactor
{
	typedef Atscript::TatScriptRefactor inherited;
	
protected:
	virtual bool __fastcall IsStatementEndChar(System::WideChar ch);
	virtual System::UnicodeString __fastcall BuildMethodHint(Atscript::TatMethod* meth);
	virtual System::UnicodeString __fastcall BuildRoutineHint(Atscript::TatRoutineInfo* routine);
	
public:
	virtual void __fastcall UpdateFormHeader(System::UnicodeString AFormClass, System::UnicodeString AFileName);
	virtual int __fastcall DeclareRoutine(Atscript::TatRoutineInfo* AInfo)/* overload */;
	virtual void __fastcall AddUsedUnit(System::UnicodeString AUnitName);
public:
	/* TatScriptRefactor.Create */ inline __fastcall TatPascalRefactor(Atscript::TatScript* AScript) : Atscript::TatScriptRefactor(AScript) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TatPascalRefactor(void) { }
	
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  DeclareRoutine(System::UnicodeString ProcName){ return Atscript::TatScriptRefactor::DeclareRoutine(ProcName); }
	
};

#pragma pack(pop)

class DELPHICLASS TatPascalScript;
class PASCALIMPLEMENTATION TatPascalScript : public Atscript::TatScript
{
	typedef Atscript::TatScript inherited;
	
private:
	int FForCount;
	int FCurrentFor;
	int FWhileCount;
	int FCurrentWhile;
	int FRepeatCount;
	int FCurrentRepeat;
	int FIfCount;
	int FCurrentIf;
	int FCaseCount;
	int FCurrentCase;
	int FWithCount;
	int FCurrentWith;
	int FOperatorCount;
	int FCurrentOperator;
	int FCaseVarIndex;
	int FCaseBranchLevel;
	Atscript::TLoopStatement FCurrentLoop;
	Atscript::TatClass* FCurrentClass;
	bool FIsClassReference;
	int FLastByRefArgMask;
	int FByRefArgMask;
	bool FThereIsAnySubrot;
	System::Contnrs::TObjectList* FPushVarListObjects;
	System::Classes::TList* FPushVarList;
	System::Classes::TList* FLastPushVarList;
	bool __fastcall AcceptNodeId(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeMain(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterMain(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterImports(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterUses(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeSubRoutine(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterSubRoutine(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterInputArgs(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterVarDecl(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterConstExpr(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterPushOutput(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeFor(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterFor(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterForControl(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterStep(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeWhile(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterWhile(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeWhileControl(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterWhileControl(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeRepeat(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeUntil(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterUntil(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeIf(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterIf(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeThen(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterThen(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeElse(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeExpression(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterExpression(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterOperator(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterUnary(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterLabel(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterId(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterReal(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterHex(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterString(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterVector(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeArgList(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterArgList(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeCallCode(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeCallPtrCode(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeDataValCode(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeDataRefCode(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeTry(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterTryStatements(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterTryUpshot(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterCase(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeCase(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterCaseExpr(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterCaseTest(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterCaseMatch(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeCaseMatch(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterCaseBranch(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeCaseBranch(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterAsClass(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterWithObj(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterWith(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeGlobalDecl(Atparser::TNoTerminalNode* Node);
	void __fastcall AfterExternal(Atparser::TNoTerminalNode* Node);
	void __fastcall MakeDataElementCode(Atparser::TNoTerminalNode* Node, Atscript::TDataOperation operation);
	bool __fastcall SpecialKeyWord(System::UnicodeString AName, Atscript::TDataOperation operation);
	System::UnicodeString __fastcall ExtractQuotedString(const System::UnicodeString S);
	void __fastcall ExtractSourceRemark(Atparser::TatSyntaxParser* AParser, int AStartPos, int AFinalPos);
	void __fastcall AfterIndexing(Atparser::TNoTerminalNode* Node);
	void __fastcall BeforeIndexing(Atparser::TNoTerminalNode* Node);
	
protected:
	virtual System::UnicodeString __fastcall EncodeSingleAssign(System::UnicodeString AVarName, System::UnicodeString AExpression);
	
public:
	__fastcall virtual TatPascalScript(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatPascalScript(void);
	virtual void __fastcall Clear(void);
	TatPascalScripter* __fastcall PascalScripter(void);
};


class DELPHICLASS TatProcCollectionItem;
class PASCALIMPLEMENTATION TatProcCollectionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatPascalScripter* FScripter;
	TUserProc FUserProc;
	void __fastcall GenericProc(void);
	
public:
	__property TatPascalScripter* Scripter = {read=FScripter, write=FScripter};
	__property TUserProc UserProc = {read=FUserProc, write=FUserProc};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatProcCollectionItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatProcCollectionItem(void) { }
	
};


class DELPHICLASS TatProcCollection;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatProcCollection : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatProcCollectionItem* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatProcCollectionItem* __fastcall GetItem(int i);
	
public:
	__fastcall TatProcCollection(void);
	TatProcCollectionItem* __fastcall AddUserProc(TatPascalScripter* AScripter, TUserProc AUserProc);
	__property TatProcCollectionItem* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatProcCollection(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM atPASCAL_NOTERMINALS : unsigned char { noProgram, noGlobalDecl, noMain, noLibraries, noUses, noImports, noSubroutine, noCallingConvetion, noExternal, noFileName, noForward, noProcedure, noFunction, noInputArgs, noByRef, noByVal, noConstDecl, noConstExpr, noConstName, noVarDecl, noVarList, noVarName, noVarType, noStatement, noBlock, noCall, noCall_code, noCall_ptr, noCall_ptr_code, noData_val, noData_val_code, noData_ref, noData_ref_code, noArg_list, noIndexing, noAssign, noPush_output, noFor, noFor_control, noFor_downto, noStep, noWhile, noWhile_control, noRepeat, noUntil, noIf, noThen, noElse, noExpression, noOperator, noUnary, noLabel, noId, noReal, noHex, noFrac, noExp, noString, noVector, noTry, noFinally, noExcept, noTry_statements, 
	noTry_upshot, noCase, noCase_expr, noCase_branch, noCase_test, noCase_match, noWith, noWith_Obj, noAs_Class };

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TatProcCollection* atProcCollection;
}	/* namespace Atpascal */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ATPASCAL)
using namespace Atpascal;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AtpascalHPP
