//---------------------------------------------------------------------------

#pragma hdrstop

#include "AdoConnectPool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TADOConnectionPool::TADOConnectionPool(TComponent* Owner, String ConnStr, int ACapicity)
{
	FTimeout   = 3000;
	FMaxCount  = ACapicity;
	FConnStr   = ConnStr;
	FObjList   = new TThreadList();
	FSemaphore = CreateSemaphore(NULL, FMaxCount, FMaxCount, NULL);
}
//---------------------------------------------------------------------------
__fastcall TADOConnectionPool::~TADOConnectionPool()
{
	TList *List = FObjList->LockList();
	try
	{
		for(int i=List->Count-1;i>=0;i--)
		{
			delete (TADOConnection *)List->Items[i];
		}
	}
	__finally
	{
		FObjList->UnlockList();
	}

	if(FObjList)
	{
		delete FObjList;
		FObjList = NULL;
	}

	CloseHandle(FSemaphore);
}
//---------------------------------------------------------------------------
TADOConnection* __fastcall TADOConnectionPool::CreateNewInstance(TList *List)
{
	TADOConnection *AConnection=NULL;
	try
	{
		AConnection = new TADOConnection(NULL);
		AConnection->ConnectionString = FConnStr;
		AConnection->LoginPrompt = false;
		AConnection->Connected = true;
		AConnection->Tag = 1;
		List->Add(AConnection);
		return AConnection;
	}
	catch(Exception &e)
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TADOConnectionPool::GetLock(int Index, TList *List)
{
	bool bResult=false;
	try
	{
		bResult = ((TADOConnection *)List->Items[Index])->Tag==0;
		if(bResult)
			((TADOConnection *)List->Items[Index])->Tag = 1;
	}
	catch(Exception &e)
	{
		bResult=false;
	}
	return bResult;
}
//---------------------------------------------------------------------------
TADOConnection* __fastcall TADOConnectionPool::Lock()
{
	TADOConnection *aResult=NULL;
	if(WaitForSingleObject(FSemaphore, FTimeout) == WAIT_FAILED) return aResult;
	TList *List = FObjList->LockList();
	try
	{
		for(int i=0;i<List->Count;i++)
		{
			if(GetLock(i,List))
			{
				aResult = (TADOConnection *)List->Items[i];
			}
		}

		if(List->Count < FMaxCount)
		{
			aResult = CreateNewInstance(List);
		}
	}
	__finally
	{
		FObjList->UnlockList();
	}

	return aResult;
}
//---------------------------------------------------------------------------
void __fastcall TADOConnectionPool::Unlock(TADOConnection *Value)
{
	TList *List = FObjList->LockList();
	try
	{
		int iPos = List->IndexOf(Value);
		((TADOConnection *)List->Items[iPos])->Tag = 0;
		ReleaseSemaphore(FSemaphore, 1, NULL);
	}
	__finally
	{
		FObjList->UnlockList();
	}
}
//---------------------------------------------------------------------------
