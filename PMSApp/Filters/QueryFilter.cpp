//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "QueryFilter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TQueryFilterForm *QueryFilterForm;
//---------------------------------------------------------------------------
__fastcall TQueryFilterForm::TQueryFilterForm(TComponent* Owner,TClientBroker *clBroker,
			TEdit *TagEdit,String ATitle,String ASQL)
	: TForm(Owner)
{
	lbTitle->Text=ATitle;
	FEdit=TagEdit;
	FSQL=ASQL;
	FBroker=clBroker;
	Query=new TZClientQuery(this,FBroker);
}
//---------------------------------------------------------------------------
__fastcall TQueryFilterForm::~TQueryFilterForm()
{
	delete Query;
}
//---------------------------------------------------------------------------
void __fastcall TQueryFilterForm::FillQueryData()
{
  try{
	  lvQueryData->BeginUpdate();
	  lvQueryData->Items->Clear();
	  Query->Close();
	  Query->SQL->Text=FSQL;
	  Query->Open();
	  while(!Query->Eof)
	  {
		 TListViewItem* vItem=lvQueryData->Items->Add();
		 vItem->ButtonText=Query->Fields->Fields[0]->AsString;
		 vItem->Text=Query->Fields->Fields[1]->AsString;
		 //vItem->Detail=;
		 Query->Next();
	  }
  }
  __finally
  {
   lvQueryData->EndUpdate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TQueryFilterForm::btCancelClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TQueryFilterForm::btQueryClick(TObject *Sender)
{
 if(lvQueryData->Selected)
 {
  if(FEdit)
  {
	FEdit->Text=lvQueryData->Selected->Text;
	FEdit->TagString=lvQueryData->Selected->ButtonText;
	if(FEdit->CanFocus)
	   FEdit->SetFocus();
  }
  Close();
  }
  else
   ShowMessage(L"请选中某条记录！");
}
//---------------------------------------------------------------------------

void __fastcall TQueryFilterForm::FormShow(TObject *Sender)
{
  FillQueryData();
}
//---------------------------------------------------------------------------

