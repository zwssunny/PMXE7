//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZSpeedButton.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZSpeedButton *)
{
  new TZSpeedButton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZSpeedButton::TZSpeedButton(TComponent* Owner)
  : TSpeedButton(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zspeedbutton
{
  void __fastcall PACKAGE Register()
  {
	 TComponentClass classes[1] = {__classid(TZSpeedButton)};
     RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------
 