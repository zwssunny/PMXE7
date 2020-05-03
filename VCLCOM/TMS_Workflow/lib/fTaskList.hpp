// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fTaskList.pas' rev: 28.00 (Windows)

#ifndef FtasklistHPP
#define FtasklistHPP

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
#include <wsMain.hpp>	// Pascal unit
#include <Data.DB.hpp>	// Pascal unit
#include <Vcl.Grids.hpp>	// Pascal unit
#include <Vcl.DBGrids.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <wsControls.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <fTaskInstanceView.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsDB.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ftasklist
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmTaskList;
class PASCALIMPLEMENTATION TfmTaskList : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Wscontrols::TTaskListView* lvTasks;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TSplitter* Splitter2;
	Vcl::Extctrls::TSplitter* Splitter3;
	Vcl::Stdctrls::TButton* btSaveChanges;
	Vcl::Comctrls::TTabControl* TabControl1;
	Ftaskinstanceview::TfrTaskInstanceView* frTaskView;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acShowAllTasks;
	Vcl::Menus::TPopupMenu* PopupMenu1;
	Vcl::Actnlist::TAction* acShowOnlyOpen;
	Vcl::Menus::TMenuItem* miView;
	Vcl::Menus::TMenuItem* Showonlyopentasks2;
	Vcl::Menus::TMenuItem* Showalltasks2;
	Wsdiagram::TWorkflowDiagram* WorkflowDiagram1;
	Vcl::Extctrls::TTimer* Timer1;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall btSaveChangesClick(System::TObject* Sender);
	void __fastcall WorkflowDiagram1Click(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall lvTasksSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall acShowOnlyOpenExecute(System::TObject* Sender);
	void __fastcall acShowOnlyOpenUpdate(System::TObject* Sender);
	void __fastcall acShowAllTasksExecute(System::TObject* Sender);
	void __fastcall acShowAllTasksUpdate(System::TObject* Sender);
	void __fastcall lvTasksCustomDrawItem(Vcl::Comctrls::TCustomListView* Sender, Vcl::Comctrls::TListItem* Item, Vcl::Comctrls::TCustomDrawState State, bool &DefaultDraw);
	void __fastcall Timer1Timer(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	
private:
	Wsclasses::TWorkflowInstance* FWorkIns;
	System::UnicodeString FLastActivePageName;
	int FUpdatingTabs;
	Wscontrols::TTaskFieldPanel* FFieldPanel;
	Wscontrols::TTaskLogListView* FLogView;
	bool FFreeOnClose;
	Wsmain::TWorkflowStudio* FWorkflowStudio;
	Wsclasses::TWorkflowInstance* __fastcall GetWorkIns(void);
	void __fastcall AddAttachmentTab(Wsclasses::TWorkflowAttachment* AAttach, Wsclasses::TAttachmentPermissions APermissions);
	void __fastcall UpdateFieldsTab(void);
	void __fastcall UpdateActivePage(void);
	void __fastcall UpdateFixedTabs(void);
	int __fastcall FindTabByType(int AType);
	void __fastcall SaveChanges(void);
	void __fastcall UpdateWorkflowDiagram(void);
	void __fastcall UpdateAttachmentTabs(void);
	void __fastcall BeginUpdateTabs(void);
	void __fastcall EndUpdateTabs(void);
	void __fastcall Localize(void);
	void __fastcall UpdateLogTab(void);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall TfmTaskList(System::Classes::TComponent* AOwner, Wsmain::TWorkflowStudio* AWorkflowStudio);
	void __fastcall SetFilter(Wsclasses::TTaskFilterType FilterType, System::UnicodeString AFilter);
	void __fastcall LoadData(void);
	__property bool FreeOnClose = {read=FFreeOnClose, write=FFreeOnClose, nodefault};
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmTaskList(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmTaskList(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmTaskList(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ftasklist */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FTASKLIST)
using namespace Ftasklist;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FtasklistHPP
