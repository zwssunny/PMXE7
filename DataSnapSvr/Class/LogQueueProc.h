//---------------------------------------------------------------------------

#ifndef LogQueueProcH
#define LogQueueProcH
#include "Classes.hpp"
#include "SysUtils.hpp"
//---------------------------------------------------------------------------
//用于多线程处理日志记录
typedef void __fastcall (__closure *TWriteUserLog)(String UserID, String IPAddress,String AcckBook,
	String ClassCode, int type, String Desc);
class TLogQueueProc : public  TThread
{
  private:
	TWriteUserLog FWriteUserLog;
	String FUserID;
	String FIPAddress;
	String FAcckBook ;
	int Ftype;
	String FDesc;
	String FClassCode;
  public:
	virtual TLogQueueProc(TWriteUserLog& AWriteUserLog,String AUserID, String AIPAddress,
						 String AAcckBook,String AClassCode,int Atype, String ADesc);
	void __fastcall Execute();
};
#endif
