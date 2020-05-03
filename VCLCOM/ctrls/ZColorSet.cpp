//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZColorSet.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
namespace Zcolorset
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TZColorSet)};
                 RegisterComponents("ZAdditional", classes, 0);
        }
}
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(TZColorSet *)
{
        new TZColorSet(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZColorSet::TZColorSet(TComponent* Owner)
        : TWinControl(Owner)
{
       Width = 50;
       Height = 16;
       Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TZColorSet::Click(void)
{
    if(!Enabled)
       return;
       
       TColorDialog* cd;
       try{
           cd = new TColorDialog(this);
           cd->Color = Color;
           if(cd->Execute())
           {
              Color = cd->Color;
              if(FColorChange)
                 FColorChange(this);
           }
       }__finally
       {
           delete cd;
       }
}
void __fastcall TZColorSet::WMPaint(Messages::TWMPaint &Message)
{
   ControlState << csCustomPaint;
   TWinControl::Dispatch(&Message);
   ControlState >> csCustomPaint;
}
void __fastcall TZColorSet::PaintWindow(HDC DC)
{
   HPEN Pen = CreatePen(PS_SOLID, 2, ColorToRGB(Color) ^0xffffffff);
   HGDIOBJ oldPen = SelectObject(DC, Pen);
   MoveToEx(DC, 0, 0, NULL);
   LineTo(DC, Width, 0);
   LineTo(DC, Width, Height);
   LineTo(DC, 0, Height);
   LineTo(DC, 0, 0);
   SelectObject(DC, oldPen);
   DeleteObject(Pen);
}

