//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Test.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmTest *frmTest;
//---------------------------------------------------------------------------
__fastcall TfrmTest::TfrmTest(TComponent* Owner, TClientBroker *AClientBroker)
	: TForm(Owner)
{
	FClientBroker = AClientBroker;
	FJServerDataSetClient=new TZClientDataSet(this, FClientBroker,"101001");
	m_MasterDisplayName = new TStringList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTest::Button1Click(TObject *Sender)
{
	String sStatus, sFieldName, sFieldVal;
	FJServerDataSetClient->Open();
	DataSource1->DataSet=FJServerDataSetClient->MasterDataSet;
	// ��ȡҵ������Ϣ
/*	TJSONObject *ClsJSON = FJServerDataSetClient->GetInitResult("101001");
	if(ClsJSON->Size() > 0)
	{
		sStatus = ClsJSON->Get("Status")->JsonValue->Value();
		if(sStatus=="s")
		{
			m_DataSetType = ClsJSON->Get("DataSetType")->JsonValue->Value().ToInt();
			m_MasterDisplayName->Clear();
			m_MasterDisplayName->Text = ClsJSON->Get("MasterDisplayName")->JsonValue->Value();
			TStringColumn *pt = NULL;
			for(int i=0;i<m_MasterDisplayName->Count;i++)
			{
				pt = new TStringColumn(this);
				pt->Parent = StringGrid1;
				pt->Header = m_MasterDisplayName->Strings[i];
			}
		}
		else
		{
			String ErrorMsg = ClsJSON->Get("ErrorMessage")->JsonValue->Value();
			throw Exception(ErrorMsg);
		}
	}  */
/*
	// ����JSON��������
	TJSONObject *InJSON = new TJSONObject();
	InJSON->AddPair(new TJSONPair("MasterWhere",""));
	InJSON->AddPair(new TJSONPair("MasterOrder",""));
	InJSON->AddPair(new TJSONPair("DetailWhere",""));
	InJSON->AddPair(new TJSONPair("DetailOrder",""));

	// ��ȡJSON���ݣ���������䵽������
	TJSONObject *OutJSON = new TJSONObject();
	OutJSON = (TJSONObject*)(FJServerDataSetClient->Open(InJSON,"101001")->Clone());
	if(OutJSON->Size() > 0)
	{
		sStatus = OutJSON->Get("Status")->JsonValue->Value();
		if(sStatus=="s")
		{
			// ȡ����Ϣ
			TJSONObject *MstJson   = (TJSONObject*)OutJSON->Get("Master")->JsonValue;
			TJSONArray *JSONArray  = (TJSONArray*)(MstJson->Get(1)->JsonValue);
			TJSONObject *elmObject = NULL;
			TStringColumn *pt      = NULL;
			for(int i=0;i<JSONArray->Size();i++)
			{
				elmObject = (TJSONObject*)(JSONArray->Get(i));
				pt = new TStringColumn(this);
				pt->Parent = StringGrid1;
				pt->Header = elmObject->Get("FieldName")->JsonValue->Value();
			}

			// ȡ��¼
			JSONArray = (TJSONArray*)(MstJson->Get(0)->JsonValue);
			StringGrid1->RowCount = JSONArray->Size();
			for(int iRow=0;iRow<StringGrid1->RowCount;iRow++)
			{
				elmObject = (TJSONObject*)(JSONArray->Get(iRow));
				for(int iCol=0;iCol<StringGrid1->ColumnCount;iCol++)
				{
					sFieldName = StringGrid1->Columns[iCol]->Header;
					sFieldVal  = elmObject->Get(sFieldName)->JsonValue->Value();
					StringGrid1->Cells[iCol][iRow] = sFieldVal;
				}
			}
		}
		else
		{
			String ErrorMsg = OutJSON->Get("ErrorMessage")->JsonValue->Value();
			throw Exception(ErrorMsg);
		}
	}  */
}
//---------------------------------------------------------------------------
__fastcall TfrmTest::~TfrmTest()
{
	delete m_MasterDisplayName;
	delete  FJServerDataSetClient;
}
//---------------------------------------------------------------------------
