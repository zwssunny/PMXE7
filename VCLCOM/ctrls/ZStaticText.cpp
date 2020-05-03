//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZStaticText.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZStaticText *)
{
        new TZStaticText(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZStaticText::TZStaticText(TComponent* Owner)
        : TStaticText(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zstatictext
{
        void __fastcall PACKAGE Register()
        {
				 TComponentClass classes[1] = {__classid(TZStaticText)};
                 RegisterComponents("ZStandard", classes, 0);
        }
}
//---------------------------------------------------------------------------
 