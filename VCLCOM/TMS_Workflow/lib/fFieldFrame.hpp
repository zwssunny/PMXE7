// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fFieldFrame.pas' rev: 28.00 (Windows)

#ifndef FfieldframeHPP
#define FfieldframeHPP

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

namespace Ffieldframe
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrFieldFrame;
class PASCALIMPLEMENTATION TfrFieldFrame : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Comctrls::TListView* lvVars;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* edCaption;
	Vcl::Stdctrls::TCheckBox* cbReadOnly;
	Vcl::Stdctrls::TCheckBox* cbRequired;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TComboBox* cbVariable;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* btAdd;
	Vcl::Stdctrls::TButton* btDelete;
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall lvVarsSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall lvVarsEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	void __fastcall edCaptionChange(System::TObject* Sender);
	
private:
	Wsclasses::TTaskFields* FFields;
	int FUpdatingControls;
	void __fastcall BeginUpdateControls(void);
	void __fastcall DeleteCurrentVar(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall LoadVarInEditors(Wsclasses::TTaskField* AVar);
	void __fastcall SaveEditorsInVar(Wsclasses::TTaskField* AVar);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall UpdateListItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TTaskField* AVar);
	void __fastcall VarsToInterface(void);
	void __fastcall ClearEditors(void);
	void __fastcall FillVariableCombo(Wsclasses::TCustomWorkflowDiagram* ADiagram);
	void __fastcall Localize(void);
	Wsclasses::TTaskField* __fastcall TaskFieldFromItem(Vcl::Comctrls::TListItem* AItem);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TfrFieldFrame(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfrFieldFrame(void);
	void __fastcall LoadTaskInEditors(Wsclasses::TTaskDefinition* ATask, Wsclasses::TCustomWorkflowDiagram* ADiagram);
	void __fastcall SaveEditorsInTask(Wsclasses::TTaskDefinition* ATask);
	void __fastcall ClearAll(void);
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrFieldFrame(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ffieldframe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FFIELDFRAME)
using namespace Ffieldframe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FfieldframeHPP
