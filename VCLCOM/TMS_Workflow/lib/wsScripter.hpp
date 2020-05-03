// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsScripter.pas' rev: 28.00 (Windows)

#ifndef WsscripterHPP
#define WsscripterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit
#include <atScript.hpp>	// Pascal unit
#include <atPascal.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <ap_wsClasses.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsBlocks.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsscripter
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EWorkflowScriptException;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EWorkflowScriptException : public Wsclasses::EWorkflowException
{
	typedef Wsclasses::EWorkflowException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWorkflowScriptException(const System::UnicodeString Msg) : Wsclasses::EWorkflowException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWorkflowScriptException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : Wsclasses::EWorkflowException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWorkflowScriptException(NativeUInt Ident)/* overload */ : Wsclasses::EWorkflowException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWorkflowScriptException(System::PResStringRec ResStringRec)/* overload */ : Wsclasses::EWorkflowException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWorkflowScriptException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : Wsclasses::EWorkflowException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWorkflowScriptException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : Wsclasses::EWorkflowException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWorkflowScriptException(const System::UnicodeString Msg, int AHelpContext) : Wsclasses::EWorkflowException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWorkflowScriptException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : Wsclasses::EWorkflowException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWorkflowScriptException(NativeUInt Ident, int AHelpContext)/* overload */ : Wsclasses::EWorkflowException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWorkflowScriptException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Wsclasses::EWorkflowException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWorkflowScriptException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : Wsclasses::EWorkflowException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWorkflowScriptException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : Wsclasses::EWorkflowException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWorkflowScriptException(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TScripterEngine;
class PASCALIMPLEMENTATION TScripterEngine : public Wsclasses::TWorkflowScriptEngine
{
	typedef Wsclasses::TWorkflowScriptEngine inherited;
	
private:
	Atscript::TatCustomScripter* FScripter;
	System::Contnrs::TObjectList* FVarProps;
	void __fastcall GetInsVariableProp(Atscript::TatVirtualMachine* AMachine);
	void __fastcall SetInsVariableProp(Atscript::TatVirtualMachine* AMachine);
	void __fastcall UnknownElementEvent(System::TObject* Sender, Atscript::TElementContext &Context);
	void __fastcall GetDefVariableProp(Atscript::TatVirtualMachine* AMachine);
	void __fastcall SetDefVariableProp(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetVariableProp(Atscript::TatVirtualMachine* AMachine, Wsclasses::TCustomWorkflowDiagram* ADiagram);
	void __fastcall SetVariableProp(Atscript::TatVirtualMachine* AMachine, Wsclasses::TCustomWorkflowDiagram* ADiagram);
	void __fastcall GetDefDiagramProp(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetInsDiagramProp(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetInsTaskProp(Atscript::TatVirtualMachine* AMachine);
	
protected:
	virtual void __fastcall RunContextChanged(void);
	
public:
	__fastcall virtual TScripterEngine(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TScripterEngine(void);
	virtual System::Variant __fastcall CalculateExpression(System::UnicodeString Expr);
	__property Atscript::TatCustomScripter* Scripter = {read=FScripter};
};


class DELPHICLASS TWorkflowScriptBlock;
class PASCALIMPLEMENTATION TWorkflowScriptBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
private:
	System::UnicodeString FSourceCode;
	TScripterEngine* FEngine;
	bool FForceRecompile;
	void __fastcall SetSourceCode(const System::UnicodeString Value);
	void __fastcall PrepareAndCompile(void);
	
protected:
	virtual Livediagram::TCustomLiveBlock* __fastcall ScanTransitions(void);
	
public:
	__fastcall virtual TWorkflowScriptBlock(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Link(void);
	__fastcall virtual ~TWorkflowScriptBlock(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DoExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	__property TScripterEngine* Engine = {read=FEngine};
	
__published:
	__property System::UnicodeString SourceCode = {read=FSourceCode, write=SetSourceCode};
	__property OnExecuteEx;
};


class DELPHICLASS TWorkflowScriptBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowScriptBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowScriptBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowScriptBlockEditor(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wsscripter */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSSCRIPTER)
using namespace Wsscripter;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsscripterHPP
