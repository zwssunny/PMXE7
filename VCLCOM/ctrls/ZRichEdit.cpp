//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZRichEdit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZRichEdit *)
{
  new TZRichEdit(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZRichEdit::TZRichEdit(TComponent* Owner)
  : TRichEdit(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zrichedit
{
  void __fastcall PACKAGE Register()
  {
	 TComponentClass classes[1] = {__classid(TZRichEdit)};
     RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------
