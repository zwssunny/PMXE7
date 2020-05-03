// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Preview.pas' rev: 5.00

#ifndef PreviewHPP
#define PreviewHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Printers.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <WinSpool.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Preview
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EInvalidPreviewData;
class PASCALIMPLEMENTATION EInvalidPreviewData : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EInvalidPreviewData(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EInvalidPreviewData(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EInvalidPreviewData(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EInvalidPreviewData(int Ident, const System::TVarRec 
		* Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EInvalidPreviewData(const AnsiString Msg, int AHelpContext
		) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalidPreviewData(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EInvalidPreviewData(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidPreviewData(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EInvalidPreviewData(void) { }
	#pragma option pop
	
};


class DELPHICLASS TMetaFileList;
class PASCALIMPLEMENTATION TMetaFileList : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FRecords;
	Classes::TStream* FDataStream;
	Graphics::TMetafile* FMetaFile;
	bool FUseTempFile;
	AnsiString FTempFile;
	Classes::TNotifyEvent FOnChange;
	int __fastcall GetCount(void);
	Graphics::TMetafile* __fastcall GetItems(int Index);
	void __fastcall SetUseTempFile(bool Value);
	Classes::TStream* __fastcall CreateMetaFileStream(void);
	
public:
	__fastcall TMetaFileList(void);
	__fastcall virtual ~TMetaFileList(void);
	void __fastcall Clear(void);
	int __fastcall Add(Graphics::TMetafile* AMetaFile);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall SaveToFile(const AnsiString FileName);
	__property int Count = {read=GetCount, nodefault};
	__property Graphics::TMetafile* Items[int Index] = {read=GetItems/*, default*/};
	__property bool UseTempFile = {read=FUseTempFile, write=SetUseTempFile, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


typedef void __fastcall (__closure *TPaperPaintEvent)(System::TObject* Sender, Graphics::TCanvas* Canvas
	, const Windows::TRect &PageRect);

class DELPHICLASS TPaperPreview;
class PASCALIMPLEMENTATION TPaperPreview : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
private:
	Graphics::TColor FPaperColor;
	Graphics::TColor FBorderColor;
	Controls::TBorderWidth FBorderSize;
	Graphics::TColor FShadowColor;
	Controls::TBorderWidth FShadowSize;
	Classes::TNotifyEvent FOnResize;
	TPaperPaintEvent FOnPaint;
	Graphics::TBitmap* FOffScreen;
	bool FOffScreenOK;
	void __fastcall SetPaperWidth(int Value);
	int __fastcall GetPaperWidth(void);
	void __fastcall SetPaperHeight(int Value);
	int __fastcall GetPaperHeight(void);
	void __fastcall SetPaperColor(Graphics::TColor Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	void __fastcall SetBorderSize(Controls::TBorderWidth Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetShadowSize(Controls::TBorderWidth Value);
	
protected:
	__property Canvas ;
	virtual void __fastcall Paint(void);
	DYNAMIC Windows::TRect __fastcall PageRect(void);
	HIDESBASE MESSAGE void __fastcall WMSize(Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	int __fastcall ActualWidth(int APaperWidth);
	int __fastcall ActualHeight(int APaperHeight);
	int __fastcall LogicalWidth(int AWidth);
	int __fastcall LogicalHeight(int AHeight);
	__property bool OffScreenOK = {read=FOffScreenOK, nodefault};
	
public:
	__fastcall virtual TPaperPreview(Classes::TComponent* AOwner);
	__fastcall virtual ~TPaperPreview(void);
	
__published:
	__property Align ;
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=0};
	__property Controls::TBorderWidth BorderSize = {read=FBorderSize, write=SetBorderSize, default=1};
	__property Color ;
	__property Cursor ;
	__property DragCursor ;
	__property DragMode ;
	__property ParentColor ;
	__property ParentShowHint ;
	__property PopupMenu ;
	__property Graphics::TColor PaperColor = {read=FPaperColor, write=SetPaperColor, default=16777215};
		
	__property int PaperWidth = {read=GetPaperWidth, write=SetPaperWidth, nodefault};
	__property int PaperHeight = {read=GetPaperHeight, write=SetPaperHeight, nodefault};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=-2147483632
		};
	__property Controls::TBorderWidth ShadowSize = {read=FShadowSize, write=SetShadowSize, default=3};
	__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDRop ;
	__property OnDragOver ;
	__property OnKeyDown ;
	__property OnKeyPress ;
	__property OnKeyUp ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property Classes::TNotifyEvent OnResize = {read=FOnResize, write=FOnResize};
	__property TPaperPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TPaperPreview(HWND ParentWindow) : Controls::TCustomControl(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TPaperPreviewOptions;
class PASCALIMPLEMENTATION TPaperPreviewOptions : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	Graphics::TColor FPaperColor;
	Graphics::TColor FBorderColor;
	Controls::TBorderWidth FBorderWidth;
	Graphics::TColor FShadowColor;
	Controls::TBorderWidth FShadowWidth;
	Controls::TCursor FCursor;
	Controls::TCursor FDragCursor;
	Controls::TCursor FGrabCursor;
	Menus::TPopupMenu* FPopupMenu;
	Classes::TNotifyEvent FOnChange;
	void __fastcall SetPaperColor(Graphics::TColor Value);
	void __fastcall SetBorderColor(Graphics::TColor Value);
	void __fastcall SetBorderWidth(Controls::TBorderWidth Value);
	void __fastcall SetShadowColor(Graphics::TColor Value);
	void __fastcall SetShadowWidth(Controls::TBorderWidth Value);
	void __fastcall SetCursor(Controls::TCursor Value);
	void __fastcall SetDragCursor(Controls::TCursor Value);
	void __fastcall SetGrabCursor(Controls::TCursor Value);
	void __fastcall SetPopupMenu(Menus::TPopupMenu* Value);
	
protected:
	void __fastcall DoChange(void);
	
public:
	__fastcall TPaperPreviewOptions(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property Graphics::TColor BorderColor = {read=FBorderColor, write=SetBorderColor, default=0};
	__property Controls::TBorderWidth BorderWidth = {read=FBorderWidth, write=SetBorderWidth, default=1
		};
	__property Controls::TCursor Cursor = {read=FCursor, write=SetCursor, default=0};
	__property Controls::TCursor DragCursor = {read=FDragCursor, write=SetDragCursor, default=10};
	__property Controls::TCursor GrabCursor = {read=FGrabCursor, write=SetGrabCursor, default=11};
	__property Graphics::TColor PaperColor = {read=FPaperColor, write=SetPaperColor, default=16777215};
		
	__property Menus::TPopupMenu* PopupMenu = {read=FPopupMenu, write=SetPopupMenu};
	__property Graphics::TColor ShadowColor = {read=FShadowColor, write=SetShadowColor, default=-2147483632
		};
	__property Controls::TBorderWidth ShadowWidth = {read=FShadowWidth, write=SetShadowWidth, default=3
		};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPaperPreviewOptions(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TPreviewPrintProgress)(System::TObject* Sender, int PageNum, int 
	Progress, bool &AbortIt);

#pragma option push -b-
enum TPreviewState { psReady, psCreating, psPrinting };
#pragma option pop

#pragma option push -b-
enum TZoomState { zsZoomOther, zsZoomToWidth, zsZoomToHeight, zsZoomToFit };
#pragma option pop

#pragma option push -b-
enum TUnits { mmPixel, mmLoMetric, mmHiMetric, mmLoEnglish, mmHiEnglish, mmTWIPS };
#pragma option pop

#pragma option push -b-
enum TPaperType { pLetter, pLetterSmall, pTabloid, pLedger, pLegal, pStatement, pExecutive, pA3, pA4, 
	pA4Small, pA5, pB4, pB5, pFolio, pQuatro, p10x14, p11x17, pNote, pEnv9, pEnv10, pEnv11, pEnv12, pEnv14, 
	pCSheet, pDSheet, pESheet, pEnvDL, pEnvC5, pEnvC3, pEnvC4, pEnvC6, pEnvC65, pEnvB4, pEnvB5, pEnvB6, 
	pEnvItaly, pEnvMonarch, pEnvPersonal, pFanfoldUSStd, pFanfoldGermanStd, pFanfoldGermanLegal, pB4ISO, 
	pJapanesePostcard, p9x11, p10x11, p15x11, pEnvInvite, pLetterExtra, pLegalExtra, TabloidExtra, pA4Extra, 
	pLetterTransverse, pA4Transverse, pLetterExtraTransverse, pAPlus, pBPlus, pLetterPlus, pA4Plus, pA5Transverse, 
	pB5Transverse, pA3Extra, pA5Extra, pB5Extra, pA2, pA3Transverse, pA3ExtraTransverse, pCustom };
#pragma option pop

class DELPHICLASS TPrintPreview;
class PASCALIMPLEMENTATION TPrintPreview : public Forms::TScrollBox 
{
	typedef Forms::TScrollBox inherited;
	
private:
	TPaperPreview* FPaperView;
	TPaperPreviewOptions* FPaperViewOptions;
	AnsiString FPrintJobTitle;
	TMetaFileList* FPages;
	Graphics::TCanvas* FCanvas;
	TUnits FUnits;
	Windows::TPoint FPixels;
	bool FAborted;
	Printers::TPrinterOrientation FOrientation;
	int FCurrentPage;
	TPaperType FPaperType;
	int FPaperWidth;
	int FPaperHeight;
	TPreviewState FState;
	int FZoom;
	TZoomState FZoomState;
	bool FZoomSavePos;
	int FZoomMin;
	int FZoomMax;
	int FZoomStep;
	bool FFastPrint;
	bool FUsePrinterOptions;
	Classes::TNotifyEvent FOnBeginDoc;
	Classes::TNotifyEvent FOnEndDoc;
	Classes::TNotifyEvent FOnNewPage;
	Classes::TNotifyEvent FOnAbort;
	Classes::TNotifyEvent FOnChange;
	TPreviewPrintProgress FOnPrintProgress;
	Classes::TNotifyEvent FOnBeforePrint;
	Classes::TNotifyEvent FOnAfterPrint;
	Classes::TNotifyEvent FOnZoomChange;
	Windows::TPoint FOldMousePos;
	bool FCanScrollHorz;
	bool FCanScrollVert;
	bool FDraggingPage;
	Windows::TPoint DPI;
	Graphics::TMetafile* MetaFile;
	int WheelAccumulator;
	void __fastcall SetPaperViewOptions(TPaperPreviewOptions* Value);
	void __fastcall SetUnits(TUnits Value);
	void __fastcall SetPaperType(TPaperType Value);
	void __fastcall SetPaperWidth(int Value);
	void __fastcall SetPaperHeight(int Value);
	void __fastcall SetOrientation(Printers::TPrinterOrientation Value);
	void __fastcall SetZoomState(TZoomState Value);
	void __fastcall SetZoom(int Value);
	void __fastcall SetZoomMin(int Value);
	void __fastcall SetZoomMax(int Value);
	void __fastcall SetCurrentPage(int Value);
	bool __fastcall GetUseTempFile(void);
	void __fastcall SetUseTempFile(bool Value);
	int __fastcall GetTotalPages(void);
	Graphics::TMetafile* __fastcall GetPages(int PageNo);
	Graphics::TCanvas* __fastcall GetCanvas(void);
	bool __fastcall GetPrinterInstalled(void);
	Windows::TPoint __fastcall CalculateViewSize(const Windows::TPoint &Space);
	bool __fastcall IsCustomPaper(void);
	bool __fastcall IsZoomStored(void);
	void __fastcall PaperClick(System::TObject* Sender);
	void __fastcall PaperDblClick(System::TObject* Sender);
	void __fastcall PaperMouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall PaperMouseMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	void __fastcall PaperMouseUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState 
		Shift, int X, int Y);
	void __fastcall PaperViewOptionsChanged(System::TObject* Sender);
	void __fastcall PagesChanged(System::TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CNKeyDown(Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseWheel(Messages::TMessage &Message);
	
protected:
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall Resize(void);
	virtual void __fastcall DoProgress(int Current, int Done, int Total);
	virtual void __fastcall PaintPage(System::TObject* Sender, Graphics::TCanvas* Canvas, const Windows::TRect 
		&PageRect);
	virtual void __fastcall CalculateMetafileSize(void);
	virtual void __fastcall CreateMetaFileCanvas(void);
	virtual void __fastcall CloseMetaFileCanvas(void);
	virtual void __fastcall AdjustCanvasView(void);
	virtual Windows::TRect __fastcall GetPrintPageBounds(void);
	
public:
	__fastcall virtual TPrintPreview(Classes::TComponent* AOwner);
	__fastcall virtual ~TPrintPreview(void);
	int __fastcall ConvertUnit(int Value, TUnits FromUnit, TUnits ToUnit);
	int __fastcall ToPrinterUnit(int Value, int Resolution);
	int __fastcall Screen2PrinterUnit(int Value);
	Windows::TPoint __fastcall PaintGraphic(int X, int Y, Graphics::TGraphic* Graphic);
	Windows::TRect __fastcall PaintGraphicEx(const Windows::TRect &Rect, Graphics::TGraphic* Graphic, bool 
		Proportinal, bool ShrinkOnly, bool Center);
	Windows::TPoint __fastcall PaintWinControl(int X, int Y, Controls::TWinControl* WinControl);
	Windows::TRect __fastcall PaintWinControlEx(const Windows::TRect &Rect, Controls::TWinControl* WinControl
		, bool Proportinal, bool ShrinkOnly, bool Center);
	int __fastcall PaintRichText(const Windows::TRect &Rect, Comctrls::TCustomRichEdit* RichEdit, int MaxPages
		, Windows::PInteger pOffset);
	int __fastcall GetRichTextRect(Windows::TRect &Rect, Comctrls::TCustomRichEdit* RichEdit, Windows::PInteger 
		pOffset);
	void __fastcall Clear(void);
	void __fastcall BeginDoc(void);
	void __fastcall EndDoc(void);
	void __fastcall NewPage(void);
	void __fastcall Abort(void);
	void __fastcall Print(void);
	void __fastcall UpdateZoom(void);
	void __fastcall SetPrinterOptions(void);
	void __fastcall GetPrinterOptions(void);
	void __fastcall PrintPages(int FirstPage, int LastPage);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromFile(const AnsiString FileName);
	void __fastcall SaveToFile(const AnsiString FileName);
	__property bool Aborted = {read=FAborted, nodefault};
	__property Graphics::TCanvas* Canvas = {read=GetCanvas};
	__property int TotalPages = {read=GetTotalPages, nodefault};
	__property TPreviewState State = {read=FState, nodefault};
	__property bool PrinterInstalled = {read=GetPrinterInstalled, nodefault};
	__property int CurrentPage = {read=FCurrentPage, write=SetCurrentPage, nodefault};
	__property Graphics::TMetafile* Pages[int PageNo] = {read=GetPages};
	
__published:
	__property Align ;
	__property bool FastPrint = {read=FFastPrint, write=FFastPrint, default=1};
	__property TabStop ;
	__property ParentFont ;
	__property AnsiString PrintJobTitle = {read=FPrintJobTitle, write=FPrintJobTitle};
	__property TUnits Units = {read=FUnits, write=SetUnits, default=2};
	__property Printers::TPrinterOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0
		};
	__property TPaperType PaperType = {read=FPaperType, write=SetPaperType, default=8};
	__property TPaperPreviewOptions* PaperView = {read=FPaperViewOptions, write=SetPaperViewOptions};
	__property int PaperWidth = {read=FPaperWidth, write=SetPaperWidth, stored=IsCustomPaper, nodefault
		};
	__property int PaperHeight = {read=FPaperHeight, write=SetPaperHeight, stored=IsCustomPaper, nodefault
		};
	__property TZoomState ZoomState = {read=FZoomState, write=SetZoomState, default=3};
	__property int Zoom = {read=FZoom, write=SetZoom, stored=IsZoomStored, nodefault};
	__property int ZoomMin = {read=FZoomMin, write=SetZoomMin, default=10};
	__property int ZoomMax = {read=FZoomMax, write=SetZoomMax, default=500};
	__property bool ZoomSavePos = {read=FZoomSavePos, write=FZoomSavePos, default=1};
	__property int ZoomStep = {read=FZoomStep, write=FZoomStep, default=10};
	__property bool UsePrinterOptions = {read=FUsePrinterOptions, write=FUsePrinterOptions, default=0};
		
	__property bool UseTempFile = {read=GetUseTempFile, write=SetUseTempFile, default=0};
	__property Classes::TNotifyEvent OnBeginDoc = {read=FOnBeginDoc, write=FOnBeginDoc};
	__property Classes::TNotifyEvent OnEndDoc = {read=FOnEndDoc, write=FOnEndDoc};
	__property Classes::TNotifyEvent OnNewPage = {read=FOnNewPage, write=FOnNewPage};
	__property Classes::TNotifyEvent OnAbort = {read=FOnAbort, write=FOnAbort};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TPreviewPrintProgress OnPrintProgress = {read=FOnPrintProgress, write=FOnPrintProgress};
		
	__property Classes::TNotifyEvent OnBeforePrint = {read=FOnBeforePrint, write=FOnBeforePrint};
	__property Classes::TNotifyEvent OnAfterPrint = {read=FOnAfterPrint, write=FOnAfterPrint};
	__property Classes::TNotifyEvent OnZoomChange = {read=FOnZoomChange, write=FOnZoomChange};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TPrintPreview(HWND ParentWindow) : Forms::TScrollBox(
		ParentWindow) { }
	#pragma option pop
	
};


struct TPaperSizeInfo
{
	short ID;
	int Width;
	int Height;
	TUnits Units;
} ;

//-- var, const, procedure ---------------------------------------------------
static const Shortint crHand = 0xa;
static const Shortint crGrab = 0xb;
extern PACKAGE TPaperSizeInfo PaperSizes[67];
extern PACKAGE void __fastcall DrawGraphicAsDIB(HDC DC, const Windows::TRect &Rect, Graphics::TGraphic* 
	Graphic);
extern PACKAGE int __fastcall ConvertUnits(int Value, int DPI, TUnits InUnits, TUnits OutUnits);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Preview */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Preview;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Preview
