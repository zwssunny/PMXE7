//---------------------------------------------------------------------------
// 工作日历组件  类声明  SDCaleView.h
//---------------------------------------------------------------------------
// Calendar View Component for HYWY CPM  Series
// Created by Sunny Zhan, 2002-5
//---------------------------------------------------------------------------
// Last modified at: 2002-11-18
//---------------------------------------------------------------------------
#ifndef CalendarViewH
#define CalendarViewH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "ZCnDate.hpp"
#include "PrjCalendar.h"
#include "ProjectStruct.h"
//任务属性
#define ATTR_NORMAL     0x0000000F  //正常
#define ATTR_EXTERNAL   0x000000F0  //外部
#define ATTR_CRITICAL   0x00000F00  //关键
#define ATTR_MILESTONE  0x0000F000  //里程碑

using namespace ProjectStruct;

typedef void __fastcall (__closure *CaleCellEvent)(int ACol,int ARow,TDateTime ADate);
enum TCaptionType { ctName = 0, ctCode = 1};  //标题类型：0-显示名称  1-显示代码


//---------------------------------------------------------------------------
// Class TCalendarViewGrid
//---------------------------------------------------------------------------
class PACKAGE TCalendarView;
class TCalendarViewGrid : public TCustomGrid
{
  friend TCalendarView;
private:
  TCalendarView *CaleView;      //容器指针
  TDateTime Dates[7][6];    //日期数组
  bool CellFlag[7][6];      //显示超界标志。出现显示超界的工作日会显示符号"▼"
  Grids::TGridCoord Fgc;
  void __fastcall AssignDates(TDateTime StartDate);   //得到日历日期数组
  TTask* __fastcall PointToTask(POINT p, POINT Cell);  //得到网格cell中点p位置的任务
  void __fastcall DrawArrow(int ACol, int ARow);      //绘制"▼"
  int __fastcall GetTaskLine(int TaskID, TDateTime TaskSDate);  //计算某任务的绘制行

protected:
  virtual void __fastcall DrawCell(int ACol, int ARow,
                         const TRect &ARect, TGridDrawState AState);
  virtual bool __fastcall SelectCell(int ACol, int ARow);
  DYNAMIC void __fastcall Click(void);
  DYNAMIC void __fastcall DblClick(void);
  MESSAGE void __fastcall CMWantSpecialKey(TCMWantSpecialKey &Message);
  virtual void __fastcall Paint(void);
  DYNAMIC void __fastcall Resize(void);
  DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
  void __fastcall ResetCellFlag();  //重置超界标志
  void __fastcall DrawTaskCaption(TPoint p1, TPoint p2, int ID,String TaskName,bool Hot, int TaskAttr); //绘制标题
  void __fastcall PlanTaskLines();  //绘制任务条

  TColor FColor;
  TColor FBackColor;
  TColor FTextColor;
  TColor FHotTextColor;
  TColor FTitleBackColor;
  TColor FTitleTextColor;
  TColor FSelectedBackColor;
  TColor FCompBackColor;
  TColor FCompTextColor;
  TColor FWeekEndBackColor;
  TColor FTaskBorderColor;
  TColor FTaskBorderHotColor;
  TColor FTaskFillColor;
  TColor FMileStoneFillColor;
  TColor FTaskFillHotColor;
  TColor FCriticalBorderColor;
  TColor FTaskRestColor;
  TDateTime FPageStartDate;
  TDateTime FPageEndDate;
  TDateTime FDate;
  TCaptionType FCaptionType;
  TTask * FSelectedTask;
  TProject *FProject;
  int FTaskBarHeight;
  int FTaskBarGap;
  TFont *FTaskFont;
  unsigned short FActiveMonth;
  int FWeekCount;
  DynamicArray<int> TaskLineNo;
  TTaskEvent FOnTaskClick, FOnTaskDblClick;
  CaleCellEvent FOnCellClick,FOnCellDblClick;

public:
    __fastcall TCalendarViewGrid(TComponent *Owner);
    __fastcall ~TCalendarViewGrid();
    __property FixedCols;
    __property FixedRows;
    __property ColCount;
    __property RowCount;
    __property DefaultColWidth;
    __property DefaultRowHeight;
    __property GridLineWidth;
    __property Height;
    __property Width;
    __property DefaultDrawing;
    __property Align;
    __property ScrollBars;
    __property Options;
    __property Canvas;
    __property Row;
    __property Col;
    void __fastcall ClickHandler(TObject *Sender);
    TRect __fastcall CellRect(int ACol, int ARow);
    void __fastcall SetADate(TDateTime ADate);
    void __fastcall PaintTasks();
    void __fastcall DrawATask(int ID,TDateTime SDate,TDateTime EDate,String TaskName, bool Hot, int TaskAttr);
    TPoint __fastcall DateToCell(TDateTime ADate);
    TPoint __fastcall GetWeekStartCell(TPoint p);
    TPoint __fastcall GetWeekEndCell(TPoint p);
    void __fastcall DrawStartBar(int ID,TPoint p,String TaskName,bool Hot, int TaskAttr);
    void __fastcall DrawEndBar(int ID,TPoint p,String TaskName,bool Hot,int TaskAttr);
    void __fastcall DrawStraightBar(int ID,TPoint p1,TPoint p2,String TaskName,bool Hot,int TaskAttr);
    void __fastcall DrawBar(int ID,TPoint p1, TPoint p2,String TaskName,bool Hot,int TaskAttr);

#pragma option -w-inl
BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(CM_WANTSPECIALKEY, TCMWantSpecialKey, CMWantSpecialKey);
END_MESSAGE_MAP(TCustomGrid);
#pragma option -winl
};

//---------------------------------------------------------------------------
// TCalendarView Class
//---------------------------------------------------------------------------
class PACKAGE TCalendarView : public TPanel
{
  friend TCalendarViewGrid;
private:
  TPaintBox *pnlMonth;
  TPaintBox *pnlDayCaption;
  TPanel *pnlMain;
  TScrollBar *Scrollbar;
  bool FFlat;
  TPrjDataChangeLink * FDataLink;
  void __fastcall InitCalendar();
  void __fastcall PaintWeekCaption();
  void __fastcall PaintMonthName(TDateTime d);
  void __fastcall SetDate(TDateTime value);
  TDateTime __fastcall GetDate();
  void __fastcall SetCompDate(TDateTime value);
  TDateTime __fastcall GetCompDate();
  void __fastcall ScrollHandler(TObject *Sender,TScrollCode ScrollCode,int &ScrollPos);

  void __fastcall SetColor(TColor value);
  TColor __fastcall GetColor();
  void __fastcall SetBackColor(TColor value);
  TColor __fastcall GetBackColor();
  void __fastcall SetTextColor(TColor value);
  TColor __fastcall GetTextColor();
  void __fastcall SetTitleBackColor(TColor value);
  TColor __fastcall GetTitleBackColor();
  void __fastcall SetTitleTextColor(TColor value);
  TColor __fastcall GetTitleTextColor();
  void __fastcall SetHotTextColor(TColor value);
  TColor __fastcall GetHotTextColor();
  void __fastcall SetSelectedBackColor(TColor value);
  TColor __fastcall GetSelectedBackColor();
  void __fastcall SetCompBackColor(TColor value);
  TColor __fastcall GetCompBackColor();
  void __fastcall SetCompTextColor(TColor value);
  TColor __fastcall GetCompTextColor();
  void __fastcall SetWeekEndBackColor(TColor value);
  TColor __fastcall GetWeekEndBackColor();
  void __fastcall SetTaskBorderHotColor(TColor value);
  TColor __fastcall GetTaskBorderHotColor();
  void __fastcall SetTaskRestColor(TColor value);
  TColor __fastcall GetTaskRestColor();

  void __fastcall SetFlat(bool value);
  void __fastcall ScrollPage(TDateTime ADate);
  void __fastcall DrawCalendar(String PrjCode, String TaskCode);

  TDateTime __fastcall PosToDateTime(int pos);
  int __fastcall DateTimeToPos(TDateTime ADate);

  void __fastcall SetProject(TProject* value);
  TProject* __fastcall GetProject();

  void __fastcall SetTaskBorderColor(TColor value);
  TColor __fastcall GetTaskBorderColor();

  void __fastcall SetTaskFillColor(TColor value);
  TColor __fastcall GetTaskFillColor();

  void __fastcall SetTaskBarHeight(int value);
  int __fastcall GetTaskBarHeight();

  void __fastcall SetTaskBarGap(int value);
  int __fastcall GetTaskBarGap();

  void __fastcall SetTaskFont(TFont *value);
  TFont* __fastcall GetTaskFont();

