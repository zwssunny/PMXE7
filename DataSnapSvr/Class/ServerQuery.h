//---------------------------------------------------------------------------

#ifndef ServerQueryH
#define ServerQueryH
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
#include "MsgStream.h"
//---------------------------------------------------------------------------
class TServerQuery : public TDMBaseServerClass
{
private:
	int FSysDbType;
	int FAccDbType;
	String FUserCode;
	String FUserIP;
	String FAcckBook;
	TADOQuery *m_Query;
	TADOQuery *b_Query;
	TADOQuery *LogQuery;
	TADOConnection *m_Connection;
	TADOConnection *m_BuildConn;
	void  WriteUserLog(int type, String Desc);
	TStream*  SendFailMessage(int operate, String errormessage);
	TStream*  SendErrorMessage(int errortype, int errorcode, String errormessage);
public:
	__fastcall TServerQuery(TComponent* Owner);
	__fastcall ~TServerQuery();
	TStream*  QueryOpen(String SQLText);
	//	TStream*  QueryUpdate(TStream *Stream);
	//	TStream*  QueryDelete(TStream *Stream);
	int  QueryExecSQL(String SQLText);
	int  ExecSQL(String SQLText,TParams* Parameters);
	// Ö´ÐÐÏµÍ³¿â
	TStream*  QuerySysOpen(String SQLText);
	//	TStream*  QuerySysUpdate(TStream *Stream);
	//	TStream*  QuerySysDelete(TStream *Stream);
	int  QuerySysExecSQL(String SQLText);
	int  SysExecSQL(String SQLText,TParams* Parameters);

};
#endif
