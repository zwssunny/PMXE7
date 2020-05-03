//---------------------------------------------------------------------------


#pragma hdrstop

#include "dmConn.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma resource "*.dfm"
TdmSQLConn *dmSQLConn;
//---------------------------------------------------------------------------
__fastcall TdmSQLConn::TdmSQLConn(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
