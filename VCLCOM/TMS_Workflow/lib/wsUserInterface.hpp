// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsUserInterface.pas' rev: 28.00 (Windows)

#ifndef WsuserinterfaceHPP
#define WsuserinterfaceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsuserinterface
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWorkflowUserInterface;
class PASCALIMPLEMENTATION TWorkflowUserInterface : public Wsmain::TCustomWorkflowUserInterface
{
	typedef Wsmain::TCustomWorkflowUserInterface inherited;
	
public:
	virtual void __fastcall ShowUserTasksDlg(System::UnicodeString AUserKey, Wsmain::TWorkflowFormMode AFormMode = (Wsmain::TWorkflowFormMode)(0x0));
	virtual void __fastcall ShowUsersTasksDlg(System::UnicodeString AUserKeys, Wsmain::TWorkflowFormMode AFormMode = (Wsmain::TWorkflowFormMode)(0x0));
	virtual void __fastcall ShowWorkInsTasksDlg(System::UnicodeString AWorkInsKey, Wsmain::TWorkflowFormMode AFormMode = (Wsmain::TWorkflowFormMode)(0x0));
	virtual void __fastcall ShowWorkflowDefinitionsDlg(void);
	virtual void __fastcall EditWorkflowDefinition(Wsclasses::TWorkflowDefinition* AWorkDef);
	virtual void __fastcall EditWorkflowInstance(Wsclasses::TWorkflowInstance* AWorkIns);
public:
	/* TCustomWorkflowUserInterface.Create */ inline __fastcall TWorkflowUserInterface(System::Classes::TComponent* AOwner, Wsmain::TWorkflowStudio* AWorkflowStudio) : Wsmain::TCustomWorkflowUserInterface(AOwner, AWorkflowStudio) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TWorkflowUserInterface(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wsuserinterface */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSUSERINTERFACE)
using namespace Wsuserinterface;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsuserinterfaceHPP
