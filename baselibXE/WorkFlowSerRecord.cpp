//---------------------------------------------------------------------------

#pragma hdrstop

#include "WorkFlowSerRecord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TWorkFlowSerRecord::TWorkFlowSerRecord()
:TBaseObject()
{
 Initialized();
}
void __fastcall TWorkFlowSerRecord::Initialized()
{
	FThreadSessionId=0;
	FIpAdress="";
	FClientPort="";
	FProtocol="";
	FCallBackClientID="";
	FAppName="";
	FLoginTime=Now();

}
__fastcall TWorkFlowSerRecord:: ~TWorkFlowSerRecord()
{

}
__fastcall TWorkFlowSerRecord::TWorkFlowSerRecord(TJSONObject* Json)
:TBaseObject()
{
  Initialized();
  if (Json->Count>0)
   {
   FThreadSessionId=Json->GetValue("threadSessionid")->Value().ToInt();
   FCallBackClientID=Json->GetValue("callbackclientid")->Value();
   FIpAdress=Json->GetValue("ipadress")->Value();
   FClientPort=Json->GetValue("clientport")->Value();
   FProtocol=Json->GetValue("protocol")->Value();
   FAppName= Json->GetValue("appname")->Value();
   FLoginTime=StrToDateTime(Json->GetValue("logintime")->Value());
   }
}
TJSONObject* __fastcall  TWorkFlowSerRecord::ObjectToJSON()
{
  TJSONObject *result=new  TJSONObject();
  result->AddPair(new TJSONPair("threadSessionid", IntToStr(FThreadSessionId)));
  result->AddPair(new TJSONPair("callbackclientid", FCallBackClientID));
  result->AddPair(new TJSONPair("ipadress", FIpAdress));
  result->AddPair(new TJSONPair("protocol", FProtocol));
  result->AddPair(new TJSONPair("clientport", FClientPort));
  result->AddPair(new TJSONPair("appname", FAppName));
  result->AddPair(new TJSONPair("logintime", FormatDateTime("yyyy-MM-dd HH:mm:ss",FLoginTime)));
  return result;
}
