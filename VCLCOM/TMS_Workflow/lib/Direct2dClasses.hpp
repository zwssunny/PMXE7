// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Direct2dClasses.pas' rev: 28.00 (Windows)

#ifndef Direct2dclassesHPP
#define Direct2dclassesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.AxCtrls.hpp>	// Pascal unit
#include <Winapi.D2D1.hpp>	// Pascal unit
#include <Vcl.Direct2D.hpp>	// Pascal unit
#include <Winapi.Wincodec.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Winapi.ActiveX.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Direct2dclasses
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TD2DPushKind : unsigned char { pkNone, pkAxisAligned, pkLayer };

class DELPHICLASS TD2DBrush;
class DELPHICLASS TD2DCanvas;
class PASCALIMPLEMENTATION TD2DBrush : public Dgrclasses::TDgrBrush
{
	typedef Dgrclasses::TDgrBrush inherited;
	
private:
	_di_ID2D1Brush FD2DBrush;
	TD2DCanvas* FD2DCanvas;
	Diagramutils::TSquare FGradientRect;
	D2D_MATRIX_3X2_F FRotMatrix;
	Vcl::Graphics::TBrushStyle FBrushStyle;
	void __fastcall CreateD2DBrush(void);
	void __fastcall DestroyD2DBrush(void);
	void __fastcall SetBrushStyle(const Vcl::Graphics::TBrushStyle Value);
	_di_ID2D1Bitmap __fastcall CreateHatchBitmap(Vcl::Graphics::TBrushStyle ABrushStyle);
	
protected:
	virtual void __fastcall Change(void);
	virtual Dgrclasses::TDgrPicture* __fastcall CreatePicture(void);
	_di_ID2D1Brush __fastcall D2DBrush(void);
	virtual void __fastcall DoUpdateBrushPosition(const Diagramutils::TSquare &ARect, double AAngle, const Diagramutils::TDot &ARotCenter);
	
public:
	__fastcall TD2DBrush(TD2DCanvas* ACanvas);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property Vcl::Graphics::TBrushStyle BrushStyle = {read=FBrushStyle, write=SetBrushStyle, nodefault};
public:
	/* TDgrBrush.Destroy */ inline __fastcall virtual ~TD2DBrush(void) { }
	
};


class DELPHICLASS TD2DPen;
class PASCALIMPLEMENTATION TD2DPen : public Dgrclasses::TDgrPen
{
	typedef Dgrclasses::TDgrPen inherited;
	
private:
	TD2DCanvas* FD2DCanvas;
	_di_ID2D1Brush FD2DBrush;
	_di_ID2D1StrokeStyle FStrokeStyle;
	Vcl::Graphics::TPenStyle FPenStyle;
	_di_ID2D1Brush __fastcall GetD2DBrush(void);
	_di_ID2D1StrokeStyle __fastcall GetStrokeStyle(void);
	void __fastcall SetPenStyle(const Vcl::Graphics::TPenStyle Value);
	
protected:
	virtual void __fastcall Change(void);
	__property _di_ID2D1Brush D2DBrush = {read=GetD2DBrush};
	__property _di_ID2D1StrokeStyle StrokeStyle = {read=GetStrokeStyle};
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall TD2DPen(TD2DCanvas* ACanvas);
	__fastcall virtual ~TD2DPen(void);
	
__published:
	__property Vcl::Graphics::TPenStyle PenStyle = {read=FPenStyle, write=SetPenStyle, nodefault};
};


class DELPHICLASS TD2DPaintEngine;
class PASCALIMPLEMENTATION TD2DCanvas : public Dgrclasses::TDgrCanvas
{
	typedef Dgrclasses::TDgrCanvas inherited;
	
private:
	TD2DBrush* FBrush;
	TD2DPen* FPen;
	HDC FCanvasHandle;
	Vcl::Direct2d::TDirect2DCanvas* FInternalCanvas;
	D2D_MATRIX_3X2_F FTransMatrix;
	D2D_MATRIX_3X2_F FStateMatrix;
	Vcl::Direct2d::TDirect2DCanvas* FTempCanvas;
	TD2DPaintEngine* FPaintEngine;
	TD2DPushKind FPushKind;
	_di_IDWriteTextFormat __fastcall CreateDWriteTextFormat(Vcl::Graphics::TFont* AFont, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft);
	void __fastcall DestroyCanvas(void);
	Vcl::Direct2d::TDirect2DCanvas* __fastcall GetDirect2DCanvas(void);
	void __fastcall DoStretchDrawD2DBitmap(const System::Types::TRect &ARect, _di_ID2D1Bitmap ABitmap, int ATransparency);
	
protected:
	virtual void __fastcall Changed(void);
	virtual void __fastcall Changing(void);
	virtual Dgrclasses::TDgrBrush* __fastcall GetBrush(void);
	virtual HDC __fastcall GetHandle(void);
	virtual Dgrclasses::TDgrPen* __fastcall GetPen(void);
	D2D_MATRIX_3X2_F __fastcall GetTransformMatrix(void);
	virtual void __fastcall SetHandle(const HDC Value);
	virtual void __fastcall DoDrawEllipse(double x, double y, double width, double height);
	virtual void __fastcall DoDrawLine(double X1, double Y1, double X2, double Y2);
	virtual void __fastcall DoDrawPath(Dgrclasses::TDgrGraphicsPath* APath);
	virtual void __fastcall DoDrawRectangle(double x, double y, double width, double height);
	virtual void __fastcall DoFillPath(Dgrclasses::TDgrGraphicsPath* APath);
	virtual void __fastcall DoPolygon(Diagramutils::TDotArray APoints);
	virtual void __fastcall DoStretchDraw(const Diagramutils::TSquare &Rect, Vcl::Graphics::TGraphic* Graphic, int ATransparency = 0x0, bool ABitmapTransparent = false)/* overload */;
	virtual void __fastcall DoStretchDraw(const Diagramutils::TSquare &Rect, Dgrclasses::TDgrImage* ADgrImage, int ATransparency = 0x0, bool ABitmapTransparent = false)/* overload */;
	virtual void __fastcall DoUpdateFactors(const Diagramutils::TSquare &ASourceRect, const Diagramutils::TSquare &ADestRect, double AScaleX, double AScaleY);
	
public:
	__fastcall virtual TD2DCanvas(HDC AHandle);
	__fastcall virtual ~TD2DCanvas(void);
	virtual Dgrclasses::TDgrBrush* __fastcall CreateBrush(void);
	virtual Dgrclasses::TDgrGraphic* __fastcall CreateGraphic(void);
	virtual Dgrclasses::TDgrPaintEngine* __fastcall CreatePaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect);
	virtual Dgrclasses::TDgrGraphicsPath* __fastcall CreatePath(void);
	virtual Dgrclasses::TDgrPen* __fastcall CreatePen(void);
	virtual void __fastcall ClipRegion(Dgrclasses::TDgrRegion* ARegion);
	virtual void __fastcall DrawString(System::UnicodeString AStr, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft, int ATransparency);
	virtual void __fastcall RestoreDrawingState(void);
	virtual void __fastcall SaveDrawingState(void);
	virtual Diagramutils::TSquare __fastcall StringBounds(System::UnicodeString AStr, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft);
	virtual int __fastcall TranslateTransform(double AX, double AY);
	virtual int __fastcall ScaleTransform(double AX, double AY);
	virtual int __fastcall RotateTransform(double AAngle)/* overload */;
	virtual int __fastcall RotateTransform(double AAngle, const Diagramutils::TDot &ARotCenter)/* overload */;
	virtual int __fastcall ResetClip(void);
	virtual int __fastcall ResetTransform(void);
	virtual int __fastcall SetClip(const Diagramutils::TSquare &ARect)/* overload */;
	virtual int __fastcall SetClip(HRGN ARegion)/* overload */;
	__property Vcl::Direct2d::TDirect2DCanvas* Direct2DCanvas = {read=GetDirect2DCanvas};
};


class DELPHICLASS TD2DBlockDrawer;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TD2DBlockDrawer : public Dgrclasses::TDgrBlockDrawer
{
	typedef Dgrclasses::TDgrBlockDrawer inherited;
	
private:
	TD2DCanvas* FD2DCanvas;
	
protected:
	virtual void __fastcall DoRotatePath(Dgrclasses::TDgrGraphicsPath* APath);
	virtual Dgrclasses::TDgrCanvas* __fastcall GetCanvas(void);
	virtual void __fastcall SetPaintEngine(Dgrclasses::TDgrPaintEngine* const Value);
	
public:
	__fastcall virtual TD2DBlockDrawer(void);
	__fastcall virtual ~TD2DBlockDrawer(void);
	virtual void __fastcall TranslateRectsPath(Dgrclasses::TDgrGraphicsPath* APath);
	__property TD2DCanvas* D2DCanvas = {read=FD2DCanvas};
};

#pragma pack(pop)

class DELPHICLASS TD2DGraphicsPath;
class PASCALIMPLEMENTATION TD2DGraphicsPath : public Dgrclasses::TDgrGraphicsPath
{
	typedef Dgrclasses::TDgrGraphicsPath inherited;
	
private:
	_di_ID2D1PathGeometry FD2DPath;
	_di_ID2D1GeometrySink FD2DSink;
	_di_ID2D1TransformedGeometry FTransPath;
	D2D_MATRIX_3X2_F FTransMatrix;
	Diagramutils::TDot FPosition;
	bool FFigureOpen;
	void __fastcall CreateD2DPath(void);
	void __fastcall DestroyD2DPath(void);
	_di_ID2D1PathGeometry __fastcall GetD2DPath(void);
	_di_ID2D1GeometrySink __fastcall GetD2DSink(void);
	void __fastcall SinkBeginFigure(const Diagramutils::TDot &APoint, D2D1_FIGURE_BEGIN AFigBegin);
	void __fastcall SinkEndFigure(D2D1_FIGURE_END AFigEnd);
	void __fastcall SetTransMatrix(const D2D_MATRIX_3X2_F &Value);
	_di_ID2D1TransformedGeometry __fastcall GetTransPath(void);
	void __fastcall CheckFinished(void);
	
protected:
	__property D2D_MATRIX_3X2_F TransMatrix = {read=FTransMatrix, write=SetTransMatrix};
	
public:
	__fastcall TD2DGraphicsPath(void);
	__fastcall virtual ~TD2DGraphicsPath(void);
	virtual int __fastcall AddArc(double x, double y, double width, double height, double startAngle, double sweepAngle);
	virtual int __fastcall AddBezier(double X1, double Y1, double X2, double Y2, double x3, double y3, double x4, double y4);
	virtual int __fastcall AddEllipse(double x, double y, double width, double height);
	virtual int __fastcall AddLine(double X1, double Y1, double X2, double Y2);
	virtual int __fastcall AddLines(Diagramutils::TDotArray points);
	virtual int __fastcall AddPolygon(Diagramutils::TDotArray points);
	virtual int __fastcall AddRectangle(const Diagramutils::TSquare &Rect);
	virtual int __fastcall AddRoundRect(double X1, double Y1, double X2, double Y2, double x3, double y3);
	virtual int __fastcall CloseFigure(bool AClosePath = true);
	virtual Dgrclasses::TDgrRegion* __fastcall CreateRegion(void);
	virtual int __fastcall GetPointCount(void);
	virtual bool __fastcall IsVisible(int x, int y);
	virtual int __fastcall Reset(void);
	virtual int __fastcall SetFillMode(Vcl::Graphics::TFillMode fillmode);
	virtual int __fastcall StartFigure(void);
	__property _di_ID2D1PathGeometry D2DPath = {read=GetD2DPath};
	__property _di_ID2D1GeometrySink D2DSink = {read=GetD2DSink};
	__property _di_ID2D1TransformedGeometry TransPath = {read=GetTransPath};
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TD2DPaintEngine : public Dgrclasses::TDgrPaintEngine
{
	typedef Dgrclasses::TDgrPaintEngine inherited;
	
private:
	Vcl::Direct2d::TDirect2DCanvas* FDirect2DCanvas;
	
protected:
	virtual void __fastcall SetSmoothMode(const Dgrclasses::TDgrSmoothMode Value);
	virtual void __fastcall SetTextRenderingMode(const Dgrclasses::TDgrTextRenderingMode Value);
	
public:
	__fastcall virtual TD2DPaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect);
	__fastcall virtual ~TD2DPaintEngine(void);
	virtual void __fastcall BeginDraw(void);
	virtual void __fastcall EndDraw(void);
	virtual void __fastcall FillRect(const System::Types::TRect &ARect, System::Uitypes::TColor AColor);
	virtual int __fastcall ResetTransform(void);
	virtual int __fastcall RotateTransform(double AAngle);
	virtual int __fastcall ScaleTransform(double AX, double AY);
	virtual int __fastcall TranslateTransform(double AX, double AY);
};

