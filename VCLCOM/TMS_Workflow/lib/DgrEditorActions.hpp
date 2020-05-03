// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrEditorActions.pas' rev: 28.00 (Windows)

#ifndef DgreditoractionsHPP
#define DgreditoractionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <DiagramActns.hpp>	// Pascal unit
#include <DiagramExtra.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <Vcl.ExtDlgs.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgreditoractions
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TdmDgrEditorActions;
class PASCALIMPLEMENTATION TdmDgrEditorActions : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
__published:
	Vcl::Actnlist::TActionList* ActionList1;
	Diagramactns::TDiagramCut* DiagramCut1;
	Diagramactns::TDiagramCopy* DiagramCopy1;
	Diagramactns::TDiagramPaste* DiagramPaste1;
	Diagramactns::TDiagramSelectAll* DiagramSelectAll1;
	Diagramactns::TDiagramDelete* DiagramDelete1;
	Diagramactns::TDiagramEditText* DiagramEditText1;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom1;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom2;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom3;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom4;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom5;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom6;
	Diagramactns::TDiagramSetZoom* DiagramSetZoom7;
	Diagramactns::TDiagramViewLeftRuler* DiagramViewLeftRuler1;
	Diagramactns::TDiagramViewTopRuler* DiagramViewTopRuler1;
	Diagramactns::TDiagramShapeColor* DiagramShapeColor1;
	Diagramactns::TDiagramLineColor* DiagramLineColor1;
	Diagramactns::TDiagramBlockPicture* DiagramBlockPicture1;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape1;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape2;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape3;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape4;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape5;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape6;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape7;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape8;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape9;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape10;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape11;
	Diagramactns::TDiagramArrowShape* DiagramArrowShape12;
	Diagramactns::TDiagramBringToFront* DiagramBringToFront1;
	Vcl::Actnlist::TAction* acHasSourceArrow;
	Vcl::Actnlist::TAction* acNewDiagram;
	Vcl::Actnlist::TAction* acOpenDiagram;
	Vcl::Actnlist::TAction* acSaveDiagram;
	Vcl::Actnlist::TAction* acPrintDiagram;
	Vcl::Actnlist::TAction* acPreviewDiagram;
	Diagramactns::TDiagramSendToBack* DiagramSendToBack1;
	Diagramactns::TDiagramControlFont* DiagramControlFont1;
	Diagramactns::TDiagramGrid* DiagramGrid1;
	Diagramactns::TDiagramGradientSetting* DiagramGradientSetting1;
	Diagramactns::TDiagramShadow* DiagramShadow1;
	Diagramactns::TDiagramUndoAction* DiagramUndoAction1;
	Diagramactns::TDiagramRedoAction* DiagramRedoAction1;
	Vcl::Actnlist::TAction* acAutomaticNodes;
	Vcl::Actnlist::TActionList* ActionList2;
	Diagramactns::TDiagramAlign* DiagramAlign1;
	Diagramactns::TDiagramAlign* DiagramAlign2;
	Diagramactns::TDiagramAlign* DiagramAlign3;
	Diagramactns::TDiagramAlign* DiagramAlign4;
	Diagramactns::TDiagramAlign* DiagramAlign5;
	Diagramactns::TDiagramAlign* DiagramAlign6;
	Diagramactns::TDiagramAlign* DiagramAlign7;
	Diagramactns::TDiagramAlign* DiagramAlign8;
	Diagramactns::TDiagramAlign* DiagramAlign9;
	Diagramactns::TDiagramAlign* DiagramAlign10;
	Diagramactns::TDiagramAlign* DiagramAlign11;
	Diagramactns::TDiagramAlign* DiagramAlign12;
	Diagramactns::TDiagramAlign* DiagramAlign14;
	Diagramactns::TDiagramAlign* DiagramAlign15;
	Diagramactns::TDiagramAlign* DiagramAlign16;
	Vcl::Dialogs::TSaveDialog* SaveDialog1;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	Vcl::Controls::TImageList* ImageList1;
	Vcl::Controls::TImageList* ImageList2;
	Vcl::Actnlist::TAction* acCopyAsImage;
	Vcl::Actnlist::TAction* acHasTargetArrow;
	Vcl::Actnlist::TAction* acGroup;
	Vcl::Actnlist::TAction* acUngroup;
	Vcl::Actnlist::TActionList* ActionList3;
	Vcl::Actnlist::TAction* acBold;
	Vcl::Actnlist::TAction* acItalic;
	Vcl::Actnlist::TAction* acUnderline;
	Vcl::Actnlist::TAction* acAlignLeft;
	Vcl::Actnlist::TAction* acAlignCenter;
	Vcl::Actnlist::TAction* acAlignRight;
	Vcl::Actnlist::TAction* acVertAlignTop;
	Vcl::Actnlist::TAction* acVertAlignMiddle;
	Vcl::Actnlist::TAction* acVertAlignBottom;
	Vcl::Controls::TImageList* ImageList3;
	Vcl::Actnlist::TAction* acPageSetup;
	Vcl::Actnlist::TAction* acAddLibrary;
	Vcl::Actnlist::TAction* acSaveDiagramAs;
	Vcl::Actnlist::TAction* acBackgroundLoad;
	Vcl::Actnlist::TAction* acBackgroundClear;
	Vcl::Extdlgs::TOpenPictureDialog* OpenPictureDialog1;
	void __fastcall acHasSourceArrowUpdate(System::TObject* Sender);
	void __fastcall acAutomaticNodesExecute(System::TObject* Sender);
	void __fastcall acAutomaticNodesUpdate(System::TObject* Sender);
	void __fastcall acHasSourceArrowExecute(System::TObject* Sender);
	void __fastcall acPrintDiagramExecute(System::TObject* Sender);
	void __fastcall acPreviewDiagramExecute(System::TObject* Sender);
	void __fastcall acSaveDiagramExecute(System::TObject* Sender);
	void __fastcall acOpenDiagramExecute(System::TObject* Sender);
	void __fastcall acNewDiagramExecute(System::TObject* Sender);
	void __fastcall acCopyAsImageExecute(System::TObject* Sender);
	void __fastcall acGroupExecute(System::TObject* Sender);
	void __fastcall acGroupUpdate(System::TObject* Sender);
	void __fastcall acUngroupExecute(System::TObject* Sender);
	void __fastcall acUngroupUpdate(System::TObject* Sender);
	void __fastcall acBoldUpdate(System::TObject* Sender);
	void __fastcall acBoldExecute(System::TObject* Sender);
	void __fastcall acItalicUpdate(System::TObject* Sender);
	void __fastcall acItalicExecute(System::TObject* Sender);
	void __fastcall acUnderlineUpdate(System::TObject* Sender);
	void __fastcall acUnderlineExecute(System::TObject* Sender);
	void __fastcall acAlignLeftUpdate(System::TObject* Sender);
	void __fastcall acAlignCenterUpdate(System::TObject* Sender);
	void __fastcall acAlignRightUpdate(System::TObject* Sender);
	void __fastcall acVertAlignTopUpdate(System::TObject* Sender);
	void __fastcall acVertAlignMiddleUpdate(System::TObject* Sender);
	void __fastcall acVertAlignBottomUpdate(System::TObject* Sender);
	void __fastcall acAlignLeftExecute(System::TObject* Sender);
	void __fastcall acAlignCenterExecute(System::TObject* Sender);
	void __fastcall acAlignRightExecute(System::TObject* Sender);
	void __fastcall acVertAlignTopExecute(System::TObject* Sender);
	void __fastcall acVertAlignMiddleExecute(System::TObject* Sender);
	void __fastcall acVertAlignBottomExecute(System::TObject* Sender);
	void __fastcall acPageSetupExecute(System::TObject* Sender);
	void __fastcall acAddLibraryExecute(System::TObject* Sender);
	void __fastcall acAddLibraryUpdate(System::TObject* Sender);
	void __fastcall acSaveDiagramUpdate(System::TObject* Sender);
	void __fastcall acSaveDiagramAsExecute(System::TObject* Sender);
	void __fastcall DataModuleCreate(System::TObject* Sender);
	void __fastcall acBackgroundLoadExecute(System::TObject* Sender);
	void __fastcall acBackgroundLoadUpdate(System::TObject* Sender);
	void __fastcall acBackgroundClearUpdate(System::TObject* Sender);
	void __fastcall acBackgroundClearExecute(System::TObject* Sender);
	
