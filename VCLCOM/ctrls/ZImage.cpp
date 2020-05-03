//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZImage.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZImage *)
{
  new TZImage(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZImage::TZImage(TComponent* Owner)
  : TImage(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zimage
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZImage)};
	 RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZImage::CMMouseEnter(TMessage &Message)
{
   if(FOnEnter)
      FOnEnter(this);
}
void __fastcall TZImage::CMMouseLeave(TMessage &Message)
{
   if(FOnExit)
      FOnExit(this);
}
