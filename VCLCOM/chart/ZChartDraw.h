#ifndef ZChartDrawH
#define ZChartDrawH
#include <windows.h>
#include <sysutils.hpp>
#include "ProjectStruct.h"
namespace ProjectStruct
{
//-------------------------------------------------------------------------
String PACKAGE PrjFormatDate(const TDateTime& dt);
POINT PACKAGE LineCircleLinkPoint(const POINT& p, const POINT& CircleCentre, int R);
void PACKAGE ArrowPoints(const POINT& p, const POINT& CircleCentre, int R, POINT* Rtn);
//-------------------------------------------------------------------------
class TLinePoint
{
public:
  int x1,y1,x2,y2;
  TLinePoint(int X1,int Y1,int X2,int Y2)
  {
    x1 = X1;
    y1 = Y1;
    x2 = X2;
    y2 = Y2;
  }
  TLinePoint(POINT p1,POINT p2)
  {
    x1 = p1.x;
    y1 = p1.y;
    x2 = p2.x;
    y2 = p2.y;
  }
};
//---------------------------------------------------------------------------
class TEventData
{
public:
  int x;
  int y;
  int EventNo;
};
//---------------------------------------------------------------------------
enum TAspect
{
  atRight, //向右
  atLeft,  //向左
  atDown,  //向下
  atUp     //向上
};
//-------------------------------------------------------------------------
class PACKAGE TPattern
{
private:
    HBITMAP FPatterns[14];
public:
    static int     Count();
    static HBITMAP Pattern(int Index);
    TPattern();
    ~TPattern();
};
//-------------------------------------------------------------------------
class PACKAGE THeadTailDraw
{
public:
    enum TFigure//形状 菱形等
    {
        fEmpty, //空心
        fTopDiamond, // 上菱形，上半部是菱形， 下半部是矩形
        fBottomDiamond, //下菱形，下半部是菱形， 上半部是矩形
        fDiamond, //菱形，
        fInsideDiamond,//内菱形，菱形在园里面
        fTriangle//三角形
    };
    enum TType//类型 点划线，空心，实心
    {
        tDash, // 点划线
        tEmpty, // 空心
        tSolid // 实心
    };
private:
public:
    TFigure  Figure;
    TType    Type;
    COLORREF Color;
    THeadTailDraw() : Figure(fEmpty), Type(tSolid), Color(0) {}
    void Draw(HDC dc, int X, int Y);//中心点
};
//-------------------------------------------------------------------------
class PACKAGE TBarDraw
{
public:
    enum TFigure//形状
    {
        fEmpty,
        fSolid,
        fTopLarge,
        fMiddleLarge,
        fBottomLarge,
        fTopSmall,
        fMiddleSmall,
        fBottomSmall
    };
private:
    void DrawImpl(HDC dc, int StartX, int EndX, int Y);
public:
    TFigure       Figure;
    int           Pattern;
    COLORREF      Color;
    COLORREF      BorderColor;
    THeadTailDraw HeadDraw;
    THeadTailDraw TailDraw;
    TBarDraw() : Figure(fSolid), Pattern(0), Color(0), BorderColor(0) {}

    void Draw(HDC dc, int StartX, int EndX, int Y);

    int  Left(int BarStartX, int BarEndX, int BarY);
    int  Top(int BarStartX, int BarEndX, int BarY, int X);
    int  Right(int BarStartX, int BarEndX, int BarY);
    int  Bottom(int BarStartX, int BarEndX, int BarY, int X);
    int  Mid(int BarY);
};
//-------------------------------------------------------------------------
class PACKAGE T1BarDraw
{
public:
    TBarDraw Bar;
    void     Draw(HDC dc, int StartX, int EndX, int Y);
};
class PACKAGE T2BarDraw
{
public:
    TBarDraw Bar1;
    TBarDraw Bar2;
    bool     Bar2Draw;
    T2BarDraw();
    void Draw(HDC dc, int StartX1, int EndX1,
                      int StartX2, int EndX2, int Y);
};
class PACKAGE T3BarDraw
{
public:
    TBarDraw Bar1;
    TBarDraw Bar2;
    TBarDraw BaseBar;
    bool     Bar2Draw;
    bool     BaseDraw;
    T3BarDraw();
    void Draw(HDC dc, int StartX1, int EndX1,
                      int StartX2, int EndX2,int BaseStartX, int BaseEndX, int Y);
};
//-------------------------------------------------------------------------
class PACKAGE TGTLinkDraw
{
private:
    void FillLinePoint(POINT*pLine, int& LineCount, POINT*pArrow, int StartX, int StartY, int EndX, int EndY);
    void FillLinePoint(POINT*pLine, int& LineCount, POINT*pArrow, int StartX, int StartY, int EndX, int EndY, int MidY);
public:
    COLORREF Color;
    TGTLinkDraw() : Color(clBlack) {}
    void Draw(HDC dc, TBarDraw&StartBar1, TBarDraw*StartBar2,
                      int StartStartX1, int StartEndX1,
                      int StartStartX2, int StartEndX2, int StartBarY,
                      int StartTop, int StartBottom,
                      TBarDraw&EndBar1, TBarDraw*EndBar2,
                      int EndStartX1, int EndEndX1,
                      int EndStartX2, int EndEndX2, int EndBarY,
                      TFrontType FrontType);
};
//-------------------------------------------------------------------------
class PACKAGE TCalendarDraw
{
public:
    enum TGTCalendarType{
        gct2Hour,//二小时
        gct6Hour,//六小时
        gctDay, //日
        gct3Day, //三日
        gctWeek, //周
        gctMonth1, //月
        gctMonth2, //月
        gctQuarter, //季度
        gctHalfYear //半年
    };
private:
    String Line1StrReturn;
    String Line2StrReturn;
    int FLanguage; //0中文,1英文
    int        FColWidth;
	bool       FShowDays;//显示日期
    TDateTime  FStartDay;
    TDateTime  FEndDay;
    String &Line1Str(TDateTime &ADate,
                         unsigned short year,
                         unsigned short month,
                         unsigned short day);
    String &Line2Str(TDateTime &ADate,
                         unsigned short year,
                         unsigned short month,
                         unsigned short day);
    int        Line1HaveLine2Count();
    void       AlignLine1(TDateTime&ADate);
    void       AlignLine2(TDateTime&ADate);
    void       IncLine1(TDateTime&ADate,
                        unsigned short year,
                        unsigned short month,
                        unsigned short day);
    void       IncLine2(TDateTime&ADate,
                        unsigned short year,
                        unsigned short month,
                        unsigned short day);
public:
    COLORREF         BackColor;
    COLORREF         FontColor;
    COLORREF         LineColor;
    TGTCalendarType  Type;
	bool             DrawLine1;
	bool             DrawLine2;
	COLORREF         Line1Color;
	COLORREF         Line2Color;
    int              ChartHeight;

	TCalendarDraw() ;

    int       GetColWidth() { return FColWidth; }
    TDateTime GetStartDay() { return FStartDay; }
    void      SetStartDay(TDateTime ADay) { FStartDay = ADay; }
	TDateTime GetEndDay() { return FEndDay; }
	void      SetEndDay(TDateTime ADay) { FEndDay = ADay; }
	void      AutoAlignStartEnd(const TDateTime&MustStart, const TDateTime&MustEnd,int LeftReserved,int RightReserved);
    int       GetDayLeft(const TDateTime& ADay);
	int       GetDayRight(const TDateTime& ADay);
    TDateTime XAtDay(const int& X);

    void      Init();
    void      Draw(HDC dc, const RECT &rect, int LineHeight);
    
	__property bool ShowDays={read=FShowDays,write=FShowDays};
	__property int Language={read=FLanguage,write=FLanguage};
};
//-------------------------------------------------------------------------
class PACKAGE TTaskShowCol
{
	String GetAbstractData(TAbstractTask&);
	String GetTaskData(TTask&);
public:
    int        DataIndex;

    String GetTitle();
    String GetData(TPrjObject&AObj);
    unsigned   GetTitleFormat();
    unsigned   GetDataFormat();
    int        DataTypeCount();
};
//-------------------------------------------------------------------------
class PACKAGE TTaskShowString
{
    TTaskShowCol* FShowCols;
    String* FSpaces;
    String FDefineString;
    int        FDefineColCount;
public:
    TTaskShowString();
    ~TTaskShowString();
    String GetShowString(TPrjObject& AObj);
    void SetDefineString(String AStr);
    String GetDefineString() { return FDefineString; }
};
//-------------------------------------------------------------------------
void DrawExpandFold(HDC dc, int X, int Y, bool Expanded);
class PACKAGE TFrameDraw
{
public:
    enum TBorderType{
         btRectangle, //矩形
         btParallelogram1,//平行四边形
         btParallelogram2,//平行四边形
         btDiamond        //菱形
         };
    enum TExpandFoldType{
         eftNone,
         eftExpanded,
         eftFolded
         };
public:
    TTaskShowCol ShowItems[10];
    TBorderType  BorderType;
    int          ItemHeight;
    COLORREF     LineColor;
    COLORREF     BkColor;
    int          BkPattern;
    int          Abstract; //0: Not a abstract, 1: expended, 2: not expended
    int          Sign;   //0: not show sign  1: show started  2: show overed
    TFrameDraw();
    void Init(HDC dc);
    void Draw(HDC dc, int Left, int Top, int Right, int Bottom, int Margin,
              TPrjObject*AObj, bool Focus = false, TExpandFoldType ExpandFold = eftNone);
};
//-------------------------------------------------------------------------
class PACKAGE TNCLinkDraw
{
private:
    void DrawBridgeLine(HDC dc, POINT Start, POINT End, int BridgePointCount, POINT*BridgePoint);
public:
    COLORREF     Color;
    TNCLinkDraw(int PWidth=1);
    int PenWidth;
    void Draw(HDC dc, POINT *p, int pCount, int CornerSize = 10);
    void DrawWidthBridge(HDC dc, POINT*p, int pCount,
                         int BridgeIndex, int BridgePointCount,
                         POINT*BridgePoint, int CornerSize = 10);
};
//-------------------------------------------------------------------------
class PACKAGE TEventDraw
{
private:
public:
    int Radial;
    COLORREF   LineColor;
    COLORREF   FontColor;
    COLORREF   BackColor;
    TFont*     EventFont;
	TEventDraw() : LineColor(clBlack), FontColor(clBlack), BackColor(clLtGray)
    {
      EventFont = new TFont();
    }
    void Init(HDC dc, int MaxEvent);
    void Draw(HDC dc, const POINT& CircleCentre, int Event, bool Focus=false);
};
//-------------------------------------------------------------------------
class PACKAGE TWaveLine
{
public:
    COLORREF   Color;
    TWaveLine() : Color(0) {}
    void Draw(HDC dc, int Left, int Top, int Right, int Bottom);
};
//-------------------------------------------------------------------------
class PACKAGE TBridgeLine
{
public:
    enum TDirection {
         bldLeft, //半圆在左边
         bldRight //半园在右边
         };
public:
    int Y;
    TDirection Direction;
    TBridgeLine() : Y(0), Direction(bldLeft) {}
    void Draw(HDC dc, int X);
    void Draw(HDC dc, int X, int Y,const int Radii);
};
//-------------------------------------------------------------------------
enum TLineStyle{
    lsBigSolid, //宽实心
    lsSmallSolid, //小实心
    lsSmallDot  //窄点划线
};
//-------------------------------------------------------------------------
class PACKAGE TTaskLine //横线
{
public:
    COLORREF   Color;
    TLineStyle Style;
    TWaveLine  WaveLine;
    TTaskLine() : Color(clBlack), Style(lsBigSolid) {}
    void Draw(HDC dc, int x1, int x2, int Wavex1, int Wavex2, int y, int R);
    void Draw(HDC dc, int x1, int x2, int Wavex1, int Wavex2, int y, int R,bool DrawArrow);
};
//-------------------------------------------------------------------------
class PACKAGE TVirtualLine //虚线
{
public:
    COLORREF   Color;
    TLineStyle Style;
    TVirtualLine() : Color(clBlack), Style(lsSmallDot) {}
    void Draw(HDC dc, const POINT& p, const POINT& CircleCentre, int R);
    void Draw(HDC dc, POINT*pLine, int& PointCount, int R);
    void Draw(HDC dc, POINT*pLine, int& PointCount, int R ,bool DrawArrow,bool DrawSolid);
    void Draw(HDC dc,TList* Line, int R ,bool DrawArrow,bool DrawSolid);
};
//-------------------------------------------------------------------------

}
//-------------------------------------------------------------------------
//#include <Jpeg.hpp>
enum TSDSavePicType {sptWmf = 1, sptBitmap = 2, sptJpeg = 3};
template <class SDChart>
void SDChartSaveAsWMF(SDChart*AChart, String FileName)
{
    HENHMETAFILE MetaFile;//矢量图
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    TSDSavePicType AType(sptWmf);
	String Ext = FileName.SubString(FileName.Length() - 3, 4);
    if(Ext.LowerCase() == ".bmp")
       AType = sptBitmap;
    else if(Ext.LowerCase() == ".jpg" || Ext.LowerCase() == "jpeg")
       AType = sptJpeg;

    switch(AType)
    {
        case sptWmf:
        {
            HDC tempdc = GetDC(0);
            int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
            int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
            int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
            int iHeightPels = GetDeviceCaps(tempdc, VERTRES);
            rect.right = double(AChart->TotalWidth * iWidthMM * 100) / double(iWidthPels);
            rect.bottom = double(AChart->TotalHeight * iHeightMM * 100) / double(iHeightPels);
            //创建矢量图
			HDC MetaFileDc = CreateEnhMetaFile(tempdc, FileName.c_str(), &rect, L"CPM---网络图");
            ReleaseDC(0, tempdc);

            rect.right = AChart->TotalWidth;
            rect.bottom = AChart->TotalHeight;
            TPrjObject* bkSelected = AChart->Project->Selected;
            AChart->Project->Selected = NULL;
            AChart->Draw(MetaFileDc, rect);
            AChart->Project->Selected = bkSelected;
            //关闭矢量图
            MetaFile = CloseEnhMetaFile(MetaFileDc);
            //删除矢量图
            DeleteEnhMetaFile(MetaFile);
            break;
        }
        case sptBitmap:
        {
            rect.right = AChart->TotalWidth;
            rect.bottom = AChart->TotalHeight;
            Graphics::TBitmap* ABitmap = new Graphics::TBitmap();
            try{
                ABitmap->Width = AChart->TotalWidth;
                ABitmap->Height = AChart->TotalHeight;
                TPrjObject* bkSelected = AChart->Project->Selected;
                AChart->Project->Selected = NULL;
                AChart->Draw(ABitmap->Canvas->Handle, rect);
                AChart->Project->Selected = bkSelected;

                ABitmap->SaveToFile(FileName);
            }__finally
            {
                delete ABitmap;
            }
            break;
        }
		case sptJpeg:
        {
            rect.right = AChart->TotalWidth;
            rect.bottom = AChart->TotalHeight;
            Graphics::TBitmap* ABitmap = new Graphics::TBitmap();
            TJPEGImage* AJpeg = new TJPEGImage();
            try{
                ABitmap->Width = AChart->TotalWidth;
                ABitmap->Height = AChart->TotalHeight;
				TPrjObject* bkSelected = AChart->Project->Selected;
                AChart->Project->Selected = NULL;
                AChart->Draw(ABitmap->Canvas->Handle, rect);
                AChart->Project->Selected = bkSelected;
				//bitmap转为JPG
                AJpeg->Assign(ABitmap);
                AJpeg->SaveToFile(FileName);
            }__finally
            {
                delete ABitmap;
                delete AJpeg;
            }
            break;
        }
    }
}
#endif
