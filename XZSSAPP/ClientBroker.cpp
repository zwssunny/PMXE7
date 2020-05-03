//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "ClientBroker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TClientBroker::TClientBroker(TComponent* Owner)
{
    Connected = false;
	RESTClient = new TRESTClient(Owner);
	Request = new TRESTRequest(Owner);
	Response = new TRESTResponse(Owner);
	BaseDataSet = new TClientDataSet(Owner);
	DataSetAdapter = new TRESTResponseDataSetAdapter(Owner);
	Request->AcceptCharset = "UTF-8, *;q=0.8";
	Request->Client = RESTClient;
	Request->Response = Response;
	DataSetAdapter->Response = Response;
	DataSetAdapter->Dataset = BaseDataSet;
}
//---------------------------------------------------------------------------
void __fastcall TClientBroker::SetBaseUrl(String Url)
{
 	RESTClient->BaseURL = Url;
}
//---------------------------------------------------------------------------
TClientDataSet* __fastcall TClientBroker::Execute(String Resource, TRESTRequestMethod Method, TRESTRequestParameterList *Params)
{
   try{
	DataSetAdapter->RootElement = "";
	Request->Resource = Resource;
	Request->Method = Method;
	Request->Params = Params;
	Request->Execute();
	return BaseDataSet;
   }
	catch(System::Sysutils::Exception &e)
	{
		throw System::Sysutils::Exception(e.Message);
	}
}
//---------------------------------------------------------------------------
TClientDataSet* __fastcall TClientBroker::SetRootElement(String Root)
{
	DataSetAdapter->RootElement = Root;
    return BaseDataSet;
}
//---------------------------------------------------------------------------
