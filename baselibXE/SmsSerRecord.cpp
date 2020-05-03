//---------------------------------------------------------------------------

#pragma hdrstop

#include "SmsSerRecord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TSmsSerRecord::TSmsSerRecord()
:TBaseObject()
{
 Initialized();
}
void __fastcall TSmsSerRecord::Initialized()
{
	FThreadSessionId=0;
	FIpAdress="";
	FClientPort="";
	FProtocol="";
	FCallBackClientID="";
	FAppName="";
	FLoginTime=Now();

}
__fastcall TSmsSerRecord:: ~TSmsSerRecord()
{

}
__fastcall TSmsSerRecord::TSmsSerRecord(TJSONObject* Json)
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
TJSONObject* __fastcall  TSmsSerRecord::ObjectToJSON()
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
