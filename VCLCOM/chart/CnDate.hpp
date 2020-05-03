// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'CnDate.pas' rev: 5.00

#ifndef CnDateHPP
#define CnDateHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cndate
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Byte CnData[600];
extern PACKAGE AnsiString __fastcall CnMonthOfDate(TDate Date);
extern PACKAGE AnsiString __fastcall CnDayOfDate(TDate Date);
extern PACKAGE AnsiString __fastcall CnDateOfDateStr(TDate Date);

}	/* namespace Cndate */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Cndate;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// CnDate
