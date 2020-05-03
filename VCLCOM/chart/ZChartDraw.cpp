//---------------------------------------------------------------------------
//    File:               ZChartDraw.h, ZChartDraw.cpp
//    Function:           画图型构件，包括甘特图，网络图，双代号网络图
//    Author:             Sunny Zhan
//    Last Modify:        2009-08-20
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "ZChartDraw.h"
#include "vclComFunc.h"
#pragma package(smart_init)
using namespace Vclcomfunc;
namespace ProjectStruct
{
//---------------------------------------------------------------------------
//ptTriangle是箭头的顶点坐标
//Aspect:0向右,1向左,2向下,3向上
void DrawTriangle(HDC dc,TPoint ptTriangle,TAspect aspect)
{
  TPoint points[4];
  switch(aspect)
  {
    case atRight:
      points[0].x = ptTriangle.x - 8;
      points[0].y = ptTriangle.y - 3;
      points[1].x = ptTriangle.x - 8;
      points[1].y = ptTriangle.y + 3;
      break;
    case atLeft:
      points[0].x = ptTriangle.x + 8;
      points[0].y = ptTriangle.y - 3;
      points[1].x = ptTriangle.x + 8;
      points[1].y = ptTriangle.y + 3;
      break;
    case atUp:
      points[0].x = ptTriangle.x - 3;
      points[0].y = ptTriangle.y + 8;
      points[1].x = ptTriangle.x + 8;
	  points[1].y = ptTriangle.y + 3;
      break;
    case atDown:
      points[0].x = ptTriangle.x - 3;
      points[0].y = ptTriangle.y - 8;
      points[1].x = ptTriangle.x - 8;
      points[1].y = ptTriangle.y + 3;
      break;
    default:
      points[0].x = 0;
      points[0].y = 0;
      points[1]   = points[0];
      points[2]   = points[0];
      points[3]   = points[0];
    break;
  }
  points[2]   = ptTriangle;
  points[3]   = points[0];

  TCanvas *cv = new TCanvas();
  cv->Handle = dc;
  cv->Polyline(points,4);
  delete cv;
}
//---------------------------------------------------------------------------

String PrjFormatDate(const TDateTime& dt)
{
    if(double(dt) <= 1)
       return "";
    return const_cast< TDateTime* >(&dt)->FormatString("yyyy-mm-dd");
}
POINT LineCircleLinkPoint(const POINT& P, const POINT& CircleCentre, int R)
{
    POINT rtn;
    if(abs(P.y - CircleCentre.y) <= 2)
    {
        rtn.y = CircleCentre.y;
        if(P.x < CircleCentre.x)
        {
            rtn.x = CircleCentre.x - R;
        }else
        {
            rtn.x = CircleCentre.x + R;
        }
	}else if(abs(P.x - CircleCentre.x) <= 2)
	{
		rtn.x = CircleCentre.x;
		if(P.y < CircleCentre.y)
		{
			rtn.y = CircleCentre.y - R;
		}else
		{
			rtn.y = CircleCentre.y + R;
		}
	}else
	{
		POINT tp;
		tp.x = P.x - CircleCentre.x;
		tp.y = P.y - CircleCentre.y;
		double line_d = double(tp.y) / double(tp.x);
		double line_k = P.y - line_d * P.x;

		float fR = R;
		float f = (float)sqrt(1 + line_d * line_d);
		int ik = abs(int(line_d));
		float fk = ik>10 ? 1 : ik>=7? 1+(10-ik)/10.0 : 2;
		if((fR/f)<fk) fR = fk * f *1.1;

		if(P.x < CircleCentre.x)
        {
			rtn.x = -(fR / sqrt(1 + line_d * line_d));
			rtn.x += CircleCentre.x;
			rtn.y = line_d * rtn.x + line_k;
		}else
		{
			rtn.x = fR / sqrt(1 + line_d * line_d);
			rtn.x += CircleCentre.x;
			rtn.y = line_d * rtn.x + line_k;
		}
	}
	return rtn;
}
int const glArrowWidth = 10;
int const glArrowHeight = 4;
void ArrowPoints(const POINT& P, const POINT& CircleCentre, int R, POINT* Rtn)
{
    Rtn[0] = LineCircleLinkPoint(P, CircleCentre, R);
    if(abs(P.y - CircleCentre.y) <= 2)
    {
        Rtn[1].x = Rtn[0].x - ((P.x < CircleCentre.x) ? glArrowWidth : -glArrowWidth);
        Rtn[1].y = Rtn[0].y - glArrowHeight;
        Rtn[2].x = Rtn[1].x;
        Rtn[2].y = Rtn[0].y + glArrowHeight;
        Rtn[3] = Rtn[0];
    }else if(abs(P.x - CircleCentre.x) <= 2)
    {
        Rtn[1].x = Rtn[0].x - glArrowHeight;
        Rtn[1].y = Rtn[0].y - ((P.y < CircleCentre.y) ? glArrowWidth : -glArrowWidth);
        Rtn[2].x = Rtn[0].x + glArrowHeight;
        Rtn[2].y = Rtn[1].y;
        Rtn[3] = Rtn[0];
    }else
    {
        POINT temp = LineCircleLinkPoint(P, Rtn[0], glArrowWidth);
        double line_d = - (double(P.x - CircleCentre.x) / double(P.y - CircleCentre.y));
        double line_k = temp.y - line_d * temp.x;
        POINT rtn1, rtn2;
        rtn1.x = -(glArrowHeight / sqrt(1 + line_d * line_d));
        rtn1.x += temp.x;
        rtn1.y = line_d * rtn1.x + line_k;

        rtn2.x = glArrowHeight / sqrt(1 + line_d * line_d);
        rtn2.x += temp.x;
        rtn2.y = line_d * rtn2.x + line_k;

        Rtn[1] = rtn1;
        Rtn[2] = rtn2;
        Rtn[3] = Rtn[0];
    }
}
//---------------------------------------------------------------------------
//  TPattern
//---------------------------------------------------------------------------
TPattern::TPattern()
{
    UINT FBrushBits[8];
    //0
    //00000000    00000000  solid
    for(int i = 0; i < 8; i++)
        FBrushBits[i] = 0x0;
    FPatterns[0] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //1
    //1111111     11111111  empty
    for(int i = 0; i < 8; i++)
        FBrushBits[i] = 0x00ff00ff;
    FPatterns[1] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //2
    //10101010     01010101
    FBrushBits[0] = 0xAAAAAAAA;
    FBrushBits[1] = 0x55555555;
    FBrushBits[2] = 0xAAAAAAAA;
    FBrushBits[3] = 0x55555555;
    FBrushBits[4] = 0xAAAAAAAA;
    FBrushBits[5] = 0x55555555;
    FBrushBits[6] = 0xAAAAAAAA;
    FBrushBits[7] = 0x55555555;
    FPatterns[2] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //3
    //00100010     10001000
    FBrushBits[0] = 0x22222222;
    FBrushBits[1] = 0x88888888;
    FBrushBits[2] = 0x22222222;
    FBrushBits[3] = 0x88888888;
    FBrushBits[4] = 0x22222222;
    FBrushBits[5] = 0x88888888;
    FBrushBits[6] = 0x22222222;
    FBrushBits[7] = 0x88888888;
    FPatterns[3] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //4
    //10111011     11101110
    FBrushBits[0] = 0xBBBBBBBB;
    FBrushBits[1] = 0xEEEEEEEE;
    FBrushBits[2] = 0xBBBBBBBB;
    FBrushBits[3] = 0xEEEEEEEE;
    FBrushBits[4] = 0xBBBBBBBB;
    FBrushBits[5] = 0xEEEEEEEE;
    FBrushBits[6] = 0xBBBBBBBB;
    FBrushBits[7] = 0xEEEEEEEE;
    FPatterns[4] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //5
    //11011101:dd   11101110:ee   01110111:77   10111011:bb 右斜
    FBrushBits[0] = 0xDDDDDDDD;
    FBrushBits[1] = 0xEEEEEEEE;
    FBrushBits[2] = 0x77777777;
    FBrushBits[3] = 0xBBBBBBBB;
    FBrushBits[4] = 0xDDDDDDDD;
    FBrushBits[5] = 0xEEEEEEEE;
    FBrushBits[6] = 0x77777777;
    FBrushBits[7] = 0xBBBBBBBB;
    FPatterns[5] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //6
    //10111011:bb   01110111:77   11101110:ee   11011101:dd 左斜
    FBrushBits[0] = 0xBBBBBBBB;
    FBrushBits[1] = 0x77777777;
    FBrushBits[2] = 0xEEEEEEEE;
    FBrushBits[3] = 0xDDDDDDDD;
    FBrushBits[4] = 0xBBBBBBBB;
    FBrushBits[5] = 0x77777777;
    FBrushBits[6] = 0xEEEEEEEE;
    FBrushBits[7] = 0xDDDDDDDD;
    FPatterns[6] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //7
    //10111011:bb   01010101:55   11101110:ee   01010101:55
    FBrushBits[0] = 0xBBBBBBBB;
    FBrushBits[1] = 0x55555555;
    FBrushBits[2] = 0xEEEEEEEE;
    FBrushBits[3] = 0x55555555;
    FBrushBits[4] = 0xBBBBBBBB;
    FBrushBits[5] = 0x55555555;
    FBrushBits[6] = 0xEEEEEEEE;
    FBrushBits[7] = 0x55555555;
    FPatterns[7] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //8
    //00100010:22 竖条粗
    for(int i = 0; i < 8; i++)
       FBrushBits[i] = 0x22222222;
    FPatterns[8] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //9
    //11011101:dd 竖条细
    for(int i = 0; i < 8; i++)
       FBrushBits[i] = 0xDDDDDDDD;
    FPatterns[9] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //10 间隔横条
    FBrushBits[0] = 0xFFFFFFF;
    FBrushBits[1] = 0x0;
    FBrushBits[2] = 0xFFFFFFF;
    FBrushBits[3] = 0x0;
    FBrushBits[4] = 0xFFFFFFF;
    FBrushBits[5] = 0x0;
    FBrushBits[6] = 0xFFFFFFF;
    FBrushBits[7] = 0x0;

    FPatterns[10] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //11 间隔竖条
    for(int i = 0; i < 8; i++)
       FBrushBits[i] = 0xFEFEFEFE;
    FPatterns[11] = CreateBitmap(8, 8, 1, 1, FBrushBits);
    //12
    // 右斜
    FBrushBits[0] = 0xFEFEFEFE;
    FBrushBits[1] = 0x7F7F7F7F;
    FBrushBits[2] = 0xBFBFBFBF;
    FBrushBits[3] = 0xDFDFDFDF;
    FBrushBits[4] = 0xEFEFEFEF;
    FBrushBits[5] = 0xF7F7F7F7;
    FBrushBits[6] = 0xFBFBFBFB;
    FBrushBits[7] = 0xFDFDFDFD;
    FPatterns[12] = CreateBitmap(8, 8, 1, 1, FBrushBits);

    //13
    //  左斜
    FBrushBits[7] = 0xFEFEFEFE;
    FBrushBits[6] = 0x7F7F7F7F;
    FBrushBits[5] = 0xBFBFBFBF;
    FBrushBits[4] = 0xDFDFDFDF;
    FBrushBits[3] = 0xEFEFEFEF;
    FBrushBits[2] = 0xF7F7F7F7;
    FBrushBits[1] = 0xFBFBFBFB;
    FBrushBits[0] = 0xFDFDFDFD;
    FPatterns[13] = CreateBitmap(8, 8, 1, 1, FBrushBits);

}
//---------------------------------------------------------------------------
TPattern::~TPattern()
{
    for(int i = 0; i < Count(); i++)
    {
        DeleteObject(FPatterns[i]);
    }
}
//---------------------------------------------------------------------------
int TPattern::Count()
{
    return 14;
}
//---------------------------------------------------------------------------
HBITMAP TPattern::Pattern(int Index)
{
    static TPattern PatternObject;

    if(Index >= 0 && Index < PatternObject.Count())
        return PatternObject.FPatterns[Index];
    return NULL;
}
//---------------------------------------------------------------------------
//   THeadTailDraw
//---------------------------------------------------------------------------
void THeadTailDraw::Draw(HDC dc, int X, int Y)//中心点
{
    POINT p[6];
    int pcount;
    switch(Figure)
    {
        case fEmpty: //空心
            return;
        case fTopDiamond: // 上菱形，上半部是菱形， 下半部是矩形
            p[0].x = X;          //                X  0
            p[0].y = Y - 4;      //               X X
            p[1].x = X + 5;      //              X   X
            p[1].y = Y + 1;      //             X     X
            p[2].x = X + 5;      //            X       X
            p[2].y = Y + 7;      //        4  X    X    X  1
            p[3].x = X - 5;      //           X         X
            p[3].y = Y + 7;      //           X         X
            p[4].x = X - 5;      //           X         X
            p[4].y = Y + 1;      //           X         X
            pcount = 5;          //        3  XXXXXXXXXXX  2
            break;
        case fBottomDiamond: //下菱形，下半部是菱形， 上半部是矩形
            p[0].x = X - 5;      //        0  XXXXXXXXXXX 1
            p[0].y = Y - 7;      //           X         X
            p[1].x = X + 5;      //           X         X
            p[1].y = Y - 7;      //           X         X
            p[2].x = X + 5;      //           X         X
            p[2].y = Y - 1;      //        4  X    X    X  2
            p[3].x = X;          //            X       X
            p[3].y = Y + 4;      //             X     X
            p[4].x = X - 5;      //              X   X
            p[4].y = Y  -1;      //               X X
            pcount = 5;          //                X  3
            break;
        case fDiamond: //菱形，
            p[0].x = X;          //              0 X
            p[0].y = Y - 5;      //               X X
            p[1].x = X + 5;      //              X   X
            p[1].y = Y;          //             X     X
            p[2].x = X;          //            X       X
            p[2].y = Y + 5;      //        3  X    X    X  1
            p[3].x = X - 5;      //            X       X
            p[3].y = Y;          //             X     X
            p[4].x = X;          //              X   X
            p[4].y = Y;          //               X X
            pcount = 4;          //                X  2
            break;
        case fInsideDiamond://内菱形，菱形在园里面
        {
            p[0].x = X;          //              X X X
            p[0].y = Y - 3;      //             X     X         0
            p[1].x = X + 3;      //            X   X   X
            p[1].y = Y;          //           X   X X   X
            p[2].x = X;          //           X  X   X  X
            p[2].y = Y + 3;      //           X X  X  X X   3        1
            p[3].x = X - 3;      //           X  X   X  X
            p[3].y = Y;          //           X   X X   X
            p[4].x = X;          //            X   X   X
            p[4].y = Y;          //             X     X         2
            pcount = 4;          //              X X X2
            HPEN pen = CreatePen(PS_SOLID, 1, Color);
            HGDIOBJ oldpen = SelectObject(dc, pen);
            Ellipse(dc, X-5, Y-5, X+6, Y+6);
            SelectObject(dc, oldpen);
            DeleteObject(pen);
            break;
        }
        case fTriangle://三角形
            p[0].x = X;          //              0 X
            p[0].y = Y - 7;      //               X X
            p[1].x = X + 7;      //
            p[1].y = Y + 7;      //
            p[2].x = X - 7;      //
            p[2].y = Y + 7;      //                X
            p[3].x = X;          //
            p[3].y = Y - 7;      //
            p[4].x = X;          //
            p[4].y = Y;          //
            pcount = 3;          //   2       XXXXXXXXXXX       1
            break;
        default:
            pcount = 0;
    }
    p[pcount] = p[0];
    pcount++;
    switch(Type)
    {
        case tDash: // 点划线
        {
            HPEN pen = CreatePen(PS_DOT, 1, Color);
            HGDIOBJ oldpen = SelectObject(dc, pen);
            Polyline(dc, p, pcount);
            SelectObject(dc, oldpen);
            DeleteObject(pen);
            break;
        }
        case tEmpty: // 空心
        {
            HPEN pen = CreatePen(PS_SOLID, 1, Color);
            HGDIOBJ oldpen = SelectObject(dc, pen);
            HBRUSH brush = CreateSolidBrush(clWhite);
            HGDIOBJ oldbrush = SelectObject(dc, brush);
            Polygon(dc, p, pcount);
            SelectObject(dc, oldpen);
            DeleteObject(pen);
            SelectObject(dc, oldbrush);
            DeleteObject(brush);
            break;
        }
        case tSolid: // 实心
        {
            HBRUSH brush = CreateSolidBrush(Color);
            HGDIOBJ oldbrush = SelectObject(dc, brush);
            Polygon(dc, p, pcount);
            SelectObject(dc, oldbrush);
            DeleteObject(brush);
            break;
        }
        default:;
    }
}
//---------------------------------------------------------------------------
//   TTaskDraw
//---------------------------------------------------------------------------
void TBarDraw::Draw(HDC dc, int StartX, int EndX, int Y)//中心点
{
    HPEN Pen;
    HGDIOBJ oldPen;
    Pen = CreatePen(PS_SOLID, 1, BorderColor);    //1
    oldPen = SelectObject(dc, Pen);

    DrawImpl(dc, StartX, EndX, Y);
    HeadDraw.Draw(dc, StartX, Y);
    TailDraw.Draw(dc, EndX, Y);

    SelectObject(dc, oldPen);
    DeleteObject(Pen);
}
//---------------------------------------------------------------------------
void TBarDraw::DrawImpl(HDC dc, int StartX, int EndX, int Y)
{
    if(StartX == EndX)
        return;
    RECT rect;
    switch(Figure)
    {
        case fEmpty:
            return;
        case fSolid:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y - 7;
            rect.bottom = Y + 8;
            break;
        case fTopLarge:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y - 7;
            rect.bottom = Y;
            break;
        case fMiddleLarge:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y - 3;
            rect.bottom = Y + 4;
            break;
        case fBottomLarge:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y;
            rect.bottom = Y + 7;
            break;
        case fTopSmall:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y - 7;
            rect.bottom = Y - 4;
            break;
        case fMiddleSmall:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y - 2;
            rect.bottom = Y + 3;
            break;
        case fBottomSmall:
            rect.left = StartX;
            rect.right = EndX;
            rect.top = Y + 5;
            rect.bottom = Y + 8;
            break;
        default:
            throw Exception("条形图形状未定义");
    }
    COLORREF oldcolor = SetTextColor(dc, Color);

    HBRUSH Brush;
    HGDIOBJ oldBrush;
    Brush= CreatePatternBrush(TPattern::Pattern(Pattern));
    oldBrush = SelectObject(dc, Brush);

    Rectangle(dc, rect.left, rect.top, rect.right, rect.bottom);

    SelectObject(dc, oldBrush);
    DeleteObject(Brush);
    SetTextColor(dc, oldcolor);
}
//---------------------------------------------------------------------------
int TBarDraw::Left(int BarStartX, int BarEndX, int BarY)
{
    if(HeadDraw.Figure != THeadTailDraw::fEmpty)
    {
        return BarStartX - 6;
    }else
    {
        return BarStartX;
    }
}
//---------------------------------------------------------------------------
int TBarDraw::Top(int BarStartX, int BarEndX, int BarY, int X)
{
    if(HeadDraw.Figure != THeadTailDraw::fEmpty && X <= BarStartX + 8 &&
       X >= BarStartX - 8)
    {
        return BarY - 8;
    }else if(TailDraw.Figure != THeadTailDraw::fEmpty && X <= BarEndX + 8 &&
       X >= BarEndX - 8)
    {
        return BarY - 8;
    }else
    {
        switch(Figure)
        {//top 上一象素
            case fEmpty:
                return BarY;
            case fSolid:
                return BarY - 8;
            case fTopLarge:
                return BarY - 8;
            case fMiddleLarge:
                return BarY - 4;
            case fBottomLarge:
                return BarY;
            case fTopSmall:
                return BarY - 8;
            case fMiddleSmall:
                return BarY - 2;
            case fBottomSmall:
                return BarY + 4;
            default:
                throw Exception("条形图形状未定义");
        }
    }
}
//---------------------------------------------------------------------------
int TBarDraw::Right(int BarStartX, int BarEndX, int BarY)
{
    if(TailDraw.Figure != THeadTailDraw::fEmpty)
    {
        return BarEndX + 6;
    }else
    {
        return BarEndX;
    }
}
//---------------------------------------------------------------------------
int TBarDraw::Bottom(int BarStartX, int BarEndX, int BarY, int X)
{
    if(HeadDraw.Figure != THeadTailDraw::fEmpty && X <= BarStartX + 8 &&
       X >= BarStartX - 8)
    {
        return BarY + 9;
    }else if(TailDraw.Figure != THeadTailDraw::fEmpty && X <= BarEndX + 8 &&
       X >= BarEndX - 8)
    {
        return BarY + 9;
    }else
    {
        switch(Figure)
        {//bottom 下一象素
            case fEmpty:
                return BarY;
            case fSolid:
                return BarY + 9;
            case fTopLarge:
                return BarY + 1;
            case fMiddleLarge:
                return BarY + 4;
            case fBottomLarge:
                return BarY + 9;
            case fTopSmall:
                return BarY - 1;
            case fMiddleSmall:
                return BarY + 5;
            case fBottomSmall:
                return BarY + 9;
            default:
                throw Exception("条形图形状未定义");
        }
    }
}
//---------------------------------------------------------------------------
int TBarDraw::Mid(int BarY)
{
    switch(Figure)
    {//bottom 下一象素
        case fEmpty:
            return BarY;
        case fSolid:
            return BarY;
        case fTopLarge:
            return BarY - 4;
        case fMiddleLarge:
            return BarY;
        case fBottomLarge:
            return BarY + 5;
        case fTopSmall:
            return BarY - 3;
        case fMiddleSmall:
            return BarY;
        case fBottomSmall:
            return BarY + 4;
        default:
            throw Exception("条形图形状未定义");
    }
}
//---------------------------------------------------------------------------
//   T1BarDraw
//---------------------------------------------------------------------------
void T1BarDraw::Draw(HDC dc, int StartX, int EndX, int Y)
{
    Bar.Draw(dc, StartX, EndX, Y);
}
//---------------------------------------------------------------------------
//   T2BarDraw
//---------------------------------------------------------------------------
T2BarDraw::T2BarDraw()
{
    Bar2Draw = true; 
}
//---------------------------------------------------------------------------
void T2BarDraw::Draw(HDC dc, int StartX1, int EndX1,
                      int StartX2, int EndX2, int Y)
{
    if(Bar2Draw)
        Bar2.Draw(dc, StartX2, EndX2, Y);
    Bar1.Draw(dc, StartX1, EndX1, Y);
}
//---------------------------------------------------------------------------
//   T3BarDraw
//---------------------------------------------------------------------------
T3BarDraw::T3BarDraw()
{
    Bar2Draw = true;
    BaseDraw = false;
    BaseBar.Figure=TBarDraw::fBottomSmall;
    BaseBar.Color = (TColor)RGB(128, 128, 128);
    BaseBar.BorderColor = (TColor)RGB(128, 128, 128);
    BaseBar.HeadDraw.Color = (TColor)RGB(128, 128, 128);
    BaseBar.TailDraw.Color = (TColor)RGB(128, 128, 128);
}
//---------------------------------------------------------------------------
void T3BarDraw::Draw(HDC dc, int StartX1, int EndX1,
                      int StartX2, int EndX2,int BaseStartX, int BaseEndX, int Y)
{
     if(BaseDraw)
     {
       Bar2.Figure = TBarDraw::fTopSmall;
       //BaseBar.HeadDraw.Figure = Bar1.HeadDraw.Figure;
       //BaseBar.HeadDraw.Type = Bar1.HeadDraw.Type;
       //BaseBar.TailDraw.Figure = Bar1.TailDraw.Figure;
       //BaseBar.TailDraw.Type = Bar1.TailDraw.Type;
       BaseBar.Draw(dc,BaseStartX,BaseEndX,Y);
      }
     else
     {
      Bar2.Figure = TBarDraw::fBottomLarge;
     }
    Bar1.Draw(dc, StartX1, EndX1, Y);
    if(Bar2Draw)
        Bar2.Draw(dc, StartX2, EndX2, Y);
}
//---------------------------------------------------------------------------
//   TGTLinkDraw
//---------------------------------------------------------------------------
void TGTLinkDraw::FillLinePoint(POINT*pLine, int& LineCount, POINT*pArrow, int StartX, int StartY, int EndX, int EndY)
{//转一次弯的线
   pLine[0].x = StartX;
   pLine[0].y = StartY;
   pLine[1].x = EndX;
   pLine[1].y = StartY;
   pLine[2].x = EndX;
   pLine[2].y = EndY;
   LineCount = 3;
   if(StartY < EndY)
   {//向下
       pArrow[0].x = EndX;
       pArrow[0].y = EndY;
       pArrow[1].x = EndX - 5;
       pArrow[1].y = EndY - 5;
       pArrow[2].x = EndX + 5;
       pArrow[2].y = EndY - 5;
       pArrow[3] = pArrow[0];
   }else
   {//向上
       pArrow[0].x = EndX;
       pArrow[0].y = EndY;
       pArrow[1].x = EndX - 5;
       pArrow[1].y = EndY + 5;
       pArrow[2].x = EndX + 5;
       pArrow[2].y = EndY + 5;
       pArrow[3] = pArrow[0];
   }
}
//---------------------------------------------------------------------------
void TGTLinkDraw::FillLinePoint(POINT*pLine, int& LineCount, POINT*pArrow, int StartX, int StartY,
                               int EndX, int EndY, int MidY)
{//转四次弯的线
   LineCount = 6;
   if(StartX < EndX)
   {
           pLine[0].x = StartX;
           pLine[0].y = StartY;
           pLine[1].x = StartX - 5;
           pLine[1].y = StartY;
           pLine[2].x = StartX - 5;
           pLine[2].y = MidY;
           pLine[3].x = EndX + 8;
           pLine[3].y = MidY;
           pLine[4].x = EndX + 8;
           pLine[4].y = EndY;
           pLine[5].x = EndX;
           pLine[5].y = EndY;
           //向左
           pArrow[0].x = EndX;
           pArrow[0].y = EndY;
           pArrow[1].x = EndX + 5;
           pArrow[1].y = EndY - 5;
           pArrow[2].x = EndX + 5;
           pArrow[2].y = EndY + 5;
           pArrow[3] = pArrow[0];
   }else
   {
           pLine[0].x = StartX;
           pLine[0].y = StartY;
           pLine[1].x = StartX + 5;
           pLine[1].y = StartY;
           pLine[2].x = StartX + 5;
           pLine[2].y = MidY;
           pLine[3].x = EndX - 8;
           pLine[3].y = MidY;
           pLine[4].x = EndX - 8;
           pLine[4].y = EndY;
           pLine[5].x = EndX;
           pLine[5].y = EndY;
           //向右
           pArrow[0].x = EndX;
           pArrow[0].y = EndY;
           pArrow[1].x = EndX - 5;
           pArrow[1].y = EndY - 5;
           pArrow[2].x = EndX - 5;
           pArrow[2].y = EndY + 5;
           pArrow[3] = pArrow[0];
   }
}
//---------------------------------------------------------------------------
void TGTLinkDraw::Draw(HDC dc,
                     TBarDraw&StartBar1, TBarDraw*StartBar2,
                     int StartStartX1, int StartEndX1,
                     int StartStartX2, int StartEndX2, int StartBarY,
                     int StartTop, int StartBottom,
                     
                     TBarDraw&EndBar1, TBarDraw*EndBar2,
                     int EndStartX1, int EndEndX1,
                     int EndStartX2, int EndEndX2, int EndBarY,
                     TFrontType FrontType
                     )
{
   POINT pLine[6];
   POINT pArrow[4];
   int pLineCount;

   switch(FrontType)
   {
      case ftNone://0-无
         break;
      case ftFinishStart://1-完成-开始
      {
                  //完成
                  int StartX = StartBar1.Right(StartStartX1, StartEndX1, StartBarY);
                  int StartY = StartBar1.Mid(StartBarY);
/*                  if(StartBar2)
                  {
                      int Bar2Right = StartBar2->Right(StartStartX2, StartEndX2, StartBarY);
                      if(StartX < Bar2Right)
                      {
                         StartX = Bar2Right;
                         StartY = StartBar2->Mid(StartBarY);
                      }
                  }
*/
                  //开始
                  TBarDraw*ABar;
                  int EndX1, EndX2;
/*                  if(EndBar2 && EndStartX1 > EndStartX2)
                  {   //EndBar2
                     ABar = EndBar2;
                     EndX1 = EndStartX2;
                     EndX2 = EndEndX2;
                  }else
*/
                  {
                     ABar = &EndBar1;
                     EndX1 = EndStartX1;
                     EndX2 = EndEndX2;
                  }
                  if(StartX+5 < EndX1)
                  {
                      int EndY;
                      if(StartBarY < EndBarY)
                           EndY = ABar->Top(EndX1, EndX2, EndBarY, EndX1);
                      else
                           EndY = ABar->Bottom(EndX1, EndX2, EndBarY, EndX1);
                      FillLinePoint(pLine, pLineCount, pArrow,
                                    StartX, StartY,
                                    EndX1, EndY);
                  }else if(StartX <= EndX1)
                  {
                      int EndY;
                      if(StartBarY < EndBarY)
                          EndY = ABar->Top(EndX1, EndX2, EndBarY, EndX1 + 5);
                      else
                          EndY = ABar->Bottom(EndX1, EndX2, EndBarY, EndX1 + 5);
                      FillLinePoint(pLine, pLineCount, pArrow,
                                    StartX, StartY,
                                    EndX1 + 5, EndY);
                  }else
                  {
                      int EndY = ABar->Mid(EndBarY);
                      int EndLeft = ABar->Left(EndX1, EndX2, EndBarY);
                      if(StartBarY < EndBarY)
                      {
                          FillLinePoint(pLine, pLineCount, pArrow,
                                        StartX, StartY,
                                        EndLeft, EndY,
                                        StartBottom);
                      }else
                      {
                          FillLinePoint(pLine, pLineCount, pArrow,
                                        StartX, StartY,
                                        EndLeft, EndY,
                                        StartTop);
                      }
                  }
                  break;
      }
      case ftStartStart://2-开始-开始
      {
                  //开始
                  int StartX = StartBar1.Left(StartStartX1, StartEndX1, StartBarY);
                  int StartY = StartBar1.Mid(StartBarY);
/*                  if(StartBar2)
                  {
                      int Bar2Left = StartBar2->Left(StartStartX2, StartEndX2, StartBarY);
                      if(StartX > Bar2Left)
                      {
                         StartX = Bar2Left;
                         StartY = StartBar2->Mid(StartBarY);
                      }
                  }
*/
                  //开始
                  int EndX = EndBar1.Left(EndStartX1, EndEndX1, EndBarY);
                  int EndY = EndBar1.Mid(EndBarY);
/*                  if(EndBar2)
                  {
                      int Bar2Left = EndBar2->Left(EndStartX2, EndEndX2, EndBarY);
                      if(EndX > Bar2Left)
                      {
                         EndX = Bar2Left;
                         EndY = EndBar2->Mid(EndBarY);
                      }
                  }
*/
                  pLineCount = 4;
                  pLine[0].x = StartX;
                  pLine[0].y = StartY;
                  pLine[1].x = StartX < EndX ? (StartX - 3) : (EndX - 8);
                  pLine[1].y = StartY;
                  pLine[2].x = pLine[1].x;
                  pLine[2].y = EndY;
                  pLine[3].x = EndX;
                  pLine[3].y = EndY;
                  //向右
                  pArrow[0].x = EndX;
                  pArrow[0].y = EndY;
                  pArrow[1].x = EndX - 5;
                  pArrow[1].y = EndY - 5;
                  pArrow[2].x = EndX - 5;
                  pArrow[2].y = EndY + 5;
                  pArrow[3] = pArrow[0];

                  break;
      }
      case ftFinishFinish://3-完成-完成
      {
                  //完成
                  int StartX = StartBar1.Right(StartStartX1, StartEndX1, StartBarY);
                  int StartY = StartBar1.Mid(StartBarY);
/*                  if(StartBar2)
                  {
                      int Bar2Right = StartBar2->Right(StartStartX2, StartEndX2, StartBarY);
                      if(StartX < Bar2Right)
                      {
                         StartX = Bar2Right;
                         StartY = StartBar2->Mid(StartBarY);
                      }
                  }
*/
                  //完成
                  int EndX = EndBar1.Right(EndStartX1, EndEndX1, EndBarY);
                  int EndY = EndBar1.Mid(EndBarY);
/*                  if(EndBar2)
                  {
                      int Bar2Right = EndBar2->Right(EndStartX2, EndEndX2, EndBarY);
                      if(EndX < Bar2Right)
                      {
                         EndX = Bar2Right;
                         EndY = EndBar2->Mid(EndBarY);
                      }
                  }
*/
                  pLineCount = 4;
                  pLine[0].x = StartX;
                  pLine[0].y = StartY;
                  pLine[1].x = StartX > EndX ? (StartX + 3) : (EndX + 8);
                  pLine[1].y = StartY;
                  pLine[2].x = pLine[1].x;
                  pLine[2].y = EndY;
                  pLine[3].x = EndX;
                  pLine[3].y = EndY;
                  //向左
                  pArrow[0].x = EndX;
                  pArrow[0].y = EndY;
                  pArrow[1].x = EndX + 5;
                  pArrow[1].y = EndY - 5;
                  pArrow[2].x = EndX + 5;
                  pArrow[2].y = EndY + 5;
                  pArrow[3] = pArrow[0];
                  break;
      }
      case ftStartFinish://4-开始-完成
      {
                  //开始
                  int StartX = StartBar1.Left(StartStartX1, StartEndX1, StartBarY);
                  int StartY = StartBar1.Mid(StartBarY);
/*                  if(StartBar2)
                  {
                      int Bar2Right = StartBar2->Left(StartStartX2, StartEndX2, StartBarY);
                      if(StartX > Bar2Right)
                      {
                         StartX = Bar2Right;
                         StartY = StartBar2->Mid(StartBarY);
                      }
                  }
*/
                  //完成
                  TBarDraw*ABar;
                  int EndX1, EndX2;
/*                  if(EndBar2 && EndEndX1 < EndEndX2)
                  {   //EndBar2
                     ABar = EndBar2;
                     EndX1 = EndStartX2;
                     EndX2 = EndEndX2;
                  }else
*/
                  {
                     ABar = &EndBar1;
                     EndX1 = EndStartX1;
                     EndX2 = EndEndX1;
                  }
                  if(StartX-5 >= EndX2)
                  {
                      int EndY = ABar->Top(EndX1, EndX2, EndBarY, EndX2);
                      FillLinePoint(pLine, pLineCount, pArrow,
                                    StartX, StartY,
                                    EndX2, EndY);
                  }else if(StartX >= EndX2)
                  {
                      int EndY = ABar->Top(EndX1, EndX2, EndBarY, EndX2 - 5);
                      FillLinePoint(pLine, pLineCount, pArrow,
                                    StartX, StartY,
                                    EndX2 - 5, EndY);
                  }else
                  {
                      int EndY = ABar->Mid(EndBarY);
                      int EndRight = ABar->Right(EndX1, EndX2, EndBarY);
                      if(StartBarY < EndBarY)
                      {
                          FillLinePoint(pLine, pLineCount, pArrow,
                                        StartX, StartY,
                                        EndRight, EndY,
                                        StartBottom);
                      }else
                      {
                          FillLinePoint(pLine, pLineCount, pArrow,
                                        StartX, StartY,
                                        EndRight, EndY,
                                        StartTop);
                      }
                  }
                  break;
      }
      default:
         throw Exception("前置任务类行未定义");
   }
   int AWidth = 1;
   HPEN Pen = CreatePen(PS_SOLID, AWidth, Color);
   HGDIOBJ oldPen = SelectObject(dc, Pen);
   HBRUSH Brush= CreateSolidBrush(Color);
   HGDIOBJ oldBrush = SelectObject(dc, Brush);

   ::Polyline(dc, pLine, pLineCount);
   Polygon(dc, pArrow, 4);

   SelectObject(dc, oldPen);
   DeleteObject(Pen);
   SelectObject(dc, oldBrush);
   DeleteObject(Brush);
}
//---------------------------------------------------------------------------
//   TCalendarDraw
//---------------------------------------------------------------------------
TCalendarDraw::TCalendarDraw()
{
		FColWidth=20;
		Type=gctDay;
		BackColor=clSkyBlue;
		FontColor=clBlack;
		LineColor=clBlack;
		DrawLine1=false;
		DrawLine2=false;
		Line1Color=RGB(220,220,220);//clGreen;
		Line2Color=RGB(220,220,220);
		FStartDay = int(TDateTime::CurrentDate()) - 5;
		FShowDays=true;
		Language=0;
}
//---------------------------------------------------------------------------					  
String GetWeekEnglish(int iWeek)
{
   switch(iWeek)
   {
      case 1:
        return "Sun";
      case 2:
        return "Mon";
      case 3:
        return "Tue";
      case 4:
        return "Wed";
      case 5:
        return "Thu";
      case 6:
        return "Fri";
      case 7:
        return "Sat";
   }
   return "";
}
String GetMonthEnglish(int iMonth)
{
    switch(iMonth)
    {
      case 1:
        return "January";
      case 2:
        return "February";
      case 3:
        return "March";
      case 4:
        return "April";
      case 5:
        return "May";
      case 6:
        return "June";
      case 7:
        return "July";
      case 8:
        return "August";
      case 9:
        return "September";
      case 10:
        return "October";
      case 11:
        return "November";
      case 12:
        return "December";
    }
    return "";
}

String& TCalendarDraw::Line1Str(TDateTime &ADate,
                                    unsigned short year,
                                    unsigned short month,
                                    unsigned short day)
{
   if(Language==0)
   {
     switch(Type)
     {
         case gct2Hour:
             Line1StrReturn = IntToStr(year) + "年" + IntToStr(month) + "月" + IntToStr(day) + "日";
             return Line1StrReturn;
         case gct6Hour:
             Line1StrReturn = PrjFormatDate(ADate);
             return Line1StrReturn;
         case gctDay: //日
             Line1StrReturn = IntToStr(year) + "年" + IntToStr(month) + "月" + IntToStr(day) + "日";
             return Line1StrReturn;
         case gct3Day://三日
             Line1StrReturn = IntToStr(year) + "年" + IntToStr(month) + "月";
             return Line1StrReturn;
         case gctWeek: //周
             Line1StrReturn = IntToStr(year) + "年" + IntToStr(month) + "月";
             return Line1StrReturn;
         case gctMonth1: //月
             switch(month)
             {
                 case 1:
                 case 2:
                 case 3:
                     Line1StrReturn = IntToStr(year) + "年第1季度";
                     return Line1StrReturn;
                 case 4:
                 case 5:
                 case 6:
                     Line1StrReturn = IntToStr(year) + "年第2季度";
                     return Line1StrReturn;
                  case 7:
                 case 8:
                 case 9:
                     Line1StrReturn = IntToStr(year) + "年第3季度";
                     return Line1StrReturn;
                 case 10:
                 case 11:
                 case 12:
                     Line1StrReturn = IntToStr(year) + "年第4季度";
                     return Line1StrReturn;
             }
         case gctMonth2: //月
             Line1StrReturn = IntToStr(year) + "年";
             return Line1StrReturn;
         case gctQuarter://季度
             Line1StrReturn = IntToStr(year) + "年";
             return Line1StrReturn;
         case gctHalfYear:  //半年
             Line1StrReturn = IntToStr(year);
             return Line1StrReturn;
         default:
             throw Exception("甘特图日历类型错误");
     }
   }
   else
   {
     switch(Type)
     {
         case gct2Hour:
         case gct6Hour:
         case gctDay: //日
             //Line1StrReturn = IntToStr(year) + "-" + IntToStr(month) + "-" + IntToStr(day) + "";
             Line1StrReturn = GetMonthEnglish(month)+" "+IntToStr(day)+","+IntToStr(year);
             return Line1StrReturn;
         case gct3Day://三日
         case gctWeek: //周
             //Line1StrReturn = IntToStr(year) + "" + IntToStr(month) + "";
             Line1StrReturn = GetMonthEnglish(month)+" "+IntToStr(year);
             return Line1StrReturn;
         case gctMonth1: //月
             switch(month)
             {
                 case 1:
                 case 2:
                 case 3:                            //quarter in
                     Line1StrReturn = "First Q "+IntToStr(year);
                     return Line1StrReturn;
                 case 4:
                 case 5:
                 case 6:
                     Line1StrReturn = "Second Q "+IntToStr(year);
                     return Line1StrReturn;
                  case 7:
                 case 8:
                 case 9:
                     Line1StrReturn = "Third Q "+IntToStr(year);
                     return Line1StrReturn;
                 case 10:
                 case 11:
                 case 12:
                     Line1StrReturn = "Fourth Q "+IntToStr(year);
                     return Line1StrReturn;
             }
         case gctMonth2: //月
         case gctQuarter://季度
         case gctHalfYear:  //半年
             Line1StrReturn = IntToStr(year);
             return Line1StrReturn;
         default:
             throw Exception("甘特图日历类型错误");
     }
   }
}
//---------------------------------------------------------------------------
String& TCalendarDraw::Line2Str(TDateTime &ADate,
                                    unsigned short year,
                                    unsigned short month,
                                    unsigned short day)
{
   switch(Type)
   {
       case gct2Hour:
       {
           static unsigned short hour, min, sec, msec;
           ADate.DecodeTime(&hour, &min, &sec, &msec);
           switch(hour)
           {
               case 24:
               case 0:
               case 1:
                   Line2StrReturn = "0";
                   break;
               case 2:
               case 3:
                   Line2StrReturn = "2";
                   break;
               case 4:
               case 5:
                   Line2StrReturn = "4";
                   break;
               case 6:
               case 7:
                   Line2StrReturn = "6";
                   break;
               case 8:
               case 9:
                   Line2StrReturn = "8";
                   break;
               case 10:
               case 11:
                   Line2StrReturn = "10";
                   break;
               case 12:
               case 13:
                   Line2StrReturn = "12";
                   break;
               case 14:
               case 15:
                   Line2StrReturn = "14";
                   break;
               case 16:
               case 17:
                   Line2StrReturn = "16";
                   break;
               case 18:
               case 19:
                   Line2StrReturn = "18";
                   break;
               case 20:
               case 21:
                   Line2StrReturn = "20";
                   break;
               case 22:
               case 23:
                   Line2StrReturn = "22";
                   break;
               default:
                   Line2StrReturn = "";
           }
           return Line2StrReturn;
       }
       case gct6Hour:
       {
           static unsigned short hour, min, sec, msec;
           ADate.DecodeTime(&hour, &min, &sec, &msec);
           switch(hour)
           {
               case 0:
               case 24:
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
                   Line2StrReturn = "0";
                   break;
               case 6:
               case 7:
               case 8:
               case 9:
               case 10:
               case 11:
                   Line2StrReturn = "6";
                   break;
               case 12:
               case 13:
               case 14:
               case 15:
               case 16:
               case 17:
                   Line2StrReturn = "12";
                   break;
               case 18:
               case 19:
               case 20:
               case 21:
               case 22:
               case 23:
                   Line2StrReturn = "18";
                   break;
               default:
                   Line2StrReturn = "";
           }
           return Line2StrReturn;
       }
       case gctDay: //日
           if(FShowDays)
           {
             Line2StrReturn = IntToStr(day);
             return  Line2StrReturn;
           }
           if(Language==0)
           {
             switch(ADate.DayOfWeek())
             {
                 case 1:
                    Line2StrReturn = "日";
                    return Line2StrReturn;
                 case 2:
                    Line2StrReturn = "一";
                    return Line2StrReturn;
                 case 3:
                    Line2StrReturn = "二";
                    return Line2StrReturn;
                 case 4:
                    Line2StrReturn = "三";
                    return Line2StrReturn;
                 case 5:
                    Line2StrReturn = "四";
                    return Line2StrReturn;
                 case 6:
                    Line2StrReturn = "五";
                    return Line2StrReturn;
                 case 7:
                    Line2StrReturn = "六";
                    return Line2StrReturn;
                 default:
                     throw Exception("星期错误");
             }
           }
           else
           {
             Line2StrReturn = GetWeekEnglish((int)ADate.DayOfWeek());
             return Line2StrReturn;
           }
       case gct3Day://三日
           Line2StrReturn = IntToStr(day);
           return Line2StrReturn;
       case gctWeek: //周
           Line2StrReturn = IntToStr(day);
           return Line2StrReturn;
       case gctMonth1: //月
           Line2StrReturn = IntToStr(month);
           return Line2StrReturn;
       case gctMonth2: //月
           Line2StrReturn = IntToStr(month);
           return Line2StrReturn;
       case gctQuarter://季度
           switch(month)
           {
               case 1:
               case 2:
               case 3:
                   Line2StrReturn = String("Q") + "1";
                   return Line2StrReturn;
               case 4:
               case 5:
               case 6:
                   Line2StrReturn = String("Q") + "2";
                   return Line2StrReturn;
               case 7:
               case 8:
               case 9:
                   Line2StrReturn = String("Q") + "3";
                   return Line2StrReturn;
               case 10:
               case 11:
               case 12:
                   Line2StrReturn = String("Q") + "4";
                   return Line2StrReturn;
           }
       case gctHalfYear:  //半年
           switch(month)
           {
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
               case 6:
                   Line2StrReturn = String("H") + "1";
                   return Line2StrReturn;
               case 7:
               case 8:
               case 9:
               case 10:
               case 11:
               case 12:
                   Line2StrReturn = String("H") + "2";
                   return Line2StrReturn;
           }
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
int TCalendarDraw::Line1HaveLine2Count()
{
   switch(Type)
   {
       case gct2Hour:
           return 12;
       case gct6Hour:
           return 4;
       case gctDay: //日
           return 7;
       case gct3Day://三日
           return 11;
       case gctWeek: //周
           return 5;
       case gctMonth1: //月
           return 3;
       case gctMonth2: //月
           return 12;
       case gctQuarter://季度
           return 4;
       case gctHalfYear:  //半年
           return 2;
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
void TCalendarDraw::AlignLine1(TDateTime&ADate)
{
   switch(Type)
   {
       case gct2Hour:
           ADate = int(ADate);
           break;
       case gct6Hour:
           ADate = int(ADate);
           break;
       case gctDay: //日
       {
           ADate = int(ADate) - (ADate.DayOfWeek()) + 1;
           break;
       }
       case gct3Day://三日
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = int(ADate) - day + 1;
           break;
       }
       case gctWeek: //周
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = int(ADate) - day + 1;
           break;
       }
       case gctMonth1: //月
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           switch(month)
           {
               case 1:
               case 2:
               case 3:
                   month = 1;
                   break;
               case 4:
               case 5:
               case 6:
                   month = 4;
                   break;
               case 7:
               case 8:
               case 9:
                   month = 7;
                   break;
               case 10:
               case 11:
               case 12:
                   month = 10;
                   break;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       case gctMonth2: //月
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = IntToStr(year) + "-1-1";
           break;
       }
       case gctQuarter://季度
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = IntToStr(year) + "-1-1";
           break;
       }
       case gctHalfYear:  //半年
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = IntToStr(year) + "-1-1";
           break;
       }
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
void TCalendarDraw::AlignLine2(TDateTime&ADate)
{
   switch(Type)
   {
       case gct2Hour:
           ADate = int(ADate);
           break;
       case gct6Hour:
           ADate = int(ADate);
           break;
       case gctDay: //日
           break;
       case gct3Day://三日
           ADate = ADate - (ADate - FStartDay) % 3 + 1;
           break;
       case gctWeek: //周
           ADate = ADate - ADate.DayOfWeek() + 1;
           break;
       case gctMonth1: //月
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = ADate - day + 1;
           break;
       }
       case gctMonth2: //月
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           ADate = ADate - day + 1;
           break;
       }
       case gctQuarter://季度
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           switch(month)
           {
               case 1:
               case 2:
               case 3:
                   month = 1;
                   break;
               case 4:
               case 5:
               case 6:
                   month = 4;
                   break;
               case 7:
               case 8:
               case 9:
                   month = 7;
                   break;
               case 10:
               case 11:
               case 12:
                   month = 10;
                   break;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       case gctHalfYear:  //半年
       {
           static unsigned short year, month, day;
           ADate.DecodeDate(&year, &month, &day);
           switch(month)
           {
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
               case 6:
                   month = 1;
                   break;
               case 7:
               case 8:
               case 9:
               case 10:
               case 11:
               case 12:
                   month = 6;
                   break;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
void TCalendarDraw::IncLine1(TDateTime&ADate,
                             unsigned short year,
                             unsigned short month,
                             unsigned short day)
{
   switch(Type)
   {
       case gct2Hour:
           ADate += 1;
           break;
       case gct6Hour:
           ADate += 1;
           break;
       case gctDay: //日
           ADate += 7;
           break;
       case gct3Day://三日
       {
           month++;
           if(month >= 13)
           {
              month = 1;
              year++;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       case gctWeek: //周
       {
           month++;
           if(month >= 13)
           {
              month = 1;
              year++;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       case gctMonth1: //月
       {
           switch(month)
           {
               case 1:
               case 2:
               case 3:
                   month = 4;
                   break;
               case 4:
               case 5:
               case 6:
                   month = 7;
                   break;
               case 7:
               case 8:
               case 9:
                   month = 10;
                   break;
               case 10:
               case 11:
               case 12:
                   month = 1;
                   year++;
                   break;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       case gctMonth2: //月
       {
           year++;
           ADate = IntToStr(year) + "-1-1";
           break;
       }
       case gctQuarter://季度
       {
           year++;
           ADate = IntToStr(year) + "-1-1";
           break;
       }
       case gctHalfYear:  //半年
       {
           year++;
           ADate = IntToStr(year) + "-1-1";
           break;
       }
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
void TCalendarDraw::IncLine2(TDateTime&ADate,
                             unsigned short year,
                             unsigned short month,
                             unsigned short day)
{
   switch(Type)
   {
       case gct2Hour:
       {
           ADate = double(ADate )+ double(1) / double(12);
           break;
       }
       case gct6Hour:
           ADate = double(ADate) + double(0.25);
           break;
       case gctDay: //日
           ADate++;
           break;
       case gct3Day://三日
           ADate += 3;
           break;
       case gctWeek: //周
           ADate += 7;
           break;
       case gctMonth1: //月
       {
           month++;
           if(month >= 13)
           {
              month = 1;
              year++;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-01";
           break;
       }
       case gctMonth2: //月
       {
           month++;
           if(month >= 13)
           {
              month = 1;
              year++;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-01";
           break;
       }
       case gctQuarter://季度
       {
           switch(month)
           {
               case 1:
               case 2:
               case 3:
                   month = 4;
                   break;
               case 4:
               case 5:
               case 6:
                   month = 7;
                   break;
               case 7:
               case 8:
               case 9:
                   month = 10;
                   break;
               case 10:
               case 11:
               case 12:
                   month = 1;
                   year++;
                   break;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       case gctHalfYear:  //半年
       {
           switch(month)
           {
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
               case 6:
                   month = 7;
                   break;
               case 7:
               case 8:
               case 9:
               case 10:
               case 11:
               case 12:
                   month = 1;
                   year++;
                   break;
           }
           ADate = IntToStr(year) + "-" + IntToStr(month) + "-1";
           break;
       }
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
void TCalendarDraw::Init()
{
   HDC dc = GetDC(NULL);
   static unsigned short year, month, day;
   TDateTime adate =Now();// TDateTime("2000-12-30 23:59:59");
   adate.DecodeDate(&year, &month, &day);
   String& aLine1 = Line1Str(adate, year, month, day);
   String& aLine2 = Line2Str(adate, year, month, day);
   int aLine1HaveLine2Count = Line1HaveLine2Count();//行一 的天数包括几个 行二

   RECT r;
   r.top = 0;
   r.left = 0;
   r.right = 1000;
   r.bottom = 1000;

   ::DrawText(dc, aLine1.c_str(), aLine1.Length(), &r, DT_CALCRECT | DT_SINGLELINE);
   int line1length = r.right - r.left;
   ::DrawText(dc, aLine2.c_str(), aLine2.Length(), &r, DT_CALCRECT | DT_SINGLELINE);
   int line2length = r.right - r.left;
   //zws2008-10-28
   //   FColWidth = ((line2length + 4)* aLine1HaveLine2Count) > (line1length + 4)?
//               (line2length + 4) :
//               ((line1length + 4) / aLine1HaveLine2Count);
   ReleaseDC(NULL, dc);
}
//---------------------------------------------------------------------------
void TCalendarDraw::Draw(HDC dc, const RECT &rect, int LineHeight)
{
   COLORREF oldbkcolor = SetBkColor(dc, BackColor);
   COLORREF oldtextcolor = SetTextColor(dc, FontColor);
   HBRUSH  brush = CreateSolidBrush(BackColor);
   HGDIOBJ oldbrush = SelectObject(dc, brush);
   HPEN    pen = CreatePen(PS_SOLID, 1, LineColor);
   HGDIOBJ oldpen = SelectObject(dc, pen);
   HPEN    line1pen, line2pen;
   SIZE Textsize;
   if(DrawLine1)
       line1pen = CreatePen(PS_SOLID, 1, Line1Color);
   if(DrawLine2)
       line2pen = CreatePen(PS_SOLID, 1, Line2Color);

   static unsigned short year, month, day;
   //第二行
   {
       TDateTime StartDay = XAtDay(rect.left);
       AlignLine2(StartDay);
       int atop  = rect.top + (rect.bottom - rect.top) / 2;
       int abottom = rect.bottom;
       RECT dr;
       do{
           StartDay.DecodeDate(&year, &month, &day);
           dr.top = atop;
           dr.bottom = abottom;
           dr.left = GetDayLeft(StartDay);
           String &drawstr = Line2Str(StartDay, year, month, day);
           TDateTime bkStartDay = StartDay;
           IncLine2(StartDay, year, month, day);
           dr.right = GetDayLeft(StartDay);
           //draw
           RECT tRect1=dr;
//           POINT p2[4];
//           p2[0].x=dr.left;
//           p2[0].y=dr.top;
//           p2[1].x=dr.right;
//           p2[1].y=dr.top;
//           p2[2].x=dr.right;
//           p2[2].y=dr.bottom;
//           p2[3].x=dr.left;
//           p2[3].y=dr.bottom;
//           Polyline(dc,p2,4);
//           GetTextExtentPoint32(dc,drawstr.c_str(),drawstr.Length(),&Textsize);
//           int x=dr.left+(dr.right-dr.left-Textsize.cx)/2;
//           int y=dr.top+(dr.bottom-dr.top-Textsize.cy)/2;
//           TextOut(dc,x,y,drawstr.c_str(),drawstr.Length());
		   Rectangle(dc, tRect1.left, tRect1.top-1, tRect1.right+1, tRect1.bottom);
		   ::DrawText(dc, drawstr.c_str(), drawstr.Length(), &tRect1,
					  DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		   if(DrawLine2)
           {
                HGDIOBJ aoldpen = SelectObject(dc, line2pen);
                MoveToEx(dc, dr.left, dr.bottom - 2, NULL);
                LineTo(dc, dr.left, dr.bottom + LineHeight);
                SelectObject(dc, aoldpen);
           }
           //draw over
       }while(dr.left < rect.right);
   }
   //第一行
   {
       TDateTime StartDay = XAtDay(rect.left);
       AlignLine1(StartDay);
       int atop  = rect.top;
       int abottom = atop + (rect.bottom - rect.top) / 2;
       RECT dr;
       do{
           StartDay.DecodeDate(&year, &month, &day);
           dr.top = atop;
           dr.bottom = abottom;
           dr.left = GetDayLeft(StartDay);
           String&drawstr = Line1Str(StartDay, year, month, day);
           TDateTime bkStartDay = StartDay;
           IncLine1(StartDay, year, month, day);
           dr.right = GetDayLeft(StartDay);
           //draw
           RECT tRect2=dr;
//           POINT p1[4];
//           p1[0].x=dr.left;
//           p1[0].y=dr.top;
//           p1[1].x=dr.right;
//           p1[1].y=dr.top;
//           p1[2].x=dr.right;
//           p1[2].y=dr.bottom;
//           p1[3].x=dr.left;
//           p1[3].y=dr.bottom;
//           Polyline(dc,p1,4);
//           GetTextExtentPoint32(dc,drawstr.c_str(),drawstr.Length(),&Textsize);
//           int x=dr.left+(dr.right-dr.left-Textsize.cx)/2;
//           int y=dr.top+(dr.bottom-dr.top-Textsize.cy)/2;
//           TextOut(dc,x,y,drawstr.c_str(),drawstr.Length());

		   Rectangle(dc, tRect2.left, tRect2.top, tRect2.right+1, tRect2.bottom);
					   ::DrawText(dc, drawstr.c_str(), drawstr.Length(), &tRect2,
					  DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		   if(DrawLine1)
           {
                HGDIOBJ aoldpen = SelectObject(dc, line1pen);
                MoveToEx(dc, dr.left, dr.bottom + (dr.bottom - dr.top) - 2, NULL);
                LineTo(dc, dr.left, dr.bottom + LineHeight+(dr.bottom-dr.top));
                SelectObject(dc, aoldpen);
           }
           //draw over
       }while(dr.right < rect.right);
   }
   SelectObject(dc, oldbrush);
   SelectObject(dc, oldpen);
   DeleteObject(brush);
   DeleteObject(pen);
   SetBkColor(dc, oldbkcolor);
   SetTextColor(dc, oldtextcolor);
   if(DrawLine1)
       DeleteObject(line1pen);
   if(DrawLine2)
       DeleteObject(line2pen);
}
//---------------------------------------------------------------------------
int TCalendarDraw::GetDayLeft(const TDateTime& ADay)
{
   switch(Type)
   {
       case gct2Hour://二小时
           return FColWidth * (double(ADay - FStartDay) * 12);
       case gct6Hour://六小时
           return FColWidth * (double(ADay - FStartDay) * 4);
       case gctDay: //日
           return FColWidth * (double(ADay - FStartDay));
       case gct3Day://三日
           return FColWidth * (double(ADay - FStartDay) / 3);
       case gctWeek: //周
           return FColWidth * (double(ADay - FStartDay) / 7);
       case gctMonth1: //月
           return FColWidth * (double(ADay - FStartDay) / 30);
       case gctMonth2: //月
           return FColWidth * (double(ADay - FStartDay) / 60);
       case gctQuarter://季度
           return FColWidth * (double(ADay - FStartDay) / 90);
       case gctHalfYear:  //半年
           return FColWidth * (double(ADay - FStartDay) / 183);
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
int TCalendarDraw::GetDayRight(const TDateTime& ADay)
{
   TDateTime day = ADay + 1;
   return GetDayLeft(day);
}
//---------------------------------------------------------------------------
TDateTime TCalendarDraw::XAtDay(const int &X)
{
   switch(Type)
   {
       case gct2Hour:
           return FStartDay +  int(X / FColWidth) / 12;
       case gct6Hour:
           return FStartDay +  int(X / FColWidth) / 4;
       case gctDay: //日
           return FStartDay + int(X / FColWidth);
       case gct3Day://三日
           return FStartDay + int((X / FColWidth) * 3);
       case gctWeek: //周
           return FStartDay + int((X / FColWidth) * 7);
       case gctMonth1: //月
           return FStartDay + int((X / FColWidth) * 30);
       case gctMonth2: //月
           return FStartDay + int((X / FColWidth) * 60);
       case gctQuarter://季度
           return FStartDay + int((X / FColWidth) * 90);
       case gctHalfYear:  //半年
           return FStartDay + int((X / FColWidth) * 183);
       default:
           throw Exception("甘特图日历类型错误");
   }
}
//---------------------------------------------------------------------------
void TCalendarDraw::AutoAlignStartEnd(const TDateTime&MustStart, const TDateTime&MustEnd,int LeftReserved,int RightReserved)
{
   int leftReservedUnit=LeftReserved/FColWidth;
   int rightReservedUnit=RightReserved/FColWidth;
   switch(Type)
   {
       case gct2Hour:
           FStartDay = MustStart - (leftReservedUnit/12+1);
           FEndDay = MustEnd + (rightReservedUnit/12+1);
           break;
       case gct6Hour:
           FStartDay = MustStart - (6*leftReservedUnit/24+1);
           FEndDay = MustEnd + (6*rightReservedUnit/24+1);
           break;
       case gctDay: //日
           FStartDay = MustStart - leftReservedUnit-1;
           FEndDay = MustEnd + rightReservedUnit+1;
           break;
       case gct3Day://三日
           FStartDay = MustStart - leftReservedUnit*3-3;
           FEndDay = MustEnd + rightReservedUnit*3+3;
           break;
       case gctWeek: //周
           FStartDay = MustStart - leftReservedUnit*7-7;
           FEndDay = MustEnd + rightReservedUnit*7+7;
           break;
       case gctMonth1: //月
           FStartDay = MustStart - leftReservedUnit*31-31;
           FEndDay = MustEnd + rightReservedUnit*31+31;
           break;
       case gctMonth2: //月
           FStartDay = MustStart - leftReservedUnit*62-62;
           FEndDay = MustEnd + rightReservedUnit*62+62;
           break;
       case gctQuarter://季度
           FStartDay = MustStart - leftReservedUnit*91-91;
           FEndDay = MustEnd + rightReservedUnit*91+91;
           break;
       case gctHalfYear:  //半年
           FStartDay = MustStart - leftReservedUnit*183-183;
           FEndDay = MustEnd + rightReservedUnit*183+183;
           break;
       default:
           throw Exception("甘特图日历类型错误");
   }
}

//------------------------------------------------------------------------
// TTaskShowCol
//------------------------------------------------------------------------
String TTaskShowCol::GetData(TPrjObject&AObj)
{
    switch(DataIndex)
	{
        case 0://序号
            if(AObj.IsForeign())
            {
                String rtn = IntToStr(AObj.Index);
                TPrjObject* tempObj = AObj.Parent();
                while(tempObj)
                {
                    switch(tempObj->GetType())
                    {
                        case ttForeignProject:
                            rtn = IntToStr(tempObj->Index) + "." + rtn;
                            break;
                        case ttProject:
                            return rtn;
                        case ttTask:
                            break;
                        case ttAbstractTask:
                            break;
                        default:
                            throw Exception("对象类型未定义");
                    }
                    tempObj = tempObj->Parent();
                }
                return rtn;
            }else
            {
                return IntToStr(AObj.Index);
            }
        case 1://名称
            return AObj.Name;
        case 2://描述
            return AObj.Desc;
        case 3://计划时间
            return PrjFormatDate(AObj.StartDate) + " ~ " +
                   PrjFormatDate(AObj.EndDate);
        case 4://工期
            return AObj.CostDays;
        case 5://产值
			return Format("%.2f",ARRAYOFCONST(((double)AObj.Invest)));
		case 6://任务代码
            return AObj.Code;
		case 7: //实际工期			其中:停工工期在项目日历中加以说明
			return Format("%.1f",ARRAYOFCONST(((double)AObj.FactCostDays)));
		case 8://计划开始时间
            return AObj.StartDate;
		case 9://计划工程量			在进度截止日期的计划数由任务日历汇总得到
			return Format("%.2f",ARRAYOFCONST(((double)AObj.WorkLoad)));
		case 10://实际工程量		汇总	实际工程量只能小于等于计划工程量,当任务完工时二者完全相等
			return Format("%.2f",ARRAYOFCONST(((double)AObj.FactWorkLoad)));
		case 11://进度评估值		汇总	这里会生成百分比
			return Format("%.2f",ARRAYOFCONST(((double)AObj.EnvaluedWorkLoad)));
        case 12://计划结束时间
            return AObj.EndDate;
		case 13://计划完成产值
			return Format("%.2f",ARRAYOFCONST(((double)AObj.BCWS)));
		case 14://实际投资(产值)		汇总	实际产值可以小于也可以大于计划产值
			return Format("%.2f",ARRAYOFCONST(((double)AObj.FactInvest)));
		case 15://赢得值		汇总
			return Format("%.2f",ARRAYOFCONST(((double)AObj.BCWP)));
		case 16://最早开工日期		计算
            return PrjFormatDate(AObj.ASAP_StartDate);
		case 17://最早完工日期		计算
			return PrjFormatDate(AObj.ASAP_EndDate);
		case 18://最晚开工日期		计算
            return PrjFormatDate(AObj.ALAP_StartDate);
		case 19://最晚完工日期		计算
            return PrjFormatDate(AObj.ALAP_EndDate);
		case 20://实际开工日期		输入
            return PrjFormatDate(AObj.FactStartDate);
		case 21://实际完工日期		输入
            return PrjFormatDate(AObj.FactEndDate);
		case 22://任务完成期限		0-无期限	1-最早开工0-无限制，1-最早开工，2-最迟完工
            if(! (AObj.GetType()==ttForeignProject))
			  return GetPlanTypeName((int)AObj.PlanType);
            else
              switch(AObj.PlanType)
			  {
                case ptASAP:
                    return "最早开工";
                case ptALAP:
                    return "最迟完工";
                case 3:
                    return "同步";
              }
		case 23://任务类型			0-非关键任务	1-关键任务
            if(AObj.Critical)
               return "是";
            else
               return "否";
		case 24://进度截止日期
            return PrjFormatDate(AObj.ProcessDate);
		case 25:////里程碑标识		0-非里程碑	1-里程碑
            if(AObj.MileStone)
               return "是";
            else
               return "否";
		case 26: ////乐观工期		输入
			return Format("%.2f",ARRAYOFCONST(((double)AObj.AnticipateCostDays)));
		case 27:////预期工期		输入
			return Format("%.2f",ARRAYOFCONST(((double)AObj.OptimismCostDays)));
		case 28:////悲观工期		输入
			return Format("%.2f",ARRAYOFCONST(((double)AObj.PessimismCostDays)));
        case 29://开工状态
            switch(AObj.TaskStatus)
            {
                case tsNotStart:
                    return "未开工";
                case tsStarted:
                    return "已开工";
                case tsOvered:
                    return "已完工";
                case tsPaused:
                    return "停工";
                default:
                    return "未定义";
            }
        case 30://类型
            switch(AObj.GetType())
            {
                case ttProject:
                    return "项目";
                case ttTask:
                    return "常规任务";
                case ttAbstractTask:
                    return "任务分组";
                case ttForeignProject:
					return "外部项目";
				case ttMileStone:
					return "里程碑";
                default:
                    return "未定义";
            }
        case 31://WBS
            return AObj.WBS;
        case 32://工程量类型
            switch(AObj.WorkLoadType)
            {
                case 0:
                    return "无明细工程量";
                case 1:
                    return "有明细工程量";
                default:
                    return "未定义";
            }
        case 33://累计工期
            if(AObj.Critical)
              return IntToStr(AObj.CumulateDays);
            else
              return "";
        case 34://团队组织
            return AObj.Personnel;
        case 35://实际时间
            if(PrjFormatDate(AObj.FactStartDate)=="" && PrjFormatDate(AObj.FactEndDate)=="")
              return "";
            else
              return PrjFormatDate(AObj.FactStartDate) + " ~ " +
                   PrjFormatDate(AObj.FactEndDate);
        case 36://挺复工标志
            if (AObj.StopFlag == 0)
               return "无停/复工" ;
            else
            if (AObj.StopFlag == 1)
               return "停工" ;
            else
               return "复工";
		case 37:
			 return AObj.TotalDiff;
		case 38:
			 return AObj.FreeDays;
		case 39:
			return  Format("%.2f",ARRAYOFCONST((AObj.TaskPctPercent)))+"%";
		default:
            return "";
    }
}
//---------------------------------------------------------------------------
String TTaskShowCol::GetTitle()
{
   switch(DataIndex)
   {
       case 0:
          return "序号";
       case 1://
		  return "名称";
       case 2://
          return "描述";
       case 3://
          return "计划时间";
       case 4://
		  return "计划工期";
       case 5://
		  return "计划总产值";
	   case 6://任务代码
          return "任务代码";
	   case 7: //实际工期			其中:停工工期在项目日历中加以说明
          return "实际工期";
	   case 8://计划开始时间
		   return "计划开始";
	   case 9://计划工程量			在进度截止日期的计划数由任务日历汇总得到
		   return "计划工程量";
	   case 10://实际工程量		汇总	实际工程量只能小于等于计划工程量,当任务完工时二者完全相等
		   return "实际工程量";
	   case 11://进度评估值		汇总	这里会生成百分比
		   return "进度评估值";
	   case 12://计划完成时间
           return "计划完成";
	   case 13://计划产值
		   return "计划完成产值";
	   case 14://实际产值		汇总	实际产值可以小于也可以大于计划产值
		   return "实际完成产值";
	   case 15://产值评估值		汇总
		   return "赢得值";
	   case 16://最早开工日期
		   return "最早开工";
	   case 17://最早完工日期
		   return "最早完工";
	   case 18://最晚开工日期
		   return "最晚开工";
	   case 19://最晚完工日期
		   return "最晚完工";
	   case 20://实际开工日期
		   return "实际开工";
	   case 21://实际完工日期
		   return "实际完工";
	   case 22://任务完成期限			0-无期限	1-最早开工0-无限制，1-最早开工，2-最迟完工
		   return "计划类型";
	   case 23://任务类型			0-非关键任务	1-关键任务
		   return "关键任务?";
	   case 24://进度截止日期
		   return "进度截止日";
	   case 25:////里程碑标识		0-非里程碑	1-里程碑
           return "里程碑?";
	   case 26: ////乐观工期	
           return "乐观工期";
	   case 27:////预期工期
           return "预期工期";
	   case 28:////悲观工期
           return "悲观工期";
       case 29://开工状态
           return "开工状态";
       case 30://类型
           return "类型";
       case 31://WBS
		   return "WBS";
       case 32://工程量类型
           return "工程量类型";
       case 33://累计工期
           return "累计工期";
	   case 35://
		   return "实际时间";
       case 34://
		   return "负责人";
	   case 36://
		   return "停/复工";
	   case 37:
			return "总时差";
	   case 38:
			return "自由时差" ;
	   case 39:
			return "实际进度" ;
       default:
		   return "";
   }
}
//---------------------------------------------------------------------------
unsigned int TTaskShowCol::GetTitleFormat()
{
   switch(DataIndex)
   {
       case 0:
          return DT_VCENTER | DT_CENTER | DT_SINGLELINE;
       default:
          return DT_VCENTER | DT_CENTER | DT_SINGLELINE;
   }
}
//---------------------------------------------------------------------------
unsigned int TTaskShowCol::GetDataFormat()
{
   switch(DataIndex)
   {
	   case 0:
		  return DT_VCENTER | DT_CENTER | DT_SINGLELINE;
	   case 4:
	   case 5:
	   case 37:
	   case 38:
		  return DT_VCENTER | DT_RIGHT | DT_SINGLELINE;
	   default:
          return DT_VCENTER | DT_LEFT | DT_SINGLELINE;
   }
}
//---------------------------------------------------------------------------
int TTaskShowCol::DataTypeCount()
{
   return 40;
}
//------------------------------------------------------------------------
// TTaskShowString
//------------------------------------------------------------------------
TTaskShowString::TTaskShowString()
                :FShowCols(NULL), FSpaces(NULL)
{
}
TTaskShowString::~TTaskShowString()
{
    if(FShowCols)
        delete [] FShowCols;
    if(FSpaces)
        delete [] FSpaces;
}
String TTaskShowString::GetShowString(TPrjObject& AObj)
{
    if(!FShowCols || !FSpaces || FDefineColCount <= 0)
        return FDefineString;
    String Rtn;
    for(int i = 0; i < FDefineColCount; i++)
    {
        Rtn += FSpaces[i];
        Rtn += FShowCols[i].GetData(AObj);
    }
    Rtn += FSpaces[FDefineColCount];
    return Rtn;
}
void TTaskShowString::SetDefineString(String AStr)
{
    FDefineString = AStr;
	StackArray< Char*,128 > Start(128);
	StackArray< Char*,128 > End(128);
	Char* c = FDefineString.c_str();
    int StartEndIndex(0);
    while(*c != '\0')
    {
        if(*c == '[')
        {
            Start[StartEndIndex] = c;
            c++;
            while(*c != '\0')
            {
                 if(*c == ']')
                 {
                     End[StartEndIndex] = c;
                     StartEndIndex++;
                     goto labelNext;
                 }
                 if(*c == '[')
                 {
                     throw Exception("错误：文字显示字符串定义错误！");
                 }
                 c++;
            }
        }
    labelNext:
        c++;
    }
    if(FShowCols)
        delete [] FShowCols;
    if(FSpaces)
        delete [] FSpaces;
    FShowCols = NULL;
    FSpaces = NULL;
    if(StartEndIndex <= 0)
    {
		FDefineColCount = 0;
        return;
    }
    FShowCols = new TTaskShowCol[StartEndIndex];
    FSpaces = new String[StartEndIndex+1];
    for(int i = 0; i < StartEndIndex; i++)
    {
        String aTitle = String(Start[i]+1, End[i]-Start[i]-1);
        for(int k = 0; k < FShowCols[i].DataTypeCount(); k ++)
        {
            FShowCols[i].DataIndex = k;
            if(FShowCols[i].GetTitle() == aTitle)
            {
                goto labelNextTitle;
            }
        }

    labelNextTitle:
        ;
    }
	c = FDefineString.c_str();
    for(int i = 0; i < StartEndIndex; i++)
    {
        FSpaces[i] = String(c, Start[i] - c);
        c = End[i] + 1;
    }
    FSpaces[StartEndIndex] = String(End[StartEndIndex-1] + 1);
    FDefineColCount = StartEndIndex;
}
//---------------------------------------------------------------------------
//   DrawExpandFold
//---------------------------------------------------------------------------
void DrawExpandFold(HDC dc, int X, int Y, bool Expanded)
{
   HPEN pen = CreatePen(PS_SOLID, 1, TColor(RGB(128, 128, 128)));
   HGDIOBJ oldpen = SelectObject(dc, pen);
   MoveToEx(dc, X - 4, Y - 4, NULL);
   LineTo(dc, X + 4, Y - 4);
   LineTo(dc, X + 4, Y + 4);
   LineTo(dc, X - 4, Y + 4);
   LineTo(dc, X - 4, Y - 4);

   HPEN temppen = CreatePen(PS_SOLID, 1, clBlack);
   SelectObject(dc, temppen);
   DeleteObject(pen);
   pen = temppen;
   
   MoveToEx(dc, X - 2, Y, NULL);
   LineTo(dc, X + 3, Y);
   if(Expanded)
   {
       MoveToEx(dc, X, Y - 2, NULL);
       LineTo(dc, X, Y + 3);
   }
   SelectObject(dc, oldpen);
   DeleteObject(pen);
}                                     
//---------------------------------------------------------------------------
//   TFrameDraw
//---------------------------------------------------------------------------
TFrameDraw::TFrameDraw()
		   : ItemHeight(12), LineColor(clBlack), BkPattern(0),
             BkColor(clWhite), Sign(0), Abstract(0), BorderType(btRectangle)
{
   ShowItems[0].DataIndex = 1;
   ShowItems[1].DataIndex = -1;
   ShowItems[2].DataIndex = 16;
   ShowItems[3].DataIndex = 17;
   ShowItems[4].DataIndex = 18;
   ShowItems[5].DataIndex = 19;
   ShowItems[6].DataIndex = 37;
   ShowItems[7].DataIndex = 38;
   ShowItems[8].DataIndex = 31;
   ShowItems[9].DataIndex = 4;
}
//---------------------------------------------------------------------------
void TFrameDraw::Init(HDC dc)
{
   String dstr = "测试";
   RECT r;
   r.top = 0;
   r.left = 0;
   r.right = 1200;
   r.bottom = 1000;
	::DrawText(dc, dstr.c_str(), dstr.Length(), &r, DT_CALCRECT | DT_SINGLELINE);
   ItemHeight = r.bottom - r.top + 4;
}
//---------------------------------------------------------------------------
void TFrameDraw::Draw(HDC dc, int Left, int Top, int Right, int Bottom,
			 int Margin, TPrjObject*AObj, bool Focus, TExpandFoldType ExpandFold)
{
    SetBkMode(dc, TRANSPARENT);
    HPEN Pen;
    HGDIOBJ oldPen;
    HBRUSH Brush;
    HGDIOBJ oldBrush;
    COLORREF oldcolor = SetTextColor(dc, BkColor);
    Brush= CreatePatternBrush(TPattern::Pattern(BkPattern));
    Pen = CreatePen(PS_SOLID, 2, LineColor);
    oldBrush = SelectObject(dc, Brush);
    oldPen = SelectObject(dc, Pen);
    POINT p[7];
    int pCount;
    switch(BorderType)
    {
        case btRectangle: //矩形
             p[0].x = Left;
             p[0].y = Top;
             p[1].x = Right;
             p[1].y = Top;
             p[2].x = Right;
             p[2].y = Bottom;
             p[3].x = Left;
             p[3].y = Bottom;
             p[4] = p[0];
             pCount = 5;
             break;
        case btParallelogram1://平行四边形
             p[0].x = Left + Margin - 2;
             p[0].y = Top;
             p[1].x = Right;
             p[1].y = Top;
             p[2].x = Right - Margin + 2;
             p[2].y = Bottom;
             p[3].x = Left;
             p[3].y = Bottom;
             p[4] = p[0];
             pCount = 5;
             break;
        case btParallelogram2://平行四边形
             p[0].x = Left;
             p[0].y = Top;
             p[1].x = Right - Margin + 2;
             p[1].y = Top;
             p[2].x = Right;
             p[2].y = Bottom;
             p[3].x = Left + Margin - 2;
             p[3].y = Bottom;
             p[4] = p[0];
             pCount = 5;
             break;
        case btDiamond:        //菱形
             p[0].x = Left + Margin - 2;
             p[0].y = Top;
             p[1].x = Right - Margin + 2;
             p[1].y = Top;
             p[2].x = Right;
             p[2].y = (Top + Bottom) / 2;
             p[3].x = Right - Margin + 2;
             p[3].y = Bottom;
             p[4].x = Left + Margin - 2;
             p[4].y = Bottom;
             p[5].x = Left;
             p[5].y = (Top + Bottom) / 2;
             p[6] = p[0];
             pCount = 7;
             break;
        default:
             ;
    }
    Polygon(dc, p, pCount);
    SelectObject(dc, oldPen);
    DeleteObject(Pen);
    SelectObject(dc, oldBrush);
    DeleteObject(Brush);
    SetTextColor(dc, oldcolor);
//--------------------------------------------------------------------------
    Pen = CreatePen(PS_SOLID, 1, LineColor);
    oldPen = SelectObject(dc, Pen);

    if(Sign)
    {
        MoveToEx(dc, Left + Margin, Bottom, NULL);
        LineTo(dc, Right - Margin, Top);
        if(Sign == 2)
        {
           MoveToEx(dc, Left + Margin, Top, NULL);
           LineTo(dc, Right - Margin, Bottom);
        }
    }

	int DrawItemHeight = ItemHeight;
    int ItemCount = (Bottom - Top - 2) / DrawItemHeight;
    int ShowItemIndex = 0;
    String str1;
    String str2;
    bool       Have1Str;
    for(int i = 0; i < ItemCount && ShowItemIndex < 10; i++)
    {
                if(ShowItems[ShowItemIndex].DataIndex == -1 &&
                   ShowItems[ShowItemIndex+1].DataIndex != -1)
                {
                    Have1Str = true;
                    str1 = ShowItems[ShowItemIndex+1].GetTitle() + String(":")
                         +(AObj ? ShowItems[ShowItemIndex+1].GetData(*AObj):
                                    String(""));
                }else if(ShowItems[ShowItemIndex].DataIndex != -1 &&
                   ShowItems[ShowItemIndex+1].DataIndex == -1)
                {
                    Have1Str = true;
                    str1 = ShowItems[ShowItemIndex].GetTitle() + String(":") +
                           (AObj ? ShowItems[ShowItemIndex].GetData(*AObj) :
                                    String(""));
                }else if(ShowItems[ShowItemIndex].DataIndex == -1 &&
                   ShowItems[ShowItemIndex+1].DataIndex == -1)
                {
                    Have1Str = true;
                    str1 = "";
                }else
                {
                    Have1Str = false;
                    str1 = ShowItems[ShowItemIndex].GetTitle() + String(":") +
                           (AObj != NULL ? ShowItems[ShowItemIndex].GetData(*AObj) :
                                           String(""));
                    str2 = ShowItems[ShowItemIndex+1].GetTitle() + String(":") +
                           (AObj != NULL ? ShowItems[ShowItemIndex+1].GetData(*AObj) :
                                           String(""));
                }
                if(AObj && AObj->Critical)
                {
                  if(ShowItems[ShowItemIndex+1].DataIndex==4)
                  {
                    ShowItems[ShowItemIndex+1].DataIndex=33;
                    if(Have1Str)
                      str1 = str1+" ("+ShowItems[ShowItemIndex+1].GetData(*AObj)+")";
                    else
                      str2 = str2+" ("+ShowItems[ShowItemIndex+1].GetData(*AObj)+")";
                    ShowItems[ShowItemIndex+1].DataIndex=4;
                  }
                  if(ShowItems[ShowItemIndex].DataIndex==4)
                  {
                    ShowItems[ShowItemIndex].DataIndex=33;
                    str1 = str1+" ("
                               +ShowItems[ShowItemIndex].GetData(*AObj)
                               +")";
                    ShowItems[ShowItemIndex].DataIndex=4;
                  }
                }
                ShowItemIndex += 2;

                RECT dr;
                if(Have1Str)
                {
                    dr.left = Left + Margin;
                    dr.right = Right - Margin;
                    dr.top = Top + 2 + DrawItemHeight * i;
					dr.bottom = Top + 2 + DrawItemHeight * (i+1);
					DrawText(dc, str1.c_str(), str1.Length(), &dr,
						 DT_SINGLELINE | DT_VCENTER);
				}else
				{
					dr.left = Left + Margin;
                    dr.right = (Left + Right) / 2;
                    dr.top = Top + 2 + DrawItemHeight * i;
					dr.bottom = Top + 2 + DrawItemHeight * (i+1);
					DrawText(dc, str1.c_str(), str1.Length(), &dr,
						 DT_SINGLELINE | DT_VCENTER);
					dr.left = dr.right;
					dr.right = Right - Margin;
					DrawText(dc, str2.c_str(), str2.Length(), &dr,
						 DT_SINGLELINE | DT_VCENTER);
				}
                MoveToEx(dc, Left + Margin, dr.bottom, NULL);
                LineTo(dc, Right - Margin, dr.bottom);
    }

    if(Abstract)
    {
    }

    SelectObject(dc, oldPen);
    DeleteObject(Pen);

    if(Focus)
    {
        HRGN invert = CreatePolygonRgn(p, pCount, ALTERNATE);
        InvertRgn(dc, invert);
        DeleteObject(invert);
    }
    switch(ExpandFold)
    {
        case eftNone:
            break;
        case eftExpanded:
            DrawExpandFold(dc, Left + 5, Top - 8, true);
            break;
        case eftFolded:
            DrawExpandFold(dc, Left + 5, Top - 8, false);
            break;
        default:
             throw Exception("TFrameDraw::Draw ExpandFold未定义");
    }
}
//---------------------------------------------------------------------------
//TNCLinkDraw
//---------------------------------------------------------------------------
TNCLinkDraw::TNCLinkDraw(int PWidth)
{
   PenWidth=PWidth;
}
void TNCLinkDraw::Draw(HDC dc, POINT* p, int pCount, int CornerSize)
{
    if(pCount < 2)
        return;
    HPEN pen = CreatePen(PS_SOLID, PenWidth, Color);
    HGDIOBJ oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(Color);
    HGDIOBJ oldbrush = SelectObject(dc, brush);


	StackArray< POINT,512 > dp(pCount*2);
	int dpIndex = 0;
	dp[dpIndex] = p[0];
	dpIndex++;
    for(int i = 1; i < pCount - 1; i++)
    {
        if(p[i-1].x < p[i].x && p[i-1].y == p[i].y)//向右
        {
            dp[dpIndex].x = p[i].x - CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i-1].x > p[i].x && p[i-1].y == p[i].y)//向左
        {
            dp[dpIndex].x = p[i].x + CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i-1].y < p[i].y && p[i-1].x == p[i].x)//向下
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y - CornerSize;
        }else if(p[i-1].y > p[i].y && p[i-1].x == p[i].x)//向上
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y + CornerSize;
        }
        dpIndex++;

        if(p[i].x < p[i+1].x && p[i].y == p[i+1].y)//向右
        {
            dp[dpIndex].x = p[i].x + CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i].x > p[i+1].x && p[i].y == p[i+1].y)//向左
        {
            dp[dpIndex].x = p[i].x - CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i].y < p[i+1].y && p[i].x == p[i+1].x)//向下
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y + CornerSize;
        }else if(p[i].y > p[i+1].y && p[i].x == p[i+1].x)//向上
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y - CornerSize;
        }
        dpIndex++;
    }
    if(p[pCount-1].x - 8 > dp[dpIndex-1].x)
        dp[dpIndex].x = p[pCount-1].x - 8;
    else
        dp[dpIndex].x = dp[dpIndex-1].x+1;
    dp[dpIndex].y = p[pCount-1].y;
    dpIndex++;
    dp[dpIndex].x = p[pCount-1].x - 1;
    dp[dpIndex].y = p[pCount-1].y;
    dpIndex++;
    Polyline(dc, dp, dpIndex);

    int ArrowSize = 5;
    if(CornerSize < 5)
        ArrowSize = CornerSize;
    POINT pArrow[4];
    //向右
    pArrow[0].x = p[pCount-1].x;
    pArrow[0].y = p[pCount-1].y;
    pArrow[1].x = p[pCount-1].x - ArrowSize;
    pArrow[1].y = p[pCount-1].y - ArrowSize;
    pArrow[2].x = p[pCount-1].x - ArrowSize;
    pArrow[2].y = p[pCount-1].y + ArrowSize;
    pArrow[3] = pArrow[0];
    Polygon(dc, pArrow, 4);

    SelectObject(dc, oldpen);
    DeleteObject(pen);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
}
//---------------------------------------------------------------------------
void TNCLinkDraw::DrawWidthBridge(HDC dc, POINT*p, int pCount,
                         int BridgeIndex, int BridgePointCount,
                         POINT*BridgePoint, int CornerSize)
{
    if(pCount < 2)
        return;
    HPEN pen = CreatePen(PS_SOLID, PenWidth, Color);
    HGDIOBJ oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(Color);
    HGDIOBJ oldbrush = SelectObject(dc, brush);

	StackArray< POINT,512 > dp(pCount*2);
    int dpIndex = 0;
    dp[dpIndex] = p[0];
    dpIndex++;
    for(int i = 1; i < pCount - 1; i++)
    {
        if(p[i-1].x < p[i].x && p[i-1].y == p[i].y)//向右
        {
            dp[dpIndex].x = p[i].x - CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i-1].x > p[i].x && p[i-1].y == p[i].y)//向左
        {
            dp[dpIndex].x = p[i].x + CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i-1].y < p[i].y && p[i-1].x == p[i].x)//向下
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y - CornerSize;
        }else if(p[i-1].y > p[i].y && p[i-1].x == p[i].x)//向上
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y + CornerSize;
        }
        dpIndex++;

        if(p[i].x < p[i+1].x && p[i].y == p[i+1].y)//向右
        {
            dp[dpIndex].x = p[i].x + CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i].x > p[i+1].x && p[i].y == p[i+1].y)//向左
        {
            dp[dpIndex].x = p[i].x - CornerSize;
            dp[dpIndex].y = p[i].y;
        }else if(p[i].y < p[i+1].y && p[i].x == p[i+1].x)//向下
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y + CornerSize;
        }else if(p[i].y > p[i+1].y && p[i].x == p[i+1].x)//向上
        {
            dp[dpIndex].x = p[i].x;
            dp[dpIndex].y = p[i].y - CornerSize;
        }
        dpIndex++;
    }
    if(p[pCount-1].x - 8 > dp[dpIndex-1].x)
        dp[dpIndex].x = p[pCount-1].x - 8;
    else
        dp[dpIndex].x = dp[dpIndex-1].x+1;
    dp[dpIndex].y = p[pCount-1].y;
    dpIndex++;
    dp[dpIndex].x = p[pCount-1].x - 1;
    dp[dpIndex].y = p[pCount-1].y;
    dpIndex++;
    if(BridgePointCount > 0 && CornerSize >= 4)
    {
         int BridgePointStart = BridgeIndex * 2;
         Polyline(dc, dp, BridgePointStart+1);
         Polyline(dc, &(dp[BridgePointStart+1]), dpIndex - BridgePointStart - 1);
         DrawBridgeLine(dc, dp[BridgePointStart], dp[BridgePointStart+1],
                       BridgePointCount, BridgePoint);
    }else
    {
         Polyline(dc, dp, dpIndex);
    }

    int ArrowSize = 5;
    if(CornerSize < 5)
        ArrowSize = CornerSize;
    POINT pArrow[4];
    //向右
    pArrow[0].x = p[pCount-1].x;
    pArrow[0].y = p[pCount-1].y;
    pArrow[1].x = p[pCount-1].x - ArrowSize;
    pArrow[1].y = p[pCount-1].y - ArrowSize;
    pArrow[2].x = p[pCount-1].x - ArrowSize;
    pArrow[2].y = p[pCount-1].y + ArrowSize;
    pArrow[3] = pArrow[0];
    Polygon(dc, pArrow, 4);

    SelectObject(dc, oldpen);
    DeleteObject(pen);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
}
//---------------------------------------------------------------------------
void TNCLinkDraw::DrawBridgeLine(HDC dc, POINT Start, POINT End, int BridgePointCount, POINT*BridgePoint)
{
    if(Start.x != End.x || Start.x != BridgePoint[0].x)
         throw Exception("TNCLinkDraw::DrawBridgeLine 逻辑错误！");
    if(Start.y > End.y)
    {//交换保持从上到下
         POINT temp = Start;
         Start = End;
         End = temp;
    }
    MoveToEx(dc, Start.x, Start.y, NULL);
    for(int i = 0; i < BridgePointCount; i++)
    {
         LineTo(dc, BridgePoint[i].x, BridgePoint[i].y - 4);
         Arc(dc, BridgePoint[i].x - 5, BridgePoint[i].y - 5,
                 BridgePoint[i].x + 5, BridgePoint[i].y + 5,
                 BridgePoint[i].x, BridgePoint[i].y - 5,
                 BridgePoint[i].x+1, BridgePoint[i].y + 5);
         MoveToEx(dc, BridgePoint[i].x, BridgePoint[i].y + 4, NULL);
    }
    LineTo(dc, End.x, End.y);
}
//---------------------------------------------------------------------------
//TEventDraw
//---------------------------------------------------------------------------
void TEventDraw::Init(HDC dc, int MaxEvent)
{
   String dstr = IntToStr(MaxEvent);
//   RECT r;
//   r.top = 0;
//   r.left = 0;
//   r.right = 1000;
//   r.bottom = 1000;
//   ::DrawText(dc, dstr.c_str(), dstr.Length(), &r, DT_CALCRECT | DT_SINGLELINE);
   SIZE size;
   size.cx = 1000;
   GetTextExtentPoint32(dc,dstr.c_str(),dstr.Length(),&size);
   int width = size.cx; //r.right - r.left;
   width += width % 2;
   int height = size.cy;//r.bottom - r.top;
   height += height %2;
   Radial = width > height ? width : height;
   Radial = Radial / 2 + 2;
//   if(Radial < 10)
//      Radial = 10;
   if(size.cx ==1000)
     Radial = 8;
   else if(Radial < 3)
      Radial = 3;
}
//---------------------------------------------------------------------------
void TEventDraw::Draw(HDC dc, const POINT& CircleCentre, int Event, bool Focus)
{
   COLORREF oldbkcolor = SetBkColor(dc, BackColor);
   COLORREF oldtextcolor = SetTextColor(dc, FontColor);
   HBRUSH  brush = CreateSolidBrush(BackColor);
   HGDIOBJ oldbrush = SelectObject(dc, brush);
   HPEN    pen = CreatePen(PS_SOLID, 1, LineColor);//1
   HGDIOBJ oldpen = SelectObject(dc, pen);
   SetBkMode(dc, TRANSPARENT);

   String dstr = IntToStr(Event);
   RECT rect;
   rect.left = CircleCentre.x - Radial;
   rect.top = CircleCentre.y - Radial;
   rect.right = CircleCentre.x + Radial;
   rect.bottom = CircleCentre.y + Radial;
   Ellipse(dc, rect.left, rect.top, rect.right+1, rect.bottom+1);
   DrawText(dc, dstr.c_str(), dstr.Length(), &rect,
			   DT_SINGLELINE | DT_VCENTER | DT_CENTER);
   SelectObject(dc, oldbrush);
   SelectObject(dc, oldpen);
   DeleteObject(brush);
   DeleteObject(pen);
   SetBkColor(dc, oldbkcolor);
   SetTextColor(dc, oldtextcolor);

   if(Focus)
   {
       HRGN invert = CreateEllipticRgn(rect.left-1, rect.top-1,
                                       rect.right+3, rect.bottom+3);
       InvertRgn(dc, invert);
       DeleteObject(invert);
   }
}
//---------------------------------------------------------------------------
//   TBridgeLine
//---------------------------------------------------------------------------
void TBridgeLine::Draw(HDC dc, int X)
{
   switch(Direction)
   {
       case bldLeft: //半圆在左边
           Arc(dc, X - 8, Y - 8, X + 8, Y + 8,
                   X, Y - 8, X, Y + 8);
           break;
       case bldRight: //半园在右边
           Arc(dc, X - 8, Y - 8, X + 8, Y + 8,
                   X + 8, Y, X+1, Y - 8);
           Arc(dc, X - 8, Y - 8, X + 8, Y + 8,
                   X+1, Y + 8, X + 8, Y);
           break;
       default:
           throw Exception("桥线方向错误");
   }
}
//---------------------------------------------------------------------------
void TBridgeLine::Draw(HDC dc, int X, int Y,const int Radii)
{
   switch(Direction)
   {
       case bldLeft: //半圆在左边
           Arc(dc, X - Radii, Y - Radii, X + Radii, Y + Radii,
                   X, Y - Radii, X, Y + Radii);
           break;
       case bldRight: //半园在右边
           Arc(dc, X - Radii, Y - Radii, X + Radii, Y + Radii,
                   X + Radii, Y, X+1, Y - Radii);
           Arc(dc, X - Radii, Y - Radii, X + Radii, Y + Radii,
                   X+1, Y + Radii, X + Radii, Y);
           break;
       default:
           throw Exception("桥线方向错误");
   }
}
//---------------------------------------------------------------------------
//   TTaskLine
//---------------------------------------------------------------------------
void TTaskLine::Draw(HDC dc, int x1, int x2, int Wavex1, int Wavex2, int y, int R)
{
    COLORREF DrawColor = Color;
    if(abs(x1 - x2) < 3)
        return;
    HPEN pen;
    switch(Style)
    {
        case lsBigSolid:
            pen = CreatePen(PS_SOLID, 3, DrawColor);
            break;
        case lsSmallSolid:
            pen = CreatePen(PS_SOLID, 1, DrawColor);
            break;
        case lsSmallDot:
            pen = CreatePen(PS_DOT, 0, DrawColor);
            break;
    }
    HGDIOBJ oldpen = SelectObject(dc, pen);

    MoveToEx(dc, x1, y, NULL);
    LineTo(dc, x2, y);

    SelectObject(dc, oldpen);
    DeleteObject(pen);

    WaveLine.Color = DrawColor;
    WaveLine.Draw(dc, Wavex1, y, Wavex2, y);
/*
    POINT pArrow[4];
    int EndX = x2 < Wavex2 ? Wavex2 : x2;
    //向右
    pArrow[0].x = EndX;
    pArrow[0].y = y;
    pArrow[1].x = EndX - 5;
    pArrow[1].y = y - 5;
    pArrow[2].x = EndX - 5;
    pArrow[2].y = y + 5;
    pArrow[3] = pArrow[0];

    pen = CreatePen(PS_SOLID, 1, DrawColor);
    oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(DrawColor);
    HGDIOBJ oldbrush = SelectObject(dc, brush);
    Polygon(dc, pArrow, 4);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
    SelectObject(dc, oldpen);
    DeleteObject(pen);
*/
    POINT P, CircleCentre;
    P.x = x1;
    P.y = y;
    CircleCentre.x = x2 > Wavex2 ? x2 : Wavex2;
    CircleCentre.y = y;
    POINT pArrow[4];
    ArrowPoints(P, CircleCentre, R, pArrow);

    pen = CreatePen(PS_SOLID, 1, Color);
    oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(DrawColor);
    HGDIOBJ oldbrush = SelectObject(dc, brush);
//    MoveToEx(dc, pArrow[0].x, pArrow[0].y, NULL);
//    LineTo(dc, pArrow[1].x, pArrow[1].y);
//    MoveToEx(dc, pArrow[0].x, pArrow[0].y, NULL);
//    LineTo(dc, pArrow[2].x, pArrow[2].y);
    Polygon(dc, pArrow, 4);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
    SelectObject(dc, oldpen);
    DeleteObject(pen);
}
//---------------------------------------------------------------------------
void TTaskLine::Draw(HDC dc, int x1, int x2, int Wavex1, int Wavex2, int y, int R,bool DrawArrow)
{
    COLORREF DrawColor = Color;
    if( abs(x1 - x2)<3 && abs(Wavex1 - Wavex2)<3 )
        return;
    HPEN pen;
    switch(Style)
    {
        case lsBigSolid:
            pen = CreatePen(PS_SOLID, 3, DrawColor);
            break;
        case lsSmallSolid:
            pen = CreatePen(PS_SOLID, 1, DrawColor);
            break;
        case lsSmallDot:
            pen = CreatePen(PS_DOT, 0, DrawColor);
            break;
    }
    HGDIOBJ oldpen = SelectObject(dc, pen);

    MoveToEx(dc, x1, y, NULL);
    LineTo(dc, x2, y);

    SelectObject(dc, oldpen);
    DeleteObject(pen);

    WaveLine.Color = DrawColor;
    WaveLine.Draw(dc, Wavex1, y, Wavex2, y);

    if(!DrawArrow) return;

    POINT P, CircleCentre;
    P.x = x1;
    P.y = y;
    CircleCentre.x = x2 > Wavex2 ? x2 : Wavex2;
    CircleCentre.y = y;
    POINT pArrow[4];
    ArrowPoints(P, CircleCentre, R, pArrow);

    pen = CreatePen(PS_SOLID, 1, Color);
    oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(DrawColor);
    HGDIOBJ oldbrush = SelectObject(dc, brush);
//    MoveToEx(dc, pArrow[0].x, pArrow[0].y, NULL);
//    LineTo(dc, pArrow[1].x, pArrow[1].y);
//    MoveToEx(dc, pArrow[0].x, pArrow[0].y, NULL);
//    LineTo(dc, pArrow[2].x, pArrow[2].y);
    Polygon(dc, pArrow, 4);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
    SelectObject(dc, oldpen);
    DeleteObject(pen);
}
//---------------------------------------------------------------------------
//   TVirtualLine
//---------------------------------------------------------------------------
//=true:是一条斜线
bool IsBiasLine(const POINT& P, const POINT& CircleCentre)
{
  return (abs(P.y - CircleCentre.y)>2) && (abs(P.x - CircleCentre.x)>2);
}
//---------------------------------------------------------------------------
void TVirtualLine::Draw(HDC dc, const POINT& P, const POINT& CircleCentre, int R)
{
    COLORREF DrawColor = Color;
    if(abs(P.x - CircleCentre.x) < 3 && abs(P.y - CircleCentre.y) < 3)
        return;
    HPEN pen;
    switch(Style)
    {
        case lsBigSolid:
            pen = CreatePen(PS_SOLID, 3, DrawColor);
            break;
        case lsSmallDot:
            pen = CreatePen(PS_DOT, 0, DrawColor);
            break;
    }
    HGDIOBJ oldpen = SelectObject(dc, pen);

    MoveToEx(dc, P.x, P.y, NULL);
    LineTo(dc, CircleCentre.x, CircleCentre.y);
    SelectObject(dc, oldpen);
    DeleteObject(pen);

    POINT pArrow[4];
    ArrowPoints(P, CircleCentre, R, pArrow);

    pen = CreatePen(PS_SOLID, 1, DrawColor);
    oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(DrawColor);
    HGDIOBJ oldbrush = SelectObject(dc, brush);
    MoveToEx(dc, pArrow[0].x, pArrow[0].y, NULL);
    LineTo(dc, pArrow[1].x, pArrow[1].y);
    MoveToEx(dc, pArrow[0].x, pArrow[0].y, NULL);
    LineTo(dc, pArrow[2].x, pArrow[2].y);
    //Polygon(dc, pArrow, 4);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
    SelectObject(dc, oldpen);
    DeleteObject(pen);
}
void TVirtualLine::Draw(HDC dc, POINT*pLine, int& PointCount, int R)
{
 TVirtualLine::Draw(dc, pLine, PointCount, R ,true , false);
}
void TVirtualLine::Draw(HDC dc, POINT*pLine, int& PointCount, int R ,bool DrawArrow,bool DrawSolid)
{
    if(PointCount<2) return;
    COLORREF DrawColor = Color;
    if(abs(pLine[0].x - pLine[PointCount-1].x) < 3 && abs(pLine[0].y - pLine[PointCount-1].y) < 3)
        return;
    HPEN pen;
    if(DrawSolid)
      pen = CreatePen(PS_SOLID, 1, DrawColor);
    else switch(Style)
    {
        case lsBigSolid:
            pen = CreatePen(PS_SOLID, 3, DrawColor);
            break;
        case lsSmallDot:
            pen = CreatePen(PS_DOT, 0, DrawColor);       //only width=0 then print dot
            break;
    }
    HGDIOBJ oldpen = SelectObject(dc, pen);

    MoveToEx(dc, pLine[0].x, pLine[0].y, NULL);
    for(int i=1; i<PointCount; i++)
    {
      LineTo(dc, pLine[i].x, pLine[i].y);
    }

    SelectObject(dc, oldpen);
    DeleteObject(pen);

    if(!DrawArrow) return;

    POINT pArrow[4];
    ArrowPoints(pLine[PointCount-2], pLine[PointCount-1], R, pArrow);

    pen = CreatePen(PS_SOLID, 1, DrawColor);
    oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(DrawColor);
    HGDIOBJ oldbrush = SelectObject(dc, brush);
	Polygon(dc, pArrow, 4);
    SelectObject(dc, oldbrush);
    DeleteObject(brush);
    SelectObject(dc, oldpen);
    DeleteObject(pen);
}
//---------------------------------------------------------------------------
void TVirtualLine::Draw(HDC dc,TList* Line, int R ,bool DrawArrow,bool DrawSolid)
{
    if(Line->Count<1) return;
    COLORREF DrawColor = Color;
    HPEN pen;
    if(DrawSolid)
      pen = CreatePen(PS_SOLID, 1, DrawColor);
    else switch(Style)
    {
        case lsBigSolid:
            pen = CreatePen(PS_SOLID, 3, DrawColor);
            break;
        case lsSmallDot:
            pen = CreatePen(PS_DOT, 0, DrawColor);       //only width=0 then print dot
            break;
    }
    HGDIOBJ oldpen = SelectObject(dc, pen);
    TLinePoint *linePt;
    int iCount = Line->Count;
    for(int i=0; i<iCount; i++)
    {
      linePt = (TLinePoint *)Line->Items[i];
      MoveToEx(dc, linePt->x1, linePt->y1, NULL);
      LineTo(dc, linePt->x2, linePt->y2);
    }

    SelectObject(dc, oldpen);
    DeleteObject(pen);

    if(!DrawArrow) return;

    POINT pArrow[4];
    POINT p1,p2;
    p1.x = linePt->x1;
    p1.y = linePt->y1;
    p2.x = linePt->x2;
    p2.y = linePt->y2;
    ArrowPoints( p1, p2, R, pArrow);

    pen = CreatePen(PS_SOLID, 1, DrawColor);
    oldpen = SelectObject(dc, pen);
    HBRUSH brush = CreateSolidBrush(DrawColor);
    HGDIOBJ oldbrush = SelectObject(dc, brush);
	Polygon(dc, pArrow, 4);
	SelectObject(dc, oldbrush);
	DeleteObject(brush);
	SelectObject(dc, oldpen);
	DeleteObject(pen);
}
//---------------------------------------------------------------------------
//   TWaveLine
//---------------------------------------------------------------------------
void TWaveLine::Draw(HDC dc, int Left, int Top, int Right, int Bottom)
{
/*
   if(Left == Right)
   {
       if(abs(Top - Bottom) < 3)
           return;
       POINT *p;
       POINT pp[10008];
       p = pp;
       bool Free = false;
       if(abs(Top-Bottom) > 20000)
       {
           p = new POINT[abs(Bottom-Top)/2 + 8];
           Free = true;
       }
       int pcount = 0;
       int atop = Top;
       int abottom = Bottom;
       if(Bottom < Top)
       {
          atop = Bottom;
          abottom = Top;
       }
       int x = Left;
       p[pcount].x = x;
       p[pcount].y = atop;
       pcount++;
       atop += 1;
       x += 1;
       p[pcount].x = x;
       p[pcount].y = atop;
       pcount++;
       do{
           atop += 2;
           x -= 2;
           p[pcount].x = x;
           p[pcount].y = atop;
           pcount++;
           atop += 2;
           x += 2;
           p[pcount].x = x;
           p[pcount].y = atop;
           pcount++;
       }while(atop+4 < abottom);
       p[pcount].x = x;
       p[pcount].y = atop;
       pcount++;
       Polyline(dc, p, pcount);
       if(Free)
          delete [] p;
   }else if(Top == Bottom)
   {
       if(abs(Left - Right) < 3)
          return;
       POINT *p;
       POINT pp[10008];
       p = pp;
       bool Free = false;
       if(abs(Right-Left) > 20000)
       {
           p = new POINT[abs(Right-Left)/2 + 8];
           Free = true;
       }
       int pcount = 0;
       int aleft = Left;
       int aright = Right;
       if(Right < Left)
       {
          aleft = Right;
          aright = Left;
       }
       int y = Top;
       p[pcount].x = aleft;
       p[pcount].y = y;
       pcount++;
       aleft += 1;
       y += 1;
       p[pcount].x = aleft;
       p[pcount].y = y;
       pcount++;
       do{
           aleft += 2;
           y -= 2;
           p[pcount].x = aleft;
           p[pcount].y = y;
           pcount++;
           aleft += 2;
           y += 2;
           p[pcount].x = aleft;
           p[pcount].y = y;
           pcount++;
       }while(aleft+4 < aright);
       p[pcount].x = aright;
       p[pcount].y = Top;
       pcount++;
       Polyline(dc, p, pcount);
       if(Free)
          delete [] p;
   }else
       throw Exception("波浪线方向错误");
*/
   if(Left == Right)
   {
       if(abs(Top - Bottom) < 3)
           return;
       HPEN    pen = CreatePen(PS_SOLID, 1, Color);
       HGDIOBJ oldpen = SelectObject(dc, pen);
       POINT *p;
       POINT pp[10008];
       p = pp;
       bool Free = false;
       if(abs(Top-Bottom) > 20000)
       {
           p = new POINT[abs(Bottom-Top)/2 + 8];
           Free = true;
       }
       int pcount = 0;
       int atop = Top;
       int abottom = Bottom;
       if(Bottom < Top)
       {
          atop = Bottom;
          abottom = Top;
       }
       int x = Left;
       p[pcount].x = x;
       p[pcount].y = atop;
       pcount++;
       atop += 1;
       x += 1;
       p[pcount].x = x;
       p[pcount].y = atop;

       pcount = (abottom - atop) / 2 + 1 + (abottom - atop) % 2;
       asm{
           mov eax, atop
           mov ebx, x
           mov ecx, p
           add ecx, 16
           mov edx, abottom
           add eax, 4
       labelLoop:
           sub eax, 4
           add eax, 2
           sub ebx, 2
           mov [ecx], ebx
           add ecx, 4
           mov [ecx], eax
           add ecx, 4
           add eax, 2
           add ebx, 2
           mov [ecx], ebx
           add ecx, 4
           mov [ecx], eax
           add ecx, 4

           add eax, 4
           cmp eax, edx
           jng labelLoop
           sub eax, 4

           mov edx, Left
           mov [ecx], edx
           add ecx, 4
           mov edx, abottom
           mov [ecx], edx
           mov atop, eax
           mov x, ebx
       }

/*
       do{
           atop += 2;
           x -= 2;
           p[pcount].x = x;
           p[pcount].y = atop;
           pcount++;
           atop += 2;
           x += 2;
           p[pcount].x = x;
           p[pcount].y = atop;
           pcount++;
       }while(atop+4 < abottom);
       p[pcount].x = x;
       p[pcount].y = atop;
       pcount++;
*/
       Polyline(dc, p, pcount);
       SelectObject(dc, oldpen);
       DeleteObject(pen);
       if(Free)
          delete [] p;
   }else if(Top == Bottom)
   {
       if(abs(Left - Right) < 3)
          return;
       HPEN    pen = CreatePen(PS_SOLID, 1, Color);
       HGDIOBJ oldpen = SelectObject(dc, pen);
       POINT *p;
       POINT pp[10008];
       p = pp;
       bool Free = false;
       if(abs(Right-Left) > 20000)
       {
           p = new POINT[abs(Right-Left)/2 + 8];
           Free = true;
       }
       int pcount = 0;
       int aleft = Left;
       int aright = Right;
       if(Right < Left)
       {
          aleft = Right;
          aright = Left;
       }
       int y = Top;
       p[pcount].x = aleft;
       p[pcount].y = y;
       pcount++;
       aleft += 1;
       y += 1;
       p[pcount].x = aleft;
       p[pcount].y = y;
       pcount = (aright - aleft) / 2 + 1 + (aright - aleft) % 2;
       asm{
           mov eax, aleft
           mov ebx, y
           mov ecx, p
           add ecx, 16
           mov edx, aright
           add eax, 4
       labelLoop1:
           sub eax, 4
           add eax, 2
           sub ebx, 2
           mov [ecx], eax
           add ecx, 4
           mov [ecx], ebx
           add ecx, 4
           add eax, 2
           add ebx, 2
           mov [ecx], eax
           add ecx, 4
           mov [ecx], ebx
           add ecx, 4

           add eax, 4
           cmp eax, edx
           jng labelLoop1
           sub eax, 4

           mov edx, aright
           mov [ecx], edx
           add ecx, 4
           mov edx, Top
           mov [ecx], edx
           mov aleft, eax
           mov y, ebx
       }
/*
       do{
           aleft += 2;
           y -= 2;
           p[pcount].x = aleft;
           p[pcount].y = y;
           pcount++;
           aleft += 2;
           y += 2;
           p[pcount].x = aleft;
           p[pcount].y = y;
           pcount++;
       }while(aleft+4 < aright);
       p[pcount].x = aright;
       p[pcount].y = Top;
       pcount++;
*/
       Polyline(dc, p, pcount);
       SelectObject(dc, oldpen);
       DeleteObject(pen);
       if(Free)
          delete [] p;
   }else
	   throw Exception("波浪线方向错误");}


}



