//---------------------------------------------------------------------------

#ifndef LogicalChartH
#define LogicalChartH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "ProjectStruct.h"
#define TPrintHandle void*
using namespace ProjectStruct;
//---------------------------------------------------------------------------
class TLGProject;
class TLogicalChart;

class PACKAGE TLGProject
{
    friend TLogicalChart;
    enum DrawFrameType {dftNormal, dftFocus, dftMove};
private:
    void Task_Draw(TTask&ATask, HDC dc);
    inline RECT Task_ClientRect(TTask&ATask);
    void TaskLink_Draw(TTaskLink&ALink, HDC dc);
    inline RECT TaskLink_ClientRect(TTaskLink&ALink);
    inline POINT TaskLink_FirstPoint(TTaskLink&ALink);
    inline POINT TaskLink_LastPoint(TTaskLink&ALink);
private:
    TProject* FProject;
    bool FMustDelete;
    RECT FMoveRect;
    bool FUpdating;
	TPrjDataChangeLink * FLGPrjDataChangeLink;
    bool AlignATask(TTask* ATask);
    inline int MaxHeight();
    void SetACurrTask(TTask*ATask);
protected:
    TLogicalChart * FChart;
    TTask* FCurrTask;
    RECT PointAtRect(int X, int Y);
    POINT PointAtTaskPosition(int X, int Y);
    RECT PositionAtRect(int Left, int Top);
    void DrawFrame(HDC dc, RECT dr, DrawFrameType Type);
    void __fastcall SetProject(TProject*);
    void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
    void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
public:
    __fastcall TLGProject(TLogicalChart* AChart);
    __fastcall ~TLGProject();
    void Draw(HDC dc);
    void SetCurrTask(String AID);
    __property TProject* Project = {read=FProject, write=SetProject};
    __property TLogicalChart* Chart = {read=FChart};
    __property TTask* CurrTask = {read=FCurrTask, write=SetACurrTask};
    __property bool Updating = {read=FUpdating, write=FUpdating};
};
class PACKAGE TLogicalChart : public TWinControl
{
    friend TLGProject;
private:
    SCROLLINFO FHORZ;
    SCROLLINFO FVERT;
    TLGProject * FProject;
    int CalcTaskHeight(HDC dc);
    HDC GetDrawDc();
    TProject* __fastcall GetProject();
    void __fastcall SetProject(TProject*);
    TTask* __fastcall GetCurrTask();
    void __fastcall SetCurrTask(TTask*);
    TPrintHandle FPrintHandle;
    TPrintHandle __fastcall GetPrintHandle();
    MESSAGE void __fastcall WMHScroll(Messages::TMessage &Message);
    MESSAGE void __fastcall WMVScroll(Messages::TMessage &Message);
    MESSAGE void __fastcall WMKeyDown(Messages::TWMKey &Message);
    MESSAGE void __fastcall WMKeyUp(Messages::TWMKey &Message);
    MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
//    MESSAGE void __fastcall WMDblClick(Messages::TMessage &Message);
protected:
    void __fastcall PaintWindow(HDC DC);
    DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall Click(void);
    DYNAMIC void __fastcall DblClick(void);
    DYNAMIC void __fastcall AdjustSize(void);
public:
    __fastcall TLogicalChart(TComponent* Owner);
    __fastcall ~TLogicalChart();
    void AdjustScrollBar();
    void Draw(HDC dc);
	void SetCurrTask(String AID);
    __property TPrintHandle PrintHandle = {read=GetPrintHandle};
	__property TProject* Project = {read=GetProject, write=SetProject};
    __property TLGProject* LGProject = {read=FProject};
    __property TTask* CurrTask = {read=GetCurrTask, write=SetCurrTask};
#pragma option -w-inl
BEGIN_MESSAGE_MAP
      VCL_MESSAGE_HANDLER(WM_KEYUP, TWMKeyUp, WMKeyUp);
      VCL_MESSAGE_HANDLER(CN_KEYDOWN, TWMKey, WMKeyDown);
      VCL_MESSAGE_HANDLER(CN_SYSKEYDOWN, TWMKey, WMKeyDown);
      VCL_MESSAGE_HANDLER(WM_HSCROLL, TMessage, WMHScroll);
      VCL_MESSAGE_HANDLER(WM_VSCROLL, TMessage, WMVScroll);
      VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
END_MESSAGE_MAP(TWinControl);
#pragma option -winl
__published:
    __property Align;
    __property Color;
    __property Font;
private:
    int FTaskWidth, FTaskHeight, FColDistance, FRowDistance, FTaskRowDistance;
    int FBorderWidth, FFocusBorderWidth, FLineWidth, FFocusLineWidth, FCrossLineWidth;
    TColor FBackColor, FBorderColor, FFocusColor,
           FLineColor, FFocusLineColor, FCrossLineColor;
    TColor FKeyPathColor, FSubRowColor1, FSubRowColor2;
    TPopupMenu* FTaskPopMenu, *FTaskLinkPopMenu, *FNoneTaskPopMenu;
    void __fastcall SetTaskWidth(int AWidth);
    void __fastcall SetColDistance(int AWidth);
    void __fastcall SetRowDistance(int AHeight);
    void __fastcall SetTaskRowDistance(int AWidth);
    void __fastcall SetBackColor(TColor AColor);
    void __fastcall SetBorderColor(TColor AColor);
    void __fastcall SetFocusColor(TColor AColor);
    void __fastcall SetLineColor(TColor AColor);
    void __fastcall SetFocusLineColor(TColor AColor);
    void __fastcall SetCrossLineColor(TColor AColor);
    void __fastcall SetBorderWidth(int AWidth);
    void __fastcall SetFocusBorderWidth(int AWidth);
    void __fastcall SetLineWidth(int AWidth);
    void __fastcall SetFocusLineWidth(int AWidth);
    void __fastcall SetCrossLineWidth(int AWidth);
    void __fastcall SetKeyPathColor(TColor AColor);

    TTaskEvent FOnTaskClick, FOnTaskDblClick;
__published:
    __property int TaskWidth = {read=FTaskWidth, write=SetTaskWidth};
    __property int TaskHeight = {read=FTaskHeight};
    __property int ColDistance = {read=FColDistance, write=SetColDistance};
    __property int RowDistance = {read=FRowDistance, write=SetRowDistance};
    __property int TaskRowDistance = {read=FTaskRowDistance, write=SetTaskRowDistance};
    __property TColor BorderColor = {read=FBorderColor, write=SetBorderColor};
    __property TColor FocusColor = {read=FFocusColor, write=SetFocusColor};
    __property TColor LineColor = {read=FLineColor, write=SetLineColor};
    __property TColor FocusLineColor = {read=FFocusLineColor, write=SetFocusLineColor};
    __property TColor BackColor = {read=FBackColor, write=SetBackColor};
    __property TColor CrossLineColor = {read=FCrossLineColor, write=SetCrossLineColor};
    __property TColor SubRowColor1 = {read=FSubRowColor1, write=FSubRowColor1};
    __property TColor SubRowColor2 = {read=FSubRowColor2, write=FSubRowColor2};
    __property int BorderWidth = {read=FBorderWidth, write=SetBorderWidth};
    __property int FocusBorderWidth = {read=FFocusBorderWidth, write=SetFocusBorderWidth};
    __property int LineWidth = {read=FLineWidth, write=SetLineWidth};
    __property int FocusLineWidth = {read=FFocusLineWidth, write=SetFocusLineWidth};
    __property int CrossLineWidth = {read=FCrossLineWidth, write=SetCrossLineWidth};
    __property TColor KeyPathColor = {read=FKeyPathColor, write=SetKeyPathColor};

    __property TPopupMenu* TaskPopMenu = {read=FTaskPopMenu, write=FTaskPopMenu};
    __property TPopupMenu* TaskLinkPopMenu = {read=FTaskLinkPopMenu, write=FTaskLinkPopMenu};
    __property TPopupMenu* NoneTaskPopMenu = {read=FNoneTaskPopMenu, write=FNoneTaskPopMenu};

    __property TTaskEvent OnTaskClick = {read=FOnTaskClick, write=FOnTaskClick};
    __property TTaskEvent OnTaskDblClick = {read=FOnTaskDblClick, write=FOnTaskDblClick};
};
//---------------------------------------------------------------------------
#endif
