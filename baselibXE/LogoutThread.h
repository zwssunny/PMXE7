//---------------------------------------------------------------------------

#ifndef LogoutThreadH
#define LogoutThreadH
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include "DSClientProxy.h"
//---------------------------------------------------------------------------
class TLogOutThread : public  TThread
{
  private:
  TLoginUserClient *FLoginUserClient;
  TSQLConnection *FDSConnection;
  TEvent *FEvent;
  public:
  virtual TLogOutThread(TSQLConnection *ADSConnection,TLoginUserClient *ALoginUserClient,TEvent *AEvent);
  void __fastcall Execute();
};
#endif
