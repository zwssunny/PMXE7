// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ZXPTab.pas' rev: 27.00 (Windows)

#ifndef ZxptabHPP
#define ZxptabHPP

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
#include <XPButton.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Zxptab
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TZXPTabChangeEvent)(System::TObject* Sender, int NewTab, bool &AllowChange);

typedef void __fastcall (__closure *TZXPTabCloseEvent)(System::TObject* Sender, int TabSelected, bool &AllowClose);

typedef void __fastcall (__closure *TZXPTabClickEvent)(System::TObject* Sender, int TabClicked);

enum DECLSPEC_DENUM TTabLayOut : unsigned char { tlTop, tlBottom };

enum DECLSPEC_DENUM TTabStyle : unsigned char { tsRectangle, tsTrapezoid };

class DELPHICLASS TZXPTab;
class DELPHICLASS TZXPTabs;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TZXPTab : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TZXPTabs* FTabs;
	System::UnicodeString FCaption;
	int FSize;
	int FStartPos;
	int FOffStartPos;
	System::Uitypes::TImageIndex FImageIndex;
	bool FCanClose;
	bool FSelected;
	bool FEnabled;
	bool FVisible;
	void __fastcall SetImageIndex(const System::Uitypes::TImageIndex Value);
	void __fastcall SetCaption(const System::UnicodeString Value);
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetVisible(const bool Value);
	
public:
	__property int Size = {read=FSize, write=FSize, nodefault};
	__property int StartPos = {read=FStartPos, write=FStartPos, nodefault};
	__property int OffStartPos = {read=FOffStartPos, write=FOffStartPos, nodefault};
	__property bool Selected = {read=FSelected, write=FSelected, nodefault};
	__fastcall virtual TZXPTab(System::Classes::TCollection* Collection);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::UnicodeString Caption = {read=FCaption, write=SetCaption};
	__property System::Uitypes::TImageIndex ImageIndex = {read=FImageIndex, write=SetImageIndex, nodefault};
	__property bool CanClose = {read=FCanClose, write=FCanClose, nodefault};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TZXPTab(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TZXPTabSet;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TZXPTabs : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TZXPTab* operator[](int Index) { return Items[Index]; }
	
private:
	TZXPTabSet* FTabSet;
	HIDESBASE TZXPTab* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TZXPTab* Value);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner(void);
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	__fastcall TZXPTabs(TZXPTabSet* Tabset);
	HIDESBASE TZXPTab* __fastcall Add(void);
	__property TZXPTab* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TZXPTabs(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TZXPTabSet : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	Xpbutton::TTimerXPButton* FPrevBtn;
	Xpbutton::TTimerXPButton* FNextBtn;
	Xpbutton::TTimerXPButton* FCloseBtn;
	Vcl::Imglist::TCustomImageList* FImages;
	Vcl::Graphics::TBitmap* FTabsBitmap;
	Vcl::Extctrls::TNotebook* FNoteBook;
	int FTabIndex;
	TTabLayOut FLayOut;
	bool FTabChanged;
	bool FAllowChange;
	bool FBoldSelect;
	bool FScrollable;
	TTabStyle FTabStyle;
	int FEdgeWidth;
	int FIndent;
	bool FInitializing;
	int FTabHeight;
	int FMargin;
	int FScrollPos;
	int FScrollSpeed;
	System::Uitypes::TColor FSelectedColor;
	System::Uitypes::TColor FUnselectedColor;
	System::Uitypes::TColor FBackgroundColor;
	System::Uitypes::TColor FSelectedFontColor;
	System::Uitypes::TColor FUnSelectedFontColor;
	System::Uitypes::TColor FHighLightColor;
	System::Uitypes::TColor FShadowColor;
	System::Uitypes::TColor FSaperatorColor;
	System::Uitypes::TColor FDisabledColor;
	System::Uitypes::TColor FDisabledFontColor;
	TZXPTabChangeEvent FOnChange;
	TZXPTabCloseEvent FOnClose;
	TZXPTabClickEvent FOnTabClick;
	void __fastcall NBPageChange(System::TObject* Sender);
	void __fastcall SetSelectedColor(System::Uitypes::TColor Value);
	void __fastcall SetUnselectedColor(System::Uitypes::TColor Value);
	void __fastcall SetSelectedFontColor(System::Uitypes::TColor Value);
	void __fastcall SetUnselectedFontColor(System::Uitypes::TColor Value);
	void __fastcall SetBackgroundColor(System::Uitypes::TColor Value);
	void __fastcall SetMargin(int Value);
	void __fastcall SetTabIndex(int Value);
	int __fastcall GetTabsCount(void);
	void __fastcall SetTabHeight(int Value);
	void __fastcall SetTabLayOut(TTabLayOut Value);
	void __fastcall SetBoldSelect(bool Value);
	void __fastcall SetScrollable(bool Value);
	void __fastcall SetHighlightColor(System::Uitypes::TColor Value);
	void __fastcall SetShadowColor(System::Uitypes::TColor Value);
	void __fastcall SetSaperatorColor(System::Uitypes::TColor Value);
	void __fastcall SetTabStyle(TTabStyle value);
	void __fastcall SetEdgeWidth(int value);
	void __fastcall SetIndent(int value);
	void __fastcall SetNoteBook(Vcl::Extctrls::TNotebook* value);
	void __fastcall SetTabs(TZXPTabs* value);
	HIDESBASE MESSAGE void __fastcall WMSize(Winapi::Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall CMSysColorChange(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMDesignHitTest(Winapi::Messages::TWMMouse &Message);
	void __fastcall PrevBtnClick(System::TObject* Sender);
	void __fastcall NextBtnClick(System::TObject* Sender);
	void __fastcall CloseBtnClick(System::TObject* Sender);
	void __fastcall ClearAllSelectedState(void);
	void __fastcall ScrollTabs(int Offset);
	void __fastcall BuildTabImage(Vcl::Graphics::TCanvas* ACanvas);
	void __fastcall DrawSelectedTab(Vcl::Graphics::TCanvas* ACanvas, TZXPTab* ATab);
	void __fastcall DrawTab(Vcl::Graphics::TCanvas* ACanvas, TZXPTab* ATab);
	void __fastcall SetButtonStat(void);
	void __fastcall DrawTFirstTab(Vcl::Graphics::TCanvas* ACanvas);
	void __fastcall DrawTTab(Vcl::Graphics::TCanvas* ACanvas, TZXPTab* ATab);
	void __fastcall DrawTLastTab(Vcl::Graphics::TCanvas* ACanvas);
	void __fastcall DrawTSelectedTab(Vcl::Graphics::TCanvas* ACanvas);
	void __fastcall SetDisabledColor(const System::Uitypes::TColor Value);
	void __fastcall SetDisabledFontColor(const System::Uitypes::TColor Value);
	void __fastcall SetImages(Vcl::Imglist::TCustomImageList* const Value);
	
protected:
	TZXPTabs* FTabs;
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TZXPTabSet(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TZXPTabSet(void);
	int __fastcall AddTab(System::UnicodeString ACaption, System::Uitypes::TImageIndex AImageIndex, bool ASelected, bool CanClose = true, bool Disabled = false);
	void __fastcall DeleteTab(int AIndex);
	void __fastcall ClearAllTabs(void);
	void __fastcall ChangeTabCaption(int AIndex, System::UnicodeString ACaption);
	void __fastcall UpdateTabs(void);
	void __fastcall CloseTab(int AIndex);
	__property Canvas;
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property System::Uitypes::TColor BackgroundColor = {read=FBackgroundColor, write=SetBackgroundColor, default=-16777201};
	__property bool BoldSelect = {read=FBoldSelect, write=SetBoldSelect, nodefault};
	__property Color = {default=-16777211};
	__property Constraints;
	__property DragCursor = {default=-12};
	__property DragKind = {default=0};
	__property DragMode = {default=0};
	__property System::Uitypes::TColor DisabledColor = {read=FDisabledColor, write=SetDisabledColor, nodefault};
	__property System::Uitypes::TColor DisabledFontColor = {read=FDisabledFontColor, write=SetDisabledFontColor, nodefault};
	__property Enabled = {default=1};
	__property int EdgeWidth = {read=FEdgeWidth, write=SetEdgeWidth, nodefault};
	__property Font;
	__property System::Uitypes::TColor HighlightColor = {read=FHighLightColor, write=SetHighlightColor, nodefault};
	__property int Indent = {read=FIndent, write=SetIndent, nodefault};
	__property Vcl::Extctrls::TNotebook* NoteBook = {read=FNoteBook, write=SetNoteBook};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property System::Uitypes::TColor SaperatorColor = {read=FSaperatorColor, write=SetSaperatorColor, nodefault};
	__property bool Scrollable = {read=FScrollable, write=SetScrollable, nodefault};
	__property int ScrollSpeed = {read=FScrollSpeed, write=FScrollSpeed, default=20};
	__property System::Uitypes::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, nodefault};
	__property ShowHint;
	__property int Margin = {read=FMargin, write=SetMargin, default=4};
	__property System::Uitypes::TColor SelectedColor = {read=FSelectedColor, write=SetSelectedColor, default=-16777201};
	__property System::Uitypes::TColor SelectedFontColor = {read=FSelectedFontColor, write=SetSelectedFontColor, default=-16777208};
	__property int TabHeight = {read=FTabHeight, write=SetTabHeight, default=22};
	__property int TabIndex = {read=FTabIndex, write=SetTabIndex, default=-1};
	__property int TabsCount = {read=GetTabsCount, nodefault};
	__property TZXPTabs* Tabs = {read=FTabs, write=SetTabs};
	__property TTabStyle TabStyle = {read=FTabStyle, write=SetTabStyle, nodefault};
	__property System::Uitypes::TColor UnselectedColor = {read=FUnselectedColor, write=SetUnselectedColor, default=-16777211};
	__property System::Uitypes::TColor UnselectedFontColor = {read=FUnSelectedFontColor, write=SetUnselectedFontColor, default=8421504};
	__property Visible = {default=1};
	__property TZXPTabChangeEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TZXPTabCloseEvent OnClose = {read=FOnClose, write=FOnClose};
	__property TZXPTabClickEvent OnTabClick = {read=FOnTabClick, write=FOnTabClick};
	__property TTabLayOut LayOut = {read=FLayOut, write=SetTabLayOut, nodefault};
	__property Vcl::Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
public:
	/* TWinControl.CreateParented */ inline __fastcall TZXPTabSet(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Zxptab */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ZXPTAB)
using namespace Zxptab;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ZxptabHPP
