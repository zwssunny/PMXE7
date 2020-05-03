//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZCheckBox.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZCheckBox *)
{
  new TZCheckBox(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZCheckBox::TZCheckBox(TComponent* Owner)
  : TCheckBox(Owner)
{
  FBorderColor=crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  FCheckBoxFlat=false;
}
//---------------------------------------------------------------------------
namespace Zcheckbox
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZCheckBox)};
     RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::SetBorderColor(TColor value)
{
  FBorderColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::SetHoverColor(TColor value)
{
  FHoverColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::DrawFlatCheckBox(TRect &FRect)
{
  if(!FCheckBoxFlat)
    return;
  if(!FIsHovered)
    ParentColor=true;
  HDC dc = GetDC(Handle);
  HBRUSH brush;
  brush = CreateSolidBrush(GetPixel(dc, 13, 3));
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FillRect(dc, &FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);
  brush=CreateSolidBrush(ColorToRGB(FBorderColor));
  oldbrush = (HBRUSH)SelectObject(dc,brush);
  FrameRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);
  HPEN pen;
  HPEN OldPen;
  if(Checked)
  {
    pen = CreatePen(PS_SOLID, 1, clBlack);
	OldPen = (HPEN)SelectObject(dc, pen);
    MoveToEx(dc, FRect.Left+2, FRect.Top+4, NULL);
    LineTo(dc, FRect.Left+6, FRect.Top+8);
    MoveToEx(dc, FRect.Left+2, FRect.Top+5, NULL);
    LineTo(dc, FRect.Left+5, FRect.Top+8);
    MoveToEx(dc, FRect.Left+2, FRect.Top+6, NULL);
    LineTo(dc, FRect.Left+5, FRect.Top+9);
    MoveToEx(dc, FRect.Left+8, FRect.Top+2, NULL);
    LineTo(dc, FRect.Left+4, FRect.Top+6);
    MoveToEx(dc, FRect.Left+8, FRect.Top+3, NULL);
    LineTo(dc, FRect.Left+4, FRect.Top+7);
    MoveToEx(dc, FRect.Left+8, FRect.Top+4, NULL);
    LineTo(dc, FRect.Left+5, FRect.Top+7);

    SelectObject(dc, OldPen);
    DeleteObject(pen);
  }
  ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::WMSize(TWMSize &Message)
{
  TCheckBox::Dispatch(&Message);
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::WMPaint(TWMPaint &Message)
{
  if(FCheckBoxFlat)
  {
    TControl::Dispatch(&Message);
    TRect ARect;
    switch(Alignment)
    {
       case taLeftJustify:
          ARect.Left = ClientRect.Right-13;
          ARect.Top = ClientRect.Height()/2-6;
          ARect.Right = ClientRect.Right;
          ARect.Bottom = ClientRect.Height()/2+7;
          break;
       case taRightJustify:
          ARect.Left = ClientRect.Left;
          ARect.Top = ClientRect.Height()/2-6;
          ARect.Right = ClientRect.Left+13;
          ARect.Bottom = ClientRect.Height()/2+7;
          break;
    }
    DrawFlatCheckBox(ARect);
  }else
  {
    TCheckBox::Dispatch(&Message);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::CMMouseEnter(TMessage &Message)
{
  TCheckBox::Dispatch(&Message);
  if(FCheckBoxFlat)
  {
    FIsHovered=true;
//    if(Focused())
//      Color=FFocusedColor;
//    else
      Color=FHoverColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::CMMouseLeave(TMessage &Message)
{
  TCheckBox::Dispatch(&Message);
  if(FCheckBoxFlat)
  {
    FIsHovered=false;
//    if(Focused())
//      Color=FFocusedColor;
//    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::WMSetFocus(TWMSetFocus &Message)
{
  TCheckBox::Dispatch(&Message);
  Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::WMKillFocus(TWMSetFocus &Message)
{
  TCheckBox::Dispatch(&Message);
  Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::CNCommand(TWMCommand &Message)
{
  TCheckBox::Dispatch(&Message);
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::CMCtl3DChanged(TMessage &Message)
{
  TCheckBox::Dispatch(&Message);
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::SetChecked(bool value)
{
  TCheckBox::SetChecked(value);
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZCheckBox::SetCheckBoxFlat(bool value)
{
  FCheckBoxFlat=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
