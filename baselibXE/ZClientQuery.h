// ---------------------------------------------------------------------------

#ifndef ZClientQueryH
#define ZClientQueryH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include "MsgStream.h"
#include "ClientBroker.h"
#include "DataSnapClientDataSet.h"
// ---------------------------------------------------------------------------
class PACKAGE TServerQueryClient;
class PACKAGE TZClientDataSet;
class PACKAGE TZClientQuery : public TDataSnapClientDataSet
{
private:
	TStringList* FSQL;
	TStringList* __fastcall GetSQL(void);
	void __fastcall SetSQL(TStringList* Value);
	int FRowsAffected;
	TClientBroker *FClientBroker;
	TServerQueryClient *ServerQuery;
	TDataSnapClientDataSet* __fastcall GetDataSet();
	int __fastcall GetSysDbType();
	int __fastcall GetAccDbType();
	int __fastcall get_CurRecNo();

protected:
	void __fastcall QueryChanged(TObject* Sender);

public:
	__fastcall TZClientQuery(TComponent* AOwner,TClientBroker *FBroker);
	__fastcall virtual ~TZClientQuery();
	void __fastcall Open();
	int __fastcall ExecSQL();
	int __fastcall ExecSQLByParams();
	void __fastcall SysOpen();
	int __fastcall SysExecSQL();
	int __fastcall SysExecSQLByParams();
	__property int RowsAffected = {read = FRowsAffected, nodefault};
	__property int CurRecNo = {read = get_CurRecNo};
	__property TCustomClientDataSet* DataSet = {read = GetDataSet};
	__property int SysDbType = {read = GetSysDbType};
	__property int AccDbType = {read = GetAccDbType};

__published:
	__property Params;
	__property TStringList* SQL = {read = GetSQL, write = SetSQL};
};
#endif
