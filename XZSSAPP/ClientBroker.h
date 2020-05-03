//---------------------------------------------------------------------------

#ifndef ClientBrokerH
#define ClientBrokerH
//---------------------------------------------------------------------------
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <IPPeerClient.hpp>
#include <REST.Response.Adapter.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class PACKAGE TClientBroker
{
private:

public:
	String UserName;
	int UserID;
	int DepID;
	String DepName;
	int RoleID;
	String RoleName;
	String LoginCode;
	TRESTClient *RESTClient;
	TRESTRequest *Request;
	TRESTResponse *Response;
	TRESTResponseDataSetAdapter *DataSetAdapter;
	TClientDataSet *BaseDataSet;
	bool Connected;
	String LogonCode,Password;
	double BaseBusiRate,BaseAccuRate;
	void __fastcall SetBaseUrl(String Url);
	TClientDataSet* __fastcall Execute(String Resource, TRESTRequestMethod Method, TRESTRequestParameterList *Params);
    TClientDataSet* __fastcall SetRootElement(String Root);
	__fastcall TClientBroker(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif

