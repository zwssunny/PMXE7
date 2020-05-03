//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZGroupBox.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZGroupBox *)
{
  new TZGroupBox(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZGroupBox::TZGroupBox(TComponent* Owner)
  : TGroupBox(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zgroupbox
{
  void __fastcall PACKAGE Register()
  {
	 TComponentClass classes[1] = {__classid(TZGroupBox)};
	 RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
 