#pragma pack(pop)

class DELPHICLASS TD2DRegion;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TD2DRegion : public Dgrclasses::TDgrRegion
{
	typedef Dgrclasses::TDgrRegion inherited;
	
private:
	_di_ID2D1PathGeometry FD2DPath;
	TD2DGraphicsPath* FPath;
	
public:
	__fastcall virtual TD2DRegion(Dgrclasses::TDgrGraphicsPath* APath);
	virtual HRGN __fastcall GetHRGN(Dgrclasses::TDgrCanvas* ACanvas);
	virtual bool __fastcall IsVisible(const Diagramutils::TSquare &ARect);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TD2DRegion(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TD2DGraphic;
class PASCALIMPLEMENTATION TD2DGraphic : public Dgrclasses::TDgrGraphic
{
	typedef Dgrclasses::TDgrGraphic inherited;
	
private:
	bool FBitmapTransparent;
	_di_ID2D1Bitmap FD2DBitmap;
	_di_IWICBitmap FWICBitmap;
	void __fastcall CreateD2DBitmap(Vcl::Direct2d::TDirect2DCanvas* ACanvas);
	void __fastcall MakeBitmapTransparent(_di_IWICBitmap ABMP);
	
protected:
	virtual void __fastcall Changed(System::TObject* Sender);
	virtual bool __fastcall DoGetImageSizes(void);
	virtual void __fastcall DoDraw(Vcl::Graphics::TCanvas* ACanvas, const Diagramutils::TSquare &ARect);
	_di_ID2D1Bitmap __fastcall GetD2DBitmap(Vcl::Direct2d::TDirect2DCanvas* ACanvas);
	
public:
	__fastcall virtual TD2DGraphic(void);
	__fastcall virtual ~TD2DGraphic(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
};


class DELPHICLASS TD2DPicture;
class PASCALIMPLEMENTATION TD2DPicture : public Dgrclasses::TDgrPicture
{
	typedef Dgrclasses::TDgrPicture inherited;
	
public:
	__fastcall virtual TD2DPicture(void);
	__fastcall virtual ~TD2DPicture(void);
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterD2DFileFormats(void);
extern DELPHI_PACKAGE void __fastcall UnRegisterD2DFileFormats(void);
}	/* namespace Direct2dclasses */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DIRECT2DCLASSES)
using namespace Direct2dclasses;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Direct2dclassesHPP
