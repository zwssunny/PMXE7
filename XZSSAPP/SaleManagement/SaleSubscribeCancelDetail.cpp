//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SaleSubscribeCancelDetail.h"
#include "CommFunc.h"
#include <REST.Json.Types.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WorkFlowDetailForm"
#pragma resource "*.fmx"
TfrmSaleSubscribeCancelDetail *frmSaleSubscribeCancelDetail;
//---------------------------------------------------------------------------
__fastcall TfrmSaleSubscribeCancelDetail::TfrmSaleSubscribeCancelDetail(TComponent* Owner,TClientBroker *clBroker,int modulecode,TClientDataSet *m_DataSet,String param)
	: TfrmWorkFlowDetailForm(Owner,clBroker,modulecode,m_DataSet,param)
{
	Dictionary = new TStringList();
	GetDictionary();
	InitPayMode();
}
//---------------------------------------------------------------------------
__fastcall TfrmSaleSubscribeCancelDetail::~TfrmSaleSubscribeCancelDetail()
{
	if(Dictionary)
	{
		delete Dictionary;
		Dictionary = NULL;
	}
	if(DocumentFields)
	{
		delete DocumentFields;
		DocumentFields = NULL;
	}
	if(CanNotPassWfs)
	{
		delete CanNotPassWfs;
		CanNotPassWfs = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::LoadConfig()
{
	if(DataSet->Active && DataSet->RecordCount > 0)
	{
        FWfsID = DataSet->FieldByName("WfsID")->AsString;
		TJSONObject *ParamData = new TJSONObject();
		ParamData->AddPair("Mode","Edit");
		ParamData->AddPair("MenuID",ModuleCode);
		ParamData->AddPair("FlowID",DataSet->FieldByName("FlowID")->AsInteger);
		ParamData->AddPair("WfsID",DataSet->FieldByName("WfsID")->AsString);
		ParamData->AddPair("GUID",DataSet->FieldByName("GUID")->AsString);
		ParamData->AddPair("FID",DataSet->FieldByName("FID")->AsString);
		ParamData->AddPair("MainID",DataSet->FieldByName("MainID")->AsString);
		ParamData->AddPair("DocSN",DataSet->FieldByName("DocSN")->AsString);
		TRESTRequestParameterList *ConfigParame = new TRESTRequestParameterList(this);
		ConfigParame->AddItem("Param",ParamData->ToString());

		Query = csGetData("/WorkFlow/WorkFlowBusinessPage/LoadConfig",ConfigParame);
		if(Query->Active && Query->RecordCount > 0)
		{
			String ResponseContent = ClientBroker->Response->Content;
			ResponseContent = ReplaceStr(ResponseContent,"\"[","[");
			ResponseContent = ReplaceStr(ResponseContent,"]\"","]");
			ResponseContent = ReplaceStr(ResponseContent,"\\\"","\"");
			ResponseContent = ReplaceStr(ResponseContent,"\\r","");
			ResponseContent = ReplaceStr(ResponseContent,"\\n","");
			TJSONObject *ParamJson = new TJSONObject();
			ParamJson->Parse(BytesOf(ResponseContent),0);
			TJSONObject *WorkFlowInfo = (TJSONObject *)ParamJson->Get("WorkFlowInfo")->JsonValue;
			DocumentFields = (TJSONArray*)((TJSONPair*)WorkFlowInfo->Get("DocumentFields")->JsonValue);
			CanNotPassWfs = (TJSONArray*)((TJSONPair*)WorkFlowInfo->Get("CanNotPassWfs")->JsonValue);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::FillData()
{
	LoadConfig();
	NeedRefresh = false;
	if(DataSet->Active && DataSet->RecordCount > 0 && !LoadUrl.IsEmpty())
	{
		TRESTRequestParameterList *Params = new TRESTRequestParameterList(this);
		Params->AddUrlSegment("ID",DataSet->FieldByName("FID")->AsString);
		Query = csGetData(LoadUrl,Params);
		if(Query->Active && Query->RecordCount > 0)
		{
			edSubscribeID->Text = Query->FieldByName("SubscribeID")->AsString;
			edClientIDName->Text = Query->FieldByName("ClientIDName")->AsString;
			edEstateIDName->Text = Query->FieldByName("EstateIDName")->AsString;
			edBuildingIDName->Text = Query->FieldByName("BuildingIDName")->AsString;
			edRoomIDName->Text = Query->FieldByName("RoomIDName")->AsString;
			edDate->Text = EncodeJsonDate(Query->FieldByName("Date")->AsString);
			edChargeAmt->Text = FormatFloatToStr(Query->FieldByName("ChargeAmt")->AsFloat,ftAmt,2);
			edFactReturnAmt->Text = FormatFloatToStr(Query->FieldByName("FactReturnAmt")->AsFloat,ftAmt,2);
			mmReason->Text = Query->FieldByName("Reason")->AsString;

			edHouseTypeName->Text = GetTextFromDict(Query->FieldByName("HouseTypeName")->AsString);
			edPresellAmt->Text = FormatFloatToStr(Query->FieldByName("PresellAmt")->AsFloat,ftAmt,2);
			edStatus->Text = GetTextFromDict(Query->FieldByName("Status")->AsString);
			edSellType->Text = GetTextFromDict(Query->FieldByName("SellType")->AsString);
			edFloorAreaPrice->Text = FormatFloatToStr(Query->FieldByName("FloorAreaPrice")->AsFloat,ftPrice,2);
			edFloorArea->Text = FormatFloatToStr(Query->FieldByName("FloorArea")->AsFloat,ftQty,2);
			edInnerAreaPrice->Text = FormatFloatToStr(Query->FieldByName("InnerAreaPrice")->AsFloat,ftPrice,2);
			edInnerArea->Text = FormatFloatToStr(Query->FieldByName("InnerArea")->AsFloat,ftQty,2);
			cbAreaType->ItemIndex = Query->FieldByName("AreaType")->AsInteger;
			edSignDate->Text = EncodeJsonDate(Query->FieldByName("SignDate")->AsString);
			edSalesName->Text = Query->FieldByName("SalesName")->AsString;

			for(int i=0;i<cbPayMode->Count;i++)
			{
				if(cbPayMode->ListItems[i]->TagString == Query->FieldByName("PayMode")->AsString)
				{
					cbPayMode->ListItems[i]->IsSelected = true;
					break;
                }
            }
			edFloorPrice->Text = FormatFloatToStr(Query->FieldByName("FloorAreaPrice")->AsFloat,ftPrice,2);
			edInnerPrice->Text = FormatFloatToStr(Query->FieldByName("InnerAreaPrice")->AsFloat,ftPrice,2);
			edDealFloorPrice->Text = FormatFloatToStr(Query->FieldByName("DealFloorPrice")->AsFloat,ftPrice,2);
			edDealInnerPrice->Text = FormatFloatToStr(Query->FieldByName("DealInnerPrice")->AsFloat,ftPrice,2);
			edAmt->Text = FormatFloatToStr(Query->FieldByName("Amt")->AsFloat,ftAmt,2);
			edDiscount->Text = FormatFloatToStr(Query->FieldByName("Discount")->AsFloat,ftAmt,2);
			edDisAmt->Text = FormatFloatToStr(Query->FieldByName("DisAmt")->AsFloat,ftAmt,2);
			edDealAmt->Text = FormatFloatToStr(Query->FieldByName("DealAmt")->AsFloat,ftAmt,2);
		}
	}
	SetUserCtrlStatus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::GetDictionary()
{
	Query = csGetData("/Common/MobileService/GetDictData?IDArray=24,17,25",new TRESTRequestParameterList(this));
	Dictionary->Clear();
	if(Query->Active && Query->RecordCount > 0)
	{
		Query->First();
		while(!Query->Eof)
		{
			Dictionary->Add(Query->FieldByName("FID")->AsString);
			Dictionary->Values[Dictionary->Count -1] =  Query->FieldByName("Name")->AsString;
			Query->Next();
		}
	}
}
//---------------------------------------------------------------------------
String __fastcall TfrmSaleSubscribeCancelDetail::GetTextFromDict(String id)
{
	int index = Dictionary->IndexOf(id);
	if(index >= 0)
		return Dictionary->Values[index];
	else
		return id;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::InitPayMode()
{
	cbPayMode->Clear();
	Query = csGetData("/SalesManagement/tbSalePayMode/GetAllData",new TRESTRequestParameterList(this));
    if(Query->Active && Query->RecordCount > 0)
	{
		Query->First();
		while(!Query->Eof)
		{
			TListBoxItem * newBoxItem=new TListBoxItem(cbPayMode);
			newBoxItem->Text = Query->FieldByName("Name")->AsString;
			newBoxItem->TagString = Query->FieldByName("FID")->AsString;
			cbPayMode->AddObject(newBoxItem);
			Query->Next();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::SetUserCtrlStatus()
{
	bool CanNotPass = false,CanComit = false;
	if(CanNotPassWfs)
	{
		for(int i=0;i<CanNotPassWfs->Count;i++)
		{
			if(CanNotPassWfs->Get(i)->ToString() == FWfsID)
			{
				CanNotPass = true;
				break;
            }
        }
	}
	if(DataSet->Active && DataSet->RecordCount > 0)
	{
		bool IsComplete = DataSet->FieldByName("IsComplete")->AsInteger;
		CanComit = !IsComplete;
		CanNotPass = CanNotPass && !IsComplete;
	}
	BtnCommit->Enabled = CanComit;
	BtnNotPass->Enabled = CanNotPass;
}
//---------------------------------------------------------------------------
TRESTRequestParameterList* __fastcall TfrmSaleSubscribeCancelDetail::GetCommitParam()
{
	TRESTRequestParameterList *CommitParame = new TRESTRequestParameterList(this);
	TJSONObject *PostData = new TJSONObject();
	PostData->AddPair("WfsID",DataSet->FieldByName("WfsID")->AsString);
	PostData->AddPair("FlowID",DataSet->FieldByName("FlowID")->AsInteger);
	PostData->AddPair("GUID",DataSet->FieldByName("GUID")->AsString);
	PostData->AddPair("MainID",DataSet->FieldByName("MainID")->AsString);
	PostData->AddPair("DocSN",DataSet->FieldByName("DocSN")->AsString);
	PostData->AddPair("FID",DataSet->FieldByName("FID")->AsString);

	for(int i=0;i<DocumentFields->Count;i++)
	{
		TJSONObject *field = (TJSONObject*)DocumentFields->Items[i];
		String Name = field->Values["Name"]->ToString().Trim();
		int Show = StrToInt(ReplaceStr(field->Values["Show"]->ToString(),"\"",""));
		if(Show)
		{
			String FieldName = ReplaceStr(field->Values["Name"]->ToString().Trim(),"\"","");
			if(DataSet->FindField(FieldName))
			{
				PostData->AddPair(FieldName,DataSet->FieldByName(FieldName)->AsString);
			}
		}
	}
	CommitParame->AddItem("Data",PostData->ToString());
	return CommitParame;
}
//---------------------------------------------------------------------------
TRESTRequestParameterList* __fastcall TfrmSaleSubscribeCancelDetail::GetNotPassParam(String reason)
{
	TRESTRequestParameterList *NotPassParame = new TRESTRequestParameterList(this);
	if(DataSet->Active && DataSet->RecordCount > 0)
	{
		TJSONObject *ParamData = new TJSONObject();
		ParamData->AddPair("FID",DataSet->FieldByName("FID")->AsString);
		ParamData->AddPair("MainID",DataSet->FieldByName("MainID")->AsString);
		ParamData->AddPair("WfsID",DataSet->FieldByName("WfsID")->AsString);
		ParamData->AddPair("FlowID",DataSet->FieldByName("FlowID")->AsInteger);
		ParamData->AddPair("GUID",DataSet->FieldByName("GUID")->AsString);
		ParamData->AddPair("NotPassText",reason);
		ParamData->AddPair("DocSN",DataSet->FieldByName("DocSN")->AsString);
		NotPassParame->AddItem("Data",ParamData->ToString());
	}
	return NotPassParame;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::AfterCommit(TClientDataSet *Result)
{
	if(Result->Active && Result->RecordCount > 0)
	{
		bool Success = Result->FieldByName("Success")->AsBoolean;
		if(Success)
		{
			TJSONObject *data = (TJSONObject*)TJSONObject::ParseJSONValue(Result->FieldByName("Data")->AsString);
			if(data->Values["IsComplete"]->ToString().Trim().LowerCase() == "true")
			{
				BtnCommit->Enabled = false;
				BtnNotPass->Enabled = false;
				ShowMessage(L"当前业务已审核完成！");
			}
			else
				ShowMessage(L"当前业务已提交至:" + data->Values["NextStateName"]->ToString() + L"状态，请等待审核。");

			NeedRefresh = true;
			Close();
		}
		else
		{
			String Message = Result->FieldByName("Message")->AsString;
			if(Message.IsEmpty())
				Message = L"提交失败，请稍候重试!";
			ShowMessage(Message);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSaleSubscribeCancelDetail::AfterNotPass(TClientDataSet *Result)
{
 	if(Result->Active && Result->RecordCount > 0)
	{
		bool Success = Result->FieldByName("Success")->AsBoolean;
		if(Success)
		{
			TJSONObject *data = (TJSONObject*)TJSONObject::ParseJSONValue(Result->FieldByName("Data")->AsString);
			ShowMessage(L"当前业务已返回至:" + data->Values["NextStateName"]->ToString() + L"状态，请等待操作人员重新提交审核。");
            NeedRefresh = true;
			Close();
		}
		else
		{
			String Message = Result->FieldByName("Message")->AsString;
			if(Message.IsEmpty())
				Message = L"提交失败，请稍候重试!";
			ShowMessage(Message);
        }
    }
}
//---------------------------------------------------------------------------

