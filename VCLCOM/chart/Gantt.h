//---------------------------------------------------------------------------
#ifndef GanttH
#define GanttH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>  
#include <Classes.hpp>
#include "ProjectStruct.h"
#include "ZChartDraw.h"
using namespace ProjectStruct;
//---------------------------------------------------------------------------
#define TPrintHandle void*
class PACKAGE TGanttSet
{
public:
	bool   ShowWarning;
    bool   ShowLine;
    bool   ShowHLine;
    bool   ShowProgressLine;
    bool   ShowPgViewLine;

    COLORREF LineColor;
    COLORREF CriticalLineColor;
    COLORREF CalendarBkColor;
    COLORREF CaldndarFontColor;
    COLORREF ProgressLineColor;
    COLORREF PgViewLineColor;

    T3BarDraw NotStartDraw;
    T3BarDraw StartedDraw;
    T3BarDraw OveredDraw;
    T3BarDraw CriticalNotStartDraw;
    T3BarDraw CriticalStartedDraw;
    T3BarDraw CriticalOveredDraw;
    T3BarDraw AbstractDraw;
    T3BarDraw MarkerDraw;
    T3BarDraw MarkerOverDraw;
    T3BarDraw WarningDraw;
    T3BarDraw ForeignNotStartDraw;
    T3BarDraw ForeignStartedDraw;
    T3BarDraw ForeignOveredDraw;
    T3BarDraw CriticalForeignNotStartDraw;
    T3BarDraw CriticalForeignStartedDraw;
    T3BarDraw CriticalForeignOveredDraw;
    T3BarDraw ForeignAbstractDraw;
    T3BarDraw ForeignMarkerDraw;
    T3BarDraw ForeignMarkerOverDraw;
    T3BarDraw ForeignProjectDraw;
	bool ShowDays;
	int Language;
    TStateDateType StateDateType;
    TDateTime ManualStateDate;

};

class PACKAGE TGanttProject;
class PACKAGE TGantt;
class PACKAGE TPrjGrid;

typedef void __fastcall (__closure *TTopTaskChanged)(TProject*AProject, TPrjObject*New, TPrjObject* Old);

class PACKAGE TGantt : public TWinControl
{
    friend TGanttProject;
    friend TPrjGrid;
private:
		bool FDblClickAdjust;
        SCROLLINFO FHORZ;
        SCROLLINFO FVERT;
        TGanttProject*  FProject;
        TPrintHandle FPrintHandle;
        TPrjGrid*    FBindGrid;
        TPrintHandle __fastcall GetPrintHandle();
        int GetDayWidth();
        void AdjustScrollBar();
        int __fastcall GetTotalHeight();
        int __fastcall GetTotalWidth();
        TProject* __fastcall GetProject();
        void __fastcall SetProject(TProject* AProject);
        TPrjObject* __fastcall GetTopTask();
        void __fastcall SetTopTask(TPrjObject*ATask);
        TDateTime __fastcall GetLeftDay();
        void __fastcall SetLeftDay(TDateTime ADate);
        TCalendarDraw* __fastcall GetCalendar();
        T3BarDraw* __fastcall GetNotStartDraw();//未开工
        T3BarDraw* __fastcall GetStartedDraw();//已开工
        T3BarDraw* __fastcall GetOveredDraw();//已完工
        T3BarDraw* __fastcall GetCriticalNotStartDraw();//未开工
        T3BarDraw* __fastcall GetCriticalStartedDraw();//已开工
        T3BarDraw* __fastcall GetCriticalOveredDraw();//已完工
        T3BarDraw* __fastcall GetAbstractDraw();//摘要任务
        T3BarDraw* __fastcall GetMarkerDraw();//里程碑
        T3BarDraw* __fastcall GetWarningDraw();//有问题任务
        T3BarDraw* __fastcall GetForeignNotStartDraw();//外部未开工
        T3BarDraw* __fastcall GetForeignStartedDraw();//外部已开工
        T3BarDraw* __fastcall GetForeignOveredDraw();//外部已完工
        T3BarDraw* __fastcall GetCriticalForeignNotStartDraw();//外部未开工
        T3BarDraw* __fastcall GetCriticalForeignStartedDraw();//外部已开工
        T3BarDraw* __fastcall GetCriticalForeignOveredDraw();//外部已完工
        T3BarDraw* __fastcall GetForeignAbstractDraw();//外部摘要任务
        T3BarDraw* __fastcall GetForeignMarkerDraw();//外部里程碑
        T3BarDraw* __fastcall GetForeignProjectDraw();//外部工程
        T3BarDraw* __fastcall GetMarkerOverDraw();    //里程碑
        T3BarDraw* __fastcall GetForeignMarkerOverDraw();//外部里程碑

        TGTLinkDraw* __fastcall GetCriticalLinkDraw();
        TGTLinkDraw* __fastcall GetNormalLinkDraw();
        TTaskShowString* __fastcall GetFrontShowString();
        TTaskShowString* __fastcall GetLateShowString();
        MESSAGE void __fastcall WMHScroll(Messages::TMessage &Message);
        MESSAGE void __fastcall WMVScroll(Messages::TMessage &Message);
        MESSAGE void __fastcall WMKeyDown(Messages::TWMKey &Message);
        MESSAGE void __fastcall WMKeyUp(Messages::TWMKey &Message);
        MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
        MESSAGE void __fastcall WMDblClick(Messages::TMessage &Message);
        MESSAGE void __fastcall WMErasebkgnd(Messages::TMessage &Message);
protected:
    void __fastcall PaintWindow(HDC DC);
    DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall AdjustSize(void);
public:
    __fastcall TGantt(TComponent* Owner);
	virtual __fastcall ~TGantt();
    void Refresh();
	void AutoAlign();
    void Draw(HDC dc, RECT dr, int TotalHeight = -1);
    void DrawCalendar(HDC dc, int ALeft, int AWidth, int LineHeight);
    void SetDefault();
    TPrjGrid* GetBindGrid() { return FBindGrid; }

	__property TProject* Project = {read=GetProject, write=SetProject};
	__property TGanttProject* GTProject = {read=FProject};
    __property TPrintHandle PrintHandle = {read=GetPrintHandle};
    __property int TotalHeight = {read=GetTotalHeight};
    __property int TotalWidth = {read=GetTotalWidth};
	__property TPrjObject* TopTask = {read=GetTopTask, write=SetTopTask};
    __property TDateTime LeftDay = {read=GetLeftDay, write=SetLeftDay};
    __property TCalendarDraw* Calendar = {read=GetCalendar};
    __property T3BarDraw* NotStartDraw = {read=GetNotStartDraw};//未开工
    __property T3BarDraw* StartedDraw = {read=GetStartedDraw};//已开工
    __property T3BarDraw* OveredDraw = {read=GetOveredDraw};//已完工
    __property T3BarDraw* CriticalNotStartDraw = {read=GetCriticalNotStartDraw};//未开工
    __property T3BarDraw* CriticalStartedDraw = {read=GetCriticalStartedDraw};//已开工
    __property T3BarDraw* CriticalOveredDraw = {read=GetCriticalOveredDraw};//已完工
    __property T3BarDraw* AbstractDraw = {read=GetAbstractDraw};//摘要任务
    __property T3BarDraw* MarkerDraw = {read=GetMarkerDraw};//里程碑
    __property T3BarDraw* WarningDraw = {read=GetWarningDraw};//有问题任务
    __property T3BarDraw* ForeignNotStartDraw = {read=GetForeignNotStartDraw};//外部未开工
    __property T3BarDraw* ForeignStartedDraw = {read=GetForeignStartedDraw};//外部已开工
    __property T3BarDraw* ForeignOveredDraw = {read=GetForeignOveredDraw};//外部已完工
    __property T3BarDraw* CriticalForeignNotStartDraw = {read=GetCriticalForeignNotStartDraw};//外部未开工
    __property T3BarDraw* CriticalForeignStartedDraw = {read=GetCriticalForeignStartedDraw};//外部已开工
    __property T3BarDraw* CriticalForeignOveredDraw = {read=GetCriticalForeignOveredDraw};//外部已完工
    __property T3BarDraw* ForeignAbstractDraw = {read=GetForeignAbstractDraw};//外部摘要任务
    __property T3BarDraw* ForeignMarkerDraw = {read=GetForeignMarkerDraw};//外部里程碑
    __property T3BarDraw* ForeignProjectDraw = {read=GetForeignProjectDraw};//外部工程
    __property T3BarDraw* ForeignMarkerOverDraw  = { read=GetForeignMarkerOverDraw };
    __property T3BarDraw* MarkerOverDraw  = { read=GetMarkerOverDraw };
    __property TGTLinkDraw* CriticalLinkDraw = {read=GetCriticalLinkDraw};
    __property TGTLinkDraw* NormalLinkDraw = {read=GetNormalLinkDraw};
    __property TTaskShowString* FrontShowString = {read=GetFrontShowString};
    __property TTaskShowString* LateShowString = {read=GetLateShowString};
    __property TTopTaskChanged OnTopTaskChanged = {read=FOnTopTaskChanged, write=FOnTopTaskChanged};
    __property bool ShowProgressLine  = { read=FShowProgressLine, write=SetShowProgressLine };
    __property bool ShowPgViewLine  = { read=FShowPgViewLine, write=SetShowPgViewLine };
    __property TColor ProgressLineColor  = { read=FProgressLineColor, write=SetProgressLineColor };
    __property TColor PgViewLineColor  = { read=FPgViewLineColor, write=SetPgViewLineColor };
    __property TStateDateType StateDateType  = { read=FStateDateType, write=SetStateDateType };
    __property TDateTime ManualStateDate  = { read=FManualStateDate, write=SetManualStateDate };
    __property bool ShowBasePlan  = { read=FShowBasePlan, write=SetShowBasePlan };

#pragma option -w-inl
BEGIN_MESSAGE_MAP
      VCL_MESSAGE_HANDLER(WM_KEYUP, TWMKeyUp, WMKeyUp);
      VCL_MESSAGE_HANDLER(CN_KEYDOWN, TWMKey, WMKeyDown);
      VCL_MESSAGE_HANDLER(CN_SYSKEYDOWN, TWMKey, WMKeyDown);
      VCL_MESSAGE_HANDLER(WM_HSCROLL, TMessage, WMHScroll);
      VCL_MESSAGE_HANDLER(WM_VSCROLL, TMessage, WMVScroll);
      VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
      VCL_MESSAGE_HANDLER(WM_LBUTTONDBLCLK, TMessage, WMDblClick);
END_MESSAGE_MAP(TWinControl);
#pragma option -winl
private:
    int FRowHeight, FCalendarHeight;
    bool FShowLine;
    bool FShowWarning;
    void __fastcall SetShowWarning(bool AValue);
    void __fastcall SetRowHeight(int AHeight);
    void __fastcall SetCalendarHeight(int AHeight);
    void __fastcall SetFocusColor(TColor AColor);
    void __fastcall SetLineColor(TColor AColor);
    void __fastcall SetCalendarBkColor(TColor AColor);
    void __fastcall SetCalendarFontColor(TColor AColor);
    void __fastcall SetShowLine(bool AValue);
    void __fastcall SetManualStateDate(TDateTime AValue);
    TColor __fastcall GetCalendarBkColor();
    TColor __fastcall GetCalendarFontColor();

    TPopupMenu* FTaskPopMenu, *FTaskLinkPopMenu, *FNoneTaskPopMenu;

    TTaskEvent      FOnTaskClick, FOnTaskDblClick,
                    FOnTaskSelect;
    TTopTaskChanged FOnTopTaskChanged;
        bool FShowHLine;
        bool FShowVLine;
        bool FShowProgressLine;
        bool FShowPgViewLine;
        TColor FProgressLineColor;
        TColor FPgViewLineColor;
        TStateDateType FStateDateType;
        TDateTime FManualStateDate;
        bool FShowBasePlan;
        void __fastcall SetShowHLine(bool value);
        void __fastcall SetShowVLine(bool value);
        void __fastcall SetShowProgressLine(bool value);
        void __fastcall SetShowPgViewLine(bool value);
        void __fastcall SetProgressLineColor(TColor value);
        void __fastcall SetPgViewLineColor(TColor value);
        void __fastcall SetStateDateType(TStateDateType value);
        void __fastcall SetShowDays(bool value);
        bool __fastcall GetShowDays();
        void __fastcall SetLanguage(int value);
        int __fastcall GetLanguage();
        void __fastcall SetShowBasePlan(bool value);
__published:
    __property bool   ShowWarning = {read=FShowWarning, write=SetShowWarning};
    __property int    RowHeight = {read=FRowHeight, write=SetRowHeight};
    __property int    CalendarHeight = {read=FCalendarHeight, write=SetCalendarHeight};
    __property TColor CalendarBkColor = {read=GetCalendarBkColor, write=SetCalendarBkColor};
    __property TColor CaldndarFontColor = {read=GetCalendarFontColor, write=SetCalendarFontColor};
    __property bool   ShowLine = {read=FShowLine, write=SetShowLine};//关系线
    __property bool   ShowHLine = {read=FShowHLine, write=SetShowHLine,default = false}; //横线
    __property bool   ShowVLine = {read=FShowVLine, write=SetShowVLine,default = true}; //竖线
    __property bool   ShowDays  = { read=GetShowDays, write=SetShowDays,default = true };
    __property int    Language  = { read=GetLanguage, write=SetLanguage ,default = 0};

    __property TPopupMenu* TaskPopMenu = {read=FTaskPopMenu, write=FTaskPopMenu};
    __property TPopupMenu* TaskLinkPopMenu = {read=FTaskLinkPopMenu, write=FTaskLinkPopMenu};
    __property TPopupMenu* NoneTaskPopMenu = {read=FNoneTaskPopMenu, write=FNoneTaskPopMenu};
    //事件
    __property TTaskEvent OnTaskClick = {read=FOnTaskClick, write=FOnTaskClick};
    __property TTaskEvent OnTaskDblClick = {read=FOnTaskDblClick, write=FOnTaskDblClick};
    __property TTaskEvent OnTaskSelect = {read=FOnTaskSelect, write=FOnTaskSelect};

    __property Align;
    __property Color;
    __property Font;
    __property Visible;
};
//---------------------------------------------------------------------------
#endif
