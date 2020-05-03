//---------------------------------------------------------------------------

#ifndef ZDateEditH
#define ZDateEditH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "ZMonthCalendar.h"
#include "ColorDefine.h"
class TBYPopupForm;
//---------------------------------------------------------------------------
class PACKAGE TZDateEdit : public TCustomEdit
{
private:
  TSpeedButton *FDateButton;
  TNotifyEvent FOnButtonClick;
  TBYPopupForm* EditForm;
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FIsFocused;
  bool FIsHovered;
  bool FDateEditFlat;
  String FBackDate;

  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetDateEditFlat(bool value);

  String __fastcall GetDate();
  void __fastcall SetDate(String value);
  bool __fastcall GetButtonFlat();
  void __fastcall SetButtonFlat(bool value);
  bool __fastcall GetButtonTransparent();
  void __fastcall SetButtonTransparent(bool value);

protected:
  void __fastcall WMPaint(TWMPaint &Message);
  void __fastcall WMSize(TWMSize &Message);
  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
  void __fastcall WMSetFocus(TWMSetFocus &Message);
  void __fastcall WMKillFocus(TWMSetFocus &Message);
  void __fastcall WMKeyDown(TWMKeyDown&Message);
  void __fastcall WMChar(TWMKeyUp&Message);

  static int DayCount(String DateString);
  static String ValidDay(String DateString);

  virtual void __fastcall ButtonClick(TObject *Sender);
  virtual void __fastcall DrawDateEditFlat();
  void __fastcall ClearCtrlBorder(TWinControl* WinControl, TColor color);
public:
  __fastcall TZDateEdit(TComponent* Owner);
  __fastcall ~TZDateEdit();

  __property String Date={read=GetDate, write=SetDate};
  __property String Text={read=GetDate, write=SetDate};

  BEGIN_MESSAGE_MAP
     VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
     VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
     VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
     VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
     VCL_MESSAGE_HANDLER(WM_SETFOCUS,TWMSetFocus,WMSetFocus);
     VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TWMSetFocus,WMKillFocus);
     VCL_MESSAGE_HANDLER(WM_KEYDOWN,TWMKeyDown,WMKeyDown);
     VCL_MESSAGE_HANDLER(WM_CHAR,TWMChar,WMChar);
  END_MESSAGE_MAP(TCustomEdit);
__published:
  __property TNotifyEvent OnButtonClick={read=FOnButtonClick,write=FOnButtonClick};
  __property bool ButtonFlat={read=GetButtonFlat,write=SetButtonFlat,default=true};
  __property bool ButtonTransparent={read=GetButtonTransparent,write=SetButtonTransparent,default=true};
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=clWhite};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=crFocusedColor};
  __property bool Flat={read=FDateEditFlat,write=SetDateEditFlat};

//inherited form TCustomMaskEdit
	__property Anchors ;
	__property AutoSelect ;
	__property AutoSize ;
	__property BiDiMode ;
	__property BorderStyle ;
	__property CharCase ;
	__property Color ;
	__property Constraints ;
	__property Ctl3D ;
	__property DragCursor ;
	__property DragKind ;
	__property DragMode ;
	__property Enabled ;
	__property Font ;
	__property ImeMode ;
	__property ImeName ;
	__property MaxLength ;
	__property ParentBiDiMode ;
	__property ParentColor ;
	__property ParentCtl3D ;
	__property ParentFont ;
	__property ParentShowHint ;
	__property PasswordChar ;
	__property PopupMenu ;
	__property ReadOnly ;
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnChange ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDock ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDock ;
	__property OnStartDrag ;

};
class TBYPopupForm : public TForm
{
public:
    TZDateEdit* DateEdit;
    TZMonthCalendar *MonthCale;
    void __fastcall  MonthCalendarSelect(TObject *Sender);
    void __fastcall  MonthCalendarClick(TObject *Sender);
    void __fastcall  MonthCalendarKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
    void __fastcall  MonthCalendarExit(TObject *Sender);
    void __fastcall  FormClose(System::TObject* Sender, TCloseAction &Action);
    void __fastcall  WMActivate(TMessage &Message);
    BEGIN_MESSAGE_MAP
          VCL_MESSAGE_HANDLER(WM_ACTIVATE, TMessage, WMActivate);
    END_MESSAGE_MAP(TForm);
public:
    __fastcall TBYPopupForm();
	void ShowForm(TZDateEdit* ADateEdit);
};
//---------------------------------------------------------------------------
#endif
