// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fTaskEditor.pas' rev: 28.00 (Windows)

#ifndef FtaskeditorHPP
#define FtaskeditorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <fAttachPermissions.hpp>	// Pascal unit
#include <fFieldFrame.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <fStatusFrame.hpp>	// Pascal unit
#include <fExpirationFrame.hpp>	// Pascal unit
#include <fAssignedUserFrame.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ftaskeditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmTaskEditor;
class PASCALIMPLEMENTATION TfmTaskEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* tsGeneral;
	Vcl::Comctrls::TListView* lvTasks;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* edSubject;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TMemo* mmComments;
	Vcl::Buttons::TSpeedButton* btAdd;
	Vcl::Buttons::TSpeedButton* btDelete;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Stdctrls::TCheckBox* cbMailNotification;
	Vcl::Comctrls::TTabSheet* tsAttachment;
	Fattachpermissions::TfrAttachPermissions* frPermissions;
	Vcl::Comctrls::TTabSheet* tsFields;
	Ffieldframe::TfrFieldFrame* frFields;
	Fstatusframe::TfrStatusFrame* frStatus;
	Vcl::Comctrls::TTabSheet* tsExpiration;
	Fexpirationframe::TfrExpirationFrame* frExpiration;
	Fassigneduserframe::TfrAssignedUserFrame* frAssignedUser;
	Vcl::Stdctrls::TButton* btCopy;
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall lvTasksSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall lvTasksEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall btCopyClick(System::TObject* Sender);
	
private:
	Wsclasses::TCustomWorkflowDiagram* FDiagram;
	Wsclasses::TTaskDefinitions* FTasks;
	Wsclasses::TTaskDefinition* FLastTask;
	int FUpdatingControls;
	Wsclasses::TCustomWorkflowStudio* FWorkflowStudio;
	void __fastcall TasksToInterface(void);
	void __fastcall UpdateListItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TTaskDefinition* ATask);
	void __fastcall LoadTaskInEditors(Wsclasses::TTaskDefinition* ATask);
	void __fastcall ClearEditors(void);
	void __fastcall SaveEditorsInTask(Wsclasses::TTaskDefinition* ATask);
	void __fastcall DeleteCurrentTask(void);
	void __fastcall BeginUpdateControls(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall SaveTask(void);
	void __fastcall Localize(void);
	Wsclasses::TTaskDefinition* __fastcall TaskDefFromItem(Vcl::Comctrls::TListItem* AItem);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	bool __fastcall EditTaskDefinitions(Wsclasses::TTaskDefinitions* ATasks, Wsclasses::TCustomWorkflowDiagram* ADiagram);
	__fastcall TfmTaskEditor(System::Classes::TComponent* AOwner, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	__fastcall virtual ~TfmTaskEditor(void);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmTaskEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmTaskEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfmTaskEditor* fmTaskEditor;
}	/* namespace Ftaskeditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FTASKEDITOR)
using namespace Ftaskeditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FtaskeditorHPP
