// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'XPMenu.pas' rev: 27.00 (Windows)

#ifndef XpmenuHPP
#define XpmenuHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Winapi.CommCtrl.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Xpmenu
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TXPContainer : unsigned char { xccForm, xccFrame, xccToolbar, xccCoolbar, xccControlbar, xccPanel, xccScrollBox, xccGroupBox, xccTabSheet, xccPageScroller };

typedef System::Set<TXPContainer, TXPContainer::xccForm, TXPContainer::xccPageScroller> TXPContainers;

enum DECLSPEC_DENUM TXPControl : unsigned char { xcMainMenu, xcPopupMenu, xcToolbar, xcControlbar, xcCombo, xcEdit, xcMaskEdit, xcMemo, xcRichEdit, xcCheckBox, xcRadioButton, xcButton, xcBitBtn, xcSpeedButton, xcPanel, xcGroupBox };

typedef System::Set<TXPControl, TXPControl::xcMainMenu, TXPControl::xcGroupBox> TXPControls;

class DELPHICLASS TControlSubClass;
class DELPHICLASS TXPMenu;
class PASCALIMPLEMENTATION TControlSubClass : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Vcl::Controls::TControl* Control;
	bool FBuilding;
	bool FMouseInControl;
	bool FLButtonBressed;
	bool FBressed;
	bool FIsKeyDown;
	bool FIsFocused;
	System::Classes::TWndMethod orgWindowProc;
	TXPMenu* XPMenu;
	bool FCtl3D;
	Vcl::Forms::TFormBorderStyle FBorderStyle;
	unsigned FMsg;
	void __fastcall ControlSubClass(Winapi::Messages::TMessage &Message);
	void __fastcall PaintControlXP(void);
	void __fastcall PaintCombo(void);
	void __fastcall PaintDBLookupCombo(void);
	void __fastcall PaintEdit(void);
	void __fastcall PaintRichEdit(void);
	void __fastcall PaintCheckBox(void);
	void __fastcall PaintRadio(void);
	void __fastcall PaintButton(void);
	void __fastcall PaintBitButn(void);
	void __fastcall PaintUpDownButton(void);
	void __fastcall PaintSpeedButton(void);
	void __fastcall PaintPanel(void);
	void __fastcall PaintGroupBox(void);
public:
	/* TComponent.Create */ inline __fastcall virtual TControlSubClass(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TControlSubClass(void) { }
	
};


