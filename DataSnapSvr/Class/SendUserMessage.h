//---------------------------------------------------------------------------

#ifndef SendUserMessageH
#define SendUserMessageH
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
//---------------------------------------------------------------------------
class TSendUserMessage : public TDMBaseServerClass
{
private:
	void  SendEmailMessage(String AEmailID);
	void  SendSMSMessage(String ASMSID);
	void  SendMemoMessage(String AMemoID);
public:
	__fastcall TSendUserMessage(TComponent* Owner);
   	void  SendUserMessage(int type,String AID);
};
#endif
