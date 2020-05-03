//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZMonthCalendar.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZMonthCalendar *)
{
        new TZMonthCalendar(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZMonthCalendar::TZMonthCalendar(TComponent* Owner)
        : TMonthCalendar(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zmonthcalendar
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TZMonthCalendar)};
				 RegisterComponents("ZStandard", classes, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TZMonthCalendar::WMNotify(TWMNotify &Message)
{
   TMonthCalendar::Dispatch(&Message);
   switch(Message.NMHdr->code)
   {
      case MCN_SELCHANGE:
         if(FOnSelChange)
            FOnSelChange(this);
         break;
      case MCN_SELECT:
         if(FOnSelect)
            FOnSelect(this);
         break;
   }
}
