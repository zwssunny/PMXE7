// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fLibItemEditor.pas' rev: 28.00 (Windows)

#ifndef FlibitemeditorHPP
#define FlibitemeditorHPP

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
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ExtDlgs.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Flibitemeditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmLibItemEditor;
class PASCALIMPLEMENTATION TfmLibItemEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TGroupBox* gbIcon;
	Vcl::Stdctrls::TButton* btLoadIcon;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Stdctrls::TGroupBox* gbData;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* edCaption;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TComboBox* cbCategory;
	Vcl::Extctrls::TImage* imIcon;
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Extdlgs::TOpenPictureDialog* OpenPictureDialog1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TComboBox* cbLibrary;
	Vcl::Extctrls::TImage* imDefault;
	void __fastcall btLoadIconClick(System::TObject* Sender);
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall cbLibraryChange(System::TObject* Sender);
	
private:
	Atdiagram::TDgrLibraryManager* FLibraryManager;
	bool __fastcall DrawIconFromBlock(Atdiagram::TDgrLibraryItem* AItem);
	void __fastcall LoadLibraries(void);
	void __fastcall ValidateData(void);
	Atdiagram::TDgrLibrary* __fastcall GetSelectedLibrary(void);
	void __fastcall SetSelectedLibrary(Atdiagram::TDgrLibrary* const Value);
	void __fastcall SetLibraryManager(Atdiagram::TDgrLibraryManager* const Value);
	__property Atdiagram::TDgrLibraryManager* LibraryManager = {read=FLibraryManager, write=SetLibraryManager};
	__property Atdiagram::TDgrLibrary* SelectedLibrary = {read=GetSelectedLibrary, write=SetSelectedLibrary};
	
public:
	void __fastcall FormToLibItem(Atdiagram::TDgrLibraryItem* AItem);
	void __fastcall LibItemToForm(Atdiagram::TDgrLibraryItem* AItem);
	__classmethod bool __fastcall EditLibraryItem(Atdiagram::TDgrLibraryItem* AItem, Atdiagram::TDgrLibraryManager* ALibraryManager, Atdiagram::TDgrLibrary* &ALibrary);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfmLibItemEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmLibItemEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmLibItemEditor(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmLibItemEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Flibitemeditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FLIBITEMEDITOR)
using namespace Flibitemeditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FlibitemeditorHPP
