//---------------------------------------------------------------------------
//    File:               NetChart.h, NetChart.cpp
//    Function:           网络图
//    Author:             sunny
//    Last Modify:        2009-08-28
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "NetChart.h"
#include "vclComFunc.h"
#include "ZChartPrint.h"
#include "CopyRight.h"
#include <graphics.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TNetChart *)
{
        new TNetChart(NULL);
}
namespace Netchart
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TNetChart)};
                 RegisterComponents("ZChart", classes, 0);
        }
}


class PACKAGE TNCProject
{
    friend TNetChart;
    enum NCPAct {naNone, naDragTask, naExpandFold};
    enum DrawFrameType {dftNormal, dftFocus, dftMove};
private:
    void  Task_Draw(TPrjObject&AObj, HDC dc);
    TFrameDraw& ObjectFrameDraw(TPrjObject&AObj);
    void  TaskLink_Draw(TTaskLink&ALink, HDC dc);
    POINT TaskLink_FirstPoint(TTaskLink&ALink);
    POINT TaskLink_LastPoint(TTaskLink&ALink);
    int   PointTop(int Top);
    int   PointLeft(int Left);
    int   PointYMiddle(int Top);
    bool  PointOnLine(POINT p1, POINT p2, POINT point);
    TTaskLink* FDragTaskLink;
    POINT        FDragTaskLinkOldPoint;
    int          FDragTaskLinkType;

	RECT FMoveRect;
    bool StartDragTask(int, int);
    void DragingTask(int, int);
    void EndDragTask(int, int);
    bool StartExpandFold(int, int);
    void EndExpandFold(int, int);
private:
    TProject*            FProject;
    bool                   FMustDelete;
    NCPAct                 FAct;
    TPrjDataChangeLink * FNCPrjDataChangeLink;
    bool                   FUpdating;
    TPrjObject* HaveTaskAtPosition(int Left, int Top);
    TPrjObject* HaveTaskAtPoint(int x, int y);
    int      MaxLeft();
    int      MaxTop();
    void __fastcall SetProject(TProject*AProject);

    void AlignTaskPosition();
    void AlignAAbstract(TPrjObject&AObj);
    int  GetChildMaxTop(TPrjObject&AObj);
    void AlignATask(TPrjObject& ATask);
    void AlignTaskLinkPosition();
    void AlignTaskTaskLinkPosition(TPrjObject&ATask);
    void AlignALink(TTaskLink&ALink);
    void AlignTaskLinkLines(POINT*p1, int PointCount);
    void AlingALine(POINT&p1, POINT&p2);
    void BuildTaskLinkBridge(TTaskLink&ALink);
    void SumFrontTastLeft(TPrjObject* AObj);
    void SumFrontTastTop(TPrjObject* AObj);
    bool PositionIsOverlap(TPrjObject *AObj,int NCTop);
    TPoint* FindTaskByName(const String TaskName);////////////
protected:
    TNetChart * FChart;
    RECT  PointAtRect(int X, int Y);
    POINT PointAtTaskPosition(int X, int Y);
    RECT  PositionAtRect(int Left, int Top);
    void  DrawFrame(HDC dc, RECT dr, DrawFrameType Type);
    void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
    void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);

    TFrameDraw  NotStartDraw;//未开工
    TFrameDraw  CriticalNotStartDraw;//未开工
    TFrameDraw  StartedDraw;//已开工
    TFrameDraw  CriticalStartedDraw;//已开工
    TFrameDraw  OveredDraw;//已完工
    TFrameDraw  CriticalOveredDraw;//已完工
    TFrameDraw  AbstractDraw;//摘要任务
    TFrameDraw  MarkerDraw;//里程碑
    TFrameDraw  WarningDraw;//有问题任务
    TFrameDraw  ForeignNotStartDraw;//外部未开工
    TFrameDraw  CriticalForeignNotStartDraw;//外部未开工
    TFrameDraw  ForeignStartedDraw;//外部已开工
    TFrameDraw  CriticalForeignStartedDraw;//外部已开工
    TFrameDraw  ForeignOveredDraw;//外部已完工
    TFrameDraw  CriticalForeignOveredDraw;//外部已完工
    TFrameDraw  ForeignAbstractDraw;//外部摘要任务
    TFrameDraw  ForeignMarkerDraw;//外部里程碑
    TFrameDraw  ForeignProjectDraw;//外部工程

    TNCLinkDraw CriticalLinkDraw;
    TNCLinkDraw LinkDraw;
public:
    __fastcall TNCProject(TNetChart* AChart);
	virtual __fastcall ~TNCProject();
    void Draw(HDC dc, RECT dr);
    void AutoAlign();
    RECT Task_ClientRect(TPrjObject&ATask);
    __property TProject* Project = {read=FProject, write=SetProject};
    __property TNetChart* Chart = {read=FChart};
    __property bool Updating = {read=FUpdating, write=FUpdating};
};

class TNCPrjDataChangeLink : public TPrjDataChangeLink
{
public:
    TNCProject* FNCProject;
    TNCPrjDataChangeLink(TNCProject*AProject)
	   :TPrjDataChangeLink(AProject->Project) { FNCProject = AProject; }

    virtual void BeforeProjectChange()
    {
    }
    virtual void AfterProjectChange()
    {
        if(!(FNCProject->Updating)&&FNCProject->Project->NeedEditStatus)
            FNCProject->Chart->Invalidate();
    }
    virtual void BeforeTaskChange(TPrjObject*ATask){}
    virtual void AfterTaskChange(TPrjObject*ATask)
    {
        if(!(FNCProject->Updating)&&FNCProject->Project->NeedEditStatus)
            FNCProject->Chart->Invalidate();
    }
    virtual void BeforeTaskDelete(TPrjObject*ATask){}
    virtual void AfterTaskDelete()
    {
        if(!(FNCProject->Updating))
            FNCProject->Chart->Invalidate();
    }
    virtual void AfterTaskAdd(TPrjObject*ATask)
    {
        if(!(FNCProject->Updating)&&FNCProject->Project->NeedEditStatus)
            FNCProject->Chart->Invalidate();
    }
    virtual void BeforeTaskLinkChange(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkChange(TTaskLink*ATaskLink)
    {
        if(!(FNCProject->Updating)&&FNCProject->Project->NeedEditStatus)
            FNCProject->Chart->Invalidate();
    }
    virtual void BeforeTaskLinkDelete(TTaskLink*ATaskLink){}
    virtual void AfterTaskLinkAdd(TTaskLink*ATaskLink)
    {
        if(!(FNCProject->Updating)&&FNCProject->Project->NeedEditStatus)
            FNCProject->Chart->Invalidate();
    }
    virtual void BeginUpdate(){}
    virtual void EndUpdate()
    {
        if(!(FNCProject->Updating) && FNCProject->Chart->Visible)
        {
            FNCProject->AutoAlign();
        }
    }
    virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect)
    {
        if(FNCProject->Chart->OnTaskSelect)
        {
            FNCProject->Chart->OnTaskSelect(FProject, FProject->Selected);
        }
        if(!(FNCProject->Updating))
        {
            FNCProject->Chart->Invalidate();
        }
    }
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TNCProject::Task_Draw(TPrjObject&AObj, HDC dc)
{
    int Margin = (FChart->TaskHeight * FChart->ShowZoom / ncszNormal) / 2 + 2;
    RECT dr = Task_ClientRect(AObj);
    TFrameDraw& FrameDraw = ObjectFrameDraw(AObj);
    if(AObj.ChildCount() > 0 || AObj.GetType() == ttForeignProject)
    {
        FrameDraw.Draw(dc, dr.left, dr.top, dr.right, dr.bottom,
                       Margin, &AObj, FProject->Selected == &AObj,
                       AObj.EFExpanded ? TFrameDraw::eftFolded : TFrameDraw::eftExpanded);
    }else
    {
        FrameDraw.Draw(dc, dr.left, dr.top, dr.right, dr.bottom,
                       Margin, &AObj, FProject->Selected == &AObj,
                       TFrameDraw::eftNone);
    }
}
inline RECT TNCProject::Task_ClientRect(TPrjObject&ATask)
{
   RECT r;
   r.left = ATask.NCLeft * (FChart->FTaskWidth + FChart->FColDistance) +
            (FChart->FColDistance) / 2;
   r.right = r.left + FChart->FTaskWidth;
   r.top = ATask.NCTop * (FChart->FTaskHeight + FChart->FRowDistance) +
            (FChart->FRowDistance) / 2;
   r.bottom = r.top + FChart->FTaskHeight;
   return r;
}
TFrameDraw& TNCProject::ObjectFrameDraw(TPrjObject&AObj)
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
                      return ForeignMarkerDraw;
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
                      return MarkerDraw;
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
//---------------------------------------------------------------------------
void TNCProject::TaskLink_Draw(TTaskLink&ALink, HDC dc)
{
   int CornerSize = FChart->FColDistance / 8;
   TNCLinkDraw* draw;
   if(ALink.Critical)
   {
       draw = &CriticalLinkDraw;
   }else
   {
       draw = &LinkDraw;
   }
   draw->DrawWidthBridge(dc, ALink.NCPoint, ALink.NCPointCount,
                         ALink.NCBridgeLineIndex, ALink.NCBridgePointCount,
                         ALink.NCBridgePoint,
                         CornerSize);
}
POINT TNCProject::TaskLink_FirstPoint(TTaskLink&ALink)
{
   POINT r;
   if(ALink.Front)
   {
      r.x = (ALink.Front->NCLeft+1) * FChart->FTaskWidth +
            (ALink.Front->NCLeft+0.5) * FChart->FColDistance;
      r.y = (ALink.Front->NCTop+0.5) * (FChart->FTaskHeight +
                                   FChart->FRowDistance);
   }
   return r;
}
POINT TNCProject::TaskLink_LastPoint(TTaskLink&ALink)
{
   POINT r;
   if(ALink.Task)
   {
      r.x = ALink.Task->NCLeft * FChart->FTaskWidth +
            (ALink.Task->NCLeft+0.5) * FChart->FColDistance - 8;
      r.y = (ALink.Task->NCTop+0.5) * (FChart->FTaskHeight +
              FChart->FRowDistance);
   }
   return r;
}
bool TNCProject::PointOnLine(POINT p1, POINT p2, POINT point)
{
   if(p1.y == p2.y && p1.x == p2.x)
      return false;
   double k;
   if(abs(p2.y - p1.y) < abs(p2.x - p1.x))
   {
      if((point.x < p1.x-5 && point.x < p2.x-5) ||
         (point.x > p1.x+5 && point.x > p2.x+5))
         return false;
      k = double(p2.y - p1.y) / double(p2.x - p1.x);
      double y = k * double(point.x - p2.x) + p2.y;
      if((y - point.y) <= 5 && (point.y - y) <= 5)
         return true;
      else
         return false;
   }else
   {
      if((point.y < p1.y-5 && point.y < p2.y-5) ||
         (point.y > p1.y+5 && point.y > p2.y+5))
         return false;
      k = double(p2.x - p1.x) / double(p2.y - p1.y);
      double x = k * double(point.y - p2.y) + p2.x;
      if((x - point.x) <= 5 && (point.x - x) <= 5)
         return true;
      else
         return false;
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TNCProject::TNCProject(TNetChart* AChart)
{
    FChart = AChart;
    FAct = naNone;
    FProject = new TProject();
    FMustDelete = true;
    FNCPrjDataChangeLink = new TNCPrjDataChangeLink(this);
    FUpdating = false;
    FDragTaskLinkType = 0;
}
__fastcall TNCProject::~TNCProject()
{
    if(FMustDelete)
       delete FProject;
    if(FNCPrjDataChangeLink)
       delete FNCPrjDataChangeLink;
}
void TNCProject::Draw(HDC dc, RECT dr)
{
    TFont* AFont = new TFont();
    AFont->Assign(FChart->Font);
    AFont->Height = AFont->Height * FChart->ShowZoom / ncszNormal;
	HFONT font = Vclcomfunc::CreateFontByTFont(AFont);
    delete AFont;
    HGDIOBJ oldfont = SelectObject(dc, font);

    FUpdating = true;
    TPrjObject* t;
    RECT r;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
        t = FProject->ExpandFoldTasks[i];
        r = Task_ClientRect(*t);
        if((dr.left <= r.right && dr.right >= r.left) &&
           (dr.top-15 <= r.bottom && dr.bottom >= r.top-15))
        {
            Task_Draw(*t, dc);
        }
    }
    for(int i = 0; i < FProject->TaskLinks.Count(); i++)
    {
        TTaskLink* tl = FProject->TaskLinks[i];
        if(tl->Task && tl->Front && tl->Critical &&
           tl->Task->EFExpandIndex >= 0 && tl->Front->EFExpandIndex >= 0)
        {
            TaskLink_Draw(*tl, dc);
        }
    }
    for(int i = 0; i < FProject->TaskLinks.Count(); i++)
    {
        TTaskLink* tl = FProject->TaskLinks[i];
        if(tl->Task && tl->Front && !tl->Critical &&
           tl->Task->EFExpandIndex >= 0 && tl->Front->EFExpandIndex >= 0)
        {
            TaskLink_Draw(*tl, dc);
        }
    }
    FUpdating = false;

    SelectObject(dc, oldfont);
    DeleteObject(font);
}
void TNCProject::AutoAlign()
{//算法：循环各任务，如果要排列且不能排列，备份此任务，最后如果有要且没排列的任务
 //则再次循环各任务，否则退出，如果是备份任务，排列此任务，如果能排，继续，如果不
 //能，是循环任务错误，则退出
    try{
        FUpdating = true;
        AlignTaskPosition();
        FChart->AdjustScrollBar(true);
        AlignTaskLinkPosition();
    }__finally
    {
        FUpdating = false;
    }
}
void TNCProject::SumFrontTastLeft(TPrjObject* AObj)
{
   TPrjObject* AParent = AObj->Parent();
   if(AParent->NCLeft<-2)
     SumFrontTastLeft(AParent);
   int FrontLeft=AParent->NCLeft;
   for(int j = 0; j < AObj->FrontTaskCount; j++)
   {
        TPrjObject* AFront = AObj->FrontTasks[j]->Front;
        if(AFront->EFExpandIndex<0) continue;
        if(AFront->NCLeft<-1)
           SumFrontTastLeft(AFront);
         FrontLeft = FrontLeft > AFront->NCLeft ?
                     FrontLeft : AFront->NCLeft;

   }
   AObj->NCLeft = FrontLeft + 1;
}
bool TNCProject::PositionIsOverlap(TPrjObject *AObj,int NCTop)
{
    for(int k = 0; k < FProject->ExpandFoldTasks.Count(); k++)
    {
	  TPrjObject* Obj=FProject->ExpandFoldTasks[k];
      if((Obj->NCLeft!=AObj->NCLeft)||(AObj->Parent()!=Obj->Parent()))continue;
      if(Obj->NCTop==NCTop)
         return true;
    }
    return false;
}
void TNCProject::SumFrontTastTop(TPrjObject* AObj)
{
   if(AObj->NCTop>0) return;
   TPrjObject* AParent = AObj->Parent();
   int FrontTop=AParent->NCTop;
   int j=0;
   for(j = 0; j < AObj->FrontTaskCount; j++)
   {
		TPrjObject* AFront = AObj->FrontTasks[j]->Front;
		if((AFront->NCTop<-1)&&AFront->Parent()==AObj->Parent())
           SumFrontTastTop(AFront);
         FrontTop = FrontTop > AFront->NCTop ?
                     FrontTop : AFront->NCTop;
        if(!PositionIsOverlap(AObj,FrontTop))
            break;
   }
   if(j>=AObj->FrontTaskCount)
   {
     while(PositionIsOverlap(AObj,FrontTop))
     {
       FrontTop++ ;
     }
   }
   AObj->NCTop = FrontTop;
}

void TNCProject::AlignTaskPosition()
{
//准备环境
    TPrjObject* AObj;
    TPrjObject* AParent;
    for(int i = 0; i < FProject->Objects.Count(); i++)
    {
         AObj = FProject->Objects[i];
         AObj->NCLeft = -3;
         AObj->NCTop =-3;
    }

    FProject->NCLeft = -1;
    FProject->NCTop = 0;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
         AObj = FProject->ExpandFoldTasks[i];
         SumFrontTastLeft(AObj);
    }
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
         AObj = FProject->ExpandFoldTasks[i];
         SumFrontTastTop(AObj);
         AlignAAbstract(*AObj);//分组布局

    }

}
void TNCProject::AlignAAbstract(TPrjObject&AObj)
{
    TPrjObject* Parent = AObj.Parent();
    if(Parent)
    {
         int CurTop=AObj.NCTop;
         for(int i = 0; i < Parent->ChildCount(); i++)
         {
             TPrjObject& ABrother = Parent->GetChild(i);
             if(&ABrother==&AObj)continue;

             if((ABrother.EFExpandIndex < AObj.EFExpandIndex)/*&&(ABrother.NCLeft==AObj.NCLeft)*/)
             {
                  int BrotherMax=ABrother.NCTop;
                  if(ABrother.GetType()!=ttTask)
                  {
                     BrotherMax= GetChildMaxTop(ABrother);
                     CurTop = CurTop > BrotherMax ? CurTop : (BrotherMax + 1);
                   }
                  else
                  {
                     if((AObj.GetType()!=ttTask)||(ABrother.NCLeft==AObj.NCLeft))
                      CurTop = CurTop > BrotherMax ? CurTop : (BrotherMax + 1);
                   }
             }
         }
         AObj.NCTop = CurTop;
    }else
    {
         throw Exception("系统发生严重错误！");
    }
}
int TNCProject::GetChildMaxTop(TPrjObject&AParent)
{
    if(AParent.EFExpanded)
    {
         int Max = AParent.NCTop;
         for(int i = 0; i < AParent.ChildCount(); i++)
         {
              int CMax = GetChildMaxTop(AParent.GetChild(i));
              Max = Max < CMax ? CMax : Max;
         }
         return Max;
    }else
    {
         return AParent.NCTop;
    }
}
void TNCProject::AlignATask(TPrjObject& ATask)
{//算法：

}
void TNCProject::AlignTaskLinkPosition()
{//先清除环境，然后排列
    for(int i = 0; i < FProject->TaskLinks.Count(); i++)
    {
         FProject->TaskLinks[i]->NCPointCount = 0;
    }
    int CurrMaxTop = MaxTop();
    int CurrMaxLeft = MaxLeft();
    for(int i = 0; i <= CurrMaxTop; i++)
    {
         for(int j = 0; j <= CurrMaxLeft; j++)
         {
              TPrjObject*ATask = HaveTaskAtPosition(j, i);
              if(ATask && ATask->EFExpandIndex >= 0)
              {
                   AlignTaskTaskLinkPosition(*ATask);
              }
         }
    }
    //桥线
    for(int i = 0; i < FProject->TaskLinks.Count(); i++)
    {
         delete [] (FProject->TaskLinks[i]->NCBridgePoint);
         FProject->TaskLinks[i]->NCBridgePoint = NULL;
         FProject->TaskLinks[i]->NCBridgePointCount = 0;
    }
    for(int i = 0; i < FProject->TaskLinks.Count(); i++)
    {
         TTaskLink& ALink = *(FProject->TaskLinks[i]);
         if(ALink.Task->EFExpandIndex >= 0 && ALink.Front->EFExpandIndex >= 0)
             BuildTaskLinkBridge(ALink);
    }
}
//---------------------------------------------------------------------
struct TLateTaskTop
{
    int          Top;
    TTaskLink* TaskLink;
};
void TNCProject::AlignTaskTaskLinkPosition(TPrjObject&ATask)
{
   if(ATask.LateTaskCount <= 0)
       return;

   const int __MaxIntTop__ = 0x0fffffff;

   StackArray<TLateTaskTop, 512> LateTop(ATask.LateTaskCount);
   for(int i = 0; i < ATask.LateTaskCount; i++)
   {
       LateTop[i].TaskLink = ATask.LateTasks[i];
       LateTop[i].Top = LateTop[i].TaskLink->Task->NCTop;
   }
   while(true)
   {
       int MinIndex = -1;
       int Min = __MaxIntTop__;
       for(int i = 0; i < ATask.LateTaskCount; i++)
       {
           if(LateTop[i].Top < Min)
           {
               Min = LateTop[i].Top;
               MinIndex = i;
           }
       }
       if(MinIndex == -1)
			break;
       TTaskLink&ALink = *(LateTop[MinIndex].TaskLink);
       LateTop[MinIndex].Top = __MaxIntTop__;
       if(ALink.NCPointCount <= 0)
           AlignALink(ALink);
   }
}
void TNCProject::AlignALink(TTaskLink&ALink)
{
   int FirstLeft = ALink.Front->NCLeft;
   int FirstTop = ALink.Front->NCTop;
   int LastLeft = ALink.Task->NCLeft;
   int LastTop = ALink.Task->NCTop;
   if(FirstLeft + 1 == LastLeft)//相邻的
   {
       if(abs(FirstTop - LastTop) < 1)
       {
                      ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                      ALink.NCPoint[1] = TaskLink_LastPoint(ALink);
                      //AlignTaskLinkLines(ALink.NCPoint, 2);
                      ALink.NCPointCount = 2;
                      ALink.NCBridgeLineIndex = -1;
       }else
       {
                      ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                      ALink.NCPoint[3] = TaskLink_LastPoint(ALink);
                      ALink.NCPoint[1].x = PointLeft(FirstLeft+1);
                      ALink.NCPoint[1].y = ALink.NCPoint[0].y;
                      ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                      ALink.NCPoint[2].y = ALink.NCPoint[3].y;
                      AlignTaskLinkLines(ALink.NCPoint, 4);
                      ALink.NCPointCount = 4;
                      ALink.NCBridgeLineIndex = 1;
       }
       return;
   }else if(FirstTop == LastTop)//平行
   {
       if(FirstLeft >= LastLeft)
           goto labelNotCanIndirect;
       for(int i = FirstLeft+1; i < LastLeft; i++)
       {
           if(HaveTaskAtPosition(i, FirstTop))
           {
              goto labelNotCanIndirect;
           }
       }
	   //直接连线
				  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
				  ALink.NCPoint[1] = TaskLink_LastPoint(ALink);
				  AlignTaskLinkLines(ALink.NCPoint, 2);
				  ALink.NCPointCount = 2;
				  ALink.NCBridgeLineIndex = -1;
       goto LabelExitFirstTopEquelLastTop;
   labelNotCanIndirect://从上面绕过
                  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                  ALink.NCPoint[1].x = PointLeft(FirstLeft+1);
                  ALink.NCPoint[1].y = ALink.NCPoint[0].y;
                  ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                  ALink.NCPoint[2].y = PointTop(FirstTop);

                  ALink.NCPoint[3].x = PointLeft(LastLeft);
                  ALink.NCPoint[3].y = ALink.NCPoint[2].y;
                  ALink.NCPoint[5] = TaskLink_LastPoint(ALink);
                  ALink.NCPoint[4].x = ALink.NCPoint[3].x;
                  ALink.NCPoint[4].y = ALink.NCPoint[5].y;
                  AlignTaskLinkLines(ALink.NCPoint, 6);
                  ALink.NCPointCount = 6;
                  ALink.NCBridgeLineIndex = -1;
   LabelExitFirstTopEquelLastTop:
       return;
   }else if(FirstLeft >= LastLeft)//在开始列大于等于结束列
   {
                  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                  ALink.NCPoint[1].x = PointLeft(FirstLeft+1);
                  ALink.NCPoint[1].y = ALink.NCPoint[0].y;
                  if(FirstTop < LastTop)//在下面
                  {
                      ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                      ALink.NCPoint[2].y = PointTop(FirstTop+1);
                  }else//在上面
                  {
                      ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                      ALink.NCPoint[2].y = PointTop(FirstTop);
                  }
                  ALink.NCPoint[3].x = PointLeft(LastLeft);
                  ALink.NCPoint[3].y = ALink.NCPoint[2].y;
                  ALink.NCPoint[5] = TaskLink_LastPoint(ALink);
                  ALink.NCPoint[4].x = ALink.NCPoint[3].x;
                  ALink.NCPoint[4].y = ALink.NCPoint[5].y;
                  AlignTaskLinkLines(ALink.NCPoint, 6);
                  ALink.NCPointCount = 6;
                  ALink.NCBridgeLineIndex = 3;
       return;
   }else if(FirstLeft < LastLeft)//在开始列小于等于结束列
   {
       int LeftToRightLastEmpty = FirstLeft;//看开始任务的右边直到结束任务有没有任务
       for(int i = FirstLeft+1; i < LastLeft; i++)
       {
           if(HaveTaskAtPosition(i, FirstTop))
               goto labelExitLeftToRightLastEmpty;
           LeftToRightLastEmpty = i;
       }
       //由开始向右一直到结束任务
                  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                  ALink.NCPoint[3] = TaskLink_LastPoint(ALink);
                  ALink.NCPoint[2].x = PointLeft(LastLeft);
                  ALink.NCPoint[2].y = ALink.NCPoint[3].y;
                  ALink.NCPoint[1].x = ALink.NCPoint[2].x;
                  ALink.NCPoint[1].y = ALink.NCPoint[0].y;
                  AlignTaskLinkLines(ALink.NCPoint, 4);
                  ALink.NCPointCount = 4;
                  ALink.NCBridgeLineIndex = 1;
       return;
   labelExitLeftToRightLastEmpty:
       int RightToLeftFirstEmpty = LastLeft;
       for(int i = LastLeft-1; i > FirstLeft; i--)
       {
           if(HaveTaskAtPosition(i, LastTop))
               goto labelExitRightToLeftFirstEmpty;
           RightToLeftFirstEmpty = i;
       }
       //由开始拐弯到结束任务的y, 向右一直到结束任务
                  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                  ALink.NCPoint[3] = TaskLink_LastPoint(ALink);
                  ALink.NCPoint[1].x = PointLeft(FirstLeft+1);
                  ALink.NCPoint[1].y = ALink.NCPoint[0].y;
                  ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                  ALink.NCPoint[2].y = ALink.NCPoint[3].y;
                  AlignTaskLinkLines(ALink.NCPoint, 4);
                  ALink.NCPointCount = 4;
                  ALink.NCBridgeLineIndex = 1;
	   return;
   labelExitRightToLeftFirstEmpty:
       if(LeftToRightLastEmpty+1 >= RightToLeftFirstEmpty)
	   {//由开始拐弯到开始和结束任务的中间, 向右一直到结束任务
				  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
				  ALink.NCPoint[3] = TaskLink_LastPoint(ALink);
				  ALink.NCPoint[1].x = (PointLeft(LeftToRightLastEmpty+1) +
						   PointLeft(RightToLeftFirstEmpty)) / 2;
				  ALink.NCPoint[1].y = ALink.NCPoint[0].y;
				  ALink.NCPoint[2].x = ALink.NCPoint[1].x;
				  ALink.NCPoint[2].y = ALink.NCPoint[3].y;
				  AlignTaskLinkLines(ALink.NCPoint, 4);
                  ALink.NCPointCount = 4;
				  ALink.NCBridgeLineIndex = 1;
           return;
       }
       //开始之后拐弯，向右到结束时再拐弯
                  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                  ALink.NCPoint[1].x = PointLeft(FirstLeft+1);
                  ALink.NCPoint[1].y = ALink.NCPoint[0].y;
                  if(FirstTop < LastTop)//在下面
                  {
                      ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                      ALink.NCPoint[2].y = PointTop(FirstTop+1);
                  }else//在上面
                  {
                      ALink.NCPoint[2].x = ALink.NCPoint[1].x;
                      ALink.NCPoint[2].y = PointTop(FirstTop);
                  }
                  ALink.NCPoint[3].x = PointLeft(LastLeft);
                  ALink.NCPoint[3].y = ALink.NCPoint[2].y;
                  ALink.NCPoint[5] = TaskLink_LastPoint(ALink);
                  ALink.NCPoint[4].x = ALink.NCPoint[3].x;
                  ALink.NCPoint[4].y = ALink.NCPoint[5].y;
                  AlignTaskLinkLines(ALink.NCPoint, 6);
                  ALink.NCPointCount = 6;
                  ALink.NCBridgeLineIndex = 3;
       return;
   }else
   {
                  ALink.NCPoint[0] = TaskLink_FirstPoint(ALink);
                  ALink.NCPoint[1] = TaskLink_LastPoint(ALink);
                  ALink.NCPointCount = 2;
                  ALink.NCBridgeLineIndex = -1;
   }
}
void TNCProject::AlignTaskLinkLines(POINT*p1, int PointCount)
{
   for(int i = 1; i < PointCount-2; i++)
   {//从第二条线段到到数第二条才需要调整
       AlingALine(p1[i], p1[i+1]);
   }
}
void TNCProject::AlingALine(POINT&p1, POINT&p2)
{
/*
   在所有已排好的线段中找出和要排线端重合的线段，根据已排好线端的位置找
   一个空的，如果没有空位，则不排退出
*/
   if(p1.x == p2.x)
   {//竖线
           int AllowWidth = FChart->FColDistance / 4;
           if(AllowWidth < 4)
               return;
           TTaskLink* CurrTaskLink;
           int HaveLineAtX[20];
           int HaveLineAtXCount(0);
           for(int i = 0; i < FProject->TaskLinks.Count(); i++)
           {//找所有的连线
                CurrTaskLink = FProject->TaskLinks[i];
                if(CurrTaskLink->NCPointCount > 0)
                {//已排好的才能算数
                     for(int i = 1; i < CurrTaskLink->NCPointCount-2; i++)
                     {//找联线的第二线段到倒竖第二条线段
                          POINT &currp1 = CurrTaskLink->NCPoint[i];
                          POINT &currp2 = CurrTaskLink->NCPoint[i+1];
                          if(currp1.x == currp2.x &&
                             currp1.x <= p1.x &&
                             currp1.x >= p1.x - AllowWidth
                             )
                          {//如果在同一列上
                                          if((currp1.y > p1.y && currp1.y < p2.y) ||
                                             (currp2.y > p1.y && currp2.y < p2.y))
                                          {
                                              if(HaveLineAtXCount < 20)
                                              {
                                                   HaveLineAtX[HaveLineAtXCount] = currp1.x;
                                                   HaveLineAtXCount++;
                                              }else
                                              {
                                                   return;
                                              }
                                          }else if((p1.y > currp1.y && p1.y < currp2.y) ||
                                             (p2.y > currp1.y && p2.y < currp2.y))
                                          {
                                              if(HaveLineAtXCount < 20)
                                              {
                                                   HaveLineAtX[HaveLineAtXCount] = currp1.x;
                                                   HaveLineAtXCount++;
                                              }else
                                              {
                                                   return;
                                              }
                                          }
                          }
                     }
                }
           }
           int Min = p1.x;
           for(int i = 0; i < HaveLineAtXCount; i++)
           {
               Min = HaveLineAtX[i] <= Min ? (HaveLineAtX[i] - 3) : Min;
           }
           if(Min < p1.x - AllowWidth)
               return;
           p1.x = Min;
           p2.x = Min;
           return;
   }else if(p1.y == p2.y)
   {//横线
           int AllowHeight = FChart->FRowDistance / 4;
           if(AllowHeight < 4)
               return;
           TTaskLink* CurrTaskLink;
           int HaveLineAtY[20];
           int HaveLineAtYCount(0);
           for(int i = 0; i < FProject->TaskLinks.Count(); i++)
           {//在所有连线中找
                CurrTaskLink = FProject->TaskLinks[i];
                if(CurrTaskLink->NCPointCount > 0)
                {
                     for(int i = 1; i < CurrTaskLink->NCPointCount-2; i++)
                     {
                          POINT &currp1 = CurrTaskLink->NCPoint[i];
                          POINT &currp2 = CurrTaskLink->NCPoint[i+1];
                          if(currp1.y == currp2.y &&
                             currp1.y <= p1.y + AllowHeight &&
                             currp1.y >= p1.y - AllowHeight
                             )
                          {//如果在同一行
                                          if((currp1.x > p1.x && currp1.x < p2.x) ||
                                             (currp2.x > p1.x && currp2.x < p2.x))
                                          {
                                              if(HaveLineAtYCount < 20)
                                              {
                                                   HaveLineAtY[HaveLineAtYCount] = currp1.y;
                                                   HaveLineAtYCount++;
                                              }else
                                              {
                                                   return;
                                              }
                                          }else if((p1.x > currp1.x && p1.x < currp2.x) ||
                                             (p2.x > currp1.x && p2.x < currp2.x))
                                          {
                                              if(HaveLineAtYCount < 20)
                                              {
                                                   HaveLineAtY[HaveLineAtYCount] = currp1.y;
                                                   HaveLineAtYCount++;
                                              }else
                                              {
                                                   return;
                                              }
                                          }
                          }
                     }
                }
           }
           int Min = p1.y;
           int Max = p1.y;
           for(int i = 0; i < HaveLineAtYCount; i++)
           {
               Min = HaveLineAtY[i] <= Min ? (HaveLineAtY[i] - 3) : Min;
               Max = HaveLineAtY[i] >= Max ? (HaveLineAtY[i] + 3) : Max;
           }
           if(Max - p1.y < p1.y - Min)
           {
               if(Max > p1.y + AllowHeight)
                   return;
               p1.y = Max;
               p2.y = Max;
           }else
           {
               if(Min < p1.y - AllowHeight)
                   return;
               p1.y = Min;
               p2.y = Min;
           }
           return;
   }else
   {
       throw Exception("TNCProject::AlingALine 直线类型错误");
   }
}
void TNCProject::BuildTaskLinkBridge(TTaskLink&ALink)
{
   if(ALink.NCBridgeLineIndex <= 0)
       return;

   StackArray<POINT, 1024> pb(FProject->TaskLinks.Count());
   int pbIndex(0);
   POINT bridgep1 = ALink.NCPoint[ALink.NCBridgeLineIndex];
   POINT bridgep2 = ALink.NCPoint[ALink.NCBridgeLineIndex+1];
   if(bridgep1.x != bridgep2.x)
   {
       throw Exception("逻辑错误！");
   }else
   {
       if(bridgep1.y > bridgep2.y)
       {//如果点1在点2的下面，交换他们，保持从上到下的顺序
           POINT temp = bridgep1;
           bridgep1 = bridgep2;
           bridgep2 = temp;
       }
   }
   for(int i = 0; i < FProject->TaskLinks.Count(); i++)
   {//循环所有的连接，不包括本连接,因为自己不和自己相交
	   TTaskLink& ProcessLink = *(FProject->TaskLinks[i]);
       if(&ProcessLink != &ALink && ProcessLink.Task->EFExpandIndex >= 0 &&
           ProcessLink.Front->EFExpandIndex >= 0)
       {
            for(int j = 0; j < ProcessLink.NCPointCount-1; j++)
            {
                POINT& ProcessP1 = ProcessLink.NCPoint[j];
                POINT& ProcessP2 = ProcessLink.NCPoint[j+1];
                if(ProcessP1.y == ProcessP2.y)
                {//是横线
                                if(ProcessP1.y > bridgep1.y && ProcessP2.y < bridgep2.y)
                                {
                                    if(ProcessP1.x < ProcessP2.x)
                                    {
                                         if(ProcessP1.x < bridgep1.x && ProcessP2.x > bridgep1.x)
                                         {
                                              goto labelAddBridge;
                                         }else
                                         {
                                              goto labelLoop;
                                         }
                                    }
                                    if(ProcessP1.x > ProcessP2.x)
                                    {
                                         if(ProcessP1.x > bridgep1.x && ProcessP2.x < bridgep1.x)
                                         {
                                              goto labelAddBridge;
                                         }else
                                         {
                                              goto labelLoop;
                                         }
                                    }
                                }
                }
                goto labelLoop;
                labelAddBridge://加入一个桥点
                     pb[pbIndex].x = bridgep1.x;
                     pb[pbIndex].y = ProcessP1.y;
                     pbIndex++;
                labelLoop:
            }
       }
   }
   if(pbIndex > 0)
   {
       //由小到大排序
       for(int i = 0; i < pbIndex; i++)
       {
            for(int j = i; j < pbIndex; j++)
            {
                 if(pb[j].y < pb[i].y)
                 {
                      POINT temp = pb[i];
                      pb[i] = pb[j];
                      pb[j] = temp;
                 }
            }
       }
       //去除重复的点
       for(int i = 0; i < pbIndex-1; i++)
       {
            if(pb[i+1].y - pb[i].y < 3)
            {
                 //将后续的点前移
                 for(int j = i+1; j < pbIndex; j++)
                      pb[j] = pb[j+1];
                 pbIndex--;
                 i--;
            }
       }
       ALink.NCBridgePoint = new POINT[pbIndex];
       ALink.NCBridgePointCount = pbIndex;
       memcpy(ALink.NCBridgePoint, pb, sizeof(POINT)*pbIndex);
   }
}
TPrjObject* TNCProject::HaveTaskAtPosition(int Left, int Top)
{
    TPrjObject* t;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
       t = FProject->ExpandFoldTasks[i];
       if(t->NCLeft == Left && t->NCTop == Top)
          return t;
    }
    return NULL;
}
TPrjObject* TNCProject::HaveTaskAtPoint(int x, int y)
{
    TPrjObject* t;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
    {
       t = FProject->ExpandFoldTasks[i];
       if(((t->NCLeft)*(FChart->FTaskWidth+FChart->FColDistance) + FChart->FColDistance/2) <= x &&
          ((t->NCTop)*(FChart->FTaskHeight+FChart->FRowDistance) + FChart->FRowDistance/2) <= y &&
          ((t->NCLeft+1)*(FChart->FTaskWidth+FChart->FColDistance) - FChart->FColDistance/2) >= x &&
          ((t->NCTop+1)*(FChart->FTaskHeight+FChart->FRowDistance) - FChart->FRowDistance/2) >= y)
          return t;
    }
    return NULL;
}
int TNCProject::MaxLeft()
{
    int Max = 0;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
       Max = Max > FProject->ExpandFoldTasks[i]->NCLeft ? Max : FProject->ExpandFoldTasks[i]->NCLeft;
    return Max;
}
int TNCProject::MaxTop()
{
    int Max = 0;
    for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
       Max = Max > FProject->ExpandFoldTasks[i]->NCTop ? Max : FProject->ExpandFoldTasks[i]->NCTop;
    return Max;
}
void __fastcall TNCProject::MouseDown(TMouseButton Button,
        Classes::TShiftState Shift, int X, int Y)
{
    FUpdating = true;
    TPrjObject* bkSelected = FProject->Selected;
    try{
        if(StartExpandFold(X, Y))
            return;  
        if(StartDragTask(X, Y))
            return;
    }__finally
    {
        if(bkSelected != FProject->Selected)
        {
           FChart->Invalidate();
        }
        FUpdating = false;
    }
}
void __fastcall TNCProject::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
    switch(FAct)
    {
       case naNone:
          break;
       case naDragTask:
          DragingTask(X, Y);
          break;
       case naExpandFold:
          break;
       default:
          throw Exception("网络图动作错误");//无处理
    }
}
void __fastcall TNCProject::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
    try{
       FUpdating = true;
       switch(FAct)
       {
          case naNone:
             break;
          case naDragTask:
             EndDragTask(X, Y);
             break;
          case naExpandFold:
             EndExpandFold(X, Y);
             break;
          default:
             throw Exception("网络图动作错误");//无处理
       }
    }__finally
    {
       FUpdating = false;
    }
}
bool TNCProject::StartDragTask(int X, int Y)
{
   RECT r;
   TPrjObject* t;
   for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
   {
      t = FProject->ExpandFoldTasks[i];
      r = Task_ClientRect(*t);
      if(X >= r.left && X <= r.right && Y >= r.top && Y <= r.bottom)
      {
         FProject->Selected = t;
         FMoveRect = PointAtRect(X, Y);
         FAct = naDragTask;
         SetCapture(FChart->Handle);
         return true;
      }
   }
   return false;
}
void TNCProject::DragingTask(int X, int Y)
{
   RECT NewRect = PointAtRect(X, Y);
   if(NewRect.left != FMoveRect.left || NewRect.top != FMoveRect.top)
   {
        FChart->Invalidate();
		HDC dc = FChart->GetDrawDc();
        FMoveRect = NewRect;
        DrawFrame(dc, NewRect, dftMove);
        ReleaseDC(FChart->Handle, dc);
   }
}
void TNCProject::EndDragTask(int X, int Y)
{
   FAct = naNone;
   if(FProject->Selected != NULL)
   {
	  ReleaseCapture();
	  POINT Pos = PointAtTaskPosition(X, Y);
      if(FProject->Selected->NCLeft == Pos.x && FProject->Selected->NCTop == Pos.y)
      {
         FChart->Invalidate();
      }else
      {
         FProject->Selected->NCLeft = Pos.x;
         FProject->Selected->NCTop = Pos.y;
         AlignTaskLinkPosition();
         FChart->AdjustScrollBar();
         FChart->Invalidate();
      }
   }
}
bool TNCProject::StartExpandFold(int X, int Y)
{
   RECT r;
   TPrjObject* t;
   for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
   {
       if(FProject->ExpandFoldTasks.CanExpandFold(i))
       {
           t = FProject->ExpandFoldTasks[i];
           r = Task_ClientRect(*t);
           if(X >= r.left && X <= r.left + 10 && Y < r.top && Y >= r.top - 13)
           {
               if(t->EFExpanded)
                   FProject->ExpandFoldTasks.Fold(i);
               else
                   FProject->ExpandFoldTasks.Expand(i);
               FProject->Selected = t;
               FAct = naExpandFold;
               SetCapture(FChart->Handle);
               AutoAlign();
               FChart->Invalidate();
               FChart->ShowNavigation();/////
               return true;
           }
       }
   }
   return false;
}
void TNCProject::EndExpandFold(int X, int Y)
{
    FAct = naNone;
}
inline RECT TNCProject::PointAtRect(int X, int Y)
{
    RECT r;
    r.left = X - X % (FChart->FTaskWidth+FChart->FColDistance);
    r.left += FChart->FColDistance / 2;
    r.right = r.left + FChart->FTaskWidth;
    r.top = Y - Y % (FChart->FTaskHeight+FChart->FRowDistance);
    r.top += FChart->FRowDistance / 2;
    r.bottom = r.top + FChart->FTaskHeight;
    return r;
}
inline POINT TNCProject::PointAtTaskPosition(int X, int Y)
{
    POINT r;
    r.x = X / (FChart->FTaskWidth + FChart->FColDistance);
    r.y = Y / (FChart->FTaskHeight + FChart->FRowDistance);
    return r;
}
inline RECT TNCProject::PositionAtRect(int Left, int Top)
{
    RECT r;
    r.left = Left * (FChart->FTaskWidth + FChart->FColDistance);
    r.right = r.left + FChart->FTaskWidth + FChart->FColDistance;
    r.top = Top * (FChart->FTaskHeight + FChart->FRowDistance);
    r.bottom = r.top + FChart->FTaskHeight + FChart->FRowDistance;
    return r;
}
int TNCProject::PointTop(int Top)
{
    return Top * (FChart->FTaskHeight + FChart->FRowDistance);
}
int TNCProject::PointLeft(int Left)
{
    return Left * (FChart->FTaskWidth + FChart->FColDistance);
}
int TNCProject::PointYMiddle(int Top)
{
    return Top * (FChart->FTaskHeight + FChart->FRowDistance) +
           (FChart->FTaskHeight + FChart->FRowDistance) / 2;
}
void TNCProject::DrawFrame(HDC dc, RECT dr, DrawFrameType Type)
{
    switch(Type)
    {
       case dftNormal:
       {
           break;
       }
       case dftFocus:
       {
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

void __fastcall TNCProject::SetProject(TProject*AProject)
{
    if(FMustDelete)
    {
        delete FProject;
        FMustDelete = false;
    }
    if(FProject != AProject)
    {
        FProject = AProject;
        FNCPrjDataChangeLink->SetProject(FProject);
    }
}
TPoint* TNCProject::FindTaskByName(const String TaskName)
{
  TPoint *pt = NULL;
  RECT r;
  for(int i = 0; i < FProject->ExpandFoldTasks.Count(); i++)
  {
    if(TaskName==FProject->ExpandFoldTasks[i]->Name)
    {
      r = Task_ClientRect(*FProject->ExpandFoldTasks[i]);
      pt = new TPoint();
      pt->x = (r.left + r.right)/2;
      pt->y = (r.top + r.bottom)/2;
      FProject->Selected = FProject->ExpandFoldTasks[i] ;
      break;
    }
  }
  return pt;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TNetChart::TNetChart(TComponent* Owner)
        : TWinControl(Owner)
{

    DoubleBuffered = true;
    TControlStyle cs;
    cs<<csAcceptsControls<<csCaptureMouse<<csClickEvents<<
		 csSetCaption<<csDoubleClicks<<csMenuEvents;
	this->ControlStyle = cs;
    FProject = new TNCProject(this);

    Width = 200;
    Height = 180;
	Color = clWhite;
    FShowZoom = ncszNormal;

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

    SetDefault();
}
//---------------------------------------------------------------------------
__fastcall TNetChart::~TNetChart()
{
    if(FPrintHandle)
    {
	   delete ((TNetChartPrint*)(FPrintHandle));
	}
    delete FProject;
}
//---------------------------------------------------------------------------
void __fastcall TNetChart::PaintWindow(HDC DC)
{
	if(FTaskHeight == -1)
        FTaskHeight = CalcTaskHeight(DC);
    RECT dr = ClientRect;
    dr.left += FHORZ.nPos;
    dr.right += FHORZ.nPos;
    dr.top += FVERT.nPos;
    dr.bottom += FVERT.nPos;
    SetBkMode(DC, TRANSPARENT);
    SetViewportOrgEx(DC, -FHORZ.nPos, -FVERT.nPos, NULL);
    SetBrushOrgEx(DC, (8 - FHORZ.nPos % 8), (8-FVERT.nPos % 8), NULL);
    FProject->Draw(DC, dr);

    SetViewportOrgEx(DC, 0, 0, NULL);
}
HDC TNetChart::GetDrawDc()
{
	HDC dc = GetDC(Handle);
    SetViewportOrgEx(dc, -FHORZ.nPos, -FVERT.nPos, NULL);
    return dc;
}
void __fastcall TNetChart::WMPaint(Messages::TWMPaint &Message)
{
    ControlState << csCustomPaint;
    TWinControl::Dispatch(&Message);
    ControlState >> csCustomPaint;
}
void __fastcall TNetChart::WMHScroll(Messages::TMessage &Message)
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
   // If the current position does not change, do not scroll.
   xDelta = xNewPos - FHORZ.nPos;
   // Reset the current scroll position.
   FHORZ.nPos = xNewPos;
   ScrollWindow(Handle, -xDelta, 0, NULL, NULL);
   UpdateWindow(Handle);
   // Reset the scroll bar.
   SetScrollPos(Handle, SB_HORZ, xNewPos, true);

   if(NaviImage && NaviImage->Showing)
	 NaviImage->SetFrameRect(FHORZ.nPos,FVERT.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TNetChart::Resize(void)
{
   if(NaviImage && NaviImage->Showing)
	 NaviImage->SetFrameRect(ClientRect,FHORZ.nPos,FVERT.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TNetChart::WMVScroll(Messages::TMessage &Message)
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

   if(NaviImage && NaviImage->Showing)
     NaviImage->SetFrameRect(FHORZ.nPos,FVERT.nPos);
}
void __fastcall TNetChart::WMKeyDown(Messages::TWMKey &Message)
{
    TWinControl::Dispatch(&Message);
    TMessage msg;
    switch(Message.CharCode)
    {
        case VK_LEFT:
            msg.Msg = WM_HSCROLL;
            msg.WParamLo = SB_LINELEFT;
            Dispatch(&msg);
            break;
        case VK_UP:
            msg.Msg = WM_VSCROLL;
            msg.WParamLo = SB_LINEUP;
            Dispatch(&msg);
            break;
        case VK_RIGHT:
            msg.Msg = WM_HSCROLL;
            msg.WParamLo = SB_LINERIGHT;
            Dispatch(&msg);
            break;
        case VK_DOWN:
            msg.Msg = WM_VSCROLL;
            msg.WParamLo = SB_LINEDOWN;
            Dispatch(&msg);
            break;
        default:
            ;//无处理
    }
    SetFocus();
}
void __fastcall TNetChart::WMKeyUp(Messages::TWMKey &Message)
{
    TWinControl::Dispatch(&Message);
}
void __fastcall TNetChart::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
    GetScrollInfo(Handle, SB_VERT, &FVERT);
    GetScrollInfo(Handle, SB_HORZ, &FHORZ);
    FProject->MouseDown(Button, Shift, X+FHORZ.nPos, Y+FVERT.nPos);
    SetFocus();
}
void __fastcall TNetChart::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
    GetScrollInfo(Handle, SB_VERT, &FVERT);
    GetScrollInfo(Handle, SB_HORZ, &FHORZ);
    FProject->MouseMove(Shift, X+FHORZ.nPos, Y+FVERT.nPos);
}
void __fastcall TNetChart::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
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
void __fastcall TNetChart::Click(void)
{
/*   SetFocus();
   if(FOnTaskClick && FProject->Selected)
      FOnTaskClick(FProject, FProject->SelectTask);
   if(FOnTaskLinkClick && FProject->SelectTaskLink)
      FOnTaskLinkClick(FProject, FProject->SelectTaskLink->Task, FProject->SelectTaskLink);
   if(FOnNoneTaskClick && !FProject->SelectTask && !FProject->SelectTaskLink)
   {
      POINT point;
      GetCursorPos(&point);
	  GetScrollInfo(Handle, SB_VERT, &FVERT);
	  GetScrollInfo(Handle, SB_HORZ, &FHORZ);
	  point.x = point.x - ClientOrigin.x + FHORZ.nPos;
	  point.y = point.y - ClientOrigin.y + FVERT.nPos;
	  point = FProject->PointAtTaskPosition(point.x, point.y);
	  FOnNoneTaskClick(FProject, point.x, point.y);
   }*/
}
void __fastcall TNetChart::WMDblClick(Messages::TMessage &Message)
{
   TWinControl::Dispatch(&Message);
   FProject->FAct = TNCProject::naNone;
   if(FOnTaskDblClick && FProject->Project->Selected)
      FOnTaskDblClick(FProject->Project, FProject->Project->Selected);
/*   if(FOnTaskLinkDblClick && FProject->SelectTaskLink)
      FOnTaskLinkDblClick(FProject, FProject->SelectTaskLink->Task, FProject->SelectTaskLink);
   if(FOnNoneTaskDblClick && !FProject->SelectTask && !FProject->SelectTaskLink)
   {
      POINT point;
      GetCursorPos(&point);
      GetScrollInfo(Handle, SB_VERT, &FVERT);
      GetScrollInfo(Handle, SB_HORZ, &FHORZ);
      point.x = point.x - ClientOrigin.x + FHORZ.nPos;
      point.y = point.y - ClientOrigin.y + FVERT.nPos;
      point = FProject->PointAtTaskPosition(point.x, point.y);
      FOnNoneTaskDblClick(FProject, point.x, point.y);
   }*/
}
/*void __fastcall TNetChart::DblClick(void)
{
   TWinControl::DblClick();
   if(FOnTaskDblClick && FProject->SelectTask)
	  FOnTaskDblClick(FProject, FProject->SelectTask);
   if(FOnTaskLinkDblClick && FProject->SelectTaskLink)
	  FOnTaskLinkDblClick(FProject, FProject->SelectTaskLink->Task, FProject->SelectTaskLink);
   if(FOnNoneTaskDblClick && !FProject->SelectTask && !FProject->SelectTaskLink)
   {
	  POINT point;
	  GetCursorPos(&point);
	  GetScrollInfo(Handle, SB_VERT, &FVERT);
	  GetScrollInfo(Handle, SB_HORZ, &FHORZ);
	  point.x = point.x - ClientOrigin.x + FHORZ.nPos;
	  point.y = point.y - ClientOrigin.y + FVERT.nPos;
	  point = FProject->PointAtTaskPosition(point.x, point.y);
	  FOnNoneTaskDblClick(FProject, point.x, point.y);
   }
} */
void __fastcall TNetChart::AdjustSize(void)
{
   TWinControl::AdjustSize();
   AdjustScrollBar();
}
void TNetChart::AdjustScrollBar(bool Force)
{
    if(FTaskHeight <= 1)
    {
       HDC dc = CreateCompatibleDC(NULL);
       FTaskHeight = CalcTaskHeight(dc);
       DeleteDC(dc);
    }
    FHORZ.fMask = SIF_ALL;
    FHORZ.nMin = 0;
    FHORZ.nPage = 0;
    int Max = FProject->MaxLeft();
    Max = (Max+2)*(FTaskWidth + FColDistance) - ClientRect.Width();
    if(Force || FHORZ.nMax < Max)
    {
       FHORZ.nMax = Max;
       if(FHORZ.nPos > Max)
          FHORZ.nPos = Max;
       if(FHORZ.nPos < 0)
          FHORZ.nPos = 0;
       SetScrollInfo(Handle, SB_HORZ, &FHORZ, true);
    }

    FVERT.fMask = SIF_ALL;
    FVERT.nMin = 0;
    FVERT.nPage = 0;
    Max = FProject->MaxTop();
    Max = (Max+2)*(FTaskHeight + FRowDistance) - ClientRect.Height();
    if(Force || FVERT.nMax < Max)
    {
       FVERT.nMax = Max;
       if(FVERT.nPos > Max)
          FVERT.nPos = Max;
       if(FVERT.nPos < 0)
          FVERT.nPos = 0;
       SetScrollInfo(Handle, SB_VERT, &FVERT, true);
    }
}

void TNetChart::Draw(HDC dc, RECT dr)
{
   if(FTaskHeight == -1)
   {
        HDC adc = GetDC(Handle);
        FTaskHeight = CalcTaskHeight(adc);
        ReleaseDC(Handle, adc);
   }
   FProject->Draw(dc, dr);
}

void TNetChart::AutoAlign()
{
   FProject->AutoAlign();
}
void TNetChart::AlignLines()
{
    if(FTaskHeight <= 1)
    {
       HDC dc = CreateCompatibleDC(NULL);
       FTaskHeight = CalcTaskHeight(dc);
       DeleteDC(dc);
    }
    FProject->AlignTaskLinkPosition();
}
TProject* __fastcall TNetChart::GetProject()
{
   return FProject->Project;
}

void __fastcall TNetChart::SetProject(TProject*AProject)
{
   FProject->Project = AProject;
}

int TNetChart::CalcTaskHeight(HDC dc)
{
   TFont* AFont = new TFont();
   AFont->Assign(Font);
   AFont->Height = AFont->Height * ShowZoom / ncszNormal;
   HFONT font = CreateFontByTFont(AFont);
   delete AFont;

   HGDIOBJ oldFont = SelectObject(dc, font);

   FProject->CriticalNotStartDraw.Init(dc);
   FProject->CriticalStartedDraw.Init(dc);
   FProject->CriticalOveredDraw.Init(dc);
   FProject->NotStartDraw.Init(dc);
   FProject->StartedDraw.Init(dc);
   FProject->OveredDraw.Init(dc);
   FProject->AbstractDraw.Init(dc);//摘要任务
   FProject->MarkerDraw.Init(dc);//里程碑
   FProject->WarningDraw.Init(dc);//有问题任务
   FProject->ForeignNotStartDraw.Init(dc);//外部未开工
   FProject->CriticalForeignNotStartDraw.Init(dc);//外部未开工
   FProject->ForeignStartedDraw.Init(dc);//外部已开工
   FProject->CriticalForeignStartedDraw.Init(dc);//外部已开工
   FProject->ForeignOveredDraw.Init(dc);//外部已完工
   FProject->CriticalForeignOveredDraw.Init(dc);//外部已完工
   FProject->ForeignAbstractDraw.Init(dc);//外部摘要任务
   FProject->ForeignMarkerDraw.Init(dc);//外部里程碑
   FProject->ForeignProjectDraw.Init(dc);//外部工程

   SelectObject(dc, oldFont);
   DeleteObject(font);

   return FProject->CriticalNotStartDraw.ItemHeight * 5 + 2;
}
void __fastcall TNetChart::SetTaskWidth(int AWidth)
{
    if(AWidth >= 40)
    {
        FTaskWidth = AWidth * FShowZoom / ncszNormal;
    }
}
void __fastcall TNetChart::SetColDistance(int AWidth)
{
    FColDistance = AWidth * FShowZoom / ncszNormal;
}
void __fastcall TNetChart::SetRowDistance(int AHeight)
{
    FRowDistance = AHeight * FShowZoom / ncszNormal;
}
int __fastcall TNetChart::GetTaskWidth()
{
    return FTaskWidth * ncszNormal / FShowZoom;
}
int __fastcall TNetChart::GetTaskHeight()
{
    return FTaskHeight * ncszNormal / FShowZoom;
}
int __fastcall TNetChart::GetColDistance()
{
    return FColDistance * ncszNormal / FShowZoom;
}
int __fastcall TNetChart::GetRowDistance()
{
    return FRowDistance * ncszNormal / FShowZoom;
}
void __fastcall TNetChart::SetShowZoom(TNCShowZoom Zoom)
{
    TNCShowZoom oldZoom = FShowZoom;
    FShowZoom = Zoom;

    FTaskWidth = FTaskWidth * Zoom / oldZoom;
    FColDistance = FColDistance * Zoom / oldZoom;
    FRowDistance = FRowDistance * Zoom / oldZoom;

    FTaskHeight = -1;
    AdjustScrollBar();
    FProject->AlignTaskLinkPosition();
    ShowNavigation();
}
TPrintHandle __fastcall TNetChart::GetPrintHandle()
{
    if(FPrintHandle)
    {
    }else
    {
	   FPrintHandle = new TNetChartPrint(this);
    }
    return FPrintHandle;
}
int __fastcall TNetChart::GetTotalHeight()
{
    int Max = FProject->MaxTop();
    Max = (Max+2)*(FTaskHeight + FRowDistance);
    return Max;
}
int __fastcall TNetChart::GetTotalWidth()
{
    int Max = FProject->MaxLeft();
    Max = (Max+2)*(FTaskWidth + FColDistance);
    return Max;
}
TFrameDraw*  TNetChart::CriticalNotStartDraw()
{
    return &(FProject->CriticalNotStartDraw);
}
TFrameDraw*  TNetChart::CriticalStartedDraw()
{
    return &(FProject->CriticalStartedDraw);
}
TFrameDraw*  TNetChart::CriticalOveredDraw()
{
    return &(FProject->CriticalOveredDraw);
}
TFrameDraw*  TNetChart::NotStartDraw()
{
    return &(FProject->NotStartDraw);
}
TFrameDraw*  TNetChart::StartedDraw()
{
    return &(FProject->StartedDraw);
}
TFrameDraw*  TNetChart::OveredDraw()
{
    return &(FProject->OveredDraw);
}
TFrameDraw*  TNetChart::AbstractDraw()//摘要任务
{
    return &(FProject->AbstractDraw);
}
TFrameDraw*  TNetChart::MarkerDraw()//里程碑
{
    return &(FProject->MarkerDraw);
}
TFrameDraw*  TNetChart::WarningDraw()//有问题任务
{
    return &(FProject->WarningDraw);
}
TFrameDraw*  TNetChart::ForeignNotStartDraw()//外部未开工
{
    return &(FProject->ForeignNotStartDraw);
}
TFrameDraw*  TNetChart::CriticalForeignNotStartDraw()//外部未开工
{
    return &(FProject->CriticalForeignNotStartDraw);
}
TFrameDraw*  TNetChart::ForeignStartedDraw()//外部已开工
{
    return &(FProject->ForeignStartedDraw);
}
TFrameDraw*  TNetChart::CriticalForeignStartedDraw()//外部已开工
{
    return &(FProject->CriticalForeignStartedDraw);
}
TFrameDraw*  TNetChart::ForeignOveredDraw()//外部已完工
{
    return &(FProject->ForeignOveredDraw);
}
TFrameDraw*  TNetChart::CriticalForeignOveredDraw()//外部已完工
{
    return &(FProject->CriticalForeignOveredDraw);
}
TFrameDraw*  TNetChart::ForeignAbstractDraw()//外部摘要任务
{
    return &(FProject->ForeignAbstractDraw);
}
TFrameDraw*  TNetChart::ForeignMarkerDraw()//外部里程碑
{
    return &(FProject->ForeignMarkerDraw);
}
TFrameDraw*  TNetChart::ForeignProjectDraw()//外部工程
{
    return &(FProject->ForeignProjectDraw);
}

TNCLinkDraw* TNetChart::CriticalLinkDraw()
{
    return &(FProject->CriticalLinkDraw);
}
TNCLinkDraw* TNetChart::LinkDraw()
{
    return &(FProject->LinkDraw);
}
//---------------------------------------------------------------------------
void TNetChart::SetDefault()
{
	FTaskHeight = -1;
	FTaskWidth = 320;
	FColDistance = 80;
    FRowDistance = 40;
    //关键未开工
    FProject->CriticalNotStartDraw.LineColor = clRed;
    FProject->CriticalNotStartDraw.BkColor = 0x00FDE7E3;
    FProject->CriticalNotStartDraw.BorderType = TFrameDraw::btParallelogram1;
    FProject->CriticalNotStartDraw.BkPattern = 1;
    FProject->CriticalNotStartDraw.Abstract = 0;
    FProject->CriticalNotStartDraw.Sign = 0;
    //关键已开工
    FProject->CriticalStartedDraw.LineColor = clRed;
    FProject->CriticalStartedDraw.BkColor = 0x00FDE7E3;
    FProject->CriticalStartedDraw.BorderType = TFrameDraw::btRectangle;
    FProject->CriticalStartedDraw.Sign = 1;
    FProject->CriticalStartedDraw.BkPattern = 1;
    FProject->CriticalStartedDraw.Abstract = 0;
    //关键已完工
    FProject->CriticalOveredDraw.LineColor = clRed;
    FProject->CriticalOveredDraw.BkColor = 0x00FDE7E3;
    FProject->CriticalOveredDraw.BorderType = TFrameDraw::btDiamond;
    FProject->CriticalOveredDraw.Sign = 2;
    FProject->CriticalOveredDraw.BkPattern = 1;
    FProject->CriticalOveredDraw.Abstract = 0;
    //未开工
    FProject->NotStartDraw.LineColor = clBlue;
    FProject->NotStartDraw.BkColor = 0x00FDE7E3;
    FProject->NotStartDraw.BorderType = TFrameDraw::btParallelogram1;
    FProject->NotStartDraw.BkPattern = 1;
    FProject->NotStartDraw.Abstract = 0;
    FProject->NotStartDraw.Sign = 0;
    //已开工
    FProject->StartedDraw.LineColor = clBlue;
    FProject->StartedDraw.BkColor = 0x00FDE7E3;
    FProject->StartedDraw.BorderType = TFrameDraw::btRectangle;
    FProject->StartedDraw.Sign = 1;
    FProject->StartedDraw.BkPattern = 1;
    FProject->StartedDraw.Abstract = 0;
    //已完工
    FProject->OveredDraw.LineColor = clBlue;
    FProject->OveredDraw.BkColor = 0x00FDE7E3;
    FProject->OveredDraw.BorderType = TFrameDraw::btDiamond;
    FProject->OveredDraw.Sign = 2;
    FProject->OveredDraw.BkPattern = 1;
    FProject->OveredDraw.Abstract = 0;
    //摘要任务
    FProject->AbstractDraw.LineColor = clBlue;
    FProject->AbstractDraw.BkColor = 0x00FDE7E3;
    FProject->AbstractDraw.BorderType = TFrameDraw::btDiamond;
    FProject->AbstractDraw.Sign = 0;
    FProject->AbstractDraw.BkPattern = 1;
    FProject->AbstractDraw.Abstract = 0;
    //里程碑
    FProject->MarkerDraw.LineColor = clBlue;
    FProject->MarkerDraw.BkColor = 0x00FDE7E3;
    FProject->MarkerDraw.BorderType = TFrameDraw::btDiamond;
    FProject->MarkerDraw.Sign = 0;
    FProject->MarkerDraw.BkPattern = 1;
    FProject->MarkerDraw.Abstract = 0;
    //有问题任务
    FProject->WarningDraw.LineColor = clBlue;
    FProject->WarningDraw.BkColor = 0x00FDE7E3;
    FProject->WarningDraw.BorderType = TFrameDraw::btDiamond;
    FProject->WarningDraw.Sign = 0;
    FProject->WarningDraw.BkPattern = 1;
    FProject->WarningDraw.Abstract = 0;
    //外部未开工
    FProject->ForeignNotStartDraw.LineColor = clBlue;
    FProject->ForeignNotStartDraw.BkColor = 0x00FDE7E3;
    FProject->ForeignNotStartDraw.BorderType = TFrameDraw::btDiamond;
    FProject->ForeignNotStartDraw.Sign = 0;
    FProject->ForeignNotStartDraw.BkPattern = 1;
    FProject->ForeignNotStartDraw.Abstract = 0;
    //外部未开工
    FProject->CriticalForeignNotStartDraw.LineColor = clBlue;
    FProject->CriticalForeignNotStartDraw.BkColor = 0x00FDE7E3;
    FProject->CriticalForeignNotStartDraw.BorderType = TFrameDraw::btDiamond;
    FProject->CriticalForeignNotStartDraw.Sign = 0;
    FProject->CriticalForeignNotStartDraw.BkPattern = 1;
    FProject->CriticalForeignNotStartDraw.Abstract = 0;
    //外部已开工
    FProject->ForeignStartedDraw.LineColor = clBlue;
    FProject->ForeignStartedDraw.BkColor = 0x00FDE7E3;
    FProject->ForeignStartedDraw.BorderType = TFrameDraw::btDiamond;
    FProject->ForeignStartedDraw.Sign = 1;
    FProject->ForeignStartedDraw.BkPattern = 1;
    FProject->ForeignStartedDraw.Abstract = 0;
    //外部已开工
    FProject->CriticalForeignStartedDraw.LineColor = clBlue;
    FProject->CriticalForeignStartedDraw.BkColor = 0x00FDE7E3;
    FProject->CriticalForeignStartedDraw.BorderType = TFrameDraw::btDiamond;
    FProject->CriticalForeignStartedDraw.Sign = 1;
    FProject->CriticalForeignStartedDraw.BkPattern = 1;
    FProject->CriticalForeignStartedDraw.Abstract = 0;
    //外部已完工
    FProject->ForeignOveredDraw.LineColor = clBlue;
    FProject->ForeignOveredDraw.BkColor = 0x00FDE7E3;
    FProject->ForeignOveredDraw.BorderType = TFrameDraw::btDiamond;
    FProject->ForeignOveredDraw.Sign = 2;
    FProject->ForeignOveredDraw.BkPattern = 1;
    FProject->ForeignOveredDraw.Abstract = 0;
    //外部已完工
    FProject->CriticalForeignOveredDraw.LineColor = clBlue;
    FProject->CriticalForeignOveredDraw.BkColor = 0x00FDE7E3;
    FProject->CriticalForeignOveredDraw.BorderType = TFrameDraw::btDiamond;
    FProject->CriticalForeignOveredDraw.Sign = 2;
    FProject->CriticalForeignOveredDraw.BkPattern = 1;
    FProject->CriticalForeignOveredDraw.Abstract = 0;
    //外部摘要任务
    FProject->ForeignAbstractDraw.LineColor = clBlue;
    FProject->ForeignAbstractDraw.BkColor = 0x00FDE7E3;
    FProject->ForeignAbstractDraw.BorderType = TFrameDraw::btDiamond;
    FProject->ForeignAbstractDraw.Sign = 0;
    FProject->ForeignAbstractDraw.BkPattern = 1;
    FProject->ForeignAbstractDraw.Abstract = 0;
    //外部里程碑
	FProject->ForeignMarkerDraw.LineColor = clBlue;
    FProject->ForeignMarkerDraw.BkColor = 0x00FDE7E3;
    FProject->ForeignMarkerDraw.BorderType = TFrameDraw::btDiamond;
    FProject->ForeignMarkerDraw.Sign = 0;
    FProject->ForeignMarkerDraw.BkPattern = 1;
    FProject->ForeignMarkerDraw.Abstract = 0;
    //外部工程
    FProject->ForeignProjectDraw.LineColor = clBlue;
    FProject->ForeignProjectDraw.BkColor = 0x00FDE7E3;
	FProject->ForeignProjectDraw.BorderType = TFrameDraw::btDiamond;
    FProject->ForeignProjectDraw.Sign = 0;
    FProject->ForeignProjectDraw.BkPattern = 1;
    FProject->ForeignProjectDraw.Abstract = 0;

    FProject->CriticalLinkDraw.Color = clRed;
    FProject->CriticalLinkDraw.PenWidth=2;
    FProject->LinkDraw.Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TNetChart::AdjustOnFrameMove(int X, int Y)
{
  X = X > FHORZ.nMin ? X : FHORZ.nMin;
  X = X < FHORZ.nMax ? X : FHORZ.nMax;
  Y = Y > FVERT.nMin ? Y : FVERT.nMin;
  Y = Y < FVERT.nMax ? Y : FVERT.nMax;

  ScrollWindow(Handle, X - FHORZ.nPos , Y - FVERT.nPos , NULL, NULL);
  SetScrollPos(Handle, SB_HORZ, X, true);
  SetScrollPos(Handle, SB_VERT, Y, true);
  FHORZ.nPos = X;
  FVERT.nPos = Y;
  this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TNetChart::ShowNavigation()
{
  if(!NaviImage || !NaviImage->Showing) return;

  NaviImage->OnFrameMove = NULL;
  NaviImage->ShowNavigationPicture(this);
  NaviImage->SetFrameRect(this->ClientRect,FHORZ.nPos,FVERT.nPos);
  NaviImage->OnFrameMove = AdjustOnFrameMove;
}
//---------------------------------------------------------------------------
void __fastcall TNetChart::FindTaskByName(const String TaskName)
{
  TPoint *pt = FProject->FindTaskByName(TaskName);
  if(pt!=NULL)
  {
    AdjustOnFrameMove(pt->x-Width/2,pt->y-Height/2);
    if(NaviImage && NaviImage->Showing)
      NaviImage->SetFrameRect(FHORZ.nPos,FVERT.nPos);
    delete pt;
  }
}
//---------------------------------------------------------------------------

