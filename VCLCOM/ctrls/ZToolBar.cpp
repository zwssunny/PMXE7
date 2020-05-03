//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZToolBar.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZToolBar *)
{
  new TZToolBar(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZToolBar::TZToolBar(TComponent* Owner)
  : TToolBar(Owner)
{
}
//---------------------------------------------------------------------------
namespace Ztoolbar
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZToolBar)};
     RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------
 