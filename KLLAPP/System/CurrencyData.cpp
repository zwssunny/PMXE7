//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CurrencyData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseListShow"
#pragma resource "*.fmx"
TfrmCurrencyData *frmCurrencyData;
//---------------------------------------------------------------------------
__fastcall TfrmCurrencyData::TfrmCurrencyData(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,
							 String WhereStr)
	: TfrmBaseListShow(Owner, clBroker,ModuleCode,WhereStr)
{
	 EditForm=NULL;
	 GridBindSourceDB->DataSet=this->DataSet->MasterDataSet;
	 GridBindSourceDB->DataSource=this->MasterDataSource;
}
//---------------------------------------------------------------------------
TForm * __fastcall TfrmCurrencyData::NewEditForm(TZClientDataSet *FDataSet,int status)
{
  if(EditForm==NULL)
   EditForm=new TfrmCurrencyDataEdit(this,ClientBroker,this->FormModuleCode,FDataSet,status);
  return EditForm;
}
void __fastcall TfrmCurrencyData::FormFillData()
{
	 BindStringGridLink->Active=false;
	 BindStringGridLink->Active=true;
}
bool __fastcall TfrmCurrencyData::BeforeUpdateData(int OptType)
{
     switch(OptType)
   {
	  case 1:   //Add
         return true;
	  case 2:  //Edit
         return true;
      case 3:  //Del
          if(GetFieldValue("CurDataIsStandard")==1)
          {
 			  MessageDlg(_D("系统使用了当前币种，不能删除") ,TMsgDlgType::mtInformation,TMsgDlgButtons()<< TMsgDlgBtn::mbYes,0);
			  return false;
          }
          return true;

      default:
          return true;
   }

}


