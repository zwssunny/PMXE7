// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsClasses.pas' rev: 28.00 (Windows)

#ifndef WsclassesHPP
#define WsclassesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Data.DB.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <Vcl.FileCtrl.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit
#include <atScript.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsclasses
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EWorkflowException;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EWorkflowException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWorkflowException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWorkflowException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWorkflowException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWorkflowException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWorkflowException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWorkflowException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWorkflowException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWorkflowException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWorkflowException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWorkflowException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWorkflowException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWorkflowException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWorkflowException(void) { }
	
};

#pragma pack(pop)

typedef System::TMetaClass* TWorkflowBlockEditorClass;

enum DECLSPEC_DENUM TAttachmentPermission : unsigned char { apDelete, apInsert, apEdit };

typedef System::Set<TAttachmentPermission, TAttachmentPermission::apDelete, TAttachmentPermission::apEdit> TAttachmentPermissions;

enum DECLSPEC_DENUM TStateShape : unsigned char { ssCircle, ssSquare };

enum DECLSPEC_DENUM TTaskFilterType : unsigned char { tfUser, tfWorkIns, tfUserList };

enum DECLSPEC_DENUM TLogFilterType : unsigned char { lfTaskIns, lfWorkIns };

enum DECLSPEC_DENUM TGroupAssignmentMode : unsigned char { gamMultipleTasks, gamSingleTask };

class DELPHICLASS TCustomWorkflowBlock;
typedef void __fastcall (__closure *TWorkflowBlockEvent)(System::TObject* Sender, TCustomWorkflowBlock* ABlock);

typedef void __fastcall (__closure *TWorkflowGetNowEvent)(System::TObject* Sender, System::TDateTime &ANow);

class DELPHICLASS TTaskInstance;
typedef void __fastcall (__closure *TWorkflowTaskEvent)(System::TObject* Sender, TTaskInstance* ATaskIns);

typedef void __fastcall (__closure *TWorkflowTaskActionEvent)(System::TObject* Sender, TTaskInstance* ATaskIns, bool &AContinue);

class DELPHICLASS TWorkflowScriptEngine;
typedef void __fastcall (__closure *TWorkflowScriptEngineEvent)(TWorkflowScriptEngine* AEngine);

class DELPHICLASS TWorkflowDefinition;
class DELPHICLASS TCustomWorkflowDiagram;
class DELPHICLASS TCustomWorkflowStudio;
class PASCALIMPLEMENTATION TWorkflowDefinition : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	Vcl::Forms::TForm* FContainer;
	TCustomWorkflowDiagram* FDiagram;
	System::UnicodeString FKey;
	System::UnicodeString FName;
	System::UnicodeString FFlowExplan;
	System::UnicodeString FWorkType;
	int FFlowIsPublic;
	int FFlowIsTerm;
	System::TDateTime FFlowCreatOn;
	System::UnicodeString FFlowCreator;
	TCustomWorkflowStudio* __fastcall GetWorkflowStudio(void);
	void __fastcall Initialize(TCustomWorkflowStudio* AWorkflowStudio);
	void __fastcall SetKey(const System::UnicodeString Value);
	void __fastcall SetName(const System::UnicodeString Value);
	void __fastcall SetWorkflowStudio(TCustomWorkflowStudio* const Value);
	
public:
	__fastcall virtual TWorkflowDefinition(System::Classes::TCollection* Collection)/* overload */;
	__fastcall TWorkflowDefinition(TCustomWorkflowStudio* AWorkflowStudio)/* overload */;
	__fastcall virtual ~TWorkflowDefinition(void);
	void __fastcall AssignFromDiagram(TCustomWorkflowDiagram* ADiagram);
	void __fastcall AssignToDiagram(TCustomWorkflowDiagram* ADiagram);
	__property TCustomWorkflowDiagram* Diagram = {read=FDiagram};
	__property System::UnicodeString Key = {read=FKey, write=SetKey};
	__property System::UnicodeString Name = {read=FName, write=SetName};
	__property System::UnicodeString WorkType = {read=FWorkType, write=FWorkType};
	__property System::UnicodeString FlowExplan = {read=FFlowExplan, write=FFlowExplan};
	__property int FlowIsPublic = {read=FFlowIsPublic, write=FFlowIsPublic, nodefault};
	__property int FlowIsTerm = {read=FFlowIsTerm, write=FFlowIsTerm, nodefault};
	__property System::TDateTime FlowCreatOn = {read=FFlowCreatOn, write=FFlowCreatOn};
	__property System::UnicodeString FlowCreator = {read=FFlowCreator, write=FFlowCreator};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=GetWorkflowStudio, write=SetWorkflowStudio};
};


class DELPHICLASS TWorkflowDefinitions;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowDefinitions : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowDefinition* operator[](int Index) { return Items[Index]; }
	
private:
	TCustomWorkflowStudio* FWorkflowStudio;
	HIDESBASE TWorkflowDefinition* __fastcall GetItem(int Index);
	void __fastcall SetWorkflowStudio(TCustomWorkflowStudio* const Value);
	
public:
	__fastcall TWorkflowDefinitions(System::Classes::TComponent* AOwner);
	HIDESBASE TWorkflowDefinition* __fastcall Add(void);
	TWorkflowDefinition* __fastcall FindByName(System::UnicodeString AName);
	TWorkflowDefinition* __fastcall FindByKey(System::UnicodeString AKey);
	System::UnicodeString __fastcall FindNewName(void);
	__property TWorkflowDefinition* Items[int Index] = {read=GetItem/*, default*/};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=FWorkflowStudio, write=SetWorkflowStudio};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowDefinitions(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TWorkflowStatus : unsigned char { wsNotStarted, wsRunning, wsFinished, wsFinishedWithError };

class DELPHICLASS TWorkflowInstance;
class PASCALIMPLEMENTATION TWorkflowInstance : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Vcl::Forms::TForm* FContainer;
	TCustomWorkflowDiagram* FDiagram;
	System::UnicodeString FKey;
	System::UnicodeString FDefinitionKey;
	TWorkflowStatus FStatus;
	System::TDateTime FFlowMnCreateTime;
	System::UnicodeString FFlowMnCreator;
	System::UnicodeString FFlowMnSubject;
	System::UnicodeString FFlowMnContent;
	System::UnicodeString FFlowMnBusWindow;
	System::UnicodeString FFlowMnBusCode;
	int FFlowMnRank;
	int FFlowMoveTimeLimit;
	System::TDateTime FFlowMnLastUpDateTime;
	System::TDateTime FFlowMnFinishTime;
	System::UnicodeString FFlowMnReport;
	TCustomWorkflowStudio* FWorkflowStudio;
	System::TDateTime FNextRunTime;
	System::UnicodeString FChildKey;
	System::UnicodeString FParentKey;
	System::UnicodeString FFlowMnPrjID;
	void __fastcall LoadDiagramProp(System::Classes::TReader* Reader);
	void __fastcall StoreDiagramProp(System::Classes::TWriter* Writer);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall TWorkflowInstance(System::Classes::TComponent* AOwner, TCustomWorkflowStudio* AWorkflowStudio);
	__fastcall virtual ~TWorkflowInstance(void);
	void __fastcall AssignFromDiagram(TCustomWorkflowDiagram* ADiagram, bool State);
	void __fastcall AssignToDiagram(TCustomWorkflowDiagram* ADiagram, bool State);
	__property TCustomWorkflowDiagram* Diagram = {read=FDiagram};
	__property System::TDateTime NextRunTime = {read=FNextRunTime, write=FNextRunTime};
	__property System::TDateTime FlowMnCreateTime = {read=FFlowMnCreateTime, write=FFlowMnCreateTime};
	__property System::UnicodeString FlowMnCreator = {read=FFlowMnCreator, write=FFlowMnCreator};
	__property System::UnicodeString FlowMnSubject = {read=FFlowMnSubject, write=FFlowMnSubject};
	__property System::UnicodeString FlowMnContent = {read=FFlowMnContent, write=FFlowMnContent};
	__property System::UnicodeString FlowMnBusWindow = {read=FFlowMnBusWindow, write=FFlowMnBusWindow};
	__property System::UnicodeString FlowMnBusCode = {read=FFlowMnBusCode, write=FFlowMnBusCode};
	__property int FlowMnRank = {read=FFlowMnRank, write=FFlowMnRank, nodefault};
	__property System::UnicodeString FlowMnReport = {read=FFlowMnReport, write=FFlowMnReport};
	__property int FlowMoveTimeLimit = {read=FFlowMoveTimeLimit, write=FFlowMoveTimeLimit, nodefault};
	__property System::TDateTime FlowMnLastUpDateTime = {read=FFlowMnLastUpDateTime, write=FFlowMnLastUpDateTime};
	__property System::TDateTime FlowMnFinishTime = {read=FFlowMnFinishTime, write=FFlowMnFinishTime};
	
__published:
	__property System::UnicodeString Key = {read=FKey, write=FKey};
	__property System::UnicodeString DefinitionKey = {read=FDefinitionKey, write=FDefinitionKey};
	__property TWorkflowStatus Status = {read=FStatus, write=FStatus, nodefault};
	__property System::UnicodeString ParentKey = {read=FParentKey, write=FParentKey};
	__property System::UnicodeString ChildKey = {read=FChildKey, write=FChildKey};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=FWorkflowStudio};
	__property System::UnicodeString FlowMnPrjID = {read=FFlowMnPrjID, write=FFlowMnPrjID};
};


class DELPHICLASS TWorkflowVariable;
class PASCALIMPLEMENTATION TWorkflowVariable : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::Variant FValue;
	bool FInteraction;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::Variant Value = {read=FValue, write=FValue};
	__property bool Interaction = {read=FInteraction, write=FInteraction, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TWorkflowVariable(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TWorkflowVariable(void) { }
	
};


class DELPHICLASS TWorkflowVariables;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowVariables : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowVariable* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TWorkflowVariable* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TWorkflowVariable* __fastcall Add(void);
	TWorkflowVariable* __fastcall FindByName(System::UnicodeString AName);
	__property TWorkflowVariable* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TWorkflowVariables(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowVariables(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowBiz;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowBiz : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FBizFormID;
	System::UnicodeString FBizName;
	System::UnicodeString FBizMenuID;
	System::UnicodeString FBizTableName;
	System::UnicodeString FBizKey;
	System::UnicodeString FBizCheck;
	System::UnicodeString FBizChecker;
	System::UnicodeString FBizCheckDate;
	System::UnicodeString FBizEditMenuID;
	System::UnicodeString FBizCheckValue;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::UnicodeString BizName = {read=FBizName, write=FBizName};
	__property System::UnicodeString BizFormID = {read=FBizFormID, write=FBizFormID};
	__property System::UnicodeString BizMenuID = {read=FBizMenuID, write=FBizMenuID};
	__property System::UnicodeString BizTableName = {read=FBizTableName, write=FBizTableName};
	__property System::UnicodeString BizKey = {read=FBizKey, write=FBizKey};
	__property System::UnicodeString BizCheck = {read=FBizCheck, write=FBizCheck};
	__property System::UnicodeString BizChecker = {read=FBizChecker, write=FBizChecker};
	__property System::UnicodeString BizCheckDate = {read=FBizCheckDate, write=FBizCheckDate};
	__property System::UnicodeString BizEditMenuID = {read=FBizEditMenuID, write=FBizEditMenuID};
	__property System::UnicodeString BizCheckValue = {read=FBizCheckValue, write=FBizCheckValue};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TWorkflowBiz(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TWorkflowBiz(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowBizs;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowBizs : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowBiz* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TWorkflowBiz* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TWorkflowBiz* __fastcall Add(void);
	__property TWorkflowBiz* Items[int Index] = {read=GetItem/*, default*/};
	TWorkflowBiz* __fastcall FindByBizFormID(System::UnicodeString ABizFormID);
	TWorkflowBiz* __fastcall FindByBizMenuID(System::UnicodeString ABizMenuID);
	TWorkflowBiz* __fastcall FindByBizEditMenuID(System::UnicodeString ABizEditMenuID);
public:
	/* TOwnedCollection.Create */ inline __fastcall TWorkflowBizs(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowBizs(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TNotifyThread;
class DELPHICLASS TAttachmentItem;
class PASCALIMPLEMENTATION TNotifyThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::UnicodeString FFileName;
	TAttachmentItem* FItem;
	System::TDateTime FFileAge;
	
public:
	__fastcall TNotifyThread(TAttachmentItem* AItem, const System::UnicodeString FileName, System::Classes::TNotifyEvent OnClosed)/* overload */;
	__fastcall virtual ~TNotifyThread(void);
	virtual void __fastcall Execute(void);
public:
	/* TThread.Create */ inline __fastcall TNotifyThread(void)/* overload */ : System::Classes::TThread() { }
	/* TThread.Create */ inline __fastcall TNotifyThread(bool CreateSuspended)/* overload */ : System::Classes::TThread(CreateSuspended) { }
	
};


class PASCALIMPLEMENTATION TAttachmentItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FContent;
	System::UnicodeString FOriginalName;
	System::UnicodeString FKey;
	bool FDirtyContent;
	TNotifyThread* FNotifyThread;
	System::Uitypes::TCursor FSaveCursor;
	System::TDateTime FCreatedOn;
	System::UnicodeString FWorkKey;
	int FAttachType;
	TCustomWorkflowStudio* FWorkflowStudio;
	void __fastcall CursorDefault(void);
	void __fastcall CursorHourGlass(void);
	void __fastcall DoShellOpen(System::UnicodeString AFileName, bool AllowEdit);
	System::UnicodeString __fastcall GetContent(void);
	System::UnicodeString __fastcall GetExtension(void);
	void __fastcall Initialize(TCustomWorkflowStudio* AWorkflowStudio);
	bool __fastcall IsContentStored(void);
	bool __fastcall Loading(void);
	void __fastcall SetContent(const System::UnicodeString Value);
	void __fastcall SetDirtyContent(const bool Value);
	void __fastcall ShellAppClosed(System::TObject* Sender);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TAttachmentItem(System::Classes::TCollection* Collection)/* overload */;
	__fastcall TAttachmentItem(TCustomWorkflowStudio* AWorkflowStudio)/* overload */;
	__fastcall virtual ~TAttachmentItem(void);
	void __fastcall LoadContentFromFile(System::UnicodeString AFileName);
	void __fastcall SaveContentToFile(System::UnicodeString AFileName);
	void __fastcall Open(bool AllowEdit, System::UnicodeString APath = System::UnicodeString());
	__property System::UnicodeString Extension = {read=GetExtension};
	
__published:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString OriginalName = {read=FOriginalName, write=FOriginalName};
	__property System::UnicodeString Key = {read=FKey, write=FKey};
	__property bool DirtyContent = {read=FDirtyContent, write=SetDirtyContent, nodefault};
	__property System::TDateTime CreatedOn = {read=FCreatedOn, write=FCreatedOn};
	__property System::UnicodeString Content = {read=GetContent, write=SetContent, stored=IsContentStored};
	__property int AttachType = {read=FAttachType, write=FAttachType, nodefault};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=FWorkflowStudio};
	__property System::UnicodeString WorkKey = {read=FWorkKey, write=FWorkKey};
};


class DELPHICLASS TAttachmentItems;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TAttachmentItems : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TAttachmentItem* operator[](int Index) { return Items[Index]; }
	
private:
	TCustomWorkflowStudio* FWorkflowStudio;
	HIDESBASE TAttachmentItem* __fastcall GetItem(int Index);
	void __fastcall SetWorkflowStudio(TCustomWorkflowStudio* const Value);
	
public:
	__fastcall TAttachmentItems(System::Classes::TPersistent* AOwner);
	HIDESBASE TAttachmentItem* __fastcall Add(void);
	TAttachmentItem* __fastcall FindByName(System::UnicodeString AName);
	TAttachmentItem* __fastcall AddFile(System::UnicodeString AFileName);
	__property TAttachmentItem* Items[int Index] = {read=GetItem/*, default*/};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=FWorkflowStudio, write=SetWorkflowStudio};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TAttachmentItems(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowAttachment;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowAttachment : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	TAttachmentItems* FItems;
	void __fastcall SetItems(TAttachmentItems* const Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TWorkflowAttachment(System::Classes::TCollection* Collection);
	__fastcall virtual ~TWorkflowAttachment(void);
	
__published:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TAttachmentItems* Items = {read=FItems, write=SetItems};
};

#pragma pack(pop)

class DELPHICLASS TWorkflowAttachments;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowAttachments : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowAttachment* operator[](int Index) { return Items[Index]; }
	
private:
	TCustomWorkflowStudio* FWorkflowStudio;
	HIDESBASE TWorkflowAttachment* __fastcall GetItem(int Index);
	void __fastcall SetWorkflowStudio(TCustomWorkflowStudio* const Value);
	
public:
	__fastcall TWorkflowAttachments(System::Classes::TPersistent* AOwner);
	HIDESBASE TWorkflowAttachment* __fastcall Add(void);
	TWorkflowAttachment* __fastcall FindByName(System::UnicodeString AName);
	TAttachmentItem* __fastcall AddFile(System::UnicodeString AName, System::UnicodeString AFileName);
	void __fastcall MakeAllDirty(void);
	__property TWorkflowAttachment* Items[int Index] = {read=GetItem/*, default*/};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=FWorkflowStudio, write=SetWorkflowStudio};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowAttachments(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowEngine;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowEngine : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCustomWorkflowStudio* FWorkflowStudio;
	void __fastcall WorkflowTerminated(Livediagram::TLiveDiagram* Sender, int ExitCode);
	void __fastcall WorkflowSaveState(System::TObject* Sender);
	
public:
	__fastcall TWorkflowEngine(TCustomWorkflowStudio* AWorkflowStudio);
	void __fastcall RunWorkflow(TWorkflowInstance* WorkIns);
	int __fastcall RunPendingWorkflowInstances(void);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowEngine(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TCustomWorkflowBlock : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
private:
	TStateShape FStateShape;
	bool FOneShot;
	bool FTriggered;
	bool FSingleOutput;
	bool FAutoHandleTrigger;
	System::UnicodeString FOutput;
	System::UnicodeString FLastOutput;
	void __fastcall SetFStateShape(const TStateShape Value);
	void __fastcall DefaultLinkPoints(void);
	TCustomWorkflowDiagram* __fastcall GetWorkflowDiagram(void);
	void __fastcall LoadTriggeredProp(System::Classes::TReader* Reader);
	void __fastcall StoreTriggeredProp(System::Classes::TWriter* Writer);
	void __fastcall SetOutput(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall AdjustLinkPoints(void);
	virtual int __fastcall GetLinkPointsCount(void);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual Livediagram::TCustomLiveBlock* __fastcall GetNext(void);
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual void __fastcall UpdateLinkPoints(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual Livediagram::TCustomLiveBlock* __fastcall ScanTransitions(void);
	__property bool SingleOutput = {read=FSingleOutput, write=FSingleOutput, nodefault};
	__property bool AutoHandleTrigger = {read=FAutoHandleTrigger, write=FAutoHandleTrigger, nodefault};
	__property System::UnicodeString Output = {read=FOutput, write=SetOutput};
	
public:
	__fastcall virtual TCustomWorkflowBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWorkflowBlock(void);
	virtual void __fastcall FillOutputList(System::Classes::TStrings* AOutputs);
	bool __fastcall HasOutputList(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DoBeforeRun(void);
	virtual bool __fastcall Link(void);
	virtual TWorkflowBlockEditorClass __fastcall EditorClass(void);
	virtual void __fastcall ExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	__property TStateShape StateShape = {read=FStateShape, write=SetFStateShape, nodefault};
	__property bool OneShot = {read=FOneShot, write=FOneShot, nodefault};
	__property TCustomWorkflowDiagram* WorkflowDiagram = {read=GetWorkflowDiagram};
	__property bool Triggered = {read=FTriggered, write=FTriggered, nodefault};
	
__published:
	__property System::UnicodeString LastOutput = {read=FLastOutput, write=FLastOutput};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TCustomTaskManager;
class PASCALIMPLEMENTATION TCustomWorkflowDiagram : public Livediagram::TLiveDiagram
{
	typedef Livediagram::TLiveDiagram inherited;
	
private:
	TWorkflowVariables* FVariables;
	TWorkflowAttachments* FAttachments;
	TWorkflowInstance* FWorkflowInstance;
	TCustomWorkflowStudio* FWorkflowStudio;
	TCustomTaskManager* FTaskManager;
	bool FDisplayTaskStatus;
	void __fastcall SetVariables(TWorkflowVariables* const Value);
	void __fastcall SetAttachments(TWorkflowAttachments* const Value);
	TCustomWorkflowStudio* __fastcall GetWorkflowStudio(void);
	void __fastcall SetWorkflowStudio(TCustomWorkflowStudio* const Value);
	void __fastcall SetDisplayTaskStatus(const bool Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TCustomWorkflowDiagram(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWorkflowDiagram(void);
	__property TWorkflowVariables* Variables = {read=FVariables, write=SetVariables};
	__property TWorkflowAttachments* Attachments = {read=FAttachments, write=SetAttachments};
	__property TCustomTaskManager* TaskManager = {read=FTaskManager};
	__property TCustomWorkflowStudio* WorkflowStudio = {read=GetWorkflowStudio, write=SetWorkflowStudio};
	__property TWorkflowInstance* WorkflowInstance = {read=FWorkflowInstance};
	__property bool DisplayTaskStatus = {read=FDisplayTaskStatus, write=SetDisplayTaskStatus, nodefault};
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomWorkflowDiagram(HWND ParentWindow) : Livediagram::TLiveDiagram(ParentWindow) { }
	
};


class DELPHICLASS TCustomWorkflowManager;
class PASCALIMPLEMENTATION TCustomWorkflowManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	virtual void __fastcall LoadWorkflowDefinitionList(TWorkflowDefinitions* WorkDefs) = 0 ;
	virtual TWorkflowDefinition* __fastcall FindWorkflowDefinitionByName(System::UnicodeString AName) = 0 ;
	virtual void __fastcall ListWorkflowDefinitionNames(System::Classes::TStrings* AList, System::Classes::TStrings* BList) = 0 ;
	virtual TWorkflowBizs* __fastcall CreateWorkflowBizList(void) = 0 ;
	virtual void __fastcall LoadWorkflowBizList(TWorkflowBizs* WorkflowBizs) = 0 ;
	virtual void __fastcall LoadWorkflowBiz(TWorkflowBiz* WorkflowBiz) = 0 ;
	virtual void __fastcall CheckWorkflowBiz(TWorkflowBiz* WorkflowBiz, System::UnicodeString BizKeyValue, System::UnicodeString BillState) = 0 ;
	virtual void __fastcall UpdateWorkflowBiz(TWorkflowBiz* WorkflowBiz, TWorkflowInstance* WorkIns) = 0 ;
	virtual TWorkflowDefinitions* __fastcall CreateWorkflowDefinitionList(void) = 0 ;
	virtual TWorkflowInstance* __fastcall CreateWorkflowInstance(TWorkflowDefinition* WorkDef) = 0 ;
	virtual TWorkflowInstance* __fastcall CreateWorkflowInstanceByName(System::UnicodeString WorkDefName) = 0 ;
	virtual TWorkflowInstance* __fastcall CreateWorkflowInstanceByKey(System::UnicodeString AKey) = 0 ;
	virtual TWorkflowInstance* __fastcall FindWorkflowInstanceByKey(System::UnicodeString AKey) = 0 ;
	virtual void __fastcall ListPendingWorkflowInstances(System::Classes::TStrings* AKeyList) = 0 ;
	virtual void __fastcall DeleteWorkflowInstance(TWorkflowInstance* WorkIns) = 0 ;
	virtual void __fastcall DeleteWorkflowInstanceByKey(System::UnicodeString WorkInsKey) = 0 ;
	virtual void __fastcall SignalWorkflowInstance(System::UnicodeString AKey) = 0 ;
	virtual void __fastcall LoadWorkflowInstance(TWorkflowInstance* WorkIns) = 0 ;
	virtual void __fastcall SaveWorkflowInstance(TWorkflowInstance* WorkIns) = 0 ;
	virtual void __fastcall SaveWorkflowDefinition(TWorkflowDefinition* WorkDef) = 0 ;
	virtual void __fastcall LoadWorkflowDefinition(System::UnicodeString AKey, TWorkflowDefinition* WorkDef) = 0 ;
	virtual void __fastcall DeleteWorkflowDefinition(TWorkflowDefinition* WorkDef) = 0 ;
	virtual void __fastcall AssignWorkflowInstanceDiagram(TCustomWorkflowDiagram* ADiagram, System::UnicodeString WorkInsKey) = 0 ;
public:
	/* TComponent.Create */ inline __fastcall virtual TCustomWorkflowManager(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomWorkflowManager(void) { }
	
};


class DELPHICLASS TWorkflowUserManager;
class PASCALIMPLEMENTATION TCustomWorkflowStudio : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TWorkflowGetNowEvent FOnGetNow;
	TCustomWorkflowManager* FWorkflowManager;
	TWorkflowBlockEvent FOnAfterExecuteNode;
	TWorkflowBlockEvent FOnBeforeExecuteNode;
	TWorkflowTaskEvent FOnTaskCreated;
	TCustomTaskManager* FTaskManager;
	TWorkflowEngine* FWorkflowEngine;
	TWorkflowUserManager* FUserManager;
	TWorkflowScriptEngine* FInternalScriptEngine;
	TWorkflowScriptEngine* FScriptEngine;
	TWorkflowTaskEvent FOnTaskFinished;
	TWorkflowTaskActionEvent FBeforeSaveTaskInstance;
	TWorkflowScriptEngineEvent FOnInitializeScriptEngine;
	TWorkflowScriptEngine* __fastcall GetScriptEngine(void);
	void __fastcall SetScriptEngine(TWorkflowScriptEngine* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	System::TDateTime __fastcall GetNow(void);
	__fastcall virtual TCustomWorkflowStudio(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWorkflowStudio(void);
	virtual void __fastcall RunFinished(TWorkflowInstance* WI) = 0 ;
	virtual void __fastcall WorkflowInstanceError(TWorkflowInstance* WI, System::UnicodeString ErrMsg, bool &ShowError) = 0 ;
	virtual void __fastcall InitializeScriptEngine(TWorkflowScriptEngine* AEngine);
	__property TCustomTaskManager* TaskManager = {read=FTaskManager, write=FTaskManager};
	__property TCustomWorkflowManager* WorkflowManager = {read=FWorkflowManager, write=FWorkflowManager};
	__property TWorkflowEngine* WorkflowEngine = {read=FWorkflowEngine};
	__property TWorkflowUserManager* UserManager = {read=FUserManager};
	__property TWorkflowScriptEngine* ScriptEngine = {read=GetScriptEngine, write=SetScriptEngine};
	__property TWorkflowBlockEvent OnAfterExecuteNode = {read=FOnAfterExecuteNode, write=FOnAfterExecuteNode};
	__property TWorkflowBlockEvent OnBeforeExecuteNode = {read=FOnBeforeExecuteNode, write=FOnBeforeExecuteNode};
	__property TWorkflowTaskEvent OnTaskCreated = {read=FOnTaskCreated, write=FOnTaskCreated};
	__property TWorkflowTaskEvent OnTaskFinished = {read=FOnTaskFinished, write=FOnTaskFinished};
	__property TWorkflowGetNowEvent OnGetNow = {read=FOnGetNow, write=FOnGetNow};
	__property TWorkflowTaskActionEvent BeforeSaveTaskInstance = {read=FBeforeSaveTaskInstance, write=FBeforeSaveTaskInstance};
	__property TWorkflowScriptEngineEvent OnInitializeScriptEngine = {read=FOnInitializeScriptEngine, write=FOnInitializeScriptEngine};
};


class DELPHICLASS TWorkflowBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowBlockEditor : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall EditBlock(TCustomWorkflowBlock* ABlock) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TWorkflowBlockEditor(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowBlockEditor(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskField;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskField : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	bool FRequired;
	bool FReadOnly;
	System::UnicodeString FCaption;
	System::UnicodeString FWorkflowVarName;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::UnicodeString Caption = {read=FCaption, write=FCaption};
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly, nodefault};
	__property bool Required = {read=FRequired, write=FRequired, nodefault};
	__property System::UnicodeString WorkflowVarName = {read=FWorkflowVarName, write=FWorkflowVarName};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TTaskField(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TTaskField(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskFields;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskFields : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTaskField* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TTaskField* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TTaskField* __fastcall Add(void);
	TTaskField* __fastcall FindByVarName(System::UnicodeString AVarName);
	__property TTaskField* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TTaskFields(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTaskFields(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TAssignedUserType : unsigned char { autUser, autGroup, autJob, autDepartment, autDepartmentManager };

class DELPHICLASS TTaskAssignedUser;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskAssignedUser : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FAssignedUserID;
	System::UnicodeString FAssignedUserName;
	int FStepDefin;
	TAssignedUserType FAssignedUserType;
	bool FCanPrint;
	TGroupAssignmentMode FAssignmentMode;
	bool FNeedPrjRight;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::UnicodeString AssignedUserName = {read=FAssignedUserName, write=FAssignedUserName};
	__property System::UnicodeString AssignedUserID = {read=FAssignedUserID, write=FAssignedUserID};
	__property int StepDefin = {read=FStepDefin, write=FStepDefin, default=0};
	__property TAssignedUserType AssignedUserType = {read=FAssignedUserType, write=FAssignedUserType, nodefault};
	__property bool CanPrint = {read=FCanPrint, write=FCanPrint, nodefault};
	__property TGroupAssignmentMode AssignmentMode = {read=FAssignmentMode, write=FAssignmentMode, nodefault};
	__property bool NeedPrjRight = {read=FNeedPrjRight, write=FNeedPrjRight, default=0};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TTaskAssignedUser(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TTaskAssignedUser(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskAssignedUsers;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskAssignedUsers : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTaskAssignedUser* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TTaskAssignedUser* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TTaskAssignedUser* __fastcall Add(void);
	__property TTaskAssignedUser* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TTaskAssignedUsers(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTaskAssignedUsers(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskDefinition;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskDefinition : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FDescription;
	System::UnicodeString FName;
	System::Classes::TStrings* FStatusList;
	System::Classes::TStrings* FTaskInstanceKeys;
	System::Classes::TStrings* FPreviousTaskInsKeys;
	System::UnicodeString FKey;
	System::UnicodeString FSubject;
	bool FMailNotification;
	bool FShowAttachments;
	TAttachmentPermissions FAttachmentPermissions;
	TTaskFields* FFields;
	TTaskAssignedUsers* FUsers;
	System::UnicodeString FExpirationDateTime;
	System::UnicodeString FExpirationStatus;
	System::Classes::TStrings* FHiddenStatusList;
	void __fastcall SetStatusList(System::Classes::TStrings* const Value);
	System::UnicodeString __fastcall GetInitialStatus(void);
	void __fastcall SetFields(TTaskFields* const Value);
	void __fastcall SetUsers(TTaskAssignedUsers* const Value);
	void __fastcall SetHiddenStatusList(System::Classes::TStrings* const Value);
	int __fastcall GetStatusCount(void);
	bool __fastcall GetStatusHidden(int i);
	void __fastcall SetStatusHidden(int i, const bool Value);
	System::UnicodeString __fastcall GetStatusName(int i);
	void __fastcall SetStatusName(int i, const System::UnicodeString Value);
	bool __fastcall GetStatusCompletion(int i);
	void __fastcall SetStatusCompletion(int i, const bool Value);
	
public:
	__fastcall virtual TTaskDefinition(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTaskDefinition(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall IsCompletionStatus(System::UnicodeString AStatus);
	void __fastcall FillStatusList(System::Classes::TStrings* AList, bool AIncludeHidden = false);
	int __fastcall StatusAdd(System::UnicodeString AStatus, bool ACompletion = false, bool AHidden = false);
	void __fastcall StatusDelete(System::UnicodeString AStatus);
	__property System::UnicodeString InitialStatus = {read=GetInitialStatus};
	__property int StatusCount = {read=GetStatusCount, nodefault};
	__property System::UnicodeString StatusName[int i] = {read=GetStatusName, write=SetStatusName};
	__property bool StatusCompletion[int i] = {read=GetStatusCompletion, write=SetStatusCompletion};
	__property bool StatusHidden[int i] = {read=GetStatusHidden, write=SetStatusHidden};
	
__published:
	__property System::UnicodeString Key = {read=FKey, write=FKey};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString Subject = {read=FSubject, write=FSubject};
	__property System::UnicodeString Description = {read=FDescription, write=FDescription};
	__property TTaskAssignedUsers* Users = {read=FUsers, write=SetUsers};
	__property System::Classes::TStrings* StatusList = {read=FStatusList, write=SetStatusList};
	__property System::Classes::TStrings* HiddenStatusList = {read=FHiddenStatusList, write=SetHiddenStatusList};
	__property System::Classes::TStrings* TaskInstanceKeys = {read=FTaskInstanceKeys, write=FTaskInstanceKeys};
	__property System::Classes::TStrings* PreviousTaskInsKeys = {read=FPreviousTaskInsKeys, write=FPreviousTaskInsKeys};
	__property bool MailNotification = {read=FMailNotification, write=FMailNotification, nodefault};
	__property bool ShowAttachments = {read=FShowAttachments, write=FShowAttachments, nodefault};
	__property TAttachmentPermissions AttachmentPermissions = {read=FAttachmentPermissions, write=FAttachmentPermissions, nodefault};
	__property TTaskFields* Fields = {read=FFields, write=SetFields};
	__property System::UnicodeString ExpirationDateTime = {read=FExpirationDateTime, write=FExpirationDateTime};
	__property System::UnicodeString ExpirationStatus = {read=FExpirationStatus, write=FExpirationStatus};
};

#pragma pack(pop)

class DELPHICLASS TTaskDefinitions;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskDefinitions : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTaskDefinition* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TTaskDefinition* __fastcall GetItem(int Index);
	
public:
	__fastcall TTaskDefinitions(System::Classes::TComponent* AOwner);
	HIDESBASE TTaskDefinition* __fastcall Add(void);
	TTaskDefinition* __fastcall FindByName(System::UnicodeString AName);
	__property TTaskDefinition* Items[int Index] = {read=GetItem/*, default*/};
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner(void);
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTaskDefinitions(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TTaskInstance : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Classes::TDataModule* FContainer;
	Livediagram::TLiveDiagram* FDiagram;
	System::UnicodeString FComments;
	System::UnicodeString FStatus;
	System::UnicodeString FUserID;
	System::UnicodeString FKey;
	System::UnicodeString FWorkInsKey;
	TTaskDefinition* FTaskDef;
	System::TDateTime FCreatedOn;
	bool FCanPrint;
	TAssignedUserType FAssignedUserType;
	System::TDateTime FFlowMnDtlChkTime;
	System::TDateTime FFlowMnDtlLimitTime;
	int FFlowMnDtlNum;
	System::UnicodeString FFlowMnDtlReceiver;
	System::TDateTime FFlowMnDtlStateChgTime;
	System::UnicodeString FFlowMnDtlRemark;
	int FFlowMnDtlStepDefin;
	System::UnicodeString FFlowMnDtlProjectID;
	bool FNeedPrjRight;
	void __fastcall SetTaskDef(TTaskDefinition* const Value);
	bool __fastcall GetCompleted(void);
	
public:
	__fastcall virtual TTaskInstance(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTaskInstance(void);
	bool __fastcall CanUpdate(System::UnicodeString AUserId, TCustomWorkflowStudio* AWorkflowStudio);
	bool __fastcall IsCompletionStatus(System::UnicodeString AStatus);
	__property bool Completed = {read=GetCompleted, nodefault};
	
__published:
	__property bool NeedPrjRight = {read=FNeedPrjRight, write=FNeedPrjRight, default=0};
	__property System::UnicodeString Key = {read=FKey, write=FKey};
	__property System::UnicodeString WorkInsKey = {read=FWorkInsKey, write=FWorkInsKey};
	__property System::UnicodeString UserID = {read=FUserID, write=FUserID};
	__property System::UnicodeString Status = {read=FStatus, write=FStatus};
	__property System::UnicodeString Comments = {read=FComments, write=FComments};
	__property TTaskDefinition* TaskDef = {read=FTaskDef, write=SetTaskDef};
	__property System::TDateTime CreatedOn = {read=FCreatedOn, write=FCreatedOn};
	__property bool CanPrint = {read=FCanPrint, write=FCanPrint, nodefault};
	__property TAssignedUserType AssignedUserType = {read=FAssignedUserType, write=FAssignedUserType, nodefault};
	__property System::TDateTime FlowMnDtlChkTime = {read=FFlowMnDtlChkTime, write=FFlowMnDtlChkTime};
	__property System::TDateTime FlowMnDtlLimitTime = {read=FFlowMnDtlLimitTime, write=FFlowMnDtlLimitTime};
	__property int FlowMnDtlNum = {read=FFlowMnDtlNum, write=FFlowMnDtlNum, nodefault};
	__property System::UnicodeString FlowMnDtlReceiver = {read=FFlowMnDtlReceiver, write=FFlowMnDtlReceiver};
	__property System::TDateTime FlowMnDtlStateChgTime = {read=FFlowMnDtlStateChgTime, write=FFlowMnDtlStateChgTime};
	__property System::UnicodeString FlowMnDtlRemark = {read=FFlowMnDtlRemark, write=FFlowMnDtlRemark};
	__property int FlowMnDtlStepDefin = {read=FFlowMnDtlStepDefin, write=FFlowMnDtlStepDefin, default=0};
	__property System::UnicodeString FlowMnDtlProjectID = {read=FFlowMnDtlProjectID, write=FFlowMnDtlProjectID};
};


class DELPHICLASS TTaskInstanceItem;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskInstanceItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TTaskInstance* FTask;
	
public:
	__fastcall virtual TTaskInstanceItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTaskInstanceItem(void);
	__property TTaskInstance* Task = {read=FTask};
};

#pragma pack(pop)

class DELPHICLASS TTaskInstanceList;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskInstanceList : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TTaskInstanceItem* operator[](int index) { return Items[index]; }
	
private:
	HIDESBASE TTaskInstanceItem* __fastcall GetItem(int index);
	
public:
	HIDESBASE TTaskInstanceItem* __fastcall Add(void);
	TTaskInstanceItem* __fastcall FindByKey(System::UnicodeString ATaskInsKey);
	__property TTaskInstanceItem* Items[int index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TTaskInstanceList(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TTaskInstanceList(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TCustomTaskManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	virtual void __fastcall CreateTaskInstance(TWorkflowInstance* WorkIns, TTaskDefinition* TaskDef) = 0 ;
	virtual void __fastcall LoadTaskInstance(TTaskInstance* TaskIns) = 0 ;
	virtual void __fastcall SaveTaskInstance(TTaskInstance* TaskIns) = 0 ;
	virtual void __fastcall UpdateTaskInstance(TTaskInstance* TaskIns) = 0 ;
	virtual bool __fastcall IsTaskFinished(System::UnicodeString AKey) = 0 ;
	virtual void __fastcall LoadTaskInstanceList(TTaskInstanceList* ATasks, TTaskFilterType AFilterType, System::UnicodeString AFilterKey, int completeState, System::UnicodeString AOtherCondition = System::UnicodeString()) = 0 ;
	virtual System::TDateTime __fastcall TaskExpirationDateTime(TWorkflowInstance* AWorkIns, TTaskInstance* ATaskInstance) = 0 ;
	virtual void __fastcall LogTaskInfo(TTaskInstance* TaskIns, System::UnicodeString Info) = 0 ;
public:
	/* TComponent.Create */ inline __fastcall virtual TCustomTaskManager(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomTaskManager(void) { }
	
};


enum DECLSPEC_DENUM TTaskLogOperation : unsigned char { tlNone, tlStatusChange, tlUpdate, tlCreate, tlInfo };

class DELPHICLASS TTaskLogItem;
class PASCALIMPLEMENTATION TTaskLogItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	int FIndexID;
	System::UnicodeString FTaskInsKey;
	System::UnicodeString FInfo;
	System::UnicodeString FUserId;
	System::TDateTime FEventDate;
	TTaskLogOperation FOperation;
	System::UnicodeString FInfo2;
	System::UnicodeString FFlowInsKey;
	
public:
	__property TTaskLogOperation Operation = {read=FOperation, write=FOperation, nodefault};
	__property System::UnicodeString TaskInsKey = {read=FTaskInsKey, write=FTaskInsKey};
	__property System::TDateTime EventDate = {read=FEventDate, write=FEventDate};
	__property System::UnicodeString UserId = {read=FUserId, write=FUserId};
	__property System::UnicodeString Info = {read=FInfo, write=FInfo};
	__property System::UnicodeString Info2 = {read=FInfo2, write=FInfo2};
	__property System::UnicodeString FlowInsKey = {read=FFlowInsKey, write=FFlowInsKey};
	__property int IndexID = {read=FIndexID, write=FIndexID, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TTaskLogItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TTaskLogItem(void) { }
	
};


class DELPHICLASS TTaskLogItems;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskLogItems : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTaskLogItem* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TTaskLogItem* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TTaskLogItem* __fastcall Add(void);
	__property TTaskLogItem* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TTaskLogItems(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTaskLogItems(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TScriptContext : unsigned char { scRuntimeInstance, scDesignDiagram };

class PASCALIMPLEMENTATION TWorkflowScriptEngine : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FExprDelim;
	TWorkflowInstance* FWorkIns;
	TScriptContext FRunContext;
	TCustomWorkflowDiagram* FDiagram;
	TTaskInstance* FTaskIns;
	System::UnicodeString __fastcall ExtractExpression(System::UnicodeString AText, System::UnicodeString OpenDelim, System::UnicodeString CloseDelim, int &i, int &j);
	
protected:
	System::UnicodeString __fastcall ExpressionToStr(const System::Variant &Value);
	__property TWorkflowInstance* WorkflowInstance = {read=FWorkIns};
	__property TTaskInstance* TaskInstance = {read=FTaskIns};
	__property TCustomWorkflowDiagram* Diagram = {read=FDiagram};
	virtual void __fastcall RunContextChanged(void) = 0 ;
	__property TScriptContext RunContext = {read=FRunContext, nodefault};
	
public:
	__fastcall virtual TWorkflowScriptEngine(System::Classes::TComponent* AOwner);
	void __fastcall SetRuntimeContext(TWorkflowInstance* AWorkIns, TTaskInstance* ATaskIns = (TTaskInstance*)(0x0));
	void __fastcall SetDesignContext(TCustomWorkflowDiagram* ADiagram);
	virtual System::Variant __fastcall CalculateExpression(System::UnicodeString Expr);
	System::UnicodeString __fastcall TranslateText(System::UnicodeString AText);
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TWorkflowScriptEngine(void) { }
	
};


class DELPHICLASS TWorkflowUser;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowUser : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FUserName;
	System::UnicodeString FEmail;
	System::UnicodeString FUserId;
	System::UnicodeString FUserCode;
	System::UnicodeString FPhoneCode;
	bool FCanPrint;
	int FStepDefin;
	bool FNeedPrjRight;
	System::UnicodeString __fastcall GetUserNameOrId(void);
	TWorkflowUserManager* __fastcall GetUserManager(void);
	
public:
	__property TWorkflowUserManager* UserManager = {read=GetUserManager};
	void __fastcall FillGroupIds(System::Classes::TStrings* AGroupIds);
	void __fastcall FillJobIds(System::Classes::TStrings* AJobIds);
	void __fastcall FillDepartmentIds(System::Classes::TStrings* ADepartmentIds);
	bool __fastcall BelongsToGroup(System::UnicodeString AGroupId);
	bool __fastcall BelongsToJob(System::UnicodeString AJobId);
	bool __fastcall BelongsToDepartment(System::UnicodeString ADepartmentId);
	bool __fastcall BelongsToAdminGroup(void);
	
__published:
	__property System::UnicodeString UserName = {read=GetUserNameOrId, write=FUserName};
	__property System::UnicodeString UserId = {read=FUserId, write=FUserId};
	__property System::UnicodeString Email = {read=FEmail, write=FEmail};
	__property bool CanPrint = {read=FCanPrint, write=FCanPrint, nodefault};
	__property int StepDefin = {read=FStepDefin, write=FStepDefin, nodefault};
	__property System::UnicodeString PhoneCode = {read=FPhoneCode, write=FPhoneCode};
	__property System::UnicodeString UserCode = {read=FUserCode, write=FUserCode};
	__property bool NeedPrjRight = {read=FNeedPrjRight, write=FNeedPrjRight, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TWorkflowUser(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TWorkflowUser(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowUsers;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowUsers : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowUser* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TWorkflowUser* __fastcall GetItem(int Index);
	
public:
	TWorkflowUser* __fastcall FindById(System::UnicodeString AName);
	TWorkflowUser* __fastcall FindByName(System::UnicodeString AName);
	HIDESBASE TWorkflowUser* __fastcall Add(void)/* overload */;
	HIDESBASE TWorkflowUser* __fastcall Add(System::UnicodeString AUserID, System::UnicodeString AUserName = System::UnicodeString(), System::UnicodeString AEmail = System::UnicodeString(), System::UnicodeString AUserCode = System::UnicodeString())/* overload */;
	__property TWorkflowUser* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TWorkflowUsers(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowUsers(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowGroup;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowGroup : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FGroupName;
	System::Classes::TStrings* FUserIds;
	System::UnicodeString FGroupId;
	bool FCanPrint;
	bool FIsAdmin;
	int FStepDefin;
	bool FNeedPrjRight;
	void __fastcall SetUserIds(System::Classes::TStrings* const Value);
	TWorkflowUserManager* __fastcall GetUserManager(void);
	System::UnicodeString __fastcall GetGroupId(void);
	System::UnicodeString __fastcall GetGroupName(void);
	
public:
	__fastcall virtual TWorkflowGroup(System::Classes::TCollection* Collection);
	__fastcall virtual ~TWorkflowGroup(void);
	__property TWorkflowUserManager* UserManager = {read=GetUserManager};
	
__published:
	__property System::UnicodeString GroupId = {read=GetGroupId, write=FGroupId};
	__property System::UnicodeString GroupName = {read=GetGroupName, write=FGroupName};
	__property System::Classes::TStrings* UserIds = {read=FUserIds, write=SetUserIds};
	__property bool IsAdmin = {read=FIsAdmin, write=FIsAdmin, default=0};
	__property bool CanPrint = {read=FCanPrint, write=FCanPrint, nodefault};
	__property int StepDefin = {read=FStepDefin, write=FStepDefin, nodefault};
	__property bool NeedPrjRight = {read=FNeedPrjRight, write=FNeedPrjRight, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TWorkflowGroups;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowGroups : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowGroup* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TWorkflowGroup* __fastcall GetItem(int Index);
	
public:
	TWorkflowGroup* __fastcall FindByName(System::UnicodeString AName);
	TWorkflowGroup* __fastcall FindByID(System::UnicodeString AId);
	HIDESBASE TWorkflowGroup* __fastcall Add(void)/* overload */;
	HIDESBASE TWorkflowGroup* __fastcall Add(System::UnicodeString AGroupName)/* overload */;
	HIDESBASE TWorkflowGroup* __fastcall Add(System::UnicodeString AGroupID, System::UnicodeString AGroupName)/* overload */;
	__property TWorkflowGroup* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TWorkflowGroups(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowGroups(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowDepartment;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowDepartment : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FDepartmentName;
	System::Classes::TStrings* FUserIds;
	System::UnicodeString FDepartmentId;
	System::UnicodeString FDepartmentManagerId;
	bool FCanPrint;
	int FStepDefin;
	bool FNeedPrjRight;
	void __fastcall SetUserIds(System::Classes::TStrings* const Value);
	TWorkflowUserManager* __fastcall GetUserManager(void);
	System::UnicodeString __fastcall GetDepartmentId(void);
	System::UnicodeString __fastcall GetDepartmentName(void);
	System::UnicodeString __fastcall GetDepartmentManagerId(void);
	
public:
	__fastcall virtual TWorkflowDepartment(System::Classes::TCollection* Collection);
	__fastcall virtual ~TWorkflowDepartment(void);
	__property TWorkflowUserManager* UserManager = {read=GetUserManager};
	
__published:
	__property bool CanPrint = {read=FCanPrint, write=FCanPrint, nodefault};
	__property int StepDefin = {read=FStepDefin, write=FStepDefin, nodefault};
	__property System::UnicodeString DepartmentId = {read=GetDepartmentId, write=FDepartmentId};
	__property System::UnicodeString DepartmentName = {read=GetDepartmentName, write=FDepartmentName};
	__property System::UnicodeString DepartmentManagerId = {read=GetDepartmentManagerId, write=FDepartmentManagerId};
	__property System::Classes::TStrings* UserIds = {read=FUserIds, write=SetUserIds};
	__property bool NeedPrjRight = {read=FNeedPrjRight, write=FNeedPrjRight, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TWorkflowDepartments;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowDepartments : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowDepartment* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TWorkflowDepartment* __fastcall GetItem(int Index);
	
public:
	TWorkflowDepartment* __fastcall FindByName(System::UnicodeString AName);
	TWorkflowDepartment* __fastcall FindByID(System::UnicodeString AId);
	HIDESBASE TWorkflowDepartment* __fastcall Add(void)/* overload */;
	HIDESBASE TWorkflowDepartment* __fastcall Add(System::UnicodeString ADepartmentName)/* overload */;
	HIDESBASE TWorkflowDepartment* __fastcall Add(System::UnicodeString ADepartmentID, System::UnicodeString ADepartmentName)/* overload */;
	__property TWorkflowDepartment* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TWorkflowDepartments(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowDepartments(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowJob;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowJob : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FJobName;
	System::Classes::TStrings* FUserIds;
	System::UnicodeString FJobId;
	bool FCanPrint;
	int FStepDefin;
	bool FNeedPrjRight;
	void __fastcall SetUserIds(System::Classes::TStrings* const Value);
	TWorkflowUserManager* __fastcall GetUserManager(void);
	System::UnicodeString __fastcall GetJobId(void);
	System::UnicodeString __fastcall GetJobName(void);
	
public:
	__fastcall virtual TWorkflowJob(System::Classes::TCollection* Collection);
	__fastcall virtual ~TWorkflowJob(void);
	__property TWorkflowUserManager* UserManager = {read=GetUserManager};
	
__published:
	__property bool CanPrint = {read=FCanPrint, write=FCanPrint, nodefault};
	__property int StepDefin = {read=FStepDefin, write=FStepDefin, nodefault};
	__property System::UnicodeString JobId = {read=GetJobId, write=FJobId};
	__property System::UnicodeString JobName = {read=GetJobName, write=FJobName};
	__property System::Classes::TStrings* UserIds = {read=FUserIds, write=SetUserIds};
	__property bool NeedPrjRight = {read=FNeedPrjRight, write=FNeedPrjRight, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TWorkflowJobs;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowJobs : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TWorkflowJob* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TWorkflowJob* __fastcall GetItem(int Index);
	
public:
	TWorkflowJob* __fastcall FindByName(System::UnicodeString AName);
	TWorkflowJob* __fastcall FindByID(System::UnicodeString AId);
	HIDESBASE TWorkflowJob* __fastcall Add(void)/* overload */;
	HIDESBASE TWorkflowJob* __fastcall Add(System::UnicodeString AJobName)/* overload */;
	HIDESBASE TWorkflowJob* __fastcall Add(System::UnicodeString AJobID, System::UnicodeString AJobName)/* overload */;
	__property TWorkflowJob* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TWorkflowJobs(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWorkflowJobs(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TWorkflowUserManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TWorkflowUsers* FUsers;
	TWorkflowGroups* FGroups;
	TWorkflowJobs* FJobs;
	TWorkflowDepartments* FDepartments;
	System::UnicodeString FLoggedUserId;
	System::UnicodeString FLoggedUserCode;
	TCustomWorkflowStudio* FWorkflowStudio;
	
public:
	__fastcall TWorkflowUserManager(System::Classes::TComponent* AOwner, TCustomWorkflowStudio* AWorkflowStudio);
	__fastcall virtual ~TWorkflowUserManager(void);
	void __fastcall GetAssignedUserList(TTaskAssignedUsers* AAssignedUsers, System::Classes::TStringList* AUserList, System::UnicodeString AProjectID);
	void __fastcall LoadWorkflowUsers(void);
	void __fastcall LoadWorkflowGroups(void);
	void __fastcall LoadWorkflowJobs(void);
	void __fastcall LoadWorkflowDepartments(void);
	void __fastcall FillAssignmentList(System::Classes::TStrings* AList, bool AddObjects = false);
	void __fastcall FillUserList(System::Classes::TStrings* AList, bool AddObjects = false);
	void __fastcall FillGroupList(System::Classes::TStrings* AList, bool AddObjects = false);
	void __fastcall FillJobList(System::Classes::TStrings* AList, bool AddObjects = false);
	void __fastcall FillDepartmentList(System::Classes::TStrings* AList, bool AddObjects = false);
	bool __fastcall IsSameUser(System::UnicodeString AUserId1, System::UnicodeString AUserId2);
	bool __fastcall BelongsToGroup(System::UnicodeString AUserId, System::UnicodeString AGroupId);
	bool __fastcall BelongsToJob(System::UnicodeString AUserId, System::UnicodeString AJobId);
	bool __fastcall BelongsToDepartment(System::UnicodeString AUserId, System::UnicodeString ADepartmentId);
	bool __fastcall BelongsToAdminGroup(System::UnicodeString AUserId);
	bool __fastcall BelongsToProject(System::UnicodeString AUserId, System::UnicodeString AProjectId);
	__property TWorkflowUsers* Users = {read=FUsers};
	__property TWorkflowGroups* Groups = {read=FGroups};
	__property TWorkflowJobs* Jobs = {read=FJobs};
	__property TWorkflowDepartments* Departments = {read=FDepartments};
	__property System::UnicodeString LoggedUserId = {read=FLoggedUserId, write=FLoggedUserId};
	__property System::UnicodeString LoggedUserCode = {read=FLoggedUserCode, write=FLoggedUserCode};
};


struct DECLSPEC_DRECORD TEmailInformation
{
public:
	System::UnicodeString ToAddr;
	System::UnicodeString From;
	System::UnicodeString Bcc;
	System::UnicodeString Cc;
	System::UnicodeString Subject;
	System::UnicodeString Text;
};


struct DECLSPEC_DRECORD TFtpInformation
{
public:
	System::UnicodeString HostName;
	System::UnicodeString UserName;
	System::UnicodeString Password;
	System::UnicodeString Root;
	System::UnicodeString SpaceName;
	System::UnicodeString FtpDirectory;
	int Port;
	bool Passive;
};


//-- var, const, procedure ---------------------------------------------------
#define AllAttachmentPermissions (System::Set<TAttachmentPermission, TAttachmentPermission::apDelete, TAttachmentPermission::apEdit>() << TAttachmentPermission::apDelete << TAttachmentPermission::apInsert << TAttachmentPermission::apEdit )
#define wsFormName L"_wsFormName_"
}	/* namespace Wsclasses */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSCLASSES)
using namespace Wsclasses;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsclassesHPP
