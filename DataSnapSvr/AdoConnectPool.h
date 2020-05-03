//---------------------------------------------------------------------------

#ifndef AdoConnectPoolH
#define AdoConnectPoolH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TADOConnectionPool : public System::TObject
{
private:
	int FTimeout;
	int FMaxCount;
	String FConnStr;
	HANDLE FSemaphore;
	TThreadList *FObjList;
	TADOConnection* __fastcall CreateNewInstance(TList *List);
	bool __fastcall GetLock(int Index, TList *List);
public:
	__property int Timeout  = {read=FTimeout,write=FTimeout};
	__property int MaxCount = {read=FMaxCount};
	TADOConnection* __fastcall Lock();
	void __fastcall Unlock(TADOConnection *Value);
public:
	__fastcall TADOConnectionPool(TComponent* Owner, String ConnStr, int ACapicity=10);
	__fastcall ~TADOConnectionPool();
};
//---------------------------------------------------------------------------
#endif
