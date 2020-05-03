//---------------------------------------------------------------------------

#ifndef LogQueueProcH
#define LogQueueProcH
#include "Classes.hpp"
#include "SysUtils.hpp"
//---------------------------------------------------------------------------
//用于多线程处理日志记录
typedef void __fastcall (__closure *TWriteUserLog)(String Msg,TDateTime dtime);
class TLogQueueProc : public TCppInterfacedObject<TThreadProcedure>
{
  private:
	TWriteUserLog FWriteUserLog;
	String FIPAddress;
	TDateTime Fdtime;
	String FMsg;
  public:
	virtual TLogQueueProc(TWriteUserLog& AWriteUserLog,String AIPAddress, TDateTime Adtime,String AMsg);
	__fastcall ~TLogQueueProc() {}
	virtual void __fastcall Invoke();
};
#endif                                 c
