//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ZhengQiGuoLuEdit.h"
#include "NotPassTextForm.h"
#include "NotPassMethod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmZhengQiGuoLuEdit *frmZhengQiGuoLuEdit;
//---------------------------------------------------------------------------
__fastcall TfrmZhengQiGuoLuEdit::TfrmZhengQiGuoLuEdit(TComponent* Owner,TClientBroker *ClientBroker,String Flowid,String Mainid,String Relid)
	: TForm(Owner)
{
	FClientBroker = ClientBroker;
	FlowID = Flowid;
	RelID = Relid;
	MainID = Mainid;

	ClientBroker->DataSetAdapter->Dataset = ClientDataSet1;

	ClientBroker->Request->Resource = "Document/EditDynamicPage/Load";
	ClientBroker->Request->Params->Clear();
	ClientBroker->Request->Params->AddItem("FlowID",Flowid);
	ClientBroker->Request->Params->AddItem("MainID",Mainid);
	ClientBroker->Request->Params->AddItem("ViewMode","Browse");
	ClientBroker->Request->Params->AddItem("RelID",Relid);
	ClientBroker->Request->Execute();

	bool aa = ClientDataSet1->FieldByName("success")->AsBoolean;

	if(ClientDataSet1->FieldByName("success")->AsBoolean)
	{
		ClientBroker->DataSetAdapter->RootElement = "data.Header";
		if(ClientDataSet1->RecordCount > 0)
		{
			ClientDataSet1->First();
			UseProject = ClientDataSet1->FieldByName("UseProject")->AsString;
			GUID = ClientDataSet1->FieldByName("GUID")->AsString;
			UseDep = ClientDataSet1->FieldByName("UseDep")->AsString;
			WfsID = ClientDataSet1->FieldByName("WfsID")->AsString;
			edUseDepName->Text = ClientDataSet1->FieldByName("UseDepName")->AsString;
			edDocSN->Text = ClientDataSet1->FieldByName("DocSN")->AsString;
			edUseProjectName->Text = ClientDataSet1->FieldByName("UseProjectName")->AsString;
			edUseAddress->Text = ClientDataSet1->FieldByName("UseAddress")->AsString;
		}

		ClientBroker->DataSetAdapter->RootElement = "data.Body";
        if(ClientDataSet1->RecordCount > 0)
		{
			ClientDataSet1->First();
			SubID = ClientDataSet1->FieldByName("SubID")->AsString;
			edBoilerGuoLuShuiWei->Text = ClientDataSet1->FieldByName("BoilerGuoLuShuiWeiName")->AsString;
			edBoilerRanShaoJi->Text = ClientDataSet1->FieldByName("BoilerRanShaoJiName")->AsString;
			edBoilerKongZhiXiangJiAnNiu->Text = ClientDataSet1->FieldByName("BoilerKongZhiXiangJiAnNiuName")->AsString;
			edBoilerShuiWeiKongZhiXiTong->Text = ClientDataSet1->FieldByName("BoilerShuiWeiKongZhiXiTongName")->AsString;
			edBoilerYaLiKongZhiXiTong->Text = ClientDataSet1->FieldByName("BoilerYaLiKongZhiXiTongName")->AsString;
			edBoilerAnQuanFa->Text = ClientDataSet1->FieldByName("BoilerAnQuanFaName")->AsString;
			edBoilerPaiYanXiTong->Text = ClientDataSet1->FieldByName("BoilerPaiYanXiTongName")->AsString;
			edBoilerZhuZhengQiFa->Text = ClientDataSet1->FieldByName("BoilerZhuZhengQiFaName")->AsString;
			edBoilerPaiWuFa->Text = ClientDataSet1->FieldByName("BoilerPaiWuFaName")->AsString;
			edBoilerBaoJingZhuangZhi->Text = ClientDataSet1->FieldByName("BoilerBaoJingZhuangZhiName")->AsString;
			edAEgongShuiXiTong->Text = ClientDataSet1->FieldByName("AEgongShuiXiTongName")->AsString;
			edAEgongYouXiTong->Text = ClientDataSet1->FieldByName("AEgongYouXiTongName")->AsString;
			edAEgongQiXiTong->Text = ClientDataSet1->FieldByName("AEgongQiXiTongName")->AsString;
			edAEfenQiXiang->Text = ClientDataSet1->FieldByName("AEfenQiXiangName")->AsString;
			edAEruanShuiChuLiQi->Text = ClientDataSet1->FieldByName("AEruanShuiChuLiQiName")->AsString;
			edAEriYongShuiXiangShuiWei->Text = ClientDataSet1->FieldByName("AEriYongShuiXiangShuiWeiName")->AsString;
			edAEriYongYouXiangYouWei->Text = ClientDataSet1->FieldByName("AEriYongYouXiangYouWeiName")->AsString;
			mmQITaQingKuang->Text = ClientDataSet1->FieldByName("QITaQingKuang")->AsString;
		}

		ClientBroker->DataSetAdapter->RootElement = "data.Footer";
		if(ClientDataSet1->RecordCount > 0)
		{
			ClientDataSet1->First();
			edAddMan->Text = ClientDataSet1->FieldByName("AddManName")->AsString;
			edAddDate->Text = ClientDataSet1->FieldByName("AddDate")->AsString;
		}
	}
	ClientBroker->DataSetAdapter->RootElement = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmZhengQiGuoLuEdit::Button1Click(TObject *Sender)
{
    if(MessageDlg(_D("确定提交审批吗？") ,TMsgDlgType::mtConfirmation,mbYesNo,0)==mrYes)
	{
		TJSONObject *PostData = new TJSONObject();
		TJSONObject *HeaderData = new TJSONObject();
		TJSONArray *BodyData = new TJSONArray();
		TJSONObject *FooterData = new TJSONObject();

		HeaderData->AddPair("UseProject",UseProject);
		HeaderData->AddPair("UseDep",UseDep);
		HeaderData->AddPair("ViewMode","Edit");
		HeaderData->AddPair("FlowID",FlowID);
		HeaderData->AddPair("MainID",MainID);
		HeaderData->AddPair("WfsID",WfsID);
		HeaderData->AddPair("RelID",RelID);
		HeaderData->AddPair("GUID",GUID);
		HeaderData->AddPair("IDArray",MainID);
		HeaderData->AddPair("AutoCreatePriceID",false);
		HeaderData->AddPair("AutoCreateField","[\"PriceID\"]");

		TJSONObject *SubData = new TJSONObject();
		SubData->AddPair("SubID",SubID);
		BodyData->Add(SubData);

		FooterData->AddPair("AuditDate",Now().FormatString("YYYY-MM-DD"));
		FooterData->AddPair("AuditMan",IntToStr(FClientBroker->UserID));

		PostData->AddPair("Header",HeaderData);
		PostData->AddPair("Body",BodyData);
		PostData->AddPair("Footer",FooterData);

		FClientBroker->Request->Resource = "Document/EditDynamicPage/Commit";
		FClientBroker->Request->Params->Clear();
		FClientBroker->Request->Params->AddItem("GUID",GUID);
		FClientBroker->Request->Params->AddItem("FlowID",FlowID);
		FClientBroker->Request->Params->AddItem("Data",PostData->ToString());
		FClientBroker->Request->Execute();

		String result = ClientDataSet1->FieldByName("success")->AsString;
		if(result.LowerCase() == "true")
		{
			FClientBroker->DataSetAdapter->RootElement = "data";
			String current = ClientDataSet1->FieldByName("current")->AsString;
			String Msg = "";
			if(current.IsEmpty())
				Msg = L"提交成功！";
			else
				Msg = L"业务已提交至【" + current + L"】状态，等待其它人员处理！";
			MessageDlg(Msg ,TMsgDlgType::mtInformation,mbOKCancel,0);
			FClientBroker->DataSetAdapter->RootElement = "";
		}
		else
		{
			MessageDlg(_D("提交失败！"+ClientDataSet1->FieldByName("message")->AsString) ,TMsgDlgType::mtInformation,mbOKCancel,0);
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZhengQiGuoLuEdit::btCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmZhengQiGuoLuEdit::Button2Click(TObject *Sender)
{
	TfrmNotPassTextForm *p = new TfrmNotPassTextForm(this);
	TNotPassMethodReference  *Lm=new TNotPassMethodReference;
	Lm->dlg=p;
	Lm->OwerForm=this;
	p->ShowModal(Lm);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZhengQiGuoLuEdit::NotPass(String reason)
{
 	String NotPassText = reason;
	TJSONObject *PostData = new TJSONObject();
	TJSONObject *HeaderData = new TJSONObject();
	TJSONObject *FooterData = new TJSONObject();

	HeaderData->AddPair("UseProject",UseProject);
	HeaderData->AddPair("UseDep",UseDep);
	HeaderData->AddPair("ViewMode","Edit");
	HeaderData->AddPair("FlowID",FlowID);
	HeaderData->AddPair("MainID",MainID);
	HeaderData->AddPair("WfsID",WfsID);
	HeaderData->AddPair("RelID",RelID);
	HeaderData->AddPair("GUID",GUID);
	HeaderData->AddPair("IDArray",MainID);
	HeaderData->AddPair("AutoCreatePriceID",false);
	HeaderData->AddPair("AutoCreateField","[\"PriceID\"]");
	HeaderData->AddPair("NotPassText",NotPassText);

	FooterData->AddPair("AuditDate",Now().FormatString("YYYY-MM-DD"));
	FooterData->AddPair("AuditMan",IntToStr(FClientBroker->UserID));

	PostData->AddPair("Header",HeaderData);
	PostData->AddPair("Footer",FooterData);

	FClientBroker->Request->Resource = "Document/EditDynamicPage/NotPass";
	FClientBroker->Request->Params->Clear();
	FClientBroker->Request->Params->AddItem("GUID",GUID);
	FClientBroker->Request->Params->AddItem("FlowID",FlowID);
	FClientBroker->Request->Params->AddItem("Data",PostData->ToString());
	FClientBroker->Request->Execute();

	String result = ClientDataSet1->FieldByName("success")->AsString;
	if(result.LowerCase() == "true")
	{
		FClientBroker->DataSetAdapter->RootElement = "data";
		String current = ClientDataSet1->FieldByName("current")->AsString;
		String Msg = "";
		if(current.IsEmpty())
			Msg = L"提交成功！";
		else
			Msg = L"业务已返回至【" + current + L"】状态，等待其它人员处理！";
		MessageDlg(Msg ,TMsgDlgType::mtInformation,mbOKCancel,0);
		FClientBroker->DataSetAdapter->RootElement = "";
	}
	else
	{
		MessageDlg(_D("提交失败！"+ClientDataSet1->FieldByName("message")->AsString) ,TMsgDlgType::mtInformation,mbOKCancel,0);
	}
}
//---------------------------------------------------------------------------
