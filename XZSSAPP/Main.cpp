//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Main.h"
#include "Config.h"
#include "Login.h"
#include "loginShowMethod.h"
#include <System.Ioutils.hpp>
#include "DocCheck.h"
#include "ShowBizForm.h"
#include "FSTMessageDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	FClientBroker = new TClientBroker(this);
	FAgentAddress = "http://192.168.1.15:9000";
	ChangeControlState();

	#if  defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    	AppPath= System::Ioutils::TPath::GetDocumentsPath();
	#else
		AppPath = ExtractFilePath(ParamStr(0));
	#endif
		settingfile=System::Ioutils::TPath::Combine(AppPath, "ClientConfig.xml");
	FWaitThread=NULL;
	InitAllMainChildForms();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btLoginClick(TObject *Sender)
{
	if(!FClientBroker->Connected)
	{
		 LoadConnectSetting(); //读链接参数
		 ClientBroker->SetBaseUrl(FAgentAddress);
		 TLoginForm * pLogin=new TLoginForm(this);
		 TLoginMethodReference  *Lm=new TLoginMethodReference;
		 Lm->dlg=pLogin;
		 Lm->OwerForm=this;
		 pLogin->StyleBook = this->StyleBook;
		 pLogin->ShowModal(Lm);
	}
	else
	{
		TMessageDialogEventProc msgDialogCloseProc=&LogOff;
	   	FSTMessageDlg(_D("您确认要注销吗？") ,TMsgDlgType::mtConfirmation,mbYesNo,0,msgDialogCloseProc);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btSetupClick(TObject *Sender)
{
	TConfigForm * cf=new TConfigForm(this);
	cf->StyleBook = this->StyleBook;
	cf->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadConnectSetting()
{
	if (!FileExists(settingfile))
		throw System::Sysutils::Exception(L"配置文件" + settingfile + L"找不到");
	_di_IXMLDocument xdoc = LoadXMLDocument(settingfile);
	IXMLNodeList *NodeList = xdoc->ChildNodes;
	IXMLNode *selectNode = NULL;
	for (int i = 0; i < NodeList->Count; i++) {
		IXMLNode *curNode = NodeList->Nodes[i];
		if (curNode->LocalName == String("DefaultSettings") &&
			(curNode->GetAttribute("Version") == String("2.0.0.2"))) {
			selectNode = curNode;
			break;
		}
	}
	if (selectNode != NULL) {
		IXMLNodeList *sNodeList = selectNode->ChildNodes;
		for (int j = 0; j < sNodeList->Count; j++) {
			IXMLNode *sNode = sNodeList->Nodes[j];
			if (sNode->GetAttribute("Name") == String("AgentAddress"))
				FAgentAddress = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("AgentPort"))
				FAgentPort = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("Protocol"))
				FCommunicationProtocol = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("LogInURL"))
				FLogInURL = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("LogOutURL"))
				FLogOutURL = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("LogUserDataURL"))
				FLogUserDataURL = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("BaseBusiRate"))
				FBaseBusiRate = sNode->GetAttribute("value");
			else if (sNode->GetAttribute("Name") == String("BaseAccuRate"))
				FBaseAccuRate = sNode->GetAttribute("value");
		}
	}
	xdoc->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ChangeControlState()
{
	btSetup->Enabled =!FClientBroker->Connected;
	gplayoutMain->Visible=FClientBroker->Connected;
	if(FClientBroker->Connected)
	{
	  UserLabel->Text=FClientBroker->UserName;
	  UserLabel->FontColor=TAlphaColor(claBlue);
	  btLogin->Text=L"注销";
	}
	else
	{
	  UserLabel->Text=L"请登录";
	  btLogin->Text=L"登录";
	  UserLabel->FontColor=TAlphaColor(claBlack);
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit()
{
  	if(FClientBroker->Connected)
	{
        TCloseDialogHandler *closeHandeler=new TCloseDialogHandler;
		closeHandeler->OwerForm=this;
		MessageDlg(_D("您是否确认要退出系统？") ,TMsgDlgType::mtConfirmation,mbYesNo,0,closeHandeler);
	}
	else
	 Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::icMenuClick(TObject *Sender)
{
//	if(!FWaitThread)
//		FWaitThread = new TWaitThread(MainPanel);
//	else
//		FWaitThread->Execute();
	TImage * p = static_cast<TImage *>(Sender);
	ShowClientForm(p->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowClientForm(int modulecode)
{
   String szRight;
   TForm* form=	ShowBizForm(this,modulecode,FClientBroker,"");
   if(form)
   {
	 form->StyleBook = this->StyleBook;
	// form->OnShow = AfterShow;
	 form->Show();
   }
   else
   {
	 ShowMessage(L"未实现菜单号:"+IntToStr(modulecode)+L"请在文件ShowBizForm中定义");
	 if(FWaitThread)
	 	FWaitThread->Hide();
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LogIn()
{
	TRESTRequestParameterList *Params = new TRESTRequestParameterList(this);
	Params->AddItem("UserName",ClientBroker->LogonCode);
	Params->AddItem("Password",ClientBroker->Password);
	MainFormDataSet = ClientBroker->Execute(FLogInURL,rmPOST,Params);
	if(MainFormDataSet->RecordCount > 0)
	{
		if(MainFormDataSet->FieldByName("success")->AsString.Trim().LowerCase() == "true" )
		{
			ClientBroker->Connected = true;
			Params->Clear();
			MainFormDataSet = ClientBroker->Execute(FLogUserDataURL,rmPOST,Params);
			if(MainFormDataSet->RecordCount > 0)
			{
				ClientBroker->UserName = MainFormDataSet->FieldByName("UserName")->AsString;
				ClientBroker->UserID = MainFormDataSet->FieldByName("UserID")->AsInteger;
				ClientBroker->DepID = MainFormDataSet->FieldByName("DepID")->AsInteger;
				ClientBroker->DepName = MainFormDataSet->FieldByName("DepName")->AsString;
				ClientBroker->RoleID = MainFormDataSet->FieldByName("RoleID")->AsInteger;
				ClientBroker->RoleName = MainFormDataSet->FieldByName("RoleName")->AsString;
				ClientBroker->LoginCode = MainFormDataSet->FieldByName("LoginCode")->AsString;
				ClientBroker->BaseBusiRate = FBaseBusiRate;
                ClientBroker->BaseAccuRate = FBaseAccuRate;

			}
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LogOff(System::Uitypes::TModalResult AResult)
{
    if(AResult==mrYes)
	{
		DeleteAllMainChildForms();
		MainFormDataSet = ClientBroker->Execute(FLogOutURL,rmPOST,new TRESTRequestParameterList(this));
		ClientBroker->Connected = false;
		ChangeControlState();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkHardwareBack)
	{
		Key = 0;
		Exit();
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AfterShow(TObject *Sender)
{
	if(FWaitThread)
	 	FWaitThread->Hide();
}
//---------------------------------------------------------------------------

