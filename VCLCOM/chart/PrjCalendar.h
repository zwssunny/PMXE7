//---------------------------------------------------------------------------
// 任务日历/计划编排组件 类声明 PrjCalendar.h
//---------------------------------------------------------------------------
// Calendar Planning Component for HYWY CPM  Series
// Created by Sunny Zhan,  2002
//---------------------------------------------------------------------------
#ifndef PrjCalendarH
#define PrjCalendarH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <set>
#include <iterator>
#include "ZCnDate.hpp"
#include "Zedit.h"
using namespace std;
//---------------------------------------------------------------------------
// Constants and Enums
//---------------------------------------------------------------------------
const RecodeLeaveFieldAsIs = 65535;
const BASEDATE = 30682; //1984-1-1
const MAXDATE = 54788;//2049-12-31

enum TWorkDayType {dtNormal , dtWeekEnd, dtCompleted, dtWorkRef};
enum TViewType {vtWorkLoad=0, vtPValue=1, vtResource=2, vtMaterial=3, vtTaskWorkLoad=4};
const String WeekCaps[7] = {"日","一","二","三","四","五","六"};
//---------------------------------------------------------------------------
// TDailyPlanData
//---------------------------------------------------------------------------
//记录工作日数据的结构体
struct TDailyPlanData
{
  int ID;
  TDateTime Date;
  double Value;
  TWorkDayType DayType;
};

class TPrjCalendarPanel;

//---------------------------------------------------------------------------
// TCalendarGrid Class   日期网格
//---------------------------------------------------------------------------
class PACKAGE TCalendarGrid : public TCustomGrid
{
  friend TPrjCalendarPanel;

private:
    TPrjCalendarPanel *PrjCale;
    TDateTime Dates[7][6];
	TZEdit *EditBox;           //编辑框
	set<TDateTime> FSelList;  //选中项列表
    TDateTime FLastSelDate;
    void TagSelected(TDateTime ADate);
	void __fastcall AssignDates(TDateTime StartDate);  //得到日历日期
    void __fastcall ShowEditAt(int ACol, int ARow, double InitValue); //构建编辑框
    void __fastcall EditKeyDown(TObject* Sender, Word &Key, TShiftState Shift);

protected:
    TColor FColor;
    TColor FBackColor;
    TColor FTextColor;
    TColor FTitleBackColor;
    TColor FTitleTextColor;
    TColor FSelectedBackColor;
    TColor FSelectedTextColor;
    TColor FCompBackColor;
    TColor FCompTextColor;
    TColor FTaskColor;
    TColor FTaskRestColor;
    TDateTime FPageStartDate;
    TDateTime FPageEndDate;
    TDateTime PlanStartDate, PlanEndDate;
    TList * DailyPlans;
    TDateTime FDate;
    TDateTime FCompletedDate;
	unsigned short FActiveMonth; //当前显示之月份
    int EditX;                   //当前编辑X坐标
    int EditY;                   //当前编辑Y坐标
    bool FModified;              //更改标志
    bool FPrjFinished;           //项目完工标志

	virtual void __fastcall DrawCell(int ACol, int ARow, const TRect &ARect, TGridDrawState AState);
    virtual bool __fastcall SelectCell(int ACol, int ARow);
    DYNAMIC void __fastcall TopLeftChanged(void);
    DYNAMIC void __fastcall DblClick(void);
	DYNAMIC void __fastcall KeyDown(Word &Key, TShiftState Shift);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X,	int Y);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Resize(void);
public:
    __fastcall TCalendarGrid(TComponent *Owner);
    __fastcall ~TCalendarGrid();
	__property Height;
    __property Width;
    __property Align;
    __property ScrollBars;
	void __fastcall ClickHandler(TObject *Sender);
    TRect __fastcall CellRect(int ACol, int ARow);
    void __fastcall SetADate(TDateTime ADate);
    void __fastcall PaintTaskPlan();
	void __fastcall WMSize(TMessage &Msg);
	BEGIN_MESSAGE_MAP
	 VCL_MESSAGE_HANDLER(WM_SIZE,TMessage, WMSize)
	END_MESSAGE_MAP(TCustomGrid)
};

//---------------------------------------------------------------------------
// TPrjCalendarPanel Class
//---------------------------------------------------------------------------
class PACKAGE TPrjCalendarPanel : public TPanel
{
  friend TCalendarGrid;
private:
  TPaintBox *pnlMonth;
  TPaintBox *pnlDayCaption;
  TPanel *pnlMain;
  TScrollBar *Scrollbar;

  bool FFlat;
  bool FEnableEdit;
  float FMaxValue;
  TViewType FViewType;

