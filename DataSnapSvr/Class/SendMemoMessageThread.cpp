//---------------------------------------------------------------------------

#pragma hdrstop

#include "SendMemoMessageThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TSendMemoMessageThread::TSendMemoMessageThread(TADOConnection *AConnection,String AID)
{
	m_Connection=AConnection;
	AccQuery = new TADOQuery(NULL);
	AccQuery->ParamCheck = false;
	AccQuery->EnableBCD = false;
	AccQuery->CommandTimeout = 60;
	AccQuery->Connection = m_Connection;

	FID= AID;
	FFMessageManage = new TMessageManage(NULL);
	FFMessageManage->NeedSendToOwn=false;
}
//---------------------------------------------------------------------------
void __fastcall TSendMemoMessageThread::Execute()
{
  FreeOnTerminate=true;
   AccQuery->Close();
   AccQuery->SQL->Text="Select * from tbMemo where MemoID="+QuotedStr(FID);
   AccQuery->Open();
   if(AccQuery->RecordCount>0)
	FTitle=AccQuery->FieldByName("MemoTopic")->AsString;
   FTitle=L"±¸ÍüÂ¼Í¨Öª:"+FTitle;
   AccQuery->Close();
   AccQuery->SQL->Text="select * from tbMemoUser where  MemoUserID="+QuotedStr(FID);
   AccQuery->Open();
   AccQuery->First();
   while(!AccQuery->Eof)
   {
	   String ToUser= AccQuery->FieldByName("MemoUserPartner")->AsString;
	   FFMessageManage->SendMessageToUser(FTitle,ToUser);
	   AccQuery->Next();
   }
   AccQuery->Close();
   delete  AccQuery;
   delete  FFMessageManage;
}
