//---------------------------------------------------------------------------
//    File:               DblCode.h, DblCode.cpp
//    Function:           双代号网络图
//    Author:             sunny zhan
//    Last Modify:        2009-05-22
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#include "vclComFunc.h"
#include "ZChartPrint.h"
#pragma hdrstop

#include "DoubleCode.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TDoubleCode *)
{
  new TDoubleCode(NULL);
}
//---------------------------------------------------------------------------
namespace Doublecode
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TDoubleCode)};
	 RegisterComponents("ZChart", classes, 0);
  }
}
//---------------------------------------------------------------------------
class TDCTaskDrawInfo
{
public:
  int X1;
  int X2;
  int X3;
  int X4;
  int DCYPointY;
  int xLeft;
  int xRight;
  bool DrawArrow;
};
//---------------------------------------------------------------------------
class TDCTaskLinkInfo
{
public:
  bool DrawArrow;
  bool DrawSolid;
  POINT pStart;
  POINT pEnd;
  POINT pTextStart;
  POINT pTextEnd;
  TList *LinkLineList;
  TList *LinkBridgeList;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  TDCProject
//---------------------------------------------------------------------------
class TDCProject{
    friend TDoubleCode;
private:
    TDCPrjDataChangeLink* FDCPrjDataChangeLink;
    TDoubleCode*           FChart;
    TProject*           FProject;
    bool                  FMustDelete;
    //DragTask
    bool                  FDraging;
    int                   FDragStartY;
    int                   FOldInvertY;
    TTask*              FDragTask;
    int EventDiameter;//事件的直径   ////////////////
    int MaxEventNo ;//最大的代号，用于设置代号时使用  ////////////////
    int TaskBridgeRadii ;//桥线的半径//////////
    TList *EventPointList;//记录显示的代号的坐标 ////////////////
    TList *TaskPointList;//记录任务的显示坐标   ////////////////
    TList *TaskLinkList;//记录虚线的显示坐标及信息//////////////////////
    TList *TaskLinkLineList;//在画任务线时记录一个任务的线，用于DrawTaskLink
    TList *TaskLinkBridgeList;//在画任务线时记录一个任务的桥坐标，用于DrawTaskLink
    //____导航图________
    bool DrawingNavigation; //true在画导航图
//    TCalendarDraw::TGTCalendarType NavigationType;     //日期类型
//    int NavigationRowHeight;//每项高度
//    SIZE NavigationImageSize;//图的大小
    //____导航图________

    void __fastcall SetProject(TProject*);
    void __fastcall InitData();

    TTask* __fastcall TaskFromPoint(int X, int Y);
    int PointYWithRowY(int ARowY);
    int RowYWithPointY(int APointY);
    void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
    void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
public:
    __fastcall TDCProject(TDoubleCode* AChart);
    __fastcall ~TDCProject();
    void InitTaskLink();
    void Draw(HDC dc, RECT dr);
    void DrawCalendar(HDC dc, int ALeft, int AWidth);
    void IniCalendar();
    void AutoAlign();
    void AdjuestTaskLinkLine(POINT *pLine,int LineCount);////////
    TPoint* FindTaskByName(const String TaskName);/////////
    bool PointInEventPoint(POINT pt);///////////////
    bool LineCrossEventPoint(POINT pStart,POINT pEnd);///////////////
    bool LineIntersectTaskLine(POINT p1,POINT p2, POINT & pBridge);////////
    bool LineOverTaskLine(POINT p1,POINT p2);///////////////
    int HaveFSFrontTask(TTask* ATask);///////////
    void SetTaskEventNo(TTask* ATask);//////////
    void SetATaskStartEventNo(TTask* ATask,int iFrontCount);///////
    void SetATaskEndEventNo(TTask* ATask,int iLateCount);////////
    TTask* GetIlkDayLateTask(TTask* CurTask,bool bStart);////////
    TTask* GetIlkDayTask(TTask* CurTask,bool bStart);////////////
    TTask* GetMaxLateTask(TTask* CurTask,int iMaxValue);////////
    TTask* GetEqualDCYTask(TTask* CurTask);/////////////////////
    bool AllLateHaveIlkFront(TTask* ATask,int iLateCount);/////////
    void LateHaveIlkFrontNo(TTask* ATask,TList* IlkTasks,TList* DiffTasks);
    int HaveIlkFrontNo(TTask* ATask);///////////////
    void SortEventNo();////////////
    bool TaskIsOver(TTask* sdTask1,TTask* sdTask2);////////////////
    bool TaskIsOver(TTask* sdTask);///////////////
    int GetMaxLateTaskDCY(TTask* CurTask);///////////////
    int GetMaxDCY();//////////////
    bool HaveOtherParentTask(TTask * CurTask,TTask *ATask);////////////
    void DrawTaskText(HDC dc, RECT dr,int LimitHeight,TTask &ATask);////////
    void DrawLinkText(HDC dc, int days,TFrontType ftType,POINT p1,POINT p2);//////
    void InitTaskDCY();///////////////
    void GetTaskDate(TTask* ATask, int &DateLeft, int &DateRight);///////////////
    void MoveBigDCY(TTask* AStart, int Inc);///////////////
    //bool DownWillOverlap(TTask* AStart, int Inc);
    TCalendarDraw Calendar;
    int CalendarHeight;
    int RowHeight;
    TEventDraw    EventDraw;
    TTaskLine     CriticalDraw;
    TTaskLine     TaskDraw;
    TVirtualLine  CriticalVirtualDraw;
    TVirtualLine  VirtualDraw;
    TTaskShowString TopShowString;
    TTaskShowString BottomShowString;
    int oldCalendarType;
    String oldProjectTaskID;

    __property TProject* Project = {read=FProject, write=SetProject};
    __property TDoubleCode* Chart = {read=FChart};
};
//---------------------------------------------------------------------------
// TDCPrjDataChangeLink
//---------------------------------------------------------------------------
class TDCPrjDataChangeLink : public TPrjDataChangeLink
{
public:
    TDCProject* LDCProject;
    TDCPrjDataChangeLink(TDCProject*AProject)
	   :TPrjDataChangeLink(AProject->Project) { LDCProject = AProject; }

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
    virtual void BeforeTaskDelete(TPrjObject*ATask)
    {
    }
    virtual void AfterTaskDelete()
    {
    }
    virtual void AfterTaskDelete(TPrjObject*ATask)
    {
    }
    virtual void AfterTaskAdd(TPrjObject*ATask)
    {
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
//        LDCProject->Project = LDCProject->Project;
    }
	virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect)
    {
        //FDCProject->Chart->Invalidate();
    }
};
//---------------------------------------------------------------------------
// TDCProject
//---------------------------------------------------------------------------
__fastcall TDCProject::TDCProject(TDoubleCode* AChart)
{
    FChart = AChart;
//    (&EventDraw)->EventFont->Assign(FChart->Font);
    CalendarHeight = 32;
    RowHeight = 48;
//    NavigationRowHeight = RowHeight;///////////////
//    NavigationImageSize.cx = 1;///////////////
//    NavigationImageSize.cy = 1;///////////////
    TaskBridgeRadii = 6;/////////////////
    FProject = new TProject();
    FMustDelete = true;
    FDraging = false;
    FDCPrjDataChangeLink = new TDCPrjDataChangeLink(this);

    EventPointList = NULL;
    TaskPointList  = NULL;
    TaskLinkList = NULL;
    TaskLinkBridgeList = NULL;
    TaskLinkLineList = NULL;
    oldCalendarType = -1;
    oldProjectTaskID = "";
}
//---------------------------------------------------------------------------
__fastcall TDCProject::~TDCProject()
{
    if(FMustDelete && FProject)
        delete FProject;
    if(FDCPrjDataChangeLink)
        delete FDCPrjDataChangeLink;

    if(EventPointList)
      delete EventPointList;
    if(TaskPointList)
      delete TaskPointList;
    if(TaskLinkList)
      delete TaskLinkList;
//    if(TaskLinkBridgeList)
//      delete TaskLinkBridgeList;
//    if(TaskLinkLineList)
//      delete TaskLinkLineList;
}
//---------------------------------------------------------------------------
void __fastcall TDCProject::SetProject(TProject*AProject)
{
    if(FMustDelete)
    {
        delete FProject;
        FMustDelete = false;
    }

    if(FProject != AProject)
    {
        FProject = AProject;
        FDCPrjDataChangeLink->SetProject(FProject);
    }
    if(!AProject)
    {
      if(EventPointList)
        delete EventPointList;
      if(TaskPointList)
        delete TaskPointList;
      if(TaskLinkList)
        delete TaskLinkList;
      EventPointList = NULL;
      TaskPointList = NULL;
      TaskLinkList = NULL;
      return;
    }

    if(oldProjectTaskID==AProject->TaskID && oldCalendarType==(int)Calendar.Type)
    {
      if((FProject->Tasks.Count()>0) && TaskPointList && TaskLinkList)
        if((TaskPointList->Count==FProject->Tasks.Count())
          && TaskLinkList->Count==(FProject->TaskLinks.Count()))
        {
          FChart->Invalidate();
          return;
        }
    }
    if(EventPointList)
      delete EventPointList;
    if(TaskPointList)
      delete TaskPointList;
    if(TaskLinkList)
      delete TaskLinkList;
    EventPointList = NULL;
    TaskPointList = NULL;
    TaskLinkList = NULL;

    oldCalendarType = Calendar.Type;
    if(oldProjectTaskID!=AProject->TaskID)
    {
      if(FProject->Tasks.Count()>0)
      {
        int i ;
        for(i = 0; i < FProject->Tasks.Count(); i++)
        {
          FProject->Tasks[i]->SumFFDate();
        }

        Calendar.Type = TCalendarDraw::gctDay;
        IniCalendar();
        InitTaskDCY();
        Calendar.Type = (TCalendarDraw::TGTCalendarType)oldCalendarType;
        IniCalendar();

        SortEventNo();
        InitData();

        Calendar.Init();
        FChart->AdjustScrollBar();
        FChart->Invalidate();
      }
    }
    else
    {
      AutoAlign();

      if(FProject->Tasks.Count()>0)
        InitData();
    }
    oldProjectTaskID = AProject->TaskID;
}
//---------------------------------------------------------------------------
//=true:是一条斜线
bool IsBiasLine(const POINT& pStart, const POINT& pEnd)
{
  return (abs(pStart.y - pEnd.y)>2) && (abs(pStart.x - pEnd.x)>2);
}
//---------------------------------------------------------------------------
void __fastcall TDCProject::InitData()
{
    int TasksCount = FProject->Tasks.Count();
    int i;
    int R = EventDraw.Radial;

    //计算代号位置
    TTask *tmTask;
    EventPointList = new TList();
    TEventData *AEvent ;
    TDateTime date;
    int TaskYPos ;
    for(i=0; i<TasksCount; i++)
    {
        tmTask = FProject->Tasks[i];
        date = tmTask->FF_StartDate;
        TaskYPos = PointYWithRowY(tmTask->DCY);
        if(!tmTask->StartInherit || tmTask->CostDays==0)
        {
            AEvent = new TEventData();
            AEvent->x = Calendar.GetDayLeft(date);
            AEvent->y = TaskYPos;
            AEvent->EventNo = tmTask->DCStartEvent;
            EventPointList->Add(AEvent);
        }
        //后节点代号
        if(tmTask->CostDays > 0)
        {
            date = tmTask->FF_EndDate;
            if(!FProject->Tasks[i]->EndInherit)
            {
                AEvent = new TEventData();
                AEvent->x = Calendar.GetDayRight(date);
                AEvent->y = TaskYPos;
                AEvent->EventNo = tmTask->DCEndEvent;
                EventPointList->Add(AEvent);
            }
        }
    }

    //任务
    TaskPointList = new TList();
    TDCTaskDrawInfo *tdInfo ;
    POINT TaskEndPoint;
    //int DCYPointY;
    int X1, X2, X3, X4;
    for(i = 0; i < TasksCount; i++)
    {
        TTask& ATask = *(FProject->Tasks[i]);
        tdInfo = new TDCTaskDrawInfo();
        if(ATask.CostDays <= 0)
        {
            if (ATask.PlanType==ptALAP)
              tdInfo->X1  = Calendar.GetDayLeft(ATask.ALAP_EndDate)-R ;
            else
              tdInfo->X1  = Calendar.GetDayLeft(ATask.ASAP_StartDate)-R ;

            tdInfo->xLeft = tdInfo->X1;
            if(ATask.FrontTaskCount==0)
              tdInfo->xLeft = tdInfo->X1 - EventDiameter ;
            else if(ATask.LateTaskCount==0)
              tdInfo->xLeft = tdInfo->X1 + EventDiameter ;

            tdInfo->xRight = tdInfo->xLeft+EventDiameter;
            tdInfo->DCYPointY = PointYWithRowY(ATask.DCY);
            TaskPointList->Add(tdInfo);
            continue;
        }
        switch(ATask.PlanType)
        {
            case ptASAP:
            case ptMSO:
            case ptAFO:
            case ptASO:
            case ptBSO:
            case ptBFO:
            case ptMFO:
            {
                X1 = Calendar.GetDayLeft(ATask.ASAP_StartDate);
                X2 = Calendar.GetDayRight(ATask.ASAP_EndDate);
                X3 = X2;
                X4 = X2;
                if(ATask.ASAP_EndDate != ATask.FF_EndDate)
                  X4 = Calendar.GetDayRight(ATask.FF_EndDate);
                break;
            }
            case ptALAP:
            {
                X2 = Calendar.GetDayRight(ATask.ALAP_EndDate);
                X1 = Calendar.GetDayLeft(ATask.ALAP_StartDate);
                X3 = X1;
                X4 = X1;
                if(ATask.ALAP_StartDate != ATask.FF_StartDate)
                  X3 = Calendar.GetDayLeft(ATask.FF_StartDate);
                break;
            }
            default:
                throw Exception("不支持此计划方法");
        }
        tdInfo->X1 = X1;
        tdInfo->X2 = X2;
        tdInfo->X3 = X3;
        tdInfo->X4 = X4;
        tdInfo->DCYPointY = PointYWithRowY(ATask.DCY);
        tdInfo->xLeft = X1 < X3 ? X1 : X3;
        tdInfo->xRight = X2 > X4 ? X2 : X4;
        TaskEndPoint.x = tdInfo->xRight;
        TaskEndPoint.y = tdInfo->DCYPointY;
        tdInfo->DrawArrow = PointInEventPoint(TaskEndPoint);
        TaskPointList->Add(tdInfo);
    }//画任务

    InitTaskLink();
}
//---------------------------------------------------------------------------
//p1,p2组成的线是否与任务线相交.（不判断重叠的情况）
bool TDCProject::LineIntersectTaskLine(POINT p1,POINT p2, POINT & pBridge)
{
  if(p1.x!=p2.x) return false; //只有竖线才会相交。横线是相重合

  TDCTaskDrawInfo *t;
  int ps = p1.y;
  int pe = p2.y;

  if(ps>pe)
  {
    ps = p2.y;
    pe = p1.y;
  }
  for(int i=TaskPointList->Count-1; i>=0; i--)
  {
    t = (TDCTaskDrawInfo *) TaskPointList->Items[i];
    if(t->DCYPointY > ps && t->DCYPointY < pe  &&  p1.x > t->xLeft && p1.x < t->xRight)
    {
      pBridge.x = p1.x;
      pBridge.y = t->DCYPointY;
      return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------------
//p1,p2组成的线是否与任务线重叠.（不判断相交的情况）
bool TDCProject::LineOverTaskLine(POINT p1,POINT p2)
{
  if(p1.y!=p2.y) return false; //任务线肯定是横线

  TDCTaskDrawInfo *t;
  int ps = p1.x;
  int pe = p2.x;

  if(ps>pe)
  {
    ps = p2.x;
    pe = p1.x;
  }
  for(int i=TaskPointList->Count-1; i>=0; i--)
  {
    t = (TDCTaskDrawInfo *) TaskPointList->Items[i];
    if(t->DCYPointY==p1.y)//任务线肯定是横线且记录时都是x1<x2
    {
//      if(!(ps >= t->x2 || pe <= t->x1))
      if(!(ps > t->xRight || pe < t->xLeft))
        return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------------
//线是否与事件有相交（只处理横竖）
bool TDCProject::LineCrossEventPoint(POINT pStart,POINT pEnd)
{
  TEventData *t;
  int iStart, iEnd , iLineS, iLineE;
  if(pStart.y==pEnd.y)//横
  {
    for(int i=EventPointList->Count-1; i>=0; i--)
    {
      t = (TEventData *) EventPointList->Items[i];
      iStart = t->y - EventDraw.Radial;
      iEnd   = t->y + EventDraw.Radial;
      if(pStart.y>=iStart && pStart.y<=iEnd)
      {
        iStart = t->x - EventDraw.Radial;
        iEnd   = t->x + EventDraw.Radial;
        if(pStart.x<pEnd.x)
        {
          iLineS = pStart.x;
          iLineE = pEnd.x;
        }
        else
        {
          iLineS = pEnd.x;
          iLineE = pStart.x;
        }
        if(iLineS<=iEnd && iLineE>=iStart)
          return true;
      }
    }//for
  }
  else
  {
    for(int i=EventPointList->Count-1; i>=0; i--)
    {
      t = (TEventData *) EventPointList->Items[i];
      iStart = t->x - EventDraw.Radial;
      iEnd   = t->x + EventDraw.Radial;
      if(pStart.x>=iStart && pStart.x<=iEnd)
      {
        iStart = t->y - EventDraw.Radial;
        iEnd   = t->y + EventDraw.Radial;
        if(pStart.y<pEnd.y)
        {
          iLineS = pStart.y;
          iLineE = pEnd.y;
        }
        else
        {
          iLineS = pEnd.y;
          iLineE = pStart.y;
        }
        if(iLineS<=iEnd && iLineE>=iStart)
          return true;
      }
    }//for
  }
  return false;
}
//---------------------------------------------------------------------------
//坐标pt是否和一个事件重叠
bool TDCProject::PointInEventPoint(POINT pt)
{
  TEventData *t;
  for(int i=EventPointList->Count-1; i>=0; i--)
  {
    t = (TEventData *) EventPointList->Items[i];
    if(t->y == pt.y  &&  abs(t->x-pt.x) < EventDraw.Radial)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------
TPoint* TDCProject::FindTaskByName(const String TaskName)
{
  TPoint *pt = NULL;
  for(int i = FProject->Tasks.Count()-1; i >=0; i--)
  {
    if(TaskName==FProject->Tasks[i]->Name)
    {
      TDCTaskDrawInfo *tdInfo = (TDCTaskDrawInfo *)TaskPointList->Items[i];
      pt = new TPoint();
      pt->x = (tdInfo->xLeft+tdInfo->xRight)/2;
      pt->y = tdInfo->DCYPointY;
      FProject->Selected = FProject->Tasks[i];
    }
  }
  return pt;
}
//---------------------------------------------------------------------------
//调整线，加入桥线
//LineCount表示pLine的元素个数，必须大于1
void TDCProject::AdjuestTaskLinkLine(POINT *pLine,int LineCount)
{
  TaskLinkLineList->Clear();
  TaskLinkBridgeList->Clear();
  int BridgeStart = 0,BridgeEnd = -1,BridgeCount = 0;
  POINT p1,p2,pBridge;
  int ps ,pe , i,k,n,v;
  TDCTaskDrawInfo *t;

  for(i=0 ; i<LineCount-1; i++)
  {
    p1 = pLine[i];
    p2 = pLine[i+1];

    if(p1.x!=p2.x)
    {
      TaskLinkLineList->Add(new TLinePoint(p1,p2));
      continue; //只有竖线才会相交。横线是相重合
    }

    ps = p1.y;
    pe = p2.y;
    if(ps>pe)
    {
      ps = p2.y;
      pe = p1.y;
    }
    //取所有相交点
    BridgeStart = BridgeEnd+1;
    for(k=TaskPointList->Count-1; k>=0; k--)
    {
      t = (TDCTaskDrawInfo *) TaskPointList->Items[k];
      if(t->DCYPointY > ps && t->DCYPointY < pe  &&  p1.x > t->xLeft && p1.x < t->xRight)
      {
        TaskLinkBridgeList->Add(new TPoint(p1.x,t->DCYPointY));
      }
    }
    BridgeEnd = TaskLinkBridgeList->Count-1;
    BridgeCount = BridgeEnd - BridgeStart + 1;
    if(BridgeCount <= 0)
      TaskLinkLineList->Add(new TLinePoint(p1,p2));
    else
    {
      StackArray<int,10> Bridges(BridgeCount);
      for(k=BridgeStart; k<=BridgeEnd; k++)
      {
        Bridges[k-BridgeStart] = ((TPoint *)TaskLinkBridgeList->Items[k])->y;
      }
      bool change = false;
      for(k=0; k<BridgeCount; k++)
      {//从小到大排序
        change = false;
        for(n=1; n<BridgeCount; n++)
          if(Bridges[n-1]>Bridges[n])
          {
            v = Bridges[n-1];
            Bridges[n-1] = Bridges[n];
            Bridges[n] = v;
            change = true;
          }
        if(!change) break;
      }
      if(p1.y<p2.y)
      {
        for(k=0; k<BridgeCount; k++)
        {
          v = Bridges[k];
          TaskLinkLineList->Add(new TLinePoint(p1.x,p1.y,p1.x,v-TaskBridgeRadii));
          p1.y = v + TaskBridgeRadii;
        }
        TaskLinkLineList->Add(new TLinePoint(p1,p2));
      }
      else
      {
        for(k=BridgeCount-1; k>=0; k--)
        {
          v = Bridges[k];
          TaskLinkLineList->Add(new TLinePoint(p1.x,p1.y,p1.x,v+TaskBridgeRadii));
          p1.y = v - TaskBridgeRadii;
        }
        TaskLinkLineList->Add(new TLinePoint(p1,p2));
      }
    }//if else
  }//for i
}
//---------------------------------------------------------------------------
//画关系线
void TDCProject::InitTaskLink()
{
  if(!FProject) return;

  int R = EventDraw.Radial;
  TaskLinkList = new TList();

  POINT pStart, pEnd;
  POINT pLine[4];
  int LineCount;
  bool DrawArrow = true;
  bool DrawSolid = false;
  bool StartInEvent,EndInEvent;
  int AHeight = RowHeight;//PointYWithRowY(1) - PointYWithRowY(0);
  int TaskLinksCount = FProject->TaskLinks.Count();
  for(int i = 0; i < TaskLinksCount; i++)
  {
      DrawArrow = true;
      DrawSolid = false;
      TTaskLink& ALink = *(FProject->TaskLinks[i]);
      if(ALink.IsForeign())
      {
        TaskLinkList->Add(NULL);
        continue;
      }
      switch(ALink.Type)
      {
          case ftNone:
              break;
          case ftFinishStart:
              if(!ALink.Front->MileStone)
                pStart.x = Calendar.GetDayRight(ALink.Front->FF_EndDate);
              else
                pStart.x = Calendar.GetDayLeft(ALink.Front->FF_StartDate);
              pStart.y = PointYWithRowY(ALink.Front->DCY);

              pEnd.x = Calendar.GetDayLeft(ALink.Task->FF_StartDate);
              pEnd.y = PointYWithRowY(ALink.Task->DCY);
              break;
          case ftStartStart:
              pStart.x = Calendar.GetDayLeft(ALink.Front->FF_StartDate);
              pStart.y = PointYWithRowY(ALink.Front->DCY);
              pEnd.x = Calendar.GetDayLeft(ALink.Task->FF_StartDate);
              pEnd.y = PointYWithRowY(ALink.Task->DCY);
              break;
          case ftFinishFinish:
              if(!ALink.Front->MileStone)
                pStart.x = Calendar.GetDayRight(ALink.Front->FF_EndDate);
              else
                pStart.x = Calendar.GetDayLeft(ALink.Front->FF_StartDate);
              pStart.y = PointYWithRowY(ALink.Front->DCY);
              if(!ALink.Task->MileStone)
                pEnd.x = Calendar.GetDayRight(ALink.Task->FF_EndDate);
              else
                pEnd.x = Calendar.GetDayLeft(ALink.Task->FF_StartDate);
              pEnd.y = PointYWithRowY(ALink.Task->DCY);
              break;
          case ftStartFinish:
              pStart.x = Calendar.GetDayLeft(ALink.Front->FF_StartDate);
              pStart.y = PointYWithRowY(ALink.Front->DCY);
              if(!ALink.Task->MileStone)
                pEnd.x = Calendar.GetDayRight(ALink.Task->FF_EndDate);
              else
                pEnd.x = Calendar.GetDayLeft(ALink.Task->FF_StartDate);
              pEnd.y = PointYWithRowY(ALink.Task->DCY);
              break;
          default:
              throw Exception("不支持此类型");
      }

//      if(pStart.y==pEnd.y && pStart.x==pEnd.x) continue;
      if(abs(pStart.y-pEnd.y)<=R && abs(pStart.x-pEnd.x)<=R)
      {
        TaskLinkList->Add(NULL);
        continue;
      }

      StartInEvent = PointInEventPoint(pStart);
      EndInEvent = PointInEventPoint(pEnd);
      DrawArrow = EndInEvent;
      DrawSolid = !(StartInEvent && EndInEvent);

      POINT pTextStart,pTextEnd;
      POINT ptm1,ptm2;
      //直线
      LineCount = 2;
      pLine[0] = pStart;
      pLine[1] = pEnd;
      pTextStart = pLine[0];
      pTextEnd = pLine[1];

      //处理线与代码号的重叠情况
      if(!IsBiasLine(pStart,pEnd))
      {
        if(pStart.y==pEnd.y)//横线
        {
          ptm1=pStart;
          ptm2=pEnd;
          if(pStart.x<pEnd.x)
          {
            ptm1.x = ptm1.x+1;
            ptm2.x = ptm2.x-1;
          }
          else
          {
            ptm1.x = ptm1.x-1;
            ptm2.x = ptm2.x+1;
          }
          if(LineOverTaskLine(ptm1,ptm2))
          {
            LineCount = 4;
            pLine[0] = pStart;
            pLine[1] = pStart;
            pLine[2] = pEnd;
            pLine[3] = pEnd;
            pLine[1].y += 3*EventDraw.Radial;
            pLine[2].y = pLine[1].y;
            pTextStart = pLine[1];
            pTextEnd = pLine[2];
//            if(pStart.x<pEnd.x)
//            {
//              pTextStart.x = pTextEnd.x - 3*EventDraw.Radial;
//              if(pTextStart.x<pStart.x) pTextStart.x=pStart.x;
//            }
//            else
//            {
//              pTextStart.x = pTextEnd.x + 3*EventDraw.Radial;
//              if(pTextStart.x>pStart.x) pTextStart.x=pStart.x;
//            }
          }
        }//横线
        else//竖线
        {
          ptm1=pStart;
          ptm2=pEnd;
          if(pStart.y<pEnd.y)
          {
            ptm1.y = ptm1.y+EventDraw.Radial+1;
            ptm2.y = ptm2.y-EventDraw.Radial-1;
          }
          else
          {
            ptm1.y = ptm1.y-EventDraw.Radial-1;
            ptm2.y = ptm2.y+EventDraw.Radial+1;
          }
          if(LineCrossEventPoint(ptm1,ptm2))
          {
            LineCount = 4;
            pLine[0] = pStart;
            bool bLeft = ALink.Type==ftStartStart;
            if(bLeft)
              pLine[1].x = pStart.x-EventDiameter+3;
            else
              pLine[1].x = pStart.x+EventDiameter-3;
            if(pStart.y<pEnd.y)
              pLine[1].y = pStart.y+EventDiameter-3;
            else
              pLine[1].y = pStart.y-EventDiameter+3;

            if(bLeft)
              pLine[2].x = pStart.x-EventDiameter+3;
            else
              pLine[2].x = pStart.x+EventDiameter-3;
            if(pStart.y<pEnd.y)
              pLine[2].y = pEnd.y-EventDiameter+3;
            else
              pLine[2].y = pEnd.y+EventDiameter-3;

            pLine[3] = pEnd;

            pTextStart = pLine[1];
            pTextEnd = pLine[2];
          }//LineCrossEventPoint
          else if(StartInEvent && EndInEvent)
          {
            if(pStart.y<pEnd.y)
            {
              pStart.x += 2;
              pEnd.x += 2;
            }
            else
            {
              pStart.x -= 2;
              pEnd.x -= 2;
            }
            pLine[0] = pStart;
            pLine[1] = pEnd;
            pTextStart = pLine[0];
            pTextEnd = pLine[1];
          }
        }//else //竖线
      }
      else
      {//把斜线转换成曲线
          Byte LineType = 0;
          POINT tmPt;
          LineCount = 3;
          POINT tmStart,tmEnd;
          tmStart = pStart;
          tmEnd = pEnd;
          if(LineType==0)//竖横型
          {
            if(StartInEvent && EndInEvent)
            {
              if(pStart.y<pEnd.y)
              {
                pStart.x = tmStart.x+2;
              }
              else
              {
                pStart.x = tmStart.x-2;
              }
            }
            pLine[0] = pStart;
            pLine[1].x = pStart.x;
            pLine[1].y = pEnd.y;
            pLine[2] = pEnd;
            ptm1 = pLine[1];
            ptm2 = pLine[2];
            ptm2.x = pLine[1].x<pLine[2].x ? ptm2.x-1 : ptm2.x+1;
            //if(!LineOverTaskLine(pLine[1],pLine[2]) && !PointInEventPoint(pLine[1]))
            if(!LineOverTaskLine(ptm1,ptm2) && !PointInEventPoint(ptm1))
              LineType = 2;
          }
          if(LineType==0)//横竖型
          {
            if(StartInEvent && EndInEvent)
            {
              if(pStart.y<pEnd.y)
              {
                pEnd.x = tmEnd.x+2;
              }
              else
              {
                pEnd.x = tmEnd.x-2;
              }
            }
            pLine[0] = pStart;
            pLine[1].x = pEnd.x;
            pLine[1].y = pStart.y;
            pLine[2] = pEnd;
            ptm1 = pLine[0];
            ptm2 = pLine[1];
            ptm1.x = pStart.x<pEnd.x ? ptm1.x+1 : ptm1.x-1;
//            if(!LineOverTaskLine(pLine[0],pLine[1]) && !PointInEventPoint(pLine[1]))
            if(!LineOverTaskLine(ptm1,ptm2) && !PointInEventPoint(ptm2))
              LineType = 1;
          }

          if(LineType==0)//折型初始化　
          {
            LineCount = 4;
            pLine[0] = pStart;
            pLine[3] = pEnd;
          }
          if(LineType==0)//横竖横
          {
            pLine[1].y = pStart.y;
            pLine[2].y = pEnd.y;
            pLine[1].x = (pStart.x+pEnd.x)/2;
            pLine[2].x = pLine[1].x;
            ptm1 = pLine[0];
            ptm2 = pLine[1];
            ptm1.x = pStart.x<pEnd.x ? ptm1.x+1 : ptm1.x-1;
            if(!LineOverTaskLine(ptm1,ptm2) && !PointInEventPoint(ptm2))
            {
              ptm1 = pLine[2];
              ptm2 = pLine[3];
              ptm2.x = pLine[2].x<pLine[3].x ? ptm2.x-1 : ptm2.x+1;
              if(!LineOverTaskLine(ptm1,ptm2) && !PointInEventPoint(ptm1))
                LineType = 3;
            }
//            if(
//               !LineOverTaskLine(pLine[0],pLine[1]) && !PointInEventPoint(pLine[1])
//               && !LineOverTaskLine(pLine[2],pLine[3]) && !PointInEventPoint(pLine[2])
//              )
//              LineType = 3;
          }
          if(LineType==0)//竖横竖
          {
            if(StartInEvent && EndInEvent)
            {
              if(pStart.y<pEnd.y)
              {
                pStart.x = tmStart.x+2;
                pEnd.x = tmEnd.x+2;
              }
              else
              {
                pStart.x = tmStart.x-2;
                pEnd.x = tmEnd.x-2;
              }
            }
            pLine[1].x = pStart.x;
            pLine[2].x = pEnd.x;
            pLine[1].y = (pStart.y+pEnd.y)/2;
            pLine[2].y = pLine[1].y;
            if(
               !LineOverTaskLine(pLine[1],pLine[2]) && !PointInEventPoint(pLine[1])
               && !PointInEventPoint(pLine[2])
              )
              LineType = 4;

            int Step = AHeight;
            if(LineType==0)
            {
              if(pLine[0].y>pLine[1].y) Step = -Step;
              pLine[1].y = pStart.y;
              while(LineType==0 && abs(pLine[1].y-pEnd.y)>AHeight)//竖横竖
              {
                pLine[1].y +=Step;
                pLine[2].y = pLine[1].y;
                if(
                 !LineOverTaskLine(pLine[1],pLine[2]) && !PointInEventPoint(pLine[1])
                 && !PointInEventPoint(pLine[2])
                  )
                  LineType = 4;
              }
            }
            if(LineType==0)
            {
              Step = Step /2 ;
              pLine[1].y = pStart.y;
              while(LineType==0 && abs(pLine[1].y-pEnd.y)>AHeight)//竖横竖
              {
                pLine[1].y +=Step;
                pLine[2].y = pLine[1].y;
                if(
                 !LineOverTaskLine(pLine[1],pLine[2]) && !PointInEventPoint(pLine[1])
                 && !PointInEventPoint(pLine[2])
                  )
                  LineType = 4;
              }
            }
          }
          switch(LineType)
          {
            case 1:
            case 2:
              pTextStart = pLine[0];
              pTextEnd = pLine[1];
              break;
            case 3:
            case 4:
              pTextStart = pLine[1];
              pTextEnd = pLine[2];
              break;
          }
      }//else
      //画关系线
      TaskLinkLineList = new TList();
      TaskLinkBridgeList = new TList();
      AdjuestTaskLinkLine(pLine,LineCount);
      //画关系说明
      if(pTextStart.y==pTextEnd.y)//横线
      {
        if(pTextStart.x<pTextEnd.x)
          pTextStart.x += 7;
        else
          pTextEnd.x += 7;
      }
      else//竖线
      {
        if(AHeight < abs(pTextStart.y-pTextEnd.y))
          if(pTextStart.y<pTextEnd.y)
            pTextStart.y = pTextEnd.y - AHeight;//(pTextEnd.y-pTextStart.y)/3;
          else
            pTextStart.y = pTextEnd.y + AHeight;//(pTextStart.y-pTextEnd.y)/3;
      }

      TDCTaskLinkInfo *LinkInfo = new TDCTaskLinkInfo();
      LinkInfo->DrawArrow = DrawArrow;
      LinkInfo->DrawSolid = DrawSolid;
      LinkInfo->pStart = pStart;
      LinkInfo->pEnd = pEnd;
      LinkInfo->pTextStart = pTextStart;
      LinkInfo->pTextEnd = pTextEnd;
      LinkInfo->LinkLineList = TaskLinkLineList;
      LinkInfo->LinkBridgeList = TaskLinkBridgeList;
      TaskLinkList->Add(LinkInfo);
  }//for
}
//----------------------------------------------------------------------------
//画关系文字， p1,p2组成的直线必须是一条横线或竖线
void TDCProject::DrawLinkText(HDC dc,int days,TFrontType ftType,POINT p1,POINT p2)
{
  String sDays = StrToInt(days);
  String sLinkType = "FS";
  switch(ftType)
  {
    case ftStartStart:
      sLinkType = "SS";
      break;
    case ftFinishFinish:
      sLinkType = "FF";
      break;
    case ftStartFinish:
      sLinkType = "SF";
      break;
  }
  RECT dr;
  if(p1.y==p2.y)//横线
  {
    if(p1.x==p2.x) return;
    if(p1.x<p2.x)
    {
      dr.left =  p1.x;
      dr.right = p2.x;
    }
    else
    {
      dr.left =  p2.x;
      dr.right = p1.x;
    }
    dr.top = p1.y - 50;
	dr.bottom = p1.y - 2;
	DrawText(dc, sLinkType.c_str(), sLinkType.Length(), &dr, DT_BOTTOM | DT_CENTER |DT_SINGLELINE);
	dr.top = p1.y + 2;
	dr.bottom = p1.y + 50;
	DrawText(dc, sDays.c_str(), sDays.Length(), &dr, DT_CENTER |DT_TOP |DT_SINGLELINE);
  }
  else//竖线
  {
    if(p1.y==p2.y) return;
    if(p1.y<p2.y)
    {
      dr.top =  p1.y;
      dr.bottom = p2.y;
    }
    else
    {
      dr.top =  p2.y;
      dr.bottom = p1.y;
    }
    dr.left = p1.x - 50;
	dr.right = p1.x - 2;
	DrawText(dc, sLinkType.c_str(), sLinkType.Length(), &dr, DT_VCENTER |DT_RIGHT |DT_SINGLELINE);

	dr.left = p1.x + 2;
	dr.right = p1.x + 50;

	DrawText(dc, sDays.c_str(), sDays.Length(), &dr, DT_VCENTER |DT_LEFT |DT_SINGLELINE);
  }
}
//----------------------------------------------------------------------------
//dr确定画的最大宽度,必须传入
void TDCProject::DrawTaskText(HDC dc, RECT dr,int LimitHeight,TTask &ATask)
{
  int R = EventDraw.Radial;
  SIZE size;
  GetTextExtentPoint32(dc,L"长",2,&size);
  int ACharLen = size.cx;
  if(dr.right-dr.left < ACharLen) return;//不够位置画

  int iLeft = dr.right;
  int YPos = PointYWithRowY(ATask.DCY);
  int tmACharLen;
  int charCount;

  String ShowText ;
  if(!ATask.MileStone)
    ShowText = TopShowString.GetShowString(ATask);
  else
    ShowText = ATask.Name;

  if(dr.right-dr.left >= EventDiameter+ACharLen)
  {
    dr.left  += R;
    dr.right -= R;
  }

  dr.bottom = YPos;
  if(dr.right>iLeft-R)
  {
    dr.bottom = dr.bottom - R;
    LimitHeight -= R;
  }
  else
  {
    dr.bottom -= 3;
  }
  GetTextExtentPoint32(dc,ShowText.c_str(),ShowText.Length(),&size);
  charCount = (dr.right-dr.left)/ACharLen;
  charCount = charCount*ACharLen;
  charCount = size.cx%charCount==0 ? size.cx/charCount : size.cx/charCount+1;
  dr.top = dr.bottom - charCount*size.cy;
  if(dr.bottom-dr.top>LimitHeight)
  {
    TFont *tmFont = new TFont();
    tmFont->Assign(FChart->TextFont);
    HFONT tmHFont=NULL ,OldFont=NULL;
    while (dr.bottom-dr.top>LimitHeight && tmFont->Size>0)
    {
      tmFont->Size = tmFont->Size-1;
      if(tmHFont)     DeleteObject(tmHFont);
      tmHFont = CreateFontByTFont(tmFont);
      if(!OldFont)
		OldFont =(HFONT) SelectObject(dc, tmHFont);
      else
        SelectObject(dc, tmHFont);
	  GetTextExtentPoint32(dc,L"长",2,&size);
      tmACharLen = size.cx;
      charCount = (dr.right-dr.left)/tmACharLen;
      charCount = charCount*tmACharLen;
	  GetTextExtentPoint32(dc,ShowText.c_str(),ShowText.Length(),&size);
      charCount = size.cx%charCount==0 ? size.cx/charCount : size.cx/charCount+1;
      dr.top = dr.bottom - charCount*size.cy;
    }
    if(ATask.MileStone)
    {
      COLORREF oldcolor = SetTextColor(dc, clRed);
	  DrawText(dc, ShowText.c_str(), ShowText.Length(), &dr, DT_CENTER |DT_BOTTOM | DT_WORDBREAK);
      SetTextColor(dc, oldcolor);
    }
    else
	  DrawText(dc, ShowText.c_str(), ShowText.Length(), &dr, DT_CENTER |DT_BOTTOM | DT_WORDBREAK);
//    tmHFont = CreateFontByTFont(FChart->TextFont);
    SelectObject(dc, OldFont);
    DeleteObject(tmHFont);
  }
  else
	DrawText(dc, ShowText.c_str(), ShowText.Length(), &dr, DT_CENTER |DT_BOTTOM | DT_WORDBREAK);

  //BottomString
  if(ATask.MileStone) return;//里程碑不画
  ShowText = BottomShowString.GetShowString(ATask);
  GetTextExtentPoint32(dc,ShowText.c_str(),ShowText.Length(),&size);
  dr.top = YPos;
  if(dr.right>iLeft-R)
  {
    dr.top = dr.top + R;
    LimitHeight -= R;
  }
  else dr.top += 3;

  charCount = (dr.right-dr.left)/ACharLen;
  charCount = charCount*ACharLen;
  charCount = size.cx%charCount==0 ? size.cx/charCount : size.cx/charCount+1;
  dr.bottom = dr.top + charCount*size.cy;
  if(dr.bottom-dr.top>LimitHeight)
  {
    TFont *tmFont = new TFont();
    tmFont->Assign(FChart->TextFont);
    HFONT tmHFont=NULL ,OldFont=NULL;
    while (dr.bottom-dr.top>LimitHeight && tmFont->Size>0)
    {
      tmFont->Size = tmFont->Size-1;
      tmHFont = CreateFontByTFont(tmFont);
      if(tmHFont)     DeleteObject(tmHFont);
      if(!OldFont)
		OldFont =(HFONT) SelectObject(dc, tmHFont);
      else
        SelectObject(dc, tmHFont);
	  GetTextExtentPoint32(dc,L"长",2,&size);
	  tmACharLen = size.cx;
      charCount = (dr.right-dr.left)/tmACharLen;
      charCount = charCount*tmACharLen;
	  GetTextExtentPoint32(dc,ShowText.c_str(),ShowText.Length(),&size);
      charCount = size.cx%charCount==0 ? size.cx/charCount : size.cx/charCount+1;
      dr.bottom = dr.top + charCount*size.cy;
    }
	DrawText(dc, ShowText.c_str(), ShowText.Length(), &dr, DT_CENTER |DT_TOP | DT_WORDBREAK);
//    tmHFont = CreateFontByTFont(FChart->TextFont);
    SelectObject(dc, OldFont);
    DeleteObject(tmHFont);
  }
  else
	DrawText(dc, ShowText.c_str(), ShowText.Length(), &dr, DT_CENTER |DT_TOP | DT_WORDBREAK);
}
//----------------------------------------------------------------------------
void TDCProject::Draw(HDC dc, RECT dr)
{
    if(!FProject) return;

    if(!TaskPointList || !TaskLinkList) return;

    int TasksCount = FProject->Tasks.Count();
    int TaskLinksCount = FProject->TaskLinks.Count();

    if(TaskPointList->Count!=TasksCount) return;
    if(TaskLinkList->Count!=TaskLinksCount) return;

    HFONT aFont = CreateFontByTFont((&EventDraw)->EventFont);
    HGDIOBJ oldFont = SelectObject(dc, aFont);
    EventDraw.Init(dc, FProject->Tasks.Count()*2);//事件必须初始化
    EventDiameter = 2*EventDraw.Radial;
    int ArrowInc = EventDraw.Radial;
    SelectObject(dc, oldFont);
    DeleteObject(aFont);
    //FChart->TextFont->Size = 9;
    aFont = CreateFontByTFont(FChart->TextFont);
    oldFont = SelectObject(dc, aFont);
//    SetBkMode(dc, TRANSPARENT);
//    DrawText(dc, FChart->TextFont->Name.c_str(), FChart->TextFont->Name.Length(), &dr, DT_TOP | DT_SINGLELINE);
    int itop = dr.top-30 ;
    int ibottom = dr.bottom+30 ;
    int ileft = dr.left-150 ;
    int iright = dr.right+150 ;
//    int       TopRow , BottomRow;
//    TDateTime DrawLeftDay, DrawRightDay;
//    TopRow = RowYWithPointY(dr.top)-1;
//    BottomRow = RowYWithPointY(dr.bottom)+1;
//    DrawLeftDay = Calendar.XAtDay(dr.left - 2*ArrowInc);
//    DrawRightDay = Calendar.XAtDay(dr.right + 2*ArrowInc);
    //画任务
    RECT rtTask;
    TDCTaskDrawInfo *tdInfo ;
    SIZE size; POINT TaskEndPoint;
	GetTextExtentPoint32(dc,L"长",2,&size);
    int ACharLen = size.cx;
    int AHeight = RowHeight-3;
    int DCYPointY;

	int x1,x2,x3,x4;
    for(int i = 0; i < TasksCount; i++)
    {
        tdInfo = (TDCTaskDrawInfo *)TaskPointList->Items[i];
//        if(ATask.FF_StartDate > DrawRightDay || ATask.FF_EndDate < DrawLeftDay
//           || ATask.DCY < TopRow || ATask.DCY > BottomRow)
        if(tdInfo->xLeft > iright || tdInfo->xRight < ileft
           || tdInfo->DCYPointY < itop || tdInfo->DCYPointY > ibottom)
        {
            continue;
        }
        TTask& ATask = *(FProject->Tasks[i]);
        if(ATask.CostDays <= 0)
        {
            rtTask.left = tdInfo->xLeft;
            rtTask.right = tdInfo->xRight;
            DrawTaskText(dc,rtTask,AHeight,ATask);
            continue;
        }
        TTaskLine& ADraw = ATask.Critical ? CriticalDraw : TaskDraw;
        x1 = tdInfo->X1; x2 = tdInfo->X2; x3 = tdInfo->X3; x4 = tdInfo->X4;
        if(x1<ileft) x1=ileft;  if(x1>iright) x1 = iright;
        if(x2<ileft) x2=ileft;  if(x2>iright) x2 = iright;
        if(x3<ileft) x3=ileft;  if(x3>iright) x3 = iright;
        if(x4<ileft) x4=ileft;  if(x4>iright) x4 = iright;
        switch(ATask.PlanType)
        {
            case ptASAP:
            case ptMSO:
            case ptAFO:
            case ptASO:
            case ptBSO:
            case ptBFO:
            case ptMFO:
            {
                rtTask.left  = tdInfo->xLeft;
                rtTask.right = tdInfo->xRight;

                ADraw.Draw(dc, x1,x2,x3,x4,//Info->X1, tdInfo->X2, tdInfo->X3, tdInfo->X4,
                  tdInfo->DCYPointY, ArrowInc,tdInfo->DrawArrow);
                DrawTaskText(dc,rtTask,AHeight,ATask);
                break;
            }
            case ptALAP:
            {
                rtTask.left  = tdInfo->xLeft;
                rtTask.right = tdInfo->xRight;
                ADraw.Draw(dc, x1,x2,x3,x4,//Info->X1, tdInfo->X2, tdInfo->X3, tdInfo->X4,
                    tdInfo->DCYPointY, ArrowInc,tdInfo->DrawArrow);
                DrawTaskText(dc,rtTask,AHeight,ATask);
                break;
            }
            default:
                throw Exception("不支持此计划方法");
        }
    }//画任务

    int diff = ArrowInc*1.5;
    itop = dr.top-diff;
    ibottom = dr.bottom+diff;
    ileft = dr.left-diff;
    iright = dr.right+diff;

    //画虚任务
    TDCTaskLinkInfo *LinkInfo;
    //POINT pTextStart,pTextEnd;
    for(int i = 0; i < TaskLinksCount; i++)
    {
      if(TaskLinkList->Items[i]==NULL) continue;
      LinkInfo = (TDCTaskLinkInfo *)TaskLinkList->Items[i];
      if( (LinkInfo->pStart.y<itop && LinkInfo->pEnd.y<itop)
         ||(LinkInfo->pStart.y>ibottom && LinkInfo->pEnd.y>ibottom)
         ||(LinkInfo->pStart.x>iright && LinkInfo->pEnd.x>iright)
         ||(LinkInfo->pStart.x<ileft && LinkInfo->pEnd.x<ileft)
        )
      {
        continue;
      }

      TTaskLink& ALink = *(FProject->TaskLinks[i]);
      TVirtualLine& Draw = ALink.Critical ?
//      (ALink.Task->Critical && ALink.Front->Critical) ?      //zws2004-08-30
                   CriticalVirtualDraw : VirtualDraw;

      TaskLinkLineList = LinkInfo->LinkLineList;
      TaskLinkBridgeList = LinkInfo->LinkBridgeList;

      if(TaskLinkBridgeList->Count>0)
      {
        TBridgeLine* bridge = new TBridgeLine();
        bridge->Direction = TBridgeLine::bldRight;
        HPEN pen ;
        if(LinkInfo->DrawSolid)
          pen = CreatePen(PS_SOLID, 1, Draw.Color);
        else
          pen = CreatePen(PS_DOT, 0, Draw.Color);
        HGDIOBJ oldpen = SelectObject(dc, pen);
        TPoint * pt; POINT tmp;
        for(int k=TaskLinkBridgeList->Count-1; k>=0; k--)
        {
          pt = (TPoint *)TaskLinkBridgeList->Items[k];
          tmp. y= pt->y;
          tmp. x= pt->x+TaskBridgeRadii+1;
          if(PointInEventPoint(tmp))
          {
            bridge->Direction = TBridgeLine::bldLeft;
            bridge->Draw(dc,pt->x,pt->y,TaskBridgeRadii);
            bridge->Direction = TBridgeLine::bldRight;
          }
          else  bridge->Draw(dc,pt->x,pt->y,TaskBridgeRadii);
        }
        SelectObject(dc, oldpen);
        DeleteObject(pen);
      }
      Draw.Draw(dc,TaskLinkLineList,ArrowInc,LinkInfo->DrawArrow,LinkInfo->DrawSolid);
      //pTextStart = LinkInfo->pTextStart;
      //pTextEnd = LinkInfo->pTextEnd;
      DrawLinkText(dc,ALink.FreeTime,ALink.Type,LinkInfo->pTextStart,LinkInfo->pTextEnd);
    }//for

    //画事件
    SelectObject(dc, oldFont);
    DeleteObject(aFont);
    aFont = CreateFontByTFont((&EventDraw)->EventFont);
    oldFont = SelectObject(dc, aFont);

    TEventData *t;
    POINT pt;
    for(int i=EventPointList->Count-1; i>=0; i--)
    {
      t = (TEventData *) EventPointList->Items[i];
      if(t->x < ileft || t->x > iright || t->y < itop || t->y > ibottom)
        continue;
      pt.x = t->x;
      pt.y = t->y;
      EventDraw.Draw(dc, pt, t->EventNo, false);
    }
    SelectObject(dc, oldFont);
    DeleteObject(aFont);
    if(FProject->Selected)
    {
      int iY = PointYWithRowY(FProject->Selected->DCY);
      HRGN invert = CreateRectRgn(Calendar.GetDayLeft(FProject->Selected->FF_StartDate),// - FChart->FHORZ.nPos,
                              iY - 5 ,//- FChart->FVERT.nPos,
                              Calendar.GetDayRight(FProject->Selected->FF_EndDate),// - FChart->FHORZ.nPos,
                              iY + 5 //- FChart->FVERT.nPos
                              );
      InvertRgn(dc, invert);
      DeleteObject(invert);
    }
}
//---------------------------------------------------------------------------
void TDCProject::DrawCalendar(HDC dc, int ALeft, int AWidth)
{
    HFONT font = CreateFontByTFont(FChart->Font);
    HGDIOBJ oldfont = SelectObject(dc, font);

    RECT rect;
    rect.left = ALeft;
    rect.right = rect.left + AWidth;
    rect.top = 0;
    rect.bottom = CalendarHeight;
    int maxHeight=max(FChart->TotalHeight,Calendar.ChartHeight);
    Calendar.Draw(dc, rect, maxHeight/*Calendar.ChartHeight*/);

    SelectObject(dc, oldfont);
    DeleteObject(font);
}
//---------------------------------------------------------------------------
void TDCProject::IniCalendar()
{
    int ReservedLength= Calendar.GetColWidth()*2;
    Calendar.AutoAlignStartEnd(FProject->ASAP_StartDate,FProject->ALAP_EndDate ,ReservedLength,ReservedLength);
}
//---------------------------------------------------------------------------
void TDCProject::AutoAlign()
{
    IniCalendar();
    Calendar.Init();
    FChart->AdjustScrollBar();
    FChart->Invalidate();
}
//---------------------------------------------------------------------------
//-------  事件  -------------------------------------------------------
const IniEventValue = -1;
//---------------------------------------------------------------------------
//设置一个任务的前节点
void TDCProject::SetATaskStartEventNo(TTask* ATask,int iFrontCount)
{
  if(iFrontCount==0)
  {//没有前置任务，设前节点
    ATask->DCStartEvent = MaxEventNo;
    MaxEventNo++;
    if(ATask->CostDays == 0)
      ATask->DCEndEvent = ATask->DCStartEvent;
  }
  else
  {//有前置任务
    TTask *AFront = GetIlkDayLateTask(ATask,true);
    if(AFront)
    {
      ATask->DCStartEvent  = AFront->DCEndEvent;
//      ATask->EventStartDcy = AFront->EventEndDcy;
      ATask->StartInherit = true;
      return;
    }

    int i;
	if(ATask->StartLinkCount>1)
    {
      ATask->DCStartEvent  = MaxEventNo;
      MaxEventNo++;
      return;
    }

    AFront = NULL;
    int TaskDcy = ATask->DCY;
    //取一个ftFinishStart关系的前置
    for(i=ATask->FrontTaskCount-1; i>=0; i--)
    {
      if(ATask->FrontTasks[i]->Type==ftFinishStart)
      {
        AFront = ATask->FrontTasks[i]->Front;
        if(TaskDcy == AFront->DCY)//DCY相同者优先
        {
          break;
        }
      }
    }//for
    if(!AFront)
    {
      ATask->DCStartEvent  = MaxEventNo;
      MaxEventNo++;
    }
    else
    {
      ATask->DCStartEvent  = AFront->DCEndEvent;
//      ATask->EventStartDcy = AFront->EventEndDcy;
      ATask->StartInherit = true;
    }
  }//else
}
//---------------------------------------------------------------------------
//仅有的一个后置的所有前置具有相同的前节点号,true0：都相等；
//调用前要保证ATask仅有一个后置
void TDCProject::LateHaveIlkFrontNo(TTask* ATask,TList* IlkTasks,TList* DiffTasks)
{
  TTask* Late = ATask->LateTasks[0]->Task;
  TList * AList = NULL;
  int DealCount = 0;
  int FrontCount = Late->FrontTaskCount ;
  int iFrontNo = 0;// = Late->FrontTasks[0]->Front->DCStartEvent;
  int i,n;
  StackArray<byte,8> DealIndex(FrontCount);
  for(i=0; i<FrontCount; i++)
  {
    for(n=0; n<DealCount; n++)
      if(i==DealIndex[n]) continue;

    iFrontNo = Late->FrontTasks[i]->Front->DCStartEvent;
    AList = new TList();
    for(int n=0; n<FrontCount; n++)
    {
      if(n==i)continue;
      if(iFrontNo==Late->FrontTasks[n]->Front->DCStartEvent)
      {
        AList->Add(Late->FrontTasks[n]);
        DealIndex[DealCount] = n;
        DealCount++;
      }
    }
    if(AList->Count>0)
    {
      AList->Add(Late->FrontTasks[i]);
      DealIndex[DealCount] = i;
      DealCount++;
      IlkTasks->Add(AList);
    }
    if(DealCount==FrontCount)
      return;
  }
  for(i=0; i<FrontCount; i++)
  {
    for(n=0; n<DealCount; n++)
      if(i==DealIndex[n]) continue;
      
    DiffTasks->Add(Late->FrontTasks[i]);
  }
}
//---------------------------------------------------------------------------
//后置的所有前置具有相同的前节点号,0：都不相等；1：前节点号都相等；2：部分相等
//调用前要保证ATask有后置
int TDCProject::HaveIlkFrontNo(TTask* ATask)
{
  TTask* Late = ATask->LateTasks[0]->Task;
  int iFrontNo = Late->FrontTasks[0]->Front->DCStartEvent;
  int iCount;
  int iFrontCount =Late->FrontTaskCount;
  for(int n=iFrontCount-1; n>=0; n--)
  {
    iFrontNo = Late->FrontTasks[n]->Front->DCStartEvent;
    iCount = 0;
    for(int i=iFrontCount-1; i>=0; i--)
    {
      if(iFrontNo==Late->FrontTasks[i]->Front->DCStartEvent)
        iCount++;
    }
    if(iCount==iFrontCount)
      return 1;
    else if(iCount>1)
      return 2;
  }
  return 0;
}
//---------------------------------------------------------------------------
//ATask的所有后置的前置是相同的,true为是
bool TDCProject::AllLateHaveIlkFront(TTask* ATask,int iLateCount)
{
//  if(iLateCount==1)
//    return true;

  int i,k,n;
  int CurFrontCount = ATask->LateTasks[0]->Task->FrontTaskCount;
  for(i=1; i<iLateCount; i++)
  {
    if(CurFrontCount != ATask->LateTasks[i]->Task->FrontTaskCount)
      return false;//数目不相等
  }

  StackArray<TTask*,8> CurLateTask(iLateCount);
  for(i=0; i<iLateCount; i++)
  {
    CurLateTask[i] = ATask->LateTasks[i]->Task;
  }
  int iFrontCount = CurLateTask[0]->FrontTaskCount;
  StackArray<TTask*,8> CurFrontTask(iFrontCount);
  for(i=0; i<iFrontCount; i++)
  {
    CurFrontTask[i] = CurLateTask[0]->FrontTasks[i]->Front;
  }
  TTask *AFront;
  bool bIn = false;
  for(i=0; i<iLateCount; i++)
  {
    for(k=0; k<iFrontCount; k++)
    {
      AFront = CurLateTask[i]->FrontTasks[k]->Front;
      bIn = false;
      for(n=0; n<iFrontCount; n++)
        if(AFront==CurFrontTask[n])
        {
          bIn = true;
          break;
        }
      if(!bIn) return false;
    }
  }
  return true;
}
//---------------------------------------------------------------------------
//取首尾相接的前(/后)置任务
TTask* TDCProject::GetIlkDayLateTask(TTask* CurTask,bool bStart)
{
  int iDcy = CurTask->DCY;
  TDateTime dt ;
  if(bStart)
  {
    dt = CurTask->FF_StartDate;
    for(int i=CurTask->FrontTaskCount-1; i>=0; i--)
    {
      if(CurTask->FrontTasks[i]->Front->DCY == iDcy)
		if(abs(CurTask->FrontTasks[i]->Front->FF_EndDate - dt)<=1)
          return CurTask->FrontTasks[i]->Front;
    }
  }
  else
  {
    for(int i=CurTask->LateTaskCount-1; i>=0; i--)
    {
      dt = CurTask->FF_EndDate;
      if(CurTask->LateTasks[i]->Task->DCY == iDcy)
		if(abs(CurTask->LateTasks[i]->Task->FF_StartDate - dt)<=1)
          return CurTask->LateTasks[i]->Task;
    }
  }
  return NULL;
}
//---------------------------------------------------------------------------
//取首尾相接的任务
TTask* TDCProject::GetIlkDayTask(TTask* CurTask,bool bStart)
{
  int iDcy = CurTask->DCY;
  TDateTime dt ;
  if(bStart)
  {
    dt = CurTask->FF_StartDate;
    for(int i=FProject->Tasks.Count()-1; i>=0; i--)
    {
      if(FProject->Tasks[i]->DCY == iDcy)
		if(abs(FProject->Tasks[i]->FF_EndDate - dt)<=1)
          return FProject->Tasks[i];
    }
  }
  else
  {
    dt = CurTask->FF_EndDate;
    for(int i=FProject->Tasks.Count()-1; i>=0; i--)
    {
      if(FProject->Tasks[i]->DCY == iDcy)
		if(abs(FProject->Tasks[i]->FF_StartDate - dt)<=1)
          return FProject->Tasks[i];
    }
  }
  return NULL;
}
//---------------------------------------------------------------------------
//返回CurTask后置中比 iMaxValue小的 最大DCY的任务
//要确保有后置
TTask* TDCProject::GetMaxLateTask(TTask* CurTask,int iMaxValue)
{
  TTask* LateTask = CurTask->LateTasks[0]->Task;
  int iDcy = -1;
  bool HaveFinishStart = false;
  for(int i=CurTask->LateTaskCount-1; i>=0; i--)
  {
    if(CurTask->LateTasks[i]->Type==ftFinishStart)
    {
      HaveFinishStart = true;
      iDcy = CurTask->LateTasks[i]->Task->DCY;
      if(iDcy < iMaxValue && LateTask->DCY < iDcy)
        LateTask = CurTask->LateTasks[i]->Task;//取DCY最大的后置
    }
  }
  if(!HaveFinishStart)//不存在 完成开始 类型时才取其它类型
      for(int i=CurTask->LateTaskCount-1; i>=0; i--)
      {
          HaveFinishStart = true;
          iDcy = CurTask->LateTasks[i]->Task->DCY;
          if(iDcy < iMaxValue && LateTask->DCY < iDcy)
            LateTask = CurTask->LateTasks[i]->Task;//取DCY最大的后置
      }

  if(LateTask->DCY>iMaxValue) return NULL;

  return LateTask;
}
//---------------------------------------------------------------------------
//取与CurTask有相等DCY的CurTask的紧后置
TTask* TDCProject::GetEqualDCYTask(TTask* CurTask)
{
  for(int i=CurTask->LateTaskCount-1; i>=0; i--)
  {
	if(CurTask->LateTasks[i]->Task->DCY = CurTask->DCY)
    {
	  if(abs(CurTask->EndDate - CurTask->LateTasks[i]->Task->StartDate)==0)
		return CurTask->LateTasks[i]->Task;
    }
  }
  return NULL;
}
//---------------------------------------------------------------------------
//设置一个任务的后节点
void TDCProject::SetATaskEndEventNo(TTask* ATask,int iLateCount)
{
  if(iLateCount==0)
  {
    if(ATask->CostDays == 0)//里程碑
      ATask->DCEndEvent = ATask->DCStartEvent;
    else
    {
      ATask->DCEndEvent = MaxEventNo;
      MaxEventNo++;
    }
    return;
  }
  //下面的代码已确定有后置
//  int Count = 0;
//  for(int i=ATask->LateTaskCount-1; i>=0; i--)
//    if(ATask->LateTasks[i]->Type==ftFinishStart)
//      Count++;
//  //if(iLateCount==1 && ATask->LateTasks[0]->Type==ftFinishStart)
//  if(Count==0)
  if(ATask->EndFSCount==0)
  {
    ATask->DCEndEvent = MaxEventNo;
    MaxEventNo++;
    return;
  }
  else if(ATask->EndFSCount==1)
  {
    int i;
    TTask* LateTask;
    for(i=ATask->LateTaskCount-1; i>=0; i--)
      if(ATask->LateTasks[i]->Type == ftFinishStart)
        LateTask = ATask->LateTasks[i]->Task;

    if(LateTask->StartLinkCount==1)
    {
      if(LateTask->DCStartEvent==IniEventValue)
      {
        ATask->DCEndEvent = MaxEventNo;
        LateTask->DCStartEvent = MaxEventNo;
        LateTask->StartInherit = true;
        MaxEventNo++;
      }
      else
      {
        ATask->DCEndEvent = LateTask->DCStartEvent;
        ATask->EndInherit = true;
      }
      return;
    }
    else //(LateTask->StartLinkCount>1)
    {
      TTask* IlkDayTask = GetIlkDayLateTask(LateTask,true);
      TTask* FrontTask;
      for(int i=LateTask->FrontTaskCount-1; i>=0; i--)
      {
        FrontTask = LateTask->FrontTasks[i]->Front;
        if(IlkDayTask==FrontTask)continue;
        switch(LateTask->FrontTasks[i]->Type)
        {
          case ftFinishStart:
            if(FrontTask->DCEndEvent!=IniEventValue) continue;
            if(FrontTask->StartInherit || FrontTask->EndLinkCount>1)
            {
              FrontTask->DCEndEvent = MaxEventNo;
              MaxEventNo++;
            }
            break;
          case ftStartStart:
            if(FrontTask->DCStartEvent!=IniEventValue) continue;
            FrontTask->DCStartEvent = MaxEventNo;
            MaxEventNo++;
            break;
          case ftFinishFinish:
            if(FrontTask->DCEndEvent!=IniEventValue) continue;
            FrontTask->DCEndEvent = MaxEventNo;
            MaxEventNo++;
            break;
          case ftStartFinish:
            if(FrontTask->DCStartEvent!=IniEventValue) continue;
            FrontTask->DCStartEvent = MaxEventNo;
            MaxEventNo++;
            break;
        }//switch
      }//for

      //if(LateTask->DCStartEvent==IniEventValue)//不可能为IniEventValue
      //{
        LateTask->DCStartEvent = MaxEventNo;
        MaxEventNo++;
      //}
      int iEventNo = LateTask->DCStartEvent;
      if(IlkDayTask)
      {
        IlkDayTask->DCEndEvent = iEventNo;
        IlkDayTask->EndInherit = true;
      }
      for(i=LateTask->FrontTaskCount-1; i>=0; i--)
      {
        FrontTask = LateTask->FrontTasks[i]->Front;
        if(LateTask->FrontTasks[i]->Type==ftFinishStart)
          if(FrontTask->DCEndEvent==IniEventValue)
          {
            FrontTask->DCEndEvent = iEventNo;
            FrontTask->EndInherit = true;
          }
      }
    }//else
  }//else if(ATask->EndFSCount==1)
}
//---------------------------------------------------------------------------
//设置一个任务的节点
void TDCProject::SetTaskEventNo(TTask* ATask)
{
//  String sss = ATask->Name+":-:\n";
//  TTask *tt ;
//  for(int i = 0; i < FProject->Tasks.Count(); i++)
//  {
//    tt = FProject->Tasks[i];
//    sss =  sss
//        +": se="+ tt->DCStartEvent
//        +": ee="+ tt->DCEndEvent
//  //      +": sd="+ tt->EventStartDcy
//  //      +": ed="+ tt->EventEndDcy
//        +": si="+ String(tt->StartInherit? 1 : 0)
//        +": ei="+ String(tt->EndInherit? 1 : 0)
//        +"  "+  tt->Name+" \n ";
//  }
//  ShowMessage(sss);
//  sss = sss;
  if(ATask->DCStartEvent!=IniEventValue && ATask->DCEndEvent!=IniEventValue)
    return;

  int i,k,iFrontCount,iLateCount;
  TTask* AFront,*ALate ;
  iFrontCount = ATask->FrontTaskCount;
  iLateCount = ATask->LateTaskCount;

  //前置处理
  if(ATask->DCStartEvent==IniEventValue || ATask->DCEndEvent==IniEventValue)
  {
      for(i=0; i < iFrontCount; i++)
      {
          AFront = ATask->FrontTasks[i]->Front;
//          if(AFront->DCEndEvent==IniEventValue && ATask->FrontTasks[i]->Type==ftFinishStart)
          switch(ATask->FrontTasks[i]->Type)
          {
            case ftFinishStart:
            case ftFinishFinish:
              if(AFront->DCEndEvent==IniEventValue)
                SetTaskEventNo(AFront);
              break;
            case ftStartStart:
            case ftStartFinish:
              if(AFront->DCStartEvent==IniEventValue)
                SetTaskEventNo(AFront);
              break;
          }
      }
  }

  if(ATask->DCStartEvent==IniEventValue)
    SetATaskStartEventNo(ATask,iFrontCount);//设前节点

//      for(i=0; i < iFrontCount; i++)
//      {
//          AFront = ATask->FrontTasks[i]->Front;
//          if(AFront->DCEndEvent==IniEventValue && ATask->FrontTasks[i]->Type!=ftFinishStart)
//            SetTaskEventNo(AFront);
//      }

  //后置处理
  if(ATask->DCEndEvent == IniEventValue)
  {
    ALate = GetIlkDayLateTask(ATask,false);
    if(ALate && (ALate->DCStartEvent==IniEventValue))
    {
      TTask *tmFront;
      for(k=0; k<ALate->FrontTaskCount; k++)
      {
        if(ALate->FrontTasks[k]->Type==ftFinishStart || ALate->FrontTasks[k]->Type==ftStartStart)
        {
          tmFront = ALate->FrontTasks[k]->Front;
          if(tmFront->DCStartEvent==IniEventValue)
            SetTaskEventNo(tmFront);
        }
      }
    }
    if(ATask->DCEndEvent == IniEventValue)
    {//有两个及以上的后置，则必须有后节点
//      i = 0;
//      for(k=0; k<iLateCount; k++)
//        if(ATask->LateTasks[k]->Type==ftFinishStart || ATask->LateTasks[k]->Type==ftFinishFinish)
//          i++;
//      for(k=0; k<iFrontCount; k++)
//        if(ATask->FrontTasks[k]->Type==ftStartFinish || ATask->FrontTasks[k]->Type==ftFinishFinish)
//          i++;
//      if(i>1)

      if(ATask->EndLinkCount>1)
      {
        if(!ATask->CostDays==0)
        {
          ATask->DCEndEvent = MaxEventNo;
          MaxEventNo++;
        }
        else
        {
          ATask->DCEndEvent = ATask->DCStartEvent;
          ATask->EndInherit = true;
        }
      }
    }
    if(ATask->DCEndEvent==IniEventValue)
    { //找ATask的有1个以上前置的后置中的前置
      for(i=0; i<iLateCount; i++)
      {
        if(!(ATask->LateTasks[i]->Type==ftFinishStart || ATask->LateTasks[i]->Type==ftFinishFinish))
          continue;

        ALate = ATask->LateTasks[i]->Task;
        if(ALate->DCStartEvent==IniEventValue && ALate->FrontTaskCount>=2)
        {
          TTask *tmFront;
          for(k=0; k<ALate->FrontTaskCount; k++)
          {
  //          if(ALate->FrontTasks[k]->Type!=ftFinishStart) continue;
            tmFront = ALate->FrontTasks[k]->Front;
            if(tmFront->DCStartEvent==IniEventValue)
              SetTaskEventNo(tmFront);
          }
        }
      }//for
    }
  }
  if(ATask->DCEndEvent==IniEventValue)//这个判断必须再次使用
    SetATaskEndEventNo(ATask,iLateCount);//设后节点

  for(k=0; k<iLateCount; k++)
  {
    ALate = ATask->LateTasks[k]->Task;
    if(ALate->DCStartEvent==IniEventValue || ALate->DCEndEvent==IniEventValue)
      SetTaskEventNo(ALate);
  }
}
//---------------------------------------------------------------------------
void TDCProject::SortEventNo()
{
  TTask* ATask;
  MaxEventNo = 1;
  int TasksCount = FProject->Tasks.Count();
  for(int i = 0; i < TasksCount; i++)
  {
      ATask = FProject->Tasks[i];
      ATask->DCStartEvent  = IniEventValue;
      ATask->DCEndEvent    = IniEventValue;
      ATask->StartInherit  = false;
      ATask->EndInherit    = false;
//      ATask->EventStartDcy = ATask->DCY;
//      ATask->EventEndDcy   = ATask->DCY;
  }
  for(int i = 0; i < TasksCount; i++)
  {
      ATask = FProject->Tasks[i];
      if(ATask->FrontTaskCount==0 && ATask->DCStartEvent==IniEventValue)
        SetTaskEventNo(ATask);
  }
}
//________________ 事件 ____________________________________________________
//---------------------------------------------------------------------------
bool __fastcall PointInRoundRect(POINT C, int R, int X, int Y)
{
  return R*R >= (X-C.x)*(X-C.x)+(Y-C.y)*(Y-C.y);
}
//---------------------------------------------------------------------------
TTask* __fastcall TDCProject::TaskFromPoint(int X, int Y)
{
    if(!FProject)
        return NULL;

    TTask* result = NULL;

	int dcy = RowYWithPointY(Y);
    int iRadial = EventDraw.Radial;
    int TasksCount = FProject->Tasks.Count();
    TDCTaskDrawInfo *tdInfo;
    for(int i = 0; i < TasksCount; i++)
    {
       if (FProject->Tasks[i]->DCY != dcy) continue;
       tdInfo = (TDCTaskDrawInfo *)TaskPointList->Items[i];
       if((abs(tdInfo->DCYPointY - Y) < 10)
           && tdInfo->xLeft-iRadial <= X
           && tdInfo->xRight+iRadial >= X
         )
       {
         result = FProject->Tasks[i];
       }
    }
    return result;
}
//---------------------------------------------------------------------------
void __fastcall TDCProject::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
    if(!FProject)
        return;

//    POINT EventPoint;
    int dcy = RowYWithPointY(Y);
    int iRadial = EventDraw.Radial;
//    TDateTime dt = Calendar.XAtDay(X);
    int TasksCount = FProject->Tasks.Count();
    TDCTaskDrawInfo *tdInfo;
    for(int i = 0; i < TasksCount; i++)
    {
       if (FProject->Tasks[i]->DCY != dcy) continue;
       tdInfo = (TDCTaskDrawInfo *)TaskPointList->Items[i];
       if((abs(tdInfo->DCYPointY - Y) < 10)
           && tdInfo->xLeft-iRadial <= X
           && tdInfo->xRight+iRadial >= X
         )
       {
         FDragTask = FProject->Tasks[i];
         FProject->Selected = FDragTask;
         FDraging = true;
         FDragStartY = Y;
         SetCapture(FChart->Handle);
         FOldInvertY = -1;
         return;
       }
    }
}
//---------------------------------------------------------------------------
void __fastcall TDCProject::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
    if(FDraging)
    {
         if(FOldInvertY > 0 || abs(Y - FDragStartY) > 10)
         {
              HDC dc = GetDC(FChart->Handle);
              if(FOldInvertY > 0)
              {
                   HRGN invert = CreateRectRgn(Calendar.GetDayLeft(FDragTask->FF_StartDate) - FChart->FHORZ.nPos,
                                               FOldInvertY - 5 - FChart->FVERT.nPos,
                                               Calendar.GetDayRight(FDragTask->FF_EndDate) - FChart->FHORZ.nPos,
                                               FOldInvertY + 5 - FChart->FVERT.nPos);
                   InvertRgn(dc, invert);
                   DeleteObject(invert);
              }
              HRGN invert = CreateRectRgn(Calendar.GetDayLeft(FDragTask->FF_StartDate) - FChart->FHORZ.nPos,
                                          Y - 5 - FChart->FVERT.nPos,
                                          Calendar.GetDayRight(FDragTask->FF_EndDate) - FChart->FHORZ.nPos,
                                          Y + 5 - FChart->FVERT.nPos);
              InvertRgn(dc, invert);
              DeleteObject(invert);
              FOldInvertY = Y;
              ReleaseDC(FChart->Handle, dc);
         }
    }
}
//---------------------------------------------------------------------------
void __fastcall TDCProject::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{

    if(FDraging)
    {
         FDraging = false;
         ReleaseCapture();
         if(FDragTask)
         {
             int dcy = RowYWithPointY(Y);
             if(FDragTask->DCY != dcy)
             {
                 FDragTask->DCY = dcy;
                 //SortEventNo();
                 InitData();
                 FChart->AdjustScrollBar();
             }
         }
         FChart->Invalidate();
    }
}
//---------------------------------------------------------------------------
//有任务完全被ATask覆盖时调DCY垂直位置
//垂直移动某一任务的所有前后置任务
//void MoveAPath(TTask* AStart, int Inc)
//{
//    AStart->DCY += Inc;
//    AStart->Visited = true;
//    for(int i = 0; i < AStart->LateTaskCount; i++)
//    {
//        if(!AStart->LateTasks[i]->Task->Visited)
//        {
//            MoveAPath(AStart->LateTasks[i]->Task, Inc);
//        }
//    }
//    for(int i = 0; i < AStart->FrontTaskCount; i++)
//    {
//        if(!AStart->FrontTasks[i]->Front->Visited)
//        {
//            MoveAPath(AStart->FrontTasks[i]->Front, Inc);
//        }
//    }
//}

//bool TDCProject::DownWillOverlap(TTask* AStart, int Inc)
//{
//    int AStartDCY = AStart->DCY ;
//    int AddDcy = AStartDCY+Inc;
//    if(AddDcy<0) return true;     //zws2004-08-31
//    int StartDateLeft,StartDateRight,DateLeft,DateRight;
//     GetTaskDate(AStart,StartDateLeft,StartDateRight);
//     //int EventDiameter = EventDraw.Radial*2;
//      for(int k = 0; k < FProject->Tasks.Count(); k++)
//      {
//          if(AddDcy == FProject->Tasks[k]->DCY)
//          {
//              GetTaskDate(FProject->Tasks[k], DateLeft, DateRight);
//              if(!(StartDateLeft>DateRight || StartDateRight<DateLeft)||abs(StartDateLeft-DateRight)<EventDiameter || abs(StartDateLeft-DateLeft)<EventDiameter
//               || abs(StartDateRight-DateRight)<EventDiameter || abs(StartDateRight-DateLeft)<EventDiameter)
//              {
//                  return true;
//              }
//          }
//      }
//    return false;
//}
//垂直移动所有 级数更大的 任务
void TDCProject::MoveBigDCY(TTask* AStart, int Inc)
{
    //ShowMessage("MoveBigDCY: "+AStart->Name +"-"+ IntToStr(AStart->DCY));
    int AStartDCY = AStart->DCY;

    for(int i = 0; i < FProject->Tasks.Count(); i++)
    {
        if(AStart!=FProject->Tasks[i] && AStartDCY <= FProject->Tasks[i]->DCY)
        {
          FProject->Tasks[i]->DCY += Inc ;
//          //ShowMessage(FProject->Tasks[i]->Name +"-"+ IntToStr(FProject->Tasks[i]->DCY));
        }
    }
}
//垂直移动某一任务的所有 同级的后置的 任务
//void MoveAPathLate(TTask* AStart, int Inc)
//{
    //ShowMessage("MoveAPathLate: "+AStart->Name +"-"+ IntToStr(AStart->DCY));
//
//    int AStartDCY = AStart->DCY;
//    AStart->DCY += Inc;
//    for(int i = 0; i < AStart->LateTaskCount; i++)
//    {
//        if(AStartDCY == AStart->LateTasks[i]->Task->DCY)
//        {
//          AStart->LateTasks[i]->Task->DCY += Inc;
////          ShowMessage(AStart->LateTasks[i]->Task->Name +"-"+ IntToStr(AStart->LateTasks[i]->Task->DCY));
//        }
//    }
//}
void TDCProject::GetTaskDate(TTask* ATask, int &DateLeft, int &DateRight)
{
  TTask & sdTask = *ATask;
  DateLeft = Calendar.GetDayLeft(sdTask.FF_StartDate);
  DateRight = Calendar.GetDayRight(sdTask.FF_EndDate);
}

//sdTask1是否与sdTask2重叠
bool TDCProject::TaskIsOver(TTask* sdTask1,TTask* sdTask2)
{
//  if(sdTask1->DCY!=sdTask2->DCY)
//    return false;
//  double d1 = (double)sdTask2->FF_StartDate - sdTask1->FF_EndDate;
//  double d2 = (double)sdTask1->FF_StartDate - sdTask2->FF_EndDate;
//  if(d1>-1 || d2>-1)
//      return false;
//    else
//      return true;
    if(sdTask1->MileStone || sdTask2->MileStone)
      return false;

    int CurDateLeft,CurDateRight,DateLeft,DateRight;

    GetTaskDate(sdTask1,CurDateLeft,CurDateRight);
    GetTaskDate(sdTask2,DateLeft,DateRight);

    if(!(CurDateRight<=DateLeft||CurDateLeft>=DateRight))
      return true;
    else
      return false;
}
//aTask是否与别的任务重叠
bool TDCProject::TaskIsOver(TTask* sdTask)
{
//    TTask* tmTask;
//    int TasksCount = FProject->Tasks.Count();
//    for(int k = 0; k < TasksCount; k++)
//    {
//      tmTask = FProject->Tasks[k];
//      if(!tmTask->Visited || sdTask==tmTask || sdTask->DCY != tmTask->DCY)
//        continue;//只判断可见、DCY相同的任务
//
//      if((double)tmTask->FF_StartDate - sdTask->FF_EndDate >-1
//         || (double)sdTask->FF_StartDate - tmTask->FF_EndDate>-1)
//          return false;
//        else
//          return true;
////      if( abs((double)tmTask->FF_StartDate - sdTask->FF_EndDate) >=0
////         ||abs((double)sdTask->FF_StartDate - tmTask->FF_EndDate) >=0)
////        return false;
////      else
////        return true;
//    }
//
    if(sdTask->MileStone)
      return false;

    int CurDateLeft,CurDateRight,DateLeft,DateRight;

    GetTaskDate(sdTask,CurDateLeft,CurDateRight);

    for(int k = 0; k < FProject->Tasks.Count(); k++)
    {
      if(!FProject->Tasks[k]->Visited || sdTask==FProject->Tasks[k]
          || sdTask->DCY != FProject->Tasks[k]->DCY || FProject->Tasks[k]->MileStone)
        continue;//只判断可见、DCY相同的任务

      GetTaskDate(FProject->Tasks[k], DateLeft,DateRight);
//      if(!(CurDateRight<DateLeft||CurDateLeft>DateRight)||abs(CurDateRight-DateRight)<EventDiameter || abs(CurDateRight-DateLeft)<EventDiameter
  //       || abs(CurDateLeft-DateRight)<EventDiameter || abs(CurDateLeft-DateLeft)<EventDiameter)
      if(!(CurDateRight<=DateLeft||CurDateLeft>=DateRight))
      {
        return true;
      }
    }

    return false;
}
//返回CurTask后续未可见任务的最大DCY值
int TDCProject::GetMaxLateTaskDCY(TTask* CurTask)
{
  int MaxDcy = -1;
  for(int k=CurTask->LateTaskCount-1; k>=0; k--)
  {
    if(!CurTask->LateTasks[k]->Task->Visited)
    {
      if(MaxDcy < CurTask->LateTasks[k]->Task->DCY)
        MaxDcy = CurTask->LateTasks[k]->Task->DCY;
    }
  }
  return MaxDcy;
}
//返回　FProject中最大的DCY值
int TDCProject::GetMaxDCY()
{
  int MaxDcy = -1;
  for(int i = 0; i < FProject->Tasks.Count(); i++)
  {
    if(MaxDcy < FProject->Tasks[i]->DCY)
      MaxDcy = FProject->Tasks[i]->DCY;
  }
  return MaxDcy;
}
//若ATask有一个(不是CurTask的)前置,这个前置就只有ATask这个时后置时返回true
bool TDCProject::HaveOtherParentTask(TTask * CurTask,TTask *ATask)
{
  TTask *AFront;
  bool NotFSLink = false;
  bool HaveFSLink = false;
  for(int j=ATask->FrontTaskCount-1; j>=0; j--)
  {
    AFront = ATask->FrontTasks[j]->Front;
    if(CurTask==AFront)
    {
      NotFSLink = ATask->FrontTasks[j]->Type!=ftFinishStart;
      continue;
    }
//    if(AFront->LateTaskCount==1)
    if(ATask->FrontTasks[j]->Type==ftFinishStart)
    {
      HaveFSLink = true;
      if(AFront->EndFSCount==1)
        return true; //有
    }
  }
  if(NotFSLink && HaveFSLink)
    return true;
  else
    return false;//没有
}
void TDCProject::InitTaskDCY()
{
  HFONT aFont = CreateFontByTFont((&EventDraw)->EventFont);
  HDC dc = FChart->GetDrawDc();
  HGDIOBJ oldFont = SelectObject(dc, aFont);
  EventDraw.Init(dc, FProject->Tasks.Count()*2);
  EventDiameter = EventDraw.Radial*2;
  SelectObject(dc, oldFont);
  DeleteObject(aFont);


  int TasksCount = FProject->Tasks.Count();
  int TaskLinksCount = FProject->TaskLinks.Count();
  int i ;
  TTask *ATask;
  for(i= 0; i < TasksCount; i++)
  {
      ATask = FProject->Tasks[i];
      ATask->EndLinkCount  = 0;
      ATask->StartLinkCount= 0;
      ATask->EndFSCount  = 0;
  }

  TTaskLink* ALink = NULL;
  for(int i = 0; i < TaskLinksCount; i++)
  {
    ALink = FProject->TaskLinks[i];
    switch(ALink->Type)
    {
      case ftFinishStart :
        ALink->Front->EndLinkCount++;
        ALink->Front->EndFSCount++;
        ALink->Task->StartLinkCount++;
        break;
      case ftFinishFinish:
        ALink->Front->EndLinkCount++;
        ALink->Task->EndLinkCount++;
        break;
      case ftStartStart  :
        ALink->Front->StartLinkCount++;
        ALink->Task->StartLinkCount++;
        break;
      case ftStartFinish :
        ALink->Front->StartLinkCount++;
        ALink->Task->EndLinkCount++;
        break;
    }
  }//for

  const int ErrDCY = -1 ;
  TList *waitList = new TList;
  int k,n;
  int dealCount = 0;//后继且不可见的任务数
  int ltCount = 0;//后继任务数
  TTask * CurTask;
  int CurTaskDcy = 0;
  for(i = 0; i < TasksCount; i++) //初始化
  {
    FProject->Tasks[i]->DCY = ErrDCY;
//    FProject->Tasks[i]->DCYPathIndex = ErrDCY;
    FProject->Tasks[i]->Visited = false;
  }
  for(i = 0; i < TasksCount; i++)
  {
    CurTask = FProject->Tasks[i];
    if(CurTask->DCY==ErrDCY && CurTask->FrontTaskCount<=0)
    {
      CurTask->DCY = GetMaxDCY();
      if(CurTask->LateTaskCount>0 || TaskIsOver(CurTask))
        CurTask->DCY += 1;
      if(CurTask->DCY<0) CurTask->DCY = 0;
      CurTask->Visited = true;
lbStart:
      CurTaskDcy = CurTask->DCY;
      ltCount = CurTask->LateTaskCount;
      dealCount = 0;
      if(ltCount==1)
      {
          if(!CurTask->LateTasks[0]->Task->Visited)
          {
            CurTask->LateTasks[0]->Task->DCY = CurTaskDcy;
            dealCount++;
          }
      }
      else
      {
          for(k=0; k<ltCount; k++)//初始化下级位置
          {
            if(!CurTask->LateTasks[k]->Task->Visited
               && ! HaveOtherParentTask(CurTask,CurTask->LateTasks[k]->Task))
            {
              if(CurTask->EndFSCount==0)
                CurTask->LateTasks[k]->Task->DCY = CurTaskDcy+1;
              else
                CurTask->LateTasks[k]->Task->DCY = CurTaskDcy;
              dealCount++;
            }
          }
          if(dealCount==0)
          {
            if(waitList->Count>0)
            {
              CurTask = (TTask*)waitList->Items[0];
              waitList->Delete(0);
              goto lbStart;
            }
          }
          int kAuthority,nAuthority;
          for(k=0; k<ltCount; k++)//对下级进行排序，按工期长下短上排
          {
            if(CurTask->LateTasks[k]->Task->Visited
                || CurTask->LateTasks[k]->Task->DCY==ErrDCY) continue;

            for(n=k+1; n<ltCount; n++)
            {
              if(CurTask->LateTasks[n]->Task->Visited
                  || CurTask->LateTasks[n]->Task->DCY==ErrDCY)
                continue;//可见者不再处理，CurTask->DCY==ErrDCY者暂不处理

              kAuthority = 0;  nAuthority = 0;
              //ftFinishStart在上

              if(CurTask->LateTasks[k]->Type!=ftFinishStart)
                kAuthority = kAuthority + 1000;
              if(CurTask->LateTasks[n]->Type!=ftFinishStart)
                nAuthority = nAuthority + 1000;
			  if(CurTask->LateTasks[k]->Task->FF_StartDate!=CurTask->LateTasks[n]->Task->FF_StartDate)
              {
				if(CurTask->LateTasks[k]->Task->FF_StartDate < CurTask->FF_EndDate)
                  kAuthority = kAuthority + 100;
				if(CurTask->LateTasks[n]->Task->FF_StartDate < CurTask->FF_EndDate)
                  nAuthority = nAuthority + 100;
				if(CurTask->LateTasks[k]->Task->FF_StartDate > CurTask->LateTasks[n]->Task->FF_StartDate)
                  kAuthority = kAuthority + 10;
				else
                  nAuthority = nAuthority + 10;
              }
              if(CurTask->LateTasks[k]->Task->CostDays > CurTask->LateTasks[n]->Task->CostDays)
                kAuthority = kAuthority + 1;
              else
                nAuthority = nAuthority + 1;
              if(kAuthority > nAuthority)
                CurTask->LateTasks[k]->Task->DCY = CurTask->LateTasks[k]->Task->DCY + 1;
              else
                CurTask->LateTasks[n]->Task->DCY = CurTask->LateTasks[n]->Task->DCY + 1;
            }
          }
      }//else if(ltCount==1)
//String tstr = "";
//    tstr = CurTask->Name+"-"+IntToStr(CurTask->DCY)+" :: ";
//    for(k=0; k<ltCount; k++)
//    {
//      tstr = tstr +CurTask->LateTasks[k]->Task->Name+":"
//                +CurTask->LateTasks[k]->Task->CostDays+" - "
//                +IntToStr(CurTask->LateTasks[k]->Task->DCY)+"\n ";
//    }
//tstr = tstr + " ";
      for(k=0; k<ltCount; k++)
      {
        if(CurTaskDcy==CurTask->LateTasks[k]->Task->DCY && !CurTask->LateTasks[k]->Task->Visited)
        {
          if( TaskIsOver(CurTask->LateTasks[k]->Task,CurTask) )//最上面的任务与父任务重叠
          {//每个都+1
            for(n=0; n<ltCount; n++)
              if(!CurTask->LateTasks[n]->Task->Visited)
                CurTask->LateTasks[n]->Task->DCY = CurTask->LateTasks[n]->Task->DCY+1;
          }
          break;
        }
      }
      //下移大级的任务
      int tmMax = GetMaxLateTaskDCY(CurTask);
      if(tmMax>CurTaskDcy)
      {
        int moveDcy = tmMax - CurTaskDcy;
        TTask * tmTask;
        for(k=FProject->Tasks.Count()-1; k>=0; k--)
        {
          tmTask = FProject->Tasks[k];
          if(tmTask->Visited && tmTask->DCY > CurTaskDcy)
            tmTask->DCY = tmTask->DCY+moveDcy;
        }
      }

      //判断重叠性
      for(k=0; k<ltCount; k++)
      {
        if(!CurTask->LateTasks[k]->Task->Visited)
        {
          if(TaskIsOver(CurTask->LateTasks[k]->Task))
            MoveBigDCY(CurTask->LateTasks[k]->Task,1);
        }
      }

//String str = "";
//    str = CurTask->Name+"-"+IntToStr(CurTask->DCY)+" :: ";
//    for(k=0; k<ltCount; k++)
//    {
//      str = str +CurTask->LateTasks[k]->Task->Name+":"
//                +CurTask->LateTasks[k]->Task->CostDays+" - "
//                +IntToStr(CurTask->LateTasks[k]->Task->DCY)+"\n ";
//    }
//str = str + " ";
//String sstr = "";
//for(int ji = 0; ji < FProject->Tasks.Count(); ji++)
//      sstr = sstr +FProject->Tasks[ji]->Name+":"
//                +FProject->Tasks[ji]->CostDays+" - "
//                +IntToStr(FProject->Tasks[ji]->DCY)+"\n ";
//sstr = sstr+" ";

int LimitDCY = MAXINT;
      int index = -1;
      int iMax = -1;
      int tmDCY = 0;
      for(k=0; k<dealCount; k++)
      {
          index = -1;   iMax = -1;
          for(n=0; n<ltCount; n++)
          {
            if(!CurTask->LateTasks[n]->Task->Visited)
            {
              tmDCY = CurTask->LateTasks[n]->Task->DCY;
              if(tmDCY<LimitDCY && tmDCY>iMax)
              {
                iMax = tmDCY;
                index = n;
              }
            }
		  }
          if(index>-1)
          {
            LimitDCY = CurTask->LateTasks[index]->Task->DCY;
            CurTask->LateTasks[index]->Task->Visited = true;
            waitList->Add(CurTask->LateTasks[index]->Task);
          }
      }//for
lbNext:
      if(waitList->Count>0)
      {
		CurTask = (TTask*)waitList->Items[0];
        waitList->Delete(0);
        goto lbStart;
      }
    }//if
  }
  delete waitList;
//String sstr = "", ss="";
//for(int ji = 0; ji < FProject->Tasks.Count(); ji++)
//{
//      sstr = sstr +FProject->Tasks[ji]->Name+":"
//                +FProject->Tasks[ji]->CostDays+" - "
//                +IntToStr(FProject->Tasks[ji]->DCY)+"\n ";
//  if(FProject->Tasks[ji]->DCY<0)
//      ss = ss +FProject->Tasks[ji]->Name+":"
//                +FProject->Tasks[ji]->CostDays+" - "
//                +IntToStr(FProject->Tasks[ji]->DCY)+"\n ";
//}
//if(ss!="")
//  ShowMessage(ss);
//sstr = sstr+" ";
}
//---------------------------------------------------------------------------
int TDCProject::PointYWithRowY(int ARowY)
{
//    return CalendarHeight + ARowY * RowHeight + RowHeight / 2;
    return CalendarHeight + (ARowY+1) * RowHeight;
}
//---------------------------------------------------------------------------
int TDCProject::RowYWithPointY(int APointY)
{
//    return (APointY - CalendarHeight) / RowHeight;
    APointY = APointY - CalendarHeight;
    if(APointY <= RowHeight) return 0;
    int iRow = APointY/RowHeight;
    if(APointY%RowHeight *2 < RowHeight) iRow--;
    return iRow;
}
//---------------------------------------------------------------------------
// TDoubleCode
//---------------------------------------------------------------------------
__fastcall TDoubleCode::TDoubleCode(TComponent* Owner)
  : TWinControl(Owner)
{
    DrawingNavigation = false;
    DoubleBuffered = true;
    Font->Name = "宋体";
    Font->Size = 9;
    Font->Charset = GB2312_CHARSET;

    Width = 300;
    Height = 200;
    Color = clWhite;
    FDCProject = new TDCProject(this);
    FDCProject->Calendar.ChartHeight = Height;
    FDblClickAdjust = false;
    FTextFont = new TFont();
    SetDefault();
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

//    NaviImage = new TNavigationImage(this);//////
}
//---------------------------------------------------------------------------
__fastcall TDoubleCode::~TDoubleCode()
{
    delete FDCProject;
    delete FTextFont;
    //delete NaviImage;//////////
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::PaintWindow(HDC DC)
{
    int ftsize=FTextFont->Size;
    int efsize=EventDraw->EventFont->Size;
    FTextFont->Assign(Font);
    FTextFont->Size=ftsize;
    EventDraw->EventFont->Assign(Font);
    EventDraw->EventFont->Size=efsize;

    RECT dr = ClientRect;
    dr.left += FHORZ.nPos;
    dr.right += FHORZ.nPos;
    dr.top += (FVERT.nPos+FDCProject->CalendarHeight);
    dr.bottom += FVERT.nPos;
    SetMapMode(DC, MM_ANISOTROPIC);
    SetBkMode(DC, TRANSPARENT);

    FDCProject->Calendar.DrawLine1 = true;
//    FDCProject->Calendar.DrawLine2 = true;
    SetViewportOrgEx(DC, -FHORZ.nPos, 0, NULL);
    FDCProject->Calendar.ShowDays = ShowDays;
    FDCProject->Calendar.Language = Language;
    FDCProject->DrawCalendar(DC, FHORZ.nPos, Width);

    SetViewportOrgEx(DC, -FHORZ.nPos, -FVERT.nPos, NULL);
    FDCProject->Draw(DC, dr);

    FDCProject->Calendar.DrawLine1 = false;
  //  FDCProject->Calendar.DrawLine2 = false;
    SetViewportOrgEx(DC, -FHORZ.nPos, 0, NULL);
    FDCProject->DrawCalendar(DC, FHORZ.nPos, Width);

    SetViewportOrgEx(DC, 0, 0, NULL);
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::WMPaint(Messages::TWMPaint &Message)
{
    ControlState << csCustomPaint;
    TWinControl::Dispatch(&Message);
    ControlState >> csCustomPaint;
}
//---------------------------------------------------------------------------
//double __fastcall TDoubleCode::GetZoomX()
//{
//  double NaType = 0;
//  switch(FDCProject->NavigationType)
//  {
//    case TCalendarDraw::gctDay:
//      NaType = 1;
//      break;
//    case TCalendarDraw::gct3Day: //三日
//      NaType = 3;
//      break;
//    case TCalendarDraw::gctWeek: //周
//      NaType = 7;
//      break;
//    case TCalendarDraw::gctMonth1: //月1
//      NaType = 30;
//      break;
//    case TCalendarDraw::gctMonth2: //月2
//      NaType = 60;
//      break;
//    case TCalendarDraw::gctQuarter: //季度
//      NaType = 90;
//      break;
//    case TCalendarDraw::gctHalfYear: //半年
//      NaType = 183;
//      break;
//  }
//  switch(FDCProject->Calendar.Type)
//  {
//    case TCalendarDraw::gct2Hour://二小时
//      NaType *= 12;//放大12倍
//      break;
//    case TCalendarDraw::gct6Hour://六小时
//      NaType *= 4;
//      break;
//    case TCalendarDraw::gctDay:
//      break;
//    case TCalendarDraw::gct3Day: //三日
//      NaType = NaType/3;
//      break;
//    case TCalendarDraw::gctWeek: //周
//      NaType = NaType/7;
//      break;
//    case TCalendarDraw::gctMonth1: //月1
//      NaType = NaType/30;
//      break;
//    case TCalendarDraw::gctMonth2: //月2
//      NaType = NaType/61;
//      break;
//    case TCalendarDraw::gctQuarter: //季度
//      NaType = NaType/91;
//      break;
//    case TCalendarDraw::gctHalfYear: //半年
//      NaType = NaType/183;
//      break;
//  }
//  return NaType;
//}
//---------------------------------------------------------------------------
//double __fastcall TDoubleCode::GetZoomY()
//{
//  return FDCProject->RowHeight / (double)FDCProject->NavigationRowHeight;
//}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::FindTaskByName(const String TaskName)
{
  TPoint *pt = FDCProject->FindTaskByName(TaskName);
  if(pt!=NULL)
  {
    AdjustOnFrameMove(pt->x-Width/2,pt->y-Height/2);
    if(NaviImage && NaviImage->Showing)
      NaviImage->SetFrameRect(FHORZ.nPos,FVERT.nPos);
    delete pt;
  }
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::AdjustOnFrameMove(int X, int Y)
{
//  X = ZoomX * X;
//  Y = ZoomY * Y;
//  Y += CalendarHeight;
  X = X > FHORZ.nMin ? X : FHORZ.nMin;
  X = X < FHORZ.nMax ? X : FHORZ.nMax;
  Y = Y > FVERT.nMin ? Y : FVERT.nMin;
  Y = Y < FVERT.nMax ? Y : FVERT.nMax;

  ScrollWindow(Handle, X - FHORZ.nPos , Y - FVERT.nPos , NULL, NULL);
//  UpdateWindow(Handle);
  SetScrollPos(Handle, SB_HORZ, X, true);
  SetScrollPos(Handle, SB_VERT, Y, true);
  FHORZ.nPos = X;
  FVERT.nPos = Y;
  this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::WMHScroll(Messages::TMessage &Message)
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
   // If the current position does not  change, do not scroll.
   xDelta = xNewPos - FHORZ.nPos;
   // Reset the current scroll position.
   FHORZ.nPos = xNewPos;
   ScrollWindow(Handle, -xDelta, 0, NULL, NULL);
   UpdateWindow(Handle);
   // Reset the scroll bar.
   SetScrollPos(Handle, SB_HORZ, xNewPos, true);

   if(NaviImage && NaviImage->Showing)
   {
     NaviImage->SetFrameRect(FHORZ.nPos,FVERT.nPos);
//     NaviImage->SetFrameRect(FHORZ.nPos/ZoomX,-1);
   }
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::WMVScroll(Messages::TMessage &Message)
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
   // Reset the current scroll position.
   FVERT.nPos = yNewPos;
   SetScrollPos(Handle, SB_VERT, yNewPos, true);
   // Reset the scroll bar.
   Invalidate();

   if(NaviImage && NaviImage->Showing)
   {
     NaviImage->SetFrameRect(FHORZ.nPos,FVERT.nPos);
//     NaviImage->SetFrameRect(-1,FVERT.nPos/ZoomY);
   }
}
//---------------------------------------------------------------------------
HDC TDoubleCode::GetDrawDc()
{
    HDC dc = GetDC(Handle);
    SetViewportOrgEx(dc, -FHORZ.nPos, -FVERT.nPos, NULL);
    return dc;
}
//---------------------------------------------------------------------------
void TDoubleCode::Draw(HDC dc, RECT dr)
{
    int ftsize=FTextFont->Size;
    int efsize=EventDraw->EventFont->Size;
    if(ftsize>1000 || ftsize<=0) ftsize = 9;
    if(efsize>1000 || efsize<=0) efsize = 9;

    FTextFont->Assign(Font);
    FTextFont->Size=ftsize;
    EventDraw->EventFont->Assign(Font);
    EventDraw->EventFont->Size=efsize;
    FDCProject->Calendar.DrawLine1 = true;
//    FDCProject->Calendar.DrawLine2 = true;
    FDCProject->Calendar.ShowDays = ShowDays;
    FDCProject->Calendar.Language = Language;
    if(!DrawingNavigation)
      FDCProject->DrawCalendar(dc, dr.left, dr.right - dr.left);
    dr.top += CalendarHeight;
    FDCProject->Draw(dc, dr);
    FDCProject->Calendar.DrawLine1 = false;
  //  FDCProject->Calendar.DrawLine2 = false;
    if(!DrawingNavigation)
      FDCProject->DrawCalendar(dc, dr.left, dr.right - dr.left);
}
//---------------------------------------------------------------------------
void TDoubleCode::DrawCalendar(HDC dc, int ALeft, int AWidth)
{
    FDCProject->Calendar.ShowDays = ShowDays;
    FDCProject->Calendar.Language = Language;
    FDCProject->DrawCalendar(dc, ALeft, AWidth);
}
//---------------------------------------------------------------------------
void TDoubleCode::AutoAlign()
{
    FDCProject->AutoAlign();
}
//---------------------------------------------------------------------------
void TDoubleCode::AdjustScrollBar()
{
    FHORZ.fMask = SIF_ALL;
    FHORZ.nMin = 0;
    FHORZ.nPage = 0;
    FHORZ.nMax = (FDCProject->Calendar.GetDayRight(FDCProject->Calendar.GetEndDay()) -
                  FDCProject->Calendar.GetDayLeft(FDCProject->Calendar.GetStartDay()))
                  - ClientRect.Width();
    FHORZ.nPos = FHORZ.nPos > FHORZ.nMax ? FHORZ.nMax : FHORZ.nPos;
    FHORZ.nPos = FHORZ.nPos > 0 ? FHORZ.nPos : 0;
    SetScrollInfo(Handle, SB_HORZ, &FHORZ, true);

    int MaxDCY(0);
    if(FDCProject->Project)
    {
         for(int i = 0; i < FDCProject->Project->Tasks.Count(); i++)
         {
             MaxDCY = MaxDCY < FDCProject->Project->Tasks[i]->DCY ?
                      FDCProject->Project->Tasks[i]->DCY : MaxDCY;
         }
    }
    FVERT.fMask = SIF_ALL;
    FVERT.nMin = 0;
    FVERT.nPage = 0;
    FVERT.nMax = FDCProject->RowHeight * (MaxDCY + 2) + FDCProject->CalendarHeight - ClientRect.Height();
    FVERT.nMax = FVERT.nMax - FVERT.nMax % FDCProject->RowHeight + FDCProject->RowHeight;
    FVERT.nPos = FVERT.nPos > FVERT.nMax ? FVERT.nMax : FVERT.nPos;
    FVERT.nPos = FVERT.nPos > 0 ? FVERT.nPos : 0;
    SetScrollInfo(Handle, SB_VERT, &FVERT, true);
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::Resize(void)
{
   if(NaviImage && NaviImage->Showing)
     NaviImage->SetFrameRect(this->ClientRect,FHORZ.nPos,FVERT.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::AdjustSize(void)
{
    TWinControl::AdjustSize();
    AdjustScrollBar();
    FDCProject->Calendar.ChartHeight = Height;
}
//---------------------------------------------------------------------------
TProject* __fastcall TDoubleCode::GetProject()
{
    return FDCProject->Project;
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::SetProject(TProject*AProject)
{
    Screen->Cursor = crHourGlass;
    FDCProject->Project = AProject;
    if(NaviImage && NaviImage->Showing)
    {
      ShowNavigation();
    }
    Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
int __fastcall TDoubleCode::GetCalendarHeight()
{
    return FDCProject->CalendarHeight;
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::SetCalendarHeight(int AHeight)
{
    FDCProject->CalendarHeight = AHeight;
}
//---------------------------------------------------------------------------
int __fastcall TDoubleCode::GetRowHeight()
{
    return FDCProject->RowHeight;
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::SetRowHeight(int AHeight)
{
    FDCProject->RowHeight = AHeight;
}
//---------------------------------------------------------------------------
TEventDraw*   TDoubleCode::GetEventDraw()
{
    return &(FDCProject->EventDraw);
}
//---------------------------------------------------------------------------
TTaskLine*    TDoubleCode::GetCriticalDraw()
{
    return &(FDCProject->CriticalDraw);
}
//---------------------------------------------------------------------------
TTaskLine*    TDoubleCode::GetTaskDraw()
{
    return &(FDCProject->TaskDraw);
}
//---------------------------------------------------------------------------
TVirtualLine* TDoubleCode::GetCriticalVirtualDraw()
{
    return &(FDCProject->CriticalVirtualDraw);
}
//---------------------------------------------------------------------------
TVirtualLine* TDoubleCode::GetVirtualDraw()
{
    return &(FDCProject->VirtualDraw);
}
//---------------------------------------------------------------------------
TCalendarDraw* TDoubleCode::GetCalendarDraw()
{
    return &(FDCProject->Calendar);
}
//---------------------------------------------------------------------------
TTaskShowString* __fastcall TDoubleCode::GetTopShowString()
{
    return &(FDCProject->TopShowString);
}
//---------------------------------------------------------------------------
TTaskShowString* __fastcall TDoubleCode::GetBottomShowString()
{
    return &(FDCProject->BottomShowString);
}
//---------------------------------------------------------------------------
void TDoubleCode::SetDefault()
{
    TopShowString->SetDefineString("[名称]");
    BottomShowString->SetDefineString("[计划工期]天");

    VirtualDraw->Style = lsSmallDot;
    VirtualDraw->Color = clBlack;
    CriticalVirtualDraw->Style = lsSmallDot;
    CriticalVirtualDraw->Color = clRed;
    CriticalDraw->Color = clRed;
    CriticalDraw->Style = lsBigSolid;
    TaskDraw->Color = clGreen;
    TaskDraw->Style = lsBigSolid;
    CalendarDraw->BackColor = clSkyBlue;
    CalendarDraw->FontColor = clBlack;
    FDCProject->RowHeight = 60;
    FAllowOverlap = false;
    FTextFont->Assign(Font);
    EventDraw->EventFont->Assign(Font);
    FTextFont->Size = 9;
    EventDraw->EventFont->Size = 9;
    ShowDays = false;
    Language = 0;
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   TWinControl::MouseDown(Button, Shift, X, Y);
   if(FDblClickAdjust)
   {
      FDblClickAdjust = false;
      return;
   }
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FDCProject->MouseDown(Button, Shift, X+FHORZ.nPos, Y+FVERT.nPos);
   SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
   TWinControl::MouseMove(Shift, X, Y);
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FDCProject->MouseMove(Shift, X+FHORZ.nPos, Y+FVERT.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   TWinControl::MouseUp(Button, Shift, X, Y);
   GetScrollInfo(Handle, SB_VERT, &FVERT);
   GetScrollInfo(Handle, SB_HORZ, &FHORZ);
   FDCProject->MouseUp(Button, Shift, X+FHORZ.nPos, Y+FVERT.nPos);
}
//---------------------------------------------------------------------------
void __fastcall TDoubleCode::WMDblClick(Messages::TMessage &Message)
{
   TWinControl::Dispatch(&Message);
   FDCProject->FDraging = false;
   TPoint point;
   if(GetCursorPos(&point))
   {
	 point = ScreenToClient(point);
     point.x = point.x+FHORZ.nPos;
     point.y = point.y+FVERT.nPos;
     FDCProject->Project->Selected = FDCProject->TaskFromPoint(point.x,point.y);
   }
   if(FOnTaskDblClick && FDCProject->Project->Selected)
      FOnTaskDblClick(FDCProject->Project, FDCProject->Project->Selected);
}
//---------------------------------------------------------------------------
TPrintHandle __fastcall TDoubleCode::GetPrintHandle()
{
    if(FPrintHandle)
    {
    }else
    {
        FPrintHandle = new TDoubleCodePrint(this);
    }
    return FPrintHandle;
}
//---------------------------------------------------------------------------
int __fastcall TDoubleCode::GetTotalHeight()
{
    int MaxDCY(0);
    int ADCY;
    for(int i = 0; i < FDCProject->Project->Tasks.Count(); i++)
    {
        ADCY = FDCProject->Project->Tasks[i]->DCY;
        if(ADCY > MaxDCY)
            MaxDCY = ADCY;
    }
    return CalendarHeight + (MaxDCY+2) * RowHeight;
}
//---------------------------------------------------------------------------
int __fastcall TDoubleCode::GetTotalWidth()
{
    return CalendarDraw->GetDayRight(FDCProject->Project->EndDate + 6);
}
//---------------------------------------------------------------------------
//void __fastcall TDoubleCode::ShowNavigation()
//{
//  if(!NaviImage->Showing) return;
//  NaviImage->OnFrameMove = NULL;
//  //  NaviImage->Align = alTop;
//  //  NaviImage->Height = 200;
//  NaviImage->ShowNavigationPicture(this);//  NaviImage->ShowNavigationImage(this);
//  double zx = ZoomX;
//  double zy = ZoomY;
//  NaviImage->ZoomX = zx;
//  NaviImage->ZoomY = zy;
//  TRect r;
//  r.left   = FHORZ.nPos / zx;
//  r.top    = FVERT.nPos / zy;
//  zx = GetTotalWidth() / (double)FDCProject->NavigationImageSize.cx;
//  zy = (GetTotalHeight() - CalendarHeight) / (double)FDCProject->NavigationImageSize.cy;
//  if(zx<1) zx = 1;
//  if(zy<1) zy = 1;
//  r.right  = (FHORZ.nPos + Width) / zx;
//  r.bottom = (FVERT.nPos + Height - CalendarHeight) / zy;
//  //  NaviImage->SetFrameRect(r);
//  NaviImage->OnFrameMove = AdjustOnFrameMove;
//  NaviImage->Invalidate();
//}
void __fastcall TDoubleCode::ShowNavigation()
{
  if(!NaviImage || !NaviImage->Showing) return;
  
  NaviImage->OnFrameMove = NULL;
  DrawingNavigation = true;
  NaviImage->ShowNavigationPicture(this);
  DrawingNavigation = false;
  NaviImage->SetFrameRect(this->ClientRect,FHORZ.nPos,FVERT.nPos);
  NaviImage->OnFrameMove = AdjustOnFrameMove;
}
void __fastcall TDoubleCode::SetOldProjectTaskID(String str)
{
  FDCProject->oldProjectTaskID = str;
}
//---------------------------------------------------------------------------


