//---------------------------------------------------------------------------

#ifndef LocateQueueProcH
#define LocateQueueProcH
#include "Classes.hpp"
#include "SysUtils.hpp"
//---------------------------------------------------------------------------
//用于多线程处理日志记录
typedef void __fastcall (__closure *TLocateRecord)(String Key,String Value);
class TLocateQueueProc : public TCppInterfacedObject<TThreadProcedure>
{
  private:
	TLocateRecord FLocateRecord;
	String FKey;
	String FValue;
  public:
	virtual TLocateQueueProc(TLocateRecord& ALocateRecord,String AKey, String AValue);
	__fastcall ~TLocateQueueProc() {}
	virtual void __fastcall Invoke();
};
#endif                                 
