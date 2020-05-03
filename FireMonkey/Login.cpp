//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmLogin *frmLogin;
//---------------------------------------------------------------------------
__fastcall TfrmLogin::TfrmLogin(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
String __fastcall TfrmLogin::get_LogonCode()
{
   return edUserLoginCode->Text;
}
//---------------------------------------------------------------------------
String __fastcall TfrmLogin::get_Password()
{
   return edPassword->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmLogin::btOkClick(TObject *Sender)
{
  if(edUserLoginCode->Text.Trim()=="")
  {
	edUserLoginCode->Text="";
	ShowMessage("请输入登录用户名.");
	edUserLoginCode->SetFocus();
	return;
  }
   ModalResult=mrOk;
}
//---------------------------------------------------------------------------



