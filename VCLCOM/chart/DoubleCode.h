//---------------------------------------------------------------------------

#ifndef DoubleCodeH
#define DoubleCodeH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <values.h>
#include <Forms.hpp>
#include "ProjectStruct.h"
#include "ZChartDraw.h"
#include "NavigationImage.h"
using namespace ProjectStruct;
#define TPrintHandle void*
//---------------------------------------------------------------------------
class TDCPrjDataChangeLink;
class TDCProject;
class PACKAGE TDoubleCode : public TWinControl
{
     friend TDCProject;
private:
     TPrintHandle FPrintHandle;
     bool FDblClickAdjust;
     TTaskEvent FOnTaskClick, FOnTaskDblClick;
     void __fastcall PaintWindow(HDC DC);
     DYNAMIC void __fastcall AdjustSize(void);
     DYNAMIC void __fastcall Resize(void);
     MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
     MESSAGE void __fastcall WMHScroll(Messages::TMessage &Message);
     MESSAGE void __fastcall WMVScroll(Messages::TMessage &Message);
     MESSAGE void __fastcall WMDblClick(Messages::TMessage &Message);

protected:
     DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
     DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
     DYNAMIC void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
#pragma option -w-inl
BEGIN_MESSAGE_MAP
      VCL_MESSAGE_HANDLER(WM_HSCROLL, TMessage, WMHScroll);
      VCL_MESSAGE_HANDLER(WM_VSCROLL, TMessage, WMVScroll);
      VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
      VCL_MESSAGE_HANDLER(WM_LBUTTONDBLCLK, TMessage, WMDblClick);
END_MESSAGE_MAP(TWinControl);
#pragma option -winl
private:
     TDCProject* FDCProject;
     int FAllowOverlap;
     TFont*   FTextFont;

     TPrintHandle __fastcall GetPrintHandle();
     int __fastcall GetTotalHeight();
     int __fastcall GetTotalWidth();
     TProject* __fastcall GetProject();
     void __fastcall SetProject(TProject*);
     int __fastcall GetCalendarHeight();
     void __fastcall SetCalendarHeight(int);
     int __fastcall GetRowHeight();
     void __fastcall SetRowHeight(int);
     TEventDraw*    GetEventDraw();
     TTaskLine*     GetCriticalDraw();
     TTaskLine*     GetTaskDraw();
     TVirtualLine*  GetCriticalVirtualDraw();
     TVirtualLine*  GetVirtualDraw();
     TCalendarDraw* GetCalendarDraw();
     TTaskShowString* __fastcall GetTopShowString();
     TTaskShowString* __fastcall GetBottomShowString();
     void __fastcall SetOldProjectTaskID(String str);
public:
     SCROLLINFO FHORZ;
     SCROLLINFO FVERT;
	 bool DrawingNavigation;
	 TNavigationImage * NaviImage;
     bool ShowDays;
     int Language;

     __fastcall TDoubleCode(TComponent* Owner);
	 __fastcall ~TDoubleCode();

	 void __fastcall AdjustOnFrameMove(int X, int Y);
	 void __fastcall ShowNavigation();

     HDC  GetDrawDc();
     void Draw(HDC dc, RECT dr);
     void DrawCalendar(HDC dc, int ALeft, int AWidth);
     void AutoAlign();
     void AdjustScrollBar();
     void SetDefault();
	 void __fastcall FindTaskByName(String TaskName);
     __property int AllowOverlap = {read=FAllowOverlap,write=FAllowOverlap};
     __property TEventDraw*      EventDraw = {read=GetEventDraw};
     __property TTaskLine*       CriticalDraw = {read=GetCriticalDraw};
     __property TTaskLine*       TaskDraw = {read=GetTaskDraw};
     __property TVirtualLine*    CriticalVirtualDraw = {read=GetCriticalVirtualDraw};
     __property TVirtualLine*    VirtualDraw = {read=GetVirtualDraw};
     __property TCalendarDraw*   CalendarDraw = {read=GetCalendarDraw};
     __property TTaskShowString* TopShowString = {read=GetTopShowString};
     __property TTaskShowString* BottomShowString = {read=GetBottomShowString};

	 __property TProject*    Project = {read=GetProject, write=SetProject};
     __property int          CalendarHeight = {read=GetCalendarHeight, write=SetCalendarHeight};
     __property int          RowHeight = {read=GetRowHeight, write=SetRowHeight};
     __property TPrintHandle PrintHandle = {read=GetPrintHandle};
     __property int          TotalHeight = {read=GetTotalHeight};
     __property int          TotalWidth = {read=GetTotalWidth};
     __property TFont*       TextFont  = {read=FTextFont,write=FTextFont};
	 __property String   OldProjectTaskID = {write=SetOldProjectTaskID};
__published:
     __property TTaskEvent OnTaskClick = {read=FOnTaskClick, write=FOnTaskClick};
     __property TTaskEvent OnTaskDblClick = {read=FOnTaskDblClick, write=FOnTaskDblClick};
     __property Align;
     __property Color;
     __property Font;
	 __property Visible;
};
//---------------------------------------------------------------------------
#endif
