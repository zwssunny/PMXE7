//---------------------------------------------------------------------------

#pragma hdrstop

#include "SendEmailMessageThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TSendEmailMessageThread::TSendEmailMessageThread(TADOConnection *AConnection,String AEmailID)
{
	m_Connection=AConnection;
	AccQuery = new TADOQuery(NULL);
	AccQuery->ParamCheck = false;
	AccQuery->EnableBCD = false;
	AccQuery->CommandTimeout = 60;
	AccQuery->Connection = m_Connection;

	FEmailID= AEmailID;
	FFMessageManage = new TMessageManage(NULL);
	FFMessageManage->NeedSendToOwn=false;
}
//---------------------------------------------------------------------------
void __fastcall TSendEmailMessageThread::Execute()
{
  FreeOnTerminate=true;
   AccQuery->Close();
   AccQuery->SQL->Text="Select * from tbMessege where MsgPKID="+QuotedStr(FEmailID);
   AccQuery->Open();
   if(AccQuery->RecordCount>0)
	EmailTitle=AccQuery->FieldByName("MsgSubject")->AsString;
   EmailTitle=L"内部邮件通知:"+EmailTitle;
   AccQuery->Close();
   AccQuery->SQL->Text="select * from tbMessageRecSend where MRSMsgPK_FKID="+QuotedStr(FEmailID);
   AccQuery->Open();
   AccQuery->First();
   while(!AccQuery->Eof)
   {
	   String ToUser= AccQuery->FieldByName("MRSRecFKID")->AsString;
	   FFMessageManage->SendMessageToUser(EmailTitle,ToUser);
	   AccQuery->Next();
   }
   AccQuery->Close();
   delete  AccQuery;
   delete  FFMessageManage;
}
//---------------------------------------------------------------------------
