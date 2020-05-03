// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GdipClasses.pas' rev: 28.00 (Windows)

#ifndef GdipclassesHPP
#define GdipclassesHPP

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
#include <DgrGdipApi.hpp>	// Pascal unit
#include <DgrGdipObj.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Winapi.ActiveX.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Gdipclasses
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TGdipGraphic;
class PASCALIMPLEMENTATION TGdipGraphic : public Dgrclasses::TDgrGraphic
{
	typedef Dgrclasses::TDgrGraphic inherited;
	
private:
	Dgrgdipobj::TGPImage* FGPImage;
	void __fastcall CreateGPImage(void);
	void __fastcall DestroyGPImage(void);
	
protected:
	virtual void __fastcall Changed(System::TObject* Sender);
	Dgrgdipobj::TGPImage* __fastcall GPImage(void);
	virtual bool __fastcall DoGetImageSizes(void);
	virtual void __fastcall DoDraw(Vcl::Graphics::TCanvas* ACanvas, const Diagramutils::TSquare &ARect);
	
public:
	__fastcall virtual TGdipGraphic(void);
	__fastcall virtual ~TGdipGraphic(void);
};


class DELPHICLASS TGdipPicture;
class PASCALIMPLEMENTATION TGdipPicture : public Dgrclasses::TDgrPicture
{
	typedef Dgrclasses::TDgrPicture inherited;
	
private:
	Dgrgdipobj::TGPImage* FGPImage;
	void __fastcall CreateGPImage(void);
	void __fastcall DestroyGPImage(void);
	
protected:
	DYNAMIC void __fastcall Changed(System::TObject* Sender);
	Dgrgdipobj::TGPImage* __fastcall GPImage(void);
	
public:
	__fastcall virtual TGdipPicture(void);
	__fastcall virtual ~TGdipPicture(void);
};


class DELPHICLASS TGdipImage;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGdipImage : public Dgrclasses::TDgrImage
{
	typedef Dgrclasses::TDgrImage inherited;
	
private:
	Dgrgdipobj::TGPImage* FGPImage;
	void __fastcall CreateGPImage(void);
	void __fastcall DestroyGPImage(void);
	Dgrgdipobj::TGPImage* __fastcall GetGPImage(void);
	
protected:
	__property Dgrgdipobj::TGPImage* GPImage = {read=GetGPImage, write=FGPImage};
	
public:
	__fastcall TGdipImage(void);
	__fastcall virtual ~TGdipImage(void);
};

#pragma pack(pop)

class DELPHICLASS TGdipBrush;
class PASCALIMPLEMENTATION TGdipBrush : public Dgrclasses::TDgrBrush
{
	typedef Dgrclasses::TDgrBrush inherited;
	
private:
	Dgrgdipobj::TGPBrush* FGPBrush;
	Dgrgdipapi::TGPRectF FGradientRect;
	Dgrgdipapi::HatchStyle FHatchStyle;
	Dgrgdipobj::TGPMatrix* FRotMatrix;
	void __fastcall CreateGPBrush(void);
	void __fastcall DestroyGPBrush(void);
	void __fastcall SetHatchStyle(const Dgrgdipapi::HatchStyle Value);
	
protected:
	virtual void __fastcall Change(void);
	virtual Dgrclasses::TDgrPicture* __fastcall CreatePicture(void);
	Dgrgdipobj::TGPBrush* __fastcall GetGPBrush(void);
	virtual void __fastcall DoUpdateBrushPosition(const Diagramutils::TSquare &ARect, double AAngle, const Diagramutils::TDot &ARotCenter);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TGdipBrush(void);
	__fastcall virtual ~TGdipBrush(void);
	__property Dgrgdipobj::TGPBrush* GPBrush = {read=GetGPBrush};
	
__published:
	__property Dgrgdipapi::HatchStyle HatchStyle = {read=FHatchStyle, write=SetHatchStyle, nodefault};
};


class DELPHICLASS TGdipPen;
class PASCALIMPLEMENTATION TGdipPen : public Dgrclasses::TDgrPen
{
	typedef Dgrclasses::TDgrPen inherited;
	
private:
	Dgrgdipobj::TGPPen* FGPPen;
	Dgrgdipapi::DashStyle FDashStyle;
	void __fastcall CreateGPPen(void);
	void __fastcall DestroyGPPen(void);
	void __fastcall SetDashStyle(const Dgrgdipapi::DashStyle Value);
	
protected:
	virtual void __fastcall Change(void);
	Dgrgdipobj::TGPPen* __fastcall GetGPPen(void);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TGdipPen(void);
	__fastcall virtual ~TGdipPen(void);
	__property Dgrgdipobj::TGPPen* GPPen = {read=GetGPPen};
	
__published:
	__property Dgrgdipapi::DashStyle DashStyle = {read=FDashStyle, write=SetDashStyle, nodefault};
};


class DELPHICLASS TGPCanvas;
class PASCALIMPLEMENTATION TGPCanvas : public Dgrclasses::TDgrCanvas
{
	typedef Dgrclasses::TDgrCanvas inherited;
	
private:
	TGdipBrush* FBrush;
	Dgrgdipobj::TGPGraphics* FInternalGraphics;
	TGdipPen* FPen;
	Dgrgdipobj::TGPGraphics* FTempGraphics;
	Dgrgdipobj::TGPMatrix* FTransMatrix;
	unsigned FDrawingState;
	Dgrgdipobj::TGPFont* __fastcall CreateGPFont(Vcl::Graphics::TFont* AFont);
	Dgrgdipobj::TGPStringFormat* __fastcall CreateGPStringFormat(System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft);
	void __fastcall DestroyGraphics(void);
	Dgrgdipobj::TGPGraphics* __fastcall GetGraphics(void);
	void __fastcall DoDrawGPPath(Dgrgdipobj::TGPGraphicsPath* APath);
	void __fastcall DoFillGPPath(Dgrgdipobj::TGPGraphicsPath* APath);
	
protected:
	virtual Dgrclasses::TDgrBrush* __fastcall GetBrush(void);
	virtual HDC __fastcall GetHandle(void);
	virtual Dgrclasses::TDgrPen* __fastcall GetPen(void);
	virtual void __fastcall SetHandle(const HDC Value);
	virtual void __fastcall DoDrawEllipse(double x, double y, double width, double height);
	virtual void __fastcall DoDrawLine(double X1, double Y1, double X2, double Y2);
	virtual void __fastcall DoDrawPath(Dgrclasses::TDgrGraphicsPath* APath);
	virtual void __fastcall DoDrawRectangle(double x, double y, double width, double height);
	virtual void __fastcall DoFillPath(Dgrclasses::TDgrGraphicsPath* APath);
	virtual void __fastcall DoPolygon(Diagramutils::TDotArray APoints);
	virtual void __fastcall DoStretchDraw(const Diagramutils::TSquare &Rect, Vcl::Graphics::TGraphic* Graphic, int ATransparency = 0x0, bool ABitmapTransparent = false)/* overload */;
	virtual void __fastcall DoStretchDraw(const Diagramutils::TSquare &Rect, Dgrclasses::TDgrImage* ADgrImage, int ATransparency = 0x0, bool ABitmapTransparent = false)/* overload */;
	void __fastcall DoStretchDrawGPImage(const Diagramutils::TSquare &Rect, Dgrgdipobj::TGPImage* AGPImage, int ATransparency = 0x0, bool ABitmapTransparent = false);
	virtual void __fastcall DoUpdateFactors(const Diagramutils::TSquare &ASourceRect, const Diagramutils::TSquare &ADestRect, double AScaleX, double AScaleY);
	
public:
	__fastcall virtual TGPCanvas(HDC AHandle);
	__fastcall virtual ~TGPCanvas(void);
	virtual Dgrclasses::TDgrBrush* __fastcall CreateBrush(void);
	virtual Dgrclasses::TDgrGraphic* __fastcall CreateGraphic(void);
	virtual Dgrclasses::TDgrPaintEngine* __fastcall CreatePaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect);
	virtual Dgrclasses::TDgrGraphicsPath* __fastcall CreatePath(void);
	virtual Dgrclasses::TDgrPen* __fastcall CreatePen(void);
	virtual void __fastcall DrawString(System::UnicodeString AStr, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft, int ATransparency);
	virtual void __fastcall RestoreDrawingState(void);
	virtual void __fastcall SaveDrawingState(void);
	virtual Diagramutils::TSquare __fastcall StringBounds(System::UnicodeString AStr, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft);
	virtual int __fastcall TranslateTransform(double AX, double AY);
	virtual int __fastcall ScaleTransform(double AX, double AY);
	virtual int __fastcall ResetClip(void);
	virtual int __fastcall ResetTransform(void);
	virtual int __fastcall RotateTransform(double AAngle)/* overload */;
	virtual int __fastcall SetClip(const Diagramutils::TSquare &ARect)/* overload */;
	virtual int __fastcall SetClip(HRGN ARegion)/* overload */;
	HIDESBASE void __fastcall DrawPath(Dgrclasses::TDgrGraphicsPath* APath)/* overload */;
	HIDESBASE void __fastcall DrawPath(Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	HIDESBASE void __fastcall AddRoundRectPath(Dgrclasses::TDgrGraphicsPath* APath, double X1, double Y1, double X2, double Y2, double X3, double Y3)/* overload */;
	HIDESBASE void __fastcall AddRoundRectPath(Dgrgdipobj::TGPGraphicsPath* APath, double X1, double Y1, double X2, double Y2, double X3, double Y3)/* overload */;
	HIDESBASE void __fastcall Path(Dgrclasses::TDgrGraphicsPath* APath)/* overload */;
	HIDESBASE void __fastcall Path(Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	__property Dgrgdipobj::TGPGraphics* GPGraphics = {read=GetGraphics};
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  RotateTransform(double AAngle, const Diagramutils::TDot &ARotCenter){ return Dgrclasses::TDgrCanvas::RotateTransform(AAngle, ARotCenter); }
	
};


class DELPHICLASS TGPBlockDrawer;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPBlockDrawer : public Dgrclasses::TDgrBlockDrawer
{
	typedef Dgrclasses::TDgrBlockDrawer inherited;
	
private:
	TGPCanvas* FGPCanvas;
	Dgrgdipobj::TGPMatrix* FMatrix;
	void __fastcall DoRotateGPPath(Dgrgdipobj::TGPGraphicsPath* APath);
	
protected:
	virtual void __fastcall DoRotatePath(Dgrclasses::TDgrGraphicsPath* APath);
	virtual Dgrclasses::TDgrCanvas* __fastcall GetCanvas(void);
	virtual void __fastcall SetPaintEngine(Dgrclasses::TDgrPaintEngine* const Value);
	
public:
	__fastcall virtual TGPBlockDrawer(void);
	__fastcall virtual ~TGPBlockDrawer(void);
	virtual void __fastcall TranslateRectsPath(Dgrclasses::TDgrGraphicsPath* APath);
	HIDESBASE void __fastcall TransformPath(Dgrclasses::TDgrGraphicsPath* APath)/* overload */;
	HIDESBASE void __fastcall TransformPath(Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	HIDESBASE void __fastcall RotatePath(Dgrclasses::TDgrGraphicsPath* APath)/* overload */;
	HIDESBASE void __fastcall RotatePath(Dgrgdipobj::TGPGraphicsPath* APath)/* overload */;
	void __fastcall SetGraphics(Dgrgdipobj::TGPGraphics* AGPGraphics);
	__property TGPCanvas* GPCanvas = {read=FGPCanvas};
};

#pragma pack(pop)

class DELPHICLASS TGdipGraphicsPath;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGdipGraphicsPath : public Dgrclasses::TDgrGraphicsPath
{
	typedef Dgrclasses::TDgrGraphicsPath inherited;
	
private:
	Dgrgdipobj::TGPGraphicsPath* FGPPath;
	void __fastcall CreateGPPath(void);
	void __fastcall DestroyGPPath(void);
	Dgrgdipobj::TGPGraphicsPath* __fastcall GetGPPath(void);
	
public:
	__fastcall TGdipGraphicsPath(void);
	__fastcall virtual ~TGdipGraphicsPath(void);
	virtual int __fastcall AddArc(double x, double y, double width, double height, double startAngle, double sweepAngle);
	virtual int __fastcall AddBezier(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
	virtual int __fastcall AddEllipse(double x, double y, double width, double height);
	virtual int __fastcall AddLine(double x1, double y1, double x2, double y2);
	virtual int __fastcall AddLines(Diagramutils::TDotArray points);
	virtual int __fastcall AddPolygon(Diagramutils::TDotArray points);
	virtual int __fastcall AddRectangle(const Diagramutils::TSquare &rect);
	virtual int __fastcall AddRoundRect(double X1, double Y1, double X2, double Y2, double X3, double Y3);
	virtual int __fastcall CloseFigure(bool AClosePath = true);
	virtual Dgrclasses::TDgrRegion* __fastcall CreateRegion(void);
	virtual int __fastcall GetPointCount(void);
	virtual bool __fastcall IsVisible(int x, int y);
	virtual int __fastcall Reset(void);
	virtual int __fastcall SetFillMode(Vcl::Graphics::TFillMode fillmode);
	virtual int __fastcall StartFigure(void);
	__property Dgrgdipobj::TGPGraphicsPath* GPPath = {read=GetGPPath};
};

#pragma pack(pop)

class DELPHICLASS TGdipPaintEngine;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGdipPaintEngine : public Dgrclasses::TDgrPaintEngine
{
	typedef Dgrclasses::TDgrPaintEngine inherited;
	
private:
	Dgrgdipobj::TGPGraphics* FGPGraphics;
	
protected:
	virtual void __fastcall SetPageUnit(const Dgrclasses::TDgrPageUnit Value);
	virtual void __fastcall SetSmoothMode(const Dgrclasses::TDgrSmoothMode Value);
	virtual void __fastcall SetTextRenderingMode(const Dgrclasses::TDgrTextRenderingMode Value);
	
public:
	__fastcall virtual TGdipPaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect);
	__fastcall virtual ~TGdipPaintEngine(void);
	virtual void __fastcall FillRect(const System::Types::TRect &ARect, System::Uitypes::TColor AColor);
	virtual int __fastcall ResetTransform(void);
	virtual int __fastcall RotateTransform(double AAngle);
	virtual int __fastcall ScaleTransform(double AX, double AY);
	virtual int __fastcall TranslateTransform(double AX, double AY);
	__property Dgrgdipobj::TGPGraphics* GPGraphics = {read=FGPGraphics};
};

#pragma pack(pop)

class DELPHICLASS TGdipRegion;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGdipRegion : public Dgrclasses::TDgrRegion
{
	typedef Dgrclasses::TDgrRegion inherited;
	
private:
	Dgrgdipobj::TGPRegion* FGPRegion;
	
public:
	__fastcall virtual TGdipRegion(Dgrclasses::TDgrGraphicsPath* APath);
	__fastcall virtual ~TGdipRegion(void);
	virtual HRGN __fastcall GetHRGN(Dgrclasses::TDgrCanvas* ACanvas);
	virtual bool __fastcall IsVisible(const Diagramutils::TSquare &ARect);
	__property Dgrgdipobj::TGPRegion* GPRegion = {read=FGPRegion};
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterGdipFileFormats(void);
extern DELPHI_PACKAGE void __fastcall UnRegisterGdipFileFormats(void);
extern DELPHI_PACKAGE unsigned __fastcall ColorToARGB(System::Uitypes::TColor AColor, System::Byte Alpha = (System::Byte)(0xff));
extern DELPHI_PACKAGE Dgrgdipapi::TGPPointF __fastcall PointGP(float x, float y);
extern DELPHI_PACKAGE Dgrgdipapi::TGPRectF __fastcall RectGP(const Diagramutils::TSquare &ASquare);
extern DELPHI_PACKAGE Diagramutils::TSquare __fastcall ToSquare(const Dgrgdipapi::TGPRectF &ARectGP);
extern DELPHI_PACKAGE Diagramutils::TSquare __fastcall ToRectX(const Dgrgdipapi::TGPRectF &ARectGP);
}	/* namespace Gdipclasses */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GDIPCLASSES)
using namespace Gdipclasses;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GdipclassesHPP
