//---------------------------------------------------------------------------

#ifndef ContractProjectH
#define ContractProjectH
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
//---------------------------------------------------------------------------
class TContractProject : public TDMBaseServerClass
{
private:
	TADOQuery *AccQuery;
public:
	__fastcall TContractProject(TComponent* Owner);
	__fastcall ~TContractProject();
	TJSONArray*  GetContype();
	TJSONArray*  GetContlist(String userid,String ctypeid);
	TJSONArray*  GetContdata(String contid);
	TJSONArray*  GetProtype();
	TJSONArray*  GetProlist(String userid,String ProTypeid);
	TJSONArray*  GetProdata(String Projectid);
};
#endif
