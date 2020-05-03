// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsDB.pas' rev: 28.00 (Windows)

#ifndef WsdbHPP
#define WsdbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Data.DB.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsdb
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TwsBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TwsBindary : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::UnicodeString FKeyField;
	System::Classes::TComponent* FWorkflowDB;
	System::UnicodeString FTableName;
	
protected:
	__property System::Classes::TComponent* WorkflowDB = {read=FWorkflowDB};
	
public:
	__fastcall virtual TwsBindary(System::Classes::TComponent* AWorkflowDB);
	__fastcall virtual ~TwsBindary(void);
	
__published:
	__property System::UnicodeString TableName = {read=FTableName, write=FTableName};
	__property System::UnicodeString KeyField = {read=FKeyField, write=FKeyField};
};

#pragma pack(pop)

class DELPHICLASS TWorkInsBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkInsBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FFlowMnFlowContentField;
	System::UnicodeString FFlowMnBusCodeField;
	System::UnicodeString FFlowMnBusWindowField;
	System::UnicodeString FFlowMnContentField;
	System::UnicodeString FFlowMnCreateTimeField;
	System::UnicodeString FFlowMnCreatorField;
	System::UnicodeString FFlowMnFKID_FlowField;
	System::UnicodeString FFlowMnLastUpdateTimeField;
	System::UnicodeString FFlowMnRankField;
	System::UnicodeString FFlowMnStateField;
	System::UnicodeString FFlowMnSubjectField;
	System::UnicodeString FFlowMoveTimeLimitField;
	System::UnicodeString FFlowMnReportField;
	System::UnicodeString FFlowMnFinishTimeField;
	System::UnicodeString FNextRunTimeField;
	System::UnicodeString FFlowMnPrjIDField;
	
