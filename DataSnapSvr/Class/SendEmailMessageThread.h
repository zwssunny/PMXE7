//---------------------------------------------------------------------------

#ifndef SendEmailMessageThreadH
#define SendEmailMessageThreadH
#include "Classes.hpp"
#include "SysUtils.hpp"
#include "MessageManage.h"
//---------------------------------------------------------------------------
class  TSendEmailMessageThread :public TThread
{
private:
	TMessageManage * FFMessageManage;
	String FEmailID;
	String EmailTitle;
	TADOQuery *AccQuery;
	TADOConnection *m_Connection;

protected:
public:
	virtual TSendEmailMessageThread(TADOConnection *AConnection,String AEmailID);
	void __fastcall Execute();
};
#endif
