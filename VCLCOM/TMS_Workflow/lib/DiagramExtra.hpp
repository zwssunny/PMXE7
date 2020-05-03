// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DiagramExtra.pas' rev: 28.00 (Windows)

#ifndef DiagramextraHPP
#define DiagramextraHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Buttons.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.ExtCtrls.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <Vcl.ImgList.hpp>	// Pascal unit
#include <DiagramActns.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <System.Actions.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Diagramextra
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TDTGetImageIndexEvent)(const System::UnicodeString ABlockID, int &AIdx);

enum DECLSPEC_DENUM TDiagramBarButton : unsigned char { dbBlocks, dbCancelInsert, dbDelete, dbLines };

typedef System::Set<TDiagramBarButton, TDiagramBarButton::dbBlocks, TDiagramBarButton::dbLines> TDiagramBarButtons;

class DELPHICLASS TDiagramButton;
class PASCALIMPLEMENTATION TDiagramButton : public Vcl::Buttons::TSpeedButton
{
	typedef Vcl::Buttons::TSpeedButton inherited;
	
public:
	/* TSpeedButton.Create */ inline __fastcall virtual TDiagramButton(System::Classes::TComponent* AOwner) : Vcl::Buttons::TSpeedButton(AOwner) { }
	/* TSpeedButton.Destroy */ inline __fastcall virtual ~TDiagramButton(void) { }
	
};


class DELPHICLASS TDiagramButtonActionLink;
class PASCALIMPLEMENTATION TDiagramButtonActionLink : public Vcl::Controls::TControlActionLink
{
	typedef Vcl::Controls::TControlActionLink inherited;
	
protected:
	Vcl::Buttons::TSpeedButton* FClient;
	virtual void __fastcall AssignClient(System::TObject* AClient);
	virtual bool __fastcall IsCheckedLinked(void);
	virtual void __fastcall SetChecked(bool Value);
	
public:
	virtual bool __fastcall Execute(System::Classes::TComponent* AComponent = (System::Classes::TComponent*)(0x0));
public:
	/* TBasicActionLink.Create */ inline __fastcall virtual TDiagramButtonActionLink(System::TObject* AClient) : Vcl::Controls::TControlActionLink(AClient) { }
	/* TBasicActionLink.Destroy */ inline __fastcall virtual ~TDiagramButtonActionLink(void) { }
	
};


enum DECLSPEC_DENUM TToolbarMode : unsigned char { tmObjects, tmConnections };

class DELPHICLASS TDiagramToolBar;
class PASCALIMPLEMENTATION TDiagramToolBar : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	System::Contnrs::TObjectList* FActionList;
	bool FFlatButtons;
	System::UnicodeString FCategory;
	Atdiagram::TatDiagram* FDiagram;
	Vcl::Imglist::TCustomImageList* FImages;
	TDTGetImageIndexEvent FOnGetImageIndex;
	Vcl::Imglist::TChangeLink* FImageChangeLink;
	TDiagramBarButtons FButtons;
	Diagramactns::TKeepInsertingMode FKeepInsertingMode;
	System::Contnrs::TObjectList* FButtonList;
	TToolbarMode FToolbarMode;
	int FButtonSize;
	void __fastcall RecreateButtons(void);
	void __fastcall CheckActions(void);
	void __fastcall CreateActions(void);
	void __fastcall SetFlatButtons(const bool Value);
	void __fastcall SetCategory(const System::UnicodeString Value);
	void __fastcall SetDiagram(Atdiagram::TatDiagram* const Value);
	void __fastcall CancelButtonClick(System::TObject* Sender);
	void __fastcall DeleteButtonClick(System::TObject* Sender);
	void __fastcall ButtonClick(System::TObject* Sender);
	bool __fastcall Designing(void);
	void __fastcall SetImages(Vcl::Imglist::TCustomImageList* const Value);
	void __fastcall ImageListChange(System::TObject* Sender);
	void __fastcall UpdateButtonGlyph(Vcl::Buttons::TSpeedButton* ABtn, const System::UnicodeString ABlockID, System::TClass AClass);
	void __fastcall SetButtons(const TDiagramBarButtons Value);
	Vcl::Buttons::TSpeedButton* __fastcall CreateButton(const System::UnicodeString AName, System::TClass AClass);
	void __fastcall SetKeepInsertingMode(const Diagramactns::TKeepInsertingMode Value);
	void __fastcall DestroyActions(void);
	void __fastcall DestroyButtons(void);
	void __fastcall SetToolbarMode(const TToolbarMode Value);
	void __fastcall AdjustBarButtons(void);
	void __fastcall SetButtonSize(const int Value);
	void __fastcall DgrNotification(Atdiagram::TDgrNotificationInfo AInfo);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall CreateWnd(void);
	void __fastcall UpdateButtons(void);
	
public:
	__fastcall virtual TDiagramToolBar(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDiagramToolBar(void);
	void __fastcall Rebuild(void);
	
__published:
	__property bool FlatButtons = {read=FFlatButtons, write=SetFlatButtons, default=1};
	__property TDiagramBarButtons Buttons = {read=FButtons, write=SetButtons, default=15};
	__property System::UnicodeString Category = {read=FCategory, write=SetCategory};
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
	__property Vcl::Imglist::TCustomImageList* Images = {read=FImages, write=SetImages};
	__property Align = {default=1};
	__property TDTGetImageIndexEvent OnGetImageIndex = {read=FOnGetImageIndex, write=FOnGetImageIndex};
	__property Diagramactns::TKeepInsertingMode KeepInsertingMode = {read=FKeepInsertingMode, write=SetKeepInsertingMode, nodefault};
	__property TToolbarMode Mode = {read=FToolbarMode, write=SetToolbarMode, nodefault};
	__property int ButtonSize = {read=FButtonSize, write=SetButtonSize, nodefault};
public:
	/* TWinControl.CreateParented */ inline __fastcall TDiagramToolBar(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
private:
	void *__IDiagramSubscriber;	// Atdiagram::IDiagramSubscriber 
	
public:
	operator Atdiagram::IDiagramSubscriber*(void) { return (Atdiagram::IDiagramSubscriber*)&__IDiagramSubscriber; }
	
};


//-- var, const, procedure ---------------------------------------------------
#define DiagramBarButtons (System::Set<TDiagramBarButton, TDiagramBarButton::dbBlocks, TDiagramBarButton::dbLines>() << TDiagramBarButton::dbBlocks << TDiagramBarButton::dbCancelInsert << TDiagramBarButton::dbDelete << TDiagramBarButton::dbLines )
}	/* namespace Diagramextra */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DIAGRAMEXTRA)
using namespace Diagramextra;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DiagramextraHPP
