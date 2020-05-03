// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fDgrPrintDialog.pas' rev: 28.00 (Windows)

#ifndef FdgrprintdialogHPP
#define FdgrprintdialogHPP

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
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fdgrprintdialog
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfmDgrPrintDialog;
class PASCALIMPLEMENTATION TfmDgrPrintDialog : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TButton* btOk;
	Vcl::Stdctrls::TButton* btCancel;
	Vcl::Stdctrls::TGroupBox* Label12;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* lbType;
	Vcl::Stdctrls::TLabel* lbWhere;
	Vcl::Stdctrls::TComboBox* cbPrinters;
	Vcl::Stdctrls::TButton* btProperties;
	Vcl::Stdctrls::TGroupBox* Label1;
	Vcl::Stdctrls::TLabel* lbDescription;
	Vcl::Stdctrls::TRadioButton* rbAllPages;
	Vcl::Stdctrls::TRadioButton* rbPageNumbers;
	Vcl::Stdctrls::TEdit* edPageNumbers;
	Vcl::Stdctrls::TGroupBox* Label2;
	Vcl::Stdctrls::TLabel* lbCopies;
	Vcl::Extctrls::TImage* imgNoCollate;
	Vcl::Extctrls::TImage* imgCollate;
	Vcl::Stdctrls::TEdit* edCopies;
	Vcl::Stdctrls::TCheckBox* cbCollate;
	Vcl::Comctrls::TUpDown* UpDown1;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall btPropertiesClick(System::TObject* Sender);
	void __fastcall cbPrintersChange(System::TObject* Sender);
	void __fastcall edPageNumbersChange(System::TObject* Sender);
	void __fastcall rbPageNumbersClick(System::TObject* Sender);
	
private:
	int FOldIndex;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfmDgrPrintDialog(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmDgrPrintDialog(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfmDgrPrintDialog(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmDgrPrintDialog(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fdgrprintdialog */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FDGRPRINTDIALOG)
using namespace Fdgrprintdialog;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FdgrprintdialogHPP
