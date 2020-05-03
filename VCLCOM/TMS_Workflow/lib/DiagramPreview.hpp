// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DiagramPreview.pas' rev: 28.00 (Windows)

#ifndef DiagrampreviewHPP
#define DiagrampreviewHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Diagrampreview
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPagePreview;
class PASCALIMPLEMENTATION TPagePreview : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	Vcl::Graphics::TGraphic* FPage;
	
protected:
	HIDESBASE MESSAGE void __fastcall WMEraseBkGnd(Winapi::Messages::TWMEraseBkgnd &Message);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual ~TPagePreview(void);
public:
	/* TCustomControl.Create */ inline __fastcall virtual TPagePreview(System::Classes::TComponent* AOwner) : Vcl::Controls::TCustomControl(AOwner) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TPagePreview(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
};


class DELPHICLASS TfmDiagramPreview;
class PASCALIMPLEMENTATION TfmDiagramPreview : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Forms::TScrollBox* ScrollBox1;
	Vcl::Extctrls::TPanel* pnToolbar;
	Vcl::Buttons::TSpeedButton* btPreviousPage;
	Vcl::Buttons::TSpeedButton* btNextPage;
	Vcl::Buttons::TSpeedButton* btPrint;
	Vcl::Buttons::TSpeedButton* btZoom;
	Vcl::Buttons::TSpeedButton* SpeedButton2;
	Vcl::Menus::TPopupMenu* pmZoom;
	Vcl::Menus::TMenuItem* N5001;
	Vcl::Menus::TMenuItem* N2001;
	Vcl::Menus::TMenuItem* N1501;
	Vcl::Menus::TMenuItem* N1001;
	Vcl::Menus::TMenuItem* N751;
	Vcl::Menus::TMenuItem* N501;
	Vcl::Menus::TMenuItem* N251;
	Vcl::Menus::TMenuItem* N101;
	Vcl::Extctrls::TPanel* pnPage;
	void __fastcall btPreviousPageClick(System::TObject* Sender);
	void __fastcall btNextPageClick(System::TObject* Sender);
	void __fastcall btPrintClick(System::TObject* Sender);
	void __fastcall btZoomClick(System::TObject* Sender);
	void __fastcall N101Click(System::TObject* Sender);
	void __fastcall SpeedButton2Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall FormResize(System::TObject* Sender);
	
private:
	Atdiagram::TatDiagram* FDiagram;
	double FZoomRatio;
	int FCurPage;
	TPagePreview* FPagePreview;
	void __fastcall UpdateImagePlacement(void);
	void __fastcall Redraw(void);
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	void __fastcall UpdateZoomCaption(void);
	void __fastcall UpdatePageCaption(void);
	void __fastcall CalculateImageSize(void);
	
public:
	__fastcall virtual TfmDiagramPreview(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TfmDiagramPreview(void);
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfmDiagramPreview(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfmDiagramPreview(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Diagrampreview */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DIAGRAMPREVIEW)
using namespace Diagrampreview;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DiagrampreviewHPP
