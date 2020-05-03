// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fTaskInstanceView.pas' rev: 28.00 (Windows)

#ifndef FtaskinstanceviewHPP
#define FtaskinstanceviewHPP

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
#include <wsControls.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ftaskinstanceview
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TfrTaskInstanceView;
class PASCALIMPLEMENTATION TfrTaskInstanceView : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* lbSubject;
	Vcl::Stdctrls::TMemo* mmDescription;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TLabel* Label2;
	Wscontrols::TTaskStatusCombo* cbTaskStatus;
	Vcl::Stdctrls::TLabel* lbExpiration;
	
private:
	Wsclasses::TTaskInstance* FTask;
	System::TDateTime FExpirationDateTime;
	void __fastcall SetTask(Wsclasses::TTaskInstance* const Value);
	void __fastcall TaskToInterface(void);
	void __fastcall Localize(void);
	void __fastcall ShowTaskExpiration(void);
	void __fastcall SetExpirationDateTime(const System::TDateTime Value);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__property Wsclasses::TTaskInstance* Task = {read=FTask, write=SetTask};
	void __fastcall SaveEditorsInVar(void);
	__property System::TDateTime ExpirationDateTime = {read=FExpirationDateTime, write=SetExpirationDateTime};
public:
	/* TCustomFrame.Create */ inline __fastcall virtual TfrTaskInstanceView(System::Classes::TComponent* AOwner) : Vcl::Forms::TFrame(AOwner) { }
	
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrTaskInstanceView(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrTaskInstanceView(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ftaskinstanceview */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FTASKINSTANCEVIEW)
using namespace Ftaskinstanceview;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// FtaskinstanceviewHPP
