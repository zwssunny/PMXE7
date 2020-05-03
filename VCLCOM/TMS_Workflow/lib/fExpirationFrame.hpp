// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fExpirationFrame.pas' rev: 28.00 (Windows)

#ifndef FexpirationframeHPP
#define FexpirationframeHPP

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
#include <wsClasses.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fexpirationframe
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrExpirationFrame;
class PASCALIMPLEMENTATION TfrExpirationFrame : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Stdctrls::TRadioButton* rbExpNever;
	Vcl::Stdctrls::TRadioButton* rbExpTerm;
	Vcl::Stdctrls::TRadioButton* rbExpDate;
	Vcl::Stdctrls::TRadioButton* rbExpCustom;
	Vcl::Stdctrls::TEdit* edTerm;
	Vcl::Stdctrls::TComboBox* cbTermType;
	Vcl::Comctrls::TDateTimePicker* edDate;
	Vcl::Comctrls::TDateTimePicker* edTime;
	Vcl::Stdctrls::TEdit* edExpression;
	Vcl::Stdctrls::TLabel* lbStatus;
	Vcl::Stdctrls::TComboBox* cbStatus;
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall rbExpCustomClick(System::TObject* Sender);
	void __fastcall edTermChange(System::TObject* Sender);
	
private:
	bool FUpdatingControls;
	System::Classes::TNotifyEvent FOnPropertyChanged;
	void __fastcall BeginUpdateControls(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall Localize(void);
	System::UnicodeString __fastcall GetDateTimeExpression(void);
	void __fastcall SetDateTimeExpression(const System::UnicodeString Value);
	bool __fastcall GetExpTerm(System::UnicodeString AExp, double &ATerm, int &AType);
	bool __fastcall GetExpDateTime(System::UnicodeString AExp, System::TDateTime &ADate, System::TDateTime &ATime);
	System::UnicodeString __fastcall BuildExpression(void);
	
protected:
	virtual void __fastcall Loaded(void);
	__property System::UnicodeString DateTimeExpression = {read=GetDateTimeExpression, write=SetDateTimeExpression};
	
public:
	__fastcall virtual TfrExpirationFrame(System::Classes::TComponent* Owner);
	void __fastcall ClearEditors(void);
	void __fastcall LoadTaskInEditors(Wsclasses::TTaskDefinition* ATask);
	void __fastcall SaveEditorsInTask(Wsclasses::TTaskDefinition* ATask);
	__property System::Classes::TNotifyEvent OnPropertyChanged = {read=FOnPropertyChanged, write=FOnPropertyChanged};
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrExpirationFrame(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrExpirationFrame(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fexpirationframe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FEXPIRATIONFRAME)
using namespace Fexpirationframe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FexpirationframeHPP
