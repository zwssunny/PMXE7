//---------------------------------------------------------------------------
#ifndef SyAccBookH
#define SyAccBookH
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
//---------------------------------------------------------------------------
class TSyAccBook : public TDMBaseServerClass
{
private:
	 TADOQuery *b_Query;
public:
	__fastcall TSyAccBook(TComponent* Owner);
	__fastcall ~TSyAccBook();
public:
	TStream *  GetAllAccBook();
	TStream *  GetActiveAccBook();

	TJSONObject*  GetAllAccBookJO();
	TJSONObject*  GetActiveAccBookJO();
};
#endif
