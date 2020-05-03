//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZRadioButton.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZRadioButton *)
{
  new TZRadioButton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZRadioButton::TZRadioButton(TComponent* Owner)
  : TRadioButton(Owner)
{
  FBorderColor=crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  FRadioButtonFlat=false;
}
//---------------------------------------------------------------------------
namespace Zradiobutton
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZRadioButton)};
     RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::SetBorderColor(TColor value)
{
  FBorderColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::SetHoverColor(TColor value)
{
  FHoverColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::SetRadioButtonFlat(bool value)
{
  FRadioButtonFlat=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::DrawRadioButtonFlat()
{
  if(!FIsHovered && !FIsFocused)
    ParentColor=true;
  HDC dc = GetDC(Handle);
  HBRUSH brush;
  TRect FRect;
  brush=CreateSolidBrush(GetPixel(dc, 13, 3));
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FRect.Left=ClientRect.Left+1;
  FRect.Top=ClientRect.Top+(ClientRect.Height()-12)/2-1;
  FRect.Right=FRect.Left+12;
  FRect.Bottom=FRect.Top+13;
  FillRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);

  HPEN pen = CreatePen(PS_SOLID, 1, ColorToRGB(FBorderColor));
  HPEN OldPen = (HPEN)SelectObject(dc, pen);
  FRect.Left=ClientRect.Left+1;
  FRect.Top=ClientRect.Top+(ClientRect.Height()-12)/2;
  FRect.Right=FRect.Left+11;
  FRect.Bottom=FRect.Top+11;
  Ellipse(dc,FRect.Left,FRect.Top,FRect.Right,FRect.Bottom);
  SelectObject(dc, OldPen);
  DeleteObject(pen);

  if(Checked)
  {
    pen = CreatePen(PS_SOLID, 1, GetPixel(dc, 13, 3));
	OldPen = (HPEN)SelectObject(dc, pen);
    for(int i=1;i<3;i++)
      Ellipse(dc,FRect.Left+i,FRect.Top+i,FRect.Right-i,FRect.Bottom-i);
    SelectObject(dc, OldPen);
    DeleteObject(pen);
    pen = CreatePen(PS_SOLID, 1, clBlack);
	OldPen = (HPEN)SelectObject(dc, pen);
    Ellipse(dc,FRect.Left+3,FRect.Top+3,FRect.Right-3,FRect.Bottom-3);
    SelectObject(dc, OldPen);
    DeleteObject(pen);
    brush=CreateSolidBrush(clBlack);
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=FRect.Left+4;
    FRect.Top=FRect.Top+4;
    FRect.Right=FRect.Right-4;
    FRect.Bottom=FRect.Bottom-4;
    FillRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
  }
  else
  {
    pen = CreatePen(PS_SOLID, 1, GetPixel(dc, 13, 3));
	OldPen = (HPEN)SelectObject(dc, pen);
    for(int i=1;i<4;i++)
      Ellipse(dc,FRect.Left+i,FRect.Top+i,FRect.Right-i,FRect.Bottom-i);
    SelectObject(dc, OldPen);
    DeleteObject(pen);
    brush=CreateSolidBrush(GetPixel(dc, 13, 3));
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=FRect.Left+4;
    FRect.Top=FRect.Top+4;
    FRect.Right=FRect.Right-4;
    FRect.Bottom=FRect.Bottom-4;
    FillRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);    
  }
  ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::WMSize(TWMSize &Message)
{
  TRadioButton::Dispatch(&Message);
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::WMPaint(TWMPaint &Message)
{
  TRadioButton::Dispatch(&Message);
  if(FRadioButtonFlat)
    DrawRadioButtonFlat();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::CMMouseEnter(TMessage &Message)
{
  TRadioButton::Dispatch(&Message);
  if(FRadioButtonFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
      Color=(TColor)ColorToRGB(FFocusedColor);
    else
      Color=(TColor)ColorToRGB(FHoverColor);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::CMMouseLeave(TMessage &Message)
{
  TRadioButton::Dispatch(&Message);
  if(FRadioButtonFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
      Color=(TColor)ColorToRGB(FFocusedColor);
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::WMSetFocus(TWMSetFocus &Message)
{
  TRadioButton::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::WMKillFocus(TWMSetFocus &Message)
{
  TRadioButton::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::CNCommand(TWMCommand &Message)
{
  TRadioButton::Dispatch(&Message);
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::CMCtl3DChanged(TMessage &Message)
{
  TRadioButton::Dispatch(&Message);
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZRadioButton::SetChecked(bool value)
{
  TRadioButton::SetChecked(value);
  Invalidate();
}
//---------------------------------------------------------------------------
