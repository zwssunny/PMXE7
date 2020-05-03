//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HouseReserveFilters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseFilters"
#pragma resource "*.fmx"
THouseReserveFiltersForm *HouseReserveFiltersForm;
//---------------------------------------------------------------------------
__fastcall THouseReserveFiltersForm::THouseReserveFiltersForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker)
	: TBaseFiltersForm(Owner,AOnFilteredDataSet,ABroker)
{
}
//---------------------------------------------------------------------------
String __fastcall THouseReserveFiltersForm::BuildFilters()
{
  String custFilters="";
  if(cbBoxHseRsveProperty->ItemIndex>0)
  {
	 custFilters="HseRsveProperty="+IntToStr(cbBoxHseRsveProperty->ItemIndex);
  }
  if(cbHseRsveFKID_Est->ItemIndex>0)
  {
	if(custFilters>" ")
		custFilters=custFilters+" and ";
	 custFilters=custFilters+"HseRsveFKID_Est="+QuotedStr(cbHseRsveFKID_Est->Selected->TagString);
  }
  if(cbHsgFKID_Bdg->ItemIndex>0)
  {
	if(custFilters>" ")
		custFilters=custFilters+" and ";
	 custFilters=custFilters+"HseRsveFKID_Bdg="+QuotedStr(cbHsgFKID_Bdg->Selected->TagString);
  }
  if(!edHsgNum->Text.Trim().IsEmpty())
  {
	  if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"HsgNum like '%"+edHsgNum->Text.Trim()+"%'";
  }
  if(!edHseRsveNum->Text.Trim().IsEmpty())
  {
	  if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"HseRsveNum like '%"+edHseRsveNum->Text.Trim()+"%'";
  }
  if(!edClientTheName->Text.Trim().IsEmpty())
  {
	if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"ClientTheName like '%"+edClientTheName->Text.Trim()+"%'";
  }
   return custFilters;
}
void __fastcall THouseReserveFiltersForm::InitControl()
{
   InitEstNameComboBox();
   InitBdgNameComboBox();
}
void __fastcall THouseReserveFiltersForm::InitEstNameComboBox()
{
   cbHseRsveFKID_Est->Clear();
  TListBoxItem * newBoxItem=new TListBoxItem(cbHseRsveFKID_Est);
  newBoxItem->Text=L"所有楼盘";
  newBoxItem->TagString="0"; //楼盘ID
  cbHseRsveFKID_Est->AddObject(newBoxItem);
   Query->Close();
   Query->SQL->Text="select EstatePKID,EstateCode,EstateName from tbEstate order by EstateCode";
   Query->Open();
   Query->First();
   while(!Query->Eof)
   {
		newBoxItem=new TListBoxItem(cbHseRsveFKID_Est);
		newBoxItem->Text=Query->FieldByName("EstateName")->AsString;
		newBoxItem->TagString=Query->FieldByName("EstatePKID")->AsString;
		cbHseRsveFKID_Est->AddObject(newBoxItem);
		Query->Next();
   }
   Query->Close();
  if(cbHseRsveFKID_Est->Count>1)
   cbHseRsveFKID_Est->ItemIndex=1;
  else
   cbHseRsveFKID_Est->ItemIndex=0;
}
void __fastcall THouseReserveFiltersForm::InitBdgNameComboBox()
{
  cbHsgFKID_Bdg->Clear();
  TListBoxItem * newBoxItem=new TListBoxItem(cbHsgFKID_Bdg);
  newBoxItem->Text=L"所有楼阁";
  newBoxItem->TagString="0"; //ID
  cbHsgFKID_Bdg->AddObject(newBoxItem);
  if(cbHseRsveFKID_Est->ItemIndex>0) //有选中某楼盘
  {
   Query->Close();
   Query->SQL->Text="select BdgPKID,BdgNum,BdgName from tbBuilding where BdgFKID_Est="+QuotedStr(cbHseRsveFKID_Est->Selected->TagString);
   Query->Open();
   Query->First();
   while(!Query->Eof)
   {
		newBoxItem=new TListBoxItem(cbHsgFKID_Bdg);
		newBoxItem->Text=Query->FieldByName("BdgName")->AsString;
		newBoxItem->TagString=Query->FieldByName("BdgPKID")->AsString;
		cbHsgFKID_Bdg->AddObject(newBoxItem);
		Query->Next();
   }
   Query->Close();
  }
  if(cbHsgFKID_Bdg->Count>1)
   cbHsgFKID_Bdg->ItemIndex=1;
  else
   cbHsgFKID_Bdg->ItemIndex=0;
}
void __fastcall THouseReserveFiltersForm::cbHseRsveFKID_EstClosePopup(TObject *Sender)

{
   InitBdgNameComboBox();
}
//---------------------------------------------------------------------------

