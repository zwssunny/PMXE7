//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZMaskEdit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZMaskEdit *)
{
  new TZMaskEdit(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZMaskEdit::TZMaskEdit(TComponent* Owner)
  : TMaskEdit(Owner)
{
  FBorderColor=crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  FMaskEditFlat=false;
}
//---------------------------------------------------------------------------
namespace Zmaskedit
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZMaskEdit)};
	 RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::CMMouseEnter(TMessage &Message)
{
  TCustomMaskEdit::Dispatch(&Message);
  if(FMaskEditFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
      Color=(TColor)ColorToRGB(FFocusedColor);
    else
      Color=(TColor)ColorToRGB(FHoverColor);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::CMMouseLeave(TMessage &Message)
{
  TCustomMaskEdit::Dispatch(&Message);
  if(FMaskEditFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
      Color=(TColor)ColorToRGB(FFocusedColor);
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::WMSetFocus(TWMSetFocus &Message)
{
  TCustomMaskEdit::Dispatch(&Message);
  if(FMaskEditFlat)
  {
    FIsFocused=true;
    Color=(TColor)ColorToRGB(FFocusedColor);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::WMKillFocus(TWMSetFocus &Message)
{
  TCustomMaskEdit::Dispatch(&Message);
  if(FMaskEditFlat)
  {
    FIsFocused=false;
    if(FIsHovered)
      Color=(TColor)ColorToRGB(FHoverColor);
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::WMPaint(TWMPaint &Message)
{
  SendMessage(this->Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
  TCustomMaskEdit::Dispatch(&Message);
  DrawMaskEditFlat();
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::DrawMaskEditFlat()
{
  if(!FIsHovered && !FIsFocused)
    ParentColor=true;
  HBRUSH brush;
  TRect FRect;
  HDC dc = GetDC(Handle);
  brush=CreateSolidBrush(ColorToRGB(FBorderColor));
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FRect.Left=ClientRect.Left;
  FRect.Top=ClientRect.Top;
  FRect.Right=ClientRect.Right;
  FRect.Bottom=ClientRect.Bottom;
  FrameRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);
  ReleaseDC(Handle, dc);
}
void __fastcall TZMaskEdit::SetBorderColor(TColor value)
{
  FBorderColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZMaskEdit::SetHoverColor(TColor value)
{
  FHoverColor=value;
  Invalidate();
}
void __fastcall TZMaskEdit::SetMaskEditFlat(bool value)
{
  FMaskEditFlat=value;
  if(value)
     Ctl3D = false;
  else
     Ctl3D = true;
  Invalidate();
}
