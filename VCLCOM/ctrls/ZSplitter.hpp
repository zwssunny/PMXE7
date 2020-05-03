// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ZSplitter.pas' rev: 27.00 (Windows)

#ifndef ZsplitterHPP
#define ZsplitterHPP

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
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Zsplitter
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TrsButtonWidthType : unsigned char { btwPixels, btwPercentage };

enum DECLSPEC_DENUM TrsButtonStyle : unsigned char { bsNetscape, bsWindows };

enum DECLSPEC_DENUM TrsWindowsButton : unsigned char { wbMin, wbMax, wbClose };

typedef System::Set<TrsWindowsButton, TrsWindowsButton::wbMin, TrsWindowsButton::wbClose> TrsWindowsButtons;

class DELPHICLASS TZSplitter;
class PASCALIMPLEMENTATION TZSplitter : public Vcl::Extctrls::TSplitter
{
	typedef Vcl::Extctrls::TSplitter inherited;
	
private:
	bool FShowButton;
	TrsButtonWidthType FButtonWidthType;
	int FButtonWidth;
	System::Classes::TNotifyEvent FOnMaximize;
	System::Classes::TNotifyEvent FOnMinimize;
	System::Classes::TNotifyEvent FOnRestore;
	bool FMaximized;
	bool FMinimized;
	int FRestorePos;
	System::Types::TRect FLastKnownButtonRect;
	bool FIsHighlighted;
	bool FGotMouseDown;
	System::Uitypes::TColor FButtonColor;
	System::Uitypes::TColor FButtonHighlightColor;
	System::Uitypes::TColor FArrowColor;
	System::Uitypes::TColor FTextureColor1;
	System::Uitypes::TColor FTextureColor2;
	bool FAutoHighlightColor;
	bool FAllowDrag;
	TrsButtonStyle FButtonStyle;
	TrsWindowsButtons FWindowsButtons;
	System::Classes::TNotifyEvent FOnClose;
	System::Uitypes::TCursor FButtonCursor;
	void __fastcall SetShowButton(const bool Value);
	void __fastcall SetButtonWidthType(const TrsButtonWidthType Value);
	void __fastcall SetButtonWidth(const int Value);
	System::Types::TRect __fastcall GetButtonRect(void);
	void __fastcall SetMaximized(const bool Value);
	void __fastcall SetMinimized(const bool Value);
	Vcl::Controls::TAlign __fastcall GetAlign(void);
	HIDESBASE void __fastcall SetAlign(Vcl::Controls::TAlign Value);
	void __fastcall SetArrowColor(const System::Uitypes::TColor Value);
	void __fastcall SetButtonColor(const System::Uitypes::TColor Value);
	void __fastcall SetButtonHighlightColor(const System::Uitypes::TColor Value);
	void __fastcall SetButtonStyle(const TrsButtonStyle Value);
	void __fastcall SetTextureColor1(const System::Uitypes::TColor Value);
	void __fastcall SetTextureColor2(const System::Uitypes::TColor Value);
	void __fastcall SetAutoHighLightColor(const bool Value);
	void __fastcall SetAllowDrag(const bool Value);
	void __fastcall SetWindowsButtons(const TrsWindowsButtons Value);
	void __fastcall SetButtonCursor(const System::Uitypes::TCursor Value);
	System::UnicodeString __fastcall GetVersion(void);
	void __fastcall SetVersion(const System::UnicodeString Val);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TWMMouse &Msg);
	
protected:
	Vcl::Controls::TControl* FControl;
	System::Types::TPoint FDownPos;
	DYNAMIC void __fastcall LoadOtherProperties(System::Classes::TReader* Reader);
	DYNAMIC void __fastcall StoreOtherProperties(System::Classes::TWriter* Writer);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall Paint(void);
	virtual bool __fastcall DoCanResize(int &NewSize);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall PaintButton(bool Highlight);
	DYNAMIC int __fastcall DrawArrow(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &AvailableRect, int iOffset, int ArrowSize, System::Uitypes::TColor Color);
	DYNAMIC TrsWindowsButton __fastcall WindowButtonHitTest(int X, int Y);
	DYNAMIC bool __fastcall ButtonHitTest(int X, int Y);
	DYNAMIC void __fastcall DoMaximize(void);
	DYNAMIC void __fastcall DoMinimize(void);
	DYNAMIC void __fastcall DoRestore(void);
	DYNAMIC void __fastcall DoClose(void);
	HIDESBASEDYNAMIC void __fastcall FindControl(void);
	HIDESBASEDYNAMIC void __fastcall UpdateControlSize(int NewSize);
	System::Uitypes::TColor __fastcall GrabBarColor(void);
	int __fastcall VisibleWinButtons(void);
	
public:
	__fastcall virtual TZSplitter(System::Classes::TComponent* AOwner);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	__property System::Types::TRect ButtonRect = {read=GetButtonRect};
	__property int RestorePos = {read=FRestorePos, write=FRestorePos, nodefault};
	
__published:
	__property bool Maximized = {read=FMaximized, write=SetMaximized, nodefault};
	__property bool Minimized = {read=FMinimized, write=SetMinimized, nodefault};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion, stored=false};
	__property bool AllowDrag = {read=FAllowDrag, write=SetAllowDrag, default=1};
	__property System::Uitypes::TCursor ButtonCursor = {read=FButtonCursor, write=SetButtonCursor, nodefault};
	__property TrsButtonStyle ButtonStyle = {read=FButtonStyle, write=SetButtonStyle, default=0};
	__property TrsWindowsButtons WindowsButtons = {read=FWindowsButtons, write=SetWindowsButtons, default=7};
	__property TrsButtonWidthType ButtonWidthType = {read=FButtonWidthType, write=SetButtonWidthType, default=0};
	__property int ButtonWidth = {read=FButtonWidth, write=SetButtonWidth, default=100};
	__property bool ShowButton = {read=FShowButton, write=SetShowButton, default=1};
	__property System::Uitypes::TColor ButtonColor = {read=FButtonColor, write=SetButtonColor, default=-16777201};
	__property System::Uitypes::TColor ArrowColor = {read=FArrowColor, write=SetArrowColor, default=8388608};
	__property System::Uitypes::TColor ButtonHighlightColor = {read=FButtonHighlightColor, write=SetButtonHighlightColor, default=16764879};
	__property bool AutoHighlightColor = {read=FAutoHighlightColor, write=SetAutoHighLightColor, default=0};
	__property System::Uitypes::TColor TextureColor1 = {read=FTextureColor1, write=SetTextureColor1, default=16777215};
	__property System::Uitypes::TColor TextureColor2 = {read=FTextureColor2, write=SetTextureColor2, default=8388608};
	__property Vcl::Controls::TAlign Align = {read=GetAlign, write=SetAlign, nodefault};
	__property Width = {default=10};
	__property Beveled = {default=0};
	__property Enabled = {default=1};
	__property System::Classes::TNotifyEvent OnClose = {read=FOnClose, write=FOnClose};
	__property System::Classes::TNotifyEvent OnMaximize = {read=FOnMaximize, write=FOnMaximize};
	__property System::Classes::TNotifyEvent OnMinimize = {read=FOnMinimize, write=FOnMinimize};
	__property System::Classes::TNotifyEvent OnRestore = {read=FOnRestore, write=FOnRestore};
public:
	/* TSplitter.Destroy */ inline __fastcall virtual ~TZSplitter(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 MOVEMENT_TOLERANCE = System::Int8(0x5);
static const int DEF_BUTTON_HIGHLIGHT_COLOR = int(0xffcfcf);
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Zsplitter */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ZSPLITTER)
using namespace Zsplitter;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ZsplitterHPP
