// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fRunWorkflowEditor.pas' rev: 28.00 (Windows)

#ifndef FrunworkfloweditorHPP
#define FrunworkfloweditorHPP

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
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsBlocks.hpp>	// Pascal unit
#include <Vcl.Grids.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Frunworkfloweditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmRunWorkflowEditor;
class PASCALIMPLEMENTATION TfmRunWorkflowEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* tsGeneral;
	Vcl::Stdctrls::TLabel* lbWorkflowDefinition;
	Vcl::Stdctrls::TComboBox* cbWorkflowDefinition;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Grids::TStringGrid* grVariableMapping;
	Vcl::Stdctrls::TLabel* lbVariableMapping;
	Vcl::Stdctrls::TCheckBox* chWaitExecution;
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall cbWorkflowDefinitionChange(System::TObject* Sender);
	void __fastcall grVariableMappingSelectCell(System::TObject* Sender, int ACol, int ARow, bool &CanSelect);
	
private:
	Wsblocks::TWorkflowRunWorkflowBlock* FBlock;
	Vcl::Stdctrls::TComboBox* FComboVar;
	Wsclasses::TWorkflowDefinition* FWorkflowDefinition;
	System::Classes::TStrings* FList;
	void __fastcall BlockToInterface(void);
	void __fastcall ComboVarChange(System::TObject* Sender);
	void __fastcall ComboVarExit(System::TObject* Sender);
	void __fastcall InterfaceToBlock(void);
	void __fastcall LoadComboVar(void);
	void __fastcall LoadVariableMapping(System::Classes::TStrings* AList);
	void __fastcall Localize(void);
	void __fastcall SaveVariableMapping(System::Classes::TStrings* AList);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	bool __fastcall EditRunWorkflowBlock(Wsblocks::TWorkflowRunWorkflowBlock* ABlock);
	__fastcall virtual TfmRunWorkflowEditor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfmRunWorkflowEditor(void);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmRunWorkflowEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmRunWorkflowEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Frunworkfloweditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FRUNWORKFLOWEDITOR)
using namespace Frunworkfloweditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FrunworkfloweditorHPP
