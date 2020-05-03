// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fAuditEditor.pas' rev: 28.00 (Windows)

#ifndef FauditeditorHPP
#define FauditeditorHPP

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

//-- user supplied -----------------------------------------------------------

namespace Fauditeditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmAuditEditor;
class PASCALIMPLEMENTATION TfmAuditEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* edCondition;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TButton* btOk;
	void __fastcall btOkClick(System::TObject* Sender);
	void __fastcall btCancelClick(System::TObject* Sender);
	void __fastcall edConditionKeyPress(System::TObject* Sender, System::WideChar &Key);
	
private:
	Wsblocks::TWorkflowAuditBlock* FBlock;
	void __fastcall BlockToInterface(void);
	void __fastcall InterfaceToBlock(void);
	void __fastcall Localize(void);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	bool __fastcall EditAuditBlock(Wsblocks::TWorkflowAuditBlock* ABlock);
	__fastcall virtual TfmAuditEditor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfmAuditEditor(void);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmAuditEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmAuditEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fauditeditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FAUDITEDITOR)
using namespace Fauditeditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FauditeditorHPP
