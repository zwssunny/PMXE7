//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "ServerContainerModule.h"
#include "ServerCtl.h"
#include "AppSetup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMainForm *frmMainForm;
//---------------------------------------------------------------------------
__fastcall TfrmMainForm::TfrmMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::Button1Click(TObject *Sender)
{
  ServerControlModule->StartServer();
  Button1->Enabled=!ServerControlModule->DSServer1->Started;
  Button5->Enabled=ServerControlModule->DSServer1->Started;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainForm::Button4Click(TObject *Sender)
{
 TfrmAppSetup *p=new TfrmAppSetup(this);
 p->ShowModal();
 delete p;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainForm::Button5Click(TObject *Sender)
{
  ServerControlModule->StopServer();
  Button1->Enabled=!ServerControlModule->DSServer1->Started;
  Button5->Enabled=ServerControlModule->DSServer1->Started;
}
//---------------------------------------------------------------------------

