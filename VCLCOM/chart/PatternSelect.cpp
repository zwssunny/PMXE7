//---------------------------------------------------------------------------
#include "ZChartDraw.h"
#include <vcl.h>
#pragma hdrstop

#include "PatternSelect.h"
#pragma package(smart_init)
using namespace ProjectStruct;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TPatternSelect *)
{
  new TPatternSelect(NULL);
}
//---------------------------------------------------------------------------
namespace Patternselect
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TPatternSelect)};
     RegisterComponents("ZChart", classes, 0);
  }
}
//---------------------------------------------------------------------------
class TfrmPatternSelect : public TForm
{
private:
    void __fastcall FormKeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift);
protected:
    void __fastcall PaintWindow(HDC DC);
    DYNAMIC void __fastcall Click(void);
    int FHovered;
    DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
public:
    __fastcall TfrmPatternSelect(TComponent* AOwner);
    int SelectPattern;
};
__fastcall TfrmPatternSelect::TfrmPatternSelect(TComponent* AOwner)
                       : TForm(Owner, 0)
{
    ClientWidth = 100;
	ClientHeight = TPattern::Count() * 20;
    BorderStyle = bsToolWindow;
    DoubleBuffered = true;
    OnKeyDown = FormKeyDown;
    Caption = "Í¼ÑùÑ¡Ôñ";
}
void __fastcall TfrmPatternSelect::PaintWindow(HDC DC)
{
    int height = ClientHeight / TPattern::Count();
    HBITMAP Bitmap;
    HBRUSH Brush;
    HGDIOBJ oldBrush;
    SetTextColor(DC, clBlack);
    for(int i = 0; i < TPattern::Count(); i++)
    {
        Bitmap = TPattern::Pattern(i);
        Brush = CreatePatternBrush(Bitmap);
        oldBrush = SelectObject(DC, Brush);
        HPEN Pen;
        HGDIOBJ oldPen;
        if(FHovered == i)
        {
            Pen = CreatePen(PS_SOLID, 4, clBlue);
            oldPen = SelectObject(DC, Pen);
        }else
        {
            Pen = CreatePen(PS_SOLID, 1, clBlack);
            oldPen = SelectObject(DC, Pen);
        }

        Rectangle(DC, 0, height *i, ClientWidth, height * (i+1));

        SelectObject(DC, oldBrush);
        DeleteObject(Brush);
        SelectObject(DC, oldPen);
        DeleteObject(Pen);
    }
}
void __fastcall TfrmPatternSelect::Click(void)
{
    POINT point;
    GetCursorPos(&point);
    SelectPattern = (point.y - ClientOrigin.y) / (ClientHeight / TPattern::Count());
    Close();
}
void __fastcall TfrmPatternSelect::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
    int height = ClientHeight / TPattern::Count();
    int h = Y / height;
    if(h >= 0 && h < TPattern::Count() && FHovered != h)
    {
       FHovered = h;
       Invalidate();
    }
}
void __fastcall TfrmPatternSelect::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
    if(Button != mbLeft)
       Close();
}
void __fastcall TfrmPatternSelect::FormKeyDown(System::TObject* Sender, Word &Key, Classes::TShiftState Shift)
{
   switch(Key)
   {
       case VK_ESCAPE:
           Close();
           break;
       case VK_RETURN:
           SelectPattern = FHovered;
           Close();
           break;  	 
   }
}
//---------------------------------------------------------------------------
__fastcall TPatternSelect::TPatternSelect(TComponent* Owner)
  : TGraphicControl(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPatternSelect::Paint(void)
{
    HBRUSH Brush= CreatePatternBrush(TPattern::Pattern(FPattern));
    HGDIOBJ oldBrush = SelectObject(Canvas->Handle, Brush);
    HPEN    pen = CreatePen(PS_SOLID, 1, clBlack);
    HGDIOBJ oldpen = SelectObject(Canvas->Handle, pen);

    Rectangle(Canvas->Handle, 0, 0, ClientWidth, ClientHeight);

    SelectObject(Canvas->Handle, oldBrush);
    DeleteObject(Brush);
    SelectObject(Canvas->Handle, oldpen);
    DeleteObject(pen);
}
void __fastcall TPatternSelect::SetPattern(int APattern)
{
	if(APattern >= 0 && APattern < TPattern::Count())
    {
        FPattern = APattern;
        Invalidate();
    }
}
void __fastcall TPatternSelect::Click(void)
{
    TfrmPatternSelect * APatternSelect = new TfrmPatternSelect(this);
    try{
       POINT point;
       GetCursorPos(&point);
       APatternSelect->Left = point.x;
       if(point.y + APatternSelect->Height > Screen->Height-50)
          APatternSelect->Top = point.y - APatternSelect->Height;
       else
          APatternSelect->Top = point.y;
       APatternSelect->SelectPattern = FPattern;
       APatternSelect->ShowModal();
       if(FPattern != APatternSelect->SelectPattern)
       {
           FPattern = APatternSelect->SelectPattern;
           Invalidate();
           if(FOnSelect)
               FOnSelect(this, FPattern);
       }
    }__finally
    {
       delete APatternSelect;
	}
}