private:
	Atdiagram::TatDiagram* FDiagram;
	Diagramextra::TDiagramToolBar* FToolbar;
	Vcl::Comctrls::TTabControl* FTabControl;
	System::Classes::TNotifyEvent FOnModified;
	bool FModified;
	Vcl::Forms::TCloseEvent FOldFormClose;
	System::Classes::TNotifyEvent FOnSaveDiagram;
	Atdiagram::TDgrLibraryManager* FLibManager;
	System::UnicodeString FCurrentDiagramFileName;
	bool FNewDiagram;
	System::Classes::TNotifyEvent FOnFileNameChanged;
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	void __fastcall SetActionsDiagram(Vcl::Actnlist::TActionList* ActionList);
	void __fastcall DiagramModified(System::TObject* Sender);
	void __fastcall SetModified(bool Value);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall TabControlChange(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	Atdiagram::TTextCell* __fastcall FirstCellSelected(void);
	void __fastcall SwitchSelectedFontStyle(System::Uitypes::TFontStyle AStyle, bool AInclude);
	void __fastcall SetSelectedAlignment(System::Classes::TAlignment AAlign);
	void __fastcall SetSelectedVertAlign(Diagramutils::TVertAlign AAlign);
	void __fastcall SetCurrentDiagramFileName(const System::UnicodeString Value);
	
public:
	void __fastcall PrepareDiagram(void);
	void __fastcall PrepareForm(Vcl::Forms::TForm* AForm);
	void __fastcall PrepareCategoryTab(Vcl::Comctrls::TTabControl* ATabControl, Diagramextra::TDiagramToolBar* AToolbar);
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
	__property Atdiagram::TDgrLibraryManager* LibManager = {read=FLibManager, write=FLibManager};
	__property bool Modified = {read=FModified, nodefault};
	__property System::UnicodeString CurrentDiagramFileName = {read=FCurrentDiagramFileName, write=SetCurrentDiagramFileName};
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
	__property System::Classes::TNotifyEvent OnSaveDiagram = {read=FOnSaveDiagram, write=FOnSaveDiagram};
	__property System::Classes::TNotifyEvent OnFileNameChanged = {read=FOnFileNameChanged, write=FOnFileNameChanged};
public:
	/* TDataModule.Create */ inline __fastcall virtual TdmDgrEditorActions(System::Classes::TComponent* AOwner) : System::Classes::TDataModule(AOwner) { }
	/* TDataModule.CreateNew */ inline __fastcall virtual TdmDgrEditorActions(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	/* TDataModule.Destroy */ inline __fastcall virtual ~TdmDgrEditorActions(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dgreditoractions */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGREDITORACTIONS)
using namespace Dgreditoractions;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgreditoractionsHPP
