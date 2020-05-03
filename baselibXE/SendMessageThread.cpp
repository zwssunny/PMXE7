//---------------------------------------------------------------------------

#pragma hdrstop

#include "SendMessageThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TSendMessageThread::TSendMessageThread(TDBXConnection* DBXConnection, TUserType AUserType,String AMsg,String CurUserID)
{
  FMessageManage = new TMessageManageClient(DBXConnection);
  FUserType = AUserType;
  UserID = CurUserID;
  MsgRemark = AMsg;
}
//---------------------------------------------------------------------------
void __fastcall TSendMessageThread::Execute()
{
  FreeOnTerminate=true;
	switch(FUserType)
	{
		case utGroup:
		  SendMessageToRole(MsgRemark,UserID);
			break;
		case utJob:
			SendMessageToJob(MsgRemark,UserID);
			break;
		case utDepartment:
			SendMessageToDepartment(MsgRemark,UserID);
			break;
		case utCompany:
			SendMessageToDepartment(MsgRemark,UserID);
			break;
		default:  //autUser:autDepartmentManager:
			SendMessageToUser(MsgRemark,UserID);
	}
  delete FMessageManage;
}
System::UnicodeString __fastcall TSendMessageThread::GetHTMLEscapedString(System::UnicodeString Value)
{
		  return FMessageManage->GetHTMLEscapedString(Value);
}
//---------------------------------------------------------------------------
bool __fastcall TSendMessageThread::SendMessageToAll(System::UnicodeString Msg)
{
   return FMessageManage->SendMessageToAll(Msg);
}
//---------------------------------------------------------------------------
bool __fastcall TSendMessageThread::SendMessageToUser(System::UnicodeString Msg, System::UnicodeString UserID)
{
  return FMessageManage->SendMessageToUser(Msg,UserID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendMessageThread::SendMessageToDepartment(System::UnicodeString Msg, System::UnicodeString DepartmentID)
{
   return FMessageManage->SendMessageToDepartment(Msg,DepartmentID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendMessageThread::SendMessageToJob(System::UnicodeString Msg, System::UnicodeString JobID)
{
   return FMessageManage->SendMessageToJob(Msg,JobID);
}
//---------------------------------------------------------------------------
bool __fastcall TSendMessageThread::SendMessageToRole(System::UnicodeString Msg, System::UnicodeString RoleID)
{
   return FMessageManage->SendMessageToRole(Msg,RoleID);
}
//---------------------------------------------------------------------------
