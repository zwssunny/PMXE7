//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SaleSubscribeCancel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WorkFlowBrowseForm"
#pragma resource "*.fmx"
TfrmSaleSubscribeCancel *frmSaleSubscribeCancel;
//---------------------------------------------------------------------------
__fastcall TfrmSaleSubscribeCancel::TfrmSaleSubscribeCancel(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param)
	: TfrmWorkFlowBrowseForm(Owner,clBroker,modulecode,param)
{
	DetailForm = NULL;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSaleSubscribeCancel::GetConfigUrl()
{
 	return "/Work/tbSaleSubscribeCancel/LoadConfig";
}
//---------------------------------------------------------------------------
TForm * __fastcall TfrmSaleSubscribeCancel::NewEditForm()
{
    TLocateOptions ops;
	ops.Clear();
	ops << loCaseInsensitive;
	String id = VarToStr(BrowseGrid->Cells[0][BrowseGrid->Selected]);
	if(BusinessDataSet->Active && BusinessDataSet->Locate("SubscribeID",id,ops))
	{
		if(DetailForm == NULL)
		{
			DetailForm = new TfrmSaleSubscribeCancelDetail(this,ClientBroker,ModuleCode,BusinessDataSet,"");
			DetailForm->StyleBook = this->StyleBook;
		}
		DetailForm->CommitUrl = CommitUrl;
		DetailForm->NotPassUrl = NotPassUrl;
        DetailForm->LoadUrl = LoadUrl;
		DetailForm->FillData();
		return DetailForm;
	}
	return NULL;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSaleSubscribeCancel::GetIDColumnName()
{
	return "SubscribeID";
}
//---------------------------------------------------------------------------


