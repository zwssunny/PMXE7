//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZListBox.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZListBox *)
{
  new TZListBox(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZListBox::TZListBox(TComponent* Owner)
  : TListBox(Owner)
{
  FBorderColor=crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  FListFlat=false;
}
//---------------------------------------------------------------------------
namespace Zlistbox
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZListBox)};
	 RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::CMMouseEnter(TMessage &Message)
{
  TListBox::Dispatch(&Message);
  if(FListFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
      Color=FFocusedColor;
    else
      Color=FHoverColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::CMMouseLeave(TMessage &Message)
{
  TListBox::Dispatch(&Message);
  if(FListFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
      Color=FFocusedColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::WMSetFocus(TWMSetFocus &Message)
{
  TListBox::Dispatch(&Message);
  if(FListFlat)
  {
    FIsFocused=true;
    Color=FFocusedColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::WMKillFocus(TWMSetFocus &Message)
{
  TListBox::Dispatch(&Message);
  if(FListFlat)
  {
    FIsFocused=false;
    if(FIsHovered)
      Color=FHoverColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::WMPaint(TWMPaint &Message)
{
  TListBox::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::WMSize(TWMSize &Message)
{
  TListBox::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::DrawListFlat()
{
  if(!FIsHovered && !FIsFocused)
    ParentColor=true;
  HBRUSH brush;
  TRect FRect;
  HDC dc = GetDC(Handle);
  brush=CreateSolidBrush(FBorderColor);
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FRect=ClientRect;
  FRect.Left = 0;
  FRect.Top = 0;
  FRect.Right = Width;
  FRect.Bottom = Height;
  FrameRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);
  ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::SetBorderColor(TColor value)
{
  FBorderColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
 this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::SetHoverColor(TColor value)
{
  FHoverColor=value;
this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::SetListFlat(bool value)
{
  FListFlat=value;
  if(FListFlat)
  {
    Ctl3D=false;
    BorderStyle = bsSingle;
  }
this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZListBox::WMNcPaint(TMessage &Message)
{
   TListBox::Dispatch(&Message);
   if(FListFlat)
   {
      HDC hdc;
      HBRUSH brush;
      hdc = GetWindowDC(Handle);
      brush = CreateSolidBrush(FBorderColor);
	  HBRUSH oldbrush = (HBRUSH)SelectObject(hdc,brush);
      TRect R;
      GetWindowRect(Handle, &R);
      OffsetRect(&R, -R.Left, -R.Top);
      FrameRect(hdc, &R, brush);
      SelectObject(hdc, oldbrush);
      DeleteObject(brush);
      ReleaseDC(Handle, hdc);
      Message.Result = 1;
   }
}

