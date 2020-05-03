// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'uSystemLibrary.pas' rev: 28.00 (Windows)

#ifndef UsystemlibraryHPP
#define UsystemlibraryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.TypInfo.hpp>	// Pascal unit
#include <atScript.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Usystemlibrary
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TatSystemLibrary;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TatSystemLibrary : public Atscript::TatScripterLibrary
{
	typedef Atscript::TatScripterLibrary inherited;
	
private:
	void __fastcall VarIsNullProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall RoundProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TruncProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall CopyProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DeleteProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall InsertProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall PosProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall LengthProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IncProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DecProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall UpperCaseProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall LowerCaseProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall CompareStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall CompareTextProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall AnsiUpperCaseProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall AnsiLowerCaseProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall AnsiCompareStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall AnsiCompareTextProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TrimProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TrimLeftProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TrimRightProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IsValidIdentProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IntToStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IntToHexProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall StrToIntProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall StrToIntDefProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall FloatToStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall FormatFloatProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall StrToFloatProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall EncodeDateProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall EncodeTimeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DecodeDateProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DecodeTimeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DayOfWeekProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DateProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TimeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall NowProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IncMonthProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IsLeapYearProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DateToStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TimeToStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall DateTimeToStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall StrToDateProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall StrToTimeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall StrToDateTimeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall FormatDateTimeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall BeepProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall FormatProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall RandomProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall MachineProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall ScripterProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall ShowMessageProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall InputQueryProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall RaiseProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall CreateOleObjectProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetActiveOleObjectProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall VarToStrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall HighProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall LowProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall VarArrayHighBoundProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall VarArrayLowBoundProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall VarArrayCreateProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetLastExceptionMessageProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetLastExceptionHelpContextProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall GetLastExceptionClassNameProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TObjectCreateProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall TObjectFreeProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall AssignedProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall InterpretProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall SetOfProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall CosProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall SinProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall AbsProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall ArctanProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall ChDirProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall ChrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall ExpProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall FracProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall IntProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall LnProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall OddProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall OrdProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall SqrProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall SqrtProc(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __AssignFile(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __Reset(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __Rewrite(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __Append(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __CloseFile(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __Write(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __WriteLn(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __ReadLn(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __EOF(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __FilePos(Atscript::TatVirtualMachine* AMachine);
	void __fastcall __FileSize(Atscript::TatVirtualMachine* AMachine);
	
public:
	__classmethod virtual System::UnicodeString __fastcall LibraryName();
	virtual void __fastcall Init(void);
public:
	/* TatScripterLibrary.Create */ inline __fastcall virtual TatSystemLibrary(Atscript::TatCustomScripter* AScripter) : Atscript::TatScripterLibrary(AScripter) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TatSystemLibrary(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Usystemlibrary */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_USYSTEMLIBRARY)
using namespace Usystemlibrary;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UsystemlibraryHPP
