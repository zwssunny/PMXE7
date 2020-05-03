// ---------------------------------------------------------------------------

#pragma hdrstop

#include "MessageManage.h"
#include "FSServerContainer.h"
#include "SHConst.h"
#include "ChatRoomServer.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TMessageManage::TMessageManage(TComponent* Owner)
	: TDMBaseServerClass(Owner) {
	m_Connection=AccConnection;
	AccQuery = new TADOQuery(NULL);
	AccQuery->ParamCheck = false;
	AccQuery->EnableBCD = false;
	AccQuery->CommandTimeout = 60;
	AccQuery->Connection = m_Connection;

	Query = new TADOQuery(NULL);
	Query->ParamCheck = false;
	Query->EnableBCD = false;
	Query->CommandTimeout = 60;
	Query->Connection = m_Connection;

	EmpQuery = new TADOQuery(this);
	EmpQuery->Connection = m_Connection;

	curLoginUser = GetCurLoginUser();
	FNeedSendToOwn=true;
}

// ---------------------------------------------------------------------------
__fastcall TMessageManage::~TMessageManage() {
	delete AccQuery;
	delete Query;
	delete EmpQuery;
}

// ---------------------------------------------------------------------------
void TMessageManage::NewMessageGroup(String GroupName, String Description) {
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgGroupID = GUIDToString(msgGuid);

	try {
		String InsertString =
			"insert into tbMessageGroup(Groupid,GroupName,GroupCreator,GroupCreated,GroupMemo)" " Values ('"
			+ MsgGroupID + "','" + GroupName + "','" + curLoginUser->UserID + "','" +
			Now().FormatString("YYYY-mm-DD HH:mm:ss") + "','" +
			Description + "')";
		AccQuery->Close();
		AccQuery->SQL->Text = InsertString;
		AccQuery->ExecSQL();
	}
	catch (Exception &e) {
		AccQuery->Close();
		throw Exception("�½�Ⱥ����!");
	}
	NewMessageMember(MsgGroupID, curLoginUser->UserID, 1);
}

// ---------------------------------------------------------------------------
void TMessageManage::DelMessageGroup(String GroupID) {
	try {
		String deleteString = "delete from tbMessageGroup where Groupid =" + QuotedStr(GroupID);
		AccQuery->Close();
		AccQuery->SQL->Text = deleteString;
		AccQuery->ExecSQL();
	}
	catch (Exception &e) {
		AccQuery->Close();
		throw Exception("ɾ��Ⱥ����!");
	}
}

// ---------------------------------------------------------------------------
void TMessageManage::UpdateMessageGroup(String GroupID, String GroupName,
	String Description) {
	try {
	String UpdateString = " Update tbMessageGroup set GroupName=" +QuotedStr(GroupName) + ",GroupMemo='" + QuotedStr(Description) +
			" where Groupid =" + QuotedStr(GroupID);
		AccQuery->Close();
		AccQuery->SQL->Text = UpdateString;
		AccQuery->ExecSQL();
	}
	catch (Exception &e) {
		AccQuery->Close();
		throw Exception("�޸�Ⱥ����!");
	}
}

// ---------------------------------------------------------------------------
void TMessageManage::NewMessageMember(String GroupID, String GroupMemberID,
	int IsAdmin) {
	try {
		String InsertString =
			"insert into tbGroupMember(GroupMemberGroupID,GroupMemberID,GroupMemberCreated,GroupMemberIsAdmin)" " Values ("
			+ QuotedStr(GroupID) + "," + QuotedStr(GroupMemberID) + ",'" + Now().FormatString
			("YYYY-mm-DD HH:mm:ss") + "'," + IntToStr(IsAdmin) + ")";
		AccQuery->Close();
		AccQuery->SQL->Text = InsertString;
		AccQuery->ExecSQL();
	}
	catch (Exception &e) {
		AccQuery->Close();
		throw Exception("����Ⱥ��Ա����!");
	}
}

// ---------------------------------------------------------------------------
void TMessageManage::UpdateMessageMember(String GroupID, String GroupMemberID,
	int IsAdmin) {
	try {
		String UpdateString = "Update tbGroupMember set GroupMemberIsAdmin=" +
			IntToStr(IsAdmin) + " where GroupMemberGroupID=" + QuotedStr(GroupID) +
			" and GroupMemberID=" + QuotedStr(GroupMemberID);
		AccQuery->Close();
		AccQuery->SQL->Text = UpdateString;
		AccQuery->ExecSQL();
	}
	catch (Exception &e) {
		AccQuery->Close();
		throw Exception("����Ⱥ��Ա����!");
	}
}

// ---------------------------------------------------------------------------
void TMessageManage::DelMessageMember(String GroupID, String GroupMemberID) {
	try {
		String deleteString =
			"delete from tbGroupMember where GroupMemberGroupID=" + QuotedStr(GroupID) +
			" and GroupMemberID=" + QuotedStr(GroupMemberID);
		AccQuery->Close();
		AccQuery->SQL->Text = deleteString;
		AccQuery->ExecSQL();
	}
	catch (Exception &e) {
		AccQuery->Close();
		throw Exception("ɾ��Ⱥ��Ա����!");
	}
}

// ----------------------------------------------------------------------------
TJSONArray* TMessageManage::GetMessageGroupList() {
	// ע�⣬�����㷨û�п���Blob�ֶΡ�
	TJSONArray *retArray = new TJSONArray();
	if (curLoginUser == NULL)
		return false;
	TJSONObject *itemJson;
	AccQuery->Close();
	AccQuery->SQL->Text =
		"select Groupid as id,GroupName as name,GroupMemo,GroupCreated,GroupCreator  from tbMessageGroup where  " +
		QuotedStr(curLoginUser->UserID) +
		" in (select GroupMemberID from tbGroupMember where GroupMemberGroupID = Groupid)";
	AccQuery->Open();
	while (!AccQuery->Eof) {
		itemJson = new TJSONObject();
		for (int i = 0; i < AccQuery->FieldCount; i++) {
			itemJson->AddPair
				(new TJSONPair(AccQuery->Fields->Fields[i]->FieldName,
				AccQuery->Fields->Fields[i]->AsString));
		}
		retArray->AddElement(itemJson);
		AccQuery->Next();
	}
	return retArray;
}

// ---------------------------------------------------------------------------
TJSONArray* TMessageManage::GetGroupMemberList(String GroudId) {
	// ע�⣬�����㷨û�п���Blob�ֶΡ�
	TJSONArray *retArray = new TJSONArray();
	TJSONObject *itemJson;
	AccQuery->Close();
	AccQuery->SQL->Text =
		"select GroupMemberID as userid,EmpName as username,GroupMemberIsAdmin  from tbGroupMember,tbEmployeeData where GroupMemberID=EmpPKID and GroupMemberGroupID =" +
		QuotedStr(GroudId) + " order by GroupMemberIsAdmin DESC";
	AccQuery->Open();
	while (!AccQuery->Eof) {
		itemJson = new TJSONObject();
		for (int i = 0; i < AccQuery->FieldCount; i++) {
			itemJson->AddPair
				(new TJSONPair(AccQuery->Fields->Fields[i]->FieldName,
				AccQuery->Fields->Fields[i]->AsString));
		}
		retArray->AddElement(itemJson);
		AccQuery->Next();
	}
	return retArray;
}

// ---------------------------------------------------------------------------
TJSONArray* TMessageManage::GetAllEmployee(String GroupId) {
	// ע�⣬�����㷨û�п���Blob�ֶΡ�
	TJSONArray *retArray = new TJSONArray();
	TJSONObject *itemJson;
	AccQuery->Close();
	AccQuery->SQL->Text =
		"select EmpPKID as userid,EmpName as username from tbEmployeeData left join tbGroupMember on GroupMemberID=EmpPKID and GroupMemberGroupID =" +
		QuotedStr(GroupId) + " order by GroupMemberID DESC";
	AccQuery->Open();
	while (!AccQuery->Eof) {
		itemJson = new TJSONObject();
		for (int i = 0; i < AccQuery->FieldCount; i++) {
			itemJson->AddPair
				(new TJSONPair(AccQuery->Fields->Fields[i]->FieldName,
				AccQuery->Fields->Fields[i]->AsString));
		}
		retArray->AddElement(itemJson);
		AccQuery->Next();
	}
	return retArray;
}

// ---------------------------------------------------------------------------
bool TMessageManage::IsGroupMember(String GroupId, String MemberId) {
	AccQuery->Close();
	AccQuery->SQL->Text = "select * from tbGroupMember where GroupMemberID =" +
		QuotedStr(MemberId) + " and GroupMemberGroupID=" + QuotedStr(GroupId);
	AccQuery->Open();
	if (AccQuery->RecordCount > 0)
		return true;
	return false;
}

// ----------------------------------------------------------------------------
void TMessageManage::SendMissMessage(String UserId) {
	// ע�⣬�����㷨û�п���Blob�ֶΡ�
	AccQuery->Close();
	String SQLText="select tbMissMember.RecMsgID,tbMissMember.RecMsgUserID, tbMessageRecords.*,EmpName as username "
					" from tbMissMember left join tbMessageRecords on RecMsgID=MsgID "
					" left join tbEmployeeData on MsgUserID=EmpPKID "
					" where RecMsgRead=0 and RecMsgUserID ="+QuotedStr(UserId) + " order by MsgSendTime";
	AccQuery->SQL->Text = SQLText;
	AccQuery->Open();
	while (!AccQuery->Eof) {
		if (AccQuery->FieldByName("MsgRecType")->AsInteger == 2) {  //����
			SendMissMessageToUser(AccQuery->FieldByName("MsagContent")
				->AsString, AccQuery->FieldByName("MsgUserID")->AsString,
				AccQuery->FieldByName("username")->AsString,
				AccQuery->FieldByName("MsgID")->AsString,AccQuery->FieldByName("MsgSendTime")->AsString);
		}

		else if (AccQuery->FieldByName("MsgRecType")->AsInteger == 3) { //Ⱥ
			SendMissMessageToGroup(AccQuery->FieldByName("MsagContent")
				->AsString, AccQuery->FieldByName("MsgUserID")->AsString,
				AccQuery->FieldByName("username")->AsString,AccQuery->FieldByName("MsgReceiver")->AsString,
				AccQuery->FieldByName("MsgID")->AsString,AccQuery->FieldByName("MsgSendTime")->AsString);
		}
		else  /*if(AccQuery->FieldByName("MsgRecType")->AsInteger == 1) */{  //���� ��˾
			SendMissMessageToDepartment(AccQuery->FieldByName("MsagContent")
				->AsString, AccQuery->FieldByName("MsgUserID")->AsString,
				AccQuery->FieldByName("username")->AsString,
				AccQuery->FieldByName("MsgReceiver")->AsString,
				AccQuery->FieldByName("MsgID")->AsString,AccQuery->FieldByName("MsgSendTime")->AsString);
		}
		AccQuery->Next();
	}
	AccQuery->Close();
}

// ---------------------------------------------------------------------------
TJSONArray* TMessageManage::GetLatelyMessage(String UserId, String ReceId,int RecType) {
	// ע�⣬�����㷨û�п���Blob�ֶΡ�
	TJSONArray *retArray = new TJSONArray();
	TJSONObject *itemJson;
	if (RecType == 2) { //�û����û���Ϣ
		AccQuery->Close();
		AccQuery->SQL->Text =
			"select tbMessageRecords.*,EmpName as username from tbMessageRecords,tbEmployeeData where  MsgRecType =" +
			IntToStr(RecType) + " and ( MsgUserID=EmpPKID and  MsgUserID='" +
			UserId + "' and MsgReceiver ='" + ReceId +
			"') or ( MsgUserID=EmpPKID and MsgUserID='" + ReceId +
			"' and MsgReceiver ='" + UserId + "') order by MsgSendTime ";
		AccQuery->Open();
		while (!AccQuery->Eof) {
			itemJson = new TJSONObject();
			for (int i = 0; i < AccQuery->FieldCount; i++) {
				itemJson->AddPair
					(new TJSONPair(AccQuery->Fields->Fields[i]->FieldName,
					AccQuery->Fields->Fields[i]->AsString));
			}
			retArray->AddElement(itemJson);
			AccQuery->Next();
		}
	}
	else { //��˾�����ţ�Ⱥ��Ϣ
		AccQuery->Close();
		AccQuery->SQL->Text =
			"select tbMessageRecords.*,EmpName as username from tbMessageRecords left join tbEmployeeData on MsgUserID=EmpPKID  where MsgRecType =" +
			IntToStr(RecType) + " and  MsgReceiver ='" + ReceId +
			"' order by MsgSendTime ";
		AccQuery->Open();
		while (!AccQuery->Eof) {
			itemJson = new TJSONObject();
			for (int i = 0; i < AccQuery->FieldCount; i++) {
				itemJson->AddPair
					(new TJSONPair(AccQuery->Fields->Fields[i]->FieldName,
					AccQuery->Fields->Fields[i]->AsString));
			}
			retArray->AddElement(itemJson);
			AccQuery->Next();
		}

   }
	return retArray;
}

// ---------------------------------------------------------------------------
bool TMessageManage::SendMissMessageToUser(String const Msg,
	String const FromID, String const FromName, String const MsgID,String const sendtime) {
	TJSONValue *Resp = NULL;
	String MesgTrimmed;
	TLoginUserRecord * RecUser = NULL;
	TJSONObject *JSONMsg = NULL;
	bool result = false;
	MesgTrimmed = Trim(Msg);

	// no message to send, so just exit
	if (Msg == EmptyStr)
		return false;

	if (curLoginUser == NULL)
		return false;

	JSONMsg = new TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
	JSONMsg->AddPair(new TJSONPair("from", FromID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", FromName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
	JSONMsg->AddPair(new TJSONPair("to", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	JSONMsg->AddPair(new TJSONPair("datetime",sendtime));
	JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));

	result = DMServerContainer->FSDSServer->NotifyCallback(curLoginUser->CallBackClientID, SMsgCallback, JSONMsg, Resp);
	if (result&&Resp != NULL)
		Resp->Free();
	if (result) {
		Query->Close();
		Query->SQL->Text = "update tbMissMember set RecMsgRead=1 where RecMsgID='" +
			MsgID + "' and RecMsgUserID='" + curLoginUser->UserID + "'";
		Query->ExecSQL();
	}
	return result;
}

// ---------------------------------------------------------------------------
bool TMessageManage::SendMissMessageToDepartment(String const Msg, String const FromID,String const FromName,
	String const DepartmentID, String const MsgID,String const sendtime) {
	String MesgTrimmed;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);
	bool allSender = true;
	bool curSender = false;

	// no message to send, so just exit
	if (Msg == EmptyStr)
		return false;

	if (curLoginUser == NULL)
		return false;


	// wrap the message in a JSON object
	JSONMsg = new TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
	JSONMsg->AddPair(new TJSONPair("from", FromID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", FromName));
	if(DepartmentID=="0")
	   JSONMsg->AddPair(new TJSONPair("msgtype", "0"));
	else
	   JSONMsg->AddPair(new TJSONPair("msgtype", "1"));
	JSONMsg->AddPair(new TJSONPair("to", DepartmentID));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	JSONMsg->AddPair(new TJSONPair("datetime",sendtime));
	JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));

	curSender = DMServerContainer->FSDSServer->NotifyCallback
		(curLoginUser->CallBackClientID, SMsgCallback, JSONMsg, Resp);
	if (curSender&&Resp != NULL)
		Resp->Free();
	if (curSender) {
		Query->Close();
		Query->SQL->Text = "update tbMissMember set RecMsgRead=1 where RecMsgID='" +
			MsgID + "' and RecMsgUserID='" + curLoginUser->UserID + "'";
		Query->ExecSQL();
	}
	return curSender;
}

// ---------------------------------------------------------------------------
bool TMessageManage::SendMissMessageToGroup(String const Msg,String const FromID,String const FromName,
	String const GroupID, String const MsgID,String const sendtime) {
	String MesgTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);
	bool allSender = true;
	bool curSender = false;

	// no message to send, so just exit
	if (Msg == EmptyStr)
		return false;

	if (curLoginUser == NULL)
		return false;


	// wrap the message in a JSON object
	JSONMsg = new TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
	JSONMsg->AddPair(new TJSONPair("from", FromID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", FromName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "3"));
	JSONMsg->AddPair(new TJSONPair("to", GroupID));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	JSONMsg->AddPair(new TJSONPair("datetime",sendtime));
	JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));

	curSender = DMServerContainer->FSDSServer->NotifyCallback
		(curLoginUser->CallBackClientID, SMsgCallback, JSONMsg, Resp);
	if (curSender&&Resp != NULL)
		Resp->Free();
	if (curSender) {
		Query->Close();
		Query->SQL->Text = "update tbMissMember set RecMsgRead=1 where RecMsgID='" +
			MsgID + "' and RecMsgUserID='" + curLoginUser->UserID + "'";
		Query->ExecSQL();
	}
	return curSender;
}
// ---------------------------------------------------------------------------
String  TMessageManage::GetHTMLEscapedString(String const Value)
{
  TReplaceFlags Flags;
	Flags << rfReplaceAll;
  String Result = Value;
  Result = StringReplace(Result, "&", "&amp;", Flags);
  Result = StringReplace(Result, "\"", "&quot;", Flags);
  Result = StringReplace(Result, "<", "&lt;", Flags);
  Result = StringReplace(Result, ">", "&gt;", Flags);
	return Result;
}
//---------------------------------------------------------------------------
TJSONArray*  TMessageManage::GetUserList()
{
	return DMServerContainer->GetLoginUserList();
}
//---------------------------------------------------------------------------
bool  TMessageManage::UpdateCurUserCallbackClientID(String const Value)
{
	String FCallbackIdTrimmed = Trim(Value);
	if(FCallbackIdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;
	curLoginUser->CallBackClientID = FCallbackIdTrimmed;
	return true;
}
//---------------------------------------------------------------------------
void  TMessageManage::SaveMessage(String MsgID,String MsgUserID,int MsgRecType,String MsgReceiver,String MsgContent)
{
	try
	{
		EmpQuery->Close();
		EmpQuery->SQL->Clear();
		switch (curLoginUser->AccDbType)
		{
			case 1:
				EmpQuery->SQL->Text = "exec tbMessageRecords_update '"+MsgID+"','"+MsgUserID+"',"+IntToStr(MsgRecType)+",'"+MsgReceiver+"','"+MsgContent+"','"+FormatDateTime("YYYY-MM-DD HH:MM:SS",Now())+"'";
				break;
			case 2:
				EmpQuery->SQL->Text = "{call tbMessageRecords_update('"+MsgID+"','"+MsgUserID+"',"+IntToStr(MsgRecType)+",'"+MsgReceiver+"','"+MsgContent+"','"+FormatDateTime("YYYY-MM-DD HH:MM:SS",Now())+"')}";
				break;
		}
		EmpQuery->ExecSQL();
		EmpQuery->Close();
	}
	catch(Exception &e)
	{
		throw Exception(e.Message);
	}
}
//---------------------------------------------------------------------------
void  TMessageManage::SaveMsgToReceiver(String MsgID,String UserID,int online)
{
	try
	{
		EmpQuery->Close();
		EmpQuery->SQL->Clear();
		switch (curLoginUser->AccDbType)
		{
			case 1:
				EmpQuery->SQL->Text = "exec tbMissMember_insert "+QuotedStr(MsgID)+","+QuotedStr(UserID)+","+IntToStr(online);
				break;
			case 2:
				EmpQuery->SQL->Text = "{call tbMissMember_insert("+QuotedStr(MsgID)+","+QuotedStr(UserID)+","+IntToStr(online)+")}";
				break;
		}
		EmpQuery->ExecSQL();
		EmpQuery->Close();
	}
	catch(Exception &e)
	{
		throw Exception(e.Message);
	}
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToAll(String const Msg)
{
	String MesgTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);

  //no message to send, so just exit
	if(Msg == EmptyStr)
		return false;

	if(curLoginUser==NULL)
		return false;
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgID = GUIDToString(msgGuid);

	//��Ҫ�ж��Ƿ���ͬһ�����ף��������ͬһ�����׵��û�������
	//�ȱ�����Ϣ��Ȼ������ж��Ƿ��¼
	SaveMessage(MsgID,curLoginUser->UserID,0,"0",MesgTrimmed);
	SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1";
	AccQuery->Open();
	while(!AccQuery->Eof)
	{
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		if(AnsiCompareText(curLoginUser->UserID, UserID) != 0) //���Ǳ���
		{
			RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
			if(RecUser==NULL)
			   SaveMsgToReceiver(MsgID,UserID);
			else
			  SaveMsgToReceiver(MsgID,UserID,1);
		}
		AccQuery->Next();
	}
	AccQuery->Close();

  //wrap the message in a JSON object
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
	JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "0"));
	JSONMsg->AddPair(new TJSONPair("to", "0"));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));

  //Send the message to all logged in users
  return DMServerContainer->FSDSServer->BroadcastMessage(SMessageChannel+curLoginUser->AccBookID, SMsgCallback, JSONMsg);
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToUser(String const Msg,	String const UserID)
{
	TJSONValue *Resp = NULL;
	String MesgTrimmed;
	TLoginUserRecord * RecUser = NULL;
	TJSONObject *JSONMsg = NULL;
	bool result = false;
	MesgTrimmed = Trim(Msg);

  //no message to send, so just exit
	if(Msg == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

	//���ܷ��͸��Լ�
	if(AnsiCompareText(curLoginUser->UserID, UserID) == 0) return false;

 //��Ҫ�ж��Ƿ���ͬһ�����ף��Ƿ��¼������û�û��¼�������ͣ��򱣴�
	RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		//������Ϣ
		TGUID msgGuid;
		CreateGUID(msgGuid);
		String MsgID = GUIDToString(msgGuid);
		SaveMessage(MsgID,curLoginUser->UserID,2,UserID,MesgTrimmed);
   if(RecUser==NULL)
		SaveMsgToReceiver(MsgID,UserID,0);
	else
		SaveMsgToReceiver(MsgID,UserID,1);
		SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��


		//wrap the message in a JSON object
		JSONMsg = new  TJSONObject();
		JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
		JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
		JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
		JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
		JSONMsg->AddPair(new TJSONPair("to",UserID ));
		JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
		JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
		JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));
	   if(RecUser)
		{
		 Resp=NULL;
		//Send the message to logged in user
		 result = DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, (TJSONObject*)( JSONMsg->Clone()), Resp);
		 if(result&&Resp!=NULL)
			Resp->Free();
		}
		//Send the message to myself ��һ�½Ƕȣ��Է���ǰ̨������ȷ�Ĵ���
		if(FNeedSendToOwn)
		{
			JSONMsg->RemovePair("from");
			JSONMsg->AddPair(new TJSONPair("from",UserID ));
			TSendMessageThread *sendMessageThread=new TSendMessageThread(DMServerContainer->FSDSServer,curLoginUser,JSONMsg);
		}
	   delete JSONMsg;
	   return result;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToDepartment(String const Msg, String const DepartmentID)
{
	String MesgTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);
	bool allSender = true;
	bool curSender = false;

  //no message to send, so just exit
	if(Msg == EmptyStr) return false;


	if(curLoginUser==NULL) return false;
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgID = GUIDToString(msgGuid);

	//��Ҫ�ж��Ƿ���ͬһ�����ף��������ͬһ�����׵��û�������
	//�ȱ�����Ϣ��Ȼ������ж��Ƿ��¼
	SaveMessage(MsgID,curLoginUser->UserID,1,DepartmentID,MesgTrimmed);
	SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��
  //wrap the message in a JSON object
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
	JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "1"));
	JSONMsg->AddPair(new TJSONPair("to", DepartmentID));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpDeptCodeFKID="+QuotedStr(DepartmentID);
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)   //���Ǳ���
		{
			RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
			if(RecUser==NULL)
				SaveMsgToReceiver(MsgID,UserID);  //û����
			else
			{
				SaveMsgToReceiver(MsgID,UserID,1);
				if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)  //�����ظ�����
				{
					curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback,(TJSONObject*)( JSONMsg->Clone()), Resp));
					allSender = allSender || curSender;
					if(curSender&&Resp!=NULL)
					   Resp->Free();
				}
			}
		}
		AccQuery->Next();
	}
	AccQuery->Close();
	//Send the message to myself  ���п��ܸ��������ŷ�����Ϣ���Լ����ڸò���
  if(FNeedSendToOwn)
	TSendMessageThread *sendMessageThread=new TSendMessageThread(DMServerContainer->FSDSServer,curLoginUser,(TJSONValue*)( JSONMsg->Clone()));
   delete JSONMsg;
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToGroup(String const Msg, String const GroupID)
{
	String MesgTrimmed;

	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);
	bool allSender = true;
	bool curSender = false;

  //no message to send, so just exit
	if(Msg == EmptyStr) return false;


	if(curLoginUser==NULL) return false;
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgID = GUIDToString(msgGuid);

	//��Ҫ�ж��Ƿ���ͬһ�����ף��������ͬһ�����׵��û�������
	//�ȱ�����Ϣ��Ȼ������ж��Ƿ��¼
	SaveMessage(MsgID,curLoginUser->UserID,3,GroupID,MesgTrimmed);
	SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��
  //wrap the message in a JSON object
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
	JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "3"));
	JSONMsg->AddPair(new TJSONPair("to", GroupID));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));

		//Send the message to myself
  //		DMServerContainer->FSDSServer->NotifyCallback(curLoginUser->CallBackClientID, SMsgCallback, (TJSONObject*)( JSONMsg->Clone()), Resp);

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpPKID in (select GroupMemberID from tbGroupMember where GroupMemberGroupID="+QuotedStr(GroupID)+")";
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)   //���Ǳ���
		{
			RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
			if(RecUser==NULL)
				SaveMsgToReceiver(MsgID,UserID);  //û����
			else
			{
				SaveMsgToReceiver(MsgID,UserID,1);
				 curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, (TJSONObject*)(JSONMsg->Clone()), Resp));
				 allSender = allSender || curSender;
				 if(curSender&&Resp!=NULL)
					Resp->Free();
			}
		}
		AccQuery->Next();
	}
	AccQuery->Close();
  if(FNeedSendToOwn)
	 TSendMessageThread *sendMessageThread=new TSendMessageThread(DMServerContainer->FSDSServer,curLoginUser,JSONMsg);
  delete JSONMsg;
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToJob(String const Msg, String const JobID)
{
	String MesgTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);
	bool allSender = true;
	bool curSender = false;

  //no message to send, so just exit
	if(Msg == EmptyStr) return false;

	if(curLoginUser==NULL) return false;
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgID = GUIDToString(msgGuid);

	//��Ҫ�ж��Ƿ���ͬһ�����ף��������ͬһ�����׵��û�������
	//�ȱ�����Ϣ��Ȼ������ж��Ƿ��¼
	SaveMessage(MsgID,curLoginUser->UserID,3,"0",MesgTrimmed);
	SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��
  //wrap the message in a JSON object

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpPKID in (select EDEmpPK_FKID from tbEmpDuty where EDDutyPK_FKID="+QuotedStr(JobID)+")";
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser==NULL)
			SaveMsgToReceiver(MsgID,UserID);  //û����
		else
		{
			SaveMsgToReceiver(MsgID,UserID,1);
			JSONMsg = new  TJSONObject();
			JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
			JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
			JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
			JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
			JSONMsg->AddPair(new TJSONPair("to", UserID));
			JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
			JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
			JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));
		if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)   //���Ǳ���
		 {

			 curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp));
			 allSender = allSender || curSender;
			 if(curSender&&Resp!=NULL)
				Resp->Free();
		}
		else
		{

			TSendMessageThread *sendMessageThread=new TSendMessageThread(DMServerContainer->FSDSServer,curLoginUser,JSONMsg);
			delete JSONMsg;
		}
	 }

		AccQuery->Next();
	}
	AccQuery->Close();
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToRole(String const Msg, String const RoleID)
{
	String MesgTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	MesgTrimmed = Trim(Msg);
	bool allSender = true;
	bool curSender = false;

  //no message to send, so just exit
	if(Msg == EmptyStr) return false;

	if(curLoginUser==NULL) return false;
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgID = GUIDToString(msgGuid);

	//��Ҫ�ж��Ƿ���ͬһ�����ף��������ͬһ�����׵��û�������
	//�ȱ�����Ϣ��Ȼ������ж��Ƿ��¼
	SaveMessage(MsgID,curLoginUser->UserID,3,"0",MesgTrimmed);
	SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��
  //wrap the message in a JSON object

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpPKID in (select REEmpPK_FKID from tbRoleEmp where RERolePK_FKID="+QuotedStr(RoleID)+")";
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;

			RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
			if(RecUser==NULL)
				SaveMsgToReceiver(MsgID,UserID);  //û����
			else
			{
				SaveMsgToReceiver(MsgID,UserID,1);
				JSONMsg = new  TJSONObject();
				JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
				JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
				JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
				JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
				JSONMsg->AddPair(new TJSONPair("to", UserID));
				JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
				JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
				JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));
				if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)   //���Ǳ���
				  {
					 curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp));
					 allSender = allSender || curSender;
					 if(curSender&&Resp!=NULL)
						Resp->Free();
				  }
				else
				{
						TSendMessageThread *sendMessageThread=new TSendMessageThread(DMServerContainer->FSDSServer,curLoginUser,JSONMsg);
						delete JSONMsg;
				}
		}
		AccQuery->Next();

	}
	AccQuery->Close();
  return allSender;
}

//---------------------------------------------------------------------------
bool  TMessageManage::SendMessageToFollow(String const Msg)
{
	String MesgTrimmed;

	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	MesgTrimmed = Trim(Msg);
	bool allSender = false;
	bool curSender = false;

  //no message to send, so just exit
	if(Msg == EmptyStr) return false;

	if(curLoginUser==NULL) return false;
	TGUID msgGuid;
	CreateGUID(msgGuid);
	String MsgID = GUIDToString(msgGuid);

	//��Ҫ�ж��Ƿ���ͬһ�����ף��������ͬһ�����׵��û�������
	//�ȱ�����Ϣ��Ȼ������ж��Ƿ��¼
	SaveMessage(MsgID,curLoginUser->UserID,0,"0",MesgTrimmed);
	SaveMsgToReceiver(MsgID,curLoginUser->UserID,1);//���Լ���һ��
  //wrap the message in a JSON object
	for(int i=0;i<curLoginUser->FollowList->Count;i++)
	{
		String UserID = curLoginUser->FollowList->Strings[i];
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser==NULL)
			SaveMsgToReceiver(MsgID,UserID);  //û����
		else
		{
			SaveMsgToReceiver(MsgID,UserID,1);
			TJSONObject *JSONMsg = new  TJSONObject();
			JSONMsg->AddPair(new TJSONPair("notificationType", "message"));
			JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
			JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
			JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
			JSONMsg->AddPair(new TJSONPair("to", RecUser->UserID));
			JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
			JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
			JSONMsg->AddPair(new TJSONPair("message", MesgTrimmed));
			if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
			{
				/********************************************************************
				//NotifyCallback�������Իؽ�ָ���ؽ�ͨ�����ض��ͻ���ʶ���Լ��ؽ�ʶ��Ŀͻ���
				//�������  ��������    ����˵��
				//Params01: ChannelName �ؽ�ͨ������;
				//Params02: ClientId    �ͻ���ʶ��;
				//Params03: CallbackId  �ؽ�ʶ��
				//Params04: Msg         ���ݵ���Ѷ;
				//Params05: Response    ���ؽпͻ��˵Ļش���Ѷ
				********************************************************************/
				curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp));
				allSender = curSender || allSender;
				if(curSender&&Resp!=NULL)
					Resp->Free();
			}
			else  //���Լ�Ҳ��
			{
				TSendMessageThread *sendMessageThread=new TSendMessageThread(DMServerContainer->FSDSServer,curLoginUser,JSONMsg);
				delete JSONMsg;
		   }
		}
  }
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendCMDToFollow(String const cmdStr)
{
	String cmdTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;
	bool curSender = false;

	//no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object
  for(int i=0;i<curLoginUser->FollowList->Count;i++)
  {
		String UserID = curLoginUser->FollowList->Strings[i];
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser)
		{
			if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
			{
				TJSONObject* JSONMsg = new  TJSONObject();
				JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
				JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
				JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
				JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
				JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
				JSONMsg->AddPair(new TJSONPair("to", RecUser->UserID));
				JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
				JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
				curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp));
				allSender = allSender || curSender;
				if(curSender&&Resp!=NULL)
					Resp->Free();
			}
		}
  }
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendCMDToAll(String const cmdStr)
{
	String cmdTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONObject *JSONMsg;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;

  //no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
	JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
	JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "0"));
	JSONMsg->AddPair(new TJSONPair("to", "0"));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
	allSender = DMServerContainer->FSDSServer->BroadcastMessage(SMessageChannel+curLoginUser->AccBookID,SMsgCallback, JSONMsg);
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendCMDToUser(String const cmdStr, String const UserID)
{
	String cmdTrimmed;

	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;

	//no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object
	RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
	if(RecUser)
	{
		if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
		{
			JSONMsg = new  TJSONObject();
			JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
			JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
			JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
			JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
			JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
			JSONMsg->AddPair(new TJSONPair("to", RecUser->UserID));
			JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
			JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
			allSender = DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp);
			if(allSender&&Resp!=NULL)
				Resp->Free();
		}
  }
	return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendCMDToDepartment(String const cmdStr, String const DepartmentID)
{
	String cmdTrimmed;

	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;
	bool curSender = false;

	//no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
	JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
	JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "1"));
	JSONMsg->AddPair(new TJSONPair("to", DepartmentID));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpDeptCodeFKID="+QuotedStr(DepartmentID);
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser)
		{
			if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
			{
				curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, (TJSONObject*)(JSONMsg->Clone()), Resp));
				allSender = allSender || curSender;
				if(curSender&&Resp!=NULL)
					Resp->Free();
			}
		}
		AccQuery->Next();
	}
	AccQuery->Close();
  return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendCMDToGroup(String const cmdStr, String const GroupID)
{
	String cmdTrimmed;

	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;
	bool curSender = false;

	//no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
	JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
	JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
	JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
	JSONMsg->AddPair(new TJSONPair("msgtype", "3"));
	JSONMsg->AddPair(new TJSONPair("to", GroupID));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpPKID in (select GroupMemberID from tbGroupMember where GroupMemberGroupID="+QuotedStr(GroupID)+")";
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser)
	  {
			if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
			{
				curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, (TJSONObject*)(JSONMsg->Clone()), Resp));
				allSender = allSender || curSender;
				if(curSender&&Resp!=NULL)
					Resp->Free();
			}
		}
		AccQuery->Next();
	}
	AccQuery->Close();
	return allSender;
}
bool  TMessageManage::SendCMDToRole(String const cmdStr, String const RoleID)
{
	String cmdTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;
	bool curSender = false;

	//no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpPKID in (select REEmpPK_FKID from tbRoleEmp where RERolePK_FKID="+QuotedStr(RoleID)+")";
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser)
	  {
			if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
			{
				JSONMsg = new  TJSONObject();
				JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
				JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
				JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
				JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
				JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
				JSONMsg->AddPair(new TJSONPair("to", UserID));
				JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
				JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
				curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp));
				allSender = allSender || curSender;
				if(curSender&&Resp!=NULL)
					Resp->Free();
			}
		}
		AccQuery->Next();
	}
	AccQuery->Close();
	return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendCMDToJob(String const cmdStr, String const JobID)
{
	String cmdTrimmed;
	TLoginUserRecord *RecUser = NULL;
	TJSONValue *Resp;
	TJSONObject *JSONMsg;
	cmdTrimmed = Trim(cmdStr);
	bool allSender = false;
	bool curSender = false;

	//no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;

  //get the current user
	if(curLoginUser==NULL) return false;

  //wrap the message in a JSON object

	AccQuery->Close();
	AccQuery->SQL->Text="select EmpPKID from tbEmployeeData where EmpState=1 and EmpPKID in (select EDEmpPK_FKID from tbEmpDuty where EDDutyPK_FKID="+QuotedStr(JobID)+")";
	AccQuery->Open();
	while(!AccQuery->Eof)
  {
		String UserID = AccQuery->FieldByName("EmpPKID")->AsString;
		RecUser = DMServerContainer->GetLoginUser(UserID,curLoginUser->AccBookID);
		if(RecUser)
	  {
			if(AnsiCompareText(curLoginUser->UserID, UserID) != 0)
			{
				JSONMsg = new  TJSONObject();
				JSONMsg->AddPair(new TJSONPair("notificationType", "cmd"));
				JSONMsg->AddPair(new TJSONPair("cmd", cmdTrimmed));
				JSONMsg->AddPair(new TJSONPair("from", curLoginUser->UserID));
				JSONMsg->AddPair(new TJSONPair("fromusrname", curLoginUser->UserName));
				JSONMsg->AddPair(new TJSONPair("msgtype", "2"));
				JSONMsg->AddPair(new TJSONPair("to", UserID));
				JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
				JSONMsg->AddPair(new TJSONPair("accbookid", curLoginUser->AccBookID));
				curSender = (DMServerContainer->FSDSServer->NotifyCallback(RecUser->CallBackClientID, SMsgCallback, JSONMsg, Resp));
				allSender = allSender || curSender;
				if(curSender&&Resp!=NULL)
					Resp->Free();
			}
		}
		AccQuery->Next();
	}
	AccQuery->Close();
	return allSender;
}
//---------------------------------------------------------------------------
bool  TMessageManage::SendMgrMessage(int itype, String const Msg)
{
	String cmdTrimmed=Trim(Msg);
	TJSONObject *JSONMsg;
	bool allSender = false;

  //no message to send, so just exit
	if(cmdTrimmed == EmptyStr) return false;


  //wrap the message in a JSON object
	String AcckBookID="0";
	JSONMsg = new  TJSONObject();
	JSONMsg->AddPair(new TJSONPair("notificationType", "mgr"));
	JSONMsg->AddPair(new TJSONPair("from", "Admin"));
	JSONMsg->AddPair(new TJSONPair("fromusrname", "Admin"));
	JSONMsg->AddPair(new TJSONPair("msgtype", itype));
	JSONMsg->AddPair(new TJSONPair("to", "0"));
	JSONMsg->AddPair(new TJSONPair("accbookid", AcckBookID));
	JSONMsg->AddPair(new TJSONPair("datetime", Now().FormatString("YYYY-mm-DD HH:mm:ss")));
	JSONMsg->AddPair(new TJSONPair("message", cmdTrimmed));
	allSender = DMServerContainer->FSDSServer->BroadcastMessage(SMessageChannel+AcckBookID,SMsgCallback, JSONMsg);
  return allSender;
}