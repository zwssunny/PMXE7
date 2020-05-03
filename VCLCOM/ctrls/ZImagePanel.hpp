// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ZImagePanel.pas' rev: 27.00 (Windows)

#ifndef ZimagepanelHPP
#define ZimagepanelHPP

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
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <System.TypInfo.hpp>	// Pascal unit
#include <System.SyncObjs.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Zimagepanel
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TMenuWindow;
class DELPHICLASS TZImagePanel;
class PASCALIMPLEMENTATION TMenuWindow : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Winapi::Messages::TWMNCHitTest &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMTextChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Winapi::Messages::TWMEraseBkgnd &Message);
	
protected:
	TZImagePanel* ParentControl;
	int PaintHeight;
	System::Classes::TStringList* FItems;
	int FCurPos;
	int TmpPos;
	int FItemHeight;
	int FItemWidth;
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	virtual void __fastcall Paint(void);
	
public:
	void __fastcall CaclCurPos(const System::Types::TPoint &P);
	__fastcall virtual TMenuWindow(System::Classes::TComponent* AOwner);
	virtual void __fastcall ActivateHint(const System::Types::TRect &Rect, const System::UnicodeString AHint);
	virtual void __fastcall ActivateHintData(const System::Types::TRect &Rect, const System::UnicodeString AHint, void * AData);
	virtual System::Types::TRect __fastcall CalcHintRect(int MaxWidth, const System::UnicodeString AHint, System::Classes::TStringList* AData);
	virtual bool __fastcall IsHintMsg(tagMSG &Msg);
	void __fastcall ReleaseHandle(void);
	__property Caption = {default=0};
	__property Color = {default=-16777211};
	__property Canvas;
public:
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TMenuWindow(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TMenuWindow(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
};


typedef void __fastcall (__closure *TPopupClick)(System::TObject* Sender, int Index);

typedef void __fastcall (__closure *TItemChanged)(System::TObject* Sender, int Index);

typedef void __fastcall (__closure *TPopupActive)(System::TObject* Sender);

class PASCALIMPLEMENTATION TZImagePanel : public Vcl::Controls::TGraphicControl
{
	typedef Vcl::Controls::TGraphicControl inherited;
	
private:
	Vcl::Extctrls::TTimer* FTimer;
	Vcl::Controls::TImageList* FImageList;
	int FImageIndex;
	int FSelectIndex;
	Vcl::Controls::TCaption FCaption;
	System::Classes::TStringList* FItems;
	TMenuWindow* FMenuWindow;
	System::UnicodeString FTitle;
	TPopupClick FOnPopupClick;
	TItemChanged FOnItemChanged;
	TPopupActive FOnPopupActive;
	Vcl::Graphics::TPicture* FPicture;
	Vcl::Graphics::TPicture* FPictureSelected;
	void __fastcall OnTimer(System::TObject* Sender);
	void __fastcall SetItems(System::Classes::TStringList* Value);
	void __fastcall SetPicture(Vcl::Graphics::TPicture* Value);
	void __fastcall SetPictureSelected(Vcl::Graphics::TPicture* Value);
	void __fastcall PictureChanged(System::TObject* Sender);
	DYNAMIC void __fastcall Progress(System::TObject* Sender, Vcl::Graphics::TProgressStage Stage, System::Byte PercentDone, bool RedrawNow, const System::Types::TRect &R, const System::UnicodeString Msg);
	
protected:
	void __fastcall HideHint(void);
	void __fastcall SetCaption(Vcl::Controls::TCaption Value);
	Vcl::Controls::TCaption __fastcall GetCaption(void);
	virtual void __fastcall Paint(void);
	
public:
	bool FPaintNormal;
	__fastcall virtual TZImagePanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TZImagePanel(void);
	HIDESBASE MESSAGE void __fastcall WMMOUSEMOVE(Winapi::Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Winapi::Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	__property MouseCapture;
	__property Vcl::Graphics::TPicture* Picture = {read=FPicture, write=SetPicture};
	__property Vcl::Graphics::TPicture* PictureSelected = {read=FPictureSelected, write=SetPictureSelected};
	
__published:
	__property Align = {default=0};
	__property DragCursor = {default=-12};
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property Caption = {default=0};
	__property Color = {default=-16777211};
	__property Font;
	__property ParentColor = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property Visible = {default=1};
	__property OnClick;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDrag;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnStartDrag;
	__property Vcl::Controls::TImageList* ImageList = {read=FImageList, write=FImageList};
	__property int ImageIndex = {read=FImageIndex, write=FImageIndex, nodefault};
	__property int SelectIndex = {read=FSelectIndex, write=FSelectIndex, nodefault};
	__property System::Classes::TStringList* Items = {read=FItems, write=SetItems};
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
	__property TPopupClick OnPopupClick = {read=FOnPopupClick, write=FOnPopupClick};
	int __fastcall GetItemWidth(void);
	int __fastcall GetItemHeight(void);
	__property TItemChanged OnItemChanged = {read=FOnItemChanged, write=FOnItemChanged};
	__property TPopupActive OnPopupActive = {read=FOnPopupActive, write=FOnPopupActive};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Zimagepanel */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ZIMAGEPANEL)
using namespace Zimagepanel;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ZimagepanelHPP
