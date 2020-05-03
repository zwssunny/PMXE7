//---------------------------------------------------------------------------

#pragma hdrstop

#include "LocateQueueProc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TLocateQueueProc::TLocateQueueProc(TLocateRecord& ALocateRecord,String AKey, String AValue)
{
	FLocateRecord=ALocateRecord;
	FKey=AKey;
	FValue=AValue;
}
//---------------------------------------------------------------------------
void __fastcall TLocateQueueProc::Invoke()
{
  FLocateRecord(FKey,FValue);
}
//---------------------------------------------------------------------------
