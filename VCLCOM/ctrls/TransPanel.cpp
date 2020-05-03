//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "TransPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TTransPanel *)
{
        new TTransPanel(NULL);
}
//---------------------------------------------------------------------------
__fastcall TTransPanel::TTransPanel(TComponent* Owner)
        : TCustomPanel(Owner)
{
}
//---------------------------------------------------------------------------
namespace Transpanel
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TTransPanel)};
                 RegisterComponents("ZOther", classes, 0);
        }
}
//---------------------------------------------------------------------------


void __fastcall TTransPanel::SetTransParent(bool value)
{
        if(FTransParent != value) {
                FTransParent = value;
                Invalidate();
        }
}

void __fastcall TTransPanel::Paint()
{
        if(FTransParent)
        {
          //»­±³¾°
//          Screen->HasParent()£»
          Canvas->Font = Font;
          Canvas->Brush->Color = Color;
          Canvas->Pen->Style=psDash;
          Canvas->Pen->Width=2;
//          TRect TheRect = Rect(0, 0, Width, Height);
          Canvas->FrameRect(ClientRect);
        }
        else
        TCustomPanel::Paint();
}