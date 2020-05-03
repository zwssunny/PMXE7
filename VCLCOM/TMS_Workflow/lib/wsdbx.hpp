// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsDbx.pas' rev: 28.00 (Windows)

#ifndef WsdbxHPP
#define WsdbxHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <wsDB.hpp>	// Pascal unit
#include <Data.DB.hpp>	// Pascal unit
#include <Data.SqlExpr.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsdbx
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TDBXDBType : unsigned char { dbxAny, dbxOracle, dbxSQLServer, dbxFirebird };

class DELPHICLASS TWorkflowDBXDB;
class PASCALIMPLEMENTATION TWorkflowDBXDB : public Wsdb::TCustomWorkflowDB
{
	typedef Wsdb::TCustomWorkflowDB inherited;
	
private:
	Data::Sqlexpr::TSQLConnection* FConnection;
	TDBXDBType FDBType;
	void __fastcall SetConnection(Data::Sqlexpr::TSQLConnection* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual Data::Db::TDataSet* __fastcall DoCreateQuery(System::UnicodeString SQL);
	virtual void __fastcall DoExecuteQuery(Data::Db::TDataSet* Dataset);
	virtual void __fastcall DoAssignSQLParams(Data::Db::TDataSet* Dataset, Data::Db::TParams* AParams);
	
public:
	__fastcall virtual TWorkflowDBXDB(System::Classes::TComponent* AOwner);
	
__published:
	__property Data::Sqlexpr::TSQLConnection* SQLConnection = {read=FConnection, write=SetConnection};
	__property TDBXDBType DBType = {read=FDBType, write=FDBType, nodefault};
public:
	/* TCustomWorkflowDB.Destroy */ inline __fastcall virtual ~TWorkflowDBXDB(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Wsdbx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSDBX)
using namespace Wsdbx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsdbxHPP
