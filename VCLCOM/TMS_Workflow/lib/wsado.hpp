// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsADO.pas' rev: 28.00 (Windows)

#ifndef WsadoHPP
#define WsadoHPP

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
#include <Data.Win.ADODB.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsado
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWorkflowADODB;
class PASCALIMPLEMENTATION TWorkflowADODB : public Wsdb::TCustomWorkflowDB
{
	typedef Wsdb::TCustomWorkflowDB inherited;
	
private:
	Data::Win::Adodb::TADOConnection* FConnection;
	void __fastcall SetConnection(Data::Win::Adodb::TADOConnection* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual Data::Db::TDataSet* __fastcall DoCreateQuery(System::UnicodeString SQL);
	virtual void __fastcall DoExecuteQuery(Data::Db::TDataSet* Dataset);
	virtual void __fastcall DoAssignSQLParams(Data::Db::TDataSet* Dataset, Data::Db::TParams* AParams);
	virtual System::UnicodeString __fastcall BlobFieldToString(Data::Db::TField* AField);
	
public:
	__fastcall virtual TWorkflowADODB(System::Classes::TComponent* AOwner);
	
__published:
	__property Data::Win::Adodb::TADOConnection* Connection = {read=FConnection, write=SetConnection};
public:
	/* TCustomWorkflowDB.Destroy */ inline __fastcall virtual ~TWorkflowADODB(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Wsado */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSADO)
using namespace Wsado;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsadoHPP
