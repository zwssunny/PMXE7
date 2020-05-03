//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TLoginForm *LoginForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
String __fastcall TLoginForm::get_LogonCode()
{
	return edUserLoginCode->Text;
}

String __fastcall TLoginForm::get_Password()
{
	return edPassword->Text;
}

void __fastcall TLoginForm::btOkClick(TObject *Sender)
{
  if(edUserLoginCode->Text.Trim()=="")
  {
	edUserLoginCode->Text="";
	ShowMessage(L"请输入登录用户名.");
	edUserLoginCode->SetFocus();
	return;
  }
  ModalResult=System::Uitypes::TModalResult(mrOk);
}
//---------------------------------------------------------------------------


