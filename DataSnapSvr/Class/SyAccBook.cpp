//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SyAccBook.h"
#include "FSServerContainer.h"
#include "XMLData.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TSyAccBook::TSyAccBook(TComponent* Owner)
	:TDMBaseServerClass(Owner)
{
	b_Query = new TADOQuery(NULL);
	b_Query->ParamCheck = false;
	b_Query->EnableBCD  = false;
	b_Query->Connection = SysConnection;
}
//---------------------------------------------------------------------------
__fastcall TSyAccBook::~TSyAccBook()
{
	delete b_Query;
}
//---------------------------------------------------------------------------
TStream *  TSyAccBook::GetAllAccBook()
{
	b_Query->Close();
	b_Query->SQL->Text = "select * from SyAccBook" ;
	b_Query->Open();
	return AdoDataSetToCDStream(b_Query);
}
//---------------------------------------------------------------------------
TStream *  TSyAccBook::GetActiveAccBook()
{
	b_Query->Close();
	b_Query->SQL->Text = "select * from SyAccBook where SyAccBookStatue=1" ;
	b_Query->Open();
	return AdoDataSetToCDStream(b_Query);
}
//---------------------------------------------------------------------------
TJSONObject*  TSyAccBook::GetAllAccBookJO()
{
	return DataSetSysToJsonObject("select * from SyAccBook");
}
//---------------------------------------------------------------------------
TJSONObject*  TSyAccBook::GetActiveAccBookJO()
{
	return DataSetSysToJsonObject("select * from SyAccBook where SyAccBookStatue=1");
}
//---------------------------------------------------------------------------
