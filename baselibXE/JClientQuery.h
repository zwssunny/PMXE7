// ---------------------------------------------------------------------------

#ifndef JClientQueryH
#define JClientQueryH
#include <Classes.hpp>
#include <adodb.hpp>
#include <db.hpp>
#include <stdio.h>
#include "JClientDataset.h"

#ifdef VER190
#include <WideStrings.hpp>
#endif
// ---------------------------------------------------------------------------
class PACKAGE TJServerQueryClient;
class PACKAGE TJClientDataSet;
class PACKAGE TJClientQuery : public TADODataSet
{
	private:
		#ifdef VER190
		TWideStrings *FSQL;
		TWideStrings* __fastcall GetSQL(void);
		void __fastcall SetSQL(TWideStrings* Value);
		#else
		TStringList* FSQL;
		TStringList* __fastcall GetSQL(void);
		void __fastcall SetSQL(TStringList* Value);
		#endif
		int FRowsAffected;
		TClientBroker *FClientBroker;
//		HWND m_Parent;
//		HWND m_Handle;
		String m_FileName;
//		bool ClientCommConnectState;
		int QueryOperateStatus;
		String QueryErrorMessage;
		TJServerQueryClient *ServerQuery;
		//void __fastcall WndProc(TMessage &Msg);
		/*********************************************************************
		// 传入JSONObject格式
		//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
		//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
		// Status:}
		**********************************************************************/
		void __fastcall RecvOpenMessage(TJSONObject *Json);
		/*********************************************************************
		// 传入JSONObject格式
		//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
		//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
		// Status:}
		**********************************************************************/
		void __fastcall RecvUpdateMessage(TJSONObject *Json);
		/*********************************************************************
		// 传入JSONObject格式
		// {Status:}
		**********************************************************************/
		void __fastcall RecvDeleteMessage(TJSONObject *Json);
		/*********************************************************************
		// 传入JSONObject格式
		// {Status:,RowsAffected:}
		**********************************************************************/
		void __fastcall RecvExecSQLMessage(TJSONObject *Json);
		void __fastcall CheckResultStatus(int status);
		TADODataSet* __fastcall GetDataSet();
		int __fastcall GetSysDbType();
		int __fastcall GetAccDbType();
		int __fastcall get_CurRecNo();
	protected:
		void __fastcall QueryChanged(TObject* Sender);
	public:
		__fastcall TJClientQuery(TComponent* AOwner, TClientBroker *FBroker, TJClientDataSet *AClientDataSet);
		__fastcall TJClientQuery(TClientBroker *FBroker);
		__fastcall virtual ~TJClientQuery();
		void __fastcall Open();
		int __fastcall ExecSQL();
		void __fastcall SysOpen();
		int __fastcall SysExecSQL();
	public:
		__property int RowsAffected = {read = FRowsAffected, nodefault};
//		__property HWND Handle = {read = m_Handle};
//		__property HWND Parent = {read = m_Parent};
		__property int CurRecNo = {read = get_CurRecNo};
		__property TADODataSet* DataSet = {read = GetDataSet};
		__property int SysDbType = {read = GetSysDbType};
		__property int AccDbType = {read = GetAccDbType};
	__published:
		__property CommandTimeout = { default = 30};
		__property DataSource;
		__property EnableBCD = { default = 1};
		__property ParamCheck = { default = 1};
		__property Parameters;
		__property Prepared = { default = 0};
		#ifdef VER190
		__property TWideStrings* SQL = {read = GetSQL, write = SetSQL};
		#else
		__property TStringList* SQL = {read = GetSQL, write = SetSQL};
		#endif
};
#endif
