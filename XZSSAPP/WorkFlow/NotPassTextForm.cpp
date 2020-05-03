//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "NotPassTextForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmNotPassTextForm *frmNotPassTextForm;
//---------------------------------------------------------------------------
__fastcall TfrmNotPassTextForm::TfrmNotPassTextForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNotPassTextForm::Button1Click(TObject *Sender)
{
	this->Reason = Memo1->Text;
	ModalResult=System::Uitypes::TModalResult(mrOk);
}
//---------------------------------------------------------------------------

void __fastcall TfrmNotPassTextForm::btCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
