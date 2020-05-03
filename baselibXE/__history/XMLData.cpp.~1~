// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "XMLData.h"
#include "BaseFunc.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
String __fastcall DataSetToXMLData(TCustomADODataSet *ADataSet)
{
	String retString = "";
	if(ADataSet == NULL) return retString;
	TClientDataSet *ClientDataSet = new TClientDataSet(NULL);
	TDataSetProvider *DataSetProvider = new TDataSetProvider(NULL);
	try
	{
		DataSetProvider->DataSet = ADataSet;
		ClientDataSet->SetProvider(DataSetProvider);
		ClientDataSet->Active = true;
		retString = ClientDataSet->XMLData;
	}
	__finally
	{
		delete ClientDataSet;
		delete DataSetProvider;
	}
	return retString;
}
// ---------------------------------------------------------------------------
TStream* __fastcall AdoDataSetToCDStream(TCustomADODataSet *ADataSet)
{
	if(ADataSet == NULL) return NULL;
	TMemoryStream *retStream = new TMemoryStream();
	TClientDataSet *ClientDataSet = new TClientDataSet(NULL);
	TDataSetProvider *DataSetProvider = new TDataSetProvider(NULL);
	try
	{
		DataSetProvider->DataSet = ADataSet;
		ClientDataSet->SetProvider(DataSetProvider);
		ClientDataSet->Active = true;
		ClientDataSet->SaveToStream(retStream,dfBinary);
		retStream->Position=0;
	}
	__finally
	{
		delete ClientDataSet;
		delete DataSetProvider;
	}
	return retStream;
}
// ---------------------------------------------------------------------------
bool __fastcall XMLDataToDataSet(String xmlData, TADODataSet &ADataSet)
{
	if(xmlData == "") return false;
	TClientDataSet *ClientDataSet = new TClientDataSet(NULL);
	try
	{
		ClientDataSet->XMLData = xmlData;
		ADataSet.ClearFields();
		ADataSet.FieldDefs->Assign(ClientDataSet->FieldDefs);
		ADataSet.CreateDataSet();
		ClientDataSet->First();
		while (!ClientDataSet->Eof)
		{
			ADataSet.Append();
			for (int i = 0; i < ClientDataSet->FieldCount; i++)
			{
				ADataSet.Fields->Fields[i]->Value =
					ClientDataSet->Fields->Fields[i]->Value;
			}
			ADataSet.Post();
			ClientDataSet->Next();
		}
	}
	__finally
	{
		delete ClientDataSet;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall SetAllFieldCanModify(TCustomADODataSet *ds)
{
	String temFileName = OpenTempFile("QDS");
	String TemBuff,retstr;
	int endpos;
  ds->SaveToFile(temFileName,pfXML);
  TStringStream	*ms = new TStringStream("", TEncoding::UTF8, true);
	try
	{
		ms->LoadFromFile(temFileName);
		ms->Position = 0;
		TemBuff = ms->DataString;
		for (int i = 0; i < ds->FieldCount; i++)
		{
			if(ds->Fields->Fields[i]->ReadOnly)
			{
				retstr = GetSpecStr(TemBuff,"<s:AttributeType name='"+ds->Fields->Fields[i]->FieldName+"'",">",endpos);
				if(!retstr.Trim().IsEmpty())
					TemBuff.Insert(" rs:writeunknown='true'", endpos);
			}
		}
		ms->Clear();
		ms->WriteString(TemBuff);
		ms->SaveToFile(temFileName);
		ds->LoadFromFile(temFileName);
	}
	__finally
	{
		DeleteFile(temFileName);
		delete ms;
	}
}
//---------------------------------------------------------------------------
