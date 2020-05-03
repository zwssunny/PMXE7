//---------------------------------------------------------------------------
//    File:               Gantt.cpp,Gantt.h
//    Function:           甘特图
//    Author:             Sunny Zhan
//    Last Modify:        2009-05-12
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Gantt.h"
#include "PrjGrid.h"
#include "Vclcomfunc.h"
#include "CopyRight.h"
#include "ZChartPrint.h"
#include <ToolsApi.hpp>
#pragma package(smart_init)

using namespace Vclcomfunc;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

namespace Gantt
{
        void __fastcall PACKAGE Register()
        {
				SplashScreenServices->AddPluginBitmap("Foresight Software",LoadBitmap(HInstance, L"SPLASH_ICON"));
				 TComponentClass classes[1] = {__classid(TGantt)};
				 RegisterComponents("ZChart", classes, 0);
        }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class PACKAGE TGanttProject
{
    friend TGantt;
    enum GanttAct {naNone, naDragTask};
    struct TObjDrawInfo{
          int StartX1;
          int EndX1;
          int StartX2;
          int EndX2;
          int BaseStartX;
          int BaseEndX;
          int Y;
    };
private:
    void Task_Draw(TPrjObject&ATask, HDC dc);
    T3BarDraw& ObjectBarDraw(TPrjObject&AObj);
    void ObjectDrawInfo(TObjDrawInfo&Info, TPrjObject&AObj);
    void TaskLink_Draw(TTaskLink&ALink, HDC dc);
private:
        TProject* FProject;
        bool FMustDelete;
        GanttAct FAct;
        TPrjDataChangeLink * FGTPrjDataChangeLink;
        bool FUpdating;
        bool FShowBasePlan;
        TDateTime FStateDate;
        int YAtRow(int Y);
        inline TPrjObject* YAtTask(int Y);
        TDateTime XAtDay(int X);
        inline int GetDayLeft(const TDateTime &adt);
        inline int GetDayRight(const TDateTime &adt);
        TPrjObject* __fastcall GetTopTask();
        void __fastcall SetTopTask(TPrjObject*ATask);
        TDateTime __fastcall GetLeftDay();
		void __fastcall SetLeftDay(TDateTime ADate);
		void __fastcall SetProject(TProject* AProject);
        POINT StatePointByObject(TPrjObject * obj);
protected:
        TGantt* FChart;
        void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
        void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
        void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
public:
        __fastcall TGanttProject(TGantt* AChart);
        virtual __fastcall ~TGanttProject();
        void __fastcall SetStateDate();
        void AutoAlign();
        void Draw(HDC dc, RECT dr);
        void DrawCalendar(HDC dc, int ALeft, int AWidth, int LineHeight);
        void DrawProgressLine(HDC dc,RECT dr);
        void DrawPgViewLine(HDC dc,RECT dr);
        void DrawHLine(HDC dc, RECT rect);
        TCalendarDraw Calendar;

        T3BarDraw  NotStartDraw;//未开工
        T3BarDraw  CriticalNotStartDraw;//未开工
        T3BarDraw  StartedDraw;//已开工
        T3BarDraw  CriticalStartedDraw;//已开工
        T3BarDraw  OveredDraw;//已完工
        T3BarDraw  CriticalOveredDraw;//已完工
        T3BarDraw  AbstractDraw;//摘要任务
        T3BarDraw  MarkerDraw;//里程碑
        T3BarDraw  MarkerOverDraw;//里程碑
        T3BarDraw  WarningDraw;//有问题任务
        T3BarDraw  ForeignNotStartDraw;//外部未开工
        T3BarDraw  CriticalForeignNotStartDraw;//外部未开工
        T3BarDraw  ForeignStartedDraw;//外部已开工
        T3BarDraw  CriticalForeignStartedDraw;//外部已开工
        T3BarDraw  ForeignOveredDraw;//外部已完工
        T3BarDraw  CriticalForeignOveredDraw;//外部已完工
        T3BarDraw  ForeignAbstractDraw;//外部摘要任务
        T3BarDraw  ForeignMarkerDraw;//外部里程碑
        T3BarDraw  ForeignMarkerOverDraw;//外部里程碑
        T3BarDraw  ForeignProjectDraw;//外部工程

        TGTLinkDraw CriticalLinkDraw;
        TGTLinkDraw NormalLinkDraw;

        TTaskShowString FrontShowString;
        TTaskShowString LateShowString;


        __property TProject* Project = {read=FProject, write=SetProject};
        __property TGantt* Chart = {read=FChart};
        __property TPrjObject* TopTask = {read=GetTopTask, write=SetTopTask};
        __property TDateTime LeftDay = {read=GetLeftDay, write=SetLeftDay};
        __property bool Updating = {read=FUpdating, write=FUpdating};
        __property bool ShowBasePlan  = { read=FShowBasePlan, write=FShowBasePlan };
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TGTPrjDataChangeLink : public TPrjDataChangeLink
{
public:
    TGanttProject* FGTProject;
    TGTPrjDataChangeLink(TGanttProject*AProject)
	   :TPrjDataChangeLink(AProject->Project) { FGTProject = AProject; }

    virtual void AfterProjectChange()
    {
       if(!FGTProject->Chart->Visible&&!FGTProject->Project->NeedEditStatus)
          return;
       if(!(FGTProject->Updating))
          FGTProject->Chart->Invalidate();
    }
    virtual void BeforeTaskChange(TPrjObject*ATask){}
    virtual void AfterTaskChange(TPrjObject*ATask)
    {
       if(!FGTProject->Chart->Visible&&!FGTProject->Project->NeedEditStatus)
          return;
       if(!(FGTProject->Updating))
       {
          FGTProject->AutoAlign();
       }
    }
    virtual void BeforeTaskDelete(TPrjObject*ATask)
    {
    }
    virtual void AfterTaskDelete()
    {
       if(!FGTProject->Chart->Visible)
          return;
       if(!(FGTProject->Updating))
          FGTProject->Chart->Invalidate();
    }
    virtual void AfterTaskAdd(TPrjObject*ATask)
    {
       if(!FGTProject->Chart->Visible&&!FGTProject->Project->NeedEditStatus)
          return;
       if(!(FGTProject->Updating))
          FGTProject->AutoAlign();
    }
    virtual void BeforeTaskLinkChange(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkChange(TTaskLink*ATaskLink)
    {
       if(!FGTProject->Chart->Visible&&!FGTProject->Project->NeedEditStatus)
          return;
       if(!(FGTProject->Updating))
          FGTProject->Chart->Invalidate();
    }
    virtual void BeforeTaskLinkDelete(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkAdd(TTaskLink*ATaskLink)
    {
       if(!FGTProject->Chart->Visible&&!FGTProject->Project->NeedEditStatus)
          return;
       if(!(FGTProject->Updating))
          FGTProject->Chart->Invalidate();
    }
    virtual void BeginUpdate(){}
    virtual void EndUpdate()
    {
//          FGTProject->Chart->Invalidate();
       if(!(FGTProject->Updating))
            FGTProject->AutoAlign();
    }
    virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect)
    {
       if(FGTProject->Chart->OnTaskSelect)
       {
          //FGTProject->Chart->OnTaskSelect(FProject, FProject->SelectTask);
       }
       if(!FGTProject->Chart->Visible)
          return;
       if(!(FGTProject->Updating))
       {
          FGTProject->Chart->Invalidate();
       }
    }
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TGanttProject::Task_Draw(TPrjObject&AObj, HDC dc)
{
   T3BarDraw& Draw = ObjectBarDraw(AObj);
   Draw.BaseDraw=FShowBasePlan;
   TObjDrawInfo Info;
   ObjectDrawInfo(Info, AObj);
   Draw.Draw(dc, Info.StartX1, Info.EndX1, Info.StartX2, Info.EndX2, Info.BaseStartX,Info.BaseEndX,Info.Y);
   RECT dr;
   //画完成百分比
   if(FShowBasePlan)
   {
    String str=FloatToStr(AObj.TaskPctPercent)+"%";
     dr.left = Info.StartX1;
     dr.right = Info.EndX1;
     dr.top = Info.Y - 20;
     dr.bottom = Info.Y ;
	 DrawText(dc, str.c_str(), str.Length(), &dr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
   }
   //FrontString
   String str = FrontShowString.GetShowString(AObj);
   dr.right = Info.StartX1;
   if(Info.StartX2 > 10)
   {
       dr.right = dr.right > Info.StartX2 ? Info.StartX2 : dr.right;
   }
   dr.left = 0;
   dr.right -= 15;
   dr.top = Info.Y - 50;
   dr.bottom = Info.Y + 50;
   DrawText(dc, str.c_str(), str.Length(), &dr, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
   //LateString
      //停复工标志
   str = "";
   switch(AObj.StopFlag )
   {
     case 1:
       str += "×";
       break;
     case 2:
       str += "√";
       break;
   }

   str += LateShowString.GetShowString(AObj);
   switch(AObj.VitalLevel)
   {
     case 1:
       str += "●";
       break;
     case 2:
       str += "★";
       break;
   }
   dr.left = Info.EndX1;
   if(Info.EndX2 > 10)
   {
       dr.left = dr.left < Info.EndX2 ? Info.EndX2 : dr.left;
   }
   dr.left += 15;
   dr.right = dr.left + 10000;
   dr.top = Info.Y - 50;
   dr.bottom = Info.Y + 50;
   DrawText(dc, str.c_str(), str.Length(), &dr, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}
//---------------------------------------------------------------------------
T3BarDraw& TGanttProject::ObjectBarDraw(TPrjObject&AObj)
{
   if(AObj.IsForeign())
   {//外部工程
        switch(AObj.GetType())
        {
             case ttProject:
                  throw Exception("任务类型错误");
             case ttAbstractTask:
                  return ForeignAbstractDraw;
             case ttTask:
                  if(AObj.MileStone)
                  {
                      return AObj.TaskStatus==tsOvered ? ForeignMarkerOverDraw : ForeignMarkerDraw;
                  }
                  switch(AObj.TaskStatus)
                  {
                      case tsNotStart:
                          return AObj.Critical ? CriticalForeignNotStartDraw : ForeignNotStartDraw;
                      case tsStarted:
                          return AObj.Critical ? CriticalForeignStartedDraw : ForeignStartedDraw;
                      case tsOvered:
                          return AObj.Critical ? CriticalForeignOveredDraw : ForeignOveredDraw;
                      default:
                          throw Exception("任务状态错误");
                  }
             case ttForeignProject:
                  return ForeignProjectDraw;
             default:
                  throw Exception("任务类型未定义");
        }
   }else
   {//
        switch(AObj.GetType())
        {
             case ttProject:
                  throw Exception("任务类型错误");
             case ttAbstractTask:
                  return AbstractDraw;
             case ttTask:
                  if(AObj.MileStone)
                  {
                      return AObj.TaskStatus==tsOvered ? MarkerOverDraw : MarkerDraw;
                  }
                  if(FChart->ShowWarning &&(AObj.TaskStatus!=tsOvered)&&(AObj.CostDays>0)&&
                       (AObj.FactCostDays/AObj.CostDays*100.0 -AObj.TaskPctPercent) >= FProject->StatError)
                  {//警报(计划应完成工程量-实际完成工程量)/计划应完成量%>=容许范围%
                   //且未完工
                      return WarningDraw;
                  }
                  switch(AObj.TaskStatus)
                  {
                      case tsNotStart:
                          return AObj.Critical ? CriticalNotStartDraw : NotStartDraw;
                      case tsStarted:
                          return AObj.Critical ? CriticalStartedDraw : StartedDraw;
                      case tsOvered:
                          return AObj.Critical ? CriticalOveredDraw : OveredDraw;
                      default:
                          throw Exception("任务状态错误");
                  }
             case ttForeignProject:
                  return ForeignProjectDraw;
             default:
                  throw Exception("任务类型未定义");
        }
   }
}
//---------------------------------------------------------------------------
void TGanttProject::ObjectDrawInfo(TObjDrawInfo&Info, TPrjObject&AObj)
{
   //当前计划
   Info.StartX1 = GetDayLeft(AObj.StartDate);
   if(AObj.CostDays > 0)
      Info.EndX1 = GetDayRight(AObj.EndDate);
   else
      Info.EndX1 = Info.StartX1;
   //基准计划
   if(FShowBasePlan)
   {
   Info.BaseStartX = GetDayLeft(AObj.BStartDate);
   if(AObj.BCostDays > 0)
      Info.BaseEndX = GetDayRight(AObj.BEndDate);
   else
      Info.BaseEndX = Info.BaseStartX;
    }
   //当前进度
   if(int(AObj.FactStartDate)>5)
	Info.StartX2 = GetDayLeft(AObj.FactStartDate);
   else
	Info.StartX2 = Info.StartX1;
   Info.EndX2 = Info.StartX2;
   if(AObj.FactCostDays > 0)
   {
	  if((AObj.TaskStatus==tsOvered)&&(int(AObj.FactEndDate) > 5))
		  Info.EndX2 = GetDayRight(AObj.FactEndDate);
	  else if((AObj.TaskStatus==tsStarted)&&(int(AObj.ProcessDate) > 5))
		  Info.EndX2 = GetDayRight(AObj.ProcessDate);
	  // else if((AObj.TaskStatus==tsPaused)&&(int(AObj.PausedDate) > 5))考虑停工/复工
   }
   Info.Y = AObj.EFExpandIndex * FChart->FRowHeight +
            FChart->FCalendarHeight + FChart->FRowHeight / 2;
}
POINT TGanttProject::StatePointByObject(TPrjObject * obj)
{
        POINT p;
        p.y= obj->EFExpandIndex * FChart->FRowHeight +
            FChart->FCalendarHeight + FChart->FRowHeight / 3;
        int mx=GetDayLeft(obj->StartDate);
        p.x=GetDayRight(FStateDate);
        //下面均考虑手动设置完工的情况
        if(obj->EndDate<=FStateDate)
        {
            //未完工
           if(obj->TaskStatus!=tsOvered&&obj->TaskPctPercent<(100-FProject->StatError))
              p.x=(GetDayRight(obj->EndDate)-mx)*obj->TaskPctPercent/100+mx;

        }
        else if(obj->EndDate>FStateDate&&FStateDate>=obj->StartDate)
        {
             if(obj->TaskStatus!=tsOvered) //未完工
                p.x=(GetDayRight(obj->EndDate)-mx)*obj->TaskPctPercent/100+mx;
             else   //已完工
               {
                   if(obj->MileStone) //是里程碑
                    p.x=GetDayLeft(obj->EndDate);
                   else
                    p.x=GetDayRight(obj->EndDate);
                 }
        }
        else  //(obj->StartDate>StateDate)
        {
            //未完工且有进度
         if(obj->TaskStatus!=tsOvered&&obj->TaskPctPercent>0.0001)
             p.x=(GetDayRight(obj->EndDate)-mx)*obj->TaskPctPercent/100+mx;
          else if(obj->TaskStatus==tsOvered)  //已完工
             {
               if(obj->MileStone)
                p.x=GetDayLeft(obj->EndDate);
               else
				p.x=GetDayRight(obj->EndDate);
             }
        }
        return p;
}
void __fastcall TGanttProject::SetStateDate()
{
   switch(FChart->StateDateType)
   {
     case sdtCurrentDate:
          FStateDate= Date();
          break;
     case sdtManualDate:
          FStateDate= FChart->ManualStateDate;
          break;
     default: FStateDate= FProject->StateDate;     //case sdtPrjProgressDate:
   }
}
//---------------------------------------------------------------------------
//TGTTaskLink
//---------------------------------------------------------------------------
void TGanttProject::TaskLink_Draw(TTaskLink&ALink, HDC dc)
{
   TObjDrawInfo InfoTask, InfoFront;
   T3BarDraw & TaskBarDraw = ObjectBarDraw(*(ALink.Task));
   T3BarDraw & FrontBarDraw = ObjectBarDraw(*(ALink.Front));
   ObjectDrawInfo(InfoTask, *(ALink.Task));
   ObjectDrawInfo(InfoFront, *(ALink.Front));
   TGTLinkDraw & LinkDraw = ALink.Critical ? CriticalLinkDraw : NormalLinkDraw;
   int TopBottomInc = FChart->RowHeight / 2;//画折线时离中心

   LinkDraw.Draw(dc, FrontBarDraw.Bar1,
                     FrontBarDraw.Bar2Draw ? &FrontBarDraw.Bar2 : NULL,
                     InfoFront.StartX1, InfoFront.EndX1,
                     InfoFront.StartX2, InfoFront.EndX2,
                     InfoFront.Y,
                     InfoFront.Y - TopBottomInc, InfoFront.Y + TopBottomInc,

                     TaskBarDraw.Bar1,
                     TaskBarDraw.Bar2Draw ? &TaskBarDraw.Bar2 : NULL, 
                     InfoTask.StartX1, InfoTask.EndX1,
                     InfoTask.StartX2, InfoTask.EndX2,
                     InfoTask.Y,

                     ALink.Type);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TGanttProject::TGanttProject(TGantt* AChart)
{
    FChart = AChart;
    FAct = naNone;
    FProject = new TProject();
    FMustDelete = true;
    FGTPrjDataChangeLink = new TGTPrjDataChangeLink(this);
    FUpdating = false;
    FShowBasePlan=false;
}
//---------------------------------------------------------------------------
__fastcall TGanttProject::~TGanttProject()
{
    if(FMustDelete)
        delete FProject;
    if(FGTPrjDataChangeLink)
        delete FGTPrjDataChangeLink;
}
//---------------------------------------------------------------------------
void TGanttProject::Draw(HDC dc, RECT dr)
{
    FUpdating = true;
    TPrjObject* t;
    RECT r;
    HFONT aFont = CreateFontByTFont(FChart->Font);
    HGDIOBJ oldFont = SelectObject(dc, aFont);
    int top = (dr.top - FChart->FCalendarHeight)/FChart->FRowHeight;
    int bottom = (dr.bottom - FChart->FCalendarHeight)/FChart->FRowHeight + 1;
    try{
        for(int i = top; i <= bottom && i < FProject->ExpandFoldTasks.Count(); i++)
        {
            if(i >= 0)
            {
                t = FProject->ExpandFoldTasks[i];
                Task_Draw(*t, dc);
            }
        }
    }__finally
    {
        SelectObject(dc, oldFont);
        DeleteObject(aFont);
        FUpdating = false;
    }
    if(FChart->FShowLine)
    {
		TTaskLink* tl;
        for(int i = 0; i < FProject->TaskLinks.Count(); i++)
        {
            tl = FProject->TaskLinks[i];
            if(tl->Task && tl->Front &&
               tl->Task->EFExpandIndex >= 0 && tl->Front->EFExpandIndex >= 0)
            {
                if((tl->Task->EFExpandIndex >= top && tl->Front->EFExpandIndex <= bottom) ||
                   (tl->Task->EFExpandIndex <= bottom && tl->Front->EFExpandIndex >= top))
                {                          
                    TaskLink_Draw(*tl, dc);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void TGanttProject::DrawCalendar(HDC dc, int ALeft, int AWidth, int LineHeight)
{
	HFONT font = CreateFontByTFont(FChart->Font);
    HGDIOBJ oldfont = SelectObject(dc, font);

    RECT rect;
    rect.left = ALeft;
    rect.right = rect.left + AWidth;
    rect.top = 0;
    rect.bottom = FChart->CalendarHeight;
	  Calendar.Draw(dc, rect, LineHeight);
    //画休息日底图

    SelectObject(dc, oldfont);
    DeleteObject(font);
}
void TGanttProject::DrawHLine(HDC dc, RECT rect)
{
   HPEN  line2pen = CreatePen(PS_SOLID, 1, Calendar.Line2Color);
   HGDIOBJ aoldpen = SelectObject(dc, line2pen);
   int iStepHeight=FChart->FRowHeight;
   int itop=rect.top;
   while(itop<=rect.bottom)
   {
    MoveToEx(dc, rect.left, itop, NULL);
    LineTo(dc, rect.right, itop);
    itop+=iStepHeight;
   }
    SelectObject(dc, aoldpen);
}
//---------------------------------------------------------------------------
void TGanttProject::DrawPgViewLine(HDC dc,RECT dr)
{
    int Xp=GetDayRight(FStateDate);
    int  Yp =dr.top;
    HPEN  linepen = CreatePen(PS_SOLID, 1, FChart->PgViewLineColor);
    HGDIOBJ aoldpen = SelectObject(dc, linepen);
    SelectObject(dc,linepen);
    Xp=Xp+1;//错开前锋线

    MoveToEx(dc,Xp,Yp,NULL);
    LineTo(dc,Xp,dr.bottom);

    DeleteObject(linepen);
    SelectObject(dc, aoldpen);

}
void TGanttProject::DrawProgressLine(HDC dc,RECT dr)
{
    int Xp=GetDayRight(FStateDate);
    int  Yp =dr.top;// FChart->FCalendarHeight;// + FChart->FRowHeight / 2;
    HPEN  linepen = CreatePen(PS_SOLID, 1, FChart->ProgressLineColor);
    HGDIOBJ aoldpen = SelectObject(dc, linepen);

    TPrjObject* t;
    POINT p;
    RECT rect;
    int Radial=4;

    int top = (dr.top - FChart->FCalendarHeight)/FChart->FRowHeight;
    int bottom = (dr.bottom - FChart->FCalendarHeight)/FChart->FRowHeight + 1;
    MoveToEx(dc, Xp, Yp, NULL);

    for(int i = top; i <= bottom && i < FProject->ExpandFoldTasks.Count(); i++)
       {
            if(i >= 0)
            {
                t = FProject->ExpandFoldTasks[i];
                p=StatePointByObject(t);
                //先画个小圆
               if(p.x!=Xp)//在观察线上不画
               {
                   rect.left = p.x - Radial;
                   rect.top = p.y - Radial;
                   rect.right = p.x + Radial;
                   rect.bottom = p.y + Radial;
                   Ellipse(dc, rect.left, rect.top, rect.right+1, rect.bottom+1);
               }
               //再画条线
                LineTo(dc,p.x,p.y);
                p.x=Xp;
                p.y= (t->EFExpandIndex+1) * FChart->FRowHeight +
                     FChart->FCalendarHeight;
               //再画回观察线
                LineTo(dc,p.x,p.y);
          }
        }
    if(p.y<dr.bottom)
    {
        p.x=Xp;
        if(p.y<dr.bottom)
           LineTo(dc,p.x,dr.bottom);
    }
    DeleteObject(linepen);
    SelectObject(dc, aoldpen);
}

//---------------------------------------------------------------------------
void __fastcall TGanttProject::MouseDown(TMouseButton Button,
        Classes::TShiftState Shift, int X, int Y)
{
//选中任务
    FUpdating = true;
    TPrjObject* t = YAtTask(Y);
    TPrjObject* bks = FProject->Selected;
    if(t)
    {
       TDateTime dt = XAtDay(X);
       if(t->StartDate <= dt && t->EndDate >= dt)
       {
             FProject->Selected = t;
             FChart->Invalidate();
       }else if(t->FactStartDate <= dt && t->FactEndDate >= dt)
       {
             FProject->Selected = t;
             FChart->Invalidate();
       }else
       {//如果没有任务选中，则恢复已前的
             FProject->Selected = bks;
       }
       if(FProject->Selected != bks && FChart->FOnTaskSelect)
       {
             FChart->FOnTaskSelect(FProject, FProject->Selected);
       }
    }
    FUpdating = false;
}
//---------------------------------------------------------------------------
void __fastcall TGanttProject::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
    switch(FAct)
    {
       case naNone:
            break;
       case naDragTask:
            break;
       default:
            ;//无处理
    }
}
//---------------------------------------------------------------------------
void __fastcall TGanttProject::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
}
//---------------------------------------------------------------------------
void TGanttProject::AutoAlign()
{
    FUpdating = true;
    TDateTime tempstart = 0;
    TDateTime tempend;
    TPrjObject* t;
	String str,MaxLeftString,MaxRightString;
    int MaxLeftLength=0,MaxRightLength=0;
    //if(FProject->ExpandFoldTasks.Count() > 0)
    //    tempstart = FProject->ExpandFoldTasks[0]->StartDate;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
        t = FProject->ExpandFoldTasks[i];
        str=FrontShowString.GetShowString(*t);
        if(MaxLeftLength<str.Length())
        {
           MaxLeftLength=str.Length();
           MaxLeftString=str;
         }

        if(int(tempstart) <= 2)
        {
            if(int(t->StartDate) > 2)
				tempstart = t->StartDate;
            if(int(t->FactStartDate) > 2)
                tempstart = t->FactStartDate;
        }else
        {
            if(int(t->StartDate) > 2&&tempstart >t->StartDate)
            {
                tempstart =  t->StartDate ;

            }
            if(int(t->FactStartDate) > 2&&tempstart > t->FactStartDate)
            {
                tempstart = t->FactStartDate;
            }
        }
    }
    tempend = tempstart;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
        t = FProject->ExpandFoldTasks[i];
        str=LateShowString.GetShowString(*t);
        if(MaxRightLength<str.Length())
        {
          MaxRightLength=str.Length();
          MaxRightString=str;
        }

        if(int(t->EndDate) > 2&&t->EndDate>=tempend)
        {
            tempend = t->EndDate ;
         }
        if(t->TaskStatus == tsStarted&&t->ProcessDate>=tempend)
        {
            tempend =  t->ProcessDate ;

         }
        if(int(t->FactEndDate) > 2&& t->FactEndDate>=tempend)
        {
            tempend =  t->FactEndDate;

        }
    }
    if(int(tempstart) < 10)
    {
        tempstart = tempstart.CurrentDate();
        tempend = tempstart + 1;
    }
    int LeftReservedLength=0;
    int RightReservedLength=0;

    TSize size;
    HDC chartDC=GetDC(FChart->Handle);
    if(MaxLeftLength>0)
    {
	 GetTextExtentPoint32(chartDC,MaxLeftString.c_str(),MaxLeftString.Length(),&size);
     LeftReservedLength=size.cx;
	}
    if(MaxRightLength>0)
    {
	  GetTextExtentPoint32(chartDC,MaxRightString.c_str(),MaxRightString.Length(),&size);
      RightReservedLength=size.cx;
    }
    ReleaseDC(FChart->Handle,chartDC);

    SetStateDate();
    // 考虑前锋线显示
    if(FChart->ShowPgViewLine||FChart->ShowProgressLine)
    {
        if(tempstart>FStateDate)
            tempstart=FStateDate;
        if(tempend<FStateDate)
            tempend=FStateDate;
     }

    Calendar.AutoAlignStartEnd(tempstart, tempend,LeftReservedLength+24,RightReservedLength+24); //zws 2003-06-26 15:21
    Calendar.Init();
    FChart->AdjustScrollBar();
    FChart->Invalidate();
	FUpdating = false;
}
//---------------------------------------------------------------------------
inline int TGanttProject::YAtRow(int Y)
{
    return (Y - FChart->FCalendarHeight) / FChart->RowHeight;
}
//---------------------------------------------------------------------------
inline TPrjObject* TGanttProject::YAtTask(int Y)
{
   int Row = YAtRow(Y);
   if(Row >= 0 && Row < FProject->ExpandFoldTasks.Count())
      return FProject->ExpandFoldTasks[Row];
   else
      return NULL;
}
//---------------------------------------------------------------------------
TDateTime TGanttProject::XAtDay(int X)
{
   return Calendar.XAtDay(X);
}
//---------------------------------------------------------------------------
int TGanttProject::GetDayLeft(const TDateTime &adt)
{
    return Calendar.GetDayLeft(adt);
}
//---------------------------------------------------------------------------
inline int TGanttProject::GetDayRight(const TDateTime &adt)
{
    return Calendar.GetDayRight(adt);
}
//---------------------------------------------------------------------------
TPrjObject* __fastcall TGanttProject::GetTopTask()
{
   return YAtTask(FChart->FVERT.nPos + FChart->FCalendarHeight);
}
//---------------------------------------------------------------------------
void __fastcall TGanttProject::SetTopTask(TPrjObject*ATask)
{
   if(FChart->FVERT.nMax <= FChart->FVERT.nMin)
      return;
   TMessage msg;
   msg.WParamLo = SB_THUMBPOSITION;
   msg.WParamHi = ATask->EFExpandIndex * FChart->FRowHeight;
   FChart->WMVScroll(msg);
}
//---------------------------------------------------------------------------
TDateTime __fastcall TGanttProject::GetLeftDay()
{
   return XAtDay(FChart->FHORZ.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TGanttProject::SetLeftDay(TDateTime ADate)
{
   int xNewPos = GetDayLeft(ADate);    // new position
   // New position must be between 0 and the screen width.
   xNewPos = xNewPos > FChart->FHORZ.nMin ? xNewPos : FChart->FHORZ.nMin;
   xNewPos = xNewPos < FChart->FHORZ.nMax ? xNewPos : FChart->FHORZ.nMax;
   xNewPos = xNewPos - xNewPos % 8;
   // If the current position does not change, do not scroll.
   // Reset the current scroll position.
   FChart->FHORZ.nPos = xNewPos;
//   ScrollWindow(FChart->Handle, -xDelta, 0, NULL, NULL);
   // Reset the scroll bar.
   SetScrollPos(FChart->Handle, SB_HORZ, xNewPos, true);
   UpdateWindow(FChart->Handle);
   FChart->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TGanttProject::SetProject(TProject*AProject)
{
   if(FMustDelete)
   {
      delete FProject;
      FMustDelete = false;
   }
   if(FProject != AProject)
   {
      FProject = AProject;
      FGTPrjDataChangeLink->SetProject(FProject);
      AutoAlign();
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TGantt::TGantt(TComponent* Owner)
        : TWinControl(Owner), FBindGrid(NULL)
{
    //checkCopyRight();
    DoubleBuffered = true;
    TControlStyle cs;
    cs<<csAcceptsControls<<csCaptureMouse<<csClickEvents<<
          csSetCaption<<csDoubleClicks<<csMenuEvents;
    this->ControlStyle = cs;

	FProject = new TGanttProject(this);
    FProject->Calendar.Init();

    Width = 200;
	Height = 180;
    Color = clWhite;
	FRowHeight=30;

    FHORZ.cbSize = sizeof(SCROLLINFO);
    FHORZ.fMask = SIF_DISABLENOSCROLL;
    FHORZ.nMin = 0;
    FHORZ.nMax = Width;
    FHORZ.nPos = 0;
    FVERT.cbSize = sizeof(SCROLLINFO);
    FVERT.fMask = SIF_DISABLENOSCROLL;
    FVERT.nMin = 0;
    FVERT.nMax = Height;
    FVERT.nPos = 0;

    FDblClickAdjust = false;
    FShowHLine=true;     //显示竖线
    FShowProgressLine= false;  //不显示前锋线
    FShowPgViewLine =false;  //不显示基准线
    FShowBasePlan = false;//不显示基准计划
    SetDefault();
}
//---------------------------------------------------------------------------
__fastcall TGantt::~TGantt()
{
    if(FPrintHandle)
    {
	   delete ((TGanttPrint*)(FPrintHandle));
    }
    delete FProject;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::PaintWindow(HDC DC)
{
    RECT dr = ClientRect;
    dr.left += FHORZ.nPos;
    dr.right += FHORZ.nPos;
    dr.top += (FVERT.nPos+FCalendarHeight);
    dr.bottom += FVERT.nPos;
    SetMapMode(DC, MM_ANISOTROPIC);
    SetBkMode(DC, TRANSPARENT);

    FProject->Calendar.DrawLine1 = true;
   // FProject->Calendar.DrawLine2 = true;
    SetViewportOrgEx(DC, -FHORZ.nPos, 0, NULL);
    if(FShowVLine)
        FProject->DrawCalendar(DC, FHORZ.nPos, Width, Height);
    else
        FProject->DrawCalendar(DC, FHORZ.nPos, Width, 0);

//    SetViewportOrgEx(DC, 0, 0, NULL);
//    ExcludeClipRect(DC, 0, 0, ClientWidth, CalendarHeight);

    SetViewportOrgEx(DC, -FHORZ.nPos, -FVERT.nPos, NULL);
    if(FShowHLine)
      FProject->DrawHLine(DC,dr);
    FProject->Draw(DC, dr);
    if(FShowProgressLine)
       FProject->DrawProgressLine(DC,dr);
    if(FShowPgViewLine)
        FProject->DrawPgViewLine(DC,dr);
    FProject->Calendar.DrawLine1 = false;
   // FProject->Calendar.DrawLine2 = false;    
    SetViewportOrgEx(DC, -FHORZ.nPos, 0, NULL);
    FProject->DrawCalendar(DC, FHORZ.nPos, Width, Height);

    SetViewportOrgEx(DC, 0, 0, NULL);
}
//---------------------------------------------------------------------------
void __fastcall TGantt::WMPaint(Messages::TWMPaint &Message)
{
   ControlState << csCustomPaint;
   TWinControl::Dispatch(&Message);
   ControlState >> csCustomPaint;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::WMErasebkgnd(Messages::TMessage &Message)
{
   Message.Result = 0;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::WMHScroll(Messages::TMessage &Message)
{
   int xDelta;     // xDelta = new_pos - current_pos
   int xNewPos;    // new position
   switch(Message.WParamLo)
   {
        // User clicked the shaft left of the scroll box.
        case SB_PAGELEFT:
            xNewPos = FHORZ.nPos - ClientWidth;
            break;
        // User clicked the shaft right of the scroll box.
        case SB_PAGERIGHT:
            xNewPos = FHORZ.nPos + ClientWidth;
            break;
        // User clicked the left arrow.
        case SB_LINELEFT:
            xNewPos = FHORZ.nPos - 20;
            break;
        // User clicked the right arrow.
        case SB_LINERIGHT:
            xNewPos = FHORZ.nPos + 20;
            break;
        // User dragged the scroll box.
        case SB_THUMBPOSITION:
//            xNewPos = Message.WParamHi;
//            break;
        case SB_THUMBTRACK:
//            xNewPos = Message.WParamHi;
//            break;
        {//此消息只能传递十六位的滚动条位置，所以如果滚动条位置大于65535，
         //则不正常，用GetScrollInfo来修正-----from msdn
            SCROLLINFO si;
            ZeroMemory(&si, sizeof(SCROLLINFO));
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_ALL;
            if(GetScrollInfo(Handle, SB_HORZ, &si) )
               xNewPos = si.nTrackPos;
            else
               xNewPos = Message.WParamHi;
            break;
        }
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
   xNewPos = xNewPos - xNewPos % 8;
   // If the current position does not change, do not scroll.
   // Reset the current scroll position.
   FHORZ.nPos = xNewPos;
   Invalidate();
   // Reset the scroll bar.
   SetScrollPos(Handle, SB_HORZ, xNewPos, true);
}
//---------------------------------------------------------------------------
void __fastcall TGantt::WMVScroll(Messages::TMessage &Message)
{
   TPrjObject* bkTopTask = FProject->TopTask;
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
            yNewPos = FVERT.nPos - FRowHeight;
            break;
        // User clicked the right arrow.
        case SB_LINEDOWN:
            yNewPos = FVERT.nPos + FRowHeight;
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
   yNewPos = yNewPos - yNewPos % FRowHeight;
   // If the current position does not change, do not scroll.
   // Reset the current scroll position.
   FVERT.nPos = yNewPos;
   SetScrollPos(Handle, SB_VERT, yNewPos, true);
   Invalidate();
   // Reset the scroll bar.
   if(FOnTopTaskChanged && bkTopTask != FProject->TopTask)
      FOnTopTaskChanged(FProject->Project, FProject->TopTask, bkTopTask);
}
//---------------------------------------------------------------------------
void __fastcall TGantt::WMKeyDown(Messages::TWMKey &Message)
{
    TWinControl::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TGantt::WMKeyUp(Messages::TWMKey &Message)
{
    TWinControl::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TGantt::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
    TWinControl::MouseDown(Button, Shift, X, Y);
    if(FDblClickAdjust)
    {
        FDblClickAdjust = false;
        return;
    }
    GetScrollInfo(Handle, SB_VERT, &FVERT);
    GetScrollInfo(Handle, SB_HORZ, &FHORZ);
    FProject->MouseDown(Button, Shift, X+FHORZ.nPos, Y+FVERT.nPos);
    SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TGantt::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
   TWinControl::MouseMove(Shift, X, Y);
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FProject->MouseMove(Shift, X+FHORZ.nPos, Y+FVERT.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TGantt::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   TWinControl::MouseUp(Button, Shift, X, Y);
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
//---------------------------------------------------------------------------
void __fastcall TGantt::WMDblClick(Messages::TMessage &Message)
{
   TWinControl::Dispatch(&Message);
   if(FOnTaskDblClick && FProject->Project->Selected)
      FOnTaskDblClick(FProject->Project, FProject->Project->Selected);
}
//---------------------------------------------------------------------------
TProject* __fastcall TGantt::GetProject()
{
    return FProject->Project;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetProject(TProject* AProject)
{
    FProject->Project = AProject;
}
//---------------------------------------------------------------------------
void TGantt::AutoAlign()
{
    FProject->AutoAlign();
}
//---------------------------------------------------------------------------
void TGantt::Draw(HDC dc, RECT dr, int TotalHeight)
{
    FProject->Calendar.DrawLine1 = true;
   // FProject->Calendar.DrawLine2 = true;
    FProject->DrawCalendar(dc, dr.left, dr.right - dr.left, TotalHeight);
    dr.top += FCalendarHeight;
    if(FShowHLine)
      FProject->DrawHLine(dc,dr);
    FProject->Draw(dc, dr);
    if(FShowProgressLine)
      FProject->DrawProgressLine(dc,dr);
    if(FShowPgViewLine)
        FProject->DrawPgViewLine(dc,dr);
    FProject->Calendar.DrawLine1 = false;
   // FProject->Calendar.DrawLine2 = false;
    FProject->DrawCalendar(dc, dr.left, dr.right - dr.left, TotalHeight < 0 ? (dr.bottom - dr.top) : TotalHeight);
}
//---------------------------------------------------------------------------
void TGantt::DrawCalendar(HDC dc, int ALeft, int AWidth, int LineHeight)
{
   FProject->DrawCalendar(dc, ALeft, AWidth, LineHeight);
}
//---------------------------------------------------------------------------
TPrjObject* __fastcall TGantt::GetTopTask()
{
   return FProject->TopTask;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetTopTask(TPrjObject*ATask)
{
   FProject->TopTask = ATask;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TGantt::GetLeftDay()
{
   return FProject->LeftDay;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetLeftDay(TDateTime ADate)
{
   FProject->LeftDay = ADate;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::AdjustSize(void)
{
   TWinControl::AdjustSize();
   AdjustScrollBar();
   FProject->Calendar.ChartHeight = Height;
}
//---------------------------------------------------------------------------
void TGantt::AdjustScrollBar()
{
    FHORZ.fMask = SIF_ALL;
    FHORZ.nMin = 0;
    FHORZ.nPage = 0;
    FHORZ.nMax = (GTProject->Calendar.GetDayRight(GTProject->Calendar.GetEndDay()) -
                  GTProject->Calendar.GetDayLeft(GTProject->Calendar.GetStartDay()))
                  - ClientRect.Width();
    FHORZ.nPos = FHORZ.nPos > FHORZ.nMax ? FHORZ.nMax : FHORZ.nPos;
    FHORZ.nPos = FHORZ.nPos > 0 ? FHORZ.nPos : 0;
    SetScrollInfo(Handle, SB_HORZ, &FHORZ, true);

    FVERT.fMask = SIF_ALL;
    FVERT.nMin = 0;
    FVERT.nPage = 0;
    FVERT.nMax = FRowHeight * (FProject->Project->ExpandFoldTasks.Count() + 2) + FCalendarHeight - ClientRect.Height();
    FVERT.nMax = FVERT.nMax - FVERT.nMax % FRowHeight + FRowHeight;
    FVERT.nPos = FVERT.nPos > FVERT.nMax ? FVERT.nMax : FVERT.nPos;
    FVERT.nPos = FVERT.nPos > 0 ? FVERT.nPos : 0;
    SetScrollInfo(Handle, SB_VERT, &FVERT, true);
}
//---------------------------------------------------------------------------
void TGantt::Refresh()
{
    AdjustScrollBar();
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetRowHeight(int AHeight)
{
    if(FRowHeight!=AHeight)
    {
      if(AHeight < 5)
       return;
      FRowHeight = AHeight;
      if(FBindGrid)
      {
       //FBindGrid->DefaultRowHeight=AHeight;
       FBindGrid->Init();
     }
       Invalidate();
   }
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetCalendarHeight(int AHeight)
{
    FCalendarHeight = AHeight;
    Invalidate();
    if(FBindGrid)
       FBindGrid->Init();
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetShowLine(bool AValue)
{
    FShowLine = AValue;
    Invalidate();
}
void __fastcall TGantt::SetShowHLine(bool value)
{
        if(FShowHLine != value) {
                FShowHLine = value;
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetShowVLine(bool value)
{
        if(FShowVLine != value) {
                FShowVLine = value;
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetShowProgressLine(bool value)
{
        if(FShowProgressLine != value) {
                FShowProgressLine = value;
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetShowPgViewLine(bool value)
{
        if(FShowPgViewLine != value) {
                FShowPgViewLine = value;
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetStateDateType(TStateDateType value)
{
        if(FStateDateType != value) {
                FStateDateType = value;
                FProject->SetStateDate();
                Invalidate();
        }
}
void __fastcall TGantt::SetManualStateDate(TDateTime AValue)
{
     if(FManualStateDate!=AValue){
               FManualStateDate=AValue;
            if(FStateDateType==sdtManualDate)
              {
                FProject->SetStateDate();
                Invalidate();
              }
      }
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetCalendarBkColor(TColor AColor)
{
	FProject->Calendar.BackColor = AColor;
	Invalidate();
}
void __fastcall TGantt::SetProgressLineColor(TColor value)
{
        if(FProgressLineColor != value) {
                FProgressLineColor = value;
                Invalidate();
        }
}

void __fastcall TGantt::SetPgViewLineColor(TColor value)
{
        if(FPgViewLineColor != value) {
                FPgViewLineColor = value;
                Invalidate();
        }
}
//---------------------------------------------------------------------------
TColor __fastcall TGantt::GetCalendarBkColor()
{
    return (TColor)FProject->Calendar.BackColor;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetCalendarFontColor(TColor AColor)
{
    FProject->Calendar.FontColor = AColor;
    Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TGantt::GetCalendarFontColor()
{
    return (TColor)FProject->Calendar.FontColor;
}
//---------------------------------------------------------------------------
void __fastcall TGantt::SetShowWarning(bool AValue)
{
    FShowWarning = AValue;
}
//---------------------------------------------------------------------------
TPrintHandle __fastcall TGantt::GetPrintHandle()
{
    if(FPrintHandle)
    {
    }else
    {
        FPrintHandle = new TGanttPrint(this);
    }
    return FPrintHandle;
}
//---------------------------------------------------------------------------
int __fastcall TGantt::GetTotalHeight()
{
    return FVERT.nMax + ClientRect.Height();
}
//---------------------------------------------------------------------------
int __fastcall TGantt::GetTotalWidth()
{
    return FHORZ.nMax + ClientRect.Width();
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetNotStartDraw()//未开工
{
    return &(FProject->NotStartDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetStartedDraw()//已开工
{
    return &(FProject->StartedDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetOveredDraw()//已完工
{
    return &(FProject->OveredDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetCriticalNotStartDraw()//未开工
{
    return &(FProject->CriticalNotStartDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetCriticalStartedDraw()//已开工
{
    return &(FProject->CriticalStartedDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetCriticalOveredDraw()//已完工
{
    return &(FProject->CriticalOveredDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetAbstractDraw()//摘要任务
{
    return &(FProject->AbstractDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetMarkerDraw()//里程碑
{
    return &(FProject->MarkerDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetWarningDraw()//有问题任务
{
    return &(FProject->WarningDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignNotStartDraw()//外部未开工
{
    return &(FProject->ForeignNotStartDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignStartedDraw()//外部已开工
{
    return &(FProject->ForeignStartedDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignOveredDraw()//外部已完工
{
    return &(FProject->ForeignOveredDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetCriticalForeignNotStartDraw()//外部未开工
{
    return &(FProject->CriticalForeignNotStartDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetCriticalForeignStartedDraw()//外部已开工
{
    return &(FProject->CriticalForeignStartedDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetCriticalForeignOveredDraw()//外部已完工
{
    return &(FProject->CriticalForeignOveredDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignAbstractDraw()//外部摘要任务
{
    return &(FProject->ForeignAbstractDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignMarkerDraw()//外部里程碑
{
    return &(FProject->ForeignMarkerDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetMarkerOverDraw()
{
    return &(FProject->MarkerOverDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignMarkerOverDraw()
{
    return &(FProject->ForeignMarkerOverDraw);
}
//---------------------------------------------------------------------------
T3BarDraw* __fastcall TGantt::GetForeignProjectDraw()//外部工程
{
    return &(FProject->ForeignProjectDraw);
}
//---------------------------------------------------------------------------
TCalendarDraw* __fastcall TGantt::GetCalendar()
{
    return &(FProject->Calendar);
}
//---------------------------------------------------------------------------
TGTLinkDraw* __fastcall TGantt::GetCriticalLinkDraw()
{
    return &(FProject->CriticalLinkDraw);
}
//---------------------------------------------------------------------------
TGTLinkDraw* __fastcall TGantt::GetNormalLinkDraw()
{
    return &(FProject->NormalLinkDraw);
}
//---------------------------------------------------------------------------
TTaskShowString* __fastcall TGantt::GetFrontShowString()
{
    return &(FProject->FrontShowString);
}
//---------------------------------------------------------------------------
TTaskShowString* __fastcall TGantt::GetLateShowString()
{
    return &(FProject->LateShowString);
}
//---------------------------------------------------------------------------
void TGantt::SetDefault()
{
    FRowHeight = 24;
    FCalendarHeight = 32;
	CalendarBkColor = clSkyBlue;
    CaldndarFontColor = clBlack;
    FProgressLineColor = clGreen;
    FPgViewLineColor = clRed;

    FShowLine = true;
    FShowHLine = false;
    FShowVLine = true;
	  FShowWarning = true;
    FShowProgressLine = false;
    FShowPgViewLine = false;

    FManualStateDate=Date();
    FStateDateType=sdtPrjProgressDate;

    FrontShowString->SetDefineString("");
    LateShowString->SetDefineString("[名称] [计划工期]天");
    //未开工
    NotStartDraw->Bar2Draw = false;
    NotStartDraw->Bar1.Pattern = 2;
    NotStartDraw->Bar1.Figure = TBarDraw::fTopLarge;
    NotStartDraw->Bar1.Color = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    NotStartDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    NotStartDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    NotStartDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    NotStartDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar2.Pattern = 1;
    NotStartDraw->Bar2.Figure = TBarDraw::fEmpty;
    NotStartDraw->Bar2.Color = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar2.BorderColor = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    NotStartDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    NotStartDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    NotStartDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    NotStartDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    NotStartDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 0, 255);
    //未开工   关键
    CriticalNotStartDraw->Bar2Draw = false;
    CriticalNotStartDraw->Bar1.Pattern = 2;
    CriticalNotStartDraw->Bar1.Figure = TBarDraw::fTopLarge;
    CriticalNotStartDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalNotStartDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalNotStartDraw->Bar1.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalNotStartDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalNotStartDraw->Bar1.TailDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar2.Pattern = 1;
    CriticalNotStartDraw->Bar2.Figure = TBarDraw::fEmpty;
    CriticalNotStartDraw->Bar2.Color = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar2.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalNotStartDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalNotStartDraw->Bar2.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalNotStartDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalNotStartDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalNotStartDraw->Bar2.TailDraw.Color = (TColor)RGB(255, 0, 0);
    //已开工
    StartedDraw->Bar2Draw = true;
    StartedDraw->Bar1.Pattern = 2;
    StartedDraw->Bar1.Figure = TBarDraw::fTopLarge;
    StartedDraw->Bar1.Color = (TColor)RGB(0, 0, 255);
    StartedDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 255);
    StartedDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    StartedDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    StartedDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    StartedDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    StartedDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    StartedDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    StartedDraw->Bar2.Pattern = 0;
    StartedDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    StartedDraw->Bar2.Color = (TColor)RGB(0, 128, 0);
    StartedDraw->Bar2.BorderColor = (TColor)RGB(0, 128, 0);
    StartedDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    StartedDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    StartedDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 128, 0);
    StartedDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    StartedDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    StartedDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 128, 0);
    //已开工       关键
    CriticalStartedDraw->Bar2Draw = true;
    CriticalStartedDraw->Bar1.Pattern = 2;
    CriticalStartedDraw->Bar1.Figure = TBarDraw::fTopLarge;
    CriticalStartedDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    CriticalStartedDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalStartedDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalStartedDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalStartedDraw->Bar1.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalStartedDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalStartedDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalStartedDraw->Bar1.TailDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalStartedDraw->Bar2.Pattern = 0;
    CriticalStartedDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    CriticalStartedDraw->Bar2.Color = (TColor)RGB(0, 128, 0);
    CriticalStartedDraw->Bar2.BorderColor = (TColor)RGB(0, 128, 0);
    CriticalStartedDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalStartedDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalStartedDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 128, 0);
    CriticalStartedDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalStartedDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalStartedDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 128, 0);
    //已完工
    OveredDraw->Bar2Draw = true;
    OveredDraw->Bar1.Pattern = 2;
    OveredDraw->Bar1.Figure = TBarDraw::fTopLarge;
    OveredDraw->Bar1.Color = (TColor)RGB(0, 0, 255);
    OveredDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 255);
    OveredDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    OveredDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    OveredDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    OveredDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    OveredDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    OveredDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    OveredDraw->Bar2.Pattern = 0;
    OveredDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    OveredDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    OveredDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    OveredDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    OveredDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    OveredDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    OveredDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    OveredDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    OveredDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //已完工   关键
    CriticalOveredDraw->Bar2Draw = true;
    CriticalOveredDraw->Bar1.Pattern = 2;
    CriticalOveredDraw->Bar1.Figure = TBarDraw::fTopLarge;
    CriticalOveredDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    CriticalOveredDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalOveredDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalOveredDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalOveredDraw->Bar1.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalOveredDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalOveredDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalOveredDraw->Bar1.TailDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalOveredDraw->Bar2.Pattern = 0;
    CriticalOveredDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    CriticalOveredDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    CriticalOveredDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    CriticalOveredDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalOveredDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalOveredDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    CriticalOveredDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalOveredDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalOveredDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //摘要任务
    AbstractDraw->Bar2Draw = false;
    AbstractDraw->Bar1.Pattern = 0;
    AbstractDraw->Bar1.Figure = TBarDraw::fTopLarge;
    AbstractDraw->Bar1.Color = (TColor)RGB(0, 0, 0);
    AbstractDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 0);
    AbstractDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fBottomDiamond;
    AbstractDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    AbstractDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 0);
    AbstractDraw->Bar1.TailDraw.Figure = THeadTailDraw::fBottomDiamond;
    AbstractDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    AbstractDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 0);
    AbstractDraw->Bar2.Pattern = 0;
    AbstractDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    AbstractDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    AbstractDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    AbstractDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    AbstractDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    AbstractDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    AbstractDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    AbstractDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    AbstractDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //里程碑
    MarkerDraw->Bar2Draw = false;
    MarkerDraw->Bar1.Pattern = 0;
    MarkerDraw->Bar1.Figure = TBarDraw::fEmpty;
    MarkerDraw->Bar1.Color = (TColor)RGB(0, 0, 0);
    MarkerDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 0);
    MarkerDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fDiamond;
    MarkerDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    MarkerDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 0);
    MarkerDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    MarkerDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    MarkerDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 0);
    MarkerDraw->Bar2.Pattern = 0;
    MarkerDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    MarkerDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    MarkerDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    MarkerDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    MarkerDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    MarkerDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    MarkerDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    MarkerDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    MarkerDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //里程碑已完工
    MarkerOverDraw->Bar2Draw = false;
    MarkerOverDraw->Bar1.Pattern = 0;
    MarkerOverDraw->Bar1.Figure = TBarDraw::fEmpty;
    MarkerOverDraw->Bar1.Color = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar1.BorderColor = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fDiamond;
    MarkerOverDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    MarkerOverDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    MarkerOverDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    MarkerOverDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar2.Pattern = 0;
    MarkerOverDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    MarkerOverDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    MarkerOverDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    MarkerOverDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    MarkerOverDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    MarkerOverDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    MarkerOverDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);

    //警报
    WarningDraw->Bar2Draw = true;
    WarningDraw->Bar1.Pattern = 2;
    WarningDraw->Bar1.Figure = TBarDraw::fTopLarge;
    WarningDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    WarningDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    WarningDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    WarningDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    WarningDraw->Bar1.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    WarningDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    WarningDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    WarningDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    WarningDraw->Bar2.Pattern = 0;
    WarningDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    WarningDraw->Bar2.Color = (TColor)RGB(255, 0, 0);
    WarningDraw->Bar2.BorderColor = (TColor)RGB(255, 0, 0);
    WarningDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    WarningDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    WarningDraw->Bar2.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    WarningDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    WarningDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    WarningDraw->Bar2.TailDraw.Color = (TColor)RGB(255, 0, 0);
//外部工程
    ForeignProjectDraw->Bar2Draw = false;
    ForeignProjectDraw->Bar1.Pattern = 0;
    ForeignProjectDraw->Bar1.Figure = TBarDraw::fTopLarge;
    ForeignProjectDraw->Bar1.Color = (TColor)RGB(128, 128, 128);
    ForeignProjectDraw->Bar1.BorderColor = (TColor)RGB(128, 128, 128);
    ForeignProjectDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fBottomDiamond;
    ForeignProjectDraw->Bar1.HeadDraw.Type = THeadTailDraw::tEmpty;
    ForeignProjectDraw->Bar1.HeadDraw.Color = (TColor)RGB(128, 128, 128);
    ForeignProjectDraw->Bar1.TailDraw.Figure = THeadTailDraw::fBottomDiamond;
    ForeignProjectDraw->Bar1.TailDraw.Type = THeadTailDraw::tEmpty;
    ForeignProjectDraw->Bar1.TailDraw.Color = (TColor)RGB(128, 128, 128);
    ForeignProjectDraw->Bar2.Pattern = 0;
    ForeignProjectDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    ForeignProjectDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    ForeignProjectDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    ForeignProjectDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignProjectDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignProjectDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignProjectDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignProjectDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignProjectDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //外部未开工
    ForeignNotStartDraw->Bar2Draw = false;
    ForeignNotStartDraw->Bar1.Pattern = 1;
    ForeignNotStartDraw->Bar1.Figure = TBarDraw::fTopLarge;
    ForeignNotStartDraw->Bar1.Color = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignNotStartDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignNotStartDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignNotStartDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignNotStartDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar2.Pattern = 1;
    ForeignNotStartDraw->Bar2.Figure = TBarDraw::fEmpty;
    ForeignNotStartDraw->Bar2.Color = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar2.BorderColor = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignNotStartDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignNotStartDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignNotStartDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignNotStartDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignNotStartDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 0, 255);
    //外部未开工  关键
    CriticalForeignNotStartDraw->Bar2Draw = false;
    CriticalForeignNotStartDraw->Bar1.Pattern = 2;
    CriticalForeignNotStartDraw->Bar1.Figure = TBarDraw::fTopLarge;
    CriticalForeignNotStartDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignNotStartDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignNotStartDraw->Bar1.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignNotStartDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignNotStartDraw->Bar1.TailDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar2.Pattern = 1;
    CriticalForeignNotStartDraw->Bar2.Figure = TBarDraw::fEmpty;
    CriticalForeignNotStartDraw->Bar2.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar2.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignNotStartDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignNotStartDraw->Bar2.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignNotStartDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignNotStartDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignNotStartDraw->Bar2.TailDraw.Color = (TColor)RGB(255, 0, 0);
    //外部已开工
    ForeignStartedDraw->Bar2Draw = true;
    ForeignStartedDraw->Bar1.Pattern = 2;
    ForeignStartedDraw->Bar1.Figure = TBarDraw::fTopLarge;
    ForeignStartedDraw->Bar1.Color = (TColor)RGB(0, 0, 255);
    ForeignStartedDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 255);
    ForeignStartedDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignStartedDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignStartedDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignStartedDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignStartedDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignStartedDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignStartedDraw->Bar2.Pattern = 0;
    ForeignStartedDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    ForeignStartedDraw->Bar2.Color = (TColor)RGB(0, 128, 0);
    ForeignStartedDraw->Bar2.BorderColor = (TColor)RGB(0, 128, 0);
    ForeignStartedDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignStartedDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignStartedDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 128, 0);
    ForeignStartedDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignStartedDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignStartedDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 128, 0);
    //外部已开工   关键
    CriticalForeignStartedDraw->Bar2Draw = true;
    CriticalForeignStartedDraw->Bar1.Pattern = 2;
    CriticalForeignStartedDraw->Bar1.Figure = TBarDraw::fTopLarge;
    CriticalForeignStartedDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignStartedDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalForeignStartedDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignStartedDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignStartedDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    CriticalForeignStartedDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignStartedDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignStartedDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    CriticalForeignStartedDraw->Bar2.Pattern = 0;
    CriticalForeignStartedDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    CriticalForeignStartedDraw->Bar2.Color = (TColor)RGB(0, 128, 0);
    CriticalForeignStartedDraw->Bar2.BorderColor = (TColor)RGB(0, 128, 0);
    CriticalForeignStartedDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignStartedDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignStartedDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 128, 0);
    CriticalForeignStartedDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignStartedDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignStartedDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 128, 0);
    //外部已完工
    ForeignOveredDraw->Bar2Draw = true;
    ForeignOveredDraw->Bar1.Pattern = 2;
    ForeignOveredDraw->Bar1.Figure = TBarDraw::fTopLarge;
    ForeignOveredDraw->Bar1.Color = (TColor)RGB(0, 0, 255);
    ForeignOveredDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 255);
    ForeignOveredDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignOveredDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignOveredDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignOveredDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignOveredDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignOveredDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 255);
    ForeignOveredDraw->Bar2.Pattern = 0;
    ForeignOveredDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    ForeignOveredDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    ForeignOveredDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    ForeignOveredDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignOveredDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignOveredDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignOveredDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignOveredDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignOveredDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //外部已完工   关键
    CriticalForeignOveredDraw->Bar2Draw = true;
    CriticalForeignOveredDraw->Bar1.Pattern = 2;
    CriticalForeignOveredDraw->Bar1.Figure = TBarDraw::fTopLarge;
    CriticalForeignOveredDraw->Bar1.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignOveredDraw->Bar1.BorderColor = (TColor)RGB(255, 0, 0);
    CriticalForeignOveredDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignOveredDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignOveredDraw->Bar1.HeadDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignOveredDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignOveredDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignOveredDraw->Bar1.TailDraw.Color = (TColor)RGB(255, 0, 0);
    CriticalForeignOveredDraw->Bar2.Pattern = 0;
    CriticalForeignOveredDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    CriticalForeignOveredDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    CriticalForeignOveredDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    CriticalForeignOveredDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignOveredDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignOveredDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    CriticalForeignOveredDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    CriticalForeignOveredDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    CriticalForeignOveredDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);
    //外部摘要任务
    ForeignAbstractDraw->Bar2Draw = false;
    ForeignAbstractDraw->Bar1.Pattern = 0;
    ForeignAbstractDraw->Bar1.Figure = TBarDraw::fTopLarge;
    ForeignAbstractDraw->Bar1.Color = (TColor)RGB(192, 192, 192);
    ForeignAbstractDraw->Bar1.BorderColor = (TColor)RGB(192, 192, 192);
    ForeignAbstractDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fBottomDiamond;
    ForeignAbstractDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignAbstractDraw->Bar1.HeadDraw.Color = (TColor)RGB(192, 192, 192);
    ForeignAbstractDraw->Bar1.TailDraw.Figure = THeadTailDraw::fBottomDiamond;
    ForeignAbstractDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignAbstractDraw->Bar1.TailDraw.Color = (TColor)RGB(192, 192, 192);
    ForeignAbstractDraw->Bar2.Pattern = 0;
    ForeignAbstractDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    ForeignAbstractDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    ForeignAbstractDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    ForeignAbstractDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignAbstractDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignAbstractDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignAbstractDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignAbstractDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignAbstractDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);

    //外部里程碑
    ForeignMarkerDraw->Bar2Draw = false;
    ForeignMarkerDraw->Bar1.Pattern = 0;
    ForeignMarkerDraw->Bar1.Figure = TBarDraw::fEmpty;
    ForeignMarkerDraw->Bar1.Color = (TColor)RGB(0, 0, 0);
    ForeignMarkerDraw->Bar1.BorderColor = (TColor)RGB(0, 0, 0);
    ForeignMarkerDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fDiamond;
    ForeignMarkerDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 0, 0);
    ForeignMarkerDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignMarkerDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 0, 0);
    ForeignMarkerDraw->Bar2.Pattern = 0;
    ForeignMarkerDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    ForeignMarkerDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    ForeignMarkerDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignMarkerDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignMarkerDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);

    //外部里程碑，已完工
    ForeignMarkerOverDraw->Bar2Draw = false;
    ForeignMarkerOverDraw->Bar1.Pattern = 0;
    ForeignMarkerOverDraw->Bar1.Figure = TBarDraw::fEmpty;
    ForeignMarkerOverDraw->Bar1.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar1.BorderColor = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar1.HeadDraw.Figure = THeadTailDraw::fDiamond;
    ForeignMarkerOverDraw->Bar1.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerOverDraw->Bar1.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar1.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignMarkerOverDraw->Bar1.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerOverDraw->Bar1.TailDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar2.Pattern = 0;
    ForeignMarkerOverDraw->Bar2.Figure = TBarDraw::fBottomLarge;
    ForeignMarkerOverDraw->Bar2.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar2.BorderColor = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar2.HeadDraw.Figure = THeadTailDraw::fEmpty;
    ForeignMarkerOverDraw->Bar2.HeadDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerOverDraw->Bar2.HeadDraw.Color = (TColor)RGB(0, 255, 0);
    ForeignMarkerOverDraw->Bar2.TailDraw.Figure = THeadTailDraw::fEmpty;
    ForeignMarkerOverDraw->Bar2.TailDraw.Type = THeadTailDraw::tSolid;
    ForeignMarkerOverDraw->Bar2.TailDraw.Color = (TColor)RGB(0, 255, 0);


    CriticalLinkDraw->Color = clRed;
    NormalLinkDraw->Color = clBlack;

    if(FBindGrid)
       FBindGrid->Init();
}


void __fastcall TGantt::SetShowDays(bool value)
{
	   if(FProject->Calendar.ShowDays!=value)
	   {
		FProject->Calendar.ShowDays = value;
		Invalidate();
	   }
		//TODO: Add your source code here
}
bool __fastcall TGantt::GetShowDays()
{
		return FProject->Calendar.ShowDays;
		//TODO: Add your source code here
}

void __fastcall TGantt::SetLanguage(int value)
{
	   if(FProject->Calendar.Language != value)
	   {
	    FProject->Calendar.Language = value;
		Invalidate();
	   }
}
int __fastcall TGantt::GetLanguage()
{
       return FProject->Calendar.Language;
}

void __fastcall TGantt::SetShowBasePlan(bool value)
{
        if(FShowBasePlan != value) {
                FShowBasePlan = value;
           FProject->ShowBasePlan=value;
           Invalidate();
        }
}
