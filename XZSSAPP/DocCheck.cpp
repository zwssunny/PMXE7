//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DocCheck.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <IPPeerClient.hpp>
#include <REST.Response.Adapter.hpp>
#include <System.JSON.hpp>
//#include "ZhengQiGuoLu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmDocCheck *frmDocCheck;
//---------------------------------------------------------------------------
__fastcall TfrmDocCheck::TfrmDocCheck(TComponent* Owner,TClientBroker *ClientBroker)
	: TForm(Owner)
{
	FClientBroker =  ClientBroker;
	ClientBroker->DataSetAdapter->Dataset = ClientDataSet1;

	ClientBroker->Request->Resource = "PageCenter/GetWaitWork";
	ClientBroker->Request->Params->Clear();
	ClientBroker->Request->Execute();
//	ClientBroker->DataSetAdapter->RootElement = "rows";

	if(!ClientDataSet1->Active)
		ClientDataSet1->Open();
	StringGrid1->RowCount = ClientDataSet1->RecordCount;
	ClientDataSet1->First();
	int i=0;
	while(!ClientDataSet1->Eof)
	{
		StringGrid1->Cells[0][i] = ClientDataSet1->FieldByName("Num")->AsString;
		StringGrid1->Cells[1][i] = ClientDataSet1->FieldByName("Menu")->AsString;
		StringGrid1->Cells[2][i] = ClientDataSet1->FieldByName("MenuID")->AsString;
		StringGrid1->Cells[3][i] = ClientDataSet1->FieldByName("FlowID")->AsString;
		ClientDataSet1->Next();
		i++;
    }

//	TJSONObject *result = (TJSONObject*)TJSONObject::ParseJSONValue(ClientBroker->Response->Content);
//	TJSONArray *DataList = (TJSONArray*)result->GetValue("rows");
//	StringGrid1->RowCount = DataList->Count;
//	for(int i=0;i<DataList->Count;i++)
//	{
//		TJSONObject *Item = (TJSONObject*)DataList->Get(i);
//		StringGrid1->Cells[0][i] = Item->GetValue("Name")->ToString();
//        StringGrid1->Cells[1][i] = Item->GetValue("Number")->ToString();
//    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDocCheck::btCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDocCheck::btLookClick(TObject *Sender)
{
	int row = StringGrid1->Selected;
	if(row >= 0)
	{
		String Menuid = StringGrid1->Cells[2][row];
		String Flowid = StringGrid1->Cells[3][row];
		ShowMessage(L"²Ëµ¥ID"+Menuid+L" Á÷³ÌID"+Flowid);
//		if(Menuid == "56")
//		{
//			TfrmZhengQiGuoLu *p =  new TfrmZhengQiGuoLu(this,FClientBroker,Flowid);
//			p->Show();
//        }
	}
}
//---------------------------------------------------------------------------

