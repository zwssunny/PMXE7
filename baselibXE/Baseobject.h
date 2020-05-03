//---------------------------------------------------------------------------

#ifndef BaseobjectH
#define BaseobjectH
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Data.DBXJSON.hpp>	// Pascal unit
#include <Data.DBXJSONReflect.hpp>	// Pascal unit
//---------------------------------------------------------------------------
class  TBaseObject  :public TPersistent
{

public:
   __fastcall  TBaseObject();
   virtual void __fastcall  RegisterConverter(TJSONMarshal *m);
   virtual void __fastcall  RegisterReverter(TJSONUnMarshal *unm);
};
#endif
