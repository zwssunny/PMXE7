//---------------------------------------------------------------------------

#ifndef dmConnH
#define dmConnH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXDataSnap.hpp>
#include <Data.SqlExpr.hpp>
#include <IPPeerClient.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class TdmSQLConn : public TDataModule
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection2;
	TClientDataSet *ClientDataSet1;
private:	// User declarations
public:		// User declarations
	__fastcall TdmSQLConn(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmSQLConn *dmSQLConn;
//---------------------------------------------------------------------------
#endif
