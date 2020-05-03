// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "JClientQuery.h"
#include "BaseFunc.h"
#include "MessageDef.h"
#include "SHConst.h"
#include "DSClientProxy.h"
#include "ClientBroker.h"
#include "ADODataSetStream.h"
#include "fsScreenCursor.h"
#include "DBJson.hpp"

#define _TimeOuts 60  //秒
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
__fastcall TJClientQuery::TJClientQuery(TComponent* AOwner, TClientBroker *FBroker, TJClientDataSet *AClientDataSet)
	: TADODataSet(AOwner)
{
	FClientBroker = FBroker;
	QueryErrorMessage = "";
	QueryOperateStatus = 0;
//	m_Handle = AllocateHWnd(WndProc); // Local Handle
	EnableBCD = false;
#ifdef VER190
	FSQL = new TWideStringList();
	((TWideStringList*)FSQL)->OnChange = QueryChanged;
#else
	FSQL = new TStringList();
	((TStringList*)FSQL)->OnChange = QueryChanged;
#endif
	ServerQuery = new TJServerQueryClient(FClientBroker->DBXConnection,false);
//	ClientCommConnectState = true;
}
// ---------------------------------------------------------------------------
__fastcall TJClientQuery::TJClientQuery(TClientBroker *FBroker)
	: TADODataSet(NULL)
{
 	FClientBroker = FBroker;
	QueryErrorMessage = "";
	QueryOperateStatus = 0;
//	m_Handle = AllocateHWnd(WndProc); // Local Handle
	EnableBCD = false;
#ifdef VER190
	FSQL = new TWideStringList();
	((TWideStringList*)FSQL)->OnChange = QueryChanged;
#else
	FSQL = new TStringList();
	((TStringList*)FSQL)->OnChange = QueryChanged;
#endif
	ServerQuery = new TJServerQueryClient(FClientBroker->DBXConnection,false);
//	ClientCommConnectState = true;
}
// ---------------------------------------------------------------------------
__fastcall TJClientQuery::~TJClientQuery()
{
	delete FSQL;

	if(ServerQuery)
		delete ServerQuery;

//	if(m_Handle != 0)
//		DeallocateHWnd(m_Handle);

	Close();
	if(FileExists(m_FileName))
		DeleteFile(m_FileName);
}
// ---------------------------------------------------------------------------
#ifdef VER190
TWideStrings* __fastcall TJClientQuery::GetSQL(void)
{
	return FSQL;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::SetSQL(TWideStrings* Value)
{
	FSQL->Assign(Value);
}
// ---------------------------------------------------------------------------
#else
TStringList* __fastcall TJClientQuery::GetSQL(void)
{
	return FSQL;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::SetSQL(TStringList* Value)
{
	FSQL->Assign(Value);
}
#endif
// ---------------------------------------------------------------------------
//void __fastcall TJClientQuery::WndProc(TMessage &Msg)
//{
//	String s;
//	switch (Msg.Msg)
//	{
//		case WM_CLIENTCOMM_CONNETSTATE:
//			ClientCommConnectState = Msg.WParam != 0;
//			break;
//		default:
//			Msg.Result = DefWindowProc(m_Handle, Msg.Msg, Msg.WParam, Msg.LParam);
//	}
//}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::RecvOpenMessage(TJSONObject *Json)
{
	try
	{
		if(Json->Size() > 0)
		{
			TJSONObject *MstJson = NULL;
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus == "s")
			{
				MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(this,pso);
				QueryOperateStatus = 1;
			}
			else
			{
				QueryErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				QueryOperateStatus = 2;
      }
		}
	}
	catch (Exception &e)
	{
		QueryErrorMessage  = "打开数据集失败,错误:" + e.Message;
		QueryOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::RecvUpdateMessage(TJSONObject *Json)
{
	TADOQuery *FQuery;
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			TJSONObject *MstJson = NULL;
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus == "s")
			{
				FQuery = new TADOQuery(NULL);
				FQuery->EnableBCD = false;
				MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(this,pso);
				if(this->State != dsBrowse)
				{
					for (int i = 0; i < FQuery->FieldCount; i++)
					{
						if(this->Fields->Fields[i]->ReadOnly)
							this->Fields->Fields[i]->ReadOnly = false;
						this->FieldValues[FQuery->Fields->Fields[i]->Name] = FQuery->FieldValues[FQuery->Fields->Fields[i]->Name];
					}
				}
				QueryOperateStatus = 1;
				delete FQuery;
			}
			else
			{
				QueryErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				QueryOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		QueryErrorMessage  = "更新数据失败,错误:" + e.Message;
		QueryOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::RecvDeleteMessage(TJSONObject *Json)
{
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus == "s")
				QueryOperateStatus = 1;
			else
			{
				QueryErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				QueryOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		QueryErrorMessage  = "删除数据失败,错误:" + e.Message;
		QueryOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::RecvExecSQLMessage(TJSONObject *Json)
{
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus == "s")
			{
				QueryOperateStatus = 1;
				FRowsAffected = Json->Get("RowsAffected")->JsonValue->Value().ToInt();
			}
			else
			{
				FRowsAffected      = 0;
				QueryErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				QueryOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		QueryErrorMessage  = "执行命令失败,错误:" + e.Message;
		QueryOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::Open()
{
	if(CommandType == cmdText)
	{
		TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
		try
		{
			QueryOperateStatus = 0;
			TJSONObject *JSONObject = ServerQuery->QueryOpen(this->SQL->Text);
			TJSONObject *MstJson = (TJSONObject*)JSONObject->Get("Master")->JsonValue;
			_di_ISuperObject pso = SO(MstJson->ToString());
			TTableJson::JsonToDataSet(this,pso);
		}
		__finally
		{
			delete ScreenCursor;
		}
	}
	else
	{
		if(this->Active == false)
			TCustomADODataSet::Open();
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::SysOpen()
{
	if(CommandType == cmdText)
	{
		TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
		try
		{
			QueryOperateStatus = 0;
			TJSONObject *JSONObject = ServerQuery->QuerySysOpen(this->SQL->Text);
			TJSONObject *MstJson = (TJSONObject*)JSONObject->Get("Master")->JsonValue;
			_di_ISuperObject pso = SO(MstJson->ToString());
			TTableJson::JsonToDataSet(this,pso);
		}
	  __finally
		{
			delete ScreenCursor;
	  }
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::QueryChanged(TObject* Sender)
{
	if(!ComponentState.Contains(csLoading))
		Close();
	CommandType = cmdText;
	CommandText = FSQL->Text;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientQuery::ExecSQL()
{
	int retint=0;
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		retint = ServerQuery->QueryExecSQL(this->SQL->Text);
	}
	__finally
	{
		delete ScreenCursor;
	}
	return retint;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientQuery::SysExecSQL()
{
	int retint=0;
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		retint = ServerQuery->QuerySysExecSQL(this->SQL->Text);
	}
	__finally
	{
		delete ScreenCursor;
	}
	return retint;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientQuery::CheckResultStatus(int status)
{
	String errmsg = QueryErrorMessage;
	QueryErrorMessage = "";
	if(status == 2)
	{
		if(errmsg > "")
			throw Exception(errmsg);
	}
	else if(status == 3)
		throw Exception("系统操作超时.");
}
// ---------------------------------------------------------------------------
TADODataSet* __fastcall TJClientQuery::GetDataSet()
{
	return (TADODataSet*)(this);
}
// ---------------------------------------------------------------------------
int __fastcall TJClientQuery::get_CurRecNo()
{
	return this->RecNo;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientQuery::GetSysDbType()
{
	return FClientBroker->SysDbType;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientQuery::GetAccDbType()
{
	return FClientBroker->AccDbType;
}
// ---------------------------------------------------------------------------
