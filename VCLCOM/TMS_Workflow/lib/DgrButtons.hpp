// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrButtons.pas' rev: 28.00 (Windows)

#ifndef DgrbuttonsHPP
#define DgrbuttonsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.CategoryButtons.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <System.Actions.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgrbuttons
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDiagramButtonItemActionLink;
class DELPHICLASS TDiagramButtonItem;
class PASCALIMPLEMENTATION TDiagramButtonItemActionLink : public Vcl::Categorybuttons::TButtonItemActionLink
{
	typedef Vcl::Categorybuttons::TButtonItemActionLink inherited;
	
private:
	TDiagramButtonItem* FClient;
	
protected:
	virtual void __fastcall AssignClient(System::TObject* AClient);
	
public:
	virtual bool __fastcall IsOnExecuteLinked(void);
public:
	/* TBasicActionLink.Create */ inline __fastcall virtual TDiagramButtonItemActionLink(System::TObject* AClient) : Vcl::Categorybuttons::TButtonItemActionLink(AClient) { }
	/* TBasicActionLink.Destroy */ inline __fastcall virtual ~TDiagramButtonItemActionLink(void) { }
	
};


class PASCALIMPLEMENTATION TDiagramButtonItem : public Vcl::Categorybuttons::TButtonItem
{
	typedef Vcl::Categorybuttons::TButtonItem inherited;
	
private:
	System::UnicodeString FDControlID;
	
protected:
	virtual Vcl::Categorybuttons::TButtonItemActionLinkClass __fastcall GetActionLinkClass(void);
	
public:
	__property System::UnicodeString DControlID = {read=FDControlID, write=FDControlID};
public:
	/* TBaseButtonItem.Create */ inline __fastcall virtual TDiagramButtonItem(System::Classes::TCollection* Collection) : Vcl::Categorybuttons::TButtonItem(Collection) { }
	/* TBaseButtonItem.Destroy */ inline __fastcall virtual ~TDiagramButtonItem(void) { }
	
};


enum DECLSPEC_DENUM TDgrKeepInsertingMode : unsigned char { dkmNever, dkmAlways, dkmOnShiftPressed };

class DELPHICLASS TDiagramButtons;
class PASCALIMPLEMENTATION TDiagramButtons : public Vcl::Categorybuttons::TCategoryButtons
{
	typedef Vcl::Categorybuttons::TCategoryButtons inherited;
	
private:
	Atdiagram::TatDiagram* FDiagram;
	Vcl::Imglist::TCustomImageList* FImages;
	System::Classes::TStrings* FCatList;
	bool FShowAll;
	bool FShowEmptyCategory;
	TDgrKeepInsertingMode FKeepInsertingMode;
	void __fastcall CheckImages(void);
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	void __fastcall SetCatList(System::Classes::TStrings* const Value);
	void __fastcall CreateDgrCategory(System::UnicodeString ACaption);
	void __fastcall CreateButton(Vcl::Categorybuttons::TButtonCategory* aCategory, int ControlIndex, int index);
	void __fastcall DiagramButtonClick(System::TObject* sender);
	void __fastcall SetKeepInsertingMode(const TDgrKeepInsertingMode Value);
	void __fastcall DgrNotification(Atdiagram::TDgrNotificationInfo AInfo);
	
protected:
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall DoItemClicked(Vcl::Categorybuttons::TBaseItem* const Button);
	
public:
	__fastcall virtual TDiagramButtons(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDiagramButtons(void);
	virtual void __fastcall InitiateAction(void);
	void __fastcall Populate(void);
	
__published:
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
	__property System::Classes::TStrings* DiagramCategories = {read=FCatList, write=SetCatList};
	__property bool ShowAllObjects = {read=FShowAll, write=FShowAll, nodefault};
	__property bool ShowEmptyCategory = {read=FShowEmptyCategory, write=FShowEmptyCategory, nodefault};
	__property TDgrKeepInsertingMode KeepInsertingMode = {read=FKeepInsertingMode, write=SetKeepInsertingMode, nodefault};
	__property BevelKind = {default=3};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDiagramButtons(HWND ParentWindow) : Vcl::Categorybuttons::TCategoryButtons(ParentWindow) { }
	
private:
	void *__IDiagramSubscriber;	// Atdiagram::IDiagramSubscriber 
	
public:
	operator Atdiagram::IDiagramSubscriber*(void) { return (Atdiagram::IDiagramSubscriber*)&__IDiagramSubscriber; }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dgrbuttons */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGRBUTTONS)
using namespace Dgrbuttons;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgrbuttonsHPP
