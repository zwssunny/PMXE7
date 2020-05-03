//---------------------------------------------------------------------------

#ifndef ZMaskEditH
#define ZMaskEditH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <StdCtrls.hpp>
#include "ColorDefine.h"
//---------------------------------------------------------------------------
class PACKAGE TZMaskEdit : public TMaskEdit
{
private:
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FIsFocused;
  bool FIsHovered;
  bool FMaskEditFlat;

  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetMaskEditFlat(bool value);
  void __fastcall WMPaint(TWMPaint &Message);
  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
  void __fastcall WMSetFocus(TWMSetFocus &Message);
  void __fastcall WMKillFocus(TWMSetFocus &Message);
protected:
  void __fastcall DrawMaskEditFlat();
public:
  __fastcall TZMaskEdit(TComponent* Owner);
  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
    VCL_MESSAGE_HANDLER(WM_SETFOCUS,TWMSetFocus,WMSetFocus);
    VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TWMSetFocus,WMKillFocus);
  END_MESSAGE_MAP(TMaskEdit);
__published:
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=clWhite};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=crFocusedColor};
  __property bool Flat={read=FMaskEditFlat,write=SetMaskEditFlat};
};
//---------------------------------------------------------------------------
#endif
