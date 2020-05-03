//---------------------------------------------------------------------------

#ifndef CheckServiceH
#define CheckServiceH
#include "Classes.hpp"
#include "SysUtils.hpp"
#include <DSServer.hpp>
//---------------------------------------------------------------------------
class TCheckServiceProc : public  TThread
{
private:
	TDSServer *FServer;
	TJSONArray *FServerList;
	String FComputerIP;
	int SIndex;
public:
	virtual TCheckServiceProc(TDSServer *AServer,TJSONArray *AServerList,String AComputerIP,int AIndex);
	void __fastcall Execute();
};
#endif
