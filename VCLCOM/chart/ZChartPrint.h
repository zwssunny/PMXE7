#ifndef ZChartPrintH
#define ZChartPrintH
//---------------------------------------------------------------------------
#include "PrintInterface.h"
#include "Gantt.h"
#include "NetChart.h"
#include "LogicalChart.h"
#include "DoubleCode.h"
#include "PrjGrid.h"
//---------------------------------------------------------------------------
class PACKAGE TGanttPrint : public TPrintInterface
{
private:
     TGantt *FChart;
     int XLength();
     int YLength();
     int __fastcall GetPageCount();
     int __fastcall GetPropertyCount(){ return 0; }
     String __fastcall GetName();
     int GridWidth();
     HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
     void PaintGrid(HDC dc, RECT dr);

public:
	 TGanttPrint(TGantt* AChart);
};
class PACKAGE TGanttSetPrint : public TPrintInterface
{
private:
        TGanttSet AGanttSet;
        int XLength();
        int YLength();
        int __fastcall GetPageCount();
        int __fastcall GetPropertyCount(){ return 0; }
        String __fastcall GetName();
        HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
        void DrawRect(HDC DC,RECT rect,int iPattern,TColor pcolor);
        void DrawSetText(HDC DC,RECT rect,String text,TFont *textFont,TColor pcolor=clBlack);
        void DrawGanttSet(HDC DC,RECT rect);
public:
		TGanttSetPrint(TGanttSet ASet);
};
//----------------------------------------------------------------------------
class PACKAGE TNetChartPrint : public TPrintInterface
{
private:
     TNetChart *FChart;
     int XLength();
     int YLength();
     void ClearMargin(HDC dc);
     int __fastcall GetPageCount();
     void PaintAPageImpl(HDC dc, int PageNo);
     HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
     int __fastcall GetPropertyCount(){ return 0; }
     String __fastcall GetName();
public:
	 TNetChartPrint(TNetChart* AChart);
};
//----------------------------------------------------------------------------
//class TOrgChartPrint : public TPrintInterface
//{
//private:
//     TOrgChart *FChart;
//     int XLength();
//     int YLength();
//     void ClearMargin(HDC dc);
//     int __fastcall GetPageCount();
//     void PaintAPageImpl(HDC dc, int PageNo);
//     HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
//     int __fastcall GetPropertyCount(){ return 0; }
//     String __fastcall GetName();
//public:
//     TOrgChartPrint(TOrgChart* AChart);
//};
//----------------------------------------------------------------------------
class PACKAGE TLogicalChartPrint : public TPrintInterface
{
private:
     TLogicalChart *FChart;
     int XLength();
     int YLength();
     int __fastcall GetPageCount();
     void PaintAPageImpl(HDC dc, int PageNo);
     HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
     int __fastcall GetPropertyCount(){ return 0; }
     String __fastcall GetName();
public:
	 TLogicalChartPrint(TLogicalChart* AChart);
};
//----------------------------------------------------------------------------
class PACKAGE TDoubleCodePrint : public TPrintInterface
{
private:
     TDoubleCode *FChart;
     int XLength();
	 int YLength();
     void ClearMargin(HDC dc);
     int __fastcall GetPageCount();
     HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
     int __fastcall GetPropertyCount(){ return 0; }
     String __fastcall GetName();
public:
	 TDoubleCodePrint(TDoubleCode* AChart);
};
class PACKAGE TNetChartSetPrint : public TPrintInterface
{
private:
     TNetChart *FNetChart;
     int XLength(){return 1; }
     int YLength(){return 1; }
     int __fastcall GetPageCount(){return 1;}
     int __fastcall GetPropertyCount(){ return 0; }
     String __fastcall GetName(){return "NetChartSet";}
     HENHMETAFILE __fastcall MakeMetalFile( int PageNo);
     void DrawSetText(HDC DC,RECT rect,String text,TFont *textFont,TColor pcolor=clBlack);
     void DrawGridTitle(HDC DC,RECT rect,TFont *textFont);     
     void DrawBGColorRect(HDC DC,TFrameDraw *FrameDraw,RECT rect);
     void DrawBordStyleRect(HDC DC,TFrameDraw *FrameDraw,RECT rect);
     void DrawPatternRect(HDC DC,TFrameDraw *FrameDraw,RECT rect);
     void DrawLineColorRect(HDC DC,TFrameDraw *FrameDraw,RECT rect);
     void DrawSignRect(HDC DC,TFrameDraw *FrameDraw,RECT rect);
	 void DrawNetSetRow(HDC DC,TFrameDraw *FrameDraw,RECT rect,String text,TFont *textFont);
     void DrawNetSet(HDC DC,RECT rect);
public:
		TNetChartSetPrint(TNetChart * Chart);
};

//----------------------------------------------------------------------------
#endif
