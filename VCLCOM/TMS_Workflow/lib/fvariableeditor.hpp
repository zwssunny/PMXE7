// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fVariableEditor.pas' rev: 28.00 (Windows)

#ifndef FvariableeditorHPP
#define FvariableeditorHPP

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
#include <System.Variants.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fvariableeditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmVariableEditor;
class PASCALIMPLEMENTATION TfmVariableEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TListView* lvVars;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* edValue;
	Vcl::Stdctrls::TButton* btAdd;
	Vcl::Stdctrls::TButton* btDelete;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Stdctrls::TCheckBox* ckbInteraction;
	Vcl::Stdctrls::TMemo* Memo1;
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall lvVarsSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall lvVarsEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	
private:
	Wsclasses::TWorkflowVariables* FVars;
	int FUpdatingControls;
	void __fastcall VarsToInterface(void);
	void __fastcall UpdateListItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TWorkflowVariable* AVar);
	void __fastcall LoadVarInEditors(Wsclasses::TWorkflowVariable* AVar);
	void __fastcall ClearEditors(void);
	void __fastcall SaveEditorsInVar(Wsclasses::TWorkflowVariable* AVar);
	void __fastcall DeleteCurrentVar(void);
	void __fastcall BeginUpdateControls(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall Localize(void);
	Wsclasses::TWorkflowVariable* __fastcall WorkVarFromItem(Vcl::Comctrls::TListItem* AItem);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	bool __fastcall EditVariables(Wsclasses::TWorkflowVariables* AVars);
	__fastcall virtual TfmVariableEditor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfmVariableEditor(void);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmVariableEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmVariableEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fvariableeditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FVARIABLEEDITOR)
using namespace Fvariableeditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FvariableeditorHPP
