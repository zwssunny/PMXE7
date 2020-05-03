//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZBitBtn.h"
#include "vclComFunc.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZBitBtn *)
{
  new TZBitBtn(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZBitBtn::TZBitBtn(TComponent* Owner)
  : TBitBtn(Owner)
{
  FBorderColor=crBorderColor;
  FFocusedColor=crFocusedColor;
  FHoverColor=crFocusedColor;
  FBitBtnFlat = false;
  FMouseDown = false;
}
//---------------------------------------------------------------------------
__fastcall TZBitBtn::~TZBitBtn()
{
}
//---------------------------------------------------------------------------
namespace Zbitbtn
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZBitBtn)};
	 RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::CMMouseEnter(TMessage &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
    FIsHovered=true;
    if(Focused())
       Color=FFocusedColor;
    else
       Color=FHoverColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::CMMouseLeave(TMessage &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
    FIsHovered=false;
    if(Focused())
       Color=FFocusedColor;
    else
       ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::WMSetFocus(TWMSetFocus &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
	Color=FFocusedColor;
	Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::WMKillFocus(TWMSetFocus &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
    if(FIsHovered)
      Color=FHoverColor;
    else
      ParentColor=true;
	Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::WMPaint(TWMPaint &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
	 DrawBitBtnFlat();
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::WMMouseDown(TMessage &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
	  Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::WMMouseUp(TMessage &Message)
{
  TBitBtn::Dispatch(&Message);
  if(FBitBtnFlat)
  {
	Invalidate();
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::DrawBitBtnFlat()
{
  if(!FBitBtnFlat)
    return;
  HDC dc = GetDC(Handle);
  HDC dc1;
  HBRUSH brush,oldbrush;
  HPEN pen,OldPen;
  TRect FRect;

  HFONT hFont;
  HGDIOBJ oldfont;
  hFont = Vclcomfunc::CreateFontByTFont(Font);
  oldfont = SelectObject(dc, hFont);
  SetBkMode(dc, TRANSPARENT);
  if(FMouseDown)
     SetTextColor(dc, ColorToRGB(Font->Color)|0x007f7f7f);
  else
     SetTextColor(dc, ColorToRGB(Font->Color));

  if(Focused())
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
    pen = CreatePen(PS_SOLID	, 1, ColorToRGB(clBtnShadow));
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
	brush=CreateSolidBrush(ColorToRGB(Color));

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
  RECT r;
  r.top = 0;
  r.left = 0;
  r.right = 1000;
  r.bottom = 1000;
  DrawText(dc, Caption.c_str(), Caption.Length(), &r, DT_CALCRECT);
  int TextWidth = r.right - r.left;
  int GraphLeft;
  int TextLeft;
  int GraphTop = (Height - Glyph->Height) / 2;
  GraphLeft = (Width - Glyph->Width/NumGlyphs - TextWidth - Spacing) / 2;
  TextLeft = GraphLeft + Glyph->Width/NumGlyphs + Spacing;

  int DrawGlyphIndex;
  switch(NumGlyphs)
  {
     case 4:
     case 3:
        if(FMouseDown && Enabled)
        {
           DrawGlyphIndex = 2;
           break;
        }
     case 2:
        if(!Enabled)
        {
           DrawGlyphIndex = 1;
           break;
        }
     case 1:
        DrawGlyphIndex = 0;
        break;
     case 0:
        TextLeft = GraphLeft + Glyph->Width / 2;
        DrawGlyphIndex = -1;
        break;
  }
  //Draw Picture
  if(!Glyph->Empty)
  {
  TImageList *FTmpGlyph=new TImageList(this);
  FTmpGlyph->Width=Glyph->Width / NumGlyphs;
  FTmpGlyph->Height=Glyph->Height;
  FTmpGlyph->AddMasked(Glyph,Glyph->TransparentColor);
  ImageList_DrawEx((HIMAGELIST)FTmpGlyph->Handle, DrawGlyphIndex, dc,
		 GraphLeft, GraphTop, 0, 0,clNone, clNone, ILD_TRANSPARENT);
  delete FTmpGlyph;
  }
  //draw text
  int Flags = DrawTextBiDiModeFlags(DT_SINGLELINE);
 // DrawText(Handle, PChar(Text), Length(Text), R, Flags | DT_CALCRECT);
 // TextOut(dc, TextLeft, (Height - (r.bottom - r.top)) / 2, dstr.c_str(), dstr.Length());
  FRect= ClientRect;
  FRect.left= TextLeft;
  FRect.top = (Height - (r.bottom - r.top)) / 2;
  DrawText(dc, Caption.c_str(), Caption.Length(),&FRect,Flags);
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
void __fastcall TZBitBtn::SetBorderColor(TColor value)
{
  FBorderColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::SetHoverColor(TColor value)
{
  FHoverColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZBitBtn::SetBitBtnFlat(bool value)
{
  FBitBtnFlat=value;
  if(FBitBtnFlat)
  {
    TControl::ParentColor=true;
    Perform(CM_PARENTCOLORCHANGED, 0, 0);
  }
  Invalidate();
}
//---------------------------------------------------------------------------
