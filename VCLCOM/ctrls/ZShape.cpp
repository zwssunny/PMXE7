//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZShape.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZShape *)
{
  new TZShape(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZShape::TZShape(TComponent* Owner)
  : TShape(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zshape
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZShape)};
	 RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------
 