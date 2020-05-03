//----------------------------------------------------------------------------

#ifndef ServerControlMethodsH
#define ServerControlMethodsH
//----------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <DataSnap.DSServer.hpp>
//----------------------------------------------------------------------------
class DECLSPEC_DRTTI TServerControlMethods : public TComponent
{
private:	// User declarations
public:		// User declarations
   TJSONArray* GetServerList();
   TJSONObject * GetServerInfo(String ServerName);
   int GetServerStatus(String ServerName);
   bool StartServer(String ServerName);
   bool StopServer(String ServerName);
   bool RegServer(String ServerName);
   bool UnregServer(String ServerName);
   bool RebootComputer();
   bool ShutdownComputer();
};
#endif

