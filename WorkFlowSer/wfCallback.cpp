//---------------------------------------------------------------------------

#pragma hdrstop

#include "wfCallback.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TWFCallbackClient:: TWFCallbackClient(TDSClientCallbackChannelManager* AChannelManager, String ACallbackName)
:TDBXCallback()
{
  FHookCallBack=NULL;
  FChannelManager=AChannelManager;
  FCallbackName=ACallbackName;
  if(FChannelManager)
	 FChannelManager->RegisterCallback(FCallbackName,this);
}
//---------------------------------------------------------------------------
__fastcall TWFCallbackClient:: ~TWFCallbackClient()
{
  // if(FChannelManager)
 //  FChannelManager->UnregisterCallback(FCallbackName);
}
TJSONValue* __fastcall TWFCallbackClient::Execute(TJSONValue* const Arg)
{
   TJSONObject * Result=new TJSONObject();
   Result->AddPair(new TJSONPair("notificationType", "workflow"));
   TJSONObject * FArg=(TJSONObject*)Arg;
  if(FArg->Count>0)
  {
	if(FHookCallBack)
	{
      FHookCallBack((TJSONObject*)(FArg->Clone()),Result);
  //	 TThreadProcedure* methProc(static_cast<TThreadProcedure*>(new TWFQueueProc(FHookCallBack,(TJSONObject*)(FArg->Clone()),Result)));
   //	 TThread::Queue(0, methProc);
	 }
   }
   return Result;
}
//---------------------------------------------------------------------------
System::TObject* __fastcall TWFCallbackClient::Execute(System::TObject* Arg)
{
   return NULL;
}
//---------------------------------------------------------------------------

