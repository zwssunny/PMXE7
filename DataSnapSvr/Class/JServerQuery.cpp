//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "JServerQuery.h"
#include "BaseFunc.h"
#include "SHConst.h"
//#include "ADODataSetStream.h"
#include "DBJson.hpp"
#include "FSServerContainer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TJServerQuery::TJServerQuery(TComponent* Owner):TDMBaseServerClass(Owner)
{
	FSysDbType = 1;
	FAccDbType = 1;
	TLoginUserRecord *curLoginUser = GetCurLoginUser();

	if(curLoginUser)
	{
		FSysDbType = curLoginUser->SysDbType;
		FAccDbType = curLoginUser->AccDbType;
		FUserCode  = curLoginUser->UserLoginCode;
		FUserIP    = curLoginUser->IP;
		FAcckBook  = curLoginUser->AccBookID;
	}
	m_Query = new TADOQuery(NULL);
	m_Query->ParamCheck = false;
	m_Query->EnableBCD = false;
	m_Query->CommandTimeout = 60;

	b_Query = new TADOQuery(NULL);
	b_Query->ParamCheck = false;
	b_Query->EnableBCD = false;
	b_Query->CommandTimeout = 60;

	LogQuery = new TADOQuery(NULL);
	LogQuery->ParamCheck = false;

	m_Connection = this->AccConnection;
	m_Query->Connection = m_Connection;

	m_BuildConn  = this->SysConnection;
	b_Query->Connection  = m_BuildConn;
	LogQuery->Connection = m_BuildConn;
}
//---------------------------------------------------------------------------
__fastcall TJServerQuery::~TJServerQuery()
{
	delete m_Query;
	delete b_Query;
	delete LogQuery;
}
//---------------------------------------------------------------------------
TJSONObject*  TJServerQuery::QueryOpen(String SQLText)
{
	return (TJSONObject*)(DataSetToJsonObject(SQLText)->Clone());
}
//---------------------------------------------------------------------------
TJSONObject*  TJServerQuery::QueryUpdate(TJSONObject *Json, String ClassCode)
{

}
//---------------------------------------------------------------------------
int  TJServerQuery::QueryExecSQL(String SQLText)
{
	int affectedrows = 0;
	TExecuteOptions eos;
	eos << eoExecuteNoRecords;
	m_Connection->Execute(SQLText, affectedrows, eos);
	return affectedrows;
}
//---------------------------------------------------------------------------
TJSONObject*  TJServerQuery::QuerySysOpen(String SQLText)
{
	return (TJSONObject*)(DataSetSysToJsonObject(SQLText)->Clone());
}
//---------------------------------------------------------------------------
int  TJServerQuery::QuerySysExecSQL(String SQLText)
{
	int affectedrows = 0;
	TExecuteOptions eos;
	eos << eoExecuteNoRecords;
	m_BuildConn->Execute(SQLText, affectedrows, eos);
	return affectedrows;
}
//---------------------------------------------------------------------------
TJSONObject*  TJServerQuery::SendFailMessage(int operate, String errormessage)
{
	TJSONObject *JSONObject = new TJSONObject();
	try
	{
		JSONObject->AddPair("Operate",operate);
		JSONObject->AddPair("Status","f");
		JSONObject->AddPair("ErrorMessage",errormessage);
		return JSONObject;
	}
	catch(Exception &e)
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------
TJSONObject*  TJServerQuery::SendErrorMessage(int errortype, int errorcode, String errormessage)
{
	TJSONObject *JSONObject = new TJSONObject();
	try
	{
		JSONObject->AddPair("ErrorType",errortype);
		JSONObject->AddPair("ErrorCode",errorcode);
		JSONObject->AddPair("ErrorMessage",errormessage);
		return JSONObject;
	}
	catch(Exception &e)
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------
void  TJServerQuery::WriteUserLog(int type, String Desc)
{
   DMServerContainer->NotifyWriteLog(FUserCode,FUserIP,FAcckBook,"100",type,Desc);
}
//---------------------------------------------------------------------------
