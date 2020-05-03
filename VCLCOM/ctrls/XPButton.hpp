// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'XPButton.pas' rev: 27.00 (Windows)

#ifndef XpbuttonHPP
#define XpbuttonHPP

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
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <Winapi.CommCtrl.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Xpbutton
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TButtonLayout : unsigned char { blGlyphLeft, blGlyphRight, blGlyphTop, blGlyphBottom };

class DELPHICLASS TZXPButton;
class PASCALIMPLEMENTATION TZXPButton : public Vcl::Controls::TGraphicControl
{
	typedef Vcl::Controls::TGraphicControl inherited;
	
private:
	int FGroupIndex;
	void *FGlyph;
	bool FDown;
	bool FAllowAllUp;
	TButtonLayout FLayout;
	int FSpacing;
	int FMargin;
	bool FMouseInControl;
	System::Uitypes::TColor FSelectedColor;
	System::Uitypes::TColor ASelectedColor;
	System::Uitypes::TColor FBorderColor;
	System::Uitypes::TColor FHotBorderColor;
	bool FDragging;
	bool FShowBorder;
	void __fastcall GlyphChanged(System::TObject* Sender);
	void __fastcall UpdateExclusive(void);
	Vcl::Graphics::TBitmap* __fastcall GetGlyph(void);
	void __fastcall SetGlyph(Vcl::Graphics::TBitmap* Value);
	Vcl::Buttons::TNumGlyphs __fastcall GetNumGlyphs(void);
	void __fastcall SetNumGlyphs(Vcl::Buttons::TNumGlyphs Value);
	void __fastcall SetDown(bool Value);
	void __fastcall SetAllowAllUp(bool Value);
	void __fastcall SetGroupIndex(int Value);
	void __fastcall SetLayout(TButtonLayout Value);
	void __fastcall SetSpacing(int Value);
	void __fastcall SetMargin(int Value);
	void __fastcall SetSelectedColor(System::Uitypes::TColor value);
	void __fastcall SetBorderColor(System::Uitypes::TColor value);
	void __fastcall SetHotBorderColor(System::Uitypes::TColor value);
	void __fastcall UpdateTracking(void);
	HIDESBASE MESSAGE void __fastcall WMLButtonDblClk(Winapi::Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall CMButtonPressed(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall CMDialogChar(Winapi::Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall CMTextChanged(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall CMSysColorChange(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	
protected:
	Vcl::Buttons::TButtonState FState;
	DYNAMIC HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	__property bool MouseInControl = {read=FMouseInControl, nodefault};
	
public:
	__fastcall virtual TZXPButton(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TZXPButton(void);
	DYNAMIC void __fastcall Click(void);
	
__published:
	__property bool AllowAllUp = {read=FAllowAllUp, write=SetAllowAllUp, default=0};
	__property Anchors = {default=3};
	__property BiDiMode;
	__property Constraints;
	__property Color = {default=-16777211};
	__property int GroupIndex = {read=FGroupIndex, write=SetGroupIndex, default=0};
	__property bool Down = {read=FDown, write=SetDown, default=0};
	__property Caption = {default=0};
	__property Enabled = {default=1};
	__property Font;
	__property Vcl::Graphics::TBitmap* Glyph = {read=GetGlyph, write=SetGlyph};
	__property TButtonLayout Layout = {read=FLayout, write=SetLayout, default=0};
	__property int Margin = {read=FMargin, write=SetMargin, default=-1};
	__property Vcl::Buttons::TNumGlyphs NumGlyphs = {read=GetNumGlyphs, write=SetNumGlyphs, default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property ParentBiDiMode = {default=1};
	__property PopupMenu;
	__property System::Uitypes::TColor SelectedColor = {read=FSelectedColor, write=SetSelectedColor, nodefault};
	__property System::Uitypes::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, nodefault};
	__property System::Uitypes::TColor HotBorderColor = {read=FHotBorderColor, write=SetHotBorderColor, nodefault};
	__property ShowHint;
	__property int Spacing = {read=FSpacing, write=SetSpacing, default=4};
	__property bool ShowBorder = {read=FShowBorder, write=FShowBorder, default=1};
	__property Visible = {default=1};
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
};


enum DECLSPEC_DENUM Xpbutton__2 : unsigned char { tbFocusRect, tbAllowTimer };

typedef System::Set<Xpbutton__2, Xpbutton__2::tbFocusRect, Xpbutton__2::tbAllowTimer> TTimeBtnState;

class DELPHICLASS TTimerXPButton;
class PASCALIMPLEMENTATION TTimerXPButton : public TZXPButton
{
	typedef TZXPButton inherited;
	
private:
	Vcl::Extctrls::TTimer* FRepeatTimer;
	TTimeBtnState FTimeBtnState;
	void __fastcall TimerExpired(System::TObject* Sender);
	
protected:
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	
public:
	__fastcall virtual ~TTimerXPButton(void);
	__property TTimeBtnState TimeBtnState = {read=FTimeBtnState, write=FTimeBtnState, nodefault};
public:
	/* TZXPButton.Create */ inline __fastcall virtual TTimerXPButton(System::Classes::TComponent* AOwner) : TZXPButton(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 InitRepeatPause = System::Int8(0x1);
static const System::Int8 RepeatPause = System::Int8(0x1);
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Xpbutton */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XPBUTTON)
using namespace Xpbutton;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// XpbuttonHPP
