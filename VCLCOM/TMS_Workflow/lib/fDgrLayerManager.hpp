// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fDgrLayerManager.pas' rev: 28.00 (Windows)

#ifndef FdgrlayermanagerHPP
#define FdgrlayermanagerHPP

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
#include <Winapi.CommCtrl.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.ToolWin.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fdgrlayermanager
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDgrLayerManager;
class PASCALIMPLEMENTATION TDgrLayerManager : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TToolBar* ToolBar1;
	Vcl::Comctrls::TToolButton* btAdd;
	Vcl::Comctrls::TToolButton* btRemove;
	Vcl::Comctrls::TToolButton* ToolButton3;
	Vcl::Comctrls::TToolButton* btMoveUp;
	Vcl::Comctrls::TToolButton* btMoveDown;
	Vcl::Comctrls::TListView* lvLayers;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acRemove;
	Vcl::Actnlist::TAction* acMoveUp;
	Vcl::Actnlist::TAction* acMoveDown;
	Vcl::Controls::TImageList* ilActions;
	Vcl::Actnlist::TAction* acAdd;
	Vcl::Actnlist::TAction* acVisible;
	Vcl::Actnlist::TAction* acEditable;
	Vcl::Menus::TPopupMenu* PopupMenu1;
	Vcl::Menus::TMenuItem* Visible1;
	Vcl::Menus::TMenuItem* Editable1;
	Vcl::Controls::TImageList* ilVisible;
	Vcl::Controls::TImageList* ilEditable;
	Vcl::Menus::TMenuItem* N1;
	Vcl::Actnlist::TAction* acRename;
	Vcl::Menus::TMenuItem* Rename1;
	Vcl::Comctrls::TToolButton* btDeleteControls;
	Vcl::Actnlist::TAction* acDeleteControls;
	void __fastcall acAddExecute(System::TObject* Sender);
	void __fastcall lvLayersEdited(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, System::UnicodeString &S);
	void __fastcall acRemoveExecute(System::TObject* Sender);
	void __fastcall acVisibleExecute(System::TObject* Sender);
	void __fastcall acEditableExecute(System::TObject* Sender);
	void __fastcall acMoveUpExecute(System::TObject* Sender);
	void __fastcall acRenameExecute(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall lvLayersMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall acDeleteControlsExecute(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall lvLayersCustomDrawItem(Vcl::Comctrls::TCustomListView* Sender, Vcl::Comctrls::TListItem* Item, Vcl::Comctrls::TCustomDrawState State, bool &DefaultDraw);
	
private:
	Atdiagram::TatDiagram* FDiagram;
	System::Classes::TStringList* FLayerList;
	void __fastcall AddLayerToList(Atdiagram::TDiagramLayer* ALayer);
	bool __fastcall DiagramLayersChanged(void);
	Atdiagram::TDiagramLayer* __fastcall GetSelectedLayer(void);
	void __fastcall LoadLayers(void);
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	
public:
	void __fastcall Execute(void);
	virtual void __fastcall InitiateAction(void);
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
	__property Atdiagram::TDiagramLayer* SelectedLayer = {read=GetSelectedLayer};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDgrLayerManager(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDgrLayerManager(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDgrLayerManager(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrLayerManager(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fdgrlayermanager */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FDGRLAYERMANAGER)
using namespace Fdgrlayermanager;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FdgrlayermanagerHPP
