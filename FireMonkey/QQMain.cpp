//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "QQMain.h"
#include <System.UITypes.hpp>
#include "QQMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmQQMain *frmQQMain;
//---------------------------------------------------------------------------
__fastcall TfrmQQMain::TfrmQQMain(TComponent* Owner,TClientBroker *AClientBroker)
	: TForm(Owner)
{
  FClientBroker=AClientBroker;
  FillCompanyTv();
  FClientBroker->HookCallBack=&MessageCallBackHook;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQQMain::FormClose(TObject *Sender, TCloseAction &Action)
{
   Action=TCloseAction::caHide;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQQMain::FillCompanyTv()
{
  TTreeViewItem  *ParentTrNode[11];  //最多10级
   String SortCode="";
   TQQUserRecord* QQUserRecord;
   TJSONArray* orgArray;
   TJSONObject* recdObject;
   int ilen=0;
  try
  {
	orgArray=FClientBroker->GetDepartmentAndUsersList();
	tvCompany->BeginUpdate();
    tvCompanyDeletion();
	tvCompany->Clear();
	QQUserRecord=new TQQUserRecord();
	QQUserRecord->State=1; //
	QQUserRecord->UserType=qutCompany;
	QQUserRecord->ID="0";
	QQUserRecord->Name=TabCompany->Text;
	QQUserRecord->iMessageFormID=0;
	ParentTrNode[0]= new TTreeViewItem(tvCompany);
	ParentTrNode[0]->Parent=tvCompany;
	ParentTrNode[0]->Text=QQUserRecord->Name;
	ParentTrNode[0]->TagObject=(TObject*)QQUserRecord;

	for(int i=0;i<orgArray->Size();i++)
	{
	  recdObject=(TJSONObject*)orgArray->Get(i);
	  SortCode=recdObject->Get("sortcode")->JsonValue->Value();
	  ilen=SortCode.Length()/8;//8个字符一级

	  ParentTrNode[ilen]= new TTreeViewItem(tvCompany);
	  ParentTrNode[ilen]->Parent=ParentTrNode[ilen-1];
	 // ParentTrNode[ilen]->Text=recdObject->Get("code")->JsonValue->Value()+"("+recdObject->Get("name")->JsonValue->Value()+")";
	  ParentTrNode[ilen]->Text=recdObject->Get("name")->JsonValue->Value();
	  QQUserRecord=new TQQUserRecord();
	  QQUserRecord->State=0;
		if(recdObject->Get("type")->JsonValue->Value().ToInt()==1)
		{
		 QQUserRecord->UserType=qutDepartment;
		// ParentTrNode[ilen]->ImageIndex =1;
	   //	 ParentTrNode[ilen]->SelectedIndex = 1;
		}
		else
		{
		 QQUserRecord->UserType=qutUser;
		// ParentTrNode[ilen]->ImageIndex =2;
		// ParentTrNode[ilen]->SelectedIndex = 2;
		}
		QQUserRecord->ID=recdObject->Get("id")->JsonValue->Value();
		QQUserRecord->Name=recdObject->Get("name")->JsonValue->Value();
		QQUserRecord->iMessageFormID=0;
		ParentTrNode[ilen]->TagObject = (TObject*)QQUserRecord;
	 // ParentTrNode[ilen]->StateIndex = 0;
	}
	delete recdObject;
	tvCompany->ExpandAll();
	UpdateLoginUserNode();   //更新登录用户状态
  }
  __finally
  {
	tvCompany->EndUpdate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmQQMain::tvCompanyDeletion()
{
  TTreeViewItem* ANode;
  for(int i=0;i<tvCompany->GlobalCount;i++)
  {
	  ANode=tvCompany->ItemByGlobalIndex(i);
	 TQQUserRecord *QQUserRecord=(TQQUserRecord*)(ANode->TagObject);
	 if(QQUserRecord)
	 {
	  if(QQUserRecord->iMessageFormID >0)  //关闭关联窗体
	  {
	   TForm * msgForm=(TForm*)(QQUserRecord->iMessageFormID);
	   if(msgForm)
		  msgForm->Close();
	  }
	   delete QQUserRecord;
	 }
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmQQMain::MessageCallBackHook(TJSONObject* Arg)
{
   if(Arg->Size()>2)
   {

	   String notificationType=Arg->Get("notificationType")->JsonValue->Value();
	   String UsrID,RecID;
	   TTreeViewItem* ANode=NULL;
	   TQQUserType msgtype;
	   String AccbookID=Arg->Get("accbookid")->JsonValue->Value();
	   if(FClientBroker->AccBookID!=AccbookID) return;
	   if(notificationType=="user_login"||notificationType=="user_logout")
	   {
		 UsrID=Arg->Get("from")->JsonValue->Value();
		 ANode=LocateCompanyTVNode(qutUser,UsrID);
		 //做一些更新用户节点信息
		 if(ANode)
		 {
//            PlaySound(L"cmd.wav",NULL,SND_ASYNC|SND_FILENAME);
			TQQUserRecord *userRecord=(TQQUserRecord*)( ANode->TagObject);
			if(userRecord)
			{

			if(notificationType=="user_login")
			{
				userRecord->State =1;
			   //	ANode->ImageIndex=3;
			   //	ANode->SelectedIndex=3;
			}
			else
				{
				userRecord->State =0;
			   //	ANode->ImageIndex=2;
			   //	ANode->SelectedIndex=2;
				}
				String msgText=userRecord->Name;
				if(userRecord->State==1)
				msgText=msgText+"登录";
				else
					msgText=msgText+"退出";
			   //	TfrmEbsMessageBox * msgBox=new TfrmEbsMessageBox(this,msgText,tvCompany);
			  //	msgBox->Show();
			}


		 }
	   }
	   else if(notificationType=="message"||notificationType=="cmd")
	   {
		 UsrID=Arg->Get("from")->JsonValue->Value();
		 msgtype=(TQQUserType)(Arg->Get("msgtype")->JsonValue->Value().ToInt());
		 RecID=Arg->Get("to")->JsonValue->Value();
		 if(msgtype==qutUser)  //找登录用户
		   ANode=LocateCompanyTVNode(msgtype,UsrID);
		 else
		   ANode=LocateCompanyTVNode(msgtype,RecID);
		 if(ANode)
		 {
		   TQQUserRecord *userRecord=(TQQUserRecord*)( ANode->TagObject);
		   TfrmQQMessage* qqMsgForm=NULL;
		   if(userRecord->iMessageFormID==0)
			qqMsgForm=new TfrmQQMessage(this,FClientBroker,userRecord);
		   else
			qqMsgForm=(TfrmQQMessage*)(userRecord->iMessageFormID);
		   if(qqMsgForm)
		   {
			  qqMsgForm->LastRecMessage=Arg;
			  qqMsgForm->Show();
		   }
		 }
	   }
   }
}
TTreeViewItem* __fastcall TfrmQQMain::LocateCompanyTVNode(TQQUserType AUserType,String AID )
{
  TTreeViewItem* Fnode=NULL;
  TTreeViewItem* ANode;
  for(int i=0;i<tvCompany->GlobalCount;i++)
  {
	  ANode=tvCompany->ItemByGlobalIndex(i);
	  TQQUserRecord *userRecord=(TQQUserRecord*)( ANode->TagObject);
	  if(userRecord->UserType==AUserType && userRecord->ID==AID)
	  {
		Fnode= ANode;
		break;
	  }
  }
  return Fnode;
}
void __fastcall TfrmQQMain::UpdateLoginUserNode()
{
  TJSONObject* userRecord;
  TTreeViewItem* ANode;
  String IDValue,AccbookID;
  TJSONArray* UserList=FClientBroker->GetUserList();
  if(UserList==NULL) return;
  for(int i=0;i<UserList->Size();i++)
  {
	userRecord=(TJSONObject*)UserList->Get(i);
	if(userRecord->Size()>1)
	{
	 AccbookID=userRecord->Get("accbookid")->JsonValue->Value();
	 if(FClientBroker->AccBookID!=AccbookID) continue;
	 IDValue=userRecord->Get("userid")->JsonValue->Value();
	 ANode=LocateCompanyTVNode(qutUser,IDValue);
	 if(ANode)
	 {
	   TQQUserRecord *userRecord=(TQQUserRecord*)( ANode->TagObject);
	   userRecord->State=1;
//	   ANode->ImageIndex=3;
 //	   ANode->SelectedIndex=3;
	 }
	}
  }
}

void __fastcall TfrmQQMain::tvCompanyDblClick(TObject *Sender)
{
 TTreeViewItem* ANode = tvCompany->Selected;
 if(ANode)
 {
	TQQUserRecord *userRecord=(TQQUserRecord*)( ANode->TagObject);
	if(AnsiCompareText(userRecord->ID,FClientBroker->UserEmpID)==0)return;
	TfrmQQMessage* qqMsgForm=NULL;
	if(userRecord->iMessageFormID==0)
	   qqMsgForm=new TfrmQQMessage(this,FClientBroker,userRecord);
	else
	  qqMsgForm=(TfrmQQMessage*)(userRecord->iMessageFormID);
	qqMsgForm->Show();
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmQQMain::FormDestroy(TObject *Sender)
{
  FClientBroker->HookCallBack=NULL;
//  tvCompanyDeletion();
  tvCompany->Clear();
}
//---------------------------------------------------------------------------


