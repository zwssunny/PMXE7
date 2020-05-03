//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "wfMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmWFmain *frmWFmain;
//---------------------------------------------------------------------------
__fastcall TfrmWFmain::TfrmWFmain(TComponent* Owner)
	: TForm(Owner)
{
	 FClientBroker=new TwfClientBroker(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWFmain::FormClose(TObject *Sender, TCloseAction &Action)
{
 delete FClientBroker;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWFmain::RunWFServer()
{
   FClientBroker->ReadOption();
   if(FClientBroker->InitClientComm())
	  FClientBroker->RegCallBack();
   Button1->Enabled=!FClientBroker->Connected;
}
void __fastcall TfrmWFmain::Button1Click(TObject *Sender)
{
   RunWFServer();
}
//---------------------------------------------------------------------------

