//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZStatusBar.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZStatusBar *)
{
  new TZStatusBar(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZStatusBar::TZStatusBar(TComponent* Owner)
  : TStatusBar(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zstatusbar
{
  void __fastcall PACKAGE Register()
  {
	 TComponentClass classes[1] = {__classid(TZStatusBar)};
     RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------
 