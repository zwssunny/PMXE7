// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'atDiagram.pas' rev: 28.00 (Windows)

#ifndef AtdiagramHPP
#define AtdiagramHPP

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
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit
#include <Direct2dClasses.hpp>	// Pascal unit
#include <DgrGdipApi.hpp>	// Pascal unit
#include <DgrGdipObj.hpp>	// Pascal unit
#include <GdipClasses.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Clipbrd.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Imaging.jpeg.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <Winapi.CommCtrl.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Atdiagram
{
//-- type declarations -------------------------------------------------------
typedef double number;

enum DECLSPEC_DENUM THandleMoveAction : unsigned char { haEraseCursor, haDrawCursor, haMoved, haPositionCursor };

class DELPHICLASS TStretchHandle;
class DELPHICLASS TLinkPoint;
class DELPHICLASS TDiagramControl;
struct DECLSPEC_DRECORD THandleMoveInfo
{
public:
	Vcl::Graphics::TCanvas* Canvas;
	TStretchHandle* AHandle;
	THandleMoveAction Action;
	TLinkPoint* AnchorPoint;
	TDiagramControl* DControl;
	Diagramutils::TDot Delta;
};


enum DECLSPEC_DENUM TExportFormat : unsigned char { efAuto, efBMP, efWMF };

enum DECLSPEC_DENUM TExportSize : unsigned char { esStandard, esCentered, esNetto };

class DELPHICLASS EDiagramException;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EDiagramException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDiagramException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDiagramException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDiagramException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDiagramException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDiagramException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDiagramException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDiagramException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDiagramException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDiagramException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDiagramException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDiagramException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDiagramException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDiagramException(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EDControlNotFound;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EDControlNotFound : public EDiagramException
{
	typedef EDiagramException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDControlNotFound(const System::UnicodeString Msg) : EDiagramException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDControlNotFound(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : EDiagramException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDControlNotFound(NativeUInt Ident)/* overload */ : EDiagramException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDControlNotFound(System::PResStringRec ResStringRec)/* overload */ : EDiagramException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDControlNotFound(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : EDiagramException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDControlNotFound(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : EDiagramException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDControlNotFound(const System::UnicodeString Msg, int AHelpContext) : EDiagramException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDControlNotFound(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : EDiagramException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDControlNotFound(NativeUInt Ident, int AHelpContext)/* overload */ : EDiagramException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDControlNotFound(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDiagramException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDControlNotFound(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : EDiagramException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDControlNotFound(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : EDiagramException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDControlNotFound(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS EDiagramPrintException;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EDiagramPrintException : public EDiagramException
{
	typedef EDiagramException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDiagramPrintException(const System::UnicodeString Msg) : EDiagramException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDiagramPrintException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : EDiagramException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDiagramPrintException(NativeUInt Ident)/* overload */ : EDiagramException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDiagramPrintException(System::PResStringRec ResStringRec)/* overload */ : EDiagramException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDiagramPrintException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : EDiagramException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDiagramPrintException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : EDiagramException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDiagramPrintException(const System::UnicodeString Msg, int AHelpContext) : EDiagramException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDiagramPrintException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : EDiagramException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDiagramPrintException(NativeUInt Ident, int AHelpContext)/* overload */ : EDiagramException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDiagramPrintException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDiagramException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDiagramPrintException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : EDiagramException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDiagramPrintException(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : EDiagramException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDiagramPrintException(void) { }
	
};

#pragma pack(pop)

typedef System::TMetaClass* TGroupBlockClass;

typedef System::TMetaClass* TDiagramMemoClass;

typedef System::Types::TRect *TRectPtr;

enum DECLSPEC_DENUM TSelectDirection : unsigned char { sdUp, sdLeft, sdDown, sdRight };

enum DECLSPEC_DENUM TDiagramControlFilter : unsigned char { cfAll, cfIgnoreMembers, cfIgnoreGroups, cfIgnoreAsMembers };

class DELPHICLASS TDiagramUndoItem;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramUndoItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FActionName;
	System::Classes::TStream* FState;
	System::TObject* FObj;
	
public:
	__fastcall virtual TDiagramUndoItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TDiagramUndoItem(void);
	__property System::UnicodeString ActionName = {read=FActionName, write=FActionName};
	__property System::TObject* Obj = {read=FObj, write=FObj};
	__property System::Classes::TStream* State = {read=FState};
};

#pragma pack(pop)

class DELPHICLASS TDiagramUndoStack;
class DELPHICLASS TatDiagram;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramUndoStack : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
private:
	int FCurrent;
	TatDiagram* FDiagram;
	void __fastcall ClearUndoStack(void);
	void __fastcall PushState(const System::UnicodeString AActionName);
	void __fastcall Undo(void);
	void __fastcall Redo(void);
	System::UnicodeString __fastcall NextUndoAction(void);
	System::UnicodeString __fastcall NextRedoAction(void);
	
public:
	__fastcall TDiagramUndoStack(TatDiagram* ADiagram);
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDiagramUndoStack(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TDiagramPersistent;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramPersistent : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TDiagramControl* FDControl;
	
protected:
	virtual void __fastcall Changed(void);
	
public:
	__fastcall TDiagramPersistent(TDiagramControl* ADControl);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDiagramPersistent(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM THandleAppearanceStyle : unsigned char { hhRectangle, hhEllipse, hhDiamond, hhCrossedEllipse, hhRectangleX, hhEllipseX };

class DELPHICLASS THandleAppearance;
#pragma pack(push,4)
class PASCALIMPLEMENTATION THandleAppearance : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	Vcl::Graphics::TPen* FPen;
	Vcl::Graphics::TBrush* FDisabledBrush;
	Vcl::Graphics::TBrush* FBrush;
	int FSize;
	THandleAppearanceStyle FStyle;
	Vcl::Graphics::TPen* FDisabledPen;
	bool FVisible;
	void __fastcall SetBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetDisabledBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetDisabledPen(Vcl::Graphics::TPen* const Value);
	void __fastcall SetPen(Vcl::Graphics::TPen* const Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetStyle(const THandleAppearanceStyle Value);
	void __fastcall SetVisible(const bool Value);
	
public:
	__fastcall THandleAppearance(void);
	__fastcall virtual ~THandleAppearance(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property Vcl::Graphics::TPen* Pen = {read=FPen, write=SetPen};
	__property Vcl::Graphics::TBrush* Brush = {read=FBrush, write=SetBrush};
	__property Vcl::Graphics::TPen* DisabledPen = {read=FDisabledPen, write=SetDisabledPen};
	__property Vcl::Graphics::TBrush* DisabledBrush = {read=FDisabledBrush, write=SetDisabledBrush};
	__property int Size = {read=FSize, write=SetSize, nodefault};
	__property THandleAppearanceStyle Style = {read=FStyle, write=SetStyle, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
};

#pragma pack(pop)

class DELPHICLASS THandlesAppearance;
#pragma pack(push,4)
class PASCALIMPLEMENTATION THandlesAppearance : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	THandleAppearance* FCustom;
	THandleAppearance* FRotate;
	THandleAppearance* FRotCenter;
	THandleAppearance* FSize;
	void __fastcall SetCustom(THandleAppearance* const Value);
	void __fastcall SetRotate(THandleAppearance* const Value);
	void __fastcall SetRotCenter(THandleAppearance* const Value);
	void __fastcall SetSize(THandleAppearance* const Value);
	
public:
	__fastcall THandlesAppearance(void);
	__fastcall virtual ~THandlesAppearance(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property THandleAppearance* Size = {read=FSize, write=SetSize};
	__property THandleAppearance* Rotate = {read=FRotate, write=SetRotate};
	__property THandleAppearance* Custom = {read=FCustom, write=SetCustom};
	__property THandleAppearance* RotCenter = {read=FRotCenter, write=SetRotCenter};
};

#pragma pack(pop)

enum DECLSPEC_DENUM THandleStyle : unsigned char { hsSize, hsRotate, hsRotCenter, hsCustom };

class PASCALIMPLEMENTATION TStretchHandle : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	double FOrX;
	double FOrY;
	System::Uitypes::TCursor FCursor;
	int FData;
	THandleStyle FStyle;
	bool FVisible;
	bool FAlwaysMovable;
	TDiagramControl* __fastcall GetControl(void);
	Diagramutils::TDot __fastcall GetOrPoint(void);
	void __fastcall SetOrPoint(const Diagramutils::TDot &Value);
	void __fastcall SetOrX(const double Value);
	void __fastcall SetOrY(const double Value);
	void __fastcall SetStyle(const THandleStyle Value);
	void __fastcall SetVisible(const bool Value);
	bool __fastcall GetVisible(void);
	
protected:
	__property TDiagramControl* DControl = {read=GetControl};
	bool __fastcall Movable(void);
	
public:
	__fastcall virtual TStretchHandle(System::Classes::TCollection* Collection);
	__fastcall virtual ~TStretchHandle(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	Diagramutils::TDot __fastcall DiagramPoint(void);
	__property bool AlwaysMovable = {read=FAlwaysMovable, write=FAlwaysMovable, nodefault};
	__property System::Uitypes::TCursor Cursor = {read=FCursor, write=FCursor, nodefault};
	__property int Data = {read=FData, write=FData, nodefault};
	__property Diagramutils::TDot OrPoint = {read=GetOrPoint, write=SetOrPoint};
	__property bool Visible = {read=GetVisible, write=SetVisible, default=1};
	
__published:
	__property double OrX = {read=FOrX, write=SetOrX};
	__property double OrY = {read=FOrY, write=SetOrY};
	__property THandleStyle Style = {read=FStyle, write=SetStyle, nodefault};
};


class DELPHICLASS TStretchHandles;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TStretchHandles : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TStretchHandle* operator[](int Index) { return Items[Index]; }
	
private:
	TDiagramControl* FDControl;
	HIDESBASE TStretchHandle* __fastcall GetItem(int Index);
	
public:
	__fastcall TStretchHandles(TDiagramControl* ADControl);
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	HIDESBASE TStretchHandle* __fastcall Add(void)/* overload */;
	HIDESBASE TStretchHandle* __fastcall Add(double AOrX, double AOrY, System::Uitypes::TCursor ACursor = (System::Uitypes::TCursor)(0xfffffff8), int AData = 0x0, THandleStyle AStyle = (THandleStyle)(0x0))/* overload */;
	TStretchHandle* __fastcall FindByData(int AData);
	TStretchHandle* __fastcall RotateHandle(void);
	TStretchHandle* __fastcall RotCenterHandle(void);
	__property TStretchHandle* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TStretchHandles(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TLinkPointStyle : unsigned char { ptNone, ptEllipse, ptRectangle, ptDiamond, ptCross, ptImplicit };

enum DECLSPEC_DENUM TAnchorChange : unsigned char { acPosition, acRemoval };

enum DECLSPEC_DENUM TAnchorOrientation : unsigned char { aoNone, aoHorz, aoVert, aoUp, aoDown, aoLeft, aoRight };

enum DECLSPEC_DENUM TLinkConstraint : unsigned char { lcAll, lcSourceOnly, lcTargetOnly, lcNone };

class PASCALIMPLEMENTATION TLinkPoint : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	double FOrX;
	double FOrY;
	int FAnchorIndex;
	TDiagramControl* FAnchor;
	TAnchorOrientation FOrientation;
	System::Classes::TList* FAnchoreds;
	bool FCollapsable;
	bool FCollapsed;
	System::TObject* FObj;
	TLinkConstraint FLinkConstraint;
	bool FVisible;
	bool FCanAnchor;
	bool FAcceptAnchoreds;
	bool FCanAnchorInMove;
	TDiagramControl* __fastcall GetDControl(void);
	void __fastcall SetAnchor(TDiagramControl* const Value);
	TLinkPoint* __fastcall GetAnchorLink(void);
	void __fastcall SetAnchorLink(TLinkPoint* const Value);
	void __fastcall SetAnchorIndex(const int Value);
	TLinkPointStyle __fastcall GetStyle(void);
	TAnchorOrientation __fastcall GetRealOrientation(void);
	TLinkPoint* __fastcall GetAnchoredItem(int Index);
	Diagramutils::TDot __fastcall GetOrPoint(void);
	void __fastcall SetOrPoint(const Diagramutils::TDot &Value);
	bool __fastcall IsNode(void);
	void __fastcall SetCollapsed(const bool Value);
	bool __fastcall DoCollapseControls(bool ACollapse);
	void __fastcall SetVisible(const bool Value);
	
public:
	__fastcall virtual TLinkPoint(System::Classes::TCollection* Collection);
	__fastcall virtual ~TLinkPoint(void);
	void __fastcall AnchorChanged(TAnchorChange AChangeType);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	Diagramutils::TDot __fastcall DiagramPoint(void);
	int __fastcall AnchoredCount(void);
	void __fastcall Expand(void);
	void __fastcall Collapse(void);
	__property TDiagramControl* DControl = {read=GetDControl};
	__property TLinkPoint* Anchoreds[int Index] = {read=GetAnchoredItem};
	__property TAnchorOrientation RealOrientation = {read=GetRealOrientation, nodefault};
	__property TLinkPoint* AnchorLink = {read=GetAnchorLink, write=SetAnchorLink};
	__property TLinkPointStyle Style = {read=GetStyle, nodefault};
	__property Diagramutils::TDot OrPoint = {read=GetOrPoint, write=SetOrPoint};
	__property System::TObject* Obj = {read=FObj, write=FObj};
	__property bool CanAnchor = {read=FCanAnchor, write=FCanAnchor, nodefault};
	__property bool CanAnchorInMove = {read=FCanAnchorInMove, write=FCanAnchorInMove, nodefault};
	__property bool AcceptAnchoreds = {read=FAcceptAnchoreds, write=FAcceptAnchoreds, nodefault};
	
__published:
	__property TDiagramControl* Anchor = {read=FAnchor, write=SetAnchor};
	__property int AnchorIndex = {read=FAnchorIndex, write=SetAnchorIndex, default=-1};
	__property double OrX = {read=FOrX, write=FOrX};
	__property double OrY = {read=FOrY, write=FOrY};
	__property TAnchorOrientation Orientation = {read=FOrientation, write=FOrientation, default=0};
	__property bool Collapsable = {read=FCollapsable, write=FCollapsable, nodefault};
	__property bool Collapsed = {read=FCollapsed, write=SetCollapsed, nodefault};
	__property TLinkConstraint LinkConstraint = {read=FLinkConstraint, write=FLinkConstraint, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
};


class DELPHICLASS TLinkPoints;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TLinkPoints : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TLinkPoint* operator[](int Index) { return Items[Index]; }
	
private:
	TDiagramControl* FDControl;
	HIDESBASE TLinkPoint* __fastcall GetItem(int Index);
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	HIDESBASE TLinkPoint* __fastcall Add(void)/* overload */;
	HIDESBASE TLinkPoint* __fastcall Add(double AOrX, double AOrY, TAnchorOrientation AOr = (TAnchorOrientation)(0x0))/* overload */;
	__property TLinkPoint* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TLinkPoints(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TLinkPoints(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TControlRestriction : unsigned char { crNoMove, crNoResize, crNoRotation, crNoEdit, crNoDelete, crKeepRatio, crNoClipboard, crNoSelect, crNoRotCenterMove, crNoLink };

typedef System::Set<TControlRestriction, TControlRestriction::crNoMove, TControlRestriction::crNoLink> TControlRestrictions;

enum DECLSPEC_DENUM TControlMoveAction : unsigned char { caEraseCursor, caDrawCursor, caMoved, caPositionCursor };

struct DECLSPEC_DRECORD TControlMoveInfo
{
public:
	Vcl::Graphics::TCanvas* Canvas;
	TStretchHandle* AHandle;
	TControlMoveAction Action;
	TLinkPoint* AnchorPoint;
	TLinkPoint* LinkPoint;
	Diagramutils::TDot Delta;
};


struct DECLSPEC_DRECORD TDiagramDrawInfo
{
public:
	Vcl::Graphics::TCanvas* Canvas;
	Diagramutils::TBlockDrawer* Drawer;
	Dgrclasses::TDgrBlockDrawer* DgrDrawer;
};


struct DECLSPEC_DRECORD TDiagramDrawBlockInfo
{
public:
	Diagramutils::TSquare Rect;
	double Angle;
};


struct DECLSPEC_DRECORD TDiagramDrawLineInfo
{
public:
	TStretchHandles* Handles;
	bool DrawArrows;
};


struct DECLSPEC_DRECORD TDiagramDrawArrowInfo
{
public:
	Diagramutils::TDot FromPoint;
	Diagramutils::TDot ToPoint;
	double ZoomRatio;
};


typedef System::DynamicArray<TControlMoveInfo> TControlMoveInfoArray;

enum DECLSPEC_DENUM TControlInsertAction : unsigned char { iaEraseCursor, iaDrawCursor, iaInserted };

struct DECLSPEC_DRECORD TControlInsertInfo
{
public:
	TatDiagram* Diagram;
	Vcl::Graphics::TCanvas* Canvas;
	TControlInsertAction Action;
	TLinkPoint* AnchorPoint1;
	TLinkPoint* AnchorPoint2;
	TDiagramControl* DControl;
	Diagramutils::TDot P1;
	Diagramutils::TDot P2;
	bool Clicked;
};


enum DECLSPEC_DENUM TControlDrawAction : unsigned char { daEraseCursor, daDrawCursor, daStart, daStep, daInserted };

struct DECLSPEC_DRECORD TControlDrawInfo
{
public:
	TatDiagram* Diagram;
	Vcl::Graphics::TCanvas* Canvas;
	TControlDrawAction Action;
	TLinkPoint* AnchorPoint1;
	TLinkPoint* AnchorPoint2;
	TDiagramControl* DControl;
	Diagramutils::TDot P1;
	Diagramutils::TDot P2;
};


enum DECLSPEC_DENUM TGradientDirection : unsigned char { grTopBottom, grBottomTop, grLeftRight, grRightLeft, grLeftTop, grRightTop, grLeftBottom, grRightBottom, grInOut, grOutIn, grHorzInOut, grHorzOutIn, grVertInOut, grVertOutIn };

class DELPHICLASS TDiagramGradient;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramGradient : public TDiagramPersistent
{
	typedef TDiagramPersistent inherited;
	
private:
	TGradientDirection FDirection;
	System::Uitypes::TColor FStartColor;
	System::Uitypes::TColor FEndColor;
	Diagramutils::TBlockDrawer* FDrawer;
	bool FVisible;
	TatDiagram* FDiagram;
	void __fastcall SetDirection(const TGradientDirection Value);
	void __fastcall SetEndColor(const System::Uitypes::TColor Value);
	void __fastcall SetStartColor(const System::Uitypes::TColor Value);
	void __fastcall SetVisible(const bool Value);
	Dgrclasses::TDgrGradientMode __fastcall GetDgrGradientMode(void);
	
public:
	virtual void __fastcall Changed(void);
	__fastcall TDiagramGradient(TDiagramControl* ADControl, TatDiagram* ADiagram);
	__fastcall virtual ~TDiagramGradient(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall DrawGradient(Vcl::Graphics::TCanvas* Canvas, const Diagramutils::TSquare &ARect, double AAngle)/* overload */;
	void __fastcall DrawGradient(Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
__published:
	__property TGradientDirection Direction = {read=FDirection, write=SetDirection, nodefault};
	__property System::Uitypes::TColor StartColor = {read=FStartColor, write=SetStartColor, nodefault};
	__property System::Uitypes::TColor EndColor = {read=FEndColor, write=SetEndColor, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TCustomDiagramLine;
typedef void __fastcall (__closure *TDControlLinkEvent)(TDiagramControl* ADControl, TCustomDiagramLine* ALink, TLinkPoint* ALinkPoint);

typedef void __fastcall (__closure *TDiagramLinkEvent)(System::TObject* Sender, TDiagramControl* ADControl, TCustomDiagramLine* ALink, TLinkPoint* ALinkPoint);

typedef void __fastcall (__closure *TDiagramPosEvent)(System::TObject* Sender, int X, int Y);

typedef void __fastcall (__closure *TAcceptAnchorEvent)(System::TObject* Sender, TLinkPoint* ALink, TLinkPoint* AAnchor, bool &Accept);

typedef void __fastcall (__closure *TAcceptLinkEvent)(System::TObject* Sender, TCustomDiagramLine* ALink, TLinkPoint* Anchor1, TLinkPoint* Anchor2, bool &Accept);

enum DECLSPEC_DENUM TInsertStyle : unsigned char { isInsert, isDraw };

enum DECLSPEC_DENUM TMouseState : unsigned char { msBrowsing, msSelecting, msInserting, msToInsert, msMoving, msLink, msResizing, msToDraw, msDrawing, msToPan, msPanning, msClickingNode, msToZoom, msZooming };

enum DECLSPEC_DENUM TZoomingState : unsigned char { zsZoomIn, zsZoomOut };

class DELPHICLASS TTextCellFrame;
class DELPHICLASS TTextCell;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTextCellFrame : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TTextCell* FTextCell;
	bool FTransparent;
	bool FAutoFrame;
	int FAutoFrameMargin;
	Vcl::Graphics::TBrush* FBrush;
	System::Uitypes::TColor FColor;
	Vcl::Graphics::TPen* FPen;
	bool FVisible;
	void __fastcall SetAutoFrame(const bool Value);
	void __fastcall SetAutoFrameMargin(const int Value);
	void __fastcall SetBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetPen(Vcl::Graphics::TPen* const Value);
	void __fastcall SetTransparent(const bool Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall StyleChanged(System::TObject* Sender);
	
public:
	__fastcall TTextCellFrame(TTextCell* ATextCell);
	__fastcall virtual ~TTextCellFrame(void);
	void __fastcall Changed(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property Vcl::Graphics::TBrush* Brush = {read=FBrush, write=SetBrush};
	__property Vcl::Graphics::TPen* Pen = {read=FPen, write=SetPen};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, nodefault};
	__property bool AutoFrame = {read=FAutoFrame, write=SetAutoFrame, nodefault};
	__property int AutoFrameMargin = {read=FAutoFrameMargin, write=SetAutoFrameMargin, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TTextCell : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	bool FWordWrap;
	bool FClip;
	double FAngle;
	double FHeight;
	double FTop;
	double FLeft;
	double FWidth;
	System::UnicodeString FText;
	Vcl::Graphics::TFont* FFont;
	bool FDControlFont;
	System::Classes::TAlignment FAlignment;
	Diagramutils::TVertAlign FVertAlign;
	bool FRotateFont;
	bool FDControlAngle;
	TTextCellFrame* FCellFrame;
	bool FVisible;
	System::TObject* FObj;
	bool FParentTransparency;
	int FTransparency;
	void __fastcall SetAngle(const double Value);
	void __fastcall SetClip(const bool Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall SetHeight(const double Value);
	void __fastcall SetLeft(const double Value);
	void __fastcall SetText(const System::UnicodeString Value);
	void __fastcall SetTop(const double Value);
	void __fastcall SetWidth(const double Value);
	void __fastcall SetWordWrap(const bool Value);
	bool __fastcall IsFontStored(void);
	void __fastcall SetDControlFont(const bool Value);
	TDiagramControl* __fastcall GetDControl(void);
	void __fastcall SetBoundsRect(const Diagramutils::TSquare &Value);
	Diagramutils::TSquare __fastcall GetBoundsRect(void);
	void __fastcall SetAlignment(const System::Classes::TAlignment Value);
	void __fastcall SetVertAlign(const Diagramutils::TVertAlign Value);
	void __fastcall SetRotateFont(const bool Value);
	double __fastcall GetBottom(void);
	double __fastcall GetRight(void);
	bool __fastcall IsAngleStored(void);
	void __fastcall SetDControlAngle(const bool Value);
	void __fastcall SetCellFrame(TTextCellFrame* const Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetParentTransparency(const bool Value);
	void __fastcall SetTransparency(const int Value);
	
protected:
	Diagramutils::TSquare __fastcall GetDiagramRect(void);
	void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall DControlFontChanged(void);
	void __fastcall DControlAngleChanged(void);
	void __fastcall BoundsChanged(const Diagramutils::TSquare &AOld, const Diagramutils::TSquare &ANew);
	__property TDiagramControl* DControl = {read=GetDControl};
	
public:
	__fastcall virtual TTextCell(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTextCell(void);
	void __fastcall SetBounds(double ALeft, double ATop, double AWidth, double AHeight);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property Diagramutils::TSquare DiagramRect = {read=GetDiagramRect};
	__property Diagramutils::TSquare BoundsRect = {read=GetBoundsRect, write=SetBoundsRect};
	__property double Right = {read=GetRight};
	__property double Bottom = {read=GetBottom};
	__property System::TObject* Obj = {read=FObj, write=FObj};
	
__published:
	__property Vcl::Graphics::TFont* Font = {read=FFont, write=SetFont, stored=IsFontStored};
	__property bool DControlAngle = {read=FDControlAngle, write=SetDControlAngle, nodefault};
	__property double Angle = {read=FAngle, write=SetAngle, stored=IsAngleStored};
	__property double Left = {read=FLeft, write=SetLeft};
	__property double Top = {read=FTop, write=SetTop};
	__property double Width = {read=FWidth, write=SetWidth};
	__property double Height = {read=FHeight, write=SetHeight};
	__property System::UnicodeString Text = {read=FText, write=SetText};
	__property bool Clip = {read=FClip, write=SetClip, nodefault};
	__property bool WordWrap = {read=FWordWrap, write=SetWordWrap, nodefault};
	__property bool DControlFont = {read=FDControlFont, write=SetDControlFont, nodefault};
	__property System::Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, nodefault};
	__property Diagramutils::TVertAlign VertAlign = {read=FVertAlign, write=SetVertAlign, nodefault};
	__property bool RotateFont = {read=FRotateFont, write=SetRotateFont, nodefault};
	__property TTextCellFrame* CellFrame = {read=FCellFrame, write=SetCellFrame};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property bool ParentTransparency = {read=FParentTransparency, write=SetParentTransparency, default=1};
	__property int Transparency = {read=FTransparency, write=SetTransparency, nodefault};
};


class DELPHICLASS TTextCells;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTextCells : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TTextCell* operator[](int Index) { return Items[Index]; }
	
private:
	TDiagramControl* FDControl;
	HIDESBASE TTextCell* __fastcall GetItem(int Index);
	
public:
	__fastcall TTextCells(TDiagramControl* ADControl);
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	HIDESBASE TTextCell* __fastcall Add(void);
	__property TTextCell* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TTextCells(void) { }
	
};

#pragma pack(pop)

typedef System::TMetaClass* TLinkPointClass;

enum DECLSPEC_DENUM TDControlPaintMode : unsigned char { pmNormal, pmNormalCursor, pmCursorOnly };

class DELPHICLASS TDiagramLayer;
class DELPHICLASS TGroupBlock;
class PASCALIMPLEMENTATION TDiagramControl : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TatDiagram* FDiagram;
	bool FSelected;
	TStretchHandles* FHandles;
	TLinkPoints* FLinkPoints;
	TControlRestrictions FRestrictions;
	System::UnicodeString FDControlID;
	Vcl::Graphics::TBrush* FLinkPointBrush;
	Vcl::Graphics::TPen* FLinkPointPen;
	double FAngle;
	Diagramutils::TBlockDrawer* FDrawer;
	Diagramutils::TBlockDrawer* FTempDrawer;
	TLinkPointStyle FLinkPointStyle;
	TDControlLinkEvent FOnLinkRemoved;
	TDControlLinkEvent FOnLinkAdded;
	System::TObject* FObj;
	TInsertStyle FInsertStyle;
	System::UnicodeString FHint;
	bool FShowHint;
	bool FParentShowHint;
	System::Uitypes::TCursor FCursor;
	Vcl::Graphics::TFont* FFont;
	bool FDiagramFont;
	TTextCells* FTextCells;
	int FNotifying;
	System::UnicodeString FStringData;
	bool FVisible;
	int FLayerInteger;
	TDiagramLayer* FLayerObj;
	bool FCollapsed;
	bool FAutoCreateLinkPoints;
	bool FIsBackgroundControl;
	Dgrclasses::TDgrBlockDrawer* FDgrDrawer;
	Dgrclasses::TDgrGraphicsPath* FTempPath;
	TDControlPaintMode FIntPaintMode;
	int FTransparency;
	TGroupBlock* FGroupBlock;
	System::UnicodeString FLayerNameFix;
	THandlesAppearance* FHandlesAppearance;
	Dgrclasses::TDgrGraphicLib FGraphicLib;
	bool FCustomGraphicLib;
	void __fastcall SetPaintMode(TDControlPaintMode Value);
	void __fastcall SetDiagram(TatDiagram* const Value);
	void __fastcall SetSelected(bool Value);
	void __fastcall SetHandles(TStretchHandles* const Value);
	void __fastcall IntDiagramChanged(TatDiagram* Old, TatDiagram* New);
	void __fastcall SetRestrictions(const TControlRestrictions Value);
	void __fastcall SetLinkPoints(TLinkPoints* const Value);
	void __fastcall DrawLinkPoint(TLinkPoint* ALinkPoint, const System::Types::TPoint &APoint);
	void __fastcall SetLinkPointBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetLinkPointPen(Vcl::Graphics::TPen* const Value);
	void __fastcall DrawObjectChanged(System::TObject* Sender);
	void __fastcall AddAnchored(TLinkPoint* AnchorLinkPoint, TLinkPoint* ControlLinkPoint);
	void __fastcall RemoveAnchored(TLinkPoint* AnchorLinkPoint, TLinkPoint* ControlLinkPoint);
	void __fastcall SetAngle(const double Value);
	bool __fastcall IsAngleStored(void);
	void __fastcall DrawLinkPoints(Vcl::Graphics::TCanvas* ACanvas, Dgrclasses::TDgrPaintEngine* APaintEngine, bool OnlyNodes = false);
	void __fastcall Paint(Vcl::Graphics::TCanvas* Canvas, Dgrclasses::TDgrPaintEngine* ADgrPaintEngine = (Dgrclasses::TDgrPaintEngine*)(0x0));
	System::UnicodeString __fastcall GetDControlID(void);
	void __fastcall LoadDControlIDProp(System::Classes::TReader* Reader);
	void __fastcall StoreDControlIDProp(System::Classes::TWriter* Writer);
	void __fastcall SetLinkPointStyle(const TLinkPointStyle Value);
	TMouseState __fastcall InsertMouseState(void);
	bool __fastcall IsShowHintStored(void);
	void __fastcall SetShowHint(const bool Value);
	void __fastcall SetParentShowHint(const bool Value);
	void __fastcall DiagramShowHintChanged(void);
	void __fastcall SetDiagramFont(const bool Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall DiagramFontChanged(void);
	bool __fastcall IsFontStored(void);
	void __fastcall SetTextCells(TTextCells* const Value);
	void __fastcall SetVisible(const bool Value);
	System::UnicodeString __fastcall GetLayerName(void);
	void __fastcall SetLayerName(const System::UnicodeString Value);
	int __fastcall GetLayerInteger(void);
	void __fastcall SetLayerInteger(const int Value);
	void __fastcall SetLayerObj(TDiagramLayer* Value);
	void __fastcall LoadCollapsedProp(System::Classes::TReader* Reader);
	void __fastcall StoreCollapsedProp(System::Classes::TWriter* Writer);
	bool __fastcall GetIsVisible(void);
	bool __fastcall GetSelected(void);
	void __fastcall InternalWriteText(Vcl::Graphics::TCanvas* Canvas, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, const System::UnicodeString S, System::Classes::TAlignment HAlign, Diagramutils::TVertAlign VAlign, bool AWrap, double AAngle, double CX, double CY, bool DrawText, Diagramutils::TSquare &NewRect, bool IgnoreZoom);
	Diagramutils::TSquare __fastcall InternalWriteTextDgr(Dgrclasses::TDgrBlockDrawer* ADrawer, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, const System::UnicodeString S, System::Classes::TAlignment HAlign, Diagramutils::TVertAlign VAlign, bool AWrap, double AAngle, const Diagramutils::TDot &RotC, bool AClip, bool ADrawFrame, bool ADrawText, int ATransparency, int AFrameMargin = 0x0);
	void __fastcall SetIsBackgroundControl(const bool Value);
	void __fastcall SetTransparency(const int Value);
	bool __fastcall DrawGrouped(void);
	void __fastcall BeginNotifying(void);
	void __fastcall EndNotifying(void);
	TGroupBlock* __fastcall GetGroupBlock(void);
	TGroupBlock* __fastcall GetMasterGroup(void);
	void __fastcall IncludedInGroup(TGroupBlock* AGroup);
	void __fastcall RemovedFromGroup(TGroupBlock* AGroup);
	bool __fastcall GetIsMember(void);
	bool __fastcall GetIsGroup(void);
	bool __fastcall CanRotate(void);
	bool __fastcall CanResize(void);
	bool __fastcall CanMove(void);
	bool __fastcall CanSelect(void);
	bool __fastcall CanDoClipboard(void);
	bool __fastcall CanEditText(void);
	bool __fastcall CanMoveRotCenter(void);
	bool __fastcall CanLink(void);
	bool __fastcall LayerEditable(void);
	bool __fastcall GetAsMember(void);
	void __fastcall PaintHandle(const TDiagramDrawInfo &AInfo, TStretchHandle* AHandle, THandlesAppearance* AAppearance);
	void __fastcall GetDefaultHandlesAppearance(THandlesAppearance* AAppearance);
	Dgrclasses::TDgrGraphicLib __fastcall GetGraphicLib(void);
	void __fastcall SetGraphicLib(const Dgrclasses::TDgrGraphicLib Value);
	Diagramutils::TSquare __fastcall GetOriginalRect(void);
	void __fastcall SetOriginalRect(const Diagramutils::TSquare &Value);
	Gdipclasses::TGPBlockDrawer* __fastcall GetGPDrawer(void);
	__property TDControlPaintMode PaintMode = {read=FIntPaintMode, write=SetPaintMode, nodefault};
	bool __fastcall GetIsGdiPlus(void);
	void __fastcall SetIsGdiPlus(const bool Value);
	bool __fastcall GetPathDrawingMode(void);
	void __fastcall CheckGraphicLibObjects(void);
	Dgrclasses::TDgrBlockDrawerClass __fastcall DgrBlockDrawerClass(void);
	void __fastcall RestoreLayer(void);
	
protected:
	virtual void __fastcall HandleDestroyed(TStretchHandle* AHandle);
	virtual void __fastcall TextCellDestroyed(TTextCell* ACell);
	virtual void __fastcall RemoveAnchorsAfterMoving(void);
	virtual TLinkPoint* __fastcall LinkPointByHandle(TStretchHandle* AHandle);
	bool __fastcall HasAnchorableLinkPoints(void);
	virtual void __fastcall StartCursorPlacement(void);
	virtual void __fastcall EndCursorPlacement(void);
	virtual void __fastcall InitDgrDrawer(Dgrclasses::TDgrBlockDrawer* ADrawer);
	virtual void __fastcall InitDrawer(Diagramutils::TBlockDrawer* ADrawer);
	void __fastcall UpdateSelected(void);
	virtual void __fastcall TextCellsChanged(void);
	virtual void __fastcall HandlesChanged(void) = 0 ;
	virtual void __fastcall Loaded(void);
	void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall ClipRegion(Vcl::Graphics::TCanvas* Canvas, HRGN R);
	void __fastcall UnclipRegion(Vcl::Graphics::TCanvas* Canvas);
	virtual Diagramutils::TSquare __fastcall GetTextCellRect(TTextCell* ACell, const Diagramutils::TSquare &ARect);
	virtual void __fastcall WriteText(Vcl::Graphics::TCanvas* Canvas, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, const System::UnicodeString S, System::Classes::TAlignment HAlign, Diagramutils::TVertAlign VAlign, bool AWrap, double AAngle = 0.000000E+00, double CX = 0.000000E+00, double CY = 0.000000E+00, bool IgnoreZoom = false);
	Diagramutils::TSquare __fastcall CalculateTextRect(Vcl::Graphics::TCanvas* Canvas, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, const System::UnicodeString S, System::Classes::TAlignment HAlign, Diagramutils::TVertAlign VAlign, bool AWrap, double AAngle = 0.000000E+00, double CX = 0.000000E+00, double CY = 0.000000E+00, bool IgnoreZoom = false);
	virtual void __fastcall DoLinkAdded(TCustomDiagramLine* ALink, TLinkPoint* ALinkPoint);
	virtual void __fastcall DoLinkRemoved(TCustomDiagramLine* ALink, TLinkPoint* ALinkPoint);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall AngleChanged(void);
	virtual void __fastcall AngleChangedEx(double AOld, double ANew);
	Diagramutils::TDot __fastcall MovedLinkPoint(TLinkPoint* ALinkPoint, const Diagramutils::TDot &ADelta);
	void __fastcall NotifyAnchoreds(TAnchorChange AChange);
	virtual void __fastcall AnchorLinkChanged(TLinkPoint* ALinkPoint) = 0 ;
	virtual void __fastcall LinkedAnchorChanged(TLinkPoint* ALinkPoint, TAnchorChange AChange) = 0 ;
	virtual void __fastcall Redraw(void);
	virtual void __fastcall DrawCells(const TDiagramDrawInfo &AInfo);
	virtual void __fastcall DrawCell(const TDiagramDrawInfo &AInfo, TTextCell* ACell);
	virtual void __fastcall PaintControl(const TDiagramDrawInfo &AInfo) = 0 ;
	virtual bool __fastcall PointInControl(const System::Types::TPoint &Pos) = 0 ;
	virtual void __fastcall DblClick(void);
	virtual void __fastcall Click(void);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MouseDownEx(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y, TStretchHandle* &AHandle);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall MovePosition(double ADeltaX, double ADeltaY) = 0 ;
	virtual Diagramutils::TSquare __fastcall ControlRect(void) = 0 ;
	virtual Diagramutils::TSquare __fastcall SurroundRect(void) = 0 ;
	virtual void __fastcall StartMoving(void) = 0 ;
	virtual void __fastcall UpdateMoving(const TControlMoveInfo &AInfo) = 0 ;
	virtual void __fastcall UpdateInserting(const TControlInsertInfo &AInfo) = 0 ;
	virtual void __fastcall UpdateDrawing(const TControlDrawInfo &AInfo) = 0 ;
	virtual void __fastcall StartMovingHandle(void) = 0 ;
	virtual void __fastcall HandleMoving(const THandleMoveInfo &AInfo) = 0 ;
	virtual void __fastcall DrawHandles(const TDiagramDrawInfo &AInfo);
	virtual void __fastcall DrawHandle(const TDiagramDrawInfo &AInfo, TStretchHandle* AHandle);
	virtual Diagramutils::TDot __fastcall GetHandlePoint(TStretchHandle* AHandle);
	virtual Diagramutils::TDot __fastcall GetLinkPoint(TLinkPoint* ALinkPoint);
	virtual void __fastcall DiagramChanged(TatDiagram* Old, TatDiagram* New);
	DYNAMIC void __fastcall SetParentComponent(System::Classes::TComponent* AParent);
	virtual void __fastcall ReadState(System::Classes::TReader* Reader);
	virtual void __fastcall SelectedChanged(void);
	virtual TLinkPointClass __fastcall GetLinkPointClass(void);
	virtual void __fastcall CreateGraphicLibObjects(void);
	virtual void __fastcall DestroyGraphicLibObjects(void);
	Dgrclasses::TDgrGraphicsPath* __fastcall CreatePath(void);
	TDiagramDrawInfo __fastcall GetDiagramDrawInfo(void);
	__classmethod TDiagramDrawInfo __fastcall DiagramDrawInfo(Vcl::Graphics::TCanvas* ACanvas, Diagramutils::TBlockDrawer* ADrawer, Dgrclasses::TDgrBlockDrawer* ADgrDrawer);
	__property TInsertStyle InsertStyle = {read=FInsertStyle, write=FInsertStyle, nodefault};
	__property Diagramutils::TBlockDrawer* Drawer = {read=FDrawer};
	__property Diagramutils::TBlockDrawer* TempDrawer = {read=FTempDrawer};
	__property Gdipclasses::TGPBlockDrawer* GPDrawer = {read=GetGPDrawer};
	__property Dgrclasses::TDgrGraphicsPath* TempPath = {read=FTempPath};
	__property TStretchHandles* Handles = {read=FHandles, write=SetHandles};
	__property TLinkPoints* LinkPoints = {read=FLinkPoints, write=SetLinkPoints};
	__property Vcl::Graphics::TPen* LinkPointPen = {read=FLinkPointPen, write=SetLinkPointPen};
	__property Vcl::Graphics::TBrush* LinkPointBrush = {read=FLinkPointBrush, write=SetLinkPointBrush};
	__property TLinkPointStyle LinkPointStyle = {read=FLinkPointStyle, write=SetLinkPointStyle, nodefault};
	__property double Angle = {read=FAngle, write=SetAngle, stored=IsAngleStored};
	__property TDControlLinkEvent OnLinkAdded = {read=FOnLinkAdded, write=FOnLinkAdded};
	__property TDControlLinkEvent OnLinkRemoved = {read=FOnLinkRemoved, write=FOnLinkRemoved};
	__property bool IsGdiPlus = {read=GetIsGdiPlus, write=SetIsGdiPlus, nodefault};
	__property Dgrclasses::TDgrGraphicLib GraphicLib = {read=GetGraphicLib, write=SetGraphicLib, nodefault};
	__property bool PathDrawingMode = {read=GetPathDrawingMode, nodefault};
	__property Diagramutils::TSquare OriginalRect = {read=GetOriginalRect, write=SetOriginalRect};
	
public:
	__fastcall virtual TDiagramControl(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDiagramControl(void);
	DYNAMIC bool __fastcall HasParent(void);
	DYNAMIC System::Classes::TComponent* __fastcall GetParentComponent(void);
	bool __fastcall HasDefaultTextCell(void);
	TTextCell* __fastcall DefaultTextCell(void);
	void __fastcall BringToFront(void);
	void __fastcall SendToBack(void);
	void __fastcall EditText(void);
	virtual void __fastcall CalcSize(Vcl::Graphics::TCanvas* Canvas);
	void __fastcall MakeVisible(void);
	TTextCell* __fastcall SelectNextCell(TTextCell* ACell, bool AForward);
	__property TTextCells* TextCells = {read=FTextCells, write=SetTextCells};
	__property TControlRestrictions Restrictions = {read=FRestrictions, write=SetRestrictions, nodefault};
	__property bool Selected = {read=GetSelected, write=SetSelected, nodefault};
	__property TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
	__property System::UnicodeString DControlID = {read=GetDControlID, write=FDControlID};
	__property System::TObject* Obj = {read=FObj, write=FObj};
	__property System::UnicodeString Hint = {read=FHint, write=FHint};
	__property bool ShowHint = {read=FShowHint, write=SetShowHint, stored=IsShowHintStored, nodefault};
	__property bool ParentShowHint = {read=FParentShowHint, write=SetParentShowHint, nodefault};
	__property System::Uitypes::TCursor Cursor = {read=FCursor, write=FCursor, nodefault};
	__property Vcl::Graphics::TFont* Font = {read=FFont, write=SetFont, stored=IsFontStored};
	__property bool DiagramFont = {read=FDiagramFont, write=SetDiagramFont, nodefault};
	__property System::UnicodeString StringData = {read=FStringData, write=FStringData};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property int Layer = {read=GetLayerInteger, write=SetLayerInteger, nodefault};
	__property TDiagramLayer* LayerObj = {read=FLayerObj, write=SetLayerObj};
	__property System::UnicodeString LayerName = {read=GetLayerName, write=SetLayerName};
	__property bool AutoCreateLinkPoints = {read=FAutoCreateLinkPoints, write=FAutoCreateLinkPoints, nodefault};
	__property bool IsVisible = {read=GetIsVisible, nodefault};
	__property bool IsBackgroundControl = {read=FIsBackgroundControl, write=SetIsBackgroundControl, nodefault};
	__property int Transparency = {read=FTransparency, write=SetTransparency, nodefault};
	__property TGroupBlock* GroupBlock = {read=GetGroupBlock};
	__property TGroupBlock* MasterGroup = {read=GetMasterGroup};
	__property bool IsMember = {read=GetIsMember, nodefault};
	__property bool IsGroup = {read=GetIsGroup, nodefault};
	__property bool AsMember = {read=GetAsMember, nodefault};
};


class DELPHICLASS TDrawPoint;
class PASCALIMPLEMENTATION TDrawPoint : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	double FX;
	double FY;
	void __fastcall SetX(const double Value);
	void __fastcall SetY(const double Value);
	Diagramutils::TDot __fastcall GetP(void);
	void __fastcall SetP(const Diagramutils::TDot &Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property Diagramutils::TDot P = {read=GetP, write=SetP};
	
__published:
	__property double X = {read=FX, write=SetX};
	__property double Y = {read=FY, write=SetY};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TDrawPoint(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TDrawPoint(void) { }
	
};


class DELPHICLASS TDrawPoints;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDrawPoints : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TDrawPoint* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TDrawPoint* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TDrawPoint* __fastcall Add(void)/* overload */;
	HIDESBASE TDrawPoint* __fastcall Add(double AX, double AY)/* overload */;
	void __fastcall Append(TDrawPoints* APoints);
	__property TDrawPoint* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TDrawPoints(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDrawPoints(void) { }
	
};

#pragma pack(pop)

typedef System::TMetaClass* TDiagramControlClass;

class DELPHICLASS TTransMemo;
class PASCALIMPLEMENTATION TTransMemo : public Vcl::Stdctrls::TMemo
{
	typedef Vcl::Stdctrls::TMemo inherited;
	
private:
	MESSAGE void __fastcall WMTransMemoInvalidate(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMGetDlgCode(Winapi::Messages::TWMNoParams &Message);
	MESSAGE void __fastcall WMSetText(Winapi::Messages::TWMSetText &Message);
	MESSAGE void __fastcall CNCTLCOLOREDIT(Winapi::Messages::TWMCtlColor &Message);
	HIDESBASE MESSAGE void __fastcall WMKeyDown(Winapi::Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Winapi::Messages::TWMEraseBkgnd &Message);
	HIDESBASE MESSAGE void __fastcall WMHScroll(Winapi::Messages::TWMScroll &Message);
	HIDESBASE MESSAGE void __fastcall WMVScroll(Winapi::Messages::TWMScroll &Message);
	
protected:
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	
public:
	__fastcall virtual TTransMemo(System::Classes::TComponent* AOwner);
public:
	/* TCustomMemo.Destroy */ inline __fastcall virtual ~TTransMemo(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTransMemo(HWND ParentWindow) : Vcl::Stdctrls::TMemo(ParentWindow) { }
	
};


class DELPHICLASS TDiagramMemo;
class PASCALIMPLEMENTATION TDiagramMemo : public TTransMemo
{
	typedef TTransMemo inherited;
	
private:
	TatDiagram* FDiagram;
	TTextCell* FCell;
	bool FKeepPosition;
	void __fastcall UpdatePosition(void);
	int __fastcall CalculateHeight(void);
	TDiagramControl* __fastcall DControl(void);
	
protected:
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(System::WideChar &Key);
	DYNAMIC void __fastcall Change(void);
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Msg);
	
public:
	__fastcall virtual TDiagramMemo(System::Classes::TComponent* AOwner);
public:
	/* TCustomMemo.Destroy */ inline __fastcall virtual ~TDiagramMemo(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDiagramMemo(HWND ParentWindow) : TTransMemo(ParentWindow) { }
	
};


enum DECLSPEC_DENUM TBlockShape : unsigned char { bsNoShape, bsRectangle, bsEllipse, bsRoundRect, bsDiamond, bsSquareRound };

class DELPHICLASS TCustomDiagramBlock;
typedef void __fastcall (__closure *TGetSurroundPtsEvent)(System::TObject* Sender, TCustomDiagramBlock* ABlock, Diagramutils::TPointArray &APts);

typedef void __fastcall (__closure *TDrawBlockEvent)(System::TObject* Sender, TCustomDiagramBlock* ABlock, const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo, bool &APainted);

typedef Diagramutils::TPointArray TPointArray;

class DELPHICLASS TBlockShadow;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TBlockShadow : public TDiagramPersistent
{
	typedef TDiagramPersistent inherited;
	
private:
	bool FVisible;
	int FHOffset;
	int FVOffset;
	System::Uitypes::TColor FColor;
	int FTransparency;
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetHOffset(const int Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetVOffset(const int Value);
	void __fastcall SetTransparency(const int Value);
	
public:
	__fastcall TBlockShadow(TDiagramControl* ADControl);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property int HOffset = {read=FHOffset, write=SetHOffset, nodefault};
	__property int VOffset = {read=FVOffset, write=SetVOffset, nodefault};
	__property int Transparency = {read=FTransparency, write=SetTransparency, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TBlockShadow(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TBitmapMode : unsigned char { bmStretch, bmCenter, bmTile };

enum DECLSPEC_DENUM TPictureMode : unsigned char { pmStretch, pmCenter, pmTile };

class PASCALIMPLEMENTATION TCustomDiagramBlock : public TDiagramControl
{
	typedef TDiagramControl inherited;
	
private:
	double FHeight;
	double FWidth;
	double FLeft;
	double FTop;
	double FCursorAngle;
	Diagramutils::TSquare FCursorRect;
	Diagramutils::TDot FCursorRotCenter;
	TBlockShape FShape;
	Vcl::Graphics::TBrush* FBrush;
	Vcl::Graphics::TBrush* FSelBrush;
	Vcl::Graphics::TPen* FPen;
	System::Classes::TStrings* FStrings;
	bool FClipText;
	int FMinWidth;
	int FMinHeight;
	TBlockShadow* FShadow;
	TDiagramGradient* FGradient;
	Vcl::Graphics::TBitmap* FBitmap;
	TBitmapMode FBitmapMode;
	Dgrclasses::TDgrGraphic* FDgrBitmap;
	Dgrclasses::TDgrGraphic* FDgrMetafile;
	Dgrclasses::TDgrGraphic* FDgrPicture;
	TPictureMode FPictureMode;
	Vcl::Graphics::TMetafile* FMetafile;
	Vcl::Graphics::TPicture* FPicture;
	bool FShapeCursor;
	System::Uitypes::TColor FSelColor;
	System::Uitypes::TColor FColor;
	bool FTransparent;
	int FRotationStep;
	double FSaveAngle;
	Diagramutils::TSquare FSaveRect;
	Diagramutils::TDot FSaveRotCenter;
	Diagramutils::TDot FRotCenter;
	Diagramutils::TSquare __fastcall GetBoundsRect(void);
	void __fastcall SetBoundsRect(const Diagramutils::TSquare &Value);
	double __fastcall GetBottom(void);
	double __fastcall GetRight(void);
	void __fastcall SetHeight(const double Value);
	void __fastcall SetLeft(const double Value);
	void __fastcall SetTop(const double Value);
	void __fastcall SetWidth(const double Value);
	void __fastcall SetBounds(double ALeft, double ATop, double AWidth, double AHeight);
	void __fastcall SetShape(const TBlockShape Value);
	void __fastcall SetBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetPen(Vcl::Graphics::TPen* const Value);
	void __fastcall SetSelBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetStrings(System::Classes::TStrings* const Value);
	void __fastcall StringsChange(System::TObject* Sender);
	void __fastcall SetAlignment(const System::Classes::TAlignment Value);
	void __fastcall SetVertAlign(const Diagramutils::TVertAlign Value);
	void __fastcall SetClipText(const bool Value);
	void __fastcall SetWordWrap(const bool Value);
	void __fastcall SetMinHeight(const int Value);
	void __fastcall SetMinWidth(const int Value);
	Diagramutils::TSquare __fastcall ResizeNewRect(TStretchHandle* AHandle, double ADeltaX, double ADeltaY);
	double __fastcall RotateNewAngle(TStretchHandle* AHandle, double ADeltaX, double ADeltaY);
	Diagramutils::TSquare __fastcall RotateNewRect(TStretchHandle* AHandle, double ADeltaX, double ADeltaY);
	Diagramutils::TDot __fastcall CalcNewRotCenter(TStretchHandle* AHandle, double ADeltaX, double ADeltaY);
	Diagramutils::TSquare __fastcall MoveRectByDelta(const Diagramutils::TSquare &ARect, const Diagramutils::TDot &ADelta);
	void __fastcall SetShadow(TBlockShadow* const Value);
	void __fastcall SetGradient(TDiagramGradient* const Value);
	void __fastcall SetBitmap(Vcl::Graphics::TBitmap* const Value);
	void __fastcall DrawBitmap(void);
	void __fastcall SetMetafile(Vcl::Graphics::TMetafile* const Value);
	void __fastcall SetPicture(Vcl::Graphics::TPicture* const Value);
	void __fastcall DrawMetafile(void);
	void __fastcall DrawPicture(void);
	void __fastcall BitmapChange(System::TObject* Sender);
	void __fastcall MetafileChange(System::TObject* Sender);
	void __fastcall PictureChange(System::TObject* Sender);
	void __fastcall SetBitmapMode(const TBitmapMode Value);
	void __fastcall SetPictureMode(const TPictureMode Value);
	void __fastcall DoDrawShape(const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	void __fastcall SetRotateFont(const bool Value);
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetSelColor(const System::Uitypes::TColor Value);
	void __fastcall SetTransparent(const bool Value);
	System::Classes::TStrings* __fastcall GetStrings(void);
	System::Classes::TAlignment __fastcall GetAlignment(void);
	bool __fastcall GetRotateFont(void);
	Diagramutils::TVertAlign __fastcall GetVertAlign(void);
	bool __fastcall GetWordWrap(void);
	void __fastcall SetBitmapTransparent(const bool Value);
	bool __fastcall GetBitmapTransparent(void);
	void __fastcall LoadCollapsedNodesProp(System::Classes::TReader* Reader);
	void __fastcall StoreCollapsedNodesProp(System::Classes::TWriter* Writer);
	void __fastcall SetRotationStep(const int Value);
	System::Uitypes::TColor __fastcall CurrentColor(void);
	Vcl::Graphics::TBrush* __fastcall CurrentBrush(void);
	void __fastcall InternalDrawGraphic(Vcl::Graphics::TCanvas* Canvas, const Diagramutils::TSquare &ARect, Vcl::Graphics::TGraphic* AGraphic, double AAngle, TPictureMode AMode);
	void __fastcall InternalDrawGraphicDgr(Dgrclasses::TDgrBlockDrawer* ADrawer, const Diagramutils::TSquare &ARect, Vcl::Graphics::TGraphic* AGraphic, double AAngle, TPictureMode AMode, int ATransparency);
	void __fastcall DrawGraphic(Vcl::Graphics::TGraphic* AGraphic, TPictureMode AMode);
	void __fastcall SetRotationCenter(const Diagramutils::TDot &Value);
	Diagramutils::TDotArray __fastcall AngledSurroundRect(double AAngle);
	Diagramutils::TDot __fastcall TranslateRotCenter(const Diagramutils::TSquare &ARect, double AAngle, const Diagramutils::TDot &ARotCenter);
	
protected:
	void __fastcall ClipBlock(const TDiagramDrawInfo &AInfo);
	void __fastcall UnclipBlock(const TDiagramDrawInfo &AInfo);
	virtual Diagramutils::TDot __fastcall DiagramRotCenter(void);
	virtual void __fastcall PenChanged(void);
	virtual void __fastcall BoundsChanged(const Diagramutils::TSquare &AOld, const Diagramutils::TSquare &ANew);
	virtual void __fastcall StartCursorPlacement(void);
	virtual void __fastcall EndCursorPlacement(void);
	virtual void __fastcall InitDgrDrawer(Dgrclasses::TDgrBlockDrawer* ADrawer);
	virtual void __fastcall InitDrawer(Diagramutils::TBlockDrawer* ADrawer);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall Resize(void);
	virtual void __fastcall MouseEnter(void);
	virtual void __fastcall MouseLeave(void);
	Diagramutils::TDotArray __fastcall GetSurroundRgn(void);
	virtual void __fastcall HandlesChanged(void);
	virtual void __fastcall AnchorLinkChanged(TLinkPoint* ALinkPoint);
	virtual void __fastcall Loaded(void);
	virtual Diagramutils::TSquare __fastcall GetTextCellRect(TTextCell* ACell, const Diagramutils::TSquare &ARect);
	virtual void __fastcall LinkedAnchorChanged(TLinkPoint* ALinkPoint, TAnchorChange AChange);
	virtual void __fastcall AngleChanged(void);
	virtual void __fastcall PaintControl(const TDiagramDrawInfo &AInfo);
	virtual void __fastcall MovePosition(double ADeltaX, double ADeltaY);
	virtual Diagramutils::TSquare __fastcall ControlRect(void);
	virtual Diagramutils::TDotArray __fastcall SurroundRgn(void);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual void __fastcall GetSurroundBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual void __fastcall GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	virtual void __fastcall GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	virtual void __fastcall GetSurroundBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	virtual Diagramutils::TSquare __fastcall SurroundRect(void);
	HRGN __fastcall GetBlockClipRegion(void);
	virtual void __fastcall DrawBlockCursor(const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	virtual void __fastcall StartMoving(void);
	virtual void __fastcall UpdateMoving(const TControlMoveInfo &AInfo);
	virtual void __fastcall UpdateInserting(const TControlInsertInfo &AInfo);
	virtual void __fastcall UpdateDrawing(const TControlDrawInfo &AInfo);
	virtual void __fastcall StartMovingHandle(void);
	virtual void __fastcall HandleMoving(const THandleMoveInfo &AInfo);
	virtual Diagramutils::TDot __fastcall GetHandlePoint(TStretchHandle* AHandle);
	virtual Diagramutils::TDot __fastcall GetLinkPoint(TLinkPoint* ALinkPoint);
	virtual void __fastcall SelectedChanged(void);
	virtual void __fastcall DiagramChanged(TatDiagram* Old, TatDiagram* New);
	void __fastcall StyleChanged(System::TObject* Sender);
	virtual void __fastcall DrawHandles(const TDiagramDrawInfo &AInfo);
	virtual void __fastcall DrawShape(const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	void __fastcall DrawText(const TDiagramDrawInfo &AInfo);
	virtual void __fastcall DrawBlock(const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	virtual bool __fastcall AcceptOverlap(TCustomDiagramBlock* ABlock);
	virtual void __fastcall CreateGraphicLibObjects(void);
	virtual void __fastcall DestroyGraphicLibObjects(void);
	__classmethod TDiagramDrawBlockInfo __fastcall DiagramDrawBlockInfo(const Diagramutils::TSquare &ARect, double AAngle);
	__property bool ShapeCursor = {read=FShapeCursor, write=FShapeCursor, nodefault};
	__property double CursorAngle = {read=FCursorAngle, write=FCursorAngle};
	__property Diagramutils::TSquare CursorRect = {read=FCursorRect, write=FCursorRect};
	__property Diagramutils::TDot CursorRotCenter = {read=FCursorRotCenter, write=FCursorRotCenter};
	
public:
	__fastcall virtual TCustomDiagramBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDiagramBlock(void);
	virtual bool __fastcall PointInControl(const System::Types::TPoint &Pos);
	void __fastcall UpdateBlockHandles(void);
	void __fastcall DrawBlockInCanvas(Vcl::Graphics::TCanvas* Canvas, const System::Types::TRect &ARect);
	__property Diagramutils::TSquare BoundsRect = {read=GetBoundsRect, write=SetBoundsRect};
	__property double Right = {read=GetRight};
	__property double Bottom = {read=GetBottom};
	__property TBlockShape Shape = {read=FShape, write=SetShape, nodefault};
	__property Vcl::Graphics::TBrush* Brush = {read=FBrush, write=SetBrush};
	__property Vcl::Graphics::TBrush* SelBrush = {read=FSelBrush, write=SetSelBrush};
	__property Vcl::Graphics::TPen* Pen = {read=FPen, write=SetPen};
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property System::Uitypes::TColor SelColor = {read=FSelColor, write=SetSelColor, nodefault};
	__property System::Classes::TStrings* Strings = {read=GetStrings, write=SetStrings, stored=false};
	__property System::Classes::TAlignment Alignment = {read=GetAlignment, write=SetAlignment, stored=false, nodefault};
	__property Diagramutils::TVertAlign VertAlign = {read=GetVertAlign, write=SetVertAlign, stored=false, nodefault};
	__property bool WordWrap = {read=GetWordWrap, write=SetWordWrap, stored=false, nodefault};
	__property bool RotateFont = {read=GetRotateFont, write=SetRotateFont, stored=false, nodefault};
	__property bool ClipText = {read=FClipText, write=SetClipText, nodefault};
	__property int MinWidth = {read=FMinWidth, write=SetMinWidth, nodefault};
	__property int MinHeight = {read=FMinHeight, write=SetMinHeight, nodefault};
	__property TBlockShadow* Shadow = {read=FShadow, write=SetShadow};
	__property TDiagramGradient* Gradient = {read=FGradient, write=SetGradient};
	__property Vcl::Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property TBitmapMode BitmapMode = {read=FBitmapMode, write=SetBitmapMode, nodefault};
	__property bool BitmapTransparent = {read=GetBitmapTransparent, write=SetBitmapTransparent, nodefault};
	__property Vcl::Graphics::TMetafile* Metafile = {read=FMetafile, write=SetMetafile};
	__property Vcl::Graphics::TPicture* Picture = {read=FPicture, write=SetPicture};
	__property TPictureMode PictureMode = {read=FPictureMode, write=SetPictureMode, nodefault};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, nodefault};
	__property int RotationStep = {read=FRotationStep, write=SetRotationStep, nodefault};
	__property Diagramutils::TDot RotationCenter = {read=FRotCenter, write=SetRotationCenter};
	__property Selected;
	__property LinkPoints;
	__property Drawer;
	__property Angle = {default=0};
	__property Handles;
	
__published:
	__property double Left = {read=FLeft, write=SetLeft};
	__property double Top = {read=FTop, write=SetTop};
	__property double Width = {read=FWidth, write=SetWidth};
	__property double Height = {read=FHeight, write=SetHeight};
};


class DELPHICLASS TDiagramBlock;
class PASCALIMPLEMENTATION TDiagramBlock : public TCustomDiagramBlock
{
	typedef TCustomDiagramBlock inherited;
	
public:
	__fastcall virtual TDiagramBlock(System::Classes::TComponent* AOwner);
	
__published:
	__property Angle = {default=0};
	__property Brush;
	__property SelBrush;
	__property Color;
	__property SelColor;
	__property Pen;
	__property Shape;
	__property LinkPoints;
	__property Strings;
	__property Alignment;
	__property VertAlign;
	__property ClipText;
	__property WordWrap;
	__property TextCells;
	__property Restrictions;
	__property Font;
	__property DiagramFont;
	__property MinWidth;
	__property MinHeight;
	__property Shadow;
	__property ShowHint;
	__property ParentShowHint;
	__property Hint = {default=0};
	__property Gradient;
	__property Bitmap;
	__property BitmapMode;
	__property BitmapTransparent;
	__property Metafile;
	__property Picture;
	__property PictureMode;
	__property Transparent;
	__property Cursor;
	__property StringData = {default=0};
	__property Visible;
	__property Layer;
	__property LayerName = {default=0};
	__property Transparency;
public:
	/* TCustomDiagramBlock.Destroy */ inline __fastcall virtual ~TDiagramBlock(void) { }
	
};


class DELPHICLASS TPolygonPoint;
class PASCALIMPLEMENTATION TPolygonPoint : public TDrawPoint
{
	typedef TDrawPoint inherited;
	
private:
	TStretchHandle* FHandle;
	
public:
	__fastcall virtual ~TPolygonPoint(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property TStretchHandle* Handle = {read=FHandle};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TPolygonPoint(System::Classes::TCollection* Collection) : TDrawPoint(Collection) { }
	
};


class DELPHICLASS TPolygonPoints;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TPolygonPoints : public TDrawPoints
{
	typedef TDrawPoints inherited;
	
public:
	TPolygonPoint* operator[](int Index) { return Items[Index]; }
	
private:
	bool FDestroyObjects;
	HIDESBASE TPolygonPoint* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TPolygonPoint* const Value);
	TPolygonPoint* __fastcall FindByHandle(TStretchHandle* AHandle);
	Diagramutils::TDotArray __fastcall PointArray(void);
	
public:
	HIDESBASE TPolygonPoint* __fastcall Add(double AX, double AY)/* overload */;
	HIDESBASE TPolygonPoint* __fastcall Add(void)/* overload */;
	__property TPolygonPoint* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TPolygonPoints(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : TDrawPoints(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TPolygonPoints(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TCustomPolygonBlock;
class PASCALIMPLEMENTATION TCustomPolygonBlock : public TCustomDiagramBlock
{
	typedef TCustomDiagramBlock inherited;
	
private:
	TPolygonPoints* FPolygon;
	TPolygonPoints* FTempPolygon;
	TPolygonPoints* FCursorPolygon;
	TPolygonPoints* FSavePolygon;
	Diagramutils::TDot TempPolygonPoint;
	System::Uitypes::TColor FPointColor;
	void __fastcall PolygonChanged(void);
	void __fastcall UpdatePolygonHandles(void);
	Diagramutils::TSquare __fastcall BuildOriginalRect(TPolygonPoints* APolygon);
	void __fastcall UpdatePolygonLinkPoints(void);
	void __fastcall LoadPolygonProp(System::Classes::TReader* Reader);
	void __fastcall StorePolygonProp(System::Classes::TWriter* Writer);
	void __fastcall RepositionPolygon(TPolygonPoints* APolygon, const Diagramutils::TSquare &ANewRect);
	void __fastcall RotatePolygon(TPolygonPoints* APolygon, double AAngle, TPolygonPoints* ARotationBasePolygon = (TPolygonPoints*)(0x0));
	void __fastcall DrawOutlineCursor(Vcl::Graphics::TCanvas* ACanvas, TPolygonPoints* APolygon);
	Diagramutils::TDot __fastcall UpdateRotationCenter(const Diagramutils::TSquare &ANewRect);
	void __fastcall ChangeOriginalRect(const Diagramutils::TSquare &ARect);
	Diagramutils::TDot __fastcall CalcNewPolygonRotCenter(TStretchHandle* AHandle, double ADeltaX, double ADeltaY);
	void __fastcall SetPointColor(const System::Uitypes::TColor Value);
	
protected:
	virtual Diagramutils::TDot __fastcall GetHandlePoint(TStretchHandle* AHandle);
	virtual Diagramutils::TDot __fastcall DiagramRotCenter(void);
	virtual void __fastcall EndCursorPlacement(void);
	virtual void __fastcall StartCursorPlacement(void);
	virtual void __fastcall BoundsChanged(const Diagramutils::TSquare &AOld, const Diagramutils::TSquare &ANew);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual Diagramutils::TSquare __fastcall GetTextCellRect(TTextCell* ACell, const Diagramutils::TSquare &ARect);
	virtual void __fastcall HandleMoving(const THandleMoveInfo &AInfo);
	virtual void __fastcall UpdateMoving(const TControlMoveInfo &AInfo);
	virtual void __fastcall UpdateDrawing(const TControlDrawInfo &AInfo);
	virtual Diagramutils::TDotArray __fastcall SurroundRgn(void);
	virtual void __fastcall DrawShape(const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	void __fastcall CanvasPolygon(TPolygonPoints* APolygon);
	virtual void __fastcall DrawHandle(const TDiagramDrawInfo &AInfo, TStretchHandle* AHandle);
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TCustomPolygonBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomPolygonBlock(void);
	__property TPolygonPoints* Polygon = {read=FPolygon};
	void __fastcall ChangePolygon(TPolygonPoints* APolygon);
	__property System::Uitypes::TColor PointColor = {read=FPointColor, write=SetPointColor, default=65280};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


class DELPHICLASS TPolygonBlock;
class PASCALIMPLEMENTATION TPolygonBlock : public TCustomPolygonBlock
{
	typedef TCustomPolygonBlock inherited;
	
__published:
	__property Angle = {default=0};
	__property Brush;
	__property SelBrush;
	__property Color;
	__property SelColor;
	__property Pen;
	__property LinkPoints;
	__property Strings;
	__property Alignment;
	__property VertAlign;
	__property ClipText;
	__property WordWrap;
	__property TextCells;
	__property Restrictions;
	__property Font;
	__property DiagramFont;
	__property MinWidth;
	__property MinHeight;
	__property Shadow;
	__property ShowHint;
	__property ParentShowHint;
	__property Hint = {default=0};
	__property Gradient;
	__property Bitmap;
	__property BitmapMode;
	__property BitmapTransparent;
	__property Metafile;
	__property Picture;
	__property PictureMode;
	__property Transparent;
	__property Cursor;
	__property StringData = {default=0};
	__property Transparency;
	__property PointColor = {default=65280};
	__property LayerName = {default=0};
public:
	/* TCustomPolygonBlock.Create */ inline __fastcall virtual TPolygonBlock(System::Classes::TComponent* AOwner) : TCustomPolygonBlock(AOwner) { }
	/* TCustomPolygonBlock.Destroy */ inline __fastcall virtual ~TPolygonBlock(void) { }
	
};


class DELPHICLASS TDiagramLineJoin;
class PASCALIMPLEMENTATION TDiagramLineJoin : public TCustomDiagramBlock
{
	typedef TCustomDiagramBlock inherited;
	
private:
	Diagramutils::TDot FOldAnchorPos;
	TDiagramControl* __fastcall GetAnchor(void);
	int __fastcall GetAnchorIndex(void);
	void __fastcall SetAnchor(TDiagramControl* const Value);
	void __fastcall SetAnchorIndex(const int Value);
	TAnchorOrientation __fastcall GetOrientation(void);
	void __fastcall SetOrientation(const TAnchorOrientation Value);
	
public:
	__fastcall virtual TDiagramLineJoin(System::Classes::TComponent* AOwner);
	virtual void __fastcall AnchorLinkChanged(TLinkPoint* ALinkPoint);
	virtual void __fastcall LinkedAnchorChanged(TLinkPoint* ALinkPoint, TAnchorChange AChange);
	
__published:
	__property Brush;
	__property SelBrush;
	__property Color;
	__property SelColor;
	__property Pen;
	__property TDiagramControl* Anchor = {read=GetAnchor, write=SetAnchor};
	__property int AnchorIndex = {read=GetAnchorIndex, write=SetAnchorIndex, nodefault};
	__property TAnchorOrientation Orientation = {read=GetOrientation, write=SetOrientation, nodefault};
public:
	/* TCustomDiagramBlock.Destroy */ inline __fastcall virtual ~TDiagramLineJoin(void) { }
	
};


class DELPHICLASS TTextBlock;
class PASCALIMPLEMENTATION TTextBlock : public TCustomDiagramBlock
{
	typedef TCustomDiagramBlock inherited;
	
public:
	__fastcall virtual TTextBlock(System::Classes::TComponent* AOwner);
	
__published:
	__property Angle = {default=0};
	__property Brush;
	__property SelBrush;
	__property Color;
	__property SelColor;
	__property Pen;
	__property Shape;
	__property LinkPoints;
	__property Strings;
	__property Alignment;
	__property VertAlign;
	__property ClipText;
	__property WordWrap;
	__property TextCells;
	__property Restrictions;
	__property Font;
	__property DiagramFont;
	__property MinWidth;
	__property MinHeight;
	__property Shadow;
	__property ShowHint;
	__property ParentShowHint;
	__property Hint = {default=0};
	__property Gradient;
	__property Bitmap;
	__property BitmapMode;
	__property BitmapTransparent;
	__property Metafile;
	__property Picture;
	__property PictureMode;
	__property Transparent;
	__property Cursor;
	__property StringData = {default=0};
	__property Visible;
	__property Layer;
	__property LayerName = {default=0};
	__property Transparency;
public:
	/* TCustomDiagramBlock.Destroy */ inline __fastcall virtual ~TTextBlock(void) { }
	
};


enum DECLSPEC_DENUM TArrowShape : unsigned char { asNone, asSolidArrow, asLineArrow, asDiamond, asRectangle, asEllipse, asHalfLine, asAngledDiamond };

class DELPHICLASS TLineArrow;
class PASCALIMPLEMENTATION TLineArrow : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TArrowShape FShape;
	int FHeight;
	int FWidth;
	Vcl::Graphics::TBrush* FBrush;
	TCustomDiagramLine* FDiagramLine;
	Diagramutils::TDot FDrawFrom;
	Diagramutils::TDot FDrawTo;
	void __fastcall SetShape(const TArrowShape Value);
	void __fastcall SetBrush(Vcl::Graphics::TBrush* const Value);
	void __fastcall SetHeight(const int Value);
	void __fastcall SetWidth(const int Value);
	
protected:
	void __fastcall Changed(void);
	void __fastcall StyleChanged(System::TObject* Sender);
	__property Diagramutils::TDot DrawFrom = {read=FDrawFrom, write=FDrawFrom};
	__property Diagramutils::TDot DrawTo = {read=FDrawTo, write=FDrawTo};
	virtual void __fastcall Draw(const TDiagramDrawInfo &AInfo, const TDiagramDrawArrowInfo &AArrowInfo);
	__classmethod TDiagramDrawArrowInfo __fastcall DiagramDrawArrowInfo(const Diagramutils::TDot &AFromPoint, const Diagramutils::TDot &AToPoint, double AZoomRatio);
	
public:
	__fastcall TLineArrow(TCustomDiagramLine* ADiagramLink);
	__fastcall virtual ~TLineArrow(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall RestoreDefaults(void);
	__property TCustomDiagramLine* DiagramLine = {read=FDiagramLine};
	
__published:
	__property TArrowShape Shape = {read=FShape, write=SetShape, nodefault};
	__property int Width = {read=FWidth, write=SetWidth, nodefault};
	__property int Height = {read=FHeight, write=SetHeight, nodefault};
	__property Vcl::Graphics::TBrush* Brush = {read=FBrush, write=SetBrush};
};


enum DECLSPEC_DENUM TCalcHandlesAction : unsigned char { chNone, chInsert, chMove, chHandleMove, chAnchorChanged };

struct DECLSPEC_DRECORD TCalcHandlesInfo
{
public:
	Diagramutils::TDot P1;
	Diagramutils::TDot P2;
	TLinkPoint* Anchor1;
	TLinkPoint* Anchor2;
	TStretchHandle* HandleMoved;
	Diagramutils::TDot DeltaMove;
	TCalcHandlesAction Action;
};


enum DECLSPEC_DENUM TTextCellsMode : unsigned char { tmSegments, tmSingle, tmManual, tmSpecific };

enum DECLSPEC_DENUM TDiagramLineStyle : unsigned char { lsLine, lsSideLine, lsParabolicArc, lsCircularArc, lsBezier };

typedef System::TMetaClass* TLineArrowClass;

class PASCALIMPLEMENTATION TCustomDiagramLine : public TDiagramControl
{
	typedef TDiagramControl inherited;
	
private:
	Diagramutils::TDotArray FPoints;
	Vcl::Graphics::TPen* FPen;
	Vcl::Graphics::TPen* FSelPen;
	TLineArrow* FSourceArrow;
	TLineArrow* FTargetArrow;
	TStretchHandles* FTempHandles;
	TTextCellsMode FTextCellsMode;
	bool FRequiresConnections;
	TTextCell* FCenterTextCell;
	TTextCell* FSourceTextCell;
	TTextCell* FTargetTextCell;
	TTextCell* FAltSourceTextCell;
	TTextCell* FAltTargetTextCell;
	TAnchorOrientation FOrientation1;
	TAnchorOrientation FOrientation2;
	TDiagramLineStyle FLineStyle;
	bool FRecalcIntermediateArcHandles;
	bool __fastcall FixedSideLine(void);
	void __fastcall SetOrientation1(const TAnchorOrientation Value);
	void __fastcall SetOrientation2(const TAnchorOrientation Value);
	void __fastcall AddFPoint(double X, double Y);
	void __fastcall SetPen(Vcl::Graphics::TPen* const Value);
	void __fastcall StyleChanged(System::TObject* Sender);
	void __fastcall SetSourceArrow(TLineArrow* const Value);
	void __fastcall SetTargetArrow(TLineArrow* const Value);
	void __fastcall SetSelPen(Vcl::Graphics::TPen* const Value);
	TStretchHandle* __fastcall HandleByLinkPoint(TLinkPoint* ALinkPoint);
	void __fastcall CheckHandles(void);
	void __fastcall LoadHandlesProp(System::Classes::TReader* Reader);
	void __fastcall LoadLinkPointsProp(System::Classes::TReader* Reader);
	void __fastcall StoreHandlesProp(System::Classes::TWriter* Writer);
	void __fastcall StoreLinkPointsProp(System::Classes::TWriter* Writer);
	TLinkPoint* __fastcall GetSourceLinkPoint(void);
	TLinkPoint* __fastcall GetTargetLinkPoint(void);
	void __fastcall SetTextCellsMode(const TTextCellsMode Value);
	void __fastcall DestroySpecificTextCells(void);
	void __fastcall CreateSpecificTextCells(void);
	void __fastcall PositionEndCell(TTextCell* ACell, const Diagramutils::TDot &AFrom, const Diagramutils::TDot &ATo, bool ANormal);
	void __fastcall PositionCenterCell(TTextCell* ACell);
	void __fastcall SetLineStyle(TDiagramLineStyle Value);
	void __fastcall RecalcBezierPoints(TStretchHandles* AHandles);
	void __fastcall CalcLineNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	void __fastcall CalcSideLineNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	void __fastcall CalcArcNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	void __fastcall CalcBezierNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	void __fastcall RecalcLinePoints(TStretchHandles* AHandles);
	void __fastcall RecalcSideLinePoints(TStretchHandles* AHandles);
	void __fastcall RecalcArcPoints(TStretchHandles* AHandles);
	
protected:
	bool __fastcall IsSideLine(void);
	virtual void __fastcall TextCellDestroyed(TTextCell* ACell);
	void __fastcall InvertOrientation(void);
	void __fastcall UpdateOrientations(void);
	void __fastcall CheckLinkPoints(void);
	virtual void __fastcall PenChanged(void);
	virtual void __fastcall SelPenChanged(void);
	virtual void __fastcall StartCursorPlacement(void);
	virtual void __fastcall EndCursorPlacement(void);
	virtual void __fastcall DrawLine(const TDiagramDrawInfo &AInfo, const TDiagramDrawLineInfo &ALineInfo);
	virtual TLinkPoint* __fastcall LinkPointByHandle(TStretchHandle* AHandle);
	void __fastcall DrawLineCursor(Vcl::Graphics::TCanvas* Canvas, TStretchHandles* AHandles);
	virtual void __fastcall RecalcTextCells(void);
	virtual void __fastcall HandlesChanged(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall CalcNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	virtual void __fastcall RecalcPoints(TStretchHandles* AHandles);
	virtual void __fastcall AnchorLinkChanged(TLinkPoint* ALinkPoint);
	virtual void __fastcall RecalcAnchors(void);
	virtual void __fastcall RecalcHandles(void);
	virtual void __fastcall LinkedAnchorChanged(TLinkPoint* ALinkPoint, TAnchorChange AChange);
	virtual void __fastcall DiagramChanged(TatDiagram* Old, TatDiagram* New);
	virtual Diagramutils::TDot __fastcall GetLinkPoint(TLinkPoint* ALinkPoint);
	virtual void __fastcall PaintControl(const TDiagramDrawInfo &AInfo);
	virtual void __fastcall StartMovingHandle(void);
	virtual void __fastcall HandleMoving(const THandleMoveInfo &AInfo);
	virtual void __fastcall StartMoving(void);
	virtual void __fastcall UpdateMoving(const TControlMoveInfo &AInfo);
	virtual void __fastcall UpdateInserting(const TControlInsertInfo &AInfo);
	virtual void __fastcall UpdateDrawing(const TControlDrawInfo &AInfo);
	virtual void __fastcall SelectedChanged(void);
	virtual void __fastcall MovePosition(double ADeltaX, double ADeltaY);
	Vcl::Graphics::TPen* __fastcall CurPen(void);
	virtual TLineArrowClass __fastcall GetLineArrowClass(void);
	__classmethod TDiagramDrawLineInfo __fastcall DiagramDrawLineInfo(TStretchHandles* AHandles, bool ADrawArrows);
	__property TTextCellsMode TextCellsMode = {read=FTextCellsMode, write=SetTextCellsMode, nodefault};
	__property TTextCell* SourceTextCell = {read=FSourceTextCell};
	__property TTextCell* TargetTextCell = {read=FTargetTextCell};
	__property TTextCell* AltSourceTextCell = {read=FAltSourceTextCell};
	__property TTextCell* AltTargetTextCell = {read=FAltTargetTextCell};
	__property TTextCell* CenterTextCell = {read=FCenterTextCell};
	__property TAnchorOrientation Orientation1 = {read=FOrientation1, write=SetOrientation1, nodefault};
	__property TAnchorOrientation Orientation2 = {read=FOrientation2, write=SetOrientation2, nodefault};
	
public:
	virtual Diagramutils::TSquare __fastcall ControlRect(void);
	virtual Diagramutils::TSquare __fastcall SurroundRect(void);
	virtual bool __fastcall PointInControl(const System::Types::TPoint &Pos);
	__fastcall virtual TCustomDiagramLine(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDiagramLine(void);
	__property TDiagramLineStyle LineStyle = {read=FLineStyle, write=SetLineStyle, nodefault};
	__property Handles;
	__property Diagramutils::TDotArray Points = {read=FPoints, write=FPoints};
	__property TLinkPoint* TargetLinkPoint = {read=GetTargetLinkPoint};
	__property TLinkPoint* SourceLinkPoint = {read=GetSourceLinkPoint};
	__property Selected;
	__property Vcl::Graphics::TPen* Pen = {read=FPen, write=SetPen};
	__property Vcl::Graphics::TPen* SelPen = {read=FSelPen, write=SetSelPen};
	__property TLineArrow* SourceArrow = {read=FSourceArrow, write=SetSourceArrow};
	__property TLineArrow* TargetArrow = {read=FTargetArrow, write=SetTargetArrow};
	__property bool RequiresConnections = {read=FRequiresConnections, write=FRequiresConnections, nodefault};
};


typedef System::TMetaClass* TCustomDiagramLineClass;

class DELPHICLASS TBaseDiagramLine;
class PASCALIMPLEMENTATION TBaseDiagramLine : public TCustomDiagramLine
{
	typedef TCustomDiagramLine inherited;
	
public:
	__property Selected;
	
__published:
	__property Pen;
	__property SelPen;
	__property SourceArrow;
	__property TargetArrow;
	__property Cursor;
	__property TextCells;
	__property Font;
	__property StringData = {default=0};
	__property Visible;
	__property Layer;
	__property LayerName = {default=0};
	__property Transparency;
	__property LineStyle;
	__property Orientation1 = {stored=IsSideLine};
	__property Orientation2 = {stored=IsSideLine};
public:
	/* TCustomDiagramLine.Create */ inline __fastcall virtual TBaseDiagramLine(System::Classes::TComponent* AOwner) : TCustomDiagramLine(AOwner) { }
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TBaseDiagramLine(void) { }
	
};


class DELPHICLASS TDiagramLine;
class PASCALIMPLEMENTATION TDiagramLine : public TBaseDiagramLine
{
	typedef TBaseDiagramLine inherited;
	
public:
	/* TCustomDiagramLine.Create */ inline __fastcall virtual TDiagramLine(System::Classes::TComponent* AOwner) : TBaseDiagramLine(AOwner) { }
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TDiagramLine(void) { }
	
};


class DELPHICLASS TDiagramPolyLine;
class PASCALIMPLEMENTATION TDiagramPolyLine : public TDiagramLine
{
	typedef TDiagramLine inherited;
	
protected:
	virtual void __fastcall CalcNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	virtual void __fastcall UpdateDrawing(const TControlDrawInfo &AInfo);
	
public:
	__fastcall virtual TDiagramPolyLine(System::Classes::TComponent* AOwner);
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TDiagramPolyLine(void) { }
	
};


class DELPHICLASS TDiagramSideLine;
class PASCALIMPLEMENTATION TDiagramSideLine : public TBaseDiagramLine
{
	typedef TBaseDiagramLine inherited;
	
public:
	__fastcall virtual TDiagramSideLine(System::Classes::TComponent* AOwner);
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TDiagramSideLine(void) { }
	
};


enum DECLSPEC_DENUM TArcType : unsigned char { atParabolic, atCircular };

class DELPHICLASS TDiagramArc;
class PASCALIMPLEMENTATION TDiagramArc : public TBaseDiagramLine
{
	typedef TBaseDiagramLine inherited;
	
private:
	TArcType FArcType;
	void __fastcall SetArcType(const TArcType Value);
	
public:
	__fastcall virtual TDiagramArc(System::Classes::TComponent* AOwner);
	
__published:
	__property TArcType ArcType = {read=FArcType, write=SetArcType, nodefault};
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TDiagramArc(void) { }
	
};


class DELPHICLASS TDiagramBezier;
class PASCALIMPLEMENTATION TDiagramBezier : public TBaseDiagramLine
{
	typedef TBaseDiagramLine inherited;
	
public:
	__fastcall virtual TDiagramBezier(System::Classes::TComponent* AOwner);
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TDiagramBezier(void) { }
	
};


class DELPHICLASS TDiagramPolyBezier;
class PASCALIMPLEMENTATION TDiagramPolyBezier : public TDiagramPolyLine
{
	typedef TDiagramPolyLine inherited;
	
protected:
	virtual void __fastcall UpdateDrawing(const TControlDrawInfo &AInfo);
	virtual void __fastcall CalcNewHandles(TStretchHandles* AHandles, const TCalcHandlesInfo &AInfo);
	virtual void __fastcall RecalcPoints(TStretchHandles* AHandles);
	
public:
	__fastcall virtual TDiagramPolyBezier(System::Classes::TComponent* AOwner);
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TDiagramPolyBezier(void) { }
	
};


enum DECLSPEC_DENUM TGridStyle : unsigned char { gsDots, gsLines, gsRuler };

class DELPHICLASS TSnapGrid;
class PASCALIMPLEMENTATION TSnapGrid : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FForce;
	bool FActive;
	bool FVisible;
	double FSizeX;
	double FSizeY;
	TatDiagram* FDiagram;
	Vcl::Graphics::TPen* FPen;
	TGridStyle FStyle;
	bool FSnapToRuler;
	void __fastcall SetActive(const bool Value);
	void __fastcall SetSizeX(const double Value);
	void __fastcall SetSizeY(const double Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetPen(Vcl::Graphics::TPen* const Value);
	void __fastcall StyleChanged(System::TObject* Sender);
	void __fastcall SetStyle(const TGridStyle Value);
	void __fastcall SetSnapToRuler(const bool Value);
	
protected:
	void __fastcall Changed(void);
	void __fastcall Draw(Vcl::Graphics::TCanvas* Canvas);
	void __fastcall UpdateSize(void);
	
public:
	__fastcall TSnapGrid(TatDiagram* ADiagram);
	__fastcall virtual ~TSnapGrid(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property bool Force = {read=FForce, write=FForce, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property double SizeX = {read=FSizeX, write=SetSizeX};
	__property double SizeY = {read=FSizeY, write=SetSizeY};
	__property TGridStyle Style = {read=FStyle, write=SetStyle, nodefault};
	__property Vcl::Graphics::TPen* Pen = {read=FPen, write=SetPen};
	__property bool SnapToRuler = {read=FSnapToRuler, write=SetSnapToRuler, nodefault};
};


enum DECLSPEC_DENUM TBackImageStyle : unsigned char { biTile, biFixed };

class DELPHICLASS TDiagramBackground;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramBackground : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	Vcl::Graphics::TPicture* FPicture;
	TatDiagram* FDiagram;
	Vcl::Graphics::TBitmap* FBitmap;
	TBackImageStyle FStyle;
	bool FScroll;
	bool FVisible;
	TDiagramGradient* FGradient;
	bool FPrintGradient;
	void __fastcall SetBitmap(Vcl::Graphics::TBitmap* const Value);
	void __fastcall BitmapChange(System::TObject* Sender);
	void __fastcall PictureChange(System::TObject* Sender);
	void __fastcall SetStyle(const TBackImageStyle Value);
	void __fastcall Changed(void);
	void __fastcall SetScroll(const bool Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetGradient(TDiagramGradient* const Value);
	void __fastcall SetPicture(Vcl::Graphics::TPicture* const Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall TDiagramBackground(TatDiagram* ADiagram);
	__fastcall virtual ~TDiagramBackground(void);
	void __fastcall Draw(Vcl::Graphics::TCanvas* Canvas);
	
__published:
	__property Vcl::Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property Vcl::Graphics::TPicture* Picture = {read=FPicture, write=SetPicture};
	__property bool Scroll = {read=FScroll, write=SetScroll, nodefault};
	__property TBackImageStyle Style = {read=FStyle, write=SetStyle, nodefault};
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property TDiagramGradient* Gradient = {read=FGradient, write=SetGradient};
	__property bool PrintGradient = {read=FPrintGradient, write=FPrintGradient, nodefault};
};

#pragma pack(pop)

enum DECLSPEC_DENUM TRulerUnits : unsigned char { unMili, unCenti, unInch, unPixel };

enum DECLSPEC_DENUM TRulerPosition : unsigned char { rpTop, rpLeft };

class DELPHICLASS TCustomRuler;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TCustomRuler : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FZoom;
	TRulerUnits FUnits;
	Vcl::Graphics::TFont* FFont;
	HFONT FFont0;
	HFONT FFont90;
	int FOffset;
	int FMajorTickLength;
	int FMinorTickLength;
	TRulerPosition FPosition;
	int FDivisions;
	System::Uitypes::TColor FColor;
	int FSize;
	System::Uitypes::TColor FTickColor;
	bool FAutoFactor;
	System::Uitypes::TColor FGridColor;
	void __fastcall SetUnits(const TRulerUnits Value);
	void __fastcall SetZoom(const int Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall DeleteFonts(void);
	void __fastcall UpdateFonts(void);
	void __fastcall SetMajorTickLength(const int Value);
	void __fastcall SetMinorTickLength(const int Value);
	void __fastcall SetPosition(const TRulerPosition Value);
	void __fastcall SetDivisions(const int Value);
	void __fastcall UpdateDivisions(void);
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall FontChanged(System::TObject* Sender);
	void __fastcall SetSize(const int Value);
	void __fastcall SetTickColor(const System::Uitypes::TColor Value);
	void __fastcall GetStepAndFactor(double &AStep, double &AFactor);
	double __fastcall RulerStep(void);
	void __fastcall SetAutoFactor(const bool Value);
	void __fastcall SetGridColor(const System::Uitypes::TColor Value);
	__property System::Uitypes::TColor GridColor = {read=FGridColor, write=SetGridColor, nodefault};
	
protected:
	virtual TRulerUnits __fastcall GetUnits(void);
	virtual void __fastcall Changed(void);
	virtual void __fastcall UpdateSize(int ASize);
	virtual int __fastcall ScreenDPI(void);
	__property int Divisions = {read=FDivisions, write=SetDivisions, nodefault};
	__property Vcl::Graphics::TFont* Font = {read=FFont, write=SetFont};
	__property int Zoom = {read=FZoom, write=SetZoom, nodefault};
	__property TRulerUnits Units = {read=GetUnits, write=SetUnits, nodefault};
	__property int MinorTickLength = {read=FMinorTickLength, write=SetMinorTickLength, nodefault};
	__property int MajorTickLength = {read=FMajorTickLength, write=SetMajorTickLength, nodefault};
	__property TRulerPosition Position = {read=FPosition, write=SetPosition, nodefault};
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property System::Uitypes::TColor TickColor = {read=FTickColor, write=SetTickColor, nodefault};
	__property int Size = {read=FSize, write=SetSize, nodefault};
	__property int Offset = {read=FOffset, write=FOffset, nodefault};
	__property bool AutoFactor = {read=FAutoFactor, write=SetAutoFactor, nodefault};
	
public:
	__fastcall TCustomRuler(void);
	__fastcall virtual ~TCustomRuler(void);
	void __fastcall Draw(Vcl::Graphics::TCanvas* Canvas, const System::Types::TRect &ARect, int TempOffset = 0x0, int MaxSize = 0x0, bool ADrawGrid = false);
};

#pragma pack(pop)

class DELPHICLASS TDiagramRuler;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramRuler : public TCustomRuler
{
	typedef TCustomRuler inherited;
	
private:
	TatDiagram* FDiagram;
	bool FVisible;
	void __fastcall SetVisible(const bool Value);
	
protected:
	virtual TRulerUnits __fastcall GetUnits(void);
	virtual void __fastcall UpdateSize(int ASize);
	virtual void __fastcall Changed(void);
	virtual int __fastcall ScreenDPI(void);
	
public:
	__fastcall TDiagramRuler(TatDiagram* ADiagram);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	int __fastcall VisibleSize(void);
	
__published:
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property Divisions;
	__property Font;
	__property Units;
	__property MinorTickLength;
	__property MajorTickLength;
	__property Color;
	__property TickColor;
	__property Size;
	__property AutoFactor;
	__property GridColor;
public:
	/* TCustomRuler.Destroy */ inline __fastcall virtual ~TDiagramRuler(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TDiagramScrollBar;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramScrollBar : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TatDiagram* FDiagram;
	Vcl::Forms::TScrollBarInc FIncrement;
	Vcl::Forms::TScrollBarInc FPageIncrement;
	int FPosition;
	int FRange;
	int FCalcRange;
	Vcl::Forms::TScrollBarKind FKind;
	System::Word FMargin;
	bool FVisible;
	bool FTracking;
	bool FSmooth;
	int FDelay;
	System::Uitypes::TColor FColor;
	bool FParentColor;
	int FSize;
	Vcl::Forms::TScrollBarStyle FStyle;
	int FThumbSize;
	int FPageDiv;
	int FLineDiv;
	bool FUpdateNeeded;
	
protected:
	__fastcall TDiagramScrollBar(TatDiagram* ADiagram, Vcl::Forms::TScrollBarKind AKind);
	
private:
	int __fastcall ControlSize(bool ControlSB, bool AssumeSB);
	void __fastcall DoSetRange(int Value);
	int __fastcall GetScrollPos(void);
	bool __fastcall NeedsScrollBarVisible(void);
	bool __fastcall IsIncrementStored(void);
	void __fastcall ScrollMessage(Winapi::Messages::TWMScroll &Msg);
	void __fastcall SetColor(System::Uitypes::TColor Value);
	void __fastcall SetParentColor(bool Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetRange(int Value);
	void __fastcall SetSize(int Value);
	void __fastcall SetStyle(Vcl::Forms::TScrollBarStyle Value);
	void __fastcall SetThumbSize(int Value);
	void __fastcall SetVisible(bool Value);
	void __fastcall Update(bool ControlSB, bool AssumeSB);
	bool __fastcall IsRangeStored(void);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall ChangeBiDiPosition(void);
	__property Vcl::Forms::TScrollBarKind Kind = {read=FKind, nodefault};
	bool __fastcall IsScrollBarVisible(void);
	__property int ScrollPos = {read=GetScrollPos, nodefault};
	
__published:
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, default=-16777196};
	__property Vcl::Forms::TScrollBarInc Increment = {read=FIncrement, write=FIncrement, stored=IsIncrementStored, default=8};
	__property System::Word Margin = {read=FMargin, write=FMargin, default=0};
	__property bool ParentColor = {read=FParentColor, write=SetParentColor, default=1};
	__property int Position = {read=FPosition, write=SetPosition, default=0};
	__property int Range = {read=FRange, write=SetRange, stored=IsRangeStored, default=0};
	__property bool Smooth = {read=FSmooth, write=FSmooth, default=0};
	__property int Size = {read=FSize, write=SetSize, default=0};
	__property Vcl::Forms::TScrollBarStyle Style = {read=FStyle, write=SetStyle, default=0};
	__property int ThumbSize = {read=FThumbSize, write=SetThumbSize, default=0};
	__property bool Tracking = {read=FTracking, write=FTracking, default=0};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDiagramScrollBar(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TPageLines;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TPageLines : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	bool FVisible;
	TatDiagram* FDiagram;
	Vcl::Graphics::TPen* FPen;
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetPen(Vcl::Graphics::TPen* const Value);
	void __fastcall StyleChanged(System::TObject* Sender);
	
protected:
	void __fastcall Changed(void);
	void __fastcall Draw(Vcl::Graphics::TCanvas* Canvas);
	
public:
	__fastcall TPageLines(TatDiagram* ADiagram);
	__fastcall virtual ~TPageLines(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool Visible = {read=FVisible, write=SetVisible, nodefault};
	__property Vcl::Graphics::TPen* Pen = {read=FPen, write=SetPen};
};

#pragma pack(pop)

class DELPHICLASS TDControlListItem;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDControlListItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TDiagramControl* FDControl;
	void __fastcall SetDControl(TDiagramControl* const Value);
	void __fastcall MemberRemoved(TDiagramControl* ADControl);
	void __fastcall MemberIncluded(TDiagramControl* ADControl);
	
public:
	__fastcall virtual ~TDControlListItem(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TDiagramControl* DControl = {read=FDControl, write=SetDControl};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TDControlListItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	
};

#pragma pack(pop)

class DELPHICLASS TDControlList;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDControlList : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TDControlListItem* operator[](int Index) { return Items[Index]; }
	
private:
	TDControlListItem* __fastcall GetItems(int Index);
	void __fastcall SetItems(int Index, TDControlListItem* AItem);
	TDControlListItem* __fastcall FindByDControl(TDiagramControl* ADControl);
	
protected:
	virtual void __fastcall MemberIncluded(TDiagramControl* ADControl);
	virtual void __fastcall MemberRemoved(TDiagramControl* ADControl);
	
public:
	HIDESBASE TDControlListItem* __fastcall Add(TDiagramControl* ADControl);
	void __fastcall Remove(TDiagramControl* ADControl);
	__property TDControlListItem* Items[int Index] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TDControlList(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDControlList(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGroupMemberList;
class DELPHICLASS TBaseGroupBlock;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGroupMemberList : public TDControlList
{
	typedef TDControlList inherited;
	
private:
	TBaseGroupBlock* FGroup;
	
protected:
	virtual void __fastcall MemberIncluded(TDiagramControl* ADControl);
	virtual void __fastcall MemberRemoved(TDiagramControl* ADControl);
public:
	/* TOwnedCollection.Create */ inline __fastcall TGroupMemberList(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : TDControlList(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TGroupMemberList(void) { }
	
};

#pragma pack(pop)

typedef void __fastcall (*TGroupMemberProc)(TDiagramControl* ADControl);

class PASCALIMPLEMENTATION TBaseGroupBlock : public TCustomDiagramBlock
{
	typedef TCustomDiagramBlock inherited;
	
private:
	TGroupMemberList* FMembers;
	Diagramutils::TSquare __fastcall ResizeMemberRect(TCustomDiagramBlock* ABlock, const Diagramutils::TSquare &ABlockRect, const Diagramutils::TSquare &AOldGroup, const Diagramutils::TSquare &ANewGroup);
	Diagramutils::TSquare __fastcall RotateMemberRect(const Diagramutils::TSquare &ARect, double AAngle, const Diagramutils::TSquare &AGroupRect);
	void __fastcall RotateMemberLine(TCustomDiagramLine* ALine, TStretchHandles* AHandles, double AAngle, const Diagramutils::TSquare &AGroupRect);
	void __fastcall ResizeMemberLine(TCustomDiagramLine* ALine, TStretchHandles* AHandles, const Diagramutils::TSquare &AOld, const Diagramutils::TSquare &ANew);
	void __fastcall RotateMembers(double ADeltaAngle, bool ATemporary);
	void __fastcall ResizeMembers(const Diagramutils::TSquare &AOld, const Diagramutils::TSquare &ANew, bool ATemporary);
	void __fastcall NotifyAnchoredMembers(void);
	void __fastcall IterateAllMembers(TGroupMemberProc AProc);
	void __fastcall SetMembers(TGroupMemberList* const Value);
	void __fastcall MoveLineHandle(TCustomDiagramLine* ALine, TStretchHandles* AHandles, TStretchHandle* AHandle, const Diagramutils::TDot &ADeltaMove);
	void __fastcall DestroyMembers(void);
	
protected:
	virtual void __fastcall DiagramChanged(TatDiagram* Old, TatDiagram* New);
	virtual void __fastcall DrawBlockCursor(const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	virtual void __fastcall MemberIncluded(TDiagramControl* AMember);
	virtual void __fastcall MemberRemoved(TDiagramControl* AMember);
	virtual void __fastcall UpdateGroupMembers(void);
	virtual void __fastcall AngleChangedEx(double AOld, double ANew);
	virtual void __fastcall BoundsChanged(const Diagramutils::TSquare &AOld, const Diagramutils::TSquare &ANew);
	virtual Diagramutils::TDotArray __fastcall SurroundRgn(void);
	virtual void __fastcall HandleMoving(const THandleMoveInfo &AInfo);
	bool __fastcall HasSelecteds(void);
	
public:
	void __fastcall RecalculateRect(void);
	__fastcall virtual TBaseGroupBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseGroupBlock(void);
	__property TGroupMemberList* Members = {read=FMembers, write=SetMembers};
};


class DELPHICLASS TSelectionBlock;
class PASCALIMPLEMENTATION TSelectionBlock : public TBaseGroupBlock
{
	typedef TBaseGroupBlock inherited;
	
protected:
	virtual void __fastcall UpdateGroupMembers(void);
public:
	/* TBaseGroupBlock.Create */ inline __fastcall virtual TSelectionBlock(System::Classes::TComponent* AOwner) : TBaseGroupBlock(AOwner) { }
	/* TBaseGroupBlock.Destroy */ inline __fastcall virtual ~TSelectionBlock(void) { }
	
};


class PASCALIMPLEMENTATION TGroupBlock : public TBaseGroupBlock
{
	typedef TBaseGroupBlock inherited;
	
protected:
	virtual void __fastcall MemberIncluded(TDiagramControl* AMember);
	virtual void __fastcall MemberRemoved(TDiagramControl* AMember);
	virtual void __fastcall DrawHandles(const TDiagramDrawInfo &AInfo);
	
__published:
	__property Angle = {default=0};
	__property Restrictions;
	__property MinWidth;
	__property MinHeight;
	__property Visible;
	__property Members;
public:
	/* TBaseGroupBlock.Create */ inline __fastcall virtual TGroupBlock(System::Classes::TComponent* AOwner) : TBaseGroupBlock(AOwner) { }
	/* TBaseGroupBlock.Destroy */ inline __fastcall virtual ~TGroupBlock(void) { }
	
};


class DELPHICLASS TDiagramPrinterPaperInfo;
class PASCALIMPLEMENTATION TDiagramPrinterPaperInfo : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Extended FPaperHeight;
	int FPaperID;
	System::Extended FPaperWidth;
	System::UnicodeString FPaperName;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString PaperName = {read=FPaperName, write=FPaperName};
	__property int PaperID = {read=FPaperID, write=FPaperID, nodefault};
	__property System::Extended PaperWidth = {read=FPaperWidth, write=FPaperWidth};
	__property System::Extended PaperHeight = {read=FPaperHeight, write=FPaperHeight};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDiagramPrinterPaperInfo(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TDiagramPrinterPaperInfo(void) : System::Classes::TPersistent() { }
	
};


enum DECLSPEC_DENUM TDiagramPageOrientation : unsigned char { dpoPortrait, dpoLandscape };

class DELPHICLASS TDiagramPrinter;
class DELPHICLASS TDiagramPrinterCanvas;
class PASCALIMPLEMENTATION TDiagramPrinter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FBin;
	System::Classes::TStrings* FBins;
	TDiagramPrinterCanvas* FCanvas;
	TDiagramPageOrientation FDefOrientation;
	TDiagramPrinterPaperInfo* FDefPaper;
	System::Types::TPoint FDPI;
	bool FInitialized;
	System::UnicodeString FDeviceName;
	System::Contnrs::TObjectList* FPapers;
	System::Extended FLeftMargin;
	System::Extended FTopMargin;
	System::Extended FRightMargin;
	System::Extended FBottomMargin;
	TDiagramPageOrientation FOrientation;
	System::UnicodeString FPort;
	bool FPrinting;
	System::UnicodeString FTitle;
	TDiagramPrinterPaperInfo* __fastcall FindPaper(int APaperID);
	void __fastcall AddDefaultBin(void);
	TDiagramPrinterPaperInfo* __fastcall GetPaper(int Index);
	int __fastcall GetPaperCount(void);
	int __fastcall GetBinCount(void);
	int __fastcall GetBinID(int Index);
	System::UnicodeString __fastcall GetBinName(int Index);
	void __fastcall UpdateStandardPapers(void);
	void __fastcall InitializeDefault(void);
	void __fastcall CheckInitialized(void);
	
protected:
	virtual void __fastcall Initialize(void);
	virtual void __fastcall BeginDoc(void);
	virtual void __fastcall BeginPage(void);
	virtual void __fastcall EndDoc(void);
	virtual void __fastcall EndPage(void);
	virtual void __fastcall SetPrintParams(int APaperSize, System::Extended APaperWidth, System::Extended APaperHeight, TDiagramPageOrientation AOrientation);
	
public:
	__fastcall TDiagramPrinter(const System::WideChar * ADeviceName, const System::WideChar * APort);
	__fastcall virtual ~TDiagramPrinter(void);
	int __fastcall MMToPixelsX(System::Extended AMM);
	int __fastcall MMToPixelsY(System::Extended AMM);
	virtual void __fastcall PropertiesDlg(void);
	__property System::UnicodeString DeviceName = {read=FDeviceName};
	__property TDiagramPrinterPaperInfo* Papers[int Index] = {read=GetPaper};
	__property int PaperCount = {read=GetPaperCount, nodefault};
	__property System::UnicodeString BinNames[int Index] = {read=GetBinName};
	__property int BinIDs[int Index] = {read=GetBinID};
	__property int BinCount = {read=GetBinCount, nodefault};
	__property TDiagramPrinterPaperInfo* DefPaper = {read=FDefPaper};
	__property TDiagramPageOrientation DefOrientation = {read=FDefOrientation, nodefault};
	__property System::Types::TPoint DPI = {read=FDPI};
	__property System::UnicodeString Port = {read=FPort};
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
};


class DELPHICLASS TDiagramRealPrinter;
class PASCALIMPLEMENTATION TDiagramRealPrinter : public TDiagramPrinter
{
	typedef TDiagramPrinter inherited;
	
private:
	NativeUInt FPrinterHandle;
	_devicemodeW *FDevMode;
	NativeUInt FDeviceMode;
	HDC FDC;
	void __fastcall RecreateDC(void);
	void __fastcall CreateDeviceMode(void);
	void __fastcall UpdateDeviceCaps(void);
	
protected:
	virtual void __fastcall Initialize(void);
	virtual void __fastcall BeginDoc(void);
	virtual void __fastcall BeginPage(void);
	virtual void __fastcall EndDoc(void);
	virtual void __fastcall EndPage(void);
	virtual void __fastcall SetPrintParams(int APaperSize, System::Extended APaperWidth, System::Extended APaperHeight, TDiagramPageOrientation AOrientation);
	
public:
	__fastcall virtual ~TDiagramRealPrinter(void);
	virtual void __fastcall PropertiesDlg(void);
public:
	/* TDiagramPrinter.Create */ inline __fastcall TDiagramRealPrinter(const System::WideChar * ADeviceName, const System::WideChar * APort) : TDiagramPrinter(ADeviceName, APort) { }
	
};


class DELPHICLASS TDiagramGenericPrinter;
class PASCALIMPLEMENTATION TDiagramGenericPrinter : public TDiagramPrinter
{
	typedef TDiagramPrinter inherited;
	
protected:
	virtual void __fastcall Initialize(void);
public:
	/* TDiagramPrinter.Create */ inline __fastcall TDiagramGenericPrinter(const System::WideChar * ADeviceName, const System::WideChar * APort) : TDiagramPrinter(ADeviceName, APort) { }
	/* TDiagramPrinter.Destroy */ inline __fastcall virtual ~TDiagramGenericPrinter(void) { }
	
};


class PASCALIMPLEMENTATION TDiagramPrinterCanvas : public Vcl::Graphics::TCanvas
{
	typedef Vcl::Graphics::TCanvas inherited;
	
private:
	TDiagramPrinter* FPrinter;
	void __fastcall UpdateFont(void);
	
public:
	virtual void __fastcall Changing(void);
public:
	/* TCanvas.Create */ inline __fastcall TDiagramPrinterCanvas(void) : Vcl::Graphics::TCanvas() { }
	/* TCanvas.Destroy */ inline __fastcall virtual ~TDiagramPrinterCanvas(void) { }
	
};


class DELPHICLASS TDiagramPrinters;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramPrinters : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FHasPrinterInstalled;
	System::Classes::TStrings* FPrinters;
	int FPrinterIndex;
	TDiagramPrinter* __fastcall GetItem(int Index);
	System::UnicodeString __fastcall DefaultPrinterName(void);
	void __fastcall Clear(void);
	TDiagramPrinter* __fastcall GetPrinter(void);
	int __fastcall GetPrinterIndex(void);
	void __fastcall SetPrinterIndex(const int Value);
	int __fastcall IndexOf(System::UnicodeString DeviceName);
	__property TDiagramPrinter* Items[int Index] = {read=GetItem};
	void __fastcall UpdatePrinters(void);
	__property bool HasPrinterInstalled = {read=FHasPrinterInstalled, nodefault};
	
public:
	__fastcall TDiagramPrinters(void);
	__fastcall virtual ~TDiagramPrinters(void);
	__property TDiagramPrinter* Printer = {read=GetPrinter};
	__property int PrinterIndex = {read=GetPrinterIndex, write=SetPrinterIndex, nodefault};
	__property System::Classes::TStrings* Printers = {read=FPrinters};
};

#pragma pack(pop)

class DELPHICLASS TDiagramPageSettings;
class PASCALIMPLEMENTATION TDiagramPageSettings : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Extended FPaperHeight;
	System::Extended FPaperWidth;
	int FPaperId;
	System::UnicodeString FPaperName;
	TDiagramPageOrientation FOrientation;
	TatDiagram* FDiagram;
	System::Extended FTopMargin;
	System::Extended FLeftMargin;
	System::Extended FRightMargin;
	System::Extended FBottomMargin;
	System::UnicodeString __fastcall _NumToStr(System::Extended N);
	System::Extended __fastcall _StrToNum(System::UnicodeString S);
	void __fastcall SetOrientation(const TDiagramPageOrientation Value);
	void __fastcall SetPaperHeight(const System::Extended Value);
	void __fastcall SetPaperId(const int Value);
	void __fastcall SetPaperName(const System::UnicodeString Value);
	void __fastcall SetPaperWidth(const System::Extended Value);
	void __fastcall Changed(void);
	void __fastcall SetBottomMargin(const System::Extended Value);
	void __fastcall SetLeftMargin(const System::Extended Value);
	void __fastcall SetRightMargin(const System::Extended Value);
	void __fastcall SetTopMargin(const System::Extended Value);
	void __fastcall RetrieveDefaultSize(void);
	Diagramutils::TSquare __fastcall PrintPageRect(void);
	System::Types::TPoint __fastcall PrintPaperSize(void);
	System::UnicodeString __fastcall GetBottomMarginStr(void);
	System::UnicodeString __fastcall GetLeftMarginStr(void);
	System::UnicodeString __fastcall GetRightMarginStr(void);
	System::UnicodeString __fastcall GetTopMarginStr(void);
	void __fastcall SetBottomMarginStr(const System::UnicodeString Value);
	void __fastcall SetLeftMarginStr(const System::UnicodeString Value);
	void __fastcall SetRightMarginStr(const System::UnicodeString Value);
	void __fastcall SetTopMarginStr(const System::UnicodeString Value);
	
public:
	__fastcall TDiagramPageSettings(TatDiagram* ADiagram);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall ChangePaperID(int APaperID);
	__property System::Extended LeftMargin = {read=FLeftMargin, write=SetLeftMargin};
	__property System::Extended TopMargin = {read=FTopMargin, write=SetTopMargin};
	__property System::Extended RightMargin = {read=FRightMargin, write=SetRightMargin};
	__property System::Extended BottomMargin = {read=FBottomMargin, write=SetBottomMargin};
	
__published:
	__property System::UnicodeString PaperName = {read=FPaperName, write=SetPaperName};
	__property int PaperId = {read=FPaperId, write=SetPaperId, nodefault};
	__property System::Extended PaperWidth = {read=FPaperWidth, write=SetPaperWidth};
	__property System::Extended PaperHeight = {read=FPaperHeight, write=SetPaperHeight};
	__property TDiagramPageOrientation Orientation = {read=FOrientation, write=SetOrientation, nodefault};
	__property System::UnicodeString LeftMarginStr = {read=GetLeftMarginStr, write=SetLeftMarginStr};
	__property System::UnicodeString TopMarginStr = {read=GetTopMarginStr, write=SetTopMarginStr};
	__property System::UnicodeString RightMarginStr = {read=GetRightMarginStr, write=SetRightMarginStr};
	__property System::UnicodeString BottomMarginStr = {read=GetBottomMarginStr, write=SetBottomMarginStr};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDiagramPageSettings(void) { }
	
};


class DELPHICLASS TDgrLibraryItem;
class DELPHICLASS TDgrLibrary;
class PASCALIMPLEMENTATION TDgrLibraryItem : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FCaption;
	System::UnicodeString FCategory;
	Vcl::Graphics::TPicture* FGlyph;
	System::UnicodeString FData;
	TDgrLibrary* FLibrary;
	System::UnicodeString FItemName;
	void __fastcall SetGlyph(Vcl::Graphics::TPicture* const Value);
	System::UnicodeString __fastcall RealControlID(void);
	void __fastcall RegisterItem(void);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TDgrLibraryItem(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrLibraryItem(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Save(void);
	void __fastcall UnregisterItem(void);
	TDiagramControl* __fastcall CreateControl(TatDiagram* ADiagram);
	__property TDgrLibrary* OwnerLibrary = {read=FLibrary};
	
__published:
	__property System::UnicodeString ItemName = {read=FItemName, write=FItemName};
	__property System::UnicodeString Category = {read=FCategory, write=FCategory};
	__property System::UnicodeString Caption = {read=FCaption, write=FCaption};
	__property Vcl::Graphics::TPicture* Glyph = {read=FGlyph, write=SetGlyph};
	__property System::UnicodeString Data = {read=FData, write=FData};
};


class DELPHICLASS TDgrLibraryManager;
class PASCALIMPLEMENTATION TDgrLibrary : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	TDgrLibraryItem* operator[](int Index) { return Items[Index]; }
	
private:
	System::Contnrs::TObjectList* FLibItems;
	System::UnicodeString FLibraryName;
	TDgrLibraryManager* FManager;
	TDgrLibraryItem* __fastcall GetItem(int Index);
	void __fastcall AddItem(TDgrLibraryItem* ALibItem);
	void __fastcall RemoveItem(TDgrLibraryItem* ALibItem);
	void __fastcall RegisterLibrary(void);
	
public:
	__fastcall virtual TDgrLibrary(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrLibrary(void);
	void __fastcall Clear(void);
	TDgrLibraryItem* __fastcall NewItem(void);
	int __fastcall Count(void);
	void __fastcall DeleteItem(TDgrLibraryItem* ALibItem);
	TDgrLibraryItem* __fastcall FindItem(System::UnicodeString ACategory, System::UnicodeString AItemName);
	__property System::UnicodeString LibraryName = {read=FLibraryName};
	__property TDgrLibraryItem* Items[int Index] = {read=GetItem/*, default*/};
};


class DELPHICLASS TDgrLibraryFiler;
class PASCALIMPLEMENTATION TDgrLibraryFiler : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
protected:
	virtual void __fastcall GetLibraryNames(System::Classes::TStrings* AStrings) = 0 ;
	virtual bool __fastcall LoadItem(TDgrLibraryItem* AItem) = 0 ;
	virtual bool __fastcall SaveItem(TDgrLibraryItem* AItem) = 0 ;
	virtual void __fastcall DeleteItem(TDgrLibraryItem* AItem) = 0 ;
	virtual void __fastcall Load(TDgrLibrary* ALibrary) = 0 ;
	virtual void __fastcall Save(TDgrLibrary* ALibrary) = 0 ;
	virtual void __fastcall CreateLibrary(TDgrLibrary* ALibrary) = 0 ;
	virtual void __fastcall DeleteLibrary(TDgrLibrary* ALibrary) = 0 ;
public:
	/* TComponent.Create */ inline __fastcall virtual TDgrLibraryFiler(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDgrLibraryFiler(void) { }
	
};


class PASCALIMPLEMENTATION TDgrLibraryManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	TDgrLibrary* operator[](int Index) { return Libraries[Index]; }
	
private:
	TDgrLibraryFiler* FFiler;
	System::Contnrs::TObjectList* FLibs;
	bool FAutoLoad;
	void __fastcall SetFiler(TDgrLibraryFiler* const Value);
	void __fastcall CheckFiler(void);
	void __fastcall AddLibrary(TDgrLibrary* ALib);
	TDgrLibrary* __fastcall GetLibrary(int Index);
	void __fastcall SaveItem(TDgrLibraryItem* AItem);
	void __fastcall RegisterAll(void);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall Clear(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TDgrLibraryManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDgrLibraryManager(void);
	void __fastcall LoadLibraries(void);
	TDgrLibrary* __fastcall LibraryByName(System::UnicodeString AName);
	TDgrLibrary* __fastcall CreateLibrary(System::UnicodeString ALibName);
	void __fastcall DeleteLibrary(System::UnicodeString ALibName);
	TDgrLibraryItem* __fastcall CreateItemDlg(TDiagramControl* ADControl);
	void __fastcall GetLibraryNames(System::Classes::TStrings* AStrings);
	int __fastcall LibraryCount(void);
	void __fastcall ReloadLibrary(System::UnicodeString ALibName);
	__property TDgrLibrary* Libraries[int Index] = {read=GetLibrary/*, default*/};
	
__published:
	__property TDgrLibraryFiler* Filer = {read=FFiler, write=SetFiler};
	__property bool AutoLoad = {read=FAutoLoad, write=FAutoLoad, default=1};
};


class DELPHICLASS TDgrLibraryFolderFiler;
class PASCALIMPLEMENTATION TDgrLibraryFolderFiler : public TDgrLibraryFiler
{
	typedef TDgrLibraryFiler inherited;
	
private:
	System::UnicodeString FBaseFolder;
	System::UnicodeString FDefaultExt;
	System::UnicodeString FLibPrefix;
	System::UnicodeString __fastcall GetBaseFolder(void);
	System::UnicodeString __fastcall RealBaseFolder(void);
	void __fastcall SetBaseFolder(const System::UnicodeString Value);
	void __fastcall CheckBaseFolder(void);
	bool __fastcall IsLibraryFileName(System::UnicodeString ALibName);
	System::UnicodeString __fastcall BuildLibraryFileName(System::UnicodeString ALibName);
	System::UnicodeString __fastcall ExtractLibraryName(System::UnicodeString AFileName);
	
protected:
	virtual void __fastcall GetLibraryNames(System::Classes::TStrings* AStrings);
	virtual bool __fastcall LoadItem(TDgrLibraryItem* AItem);
	virtual bool __fastcall SaveItem(TDgrLibraryItem* AItem);
	virtual void __fastcall DeleteItem(TDgrLibraryItem* AItem);
	virtual void __fastcall Load(TDgrLibrary* ALibrary);
	virtual void __fastcall Save(TDgrLibrary* ALibrary);
	virtual void __fastcall CreateLibrary(TDgrLibrary* ALibrary);
	virtual void __fastcall DeleteLibrary(TDgrLibrary* ALibrary);
	
public:
	__fastcall virtual TDgrLibraryFolderFiler(System::Classes::TComponent* AOwner);
	
__published:
	__property System::UnicodeString BaseFolder = {read=GetBaseFolder, write=SetBaseFolder};
	__property System::UnicodeString DefaultExt = {read=FDefaultExt, write=FDefaultExt};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDgrLibraryFolderFiler(void) { }
	
};


class DELPHICLASS TDiagramPrintSettings;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramPrintSettings : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FCopies;
	System::UnicodeString FTitle;
	System::UnicodeString FPageNumbers;
	
public:
	__fastcall TDiagramPrintSettings(void);
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
	__property int Copies = {read=FCopies, write=FCopies, nodefault};
	__property System::UnicodeString PageNumbers = {read=FPageNumbers, write=FPageNumbers};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDiagramPrintSettings(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramLayer : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TatDiagram* FDiagram;
	bool FEditable;
	bool FVisible;
	System::UnicodeString FLayerName;
	void __fastcall SetVisible(bool Value);
	
protected:
	__property TatDiagram* Diagram = {read=FDiagram};
	
public:
	__fastcall virtual TDiagramLayer(System::Classes::TCollection* Collection);
	__fastcall virtual ~TDiagramLayer(void);
	
__published:
	__property System::UnicodeString LayerName = {read=FLayerName, write=FLayerName};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
	__property bool Editable = {read=FEditable, write=FEditable, default=1};
};

#pragma pack(pop)

class DELPHICLASS TDiagramLayers;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDiagramLayers : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TDiagramLayer* operator[](int Index) { return Items[Index]; }
	
private:
	TatDiagram* FDiagram;
	HIDESBASE TDiagramLayer* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TDiagramLayer* Value);
	System::UnicodeString __fastcall FindLayerName(void);
	
public:
	__fastcall TDiagramLayers(TatDiagram* ADiagram);
	TDiagramLayer* __fastcall FindByName(const System::UnicodeString AName);
	HIDESBASE TDiagramLayer* __fastcall Add(System::UnicodeString AName = System::UnicodeString());
	__property TDiagramLayer* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDiagramLayers(void) { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TDgrEvent : unsigned char { deLibraryChanged };

struct DECLSPEC_DRECORD TDgrNotificationInfo
{
public:
	TDgrEvent Event;
};


__interface IDiagramSubscriber;
typedef System::DelphiInterface<IDiagramSubscriber> _di_IDiagramSubscriber;
__interface IDiagramSubscriber  : public System::IInterface 
{
	
public:
	virtual void __fastcall DgrNotification(TDgrNotificationInfo AInfo) = 0 ;
};

typedef void __fastcall (__closure *TDControlEvent)(System::TObject* Sender, TDiagramControl* ADControl);

typedef void __fastcall (__closure *TBlockEvent)(System::TObject* Sender, TCustomDiagramBlock* ABlock);

typedef void __fastcall (__closure *TLinkEvent)(System::TObject* Sender, TCustomDiagramLine* ALink);

enum DECLSPEC_DENUM TDiagramEventType : unsigned char { etSelectionChanging, etSelectionChanged, etControlSelected, etControlUnselected };

typedef void __fastcall (__closure *TDiagramDesignEvent)(System::TObject* Sender, TDiagramEventType AEventType, int Info);

typedef void __fastcall (__closure *TDControlMouseEvent)(System::TObject* Sender, TDiagramControl* ADControl, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TDControlMouseEventEx)(System::TObject* Sender, TDiagramControl* ADControl, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y, TStretchHandle* &AHandle);

typedef void __fastcall (__closure *TBlockMouseEvent)(System::TObject* Sender, TCustomDiagramBlock* ABlock, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TDControlMouseMoveEvent)(System::TObject* Sender, TDiagramControl* ADControl, System::Classes::TShiftState Shift, int X, int Y);

typedef void __fastcall (__closure *TDiagramPaintEvent)(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas);

typedef void __fastcall (__closure *TDiagramDrawLinkPointEvent)(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, TLinkPoint* ALinkPoint, const System::Types::TPoint &APoint, bool &DrawingDone);

typedef void __fastcall (__closure *TDiagramCloseEditorEvent)(System::TObject* Sender, TTextCell* ATextCell, bool AUpdate);

typedef void __fastcall (__closure *TBeforeCreateControlEvent)(System::TObject* Sender, System::UnicodeString ADControlID, System::UnicodeString &AComponentBaseName);

enum DECLSPEC_DENUM TPaintStyle : unsigned char { psScreen, psPreview, psPrint, psBitmap };

enum DECLSPEC_DENUM TMouseWheelMode : unsigned char { mwOff, mwHorizontal, mwVertical };

enum DECLSPEC_DENUM TControlSearchMode : unsigned char { csmAll, csmIgnoreLines };

typedef System::TMetaClass* TatDiagramClass;

enum DECLSPEC_DENUM TDiagramKeyAction : unsigned char { kaEscape, kaMove, kaPage, kaResize, kaSelect };

typedef System::Set<TDiagramKeyAction, TDiagramKeyAction::kaEscape, TDiagramKeyAction::kaSelect> TDiagramKeyActions;

enum DECLSPEC_DENUM TDiagramDragStyle : unsigned char { dsOutline, dsShape };

enum DECLSPEC_DENUM TDiagramHandlesStyle : unsigned char { hsClassic, hsVisio };

enum DECLSPEC_DENUM TDiagramSelectionMode : unsigned char { slmMultiple, slmGroup };

enum DECLSPEC_DENUM TDiagramMeasUnit : unsigned char { duMili, duCenti, duInch };

enum DECLSPEC_DENUM TDiagramDesignMode : unsigned char { ddmEditable, ddmNonEditable };

enum DECLSPEC_DENUM TDgrSelectionClickMode : unsigned char { dcmClick, dcmSubClick, dcmShiftClick };

class PASCALIMPLEMENTATION TatDiagram : public Vcl::Controls::TWinControl
{
	typedef Vcl::Controls::TWinControl inherited;
	
private:
	System::Types::TRect FCurRect;
	Diagramutils::TDot FDragStart;
	int FConnOff;
	Vcl::Graphics::TCanvas* FControlCanvas;
	TMouseState FMouseState;
	TLinkPoint* FLinkPoint;
	TStretchHandle* FHandle;
	TBlockEvent FOnInsertBlock;
	TDControlEvent FOnInsertDControl;
	TDControlEvent FOnRemoveDControl;
	TDControlEvent FOnSelectDControl;
	TDControlEvent FOnUnselectDControl;
	System::Classes::TList* FBlocks;
	System::Classes::TList* FLinks;
	System::Classes::TList* FDControls;
	System::Classes::TList* FSelecteds;
	System::Uitypes::TCursor FOldScreenCursor;
	TDiagramBackground* FBackground;
	System::Classes::TNotifyEvent FOnModified;
	bool FInternalStreaming;
	bool FClipboardStreaming;
	int FInternalUpdating;
	int FUpdatingPos;
	int FUpdatingSel;
	TDiagramControl* FInsertDControl;
	TDiagramControl* FPreviousDControl;
	bool FDesigning;
	TDiagramDesignEvent FOnDesignEvent;
	System::Classes::TNotifyEvent FOnSelectionChanged;
	System::Classes::TNotifyEvent FOnSelectionChanging;
	TSnapGrid* FSnapGrid;
	TDrawBlockEvent FOnDrawBlock;
	TDrawBlockEvent FOnDrawShape;
	TDiagramMemo* FInplaceMemo;
	TLinkEvent FOnInsertLink;
	bool FShowLinkPoints;
	int FUpdateCount;
	int FRedrawRequestCount;
	TDiagramControl* FDControlClicked;
	TDControlEvent FOnDControlClick;
	TDControlEvent FOnDControlDblClick;
	TDControlMouseEvent FOnDControlMouseDown;
	TDControlMouseEventEx FOnDControlMouseDownEx;
	TDControlMouseEvent FOnDControlMouseUp;
	TDControlMouseMoveEvent FOnDControlMouseMove;
	TBlockEvent FOnBlockMouseEnter;
	TBlockEvent FOnBlockMouseLeave;
	bool FPainting;
	Diagramutils::TDot FOldDragPos;
	System::Types::TPoint FOldPosition;
	THandleMoveInfo FHandleMoveInfo;
	TControlInsertInfo FControlInsertInfo;
	TControlDrawInfo FControlDrawInfo;
	TControlMoveInfoArray FControlMoveInfos;
	TDiagramRuler* FTopRuler;
	TDiagramRuler* FLeftRuler;
	bool FUpdatingScrollBars;
	TDiagramScrollBar* FHorzScrollBar;
	TDiagramScrollBar* FVertScrollBar;
	Vcl::Forms::TFormBorderStyle FBorderStyle;
	double FZoomRatio;
	double FPreviewZoom;
	TPaintStyle FPaintStyle;
	Diagramutils::TDot FPreviewOffset;
	float FPrintConvX;
	float FPrintConvY;
	TDiagramLinkEvent FOnLinkRemoved;
	TDiagramLinkEvent FOnLinkAdded;
	System::Uitypes::TColor FBorderColor;
	bool FAutoScroll;
	TAcceptAnchorEvent FOnAcceptAnchor;
	TAcceptLinkEvent FOnAcceptLink;
	TGetSurroundPtsEvent FOnGetSurroundPts;
	TMouseWheelMode FMouseWheelMode;
	System::Classes::TNotifyEvent FOnAfterMove;
	System::Classes::TNotifyEvent FOnBeforeMove;
	TDiagramPosEvent FOnMoving;
	TDiagramPaintEvent FOnBeforePaint;
	TDiagramPaintEvent FOnAfterPaint;
	TDiagramDrawLinkPointEvent FOnDrawLinkPoint;
	bool FAutomaticNodes;
	int FNettoExportOffset;
	System::Uitypes::TCursor FLinkCursor;
	System::Uitypes::TCursor FPanCursor;
	System::Uitypes::TCursor FZoomCursor;
	System::UnicodeString FClipPrefix;
	TDiagramUndoStack* FUndoStack;
	bool FKeepInserting;
	System::Uitypes::TColor FExportBackgroundColor;
	TZoomingState FZoomingState;
	bool FPaintLinesFirst;
	TDiagramCloseEditorEvent FOnCloseEditor;
	bool FIgnoreScreenDPI;
	bool FShowCrossIndicators;
	TDiagramPosEvent FOnDControlResizing;
	System::Classes::TNotifyEvent FOnAfterResize;
	System::Classes::TNotifyEvent FOnBeforeResize;
	bool FAutoPage;
	TPageLines* FPageLines;
	System::UnicodeString FConnectionLineId;
	TDiagramKeyActions FKeyActions;
	TDrawBlockEvent FOnAfterDrawBlock;
	TDiagramDragStyle FDragStyle;
	TDiagramHandlesStyle FHandlesStyle;
	double FAdjustRatioX;
	double FAdjustRatioY;
	Vcl::Graphics::TBitmap* FCacheImage;
	bool FUseCache;
	Dgrclasses::TDgrSmoothMode FSmoothMode;
	Dgrclasses::TDgrTextRenderingMode FTextRenderingMode;
	TSelectionBlock* FSelBlock;
	TDiagramSelectionMode FSelectionMode;
	bool FDoingCache;
	bool FCanMoveOutOfBounds;
	bool FFixedSideLines;
	TDiagramPageSettings* FPageSettings;
	TDiagramPrintSettings* FPrintSettings;
	TDiagramMeasUnit FIntMeasUnit;
	bool FRulerAutoUnit;
	bool FWheelZoom;
	int FWheelZoomIncrement;
	int FWheelZoomMax;
	int FWheelZoomMin;
	System::Types::TRect FPrintClipRect;
	TDiagramDesignMode FDesignMode;
	__int64 FActiveLayers;
	TDiagramLayers* FLayers;
	System::Classes::TInterfaceList* FSubList;
	TBeforeCreateControlEvent FOnBeforeCreateControl;
	Dgrclasses::TDgrGraphicLib FGraphicLib;
	TGroupBlockClass FCustomGroupBlockClass;
	TDiagramMemoClass FCustomDiagramMemoClass;
	void __fastcall BeginCacheBitmap(void);
	void __fastcall EndCacheBitmap(void);
	void __fastcall AddBlock(TCustomDiagramBlock* ABlock);
	void __fastcall RemoveBlock(TCustomDiagramBlock* ABlock);
	void __fastcall RemoveDControl(TDiagramControl* ADControl);
	TCustomDiagramBlock* __fastcall GetBlocks(int Index);
	void __fastcall AddLink(TCustomDiagramLine* ALink);
	void __fastcall RemoveLink(TCustomDiagramLine* ALink);
	TCustomDiagramLine* __fastcall GetLinks(int Index);
	void __fastcall CalcPanelSize(void);
	void __fastcall SelectCursor(int XPos, int YPos, bool ShowBox);
	void __fastcall DrawZoomCursor(int XPos, int YPos, bool ShowBox);
	void __fastcall CancelSelecting(void);
	Diagramutils::TSquare __fastcall SelectionRect(bool OnlyBlocks, double AAngle = 0.000000E+00);
	HIDESBASE void __fastcall SelectNext(TSelectDirection Direction);
	void __fastcall SerializeFromClipboard(void);
	void __fastcall SerializeFromString(System::UnicodeString S);
	System::UnicodeString __fastcall SerializeToString(void);
	void __fastcall BeginInternalUpdate(void);
	void __fastcall EndInternalUpdate(void);
	void __fastcall BeginUpdatePos(void);
	void __fastcall EndUpdatePos(void);
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Winapi::Messages::TWMEraseBkgnd &m);
	HIDESBASE MESSAGE void __fastcall WMHScroll(Winapi::Messages::TWMScroll &Message);
	HIDESBASE MESSAGE void __fastcall WMVScroll(Winapi::Messages::TWMScroll &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall WMGetDlgCode(Winapi::Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall CMCtl3DChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMPaint(Winapi::Messages::TWMPaint &Message);
	HIDESBASE MESSAGE void __fastcall CMDesignHitTest(Winapi::Messages::TWMMouse &Msg);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMHintShow(Winapi::Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall CMShowHintChanged(Winapi::Messages::TMessage &Message);
	TDiagramControl* __fastcall GetSelecteds(int Index);
	Diagramutils::TDot __fastcall SnapDeltaPoint(const Diagramutils::TDot &APoint);
	void __fastcall SetSnapGrid(TSnapGrid* const Value);
	void __fastcall Redraw(void);
	void __fastcall UpdateMemoEditor(TTextCell* ACell);
	void __fastcall SetShowLinkPoints(const bool Value);
	void __fastcall SelectControlsInRect(const Diagramutils::TSquare &ASelRect);
	TDiagramControl* __fastcall GetDControls(int Index);
	void __fastcall AddDControl(TDiagramControl* ADControl);
	bool __fastcall UpdateInserting(double XPos, double YPos);
	void __fastcall EndInserting(int XPos, int YPos, bool Cancel);
	void __fastcall StartDrawing(double XPos, double YPos);
	void __fastcall UpdateDrawing(double XPos, double YPos);
	void __fastcall DrawingStep(double XPos, double YPos);
	void __fastcall EndDrawing(double XPos, double YPos, bool Cancel);
	void __fastcall StartMoving(void);
	bool __fastcall UpdateMoving(double XPos, double YPos);
	void __fastcall EndMoving(double XPos, double YPos, bool Cancel);
	void __fastcall StartResizing(void);
	void __fastcall UpdateResizing(double XPos, double YPos);
	void __fastcall EndResizing(double XPos, double YPos, bool Cancel);
	Diagramutils::TDot __fastcall SnapCanvasPoint(const Diagramutils::TDot &APoint);
	TDiagramRuler* __fastcall RulerAtPos(const Diagramutils::TDot &CP);
	Diagramutils::TDot __fastcall MoveDelta(TDiagramControl* ADControl, double XPos, double YPos);
	THandleMoveInfo __fastcall UpdateHandleMoveInfo(double X, double Y, THandleMoveAction AAction);
	void __fastcall UpdateControlMoveInfos(double X, double Y, TControlMoveAction AAction);
	TControlInsertInfo __fastcall UpdateControlInsertInfo(double X, double Y, TControlInsertAction AAction);
	TControlDrawInfo __fastcall UpdateControlDrawingInfo(double X, double Y, TControlDrawAction AAction);
	void __fastcall SetBackground(TDiagramBackground* const Value);
	void __fastcall SetLeftRuler(TDiagramRuler* const Value);
	void __fastcall SetTopRuler(TDiagramRuler* const Value);
	void __fastcall UpdateScrollBars(void);
	void __fastcall SetBorderStyle(const Vcl::Forms::TBorderStyle Value);
	void __fastcall SetZoom(const int Value);
	int __fastcall GetZoom(void);
	Diagramutils::TDotArray __fastcall PolygonToCanvas(Diagramutils::TDotArray Pts);
	int __fastcall GetDiagramHeight(void);
	int __fastcall GetDiagramWidth(void);
	int __fastcall GetDiagramLeft(void);
	int __fastcall GetDiagramTop(void);
	double __fastcall GetZoomRatio(void);
	int __fastcall GetPageCount(void);
	double __fastcall PrintClientHeight(void);
	double __fastcall PrintClientWidth(void);
	Diagramutils::TDot __fastcall PageOffset(int Idx);
	void __fastcall PaintToCanvas(Vcl::Graphics::TCanvas* ACanvas, TPaintStyle APaintStyle, const Diagramutils::TDot &AOffset);
	void __fastcall UpdatePixelConvertion(void);
	void __fastcall SetDiagramDefaults(void);
	Diagramutils::TSquare __fastcall ClipRect(Vcl::Graphics::TCanvas* ACanvas);
	void __fastcall SetBorderColor(const System::Uitypes::TColor Value);
	void __fastcall SetAutoScroll(const bool Value);
	void __fastcall SetHorzScrollBar(TDiagramScrollBar* const Value);
	void __fastcall SetVertScrollBar(TDiagramScrollBar* const Value);
	Diagramutils::TDotArray __fastcall DoGetSurroundRgn(TCustomDiagramBlock* ABlock);
	Vcl::Graphics::TCanvas* __fastcall CreateMetaFileCanvas(int AWidth, int AHeight);
	Vcl::Graphics::TMetafile* __fastcall DestroyMetaFileCanvas(Vcl::Graphics::TCanvas* ACanvas);
	bool __fastcall IsDesignTime(void);
	void __fastcall SetActiveLayers(const __int64 Value);
	void __fastcall SetAutomaticNodes(const bool Value);
	void __fastcall GetExportSizeAndPos(TExportSize exportSize, System::Types::TPoint &ASize, System::Types::TPoint &APos);
	int __fastcall ScreenDPI(void);
	void __fastcall SetShowCrossIndicators(const bool Value);
	void __fastcall DeleteControls(TControlRestrictions restricted);
	void __fastcall SetAutoPage(const bool Value);
	void __fastcall SetPageLines(TPageLines* const Value);
	bool __fastcall CanCreateConnection(const Diagramutils::TDot &P);
	void __fastcall SetHandlesStyle(const TDiagramHandlesStyle Value);
	void __fastcall SetSmoothMode(const Dgrclasses::TDgrSmoothMode Value);
	void __fastcall SetTextRenderingMode(const Dgrclasses::TDgrTextRenderingMode Value);
	void __fastcall CutObjectsToClipboard(void);
	void __fastcall CopyObjectsToClipboard(void);
	void __fastcall PasteObjectsFromClipboard(void);
	void __fastcall CutTextToClipboard(void);
	void __fastcall CopyTextToClipboard(void);
	void __fastcall PasteTextFromClipboard(void);
	bool __fastcall GroupSelection(void);
	void __fastcall SetSelectionMode(const TDiagramSelectionMode Value);
	void __fastcall UpdateSelectionBlock(void);
	void __fastcall ExportToBitmap(Vcl::Graphics::TBitmap* ABitmap, TExportSize exportSize);
	Vcl::Graphics::TMetafile* __fastcall ExportToMetafile(TExportSize exportSize = (TExportSize)(0x0));
	void __fastcall DoMemberGroupIncluded(TGroupBlock* AGroup, TDiagramControl* AMember);
	void __fastcall DoMemberGroupRemoved(TGroupBlock* AGroup, TDiagramControl* AMember);
	void __fastcall NameAllDControls(void);
	void __fastcall CheckGraphicLibObjects(void);
	void __fastcall SetGroupSelected(TDiagramControl* ADControl, bool ASelected);
	void __fastcall UpdateSelectionBlockAngle(void);
	void __fastcall KeepInBounds(void);
	void __fastcall SetPageSettings(TDiagramPageSettings* const Value);
	void __fastcall SetMeasUnit(const TDiagramMeasUnit Value);
	void __fastcall SetRulerAutoUnit(const bool Value);
	System::UnicodeString __fastcall GetUnitSymbol(void);
	void __fastcall SetDesignMode(const TDiagramDesignMode Value);
	void __fastcall ReadDiagramStream(System::Classes::TStream* AStream);
	System::UnicodeString __fastcall SerializeObjectToString(TDiagramControl* ADControl);
	Diagramutils::TSquare __fastcall GetObjectsRect(void);
	void __fastcall CalculateZoomToFitRatio(const System::Types::TRect &TargetRect, int AMargin, double &AZoomRatio, System::Types::TPoint &AOffset);
	void __fastcall SetLayers(TDiagramLayers* const Value);
	void __fastcall UpdateSelecteds(void);
	void __fastcall NotifySubscribers(TDgrNotificationInfo AInfo);
	void __fastcall PerformSelection(TDiagramControl* ClickedControl, TDgrSelectionClickMode ClickMode);
	TDiagramControl* __fastcall SubControlToSelect(TDiagramControl* ClickedControl);
	void __fastcall SetGraphicLib(const Dgrclasses::TDgrGraphicLib Value);
	Dgrclasses::TDgrPaintEngineClass __fastcall DgrPaintEngineClass(void);
	void __fastcall TransformPaintEngine(Dgrclasses::TDgrPaintEngine* APaintEngine);
	bool __fastcall GetPathDrawingMode(void);
	bool __fastcall GetUseGdiPlus(void);
	void __fastcall SetUseGdiPlus(const bool Value);
	int __fastcall GetPageColCount(void);
	int __fastcall GetPageRowCount(void);
	void __fastcall SetCustomGroupBlockClass(const TGroupBlockClass Value);
	void __fastcall SetCustomDiagramMemoClass(const TDiagramMemoClass Value);
	System::Types::TRect __fastcall GetPaintRect(Vcl::Graphics::TCanvas* ACanvas);
	
protected:
	virtual TDiagramMeasUnit __fastcall GetMeasUnit(void);
	virtual void __fastcall LinkNodeMouseDown(TLinkPoint* ALinkPoint);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	virtual void __fastcall CreateWnd(void);
	void __fastcall ClipRegion(Vcl::Graphics::TCanvas* Canvas, HRGN ARgn);
	void __fastcall UnclipRegion(Vcl::Graphics::TCanvas* Canvas);
	Diagramutils::TDot __fastcall CanvasOffset(void);
	Diagramutils::TDot __fastcall RulerOffset(void);
	DYNAMIC System::Classes::TComponent* __fastcall GetChildOwner(void);
	DYNAMIC void __fastcall Resize(void);
	DYNAMIC bool __fastcall DoMouseWheelDown(System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos);
	DYNAMIC bool __fastcall DoMouseWheelUp(System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall DoDControlMouseDown(TDiagramControl* ADControl, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall DoDControlMouseDownEx(TDiagramControl* ADControl, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y, TStretchHandle* &AHandle);
	void __fastcall DoDControlMouseEnter(TDiagramControl* ADControl);
	void __fastcall DoDControlMouseLeave(TDiagramControl* ADControl);
	void __fastcall DoDControlMouseMove(TDiagramControl* ADControl, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall DoDControlMouseUp(TDiagramControl* ADControl, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall DoDControlClick(TDiagramControl* ADControl);
	void __fastcall DoDControlDblClick(TDiagramControl* ADControl);
	void __fastcall DoDrawLinkPoint(Vcl::Graphics::TCanvas* ACanvas, TLinkPoint* ALinkPoint, const System::Types::TPoint &APoint, bool &DrawingDone);
	bool __fastcall AcceptAnchor(TLinkPoint* ALink, TLinkPoint* AAnchor);
	virtual bool __fastcall AcceptLink(TCustomDiagramLine* ALink, TLinkPoint* Anchor1, TLinkPoint* Anchor2);
	void __fastcall DoLinkAdded(TDiagramControl* ADControl, TCustomDiagramLine* ALink, TLinkPoint* ALinkPoint);
	void __fastcall DoLinkRemoved(TDiagramControl* ADControl, TCustomDiagramLine* ALink, TLinkPoint* ALinkPoint);
	virtual void __fastcall InternalPaint(Vcl::Graphics::TCanvas* ACanvas);
	Diagramutils::TPointArray __fastcall DoGetSurroundRegion(TCustomDiagramBlock* ABlock);
	bool __fastcall CustomDrawBlock(TCustomDiagramBlock* ABlock, const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	bool __fastcall CustomDrawShape(TCustomDiagramBlock* ABlock, const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	void __fastcall DoInsertLink(TCustomDiagramLine* ANewLink);
	void __fastcall DoInsertBlock(TCustomDiagramBlock* ANewBlock);
	void __fastcall DoInsertDControl(TDiagramControl* ANewDControl);
	void __fastcall DoUnselectDControl(TDiagramControl* ADControl);
	void __fastcall DoSelectDControl(TDiagramControl* ADControl);
	void __fastcall DesignEvent(System::TObject* Sender, TDiagramEventType AEventType, int Info);
	void __fastcall DestroyInsertControl(void);
	TDiagramControl* __fastcall CreateControl(TDiagramControlClass ADControlClass, System::UnicodeString ADControlID);
	TDiagramControl* __fastcall CreateLibraryControl(System::UnicodeString AData, System::UnicodeString ADControlID);
	bool __fastcall StoreDesignProperty(void);
	virtual TatDiagramClass __fastcall DiagramStreamClass(void);
	virtual bool __fastcall DoAfterDrawBlock(TCustomDiagramBlock* ABlock, const TDiagramDrawInfo &AInfo, const TDiagramDrawBlockInfo &ABlockInfo);
	TGroupBlockClass __fastcall GroupBlockClass(void);
	TDiagramMemoClass __fastcall DiagramMemoClass(void);
	__property bool Designing = {read=FDesigning, write=FDesigning, nodefault};
	__property TDiagramDesignEvent OnDesignEvent = {read=FOnDesignEvent, write=FOnDesignEvent};
	__property int InternalUpdating = {read=FInternalUpdating, nodefault};
	
public:
	void __fastcall AddSubscriber(_di_IDiagramSubscriber ASubscriber);
	void __fastcall RefreshToolbars(void);
	DYNAMIC void __fastcall GetChildren(System::Classes::TGetChildProc Proc, System::Classes::TComponent* Root);
	System::UnicodeString __fastcall FindCompName(System::Classes::TComponent* AComponent, System::UnicodeString ABaseName = System::UnicodeString());
	void __fastcall CloseEditor(bool AUpdate);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	double __fastcall ClientToInches(double X);
	double __fastcall ClientToMilimeters(double X);
	double __fastcall MilimetersToClient(double X);
	double __fastcall InchesToClient(double X);
	Diagramutils::TDot __fastcall ClientToCanvas(const Diagramutils::TDot &APoint)/* overload */;
	System::Types::TPoint __fastcall ClientToCanvas(const System::Types::TPoint &APoint)/* overload */;
	System::Types::TRect __fastcall ClientToCanvas(const System::Types::TRect &ARect)/* overload */;
	Diagramutils::TSquare __fastcall ClientToCanvas(const Diagramutils::TSquare &ARect)/* overload */;
	System::Types::TPoint __fastcall CanvasToClient(const System::Types::TPoint &APoint)/* overload */;
	Diagramutils::TSquare __fastcall CanvasToClient(const Diagramutils::TSquare &ARect)/* overload */;
	Diagramutils::TDot __fastcall CanvasToClient(const Diagramutils::TDot &APoint)/* overload */;
	TDiagramControl* __fastcall DControlAtPos(const Diagramutils::TDot &Pos, TControlSearchMode SearchMode = (TControlSearchMode)(0x0), TDiagramControlFilter AGroupFilter = (TDiagramControlFilter)(0x2));
	TStretchHandle* __fastcall HandleAtPos(const Diagramutils::TDot &Pos, bool AIgnoreZoom = false);
	Vcl::Graphics::TBitmap* __fastcall BuildPreviewBitmap(int APageIdx, int AWidth, int AHeight = 0x0);
	virtual void __fastcall PaintWindow(HDC DC);
	__fastcall virtual TatDiagram(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TatDiagram(void);
	Vcl::Graphics::TPixelFormat __fastcall GetPixelFormat(void);
	virtual void __fastcall Modified(void);
	void __fastcall PaintToBitmap(Vcl::Graphics::TBitmap* ABitmap, TExportSize exportSize = (TExportSize)(0x0));
	void __fastcall BeginUpdate(void);
	int __fastcall EndUpdate(bool AOptimize = false);
	void __fastcall BeginUpdateSel(void);
	void __fastcall EndUpdateSel(void);
	bool __fastcall Print(bool AShowDialog = false);
	void __fastcall Preview(void);
	void __fastcall PageSetupDlg(void);
	void __fastcall CopyBitmapToClipboard(TExportSize exportSize = (TExportSize)(0x0));
	void __fastcall CopyMetafileToClipboard(TExportSize exportSize = (TExportSize)(0x0));
	void __fastcall ExportToFile(const System::UnicodeString fileName, TExportFormat exportFormat = (TExportFormat)(0x0), TExportSize exportSize = (TExportSize)(0x1));
	void __fastcall ExportAsBMP(const System::UnicodeString fileName, TExportSize exportSize = (TExportSize)(0x1));
	void __fastcall ExportAsBMPStream(System::Classes::TStream* AStream, TExportSize exportSize = (TExportSize)(0x1));
	void __fastcall ExportAsWMF(System::UnicodeString fileName, TExportSize exportSize = (TExportSize)(0x0));
	void __fastcall ExportAsWMFStream(System::Classes::TStream* AStream, TExportSize exportSize = (TExportSize)(0x0));
	void __fastcall ExportAsJPG(const System::UnicodeString fileName, TExportSize exportSize = (TExportSize)(0x1));
	void __fastcall ExportAsJPGStream(System::Classes::TStream* AStream, TExportSize exportSize = (TExportSize)(0x1));
	void __fastcall CutToClipboard(void);
	void __fastcall CopyToClipboard(void);
	void __fastcall PasteFromClipboard(void);
	bool __fastcall CanPaste(void);
	bool __fastcall CanCopy(void);
	void __fastcall Clear(void);
	void __fastcall DeleteSelecteds(void);
	void __fastcall UnselectAll(void);
	void __fastcall SelectAll(void);
	void __fastcall StartPanning(void);
	void __fastcall CancelPanning(void);
	void __fastcall StartZooming(TZoomingState ZoomingState);
	void __fastcall CancelZooming(void);
	void __fastcall ZoomIn(const Diagramutils::TSquare &ARect);
	void __fastcall ZoomOut(const Diagramutils::TSquare &ARect);
	void __fastcall ZoomMoveToFit(int AMargin = 0x0);
	HIDESBASE void __fastcall BringToFront(TDiagramControl* ADControl)/* overload */;
	HIDESBASE void __fastcall SendToBack(TDiagramControl* ADControl)/* overload */;
	HIDESBASE void __fastcall BringToFront(void)/* overload */;
	HIDESBASE void __fastcall SendToBack(void)/* overload */;
	void __fastcall MoveControlIndex(TDiagramControl* ADControl, int NewIndex);
	void __fastcall SaveToFile(const System::UnicodeString AFileName);
	void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream, bool TextFormat = false);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream, bool TextFormat = false);
	void __fastcall EditBlockText(TCustomDiagramBlock* ABlock);
	void __fastcall EditControlText(TDiagramControl* ADControl);
	void __fastcall EditTextCell(TTextCell* ACell);
	TDiagramControl* __fastcall FindDControl(const System::UnicodeString AName);
	TCustomDiagramBlock* __fastcall FindBlock(const System::UnicodeString AName);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall StartInsertingControl(const System::UnicodeString ADControlID, bool AKeepInserting = false)/* overload */;
	void __fastcall StartInsertingControl(TDiagramControlClass ADControlClass, bool AKeepInserting = false)/* overload */;
	void __fastcall StartInsertingControl(TDiagramControl* ADControl, bool AKeepInserting = false)/* overload */;
	void __fastcall CancelInsertingBlock(void);
	int __fastcall SelectedBlockCount(TDiagramControlFilter AFilter = (TDiagramControlFilter)(0x0));
	int __fastcall SelectedLinkCount(void);
	int __fastcall LinkCount(void);
	int __fastcall BlockCount(void);
	int __fastcall SelectedCount(TDiagramControlFilter AFilter = (TDiagramControlFilter)(0x0));
	int __fastcall DControlCount(void);
	bool __fastcall AreBlocksLinked(TCustomDiagramBlock* ABlock1, TCustomDiagramBlock* ABlock2);
	TCustomDiagramLine* __fastcall LinkBetweenBlocks(TCustomDiagramBlock* ABlock1, TCustomDiagramBlock* ABlock2);
	void __fastcall Undo(void);
	void __fastcall Redo(void);
	System::UnicodeString __fastcall NextUndoAction(void);
	System::UnicodeString __fastcall NextRedoAction(void);
	void __fastcall PushUndoStack(const System::UnicodeString AActionName);
	void __fastcall ClearUndoStack(void);
	bool __fastcall EditingText(void);
	TTextCell* __fastcall EditingCell(void);
	void __fastcall MoveBlocks(double ADeltaX, double ADeltaY, bool AOnlySelected = false, bool AOnlyMovable = true);
	bool __fastcall LayerActive(int ALayer);
	void __fastcall ActivateLayer(int ALayer);
	void __fastcall DeactivateLayer(int ALayer);
	TLinkPoint* __fastcall LinkNodeAtPos(const Diagramutils::TDot &Pos);
	TLinkPoint* __fastcall LinkPointAtPos(const Diagramutils::TDot &Pos, TDiagramControl* ADControl = (TDiagramControl*)(0x0), bool OnlyUnselected = false, bool OnlyNodes = false, bool OnlyAcceptAnchoreds = false);
	void __fastcall MakeControlVisible(TDiagramControl* AControl);
	TCustomDiagramLineClass __fastcall ConnectionLineClass(void);
	TGroupBlock* __fastcall AddGroup(void);
	TGroupBlock* __fastcall GroupSelectedBlocks(void);
	void __fastcall UngroupSelectedBlocks(void);
	TDiagramPrinter* __fastcall DPrinter(void);
	System::Extended __fastcall MMToMeasUnit(System::Extended AMM);
	System::Extended __fastcall MeasUnitToMM(System::Extended AUnit);
	void __fastcall ClearDControls(void);
	void __fastcall DeleteLayerControls(TDiagramLayer* ALayer);
	__property System::UnicodeString ClipboardNamePrefix = {read=FClipPrefix, write=FClipPrefix};
	__property int PageCount = {read=GetPageCount, nodefault};
	__property int PageColCount = {read=GetPageColCount, nodefault};
	__property int PageRowCount = {read=GetPageRowCount, nodefault};
	__property TDiagramControl* InsertDControl = {read=FInsertDControl};
	__property TCustomDiagramBlock* Blocks[int Index] = {read=GetBlocks};
	__property TCustomDiagramLine* Links[int Index] = {read=GetLinks};
	__property TDiagramControl* DControls[int Index] = {read=GetDControls};
	__property TDiagramControl* Selecteds[int Index] = {read=GetSelecteds};
	__property TMouseState MouseState = {read=FMouseState, nodefault};
	__property int DiagramWidth = {read=GetDiagramWidth, nodefault};
	__property int DiagramHeight = {read=GetDiagramHeight, nodefault};
	__property Diagramutils::TDot MovingStartPoint = {read=FDragStart};
	__property TPaintStyle PaintStyle = {read=FPaintStyle, nodefault};
	__property System::Uitypes::TColor ExportBackgroundColor = {read=FExportBackgroundColor, write=FExportBackgroundColor, nodefault};
	__property double ZoomRatio = {read=GetZoomRatio};
	__property System::UnicodeString ConnectionLineId = {read=FConnectionLineId, write=FConnectionLineId};
	__property TDiagramDragStyle DragStyle = {read=FDragStyle, write=FDragStyle, nodefault};
	__property bool FixedSideLines = {read=FFixedSideLines, write=FFixedSideLines, nodefault};
	__property TDiagramPrintSettings* PrintSettings = {read=FPrintSettings};
	__property System::UnicodeString UnitSymbol = {read=GetUnitSymbol};
	__property TDiagramDesignMode DesignMode = {read=FDesignMode, write=SetDesignMode, nodefault};
	__property Dgrclasses::TDgrGraphicLib GraphicLib = {read=FGraphicLib, write=SetGraphicLib, nodefault};
	__property bool PathDrawingMode = {read=GetPathDrawingMode, nodefault};
	__property TGroupBlockClass CustomGroupBlockClass = {read=FCustomGroupBlockClass, write=SetCustomGroupBlockClass};
	__property TDiagramMemoClass CustomDiagramMemoClass = {read=FCustomDiagramMemoClass, write=SetCustomDiagramMemoClass};
	__property bool UseGdiPlus = {read=GetUseGdiPlus, write=SetUseGdiPlus, nodefault};
	
__published:
	__property bool PaintLinesFirst = {read=FPaintLinesFirst, write=FPaintLinesFirst, default=0};
	__property int NettoExportOffset = {read=FNettoExportOffset, write=FNettoExportOffset, nodefault};
	__property bool AutomaticNodes = {read=FAutomaticNodes, write=SetAutomaticNodes, nodefault};
	__property bool AutoScroll = {read=FAutoScroll, write=SetAutoScroll, nodefault};
	__property bool AutoPage = {read=FAutoPage, write=SetAutoPage, nodefault};
	__property TDiagramBackground* Background = {read=FBackground, write=SetBackground};
	__property TSnapGrid* SnapGrid = {read=FSnapGrid, write=SetSnapGrid};
	__property bool ShowLinkPoints = {read=FShowLinkPoints, write=SetShowLinkPoints, nodefault};
	__property TDiagramRuler* LeftRuler = {read=FLeftRuler, write=SetLeftRuler};
	__property TDiagramRuler* TopRuler = {read=FTopRuler, write=SetTopRuler};
	__property int Zoom = {read=GetZoom, write=SetZoom, nodefault};
	__property System::Uitypes::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, nodefault};
	__property TDiagramScrollBar* VertScrollBar = {read=FVertScrollBar, write=SetVertScrollBar};
	__property TDiagramScrollBar* HorzScrollBar = {read=FHorzScrollBar, write=SetHorzScrollBar};
	__property TMouseWheelMode MouseWheelMode = {read=FMouseWheelMode, write=FMouseWheelMode, nodefault};
	__property __int64 ActiveLayers = {read=FActiveLayers, write=SetActiveLayers};
	__property TDiagramLayers* Layers = {read=FLayers, write=SetLayers};
	__property System::Uitypes::TCursor LinkCursor = {read=FLinkCursor, write=FLinkCursor, nodefault};
	__property System::Uitypes::TCursor PanCursor = {read=FPanCursor, write=FPanCursor, nodefault};
	__property System::Uitypes::TCursor ZoomCursor = {read=FZoomCursor, write=FZoomCursor, nodefault};
	__property bool IgnoreScreenDPI = {read=FIgnoreScreenDPI, write=FIgnoreScreenDPI, nodefault};
	__property bool ShowCrossIndicators = {read=FShowCrossIndicators, write=SetShowCrossIndicators, nodefault};
	__property TPageLines* PageLines = {read=FPageLines, write=SetPageLines};
	__property TDiagramKeyActions KeyActions = {read=FKeyActions, write=FKeyActions, nodefault};
	__property TDiagramHandlesStyle HandlesStyle = {read=FHandlesStyle, write=SetHandlesStyle, nodefault};
	__property Dgrclasses::TDgrSmoothMode SmoothMode = {read=FSmoothMode, write=SetSmoothMode, nodefault};
	__property Dgrclasses::TDgrTextRenderingMode TextRenderingMode = {read=FTextRenderingMode, write=SetTextRenderingMode, nodefault};
	__property TDiagramSelectionMode SelectionMode = {read=FSelectionMode, write=SetSelectionMode, nodefault};
	__property bool CanMoveOutOfBounds = {read=FCanMoveOutOfBounds, write=FCanMoveOutOfBounds, nodefault};
	__property TDiagramPageSettings* PageSettings = {read=FPageSettings, write=SetPageSettings};
	__property bool RulerAutoUnit = {read=FRulerAutoUnit, write=SetRulerAutoUnit, nodefault};
	__property TDiagramMeasUnit MeasUnit = {read=GetMeasUnit, write=SetMeasUnit, nodefault};
	__property bool WheelZoom = {read=FWheelZoom, write=FWheelZoom, nodefault};
	__property int WheelZoomIncrement = {read=FWheelZoomIncrement, write=FWheelZoomIncrement, nodefault};
	__property int WheelZoomMin = {read=FWheelZoomMin, write=FWheelZoomMin, nodefault};
	__property int WheelZoomMax = {read=FWheelZoomMax, write=FWheelZoomMax, nodefault};
	__property TBlockEvent OnInsertBlock = {read=FOnInsertBlock, write=FOnInsertBlock};
	__property TDControlEvent OnInsertDControl = {read=FOnInsertDControl, write=FOnInsertDControl};
	__property TDControlEvent OnRemoveDControl = {read=FOnRemoveDControl, write=FOnRemoveDControl};
	__property TDControlEvent OnSelectDControl = {read=FOnSelectDControl, write=FOnSelectDControl};
	__property TDControlEvent OnUnselectDControl = {read=FOnUnselectDControl, write=FOnUnselectDControl};
	__property TLinkEvent OnInsertLink = {read=FOnInsertLink, write=FOnInsertLink};
	__property System::Classes::TNotifyEvent OnSelectionChanging = {read=FOnSelectionChanging, write=FOnSelectionChanging};
	__property System::Classes::TNotifyEvent OnSelectionChanged = {read=FOnSelectionChanged, write=FOnSelectionChanged};
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
	__property TDrawBlockEvent OnDrawBlock = {read=FOnDrawBlock, write=FOnDrawBlock};
	__property TDrawBlockEvent OnDrawShape = {read=FOnDrawShape, write=FOnDrawShape};
	__property TGetSurroundPtsEvent OnGetSurroundPts = {read=FOnGetSurroundPts, write=FOnGetSurroundPts};
	__property TDControlMouseEvent OnDControlMouseDown = {read=FOnDControlMouseDown, write=FOnDControlMouseDown};
	__property TDControlMouseEvent OnDControlMouseUp = {read=FOnDControlMouseUp, write=FOnDControlMouseUp};
	__property TDControlMouseMoveEvent OnDControlMouseMove = {read=FOnDControlMouseMove, write=FOnDControlMouseMove};
	__property TBlockEvent OnBlockMouseEnter = {read=FOnBlockMouseEnter, write=FOnBlockMouseEnter};
	__property TBlockEvent OnBlockMouseLeave = {read=FOnBlockMouseLeave, write=FOnBlockMouseLeave};
	__property TDControlEvent OnDControlClick = {read=FOnDControlClick, write=FOnDControlClick};
	__property TDControlEvent OnDControlDblClick = {read=FOnDControlDblClick, write=FOnDControlDblClick};
	__property TDiagramLinkEvent OnLinkAdded = {read=FOnLinkAdded, write=FOnLinkAdded};
	__property TDiagramLinkEvent OnLinkRemoved = {read=FOnLinkRemoved, write=FOnLinkRemoved};
	__property TAcceptAnchorEvent OnAcceptAnchor = {read=FOnAcceptAnchor, write=FOnAcceptAnchor};
	__property TAcceptLinkEvent OnAcceptLink = {read=FOnAcceptLink, write=FOnAcceptLink};
	__property System::Classes::TNotifyEvent OnBeforeMove = {read=FOnBeforeMove, write=FOnBeforeMove};
	__property TDiagramPosEvent OnMoving = {read=FOnMoving, write=FOnMoving};
	__property System::Classes::TNotifyEvent OnAfterMove = {read=FOnAfterMove, write=FOnAfterMove};
	__property System::Classes::TNotifyEvent OnBeforeResize = {read=FOnBeforeResize, write=FOnBeforeResize};
	__property TDiagramPosEvent OnDControlResizing = {read=FOnDControlResizing, write=FOnDControlResizing};
	__property System::Classes::TNotifyEvent OnAfterResize = {read=FOnAfterResize, write=FOnAfterResize};
	__property TDiagramPaintEvent OnBeforePaint = {read=FOnBeforePaint, write=FOnBeforePaint};
	__property TDiagramPaintEvent OnAfterPaint = {read=FOnAfterPaint, write=FOnAfterPaint};
	__property TDiagramDrawLinkPointEvent OnDrawLinkPoint = {read=FOnDrawLinkPoint, write=FOnDrawLinkPoint};
	__property TDiagramCloseEditorEvent OnCloseEditor = {read=FOnCloseEditor, write=FOnCloseEditor};
	__property TDrawBlockEvent OnAfterDrawBlock = {read=FOnAfterDrawBlock, write=FOnAfterDrawBlock};
	__property TBeforeCreateControlEvent OnBeforeCreateControl = {read=FOnBeforeCreateControl, write=FOnBeforeCreateControl};
	__property Align = {stored=IsDesignTime, default=0};
	__property Left = {stored=IsDesignTime};
	__property Width = {stored=IsDesignTime};
	__property Top = {stored=IsDesignTime};
	__property Height = {stored=IsDesignTime};
	__property Anchors = {stored=IsDesignTime, default=3};
	__property BevelEdges = {stored=IsDesignTime, default=15};
	__property BevelInner = {index=0, default=2};
	__property BevelOuter = {index=1, default=1};
	__property BevelKind = {stored=IsDesignTime, default=0};
	__property BevelWidth = {stored=IsDesignTime, default=1};
	__property BiDiMode = {stored=IsDesignTime};
	__property Vcl::Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, nodefault};
	__property Constraints = {stored=IsDesignTime};
	__property DockSite = {stored=IsDesignTime, default=0};
	__property DragCursor = {stored=IsDesignTime, default=-12};
	__property DragKind = {stored=IsDesignTime, default=0};
	__property DragMode = {stored=IsDesignTime, default=0};
	__property Enabled = {stored=IsDesignTime, default=1};
	__property Color;
	__property Ctl3D = {stored=IsDesignTime, default=0};
	__property Font;
	__property ParentBiDiMode = {stored=IsDesignTime, default=1};
	__property ParentBackground = {stored=IsDesignTime, default=0};
	__property ParentColor = {default=1};
	__property ParentCtl3D = {default=0};
	__property ParentFont = {default=1};
	__property ParentShowHint = {stored=IsDesignTime, default=1};
	__property PopupMenu = {stored=StoreDesignProperty};
	__property ShowHint = {stored=IsDesignTime};
	__property TabOrder = {stored=IsDesignTime, default=-1};
	__property TabStop = {stored=IsDesignTime, default=0};
	__property Visible = {stored=IsDesignTime, default=1};
	__property OnCanResize;
	__property OnClick;
	__property OnConstrainedResize;
	__property OnContextPopup;
	__property OnDblClick;
	__property OnDockDrop;
	__property OnDockOver;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDock;
	__property OnEndDrag;
	__property OnEnter;
	__property OnExit;
	__property OnGetSiteInfo;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnResize;
	__property OnStartDock;
	__property OnStartDrag;
	__property OnUnDock;
public:
	/* TWinControl.CreateParented */ inline __fastcall TatDiagram(HWND ParentWindow) : Vcl::Controls::TWinControl(ParentWindow) { }
	
};


class DELPHICLASS TStreamDiagram;
class PASCALIMPLEMENTATION TStreamDiagram : public TatDiagram
{
	typedef TatDiagram inherited;
	
private:
	HIDESBASE MESSAGE void __fastcall WMNCPaint(Winapi::Messages::TMessage &Message);
	
public:
	virtual void __fastcall PaintWindow(HDC DC);
	__fastcall virtual TStreamDiagram(System::Classes::TComponent* Owner);
public:
	/* TatDiagram.Destroy */ inline __fastcall virtual ~TStreamDiagram(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TStreamDiagram(HWND ParentWindow) : TatDiagram(ParentWindow) { }
	
};


class DELPHICLASS TRegDControl;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TRegDControl : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FCaption;
	TDiagramControlClass FDControlClass;
	System::UnicodeString FDControlID;
	System::UnicodeString FCategory;
	System::UnicodeString FData;
	Vcl::Graphics::TPicture* FGlyph;
	bool FUseGlyph;
	void __fastcall SetGlyph(Vcl::Graphics::TPicture* const Value);
	__property System::UnicodeString Data = {read=FData, write=FData};
	
public:
	__fastcall virtual TRegDControl(System::Classes::TCollection* Collection);
	__fastcall virtual ~TRegDControl(void);
	__property TDiagramControlClass DControlClass = {read=FDControlClass, write=FDControlClass};
	__property System::UnicodeString DControlID = {read=FDControlID, write=FDControlID};
	__property System::UnicodeString Category = {read=FCategory, write=FCategory};
	__property System::UnicodeString Caption = {read=FCaption, write=FCaption};
	__property Vcl::Graphics::TPicture* Glyph = {read=FGlyph, write=SetGlyph};
	__property bool UseGlyph = {read=FUseGlyph, write=FUseGlyph, nodefault};
};

#pragma pack(pop)

class DELPHICLASS TRegDControls;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TRegDControls : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TRegDControl* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TRegDControl* __fastcall GetItem(int Index);
	
public:
	TRegDControl* __fastcall FindByID(const System::UnicodeString ADControlID);
	HIDESBASE TRegDControl* __fastcall Add(void);
	__property TRegDControl* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TRegDControls(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TRegDControls(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const System::Word WM_TRANSMEMOINVALIDATE = System::Word(0x5f4);
extern DELPHI_PACKAGE System::Word CF_DIAGRAM;
extern DELPHI_PACKAGE TRegDControls* RegDControlList;
extern DELPHI_PACKAGE System::ResourceString _SRegisterDControlError;
#define Atdiagram_SRegisterDControlError System::LoadResourceString(&Atdiagram::_SRegisterDControlError)
#define SDiagramOwnerName L"__DSOwner___"
extern DELPHI_PACKAGE TDiagramPrinters* __fastcall DPrinters(void);
extern DELPHI_PACKAGE void __fastcall RegisterDControl(TDiagramControlClass ADControlClass, System::UnicodeString ADControlID = System::UnicodeString(), System::UnicodeString ACaption = System::UnicodeString(), System::UnicodeString ACategory = System::UnicodeString());
extern DELPHI_PACKAGE void __fastcall RegisterStandardDControls(void);
}	/* namespace Atdiagram */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ATDIAGRAM)
using namespace Atdiagram;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AtdiagramHPP
