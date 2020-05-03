// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DispatchLib.pas' rev: 28.00 (Windows)

#ifndef DispatchlibHPP
#define DispatchlibHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.ActiveX.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <System.Win.ComObj.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dispatchlib
{
//-- type declarations -------------------------------------------------------
typedef int DISPATCHKIND;

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 DISPATCH_METHOD = System::Int8(0x1);
static const System::Int8 DISPATCH_PROPERTYGET = System::Int8(0x2);
static const System::Int8 DISPATCH_PROPERTYPUT = System::Int8(0x4);
static const System::Int8 DISPATCH_PROPERTYPUTREF = System::Int8(0x8);
extern DELPHI_PACKAGE System::OleVariant __fastcall DispatchInvoke(_di_IDispatch obj, System::UnicodeString DispatchName, int InvokeMethod, int ParamCount, System::OleVariant &ParamArray);
extern DELPHI_PACKAGE System::OleVariant __fastcall DispatchInvokeEx(_di_IDispatch obj, int DispatchId, int InvokeMethod, int ParamCount, System::OleVariant &ParamArray);
}	/* namespace Dispatchlib */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DISPATCHLIB)
using namespace Dispatchlib;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DispatchlibHPP
