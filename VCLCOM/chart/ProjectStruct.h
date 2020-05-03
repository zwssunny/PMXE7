//---------------------------------------------------------------------------
#ifndef ProjectStructH
#define ProjectStructH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <vector>
#include "Vclcomfunc.h"
using namespace std;
using namespace Vclcomfunc;
namespace ProjectStruct
{

//---------------------------------------------------------------------------
enum TFrontType	{
		ftNone=0,    //0-无
		ftFinishStart=1,// 1-完成-开始
		ftStartStart=2, // 2-开始-开始
		ftFinishFinish=3,// 3-完成-完成
		ftStartFinish=4  //4-开始-完成
		};
enum TDateStatus{ //日期状态
		dsRest=0, //休息
		dsWork=1, //工作
		dsSuspend=2  //停工
		};
enum TWeekDay{
		wdSunday=0,
		wdMonday=1,
		wdTuesday=2,
		wdWednesday=3,
		wdThursday=4,
		wdFriday=5,
		wdSaturday=6
		};
enum TEditStatus { //节点修改状态
		esNone=0,
		esNew=1,
		esModified=2,
		esDeleted=4,
		esEditTaskStatus=8
		};
enum TTaskStatus{  //任务状态
		tsNotStart=0,
		tsStarted=1,
		tsOvered=2,
		tsPaused=3
		};
enum TTaskType { //节点类型
		ttProject=0,
		ttTask=1,
		ttAbstractTask=2,
		ttForeignProject=3,
		ttMileStone=4
		};
enum TStateDateType {
		sdtPrjProgressDate=0,
		sdtCurrentDate=1,
		sdtManualDate=2
		};//状态日期取值方式
enum TTaskPctType {
		taptDurtion=0,
		taptWorkLoad=1,
		taptManual=2
		}; //实际完成百分比计算类型
enum TTaskDtnType {
		tdtUnit=0,
		tdtDuration=1,
		tdtLabor=2
		};//工期类型
enum TProjectType {
			ptSingle, //单项目
			ptComplex //多项目
			};//项目类型
enum TPlanType {ptNone,
				ptASAP,//越早越好
				ptALAP,//越晚越好
				ptMSO ,//必须开始于
				ptMFO, //必须完成于
				ptBSO ,//不得晚于...开始
				ptBFO, //不得晚于...完成
				ptASO, //不得早于...开始
				ptAFO //不得早于...完成
			   };

extern PACKAGE String GetPlanTypeName(int plantype);

//---------------------------------------------------------------------------
class PACKAGE TPrjObject; //所有节点对象
class PACKAGE TProject;//项目
class PACKAGE TTask;//任务
class PACKAGE TAbstractTask;//摘要任务
class PACKAGE TForeignProject;//外部项目
class PACKAGE TIteratorBase;//迭代器
class PACKAGE TTaskIterator;
class PACKAGE TTaskLink;//任务关系
class PACKAGE TTaskLinkIterator; //任务关系迭代器
class PACKAGE TPrjDataChangeLink;
class PACKAGE TCalculator; //计算器
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TRequestSaveEvent)(TProject* AProject);
typedef void __fastcall (__closure *TLoadDataEvent)(TProject* AProject, TForeignProject* AForPrj);
typedef void __fastcall (__closure *TTaskEvent)(TProject* AProject, TPrjObject* ATask);
typedef void __fastcall (__closure *TTaskLinkEvent)(TProject* AProject,
                                             TTask* ATask, TTaskLink* ATaskLink);
//---------------------------------------------------------------------------
class PACKAGE TCalculator
{
private:
	TDateTime b_StartDate, b_EndDate;
    TProject* FProject;
	void PreCalcTask(TTask *ATask,TDateTime &SDate, TDateTime &EDate, BYTE Plan);
	void CalcTask(TTask *ATask,TDateTime &SDate, TDateTime &EDate, BYTE Plan);
    void CalcTaskPert(TTask *ATask,double &SDate, double &EDate,double &SQ,double &EQ);
    void PreCalcTaskPert(TTask *ATask,double &SDate, double &EDate,double &SQ,double &EQ);
	void CalcTaskFreeDays();
    void ResetCalcFlags();
    TDateTime GetMaxDate();
	TDateTime GetMinDate();
    TDateTime GetProperStartDate(TTask * t);
    TDateTime GetProperEndDate(TTask * t);
    void ResetVisitFlags();
    int GetInDegree(TTask *t);
    String GetErrorLinks();
    int CalculateImpl();
    TDateTime WorkDayOffset(TDateTime BaseDate, int Delta);
public:
    TCalculator(TProject * AProject):FProject(AProject){}
    bool IsCyclic();
    int Calculate();
        void CalculatePert();
};
//---------------------------------------------------------------------------
class PACKAGE TTaskData
{
private:
		TDateTime FBStartDate;
		TDateTime FBEndDate;
		int FBCostDays;             //运算服务
protected:
		TDateTime   FLimitedDate;       //限制开始日期（对于ptMSO计划方法的任务有效）
		TDateTime   FLimitedEndDate;    //限制结束日期（对于ptMSO计划方法的任务有效）
		bool        FCheckItem;         //是否核算项目
		double      FTaskPctPercent;    //任务完成百分比%,由下面类型决定。
		TTaskPctType FPctType;          //任务完成百分比计算依据，0-工期，1-数量，2-输入
		TTaskDtnType FTaskDtnType;  //工期类型
		String  FDesc;              //任务描述
		double      FCostDays;          //计划工期
		double      FFactCostDays;      //实际工期
                                    // 默认工程量计量单位为系统计量单位"百分比"
		double      FWorkLoad;          //计划工程量
                                    //在生成进度报告时，各时间段统计数据来源于进度截止日期的计划数，由任务日历汇总得到，工期为0时，工程量必须为0；
		double      FFactWorkLoad;      //(实际工程量	汇总
                                    //实际工程量只能小于等于计划工程量,当任务完工时二者完全相等
		double      FEnvaluedWorkLoad;    //工程量评估值
		double      FInvest;            //计划产值
		double      FFactInvest;        //实际产值 汇总
                                    //实际产值可以小于也可以大于计划产值
		double      FEnvaluedInvest;
		bool        FMileStone;         //里程碑标识	0-非里程碑	1-里程碑
		double      FOptimismCostDays;  //乐观工期
		double      FAnticipateCostDays;//预期工期
		double      FPessimismCostDays; //悲观工期
		double      FRiskProbability;   //风险概率		该任务发生风险的概率
		double      FRiskQty;           //风险量	风险发生时预计产生的损失
		double      FRiskLoss;          //风险损失	实际发生的风险损失
		TDateTime   FProcessDate;       //进度截止日期
		TTaskStatus FTaskStatus;        //进度标识

		TTaskType   FTaskType;          //任务类型 1-常规，2-组，3-外部工程,4-里程碑
		String  	FGroupCode;         //上级任务组
		String  	FForeignID;       //外部项目号
		int         FForeignChangeFlag; //外部变化标识 0-无，1-有
		int         FPlanAdjFlag;       //计划调整标识
		int         FStopFlag;          //挺复工标志
		int         FWorkLoadType;//工程量类型，0：无明细工程量，1：有明细工程量
		double      FProportion;
		String  	FCode;
		String  	FSmartCode;
		String  	FName;
		//计划时间临时变量
		TDateTime FTempStartDate;
		TDateTime FTempEndDate;
		TDateTime FTempStartQ;
		TDateTime FTempEndQ;

		TDateTime FStartDate;
		TDateTime FEndDate;
		TDateTime FALAP_StartDate;
		TDateTime FALAP_EndDate;
		TDateTime FASAP_StartDate;
		TDateTime FASAP_EndDate;
		TDateTime FFactStartDate;
		TDateTime FFactEndDate;
		TDateTime FFF_StartDate;
		TDateTime FFF_EndDate;
		int         FIndex;
		TPlanType   FPlanType; //任务完成期限
		bool        FCritical;//任务类型
		String  FWBS;
		int         FVitalLevel;//0一般，1重要，2重大
		String  FPersonnel;
		double      FFreeDays;
		double      FTotalDiff;
        String FPrjCode;
        String FTaskID;
        String FTempTaskSyncDesc;
        double FPertStartTime;
        double FPertStartQ;
        double FPertEndTime;
        double FPertEndQ;
        double FBCWS;
        double FBCWP;
#pragma option -w-inl
template<class Type>
bool CompareSetValue(Type& OldValue, Type& NewValue)
    {
		if(OldValue != NewValue)
        {
			 OldValue = NewValue;
             if(!ReadingData)
             {
                 FEditStatus = TEditStatus(FEditStatus | esModified);
				 if(((TPrjObject*)(this))->Parent() != NULL)
                     return true;
             }
		}
		return false;
    }
#pragma option -winl
    void __fastcall SetDesc(String);
	void __fastcall SetPctType(TTaskPctType value);
	void __fastcall SetTaskPctPercent(double Value);
	void __fastcall SetWorkLoad(double Value);
    void __fastcall SetFactCostDays(double);
    void __fastcall SetFactWorkLoad(double);
    void __fastcall SetEnvaluedWorkLoad(double);
	void __fastcall SetInvestUnit(String);
    void __fastcall SetInvest(double);
    void __fastcall SetFactInvest(double);
    void __fastcall SetEnvaluedInvest(double);
    void __fastcall SetMileStone(bool);
    void __fastcall SetAnticipateCostDays(double);
    void __fastcall SetOptimismCostDays(double);
    void __fastcall SetPessimismCostDays(double);
    void __fastcall SetRiskProbability(double);
    void __fastcall SetRiskQty(double);
    void __fastcall SetRiskLoss(double);
    void __fastcall SetProcessDate(TDateTime);
    void __fastcall SetTaskStatus(TTaskStatus);
    void __fastcall SetWBS(String AWBS);
    void __fastcall SetFreeDays(double );
    void __fastcall SetTotalDiff(double );

    void __fastcall SetWorkLoadType(int Value);


	void __fastcall SetTaskType(TTaskType Value);          //任务类型 1-常规，2-组，3-外部工程 ，4-里程碑
    void __fastcall SetGroupID(String);         //上级任务组
    void __fastcall SetForeignID(String);       //外部项目号
    void __fastcall SetForeignChangeFlag(int); //外部变化标识 0-无，1-有
    void __fastcall SetPlanAdjFlag(int);       //计划调整标识

    bool __fastcall GetIsNew();
    void __fastcall SetIsNew(bool Value);
    bool __fastcall GetIsModified();
    void __fastcall SetIsModified(bool Value);
	void __fastcall SetCode(String Code);
    void __fastcall SetSmartCode(String Code);
    void __fastcall SetName(String Name);
    void __fastcall SetIndex(int AIndex);
    void __fastcall SetCostDays(double ACostDays);
    void __fastcall SetStartDate(TDateTime AStartDate);
    void __fastcall SetEndDate(TDateTime AEndDate);
    void __fastcall SetASAP_StartDate(TDateTime ASAP_StartDate);
    void __fastcall SetASAP_EndDate(TDateTime ASAP_EndDate);
    void __fastcall SetALAP_StartDate(TDateTime ALAP_StartDate);
    void __fastcall SetALAP_EndDate(TDateTime ALAP_EndDate);
    void __fastcall SetFactStartDate(TDateTime FactStartDate);
    void __fastcall SetFactEndDate(TDateTime FactEndDate);
    void __fastcall SetPlanType(TPlanType PlanType);
    void __fastcall SetCritical(bool Critical);
    void __fastcall SetProportion(double dProportion);
    void __fastcall SetVitalLevel(int ivalue);
    String __fastcall GetGroupID();
    String __fastcall GetSortCode();
    String __fastcall GetForeignID();
    TTaskType __fastcall GetTaskType();
    void __fastcall SetCheckItem(bool bCheckItem);
    void __fastcall SetPrjCode(String value);
    void __fastcall SetTaskID(String value);
    double __fastcall GetCV();
    double __fastcall GetSV();
    double __fastcall GetCPI();
    double __fastcall GetSPI();
    void __fastcall SetBCWS(double Value);
    void __fastcall SetBCWP(double Value);
    double __fastcall GetACWP();
    double __fastcall CalBCWP();
    double __fastcall CalBCWS();    
    double __fastcall GetPertDuration();
    double __fastcall GetPertDurationQ();
    void __fastcall SetPertStartTime(double value);
    void __fastcall SetPertStartQ(double value);
    void __fastcall SetPertEndTime(double value);
    void __fastcall SetPertEndQ(double value);
    TEditStatus FEditStatus;
public:
    static bool ReadingData;
    static bool Moving;
    TTaskData();
    void InitData();
    TTaskData& operator=(TTaskData&);
    void SumBCWS();
    void SumWorkLoad();
	void SumFactCostDays();
	void SumFreeDays();
	void SumFactWorkLoad();
    void SumEnvaluedWorkLoad();
    void SumInvest();
    void SumFactInvest();
	void SumEnvaluedInvest();
    void SumAnticipateCostDays();
    void SumOptimismCostDays();
    void SumPessimismCostDays();
    void SumProcessDate();
    void SumTaskStatus();
    void SumCostDays();
    void SumASAP_StartDate();
    void SumASAP_EndDate();
    void SumALAP_StartDate();
    void SumALAP_EndDate();
    void SumStartDate();
    void SumEndDate();
    void SumStartEndDate();
    void SumFactStartDate();
    void SumFactEndDate();
    void SumMileStone();
    void SumFFDate();
	void SumAll();
	void SumPctPercent();

	virtual int GetCumulateDays();
	TDateTime GetptyLimitedDate();
    void SetptyLimitedDate(TDateTime date);
    void SumPertStartTime();
	void SumPertEndTime();
    __property TDateTime    LimitedDate = {read=FLimitedDate, write=FLimitedDate};//限制开始日期
    __property TDateTime    LimitedEndDate = {read=FLimitedEndDate, write=FLimitedEndDate}; //限制结束日期
    __property TDateTime    ptyLimitedDate = {read=GetptyLimitedDate, write=SetptyLimitedDate};
	__property String   	Desc = {read=FDesc, write=SetDesc};
    __property double       FactCostDays = {read=FFactCostDays, write=SetFactCostDays}; //实际已投入工期
    __property double       WorkLoad = {read=FWorkLoad,write=SetWorkLoad }; //计划进度  到项目观察日应完成的进度％
    __property double       FactWorkLoad = {read=FFactWorkLoad, write=SetFactWorkLoad}; //实际进度
    __property double       EnvaluedWorkLoad = {read=FEnvaluedWorkLoad, write=SetEnvaluedWorkLoad};   //评估实际进度
    __property double       Invest = {read=FInvest, write=SetInvest};    //计划总投资/产值
    __property double       FactInvest = {read=FFactInvest, write=SetFactInvest};//实际已投资/产值 ACWP/AC
    __property double       EnvaluedInvest = {read=FEnvaluedInvest, write=SetEnvaluedInvest}; //评估实际已投资
    __property double       BCWS  = { read=FBCWS,write=SetBCWS }; // 计划完成投资 BCWS/PV
    __property double       ACWP  = { read=GetACWP }; // 实际已投资 ACWP/AC
    __property double       BCWP  = { read=FBCWP,write=SetBCWP};  // 已完成投资  赢得值 BCWP/EV
    __property double       CV  = { read=GetCV };  //费用偏差；
    __property double       SV  = { read=GetSV };  //进度偏差；
    __property double       CPI  = { read=GetCPI }; //费用绩效指数；
    __property double       SPI  = { read=GetSPI }; //进度绩效指数；
    __property bool         MileStone = {read=FMileStone, write=SetMileStone};//里程碑
    __property double       AnticipateCostDays = {read=FAnticipateCostDays, write=SetAnticipateCostDays}; //乐观工期
    __property double       OptimismCostDays = {read=FOptimismCostDays, write=SetOptimismCostDays}; //正常工期
    __property double       PessimismCostDays = {read=FPessimismCostDays, write=SetPessimismCostDays}; //悲观工期
    __property double       RiskProbability = {read=FRiskProbability, write=SetRiskProbability};  // 风险概率
    __property double       RiskQty = {read=FRiskQty, write=SetRiskQty};               //风险量
    __property double       RiskLoss = {read=FRiskLoss, write=SetRiskLoss};            //风险损失
    __property TDateTime    ProcessDate = {read=FProcessDate, write=SetProcessDate};    //进度截至日
    __property TTaskStatus  TaskStatus = {read=FTaskStatus, write=SetTaskStatus};       //任务状态

	__property TTaskType    TaskType = {read=GetTaskType, write=SetTaskType};          //任务类型 1-常规，2-组，3-外部工程
	__property String   	GroupID = {read=GetGroupID, write=SetGroupID};         //上级任务组
	__property String   	ForeignID = {read=GetForeignID, write=SetForeignID};       //外部项目号
    __property int          ForeignChangeFlag = {read=FForeignChangeFlag, write=SetForeignChangeFlag}; //外部变化标识 0-无，1-有
    __property int          PlanAdjFlag = {read=FPlanAdjFlag, write=SetPlanAdjFlag};       //计划调整标识

    __property bool         IsNew = {read=GetIsNew, write=SetIsNew};
    __property bool         IsModified = {read=GetIsModified, write=SetIsModified};
	__property String   	Code = {read=FCode, write=SetCode};
	__property String   	SmartCode = {read=FSmartCode, write=SetSmartCode};   //在公路版中用作起止桩号
	__property String   	Name = {read=FName, write=SetName};
    __property int          Index = {read=FIndex, write=SetIndex};
    __property double       CostDays = {read=FCostDays, write=SetCostDays};//计划工期
	__property double       CumulateDays = {read=GetCumulateDays};//累积工期，不算假期在内
	__property TDateTime    StartDate = {read=FStartDate, write=SetStartDate};//计划开始时间
    __property TDateTime    EndDate = {read=FEndDate, write=SetEndDate};//计划结束时间
    __property TDateTime    ALAP_StartDate = {read=FALAP_StartDate, write=SetALAP_StartDate};//最晚开始时间
    __property TDateTime    ALAP_EndDate = {read=FALAP_EndDate, write=SetALAP_EndDate};//最晚完成时间
    __property TDateTime    ASAP_StartDate = {read=FASAP_StartDate, write=SetASAP_StartDate};//最早开始时间
    __property TDateTime    ASAP_EndDate = {read=FASAP_EndDate, write=SetASAP_EndDate};//最早完成时间
    __property TDateTime    FF_StartDate = {read=FFF_StartDate, write=FFF_StartDate};//最早完成时间(中间变量)
    __property TDateTime    FF_EndDate = {read=FFF_EndDate, write=FFF_EndDate};//最早完成时间      (中间变量)
    __property TDateTime    FactStartDate = {read=FFactStartDate, write=SetFactStartDate};//实际开始时间
    __property TDateTime    FactEndDate = {read=FFactEndDate, write=SetFactEndDate};//实际结束时间
    __property TPlanType    PlanType = {read=FPlanType, write=SetPlanType};//计划类型
    __property bool         Critical = {read=FCritical, write=SetCritical};//是否关键
	__property String   	WBS = {read=FWBS, write=SetWBS};
	__property double       FreeDays= {read=FFreeDays, write=SetFreeDays};      //自由时差
    __property double       TotalDiff= {read=FTotalDiff, write=SetTotalDiff};   //总时差
    __property int          VitalLevel = {read=FVitalLevel, write=SetVitalLevel}; //任务重要性
	__property String   	Personnel = {read=FPersonnel, write=FPersonnel};    //责任单位
	__property int          WorkLoadType = {read=FWorkLoadType, write=SetWorkLoadType}; //0-普通，1-单位工程，2-分部工程，3-分项工程
	__property String   	SortCode = {read=GetSortCode};                //排序号
	__property String   	PrjCode  = { read=FPrjCode, write=SetPrjCode }; //该任务所属项目号
	__property String   	TaskID  = { read=FTaskID, write=SetTaskID }; //任务ID，在项目内唯一
    __property TDateTime    TempStartDate  = { read=FTempStartDate, write=FTempStartDate }; //运算服务
    __property TDateTime    TempEndDate  = { read=FTempEndDate, write=FTempEndDate };   //运算服务
	__property String   	TempTaskSyncDesc  = { read=FTempTaskSyncDesc, write=FTempTaskSyncDesc };//在描叙外部项目同步情况
    __property double       Proportion = {read=FProportion,write=SetProportion};  //权重，用于计算对上级任务组的进度贡献
    __property int          StopFlag = {write=FStopFlag,read=FStopFlag};//停工标志 0:没有停工记录 1停工 2复工
    __property bool         CheckItem={read=FCheckItem,write=SetCheckItem};     //是否是核算项目
    __property TTaskPctType PctType  = { read=FPctType, write=SetPctType };     //任务完成百分比计算类型
    __property double       TaskPctPercent  = { read=FTaskPctPercent, write=SetTaskPctPercent };  //任务完成百分比
    __property TTaskDtnType TaskDtnType  = { read=FTaskDtnType, write=FTaskDtnType };  // 工期类型
	__property double 		PertStartTime  = { read=FPertStartTime, write=SetPertStartTime };   //期望开始时间
	__property double 		PertStartQ  = { read=FPertStartQ, write=SetPertStartQ };
	__property double 		PertEndTime  = { read=FPertEndTime, write=SetPertEndTime };    //期望结束时间
	__property double 		PertEndQ  = { read=FPertEndQ, write=SetPertEndQ };
	__property double 		PertDuration  = { read=GetPertDuration };                 //期望工期
	__property double 		PertDurationQ  = { read=GetPertDurationQ };
	__property TDateTime 	TempStartQ  = { read=FTempStartQ, write=FTempStartQ };   //运算服务
	__property TDateTime 	TempEndQ  = { read=FTempEndQ, write=FTempEndQ };
	__property TDateTime 	BStartDate  = { read=FBStartDate, write=FBStartDate };
	__property TDateTime 	BEndDate  = { read=FBEndDate, write=FBEndDate };
	__property int 			BCostDays  = { read=FBCostDays, write=FBCostDays };


};
//---------------------------------------------------------------------------
class PACKAGE TPrjCalendar
{
private:
        TDateStatus FPrjCalendar[7];
        DynamicArray<TDateTime> FHolidays;
        DynamicArray<TDateTime> FOutOfdays;
        TDateStatus __fastcall GetPrjCalendar(TWeekDay AWeekDay);
        void __fastcall SetPrjCalendar(TWeekDay AWeekDay, TDateStatus AStatus);
public:
        void SetCalendar(TDateStatus Sunday, TDateStatus Monday,
                         TDateStatus Tuesday, TDateStatus Wednesday,
                         TDateStatus Thursday, TDateStatus Friday,
                         TDateStatus Saturday);
        void AddHoliday(TDateTime ADate);
        void AddOutOfday(TDateTime ADate);
        void DelOutOfday(TDateTime ADate);
        void DelHoliday(TDateTime ADate);
        void ClearHoliday();
        void ClearOutOfday();
        bool IsWorkDay(TDateTime ADate);
        bool IsOutOfDay(TDateTime ADate);
        bool IsHoliday(TDateTime ADate);
		__property TDateStatus PrjCalendar[TWeekDay AWeekDay] = {read=GetPrjCalendar, write=SetPrjCalendar};
};
//---------------------------------------------------------------------------
class PACKAGE TIteratorBase
{
        friend TProject;
        friend TForeignProject;
private:
        virtual void OnTaskAdd(TPrjObject&) = 0;
        virtual void OnTaskDelete(TPrjObject&) = 0;
        virtual void OnTaskLinkAdd(TTaskLink&) = 0;
        virtual void OnTaskLinkDelete(TTaskLink&) = 0;
        virtual void OnClear() = 0;
protected:
        TProject& FProject;
        TIteratorBase(TProject&);
        virtual ~TIteratorBase();
};
//---------------------------------------------------------------------------
class PACKAGE TTaskIterator : public TIteratorBase
{
private:
        virtual void OnTaskAdd(TPrjObject&);
        virtual void OnTaskDelete(TPrjObject&);
        virtual void OnTaskLinkAdd(TTaskLink&);
        virtual void OnTaskLinkDelete(TTaskLink&);
        virtual void OnClear();
		TPointerArray< TTask > FTasks;
        TTask* GetNextTask(TTask*ATask);
        TTask* GetChildTask(TPrjObject*AObj);
		void AddObjectChilds(TPrjObject&);
        void DeleteObjectChilds(TPrjObject&);
public:
        TTaskIterator(TProject&);
        TTask* operator [] (int Index);
        int Count();
        int TaskIndexOf(TTask&);
};
//---------------------------------------------------------------------------
class PACKAGE TTaskLinkIterator : public TIteratorBase
{
private:
        virtual void OnTaskAdd(TPrjObject&);
        virtual void OnTaskDelete(TPrjObject&);
        virtual void OnTaskLinkAdd(TTaskLink&);
        virtual void OnTaskLinkDelete(TTaskLink&);
        virtual void OnClear();
        TPointerArray< TTaskLink > FTaskLinks;
public:
        TTaskLinkIterator(TProject&);
        TTaskLink* operator [] (int Index);
        int Count();
};
//---------------------------------------------------------------------------
class PACKAGE TExpandFoldIterator : public TIteratorBase
{
private:
        virtual void OnTaskAdd(TPrjObject&);
        virtual void OnTaskDelete(TPrjObject&);
        virtual void OnTaskLinkAdd(TTaskLink&);
        virtual void OnTaskLinkDelete(TTaskLink&);
        virtual void OnClear();
        TPointerArray< TPrjObject > FObjects;
        int ExpandChild(TPrjObject&AObj, int Index);
        void ReIndex();
        void InsertObjectChilds(TPrjObject&, int& Index);
        void AddObjectChilds(TPrjObject&);
        void DeleteObjectChilds(TPrjObject&);
public:
        TExpandFoldIterator(TProject&);
        TPrjObject* operator [] (int Index);
        int  Count();
        void Expand(int Index);
        void Expand(TPrjObject*);
        void Fold(int Index);
        bool CanExpandFold(int Index);
        bool IsVisible(TPrjObject& AObj);
};
//---------------------------------------------------------------------------
class PACKAGE TObjectIterator : public TIteratorBase
{//所有对象，包括外部项目子任务
private:
        virtual void OnTaskAdd(TPrjObject&);
        virtual void OnTaskDelete(TPrjObject&);
        virtual void OnTaskLinkAdd(TTaskLink&);
        virtual void OnTaskLinkDelete(TTaskLink&);
        virtual void OnClear();
        TPointerArray< TPrjObject > FObjects;
        TPrjObject* GetNextObject(TPrjObject&);
        void InsertObjectChilds(TPrjObject&, int& Index);
        void AddObjectChilds(TPrjObject&);
        void DeleteObjectChilds(TPrjObject&);
public:
        TObjectIterator(TProject&);
        TPrjObject* operator [] (int Index);
        int Count();
};
//---------------------------------------------------------------------------
class PACKAGE TInnerObjectIterator : public TIteratorBase
{//所有对象，不包括外部项目子任务
private:
        virtual void OnTaskAdd(TPrjObject&);
        virtual void OnTaskDelete(TPrjObject&);
        virtual void OnTaskLinkAdd(TTaskLink&);
        virtual void OnTaskLinkDelete(TTaskLink&);
        virtual void OnClear();
        TPointerArray< TPrjObject > FObjects;
        TPrjObject* GetNextObject(TPrjObject&);
        void InsertObjectChilds(TPrjObject&, int& Index);
        void AddObjectChilds(TPrjObject&);
        void DeleteObjectChilds(TPrjObject&);
public:
        TInnerObjectIterator(TProject&);
        TPrjObject* operator [] (int Index);
        int Count();
};
//---------------------------------------------------------------------------
class PACKAGE TPrjObject : public TTaskData
{
        friend TProject;
        friend TAbstractTask;
        friend TForeignProject;
private:
        virtual TTaskType GetTypeImpl() = 0;
        virtual TPrjObject& GetChildImpl(int Index);
        virtual int ChildCountImpl();
        virtual TPrjObject& InsertChildImpl(int Position, TTaskType AType);
        virtual void InsertChildObjectImpl(int Position, TPrjObject*);
        virtual void DeleteChildImpl(TPrjObject&AChild);
        virtual void RemoveChildImpl(TPrjObject&AChild);
        virtual void ClearImpl();
        virtual int ChildIndexImpl(TPrjObject&AChild);

        virtual TTaskLink* __fastcall GetFrontTask(int Index);
        virtual TTaskLink* __fastcall GetLateTask(int Index);
        virtual int __fastcall GetFrontTaskCount();
        virtual int __fastcall GetLateTaskCount();
		virtual TTaskLink* AddFrontTaskImpl(const String& FrontCode,const String& FrontPrjCode);
		virtual TTaskLink* AddLateTaskImpl(const String& LateCode,const String& LatePrjCode);
        virtual void DelFrontTaskImpl(TTaskLink&ATaskLink);
        virtual void DelLateTaskImpl(TTaskLink&ATaskLink);
		virtual void ClearFrontTaskImpl();
        virtual void ClearLateTaskImpl();
        virtual void AllChildIsModified(TPrjObject&AChild);
protected:
		TProject*   FProject;
		TPrjObject* FParent;
		TPrjCalendar* FPrjCalendar;
		virtual int ReIndexImpl(int Start);
		TPrjObject(TProject*AProject, TPrjObject*AParent, TPrjCalendar*APrjCalendar);
		virtual ~TPrjObject();
public:
		TPrjObject* Parent();
        TProject*   Project();
		TTaskType     GetType()                                 { return GetTypeImpl(); }
        TPrjObject& GetChild(int Index)                       { return GetChildImpl(Index); }
        int           ChildCount()                              { return ChildCountImpl(); }
        TPrjObject& InsertChild(int Position, TTaskType AType){ return InsertChildImpl(Position, AType); }
        TPrjObject& AddChild(TTaskType AType)                 { return InsertChildImpl(ChildCount(), AType); }
        void          DeleteChild(TPrjObject&AChild)          { DeleteChildImpl(AChild); }
        void          RemoveChild(TPrjObject&AChild)          { RemoveChildImpl(AChild); }
        void          Clear()                                   { ClearImpl(); }
        int           ChildIndex(TPrjObject&AChild)           { return ChildIndexImpl(AChild); }
        void SetAllChildIsModified(TPrjObject&AChild)         { AllChildIsModified(AChild); };
        bool          IsForeign();
        int           Layer();
        virtual void  Assign(TPrjObject*);
		TPrjObject*      ObjByID(String AID,String PrjID="");   //目前PrjID=PrjCode
		TPrjObject*      ObjByCode(String ACode,String PrjCode="");

		int GetCumulateDays();

		TTaskLink* AddFrontTask(const String& FrontCode,const String& FrontPrjCode="")  { return AddFrontTaskImpl(FrontCode,FrontPrjCode); }
		TTaskLink* AddLateTask(const String& LateCode,const String& LatePrjCode="")  { return AddLateTaskImpl(LateCode,LatePrjCode); }
		void DelFrontTask(TTaskLink&ATaskLink)                { DelFrontTaskImpl(ATaskLink); }
		void DelLateTask(TTaskLink&ATaskLink)                 { DelLateTaskImpl(ATaskLink); }
		void ClearFrontTask()                                   { ClearFrontTaskImpl(); }
		void ClearLateTask()                                    { ClearLateTaskImpl(); }
		__property TTaskLink* FrontTasks[int Index] = {read=GetFrontTask};
		__property TTaskLink* LateTasks[int Index] = {read=GetLateTask};
		__property int FrontTaskCount = {read=GetFrontTaskCount};
		__property int LateTaskCount = {read=GetLateTaskCount};

		bool CheckExclusiveWBS(String sWBS);
        void CheckWBSRule(String sWBS);
        String FillPrefix(String sWBS);
        String BuildWBS(int iLevel,int order);
        virtual void BuildChildWBS();
        void BuildSelfWBS();
        void ClearChildWBS();

		TTask* GetTaskByID(TPrjObject* AObj, const String& AID,const String& APrjID="");
protected:
		bool        FCalced;
		void        ResetEditStatus();
public:
		__property TPrjObject& Childs[int Index] = {read = GetChildImpl};
		__property TPrjCalendar*     Calendar = { read  = FPrjCalendar };
		__property bool          Calced = {read=FCalced,write=FCalced};
public:
		bool  Visited;//是否已经计算
		int   EFExpandIndex;//支持展开合拢
		bool  EFExpanded;//支持展开合拢
		int   NCLeft;  //网络图
		int   NCTop;
		RECT  LGRect;//逻辑图
        int   DCStartEvent;//双代号网络图
        int   DCEndEvent;//双代号网络图
        bool  StartInherit;//前节点是继承的
        bool  EndInherit;  //后节点是继承的
		int   DCY;			//双代号网络图
        int   StartLinkCount;//开始节点的入线数
		int   EndLinkCount;  //结束节点的出线数
        int   EndFSCount;  //结束节点的入线关系为FS的个数
};
//---------------------------------------------------------------------------
struct TDeletedTaskLinkItem{
       String TaskID;
	   String FrontID;
	   String ProjectID;
	   String FrontPrjID;
};
class TDeletedTaskLinks : public TPointerArray< TDeletedTaskLinkItem >
{
       static void OnDeleteTaskLinkItem(void*AItem){ delete (TDeletedTaskLinkItem*)AItem; }
public:
       TDeletedTaskLinks() : TPointerArray< TDeletedTaskLinkItem >(OnDeleteTaskLinkItem) {}
	   void Add(const String& TaskID, const String& FrontID,const String& ProjectID,const String& FrontPrjID)
       {
		   TDeletedTaskLinkItem* AItem = new TDeletedTaskLinkItem();
           AItem->TaskID = TaskID;
		   AItem->FrontID = FrontID;
		   AItem->ProjectID = ProjectID;
		   AItem->FrontPrjID = FrontPrjID;
		   TPointerArray< TDeletedTaskLinkItem >::Add(AItem);
	   }
};
//---------------------------------------------------------------------------
//WBS规则
class PACKAGE TWBSRule
{
private:
public:
    int Level;
    int CharType;
    int Length;
    String Separator;

    TWBSRule();
    String GetChar(int order);
    String BuildWBS(int order);
    String FillPrefix(String sWBS);
    void CheckWBSRule(String sWBS);
};
class PACKAGE TProject : public TPrjObject
{
        friend TTask;
        friend TTaskLink;
		friend TPrjDataChangeLink;
        friend TAbstractTask;
        friend TForeignProject;
        friend TIteratorBase;
        friend TExpandFoldIterator;
private:
		String FCalendarType;//日历类型	日历代码
		String FPrjType;//项目类型

        TCalculator* Calc;
		void __fastcall SetCalendarType(String ACalendarType);//日历类型
		void __fastcall SetPrjType(String APrjType);//项目类型

        bool FUsePCWBS;
		TPrjCalendar FPrjCalendarObj;
        TPointerArray<TPrjDataChangeLink> __FPrjDataChangeLink;

        virtual TTaskType GetTypeImpl();
        TPointerArray< TPrjObject > FChilds;
        static void OnDeleteChild(void*);
        virtual TPrjObject& GetChildImpl(int Index);
        virtual int ChildCountImpl();
        virtual TPrjObject& InsertChildImpl(int Position, TTaskType AType);
        virtual void InsertChildObjectImpl(int Position, TPrjObject*);
        virtual void DeleteChildImpl(TPrjObject&AChild);
        virtual void RemoveChildImpl(TPrjObject&AChild);
        virtual void ClearImpl();
        virtual int ChildIndexImpl(TPrjObject&AChild);
        TPointerArray< TIteratorBase > FIterators;
        void OnTaskAdd(TPrjObject&);
        void OnTaskDelete(TPrjObject&);
        void OnTaskLinkAdd(TTaskLink&);
        void OnTaskLinkDelete(TTaskLink&);
		 //当需要保存数据时触发，现只被MoveTask函数用到了
		TRequestSaveEvent   FOnRequestSave;
		TLoadDataEvent      FOnLoadData;
        TDateTime GetStateDate();
        TDateTime FStateDate;
		double __fastcall GetFactWorkLoad();
		double __fastcall GetEnvaluedWorkLoad();
		double __fastcall GetCV();
		double __fastcall GetSV();
		double __fastcall GetCPI();
		double __fastcall GetSPI();
		double __fastcall GetBCWS();
		double __fastcall GetACWP();
		double __fastcall GetBCWP();
protected:
		TStrings* FDeletedTasks;
        TPrjObject*  FSelected;
        bool FNeedEditStatus;
		void __fastcall SetNeedEditStatus(bool AStatus);
        void __fastcall SetSelected(TPrjObject* ATask);
public:
		TProject();
        virtual    ~TProject();
        void       BeginUpdate();
        void       EndUpdate();
        void       ReIndex();
        void       AddIterator(TIteratorBase*Itr);
		void       DeleteIterator(TIteratorBase*Itr);
		TTask*     TaskByID(String AID,String APrjID="");
        void       UpdateEditStatus();
		void       Assign(TPrjObject*);
        void       RequestUpdate();
        void       LoadForeignData(TForeignProject* AForPrj);

        TPrjObject*      MoveTask(int OldIndex, int NewIndex);//移动一个任务
        TPrjObject*      AddChildTask(int Child, int Parent);//移动一个任务
		TAbstractTask*   AddAbstractWidthSelection();//由当前选中的任务添加摘要任务
        void               CheckNoChildAbstract();

        int                Calculate();
        bool               IsCyclic();

        TTaskIterator                            Tasks;
        TTaskLinkIterator                        TaskLinks;
        TExpandFoldIterator                      ExpandFoldTasks;
        TObjectIterator                          Objects;
        TInnerObjectIterator                     InnerObjects;
		TPointerArray< TPrjObject > Selections;
        double                                   StatError;//进度误差
		TDeletedTaskLinks                      DeletedTaskLinks;
		__property TStrings*     	DeletedTasks = {read=FDeletedTasks};
		__property bool          	NeedEditStatus = {read=FNeedEditStatus, write=SetNeedEditStatus};
		__property TPrjObject* 		Selected = {read=FSelected, write=SetSelected};
		__property bool          	UsePCWBS = {read=FUsePCWBS, write=FUsePCWBS};
		__property String    		CalendarType = {read=FCalendarType, write=SetCalendarType};//日历类型
		__property String    		PrjType = {read=FPrjType, write=SetPrjType};//项目类型
		__property TRequestSaveEvent  RequestSave = {read=FOnRequestSave, write=FOnRequestSave};
		__property TLoadDataEvent     OnLoadData = {read=FOnLoadData, write=FOnLoadData};
		__property TDateTime 		  StateDate  = { read=GetStateDate };
		//功能函数
        String CreateNewTaskCode();
		//项目特有数据
		String 		ParentProject;//父项目
		String 		ParentProjectTask;//父项目任务
		int        SynchronizationMark;//同步标识 0：同步，1：发生误差
        TDateTime  TaskASAP_StartDate;//父项目任务最早开工
        TDateTime  TaskASAP_EndDate;
        TDateTime  TaskALAP_StartDate;
        TDateTime  TaskALAP_EndDate;
        TPlanType  TaskPlanType;//父项目任务计划类型

        TDateTime  PBeginDate; //预计开始时间
        TDateTime  PEndDate;   //合同规定必修完成时间

        TPointerArray< TWBSRule >     WBSRules;//WBS规则
		static void OnDeleteWBSRule(void*Item);
        String WBSPreNo; //WBS项目前缀
        TWBSRule* GetWBSRule(int index);
        void BuildChildWBS();
        __property double FactWorkLoad  = { read=GetFactWorkLoad };
		__property double EnvaluedWorkLoad  = { read=GetEnvaluedWorkLoad };
		__property double BCWS  = { read=GetBCWS }; // 计划完成投资 BCWS/PV
		__property double ACWP  = { read=GetACWP }; // 实际已投资 ACWP/AC
		__property double BCWP  = { read=GetBCWP };  // 已完成投资  赢得值 BCWP/EV
		__property double CV  = { read=GetCV };  //费用偏差；
		__property double SV  = { read=GetSV };  //进度偏差；
		__property double CPI  = { read=GetCPI }; //费用绩效指数；
		__property double SPI  = { read=GetSPI }; //进度绩效指数；
};
//---------------------------------------------------------------------------
class PACKAGE TAbstractTask : public TPrjObject
{
        friend TProject;
        friend TForeignProject;
private:
        TPointerArray< TPrjObject > FChilds;
        static void OnDeleteChild(void*AChild);

        virtual TTaskType GetTypeImpl();
        virtual TPrjObject& GetChildImpl(int Index);
        virtual int ChildCountImpl();
        virtual TPrjObject& InsertChildImpl(int Position, TTaskType AType);
        virtual void InsertChildObjectImpl(int Position, TPrjObject*);
        virtual void DeleteChildImpl(TPrjObject&AChild);
        virtual void RemoveChildImpl(TPrjObject&AChild);
        virtual void ClearImpl();
        virtual int ChildIndexImpl(TPrjObject&AObj);
		TAbstractTask(TProject&AProject, TPrjObject&AParent, TPrjCalendar*APrjCalendar);
public:
		virtual void Assign(TPrjObject*);
};
//---------------------------------------------------------------------------
class PACKAGE TTask : public TPrjObject
{
	   friend TProject;
       friend TTaskLink;
       friend TAbstractTask;
       friend TForeignProject;
private:
       int __AddLateTask(TTaskLink*ATaskLink);
       void __DelLateTask(TTaskLink*ATaskLink);
	   static void OnFrontTaskDelete(void*);
       virtual TTaskType GetTypeImpl();
protected:
	   TPointerArray<TTaskLink> FFrontTasks;
	   TPointerArray<TTaskLink> FLateTasks;
       virtual TTaskLink* __fastcall GetFrontTask(int Index);
       virtual TTaskLink* __fastcall GetLateTask(int Index);
       virtual int __fastcall GetFrontTaskCount();
       virtual int __fastcall GetLateTaskCount();
	   virtual TTaskLink* AddFrontTaskImpl(const String& FrontID,const String& FrontPrjID);
	   virtual TTaskLink* AddLateTaskImpl(const String& LateID,const String& LatePrjID);
       virtual void DelFrontTaskImpl(TTaskLink&ATaskLink);
       virtual void DelLateTaskImpl(TTaskLink&ATaskLink);
       virtual void ClearFrontTaskImpl();
       virtual void ClearLateTaskImpl();

       virtual void Assign(TPrjObject*);
	   void AssignLink(TTask*);

       TTask(TProject&AProject, TPrjObject&AParent, TPrjCalendar*APrjCalendar);
       virtual ~TTask();
};
//---------------------------------------------------------------------------
class PACKAGE TTaskLink
{
       friend TProject;
       friend TTask;
private:
       TFrontType FType;
	   double FFreeTime;
       void __fastcall SetType(TFrontType AType);
       void __fastcall SetFreeTime(double ATime);
       bool __fastcall GetCritical();
       int __fastcall WorkDayCount(TDateTime Start, TDateTime End);
       bool __fastcall GetIsNew();
       void __fastcall SetIsNew(bool Value);
       bool __fastcall GetIsModified();
       void __fastcall SetIsModified(bool Value);
       void ResetEditStatus();
private:
	   void __SetVoidFrontTask(void* Data);
protected:
       TEditStatus FEditStatus;
       TTask* FTask;
       TTask* FFrontTask;
       TProject* FProject;
       __fastcall TTaskLink(TTask& ATask, TTask&AFront);
       virtual __fastcall ~TTaskLink();
       void Assign(TTaskLink*);
public:
       bool IsForeign();
       __property TFrontType   Type = {read=FType, write=SetType};
	   __property double       FreeTime = {read=FFreeTime, write=SetFreeTime};
       __property TTask*     Front = {read=FFrontTask};
       __property TTask*     Task = {read=FTask};
       __property TProject*  Project = {read=FProject};
       __property bool         Critical = {read=GetCritical};
       __property bool         IsNew = {read=GetIsNew, write=SetIsNew};
       __property bool         IsModified = {read=GetIsModified, write=SetIsModified};
public:
	   POINT NCPoint[6];   //用于网络图，记录联线的位置及点个数
	   int   NCPointCount;//用于网络图
	   int   NCBridgeLineIndex;//用于网络图
	   POINT *NCBridgePoint;//用于网络图
	   int   NCBridgePointCount;//用于网络图
};
//---------------------------------------------------------------------------
class PACKAGE TForeignTaskIterator : public TIteratorBase
{
private:
        virtual void OnTaskAdd(TPrjObject&);
		virtual void OnTaskDelete(TPrjObject&);
        virtual void OnTaskLinkAdd(TTaskLink&);
        virtual void OnTaskLinkDelete(TTaskLink&);
        TPointerArray< TTask > FTasks;
        TForeignProject&  FForeignProject;
public:
        TForeignTaskIterator(TProject&, TForeignProject&);
        TTask& operator [] (int Index);
        int Count();
};
//---------------------------------------------------------------------------
class PACKAGE TForeignProject : public TTask
{
        friend TProject;
		friend TAbstractTask;
private:
		TPrjCalendar FPrjCalendarObj;
		TPointerArray< TPrjObject > FChilds;
        static void OnDeleteChild(void*AChild);

        virtual TTaskType GetTypeImpl();
        virtual TPrjObject& GetChildImpl(int Index);
        virtual int ChildCountImpl();
        virtual TPrjObject& InsertChildImpl(int Position, TTaskType AType);
        virtual void InsertChildObjectImpl(int Position, TPrjObject*);
        virtual void DeleteChildImpl(TPrjObject&AChild);
        virtual void RemoveChildImpl(TPrjObject&AChild);
        virtual void ClearImpl();
        virtual int ChildIndexImpl(TPrjObject&AObj);
        virtual int ReIndexImpl(int Start);

//		TForeignProject(TProject&AProject, TPrjObject&AParent, TPrjCalendar*APrjCalendar);
		TForeignProject(TProject&AProject, TPrjObject&AParent);
public:
        virtual void Assign(TPrjObject*);
		bool LoadedData;
};
//---------------------------------------------------------------------------
//  TPrjDataChangeLink 用于当项目数据结构有数据变动时通知
//  绑定的其他结构(如甘特图，网络图等)更新数据，此类是一个接口，提供各种虚方法供
//  绑定者重载  它存储于TProject的 vector<TPrjDataChangeLink*> __FPrjDataChangeLink;
class TPrjDataChangeLink
{
      friend TProject;
private:
protected:
      virtual void NoBind();
      virtual void Bind();
      TProject* FProject;
public:
      void SetProject(TProject*AProject);
	  TPrjDataChangeLink(TProject*AProject);
	  virtual ~TPrjDataChangeLink();

	  virtual void BeginUpdate() = 0;
	  virtual void EndUpdate() = 0;

	  virtual void BeforeProjectChange(){}
	  virtual void AfterProjectChange(){}

	  virtual void BeforeTaskChange(TPrjObject*ATask){}
	  virtual void AfterTaskChange(TPrjObject*ATask){}

	  virtual void BeforeTaskDelete(TPrjObject*ATask){}
	  virtual void AfterTaskDelete(){}

	  virtual void AfterTaskAdd(TPrjObject*ATask){}

	  virtual void BeforeTaskLinkChange(TTaskLink*ATaskLink){}
	  virtual void AfterTaskLinkChange(TTaskLink*ATaskLink){}

	  virtual void BeforeTaskLinkDelete(TTaskLink*ATaskLink){}
	  virtual void AfterTaskLinkAdd(TTaskLink*ATaskLink){}

	  virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect){}
};


}
#endif
