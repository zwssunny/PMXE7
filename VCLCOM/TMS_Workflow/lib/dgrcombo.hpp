// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrCombo.pas' rev: 28.00 (Windows)

#ifndef DgrcomboHPP
#define DgrcomboHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <System.Math.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgrcombo
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TDgrFontType : unsigned char { aftBitmap, aftTrueType, aftPostScript, aftPrinter, aftFixedPitch, aftProportional };

typedef System::Set<TDgrFontType, TDgrFontType::aftBitmap, TDgrFontType::aftProportional> TDgrFontTypes;

class DELPHICLASS TWinCtrl;
class PASCALIMPLEMENTATION TWinCtrl : public Vcl::Controls::TWinControl
{
	typedef Vcl::Controls::TWinControl inherited;
	
public:
	/* TWinControl.Create */ inline __fastcall virtual TWinCtrl(System::Classes::TComponent* AOwner) : Vcl::Controls::TWinControl(AOwner) { }
	/* TWinControl.CreateParented */ inline __fastcall TWinCtrl(HWND ParentWindow) : Vcl::Controls::TWinControl(ParentWindow) { }
	/* TWinControl.Destroy */ inline __fastcall virtual ~TWinCtrl(void) { }
	
};


class DELPHICLASS TDropDownWindow;
class PASCALIMPLEMENTATION TDropDownWindow : public Vcl::Controls::THintWindow
{
	typedef Vcl::Controls::THintWindow inherited;
	
private:
	Vcl::Stdctrls::TListBox* FListControl;
	bool FHideOnDeActivate;
	MESSAGE void __fastcall WMNCButtonDown(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall WMActivate(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Winapi::Messages::TWMNCHitTest &Message);
	
protected:
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	__property bool HideOnDeActivate = {read=FHideOnDeActivate, write=FHideOnDeActivate, nodefault};
	
public:
	__fastcall virtual TDropDownWindow(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDropDownWindow(void);
	
__published:
	__property BorderWidth = {default=0};
	__property Vcl::Stdctrls::TListBox* ListControl = {read=FListControl, write=FListControl};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDropDownWindow(HWND ParentWindow) : Vcl::Controls::THintWindow(ParentWindow) { }
	
};


class DELPHICLASS TDgrComboBtn;
class DELPHICLASS TDgrCustomComboBox;
class PASCALIMPLEMENTATION TDgrComboBtn : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Classes::TNotifyEvent FOnChange;
	int FWidth;
	Vcl::Graphics::TBitmap* FGlyph;
	Vcl::Graphics::TBitmap* FGlyphDown;
	Vcl::Graphics::TBitmap* FGlyphHot;
	System::Uitypes::TColor FColorHot;
	System::Uitypes::TColor FColorTo;
	System::Uitypes::TColor FColorDownTo;
	System::Uitypes::TColor FColorDown;
	System::Uitypes::TColor FColorHotTo;
	System::Uitypes::TColor FColor;
	System::Uitypes::TColor FDownArrowColor;
	System::Uitypes::TColor FHotArrowColor;
	System::Uitypes::TColor FArrowColor;
	TDgrCustomComboBox* FCombo;
	bool FDownArrow;
	void __fastcall SetWidth(const int Value);
	void __fastcall Change(void);
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetColorTo(const System::Uitypes::TColor Value);
	void __fastcall SetColorDown(const System::Uitypes::TColor Value);
	void __fastcall SetColorDownTo(const System::Uitypes::TColor Value);
	void __fastcall SetGlyphDown(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetGlyph(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetColorHot(const System::Uitypes::TColor Value);
	void __fastcall SetColorHotTo(const System::Uitypes::TColor Value);
	void __fastcall SetGlyphHot(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetArrowColor(const System::Uitypes::TColor Value);
	void __fastcall SetDownArrowColor(const System::Uitypes::TColor Value);
	void __fastcall SetHotArrowColor(const System::Uitypes::TColor Value);
	
protected:
	__property System::Uitypes::TColor ArrowColor = {read=FArrowColor, write=SetArrowColor, nodefault};
	__property System::Uitypes::TColor HotArrowColor = {read=FHotArrowColor, write=SetHotArrowColor, nodefault};
	__property System::Uitypes::TColor DownArrowColor = {read=FDownArrowColor, write=SetDownArrowColor, nodefault};
	__property bool DownArrow = {read=FDownArrow, write=FDownArrow, nodefault};
	__property TDgrCustomComboBox* Combo = {read=FCombo, write=FCombo};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
public:
	__fastcall TDgrComboBtn(void);
	__fastcall virtual ~TDgrComboBtn(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property System::Uitypes::TColor ColorTo = {read=FColorTo, write=SetColorTo, nodefault};
	__property System::Uitypes::TColor ColorHot = {read=FColorHot, write=SetColorHot, nodefault};
	__property System::Uitypes::TColor ColorHotTo = {read=FColorHotTo, write=SetColorHotTo, nodefault};
	__property System::Uitypes::TColor ColorDown = {read=FColorDown, write=SetColorDown, nodefault};
	__property System::Uitypes::TColor ColorDownTo = {read=FColorDownTo, write=SetColorDownTo, nodefault};
	__property Vcl::Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property Vcl::Graphics::TBitmap* GlyphHot = {read=FGlyphHot, write=SetGlyphHot};
	__property Vcl::Graphics::TBitmap* GlyphDown = {read=FGlyphDown, write=SetGlyphDown};
	__property int Width = {read=FWidth, write=SetWidth, nodefault};
};


enum DECLSPEC_DENUM TDgrComboStyle : unsigned char { esOffice2003Blue, esOffice2003Silver, esOffice2003Olive, esOffice2003Classic, esOffice2007Luna, esOffice2007Obsidian, esWindowsXP, esWhidbey, esCustom, esOffice2007Silver };

enum DECLSPEC_DENUM TComboStyle : unsigned char { csDropDown, csDropDownList };

enum DECLSPEC_DENUM TSelectionGradient : unsigned char { sgVertical, sgHorizontal, sgVerticalInOut, sgHorizontalInOut };

class PASCALIMPLEMENTATION TDgrCustomComboBox : public Vcl::Stdctrls::TCustomEdit
{
	typedef Vcl::Stdctrls::TCustomEdit inherited;
	
private:
	bool FAutoFocus;
	bool FMouseInControl;
	System::Classes::TNotifyEvent FOnMouseEnter;
	bool FButtonDown;
	bool FDroppedDown;
	System::Classes::TNotifyEvent FOnMouseLeave;
	TDgrComboBtn* FButton;
	bool FFlat;
	System::Uitypes::TColor FBorderHotColor;
	System::Uitypes::TColor FBorderColor;
	bool FAutoThemeAdapt;
	TDgrComboStyle FAppearanceStyle;
	System::Uitypes::TCursor FOldCursor;
	TDropDownWindow* FDropDownList;
	Vcl::Stdctrls::TListBox* FDropDownListBox;
	System::Classes::TStringList* FItems;
	int FDropDownCount;
	System::Classes::TNotifyEvent FOnBeforeDropDown;
	int FItemIndex;
	System::Uitypes::TColor FSelectionColor;
	int FFontHeight;
	int FItemHeight;
	bool FLookUp;
	bool FChanged;
	bool FMatchCase;
	bool FWorkMode;
	System::UnicodeString FOldText;
	System::Uitypes::TColor FSelectionColorTo;
	TSelectionGradient FSelectionGradient;
	bool FDisplayRecentSelection;
	System::Classes::TStringList* FRecentSelection;
	TComboStyle FStyle;
	bool FAutoItemSize;
	System::Uitypes::TColor FSelectionTextColor;
	System::Classes::TNotifyEvent FOnSelect;
	System::Classes::TNotifyEvent FOnDropDown;
	System::Classes::TNotifyEvent FOnCloseUp;
	System::Uitypes::TColor FDropDownListColor;
	MESSAGE void __fastcall CNCtlColorEdit(Winapi::Messages::TWMCtlColor &Message);
	MESSAGE void __fastcall CNCtlColorStatic(Winapi::Messages::TWMCtlColor &Message);
	MESSAGE void __fastcall CMCancelMode(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Winapi::Messages::TWMSetFocus &Msg);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Winapi::Messages::TWMKillFocus &Msg);
	HIDESBASE MESSAGE void __fastcall WMChar(Winapi::Messages::TWMKey &Msg);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall WMPaint(Winapi::Messages::TWMPaint &Msg);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSize(Winapi::Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall WMEraseBkGnd(Winapi::Messages::TWMEraseBkgnd &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMEnter(Winapi::Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall CMExit(Winapi::Messages::TWMNoParams &Message);
	MESSAGE void __fastcall CMWantSpecialKey(Winapi::Messages::TWMKey &Msg);
	void __fastcall DrawButton(HDC DC)/* overload */;
	void __fastcall DrawButton(void)/* overload */;
	void __fastcall DrawBorders(HDC DC)/* overload */;
	void __fastcall DrawBorders(void)/* overload */;
	System::Types::TRect __fastcall GetButtonRect(void);
	int __fastcall GetMinHeight(void);
	int __fastcall GetListItemHeight(void);
	void __fastcall ResizeControl(void);
	void __fastcall ButtonOnChange(System::TObject* Sender);
	void __fastcall ButtonClick(void);
	void __fastcall ListBoxKeyPress(System::TObject* Sender, System::WideChar &Key);
	void __fastcall ListBoxMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ListBoxMouseMove(System::TObject* Sender, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ListBoxKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall ListBoxOnEnter(System::TObject* Sender);
	void __fastcall ListBoxChange(System::TObject* Sender);
	void __fastcall ShowDropDown(void);
	void __fastcall HideDropDown(void);
	void __fastcall LookUpText(void);
	void __fastcall ThemeAdapt(void);
	virtual int __fastcall GetVersionNr(void);
	void __fastcall SetButton(TDgrComboBtn* const Value);
	void __fastcall SetFlat(const bool Value);
	void __fastcall SetBorderColor(const System::Uitypes::TColor Value);
	void __fastcall SetBorderHotColor(const System::Uitypes::TColor Value);
	void __fastcall SetAppearanceStyle(const TDgrComboStyle Value);
	void __fastcall SetItems(System::Classes::TStringList* const Value);
	void __fastcall SetItemIndex(const int Value);
	void __fastcall SetSelectionColor(const System::Uitypes::TColor Value);
	void __fastcall SetFontHeight(const int Value);
	void __fastcall SetLookUp(const bool Value);
	int __fastcall GetItemIndex(void);
	void __fastcall SetSelectionColorTo(const System::Uitypes::TColor Value);
	void __fastcall SetSelectionGradient(const TSelectionGradient Value);
	void __fastcall SetDisplayRecentSelection(const bool Value);
	int __fastcall GetItemHeight(void);
	void __fastcall SetItemHeight(const int Value);
	void __fastcall SetStyle(const TComboStyle Value);
	void __fastcall SetAutoItemSize(const bool Value);
	void __fastcall SetTextEx(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTextEx(void);
	System::UnicodeString __fastcall GetVersion(void);
	void __fastcall SetVersion(const System::UnicodeString Value);
	bool __fastcall GetDropDown(void);
	void __fastcall SetDropDown(const bool Value);
	void __fastcall ItemsChanged(System::TObject* Sender);
	
protected:
	void __fastcall SetEditRect(void);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall DoEnter(void);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	DYNAMIC void __fastcall KeyUp(System::Word &Key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall First(void);
	void __fastcall Previous(void);
	void __fastcall Next(void);
	void __fastcall Last(void);
	void __fastcall PageJump(bool GoForward);
	virtual void __fastcall BeforeDropDown(void);
	virtual void __fastcall DoDropDown(void);
	virtual void __fastcall DoCloseUp(void);
	virtual void __fastcall DoSelect(void);
	virtual void __fastcall DropDownOnDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	virtual void __fastcall ValueChanged(void);
	virtual void __fastcall UpdateIndex(void);
	virtual void __fastcall PopulateListBox(void);
	__property bool Flat = {read=FFlat, write=SetFlat, nodefault};
	__property bool AutoItemSize = {read=FAutoItemSize, write=SetAutoItemSize, default=1};
	__property int ItemHeight = {read=GetItemHeight, write=SetItemHeight, nodefault};
	__property int FontHeight = {read=FFontHeight, write=SetFontHeight, nodefault};
	__property TComboStyle Style = {read=FStyle, write=SetStyle, default=0};
	
public:
	__fastcall virtual TDgrCustomComboBox(System::Classes::TComponent* aOwner);
	__fastcall virtual ~TDgrCustomComboBox(void);
	int __fastcall CharFromPos(const System::Types::TPoint &pt);
	DYNAMIC void __fastcall Change(void);
	__property System::Classes::TStringList* Items = {read=FItems, write=SetItems};
	__property int ItemIndex = {read=GetItemIndex, write=SetItemIndex, nodefault};
	__property System::Classes::TStringList* RecentSelection = {read=FRecentSelection};
	__property TDgrComboStyle AppearanceStyle = {read=FAppearanceStyle, write=SetAppearanceStyle, nodefault};
	__property bool DroppedDown = {read=GetDropDown, write=SetDropDown, nodefault};
	
__published:
	__property Anchors = {default=3};
	__property Color = {default=-16777211};
	__property Align = {default=0};
	__property bool AutoFocus = {read=FAutoFocus, write=FAutoFocus, default=0};
	__property bool AutoThemeAdapt = {read=FAutoThemeAdapt, write=FAutoThemeAdapt, default=0};
	__property TDgrComboBtn* Button = {read=FButton, write=SetButton};
	__property bool DisplayRecentSelection = {read=FDisplayRecentSelection, write=SetDisplayRecentSelection, default=1};
	__property int DropDownCount = {read=FDropDownCount, write=FDropDownCount, nodefault};
	__property System::Uitypes::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, nodefault};
	__property System::Uitypes::TColor BorderHotColor = {read=FBorderHotColor, write=SetBorderHotColor, nodefault};
	__property bool LookUp = {read=FLookUp, write=SetLookUp, default=1};
	__property System::Uitypes::TColor SelectionColor = {read=FSelectionColor, write=SetSelectionColor, nodefault};
	__property System::Uitypes::TColor SelectionColorTo = {read=FSelectionColorTo, write=SetSelectionColorTo, default=536870911};
	__property System::Uitypes::TColor SelectionTextColor = {read=FSelectionTextColor, write=FSelectionTextColor, default=-16777202};
	__property TSelectionGradient SelectionGradient = {read=FSelectionGradient, write=SetSelectionGradient, default=2};
	__property System::UnicodeString Text = {read=GetTextEx, write=SetTextEx};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
	__property System::Uitypes::TColor DropDownListColor = {read=FDropDownListColor, write=FDropDownListColor, nodefault};
	__property PopupMenu;
	__property OnExit;
	__property OnEnter;
	__property OnChange;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property System::Classes::TNotifyEvent OnDropDown = {read=FOnDropDown, write=FOnDropDown};
	__property System::Classes::TNotifyEvent OnCloseUp = {read=FOnCloseUp, write=FOnCloseUp};
	__property System::Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property System::Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property System::Classes::TNotifyEvent OnBeforeDropDown = {read=FOnBeforeDropDown, write=FOnBeforeDropDown};
	__property System::Classes::TNotifyEvent OnSelect = {read=FOnSelect, write=FOnSelect};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrCustomComboBox(HWND ParentWindow) : Vcl::Stdctrls::TCustomEdit(ParentWindow) { }
	
};


class DELPHICLASS TDgrOfficeComboBox;
class PASCALIMPLEMENTATION TDgrOfficeComboBox : public TDgrCustomComboBox
{
	typedef TDgrCustomComboBox inherited;
	
public:
	__fastcall virtual TDgrOfficeComboBox(System::Classes::TComponent* aOwner);
	
__published:
	__property Anchors = {default=3};
	__property Enabled = {default=1};
	__property Items;
	__property ItemIndex;
	__property ItemHeight;
	__property Text;
	__property Font;
	__property Style = {default=0};
	__property Color = {default=-16777211};
	__property BiDiMode;
	__property Constraints;
	__property ParentBiDiMode = {default=1};
	__property ImeMode = {default=3};
	__property ImeName = {default=0};
	__property ParentColor = {default=0};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property OnClick;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnStartDrag;
	__property OnEndDock;
	__property OnStartDock;
public:
	/* TDgrCustomComboBox.Destroy */ inline __fastcall virtual ~TDgrOfficeComboBox(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrOfficeComboBox(HWND ParentWindow) : TDgrCustomComboBox(ParentWindow) { }
	
};


class DELPHICLASS TDgrBaseComboBox;
class PASCALIMPLEMENTATION TDgrBaseComboBox : public TDgrCustomComboBox
{
	typedef TDgrCustomComboBox inherited;
	
private:
	Atdiagram::TatDiagram* FDiagram;
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	
protected:
	virtual void __fastcall DiagramChanged(void);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation AOperation);
	
__published:
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
public:
	/* TDgrCustomComboBox.Create */ inline __fastcall virtual TDgrBaseComboBox(System::Classes::TComponent* aOwner) : TDgrCustomComboBox(aOwner) { }
	/* TDgrCustomComboBox.Destroy */ inline __fastcall virtual ~TDgrBaseComboBox(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrBaseComboBox(HWND ParentWindow) : TDgrCustomComboBox(ParentWindow) { }
	
};


class DELPHICLASS TDgrFontSelector;
class PASCALIMPLEMENTATION TDgrFontSelector : public TDgrBaseComboBox
{
	typedef TDgrBaseComboBox inherited;
	
private:
	Vcl::Graphics::TBitmap* FFontGlyphTT;
	Vcl::Graphics::TBitmap* FFontGlyphPS;
	Vcl::Graphics::TBitmap* FFontGlyphPRN;
	Vcl::Graphics::TBitmap* FFontGlyphBMP;
	bool FShowFontStyle;
	bool FShowFontGlyph;
	TDgrFontTypes FAllowedFontTypes;
	void __fastcall SetFontGlyphTT(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetFontGlyphPS(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetFontGlyphPRN(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetFontGlyphBMP(Vcl::Graphics::TBitmap* const Value);
	HIDESBASE MESSAGE void __fastcall CMTextChanged(Winapi::Messages::TMessage &Message);
	TDgrFontTypes __fastcall GetFontType(const System::UnicodeString Fontname);
	
protected:
	virtual void __fastcall DiagramChanged(void);
	virtual void __fastcall ApplySelectedFont(Atdiagram::TatDiagram* ADiagram, System::UnicodeString AFontName);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall BeforeDropDown(void);
	virtual void __fastcall DropDownOnDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	virtual void __fastcall ValueChanged(void);
	
public:
	__fastcall virtual TDgrFontSelector(System::Classes::TComponent* aOwner);
	virtual void __fastcall CreateWnd(void);
	__fastcall virtual ~TDgrFontSelector(void);
	void __fastcall LoadFontNames(void);
	
__published:
	__property TDgrFontTypes AllowedFontTypes = {read=FAllowedFontTypes, write=FAllowedFontTypes, nodefault};
	__property Vcl::Graphics::TBitmap* FontGlyphTT = {read=FFontGlyphTT, write=SetFontGlyphTT};
	__property Vcl::Graphics::TBitmap* FontGlyphPS = {read=FFontGlyphPS, write=SetFontGlyphPS};
	__property Vcl::Graphics::TBitmap* FontGlyphPRN = {read=FFontGlyphPRN, write=SetFontGlyphPRN};
	__property Vcl::Graphics::TBitmap* FontGlyphBMP = {read=FFontGlyphBMP, write=SetFontGlyphBMP};
	__property bool ShowFontStyle = {read=FShowFontStyle, write=FShowFontStyle, default=1};
	__property bool ShowFontGlyph = {read=FShowFontGlyph, write=FShowFontGlyph, default=1};
	__property FontHeight;
	__property Color = {default=-16777211};
	__property Enabled = {default=1};
	__property Font;
	__property Anchors = {default=3};
	__property BiDiMode;
	__property Constraints;
	__property ParentBiDiMode = {default=1};
	__property ImeMode = {default=3};
	__property ImeName = {default=0};
	__property ParentColor = {default=0};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property Style = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property OnClick;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnStartDrag;
	__property OnEndDock;
	__property OnStartDock;
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrFontSelector(HWND ParentWindow) : TDgrBaseComboBox(ParentWindow) { }
	
};


class DELPHICLASS TDgrZoomSelector;
class PASCALIMPLEMENTATION TDgrZoomSelector : public TDgrBaseComboBox
{
	typedef TDgrBaseComboBox inherited;
	
private:
	void __fastcall LoadZoomItems(void);
	int __fastcall GetZoom(void);
	
protected:
	virtual System::UnicodeString __fastcall GetZoomText(int AZoom);
	virtual void __fastcall DiagramChanged(void);
	virtual void __fastcall ApplySelectedZoom(Atdiagram::TatDiagram* ADiagram, int AZoom);
	virtual void __fastcall ValueChanged(void);
	virtual int __fastcall GetZoomFromText(System::UnicodeString AText);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall CreateWnd(void);
	
public:
	__fastcall virtual TDgrZoomSelector(System::Classes::TComponent* AOwner);
	virtual void __fastcall InitiateAction(void);
	__property int Zoom = {read=GetZoom, nodefault};
public:
	/* TDgrCustomComboBox.Destroy */ inline __fastcall virtual ~TDgrZoomSelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrZoomSelector(HWND ParentWindow) : TDgrBaseComboBox(ParentWindow) { }
	
};


class DELPHICLASS TDgrFontSizeSelector;
class PASCALIMPLEMENTATION TDgrFontSizeSelector : public TDgrBaseComboBox
{
	typedef TDgrBaseComboBox inherited;
	
private:
	void __fastcall LoadSizeItems(void);
	int __fastcall GetFontSize(void);
	
protected:
	virtual System::UnicodeString __fastcall GetSizeText(int ASize);
	virtual void __fastcall DiagramChanged(void);
	virtual void __fastcall ApplySelectedSize(Atdiagram::TatDiagram* ADiagram, int ASize);
	virtual void __fastcall ValueChanged(void);
	virtual int __fastcall GetSizeFromText(System::UnicodeString AText);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall CreateWnd(void);
	
public:
	__fastcall virtual TDgrFontSizeSelector(System::Classes::TComponent* AOwner);
	__property int FontSize = {read=GetFontSize, nodefault};
public:
	/* TDgrCustomComboBox.Destroy */ inline __fastcall virtual ~TDgrFontSizeSelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrFontSizeSelector(HWND ParentWindow) : TDgrBaseComboBox(ParentWindow) { }
	
};


class DELPHICLASS TDgrLayerSelector;
class PASCALIMPLEMENTATION TDgrLayerSelector : public TDgrBaseComboBox
{
	typedef TDgrBaseComboBox inherited;
	
private:
	bool FAutoChange;
	void __fastcall LoadLayerItems(void);
	System::UnicodeString __fastcall GetLayerName(void);
	void __fastcall SetLayerName(const System::UnicodeString Value);
	
protected:
	void __fastcall ApplySelectedLayer(Atdiagram::TatDiagram* ADiagram, System::UnicodeString ALayerName);
	virtual void __fastcall ValueChanged(void);
	
public:
	__fastcall virtual TDgrLayerSelector(System::Classes::TComponent* AOwner);
	virtual void __fastcall InitiateAction(void);
	__property System::UnicodeString LayerName = {read=GetLayerName, write=SetLayerName};
public:
	/* TDgrCustomComboBox.Destroy */ inline __fastcall virtual ~TDgrLayerSelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrLayerSelector(HWND ParentWindow) : TDgrBaseComboBox(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 LISTITEMHEIGHT = System::Int8(0xe);
static const System::Int8 MAJ_VER = System::Int8(0x2);
static const System::Int8 MIN_VER = System::Int8(0x0);
static const System::Int8 REL_VER = System::Int8(0x0);
static const System::Int8 BLD_VER = System::Int8(0x0);
extern DELPHI_PACKAGE void __fastcall DrawGradient(Vcl::Graphics::TCanvas* Canvas, System::Uitypes::TColor FromColor, System::Uitypes::TColor ToColor, int Steps, const System::Types::TRect &R, bool Direction);
}	/* namespace Dgrcombo */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGRCOMBO)
using namespace Dgrcombo;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgrcomboHPP
