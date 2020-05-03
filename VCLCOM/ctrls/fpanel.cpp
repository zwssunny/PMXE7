//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fpanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TFloatPanel *)
{
  new TFloatPanel(NULL);
}
//---------------------------------------------------------------------------
__fastcall TFloatPanel::TFloatPanel(TComponent* Owner)
  : TCustomControl(Owner)
{
  ControlStyle << csAcceptsControls << csCaptureMouse << csClickEvents
    << csSetCaption << csOpaque << csDoubleClicks << csReplicatable;
  Width = 185;
  Height = 41;
  FAlignment = taCenter;
	FBorderWidth = 8;
  Color = clWhite;
}
//---------------------------------------------------------------------------
namespace Fpanel
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TFloatPanel)};
     RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall  TFloatPanel::CreateParams(Controls::TCreateParams &Params)
{
  TCustomControl::CreateParams(Params);

  long BorderStyle = 0;
  Params.Style = Params.Style | BorderStyle;
  Params.WindowClass.style = Params.WindowClass.style & (!(CS_HREDRAW | CS_VREDRAW));
}

void __fastcall TFloatPanel::Resize()
{
  if (FOnResize) FOnResize(this);
}


void __fastcall TFloatPanel::WMWindowPosChanged(TWMWindowPosChanged &Message)
{
  TCustomControl::Dispatch(&Message);

  Invalidate();
}

void __fastcall TFloatPanel::AlignControls(Controls::TControl* AControl, TRect &Rect)
{
  InflateRect(&Rect, -1, -1);
  Rect.Right -= 5;
  Rect.Bottom -= 5;
  //InflateRect(&RECT(Rect), -FBorderWidth, -FBorderWidth);
  Rect.Left += FBorderWidth;
  Rect.Top += FBorderWidth;
  Rect.Right -= FBorderWidth;
  Rect.Bottom -= FBorderWidth;
  TCustomControl::AlignControls(AControl, Rect);
}

void __fastcall TFloatPanel::ShadeLine(TRect Rect, TColor Color)
{
  TPoint Points[3];

  Canvas->Pen->Color = Color;
  Points[0].x = Rect.Left;
  Points[0].y = Rect.Bottom;
  Points[1].x = Rect.Right;
  Points[1].y = Rect.Bottom;
  Points[2].x = Rect.Right;
  Points[2].y = Rect.Top;
  Canvas->Polyline(Points,2);

}

void __fastcall TFloatPanel::Paint()
{
  TRect Rect;

  Rect = GetClientRect();
  Canvas->Brush->Color = Color;
  Canvas->FillRect(Rect);

  Rect.Right -= 5;
  Rect.Bottom -= 5;
  Canvas->Brush->Color = clBlack;
  Canvas->FrameRect(Rect);

/*  TRect CornerRect;
  Canvas->Brush->Color = clInfoBk;

  CornerRect.Left = Rect.Left;
  CornerRect.Right = CornerRect.Left+4;
  CornerRect.Top = Rect.Bottom;
  CornerRect.Bottom = Rect.Bottom+5;
  Canvas->FillRect(CornerRect);

  CornerRect.Left = Rect.Right;
  CornerRect.Top = Rect.Top;
  CornerRect.Right = Rect.Right+5;
  CornerRect.Bottom = Rect.Top+4;
  Canvas->FillRect(CornerRect);*/

  //Rect.Left += 4;
  //Rect.Top += 3;
  ShadeLine(Rect, clDkGray);

  const TColor ShadeColors[] =
  	{ clGray, clGray, clLtGray, clLtGray };
  for (int i=0; i<4; i++)
  {
  	Rect.Right ++;
    Rect.Bottom ++;
  	ShadeLine(Rect, ShadeColors[i]);
  }

  /*Rect.Right ++; Rect.Bottom ++;
  ShadeLine(Rect, clGray);

  Rect.Right ++; Rect.Bottom ++;
  ShadeLine(Rect, clLtGray);
  Rect.Right ++; Rect.Bottom ++;
  ShadeLine(Rect, clLtGray);

  Rect.Right ++; Rect.Bottom ++;
  ShadeLine(Rect, clYellow);
  Rect.Right ++; Rect.Bottom ++;
  ShadeLine(Rect, clInfoBk);*/
}

void __fastcall TFloatPanel::SetAlignment(TAlignment Value)
{
  FAlignment = Value;
  Invalidate();
}

void __fastcall TFloatPanel::SetBorderWidth(TBorderWidth Value)
{
  FBorderWidth = Value;
  Realign();
  Invalidate();
}

//---------------------------------------------------------------------------
 