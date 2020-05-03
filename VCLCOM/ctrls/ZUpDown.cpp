//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZUpDown.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZUpDown *)
{
        new TZUpDown(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZUpDown::TZUpDown(TComponent* Owner)
        : TUpDown(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zupdown
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TZUpDown)};
                 RegisterComponents("ZWin32", classes, 0);
        }
}
//---------------------------------------------------------------------------
 