class PASCALIMPLEMENTATION TXPMenu : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FActive;
	Vcl::Forms::TScrollingWinControl* FForm;
	Vcl::Graphics::TFont* FFont;
	System::Uitypes::TColor FColor;
	System::Uitypes::TColor FIconBackColor;
	System::Uitypes::TColor FMenuBarColor;
	System::Uitypes::TColor FCheckedColor;
	System::Uitypes::TColor FSeparatorColor;
	System::Uitypes::TColor FSelectBorderColor;
	System::Uitypes::TColor FSelectColor;
	System::Uitypes::TColor FDisabledColor;
	System::Uitypes::TColor FSelectFontColor;
	int FIconWidth;
	bool FDrawSelect;
	bool FUseSystemColors;
	System::Uitypes::TColor FFColor;
	System::Uitypes::TColor FFIconBackColor;
	System::Uitypes::TColor FFSelectColor;
	System::Uitypes::TColor FFSelectBorderColor;
	System::Uitypes::TColor FFSelectFontColor;
	System::Uitypes::TColor FCheckedAreaColor;
	System::Uitypes::TColor FCheckedAreaSelectColor;
	System::Uitypes::TColor FFCheckedColor;
	System::Uitypes::TColor FFMenuBarColor;
	System::Uitypes::TColor FFDisabledColor;
	System::Uitypes::TColor FFSeparatorColor;
	System::Uitypes::TColor FMenuBorderColor;
	System::Uitypes::TColor FMenuShadowColor;
	bool Is16Bit;
	bool FOverrideOwnerDraw;
	bool FGradient;
	bool FFlatMenu;
	bool FAutoDetect;
	TXPContainers FXPContainers;
	TXPControls FXPControls;
	System::Byte FGrayLevel;
	System::Byte FDimLevel;
	bool FDrawMenuBar;
	bool FUseDimColor;
	int FDimParentColor;
	int FDimParentColorSelect;
	void __fastcall SetActive(const bool Value);
	void __fastcall SetAutoDetect(const bool Value);
	void __fastcall SetForm(Vcl::Forms::TScrollingWinControl* const Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetIconBackColor(const System::Uitypes::TColor Value);
	void __fastcall SetMenuBarColor(const System::Uitypes::TColor Value);
	void __fastcall SetCheckedColor(const System::Uitypes::TColor Value);
	void __fastcall SetDisabledColor(const System::Uitypes::TColor Value);
	void __fastcall SetSelectColor(const System::Uitypes::TColor Value);
	void __fastcall SetSelectBorderColor(const System::Uitypes::TColor Value);
	void __fastcall SetSeparatorColor(const System::Uitypes::TColor Value);
	void __fastcall SetSelectFontColor(const System::Uitypes::TColor Value);
	void __fastcall SetIconWidth(const int Value);
	void __fastcall SetDrawSelect(const bool Value);
	void __fastcall SetUseSystemColors(const bool Value);
	void __fastcall SetOverrideOwnerDraw(const bool Value);
	void __fastcall SetGradient(const bool Value);
	void __fastcall SetFlatMenu(const bool Value);
	void __fastcall SetXPContainers(const TXPContainers Value);
	void __fastcall SetXPControls(const TXPControls Value);
	void __fastcall SetDrawMenuBar(const bool Value);
	void __fastcall SetUseDimColor(const bool Value);
	
protected:
	void __fastcall InitItems(Vcl::Controls::TWinControl* wForm, bool Enable, bool Update);
	void __fastcall InitItem(System::Classes::TComponent* Comp, bool Enable, bool Update);
	void __fastcall DrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall MenueDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall ControlBarPaint(System::TObject* Sender, Vcl::Controls::TControl* Control, Vcl::Graphics::TCanvas* Canvas, System::Types::TRect &ARect, Vcl::Extctrls::TBandPaintOptions &Options);
	void __fastcall ActivateMenuItem(Vcl::Menus::TMenuItem* MenuItem);
	void __fastcall SetGlobalColor(Vcl::Graphics::TCanvas* ACanvas);
	void __fastcall DrawTopMenuItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, System::Uitypes::TColor BckColor, bool IsRightToLeft);
	void __fastcall DrawCheckedItem(Vcl::Menus::TMenuItem* FMenuItem, bool Selected, bool Enabled, bool HasImgLstBitmap, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &CheckedRect);
	void __fastcall DrawTheText(System::TObject* Sender, System::UnicodeString txt, System::UnicodeString ShortCuttext, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &TextRect, bool Selected, bool Enabled, bool Default, bool TopMenu, bool IsRightToLeft, Vcl::Graphics::TFont* &TxtFont, int TextFormat);
	void __fastcall DrawIcon(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, Vcl::Graphics::TBitmap* B, const System::Types::TRect &IconRect, bool Hot, bool Selected, bool Enabled, bool Checked, bool FTopMenu, bool IsRightToLeft);
	void __fastcall MeasureItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, int &Width, int &Height);
	System::Types::TPoint __fastcall GetImageExtent(Vcl::Menus::TMenuItem* MenuItem);
	System::Uitypes::TColor __fastcall TopMenuFontColor(Vcl::Graphics::TCanvas* ACanvas, System::Uitypes::TColor Color);
	void __fastcall DrawGradient(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool IsRightToLeft);
	void __fastcall DrawWindowBorder(HWND hWnd, bool IsRightToLeft);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TXPMenu(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXPMenu(void);
	virtual void __fastcall Loaded(void);
	void __fastcall InitComponent(System::Classes::TComponent* Comp);
	__property Vcl::Forms::TScrollingWinControl* Form = {read=FForm, write=SetForm};
	
__published:
	__property System::Byte DimLevel = {read=FDimLevel, write=FDimLevel, nodefault};
	__property System::Byte GrayLevel = {read=FGrayLevel, write=FGrayLevel, nodefault};
	__property Vcl::Graphics::TFont* Font = {read=FFont, write=SetFont};
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property bool DrawMenuBar = {read=FDrawMenuBar, write=SetDrawMenuBar, nodefault};
	__property System::Uitypes::TColor IconBackColor = {read=FIconBackColor, write=SetIconBackColor, nodefault};
	__property System::Uitypes::TColor MenuBarColor = {read=FMenuBarColor, write=SetMenuBarColor, nodefault};
	__property System::Uitypes::TColor SelectColor = {read=FSelectColor, write=SetSelectColor, nodefault};
	__property System::Uitypes::TColor SelectBorderColor = {read=FSelectBorderColor, write=SetSelectBorderColor, nodefault};
	__property System::Uitypes::TColor SelectFontColor = {read=FSelectFontColor, write=SetSelectFontColor, nodefault};
	__property System::Uitypes::TColor DisabledColor = {read=FDisabledColor, write=SetDisabledColor, nodefault};
	__property System::Uitypes::TColor SeparatorColor = {read=FSeparatorColor, write=SetSeparatorColor, nodefault};
	__property System::Uitypes::TColor CheckedColor = {read=FCheckedColor, write=SetCheckedColor, nodefault};
	__property int IconWidth = {read=FIconWidth, write=SetIconWidth, nodefault};
	__property bool DrawSelect = {read=FDrawSelect, write=SetDrawSelect, nodefault};
	__property bool UseSystemColors = {read=FUseSystemColors, write=SetUseSystemColors, nodefault};
	__property bool UseDimColor = {read=FUseDimColor, write=SetUseDimColor, nodefault};
	__property bool OverrideOwnerDraw = {read=FOverrideOwnerDraw, write=SetOverrideOwnerDraw, nodefault};
	__property bool Gradient = {read=FGradient, write=SetGradient, nodefault};
	__property bool FlatMenu = {read=FFlatMenu, write=SetFlatMenu, nodefault};
	__property bool AutoDetect = {read=FAutoDetect, write=SetAutoDetect, nodefault};
	__property TXPContainers XPContainers = {read=FXPContainers, write=SetXPContainers, default=1023};
	__property TXPControls XPControls = {read=FXPControls, write=SetXPControls, default=65535};
	__property bool Active = {read=FActive, write=SetActive, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
extern DELPHI_PACKAGE void __fastcall GetSystemMenuFont(Vcl::Graphics::TFont* Font);
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall GetShadeColor(Vcl::Graphics::TCanvas* ACanvas, System::Uitypes::TColor clr, int Value);
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall NewColor(Vcl::Graphics::TCanvas* ACanvas, System::Uitypes::TColor clr, int Value);
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall GrayColor(Vcl::Graphics::TCanvas* ACanvas, System::Uitypes::TColor clr, int Value);
extern DELPHI_PACKAGE void __fastcall GrayBitmap(Vcl::Graphics::TBitmap* ABitmap, int Value);
extern DELPHI_PACKAGE void __fastcall DimBitmap(Vcl::Graphics::TBitmap* ABitmap, int Value);
extern DELPHI_PACKAGE void __fastcall DrawArrow(Vcl::Graphics::TCanvas* ACanvas, int X, int Y);
extern DELPHI_PACKAGE void __fastcall DrawBitmapShadow(Vcl::Graphics::TBitmap* B, Vcl::Graphics::TCanvas* ACanvas, int X, int Y, System::Uitypes::TColor ShadowColor);
extern DELPHI_PACKAGE void __fastcall DrawCheckMark(Vcl::Graphics::TCanvas* ACanvas, int X, int Y);
}	/* namespace Xpmenu */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XPMENU)
using namespace Xpmenu;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// XpmenuHPP
