//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ZhengQiGuoLu.h"
#include <System.SysUtils.hpp>
#include "ZhengQiGuoLuEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmZhengQiGuoLu *frmZhengQiGuoLu;
//---------------------------------------------------------------------------
__fastcall TfrmZhengQiGuoLu::TfrmZhengQiGuoLu(TComponent* Owner,TClientBroker *ClientBroker,String Flowid)
	: TForm(Owner)
{
    FClientBroker = new TClientBroker(this);
	FlowID = Flowid;
	ClientBroker->DataSetAdapter->Dataset = ClientDataSet1;

	ClientBroker->Request->Resource = "Document/EditDynamicPage/GetMainBrowseSource";
	ClientBroker->Request->Params->Clear();
	ClientBroker->Request->Params->AddItem("FlowID",FlowID);
	ClientBroker->Request->Params->AddItem("pageIndex",0);
	ClientBroker->Request->Params->AddItem("pageSize",200);
	TJSONArray *FilterParam = new TJSONArray();
	TJSONObject *temp1 = new TJSONObject();
	temp1->AddPair("Key","FlowID");
	temp1->AddPair("Value",FlowID);
	temp1->AddPair("Oper","AddEqualTo");

	TJSONObject *temp2 = new TJSONObject();
	temp2->AddPair("Key","WfsID");
	temp2->AddPair("Value","9998");
	temp2->AddPair("Oper","AddEqualTo");

	FilterParam->Add(temp1);
	FilterParam->Add(temp2);

	ClientBroker->Request->Params->AddItem("FilterParam",FilterParam->ToString());
	ClientBroker->Request->Execute();
//	ClientBroker->DataSetAdapter->RootElement = "rows";

	if(!ClientDataSet1->Active)
		ClientDataSet1->Open();
	StringGrid1->RowCount = ClientDataSet1->RecordCount;
	ClientDataSet1->First();
	int i=0;

	while(!ClientDataSet1->Eof)
	{
		StringGrid1->Cells[0][i] = ClientDataSet1->FieldByName("WfsName")->AsString;
		StringGrid1->Cells[1][i] = ClientDataSet1->FieldByName("DocSN")->AsString;
		StringGrid1->Cells[2][i] = ClientDataSet1->FieldByName("UseProjectName")->AsString;
		StringGrid1->Cells[3][i] = ClientDataSet1->FieldByName("UseDepName")->AsString;
		StringGrid1->Cells[4][i] = ClientDataSet1->FieldByName("UseAddress")->AsString;
		StringGrid1->Cells[5][i] = ClientDataSet1->FieldByName("InManName")->AsString;
		StringGrid1->Cells[6][i] = EncodeJsonDate(ClientDataSet1->FieldByName("InDate")->AsString);
		StringGrid1->Cells[7][i] = ClientDataSet1->FieldByName("MainID")->AsString;
		StringGrid1->Cells[8][i] = ClientDataSet1->FieldByName("RelID")->AsString;
		ClientDataSet1->Next();
		i++;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZhengQiGuoLu::btCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
String __fastcall TfrmZhengQiGuoLu::EncodeJsonDate(String date)
{
	String dateint = date.SubString1(7,date.Length()-8);
	unsigned __int64 bb = StrToInt64(dateint);
	double days = bb / MSecsPerDay;
	TDateTime indate = EncodeDate(1970,1,1) + days;
	return indate.FormatString("YYYY-MM-DD");
}
//---------------------------------------------------------------------------
void __fastcall TfrmZhengQiGuoLu::btLookClick(TObject *Sender)
{
	int row = StringGrid1->Selected;
	if(row >= 0)
	{
		String Mainid = StringGrid1->Cells[7][row];
		String Relid = StringGrid1->Cells[8][row];

		TfrmZhengQiGuoLuEdit *p =  new TfrmZhengQiGuoLuEdit(this,FClientBroker,FlowID,Mainid,Relid);
		p->Show();
	}
}
//---------------------------------------------------------------------------

