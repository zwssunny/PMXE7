// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fApprovalEditor.pas' rev: 28.00 (Windows)

#ifndef FapprovaleditorHPP
#define FapprovaleditorHPP

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
#include <wsClasses.hpp>	// Pascal unit
#include <wsBlocks.hpp>	// Pascal unit
#include <fAttachPermissions.hpp>	// Pascal unit
#include <fFieldFrame.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit
#include <fStatusFrame.hpp>	// Pascal unit
#include <fExpirationFrame.hpp>	// Pascal unit
#include <fAssignedUserFrame.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fapprovaleditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmApprovalEditor;
class PASCALIMPLEMENTATION TfmApprovalEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* tsGeneral;
	Vcl::Stdctrls::TLabel* lbSubject;
	Vcl::Stdctrls::TEdit* edSubject;
	Vcl::Stdctrls::TLabel* lbDescription;
	Vcl::Stdctrls::TMemo* mmComments;
	Vcl::Comctrls::TTabSheet* tsStatus;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Stdctrls::TCheckBox* cbMailNotification;
	Vcl::Comctrls::TTabSheet* tsAttachments;
	Fattachpermissions::TfrAttachPermissions* frPermissions;
	Vcl::Comctrls::TTabSheet* tsFields;
	Ffieldframe::TfrFieldFrame* frFields;
	Vcl::Comctrls::TTabSheet* tsExpiration;
	Fstatusframe::TfrStatusFrame* frStatus;
	Fexpirationframe::TfrExpirationFrame* frExpiration;
	Fassigneduserframe::TfrAssignedUserFrame* frAssignedUser;
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	
private:
	Wsclasses::TCustomWorkflowDiagram* FDiagram;
	Wsclasses::TTaskDefinition* FTask;
	int FUpdatingControls;
	Wsclasses::TCustomWorkflowStudio* FWorkflowStudio;
	void __fastcall TaskToInterface(void);
	void __fastcall LoadTaskInEditors(Wsclasses::TTaskDefinition* ATask);
	void __fastcall SaveEditorsInTask(Wsclasses::TTaskDefinition* ATask);
	void __fastcall BeginUpdateControls(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall Localize(void);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	bool __fastcall EditApprovalDefinition(Wsblocks::TWorkflowApprovalBlock* ABlock, Wsclasses::TCustomWorkflowDiagram* ADiagram);
	__fastcall TfmApprovalEditor(System::Classes::TComponent* AOwner, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	__fastcall virtual ~TfmApprovalEditor(void);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmApprovalEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmApprovalEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfmApprovalEditor* fmApprovalEditor;
}	/* namespace Fapprovaleditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FAPPROVALEDITOR)
using namespace Fapprovaleditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FapprovaleditorHPP
