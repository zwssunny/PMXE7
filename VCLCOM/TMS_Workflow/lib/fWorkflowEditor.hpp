// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fWorkflowEditor.pas' rev: 28.00 (Windows)

#ifndef FworkfloweditorHPP
#define FworkfloweditorHPP

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
#include <Vcl.Menus.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <DiagramEditor.hpp>	// Pascal unit
#include <fDiagramEditor.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsBlocks.hpp>	// Pascal unit
#include <LiveFlowChart.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fworkfloweditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmDummyWorkflowEditor;
class PASCALIMPLEMENTATION TfmDummyWorkflowEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
private:
	Atdiagram::TCustomDiagramLine* FLastUnlinkedLine;
	Atdiagram::TDiagramControl* FLastUnlinkedBlock;
	void __fastcall EditorCreateDesigner(System::TObject* Sender);
	void __fastcall EditorShowDesigner(System::TObject* Sender);
	void __fastcall WorkDefEditorSaveDiagram(System::TObject* Sender);
	void __fastcall WorkDefEditorCreateDesigner(System::TObject* Sender);
	void __fastcall WorkInsEditorCreateDesigner(System::TObject* Sender);
	void __fastcall WorkInsEditorSaveDiagram(System::TObject* Sender);
	void __fastcall EditTransition(Atdiagram::TCustomDiagramLine* ALine);
	void __fastcall Localize(Fdiagrameditor::TfmDiagramEditor* F);
	void __fastcall DiagramDControlDblClick(System::TObject* Sender, Atdiagram::TDiagramControl* ADControl);
	void __fastcall DiagramLinkAdded(System::TObject* Sender, Atdiagram::TDiagramControl* ADControl, Atdiagram::TCustomDiagramLine* ALink, Atdiagram::TLinkPoint* ALinkPoint);
	void __fastcall DiagramLinkRemoved(System::TObject* Sender, Atdiagram::TDiagramControl* ADControl, Atdiagram::TCustomDiagramLine* ALink, Atdiagram::TLinkPoint* ALinkPoint);
	void __fastcall MenuCheckClick(System::TObject* Sender);
	void __fastcall MenuAttachmentsClick(System::TObject* Sender);
	void __fastcall MenuVariablesClick(System::TObject* Sender);
	Wsdiagram::TWorkflowDiagram* FDiagram;
	Diagrameditor::TDiagramEditor* FEditor;
	Wsclasses::TWorkflowDefinition* FWorkDef;
	Wsclasses::TWorkflowInstance* FWorkIns;
	Wsclasses::TCustomWorkflowStudio* FWorkflowStudio;
	void __fastcall EditWorkDef(Wsclasses::TWorkflowDefinition* AWorkDef);
	void __fastcall EditWorkIns(Wsclasses::TWorkflowInstance* AWorkIns);
	
public:
	__fastcall TfmDummyWorkflowEditor(System::Classes::TComponent* AOwner, Wsclasses::TCustomWorkflowStudio* AWorkflowStudio);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmDummyWorkflowEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmDummyWorkflowEditor(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmDummyWorkflowEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall EditWorkflowDefDiagram(Wsclasses::TWorkflowDefinition* AWorkDef);
extern DELPHI_PACKAGE void __fastcall EditWorkflowInsDiagram(Wsclasses::TWorkflowInstance* AWorkIns);
}	/* namespace Fworkfloweditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FWORKFLOWEDITOR)
using namespace Fworkfloweditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FworkfloweditorHPP
