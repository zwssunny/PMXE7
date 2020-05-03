// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fDgrPageSettings.pas' rev: 28.00 (Windows)

#ifndef FdgrpagesettingsHPP
#define FdgrpagesettingsHPP

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
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fdgrpagesettings
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmDgrPageSettings;
class PASCALIMPLEMENTATION TfmDgrPageSettings : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* tsPaper;
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Extctrls::TShape* Shape1;
	Vcl::Stdctrls::TComboBox* cbPaperSize;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* edWidth;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* edHeight;
	Vcl::Stdctrls::TLabel* lbUnit2;
	Vcl::Stdctrls::TLabel* lbUnit1;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Extctrls::TShape* Shape2;
	Vcl::Extctrls::TImage* imgLandscape;
	Vcl::Extctrls::TImage* imgPortrait;
	Vcl::Stdctrls::TRadioButton* rbPortrait;
	Vcl::Stdctrls::TRadioButton* rbLandscape;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Extctrls::TShape* Shape3;
	Vcl::Stdctrls::TLabel* lbMarginTop;
	Vcl::Stdctrls::TLabel* lbMarginLeft;
	Vcl::Stdctrls::TLabel* lbMarginBottom;
	Vcl::Stdctrls::TLabel* lbMarginRight;
	Vcl::Stdctrls::TLabel* lbUnit3;
	Vcl::Stdctrls::TLabel* lbUnit4;
	Vcl::Stdctrls::TLabel* lbUnit5;
	Vcl::Stdctrls::TLabel* lbUnit6;
	Vcl::Stdctrls::TEdit* edMarginTop;
	Vcl::Stdctrls::TEdit* edMarginLeft;
	Vcl::Stdctrls::TEdit* edMarginBottom;
	Vcl::Stdctrls::TEdit* edMarginRight;
	void __fastcall cbPaperSizeChange(System::TObject* Sender);
	void __fastcall rbPortraitClick(System::TObject* Sender);
	void __fastcall rbLandscapeClick(System::TObject* Sender);
	void __fastcall btOkClick(System::TObject* Sender);
	
private:
	Atdiagram::TatDiagram* FDiagram;
	System::UnicodeString __fastcall MMToDisplay(System::Extended AMM);
	System::Extended __fastcall DisplayToMM(System::UnicodeString AValue);
	void __fastcall DiagramToForm(void);
	void __fastcall FormToDiagram(void);
	void __fastcall LoadPaperSize(void);
	void __fastcall UpdateUnitLabels(void);
	
public:
	bool __fastcall EditPageSettings(Atdiagram::TatDiagram* ADiagram);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfmDgrPageSettings(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmDgrPageSettings(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmDgrPageSettings(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmDgrPageSettings(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fdgrpagesettings */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FDGRPAGESETTINGS)
using namespace Fdgrpagesettings;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FdgrpagesettingsHPP
