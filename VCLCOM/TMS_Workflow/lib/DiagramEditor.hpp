// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DiagramEditor.pas' rev: 28.00 (Windows)

#ifndef DiagrameditorHPP
#define DiagrameditorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <fDiagramEditor.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Diagrameditor
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDiagramEditor;
class PASCALIMPLEMENTATION TDiagramEditor : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Classes::TNotifyEvent FOnCloseDesigner;
	System::Classes::TNotifyEvent FOnCreateDesigner;
	System::Classes::TNotifyEvent FOnShowDesigner;
	Fdiagrameditor::TfmDiagramEditor* FForm;
	System::UnicodeString FTitle;
	Atdiagram::TatDiagramClass FDiagramClass;
	System::Classes::TNotifyEvent FOnSaveDiagram;
	Atdiagram::TDgrLibraryManager* FLibManager;
	Atdiagram::TatDiagram* FDiagramInstance;
	void __fastcall CreateDesignerForm(void);
	void __fastcall FormClosed(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall SetLibManager(Atdiagram::TDgrLibraryManager* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TDiagramEditor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDiagramEditor(void);
	void __fastcall Execute(void);
	__property Atdiagram::TatDiagramClass DiagramClass = {read=FDiagramClass, write=FDiagramClass};
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagramInstance, write=FDiagramInstance};
	__property System::Classes::TNotifyEvent OnCreateDesigner = {read=FOnCreateDesigner, write=FOnCreateDesigner};
	__property System::Classes::TNotifyEvent OnShowDesigner = {read=FOnShowDesigner, write=FOnShowDesigner};
	__property System::Classes::TNotifyEvent OnSaveDiagram = {read=FOnSaveDiagram, write=FOnSaveDiagram};
	
__published:
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
	__property System::Classes::TNotifyEvent OnCloseDesigner = {read=FOnCloseDesigner, write=FOnCloseDesigner};
	__property Atdiagram::TDgrLibraryManager* LibManager = {read=FLibManager, write=SetLibManager};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Diagrameditor */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DIAGRAMEDITOR)
using namespace Diagrameditor;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DiagrameditorHPP
