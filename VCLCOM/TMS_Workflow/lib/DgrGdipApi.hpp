// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrGdipApi.pas' rev: 28.00 (Windows)

#ifndef DgrgdipapiHPP
#define DgrgdipapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.ActiveX.hpp>	// Pascal unit
#include <System.Math.hpp>	// Pascal unit
#include <System.Types.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgrgdipapi
{
//-- type declarations -------------------------------------------------------
typedef short INT16;

typedef System::Word UINT16;

typedef UINT16 *PUINT16;

typedef unsigned UINT32;

typedef System::DynamicArray<float> TSingleDynArray;

class DELPHICLASS TGdiplusBase;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGdiplusBase : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod virtual System::TObject* __fastcall NewInstance();
	virtual void __fastcall FreeInstance(void);
public:
	/* TObject.Create */ inline __fastcall TGdiplusBase(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGdiplusBase(void) { }
	
};

#pragma pack(pop)

typedef unsigned GraphicsState;

typedef unsigned GraphicsContainer;

enum DECLSPEC_DENUM FillMode : unsigned int { FillModeAlternate, FillModeWinding };

typedef FillMode TFillMode;

typedef int QualityMode;

enum DECLSPEC_DENUM CompositingMode : unsigned int { CompositingModeSourceOver, CompositingModeSourceCopy };

typedef CompositingMode TCompositingMode;

typedef int CompositingQuality;

typedef int TCompositingQuality;

enum DECLSPEC_DENUM Unit_ : unsigned int { UnitWorld, UnitDisplay, UnitPixel, UnitPoint, UnitInch, UnitDocument, UnitMillimeter };

typedef Unit_ TUnit;

typedef int MetafileFrameUnit;

typedef int TMetafileFrameUnit;

enum DECLSPEC_DENUM CoordinateSpace : unsigned int { CoordinateSpaceWorld, CoordinateSpacePage, CoordinateSpaceDevice };

typedef CoordinateSpace TCoordinateSpace;

enum DECLSPEC_DENUM WrapMode : unsigned int { WrapModeTile, WrapModeTileFlipX, WrapModeTileFlipY, WrapModeTileFlipXY, WrapModeClamp };

typedef WrapMode TWrapMode;

enum DECLSPEC_DENUM HatchStyle : unsigned int { HatchStyleHorizontal, HatchStyleVertical, HatchStyleForwardDiagonal, HatchStyleBackwardDiagonal, HatchStyleCross, HatchStyleDiagonalCross, HatchStyle05Percent, HatchStyle10Percent, HatchStyle20Percent, HatchStyle25Percent, HatchStyle30Percent, HatchStyle40Percent, HatchStyle50Percent, HatchStyle60Percent, HatchStyle70Percent, HatchStyle75Percent, HatchStyle80Percent, HatchStyle90Percent, HatchStyleLightDownwardDiagonal, HatchStyleLightUpwardDiagonal, HatchStyleDarkDownwardDiagonal, HatchStyleDarkUpwardDiagonal, HatchStyleWideDownwardDiagonal, HatchStyleWideUpwardDiagonal, HatchStyleLightVertical, HatchStyleLightHorizontal, HatchStyleNarrowVertical, HatchStyleNarrowHorizontal, HatchStyleDarkVertical, 
	HatchStyleDarkHorizontal, HatchStyleDashedDownwardDiagonal, HatchStyleDashedUpwardDiagonal, HatchStyleDashedHorizontal, HatchStyleDashedVertical, HatchStyleSmallConfetti, HatchStyleLargeConfetti, HatchStyleZigZag, HatchStyleWave, HatchStyleDiagonalBrick, HatchStyleHorizontalBrick, HatchStyleWeave, HatchStylePlaid, HatchStyleDivot, HatchStyleDottedGrid, HatchStyleDottedDiamond, HatchStyleShingle, HatchStyleTrellis, HatchStyleSphere, HatchStyleSmallGrid, HatchStyleSmallCheckerBoard, HatchStyleLargeCheckerBoard, HatchStyleOutlinedDiamond, HatchStyleSolidDiamond, HatchStyleTotal };

typedef HatchStyle THatchStyle;

enum DECLSPEC_DENUM DashStyle : unsigned int { DashStyleSolid, DashStyleDash, DashStyleDot, DashStyleDashDot, DashStyleDashDotDot, DashStyleCustom };

typedef DashStyle TDashStyle;

typedef int DashCap;

typedef int TDashCap;

typedef int LineCap;

typedef int TLineCap;

enum DECLSPEC_DENUM CustomLineCapType : unsigned int { CustomLineCapTypeDefault, CustomLineCapTypeAdjustableArrow };

typedef CustomLineCapType TCustomLineCapType;

enum DECLSPEC_DENUM LineJoin : unsigned int { LineJoinMiter, LineJoinBevel, LineJoinRound, LineJoinMiterClipped };

typedef LineJoin TLineJoin;

typedef System::Byte PathPointType;

typedef System::Byte TPathPointType;

enum DECLSPEC_DENUM WarpMode : unsigned int { WarpModePerspective, WarpModeBilinear };

typedef WarpMode TWarpMode;

enum DECLSPEC_DENUM LinearGradientMode : unsigned int { LinearGradientModeHorizontal, LinearGradientModeVertical, LinearGradientModeForwardDiagonal, LinearGradientModeBackwardDiagonal };

typedef LinearGradientMode TLinearGradientMode;

enum DECLSPEC_DENUM CombineMode : unsigned int { CombineModeReplace, CombineModeIntersect, CombineModeUnion, CombineModeXor, CombineModeExclude, CombineModeComplement };

typedef CombineMode TCombineMode;

enum DECLSPEC_DENUM ImageType : unsigned int { ImageTypeUnknown, ImageTypeBitmap, ImageTypeMetafile };

typedef ImageType TImageType;

typedef int InterpolationMode;

typedef int TInterpolationMode;

enum DECLSPEC_DENUM PenAlignment : unsigned int { PenAlignmentCenter, PenAlignmentInset };

typedef PenAlignment TPenAlignment;

enum DECLSPEC_DENUM BrushType : unsigned int { BrushTypeSolidColor, BrushTypeHatchFill, BrushTypeTextureFill, BrushTypePathGradient, BrushTypeLinearGradient };

typedef BrushType TBrushType;

typedef int PenType;

typedef int TPenType;

enum DECLSPEC_DENUM MatrixOrder : unsigned int { MatrixOrderPrepend, MatrixOrderAppend };

typedef MatrixOrder TMatrixOrder;

enum DECLSPEC_DENUM GenericFontFamily : unsigned int { GenericFontFamilySerif, GenericFontFamilySansSerif, GenericFontFamilyMonospace };

typedef GenericFontFamily TGenericFontFamily;

typedef int FontStyle;

typedef int TFontStyle;

typedef int SmoothingMode;

typedef int TSmoothingMode;

typedef int PixelOffsetMode;

typedef int TPixelOffsetMode;

enum DECLSPEC_DENUM TextRenderingHint : unsigned int { TextRenderingHintSystemDefault, TextRenderingHintSingleBitPerPixelGridFit, TextRenderingHintSingleBitPerPixel, TextRenderingHintAntiAliasGridFit, TextRenderingHintAntiAlias, TextRenderingHintClearTypeGridFit };

typedef TextRenderingHint TTextRenderingHint;

enum DECLSPEC_DENUM MetafileType : unsigned int { MetafileTypeInvalid, MetafileTypeWmf, MetafileTypeWmfPlaceable, MetafileTypeEmf, MetafileTypeEmfPlusOnly, MetafileTypeEmfPlusDual };

typedef MetafileType TMetafileType;

typedef int EmfType;

typedef int TEmfType;

enum DECLSPEC_DENUM ObjectType : unsigned int { ObjectTypeInvalid, ObjectTypeBrush, ObjectTypePen, ObjectTypePath, ObjectTypeRegion, ObjectTypeImage, ObjectTypeFont, ObjectTypeStringFormat, ObjectTypeImageAttributes, ObjectTypeCustomLineCap };

typedef ObjectType TObjectType;

typedef int EmfPlusRecordType;

typedef int TEmfPlusRecordType;

typedef int StringFormatFlags;

typedef int TStringFormatFlags;

enum DECLSPEC_DENUM StringTrimming : unsigned int { StringTrimmingNone, StringTrimmingCharacter, StringTrimmingWord, StringTrimmingEllipsisCharacter, StringTrimmingEllipsisWord, StringTrimmingEllipsisPath };

typedef StringTrimming TStringTrimming;

enum DECLSPEC_DENUM StringDigitSubstitute : unsigned int { StringDigitSubstituteUser, StringDigitSubstituteNone, StringDigitSubstituteNational, StringDigitSubstituteTraditional };

typedef StringDigitSubstitute TStringDigitSubstitute;

typedef StringDigitSubstitute *PStringDigitSubstitute;

enum DECLSPEC_DENUM HotkeyPrefix : unsigned int { HotkeyPrefixNone, HotkeyPrefixShow, HotkeyPrefixHide };

typedef HotkeyPrefix THotkeyPrefix;

enum DECLSPEC_DENUM StringAlignment : unsigned int { StringAlignmentNear, StringAlignmentCenter, StringAlignmentFar };

typedef StringAlignment TStringAlignment;

typedef int DriverStringOptions;

typedef int TDriverStringOptions;

enum DECLSPEC_DENUM FlushIntention : unsigned int { FlushIntentionFlush, FlushIntentionSync };

typedef FlushIntention TFlushIntention;

typedef int EncoderParameterValueType;

typedef int TEncoderParameterValueType;

enum DECLSPEC_DENUM EncoderValue : unsigned int { EncoderValueColorTypeCMYK, EncoderValueColorTypeYCCK, EncoderValueCompressionLZW, EncoderValueCompressionCCITT3, EncoderValueCompressionCCITT4, EncoderValueCompressionRle, EncoderValueCompressionNone, EncoderValueScanMethodInterlaced, EncoderValueScanMethodNonInterlaced, EncoderValueVersionGif87, EncoderValueVersionGif89, EncoderValueRenderProgressive, EncoderValueRenderNonProgressive, EncoderValueTransformRotate90, EncoderValueTransformRotate180, EncoderValueTransformRotate270, EncoderValueTransformFlipHorizontal, EncoderValueTransformFlipVertical, EncoderValueMultiFrame, EncoderValueLastFrame, EncoderValueFlush, EncoderValueFrameDimensionTime, EncoderValueFrameDimensionResolution, 
	EncoderValueFrameDimensionPage };

typedef EncoderValue TEncoderValue;

typedef int EmfToWmfBitsFlags;

typedef int TEmfToWmfBitsFlags;

typedef BOOL __stdcall (*ImageAbort)(void);

typedef ImageAbort DrawImageAbort;

typedef ImageAbort GetThumbnailImageAbort;

typedef BOOL __stdcall (*EnumerateMetafileProc)(int recordType, unsigned flags, unsigned dataSize, System::PByte data, void * callbackData);

enum DECLSPEC_DENUM Status : unsigned int { Ok, GenericError, InvalidParameter, OutOfMemory, ObjectBusy, InsufficientBuffer, NotImplemented, Win32Error, WrongState, Aborted, FileNotFound, ValueOverflow, AccessDenied, UnknownImageFormat, FontFamilyNotFound, FontStyleNotFound, NotTrueTypeFont, UnsupportedGdiplusVersion, GdiplusNotInitialized, PropertyNotFound, PropertyNotSupported };

typedef Status TStatus;

struct TGPSizeF;
typedef TGPSizeF *PGPSizeF;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TGPSizeF
{
public:
	float Width;
	float Height;
};
#pragma pack(pop)


struct TGPSize;
typedef TGPSize *PGPSize;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TGPSize
{
public:
	int Width;
	int Height;
};
#pragma pack(pop)


struct TGPPointF;
typedef TGPPointF *PGPPointF;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TGPPointF
{
public:
	float X;
	float Y;
};
#pragma pack(pop)


typedef System::DynamicArray<TGPPointF> TPointFDynArray;

struct TGPPoint;
typedef TGPPoint *PGPPoint;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TGPPoint
{
public:
	int X;
	int Y;
};
#pragma pack(pop)


typedef System::DynamicArray<TGPPoint> TPointDynArray;

struct TGPRectF;
typedef TGPRectF *PGPRectF;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TGPRectF
{
public:
	float X;
	float Y;
	float Width;
	float Height;
};
#pragma pack(pop)


typedef System::DynamicArray<TGPRectF> TRectFDynArray;

struct TGPRect;
typedef TGPRect *PGPRect;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TGPRect
{
public:
	int X;
	int Y;
	int Width;
	int Height;
};
#pragma pack(pop)


typedef System::DynamicArray<TGPRect> TRectDynArray;

class DELPHICLASS TPathData;
#pragma pack(push,1)
class PASCALIMPLEMENTATION TPathData : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int Count;
	TGPPointF *Points;
	System::Byte *Types;
	__fastcall TPathData(void);
	__fastcall virtual ~TPathData(void);
};

#pragma pack(pop)

struct TCharacterRange;
typedef TCharacterRange *PCharacterRange;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TCharacterRange
{
public:
	int First;
	int Length;
};
#pragma pack(pop)


enum DECLSPEC_DENUM DebugEventLevel : unsigned int { DebugEventLevelFatal, DebugEventLevelWarning };

typedef DebugEventLevel TDebugEventLevel;

typedef void __stdcall (*DebugEventProc)(DebugEventLevel level, System::WideChar * message);

typedef Status __stdcall (*NotificationHookProc)(/* out */ unsigned &token);

typedef void __stdcall (*NotificationUnhookProc)(unsigned token);

#pragma pack(push,1)
struct DECLSPEC_DRECORD GdiplusStartupInput
{
public:
	unsigned GdiplusVersion;
	DebugEventProc DebugEventCallback;
	BOOL SuppressBackgroundThread;
	BOOL SuppressExternalCodecs;
};
#pragma pack(pop)


typedef GdiplusStartupInput TGdiplusStartupInput;

typedef GdiplusStartupInput *PGdiplusStartupInput;

#pragma pack(push,1)
struct DECLSPEC_DRECORD GdiplusStartupOutput
{
public:
	NotificationHookProc NotificationHook;
	NotificationUnhookProc NotificationUnhook;
};
#pragma pack(pop)


typedef GdiplusStartupOutput TGdiplusStartupOutput;

typedef GdiplusStartupOutput *PGdiplusStartupOutput;

typedef unsigned *PARGB;

typedef unsigned ARGB;

typedef __int64 ARGB64;

typedef int PixelFormat;

typedef int TPixelFormat;

typedef int PaletteFlags;

typedef int TPaletteFlags;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ColorPalette
{
public:
	unsigned Flags;
	unsigned Count;
	System::StaticArray<unsigned, 1> Entries;
};
#pragma pack(pop)


typedef ColorPalette TColorPalette;

typedef ColorPalette *PColorPalette;

enum DECLSPEC_DENUM ColorMode : unsigned int { ColorModeARGB32, ColorModeARGB64 };

typedef ColorMode TColorMode;

enum DECLSPEC_DENUM ColorChannelFlags : unsigned int { ColorChannelFlagsC, ColorChannelFlagsM, ColorChannelFlagsY, ColorChannelFlagsK, ColorChannelFlagsLast };

typedef ColorChannelFlags TColorChannelFlags;

typedef unsigned *PGPColor;

typedef unsigned TGPColor;

typedef System::DynamicArray<unsigned> TColorDynArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ENHMETAHEADER3
{
public:
	unsigned iType;
	unsigned nSize;
	System::Types::TRect rclBounds;
	System::Types::TRect rclFrame;
	unsigned dSignature;
	unsigned nVersion;
	unsigned nBytes;
	unsigned nRecords;
	System::Word nHandles;
	System::Word sReserved;
	unsigned nDescription;
	unsigned offDescription;
	unsigned nPalEntries;
	System::Types::TSize szlDevice;
	System::Types::TSize szlMillimeters;
};
#pragma pack(pop)


typedef ENHMETAHEADER3 TENHMETAHEADER3;

typedef ENHMETAHEADER3 *PENHMETAHEADER3;

#pragma pack(push,1)
struct DECLSPEC_DRECORD PWMFRect16
{
public:
	INT16 Left;
	INT16 Top;
	INT16 Right;
	INT16 Bottom;
};
#pragma pack(pop)


typedef PWMFRect16 TPWMFRect16;

typedef PWMFRect16 *PPWMFRect16;

#pragma pack(push,1)
struct DECLSPEC_DRECORD WmfPlaceableFileHeader
{
public:
	UINT32 Key;
	INT16 Hmf;
	PWMFRect16 BoundingBox;
	INT16 Inch;
	UINT32 Reserved;
	INT16 Checksum;
};
#pragma pack(pop)


typedef WmfPlaceableFileHeader TWmfPlaceableFileHeader;

typedef WmfPlaceableFileHeader *PWmfPlaceableFileHeader;

class DELPHICLASS TMetafileHeader;
#pragma pack(push,1)
class PASCALIMPLEMENTATION TMetafileHeader : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	MetafileType Type_;
	unsigned Size;
	unsigned Version;
	unsigned EmfPlusFlags;
	float DpiX;
	float DpiY;
	int X;
	int Y;
	int Width;
	int Height;
	ENHMETAHEADER3 EmfHeader;
	int EmfPlusHeaderSize;
	int LogicalDpiX;
	int LogicalDpiY;
	__property MetafileType GetType = {read=Type_, nodefault};
	__property unsigned GetMetafileSize = {read=Size, nodefault};
	__property unsigned GetVersion = {read=Version, nodefault};
	__property unsigned GetEmfPlusFlags = {read=EmfPlusFlags, nodefault};
	__property float GetDpiX = {read=DpiX};
	__property float GetDpiY = {read=DpiY};
	void __fastcall GetBounds(/* out */ TGPRect &Rect);
	BOOL __fastcall IsWmf(void);
	BOOL __fastcall IsWmfPlaceable(void);
	BOOL __fastcall IsEmf(void);
	BOOL __fastcall IsEmfOrEmfPlus(void);
	BOOL __fastcall IsEmfPlus(void);
	BOOL __fastcall IsEmfPlusDual(void);
	BOOL __fastcall IsEmfPlusOnly(void);
	BOOL __fastcall IsDisplay(void);
	Winapi::Windows::PMetaHeader __fastcall GetWmfHeader(void);
	PENHMETAHEADER3 __fastcall GetEmfHeader(void);
public:
	/* TObject.Create */ inline __fastcall TMetafileHeader(void) : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMetafileHeader(void) { }
	
};

#pragma pack(pop)

__interface IImageBytes;
typedef System::DelphiInterface<IImageBytes> _di_IImageBytes;
__interface  INTERFACE_UUID("{025D1823-6C7D-447B-BBDB-A3CBC3DFA2FC}") IImageBytes  : public System::IInterface 
{
	
public:
	virtual HRESULT __stdcall CountBytes(/* out */ unsigned &pcb) = 0 ;
	virtual HRESULT __stdcall LockBytes(unsigned cb, unsigned ulOffset, /* out */ void * &ppvBytes) = 0 ;
	virtual HRESULT __stdcall UnlockBytes(void * pvBytes, unsigned cb, unsigned ulOffset) = 0 ;
};

#pragma pack(push,1)
struct DECLSPEC_DRECORD ImageCodecInfo
{
public:
	GUID Clsid;
	GUID FormatID;
	System::WideChar *CodecName;
	System::WideChar *DllName;
	System::WideChar *FormatDescription;
	System::WideChar *FilenameExtension;
	System::WideChar *MimeType;
	unsigned Flags;
	unsigned Version;
	unsigned SigCount;
	unsigned SigSize;
	System::Byte *SigPattern;
	System::Byte *SigMask;
};
#pragma pack(pop)


typedef ImageCodecInfo TImageCodecInfo;

typedef ImageCodecInfo *PImageCodecInfo;

typedef int ImageCodecFlags;

typedef int TImageCodecFlags;

typedef int ImageLockMode;

typedef int TImageLockMode;

#pragma pack(push,1)
struct DECLSPEC_DRECORD BitmapData
{
public:
	unsigned Width;
	unsigned Height;
	int Stride;
	int PixelFormat;
	void *Scan0;
	unsigned Reserved;
};
#pragma pack(pop)


typedef BitmapData TBitmapData;

typedef BitmapData *PBitmapData;

typedef int ImageFlags;

typedef int TImageFlags;

enum DECLSPEC_DENUM RotateFlipType : unsigned int { RotateNoneFlipNone, Rotate90FlipNone, Rotate180FlipNone, Rotate270FlipNone, RotateNoneFlipX, Rotate90FlipX, Rotate180FlipX, Rotate270FlipX };

typedef RotateFlipType TRotateFlipType;

#pragma pack(push,1)
struct DECLSPEC_DRECORD EncoderParameter
{
public:
	GUID Guid;
	unsigned NumberOfValues;
	unsigned Type_;
	void *Value;
};
#pragma pack(pop)


typedef EncoderParameter TEncoderParameter;

typedef EncoderParameter *PEncoderParameter;

#pragma pack(push,1)
struct DECLSPEC_DRECORD EncoderParameters
{
public:
	unsigned Count;
	System::StaticArray<EncoderParameter, 1> Parameter;
};
#pragma pack(pop)


typedef EncoderParameters TEncoderParameters;

typedef EncoderParameters *PEncoderParameters;

struct DECLSPEC_DRECORD PropertyItem
{
public:
	unsigned id;
	unsigned length;
	System::Word type_;
	void *value;
};


typedef PropertyItem TPropertyItem;

typedef PropertyItem *PPropertyItem;

typedef System::StaticArray<System::StaticArray<float, 5>, 5> ColorMatrix;

typedef ColorMatrix TColorMatrix;

typedef ColorMatrix *PColorMatrix;

enum DECLSPEC_DENUM ColorMatrixFlags : unsigned int { ColorMatrixFlagsDefault, ColorMatrixFlagsSkipGrays, ColorMatrixFlagsAltGray };

typedef ColorMatrixFlags TColorMatrixFlags;

enum DECLSPEC_DENUM ColorAdjustType : unsigned int { ColorAdjustTypeDefault, ColorAdjustTypeBitmap, ColorAdjustTypeBrush, ColorAdjustTypePen, ColorAdjustTypeText, ColorAdjustTypeCount, ColorAdjustTypeAny };

typedef ColorAdjustType TColorAdjustType;

#pragma pack(push,1)
struct DECLSPEC_DRECORD ColorMap
{
public:
	unsigned oldColor;
	unsigned newColor;
};
#pragma pack(pop)


typedef ColorMap TColorMap;

typedef ColorMap *PColorMap;

typedef void * GpGraphics;

typedef void * GpBrush;

typedef void * GpTexture;

typedef void * GpSolidFill;

typedef void * GpLineGradient;

typedef void * GpPathGradient;

typedef void * GpHatch;

typedef void * GpPen;

typedef void * GpCustomLineCap;

typedef void * GpAdjustableArrowCap;

typedef void * GpImage;

typedef void * GpBitmap;

typedef void * GpMetafile;

typedef void * GpImageAttributes;

typedef void * GpPath;

typedef void * GpRegion;

typedef void * GpPathIterator;

typedef void * GpFontFamily;

typedef void * GpFont;

typedef void * GpStringFormat;

typedef void * GpFontCollection;

typedef void * GpCachedBitmap;

typedef Status GpStatus;

typedef FillMode GpFillMode;

typedef WrapMode GpWrapMode;

typedef Unit_ GpUnit;

typedef CoordinateSpace GpCoordinateSpace;

typedef PGPPointF GpPointF;

typedef PGPPoint GpPoint;

typedef PGPRectF GpRectF;

typedef PGPRect GpRect;

typedef PGPSizeF GpSizeF;

typedef HatchStyle GpHatchStyle;

typedef DashStyle GpDashStyle;

typedef int GpLineCap;

typedef int GpDashCap;

typedef PenAlignment GpPenAlignment;

typedef LineJoin GpLineJoin;

typedef int GpPenType;

typedef void * GpMatrix;

typedef BrushType GpBrushType;

typedef MatrixOrder GpMatrixOrder;

typedef FlushIntention GpFlushIntention;

typedef TPathData GpPathData;