public:
	__fastcall virtual TWorkInsBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString FlowMnFlowContentField = {read=FFlowMnFlowContentField, write=FFlowMnBusCodeField};
	__property System::UnicodeString FlowMnBusCodeField = {read=FFlowMnBusCodeField, write=FFlowMnBusCodeField};
	__property System::UnicodeString FlowMnBusWindowField = {read=FFlowMnBusWindowField, write=FFlowMnBusWindowField};
	__property System::UnicodeString FlowMnContentField = {read=FFlowMnContentField, write=FFlowMnContentField};
	__property System::UnicodeString FlowMnCreateTimeField = {read=FFlowMnCreateTimeField, write=FFlowMnCreateTimeField};
	__property System::UnicodeString FlowMnCreatorField = {read=FFlowMnCreatorField, write=FFlowMnCreatorField};
	__property System::UnicodeString FlowMnFKID_FlowField = {read=FFlowMnFKID_FlowField, write=FFlowMnFKID_FlowField};
	__property System::UnicodeString FlowMnLastUpdateTimeField = {read=FFlowMnLastUpdateTimeField, write=FFlowMnLastUpdateTimeField};
	__property System::UnicodeString FlowMnRankField = {read=FFlowMnRankField, write=FFlowMnRankField};
	__property System::UnicodeString FlowMnStateField = {read=FFlowMnStateField, write=FFlowMnStateField};
	__property System::UnicodeString FlowMnSubjectField = {read=FFlowMnSubjectField, write=FFlowMnSubjectField};
	__property System::UnicodeString FlowMoveTimeLimitField = {read=FFlowMoveTimeLimitField, write=FFlowMoveTimeLimitField};
	__property System::UnicodeString FlowMnReportField = {read=FFlowMnReportField, write=FFlowMnReportField};
	__property System::UnicodeString FlowMnFinishTimeField = {read=FFlowMnFinishTimeField, write=FFlowMnFinishTimeField};
	__property System::UnicodeString NextRunTimeField = {read=FNextRunTimeField, write=FNextRunTimeField};
	__property System::UnicodeString FlowMnPrjIDField = {read=FFlowMnPrjIDField, write=FFlowMnPrjIDField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TWorkInsBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkDefBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkDefBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FFlowDnContentField;
	System::UnicodeString FFlowDnNameField;
	System::UnicodeString FFlowDnExplanField;
	System::UnicodeString FFlowDnFKID_ClsField;
	System::UnicodeString FFlowDnIsPublicField;
	System::UnicodeString FFlowDnIsTermField;
	System::UnicodeString FFlowDnDateField;
	System::UnicodeString FFlowDnCreatorField;
	
public:
	__fastcall virtual TWorkDefBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString FlowDnContentField = {read=FFlowDnContentField, write=FFlowDnContentField};
	__property System::UnicodeString FlowDnNameField = {read=FFlowDnNameField, write=FFlowDnNameField};
	__property System::UnicodeString FlowDnExplanField = {read=FFlowDnExplanField, write=FFlowDnExplanField};
	__property System::UnicodeString FlowDnIsPublicField = {read=FFlowDnIsPublicField, write=FFlowDnIsPublicField};
	__property System::UnicodeString FlowDnIsTermField = {read=FFlowDnIsTermField, write=FFlowDnIsTermField};
	__property System::UnicodeString FlowDnDateField = {read=FFlowDnDateField, write=FFlowDnDateField};
	__property System::UnicodeString FlowDnCreatorField = {read=FFlowDnCreatorField, write=FFlowDnCreatorField};
	__property System::UnicodeString FlowDnFKID_ClsField = {read=FFlowDnFKID_ClsField, write=FFlowDnFKID_ClsField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TWorkDefBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkBizBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkBizBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FBizFormIDField;
	System::UnicodeString FBizNameField;
	System::UnicodeString FBizTableNameField;
	System::UnicodeString FBizKeyField;
	System::UnicodeString FBizCheckField;
	System::UnicodeString FBizCheckerField;
	System::UnicodeString FBizCheckDateField;
	System::UnicodeString FBizEditMenuIDField;
	System::UnicodeString FBizCheckValueField;
	
public:
	__fastcall virtual TWorkBizBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString BizFormIDField = {read=FBizFormIDField, write=FBizFormIDField};
	__property System::UnicodeString BizNameField = {read=FBizNameField, write=FBizNameField};
	__property System::UnicodeString BizTableNameField = {read=FBizTableNameField, write=FBizTableNameField};
	__property System::UnicodeString BizKeyField = {read=FBizKeyField, write=FBizKeyField};
	__property System::UnicodeString BizCheckField = {read=FBizCheckField, write=FBizCheckField};
	__property System::UnicodeString BizCheckerField = {read=FBizCheckerField, write=FBizCheckerField};
	__property System::UnicodeString BizCheckDateField = {read=FBizCheckDateField, write=FBizCheckDateField};
	__property System::UnicodeString BizEditMenuIDField = {read=FBizEditMenuIDField, write=FBizEditMenuIDField};
	__property System::UnicodeString BizCheckValueField = {read=FBizCheckValueField, write=FBizCheckValueField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TWorkBizBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskInsBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskInsBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FFlowMnDtlFKIDField;
	System::UnicodeString FFlowMnDtlNameField;
	System::UnicodeString FFlowMnDtlSenderField;
	System::UnicodeString FFlowMnDtlTaskContentField;
	System::UnicodeString FFlowMnDtlStateField;
	System::UnicodeString FFlowMnDtlResultsField;
	System::UnicodeString FFlowMnDtlChkTimeField;
	System::UnicodeString FFlowMnDtlCommentsField;
	System::UnicodeString FFlowMnDtlLimitTimeField;
	System::UnicodeString FFlowMnDtlNumField;
	System::UnicodeString FFlowMnDtlPrintRightField;
	System::UnicodeString FFlowMnDtlReceiverField;
	System::UnicodeString FFlowMnDtlRemarkField;
	System::UnicodeString FFlowMnDtlSendTimeField;
	System::UnicodeString FFlowMnDtlStateChgTimeField;
	System::UnicodeString FFlowMnDtlUserTypeField;
	System::UnicodeString FFlowMnDtlStepField;
	System::UnicodeString FFlowMnDtlNeedPrjRightField;
	System::UnicodeString FFlowMnDtlPrjIDField;
	
public:
	__fastcall virtual TTaskInsBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString FlowMnDtlTaskContentField = {read=FFlowMnDtlTaskContentField, write=FFlowMnDtlTaskContentField};
	__property System::UnicodeString FlowMnDtlSenderField = {read=FFlowMnDtlSenderField, write=FFlowMnDtlSenderField};
	__property System::UnicodeString FlowMnDtlNameField = {read=FFlowMnDtlNameField, write=FFlowMnDtlNameField};
	__property System::UnicodeString FlowMnDtlFKIDField = {read=FFlowMnDtlFKIDField, write=FFlowMnDtlFKIDField};
	__property System::UnicodeString FlowMnDtlStateField = {read=FFlowMnDtlStateField, write=FFlowMnDtlStateField};
	__property System::UnicodeString FlowMnDtlResultsField = {read=FFlowMnDtlResultsField, write=FFlowMnDtlResultsField};
	__property System::UnicodeString FlowMnDtlChkTimeField = {read=FFlowMnDtlChkTimeField, write=FFlowMnDtlChkTimeField};
	__property System::UnicodeString FlowMnDtlCommentsField = {read=FFlowMnDtlCommentsField, write=FFlowMnDtlCommentsField};
	__property System::UnicodeString FlowMnDtlLimitTimeField = {read=FFlowMnDtlLimitTimeField, write=FFlowMnDtlLimitTimeField};
	__property System::UnicodeString FlowMnDtlNumField = {read=FFlowMnDtlNumField, write=FFlowMnDtlNumField};
	__property System::UnicodeString FlowMnDtlPrintRightField = {read=FFlowMnDtlPrintRightField, write=FFlowMnDtlPrintRightField};
	__property System::UnicodeString FlowMnDtlReceiverField = {read=FFlowMnDtlReceiverField, write=FFlowMnDtlReceiverField};
	__property System::UnicodeString FlowMnDtlRemarkField = {read=FFlowMnDtlRemarkField, write=FFlowMnDtlRemarkField};
	__property System::UnicodeString FlowMnDtlSendTimeField = {read=FFlowMnDtlSendTimeField, write=FFlowMnDtlSendTimeField};
	__property System::UnicodeString FlowMnDtlStateChgTimeField = {read=FFlowMnDtlStateChgTimeField, write=FFlowMnDtlStateChgTimeField};
	__property System::UnicodeString FlowMnDtlUserTypeField = {read=FFlowMnDtlUserTypeField, write=FFlowMnDtlUserTypeField};
	__property System::UnicodeString FlowMnDtlStepField = {read=FFlowMnDtlStepField, write=FFlowMnDtlStepField};
	__property System::UnicodeString FlowMnDtlNeedPrjRightField = {read=FFlowMnDtlNeedPrjRightField, write=FFlowMnDtlNeedPrjRightField};
	__property System::UnicodeString FlowMnDtlPrjIDField = {read=FFlowMnDtlPrjIDField, write=FFlowMnDtlPrjIDField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TTaskInsBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TAttachmentBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TAttachmentBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FContentField;
	System::UnicodeString FWorkKeyField;
	System::UnicodeString FCreatedOnField;
	System::UnicodeString FObjectTypeField;
	
public:
	__fastcall virtual TAttachmentBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString ContentField = {read=FContentField, write=FContentField};
	__property System::UnicodeString WorkKeyField = {read=FWorkKeyField, write=FWorkKeyField};
	__property System::UnicodeString CreatedOnField = {read=FCreatedOnField, write=FCreatedOnField};
	__property System::UnicodeString ObjectTypeField = {read=FObjectTypeField, write=FObjectTypeField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TAttachmentBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskLogBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskLogBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FFlowTaskLogTaskInsIDField;
	System::UnicodeString FFlowTaskInsField;
	System::UnicodeString FFlowTaskLogDateField;
	System::UnicodeString FFlowTaskLogFlowInsIDField;
	System::UnicodeString FFlowTaskLogInfoField;
	System::UnicodeString FFlowTaskLogInfo2Field;
	System::UnicodeString FFlowTaskLogOperationField;
	System::UnicodeString FFlowTaskLogUserIDField;
	
public:
	__fastcall virtual TTaskLogBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString FlowTaskLogTaskInsIDField = {read=FFlowTaskLogTaskInsIDField, write=FFlowTaskLogTaskInsIDField};
	__property System::UnicodeString FlowTaskInsField = {read=FFlowTaskInsField, write=FFlowTaskInsField};
	__property System::UnicodeString FlowTaskLogDateField = {read=FFlowTaskLogDateField, write=FFlowTaskLogDateField};
	__property System::UnicodeString FlowTaskLogFlowInsIDField = {read=FFlowTaskLogFlowInsIDField, write=FFlowTaskLogFlowInsIDField};
	__property System::UnicodeString FlowTaskLogInfoField = {read=FFlowTaskLogInfoField, write=FFlowTaskLogInfoField};
	__property System::UnicodeString FlowTaskLogInfo2Field = {read=FFlowTaskLogInfo2Field, write=FFlowTaskLogInfo2Field};
	__property System::UnicodeString FlowTaskLogOperationField = {read=FFlowTaskLogOperationField, write=FFlowTaskLogOperationField};
	__property System::UnicodeString FlowTaskLogUserIDField = {read=FFlowTaskLogUserIDField, write=FFlowTaskLogUserIDField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TTaskLogBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TUserBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TUserBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FUserNameField;
	System::UnicodeString FUserCodeField;
	System::UnicodeString FEmailField;
	System::UnicodeString FPhoneCodeField;
	System::UnicodeString FDepartmentField;
	
public:
	__fastcall virtual TUserBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString UserNameField = {read=FUserNameField, write=FUserNameField};
	__property System::UnicodeString UserCodeField = {read=FUserCodeField, write=FUserCodeField};
	__property System::UnicodeString EmailField = {read=FEmailField, write=FEmailField};
	__property System::UnicodeString PhoneCodeField = {read=FPhoneCodeField, write=FPhoneCodeField};
	__property System::UnicodeString DepartmentField = {read=FDepartmentField, write=FDepartmentField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TUserBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGroupBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGroupBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FGroupNameField;
	System::UnicodeString FIsAdminField;
	
public:
	__fastcall virtual TGroupBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString GroupNameField = {read=FGroupNameField, write=FGroupNameField};
	__property System::UnicodeString IsAdminField = {read=FIsAdminField, write=FIsAdminField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TGroupBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TDepartmentBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDepartmentBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FDepartmentNameField;
	System::UnicodeString FDepartmentManagerIdField;
	
public:
	__fastcall virtual TDepartmentBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString DepartmentNameField = {read=FDepartmentNameField, write=FDepartmentNameField};
	__property System::UnicodeString DepartmentManagerIdField = {read=FDepartmentManagerIdField, write=FDepartmentManagerIdField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TDepartmentBindary(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TJobBindary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TJobBindary : public TwsBindary
{
	typedef TwsBindary inherited;
	
private:
	System::UnicodeString FJobNameField;
	
public:
	__fastcall virtual TJobBindary(System::Classes::TComponent* AWorkflowDB);
	
__published:
	__property System::UnicodeString JobNameField = {read=FJobNameField, write=FJobNameField};
public:
	/* TwsBindary.Destroy */ inline __fastcall virtual ~TJobBindary(void) { }
	
};

#pragma pack(pop)

typedef void __fastcall (__closure *TCreateQueryEvent)(System::TObject* Sender, System::UnicodeString SQL, Data::Db::TDataSet* &Dataset, bool &Done);

typedef void __fastcall (__closure *TAssignSQLParamsEvent)(System::TObject* Sender, Data::Db::TDataSet* Dataset, Data::Db::TParams* AParams, bool &Done);

typedef void __fastcall (__closure *TExecuteQueryEvent)(System::TObject* Sender, Data::Db::TDataSet* Dataset, bool &Done);

enum DECLSPEC_DENUM TAttachmentParentType : unsigned char { ptDefinition, ptInstance };

class DELPHICLASS TCustomWorkflowDB;
class PASCALIMPLEMENTATION TCustomWorkflowDB : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TWorkInsBindary* FWorkInsBindary;
	TTaskInsBindary* FTaskInsBindary;
	TWorkDefBindary* FWorkDefBindary;
	TTaskLogBindary* FTaskLogBindary;
	TAttachmentBindary* FAttachmentBindary;
	TUserBindary* FUserBindary;
	TGroupBindary* FGroupBindary;
	TDepartmentBindary* FDepartmentBindary;
	TJobBindary* FJobBindary;
	TWorkBizBindary* FWorkBizBindary;
	Data::Db::TParams* FParams;
	TCreateQueryEvent FOnCreateQuery;
	TExecuteQueryEvent FOnExecuteQuery;
	TAssignSQLParamsEvent FOnAssignSQLParams;
	bool FDestroyQueries;
	bool FStructureChecked;
	void __fastcall WorkflowDefinitionLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowDefinition* WorkDef);
	void __fastcall WorkflowInstanceLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowInstance* WorkIns);
	void __fastcall TaskInstanceLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TTaskInstance* TaskIns);
	void __fastcall TaskLogLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TTaskLogItem* LogItem);
	void __fastcall AttachmentItemLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TAttachmentItem* AItem);
	Data::Db::TDataSet* __fastcall OpenQuery(System::UnicodeString SQL, Data::Db::TParams* Params);
	void __fastcall ExecuteQuery(System::UnicodeString SQL, Data::Db::TParams* Params);
	Data::Db::TDataSet* __fastcall OpenSysQuery(System::UnicodeString SQL, Data::Db::TParams* Params);
	void __fastcall ExecuteSysQuery(System::UnicodeString SQL, Data::Db::TParams* Params);
	System::UnicodeString __fastcall MapOperationToStr(Wsclasses::TTaskLogOperation AOperation);
	Wsclasses::TTaskLogOperation __fastcall MapStrToOperation(System::UnicodeString AStr);
	System::UnicodeString __fastcall NewID(void);
	int __fastcall FindNextID(System::UnicodeString ATableName, System::UnicodeString AFieldName);
	virtual int __fastcall FindOtherNextID(System::UnicodeString ATableName, System::UnicodeString AKeyFieldName, System::UnicodeString ANumFieldName, System::UnicodeString AKeyValue);
	void __fastcall WorkflowDepartmentLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowDepartment* WorkDepartment);
	void __fastcall WorkflowJobLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowJob* WorkJob);
	void __fastcall WorkflowGroupLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowGroup* WorkGroup);
	void __fastcall WorkflowUserLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowUser* WorkUser);
	void __fastcall WorkflowBizLoadRecord(Data::Db::TDataSet* DS, Wsclasses::TWorkflowBiz* WorkflowBiz);
	void __fastcall CheckStructure(void);
	
protected:
	System::UnicodeString __fastcall ComponentToString(System::Classes::TComponent* AComp);
	void __fastcall ComponentFromString(System::Classes::TComponent* AComp, System::UnicodeString AStr);
	virtual System::UnicodeString __fastcall BlobFieldToString(Data::Db::TField* AField);
	virtual void __fastcall SetBlobParam(Data::Db::TParam* AParam, System::UnicodeString BlobStream);
	virtual void __fastcall DoOpenQuery(Data::Db::TDataSet* Dataset);
	virtual void __fastcall DoOpenSysQuery(Data::Db::TDataSet* Dataset);
	virtual Data::Db::TDataSet* __fastcall DoCreateQuery(System::UnicodeString SQL);
	virtual void __fastcall DoAssignSQLParams(Data::Db::TDataSet* Dataset, Data::Db::TParams* AParams);
	virtual void __fastcall DoExecuteQuery(Data::Db::TDataSet* Dataset);
	virtual void __fastcall DoExecuteSysQuery(Data::Db::TDataSet* Dataset);
	void __fastcall TaskInstancesDeleteByWorkIns(System::UnicodeString AWorkInsKey);
	void __fastcall SaveAttachments(Wsclasses::TCustomWorkflowDiagram* ADiagram, TAttachmentParentType AType, System::UnicodeString AWorkKey);
	void __fastcall LogTaskOperation(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TTaskLogOperation Operation, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio, System::UnicodeString Info1 = System::UnicodeString(), System::UnicodeString Info2 = System::UnicodeString());
	
public:
	__fastcall virtual TCustomWorkflowDB(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWorkflowDB(void);
	void __fastcall WorkflowDepartmentLoad(Wsclasses::TWorkflowDepartment* WorkDepartment);
	void __fastcall WorkflowDepartmentLoadList(Wsclasses::TWorkflowDepartments* WorkDepartments);
	void __fastcall WorkflowDepartmentFillUserIds(Wsclasses::TWorkflowDepartment* WorkDepartment);
	void __fastcall WorkflowJobLoad(Wsclasses::TWorkflowJob* WorkJob);
	void __fastcall WorkflowJobLoadList(Wsclasses::TWorkflowJobs* WorkJobs);
	void __fastcall WorkflowJobFillUserIds(Wsclasses::TWorkflowJob* WorkJob);
	void __fastcall WorkflowGroupLoad(Wsclasses::TWorkflowGroup* WorkGroup);
	void __fastcall WorkflowGroupLoadList(Wsclasses::TWorkflowGroups* WorkGroups);
	void __fastcall WorkflowGroupFillUserIds(Wsclasses::TWorkflowGroup* WorkGroup);
	void __fastcall WorkflowUserLoad(Wsclasses::TWorkflowUser* WorkUser);
	void __fastcall WorkflowUserLoadList(Wsclasses::TWorkflowUsers* WorkUsers);
	virtual void __fastcall TaskLogLoadList(Wsclasses::TTaskLogItems* ALogItems, Wsclasses::TLogFilterType ALogFilterType, System::UnicodeString AFilterKey);
	virtual void __fastcall TaskInstanceInsert(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	virtual void __fastcall TaskInstanceLoad(Wsclasses::TTaskInstance* TaskIns);
	virtual void __fastcall TaskInstanceUpdate(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio, bool Inserting = false);
	virtual void __fastcall TaskInstanceLoadList(Wsclasses::TTaskInstanceList* ATasks, Wsclasses::TTaskFilterType AFilterType, System::UnicodeString AFilterKey, int completeState, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio, System::UnicodeString AOtherCondition);
	virtual void __fastcall WorkflowInstanceInsert(Wsclasses::TWorkflowInstance* WorkIns, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	virtual bool __fastcall WorkflowInstanceLoad(Wsclasses::TWorkflowInstance* WorkIns);
	virtual void __fastcall WorkflowInstanceUpdate(Wsclasses::TWorkflowInstance* WorkIns);
	virtual void __fastcall WorkflowInstanceDelete(Wsclasses::TWorkflowInstance* WorkIns);
	virtual void __fastcall ListPendingWorkflowInstances(System::Classes::TStrings* AKeyList, System::TDateTime AToDate);
	virtual void __fastcall WorkflowDefinitionDelete(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall WorkflowDefinitionInsert(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall WorkflowDefinitionUpdate(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall WorkflowDefinitionLoad(Wsclasses::TWorkflowDefinition* WorkDef);
	virtual void __fastcall WorkflowDefinitionLoadList(Wsclasses::TWorkflowDefinitions* WorkDefs, System::UnicodeString AFlowType = System::UnicodeString());
	virtual void __fastcall ListWorkflowDefinitionNames(System::Classes::TStrings* AList, System::Classes::TStrings* BList);
	virtual void __fastcall WorkflowBizLoad(Wsclasses::TWorkflowBiz* WorkflowBiz);
	virtual void __fastcall WorkflowBizLoadList(Wsclasses::TWorkflowBizs* WorkflowBizs);
	virtual void __fastcall WorkflowBizCheck(Wsclasses::TWorkflowBiz* WorkflowBiz, System::UnicodeString BizKey, System::UnicodeString BillState, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	virtual void __fastcall WorkflowBizUpdate(Wsclasses::TWorkflowBiz* WorkflowBiz, Wsclasses::TWorkflowInstance* WorkIns, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	virtual bool __fastcall BelongsToProject(System::UnicodeString AUserID, System::UnicodeString AProjectID);
	virtual void __fastcall AttachmentItemInsert(Wsclasses::TAttachmentItem* AItem, TAttachmentParentType AType, System::UnicodeString AWorkKey);
	virtual bool __fastcall AttachmentItemLoad(Wsclasses::TAttachmentItem* AItem);
	virtual void __fastcall AttachmentItemUpdate(Wsclasses::TAttachmentItem* AItem, TAttachmentParentType AType, System::UnicodeString AWorkKey);
	void __fastcall LogTaskInfo(Wsclasses::TTaskInstance* TaskIns, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio, System::UnicodeString AInfo, System::UnicodeString AInfo2 = System::UnicodeString());
	__property TWorkInsBindary* WorkInsBindary = {read=FWorkInsBindary, write=FWorkInsBindary};
	__property TWorkDefBindary* WorkDefBindary = {read=FWorkDefBindary, write=FWorkDefBindary};
	__property TTaskInsBindary* TaskInsBindary = {read=FTaskInsBindary, write=FTaskInsBindary};
	__property TTaskLogBindary* TaskLogBindary = {read=FTaskLogBindary, write=FTaskLogBindary};
	__property TAttachmentBindary* AttachmentBindary = {read=FAttachmentBindary, write=FAttachmentBindary};
	__property TUserBindary* UserBindary = {read=FUserBindary, write=FUserBindary};
	__property TGroupBindary* GroupBindary = {read=FGroupBindary, write=FGroupBindary};
	__property TDepartmentBindary* DepartmentBindary = {read=FDepartmentBindary, write=FDepartmentBindary};
	__property TJobBindary* JobBindary = {read=FJobBindary, write=FJobBindary};
	__property TWorkBizBindary* WorkBizBindary = {read=FWorkBizBindary, write=FWorkBizBindary};
	__property TCreateQueryEvent OnCreateQuery = {read=FOnCreateQuery, write=FOnCreateQuery};
	__property TAssignSQLParamsEvent OnAssignSQLParams = {read=FOnAssignSQLParams, write=FOnAssignSQLParams};
	__property TExecuteQueryEvent OnExecuteQuery = {read=FOnExecuteQuery, write=FOnExecuteQuery};
	__property bool DestroyQueries = {read=FDestroyQueries, write=FDestroyQueries, nodefault};
};


class DELPHICLASS TWorkflowDB;
class PASCALIMPLEMENTATION TWorkflowDB : public TCustomWorkflowDB
{
	typedef TCustomWorkflowDB inherited;
	
__published:
	__property WorkInsBindary;
	__property WorkDefBindary;
	__property TaskInsBindary;
	__property TaskLogBindary;
	__property AttachmentBindary;
	__property UserBindary;
	__property GroupBindary;
	__property DepartmentBindary;
	__property JobBindary;
	__property OnCreateQuery;
	__property OnAssignSQLParams;
	__property OnExecuteQuery;
	__property DestroyQueries;
public:
	/* TCustomWorkflowDB.Create */ inline __fastcall virtual TWorkflowDB(System::Classes::TComponent* AOwner) : TCustomWorkflowDB(AOwner) { }
	/* TCustomWorkflowDB.Destroy */ inline __fastcall virtual ~TWorkflowDB(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall wsDBError(System::UnicodeString msg);
extern DELPHI_PACKAGE void __fastcall DiagramFromString(Livediagram::TLiveDiagram* Diagram, System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DiagramToString(Livediagram::TLiveDiagram* Diagram);
extern DELPHI_PACKAGE void __fastcall StateFromString(Livediagram::TLiveDiagram* Diagram, System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall StateToString(Livediagram::TLiveDiagram* Diagram);
}	/* namespace Wsdb */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSDB)
using namespace Wsdb;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsdbHPP
