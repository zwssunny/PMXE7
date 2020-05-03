// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ModeInter.pas' rev: 28.00 (Windows)

#ifndef ModeinterHPP
#define ModeinterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Modeinter
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __stdcall (*fnSetThreadMode)(int nMode);
extern DELPHI_PACKAGE int __stdcall (*fnSetModemType)(int ComNo, int modemType);
extern DELPHI_PACKAGE int __stdcall (*fnGetModemType)(int ComNo);
extern DELPHI_PACKAGE int __stdcall (*fnInitModem)(int comx);
extern DELPHI_PACKAGE int __stdcall (*fnSendMsg)(int comx, System::WideChar * receivephone, System::WideChar * sendmsg);
extern DELPHI_PACKAGE int __stdcall (*fnGetStatus)(int nPortNo);
extern DELPHI_PACKAGE int __stdcall (*fnReadMsgEx)(int comx, System::WideChar * szHeader, System::WideChar * receivemsg);
extern DELPHI_PACKAGE int __stdcall (*fnGetSndCount)(int nPortNo);
extern DELPHI_PACKAGE int __stdcall (*fnGetRecCount)(int nPortNo);
extern DELPHI_PACKAGE int __stdcall (*fnCloseModem)(int comx);
extern DELPHI_PACKAGE bool __fastcall LoadModeDll(void);
}	/* namespace Modeinter */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MODEINTER)
using namespace Modeinter;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ModeinterHPP
