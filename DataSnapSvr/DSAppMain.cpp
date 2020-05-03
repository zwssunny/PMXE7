//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DSAppMain.h"
#include "FSServerContainer.h"
#include "LoginUserRecord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDSAppMain *frmDSAppMain;
//---------------------------------------------------------------------------
__fastcall TfrmDSAppMain::TfrmDSAppMain(TComponent* Owner)
	: TForm(Owner)
{
 /*	SetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDATE, L"-");
	SetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, L":");
	SetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, L"yyyy-MM-dd");
	SetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, L"HH:mm:ss"); */
	CloseCofirm = false;
	Application->Minimize();
	Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::ChangeButtonState()
{
	// btStart->Enabled= !DMServerContainer->FSDSServer->Started;
	// btStop->Enabled= DMServerContainer->FSDSServer->Started;
	lbDSServerState->Caption= DMServerContainer->FSDSServer->Started? "运行":"停止";
	lbDSServerState->Color= DMServerContainer->FSDSServer->Started? clGreen:clRed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::pmuExitClick(TObject *Sender)
{
	CloseCofirm = true;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::FormCreate(TObject *Sender)
{
  DMServerContainer->MaxOAUserCount=50;
  DMServerContainer->MaxUserCount=50;
  DMServerContainer->StartServer();
  ChangeButtonState();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	DMServerContainer->Shutdown();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::Timer1Timer(TObject *Sender)
{
	lbLastTime->Caption = FormatFloat("00.00", DMServerContainer->RemainTimes) + "分钟";
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::pmuRestoreClick(TObject *Sender)
{
	Application->Restore();
	Show();
	ShowWindow(Application->Handle, SW_RESTORE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if(Application->MessageBox(L"您确定要退出先智服务器吗，所有客户端将不能使用？", L"服务器", MB_OKCANCEL) == IDOK)
		CanClose = true;
	else
		CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::Button1Click(TObject *Sender)
{
  String LURL = L"http://localhost:"+IntToStr(DMServerContainer->FSDSHTTPService->HttpPort)+L"/ChatRoom.html";
  ShellExecute(0, L"Open", LURL.c_str(), NULL, DMServerContainer->FSDSHTTPServiceFileDispatcher->RootDirectory.c_str(), SW_SHOWNOACTIVATE);

}
//---------------------------------------------------------------------------
void __fastcall TfrmDSAppMain::btGenClick(TObject *Sender)
{
  TDSJavaScriptProxyWriter *JSProxy;
  String OutputFile;

	OutputFile = ExpandFileName(DMServerContainer->FSDSHTTPServiceFileDispatcher->RootDirectory);

  JSProxy = new TDSJavaScriptProxyWriter();

  try
  {
	if (!DirectoryExists(OutputFile))
	  ForceDirectories(OutputFile);

	if ( !AnsiEndsStr("\\", OutputFile) &&
	   !AnsiEndsStr("/", OutputFile))
	  OutputFile = OutputFile + Sysutils::PathDelim;

	//put the proxy file in a subdirectory of the root folder
	OutputFile = OutputFile + "proxy" + Sysutils::PathDelim;

	//name the proxy file
	OutputFile = OutputFile + "JSProxy.js";

	ProxyConnection->Connected = true;
	JSProxy->UpdateJSProxyFile(ProxyConnection->DBXConnection, OutputFile);
	ProxyConnection->Close();
  }
  __finally
  {
	JSProxy->Free();
  }
}
//---------------------------------------------------------------------------


