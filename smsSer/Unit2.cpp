//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "Basefunc.h"
#include "DecEnc.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
           FSMSType=0;
           FBeginTime=7 ;//开始时间
           FEndTime=22; //结束时间
           FWaitLong=1;//消息处理间隔时间 秒为单位
           FRepeatCount=3;//发送错误时，需要重复次数
		   OleInitialize(NULL);

}
//---------------------------------------------------------------------------
void __fastcall TForm2::LoadSetting()
{
  String settingfile=ExtractFilePath(Forms::Application->ExeName)+"default.xml";
  try
  {
   if(!FileExists(settingfile))
	 throw Exception("找不到系统配置文件"+settingfile);
	_di_IXMLDocument xdoc=NewXMLDocument();
    xdoc->LoadFromFile(settingfile);
    xdoc->Active=true;
    IXMLNodeList *NodeList=xdoc->ChildNodes;
    IXMLNode *selectNode=NULL;
    for(int i=0;i<NodeList->Count;i++)
	{
	   IXMLNode *curNode=NodeList->Nodes[i];
	   if(curNode->LocalName==WideString("DefaultSettings")&&(curNode->GetAttribute("Version")==String("2.0.0.2")))
         {
            selectNode=curNode;
            break;
         }
	}
    if(selectNode!=NULL)
    {
        IXMLNodeList *sNodeList=selectNode->ChildNodes;
        for(int j=0;j<sNodeList->Count;j++)
        {
            IXMLNode *sNode=sNodeList->Nodes[j];
		if(sNode->GetAttribute("Name")==String("DbConStr"))
			FDbConStr=DecryptAES(sNode->GetAttribute("value"));
			else if(sNode->GetAttribute("Name")==String("SMSType"))
               FSMSType=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("BeginTime"))
			   FBeginTime=FormatDateTime("hh:mm:ss",StrToDateTime(sNode->GetAttribute("value")));
			else if(sNode->GetAttribute("Name")==String("EndTime"))
			   FEndTime=FormatDateTime("hh:mm:ss",StrToDateTime(sNode->GetAttribute("value")));
			else if(sNode->GetAttribute("Name")==String("WaitLong"))
			   FWaitLong=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("RepeatCount"))
			   FRepeatCount=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("MonType"))
			   FMonType=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("PortNum"))
			   FPortNum=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("GateCordId"))
			   FCordId=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("GateUserName"))
			   FUserName=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("GatePassWord"))
			   FPassword=sNode->GetAttribute("value");

		}
    }
	xdoc->Active=false;
 }
 catch(Exception &e)
 {
   WritErrorLog("读取参数错误,"+e.Message);
 }
}
void  __fastcall TForm2::WritErrorLog(String ErrorLong)
{
   String Errorfile=ExtractFilePath(Forms::Application->ExeName)+"ErrorLong.txt";
   ErrorLong = DateTimeToStr(Now())+"  "+ErrorLong+"\r\n";
   int iFileHandle;
   try
   {
       if (FileExists(Errorfile))
           iFileHandle = FileOpen(Errorfile,fmOpenWrite);
       else
           iFileHandle = FileCreate(Errorfile);
       FileSeek(iFileHandle,0,2);
       FileWrite(iFileHandle,ErrorLong.c_str(),ErrorLong.Length());
   }
   __finally
   {
       FileClose(iFileHandle);
   }
}
void __fastcall TForm2::FormDestroy(TObject *Sender)
{
  OleUninitialize();  	
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
     try
     {
      try
       {
		 if (FSMSType != 0)
            delete ShortInfo;
       }
       catch(Exception &e)
       {
		WritErrorLog(e.Message);
	   }
      }
      __finally
      {
	   WritErrorLog("短信服务器已停止");
	  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
     LoadSetting();
	if (FSMSType == 0)
	 {
	  return;
	 }
	 int Flag = FSMSType - 1;
	 ShortInfo = new TShortInfo(Owner,Flag);
	 ShortInfo->BeginTime=FBeginTime;
	 ShortInfo->EndTime=FEndTime;
     ShortInfo->WaitLong=FWaitLong*1000;
     ShortInfo->RepeatCount=FRepeatCount;
	 ShortInfo->DBConnectString=FDbConStr;
	 ShortInfo->OnWriteErrorLog  = WritErrorLog;
	 ShortInfo->ModeType = FMonType;
	 ShortInfo->ComPort = FPortNum;
	 ShortInfo->CordId = FCordId;
	 ShortInfo->UserName = FUserName;
	 ShortInfo->PassWord = FPassword;
	 ShortInfo->Initializtion();
	 ShortInfo->StarTimer();
	 WritErrorLog("短信服务器已运行");
	 Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


