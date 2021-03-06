//---------------------------------------------------------------------------

#ifndef WorkFlowServerH
#define WorkFlowServerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
#include "wsClasses.hpp"
#include "wsDB.hpp"
#include "wsAccAndSysDB.hpp"
#include "wsMain.hpp"
//---------------------------------------------------------------------------
class TWorkFlowServer : public TDMBaseServerClass
{
private:	// User declarations
		TWorkflowInstance* __fastcall GetWorkIns(String FFlowDefID,String WorkInsID);
		void __fastcall InitWorkFlowStudio();
		TWorkflowStudio *WorkflowStudio;
		TWorkflowAccAndSysDB *WorkflowAccAndSysDB;
		TLoginUserRecord *curUser;
private:	// User declarations
		TADOQuery *m_Query;
public:		// User declarations
		__fastcall TWorkFlowServer(TComponent* Owner);
		__fastcall ~TWorkFlowServer();
		//返回当前工作流ID
		String ServerWorkFlowStartJSON(TJSONObject* jsonValue);
		String ServerWorkFlowStart(String FlowDefID, String Subject, String Content, String BusWindow, String BusCode, int Rank, String PrjID, String Report);
		//返回是否调用成功
		bool  ServerWorkFlowExecJSON(TJSONObject* jsonValue);
		bool  ServerWorkFlowExec(String FlowDefID, String WorkInsID, String TaskInsID, String TskStatus, String TskComments, TJSONArray *VariableList);
		TJSONObject* GetTaskList(String AUserID, int ACompletedState, String AOtherCondition);// AUserID:查询员工ID；ACompletedState：查询任务状态，0-待办，1-已完成，2-全部；AOtherCondition：查询过滤条件。
		String GetLogList(int ALogFilterType, String AFilterKey); //ALogFilterType：日志类型，1-流程日志，2-任务日志。AFilterKey：流程实例ID或任务实例ID
		String GetDiagram(int ADiagramType, String ADiagramKey);//ADiagramType:查询流程图类型，0-流程定义，1-流程实例，2-任务实例；ADiagramKey:流程定义ID、流程实例ID或者任务实例ID。
		TJSONObject* GetTaskdefList(String TaskInsID);
		TJSONObject* GetVariableList(String TaskInsID);
		TStream* GetVariableListDS(String TaskInsID);
		TStream* GetTaskdefListDS(String TaskInsID);
		///传入Id，isDef表示是定义的还是实例的。 返回JPG格式。
		TStream* GetWorkFlowChart(String FlowID,bool isDef);
		TStream* GetTaskListDS(String AUserID, int ACompletedState, String AOtherCondition);
		bool TaskCanUpdate(String TaskInsID);
};
//---------------------------------------------------------------------------
extern PACKAGE TWorkFlowServer *DMWorkFlowServer;
//---------------------------------------------------------------------------
#endif
