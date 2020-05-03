//---------------------------------------------------------------------------

#ifndef ZRadioButtonH
#define ZRadioButtonH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include "ColorDefine.h"
//---------------------------------------------------------------------------
class PACKAGE TZRadioButton : public TRadioButton
{
private:
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FIsFocused;
  bool FIsHovered;
  bool FRadioButtonFlat;

  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetRadioButtonFlat(bool value);
  void __fastcall DrawRadioButtonFlat();

protected:
  void __fastcall WMSize(TWMSize &Message);
  void __fastcall WMPaint(TWMPaint &Message);
  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
	void __fastcall WMSetFocus(TWMSetFocus &Message);
	void __fastcall WMKillFocus(TWMSetFocus &Message);
  void __fastcall CNCommand(TWMCommand &Message);
  void __fastcall CMCtl3DChanged(TMessage &Message);

  virtual void __fastcall SetChecked(bool Value);

public:
  __fastcall TZRadioButton(TComponent* Owner);

__published:
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=clWhite};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=crFocusedColor};
  __property bool Flat={read=FRadioButtonFlat,write=SetRadioButtonFlat};

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
    VCL_MESSAGE_HANDLER(WM_SETFOCUS,TWMSetFocus,WMSetFocus);
    VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TWMSetFocus,WMKillFocus);
    VCL_MESSAGE_HANDLER(CN_COMMAND,TWMCommand,CNCommand);
    VCL_MESSAGE_HANDLER(CM_CTL3DCHANGED,TMessage,CMCtl3DChanged);
  END_MESSAGE_MAP(TRadioButton);

};
//---------------------------------------------------------------------------
#endif
