//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZButton.h"
#include "vclComFunc.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZButton *)
{
  new TZButton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZButton::TZButton(TComponent* Owner)
  : TButton(Owner)
{
  FBorderColor=crBorderColor;
  FFocusedColor=crFocusedColor;
  FHoverColor=crFocusedColor;
  FButtonFlat=false;
  FMouseDown = false;
}
//---------------------------------------------------------------------------
namespace Zbutton
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZButton)};
     RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::CMMouseEnter(TMessage &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
      Color=FFocusedColor;
    else
      Color=FHoverColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::CMMouseLeave(TMessage &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
      Color=FFocusedColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::WMSetFocus(TWMSetFocus &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
  {
    FIsFocused=true;
    Color=FFocusedColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::WMKillFocus(TWMSetFocus &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
  {
    FIsFocused=false;
    if(FIsHovered)
      Color=FHoverColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::WMPaint(TWMPaint &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
    DrawButtonFlat();
}
//---------------------------------------------------------------------------
void __fastcall TZButton::WMLButtonDblClk(TWMMouse &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
    DrawButtonFlat();
}
//---------------------------------------------------------------------------
void __fastcall TZButton::WMMouseDown(TMessage &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
  {
      FMouseDown = true;
      SetCapture(Handle);
      Repaint();
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::WMMouseUp(TMessage &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
  {
       ReleaseCapture();
       if(FMouseDown)
       {
          POINT p;
          GetCursorPos(&p);
          if(p.x > ClientOrigin.x && p.x < ClientOrigin.x + Width
             && p.y > ClientOrigin.y && p.y < ClientOrigin.y + Height && OnClick)
             OnClick(this);
       }
       FMouseDown = false;
       Repaint();
  }
}
//---------------------------------------------------------------------------
void __fastcall TZButton::CNDrawItem(TWMDrawItem &Message)
{
  TButton::Dispatch(&Message);
  if(FButtonFlat)
    DrawButtonFlat();
}
//---------------------------------------------------------------------------
void __fastcall TZButton::DrawButtonFlat()
{
  if(!FButtonFlat)
    return;
  HDC dc = GetDC(Handle);
  HDC dc1;
  HBRUSH brush,oldbrush;
  HPEN pen,OldPen;
  TRect FRect;
  if(FIsFocused)
  {
    brush=CreateSolidBrush(ColorToRGB(FFocusedColor));
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=ClientRect.Left;
    FRect.Top=ClientRect.Top;
    FRect.Right=ClientRect.Right;
    FRect.Bottom=ClientRect.Bottom;
    FillRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);

    brush=CreateSolidBrush(ColorToRGB(FBorderColor));
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=ClientRect.Left;
    FRect.Top=ClientRect.Top;
    FRect.Right=ClientRect.Right;
    FRect.Bottom=ClientRect.Bottom;
    FrameRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
  }else if(FIsHovered)
  {
    brush=CreateSolidBrush(ColorToRGB(FHoverColor));
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=ClientRect.Left;
    FRect.Top=ClientRect.Top;
    FRect.Right=ClientRect.Right;
    FRect.Bottom=ClientRect.Bottom;
    FillRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);

    pen = CreatePen(PS_SOLID	, 1, clWhite);
	OldPen = (HPEN)SelectObject(dc, pen);
    MoveToEx(dc, ClientRect.Left, ClientRect.Top, NULL);
    LineTo(dc, ClientRect.Right, ClientRect.Top);
    MoveToEx(dc, ClientRect.Left, ClientRect.Top, NULL);
    LineTo(dc, ClientRect.Left, ClientRect.Bottom);
    SelectObject(dc, OldPen);
    DeleteObject(pen);
    pen = CreatePen(PS_SOLID	, 1, clBtnShadow);
	OldPen = (HPEN)SelectObject(dc, pen);
    MoveToEx(dc, ClientRect.Right, ClientRect.Top, NULL);
    LineTo(dc, ClientRect.Right, ClientRect.Bottom);
    MoveToEx(dc, ClientRect.Left+1, ClientRect.Bottom, NULL);
    LineTo(dc, ClientRect.Right, ClientRect.Bottom);
    SelectObject(dc, OldPen);
    DeleteObject(pen);
  }
  else
  {
    dc1=GetDC(Parent->Handle);
    brush=CreateSolidBrush(GetPixel(dc1, 1, 1));
    ReleaseDC(Handle, dc1);
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=ClientRect.Left;
    FRect.Top=ClientRect.Top;
    FRect.Right=ClientRect.Right;
    FRect.Bottom=ClientRect.Bottom;
    FillRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);

    brush=CreateSolidBrush(ColorToRGB(FBorderColor));
	oldbrush = (HBRUSH)SelectObject(dc,brush);
    FRect.Left=ClientRect.Left;
    FRect.Top=ClientRect.Top;
    FRect.Right=ClientRect.Right;
    FRect.Bottom=ClientRect.Bottom;
    FrameRect(dc,&FRect,brush);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
  }
  SetBkMode(dc, TRANSPARENT);

  HGDIOBJ oldfont;
  //createfont
  HFONT hFont;
  hFont = Vclcomfunc::CreateFontByTFont(Font);
  oldfont = SelectObject(dc, hFont);
  SetBkMode(dc, TRANSPARENT);
  if(FMouseDown)
     SetTextColor(dc, ColorToRGB(Font->Color)|0x007f7f7f);
  else
     SetTextColor(dc, ColorToRGB(Font->Color));
  DrawText(dc, Caption.c_str(),Caption.Length(), &ClientRect,
		DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  SelectObject(dc, oldfont);
  DeleteObject(hFont);

  if(FMouseDown)
  {//»­°¼Ïß
      TColor DrawColor = (TColor)(ColorToRGB(FBorderColor) ^ 0x00f0f0f0);
      //left top
      pen=CreatePen(PS_SOLID, 2, DrawColor);
	  OldPen = (HPEN)SelectObject(dc,pen);
      MoveToEx(dc, ClientRect.Right, ClientRect.Top, NULL);
      LineTo(dc, ClientRect.Left, ClientRect.Top);
      LineTo(dc, ClientRect.Left, ClientRect.Bottom);
      SelectObject(dc, OldPen);
      DeleteObject(pen);
      //right bottom
      DrawColor = (TColor)ColorToRGB((TColor)(FBorderColor | 0x00f0f0f0));
      pen=CreatePen(PS_SOLID, 2, DrawColor);
      OldPen = (HPEN)SelectObject(dc,pen);
      MoveToEx(dc, ClientRect.Right, ClientRect.Top, NULL);
      LineTo(dc, ClientRect.Right, ClientRect.Bottom);
      LineTo(dc, ClientRect.Left, ClientRect.Bottom);
      SelectObject(dc, OldPen);
      DeleteObject(pen);
  }

  ReleaseDC(Handle, dc);
}

//---------------------------------------------------------------------------
void __fastcall TZButton::SetBorderColor(TColor value)
{
  FBorderColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZButton::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZButton::SetHoverColor(TColor value)
{
  FHoverColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZButton::SetButtonFlat(bool value)
{
  FButtonFlat=value;
  if(FButtonFlat)
  {
    TControl::ParentColor=true;
    Perform(CM_PARENTCOLORCHANGED, 0, 0);
  }
  this->Repaint();
}
//--------------------------------------------------------------------------- 