//---------------------------------------------------------------------------

#include <vcl.h>
#include "vclComFunc.h"
#pragma hdrstop

#include "ZPageControl.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZPageControl *)
{
  new TZPageControl(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZPageControl::TZPageControl(TComponent* Owner)
  : TPageControl(Owner)
{
   FActiveFont = new TFont();
}
//---------------------------------------------------------------------------
__fastcall TZPageControl::~TZPageControl()
{
   delete FActiveFont;
}
//---------------------------------------------------------------------------
namespace Zpagecontrol
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZPageControl)};
     RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZPageControl::SetPageControlFlat(bool Value)
{
  FPageControlFlat = Value;
  if(FPageControlFlat)
  {
     Style = tsFlatButtons;
     OwnerDraw = true;
  }else
     OwnerDraw = false;
}
//---------------------------------------------------------------------------
void __fastcall TZPageControl::SetPageColor(TColor Value)
{
   FPageColor = Value;
   Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZPageControl::SetActivePageColor(TColor Value)
{
   FActivePageColor = Value;
   Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZPageControl::SetActiveFont(TFont* Value)
{
  FActiveFont->Assign(Value);
}

