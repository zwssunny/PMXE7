// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fAssignedUserFrame.pas' rev: 28.00 (Windows)

#ifndef FassigneduserframeHPP
#define FassigneduserframeHPP

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
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fassigneduserframe
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrAssignedUserFrame;
class PASCALIMPLEMENTATION TfrAssignedUserFrame : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Comctrls::TListView* lvAssignedUsers;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* btAdd;
	Vcl::Stdctrls::TButton* btDelete;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TComboBox* cbAssAssignedUserType;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TComboBox* cbAssAssignedUsers;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TCheckBox* cbCanPrint;
	Vcl::Stdctrls::TCheckBox* cbkAssignmentMode;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* cbStepDefin;
	Vcl::Stdctrls::TCheckBox* cbNeedPrjRight;
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall lvAssignedUsersSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall cbAssAssignedUserTypeChange(System::TObject* Sender);
	void __fastcall cbStepDefinKeyPress(System::TObject* Sender, System::WideChar &Key);
	
private:
	Wsclasses::TTaskAssignedUsers* FAssignedUsers;
	int FUpdatingControls;
	Wsclasses::TAssignedUserType FPreAssignedUserType;
	Wsclasses::TCustomWorkflowDiagram* FDiagram;
	void __fastcall BeginUpdateControls(void);
	void __fastcall DeleteCurrentVar(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall LoadVarInEditors(Wsclasses::TTaskAssignedUser* AVar);
	void __fastcall SaveEditorsInVar(Wsclasses::TTaskAssignedUser* AVar);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall UpdateListItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TTaskAssignedUser* AVar);
	void __fastcall VarsToInterface(void);
	void __fastcall ClearEditors(void);
	void __fastcall FillAssignedUsers(void);
	System::UnicodeString __fastcall GetAssignedUserID(void);
	void __fastcall Localize(void);
	Wsclasses::TTaskAssignedUser* __fastcall TaskAssignedUserFromItem(Vcl::Comctrls::TListItem* AItem);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TfrAssignedUserFrame(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfrAssignedUserFrame(void);
	void __fastcall LoadTaskInEditors(Wsclasses::TTaskDefinition* ATask, Wsclasses::TCustomWorkflowDiagram* ADiagram);
	void __fastcall SaveEditorsInTask(Wsclasses::TTaskDefinition* ATask);
	void __fastcall ClearAll(void);
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrAssignedUserFrame(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fassigneduserframe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FASSIGNEDUSERFRAME)
using namespace Fassigneduserframe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FassigneduserframeHPP
