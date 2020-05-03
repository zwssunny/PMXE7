//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZTabControl.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZTabControl *)
{
  new TZTabControl(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZTabControl::TZTabControl(TComponent* Owner)
  : TTabControl(Owner)
{
}
//---------------------------------------------------------------------------
namespace Ztabcontrol
{
  void __fastcall PACKAGE Register()
  {
	 TComponentClass classes[1] = {__classid(TZTabControl)};
     RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------
 