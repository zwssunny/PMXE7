//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CustomerFilters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseFilters"
#pragma resource "*.fmx"
TCustomerFiltersForm *CustomerFiltersForm;
//---------------------------------------------------------------------------
__fastcall TCustomerFiltersForm::TCustomerFiltersForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker)
	: TBaseFiltersForm(Owner,AOnFilteredDataSet,ABroker)
{
}
//---------------------------------------------------------------------------
String __fastcall TCustomerFiltersForm::BuildFilters()
{
	String custFilters="";
	  if(cbBoxClientClass->ItemIndex>0)  //分类
	  {
		custFilters="ClientTheFKID_Cls="+QuotedStr(cbBoxClientClass->Selected->TagString);
	  }
	if(cboClientType->ItemIndex>0)  //状态
	{
	 if(custFilters>" ")
		custFilters=custFilters+" and " ;
	  custFilters=custFilters+"ClientType="+IntToStr(cboClientType->ItemIndex-1);
	}
	if(!edCustName->Text.Trim().IsEmpty())
	{
	 if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters="ClientTheName like '%"+edCustName->Text.Trim()+"%'";
	}
	if(!edCustNum->Text.Trim().IsEmpty())
	 {
	  if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"ClientNum like '%"+edCustNum->Text.Trim()+"%'";
	 }
	if(!edMobilePhone->Text.Trim().IsEmpty())
	{
	  if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"ClientMobilePhoneNum like '%"+edMobilePhone->Text.Trim()+"%'";
	}
	if(!edCardNo->Text.Trim().IsEmpty())
	{
	   if(custFilters>" ")
		custFilters=custFilters+" and " ;
	   custFilters=custFilters+"ClientCardNum like '%"+edCardNo->Text.Trim()+"%'";

	}
	if(!edCardID->Text.Trim().IsEmpty())
	{
	   if(custFilters>" ")
		custFilters=custFilters+" and " ;
	   custFilters=custFilters+"ClientPaperName like '%"+edCardID->Text.Trim()+"%'";

	}

	return custFilters;
}
void __fastcall TCustomerFiltersForm::InitControl()
{
  /*	cboClientType->Clear();
	cboClientType->Items->Add(L"所有状态");
	cboClientType->Items->Add(L"登记客户");
	cboClientType->Items->Add(L"业主");
	cboClientType->Items->Add(L"预定客户");
	cboClientType->Items->Add(L"签约客户");
	cboClientType->ItemIndex=0;
	*/
  cbBoxClientClass->Clear();
  TListBoxItem * newBoxItem=new TListBoxItem(cbBoxClientClass);
  newBoxItem->Text=L"所有类型";
  newBoxItem->TagString="0";
  cbBoxClientClass->AddObject(newBoxItem);
   Query->Close();
   Query->SQL->Text="SELECT ClientClassPKID,ClientClassName FROM tbClientClass";
   Query->Open();
   Query->First();
   while(!Query->Eof)
   {
		newBoxItem=new TListBoxItem(cbBoxClientClass);
		newBoxItem->Text=Query->FieldByName("ClientClassName")->AsString;
		newBoxItem->TagString=Query->FieldByName("ClientClassPKID")->AsString;
		cbBoxClientClass->AddObject(newBoxItem);
		Query->Next();
   }
   Query->Close();
  if(cbBoxClientClass->Count>0)
   cbBoxClientClass->ItemIndex=0;
}
