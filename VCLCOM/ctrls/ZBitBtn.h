//---------------------------------------------------------------------------

#ifndef ZBitBtnH
#define ZBitBtnH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include "ColorDefine.h"
//---------------------------------------------------------------------------
class PACKAGE TZBitBtn : public TBitBtn
{
private:
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FMouseDown;
  bool FIsHovered;
  bool FBitBtnFlat;

  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetBitBtnFlat(bool value);
protected:
  void __fastcall WMPaint(TWMPaint &Message);
  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
  void __fastcall WMSetFocus(TWMSetFocus &Message);
  void __fastcall WMKillFocus(TWMSetFocus &Message);
  void __fastcall WMMouseUp(TMessage &Message);
  void __fastcall WMMouseDown(TMessage &Message);
  virtual void __fastcall DrawBitBtnFlat();
public:
  __fastcall TZBitBtn(TComponent* Owner);
  __fastcall ~TZBitBtn();

__published:
  __property bool Flat={read=FBitBtnFlat,write=SetBitBtnFlat};
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=crFocusedColor};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=crHoverColor};
  __property Color;

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
    VCL_MESSAGE_HANDLER(WM_SETFOCUS,TWMSetFocus,WMSetFocus);
	VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TWMSetFocus,WMKillFocus);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN,TMessage,WMMouseDown);
	VCL_MESSAGE_HANDLER(WM_LBUTTONUP,TMessage,WMMouseUp);
  END_MESSAGE_MAP(TBitBtn);
};
//---------------------------------------------------------------------------
#endif
