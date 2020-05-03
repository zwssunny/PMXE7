// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrSelectors.pas' rev: 28.00 (Windows)

#ifndef DgrselectorsHPP
#define DgrselectorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <System.Math.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <DiagramShadow.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgrselectors
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TDgrSelectorstyle : unsigned char { ssButton, ssCombo };

enum DECLSPEC_DENUM TAdvAppearanceStyle : unsigned char { esOffice2003Blue, esOffice2003Silver, esOffice2003Olive, esOffice2003Classic, esWhidbey, esCustom, esXP };

enum DECLSPEC_DENUM TAdvButtonState : unsigned char { absUp, absDown, absDropDown };

enum DECLSPEC_DENUM TDgrGradientDirection : unsigned char { gdVertical, gdHorizontal };

enum DECLSPEC_DENUM TSelectorItemType : unsigned char { itAutoSizeButton, itFullWidthButton };

enum DECLSPEC_DENUM TColorSelectionStyle : unsigned char { csDiscrete, csColorCube, csSpectrum };

typedef System::Int8 TNoOfButtons;

class DELPHICLASS TDgrSelectorItem;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrSelectorItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::Types::TRect FItemRect;
	System::UnicodeString FCaption;
	bool FEnable;
	int FImageIndex;
	System::UnicodeString FValue;
	System::UnicodeString FHint;
	System::Classes::TAlignment FCaptionAlignment;
	TSelectorItemType FItemType;
	System::Uitypes::TColor FBackGroundColor;
	int FTag;
	void __fastcall SetCaption(const System::UnicodeString Value);
	void __fastcall SetEnable(const bool Value);
	void __fastcall SetHint(const System::UnicodeString Value);
	void __fastcall SetImageIndex(const int Value);
	void __fastcall SetValue(const System::UnicodeString Value);
	void __fastcall SetvCaptionAlignment(const System::Classes::TAlignment Value);
	void __fastcall SetItemType(const TSelectorItemType Value);
	void __fastcall SetBackGroundColor(const System::Uitypes::TColor Value);
	void __fastcall SetTag(const int Value);
	
protected:
	__property System::Types::TRect ItemRect = {read=FItemRect, write=FItemRect};
	__property bool Enable = {read=FEnable, write=SetEnable, nodefault};
	
public:
	__fastcall virtual TDgrSelectorItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TDgrSelectorItem(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TColor BackGroundColor = {read=FBackGroundColor, write=SetBackGroundColor, default=536870911};
	__property System::UnicodeString Caption = {read=FCaption, write=SetCaption};
	__property System::Classes::TAlignment CaptionAlignment = {read=FCaptionAlignment, write=SetvCaptionAlignment, nodefault};
	__property int ImageIndex = {read=FImageIndex, write=SetImageIndex, nodefault};
	__property System::UnicodeString Hint = {read=FHint, write=SetHint};
	__property System::UnicodeString Value = {read=FValue, write=SetValue};
	__property TSelectorItemType ItemType = {read=FItemType, write=SetItemType, default=0};
	__property int Tag = {read=FTag, write=SetTag, default=0};
};

#pragma pack(pop)

class DELPHICLASS TDgrSelectorItems;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrSelectorItems : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TDgrSelectorItem* operator[](int Index) { return Items[Index]; }
	
private:
	System::Classes::TPersistent* FOwner;
	HIDESBASE TDgrSelectorItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TDgrSelectorItem* const Value);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner(void);
	
public:
	__fastcall TDgrSelectorItems(System::Classes::TPersistent* AOwner);
	HIDESBASE TDgrSelectorItem* __fastcall Add(void);
	HIDESBASE TDgrSelectorItem* __fastcall Insert(int Index);
	TDgrSelectorItem* __fastcall IndexOfValue(System::UnicodeString AValue);
	__property TDgrSelectorItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDgrSelectorItems(void) { }
	
};

#pragma pack(pop)

typedef void __fastcall (__closure *TChangeSelectionEvent)(int OldItemIndex, int NewItemIndex);

typedef void __fastcall (__closure *THotToolEvent)(System::TObject* Sender, int HotItemIndex);

class DELPHICLASS TDgrCustomSelectorPanel;
class PASCALIMPLEMENTATION TDgrCustomSelectorPanel : public Vcl::Extctrls::TCustomPanel
{
	typedef Vcl::Extctrls::TCustomPanel inherited;
	
private:
	System::Classes::TComponent* FOwner;
	System::Uitypes::TColor FColorTo;
	TDgrGradientDirection FGradientDirection;
	System::Uitypes::TColor FWindowBorderColor;
	System::Classes::TNotifyEvent FOnShouldHide;
	void __fastcall SetColorTo(const System::Uitypes::TColor Value);
	void __fastcall SetGradientDirection(const TDgrGradientDirection Value);
	void __fastcall SetWindowBorderColor(const System::Uitypes::TColor Value);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	virtual int __fastcall GetVisibleHeight(void);
	__property System::Classes::TNotifyEvent OnShouldHide = {read=FOnShouldHide, write=FOnShouldHide};
	
public:
	__fastcall virtual TDgrCustomSelectorPanel(System::Classes::TComponent* AOwner);
	
__published:
	__property System::Uitypes::TColor ColorTo = {read=FColorTo, write=SetColorTo, default=536870911};
	__property System::Uitypes::TColor WindowBorderColor = {read=FWindowBorderColor, write=SetWindowBorderColor, default=8421504};
	__property TDgrGradientDirection GradientDirection = {read=FGradientDirection, write=SetGradientDirection, nodefault};
public:
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TDgrCustomSelectorPanel(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrCustomSelectorPanel(HWND ParentWindow) : Vcl::Extctrls::TCustomPanel(ParentWindow) { }
	
};


typedef void __fastcall (__closure *TItemDrawEvent)(System::TObject* Sender, int Index, const System::Types::TRect &R);

typedef void __fastcall (__closure *TSelectEvent)(System::TObject* Sender, int Index, TDgrSelectorItem* Item);

class DELPHICLASS TDgrSelectorPanel;
class PASCALIMPLEMENTATION TDgrSelectorPanel : public TDgrCustomSelectorPanel
{
	typedef TDgrCustomSelectorPanel inherited;
	
private:
	int FItemIndex;
	TDgrSelectorItems* FItems;
	System::Uitypes::TColor FColorHotTo;
	System::Uitypes::TColor FBorderColor;
	System::Uitypes::TColor FBorderDownColor;
	System::Uitypes::TColor FColorHot;
	System::Uitypes::TColor FBorderHotColor;
	System::Uitypes::TColor FColorDownTo;
	System::Uitypes::TColor FColorDown;
	Vcl::Imglist::TCustomImageList* FImages;
	int FHotItemIndex;
	int FDownItemIndex;
	int FButtonHeight;
	int FTopOffSet;
	int FLeftOffSet;
	TNoOfButtons FButtonsPerRow;
	TChangeSelectionEvent FOnChangeSelection;
	int FButtonMargin;
	bool FMouseDown;
	System::Classes::TNotifyEvent FOnSelect;
	System::Uitypes::TColor FBorderSelectedColor;
	System::Uitypes::TColor FColorSelected;
	System::Uitypes::TColor FColorSelectedTo;
	THotToolEvent FOnHotTool;
	int FMaxCaptionLength;
	TItemDrawEvent FOnDrawItem;
	int FMinButtonWidth;
	int FMinButtonHeight;
	bool FNoPrefix;
	bool FTwoColorImages;
	HIDESBASE MESSAGE void __fastcall WMChar(Winapi::Messages::TWMKey &Msg);
	MESSAGE void __fastcall CMWantSpecialKey(Winapi::Messages::TWMKey &Msg);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	void __fastcall SetBorderColor(const System::Uitypes::TColor Value);
	void __fastcall SetItemIndex(const int Value);
	void __fastcall SetItems(TDgrSelectorItems* const Value);
	void __fastcall SetImages(Vcl::Imglist::TCustomImageList* const Value);
	void __fastcall SetButtonsPerRow(const TNoOfButtons Value);
	void __fastcall SetButtonMargin(const int Value);
	void __fastcall SetMinButtonHeight(const int Value);
	void __fastcall SetMinButtonWidth(const int Value);
	void __fastcall SetTwoColorImages(const bool Value);
	
protected:
	void __fastcall DrawItem(int Index, bool RefreshItem = false);
	virtual void __fastcall Paint(void);
	void __fastcall SetItemsPosition(void);
	int __fastcall GetMaxWidth(void);
	int __fastcall TotalAutoSizeButtons(void);
	int __fastcall ItemAtPos(int X, int Y);
	void __fastcall SetPanelHeight(void);
	void __fastcall AutoSizeBtnSize(int &W, int &H);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	__property int MinButtonWidth = {read=FMinButtonWidth, write=SetMinButtonWidth, default=16};
	__property int MinButtonHeight = {read=FMinButtonHeight, write=SetMinButtonHeight, default=16};
	__property bool NoPrefix = {read=FNoPrefix, write=FNoPrefix, nodefault};
	__property bool TwoColorImages = {read=FTwoColorImages, write=SetTwoColorImages, nodefault};
	
public:
	__fastcall virtual TDgrSelectorPanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrSelectorPanel(void);
	__property TDgrSelectorItems* Items = {read=FItems, write=SetItems};
	__property int ItemIndex = {read=FItemIndex, write=SetItemIndex, nodefault};
	__property int HotItemIndex = {read=FHotItemIndex, nodefault};
	
__published:
	__property System::Uitypes::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=536870911};
	__property System::Uitypes::TColor BorderDownColor = {read=FBorderDownColor, write=FBorderDownColor, default=536870911};
	__property System::Uitypes::TColor BorderHotColor = {read=FBorderHotColor, write=FBorderHotColor, default=536870911};
	__property System::Uitypes::TColor BorderSelectedColor = {read=FBorderSelectedColor, write=FBorderSelectedColor, default=0};
	__property System::Uitypes::TColor ColorDown = {read=FColorDown, write=FColorDown, nodefault};
	__property System::Uitypes::TColor ColorDownTo = {read=FColorDownTo, write=FColorDownTo, default=536870911};
	__property System::Uitypes::TColor ColorHot = {read=FColorHot, write=FColorHot, nodefault};
	__property System::Uitypes::TColor ColorHotTo = {read=FColorHotTo, write=FColorHotTo, default=536870911};
	__property System::Uitypes::TColor ColorSelected = {read=FColorSelected, write=FColorSelected, nodefault};
	__property System::Uitypes::TColor ColorSelectedTo = {read=FColorSelectedTo, write=FColorSelectedTo, nodefault};
	__property TNoOfButtons ButtonsPerRow = {read=FButtonsPerRow, write=SetButtonsPerRow, default=1};
	__property Vcl::Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property int ButtonMargin = {read=FButtonMargin, write=SetButtonMargin, default=3};
	__property TChangeSelectionEvent OnChangeSelection = {read=FOnChangeSelection, write=FOnChangeSelection};
	__property System::Classes::TNotifyEvent OnSelect = {read=FOnSelect, write=FOnSelect};
	__property THotToolEvent OnHotTool = {read=FOnHotTool, write=FOnHotTool};
	__property TItemDrawEvent OnDrawItem = {read=FOnDrawItem, write=FOnDrawItem};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrSelectorPanel(HWND ParentWindow) : TDgrCustomSelectorPanel(ParentWindow) { }
	
};


struct DECLSPEC_DRECORD TColorCubeCell
{
public:
	System::Types::TPoint CenterPos;
	System::Uitypes::TColor Color;
};


class DELPHICLASS TDgrColorCubePanel;
class PASCALIMPLEMENTATION TDgrColorCubePanel : public TDgrCustomSelectorPanel
{
	typedef TDgrCustomSelectorPanel inherited;
	
private:
	System::StaticArray<TColorCubeCell, 127> FCubeCells;
	System::Types::TPoint FCubeSize;
	System::Uitypes::TColor FSelectedColor;
	int FSelectedIndex;
	int FHotIndex;
	System::Classes::TNotifyEvent FOnSelect;
	bool FShowRGBHint;
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	void __fastcall DrawColorCube(int Index);
	void __fastcall DrawAllColorCube(void);
	void __fastcall DrawSelectedBorder(void);
	void __fastcall DrawHotBorder(void);
	void __fastcall SetSelectedColor(const System::Uitypes::TColor Value);
	void __fastcall SetSelectedIndexAndColor(System::Uitypes::TColor clr, int index = 0xffffffff);
	void __fastcall SetShowRGBHint(const bool Value);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	bool __fastcall PtInCell(int Index, const System::Types::TPoint &P);
	int __fastcall IndexOfCellAt(int X, int Y);
	void __fastcall DrawHexagon(Vcl::Graphics::TCanvas* aCanvas, const System::Types::TPoint &P, int X, int Y);
	void __fastcall Initialize(void);
	void __fastcall SetItemsPosition(void);
	void __fastcall SetPanelSize(void);
	
public:
	__fastcall virtual TDgrColorCubePanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrColorCubePanel(void);
	
__published:
	__property System::Uitypes::TColor SelectedColor = {read=FSelectedColor, write=SetSelectedColor, nodefault};
	__property bool ShowRGBHint = {read=FShowRGBHint, write=SetShowRGBHint, nodefault};
	__property System::Classes::TNotifyEvent OnSelect = {read=FOnSelect, write=FOnSelect};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrColorCubePanel(HWND ParentWindow) : TDgrCustomSelectorPanel(ParentWindow) { }
	
};


class DELPHICLASS TDgrColorSpectrumPanel;
class PASCALIMPLEMENTATION TDgrColorSpectrumPanel : public TDgrCustomSelectorPanel
{
	typedef TDgrCustomSelectorPanel inherited;
	
private:
	Vcl::Extctrls::TImage* FSpectrumImage;
	System::Uitypes::TColor FHotColor;
	System::Uitypes::TColor FSelectedColor;
	System::Types::TRect FHotRect;
	System::Types::TRect FSelectedRect;
	System::Classes::TNotifyEvent FOnSelect;
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	void __fastcall SpectrumImageMouseMove(System::TObject* Sender, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall SpectrumImageMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall SpectrumImageMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall DrawHotRect(void);
	void __fastcall DrawSelectedRect(void);
	void __fastcall DrawFocusPoint(void);
	void __fastcall SetSelectedColor(const System::Uitypes::TColor Value);
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall SetItemsPosition(void);
	void __fastcall SetPanelSize(void);
	
public:
	__fastcall virtual TDgrColorSpectrumPanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrColorSpectrumPanel(void);
	
__published:
	__property System::Uitypes::TColor SelectedColor = {read=FSelectedColor, write=SetSelectedColor, nodefault};
	__property System::Classes::TNotifyEvent OnSelect = {read=FOnSelect, write=FOnSelect};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrColorSpectrumPanel(HWND ParentWindow) : TDgrCustomSelectorPanel(ParentWindow) { }
	
};


class DELPHICLASS TSelectorDropDownWindow;
class PASCALIMPLEMENTATION TSelectorDropDownWindow : public Vcl::Forms::TCustomForm
{
	typedef Vcl::Forms::TCustomForm inherited;
	
private:
	TDgrCustomSelectorPanel* FSelectorPanel;
	bool FHideOnDeActivate;
	bool FShowAbove;
	System::Classes::TComponent* FOwner;
	bool FShowFullBorder;
	Vcl::Extctrls::TTimer* FHideTimer;
	bool FShowLeft;
	HIDESBASE MESSAGE void __fastcall WMActivate(Winapi::Messages::TWMActivate &Message);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Winapi::Messages::TWMNCHitTest &Message);
	void __fastcall HideTimerOnTime(System::TObject* Sender);
	
protected:
	DYNAMIC void __fastcall Paint(void);
	HWND __fastcall GetParentWnd(void);
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	__property bool HideOnDeActivate = {read=FHideOnDeActivate, write=FHideOnDeActivate, nodefault};
	__property bool ShowAbove = {read=FShowAbove, write=FShowAbove, nodefault};
	__property bool ShowLeft = {read=FShowLeft, write=FShowLeft, default=0};
	__property bool ShowFullBorder = {read=FShowFullBorder, write=FShowFullBorder, nodefault};
	
public:
	__fastcall virtual TSelectorDropDownWindow(System::Classes::TComponent* AOwner);
	__fastcall virtual TSelectorDropDownWindow(System::Classes::TComponent* AOwner, int Dummy);
	__fastcall virtual ~TSelectorDropDownWindow(void);
	void __fastcall SetWindowSize(void);
	
__published:
	__property TDgrCustomSelectorPanel* SelectorPanel = {read=FSelectorPanel, write=FSelectorPanel};
public:
	/* TWinControl.CreateParented */ inline __fastcall TSelectorDropDownWindow(HWND ParentWindow) : Vcl::Forms::TCustomForm(ParentWindow) { }
	
};


typedef void __fastcall (__closure *TDrawToolEvent)(System::TObject* Sender, Vcl::Graphics::TCanvas* Canvas, int ItemIndex, const System::Types::TRect &R);

class DELPHICLASS TDgrCustomSelector;
class PASCALIMPLEMENTATION TDgrCustomSelector : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	TSelectorDropDownWindow* FDropDownWindow;
	TDgrSelectorPanel* FSelectorPanel;
	bool FMouseInControl;
	bool FMouseDown;
	int FDropDownBtnWidth;
	bool FDown;
	bool FShaded;
	bool FFlat;
	bool FAllowAllUp;
	bool FDropDownButton;
	bool FAutoThemeAdapt;
	TDgrSelectorstyle FStyle;
	Vcl::Graphics::TBitmap* FGlyphDown;
	Vcl::Graphics::TBitmap* FGlyphDisabled;
	Vcl::Graphics::TBitmap* FGlyphHot;
	Vcl::Graphics::TBitmap* FGlyph;
	Vcl::Graphics::TBitmap* FGlyphShade;
	System::Uitypes::TColor FBorderColor;
	System::Uitypes::TColor FColorDownTo;
	System::Uitypes::TColor FColorTo;
	System::Uitypes::TColor FColorHotTo;
	System::Uitypes::TColor FColorDown;
	System::Uitypes::TColor FBorderDownColor;
	System::Uitypes::TColor FColorHot;
	System::Uitypes::TColor FColorCheckedTo;
	System::Uitypes::TColor FColorChecked;
	System::Uitypes::TColor FBorderHotColor;
	Vcl::Imglist::TCustomImageList* FImages;
	System::Classes::TNotifyEvent FOnMouseEnter;
	System::Classes::TNotifyEvent FOnDropDown;
	System::Classes::TNotifyEvent FOnMouseLeave;
	int FGroupIndex;
	TAdvAppearanceStyle FAppearanceStyle;
	TAdvButtonState FState;
	System::Uitypes::TColor FColorDropDownTo;
	System::Uitypes::TColor FColorDropDown;
	System::Uitypes::TColor FBorderDropDownColor;
	int FDropDownCount;
	TDgrGradientDirection FGradientDirection;
	int FSelectedIndex;
	TDgrSelectorItems* FTools;
	TNoOfButtons FButtonsPerRow;
	System::Uitypes::TColor FColorSelectedTo;
	System::Uitypes::TColor FColorSelected;
	System::Uitypes::TColor FBorderSelectedColor;
	THotToolEvent FOnHotTool;
	System::Classes::TNotifyEvent FOnClick;
	TSelectEvent FOnSelect;
	System::Uitypes::TColor FColorSelectionHotTo;
	System::Uitypes::TColor FColorSelectionHot;
	System::Uitypes::TColor FColorSelectionDownTo;
	System::Uitypes::TColor FColorSelectionDown;
	TDrawToolEvent FOnDrawTool;
	int FDupSelectedIndex;
	Atdiagram::TatDiagram* FDiagram;
	bool FTwoColorImages;
	System::Uitypes::TColor FBackGroundImageColor;
	System::Uitypes::TColor FForeGroundImageColor;
	System::Uitypes::TColor FOldForeGroundImgColor;
	System::Uitypes::TColor FOldBkGroundImgColor;
	bool FStretchImageDraw;
	bool FIsThemed;
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMTextChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	void __fastcall GlyphChanged(System::TObject* Sender);
	void __fastcall OnDropDownWindowHide(System::TObject* Sender);
	void __fastcall OnDropDownPanelShouldHide(System::TObject* Sender);
	void __fastcall OnDropDownPanelSelect(System::TObject* Sender);
	void __fastcall OnDropDownPanelHotTool(System::TObject* Sender, int HotItemIndex);
	void __fastcall OnDropDownPanelDrawTool(System::TObject* Sender, int ItemIndex, const System::Types::TRect &R);
	void __fastcall PopupBtnDown(void);
	void __fastcall ButtonDown(void);
	void __fastcall DoDropDown(void);
	void __fastcall SetAllowAllUp(const bool Value);
	void __fastcall SetBorderColor(const System::Uitypes::TColor Value);
	void __fastcall SetColorChecked(const System::Uitypes::TColor Value);
	void __fastcall SetColorCheckedTo(const System::Uitypes::TColor Value);
	void __fastcall SetColorTo(const System::Uitypes::TColor Value);
	void __fastcall SetDown(const bool Value);
	void __fastcall SetDropDownButton(const bool Value);
	void __fastcall SetFlat(const bool Value);
	void __fastcall SetGlyph(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetGlyphDisabled(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetGlyphDown(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetGlyphHot(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetImages(Vcl::Imglist::TCustomImageList* const Value);
	void __fastcall SetShaded(const bool Value);
	void __fastcall SetStyle(const TDgrSelectorstyle Value);
	void __fastcall SetGroupIndex(const int Value);
	void __fastcall SetAppearanceStyle(const TAdvAppearanceStyle Value);
	void __fastcall SetColorDropDown(const System::Uitypes::TColor Value);
	void __fastcall SetColorDropDownTo(const System::Uitypes::TColor Value);
	void __fastcall SetDropDownCount(const int Value);
	void __fastcall SetGradientDirection(const TDgrGradientDirection Value);
	System::UnicodeString __fastcall GetCaption(void);
	void __fastcall SetCaption(const System::UnicodeString Value);
	void __fastcall SetSelectedIndex(const int Value);
	void __fastcall SetTools(TDgrSelectorItems* const Value);
	int __fastcall GetSelectedIndex(void);
	void __fastcall SetButtonsPerRow(const TNoOfButtons Value);
	System::UnicodeString __fastcall GetVersion(void);
	void __fastcall SetVersion(const System::UnicodeString Value);
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	void __fastcall SetTwoColorImages(const bool Value);
	void __fastcall SetForeGroundImageColor(const System::Uitypes::TColor Value);
	void __fastcall SetStretchImageDraw(const bool Value);
	
protected:
	virtual void __fastcall DoSelect(void);
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation AOperation);
	virtual void __fastcall OnToolSelect(void);
	int __fastcall DrawGlyph(Vcl::Graphics::TBitmap* aGlyph, const System::Types::TRect &aRect);
	virtual void __fastcall DrawGlyphAndCaption(Vcl::Graphics::TBitmap* aGlyph, const System::Types::TRect &R);
	void __fastcall DrawButton(void);
	void __fastcall DrawComboButton(void);
	void __fastcall SetSelectorPanelItems(void);
	virtual void __fastcall SetSelectorPanel(void);
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall Paint(void);
	__property bool MouseInControl = {read=FMouseInControl, nodefault};
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	void __fastcall ThemeAdapt(void);
	void __fastcall SetAutoThemeAdapt(const bool Value);
	virtual int __fastcall GetVersionNr(void);
	bool __fastcall DoVisualStyles(void);
	void __fastcall ChangeImagesColor(System::Uitypes::TColor ForeGColor, System::Uitypes::TColor BkGColor);
	__property bool TwoColorImages = {read=FTwoColorImages, write=SetTwoColorImages, nodefault};
	__property System::Uitypes::TColor OldForeGroundImgColor = {read=FOldForeGroundImgColor, nodefault};
	__property System::Uitypes::TColor OldBkGroundImgColor = {read=FOldBkGroundImgColor, nodefault};
	__property System::Uitypes::TColor ForeGroundImageColor = {read=FForeGroundImageColor, write=SetForeGroundImageColor, nodefault};
	__property System::Uitypes::TColor BackGroundImageColor = {read=FBackGroundImageColor, write=FBackGroundImageColor, nodefault};
	__property bool StretchImageDraw = {read=FStretchImageDraw, write=SetStretchImageDraw, default=1};
	__property bool AllowAllUp = {read=FAllowAllUp, write=SetAllowAllUp, default=0};
	__property bool AutoThemeAdapt = {read=FAutoThemeAdapt, write=SetAutoThemeAdapt, nodefault};
	__property TNoOfButtons ButtonsPerRow = {read=FButtonsPerRow, write=SetButtonsPerRow, default=1};
	__property System::Uitypes::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=536870911};
	__property System::Uitypes::TColor BorderDownColor = {read=FBorderDownColor, write=FBorderDownColor, default=536870911};
	__property System::Uitypes::TColor BorderHotColor = {read=FBorderHotColor, write=FBorderHotColor, default=536870911};
	__property System::Uitypes::TColor BorderDropDownColor = {read=FBorderDropDownColor, write=FBorderDropDownColor, default=8421504};
	__property System::Uitypes::TColor BorderSelectedColor = {read=FBorderSelectedColor, write=FBorderSelectedColor, default=0};
	__property System::UnicodeString Caption = {read=GetCaption, write=SetCaption};
	__property Color = {default=-16777211};
	__property System::Uitypes::TColor ColorTo = {read=FColorTo, write=SetColorTo, default=536870911};
	__property System::Uitypes::TColor ColorDown = {read=FColorDown, write=FColorDown, nodefault};
	__property System::Uitypes::TColor ColorDownTo = {read=FColorDownTo, write=FColorDownTo, default=536870911};
	__property System::Uitypes::TColor ColorHot = {read=FColorHot, write=FColorHot, nodefault};
	__property System::Uitypes::TColor ColorHotTo = {read=FColorHotTo, write=FColorHotTo, default=536870911};
	__property System::Uitypes::TColor ColorChecked = {read=FColorChecked, write=SetColorChecked, default=8421504};
	__property System::Uitypes::TColor ColorCheckedTo = {read=FColorCheckedTo, write=SetColorCheckedTo, default=536870911};
	__property System::Uitypes::TColor ColorDropDown = {read=FColorDropDown, write=SetColorDropDown, nodefault};
	__property System::Uitypes::TColor ColorDropDownTo = {read=FColorDropDownTo, write=SetColorDropDownTo, default=536870911};
	__property System::Uitypes::TColor ColorSelected = {read=FColorSelected, write=FColorSelected, nodefault};
	__property System::Uitypes::TColor ColorSelectedTo = {read=FColorSelectedTo, write=FColorSelectedTo, nodefault};
	__property System::Uitypes::TColor ColorSelectionHot = {read=FColorSelectionHot, write=FColorSelectionHot, nodefault};
	__property System::Uitypes::TColor ColorSelectionHotTo = {read=FColorSelectionHotTo, write=FColorSelectionHotTo, nodefault};
	__property System::Uitypes::TColor ColorSelectionDown = {read=FColorSelectionDown, write=FColorSelectionDown, nodefault};
	__property System::Uitypes::TColor ColorSelectionDownTo = {read=FColorSelectionDownTo, write=FColorSelectionDownTo, nodefault};
	__property bool Down = {read=FDown, write=SetDown, default=0};
	__property bool DropDownButton = {read=FDropDownButton, write=SetDropDownButton, default=0};
	__property int DropDownCount = {read=FDropDownCount, write=SetDropDownCount, nodefault};
	__property bool Flat = {read=FFlat, write=SetFlat, default=1};
	__property int GroupIndex = {read=FGroupIndex, write=SetGroupIndex, default=0};
	__property Vcl::Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property Vcl::Graphics::TBitmap* GlyphHot = {read=FGlyphHot, write=SetGlyphHot};
	__property Vcl::Graphics::TBitmap* GlyphDown = {read=FGlyphDown, write=SetGlyphDown};
	__property Vcl::Graphics::TBitmap* GlyphDisabled = {read=FGlyphDisabled, write=SetGlyphDisabled};
	__property TDgrGradientDirection GradientDirection = {read=FGradientDirection, write=SetGradientDirection, nodefault};
	__property Vcl::Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property bool Shaded = {read=FShaded, write=SetShaded, default=1};
	__property TDgrSelectorstyle Style = {read=FStyle, write=SetStyle, nodefault};
	__property TAdvButtonState State = {read=FState, write=FState, nodefault};
	__property TAdvAppearanceStyle AppearanceStyle = {read=FAppearanceStyle, write=SetAppearanceStyle, nodefault};
	__property TDgrSelectorItems* Tools = {read=FTools, write=SetTools};
	__property int SelectedIndex = {read=GetSelectedIndex, write=SetSelectedIndex, nodefault};
	__property System::Classes::TNotifyEvent OnMouseEnter = {read=FOnMouseEnter, write=FOnMouseEnter};
	__property System::Classes::TNotifyEvent OnMouseLeave = {read=FOnMouseLeave, write=FOnMouseLeave};
	__property System::Classes::TNotifyEvent OnDropDown = {read=FOnDropDown, write=FOnDropDown};
	__property TSelectEvent OnSelect = {read=FOnSelect, write=FOnSelect};
	__property THotToolEvent OnHotTool = {read=FOnHotTool, write=FOnHotTool};
	__property TDrawToolEvent OnDrawTool = {read=FOnDrawTool, write=FOnDrawTool};
	__property System::Classes::TNotifyEvent OnClick = {read=FOnClick, write=FOnClick};
	
public:
	__fastcall virtual TDgrCustomSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrCustomSelector(void);
	DYNAMIC void __fastcall Click(void);
	void __fastcall ShowDropDown(void);
	void __fastcall HideDropDown(void);
	
__published:
	__property Anchors = {default=3};
	__property Action;
	__property TabOrder = {default=-1};
	__property TabStop = {default=0};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
	__property Visible = {default=1};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrCustomSelector(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
};


class DELPHICLASS TDgrPenStyleSelector;
class PASCALIMPLEMENTATION TDgrPenStyleSelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	void __fastcall Initialize(void);
	Vcl::Graphics::TPenStyle __fastcall GetSelectedPenStyle(void);
	
protected:
	virtual void __fastcall SetSelectorPanel(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
public:
	__fastcall virtual TDgrPenStyleSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrPenStyleSelector(void);
	__property AppearanceStyle;
	__property Vcl::Graphics::TPenStyle SelectedPenStyle = {read=GetSelectedPenStyle, nodefault};
	__property Tools;
	
__published:
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property Style;
	__property ShowHint;
	__property SelectedIndex;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property OnHotTool;
	__property OnDrawTool;
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrPenStyleSelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrPenWidthSelector;
class PASCALIMPLEMENTATION TDgrPenWidthSelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	void __fastcall Initialize(void);
	int __fastcall GetSelectedPenWidth(void);
	void __fastcall SelectorPanelOnDrawItem(System::TObject* Sender, int Index, const System::Types::TRect &R);
	int __fastcall GetPenWidth(int AIndex);
	
protected:
	virtual void __fastcall SetSelectorPanel(void);
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
public:
	__fastcall virtual TDgrPenWidthSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrPenWidthSelector(void);
	__property AppearanceStyle;
	__property int SelectedPenWidth = {read=GetSelectedPenWidth, nodefault};
	__property Tools;
	
__published:
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property ShowHint;
	__property Style;
	__property SelectedIndex;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property OnHotTool;
	__property OnDrawTool;
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrPenWidthSelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrBrushStyleSelector;
class PASCALIMPLEMENTATION TDgrBrushStyleSelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	bool FBrushAutoColor;
	void __fastcall Initialize(void);
	void __fastcall SelectorPanelOnDrawItem(System::TObject* Sender, int Index, const System::Types::TRect &R);
	Vcl::Graphics::TBrushStyle __fastcall GetBrushStyle(int AIndex);
	Vcl::Graphics::TBrushStyle __fastcall GetSelectedBrushStyle(void);
	
protected:
	virtual void __fastcall Loaded(void);
	virtual void __fastcall SetSelectorPanel(void);
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
public:
	__fastcall virtual TDgrBrushStyleSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrBrushStyleSelector(void);
	__property AppearanceStyle;
	__property Vcl::Graphics::TBrushStyle SelectedBrushStyle = {read=GetSelectedBrushStyle, nodefault};
	__property Tools;
	
__published:
	__property bool BrushAutoColor = {read=FBrushAutoColor, write=FBrushAutoColor, nodefault};
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property Style;
	__property ShowHint;
	__property SelectedIndex;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property OnHotTool;
	__property OnDrawTool;
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrBrushStyleSelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrShadowSelector;
class PASCALIMPLEMENTATION TDgrShadowSelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	Atdiagram::TBlockShadow* FShadow;
	bool FShowSettingsOption;
	void __fastcall Initialize(void);
	void __fastcall SetShowSettingsOption(const bool Value);
	
protected:
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall SetSelectorPanel(void);
	
public:
	__fastcall virtual TDgrShadowSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrShadowSelector(void);
	__property AppearanceStyle;
	__property Tools;
	
__published:
	__property bool ShowSettingsOption = {read=FShowSettingsOption, write=SetShowSettingsOption, nodefault};
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property ShowHint;
	__property Style;
	__property SelectedIndex;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property OnHotTool;
	__property OnDrawTool;
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrShadowSelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrTransparencySelector;
class PASCALIMPLEMENTATION TDgrTransparencySelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	void __fastcall Initialize(void);
	int __fastcall GetSelectedTransparency(void);
	void __fastcall SelectorPanelOnDrawItem(System::TObject* Sender, int Index, const System::Types::TRect &R);
	
protected:
	virtual void __fastcall SetSelectorPanel(void);
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
public:
	__fastcall virtual TDgrTransparencySelector(System::Classes::TComponent* AOwner);
	__property AppearanceStyle;
	__property int SelectedTransparency = {read=GetSelectedTransparency, nodefault};
	__property Tools;
	
__published:
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property Style;
	__property ShowHint;
	__property SelectedIndex;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property OnHotTool;
	__property OnDrawTool;
public:
	/* TDgrCustomSelector.Destroy */ inline __fastcall virtual ~TDgrTransparencySelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrTransparencySelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrGradientDirectionSelector;
class PASCALIMPLEMENTATION TDgrGradientDirectionSelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	Atdiagram::TDiagramGradient* FGradient;
	bool FShowSelectedGradient;
	void __fastcall SetEndColor(const System::Uitypes::TColor Value);
	void __fastcall SetStartColor(const System::Uitypes::TColor Value);
	void __fastcall SelectorPanelOnDrawItem(System::TObject* Sender, int Index, const System::Types::TRect &R);
	void __fastcall Initialize(void);
	System::Uitypes::TColor __fastcall GetEndColor(void);
	System::Uitypes::TColor __fastcall GetStartColor(void);
	Atdiagram::TGradientDirection __fastcall GetGradientDirection(int AIndex);
	void __fastcall SetShowSelectedGradient(const bool Value);
	
protected:
	virtual void __fastcall DrawGlyphAndCaption(Vcl::Graphics::TBitmap* aGlyph, const System::Types::TRect &R);
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	virtual void __fastcall SetSelectorPanel(void);
	
public:
	__fastcall virtual TDgrGradientDirectionSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrGradientDirectionSelector(void);
	__property AppearanceStyle;
	__property Tools;
	
__published:
	__property bool ShowSelectedGradient = {read=FShowSelectedGradient, write=SetShowSelectedGradient, nodefault};
	__property System::Uitypes::TColor StartColor = {read=GetStartColor, write=SetStartColor, nodefault};
	__property System::Uitypes::TColor EndColor = {read=GetEndColor, write=SetEndColor, nodefault};
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property Style;
	__property SelectedIndex;
	__property ShowHint;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property OnHotTool;
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrGradientDirectionSelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


typedef void __fastcall (__closure *TMoreColorsOptionEvent)(System::TObject* Sender, System::Uitypes::TColor &ANewColor, bool &AApply);

class DELPHICLASS TDgrCustomColorSelector;
class PASCALIMPLEMENTATION TDgrCustomColorSelector : public TDgrCustomSelector
{
	typedef TDgrCustomSelector inherited;
	
private:
	TDgrColorCubePanel* FColorCubePanel;
	TDgrColorSpectrumPanel* FSpectrumPanel;
	TColorSelectionStyle FColorSelectionStyle;
	bool FShowSelectedColor;
	System::Uitypes::TColor FSelectedColor;
	bool FShowRGBHint;
	bool FShowMoreColors;
	TMoreColorsOptionEvent FOnMoreColorsOption;
	void __fastcall SetColorSelectionStyle(const TColorSelectionStyle Value);
	void __fastcall SelectorPanelOnDrawItem(System::TObject* Sender, int Index, const System::Types::TRect &R);
	void __fastcall SetShowSelectedColor(const bool Value);
	void __fastcall CubePanelOnSelect(System::TObject* Sender);
	void __fastcall SpectrumPanelOnSelect(System::TObject* Sender);
	void __fastcall SetSelectedColor(const System::Uitypes::TColor Value);
	System::Uitypes::TColor __fastcall GetSelectedColor(void);
	void __fastcall SetShowMoreColors(const bool Value);
	
protected:
	void __fastcall DefaultInitialize(void);
	virtual void __fastcall Initialize(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall OnToolSelect(void);
	virtual void __fastcall SetSelectorPanel(void);
	virtual void __fastcall DrawGlyphAndCaption(Vcl::Graphics::TBitmap* aGlyph, const System::Types::TRect &R);
	
public:
	__fastcall virtual TDgrCustomColorSelector(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrCustomColorSelector(void);
	__property AppearanceStyle;
	__property ButtonsPerRow = {default=1};
	__property TColorSelectionStyle SelectionStyle = {read=FColorSelectionStyle, write=SetColorSelectionStyle, default=0};
	__property bool ShowSelectedColor = {read=FShowSelectedColor, write=SetShowSelectedColor, default=1};
	__property System::Uitypes::TColor SelectedColor = {read=GetSelectedColor, write=SetSelectedColor, nodefault};
	__property bool ShowRGBHint = {read=FShowRGBHint, write=FShowRGBHint, nodefault};
	__property bool ShowMoreColors = {read=FShowMoreColors, write=SetShowMoreColors, nodefault};
	__property TMoreColorsOptionEvent OnMoreColorsOption = {read=FOnMoreColorsOption, write=FOnMoreColorsOption};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrCustomColorSelector(HWND ParentWindow) : TDgrCustomSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrColorSelector;
class PASCALIMPLEMENTATION TDgrColorSelector : public TDgrCustomColorSelector
{
	typedef TDgrCustomColorSelector inherited;
	
protected:
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
public:
	__property Tools;
	
__published:
	__property SelectionStyle = {default=0};
	__property ShowSelectedColor = {default=1};
	__property SelectedColor;
	__property ShowRGBHint;
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property ShowHint;
	__property Style;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property ShowMoreColors;
	__property OnMoreColorsOption;
public:
	/* TDgrCustomColorSelector.Create */ inline __fastcall virtual TDgrColorSelector(System::Classes::TComponent* AOwner) : TDgrCustomColorSelector(AOwner) { }
	/* TDgrCustomColorSelector.Destroy */ inline __fastcall virtual ~TDgrColorSelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrColorSelector(HWND ParentWindow) : TDgrCustomColorSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrTextColorSelector;
class PASCALIMPLEMENTATION TDgrTextColorSelector : public TDgrCustomColorSelector
{
	typedef TDgrCustomColorSelector inherited;
	
protected:
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
__published:
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property ShowHint;
	__property ShowSelectedColor = {default=1};
	__property SelectedColor;
	__property Style;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property ShowMoreColors;
	__property OnMoreColorsOption;
public:
	/* TDgrCustomColorSelector.Create */ inline __fastcall virtual TDgrTextColorSelector(System::Classes::TComponent* AOwner) : TDgrCustomColorSelector(AOwner) { }
	/* TDgrCustomColorSelector.Destroy */ inline __fastcall virtual ~TDgrTextColorSelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrTextColorSelector(HWND ParentWindow) : TDgrCustomColorSelector(ParentWindow) { }
	
};


class DELPHICLASS TDgrPenColorSelector;
class PASCALIMPLEMENTATION TDgrPenColorSelector : public TDgrCustomColorSelector
{
	typedef TDgrCustomColorSelector inherited;
	
protected:
	virtual void __fastcall ApplyDiagramSettings(Atdiagram::TatDiagram* ADiagram);
	
__published:
	__property AutoThemeAdapt;
	__property BorderColor = {default=536870911};
	__property BorderDownColor = {default=536870911};
	__property BorderHotColor = {default=536870911};
	__property BorderDropDownColor = {default=8421504};
	__property Caption;
	__property Color = {default=-16777211};
	__property ColorTo = {default=536870911};
	__property ColorDown;
	__property ColorDownTo = {default=536870911};
	__property ColorHot;
	__property ColorHotTo = {default=536870911};
	__property ColorDropDown;
	__property ColorDropDownTo = {default=536870911};
	__property ColorSelected;
	__property ColorSelectedTo;
	__property DropDownButton = {default=0};
	__property Glyph;
	__property GlyphHot;
	__property GlyphDown;
	__property ShowHint;
	__property ShowSelectedColor = {default=1};
	__property SelectedColor;
	__property Style;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnDropDown;
	__property OnClick;
	__property OnSelect;
	__property ShowMoreColors;
	__property OnMoreColorsOption;
public:
	/* TDgrCustomColorSelector.Create */ inline __fastcall virtual TDgrPenColorSelector(System::Classes::TComponent* AOwner) : TDgrCustomColorSelector(AOwner) { }
	/* TDgrCustomColorSelector.Destroy */ inline __fastcall virtual ~TDgrPenColorSelector(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDgrPenColorSelector(HWND ParentWindow) : TDgrCustomColorSelector(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 MINBUTTONSIZE = System::Int8(0x10);
static const System::Int8 TABLECELLSIZE = System::Int8(0x18);
static const System::Int8 MAJ_VER = System::Int8(0x2);
static const System::Int8 MIN_VER = System::Int8(0x0);
static const System::Int8 REL_VER = System::Int8(0x0);
static const System::Int8 BLD_VER = System::Int8(0x0);
}	/* namespace Dgrselectors */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGRSELECTORS)
using namespace Dgrselectors;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgrselectorsHPP
