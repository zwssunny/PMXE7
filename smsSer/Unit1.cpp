//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "ModeInter.hpp"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
		LoadModeDll();
		FComPort=0;
		FModeType=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GetDllHandle()
{
   AnsiString dllfilename;
   if (DllHandle != NULL) return;
   dllfilename=ExtractFilePath(Forms::Application->ExeName)+"MonDem.dll";
   DllHandle = LoadLibrary(dllfilename.c_str());
   if (DllHandle == NULL)
   {
        Abort();
   }

}

bool __fastcall  TForm1::LoadDllFunc()
{
//return LoadModeDll();
/*    FARPROC FunAddress;
    GetDllHandle();
        try
        {
            FunAddress = GetProcAddress(DllHandle,"fnSetThreadMode");
            fnSetThreadMode = (long (*)(long))FunAddress; //

            FunAddress = GetProcAddress(DllHandle,"fnCloseModem");
            fnCloseModem = (long (*)(long))FunAddress; //释放端口

            FunAddress = GetProcAddress(DllHandle,"fnInitModem");
            fnInitModem = (long (*)(long))FunAddress; //初始化端口

            FunAddress = GetProcAddress(DllHandle,"fnSetModemType");
            fnSetModemType = (long (*)(long ComNo,long modemType))FunAddress;

            FunAddress = GetProcAddress(DllHandle,"fnGetStatus");
            fnGetStatus = (long (*)(long))FunAddress; //取端口状态

            FunAddress = GetProcAddress(DllHandle,"fnGetSndCount");
            fnGetSndCount = (long (*)(long))FunAddress; //取发送缓冲区记录数

            FunAddress = GetProcAddress(DllHandle,"fnGetRecCount");
            fnGetRecCount = (long (*)(long))FunAddress; //取接收缓冲区记录数

            FunAddress = GetProcAddress(DllHandle,"fnGetPortMax");
            fnGetPortMax = (long(*)())FunAddress; //得到最大端口号

            FunAddress = GetProcAddress(DllHandle,"fnSendMsg");
            fnSendMsg = (long(*)(long nPortNo, char * szHeader, char * szMsg))FunAddress; //发送信息

            FunAddress = GetProcAddress(DllHandle,"fnReadMsgEx");
            fnReadMsgEx = (long(*)(long nPortNo,char * szHeader,char * szReadMsg))FunAddress;//接收信息
            return true;
        }
        catch(...)
        {
            return false;
        } */
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   LoadDllFunc();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{

       // fnCloseModem(-1);
       // fnSetThreadMode(0);
      /*  fnSetModemType(FComPort,FModeType);
        fnGetModemType(FComPort);
		fnInitModem(FComPort+1);  */
		fnSetModemType(0,0);
		fnGetModemType(0);
		fnInitModem(0);
        Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
     fnSendMsg(0,Edit1->Text.c_str(),Edit2->Text.c_str());
     Caption=Edit1->Text;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  // fnCloseModem(-1);
  Timer1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  int i=fnGetStatus(FComPort);
  StatusBar1->SimpleText="测试状态:"+IntToStr(i);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  TForm2 *p=new TForm2(this);
  p->ShowModal();
  delete p;	
}
//---------------------------------------------------------------------------

