//---------------------------------------------------------------------------
// 工作日历组件 实现 SDCaleView.cpp
//---------------------------------------------------------------------------
// Calendar View Component for HYWY CPM Series
// Created by Sunny Zhan,  2002-5
//---------------------------------------------------------------------------
// Last modified at: 2009-08-18
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CalendarView.h"
#include <math.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TCalendarView *)
{
        new TCalendarView(NULL);
}

class TCWPrjDataChangeLink : public TPrjDataChangeLink
{
public:
    TCalendarView* FCaleView;
    TCWPrjDataChangeLink(TCalendarView* ACaleView)
	   :TPrjDataChangeLink(ACaleView->Project) { FCaleView = ACaleView; }

    virtual void BeforeProjectChange()
    {
    }
    virtual void AfterProjectChange()
    {
    }
    virtual void BeforeTaskChange(TPrjObject*ATask){}
    virtual void AfterTaskChange(TPrjObject*ATask)
    {
    }
    virtual void BeforeTaskDelete(TPrjObject*ATask){}
    virtual void AfterTaskDelete()
    {
       FCaleView->Refresh();
    }
    virtual void AfterTaskAdd(TPrjObject*ATask)
    {
       FCaleView->Refresh();
    }
    virtual void BeforeTaskLinkChange(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkChange(TTaskLink*ATaskLink)
    {
    }
    virtual void BeforeTaskLinkDelete(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkAdd(TTaskLink*ATaskLink)
    {
    }
    virtual void BeginUpdate(){}
    virtual void EndUpdate()
    {
       FCaleView->Refresh();
    }
	virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect)
    {
       if(ATask == NULL)
       {
         FCaleView->SelectedTask = NULL;
         return;
       }
       if(ATask->GetType() == ttAbstractTask || ATask->GetType() == ttProject)
       {
         FCaleView->SelectedTask = NULL;
         return;
       }
       if(ATask && FCaleView->SelectedTask != (TTask*)ATask)
       {
         FCaleView->Date = ATask->StartDate;
         FCaleView->Refresh();
       }
       FCaleView->SelectedTask = (TTask*)ATask;
    }
};


//---------------------------------------------------------------------------
// 日期处理通用函数
bool TryEncodeDateTime(Word AYear, Word AMonth, Word ADay, Word AHour, Word AMinute, Word ASecond,
  Word AMilliSecond,TDateTime &AValue)
{
  try
  {
    TDateTime LTime;
    AValue = EncodeDate(AYear, AMonth, ADay);
    LTime =  EncodeTime(AHour, AMinute, ASecond, AMilliSecond);
    AValue = AValue + LTime;
    return true;
  }
  catch(...)
  {
    return false;
  }
}
//---------------------------------------------------------------------------
void DecodeDateTime(TDateTime AValue, Word &AYear, Word &AMonth, Word &ADay,
  Word &AHour, Word &AMinute, Word &ASecond, Word &AMilliSecond)
{
  DecodeDate(AValue, AYear, AMonth, ADay);
  DecodeTime(AValue, AHour, AMinute, ASecond, AMilliSecond);
}
//---------------------------------------------------------------------------
bool TryRecodeDateTime(TDateTime AValue, Word AYear, Word AMonth, Word ADay,
  Word AHour, Word AMinute, Word ASecond, Word AMilliSecond, TDateTime &AResult)
{
  Word LYear, LMonth, LDay, LHour, LMinute, LSecond, LMilliSecond;
  DecodeDateTime(AValue, LYear, LMonth, LDay,
                         LHour, LMinute, LSecond, LMilliSecond);
  if(AYear!=RecodeLeaveFieldAsIs) LYear = AYear;
  if(AMonth != RecodeLeaveFieldAsIs) LMonth = AMonth;
  if(ADay != RecodeLeaveFieldAsIs)LDay = ADay;
  if(AHour != RecodeLeaveFieldAsIs) LHour = AHour;
  if(AMinute != RecodeLeaveFieldAsIs) LMinute = AMinute;
  if(ASecond != RecodeLeaveFieldAsIs) LSecond = ASecond;
  if(AMilliSecond != RecodeLeaveFieldAsIs) LMilliSecond = AMilliSecond;
  return TryEncodeDateTime(LYear, LMonth, LDay,
                              LHour, LMinute, LSecond, LMilliSecond, AResult);
}
//---------------------------------------------------------------------------
TDateTime RecodeDateTime(TDateTime AValue,  Word AYear, Word AMonth, Word ADay,
  Word AHour, Word AMinute, Word ASecond, Word AMilliSecond)
{
  TDateTime AResult;
  if(!TryRecodeDateTime(AValue, AYear, AMonth, ADay,
                           AHour, AMinute, ASecond, AMilliSecond, AResult))
  {
    ShowMessage("ERROR");
    return 0;
  }
  else return AResult;
}
//---------------------------------------------------------------------------
TDateTime RecodeDate(TDateTime AValue,unsigned short AYear, unsigned short AMonth,
  unsigned short ADay)
{
  return RecodeDateTime(AValue, AYear, AMonth, ADay, RecodeLeaveFieldAsIs,
    RecodeLeaveFieldAsIs, RecodeLeaveFieldAsIs, RecodeLeaveFieldAsIs);
}
//---------------------------------------------------------------------------
TDateTime RecodeTime(TDateTime AValue,Word AHour, Word AMinute, Word ASecond,
  Word AMilliSecond)
{
  return RecodeDateTime(AValue, RecodeLeaveFieldAsIs, RecodeLeaveFieldAsIs,
    RecodeLeaveFieldAsIs, AHour, AMinute, ASecond, AMilliSecond);
}
//---------------------------------------------------------------------------
TDateTime EndOfTheDay(TDateTime AValue)
{
  return RecodeTime(AValue, 23, 59, 59, 999);
}
//---------------------------------------------------------------------------
TDateTime StartOfAMonth(unsigned short &AYear, unsigned short &AMonth)
{
  return EncodeDate(AYear, AMonth, 1);
}
//---------------------------------------------------------------------------
Word DaysInAMonth(Word AYear, Word AMonth)
{
  return MonthDays[(AMonth == 2) && IsLeapYear(AYear)][AMonth];
}
//---------------------------------------------------------------------------
TDateTime EndOfAMonth(unsigned short &AYear, unsigned short &AMonth)
{
  return EndOfTheDay(EncodeDate(AYear, AMonth, DaysInAMonth(AYear, AMonth)));
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
namespace Calendarview
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TCalendarView)};
                 RegisterComponents("ZChart", classes, 0);
        }
}
//---------------------------------------------------------------------------
//  TCalendarViewGrid  Class
//---------------------------------------------------------------------------
__fastcall TCalendarViewGrid::TCalendarViewGrid(TComponent* Owner)
        : TCustomGrid(Owner)
{
  DoubleBuffered = true;
}
__fastcall TCalendarViewGrid::~TCalendarViewGrid()
{
}
//---------------------------------------------------------------------------
TRect __fastcall TCalendarViewGrid::CellRect(int ACol, int ARow)
{
  return TCustomGrid::CellRect(ACol,ARow);
}
//画工作日-------------------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawCell(int ACol, int ARow,
                          const TRect &ARect, TGridDrawState AState)
{
  int ox,oy,x,y;
  String DayStr,CnDayStr;
  Word AYear,AMonth,ADay;
  TRect TitleRect;
  try
  {
    DecodeDate(Dates[ACol][ARow],AYear,AMonth,ADay);
    if(ADay == 1)
      DayStr = IntToStr(AMonth) + "月" + IntToStr(ADay) + "日";
    else
	  DayStr = FormatDateTime("d",Dates[ACol][ARow]);

	if(Holiday(Dates[ACol][ARow]).Trim() == "")
	{
		if(CnDayOfDateJr(Dates[ACol][ARow]).Trim() == "")
		{
			if(GetLunarHolDay(Dates[ACol][ARow]).Trim() == "")
				CnDayStr = CnDateOfDateStr(Dates[ACol][ARow]);
			else
				CnDayStr = GetLunarHolDay(Dates[ACol][ARow]);
		}
		else
			CnDayStr = CnDayOfDateJr(Dates[ACol][ARow]);
	}
	else
		CnDayStr = Holiday(Dates[ACol][ARow]);

    ox = 1;
	oy = 1;
    x = ARect.Left + ox;
    y = ARect.Top + oy;
    //PAINT BACKGROUND
    if(ACol == 0 || ACol ==6)  //周末
    {
      Canvas->Brush->Color = FWeekEndBackColor;
      Canvas->FillRect(ARect);
      Canvas->Font->Color = FTextColor;
    }
    else  //正常
    {
      Canvas->Brush->Color = FBackColor;
      Canvas->FillRect(ARect);
      Canvas->Font->Color = FTextColor;
    }
    if(Dates[ACol][ARow] == FDate)  //当前
    {
      if(FSelectedBackColor != clNone)
      {
        Canvas->Brush->Color = FSelectedBackColor;
        Canvas->FillRect(ARect);
      }
      Canvas->Font->Color = FTextColor;
    }
    //PAINT DAY TITLE
    TitleRect = TRect(ARect.Left,ARect.Top,ARect.Right,ARect.Top+13);
    Canvas->Brush->Color = FTitleBackColor;
    Canvas->FillRect(TitleRect);
    Canvas->Font->Name = "宋体";
    Canvas->Font->Size = 9;
    Canvas->Font->Color = FTitleTextColor;
    Canvas->Font->Style = Canvas->Font->Style << fsBold;
    Canvas->TextOut(x,y,DayStr);
    Canvas->Font->Style = Canvas->Font->Style >> fsBold;
    Canvas->TextOut(ARect.Right-50,y,CnDayStr);  //农历
  }
  catch(...)
  {
  }
}
//日期到日历网格转换---------------------------------------------------------
TPoint __fastcall TCalendarViewGrid::DateToCell(TDateTime ADate)
{
  TPoint p;
  FPageStartDate = Dates[0][0];
  FPageEndDate = Dates[6][FWeekCount - 1];
  if(ADate<FPageStartDate)
  {
    p.x = -1;
    p.y = -1;
    return p;
  }
  if(ADate>FPageEndDate)
  {
    p.x = 65535;
    p.y = 65535;
    return p;
  }
  p.x = (ADate - FPageStartDate) % 7;
  p.y = int(ADate - FPageStartDate) / 7;
  return p;
}
//得到某网格日期那周周末的网格---------------------------------------------
TPoint __fastcall TCalendarViewGrid::GetWeekEndCell(TPoint p)
{
  TPoint r;
  r.y = p.y;
  r.x = 6;
  return r;
}
//得到某网格日期那周开始的网格-----------------------------------------------
TPoint __fastcall TCalendarViewGrid::GetWeekStartCell(TPoint p)
{
  TPoint r;
  r.y = p.y;
  r.x = 0;
  return r;
}
//绘制任务条起始段-----------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawStartBar(int ID,TPoint p ,String TaskName, bool Hot, int TaskAttr)
{
  int RectTop,RectLeft,RectRight,RectBottom;
  int LN;
  LN = TaskLineNo[ID];
  TRect r = CellRect(p.x,p.y);
  TRect TaskRect;
  RectTop = r.top + 18 + (FTaskBarHeight + FTaskBarGap) * LN;
  if(RectTop > r.bottom)
  {
    CellFlag[p.x][p.y] = true;
    return;
  }
  RectLeft = r.left+1;
  RectRight = RectLeft + DefaultColWidth -2;
  RectBottom = RectTop + FTaskBarHeight;
  if(RectBottom > r.bottom)
  {
    CellFlag[p.x][p.y] = true;
    return;
  }
  TaskRect = TRect(RectLeft,RectTop,RectRight,RectBottom);
  if(FTaskFillColor != clNone)
  {
    if(!Hot)
    {
      if((TaskAttr & ATTR_MILESTONE) == ATTR_MILESTONE)
        Canvas->Brush->Color = FMileStoneFillColor;
      else
        Canvas->Brush->Color = FTaskFillColor;
      Canvas->Pen->Width = 1;
    }
    else
    {
      Canvas->Pen->Width = 2;
      Canvas->Brush->Color = FTaskFillHotColor;
    }
  if((TaskAttr & ATTR_EXTERNAL) != ATTR_EXTERNAL)
    Canvas->FillRect(TaskRect);
  }
  if(!Hot)
  {
    if((TaskAttr & ATTR_CRITICAL) == ATTR_CRITICAL)
      Canvas->Pen->Color = FCriticalBorderColor;
    else
      Canvas->Pen->Color = FTaskBorderColor;
    Canvas->Pen->Width = 1;
  }
  else
  {
    Canvas->Pen->Color = FTaskBorderHotColor;
    Canvas->Pen->Width = 2;
  }
  if((TaskAttr & ATTR_EXTERNAL) != ATTR_EXTERNAL)
  {
    Canvas->MoveTo(RectRight,RectTop);
    Canvas->LineTo(RectLeft,RectTop);
    Canvas->LineTo(RectLeft,RectBottom);
    Canvas->LineTo(RectRight,RectBottom);
    Canvas->Font->Assign(FTaskFont);
  }
  else
  {
    if(Hot)
    {
      Canvas->Pen->Color = FTaskFillHotColor;
      Canvas->Pen->Width = 2;
    }
    else
      Canvas->Pen->Width = 1;

    Canvas->MoveTo(RectLeft,RectTop + (RectBottom - RectTop) / 2);
    Canvas->LineTo(RectRight,RectTop + (RectBottom - RectTop) / 2);
  }
}
//绘制任务条结束段-----------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawEndBar(int ID,TPoint p, String TaskName, bool Hot, int TaskAttr)
{
  int RectTop,RectLeft,RectRight,RectBottom;
  TRect r = CellRect(p.x,p.y);
  TRect TaskRect;
  int LN;
  LN = TaskLineNo[ID];
  RectTop = r.top + 18 + (FTaskBarHeight + FTaskBarGap) * LN;
  if(RectTop > r.bottom)
  {
    CellFlag[p.x][p.y] = true;
    return;
  }
  RectLeft = r.left+2;
  RectRight = RectLeft + DefaultColWidth-3;
  RectBottom = RectTop + FTaskBarHeight;
  if(RectBottom > r.bottom)
  {
    CellFlag[p.x][p.y] = true;
    return;
  }
  TaskRect = TRect(RectLeft,RectTop,RectRight,RectBottom);
  if(FTaskFillColor != clNone)
  {
    if(!Hot)
    {
      if((TaskAttr & ATTR_MILESTONE)== ATTR_MILESTONE)
        Canvas->Brush->Color = FMileStoneFillColor;
      else
        Canvas->Brush->Color = FTaskFillColor;
      Canvas->Pen->Width = 1;
    }
    else
    {
      Canvas->Brush->Color = FTaskFillHotColor;
      Canvas->Pen->Width = 2;
    }
    if((TaskAttr & ATTR_EXTERNAL) != ATTR_EXTERNAL)
      Canvas->FillRect(TaskRect);
  }
  if(!Hot)
  {
    if((TaskAttr & ATTR_CRITICAL) == ATTR_CRITICAL)
      Canvas->Pen->Color = FCriticalBorderColor;
    else
      Canvas->Pen->Color = FTaskBorderColor;
    Canvas->Pen->Width = 1;
  }
  else
  {
    Canvas->Pen->Width = 2;
    Canvas->Pen->Color = FTaskBorderHotColor;
  }

  if((TaskAttr & ATTR_EXTERNAL) != ATTR_EXTERNAL)
  {
    Canvas->MoveTo(RectLeft,RectTop);
    Canvas->LineTo(RectRight,RectTop);
    Canvas->LineTo(RectRight,RectBottom);
    Canvas->LineTo(RectLeft,RectBottom);
    Canvas->Font->Assign(FTaskFont);
  }
  else
  {
    if(Hot)
    {
      Canvas->Pen->Color = FTaskFillHotColor;
      Canvas->Pen->Width = 2;
    }
    else
      Canvas->Pen->Width = 1;
    Canvas->MoveTo(RectLeft,RectTop + (RectBottom - RectTop) / 2);
    Canvas->LineTo(RectRight,RectTop + (RectBottom - RectTop) / 2);
  }
//  if(p.x==0)
//  {
//    SetBkMode(Canvas->Handle,TRANSPARENT);
//    DrawText(Canvas->Handle,TaskName.c_str(),TaskName.Length(),&TaskRect, DT_CENTER | DT_VCENTER);
//  }
}
//绘制任务条中间段-----------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawStraightBar(int ID,TPoint p1,TPoint p2, String TaskName, bool Hot,int TaskAttr)
{
  int RectTop,RectLeft,RectRight,RectBottom;
  TRect r1 = CellRect(p1.x,p1.y);
  TRect r2 = CellRect(p2.x,p2.y);
  TRect TaskRect;
  int LN;
  LN = TaskLineNo[ID];
  RectTop = r1.top + 18 + (FTaskBarHeight + FTaskBarGap) * LN;
  if(RectTop > r1.bottom)
  {
    int k;
    for(k = p1.x ; k <= p2.x ; k++)
    {
      CellFlag[k][p1.y] = true;
    }
    return;
  }
//  RectLeft = r1.left+1;
//  RectRight = RectLeft + (p2.x - p1.x + 1) * DefaultColWidth + p2.x - p1.x -1;
  RectLeft = r1.left-2;
  RectRight = RectLeft + (p2.x - p1.x + 1) * DefaultColWidth + p2.x - p1.x+5;
  RectBottom = RectTop + FTaskBarHeight;
  if(RectBottom > r1.bottom)
  {
    int k;
    for(k = p1.x ; k <= p2.x ; k++)
    {
      CellFlag[k][p1.y] = true;
    }
    return;
  }
  TaskRect = TRect(RectLeft,RectTop,RectRight,RectBottom);
  if(FTaskFillColor != clNone)
  {
    if(!Hot)
    {
      if((TaskAttr & ATTR_MILESTONE) == ATTR_MILESTONE)
        Canvas->Brush->Color = FMileStoneFillColor;
      else
        Canvas->Brush->Color = FTaskFillColor;
      Canvas->Pen->Width = 1;
    }
    else
    {
      Canvas->Pen->Width = 2;
      Canvas->Brush->Color = FTaskFillHotColor;
    }
    if((TaskAttr & ATTR_EXTERNAL) != ATTR_EXTERNAL)
      Canvas->FillRect(TaskRect);
  }
//  Canvas->Font->Assign(FTaskFont);
//  SetBkMode(Canvas->Handle,TRANSPARENT);
//  DrawText(Canvas->Handle,TaskName.c_str(),TaskName.Length(),&TaskRect, DT_CENTER | DT_VCENTER);
  if(!Hot)
  {
    if((TaskAttr & ATTR_CRITICAL) == ATTR_CRITICAL)
      Canvas->Pen->Color = FCriticalBorderColor;
    else
      Canvas->Pen->Color = FTaskBorderColor;
    Canvas->Pen->Width = 1;
  }
  else
  {
    Canvas->Pen->Width = 2;
    Canvas->Pen->Color = FTaskBorderHotColor;
  }
  if((TaskAttr & ATTR_EXTERNAL) != ATTR_EXTERNAL)
  {
    Canvas->MoveTo(RectLeft,RectTop);
    Canvas->LineTo(RectRight,RectTop);
    Canvas->MoveTo(RectRight,RectBottom);
    Canvas->LineTo(RectLeft,RectBottom);
  }
  else
  {
    if(Hot)
    {
      Canvas->Pen->Color = FTaskFillHotColor;
      Canvas->Pen->Width = 2;
    }
    else
      Canvas->Pen->Width = 1;
    Canvas->MoveTo(RectLeft,RectTop + (RectBottom - RectTop) / 2);
    Canvas->LineTo(RectRight,RectTop + (RectBottom - RectTop) / 2);
  }
}
//绘制任务条-----------------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawBar(int ID,TPoint p1, TPoint p2, String TaskName, bool Hot, int TaskAttr)
{
  int DeltaX,DeltaY;
  TPoint tp1,tp2;
  DeltaX = p2.x - p1.x;
  DeltaY = p2.y - p1.y;
  if(DeltaY < 0) return;
  if(DeltaY == 0)
  {
    if(DeltaX<0) return;
    if(p2.x - p1.x >1)
    {
      tp1.x = p1.x+1;
      tp1.y = p1.y;
      tp2.x = p2.x-1;
      tp2.y = p2.y;
      DrawStraightBar(ID,tp1,tp2,TaskName, Hot, TaskAttr);
    }
    DrawStartBar(ID,p1,TaskName, Hot, TaskAttr);
    DrawEndBar(ID,p2,TaskName, Hot, TaskAttr);
    DrawTaskCaption(p1,p2,ID,TaskName, Hot, TaskAttr);
  }
  else if (DeltaY == 1)
  {
    if(p1.x<=5)
    {
      tp1.x = p1.x+1;
      tp1.y = p1.y;
      DrawStraightBar(ID,tp1,GetWeekEndCell(tp1),TaskName, Hot, TaskAttr);
      DrawStartBar(ID,p1,TaskName, Hot, TaskAttr);
      DrawTaskCaption(p1,GetWeekEndCell(p1),ID,TaskName, Hot, TaskAttr);
    }
    else
    {
      DrawStartBar(ID,p1,TaskName, Hot, TaskAttr);
      DrawTaskCaption(p1,GetWeekEndCell(p1),ID,TaskName, Hot, TaskAttr);
    }
    if(p2.x>=1)
    {
      tp2.x = p2.x-1;
      tp2.y = p2.y;
      DrawStraightBar(ID,GetWeekStartCell(tp2),tp2,TaskName, Hot, TaskAttr);
      DrawEndBar(ID,p2,TaskName, Hot, TaskAttr);
      DrawTaskCaption(GetWeekStartCell(p2),p2,ID,TaskName, Hot, TaskAttr);
    }
    else
    {
      DrawEndBar(ID,p2,TaskName, Hot, TaskAttr);
      DrawTaskCaption(GetWeekStartCell(p2),p2,ID,TaskName, Hot, TaskAttr);
    }
  }
  else if (DeltaY>1)
  {
    if(p1.x<=5)
    {
      tp1.x = p1.x+1;
      tp1.y = p1.y;
      DrawStraightBar(ID,tp1,GetWeekEndCell(tp1),TaskName, Hot, TaskAttr);
      DrawStartBar(ID,p1,TaskName, Hot, TaskAttr);
    }
    else
      DrawStartBar(ID,p1,TaskName, Hot, TaskAttr);
    DrawTaskCaption(p1,GetWeekEndCell(p1),ID,TaskName, Hot, TaskAttr);

    if(p2.x>=1)
    {
      tp2.x = p2.x-1;
      tp2.y = p2.y;
      DrawStraightBar(ID,GetWeekStartCell(tp2),tp2,TaskName, Hot, TaskAttr);
      DrawEndBar(ID,p2,TaskName, Hot, TaskAttr);
    }
    else
      DrawEndBar(ID,p2,TaskName, Hot, TaskAttr);
    DrawTaskCaption(GetWeekStartCell(p2),p2,ID,TaskName, Hot, TaskAttr);
    int i;
    tp1.y= p1.y;
    for(i=1; i<=DeltaY-2+1; i++)
    {
      tp1.y++;
      tp1.x = 0;
      DrawStraightBar(ID,tp1,GetWeekEndCell(tp1),TaskName, Hot, TaskAttr);
      DrawTaskCaption(tp1,GetWeekEndCell(tp1),ID,TaskName, Hot, TaskAttr);
    }
  }
}
//画一个任务-----------------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawATask(int ID,TDateTime SDate,TDateTime EDate, String TaskName, bool Hot, int TaskAttr)
{
  TPoint sp,ep,tp;
  sp = DateToCell(SDate);
  ep = DateToCell(EDate);
  int i;
  if((sp.x == -1 || sp.y == -1) && (ep.x ==65535 || ep.y == 65535)) //FULL CALE
  {
    sp.x = 0;
    for(i=0;i<=FWeekCount-1;i++)
    {
      sp.y = i;
      DrawStraightBar(ID,sp,GetWeekEndCell(sp),TaskName, Hot, TaskAttr);
      DrawTaskCaption(sp,GetWeekEndCell(sp),ID,TaskName, Hot, TaskAttr);
    }
  }
  else if(((sp.x == -1 || sp.y == -1) && (ep.x == -1 || ep.y == -1)) ||
          ((sp.x == 65535 || sp.y == 65535) && (ep.x == 65535 || ep.y == 65535)))
    return;
  else if((sp.x == -1 || sp.y == -1))
  {
    sp.x = 0;
    for(i=1;i<=ep.y;i++)
    {
      sp.y = i-1;
      DrawStraightBar(ID,sp,GetWeekEndCell(sp),TaskName, Hot, TaskAttr);
      DrawTaskCaption(sp,GetWeekEndCell(sp),ID,TaskName, Hot, TaskAttr);
    }
    tp.x = ep.x - 1;
    tp.y = ep.y;
    DrawStraightBar(ID,GetWeekStartCell(tp),tp,TaskName, Hot, TaskAttr);
    DrawEndBar(ID,ep,TaskName, Hot, TaskAttr);
    DrawTaskCaption(GetWeekStartCell(ep),ep,ID,TaskName, Hot, TaskAttr);
  }
  else if((ep.x == 65535 || ep.y == 65535))
  {
    tp.x = sp.x + 1;
    tp.y = sp.y;
    DrawStraightBar(ID,tp,GetWeekEndCell(tp),TaskName, Hot, TaskAttr);
    DrawStartBar(ID,sp,TaskName, Hot, TaskAttr);
    DrawTaskCaption(sp,GetWeekEndCell(sp),ID,TaskName, Hot, TaskAttr);
    ep.x = 0;
    for(i=sp.y+1;i<=FWeekCount-1;i++)
    {
      ep.y = i;
      DrawStraightBar(ID,ep,GetWeekEndCell(ep),TaskName, Hot, TaskAttr);
      DrawTaskCaption(ep,GetWeekEndCell(ep),ID,TaskName, Hot, TaskAttr);
    }
  }
  else DrawBar(ID,sp,ep,TaskName, Hot, TaskAttr);
}
//画所有任务-----------------------------------------------------------------
void __fastcall TCalendarViewGrid::PaintTasks()
{
  if(!FProject) return;
  if(FProject->Tasks.Count() == 0) return;
  int i;
  TDateTime SDate,EDate;
  String TaskCaption;
  ResetCellFlag();
  TaskLineNo.Length = FProject->Tasks.Count();
  PlanTaskLines();
  int AAttr;
  for(i=0;i<FProject->Tasks.Count();i++)
  {
    SDate = FProject->Tasks[i]->StartDate;
    EDate = FProject->Tasks[i]->EndDate;
    TaskCaption = FCaptionType == ctName ? FProject->Tasks[i]->Name : FProject->Tasks[i]->WBS;
    AAttr = ATTR_NORMAL; //0x0000
    if(FProject->Tasks[i]->GetType() == ttForeignProject)  AAttr = ATTR_EXTERNAL;
    if(FProject->Tasks[i]->Critical)  AAttr = AAttr | ATTR_CRITICAL;  //关键任务
    if(FProject->Tasks[i]->MileStone) AAttr = AAttr | ATTR_MILESTONE;  //里程碑
    DrawATask(i,SDate,EDate,TaskCaption, FProject->Tasks[i]==FSelectedTask, AAttr);
  }
}
//日期赋值-------------------------------------------------------------------
void __fastcall TCalendarViewGrid::AssignDates(TDateTime StartDate)
{
  int i,j;
  for(i=0;i<=6;i++)
    for(j=0;j<=FWeekCount-1;j++)
      Dates[i][j] = StartDate + j * 7 + i;
}
//---------------------------------------------------------------------------
bool __fastcall TCalendarViewGrid::SelectCell(int ACol, int ARow)
{
   FDate = Dates[ACol][ARow];
   TRect SelRect;
   SelRect = CellRect(ACol,ARow);
   POINT cp , p;
   POINT Cell;
   cp.x = SelRect.Left;
   cp.y = SelRect.Top;
   GetCursorPos(&p);
   p.x = p.x - ClientOrigin.x - cp.x;
   p.y = p.y - ClientOrigin.y - cp.y;
   Cell.x = ACol;
   Cell.y = ARow;
   FSelectedTask = PointToTask(p,Cell);
   Invalidate();
   return TCustomGrid::SelectCell(ACol,ARow);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::ClickHandler(TObject *Sender)
{
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::DblClick(void)
{
  TControl::DblClick();
  if(FProject)
  {
    if(FOnTaskDblClick  && FSelectedTask)
      FOnTaskDblClick(FProject,FSelectedTask);
    else if(FOnCellDblClick)
      FOnCellDblClick(Col,Row,Dates[Col][Row]);
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::Click(void)
{
  TControl::Click();
  if(FProject)
  {
    if(FOnTaskClick  && FSelectedTask)
      FOnTaskClick(FProject,FSelectedTask);
    else if(FOnCellClick)
      FOnCellClick(Col,Row,Dates[Col][Row]);
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::CMWantSpecialKey(TCMWantSpecialKey &Message)
{
  Message.Result = 0;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::SetADate(TDateTime ADate)
{
  FDate = ADate;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::Resize(void)
{
  TControl::Resize();
  DefaultRowHeight = (Height - FWeekCount+1) / FWeekCount;
  DefaultColWidth = (Width - 8) / 7;
  if((DefaultRowHeight * FWeekCount) + FWeekCount + 1 > Height)
  {
    DefaultRowHeight --;
  }
  if((DefaultColWidth * 7) + 8 > Width)
  {
    DefaultColWidth --;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::Paint()
{
  TCustomGrid::Paint();
  CaleView->PaintWeekCaption();
  CaleView->PaintMonthName(FPageStartDate);
  PaintTasks();
  int i,j;
  for(i=0;i<=6;i++)
    for(j=0;j<=FWeekCount-1;j++)
    if(CellFlag[i][j])
    {
      DrawArrow(i,j);
    }
}
//绘制任务标题---------------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawTaskCaption(TPoint p1, TPoint p2, int ID,String TaskName, bool Hot, int TaskAttr)
{
  int RectTop,RectLeft,RectRight,RectBottom;
  TRect r1 = CellRect(p1.x,p1.y);
  TRect r2 = CellRect(p2.x,p2.y);
  TRect TaskRect;
  int LN;
  LN = TaskLineNo[ID];
  RectTop = r1.top + 18 + (FTaskBarHeight + FTaskBarGap) * LN;
  if(RectTop > r1.bottom) return;
  RectLeft = r1.left;
  RectRight = RectLeft + (p2.x - p1.x + 1) * DefaultColWidth + p2.x - p1.x-1;
  RectBottom = RectTop + FTaskBarHeight;
  if(RectBottom > r1.bottom) return;
  TaskRect = TRect(RectLeft,RectTop,RectRight,RectBottom);
  Canvas->Font->Assign(FTaskFont);
  int TextLen = 0;
  int TextLeft, TextRight;
  TSize Size;
  if(Hot)
  {
//    Canvas->Font->Style = Canvas->Font->Style << fsBold;
    Canvas->Font->Color = FHotTextColor;
    if((TaskAttr & ATTR_EXTERNAL) == ATTR_EXTERNAL)
    {
      Size = Canvas->TextExtent(TaskName);
      TextLen = Size.cx + 30;
      TextLeft = RectLeft + (((RectRight - RectLeft) - TextLen) / 2);
      TextRight = TextLeft + TextLen;
      Canvas->Pen->Color = FTaskFillHotColor;
      Canvas->Brush->Color = FTaskFillHotColor;
      Canvas->RoundRect(TextLeft,RectTop,TextRight,RectBottom,10,10);
      Canvas->FloodFill(TextLeft + TextLen/2,
                        RectTop + (RectBottom - RectTop) / 2,
                        FTaskFillHotColor, fsBorder);
    }
  }
  else
  {
    Canvas->Font->Style = Canvas->Font->Style >> fsBold;
    Canvas->Font->Color = FTextColor;
    if((TaskAttr & ATTR_EXTERNAL) == ATTR_EXTERNAL)
    {
      Size = Canvas->TextExtent(TaskName);
      TextLen = Size.cx + 30;
      TextLeft = RectLeft + (((RectRight - RectLeft) - TextLen) / 2);
      TextRight = TextLeft + TextLen;
      TColor AColor;
      if((TaskAttr & ATTR_CRITICAL) == ATTR_CRITICAL)
         AColor = FCriticalBorderColor;
      else
         AColor = FTaskBorderColor;
      Canvas->Pen->Color = AColor;
      Canvas->Brush->Color = AColor;
      Canvas->RoundRect(TextLeft,RectTop,TextRight,RectBottom,10,10);
      Canvas->FloodFill(TextLeft + TextLen/2,
                        RectTop + (RectBottom - RectTop) / 2,
                        AColor, fsBorder);
    }
  }
  if((TaskAttr & ATTR_EXTERNAL) == ATTR_EXTERNAL)
  {
//    Canvas->Brush->Color = FBackColor;
//    TaskName = " " + TaskName + " ";
    SetBkMode(Canvas->Handle,TRANSPARENT);
  }
  else
  {
    SetBkMode(Canvas->Handle,TRANSPARENT);
  }

  DrawText(Canvas->Handle,TaskName.c_str(),TaskName.Length(),&TaskRect, DT_CENTER
			| DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}
//点到任务转换---------------------------------------------------------------
TTask *__fastcall TCalendarViewGrid::PointToTask(POINT p, POINT Cell)
{
  if(FProject==NULL)
    return NULL;
  int h;
  int LN,i;
  TTask *ATask;
  h = p.y;
  if(h<=18) return NULL;
  h -= 18;
  LN = h / (FTaskBarHeight + FTaskBarGap);
  if(h > ((FTaskBarHeight + FTaskBarGap) * LN  +  FTaskBarHeight))
    return NULL;
  if(Cell.x < 0 || Cell.x > 6) return NULL;
  if(Cell.y < 0 || Cell.y > FWeekCount - 1) return NULL;
  for(i=0;i<=FProject->Tasks.Count()-1;i++)
  {
    ATask = FProject->Tasks[i];
	if(TaskLineNo[i] == LN && Dates[Cell.x][Cell.y]>=ATask->StartDate
       && Dates[Cell.x][Cell.y] <= ATask->EndDate)
       return ATask;
  }
  return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
  Fgc = MouseCoord(X,Y);
  POINT Cell, cp;
  Cell.x = Fgc.X;
  Cell.y = Fgc.Y;
  TRect r;
  r = CellRect(Fgc.X,Fgc.Y);
  cp.x = r.Left;
  cp.y = r.Top;
  X = X - cp.x;
  Y = Y - cp.y;
  cp.x = X;
  cp.y = Y;
  if(PointToTask(cp,Cell))
    this->Cursor = crHandPoint;
  else
    this->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarViewGrid::ResetCellFlag()
{
  int i,j;
  for(i=0;i<=6;i++)
    for(j=0;j<=5;j++)
  {
    CellFlag[i][j] = false;
  }
}
//绘制“信息不足”箭头-------------------------------------------------------
void __fastcall TCalendarViewGrid::DrawArrow(int ACol, int ARow)
{
  TRect cr;
  TPoint p1;
  cr = CellRect(ACol,ARow);
  p1.y = cr.Top + 3;
  p1.x = cr.Right - 50 - 8;
  SetBkMode(Canvas->Handle,TRANSPARENT);
  Canvas->Font->Color = FTitleTextColor;
  Canvas->Font->Size = 6;
  Canvas->Font->Name = "宋体";
  Canvas->TextOut(p1.x,p1.y,"▼");
  Canvas->Font->Size = 9;
}
//---------------------------------------------------------------------------
int __fastcall TCalendarViewGrid::GetTaskLine(int TaskID, TDateTime TaskSDate)
{
/*
  int i;
  int LineNo;
  TTask * ATask;
  for(i=0;i<=TaskID;i++)
  {
    ATask = FProject->Tasks[i];
    if(TaskSDate>=ATask->StartDate && TaskSDate<=ATask->EndDate)
    {
      LineNo =
    }
  }
*/
  return -1;
}
//计算任务行-----------------------------------------------------------------
void __fastcall TCalendarViewGrid::PlanTaskLines()
{
  //TODO: Agorithm needs more improvements
  int i;
//  int LN;
  TTask * ATask;
  TTask * PrevTask;
  for(i=0;i<=FProject->Tasks.Count()-1;i++)
  {
    if(i==0)
    {
       TaskLineNo[0] = 0;
       continue;
    }
    ATask = FProject->Tasks[i];
    PrevTask = FProject->Tasks[i-1];
	if(ATask->StartDate <= PrevTask->EndDate)//有重叠
      TaskLineNo[i] = TaskLineNo[i-1] + 1;
    else TaskLineNo[i] = TaskLineNo[i-1];
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// TCalendarView Class
//---------------------------------------------------------------------------
__fastcall TCalendarView::TCalendarView(TComponent* Owner)
        : TPanel(Owner)
{
  InitCalendar();
  FDataLink = new TCWPrjDataChangeLink(this);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetFlat(bool value)
{
  FFlat = value;
  if(FFlat)
  {
    this->BevelInner = bvNone;
    this->BevelOuter = bvNone;
    this->Ctl3D = false;
    this->BorderStyle = bsNone;
    this->BorderWidth = 0;

    Scrollbar->Ctl3D = false;
    Calendar->Ctl3D = false;
  }
  else
  {
    this->BevelInner = bvNone;
    this->BevelOuter = bvLowered;
    this->Ctl3D = true;
    this->BorderStyle = bsNone;
    this->BorderWidth = 1;

    Scrollbar->Ctl3D = true;
    Calendar->Ctl3D = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::InitCalendar()
{
  this->Width = 538+20+2;
  this->Height = 387+18+20+2;
  this->BevelOuter = bvLowered;
  this->Font->Name = "宋体";
  this->Font->Size = 9;
  Scrollbar = new TScrollBar(this);
  Scrollbar->Kind = sbVertical;
  Scrollbar->Align = alRight;
  Scrollbar->Parent = this;
  Scrollbar->Min = 1;
  Scrollbar->Max = 3444;
  Scrollbar->OnScroll = ScrollHandler;

  pnlMain = new TPanel(this);
  pnlMain->Parent = this;
  pnlMain->BevelOuter = bvNone;
  pnlMain->Align = alClient;

  pnlMonth = new TPaintBox(pnlMain);
  pnlMonth->Height = 18;
  pnlMonth->Parent = pnlMain;
  pnlMonth->Align = alTop;

  pnlDayCaption = new TPaintBox(pnlMain);
  pnlDayCaption->Height = 20;
  pnlDayCaption->Parent = pnlMain;
  pnlDayCaption->Align = alTop;

  Calendar = new TCalendarViewGrid(pnlMain);
  Calendar->FWeekCount = 6;
  Calendar->Parent = pnlMain;
  Calendar->FixedRows = 0;
  Calendar->FixedCols = 0;
  Calendar->ColCount = 7;
  Calendar->RowCount = 6;
  Calendar->DefaultColWidth = 76;
  Calendar->DefaultRowHeight = 64;
  Calendar->GridLineWidth = 1;
  Calendar->Width = 76*7+6;
  Calendar->Height = 64*6+3;
  Calendar->DefaultDrawing = true;
  Calendar->Align = alClient;
  Calendar->ScrollBars = ssNone;
  Calendar->Options >> goRangeSelect;
  Calendar->FColor = clWindow;
  Calendar->FBackColor = clWhite;
  Calendar->FTextColor = (TColor)0x00844100;
  Calendar->FHotTextColor = clBlack;
  Calendar->FTitleBackColor = (TColor)0x00DEDFE7;
  Calendar->FTitleTextColor = clBlack;
  Calendar->FSelectedBackColor =(TColor)0x00FFCECE;
  Calendar->FTaskBorderHotColor = (TColor)0x00CE9294;
  Calendar->FCompBackColor = (TColor)0x00F1E4E4;
  Calendar->FCompTextColor = clBlack;
  Calendar->FWeekEndBackColor = (TColor)0x00EFEBEF;
  Calendar->FTaskBorderColor = (TColor)0x00C68284;
  Calendar->FTaskFillColor = (TColor)0x00F7F7F7;
  Calendar->FTaskFillHotColor = (TColor)0x00FFE3CE;
  Calendar->FCriticalBorderColor = (TColor)0x008482FF;
  Calendar->FMileStoneFillColor = (TColor)0x00C58F8F;
  Calendar->FTaskBarGap = 2;
  Calendar->FTaskBarHeight = 10;
  Calendar->FTaskFont = new TFont();
  Calendar->FTaskFont->Name = "宋体";
  Calendar->FTaskFont->Size = 9;
  Calendar->FTaskFont->Style<<fsBold;
  Calendar->CaleView = this;
  SetDate(::Date());
  Calendar->FSelectedTask = NULL;
  Calendar->DefaultDrawing = false;
  Calendar->ResetCellFlag();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TCalendarView::DrawCalendar(String PrjCode, String TaskCode)
{
}
//---------------------------------------------------------------------------
__fastcall TCalendarView::~TCalendarView()
{
  try
  {
    delete pnlMonth;
    delete pnlDayCaption;
    delete Calendar;
    delete pnlMain;
    delete Scrollbar;
    delete FDataLink;
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::PaintWeekCaption()
{
  pnlDayCaption->Font->Size = 9;
  pnlDayCaption->Font->Name = "宋体";
  int i,x;
  int Gap;
  Gap = Calendar->DefaultColWidth / 2;
  for(i=1;i<=7;i++)
  {
    x = (2*i-1)*Gap;
    pnlDayCaption->Canvas->TextOut(x,4,WeekCaps[i-1]);
  }
  pnlDayCaption->Canvas->MoveTo(0,0);
  pnlDayCaption->Canvas->LineTo(pnlDayCaption->Width,0);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::PaintMonthName(TDateTime d)
{
  pnlMonth->Canvas->Font->Style = pnlMonth->Canvas->Font->Style << fsBold;
  pnlMonth->Canvas->TextOut(10,3,FormatDateTime("yyyy'年'm'月        '",d));
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetDate(TDateTime value)
{
  Calendar->SetADate(value);
  ScrollPage(value);
  Scrollbar->Position = (int)(value - 30682) / 7;

}
//---------------------------------------------------------------------------
TDateTime __fastcall TCalendarView::GetDate()
{
  return Calendar->FDate;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetWeekEndBackColor(TColor value)
{
  Calendar->FWeekEndBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetWeekEndBackColor()
{
        return Calendar->FWeekEndBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetSelectedBackColor(TColor value)
{
  Calendar->FSelectedBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetSelectedBackColor()
{
  return Calendar->FSelectedBackColor;
}

//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskBorderHotColor(TColor value)
{
  Calendar->FTaskBorderHotColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTaskBorderHotColor()
{
  return Calendar->FTaskBorderHotColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::ScrollHandler(TObject *Sender,TScrollCode ScrollCode,int &ScrollPos)
{
  TDateTime ADate;
  switch(ScrollCode)
  {
    case scLineUp: //向上翻页
       ScrollPage(Calendar->FPageStartDate - 1);
      break;
    case scLineDown: //向下一行
       ScrollPage(Calendar->FPageStartDate + 7);
      break;
    case scPageUp:  //向上一行
       ScrollPage(Calendar->FPageStartDate - (7 * Calendar->FWeekCount - 1));
      break;
    case scPageDown://向下翻页
       ScrollPage(Calendar->FPageEndDate + 1);
      break;
    case scPosition:
       ADate = ScrollPos * 7 - 30682;
       ScrollPage(Calendar->FPageEndDate + 1);
      break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::ScrollPage(TDateTime ADate)
{
  unsigned short AYear,AMonth,ADay;
  TDateTime MonthStartDate,CaleStartDate;
  BYTE dow;

  DecodeDate(ADate,AYear,AMonth,ADay);
  MonthStartDate = StartOfAMonth(AYear,AMonth);
  dow = DayOfWeek(ADate);
  CaleStartDate = ADate - dow + 1;
  Calendar->FPageStartDate = CaleStartDate;
  Calendar->FPageEndDate = CaleStartDate + 7 * Calendar->FWeekCount - 1;
  Calendar->FActiveMonth = AMonth;
  Calendar->AssignDates(CaleStartDate);
  Calendar->Invalidate();
  Scrollbar->Position = (int)(ADate - 30682) / 7;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TCalendarView::PosToDateTime(int pos)
{
  int BaseYear = 1984;
  Word AYear,AMonth;
  AYear = BaseYear + pos / 12;
  AMonth = pos % 12;
  if(AMonth == 0)
  {
   AMonth = 12;
   AYear --;
  }
  return (TDateTime)EncodeDate(AYear,AMonth,1);
}
//---------------------------------------------------------------------------
int __fastcall TCalendarView::DateTimeToPos(TDateTime ADate)
{
  int BaseYear = 1984;
  Word AYear=0,AMonth=0,ADay=0;
  DecodeDate(ADate,AYear,AMonth,ADay);
  return (AYear - BaseYear) * 12 + AMonth;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetColor(TColor value)
{
  pnlMonth->Color = value;
  pnlDayCaption->Color = value;
  pnlMain->Color = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetColor()
{
  return pnlMain->Color;
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetBackColor()
{
  return Calendar->FBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetBackColor(TColor value)
{
  Calendar->FBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTextColor()
{
  return Calendar->FTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTextColor(TColor value)
{
  Calendar->FTextColor = value;
  Calendar->Invalidate();
}
TColor __fastcall TCalendarView::GetHotTextColor()
{
  return Calendar->FHotTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetHotTextColor(TColor value)
{
  Calendar->FHotTextColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTitleBackColor()
{
  return Calendar->FTitleBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTitleBackColor(TColor value)
{
  Calendar->FTitleBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTitleTextColor()
{
  return Calendar->FTitleTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTitleTextColor(TColor value)
{
  Calendar->FTitleTextColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetCompTextColor()
{
  return Calendar->FCompTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetCompTextColor(TColor value)
{
  Calendar->FCompTextColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetCompBackColor()
{
  return Calendar->FCompBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetCompBackColor(TColor value)
{
  Calendar->FCompBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetMileStoneColor(TColor value)
{
        if(Calendar->FMileStoneFillColor != value) {
                Calendar->FMileStoneFillColor = value;
                Calendar->Invalidate();
        }
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetMileStoneColor()
{
        return Calendar->FMileStoneFillColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetCriticalBorderColor(TColor value)
{
        if(Calendar->FCriticalBorderColor != value) {
                Calendar->FCriticalBorderColor = value;
                Calendar->Invalidate();
        }
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetCriticalBorderColor()
{
        return Calendar->FCriticalBorderColor;
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTaskRestColor()
{
  return Calendar->FTaskRestColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskRestColor(TColor value)
{
  Calendar->FTaskRestColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetProject(TProject* value)
{
  if(Calendar->FProject != value)
  {
    Calendar->FProject = value;
    Calendar->TaskLineNo.Length = Calendar->FProject->Tasks.Count();
    Calendar->PlanTaskLines();
    FDataLink->SetProject(value);
  }
}
//---------------------------------------------------------------------------
TProject* __fastcall TCalendarView::GetProject()
{
  return Calendar->FProject;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskBorderColor(TColor value)
{
  if(Calendar->FTaskBorderColor != value) {
          Calendar->FTaskBorderColor = value;
          Calendar->Invalidate();
  }
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTaskBorderColor()
{
  return Calendar->FTaskBorderColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskFillColor(TColor value)
{
  if(Calendar->FTaskFillColor != value) {
          Calendar->FTaskFillColor = value;
          Calendar->Invalidate();
  }
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTaskFillColor()
{
  return Calendar->FTaskFillColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskBarHeight(int value)
{
  if(Calendar->FTaskBarHeight != value) {
          Calendar->FTaskBarHeight = value;
          Calendar->Invalidate();
  }
}
//---------------------------------------------------------------------------
int __fastcall TCalendarView::GetTaskBarHeight()
{
  return Calendar->FTaskBarHeight;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskBarGap(int value)
{
  if(Calendar->FTaskBarGap != value) {
          Calendar->FTaskBarGap = value;
          Calendar->Invalidate();
  }
}
//---------------------------------------------------------------------------
int __fastcall TCalendarView::GetTaskBarGap()
{
  return Calendar->FTaskBarGap;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskFont(TFont* value)
{
  Calendar->FTaskFont->Assign(value);
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TFont* __fastcall TCalendarView::GetTaskFont()
{
  return Calendar->FTaskFont;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetWeekCount(int value)
{
  if(Calendar->FWeekCount != value) {
          if(value>6) value = 6;
          if(value<1) value = 1;
          Calendar->FWeekCount = value;
          Calendar->ColCount = 7;
          Calendar->RowCount = Calendar->FWeekCount;
          Calendar->Resize();
          ScrollPage(Calendar->FDate);
  }
}
//---------------------------------------------------------------------------
int __fastcall TCalendarView::GetWeekCount()
{
        return Calendar->FWeekCount;
}
//---------------------------------------------------------------------------
TTaskEvent __fastcall TCalendarView::GetOnTaskClick()
{
        return Calendar->FOnTaskClick;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetOnTaskClick(TTaskEvent value)
{
  Calendar->FOnTaskClick = value;
}
//---------------------------------------------------------------------------
TTaskEvent __fastcall TCalendarView::GetOnTaskDblClick()
{
        return Calendar->FOnTaskDblClick;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetOnTaskDblClick(TTaskEvent value)
{
  Calendar->FOnTaskDblClick = value;
}
//---------------------------------------------------------------------------
CaleCellEvent __fastcall TCalendarView::GetOnCellClick()
{
   return Calendar->FOnCellClick;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetOnCellClick(CaleCellEvent value)
{
  Calendar->FOnCellClick = value;
}
//---------------------------------------------------------------------------
CaleCellEvent __fastcall TCalendarView::GetOnCellDblClick()
{
   return Calendar->FOnCellDblClick;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetOnCellDblClick(CaleCellEvent value)
{
  Calendar->FOnCellDblClick = value;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetSelectedTask(TTask * value)
{
  if(value)
  {
    Calendar->FSelectedTask = value;
  }
  else
  {
    Calendar->FSelectedTask = NULL;
   }
  Refresh();
}
//---------------------------------------------------------------------------
TTask * __fastcall TCalendarView::GetSelectedTask()
{
  if(Calendar->FProject && Calendar->FSelectedTask)
    return Calendar->FSelectedTask;
  else return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetTaskFillHotColor(TColor value)
{
        if(Calendar->FTaskFillHotColor != value) {
                Calendar->FTaskFillHotColor = value;
                Calendar->Invalidate();
        }
}
//---------------------------------------------------------------------------
TColor __fastcall TCalendarView::GetTaskFillHotColor()
{
        return Calendar->FTaskFillHotColor;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::Refresh()
{
  TWinControl::Refresh();
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TCalendarView::SetCaptionType(TCaptionType value)
{
        if(Calendar->FCaptionType != value) {
                Calendar->FCaptionType = value;
                Calendar->Invalidate();
        }
}
//---------------------------------------------------------------------------
TCaptionType __fastcall TCalendarView::GetCaptionType()
{
        return Calendar->FCaptionType;
}
//---------------------------------------------------------------------------




