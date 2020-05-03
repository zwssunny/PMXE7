//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZWeekGrid.h"
#pragma link "ZGrid"
#pragma link "ZGrids"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
String days[7] = {"日", "一", "二", "三", "四", "五", "六" };
static inline void ValidCtrCheck(TZWeekGrid *)
{
        new TZWeekGrid(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZWeekGrid::TZWeekGrid(TComponent* Owner)
		: TZGrid(Owner)
{
   if(ComponentState.Contains(csDesigning))
   {
    FixedCols=0;
    FBeginColIndex=-1;
    FDayGridWidth=19;
    FStartDate=Date()-DayOfWeek(Date())+1;
    FEndDate=Date()+(7-DayOfWeek(Date()));
    MakeGridCalendar();
   }
}
//---------------------------------------------------------------------------
namespace Zweekgrid
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TZWeekGrid)};
				 RegisterComponents("ZAdditional", classes, 0);
        }
}
//---------------------------------------------------------------------------


void __fastcall TZWeekGrid::SetStartDate(TDate value)
{
        if(FStartDate != value) {
           FStartDate=value-DayOfWeek(value)+1;
           if(FStartDate>FEndDate)
               EndDate=FStartDate+1;
           else
               MakeGridCalendar();
        }
}

void __fastcall TZWeekGrid::SetEndDate(TDate value)
{
        if(FEndDate != value) {
           FEndDate=value+(7-DayOfWeek(value));
           if(FEndDate<FStartDate)
               StartDate=FEndDate-1;
           else
               MakeGridCalendar();
        }
}

void __fastcall TZWeekGrid::SetBeginColIndex(int value)
{
        if(FBeginColIndex != value) {
          if(FBeginColIndex>value)
          {
             if(value<0)
                  FBeginColIndex = -1;
             else
                  FBeginColIndex = value;
          }
          else
             FBeginColIndex = value;
          MakeGridCalendar();
        }
}

void __fastcall TZWeekGrid::MakeGridCalendar()
{

  if(FDayGridWidth==0||FBeginColIndex<0)
     return;
     BeginUpdate();
   try
   {
	ColCount=FBeginColIndex+(int(FEndDate)-int(FStartDate)+1);
    if(RowCount<2)
	   RowCount=2;
    if(FixedRows!=2)
       FixedRows=2;
    for(int j=0;j<FBeginColIndex;j++)
    {
       Columns->Items[j]->Merged=true;
       Columns->Items[j]->RowMergeOrder=0;
       Columns->Items[j]->RowMergeCount=2;
       Columns->Items[j]->ColMergeOrder=j;
       Columns->Items[j]->ColMergeCount=1;
       Cells[j][0]=Columns->Items[j]->TitleString;
    }
    TDate ColDate;
    String DateString="";
    int MergeOrder=0;
    for(int i=FBeginColIndex;i<ColCount;i++)
      {
        ColDate=StartDate+(i-FBeginColIndex);
		Cells[i][1]=days[DayOfWeek(ColDate)-1];
        ColWidths[i]=FDayGridWidth;
        int l=(i-FBeginColIndex)%7;
        if(l==0)
        {
          MergeOrder=i;
          Columns->Items[i]->TitleString="";
          DateString=ColDate.FormatString("YYYY\"年\"MM\"月\"DD\"日\"");
		}
        Cells[i][0]=DateString;
        Columns->Items[i]->Merged=true;
        Columns->Items[i]->RowMergeOrder=0;
        Columns->Items[i]->RowMergeCount=1;
        Columns->Items[i]->ColMergeOrder=MergeOrder;
        Columns->Items[i]->ColMergeCount=7;
      }
   }
   __finally
   {
   EndUpdate();
   }
}

void __fastcall TZWeekGrid::SetDayGridWidth(int value)
{
        if(FDayGridWidth != value) {
           if(value<19)
                FDayGridWidth = 19;
           else
                FDayGridWidth = value;
           MakeGridCalendar();
        }
}

TDate __fastcall TZWeekGrid::DayByColIndex(int ColIndex)
{
     if(ColIndex<FBeginColIndex)
        throw Exception("列号不能小于开始日历列");
     else
     {
       return FStartDate+(ColIndex-FBeginColIndex);
     }
}

int __fastcall TZWeekGrid::ColIndexByDay(TDate date)
{
     if(date<FStartDate||date>FEndDate)
       throw Exception("日期不在日历范围");
     else
     {
        return (date-FStartDate)+FBeginColIndex;
     }
}

void __fastcall TZWeekGrid::SetGridStartEndDate(TDate startDate, TDate endDate)
{
           if(startDate>endDate)
              throw Exception("开始日期不能大于结束日期");
           TDate dtStart,dtEnd;
           dtStart=startDate-DayOfWeek(startDate)+1;
           dtEnd=endDate+(7-DayOfWeek(endDate));
           if(dtStart!=FStartDate||dtEnd!=FEndDate)
           {
             FStartDate=dtStart;
             FEndDate=dtEnd;
             MakeGridCalendar();
           }
}

__fastcall TZWeekGrid::~TZWeekGrid()
{

}
