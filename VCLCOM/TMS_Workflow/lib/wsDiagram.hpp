// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsDiagram.pas' rev: 28.00 (Windows)

#ifndef WsdiagramHPP
#define WsdiagramHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsdiagram
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWorkflowDiagram;
class PASCALIMPLEMENTATION TWorkflowDiagram : public Wsclasses::TCustomWorkflowDiagram
{
	typedef Wsclasses::TCustomWorkflowDiagram inherited;
	
protected:
	virtual void __fastcall DoSaveState(void);
	virtual Atdiagram::TatDiagramClass __fastcall DiagramStreamClass(void);
	virtual void __fastcall DoBeforeExecuteNode(Livediagram::TCustomLiveBlock* ANode);
	virtual void __fastcall DoAfterExecuteNode(Livediagram::TCustomLiveBlock* ANode);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TWorkflowDiagram(System::Classes::TComponent* AOwner);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream, bool TextFormat = false);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream, bool TextFormat = false);
	__property InternalUpdating;
	
__published:
	__property Variables;
	__property Attachments;
	__property WorkflowStudio;
	__property DisplayTaskStatus;
public:
	/* TCustomWorkflowDiagram.Destroy */ inline __fastcall virtual ~TWorkflowDiagram(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TWorkflowDiagram(HWND ParentWindow) : Wsclasses::TCustomWorkflowDiagram(ParentWindow) { }
	
};


class DELPHICLASS TWorkflowStreamDiagram;
class PASCALIMPLEMENTATION TWorkflowStreamDiagram : public TWorkflowDiagram
{
	typedef TWorkflowDiagram inherited;
	
private:
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Winapi::Messages::TMessage &Message);
	
public:
	virtual void __fastcall PaintWindow(HDC DC);
	__fastcall virtual TWorkflowStreamDiagram(System::Classes::TComponent* Owner);
public:
	/* TCustomWorkflowDiagram.Destroy */ inline __fastcall virtual ~TWorkflowStreamDiagram(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TWorkflowStreamDiagram(HWND ParentWindow) : TWorkflowDiagram(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wsdiagram */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSDIAGRAM)
using namespace Wsdiagram;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsdiagramHPP
