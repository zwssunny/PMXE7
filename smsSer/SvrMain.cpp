#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "SvrMain.h"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <registry.hpp>
#include "Basefunc.h"
#include "DecEnc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"

TXZSmsServerXE *XZSmsServerXE;
//---------------------------------------------------------------------------
__fastcall TXZSmsServerXE::TXZSmsServerXE(TComponent* Owner)
	: TService(Owner)
{
  smsClient=new TSmsClientBroker();
	FInstanceName="";
	DisplayName="Foresight SMS Server";
}
//---------------------------------------------------------------------------
TServiceController __fastcall TXZSmsServerXE::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}
//---------------------------------------------------------------------------
void __stdcall ServiceController(unsigned CtrlCode)
{
	XZSmsServerXE->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TXZSmsServerXE::ServiceStart(TService *Sender,
	  bool &Started)
{
	Timer1->Enabled=true;
    Started=true;
}
//---------------------------------------------------------------------------

void __fastcall TXZSmsServerXE::ServiceStop(TService *Sender, bool &Stopped)
{
 	Timer1->Enabled=false;
   smsClient->ServiceStop();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TXZSmsServerXE::ServiceDestroy(TObject *Sender)
{
         delete smsClient;
		// OleUninitialize();
}
//---------------------------------------------------------------------------

void __fastcall TXZSmsServerXE::ServiceAfterInstall(TService *Sender)
{
  if(FInstanceName!="")
 		  ChangeServiceConfiguration();
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
		reg->WriteString("Description","先智短信服务器,实例为"+Name);
		reg->CloseKey();
	}
	__finally
	{
		reg->Free();
	}
}
//---------------------------------------------------------------------------
void __fastcall TXZSmsServerXE::ChangeServiceConfiguration()
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
void __fastcall TXZSmsServerXE::SetInstanceName(String Value)
{
   if (FInstanceName != Value)
  {
	FInstanceName = Value;
	if (FInstanceName != "")
	{
	  Name = FInstanceName;
	  DisplayName = "Foresight SMS Service("+FInstanceName+")";
	}
  }
}
//---------------------------------------------------------------------------

void __fastcall TXZSmsServerXE::Timer1Timer(TObject *Sender)
{
	if(!smsClient->Connected)
	{
		if(smsClient->InitClientComm())
		{
  		  smsClient->RegCallBack();
		  smsClient->ServiceStart();
		}
	}
}
//---------------------------------------------------------------------------
String __fastcall TXZSmsServerXE::GetInstanceName()
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

void __fastcall TXZSmsServerXE::ServiceBeforeUninstall(TService *Sender)
{
  String inst=GetInstanceName();
  if(inst>"")
	 InstanceName=inst;
}
//---------------------------------------------------------------------------

void __fastcall TXZSmsServerXE::ServiceCreate(TObject *Sender)
{
  String inst=GetInstanceName();
  if(inst>"")
	 InstanceName=inst;
}
//---------------------------------------------------------------------------

void __fastcall TXZSmsServerXE::ServiceBeforeInstall(TService *Sender)
{
  String inst=GetInstanceName();
  if(inst>"")
	 InstanceName=inst;
}
//---------------------------------------------------------------------------

