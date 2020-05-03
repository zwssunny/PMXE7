//---------------------------------------------------------------------------

#ifndef ZButtonH
#define ZButtonH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include "ColorDefine.h"
//---------------------------------------------------------------------------
class PACKAGE TZButton : public TButton
{
private:
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FIsFocused;
  bool FIsHovered;
  bool FButtonFlat;
  bool FMouseDown;

  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetButtonFlat(bool value);

protected:
  void __fastcall WMPaint(TWMPaint &Message);
  void __fastcall CMMouseEnter(Messages::TMessage &Message);
  void __fastcall CMMouseLeave(Messages::TMessage &Message);
	void __fastcall WMSetFocus(TWMSetFocus &Message);
	void __fastcall WMKillFocus(TWMSetFocus &Message);
  void __fastcall WMLButtonDblClk(TWMMouse &Message);
  void __fastcall CNDrawItem(TWMDrawItem &Message);
  void __fastcall WMMouseDown(Messages::TMessage &Message);
  void __fastcall WMMouseUp(Messages::TMessage &Message);

  virtual void __fastcall DrawButtonFlat();

public:
  __fastcall TZButton(TComponent* Owner);

__published:
  __property bool Flat={read=FButtonFlat,write=SetButtonFlat};
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=0x007DCDF9};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=0x007DCDF9};

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,Messages::TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,Messages::TMessage,CMMouseEnter);
    VCL_MESSAGE_HANDLER(WM_SETFOCUS,TWMSetFocus,WMSetFocus);
    VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TWMSetFocus,WMKillFocus);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDBLCLK,TWMMouse,WMLButtonDblClk);
    VCL_MESSAGE_HANDLER(CN_DRAWITEM,TWMDrawItem,CNDrawItem);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN,Messages::TMessage,WMMouseDown);
    VCL_MESSAGE_HANDLER(WM_LBUTTONUP,Messages::TMessage,WMMouseUp);
  END_MESSAGE_MAP(TButton);
};
//---------------------------------------------------------------------------
#endif
