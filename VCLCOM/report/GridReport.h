//---------------------------------------------------------------------------

#ifndef GridReportH
#define GridReportH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "ZGrid.h"
#include "RoomGrid.h"
#include <Printers.hpp>
#include "ZPrintView.h"
//#include "BRichedeh.hpp"
//---------------------------------------------------------------------------
struct PrintEnvir
{
   int GridXPixelInch;
   int GridYPixelInch;
   int DrawXPixelInch;
   int DrawYPixelInch;
   int PhysicalOffsetX;
   int PhysicalOffsetY;
   double DrawSize;
   int Size;
};
enum TPrintContentType {pctGrid,pctBeforeGridText,pctAfterGridText};
struct PrintPage{
   int Left;
   int Right;
   int Top;
   int Bottom;
   bool Adjust;
   TPrintContentType type;
};
enum TPageColontitleLineType { pcltNon, pcltSingleLine, pcltDoubleLine };
class TGridReport;
class TReportView;
class PACKAGE TPageColontitle : public TPersistent
{

public:
        virtual void __fastcall Assign(TPersistent * Source);
        __fastcall TPageColontitle();
        virtual __fastcall ~TPageColontitle();
private:
        TStrings* FCenterText;
        TFont* FFont;
        TStrings* FLeftText;
        TStrings* FRightText;
        TPageColontitleLineType FLineType;
        void __fastcall SetCenterText(TStrings* value);
        void __fastcall SetFont(TFont* value);
        void __fastcall SetLeftText(TStrings* value);
        void __fastcall SetRightText(TStrings* value);
        void __fastcall SetLineType(TPageColontitleLineType value);
__published:
        __property TStrings* CenterText  = { read=FCenterText, write=SetCenterText };
        __property TFont* Font  = { read=FFont, write=SetFont };
        __property TStrings* LeftText  = { read=FLeftText, write=SetLeftText };
        __property TStrings* RightText  = { read=FRightText, write=SetRightText };
        __property TPageColontitleLineType LineType  = { read=FLineType, write=SetLineType, default=0 };
};
class PACKAGE TGridReport : public TComponent
{
private:
	 TZGrid* FGrid;
     TRoomGrid* FRoomGrid;
	 TFont* FTitleFont;
     int FPageWidth;
     int FPageHeight;
     int FSize;
     int FLeftMargin;
     int FRightMargin;
     int FTopMargin;
     int FBottomMargin;
     int FTitleSpace;
     bool FShowHorzLine, FShowVertLine;
     Printers::TPrinterOrientation FOrientation;
     String FPrinter;
     String FTitle;
     int FPageCount;
     void __fastcall SetGrid(TZGrid*AGrid);
     void __fastcall SetHouseGrid(TRoomGrid*AGrid);
     void __fastcall SetTitleFont(TFont* AFont);

     void DrawAPage(HDC dc, PrintEnvir&Envir, PrintPage*APage, int Index);
     int DrawBOrAGridText(HDC dc, PrintEnvir& Envir, TRect ARect,String Text, int & PrintTop);
     int DrawPageColonText(HDC dc, PrintEnvir&Envir, TRect ARect,bool IsHeader, bool CalcHeight);
//        int __fastcall DrawRichText(HDC dc, bool CalcInfoMode, TRichEditStrings* Strings,PrintEnvir&Envir,int &PrintTop);
     int DrawARow(HDC dc, PrintEnvir&Envir, PrintPage*APage, int Row, int &PrintTop, double CellScale);
     void DrawACell(HDC dc, PrintEnvir&Envir, TRect r, String Str, TColHorAlign HAlign,TColor bkColor,bool MultyLine=false,TRowVerAlign VAlign=vaMiddle);
     void DrawCellItem(HDC CanvasHandle,String sDrawText,TRect &DrawRect,UINT dpAlign,int StepHeight);
     void HDrawACell(HDC dc,PrintEnvir&Envir,  TRect r, TCells *Cells,TColHorAlign, TColor bkColor);
     void DrawPageNo(HDC dc, PrintEnvir&Envir, int No);
     void DrawPageTitle(HDC dc, PrintEnvir&Envir,int &PrintTop);
     void DrawGridFooter(HDC dc, PrintEnvir& Envir, PrintPage* APage, int & PrintTop, double CellScale);
     void DrawExpandFold(HDC dc, PrintEnvir&Envir, int X, int Y, bool Expanded);
     void DrawExpandFoldCell(HDC dc, PrintEnvir&Envir, TRect &ARect, String& AString, int Layer, int ExpandType);
     PrintPage* FPages;
     //XPageCount:  -2:不调整  -1 根据实际自动调整   > 0:调整到XPageCount宽
     double FDrawSize;

     HFONT    hFont;
     HGDIOBJ  goFont;
     HFONT    hTitleFont;
        TStrings* FAfterGridText;
        TStrings* FBeforeGridText;
        TPageColontitle* FPageFooter;
        TPageColontitle* FPageHeader;
        int FPageHeaderHeight;
        int FPageFooterHeight;
        bool FPrintHeader;
        bool FPrintFooter;
     int TextWidth(HDC dc, String Text);
     int TextHeight(HDC dc, String Text);
        void __fastcall SetAfterGridText(TStrings* value);
        TStrings* __fastcall GetAfterGridText();
        void __fastcall SetBeforeGridText(TStrings* value);
        TStrings* __fastcall GetBeforeGridText();
        void __fastcall SetPageFooter(TPageColontitle* value);
        void __fastcall SetPageHeader(TPageColontitle* value);
        int __fastcall GetRichTextHeight(HDC dc, TStrings* String);
        int __fastcall GetTitleHeight(HDC dc);
protected:
     void __fastcall Notification(TComponent* AComponent, TOperation Operation);
     TRect AnalysisCellRect(int Col, int Row, PrintPage*APage);
     TRect CellSize(int Left, int Top, int Right, int Bottom, PrintPage*APage);
//     __property int XPageCount = {read=SetXPageCount, write=FXPageCount};
      HFONT __fastcall CreateFontFromTFont(TFont *AFont,PrintEnvir&Envir);

public:
     __fastcall TGridReport(TComponent* Owner);
     __fastcall ~TGridReport();
     void BuildPages();
     void __fastcall Print();
     bool Printing;
     void __fastcall Preview(TReportView* AView);
     void __fastcall PaintAPage(HDC dc, int No, double ASize);
     void __fastcall PageSet(bool AutoPrint = false, bool AutoPreview = false);
     __property String Printer = {read=FPrinter, write=FPrinter};
__published:
	 __property TZGrid* Grid = {read=FGrid, write=SetGrid};
	 __property TRoomGrid* RoomGrid = {read=FRoomGrid, write=SetHouseGrid};
     __property TFont* TitleFont = {read=FTitleFont, write=SetTitleFont};
     __property int PageWidth = {read=FPageWidth, write=FPageWidth};
     __property int PageHeight = {read=FPageHeight, write=FPageHeight};
     __property int Size = {read=FSize, write=FSize};
     __property int LeftMargin = {read=FLeftMargin, write=FLeftMargin};
     __property int RightMargin = {read=FRightMargin, write=FRightMargin};
     __property int TopMargin = {read=FTopMargin, write=FTopMargin};
     __property int BottomMargin = {read=FBottomMargin, write=FBottomMargin};
     __property String Title = {read=FTitle, write=FTitle};
     __property int PageCount = {read=FPageCount};
     __property Printers::TPrinterOrientation Orientation = {read=FOrientation, write=FOrientation};
     __property bool ShowHorzLine = {read=FShowHorzLine, write=FShowHorzLine};
     __property bool ShowVertLine = {read=FShowVertLine, write=FShowVertLine};
        __property TPageColontitle* PageFooter  = { read=FPageFooter, write=SetPageFooter };
        __property TPageColontitle* PageHeader  = { read=FPageHeader, write=SetPageHeader };
        __property int PageHeaderHeight  = { read=FPageHeaderHeight, write=FPageHeaderHeight };
        __property int PageFooterHeight  = { read=FPageFooterHeight, write=FPageFooterHeight };
        __property bool PrintHeader  = { read=FPrintHeader, write=FPrintHeader };
        __property bool PrintFooter  = { read=FPrintFooter, write=FPrintFooter };
        __property TStrings* AfterGridText  = { read=GetAfterGridText, write=SetAfterGridText };
        __property TStrings* BeforeGridText  = { read=GetBeforeGridText, write=SetBeforeGridText };

};
//---------------------------------------------------------------------------
class PACKAGE TReportView : public TWinControl
{
private:
    TGridReport* FGridReport;
    int FZoom;
    int FPage;
    TRptViewPageHAlign FHAlign;
    TRptViewPageVAlign FVAlign;
    void __fastcall SetZoom(int AZoom);
    void __fastcall SetPage(int APage);
    void __fastcall SetHAlign(TRptViewPageHAlign Value);
    void __fastcall SetVAlign(TRptViewPageVAlign Value);
    MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
protected:
public:
    __fastcall TReportView(TComponent* Owner);
    void First();
    void Prior();
    void Next();
    void Last();
    void Print();
    void ZoomIn();
    void ZoomOut();
    void View(TGridReport* AReport);
BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
END_MESSAGE_MAP(TWinControl);
__published:
    __property TGridReport* GridReport = {read=FGridReport, write=FGridReport};
    __property int Zoom = {read=FZoom, write=SetZoom};
    __property int Page = {read=FPage, write=SetPage};
    __property TRptViewPageHAlign HAlign = {read=FHAlign, write=SetHAlign};
    __property TRptViewPageVAlign VAlign = {read=FVAlign, write=SetVAlign};
};

#endif
