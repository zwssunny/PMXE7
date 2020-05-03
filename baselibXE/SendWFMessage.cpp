//---------------------------------------------------------------------------

#pragma hdrstop

#include "SendWFMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TSendWFMessageThread::TSendWFMessageThread(TDBXConnection* DBXConnection, TTaskInstance *ATaskIns)
{
  FMessageManage = new TMessageManageClient(DBXConnection);
  FAssignedUserType = ATaskIns->AssignedUserType;
  UserID = ATaskIns->UserID;
  MsgRemark = L"系统提醒您有新的任务:"+ATaskIns->FlowMnDtlRemark;
}
TSendWFMessageThread::TSendWFMessageThread(TDBXConnection* DBXConnection, TWorkflowInstance* AWorkIns)
{
  FMessageManage = new TMessageManageClient(DBXConnection);
  FAssignedUserType = autUser;
  UserID = AWorkIns->FlowMnCreator;
 if(AWorkIns->Status==TWorkflowStatus::wsFinished)
	MsgRemark = L"系统提醒您提交的审批任务已结束:\r\n"+AWorkIns->FlowMnSubject;
 else
   	MsgRemark = L"系统提醒您提交的审批任务已终止:\r\n"+AWorkIns->FlowMnSubject;
}
//---------------------------------------------------------------------------
void __fastcall TSendWFMessageThread::Execute()
{
  FreeOnTerminate=true;
	switch(FAssignedUserType)
	{
		case autGroup:
		  SendMessageToRole(MsgRemark,UserID);
			break;
		case autJob:
			SendMessageToJob(MsgRemark,UserID);
			break;
		case autDepartment:
			SendMessageToDepartment(MsgRemark,UserID);
			break;
		default:  //autUser:autDepartmentManager:
			SendMessageToUser(MsgRemark,UserID);
	}
  delete FMessageManage;
}
//---------------------------------------------------------------------------
TJSONArray* __fastcall TSendWFMessageThread::GetUserList()
{
		  return FMessageManage->GetUserList();
}
//---------------------------------------------------------------------------
System::UnicodeString __fastcall TSendWFMessageThread::GetHTMLEscapedString(System::UnicodeString Value)
{
		  return FMessageManage->GetHTMLEscapedString(Value);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendMessageToAll(System::UnicodeString Msg)
{
   return FMessageManage->SendMessageToAll(Msg);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendMessageToUser(System::UnicodeString Msg, System::UnicodeString UserID)
{
  return FMessageManage->SendMessageToUser(Msg,UserID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendMessageToDepartment(System::UnicodeString Msg, System::UnicodeString DepartmentID)
{
   return FMessageManage->SendMessageToDepartment(Msg,DepartmentID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendMessageToJob(System::UnicodeString Msg, System::UnicodeString JobID)
{
   return FMessageManage->SendMessageToJob(Msg,JobID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendMessageToRole(System::UnicodeString Msg, System::UnicodeString RoleID)
{
   return FMessageManage->SendMessageToRole(Msg,RoleID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendCMDToAll(System::UnicodeString cmdStr)
{
  return FMessageManage->SendCMDToAll(cmdStr);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendCMDToUser(System::UnicodeString cmdStr, System::UnicodeString UserID)
{
   return FMessageManage->SendCMDToUser(cmdStr,UserID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendCMDToDepartment(System::UnicodeString cmdStr, System::UnicodeString DepartmentID)
{
  return FMessageManage->SendCMDToDepartment(cmdStr,DepartmentID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendCMDToGroup(System::UnicodeString cmdStr, System::UnicodeString GroupID)
{
  return FMessageManage->SendCMDToGroup(cmdStr,GroupID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendWFMessageThread::SendCMDToRole(System::UnicodeString cmdStr, System::UnicodeString RoleID)
{
  return FMessageManage->SendCMDToRole(cmdStr,RoleID);
}
//---------------------------------------------------------------------------

