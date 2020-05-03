// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Zgrids.pas' rev: 27.00 (Windows)

#ifndef ZgridsHPP
#define ZgridsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <System.RTLConsts.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Vcl.Menus.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Mask.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Zgrids
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EInvalidGridOperation;
#pragma pack(push,4)
class PASCALIMPLEMENTATION EInvalidGridOperation : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInvalidGridOperation(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInvalidGridOperation(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInvalidGridOperation(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInvalidGridOperation(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalidGridOperation(NativeUInt Ident, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalidGridOperation(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInvalidGridOperation(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalidGridOperation(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalidGridOperation(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalidGridOperation(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidGridOperation(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidGridOperation(NativeUInt Ident, System::TVarRec const *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInvalidGridOperation(void) { }
	
};

#pragma pack(pop)

typedef int __fastcall (__closure *TGetExtentsFunc)(int Index);

struct DECLSPEC_DRECORD TGridAxisDrawInfo
{
public:
	int EffectiveLineWidth;
	int FixedBoundary;
	int GridBoundary;
	int GridExtent;
	int LastFullVisibleCell;
	int FullVisBoundary;
	int FixedCellCount;
	int FirstGridCell;
	int GridCellCount;
	TGetExtentsFunc GetExtent;
};


struct DECLSPEC_DRECORD TGridDrawInfo
{
public:
	TGridAxisDrawInfo Horz;
	TGridAxisDrawInfo Vert;
};


enum DECLSPEC_DENUM TGridState : unsigned char { gsNormal, gsSelecting, gsRowSizing, gsColSizing, gsRowMoving, gsColMoving };

typedef TGridState TGridMovement;

typedef void __fastcall (__closure *TFillEvent)(System::TObject* Sender, int RowStart, int RowEnd);

class DELPHICLASS TBYInplaceEdit;
class DELPHICLASS TBYCustomGrid;
class PASCALIMPLEMENTATION TBYInplaceEdit : public Vcl::Mask::TCustomMaskEdit
{
	typedef Vcl::Mask::TCustomMaskEdit inherited;
	
private:
	TBYCustomGrid* FGrid;
	int FClickTime;
	bool FIsKeyDown;
	void __fastcall InternalMove(const System::Types::TRect &Loc, bool Redraw);
	void __fastcall SetGrid(TBYCustomGrid* Value);
	HIDESBASE MESSAGE void __fastcall CMShowingChanged(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall WMGetDlgCode(Winapi::Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall WMPaste(void *Message);
	HIDESBASE MESSAGE void __fastcall WMCut(void *Message);
	MESSAGE void __fastcall WMClear(void *Message);
	MESSAGE void __fastcall WMUndo(void *Message);
	
protected:
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	DYNAMIC void __fastcall DblClick(void);
	DYNAMIC bool __fastcall DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos);
	virtual bool __fastcall EditCanModify(void);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(System::WideChar &Key);
	DYNAMIC void __fastcall KeyUp(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall BoundsChanged(void);
	virtual void __fastcall UpdateContents(void);
	virtual void __fastcall MyTextOnChange(System::TObject* Sender);
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	__property TBYCustomGrid* Grid = {read=FGrid};
	
public:
	System::UnicodeString OldText;
	__fastcall virtual TBYInplaceEdit(System::Classes::TComponent* AOwner);
	void __fastcall Deselect(void);
	HIDESBASE void __fastcall Hide(void);
	HIDESBASE void __fastcall Invalidate(void);
	void __fastcall Move(const System::Types::TRect &Loc);
	bool __fastcall PosEqual(const System::Types::TRect &Rect);
	HIDESBASE void __fastcall SetFocus(void);
	void __fastcall UpdateLoc(const System::Types::TRect &Loc);
	HIDESBASE bool __fastcall Visible(void);
	
__published:
	__property OnChange;
public:
	/* TWinControl.CreateParented */ inline __fastcall TBYInplaceEdit(HWND ParentWindow) : Vcl::Mask::TCustomMaskEdit(ParentWindow) { }
	/* TWinControl.Destroy */ inline __fastcall virtual ~TBYInplaceEdit(void) { }
	
};


enum DECLSPEC_DENUM TGridOption : unsigned char { goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goTabs, goRowSelect, goAlwaysShowEditor, goThumbTracking };

typedef System::Set<TGridOption, TGridOption::goFixedVertLine, TGridOption::goThumbTracking> TGridOptions;

enum DECLSPEC_DENUM Zgrids__3 : unsigned char { gdSelected, gdFocused, gdFixed };

typedef System::Set<Zgrids__3, Zgrids__3::gdSelected, Zgrids__3::gdFixed> TBYGridDrawState;

enum DECLSPEC_DENUM Zgrids__4 : unsigned char { sdLeft, sdRight, sdUp, sdDown };

typedef System::Set<Zgrids__4, Zgrids__4::sdLeft, Zgrids__4::sdDown> TGridScrollDirection;

struct DECLSPEC_DRECORD TGridCoord
{
public:
	int X;
	int Y;
};


struct DECLSPEC_DRECORD TGridRect
{
	union
	{
		struct 
		{
			TGridCoord TopLeft;
			TGridCoord BottomRight;
		};
		struct 
		{
			int Left;
			int Top;
			int Right;
			int Bottom;
		};
		
	};
};


typedef void __fastcall (__closure *TSelectCellEvent)(System::TObject* Sender, int ACol, int ARow, bool &CanSelect);

typedef void __fastcall (__closure *TDrawCellEvent)(System::TObject* Sender, int ACol, int ARow, const System::Types::TRect &Rect, TBYGridDrawState State);

typedef void __fastcall (__closure *TEditControlChange)(System::TObject* Sender, int ACol, int ARow, System::UnicodeString Text);

typedef void __fastcall (__closure *TBeforeMovedEvent)(System::TObject* Sender, int FromIndex, int ToIndex, bool &CanMove);

class PASCALIMPLEMENTATION TBYCustomGrid : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	TGridCoord FAnchor;
	Vcl::Forms::TFormBorderStyle FBorderStyle;
	bool FCanEditModify;
	int FColCount;
	void *FColWidths;
	void *FTabStops;
	TGridCoord FCurrent;
	int FDefaultColWidth;
	int FDefaultRowHeight;
	int FFixedRowHeight;
	int FFixedCols;
	int FFixedRows;
	System::Uitypes::TColor FFixedColor;
	int FGridLineWidth;
	TGridOptions FOptions;
	int FRowCount;
	void *FRowHeights;
	bool FHasFooter;
	int FFootHeight;
	bool FAutoCal;
	System::Uitypes::TScrollStyle FScrollBars;
	TGridCoord FTopLeft;
	int FSizingIndex;
	int FSizingPos;
	int FSizingOfs;
	int FMoveIndex;
	int FMovePos;
	System::Types::TPoint FHitTest;
	TBYInplaceEdit* FInplaceEdit;
	int FInplaceCol;
	int FInplaceRow;
	int FColOffset;
	bool FDefaultDrawing;
	bool FEditorMode;
	TEditControlChange FOnEditControlChange;
	TBeforeMovedEvent FOnBeforeColumnMoved;
	TBeforeMovedEvent FOnBeforeRowMoved;
	TGridCoord __fastcall CalcCoordFromPoint(int X, int Y, const TGridDrawInfo &DrawInfo);
	void __fastcall CalcDrawInfoXY(TGridDrawInfo &DrawInfo, int UseWidth, int UseHeight);
	TGridCoord __fastcall CalcMaxTopLeft(const TGridCoord &Coord, const TGridDrawInfo &DrawInfo);
	void __fastcall CancelMode(void);
	void __fastcall ChangeGridOrientation(bool RightToLeftOrientation);
	void __fastcall ChangeSize(int NewColCount, int NewRowCount);
	void __fastcall ClampInView(const TGridCoord &Coord);
	void __fastcall DrawSizingLine(const TGridDrawInfo &DrawInfo);
	void __fastcall DrawMove(void);
	void __fastcall FocusCell(int ACol, int ARow, bool MoveAnchor);
	void __fastcall GridRectToScreenRect(const TGridRect &GridRect, System::Types::TRect &ScreenRect, bool IncludeLine);
	void __fastcall HideEdit(void);
	void __fastcall Initialize(void);
	void __fastcall InvalidateGrid(void);
	void __fastcall ModifyScrollBar(unsigned ScrollBar, unsigned ScrollCode, unsigned Pos, bool UseRightToLeft);
	void __fastcall MoveAdjust(int &CellPos, int FromIndex, int ToIndex);
	void __fastcall MoveAnchor(const TGridCoord &NewAnchor);
	void __fastcall MoveAndScroll(int Mouse, int CellHit, TGridDrawInfo &DrawInfo, TGridAxisDrawInfo &Axis, int Scrollbar, const System::Types::TPoint &MousePt);
	void __fastcall MoveCurrent(int ACol, int ARow, bool MoveAnchor, bool Show);
	void __fastcall MoveTopLeft(int ALeft, int ATop);
	void __fastcall ResizeCol(int Index, int OldSize, int NewSize);
	void __fastcall ResizeRow(int Index, int OldSize, int NewSize);
	void __fastcall SelectionMoved(const TGridRect &OldSel);
	void __fastcall ScrollDataInfo(int DX, int DY, TGridDrawInfo &DrawInfo);
	void __fastcall TopLeftMoved(const TGridCoord &OldTopLeft);
	void __fastcall UpdateScrollPos(void);
	void __fastcall UpdateScrollRange(void);
	int __fastcall GetColWidths(int Index);
	int __fastcall GetRowHeights(int Index);
	TGridRect __fastcall GetSelection(void);
	bool __fastcall GetTabStops(int Index);
	int __fastcall GetVisibleColCount(void);
	int __fastcall GetVisibleRowCount(void);
	bool __fastcall IsActiveControl(void);
	void __fastcall ReadColWidths(System::Classes::TReader* Reader);
	void __fastcall ReadRowHeights(System::Classes::TReader* Reader);
	void __fastcall SetBorderStyle(Vcl::Forms::TBorderStyle Value);
	void __fastcall SetCol(int Value);
	void __fastcall SetColCount(int Value);
	void __fastcall SetColWidths(int Index, int Value);
	void __fastcall SetDefaultColWidth(int Value);
	void __fastcall SetDefaultRowHeight(int Value);
	void __fastcall SetFixedRowHeight(int Value);
	void __fastcall SetEditorMode(bool Value);
	void __fastcall SetFixedColor(System::Uitypes::TColor Value);
	void __fastcall SetFixedCols(int Value);
	void __fastcall SetFixedRows(int Value);
	void __fastcall SetHasFooter(bool Value);
	void __fastcall SetFootHeight(int Value);
	void __fastcall SetAutoCal(bool Value);
	void __fastcall SetGridLineWidth(int Value);
	void __fastcall SetLeftCol(int Value);
	void __fastcall SetOptions(TGridOptions Value);
	void __fastcall SetRow(int Value);
	void __fastcall SetRowHeights(int Index, int Value);
	void __fastcall SetScrollBars(System::Uitypes::TScrollStyle Value);
	void __fastcall SetSelection(const TGridRect &Value);
	void __fastcall SetTabStops(int Index, bool Value);
	void __fastcall SetTopRow(int Value);
	void __fastcall UpdateEdit(void);
	void __fastcall UpdateText(void);
	void __fastcall WriteColWidths(System::Classes::TWriter* Writer);
	void __fastcall WriteRowHeights(System::Classes::TWriter* Writer);
	MESSAGE void __fastcall CMCancelMode(Winapi::Messages::TMessage &Msg);
	HIDESBASE MESSAGE void __fastcall CMFontChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMCtl3DChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMDesignHitTest(Winapi::Messages::TWMMouse &Msg);
	MESSAGE void __fastcall CMWantSpecialKey(Winapi::Messages::TWMKey &Msg);
	HIDESBASE MESSAGE void __fastcall CMShowingChanged(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMChar(Winapi::Messages::TWMKey &Msg);
	HIDESBASE MESSAGE void __fastcall WMCancelMode(Winapi::Messages::TWMNoParams &Msg);
	HIDESBASE MESSAGE void __fastcall WMCommand(Winapi::Messages::TWMCommand &Message);
	MESSAGE void __fastcall WMGetDlgCode(Winapi::Messages::TWMNoParams &Msg);
	HIDESBASE MESSAGE void __fastcall WMHScroll(Winapi::Messages::TWMScroll &Msg);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Winapi::Messages::TWMKillFocus &Msg);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Winapi::Messages::TWMNCHitTest &Msg);
	HIDESBASE MESSAGE void __fastcall WMSetCursor(Winapi::Messages::TWMSetCursor &Msg);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Winapi::Messages::TWMSetFocus &Msg);
	HIDESBASE MESSAGE void __fastcall WMSize(Winapi::Messages::TWMSize &Msg);
	MESSAGE void __fastcall WMTimer(Winapi::Messages::TWMTimer &Msg);
	HIDESBASE MESSAGE void __fastcall WMVScroll(Winapi::Messages::TWMScroll &Msg);
	
protected:
	bool FUpdating;
	TGridState FGridState;
	bool FSaveCellExtents;
	TGridOptions DesignOptionsBoost;
	bool VirtualView;
	virtual void __fastcall ReCalculate(int ACol, int ARow);
	void __fastcall InvalidateRect(const TGridRect &ARect);
	void __fastcall CalcDrawInfo(TGridDrawInfo &DrawInfo);
	void __fastcall CalcFixedInfo(TGridDrawInfo &DrawInfo);
	virtual void __fastcall CalcSizingState(int X, int Y, TGridState &State, int &Index, int &SizingPos, int &SizingOfs, TGridDrawInfo &FixedInfo);
	virtual TBYInplaceEdit* __fastcall CreateEditor(void);
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(System::WideChar &Key);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	HIDESBASEDYNAMIC void __fastcall AdjustSize(int Index, int Amount, bool Rows);
	System::Types::TRect __fastcall BoxRect(int ALeft, int ATop, int ARight, int ABottom);
	DYNAMIC void __fastcall DoExit(void);
	System::Types::TRect __fastcall CellRect(int ACol, int ARow);
	DYNAMIC bool __fastcall CanEditAcceptKey(System::WideChar Key);
	DYNAMIC bool __fastcall CanGridAcceptKey(System::Word Key, System::Classes::TShiftState Shift);
	DYNAMIC bool __fastcall CanEditModify(void);
	virtual bool __fastcall CanEditShow(void);
	DYNAMIC bool __fastcall DoMouseWheelDown(System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos);
	DYNAMIC bool __fastcall DoMouseWheelUp(System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos);
	DYNAMIC System::UnicodeString __fastcall GetEditText(int ACol, int ARow);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const System::UnicodeString Value);
	DYNAMIC System::UnicodeString __fastcall GetEditMask(int ACol, int ARow);
	DYNAMIC int __fastcall GetEditLimit(void);
	int __fastcall GetGridWidth(void);
	int __fastcall GetGridHeight(void);
	void __fastcall HideEditor(void);
	void __fastcall ShowEditor(void);
	void __fastcall ShowEditorChar(System::WideChar Ch);
	void __fastcall InvalidateEditor(void);
	void __fastcall MoveColumn(int FromIndex, int ToIndex);
	DYNAMIC void __fastcall ColumnMoved(int FromIndex, int ToIndex);
	void __fastcall MoveRow(int FromIndex, int ToIndex);
	DYNAMIC void __fastcall RowMoved(int FromIndex, int ToIndex);
	virtual void __fastcall DrawCell(int ACol, int ARow, const System::Types::TRect &ARect, TBYGridDrawState AState) = 0 ;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall MoveColRow(int ACol, int ARow, bool MoveAnchor, bool Show);
	virtual bool __fastcall SelectCell(int ACol, int ARow);
	DYNAMIC void __fastcall SizeChanged(int OldColCount, int OldRowCount);
	bool __fastcall Sizing(int X, int Y);
	void __fastcall ScrollData(int DX, int DY);
	virtual void __fastcall InvalidateCell(int ACol, int ARow);
	void __fastcall InvalidateCol(int ACol);
	void __fastcall InvalidateRow(int ARow);
	DYNAMIC void __fastcall TopLeftChanged(void);
	virtual void __fastcall SetRowCount(int Value);
	DYNAMIC void __fastcall TimedScroll(TGridScrollDirection Direction);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall ColWidthsChanged(void);
	DYNAMIC void __fastcall RowHeightsChanged(void);
	virtual void __fastcall DeleteColumn(int ACol);
	virtual void __fastcall DeleteRow(int ARow);
	void __fastcall UpdateDesigner(void);
	DYNAMIC bool __fastcall BeginColumnDrag(int &Origin, int &Destination, const System::Types::TPoint &MousePt);
	DYNAMIC bool __fastcall BeginRowDrag(int &Origin, int &Destination, const System::Types::TPoint &MousePt);
	DYNAMIC bool __fastcall CheckColumnDrag(int &Origin, int &Destination, const System::Types::TPoint &MousePt);
	DYNAMIC bool __fastcall CheckRowDrag(int &Origin, int &Destination, const System::Types::TPoint &MousePt);
	DYNAMIC bool __fastcall EndColumnDrag(int &Origin, int &Destination, const System::Types::TPoint &MousePt);
	DYNAMIC bool __fastcall EndRowDrag(int &Origin, int &Destination, const System::Types::TPoint &MousePt);
	__property Vcl::Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, default=1};
	__property int Col = {read=FCurrent.X, write=SetCol, nodefault};
	__property Color = {default=-16777211};
	__property int ColCount = {read=FColCount, write=SetColCount, default=5};
	__property int ColWidths[int Index] = {read=GetColWidths, write=SetColWidths};
	__property int DefaultColWidth = {read=FDefaultColWidth, write=SetDefaultColWidth, default=64};
	__property bool DefaultDrawing = {read=FDefaultDrawing, write=FDefaultDrawing, default=1};
	__property int DefaultRowHeight = {read=FDefaultRowHeight, write=SetDefaultRowHeight, default=24};
	__property int FixedRowHeight = {read=FFixedRowHeight, write=SetFixedRowHeight, default=20};
	__property bool EditorMode = {read=FEditorMode, write=SetEditorMode, nodefault};
	__property System::Uitypes::TColor FixedColor = {read=FFixedColor, write=SetFixedColor, default=-16777201};
	__property int FixedCols = {read=FFixedCols, write=SetFixedCols, default=1};
	__property int FixedRows = {read=FFixedRows, write=SetFixedRows, default=1};
	__property int GridHeight = {read=GetGridHeight, nodefault};
	__property int GridLineWidth = {read=FGridLineWidth, write=SetGridLineWidth, default=1};
	__property int GridWidth = {read=GetGridWidth, nodefault};
	__property System::Types::TPoint HitTest = {read=FHitTest};
	__property TBYInplaceEdit* InplaceEditor = {read=FInplaceEdit};
	__property int LeftCol = {read=FTopLeft.X, write=SetLeftCol, nodefault};
	__property TGridOptions Options = {read=FOptions, write=SetOptions, default=31};
	__property ParentColor = {default=0};
	__property int Row = {read=FCurrent.Y, write=SetRow, nodefault};
	__property int RowCount = {read=FRowCount, write=SetRowCount, default=5};
	__property int RowHeights[int Index] = {read=GetRowHeights, write=SetRowHeights};
	__property System::Uitypes::TScrollStyle ScrollBars = {read=FScrollBars, write=SetScrollBars, default=3};
	__property TGridRect Selection = {read=GetSelection, write=SetSelection};
	__property bool TabStops[int Index] = {read=GetTabStops, write=SetTabStops};
	__property int TopRow = {read=FTopLeft.Y, write=SetTopRow, nodefault};
	__property int VisibleColCount = {read=GetVisibleColCount, nodefault};
	__property int VisibleRowCount = {read=GetVisibleRowCount, nodefault};
	__property bool HasFooter = {read=FHasFooter, write=SetHasFooter, default=0};
	__property int FootHeight = {read=FFootHeight, write=SetFootHeight, nodefault};
	__property bool AutoCal = {read=FAutoCal, write=SetAutoCal, default=0};
	__property TEditControlChange OnEditControlChange = {read=FOnEditControlChange, write=FOnEditControlChange};
	__property TBeforeMovedEvent OnBeforeColumnMoved = {read=FOnBeforeColumnMoved, write=FOnBeforeColumnMoved};
	__property TBeforeMovedEvent OnBeforeRowMoved = {read=FOnBeforeRowMoved, write=FOnBeforeRowMoved};
	
public:
	__fastcall virtual TBYCustomGrid(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBYCustomGrid(void);
	TGridCoord __fastcall MouseCoord(int X, int Y);
	
__published:
	__property TabStop = {default=1};
public:
	/* TWinControl.CreateParented */ inline __fastcall TBYCustomGrid(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
};


typedef void __fastcall (__closure *TGetEditEvent)(System::TObject* Sender, int ACol, int ARow, System::UnicodeString &Value);

typedef void __fastcall (__closure *TSetEditEvent)(System::TObject* Sender, int ACol, int ARow, const System::UnicodeString Value);

typedef void __fastcall (__closure *TMovedEvent)(System::TObject* Sender, int FromIndex, int ToIndex);

class DELPHICLASS TBYDrawGrid;
class PASCALIMPLEMENTATION TBYDrawGrid : public TBYCustomGrid
{
	typedef TBYCustomGrid inherited;
	
private:
	TMovedEvent FOnColumnMoved;
	TDrawCellEvent FOnDrawCell;
	TGetEditEvent FOnGetEditMask;
	TGetEditEvent FOnGetEditText;
	TMovedEvent FOnRowMoved;
	TSelectCellEvent FOnSelectCell;
	TSetEditEvent FOnSetEditText;
	System::Classes::TNotifyEvent FOnTopLeftChanged;
	
protected:
	DYNAMIC void __fastcall ColumnMoved(int FromIndex, int ToIndex);
	virtual void __fastcall DrawCell(int ACol, int ARow, const System::Types::TRect &ARect, TBYGridDrawState AState);
	DYNAMIC System::UnicodeString __fastcall GetEditMask(int ACol, int ARow);
	DYNAMIC System::UnicodeString __fastcall GetEditText(int ACol, int ARow);
	DYNAMIC void __fastcall RowMoved(int FromIndex, int ToIndex);
	virtual bool __fastcall SelectCell(int ACol, int ARow);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const System::UnicodeString Value);
	DYNAMIC void __fastcall TopLeftChanged(void);
	
public:
	HIDESBASE System::Types::TRect __fastcall CellRect(int ACol, int ARow);
	void __fastcall MouseToCell(int X, int Y, int &ACol, int &ARow);
	__property Canvas;
	__property Col;
	__property ColWidths;
	__property EditorMode;
	__property GridHeight;
	__property GridWidth;
	__property LeftCol;
	__property Selection;
	__property Row;
	__property RowHeights;
	__property TabStops;
	__property TopRow;
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property BiDiMode;
	__property BorderStyle = {default=1};
	__property Color = {default=-16777211};
	__property ColCount = {default=5};
	__property Constraints;
	__property Ctl3D;
	__property DefaultColWidth = {default=64};
	__property DefaultRowHeight = {default=24};
	__property DefaultDrawing = {default=1};
	__property DragCursor = {default=-12};
	__property DragKind = {default=0};
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property FixedColor = {default=-16777201};
	__property FixedCols = {default=1};
	__property RowCount = {default=5};
	__property FixedRows = {default=1};
	__property Font;
	__property GridLineWidth = {default=1};
	__property Options = {default=31};
	__property ParentBiDiMode = {default=1};
	__property ParentColor = {default=0};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ScrollBars = {default=3};
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property VisibleColCount;
	__property VisibleRowCount;
	__property OnClick;
	__property TMovedEvent OnColumnMoved = {read=FOnColumnMoved, write=FOnColumnMoved};
	__property OnBeforeColumnMoved;
	__property OnBeforeRowMoved;
	__property OnContextPopup;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property TDrawCellEvent OnDrawCell = {read=FOnDrawCell, write=FOnDrawCell};
	__property OnEditControlChange;
	__property OnEndDock;
	__property OnEndDrag;
	__property OnEnter;
	__property OnExit;
	__property TGetEditEvent OnGetEditMask = {read=FOnGetEditMask, write=FOnGetEditMask};
	__property TGetEditEvent OnGetEditText = {read=FOnGetEditText, write=FOnGetEditText};
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property TMovedEvent OnRowMoved = {read=FOnRowMoved, write=FOnRowMoved};
	__property TSelectCellEvent OnSelectCell = {read=FOnSelectCell, write=FOnSelectCell};
	__property TSetEditEvent OnSetEditText = {read=FOnSetEditText, write=FOnSetEditText};
	__property OnStartDock;
	__property OnStartDrag;
	__property System::Classes::TNotifyEvent OnTopLeftChanged = {read=FOnTopLeftChanged, write=FOnTopLeftChanged};
public:
	/* TBYCustomGrid.Create */ inline __fastcall virtual TBYDrawGrid(System::Classes::TComponent* AOwner) : TBYCustomGrid(AOwner) { }
	/* TBYCustomGrid.Destroy */ inline __fastcall virtual ~TBYDrawGrid(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBYDrawGrid(HWND ParentWindow) : TBYCustomGrid(ParentWindow) { }
	
};


class DELPHICLASS TBYStringGridStrings;
class DELPHICLASS TBYStringGrid;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TBYStringGridStrings : public System::Classes::TStrings
{
	typedef System::Classes::TStrings inherited;
	
private:
	TBYStringGrid* FGrid;
	int FIndex;
	void __fastcall CalcXY(int Index, int &X, int &Y);
	
protected:
	virtual System::UnicodeString __fastcall Get(int Index);
	virtual int __fastcall GetCount(void);
	virtual System::TObject* __fastcall GetObject(int Index);
	virtual void __fastcall Put(int Index, const System::UnicodeString S);
	virtual void __fastcall PutObject(int Index, System::TObject* AObject);
	virtual void __fastcall SetUpdateState(bool Updating);
	
public:
	__fastcall TBYStringGridStrings(TBYStringGrid* AGrid, int AIndex);
	virtual int __fastcall Add(const System::UnicodeString S);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Clear(void);
	virtual void __fastcall Delete(int Index);
	virtual void __fastcall Insert(int Index, const System::UnicodeString S);
public:
	/* TStrings.Destroy */ inline __fastcall virtual ~TBYStringGridStrings(void) { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TBYStringGrid : public TBYDrawGrid
{
	typedef TBYDrawGrid inherited;
	
private:
	void *FData;
	void *FRows;
	void *FCols;
	int FEditUpdate;
	TFillEvent FOnFill;
	void __fastcall DisableEditUpdate(void);
	void __fastcall EnableEditUpdate(void);
	HIDESBASE void __fastcall Initialize(void);
	HIDESBASE void __fastcall Update(int ACol, int ARow);
	void __fastcall SetUpdateState(bool Updating);
	System::UnicodeString __fastcall GetCells(int ACol, int ARow);
	System::Classes::TStrings* __fastcall GetCols(int Index);
	System::TObject* __fastcall GetObjects(int ACol, int ARow);
	System::Classes::TStrings* __fastcall GetRows(int Index);
	void __fastcall SetCols(int Index, System::Classes::TStrings* Value);
	void __fastcall SetObjects(int ACol, int ARow, System::TObject* Value);
	void __fastcall SetRows(int Index, System::Classes::TStrings* Value);
	int __fastcall GetRecNo(int Index);
	bool __fastcall GetFilledRow(int Index);
	bool __fastcall GetFilledGroup(int Index);
	System::UnicodeString __fastcall GetData(int Index);
	double __fastcall GetDoubleData(int ACol, int ARow);
	void __fastcall SetRecNo(int Index, int ARecNo);
	void __fastcall SetFilledRow(int Index, bool AValue);
	void __fastcall SetFilledGroup(int Index, bool AValue);
	void __fastcall SetData(int Index, System::UnicodeString AValue);
	void __fastcall SetDoubleData(int ACol, int ARow, double AValue);
	
protected:
	TBYStringGridStrings* __fastcall EnsureColRow(int Index, bool IsCol);
	void * __fastcall EnsureDataRow(int ARow);
	void __fastcall SetCells(int ACol, int ARow, const System::UnicodeString Value);
	DYNAMIC void __fastcall ColumnMoved(int FromIndex, int ToIndex);
	virtual void __fastcall DrawCell(int ACol, int ARow, const System::Types::TRect &ARect, TBYGridDrawState AState);
	DYNAMIC System::UnicodeString __fastcall GetEditText(int ACol, int ARow);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const System::UnicodeString Value);
	DYNAMIC void __fastcall RowMoved(int FromIndex, int ToIndex);
	virtual void __fastcall SetRowCount(int Value);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TBYStringGrid(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBYStringGrid(void);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	__property System::UnicodeString Cells[int ACol][int ARow] = {read=GetCells, write=SetCells};
	__property System::Classes::TStrings* Cols[int Index] = {read=GetCols, write=SetCols};
	__property System::TObject* Objects[int ACol][int ARow] = {read=GetObjects, write=SetObjects};
	__property System::Classes::TStrings* Rows[int Index] = {read=GetRows, write=SetRows};
	__property double DoubleData[int ACol][int ARow] = {read=GetDoubleData, write=SetDoubleData};
	__property int RecNo[int Index] = {read=GetRecNo, write=SetRecNo};
	__property bool FilledRow[int Index] = {read=GetFilledRow, write=SetFilledRow};
	__property bool FilledGroup[int Index] = {read=GetFilledGroup, write=SetFilledGroup};
	__property System::UnicodeString Data[int Index] = {read=GetData, write=SetData};
	void __fastcall InsertRow(int Index);
	virtual void __fastcall DeleteRow(int ARow);
	__property RowHeights;
	__property ColWidths;
	
__published:
	__property TFillEvent OnFill = {read=FOnFill, write=FOnFill};
public:
	/* TWinControl.CreateParented */ inline __fastcall TBYStringGrid(HWND ParentWindow) : TBYDrawGrid(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const int MaxCustomExtents = int(0x7ffffff);
static const System::Int8 MaxShortInt = System::Int8(127);
}	/* namespace Zgrids */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ZGRIDS)
using namespace Zgrids;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ZgridsHPP