  void __fastcall InitCalendar();
  void __fastcall PaintWeekCaption();
  void __fastcall PaintMonthName(TDateTime d);
  void __fastcall SetDate(TDateTime value);
  TDateTime __fastcall GetDate();
  void __fastcall SetCompDate(TDateTime value);
  TDateTime __fastcall GetCompDate();
  void __fastcall ScrollHandler(TObject *Sender,TScrollCode ScrollCode,int &ScrollPos);
  void __fastcall SetModified(bool value);
  bool __fastcall GetModified();

  TDateTime __fastcall GetSelected(unsigned int idx);
  int __fastcall GetSelCount();

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
  void __fastcall SetSelectedBackColor(TColor value);
  TColor __fastcall GetSelectedBackColor();
  void __fastcall SetCompBackColor(TColor value);
  TColor __fastcall GetCompBackColor();
  void __fastcall SetCompTextColor(TColor value);
  TColor __fastcall GetCompTextColor();
  void __fastcall SetSelectedTextColor(TColor value);
  TColor __fastcall GetSelectedTextColor();
  void __fastcall SetTaskColor(TColor value);
  TColor __fastcall GetTaskColor();
  void __fastcall SetTaskRestColor(TColor value);
  TColor __fastcall GetTaskRestColor();
  void __fastcall SetViewType(TViewType value);
  TViewType __fastcall GetViewType();
  void __fastcall SetFlat(bool value);
  void __fastcall ScrollPage(TDateTime ADate);
  void __fastcall DrawCalendar(String PrjCode, String TaskCode);
  TDateTime __fastcall PosToDateTime(int pos);
  int __fastcall DateTimeToPos(TDateTime ADate);
  void __fastcall SetPrecision(int value);
  int __fastcall GetPrecision();
  void __fastcall SetPrjFinished(bool value);
  bool __fastcall GetPrjFinished();
  void __fastcall SetEnableEdit(bool value);
  void __fastcall SetEditCharType(TZCharType value);
  TZCharType __fastcall GetEditCharType();
  void __fastcall SetEditDigLen(int value);
  int __fastcall GetEditDigLen();
  void __fastcall SetEditMaxLength(int value);
  int __fastcall GetEditMaxLength();

public:
  TCalendarGrid *Calendar;
  __fastcall TPrjCalendarPanel(TComponent* Owner);
  __fastcall ~TPrjCalendarPanel();
  void __fastcall AddDailyPlan(int ID, TDateTime ADate,double AValue, TWorkDayType ADayType);
  void __fastcall ReplaceDailyPlan(int ID,TDateTime ADate,double AValue, TWorkDayType ADayType);
  void __fastcall ChangePlanValue(int AID, double NewValue);
  void __fastcall ClearDailyPlan();
  double __fastcall GetTotalValue();
  double __fastcall GetDailyPlan(int AID);
  void CancelEdit();
  double OldValue;
  double ModifiedValue;
  int ModifiedID;

__published:
  __property TDateTime Date  = { read=GetDate, write=SetDate };
  __property TDateTime CompletedDate  = { read=GetCompDate, write=SetCompDate };
  __property TColor Color  = { read=GetColor, write=SetColor };
  __property TColor BackColor  = { read=GetBackColor, write=SetBackColor };
  __property TColor TextColor  = { read=GetTextColor, write=SetTextColor };
  __property TColor TitleBackColor  = { read=GetTitleBackColor, write=SetTitleBackColor };
  __property TColor TitleTextColor  = { read=GetTitleTextColor, write=SetTitleTextColor };
  __property TColor CompBackColor  = { read=GetCompBackColor, write=SetCompBackColor };
  __property TColor CompTextColor  = { read=GetCompTextColor, write=SetCompTextColor };
  __property TColor SelectedBackColor  = { read=GetSelectedBackColor, write=SetSelectedBackColor };
  __property TColor SelectedTextColor = {read=GetSelectedTextColor, write=SetSelectedTextColor};
  __property TColor TaskColor = {read=GetTaskColor, write=SetTaskColor};
  __property TColor TaskRestColor = {read=GetTaskRestColor, write=SetTaskRestColor};
  __property bool Modified  = { read=GetModified ,write=SetModified };
  __property bool Flat = { read = FFlat, write = SetFlat };
  __property TViewType ViewType = {read = GetViewType,write=SetViewType};
  __property int Precision  = { read=GetPrecision, write=SetPrecision };
  __property bool PrjFinished  = { read=GetPrjFinished, write=SetPrjFinished };
  __property bool EnableEdit = { read=FEnableEdit,write=SetEnableEdit};
  __property TDateTime Selected[unsigned int idx] = {read = GetSelected};
  __property int SelCount = {read = GetSelCount};
  __property float MaxValue = {read = FMaxValue, write=FMaxValue};
  __property TZCharType EditCharType  = { read=GetEditCharType, write=SetEditCharType };
  __property int EditDigLen  = { read=GetEditDigLen, write=SetEditDigLen };
  __property int EditMaxLength  = { read=GetEditMaxLength, write=SetEditMaxLength };

};
//---------------------------------------------------------------------------
#endif
