// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fDiagramEditor.pas' rev: 28.00 (Windows)

#ifndef FdiagrameditorHPP
#define FdiagrameditorHPP

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
#include <System.Variants.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <DiagramExtra.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <DgrEditorActions.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.ToolWin.hpp>	// Pascal unit
#include <Vcl.CategoryButtons.hpp>	// Pascal unit
#include <DgrButtons.hpp>	// Pascal unit
#include <Vcl.DockTabSet.hpp>	// Pascal unit
#include <Vcl.Tabs.hpp>	// Pascal unit
#include <DgrSelectors.hpp>	// Pascal unit
#include <DgrCombo.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <fDgrLayerManager.hpp>	// Pascal unit
#include <fDgrLibraryManagerEditor.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fdiagrameditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmDiagramEditor;
class PASCALIMPLEMENTATION TfmDiagramEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Menus::TMainMenu* MainMenu1;
	Vcl::Menus::TMenuItem* Edittext1;
	Vcl::Menus::TMenuItem* Edit1;
	Vcl::Menus::TMenuItem* File1;
	Vcl::Menus::TMenuItem* Opendiagram1;
	Vcl::Menus::TMenuItem* Savediagram1;
	Vcl::Menus::TMenuItem* Copyasimage1;
	Vcl::Menus::TMenuItem* Print1;
	Vcl::Menus::TMenuItem* Edit2;
	Vcl::Menus::TMenuItem* Cut1;
	Vcl::Menus::TMenuItem* Copy1;
	Vcl::Menus::TMenuItem* Paste1;
	Vcl::Menus::TMenuItem* Delete1;
	Vcl::Menus::TMenuItem* Selectall1;
	Vcl::Menus::TMenuItem* N3;
	Vcl::Menus::TMenuItem* N4;
	Vcl::Menus::TMenuItem* Newdiagram1;
	Vcl::Menus::TMenuItem* N1;
	Vcl::Comctrls::TStatusBar* StatusBar1;
	Vcl::Menus::TMenuItem* Preview1;
	Vcl::Menus::TMenuItem* View1;
	Vcl::Menus::TMenuItem* Leftruler1;
	Vcl::Menus::TMenuItem* Topruler1;
	Vcl::Menus::TMenuItem* N2;
	Vcl::Menus::TMenuItem* Zoom1;
	Vcl::Menus::TMenuItem* N1001;
	Vcl::Menus::TMenuItem* N5;
	Vcl::Menus::TMenuItem* N3001;
	Vcl::Menus::TMenuItem* N1501;
	Vcl::Menus::TMenuItem* N751;
	Vcl::Menus::TMenuItem* N501;
	Vcl::Menus::TMenuItem* N251;
	Vcl::Menus::TMenuItem* N101;
	Vcl::Menus::TPopupMenu* PopupMenu1;
	Vcl::Menus::TMenuItem* DiagramShapeColor11;
	Vcl::Menus::TMenuItem* DiagramLineColor11;
	Vcl::Menus::TMenuItem* Sourcearrow1;
	Vcl::Menus::TMenuItem* argetarrow1;
	Vcl::Menus::TMenuItem* None1;
	Vcl::Menus::TMenuItem* Solidarrow1;
	Vcl::Menus::TMenuItem* Linearrow1;
	Vcl::Menus::TMenuItem* Ellipse1;
	Vcl::Menus::TMenuItem* Rectangle1;
	Vcl::Menus::TMenuItem* Diamond1;
	Vcl::Menus::TMenuItem* None2;
	Vcl::Menus::TMenuItem* Solidarrow2;
	Vcl::Menus::TMenuItem* Linearrow2;
	Vcl::Menus::TMenuItem* Ellipse2;
	Vcl::Menus::TMenuItem* Rectangle2;
	Vcl::Menus::TMenuItem* Diamond2;
	Vcl::Menus::TMenuItem* DiagramBlockPicture11;
	Vcl::Menus::TMenuItem* Shapecolor1;
	Vcl::Menus::TMenuItem* Linecolor1;
	Vcl::Menus::TMenuItem* Picture1;
	Vcl::Menus::TMenuItem* Sourcearrow2;
	Vcl::Menus::TMenuItem* argetarrow2;
	Vcl::Menus::TMenuItem* None3;
	Vcl::Menus::TMenuItem* Solidarrow3;
	Vcl::Menus::TMenuItem* Linearrow3;
	Vcl::Menus::TMenuItem* Ellipse3;
	Vcl::Menus::TMenuItem* Rectangle3;
	Vcl::Menus::TMenuItem* Diamond3;
	Vcl::Menus::TMenuItem* None4;
	Vcl::Menus::TMenuItem* Solidarrow4;
	Vcl::Menus::TMenuItem* Linearrow4;
	Vcl::Menus::TMenuItem* Ellipse4;
	Vcl::Menus::TMenuItem* Rectangle4;
	Vcl::Menus::TMenuItem* Diamond4;
	Vcl::Menus::TMenuItem* N6;
	Vcl::Menus::TMenuItem* N7;
	Vcl::Menus::TMenuItem* N8;
	Vcl::Menus::TMenuItem* DiagramBringToFront11;
	Vcl::Menus::TMenuItem* DiagramSendToBack11;
	Vcl::Menus::TMenuItem* Font1;
	Vcl::Menus::TMenuItem* N9;
	Vcl::Menus::TMenuItem* Font2;
	Vcl::Menus::TMenuItem* Edittext2;
	Vcl::Menus::TMenuItem* Grid1;
	Vcl::Menus::TMenuItem* Gradient1;
	Vcl::Menus::TMenuItem* N10;
	Vcl::Menus::TMenuItem* Undo1;
	Vcl::Menus::TMenuItem* DiagramRedoAction11;
	Vcl::Menus::TMenuItem* N11;
	Vcl::Menus::TMenuItem* Automaticnodes1;
	Vcl::Extctrls::TControlBar* ControlBar1;
	Vcl::Comctrls::TToolBar* ToolBar1;
	Vcl::Comctrls::TToolButton* ToolButton1;
	Vcl::Comctrls::TToolButton* ToolButton2;
	Vcl::Comctrls::TToolButton* ToolButton3;
	Vcl::Comctrls::TToolButton* ToolButton4;
	Vcl::Comctrls::TToolButton* ToolButton9;
	Vcl::Comctrls::TToolButton* ToolButton5;
	Vcl::Comctrls::TToolButton* ToolButton6;
	Vcl::Comctrls::TToolButton* ToolButton7;
	Vcl::Comctrls::TToolButton* ToolButton8;
	Vcl::Comctrls::TToolButton* ToolButton19;
	Vcl::Comctrls::TToolButton* ToolButton13;
	Vcl::Comctrls::TToolButton* ToolButton14;
	Vcl::Comctrls::TToolButton* ToolButton15;
	Vcl::Comctrls::TToolButton* ToolButton16;
	Diagramextra::TDiagramToolBar* DiagramToolBar2;
	Vcl::Comctrls::TToolBar* ToolBar3;
	Vcl::Comctrls::TToolButton* ToolButton17;
	Vcl::Comctrls::TToolButton* ToolButton18;
	Vcl::Comctrls::TToolButton* ToolButton20;
	Vcl::Comctrls::TToolButton* ToolButton21;
	Vcl::Comctrls::TToolButton* ToolButton22;
	Vcl::Comctrls::TToolButton* ToolButton23;
	Vcl::Comctrls::TToolButton* ToolButton24;
	Vcl::Comctrls::TToolButton* ToolButton25;
	Vcl::Comctrls::TToolButton* ToolButton26;
	Vcl::Comctrls::TToolButton* ToolButton27;
	Vcl::Comctrls::TToolButton* ToolButton28;
	Vcl::Comctrls::TToolButton* ToolButton29;
	Vcl::Comctrls::TToolButton* ToolButton30;
	Vcl::Comctrls::TToolButton* ToolButton31;
	Vcl::Comctrls::TToolButton* ToolButton32;
	Vcl::Comctrls::TToolButton* ToolButton34;
	Vcl::Comctrls::TToolButton* ToolButton35;
	Vcl::Comctrls::TToolButton* ToolButton36;
	Vcl::Comctrls::TToolButton* ToolButton37;
	Vcl::Comctrls::TToolBar* ToolBar2;
	Dgrcombo::TDgrFontSelector* DgrFontSelector1;
	Dgrcombo::TDgrFontSizeSelector* DgrFontSizeSelector1;
	Vcl::Comctrls::TTabControl* TabControl1;
	Diagramextra::TDiagramToolBar* DiagramToolBar1;
	Vcl::Menus::TMenuItem* N12;
	Vcl::Menus::TMenuItem* Group1;
	Vcl::Menus::TMenuItem* Ungroup1;
	Vcl::Comctrls::TToolButton* ToolButton10;
	Vcl::Comctrls::TToolButton* ToolButton12;
	Vcl::Comctrls::TToolBar* ToolBar4;
	Dgrselectors::TDgrColorSelector* DgrColorSelector2;
	Dgrselectors::TDgrGradientDirectionSelector* DgrGradientDirectionSelector2;
	Dgrselectors::TDgrBrushStyleSelector* DgrBrushStyleSelector2;
	Dgrselectors::TDgrShadowSelector* DgrShadowSelector2;
	Dgrselectors::TDgrPenStyleSelector* DgrPenStyleSelector2;
	Dgrselectors::TDgrPenColorSelector* DgrPenColorSelector2;
	Dgrselectors::TDgrTransparencySelector* DgrTransparencySelector2;
	Dgrcombo::TDgrZoomSelector* DgrZoomSelector2;
	Dgrselectors::TDgrPenWidthSelector* DgrPenWidthSelector2;
	Dgrselectors::TDgrTextColorSelector* DgrTextColorSelector2;
	Vcl::Comctrls::TToolButton* ToolButton11;
	Vcl::Comctrls::TToolButton* ToolButton33;
	Vcl::Comctrls::TToolButton* ToolButton38;
	Vcl::Comctrls::TToolButton* ToolButton39;
	Vcl::Comctrls::TToolButton* ToolButton40;
	Vcl::Comctrls::TToolButton* ToolButton41;
	Vcl::Comctrls::TToolButton* ToolButton42;
	Vcl::Comctrls::TToolButton* ToolButton43;
	Vcl::Comctrls::TToolButton* ToolButton44;
	Vcl::Comctrls::TToolButton* ToolButton45;
	Vcl::Comctrls::TToolButton* ToolButton46;
	Vcl::Comctrls::TToolButton* ToolButton47;
	Vcl::Comctrls::TToolButton* ToolButton48;
	Vcl::Menus::TMenuItem* PageSetup1;
	Vcl::Menus::TMenuItem* N13;
	Vcl::Menus::TMenuItem* AddtoLibrary1;
	Vcl::Comctrls::TToolButton* ToolButton49;
	Dgrcombo::TDgrLayerSelector* DgrLayerSelector1;
	Vcl::Menus::TMenuItem* N14;
	Vcl::Menus::TMenuItem* Layermanager1;
	Vcl::Menus::TMenuItem* Librarymanager1;
	Vcl::Extctrls::TPanel* FLeftDockPanel;
	Vcl::Extctrls::TPanel* FRightDockPanel;
	Vcl::Extctrls::TSplitter* FLeftDockSplitter;
	Vcl::Extctrls::TSplitter* FRightDockSplitter;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acViewLayerManager;
	Vcl::Actnlist::TAction* acViewLibraryManager;
	Vcl::Menus::TMenuItem* Saveas1;
	Vcl::Actnlist::TAction* acViewDiagramObjects;
	Vcl::Menus::TMenuItem* Diagramobjects1;
	Vcl::Menus::TMenuItem* Background1;
	Vcl::Menus::TMenuItem* Loadpicture1;
	Vcl::Menus::TMenuItem* Clear1;
	Vcl::Menus::TMenuItem* miLayer;
	void __fastcall ControlBar1DockOver(System::TObject* Sender, Vcl::Controls::TDragDockObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept);
	void __fastcall DockPanelUnDock(System::TObject* Sender, Vcl::Controls::TControl* Client, Vcl::Controls::TWinControl* NewTarget, bool &Allow);
	void __fastcall DockPanelDockDrop(System::TObject* Sender, Vcl::Controls::TDragDockObject* Source, int X, int Y);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall acViewLayerManagerUpdate(System::TObject* Sender);
	void __fastcall acViewLibraryManagerUpdate(System::TObject* Sender);
	void __fastcall acViewLayerManagerExecute(System::TObject* Sender);
	void __fastcall acViewLibraryManagerExecute(System::TObject* Sender);
	void __fastcall DgrNotification(Atdiagram::TDgrNotificationInfo AInfo);
	void __fastcall acViewDiagramObjectsUpdate(System::TObject* Sender);
	void __fastcall acViewDiagramObjectsExecute(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall PopupMenu1Popup(System::TObject* Sender);
	
private:
	Atdiagram::TatDiagram* FDiagram;
	Dgreditoractions::TdmDgrEditorActions* FDesigner;
	System::Classes::TNotifyEvent FOnNotifyShow;
	System::UnicodeString FTitle;
	Fdgrlayermanager::TDgrLayerManager* FLayerManager;
	Atdiagram::TDgrLibraryManager* FLibManager;
	Fdgrlibrarymanagereditor::TDgrLibraryManagerEditor* FLibraryManagerEditor;
	bool FShowLayerManager;
	bool FShowLibraryManager;
	Vcl::Docktabset::TDockTabSet* FDockTabset;
	Vcl::Forms::TForm* FButtonsForm;
	Dgrbuttons::TDiagramButtons* FButtons;
	void __fastcall FDockTabsetUnDock(System::TObject* Sender, Vcl::Controls::TControl* Client, Vcl::Controls::TWinControl* NewTarget, bool &Allow);
	void __fastcall FDockTabsetDockDrop(System::TObject* Sender, Vcl::Controls::TDragDockObject* Source, int X, int Y);
	void __fastcall DiagramModified(System::TObject* Sender);
	void __fastcall DockFormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall DesignerFileNameChanged(System::TObject* Sender);
	bool __fastcall GetLayerManagerVisible(void);
	bool __fastcall GetLibraryManagerVisible(void);
	System::Classes::TNotifyEvent __fastcall GetOnSaveDiagram(void);
	void __fastcall SetLayerManagerVisible(const bool Value);
	void __fastcall SetLibraryManagerVisible(const bool Value);
	void __fastcall SetTitle(const System::UnicodeString Value);
	void __fastcall SetOnSaveDiagram(const System::Classes::TNotifyEvent Value);
	void __fastcall SetLibManager(Atdiagram::TDgrLibraryManager* const Value);
	void __fastcall ShowDockedForm(Vcl::Forms::TForm* AForm, bool AVisible, bool AFocus = true);
	void __fastcall UpdateDockPanel(Vcl::Extctrls::TPanel* APanel, Vcl::Controls::TControl* AIgnore = (Vcl::Controls::TControl*)(0x0));
	void __fastcall SetShowLayerManager(const bool Value);
	bool __fastcall GetShowLibraryManager(void);
	void __fastcall SetShowLibraryManager(const bool Value);
	void __fastcall PrepareLayerMenu(Vcl::Menus::TMenuItem* AParent);
	void __fastcall LayerMenuItemClick(System::TObject* Sender);
	__property bool LayerManagerVisible = {read=GetLayerManagerVisible, write=SetLayerManagerVisible, nodefault};
	__property bool LibraryManagerVisible = {read=GetLibraryManagerVisible, write=SetLibraryManagerVisible, nodefault};
	
public:
	__fastcall TfmDiagramEditor(System::Classes::TComponent* AOwner, Atdiagram::TatDiagramClass ADiagramClass);
	__fastcall TfmDiagramEditor(System::Classes::TComponent* AOwner, Atdiagram::TatDiagram* ADiagramInstance);
	__fastcall virtual TfmDiagramEditor(System::Classes::TComponent* AOwner);
	__property System::Classes::TNotifyEvent OnNotifyShow = {read=FOnNotifyShow, write=FOnNotifyShow};
	__property System::Classes::TNotifyEvent OnSaveDiagram = {read=GetOnSaveDiagram, write=SetOnSaveDiagram};
	__property System::UnicodeString Title = {read=FTitle, write=SetTitle};
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram};
	__property Dgreditoractions::TdmDgrEditorActions* Actions = {read=FDesigner};
	__property Atdiagram::TDgrLibraryManager* LibManager = {read=FLibManager, write=SetLibManager};
	__property bool ShowLayerManager = {read=FShowLayerManager, write=SetShowLayerManager, nodefault};
	__property bool ShowLibraryManager = {read=GetShowLibraryManager, write=SetShowLibraryManager, nodefault};
	__property Dgrbuttons::TDiagramButtons* DButtons = {read=FButtons};
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmDiagramEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmDiagramEditor(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmDiagramEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
private:
	void *__IDiagramSubscriber;	// Atdiagram::IDiagramSubscriber 
	
public:
	operator Atdiagram::IDiagramSubscriber*(void) { return (Atdiagram::IDiagramSubscriber*)&__IDiagramSubscriber; }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fdiagrameditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FDIAGRAMEDITOR)
using namespace Fdiagrameditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FdiagrameditorHPP
