// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'LiveDiagram.pas' rev: 28.00 (Windows)

#ifndef LivediagramHPP
#define LivediagramHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Winapi.MMSystem.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Livediagram
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TLinkDirection : unsigned char { ldInput, ldOutput };

class DELPHICLASS TStateList;
class DELPHICLASS TCustomLiveBlock;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TStateList : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
private:
	System::Classes::TList* Transitions;
	TCustomLiveBlock* __fastcall GetBlock(int index);
	Atdiagram::TCustomDiagramLine* __fastcall GetLink(int index);
	
public:
	__fastcall TStateList(void);
	HIDESBASE int __fastcall Add(Atdiagram::TCustomDiagramLine* Transition, TCustomLiveBlock* aNext);
	virtual void __fastcall Clear(void);
	__fastcall virtual ~TStateList(void);
	__property Atdiagram::TCustomDiagramLine* Transition[int index] = {read=GetLink};
	__property TCustomLiveBlock* Block[int index] = {read=GetBlock};
};

#pragma pack(pop)

class DELPHICLASS TBlockColors;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TBlockColors : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TCustomLiveBlock* Owner;
	System::Uitypes::TColor FRunONColor;
	System::Uitypes::TColor FRunOFFColor;
	System::Uitypes::TColor FRunERRColor;
	void __fastcall SetFRunONColor(const System::Uitypes::TColor Value);
	void __fastcall SetFRunOFFColor(const System::Uitypes::TColor Value);
	void __fastcall SetFRunERRColor(const System::Uitypes::TColor Value);
	
public:
	__fastcall TBlockColors(TCustomLiveBlock* AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TColor RunONColor = {read=FRunONColor, write=SetFRunONColor, nodefault};
	__property System::Uitypes::TColor RunOFFColor = {read=FRunOFFColor, write=SetFRunOFFColor, nodefault};
	__property System::Uitypes::TColor RunERRColor = {read=FRunERRColor, write=SetFRunERRColor, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TBlockColors(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TWaitState : unsigned char { wsUndefined, wsNoWait, wsWaitAndSave };

class DELPHICLASS TExecutionPath;
struct DECLSPEC_DRECORD TExecuteNodeInfo
{
public:
	int Decision;
	int Error;
	System::UnicodeString ErrorMsg;
	TCustomLiveBlock* RealErrorNode;
	TCustomLiveBlock* NextNode;
	TWaitState WaitState;
	TExecutionPath* Path;
	System::TDateTime NextRunTime;
};


typedef void __fastcall (__closure *TExecuteEvent)(TCustomLiveBlock* Sender, int &Error, int &Decision);

typedef void __fastcall (__closure *TExecuteExEvent)(TCustomLiveBlock* Sender, TExecuteNodeInfo &ExecInfo);

enum DECLSPEC_DENUM TControlState : unsigned char { csEdit, csRunON, csRunOFF, csRunERR };

class DELPHICLASS TLiveDiagram;
class PASCALIMPLEMENTATION TCustomLiveBlock : public Atdiagram::TCustomDiagramBlock
{
	typedef Atdiagram::TCustomDiagramBlock inherited;
	
private:
	bool FPassThrough;
	TControlState FControlState;
	System::Uitypes::TColor FStoreColor;
	bool FStoreGradient;
	TBlockColors* FRunColors;
	bool FIsErrorHandler;
	bool FIsEndBlock;
	bool FIsStartBlock;
	TExecuteExEvent FOnExecuteEx;
	TStateList* FNextStates;
	TStateList* FPreviousStates;
	void __fastcall SetFControlState(const TControlState Value);
	void __fastcall SetFRunColors(TBlockColors* const Value);
	TLiveDiagram* __fastcall GetLiveDiagram(void);
	
protected:
	TCustomLiveBlock* FNext;
	TExecuteEvent FOnExecute;
	int __fastcall Anchoreds(void)/* overload */;
	int __fastcall Anchoreds(TLinkDirection adirection)/* overload */;
	TCustomLiveBlock* __fastcall GetNextAt(int ALinkNum);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual Diagramutils::TDotArray __fastcall SurroundRgn(void);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual TCustomLiveBlock* __fastcall GetNext(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, TLinkDirection Direction);
	virtual void __fastcall DoExecute(int &Error, int &Decision);
	virtual void __fastcall DoExecuteEx(TExecuteNodeInfo &ExecInfo);
	virtual void __fastcall ShowState(void);
	void __fastcall DrawCrossHairs(Vcl::Graphics::TCanvas* ACanvas, const Diagramutils::TSquare &ABlockRect);
	__property TStateList* NextStates = {read=FNextStates};
	__property TStateList* PreviousStates = {read=FPreviousStates};
	__property TLiveDiagram* LiveDiagram = {read=GetLiveDiagram};
	
public:
	__fastcall virtual TCustomLiveBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLiveBlock(void);
	virtual void __fastcall DoBeforeRun(void);
	virtual TCustomLiveBlock* __fastcall Execute(int &Error, int &Decision);
	virtual void __fastcall ExecuteEx(TExecuteNodeInfo &ExecInfo);
	bool __fastcall ValidateWire(Atdiagram::TCustomDiagramLine* aLine, TCustomLiveBlock* &aBlock, TLinkDirection Direction);
	void __fastcall BuildStateList(void);
	virtual bool __fastcall Link(void);
	__property bool IsErrorHandler = {read=FIsErrorHandler, write=FIsErrorHandler, nodefault};
	__property bool IsStartBlock = {read=FIsStartBlock, write=FIsStartBlock, nodefault};
	__property bool IsEndBlock = {read=FIsEndBlock, write=FIsEndBlock, nodefault};
	__property bool PassThrough = {read=FPassThrough, write=FPassThrough, nodefault};
	__property TControlState ControlState = {read=FControlState, write=SetFControlState, nodefault};
	__property TCustomLiveBlock* Next = {read=GetNext};
	__property TExecuteEvent OnExecute = {read=FOnExecute, write=FOnExecute};
	__property TExecuteExEvent OnExecuteEx = {read=FOnExecuteEx, write=FOnExecuteEx};
	
__published:
	__property TBlockColors* RunColors = {read=FRunColors, write=SetFRunColors};
	__property LinkPointStyle;
	__property Color;
	__property SelColor;
	__property Angle = {default=0};
	__property Brush;
	__property SelBrush;
	__property Pen;
	__property Strings;
	__property Alignment;
	__property VertAlign;
	__property ClipText;
	__property WordWrap;
	__property TextCells;
	__property Restrictions;
	__property Font;
	__property DiagramFont;
	__property MinWidth;
	__property MinHeight;
	__property Shadow;
	__property ShowHint;
	__property Hint = {default=0};
	__property ParentShowHint;
	__property Gradient;
	__property Bitmap;
	__property BitmapMode;
	__property BitmapTransparent;
	__property Cursor;
	__property StringData = {default=0};
	__property Visible;
	__property Layer;
	__property LayerName = {default=0};
	__property Transparency;
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TLiveLineJoin;
class PASCALIMPLEMENTATION TLiveLineJoin : public TCustomLiveBlock
{
	typedef TCustomLiveBlock inherited;
	
private:
	bool Finding;
	
protected:
	virtual TCustomLiveBlock* __fastcall GetNext(void);
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	
public:
	__fastcall virtual TLiveLineJoin(System::Classes::TComponent* AOwner);
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveLineJoin(void) { }
	
};


class DELPHICLASS TCustomLiveConnector;
class PASCALIMPLEMENTATION TCustomLiveConnector : public TCustomLiveBlock
{
	typedef TCustomLiveBlock inherited;
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TCustomLiveConnector(System::Classes::TComponent* AOwner);
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TCustomLiveConnector(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


class DELPHICLASS TLiveConnectorSource;
class PASCALIMPLEMENTATION TLiveConnectorSource : public TCustomLiveConnector
{
	typedef TCustomLiveConnector inherited;
	
private:
	bool Finding;
	
protected:
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, TLinkDirection Direction);
	virtual TCustomLiveBlock* __fastcall GetNext(void);
	
public:
	virtual bool __fastcall Link(void);
public:
	/* TCustomLiveConnector.Create */ inline __fastcall virtual TLiveConnectorSource(System::Classes::TComponent* AOwner) : TCustomLiveConnector(AOwner) { }
	
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveConnectorSource(void) { }
	
};


class DELPHICLASS TLiveConnectorTarget;
class PASCALIMPLEMENTATION TLiveConnectorTarget : public TCustomLiveConnector
{
	typedef TCustomLiveConnector inherited;
	
private:
	bool Finding;
	
protected:
	virtual TCustomLiveBlock* __fastcall GetNext(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, TLinkDirection Direction);
public:
	/* TCustomLiveConnector.Create */ inline __fastcall virtual TLiveConnectorTarget(System::Classes::TComponent* AOwner) : TCustomLiveConnector(AOwner) { }
	
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveConnectorTarget(void) { }
	
};


class DELPHICLASS TForkThread;
class DELPHICLASS TExecutionPaths;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TExecutionPath : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	int FExitCode;
	System::UnicodeString FRunErrorMsg;
	int FRunError;
	TWaitState FWaitState;
	TCustomLiveBlock* FErrorNode;
	TForkThread* FExecuteThread;
	TCustomLiveBlock* FLastNode;
	TCustomLiveBlock* FNextNode;
	TCustomLiveBlock* FStartNode;
	bool FFinished;
	System::UnicodeString FLastNodeStr;
	System::UnicodeString FNextNodeStr;
	System::UnicodeString FStartNodeStr;
	bool FDeleteFlag;
	System::TObject* FDataObj;
	System::UnicodeString FDataStr;
	TExecutionPath* FParentPath;
	TExecutionPaths* __fastcall Paths(void);
	TLiveDiagram* __fastcall Diagram(void);
	void __fastcall DoOnShift(TCustomLiveBlock* OldBlock, TCustomLiveBlock* NewBlock);
	void __fastcall OnTerminateForkThread(System::TObject* Sender);
	void __fastcall ExecuteNode(void);
	System::UnicodeString __fastcall GetLastNodeStr(void);
	System::UnicodeString __fastcall GetNextNodeStr(void);
	System::UnicodeString __fastcall GetStartNodeStr(void);
	
public:
	__property TExecutionPath* ParentPath = {read=FParentPath};
	__property System::UnicodeString DataStr = {read=FDataStr, write=FDataStr};
	__property System::TObject* DataObj = {read=FDataObj, write=FDataObj};
	
__published:
	__property int ExitCode = {read=FExitCode, write=FExitCode, nodefault};
	__property int RunError = {read=FRunError, write=FRunError, nodefault};
	__property TWaitState WaitState = {read=FWaitState, write=FWaitState, nodefault};
	__property bool Finished = {read=FFinished, write=FFinished, nodefault};
	__property System::UnicodeString NextNodeStr = {read=GetNextNodeStr, write=FNextNodeStr};
	__property System::UnicodeString LastNodeStr = {read=GetLastNodeStr, write=FLastNodeStr};
	__property System::UnicodeString StartNodeStr = {read=GetStartNodeStr, write=FStartNodeStr};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TExecutionPath(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TExecutionPath(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TLiveForkBlock;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TExecutionPaths : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TExecutionPath* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TExecutionPath* __fastcall GetItem(int Index);
	
protected:
	TLiveForkBlock* __fastcall Block(void);
	
public:
	HIDESBASE TExecutionPath* __fastcall Add(void);
	TExecutionPath* __fastcall FindStart(TCustomLiveBlock* aBlock);
	__property TExecutionPath* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TExecutionPaths(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TExecutionPaths(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TForkThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	TExecutionPath* FPath;
	
public:
	__fastcall TForkThread(TExecutionPath* aPath);
	void __fastcall DoFinish(int aExitCode);
	virtual void __fastcall Execute(void);
	__fastcall virtual ~TForkThread(void);
};


class PASCALIMPLEMENTATION TLiveForkBlock : public TCustomLiveBlock
{
	typedef TCustomLiveBlock inherited;
	
private:
	TExecutionPaths* FPaths;
	bool FThreadsCreated;
	TExecutionPath* FErrorPath;
	System::Classes::TList* FSubThreads;
	bool __fastcall AllPathsTerminatedOk(void);
	void __fastcall TerminateSubThreads(void);
	bool __fastcall ForkLinkIsOk(void);
	void __fastcall LoadPathsProp(System::Classes::TReader* Reader);
	void __fastcall StorePathsProp(System::Classes::TWriter* Writer);
	
protected:
	virtual void __fastcall DoPathStart(TExecutionPath* APath);
	virtual void __fastcall DoPathTerminate(TExecutionPath* APath);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, TLinkDirection Direction);
	
public:
	__fastcall virtual TLiveForkBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLiveForkBlock(void);
	virtual void __fastcall DoBeforeRun(void);
	virtual void __fastcall ExecuteEx(TExecuteNodeInfo &ExecInfo);
	virtual bool __fastcall Link(void);
};


class DELPHICLASS TLiveJoinBlock;
class PASCALIMPLEMENTATION TLiveJoinBlock : public TCustomLiveBlock
{
	typedef TCustomLiveBlock inherited;
	
protected:
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, TLinkDirection Direction);
	virtual void __fastcall UpdateLinkPoints(void);
	
public:
	__fastcall virtual TLiveJoinBlock(System::Classes::TComponent* AOwner);
	virtual void __fastcall ExecuteEx(TExecuteNodeInfo &ExecInfo);
	virtual bool __fastcall Link(void);
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveJoinBlock(void) { }
	
};


typedef bool __fastcall (__closure *TTransitionEvent)(Atdiagram::TCustomDiagramLine* Sender, TCustomLiveBlock* FromBlock);

class DELPHICLASS TLiveWire;
class PASCALIMPLEMENTATION TLiveWire : public Atdiagram::TDiagramLine
{
	typedef Atdiagram::TDiagramLine inherited;
	
private:
	TTransitionEvent FOnTransition;
	
protected:
	virtual void __fastcall PaintControl(const Atdiagram::TDiagramDrawInfo &AInfo);
	virtual void __fastcall RecalcTextCells(void);
	virtual bool __fastcall DoTransition(TCustomLiveBlock* Sender);
	
public:
	__fastcall virtual TLiveWire(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Transition(TCustomLiveBlock* Sender);
	
__published:
	__property TTransitionEvent OnTransition = {read=FOnTransition, write=FOnTransition};
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TLiveWire(void) { }
	
};


class DELPHICLASS TLiveSideWire;
class PASCALIMPLEMENTATION TLiveSideWire : public Atdiagram::TDiagramSideLine
{
	typedef Atdiagram::TDiagramSideLine inherited;
	
private:
	TTransitionEvent FOnTransition;
	
protected:
	virtual void __fastcall PaintControl(const Atdiagram::TDiagramDrawInfo &AInfo);
	virtual void __fastcall RecalcTextCells(void);
	virtual bool __fastcall DoTransition(TCustomLiveBlock* Sender);
	
public:
	__fastcall virtual TLiveSideWire(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Transition(TCustomLiveBlock* Sender);
	
__published:
	__property TTransitionEvent OnTransition = {read=FOnTransition, write=FOnTransition};
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TLiveSideWire(void) { }
	
};


class DELPHICLASS TLiveArc;
class PASCALIMPLEMENTATION TLiveArc : public Atdiagram::TDiagramArc
{
	typedef Atdiagram::TDiagramArc inherited;
	
private:
	TTransitionEvent FOnTransition;
	
protected:
	virtual void __fastcall PaintControl(const Atdiagram::TDiagramDrawInfo &AInfo);
	virtual void __fastcall RecalcTextCells(void);
	virtual bool __fastcall DoTransition(TCustomLiveBlock* Sender);
	
public:
	__fastcall virtual TLiveArc(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Transition(TCustomLiveBlock* Sender);
	
__published:
	__property TTransitionEvent OnTransition = {read=FOnTransition, write=FOnTransition};
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TLiveArc(void) { }
	
};


class DELPHICLASS TLiveBezier;
class PASCALIMPLEMENTATION TLiveBezier : public Atdiagram::TDiagramBezier
{
	typedef Atdiagram::TDiagramBezier inherited;
	
private:
	TTransitionEvent FOnTransition;
	
protected:
	virtual void __fastcall PaintControl(const Atdiagram::TDiagramDrawInfo &AInfo);
	virtual void __fastcall RecalcTextCells(void);
	virtual bool __fastcall DoTransition(TCustomLiveBlock* Sender);
	
public:
	__fastcall virtual TLiveBezier(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Transition(TCustomLiveBlock* Sender);
	
__published:
	__property TTransitionEvent OnTransition = {read=FOnTransition, write=FOnTransition};
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TLiveBezier(void) { }
	
};


class DELPHICLASS TDiagramThread;
class PASCALIMPLEMENTATION TDiagramThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	TLiveDiagram* FDiagram;
	
public:
	__fastcall TDiagramThread(TLiveDiagram* aDiagram);
public:
	/* TThread.Destroy */ inline __fastcall virtual ~TDiagramThread(void) { }
	
};


class DELPHICLASS TExecuteThread;
class PASCALIMPLEMENTATION TExecuteThread : public TDiagramThread
{
	typedef TDiagramThread inherited;
	
public:
	void __fastcall DoFinish(int aExitCode);
	virtual void __fastcall Execute(void);
	__fastcall virtual ~TExecuteThread(void);
public:
	/* TDiagramThread.Create */ inline __fastcall TExecuteThread(TLiveDiagram* aDiagram) : TDiagramThread(aDiagram) { }
	
};


class DELPHICLASS TVisualThread;
class PASCALIMPLEMENTATION TVisualThread : public TDiagramThread
{
	typedef TDiagramThread inherited;
	
public:
	virtual void __fastcall Execute(void);
	__fastcall virtual ~TVisualThread(void);
public:
	/* TDiagramThread.Create */ inline __fastcall TVisualThread(TLiveDiagram* aDiagram) : TDiagramThread(aDiagram) { }
	
};


typedef void __fastcall (__closure *TRunErrorEvent)(TLiveDiagram* Sender, TCustomLiveBlock* Block, int &Error, bool &ResumeNext);

enum DECLSPEC_DENUM TStartMode : unsigned char { smCold, smWarm, smContinue };

typedef void __fastcall (__closure *TStartEvent)(TLiveDiagram* Sender, TStartMode StartMode);

typedef void __fastcall (__closure *TShiftEvent)(TLiveDiagram* Sender, TCustomLiveBlock* OldBlock, TCustomLiveBlock* NewBlock);

typedef void __fastcall (__closure *TTerminateEvent)(TLiveDiagram* Sender, int ExitCode);

enum DECLSPEC_DENUM TDiagramState : unsigned char { dsEdit, dsRunning, dsPaused, dsView };

enum DECLSPEC_DENUM TDiagramAction : unsigned char { daRun, daRunPaused, daPause, daStop, daForceStop, daReset, daStep, daContinue, daContinuePaused };

typedef void __fastcall (__closure *TChangeStateEvent)(TLiveDiagram* Sender, TDiagramState NewState);

enum DECLSPEC_DENUM TViewStateMode : unsigned char { vmStart, vmRun, vmEnd };

class PASCALIMPLEMENTATION TLiveDiagram : public Atdiagram::TatDiagram
{
	typedef Atdiagram::TatDiagram inherited;
	
private:
	int FRunError;
	System::UnicodeString FRunErrorMsg;
	bool Linked;
	TDiagramState FState;
	TExecuteThread* ExecuteThread;
	TVisualThread* VisualThread;
	System::Classes::TList* FLiveds;
	TRunErrorEvent FOnRunError;
	int FExitCode;
	bool FStoreShowLinkPts;
	bool FStoreSnapGrid;
	System::Uitypes::TColor FStoreColor;
	System::Uitypes::TColor FRunColor;
	unsigned FSleepVisual;
	unsigned FIdlePercent;
	TTerminateEvent FOnTerminate;
	TStartEvent FOnStart;
	TChangeStateEvent FOnChangeState;
	TShiftEvent FOnShift;
	System::Classes::TNotifyEvent FOnMouseLeave;
	System::Classes::TNotifyEvent FOnMouseEnter;
	TWaitState FWaitState;
	System::Classes::TNotifyEvent FOnSaveState;
	System::Classes::TNotifyEvent FOnLoadState;
	bool FSavingState;
	System::UnicodeString FNextNodeStr;
	System::UnicodeString FLastNodeStr;
	System::UnicodeString FErrorNodeStr;
	System::Classes::TList* FSubThreads;
	bool FCanResumeNext;
	TViewStateMode FViewStateMode;
	TCustomLiveBlock* FStart;
	TCustomLiveBlock* FEnd;
	unsigned FMaximumIdle;
	void __fastcall SetFState(const TDiagramState Value);
	void __fastcall SetFSleepVisual(const unsigned Value);
	TCustomLiveBlock* __fastcall GetLived(int index);
	void __fastcall SetFRunColor(const System::Uitypes::TColor Value);
	void __fastcall UnhandledRunError(void);
	void __fastcall SetFIdlePercent(const unsigned Value);
	void __fastcall LoadLastNodeProp(System::Classes::TReader* Reader);
	void __fastcall StoreLastNodeProp(System::Classes::TWriter* Writer);
	void __fastcall ForceTerminateSubThreads(void);
	void __fastcall LoadErrorNodeProp(System::Classes::TReader* Reader);
	void __fastcall LoadRunErrorMsgProp(System::Classes::TReader* Reader);
	void __fastcall StoreErrorNodeProp(System::Classes::TWriter* Writer);
	void __fastcall StoreRunErrorMsgProp(System::Classes::TWriter* Writer);
	
protected:
	TCustomLiveBlock* FErrorHandler;
	NativeUInt StepEvent;
	bool StepMode;
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, Atdiagram::TLinkPoint* Anchor1, Atdiagram::TLinkPoint* Anchor2);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall LoadNextNodeProp(System::Classes::TReader* Reader);
	void __fastcall StoreNextNodeProp(System::Classes::TWriter* Writer);
	virtual void __fastcall DoOnChangeState(void);
	virtual void __fastcall DoOnStart(TStartMode StartMode);
	virtual void __fastcall DoOnShift(TCustomLiveBlock* OldBlock, TCustomLiveBlock* NewBlock);
	virtual void __fastcall DoOnTerminate(System::TObject* Sender);
	virtual void __fastcall DoOnRunError(TCustomLiveBlock* Block, int &Error, bool &ResumeNext);
	virtual void __fastcall DoStop(int TheExitCode);
	virtual void __fastcall DoForceStop(void);
	virtual void __fastcall DoStep(void);
	virtual void __fastcall DoPause(void);
	virtual void __fastcall DoRun(void);
	virtual void __fastcall DoReset(bool Continue = false);
	virtual void __fastcall ExecuteNode(void);
	void __fastcall PaintExecute(void);
	virtual void __fastcall DoLoadState(void);
	virtual void __fastcall DoSaveState(void);
	void __fastcall TerminateSubThreads(void);
	virtual void __fastcall DoBeforeExecuteNode(TCustomLiveBlock* ANode);
	virtual void __fastcall DoAfterExecuteNode(TCustomLiveBlock* ANode);
	virtual Atdiagram::TatDiagramClass __fastcall DiagramStreamClass(void);
	__property TCustomLiveBlock* StartBlock = {read=FStart};
	__property TCustomLiveBlock* EndBlock = {read=FEnd};
	
public:
	TCustomLiveBlock* LastNode;
	TCustomLiveBlock* NextNode;
	TCustomLiveBlock* ErrorNode;
	__fastcall virtual TLiveDiagram(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLiveDiagram(void);
	virtual void __fastcall Modified(void);
	virtual bool __fastcall Link(void);
	virtual bool __fastcall PrepareRun(void);
	void __fastcall DoAction(TDiagramAction Action);
	void __fastcall SaveStateToStream(System::Classes::TStream* AStream, bool TextFormat = false);
	void __fastcall LoadStateFromStream(System::Classes::TStream* AStream, bool TextFormat = false);
	void __fastcall SaveState(void);
	void __fastcall LoadState(void);
	void __fastcall MakeActiveNodeVisible(void);
	__property bool SavingState = {read=FSavingState, nodefault};
	__property TDiagramState State = {read=FState, write=SetFState, nodefault};
	__property int RunError = {read=FRunError, nodefault};
	__property System::UnicodeString RunErrorMsg = {read=FRunErrorMsg};
	__property int ExitCode = {read=FExitCode, nodefault};
	__property TCustomLiveBlock* Liveds[int index] = {read=GetLived};
	__property TViewStateMode ViewStateMode = {read=FViewStateMode, write=FViewStateMode, nodefault};
	__property unsigned MaximumIdle = {read=FMaximumIdle, write=FMaximumIdle, nodefault};
	
__published:
	__property unsigned IdlePercent = {read=FIdlePercent, write=SetFIdlePercent, default=0};
	__property unsigned SleepVisual = {read=FSleepVisual, write=SetFSleepVisual, default=0};
	__property System::Uitypes::TColor RunColor = {read=FRunColor, write=SetFRunColor, default=0};
	__property System::Classes::TNotifyEvent OnSaveState = {read=FOnSaveState, write=FOnSaveState};
	__property System::Classes::TNotifyEvent OnLoadState = {read=FOnLoadState, write=FOnLoadState};
	__property System::Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property System::Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property TRunErrorEvent OnUnhandledRunError = {read=FOnRunError, write=FOnRunError};
	__property TStartEvent OnStart = {read=FOnStart, write=FOnStart};
	__property TShiftEvent OnShift = {read=FOnShift, write=FOnShift};
	__property TTerminateEvent OnTerminate = {read=FOnTerminate, write=FOnTerminate};
	__property TChangeStateEvent OnChangeState = {read=FOnChangeState, write=FOnChangeState};
public:
	/* TWinControl.CreateParented */ inline __fastcall TLiveDiagram(HWND ParentWindow) : Atdiagram::TatDiagram(ParentWindow) { }
	
};


class DELPHICLASS TLiveStreamDiagram;
class PASCALIMPLEMENTATION TLiveStreamDiagram : public TLiveDiagram
{
	typedef TLiveDiagram inherited;
	
private:
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Winapi::Messages::TMessage &Message);
	
public:
	virtual void __fastcall PaintWindow(HDC DC);
	__fastcall virtual TLiveStreamDiagram(System::Classes::TComponent* Owner);
public:
	/* TLiveDiagram.Destroy */ inline __fastcall virtual ~TLiveStreamDiagram(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TLiveStreamDiagram(HWND ParentWindow) : TLiveDiagram(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 Sys_End_Program = System::Int8(-1);
static const System::Int8 Sys_Err_Exception = System::Int8(-2);
static const System::Int8 Sys_Broken_Link = System::Int8(-3);
static const System::Int8 Sys_Unhandled_Error = System::Int8(-4);
static const System::Int8 Sys_End_Path = System::Int8(-5);
static const System::Int8 Sys_Invalid_Join = System::Int8(-6);
static const System::Int8 xNormal_termination = System::Int8(0x0);
static const System::Int8 xUser_termination = System::Int8(0x1);
static const System::Int8 xProgram_termination = System::Int8(0x2);
static const System::Int8 xUnhandled_error = System::Int8(0x3);
static const System::Int8 xCode_Exception = System::Int8(0x4);
static const System::Int8 xBroken_link = System::Int8(0x5);
static const System::Int8 xUnknow_SysError = System::Int8(0x6);
static const System::Int8 xWaitState_Termination = System::Int8(0x7);
static const System::Int8 xPath_termination = System::Int8(0x8);
static const System::Int8 xInvalid_Join = System::Int8(0x9);
}	/* namespace Livediagram */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_LIVEDIAGRAM)
using namespace Livediagram;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LivediagramHPP
