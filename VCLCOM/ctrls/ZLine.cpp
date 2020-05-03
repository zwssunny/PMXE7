//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZLine.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TLine *)
{
  new TLine(NULL);
}
//---------------------------------------------------------------------------
__fastcall TLine::TLine(TComponent* Owner)
  : TGraphicControl(Owner)
{
  FLineWidth=1;
  TGraphicControl::Height=1;
  TGraphicControl::Width=100;
  FColor=clBlack;
  Canvas->Pen->Color=clBlack;
  Canvas->Pen->Mode=pmNotXor;
  Canvas->Pen->Width=1;
  ButtonIsDown=false;
  FDirect=ldLeftToRight;
}
//---------------------------------------------------------------------------
namespace Zline
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TLine)};
     RegisterComponents("ZOther", classes, 0);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TLine::SetLeft(int value)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  TGraphicControl::Left=value;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
}
//---------------------------------------------------------------------------
void __fastcall TLine::SetTop(int value)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  TGraphicControl::Top=value;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
}
//---------------------------------------------------------------------------
void __fastcall TLine::SetWidth(int value)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);

  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  if(value<1)
    value=1;
  TGraphicControl::Width=value;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
}
//---------------------------------------------------------------------------
void __fastcall TLine::SetHeight(int value)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);

  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  if(value<1)
    value=1;
  TGraphicControl::Height=value;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
}
//---------------------------------------------------------------------------
int __fastcall TLine::GetLeft()
{
  return TGraphicControl::Left;
}
//---------------------------------------------------------------------------
int __fastcall TLine::GetTop()
{
  return TGraphicControl::Top;
}
//---------------------------------------------------------------------------
int __fastcall TLine::GetWidth()
{
  return TGraphicControl::Width;
}
//---------------------------------------------------------------------------
int __fastcall TLine::GetHeight()
{
  return TGraphicControl::Height;
}
//---------------------------------------------------------------------------
void __fastcall TLine::SetLineWidth(int value)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);

  Canvas->Pen->Mode=pmNotXor;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);

  if(value<1)
    value=1;
  FLineWidth=value;
  Canvas->Pen->Width=value;
  Canvas->Pen->Mode=pmCopy;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Mode=pmNotXor;
}
//---------------------------------------------------------------------------
void __fastcall TLine::SetColor(TColor value)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);

  Canvas->Pen->Mode=pmNotXor;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Color=(TColor)ColorToRGB(value);
  Canvas->Pen->Mode=pmCopy;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Mode=pmNotXor;
}
//---------------------------------------------------------------------------
void __fastcall TLine::WMPaint(TWMPaint &Message)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);

  TGraphicControl::Dispatch(&Message);
  Canvas->Pen->Mode=pmNotXor;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Mode=pmCopy;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Mode=pmNotXor;
}
//---------------------------------------------------------------------------
void __fastcall TLine::WMSize(TWMSize &Message)
{
  TPoint pt;
  if(FDirect==ldLeftToRight)
    pt=TPoint(0,0);
  else
    pt=TPoint(Width-1,0);

  TGraphicControl::Dispatch(&Message);
  Canvas->Pen->Mode=pmNotXor;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Mode=pmCopy;
  Canvas->PenPos=pt;
  if(FDirect==ldLeftToRight)
    Canvas->LineTo(Width-1,Height-1);
  else
    Canvas->LineTo(0,Height-1);
  Canvas->Pen->Mode=pmNotXor;
}
//----------------------------------------------------------------------

void __fastcall TLine::SetDirect(TDir value)
{
  FDirect=value;
  TGraphicControl::Refresh();
}

