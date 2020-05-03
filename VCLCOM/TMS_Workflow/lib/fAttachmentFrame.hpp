// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fAttachmentFrame.pas' rev: 28.00 (Windows)

#ifndef FattachmentframeHPP
#define FattachmentframeHPP

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
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <wsControls.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit
#include <System.Actions.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fattachmentframe
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrAttachmentFrame;
class PASCALIMPLEMENTATION TfrAttachmentFrame : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	Vcl::Menus::TPopupMenu* PopupMenu1;
	Vcl::Menus::TMenuItem* miInsert;
	Vcl::Menus::TMenuItem* miRemove;
	Vcl::Menus::TMenuItem* miOpen;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acInsert;
	Vcl::Actnlist::TAction* acRemove;
	Vcl::Actnlist::TAction* acOpen;
	Vcl::Actnlist::TAction* acSmallIcons;
	Vcl::Actnlist::TAction* acLargeIcons;
	Vcl::Actnlist::TAction* acReport;
	Vcl::Actnlist::TAction* acList;
	Vcl::Menus::TMenuItem* N1;
	Vcl::Menus::TMenuItem* Largeicons1;
	Vcl::Menus::TMenuItem* Smallicons1;
	Vcl::Menus::TMenuItem* List1;
	Vcl::Menus::TMenuItem* Report1;
	Vcl::Extctrls::TPanel* Panel1;
	Wscontrols::TAttachmentListView* lvItems;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Buttons::TSpeedButton* btAttach;
	Vcl::Buttons::TSpeedButton* btRemove;
	Vcl::Buttons::TSpeedButton* btOpen;
	void __fastcall acInsertExecute(System::TObject* Sender);
	void __fastcall acRemoveExecute(System::TObject* Sender);
	void __fastcall acOpenExecute(System::TObject* Sender);
	void __fastcall IconExecute(System::TObject* Sender);
	void __fastcall IconUpdate(System::TObject* Sender);
	void __fastcall acRemoveUpdate(System::TObject* Sender);
	void __fastcall acOpenUpdate(System::TObject* Sender);
	void __fastcall lvItemsKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall acInsertUpdate(System::TObject* Sender);
	
private:
	Wsclasses::TAttachmentPermissions FPermissions;
	void __fastcall SetPermissions(const Wsclasses::TAttachmentPermissions Value);
	void __fastcall Localize(void);
	Wsclasses::TCustomWorkflowStudio* __fastcall GetWorkflowStudio(void);
	void __fastcall SetWorkflowStudio(Wsclasses::TCustomWorkflowStudio* const Value);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TfrAttachmentFrame(System::Classes::TComponent* AOwner, Wsmain::TWorkflowStudio* AWorkflowStudio);
	__property Wsclasses::TAttachmentPermissions Permissions = {read=FPermissions, write=SetPermissions, nodefault};
	__property Wsclasses::TCustomWorkflowStudio* WorkflowStudio = {read=GetWorkflowStudio, write=SetWorkflowStudio};
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrAttachmentFrame(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrAttachmentFrame(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fattachmentframe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FATTACHMENTFRAME)
using namespace Fattachmentframe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FattachmentframeHPP
