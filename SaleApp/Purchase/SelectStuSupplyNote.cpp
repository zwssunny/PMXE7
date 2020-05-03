//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SelectStuSupplyNote.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseFilters"
#pragma link "StartAndEndDate"
#pragma resource "*.fmx"
TSelectStuSupplyNoteForm *SelectStuSupplyNoteForm;
//---------------------------------------------------------------------------
__fastcall TSelectStuSupplyNoteForm::TSelectStuSupplyNoteForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker)
	: TBaseFiltersForm(Owner,AOnFilteredDataSet,ABroker)
{
}
//---------------------------------------------------------------------------
String __fastcall TSelectStuSupplyNoteForm::BuildFilters()
{
  if(lvSupplyNoteList->ItemIndex>-1)
   return lvSupplyNoteList->Selected->ButtonText;
  else
	 throw Exception(L"请选中供货单号");
}
void __fastcall TSelectStuSupplyNoteForm::InitControl()
{
    StartAndEndDateFrame1->cbDateRange->ItemIndex=0;

}
String __fastcall TSelectStuSupplyNoteForm::GetFilters()
{
  String custFilters="";
  if(BillDateExpander->IsChecked)
	custFilters=" StuSpyNtCreateDate>='"+StartAndEndDateFrame1->BeginDate+"' and StuSpyNtCreateDate<='"+StartAndEndDateFrame1->EndDate+"'";
  if(!edCorpName->Text.Trim().IsEmpty()) //供应商
  {
	if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"CorpName like '%"+edCorpName->Text.Trim()+"%'";
  }
  if(!edContName->Text.Trim().IsEmpty()) //供应商
  {
	if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"ContName like '%"+edContName->Text.Trim()+"%'";
  }
  if(!edStuSpyNtNum->Text.Trim().IsEmpty()) //供应商
  {
	if(custFilters>" ")
		custFilters=custFilters+" and ";
	   custFilters=custFilters+"StuSpyNtNum like '%"+edStuSpyNtNum->Text.Trim()+"%'";
  }
  return custFilters;
}
void __fastcall TSelectStuSupplyNoteForm::FillSupplyNoteList()
{
   String 	SQLStr = " select StuSpyNtPKID,StuSpyNtFKID_Prj,StuSpyNtNum,StuSpyNtFKID_BuyCont,"
					 " StuSpyNtCreateDate,StuSpyNtCreator,StuSpyNtRemark,ContName=isnull(ContName,''),"
					 " ContSecondPty_FKID=isnull(ContSecondPty_FKID,''),CorpName=isnull(CorpName,''),"
					 " PrjPrjName=isnull(PrjPrjName,'') from tbStuSupplyNote "
					 " left join tbContract on ContPKID=StuSpyNtFKID_BuyCont"
					 " left join tbProject on StuSpyNtFKID_Prj=PrjPKID"
					 " left join tbCorporation on ContSecondPty_FKID=CorpPKID"
					 " where StuSpyNtChkState=1 and StuSpyNtPKID in (select distinct StuSpyNtDtlFKID from tbStuSupplyNote_Dtl where StuSpyNtDtlHaveInQty<StuSpyNtDtlQty)" ;
  String clientFilters=GetFilters();
  if(clientFilters>"")
	   SQLStr=SQLStr +" and "+ clientFilters;
   try{
	  lvSupplyNoteList->BeginUpdate();
	  lvSupplyNoteList->Items->Clear();
	  Query->Close();
	  Query->SQL->Text=SQLStr;
	  Query->Open();
	  while(!Query->Eof)
	  {
		 TListViewItem* vItem=lvSupplyNoteList->Items->Add();
		 vItem->ButtonText=Query->FieldByName("StuSpyNtPKID")->AsString;
		 vItem->Text=L"供货单:"+Query->FieldByName("StuSpyNtNum")->AsString
		             +L"日期:"+Query->FieldByName("StuSpyNtCreateDate")->AsString;
		 vItem->Detail=L"合同名:"+Query->FieldByName("ContName")->AsString
					 +L"供应商:"+Query->FieldByName("CorpName")->AsString;
		 Query->Next();
	  }
  }
  __finally
  {
   lvSupplyNoteList->EndUpdate();
  }
}
void __fastcall TSelectStuSupplyNoteForm::SearchEditButton1Click(TObject *Sender)

{
   FillSupplyNoteList();
}
//---------------------------------------------------------------------------

