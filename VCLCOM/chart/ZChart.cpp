//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZChart.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZChart *)
{
        new TZChart(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZChart::TZChart(TComponent* Owner)
        : TChart(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zchart
{
        void __fastcall PACKAGE Register()
        {
				 TComponentClass classes[1] = {__classid(TZChart)};
				 RegisterComponents("ZChart", classes, 0);
        }
}
//---------------------------------------------------------------------------
