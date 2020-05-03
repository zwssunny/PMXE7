//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ClientVisitDetailEdit.h"
#include "System.DateUtils.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseBillForm"
#pragma resource "*.fmx"
TfrmClientVisitDetailEdit *frmClientVisitDetailEdit;
//---------------------------------------------------------------------------
__fastcall TfrmClientVisitDetailEdit::TfrmClientVisitDetailEdit(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param)
	: TfrmBaseBillForm(Owner,clBroker,modulecode,param)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmClientVisitDetailEdit::ClearData()
{
	edSubject->Text = "";
	deDate->Date = Today();
	edAddress->Text = "";
	mmSummary->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientVisitDetailEdit::FillData(String ID)
{
	FID = ID;
	if(FID.IsEmpty())
		ClearData();
	else
	{
		TRESTRequestParameterList *Params = new TRESTRequestParameterList(this);
		Params->AddItem("ID",FID);
		Query = csGetData("/Work/tbClientVisitDetail/Load",Params);
		if(Query->Active && Query->RecordCount > 0)
		{
			Query->First();
			edSubject->Text = Query->FieldByName("Subject")->AsString;
			deDate->Text = Query->FieldByName("Date")->AsString;
			edAddress->Text = Query->FieldByName("Address")->AsString;
			mmSummary->Text = Query->FieldByName("Summary")->AsString;
		}
	}
	FNeedFreshList = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientVisitDetailEdit::BtnSaveClick(TObject *Sender)
{
	if(!FMasterID.IsEmpty())
	{
		TJSONObject *formData = new TJSONObject();
		formData->AddPair("MasterID",FMasterID);
		formData->AddPair("Subject",edSubject->Text);
		formData->AddPair("Date",deDate->Text);
		formData->AddPair("Address",edAddress->Text);
		formData->AddPair("Summary",mmSummary->Text);
		if(!FID.IsEmpty())
			formData->AddPair("FID",FID);

		TJSONArray* data = new TJSONArray();
		data->Add(formData);

        TRESTRequestParameterList *Params = new TRESTRequestParameterList(this);
		Params->AddUrlSegment("data",data->ToString());
		Query = PostData("/Work/tbClientVisitDetail/SaveChange?Data={data}",Params);

		if(Query->Active && Query->RecordCount > 0)
		{
			bool Success = Query->FieldByName("Success")->AsBoolean;
			if(Success)
			{
                FNeedFreshList = true;
				ShowMessage(L"保存成功!");
			}
			else
			{
				String Message = Query->FieldByName("Message")->AsString;
				if(Message.IsEmpty())
					Message = L"提交失败，请稍候重试!";
				ShowMessage(Message);
			}
		}
		else
			ShowMessage(L"提交失败!");
	}
}
//---------------------------------------------------------------------------

