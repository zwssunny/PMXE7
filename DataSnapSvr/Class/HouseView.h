//---------------------------------------------------------------------------

#ifndef HouseViewH
#define HouseViewH
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
//---------------------------------------------------------------------------
class THouseView : public TDMBaseServerClass
{
 private:	// User declarations
		TADOQuery *m_Query;
		String AppPath;
 public:		// User declarations
		__fastcall THouseView(TComponent* Owner);
		__fastcall ~THouseView();
		TStream* GetHouseViewStream(String AKeyID);
		bool UpdateHouseViewFile(String AKeyID,String AFileName,TStream* AStream);
};
#endif
