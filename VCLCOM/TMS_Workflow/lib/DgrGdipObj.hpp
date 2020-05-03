// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DgrGdipObj.pas' rev: 28.00 (Windows)

#ifndef DgrgdipobjHPP
#define DgrgdipobjHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.ActiveX.hpp>	// Pascal unit
#include <DgrGdipApi.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dgrgdipobj
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TGPRegion;
class DELPHICLASS TGPGraphicsPath;
class DELPHICLASS TGPMatrix;
class DELPHICLASS TGPGraphics;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPRegion : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeRegion;
	Dgrgdipapi::Status lastResult;
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	void __fastcall SetNativeRegion(void * nativeRegion);
	__fastcall TGPRegion(void * nativeRegion)/* overload */;
	
public:
	__fastcall TGPRegion(void)/* overload */;
	__fastcall TGPRegion(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	__fastcall TGPRegion(const Dgrgdipapi::TGPRect &rect)/* overload */;
	__fastcall TGPRegion(TGPGraphicsPath* path)/* overload */;
	__fastcall TGPRegion(System::PByte regionData, int size)/* overload */;
	__fastcall TGPRegion(HRGN hRgn, int Dummy1, int Dummy2)/* overload */;
	TGPRegion* __fastcall FromHRGN(HRGN hRgn);
	__fastcall virtual ~TGPRegion(void);
	TGPRegion* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall MakeInfinite(void);
	Dgrgdipapi::Status __fastcall MakeEmpty(void);
	unsigned __fastcall GetDataSize(void);
	Dgrgdipapi::Status __fastcall GetData(System::PByte buffer, unsigned bufferSize, PUINT sizeFilled = (PUINT)(0x0));
	Dgrgdipapi::Status __fastcall Intersect(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Intersect(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Intersect(TGPGraphicsPath* path)/* overload */;
	Dgrgdipapi::Status __fastcall Intersect(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall Union(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Union(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Union(TGPGraphicsPath* path)/* overload */;
	Dgrgdipapi::Status __fastcall Union(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall Xor_(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Xor_(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Xor_(TGPGraphicsPath* path)/* overload */;
	Dgrgdipapi::Status __fastcall Xor_(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall Exclude(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Exclude(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Exclude(TGPGraphicsPath* path)/* overload */;
	Dgrgdipapi::Status __fastcall Exclude(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall Complement(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Complement(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall Complement(TGPGraphicsPath* path)/* overload */;
	Dgrgdipapi::Status __fastcall Complement(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall Translate(float dx, float dy)/* overload */;
	Dgrgdipapi::Status __fastcall Translate(int dx, int dy)/* overload */;
	Dgrgdipapi::Status __fastcall Transform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetBounds(/* out */ Dgrgdipapi::TGPRect &rect, TGPGraphics* g)/* overload */;
	Dgrgdipapi::Status __fastcall GetBounds(/* out */ Dgrgdipapi::TGPRectF &rect, TGPGraphics* g)/* overload */;
	HRGN __fastcall GetHRGN(TGPGraphics* g);
	BOOL __fastcall IsEmpty(TGPGraphics* g);
	BOOL __fastcall IsInfinite(TGPGraphics* g);
	BOOL __fastcall IsVisible(int x, int y, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPPoint &point, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(float x, float y, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPPointF &point, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(int x, int y, int width, int height, TGPGraphics* g)/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPRect &rect, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(float x, float y, float width, float height, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPRectF &rect, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsEqual(TGPRegion* region, TGPGraphics* g);
	unsigned __fastcall GetRegionScansCount(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetRegionScans(TGPMatrix* matrix, Dgrgdipapi::PGPRectF rects, /* out */ int &count)/* overload */;
	Dgrgdipapi::Status __fastcall GetRegionScans(TGPMatrix* matrix, Dgrgdipapi::PGPRect rects, /* out */ int &count)/* overload */;
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPFontFamily;
class DELPHICLASS TGPFontCollection;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPFontFamily : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeFamily;
	Dgrgdipapi::Status lastResult;
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPFontFamily(void * nativeOrig, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPFontFamily(void)/* overload */;
	__fastcall TGPFontFamily(System::WideString name, TGPFontCollection* fontCollection)/* overload */;
	__fastcall virtual ~TGPFontFamily(void);
	__classmethod TGPFontFamily* __fastcall GenericSansSerif();
	__classmethod TGPFontFamily* __fastcall GenericSerif();
	__classmethod TGPFontFamily* __fastcall GenericMonospace();
	Dgrgdipapi::Status __fastcall GetFamilyName(/* out */ System::UnicodeString &name, System::Word language = (System::Word)(0x0));
	TGPFontFamily* __fastcall Clone(void);
	BOOL __fastcall IsAvailable(void);
	BOOL __fastcall IsStyleAvailable(int style);
	Dgrgdipapi::UINT16 __fastcall GetEmHeight(int style);
	Dgrgdipapi::UINT16 __fastcall GetCellAscent(int style);
	Dgrgdipapi::UINT16 __fastcall GetCellDescent(int style);
	Dgrgdipapi::UINT16 __fastcall GetLineSpacing(int style);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPFontCollection : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeFontCollection;
	Dgrgdipapi::Status lastResult;
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	
public:
	__fastcall TGPFontCollection(void);
	__fastcall virtual ~TGPFontCollection(void);
	int __fastcall GetFamilyCount(void);
	Dgrgdipapi::Status __fastcall GetFamilies(int numSought, /* out */ TGPFontFamily* *gpfamilies, const int gpfamilies_High, /* out */ int &numFound);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPInstalledFontCollection;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPInstalledFontCollection : public TGPFontCollection
{
	typedef TGPFontCollection inherited;
	
public:
	__fastcall TGPInstalledFontCollection(void);
	__fastcall virtual ~TGPInstalledFontCollection(void);
};

#pragma pack(pop)

class DELPHICLASS TGPPrivateFontCollection;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPPrivateFontCollection : public TGPFontCollection
{
	typedef TGPFontCollection inherited;
	
public:
	__fastcall TGPPrivateFontCollection(void);
	__fastcall virtual ~TGPPrivateFontCollection(void);
	Dgrgdipapi::Status __fastcall AddFontFile(System::WideString filename);
	Dgrgdipapi::Status __fastcall AddMemoryFont(void * memory, int length);
};

#pragma pack(pop)

class DELPHICLASS TGPFont;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPFont : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeFont;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeFont(void * Font);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPFont(void * font, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPFont(HDC hdc)/* overload */;
	__fastcall TGPFont(HDC hdc, Winapi::Windows::PLogFontA logfont)/* overload */;
	__fastcall TGPFont(HDC hdc, Winapi::Windows::PLogFontW logfont)/* overload */;
	__fastcall TGPFont(HDC hdc, HFONT hfont)/* overload */;
	__fastcall TGPFont(TGPFontFamily* family, float emSize, int style, Dgrgdipapi::Unit_ unit_)/* overload */;
	__fastcall TGPFont(System::WideString familyName, float emSize, int style, Dgrgdipapi::Unit_ unit_, TGPFontCollection* fontCollection)/* overload */;
	Dgrgdipapi::Status __fastcall GetLogFontA(TGPGraphics* g, /* out */ tagLOGFONTA &logfontA);
	Dgrgdipapi::Status __fastcall GetLogFontW(TGPGraphics* g, /* out */ tagLOGFONTW &logfontW);
	TGPFont* __fastcall Clone(void);
	__fastcall virtual ~TGPFont(void);
	BOOL __fastcall IsAvailable(void);
	int __fastcall GetStyle(void);
	float __fastcall GetSize(void);
	Dgrgdipapi::Unit_ __fastcall GetUnit(void);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
	float __fastcall GetHeight(TGPGraphics* graphics)/* overload */;
	float __fastcall GetHeight(float dpi)/* overload */;
	Dgrgdipapi::Status __fastcall GetFamily(TGPFontFamily* family);
};

#pragma pack(pop)

class DELPHICLASS TGPImage;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPImage : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeImage;
	Dgrgdipapi::Status lastResult;
	Dgrgdipapi::Status loadStatus;
	void __fastcall SetNativeImage(void * nativeImage);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPImage(void * nativeImage, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPImage(System::WideString filename, BOOL useEmbeddedColorManagement)/* overload */;
	__fastcall TGPImage(_di_IStream stream, BOOL useEmbeddedColorManagement)/* overload */;
	TGPImage* __fastcall FromFile(System::WideString filename, BOOL useEmbeddedColorManagement = false);
	TGPImage* __fastcall FromStream(_di_IStream stream, BOOL useEmbeddedColorManagement = false);
	__fastcall virtual ~TGPImage(void);
	TGPImage* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall Save(System::WideString filename, const GUID &clsidEncoder, Dgrgdipapi::PEncoderParameters encoderParams = (Dgrgdipapi::PEncoderParameters)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall Save(_di_IStream stream, const GUID &clsidEncoder, Dgrgdipapi::PEncoderParameters encoderParams = (Dgrgdipapi::PEncoderParameters)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SaveAdd(Dgrgdipapi::PEncoderParameters encoderParams)/* overload */;
	Dgrgdipapi::Status __fastcall SaveAdd(TGPImage* newImage, Dgrgdipapi::PEncoderParameters encoderParams)/* overload */;
	Dgrgdipapi::ImageType __fastcall GetType(void);
	Dgrgdipapi::Status __fastcall GetPhysicalDimension(/* out */ Dgrgdipapi::TGPSizeF &size);
	Dgrgdipapi::Status __fastcall GetBounds(/* out */ Dgrgdipapi::TGPRectF &srcRect, /* out */ Dgrgdipapi::Unit_ &srcUnit);
	unsigned __fastcall GetWidth(void);
	unsigned __fastcall GetHeight(void);
	float __fastcall GetHorizontalResolution(void);
	float __fastcall GetVerticalResolution(void);
	unsigned __fastcall GetFlags(void);
	Dgrgdipapi::Status __fastcall GetRawFormat(/* out */ GUID &format);
	int __fastcall GetPixelFormat(void);
	int __fastcall GetPaletteSize(void);
	Dgrgdipapi::Status __fastcall GetPalette(Dgrgdipapi::PColorPalette palette, int size);
	Dgrgdipapi::Status __fastcall SetPalette(Dgrgdipapi::PColorPalette palette);
	TGPImage* __fastcall GetThumbnailImage(unsigned thumbWidth, unsigned thumbHeight, Dgrgdipapi::ImageAbort callback = 0x0, void * callbackData = (void *)(0x0));
	unsigned __fastcall GetFrameDimensionsCount(void);
	Dgrgdipapi::Status __fastcall GetFrameDimensionsList(System::PGUID dimensionIDs, unsigned count);
	unsigned __fastcall GetFrameCount(const GUID &dimensionID);
	Dgrgdipapi::Status __fastcall SelectActiveFrame(const GUID &dimensionID, unsigned frameIndex);
	Dgrgdipapi::Status __fastcall RotateFlip(Dgrgdipapi::RotateFlipType rotateFlipType);
	unsigned __fastcall GetPropertyCount(void);
	Dgrgdipapi::Status __fastcall GetPropertyIdList(unsigned numOfProperty, Winapi::Activex::PPropID list);
	unsigned __fastcall GetPropertyItemSize(unsigned propId);
	Dgrgdipapi::Status __fastcall GetPropertyItem(unsigned propId, unsigned propSize, Dgrgdipapi::PPropertyItem buffer);
	Dgrgdipapi::Status __fastcall GetPropertySize(/* out */ unsigned &totalBufferSize, /* out */ unsigned &numProperties);
	Dgrgdipapi::Status __fastcall GetAllPropertyItems(unsigned totalBufferSize, unsigned numProperties, Dgrgdipapi::PPropertyItem allItems);
	Dgrgdipapi::Status __fastcall RemovePropertyItem(unsigned propId);
	Dgrgdipapi::Status __fastcall SetPropertyItem(const Dgrgdipapi::PropertyItem &item);
	unsigned __fastcall GetEncoderParameterListSize(const GUID &clsidEncoder);
	Dgrgdipapi::Status __fastcall GetEncoderParameterList(const GUID &clsidEncoder, unsigned size, Dgrgdipapi::PEncoderParameters buffer);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPBitmap;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPBitmap : public TGPImage
{
	typedef TGPImage inherited;
	
protected:
	__fastcall TGPBitmap(void * nativeBitmap)/* overload */;
	
public:
	__fastcall TGPBitmap(System::WideString filename, BOOL useEmbeddedColorManagement)/* overload */;
	__fastcall TGPBitmap(_di_IStream stream, BOOL useEmbeddedColorManagement)/* overload */;
	HIDESBASE TGPBitmap* __fastcall FromFile(System::WideString filename, BOOL useEmbeddedColorManagement = false);
	HIDESBASE TGPBitmap* __fastcall FromStream(_di_IStream stream, BOOL useEmbeddedColorManagement = false);
	__fastcall TGPBitmap(int width, int height, int stride, int format, System::PByte scan0)/* overload */;
	__fastcall TGPBitmap(int width, int height, int format)/* overload */;
	__fastcall TGPBitmap(int width, int height, TGPGraphics* target)/* overload */;
	HIDESBASE TGPBitmap* __fastcall Clone(const Dgrgdipapi::TGPRect &rect, int format)/* overload */;
	HIDESBASE TGPBitmap* __fastcall Clone(int x, int y, int width, int height, int format)/* overload */;
	HIDESBASE TGPBitmap* __fastcall Clone(const Dgrgdipapi::TGPRectF &rect, int format)/* overload */;
	HIDESBASE TGPBitmap* __fastcall Clone(float x, float y, float width, float height, int format)/* overload */;
	Dgrgdipapi::Status __fastcall LockBits(const Dgrgdipapi::TGPRect &rect, unsigned flags, int format, /* out */ Dgrgdipapi::BitmapData &lockedBitmapData);
	Dgrgdipapi::Status __fastcall UnlockBits(Dgrgdipapi::BitmapData &lockedBitmapData);
	Dgrgdipapi::Status __fastcall GetPixel(int x, int y, /* out */ unsigned &color);
	Dgrgdipapi::Status __fastcall SetPixel(int x, int y, unsigned color);
	Dgrgdipapi::Status __fastcall SetResolution(float xdpi, float ydpi);
	__fastcall TGPBitmap(tagBITMAPINFO &gdiBitmapInfo, void * gdiBitmapData)/* overload */;
	__fastcall TGPBitmap(HBITMAP hbm, HPALETTE hpal)/* overload */;
	__fastcall TGPBitmap(HICON hicon, int Dummy1)/* overload */;
	__fastcall TGPBitmap(NativeUInt hInstance, System::WideString bitmapName)/* overload */;
	TGPBitmap* __fastcall FromBITMAPINFO(tagBITMAPINFO &gdiBitmapInfo, void * gdiBitmapData);
	TGPBitmap* __fastcall FromHBITMAP(HBITMAP hbm, HPALETTE hpal);
	TGPBitmap* __fastcall FromHICON(HICON hicon);
	TGPBitmap* __fastcall FromResource(NativeUInt hInstance, System::WideString bitmapName);
	Dgrgdipapi::Status __fastcall GetHBITMAP(unsigned colorBackground, /* out */ HBITMAP &hbmReturn);
	Dgrgdipapi::Status __fastcall GetHICON(/* out */ HICON &hicon);
protected:
	/* TGPImage.Create */ inline __fastcall TGPBitmap(void * nativeImage, Dgrgdipapi::Status status)/* overload */ : TGPImage(nativeImage, status) { }
	
public:
	/* TGPImage.Destroy */ inline __fastcall virtual ~TGPBitmap(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGPCustomLineCap;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPCustomLineCap : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeCap;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeCap(void * nativeCap);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPCustomLineCap(void * nativeCap, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPCustomLineCap(void)/* overload */;
	__fastcall TGPCustomLineCap(TGPGraphicsPath* fillPath, TGPGraphicsPath* strokePath, int baseCap, float baseInset)/* overload */;
	__fastcall virtual ~TGPCustomLineCap(void);
	TGPCustomLineCap* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall SetStrokeCap(int strokeCap);
	Dgrgdipapi::Status __fastcall SetStrokeCaps(int startCap, int endCap);
	Dgrgdipapi::Status __fastcall GetStrokeCaps(/* out */ int &startCap, /* out */ int &endCap);
	Dgrgdipapi::Status __fastcall SetStrokeJoin(Dgrgdipapi::LineJoin lineJoin);
	Dgrgdipapi::LineJoin __fastcall GetStrokeJoin(void);
	Dgrgdipapi::Status __fastcall SetBaseCap(int baseCap);
	int __fastcall GetBaseCap(void);
	Dgrgdipapi::Status __fastcall SetBaseInset(float inset);
	float __fastcall GetBaseInset(void);
	Dgrgdipapi::Status __fastcall SetWidthScale(float widthScale);
	float __fastcall GetWidthScale(void);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPCachedBitmap;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPCachedBitmap : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeCachedBitmap;
	Dgrgdipapi::Status lastResult;
	
public:
	__fastcall TGPCachedBitmap(TGPBitmap* bitmap, TGPGraphics* graphics);
	__fastcall virtual ~TGPCachedBitmap(void);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPImageAttributes;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPImageAttributes : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeImageAttr;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeImageAttr(void * nativeImageAttr);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPImageAttributes(void * imageAttr, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPImageAttributes(void)/* overload */;
	__fastcall virtual ~TGPImageAttributes(void);
	TGPImageAttributes* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall SetToIdentity(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall Reset(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetColorMatrix(const Dgrgdipapi::ColorMatrix &colorMatrix, Dgrgdipapi::ColorMatrixFlags mode = (Dgrgdipapi::ColorMatrixFlags)(0x0), Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearColorMatrix(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetColorMatrices(const Dgrgdipapi::ColorMatrix &colorMatrix, const Dgrgdipapi::ColorMatrix &grayMatrix, Dgrgdipapi::ColorMatrixFlags mode = (Dgrgdipapi::ColorMatrixFlags)(0x0), Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearColorMatrices(Dgrgdipapi::ColorAdjustType Type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetThreshold(float threshold, Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearThreshold(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetGamma(float gamma, Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearGamma(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetNoOp(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearNoOp(Dgrgdipapi::ColorAdjustType Type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetColorKey(unsigned colorLow, unsigned colorHigh, Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearColorKey(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetOutputChannel(Dgrgdipapi::ColorChannelFlags channelFlags, Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearOutputChannel(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetOutputChannelColorProfile(System::WideString colorProfileFilename, Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearOutputChannelColorProfile(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetRemapTable(unsigned mapSize, Dgrgdipapi::PColorMap map, Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall ClearRemapTable(Dgrgdipapi::ColorAdjustType type_ = (Dgrgdipapi::ColorAdjustType)(0x0));
	Dgrgdipapi::Status __fastcall SetBrushRemapTable(unsigned mapSize, Dgrgdipapi::PColorMap map);
	Dgrgdipapi::Status __fastcall ClearBrushRemapTable(void);
	Dgrgdipapi::Status __fastcall SetWrapMode(Dgrgdipapi::WrapMode wrap, unsigned color = (unsigned)(0xff000000), BOOL clamp = false);
	Dgrgdipapi::Status __fastcall GetAdjustedPalette(Dgrgdipapi::PColorPalette colorPalette, Dgrgdipapi::ColorAdjustType colorAdjustType);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

typedef System::StaticArray<float, 6> TMatrixArray;

#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPMatrix : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeMatrix;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeMatrix(void * nativeMatrix);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPMatrix(void * nativeMatrix)/* overload */;
	
public:
	__fastcall TGPMatrix(void)/* overload */;
	__fastcall TGPMatrix(float m11, float m12, float m21, float m22, float dx, float dy)/* overload */;
	__fastcall TGPMatrix(const Dgrgdipapi::TGPRectF &rect, const Dgrgdipapi::TGPPointF &dstplg)/* overload */;
	__fastcall TGPMatrix(const Dgrgdipapi::TGPRect &rect, const Dgrgdipapi::TGPPoint &dstplg)/* overload */;
	__fastcall virtual ~TGPMatrix(void);
	TGPMatrix* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall GetElements(const TMatrixArray &m);
	Dgrgdipapi::Status __fastcall SetElements(float m11, float m12, float m21, float m22, float dx, float dy);
	float __fastcall OffsetX(void);
	float __fastcall OffsetY(void);
	Dgrgdipapi::Status __fastcall Reset(void);
	Dgrgdipapi::Status __fastcall Multiply(TGPMatrix* matrix, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall Translate(float offsetX, float offsetY, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall Scale(float scaleX, float scaleY, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall Rotate(float angle, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall RotateAt(float angle, const Dgrgdipapi::TGPPointF &center, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall Shear(float shearX, float shearY, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall Invert(void);
	Dgrgdipapi::Status __fastcall TransformPoints(Dgrgdipapi::PGPPointF pts, int count = 0x1)/* overload */;
	Dgrgdipapi::Status __fastcall TransformPoints(Dgrgdipapi::PGPPoint pts, int count = 0x1)/* overload */;
	Dgrgdipapi::Status __fastcall TransformVectors(Dgrgdipapi::PGPPointF pts, int count = 0x1)/* overload */;
	Dgrgdipapi::Status __fastcall TransformVectors(Dgrgdipapi::PGPPoint pts, int count = 0x1)/* overload */;
	BOOL __fastcall IsInvertible(void);
	BOOL __fastcall IsIdentity(void);
	BOOL __fastcall IsEqual(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPBrush;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPBrush : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeBrush;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeBrush(void * nativeBrush);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPBrush(void * nativeBrush, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPBrush(void)/* overload */;
	__fastcall virtual ~TGPBrush(void);
	virtual TGPBrush* __fastcall Clone(void);
	Dgrgdipapi::BrushType __fastcall GetType(void);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPSolidBrush;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPSolidBrush : public TGPBrush
{
	typedef TGPBrush inherited;
	
public:
	__fastcall TGPSolidBrush(unsigned color)/* overload */;
	__fastcall TGPSolidBrush(void)/* overload */;
	Dgrgdipapi::Status __fastcall GetColor(/* out */ unsigned &color);
	Dgrgdipapi::Status __fastcall SetColor(unsigned color);
protected:
	/* TGPBrush.Create */ inline __fastcall TGPSolidBrush(void * nativeBrush, Dgrgdipapi::Status status)/* overload */ : TGPBrush(nativeBrush, status) { }
	
public:
	/* TGPBrush.Destroy */ inline __fastcall virtual ~TGPSolidBrush(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGPTextureBrush;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPTextureBrush : public TGPBrush
{
	typedef TGPBrush inherited;
	
public:
	__fastcall TGPTextureBrush(TGPImage* image, Dgrgdipapi::WrapMode wrapMode)/* overload */;
	__fastcall TGPTextureBrush(TGPImage* image, Dgrgdipapi::WrapMode wrapMode, const Dgrgdipapi::TGPRectF &dstRect)/* overload */;
	__fastcall TGPTextureBrush(TGPImage* image, const Dgrgdipapi::TGPRectF &dstRect, TGPImageAttributes* imageAttributes)/* overload */;
	__fastcall TGPTextureBrush(TGPImage* image, const Dgrgdipapi::TGPRect &dstRect, TGPImageAttributes* imageAttributes)/* overload */;
	__fastcall TGPTextureBrush(TGPImage* image, Dgrgdipapi::WrapMode wrapMode, const Dgrgdipapi::TGPRect &dstRect)/* overload */;
	__fastcall TGPTextureBrush(TGPImage* image, Dgrgdipapi::WrapMode wrapMode, float dstX, float dstY, float dstWidth, float dstHeight)/* overload */;
	__fastcall TGPTextureBrush(TGPImage* image, Dgrgdipapi::WrapMode wrapMode, int dstX, int dstY, int dstWidth, int dstHeight)/* overload */;
	__fastcall TGPTextureBrush(void)/* overload */;
	Dgrgdipapi::Status __fastcall SetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall ResetTransform(void);
	Dgrgdipapi::Status __fastcall MultiplyTransform(TGPMatrix* matrix, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall TranslateTransform(float dx, float dy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall ScaleTransform(float sx, float sy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall RotateTransform(float angle, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall SetWrapMode(Dgrgdipapi::WrapMode wrapMode);
	Dgrgdipapi::WrapMode __fastcall GetWrapMode(void);
	TGPImage* __fastcall GetImage(void);
protected:
	/* TGPBrush.Create */ inline __fastcall TGPTextureBrush(void * nativeBrush, Dgrgdipapi::Status status)/* overload */ : TGPBrush(nativeBrush, status) { }
	
public:
	/* TGPBrush.Destroy */ inline __fastcall virtual ~TGPTextureBrush(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGPLinearGradientBrush;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPLinearGradientBrush : public TGPBrush
{
	typedef TGPBrush inherited;
	
public:
	__fastcall TGPLinearGradientBrush(void)/* overload */;
	__fastcall TGPLinearGradientBrush(const Dgrgdipapi::TGPPointF &point1, const Dgrgdipapi::TGPPointF &point2, unsigned color1, unsigned color2)/* overload */;
	__fastcall TGPLinearGradientBrush(const Dgrgdipapi::TGPPoint &point1, const Dgrgdipapi::TGPPoint &point2, unsigned color1, unsigned color2)/* overload */;
	__fastcall TGPLinearGradientBrush(const Dgrgdipapi::TGPRectF &rect, unsigned color1, unsigned color2, Dgrgdipapi::LinearGradientMode mode)/* overload */;
	__fastcall TGPLinearGradientBrush(const Dgrgdipapi::TGPRect &rect, unsigned color1, unsigned color2, Dgrgdipapi::LinearGradientMode mode)/* overload */;
	__fastcall TGPLinearGradientBrush(const Dgrgdipapi::TGPRectF &rect, unsigned color1, unsigned color2, float angle, BOOL isAngleScalable)/* overload */;
	__fastcall TGPLinearGradientBrush(const Dgrgdipapi::TGPRect &rect, unsigned color1, unsigned color2, float angle, BOOL isAngleScalable)/* overload */;
	Dgrgdipapi::Status __fastcall SetLinearColors(unsigned color1, unsigned color2);
	Dgrgdipapi::Status __fastcall GetLinearColors(/* out */ unsigned &color1, /* out */ unsigned &color2);
	Dgrgdipapi::Status __fastcall GetRectangle(/* out */ Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall GetRectangle(/* out */ Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall SetGammaCorrection(BOOL useGammaCorrection);
	BOOL __fastcall GetGammaCorrection(void);
	int __fastcall GetBlendCount(void);
	Dgrgdipapi::Status __fastcall SetBlend(Winapi::Windows::PSingle blendFactors, Winapi::Windows::PSingle blendPositions, int count);
	Dgrgdipapi::Status __fastcall GetBlend(Winapi::Windows::PSingle blendFactors, Winapi::Windows::PSingle blendPositions, int count);
	int __fastcall GetInterpolationColorCount(void);
	Dgrgdipapi::Status __fastcall SetInterpolationColors(Dgrgdipapi::PGPColor presetColors, Winapi::Windows::PSingle blendPositions, int count);
	Dgrgdipapi::Status __fastcall GetInterpolationColors(Dgrgdipapi::PGPColor presetColors, Winapi::Windows::PSingle blendPositions, int count);
	Dgrgdipapi::Status __fastcall SetBlendBellShape(float focus, float scale = 1.000000E+00f);
	Dgrgdipapi::Status __fastcall SetBlendTriangularShape(float focus, float scale = 1.000000E+00f);
	Dgrgdipapi::Status __fastcall SetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall ResetTransform(void);
	Dgrgdipapi::Status __fastcall MultiplyTransform(TGPMatrix* matrix, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall TranslateTransform(float dx, float dy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall ScaleTransform(float sx, float sy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall RotateTransform(float angle, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall SetWrapMode(Dgrgdipapi::WrapMode wrapMode);
	Dgrgdipapi::WrapMode __fastcall GetWrapMode(void);
protected:
	/* TGPBrush.Create */ inline __fastcall TGPLinearGradientBrush(void * nativeBrush, Dgrgdipapi::Status status)/* overload */ : TGPBrush(nativeBrush, status) { }
	
public:
	/* TGPBrush.Destroy */ inline __fastcall virtual ~TGPLinearGradientBrush(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGPHatchBrush;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPHatchBrush : public TGPBrush
{
	typedef TGPBrush inherited;
	
public:
	__fastcall TGPHatchBrush(void)/* overload */;
	__fastcall TGPHatchBrush(Dgrgdipapi::HatchStyle hatchStyle, unsigned foreColor, unsigned backColor)/* overload */;
	Dgrgdipapi::HatchStyle __fastcall GetHatchStyle(void);
	Dgrgdipapi::Status __fastcall GetForegroundColor(/* out */ unsigned &color);
	Dgrgdipapi::Status __fastcall GetBackgroundColor(/* out */ unsigned &color);
protected:
	/* TGPBrush.Create */ inline __fastcall TGPHatchBrush(void * nativeBrush, Dgrgdipapi::Status status)/* overload */ : TGPBrush(nativeBrush, status) { }
	
public:
	/* TGPBrush.Destroy */ inline __fastcall virtual ~TGPHatchBrush(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGPPen;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPPen : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativePen;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativePen(void * nativePen);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPPen(void * nativePen, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPPen(unsigned color, float width)/* overload */;
	__fastcall TGPPen(TGPBrush* brush, float width)/* overload */;
	__fastcall virtual ~TGPPen(void);
	TGPPen* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall SetWidth(float width);
	float __fastcall GetWidth(void);
	Dgrgdipapi::Status __fastcall SetLineCap(int startCap, int endCap, int dashCap);
	Dgrgdipapi::Status __fastcall SetStartCap(int startCap);
	Dgrgdipapi::Status __fastcall SetEndCap(int endCap);
	Dgrgdipapi::Status __fastcall SetDashCap(int dashCap);
	int __fastcall GetStartCap(void);
	int __fastcall GetEndCap(void);
	int __fastcall GetDashCap(void);
	Dgrgdipapi::Status __fastcall SetLineJoin(Dgrgdipapi::LineJoin lineJoin);
	Dgrgdipapi::LineJoin __fastcall GetLineJoin(void);
	Dgrgdipapi::Status __fastcall SetCustomStartCap(TGPCustomLineCap* customCap);
	Dgrgdipapi::Status __fastcall GetCustomStartCap(TGPCustomLineCap* customCap);
	Dgrgdipapi::Status __fastcall SetCustomEndCap(TGPCustomLineCap* customCap);
	Dgrgdipapi::Status __fastcall GetCustomEndCap(TGPCustomLineCap* customCap);
	Dgrgdipapi::Status __fastcall SetMiterLimit(float miterLimit);
	float __fastcall GetMiterLimit(void);
	Dgrgdipapi::Status __fastcall SetAlignment(Dgrgdipapi::PenAlignment penAlignment);
	Dgrgdipapi::PenAlignment __fastcall GetAlignment(void);
	Dgrgdipapi::Status __fastcall SetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall ResetTransform(void);
	Dgrgdipapi::Status __fastcall MultiplyTransform(TGPMatrix* matrix, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall TranslateTransform(float dx, float dy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall ScaleTransform(float sx, float sy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall RotateTransform(float angle, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	int __fastcall GetPenType(void);
	Dgrgdipapi::Status __fastcall SetColor(unsigned color);
	Dgrgdipapi::Status __fastcall SetBrush(TGPBrush* brush);
	Dgrgdipapi::Status __fastcall GetColor(/* out */ unsigned &Color);
	TGPBrush* __fastcall GetBrush(void);
	Dgrgdipapi::DashStyle __fastcall GetDashStyle(void);
	Dgrgdipapi::Status __fastcall SetDashStyle(Dgrgdipapi::DashStyle dashStyle);
	float __fastcall GetDashOffset(void);
	Dgrgdipapi::Status __fastcall SetDashOffset(float dashOffset);
	Dgrgdipapi::Status __fastcall SetDashPattern(Winapi::Windows::PSingle dashArray, int count);
	int __fastcall GetDashPatternCount(void);
	Dgrgdipapi::Status __fastcall GetDashPattern(Winapi::Windows::PSingle dashArray, int count);
	Dgrgdipapi::Status __fastcall SetCompoundArray(Winapi::Windows::PSingle compoundArray, int count);
	int __fastcall GetCompoundArrayCount(void);
	Dgrgdipapi::Status __fastcall GetCompoundArray(Winapi::Windows::PSingle compoundArray, int count);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPStringFormat;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPStringFormat : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeFormat;
	Dgrgdipapi::Status lastError;
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status newStatus);
	void __fastcall Assign(TGPStringFormat* source);
	__fastcall TGPStringFormat(void * clonedStringFormat, Dgrgdipapi::Status status)/* overload */;
	
public:
	__fastcall TGPStringFormat(int formatFlags, System::Word language)/* overload */;
	__fastcall TGPStringFormat(TGPStringFormat* format)/* overload */;
	__fastcall virtual ~TGPStringFormat(void);
	__classmethod TGPStringFormat* __fastcall GenericDefault();
	__classmethod TGPStringFormat* __fastcall GenericTypographic();
	TGPStringFormat* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall SetFormatFlags(int flags);
	int __fastcall GetFormatFlags(void);
	Dgrgdipapi::Status __fastcall SetAlignment(Dgrgdipapi::StringAlignment align);
	Dgrgdipapi::StringAlignment __fastcall GetAlignment(void);
	Dgrgdipapi::Status __fastcall SetLineAlignment(Dgrgdipapi::StringAlignment align);
	Dgrgdipapi::StringAlignment __fastcall GetLineAlignment(void);
	Dgrgdipapi::Status __fastcall SetHotkeyPrefix(Dgrgdipapi::HotkeyPrefix hotkeyPrefix);
	Dgrgdipapi::HotkeyPrefix __fastcall GetHotkeyPrefix(void);
	Dgrgdipapi::Status __fastcall SetTabStops(float firstTabOffset, int count, Winapi::Windows::PSingle tabStops);
	int __fastcall GetTabStopCount(void);
	Dgrgdipapi::Status __fastcall GetTabStops(int count, Winapi::Windows::PSingle firstTabOffset, Winapi::Windows::PSingle tabStops);
	Dgrgdipapi::Status __fastcall SetDigitSubstitution(System::Word language, Dgrgdipapi::StringDigitSubstitute substitute);
	System::Word __fastcall GetDigitSubstitutionLanguage(void);
	Dgrgdipapi::StringDigitSubstitute __fastcall GetDigitSubstitutionMethod(void);
	Dgrgdipapi::Status __fastcall SetTrimming(Dgrgdipapi::StringTrimming trimming);
	Dgrgdipapi::StringTrimming __fastcall GetTrimming(void);
	Dgrgdipapi::Status __fastcall SetMeasurableCharacterRanges(int rangeCount, Dgrgdipapi::PCharacterRange ranges);
	int __fastcall GetMeasurableCharacterRangeCount(void);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPGraphicsPath : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativePath;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativePath(void * nativePath);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	__fastcall TGPGraphicsPath(void * nativePath)/* overload */;
	
public:
	__fastcall TGPGraphicsPath(TGPGraphicsPath* path)/* overload */;
	__fastcall TGPGraphicsPath(Dgrgdipapi::FillMode fillMode)/* overload */;
	__fastcall TGPGraphicsPath(Dgrgdipapi::PGPPointF points, System::PByte types, int count, Dgrgdipapi::FillMode fillMode)/* overload */;
	__fastcall TGPGraphicsPath(Dgrgdipapi::PGPPoint points, System::PByte types, int count, Dgrgdipapi::FillMode fillMode)/* overload */;
	__fastcall virtual ~TGPGraphicsPath(void);
	TGPGraphicsPath* __fastcall Clone(void);
	Dgrgdipapi::Status __fastcall Reset(void);
	Dgrgdipapi::FillMode __fastcall GetFillMode(void);
	Dgrgdipapi::Status __fastcall SetFillMode(Dgrgdipapi::FillMode fillmode);
	Dgrgdipapi::Status __fastcall GetPathData(Dgrgdipapi::TPathData* pathData);
	Dgrgdipapi::Status __fastcall StartFigure(void);
	Dgrgdipapi::Status __fastcall CloseFigure(void);
	Dgrgdipapi::Status __fastcall CloseAllFigures(void);
	Dgrgdipapi::Status __fastcall SetMarker(void);
	Dgrgdipapi::Status __fastcall ClearMarkers(void);
	Dgrgdipapi::Status __fastcall Reverse(void);
	Dgrgdipapi::Status __fastcall GetLastPoint(/* out */ Dgrgdipapi::TGPPointF &lastPoint);
	Dgrgdipapi::Status __fastcall AddLine(const Dgrgdipapi::TGPPointF &pt1, const Dgrgdipapi::TGPPointF &pt2)/* overload */;
	Dgrgdipapi::Status __fastcall AddLine(float x1, float y1, float x2, float y2)/* overload */;
	Dgrgdipapi::Status __fastcall AddLines(Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddLine(const Dgrgdipapi::TGPPoint &pt1, const Dgrgdipapi::TGPPoint &pt2)/* overload */;
	Dgrgdipapi::Status __fastcall AddLine(int x1, int y1, int x2, int y2)/* overload */;
	Dgrgdipapi::Status __fastcall AddLines(Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddArc(const Dgrgdipapi::TGPRectF &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddArc(float x, float y, float width, float height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddArc(const Dgrgdipapi::TGPRect &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddArc(int x, int y, int width, int height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddBezier(const Dgrgdipapi::TGPPointF &pt1, const Dgrgdipapi::TGPPointF &pt2, const Dgrgdipapi::TGPPointF &pt3, const Dgrgdipapi::TGPPointF &pt4)/* overload */;
	Dgrgdipapi::Status __fastcall AddBezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)/* overload */;
	Dgrgdipapi::Status __fastcall AddBeziers(Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddBezier(const Dgrgdipapi::TGPPoint &pt1, const Dgrgdipapi::TGPPoint &pt2, const Dgrgdipapi::TGPPoint &pt3, const Dgrgdipapi::TGPPoint &pt4)/* overload */;
	Dgrgdipapi::Status __fastcall AddBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)/* overload */;
	Dgrgdipapi::Status __fastcall AddBeziers(Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddCurve(Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddCurve(Dgrgdipapi::PGPPointF points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall AddCurve(Dgrgdipapi::PGPPointF points, int count, int offset, int numberOfSegments, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall AddCurve(Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddCurve(Dgrgdipapi::PGPPoint points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall AddCurve(Dgrgdipapi::PGPPoint points, int count, int offset, int numberOfSegments, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall AddClosedCurve(Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddClosedCurve(Dgrgdipapi::PGPPointF points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall AddClosedCurve(Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddClosedCurve(Dgrgdipapi::PGPPoint points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall AddRectangle(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall AddRectangles(Dgrgdipapi::PGPRectF rects, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddRectangle(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall AddRectangles(Dgrgdipapi::PGPRect rects, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddEllipse(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall AddEllipse(float x, float y, float width, float height)/* overload */;
	Dgrgdipapi::Status __fastcall AddEllipse(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall AddEllipse(int x, int y, int width, int height)/* overload */;
	Dgrgdipapi::Status __fastcall AddPie(const Dgrgdipapi::TGPRectF &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddPie(float x, float y, float width, float height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddPie(const Dgrgdipapi::TGPRect &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddPie(int x, int y, int width, int height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall AddPolygon(Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddPolygon(Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall AddPath(TGPGraphicsPath* addingPath, BOOL connect);
	Dgrgdipapi::Status __fastcall AddString(System::WideString string_, int length, TGPFontFamily* family, int style, float emSize, const Dgrgdipapi::TGPPointF &origin, TGPStringFormat* format)/* overload */;
	Dgrgdipapi::Status __fastcall AddString(System::WideString string_, int length, TGPFontFamily* family, int style, float emSize, const Dgrgdipapi::TGPRectF &layoutRect, TGPStringFormat* format)/* overload */;
	Dgrgdipapi::Status __fastcall AddString(System::WideString string_, int length, TGPFontFamily* family, int style, float emSize, const Dgrgdipapi::TGPPoint &origin, TGPStringFormat* format)/* overload */;
	Dgrgdipapi::Status __fastcall AddString(System::WideString string_, int length, TGPFontFamily* family, int style, float emSize, const Dgrgdipapi::TGPRect &layoutRect, TGPStringFormat* format)/* overload */;
	Dgrgdipapi::Status __fastcall Transform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall GetBounds(/* out */ Dgrgdipapi::TGPRectF &bounds, TGPMatrix* matrix = (TGPMatrix*)(0x0), TGPPen* pen = (TGPPen*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall GetBounds(/* out */ Dgrgdipapi::TGPRect &bounds, TGPMatrix* matrix = (TGPMatrix*)(0x0), TGPPen* pen = (TGPPen*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall Flatten(TGPMatrix* matrix = (TGPMatrix*)(0x0), float flatness = 2.500000E-01f);
	Dgrgdipapi::Status __fastcall Widen(TGPPen* pen, TGPMatrix* matrix = (TGPMatrix*)(0x0), float flatness = 2.500000E-01f);
	Dgrgdipapi::Status __fastcall Outline(TGPMatrix* matrix = (TGPMatrix*)(0x0), float flatness = 2.500000E-01f);
	Dgrgdipapi::Status __fastcall Warp(Dgrgdipapi::PGPPointF destPoints, int count, const Dgrgdipapi::TGPRectF &srcRect, TGPMatrix* matrix = (TGPMatrix*)(0x0), Dgrgdipapi::WarpMode warpMode = (Dgrgdipapi::WarpMode)(0x0), float flatness = 2.500000E-01f);
	int __fastcall GetPointCount(void);
	Dgrgdipapi::Status __fastcall GetPathTypes(System::PByte types, int count);
	Dgrgdipapi::Status __fastcall GetPathPoints(Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall GetPathPoints(Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPPointF &point, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(float x, float y, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPPoint &point, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsVisible(int x, int y, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsOutlineVisible(const Dgrgdipapi::TGPPointF &point, TGPPen* pen, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsOutlineVisible(float x, float y, TGPPen* pen, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsOutlineVisible(const Dgrgdipapi::TGPPoint &point, TGPPen* pen, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
	BOOL __fastcall IsOutlineVisible(int x, int y, TGPPen* pen, TGPGraphics* g = (TGPGraphics*)(0x0))/* overload */;
};

#pragma pack(pop)

class DELPHICLASS TGPGraphicsPathIterator;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPGraphicsPathIterator : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeIterator;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeIterator(void * nativeIterator);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	
public:
	__fastcall TGPGraphicsPathIterator(TGPGraphicsPath* path);
	__fastcall virtual ~TGPGraphicsPathIterator(void);
	int __fastcall NextSubpath(/* out */ int &startIndex, /* out */ int &endIndex, /* out */ BOOL &isClosed)/* overload */;
	int __fastcall NextSubpath(TGPGraphicsPath* path, /* out */ BOOL &isClosed)/* overload */;
	int __fastcall NextPathType(/* out */ System::Byte &pathType, /* out */ int &startIndex, /* out */ int &endIndex);
	int __fastcall NextMarker(/* out */ int &startIndex, /* out */ int &endIndex)/* overload */;
	int __fastcall NextMarker(TGPGraphicsPath* path)/* overload */;
	int __fastcall GetCount(void);
	int __fastcall GetSubpathCount(void);
	BOOL __fastcall HasCurve(void);
	void __fastcall Rewind(void);
	int __fastcall Enumerate(Dgrgdipapi::PGPPointF points, System::PByte types, int count);
	int __fastcall CopyData(Dgrgdipapi::PGPPointF points, System::PByte types, int startIndex, int endIndex);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPPathGradientBrush;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPPathGradientBrush : public TGPBrush
{
	typedef TGPBrush inherited;
	
public:
	__fastcall TGPPathGradientBrush(Dgrgdipapi::PGPPointF points, int count, Dgrgdipapi::WrapMode wrapMode)/* overload */;
	__fastcall TGPPathGradientBrush(Dgrgdipapi::PGPPoint points, int count, Dgrgdipapi::WrapMode wrapMode)/* overload */;
	__fastcall TGPPathGradientBrush(TGPGraphicsPath* path)/* overload */;
	__fastcall TGPPathGradientBrush(void)/* overload */;
	Dgrgdipapi::Status __fastcall GetCenterColor(/* out */ unsigned &Color);
	Dgrgdipapi::Status __fastcall SetCenterColor(unsigned color);
	int __fastcall GetPointCount(void);
	int __fastcall GetSurroundColorCount(void);
	Dgrgdipapi::Status __fastcall GetSurroundColors(Dgrgdipapi::PARGB colors, int &count);
	Dgrgdipapi::Status __fastcall SetSurroundColors(Dgrgdipapi::PARGB colors, int &count);
	Dgrgdipapi::Status __fastcall GetGraphicsPath(TGPGraphicsPath* path);
	Dgrgdipapi::Status __fastcall SetGraphicsPath(TGPGraphicsPath* path);
	Dgrgdipapi::Status __fastcall GetCenterPoint(/* out */ Dgrgdipapi::TGPPointF &point)/* overload */;
	Dgrgdipapi::Status __fastcall GetCenterPoint(/* out */ Dgrgdipapi::TGPPoint &point)/* overload */;
	Dgrgdipapi::Status __fastcall SetCenterPoint(const Dgrgdipapi::TGPPointF &point)/* overload */;
	Dgrgdipapi::Status __fastcall SetCenterPoint(const Dgrgdipapi::TGPPoint &point)/* overload */;
	Dgrgdipapi::Status __fastcall GetRectangle(/* out */ Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall GetRectangle(/* out */ Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall SetGammaCorrection(BOOL useGammaCorrection)/* overload */;
	BOOL __fastcall GetGammaCorrection(void)/* overload */;
	int __fastcall GetBlendCount(void);
	Dgrgdipapi::Status __fastcall GetBlend(Winapi::Windows::PSingle blendFactors, Winapi::Windows::PSingle blendPositions, int count);
	Dgrgdipapi::Status __fastcall SetBlend(Winapi::Windows::PSingle blendFactors, Winapi::Windows::PSingle blendPositions, int count);
	int __fastcall GetInterpolationColorCount(void);
	Dgrgdipapi::Status __fastcall SetInterpolationColors(Dgrgdipapi::PARGB presetColors, Winapi::Windows::PSingle blendPositions, int count);
	Dgrgdipapi::Status __fastcall GetInterpolationColors(Dgrgdipapi::PARGB presetColors, Winapi::Windows::PSingle blendPositions, int count);
	Dgrgdipapi::Status __fastcall SetBlendBellShape(float focus, float scale = 1.000000E+00f);
	Dgrgdipapi::Status __fastcall SetBlendTriangularShape(float focus, float scale = 1.000000E+00f);
	Dgrgdipapi::Status __fastcall GetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall SetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall ResetTransform(void);
	Dgrgdipapi::Status __fastcall MultiplyTransform(TGPMatrix* matrix, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall TranslateTransform(float dx, float dy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall ScaleTransform(float sx, float sy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall RotateTransform(float angle, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall GetFocusScales(/* out */ float &xScale, /* out */ float &yScale);
	Dgrgdipapi::Status __fastcall SetFocusScales(float xScale, float yScale);
	Dgrgdipapi::WrapMode __fastcall GetWrapMode(void);
	Dgrgdipapi::Status __fastcall SetWrapMode(Dgrgdipapi::WrapMode wrapMode);
protected:
	/* TGPBrush.Create */ inline __fastcall TGPPathGradientBrush(void * nativeBrush, Dgrgdipapi::Status status)/* overload */ : TGPBrush(nativeBrush, status) { }
	
public:
	/* TGPBrush.Destroy */ inline __fastcall virtual ~TGPPathGradientBrush(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TGPMetafile;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPGraphics : public Dgrgdipapi::TGdiplusBase
{
	typedef Dgrgdipapi::TGdiplusBase inherited;
	
protected:
	void *nativeGraphics;
	Dgrgdipapi::Status lastResult;
	void __fastcall SetNativeGraphics(void * graphics);
	Dgrgdipapi::Status __fastcall SetStatus(Dgrgdipapi::Status status);
	void * __fastcall GetNativeGraphics(void);
	void * __fastcall GetNativePen(TGPPen* pen);
	__fastcall TGPGraphics(void * graphics)/* overload */;
	
public:
	TGPGraphics* __fastcall FromHDC(HDC hdc)/* overload */;
	TGPGraphics* __fastcall FromHDC(HDC hdc, NativeUInt hdevice)/* overload */;
	TGPGraphics* __fastcall FromHWND(HWND hwnd, BOOL icm = false);
	TGPGraphics* __fastcall FromImage(TGPImage* image);
	__fastcall TGPGraphics(HDC hdc, int Dummy1, int Dummy2)/* overload */;
	__fastcall TGPGraphics(HDC hdc, NativeUInt hdevice)/* overload */;
	__fastcall TGPGraphics(HWND hwnd, BOOL icm)/* overload */;
	__fastcall TGPGraphics(TGPImage* image)/* overload */;
	__fastcall virtual ~TGPGraphics(void);
	void __fastcall Flush(Dgrgdipapi::FlushIntention intention = (Dgrgdipapi::FlushIntention)(0x0));
	HDC __fastcall GetHDC(void);
	void __fastcall ReleaseHDC(HDC hdc);
	Dgrgdipapi::Status __fastcall SetRenderingOrigin(int x, int y);
	Dgrgdipapi::Status __fastcall GetRenderingOrigin(/* out */ int &x, /* out */ int &y);
	Dgrgdipapi::Status __fastcall SetCompositingMode(Dgrgdipapi::CompositingMode compositingMode);
	Dgrgdipapi::CompositingMode __fastcall GetCompositingMode(void);
	Dgrgdipapi::Status __fastcall SetCompositingQuality(int compositingQuality);
	int __fastcall GetCompositingQuality(void);
	Dgrgdipapi::Status __fastcall SetTextRenderingHint(Dgrgdipapi::TextRenderingHint newMode);
	Dgrgdipapi::TextRenderingHint __fastcall GetTextRenderingHint(void);
	Dgrgdipapi::Status __fastcall SetTextContrast(unsigned contrast);
	unsigned __fastcall GetTextContrast(void);
	int __fastcall GetInterpolationMode(void);
	Dgrgdipapi::Status __fastcall SetInterpolationMode(int interpolationMode);
	int __fastcall GetSmoothingMode(void);
	Dgrgdipapi::Status __fastcall SetSmoothingMode(int smoothingMode);
	int __fastcall GetPixelOffsetMode(void);
	Dgrgdipapi::Status __fastcall SetPixelOffsetMode(int pixelOffsetMode);
	Dgrgdipapi::Status __fastcall SetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall ResetTransform(void);
	Dgrgdipapi::Status __fastcall MultiplyTransform(TGPMatrix* matrix, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall TranslateTransform(float dx, float dy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall ScaleTransform(float sx, float sy, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall RotateTransform(float angle, Dgrgdipapi::MatrixOrder order = (Dgrgdipapi::MatrixOrder)(0x0));
	Dgrgdipapi::Status __fastcall GetTransform(TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall SetPageUnit(Dgrgdipapi::Unit_ unit_);
	Dgrgdipapi::Status __fastcall SetPageScale(float scale);
	Dgrgdipapi::Unit_ __fastcall GetPageUnit(void);
	float __fastcall GetPageScale(void);
	float __fastcall GetDpiX(void);
	float __fastcall GetDpiY(void);
	Dgrgdipapi::Status __fastcall TransformPoints(Dgrgdipapi::CoordinateSpace destSpace, Dgrgdipapi::CoordinateSpace srcSpace, Dgrgdipapi::PGPPointF pts, int count)/* overload */;
	Dgrgdipapi::Status __fastcall TransformPoints(Dgrgdipapi::CoordinateSpace destSpace, Dgrgdipapi::CoordinateSpace srcSpace, Dgrgdipapi::PGPPoint pts, int count)/* overload */;
	Dgrgdipapi::Status __fastcall GetNearestColor(unsigned &color);
	Dgrgdipapi::Status __fastcall DrawLine(TGPPen* pen, float x1, float y1, float x2, float y2)/* overload */;
	Dgrgdipapi::Status __fastcall DrawLine(TGPPen* pen, const Dgrgdipapi::TGPPointF &pt1, const Dgrgdipapi::TGPPointF &pt2)/* overload */;
	Dgrgdipapi::Status __fastcall DrawLines(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawLine(TGPPen* pen, int x1, int y1, int x2, int y2)/* overload */;
	Dgrgdipapi::Status __fastcall DrawLine(TGPPen* pen, const Dgrgdipapi::TGPPoint &pt1, const Dgrgdipapi::TGPPoint &pt2)/* overload */;
	Dgrgdipapi::Status __fastcall DrawLines(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawArc(TGPPen* pen, float x, float y, float width, float height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawArc(TGPPen* pen, const Dgrgdipapi::TGPRectF &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawArc(TGPPen* pen, int x, int y, int width, int height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawArc(TGPPen* pen, const Dgrgdipapi::TGPRect &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawBezier(TGPPen* pen, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)/* overload */;
	Dgrgdipapi::Status __fastcall DrawBezier(TGPPen* pen, const Dgrgdipapi::TGPPointF &pt1, const Dgrgdipapi::TGPPointF &pt2, const Dgrgdipapi::TGPPointF &pt3, const Dgrgdipapi::TGPPointF &pt4)/* overload */;
	Dgrgdipapi::Status __fastcall DrawBeziers(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawBezier(TGPPen* pen, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)/* overload */;
	Dgrgdipapi::Status __fastcall DrawBezier(TGPPen* pen, const Dgrgdipapi::TGPPoint &pt1, const Dgrgdipapi::TGPPoint &pt2, const Dgrgdipapi::TGPPoint &pt3, const Dgrgdipapi::TGPPoint &pt4)/* overload */;
	Dgrgdipapi::Status __fastcall DrawBeziers(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawRectangle(TGPPen* pen, const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall DrawRectangle(TGPPen* pen, float x, float y, float width, float height)/* overload */;
	Dgrgdipapi::Status __fastcall DrawRectangles(TGPPen* pen, Dgrgdipapi::PGPRectF rects, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawRectangle(TGPPen* pen, const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall DrawRectangle(TGPPen* pen, int x, int y, int width, int height)/* overload */;
	Dgrgdipapi::Status __fastcall DrawRectangles(TGPPen* pen, Dgrgdipapi::PGPRect rects, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawEllipse(TGPPen* pen, const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall DrawEllipse(TGPPen* pen, float x, float y, float width, float height)/* overload */;
	Dgrgdipapi::Status __fastcall DrawEllipse(TGPPen* pen, const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall DrawEllipse(TGPPen* pen, int x, int y, int width, int height)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPie(TGPPen* pen, const Dgrgdipapi::TGPRectF &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPie(TGPPen* pen, float x, float y, float width, float height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPie(TGPPen* pen, const Dgrgdipapi::TGPRect &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPie(TGPPen* pen, int x, int y, int width, int height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPolygon(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPolygon(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawPath(TGPPen* pen, TGPGraphicsPath* path);
	Dgrgdipapi::Status __fastcall DrawCurve(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawCurve(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall DrawCurve(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count, int offset, int numberOfSegments, float tension = 5.000000E-01f)/* overload */;
	Dgrgdipapi::Status __fastcall DrawCurve(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawCurve(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall DrawCurve(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count, int offset, int numberOfSegments, float tension = 5.000000E-01f)/* overload */;
	Dgrgdipapi::Status __fastcall DrawClosedCurve(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawClosedCurve(TGPPen* pen, Dgrgdipapi::PGPPointF points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall DrawClosedCurve(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawClosedCurve(TGPPen* pen, Dgrgdipapi::PGPPoint points, int count, float tension)/* overload */;
	Dgrgdipapi::Status __fastcall Clear(unsigned color);
	Dgrgdipapi::Status __fastcall FillRectangle(TGPBrush* brush, const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall FillRectangle(TGPBrush* brush, float x, float y, float width, float height)/* overload */;
	Dgrgdipapi::Status __fastcall FillRectangles(TGPBrush* brush, Dgrgdipapi::PGPRectF rects, int count)/* overload */;
	Dgrgdipapi::Status __fastcall FillRectangle(TGPBrush* brush, const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall FillRectangle(TGPBrush* brush, int x, int y, int width, int height)/* overload */;
	Dgrgdipapi::Status __fastcall FillRectangles(TGPBrush* brush, Dgrgdipapi::PGPRect rects, int count)/* overload */;
	Dgrgdipapi::Status __fastcall FillPolygon(TGPBrush* brush, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall FillPolygon(TGPBrush* brush, Dgrgdipapi::PGPPointF points, int count, Dgrgdipapi::FillMode fillMode)/* overload */;
	Dgrgdipapi::Status __fastcall FillPolygon(TGPBrush* brush, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall FillPolygon(TGPBrush* brush, Dgrgdipapi::PGPPoint points, int count, Dgrgdipapi::FillMode fillMode)/* overload */;
	Dgrgdipapi::Status __fastcall FillEllipse(TGPBrush* brush, const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall FillEllipse(TGPBrush* brush, float x, float y, float width, float height)/* overload */;
	Dgrgdipapi::Status __fastcall FillEllipse(TGPBrush* brush, const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall FillEllipse(TGPBrush* brush, int x, int y, int width, int height)/* overload */;
	Dgrgdipapi::Status __fastcall FillPie(TGPBrush* brush, const Dgrgdipapi::TGPRectF &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall FillPie(TGPBrush* brush, float x, float y, float width, float height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall FillPie(TGPBrush* brush, const Dgrgdipapi::TGPRect &rect, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall FillPie(TGPBrush* brush, int x, int y, int width, int height, float startAngle, float sweepAngle)/* overload */;
	Dgrgdipapi::Status __fastcall FillPath(TGPBrush* brush, TGPGraphicsPath* path);
	Dgrgdipapi::Status __fastcall FillClosedCurve(TGPBrush* brush, Dgrgdipapi::PGPPointF points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall FillClosedCurve(TGPBrush* brush, Dgrgdipapi::PGPPointF points, int count, Dgrgdipapi::FillMode fillMode, float tension = 5.000000E-01f)/* overload */;
	Dgrgdipapi::Status __fastcall FillClosedCurve(TGPBrush* brush, Dgrgdipapi::PGPPoint points, int count)/* overload */;
	Dgrgdipapi::Status __fastcall FillClosedCurve(TGPBrush* brush, Dgrgdipapi::PGPPoint points, int count, Dgrgdipapi::FillMode fillMode, float tension = 5.000000E-01f)/* overload */;
	Dgrgdipapi::Status __fastcall FillRegion(TGPBrush* brush, TGPRegion* region);
	Dgrgdipapi::Status __fastcall DrawString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPRectF &layoutRect, TGPStringFormat* stringFormat, TGPBrush* brush)/* overload */;
	Dgrgdipapi::Status __fastcall DrawString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPPointF &origin, TGPBrush* brush)/* overload */;
	Dgrgdipapi::Status __fastcall DrawString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPPointF &origin, TGPStringFormat* stringFormat, TGPBrush* brush)/* overload */;
	Dgrgdipapi::Status __fastcall MeasureString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPRectF &layoutRect, TGPStringFormat* stringFormat, /* out */ Dgrgdipapi::TGPRectF &boundingBox, System::PInteger codepointsFitted = (System::PInteger)(0x0), System::PInteger linesFilled = (System::PInteger)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall MeasureString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPSizeF &layoutRectSize, TGPStringFormat* stringFormat, /* out */ Dgrgdipapi::TGPSizeF &size, System::PInteger codepointsFitted = (System::PInteger)(0x0), System::PInteger linesFilled = (System::PInteger)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall MeasureString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPPointF &origin, TGPStringFormat* stringFormat, /* out */ Dgrgdipapi::TGPRectF &boundingBox)/* overload */;
	Dgrgdipapi::Status __fastcall MeasureString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPRectF &layoutRect, /* out */ Dgrgdipapi::TGPRectF &boundingBox)/* overload */;
	Dgrgdipapi::Status __fastcall MeasureString(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPPointF &origin, /* out */ Dgrgdipapi::TGPRectF &boundingBox)/* overload */;
	Dgrgdipapi::Status __fastcall MeasureCharacterRanges(System::WideString string_, int length, TGPFont* font, const Dgrgdipapi::TGPRectF &layoutRect, TGPStringFormat* stringFormat, int regionCount, TGPRegion* const *regions, const int regions_High)/* overload */;
	Dgrgdipapi::Status __fastcall DrawDriverString(Dgrgdipapi::PUINT16 text, int length, TGPFont* font, TGPBrush* brush, Dgrgdipapi::PGPPointF positions, int flags, TGPMatrix* matrix);
	Dgrgdipapi::Status __fastcall MeasureDriverString(Dgrgdipapi::PUINT16 text, int length, TGPFont* font, Dgrgdipapi::PGPPointF positions, int flags, TGPMatrix* matrix, /* out */ Dgrgdipapi::TGPRectF &boundingBox);
	Dgrgdipapi::Status __fastcall DrawCachedBitmap(TGPCachedBitmap* cb, int x, int y);
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, const Dgrgdipapi::TGPPointF &point)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, float x, float y)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, float x, float y, float width, float height)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, const Dgrgdipapi::TGPPoint &point)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, int x, int y)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, int x, int y, int width, int height)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, Dgrgdipapi::PGPPointF destPoints, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, Dgrgdipapi::PGPPoint destPoints, int count)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, float x, float y, float srcx, float srcy, float srcwidth, float srcheight, Dgrgdipapi::Unit_ srcUnit)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, const Dgrgdipapi::TGPRectF &destRect, float srcx, float srcy, float srcwidth, float srcheight, Dgrgdipapi::Unit_ srcUnit, TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0), Dgrgdipapi::ImageAbort callback = 0x0, void * callbackData = (void *)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, Dgrgdipapi::PGPPointF destPoints, int count, float srcx, float srcy, float srcwidth, float srcheight, Dgrgdipapi::Unit_ srcUnit, TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0), Dgrgdipapi::ImageAbort callback = 0x0, void * callbackData = (void *)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, int x, int y, int srcx, int srcy, int srcwidth, int srcheight, Dgrgdipapi::Unit_ srcUnit)/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, const Dgrgdipapi::TGPRect &destRect, int srcx, int srcy, int srcwidth, int srcheight, Dgrgdipapi::Unit_ srcUnit, TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0), Dgrgdipapi::ImageAbort callback = 0x0, void * callbackData = (void *)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall DrawImage(TGPImage* image, Dgrgdipapi::PGPPoint destPoints, int count, int srcx, int srcy, int srcwidth, int srcheight, Dgrgdipapi::Unit_ srcUnit, TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0), Dgrgdipapi::ImageAbort callback = 0x0, void * callbackData = (void *)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPPointF &destPoint, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPPoint &destPoint, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPRectF &destRect, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPRect &destRect, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, Dgrgdipapi::PGPPointF destPoints, int count, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, Dgrgdipapi::PGPPoint destPoints, int count, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPPointF &destPoint, const Dgrgdipapi::TGPRectF &srcRect, Dgrgdipapi::Unit_ srcUnit, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPPoint &destPoint, const Dgrgdipapi::TGPRect &srcRect, Dgrgdipapi::Unit_ srcUnit, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPRectF &destRect, const Dgrgdipapi::TGPRectF &srcRect, Dgrgdipapi::Unit_ srcUnit, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, const Dgrgdipapi::TGPRect &destRect, const Dgrgdipapi::TGPRect &srcRect, Dgrgdipapi::Unit_ srcUnit, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, Dgrgdipapi::PGPPointF destPoints, int count, const Dgrgdipapi::TGPRectF &srcRect, Dgrgdipapi::Unit_ srcUnit, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall EnumerateMetafile(TGPMetafile* metafile, Dgrgdipapi::PGPPoint destPoints, int count, const Dgrgdipapi::TGPRect &srcRect, Dgrgdipapi::Unit_ srcUnit, Dgrgdipapi::EnumerateMetafileProc callback, void * callbackData = (void *)(0x0), TGPImageAttributes* imageAttributes = (TGPImageAttributes*)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SetClip(TGPGraphics* g, Dgrgdipapi::CombineMode combineMode = (Dgrgdipapi::CombineMode)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SetClip(const Dgrgdipapi::TGPRectF &rect, Dgrgdipapi::CombineMode combineMode = (Dgrgdipapi::CombineMode)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SetClip(const Dgrgdipapi::TGPRect &rect, Dgrgdipapi::CombineMode combineMode = (Dgrgdipapi::CombineMode)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SetClip(TGPGraphicsPath* path, Dgrgdipapi::CombineMode combineMode = (Dgrgdipapi::CombineMode)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SetClip(TGPRegion* region, Dgrgdipapi::CombineMode combineMode = (Dgrgdipapi::CombineMode)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall SetClip(HRGN hRgn, Dgrgdipapi::CombineMode combineMode = (Dgrgdipapi::CombineMode)(0x0))/* overload */;
	Dgrgdipapi::Status __fastcall IntersectClip(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall IntersectClip(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall IntersectClip(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall ExcludeClip(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall ExcludeClip(const Dgrgdipapi::TGPRect &rect)/* overload */;
	Dgrgdipapi::Status __fastcall ExcludeClip(TGPRegion* region)/* overload */;
	Dgrgdipapi::Status __fastcall ResetClip(void);
	Dgrgdipapi::Status __fastcall TranslateClip(float dx, float dy)/* overload */;
	Dgrgdipapi::Status __fastcall TranslateClip(int dx, int dy)/* overload */;
	Dgrgdipapi::Status __fastcall GetClip(TGPRegion* region);
	Dgrgdipapi::Status __fastcall GetClipBounds(/* out */ Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall GetClipBounds(/* out */ Dgrgdipapi::TGPRect &rect)/* overload */;
	BOOL __fastcall IsClipEmpty(void);
	Dgrgdipapi::Status __fastcall GetVisibleClipBounds(/* out */ Dgrgdipapi::TGPRectF &rect)/* overload */;
	Dgrgdipapi::Status __fastcall GetVisibleClipBounds(/* out */ Dgrgdipapi::TGPRect &rect)/* overload */;
	BOOL __fastcall IsVisibleClipEmpty(void);
	BOOL __fastcall IsVisible(int x, int y)/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPPoint &point)/* overload */;
	BOOL __fastcall IsVisible(int x, int y, int width, int height)/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPRect &rect)/* overload */;
	BOOL __fastcall IsVisible(float x, float y)/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPPointF &point)/* overload */;
	BOOL __fastcall IsVisible(float x, float y, float width, float height)/* overload */;
	BOOL __fastcall IsVisible(const Dgrgdipapi::TGPRectF &rect)/* overload */;
	unsigned __fastcall Save(void);
	Dgrgdipapi::Status __fastcall Restore(unsigned gstate);
	unsigned __fastcall BeginContainer(const Dgrgdipapi::TGPRectF &dstrect, const Dgrgdipapi::TGPRectF &srcrect, Dgrgdipapi::Unit_ unit_)/* overload */;
	unsigned __fastcall BeginContainer(const Dgrgdipapi::TGPRect &dstrect, const Dgrgdipapi::TGPRect &srcrect, Dgrgdipapi::Unit_ unit_)/* overload */;
	unsigned __fastcall BeginContainer(void)/* overload */;
	Dgrgdipapi::Status __fastcall EndContainer(unsigned state);
	Dgrgdipapi::Status __fastcall AddMetafileComment(System::PByte data, unsigned sizeData);
	HPALETTE __fastcall GetHalftonePalette(void);
	Dgrgdipapi::Status __fastcall GetLastStatus(void);
};

#pragma pack(pop)

class DELPHICLASS TGPAdjustableArrowCap;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPAdjustableArrowCap : public TGPCustomLineCap
{
	typedef TGPCustomLineCap inherited;
	
public:
	__fastcall TGPAdjustableArrowCap(float height, float width, BOOL isFilled);
	Dgrgdipapi::Status __fastcall SetHeight(float height);
	float __fastcall GetHeight(void);
	Dgrgdipapi::Status __fastcall SetWidth(float width);
	float __fastcall GetWidth(void);
	Dgrgdipapi::Status __fastcall SetMiddleInset(float middleInset);
	float __fastcall GetMiddleInset(void);
	Dgrgdipapi::Status __fastcall SetFillState(BOOL isFilled);
	BOOL __fastcall IsFilled(void);
public:
	/* TGPCustomLineCap.Destroy */ inline __fastcall virtual ~TGPAdjustableArrowCap(void) { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TGPMetafile : public TGPImage
{
	typedef TGPImage inherited;
	
public:
	__fastcall TGPMetafile(HMETAFILE hWmf, Dgrgdipapi::WmfPlaceableFileHeader &wmfPlaceableFileHeader, BOOL deleteWmf)/* overload */;
	__fastcall TGPMetafile(HENHMETAFILE hEmf, BOOL deleteEmf)/* overload */;
	__fastcall TGPMetafile(System::WideString filename)/* overload */;
	__fastcall TGPMetafile(System::WideString filename, Dgrgdipapi::WmfPlaceableFileHeader &wmfPlaceableFileHeader)/* overload */;
	__fastcall TGPMetafile(_di_IStream stream)/* overload */;
	__fastcall TGPMetafile(HDC referenceHdc, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(HDC referenceHdc, const Dgrgdipapi::TGPRectF &frameRect, int frameUnit, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(HDC referenceHdc, const Dgrgdipapi::TGPRect &frameRect, int frameUnit, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(System::WideString fileName, HDC referenceHdc, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(System::WideString fileName, HDC referenceHdc, const Dgrgdipapi::TGPRectF &frameRect, int frameUnit, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(System::WideString fileName, HDC referenceHdc, const Dgrgdipapi::TGPRect &frameRect, int frameUnit, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(_di_IStream stream, HDC referenceHdc, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(_di_IStream stream, HDC referenceHdc, const Dgrgdipapi::TGPRectF &frameRect, int frameUnit, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(_di_IStream stream, HDC referenceHdc, const Dgrgdipapi::TGPRect &frameRect, int frameUnit, int type_, System::WideChar * description)/* overload */;
	__fastcall TGPMetafile(void)/* overload */;
	Dgrgdipapi::Status __fastcall GetMetafileHeader(HMETAFILE hWmf, Dgrgdipapi::WmfPlaceableFileHeader &wmfPlaceableFileHeader, Dgrgdipapi::TMetafileHeader* header)/* overload */;
	Dgrgdipapi::Status __fastcall GetMetafileHeader(HENHMETAFILE hEmf, Dgrgdipapi::TMetafileHeader* header)/* overload */;
	Dgrgdipapi::Status __fastcall GetMetafileHeader(System::WideString filename, Dgrgdipapi::TMetafileHeader* header)/* overload */;
	Dgrgdipapi::Status __fastcall GetMetafileHeader(_di_IStream stream, Dgrgdipapi::TMetafileHeader* header)/* overload */;
	Dgrgdipapi::Status __fastcall GetMetafileHeader(Dgrgdipapi::TMetafileHeader* header)/* overload */;
	HENHMETAFILE __fastcall GetHENHMETAFILE(void);
	Dgrgdipapi::Status __fastcall PlayRecord(int recordType, unsigned flags, unsigned dataSize, System::PByte data);
	Dgrgdipapi::Status __fastcall SetDownLevelRasterizationLimit(unsigned metafileRasterizationLimitDpi);
	unsigned __fastcall GetDownLevelRasterizationLimit(void);
	unsigned __fastcall EmfToWmfBits(HENHMETAFILE hemf, unsigned cbData16, System::PByte pData16, int iMapMode = 0x8, int eFlags = 0x0);
protected:
	/* TGPImage.Create */ inline __fastcall TGPMetafile(void * nativeImage, Dgrgdipapi::Status status)/* overload */ : TGPImage(nativeImage, status) { }
	
public:
	/* TGPImage.Create */ inline __fastcall TGPMetafile(System::WideString filename, BOOL useEmbeddedColorManagement)/* overload */ : TGPImage(filename, useEmbeddedColorManagement) { }
	/* TGPImage.Create */ inline __fastcall TGPMetafile(_di_IStream stream, BOOL useEmbeddedColorManagement)/* overload */ : TGPImage(stream, useEmbeddedColorManagement) { }
	/* TGPImage.Destroy */ inline __fastcall virtual ~TGPMetafile(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TGPFontFamily* GenericSansSerifFontFamily;
extern DELPHI_PACKAGE TGPFontFamily* GenericSerifFontFamily;
extern DELPHI_PACKAGE TGPFontFamily* GenericMonospaceFontFamily;
extern DELPHI_PACKAGE TGPStringFormat* GenericTypographicStringFormatBuffer;
extern DELPHI_PACKAGE TGPStringFormat* GenericDefaultStringFormatBuffer;
extern DELPHI_PACKAGE Dgrgdipapi::GdiplusStartupInput StartupInput;
extern DELPHI_PACKAGE unsigned gdiplusToken;
extern DELPHI_PACKAGE Dgrgdipapi::Status __fastcall GetImageDecodersSize(/* out */ unsigned &numDecoders, /* out */ unsigned &size);
extern DELPHI_PACKAGE Dgrgdipapi::Status __fastcall GetImageDecoders(unsigned numDecoders, unsigned size, Dgrgdipapi::PImageCodecInfo decoders);
extern DELPHI_PACKAGE Dgrgdipapi::Status __fastcall GetImageEncodersSize(/* out */ unsigned &numEncoders, /* out */ unsigned &size);
extern DELPHI_PACKAGE Dgrgdipapi::Status __fastcall GetImageEncoders(unsigned numEncoders, unsigned size, Dgrgdipapi::PImageCodecInfo encoders);
extern DELPHI_PACKAGE void __fastcall InitializeGdiPlus(void);
extern DELPHI_PACKAGE void __fastcall FinalizeGdiPlus(void);
}	/* namespace Dgrgdipobj */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DGRGDIPOBJ)
using namespace Dgrgdipobj;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DgrgdipobjHPP
