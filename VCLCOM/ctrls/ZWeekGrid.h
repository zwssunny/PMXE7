//---------------------------------------------------------------------------

#ifndef ZWeekGridH
#define ZWeekGridH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "ZGrid.h"
#include "ZGrids.hpp"
//---------------------------------------------------------------------------
class PACKAGE TZWeekGrid : public TZGrid
{
private:
		TDate FStartDate;
		TDate FEndDate;
		int FBeginColIndex;
        int FDayGridWidth;
        void __fastcall SetStartDate(TDate value);
        void __fastcall SetEndDate(TDate value);
        void __fastcall SetBeginColIndex(int value);
        void __fastcall MakeGridCalendar();
        void __fastcall SetDayGridWidth(int value);
protected:
public:
        __fastcall TZWeekGrid(TComponent* Owner);
		__fastcall ~TZWeekGrid();
        TDate __fastcall DayByColIndex(int ColIndex);
        int __fastcall ColIndexByDay(TDate date);
        void __fastcall SetGridStartEndDate(TDate startDate, TDate endDate);
__published:
        __property TDate StartDate  = { read=FStartDate, write=SetStartDate };
        __property TDate EndDate  = { read=FEndDate, write=SetEndDate };
        __property int BeginColIndex  = { read=FBeginColIndex, write=SetBeginColIndex};
        __property int DayGridWidth  = { read=FDayGridWidth, write=SetDayGridWidth };
};
//---------------------------------------------------------------------------
#endif

