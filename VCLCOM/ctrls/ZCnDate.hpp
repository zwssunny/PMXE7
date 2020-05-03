// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ZCnDate.pas' rev: 27.00 (Windows)

#ifndef ZcndateHPP
#define ZcndateHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Zcndate
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const System::Word START_YEAR = System::Word(0x76d);
static const System::Word END_YEAR = System::Word(0x802);
extern DELPHI_PACKAGE System::StaticArray<System::Byte, 600> CnData;
extern DELPHI_PACKAGE System::StaticArray<System::Byte, 1800> gLunarHolDay;
extern DELPHI_PACKAGE System::UnicodeString __fastcall CnMonthOfDate(System::TDate Date);
extern DELPHI_PACKAGE System::UnicodeString __fastcall CnDayOfDate(System::TDate Date);
extern DELPHI_PACKAGE System::UnicodeString __fastcall CnDateOfDateStr(System::TDate Date);
extern DELPHI_PACKAGE System::UnicodeString __fastcall Holiday(System::TDateTime Date);
extern DELPHI_PACKAGE System::UnicodeString __fastcall CnDayOfDateJr(System::TDateTime Date);
extern DELPHI_PACKAGE System::UnicodeString __fastcall OtherHoliday(System::TDateTime Date);
extern DELPHI_PACKAGE System::Word __fastcall l_GetLunarHolDay(System::Word iYear, System::Word iMonth, System::Word iDay);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetLunarHolDay(System::TDateTime InDate)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetLunarHolDay(System::Word iYear, System::Word iMonth, System::Word iDay)/* overload */;
}	/* namespace Zcndate */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ZCNDATE)
using namespace Zcndate;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ZcndateHPP
