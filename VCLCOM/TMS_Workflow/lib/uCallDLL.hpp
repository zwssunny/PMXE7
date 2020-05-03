// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'uCallDLL.pas' rev: 28.00 (Windows)

#ifndef UcalldllHPP
#define UcalldllHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Ucalldll
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TCallingConvention : unsigned char { ccStdCall, ccRegister, ccPascal, ccCDecl, ccSafeCall };

typedef System::DynamicArray<System::TVarRec> openarray;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Variant __fastcall CallDllFunction(System::UnicodeString AFile, System::UnicodeString AFunction, openarray AArgs, openarray AArgTypes, int AReturnType = 0x0, TCallingConvention ACalling = (TCallingConvention)(0x0));
}	/* namespace Ucalldll */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_UCALLDLL)
using namespace Ucalldll;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UcalldllHPP
