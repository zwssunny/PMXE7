// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fDgrLibraryManagerEditor.pas' rev: 28.00 (Windows)

#ifndef FdgrlibrarymanagereditorHPP
#define FdgrlibrarymanagereditorHPP

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
#include <Vcl.ToolWin.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fdgrlibrarymanagereditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDgrLibraryManagerEditor;
class PASCALIMPLEMENTATION TDgrLibraryManagerEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TToolBar* ToolBar1;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acRemoveLibrary;
	Vcl::Controls::TImageList* ilActions;
	Vcl::Actnlist::TAction* acNewLibrary;
	Vcl::Menus::TPopupMenu* PopupMenu1;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TComboBox* cbLibrary;
	Vcl::Extctrls::TPanel* pnLibrary;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Comctrls::TListView* lvObject;
	Vcl::Controls::TImageList* ilObjects;
	Vcl::Extctrls::TImage* imDefault;
	Vcl::Comctrls::TToolButton* btEditItem;
	Vcl::Comctrls::TToolButton* btDeleteItem;
	Vcl::Actnlist::TAction* acEditItem;
	Vcl::Actnlist::TAction* acDeleteItem;
	Vcl::Menus::TMenuItem* Editobject1;
	Vcl::Menus::TMenuItem* Deleteobject1;
	Vcl::Buttons::TSpeedButton* btNewLibrary;
	Vcl::Buttons::TSpeedButton* btRemoveLibrary;
	Vcl::Comctrls::TToolButton* btShowCategories;
	Vcl::Actnlist::TAction* acShowCategories;
	void __fastcall acRemoveLibraryUpdate(System::TObject* Sender);
	void __fastcall acNewLibraryExecute(System::TObject* Sender);
	void __fastcall acRemoveLibraryExecute(System::TObject* Sender);
	void __fastcall cbLibraryChange(System::TObject* Sender);
	void __fastcall acEditItemUpdate(System::TObject* Sender);
	void __fastcall acDeleteItemUpdate(System::TObject* Sender);
	void __fastcall acDeleteItemExecute(System::TObject* Sender);
	void __fastcall lvObjectDblClick(System::TObject* Sender);
	void __fastcall acEditItemExecute(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall lvObjectCompare(System::TObject* Sender, Vcl::Comctrls::TListItem* Item1, Vcl::Comctrls::TListItem* Item2, int Data, int &Compare);
	void __fastcall lvObjectColumnClick(System::TObject* Sender, Vcl::Comctrls::TListColumn* Column);
	void __fastcall acShowCategoriesExecute(System::TObject* Sender);
	void __fastcall lvObjectKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	
private:
	int FCategoryColumnWidth;
	Atdiagram::TDgrLibraryManager* FLibraryManager;
	bool FSortByCategory;
	Atdiagram::TatDiagram* FDiagram;
	Atdiagram::TDgrLibraryItem* __fastcall GetSelectedItem(void);
	Atdiagram::TDgrLibrary* __fastcall GetSelectedLibrary(void);
	void __fastcall LoadLibraries(void);
	void __fastcall LoadObjects(void);
	void __fastcall ReloadItems(void);
	void __fastcall SetLibraryManager(Atdiagram::TDgrLibraryManager* const Value);
	void __fastcall SetSelectedItem(Atdiagram::TDgrLibraryItem* const Value);
	void __fastcall SetSelectedLibrary(Atdiagram::TDgrLibrary* const Value);
	
public:
	void __fastcall Execute(void);
	virtual void __fastcall InitiateAction(void);
	__property Atdiagram::TDgrLibraryManager* LibraryManager = {read=FLibraryManager, write=SetLibraryManager};
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=FDiagram};
	__property Atdiagram::TDgrLibraryItem* SelectedItem = {read=GetSelectedItem, write=SetSelectedItem};
	__property Atdiagram::TDgrLibrary* SelectedLibrary = {read=GetSelectedLibrary, write=SetSelectedLibrary};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDgrLibraryManagerEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDgrLibraryManagerEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDgrLibraryManagerEditor(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrLibraryManagerEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fdgrlibrarymanagereditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FDGRLIBRARYMANAGEREDITOR)
using namespace Fdgrlibrarymanagereditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FdgrlibrarymanagereditorHPP
