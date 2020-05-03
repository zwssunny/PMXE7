//---------------------------------------------------------------------------

#ifndef ZMonthCalendarH
#define ZMonthCalendarH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TZMonthCalendar : public TMonthCalendar
{
private:
    TNotifyEvent FOnSelect;
    TNotifyEvent FOnSelChange;
    void __fastcall WMNotify(TWMNotify &Message);
protected:
public:
        __fastcall TZMonthCalendar(TComponent* Owner);
BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(CN_NOTIFY, TWMNotify, WMNotify);
END_MESSAGE_MAP(TMonthCalendar);
__published:
    __property TNotifyEvent OnSelect = {read=FOnSelect, write=FOnSelect};
    __property TNotifyEvent OnSelChange = {read=FOnSelChange, write=FOnSelChange};
};
//---------------------------------------------------------------------------
#endif
