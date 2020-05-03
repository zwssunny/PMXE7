// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DiagramUtils.pas' rev: 28.00 (Windows)

#ifndef DiagramutilsHPP
#define DiagramutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.Contnrs.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Diagramutils
{
//-- type declarations -------------------------------------------------------
typedef double number;

struct DECLSPEC_DRECORD TDot
{
public:
	double X;
	double Y;
};


struct DECLSPEC_DRECORD TSquare
{
	union
	{
		struct 
		{
			TDot TopLeft;
			TDot BottomRight;
		};
		struct 
		{
			double Left;
			double Top;
			double Right;
			double Bottom;
		};
		
	};
};


typedef System::DynamicArray<System::Types::TPoint> TPointArray;

typedef System::DynamicArray<TDot> TDotArray;

typedef TSquare TRectX;

typedef TDot TPointX;

typedef TDotArray TPointXArray;

enum DECLSPEC_DENUM TLineOrientation : unsigned char { loPoint, loHorizontal, loVertical };

enum DECLSPEC_DENUM TRotationType : unsigned char { rtCurRectCenter, rtRotationCenter };

enum DECLSPEC_DENUM TVertAlign : unsigned char { vaTop, vaBottom, vaCenter };

class DELPHICLASS TBlockDrawer;
class PASCALIMPLEMENTATION TBlockDrawer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSquare FRect;
	TSquare FOrRect;
	double FAngle;
	double FRadAngle;
	Vcl::Graphics::TCanvas* FCanvas;
	double FSinAngle;
	double FCosAngle;
	TRotationType FRotationType;
	TDot FRotationCenter;
	System::Contnrs::TObjectStack* FStack;
	void __fastcall SetAngle(const double Value);
	
public:
	__fastcall TBlockDrawer(void);
	__fastcall virtual ~TBlockDrawer(void);
	void __fastcall DrawRotRoundRect(double X1, double Y1, double X2, double Y2, double X3, double Y3);
	void __fastcall DrawRotRect(double X1, double Y1, double X2, double Y2);
	void __fastcall DrawRotPoly(TDotArray P)/* overload */;
	void __fastcall DrawRotPoly(TDot *P, const int P_High)/* overload */;
	void __fastcall DrawRotEllipse(int X1, int Y1, int X2, int Y2);
	void __fastcall AutoRotRect(double X1, double Y1, double X2, double Y2);
	void __fastcall AutoEllipse(double X1, double Y1, double X2, double Y2);
	void __fastcall AutoRoundRect(double X1, double Y1, double X2, double Y2, double X3, double Y3);
	void __fastcall AutoLineTo(double X, double Y);
	void __fastcall AutoMoveTo(double X, double Y);
	TDotArray __fastcall RotPoly(TDotArray Pts)/* overload */;
	TDot __fastcall UnrotX(double AX, double AY)/* overload */;
	TDot __fastcall UnrotX(const TDot &AP)/* overload */;
	TDot __fastcall RotX(double AX, double AY)/* overload */;
	TDot __fastcall RotX(const TDot &AP)/* overload */;
	System::Types::TPoint __fastcall Rot(const System::Types::TPoint &AP)/* overload */;
	System::Types::TPoint __fastcall Rot(double AX, double AY)/* overload */;
	TSquare __fastcall RotByCenter(const TSquare &R);
	TDotArray __fastcall PPPoints(TDotArray Pts);
	TDot __fastcall PP(const TDot &AP)/* overload */;
	TDot __fastcall PP(double AX, double AY)/* overload */;
	TDot __fastcall PPX(double AX, double AY)/* overload */;
	TDot __fastcall PPX(const TDot &AP)/* overload */;
	virtual int __fastcall PX(double AX);
	virtual int __fastcall PY(double AY);
	double __fastcall PXS(double AX);
	double __fastcall PYS(double AY);
	TDot __fastcall UnPP(const TDot &AP)/* overload */;
	TDot __fastcall UnPP(double Ax, double AY)/* overload */;
	TDot __fastcall UnPPX(double Ax, double AY)/* overload */;
	TDot __fastcall UnPPX(const TDot &AP)/* overload */;
	int __fastcall UnPx(double AX);
	int __fastcall UnPY(double AY);
	double __fastcall UnPXS(double AX);
	double __fastcall UnPYS(double AY);
	System::Types::TPoint __fastcall RP(double AX, double AY);
	int __fastcall RX(double AX);
	int __fastcall RY(double AY);
	System::Types::TPoint __fastcall LP(double AX, double AY);
	int __fastcall LX(double AX);
	int __fastcall LY(double AY);
	void __fastcall PushState(void);
	void __fastcall PopState(void);
	void __fastcall Assign(TBlockDrawer* ASource);
	void __fastcall CanvasPolygon(TPointArray APoints);
	void __fastcall CanvasPolyLine(TPointArray APoints);
	__property double Angle = {read=FAngle, write=SetAngle};
	__property TRotationType RotationType = {read=FRotationType, write=FRotationType, nodefault};
	__property TDot RotationCenter = {read=FRotationCenter, write=FRotationCenter};
	__property TSquare OriginalRect = {read=FOrRect, write=FOrRect};
	__property TSquare CurRect = {read=FRect, write=FRect};
	__property Vcl::Graphics::TCanvas* Canvas = {read=FCanvas, write=FCanvas};
};


