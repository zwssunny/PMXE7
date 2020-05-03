// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'atScript.pas' rev: 28.00 (Windows)

#ifndef AtscriptHPP
#define AtscriptHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <atParser.hpp>	// Pascal unit
#include <System.TypInfo.hpp>	// Pascal unit
#include <System.Math.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <System.Rtti.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Atscript
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TInstruction : unsigned char { inPrepare, inPushInteger, inPushDouble, inPushString, inPushConst, inPushOutput, inPushClass, inDuplicate, inDuplicate2, inDrop2, inSwap2, inOperNE, inOperGE, inOperLE, inOperEqual, inOperGreater, inOperLess, inOperAdd, inOperConcat, inOperSub, inOperOr, inOperXor, inOperMul, inOperSlash, inOperDiv, inOperMod, inOperAnd, inOperShl, inOperShr, inOperExp, inOperIs, inOperNeg, inOperNot, inJumpIfFalse, inJumpIfTrue, inJump, inStoreVar, inStoreVarRef, inStoreIdxVar, inStoreIdxVarRef, inStoreVarInteger, inStoreVarRefInteger, inStoreVarDouble, inStoreVarRefDouble, inStoreVarString, inStoreVarRefString, inStoreVarConst, inStoreVarRefConst, inCopyVar, inCopyVarRef, inStoreInput, inPushVar, inPushIdxVar, 
	inPushVarByRef, inVarTest, inVarTestInteger, inVarTestDouble, inVarTestString, inVarTestVar, inStoreGlobalVar, inStoreGlobalIdxVar, inPushGlobalVar, inPushGlobalIdxVar, inPushGlobalVarByRef, inCall, inRet, inExecFun, inCallProc, inTryFinally, inTryExcept, inCallClassProc, inBreakPoint, inAbort, inArrayOf, inCastClass, inWithObject, inGlobalPrepare, inTestIfFalse, inTestIfTrue };

typedef int *PInteger;

typedef bool *PBoolean;

typedef void * *PPointer;

typedef System::WideChar * *PPChar;

typedef void __fastcall (__closure *TGenericProc)(void);

typedef void __fastcall (__closure *TBuiltInProc)(const System::Variant &Input, System::Variant &Output);

struct TSimplifiedCode;
typedef TSimplifiedCode *pSimplifiedCode;

struct DECLSPEC_DRECORD TSimplifiedCode
{
public:
	TInstruction OpCode;
	System::Byte vByte;
	short vSmallInt;
	int vInteger;
	int vInteger1;
	System::UnicodeString vString;
	int vDebugInfo;
	TSimplifiedCode *Next;
	TGenericProc Compute;
	System::UnicodeString vString2;
	int Dummy;
	union
	{
		struct 
		{
			int vInteger2;
			int vInteger3;
		};
		struct 
		{
			TGenericProc vProc;
		};
		struct 
		{
			double vDouble;
		};
		
	};
};


typedef System::DynamicArray<int> intarray;

typedef void __fastcall (__closure *TSingleStepProc)(pSimplifiedCode p);

enum DECLSPEC_DENUM TStackType : unsigned char { stPendingOperators, stIdentifierList, stContext, stTempVariables };

struct TStackElement;
typedef TStackElement *pStackElement;

struct DECLSPEC_DRECORD TStackElement
{
public:
	TStackElement *Previous;
	System::Variant Element;
	int Index;
};


struct TAddress;
typedef TAddress *pAddress;

struct DECLSPEC_DRECORD TAddress
{
public:
	int Address;
	TSimplifiedCode *Code;
	TAddress *Next;
};


struct TLabelSpec;
typedef TLabelSpec *pLabelSpec;

struct DECLSPEC_DRECORD TLabelSpec
{
public:
	System::UnicodeString Name;
	int Address;
	TAddress *FirstRef;
	TAddress *LastRef;
	TLabelSpec *Next;
};


struct DECLSPEC_DRECORD TImplicitClassRef
{
public:
	int ClassIndex;
	int ElementIndex;
	bool ElementIsMethod;
	int ClassNameSize;
	int ElementNameSize;
	int ElementClassIndex;
	int ElementClassNameSize;
};


struct DECLSPEC_DRECORD TUsedUnitRec
{
public:
	int UnitNameSize;
	bool IsDefault;
	bool IsScript;
	int DeclSourcePos;
};


struct DECLSPEC_DRECORD TCodeFileHeader
{
public:
	System::StaticArray<System::WideChar, 25> Signature;
	System::Byte Version;
	int ImplicitRefCount;
	int UsedUnitCount;
	int ScriptInfoSize;
	System::StaticArray<System::Byte, 28> Reserved;
};


struct DECLSPEC_DRECORD TInstructionDetails
{
public:
	System::Byte OpCode;
	System::Byte vByte;
	short vSmallInt;
	int vDebugInfo;
	int vInteger;
	int vInteger1;
	int vInteger2;
	int vInteger3;
};


struct DECLSPEC_DRECORD TInstructionDescriptor
{
public:
	int Size;
	int Size2;
	TInstructionDetails Details;
};


enum DECLSPEC_DENUM TDataOperation : unsigned char { doRead, doWrite, doExec, doAddr };

enum DECLSPEC_DENUM TClassReference : unsigned char { crNone, crGetter, crSetter, crMethod };

