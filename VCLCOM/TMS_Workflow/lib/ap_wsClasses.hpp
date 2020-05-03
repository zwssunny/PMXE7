// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ap_wsClasses.pas' rev: 28.00 (Windows)

#ifndef Ap_wsclassesHPP
#define Ap_wsclassesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Data.DB.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit
#include <atScript.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ap_wsclasses
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TatwsClassesLibrary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatwsClassesLibrary : public Atscript::TatScripterLibrary
{
	typedef Atscript::TatScripterLibrary inherited;
	
public:
	void __fastcall __GetTWorkflowDefinitionDiagram(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowDefinitionName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __SetTWorkflowDefinitionName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowDefinitionsAdd(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowDefinitionsFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowDefinitionsItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowInstanceDiagram(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowVariablesAdd(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowVariablesFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowVariablesItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TAttachmentItemLoadContentFromFile(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TAttachmentItemSaveContentToFile(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TAttachmentItemOpen(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTAttachmentItemExtension(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TAttachmentItemsAdd(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TAttachmentItemsFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TAttachmentItemsAddFile(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTAttachmentItemsItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowAttachmentsAdd(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowAttachmentsFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowAttachmentsAddFile(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowAttachmentsItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowDiagramWorkflowInstance(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TTaskFieldAssign(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TTaskFieldsAdd(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTTaskFieldsItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TTaskDefinitionIsCompletionStatus(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTTaskDefinitionInitialStatus(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TTaskDefinitionsAdd(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TTaskDefinitionsFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTTaskDefinitionsItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TTaskInstanceIsCompletionStatus(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTTaskInstanceCompleted(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowScriptEngineCalculateExpression(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowScriptEngineTranslateText(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowUsersFindById(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowUsersFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowUsersItems(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __TWorkflowGroupsFindByName(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __GetTWorkflowGroupsItems(Atscript::TatVirtualMachine* AMachine);
	virtual void __fastcall Init(void);
	__classmethod virtual System::UnicodeString __fastcall LibraryName();
public:
	/* TatScripterLibrary.Create */ inline __fastcall virtual TatwsClassesLibrary(Atscript::TatCustomScripter* AScripter) : Atscript::TatScripterLibrary(AScripter) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TatwsClassesLibrary(void) { }
	
};

#pragma pack(pop)

typedef System::TMetaClass* EWorkflowExceptionClass;

typedef System::TMetaClass* TWorkflowDefinitionClass;

typedef System::TMetaClass* TWorkflowDefinitionsClass;

typedef System::TMetaClass* TWorkflowInstanceClass;

typedef System::TMetaClass* TWorkflowVariableClass;

typedef System::TMetaClass* TWorkflowVariablesClass;

typedef System::TMetaClass* TAttachmentItemClass;

typedef System::TMetaClass* TAttachmentItemsClass;

typedef System::TMetaClass* TWorkflowAttachmentClass;

typedef System::TMetaClass* TWorkflowAttachmentsClass;

typedef System::TMetaClass* TWorkflowDiagramClass;

typedef System::TMetaClass* TTaskFieldClass;

typedef System::TMetaClass* TTaskFieldsClass;

typedef System::TMetaClass* TTaskDefinitionClass;

typedef System::TMetaClass* TTaskDefinitionsClass;

typedef System::TMetaClass* TTaskInstanceClass;

typedef System::TMetaClass* TWorkflowScriptEngineClass;

typedef System::TMetaClass* TWorkflowUserClass;

typedef System::TMetaClass* TWorkflowUsersClass;

typedef System::TMetaClass* TWorkflowGroupClass;

typedef System::TMetaClass* TWorkflowGroupsClass;

class DELPHICLASS TEmailInformationWrapper;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TEmailInformationWrapper : public Atscript::TatRecordWrapper
{
	typedef Atscript::TatRecordWrapper inherited;
	
private:
	System::UnicodeString FToAddr;
	System::UnicodeString FFrom;
	System::UnicodeString FBcc;
	System::UnicodeString FCc;
	System::UnicodeString FSubject;
	System::UnicodeString FText;
	
public:
	__fastcall TEmailInformationWrapper(const Wsclasses::TEmailInformation &ARecord);
	Wsclasses::TEmailInformation __fastcall ObjToRec(void);
	
__published:
	__property System::UnicodeString ToAddr = {read=FToAddr, write=FToAddr};
	__property System::UnicodeString From = {read=FFrom, write=FFrom};
	__property System::UnicodeString Bcc = {read=FBcc, write=FBcc};
	__property System::UnicodeString Cc = {read=FCc, write=FCc};
	__property System::UnicodeString Subject = {read=FSubject, write=FSubject};
	__property System::UnicodeString Text = {read=FText, write=FText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEmailInformationWrapper(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ap_wsclasses */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_AP_WSCLASSES)
using namespace Ap_wsclasses;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ap_wsclassesHPP
