//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "ChatRoomServerMethods.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall  TChatRoomServerMethods::TChatRoomServerMethods(TDBXConnection *ADBXConnection)
{
	FMessageManageClient = new TMessageManageClient(ADBXConnection);
}


__fastcall  TChatRoomServerMethods::TChatRoomServerMethods(TDBXConnection *ADBXConnection, bool AInstanceOwner)
{
	FMessageManageClient = new TMessageManageClient(ADBXConnection,false);
}
__fastcall TChatRoomServerMethods::~TChatRoomServerMethods()
{
  delete FMessageManageClient;
}
TJSONArray* __fastcall TChatRoomServerMethods::GetUserList()
{
		  return FMessageManageClient->GetUserList();
}
System::UnicodeString __fastcall TChatRoomServerMethods::GetHTMLEscapedString(System::UnicodeString Value)
{
		  return FMessageManageClient->GetHTMLEscapedString(Value);
}
bool __fastcall TChatRoomServerMethods::UpdateCurUserCallbackClientID(System::UnicodeString Value)
{
   return FMessageManageClient->UpdateCurUserCallbackClientID(Value);
}
bool __fastcall TChatRoomServerMethods::SendMessageToAll(System::UnicodeString Msg)
{
   return FMessageManageClient->SendMessageToAll(Msg);
}
bool __fastcall TChatRoomServerMethods::SendMessageToUser(System::UnicodeString Msg, System::UnicodeString UserID)
{
  return FMessageManageClient->SendMessageToUser(Msg,UserID);
}
bool __fastcall TChatRoomServerMethods::SendMessageToDepartment(System::UnicodeString Msg, System::UnicodeString DepartmentID)
{
   return FMessageManageClient->SendMessageToDepartment(Msg,DepartmentID);
}
bool __fastcall TChatRoomServerMethods::SendMessageToGroup(System::UnicodeString Msg, System::UnicodeString GroupID)
{
   return FMessageManageClient->SendMessageToGroup(Msg,GroupID);
}
bool __fastcall TChatRoomServerMethods::SendMessageToFollow(System::UnicodeString Msg)
{
   return FMessageManageClient->SendMessageToFollow(Msg);
}
bool __fastcall TChatRoomServerMethods::SendCMDToFollow(System::UnicodeString cmdStr)
{
  return FMessageManageClient->SendCMDToFollow(cmdStr);
}
bool __fastcall TChatRoomServerMethods::SendCMDToAll(System::UnicodeString cmdStr)
{
  return FMessageManageClient->SendCMDToAll(cmdStr);
}
bool __fastcall TChatRoomServerMethods::SendCMDToUser(System::UnicodeString cmdStr, System::UnicodeString UserID)
{
   return FMessageManageClient->SendCMDToUser(cmdStr,UserID);
}
bool __fastcall TChatRoomServerMethods::SendCMDToDepartment(System::UnicodeString cmdStr, System::UnicodeString DepartmentID)
{
  return FMessageManageClient->SendCMDToDepartment(cmdStr,DepartmentID);
}
bool __fastcall TChatRoomServerMethods::SendCMDToGroup(System::UnicodeString cmdStr, System::UnicodeString GroupID)
{
  return FMessageManageClient->SendCMDToGroup(cmdStr,GroupID);
}
bool __fastcall TChatRoomServerMethods::SendMgrMessage(int itype, System::UnicodeString Msg)
{
	return FMessageManageClient->SendMgrMessage(itype,Msg);
}
bool __fastcall TChatRoomServerMethods::SendMessageToJob(String const Msg, String const JobID)
{
	return FMessageManageClient->SendMessageToJob(Msg,JobID);
}
bool __fastcall TChatRoomServerMethods::SendMessageToRole(String const Msg, String const RoleID)
{
   return FMessageManageClient->SendMessageToRole(Msg,RoleID);
}
bool __fastcall TChatRoomServerMethods::SendCMDToRole(String const cmdStr, String const RoleID)
{
  return FMessageManageClient->SendCMDToRole(cmdStr,RoleID);
}
bool __fastcall TChatRoomServerMethods::SendCMDToJob(String const cmdStr, String const JobID)
{
   return FMessageManageClient->SendCMDToJob(cmdStr,JobID);
}
