//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZMemo.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZMemo *)
{
  new TZMemo(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZMemo::TZMemo(TComponent* Owner)
  : TMemo(Owner)
{
  FBorderColor=clBlack;//crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  FMemoFlat=false;
}
//---------------------------------------------------------------------------
namespace Zmemo
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZMemo)};
	 RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::CMMouseEnter(TMessage &Message)
{
  TMemo::Dispatch(&Message);
  if(FMemoFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
      Color=(TColor)ColorToRGB(FFocusedColor);
    else
      Color=(TColor)ColorToRGB(FHoverColor);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::CMMouseLeave(TMessage &Message)
{
  TMemo::Dispatch(&Message);
  if(FMemoFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
      Color=(TColor)ColorToRGB(FFocusedColor);
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::WMSetFocus(TWMSetFocus &Message)
{
  TMemo::Dispatch(&Message);
  if(FMemoFlat)
  {
    FIsFocused=true;
    Color=(TColor)ColorToRGB(FFocusedColor);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::WMKillFocus(TWMSetFocus &Message)
{
  TMemo::Dispatch(&Message);
  if(FMemoFlat)
  {
    FIsFocused=false;
    if(FIsHovered)
      Color=(TColor)ColorToRGB(FHoverColor);
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::WMPaint(TWMPaint &Message)
{
  TMemo::Dispatch(&Message);
  DrawMemoFlat();
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::WMSize(TWMSize &Message)
{
  TMemo::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::DrawMemoFlat()
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
//---------------------------------------------------------------------------
void __fastcall TZMemo::SetBorderColor(TColor value)
{
  FBorderColor=value;
Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::SetHoverColor(TColor value)
{
  FHoverColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZMemo::SetMemoFlat(bool value)
{
  FMemoFlat=value;
  if(FMemoFlat)
  {
     Ctl3D = false;
     BorderStyle = bsSingle;
  }
  Invalidate();
}