//-- var, const, procedure ---------------------------------------------------
#define WINGDIPDLL L"gdiplus.dll"
extern DELPHI_PACKAGE void * __stdcall (*GdipAlloc)(unsigned size);
extern DELPHI_PACKAGE void __stdcall (*GdipFree)(void * ptr);
#define FlatnessDefault  (2.500000E-01)
static const System::Int8 QualityModeInvalid = System::Int8(-1);
static const System::Int8 QualityModeDefault = System::Int8(0x0);
static const System::Int8 QualityModeLow = System::Int8(0x1);
static const System::Int8 QualityModeHigh = System::Int8(0x2);
static const System::Int8 CompositingQualityInvalid = System::Int8(-1);
static const System::Int8 CompositingQualityDefault = System::Int8(0x0);
static const System::Int8 CompositingQualityHighSpeed = System::Int8(0x1);
static const System::Int8 CompositingQualityHighQuality = System::Int8(0x2);
static const System::Int8 CompositingQualityGammaCorrected = System::Int8(0x3);
static const System::Int8 CompositingQualityAssumeLinear = System::Int8(0x4);
static const System::Int8 MetafileFrameUnitPixel = System::Int8(0x2);
static const System::Int8 MetafileFrameUnitPoint = System::Int8(0x3);
static const System::Int8 MetafileFrameUnitInch = System::Int8(0x4);
static const System::Int8 MetafileFrameUnitDocument = System::Int8(0x5);
static const System::Int8 MetafileFrameUnitMillimeter = System::Int8(0x6);
static const System::Int8 MetafileFrameUnitGdi = System::Int8(0x7);
static const HatchStyle HatchStyleLargeGrid = (HatchStyle)(4);
static const HatchStyle HatchStyleMin = (HatchStyle)(0);
static const HatchStyle HatchStyleMax = (HatchStyle)(52);
static const System::Int8 DashCapFlat = System::Int8(0x0);
static const System::Int8 DashCapRound = System::Int8(0x2);
static const System::Int8 DashCapTriangle = System::Int8(0x3);
static const System::Int8 LineCapFlat = System::Int8(0x0);
static const System::Int8 LineCapSquare = System::Int8(0x1);
static const System::Int8 LineCapRound = System::Int8(0x2);
static const System::Int8 LineCapTriangle = System::Int8(0x3);
static const System::Int8 LineCapNoAnchor = System::Int8(0x10);
static const System::Int8 LineCapSquareAnchor = System::Int8(0x11);
static const System::Int8 LineCapRoundAnchor = System::Int8(0x12);
static const System::Int8 LineCapDiamondAnchor = System::Int8(0x13);
static const System::Int8 LineCapArrowAnchor = System::Int8(0x14);
static const System::Byte LineCapCustom = System::Byte(0xff);
static const System::Byte LineCapAnchorMask = System::Byte(0xf0);
extern DELPHI_PACKAGE System::Byte PathPointTypeStart;
extern DELPHI_PACKAGE System::Byte PathPointTypeLine;
extern DELPHI_PACKAGE System::Byte PathPointTypeBezier;
extern DELPHI_PACKAGE System::Byte PathPointTypePathTypeMask;
extern DELPHI_PACKAGE System::Byte PathPointTypeDashMode;
extern DELPHI_PACKAGE System::Byte PathPointTypePathMarker;
extern DELPHI_PACKAGE System::Byte PathPointTypeCloseSubpath;
extern DELPHI_PACKAGE System::Byte PathPointTypeBezier3;
static const System::Int8 InterpolationModeInvalid = System::Int8(-1);
static const System::Int8 InterpolationModeDefault = System::Int8(0x0);
static const System::Int8 InterpolationModeLowQuality = System::Int8(0x1);
static const System::Int8 InterpolationModeHighQuality = System::Int8(0x2);
static const System::Int8 InterpolationModeBilinear = System::Int8(0x3);
static const System::Int8 InterpolationModeBicubic = System::Int8(0x4);
static const System::Int8 InterpolationModeNearestNeighbor = System::Int8(0x5);
static const System::Int8 InterpolationModeHighQualityBilinear = System::Int8(0x6);
static const System::Int8 InterpolationModeHighQualityBicubic = System::Int8(0x7);
static const System::Int8 PenTypeSolidColor = System::Int8(0x0);
static const System::Int8 PenTypeHatchFill = System::Int8(0x1);
static const System::Int8 PenTypeTextureFill = System::Int8(0x2);
static const System::Int8 PenTypePathGradient = System::Int8(0x3);
static const System::Int8 PenTypeLinearGradient = System::Int8(0x4);
static const System::Int8 PenTypeUnknown = System::Int8(-1);
static const int FontStyleRegular = int(0);
static const int FontStyleBold = int(1);
static const int FontStyleItalic = int(2);
static const int FontStyleBoldItalic = int(3);
static const int FontStyleUnderline = int(4);
static const int FontStyleStrikeout = int(8);
static const System::Int8 SmoothingModeInvalid = System::Int8(-1);
static const System::Int8 SmoothingModeDefault = System::Int8(0x0);
static const System::Int8 SmoothingModeHighSpeed = System::Int8(0x1);
static const System::Int8 SmoothingModeHighQuality = System::Int8(0x2);
static const System::Int8 SmoothingModeNone = System::Int8(0x3);
static const System::Int8 SmoothingModeAntiAlias = System::Int8(0x4);
static const System::Int8 PixelOffsetModeInvalid = System::Int8(-1);
static const System::Int8 PixelOffsetModeDefault = System::Int8(0x0);
static const System::Int8 PixelOffsetModeHighSpeed = System::Int8(0x1);
static const System::Int8 PixelOffsetModeHighQuality = System::Int8(0x2);
static const System::Int8 PixelOffsetModeNone = System::Int8(0x3);
static const System::Int8 PixelOffsetModeHalf = System::Int8(0x4);
static const System::Int8 EmfTypeEmfOnly = System::Int8(3);
static const System::Int8 EmfTypeEmfPlusOnly = System::Int8(4);
static const System::Int8 EmfTypeEmfPlusDual = System::Int8(5);
static const ObjectType ObjectTypeMax = (ObjectType)(9);
static const ObjectType ObjectTypeMin = (ObjectType)(1);
static const System::Word GDIP_EMFPLUS_RECORD_BASE = System::Word(0x4000);
static const int GDIP_WMF_RECORD_BASE = int(0x10000);
static const int WmfRecordTypeSetBkColor = int(0x10201);
static const int WmfRecordTypeSetBkMode = int(0x10102);
static const int WmfRecordTypeSetMapMode = int(0x10103);
static const int WmfRecordTypeSetROP2 = int(0x10104);
static const int WmfRecordTypeSetRelAbs = int(0x10105);
static const int WmfRecordTypeSetPolyFillMode = int(0x10106);
static const int WmfRecordTypeSetStretchBltMode = int(0x10107);
static const int WmfRecordTypeSetTextCharExtra = int(0x10108);
static const int WmfRecordTypeSetTextColor = int(0x10209);
static const int WmfRecordTypeSetTextJustification = int(0x1020a);
static const int WmfRecordTypeSetWindowOrg = int(0x1020b);
static const int WmfRecordTypeSetWindowExt = int(0x1020c);
static const int WmfRecordTypeSetViewportOrg = int(0x1020d);
static const int WmfRecordTypeSetViewportExt = int(0x1020e);
static const int WmfRecordTypeOffsetWindowOrg = int(0x1020f);
static const int WmfRecordTypeScaleWindowExt = int(0x10410);
static const int WmfRecordTypeOffsetViewportOrg = int(0x10211);
static const int WmfRecordTypeScaleViewportExt = int(0x10412);
static const int WmfRecordTypeLineTo = int(0x10213);
static const int WmfRecordTypeMoveTo = int(0x10214);
static const int WmfRecordTypeExcludeClipRect = int(0x10415);
static const int WmfRecordTypeIntersectClipRect = int(0x10416);
static const int WmfRecordTypeArc = int(0x10817);
static const int WmfRecordTypeEllipse = int(0x10418);
static const int WmfRecordTypeFloodFill = int(0x10419);
static const int WmfRecordTypePie = int(0x1081a);
static const int WmfRecordTypeRectangle = int(0x1041b);
static const int WmfRecordTypeRoundRect = int(0x1061c);
static const int WmfRecordTypePatBlt = int(0x1061d);
static const int WmfRecordTypeSaveDC = int(0x1001e);
static const int WmfRecordTypeSetPixel = int(0x1041f);
static const int WmfRecordTypeOffsetClipRgn = int(0x10220);
static const int WmfRecordTypeTextOut = int(0x10521);
static const int WmfRecordTypeBitBlt = int(0x10922);
static const int WmfRecordTypeStretchBlt = int(0x10b23);
static const int WmfRecordTypePolygon = int(0x10324);
static const int WmfRecordTypePolyline = int(0x10325);
static const int WmfRecordTypeEscape = int(0x10626);
static const int WmfRecordTypeRestoreDC = int(0x10127);
static const int WmfRecordTypeFillRegion = int(0x10228);
static const int WmfRecordTypeFrameRegion = int(0x10429);
static const int WmfRecordTypeInvertRegion = int(0x1012a);
static const int WmfRecordTypePaintRegion = int(0x1012b);
static const int WmfRecordTypeSelectClipRegion = int(0x1012c);
static const int WmfRecordTypeSelectObject = int(0x1012d);
static const int WmfRecordTypeSetTextAlign = int(0x1012e);
static const int WmfRecordTypeDrawText = int(0x1062f);
static const int WmfRecordTypeChord = int(0x10830);
static const int WmfRecordTypeSetMapperFlags = int(0x10231);
static const int WmfRecordTypeExtTextOut = int(0x10a32);
static const int WmfRecordTypeSetDIBToDev = int(0x10d33);
static const int WmfRecordTypeSelectPalette = int(0x10234);
static const int WmfRecordTypeRealizePalette = int(0x10035);
static const int WmfRecordTypeAnimatePalette = int(0x10436);
static const int WmfRecordTypeSetPalEntries = int(0x10037);
static const int WmfRecordTypePolyPolygon = int(0x10538);
static const int WmfRecordTypeResizePalette = int(0x10139);
static const int WmfRecordTypeDIBBitBlt = int(0x10940);
static const int WmfRecordTypeDIBStretchBlt = int(0x10b41);
static const int WmfRecordTypeDIBCreatePatternBrush = int(0x10142);
static const int WmfRecordTypeStretchDIB = int(0x10f43);
static const int WmfRecordTypeExtFloodFill = int(0x10548);
static const int WmfRecordTypeSetLayout = int(0x10149);
static const int WmfRecordTypeResetDC = int(0x1014c);
static const int WmfRecordTypeStartDoc = int(0x1014d);
static const int WmfRecordTypeStartPage = int(0x1004f);
static const int WmfRecordTypeEndPage = int(0x10050);
static const int WmfRecordTypeAbortDoc = int(0x10052);
static const int WmfRecordTypeEndDoc = int(0x1005e);
static const int WmfRecordTypeDeleteObject = int(0x101f0);
static const int WmfRecordTypeCreatePalette = int(0x100f7);
static const int WmfRecordTypeCreateBrush = int(0x100f8);
static const int WmfRecordTypeCreatePatternBrush = int(0x101f9);
static const int WmfRecordTypeCreatePenIndirect = int(0x102fa);
static const int WmfRecordTypeCreateFontIndirect = int(0x102fb);
static const int WmfRecordTypeCreateBrushIndirect = int(0x102fc);
static const int WmfRecordTypeCreateBitmapIndirect = int(0x102fd);
static const int WmfRecordTypeCreateBitmap = int(0x106fe);
static const int WmfRecordTypeCreateRegion = int(0x106ff);
static const System::Int8 EmfRecordTypeHeader = System::Int8(0x1);
static const System::Int8 EmfRecordTypePolyBezier = System::Int8(0x2);
static const System::Int8 EmfRecordTypePolygon = System::Int8(0x3);
static const System::Int8 EmfRecordTypePolyline = System::Int8(0x4);
static const System::Int8 EmfRecordTypePolyBezierTo = System::Int8(0x5);
static const System::Int8 EmfRecordTypePolyLineTo = System::Int8(0x6);
static const System::Int8 EmfRecordTypePolyPolyline = System::Int8(0x7);
static const System::Int8 EmfRecordTypePolyPolygon = System::Int8(0x8);
static const System::Int8 EmfRecordTypeSetWindowExtEx = System::Int8(0x9);
static const System::Int8 EmfRecordTypeSetWindowOrgEx = System::Int8(0xa);
static const System::Int8 EmfRecordTypeSetViewportExtEx = System::Int8(0xb);
static const System::Int8 EmfRecordTypeSetViewportOrgEx = System::Int8(0xc);
static const System::Int8 EmfRecordTypeSetBrushOrgEx = System::Int8(0xd);
static const System::Int8 EmfRecordTypeEOF = System::Int8(0xe);
static const System::Int8 EmfRecordTypeSetPixelV = System::Int8(0xf);
static const System::Int8 EmfRecordTypeSetMapperFlags = System::Int8(0x10);
static const System::Int8 EmfRecordTypeSetMapMode = System::Int8(0x11);
static const System::Int8 EmfRecordTypeSetBkMode = System::Int8(0x12);
static const System::Int8 EmfRecordTypeSetPolyFillMode = System::Int8(0x13);
static const System::Int8 EmfRecordTypeSetROP2 = System::Int8(0x14);
static const System::Int8 EmfRecordTypeSetStretchBltMode = System::Int8(0x15);
static const System::Int8 EmfRecordTypeSetTextAlign = System::Int8(0x16);
static const System::Int8 EmfRecordTypeSetColorAdjustment = System::Int8(0x17);
static const System::Int8 EmfRecordTypeSetTextColor = System::Int8(0x18);
static const System::Int8 EmfRecordTypeSetBkColor = System::Int8(0x19);
static const System::Int8 EmfRecordTypeOffsetClipRgn = System::Int8(0x1a);
static const System::Int8 EmfRecordTypeMoveToEx = System::Int8(0x1b);
static const System::Int8 EmfRecordTypeSetMetaRgn = System::Int8(0x1c);
static const System::Int8 EmfRecordTypeExcludeClipRect = System::Int8(0x1d);
static const System::Int8 EmfRecordTypeIntersectClipRect = System::Int8(0x1e);
static const System::Int8 EmfRecordTypeScaleViewportExtEx = System::Int8(0x1f);
static const System::Int8 EmfRecordTypeScaleWindowExtEx = System::Int8(0x20);
static const System::Int8 EmfRecordTypeSaveDC = System::Int8(0x21);
static const System::Int8 EmfRecordTypeRestoreDC = System::Int8(0x22);
static const System::Int8 EmfRecordTypeSetWorldTransform = System::Int8(0x23);
static const System::Int8 EmfRecordTypeModifyWorldTransform = System::Int8(0x24);
static const System::Int8 EmfRecordTypeSelectObject = System::Int8(0x25);
static const System::Int8 EmfRecordTypeCreatePen = System::Int8(0x26);
static const System::Int8 EmfRecordTypeCreateBrushIndirect = System::Int8(0x27);
static const System::Int8 EmfRecordTypeDeleteObject = System::Int8(0x28);
static const System::Int8 EmfRecordTypeAngleArc = System::Int8(0x29);
static const System::Int8 EmfRecordTypeEllipse = System::Int8(0x2a);
static const System::Int8 EmfRecordTypeRectangle = System::Int8(0x2b);
static const System::Int8 EmfRecordTypeRoundRect = System::Int8(0x2c);
static const System::Int8 EmfRecordTypeArc = System::Int8(0x2d);
static const System::Int8 EmfRecordTypeChord = System::Int8(0x2e);
static const System::Int8 EmfRecordTypePie = System::Int8(0x2f);
static const System::Int8 EmfRecordTypeSelectPalette = System::Int8(0x30);
static const System::Int8 EmfRecordTypeCreatePalette = System::Int8(0x31);
static const System::Int8 EmfRecordTypeSetPaletteEntries = System::Int8(0x32);
static const System::Int8 EmfRecordTypeResizePalette = System::Int8(0x33);
static const System::Int8 EmfRecordTypeRealizePalette = System::Int8(0x34);
static const System::Int8 EmfRecordTypeExtFloodFill = System::Int8(0x35);
static const System::Int8 EmfRecordTypeLineTo = System::Int8(0x36);
static const System::Int8 EmfRecordTypeArcTo = System::Int8(0x37);
static const System::Int8 EmfRecordTypePolyDraw = System::Int8(0x38);
static const System::Int8 EmfRecordTypeSetArcDirection = System::Int8(0x39);
static const System::Int8 EmfRecordTypeSetMiterLimit = System::Int8(0x3a);
static const System::Int8 EmfRecordTypeBeginPath = System::Int8(0x3b);
static const System::Int8 EmfRecordTypeEndPath = System::Int8(0x3c);
static const System::Int8 EmfRecordTypeCloseFigure = System::Int8(0x3d);
static const System::Int8 EmfRecordTypeFillPath = System::Int8(0x3e);
static const System::Int8 EmfRecordTypeStrokeAndFillPath = System::Int8(0x3f);
static const System::Int8 EmfRecordTypeStrokePath = System::Int8(0x40);
static const System::Int8 EmfRecordTypeFlattenPath = System::Int8(0x41);
static const System::Int8 EmfRecordTypeWidenPath = System::Int8(0x42);
static const System::Int8 EmfRecordTypeSelectClipPath = System::Int8(0x43);
static const System::Int8 EmfRecordTypeAbortPath = System::Int8(0x44);
static const System::Int8 EmfRecordTypeReserved_069 = System::Int8(0x45);
static const System::Int8 EmfRecordTypeGdiComment = System::Int8(0x46);
static const System::Int8 EmfRecordTypeFillRgn = System::Int8(0x47);
static const System::Int8 EmfRecordTypeFrameRgn = System::Int8(0x48);
static const System::Int8 EmfRecordTypeInvertRgn = System::Int8(0x49);
static const System::Int8 EmfRecordTypePaintRgn = System::Int8(0x4a);
static const System::Int8 EmfRecordTypeExtSelectClipRgn = System::Int8(0x4b);
static const System::Int8 EmfRecordTypeBitBlt = System::Int8(0x4c);
static const System::Int8 EmfRecordTypeStretchBlt = System::Int8(0x4d);
static const System::Int8 EmfRecordTypeMaskBlt = System::Int8(0x4e);
static const System::Int8 EmfRecordTypePlgBlt = System::Int8(0x4f);
static const System::Int8 EmfRecordTypeSetDIBitsToDevice = System::Int8(0x50);
static const System::Int8 EmfRecordTypeStretchDIBits = System::Int8(0x51);
static const System::Int8 EmfRecordTypeExtCreateFontIndirect = System::Int8(0x52);
static const System::Int8 EmfRecordTypeExtTextOutA = System::Int8(0x53);
static const System::Int8 EmfRecordTypeExtTextOutW = System::Int8(0x54);
static const System::Int8 EmfRecordTypePolyBezier16 = System::Int8(0x55);
static const System::Int8 EmfRecordTypePolygon16 = System::Int8(0x56);
static const System::Int8 EmfRecordTypePolyline16 = System::Int8(0x57);
static const System::Int8 EmfRecordTypePolyBezierTo16 = System::Int8(0x58);
static const System::Int8 EmfRecordTypePolylineTo16 = System::Int8(0x59);
static const System::Int8 EmfRecordTypePolyPolyline16 = System::Int8(0x5a);
static const System::Int8 EmfRecordTypePolyPolygon16 = System::Int8(0x5b);
static const System::Int8 EmfRecordTypePolyDraw16 = System::Int8(0x5c);
static const System::Int8 EmfRecordTypeCreateMonoBrush = System::Int8(0x5d);
static const System::Int8 EmfRecordTypeCreateDIBPatternBrushPt = System::Int8(0x5e);
static const System::Int8 EmfRecordTypeExtCreatePen = System::Int8(0x5f);
static const System::Int8 EmfRecordTypePolyTextOutA = System::Int8(0x60);
static const System::Int8 EmfRecordTypePolyTextOutW = System::Int8(0x61);
static const System::Int8 EmfRecordTypeSetICMMode = System::Int8(0x62);
static const System::Int8 EmfRecordTypeCreateColorSpace = System::Int8(0x63);
static const System::Int8 EmfRecordTypeSetColorSpace = System::Int8(0x64);
static const System::Int8 EmfRecordTypeDeleteColorSpace = System::Int8(0x65);
static const System::Int8 EmfRecordTypeGLSRecord = System::Int8(0x66);
static const System::Int8 EmfRecordTypeGLSBoundedRecord = System::Int8(0x67);
static const System::Int8 EmfRecordTypePixelFormat = System::Int8(0x68);
static const System::Int8 EmfRecordTypeDrawEscape = System::Int8(0x69);
static const System::Int8 EmfRecordTypeExtEscape = System::Int8(0x6a);
static const System::Int8 EmfRecordTypeStartDoc = System::Int8(0x6b);
static const System::Int8 EmfRecordTypeSmallTextOut = System::Int8(0x6c);
static const System::Int8 EmfRecordTypeForceUFIMapping = System::Int8(0x6d);
static const System::Int8 EmfRecordTypeNamedEscape = System::Int8(0x6e);
static const System::Int8 EmfRecordTypeColorCorrectPalette = System::Int8(0x6f);
static const System::Int8 EmfRecordTypeSetICMProfileA = System::Int8(0x70);
static const System::Int8 EmfRecordTypeSetICMProfileW = System::Int8(0x71);
static const System::Int8 EmfRecordTypeAlphaBlend = System::Int8(0x72);
static const System::Int8 EmfRecordTypeSetLayout = System::Int8(0x73);
static const System::Int8 EmfRecordTypeTransparentBlt = System::Int8(0x74);
static const System::Int8 EmfRecordTypeReserved_117 = System::Int8(0x75);
static const System::Int8 EmfRecordTypeGradientFill = System::Int8(0x76);
static const System::Int8 EmfRecordTypeSetLinkedUFIs = System::Int8(0x77);
static const System::Int8 EmfRecordTypeSetTextJustification = System::Int8(0x78);
static const System::Int8 EmfRecordTypeColorMatchToTargetW = System::Int8(0x79);
static const System::Int8 EmfRecordTypeCreateColorSpaceW = System::Int8(0x7a);
static const System::Int8 EmfRecordTypeMax = System::Int8(0x7a);
static const System::Int8 EmfRecordTypeMin = System::Int8(0x1);
static const System::Word EmfPlusRecordTypeInvalid = System::Word(0x4000);
static const System::Word EmfPlusRecordTypeHeader = System::Word(0x4001);
static const System::Word EmfPlusRecordTypeEndOfFile = System::Word(0x4002);
static const System::Word EmfPlusRecordTypeComment = System::Word(0x4003);
static const System::Word EmfPlusRecordTypeGetDC = System::Word(0x4004);
static const System::Word EmfPlusRecordTypeMultiFormatStart = System::Word(0x4005);
static const System::Word EmfPlusRecordTypeMultiFormatSection = System::Word(0x4006);
static const System::Word EmfPlusRecordTypeMultiFormatEnd = System::Word(0x4007);
static const System::Word EmfPlusRecordTypeObject = System::Word(0x4008);
static const System::Word EmfPlusRecordTypeClear = System::Word(0x4009);
static const System::Word EmfPlusRecordTypeFillRects = System::Word(0x400a);
static const System::Word EmfPlusRecordTypeDrawRects = System::Word(0x400b);
static const System::Word EmfPlusRecordTypeFillPolygon = System::Word(0x400c);
static const System::Word EmfPlusRecordTypeDrawLines = System::Word(0x400d);
static const System::Word EmfPlusRecordTypeFillEllipse = System::Word(0x400e);
static const System::Word EmfPlusRecordTypeDrawEllipse = System::Word(0x400f);
static const System::Word EmfPlusRecordTypeFillPie = System::Word(0x4010);
static const System::Word EmfPlusRecordTypeDrawPie = System::Word(0x4011);
static const System::Word EmfPlusRecordTypeDrawArc = System::Word(0x4012);
static const System::Word EmfPlusRecordTypeFillRegion = System::Word(0x4013);
static const System::Word EmfPlusRecordTypeFillPath = System::Word(0x4014);
static const System::Word EmfPlusRecordTypeDrawPath = System::Word(0x4015);
static const System::Word EmfPlusRecordTypeFillClosedCurve = System::Word(0x4016);
static const System::Word EmfPlusRecordTypeDrawClosedCurve = System::Word(0x4017);
static const System::Word EmfPlusRecordTypeDrawCurve = System::Word(0x4018);
static const System::Word EmfPlusRecordTypeDrawBeziers = System::Word(0x4019);
static const System::Word EmfPlusRecordTypeDrawImage = System::Word(0x401a);
static const System::Word EmfPlusRecordTypeDrawImagePoints = System::Word(0x401b);
static const System::Word EmfPlusRecordTypeDrawString = System::Word(0x401c);
static const System::Word EmfPlusRecordTypeSetRenderingOrigin = System::Word(0x401d);
static const System::Word EmfPlusRecordTypeSetAntiAliasMode = System::Word(0x401e);
static const System::Word EmfPlusRecordTypeSetTextRenderingHint = System::Word(0x401f);
static const System::Word EmfPlusRecordTypeSetTextContrast = System::Word(0x4020);
static const System::Word EmfPlusRecordTypeSetInterpolationMode = System::Word(0x4021);
static const System::Word EmfPlusRecordTypeSetPixelOffsetMode = System::Word(0x4022);
static const System::Word EmfPlusRecordTypeSetCompositingMode = System::Word(0x4023);
static const System::Word EmfPlusRecordTypeSetCompositingQuality = System::Word(0x4024);
static const System::Word EmfPlusRecordTypeSave = System::Word(0x4025);
static const System::Word EmfPlusRecordTypeRestore = System::Word(0x4026);
static const System::Word EmfPlusRecordTypeBeginContainer = System::Word(0x4027);
static const System::Word EmfPlusRecordTypeBeginContainerNoParams = System::Word(0x4028);
static const System::Word EmfPlusRecordTypeEndContainer = System::Word(0x4029);
static const System::Word EmfPlusRecordTypeSetWorldTransform = System::Word(0x402a);
static const System::Word EmfPlusRecordTypeResetWorldTransform = System::Word(0x402b);
static const System::Word EmfPlusRecordTypeMultiplyWorldTransform = System::Word(0x402c);
static const System::Word EmfPlusRecordTypeTranslateWorldTransform = System::Word(0x402d);
static const System::Word EmfPlusRecordTypeScaleWorldTransform = System::Word(0x402e);
static const System::Word EmfPlusRecordTypeRotateWorldTransform = System::Word(0x402f);
static const System::Word EmfPlusRecordTypeSetPageTransform = System::Word(0x4030);
static const System::Word EmfPlusRecordTypeResetClip = System::Word(0x4031);
static const System::Word EmfPlusRecordTypeSetClipRect = System::Word(0x4032);
static const System::Word EmfPlusRecordTypeSetClipPath = System::Word(0x4033);
static const System::Word EmfPlusRecordTypeSetClipRegion = System::Word(0x4034);
static const System::Word EmfPlusRecordTypeOffsetClip = System::Word(0x4035);
static const System::Word EmfPlusRecordTypeDrawDriverString = System::Word(0x4036);
static const System::Word EmfPlusRecordTotal = System::Word(0x4037);
static const System::Word EmfPlusRecordTypeMax = System::Word(0x4036);
static const System::Word EmfPlusRecordTypeMin = System::Word(0x4001);
static const System::Int8 StringFormatFlagsDirectionRightToLeft = System::Int8(0x1);
static const System::Int8 StringFormatFlagsDirectionVertical = System::Int8(0x2);
static const System::Int8 StringFormatFlagsNoFitBlackBox = System::Int8(0x4);
static const System::Int8 StringFormatFlagsDisplayFormatControl = System::Int8(0x20);
static const System::Word StringFormatFlagsNoFontFallback = System::Word(0x400);
static const System::Word StringFormatFlagsMeasureTrailingSpaces = System::Word(0x800);
static const System::Word StringFormatFlagsNoWrap = System::Word(0x1000);
static const System::Word StringFormatFlagsLineLimit = System::Word(0x2000);
static const System::Word StringFormatFlagsNoClip = System::Word(0x4000);
static const System::Int8 DriverStringOptionsCmapLookup = System::Int8(0x1);
static const System::Int8 DriverStringOptionsVertical = System::Int8(0x2);
static const System::Int8 DriverStringOptionsRealizedAdvance = System::Int8(0x4);
static const System::Int8 DriverStringOptionsLimitSubpixel = System::Int8(0x8);
extern DELPHI_PACKAGE int EncoderParameterValueTypeByte;
extern DELPHI_PACKAGE int EncoderParameterValueTypeASCII;
extern DELPHI_PACKAGE int EncoderParameterValueTypeShort;
extern DELPHI_PACKAGE int EncoderParameterValueTypeLong;
extern DELPHI_PACKAGE int EncoderParameterValueTypeRational;
extern DELPHI_PACKAGE int EncoderParameterValueTypeLongRange;
extern DELPHI_PACKAGE int EncoderParameterValueTypeUndefined;
extern DELPHI_PACKAGE int EncoderParameterValueTypeRationalRange;
static const System::Int8 EmfToWmfBitsFlagsDefault = System::Int8(0x0);
static const System::Int8 EmfToWmfBitsFlagsEmbedEmf = System::Int8(0x1);
static const System::Int8 EmfToWmfBitsFlagsIncludePlaceable = System::Int8(0x2);
static const System::Int8 EmfToWmfBitsFlagsNoXORClip = System::Int8(0x4);
static const System::Extended FLT_MAX = 3.402823E+38;
static const System::Extended FLT_MIN = 1.175494E-38;
static const System::Extended REAL_MAX = 3.402823E+38;
static const System::Extended REAL_MIN = 1.175494E-38;
static const System::Extended REAL_TOLERANCE = 1.175494E-36;
static const System::Extended REAL_EPSILON = 1.192093E-07;
extern DELPHI_PACKAGE Status __stdcall (*GdiplusStartup)(/* out */ unsigned &token, PGdiplusStartupInput input, PGdiplusStartupOutput output);
extern DELPHI_PACKAGE void __stdcall (*GdiplusShutdown)(unsigned token);
static const System::Int8 ALPHA_SHIFT = System::Int8(0x18);
static const System::Int8 RED_SHIFT = System::Int8(0x10);
static const System::Int8 GREEN_SHIFT = System::Int8(0x8);
static const System::Int8 BLUE_SHIFT = System::Int8(0x0);
static const unsigned ALPHA_MASK = unsigned(0xff000000);
static const int PixelFormatIndexed = int(0x10000);
static const int PixelFormatGDI = int(0x20000);
static const int PixelFormatAlpha = int(0x40000);
static const int PixelFormatPAlpha = int(0x80000);
static const int PixelFormatExtended = int(0x100000);
static const int PixelFormatCanonical = int(0x200000);
static const System::Int8 PixelFormatUndefined = System::Int8(0x0);
static const System::Int8 PixelFormatDontCare = System::Int8(0x0);
static const int PixelFormat1bppIndexed = int(0x30101);
static const int PixelFormat4bppIndexed = int(0x30402);
static const int PixelFormat8bppIndexed = int(0x30803);
static const int PixelFormat16bppGrayScale = int(0x101004);
static const int PixelFormat16bppRGB555 = int(0x21005);
static const int PixelFormat16bppRGB565 = int(0x21006);
static const int PixelFormat16bppARGB1555 = int(0x61007);
static const int PixelFormat24bppRGB = int(0x21808);
static const int PixelFormat32bppRGB = int(0x22009);
static const int PixelFormat32bppARGB = int(0x26200a);
static const int PixelFormat32bppPARGB = int(0xe200b);
static const int PixelFormat48bppRGB = int(0x10300c);
static const int PixelFormat64bppARGB = int(0x34400d);
static const int PixelFormat64bppPARGB = int(0x1c400e);
static const System::Int8 PixelFormatMax = System::Int8(0xf);
static const System::Int8 PaletteFlagsHasAlpha = System::Int8(0x1);
static const System::Int8 PaletteFlagsGrayScale = System::Int8(0x2);
static const System::Int8 PaletteFlagsHalftone = System::Int8(0x4);
static const unsigned aclAliceBlue = unsigned(0xfff0f8ff);
static const unsigned aclAntiqueWhite = unsigned(0xfffaebd7);
static const unsigned aclAqua = unsigned(0xff00ffff);
static const unsigned aclAquamarine = unsigned(0xff7fffd4);
static const unsigned aclAzure = unsigned(0xfff0ffff);
static const unsigned aclBeige = unsigned(0xfff5f5dc);
static const unsigned aclBisque = unsigned(0xffffe4c4);
static const unsigned aclBlack = unsigned(0xff000000);
static const unsigned aclBlanchedAlmond = unsigned(0xffffebcd);
static const unsigned aclBlue = unsigned(0xff0000ff);
static const unsigned aclBlueViolet = unsigned(0xff8a2be2);
static const unsigned aclBrown = unsigned(0xffa52a2a);
static const unsigned aclBurlyWood = unsigned(0xffdeb887);
static const unsigned aclCadetBlue = unsigned(0xff5f9ea0);
static const unsigned aclChartreuse = unsigned(0xff7fff00);
static const unsigned aclChocolate = unsigned(0xffd2691e);
static const unsigned aclCoral = unsigned(0xffff7f50);
static const unsigned aclCornflowerBlue = unsigned(0xff6495ed);
static const unsigned aclCornsilk = unsigned(0xfffff8dc);
static const unsigned aclCrimson = unsigned(0xffdc143c);
static const unsigned aclCyan = unsigned(0xff00ffff);
static const unsigned aclDarkBlue = unsigned(0xff00008b);
static const unsigned aclDarkCyan = unsigned(0xff008b8b);
static const unsigned aclDarkGoldenrod = unsigned(0xffb8860b);
static const unsigned aclDarkGray = unsigned(0xffa9a9a9);
static const unsigned aclDarkGreen = unsigned(0xff006400);
static const unsigned aclDarkKhaki = unsigned(0xffbdb76b);
static const unsigned aclDarkMagenta = unsigned(0xff8b008b);
static const unsigned aclDarkOliveGreen = unsigned(0xff556b2f);
static const unsigned aclDarkOrange = unsigned(0xffff8c00);
static const unsigned aclDarkOrchid = unsigned(0xff9932cc);
static const unsigned aclDarkRed = unsigned(0xff8b0000);
static const unsigned aclDarkSalmon = unsigned(0xffe9967a);
static const unsigned aclDarkSeaGreen = unsigned(0xff8fbc8b);
static const unsigned aclDarkSlateBlue = unsigned(0xff483d8b);
static const unsigned aclDarkSlateGray = unsigned(0xff2f4f4f);
static const unsigned aclDarkTurquoise = unsigned(0xff00ced1);
static const unsigned aclDarkViolet = unsigned(0xff9400d3);
static const unsigned aclDeepPink = unsigned(0xffff1493);
static const unsigned aclDeepSkyBlue = unsigned(0xff00bfff);
static const unsigned aclDimGray = unsigned(0xff696969);
static const unsigned aclDodgerBlue = unsigned(0xff1e90ff);
static const unsigned aclFirebrick = unsigned(0xffb22222);
static const unsigned aclFloralWhite = unsigned(0xfffffaf0);
static const unsigned aclForestGreen = unsigned(0xff228b22);
static const unsigned aclFuchsia = unsigned(0xffff00ff);
static const unsigned aclGainsboro = unsigned(0xffdcdcdc);
static const unsigned aclGhostWhite = unsigned(0xfff8f8ff);
static const unsigned aclGold = unsigned(0xffffd700);
static const unsigned aclGoldenrod = unsigned(0xffdaa520);
static const unsigned aclGray = unsigned(0xff808080);
static const unsigned aclGreen = unsigned(0xff008000);
static const unsigned aclGreenYellow = unsigned(0xffadff2f);
static const unsigned aclHoneydew = unsigned(0xfff0fff0);
static const unsigned aclHotPink = unsigned(0xffff69b4);
static const unsigned aclIndianRed = unsigned(0xffcd5c5c);
static const unsigned aclIndigo = unsigned(0xff4b0082);
static const unsigned aclIvory = unsigned(0xfffffff0);
static const unsigned aclKhaki = unsigned(0xfff0e68c);
static const unsigned aclLavender = unsigned(0xffe6e6fa);
static const unsigned aclLavenderBlush = unsigned(0xfffff0f5);
static const unsigned aclLawnGreen = unsigned(0xff7cfc00);
static const unsigned aclLemonChiffon = unsigned(0xfffffacd);
static const unsigned aclLightBlue = unsigned(0xffadd8e6);
static const unsigned aclLightCoral = unsigned(0xfff08080);
static const unsigned aclLightCyan = unsigned(0xffe0ffff);
static const unsigned aclLightGoldenrodYellow = unsigned(0xfffafad2);
static const unsigned aclLightGray = unsigned(0xffd3d3d3);
static const unsigned aclLightGreen = unsigned(0xff90ee90);
static const unsigned aclLightPink = unsigned(0xffffb6c1);
static const unsigned aclLightSalmon = unsigned(0xffffa07a);
static const unsigned aclLightSeaGreen = unsigned(0xff20b2aa);
static const unsigned aclLightSkyBlue = unsigned(0xff87cefa);
static const unsigned aclLightSlateGray = unsigned(0xff778899);
static const unsigned aclLightSteelBlue = unsigned(0xffb0c4de);
static const unsigned aclLightYellow = unsigned(0xffffffe0);
static const unsigned aclLime = unsigned(0xff00ff00);
static const unsigned aclLimeGreen = unsigned(0xff32cd32);
static const unsigned aclLinen = unsigned(0xfffaf0e6);
static const unsigned aclMagenta = unsigned(0xffff00ff);
static const unsigned aclMaroon = unsigned(0xff800000);
static const unsigned aclMediumAquamarine = unsigned(0xff66cdaa);
static const unsigned aclMediumBlue = unsigned(0xff0000cd);
static const unsigned aclMediumOrchid = unsigned(0xffba55d3);
static const unsigned aclMediumPurple = unsigned(0xff9370db);
static const unsigned aclMediumSeaGreen = unsigned(0xff3cb371);
static const unsigned aclMediumSlateBlue = unsigned(0xff7b68ee);
static const unsigned aclMediumSpringGreen = unsigned(0xff00fa9a);
static const unsigned aclMediumTurquoise = unsigned(0xff48d1cc);
static const unsigned aclMediumVioletRed = unsigned(0xffc71585);
static const unsigned aclMidnightBlue = unsigned(0xff191970);
static const unsigned aclMintCream = unsigned(0xfff5fffa);
static const unsigned aclMistyRose = unsigned(0xffffe4e1);
static const unsigned aclMoccasin = unsigned(0xffffe4b5);
static const unsigned aclNavajoWhite = unsigned(0xffffdead);
static const unsigned aclNavy = unsigned(0xff000080);
static const unsigned aclOldLace = unsigned(0xfffdf5e6);
static const unsigned aclOlive = unsigned(0xff808000);
static const unsigned aclOliveDrab = unsigned(0xff6b8e23);
static const unsigned aclOrange = unsigned(0xffffa500);
static const unsigned aclOrangeRed = unsigned(0xffff4500);
static const unsigned aclOrchid = unsigned(0xffda70d6);
static const unsigned aclPaleGoldenrod = unsigned(0xffeee8aa);
static const unsigned aclPaleGreen = unsigned(0xff98fb98);
static const unsigned aclPaleTurquoise = unsigned(0xffafeeee);
static const unsigned aclPaleVioletRed = unsigned(0xffdb7093);
static const unsigned aclPapayaWhip = unsigned(0xffffefd5);
static const unsigned aclPeachPuff = unsigned(0xffffdab9);
static const unsigned aclPeru = unsigned(0xffcd853f);
static const unsigned aclPink = unsigned(0xffffc0cb);
static const unsigned aclPlum = unsigned(0xffdda0dd);
static const unsigned aclPowderBlue = unsigned(0xffb0e0e6);
static const unsigned aclPurple = unsigned(0xff800080);
static const unsigned aclRed = unsigned(0xffff0000);
static const unsigned aclRosyBrown = unsigned(0xffbc8f8f);
static const unsigned aclRoyalBlue = unsigned(0xff4169e1);
static const unsigned aclSaddleBrown = unsigned(0xff8b4513);
static const unsigned aclSalmon = unsigned(0xfffa8072);
static const unsigned aclSandyBrown = unsigned(0xfff4a460);
static const unsigned aclSeaGreen = unsigned(0xff2e8b57);
static const unsigned aclSeaShell = unsigned(0xfffff5ee);
static const unsigned aclSienna = unsigned(0xffa0522d);
static const unsigned aclSilver = unsigned(0xffc0c0c0);
static const unsigned aclSkyBlue = unsigned(0xff87ceeb);
static const unsigned aclSlateBlue = unsigned(0xff6a5acd);
static const unsigned aclSlateGray = unsigned(0xff708090);
static const unsigned aclSnow = unsigned(0xfffffafa);
static const unsigned aclSpringGreen = unsigned(0xff00ff7f);
static const unsigned aclSteelBlue = unsigned(0xff4682b4);
static const unsigned aclTan = unsigned(0xffd2b48c);
static const unsigned aclTeal = unsigned(0xff008080);
static const unsigned aclThistle = unsigned(0xffd8bfd8);
static const unsigned aclTomato = unsigned(0xffff6347);
static const int aclTransparent = int(0xffffff);
static const unsigned aclTurquoise = unsigned(0xff40e0d0);
static const unsigned aclViolet = unsigned(0xffee82ee);
static const unsigned aclWheat = unsigned(0xfff5deb3);
static const unsigned aclWhite = unsigned(0xffffffff);
static const unsigned aclWhiteSmoke = unsigned(0xfff5f5f5);
static const unsigned aclYellow = unsigned(0xffffff00);
static const unsigned aclYellowGreen = unsigned(0xff9acd32);
static const System::Int8 AlphaShift = System::Int8(0x18);
static const System::Int8 RedShift = System::Int8(0x10);
static const System::Int8 GreenShift = System::Int8(0x8);
static const System::Int8 BlueShift = System::Int8(0x0);
static const unsigned AlphaMask = unsigned(0xff000000);
static const int RedMask = int(0xff0000);
static const System::Word GreenMask = System::Word(0xff00);
static const System::Byte BlueMask = System::Byte(0xff);
static const System::Int8 GDIP_EMFPLUSFLAGS_DISPLAY = System::Int8(0x1);
extern DELPHI_PACKAGE GUID ImageFormatUndefined;
extern DELPHI_PACKAGE GUID ImageFormatMemoryBMP;
extern DELPHI_PACKAGE GUID ImageFormatBMP;
extern DELPHI_PACKAGE GUID ImageFormatEMF;
extern DELPHI_PACKAGE GUID ImageFormatWMF;
extern DELPHI_PACKAGE GUID ImageFormatJPEG;
extern DELPHI_PACKAGE GUID ImageFormatPNG;
extern DELPHI_PACKAGE GUID ImageFormatGIF;
extern DELPHI_PACKAGE GUID ImageFormatTIFF;
extern DELPHI_PACKAGE GUID ImageFormatEXIF;
extern DELPHI_PACKAGE GUID ImageFormatIcon;
extern DELPHI_PACKAGE GUID FrameDimensionTime;
extern DELPHI_PACKAGE GUID FrameDimensionResolution;
extern DELPHI_PACKAGE GUID FrameDimensionPage;
extern DELPHI_PACKAGE GUID FormatIDImageInformation;
extern DELPHI_PACKAGE GUID FormatIDJpegAppHeaders;
extern DELPHI_PACKAGE GUID EncoderCompression;
extern DELPHI_PACKAGE GUID EncoderColorDepth;
extern DELPHI_PACKAGE GUID EncoderScanMethod;
extern DELPHI_PACKAGE GUID EncoderVersion;
extern DELPHI_PACKAGE GUID EncoderRenderMethod;
extern DELPHI_PACKAGE GUID EncoderQuality;
extern DELPHI_PACKAGE GUID EncoderTransformation;
extern DELPHI_PACKAGE GUID EncoderLuminanceTable;
extern DELPHI_PACKAGE GUID EncoderChrominanceTable;
extern DELPHI_PACKAGE GUID EncoderSaveFlag;
extern DELPHI_PACKAGE GUID CodecIImageBytes;
static const System::Int8 ImageCodecFlagsEncoder = System::Int8(0x1);
static const System::Int8 ImageCodecFlagsDecoder = System::Int8(0x2);
static const System::Int8 ImageCodecFlagsSupportBitmap = System::Int8(0x4);
static const System::Int8 ImageCodecFlagsSupportVector = System::Int8(0x8);
static const System::Int8 ImageCodecFlagsSeekableEncode = System::Int8(0x10);
static const System::Int8 ImageCodecFlagsBlockingDecode = System::Int8(0x20);
static const int ImageCodecFlagsBuiltin = int(0x10000);
static const int ImageCodecFlagsSystem = int(0x20000);
static const int ImageCodecFlagsUser = int(0x40000);
static const System::Int8 ImageLockModeRead = System::Int8(0x1);
static const System::Int8 ImageLockModeWrite = System::Int8(0x2);
static const System::Int8 ImageLockModeUserInputBuf = System::Int8(0x4);
static const System::Int8 ImageFlagsNone = System::Int8(0x0);
static const System::Int8 ImageFlagsScalable = System::Int8(0x1);
static const System::Int8 ImageFlagsHasAlpha = System::Int8(0x2);
static const System::Int8 ImageFlagsHasTranslucent = System::Int8(0x4);
static const System::Int8 ImageFlagsPartiallyScalable = System::Int8(0x8);
static const System::Int8 ImageFlagsColorSpaceRGB = System::Int8(0x10);
static const System::Int8 ImageFlagsColorSpaceCMYK = System::Int8(0x20);
static const System::Int8 ImageFlagsColorSpaceGRAY = System::Int8(0x40);
static const System::Byte ImageFlagsColorSpaceYCBCR = System::Byte(0x80);
static const System::Word ImageFlagsColorSpaceYCCK = System::Word(0x100);
static const System::Word ImageFlagsHasRealDPI = System::Word(0x1000);
static const System::Word ImageFlagsHasRealPixelSize = System::Word(0x2000);
static const int ImageFlagsReadOnly = int(0x10000);
static const int ImageFlagsCaching = int(0x20000);
static const RotateFlipType RotateNoneFlipY = (RotateFlipType)(6);
static const RotateFlipType Rotate90FlipY = (RotateFlipType)(7);
static const RotateFlipType Rotate180FlipY = (RotateFlipType)(4);
static const RotateFlipType Rotate270FlipY = (RotateFlipType)(5);
static const RotateFlipType RotateNoneFlipXY = (RotateFlipType)(2);
static const RotateFlipType Rotate90FlipXY = (RotateFlipType)(3);
static const RotateFlipType Rotate180FlipXY = (RotateFlipType)(0);
static const RotateFlipType Rotate270FlipXY = (RotateFlipType)(1);
extern DELPHI_PACKAGE int PropertyTagTypeByte;
extern DELPHI_PACKAGE int PropertyTagTypeASCII;
extern DELPHI_PACKAGE int PropertyTagTypeShort;
extern DELPHI_PACKAGE int PropertyTagTypeLong;
extern DELPHI_PACKAGE int PropertyTagTypeRational;
extern DELPHI_PACKAGE int PropertyTagTypeUndefined;
extern DELPHI_PACKAGE int PropertyTagTypeSLONG;
extern DELPHI_PACKAGE int PropertyTagTypeSRational;
static const System::Word PropertyTagExifIFD = System::Word(0x8769);
static const System::Word PropertyTagGpsIFD = System::Word(0x8825);
static const System::Byte PropertyTagNewSubfileType = System::Byte(0xfe);
static const System::Byte PropertyTagSubfileType = System::Byte(0xff);
static const System::Word PropertyTagImageWidth = System::Word(0x100);
static const System::Word PropertyTagImageHeight = System::Word(0x101);
static const System::Word PropertyTagBitsPerSample = System::Word(0x102);
static const System::Word PropertyTagCompression = System::Word(0x103);
static const System::Word PropertyTagPhotometricInterp = System::Word(0x106);
static const System::Word PropertyTagThreshHolding = System::Word(0x107);
static const System::Word PropertyTagCellWidth = System::Word(0x108);
static const System::Word PropertyTagCellHeight = System::Word(0x109);
static const System::Word PropertyTagFillOrder = System::Word(0x10a);
static const System::Word PropertyTagDocumentName = System::Word(0x10d);
static const System::Word PropertyTagImageDescription = System::Word(0x10e);
static const System::Word PropertyTagEquipMake = System::Word(0x10f);
static const System::Word PropertyTagEquipModel = System::Word(0x110);
static const System::Word PropertyTagStripOffsets = System::Word(0x111);
static const System::Word PropertyTagOrientation = System::Word(0x112);
static const System::Word PropertyTagSamplesPerPixel = System::Word(0x115);
static const System::Word PropertyTagRowsPerStrip = System::Word(0x116);
static const System::Word PropertyTagStripBytesCount = System::Word(0x117);
static const System::Word PropertyTagMinSampleValue = System::Word(0x118);
static const System::Word PropertyTagMaxSampleValue = System::Word(0x119);
static const System::Word PropertyTagXResolution = System::Word(0x11a);
static const System::Word PropertyTagYResolution = System::Word(0x11b);
static const System::Word PropertyTagPlanarConfig = System::Word(0x11c);
static const System::Word PropertyTagPageName = System::Word(0x11d);
static const System::Word PropertyTagXPosition = System::Word(0x11e);
static const System::Word PropertyTagYPosition = System::Word(0x11f);
static const System::Word PropertyTagFreeOffset = System::Word(0x120);
static const System::Word PropertyTagFreeByteCounts = System::Word(0x121);
static const System::Word PropertyTagGrayResponseUnit = System::Word(0x122);
static const System::Word PropertyTagGrayResponseCurve = System::Word(0x123);
static const System::Word PropertyTagT4Option = System::Word(0x124);
static const System::Word PropertyTagT6Option = System::Word(0x125);
static const System::Word PropertyTagResolutionUnit = System::Word(0x128);
static const System::Word PropertyTagPageNumber = System::Word(0x129);
static const System::Word PropertyTagTransferFuncition = System::Word(0x12d);
static const System::Word PropertyTagSoftwareUsed = System::Word(0x131);
static const System::Word PropertyTagDateTime = System::Word(0x132);
static const System::Word PropertyTagArtist = System::Word(0x13b);
static const System::Word PropertyTagHostComputer = System::Word(0x13c);
static const System::Word PropertyTagPredictor = System::Word(0x13d);
static const System::Word PropertyTagWhitePoint = System::Word(0x13e);
static const System::Word PropertyTagPrimaryChromaticities = System::Word(0x13f);
static const System::Word PropertyTagColorMap = System::Word(0x140);
static const System::Word PropertyTagHalftoneHints = System::Word(0x141);
static const System::Word PropertyTagTileWidth = System::Word(0x142);
static const System::Word PropertyTagTileLength = System::Word(0x143);
static const System::Word PropertyTagTileOffset = System::Word(0x144);
static const System::Word PropertyTagTileByteCounts = System::Word(0x145);
static const System::Word PropertyTagInkSet = System::Word(0x14c);
static const System::Word PropertyTagInkNames = System::Word(0x14d);
static const System::Word PropertyTagNumberOfInks = System::Word(0x14e);
static const System::Word PropertyTagDotRange = System::Word(0x150);
static const System::Word PropertyTagTargetPrinter = System::Word(0x151);
static const System::Word PropertyTagExtraSamples = System::Word(0x152);
static const System::Word PropertyTagSampleFormat = System::Word(0x153);
static const System::Word PropertyTagSMinSampleValue = System::Word(0x154);
static const System::Word PropertyTagSMaxSampleValue = System::Word(0x155);
static const System::Word PropertyTagTransferRange = System::Word(0x156);
static const System::Word PropertyTagJPEGProc = System::Word(0x200);
static const System::Word PropertyTagJPEGInterFormat = System::Word(0x201);
static const System::Word PropertyTagJPEGInterLength = System::Word(0x202);
static const System::Word PropertyTagJPEGRestartInterval = System::Word(0x203);
static const System::Word PropertyTagJPEGLosslessPredictors = System::Word(0x205);
static const System::Word PropertyTagJPEGPointTransforms = System::Word(0x206);
static const System::Word PropertyTagJPEGQTables = System::Word(0x207);
static const System::Word PropertyTagJPEGDCTables = System::Word(0x208);
static const System::Word PropertyTagJPEGACTables = System::Word(0x209);
static const System::Word PropertyTagYCbCrCoefficients = System::Word(0x211);
static const System::Word PropertyTagYCbCrSubsampling = System::Word(0x212);
static const System::Word PropertyTagYCbCrPositioning = System::Word(0x213);
static const System::Word PropertyTagREFBlackWhite = System::Word(0x214);
static const System::Word PropertyTagICCProfile = System::Word(0x8773);
static const System::Word PropertyTagGamma = System::Word(0x301);
static const System::Word PropertyTagICCProfileDescriptor = System::Word(0x302);
static const System::Word PropertyTagSRGBRenderingIntent = System::Word(0x303);
static const System::Word PropertyTagImageTitle = System::Word(0x320);
static const System::Word PropertyTagCopyright = System::Word(0x8298);
static const System::Word PropertyTagResolutionXUnit = System::Word(0x5001);
static const System::Word PropertyTagResolutionYUnit = System::Word(0x5002);
static const System::Word PropertyTagResolutionXLengthUnit = System::Word(0x5003);
static const System::Word PropertyTagResolutionYLengthUnit = System::Word(0x5004);
static const System::Word PropertyTagPrintFlags = System::Word(0x5005);
static const System::Word PropertyTagPrintFlagsVersion = System::Word(0x5006);
static const System::Word PropertyTagPrintFlagsCrop = System::Word(0x5007);
static const System::Word PropertyTagPrintFlagsBleedWidth = System::Word(0x5008);
static const System::Word PropertyTagPrintFlagsBleedWidthScale = System::Word(0x5009);
static const System::Word PropertyTagHalftoneLPI = System::Word(0x500a);
static const System::Word PropertyTagHalftoneLPIUnit = System::Word(0x500b);
static const System::Word PropertyTagHalftoneDegree = System::Word(0x500c);
static const System::Word PropertyTagHalftoneShape = System::Word(0x500d);
static const System::Word PropertyTagHalftoneMisc = System::Word(0x500e);
static const System::Word PropertyTagHalftoneScreen = System::Word(0x500f);
static const System::Word PropertyTagJPEGQuality = System::Word(0x5010);
static const System::Word PropertyTagGridSize = System::Word(0x5011);
static const System::Word PropertyTagThumbnailFormat = System::Word(0x5012);
static const System::Word PropertyTagThumbnailWidth = System::Word(0x5013);
static const System::Word PropertyTagThumbnailHeight = System::Word(0x5014);
static const System::Word PropertyTagThumbnailColorDepth = System::Word(0x5015);
static const System::Word PropertyTagThumbnailPlanes = System::Word(0x5016);
static const System::Word PropertyTagThumbnailRawBytes = System::Word(0x5017);
static const System::Word PropertyTagThumbnailSize = System::Word(0x5018);
static const System::Word PropertyTagThumbnailCompressedSize = System::Word(0x5019);
static const System::Word PropertyTagColorTransferFunction = System::Word(0x501a);
static const System::Word PropertyTagThumbnailData = System::Word(0x501b);
static const System::Word PropertyTagThumbnailImageWidth = System::Word(0x5020);
static const System::Word PropertyTagThumbnailImageHeight = System::Word(0x5021);
static const System::Word PropertyTagThumbnailBitsPerSample = System::Word(0x5022);
static const System::Word PropertyTagThumbnailCompression = System::Word(0x5023);
static const System::Word PropertyTagThumbnailPhotometricInterp = System::Word(0x5024);
static const System::Word PropertyTagThumbnailImageDescription = System::Word(0x5025);
static const System::Word PropertyTagThumbnailEquipMake = System::Word(0x5026);
static const System::Word PropertyTagThumbnailEquipModel = System::Word(0x5027);
static const System::Word PropertyTagThumbnailStripOffsets = System::Word(0x5028);
static const System::Word PropertyTagThumbnailOrientation = System::Word(0x5029);
static const System::Word PropertyTagThumbnailSamplesPerPixel = System::Word(0x502a);
static const System::Word PropertyTagThumbnailRowsPerStrip = System::Word(0x502b);
static const System::Word PropertyTagThumbnailStripBytesCount = System::Word(0x502c);
static const System::Word PropertyTagThumbnailResolutionX = System::Word(0x502d);
static const System::Word PropertyTagThumbnailResolutionY = System::Word(0x502e);
static const System::Word PropertyTagThumbnailPlanarConfig = System::Word(0x502f);
static const System::Word PropertyTagThumbnailResolutionUnit = System::Word(0x5030);
static const System::Word PropertyTagThumbnailTransferFunction = System::Word(0x5031);
static const System::Word PropertyTagThumbnailSoftwareUsed = System::Word(0x5032);
static const System::Word PropertyTagThumbnailDateTime = System::Word(0x5033);
static const System::Word PropertyTagThumbnailArtist = System::Word(0x5034);
static const System::Word PropertyTagThumbnailWhitePoint = System::Word(0x5035);
static const System::Word PropertyTagThumbnailPrimaryChromaticities = System::Word(0x5036);
static const System::Word PropertyTagThumbnailYCbCrCoefficients = System::Word(0x5037);
static const System::Word PropertyTagThumbnailYCbCrSubsampling = System::Word(0x5038);
static const System::Word PropertyTagThumbnailYCbCrPositioning = System::Word(0x5039);
static const System::Word PropertyTagThumbnailRefBlackWhite = System::Word(0x503a);
static const System::Word PropertyTagThumbnailCopyRight = System::Word(0x503b);
static const System::Word PropertyTagLuminanceTable = System::Word(0x5090);
static const System::Word PropertyTagChrominanceTable = System::Word(0x5091);
static const System::Word PropertyTagFrameDelay = System::Word(0x5100);
static const System::Word PropertyTagLoopCount = System::Word(0x5101);
static const System::Word PropertyTagPixelUnit = System::Word(0x5110);
static const System::Word PropertyTagPixelPerUnitX = System::Word(0x5111);
static const System::Word PropertyTagPixelPerUnitY = System::Word(0x5112);
static const System::Word PropertyTagPaletteHistogram = System::Word(0x5113);
static const System::Word PropertyTagExifExposureTime = System::Word(0x829a);
static const System::Word PropertyTagExifFNumber = System::Word(0x829d);
static const System::Word PropertyTagExifExposureProg = System::Word(0x8822);
static const System::Word PropertyTagExifSpectralSense = System::Word(0x8824);
static const System::Word PropertyTagExifISOSpeed = System::Word(0x8827);
static const System::Word PropertyTagExifOECF = System::Word(0x8828);
static const System::Word PropertyTagExifVer = System::Word(0x9000);
static const System::Word PropertyTagExifDTOrig = System::Word(0x9003);
static const System::Word PropertyTagExifDTDigitized = System::Word(0x9004);
static const System::Word PropertyTagExifCompConfig = System::Word(0x9101);
static const System::Word PropertyTagExifCompBPP = System::Word(0x9102);
static const System::Word PropertyTagExifShutterSpeed = System::Word(0x9201);
static const System::Word PropertyTagExifAperture = System::Word(0x9202);
static const System::Word PropertyTagExifBrightness = System::Word(0x9203);
static const System::Word PropertyTagExifExposureBias = System::Word(0x9204);
static const System::Word PropertyTagExifMaxAperture = System::Word(0x9205);
static const System::Word PropertyTagExifSubjectDist = System::Word(0x9206);
static const System::Word PropertyTagExifMeteringMode = System::Word(0x9207);
static const System::Word PropertyTagExifLightSource = System::Word(0x9208);
static const System::Word PropertyTagExifFlash = System::Word(0x9209);
static const System::Word PropertyTagExifFocalLength = System::Word(0x920a);
static const System::Word PropertyTagExifMakerNote = System::Word(0x927c);
static const System::Word PropertyTagExifUserComment = System::Word(0x9286);
static const System::Word PropertyTagExifDTSubsec = System::Word(0x9290);
static const System::Word PropertyTagExifDTOrigSS = System::Word(0x9291);
static const System::Word PropertyTagExifDTDigSS = System::Word(0x9292);
static const System::Word PropertyTagExifFPXVer = System::Word(0xa000);
static const System::Word PropertyTagExifColorSpace = System::Word(0xa001);
static const System::Word PropertyTagExifPixXDim = System::Word(0xa002);
static const System::Word PropertyTagExifPixYDim = System::Word(0xa003);
static const System::Word PropertyTagExifRelatedWav = System::Word(0xa004);
static const System::Word PropertyTagExifInterop = System::Word(0xa005);
static const System::Word PropertyTagExifFlashEnergy = System::Word(0xa20b);
static const System::Word PropertyTagExifSpatialFR = System::Word(0xa20c);
static const System::Word PropertyTagExifFocalXRes = System::Word(0xa20e);
static const System::Word PropertyTagExifFocalYRes = System::Word(0xa20f);
static const System::Word PropertyTagExifFocalResUnit = System::Word(0xa210);
static const System::Word PropertyTagExifSubjectLoc = System::Word(0xa214);
static const System::Word PropertyTagExifExposureIndex = System::Word(0xa215);
static const System::Word PropertyTagExifSensingMethod = System::Word(0xa217);
static const System::Word PropertyTagExifFileSource = System::Word(0xa300);
static const System::Word PropertyTagExifSceneType = System::Word(0xa301);
static const System::Word PropertyTagExifCfaPattern = System::Word(0xa302);
static const System::Int8 PropertyTagGpsVer = System::Int8(0x0);
static const System::Int8 PropertyTagGpsLatitudeRef = System::Int8(0x1);
static const System::Int8 PropertyTagGpsLatitude = System::Int8(0x2);
static const System::Int8 PropertyTagGpsLongitudeRef = System::Int8(0x3);
static const System::Int8 PropertyTagGpsLongitude = System::Int8(0x4);
static const System::Int8 PropertyTagGpsAltitudeRef = System::Int8(0x5);
static const System::Int8 PropertyTagGpsAltitude = System::Int8(0x6);
static const System::Int8 PropertyTagGpsGpsTime = System::Int8(0x7);
static const System::Int8 PropertyTagGpsGpsSatellites = System::Int8(0x8);
static const System::Int8 PropertyTagGpsGpsStatus = System::Int8(0x9);
static const System::Int8 PropertyTagGpsGpsMeasureMode = System::Int8(0xa);
static const System::Int8 PropertyTagGpsGpsDop = System::Int8(0xb);
static const System::Int8 PropertyTagGpsSpeedRef = System::Int8(0xc);
static const System::Int8 PropertyTagGpsSpeed = System::Int8(0xd);
static const System::Int8 PropertyTagGpsTrackRef = System::Int8(0xe);
static const System::Int8 PropertyTagGpsTrack = System::Int8(0xf);
static const System::Int8 PropertyTagGpsImgDirRef = System::Int8(0x10);
static const System::Int8 PropertyTagGpsImgDir = System::Int8(0x11);
static const System::Int8 PropertyTagGpsMapDatum = System::Int8(0x12);
static const System::Int8 PropertyTagGpsDestLatRef = System::Int8(0x13);
static const System::Int8 PropertyTagGpsDestLat = System::Int8(0x14);
static const System::Int8 PropertyTagGpsDestLongRef = System::Int8(0x15);
static const System::Int8 PropertyTagGpsDestLong = System::Int8(0x16);
static const System::Int8 PropertyTagGpsDestBearRef = System::Int8(0x17);
static const System::Int8 PropertyTagGpsDestBear = System::Int8(0x18);
static const System::Int8 PropertyTagGpsDestDistRef = System::Int8(0x19);
static const System::Int8 PropertyTagGpsDestDist = System::Int8(0x1a);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePath)(FillMode brushMode, /* out */ void * &path);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePath2)(PGPPointF v1, System::PByte v2, int v3, FillMode v4, /* out */ void * &path);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePath2I)(PGPPoint v1, System::PByte v2, int v3, FillMode v4, /* out */ void * &path);
extern DELPHI_PACKAGE Status __stdcall (*GdipClonePath)(void * path, /* out */ void * &clonePath);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeletePath)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetPath)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPointCount)(void * path, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathTypes)(void * path, System::PByte types, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathPoints)(void * v1, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathPointsI)(void * v1, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathFillMode)(void * path, FillMode &fillmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathFillMode)(void * path, FillMode fillmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathData)(void * path, void * pathData);
extern DELPHI_PACKAGE Status __stdcall (*GdipStartPathFigure)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipClosePathFigure)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipClosePathFigures)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathMarker)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipClearPathMarkers)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipReversePath)(void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathLastPoint)(void * path, PGPPointF lastPoint);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathLine)(void * path, float x1, float y1, float x2, float y2);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathLine2)(void * path, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathArc)(void * path, float x, float y, float width, float height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathBezier)(void * path, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathBeziers)(void * path, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathCurve)(void * path, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathCurve2)(void * path, PGPPointF points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathCurve3)(void * path, PGPPointF points, int count, int offset, int numberOfSegments, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathClosedCurve)(void * path, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathClosedCurve2)(void * path, PGPPointF points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathRectangle)(void * path, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathRectangles)(void * path, PGPRectF rects, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathEllipse)(void * path, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathPie)(void * path, float x, float y, float width, float height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathPolygon)(void * path, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathPath)(void * path, void * addingPath, BOOL connect);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathString)(void * path, System::WideChar * string_, int length, void * family, int style, float emSize, PGPRectF layoutRect, void * format);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathStringI)(void * path, System::WideChar * string_, int length, void * family, int style, float emSize, PGPRect layoutRect, void * format);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathLineI)(void * path, int x1, int y1, int x2, int y2);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathLine2I)(void * path, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathArcI)(void * path, int x, int y, int width, int height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathBezierI)(void * path, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathBeziersI)(void * path, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathCurveI)(void * path, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathCurve2I)(void * path, PGPPoint points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathCurve3I)(void * path, PGPPoint points, int count, int offset, int numberOfSegments, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathClosedCurveI)(void * path, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathClosedCurve2I)(void * path, PGPPoint points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathRectangleI)(void * path, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathRectanglesI)(void * path, PGPRect rects, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathEllipseI)(void * path, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathPieI)(void * path, int x, int y, int width, int height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipAddPathPolygonI)(void * path, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFlattenPath)(void * path, void * matrix, float flatness);
extern DELPHI_PACKAGE Status __stdcall (*GdipWindingModeOutline)(void * path, void * matrix, float flatness);
extern DELPHI_PACKAGE Status __stdcall (*GdipWidenPath)(void * nativePath, void * pen, void * matrix, float flatness);
extern DELPHI_PACKAGE Status __stdcall (*GdipWarpPath)(void * path, void * matrix, PGPPointF points, int count, float srcx, float srcy, float srcwidth, float srcheight, WarpMode warpMode, float flatness);
extern DELPHI_PACKAGE Status __stdcall (*GdipTransformPath)(void * path, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathWorldBounds)(void * path, PGPRectF bounds, void * matrix, void * pen);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathWorldBoundsI)(void * path, PGPRect bounds, void * matrix, void * pen);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisiblePathPoint)(void * path, float x, float y, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisiblePathPointI)(void * path, int x, int y, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsOutlineVisiblePathPoint)(void * path, float x, float y, void * pen, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsOutlineVisiblePathPointI)(void * path, int x, int y, void * pen, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePathIter)(/* out */ void * &iterator, void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeletePathIter)(void * iterator);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterNextSubpath)(void * iterator, int &resultCount, int &startIndex, int &endIndex, /* out */ BOOL &isClosed);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterNextSubpathPath)(void * iterator, int &resultCount, void * path, /* out */ BOOL &isClosed);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterNextPathType)(void * iterator, int &resultCount, System::PByte pathType, int &startIndex, int &endIndex);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterNextMarker)(void * iterator, int &resultCount, int &startIndex, int &endIndex);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterNextMarkerPath)(void * iterator, int &resultCount, void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterGetCount)(void * iterator, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterGetSubpathCount)(void * iterator, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterIsValid)(void * iterator, /* out */ BOOL &valid);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterHasCurve)(void * iterator, /* out */ BOOL &hasCurve);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterRewind)(void * iterator);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterEnumerate)(void * iterator, int &resultCount, PGPPointF points, System::PByte types, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipPathIterCopyData)(void * iterator, int &resultCount, PGPPointF points, System::PByte types, int startIndex, int endIndex);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMatrix)(/* out */ void * &matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMatrix2)(float m11, float m12, float m21, float m22, float dx, float dy, /* out */ void * &matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMatrix3)(PGPRectF rect, PGPPointF dstplg, /* out */ void * &matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMatrix3I)(PGPRect rect, PGPPoint dstplg, /* out */ void * &matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneMatrix)(void * matrix, /* out */ void * &cloneMatrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteMatrix)(void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetMatrixElements)(void * matrix, float m11, float m12, float m21, float m22, float dx, float dy);
extern DELPHI_PACKAGE Status __stdcall (*GdipMultiplyMatrix)(void * matrix, void * matrix2, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateMatrix)(void * matrix, float offsetX, float offsetY, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipScaleMatrix)(void * matrix, float scaleX, float scaleY, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipRotateMatrix)(void * matrix, float angle, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipShearMatrix)(void * matrix, float shearX, float shearY, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipInvertMatrix)(void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipTransformMatrixPoints)(void * matrix, PGPPointF pts, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipTransformMatrixPointsI)(void * matrix, PGPPoint pts, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipVectorTransformMatrixPoints)(void * matrix, PGPPointF pts, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipVectorTransformMatrixPointsI)(void * matrix, PGPPoint pts, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMatrixElements)(void * matrix, Winapi::Windows::PSingle matrixOut);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsMatrixInvertible)(void * matrix, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsMatrixIdentity)(void * matrix, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsMatrixEqual)(void * matrix, void * matrix2, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateRegion)(/* out */ void * &region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateRegionRect)(PGPRectF rect, /* out */ void * &region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateRegionRectI)(PGPRect rect, /* out */ void * &region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateRegionPath)(void * path, /* out */ void * &region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateRegionRgnData)(System::PByte regionData, int size, /* out */ void * &region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateRegionHrgn)(HRGN hRgn, /* out */ void * &region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneRegion)(void * region, /* out */ void * &cloneRegion);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteRegion)(void * region);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetInfinite)(void * region);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetEmpty)(void * region);
extern DELPHI_PACKAGE Status __stdcall (*GdipCombineRegionRect)(void * region, PGPRectF rect, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipCombineRegionRectI)(void * region, PGPRect rect, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipCombineRegionPath)(void * region, void * path, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipCombineRegionRegion)(void * region, void * region2, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateRegion)(void * region, float dx, float dy);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateRegionI)(void * region, int dx, int dy);
extern DELPHI_PACKAGE Status __stdcall (*GdipTransformRegion)(void * region, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionBounds)(void * region, void * graphics, PGPRectF rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionBoundsI)(void * region, void * graphics, PGPRect rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionHRgn)(void * region, void * graphics, /* out */ HRGN &hRgn);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsEmptyRegion)(void * region, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsInfiniteRegion)(void * region, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsEqualRegion)(void * region, void * region2, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionDataSize)(void * region, /* out */ unsigned &bufferSize);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionData)(void * region, System::PByte buffer, unsigned bufferSize, PUINT sizeFilled);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleRegionPoint)(void * region, float x, float y, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleRegionPointI)(void * region, int x, int y, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleRegionRect)(void * region, float x, float y, float width, float height, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleRegionRectI)(void * region, int x, int y, int width, int height, void * graphics, /* out */ BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionScansCount)(void * region, /* out */ unsigned &count, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionScans)(void * region, PGPRectF rects, /* out */ int &count, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRegionScansI)(void * region, PGPRect rects, /* out */ int &count, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneBrush)(void * brush, /* out */ void * &cloneBrush);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteBrush)(void * brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetBrushType)(void * brush, /* out */ BrushType &type_);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateHatchBrush)(int hatchstyle, unsigned forecol, unsigned backcol, /* out */ void * &brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetHatchStyle)(void * brush, /* out */ HatchStyle &hatchstyle);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetHatchForegroundColor)(void * brush, /* out */ unsigned &forecol);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetHatchBackgroundColor)(void * brush, /* out */ unsigned &backcol);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateTexture)(void * image, WrapMode wrapmode, void * &texture);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateTexture2)(void * image, WrapMode wrapmode, float x, float y, float width, float height, /* out */ void * &texture);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateTextureIA)(void * image, void * imageAttributes, float x, float y, float width, float height, /* out */ void * &texture);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateTexture2I)(void * image, WrapMode wrapmode, int x, int y, int width, int height, /* out */ void * &texture);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateTextureIAI)(void * image, void * imageAttributes, int x, int y, int width, int height, /* out */ void * &texture);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetTextureTransform)(void * brush, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetTextureTransform)(void * brush, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetTextureTransform)(void * brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipMultiplyTextureTransform)(void * brush, void * matrix, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateTextureTransform)(void * brush, float dx, float dy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipScaleTextureTransform)(void * brush, float sx, float sy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipRotateTextureTransform)(void * brush, float angle, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetTextureWrapMode)(void * brush, WrapMode wrapmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetTextureWrapMode)(void * brush, WrapMode &wrapmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetTextureImage)(void * brush, /* out */ void * &image);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateSolidFill)(unsigned color, /* out */ void * &brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetSolidFillColor)(void * brush, unsigned color);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetSolidFillColor)(void * brush, /* out */ unsigned &color);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateLineBrush)(PGPPointF point1, PGPPointF point2, unsigned color1, unsigned color2, WrapMode wrapMode, /* out */ void * &lineGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateLineBrushI)(PGPPoint point1, PGPPoint point2, unsigned color1, unsigned color2, WrapMode wrapMode, /* out */ void * &lineGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateLineBrushFromRect)(PGPRectF rect, unsigned color1, unsigned color2, LinearGradientMode mode, WrapMode wrapMode, /* out */ void * &lineGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateLineBrushFromRectI)(PGPRect rect, unsigned color1, unsigned color2, LinearGradientMode mode, WrapMode wrapMode, /* out */ void * &lineGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateLineBrushFromRectWithAngle)(PGPRectF rect, unsigned color1, unsigned color2, float angle, BOOL isAngleScalable, WrapMode wrapMode, /* out */ void * &lineGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateLineBrushFromRectWithAngleI)(PGPRect rect, unsigned color1, unsigned color2, float angle, BOOL isAngleScalable, WrapMode wrapMode, /* out */ void * &lineGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineColors)(void * brush, unsigned color1, unsigned color2);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineColors)(void * brush, PARGB colors);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineRect)(void * brush, PGPRectF rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineRectI)(void * brush, PGPRect rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineGammaCorrection)(void * brush, BOOL useGammaCorrection);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineGammaCorrection)(void * brush, /* out */ BOOL &useGammaCorrection);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineBlendCount)(void * brush, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineBlend)(void * brush, Winapi::Windows::PSingle blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineBlend)(void * brush, Winapi::Windows::PSingle blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLinePresetBlendCount)(void * brush, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLinePresetBlend)(void * brush, PARGB blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLinePresetBlend)(void * brush, PARGB blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineSigmaBlend)(void * brush, float focus, float scale);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineLinearBlend)(void * brush, float focus, float scale);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineWrapMode)(void * brush, WrapMode wrapmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineWrapMode)(void * brush, /* out */ WrapMode &wrapmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineTransform)(void * brush, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetLineTransform)(void * brush, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetLineTransform)(void * brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipMultiplyLineTransform)(void * brush, void * matrix, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateLineTransform)(void * brush, float dx, float dy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipScaleLineTransform)(void * brush, float sx, float sy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipRotateLineTransform)(void * brush, float angle, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePathGradient)(PGPPointF points, int count, WrapMode wrapMode, /* out */ void * &polyGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePathGradientI)(PGPPoint points, int count, WrapMode wrapMode, /* out */ void * &polyGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePathGradientFromPath)(void * path, /* out */ void * &polyGradient);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientCenterColor)(void * brush, /* out */ unsigned &colors);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientCenterColor)(void * brush, unsigned colors);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientSurroundColorsWithCount)(void * brush, PARGB color, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientSurroundColorsWithCount)(void * brush, PARGB color, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientPath)(void * brush, void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientPath)(void * brush, void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientCenterPoint)(void * brush, PGPPointF points);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientCenterPointI)(void * brush, PGPPoint points);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientCenterPoint)(void * brush, PGPPointF points);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientCenterPointI)(void * brush, PGPPoint points);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientRect)(void * brush, PGPRectF rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientRectI)(void * brush, PGPRect rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientPointCount)(void * brush, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientSurroundColorCount)(void * brush, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientGammaCorrection)(void * brush, BOOL useGammaCorrection);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientGammaCorrection)(void * brush, BOOL &useGammaCorrection);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientBlendCount)(void * brush, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientBlend)(void * brush, Winapi::Windows::PSingle blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientBlend)(void * brush, Winapi::Windows::PSingle blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientPresetBlendCount)(void * brush, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientPresetBlend)(void * brush, PARGB blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientPresetBlend)(void * brush, PARGB blend, Winapi::Windows::PSingle positions, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientSigmaBlend)(void * brush, float focus, float scale);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientLinearBlend)(void * brush, float focus, float scale);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientWrapMode)(void * brush, WrapMode &wrapmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientWrapMode)(void * brush, WrapMode wrapmode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientTransform)(void * brush, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientTransform)(void * brush, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetPathGradientTransform)(void * brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipMultiplyPathGradientTransform)(void * brush, void * matrix, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslatePathGradientTransform)(void * brush, float dx, float dy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipScalePathGradientTransform)(void * brush, float sx, float sy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipRotatePathGradientTransform)(void * brush, float angle, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPathGradientFocusScales)(void * brush, float &xScale, float &yScale);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPathGradientFocusScales)(void * brush, float xScale, float yScale);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePen1)(unsigned color, float width, Unit_ unit_, /* out */ void * &pen);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreatePen2)(void * brush, float width, Unit_ unit_, /* out */ void * &pen);
extern DELPHI_PACKAGE Status __stdcall (*GdipClonePen)(void * pen, /* out */ void * &clonepen);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeletePen)(void * pen);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenWidth)(void * pen, float width);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenWidth)(void * pen, /* out */ float &width);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenUnit)(void * pen, Unit_ unit_);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenUnit)(void * pen, Unit_ &unit_);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenLineCap197819)(void * pen, int startCap, int endCap, int dashCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenStartCap)(void * pen, int startCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenEndCap)(void * pen, int endCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenDashCap197819)(void * pen, int dashCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenStartCap)(void * pen, /* out */ int &startCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenEndCap)(void * pen, /* out */ int &endCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenDashCap197819)(void * pen, /* out */ int &dashCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenLineJoin)(void * pen, LineJoin lineJoin);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenLineJoin)(void * pen, LineJoin &lineJoin);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenCustomStartCap)(void * pen, void * customCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenCustomStartCap)(void * pen, /* out */ void * &customCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenCustomEndCap)(void * pen, void * customCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenCustomEndCap)(void * pen, /* out */ void * &customCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenMiterLimit)(void * pen, float miterLimit);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenMiterLimit)(void * pen, /* out */ float &miterLimit);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenMode)(void * pen, PenAlignment penMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenMode)(void * pen, PenAlignment &penMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenTransform)(void * pen, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenTransform)(void * pen, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetPenTransform)(void * pen);
extern DELPHI_PACKAGE Status __stdcall (*GdipMultiplyPenTransform)(void * pen, void * matrix, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslatePenTransform)(void * pen, float dx, float dy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipScalePenTransform)(void * pen, float sx, float sy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipRotatePenTransform)(void * pen, float angle, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenColor)(void * pen, unsigned argb);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenColor)(void * pen, /* out */ unsigned &argb);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenBrushFill)(void * pen, void * brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenBrushFill)(void * pen, /* out */ void * &brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenFillType)(void * pen, /* out */ int &type_);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenDashStyle)(void * pen, /* out */ DashStyle &dashstyle);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenDashStyle)(void * pen, DashStyle dashstyle);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenDashOffset)(void * pen, /* out */ float &offset);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenDashOffset)(void * pen, float offset);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenDashCount)(void * pen, int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenDashArray)(void * pen, Winapi::Windows::PSingle dash, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenDashArray)(void * pen, Winapi::Windows::PSingle dash, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenCompoundCount)(void * pen, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPenCompoundArray)(void * pen, Winapi::Windows::PSingle dash, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPenCompoundArray)(void * pen, Winapi::Windows::PSingle dash, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateCustomLineCap)(void * fillPath, void * strokePath, int baseCap, float baseInset, /* out */ void * &customCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteCustomLineCap)(void * customCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneCustomLineCap)(void * customCap, /* out */ void * &clonedCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCustomLineCapType)(void * customCap, CustomLineCapType &capType);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCustomLineCapStrokeCaps)(void * customCap, int startCap, int endCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCustomLineCapStrokeCaps)(void * customCap, int &startCap, int &endCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCustomLineCapStrokeJoin)(void * customCap, LineJoin lineJoin);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCustomLineCapStrokeJoin)(void * customCap, LineJoin &lineJoin);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCustomLineCapBaseCap)(void * customCap, int baseCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCustomLineCapBaseCap)(void * customCap, int &baseCap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCustomLineCapBaseInset)(void * customCap, float inset);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCustomLineCapBaseInset)(void * customCap, float &inset);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCustomLineCapWidthScale)(void * customCap, float widthScale);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCustomLineCapWidthScale)(void * customCap, float &widthScale);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateAdjustableArrowCap)(float height, float width, BOOL isFilled, /* out */ void * &cap);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetAdjustableArrowCapHeight)(void * cap, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetAdjustableArrowCapHeight)(void * cap, float &height);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetAdjustableArrowCapWidth)(void * cap, float width);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetAdjustableArrowCapWidth)(void * cap, float &width);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetAdjustableArrowCapMiddleInset)(void * cap, float middleInset);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetAdjustableArrowCapMiddleInset)(void * cap, float &middleInset);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetAdjustableArrowCapFillState)(void * cap, BOOL fillState);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetAdjustableArrowCapFillState)(void * cap, BOOL &fillState);
extern DELPHI_PACKAGE Status __stdcall (*GdipLoadImageFromStream)(_di_IStream stream, /* out */ void * &image);
extern DELPHI_PACKAGE Status __stdcall (*GdipLoadImageFromFile)(System::WideChar * filename, /* out */ void * &image);
extern DELPHI_PACKAGE Status __stdcall (*GdipLoadImageFromStreamICM)(_di_IStream stream, /* out */ void * &image);
extern DELPHI_PACKAGE Status __stdcall (*GdipLoadImageFromFileICM)(System::WideChar * filename, /* out */ void * &image);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneImage)(void * image, /* out */ void * &cloneImage);
extern DELPHI_PACKAGE Status __stdcall (*GdipDisposeImage)(void * image);
extern DELPHI_PACKAGE Status __stdcall (*GdipSaveImageToFile)(void * image, System::WideChar * filename, System::PGUID clsidEncoder, PEncoderParameters encoderParams);
extern DELPHI_PACKAGE Status __stdcall (*GdipSaveImageToStream)(void * image, _di_IStream stream, System::PGUID clsidEncoder, PEncoderParameters encoderParams);
extern DELPHI_PACKAGE Status __stdcall (*GdipSaveAdd)(void * image, PEncoderParameters encoderParams);
extern DELPHI_PACKAGE Status __stdcall (*GdipSaveAddImage)(void * image, void * newImage, PEncoderParameters encoderParams);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageGraphicsContext)(void * image, /* out */ void * &graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageBounds)(void * image, PGPRectF srcRect, Unit_ &srcUnit);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageDimension)(void * image, float &width, float &height);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageType)(void * image, ImageType &type_);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageWidth)(void * image, unsigned &width);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageHeight)(void * image, unsigned &height);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageHorizontalResolution)(void * image, float &resolution);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageVerticalResolution)(void * image, float &resolution);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageFlags)(void * image, unsigned &flags);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageRawFormat)(void * image, System::PGUID format);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImagePixelFormat)(void * image, /* out */ int &format);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageThumbnail)(void * image, unsigned thumbWidth, unsigned thumbHeight, /* out */ void * &thumbImage, ImageAbort callback, void * callbackData);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetEncoderParameterListSize)(void * image, System::PGUID clsidEncoder, /* out */ unsigned &size);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetEncoderParameterList)(void * image, System::PGUID clsidEncoder, unsigned size, PEncoderParameters buffer);
extern DELPHI_PACKAGE Status __stdcall (*GdipImageGetFrameDimensionsCount)(void * image, unsigned &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipImageGetFrameDimensionsList)(void * image, System::PGUID dimensionIDs, unsigned count);
extern DELPHI_PACKAGE Status __stdcall (*GdipImageGetFrameCount)(void * image, System::PGUID dimensionID, unsigned &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipImageSelectActiveFrame)(void * image, System::PGUID dimensionID, unsigned frameIndex);
extern DELPHI_PACKAGE Status __stdcall (*GdipImageRotateFlip)(void * image, RotateFlipType rfType);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImagePalette)(void * image, PColorPalette palette, int size);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImagePalette)(void * image, PColorPalette palette);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImagePaletteSize)(void * image, int &size);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPropertyCount)(void * image, unsigned &numOfProperty);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPropertyIdList)(void * image, unsigned numOfProperty, Winapi::Activex::PPropID list);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPropertyItemSize)(void * image, unsigned propId, unsigned &size);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPropertyItem)(void * image, unsigned propId, unsigned propSize, PPropertyItem buffer);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPropertySize)(void * image, unsigned &totalBufferSize, unsigned &numProperties);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetAllPropertyItems)(void * image, unsigned totalBufferSize, unsigned numProperties, PPropertyItem allItems);
extern DELPHI_PACKAGE Status __stdcall (*GdipRemovePropertyItem)(void * image, unsigned propId);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPropertyItem)(void * image, PPropertyItem item);
extern DELPHI_PACKAGE Status __stdcall (*GdipImageForceValidation)(void * image);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromStream)(_di_IStream stream, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromFile)(System::WideChar * filename, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromStreamICM)(_di_IStream stream, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromFileICM)(System::WideChar * filename, void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromScan0)(int width, int height, int stride, int format, System::PByte scan0, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromGraphics)(int width, int height, void * target, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromGdiDib)(Winapi::Windows::PBitmapInfo gdiBitmapInfo, void * gdiBitmapData, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromHBITMAP)(HBITMAP hbm, HPALETTE hpal, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateHBITMAPFromBitmap)(void * bitmap, /* out */ HBITMAP &hbmReturn, unsigned background);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromHICON)(HICON hicon, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateHICONFromBitmap)(void * bitmap, /* out */ HICON &hbmReturn);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateBitmapFromResource)(NativeUInt hInstance, System::WideChar * lpBitmapName, /* out */ void * &bitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneBitmapArea)(float x, float y, float width, float height, int format, void * srcBitmap, /* out */ void * &dstBitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneBitmapAreaI)(int x, int y, int width, int height, int format, void * srcBitmap, /* out */ void * &dstBitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipBitmapLockBits)(void * bitmap, PGPRect rect, unsigned flags, int format, PBitmapData lockedBitmapData);
extern DELPHI_PACKAGE Status __stdcall (*GdipBitmapUnlockBits)(void * bitmap, PBitmapData lockedBitmapData);
extern DELPHI_PACKAGE Status __stdcall (*GdipBitmapGetPixel)(void * bitmap, int x, int y, unsigned &color);
extern DELPHI_PACKAGE Status __stdcall (*GdipBitmapSetPixel)(void * bitmap, int x, int y, unsigned color);
extern DELPHI_PACKAGE Status __stdcall (*GdipBitmapSetResolution)(void * bitmap, float xdpi, float ydpi);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateImageAttributes)(/* out */ void * &imageattr);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneImageAttributes)(void * imageattr, /* out */ void * &cloneImageattr);
extern DELPHI_PACKAGE Status __stdcall (*GdipDisposeImageAttributes)(void * imageattr);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesToIdentity)(void * imageattr, ColorAdjustType type_);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetImageAttributes)(void * imageattr, ColorAdjustType type_);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesColorMatrix)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, PColorMatrix colorMatrix, PColorMatrix grayMatrix, ColorMatrixFlags flags);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesThreshold)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, float threshold);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesGamma)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, float gamma);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesNoOp)(void * imageattr, ColorAdjustType type_, BOOL enableFlag);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesColorKeys)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, unsigned colorLow, unsigned colorHigh);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesOutputChannel)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, ColorChannelFlags channelFlags);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesOutputChannelColorProfile)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, System::WideChar * colorProfileFilename);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesRemapTable)(void * imageattr, ColorAdjustType type_, BOOL enableFlag, unsigned mapSize, PColorMap map);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesWrapMode)(void * imageAttr, WrapMode wrap, unsigned argb, BOOL clamp);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetImageAttributesICMMode)(void * imageAttr, BOOL on_);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageAttributesAdjustedPalette)(void * imageAttr, PColorPalette colorPalette, ColorAdjustType colorAdjustType);
extern DELPHI_PACKAGE Status __stdcall (*GdipFlush)(void * graphics, FlushIntention intention);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFromHDC)(HDC hdc, /* out */ void * &graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFromHDC2)(HDC hdc, NativeUInt hDevice, /* out */ void * &graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFromHWND)(HWND hwnd, /* out */ void * &graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFromHWNDICM)(HWND hwnd, /* out */ void * &graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteGraphics)(void * graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetDC)(void * graphics, HDC &hdc);
extern DELPHI_PACKAGE Status __stdcall (*GdipReleaseDC)(void * graphics, HDC hdc);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCompositingMode)(void * graphics, CompositingMode compositingMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCompositingMode)(void * graphics, CompositingMode &compositingMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetRenderingOrigin)(void * graphics, int x, int y);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetRenderingOrigin)(void * graphics, int &x, int &y);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetCompositingQuality)(void * graphics, int compositingQuality);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCompositingQuality)(void * graphics, int &compositingQuality);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetSmoothingMode)(void * graphics, int smoothingMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetSmoothingMode)(void * graphics, int &smoothingMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPixelOffsetMode)(void * graphics, int pixelOffsetMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPixelOffsetMode)(void * graphics, int &pixelOffsetMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetTextRenderingHint)(void * graphics, TextRenderingHint mode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetTextRenderingHint)(void * graphics, TextRenderingHint &mode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetTextContrast)(void * graphics, int contrast);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetTextContrast)(void * graphics, unsigned &contrast);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetInterpolationMode)(void * graphics, int interpolationMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetInterpolationMode)(void * graphics, int &interpolationMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetWorldTransform)(void * graphics, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetWorldTransform)(void * graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipMultiplyWorldTransform)(void * graphics, void * matrix, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateWorldTransform)(void * graphics, float dx, float dy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipScaleWorldTransform)(void * graphics, float sx, float sy, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipRotateWorldTransform)(void * graphics, float angle, MatrixOrder order);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetWorldTransform)(void * graphics, void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetPageTransform)(void * graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPageUnit)(void * graphics, Unit_ &unit_);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetPageScale)(void * graphics, float &scale);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPageUnit)(void * graphics, Unit_ unit_);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetPageScale)(void * graphics, float scale);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetDpiX)(void * graphics, float &dpi);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetDpiY)(void * graphics, float &dpi);
extern DELPHI_PACKAGE Status __stdcall (*GdipTransformPoints)(void * graphics, CoordinateSpace destSpace, CoordinateSpace srcSpace, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipTransformPointsI)(void * graphics, CoordinateSpace destSpace, CoordinateSpace srcSpace, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetNearestColor)(void * graphics, PARGB argb);
extern DELPHI_PACKAGE HPALETTE __stdcall (*GdipCreateHalftonePalette)(void);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawLine)(void * graphics, void * pen, float x1, float y1, float x2, float y2);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawLineI)(void * graphics, void * pen, int x1, int y1, int x2, int y2);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawLines)(void * graphics, void * pen, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawLinesI)(void * graphics, void * pen, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawArc)(void * graphics, void * pen, float x, float y, float width, float height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawArcI)(void * graphics, void * pen, int x, int y, int width, int height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawBezier)(void * graphics, void * pen, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawBezierI)(void * graphics, void * pen, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawBeziers)(void * graphics, void * pen, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawBeziersI)(void * graphics, void * pen, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawRectangle)(void * graphics, void * pen, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawRectangleI)(void * graphics, void * pen, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawRectangles)(void * graphics, void * pen, PGPRectF rects, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawRectanglesI)(void * graphics, void * pen, PGPRect rects, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawEllipse)(void * graphics, void * pen, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawEllipseI)(void * graphics, void * pen, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawPie)(void * graphics, void * pen, float x, float y, float width, float height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawPieI)(void * graphics, void * pen, int x, int y, int width, int height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawPolygon)(void * graphics, void * pen, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawPolygonI)(void * graphics, void * pen, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawPath)(void * graphics, void * pen, void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCurve)(void * graphics, void * pen, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCurveI)(void * graphics, void * pen, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCurve2)(void * graphics, void * pen, PGPPointF points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCurve2I)(void * graphics, void * pen, PGPPoint points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCurve3)(void * graphics, void * pen, PGPPointF points, int count, int offset, int numberOfSegments, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCurve3I)(void * graphics, void * pen, PGPPoint points, int count, int offset, int numberOfSegments, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawClosedCurve)(void * graphics, void * pen, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawClosedCurveI)(void * graphics, void * pen, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawClosedCurve2)(void * graphics, void * pen, PGPPointF points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawClosedCurve2I)(void * graphics, void * pen, PGPPoint points, int count, float tension);
extern DELPHI_PACKAGE Status __stdcall (*GdipGraphicsClear)(void * graphics, unsigned color);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillRectangle)(void * graphics, void * brush, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillRectangleI)(void * graphics, void * brush, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillRectangles)(void * graphics, void * brush, PGPRectF rects, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillRectanglesI)(void * graphics, void * brush, PGPRect rects, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPolygon)(void * graphics, void * brush, PGPPointF points, int count, FillMode fillMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPolygonI)(void * graphics, void * brush, PGPPoint points, int count, FillMode fillMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPolygon2)(void * graphics, void * brush, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPolygon2I)(void * graphics, void * brush, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillEllipse)(void * graphics, void * brush, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillEllipseI)(void * graphics, void * brush, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPie)(void * graphics, void * brush, float x, float y, float width, float height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPieI)(void * graphics, void * brush, int x, int y, int width, int height, float startAngle, float sweepAngle);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillPath)(void * graphics, void * brush, void * path);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillClosedCurve)(void * graphics, void * brush, PGPPointF points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillClosedCurveI)(void * graphics, void * brush, PGPPoint points, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillClosedCurve2)(void * graphics, void * brush, PGPPointF points, int count, float tension, FillMode fillMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillClosedCurve2I)(void * graphics, void * brush, PGPPoint points, int count, float tension, FillMode fillMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipFillRegion)(void * graphics, void * brush, void * region);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImage)(void * graphics, void * image, float x, float y);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImageI)(void * graphics, void * image, int x, int y);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImageRect)(void * graphics, void * image, float x, float y, float width, float height);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImageRectI)(void * graphics, void * image, int x, int y, int width, int height);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImagePoints)(void * graphics, void * image, PGPPointF dstpoints, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImagePointsI)(void * graphics, void * image, PGPPoint dstpoints, int count);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImagePointRect)(void * graphics, void * image, float x, float y, float srcx, float srcy, float srcwidth, float srcheight, Unit_ srcUnit);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImagePointRectI)(void * graphics, void * image, int x, int y, int srcx, int srcy, int srcwidth, int srcheight, Unit_ srcUnit);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImageRectRect)(void * graphics, void * image, float dstx, float dsty, float dstwidth, float dstheight, float srcx, float srcy, float srcwidth, float srcheight, Unit_ srcUnit, void * imageAttributes, ImageAbort callback, void * callbackData);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImageRectRectI)(void * graphics, void * image, int dstx, int dsty, int dstwidth, int dstheight, int srcx, int srcy, int srcwidth, int srcheight, Unit_ srcUnit, void * imageAttributes, ImageAbort callback, void * callbackData);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImagePointsRect)(void * graphics, void * image, PGPPointF points, int count, float srcx, float srcy, float srcwidth, float srcheight, Unit_ srcUnit, void * imageAttributes, ImageAbort callback, void * callbackData);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawImagePointsRectI)(void * graphics, void * image, PGPPoint points, int count, int srcx, int srcy, int srcwidth, int srcheight, Unit_ srcUnit, void * imageAttributes, ImageAbort callback, void * callbackData);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileDestPoint)(void * graphics, void * metafile, PGPPointF destPoint, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileDestPointI)(void * graphics, void * metafile, PGPPoint destPoint, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileDestRect)(void * graphics, void * metafile, PGPRectF destRect, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileDestRectI)(void * graphics, void * metafile, PGPRect destRect, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileDestPoints)(void * graphics, void * metafile, PGPPointF destPoints, int count, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileDestPointsI)(void * graphics, void * metafile, PGPPoint destPoints, int count, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileSrcRectDestPoint)(void * graphics, void * metafile, PGPPointF destPoint, PGPRectF srcRect, Unit_ srcUnit, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileSrcRectDestPointI)(void * graphics, void * metafile, PGPPoint destPoint, PGPRect srcRect, Unit_ srcUnit, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileSrcRectDestRect)(void * graphics, void * metafile, PGPRectF destRect, PGPRectF srcRect, Unit_ srcUnit, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileSrcRectDestRectI)(void * graphics, void * metafile, PGPRect destRect, PGPRect srcRect, Unit_ srcUnit, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileSrcRectDestPoints)(void * graphics, void * metafile, PGPPointF destPoints, int count, PGPRectF srcRect, Unit_ srcUnit, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipEnumerateMetafileSrcRectDestPointsI)(void * graphics, void * metafile, PGPPoint destPoints, int count, PGPRect srcRect, Unit_ srcUnit, EnumerateMetafileProc callback, void * callbackData, void * imageAttributes);
extern DELPHI_PACKAGE Status __stdcall (*GdipPlayMetafileRecord)(void * metafile, int recordType, unsigned flags, unsigned dataSize, System::PByte data);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetClipGraphics)(void * graphics, void * srcgraphics, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetClipRect)(void * graphics, float x, float y, float width, float height, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetClipRectI)(void * graphics, int x, int y, int width, int height, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetClipPath)(void * graphics, void * path, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetClipRegion)(void * graphics, void * region, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetClipHrgn)(void * graphics, HRGN hRgn, CombineMode combineMode);
extern DELPHI_PACKAGE Status __stdcall (*GdipResetClip)(void * graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateClip)(void * graphics, float dx, float dy);
extern DELPHI_PACKAGE Status __stdcall (*GdipTranslateClipI)(void * graphics, int dx, int dy);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetClip)(void * graphics, void * region);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetClipBounds)(void * graphics, PGPRectF rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetClipBoundsI)(void * graphics, PGPRect rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsClipEmpty)(void * graphics, PBOOL result);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetVisibleClipBounds)(void * graphics, PGPRectF rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetVisibleClipBoundsI)(void * graphics, PGPRect rect);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleClipEmpty)(void * graphics, BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisiblePoint)(void * graphics, float x, float y, BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisiblePointI)(void * graphics, int x, int y, BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleRect)(void * graphics, float x, float y, float width, float height, BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsVisibleRectI)(void * graphics, int x, int y, int width, int height, BOOL &result);
extern DELPHI_PACKAGE Status __stdcall (*GdipSaveGraphics)(void * graphics, unsigned &state);
extern DELPHI_PACKAGE Status __stdcall (*GdipRestoreGraphics)(void * graphics, unsigned state);
extern DELPHI_PACKAGE Status __stdcall (*GdipBeginContainer)(void * graphics, PGPRectF dstrect, PGPRectF srcrect, Unit_ unit_, unsigned &state);
extern DELPHI_PACKAGE Status __stdcall (*GdipBeginContainerI)(void * graphics, PGPRect dstrect, PGPRect srcrect, Unit_ unit_, unsigned &state);
extern DELPHI_PACKAGE Status __stdcall (*GdipBeginContainer2)(void * graphics, unsigned &state);
extern DELPHI_PACKAGE Status __stdcall (*GdipEndContainer)(void * graphics, unsigned state);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMetafileHeaderFromWmf)(HMETAFILE hWmf, PWmfPlaceableFileHeader wmfPlaceableFileHeader, void * header);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMetafileHeaderFromEmf)(HENHMETAFILE hEmf, void * header);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMetafileHeaderFromFile)(System::WideChar * filename, void * header);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMetafileHeaderFromStream)(_di_IStream stream, void * header);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMetafileHeaderFromMetafile)(void * metafile, void * header);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetHemfFromMetafile)(void * metafile, HENHMETAFILE &hEmf);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateStreamOnFile)(System::WideChar * filename, unsigned access, /* out */ _di_IStream &stream);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMetafileFromWmf)(HMETAFILE hWmf, BOOL deleteWmf, PWmfPlaceableFileHeader wmfPlaceableFileHeader, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMetafileFromEmf)(HENHMETAFILE hEmf, BOOL deleteEmf, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMetafileFromFile)(System::WideChar * file_, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMetafileFromWmfFile)(System::WideChar * file_, PWmfPlaceableFileHeader wmfPlaceableFileHeader, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateMetafileFromStream)(_di_IStream stream, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipRecordMetafile)(HDC referenceHdc, int type_, PGPRectF frameRect, int frameUnit, System::WideChar * description, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipRecordMetafileI)(HDC referenceHdc, int type_, PGPRect frameRect, int frameUnit, System::WideChar * description, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipRecordMetafileFileName)(System::WideChar * fileName, HDC referenceHdc, int type_, PGPRectF frameRect, int frameUnit, System::WideChar * description, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipRecordMetafileFileNameI)(System::WideChar * fileName, HDC referenceHdc, int type_, PGPRect frameRect, int frameUnit, System::WideChar * description, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipRecordMetafileStream)(_di_IStream stream, HDC referenceHdc, int type_, PGPRectF frameRect, int frameUnit, System::WideChar * description, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipRecordMetafileStreamI)(_di_IStream stream, HDC referenceHdc, int type_, PGPRect frameRect, int frameUnit, System::WideChar * description, /* out */ void * &metafile);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetMetafileDownLevelRasterizationLimit)(void * metafile, unsigned metafileRasterizationLimitDpi);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetMetafileDownLevelRasterizationLimit)(void * metafile, unsigned &metafileRasterizationLimitDpi);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageDecodersSize)(/* out */ unsigned &numDecoders, /* out */ unsigned &size);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageDecoders)(unsigned numDecoders, unsigned size, PImageCodecInfo decoders);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageEncodersSize)(/* out */ unsigned &numEncoders, /* out */ unsigned &size);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetImageEncoders)(unsigned numEncoders, unsigned size, PImageCodecInfo encoders);
extern DELPHI_PACKAGE Status __stdcall (*GdipComment)(void * graphics, unsigned sizeData, System::PByte data);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFontFamilyFromName)(System::WideChar * name, void * fontCollection, /* out */ void * &FontFamily);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteFontFamily)(void * FontFamily);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneFontFamily)(void * FontFamily, /* out */ void * &clonedFontFamily);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetGenericFontFamilySansSerif)(/* out */ void * &nativeFamily);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetGenericFontFamilySerif)(/* out */ void * &nativeFamily);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetGenericFontFamilyMonospace)(/* out */ void * &nativeFamily);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFamilyName)(void * family, System::WideChar * name, System::Word language);
extern DELPHI_PACKAGE Status __stdcall (*GdipIsStyleAvailable)(void * family, int style, BOOL &IsStyleAvailable);
extern DELPHI_PACKAGE Status __stdcall (*GdipFontCollectionEnumerable)(void * fontCollection, void * graphics, int &numFound);
extern DELPHI_PACKAGE Status __stdcall (*GdipFontCollectionEnumerate)(void * fontCollection, int numSought, void * *gpfamilies, const int gpfamilies_High, int &numFound, void * graphics);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetEmHeight)(void * family, int style, /* out */ UINT16 &EmHeight);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCellAscent)(void * family, int style, UINT16 &CellAscent);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetCellDescent)(void * family, int style, UINT16 &CellDescent);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLineSpacing)(void * family, int style, UINT16 &LineSpacing);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFontFromDC)(HDC hdc, /* out */ void * &font);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFontFromLogfontA)(HDC hdc, Winapi::Windows::PLogFontA logfont, /* out */ void * &font);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFontFromLogfontW)(HDC hdc, Winapi::Windows::PLogFontW logfont, /* out */ void * &font);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateFont)(void * fontFamily, float emSize, int style, int unit_, /* out */ void * &font);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneFont)(void * font, /* out */ void * &cloneFont);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteFont)(void * font);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFamily)(void * font, /* out */ void * &family);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontStyle)(void * font, int &style);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontSize)(void * font, float &size);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontUnit)(void * font, Unit_ &unit_);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontHeight)(void * font, void * graphics, float &height);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontHeightGivenDPI)(void * font, float dpi, float &height);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLogFontA)(void * font, void * graphics, tagLOGFONTA &logfontA);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetLogFontW)(void * font, void * graphics, tagLOGFONTW &logfontW);
extern DELPHI_PACKAGE Status __stdcall (*GdipNewInstalledFontCollection)(/* out */ void * &fontCollection);
extern DELPHI_PACKAGE Status __stdcall (*GdipNewPrivateFontCollection)(/* out */ void * &fontCollection);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeletePrivateFontCollection)(/* out */ void * &fontCollection);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontCollectionFamilyCount)(void * fontCollection, int &numFound);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetFontCollectionFamilyList)(void * fontCollection, int numSought, void * gpfamilies, int &numFound);
extern DELPHI_PACKAGE Status __stdcall (*GdipPrivateAddFontFile)(void * fontCollection, System::WideChar * filename);
extern DELPHI_PACKAGE Status __stdcall (*GdipPrivateAddMemoryFont)(void * fontCollection, void * memory, int length);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawString)(void * graphics, System::WideChar * string_, int length, void * font, PGPRectF layoutRect, void * stringFormat, void * brush);
extern DELPHI_PACKAGE Status __stdcall (*GdipMeasureString)(void * graphics, System::WideChar * string_, int length, void * font, PGPRectF layoutRect, void * stringFormat, PGPRectF boundingBox, System::PInteger codepointsFitted, System::PInteger linesFilled);
extern DELPHI_PACKAGE Status __stdcall (*GdipMeasureCharacterRanges)(void * graphics, System::WideChar * string_, int length, void * font, PGPRectF layoutRect, void * stringFormat, int regionCount, const void * regions);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawDriverString)(void * graphics, const PUINT16 text, int length, const void * font, const void * brush, const PGPPointF positions, int flags, const void * matrix);
extern DELPHI_PACKAGE Status __stdcall (*GdipMeasureDriverString)(void * graphics, PUINT16 text, int length, void * font, PGPPointF positions, int flags, void * matrix, PGPRectF boundingBox);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateStringFormat)(int formatAttributes, System::Word language, /* out */ void * &format);
extern DELPHI_PACKAGE Status __stdcall (*GdipStringFormatGetGenericDefault)(/* out */ void * &format);
extern DELPHI_PACKAGE Status __stdcall (*GdipStringFormatGetGenericTypographic)(/* out */ void * &format);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteStringFormat)(void * format);
extern DELPHI_PACKAGE Status __stdcall (*GdipCloneStringFormat)(void * format, /* out */ void * &newFormat);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatFlags)(void * format, int flags);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatFlags)(void * format, /* out */ int &flags);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatAlign)(void * format, StringAlignment align);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatAlign)(void * format, /* out */ StringAlignment &align);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatLineAlign)(void * format, StringAlignment align);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatLineAlign)(void * format, /* out */ StringAlignment &align);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatTrimming)(void * format, StringTrimming trimming);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatTrimming)(void * format, /* out */ StringTrimming &trimming);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatHotkeyPrefix)(void * format, int hotkeyPrefix);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatHotkeyPrefix)(void * format, /* out */ int &hotkeyPrefix);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatTabStops)(void * format, float firstTabOffset, int count, Winapi::Windows::PSingle tabStops);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatTabStops)(void * format, int count, Winapi::Windows::PSingle firstTabOffset, Winapi::Windows::PSingle tabStops);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatTabStopCount)(void * format, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatDigitSubstitution)(void * format, System::Word language, StringDigitSubstitute substitute);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatDigitSubstitution)(void * format, PUINT language, PStringDigitSubstitute substitute);
extern DELPHI_PACKAGE Status __stdcall (*GdipGetStringFormatMeasurableCharacterRangeCount)(void * format, /* out */ int &count);
extern DELPHI_PACKAGE Status __stdcall (*GdipSetStringFormatMeasurableCharacterRanges)(void * format, int rangeCount, PCharacterRange ranges);
extern DELPHI_PACKAGE Status __stdcall (*GdipCreateCachedBitmap)(void * bitmap, void * graphics, /* out */ void * &cachedBitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipDeleteCachedBitmap)(void * cachedBitmap);
extern DELPHI_PACKAGE Status __stdcall (*GdipDrawCachedBitmap)(void * graphics, void * cachedBitmap, int x, int y);
extern DELPHI_PACKAGE unsigned __stdcall (*GdipEmfToWmfBits)(HENHMETAFILE hemf, unsigned cbData16, System::PByte pData16, int iMapMode, int eFlags);
extern DELPHI_PACKAGE unsigned GdipLibrary;
extern DELPHI_PACKAGE BOOL __fastcall ObjectTypeIsValid(ObjectType type_);
extern DELPHI_PACKAGE int __fastcall GDIP_WMF_RECORD_TO_EMFPLUS(int n);
extern DELPHI_PACKAGE int __fastcall GDIP_EMFPLUS_RECORD_TO_WMF(int n);
extern DELPHI_PACKAGE BOOL __fastcall GDIP_IS_WMF_RECORDTYPE(int n);
extern DELPHI_PACKAGE TGPPoint __fastcall MakePoint(int X, int Y)/* overload */;
extern DELPHI_PACKAGE TGPPointF __fastcall MakePoint(float X, float Y)/* overload */;
extern DELPHI_PACKAGE TGPSizeF __fastcall MakeSize(float Width, float Height)/* overload */;
extern DELPHI_PACKAGE TGPSize __fastcall MakeSize(int Width, int Height)/* overload */;
extern DELPHI_PACKAGE TCharacterRange __fastcall MakeCharacterRange(int First, int Length);
extern DELPHI_PACKAGE TGPRectF __fastcall MakeRect(float x, float y, float width, float height)/* overload */;
extern DELPHI_PACKAGE TGPRectF __fastcall MakeRect(const TGPPointF &location, const TGPSizeF &size)/* overload */;
extern DELPHI_PACKAGE TGPRect __fastcall MakeRect(int x, int y, int width, int height)/* overload */;
extern DELPHI_PACKAGE TGPRect __fastcall MakeRect(const TGPPoint &location, const TGPSize &size)/* overload */;
extern DELPHI_PACKAGE TGPRect __fastcall MakeRect(const System::Types::TRect &Rect)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall GetPixelFormatSize(int pixfmt);
extern DELPHI_PACKAGE BOOL __fastcall IsIndexedPixelFormat(int pixfmt);
extern DELPHI_PACKAGE BOOL __fastcall IsAlphaPixelFormat(int pixfmt);
extern DELPHI_PACKAGE BOOL __fastcall IsExtendedPixelFormat(int pixfmt);
extern DELPHI_PACKAGE BOOL __fastcall IsCanonicalPixelFormat(int pixfmt);
extern DELPHI_PACKAGE unsigned __fastcall MakeColor(System::Byte r, System::Byte g, System::Byte b)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall MakeColor(System::Byte a, System::Byte r, System::Byte g, System::Byte b)/* overload */;
extern DELPHI_PACKAGE System::Byte __fastcall GetAlpha(unsigned color);
extern DELPHI_PACKAGE System::Byte __fastcall GetRed(unsigned color);
extern DELPHI_PACKAGE System::Byte __fastcall GetGreen(unsigned color);
extern DELPHI_PACKAGE System::Byte __fastcall GetBlue(unsigned color);
extern DELPHI_PACKAGE unsigned __fastcall ColorRefToARGB(unsigned rgb);
extern DELPHI_PACKAGE unsigned __fastcall ARGBToColorRef(unsigned Color);
}	/* namespace Dgrgdipapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGRGDIPAPI)
using namespace Dgrgdipapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgrgdipapiHPP
