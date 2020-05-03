// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsMain.pas' rev: 28.00 (Windows)

#ifndef WsmainHPP
#define WsmainHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Data.DB.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsDB.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsBlocks.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsmain
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWorkflowManager;
class DELPHICLASS TWorkflowStudio;
class PASCALIMPLEMENTATION TWorkflowManager : public Wsclasses::TCustomWorkflowManager
{
	typedef Wsclasses::TCustomWorkflowManager inherited;
	
private:
	TWorkflowStudio* FWorkflowStudio;
	
public:
	__fastcall TWorkflowManager(System::Classes::TComponent* AOwner, TWorkflowStudio* AWorkflowStudio);
	__fastcall virtual ~TWorkflowManager(void);
	virtual void __fastcall LoadWorkflowDefinitionList(Wsclasses::TWorkflowDefinitions* WorkDefs);
	virtual Wsclasses::TWorkflowDefinition* __fastcall FindWorkflowDefinitionByName(System::UnicodeString AName);
	virtual void __fastcall ListWorkflowDefinitionNames(System::Classes::TStrings* AList, System::Classes::TStrings* BList);
	virtual Wsclasses::TWorkflowBizs* __fastcall CreateWorkflowBizList(void);
	virtual void __fastcall LoadWorkflowBizList(Wsclasses::TWorkflowBizs* WorkflowBizs);
	virtual void __fastcall LoadWorkflowBiz(Wsclasses::TWorkflowBiz* WorkflowBiz);
	virtual void __fastcall CheckWorkflowBiz(Wsclasses::TWorkflowBiz* WorkflowBiz, System::UnicodeString BizKeyValue, System::UnicodeString BillState);
	virtual void __fastcall UpdateWorkflowBiz(Wsclasses::TWorkflowBiz* WorkflowBiz, Wsclasses::TWorkflowInstance* WorkIns);
	virtual Wsclasses::TWorkflowDefinitions* __fastcall CreateWorkflowDefinitionList(void);
	virtual Wsclasses::TWorkflowInstance* __fastcall CreateWorkflowInstance(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual Wsclasses::TWorkflowInstance* __fastcall CreateWorkflowInstanceByName(System::UnicodeString WorkDefName);
	virtual Wsclasses::TWorkflowInstance* __fastcall CreateWorkflowInstanceByKey(System::UnicodeString AKey);
	virtual Wsclasses::TWorkflowInstance* __fastcall FindWorkflowInstanceByKey(System::UnicodeString AKey);
	virtual void __fastcall ListPendingWorkflowInstances(System::Classes::TStrings* AKeyList);
	virtual void __fastcall DeleteWorkflowInstance(Wsclasses::TWorkflowInstance* WorkIns);
	virtual void __fastcall DeleteWorkflowInstanceByKey(System::UnicodeString WorkInsKey);
	virtual void __fastcall SignalWorkflowInstance(System::UnicodeString AKey);
	virtual void __fastcall LoadWorkflowInstance(Wsclasses::TWorkflowInstance* WorkIns);
	virtual void __fastcall SaveWorkflowInstance(Wsclasses::TWorkflowInstance* WorkIns);
	virtual void __fastcall SaveWorkflowDefinition(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall LoadWorkflowDefinition(System::UnicodeString AKey, Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall DeleteWorkflowDefinition(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall AssignWorkflowInstanceDiagram(Wsclasses::TCustomWorkflowDiagram* ADiagram, System::UnicodeString WorkInsKey);
};


class DELPHICLASS TTaskManager;
class PASCALIMPLEMENTATION TTaskManager : public Wsclasses::TCustomTaskManager
{
	typedef Wsclasses::TCustomTaskManager inherited;
	
private:
	TWorkflowStudio* FWorkflowStudio;
	
public:
	__fastcall TTaskManager(System::Classes::TComponent* AOwner, TWorkflowStudio* AWorkflowStudio);
	virtual void __fastcall CreateTaskInstance(Wsclasses::TWorkflowInstance* WorkIns, Wsclasses::TTaskDefinition* TaskDef);
	virtual void __fastcall LoadTaskInstance(Wsclasses::TTaskInstance* TaskIns);
	virtual void __fastcall SaveTaskInstance(Wsclasses::TTaskInstance* TaskIns);
	virtual void __fastcall UpdateTaskInstance(Wsclasses::TTaskInstance* TaskIns);
	virtual bool __fastcall IsTaskFinished(System::UnicodeString AKey);
	virtual void __fastcall LoadTaskInstanceList(Wsclasses::TTaskInstanceList* ATasks, Wsclasses::TTaskFilterType AFilterType, System::UnicodeString AFilterKey, int completeState, System::UnicodeString AOtherCondition = System::UnicodeString());
	virtual System::TDateTime __fastcall TaskExpirationDateTime(Wsclasses::TWorkflowInstance* AWorkIns, Wsclasses::TTaskInstance* ATaskInstance);
	virtual void __fastcall LogTaskInfo(Wsclasses::TTaskInstance* TaskIns, System::UnicodeString Info);
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TTaskManager(void) { }
	
};


enum DECLSPEC_DENUM TWorkflowFormMode : unsigned char { wfmModal, wfmMDI };

class DELPHICLASS TCustomWorkflowUserInterface;
class PASCALIMPLEMENTATION TCustomWorkflowUserInterface : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TWorkflowStudio* FWorkflowStudio;
	
protected:
	__property TWorkflowStudio* WorkflowStudio = {read=FWorkflowStudio};
	
public:
	__fastcall TCustomWorkflowUserInterface(System::Classes::TComponent* AOwner, TWorkflowStudio* AWorkflowStudio);
	virtual void __fastcall ShowUserTasksDlg(System::UnicodeString AUserKey, TWorkflowFormMode AFormMode = (TWorkflowFormMode)(0x0)) = 0 ;
	virtual void __fastcall ShowUsersTasksDlg(System::UnicodeString AUserKeys, TWorkflowFormMode AFormMode = (TWorkflowFormMode)(0x0)) = 0 ;
	virtual void __fastcall ShowWorkInsTasksDlg(System::UnicodeString AWorkInsKey, TWorkflowFormMode AFormMode = (TWorkflowFormMode)(0x0)) = 0 ;
	virtual void __fastcall ShowWorkflowDefinitionsDlg(void) = 0 ;
	virtual void __fastcall EditWorkflowDefinition(Wsclasses::TWorkflowDefinition* AWorkDef) = 0 ;
	virtual void __fastcall EditWorkflowInstance(Wsclasses::TWorkflowInstance* AWorkIns) = 0 ;
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomWorkflowUserInterface(void) { }
	
};


typedef System::TMetaClass* TUserInterfaceClass;

typedef void __fastcall (__closure *TSendFtpFileEvent)(System::TObject* Sender, Wsclasses::TAttachmentItem* AttachmentItem, const Wsclasses::TFtpInformation &AFtpInfo, bool &Sent);

typedef void __fastcall (__closure *TGetFtpFileEvent)(System::TObject* Sender, Wsclasses::TAttachmentItem* AttachmentItem, const Wsclasses::TFtpInformation &AFtpInfo, bool &Get);

typedef void __fastcall (__closure *TSendMailEvent)(System::TObject* Sender, Wsclasses::TTaskInstance* TaskIns, Wsclasses::TWorkflowUser* AUser, const Wsclasses::TEmailInformation &AEmailInfo, bool &Sent);

typedef void __fastcall (__closure *TWorkInsErrorEvent)(System::TObject* Sender, Wsclasses::TWorkflowInstance* WI, System::UnicodeString ErrMsg, bool &ShowError);

typedef void __fastcall (__closure *TWorkflowInstanceEvent)(System::TObject* Sender, Wsclasses::TWorkflowInstance* AWorkIns);

class PASCALIMPLEMENTATION TWorkflowStudio : public Wsclasses::TCustomWorkflowStudio
{
	typedef Wsclasses::TCustomWorkflowStudio inherited;
	
private:
	Wsdb::TCustomWorkflowDB* FWorkflowDB;
	TCustomWorkflowUserInterface* FInternalUserInterface;
	TSendMailEvent FOnSendMail;
	TSendFtpFileEvent FOnSendFtpFile;
	TGetFtpFileEvent FOnGetFtpFile;
	System::UnicodeString FFromEmail;
	Wsclasses::TFtpInformation FFtpInformation;
	TWorkInsErrorEvent FOnWorkInsError;
	TWorkflowInstanceEvent FOnRunFinished;
	TCustomWorkflowUserInterface* __fastcall GetUserInterface(void);
	void __fastcall SendGroupMail(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TWorkflowGroup* AGroup, const Wsclasses::TEmailInformation &EMailInfo);
	void __fastcall SendDepartmentMail(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TWorkflowDepartment* ADepartment, const Wsclasses::TEmailInformation &EMailInfo);
	void __fastcall SendJobMail(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TWorkflowJob* AJob, const Wsclasses::TEmailInformation &EMailInfo);
	Wsdb::TCustomWorkflowDB* __fastcall GetCustomWorkflowDB(void);
	void __fastcall SetCustomWorkflowDB(Wsdb::TCustomWorkflowDB* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TWorkflowStudio(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWorkflowStudio(void);
	bool __fastcall SendMail(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TWorkflowUser* AUser, const Wsclasses::TEmailInformation &EMailInfo);
	bool __fastcall SendFtpFile(Wsclasses::TAttachmentItem* AttachmentItem);
	bool __fastcall GetFtpFile(Wsclasses::TAttachmentItem* AttachmentItem);
	virtual void __fastcall WorkflowInstanceError(Wsclasses::TWorkflowInstance* WI, System::UnicodeString ErrMsg, bool &ShowError);
	virtual void __fastcall RunFinished(Wsclasses::TWorkflowInstance* WI);
	__property TCustomWorkflowUserInterface* UserInterface = {read=GetUserInterface};
	
__published:
	__property Wsdb::TCustomWorkflowDB* WorkflowDB = {read=GetCustomWorkflowDB, write=SetCustomWorkflowDB};
	__property System::UnicodeString FromEmail = {read=FFromEmail, write=FFromEmail};
	
public:
	__property Wsclasses::TFtpInformation FtpInformation = {read=FFtpInformation, write=FFtpInformation};
	
__published:
	__property TSendMailEvent OnSendMail = {read=FOnSendMail, write=FOnSendMail};
	__property TSendFtpFileEvent OnSendFtpFile = {read=FOnSendFtpFile, write=FOnSendFtpFile};
	__property TGetFtpFileEvent OnGetFtpFile = {read=FOnGetFtpFile, write=FOnGetFtpFile};
	__property TWorkInsErrorEvent OnWorkInsError = {read=FOnWorkInsError, write=FOnWorkInsError};
	__property TWorkflowInstanceEvent OnRunFinished = {read=FOnRunFinished, write=FOnRunFinished};
	__property OnAfterExecuteNode;
	__property OnBeforeExecuteNode;
	__property OnTaskCreated;
	__property OnTaskFinished;
	__property OnGetNow;
	__property BeforeSaveTaskInstance;
	__property OnInitializeScriptEngine;
};


typedef System::TMetaClass* TWorkflowScriptEngineClass;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TWorkflowScriptEngineClass ScriptEngineClass;
extern DELPHI_PACKAGE TUserInterfaceClass UserInterfaceClass;
extern DELPHI_PACKAGE System::Sysutils::TFormatSettings UserfmtSettings;
}	/* namespace Wsmain */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSMAIN)
using namespace Wsmain;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsmainHPP
