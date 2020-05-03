//---------------------------------------------------------------------------

#ifndef SendMemoMessageThreadH
#define SendMemoMessageThreadH
//---------------------------------------------------------------------------
#include "Classes.hpp"
#include "SysUtils.hpp"
#include "MessageManage.h"
//---------------------------------------------------------------------------
class  TSendMemoMessageThread :public TThread
{
private:
	TMessageManage * FFMessageManage;
	String FID;
	String FTitle;
	TADOQuery *AccQuery;
	TADOConnection *m_Connection;

protected:
public:
	virtual TSendMemoMessageThread(TADOConnection *AConnection,String AID);
	void __fastcall Execute();
};
#endif
