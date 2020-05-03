//---------------------------------------------------------------------------

#ifndef SendSMSMessageThreadH
#define SendSMSMessageThreadH
#include "Classes.hpp"
#include "SysUtils.hpp"
#include "MessageManage.h"
//---------------------------------------------------------------------------
class  TSendSMSMessageThread :public TThread
{
private:
	TMessageManage * FFMessageManage;
	String FID;
	String FTitle;
	TADOQuery *AccQuery;
	TADOConnection *m_Connection;

protected:
public:
	virtual TSendSMSMessageThread(TADOConnection *AConnection,String AID);
	void __fastcall Execute();
};
#endif
