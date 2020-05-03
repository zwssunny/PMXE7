// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Prjcndate.pas' rev: 20.00

#ifndef PrjcndateHPP
#define PrjcndateHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Prjcndate
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE StaticArray<System::Byte, 600> CnData;
extern PACKAGE System::UnicodeString __fastcall CnMonthOfDate(System::TDate Date);
extern PACKAGE System::UnicodeString __fastcall CnDayOfDate(System::TDate Date);
extern PACKAGE System::UnicodeString __fastcall CnDateOfDateStr(System::TDate Date);

}	/* namespace Prjcndate */
using namespace Prjcndate;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// PrjcndateHPP
