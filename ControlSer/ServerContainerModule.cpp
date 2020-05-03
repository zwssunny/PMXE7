//----------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <stdio.h>
#include <memory>
#include "ServerControlMethods.h"
#include "ServerContainerModule.h"
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <System.Ioutils.hpp>
#include "CheckService.h"
#include "BaseFunc.h"
#include "ServerCtl.h"
#include "LogQueueProc.h"
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TServerControlModule *ServerControlModule;
//---------------------------------------------------------------------------
__fastcall TServerControlModule::TServerControlModule(TComponent* Owner)
	: TDataModule(Owner)
{
	FTCPIP     		= 411;
	FHttpPort       = 4040;
	FHttpsPort		= 4041;
	FPeriod         =5;//秒
	FAdminName="";
	FPassWord="";
	FComputerIP=GetComputerIP(GetMachineName());
	AppPath = ExtractFilePath(Application->ExeName);
		  if (!DirectoryExists(AppPath))
		  ForceDirectories(AppPath);
	settingfile = System::Ioutils::TPath::Combine(AppPath,"scdefault.xml");
	MsgLogFile=System::Ioutils::TPath::Combine(AppPath,"SCLong.txt");
}
//----------------------------------------------------------------------------
void __fastcall TServerControlModule::DSServerClass1GetClass(TDSServerClass *DSServerClass,
          TPersistentClass &PersistentClass)
{
	PersistentClass =  __classid(TServerControlMethods);
}
//----------------------------------------------------------------------------
void __fastcall TServerControlModule::DSAuthenticationManager1UserAuthenticate(TObject *Sender,
          const UnicodeString Protocol, const UnicodeString Context, const UnicodeString User,
          const UnicodeString Password, bool &valid, TStrings *UserRoles)

{
	if((User==FAdminName)&&(Password==FPassWord))
		valid = true;
	else
		valid = false;
}
//---------------------------------------------------------------------------
void __fastcall TServerControlModule::ReadOptions()
{
	try
	{
		if(!FileExists(settingfile))
		{
			NotifyWriteLog("找不到系统配置文件" + settingfile);
			return;
		}
		_di_IXMLDocument xdoc = NewXMLDocument();
		xdoc->LoadFromFile(settingfile);
		xdoc->Active = true;
		IXMLNodeList *NodeList = xdoc->ChildNodes;
		IXMLNode *selectNode =NULL;//xdoc->ChildNodes->FindNode("DefaultSettings");
		for (int i = 0; i < NodeList->Count; i++)
		{
			IXMLNode *curNode = NodeList->Nodes[i];
			if(curNode->LocalName == WideString("DefaultSettings") && (curNode->GetAttribute("Version") == String("2.0.0.2")))
			{
				selectNode = curNode;
				break;
			}
		}

		if(selectNode != NULL)
		{
			IXMLNodeList *sNodeList = selectNode->ChildNodes;
			for (int j = 0; j < sNodeList->Count; j++)
			{
				IXMLNode *sNode = sNodeList->Nodes[j];
				if(sNode->GetAttribute("Name") == String("TCPIP"))
					FTCPIP = sNode->GetAttribute("value"); //
				else if(sNode->GetAttribute("Name") == String("HTTP"))
					FHttpPort = sNode->GetAttribute("value"); //
				else if(sNode->GetAttribute("Name") == String("HTTPS"))
					FHttpsPort = sNode->GetAttribute("value"); //
				else if(sNode->GetAttribute("Name") == String("Admin"))
					FAdminName = sNode->GetAttribute("value"); // 管理员
				else if(sNode->GetAttribute("Name") == String("PassWord"))
					FPassWord = sNode->GetAttribute("value"); // 口令
				else if(sNode->GetAttribute("Name") == String("Period"))
					FPeriod = sNode->GetAttribute("value"); // 检测周期
			}
		}
	  //清除列表
	  while(ServerList->Count>0)
		  ServerList->Remove(ServerList->Count-1);

	  IXMLNode *ServerListNode =selectNode->ChildNodes->FindNode("ServerList");
	  if(ServerListNode)
	  {
		IXMLNodeList *SerChildList = ServerListNode->ChildNodes;
		for(int s=0;s<SerChildList->Count;s++)
		{
		   IXMLNode *sNode = SerChildList->Nodes[s];
		   TJSONObject *jNode=new TJSONObject();
		   jNode->AddPair("Name",sNode->GetAttribute("Name"));
		   jNode->AddPair("FileName",sNode->GetAttribute("FileName"));
		   jNode->AddPair("Display",sNode->GetAttribute("Display"));
		   ServerList->AddElement(jNode);
		}

      }
		xdoc->Active = false;
	}
	catch (Exception &e)
	{
		NotifyWriteLog("读取参数错误," + e.Message);
	}
}
void __fastcall TServerControlModule::InitServerStatus()
{
  int retval,ServiceStatus;
  String NtSer;
  System::TMonitor::Enter(ServerList);
  try
  {
  for(int i=0;i<ServerList->Count;i++)
  {
	TJSONObject *sNode=(TJSONObject *)(ServerList->Items[i]);
	NtSer=sNode->GetValue("Name")->Value();
	retval=SCQueryServiceStatus(NULL,NtSer.c_str(),ServiceStatus);
	if(retval!=0)
	 ServiceStatus=-1;//
	sNode->AddPair("ServiceStatus",ServiceStatus);
  }
  }
  __finally
  {
	System::TMonitor::Exit(ServerList);
  }
}
//---------------------------------------------------------------------------


void __fastcall TServerControlModule::StartServer()
{

   try{
	ReadOptions();
	InitServerStatus();
	DSTCPServerTransport1->Port=FTCPIP;
	DSHTTPService1->HttpPort=FHttpPort;
	DSServer1->Start();
	if(DSServer1->Started)
	{
		Timer1->Interval=FPeriod*1000;
		Timer1->Enabled=true;
		NotifyWriteLog(L"服务器启动了");
	}
	}
	catch(Exception &e)
	{
	   NotifyWriteLog(L"启动时错误:"+e.Message);
    }
}
void __fastcall TServerControlModule::StopServer()
{
	Timer1->Enabled=false;
	NotifyWriteLog(L"服务器结束");
	DSServer1->Stop();
}
TJSONArray* __fastcall TServerControlModule::CopyServerList()
{
  System::TMonitor::Enter(ServerList);
  TJSONArray *nServerList;
  try
  {
	 nServerList=(TJSONArray *)ServerList->Clone();
  }
  __finally
  {
		System::TMonitor::Exit(ServerList);
  }
  return nServerList;
}
void __fastcall TServerControlModule::Timer1Timer(TObject *Sender)
{
   int scount= ServerList->Count;
   for(int i=0;i<scount;i++)
   {
	   TCheckServiceProc *checkProc=new TCheckServiceProc(DSServer1,ServerList,FComputerIP,i);
   }
}
//---------------------------------------------------------------------------
void __fastcall TServerControlModule::UpdateServerList(String ServerName)
{
  System::TMonitor::Enter(ServerList);
  try
  {
	 for(int i=0;i<ServerList->Count;i++)
	 {
		 TJSONObject *sNode=(TJSONObject *)(ServerList->Items[i]);
		 String NtSer=sNode->GetValue("Name")->Value();
		 if(NtSer.UpperCase()==ServerName.UpperCase())
		 {
		  TCheckServiceProc *checkProc=new TCheckServiceProc(DSServer1,ServerList,FComputerIP,i);
		  break;
		 }
	 }
  }
  __finally
  {
		System::TMonitor::Exit(ServerList);
  }

}
// ---------------------------------------------------------------------------
void  __fastcall TServerControlModule::WritLog(String msgLong,TDateTime dtime)
{
   int iFileHandle;
	try
   {
	   AnsiString  strLong = dtime.FormatString("YYYY-MM-DD HH:MM:SS")+"  "+msgLong+"\r\n";
	   if (FileExists(MsgLogFile))
		   iFileHandle = FileOpen(MsgLogFile,fmOpenWrite);
	   else
		   iFileHandle = FileCreate(MsgLogFile);
	   FileSeek(iFileHandle,0,2);
	  FileWrite(iFileHandle,strLong.c_str(),strLong.Length());
   }
   __finally
   {
	   FileClose(iFileHandle);
   }
}
void __fastcall TServerControlModule::NotifyWriteLog(String Msg)
{
  TWriteUserLog wLog=&WritLog;
  String IpAddress="";
  TDSSession *threadSession = TDSSessionManager::Instance->GetThreadSession();
  if(threadSession)
	 IpAddress=threadSession->GetData("IpAddress");
   TThreadProcedure* methProc(static_cast<TThreadProcedure*>(new TLogQueueProc(wLog,IpAddress,Now(),Msg)));
   TThread::Queue(0, methProc);
}
void __fastcall TServerControlModule::DSServer1Connect(TDSConnectEventObject *DSConnectEventObject)

{
	if((DSConnectEventObject!=NULL)&&(DSConnectEventObject->ChannelInfo!=NULL))
	{
		TDSSession *threadSession = TDSSessionManager::Instance->GetThreadSession();
		threadSession->PutData("IpAddress",DSConnectEventObject->ChannelInfo->ClientInfo.IpAddress);
		threadSession->PutData("ClientPort",DSConnectEventObject->ChannelInfo->ClientInfo.ClientPort);
		threadSession->PutData("Protocol",DSConnectEventObject->ChannelInfo->ClientInfo.Protocol);
		threadSession->PutData("AppName",DSConnectEventObject->ChannelInfo->ClientInfo.AppName);
	  }
}
//---------------------------------------------------------------------------

void __fastcall TServerControlModule::DataModuleCreate(TObject *Sender)
{
	ServerList = new TJSONArray();
}
//---------------------------------------------------------------------------

void __fastcall TServerControlModule::DataModuleDestroy(TObject *Sender)
{
 delete  ServerList;
}
//---------------------------------------------------------------------------