class DELPHICLASS EatScripterRuntime;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatScripterRuntime : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatScripterRuntime(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatScripterRuntime(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatScripterRuntime(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatScripterRuntime(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScripterRuntime(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScripterRuntime(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatScripterRuntime(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatScripterRuntime(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScripterRuntime(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScripterRuntime(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScripterRuntime(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScripterRuntime(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatScripterRuntime(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatRuntimeError;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatRuntimeError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatRuntimeError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatRuntimeError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatRuntimeError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatRuntimeError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatRuntimeError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatRuntimeError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatRuntimeError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatRuntimeError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatRuntimeError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatRuntimeError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatRuntimeError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatRuntimeError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatRuntimeError(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatCompileError;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatCompileError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatCompileError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatCompileError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatCompileError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatCompileError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatCompileError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatCompileError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatCompileError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatCompileError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatCompileError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatCompileError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatCompileError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatCompileError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatCompileError(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatInternalError;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatInternalError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatInternalError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatInternalError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatInternalError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatInternalError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatInternalError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatInternalError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatInternalError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatInternalError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatInternalError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatInternalError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatInternalError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatInternalError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatInternalError(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatScriptInfoError;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatScriptInfoError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatScriptInfoError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatScriptInfoError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatScriptInfoError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatScriptInfoError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScriptInfoError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScriptInfoError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatScriptInfoError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatScriptInfoError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScriptInfoError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScriptInfoError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScriptInfoError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScriptInfoError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatScriptInfoError(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatDefinitionError;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatDefinitionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatDefinitionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatDefinitionError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatDefinitionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatDefinitionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatDefinitionError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatDefinitionError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatDefinitionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatDefinitionError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatDefinitionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatDefinitionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatDefinitionError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatDefinitionError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatDefinitionError(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatScripterFatal;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatScripterFatal : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatScripterFatal(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatScripterFatal(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatScripterFatal(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatScripterFatal(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScripterFatal(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScripterFatal(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatScripterFatal(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatScripterFatal(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScripterFatal(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScripterFatal(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScripterFatal(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScripterFatal(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatScripterFatal(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EatScripterDebug;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EatScripterDebug : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EatScripterDebug(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EatScripterDebug(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EatScripterDebug(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EatScripterDebug(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScripterDebug(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EatScripterDebug(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EatScripterDebug(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EatScripterDebug(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScripterDebug(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EatScripterDebug(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScripterDebug(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EatScripterDebug(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EatScripterDebug(void) { }
	
};

#pragma pack(pop)

typedef System::StaticArray<pSimplifiedCode, 1> TAddrVector;

typedef TAddrVector *pAddrVector;

enum DECLSPEC_DENUM CORE_CONST : unsigned char { coTrue, coFalse, coNull, coUnassigned, coNil };

enum DECLSPEC_DENUM TatCallingConvention : unsigned char { ccStdCall, ccRegister, ccPascal, ccCDecl, ccSafeCall };

typedef double *PReal;

typedef System::Comp *PComp;

typedef System::TMetaClass* TScriptFormClass;

typedef System::TMetaClass* TScriptBaseObjectClass;

typedef System::TMetaClass* TDispatcherClass;

enum DECLSPEC_DENUM TatEventPlacement : unsigned char { epReplaceCall, epTopCall, epBottomCall };

enum DECLSPEC_DENUM TEventSetMode : unsigned char { esReplaceEvent, esAddEventOnTop, esAddEventOnBottom };

enum DECLSPEC_DENUM TEventUnsetMode : unsigned char { euReplaceNil, euOriginalEvent, euClearEvent, euPreviousEvent };

class DELPHICLASS TatEventDispatcher;
typedef void __fastcall (__closure *TExecuteEventProc)(TatEventDispatcher* AEventDispatcher, bool &AExecute);

class DELPHICLASS TatCustomScripter;
typedef void __fastcall (__closure *TSettingEventProc)(System::TObject* Sender, System::TObject* AInstance, System::UnicodeString APropName, System::UnicodeString ARoutineName, TatCustomScripter* AScripter, TatEventPlacement APlacement, bool &AProcede);

typedef void __fastcall (__closure *TSetEventProc)(TatEventDispatcher* AEventDispatcher);

typedef void __fastcall (__closure *TUnsetEventProc)(TatEventDispatcher* AEventDispatcher, bool &AProcede);

class DELPHICLASS TatVirtualMachine;
typedef void __fastcall (__closure *TTranslateMethodGetterProc)(TatVirtualMachine* AMachine, System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, System::Variant &AValue);

typedef void __fastcall (__closure *TTranslateMethodSetterProc)(TatVirtualMachine* AMachine, System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, const System::Variant &AValue);

typedef System::TMetaClass* TScriptClass;

typedef System::TMetaClass* TMachineClass;

typedef System::TMetaClass* TatScripterLibraryClass;

enum DECLSPEC_DENUM TatArgumentModifier : unsigned char { moNone, moConst, moVar };

typedef System::Set<TatArgumentModifier, TatArgumentModifier::moNone, TatArgumentModifier::moVar> TatArgumentModifiers;

typedef void __fastcall (__closure *TScriptErrorEvent)(System::TObject* Sender, System::UnicodeString &msg, int row, int col, bool &ShowException);

typedef void __fastcall (__closure *TBeforeExecuteEvent)(TatVirtualMachine* AMachine, System::UnicodeString ALabel);

typedef void __fastcall (__closure *TMachineProc)(TatVirtualMachine* AMachine);

enum DECLSPEC_DENUM TatTypeKind : unsigned char { tkNone, tkInteger, tkChar, tkEnumeration, tkFloat, tkString, tkSet, tkClass, tkMethod, tkWChar, tkLString, tkWString, tkVariant, tkArray, tkRecord, tkInterface, tkInt64, tkDynArray, tkUString };

enum DECLSPEC_DENUM TWatchStatus : unsigned char { wsNotEvaluated, wsEvaluated, wsCompileError, wsRuntimeError, wsProcessNotAvailable };

typedef System::Set<System::Typinfo::TMemberVisibility, System::Typinfo::TMemberVisibility::mvPrivate, System::Typinfo::TMemberVisibility::mvPublished> TMemberVisibilitySet;

enum DECLSPEC_DENUM TRedefineOption : unsigned char { roNone, roInclude, roOverwrite };

class DELPHICLASS TScripterLibraryOptions;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TScripterLibraryOptions : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FUseScriptFiles;
	System::UnicodeString FCompiledFileExt;
	System::UnicodeString FSourceFileExt;
	System::UnicodeString FFormFileExt;
	System::Classes::TStrings* FSearchPath;
	void __fastcall SetSearchPath(System::Classes::TStrings* const Value);
	
public:
	__fastcall TScripterLibraryOptions(void);
	__fastcall virtual ~TScripterLibraryOptions(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Classes::TStrings* SearchPath = {read=FSearchPath, write=SetSearchPath};
	__property System::UnicodeString SourceFileExt = {read=FSourceFileExt, write=FSourceFileExt};
	__property System::UnicodeString CompiledFileExt = {read=FCompiledFileExt, write=FCompiledFileExt};
	__property System::UnicodeString FormFileExt = {read=FFormFileExt, write=FFormFileExt};
	__property bool UseScriptFiles = {read=FUseScriptFiles, write=FUseScriptFiles, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TatClass;
struct DECLSPEC_DRECORD TElementContext
{
public:
	bool HasArgList;
	bool HasUpnode;
	bool HasSubNode;
	bool IsNewClause;
	TDataOperation Operation;
	int ArgCount;
	int IdxCount;
	bool RepeatChecking;
	System::UnicodeString ElementName;
	TatClass* CurrentClass;
};


typedef void __fastcall (__closure *TUnknownElementEvent)(System::TObject* Sender, TElementContext &Context);

class DELPHICLASS TatScripts;
class DELPHICLASS TatScript;
class DELPHICLASS TatObjects;
class DELPHICLASS TatClasses;
class DELPHICLASS TatObject;
class DELPHICLASS TatScripterEventBroker;
class DELPHICLASS TatScripterWatches;
class DELPHICLASS TatScriptBreakPoints;
class DELPHICLASS TatScriptInfo;
class DELPHICLASS TatScripterLibrary;
class DELPHICLASS TatProperty;
class DELPHICLASS TatMethod;
class PASCALIMPLEMENTATION TatCustomScripter : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FDeferObjectResolution;
	TScriptClass FScriptClass;
	TMachineClass FMachineClass;
	System::Typinfo::TTypeKinds FTypeInfoFilter;
	TatScripts* FScripts;
	TatScript* FCurrentScript;
	TatObjects* FDefaultInstances;
	TatClasses* FClasses;
	System::Classes::TList* FLibInstances;
	TatObject* FInternalInstance;
	System::Classes::TMemoryStream* FPCode;
	bool FOptionExplicit;
	TScriptErrorEvent FOnCompileError;
	TScriptErrorEvent FOnRuntimeError;
	TBeforeExecuteEvent FOnBeforeExecute;
	TTranslateMethodGetterProc FOnTranslateMethodGetter;
	TTranslateMethodSetterProc FOnTranslateMethodSetter;
	bool FEventSupport;
	TEventSetMode FEventSetMode;
	TEventUnsetMode FEventUnsetMode;
	TatScripterEventBroker* FEventBroker;
	System::Classes::TList* FLoadedScripts;
	bool FShortBooleanEval;
	bool FSaveCompiledCode;
	TScripterLibraryOptions* FLibOptions;
	bool FAllowDLLCalls;
	TUnknownElementEvent FOnUnknownElement;
	System::Classes::TNotifyEvent FOnRunningChanged;
	System::Classes::TNotifyEvent FOnDebugHook;
	System::Classes::TNotifyEvent FOnSingleDebugHook;
	bool FLastRunning;
	System::Classes::TNotifyEvent FOnBreakpointStop;
	TatScripterWatches* FWatches;
	TScriptFormClass FScriptFormClass;
	TScriptBaseObjectClass FScriptBaseObjectClass;
	bool FLoadFormEvents;
	void __fastcall ReadPCodeProp(System::Classes::TStream* Stream);
	void __fastcall WritePCodeProp(System::Classes::TStream* Stream);
	bool __fastcall PCodeEquals(System::Classes::TStream* pcode);
	TatScriptBreakPoints* __fastcall GetBreakPoints(void);
	bool __fastcall GetCompiled(void);
	System::TObject* __fastcall GetCurrentObject(void);
	TatClass* __fastcall GetCurrentClass(void);
	pSimplifiedCode __fastcall GetFirstInstruction(void);
	bool __fastcall GetHalted(void);
	System::UnicodeString __fastcall GetLastExceptionClassName(void);
	int __fastcall GetLastExceptionHelpContext(void);
	System::UnicodeString __fastcall GetLastExceptionMessage(void);
	pSimplifiedCode __fastcall GetNextInstruction(void);
	System::Classes::TNotifyEvent __fastcall GetOnExecHook(void);
	System::Classes::TNotifyEvent __fastcall GetOnPauseChanged(void);
	bool __fastcall GetPaused(void);
	bool __fastcall GetRunning(void);
	System::Classes::TStrings* __fastcall GetSourceCode(void);
	void __fastcall SetCompiled(const bool Value);
	void __fastcall SetOnExecHook(const System::Classes::TNotifyEvent Value);
	void __fastcall SetOnPauseChanged(const System::Classes::TNotifyEvent Value);
	void __fastcall SetPaused(const bool Value);
	void __fastcall SetRunning(const bool Value);
	void __fastcall SetSourceCode(System::Classes::TStrings* const Value);
	void __fastcall CreateLibraries(void);
	void __fastcall SetClasses(TatClasses* const Value);
	TatScriptInfo* __fastcall GetScriptInfo(void);
	void __fastcall SetEventSetMode(const TEventSetMode Value);
	void __fastcall SetEventSupport(const bool Value);
	void __fastcall SetEventUnsetMode(const TEventUnsetMode Value);
	void __fastcall TranslateMethodGetter(TatVirtualMachine* AMachine, System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, System::Variant &AValue);
	void __fastcall TranslateMethodSetter(TatVirtualMachine* AMachine, System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, const System::Variant &AValue);
	TExecuteEventProc __fastcall GetOnExecuteEvent(void);
	TSetEventProc __fastcall GetOnSetEvent(void);
	TSettingEventProc __fastcall GetOnSettingEvent(void);
	TUnsetEventProc __fastcall GetOnUnsettingEvent(void);
	void __fastcall SetOnExecuteEvent(const TExecuteEventProc Value);
	void __fastcall SetOnSetEvent(const TSetEventProc Value);
	void __fastcall SetOnSettingEvent(const TSettingEventProc Value);
	void __fastcall SetOnUnsettingEvent(const TUnsetEventProc Value);
	void __fastcall FreeLibInstances(void);
	void __fastcall InternalCompileError(System::UnicodeString msg, int debuginfo, TatScript* AScript)/* overload */;
	void __fastcall InternalCompileError(System::UnicodeString msg, int row, int col, TatScript* AScript)/* overload */;
	void __fastcall InternalRuntimeError(System::UnicodeString msg, TatScript* AScript);
	void __fastcall SetOnBeforeExecute(const TBeforeExecuteEvent Value);
	bool __fastcall GetSilentCompiled(void);
	void __fastcall SetSilentCompiled(const bool Value);
	bool __fastcall DoSaveCompiledCode(void);
	System::UnicodeString __fastcall FindFileInSearchPath(const System::UnicodeString CompName, const System::UnicodeString SrcName);
	System::UnicodeString __fastcall FindScriptFile(System::UnicodeString AName);
	bool __fastcall IsFileRegisteredAsLibrary(System::UnicodeString AFileName, TatScripterLibrary* &ALib);
	void __fastcall SetLibOptions(TScripterLibraryOptions* const Value);
	bool __fastcall GetCallExecHookEvent(void);
	void __fastcall SetCallExecHookEvent(const bool Value);
	System::UnicodeString __fastcall FindFormFile(System::UnicodeString AName);
	void __fastcall ScriptBaseObjectCreateProc(TatVirtualMachine* AMachine);
	void __fastcall ScriptFormCreateProc(TatVirtualMachine* AMachine);
	void __fastcall ComponentCreateProc(TatVirtualMachine* AMachine);
	void __fastcall CheckRunningChanged(TatVirtualMachine* AMachine);
	bool __fastcall IsAnyRunning(void);
	TatScript* __fastcall GetCurrentDebugScript(void);
	void __fastcall SetScriptFormClass(const TScriptFormClass Value);
	void __fastcall SetScriptBaseObjectClass(const TScriptBaseObjectClass Value);
	System::TClass __fastcall ScrClassType(System::Rtti::TRttiType* AType);
	System::Rtti::TValue __fastcall ScrPrepareValue(System::Rtti::TRttiType* AType, const System::Variant &AValue);
	TatTypeKind __fastcall ScrTypeKind(System::Rtti::TRttiType* AType);
	void __fastcall GenericMethodMachineProc(TatVirtualMachine* AMachine);
	void __fastcall GenericPropGetterMachineProc(TatVirtualMachine* AMachine);
	void __fastcall GenericPropSetterMachineProc(TatVirtualMachine* AMachine);
	void __fastcall GenericFieldGetterMachineProc(TatVirtualMachine* AMachine);
	void __fastcall GenericFieldSetterMachineProc(TatVirtualMachine* AMachine);
	void __fastcall GenericRecordFieldGetterMachineProc(TatVirtualMachine* AMachine);
	void __fastcall GenericRecordFieldSetterMachineProc(TatVirtualMachine* AMachine);
	void __fastcall RecordCreateProc(TatVirtualMachine* AMachine);
	void __fastcall RecordFreeProc(TatVirtualMachine* AMachine);
	
protected:
	virtual void __fastcall DoCompileError(System::UnicodeString msg, int row, int col, bool &AShow, TatScript* AScript);
	virtual void __fastcall Loaded(void);
	void __fastcall DoUnknownElement(TElementContext &Context);
	void __fastcall BeforeExecute(TatVirtualMachine* AMachine, System::UnicodeString ALabel);
	virtual void __fastcall DefineInternalClasses(void);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall BeforeCompile(void);
	virtual void __fastcall BeforeLoadCode(void);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DoRunningChanged(TatVirtualMachine* AMachine);
	virtual bool __fastcall DoDebugHook(TatVirtualMachine* AMachine);
	virtual void __fastcall SingleDebugHook(TatVirtualMachine* AMachine);
	virtual void __fastcall SourceCodeChanged(TatScript* AScript);
	virtual TScriptClass __fastcall DefaultScriptClass(void);
	virtual void __fastcall DoBreakpointStop(void);
	__property TScriptClass ScriptClass = {read=FScriptClass, write=FScriptClass};
	__property TMachineClass MachineClass = {read=FMachineClass, write=FMachineClass};
	__property TTranslateMethodGetterProc OnTranslateMethodGetter = {read=FOnTranslateMethodGetter, write=FOnTranslateMethodGetter};
	__property TTranslateMethodSetterProc OnTranslateMethodSetter = {read=FOnTranslateMethodSetter, write=FOnTranslateMethodSetter};
	__property bool EventSupport = {read=FEventSupport, write=SetEventSupport, default=1};
	__property TEventSetMode EventSetMode = {read=FEventSetMode, write=SetEventSetMode, default=0};
	__property TEventUnsetMode EventUnsetMode = {read=FEventUnsetMode, write=SetEventUnsetMode, default=0};
	__property TExecuteEventProc OnExecuteEvent = {read=GetOnExecuteEvent, write=SetOnExecuteEvent};
	__property TSettingEventProc OnSettingEvent = {read=GetOnSettingEvent, write=SetOnSettingEvent};
	__property TSetEventProc OnSetEvent = {read=GetOnSetEvent, write=SetOnSetEvent};
	__property TUnsetEventProc OnUnsettingEvent = {read=GetOnUnsettingEvent, write=SetOnUnsettingEvent};
	
public:
	__fastcall virtual TatCustomScripter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TatCustomScripter(void);
	virtual void __fastcall Clear(void);
	void __fastcall LoadCodeFromFile(System::UnicodeString AFileName);
	void __fastcall SaveCodeToFile(System::UnicodeString AFileName);
	void __fastcall LoadCodeFromStream(System::Classes::TStream* AStream);
	void __fastcall SaveCodeToStream(System::Classes::TStream* AStream);
	void __fastcall AddFunction(System::UnicodeString Name, TBuiltInProc Address);
	virtual void __fastcall Compile(void);
	void __fastcall SilentCompile(void);
	virtual System::Variant __fastcall Execute(void)/* overload */;
	virtual System::Variant __fastcall Execute(const System::Variant &input)/* overload */;
	System::Variant __fastcall ExecuteSubroutine(System::UnicodeString ALabel, const System::Variant &input)/* overload */;
	System::Variant __fastcall ExecuteSubroutine(System::UnicodeString ALabel)/* overload */;
	System::Variant __fastcall ExecuteSubroutine(System::UnicodeString ALabel, System::TVarRec *input, const int input_High)/* overload */;
	System::Variant __fastcall GetArrayIndex(int ADim);
	int __fastcall InputArgCount(void);
	System::Variant __fastcall GetInputArg(int AIndex);
	System::UnicodeString __fastcall GetInputArgAsString(int AIndex);
	System::TClass __fastcall GetInputArgAsClass(int AIndex);
	System::WideString __fastcall GetInputArgAsWideString(int AIndex);
	int __fastcall GetInputArgAsInteger(int AIndex);
	__int64 __fastcall GetInputArgAsInt64(int AIndex);
	bool __fastcall GetInputArgAsBoolean(int AIndex);
	double __fastcall GetInputArgAsFloat(int AIndex);
	System::TDateTime __fastcall GetInputArgAsDateTime(int AIndex);
	void __fastcall SetInputArg(int AIndex, const System::Variant &AValue);
	void __fastcall SetInputArgIfByRef(int AIndex, const System::Variant &AValue);
	void __fastcall ReturnOutputArg(const System::Variant &AValue);
	void __fastcall GetRowColFromSource(int APos, int &row, int &col);
	void __fastcall SolveAbsoluteAddressing(void);
	void __fastcall Halt(void);
	pSimplifiedCode __fastcall InstructionByLine(int ARow);
	pSimplifiedCode __fastcall EntryPoint(System::UnicodeString ALabel);
	void __fastcall DebugTraceInto(void);
	void __fastcall DebugStepOver(void);
	void __fastcall DebugTraceIntoLine(void);
	void __fastcall DebugStepOverLine(void);
	void __fastcall DebugRunUntilReturn(void);
	void __fastcall DebugRunToPoint(pSimplifiedCode AInstruction);
	void __fastcall DebugRunToLine(int ALine);
	bool __fastcall DebugToggleBreakPoint(pSimplifiedCode AInstruction);
	pSimplifiedCode __fastcall DebugToggleBreakLine(int ALine);
	int __fastcall DebugExecutionLine(void);
	bool __fastcall ExpandedDebugInfo(void);
	void __fastcall ExpandDebugInfo(bool RequiresCompilation = true);
	TatClass* __fastcall ClassByName(System::UnicodeString AName);
	TatClass* __fastcall AddClass(System::UnicodeString AName, System::UnicodeString AAncestorName);
	TatClass* __fastcall AddDelphiClass(System::TClass AClass);
	TatClass* __fastcall DefineClass(System::TClass AClass, System::UnicodeString AClassName = System::UnicodeString());
	TatClass* __fastcall DefineRecord(System::Typinfo::PTypeInfo ATypeInfo, System::UnicodeString ARecordName = System::UnicodeString());
	void __fastcall AddComponent(System::Classes::TComponent* AComp);
	void __fastcall AddComponents(System::Classes::TComponent* AComp);
	TatClass* __fastcall DefineFormClass(Vcl::Forms::TCustomForm* AForm, System::UnicodeString AFormClassName = System::UnicodeString());
	void __fastcall AddForm(Vcl::Forms::TCustomForm* AForm, System::UnicodeString AFormClassName = System::UnicodeString());
	void __fastcall AddDataModule(System::Classes::TDataModule* ADataModule, System::UnicodeString ADataModuleClassName = System::UnicodeString());
	void __fastcall AddObject(System::UnicodeString AName, System::TObject* AObject);
	void __fastcall AddConstant(System::UnicodeString AName, const System::Variant &AValue);
	void __fastcall AddVariable(System::UnicodeString AName, System::Variant &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, System::Extended &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, double &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, System::UnicodeString &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, System::WideString &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, int &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, bool &AVar)/* overload */;
	void __fastcall AddEnumeration(System::Typinfo::PTypeInfo ATypeInfo);
	TatProperty* __fastcall DefineProp(System::UnicodeString AName, TatTypeKind ADataType, TMachineProc AGetter, TMachineProc ASetter, System::TClass APropertyClass = 0x0, bool AIsClassProp = false, int AIndexCount = 0x0);
	TatMethod* __fastcall DefineMethod(System::UnicodeString AName, int AArgCount, TatTypeKind AResultDataType, System::TClass AResultClass, TMachineProc AProc, bool AIsClassMethod = false, int ADefArgCount = 0x0, System::UnicodeString AParameterHints = System::UnicodeString());
	TatClass* __fastcall UsesObject(System::TObject* AObject, System::UnicodeString AName = System::UnicodeString(), System::UnicodeString AClassName = System::UnicodeString());
	void __fastcall AddLibraryInstance(TatScripterLibrary* ALibrary, System::UnicodeString AName, bool ADefault = true, bool AddMethod = true, System::UnicodeString LibName = System::UnicodeString());
	void __fastcall RemoveLibraryInstance(TatScripterLibrary* ALibrary, System::UnicodeString AName);
	TatScripterLibrary* __fastcall AddLibrary(TatScripterLibraryClass ALibraryClass, bool ADefault = true);
	TatScripterLibrary* __fastcall FindLibraryByClass(TatScripterLibraryClass ALibraryClass);
	TatScripterLibrary* __fastcall LoadLibrary(System::UnicodeString ALibraryName, bool ADefault = true, bool ASilent = false);
	void __fastcall LoadLibrary2(System::UnicodeString ALibraryName, bool ADefault = true);
	void __fastcall AssignInfo(TatCustomScripter* ASourceScripter);
	bool __fastcall InProcessExecute(System::UnicodeString AScriptStub);
	System::UnicodeString __fastcall BuildEventHandlerName(System::Classes::TComponent* Instance, System::UnicodeString PropName);
	int __fastcall DeclareEventHandler(System::UnicodeString AProcName);
	void __fastcall GetInfoFromRoutineName(System::UnicodeString &RName, TatVirtualMachine* &AMachine);
	void __fastcall DefineClassByRTTI(System::TClass AClass, System::UnicodeString AClassName = System::UnicodeString(), TMemberVisibilitySet AVisibilityFilter = (TMemberVisibilitySet() << System::Typinfo::TMemberVisibility::mvPublic << System::Typinfo::TMemberVisibility::mvPublished ), bool ARecursive = false, TRedefineOption ARedefine = (TRedefineOption)(0x0));
	void __fastcall DefineRecordByRTTI(void * ATypeInfo);
	__property TatScripterEventBroker* EventBroker = {read=FEventBroker};
	__property TatObjects* DefaultInstances = {read=FDefaultInstances};
	__property TatClasses* Classes = {read=FClasses, write=SetClasses};
	TatClass* __fastcall SystemLibrary(void);
	__property System::Classes::TStrings* SourceCode = {read=GetSourceCode, write=SetSourceCode};
	__property System::UnicodeString LastExceptionMessage = {read=GetLastExceptionMessage};
	__property int LastExceptionHelpContext = {read=GetLastExceptionHelpContext, nodefault};
	__property System::UnicodeString LastExceptionClassName = {read=GetLastExceptionClassName};
	__property TatScriptInfo* ScriptInfo = {read=GetScriptInfo};
	__property System::TObject* CurrentObject = {read=GetCurrentObject};
	__property TatClass* CurrentClass = {read=GetCurrentClass};
	__property bool Compiled = {read=GetCompiled, write=SetCompiled, stored=DoSaveCompiledCode, nodefault};
	__property bool SaveCompiledCode = {read=FSaveCompiledCode, write=FSaveCompiledCode, nodefault};
	__property bool SilentCompiled = {read=GetSilentCompiled, write=SetSilentCompiled, nodefault};
	__property System::Classes::TMemoryStream* PCode = {read=FPCode, write=FPCode};
	__property TatScriptBreakPoints* BreakPoints = {read=GetBreakPoints};
	__property bool Halted = {read=GetHalted, nodefault};
	__property bool Running = {read=GetRunning, write=SetRunning, nodefault};
	__property bool Paused = {read=GetPaused, write=SetPaused, nodefault};
	__property bool CallExecHookEvent = {read=GetCallExecHookEvent, write=SetCallExecHookEvent, nodefault};
	__property pSimplifiedCode FirstInstruction = {read=GetFirstInstruction};
	__property System::Classes::TNotifyEvent OnDebugHook = {read=FOnDebugHook, write=FOnDebugHook};
	__property System::Classes::TNotifyEvent OnSingleDebugHook = {read=FOnSingleDebugHook, write=FOnSingleDebugHook};
	__property System::Classes::TNotifyEvent OnExecHook = {read=GetOnExecHook, write=SetOnExecHook};
	__property System::Classes::TNotifyEvent OnPauseChanged = {read=GetOnPauseChanged, write=SetOnPauseChanged};
	__property System::Classes::TNotifyEvent OnRunningChanged = {read=FOnRunningChanged, write=FOnRunningChanged};
	__property pSimplifiedCode NextInstruction = {read=GetNextInstruction};
	__property TatScript* CurrentScript = {read=FCurrentScript, write=FCurrentScript};
	__property TatScript* CurrentDebugScript = {read=GetCurrentDebugScript};
	__property TScriptFormClass ScriptFormClass = {read=FScriptFormClass, write=SetScriptFormClass};
	__property TScriptBaseObjectClass ScriptBaseObjectClass = {read=FScriptBaseObjectClass, write=SetScriptBaseObjectClass};
	__property TatScripts* Scripts = {read=FScripts};
	__property bool OptionExplicit = {read=FOptionExplicit, write=FOptionExplicit, nodefault};
	__property TatScripterWatches* Watches = {read=FWatches};
	__property TScriptErrorEvent OnCompileError = {read=FOnCompileError, write=FOnCompileError};
	__property TScriptErrorEvent OnRuntimeError = {read=FOnRuntimeError, write=FOnRuntimeError};
	__property bool DeferObjectResolution = {read=FDeferObjectResolution, write=FDeferObjectResolution, nodefault};
	__property TBeforeExecuteEvent OnBeforeExecute = {read=FOnBeforeExecute, write=SetOnBeforeExecute};
	__property bool ShortBooleanEval = {read=FShortBooleanEval, write=FShortBooleanEval, nodefault};
	__property bool AllowDLLCalls = {read=FAllowDLLCalls, write=FAllowDLLCalls, nodefault};
	__property TScripterLibraryOptions* LibOptions = {read=FLibOptions, write=SetLibOptions};
	__property TUnknownElementEvent OnUnknownElement = {read=FOnUnknownElement, write=FOnUnknownElement};
	__property bool LoadFormEvents = {read=FLoadFormEvents, write=FLoadFormEvents, nodefault};
	__property System::Classes::TNotifyEvent OnBreakpointStop = {read=FOnBreakpointStop, write=FOnBreakpointStop};
};


class DELPHICLASS TatScripterWatch;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScripterWatches : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatScripterWatch* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatScripterWatch* __fastcall GetItem(int i);
	TatCustomScripter* __fastcall Scripter(void);
	
public:
	HIDESBASE TatScripterWatch* __fastcall Add(void);
	__property TatScripterWatch* Items[int i] = {read=GetItem/*, default*/};
	void __fastcall EvaluateAll(void);
public:
	/* TOwnedCollection.Create */ inline __fastcall TatScripterWatches(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatScripterWatches(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TatScripterWatch : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FExpression;
	TatScript* FDebugScript;
	bool FEnabled;
	TWatchStatus FWatchStatus;
	System::Variant FLastResult;
	void __fastcall SetExpression(const System::UnicodeString Value);
	void __fastcall ScriptDestroyed(System::TObject* Sender);
	TatScripterWatches* __fastcall Watches(void);
	TatCustomScripter* __fastcall Scripter(void);
	void __fastcall Reset(void);
	void __fastcall InternalEvaluate(TatVirtualMachine* AMachine);
	
public:
	__fastcall virtual TatScripterWatch(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatScripterWatch(void);
	void __fastcall Evaluate(void);
	__property System::UnicodeString Expression = {read=FExpression, write=SetExpression};
	__property TWatchStatus WatchStatus = {read=FWatchStatus, nodefault};
	__property System::Variant LastResult = {read=FLastResult};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScripts : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatScript* operator[](int i) { return Items[i]; }
	
private:
	TatCustomScripter* FScripter;
	HIDESBASE TatScript* __fastcall GetItem(int i);
	
public:
	__fastcall TatScripts(TatCustomScripter* AScripter);
	HIDESBASE TatScript* __fastcall Add(void);
	TatScript* __fastcall FindByUnitName(System::UnicodeString AUnitName);
	__property TatScript* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatScripts(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TScriptBaseObject;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TScriptBaseObject : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FDestroying;
	TatScript* FRunScript;
	void __fastcall NewObjectInstance(TatVirtualMachine* AMachine);
	
protected:
	__property TatScript* RunScript = {read=FRunScript, write=FRunScript};
	
public:
	__fastcall virtual ~TScriptBaseObject(void);
	virtual void __fastcall BeforeDestruction(void);
	__fastcall virtual TScriptBaseObject(TatVirtualMachine* AMachine);
public:
	/* TObject.Create */ inline __fastcall TScriptBaseObject(void) : System::Classes::TPersistent() { }
	
};

#pragma pack(pop)

class DELPHICLASS TScriptForm;
class PASCALIMPLEMENTATION TScriptForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
private:
	TatScript* FRunScript;
	TatScript* FDesignScript;
	System::Classes::TStrings* FSaveProps;
	System::Classes::TStrings* FSaveEvents;
	System::UnicodeString FLastSearchedMethod;
	void __fastcall LoadFormResource(System::UnicodeString AFormRes, bool ALoadEvents);
	void __fastcall NewFormInstance(TatVirtualMachine* AMachine);
	void __fastcall RestoreSavedProps(void);
	void __fastcall SetSaveProps(System::Classes::TStrings* const Value);
	void __fastcall SetSaveEvents(System::Classes::TStrings* const Value);
	void __fastcall RestoreSavedEvents(void);
	void __fastcall ReaderFindMethod(System::Classes::TReader* Reader, const System::UnicodeString MethodName, void * &Address, bool &Error);
	void __fastcall ReaderError(System::Classes::TReader* Reader, const System::UnicodeString Message, bool &Handled);
	
protected:
	__property TatScript* RunScript = {read=FRunScript, write=FRunScript};
	
public:
	__fastcall virtual TScriptForm(System::Classes::TComponent* AOwner);
	__fastcall virtual TScriptForm(System::Classes::TComponent* AOwner, int Dummy);
	__fastcall virtual TScriptForm(System::Classes::TComponent* AOwner, TatVirtualMachine* AMachine);
	__fastcall virtual ~TScriptForm(void);
	DYNAMIC bool __fastcall IsShortCut(Winapi::Messages::TWMKey &Message);
	__property TatScript* DesignScript = {read=FDesignScript, write=FDesignScript};
	
__published:
	__property System::Classes::TStrings* SaveProps = {read=FSaveProps, write=SetSaveProps};
	__property System::Classes::TStrings* SaveEvents = {read=FSaveEvents, write=SetSaveEvents};
	__property Visible = {stored=false, default=0};
	__property Left = {stored=false};
	__property Top = {stored=false};
	__property WindowState = {stored=false, default=0};
	__property Align = {stored=false, default=0};
	__property AutoSize = {stored=false, default=0};
	__property Enabled = {stored=false, default=1};
	__property FormStyle = {stored=false, default=0};
	__property KeyPreview = {stored=false, default=0};
	__property BorderStyle = {stored=false, default=2};
	__property ActiveControl = {stored=false};
public:
	/* TWinControl.CreateParented */ inline __fastcall TScriptForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


class DELPHICLASS TatScriptRefactor;
class DELPHICLASS TatRoutineInfo;
class DELPHICLASS TatVariableInfo;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScriptRefactor : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TatScript* FScript;
	bool FDirtySource;
	System::UnicodeString FUpcaseSource;
	System::Classes::TStrings* __fastcall GetSource(void);
	System::UnicodeString __fastcall GetUpcaseSource(void);
	
protected:
	virtual System::UnicodeString __fastcall BuildMethodHint(TatMethod* meth);
	virtual System::UnicodeString __fastcall BuildRoutineHint(TatRoutineInfo* routine);
	virtual System::UnicodeString __fastcall BuildPropertyHint(TatProperty* prop);
	virtual System::UnicodeString __fastcall BuildVariableHint(TatVariableInfo* avar);
	virtual bool __fastcall IsStatementEndChar(System::WideChar ch) = 0 ;
	virtual bool __fastcall IsQualifiedIdentifierChar(System::WideChar ch);
	__property System::Classes::TStrings* Source = {read=GetSource};
	__property System::UnicodeString UpcaseSource = {read=GetUpcaseSource};
	int __fastcall SourcePos(System::UnicodeString SubStr, int FromPos = 0x1);
	
public:
	__fastcall TatScriptRefactor(TatScript* AScript);
	void __fastcall BeginRefactor(void);
	void __fastcall EndRefactor(void);
	virtual void __fastcall UpdateFormHeader(System::UnicodeString AFormClass, System::UnicodeString AFileName);
	int __fastcall DeclareRoutine(System::UnicodeString ProcName)/* overload */;
	virtual int __fastcall DeclareRoutine(TatRoutineInfo* AInfo)/* overload */;
	virtual void __fastcall AddUsedUnit(System::UnicodeString AUnitName);
	__property TatScript* Script = {read=FScript};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TatScriptRefactor(void) { }
	
};

#pragma pack(pop)

typedef System::TMetaClass* TRefactorClass;

class DELPHICLASS TatScriptBreak;
class DELPHICLASS TatScriptBreakPoint;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScriptBreak : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	int FLine;
	System::Contnrs::TObjectList* FBreakList;
	bool FAutoDestroy;
	TatScript* __fastcall Script(void);
	void __fastcall SetLine(const int Value);
	void __fastcall UpdateBreakPoints(void);
	void __fastcall BreakpointDestroyed(TatScriptBreakPoint* ABreakPoint);
	void __fastcall RemoveBreakPoints(void);
	void __fastcall TemporaryBreakProc(void);
	
public:
	__fastcall virtual TatScriptBreak(System::Classes::TCollection* Collection);
	__fastcall virtual ~TatScriptBreak(void);
	__property int Line = {read=FLine, write=SetLine, nodefault};
	__property bool AutoDestroy = {read=FAutoDestroy, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TatScriptBreaks;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScriptBreaks : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatScriptBreak* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TatScriptBreak* __fastcall GetItem(int Index);
	TatScript* __fastcall Script(void);
	void __fastcall UpdateAll(void);
	
public:
	void __fastcall ToggleBreak(int ALine);
	TatScriptBreak* __fastcall FindByLine(int ALine);
	HIDESBASE TatScriptBreak* __fastcall Add(void);
	__property TatScriptBreak* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TatScriptBreaks(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatScriptBreaks(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatVirtualMachines;
class DELPHICLASS TatUsedUnits;
class PASCALIMPLEMENTATION TatScript : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatCustomScripter* FScripter;
	Atparser::TatSyntaxParser* FParser;
	TatVirtualMachines* FVirtualMachines;
	TatVirtualMachine* FVirtualMachine;
	System::StaticArray<pStackElement, 4> FStack;
	int FCodeLine;
	TLabelSpec *FFirstLabelSpec;
	TLabelSpec *FLastLabelSpec;
	TatRoutineInfo* FCurrentRoutine;
	bool FIsDebugScript;
	TatRoutineInfo* FDebugScriptMainRoutine;
	System::Classes::TStrings* FSourceCode;
	TSimplifiedCode *FFirstInstruction;
	TSimplifiedCode *FLastInstruction;
	TatScriptInfo* FScriptInfo;
	bool FCompiled;
	bool FSilentCompiled;
	bool FSolvedAddressing;
	bool FExpandedDebugInfo;
	TatUsedUnits* FUsedUnits;
	int FCounterInit;
	System::Classes::TNotifyEvent FOnDestroy;
	bool FRollbackSourceCode;
	System::Classes::TList* FLibraries;
	bool FSilentCompilation;
	System::UnicodeString FFileName;
	System::UnicodeString FUnitName;
	bool FLoadedDLL;
	TatObjects* FDefInstances;
	TatObject* FIntInstance;
	TScriptForm* FScriptForm;
	TatScriptRefactor* FRefactor;
	TRefactorClass FRefactorClass;
	TScriptForm* FDesignScriptForm;
	System::UnicodeString FDesignFormResource;
	System::Classes::TStream* FCodeStream;
	TatScriptBreaks* FBreaks;
	TatScript* FOriginalScript;
	System::Contnrs::TObjectList* FDerivedScripts;
	bool FCompiling;
	TScriptForm* FOriginalForm;
	TScriptBaseObject* FOriginalObject;
	bool FClearingScript;
	int FRefactoring;
	void __fastcall InternalCompile(bool Silent);
	void __fastcall DisposeDLL(void);
	void __fastcall RemoveAttachedEvents(bool RemoveAll);
	System::UnicodeString __fastcall GetFormFileAsString(System::UnicodeString AFormFile);
	void __fastcall InternalSaveCodeToStream(System::Classes::TStream* AStream);
	void __fastcall SetCompiled(const bool Value);
	bool __fastcall CheckRegisteredAsLibrary(TatCustomScripter* AScripter, TatScripterLibrary* &ALib);
	void __fastcall SetOriginalScript(TatScript* AScript);
	void __fastcall DoBreakpointStop(void);
	TatClass* __fastcall _FindClass(int idx, System::UnicodeString AName);
	TatMethod* __fastcall _FindMethod(TatClass* AClass, int idx, System::UnicodeString AName);
	TatProperty* __fastcall _FindProperty(TatClass* AClass, int idx, System::UnicodeString AName);
	void __fastcall InternalLoadCodeFromStream(System::Classes::TStream* AStream, bool AUseBehavior);
	void __fastcall GetRowColFromInst(pSimplifiedCode Inst, int &Row, int &Col);
	TatProperty* __fastcall DefineProp(System::UnicodeString AName, TatTypeKind ADataType, TMachineProc AGetter, TMachineProc ASetter, System::TClass APropertyClass = 0x0, bool AIsClassProp = false, int AIndexCount = 0x0);
	void __fastcall GetSelfBaseObjectProc(TatVirtualMachine* AMachine);
	
protected:
	void __fastcall DoUnknownElement(TElementContext &Context);
	void __fastcall CompileError(System::UnicodeString msg, int debuginfo)/* overload */;
	void __fastcall CompileError(System::UnicodeString msg, int row, int col)/* overload */;
	void __fastcall RuntimeError(System::UnicodeString msg);
	void __fastcall StackPush(TStackType StackType, const System::Variant &x);
	void __fastcall StackPushDelimitter(TStackType StackType);
	bool __fastcall EmptyStack(TStackType StackType);
	System::Variant __fastcall StackPop(TStackType StackType);
	System::Variant __fastcall StackView(TStackType StackType);
	int __fastcall StackIndex(TStackType StackType);
	bool __fastcall StackDelimitterFound(TStackType StackType);
	System::Variant __fastcall StackGetByIndex(TStackType st, int i);
	int __fastcall IndexOfStackTextValue(TStackType st, System::UnicodeString s);
	pStackElement __fastcall GetStack(TStackType st);
	void __fastcall ClearStacks(void);
	pLabelSpec __fastcall NewLabelSpec(System::UnicodeString Name);
	pLabelSpec __fastcall FindLabelSpec(System::UnicodeString name);
	int __fastcall RegisterReference(System::UnicodeString Name);
	void __fastcall SolveReference(pLabelSpec LabelSpec);
	void __fastcall DefineReferenceAddress(System::UnicodeString Name);
	void __fastcall ClearLabelSpecs(void);
	void __fastcall SolveUndefinedReferences(void);
	TatVariableInfo* __fastcall RegisterVariableReference(System::UnicodeString id);
	TatVariableInfo* __fastcall DeclareVariable(System::UnicodeString AName, int AArgIndex = 0xffffffff, TatArgumentModifier AModifier = (TatArgumentModifier)(0x0), bool AGlobal = false, int ASourcePos = 0xffffffff);
	pSimplifiedCode __fastcall AppendInstruction(TInstruction i)/* overload */;
	pSimplifiedCode __fastcall RemoveLastInstruction(void);
	void __fastcall AppendInstruction(pSimplifiedCode AInstruction)/* overload */;
	void __fastcall OptimizeStoreVar(TatVariableInfo* AVar, bool AIgnoreConstant = false);
	void __fastcall OptimizeVarTest(int ACaseVarIndex, System::UnicodeString ACaseVarName, System::UnicodeString AJumpLabel, bool ACondition);
	void __fastcall SetSourceCode(System::Classes::TStrings* value);
	System::UnicodeString __fastcall ErrorComplement(int APos);
	void __fastcall SourceCodeChange(System::TObject* Sender);
	void __fastcall DisposeCode(pSimplifiedCode &code);
	void __fastcall RelativeMethodRef(TatMethod* AMethod, pSimplifiedCode AInst);
	void __fastcall RelativeGetterRef(TatProperty* AProperty, pSimplifiedCode AInst);
	void __fastcall RelativeSetterRef(TatProperty* AProperty, pSimplifiedCode AInst);
	__property int CodeLine = {read=FCodeLine, write=FCodeLine, nodefault};
	__property pSimplifiedCode LastInstruction = {read=FLastInstruction, write=FLastInstruction};
	__property TatRoutineInfo* CurrentRoutine = {read=FCurrentRoutine, write=FCurrentRoutine};
	__property int CounterInit = {read=FCounterInit, write=FCounterInit, nodefault};
	__property TatRoutineInfo* DebugScriptMainRoutine = {read=FDebugScriptMainRoutine, write=FDebugScriptMainRoutine};
	__property bool IsDebugScript = {read=FIsDebugScript, write=FIsDebugScript, nodefault};
	__property TRefactorClass RefactorClass = {read=FRefactorClass, write=FRefactorClass};
	virtual System::UnicodeString __fastcall EncodeSingleAssign(System::UnicodeString AVarName, System::UnicodeString AExpression) = 0 ;
	virtual int __fastcall DeclareEventHandler(System::UnicodeString AProcName);
	TatScripterLibrary* __fastcall SelfRegisterAsLibrary(TatCustomScripter* AScripter, System::UnicodeString AName, System::TClass AClassRef, System::UnicodeString AClassName, bool ADefault, bool AddMethod)/* overload */;
	void __fastcall CompileForm(System::UnicodeString AFormClassName, System::UnicodeString AFormFile);
	void __fastcall RegisterForm(void);
	void __fastcall UnregisterForm(void);
	void __fastcall CompileScriptClass(System::UnicodeString AClassName);
	void __fastcall RegisterScriptClass(void);
	void __fastcall UnregisterScriptClass(void);
	
public:
	__fastcall virtual TatScript(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatScript(void);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Compile(void);
	void __fastcall SilentCompile(void);
	void __fastcall ExpandDebugInfo(bool RequiresCompilation = true);
	void __fastcall GetRowColFromSource(int APos, int &row, int &col);
	void __fastcall LoadCodeFromFile(System::UnicodeString AFileName);
	void __fastcall SaveCodeToFile(System::UnicodeString AFileName);
	virtual void __fastcall LoadCodeFromStream(System::Classes::TStream* AStream);
	virtual void __fastcall SaveCodeToStream(System::Classes::TStream* AStream);
	bool __fastcall IsRegisteredAsLibrary(TatCustomScripter* AScripter);
	TatScripterLibrary* __fastcall SelfRegisterAsLibrary(TatCustomScripter* AScripter, System::UnicodeString AName = System::UnicodeString())/* overload */;
	TatScripterLibrary* __fastcall SelfRegisterAsLibrary(System::UnicodeString AName = System::UnicodeString())/* overload */;
	void __fastcall SelfUnregisterAsLibrary(TatCustomScripter* AScripter, System::UnicodeString AName = System::UnicodeString())/* overload */;
	void __fastcall SelfUnregisterAsLibrary(System::UnicodeString AName = System::UnicodeString())/* overload */;
	TatScripterLibrary* __fastcall LoadLibrary(System::UnicodeString ALibraryName, bool ADefault = true);
	TatClass* __fastcall UsesObject(System::TObject* AObject, System::UnicodeString AName = System::UnicodeString(), System::UnicodeString AClassName = System::UnicodeString());
	void __fastcall UnuseObject(System::UnicodeString AClassName);
	void __fastcall AddObject(System::UnicodeString AName, System::TObject* AObject);
	void __fastcall RemoveObject(System::UnicodeString AName);
	__property TatUsedUnits* UsedUnits = {read=FUsedUnits};
	__property TatVirtualMachine* VirtualMachine = {read=FVirtualMachine, write=FVirtualMachine};
	__property TatVirtualMachines* VirtualMachines = {read=FVirtualMachines};
	__property TatCustomScripter* Scripter = {read=FScripter};
	__property System::Classes::TStrings* SourceCode = {read=FSourceCode, write=SetSourceCode};
	__property TatScriptInfo* ScriptInfo = {read=FScriptInfo};
	__property bool Compiled = {read=FCompiled, write=SetCompiled, nodefault};
	__property bool SilentCompiled = {read=FSilentCompiled, write=FSilentCompiled, nodefault};
	__property pSimplifiedCode FirstInstruction = {read=FFirstInstruction};
	__property bool ExpandedDebugInfo = {read=FExpandedDebugInfo, nodefault};
	__property Atparser::TatSyntaxParser* Parser = {read=FParser};
	__property TatObjects* DefInstances = {read=FDefInstances};
	__property TatObject* IntInstance = {read=FIntInstance};
	__property TatScriptRefactor* Refactor = {read=FRefactor};
	__property TScriptForm* DesignScriptForm = {read=FDesignScriptForm, write=FDesignScriptForm};
	__property System::UnicodeString DesignFormResource = {read=FDesignFormResource, write=FDesignFormResource};
	__property System::UnicodeString UnitName = {read=FUnitName, write=FUnitName};
	__property TatScriptBreaks* Breaks = {read=FBreaks};
	__property System::Classes::TNotifyEvent OnDestroy = {read=FOnDestroy, write=FOnDestroy};
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TatVirtualMachines : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatVirtualMachine* operator[](int i) { return Items[i]; }
	
private:
	TatVirtualMachine* __fastcall GetItems(int i);
	
public:
	HIDESBASE TatVirtualMachine* __fastcall Add(void);
	__property TatVirtualMachine* Items[int i] = {read=GetItems/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TatVirtualMachines(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatVirtualMachines(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatDebugWatches;
class DELPHICLASS TatDebugWatch;
class PASCALIMPLEMENTATION TatVirtualMachine : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	typedef System::StaticArray<System::Variant, 3000> _TatVirtualMachine__1;
	
	
private:
	TatScript* FScript;
	TatCustomScripter* FScripter;
	System::Classes::TNotifyEvent FOnExecHook;
	System::Classes::TNotifyEvent FOnPauseChanged;
	System::Classes::TNotifyEvent FOnRunningChanged;
	System::TObject* FCurrentObject;
	TatClass* FCurrentClass;
	System::UnicodeString FCurrentRecordName;
	System::Variant FCurrentOleObject;
	_TatVirtualMachine__1 FProcStack;
	int FStackTop;
	int FStackBase;
	int FInputBase;
	int FOutputBase;
	int FInputOffset;
	int FOutputOffset;
	int FCurrentInputArgBase;
	int FCurrentArrayIndexBase;
	int FCurrentOutputArgIndex;
	TSimplifiedCode *FNextInstruction;
	TSimplifiedCode *FCurrentInstruction;
	System::UnicodeString FLastExceptionMessage;
	int FLastExceptionHelpContext;
	System::UnicodeString FLastExceptionClassName;
	TSimplifiedCode *FPrepareInstruction;
	TatScriptBreakPoints* FBreakPoints;
	bool FHalted;
	bool FRunning;
	bool FPaused;
	bool FCallExecHookEvent;
	System::StaticArray<TGenericProc, 79> FComputeProcs;
	TSimplifiedCode *FMainBegin;
	int FInitialStackTop;
	TatDebugWatches* FDebugWatches;
	TSimplifiedCode *FStopInstruction;
	int FHooking;
	Vcl::Forms::TExceptionEvent FOldOnException;
	System::Sysutils::Exception* FExceptionRaised;
	bool FInitialized;
	int FInTryExcept;
	bool FFastSolving;
	bool FAutoPause;
	int FAutoPauseCurLine;
	int __fastcall ExecProcess(int ParamCount);
	void __fastcall _GlobalPrepare(void);
	void __fastcall _Prepare(void);
	void __fastcall _PushDouble(void);
	void __fastcall _PushVar(void);
	void __fastcall _PushIdxVar(void);
	void __fastcall _PushVarByRef(void);
	void __fastcall _PushString(void);
	void __fastcall _PushOutput(void);
	void __fastcall _PushConst(void);
	void __fastcall _Duplicate(void);
	void __fastcall _Duplicate2(void);
	void __fastcall _Drop2(void);
	void __fastcall _Swap2(void);
	void __fastcall _OperNE(void);
	void __fastcall _OperGE(void);
	void __fastcall _OperLE(void);
	void __fastcall _OperEqual(void);
	void __fastcall _OperGreater(void);
	void __fastcall _OperLess(void);
	void __fastcall _OperAdd(void);
	void __fastcall _OperConcat(void);
	void __fastcall _OperSub(void);
	void __fastcall _OperOr(void);
	void __fastcall _OperXor(void);
	void __fastcall _OperMul(void);
	void __fastcall _OperSlash(void);
	void __fastcall _OperDiv(void);
	void __fastcall _OperMod(void);
	void __fastcall _OperAnd(void);
	void __fastcall _OperShl(void);
	void __fastcall _OperShr(void);
	void __fastcall _OperExp(void);
	void __fastcall _OperNeg(void);
	void __fastcall _OperNot(void);
	void __fastcall _JumpIfFalse(void);
	void __fastcall _JumpIfTrue(void);
	void __fastcall _Jump(void);
	void __fastcall _StoreVar(void);
	void __fastcall _StoreIdxVar(void);
	void __fastcall _StoreVarInteger(void);
	void __fastcall _StoreVarDouble(void);
	void __fastcall _StoreVarString(void);
	void __fastcall _StoreVarConst(void);
	void __fastcall _CopyVar(void);
	void __fastcall _StoreVarRef(void);
	void __fastcall _StoreIdxVarRef(void);
	void __fastcall _StoreVarRefInteger(void);
	void __fastcall _StoreVarRefDouble(void);
	void __fastcall _StoreVarRefString(void);
	void __fastcall _StoreVarRefConst(void);
	void __fastcall _CopyVarRef(void);
	void __fastcall _Call(void);
	void __fastcall _Ret(void);
	void __fastcall _StoreInput(void);
	void __fastcall _ExecFun(void);
	void __fastcall _PushInteger(void);
	void __fastcall _TryFinally(void);
	void __fastcall _TryExcept(void);
	void __fastcall _CallProc(void);
	void __fastcall _CallClassProc(void);
	void __fastcall _BreakPoint(void);
	void __fastcall _VarTest(void);
	void __fastcall _VarTestInteger(void);
	void __fastcall _VarTestDouble(void);
	void __fastcall _VarTestString(void);
	void __fastcall _VarTestVar(void);
	void __fastcall _Abort(void);
	void __fastcall _ArrayOf(void);
	void __fastcall _CastClass(void);
	void __fastcall _OperIs(void);
	void __fastcall _PushClass(void);
	void __fastcall _WithObject(void);
	void __fastcall _StoreGlobalVar(void);
	void __fastcall _StoreGlobalIdxVar(void);
	void __fastcall _PushGlobalVar(void);
	void __fastcall _PushGlobalIdxVar(void);
	void __fastcall _PushGlobalVarByRef(void);
	void __fastcall _TestIfFalse(void);
	void __fastcall _TestIfTrue(void);
	void __fastcall UndefinedGetterProc(void);
	void __fastcall UndefinedSetterProc(void);
	void __fastcall UndefinedMethodProc(void);
	void __fastcall SetRunning(const bool Value);
	void __fastcall SetPaused(const bool Value);
	bool __fastcall HandleScriptRunException(System::Sysutils::Exception* ex);
	void __fastcall DoDebugHook(void);
	void __fastcall DoExecHook(void);
	System::UnicodeString __fastcall GetStackContentAsString(void);
	System::Variant __fastcall SetVarArrayElement(const System::Variant &v, int ADim);
	System::Variant __fastcall GetVarArrayElement(const System::Variant &v, int ADim);
	System::Variant __fastcall InternalExecuteSubroutine(pSimplifiedCode AInstruction, int AInputParamCount = 0x0);
	void __fastcall CompileDebugScript(TatScript* AScript);
	void __fastcall ExecuteDebugScript(TatScript* AScript, TatScripterWatch* AScripterWatch = (TatScripterWatch*)(0x0), TatDebugWatch* ADebugWatch = (TatDebugWatch*)(0x0));
	void __fastcall CheckHalted(void);
	void __fastcall AppException(System::TObject* Sender, System::Sysutils::Exception* E);
	void __fastcall InitializeScript(bool ADoBeforeExecute);
	void __fastcall RuntimeError(System::UnicodeString msg);
	System::TClass __fastcall TranslateClass(int AClassIndex);
	System::Classes::TNotifyEvent __fastcall GetOnDebugHook(void);
	void __fastcall SetOnDebugHook(const System::Classes::TNotifyEvent Value);
	System::UnicodeString __fastcall GetScriptObjectClassName(System::TObject* AObject);
	
protected:
	virtual void __fastcall DoRunningChanged(void);
	
public:
	__fastcall virtual TatVirtualMachine(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatVirtualMachine(void);
	void __fastcall Clear(void);
	virtual void __fastcall SolveAbsoluteAddressing(void);
	void __fastcall InProcessExecute(System::UnicodeString AScriptStr);
	virtual System::Variant __fastcall Execute(const System::Variant &input)/* overload */;
	virtual System::Variant __fastcall Execute(void)/* overload */;
	System::Variant __fastcall ExecuteSubroutine(System::UnicodeString ALabel, const System::Variant &input)/* overload */;
	System::Variant __fastcall ExecuteSubroutine(System::UnicodeString ALabel)/* overload */;
	System::Variant __fastcall ExecuteSubroutine(System::UnicodeString ALabel, System::TVarRec *input, const int input_High)/* overload */;
	System::Variant __fastcall ExecuteSubroutineEx(System::UnicodeString ALabel, System::TVarRec *input, const int input_High);
	System::Variant __fastcall GetArrayIndex(int ADim);
	int __fastcall InputArgCount(void);
	System::Variant __fastcall GetInputArg(int AIndex);
	System::UnicodeString __fastcall GetInputArgAsString(int AIndex);
	System::TClass __fastcall GetInputArgAsClass(int AIndex);
	System::WideString __fastcall GetInputArgAsWidestring(int AIndex);
	int __fastcall GetInputArgAsInteger(int AIndex);
	__int64 __fastcall GetInputArgAsInt64(int AIndex);
	bool __fastcall GetInputArgAsBoolean(int AIndex);
	double __fastcall GetInputArgAsFloat(int AIndex);
	System::TDateTime __fastcall GetInputArgAsDateTime(int AIndex);
	System::WideChar __fastcall GetInputArgAsChar(int AIndex);
	System::WideChar __fastcall GetInputArgAsWideChar(int AIndex);
	void __fastcall SetInputArg(int AIndex, const System::Variant &AValue);
	void __fastcall SetInputArgIfByRef(int AIndex, const System::Variant &AValue);
	void __fastcall SetInputArgValue(int AIndex, const System::Rtti::TValue &AValue);
	void __fastcall ReturnOutputArg(const System::Variant &AValue);
	void __fastcall ReturnOutputArgValue(const System::Rtti::TValue &AValue);
	void __fastcall Halt(void);
	pSimplifiedCode __fastcall InstructionByLine(int ARow);
	pSimplifiedCode __fastcall EntryPoint(System::UnicodeString ALabel);
	void __fastcall DebugTraceInto(void);
	void __fastcall DebugStepOver(void);
	void __fastcall DebugTraceIntoLine(void);
	void __fastcall DebugStepOverLine(void);
	void __fastcall DebugRunUntilReturn(void);
	void __fastcall DebugRunToPoint(pSimplifiedCode AInstruction);
	void __fastcall DebugRunToLine(int ALine);
	bool __fastcall DebugToggleBreakPoint(pSimplifiedCode AInstruction);
	pSimplifiedCode __fastcall DebugToggleBreakLine(int ALine);
	int __fastcall DebugExecutionLine(void);
	System::UnicodeString __fastcall CurrentPropertyName(void);
	System::UnicodeString __fastcall CurrentMethodName(void);
	__property TatScript* Script = {read=FScript};
	__property TatCustomScripter* Scripter = {read=FScripter};
	__property System::UnicodeString LastExceptionMessage = {read=FLastExceptionMessage};
	__property int LastExceptionHelpContext = {read=FLastExceptionHelpContext, nodefault};
	__property System::UnicodeString LastExceptionClassName = {read=FLastExceptionClassName};
	__property System::TObject* CurrentObject = {read=FCurrentObject};
	__property TatClass* CurrentClass = {read=FCurrentClass};
	__property TatScriptBreakPoints* BreakPoints = {read=FBreakPoints, write=FBreakPoints};
	__property bool Halted = {read=FHalted, nodefault};
	__property bool Running = {read=FRunning, write=SetRunning, nodefault};
	__property bool Paused = {read=FPaused, write=SetPaused, nodefault};
	__property bool CallExecHookEvent = {read=FCallExecHookEvent, write=FCallExecHookEvent, nodefault};
	__property System::Classes::TNotifyEvent OnDebugHook = {read=GetOnDebugHook, write=SetOnDebugHook};
	__property System::Classes::TNotifyEvent OnExecHook = {read=FOnExecHook, write=FOnExecHook};
	__property System::Classes::TNotifyEvent OnPauseChanged = {read=FOnPauseChanged, write=FOnPauseChanged};
	__property System::Classes::TNotifyEvent OnRunningChanged = {read=FOnRunningChanged, write=FOnRunningChanged};
	__property pSimplifiedCode CurrentInstruction = {read=FCurrentInstruction};
	__property pSimplifiedCode NextInstruction = {read=FNextInstruction, write=FNextInstruction};
	__property pSimplifiedCode PrepareInstruction = {read=FPrepareInstruction};
	__property TatDebugWatches* DebugWatches = {read=FDebugWatches};
};


enum DECLSPEC_DENUM TatScriptBehavior : unsigned char { sbNormal, sbClass, sbForm };

class DELPHICLASS TatRoutinesInfo;
class DELPHICLASS TatVariablesInfo;
class PASCALIMPLEMENTATION TatScriptInfo : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TatRoutinesInfo* FRoutines;
	int FCodeSize;
	TatVariablesInfo* FGlobals;
	TatScript* FScript;
	TatRoutineInfo* FMainRoutine;
	System::UnicodeString FScriptClassName;
	System::UnicodeString FFormResource;
	TatScriptBehavior FBehavior;
	System::UnicodeString FUnitName;
	void __fastcall UpdateRoutineInfoPointers(void);
	void __fastcall SetGlobals(TatVariablesInfo* const Value);
	void __fastcall SetRoutines(TatRoutinesInfo* const Value);
	System::UnicodeString __fastcall GetMainRoutineName(void);
	void __fastcall SetMainRoutineName(const System::UnicodeString Value);
	bool __fastcall GetIsClass(void);
	bool __fastcall GetIsForm(void);
	
public:
	__fastcall virtual TatScriptInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TatScriptInfo(void);
	void __fastcall Clear(void);
	TatRoutineInfo* __fastcall RoutineByName(System::UnicodeString AName);
	TatRoutineInfo* __fastcall DeclareRoutine(System::UnicodeString AName, pSimplifiedCode ADeclInst, bool AIsFunction);
	__property int CodeSize = {read=FCodeSize, nodefault};
	__property TatScript* Script = {read=FScript};
	__property TatRoutineInfo* MainRoutine = {read=FMainRoutine, write=FMainRoutine};
	__property bool IsForm = {read=GetIsForm, nodefault};
	__property bool IsClass = {read=GetIsClass, nodefault};
	
__published:
	__property TatRoutinesInfo* Routines = {read=FRoutines, write=SetRoutines};
	__property TatVariablesInfo* Globals = {read=FGlobals, write=SetGlobals};
	__property System::UnicodeString MainRoutineName = {read=GetMainRoutineName, write=SetMainRoutineName};
	__property System::UnicodeString ScriptClassName = {read=FScriptClassName, write=FScriptClassName};
	__property System::UnicodeString FormResource = {read=FFormResource, write=FFormResource};
	__property TatScriptBehavior Behavior = {read=FBehavior, write=FBehavior, nodefault};
	__property System::UnicodeString UnitName = {read=FUnitName, write=FUnitName};
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TatRoutinesInfo : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatRoutineInfo* operator[](int i) { return Items[i]; }
	
private:
	TatScriptInfo* FScriptInfo;
	HIDESBASE TatRoutineInfo* __fastcall GetItem(int i);
	
public:
	int __fastcall IndexOf(System::UnicodeString AName);
	void __fastcall GetNames(System::Classes::TStrings* AStrings);
	__property TatRoutineInfo* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TatRoutinesInfo(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatRoutinesInfo(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TatRoutineVisibility : unsigned char { rvPublic, rvPrivate };

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatRoutineInfo : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatVariablesInfo* FVariables;
	System::UnicodeString FName;
	TSimplifiedCode *FDeclarationInstruction;
	bool FIsFunction;
	int FArgCount;
	int FByRefArgMask;
	int FResultIndex;
	TatRoutineInfo* FPrototype;
	TatCallingConvention FCallingConvention;
	System::UnicodeString FExternalDll;
	System::UnicodeString FExternalName;
	System::UnicodeString FResultTypeDecl;
	TatClass* FResultClass;
	TatRoutineVisibility FVisibility;
	void __fastcall SetVariables(TatVariablesInfo* const Value);
	TatTypeKind __fastcall ResultTypeKind(void);
	TatClass* __fastcall ResultClass(void);
	System::TClass __fastcall ResultClassRef(void);
	void __fastcall DispatchDllCall(TatVirtualMachine* AMachine);
	System::UnicodeString __fastcall GetResultTypeDecl(void);
	void __fastcall SetResultTypeDecl(const System::UnicodeString Value);
	void __fastcall SetTypeFromString(System::UnicodeString ATypeStr);
	System::UnicodeString __fastcall GetResultClassName(void);
	void __fastcall SetResultClassName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TatRoutineInfo(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatRoutineInfo(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	TatScriptInfo* __fastcall ScriptInfo(void);
	TatVariableInfo* __fastcall VariableByName(System::UnicodeString AName);
	bool __fastcall IsByRefArg(System::Byte n);
	int __fastcall LocalVarCount(void);
	TatVariableInfo* __fastcall DeclareVariable(System::UnicodeString AName, int ASourcePos, int AArgIndex = 0xffffffff, TatArgumentModifier AModifier = (TatArgumentModifier)(0x0));
	__property pSimplifiedCode DeclarationInstruction = {read=FDeclarationInstruction, write=FDeclarationInstruction};
	__property System::UnicodeString ResultClassName = {read=GetResultClassName, write=SetResultClassName};
	__property TatRoutineInfo* Prototype = {read=FPrototype, write=FPrototype};
	void __fastcall PrepareExternalClass(void);
	bool __fastcall Internal(void);
	
__published:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TatVariablesInfo* Variables = {read=FVariables, write=SetVariables};
	__property bool IsFunction = {read=FIsFunction, write=FIsFunction, nodefault};
	__property int ArgCount = {read=FArgCount, write=FArgCount, nodefault};
	__property int ByRefArgMask = {read=FByRefArgMask, write=FByRefArgMask, nodefault};
	__property int ResultIndex = {read=FResultIndex, write=FResultIndex, nodefault};
	__property TatCallingConvention CallingConvention = {read=FCallingConvention, write=FCallingConvention, nodefault};
	__property System::UnicodeString ExternalDll = {read=FExternalDll, write=FExternalDll};
	__property System::UnicodeString ExternalName = {read=FExternalName, write=FExternalName};
	__property System::UnicodeString ResultTypeDecl = {read=GetResultTypeDecl, write=SetResultTypeDecl};
	__property TatRoutineVisibility Visibility = {read=FVisibility, write=FVisibility, nodefault};
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatVariablesInfo : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatVariableInfo* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatVariableInfo* __fastcall GetItem(int i);
	
public:
	HIDESBASE TatVariableInfo* __fastcall Add(void);
	int __fastcall IndexOf(System::UnicodeString AName);
	TatVariableInfo* __fastcall FindByName(System::UnicodeString AName);
	__property TatVariableInfo* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TatVariablesInfo(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatVariablesInfo(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TatVariableVisibility : unsigned char { vvPublic, vvPrivate };

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatVariableInfo : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FVarName;
	int FDeclarationSourcePos;
	int FArgIndex;
	TatArgumentModifier FModifier;
	TatClass* FDeclaredClass;
	bool FGlobal;
	System::UnicodeString FTypeDecl;
	int FSystemType;
	TatVariableVisibility FVisibility;
	System::Variant __fastcall GetValue(void);
	void __fastcall SetValue(const System::Variant &AValue);
	TatScript* __fastcall Script(void);
	TatRoutineInfo* __fastcall Routine(void);
	System::UnicodeString __fastcall GetDeclaredClassName(void);
	void __fastcall SetDeclaredClassName(const System::UnicodeString Value);
	void __fastcall PullSystemType(void);
	
public:
	__fastcall virtual TatVariableInfo(System::Classes::TCollection* ACollection);
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	void __fastcall SetTypeFromString(System::UnicodeString ATypeStr);
	TatScriptInfo* __fastcall ScriptInfo(void);
	bool __fastcall Internal(void);
	int __fastcall VarIndex(void);
	bool __fastcall SameDeclaration(TatVariableInfo* AVariable);
	__property System::Variant Value = {read=GetValue, write=SetValue};
	__property TatClass* DeclaredClass = {read=FDeclaredClass, write=FDeclaredClass};
	
__published:
	__property System::UnicodeString VarName = {read=FVarName, write=FVarName};
	__property int DeclarationSourcePos = {read=FDeclarationSourcePos, write=FDeclarationSourcePos, nodefault};
	__property int ArgIndex = {read=FArgIndex, write=FArgIndex, nodefault};
	__property TatArgumentModifier Modifier = {read=FModifier, write=FModifier, nodefault};
	__property bool Global = {read=FGlobal, write=FGlobal, nodefault};
	__property System::UnicodeString DeclaredClassName = {read=GetDeclaredClassName, write=SetDeclaredClassName};
	__property System::UnicodeString TypeDecl = {read=FTypeDecl, write=FTypeDecl};
	__property int SystemType = {read=FSystemType, write=FSystemType, nodefault};
	__property TatVariableVisibility Visibility = {read=FVisibility, write=FVisibility, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatVariableInfo(void) { }
	
};

#pragma pack(pop)

__interface IatInterfacedObject;
typedef System::DelphiInterface<IatInterfacedObject> _di_IatInterfacedObject;
__interface  INTERFACE_UUID("{44284F76-2152-4326-9CB7-DEC05852B5CA}") IatInterfacedObject  : public System::IInterface 
{
	
public:
	virtual System::TObject* __fastcall GetObjectReference(void) = 0 ;
};

class DELPHICLASS TatRecordWrapper;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatRecordWrapper : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	System::TObject* __fastcall GetObjectReference(void);
public:
	/* TObject.Create */ inline __fastcall TatRecordWrapper(void) : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TatRecordWrapper(void) { }
	
private:
	void *__IatInterfacedObject;	// IatInterfacedObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {44284F76-2152-4326-9CB7-DEC05852B5CA}
	operator _di_IatInterfacedObject()
	{
		_di_IatInterfacedObject intf;
		GetInterface(intf);
		return intf;
	}
	#else
	operator IatInterfacedObject*(void) { return (IatInterfacedObject*)&__IatInterfacedObject; }
	#endif
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScriptBreakPoints : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatScriptBreakPoint* operator[](int i) { return Items[i]; }
	
private:
	TatVirtualMachine* FMachine;
	HIDESBASE TatScriptBreakPoint* __fastcall GetItem(int i);
	
public:
	__fastcall TatScriptBreakPoints(TatVirtualMachine* AMachine);
	TatScriptBreakPoint* __fastcall InsertNormalBreak(pSimplifiedCode ATargetInst);
	TatScriptBreakPoint* __fastcall InsertTempBreak(pSimplifiedCode ATargetInst);
	bool __fastcall RemoveBreakPoint(pSimplifiedCode ATargetInst);
	TatScriptBreakPoint* __fastcall BreakPointByLine(int ALine);
	HIDESBASE TatScriptBreakPoint* __fastcall Add(void);
	__property TatScriptBreakPoint* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatScriptBreakPoints(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TatScriptBreakPoint : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TSimplifiedCode FOriginalInst;
	TSimplifiedCode *FBreakInst;
	int FPassCount;
	bool FEnabled;
	bool FAutoDestroy;
	TatScriptBreak* FNotifyBreak;
	void __fastcall SetBreakInst(pSimplifiedCode ATargetInst);
	void __fastcall RemoveBreak(void);
	void __fastcall NormalBreakProc(void);
	void __fastcall TemporaryBreakProc(void);
	
public:
	__fastcall virtual TatScriptBreakPoint(System::Classes::TCollection* Collection);
	__fastcall virtual ~TatScriptBreakPoint(void);
	TatVirtualMachine* __fastcall Machine(void);
	__property TSimplifiedCode OriginalInst = {read=FOriginalInst, write=FOriginalInst};
	__property int PassCount = {read=FPassCount, write=FPassCount, nodefault};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
	__property bool AutoDestroy = {read=FAutoDestroy, write=FAutoDestroy, nodefault};
};


enum DECLSPEC_DENUM TLoopStatement : unsigned char { lsNone, lsFor, lsWhile, lsRepeat };

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatClasses : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatClass* operator[](int i) { return Items[i]; }
	
private:
	TatCustomScripter* FScripter;
	HIDESBASE TatClass* __fastcall GetItem(int i);
	int __fastcall GetImplicitCount(void);
	
protected:
	TatClass* __fastcall AddClassByRTTI(System::TClass AClass, System::UnicodeString AClassName = System::UnicodeString());
	TatClass* __fastcall AddClassByRTTIEx(System::TClass AClass, System::UnicodeString AClassName = System::UnicodeString(), TMemberVisibilitySet AVisibilityFilter = (TMemberVisibilitySet() << System::Typinfo::TMemberVisibility::mvPublic << System::Typinfo::TMemberVisibility::mvPublished ), bool ARecursive = false, TRedefineOption ARedefine = (TRedefineOption)(0x0))/* overload */;
	TatClass* __fastcall AddRecord(System::Typinfo::PTypeInfo ATypeInfo, System::UnicodeString ARecordName = System::UnicodeString());
	TatClass* __fastcall AddDelphiClass(System::TClass AClass, System::UnicodeString AClassName = System::UnicodeString());
	TatClass* __fastcall CheckLoaded(System::TClass AClass, System::UnicodeString AClassName = System::UnicodeString());
	__property int ImplicitCount = {read=GetImplicitCount, nodefault};
	
public:
	__fastcall TatClasses(TatCustomScripter* AScripter);
	HIDESBASE TatClass* __fastcall Add(System::UnicodeString AName, System::UnicodeString AAncestorName);
	int __fastcall IndexOf(System::UnicodeString AName);
	TatClass* __fastcall ClassByName(System::UnicodeString AName);
	bool __fastcall TestCheckLoaded(System::TClass AClass, TatClass* &ACurrentClass, System::UnicodeString AClassName = System::UnicodeString());
	__property TatClass* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatClasses(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatProperties;
class DELPHICLASS TatMethods;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatClass : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	TatProperties* FProperties;
	TatMethods* FMethods;
	System::TClass FClassRef;
	System::Typinfo::TTypeInfo *FRecordRef;
	System::UnicodeString FAncestorName;
	TatClass* FAncestor;
	System::Classes::TList* FDescendants;
	TatProperty* FDefaultProperty;
	TatScript* FBaseScript;
	System::Classes::TCollectionItem* FImplicitElement;
	void __fastcall Inherits(System::UnicodeString AAncestorName);
	void __fastcall RemoveDescendant(TatClass* ADescendant);
	void __fastcall InsertDescendant(TatClass* ADescendant);
	void __fastcall NotifyDescendants(void);
	void __fastcall AncestorDestroyed(void);
	void __fastcall SetMethods(TatMethods* const Value);
	void __fastcall SetProperties(TatProperties* const Value);
	bool __fastcall GetIsImplicit(void);
	void __fastcall SetImplicitElement(System::Classes::TCollectionItem* const Value);
	TatCustomScripter* __fastcall Scripter(void);
	
public:
	__fastcall virtual TatClass(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatClass(void);
	TatMethod* __fastcall SetProc(System::UnicodeString AName, void * ACode, int AArgCount, TatTypeKind AResultDataType, TGenericProc AProc, System::TClass AResultClass, bool AIsClassMethod = false, int ADefArgCount = 0x0, System::UnicodeString AParameterHints = System::UnicodeString());
	TatMethod* __fastcall AddProc(System::UnicodeString AName, void * ACode, int AArgCount, TatTypeKind AResultDataType, TGenericProc AProc, System::TClass AResultClass, bool AIsClassMethod = false, int ADefArgCount = 0x0);
	TatProperty* __fastcall PropertyByName(System::UnicodeString AName);
	TatProperty* __fastcall ClassPropertyByName(System::UnicodeString AName);
	TatMethod* __fastcall MethodByName(System::UnicodeString AName);
	TatMethod* __fastcall ClassMethodByName(System::UnicodeString AName);
	TatClass* __fastcall CastFromString(System::UnicodeString AClassName);
	void __fastcall RemoveProperty(System::UnicodeString AName);
	void __fastcall AddEnumeration(System::Typinfo::PTypeInfo ATypeInfo);
	void __fastcall AddObject(System::UnicodeString AName, System::TObject* AObject);
	void __fastcall AddConstant(System::UnicodeString AName, const System::Variant &AValue);
	void __fastcall AddVariable(System::UnicodeString AName, System::Variant &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, System::Extended &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, double &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, System::UnicodeString &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, System::WideString &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, int &AVar)/* overload */;
	void __fastcall AddVariable(System::UnicodeString AName, bool &AVar)/* overload */;
	TatProperty* __fastcall AddProp(System::UnicodeString AName, TatTypeKind ADataType, TGenericProc AGetter, TGenericProc ASetter, System::TClass APropertyClass = 0x0, bool AIsClassProp = false, int AIndexCount = 0x0);
	TatProperty* __fastcall SetProp(System::UnicodeString AName, TatTypeKind ADataType, TGenericProc AGetter, TGenericProc ASetter, System::TClass APropertyClass = 0x0, bool AIsClassProp = false, int AIndexCount = 0x0);
	void __fastcall AddIntegerProp(System::UnicodeString AName, TGenericProc AGetter, TGenericProc ASetter, bool AIsClassProp = false);
	void __fastcall AddStringProp(System::UnicodeString AName, TGenericProc AGetter, TGenericProc ASetter, bool AIsClassProp = false);
	void __fastcall AddBooleanProp(System::UnicodeString AName, TGenericProc AGetter, TGenericProc ASetter, bool AIsClassProp = false);
	void __fastcall AddFloatProp(System::UnicodeString AName, TGenericProc AGetter, TGenericProc ASetter, bool AIsClassProp = false);
	void __fastcall AddVariantProp(System::UnicodeString AName, TGenericProc AGetter, TGenericProc ASetter, bool AIsClassProp = false);
	void __fastcall AddObjectProp(System::UnicodeString AName, TGenericProc AGetter, TGenericProc ASetter, System::TClass APropertyClass, bool AIsClassProp = false);
	void __fastcall AddDelphiObjectProp(System::UnicodeString AName, System::TObject* AObject);
	TatProperty* __fastcall DefineProp(System::UnicodeString AName, TatTypeKind ADataType, TMachineProc AGetter, TMachineProc ASetter, System::TClass APropertyClass = 0x0, bool AIsClassProp = false, int AIndexCount = 0x0);
	TatProperty* __fastcall DefineNewProp(System::UnicodeString AName, TatTypeKind ADataType, TMachineProc AGetter, TMachineProc ASetter, System::TClass APropertyClass = 0x0, bool AIsClassProp = false, int AIndexCount = 0x0);
	void __fastcall DefineIntegerProp(System::UnicodeString AName, TMachineProc AGetter, TMachineProc ASetter, bool AIsClassProp = false);
	void __fastcall DefineStringProp(System::UnicodeString AName, TMachineProc AGetter, TMachineProc ASetter, bool AIsClassProp = false);
	void __fastcall DefineBooleanProp(System::UnicodeString AName, TMachineProc AGetter, TMachineProc ASetter, bool AIsClassProp = false);
	void __fastcall DefineFloatProp(System::UnicodeString AName, TMachineProc AGetter, TMachineProc ASetter, bool AIsClassProp = false);
	void __fastcall DefineVariantProp(System::UnicodeString AName, TMachineProc AGetter, TMachineProc ASetter, bool AIsClassProp = false);
	void __fastcall DefineObjectProp(System::UnicodeString AName, TMachineProc AGetter, TMachineProc ASetter, System::TClass APropertyClass, bool AIsClassProp = false);
	TatMethod* __fastcall AddMethod(System::UnicodeString AName, int AArgCount, TatTypeKind AResultDataType, System::TClass AResultClass, TGenericProc AProc, bool AIsClassMethod = false, int ADefArgCount = 0x0);
	TatMethod* __fastcall DefineNewMethod(System::UnicodeString AName, int AArgCount, TatTypeKind AResultDataType, System::TClass AResultClass, TMachineProc AProc, bool AIsClassMethod = false, int ADefArgCount = 0x0);
	TatMethod* __fastcall DefineMethod(System::UnicodeString AName, int AArgCount, TatTypeKind AResultDataType, System::TClass AResultClass, TMachineProc AProc, bool AIsClassMethod = false, int ADefArgCount = 0x0, System::UnicodeString AParameterHints = System::UnicodeString());
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TatProperties* Properties = {read=FProperties, write=SetProperties};
	__property TatMethods* Methods = {read=FMethods, write=SetMethods};
	__property System::UnicodeString AncestorName = {read=FAncestorName, write=FAncestorName};
	__property System::TClass ClassRef = {read=FClassRef, write=FClassRef};
	__property TatClass* Ancestor = {read=FAncestor, write=FAncestor};
	__property TatProperty* DefaultProperty = {read=FDefaultProperty, write=FDefaultProperty};
	__property System::Classes::TCollectionItem* ImplicitElement = {read=FImplicitElement, write=SetImplicitElement};
	__property bool IsImplicit = {read=GetIsImplicit, nodefault};
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatProperties : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatProperty* operator[](int i) { return Items[i]; }
	
private:
	TatClass* FClass;
	HIDESBASE TatProperty* __fastcall GetItem(int i);
	
public:
	__fastcall TatProperties(TatClass* AClass);
	__property TatProperty* Items[int i] = {read=GetItem/*, default*/};
	TatProperty* __fastcall AddByRTTI(System::Typinfo::PPropInfo APropInfo);
	int __fastcall IndexOf(System::UnicodeString AName);
	TatProperty* __fastcall PropertyByName(System::UnicodeString AName);
	TatProperty* __fastcall ClassPropertyByName(System::UnicodeString AName);
	__property TatClass* atClass = {read=FClass};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatProperties(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TatProperty : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatCustomScripter* FScripter;
	System::UnicodeString FName;
	TatTypeKind FDataType;
	TGenericProc FGetter;
	TGenericProc FSetter;
	System::TClass FPropertyClass;
	System::UnicodeString FPropertyClassName;
	System::Typinfo::TPropInfo *FPropInfo;
	System::Variant FValue;
	bool FIsClassProp;
	int FIndexCount;
	void __fastcall RTTIGetterProc(TatVirtualMachine* AMachine);
	void __fastcall RTTISetterProc(TatVirtualMachine* AMachine);
	void __fastcall GetFormComponentProc(TatVirtualMachine* AMachine);
	void __fastcall GetDelphiObjectPropProc(TatVirtualMachine* AMachine);
	void __fastcall GetVariantPropProc(TatVirtualMachine* AMachine);
	void __fastcall GetBoolVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall GetExtVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall GetDblVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall GetIntVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall GetStrVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall GetWStrVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall GetVarVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetBoolVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetExtVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetDblVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetIntVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetStrVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetWStrVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetVarVariablePropProc(TatVirtualMachine* AMachine);
	void __fastcall SetPropExtra(TGenericProc AGetter, TGenericProc ASetter, const System::Variant &AValue);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName(void);
	
public:
	__fastcall virtual TatProperty(System::Classes::TCollection* ACollection);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall UpdateObjectInfo(TatClass* &ACurrentClass);
	TatClass* __fastcall atClass(void);
	__property TatCustomScripter* Scripter = {read=FScripter, write=FScripter};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TGenericProc Getter = {read=FGetter, write=FGetter};
	__property TGenericProc Setter = {read=FSetter, write=FSetter};
	__property TatTypeKind DataType = {read=FDataType, write=FDataType, nodefault};
	__property System::Variant Value = {read=FValue, write=FValue};
	__property bool IsClassProp = {read=FIsClassProp, write=FIsClassProp, nodefault};
	__property System::TClass PropertyClass = {read=FPropertyClass, write=FPropertyClass};
	__property System::Typinfo::PPropInfo PropInfo = {read=FPropInfo, write=FPropInfo};
	__property int IndexCount = {read=FIndexCount, write=FIndexCount, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatProperty(void) { }
	
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TatMethods : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatMethod* operator[](int i) { return Items[i]; }
	
private:
	TatClass* FClass;
	HIDESBASE TatMethod* __fastcall GetItem(int i);
	
public:
	__fastcall TatMethods(TatClass* AClass);
	__property TatMethod* Items[int i] = {read=GetItem/*, default*/};
	int __fastcall IndexOf(System::UnicodeString AName);
	TatMethod* __fastcall MethodByName(System::UnicodeString AName);
	TatMethod* __fastcall ClassMethodByName(System::UnicodeString AName);
	__property TatClass* atClass = {read=FClass};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatMethods(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatDataDefs;
class PASCALIMPLEMENTATION TatMethod : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatCustomScripter* FScripter;
	System::UnicodeString FName;
	TGenericProc FProc;
	TatTypeKind FResultDataType;
	int FArgCount;
	void *FCode;
	System::TClass FResultClass;
	TatDataDefs* FArgDefs;
	bool FIsClassMethod;
	int FByRefArgMask;
	int FDefArgCount;
	System::UnicodeString FResultClassName;
	void __fastcall SetArgDefs(TatDataDefs* const Value);
	void __fastcall AdjustArgDefsCount(void);
	void __fastcall SetArgCount(const int Value);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName(void);
	
public:
	__fastcall virtual TatMethod(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatMethod(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall UpdateObjectInfo(TatClass* &ACurrentClass);
	void __fastcall SetVarArgs(System::Byte *argi, const int argi_High);
	bool __fastcall IsByRefArg(System::Byte n);
	TatClass* __fastcall atClass(void);
	void __fastcall UpdateParameterHints(const System::UnicodeString AParameterHints);
	__property TatCustomScripter* Scripter = {read=FScripter, write=FScripter};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TGenericProc Proc = {read=FProc, write=FProc};
	__property TatTypeKind ResultDataType = {read=FResultDataType, write=FResultDataType, nodefault};
	__property int ArgCount = {read=FArgCount, write=SetArgCount, nodefault};
	__property int DefArgCount = {read=FDefArgCount, write=FDefArgCount, nodefault};
	__property TatDataDefs* ArgDefs = {read=FArgDefs, write=SetArgDefs};
	__property bool IsClassMethod = {read=FIsClassMethod, write=FIsClassMethod, nodefault};
	__property void * Code = {read=FCode, write=FCode};
	__property System::TClass ResultClass = {read=FResultClass, write=FResultClass};
	__property int ByRefArgMask = {read=FByRefArgMask, write=FByRefArgMask, nodefault};
};


class DELPHICLASS TatDataDef;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatDataDefs : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatDataDef* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatDataDef* __fastcall GetItem(int i);
	
public:
	__fastcall TatDataDefs(TatClass* AClass);
	__property TatDataDef* Items[int i] = {read=GetItem/*, default*/};
	HIDESBASE TatDataDef* __fastcall Add(System::UnicodeString AName, TatTypeKind ADataType, TatArgumentModifier AModifier);
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatDataDefs(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatDataDef : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	TatTypeKind FDataType;
	TatArgumentModifier FModifier;
	System::UnicodeString FDataTypeName;
	System::UnicodeString FDefaultValueText;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	__property System::UnicodeString Name = {read=FName};
	__property TatTypeKind DataType = {read=FDataType, nodefault};
	__property TatArgumentModifier Modifier = {read=FModifier, write=FModifier, nodefault};
	__property System::UnicodeString DataTypeName = {read=FDataTypeName};
	__property System::UnicodeString DefaultValueText = {read=FDefaultValueText};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatDataDef(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatDataDef(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatObjects : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatObject* operator[](int i) { return Items[i]; }
	
private:
	TatClasses* FClasses;
	HIDESBASE TatObject* __fastcall GetItem(int i);
	
public:
	__fastcall TatObjects(TatClasses* AClasses);
	HIDESBASE TatObject* __fastcall Add(System::TObject* AInstance, System::UnicodeString AName = System::UnicodeString(), System::UnicodeString AClassName = System::UnicodeString());
	int __fastcall FindInstanceByMethodName(System::UnicodeString AMethodName, TatMethod* &AMethod);
	int __fastcall FindInstanceByPropertyName(System::UnicodeString APropertyName, TatProperty* &AProperty);
	TatObject* __fastcall FindInstanceByClassName(System::UnicodeString AClassName);
	int __fastcall IndexOf(System::UnicodeString AName);
	__property TatObject* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatObjects(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatObject : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::TObject* FInstance;
	TatClass* FatClass;
	void __fastcall SeTatClass(TatClass* const Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::TObject* Instance = {read=FInstance, write=FInstance};
	__property TatClass* atClass = {read=FatClass, write=SeTatClass};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatObject(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatObject(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatClassRefs;
class DELPHICLASS TatClassRef;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatClassRefs : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatClassRef* operator[](int i) { return Items[i]; }
	
private:
	TatScript* FScript;
	HIDESBASE TatClassRef* __fastcall GetItem(int i);
	
public:
	__fastcall TatClassRefs(TatScript* AScript);
	HIDESBASE TatClassRef* __fastcall Add(int AClassIndex, int AElementIndex, int AElementClassIndex, bool AElementIsMethod, System::UnicodeString AClassName, System::UnicodeString AElementName, System::UnicodeString AElementClassName);
	__property TatClassRef* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatClassRefs(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatClassRef : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	int FClassIndex;
	int FElementIndex;
	bool FElementIsMethod;
	System::UnicodeString FElementName;
	System::UnicodeString FClassName;
	System::UnicodeString FElementClassName;
	int FElementClassIndex;
	
public:
	void __fastcall CheckLoaded(void);
	__property int ClassIndex = {read=FClassIndex, nodefault};
	__property int ElementIndex = {read=FElementIndex, nodefault};
	__property bool ElementIsMethod = {read=FElementIsMethod, nodefault};
	__property int ElementClassIndex = {read=FElementClassIndex, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatClassRef(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatClassRef(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatUsedUnit;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatUsedUnit : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	bool FIsDefault;
	System::UnicodeString FUnitName;
	bool FIsScript;
	int FDeclSourcePos;
	
public:
	__property System::UnicodeString UnitName = {read=FUnitName, write=FUnitName};
	__property bool IsDefault = {read=FIsDefault, write=FIsDefault, nodefault};
	__property bool IsScript = {read=FIsScript, write=FIsScript, nodefault};
	__property int DeclSourcePos = {read=FDeclSourcePos, write=FDeclSourcePos, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatUsedUnit(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatUsedUnit(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatUsedUnits : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatUsedUnit* operator[](int i) { return Items[i]; }
	
private:
	TatCustomScripter* FScripter;
	HIDESBASE TatUsedUnit* __fastcall GetItem(int i);
	
public:
	__fastcall TatUsedUnits(TatCustomScripter* AScripter);
	TatUsedUnit* __fastcall FindByName(System::UnicodeString AUnitName);
	HIDESBASE TatUsedUnit* __fastcall Add(void);
	__property TatUsedUnit* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatUsedUnits(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScripterLibrary : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TatCustomScripter* FScripter;
	System::UnicodeString FDefaultInstanceName;
	void __fastcall SelfProc(TatVirtualMachine* AMachine);
	
protected:
	virtual void __fastcall Init(void) = 0 ;
	virtual void __fastcall Finalize(void);
	__property TatCustomScripter* Scripter = {read=FScripter};
	
public:
	__classmethod virtual System::UnicodeString __fastcall LibraryName();
	__fastcall virtual TatScripterLibrary(TatCustomScripter* AScripter);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TatScripterLibrary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatDLL;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatDLL : public TatScripterLibrary
{
	typedef TatScripterLibrary inherited;
	
private:
	TatScript* FScript;
	System::UnicodeString FFileName;
	TatClass* FatClass;
	
public:
	virtual void __fastcall Init(void);
	virtual void __fastcall Finalize(void);
	__classmethod virtual System::UnicodeString __fastcall LibraryName();
public:
	/* TatScripterLibrary.Create */ inline __fastcall virtual TatDLL(TatCustomScripter* AScripter) : TatScripterLibrary(AScripter) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TatDLL(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatScriptBasedLibrary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatScriptBasedLibrary : public TatScripterLibrary
{
	typedef TatScripterLibrary inherited;
	
private:
	TatScript* FInternalScript;
	System::UnicodeString FName;
	System::Classes::TList* FMethodList;
	System::Classes::TList* FPropList;
	System::TClass FRegClass;
	System::UnicodeString FRegClassName;
	TatClass* FNewClass;
	TatScript* __fastcall GetRunScript(TatVirtualMachine* AMachine);
	void __fastcall ExecSubRoutineProc(TatVirtualMachine* AMachine);
	void __fastcall GetScriptVarProc(TatVirtualMachine* AMachine);
	void __fastcall SetScriptVarProc(TatVirtualMachine* AMachine);
	
protected:
	virtual void __fastcall Init(void);
	virtual void __fastcall Finalize(void);
	
public:
	__fastcall virtual TatScriptBasedLibrary(TatCustomScripter* AScripter);
	__fastcall virtual ~TatScriptBasedLibrary(void);
};

#pragma pack(pop)

class DELPHICLASS TatLibraryListItem;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatLibraryListItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatScripterLibraryClass FLibraryClass;
	bool FExplicitLoad;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property TatScripterLibraryClass LibraryClass = {read=FLibraryClass, write=FLibraryClass};
	__property bool ExplicitLoad = {read=FExplicitLoad, write=FExplicitLoad, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatLibraryListItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatLibraryListItem(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatLibraryList;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatLibraryList : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatLibraryListItem* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TatLibraryListItem* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TatLibraryListItem* __fastcall Add(void);
	void __fastcall Remove(TatScripterLibraryClass ALibrary);
	TatLibraryListItem* __fastcall FindByLibraryName(System::UnicodeString ALibName);
	__property TatLibraryListItem* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TatLibraryList(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TatLibraryList(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatEventDispatchers;
class DELPHICLASS TatEventAdapters;
class PASCALIMPLEMENTATION TatScripterEventBroker : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TatCustomScripter* FScripter;
	TatEventDispatchers* FDispatchers;
	TExecuteEventProc FOnExecuteEvent;
	TSettingEventProc FOnSettingEvent;
	TSetEventProc FOnSetEvent;
	TUnsetEventProc FOnUnsettingEvent;
	TatEventAdapters* FEventAdapters;
	TatEventDispatcher* __fastcall InternalSetEvent(System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, System::UnicodeString ARoutineName, TatCustomScripter* AScripter, TatEventPlacement APlacement, TatScript* AScript);
	bool __fastcall InternalUnsetEvent(System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, System::UnicodeString ARoutineName, TatCustomScripter* AScripter);
	bool __fastcall InternalUnsetEvents(System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo);
	void __fastcall SetDispatchers(TatEventDispatchers* const Value);
	void __fastcall SetOnExecuteEvent(const TExecuteEventProc Value);
	void __fastcall SetOnSetEvent(const TSetEventProc Value);
	void __fastcall SetOnUnsettingEvent(const TUnsetEventProc Value);
	System::TMethod __fastcall GetOldMethod(const System::TMethod &m);
	bool __fastcall MethodIsDesiredDispatcher(const System::TMethod &m, System::UnicodeString ARoutineName, TatCustomScripter* AScripter);
	TatEventDispatcher* __fastcall GetDispatcherFromMethod(const System::TMethod &m);
	void __fastcall SetOnSettingEvent(const TSettingEventProc Value);
	System::TMethod __fastcall GetMethodPropEx(System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo);
	void __fastcall SetMethodPropEx(System::TObject* AInstance, System::Typinfo::PPropInfo APropInfo, const System::TMethod &AMethod);
	
public:
	__fastcall virtual TatScripterEventBroker(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TatScripterEventBroker(void);
	TatEventDispatcher* __fastcall SetEvent(System::TObject* AInstance, System::UnicodeString APropName, System::UnicodeString ARoutineName, TatCustomScripter* AScripter, TatEventPlacement APlacement, TatScript* AScript = (TatScript*)(0x0));
	bool __fastcall UnsetEvent(System::TObject* AInstance, System::UnicodeString APropName, System::UnicodeString ARoutineName = System::UnicodeString(), TatCustomScripter* AScripter = (TatCustomScripter*)(0x0));
	bool __fastcall UnsetEvents(System::TObject* AInstance, System::UnicodeString APropName);
	System::UnicodeString __fastcall GetAssignedRoutineName(System::TObject* AInstance, System::UnicodeString APropName, TatCustomScripter* AScripter);
	void __fastcall UnsetAllEvents(void);
	__property TatEventAdapters* EventAdapters = {read=FEventAdapters, write=FEventAdapters};
	
__published:
	__property TatEventDispatchers* Dispatchers = {read=FDispatchers, write=SetDispatchers};
	__property TExecuteEventProc OnExecuteEvent = {read=FOnExecuteEvent, write=SetOnExecuteEvent};
	__property TSettingEventProc OnSettingEvent = {read=FOnSettingEvent, write=SetOnSettingEvent};
	__property TSetEventProc OnSetEvent = {read=FOnSetEvent, write=SetOnSetEvent};
	__property TUnsetEventProc OnUnsettingEvent = {read=FOnUnsettingEvent, write=SetOnUnsettingEvent};
};


class DELPHICLASS TatEventAdapter;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatEventAdapters : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TatEventAdapter* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatEventAdapter* __fastcall GetItem(int i);
	
public:
	HIDESBASE TatEventAdapter* __fastcall Add(void);
	__property TatEventAdapter* Items[int i] = {read=GetItem/*, default*/};
	TatEventAdapter* __fastcall FindAdapter(System::Typinfo::PTypeInfo ARttiInfo);
	TatEventAdapter* __fastcall AdapterByPropInfo(System::Typinfo::PPropInfo APropInfo);
	TatEventAdapter* __fastcall DefineEventAdapter(System::Typinfo::PTypeInfo ARttiInfo, TDispatcherClass ADispatcherClass, void * AMethodCode, bool ACheck);
public:
	/* TCollection.Create */ inline __fastcall TatEventAdapters(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TatEventAdapters(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatEventAdapter : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::Typinfo::TTypeInfo *FRttiInfo;
	void *FMethodCode;
	TDispatcherClass FDispatcherClass;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TatEventAdapter(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TatEventAdapter(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TatEventDispatchers : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatEventDispatcher* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatEventDispatcher* __fastcall GetItem(int i);
	
public:
	HIDESBASE TatEventDispatcher* __fastcall Add(void);
	__property TatEventDispatcher* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TatEventDispatchers(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatEventDispatchers(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TatDispatcherRemoveNotificator;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatEventDispatcher : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::TMethod FBeforeCall;
	System::TMethod FAfterCall;
	System::TMethod FOldCall;
	TatCustomScripter* FScripter;
	System::UnicodeString FRoutineName;
	System::TMethod FCustomCall;
	TatEventAdapter* FAdapter;
	System::TObject* FInstance;
	System::Typinfo::TPropInfo *FPropInfo;
	TatDispatcherRemoveNotificator* FNotificator;
	bool FIsComponent;
	TatScript* FScript;
	void __fastcall SetScripter(TatCustomScripter* const Value);
	void __fastcall SetAfterCall(const System::TMethod &Value);
	void __fastcall SetBeforeCall(const System::TMethod &Value);
	void __fastcall SetOldCall(const System::TMethod &Value);
	void __fastcall SetAdapter(TatEventAdapter* const Value);
	void __fastcall SetInstance(System::TObject* const Value);
	void __fastcall SetPropInfo(const System::Typinfo::PPropInfo Value);
	
protected:
	bool __fastcall DoOnExecuteEvent(void);
	
public:
	__fastcall virtual TatEventDispatcher(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatEventDispatcher(void);
	void __fastcall Unset(void);
	TatScripterEventBroker* __fastcall EventBroker(void);
	__property TatCustomScripter* Scripter = {read=FScripter, write=SetScripter};
	__property TatScript* Script = {read=FScript, write=FScript};
	__property System::TMethod BeforeCall = {read=FBeforeCall, write=SetBeforeCall};
	__property System::TMethod AfterCall = {read=FAfterCall, write=SetAfterCall};
	__property System::TMethod OldCall = {read=FOldCall, write=SetOldCall};
	__property System::UnicodeString RoutineName = {read=FRoutineName, write=FRoutineName};
	__property TatEventAdapter* Adapter = {read=FAdapter, write=SetAdapter};
	__property System::TObject* Instance = {read=FInstance, write=SetInstance};
	__property System::Typinfo::PPropInfo PropInfo = {read=FPropInfo, write=SetPropInfo};
	__property System::TMethod CustomCall = {read=FCustomCall, write=FCustomCall};
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TatDispatcherRemoveNotificator : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TatEventDispatcher* FDispatcher;
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
public:
	/* TComponent.Create */ inline __fastcall virtual TatDispatcherRemoveNotificator(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TatDispatcherRemoveNotificator(void) { }
	
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TatDebugWatches : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TatDebugWatch* operator[](int i) { return Items[i]; }
	
private:
	HIDESBASE TatDebugWatch* __fastcall GetItem(int i);
	
public:
	HIDESBASE TatDebugWatch* __fastcall Add(void);
	__property TatDebugWatch* Items[int i] = {read=GetItem/*, default*/};
	void __fastcall Reset(void);
	void __fastcall CompileAndEvaluateAll(void);
	void __fastcall EvaluateAll(void);
	void __fastcall Evaluate(TatDebugWatch* AWatch);
	void __fastcall CompileAndEvaluate(TatDebugWatch* AWatch);
public:
	/* TOwnedCollection.Create */ inline __fastcall TatDebugWatches(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TatDebugWatches(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TatDebugWatch : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FExpression;
	TatScript* FDebugScript;
	System::Variant FLastResult;
	TWatchStatus FWatchStatus;
	bool FAlwaysCompile;
	bool FEnabled;
	bool FResultChanged;
	void __fastcall SetLastResult(const System::Variant &Value);
	void __fastcall Reset(void);
	void __fastcall SetExpression(const System::UnicodeString Value);
	void __fastcall ScriptDestroyed(System::TObject* Sender);
	
public:
	__fastcall virtual TatDebugWatch(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TatDebugWatch(void);
	void __fastcall CompileAndEvaluate(void);
	TatVirtualMachine* __fastcall Machine(void);
	void __fastcall Evaluate(void);
	void __fastcall FullEvaluate(void);
	__property System::UnicodeString Expression = {read=FExpression, write=SetExpression};
	__property TatScript* DebugScript = {read=FDebugScript, write=FDebugScript};
	__property TWatchStatus WatchStatus = {read=FWatchStatus, write=FWatchStatus, nodefault};
	__property System::Variant LastResult = {read=FLastResult, write=SetLastResult};
	__property bool ResultChanged = {read=FResultChanged, write=FResultChanged, nodefault};
	__property bool AlwaysCompile = {read=FAlwaysCompile, write=FAlwaysCompile, nodefault};
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
};


class DELPHICLASS TGenericEventDispatcher;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGenericEventDispatcher : public TatEventDispatcher
{
	typedef TatEventDispatcher inherited;
	
public:
	void __fastcall RaiseEvent(void);
public:
	/* TatEventDispatcher.Create */ inline __fastcall virtual TGenericEventDispatcher(System::Classes::TCollection* ACollection) : TatEventDispatcher(ACollection) { }
	/* TatEventDispatcher.Destroy */ inline __fastcall virtual ~TGenericEventDispatcher(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGenericRecordWrapper;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGenericRecordWrapper : public TatRecordWrapper
{
	typedef TatRecordWrapper inherited;
	
private:
	System::Typinfo::TTypeInfo *FTypeInfo;
	System::Rtti::TRttiRecordType* FRecord;
	System::Rtti::TValue __fastcall GetFieldValue(System::UnicodeString AFieldName);
	void __fastcall SetFieldValue(System::UnicodeString AFieldName, const System::Rtti::TValue &AValue);
	
public:
	__fastcall TGenericRecordWrapper(System::Typinfo::PTypeInfo ATypeInfo);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TGenericRecordWrapper(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TCodeCOmpletionEntry;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TCodeCOmpletionEntry : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FToken;
	System::UnicodeString FValue;
	
public:
	__property System::UnicodeString Token = {read=FToken, write=FToken};
	__property System::UnicodeString Value = {read=FValue, write=FValue};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TCodeCOmpletionEntry(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TCodeCOmpletionEntry(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TCodeCompletionEntries;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TCodeCompletionEntries : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TCodeCOmpletionEntry* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TCodeCOmpletionEntry* __fastcall GetItem(int Index);
	
public:
	__fastcall TCodeCompletionEntries(void);
	HIDESBASE TCodeCOmpletionEntry* __fastcall Add(System::UnicodeString AToken, System::UnicodeString AValue);
	__property TCodeCOmpletionEntry* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TCodeCompletionEntries(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TCodeInsightContext;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TCodeInsightContext : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCodeCompletionEntries* FLastEntries;
	System::UnicodeString FLastUsedToken;
	
public:
	__fastcall TCodeInsightContext(void);
	__fastcall virtual ~TCodeInsightContext(void);
	__property TCodeCompletionEntries* LastEntries = {read=FLastEntries};
	__property System::UnicodeString LastUsedToken = {read=FLastUsedToken, write=FLastUsedToken};
};

#pragma pack(pop)

struct DECLSPEC_DRECORD TIgnorePair
{
public:
	System::WideChar Open;
	System::WideChar Close;
};


class DELPHICLASS TScripterCodeInsight;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TScripterCodeInsight : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	typedef System::DynamicArray<int> _TScripterCodeInsight__1;
	
	typedef System::DynamicArray<TIgnorePair> _TScripterCodeInsight__2;
	
	
private:
	TatScript* FScript;
	_TScripterCodeInsight__1 FIgnoreLevel;
	_TScripterCodeInsight__2 FIgnorePairs;
	TCodeInsightContext* FContext;
	TIgnorePair __fastcall DoPair(System::WideChar Open, System::WideChar Close);
	void __fastcall SetIgnorePairs(TIgnorePair const *APairs, const int APairs_High);
	int __fastcall IgnoreCount(void);
	void __fastcall FillMatchingItems(TatClass* AClass, System::UnicodeString AName, System::Classes::TStrings* AList);
	void __fastcall FillAllMatchingItems(TatClass* AClass, System::UnicodeString AName, System::Classes::TStrings* AList);
	TatClass* __fastcall FindResultClass(TatClass* AClass, System::UnicodeString AName);
	TatClass* __fastcall FindAnyResultClass(TatClass* AClass, System::UnicodeString AName);
	__classmethod bool __fastcall IsClassDefaultInstance(TatClass* AClass);
	void __fastcall AddItemToList(System::Classes::TStrings* AList, System::UnicodeString AClassName, System::UnicodeString AName, System::TObject* AValue);
	System::UnicodeString __fastcall ExtractExpression(System::UnicodeString s, int pos);
	int __fastcall IgnoringIndex(void);
	System::WideChar __fastcall NextChar(System::UnicodeString s, int &pos);
	System::WideChar __fastcall PreviousChar(System::UnicodeString s, int &pos);
	System::Classes::TStringList* __fastcall SplitList(System::UnicodeString s, const System::UnicodeString sep);
	__classmethod void __fastcall ConvertListToOldStyle(System::Classes::TStrings* AList);
	System::Classes::TStringList* __fastcall GetCompletionListFromToken(System::UnicodeString AToken, bool AExactMatch, int &DefaultIndex);
	System::UnicodeString __fastcall GetParameterHintFromObject(System::TObject* obj);
	
public:
	__fastcall TScripterCodeInsight(TatScript* AScript);
	__fastcall virtual ~TScripterCodeInsight(void);
	bool __fastcall GetParameterHintInfo(System::UnicodeString AInputText, int AInputPos, System::UnicodeString &AToken, int &AParIndex);
	System::UnicodeString __fastcall GetParameterHint(System::UnicodeString AToken);
	System::Classes::TStringList* __fastcall GetCodeCompletion(System::UnicodeString AInputText, int AInputPos, int &DefaultIndex);
	System::Classes::TStringList* __fastcall CreateCodeCompletionList(System::UnicodeString AInputText, int AInputPos, int &DefaultIndex);
	__property TCodeInsightContext* Context = {read=FContext, write=FContext};
};

#pragma pack(pop)

typedef System::StaticArray<System::Variant, 5> Atscript__36;

typedef void __fastcall (__closure *TAddCodeCompletionItemEvent)(System::UnicodeString AClassName, System::UnicodeString &AName);

//-- var, const, procedure ---------------------------------------------------
static const System::Word StackSize = System::Word(0xbb8);
static const System::Int8 CODEFILE_VERSION = System::Int8(0x4);
static const System::Int8 CURRENT_VERSION = System::Int8(0x4);
#define DefaultTypeInfoFilter (System::Set<System::TTypeKind, System::TTypeKind::tkUnknown, System::TTypeKind::tkProcedure>() << System::TTypeKind::tkInteger << System::TTypeKind::tkChar << System::TTypeKind::tkEnumeration << System::TTypeKind::tkFloat << System::TTypeKind::tkString << System::TTypeKind::tkSet << System::TTypeKind::tkClass << System::TTypeKind::tkWChar << System::TTypeKind::tkLString << System::TTypeKind::tkWString << System::TTypeKind::tkVariant << System::TTypeKind::tkArray << System::TTypeKind::tkUString )
static const System::Int8 vtLongint = System::Int8(0x64);
static const System::Byte vtCardinal = System::Byte(0xc8);
static const System::Word vtLongword = System::Word(0x12c);
static const System::Word vtSingle = System::Word(0x190);
static const System::Word vtByte = System::Word(0x1f6);
static const System::Word vtShortint = System::Word(0x25a);
static const System::Word vtWord = System::Word(0x2c5);
static const System::Word vtSmallint = System::Word(0x329);
static const System::Word vtDouble = System::Word(0x390);
static const System::Word vtReal = System::Word(0x3f4);
static const System::Word vtDateTime = System::Word(0x458);
static const System::Word vtComp = System::Word(0x4bc);
extern DELPHI_PACKAGE TatLibraryList* atLibraryList;
extern DELPHI_PACKAGE Atscript__36 CoreConst;
extern DELPHI_PACKAGE System::Classes::TNotifyEvent OnGlobalScripterCreate;
extern DELPHI_PACKAGE System::Classes::TNotifyEvent OnGlobalScripterLoaded;
extern DELPHI_PACKAGE TAddCodeCompletionItemEvent OnGlobalAddCodeCompletionItem;
extern DELPHI_PACKAGE System::Variant __fastcall MakeVarByRef(System::Variant &v);
extern DELPHI_PACKAGE System::TObject* __fastcall VarToObject(const System::Variant &v);
extern DELPHI_PACKAGE double __fastcall StrVal(System::UnicodeString s);
extern DELPHI_PACKAGE int __fastcall VarToInteger(const System::Variant &v);
extern DELPHI_PACKAGE __int64 __fastcall VarToInt64(const System::Variant &v);
extern DELPHI_PACKAGE int __fastcall VarToEnumInteger(const System::Variant &v, System::Typinfo::PTypeInfo PropType);
extern DELPHI_PACKAGE int __fastcall VarToSet(const System::Variant &v, System::Typinfo::PTypeInfo PropType);
extern DELPHI_PACKAGE double __fastcall VarToFloat(const System::Variant &v);
extern DELPHI_PACKAGE bool __fastcall VarToBoolean(const System::Variant &v);
extern DELPHI_PACKAGE System::UnicodeString __fastcall VarContent(const System::Variant &v);
extern DELPHI_PACKAGE bool __fastcall AssignedMethod(const System::TMethod &m);
extern DELPHI_PACKAGE int __fastcall LineNumberFromInstruction(pSimplifiedCode inst);
extern DELPHI_PACKAGE int __fastcall ColNumberFromInstruction(pSimplifiedCode inst);
extern DELPHI_PACKAGE bool __fastcall InstructionIsExecutable(TatCustomScripter* script, pSimplifiedCode inst);
extern DELPHI_PACKAGE void __fastcall IntToSet(void *ASet, int AInt, int ASize = 0x4);
extern DELPHI_PACKAGE int __fastcall IntFromSet(void *ASet, int ASize = 0x4);
extern DELPHI_PACKAGE int __fastcall IntFromConstSet(const void *ASet);
extern DELPHI_PACKAGE void __fastcall ScriptInfoError(System::UnicodeString msg);
extern DELPHI_PACKAGE void __fastcall RaiseRuntimeError(System::UnicodeString msg);
extern DELPHI_PACKAGE void __fastcall DefinitionError(System::UnicodeString msg);
extern DELPHI_PACKAGE void __fastcall InternalError(System::UnicodeString msg);
extern DELPHI_PACKAGE System::Variant __fastcall EvaluateWatch(TatCustomScripter* AScripter, System::UnicodeString AExpression);
extern DELPHI_PACKAGE System::Classes::TStringList* __fastcall CreateCodeCompletionList(TatCustomScripter* AScripter, System::UnicodeString AInputText, int AInputPos, int &AExprPos, int &AExprLen)/* overload */;
extern DELPHI_PACKAGE System::Classes::TStringList* __fastcall CreateCodeCompletionList(TatScript* AScript, System::UnicodeString AInputText, int AInputPos, int &AExprPos, int &AExprLen)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterScripterLibrary(TatScripterLibraryClass ALibrary, bool AExplicitLoad = false);
extern DELPHI_PACKAGE void __fastcall UnregisterScripterLibrary(TatScripterLibraryClass ALibrary);
extern DELPHI_PACKAGE TatEventAdapter* __fastcall DefineEventAdapter(System::Typinfo::PTypeInfo ARttiInfo, TDispatcherClass ADispatcherClass, void * AMethodCode, bool ACheck = true);
}	/* namespace Atscript */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ATSCRIPT)
using namespace Atscript;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AtscriptHPP
