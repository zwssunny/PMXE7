// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fAttachPermissions.pas' rev: 28.00 (Windows)

#ifndef FattachpermissionsHPP
#define FattachpermissionsHPP

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

//-- user supplied -----------------------------------------------------------

namespace Fattachpermissions
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrAttachPermissions;
class PASCALIMPLEMENTATION TfrAttachPermissions : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Stdctrls::TCheckBox* cbShowAttachments;
	Vcl::Stdctrls::TCheckBox* cbDelAttachment;
	Vcl::Stdctrls::TCheckBox* cbInsAttachment;
	Vcl::Stdctrls::TCheckBox* cbEditAttachment;
	void __fastcall PropertyChanged(System::TObject* Sender);
	void __fastcall cbShowAttachmentsClick(System::TObject* Sender);
	
private:
	bool FUpdatingControls;
	System::Classes::TNotifyEvent FOnPropertyChanged;
	void __fastcall BeginUpdateControls(void);
	void __fastcall EndUpdateControls(void);
	void __fastcall SetControlsEnabled(bool AEnabled);
	void __fastcall Localize(void);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	void __fastcall LoadTaskInEditors(Wsclasses::TTaskDefinition* ATask);
	void __fastcall SaveEditorsInTask(Wsclasses::TTaskDefinition* ATask);
	void __fastcall ClearEditors(void);
	__property System::Classes::TNotifyEvent OnPropertyChanged = {read=FOnPropertyChanged, write=FOnPropertyChanged};
public:
	/* TCustomFrame.Create */ inline __fastcall virtual TfrAttachPermissions(System::Classes::TComponent* AOwner) : Vcl::Forms::TFrame(AOwner) { }
	
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrAttachPermissions(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrAttachPermissions(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fattachpermissions */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FATTACHPERMISSIONS)
using namespace Fattachpermissions;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FattachpermissionsHPP
