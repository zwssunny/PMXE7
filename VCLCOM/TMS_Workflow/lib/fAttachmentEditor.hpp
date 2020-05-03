// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fAttachmentEditor.pas' rev: 28.00 (Windows)

#ifndef FattachmenteditorHPP
#define FattachmenteditorHPP

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
#include <wsClasses.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <wsControls.hpp>	// Pascal unit
#include <fAttachmentFrame.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fattachmenteditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmAttachmentEditor;
class PASCALIMPLEMENTATION TfmAttachmentEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* tsAttachments;
	Vcl::Comctrls::TListView* lvAttachs;
	Vcl::Stdctrls::TButton* btAdd;
	Vcl::Stdctrls::TButton* btDelete;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TButton* btOk;
	Fattachmentframe::TfrAttachmentFrame* frItems;
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall lvAttachsSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall lvAttachsEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	
private:
	Wsclasses::TAttachmentItems* FLastAttachs;
	Wsclasses::TWorkflowAttachments* FAttachs;
	int FUpdatingControls;
	void __fastcall ClearEditors(void);
	void __fastcall BeginUpdateControls(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall AttachsToInterface(void);
	void __fastcall DeleteCurrentAttach(void);
	void __fastcall LoadAttachInEditors(Wsclasses::TWorkflowAttachment* AAttach);
	void __fastcall UpdateListItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TWorkflowAttachment* AAttach);
	void __fastcall SaveAttachs(void);
	void __fastcall Localize(void);
	Wsclasses::TWorkflowAttachment* __fastcall AttachmentFromItem(Vcl::Comctrls::TListItem* AItem);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	bool __fastcall EditAttachments(Wsclasses::TWorkflowAttachments* AAttachs);
	__fastcall TfmAttachmentEditor(System::Classes::TComponent* AOwner, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
	__fastcall virtual ~TfmAttachmentEditor(void);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmAttachmentEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmAttachmentEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fattachmenteditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FATTACHMENTEDITOR)
using namespace Fattachmenteditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FattachmenteditorHPP
