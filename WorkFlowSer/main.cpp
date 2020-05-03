//---------------------------------------------------------------------------
#include "main.h"
#include <registry.hpp>
#include "DecEnc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//多实例注册服务采用 WorkFlowSer -install -instance=InstName;
//这样一个应用程序可以注册多个服务器名称，注意服务器开放端口不要冲突
//一般采用备份到不同目录，修改端口参数，然后才进行服务注册
TXZWorkFlowSerXE *XZWorkFlowSerXE;
//---------------------------------------------------------------------------
__fastcall TXZWorkFlowSerXE::TXZWorkFlowSerXE(TComponent* Owner)
	: TService(Owner)
{
	 FClientBroker=new TwfClientBroker(this);
	 FInstanceName="";
	 DisplayName="Foresight Workflow Server";
}

TServiceController __fastcall TXZWorkFlowSerXE::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}

void __stdcall ServiceController(unsigned CtrlCode)
{
	XZWorkFlowSerXE->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
void __fastcall TXZWorkFlowSerXE::ServiceStart(TService *Sender, bool &Started)
{
    FClientBroker->ReadOption();
	Timer1->Enabled=true;
	Started=true;
}
//---------------------------------------------------------------------------
void __fastcall TXZWorkFlowSerXE::ServiceStop(TService *Sender, bool &Stopped)
{
	Timer1->Enabled=false;
	FClientBroker->UnRegCallBack();
	Stopped=true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TXZWorkFlowSerXE::ServiceDestroy(TObject *Sender)
{
	delete FClientBroker;
   //	OleUninitialize();
}
//---------------------------------------------------------------------------

void __fastcall TXZWorkFlowSerXE::ServiceAfterInstall(TService *Sender)
{
	TRegistry *reg;
	reg = new TRegistry();
	reg->RootKey = HKEY_LOCAL_MACHINE;
	try
	{
		reg->OpenKey("SYSTEM",false);
		reg->OpenKey("CurrentControlSet",false);
		reg->OpenKey("Services",false);
		reg->OpenKey(Name,true);
		reg->WriteString("DisplayName",DisplayName);
		reg->WriteString("Description","先智软件工作流后台服务,实例为"+Name);
		reg->CloseKey();
	}
	__finally
	{
		reg->Free();
	}
}
//---------------------------------------------------------------------------
void __fastcall TXZWorkFlowSerXE::ChangeServiceConfiguration()
{
  SC_HANDLE mngr;
  SC_HANDLE svc;
  String newpath;
  // 打开服务控制器
  mngr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
  if (mngr == 0)
	RaiseLastOSError();
  try
  {
	// 打开服务
	svc = OpenService(mngr, Name.c_str(), SERVICE_CHANGE_CONFIG);
	if (svc == 0)
	  RaiseLastOSError();
	try
	{
	  // 改变它的执行参数
	  newpath = ParamStr(0) + " " + INSTANCE_SWITCH+FInstanceName; // + any other cmd line params you fancy
	  ChangeServiceConfig(svc, SERVICE_NO_CHANGE, //  dwServiceType
							   SERVICE_NO_CHANGE, //  dwStartType
							   SERVICE_NO_CHANGE, //  dwErrorControl
							   newpath.c_str(),    //  <-- 只要改变执行路径和参数
							   NULL,               //  lpLoadOrderGroup
							   NULL,               //  lpdwTagId
							   NULL,               //  lpDependencies
							   NULL,               //  lpServiceStartName
							   NULL,               //  lpPassword
							   DisplayName.c_str());              //  lpDisplayName
	}
	__finally
	{
	  CloseServiceHandle(svc);
	}
  }
  __finally
  {
	CloseServiceHandle(mngr);
  }
}
void __fastcall TXZWorkFlowSerXE::SetInstanceName(String Value)
{
   if (FInstanceName != Value)
  {
	FInstanceName = Value;
	if (FInstanceName != "")
	{
	  Name = FInstanceName;
	  DisplayName = "Foresight Workflow Service("+FInstanceName+")";
	}
  }
}

void __fastcall TXZWorkFlowSerXE::ServiceBeforeInstall(TService *Sender)
{
  String inst=GetInstanceName();
  if(inst>" ")
	 InstanceName=inst;
}
//---------------------------------------------------------------------------

void __fastcall TXZWorkFlowSerXE::ServiceBeforeUninstall(TService *Sender)
{
  String inst=GetInstanceName();
  if(inst>" ")
	 InstanceName=inst;
}
//---------------------------------------------------------------------------

void __fastcall TXZWorkFlowSerXE::ServiceCreate(TObject *Sender)
{
  String inst=GetInstanceName();
  if(inst>" ")
	 InstanceName=inst;
}
//---------------------------------------------------------------------------
String __fastcall TXZWorkFlowSerXE::GetInstanceName()
{
  String result = "";
  int PaCount=System::ParamCount();
  for(int index = 1; index<=PaCount; index++)
  {
	String paramString=ParamStr(index);
	if (SameText(INSTANCE_SWITCH, paramString.SubString(1,INSTANCE_SWITCH.Length())))
	{
	  result =paramString.SubString(INSTANCE_SWITCH.Length() + 1, MaxInt);
	  break;
	}
  }
 return result;
}
void __fastcall TXZWorkFlowSerXE::Timer1Timer(TObject *Sender)
{
  if(!FClientBroker->Connected)
  {
   if(FClientBroker->InitClientComm())
	  FClientBroker->RegCallBack();
  }
}
//---------------------------------------------------------------------------

