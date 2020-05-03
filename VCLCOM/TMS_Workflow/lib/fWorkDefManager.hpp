// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fWorkDefManager.pas' rev: 28.00 (Windows)

#ifndef FworkdefmanagerHPP
#define FworkdefmanagerHPP

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
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <wsControls.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fworkdefmanager
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmWorkDefManager;
class PASCALIMPLEMENTATION TfmWorkDefManager : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Wscontrols::TWorkDefListView* lvWorks;
	Vcl::Buttons::TSpeedButton* btAdd;
	Vcl::Buttons::TSpeedButton* btEdit;
	Vcl::Buttons::TSpeedButton* btDelete;
	Vcl::Buttons::TSpeedButton* btRefresh;
	Vcl::Buttons::TSpeedButton* btRunNew;
	Vcl::Menus::TPopupMenu* PopupMenu1;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acExport;
	Vcl::Actnlist::TAction* acImport;
	Vcl::Menus::TMenuItem* Export1;
	Vcl::Menus::TMenuItem* Import1;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	Vcl::Dialogs::TSaveDialog* SaveDialog1;
	void __fastcall btAddClick(System::TObject* Sender);
	void __fastcall btEditClick(System::TObject* Sender);
	void __fastcall btDeleteClick(System::TObject* Sender);
	void __fastcall btRefreshClick(System::TObject* Sender);
	void __fastcall btRunNewClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall lvWorksEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	void __fastcall lvWorksDblClick(System::TObject* Sender);
	void __fastcall ItemSelectedUpdate(System::TObject* Sender);
	void __fastcall acExportExecute(System::TObject* Sender);
	void __fastcall acImportExecute(System::TObject* Sender);
	
private:
	Wsmain::TWorkflowStudio* FWorkflowStudio;
	void __fastcall Localize(void);
	void __fastcall ImportFile(System::UnicodeString AFileName);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall TfmWorkDefManager(System::Classes::TComponent* AOwner, Wsmain::TWorkflowStudio* AWorkflowStudio);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmWorkDefManager(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmWorkDefManager(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmWorkDefManager(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fworkdefmanager */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FWORKDEFMANAGER)
using namespace Fworkdefmanager;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FworkdefmanagerHPP
