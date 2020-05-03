//---------------------------------------------------------------------------

#ifndef ZPrintViewH
#define ZPrintViewH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Printers.hpp>
#include "PrintInterface.h"
//---------------------------------------------------------------------------
//#define TPrintHandle void*
extern double ShowSizes[10];
enum TRptViewPageHAlign {rvpaHMid, rvpaLeft, rvpaRight};
enum TRptViewPageVAlign {rvpaVMid, rvpaTop, rvpaBottom};
class PACKAGE TPrintView : public TWinControl
{
private:
	TPrintInterface* FPrintHandle;
    HENHMETAFILE MetaFile;
    Graphics::TBitmap* FShowPage;
    int FZoom;
    int FPage;
    int FPageSize;  //÷Ω’≈¥Û–°
    void __fastcall SetZoom(int AZoom);
    void __fastcall SetPage(int APage);
    MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
	void __fastcall SetPrintHandle(TPrintInterface* Value);
public:
    __fastcall TPrintView(TComponent* Owner);
    __fastcall ~TPrintView();
    void RefreshPage();
    void First();
    void Prior();                                                 
    void Next();
    void Last();                                              
    void Print();
    void ZoomIn();                                 
    void ZoomOut();

	__property TPrintInterface* PrintHandle = {read=FPrintHandle, write=SetPrintHandle};

BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
END_MESSAGE_MAP(TWinControl);
__published:
    __property int Zoom = {read=FZoom, write=SetZoom};
    __property int Page = {read=FPage, write=SetPage};
//support for printhandle
private:
     int __fastcall GetPageWidthMm();
     void __fastcall SetPageWidthMm(int Value);
     int __fastcall GetPageHeightMm();
     void __fastcall SetPageHeightMm(int Value);
     int __fastcall GetPageCount();
     int __fastcall GetLeftMarginMm();
     void __fastcall SetLeftMarginMm(int Value);
     int __fastcall GetRightMarginMm();
     void __fastcall SetRightMarginMm(int Value);
     int __fastcall GetTopMarginMm();
     void __fastcall SetTopMarginMm(int Value);
     int __fastcall GetBottomMarginMm();
     void __fastcall SetBottomMarginMm(int Value);
	 Printers::TPrinterOrientation __fastcall GetOrientation();
	 void __fastcall SetOrientation(Printers::TPrinterOrientation);

     String __fastcall GetTitle();
     void __fastcall SetTitle(String ATitle);
     TFont*__fastcall GetTitleFont();
     void __fastcall SetTitleFont(TFont*AFont);
     bool __fastcall GetShowPageNo();
     void __fastcall SetShowPageNo(bool AValue);
     String __fastcall GetProperty(int Index);
     void __fastcall SetProperty(int Index, String Value);
     String __fastcall GetPropertyName(int Index);
     int __fastcall GetPropertyCount();
public:
     __property int PageWidthMm = {read=GetPageWidthMm, write=SetPageWidthMm};
     __property int PageHeightMm = {read=GetPageHeightMm, write=SetPageHeightMm};
     __property int PageCount = {read=GetPageCount};
     __property int LeftMarginMm = {read=GetLeftMarginMm, write=SetLeftMarginMm};
     __property int RightMarginMm = {read=GetRightMarginMm, write=SetRightMarginMm};
     __property int TopMarginMm = {read=GetTopMarginMm, write=SetTopMarginMm};
     __property int BottomMarginMm = {read=GetBottomMarginMm, write=SetBottomMarginMm};
     __property Printers::TPrinterOrientation Orientation = {read=GetOrientation, write=SetOrientation};
     __property int PageSize = {read=FPageSize, write=FPageSize};
     __property String Title = {read=GetTitle, write=SetTitle};
     __property TFont* TitleFont = {read=GetTitleFont, write=SetTitleFont};
     __property bool ShowPageNo = {read=GetShowPageNo, write=SetShowPageNo};
     __property String Property[int Index] = {read=GetProperty, write=SetProperty};
	 __property String PropertyName[int Index] = {read=GetPropertyName};
     __property int PropertyCount = {read=GetPropertyCount};
};
//---------------------------------------------------------------------------
#endif
