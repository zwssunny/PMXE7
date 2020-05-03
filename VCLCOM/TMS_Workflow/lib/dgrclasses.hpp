// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrClasses.pas' rev: 28.00 (Windows)

#ifndef DgrclassesHPP
#define DgrclassesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.UITypes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgrclasses
{
//-- type declarations -------------------------------------------------------
typedef System::TMetaClass* TDgrBlockDrawerClass;

typedef System::TMetaClass* TDgrPaintEngineClass;

enum DECLSPEC_DENUM TDgrBrushMode : unsigned char { bmSolid, bmClear, bmHatch, bmGradient, bmTexture };

enum DECLSPEC_DENUM TDgrGradientMode : unsigned char { gmTopBottom, gmBottomTop, gmLeftRight, gmRightLeft, gmLeftTop, gmRightTop, gmLeftBottom, gmRightBottom, gmInOut, gmOutIn, gmHorzInOut, gmHorzOutIn, gmVertInOut, gmVertOutIn };

enum DECLSPEC_DENUM TDgrGraphicLib : unsigned char { dglGDI, dglGDIPlus, dglDirect2D };

enum DECLSPEC_DENUM TDgrPageUnit : unsigned char { dpuWorld, dpuDisplay, dpuPixel, dpuPoint, dpuInch, dpuDocument, dpuMillimeter };

enum DECLSPEC_DENUM TDgrSmoothMode : unsigned char { smAntiAlias, smInactive, smHighSpeed, smHighQuality };

enum DECLSPEC_DENUM TDgrTextRenderingMode : unsigned char { tmAntiAlias, tmAntiAliasHint, tmDefault, tmNormal, tmNormalHint, tmClearType };

class DELPHICLASS TDgrGraphic;
class PASCALIMPLEMENTATION TDgrGraphic : public Vcl::Graphics::TGraphic
{
	typedef Vcl::Graphics::TGraphic inherited;
	
private:
	System::Classes::TMemoryStream* FDatastream;
	bool FIsEmpty;
	int FWidth;
	int FHeight;
	
protected:
	virtual void __fastcall DoDraw(Vcl::Graphics::TCanvas* ACanvas, const Diagramutils::TSquare &Rect);
	virtual bool __fastcall DoGetImageSizes(void) = 0 ;
	virtual bool __fastcall GetEmpty(void);
	void __fastcall SetEmpty(const bool Value);
	virtual int __fastcall GetHeight(void);
	virtual int __fastcall GetWidth(void);
	virtual void __fastcall SetHeight(int Value);
	virtual void __fastcall SetWidth(int Value);
	virtual void __fastcall ReadData(System::Classes::TStream* Stream);
	virtual void __fastcall WriteData(System::Classes::TStream* Stream);
	virtual void __fastcall Changed(System::TObject* Sender);
	__property System::Classes::TMemoryStream* DataStream = {read=FDatastream};
	
public:
	__fastcall virtual TDgrGraphic(void);
	__fastcall virtual ~TDgrGraphic(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Draw(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &Rect);
	virtual void __fastcall LoadFromFile(const System::UnicodeString FileName);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream);
	virtual void __fastcall LoadFromClipboardFormat(System::Word AFormat, NativeUInt AData, HPALETTE APalette);
	virtual void __fastcall SaveToClipboardFormat(System::Word &AFormat, NativeUInt &AData, HPALETTE &APalette);
	virtual bool __fastcall GetImageSizes(void);
};


class DELPHICLASS TDgrPicture;
class PASCALIMPLEMENTATION TDgrPicture : public Vcl::Graphics::TPicture
{
	typedef Vcl::Graphics::TPicture inherited;
	
private:
	System::Classes::TMemoryStream* FDatastream;
	int FTransparency;
	void __fastcall SetTransparency(const int Value);
	
protected:
	DYNAMIC void __fastcall Changed(System::TObject* Sender);
	__property System::Classes::TMemoryStream* DataStream = {read=FDatastream};
	
public:
	__fastcall virtual TDgrPicture(void);
	__fastcall virtual ~TDgrPicture(void);
	
__published:
	__property int Transparency = {read=FTransparency, write=SetTransparency, nodefault};
};


class DELPHICLASS TDgrGraphicsObject;
class PASCALIMPLEMENTATION TDgrGraphicsObject : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Classes::TNotifyEvent FOnChange;
	
protected:
	virtual void __fastcall Change(void);
	
public:
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDgrGraphicsObject(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TDgrGraphicsObject(void) : System::Classes::TPersistent() { }
	
};


class DELPHICLASS TDgrBrush;
class PASCALIMPLEMENTATION TDgrBrush : public TDgrGraphicsObject
{
	typedef TDgrGraphicsObject inherited;
	
private:
	System::Uitypes::TColor FColor;
	int FTransparency;
	TDgrBrushMode FBrushMode;
	System::Uitypes::TColor FColor2;
	TDgrGradientMode FGradientMode;
	TDgrPicture* FTexture;
	int FTransp1;
	int FTransp2;
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetTransparency(const int Value);
	void __fastcall SetBrushMode(const TDgrBrushMode Value);
	void __fastcall SetColor2(const System::Uitypes::TColor Value);
	void __fastcall SetGradientMode(const TDgrGradientMode Value);
	void __fastcall SetTexture(TDgrPicture* const Value);
	void __fastcall ItemChange(System::TObject* Sender);
	
protected:
	System::Byte __fastcall GetAlpha1(void);
	System::Byte __fastcall GetAlpha2(void);
	virtual void __fastcall Change(void);
	virtual TDgrPicture* __fastcall CreatePicture(void) = 0 ;
	virtual void __fastcall DoUpdateBrushPosition(const Diagramutils::TSquare &ARect, double AAngle, const Diagramutils::TDot &ARotCenter) = 0 ;
	
public:
	__fastcall virtual TDgrBrush(void);
	__fastcall virtual ~TDgrBrush(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall UpdateBrushPosition(const Diagramutils::TSquare &ARect, double AAngle, const Diagramutils::TDot &ARotCenter);
	
__published:
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, default=16777215};
	__property System::Uitypes::TColor Color2 = {read=FColor2, write=SetColor2, nodefault};
	__property int Transparency = {read=FTransparency, write=SetTransparency, default=0};
	__property TDgrBrushMode BrushMode = {read=FBrushMode, write=SetBrushMode, nodefault};
	__property TDgrGradientMode GradientMode = {read=FGradientMode, write=SetGradientMode, nodefault};
	__property TDgrPicture* Texture = {read=FTexture, write=SetTexture};
};


class DELPHICLASS TDgrPen;
class PASCALIMPLEMENTATION TDgrPen : public TDgrGraphicsObject
{
	typedef TDgrGraphicsObject inherited;
	
private:
	double FWidth;
	System::Uitypes::TColor FColor;
	int FTransparency;
	void __fastcall SetColor(const System::Uitypes::TColor Value);
	void __fastcall SetWidth(const double Value);
	void __fastcall SetTransparency(const int Value);
	
protected:
	virtual void __fastcall Change(void);
	System::Byte __fastcall GetAlpha(void);
	
public:
	__fastcall virtual TDgrPen(void);
	__fastcall virtual ~TDgrPen(void);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, default=0};
	__property int Transparency = {read=FTransparency, write=SetTransparency, nodefault};
	__property double Width = {read=FWidth, write=SetWidth};
};


class DELPHICLASS TDgrCanvas;
class DELPHICLASS TDgrGraphicsPath;
class DELPHICLASS TDgrImage;
class DELPHICLASS TDgrPaintEngine;
class DELPHICLASS TDgrRegion;
class PASCALIMPLEMENTATION TDgrCanvas : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	Vcl::Graphics::TCanvasState State;
	Diagramutils::TSquare FDestRect;
	Diagramutils::TSquare FSourceRect;
	bool FTranslateRects;
	bool FValidRects;
	double FAngle;
	Diagramutils::TDot FRotCenter;
	double FScaleX;
	double FScaleY;
	void __fastcall SetPen(TDgrPen* const Value);
	void __fastcall SetBrush(TDgrBrush* const Value);
	void __fastcall SetDestRect(const Diagramutils::TSquare &Value);
	void __fastcall SetSourceRect(const Diagramutils::TSquare &Value);
	void __fastcall UpdateFactors(void);
	void __fastcall SetRotCenter(const Diagramutils::TDot &Value);
	void __fastcall SetAngle(const double Value);
	
protected:
	virtual void __fastcall Changed(void);
	virtual void __fastcall Changing(void);
	virtual void __fastcall DoDrawEllipse(double x, double y, double Width, double height) = 0 ;
	virtual void __fastcall DoDrawLine(double X1, double Y1, double X2, double Y2) = 0 ;
	virtual void __fastcall DoDrawPath(TDgrGraphicsPath* APath) = 0 ;
	virtual void __fastcall DoDrawRectangle(double x, double y, double Width, double height) = 0 ;
	virtual void __fastcall DoFillPath(TDgrGraphicsPath* APath) = 0 ;
	virtual void __fastcall DoPolygon(Diagramutils::TDotArray APoints) = 0 ;
	virtual void __fastcall DoStretchDraw(const Diagramutils::TSquare &Rect, Vcl::Graphics::TGraphic* Graphic, int ATransparency = 0x0, bool ABitmapTransparent = false) = 0 /* overload */;
	virtual void __fastcall DoStretchDraw(const Diagramutils::TSquare &Rect, TDgrImage* ADgrImage, int ATransparency = 0x0, bool ABitmapTransparent = false) = 0 /* overload */;
	virtual void __fastcall DoUpdateFactors(const Diagramutils::TSquare &ASourceRect, const Diagramutils::TSquare &ADestRect, double AScaleX, double AScaleY) = 0 ;
	virtual TDgrBrush* __fastcall GetBrush(void) = 0 ;
	virtual HDC __fastcall GetHandle(void);
	virtual TDgrPen* __fastcall GetPen(void) = 0 ;
	bool __fastcall MustTranslateRects(void);
	double __fastcall PX(double x);
	double __fastcall PY(double y);
	Diagramutils::TDot __fastcall PP(const Diagramutils::TDot &D)/* overload */;
	Diagramutils::TSquare __fastcall PP(const Diagramutils::TSquare &S)/* overload */;
	double __fastcall SX(double x);
	double __fastcall SY(double y);
	virtual void __fastcall SetHandle(const HDC Value);
	void __fastcall RequiredState(Vcl::Graphics::TCanvasState ReqState);
	__property Diagramutils::TSquare SourceRect = {read=FSourceRect, write=SetSourceRect};
	__property Diagramutils::TSquare DestRect = {read=FDestRect, write=SetDestRect};
	__property Diagramutils::TDot RotationCenter = {read=FRotCenter, write=SetRotCenter};
	__property double Angle = {read=FAngle, write=SetAngle};
	
public:
	__fastcall virtual TDgrCanvas(HDC AHandle);
	__fastcall virtual ~TDgrCanvas(void);
	virtual TDgrBrush* __fastcall CreateBrush(void) = 0 ;
	virtual TDgrGraphic* __fastcall CreateGraphic(void) = 0 ;
	virtual TDgrPaintEngine* __fastcall CreatePaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect) = 0 ;
	virtual TDgrGraphicsPath* __fastcall CreatePath(void) = 0 ;
	virtual TDgrPen* __fastcall CreatePen(void) = 0 ;
	virtual void __fastcall ClipRegion(TDgrRegion* ARegion);
	void __fastcall Ellipse(double X1, double Y1, double X2, double Y2);
	void __fastcall Polygon(const Diagramutils::TDotArray Points)/* overload */;
	void __fastcall Rectangle(double X1, double Y1, double X2, double Y2)/* overload */;
	void __fastcall RoundRect(double X1, double Y1, double X2, double Y2, double X3, double Y3);
	void __fastcall AddRoundRectPath(TDgrGraphicsPath* APath, double X1, double Y1, double X2, double Y2, double X3, double Y3);
	void __fastcall Path(TDgrGraphicsPath* APath);
	void __fastcall DrawPath(TDgrGraphicsPath* APath);
	void __fastcall DrawLine(double X1, double Y1, double X2, double Y2);
	void __fastcall StretchDraw(const Diagramutils::TSquare &ARect, Vcl::Graphics::TGraphic* Graphic, int ATransparency = 0x0, bool ABitmapTransparent = false)/* overload */;
	void __fastcall StretchDraw(const Diagramutils::TSquare &ARect, TDgrImage* ADgrImage, int ATransparency = 0x0, bool ABitmapTransparent = false)/* overload */;
	virtual void __fastcall RestoreDrawingState(void) = 0 ;
	virtual void __fastcall SaveDrawingState(void) = 0 ;
	virtual Diagramutils::TSquare __fastcall StringBounds(System::UnicodeString AStr, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft) = 0 ;
	virtual void __fastcall DrawString(System::UnicodeString AStr, Vcl::Graphics::TFont* AFont, const Diagramutils::TSquare &ARect, System::Classes::TAlignment AHAlign, Diagramutils::TVertAlign AVAlign, bool AWrap, bool ARightToLeft, int ATransparency) = 0 ;
	virtual int __fastcall TranslateTransform(double AX, double AY);
	virtual int __fastcall ScaleTransform(double AX, double AY);
	virtual int __fastcall ResetClip(void);
	virtual int __fastcall ResetTransform(void);
	virtual int __fastcall RotateTransform(double AAngle)/* overload */;
	virtual int __fastcall RotateTransform(double AAngle, const Diagramutils::TDot &ARotCenter)/* overload */;
	virtual int __fastcall SetClip(const Diagramutils::TSquare &ARect)/* overload */;
	virtual int __fastcall SetClip(HRGN ARegion)/* overload */;
	__property HDC Handle = {read=GetHandle, write=SetHandle, nodefault};
	
__published:
	__property TDgrPen* Pen = {read=GetPen, write=SetPen};
	__property TDgrBrush* Brush = {read=GetBrush, write=SetBrush};
};


class DELPHICLASS TDgrBlockDrawer;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrBlockDrawer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall DoRotatePath(TDgrGraphicsPath* APath) = 0 ;
	virtual TDgrCanvas* __fastcall GetCanvas(void) = 0 ;
	virtual void __fastcall SetPaintEngine(TDgrPaintEngine* const Value) = 0 ;
	Diagramutils::TSquare __fastcall GetDestRect(void);
	Diagramutils::TSquare __fastcall GetSourceRect(void);
	void __fastcall SetDestRect(const Diagramutils::TSquare &Value);
	void __fastcall SetSourceRect(const Diagramutils::TSquare &Value);
	Diagramutils::TDot __fastcall GetRotCenter(void);
	void __fastcall SetRotCenter(const Diagramutils::TDot &Value);
	double __fastcall GetAngle(void);
	void __fastcall SetAngle(const double Value);
	
public:
	__fastcall virtual TDgrBlockDrawer(void);
	__fastcall virtual ~TDgrBlockDrawer(void);
	TDgrBrush* __fastcall CreateBrush(void);
	TDgrGraphic* __fastcall CreateGraphic(void);
	TDgrPaintEngine* __fastcall CreatePaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect);
	TDgrGraphicsPath* __fastcall CreatePath(void);
	TDgrPen* __fastcall CreatePen(void);
	void __fastcall SetDeviceContext(HDC AHandle);
	void __fastcall RotatePath(TDgrGraphicsPath* APath);
	virtual void __fastcall TranslateRectsPath(TDgrGraphicsPath* APath);
	void __fastcall TransformPath(TDgrGraphicsPath* APath);
	__property double Angle = {read=GetAngle, write=SetAngle};
	__property TDgrCanvas* Canvas = {read=GetCanvas};
	__property Diagramutils::TSquare DestRect = {read=GetDestRect, write=SetDestRect};
	__property Diagramutils::TDot RotationCenter = {read=GetRotCenter, write=SetRotCenter};
	__property Diagramutils::TSquare SourceRect = {read=GetSourceRect, write=SetSourceRect};
	__property TDgrPaintEngine* PaintEngine = {write=SetPaintEngine};
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrGraphicsPath : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual int __fastcall AddArc(double x, double y, double Width, double height, double startAngle, double sweepAngle) = 0 ;
	virtual int __fastcall AddBezier(double X1, double Y1, double X2, double Y2, double X3, double Y3, double x4, double y4) = 0 ;
	virtual int __fastcall AddEllipse(double x, double y, double Width, double height) = 0 ;
	virtual int __fastcall AddLine(double X1, double Y1, double X2, double Y2) = 0 ;
	virtual int __fastcall AddLines(Diagramutils::TDotArray Points) = 0 ;
	virtual int __fastcall AddPolygon(Diagramutils::TDotArray Points) = 0 ;
	virtual int __fastcall AddRectangle(const Diagramutils::TSquare &Rect) = 0 ;
	virtual int __fastcall AddRoundRect(double X1, double Y1, double X2, double Y2, double X3, double Y3) = 0 ;
	virtual int __fastcall CloseFigure(bool AClosePath = true) = 0 ;
	virtual TDgrRegion* __fastcall CreateRegion(void) = 0 ;
	virtual int __fastcall GetPointCount(void) = 0 ;
	virtual bool __fastcall IsVisible(int x, int y) = 0 ;
	virtual int __fastcall Reset(void) = 0 ;
	virtual int __fastcall SetFillMode(Vcl::Graphics::TFillMode fillmode) = 0 ;
	virtual int __fastcall StartFigure(void) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDgrGraphicsPath(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDgrGraphicsPath(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrImage : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDgrImage(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDgrImage(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrPaintEngine : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDgrSmoothMode FSmoothMode;
	TDgrTextRenderingMode FTextRenderingMode;
	TDgrPageUnit FPageUnit;
	
protected:
	virtual void __fastcall SetPageUnit(const TDgrPageUnit Value);
	virtual void __fastcall SetSmoothMode(const TDgrSmoothMode Value);
	virtual void __fastcall SetTextRenderingMode(const TDgrTextRenderingMode Value);
	
public:
	__fastcall virtual TDgrPaintEngine(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect) = 0 ;
	virtual void __fastcall BeginDraw(void);
	virtual void __fastcall EndDraw(void);
	virtual void __fastcall FillRect(const System::Types::TRect &ARect, System::Uitypes::TColor AColor) = 0 ;
	virtual int __fastcall ResetTransform(void) = 0 ;
	virtual int __fastcall RotateTransform(double AAngle) = 0 ;
	virtual int __fastcall ScaleTransform(double AX, double AY) = 0 ;
	virtual int __fastcall TranslateTransform(double AX, double AY) = 0 ;
	__property TDgrPageUnit PageUnit = {read=FPageUnit, write=SetPageUnit, nodefault};
	__property TDgrSmoothMode SmoothMode = {read=FSmoothMode, write=SetSmoothMode, nodefault};
	__property TDgrTextRenderingMode TextRenderingMode = {read=FTextRenderingMode, write=SetTextRenderingMode, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDgrPaintEngine(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TDgrRegion : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TDgrRegion(TDgrGraphicsPath* APath) = 0 ;
	virtual HRGN __fastcall GetHRGN(TDgrCanvas* ACanvas);
	virtual bool __fastcall IsVisible(const Diagramutils::TSquare &ARect);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDgrRegion(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TDgrGraphicLib __fastcall DefaultGraphicLib(void);
}	/* namespace Dgrclasses */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGRCLASSES)
using namespace Dgrclasses;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgrclassesHPP
