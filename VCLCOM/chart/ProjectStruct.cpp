//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <ComObj.hpp>
#include <StrUtils.hpp>
#include "ProjectStruct.h"
#pragma package(smart_init)
namespace ProjectStruct
{

//------------------------------------------------------------------------------
struct TProjectChangeNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TProjectChangeNotify(TPointerArray<TPrjDataChangeLink>& ALink)
                        : FLink(ALink)
    {
       for(int i = 0; i < FLink.Count(); i++)
	   {
          FLink[i].BeforeProjectChange();
       }
    }
    ~TProjectChangeNotify()
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].AfterProjectChange();
       }
    }
};
//------------------------------------------------------------------------------
struct TTaskChangeNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TTask* FTask;
    TTaskChangeNotify(TPointerArray<TPrjDataChangeLink>& ALink, TTask*ATask)
                        : FLink(ALink)
    {
       FTask = ATask;
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].BeforeTaskChange(FTask);
       }
    }
    ~TTaskChangeNotify()
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].AfterTaskChange(FTask);
       }
    }
};
//------------------------------------------------------------------------------
struct TTaskDeleteNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TPrjObject* FTask;
    TTaskDeleteNotify(TPointerArray<TPrjDataChangeLink>& ALink, TPrjObject*ATask)
                        : FLink(ALink)
    {
       FTask = ATask;
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].BeforeTaskDelete(FTask);
       }
    }
    ~TTaskDeleteNotify()
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].AfterTaskDelete();
       }
    }
};
//------------------------------------------------------------------------------
struct TTaskAddNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TPrjObject*  FTask;
    TTaskAddNotify(TPointerArray<TPrjDataChangeLink>& ALink)
                        : FLink(ALink)
    {
       FTask = NULL;
    }
    void SetTask(TPrjObject*ATask)
    {
       FTask = ATask;
    }
    ~TTaskAddNotify()
    {
       if(!FTask)
           throw Exception("在TTaskAddNotify中程序错误，没有设定任务");
       for(int i = 0; i < FLink.Count(); i++)
       {
           FLink[i].AfterTaskAdd(FTask);
       }
    }
};
//------------------------------------------------------------------------------
struct TTaskLinkChangeNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TTaskLink* FTaskLink;
    TTaskLinkChangeNotify(TPointerArray<TPrjDataChangeLink>& ALink, TTaskLink*ATaskLink)
                        : FLink(ALink)
    {
       FTaskLink = ATaskLink;
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].BeforeTaskLinkChange(FTaskLink);
       }
    }
    ~TTaskLinkChangeNotify()
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].AfterTaskLinkChange(FTaskLink);
       }
    }
};
//------------------------------------------------------------------------------
struct TTaskLinkDeleteNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TTaskLink* FTaskLink;
    TTaskLinkDeleteNotify(TPointerArray<TPrjDataChangeLink>& ALink, TTaskLink*ATaskLink)
                        : FLink(ALink)
    {
       FTaskLink = ATaskLink;
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].BeforeTaskLinkDelete(FTaskLink);
       }
    }
};
//------------------------------------------------------------------------------
struct TTaskLinkAddNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TTaskLink* FTaskLink;
    TTaskLinkAddNotify(TPointerArray<TPrjDataChangeLink>& ALink)
                        : FLink(ALink)
    {
    }
    void SetTaskLink(TTaskLink*ATaskLink)
    {
       FTaskLink = ATaskLink;
    }
    ~TTaskLinkAddNotify()
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].AfterTaskLinkAdd(FTaskLink);
       }
    }
};
//------------------------------------------------------------------------------
struct TUpdateNotify
{
    TPointerArray<TPrjDataChangeLink>& FLink;
    TUpdateNotify(TPointerArray<TPrjDataChangeLink>& ALink)
                        : FLink(ALink)
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].BeginUpdate();
       }
    }
    ~TUpdateNotify()
    {
       for(int i = 0; i < FLink.Count(); i++)
       {
          FLink[i].EndUpdate();
       }
	}
};
String GetPlanTypeName(int plantype)
{
  switch((TPlanType)plantype)
  {
    case ptASAP :
	  return "越早越好";
    case ptALAP:
      return "越晚越好";
    case ptMSO:
      return "必须开始于";
    case ptMFO:
      return "必须完成于";
    case ptBSO:
      return "不得晚于...开始";
    case ptBFO:
      return "不得晚于...完成";
    case ptASO:
      return "不得早于...开始";
    case ptAFO:
	  return "不得早于...完成";
  }
  return "未定义";
}
//------------------------------------------------------------------------------
//TTaskData
//------------------------------------------------------------------------------
bool TTaskData::ReadingData = false;
bool TTaskData::Moving =  false;
TTaskData::TTaskData()
{
    InitData();
    SetIsNew(true);
}
//------------------------------------------------------------------------------
TTaskData& TTaskData::operator=(TTaskData&AObj)
{
    if(this == &AObj)
        return *this;

    LimitedDate = AObj.LimitedDate;
    LimitedEndDate = AObj.LimitedEndDate;
	Desc = AObj.Desc;//任务描述
	FactCostDays = AObj.FactCostDays;//实际工期
	WorkLoad = AObj.WorkLoad;//计划工程量
	FactWorkLoad = AObj.FactWorkLoad;//实际工程量
    EnvaluedWorkLoad = AObj.EnvaluedWorkLoad;
	Invest = AObj.Invest;//计划产值
	FactInvest = AObj.FactInvest;//实际产值
    EnvaluedInvest = AObj.EnvaluedInvest;
	MileStone = AObj.MileStone;//里程碑标识	0-非里程碑	1-里程碑
	AnticipateCostDays = AObj.AnticipateCostDays;//乐观工期
	OptimismCostDays = AObj.OptimismCostDays;//预期工期
	PessimismCostDays = AObj.PessimismCostDays;//悲观工期
	RiskProbability = AObj.RiskProbability;//风险概率
	RiskQty = AObj.RiskQty;//风险量
	RiskLoss = AObj.RiskLoss;//风险损失
	ProcessDate = AObj.ProcessDate;//进度截止日期
    TaskStatus = AObj.TaskStatus;
    ForeignID = AObj.ForeignID;       //外部项目号
    ForeignChangeFlag = AObj.ForeignChangeFlag; //外部变化标识 0-无，1-有
    PlanAdjFlag = AObj.PlanAdjFlag;       //计划调整标识
	WBS = AObj.WBS;
    WorkLoadType = AObj.WorkLoadType;

    Code = AObj.Code;
	TaskID = AObj.TaskID;
	PrjCode = AObj.PrjCode;
    SmartCode = AObj.SmartCode;
    Name = AObj.Name;
    CostDays = AObj.CostDays;
    StartDate = AObj.StartDate;
    EndDate = AObj.EndDate;
    ALAP_StartDate = AObj.ALAP_StartDate;
    ALAP_EndDate = AObj.ALAP_EndDate;
    ASAP_StartDate = AObj.ASAP_StartDate;
    ASAP_EndDate = AObj.ASAP_EndDate;
    FactStartDate = AObj.FactStartDate;
    FactEndDate = AObj.FactEndDate;
    Index = AObj.Index;
	PlanType = AObj.PlanType;
	Critical = AObj.Critical;

    VitalLevel = AObj.VitalLevel;
    Personnel = AObj.Personnel;
    Proportion = AObj.Proportion;
    TotalDiff = AObj.TotalDiff;
    FreeDays = AObj.FreeDays;
	PctType  = AObj.PctType;     //任务完成百分比计算类型
    TaskPctPercent  =AObj.TaskPctPercent ;  //任务完成百分比
    TaskDtnType  =AObj.TaskDtnType;  // 工期类型
    PertStartTime  = AObj.PertStartTime;   //期望开始时间
	PertStartQ  = AObj.PertStartQ;
    PertEndTime  = AObj.PertEndTime;    //期望结束时间
    PertEndQ  = AObj.PertEndQ;
    BStartDate = AObj.BStartDate;
    BEndDate = AObj.BEndDate;
    BCostDays = AObj.BCostDays;
    return *this;
}
//------------------------------------------------------------------------------
void TTaskData::InitData()
{
   // checkCopyRight();
	FDesc = "";//任务描述
	FTaskPctPercent=0;    //任务完成百分比%,由下面类型决定。
    FPctType=taptDurtion;          //任务完成百分比计算依据，0-工期，1-数量，2-输入
    FTaskDtnType=tdtUnit;  //工期类型

	FFactCostDays = 0;//实际工期
	FWorkLoad = 0;//计划工程量
	FFactWorkLoad = 0;//实际工程量
    FEnvaluedWorkLoad = 0;

	FInvest = 0;//计划产值
	FFactInvest = 0;//实际产值
    FEnvaluedInvest = 0;
	FMileStone = false;//里程碑标识		0-非里程碑	1-里程碑
	FAnticipateCostDays = 0;//乐观工期
	FOptimismCostDays = 0;//预期工期
	FPessimismCostDays = 0;//悲观工期
	FRiskProbability = 0;//风险概率
	FRiskQty = 0;//风险量
	FRiskLoss = 0;//风险损失
	FProcessDate = 0;//进度截止日期
    FTaskStatus = tsNotStart;
	FLimitedDate = 0;
    FLimitedEndDate = 0;
    FWBS = "";
    FWorkLoadType = 0;

    FTaskType = 1;          //任务类型 1-常规，2-组，3-外部工程
	FForeignID = "";       //外部项目号
    FForeignChangeFlag = 0; //外部变化标识 0-无，1-有
    FPlanAdjFlag = 0;       //计划调整标识

    FCode = "";//任务编号
    FTaskID="";//任务ID
    FSmartCode = "000000000000000000000000000000";  //公路版起止桩号
    FName = "";
	FCostDays = 1;    //默认值给1
    FStartDate = 0;
    FEndDate = 0;
    FALAP_StartDate = 0;
    FALAP_EndDate = 0;
    FASAP_StartDate = 0;
    FASAP_EndDate = 0;
    FFF_StartDate = 0;
    FFF_EndDate = 0;
    FFactStartDate = 0;
    FFactEndDate = 0;
	FIndex = 0;
    FPlanType = ptASAP;
    FCritical = false;
    FProportion = 100;
    FVitalLevel = 0;
    FPersonnel = "";
    FTotalDiff = 0;
    FFreeDays = 0;
    FStopFlag = 0;
    FPertStartTime = 0;
    FPertStartQ = 0;
    FPertEndTime = 0;
    FPertEndQ = 0;
    FBCostDays = 0;
    FBEndDate = 0;
    FBStartDate = 0;
    FTempStartQ=0;
    FTempEndQ=0;
    FBCWS=0;
    FBCWP=0;
    FCheckItem = false;
}
//------------------------------------------------------------------------------
bool __fastcall TTaskData::GetIsNew()
{
    return FEditStatus & esNew;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetIsNew(bool Value)
{
    if(Value)
        FEditStatus = TEditStatus(FEditStatus | esNew);
    else
        FEditStatus = TEditStatus(FEditStatus & (~esNew));
}
//------------------------------------------------------------------------------
bool __fastcall TTaskData::GetIsModified()
{
    return FEditStatus & esModified;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetIsModified(bool Value)
{
    if(Value)
        FEditStatus = TEditStatus(FEditStatus | esModified);
    else
        FEditStatus = TEditStatus(FEditStatus & (~esModified));
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetDesc(String Value)
{
    CompareSetValue(FDesc, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetFactCostDays(double Value)
{
   TPrjObject* This=(TPrjObject*)(this);
   if(FPctType=taptDurtion&&CostDays>0)
	{
		 if(TaskStatus!=tsNotStart)
		   This->TaskPctPercent=Value/CostDays*100.00;
		   //FTaskPctPercent=Value/CostDays*100.00;
		 if(TaskStatus==tsOvered)
			This->TaskPctPercent=100;
			//FTaskPctPercent=100;
	}
	if(CompareSetValue(FFactCostDays, Value))
	{
        TPrjObject* ThisParent = This->Parent();
        if(ThisParent!=NULL)
        ThisParent->SumFactCostDays();
        if(This->GetType()==ttTask)
        {
           BCWS=CalBCWS();
           BCWP=CalBCWP();
        }
    }
}
//------------------------------------------------------------------------------

void TTaskData::SumFactCostDays()
{

  TPrjObject* This = ((TPrjObject*)(this));

  TDateTime dStart = 0;
  TDateTime dEnd   = 0;
  String sDate = "";
  int fcostdays=0;
  if(This->ChildCount()>0)
  {
   if(This->TaskStatus==tsStarted)
   {
	  dStart=This->FactStartDate;
	  dEnd=This->ProcessDate;
   }
   else if (This->TaskStatus==tsOvered)
   {
	  dStart=This->FactStartDate;
	  dEnd=This->FactEndDate;
   }
   for(TDateTime i = dStart; i <= dEnd; i++)
   {
		if(This->Calendar->IsWorkDay(i))
		{
		  fcostdays++;
		}
	}
	This->FactCostDays =fcostdays;
  /*  TStringList *DateList = new TStringList();    zws20091225不需要分析子任务

    try
    {
	  for(int i = 0; i < This->ChildCount(); i++)
	  {
		if(double(This->GetChild(i).ProcessDate) > 5)
        {
		  dStart = This->GetChild(i).FactStartDate;
		  if(this->TaskStatus==tsOvered)
			 dEnd = This->GetChild(i).FactEndDate;
		  else
			 dEnd = This->GetChild(i).ProcessDate;
		   if(int(dStart)<5)
			  break;
		   for(TDateTime i = dStart; i <= dEnd; i++)
			if(This->Calendar->IsWorkDay(i) )
			{
			  sDate = i.DateString();
			  if(DateList->IndexOf(sDate)==-1)
				DateList->Add(sDate);
			}
        }
	  }
      This->FactCostDays = DateList->Count;
    }
    __finally
    {
      delete DateList;
	}  */
  }
  else
	This->FactCostDays = 0;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetVitalLevel(int ivalue)
{
  CompareSetValue(FVitalLevel,ivalue);
}
void __fastcall TTaskData::SetProportion(double dProportion)
{
  CompareSetValue(FProportion,dProportion);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetWorkLoad(double Value)
{

	if(CompareSetValue(FWorkLoad, Value))
	{
		 //设置是否已完工
 /*		 if(Value > 0 && FactWorkLoad > 0 && this->TaskStatus != tsOvered && this->TaskStatus != tsPaused ) //实际工程量大于零，自动设置开工
		 {
		 if(FactWorkLoad >=WorkLoad)
			  {
				   TPrjObject* This=(TPrjObject*)(this);
				   if(This->GetType()==ttProject)
					 TaskStatus = tsStarted;
				   else
					 TaskStatus = tsOvered;
			  }else
			  {
				   TaskStatus = tsStarted;
			  }
		 } */
	  TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
          if(ThisParent!=NULL)
	  ThisParent->SumWorkLoad();
	}
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void TTaskData::SumWorkLoad()
{
return;//不汇总
	 TPrjObject* This = ((TPrjObject*)(this));
	 //汇总
	 double Sum(0);
	 for(int i = 0; i < This->ChildCount(); i++)
	 {
	   TPrjObject& AChild = This->GetChild(i);
	   Sum += AChild.WorkLoad;

	 }
       This->WorkLoad = Sum;

}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetFactWorkLoad(double Value)
{
		TPrjObject* This=(TPrjObject*)(this);
		if(FPctType=taptWorkLoad&&WorkLoad>0)
		{
		  if(TaskStatus!=tsNotStart)
		   This->TaskPctPercent=Value/WorkLoad*100.00;
		   //FTaskPctPercent=Value/WorkLoad*100.00;
		  if(TaskStatus==tsOvered)
			This->TaskPctPercent=100;
			//FTaskPctPercent=100;
		}

	if(CompareSetValue(FFactWorkLoad,Value))
	{
		TPrjObject* ThisParent = This->Parent();
		 //设置是否已完工
   /*      if(Value > 0 && WorkLoad>0 && this->TaskStatus != tsOvered && this->TaskStatus != tsPaused ) //实际工程量大于零，自动设置开工
		 {
			if((1-FactWorkLoad/WorkLoad)*100.0<ThisParent->Project()->StatError)
			 {
				  if(This->GetType()==ttProject)
					 TaskStatus = tsStarted;
				   else
					 TaskStatus = tsOvered;
			  }else
			  {
				   TaskStatus = tsStarted;
			  }
	 }  */
		ThisParent->SumFactWorkLoad();
   }
		if(This->GetType()==ttTask)
		{
		   BCWS=CalBCWS();
		   BCWP=CalBCWP();
		}

}

//------------------------------------------------------------------------------
void TTaskData::SumFactWorkLoad()
{
return;//不汇总
     TPrjObject* This = ((TPrjObject*)(this));
	 //汇总实际进度
	 double Sum(0);
	 for(int i = 0; i < This->ChildCount(); i++)
	 {
	   TPrjObject& AChild = This->GetChild(i);
	   Sum += AChild.FactWorkLoad ;
	 }
         This->FactWorkLoad=Sum;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetEnvaluedWorkLoad(double Value)
{
	if(CompareSetValue(FEnvaluedWorkLoad, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		 ThisParent->SumEnvaluedWorkLoad();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumEnvaluedWorkLoad()
{
return;//不汇总
    TPrjObject* This = ((TPrjObject*)(this));
	double Sum(0);
	for(int i = 0; i < This->ChildCount(); i++)
    {
		Sum += This->GetChild(i).EnvaluedWorkLoad ;
	}
    This->EnvaluedWorkLoad =  Sum ;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetInvest(double Value)
{
   TPrjObject* This = ((TPrjObject*)(this));
	 if(This->GetType()==ttTask)
	  {
		BCWP=CalBCWP();
		BCWS=CalBCWS();
	  }

	if(CompareSetValue(FInvest, Value))
    {
		  TPrjObject* ThisParent = This->Parent();
		  ThisParent->SumInvest();
	}
}
//------------------------------------------------------------------------------
void TTaskData::SumInvest()
{
return;//不汇总
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
          Sum += This->GetChild(i).Invest;
     This->Invest = Sum;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetFactInvest(double Value)
{
    if(CompareSetValue(FFactInvest, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
	     ThisParent->SumFactInvest();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumFactInvest()
{
return;//不汇总
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
          Sum += This->GetChild(i).FactInvest;
     This->FactInvest = Sum;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetEnvaluedInvest(double Value)
{
    if(CompareSetValue(FEnvaluedInvest, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		ThisParent->SumEnvaluedInvest();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumEnvaluedInvest()
{
return;//不汇总
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
          Sum += This->GetChild(i).EnvaluedInvest;
     This->EnvaluedInvest = Sum;
}
//------------------------------------------------------------------------------
double __fastcall TTaskData::CalBCWS()
{
//假设成本是按工期平均分配的，所以在任务的划分上要求合理，如果一道工序安装设备
      // 譬如购买并安装一个大型设备。也许，只专总工作量的1%的设备购买成本，可能占作业总成本的99%。
//如果购买要花1天，安装要化99天，如果在第100天之前，来计算该作业的CPI，则总是小于1的
//所以象这种把任务划分成两步，一步购买设备，一步安装设备，就比较合理
    if(FCostDays==0)
     return 0;
        else
	  return Invest*FFactCostDays/FCostDays;
}
void  __fastcall TTaskData::SetBCWS(double Value)
{
  if(CompareSetValue(FBCWS, Value))
  {
    TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		ThisParent->SumBCWS();
  }
}
void TTaskData::SumBCWS()
{
 return;
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
          Sum += This->GetChild(i).BCWS;
     This->BCWS = Sum;
}
void __fastcall TTaskData::SetBCWP(double Value)
{
  CompareSetValue(FBCWP, Value);
}
//------------------------------------------------------------------------------
double __fastcall TTaskData::GetACWP()
{
 return FactInvest;

}
//------------------------------------------------------------------------------
double __fastcall TTaskData::CalBCWP()
{
  return Invest*FTaskPctPercent/100.00;
}
//------------------------------------------------------------------------------
double __fastcall TTaskData::GetCV()
{
        return BCWP-ACWP;
}
//------------------------------------------------------------------------------
double __fastcall TTaskData::GetSV()
{
        return BCWP-BCWS;
}
//------------------------------------------------------------------------------
double __fastcall TTaskData::GetCPI()
{
       if(ACWP!=0)
          return BCWP/ACWP;
       else
		  return 1;
}
//------------------------------------------------------------------------------
double __fastcall TTaskData::GetSPI()
{
        if(BCWS!=0)
           return BCWP/BCWS;
        else
		   return 1;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetMileStone(bool Value)
{
	if(Value)    //zws20080712
	{
	  TPrjObject* This = ((TPrjObject*)(this));
	  if(This->TaskType!=ttTask)  //如果不是任务组，则要求下级子节点都是里程碑
		  {
		  for(int i=0;i<This->ChildCount();i++)
		  {
			if(!This->GetChild(i).MileStone)
			  throw Exception("非普通任务又有子节点,要求下级子节点都是里程碑，否则不能设为里程碑");
		  }
		  }
		}
	CompareSetValue(FMileStone, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetAnticipateCostDays(double Value)
{
    if(CompareSetValue(FAnticipateCostDays, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		ThisParent->SumAnticipateCostDays();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumAnticipateCostDays()
{
  return;//zws20090502
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
		  Sum += This->GetChild(i).AnticipateCostDays;
     This->AnticipateCostDays = Sum;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetOptimismCostDays(double Value)
{
	if(CompareSetValue(FOptimismCostDays, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		 ThisParent->SumOptimismCostDays();
	}
}
//------------------------------------------------------------------------------
void TTaskData::SumOptimismCostDays()
{
  return;//zws20090502
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
          Sum += This->GetChild(i).OptimismCostDays;
     This->OptimismCostDays = Sum;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPessimismCostDays(double Value)
{
    if(CompareSetValue(FPessimismCostDays, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		 ThisParent->SumPessimismCostDays();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumPessimismCostDays()
{
  return;//zws20090502
     TPrjObject* This = ((TPrjObject*)(this));
     double Sum(0);
     for(int i = 0; i < This->ChildCount(); i++)
          Sum += This->GetChild(i).PessimismCostDays;
     This->PessimismCostDays = Sum;
}
//------------------------------------------------------------------------------
double  __fastcall TTaskData::GetPertDuration()
{
   TPrjObject* This = ((TPrjObject*)(this));
   if(This->GetType()==ttTask)
    return (FOptimismCostDays + 4*FAnticipateCostDays + FPessimismCostDays)/6.0;
   else
      return PertEndTime-PertStartTime;
}
//------------------------------------------------------------------------------
double  __fastcall TTaskData::GetPertDurationQ()
{
   TPrjObject* This = ((TPrjObject*)(this));
    if(This->GetType()==ttTask)
      return (FPessimismCostDays-FOptimismCostDays)*(FPessimismCostDays-FOptimismCostDays)/36.0;
    else
      return PertEndQ-PertStartQ;
}
void __fastcall TTaskData::SetPertStartTime(double value)
{
        if(CompareSetValue(FPertStartTime, value))
        {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		 ThisParent->SumPertStartTime();
        }
}
//------------------------------------------------------------------------------

void TTaskData::SumPertStartTime()
{
     TPrjObject* This = ((TPrjObject*)(this));
     double MinStartTime(0),SQ(0);
    if(This->ChildCount() > 0)
     {
         MinStartTime=This->GetChild(0).PertStartTime;
         SQ=This->GetChild(0).PertStartQ;
         for(int i = 1; i < This->ChildCount(); i++)
         {
          if(MinStartTime>=This->GetChild(i).PertStartTime)
          {
           MinStartTime=This->GetChild(i).PertStartTime;
           SQ=This->GetChild(i).PertStartQ;
          }
        }
     }
     This->PertStartQ=SQ;
     This->PertStartTime = MinStartTime;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPertStartQ(double value)
{
        CompareSetValue(FPertStartQ , value) ;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPertEndTime(double value)
{
        if(CompareSetValue(FPertEndTime , value))
        {
		      TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		      ThisParent->SumPertEndTime();
        }
}
//------------------------------------------------------------------------------
void TTaskData::SumPertEndTime()
{
     TPrjObject* This = ((TPrjObject*)(this));
     double MaxEndTime(0),EQ(0);
     for(int i = 0; i < This->ChildCount(); i++)
     {
       if(MaxEndTime<=This->GetChild(i).PertEndTime)
       {
         MaxEndTime=This->GetChild(i).PertEndTime;
         EQ=This->GetChild(i).PertEndQ;
       }
     }
     This->PertEndQ=EQ;
     This->PertEndTime = MaxEndTime;

}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPertEndQ(double value)
{
       CompareSetValue(FPertEndQ , value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetRiskProbability(double Value)
{
    CompareSetValue(FRiskProbability, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetRiskQty(double Value)
{
    CompareSetValue(FRiskQty, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPctType(TTaskPctType value)
{
		CompareSetValue(FPctType, value);
}
void __fastcall TTaskData::SetTaskPctPercent(double Value)
{
   if(CompareSetValue(FTaskPctPercent, Value))
   {
		TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		ThisParent->SumPctPercent();
   }
}
//------------------------------------------------------------------------------
void TTaskData::SumPctPercent()
{
	TPrjObject* This = ((TPrjObject*)(this));
	double SumProportion=0,SumPercent=0;
	for(int i = 0; i < This->ChildCount(); i++)
	{
		SumProportion += This->GetChild(i).Proportion;
		SumPercent += This->GetChild(i).TaskPctPercent * This->GetChild(i).Proportion;
	}
	if(SumProportion > 0.00001)
	{
		This->TaskPctPercent =  SumPercent/SumProportion;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetRiskLoss(double Value)
{
    CompareSetValue(FRiskLoss, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetProcessDate(TDateTime Value)
{
    if(CompareSetValue(FProcessDate, Value))
    {
		 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
		ThisParent->SumProcessDate();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumProcessDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     TDateTime MaxEnd = 0;
     for(int i = 0; i < This->ChildCount(); i++)
         if(double(This->GetChild(i).ProcessDate) > 5)
              MaxEnd = MaxEnd > This->GetChild(i).ProcessDate ?
                       MaxEnd : This->GetChild(i).ProcessDate;
     This->ProcessDate = MaxEnd;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetTaskStatus(TTaskStatus Value)
{
	if(CompareSetValue(FTaskStatus, Value))
    {
	 TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
	 if(ThisParent)
	 {
		ThisParent->SumTaskStatus();

        TPrjObject* This = ((TPrjObject*)(this));
        for(int i = 0; i < This->LateTaskCount; i++)
        {
             TTask* ALate = This->LateTasks[i]->Task;
             if(ALate->MileStone)
             {
                  ALate->SumMileStone();
             }
        }
    }
   }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetWBS(String AWBS)
{
  bool bEqual = (FWBS==AWBS);
  CompareSetValue(FWBS, AWBS);

  if(!bEqual)
  {
    TPrjObject *task = dynamic_cast<TPrjObject *>(this);
    if(task!=NULL)
    {
      if(!task->Project()->ReadingData && !task->Project()->UsePCWBS)
        task->BuildChildWBS();
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetFreeDays(double Value)
{
  if(CompareSetValue(FFreeDays, Value))
  {
	TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
	 if(ThisParent)
	 {
		ThisParent->SumFreeDays();
	 }
  }
}
//------------------------------------------------------------------------------
void TTaskData::SumFreeDays()
{
  TPrjObject* This = ((TPrjObject*)(this));
  int minfreedays=This->TotalDiff;         //zws2010-02-06任务组自由时差设为等于总时差
 /* TDateTime dMaxASAPEnd= This->ASAP_EndDate;
  for(int i = 0; i < This->ChildCount(); i++)
  {
	 if(dMaxASAPEnd==This->GetChild(i).ASAP_EndDate)
	 {
		 if(minfreedays>This->GetChild(i).FreeDays)
			minfreedays=This->GetChild(i).FreeDays;
	 }
  }  */
  This->FreeDays=minfreedays;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetTotalDiff(double Value)
{
  CompareSetValue(FTotalDiff, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetWorkLoadType(int Value)
{
	CompareSetValue(FWorkLoadType, Value);
}
//------------------------------------------------------------------------------
void TTaskData::SumTaskStatus()
{
     TPrjObject* This = ((TPrjObject*)(this));
     TPrjObject * AChild;
     /*
       如果当前任务设置为未开工，判断上层对象的子任务是否
       全部为开工，若是，设置其上层为为开工
     */
     bool Started(false);
     bool AllOvered(true);
     for(int i=0; i < This->ChildCount(); i++)
     {
         AChild = &(This->Childs[i]);
         if(AChild->TaskStatus != tsNotStart)
         {
             Started = true;
         }
         if(AChild->TaskStatus != tsOvered)
         {
             AllOvered = false;
         }
     }
     if(AllOvered && This->ChildCount()>0)
     {
         if(This->GetType()==ttProject)
           TaskStatus = tsStarted;
         else
           TaskStatus = tsOvered;
      }
     else if(Started)
         This->TaskStatus = tsStarted;
     else
         This->TaskStatus = tsNotStart;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetTaskType(TTaskType Value)
{
	CompareSetValue(FTaskType, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetGroupID(String Value)
{
    CompareSetValue(FGroupCode, Value);     //不起作用
}
//------------------------------------------------------------------------------
String __fastcall TTaskData::GetGroupID()
{
    TPrjObject* This = ((TPrjObject*)(this));
	if(This->Parent() && This->Parent()->GetType() != ttProject)
        return ((TPrjObject*)(this))->Parent()->TaskID;
    return "";
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetForeignID(String Value)
{
    CompareSetValue(FForeignID, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetForeignChangeFlag(int Value)
{
    CompareSetValue(FForeignChangeFlag, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPlanAdjFlag(int Value)
{
    CompareSetValue(FPlanAdjFlag, Value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPrjCode(String value)
{
   CompareSetValue(FPrjCode, value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetCode(String ACode)
{
    CompareSetValue(FCode, ACode);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetTaskID(String value)
{
    CompareSetValue(FTaskID, value);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetSmartCode(String ACode)
{
    CompareSetValue(FSmartCode, ACode);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetName(String AName)
{
    CompareSetValue(FName, AName);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetIndex(int AIndex)
{
//    CompareSetValue(FIndex, AIndex);
    FIndex = AIndex;
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetCostDays(double ACostDays)
{
   if(CompareSetValue(FCostDays, ACostDays))
   {
     TPrjObject* This=(TPrjObject*)(this);
     TPrjObject* ThisParent = This->Parent();
     if(ThisParent!=NULL)
     ThisParent->SumCostDays();
     if(This->GetType()==ttTask)
         BCWS=CalBCWS();
   }

}
//------------------------------------------------------------------------------
void TTaskData::SumCostDays()
{
    TPrjObject* This = ((TPrjObject*)(this));
    if(!This->IsForeign())
	{
      if(This->GetType() == ttAbstractTask )
 //        || This->GetType() == ttProject)    //项目单独处理zws20090713
      {
           int iSumCostDays(0);
         if(This->ChildCount()<=0)
            This->CostDays = 0;
          else
          {
             bool bHaveCostDays=false;
              for(int j=0;j<This->ChildCount();j++)
              {
                   if(This->GetChild(j).CostDays>0)
                   {
                     bHaveCostDays=true;
                     break;
                   }
               }
              if(bHaveCostDays)
              {
				 iSumCostDays=0;
				for(TDateTime i = This->StartDate; i <= This->EndDate; i++)
				{
					if(This->Calendar->IsWorkDay(i))
					{
						iSumCostDays++;
					}
				}
			  }
             This->CostDays = iSumCostDays;
          }
      }
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetASAP_StartDate(TDateTime AASAP_StartDate)
{
	if(CompareSetValue(FASAP_StartDate, AASAP_StartDate))
    {
      TPrjObject* This = ((TPrjObject*)(this));
      if(This->GetType() != ttProject)
      {
           TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
           ThisParent->SumASAP_StartDate();
	  }
	}
}
//------------------------------------------------------------------------------
void TTaskData::SumASAP_StartDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->GetType() == ttProject && This->PlanType == ptASAP)
     {
         return;
     }
     if(This->ChildCount() > 0)
     {
         TDateTime MinStart=This->GetChild(0).ASAP_StartDate;
         for(int i = 0; i < This->ChildCount(); i++)
         {
                MinStart = MinStart > This->GetChild(i).ASAP_StartDate ?
                        This->GetChild(i).ASAP_StartDate : MinStart;
          }
         if(int(MinStart) > 5)
             This->ASAP_StartDate = MinStart;
         else
             This->ASAP_StartDate = 0;
     }
    else
    {
      if(This->Project()->PlanType==ptASAP)
         This->ASAP_StartDate=This->Project()->ASAP_StartDate;
     else
         This->ASAP_StartDate=This->Project()->ASAP_EndDate;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetASAP_EndDate(TDateTime AASAP_EndDate)
{
	if(CompareSetValue(FASAP_EndDate, AASAP_EndDate))
    {
      TPrjObject* This = ((TPrjObject*)(this));
      if(This->GetType() != ttProject)
      {
           TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
           ThisParent->SumASAP_EndDate();
	  }
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumASAP_EndDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->ChildCount() > 0)
	 {//注意：当子任务的工期是 0 时，EndDate 在子任务开始的前一天
         TDateTime MaxEnd = This->GetChild(0).ASAP_StartDate;
         for(int i = 0; i < This->ChildCount(); i++)
		 {
		   if(This->GetChild(i).CostDays>0)
             MaxEnd = MaxEnd > This->GetChild(i).ASAP_EndDate ?
                      MaxEnd : This->GetChild(i).ASAP_EndDate;
           else
             MaxEnd = MaxEnd > This->GetChild(i).ASAP_EndDate-1 ?
                      MaxEnd : This->GetChild(i).ASAP_EndDate-1;
         }
         if(int(MaxEnd) > 5)
			 This->ASAP_EndDate = MaxEnd;
		 else
             This->ASAP_EndDate = 0;
     }
    else
    {
      if(This->Project()->PlanType==ptASAP)
         This->ASAP_EndDate=This->Project()->ASAP_StartDate;
     else
         This->ASAP_EndDate=This->Project()->ASAP_EndDate;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetStartDate(TDateTime AStartDate)
{
     if(CompareSetValue(FStartDate, AStartDate))
    {
      FTempStartDate=FStartDate;
      TPrjObject* This = ((TPrjObject*)(this));
      if(This->GetType() != ttProject)
      {
           TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
           TDateTime OldStartDate=ThisParent->StartDate;
           ThisParent->SumStartDate();
           if(OldStartDate!=ThisParent->StartDate)
              ThisParent->SumCostDays();
      }
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetEndDate(TDateTime AEndDate)
{
   if(CompareSetValue(FEndDate, AEndDate))
    {
      FTempEndDate=FEndDate;
      TPrjObject* This = ((TPrjObject*)(this));
      if(This->GetType() != ttProject)
      {
           TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
           TDateTime OldEndDate=ThisParent->EndDate;
           ThisParent->SumEndDate();
           if(OldEndDate!=ThisParent->EndDate)
              ThisParent->SumCostDays();
      }
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumStartDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->GetType() == ttProject && This->PlanType == ptASAP)
     {
         return;
     }
     if(This->ChildCount() > 0)
     {
         TDateTime MinStart=This->GetChild(0).StartDate;
         for(int i = 0; i < This->ChildCount(); i++)
         {
                MinStart = MinStart > This->GetChild(i).StartDate ?
                        This->GetChild(i).StartDate : MinStart;
          }
         if(int(MinStart) > 5)
             This->StartDate = MinStart;
         else
             This->StartDate = 0;
     }
    else
    {
      if(This->Project()->PlanType==ptASAP)
        This->StartDate=This->Project()->StartDate;
      else
        This->StartDate=This->Project()->EndDate;
    }

}
//------------------------------------------------------------------------------
void TTaskData::SumEndDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->ChildCount() > 0)
     {//注意：当子任务的工期是 0 时，EndDate 在子任务开始的前一天
         TDateTime MaxEnd = This->GetChild(0).StartDate;
         for(int i = 0; i < This->ChildCount(); i++)
		 {
				if(This->GetChild(i).CostDays>0)
                     MaxEnd = MaxEnd > This->GetChild(i).EndDate ?
                              MaxEnd : This->GetChild(i).EndDate;
                else
                     MaxEnd = MaxEnd > This->GetChild(i).EndDate-1 ?
                              MaxEnd : This->GetChild(i).EndDate-1;
         }
         if(int(MaxEnd) > 5)
             This->EndDate = MaxEnd;  //FASAP_EndDate -> ASAP_EndDate
         else
             This->EndDate = 0;
     }
    else
    {
      if(This->Project()->PlanType==ptASAP)
           This->EndDate=This->Project()->StartDate;
       else
          This->EndDate=This->Project()->EndDate;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetALAP_StartDate(TDateTime AALAP_StartDate)
{
	if(CompareSetValue(FALAP_StartDate, AALAP_StartDate))
    {
         TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
         ThisParent->SumALAP_StartDate();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumALAP_StartDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->ChildCount() > 0)
     {
          TDateTime MinStart=This->GetChild(0).ALAP_StartDate;
          for(int i = 0; i < This->ChildCount(); i++)
          {
             MinStart = MinStart > This->GetChild(i).ALAP_StartDate ?
                        This->GetChild(i).ALAP_StartDate : MinStart;

           }
          if(int(MinStart) > 5)
              This->ALAP_StartDate = MinStart;
          else
              This->ALAP_StartDate = 0;
     }
    else
    {
      if(This->Project()->PlanType==ptASAP)
          This->ALAP_StartDate=This->Project()->ALAP_StartDate;
     else
          This->ALAP_StartDate=This->Project()->ALAP_EndDate;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetALAP_EndDate(TDateTime AALAP_EndDate)
{
	if(CompareSetValue(FALAP_EndDate, AALAP_EndDate))
    {
         TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
         ThisParent->SumALAP_EndDate();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumALAP_EndDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->GetType() == ttProject && This->PlanType == ptALAP)
     {
          return;
     }
     if(This->ChildCount() > 0)
     {//注意：当子任务的工期是 0 时，EndDate 在子任务开始的前一天
          TDateTime MaxEnd = This->GetChild(0).ALAP_EndDate-1;
          for(int i = 0; i < This->ChildCount(); i++)
          {
			  if(This->GetChild(i).CostDays>0)
                MaxEnd = MaxEnd > This->GetChild(i).ALAP_EndDate ?
                     MaxEnd : This->GetChild(i).ALAP_EndDate;
              else
                MaxEnd = MaxEnd > This->GetChild(i).ALAP_EndDate-1 ?
                     MaxEnd : This->GetChild(i).ALAP_EndDate-1;
            }
          if(int(MaxEnd) > 5)
               This->ALAP_EndDate = MaxEnd;
          else
               This->ALAP_EndDate = 0;
     }
    else
    {
      if(This->Project()->PlanType==ptASAP)
          This->ALAP_EndDate=This->Project()->ALAP_StartDate;
     else
          This->ALAP_EndDate=This->Project()->ALAP_EndDate;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetFactStartDate(TDateTime AFactStartDate)
{
    if(CompareSetValue(FFactStartDate, AFactStartDate))
    {
         TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
         ThisParent->SumFactStartDate();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumFactStartDate()
{
     int idx;
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->ChildCount() > 0)
     {
         TDateTime MinStart = 0;
         for(int i = 0; i < This->ChildCount(); i++)
         {
           if(This->GetChild(i).FactStartDate > TDateTime(5))
             MinStart = This->GetChild(i).FactStartDate;
         }
         if(MinStart == TDateTime(0))
         {
           This->FactStartDate = 0;
           return;
         }
         for(int i = 0; i < This->ChildCount(); i++)
            if(This->GetChild(i).FactStartDate>TDateTime(5))
                  MinStart = MinStart < This->GetChild(i).FactStartDate ?
                             MinStart : This->GetChild(i).FactStartDate;
         This->FactStartDate = MinStart;
     }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetFactEndDate(TDateTime AFactEndDate)
{
    if(CompareSetValue(FFactEndDate, AFactEndDate))
    {
         TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
         ThisParent->SumFactEndDate();
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumFactEndDate()
{
     TPrjObject* This = ((TPrjObject*)(this));
     if(This->ChildCount() > 0)
     {
         TDateTime MaxEnd = This->GetChild(0).FactEndDate;
         bool AllOvered=true;
         for(int i = 0; i < This->ChildCount(); i++)
		 {
			  if (This->GetChild(i).TaskStatus!=tsOvered)
              {
               AllOvered=false;
               break;
              }
              
              if(double(This->GetChild(i).FactEndDate) > 5)
              {
                  MaxEnd = MaxEnd > This->GetChild(i).FactEndDate ?
                             MaxEnd : This->GetChild(i).FactEndDate;
              }
          }
		 if(AllOvered)
         {
            This->FactEndDate = MaxEnd;
            if(This->GetTaskType()!=ttProject)  //项目不要自动完工
              This->TaskStatus=tsOvered;
         }
         else
            This->FactEndDate = 0;
     }
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetPlanType(TPlanType APlanType)
{
   CompareSetValue(FPlanType, APlanType);
}
//------------------------------------------------------------------------------
void __fastcall TTaskData::SetCritical(bool ACritical)
{
   CompareSetValue(FCritical, ACritical);
}

//------------------------------------------------------------------------------
String __fastcall TTaskData::GetSortCode()
{
   TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
   if(ThisParent)
   {
        if(ThisParent->GetType() == ttProject && ThisParent->GetType() == ttForeignProject)
        {
            return Code;
        }else
        {
            return ThisParent->SortCode + Code;
        }
   }
   return "";
}
String __fastcall TTaskData::GetForeignID()
{
    TPrjObject* This = ((TPrjObject*)(this));
    switch(This->GetType())
    {
        case ttProject:
            return "";
        case ttForeignProject:
            return FForeignID;
        default:
            if(This->Parent())
                return This->Parent()->ForeignID;
            else
                return "";
    }
}
TTaskType __fastcall TTaskData::GetTaskType()
{
    TPrjObject* This = ((TPrjObject*)(this));
    return This->GetType();
}
void TTaskData::SumMileStone()
{
    if(!MileStone)
        return;
    TTaskStatus bkTaskStatus = TaskStatus;
    TPrjObject* This = ((TPrjObject*)(this));
    bool AllNotStart(true);
    bool AllOvered(true);
    for(int i = 0; i < This->FrontTaskCount; i++)
    {
        TTask* AFront = This->FrontTasks[i]->Front;
        if(AFront->TaskStatus != tsNotStart)
            AllNotStart = false;
        if(AFront->TaskStatus != tsOvered)
            AllOvered = false;
    }
    if(AllNotStart && bkTaskStatus != tsNotStart)
    {
        TaskStatus = tsNotStart;
    }else if(AllOvered && bkTaskStatus != tsOvered)
    {
       TPrjObject* This=(TPrjObject*)(this);
       if(This->GetType()==ttProject)
		 TaskStatus = tsStarted;
	}
}
//------------------------------------------------------------------------------
void TTaskData::SumFFDate()
{
    TPrjObject* This = ((TPrjObject*)(this));
    if((This->GetType() == ttTask || This->GetType() == ttForeignProject)
          && !This->IsForeign())
    {
        FFF_StartDate = FASAP_StartDate;
        FFF_EndDate = FALAP_EndDate;
		TDateTime dData = 0;
		switch(This->PlanType)
        {
            case ptNone:
                break;
            case ptASAP:/*最早开工*/
            case ptBSO:
            case ptBFO:
            case ptASO:
            case ptAFO:
                for(int i = 0; i < This->LateTaskCount; i++)
                {
                    TTaskLink* ALink = This->LateTasks[i];
                    switch(ALink->Type)
                    {
                         case ftNone:
                             break;
                         case ftFinishStart:
                             if(ALink->FreeTime<0)
							   dData = (double)ALink->Task->StartDate - ALink->FreeTime -1;
							 else
                               dData = ALink->Task->StartDate -1;
							 FFF_EndDate = FFF_EndDate > dData ? dData : FFF_EndDate;
                             break;
                         case ftStartStart:
							 break;
                         case ftFinishFinish:
							 if(ALink->FreeTime<0)
							   dData = (double)ALink->Task->EndDate - ALink->FreeTime ;
                             else
                               dData = ALink->Task->EndDate;
                             FFF_EndDate = FFF_EndDate > dData ? dData : FFF_EndDate;
                             break;
                         case ftStartFinish:
                             break;
                         default:
                             throw Exception("前置任务类型未定义");
                    }
                }
                for(int i = 0; i < This->FrontTaskCount; i++)
                {
                    TTaskLink* ALink = This->FrontTasks[i];
                    if(ALink->Type == ftStartFinish)
                    {
						 FFF_EndDate = FFF_EndDate > ALink->Front->EndDate ?
                                       ALink->Front->EndDate : FFF_EndDate;
                    }
                }
                if(FFF_EndDate<EndDate) FFF_EndDate=EndDate;
                break;
            case ptALAP:/*最迟完工*/
                for(int i = 0; i < This->FrontTaskCount; i++)
                {
                    TTaskLink* ALink = This->FrontTasks[i];
                    switch(ALink->Type)
                    {
                         case ftNone:
                             break;
                         case ftFinishStart:
                             FFF_StartDate = FFF_StartDate < ALink->Front->EndDate+1 ?
                                             ALink->Front->EndDate+1 : FFF_StartDate;
                             break;
                         case ftStartStart:
							 FFF_StartDate = FFF_StartDate < ALink->Front->StartDate ?
                                             ALink->Front->StartDate : FFF_StartDate;
                             break;
                         case ftFinishFinish:
							 break;
                         case ftStartFinish:
                             break;
                         default:
                             throw Exception("前置任务类型未定义");
                    }
                }
                if(FFF_StartDate>FStartDate) FFF_EndDate=FStartDate;
                break;
            case ptMSO:
                FFF_StartDate = StartDate;
                FFF_EndDate = EndDate;
                break;
            case ptMFO:/*必须完成于*/
                FFF_StartDate = StartDate;
                FFF_EndDate = EndDate;
				break;
        }
    }
}

//------------------------------------------------------------------------------
void TTaskData::SumStartEndDate()
{
	TPrjObject* This = ((TPrjObject*)(this));
	switch(This->GetType())
	{
		case ttProject:
			break;
		case ttTask:
			break;
        case ttAbstractTask:
			if(This->ChildCount() > 0)
            {
				TDateTime tStartDate = 0;
				TDateTime tEndDate =  0;
                for(int i = 0; i < This->ChildCount(); i++)
                {
					if(This->GetChild(i).GetType() == ttAbstractTask)
                    {
                        This->GetChild(i).SumStartEndDate();
                    }
                    TDateTime dt = This->GetChild(i).FStartDate;
                    if((int)tStartDate==0)
                        tStartDate=dt;
                    else
                        tStartDate = tStartDate > dt ? dt : tStartDate;
                    dt = This->GetChild(i).EndDate;
                    if((int)tEndDate==0)
                       tEndDate=dt;
                     else
                        tEndDate = tEndDate < dt ? dt : tEndDate;
                }
                if(FStartDate != tStartDate)
                {
                    FStartDate = tStartDate;
                    IsModified = true;
                }
                if(FEndDate != tEndDate)
                {
                    FEndDate = tEndDate;
                    IsModified = true;
                }
				if(IsModified&&!ReadingData)
                {
                  SumCostDays();
                  if(This->Project()->PlanType==ptALAP)
                  {
                    SumASAP_StartDate();
                    SumALAP_StartDate();
                  }
                  else
                  {
                    SumASAP_EndDate();
                    SumALAP_EndDate();
                  }
                 }
            }
			else
            {
               if(This->Project()->PlanType==ptALAP)
               {
                 FStartDate = This->Project()->EndDate;
                 FEndDate =FStartDate;

                }
                else
                {
                 FStartDate = This->Project()->StartDate;
                 FEndDate =FStartDate;
                }
                IsModified = true;
            }
            break;
        case ttForeignProject:
            break;
    }
}
//------------------------------------------------------------------------------
void TTaskData::SumAll()
{
	if(ReadingData)
		 return;
	SumTaskStatus();
	SumWorkLoad();
	SumInvest();
	SumAnticipateCostDays();
	SumOptimismCostDays();
	SumPessimismCostDays();
	SumStartDate();
	SumEndDate();
	SumASAP_StartDate();
	SumASAP_EndDate();
	SumALAP_StartDate();
	SumALAP_EndDate();
	SumCostDays();
	SumPertStartTime();
	SumPertEndTime();
	SumFactWorkLoad();
	SumFactCostDays();
	SumEnvaluedWorkLoad();
	SumFactInvest();
	SumEnvaluedInvest();
	SumFactStartDate();
	SumFactEndDate();
	SumProcessDate();	
	SumFFDate();
}
//------------------------------------------------------------------------------
int TTaskData::GetCumulateDays()
{
  return 0 ;
}
TDateTime TTaskData::GetptyLimitedDate()
{
  switch(FPlanType)
    {
      case ptMFO :
      case ptBFO :
      case ptAFO :
          if(int(FLimitedEndDate)>=1)
            return FLimitedEndDate;
          else
            return Date();
        break;
      case ptMSO :
      case ptBSO :
      case ptASO :
          if(int(FLimitedDate)>=1)
            return FLimitedDate;
          else
            return Date();
        break;
      default : return Date();
    }
}
void TTaskData::SetptyLimitedDate(TDateTime date)
{
    switch(FPlanType)
    {
      case ptMFO :
      case ptBFO :
      case ptAFO :
          FLimitedEndDate = date;
        break;
      case ptMSO :
      case ptBSO :
      case ptASO :
          FLimitedDate = date;
        break;
    }
}
//-----------------------------------------------------------------------------

void __fastcall TTaskData::SetCheckItem(bool bCheckItem)
{
	if(CompareSetValue(FCheckItem, bCheckItem))
    {
      if(!bCheckItem)//设置为非核算项目时,要保证下级没有核算项目
      {
    	  TPrjObject* This = ((TPrjObject*)(this));
    	  for(int i = 0; i < This->ChildCount(); i++)
    	  {
          TPrjObject& AChild = This->GetChild(i);
          AChild.CheckItem=false;
        }
      }
      else//设置为核算项目时,保证其所有上级都是核算项目
      {
			  TPrjObject* ThisParent = ((TPrjObject*)(this))->Parent();
			  ThisParent->CheckItem=true;
	  }
	}
}

//------------------------------------------------------------------------------
//TPrjCalendar
//------------------------------------------------------------------------------
void TPrjCalendar::SetCalendar(TDateStatus Sunday, TDateStatus Monday,
                           TDateStatus Tuesday, TDateStatus Wednesday,
                           TDateStatus Thursday, TDateStatus Friday,
                           TDateStatus Saturday)
{
    FPrjCalendar[wdSunday] = Sunday;
    FPrjCalendar[wdMonday] = Monday;
    FPrjCalendar[wdTuesday] = Tuesday;
    FPrjCalendar[wdWednesday] = Wednesday;
    FPrjCalendar[wdThursday] = Thursday;
    FPrjCalendar[wdFriday] = Friday;
    FPrjCalendar[wdSaturday] = Saturday;
}
//------------------------------------------------------------------------------
void TPrjCalendar::AddHoliday(TDateTime ADate)
{
    if(FHolidays.Length)
    for(int i = FHolidays.Low; i <=FHolidays.High; i++)
    {
       if(FHolidays[i] == ADate)
          return;
    }
    FHolidays.Length = FHolidays.Length + 1;
    FHolidays[FHolidays.High] = ADate;
}
//------------------------------------------------------------------------------
void TPrjCalendar::DelHoliday(TDateTime ADate)
{
    for(int i = FHolidays.Low; i <=FHolidays.High; i++)
    {
       if(FHolidays[i] == ADate)
       {
          for(int j = i; j <= FHolidays.High; j++)
          {
             FHolidays[j+1] = FHolidays[j];
          }
          FHolidays.Length = FHolidays.Length - 1;
          return;
       }
    }
}
//------------------------------------------------------------------------------
void TPrjCalendar::ClearHoliday()
{
    FHolidays.Length = 0;
}
//------------------------------------------------------------------------------
bool TPrjCalendar::IsWorkDay(TDateTime ADate)
{
    BYTE dow;
    dow = DayOfWeek(ADate)-1;
    if(PrjCalendar[(TWeekDay)dow] == dsWork)
    {
        return !IsHoliday(ADate);
    }
    else
		return IsOutOfDay(ADate);
}
//------------------------------------------------------------------------------
bool TPrjCalendar::IsHoliday(TDateTime ADate)
{
    if(FHolidays.Length == 0)
        return false;
    for(int i = FHolidays.Low; i <=FHolidays.High; i++)
    {
        if(FHolidays[i] == ADate)
        {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
bool TPrjCalendar::IsOutOfDay(TDateTime ADate)
{
    if(FOutOfdays.Length == 0)
        return false;
    for(int i = FOutOfdays.Low; i <=FOutOfdays.High; i++)
    {
        if(FOutOfdays[i] == ADate)
        {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
TDateStatus __fastcall TPrjCalendar::GetPrjCalendar(TWeekDay AWeekDay)
{
    return FPrjCalendar[AWeekDay];
}
//------------------------------------------------------------------------------
void __fastcall TPrjCalendar::SetPrjCalendar(TWeekDay AWeekDay, TDateStatus AStatus)
{
    FPrjCalendar[AWeekDay] = AStatus;
}
//------------------------------------------------------------------------------
void TPrjCalendar::AddOutOfday(TDateTime ADate)
{
    if(FOutOfdays.Length)
    for(int i = FOutOfdays.Low; i <=FOutOfdays.High; i++)
    {
       if(FOutOfdays[i] == ADate)
          return;
    }
    FOutOfdays.Length = FOutOfdays.Length + 1;
    FOutOfdays[FOutOfdays.High] = ADate;
}
//------------------------------------------------------------------------------
void TPrjCalendar::DelOutOfday(TDateTime ADate)
{
    for(int i = FOutOfdays.Low; i <=FOutOfdays.High; i++)
    {
       if(FOutOfdays[i] == ADate)
       {
          for(int j = i; j <= FOutOfdays.High; j++)
          {
             FOutOfdays[j+1] = FOutOfdays[j];
          }
          FOutOfdays.Length = FOutOfdays.Length - 1;
          return;
       }
    }
}
//------------------------------------------------------------------------------
void TPrjCalendar::ClearOutOfday()
{
  FOutOfdays.Length = 0;
}
//------------------------------------------------------------------------------
//TTaskIterator
//------------------------------------------------------------------------------
TIteratorBase::TIteratorBase(TProject&AProject)
              :FProject(AProject)
{
    FProject.FIterators.Add(this);
}
TIteratorBase::~TIteratorBase()
{
    FProject.FIterators.Delete(*this);
}
//------------------------------------------------------------------------------
//TTaskIterator
//------------------------------------------------------------------------------
TTaskIterator::TTaskIterator(TProject&AProject)
              :TIteratorBase(AProject), FTasks(NULL)
{
}
//------------------------------------------------------------------------------
TTask* TTaskIterator::operator [] (int Index)
{
    if(Index >= 0 && Index < FTasks.Count())
         return &(FTasks[Index]);
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TTaskIterator::Count()
{
    return FTasks.Count();
}
//------------------------------------------------------------------------------
int TTaskIterator::TaskIndexOf(TTask&ATask)
{
    return FTasks.IndexOf(ATask);
}
//------------------------------------------------------------------------------
void TTaskIterator::OnTaskAdd(TPrjObject&AObj)
{
    switch(AObj.GetType())
    {
        case ttAbstractTask:
            if(!AObj.IsForeign())
                AddObjectChilds(AObj);
            break;
        case ttTask:
            if(!AObj.IsForeign())
                 goto labelAddTask;
            break;
        case ttForeignProject:
            if(!AObj.IsForeign())
                 goto labelAddTask;
            break;
        default:
            throw Exception("类型错误");
    }
    return;
labelAddTask:
    TTask* Next = GetNextTask((TTask*)&AObj);
    if(Next)
    {
        int NextIndex = FTasks.IndexOf(*Next);
        if(NextIndex >= 0)
            FTasks.Insert((TTask*)(&AObj), NextIndex);
        else
            FTasks.Add((TTask*)(&AObj));
    }else
    {
        FTasks.Add((TTask*)(&AObj));
    }
}
void TTaskIterator::AddObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
        OnTaskAdd(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
TTask* TTaskIterator::GetNextTask(TTask*ATask)
{
    TTask* Next(NULL);
    TPrjObject* CurrObj(ATask);
    while(CurrObj->Parent())
    {
        int Index = CurrObj->Parent()->ChildIndex(*CurrObj);
        if(Index == -1)
             return NULL;
        TPrjObject*CurrParent = CurrObj->Parent();
        for(int i = Index+1; i < CurrParent->ChildCount(); i++)
        {
             Next = GetChildTask(&(CurrParent->GetChild(Index+1)));
             if(Next)
                    return Next;
        }
        CurrObj = CurrParent;
    }
    return NULL;
}
//------------------------------------------------------------------------------
TTask* TTaskIterator::GetChildTask(TPrjObject*AObj)
{
    if(!AObj)
         return NULL;

    switch(AObj->GetType())
    {
        case ttAbstractTask:
            for(int i = 0; i < AObj->ChildCount(); i++)
            {
                 TTask* rtn = GetChildTask((TTask*)(&(AObj->GetChild(i))));
                 if(rtn)
                      return rtn;
            }
            break;
        case ttTask:
            if(!AObj->IsForeign())
                 return (TTask*)AObj;
            else
                 return NULL;
        case ttForeignProject:
            if(!AObj->IsForeign())
                 return (TTask*)AObj;
            else
                 return NULL;
        default:
            throw Exception("类型错误");
    }

    return NULL;
}
//------------------------------------------------------------------------------
void TTaskIterator::OnTaskDelete(TPrjObject&AObj)
{
    switch(AObj.GetType())
    {
        case ttAbstractTask:
            if(!AObj.IsForeign())
                DeleteObjectChilds(AObj);
            break;
        case ttTask:
            FTasks.Delete(*((TTask*)(&AObj)));
            break;
        case ttForeignProject:
            FTasks.Delete(*((TTask*)(&AObj)));
            break;
    }
}
//------------------------------------------------------------------------------
void TTaskIterator::DeleteObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
        OnTaskDelete(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
void TTaskIterator::OnTaskLinkAdd(TTaskLink&)
{
}
//------------------------------------------------------------------------------
void TTaskIterator::OnTaskLinkDelete(TTaskLink&)
{
}
//------------------------------------------------------------------------------
void TTaskIterator::OnClear()
{
    FTasks.Clear();
}
//------------------------------------------------------------------------------
//TTaskLinkIterator
//------------------------------------------------------------------------------
TTaskLinkIterator::TTaskLinkIterator(TProject&AProject)
                  :TIteratorBase(AProject), FTaskLinks(NULL)
{
}
//------------------------------------------------------------------------------
TTaskLink* TTaskLinkIterator::operator [] (int Index)
{
    if(Index >= 0 && Index < FTaskLinks.Count())
        return &(FTaskLinks[Index]);
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TTaskLinkIterator::Count()
{
    return FTaskLinks.Count();
}
//------------------------------------------------------------------------------
void TTaskLinkIterator::OnTaskAdd(TPrjObject&)
{
}
//------------------------------------------------------------------------------
void TTaskLinkIterator::OnTaskDelete(TPrjObject&)
{
}
//------------------------------------------------------------------------------
void TTaskLinkIterator::OnTaskLinkAdd(TTaskLink&ALink)
{
		FTaskLinks.Add(&ALink);
}
//------------------------------------------------------------------------------
void TTaskLinkIterator::OnTaskLinkDelete(TTaskLink&ALink)
{
    FTaskLinks.Delete(ALink);
}
//------------------------------------------------------------------------------
void TTaskLinkIterator::OnClear()
{
    FTaskLinks.Clear();
}
//------------------------------------------------------------------------------
//TExpandFoldIterator
//------------------------------------------------------------------------------
TExpandFoldIterator::TExpandFoldIterator(TProject&AProject)
                  :TIteratorBase(AProject), FObjects(NULL)
{
    AProject.EFExpanded = true;
}
//------------------------------------------------------------------------------
TPrjObject* TExpandFoldIterator::operator [] (int Index)
{
    if(Index >= 0 && Index < FObjects.Count())
        return &(FObjects[Index]);
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TExpandFoldIterator::Count()
{
    return FObjects.Count();
}
//------------------------------------------------------------------------------
bool EFObjectIsExpand(TPrjObject*AObj)
{
    while(AObj)
    {
        AObj = AObj->Parent();
        if(AObj && !(AObj->EFExpanded))
            return false;
    }
    return true;
}
//------------------------------------------------------------------------------
TPrjObject* EFGetNextExpandedObject(TPrjObject*AObj)
{
    TPrjObject* CurrObj(AObj);
    while(CurrObj->Parent())
    {
        int Index = CurrObj->Parent()->ChildIndex(*CurrObj);
        if(Index == -1)
             return NULL;
        TPrjObject*CurrParent = CurrObj->Parent();
        if(Index+1 < CurrParent->ChildCount())
             return &(CurrParent->GetChild(Index+1));
        CurrObj = CurrParent;
    }
    return NULL;
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::OnTaskAdd(TPrjObject&AObj)
{
    FProject.EFExpanded = true;
    if(EFObjectIsExpand(&AObj))
    {
         TPrjObject* next = EFGetNextExpandedObject(&AObj);
         int nextindex = FObjects.IndexOf(*next);
         if(nextindex >= 0 && nextindex < FObjects.Count())
         {
             FObjects.Insert(&AObj, nextindex);
             nextindex++;
             InsertObjectChilds(AObj, nextindex);
         }else
         {
             FObjects.Add(&AObj);
             AddObjectChilds(AObj);
         }
    }
    ReIndex();
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::InsertObjectChilds(TPrjObject& AObj, int& Index)
{
    if(AObj.EFExpanded)
    {
         for(int i = 0; i < AObj.ChildCount(); i++)
         {
             FObjects.Insert(&(AObj.GetChild(i)), Index);
             Index++;
             InsertObjectChilds(AObj.GetChild(i), Index);
         }
    }
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::AddObjectChilds(TPrjObject&AObj)
{
    if(AObj.EFExpanded)
    {
         for(int i = 0; i < AObj.ChildCount(); i++)
         {
             FObjects.Add(&(AObj.GetChild(i)));
             AddObjectChilds(AObj.GetChild(i));
         }
    }
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::OnTaskDelete(TPrjObject&AObj)
{
    DeleteObjectChilds(AObj);
    FObjects.Delete(AObj);
    ReIndex();
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::DeleteObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
         DeleteObjectChilds(AObj.GetChild(i));
         FObjects.Delete(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::OnTaskLinkAdd(TTaskLink&ALink)
{
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::OnTaskLinkDelete(TTaskLink&ALink)
{
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::OnClear()
{
    FObjects.Clear();
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::Expand(int Index)
{
    TUpdateNotify UpdateNotify(FProject.__FPrjDataChangeLink);
    FProject.EFExpanded = true;
    if(!(Index >= 0 && Index < Count()))
        return;
    if(FObjects[Index].GetType() == ttForeignProject)
    {
        TForeignProject& AForPrj = (TForeignProject&) FObjects[Index];
        if(!AForPrj.LoadedData)
			FProject.LoadForeignData(&AForPrj);
    }
    if(CanExpandFold(Index) && FObjects[Index].EFExpanded == false)
    {
        FObjects[Index].EFExpanded = true;
        ExpandChild(FObjects[Index], Index+1);
    }
    ReIndex();
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::Expand(TPrjObject*AObj)
{
    for(int i = 0; i < FObjects.Count(); i++)
    {
        if(&(FObjects[i]) == AObj)
        {
             Expand(i);
             return;
        }
    }
}
//------------------------------------------------------------------------------
int TExpandFoldIterator::ExpandChild(TPrjObject&AObj, int Index)
{
    if(AObj.EFExpanded == true)
    {
        for(int i = 0; i < AObj.ChildCount(); i++)
        {
            FObjects.Insert(&(AObj.GetChild(i)), Index);
            if(CanExpandFold(Index))
            {
                Index++;
                Index = ExpandChild(AObj.GetChild(i), Index);
            }else
            {
                Index++;
            }
        }
    }
    return Index;
}
//------------------------------------------------------------------------------
TPrjObject& LastExpandedChild(TPrjObject&AObj)
{
    if(AObj.ChildCount() > 0)
    {
        TPrjObject&LastChild = AObj.GetChild(AObj.ChildCount()-1);
        if(LastChild.ChildCount() > 0 && LastChild.EFExpanded == true)
        {
             return LastExpandedChild(LastChild);
        }else
             return LastChild;
    }else
		throw Exception("没有孩子的对象不能合拢!");
}
//------------------------------------------------------------------------------
void InitChildExpandIndex(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
         AObj.GetChild(i).EFExpandIndex = -1;
         InitChildExpandIndex(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::Fold(int Index)
{
    TUpdateNotify UpdateNotify(FProject.__FPrjDataChangeLink);
    FProject.EFExpanded = true;
    if(!(Index >= 0 && Index < Count()))
        return;
    if(CanExpandFold(Index) && FObjects[Index].EFExpanded == true)
    {
        TPrjObject& cur = FObjects[Index];
        if(cur.ChildCount() > 0)
        {
             int LastIndex = FObjects.IndexOf(LastExpandedChild(cur));
             for(int i = 0; i < LastIndex - Index; i++)
             {
                  FObjects.Delete(Index+1);
             }
        }
        cur.EFExpanded = false;
        InitChildExpandIndex(FObjects[Index]);
    }
    ReIndex();
}
//------------------------------------------------------------------------------
bool TExpandFoldIterator::CanExpandFold(int Index)
{
    if(Index >= 0 && Index < Count())
    {
        switch(FObjects[Index].GetType())
        {
             case ttProject:
                 FProject.EFExpanded = true;
                 return false;
             case ttAbstractTask:
                 return true;
             case ttTask:
                 return false;
             case ttForeignProject:
                 return true;
             default:
                 throw Exception("类型错误");
        }
    }
    return false;
}
//------------------------------------------------------------------------------
void TExpandFoldIterator::ReIndex()
{
    for(int i = 0; i < FObjects.Count(); i++)
    {
        FObjects[i].EFExpandIndex = i;
    }
}
//------------------------------------------------------------------------------
bool TExpandFoldIterator::IsVisible(TPrjObject&AObj)
{
    TPrjObject* AParent = AObj.Parent();
    while(AParent)
    {
        if(!(AParent->EFExpanded))
            return false;
        else
            AParent = AParent->Parent();
    }
    return true;
}
//------------------------------------------------------------------------------
//TObjectIterator
//------------------------------------------------------------------------------
TObjectIterator::TObjectIterator(TProject&AProject)
                  :TIteratorBase(AProject), FObjects(NULL)
{
}
//------------------------------------------------------------------------------
TPrjObject* TObjectIterator::operator [] (int Index)
{
    if(Index >= 0 && Index < FObjects.Count())
        return &(FObjects[Index]);
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TObjectIterator::Count()
{
    return FObjects.Count();
}
//------------------------------------------------------------------------------
void TObjectIterator::OnTaskAdd(TPrjObject&AObj)
{
    TPrjObject* next = GetNextObject(AObj);
    int nextindex = FObjects.IndexOf(*next);
    if(nextindex >= 0 && nextindex < FObjects.Count())
    {
        FObjects.Insert(&AObj, nextindex);
        nextindex++;
        InsertObjectChilds(AObj, nextindex);
    }else
    {
        FObjects.Add(&AObj);
        AddObjectChilds(AObj);
    }
}
//------------------------------------------------------------------------------
void TObjectIterator::InsertObjectChilds(TPrjObject&AObj, int& Index)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
        FObjects.Insert(&(AObj.GetChild(i)), Index);
        Index++;
        InsertObjectChilds(AObj.GetChild(i), Index);
    }
}
//------------------------------------------------------------------------------
void TObjectIterator::AddObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
        FObjects.Add(&(AObj.GetChild(i)));
        AddObjectChilds(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
TPrjObject* TObjectIterator::GetNextObject(TPrjObject&AObj)
{
    TPrjObject*Parent = AObj.Parent();
    TPrjObject*Obj = &AObj;
    while(Parent)
    {
        int Index = Parent->ChildIndex(*Obj);
        if(Index >= 0 && Index < Parent->ChildCount()-1)
        {
             return &(Parent->GetChild(Index+1));
        }else
        {
             Obj = Parent;
             Parent = Obj->Parent();
        }
    }
    return NULL;
}
//------------------------------------------------------------------------------
void TObjectIterator::OnTaskDelete(TPrjObject&AObj)
{
    DeleteObjectChilds(AObj);
    FObjects.Delete(AObj);
}
//------------------------------------------------------------------------------
void TObjectIterator::DeleteObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
         DeleteObjectChilds(AObj.GetChild(i));
         FObjects.Delete(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
void TObjectIterator::OnTaskLinkAdd(TTaskLink&ALink)
{
}
//------------------------------------------------------------------------------
void TObjectIterator::OnTaskLinkDelete(TTaskLink&ALink)
{
}
//------------------------------------------------------------------------------
void TObjectIterator::OnClear()
{
    FObjects.Clear();
}
//------------------------------------------------------------------------------
//TInnerObjectIterator
//------------------------------------------------------------------------------
TInnerObjectIterator::TInnerObjectIterator(TProject&AProject)
                  :TIteratorBase(AProject), FObjects(NULL)
{
}
//------------------------------------------------------------------------------
TPrjObject* TInnerObjectIterator::operator [] (int Index)
{
    if(Index >= 0 && Index < FObjects.Count())
        return &(FObjects[Index]);
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TInnerObjectIterator::Count()
{
    return FObjects.Count();
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::OnTaskAdd(TPrjObject&AObj)
{
    if(AObj.IsForeign())
        return;
    TPrjObject* next = GetNextObject(AObj);
    int nextindex = FObjects.IndexOf(*next);
    if(nextindex >= 0 && nextindex < FObjects.Count())
    {
        FObjects.Insert(&AObj, nextindex);
        nextindex++;
        InsertObjectChilds(AObj, nextindex);
    }else
    {
        FObjects.Add(&AObj);
        AddObjectChilds(AObj);
    }
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::InsertObjectChilds(TPrjObject&AObj, int& Index)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
        FObjects.Insert(&(AObj.GetChild(i)), Index);
        Index++;
        InsertObjectChilds(AObj.GetChild(i), Index);
    }
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::AddObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
        FObjects.Add(&(AObj.GetChild(i)));
        AddObjectChilds(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
TPrjObject* TInnerObjectIterator::GetNextObject(TPrjObject&AObj)
{
    TPrjObject*Parent = AObj.Parent();
    TPrjObject*Obj = &AObj;
    while(Parent)
    {
        int Index = Parent->ChildIndex(*Obj);
        if(Index >= 0 && Index < Parent->ChildCount()-1)
        {
             return &(Parent->GetChild(Index+1));
        }else
        {
             Obj = Parent;
             Parent = Obj->Parent();
        }
    }
    return NULL;
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::OnTaskDelete(TPrjObject&AObj)
{
    DeleteObjectChilds(AObj);
    FObjects.Delete(AObj);
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::DeleteObjectChilds(TPrjObject&AObj)
{
    for(int i = 0; i < AObj.ChildCount(); i++)
    {
         DeleteObjectChilds(AObj.GetChild(i));
         FObjects.Delete(AObj.GetChild(i));
    }
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::OnTaskLinkAdd(TTaskLink&ALink)
{
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::OnTaskLinkDelete(TTaskLink&ALink)
{
}
//------------------------------------------------------------------------------
void TInnerObjectIterator::OnClear()
{
    FObjects.Clear();
}
//------------------------------------------------------------------------------
//TPrjObject
//------------------------------------------------------------------------------
TPrjObject::TPrjObject(TProject*AProject, TPrjObject*AParent, TPrjCalendar*APrjCalendar)
			  :FProject(AProject), FParent(AParent), FPrjCalendar(APrjCalendar),
               DCStartEvent(0), DCEndEvent(0), DCY(0),
               NCLeft(0), NCTop(0)
{
    EFExpandIndex = -1;
    EFExpanded = false;
}
//------------------------------------------------------------------------------
TPrjObject::~TPrjObject()
{
    Clear();
}
//------------------------------------------------------------------------------
TPrjObject* TPrjObject::Parent()
{
    return FParent;
}
//------------------------------------------------------------------------------
TProject*   TPrjObject::Project()
{
    return FProject;
}
//------------------------------------------------------------------------------
TPrjObject& TPrjObject::GetChildImpl(int Index)
{
    throw Exception("逻辑错误");
}
//------------------------------------------------------------------------------
int TPrjObject::ChildCountImpl()
{
    return 0;
}
//------------------------------------------------------------------------------
TPrjObject& TPrjObject::InsertChildImpl(int Position, TTaskType AType)
{
    throw Exception("逻辑错误");
}
//------------------------------------------------------------------------------
void TPrjObject::InsertChildObjectImpl(int Position, TPrjObject*AChild)
{
    throw Exception("逻辑错误");
}
//------------------------------------------------------------------------------
void TPrjObject::DeleteChildImpl(TPrjObject&)
{
}
//------------------------------------------------------------------------------
void TPrjObject::RemoveChildImpl(TPrjObject&)
{
}
//------------------------------------------------------------------------------
void TPrjObject::ClearImpl()
{
}
//------------------------------------------------------------------------------
//任务组也能返回
TTask* GetTaskByIDout;
TTask* TPrjObject::GetTaskByID(TPrjObject* AObj, const String& AID,const String& APrjID)
{
	String prjid=APrjID;
	if(APrjID=="")
	   prjid=PrjCode;
	GetTaskByIDout = NULL;
    for(int i = 0; i < AObj->ChildCount(); i++)
    {
	  if(GetTaskByIDout) return GetTaskByIDout;
	  if(AObj->GetChild(i).TaskID == AID&&AObj->GetChild(i).PrjCode==prjid)
      {
        GetTaskByIDout = (TTask*)&AObj->GetChild(i);
        return GetTaskByIDout;
      }
	  if(AObj->GetChild(i).GetType()==ttAbstractTask)
		GetTaskByID(&(AObj->GetChild(i)), AID,prjid);
	}
    return GetTaskByIDout;
}
//------------------------------------------------------------------------------
int TPrjObject::ChildIndexImpl(TPrjObject&AObj)
{
    return -1;
}
//------------------------------------------------------------------------------
void TPrjObject::AllChildIsModified(TPrjObject&AChild)
{
    AChild.IsModified=true;
    for( int j=0;j<AChild.ChildCount();j++)
      {
        AllChildIsModified(AChild.GetChild(j));
      }

}
//------------------------------------------------------------------------------
bool TPrjObject::IsForeign()
{
    TPrjObject*AObj = this;
    switch(AObj->GetType())
    {
         case ttProject:
             return false;
         case ttAbstractTask:
         case ttTask:
         case ttForeignProject:
             if(AObj->Parent())
             {
                 if(AObj->Parent()->GetType() == ttForeignProject)
                 {
                     return true;
                 }else if(AObj->Parent()->IsForeign())
                 {
                     return true;
                 }
             }else
                 return false;
             break;
         default:
             throw Exception("类型错误");
    }
    return false;
}
//------------------------------------------------------------------------------
int TPrjObject::Layer()
{
    TPrjObject*AObj = this;
    int Layer = -1;
    while(AObj)
    {
         Layer++;
         AObj = AObj->Parent();
    }
    return Layer;
}
//------------------------------------------------------------------------------
int TPrjObject::ReIndexImpl(int Start)
{
    if(Index != Start && Moving)
        IsModified = true;
    Index = Start;
    Start++;
    for(int i = 0; i < ChildCount(); i++)
    {
        Start = GetChild(i).ReIndexImpl(Start);
    }
    return Start;
}
//------------------------------------------------------------------------------
void TPrjObject::ResetEditStatus()
{
    FEditStatus = esNone;
    for(int i = 0; i < ChildCount(); i++)
        GetChild(i).ResetEditStatus();
}
//------------------------------------------------------------------------------
void TPrjObject::Assign(TPrjObject* AObj)
{
      bool bkReadingData = ReadingData;
      ReadingData = true;
      TTaskData::operator=(*AObj);
     //算法描述：本算法从source到this依次向后，如果source和this相同，则赋值
     //如果不相同，则向下找，
	// 找到，则表示source中删除了一段任务，删除this的这些，赋值
   //没找到，则表示source中加入了一些任务，在其中插入；
      if(!AObj)
          throw Exception("不能Assign一个空对象");
      int ThisIndex(0), SourceIndex(0);
      TPrjObject* NewObj;
      for(; SourceIndex < AObj->ChildCount(); SourceIndex++)
      {
         if(SourceIndex < ChildCount() &&
            AObj->GetChild(SourceIndex).TaskID == GetChild(ThisIndex).TaskID &&
            AObj->GetChild(SourceIndex).GetType() == GetChild(ThisIndex).GetType())
		 {//相同，复制
			 GetChild(ThisIndex).Assign(&(AObj->GetChild(SourceIndex)));
             ThisIndex++;
         }else
         {//不相同，依次向下找
              int i = ThisIndex + 1;
              for(; i < ChildCount(); i++)
				  if(AObj->GetChild(SourceIndex).TaskID == GetChild(i).TaskID &&
                     AObj->GetChild(SourceIndex).GetType() == GetChild(i).GetType())
                     goto labelProcess;
   labelProcess:
              if(i >= ChildCount())
              {//没找到相同的，插入
                  TPrjObject& ANewObj = InsertChild(ThisIndex, AObj->GetChild(SourceIndex).GetType());
                  ANewObj.Assign(&(AObj->GetChild(SourceIndex)));
                  ANewObj.IsNew = false;
                  ANewObj.IsModified = false;
				  ThisIndex++;
              }else
              {//找到了，删除中间的
                  GetChild(i).Assign(&(AObj->GetChild(SourceIndex)));
                  for(int j = i-1; j >= ThisIndex; j--)
                      DeleteChild(GetChild(j));
                  ThisIndex++;
              }
         }
      }
      //剩下多的，删除
      for(int i = ChildCount() - 1; i >= ThisIndex; i--)
          DeleteChild(GetChild(i));
      ReadingData = bkReadingData;
}
//------------------------------------------------------------------------------
TTaskLink* __fastcall TPrjObject::GetFrontTask(int Index)
{
     throw Exception("无前置任务");
}
//------------------------------------------------------------------------------
TTaskLink* __fastcall TPrjObject::GetLateTask(int Index)
{
     throw Exception("无后置任务");
}
//------------------------------------------------------------------------------
int __fastcall TPrjObject::GetFrontTaskCount()
{
     return 0;
}
//------------------------------------------------------------------------------
int __fastcall TPrjObject::GetLateTaskCount()
{
     return 0;
}
//------------------------------------------------------------------------------
TTaskLink* TPrjObject::AddFrontTaskImpl(const String& FrontCode,const String& FrontPrjCode)
{
     throw Exception("不支持此操作");
}
//------------------------------------------------------------------------------
TTaskLink* TPrjObject::AddLateTaskImpl(const String& LateCode,const String& LatePrjCode)
{
     throw Exception("不支持此操作");
}
//------------------------------------------------------------------------------
void TPrjObject::DelFrontTaskImpl(TTaskLink&ATaskLink)
{
     throw Exception("不支持此操作");
}
//------------------------------------------------------------------------------
void TPrjObject::DelLateTaskImpl(TTaskLink&ATaskLink)
{
     throw Exception("不支持此操作");
}
//------------------------------------------------------------------------------
void TPrjObject::ClearFrontTaskImpl()
{
}
//------------------------------------------------------------------------------
void TPrjObject::ClearLateTaskImpl()
{
}
//------------------------------------------------------------------------------
TPrjObject* ChildObjByID(TPrjObject*AObj, const String& AID,const String& APrjID)
{
    if(!AObj)
		return NULL;
	String prjid=APrjID;
	if(APrjID=="")
	   prjid=AObj->PrjCode;
    for(int i = 0; i < AObj->ChildCount(); i++)
    {
        TPrjObject&obj = AObj->GetChild(i);
		if(obj.TaskID == AID&& obj.PrjCode==prjid)
        {
              return &obj;
        }else
        {
		  TPrjObject*ACObj = ChildObjByID(&obj, AID,prjid);
          if(ACObj)
          {
				  return ACObj;
          }
        }
    }
    return NULL;
}
TPrjObject* TPrjObject::ObjByID(String AID,String APrjID)
{
	if(APrjID=="")
		APrjID=PrjCode;
	return ChildObjByID(this, AID,APrjID);
}
//------------------------------------------------------------------------------
TPrjObject* ChildObjByCode(TPrjObject*AObj, const String& ACode,const String& APrjCode)
{
	if(!AObj)
		return NULL;
	String prjcode=APrjCode;
	if(APrjCode=="")
	   prjcode=AObj->PrjCode;
    for(int i = 0; i < AObj->ChildCount(); i++)
	{
        TPrjObject&obj = AObj->GetChild(i);
		if((obj.Code == ACode)&& (obj.PrjCode == prjcode))
        {
			 return &obj;
		}else
        {
		  TPrjObject*ACObj = ChildObjByCode(&obj, ACode,prjcode);
           if(ACObj)
		  {
			   return ACObj;
          }
        }
    }
    return NULL;
}
//------------------------------------------------------------------------------
TPrjObject* TPrjObject::ObjByCode(String ACode,String APrjCode)
{
	if(APrjCode=="")
       APrjCode=PrjCode;
	return ChildObjByCode(this, ACode,APrjCode);
}
//------------------------------------------------------------------------------
int TPrjObject::GetCumulateDays()
{
  int iCumulateDay=0 ;
  TDateTime dStart = FProject->StartDate;
  TDateTime dEnd   = EndDate;
  for(TDateTime dt= dStart; dt <= dEnd; dt++)
  {
    if(Calendar->IsWorkDay(dt))
      iCumulateDay++;
  }
  if(CostDays==0) iCumulateDay--;
  return iCumulateDay;
}
//------------------------------------------------------------------------------
//填充前缀
String TPrjObject::FillPrefix(String sWBS)
{
  int iLevel = FParent->SortCode.Length()/6 ;
  TWBSRule *WBSRule = FProject->GetWBSRule(iLevel);
  return WBSRule->FillPrefix(sWBS);
}
//检查是否合符规则
void TPrjObject::CheckWBSRule(String sWBS)
{
  int iLevel = FParent->SortCode.Length()/6 ;
  TWBSRule *WBSRule = FProject->GetWBSRule(iLevel);
  WBSRule->CheckWBSRule(sWBS);
}
//------------------------------------------------------------------------------
//保证唯一性(true==唯一)
bool TPrjObject::CheckExclusiveWBS(String sWBS)
{
  TPrjObject* child ;
  for(int i=FParent->ChildCount()-1; i>=0; i--)
  {
    child = &(FParent->Childs[i]);
    if((child!=this) && (sWBS==child->WBS))
      return false;
  }
  return true;
}
String TPrjObject::BuildWBS(int iLevel,int order)
{
  TWBSRule *WBSRule = FProject->GetWBSRule(iLevel);
  TWBSRule *ParentWBSRule ;
  if(iLevel>0) ParentWBSRule = FProject->GetWBSRule(iLevel-1);
  String sPreWBS;
  String sWBS;
  if(iLevel==0)
    sPreWBS = FProject->WBSPreNo;
  else
    sPreWBS = FParent->WBS + ParentWBSRule->Separator;

  sWBS = sPreWBS + WBSRule->BuildWBS(order);
  while(!CheckExclusiveWBS(sWBS))
  {
    order++;
    sWBS = sPreWBS + WBSRule->BuildWBS(order);
  }
  return sWBS;
}
//------------------------------------------------------------------------------
void TPrjObject::ClearChildWBS()
{
  TPrjObject* child ;
  for(int i=0; i<ChildCount(); i++)
  {
    child = &(Childs[i]);
	child->FWBS = "";
  }
}
//------------------------------------------------------------------------------
void TPrjObject::BuildSelfWBS()
{
  if(FParent)//对于Project是没有Parent的
  {
    int iLevel = FParent->SortCode.Length()/6 ;
    int i = 0;
    while(i<FParent->ChildCount())
    {
      if(&(FParent->Childs[i])==this)
      {
        break;
      }
      i++;
    }
    WBS = BuildWBS(iLevel,i);
  }
  BuildChildWBS();
}
//------------------------------------------------------------------------------
void TPrjObject::BuildChildWBS()
{
  if(FProject->UsePCWBS)
  {
   return;
  }
  ClearChildWBS();   //保证生成的WBS编码的连续性
  int iLevel = SortCode.Length()/6;
  TPrjObject* child ;
  for(int i=0; i<ChildCount(); i++)
  {
    child = &(Childs[i]);
	child->WBS = child->BuildWBS(iLevel,i);
    child->BuildChildWBS();
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//TWBSRule
//
//------------------------------------------------------------------------------
  TWBSRule::TWBSRule()
  {
      Level = 0; //代表没有对应的规则
      CharType = 0;
      Length = 4;
      Separator = ".";
  }
//------------------------------------------------------------------------------
//order==0时返回A, ==1->B
String TWBSRule::GetChar(int order)
{
  String Result = "";
  int residua = order;
  do
  {
    Result = String(Char(97+residua % 24)) + Result;
    residua = residua / 24;
  }while(residua>0);
  return Result;
}
//------------------------------------------------------------------------------
String TWBSRule::FillPrefix(String sWBS)
{
  String Result = "";
  int iLen = sWBS.Length();
  switch(CharType)
  {
    case 0 ://数字
    case 3 ://数字+字母,自动生成时不采用字母
      for(int i=Length-iLen; i>0; i--)
        Result = Result + "0";
    break;

    case 1 ://大写字母
    case 2 ://小写字母
      for(int i=Length-iLen; i>0; i--)
        Result = Result + "_";
    break;
  }
  return Result + sWBS;
}
//------------------------------------------------------------------------------
void TWBSRule::CheckWBSRule(String sWBS)
{
  int WBSLen = sWBS.Length() ;
  if(WBSLen>Length)
    throw Exception("长度过长，本级WBS编码只能有"+IntToStr(Length)+"位");

  switch(CharType)
  {
    case 0 ://数字
      for(int i=1; i<=WBSLen; i++)
        if(!((sWBS[i]>='0') && (sWBS[i]<='9')))
         throw Exception("本级WBS编码只能输入数字");
    case 3 ://数字+字母,自动生成时不采用字母
      for(int i=1; i<=WBSLen; i++)
        if(!((sWBS[i]=='_') || (sWBS[i]>='A') && (sWBS[i]<='Z')
           || (sWBS[i]>='a') && (sWBS[i]<='z')
           || (sWBS[i]>='0') && (sWBS[i]<='9'))
        )
         throw Exception("本级WBS编码只能输入数字、大、小写字母或下划线");
    break;

    case 1 ://大写字母
      for(int i=1; i<=WBSLen; i++)
        if(!((sWBS[i]=='_') || (sWBS[i]>='A') && (sWBS[i]<='Z')))
         throw Exception("本级WBS编码只能输入大写字母或下划线");
    break;

    case 2 ://小写字母
      for(int i=1; i<=WBSLen; i++)
        if(!((sWBS[i]=='_') || (sWBS[i]>='a') && (sWBS[i]<='z')))
         throw Exception("本级WBS编码只能输入小写字母或下划线");
    break;
  }
}
//------------------------------------------------------------------------------
//生成WBS
String TWBSRule::BuildWBS(int order)
{
  String Result = "";
  int iLen;
  switch(CharType)
  {
    case 0 ://数字
    case 3 ://数字+字母,自动生成时不采用字母
	  Result = IntToStr(order+1);
	break;
	case 1 ://大写字母
	  Result = UpperCase(GetChar(order));
	break;
	case 2 ://小写字母
	  Result = LowerCase(GetChar(order));
	break;
  }
  iLen = Result.Length();
  if(iLen<Length)
	Result =DupeString('0',Length-iLen)+Result;
  if(Length<iLen)
      throw Exception("长度过长，本级WBS编码只能有"+IntToStr(Length)+"位");
  return Result;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//TProject
//------------------------------------------------------------------------------
TProject::TProject()
		   :TPrjObject(this, NULL, &FPrjCalendarObj),
			FIterators(NULL),FChilds(OnDeleteChild), //zws 2003-06-17
			Tasks(*this), TaskLinks(*this), ExpandFoldTasks(*this),
			Objects(*this), InnerObjects(*this),WBSRules(OnDeleteWBSRule)
{
   FUsePCWBS = false;
   FOnRequestSave=NULL;
   FOnLoadData=NULL;
   FSelected=NULL;
   FNeedEditStatus=false;
   FDeletedTasks = new TStringList();
   StatError = 5;
   Calc = new TCalculator(this);
}
//------------------------------------------------------------------------------
TProject::~TProject()
{
   for(int i = 0; i < __FPrjDataChangeLink.Count(); i++)
   {
       __FPrjDataChangeLink[i].FProject = NULL;
   }
   FNeedEditStatus=false;
   FChilds.Clear();
   if(FDeletedTasks)
   {
	delete FDeletedTasks;
	FDeletedTasks=NULL;
   }
   DeletedTaskLinks.Clear();   
   delete Calc;
   WBSRules.Clear();
}
//------------------------------------------------------------------------------
void TProject::OnDeleteWBSRule(void*Item)
{
    delete (TWBSRule*)Item;
}
//------------------------------------------------------------------------------
void TProject::OnDeleteChild(void*AChild)
{
	TPrjObject* obj = (TPrjObject*)AChild;
	if(obj)
		delete obj;
}
//------------------------------------------------------------------------------
TTaskType TProject::GetTypeImpl()
{
    return ttProject;
}
//------------------------------------------------------------------------------
TPrjObject& TProject::GetChildImpl(int Index)
{
    return FChilds[Index];
}
//------------------------------------------------------------------------------
int TProject::ChildCountImpl()
{
    return FChilds.Count();
}
//------------------------------------------------------------------------------
TPrjObject& TProject::InsertChildImpl(int Position, TTaskType AType)
{
    TPrjObject* ct;
    switch(AType)
    {
        case ttProject:
        case ttAbstractTask:
           {
            ct = new TAbstractTask(*this, *this, &FPrjCalendarObj);
           }
            break;
        case ttTask:
            ct = new TTask(*this, *this, &FPrjCalendarObj);
            break;
        case ttForeignProject:
			ct = new TForeignProject(*this, *this);
            break;
        default:
			throw Exception("TProject::InsertChildImpl类型错误");
    }
    FChilds.Insert(ct, Position);

    if(!FProject->ReadingData) ct->BuildSelfWBS(); //crj

    OnTaskAdd(*ct);
    return *ct;
}
//------------------------------------------------------------------------------
void TProject::InsertChildObjectImpl(int Position, TPrjObject*AChild)
{
    FChilds.Insert(AChild, Position);
    AChild->FParent = this;

    if(!FProject->ReadingData)
    {
	  BuildChildWBS();
    }
    
    OnTaskAdd(*AChild);
}
//------------------------------------------------------------------------------
void TProject::DeleteChildImpl(TPrjObject&AChild)
{
    OnTaskDelete(AChild);
    FChilds.Delete(AChild);
    ReIndex();
	SumAll();
}
//------------------------------------------------------------------------------
void TProject::RemoveChildImpl(TPrjObject&AChild)
{
    OnTaskDelete(AChild);
    FChilds.Remove(AChild);
    AChild.FParent = NULL;
    ReIndex();
}
//------------------------------------------------------------------------------
void TProject::ClearImpl()
{
    TUpdateNotify UpdateNotify(__FPrjDataChangeLink);
    try{
        ReadingData = true;
        Selected = NULL;
        Selections.Clear();
        FChilds.Clear();
        for(int i = 0; i < FIterators.Count(); i++)
        {
            FIterators[i].OnClear();
        }
    }__finally
    {
        ReadingData = false;
    }
}
//------------------------------------------------------------------------------
int TProject::ChildIndexImpl(TPrjObject&AObj)
{
    return FChilds.IndexOf(AObj);
}
//------------------------------------------------------------------------------
void TProject::OnTaskAdd(TPrjObject&ATask)
{
    TTaskAddNotify AddNotify(__FPrjDataChangeLink);
    AddNotify.SetTask(&ATask);
    ReIndex();
    for(int i = 0; i < FIterators.Count(); i++)
    {
        FIterators[i].OnTaskAdd(ATask);
    }

}
//------------------------------------------------------------------------------
void TProject::OnTaskDelete(TPrjObject&ATask)
{
    TTaskDeleteNotify DeleteNotify(__FPrjDataChangeLink, &ATask);
    for(int i = 0; i < FIterators.Count(); i++)
    {
        FIterators[i].OnTaskDelete(ATask);
    }
    if(FNeedEditStatus && !ATask.IsForeign())
        DeletedTasks->Add(ATask.TaskID);
}
//------------------------------------------------------------------------------
void TProject::OnTaskLinkAdd(TTaskLink&ALink)
{
    for(int i = 0; i < FIterators.Count(); i++)
    {
		FIterators[i].OnTaskLinkAdd(ALink);
    }
}
//------------------------------------------------------------------------------
void TProject::OnTaskLinkDelete(TTaskLink&ALink)
{
	for(int i = 0; i < FIterators.Count(); i++)
    {
		FIterators[i].OnTaskLinkDelete(ALink);
    }
	if(FNeedEditStatus && !ALink.IsForeign())
		DeletedTaskLinks.Add(ALink.Task->TaskID, ALink.Front->TaskID,ALink.Task->PrjCode,ALink.Front->PrjCode);
}
//------------------------------------------------------------------------------
void TProject::UpdateEditStatus()
{
    ResetEditStatus();
	for(int i = 0; i < TaskLinks.Count(); i++)
		TaskLinks[i]->ResetEditStatus();
	DeletedTaskLinks.Clear();
	if(FDeletedTasks)
		FDeletedTasks->Clear();
}
//------------------------------------------------------------------------------
void TProject::Assign(TPrjObject*AObj)
{
    if(!AObj)
         throw Exception("不能Assing一个空对象");
    if(AObj->GetType() != ttProject)
		throw Exception("TProject::Assign Type Error!");
    TProject* AProject = (TProject*)(AObj);
    TUpdateNotify UpdateNotify(__FPrjDataChangeLink);
	String SelectTaskID,SelectPrjID;
    if(FSelected)
    {
	   SelectTaskID = FSelected->TaskID;
	   SelectPrjID = FSelected->PrjCode;
    }
	FSelected = NULL;

	TPrjObject::Assign(AProject);

	for(int i = 0; i < Objects.Count(); i++)
	{
	   if(Objects[i]->TaskType==ttTask)
	   {
		 TTask * task=(TTask *)Objects[i];
		 task->AssignLink((TTask *)AProject->Objects[i]);
	   }
	}

    if(Tasks.Count() > 0)
	   FSelected = (TTask*)ObjByID(SelectTaskID,SelectPrjID);
}
//------------------------------------------------------------------------------
bool IsChild(TPrjObject&AParent, TPrjObject& AObj)
{
	for(int i = 0; i < AParent.ChildCount(); i++)
    {
        TPrjObject& AChild = AParent.GetChild(i);
        if(&AChild == &AObj)
            return true;
        if(IsChild(AChild, AObj))
            return true;
    }
    return false;
}
TPrjObject* TProject::MoveTask(int OldIndex, int NewIndex)
{
    TPrjObject* From(NULL);
    TPrjObject* To(NULL);
    for(int i = 0; i < Objects.Count(); i++)
    {
        if(Objects[i]->Index == OldIndex && !Objects[i]->IsForeign())
        {
            From = Objects[i];
        }
        if(Objects[i]->Index == NewIndex && !Objects[i]->IsForeign())
        {
            To = Objects[i];
        }
    }
    if(!From)
        throw Exception("程序错误：TProject::MoveTask OldIndex未找到！");
    if(!To && NewIndex != -1)
        throw Exception("程序错误！");

    TPrjObject *FromParent = From->Parent();
    TPrjObject *ToParent(NULL);
    if(To)
        ToParent = To->Parent();
    if(!FromParent)
        throw Exception("发生严重的程序错误：TProject::MoveTask 任务没有父任务！");
    if(To && !ToParent)
        throw Exception("发生严重的程序错误：TProject::MoveTask 任务没有父任务！");
    if(From == To)
        return From;
    if(To && IsChild(*From, *To))
        return From;

    Moving = true;
    TUpdateNotify UpdateNotify(__FPrjDataChangeLink);
    //如果新位置在旧位置下面，删除旧的之后，序号要减小
    FromParent->RemoveChild(*From);
    if(ToParent)
        ToParent->InsertChildObjectImpl(ToParent->ChildIndex(*To), From);
    else
    {
        ToParent = this;
        InsertChildObjectImpl(ChildCount(), From);
    }
    ReIndex();
	SetAllChildIsModified(*From);
	ToParent->SumAll();
	FromParent->SumAll();

    String TaskID = From->TaskID;
	int DeleteIndex = DeletedTasks->IndexOf(TaskID);
    if(DeleteIndex >= 0)
        DeletedTasks->Delete(DeleteIndex);

    Moving = false;
    return From;
}
//------------------------------------------------------------------------------
//移动一个任务
TPrjObject* TProject::AddChildTask(int ChildIndex, int ParentIndex)
{
    TPrjObject*Child(NULL);
    TPrjObject*Parent(NULL);
    for(int i = 0; i < Objects.Count(); i++)
    {
        if(Objects[i]->Index == ChildIndex && !Objects[i]->IsForeign())
        {
            Child = Objects[i];
        }
        if(Objects[i]->Index == ParentIndex && !Objects[i]->IsForeign())
        {
            Parent = Objects[i];
        }
    }
    if(!Child)
        throw Exception("程序错误：TProject::MoveTask ChildIndex未找到！");

    TPrjObject *FromParent = Child->Parent();
    if(!FromParent)
		throw Exception("发生严重错误：TProject::AddChildTask 任务没有父任务！");
    if(Child == Parent)
        return Child;
    if(Parent && IsChild(*Child, *Parent))
        return Child;
    if(Parent->GetType() != ttAbstractTask)
		throw Exception("发生严重错误：TProject::AddChildTask  Parent不是分组任务！");

    TUpdateNotify UpdateNotify(__FPrjDataChangeLink);
    //如果新位置在旧位置下面，删除旧的之后，序号要减小
    FromParent->RemoveChild(*Child);
	ExpandFoldTasks.Expand(Parent);
    Parent->InsertChildObjectImpl(Parent->ChildCount(), Child);
	ReIndex();
    SetAllChildIsModified(*Child);
    Parent->SumAll();
	FromParent->SumAll();

    String TaskID = Child->TaskID;
	int DeleteIndex = DeletedTasks->IndexOf(TaskID);
    if(DeleteIndex >= 0)
        DeletedTasks->Delete(DeleteIndex);

    return Child;
}
//------------------------------------------------------------------------------
bool CheckAAbstractsNoChild(TPrjObject&AObj)
{
    for(int i = AObj.ChildCount()-1; i >= 0; i--)
    {
        if(AObj.GetChild(i).GetType() == ttAbstractTask)
        {
             if(AObj.GetChild(i).ChildCount() <= 0)
             {
                 AObj.DeleteChild(AObj.GetChild(i));
                 return true;
             }else
             {
                 if(CheckAAbstractsNoChild(AObj.GetChild(i)))
                     return true;
             }
        }
    }
    return false;
}
void TProject::CheckNoChildAbstract()
{
labelReCheck:
    for(int i = ChildCount()-1; i >= 0; i--)
    {
        if(GetChild(i).GetType() == ttAbstractTask)
        {
             if(GetChild(i).ChildCount() <= 0)
             {
                 DeleteChild(GetChild(i));
                 goto labelReCheck;
             }else
             {
                 if(CheckAAbstractsNoChild(GetChild(i)))
                      goto labelReCheck;
             }
        }
    }
    RequestUpdate();
}
//------------------------------------------------------------------------------
TPrjObject* ObjectByIndex(TProject&APrj, int AIndex)
{
    for(int i = 0; i < APrj.Objects.Count(); i++)
    {
        if(!(APrj.Objects[i]->IsForeign()) && APrj.Objects[i]->Index == AIndex)
        {
             return APrj.Objects[i];
        }
    }
    return NULL;
}
int LastChildIndex(TPrjObject&AObj)
{
    if(AObj.ChildCount() <= 0 || AObj.GetType() == ttForeignProject)
         return AObj.Index;
    TPrjObject&LastChild = AObj.GetChild(AObj.ChildCount()-1);
    switch(LastChild.GetType())
    {
         case ttProject:
             break;
         case ttForeignProject:
         case ttTask:
             return LastChild.Index;
         case ttAbstractTask:
             return LastChildIndex(LastChild);
         default:
             throw Exception("类型未定义");
    }
    return -1;
}
bool IsNum(String&AStr)
{
    for(int i=1; i <= AStr.Length(); i++)
    {
        if(AStr[i] > '9' || AStr[i] < '0')
             return false;
    }
    return true;
}
double __fastcall TProject::GetFactWorkLoad()
{
	 //汇总实际进度
	 double Sum(0);
	 for(int i = 0; i < ChildCount(); i++)
	 {
	   TPrjObject& AChild = GetChild(i);
	   Sum += AChild.FactWorkLoad ;
	 }
	 return Sum;
}
double __fastcall TProject::GetEnvaluedWorkLoad()
{
	 double Sum(0);
	 for(int i = 0; i < ChildCount(); i++)
	 {
	   TPrjObject& AChild = GetChild(i);
	   Sum += AChild.EnvaluedWorkLoad;
	 }
	   return Sum;
}
double __fastcall TProject::GetBCWS()
{
        if(FCostDays==0)
          return Invest;
        else
	  return Invest*FFactCostDays/FCostDays;

}
//------------------------------------------------------------------------------
double __fastcall TProject::GetACWP()
{
	return FactInvest;
}
//------------------------------------------------------------------------------
double __fastcall TProject::GetBCWP()
{
		return Invest*FTaskPctPercent/100.0;
}
//------------------------------------------------------------------------------
double __fastcall TProject::GetCV()
{
        return BCWP-ACWP;
}
//------------------------------------------------------------------------------
double __fastcall TProject::GetSV()
{
        return BCWP-BCWS;
}
//------------------------------------------------------------------------------
double __fastcall TProject::GetCPI()
{
       if(ACWP!=0)
		  return BCWP/ACWP;
       else
          return 0;
}
double __fastcall TProject::GetSPI()
{
        if(BCWS!=0)
           return BCWP/BCWS;
        else
           return 0;
}
TAbstractTask* TProject::AddAbstractWidthSelection()
{
    Moving = true;
    if(Selections.Count() <= 0)
         return NULL;
    //找出选中任务的第一个和最后一个
    TPrjObject* FirstSelect(NULL);
    TPrjObject* LastSelect(NULL);
    for(int i = 0; i < Selections.Count(); i++)
    {
        if(!Selections[i].IsForeign())
        {
            if(!FirstSelect && !LastSelect)
            {
                FirstSelect = &(Selections[i]);
                LastSelect = &(Selections[i]);
            }else
            {
                int SelIndex = Selections[i].Index;
                if(FirstSelect->Index > SelIndex)
                {
                    FirstSelect = &(Selections[i]);
                }
                if(LastSelect->Index < SelIndex)
                {
                    LastSelect = &(Selections[i]);
                }
            }
        }
    }
    if(!FirstSelect || !LastSelect)
        return NULL;
	TPointerArray< TPrjObject > RequestMove;
    for(int i = FirstSelect->Index; i <= LastSelect->Index; i++)
    {
        TPrjObject*AObj = ObjectByIndex(*this, i);
        if(AObj)
        {
             RequestMove.Add(AObj);
             int LastIndex = LastChildIndex(*AObj);
             if(LastIndex < 0)
				 throw Exception("系统发生错误！");
             i = LastIndex;
        }else
        {
             break;
        }
    }
    for(int i = 1; i < RequestMove.Count(); i++)
    {
        if(RequestMove[i-1].Layer() != RequestMove[i].Layer())
		{
             throw Exception("只有同级任务才支持此操作！");
        }
    }
    TUpdateNotify UpdateNotify(__FPrjDataChangeLink);
    //先添加摘要任务，再把需要移动的任务一个一个移过去
    TPrjObject& AddAbstract = RequestMove[0].Parent()->InsertChild(
                                     RequestMove[0].Parent()->ChildIndex(RequestMove[0]),
                                     ttAbstractTask);
    Project()->ExpandFoldTasks.Expand(&AddAbstract);
    for(int i = 0; i < RequestMove.Count(); i++)
    {
         RequestMove[i].Parent()->RemoveChild(RequestMove[i]);
         AddAbstract.InsertChildObjectImpl(i, &(RequestMove[i]));
         RequestMove[i].IsModified = true;
    }
    for(int i = 0; i < RequestMove.Count(); i++)
    {
         String TaskID = RequestMove[i].TaskID;
		 int DeleteIndex = DeletedTasks->IndexOf(TaskID);
		 if(DeleteIndex >= 0)
			 DeletedTasks->Delete(DeleteIndex);
    }
    AddAbstract.TaskID=CreateClassID().SubString(2,36);
	AddAbstract.Code = CreateNewTaskCode();
	AddAbstract.PrjCode = PrjCode;
    AddAbstract.Name = "分组任务";
	AddAbstract.SumAll();

    Moving = false;
    return (TAbstractTask*)(&AddAbstract);
}
//------------------------------------------------------------------------------
void TProject::BeginUpdate()
{
    //通知邦定的构件正在更新
    for(int i = 0; i < __FPrjDataChangeLink.Count(); i++)
    {
        __FPrjDataChangeLink[i].BeginUpdate();
    }
}
//------------------------------------------------------------------------------
void TProject::EndUpdate()
{
    //通知邦定的构件更新完毕
    for(int i = 0; i < __FPrjDataChangeLink.Count(); i++)
    {
        __FPrjDataChangeLink[i].EndUpdate();
    }
}
//------------------------------------------------------------------------------
void TProject::ReIndex()
{
    int Start = 0;
     for(int i = 0; i < ChildCount(); i++)
    {
        Start = GetChild(i).ReIndexImpl(Start);
    }
}
//------------------------------------------------------------------------------
void TProject::AddIterator(TIteratorBase*Itr)
{
    FIterators.Add(Itr);
}
//------------------------------------------------------------------------------
void TProject::DeleteIterator(TIteratorBase*Itr)
{
    FIterators.Delete(*Itr);
}
//------------------------------------------------------------------------------
void __fastcall TProject::SetNeedEditStatus(bool AStatus)
{
    FNeedEditStatus = AStatus;
    UpdateEditStatus();
}
//------------------------------------------------------------------------------
void __fastcall TProject::SetSelected(TPrjObject* ATask)
{
    TPrjObject* Old = FSelected;
    FSelected = ATask;
    Selections.Clear();
    Selections.Add(ATask);
    //通知邦定者，选中已改变
    for(int i = 0; i < __FPrjDataChangeLink.Count(); i++)
    {
        __FPrjDataChangeLink[i].SetSelect(ATask, Old);
    }
}
//------------------------------------------------------------------------------
TTask* TProject::TaskByID(String AID,String APrjID)
{
	if(APrjID=="")
	   APrjID=PrjCode;
	for(int i = 0; i < Tasks.Count(); i++)
	{
		if((Tasks[i]->TaskID == AID)&&(Tasks[i]->PrjCode==APrjID))
			return Tasks[i];
	}
	return NULL;
}
//------------------------------------------------------------------------------
void __fastcall TProject::SetCalendarType(String ACalendarType)//日历类型
{
   FCalendarType = ACalendarType;
}
//------------------------------------------------------------------------------
void __fastcall TProject::SetPrjType(String APrjType)//项目类型
{
   FPrjType = APrjType;
}
//------------------------------------------------------------------------------
int TProject::Calculate()
{
   TUpdateNotify UpdateNotify(__FPrjDataChangeLink);
   if(!Calc) return -1;
   return Calc->Calculate();
}
//------------------------------------------------------------------------------
bool TProject::IsCyclic()
{
   if(!Calc) return false;
   return Calc->IsCyclic();
}
String TProject::CreateNewTaskCode()
{
    while(true)
    {
         static char UsedChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                     'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                     'U', 'V', 'W', 'X', 'Y', 'Z'};
         DWORD tick = GetTickCount();
         unsigned int ticklow = tick;
         char Created[7];
         Created[0] = UsedChars[((ticklow << 26 >> 26) % 26)+10];
		 Created[1] = UsedChars[(ticklow << 18 >> 24) % 36];
		 Created[2] = UsedChars[(ticklow << 16 >> 24) % 36];
         Created[3] = UsedChars[(ticklow << 14 >> 24) % 36];
		 Created[4] = UsedChars[(ticklow << 12 >> 24) % 36];
         SYSTEMTIME CurrTime;
         GetLocalTime(&CurrTime);
         Created[5] = UsedChars[(CurrTime.wMilliseconds + CurrTime.wSecond +
                                 CurrTime.wDayOfWeek + CurrTime.wYear) % 36];
		 Created[6] = '\0';
		 TPrjObject* AObj = ObjByCode(String(Created),Code);
         if(!AObj)
             return String(Created);
    }
}
void TProject::RequestUpdate()
{
    if(FOnRequestSave)
        FOnRequestSave(this);
}
void TProject::LoadForeignData(TForeignProject* AForPrj)
{
    if(AForPrj)
    {
         if(FOnLoadData)
             FOnLoadData(this, AForPrj);
    }else
    {
		 throw Exception("TProject::LoadForeignData 外部工程不能为 NULL");
    }
}
TDateTime TProject::GetStateDate()
{
	   //zws 20080711,主要是为了解决状态日计算，提高执行效率
		TPrjObject* t;
		FStateDate=FProject->StartDate-1;
        for(int i = 0; i < InnerObjects.Count(); i++)
        {
            t = InnerObjects[i];
			if(FStateDate<t->ProcessDate)
			  FStateDate=t->ProcessDate;
		}

	 return FStateDate;   //zws20100113 已经有进度截至日期
   /*	 FStateDate=FProject->StartDate-1;
	 if(ProcessDate>FStateDate)
	   return ProcessDate;
	 else
	   return FStateDate; */ 
}
//------------------------------------------------------------------------------
TWBSRule* TProject::GetWBSRule(int index)
{
  if(index >= 0 && index < WBSRules.Count())
    return &(WBSRules[index]);
  else
    return new TWBSRule();
}
//------------------------------------------------------------------------------
//生成WBS
void TProject::BuildChildWBS()
{
  TPrjObject::BuildChildWBS();
}
//------------------------------------------------------------------------------
//TAbstractTask
//------------------------------------------------------------------------------
TAbstractTask::TAbstractTask(TProject&AProject, TPrjObject&AParent, TPrjCalendar*APrjCalendar)
                :TPrjObject(&AProject, &AParent, APrjCalendar),
                 FChilds(OnDeleteChild)
{

}
//------------------------------------------------------------------------------
void TAbstractTask::OnDeleteChild(void*AChild)
{
    delete (TPrjObject*)AChild;
}
//------------------------------------------------------------------------------
TTaskType TAbstractTask::GetTypeImpl()
{
    return ttAbstractTask;
}
//------------------------------------------------------------------------------
TPrjObject& TAbstractTask::GetChildImpl(int Index)
{
    if(Index >= 0 && Index < FChilds.Count())
		return FChilds[Index];
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TAbstractTask::ChildCountImpl()
{
    return FChilds.Count();
}
//------------------------------------------------------------------------------
TPrjObject& TAbstractTask::InsertChildImpl(int Position, TTaskType AType)
{
    TPrjObject* ct;
    switch(AType)
    {
        case ttProject:
        case ttAbstractTask:
            ct = new TAbstractTask(*FProject, *this, FPrjCalendar);
            break;
        case ttTask:
            ct = new TTask(*FProject, *this, FPrjCalendar);
            break;
        case ttForeignProject:
			ct = new TForeignProject(*FProject, *this);
            break;
        default:
			throw Exception("类型错误");
    }
    FChilds.Insert(ct, Position);

	if(!FProject->ReadingData) ct->BuildSelfWBS();

    FProject->OnTaskAdd(*ct);
    return *ct;
}
//------------------------------------------------------------------------------
void TAbstractTask::InsertChildObjectImpl(int Position, TPrjObject*AChild)
{
    FChilds.Insert(AChild, Position);
    AChild->FParent = this;

    if(!FProject->ReadingData)
    {
	  BuildChildWBS();
    }

    FProject->OnTaskAdd(*AChild);
    SumAll();
}
//------------------------------------------------------------------------------
void TAbstractTask::DeleteChildImpl(TPrjObject&AChild)
{
    int index = FChilds.IndexOf(AChild);
    TProject* AProject = Project();
    if(index >= 0)
    {
        FProject->OnTaskDelete(AChild);
        FChilds.Delete(AChild);
    }
    AProject->ReIndex();
    SumAll();
}
//------------------------------------------------------------------------------
void TAbstractTask::RemoveChildImpl(TPrjObject&AChild)
{
    int index = FChilds.IndexOf(AChild);
    TProject* AProject = Project();
    if(index >= 0)
    {
        FProject->OnTaskDelete(AChild);
        FChilds.Remove(AChild);
        AChild.FParent = NULL;
    }
    AProject->ReIndex();
    SumAll();
}
//------------------------------------------------------------------------------
void TAbstractTask::ClearImpl()
{
    TProject* AProject = Project();
    FChilds.Clear();
    AProject->ReIndex();
}
//------------------------------------------------------------------------------
int TAbstractTask::ChildIndexImpl(TPrjObject&AObj)
{
    return FChilds.IndexOf(AObj);
}
//------------------------------------------------------------------------------
void TAbstractTask::Assign(TPrjObject*AObj)
{
    if(!AObj)
		 throw Exception("不能把一个空对象赋值");
    TAbstractTask* AAbsTask = (TAbstractTask*)AObj;
    TPrjObject::Assign(AAbsTask);
}
//------------------------------------------------------------------------------
//TTask
//------------------------------------------------------------------------------
TTask::TTask(TProject&AProject, TPrjObject&AParent, TPrjCalendar*APrjCalendar)
                   : TPrjObject(&AProject, &AParent, APrjCalendar)
					// FFrontTasks(OnFrontTaskDelete)//zws 2003-06-17
					// FLateTasks(OnLaterTaskDelete)
{
   FProject = &AProject;
   FParent = &AParent;
   FEditStatus = esNew;
}
//------------------------------------------------------------------------------
TTask::~TTask()
{
   ClearFrontTask();
   ClearLateTask();
}
//------------------------------------------------------------------------------
TTaskType TTask::GetTypeImpl()
{
   return ttTask;
}
//------------------------------------------------------------------------------
int TTask::__AddLateTask(TTaskLink*ATaskLink)
{
   return FLateTasks.Add(ATaskLink);
}
//------------------------------------------------------------------------------
void TTask::__DelLateTask(TTaskLink*ATaskLink)
{
   FLateTasks.Delete(*ATaskLink);
}
//------------------------------------------------------------------------------
void TTask::OnFrontTaskDelete(void*Data)
{
   TTaskLink* Link = (TTaskLink*)Data;
	Link->Project->OnTaskLinkDelete(*Link);
	delete Link;
}
//------------------------------------------------------------------------------
/*void TTask:: OnLaterTaskDelete(void*Data)
{
   TTaskLink* Link = (TTaskLink*)Data;
   Link->Project->OnTaskLinkDelete(*Link);
   delete Link;
} */
//------------------------------------------------------------------------------
TTaskLink* __fastcall TTask::GetFrontTask(int Index)
{
   return &(FFrontTasks[Index]);
}
//------------------------------------------------------------------------------
TTaskLink* __fastcall TTask::GetLateTask(int Index)
{
   return &(FLateTasks[Index]);
}
//------------------------------------------------------------------------------
int __fastcall TTask::GetFrontTaskCount()
{
   return FFrontTasks.Count();
}
//------------------------------------------------------------------------------
int __fastcall TTask::GetLateTaskCount()
{
    return FLateTasks.Count();
}
//------------------------------------------------------------------------------
TTask* GetChildTaskByID(TPrjObject* AObj, const String& AID,const String& APrjID)
{
    for(int i = 0; i < AObj->ChildCount(); i++)
    {
         if((AObj->GetChild(i).GetType() == ttTask ||
            AObj->GetChild(i).GetType() == ttForeignProject) &&
			(AObj->GetChild(i).TaskID == AID)&&(AObj->GetChild(i).PrjCode==APrjID))
         {
			  return (TTask*)&(AObj->GetChild(i));
         }else
         {
			  TTask* Get = GetChildTaskByID(&(AObj->GetChild(i)), AID,APrjID);
              if(Get)
                  return Get;
		 }
	}
	return NULL;
}
TTask* GetForeignTask(TTask& ATask, const String& AID,const String& APrjID)
{
    TPrjObject* AParent = ATask.Parent();
	while(true)
    {
		 if(AParent)
         {
              if(AParent->GetType() == ttForeignProject)
			  {
				   return GetChildTaskByID(AParent, AID,APrjID);
              }else
				   AParent = AParent->Parent();
         }else
         {
              throw Exception("不是一个外部任务");
         }
    }
}
TTaskLink* TTask::AddFrontTaskImpl(const String& FrontID,const String& FrontPrjID)
{
   String fprjid=FrontPrjID;
   if(FrontPrjID=="")
	 fprjid=PrjCode;
/*	if(!IsForeign())
		 Front = FProject->TaskByID(FrontID,fprjid);
	else
		 Front = GetForeignTask(*this, FrontID,fprjid); */
   if((TaskType != ttTask) && (TaskType!= ttForeignProject)&& (TaskType!= ttMileStone))
	return NULL;

	TTask* Front=(TTask*)FProject->ObjByID(FrontID,fprjid);
	if(Front)
	{
		//判断任务类型是否合法，才能加关系线
		 if((Front->TaskType == ttTask) || (Front->TaskType== ttForeignProject)|| (Front->TaskType== ttMileStone))
		 {
			TTaskLink* r = new TTaskLink(*this, *Front);
			FFrontTasks.Add(r);
			FProject->OnTaskLinkAdd(*r);
			return r;
		 }
	 }
   return NULL;
 }
//------------------------------------------------------------------------------
TTaskLink* TTask::AddLateTaskImpl(const String& LateID,const String& LatePrjID)
{
	String lprjid=LatePrjID;
	if(LatePrjID=="")
	   lprjid=PrjCode;
	TTask* Later;
   /*	if(!IsForeign())
		 Later = FProject->TaskByID(LateID,lprjid);
	else
		 Later = GetForeignTask(*this, LateID,lprjid);*/
   if((TaskType != ttTask) && (TaskType!= ttForeignProject)&& (TaskType!= ttMileStone))
	return NULL;

	 Later=(TTask*)FProject->ObjByID(LateID,lprjid);
	if(Later)
	{
	//判断任务类型是否合法，才能加关系线
		 if((Later->TaskType == ttTask) || (Later->TaskType== ttForeignProject)|| (Later->TaskType== ttMileStone))
		 {
			TTaskLink* r = new TTaskLink(*Later, *this);
			Later->FFrontTasks.Add(r);
			FProject->OnTaskLinkAdd(*r);
			return r;
		 }
	}
   return NULL;
}
//------------------------------------------------------------------------------
void TTask::DelFrontTaskImpl(TTaskLink&ATaskLink)
{
	FFrontTasks.Delete(ATaskLink);
	   //zws2011-03-31
	 ATaskLink.Project->OnTaskLinkDelete(ATaskLink);
	 delete &ATaskLink;
}
//------------------------------------------------------------------------------
void TTask::DelLateTaskImpl(TTaskLink&ATaskLink)
{
	FLateTasks.Delete(ATaskLink);
	ATaskLink.Task->DelFrontTask(ATaskLink);
	   //zws2011-03-31
   //	 ATaskLink.Project->OnTaskLinkDelete(ATaskLink);
   //	 delete &ATaskLink;
}
//------------------------------------------------------------------------------
void TTask::ClearFrontTaskImpl()
{
    FFrontTasks.Clear();
}
//------------------------------------------------------------------------------
void TTask::ClearLateTaskImpl()
{  //zws2010-01-18
 //	while(FLateTasks.Count() > 0)
 //       DelLateTask(FLateTasks[0]);
    FLateTasks.Clear();
}
//------------------------------------------------------------------------------
void TTask::Assign(TPrjObject*AObj)
{
    if(!AObj)
         throw Exception("不能Assign一个空对象");
    TTask* ATask = (TTask*)AObj;
    TPrjObject::Assign(ATask);
}
//------------------------------------------------------------------------------
void TTask::AssignLink(TTask* ATask)
{
   int ThisIndex(0), SourceIndex(0);
   for(; SourceIndex < ATask->FrontTaskCount; SourceIndex++)
   {
	  if(SourceIndex < FrontTaskCount && (ATask->FrontTasks[SourceIndex]->Front->PrjCode == FrontTasks[ThisIndex]->Front->PrjCode)&&(ATask->FrontTasks[SourceIndex]->Front->TaskID == FrontTasks[ThisIndex]->Front->TaskID))
      {//相同，复制
         FrontTasks[ThisIndex]->Assign(ATask->FrontTasks[SourceIndex]);
         ThisIndex++;
	  }else
	  {//不相同，依次向下找
         int i = ThisIndex + 1;
         for(; i < FrontTaskCount; i++)
			if((ATask->FrontTasks[SourceIndex]->Front->PrjCode == FrontTasks[i]->Front->PrjCode)&&(ATask->FrontTasks[SourceIndex]->Front->TaskID == FrontTasks[i]->Front->TaskID))
			   goto labelProcess;
labelProcess:
         if(i >= FrontTaskCount)
         {//没找到相同的，插入
			TTask* NewFront = FProject->TaskByID(ATask->FrontTasks[SourceIndex]->Front->TaskID,ATask->FrontTasks[SourceIndex]->Front->PrjCode);
			if(NewFront)
			{
			 TTaskLink* ALink = new TTaskLink(*this, *NewFront);
			 FFrontTasks.Insert(ALink, ThisIndex);
			 ALink->Assign(ATask->FrontTasks[SourceIndex]);
			 ALink->IsNew = false;
			 ALink->IsModified = false;
			 FProject->OnTaskLinkAdd(*ALink);
			}
            ThisIndex++;
         }else
         {//找到了，删除中间的
            FrontTasks[i]->Assign(ATask->FrontTasks[SourceIndex]);
            for(int j = i-1; j >= ThisIndex; j--)
                FFrontTasks.Delete(j);
            ThisIndex++;
         }
	  }
   }
   //剩下多的，删除
   for(int i = FrontTaskCount - 1; i >= ThisIndex; i--)
	  FFrontTasks.Delete(i);
}
//------------------------------------------------------------------------------
//TTaskLink
//------------------------------------------------------------------------------
__fastcall TTaskLink::TTaskLink(TTask& ATask, TTask&AFront)
                       : FEditStatus(esNew), FType(ftFinishStart),
                         FFreeTime(0), NCPointCount(0),
                         NCBridgePoint(NULL), NCBridgePointCount(0),
                         NCBridgeLineIndex(0)
{
    FProject = ATask.Project();
	FTask = &ATask;
	FFrontTask = &AFront;
	FFrontTask->__AddLateTask(this);
}
//------------------------------------------------------------------------------
__fastcall TTaskLink::~TTaskLink()
{
	if(FFrontTask)
		FFrontTask->__DelLateTask(this);

    if(NCBridgePoint)
		delete [] NCBridgePoint;
}
//------------------------------------------------------------------------------
void TTaskLink::Assign(TTaskLink*ALink)
{
    FType = ALink->Type;
    FFreeTime = ALink->FreeTime;
}
//------------------------------------------------------------------------------
void __fastcall TTaskLink::SetType(TFrontType AType)
{
    if(FType != AType)
    {
        FEditStatus = (TEditStatus) (FEditStatus | esModified);
        FType = AType;
    }
}
//------------------------------------------------------------------------------
void __fastcall TTaskLink::SetFreeTime(double ATime)
{
    if(FFreeTime != ATime)
    {
        FEditStatus = (TEditStatus) (FEditStatus | esModified);
        FFreeTime = ATime;
    }
}
//------------------------------------------------------------------------------
bool __fastcall TTaskLink::GetCritical()
{
    if(!FTask || !FFrontTask || !FFrontTask->Critical||!FTask->Critical)
        return false;
    switch(FType)
    {
        case ftNone:
            return false;
		case ftFinishStart:
			return true;
		case ftStartStart:
            if(FTask->Critical ||
			   WorkDayCount(FTask->StartDate, FFrontTask->StartDate) - abs(int(FreeTime)) <= 0)
				return true;
			break;
		case ftFinishFinish:
			if(FTask->Critical ||
			   WorkDayCount(FTask->EndDate, FFrontTask->EndDate) - abs(int(FreeTime)) <= 0)
				return true;
			break;
		case ftStartFinish:
			if(FTask->Critical ||
			   WorkDayCount(FTask->EndDate, FFrontTask->StartDate) - abs(int(FreeTime)) <= 0)
                return true;
            break;
    }
	return false;
}
//------------------------------------------------------------------------------
void TTaskLink::ResetEditStatus()
{
    FEditStatus = esNone;
}
//------------------------------------------------------------------------------
bool __fastcall TTaskLink::GetIsNew()
{
    return FEditStatus & esNew;
}
//------------------------------------------------------------------------------
void __fastcall TTaskLink::SetIsNew(bool Value)
{
    if(Value)
        FEditStatus = TEditStatus(FEditStatus | esNew);
    else
        FEditStatus = TEditStatus(FEditStatus & (~esNew));
}
//------------------------------------------------------------------------------
bool __fastcall TTaskLink::GetIsModified()
{
    return FEditStatus & esModified;
}
//------------------------------------------------------------------------------
void __fastcall TTaskLink::SetIsModified(bool Value)
{
    if(Value)
        FEditStatus = TEditStatus(FEditStatus | esModified);
    else
        FEditStatus = TEditStatus(FEditStatus & (~esModified));
}
//------------------------------------------------------------------------------
int __fastcall TTaskLink::WorkDayCount(TDateTime Start, TDateTime End)
{
    int Count = 0;
    if(Start == End)
        return 0;
    else if(Start < End)
    {
        for(int i = Start+1; i < End; i++)
            if(FTask->Calendar->IsWorkDay(i))
                ++Count;
    }else{
        for(int i = End+1; i < Start; i++)
            if(FTask->Calendar->IsWorkDay(i))
                ++Count;
    }
    return Count;
}
//------------------------------------------------------------------------------
bool TTaskLink::IsForeign()
{
    if(FTask)
        return FTask->IsForeign();
    else
        throw Exception("数据结构发生错误：TTaskLink::Task == NULL");
}
//------------------------------------------------------------------------------
//TForeignTaskIterator
//------------------------------------------------------------------------------
TForeignTaskIterator::TForeignTaskIterator(TProject&AProject, TForeignProject&AForeign)
                     :TIteratorBase(AProject), FForeignProject(AForeign)
{
}
//------------------------------------------------------------------------------
TTask& TForeignTaskIterator::operator [] (int Index)
{
    throw Exception("未实现！");
}
//------------------------------------------------------------------------------
int TForeignTaskIterator::Count()
{
    throw Exception("未实现！");
}
//------------------------------------------------------------------------------
void TForeignTaskIterator::OnTaskAdd(TPrjObject&)
{
}
//------------------------------------------------------------------------------
void TForeignTaskIterator::OnTaskDelete(TPrjObject&)
{
}
//------------------------------------------------------------------------------
void TForeignTaskIterator::OnTaskLinkAdd(TTaskLink&)
{
}
//------------------------------------------------------------------------------
void TForeignTaskIterator::OnTaskLinkDelete(TTaskLink&)
{
}
//------------------------------------------------------------------------------
//TForeignProject
//------------------------------------------------------------------------------
TForeignProject::TForeignProject(TProject&AProject, TPrjObject&AParent)
				  :TTask(AProject, AParent, &FPrjCalendarObj),FChilds(OnDeleteChild)

{
 LoadedData=false;
}
//------------------------------------------------------------------------------
void TForeignProject::OnDeleteChild(void*AChild)
{
    delete (TPrjObject*)AChild;
}
//------------------------------------------------------------------------------
TTaskType TForeignProject::GetTypeImpl()
{
    return ttForeignProject;
}
//------------------------------------------------------------------------------
TPrjObject& TForeignProject::GetChildImpl(int Index)
{
    if(Index >= 0 && Index < FChilds.Count())
        return FChilds[Index];
    else
		throw Exception("序号超出范围");
}
//------------------------------------------------------------------------------
int TForeignProject::ChildCountImpl()
{
    return FChilds.Count();
}
//------------------------------------------------------------------------------
TPrjObject& TForeignProject::InsertChildImpl(int Position, TTaskType AType)
{
    TPrjObject* ct;
    switch(AType)
    {
        case ttProject:
        case ttAbstractTask:
			ct = new TAbstractTask(*FProject, *this, &FPrjCalendarObj);
            break;
        case ttTask:
            ct = new TTask(*FProject, *this, &FPrjCalendarObj);
            break;
        case ttForeignProject:
			ct = new TForeignProject(*FProject, *this);
            break;
        default:
			throw Exception("类型错误");
    }
    FChilds.Insert(ct, Position);

	if(!FProject->ReadingData) ct->BuildSelfWBS();
    
    FProject->OnTaskAdd(*ct);
    return *ct;
}
//------------------------------------------------------------------------------
void TForeignProject::InsertChildObjectImpl(int Position, TPrjObject*AChild)
{
    FChilds.Insert(AChild, Position);
    AChild->FParent = this;

    if(!FProject->ReadingData)
    {
	  BuildChildWBS();
    }

    FProject->OnTaskAdd(*AChild);
}
//------------------------------------------------------------------------------
void TForeignProject::DeleteChildImpl(TPrjObject&AChild)
{
    AChild.Project()->OnTaskDelete(AChild);
    FChilds.Delete(AChild);
    Project()->ReIndex();
}
//------------------------------------------------------------------------------
void TForeignProject::RemoveChildImpl(TPrjObject&AChild)
{
    AChild.Project()->OnTaskDelete(AChild);
    FChilds.Remove(AChild);
    AChild.FParent = NULL;
    Project()->ReIndex();
}
//------------------------------------------------------------------------------
void TForeignProject::ClearImpl()
{
    FChilds.Clear();
    Project()->ReIndex();
}
//------------------------------------------------------------------------------
int TForeignProject::ChildIndexImpl(TPrjObject&AObj)
{
    return FChilds.IndexOf(AObj);
}
//------------------------------------------------------------------------------
int TForeignProject::ReIndexImpl(int Start)
{
    if(FIndex != Start && Moving)
        IsModified = true;
    FIndex = Start;
    return Start+1;
}
//------------------------------------------------------------------------------
void TForeignProject::Assign(TPrjObject*AObj)
{
    if(!AObj)
         throw Exception("不能Assing一个空对象");
	TForeignProject* AFor = (TForeignProject*)AObj;
    LoadedData = AFor->LoadedData;
    TTask::Assign(AFor);
}
//-----------------------------------------------------------------------
//   TPrjDataChangeLink
//-----------------------------------------------------------------------
TPrjDataChangeLink::TPrjDataChangeLink(TProject*AProject)
{
   FProject = AProject;
   Bind();
}
//------------------------------------------------------------------------------
TPrjDataChangeLink::~TPrjDataChangeLink()
{
   NoBind();
}
//------------------------------------------------------------------------------
void TPrjDataChangeLink::SetProject(TProject*AProject)
{
   //如果FProject为真，则取消邦定
   NoBind();
   FProject = AProject;
   //绑定
   Bind();
}
//------------------------------------------------------------------------------
void TPrjDataChangeLink::NoBind()
{
   if(FProject)
   {
      FProject->__FPrjDataChangeLink.Delete(*this);
   }
}
//------------------------------------------------------------------------------
void TPrjDataChangeLink::Bind()
{
   if(FProject)
      FProject->__FPrjDataChangeLink.Add(this);
}
//------------------------------------------------------------------------------
// TCalculator
//------------------------------------------------------------------------------
int TCalculator::Calculate()
{
   if(FProject->Tasks.Count()==0)   //没有任务
   {
    FProject->StartDate = FProject->PBeginDate;
	FProject->EndDate = FProject->PEndDate;
	FProject->ALAP_StartDate=FProject->StartDate;
	FProject->ALAP_EndDate = FProject->EndDate;
	FProject->ASAP_StartDate = FProject->StartDate;
	FProject->ASAP_EndDate = FProject->EndDate;
	int wdays=0;
	TDateTime dt=FProject->StartDate;
	for(dt=FProject->StartDate;dt<FProject->EndDate;dt++)
	{
		if (FProject->Calendar->IsWorkDay(dt)) {  //判断是否是有效工作日
			wdays++;
		}
	}
	FProject->CostDays=wdays;
	return true;
   }
   int Rtn = CalculateImpl();
   if(FProject->PlanType == ptALAP)
	{
	  FProject->StartDate = FProject->ALAP_StartDate;
	  FProject->EndDate   = FProject->ALAP_EndDate;
	 }
	else if(FProject->PlanType == ptASAP)
	{
	  FProject->StartDate = FProject->ASAP_StartDate;
	  FProject->EndDate   = FProject->ASAP_EndDate;
	}
	//计算项目的整体计算工期。
	int iSumCostDays=0;
	for(TDateTime i = FProject->StartDate; i <= FProject->EndDate; i++)
	{
	 if(FProject->Calendar->IsWorkDay(i))
	 {
	  iSumCostDays++;
	  }
	 }
	 FProject->CostDays=iSumCostDays;
		 //计算项目的整体计算实际工期。
         iSumCostDays=0;
         if(FProject->TaskStatus!=tsNotStart)
         {
           if(FProject->TaskStatus == tsOvered)
		   {
				for(TDateTime i = FProject->FactStartDate;i<FProject->FactEndDate;i++)
				{
				 if(FProject->Calendar->IsWorkDay(i))
				 {
					iSumCostDays++;
				 }
			    }
		   }
		   else
		   {
			   for(TDateTime i = FProject->FactStartDate;i<FProject->ProcessDate;i++)
			   {
				 if(FProject->Calendar->IsWorkDay(i))
				 {
					iSumCostDays++;
				 }
			   }
		   }
		 }
		 FProject->FactCostDays=iSumCostDays;
		 CalcTaskFreeDays(); //计算浮时
         CalculatePert();//计算pert预期工期

   return Rtn;
}
void TCalculator::CalculatePert()
{
     TTask* ATask;
     double SDate=0,EDate=0,SQ=0,EQ=0;
     ResetCalcFlags();
     for(int i=0;i<FProject->Tasks.Count();i++)
     {
	  ATask = FProject->Tasks[i];
      if(ATask->AnticipateCostDays==0||ATask->OptimismCostDays==0||ATask->PessimismCostDays==0)
        continue;
      CalcTaskPert(ATask,SDate,EDate,SQ,EQ);
      ATask->PertStartQ = SQ;
      ATask->PertEndQ =EQ;
      ATask->PertStartTime = SDate;
      ATask->PertEndTime = EDate;
     }
}
//------------------------------------------------------------------------------
int TCalculator::CalculateImpl()
{
	if(IsCyclic())
    {
      throw Exception("系统在下列任务序列中检测到循环连接：\n"+GetErrorLinks()+"\n项目中不允许出现任务循环连接。请删除这些错误的连接关系");
    }
    int i;
    TTask* ATask;
	TDateTime SDate,EDate;
	switch(FProject->PlanType)
	{
	  case ptASAP: 	//从开始预定日期编排计划的项目
	  {
		  b_StartDate = FProject->PBeginDate;
		while(!(FProject->Calendar->IsWorkDay(b_StartDate)))
		  b_StartDate = WorkDayOffset(b_StartDate,2);
        ResetCalcFlags(); //重置计算标志
		//计算任务最早开工工期
        for(i=0;i<=FProject->Tasks.Count()-1;i++)
        {
          ATask = FProject->Tasks[i];

          PreCalcTask(ATask,SDate,EDate,ptASAP);
		  ATask->ASAP_StartDate = ATask->TempStartDate;
          ATask->ASAP_EndDate = ATask->TempEndDate;
        }
		FProject->ASAP_EndDate=GetMaxDate();     //得到项目最早时间
		FProject->ASAP_StartDate=GetMinDate();
		b_EndDate = FProject->ASAP_EndDate;//GetMaxDate();
		ResetCalcFlags();
		//计算任务最晚完工工期
        for(i=0;i<=FProject->Tasks.Count()-1;i++)
        {
          ATask = FProject->Tasks[i];
          PreCalcTask(ATask,SDate,EDate,ptALAP);
          ATask->ALAP_StartDate = ATask->TempStartDate;
          ATask->ALAP_EndDate = ATask->TempEndDate;
		}
		FProject->ALAP_EndDate=GetMaxDate();      //得到项目最晚时间
		FProject->ALAP_StartDate=GetMinDate();

		ResetCalcFlags();
		//根据任务实际的计划方法，将最早开工或最晚完工工期赋给任务工期
		for(i=0;i<=FProject->Tasks.Count()-1;i++)
		{
		  ATask = FProject->Tasks[i];
		  CalcTask(ATask,SDate,EDate,ptASAP);
		  //设置关键任务标志：
		  //具有下列特点之一的任务即为关键任务：
		  //1.最早开工和最完完工，工期计划完全相同（没有浮时）
		  //2.当项目计划方法时从开始日期编排，任务计划方法是最迟完工
		  //3.当项目计划方法时从结束日期编排，任务计划方法是最早开工
		  if((ATask->ASAP_StartDate == ATask->ALAP_StartDate && ATask->ASAP_EndDate == ATask->ALAP_EndDate)
			 || ATask->PlanType == ptALAP)
			ATask->Critical = true;
		  else
			ATask->Critical = false;

		}
	  }
	  break;
	  case ptALAP:
	  {
		b_EndDate = FProject->PEndDate;

		while(!(FProject->Calendar->IsWorkDay(b_EndDate)))
		  b_EndDate = WorkDayOffset(b_EndDate,-2);

        ResetCalcFlags();

        for(i=0;i<=FProject->Tasks.Count()-1;i++)
        {
          ATask = FProject->Tasks[i];
          PreCalcTask(ATask,SDate,EDate,ptALAP);
          ATask->ALAP_StartDate = ATask->TempStartDate;
          ATask->ALAP_EndDate = ATask->TempEndDate;
		}

		b_StartDate = GetMinDate();
		FProject->ALAP_EndDate=GetMaxDate();      //得到项目最晚时间
		FProject->ALAP_StartDate=b_StartDate;//GetMinDate();

        ResetCalcFlags();
		for(i=0;i<=FProject->Tasks.Count()-1;i++)
        {
          ATask = FProject->Tasks[i];
          PreCalcTask(ATask,SDate,EDate,ptASAP);
          ATask->ASAP_StartDate = ATask->TempStartDate;
          ATask->ASAP_EndDate = ATask->TempEndDate;
        }
 		FProject->ASAP_EndDate=GetMaxDate();     //得到项目最早时间
		FProject->ASAP_StartDate=GetMinDate();

		ResetCalcFlags();
		for(i=0;i<=FProject->Tasks.Count()-1;i++)
		{
		  ATask = FProject->Tasks[i];
		  CalcTask(ATask,SDate,EDate,ptALAP);
		  if((ATask->ASAP_StartDate == ATask->ALAP_StartDate && ATask->ASAP_EndDate == ATask->ALAP_EndDate)
			|| ATask->PlanType == ptASAP)
		   ATask->Critical = true;
		  else
		   ATask->Critical = false;
		}
	  }
	  break;
   }
  return true;
}
//------------------------------------------------------------------------------
void TCalculator::PreCalcTask(TTask *ATask,TDateTime &SDate, TDateTime &EDate,
                         BYTE Plan)
{
  if(ATask==NULL)
    throw Exception("错误：没有找到任务！");

  if(ATask->Calced)
  {
    SDate = ATask->TempStartDate;
    EDate = ATask->TempEndDate;
    return;
  }

  switch(Plan)
  {
    case ptASAP:
      SDate = b_StartDate;
      EDate = WorkDayOffset(SDate, ATask->CostDays);
      //如果前置任务为空，则开始日期指定为工程开始日期
      if(ATask->FrontTaskCount>0)
      { //前置任务不为空，则先遍历所有前置任务，计算出前置任务的工期
        TDateTime PrevStartDate,PrevEndDate, LimitStartDate, LimitEndDate, tmpDate;
        LimitStartDate = 0;
        LimitEndDate = 0;
        TTask * FrontTask;
        TFrontType ft;
        int Delay;
        /*开始遍历*/
        for(int i=0;i<=ATask->FrontTaskCount-1;i++)
        {
          FrontTask = ATask->FrontTasks[i]->Front;
          ft = ATask->FrontTasks[i]->Type;
          Delay = ATask->FrontTasks[i]->FreeTime;
          //递归计算该前置任务（如果该前置任务已经计算过，该函数直接返回）
          PreCalcTask(FrontTask,PrevStartDate,PrevEndDate,Plan);
          if(FrontTask->CostDays == 0) //MILESTONE
          {
             PrevEndDate = PrevStartDate-1;
          }
          //根据连接类型计算
          switch(ft)
          {
			case ftFinishStart:
			  //计算延迟
			  if(Delay>=-1)
				PrevEndDate = WorkDayOffset(PrevEndDate,Delay+2);
			  else
				PrevEndDate = WorkDayOffset(PrevEndDate,Delay);
			  //计算最早开始时间
              if(PrevEndDate>=LimitStartDate)
              {
                LimitStartDate = PrevEndDate;
                if(LimitStartDate < SDate)
                {
                  LimitStartDate = SDate;
                }
               //计算该开始时间对应的结束时间
				tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                //更新结束时间
                if(tmpDate > LimitEndDate)
                   LimitEndDate = tmpDate;
              }
              break;

			case ftStartStart:
			  if(Delay>=0)
				PrevStartDate = WorkDayOffset(PrevStartDate,Delay+1);
			  else
				PrevStartDate = WorkDayOffset(PrevStartDate,Delay-1);
              if(PrevStartDate>LimitStartDate)
              {
                LimitStartDate = PrevStartDate;
                if(LimitStartDate < SDate)
                  LimitStartDate = SDate;
                tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                if(tmpDate > LimitEndDate)
                   LimitEndDate = tmpDate;
              }
              break;
			case ftStartFinish:
			  if(Delay>=1)
				PrevStartDate = WorkDayOffset(PrevStartDate,Delay+0);
			  else
				PrevStartDate = WorkDayOffset(PrevStartDate,Delay-2);

              if(PrevStartDate>LimitEndDate)
              {
                LimitEndDate = PrevStartDate;
                tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   //算结束时间
                   tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                   if(tmpDate > LimitEndDate)
                     LimitEndDate = tmpDate;
                }
                else if(tmpDate >LimitStartDate)
                   LimitStartDate = tmpDate;
              }
              break;
			case ftFinishFinish:
			  if(Delay>=0)
				PrevEndDate = WorkDayOffset(PrevEndDate,Delay+1);
			  else
				PrevEndDate = WorkDayOffset(PrevEndDate,Delay-1);
			  if(PrevEndDate>LimitEndDate)
              {
                LimitEndDate = PrevEndDate;
                tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
				   tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                   if(tmpDate > LimitEndDate)
					 LimitEndDate = tmpDate;
                }
                else if(tmpDate >LimitStartDate)
                      LimitStartDate = tmpDate;
              }
              break;
            case ftNone:
			  break;
          }
        }//for

        /*计算最早开始时间、结束时间*/
        //工期余量大于工期
        if(WorkDayOffset(LimitStartDate,ATask->CostDays)<=LimitEndDate)
        {
           SDate = LimitStartDate;
           EDate = WorkDayOffset(SDate,ATask->CostDays);
        }
        else  //右对齐
        {
          EDate = LimitEndDate;
          SDate = WorkDayOffset(EDate, -ATask->CostDays);
        }

		if(FProject->PlanType == ptALAP)  //如果开始时间小于项目开始时间，则更新为项目开始时间
        {
          if(EDate > b_EndDate)
          {
            EDate = b_EndDate;
            SDate = WorkDayOffset(EDate,-(ATask->CostDays));
		  }
        }
        //-----------------------------------
      }//else
      switch(ATask->PlanType)
      {
        case ptMSO :
            SDate = ATask->LimitedDate;
			EDate = WorkDayOffset(SDate,ATask->CostDays);
          break;
        case ptMFO :
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          break;
        case ptBSO :
          if(SDate>ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
			EDate = WorkDayOffset(SDate,ATask->CostDays);
          }
          break;
        case ptBFO :
          if(EDate>ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          }
          break;
        case ptASO :
          if(SDate<ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
          }
          break;
        case ptAFO :
          if(EDate<ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          }
          break;
      }//switch
	  //赋值并标记为"已经计算"
	  //判断任务是否完工了
	  if(ATask->TaskStatus==tsOvered)
	  {
		if(ATask->FactEndDate>EDate)
		   EDate=ATask->FactEndDate;
		if(ATask->CostDays!=ATask->FactCostDays)
			 ATask->CostDays=ATask->FactCostDays;
	  }
	  if(ATask->TaskStatus!=tsNotStart)
	  {
		if(ATask->FactStartDate<SDate)
		{
		  if(int(ATask->FactStartDate)>5)//判断是否有效开始日期
			SDate=ATask->FactStartDate;
		  if(ATask->CostDays<ATask->FactCostDays)
			 ATask->CostDays=ATask->FactCostDays;
		  EDate = WorkDayOffset(SDate,ATask->CostDays);
		}
	  }
	  ATask->TempStartDate = SDate;
      ATask->TempEndDate = EDate;
      ATask->Calced = true;
	  break;
    case ptALAP:
      EDate = b_EndDate;
      SDate = WorkDayOffset(EDate, -ATask->CostDays);
      //如果后置任务为空，则结束日期指定为工程结束日期
      if(ATask->LateTaskCount> 0)
      {  //后置任务不为空，则先遍历所有后置任务，计算出后置任务的工期
        TDateTime NextStartDate,NextEndDate, LimitStartDate, LimitEndDate, tmpDate;
        LimitStartDate = 401769;
        LimitEndDate = 401769;
        TTask * LateTask;
        TFrontType ft;
        int Delay;
        int i;
        /*开始遍历*/
        for(i=0;i<=ATask->LateTaskCount-1;i++)
        {
          LateTask = ATask->LateTasks[i]->Task;
          ft = ATask->LateTasks[i]->Type;
          Delay = ATask->LateTasks[i]->FreeTime;
          //递归计算该后置任务（如果该后置任务已经计算过，该函数直接返回）
          PreCalcTask(LateTask,NextStartDate,NextEndDate,Plan);
          //根据连接类型计算
          switch(ft)
          {
			case ftFinishStart:
              //计算延迟
              if(ATask->CostDays != 0)
              {
                if(Delay>=-1)
				  NextStartDate = WorkDayOffset(NextStartDate,-(Delay+2));
                else
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay));
              }
              else
              {
                if(Delay>=-1)
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay+1));
                else
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay));
              }
              //计算最晚结束时间
              if(NextStartDate<=LimitEndDate)
              {
                LimitEndDate = NextStartDate;
                //计算出的结束时间大于项目结束时间，则调整为项目结束时间
                if(LimitEndDate > EDate)
                  LimitEndDate = EDate;
                //计算该结束时间对应的开始时间
                tmpDate = WorkDayOffset(LimitEndDate,-(ATask->CostDays));
                //更新开始时间
                if(tmpDate < LimitStartDate)
                   LimitStartDate = tmpDate;
              }
              break;
            case ftStartStart:
              if(Delay>=0)
                NextStartDate = WorkDayOffset(NextStartDate,-(Delay+1));
              else
                NextStartDate = WorkDayOffset(NextStartDate,-(Delay-1));

              if(NextStartDate<LimitStartDate)
              {
                LimitStartDate = NextStartDate;

                tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);

                if(tmpDate > EDate)
                {
                  LimitEndDate = EDate;
                  tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                  if(tmpDate < LimitStartDate)
                    LimitStartDate = tmpDate;
                }
                else if(tmpDate < LimitEndDate)
                   LimitEndDate = tmpDate;
              }
              break;
            case ftStartFinish:
              if(Delay>=1)
                NextEndDate = WorkDayOffset(NextEndDate,-(Delay+0));
              else
                NextEndDate = WorkDayOffset(NextEndDate,-(Delay-2));

              if(NextEndDate < LimitStartDate)
              {
				LimitStartDate = NextEndDate;
                tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);

                if(tmpDate>EDate)
                {
                   LimitEndDate = EDate;
                   tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                   if(tmpDate < LimitStartDate)
                     LimitStartDate = tmpDate;
                }
                else if(tmpDate < LimitEndDate)
                      LimitEndDate = tmpDate;
              }
              break;
			case ftFinishFinish:
              if(ATask->CostDays != 0)
              {
                if(Delay>=0)
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay+1));
                else
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay-1));
              }
              else
              {
                if(Delay>=0)
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay+2));
                else
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay));
			  }
             if(NextEndDate<LimitEndDate)
              {
                LimitEndDate = NextEndDate;
                if(LimitEndDate>EDate)
                  LimitEndDate = EDate;
                tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                if(tmpDate < LimitStartDate)
                {
                   LimitStartDate = tmpDate;
                }
              }
              break;
            case ftNone:
			  break;
          }
        }
        /*计算最早开始时间、结束时间*/
        //工期余量大于工期
        if(WorkDayOffset(LimitStartDate,ATask->CostDays)<=LimitEndDate)
        {
           EDate = LimitEndDate;
           SDate = WorkDayOffset(EDate,-ATask->CostDays);
        }
        else
        {
           SDate = LimitStartDate;
		   EDate = WorkDayOffset(SDate, ATask->CostDays);
		}

		if(FProject->PlanType == ptASAP)  //如果开始时间小于项目开始时间，则更新为项目开始时间
        {
          if(SDate < b_StartDate)
          {
            SDate = b_StartDate;
            EDate = WorkDayOffset(SDate, ATask->CostDays);
            //无需再检验EndDate,一定在正确区间内
          }
        }
	  }
	  switch(ATask->PlanType)
      {
        case ptMSO :
			SDate = ATask->LimitedDate;
			EDate = WorkDayOffset(SDate,ATask->CostDays);
          break;
        case ptMFO :
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          break;
        case ptBSO :
          if(SDate>ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
          }
          break;
        case ptBFO :
          if(EDate>ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          }
          break;
        case ptASO :
          if(SDate<ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
			EDate = WorkDayOffset(SDate,ATask->CostDays);
          }
          break;
        case ptAFO :
          if(EDate<ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          }
          break;
      }//switch
	  //赋值并标记为"已经计算"
	  if(ATask->TaskStatus==tsOvered)
	  {
		if(ATask->FactEndDate<EDate)
		{
		   if(int(ATask->FactEndDate)>5)//判断是否有效结束日期
			  EDate=ATask->FactEndDate;
		}
		if(ATask->CostDays!=ATask->FactCostDays)
			 ATask->CostDays=ATask->FactCostDays;
	  }
	  if(ATask->TaskStatus!=tsNotStart)
	  {
		if(ATask->FactStartDate>SDate)
		{
		  if(int(ATask->FactStartDate)>5) //判断是否有效开始日期
			 SDate=ATask->FactStartDate;
		  if(ATask->CostDays<ATask->FactCostDays)
			 ATask->CostDays=ATask->FactCostDays;
		  EDate = WorkDayOffset(SDate,ATask->CostDays);
		}
	  }
	  else //过了进度截至日还没有开工
	  {
		 if(ATask->ProcessDate>SDate)
		 {
			 SDate=ATask->ProcessDate;
			 EDate = WorkDayOffset(SDate,ATask->CostDays);
		 }
	  }
      ATask->TempStartDate = SDate;
      ATask->TempEndDate = EDate;
	  ATask->Calced = true;
      break;
    default:
	  throw Exception("T计算器不支持这种类型!");
  }

}
void TCalculator::CalcTaskPert(TTask *ATask,double &SDate, double &EDate,double &SQ,double &EQ)
{
  if(ATask==NULL)
	throw Exception("错误：没有找到任务！");

  if(ATask->Calced)
  {
    SQ = ATask->PertStartQ;
    EQ = ATask->PertEndQ;
    SDate = ATask->PertStartTime;
    EDate = ATask->PertEndTime;
    return;
  }
      //如果前置任务为空，则开始日期指定为工程开始日期
      if(ATask->FrontTaskCount == 0)
      {
        SDate = 0;
        SQ = 0;
        EDate = ATask->PertDuration;  
        EQ = ATask->PertDurationQ;
      }
      else //前置任务不为空，则先遍历所有前置任务，计算出前置任务的工期
      {
        double PrevStartDate,PrevEndDate, LimitStartDate, LimitEndDate, LimitSQ,LimitEQ,tmpDate,tmpQ,PrevSQ,PrevEQ;
        LimitStartDate = 0;
        LimitEndDate = 0;
        LimitEQ = 0;
        LimitSQ = 0;
        TTask * FrontTask;
        TFrontType ft;
        int Delay;
        int i;
		/*开始遍历*/
        for(i=0;i<=ATask->FrontTaskCount-1;i++)
        {
          FrontTask = ATask->FrontTasks[i]->Front;
          ft = ATask->FrontTasks[i]->Type;
          Delay = ATask->FrontTasks[i]->FreeTime;
          //递归计算该前置任务（如果该前置任务已经计算过，该函数直接返回）
          CalcTaskPert(FrontTask,PrevStartDate,PrevEndDate,PrevSQ,PrevEQ);
          if(FrontTask->CostDays == 0) //MILESTONE
          {
             PrevEndDate = PrevStartDate;
             PrevEQ=PrevSQ;
          }
          //根据连接类型计算
          switch(ft)
          {
            case ftFinishStart:
              //计算延迟
	      PrevEndDate = PrevEndDate+Delay;
	      //LimitEQ=PrevEQ;
              //计算最早开始时间
              if(PrevEndDate>=LimitStartDate)
              {
                LimitStartDate = PrevEndDate;
                LimitSQ = PrevEQ;
                if(LimitStartDate < SDate)
                {
                  LimitStartDate = SDate;
                  LimitSQ= SQ;
		}
               //计算该开始时间对应的结束时间
                tmpDate = LimitStartDate+ATask->PertDuration;
                tmpQ = LimitSQ+ATask->PertDurationQ;
                //更新结束时间
                if(tmpDate > LimitEndDate)
                {
                   LimitEndDate = tmpDate;
                   LimitEQ = tmpQ;
                }   
              }
              break;
            case ftStartStart:
                PrevStartDate = PrevStartDate+Delay;
			  if(PrevStartDate>LimitStartDate)
              {
                LimitStartDate = PrevStartDate;
                LimitSQ = PrevSQ;
                if(LimitStartDate < SDate)
                {
                  LimitStartDate = SDate;
                  LimitSQ=SQ;
                }  
                tmpDate = LimitStartDate+ATask->PertDuration;
                tmpQ=LimitSQ+ATask->PertDurationQ;
                if(tmpDate > LimitEndDate)
                {
                   LimitEndDate = tmpDate;
                   LimitEQ = tmpQ;
                }   
              }
              break;
            case ftStartFinish:
                PrevStartDate = PrevStartDate+Delay;
			  if(PrevStartDate>LimitEndDate)
              {
                LimitEndDate = PrevStartDate;
                LimitEQ = PrevSQ;
				tmpDate = LimitEndDate-ATask->PertDuration;
                tmpQ=LimitEQ-ATask->PertDurationQ;
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   LimitSQ = SQ;
                   //算结束时间
                   tmpDate = LimitStartDate+ATask->PertDuration;
                   tmpQ = LimitSQ+ATask->PertDurationQ;
                   if(tmpDate > LimitEndDate)
                   {
                     LimitEndDate = tmpDate;
                     LimitEQ = tmpQ;
                   }  
                }
                else if(tmpDate >LimitStartDate)
                {
                      LimitStartDate = tmpDate;
                      LimitSQ = tmpQ;
                }
              }
              break;
            case ftFinishFinish:
               PrevEndDate = PrevEndDate+Delay;
			  if(PrevEndDate>LimitEndDate)
              {
                LimitEndDate = PrevEndDate;
                LimitEQ = PrevEQ;
                tmpDate = LimitEndDate-ATask->PertDuration;
                tmpQ= LimitEQ-ATask->PertDurationQ;
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   LimitSQ = SQ;
                   tmpDate = LimitStartDate+ATask->PertDuration;
                   tmpQ= LimitSQ+ATask->PertDurationQ;
                   if(tmpDate > LimitEndDate)
                   {
                     LimitEndDate = tmpDate;
                     LimitEQ = tmpQ;
                   }
                }
                else if(tmpDate >LimitStartDate)
                {
                      LimitStartDate = tmpDate;
                      LimitSQ = tmpQ;
                }
              }
              break;
            case ftNone:
			  break;
          }
        }//for
          if(ATask->PlanType == ptASAP)
          {
            SDate = LimitStartDate;
            EDate = SDate+ATask->PertDuration;
            SQ = LimitSQ;
            EQ = SQ+ATask->PertDurationQ;
         }
          else if(ATask->PlanType == ptALAP)
          {
            EDate = ATask->PertEndTime;
            SDate = EDate-ATask->PertDuration;
            SQ = ATask->PertStartQ;
            EQ = ATask->PertEndQ;
          }
          else
          {
            SDate = LimitStartDate;
            EDate = SDate+ATask->PertDuration;
            SQ = LimitSQ;
            EQ = LimitSQ+ATask->PertDurationQ;
          }
      }//else
        double LimitedDate=0;
      switch(ATask->PlanType)
      {
        case ptMSO :
            for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
            SDate = LimitedDate;
            EDate = SDate+ATask->PertDuration;
            SQ=0;
            EQ =SQ+ATask->PertDurationQ;
          break;
        case ptMFO :
             for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedEndDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
            EDate = LimitedDate;
            SDate = EDate-ATask->PertDuration;
            SQ=0 ;
            EQ=SQ+ATask->PertDurationQ;
           break;
        case ptBSO :
           for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(SDate>LimitedDate)
          {
            SDate = LimitedDate;
            EDate = SDate+ATask->PertDuration;
            SQ = 0;
            EQ =SQ+ ATask->PertDurationQ;
           }
          break;
        case ptBFO :
          for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedEndDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(EDate>LimitedDate)
          {
            EDate = LimitedDate;
            SDate = EDate-ATask->PertDuration;
            SQ = 0;
            EQ =SQ+ ATask->PertDurationQ;
          }
          break;
        case ptASO :
           for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(SDate<LimitedDate)
          {
            SDate = LimitedDate;
            EDate = SDate+ATask->PertDuration;
            SQ = 0;
            EQ =SQ+ ATask->PertDurationQ;
          }
          break;
        case ptAFO :
          for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedEndDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(EDate<LimitedDate)
          {
            EDate = LimitedDate;
            SDate = EDate-ATask->PertDuration;
            SQ=0;
            EQ =SQ+ATask->PertDurationQ;
          }
          break;
      }//switch
      //赋值并标记为"已经计算"
      ATask->Calced = true;
      ATask->PertStartQ=SQ;
      ATask->PertEndQ=EQ;
      ATask->PertStartTime=SDate;
      ATask->PertEndTime=EDate;

}
//------------------------------------------------------------------------------
void TCalculator::CalcTask(TTask *ATask,TDateTime &SDate, TDateTime &EDate,
                         BYTE Plan)
{
  if(ATask==NULL)
	throw Exception("没有找到任务！");

  if(ATask->Calced)
  {
    SDate = ATask->StartDate;
    EDate = ATask->EndDate;
    return;
  }
  switch(Plan)
  {
    case ptASAP:
      SDate = b_StartDate;
      EDate = WorkDayOffset(SDate,ATask->CostDays);
      //如果前置任务为空，则开始日期指定为工程开始日期
      if(ATask->FrontTaskCount == 0)
      {
        SDate = GetProperStartDate(ATask);
        EDate = GetProperEndDate(ATask);
      }
      else //前置任务不为空，则先遍历所有前置任务，计算出前置任务的工期
      {
        TDateTime PrevStartDate,PrevEndDate, LimitStartDate, LimitEndDate, tmpDate;
        LimitStartDate = 0;
        LimitEndDate = 0;
        TTask * FrontTask;
        TFrontType ft;
        int Delay;
        int i;
		/*开始遍历*/
        for(i=0;i<=ATask->FrontTaskCount-1;i++)
        {
          FrontTask = ATask->FrontTasks[i]->Front;
          ft = ATask->FrontTasks[i]->Type;
          Delay = ATask->FrontTasks[i]->FreeTime;
          //递归计算该前置任务（如果该前置任务已经计算过，该函数直接返回）
		  CalcTask(FrontTask,PrevStartDate,PrevEndDate,Plan);
          if(FrontTask->CostDays == 0) //MILESTONE
          {
             PrevEndDate = PrevStartDate-1;
          }
          //根据连接类型计算
          switch(ft)
          {
            case ftFinishStart:
              //计算延迟
              if(Delay>=-1)
                PrevEndDate = WorkDayOffset(PrevEndDate,Delay+2);
              else
                PrevEndDate = WorkDayOffset(PrevEndDate,Delay);
              //计算最早开始时间
              if(PrevEndDate>=LimitStartDate)
              {
                LimitStartDate = PrevEndDate;
                if(LimitStartDate < SDate)
                {
                  LimitStartDate = SDate;
				}
               //计算该开始时间对应的结束时间
                tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                //更新结束时间
                if(tmpDate > LimitEndDate)
                   LimitEndDate = tmpDate;
              }
              break;
            case ftStartStart:
              if(Delay>=0)
                PrevStartDate = WorkDayOffset(PrevStartDate,Delay+1);
              else
                PrevStartDate = WorkDayOffset(PrevStartDate,Delay-1);
              if(PrevStartDate>LimitStartDate)
              {
                LimitStartDate = PrevStartDate;
                if(LimitStartDate < SDate)
                  LimitStartDate = SDate;
                tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                if(tmpDate > LimitEndDate)
                   LimitEndDate = tmpDate;
              }
              break;
            case ftStartFinish:
              if(Delay>=1)
                PrevStartDate = WorkDayOffset(PrevStartDate,Delay+0);
              else
                PrevStartDate = WorkDayOffset(PrevStartDate,Delay-2);

              if(PrevStartDate>LimitEndDate)
              {
                LimitEndDate = PrevStartDate;
                tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   //算结束时间
                   tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                   if(tmpDate > LimitEndDate)
                     LimitEndDate = tmpDate;
                }
                else if(tmpDate >LimitStartDate)
                      LimitStartDate = tmpDate;
              }
              break;
            case ftFinishFinish:
              if(Delay>=0)
                PrevEndDate = WorkDayOffset(PrevEndDate,Delay+1);
              else
                PrevEndDate = WorkDayOffset(PrevEndDate,Delay-1);
              if(PrevEndDate>LimitEndDate)
              {
                LimitEndDate = PrevEndDate;
                tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);
                   if(tmpDate > LimitEndDate)
                     LimitEndDate = tmpDate;
                }
                else if(tmpDate >LimitStartDate)
                      LimitStartDate = tmpDate;
              }
              break;
            case ftNone:
			  break;
		  }
        }//for
          if(ATask->PlanType == ptASAP)
          {
            SDate = LimitStartDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
            ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          }
          else if(ATask->PlanType == ptALAP)
          {
            EDate = ATask->ALAP_EndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
          }
          else
          {
            SDate = LimitStartDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
          }
      }//else
      switch(ATask->PlanType)
      {
        case ptMSO :
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
            ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          break;
        case ptMFO :
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
            ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          break;
        case ptBSO :
          if(SDate>ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
			ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          }
          break;
        case ptBFO :
          if(EDate>ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
            ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          }
          break;
        case ptASO :
          if(SDate<ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
            ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          }
          break;
        case ptAFO :
          if(EDate<ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
            ATask->ASAP_StartDate = SDate;
            ATask->ASAP_EndDate = EDate;
          }
          break;
      }//switch
      //赋值并标记为"已经计算"
      ATask->StartDate = SDate;
      ATask->EndDate = EDate;
      ATask->Calced = true;
      break;
    case ptALAP:
      EDate = b_EndDate;
      SDate = WorkDayOffset(EDate, -ATask->CostDays);
      //如果后置任务为空，则结束日期指定为工程结束日期
      if(ATask->LateTaskCount == 0)
      {
        SDate = GetProperStartDate(ATask);
        EDate = GetProperEndDate(ATask);
      }
      else //后置任务不为空，则先遍历所有后置任务，计算出后置任务的工期
      {
        TDateTime NextStartDate,NextEndDate, LimitStartDate, LimitEndDate, tmpDate;
        LimitStartDate = 401769;
        LimitEndDate = 401769;
        TTask * LateTask;
        TFrontType ft;
        int Delay;
        int i;
        /*开始遍历*/
        for(i=0;i<=ATask->LateTaskCount-1;i++)
        {
          LateTask = ATask->LateTasks[i]->Task;
          ft = ATask->LateTasks[i]->Type;
          Delay = ATask->LateTasks[i]->FreeTime;
          //递归计算该后置任务（如果该后置任务已经计算过，该函数直接返回）
          CalcTask(LateTask,NextStartDate,NextEndDate,Plan);
          //根据连接类型计算
          switch(ft)
          {
            case ftFinishStart:
              //计算延迟
              if(ATask->CostDays != 0)
              {
                if(Delay>=-1)
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay+2));
                else
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay));
              }
              else
              {
				if(Delay>=-1)
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay+1));
                else
                  NextStartDate = WorkDayOffset(NextStartDate,-(Delay));
              }
              //计算最晚结束时间
              if(NextStartDate<=LimitEndDate)
			  {
                LimitEndDate = NextStartDate;
                if(LimitEndDate > EDate)
                  LimitEndDate = EDate;
                //计算该结束时间对应的开始时间
                tmpDate = WorkDayOffset(LimitEndDate,-(ATask->CostDays));
                //更新开始时间
                if(tmpDate < LimitStartDate)
                   LimitStartDate = tmpDate;
              }
              break;
            case ftStartStart:
              if(Delay>=0)
                NextStartDate = WorkDayOffset(NextStartDate,-(Delay+1));
              else
                NextStartDate = WorkDayOffset(NextStartDate,-(Delay-1));

              if(NextStartDate<LimitStartDate)
              {
                LimitStartDate = NextStartDate;

				tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);

                if(tmpDate > EDate)
                {
                  LimitEndDate = EDate;
                  tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                  if(tmpDate < LimitStartDate)
					LimitStartDate = tmpDate;
                }
                else if(tmpDate < LimitEndDate)
                   LimitEndDate = tmpDate;
			  }
              break;
            case ftStartFinish:
              if(Delay>=1)
                NextEndDate = WorkDayOffset(NextEndDate,-(Delay+0));
              else
                NextEndDate = WorkDayOffset(NextEndDate,-(Delay-2));

              if(NextEndDate < LimitStartDate)
              {
                LimitStartDate = NextEndDate;
                tmpDate = WorkDayOffset(LimitStartDate,ATask->CostDays);

                if(tmpDate>EDate)
                {
                   LimitEndDate = EDate;
                   tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                   if(tmpDate < LimitStartDate)
                     LimitStartDate = tmpDate;
                }
                else if(tmpDate < LimitEndDate)
                      LimitEndDate = tmpDate;
              }
              break;
			case ftFinishFinish:
              if(ATask->CostDays != 0)
              {
                if(Delay>=0)
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay+1));
                else
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay-1));
              }
              else
              {
                if(Delay>=0)
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay+2));
                else
                  NextEndDate = WorkDayOffset(NextEndDate,-(Delay));
              }
             if(NextEndDate<LimitEndDate)
              {
                LimitEndDate = NextEndDate;
                if(LimitEndDate>EDate)
                  LimitEndDate = EDate;
                tmpDate = WorkDayOffset(LimitEndDate,-ATask->CostDays);
                if(tmpDate < LimitStartDate)
                {
                   LimitStartDate = tmpDate;
                }
              }
              break;
            case ftNone:
              break;
          }
		}

        if(ATask->PlanType == ptASAP)
        {
          SDate = ATask->ASAP_StartDate;
          EDate = WorkDayOffset(SDate,ATask->CostDays);
        }
        else if(ATask->PlanType == ptALAP)
        {
          EDate = LimitEndDate;
          SDate = WorkDayOffset(EDate,-ATask->CostDays);
          ATask->ALAP_StartDate = SDate;
          ATask->ALAP_EndDate = EDate;
        }
        else if(ATask->PlanType == ptMSO)
        {
          if(ATask->GetType() == ttForeignProject)
            EDate = ATask->LimitedEndDate;
          else
            EDate = WorkDayOffset(ATask->LimitedDate,ATask->CostDays);
          SDate = ATask->LimitedDate;

          ATask->ALAP_StartDate = SDate;
          ATask->ALAP_EndDate = EDate;
		}
      }//else
      switch(ATask->PlanType)
      {
        case ptMSO :
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
            ATask->ALAP_StartDate = SDate;
            ATask->ALAP_EndDate = EDate;
          break;
        case ptMFO :
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
            ATask->ALAP_StartDate = SDate;
            ATask->ALAP_EndDate = EDate;
          break;
        case ptBSO :
          if(SDate>ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
            ATask->ALAP_StartDate = SDate;
            ATask->ALAP_EndDate = EDate;
          }
          break;
        case ptBFO :
          if(EDate>ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
            ATask->ALAP_StartDate = SDate;
            ATask->ALAP_EndDate = EDate;
          }
          break;
        case ptASO :
          if(SDate<ATask->LimitedDate)
          {
            SDate = ATask->LimitedDate;
            EDate = WorkDayOffset(SDate,ATask->CostDays);
            ATask->ALAP_StartDate = SDate;
            ATask->ALAP_EndDate = EDate;
          }
          break;
        case ptAFO :
          if(EDate<ATask->LimitedEndDate)
          {
            EDate = ATask->LimitedEndDate;
            SDate = WorkDayOffset(EDate,-ATask->CostDays);
            ATask->ALAP_StartDate = SDate;
            ATask->ALAP_EndDate = EDate;
          }
          break;
      }//switch
      /*计算最早开始时间、结束时间*/
      //工期余量大于工期
	  //赋值并标记为"已经计算"
	  ATask->StartDate = SDate;
	  ATask->EndDate = EDate;

	  ATask->TempStartDate=SDate; //为了计算项目计划时间
	  ATask->TempEndDate=EDate;
      ATask->Calced = true;
      break;
    default:
	  throw Exception("不支持该类型!");
  }
}
//------------------------------------------------------------------------------
void TCalculator::PreCalcTaskPert(TTask *ATask,double &SDate, double &EDate,double &SQ,double &EQ)
{
  if(ATask==NULL)
	throw Exception("没有找到任务！");

  if(ATask->Calced)
  {
    SDate = ATask->TempStartDate;
    EDate = ATask->TempEndDate;
	SQ = ATask->TempStartQ;
    EQ = ATask->TempEndQ;
    return;
  }

      SDate = 0;
      EDate = ATask->PertDuration;
      SQ = 0;
      EQ = ATask->PertDurationQ;
      //如果前置任务为空，则开始日期指定为工程开始日期
      if(ATask->FrontTaskCount>0)
      { //前置任务不为空，则先遍历所有前置任务，计算出前置任务的工期
        double PrevStartDate,PrevEndDate, LimitStartDate, LimitEndDate, LimitSQ,LimitEQ,tmpDate,tmpQ,PrevSQ,PrevEQ;
        LimitStartDate = 0;
        LimitEndDate = 0;
        LimitSQ=0;
        LimitEQ=0;
        TTask * FrontTask;
        TFrontType ft;
        int Delay;
        /*开始遍历*/
        for(int i=0;i<=ATask->FrontTaskCount-1;i++)
        {
          FrontTask = ATask->FrontTasks[i]->Front;
          ft = ATask->FrontTasks[i]->Type;
          Delay = ATask->FrontTasks[i]->FreeTime;
          //递归计算该前置任务（如果该前置任务已经计算过，该函数直接返回）
          PreCalcTaskPert(FrontTask,PrevStartDate,PrevEndDate,PrevSQ,PrevEQ);
          if(FrontTask->CostDays == 0) //MILESTONE
          {
             PrevEndDate = PrevStartDate;
             PrevEQ=PrevSQ;
          }
          //根据连接类型计算
          switch(ft)
          {
            case ftFinishStart:  //FINISH - START
              //计算延迟
                PrevEndDate = PrevEndDate+Delay;
                LimitSQ=PrevEQ;
              //计算最早开始时间
              if(PrevEndDate>=LimitStartDate)
              {
                LimitStartDate = PrevEndDate;
                if(LimitStartDate < SDate)
                {
                  LimitStartDate = SDate;
                  LimitSQ= SQ;
                }
               //计算该开始时间对应的结束时间
                tmpDate = LimitStartDate+ATask->PertDuration;
                tmpQ = PrevEQ+ATask->PertDurationQ;
                //更新结束时间
                if(tmpDate > LimitEndDate)
                {
                   LimitEndDate = tmpDate;
                   LimitEQ= tmpQ;
                }
              }
              break;
			case ftStartStart:
                PrevStartDate = PrevStartDate+Delay;
                LimitSQ=PrevEQ;
              if(PrevStartDate>LimitStartDate)
              {
                LimitStartDate = PrevStartDate;
                if(LimitStartDate < SDate)
                {
                  LimitStartDate = SDate;
                  LimitSQ=SQ;
                }
                tmpDate = LimitStartDate+ATask->PertDuration;
                tmpQ = PrevEQ+ATask->PertDurationQ;
                if(tmpDate > LimitEndDate)
                {
                   LimitEndDate = tmpDate;
                   LimitEQ=tmpQ;
                 }
              }
              break;
			case ftStartFinish:
		          PrevStartDate = PrevStartDate+Delay;
		          LimitSQ=PrevEQ;
              if(PrevStartDate>LimitEndDate)
              {
                LimitEndDate = PrevStartDate;
                tmpDate = LimitEndDate-ATask->PertDuration;
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   LimitSQ=SQ;
                   //算结束时间
                   tmpDate = LimitStartDate+ATask->PertDuration;
                   tmpQ = PrevEQ+ATask->PertDurationQ;
                   if(tmpDate > LimitEndDate)
                   {
                     LimitEndDate = tmpDate;
                     LimitEQ=tmpQ;
                   }
                }
                else if(tmpDate >LimitStartDate)
                {
                   LimitStartDate = tmpDate;
                   LimitSQ=tmpQ;
                }
              }
              break;
			case ftFinishFinish:
                PrevEndDate = PrevEndDate+Delay;
                LimitSQ=PrevEQ;
              if(PrevEndDate>LimitEndDate)
              {
                LimitEndDate = PrevEndDate;
                tmpDate = LimitEndDate-ATask->PertDuration;
                //如果计算出的任务开始日期小于项目开始日期
                //则把任务开始日期设置为项目开始日期，
                //结束日期顺延
                if(tmpDate<SDate)
                {
                   LimitStartDate = SDate;
                   LimitSQ=SQ;
                   tmpDate =LimitStartDate+ATask->PertDuration;
                   tmpQ = PrevEQ+ATask->PertDurationQ;
                   if(tmpDate > LimitEndDate)
                   {
                     LimitEndDate = tmpDate;
                     LimitEQ = tmpQ;
                   }
                }
                else if(tmpDate >LimitStartDate)
                {
                      LimitStartDate = tmpDate;
                      LimitSQ = tmpQ;
                }
              }
              break;
            case ftNone:
			  break;
          }
        }//for

        /*计算最早开始时间、结束时间*/
        //工期余量大于工期
        if((LimitStartDate+ATask->PertDuration)<=LimitEndDate)
        {
           SDate = LimitStartDate;
           EDate = SDate+ATask->PertDuration;
           SQ=LimitSQ;
           EQ=SQ+ATask->PertDurationQ;
        }
        else  //右对齐
        {
          EDate = LimitEndDate;
          SDate = EDate -ATask->PertDuration;
          EQ=LimitEQ;
          SQ=EQ-ATask->PertDurationQ;
        }

      }//else
      double LimitedDate=0;
      switch(ATask->PlanType)
      {
        case ptMSO :
            for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
            SDate = LimitedDate;
            EDate = SDate+ATask->PertDuration;
          break;
        case ptMFO :
             for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedEndDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
            EDate = LimitedDate;
            SDate = EDate-ATask->PertDuration;
          break;
        case ptBSO :
            for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(SDate>LimitedDate)
          {
            SDate = LimitedDate;
            EDate = SDate+ATask->PertDuration;
          }
          break;
        case ptBFO :
           for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedEndDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(EDate>LimitedDate)
          {
            EDate = LimitedDate;
            SDate = EDate-ATask->PertDuration;
          }
          break;
        case ptASO :
            for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(SDate<LimitedDate)
          {
            SDate = LimitedDate;
            EDate = SDate+ATask->PertDuration;
          }
          break;
        case ptAFO :
           for(TDateTime dt=FProject->StartDate;dt<=ATask->LimitedEndDate;dt++)
              {
              	if (FProject->Calendar->IsWorkDay(dt))
              	    LimitedDate++;
              }
          if(EDate<LimitedDate)
          {
            EDate = LimitedDate;
            SDate = EDate-ATask->PertDuration;
          }
          break;
	  }
      //赋值并标记为"已经计算"
      ATask->Calced = true;
      ATask->TempStartQ = SQ;
      ATask->TempEndQ = EQ;
      ATask->TempStartDate = SDate;
      ATask->TempEndDate = EDate;



}
//------------------------------------------------------------------------------
//拓扑遍历法判断节点网络中是否存在循环
bool TCalculator::IsCyclic()
{
  int i;
  TPrjObject *t;
  ResetVisitFlags();
  bool FoundD0,ContinueSearch = true;
  while(ContinueSearch)
  {
    FoundD0 = false;
	for(i=0;i<=FProject->Objects.Count()-1;i++)
    {
	  t = FProject->Objects[i];
      if(!t->Visited)
	  {   //该节点未被访问，且入度为0，设为已访问
		 if(t->TaskType==ttTask||t->TaskType==ttForeignProject)
		 {

			 if(GetInDegree((TTask*)t)==0)
			 {
				t->Visited = true;
				FoundD0 = true;
			 }
		 }
		 else
		 {
		   t->Visited = true;
		   //FoundD0 = true;
		 }
      }
	}
	if(FoundD0) ContinueSearch = true;
      else ContinueSearch = false;
  }
  int visited = 0;
  int total = 0;
  for(i=0;i<=FProject->Objects.Count()-1;i++)
  {
	t = FProject->Objects[i];
    if(t->Visited) visited++;
    total ++;
  }
  return total!=visited;  //总数与访问过的个数不同，则存在循环
}
//------------------------------------------------------------------------------
//重置计算标志位
void TCalculator::ResetCalcFlags()
{
  for(int i=0;i<=FProject->Tasks.Count()-1;i++)
    FProject->Tasks[i]->Calced = false;
}
//------------------------------------------------------------------------------
TDateTime TCalculator::GetMaxDate()
{
  TDateTime MaxDate = 0;
  for(int i=0;i<FProject->Tasks.Count();i++)
  {

    if(int(MaxDate) < int(FProject->Tasks[i]->TempEndDate))
      MaxDate = FProject->Tasks[i]->TempEndDate;
  }
  return MaxDate;
}
//------------------------------------------------------------------------------
TDateTime TCalculator::GetMinDate()
{
  TDateTime MinDate = 401769;
  int i;
  for(i=0;i<FProject->Tasks.Count();i++)
  {
	  if(MinDate > FProject->Tasks[i]->TempStartDate)
        MinDate = FProject->Tasks[i]->TempStartDate;
  }
  return MinDate;
}
//------------------------------------------------------------------------------
TDateTime TCalculator::GetProperStartDate(TTask * t)
{
  switch(t->PlanType)
  {
    case ptASAP:
      return t->ASAP_StartDate;
    case ptALAP:
      return t->ALAP_StartDate;
    case ptMSO:
      return t->LimitedDate;
    default:
      return t->ASAP_StartDate;
  }
}
//------------------------------------------------------------------------------
TDateTime TCalculator::GetProperEndDate(TTask * t)
{
  switch(t->PlanType)
  {
    case ptASAP:
      return t->ASAP_EndDate;
    case ptALAP:
      return t->ALAP_EndDate;
    case ptMSO:
      if(t->GetType() == ttForeignProject)
        return t->LimitedEndDate;
      else return WorkDayOffset(t->LimitedDate,t->CostDays);
    default:
      return t->ASAP_EndDate;
  }
}
//------------------------------------------------------------------------------
//重置遍历标志位
void TCalculator::ResetVisitFlags()
{
  int i;
  TPrjObject *t;
  for(i=0;i<FProject->Objects.Count();i++)   //Tasks
  {
	t = FProject->Objects[i];
	t->Visited = false;
  }
}
//------------------------------------------------------------------------------
//得到某节点入度
int TCalculator::GetInDegree(TTask *t)
{
   int i;
   int id = 0;
   TTask *FrontTask;
   for(i=0;i<=t->FrontTaskCount-1;i++)
   {
     FrontTask = t->FrontTasks[i]->Front;
     if(!FrontTask->Visited )
        id ++;
   }
   return id;
}
//------------------------------------------------------------------------------
TDateTime TCalculator::WorkDayOffset(TDateTime BaseDate, int Delta)
{
  int i;
  TDateTime NewDate;
  i = 1;
  BYTE dow;
  NewDate = BaseDate;
  if(Delta>0)
  {
    while(i<Delta)
    {
      NewDate++ ;
      if(FProject->Calendar->IsWorkDay(NewDate))
        i++;
    }
  }
  else if(Delta<0)
  {
    while(i<-Delta)
    {
      NewDate--;
      if(FProject->Calendar->IsWorkDay(NewDate))
        i++;
    }
  }else return BaseDate;
  return NewDate;
}
//------------------------------------------------------------------------------
String TCalculator::GetErrorLinks()
{
  int i;
  TTask *t;
  String RetVal = "";
  for(i=0;i<=FProject->Tasks.Count()-1;i++)
  {
    t = FProject->Tasks[i];
    if(!t->Visited)
    {
      if(RetVal == "") RetVal = "\n"+IntToStr(t->Index)+":"+t->Name;
      else RetVal += ", " + IntToStr(t->Index) + ":" + t->Name;
    }
  }
  return RetVal+"\n";
}
//------------------------------------------------------------------------------
void TCalculator::CalcTaskFreeDays()
{
  int i,j,freedays;
  TDateTime MinDate = 401769;
  TDateTime dt,mt;
  TTask *ct,*lt;
  TPrjObject *prjObj;
  for(i=0;i<FProject->Tasks.Count();i++)   //计算普通任务
  {
	ct = FProject->Tasks[i];

	freedays=0;
	for(dt=ct->ASAP_StartDate+1;dt<=ct->ALAP_StartDate;dt++)
	{
		if (FProject->Calendar->IsWorkDay(dt)) {  //判断是否是有效工作日
			freedays++;
		}
	}
	ct->TotalDiff=freedays; //总时差

	if(ct->LateTaskCount==0)
	  MinDate=ct->ALAP_EndDate;
	else
	  MinDate=FProject->ASAP_EndDate;
	int  Delay=0;
	for(j=0;j<ct->LateTaskCount;j++)   //取后置任务最早开工日期
	{
		if(ct->LateTasks[j]->Type!=ftFinishStart)
			continue;
		lt=ct->LateTasks[j]->Task;
		Delay=ct->LateTasks[j]->FreeTime;
		if(lt->ASAP_StartDate<MinDate)
		{
		  MinDate=lt->ASAP_StartDate;
		}
	}
	if(ct->PlanType==ptMFO||ct->PlanType==ptBFO)  //任务有特殊限制
	{
	  if(MinDate>(ct->ALAP_EndDate+1))
		MinDate=ct->ALAP_EndDate+1;
	}
	freedays=0;
	if(MinDate<=ct->ASAP_EndDate)
	{
		mt=ct->ASAP_EndDate;
		if(ct->MileStone)
		  mt--;
		for(dt=MinDate;dt<mt;dt++)
		{
		if (FProject->Calendar->IsWorkDay(dt)) {  	//判断是否是有效工作日
			freedays--;
			}
		}
	}
	else
	{
		for(dt=ct->ASAP_EndDate+1;dt<MinDate;dt++)
		{
		if (FProject->Calendar->IsWorkDay(dt)) {  	//判断是否是有效工作日
			freedays++;
			}
	   }
	}
	if(freedays>ct->TotalDiff)//限制不能大于总时差
	   freedays=ct->TotalDiff;
	ct->FreeDays=freedays;         //自由时差
  }
  //计算非普通任务
   for(i=0;i<FProject->Objects.Count();i++)
  {
	  prjObj=FProject->Objects[i];
	  if(prjObj->TaskType==ttAbstractTask||prjObj->TaskType==ttForeignProject)
	  {
		freedays=0;
		for(dt=prjObj->ASAP_StartDate+1;dt<=prjObj->ALAP_StartDate;dt++)
		{
			if (FProject->Calendar->IsWorkDay(dt)) {  //判断是否是有效工作日
				freedays++;
			}
		}
		prjObj->TotalDiff=freedays; //总时差
		prjObj->SumFreeDays();
	   //	prjObj->SumAll();// 顺便计算其它信息；2011-01-26
	  }

   }
}
//------------------------------------------------------------------------------
}


