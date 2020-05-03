// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fStatusFrame.pas' rev: 28.00 (Windows)

#ifndef FstatusframeHPP
#define FstatusframeHPP

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

namespace Fstatusframe
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrStatusFrame;
class PASCALIMPLEMENTATION TfrStatusFrame : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Comctrls::TListView* lvStatus;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TLabel* lbStatusName;
	Vcl::Stdctrls::TEdit* edStatusName;
	Vcl::Stdctrls::TCheckBox* chCompletion;
	Vcl::Stdctrls::TCheckBox* chHidden;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* btAdd;
	Vcl::Stdctrls::TButton* btDelete;
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall lvStatusSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall lvStatusEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	void __fastcall edStatusNameChange(System::TObject* Sender);
	void __fastcall lvStatusCustomDrawItem(Vcl::Comctrls::TCustomListView* Sender, Vcl::Comctrls::TListItem* Item, Vcl::Comctrls::TCustomDrawState State, bool &DefaultDraw);
	
private:
	Wsclasses::TTaskDefinition* FTaskDef;
	int FUpdatingControls;
	void __fastcall BeginUpdateControls(void);
	void __fastcall DeleteCurrentStatus(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall LoadStatusInEditors(int AStatus);
	void __fastcall SaveEditorsInStatus(int AStatus);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall UpdateListItem(Vcl::Comctrls::TListItem* AItem, int AStatus);
	void __fastcall StatusListToInterface(void);
	void __fastcall ClearEditors(void);
	void __fastcall Localize(void);
	int __fastcall StatusFromItem(Vcl::Comctrls::TListItem* AItem);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TfrStatusFrame(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfrStatusFrame(void);
	void __fastcall LoadTaskStatusList(Wsclasses::TTaskDefinition* ATaskDef);
	void __fastcall ClearAll(void);
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrStatusFrame(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fstatusframe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FSTATUSFRAME)
using namespace Fstatusframe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FstatusframeHPP
