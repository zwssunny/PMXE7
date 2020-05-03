//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop


#include <System.IniFiles.hpp>
#include <IPPeerClient.hpp>
#include <Data.DbxHTTPLayer.hpp>
#include <System.Ioutils.hpp>
#include "DataSnapClientDataSet.h"
#include "APIbase.h"
#include "ZClientQuery.h"
#include "ZClientDataset.h"
#include "loginShowMethod.h"
#include "Main.h"
#include "Config.h"
#include "Login.h"
#include "BaseGlobeVars.h"
#include "MiMessage.h"
#include <System.JSON.hpp>
#include "ShowBizForm.h"
#include "FSTMessageDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMainForm *MainForm;
const String szGlobalClassName = L"GZFSTCLASS";
const String szCompanyURL = L"www.xzepm.com";
//const String szKeyUserFmt = L"%s\\Users\\%s";
const String szModuleCaption = L"modulecaption";
const String szModuleCode = L"modulecode";
const String szModuleRight = L"moduleright";
const String szFormPtr = L"formid";
const String days[7] = {L"日", L"一", L"二", L"三", L"四", L"五", L"六" };
  //	lbWeek->Text= FormatDateTime("YYYY-MM-DD",Now())+_D(" 星期")+days[DayOfWeek(Now())-1];
//---------------------------------------------------------------------------
TFmxObject*__fastcall FindItemParent(TFmxObject* Obj, TClass ParentClass)
{
   //  TFmxObject* Result=NULL;
  if (Obj&&(Obj->Parent))
  {
	if (Obj->Parent->ClassType() == ParentClass)
	  return Obj->Parent;
	else
	{
	  return FindItemParent(Obj->Parent, ParentClass);
	}
  }
  return NULL;
}
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	FAgentAddress="192.168.1.23";
	FAgentPort=8080;
	FCommunicationProtocol="HTTP";
	MsgQuery=NULL;
	FClientBroker = new TClientBroker(this);
	tcMainControl->ActiveTab=tabMain;
	ChangeControlState();
	InitAllChildForms();

#if  defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    AppPath= System::Ioutils::TPath::GetDocumentsPath();
#else
	AppPath = ExtractFilePath(ParamStr(0));
#endif
	settingfile=System::Ioutils::TPath::Combine(AppPath, "ClientConfig.xml");
}
__fastcall TMainForm::~TMainForm()
{
   delete FClientBroker;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btSetupClick(TObject *Sender)
{
	 TConfigForm * cf=new TConfigForm(this);
	 cf->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btLoginClick(TObject *Sender)
{

	if(!FClientBroker->Connected)
	{
	     LoadConnectSetting(); //读链接参数
		 FClientBroker->AgentAddress = FAgentAddress;  //这些都需要读参数文件
		 FClientBroker->AgentPort = FAgentPort;
		 FClientBroker->CommunicationProtocol=FCommunicationProtocol;
		 TLoginForm * pLogin=new TLoginForm(this);
		 TLoginMethodReference  *Lm=new TLoginMethodReference;
		 Lm->dlg=pLogin;
		 Lm->OwerForm=this;
		 pLogin->ShowModal(Lm);
	}
	else
	{
	   TMessageDialogEventProc msgDialogCloseProc=&LogOff;
	   FSTMessageDlg(_D("您确认要注销吗？") ,TMsgDlgType::mtConfirmation,mbYesNo,0,msgDialogCloseProc);
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LogOff(System::Uitypes::TModalResult AResult)
{
  if(AResult==mrYes)
  {
		DeleteAllMainChildForms();
		FClientBroker->HookCallBack=NULL;
	//   tvMenu->Clear();
	   tvCompanyDeletion();
	   DeleteGroupItems();
	   if(FClientBroker->Connected)
		{
			FClientBroker->LogOut();
		}
	   tvCompany->Clear();
	   GroupListBox->Clear();
	   ChangeControlState();
	}
}
void __fastcall TMainForm::InitAllChildForms()
{
    InitAllMainChildForms();
}
void __fastcall TMainForm::LoadConnectSetting() {

	if (!FileExists(settingfile))
		throw Exception(L"配置文件" + settingfile + L"找不到");
  //	_di_IXMLDocument XMLDocument1 = LoadXMLDocument(settingfile);
	XMLDocument1->LoadFromFile(settingfile);
	IXMLNodeList *NodeList = XMLDocument1->ChildNodes;
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
		}
	}
	XMLDocument1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ChangeControlState()
{
//	btLogin->Enabled =!FClientBroker->Connected;
	btSetup->Enabled =!FClientBroker->Connected;
	//btExit->Enabled =FClientBroker->Connected;
	gplayoutMain->Visible=FClientBroker->Connected;
	tabMI->Enabled=FClientBroker->Connected;
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
	  tcMainControl->ActiveTab=tabMain;
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadStudioPane()
{
 // FillModuleData();

  FillCompanyTv();
  FillGroupView();
  gGlobeVarsStr=FClientBroker->GlobeVarStr;
  FClientBroker->HookCallBack=&MessageCallBackHook;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FillModuleData()
{
/*
	TDataSnapClientDataSet* cdDataSet = new TDataSnapClientDataSet(NULL);
   //	gGlobeVarsStr=FClientBroker->GlobeVarStr;
	FClientBroker->GetModuleData(cdDataSet);
	if (cdDataSet->RecordCount == 0) {
		delete cdDataSet;
		return;
	}

	// 最终下面这条语句得去掉
	// 因为从数据集取过来的模块列表应该是按显示顺序排好了序的
	// 目前保留，是因为数据集没有正确的排序
	try{
	 tvMenu->BeginUpdate();
	cdDataSet->First();
	tvMenu->Clear();
	TTreeViewItem * pParent1 = NULL;
	TTreeViewItem * pParent2 = NULL;

	// 目前的实现基于以下事实
	// 顶层模块代码为3位编码
	// 第二层代码为5位编码
	// 第三层代码为7位编码
	bool CanFilter = true;
	String sRight = "";
	bool bHaveAddOne, bHaveAddTwo;
	int iItemID;
	while (!cdDataSet->Eof) {
		String sTitle = cdDataSet->FieldValues[szModuleCaption];
		String sCode = cdDataSet->FieldValues[szModuleCode];
		int level = cdDataSet->FieldValues["modulelevel"];
		if (CanFilter && level == 3) {
			sRight = cdDataSet->FieldValues[szModuleRight];
			if (sRight == "") {
				cdDataSet->Next();
				continue;
			}
		}
		if (sCode.Length() == 3) {
			TTreeViewItem * pItem = new TTreeViewItem (this);
			pItem->Parent=tvMenu;
			pItem->Text = sTitle;
			pItem->TagString = sCode;
 			pItem->OnApplyStyleLookup= DoApplyStyleLookup;
 			pItem->StyleLookup = "CustomChildItem";
			pParent1 = pItem;
			bHaveAddOne = false;
		}
		else if (sCode.Length() == 5) // 如果没有子节点, 则删除该节点
		{
			if (CanFilter && pParent2 != NULL) {
				if (pParent2->ChildrenCount == 0) {
					delete pParent2;
					pParent2 = NULL;
				}
			}
			TTreeViewItem * pItem = new TTreeViewItem (this);
			pItem->Text = sTitle;
			pItem->TagString = sCode;
			pParent2 = pItem;
			pItem->OnApplyStyleLookup= DoApplyStyleLookup;
			pItem->StyleLookup = "CustomChildItem";
			pItem->Parent=pParent1;
			bHaveAddTwo = false;
		}
		else if (sCode.Length() == 7) {
			// if(sCode.ToInt()==iAttentionCode)
			// bHasAttention=true;
			TTreeViewItem * pItem = new TTreeViewItem (this);
			pItem->Text = sTitle;
			pItem->TagString = sCode;
			pItem->OnApplyStyleLookup= DoApplyStyleLookup;
			pItem->StyleLookup = "CustomChildItem";
			pItem->OnClick = MenuItemClick;
			if (bHaveAddTwo) {
				pParent2->AddObject(pItem);
				pItem->Parent=pParent2;
			}
			else {
				if (pParent1 != NULL && pParent2 != NULL) {
					if (!bHaveAddOne) {
						bHaveAddOne = true;
					}
					if (!bHaveAddTwo) {
						pParent1->AddObject(pParent2);
						bHaveAddTwo = true;
					}
					pParent2->AddObject(pItem);
				}
			}
		}
		cdDataSet->Next();
	}
	//tvMenu->ExpandAll();
	}
	__finally
	{
	delete cdDataSet;
	tvMenu->EndUpdate();
	}
	*/
}
void __fastcall TMainForm::DoApplyStyleLookup(TObject* Sender)
{
/* TTreeViewItem *Item=static_cast<TTreeViewItem*>(Sender);
 if(Item!=NULL)
 {
	 if(Item->Count>0)
	   Item->StylesData["image"]=TValue::_op_Implicit(FoldImage->Bitmap);
	  else
	   Item->StylesData["image"]=TValue::_op_Implicit(NodeImage->Bitmap);
 }  */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DoCompanyApplyStyleLookup(TObject* Sender)
{
	TTreeViewItem *Item=static_cast<TTreeViewItem*>(Sender);
 if(Item!=NULL)
 {
	 TQQUserType ItemType=(TQQUserType)(Item->TagFloat);
	 switch(ItemType)
	 {
	 case qutCompany:
	   Item->StylesData["image"]=TValue::_op_Implicit(CompanyImage->Bitmap);
	   break;
	 case qutDepartment:
	   Item->StylesData["image"]=TValue::_op_Implicit(DepartImage->Bitmap);
	   break;
	 default:
		if(Item->IsChecked)
		{
		 Item->StylesData["image"]=TValue::_op_Implicit(OnlineImage->Bitmap);
		 Item->StylesData["online"]=TValue::From<UnicodeString>(L"在线");
		}
		else
		{
		 Item->StylesData["image"]=TValue::_op_Implicit(UserImage->Bitmap);
		 Item->StylesData["online"]=TValue::From<UnicodeString>(L"离线");
		}
	 }
   Item->StylesData["text"]=TValue::From<UnicodeString>(Item->Text);
   Item->StylesData["info.OnClick"] = TValue::From<TNotifyEvent>(DoCompanyInfoClick);
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DoListItemApplyStyleLookup(TObject* Sender)
{
  TListBoxItem *Item=static_cast<TListBoxItem*>(Sender);
 if(Item!=NULL)
 {
   Item->StylesData["image"]=TValue::_op_Implicit(DepartImage->Bitmap);
   Item->StylesData["text"]=TValue::From<UnicodeString>(Item->Text);
   Item->StylesData["info.OnClick"] = TValue::From<TNotifyEvent>(DoGroupInfoClick);
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DoCompanyInfoClick(TObject* Sender)
{

 TTreeViewItem *ANode=dynamic_cast<TTreeViewItem*>(FindItemParent(dynamic_cast<TFmxObject*>(Sender),__classid(TTreeViewItem)));
 if(ANode!=NULL)
 {
	if(AnsiCompareText(ANode->TagString,FClientBroker->UserEmpID)==0)return;
	TfrmMessageForm* qqMsgForm=NULL;
	if(ANode->TagObject==NULL)
	{
	   qqMsgForm=new TfrmMessageForm(this,FClientBroker,ANode);
	}
	else
	  qqMsgForm=(TfrmMessageForm*)(ANode->TagObject);
	qqMsgForm->Show();
	qqMsgForm->BringToFront();
 }
}
void __fastcall TMainForm::DoGroupInfoClick(TObject* Sender)
{
 TListBoxItem *ANode=dynamic_cast<TListBoxItem*>(FindItemParent(dynamic_cast<TFmxObject*>(Sender),__classid(TListBoxItem)));
  if(ANode!=NULL)
 {
	TfrmMessageForm* qqMsgForm=NULL;
	if(ANode->TagObject==NULL)
	{
	   qqMsgForm=new TfrmMessageForm(this,FClientBroker,(TTextControl*)ANode);
	}
	else
	  qqMsgForm=(TfrmMessageForm*)(ANode->TagObject);
	qqMsgForm->Show();
	qqMsgForm->BringToFront();
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowClientForm(int modulecode)
{
   String szRight;
   bool bright= FClientBroker->GetModuleRight(modulecode,szRight);
   if(bright && (!szRight.IsEmpty()))
   {
   TForm* form=	ShowBizForm(this,modulecode,"");
   if(form)
	 form->Show();
   else
	 ShowMessage(L"未实现菜单号:"+IntToStr(modulecode)+L"请在文件ShowBizForm中定义");
   }
   else
     ShowMessage(L"您没有授权操作该功能,访问拒绝!");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MenuItemClick(TObject* Sender)
{
// 	assert(Sender->InheritsFrom(__classid(TTreeViewItem )));
	TTreeViewItem * p = static_cast<TTreeViewItem *>(Sender);
	ShowClientForm(p->TagString.ToInt());
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateMsgDataSet()
{
	if (FClientBroker && FClientBroker->Connected) {
		if (MsgQuery)
			delete MsgQuery;

		MsgQuery = new TZClientQuery(this,FClientBroker);
		// MsgDataSet->Open();
		// 把用户列表查询出来，然后保存到ClientComm->UserDataSet中；
		MsgQuery->SQL->Text =
			" select UserLogonCode as LoginCode,EmpNum as UserCode,EmpName as UserName,EmpPKID as UserID from tbEmployeeData " " left join tbUser on Upper(UserIDCode)=Upper(EmpNum) order by EmpNum";

		MsgQuery->Open();
	   //	int rCount=MsgQuery->RecordCount;   //测试
		FClientBroker->InitUserDataSet(MsgQuery); // 在系统中会保存该用户列表
		MsgQuery->Close();
//		if (bHavePMQQ && MsgQuery) {
//			if (fmMessage)
//				delete fmMessage;
//			fmMessage = new TfmMessage(this, MsgQuery, ClientBroker->UserCode,
//				ClientBroker);
//		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btExitClick(TObject *Sender)
{

	if(FClientBroker->Connected)
	{
		TCloseDialogHandler *closeHandeler=new TCloseDialogHandler;
		closeHandeler->OwerForm=this;
		MessageDlg(_D("您是否确认要退出系统？") ,TMsgDlgType::mtConfirmation,mbYesNo,0,closeHandeler);
//		{
//			   LogOff();
//			   Close();
//		}
	}
	else
	 Close();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FillCompanyTv()
{
  TTreeViewItem  *ParentTrNode[11];  //最多10级
   String SortCode="";
   /*
   UserType=Level-1;
   Name=Text
   ID=TagString
   State=TagFloat
   MessageForm=TagObject
   */
   int ilen=0;
   TZClientQuery * CompanyQuery=new TZClientQuery(this,FClientBroker);
  try
  {

	tvCompany->BeginUpdate();
	tvCompanyDeletion();
	tvCompany->Clear();
	ParentTrNode[0]= new TTreeViewItem(tvCompany);
	ParentTrNode[0]->Parent=tvCompany;
	ParentTrNode[0]->Text=L"所有";   //Name
	ParentTrNode[0]->TagString="0";       //ID
	ParentTrNode[0]->TagFloat=0;       //state
	CompanyItem= ParentTrNode[0];
	ParentTrNode[0]->OnApplyStyleLookup=DoCompanyApplyStyleLookup;
	ParentTrNode[0]->StyleLookup = "customdepartItem";
	CompanyQuery->SQL->Text = " select corpognpkid as id,corpogndeptname as name,corpognfkid_upper as parent,corpognsortcode as sortcode,corpogndeptnum as code,1 as type from tbcorporationorganize"
											 " union all"
											 " select emppkid as id,empname as name,(select corpognpkid from tbcorporationorganize where corpognpkid=empdeptcodefkid ) as parent,(select corpognsortcode+corpognpkid from tbcorporationorganize where corpognpkid=empdeptcodefkid)as sortcode,empnum as code,2 as type from tbemployeedata"
											 " order by sortcode,code";

	CompanyQuery->Open();
	while(!CompanyQuery->Eof)
	{
	  SortCode=CompanyQuery->FieldByName("sortcode")->AsString;
	  ilen=SortCode.Length()/8;//8个字符一级

	  ParentTrNode[ilen]= new TTreeViewItem(tvCompany);
	  ParentTrNode[ilen]->Parent=ParentTrNode[ilen-1];
	  ParentTrNode[ilen]->Text=CompanyQuery->FieldByName("name")->AsString;     //Name
	  ParentTrNode[ilen]->TagString=CompanyQuery->FieldByName("id")->AsString;  //ID
	  ParentTrNode[ilen]->OnApplyStyleLookup=DoCompanyApplyStyleLookup;
	  if(CompanyQuery->FieldByName("type")->AsInteger==1)
	  {
		 ParentTrNode[ilen]->TagFloat=qutDepartment;    //type
		 ParentTrNode[ilen]->StyleLookup = "customdepartItem";
	  }
	  else
	  {
		 ParentTrNode[ilen]->TagFloat=qutUser;    //type
		 ParentTrNode[ilen]->StyleLookup = "CustomItem" ;
	  }
	  CompanyQuery->Next();
	}
	CompanyItem->Expand();
	UpdateLoginUserNode();   //更新登录用户状态
  }
  __finally
  {
	tvCompany->EndUpdate();
	delete CompanyQuery;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FillGroupView()
{
   TZClientQuery* GroupQuery=new TZClientQuery(this,FClientBroker);
   GroupQuery->Close();
   GroupQuery->SQL->Text=" select GroupID,GroupName from tbMessageGroup,tbGroupMember"
										 " where GroupID=GroupMemberGroupID and GroupMemberID='"+FClientBroker->UserEmpID+"'"
										 " order by GroupName";
   GroupQuery->Open();
   GroupListBox->BeginUpdate();
   DeleteGroupItems();
   GroupListBox->Clear();
   try {
	  while(!GroupQuery->Eof)
	  {
		TListBoxItem* item = new TListBoxItem(NULL);
	   //	GroupListBox->AddObject(item);
		item->Parent= GroupListBox;
		item->Text =GroupQuery->FieldByName("GroupName")->AsString;
		item->StyleLookup="customlistboxitemstyle";
		item->TagString=GroupQuery->FieldByName("GroupID")->AsString;
		item->TagFloat=qutGroup;
	   //	item->ItemData->Bitmap= DepartImage->Bitmap;
	   //	item->ItemData->Accessory =TListBoxItemData::TAccessory::aDetail;
	  //	item->StylesData["text"]=TValue::From<UnicodeString>(item->Text);
	   //	item->StylesData["info"] = TValue::From<TNotifyEvent>(DoGroupInfoClick);
		//item->OnApplyStyleLookup = DoListItemApplyStyleLookup;
		item->StylesData["image"]=TValue::_op_Implicit(DepartImage->Bitmap);
		item->StylesData["text"]=TValue::From<UnicodeString>(item->Index);
		item->StylesData["info.OnClick"] = TValue::From<TNotifyEvent>(DoGroupInfoClick);
		GroupQuery->Next();
	  }
	  GroupQuery->Close();
	}
	__finally
	{
	  GroupListBox->EndUpdate();
	  delete GroupQuery;
	}
}
//---------------------------------------------------------------------------
TListBoxItem* __fastcall TMainForm::LocateGroupNode(String AID)
{
	TListBoxItem* curItem=NULL;
	int gcount=GroupListBox->Count;
	for(int i=0;i<gcount;i++)
	{
	   curItem=GroupListBox->ItemByIndex(i);
	   if(curItem->TagString==AID)
		 break;
	}
	return curItem;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DeleteGroupItems()
{
	int gcount=GroupListBox->Count;
	for(int i=0;i<gcount;i++)
	{
	  TListBoxItem* curItem=GroupListBox->ItemByIndex(i);
	 if(curItem->TagObject)
	 {
		 TForm *msgform=static_cast<TForm*>(curItem->TagObject);
		 if(msgform)
		 {
			  delete msgform;
			  msgform=NULL;
		  }
		  curItem->TagObject=NULL;
	 }
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tvCompanyDeletion()
{
  TTreeViewItem* ANode;
  for(int i=0;i<tvCompany->GlobalCount;i++)
  {
	 ANode=tvCompany->ItemByGlobalIndex(i);
	 if(ANode->TagObject)
	 {
		 TForm *msgform=static_cast<TForm*>(ANode->TagObject);
		 if(msgform)
		 {
			  delete msgform;
			  msgform=NULL;
		  }
		  ANode->TagObject=NULL;
	 }
  }
  CompanyItem=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MessageCallBackHook(TJSONObject* Arg)
{
   if(Arg->Count>2)
   {

	   String notificationType=Arg->GetValue("notificationType")->Value();
	   String UsrID,RecID;
	   TTreeViewItem* ANode=NULL;
	   TListBoxItem *LNode=NULL;
	   TTextControl* textControl=NULL;
	   TQQUserType msgtype;
	   String AccbookID=Arg->GetValue("accbookid")->Value();
	   if(FClientBroker->AccBookID!=AccbookID) return;
	   if(notificationType=="user_login"||notificationType=="user_logout")
	   {
		 UsrID=Arg->GetValue("from")->Value();
		 ANode=LocateCompanyTVNode(CompanyItem,qutUser,UsrID);
		 //做一些更新用户节点信息
		 if(ANode)
		 {
			 String msgText=ANode->Text;
			if(notificationType=="user_login")
			{
				ANode->IsChecked=true;
				msgText=msgText+L"登录";
				ANode->TextSettings->FontColor= TAlphaColor(claBlue);
				//发送通知
				if(NotificationC->Supported())
				{
					TNotification * Notification = NotificationC->CreateNotification();

					Notification->Name = "FSTNotification";
					Notification->AlertBody = msgText;
					Notification->FireDate = Now();

					// Send notification in Notification Center
					NotificationC->ScheduleNotification(Notification);
					// also this method is equivalent

					// Free the notification
					Notification->DisposeOf();
				 }
			}
			else
			{
				ANode->IsChecked=false;
				msgText=msgText+L"退出";
				ANode->TextSettings->FontColor= TAlphaColor(claBlack);
			}
			DoCompanyApplyStyleLookup(ANode);


		}


	 }
	 else if(notificationType=="message"||notificationType=="cmd")
	   {
		 UsrID=Arg->GetValue("from")->Value();
		 msgtype=(TQQUserType)(Arg->GetValue("msgtype")->Value().ToInt());
		 RecID=Arg->GetValue("to")->Value();
		 if(msgtype==qutGroup)  //找群
		 {
		   LNode=LocateGroupNode(RecID);
		   if(LNode)
			textControl=(TTextControl*)LNode;
		 }
		 else  //找组织
		 {
		   if(msgtype==qutUser)
			  ANode=LocateCompanyTVNode(CompanyItem,msgtype,UsrID);
			else
			  ANode=LocateCompanyTVNode(CompanyItem,msgtype,RecID);
		   if(ANode)
			 textControl=(TTextControl*)ANode;
		 }
		 if(textControl)
		 {
		   TfrmMessageForm* qqMsgForm=NULL;
		   if(textControl->TagObject==NULL)
			qqMsgForm=new TfrmMessageForm(this,FClientBroker,textControl);
		   else
			qqMsgForm=(TfrmMessageForm*)(textControl->TagObject);
		   if(qqMsgForm)
		   {
			  qqMsgForm->LastRecMessage=Arg;
			  qqMsgForm->Show();
			  qqMsgForm->BringToFront();
		   }
		 }
	   }
   }
}
//---------------------------------------------------------------------------
TTreeViewItem* __fastcall TMainForm::LocateCompanyTVNode(TTreeViewItem* CurItem ,TQQUserType AUserType,String AID )
{
 if(CurItem->TagFloat==AUserType && CurItem->TagString==AID)
   return CurItem;
 else
 {
	  for(int i=0;i<CurItem->Count;i++)
	  {
		  TTreeViewItem* ANode=CurItem->Items[i];
		  if(ANode->TagFloat==AUserType && ANode->TagString==AID)
		  {
			  return ANode;
		  }
		  else if((ANode->TagFloat!=qutUser)&&(ANode->TagFloat!=AUserType))
		  {
			TTreeViewItem * fNode=LocateCompanyTVNode(ANode,AUserType,AID);
			if(fNode)
			  return fNode;
		  }

	  }
	  return NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UpdateLoginUserNode()
{
  TTreeViewItem* ANode;
  String IDValue;
  TDataSnapClientDataSet* OnLineUserDS=new TDataSnapClientDataSet(this);
  try{
  OnLineUserDS->LoadFromStream(FClientBroker->ListOfLoginUser());
  OnLineUserDS->First();
  while(!OnLineUserDS->Eof)
  {
	 IDValue=OnLineUserDS->FieldByName("userid")->AsString;
	 ANode=LocateCompanyTVNode(CompanyItem,qutUser,IDValue);
	 if(ANode)
	 {
	   ANode->FontColor= TAlphaColor(claBlue);
	   ANode->IsChecked=true;
	   DoCompanyApplyStyleLookup(ANode);
	 }
	 OnLineUserDS->Next();
  }
  OnLineUserDS->Close();
  }
  __finally
  {
	 delete OnLineUserDS;
  }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::GroupLisBoxItemClick(const TCustomListBox *Sender, const TListBoxItem *Item)

{
   if(Item)
 {
	TfrmMessageForm* qqMsgForm=NULL;
	if(Item->TagObject==NULL)
	{
	   qqMsgForm=new TfrmMessageForm(this,FClientBroker,(TTextControl*)Item);
	}
	else
	  qqMsgForm=(TfrmMessageForm*)(Item->TagObject);
	qqMsgForm->Show();
	qqMsgForm->BringToFront();
 }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::icMenuClick(TObject *Sender)
{
	TImage * p = static_cast<TImage *>(Sender);
	ShowClientForm(p->Tag);
}
//---------------------------------------------------------------------------



