//---------------------------------------------------------------------------

#ifndef LoginUserH
#define LoginUserH
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Datasnap.DBClient.hpp>
#include "BaseServerClass.h"
#include <Datasnap.DSAuth.hpp>
#include "MessageManage.h"
//---------------------------------------------------------------------------
class TLoginUser : public TDMBaseServerClass
{
private:
		TClientDataSet *FLoginListDataSet;
		TADOQuery *m_Query;
		TADOQuery *b_Query;
		TADOQuery *LogQuery;
		TMessageManage * FFMessageManage;
		TLoginUserRecord * curUser;
protected:
		void  CreateLoginListDataSet();
		void __fastcall	NotifySendMissMessage(TLoginUserRecord *user,TADOConnection *AccConn);
public:
		__fastcall TLoginUser(TComponent* Owner);
		__fastcall ~TLoginUser();
public:
		String  GetSysConnectionString();
	   //	bool  IsValidUser(String UserCode,String Password,String AccbookID,String &msg);
		bool  ChangePassword(String UserCode,String OldPassword,String NewPassword,String &msg);
		bool  UpdateCurUserCallbackClientID(String const Value);
		void  Logout();

		void  SetUsersToFollow(TJSONArray* Users);
		bool  SendMessageToFollow(String const Msg);
		bool  SendMessageToAll(String const Msg);
		bool  SendMessageToUser(String const Msg, String const UserID);
		bool  SendMessageToDepartment(String const Msg, String const DepartmentID);
		bool  SendMessageToGroup(String const Msg, String const GroupID);
		bool  SendCMDToFollow(String const cmdStr);
		bool  SendCMDToAll(String const cmdStr);
		bool  SendCMDToUser(String const cmdStr, String const UserID);
		bool  SendCMDToDepartment(String const cmdStr, String const DepartmentID);
		bool  SendCMDToGroup(String const cmdStr, String const GroupID);
		bool  SendMgrMessage(int itype, String const Msg);

		TStream*  GetAccList(); //仅返回账套列表
		TStream*  GetCurUserInfo();
		TStream*  ListOfLoginUser();
		TStream*  ListOfAllLoginUser();
		TStream*  GetClassList();
		TStream*  GetAutoCodeFields();
		TStream*  GetModuleData();
		TStream*  RefreshGlobeVar();
		TStream*  GetModuleRight();
		 //返回产品信息，ftp,mail,账套信息和系统库链接串
		TJSONObject*  GetAccInforJSON();
		TJSONObject*  GetAccListJSON();
		TJSONObject*  GetCurUserJSON();
		TJSONArray*   GetUserList();
		TJSONArray*   GetAllUserList();
		TJSONObject*  GetClassListJO();
		TJSONObject*  GetAutoCodeFieldsJO();
		TJSONObject*  GetModuleDataJO();
		TJSONObject*  RefreshGlobeVarJO();
		TJSONObject*  GetModuleRightJO();
		TJSONArray*   GetDepartmentAndUsersList();
		String  UserIdToName(String UserId);
		//返回配置信息信息
		TJSONObject* GetServerInfo();
		TJSONObject* GetFtpSetting();
		TJSONObject* GetMailSetting();
		TJSONObject* GetSmsSetting();
		//返回工作流服务器列表
		TJSONArray*  GetWorkFlowServerList();
		//返回短信服务器信息
		TJSONArray*  GetSmsServerList();
};
#endif