class DELPHICLASS TSaveBlockDrawer;
class PASCALIMPLEMENTATION TSaveBlockDrawer : public TBlockDrawer
{
	typedef TBlockDrawer inherited;
	
public:
	/* TBlockDrawer.Create */ inline __fastcall TSaveBlockDrawer(void) : TBlockDrawer() { }
	/* TBlockDrawer.Destroy */ inline __fastcall virtual ~TSaveBlockDrawer(void) { }
	
};


typedef System::TMetaClass* TBlockDrawerClass;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TDot __fastcall CalcDistPoint(const TDot &P1, const TDot &P2, const TDot &MP, double Dist);
extern DELPHI_PACKAGE void __fastcall CalcPerpendicularPoints(TDot &P1, TDot &P2, const TDot &_From, const TDot &_To, const TDot &ASize);
extern DELPHI_PACKAGE TSquare __fastcall KeepRectRatio(const TSquare &NewRect, const TSquare &OldRect);
extern DELPHI_PACKAGE TSquare __fastcall Square(double ALeft, double ATop, double ARight, double ABottom)/* overload */;
extern DELPHI_PACKAGE TSquare __fastcall Square(const System::Types::TRect &ARect)/* overload */;
extern DELPHI_PACKAGE TSquare __fastcall RectX _DEPRECATED_ATTRIBUTE0 (double ALeft, double ATop, double ARight, double ABottom)/* overload */;
extern DELPHI_PACKAGE TSquare __fastcall RectX _DEPRECATED_ATTRIBUTE0 (const System::Types::TRect &ARect)/* overload */;
extern DELPHI_PACKAGE System::Types::TRect __fastcall ToRect(const TSquare &ASquare);
extern DELPHI_PACKAGE TSquare __fastcall MoveRectXByPoint(const TSquare &ARect, const System::Types::TPoint &ADelta);
extern DELPHI_PACKAGE System::Uitypes::TColor __fastcall RotateBitmap(Vcl::Graphics::TBitmap* ASrcBmp, Vcl::Graphics::TBitmap* ADestBmp, double AAngle);
extern DELPHI_PACKAGE void __fastcall DrawTranspBitmap(Vcl::Graphics::TCanvas* Dest, Vcl::Graphics::TBitmap* Bmp, int destX, int destY, System::Uitypes::TColor TransColor);
extern DELPHI_PACKAGE TDotArray __fastcall GetPolyEllipse(double Left, double Top, double Right, double Bottom, int StartAngle = 0x0, int EndAngle = 0x168, bool ClockWise = true);
extern DELPHI_PACKAGE TDotArray __fastcall GetPolyRoundRect(double X1, double Y1, double X2, double Y2, double X3, double Y3);
extern DELPHI_PACKAGE TSquare __fastcall RectEx(const TDot &P1, const TDot &P2)/* overload */;
extern DELPHI_PACKAGE TSquare __fastcall RectEx(double ALeft, double ATop, double ARight, double ABottom)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsNullRect(const System::Types::TRect &ARect)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsNullRect(const TSquare &ARect)/* overload */;
extern DELPHI_PACKAGE bool __fastcall RectsTouch(const TSquare &ACompRect, const TSquare &ARect);
extern DELPHI_PACKAGE System::Types::TRect __fastcall RotateRect(const System::Types::TRect &ARect);
extern DELPHI_PACKAGE bool __fastcall IsSameRect(const System::Types::TRect &ARect1, const System::Types::TRect &ARect2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsSameRect(const TSquare &ARect1, const TSquare &ARect2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AroundVertLine(const System::Types::TPoint &APoint, double X, double Y1, double Y2, int APointOff = 0x5);
extern DELPHI_PACKAGE bool __fastcall AroundHorzLine(const System::Types::TPoint &APoint, double Y, double X1, double X2, int APointOff = 0x5);
extern DELPHI_PACKAGE bool __fastcall AroundPoint(const System::Types::TPoint &APoint, const System::Types::TPoint &ATargetPoint, int APointOff = 0x5)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AroundPoint(const TDot &APoint, const TDot &ATargetPoint, int APointOff = 0x5)/* overload */;
extern DELPHI_PACKAGE TPointArray __fastcall PointArray(System::Types::TPoint *P, const int P_High);
extern DELPHI_PACKAGE TDotArray __fastcall DotArray(TDot *P, const int P_High);
extern DELPHI_PACKAGE TDotArray __fastcall PointXArray _DEPRECATED_ATTRIBUTE0 (TDot *P, const int P_High);
extern DELPHI_PACKAGE TPointArray __fastcall ConcatPoints(TPointArray P1, TPointArray P2);
extern DELPHI_PACKAGE TDotArray __fastcall ConcatPointsX(TDotArray P1, TDotArray P2);
extern DELPHI_PACKAGE TPointArray __fastcall RoundDotArray(TDotArray Src);
extern DELPHI_PACKAGE TDotArray __fastcall MakeDotArray(TDot *P, const int P_High);
extern DELPHI_PACKAGE TDotArray __fastcall ToDotArray(TPointArray Src);
extern DELPHI_PACKAGE void __fastcall ClipRectangleRegion(HDC DC, int X1, int Y1, int X2, int Y2);
extern DELPHI_PACKAGE void __fastcall CalcLineParameters(double PAX, double PAY, double PBX, double PBY, double &Slope, double &Intercept, TLineOrientation &LineOrientation);
extern DELPHI_PACKAGE bool __fastcall NearLine(const System::Types::TPoint &Target, double P1X, double P1Y, double P2X, double P2Y, int AOff = 0x5);
extern DELPHI_PACKAGE TDot __fastcall DummyPointX(void);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall DummyPoint(void);
extern DELPHI_PACKAGE bool __fastcall IsNullPoint(const System::Types::TPoint &APoint)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsNullPoint(const TDot &APoint)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsDummyPoint(const TDot &APoint);
extern DELPHI_PACKAGE TSquare __fastcall MoveRectByPoint(const TSquare &ARect, const TDot &ADelta);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall PointRelativeToRect(const System::Types::TRect &ARect, const System::Types::TPoint &APoint);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall RestrictPointToRect(const System::Types::TRect &ARect, const System::Types::TPoint &APoint, int AMargin = 0x1);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall RectBottomLeft(const System::Types::TRect &ARect);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall RectTopRight(const System::Types::TRect &ARect);
extern DELPHI_PACKAGE bool __fastcall PtInRectEx(const TSquare &ARect, const TDot &P, int AOff = 0x5);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall SubPoint(const System::Types::TPoint &P1, const System::Types::TPoint &P2);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall AddPoint(const System::Types::TPoint &P1, const System::Types::TPoint &P2);
extern DELPHI_PACKAGE TDot __fastcall SubPointX(const TDot &P1, const TDot &P2);
extern DELPHI_PACKAGE TDot __fastcall AddPointX(const TDot &P1, const TDot &P2);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall MulPoint(const System::Types::TPoint &P1, double AValue)/* overload */;
extern DELPHI_PACKAGE TDot __fastcall MulPoint(const TDot &P1, double AValue)/* overload */;
extern DELPHI_PACKAGE System::Types::TPoint __fastcall RotatePoint(const System::Types::TPoint &P, double Angle);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall RectCenter(const System::Types::TRect &R);
extern DELPHI_PACKAGE System::Types::TPoint __fastcall RoundPoint(const TDot &APoint);
extern DELPHI_PACKAGE TDot __fastcall Dot(double X, double Y)/* overload */;
extern DELPHI_PACKAGE TDot __fastcall Dot(const System::Types::TPoint &P)/* overload */;
extern DELPHI_PACKAGE TDot __fastcall PointX _DEPRECATED_ATTRIBUTE0 (double X, double Y)/* overload */;
extern DELPHI_PACKAGE TDot __fastcall PointX _DEPRECATED_ATTRIBUTE0 (const System::Types::TPoint &P)/* overload */;
extern DELPHI_PACKAGE System::Types::TRect __fastcall MoveRect(const System::Types::TRect &R, int DX, int DY)/* overload */;
extern DELPHI_PACKAGE TSquare __fastcall MoveRect(const TSquare &R, double DX, double DY)/* overload */;
extern DELPHI_PACKAGE double __fastcall DistanceFromLine(const TDot &L1, const TDot &L2, const TDot &P);
extern DELPHI_PACKAGE double __fastcall PointDistance(const TDot &P1, const TDot &P2)/* overload */;
extern DELPHI_PACKAGE double __fastcall PointDistance(double p1x, double p1y, double p2x, double p2y)/* overload */;
extern DELPHI_PACKAGE TDot __fastcall MeanPoint(const TDot &P1, const TDot &P2);
extern DELPHI_PACKAGE bool __fastcall ArePointsEqual(const System::Types::TPoint &P1, const System::Types::TPoint &P2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall ArePointsEqual(const TDot &P1, const TDot &P2)/* overload */;
extern DELPHI_PACKAGE System::Types::TPoint __fastcall AbsPoint(const System::Types::TPoint &P);
extern DELPHI_PACKAGE double __fastcall Diode(double X);
extern DELPHI_PACKAGE bool __fastcall LineIntersection(const System::Types::TPoint &A1, const System::Types::TPoint &A2, const System::Types::TPoint &B1, const System::Types::TPoint &B2, System::Types::TPoint &P)/* overload */;
extern DELPHI_PACKAGE bool __fastcall LineIntersection(const TDot &A1, const TDot &A2, const TDot &B1, const TDot &B2, TDot &P)/* overload */;
extern DELPHI_PACKAGE bool __fastcall LineIntersectionSeg(const System::Types::TPoint &A1, const System::Types::TPoint &A2, const System::Types::TPoint &B1, const System::Types::TPoint &B2, System::Types::TPoint &P)/* overload */;
extern DELPHI_PACKAGE bool __fastcall LineIntersectionSeg(const TDot &A1, const TDot &A2, const TDot &B1, const TDot &B2, TDot &P)/* overload */;
extern DELPHI_PACKAGE void __fastcall LineEqIntersection(double a1, double b1, double c1, double a2, double b2, double c2, double &x, double &y);
extern DELPHI_PACKAGE TDotArray __fastcall CircumArc(double pt0x, double pt0y, double pt1x, double pt1y, double pt2x, double pt2y);
extern DELPHI_PACKAGE bool __fastcall Colinear(double x1, double y1, double x2, double y2, double x3, double y3);
extern DELPHI_PACKAGE void __fastcall Mediatriz(double x1, double y1, double x2, double y2, double &a, double &b, double &c);
extern DELPHI_PACKAGE double __fastcall VectorAngle(double x, double y, double xc, double yc);
extern DELPHI_PACKAGE void __fastcall MakeVector(double X, double Y, double D, double A, double &NX, double &NY);
extern DELPHI_PACKAGE TDot __fastcall RotatePointByLines(const TDot &P, const TDot &LA1, const TDot &LA2, const TDot &LB1, const TDot &LB2);
extern DELPHI_PACKAGE TDotArray __fastcall ParabolicArc(double pt0x, double pt0y, double pt1x, double pt1y, double pt2x, double pt2y);
extern DELPHI_PACKAGE void __fastcall RotateVector(double &x1, double &y1, double x0, double y0, double ang);
extern DELPHI_PACKAGE void __fastcall LinearSys(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double &x, double &y, double &z);
extern DELPHI_PACKAGE TDotArray __fastcall Bezier(double pt0x, double pt0y, double pp0x, double pp0y, double pp1x, double pp1y, double pt1x, double pt1y, double k);
}	/* namespace Diagramutils */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DIAGRAMUTILS)
using namespace Diagramutils;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DiagramutilsHPP
