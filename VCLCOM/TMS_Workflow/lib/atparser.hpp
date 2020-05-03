// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'atParser.pas' rev: 28.00 (Windows)

#ifndef AtparserHPP
#define AtparserHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Atparser
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TSyntaxResult : unsigned char { srNotDefined, srCorrect, srIncomplete, srOverFlow, srIncorrect };

class DELPHICLASS EParserError;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EParserError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EParserError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EParserError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EParserError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EParserError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EParserError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EParserError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EParserError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EParserError(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParserError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParserError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParserError(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParserError(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EParserError(void) { }
	
};

#pragma pack(pop)

struct DECLSPEC_DRECORD TParsingResults
{
public:
	TSyntaxResult Result;
	System::WideChar Suggestion;
	int InputPos;
	int SyntaxPos;
	int NoTerminalIndex;
	int MaxInputPos;
	TSyntaxResult LastResult;
};


class DELPHICLASS TNoTerminalNode;
typedef void __fastcall (__closure *TNodeScanProc)(TNoTerminalNode* Node);

typedef System::UnicodeString __fastcall (__closure *TNodeStringChangeProc)(TNoTerminalNode* Node);

typedef bool __fastcall (__closure *TAcceptNodeProc)(TNoTerminalNode* Node);

typedef bool __fastcall (__closure *TAcceptCharProc)(TNoTerminalNode* Node, int ACurrentPos);

class DELPHICLASS TatSyntaxParser;
typedef void __fastcall (__closure *TExtractRemarkEvent)(TatSyntaxParser* AParser, int AStartPos, int AFinalPos);

typedef void __fastcall (__closure *TNodeNotifyEvent)(TNoTerminalNode* Node);

class DELPHICLASS TInclude;
typedef void __fastcall (__closure *TRefuseInputEvent)(TInclude* AInclude, int AInputPos);

typedef void __fastcall (__closure *TIncludeInputEvent)(TatSyntaxParser* const AParser, const System::UnicodeString AName, System::UnicodeString &AInputBuffer, System::TObject* &AInfoObject);

class DELPHICLASS TNoTerminal;
class DELPHICLASS TNoTerminals;
class PASCALIMPLEMENTATION TNoTerminal : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FIdS;
	System::UnicodeString FSyntax;
	System::UnicodeString FSyntaxText;
	TNodeScanProc FOnBeforeNodeScan;
	TNodeScanProc FOnAfterNodeScan;
	TAcceptNodeProc FOnAcceptNode;
	TAcceptCharProc FOnAcceptCharacter;
	TNodeStringChangeProc FOnNodeStringChange;
	bool FReverseScanning;
	TNoTerminals* __fastcall GetNoTerminals(void);
	
public:
	void __fastcall AssignNodeScanningEvents(TNodeScanProc AOnBeforeNodeScan, TNodeScanProc AOnAfterNodeScan);
	__property System::UnicodeString IdS = {read=FIdS, write=FIdS};
	__property System::UnicodeString Syntax = {read=FSyntax, write=FSyntax};
	__property System::UnicodeString SyntaxText = {read=FSyntaxText, write=FSyntaxText};
	__property TNodeScanProc OnBeforeNodeScan = {read=FOnBeforeNodeScan, write=FOnBeforeNodeScan};
	__property TNodeScanProc OnAfterNodeScan = {read=FOnAfterNodeScan, write=FOnAfterNodeScan};
	__property bool ReverseScanning = {read=FReverseScanning, write=FReverseScanning, nodefault};
	__property TAcceptNodeProc OnAcceptNode = {read=FOnAcceptNode, write=FOnAcceptNode};
	__property TAcceptCharProc OnAcceptCharacter = {read=FOnAcceptCharacter, write=FOnAcceptCharacter};
	__property TNodeStringChangeProc OnNodeStringChange = {read=FOnNodeStringChange, write=FOnNodeStringChange};
	__property TNoTerminals* NoTerminals = {read=GetNoTerminals};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TNoTerminal(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TNoTerminal(void) { }
	
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TNoTerminals : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TNoTerminal* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TNoTerminal* __fastcall GetItem(int Index);
	
public:
	__fastcall TNoTerminals(void);
	HIDESBASE TNoTerminal* __fastcall Add(System::UnicodeString AIdS, System::UnicodeString ASyntax);
	HIDESBASE void __fastcall Delete(int i);
	int __fastcall IndexOf(System::UnicodeString IdS);
	void __fastcall LoadFromStrings(System::Classes::TStrings* List);
	__property TNoTerminal* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TNoTerminals(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TNoTerminalNodes;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TNoTerminalNode : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
public:
	TNoTerminalNode* operator[](int i) { return Items[i]; }
	
private:
	int FNoTerminalIndex;
	int FInputInitialPos;
	int FInputFinalPos;
	TNoTerminalNodes* FNodes;
	TatSyntaxParser* FatSyntaxParser;
	TInclude* FInclude;
	System::UnicodeString __fastcall GetInputToken(void);
	TNoTerminalNodes* __fastcall GetOwnerNodes(void);
	TNoTerminal* __fastcall GetNoTerminal(void);
	TNoTerminalNode* __fastcall GetParentNode(void);
	System::WideChar __fastcall GetInputChar(int i);
	int __fastcall GetFinalPos(void);
	int __fastcall GetInitialPos(void);
	int __fastcall GetTokenLength(void);
	void __fastcall SetFinalPos(const int Value);
	void __fastcall SetInitialPos(const int Value);
	void __fastcall SetTokenLength(const int Value);
	TNoTerminalNode* __fastcall GetItem(int i);
	void __fastcall MoveByOffset(int delta);
	void __fastcall SetInputFinalPos(const int Value);
	void __fastcall SetInputInitialPos(const int Value);
	System::UnicodeString __fastcall GetStrToken(void);
	
public:
	__fastcall virtual TNoTerminalNode(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TNoTerminalNode(void);
	void __fastcall ChangeNodeString(System::UnicodeString s);
	__property TNoTerminalNodes* OwnerNodes = {read=GetOwnerNodes};
	__property TNoTerminalNode* ParentNode = {read=GetParentNode};
	__property int NoTerminalIndex = {read=FNoTerminalIndex, write=FNoTerminalIndex, nodefault};
	__property int InputInitialPos = {read=FInputInitialPos, write=SetInputInitialPos, nodefault};
	__property int InputFinalPos = {read=FInputFinalPos, write=SetInputFinalPos, nodefault};
	__property TNoTerminalNodes* Nodes = {read=FNodes, write=FNodes};
	__property System::UnicodeString InputToken = {read=GetInputToken};
	__property System::UnicodeString StrToken = {read=GetStrToken};
	__property TatSyntaxParser* atSyntaxParser = {read=FatSyntaxParser};
	__property TNoTerminal* NoTerminal = {read=GetNoTerminal};
	__property System::WideChar InputChar[int i] = {read=GetInputChar};
	__property int InitialPos = {read=GetInitialPos, write=SetInitialPos, nodefault};
	__property int FinalPos = {read=GetFinalPos, write=SetFinalPos, nodefault};
	__property int TokenLenght = {read=GetTokenLength, write=SetTokenLength, nodefault};
	__property TNoTerminalNode* Items[int i] = {read=GetItem/*, default*/};
	__property TInclude* Include = {read=FInclude};
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TNoTerminalNodes : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TNoTerminalNode* operator[](int i) { return Items[i]; }
	
private:
	TNoTerminalNode* FNode;
	HIDESBASE TNoTerminalNode* __fastcall GetItem(int i);
	
public:
	__fastcall TNoTerminalNodes(TNoTerminalNode* Owner);
	HIDESBASE TNoTerminalNode* __fastcall Add(int NoTermIndex);
	HIDESBASE void __fastcall Delete(int i);
	int __fastcall IndexOf(int NoTerminalIndex);
	TNoTerminalNode* __fastcall FindByNoTerminalName(const System::UnicodeString AName);
	__property TNoTerminalNode* Node = {read=FNode, write=FNode};
	__property TNoTerminalNode* Items[int i] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TNoTerminalNodes(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TSyntaxComment;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TSyntaxComment : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FOpenString;
	System::UnicodeString FCloseString;
	System::UnicodeString FPriorDelims;
	
public:
	__property System::UnicodeString OpenString = {read=FOpenString, write=FOpenString};
	__property System::UnicodeString CloseString = {read=FCloseString, write=FCloseString};
	__property System::UnicodeString PriorDelims = {read=FPriorDelims, write=FPriorDelims};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TSyntaxComment(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TSyntaxComment(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TSyntaxComments;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TSyntaxComments : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TSyntaxComment* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TSyntaxComment* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TSyntaxComment* __fastcall Add(System::UnicodeString AOpenString, System::UnicodeString ACloseString);
	__property TSyntaxComment* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TSyntaxComments(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TSyntaxComments(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TSavedInputs;
class DELPHICLASS TIncludes;
class PASCALIMPLEMENTATION TatSyntaxParser : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	typedef System::StaticArray<System::UnicodeString, 10> _TatSyntaxParser__1;
	
	
private:
	bool FParsing;
	int FBranchCount;
	TNoTerminalNode* FNode;
	TNoTerminals* FNoTerminals;
	System::UnicodeString FSyntax;
	System::Classes::TStrings* FGrammar;
	System::UnicodeString FInput;
	System::Classes::TStrings* FStrings;
	int FScanningInputPos;
	bool FDisableBranching;
	System::WideChar FStringDelimitter;
	_TatSyntaxParser__1 FCustomLexemes;
	int FCurrentInputPos;
	int FCurrentMaxInputPos;
	TSyntaxComments* FComments;
	TExtractRemarkEvent FOnExtractRemark;
	TNodeNotifyEvent FOnRefuseNode;
	TRefuseInputEvent FOnRefuseRemarks;
	bool FContinueOnRemarks;
	TIncludeInputEvent FOnIncludeInput;
	TSavedInputs* FSavedInputs;
	TInclude* FCurrentInclude;
	bool FProcessingRemarks;
	TIncludes* FIncludes;
	int FLastRemarkFound;
	TNodeNotifyEvent FOnNewNode;
	System::Contnrs::TObjectList* FTempNodes;
	void __fastcall SetGrammar(System::Classes::TStrings* Value);
	void __fastcall SetStrings(System::Classes::TStrings* Value);
	bool __fastcall ParseInput(TNoTerminalNodes* Nodes, System::UnicodeString Syntax, int InputPosition, bool literal, int CurrentNoTerm, TParsingResults &results);
	void __fastcall GrammarChange(System::TObject* Sender);
	void __fastcall StringsChange(System::TObject* Sender);
	void __fastcall SetDisableBranching(const bool Value);
	void __fastcall SetContinueOnRemarks(const bool Value);
	void __fastcall SetCurrentInputPos(const int Value);
	void __fastcall SetCurrentMaxInputPos(const int Value);
	void __fastcall SetInput(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetCustomLexeme(int i);
	void __fastcall SetCustomLexeme(int i, const System::UnicodeString Value);
	void __fastcall SetOnNewNode(const TNodeNotifyEvent Value);
	
protected:
	void __fastcall ChangePositions(TNoTerminalNode* refnode, int delta, bool ignoresubnodes);
	__property System::UnicodeString Syntax = {read=FSyntax};
	
public:
	__fastcall virtual TatSyntaxParser(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TatSyntaxParser(void);
	void __fastcall Clear(void);
	TParsingResults __fastcall CheckLanguage(void);
	TParsingResults __fastcall CheckExpression(void);
	void __fastcall BuildSyntaxTreeView(Vcl::Comctrls::TTreeView* TreeView);
	void __fastcall ScanNode(TNoTerminalNode* ANode);
	bool __fastcall ScanSyntaxTree(void);
	System::UnicodeString __fastcall RebuildFromNodes(void);
	TNoTerminalNode* __fastcall FindNodeByPosition(int p);
	bool __fastcall TestInputString(int APos, System::UnicodeString s, bool ACaseSensitive = false);
	__property int Effort = {read=FBranchCount, nodefault};
	__property TNoTerminals* NoTerminals = {read=FNoTerminals};
	__property TNoTerminalNode* Node = {read=FNode};
	__property System::Classes::TStrings* Grammar = {read=FGrammar, write=SetGrammar};
	__property System::Classes::TStrings* Strings = {read=FStrings, write=SetStrings};
	__property int ScanningInputPos = {read=FScanningInputPos, nodefault};
	__property System::UnicodeString Input = {read=FInput, write=SetInput};
	__property bool DisableBranching = {read=FDisableBranching, write=SetDisableBranching, nodefault};
	__property bool Parsing = {read=FParsing, nodefault};
	__property System::UnicodeString CustomLexemes[int i] = {read=GetCustomLexeme, write=SetCustomLexeme};
	void __fastcall IncludeInput(System::UnicodeString AName);
	__property bool ProcessingRemarks = {read=FProcessingRemarks, nodefault};
	__property TSyntaxComments* Comments = {read=FComments};
	__property System::WideChar StringDelimitter = {read=FStringDelimitter, write=FStringDelimitter, nodefault};
	__property bool ContinueOnRemarks = {read=FContinueOnRemarks, write=SetContinueOnRemarks, nodefault};
	__property TExtractRemarkEvent OnExtractRemark = {read=FOnExtractRemark, write=FOnExtractRemark};
	__property TNodeNotifyEvent OnRefuseNode = {read=FOnRefuseNode, write=FOnRefuseNode};
	__property TRefuseInputEvent OnRefuseRemarks = {read=FOnRefuseRemarks, write=FOnRefuseRemarks};
	__property TIncludeInputEvent OnIncludeInput = {read=FOnIncludeInput, write=FOnIncludeInput};
	__property int CurrentInputPos = {read=FCurrentInputPos, write=SetCurrentInputPos, nodefault};
	__property int CurrentMaxInputPos = {read=FCurrentMaxInputPos, write=SetCurrentMaxInputPos, nodefault};
	__property TInclude* CurrentInclude = {read=FCurrentInclude};
	
__published:
	__property TNodeNotifyEvent OnNewNode = {read=FOnNewNode, write=SetOnNewNode};
};


class DELPHICLASS TSavedInput;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TSavedInputs : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TSavedInput* operator[](int i) { return Items[i]; }
	
private:
	TSavedInput* __fastcall GetItems(int i);
	
public:
	HIDESBASE TSavedInput* __fastcall Add(void);
	__property TSavedInput* Items[int i] = {read=GetItems/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TSavedInputs(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TSavedInputs(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TSavedInput : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TInclude* FSavedInclude;
	int FSavedInputPosition;
	int FSavedMaxInputPosition;
	System::UnicodeString FSavedInputBuffer;
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TSavedInput(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TSavedInput(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TIncludes : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TInclude* operator[](int i) { return Items[i]; }
	
private:
	TInclude* __fastcall GetItems(int i);
	
public:
	HIDESBASE TInclude* __fastcall Add(void);
	__property TInclude* Items[int i] = {read=GetItems/*, default*/};
	int __fastcall IndexOf(System::UnicodeString AName);
	TInclude* __fastcall FindByName(System::UnicodeString AName);
public:
	/* TOwnedCollection.Create */ inline __fastcall TIncludes(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIncludes(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TInclude : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::TObject* FInfoObject;
	System::UnicodeString FInputBuffer;
	
public:
	__property System::UnicodeString Name = {read=FName};
	__property System::TObject* InfoObject = {read=FInfoObject};
	__property System::UnicodeString InputBuffer = {read=FInputBuffer};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TInclude(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TInclude(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define AllChars L"\u0000\u0001\u0002\u0003\u0004\u0005\u0006\a\b\t\n\v\f\r\u000e"\
	L"\u000f\u0010\u0011\u0012\u0013\u0014\u0015\u0016\u0017\u0018"\
	L"\u0019\u001a\u001b\u001c\u001d\u001e\u001f !\"#$%&'()*+,-."\
	L"/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefg"\
	L"hijklmnopqrstuvwxyz{|}~\u007f\u20ac\u4e97\u510e\u5397?\u5791"\
	L"\u59ba\u5be6\u5e0d\u609c\u6300\u6543\u679f\u69de\u6baf\u6e5e"\
	L"\u704d\u724e\u2172\u3045\u0397\u012b\ue00a\ue0c8\ue186\u6c28"\
	L"\u6e24\u5439\u6597\u8179\u592f\u5180\u7a76\u61d2\u65c5\u5450"\
	L"?\u4fa8\u5892\u9882\u81c0\u95f2\u5ca9\u91c9\u7f69\u68d5\u4edd"\
	L"\u572e\u8489\u54d9\u5f95\u6c85\u5f50\u73b7\u6b9b\u8171\u770d"\
	L"\u9573\u8031\u7bdd\u8c8a\u9f2c\ue2eb\ue3a9\ue467\uf8f5"
#define SpecialChars L"\u0000\u0001\u0002\u0003\u0004\u0005\u0006\a\b\t\n\v\f\r\u000e"\
	L"\u000f\u0010\u0011\u0012\u0013\u0014\u0015\u0016\u0017\u0018"\
	L"\u0019\u001a\u001b\u001c\u001d\u001e\u001f"
extern DELPHI_PACKAGE System::UnicodeString __fastcall SubtractChars(System::UnicodeString s, System::UnicodeString chars);
extern DELPHI_PACKAGE void __fastcall GetRowColFromStrings(System::Classes::TStrings* lines, int position, int &row, int &col);
}	/* namespace Atparser */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ATPARSER)
using namespace Atparser;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AtparserHPP