  void __fastcall SetWeekCount(int value);
  int __fastcall GetWeekCount();

  TTaskEvent __fastcall GetOnTaskClick();
  void __fastcall SetOnTaskClick(TTaskEvent value);

  TTaskEvent __fastcall GetOnTaskDblClick();
  void __fastcall SetOnTaskDblClick(TTaskEvent value);

  CaleCellEvent __fastcall GetOnCellClick();
  void __fastcall SetOnCellClick(CaleCellEvent value);

  CaleCellEvent __fastcall GetOnCellDblClick();
  void __fastcall SetOnCellDblClick(CaleCellEvent value);

  void __fastcall SetSelectedTask(TTask * value);
  TTask * __fastcall GetSelectedTask();

  void __fastcall SetTaskFillHotColor(TColor value);
  TColor __fastcall GetTaskFillHotColor();

  void __fastcall SetCaptionType(TCaptionType value);
  TCaptionType __fastcall GetCaptionType();
  void __fastcall SetMileStoneColor(TColor value);
  TColor __fastcall GetMileStoneColor();
  void __fastcall SetCriticalBorderColor(TColor value);
  TColor __fastcall GetCriticalBorderColor();
public:
  TCalendarViewGrid *Calendar;
  __fastcall TCalendarView(TComponent* Owner);
  __fastcall ~TCalendarView();
  DYNAMIC void __fastcall Refresh();
  __property TTask * SelectedTask  = { read=GetSelectedTask, write=SetSelectedTask };
  __property TProject* Project  = { read=GetProject, write=SetProject };

__published:
  __property TDateTime Date  = { read=GetDate, write=SetDate };
  __property TColor Color  = { read=GetColor, write=SetColor };
  __property TColor BackColor  = { read=GetBackColor, write=SetBackColor };
  __property TColor TextColor  = { read=GetTextColor, write=SetTextColor };
  __property TColor HotTextColor  = { read=GetHotTextColor, write=SetHotTextColor };
  __property TColor TitleBackColor  = { read=GetTitleBackColor, write=SetTitleBackColor };
  __property TColor TitleTextColor  = { read=GetTitleTextColor, write=SetTitleTextColor };
  __property TColor CompBackColor  = { read=GetCompBackColor, write=SetCompBackColor };
  __property TColor CompTextColor  = { read=GetCompTextColor, write=SetCompTextColor };
  __property TColor WeekEndBackColor  = { read=GetWeekEndBackColor, write=SetWeekEndBackColor };
  __property TColor SelectedBackColor  = { read=GetSelectedBackColor, write=SetSelectedBackColor };
  __property TColor TaskBorderHotColor = {read=GetTaskBorderHotColor, write=SetTaskBorderHotColor};
  __property TColor TaskRestColor = {read=GetTaskRestColor, write=SetTaskRestColor};
  __property bool Flat = { read = FFlat, write = SetFlat };
  __property TColor TaskBorderColor  = { read=GetTaskBorderColor, write=SetTaskBorderColor };
  __property TColor TaskFillColor  = { read=GetTaskFillColor, write=SetTaskFillColor };
  __property int TaskBarHeight  = { read=GetTaskBarHeight, write=SetTaskBarHeight };
  __property int TaskBarGap  = { read=GetTaskBarGap, write=SetTaskBarGap };
  __property TFont *TaskFont  = { read=GetTaskFont, write=SetTaskFont };
  __property int WeekCount  = { read=GetWeekCount, write=SetWeekCount };
  __property TColor TaskFillHotColor  = { read=GetTaskFillHotColor, write=SetTaskFillHotColor };
  __property TCaptionType CaptionType  = { read=GetCaptionType, write=SetCaptionType };
  __property TColor MileStoneColor  = { read=GetMileStoneColor, write=SetMileStoneColor };

  __property TTaskEvent OnTaskClick = {read=GetOnTaskClick, write=SetOnTaskClick};
  __property TTaskEvent OnTaskDblClick = {read=GetOnTaskDblClick, write=SetOnTaskDblClick};
  __property CaleCellEvent OnCellClick = {read=GetOnCellClick, write=SetOnCellClick};
  __property CaleCellEvent OnCellDblClick = {read=GetOnCellDblClick, write=SetOnCellDblClick};
  __property TColor CriticalBorderColor  = { read=GetCriticalBorderColor, write=SetCriticalBorderColor };

};
//---------------------------------------------------------------------------
#endif



