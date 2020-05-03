//---------------------------------------------------------------------------
//    File:               Logicalchart.h, Logicalchart.cpp
//    Function:           逻辑图
//    Author:
//    Last Modify:
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogicalChart.h"
#include "vclComFunc.h"
#include "ZChartPrint.h"
#pragma package(smart_init)
using namespace Vclcomfunc;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

namespace Logicalchart
{
        void __fastcall PACKAGE Register()
        {
				 TComponentClass classes[1] = {__classid(TLogicalChart)};
				 RegisterComponents("ZChart", classes, 0);
        }
}
class TLGPrjDataChangeLink : public TPrjDataChangeLink
{
public:
	TLGProject* FLGProject;
    TLGPrjDataChangeLink(TLGProject*AProject)
       :TPrjDataChangeLink(AProject->Project) { FLGProject = AProject; }

    virtual void BeforeProjectChange()
    {
    }
    virtual void AfterProjectChange()
    {
       if(!(FLGProject->Updating))
          FLGProject->Chart->Invalidate();
    }
    virtual void BeforeTaskChange(TPrjObject*ATask){}
    virtual void AfterTaskChange(TPrjObject*ATask)
    {
       if(!(FLGProject->Updating))
          FLGProject->Chart->Invalidate();
    }
    virtual void BeforeTaskDelete(TPrjObject*ATask){}
    virtual void AfterTaskDelete()
    {
       if(!(FLGProject->Updating))
          FLGProject->Chart->Invalidate();
    }
    virtual void AfterTaskAdd(TPrjObject*ATask)
    {
       if(!(FLGProject->Updating))
          FLGProject->Chart->Invalidate();
    }
    virtual void BeforeTaskLinkChange(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkChange(TTaskLink*ATaskLink)
    {
       if(!(FLGProject->Updating))
          FLGProject->Chart->Invalidate();
    }
    virtual void BeforeTaskLinkDelete(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkAdd(TTaskLink*ATaskLink)
    {
       if(!(FLGProject->Updating))
          FLGProject->Chart->Invalidate();
	}
    virtual void BeginUpdate(){}
	virtual void EndUpdate()
    {
       if(FLGProject->Project->Tasks.Count())
       {
           if(FLGProject->Project->Selected &&
              !FLGProject->Project->Selected->IsForeign() &&
              (FLGProject->Project->Selected->GetType() == ttTask ||
               FLGProject->Project->Selected->GetType() == ttForeignProject))
           {
               FLGProject->CurrTask = FLGProject->Project->TaskByID(
                                                FLGProject->Project->Selected->TaskID);
           }else
           {
               FLGProject->CurrTask = FLGProject->Project->Tasks[0];
           }
       }
    }
	virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect)
    {
       if(!ATask)
       {
           FLGProject->CurrTask = NULL;
           return;
       }
       if(FLGProject->CurrTask && ATask != FLGProject->CurrTask)
       {
		  for(int i = 0; i < FLGProject->CurrTask->FrontTaskCount; i++)
		  {
			 if(FLGProject->CurrTask->FrontTasks[i]->Front == ATask)
				{
				if(!(FLGProject->Updating))
					FLGProject->Chart->Invalidate();
				return;
				}
		  }
		  for(int i = 0; i < FLGProject->CurrTask->LateTaskCount; i++)
		  {
			 if(FLGProject->CurrTask->LateTasks[i]->Task == ATask)
			 {
			   if(!(FLGProject->Updating))
					FLGProject->Chart->Invalidate();
				return;
			 }
		  }
		  if(ATask && !ATask->IsForeign())
		  {
			 switch(ATask->GetType())
			 {
				 case ttProject:
				 case ttAbstractTask:
					  return;
				 case ttTask:
				 case ttForeignProject:
					  FLGProject->CurrTask = (TTask*)ATask;
					  break;
			 }
		  }
		  return;
	   }
	   if(!(FLGProject->Updating))
			 FLGProject->Chart->Invalidate();
	}
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLGProject::Task_Draw(TTask&ATask, HDC dc)
{
   HPEN Pen;
   HGDIOBJ oldPen;
   HBRUSH Brush;
   HGDIOBJ oldBrush;
   RECT dr = Task_ClientRect(ATask);
   RECT tr;
   String AText;
   //擦底色
   tr = dr;
   tr.left -= 6;
   tr.top -= 6;
   tr.bottom += 6;
   tr.right += 6;
   Brush= CreateSolidBrush(FChart->Color);
   oldBrush = SelectObject(dc, Brush);
   FillRect(dc, &tr, Brush);
   SelectObject(dc, oldBrush);
   DeleteObject(Brush);

   if(ATask.Critical)
   {//关键路径
       Pen = CreatePen(PS_SOLID, 1, FChart->KeyPathColor);
       oldPen = SelectObject(dc, Pen);
       Rectangle(dc, dr.left-1-FChart->BorderWidth,
                     dr.top-1-FChart->BorderWidth,
                     dr.right+2+FChart->BorderWidth,
                     dr.bottom+2+FChart->BorderWidth);
       SelectObject(dc, oldPen);
       DeleteObject(Pen);
   }

   Pen = CreatePen(PS_SOLID, FChart->BorderWidth,
                             FChart->BorderColor);
   oldPen = SelectObject(dc, Pen);
   DrawFrame(dc, dr, TLGProject::dftNormal);
   SelectObject(dc, oldPen);
   DeleteObject(Pen);

   HFONT Font = CreateFontByTFont(FChart->Font);
   HGDIOBJ oldFont = SelectObject(dc, Font);
   //
   tr = dr;
   tr.left = tr.left + 3;
   tr.right = tr.right - 3;
   tr.top += FChart->TaskRowDistance;
   AText = ATask.WBS + ":" + ATask.Name;
   int textHeight = TextHeight(dc, AText);
   tr.bottom = tr.top + textHeight;
   DrawText(dc, AText.c_str(), AText.Length(), &tr, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
   tr.top = tr.bottom+FChart->TaskRowDistance;
   tr.bottom = tr.top + textHeight;
   AText = PrjFormatDate(ATask.StartDate);
   DrawText(dc, AText.c_str(), AText.Length(), &tr, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
   AText = PrjFormatDate(ATask.EndDate);
   DrawText(dc, AText.c_str(), AText.Length(), &tr, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);

   SelectObject(dc, oldFont);
   DeleteObject(Font);
   if(FProject->Selected == &ATask)
	  DrawFrame(dc, dr, TLGProject::dftFocus);
}
inline RECT TLGProject::Task_ClientRect(TTask&ATask)
{
   return ATask.LGRect;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLGProject::TaskLink_Draw(TTaskLink&ALink, HDC dc)
{
   POINT SubPoint;
   TColor AColor;
   int AWidth;
   if(ALink.Critical)
      AColor = FChart->KeyPathColor;
   else
      AColor = FChart->LineColor;
   AWidth = FChart->LineWidth;
   HPEN Pen = CreatePen(PS_SOLID, AWidth, AColor);
   HGDIOBJ oldPen = SelectObject(dc, Pen);
   HBRUSH Brush= CreateSolidBrush(AColor);
   HGDIOBJ oldBrush = SelectObject(dc, Brush);

   POINT First = TaskLink_FirstPoint(ALink);
   POINT Last = TaskLink_LastPoint(ALink);
   Last.x -= 8;
   MoveToEx(dc, First.x, First.y, NULL);
   LineTo(dc, Last.x, Last.y);//top
   POINT p[4];
   p[0].x = Last.x;
   p[0].y = Last.y - 2;
   p[1].x = Last.x;
   p[1].y = Last.y + 2;
   p[2].x = Last.x + 8;
   p[2].y = Last.y;
   p[3].x = Last.x;
   p[3].y = Last.y - 2;
   Polygon(dc, p, 4);

   SelectObject(dc, oldPen);
   DeleteObject(Pen);
   SelectObject(dc, oldBrush);
   DeleteObject(Brush);
}
inline RECT TLGProject::TaskLink_ClientRect(TTaskLink&ALink)
{
   POINT first = TaskLink_FirstPoint(ALink);
   POINT last = TaskLink_LastPoint(ALink);
   RECT r;
   r.left = first.x > last.x ? last.x : first.x;
   r.right = first.x > last.x ? first.x : last.x;
   r.top = first.y > last.y ? last.y : first.y;
   r.bottom = first.y > last.y ? first.y : last.y;
   return r;
}
inline POINT TLGProject::TaskLink_FirstPoint(TTaskLink&ALink)
{
   POINT r;
   if(ALink.Front)
   {
      r.x = ALink.Front->LGRect.right;
      r.y = (ALink.Front->LGRect.top+ALink.Front->LGRect.bottom)/2;
   }
   return r;
}
inline POINT TLGProject::TaskLink_LastPoint(TTaskLink&ALink)
{
   POINT r;
   if(ALink.Task)
   {
      r.x = ALink.Task->LGRect.left;
      r.y = (ALink.Task->LGRect.top+ALink.Task->LGRect.bottom)/2;
   }
   return r;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TLGProject::TLGProject(TLogicalChart* AChart)
{
    FCurrTask = NULL;
    FChart = AChart;
    FProject = new TProject();
    FMustDelete = true;
    FLGPrjDataChangeLink = new TLGPrjDataChangeLink(this);
    FUpdating = false;
}
__fastcall TLGProject::~TLGProject()
{
    if(FMustDelete)
       delete FProject;
    if(FLGPrjDataChangeLink)
	   delete FLGPrjDataChangeLink;
}
void TLGProject::Draw(HDC dc)
{
    FUpdating = true;
    if(!FCurrTask)
       return;
    Task_Draw(*FCurrTask, dc);
    for(int i = 0; i < FCurrTask->FrontTaskCount; i++)
       Task_Draw(*(FCurrTask->FrontTasks[i]->Front), dc);
    for(int i = 0; i < FCurrTask->LateTaskCount; i++)
       Task_Draw(*(FCurrTask->LateTasks[i]->Task), dc);
    for(int i = 0; i < FCurrTask->FrontTaskCount; i++)
       TaskLink_Draw(*(FCurrTask->FrontTasks[i]), dc);
    for(int i = 0; i < FCurrTask->LateTaskCount; i++)
       TaskLink_Draw(*(FCurrTask->LateTasks[i]), dc);
    FUpdating = false;
}
void __fastcall TLGProject::MouseDown(TMouseButton Button,
        Classes::TShiftState Shift, int X, int Y)
{
#define __TestTaskSelect do{\
                         r = Task_ClientRect(*t);\
                         if(X >= r.left && X <= r.right && Y >= r.top && Y <= r.bottom)\
                         {\
                            FProject->Selected = t;\
                            return;\
                         }\
                         }while(false)
    FUpdating = true;
    TTask* t;
    RECT r;
    try{
        //FProject->SelectTask = NULL;
        if(FCurrTask)
        {
           t = FCurrTask;
           __TestTaskSelect;
           for(int i = 0; i < FCurrTask->FrontTaskCount; i++)
           {
              t = FCurrTask->FrontTasks[i]->Front;
              __TestTaskSelect;
           }
           for(int i = 0; i < FCurrTask->LateTaskCount; i++)
           {
              t =  FCurrTask->LateTasks[i]->Task;
			  __TestTaskSelect;
           }
        }
    }__finally
    {
        FUpdating = false;
        FChart->Invalidate();
    }
}
void __fastcall TLGProject::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
}
void __fastcall TLGProject::MouseUp(TMouseButton Button, Classes::TShiftState Shift,
                                    int X, int Y)
{
}
inline RECT TLGProject::PointAtRect(int X, int Y)
{
    RECT r;
    r.left = X - X % (FChart->TaskWidth+FChart->ColDistance);
    r.left += FChart->ColDistance / 2;
    r.right = r.left + FChart->TaskWidth;
    r.top = Y - Y % (FChart->TaskHeight+FChart->RowDistance);
    r.top += FChart->RowDistance / 2;
    r.bottom = r.top + FChart->TaskHeight;
    return r;
}
inline POINT TLGProject::PointAtTaskPosition(int X, int Y)
{
    POINT r;
    r.x = X / (FChart->TaskWidth + FChart->ColDistance);
    r.y = Y / (FChart->TaskHeight + FChart->RowDistance);
    return r;
}
inline RECT TLGProject::PositionAtRect(int Left, int Top)
{
    RECT r;
    r.left = Left * (FChart->TaskWidth+FChart->ColDistance);
    r.right = r.left + FChart->TaskWidth+FChart->ColDistance;
    r.top = Top * (FChart->TaskHeight+FChart->RowDistance);
    r.bottom = r.top + FChart->TaskHeight+FChart->RowDistance;
    return r;
}
void TLGProject::DrawFrame(HDC dc, RECT dr, DrawFrameType Type)
{
   switch(Type)
   {
      case dftNormal:
      {
         HBRUSH Brush;
         HPEN Pen;
         HGDIOBJ oldPen, oldBrush;
         RECT tr;

         tr = dr;
         tr.bottom = (tr.top + tr.bottom) / 2;
         tr.left++;
         tr.right--;
         Brush = CreateSolidBrush(FChart->FSubRowColor1);
         oldBrush = SelectObject(dc, Brush);
         FillRect(dc, &tr, Brush);
         SelectObject(dc, oldBrush);
         DeleteObject(Brush);

         tr.top = tr.bottom;
         tr.bottom = dr.bottom-1;
         Brush = CreateSolidBrush(FChart->FSubRowColor2);
         oldBrush = SelectObject(dc, Brush);
         FillRect(dc, &tr, Brush);
         SelectObject(dc, oldBrush);
         DeleteObject(Brush);

         if(FChart->CrossLineWidth > 0)
         {
            Pen = CreatePen(PS_SOLID, FChart->CrossLineWidth, FChart->CrossLineColor);
            oldPen = SelectObject(dc, Pen);
            MoveToEx(dc, dr.left, (dr.top + dr.bottom)/2, NULL);
            LineTo(dc, dr.right, (dr.top + dr.bottom)/2);
            SelectObject(dc, oldPen);
            DeleteObject(Pen);
         }

         Brush = CreateSolidBrush(FChart->BackColor);
         Pen = CreatePen(PS_SOLID, FChart->BorderWidth, FChart->BorderColor);
         oldPen = SelectObject(dc, Pen);
         oldBrush = SelectObject(dc, Brush);
         MoveToEx(dc, dr.left, dr.top, NULL);
         LineTo(dc, dr.right, dr.top);
         LineTo(dc, dr.right, dr.bottom);
         LineTo(dc, dr.left, dr.bottom);
         LineTo(dc, dr.left, dr.top);
         //Rectangle(dc, dr.left, dr.top, dr.right, dr.bottom);
         SelectObject(dc, oldPen);
         DeleteObject(Pen);
         SelectObject(dc, oldBrush);
         DeleteObject(Brush);
         break;
      }
      case dftFocus:
      {
         HPEN Pen = CreatePen(PS_SOLID, FChart->FocusBorderWidth, FChart->FocusColor);
         HGDIOBJ oldPen = SelectObject(dc, Pen);
         POINT p[5];
         p[0].x = dr.left - 4;
         p[0].y = dr.top - 4;
         p[1].x = dr.right + 5;
         p[1].y = dr.top - 4;
         p[2].x = dr.right + 5;
         p[2].y = dr.bottom + 5;
         p[3].x = dr.left - 4;
         p[3].y = dr.bottom + 5;
         p[4].x = dr.left - 4;
         p[4].y = dr.top - 4;  
         Polyline(dc, p, 5);
         SelectObject(dc, oldPen);
         DeleteObject(Pen);
         break;
      }
      case dftMove:
      {
         HPEN Pen = CreatePen(PS_SOLID, 3, clGreen);
         HGDIOBJ oldPen = SelectObject(dc, Pen);
         MoveToEx(dc, dr.left-2, dr.top-2, NULL);
         LineTo(dc, dr.right+2, dr.top-2);//top
         LineTo(dc, dr.right+2, dr.bottom+2);//right
         LineTo(dc, dr.left-2, dr.bottom+2);//bottom
         LineTo(dc, dr.left-2, dr.top-2);//left
         SelectObject(dc, oldPen);
         DeleteObject(Pen);
         break;
      }
      default:
         throw Exception("任务框架类型未定义");
   }
}
void TLGProject::SetACurrTask(TTask*ATask)
{
    if(!ATask)
    {
        FCurrTask = NULL;
        return;
    }
    if(FChart->FTaskHeight == -1)
    {
        HDC dc = GetDC(FChart->Handle);
        FChart->FTaskHeight = FChart->CalcTaskHeight(dc);
        ReleaseDC(FChart->Handle, dc);
    }
    if(ATask->Index >= 0)
    {
       FCurrTask = ATask;
       int AHeight = 1;
       AHeight = FCurrTask->FrontTaskCount > AHeight ? FCurrTask->FrontTaskCount : AHeight;
       AHeight = FCurrTask->LateTaskCount > AHeight ? FCurrTask->LateTaskCount : AHeight;
       AHeight = FChart->ClientHeight > (AHeight * (FChart->FTaskHeight + FChart->FRowDistance)) ?
                 FChart->ClientHeight : (AHeight * (FChart->FTaskHeight + FChart->FRowDistance));
       RECT r;
       r.top = (AHeight - FChart->FTaskHeight) / 2;
       r.bottom = r.top + FChart->FTaskHeight;
       r.left = (FChart->ClientWidth - FChart->FTaskWidth) / 2;
       r.right = r.left + FChart->FTaskWidth;
       FCurrTask->LGRect = r;
       //前值任务
       if(FCurrTask->FrontTaskCount)
       {
           r.left = r.left - FChart->FTaskWidth - FChart->FColDistance;
           r.right = r.left + FChart->FTaskWidth;
           r.top = (AHeight - FCurrTask->FrontTaskCount * FChart->FTaskHeight -
                   (FCurrTask->FrontTaskCount-1) * FChart->FRowDistance) / 2;
           r.bottom = r.top + FChart->FTaskHeight;
           FCurrTask->FrontTasks[0]->Front->LGRect = r;
           for(int i=1; i < FCurrTask->FrontTaskCount; i++)
           {
               r.top = r.bottom + FChart->FRowDistance;
               r.bottom = r.top + FChart->FTaskHeight;
               FCurrTask->FrontTasks[i]->Front->LGRect = r;
           }
       }
       //后置任务
       if(FCurrTask->LateTaskCount)
       {
           r.left = FCurrTask->LGRect.right + FChart->FColDistance;
           r.right = r.left + FChart->FTaskWidth;
           r.top = (AHeight - FCurrTask->LateTaskCount * FChart->FTaskHeight -
                   (FCurrTask->LateTaskCount-1) * FChart->FRowDistance) / 2;
           r.bottom = r.top + FChart->FTaskHeight;
           FCurrTask->LateTasks[0]->Task->LGRect = r;
           for(int i=1; i < FCurrTask->LateTaskCount; i++)
           {
               r.top = r.bottom + FChart->FRowDistance;
               r.bottom = r.top + FChart->FTaskHeight;
               FCurrTask->LateTasks[i]->Task->LGRect = r;
           }
       }
       FChart->AdjustScrollBar();
       FChart->Invalidate();
    }
}
void TLGProject::SetCurrTask(String AID)
{
   SetACurrTask(FProject->TaskByID(AID));
}
inline int TLGProject::MaxHeight()
{
   if(FCurrTask)
   {
      int FrontHeight = FCurrTask->FrontTaskCount * (FChart->FTaskHeight + FChart->FRowDistance);
      int LateHeight = FCurrTask->LateTaskCount * (FChart->FTaskHeight + FChart->FRowDistance);
      return FrontHeight > LateHeight ? FrontHeight : LateHeight;
   }
   return 0;
}
void __fastcall TLGProject::SetProject(TProject*AProject)
{
   if(FMustDelete)
   {
      delete FProject;
      FMustDelete = false;
   }
   if(FProject != AProject)
   {
      FProject = AProject;
      FLGPrjDataChangeLink->SetProject(FProject);
   }
}  
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall TLogicalChart::TLogicalChart(TComponent* Owner)
        : TWinControl(Owner)
{
    TControlStyle cs;
    cs<<csAcceptsControls<<csCaptureMouse<<csClickEvents<<
         csSetCaption<<csDoubleClicks<<csMenuEvents;
    this->ControlStyle = cs;

    FPrintHandle = NULL;
    FProject = new TLGProject(this);

    FTaskHeight = -1;
    FTaskWidth = 140;
    FColDistance = 40;
    FRowDistance = 40;
    FTaskRowDistance = 4;
    Width = 200;
    Height = 180;
    Color = clWhite;
    FBorderWidth = 1;
    FFocusBorderWidth = 2;
    FLineWidth = 1;
    FFocusLineWidth = 2;
    FCrossLineWidth = 1;
    FBackColor = clWhite;
    FBorderColor = (TColor)RGB(255, 128, 0);
    FFocusColor = (TColor)RGB(64, 128, 128);
    FLineColor = (TColor)RGB(255, 128, 0);
    FFocusLineColor = (TColor)RGB(64, 128, 128);
    FKeyPathColor = (TColor)RGB(0, 0, 255);
    FSubRowColor1 = (TColor)RGB(205, 252, 214);
    FSubRowColor2 = (TColor)RGB(227, 231, 253);
    FCrossLineColor = (TColor)RGB(248, 234, 133);

    FHORZ.cbSize = sizeof(SCROLLINFO);
    FHORZ.fMask = SIF_DISABLENOSCROLL;
    FHORZ.nMin = 0;
    FHORZ.nMax = Width;
    FVERT.cbSize = sizeof(SCROLLINFO);
    FVERT.fMask = SIF_DISABLENOSCROLL;
    FVERT.nMin = 0;
    FVERT.nMax = Height;
}
//---------------------------------------------------------------------------
__fastcall TLogicalChart::~TLogicalChart()
{
    delete FProject;
    if(FPrintHandle)
    {
	   delete ((TLogicalChartPrint*)(FPrintHandle));
    }
}
//---------------------------------------------------------------------------
void __fastcall TLogicalChart::PaintWindow(HDC DC)
{
    if(FTaskHeight == -1)
       FTaskHeight = CalcTaskHeight(DC);
    RECT dr = ClientRect;
    dr.left += FHORZ.nPos;
    dr.right += FHORZ.nPos;
    dr.top += FVERT.nPos;
    dr.bottom += FVERT.nPos;
    SetBkMode(DC, TRANSPARENT);
    SetViewportOrgEx(DC, 0, -FVERT.nPos, NULL);
    if(FProject->CurrTask)
        FProject->Draw(DC);
}
HDC TLogicalChart::GetDrawDc()
{
    HDC dc = GetDC(Handle);
    SetViewportOrgEx(dc, 0, -FVERT.nPos, NULL);
    return dc;
}
void __fastcall TLogicalChart::WMPaint(Messages::TWMPaint &Message)
{
   ControlState << csCustomPaint;
   TWinControl::Dispatch(&Message);
   ControlState >> csCustomPaint;
}
void __fastcall TLogicalChart::WMHScroll(Messages::TMessage &Message)
{
//   int xDelta;     // xDelta = new_pos - current_pos
   int xNewPos;    // new position
   switch(Message.WParamLo)
   {
        // User clicked the shaft left of the scroll box.
        case SB_PAGELEFT:
            xNewPos = FHORZ.nPos - 1;
            break;
        // User clicked the shaft right of the scroll box.
        case SB_PAGERIGHT:
            xNewPos = FHORZ.nPos + 1;
            break;
        // User clicked the left arrow.
        case SB_LINELEFT:
            xNewPos = FHORZ.nPos - 1;
            break;
        // User clicked the right arrow.
        case SB_LINERIGHT:
            xNewPos = FHORZ.nPos + 1;
            break;
        // User dragged the scroll box.
        case SB_THUMBPOSITION:
            xNewPos = Message.WParamHi;
            break;
        case SB_THUMBTRACK:
            xNewPos = Message.WParamHi;
            break;
        case SB_ENDSCROLL:
            xNewPos = FHORZ.nPos;
            break;
        case SB_LEFT:
            xNewPos = FHORZ.nMin;
            break;
        case SB_RIGHT:
            xNewPos = FHORZ.nMax;
            break;
        default:
            xNewPos = FHORZ.nPos;
   }
   // New position must be between 0 and the screen width.
   xNewPos = xNewPos > FHORZ.nMin ? xNewPos : FHORZ.nMin;
   xNewPos = xNewPos < FHORZ.nMax ? xNewPos : FHORZ.nMax;
   if(xNewPos < 0)
      xNewPos = 0;
   if(xNewPos >= FProject->Project->Tasks.Count())
      xNewPos = FProject->Project->Tasks.Count()-1;
   // If the current position does not change, do not scroll.
//   xDelta = xNewPos - FHORZ.nPos;
   // Reset the current scroll position.
   FHORZ.nPos = xNewPos;
//   ScrollWindow(Handle, -xDelta, 0, NULL, NULL);
//   UpdateWindow(Handle);
   FProject->CurrTask = FProject->Project->Tasks[xNewPos];
   // Reset the scroll bar.
   SetScrollPos(Handle, SB_HORZ, xNewPos, true);
}
void __fastcall TLogicalChart::WMVScroll(Messages::TMessage &Message)
{
   int yDelta;     // xDelta = new_pos - current_pos
   int yNewPos;    // new position
   switch(Message.WParamLo)
   {
        // User clicked the shaft left of the scroll box.
        case SB_PAGEUP:
            yNewPos = FVERT.nPos - ClientHeight;
            break;
        // User clicked the shaft right of the scroll box.
        case SB_PAGEDOWN:
            yNewPos = FVERT.nPos + ClientHeight;
            break;
        // User clicked the left arrow.
        case SB_LINEUP:
            yNewPos = FVERT.nPos - 20;
            break;
        // User clicked the right arrow.
        case SB_LINEDOWN:
            yNewPos = FVERT.nPos + 20;
            break;
        // User dragged the scroll box.
        case SB_THUMBPOSITION:
            yNewPos = Message.WParamHi;
            break;
        case SB_THUMBTRACK:
            yNewPos = Message.WParamHi;
            break;
        case SB_ENDSCROLL:
            yNewPos = FVERT.nPos;
            break;
        case SB_TOP:
            yNewPos = FVERT.nMin;
            break;
        case SB_BOTTOM:
            yNewPos = FVERT.nMax;
            break;
        default:
            yNewPos = FVERT.nPos;
   }
   // New position must be between 0 and the screen width.
   yNewPos = yNewPos > FVERT.nMin ? yNewPos : FVERT.nMin;
   yNewPos = yNewPos < FVERT.nMax ? yNewPos : FVERT.nMax;
   // If the current position does not change, do not scroll.
   yDelta = yNewPos - FVERT.nPos;
   // Reset the current scroll position.
   FVERT.nPos = yNewPos;
   ScrollWindow(Handle, 0, -yDelta, NULL, NULL);
   UpdateWindow(Handle);
   // Reset the scroll bar.
   SetScrollPos(Handle, SB_VERT, yNewPos, true);
//   Invalidate();
}
void __fastcall TLogicalChart::WMKeyDown(Messages::TWMKey &Message)
{
   TWinControl::Dispatch(&Message);
}
void __fastcall TLogicalChart::WMKeyUp(Messages::TWMKey &Message)
{
   TWinControl::Dispatch(&Message);
}
void __fastcall TLogicalChart::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FProject->MouseDown(Button, Shift, X+FHORZ.nPos, Y+FVERT.nPos);
   SetFocus();
}
void __fastcall TLogicalChart::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FProject->MouseMove(Shift, X+FHORZ.nPos, Y+FVERT.nPos);
}
void __fastcall TLogicalChart::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FProject->MouseUp(Button, Shift, X+FHORZ.nPos, Y+FVERT.nPos);
   if(Button == mbRight)
   {
      POINT point;
      GetCursorPos(&point);
      if(FTaskPopMenu && FProject->Project->Selected)
         FTaskPopMenu->Popup(point.x, point.y);
      else if(FNoneTaskPopMenu)
         FNoneTaskPopMenu->Popup(point.x, point.y);
   }
}
void __fastcall TLogicalChart::Click(void)
{
   if(FOnTaskClick && FProject->Project->Selected)
      FOnTaskClick(FProject->Project, FProject->Project->Selected);
}
/*void __fastcall TLogicalChart::WMDblClick(Messages::TMessage &Message)
{
   TWinControl::Dispatch(&Message);
   MyDblClick();
} */
void __fastcall TLogicalChart::DblClick(void)
{
   TWinControl::DblClick();
   if(FOnTaskDblClick && FProject->Project->Selected)
      FOnTaskDblClick(FProject->Project, FProject->Project->Selected);
}
void __fastcall TLogicalChart::AdjustSize(void)
{
   TWinControl::AdjustSize();
   if(FProject->Project->Tasks.Count() > 0)
      FProject->CurrTask = FProject->CurrTask;
   AdjustScrollBar();
}
void TLogicalChart::AdjustScrollBar()
{
    FHORZ.fMask = SIF_ALL;
    FHORZ.nMin = 0;
    FHORZ.nPage = 1;
    FHORZ.nMax = FProject->Project->Tasks.Count()-1;
    if(FProject->FCurrTask)
       FHORZ.nPos = FProject->Project->Tasks.TaskIndexOf(*(FProject->FCurrTask));
    SetScrollInfo(Handle, SB_HORZ, &FHORZ, true);

    FVERT.fMask = SIF_ALL;
    FVERT.nMin = 0;
    FVERT.nPage = 20;
    FVERT.nMax = FProject->MaxHeight() - ClientRect.Height() + FRowDistance / 2;
    SetScrollInfo(Handle, SB_VERT, &FVERT, true);
}
int TLogicalChart::CalcTaskHeight(HDC dc)
{
   HFONT Font = CreateFontByTFont(FProject->Chart->Font);
   HGDIOBJ oldFont = SelectObject(dc, Font);
   int ATextHeight = TextHeight(dc, "AText");
   SelectObject(dc, oldFont);
   DeleteObject(Font);

   return ATextHeight*2 + FTaskRowDistance*3;
}
TProject* __fastcall TLogicalChart::GetProject()
{
   return FProject->Project;
}
void __fastcall TLogicalChart::SetProject(TProject*AProject)
{
   FProject->Project = AProject;
}
TPrintHandle __fastcall TLogicalChart::GetPrintHandle()
{
    if(FPrintHandle)
    {
    }else
    {
	   FPrintHandle = new TLogicalChartPrint(this);
    }
    return FPrintHandle;
}
TTask* __fastcall TLogicalChart::GetCurrTask()
{
   return FProject->CurrTask;
}
void __fastcall TLogicalChart::SetCurrTask(TTask*ATask)
{
   FProject->CurrTask = ATask;
}
void TLogicalChart::Draw(HDC dc)
{
   FProject->Draw(dc);
}
void TLogicalChart::SetCurrTask(String AID)
{
   FProject->SetCurrTask(AID);
}
void __fastcall TLogicalChart::SetTaskWidth(int AWidth)
{
    if(AWidth >= 40)
    {
       FTaskWidth = AWidth;
       Invalidate();
    }
}
void __fastcall TLogicalChart::SetBackColor(TColor AColor)
{
    FBackColor = AColor;
    Invalidate();
}
void __fastcall TLogicalChart::SetBorderColor(TColor AColor)
{
    FBorderColor = AColor;
    Invalidate();
}
void __fastcall TLogicalChart::SetLineColor(TColor AColor)
{
    FLineColor = AColor;
    Invalidate();
}
void __fastcall TLogicalChart::SetFocusColor(TColor AColor)
{
    FFocusColor = AColor;
    Invalidate();
}
void __fastcall TLogicalChart::SetFocusLineColor(TColor AColor)
{
    FFocusLineColor = AColor;
    Invalidate();
}
void __fastcall TLogicalChart::SetBorderWidth(int AWidth)
{
    FBorderWidth = AWidth;
    Invalidate();
}
void __fastcall TLogicalChart::SetFocusBorderWidth(int AWidth)
{
    FFocusBorderWidth = AWidth;
    Invalidate();
}
void __fastcall TLogicalChart::SetLineWidth(int AWidth)
{
    FLineWidth = AWidth;
    Invalidate();
}
void __fastcall TLogicalChart::SetFocusLineWidth(int AWidth)
{
    FFocusLineWidth = AWidth;
    Invalidate();
}
void __fastcall TLogicalChart::SetCrossLineColor(TColor AColor)
{
    FCrossLineColor = AColor;
    Invalidate();
}
void __fastcall TLogicalChart::SetTaskRowDistance(int AWidth)
{
    FTaskRowDistance = AWidth;
    FTaskHeight = -1;
    Invalidate();
}
void __fastcall TLogicalChart::SetColDistance(int AWidth)
{
    FColDistance = AWidth;
    Invalidate();
}
void __fastcall TLogicalChart::SetRowDistance(int AHeight)
{
    FRowDistance = AHeight;
    Invalidate();
}
void __fastcall TLogicalChart::SetCrossLineWidth(int AWidth)
{
    FCrossLineWidth = AWidth;
    Invalidate();
}
void __fastcall TLogicalChart::SetKeyPathColor(TColor AColor)
{
    FKeyPathColor = AColor;
    Invalidate();
}
