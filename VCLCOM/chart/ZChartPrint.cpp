//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZChartPrint.h"
#include "vclComFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace Vclcomfunc;
TGanttPrint::TGanttPrint(TGantt* AChart)
{
   FChart = AChart;
}
String __fastcall TGanttPrint::GetName()
{
   return "Gantt";
}
HENHMETAFILE __fastcall TGanttPrint::MakeMetalFile(int PageNo)
{
   if(FChart)
   {
	  int PX=XLength();
      int PY=YLength();
      int X = PageNo % PX;
      int Y = PageNo / PX;

      HDC tempdc = GetDC(0);
      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);

      RECT rect;
      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
      ReleaseDC(0, tempdc);
      //画图
      TPrjGrid* PrjGrid=FChart->GetBindGrid();
      RECT gridrect;
      rect.left=0;
      rect.top=0;
      rect.right=FChart->TotalWidth;
      rect.bottom=FChart->TotalHeight;
      gridrect.left =0;
      gridrect.top = 0;
      gridrect.right =PrjGrid->PrintWidth()+1;
      gridrect.bottom =rect.bottom;
      SetBkMode(pvMetaFileDc, TRANSPARENT);    //留边界
      SetViewportOrgEx(pvMetaFileDc,gridrect.right-1+iLeftPageMargin,iTopPageMargin,NULL);
      FChart->Draw(pvMetaFileDc, rect,FChart->TotalHeight);  //先画甘特图
      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
      PrjGrid->Print(pvMetaFileDc, gridrect); //再画左边的列表
      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
      //清边
      HBRUSH Brush = CreateSolidBrush(clWhite);
      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
      RECT r;
      //上边
      r.left = X*iPageWidth;
      r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = r.top+iTopPageMargin-5;
      FillRect(pvMetaFileDc, &r, Brush);
      //下边
      r.left =X*iPageWidth;
      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
      r.right=r.left+iFullPageWidth;
      r.bottom=r.top+iBottomPageMargin+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //左边
      r.left = X*iPageWidth;
      r.top =  Y*iPageHeight;
      r.right=r.left+iLeftPageMargin-5;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //右边
      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
      r.top=Y*iPageHeight;
      r.right=r.left+iRightPageMargin;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);

      SelectObject(pvMetaFileDc, oldBrush);
      DeleteObject(Brush);
      //标题
      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
      SetTextColor(pvMetaFileDc, FTitleFont->Color);
      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = iTopPageMargin+r.top-20;
	  DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
      SelectObject(pvMetaFileDc, oldFont);
      DeleteObject(hTitleFont);

      if(FShowPageNo)//页号
      {
          String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
          HFONT hFont = CreateFontByTFont(FChart->Font);
          SetTextColor(pvMetaFileDc, FChart->Font->Color);
          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
          r.left = X*iPageWidth;
          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
          r.right =iFullPageWidth+r.left;
          r.bottom =r.top+iBottomPageMargin;
		  DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
          SelectObject(pvMetaFileDc, oldFont);
          DeleteObject(hFont);

	  }
      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
      return pvMetaFile;
     }
     return NULL;
}
int __fastcall TGanttPrint::GetPageCount()
{
   return XLength() * YLength();
}
int TGanttPrint::XLength()
{
   int PX = (FChart->TotalWidth+GridWidth())/iPageWidth+1;
   return PX ;
}
int TGanttPrint::YLength()
{
   int PY = FChart->TotalHeight/iPageHeight+1;
   return PY;
}
int TGanttPrint::GridWidth()
{
   if(FChart->GetBindGrid())
   {
       TPrjGrid* PrjGrid = FChart->GetBindGrid();
       return PrjGrid->PrintWidth();
   }
   return 0;
}
void TGanttPrint::PaintGrid(HDC dc, RECT dr)
{
   if(FChart->GetBindGrid())
   {
       TPrjGrid* PrjGrid = FChart->GetBindGrid();
       PrjGrid->Print(dc, dr);
   }
}
//--------------------------------------------------------------------------------
//  TNetChartPrint
//--------------------------------------------------------------------------------
TNetChartPrint::TNetChartPrint(TNetChart* AChart)
{
   FChart = AChart;
}
String __fastcall TNetChartPrint::GetName()
{
   return "NetChart";
}
HENHMETAFILE __fastcall TNetChartPrint:: MakeMetalFile( int PageNo)
{
   if(FChart)
   {
      int PX=XLength();
      int PY=YLength();
      int X = PageNo % PX;
      int Y = PageNo / PX;

      HDC tempdc = GetDC(0);
      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);

      RECT rect;
      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
      ReleaseDC(0, tempdc);
      //画图
      rect.left=0;
      rect.top=0;
      rect.right=FChart->TotalWidth;
      rect.bottom=FChart->TotalHeight;
      SetBkMode(pvMetaFileDc, TRANSPARENT);
      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
      FChart->Draw(pvMetaFileDc, rect);
      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
      //清边
      HBRUSH Brush = CreateSolidBrush(clWhite);
      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
      RECT r;
      //上边
      r.left = X*iPageWidth;
      r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = r.top+iTopPageMargin-5;
      FillRect(pvMetaFileDc, &r, Brush);
      //下边
      r.left =X*iPageWidth;
      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
      r.right=r.left+iFullPageWidth;
      r.bottom=r.top+iBottomPageMargin+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //左边
      r.left = X*iPageWidth;
      r.top =  Y*iPageHeight;
      r.right=r.left+iLeftPageMargin-5;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //右边
      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
      r.top=Y*iPageHeight;
      r.right=r.left+iRightPageMargin;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);

      SelectObject(pvMetaFileDc, oldBrush);
      DeleteObject(Brush);
      //标题
      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
      SetTextColor(pvMetaFileDc, FTitleFont->Color);
      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = iTopPageMargin+r.top-20;
	  DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
      SelectObject(pvMetaFileDc, oldFont);
      DeleteObject(hTitleFont);

      if(FShowPageNo)//页号
      {
          String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
          HFONT hFont = CreateFontByTFont(FChart->Font);
          SetTextColor(pvMetaFileDc, FChart->Font->Color);
          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
          r.left = X*iPageWidth;
          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
          r.right =iFullPageWidth+r.left;
          r.bottom =r.top+iBottomPageMargin;
		  DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
          SelectObject(pvMetaFileDc, oldFont);
          DeleteObject(hFont);

      }
      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
      return pvMetaFile;
     }
     return NULL;
}

int __fastcall TNetChartPrint::GetPageCount()
{
   return XLength() * YLength();
}
int TNetChartPrint::XLength()
{
   int PX = FChart->TotalWidth/iPageWidth+1;
   return PX ;
}
int TNetChartPrint::YLength()
{
   int PY = FChart->TotalHeight/iPageHeight+1;
   return PY;
}
//--------------------------------------------------------------------------------
//  TOrgChartPrint
//--------------------------------------------------------------------------------
//TOrgChartPrint::TOrgChartPrint(TOrgChart* AChart)
//{
//   FChart = AChart;
//}
//String __fastcall TOrgChartPrint::GetName()
//{
//   return "NetChart";
//}
//HENHMETAFILE __fastcall TOrgChartPrint:: MakeMetalFile( int PageNo)
//{
//   if(FChart)
//   {
//      int PX=XLength();
//      int PY=YLength();
//      int X = PageNo % PX;
//      int Y = PageNo / PX;
//
//      HDC tempdc = GetDC(0);
//      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
//      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
//      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
//      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);
//
//      RECT rect;
//      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
//      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
//      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
//      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
//      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
//      ReleaseDC(0, tempdc);
//      //画图
//      rect.left=0;
//      rect.top=0;
//      rect.right=FChart->TotalWidth;
//      rect.bottom=FChart->TotalHeight;
//      SetBkMode(pvMetaFileDc, TRANSPARENT);
//      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
//      FChart->Draw(pvMetaFileDc, rect);
//      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
//      //清边
//      HBRUSH Brush = CreateSolidBrush(clWhite);
//      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
//      RECT r;
//      //上边
//      r.left = X*iPageWidth;
//      r.top = Y*iPageHeight;//上边
//      r.right = iFullPageWidth+r.left;
//      r.bottom = r.top+iTopPageMargin-5;
//      FillRect(pvMetaFileDc, &r, Brush);
//      //下边
//      r.left =X*iPageWidth;
//      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
//      r.right=r.left+iFullPageWidth;
//      r.bottom=r.top+iBottomPageMargin+100;
//      FillRect(pvMetaFileDc, &r, Brush);
//      //左边
//      r.left = X*iPageWidth;
//      r.top =  Y*iPageHeight;
//      r.right=r.left+iLeftPageMargin-5;
//      r.bottom=r.top+iFullPageHeight+100;
//      FillRect(pvMetaFileDc, &r, Brush);
//      //右边
//      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
//      r.top=Y*iPageHeight;
//      r.right=r.left+iRightPageMargin;
//      r.bottom=r.top+iFullPageHeight+100;
//      FillRect(pvMetaFileDc, &r, Brush);
//
//      SelectObject(pvMetaFileDc, oldBrush);
//      DeleteObject(Brush);
//      //标题
//      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
//      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
//      SetTextColor(pvMetaFileDc, FTitleFont->Color);
//      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
//      r.right = iFullPageWidth+r.left;
//      r.bottom = iTopPageMargin+r.top-20;
//      DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
//      SelectObject(pvMetaFileDc, oldFont);
//      DeleteObject(hTitleFont);
//
//      if(FShowPageNo)//页号
//      {
//          String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
//          HFONT hFont = CreateFontByTFont(FChart->Font);
//          SetTextColor(pvMetaFileDc, FChart->Font->Color);
//          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
//          r.left = X*iPageWidth;
//          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
//          r.right =iFullPageWidth+r.left;
//          r.bottom =r.top+iBottomPageMargin;
//          DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
//          SelectObject(pvMetaFileDc, oldFont);
//          DeleteObject(hFont);
//
//      }
//      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
//      return pvMetaFile;
//     }
//     return NULL;
//}
//
//int __fastcall TOrgChartPrint::GetPageCount()
//{
//   return XLength() * YLength();
//}
//int TOrgChartPrint::XLength()
//{
//   int PX = FChart->TotalWidth/iPageWidth+1;
//   return PX ;
//}
//int TOrgChartPrint::YLength()
//{
//   int PY = FChart->TotalHeight/iPageHeight+1;
//   return PY;
//}
//
//--------------------------------------------------------------------------------
//  TLogicalChartPrint
//--------------------------------------------------------------------------------
TLogicalChartPrint::TLogicalChartPrint(TLogicalChart* AChart)
{
   FChart = AChart;
}
String __fastcall TLogicalChartPrint::GetName()
{
   return "Logical";
}
HENHMETAFILE __fastcall TLogicalChartPrint:: MakeMetalFile( int PageNo)
{
   if(FChart)
   {
      int PX=XLength();
      int PY=YLength();
      int X = PageNo % PX;
      int Y = PageNo / PX;

      HDC tempdc = GetDC(0);
      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);

      RECT rect;
      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
      ReleaseDC(0, tempdc);
      //画图
//      rect.left=0;
//      rect.top=0;
//      rect.right=FChart->Width;
//      rect.bottom=FChart->Height;
      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
      SetBkMode(pvMetaFileDc, TRANSPARENT);
      FChart->Draw(pvMetaFileDc);
      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
      //清边
      HBRUSH Brush = CreateSolidBrush(clWhite);
      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
      RECT r;
      //上边
      r.left = X*iPageWidth;
      r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = r.top+iTopPageMargin-5;
      FillRect(pvMetaFileDc, &r, Brush);
      //下边
      r.left =X*iPageWidth;
      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
      r.right=r.left+iFullPageWidth;
      r.bottom=r.top+iBottomPageMargin+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //左边
      r.left = X*iPageWidth;
      r.top =  Y*iPageHeight;
      r.right=r.left+iLeftPageMargin-5;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //右边
      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
      r.top=Y*iPageHeight;
      r.right=r.left+iRightPageMargin;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);

      SelectObject(pvMetaFileDc, oldBrush);
      DeleteObject(Brush);
      //标题
      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
      SetTextColor(pvMetaFileDc, FTitleFont->Color);
      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = iTopPageMargin+r.top-20;
	  DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
      SelectObject(pvMetaFileDc, oldFont);
      DeleteObject(hTitleFont);

      if(FShowPageNo)//页号
      {
          String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
          HFONT hFont = CreateFontByTFont(FChart->Font);
          SetTextColor(pvMetaFileDc, FChart->Font->Color);
          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
          r.left = X*iPageWidth;
          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
          r.right =iFullPageWidth+r.left;
          r.bottom =r.top+iBottomPageMargin;
		  DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
          SelectObject(pvMetaFileDc, oldFont);
          DeleteObject(hFont);

      }
      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
      return pvMetaFile;
     }
     return NULL;
}
int __fastcall TLogicalChartPrint::GetPageCount()
{
   return XLength() * YLength();
}
int TLogicalChartPrint::XLength()
{
   int PX = FChart->Width/iPageWidth+1;
   return PX ;
}
int TLogicalChartPrint::YLength()
{
   int PY = FChart->Height/iPageHeight+1;
   return PY;
}

//--------------------------------------------------------------------------------
//  TDoubleCodePrint
//--------------------------------------------------------------------------------
TDoubleCodePrint::TDoubleCodePrint(TDoubleCode* AChart)
{
   FChart = AChart;
}
String __fastcall TDoubleCodePrint::GetName()
{
   return "NetChart";
}
HENHMETAFILE __fastcall TDoubleCodePrint:: MakeMetalFile( int PageNo)
{
   if(FChart)
   {
      int PX=XLength();
      int PY=YLength();
      int X = PageNo % PX;
      int Y = PageNo / PX;

      HDC tempdc = GetDC(0);
      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);

      RECT rect;
      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
      ReleaseDC(0, tempdc);
      //画图
      rect.left=0;
      rect.top=0;
      rect.right=FChart->TotalWidth;
      rect.bottom=FChart->TotalHeight;
      SetBkMode(pvMetaFileDc, TRANSPARENT);
      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
      FChart->Draw(pvMetaFileDc, rect);
      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
      //清边
      HBRUSH Brush = CreateSolidBrush(clWhite);
      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
      RECT r;
      //上边
      r.left = X*iPageWidth;
      r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = r.top+iTopPageMargin-5;
      FillRect(pvMetaFileDc, &r, Brush);
      //下边
      r.left =X*iPageWidth;
      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
      r.right=r.left+iFullPageWidth;
      r.bottom=r.top+iBottomPageMargin+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //左边
      r.left = X*iPageWidth;
      r.top =  Y*iPageHeight;
      r.right=r.left+iLeftPageMargin-5;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //右边
      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
      r.top=Y*iPageHeight;
      r.right=r.left+iRightPageMargin;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);

      SelectObject(pvMetaFileDc, oldBrush);
      DeleteObject(Brush);
      //标题
      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
      SetTextColor(pvMetaFileDc, FTitleFont->Color);
      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = iTopPageMargin+r.top-20;
	  DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
      SelectObject(pvMetaFileDc, oldFont);
      DeleteObject(hTitleFont);

      if(FShowPageNo)//页号
      {
          String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
          HFONT hFont = CreateFontByTFont(FChart->Font);
          SetTextColor(pvMetaFileDc, FChart->Font->Color);
          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
          r.left = X*iPageWidth;
          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
          r.right =iFullPageWidth+r.left;
          r.bottom =r.top+iBottomPageMargin;
		  DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
          SelectObject(pvMetaFileDc, oldFont);
          DeleteObject(hFont);

      }
      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
      return pvMetaFile;
     }
     return NULL;
}
int __fastcall TDoubleCodePrint::GetPageCount()
{
   return XLength() * YLength();
}
int TDoubleCodePrint::XLength()
{
   int PX = FChart->TotalWidth/iPageWidth+1;
   return PX ;
}
int TDoubleCodePrint::YLength()
{
   int PY = FChart->TotalHeight/iPageHeight+1;
   return PY;
}


int TGanttSetPrint::XLength()
{
        return 1;
}

int TGanttSetPrint::YLength()
{
        return 1;
}
int __fastcall TGanttSetPrint::GetPageCount()
{
  return XLength()*YLength();
}
String __fastcall TGanttSetPrint::GetName()
{
     return "GanttSet";
}
TGanttSetPrint::TGanttSetPrint(TGanttSet ASet)
{
        AGanttSet=ASet;
}
HENHMETAFILE __fastcall TGanttSetPrint::MakeMetalFile( int PageNo)
{
      int PX=XLength();
      int PY=YLength();
      int X = PageNo % PX;
      int Y = PageNo / PX;

      HDC tempdc = GetDC(0);
      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);

      RECT rect;
      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
      ReleaseDC(0, tempdc);
      //画图
      SetBkMode(pvMetaFileDc, TRANSPARENT);
      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
      DrawGanttSet(pvMetaFileDc, rect);
      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
      //清边
      HBRUSH Brush = CreateSolidBrush(clWhite);
      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
      RECT r;
      //上边
      r.left = X*iPageWidth;
      r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = r.top+iTopPageMargin-5;
      FillRect(pvMetaFileDc, &r, Brush);
      //下边
      r.left =X*iPageWidth;
      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
      r.right=r.left+iFullPageWidth;
      r.bottom=r.top+iBottomPageMargin+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //左边
      r.left = X*iPageWidth;
      r.top =  Y*iPageHeight;
      r.right=r.left+iLeftPageMargin-5;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //右边
      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
      r.top=Y*iPageHeight;
      r.right=r.left+iRightPageMargin;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);

      SelectObject(pvMetaFileDc, oldBrush);
      DeleteObject(Brush);
      //标题
      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
      SetTextColor(pvMetaFileDc, FTitleFont->Color);
      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = iTopPageMargin+r.top-20;
	  DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
	  SelectObject(pvMetaFileDc, oldFont);
      DeleteObject(hTitleFont);
      if(FShowPageNo)//页号
      {
          String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
          HFONT hFont = CreateFontByTFont(Screen->IconFont);
          SetTextColor(pvMetaFileDc, Screen->IconFont->Color);
          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
          r.left = X*iPageWidth;
          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
          r.right =iFullPageWidth+r.left;
          r.bottom =r.top+iBottomPageMargin;
		  DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
		  SelectObject(pvMetaFileDc, oldFont);
          DeleteObject(hFont);

      }
      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
      return pvMetaFile;
}
void TGanttSetPrint::DrawRect(HDC DC,RECT rect,int iPattern,TColor pcolor)
{
    HBITMAP Bitmap;
    HBRUSH Brush;
    HGDIOBJ oldBrush;
    SetTextColor(DC, pcolor);
    Bitmap = TPattern::Pattern(iPattern);
    Brush = CreatePatternBrush(Bitmap);
    oldBrush = SelectObject(DC, Brush);
    HPEN Pen;
    HGDIOBJ oldPen;
    Pen = CreatePen(PS_SOLID, 1, pcolor);
    oldPen = SelectObject(DC, Pen);
    Rectangle(DC,rect.left,rect.top+2,rect.right,rect.bottom-2);
    SelectObject(DC, oldBrush);
    DeleteObject(Brush);
    SelectObject(DC, oldPen);
    DeleteObject(Pen);
}
void TGanttSetPrint::DrawSetText(HDC DC,RECT rect,String text,TFont *textFont,TColor pcolor)
{
    HFONT hFont = CreateFontByTFont(textFont);
    SetTextColor(DC, pcolor);
    HGDIOBJ oldFont = SelectObject(DC, hFont);
	DrawText(DC, text.c_str(), text.Length(), &rect, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
    SelectObject(DC, oldFont);
    DeleteObject(hFont);
}
void TGanttSetPrint::DrawGanttSet(HDC DC,RECT rect)
{
  TFont *SubTitleFont=new TFont();
  SubTitleFont->Size=12;
  SubTitleFont->Name="宋体";
  TFont *TextFont=new TFont();
  TextFont->Size=9;
  TextFont->Name="宋体";
  RECT tr,pr,cr;
  tr.left=rect.left;
  tr.top=rect.top;
  tr.right=tr.left+120;
  tr.bottom=tr.top+20;
  DrawSetText(DC,tr,"一般",SubTitleFont);
  //
  tr.top=tr.top+20;
  tr.bottom=tr.top+20;
  DrawSetText(DC,tr,"关系线颜色：",TextFont);
  pr.left=tr.right+4;
  pr.right=pr.left+100;
  pr.top=tr.top;
  pr.bottom=tr.bottom;
  DrawRect(DC,pr,0,AGanttSet.LineColor);
  //
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"关键线颜色：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.CriticalLineColor);
  //
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"日历底色：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.CalendarBkColor);
  //
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"日历颜色：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.CaldndarFontColor);
 ////
  tr.top+=30;
  tr.bottom+=30;
  pr.top+=30;
  pr.bottom+=30;
  cr.top+=30;
  cr.bottom+=30;
  DrawSetText(DC,tr,"项目任务",SubTitleFont);
  //
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"计划：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.NotStartDraw.Bar1.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;
  DrawRect(DC,cr,AGanttSet.NotStartDraw.Bar1.Pattern,AGanttSet.NotStartDraw.Bar1.Color);
  //
  int offsetlength=cr.right-tr.left+4;
  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);

  DrawSetText(DC,tr,"关键任务计划：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.CriticalNotStartDraw.Bar1.Color);
  DrawRect(DC,cr,AGanttSet.CriticalNotStartDraw.Bar1.Pattern,AGanttSet.CriticalNotStartDraw.Bar1.Color);

  OffsetRect(&tr,-(offsetlength),0);
  OffsetRect(&pr,-(offsetlength),0);
  OffsetRect(&cr,-(offsetlength),0);
  ///
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"实际已开工：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.StartedDraw.Bar2.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;
  DrawRect(DC,cr,AGanttSet.StartedDraw.Bar2.Pattern,AGanttSet.StartedDraw.Bar2.Color);
  //
  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);

  DrawSetText(DC,tr,"实际已完工：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.OveredDraw.Bar2.Color);
  DrawRect(DC,cr,AGanttSet.OveredDraw.Bar2.Pattern,AGanttSet.OveredDraw.Bar2.Color);

  OffsetRect(&tr,-(offsetlength),0);
  OffsetRect(&pr,-(offsetlength),0);
  OffsetRect(&cr,-(offsetlength),0);
  ///
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"里程碑：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.MarkerDraw.Bar1.HeadDraw.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;
  //
  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);

  DrawSetText(DC,tr,"任务分组：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.AbstractDraw.Bar1.Color);
  DrawRect(DC,cr,AGanttSet.AbstractDraw.Bar1.Pattern,AGanttSet.AbstractDraw.Bar1.Color);

  OffsetRect(&tr,-(offsetlength),0);
  OffsetRect(&pr,-(offsetlength),0);
  OffsetRect(&cr,-(offsetlength),0);
///
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"外部工程：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.ForeignProjectDraw.Bar1.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;
  DrawRect(DC,cr,AGanttSet.ForeignProjectDraw.Bar1.Pattern,AGanttSet.ForeignProjectDraw.Bar1.Color);
  //
  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);

  DrawSetText(DC,tr,"工程量不足：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.WarningDraw.Bar2.Color);
  DrawRect(DC,cr,AGanttSet.WarningDraw.Bar2.Pattern,AGanttSet.WarningDraw.Bar2.Color);

  OffsetRect(&tr,-(offsetlength),0);
  OffsetRect(&pr,-(offsetlength),0);
  OffsetRect(&cr,-(offsetlength),0);
  ////
  tr.top+=30;
  tr.bottom+=30;
  pr.top+=30;
  pr.bottom+=30;
  cr.top+=30;
  cr.bottom+=30;
  DrawSetText(DC,tr,"外部工程任务",SubTitleFont);
  //
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"计划：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.ForeignNotStartDraw.Bar1.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;
  DrawRect(DC,cr,AGanttSet.ForeignNotStartDraw.Bar1.Pattern,AGanttSet.ForeignNotStartDraw.Bar1.Color);
  //

  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);

  DrawSetText(DC,tr,"关键任务计划：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.CriticalForeignNotStartDraw.Bar1.Color);
  DrawRect(DC,cr,AGanttSet.CriticalForeignNotStartDraw.Bar1.Pattern,AGanttSet.CriticalForeignNotStartDraw.Bar1.Color);

  OffsetRect(&tr,-(offsetlength),0);
  OffsetRect(&pr,-(offsetlength),0);
  OffsetRect(&cr,-(offsetlength),0);
  ///
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"实际已开工：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.ForeignStartedDraw.Bar2.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;
  DrawRect(DC,cr,AGanttSet.ForeignStartedDraw.Bar2.Pattern,AGanttSet.ForeignStartedDraw.Bar2.Color);
  //
  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);

  DrawSetText(DC,tr,"实际已完工：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.ForeignOveredDraw.Bar2.Color);
  DrawRect(DC,cr,AGanttSet.ForeignOveredDraw.Bar2.Pattern,AGanttSet.ForeignOveredDraw.Bar2.Color);

  OffsetRect(&tr,-(offsetlength),0);
  OffsetRect(&pr,-(offsetlength),0);
  OffsetRect(&cr,-(offsetlength),0);
  ///
  tr.top+=20;
  tr.bottom+=20;
  DrawSetText(DC,tr,"里程碑：",TextFont);
  pr.top+=20;
  pr.bottom+=20;
  DrawRect(DC,pr,0,AGanttSet.ForeignMarkerDraw.Bar1.HeadDraw.Color);
  cr=pr;
  cr.left=pr.right+4;
  cr.right=cr.left+100;

  OffsetRect(&tr,offsetlength,0);
  OffsetRect(&pr,offsetlength,0);
  OffsetRect(&cr,offsetlength,0);


  DrawSetText(DC,tr,"任务分组：",TextFont);
  DrawRect(DC,pr,0,AGanttSet.ForeignAbstractDraw.Bar1.Color);
  DrawRect(DC,cr,AGanttSet.ForeignAbstractDraw.Bar1.Pattern,AGanttSet.ForeignAbstractDraw.Bar1.Color);

delete SubTitleFont;
delete TextFont;

}
void TNetChartSetPrint::DrawSetText(HDC DC,RECT rect,String text,TFont *textFont,TColor pcolor)
{
    HFONT hFont = CreateFontByTFont(textFont);
    SetTextColor(DC, pcolor);
    HGDIOBJ oldFont = SelectObject(DC, hFont);
	DrawText(DC, text.c_str(), text.Length(), &rect, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
    SelectObject(DC, oldFont);
    DeleteObject(hFont);

}
void TNetChartSetPrint::DrawBGColorRect(HDC DC,TFrameDraw *FrameDraw,RECT rect)
{
          HBRUSH Brush;
          HGDIOBJ oldBrush;
          SetTextColor(DC, FrameDraw->BkColor);
          Brush = CreateSolidBrush(FrameDraw->BkColor);
          oldBrush = SelectObject(DC, Brush);

          Rectangle(DC, rect.left+2, rect.top+2, rect.right-2, rect.bottom-2);

          SelectObject(DC, oldBrush);
          DeleteObject(Brush);
          SetTextColor(DC, clBlack);

}
void TNetChartSetPrint::DrawBordStyleRect(HDC DC,TFrameDraw *FrameDraw,RECT rect)
{
          HBRUSH Brush;
          HGDIOBJ oldBrush;
          SetTextColor(DC, clBlack);
          Brush = CreateSolidBrush(clWhite);
          oldBrush = SelectObject(DC, Brush);
          POINT p[7];
          int pCount;
          int Left = rect.left + 3;
          int Top = rect.top + 3;
          int Right = rect.right - 3;
          int Bottom = rect.bottom - 3;
          int Margin = 8;
          switch(FrameDraw->BorderType)
          {
              case TFrameDraw::btRectangle: //矩形
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
              case TFrameDraw::btParallelogram1://平行四边形
                   p[0].x = Left + Margin - 3;
                   p[0].y = Top;
                   p[1].x = Right;
                   p[1].y = Top;
                   p[2].x = Right - Margin + 3;
                   p[2].y = Bottom;
                   p[3].x = Left;
                   p[3].y = Bottom;
                   p[4] = p[0];
                   pCount = 5;
                   break;
              case TFrameDraw::btParallelogram2://平行四边形
                   p[0].x = Left;
                   p[0].y = Top;
                   p[1].x = Right - Margin + 3;
                   p[1].y = Top;
                   p[2].x = Right;
                   p[2].y = Bottom;
                   p[3].x = Left + Margin - 3;
                   p[3].y = Bottom;
                   p[4] = p[0];
                   pCount = 5;
                   break;
              case TFrameDraw::btDiamond:        //菱形
                   p[0].x = Left + Margin - 3;
                   p[0].y = Top;
                   p[1].x = Right - Margin + 3;
                   p[1].y = Top;
                   p[2].x = Right;
                   p[2].y = (Top + Bottom) / 2;
                   p[3].x = Right - Margin + 3;
                   p[3].y = Bottom;
                   p[4].x = Left + Margin - 3;
                   p[4].y = Bottom;
                   p[5].x = Left;
                   p[5].y = (Top + Bottom) / 2;
                   p[6] = p[0];
                   pCount = 7;
                   break;
              default:
                   ;
          }
          Polygon(DC, p, pCount);
          SelectObject(DC, oldBrush);
          DeleteObject(Brush);
          SetTextColor(DC, clBlack);

}
void TNetChartSetPrint::DrawPatternRect(HDC DC,TFrameDraw *FrameDraw,RECT rect)
{
          HBRUSH Brush;
          HGDIOBJ oldBrush;
          SetTextColor(DC, FrameDraw->BkColor);
		  Brush = CreatePatternBrush(TPattern::Pattern(FrameDraw->BkPattern));
          oldBrush = SelectObject(DC, Brush);

          Rectangle(DC, rect.left+2, rect.top+2, rect.right-2, rect.bottom-2);

          SelectObject(DC, oldBrush);
          DeleteObject(Brush);
          SetTextColor(DC, clBlack);

}
void TNetChartSetPrint::DrawLineColorRect(HDC DC,TFrameDraw *FrameDraw,RECT rect)
{
          HBRUSH Brush;
          HGDIOBJ oldBrush;
          SetTextColor(DC, FrameDraw->BkColor);
          Brush = CreateSolidBrush(FrameDraw->LineColor);
          oldBrush = SelectObject(DC, Brush);

          Rectangle(DC, rect.left+2, rect.top+2, rect.right-2, rect.bottom-2);

          SelectObject(DC, oldBrush);
          DeleteObject(Brush);
          SetTextColor(DC, clBlack);

}
void TNetChartSetPrint::DrawSignRect(HDC DC,TFrameDraw *FrameDraw,RECT rect)
{
//          HPEN Pen;
//          HGDIOBJ oldPen;
//          Pen = CreatePen(PS_SOLID, 1, clBlack);
//          oldPen = SelectObject(DC, Pen);
          MoveToEx(DC,rect.left+2, rect.top+2,NULL);
          LineTo(DC,rect.right-2, rect.top+2);
          LineTo(DC,rect.right-2, rect.bottom-2);
          LineTo(DC,rect.left+2, rect.bottom-2);
          LineTo(DC,rect.left+2, rect.top+2);
          if(FrameDraw->Sign > 0)
          {
              MoveToEx(DC,rect.left + 2, rect.bottom-2,NULL);
              LineTo(DC,rect.right - 2, rect.top+2);
              if(FrameDraw->Sign == 2)
              {
                  MoveToEx(DC,rect.left + 2, rect.top+2,NULL);
                  LineTo(DC,rect.right - 2, rect.bottom-2);
              }
          }
}
void TNetChartSetPrint::DrawNetSetRow(HDC DC,TFrameDraw *FrameDraw,RECT rect,String text,TFont *textFont)
{
      RECT rect1,rect2,rect3,rect4,rect5,rect6;
      int iwidth=(rect.right-rect.left-150)/5;
      rect1.top=rect.top;
      rect1.bottom=rect.bottom;
      rect1.left=rect.left;
      rect1.right=150;
      DrawSetText(DC,rect1,text,textFont);
      rect2.top=rect.top;
      rect2.bottom=rect.bottom;
      rect2.left=rect1.right;
      rect2.right=rect2.left+iwidth;
      DrawBGColorRect(DC,FrameDraw,rect2);

      rect3.top=rect.top;
      rect3.bottom=rect.bottom;
      rect3.left=rect2.right;
      rect3.right=rect3.left+iwidth;
      DrawBordStyleRect(DC,FrameDraw,rect3);
      rect4.top=rect.top;
      rect4.bottom=rect.bottom;
      rect4.left=rect3.right;
      rect4.right=rect4.left+iwidth;
      DrawPatternRect(DC,FrameDraw,rect4);
      rect5.top=rect.top;
      rect5.bottom=rect.bottom;
      rect5.left=rect4.right;
      rect5.right=rect5.left+iwidth;
      DrawLineColorRect(DC,FrameDraw,rect5);
      rect6.top=rect.top;
      rect6.bottom=rect.bottom;
      rect6.left=rect5.right;
      rect6.right=rect6.left+iwidth;
      DrawSignRect(DC,FrameDraw,rect6);
}
void TNetChartSetPrint::DrawGridTitle(HDC DC,RECT rect,TFont *textFont)
{
      RECT rect1,rect2,rect3,rect4,rect5,rect6;
      int iwidth=(rect.right-rect.left-150)/5;
      String text;

      text= "任务类型";
      rect1.top=rect.top;
      rect1.bottom=rect.bottom;
      rect1.left=rect.left;
      rect1.right=150;
      DrawSetText(DC,rect1,text,textFont);

   text= "底色";
      rect2.top=rect.top;
      rect2.bottom=rect.bottom;
      rect2.left=rect1.right;
      rect2.right=rect2.left+iwidth;
      DrawSetText(DC,rect2,text,textFont);

   text= "边框类型";
      rect3.top=rect.top;
      rect3.bottom=rect.bottom;
      rect3.left=rect2.right;
      rect3.right=rect3.left+iwidth;
      DrawSetText(DC,rect3,text,textFont);

   text= "底纹";
      rect4.top=rect.top;
      rect4.bottom=rect.bottom;
      rect4.left=rect3.right;
      rect4.right=rect4.left+iwidth;
      DrawSetText(DC,rect4,text,textFont);

   text= "直线颜色";
      rect5.top=rect.top;
      rect5.bottom=rect.bottom;
      rect5.left=rect4.right;
      rect5.right=rect5.left+iwidth;
      DrawSetText(DC,rect5,text,textFont);

   text= "标记";
      rect6.top=rect.top;
      rect6.bottom=rect.bottom;
      rect6.left=rect5.right;
      rect6.right=rect6.left+iwidth;
      DrawSetText(DC,rect6,text,textFont);
}
void TNetChartSetPrint::DrawNetSet(HDC DC,RECT rect)
{
   TFrameDraw* FrameDraw;
   int iheight=(rect.bottom-rect.top)/19;
   TFont *textFont=new TFont();
   textFont->Name="宋体";
   textFont->Size=9;
   String text="";
   RECT curRect;

   curRect.top=rect.top;
   curRect.left=rect.left;
   curRect.right=rect.right;
   curRect.bottom=curRect.top+iheight;
   DrawGridTitle(DC,curRect,textFont);

   text= "关键未开工";
   FrameDraw = FNetChart->CriticalNotStartDraw();
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);


   text= "关键已开工";
   FrameDraw = FNetChart->CriticalStartedDraw();
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "关键已完工";
   FrameDraw = FNetChart->CriticalOveredDraw();
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "未开工";
   FrameDraw = FNetChart->NotStartDraw();
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "已开工";
   FrameDraw = FNetChart->StartedDraw();
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "已完工";
   FrameDraw = FNetChart->OveredDraw();
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "摘要任务";
   FrameDraw = FNetChart->AbstractDraw();//摘要任务
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "里程碑";
   FrameDraw = FNetChart->MarkerDraw();//里程碑
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text= "工程量完成不足";
   FrameDraw = FNetChart->WarningDraw();//有问题任务
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部未开工";
   FrameDraw = FNetChart->ForeignNotStartDraw();//外部未开工
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部未开工";
   FrameDraw = FNetChart->CriticalForeignNotStartDraw();//外部未开工
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部已开工";
   FrameDraw = FNetChart->ForeignStartedDraw();//外部已开工
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部关键任务已开工";
   FrameDraw = FNetChart->CriticalForeignStartedDraw();//外部已开工
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部已完工";
   FrameDraw = FNetChart->ForeignOveredDraw();//外部已完工
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部关键任务已完工";
   FrameDraw = FNetChart->CriticalForeignOveredDraw();//外部已完工
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部摘要任务";
   FrameDraw = FNetChart->ForeignAbstractDraw();//外部摘要任务
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部里程碑";
   FrameDraw = FNetChart->ForeignMarkerDraw();//外部里程碑
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);

   text = "外部工程";
   FrameDraw = FNetChart->ForeignProjectDraw();//外部工程
   OffsetRect(&curRect,0,iheight);
   DrawNetSetRow(DC,FrameDraw, curRect,text,textFont);
   delete textFont;
}

HENHMETAFILE __fastcall TNetChartSetPrint::MakeMetalFile( int PageNo)
{
      int PX=XLength();
      int PY=YLength();
      int X = PageNo % PX;
      int Y = PageNo / PX;

      HDC tempdc = GetDC(0);
      int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
      int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
      int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
      int iHeightPels = GetDeviceCaps(tempdc, VERTRES);

      RECT rect;
      rect.left = X*iPageWidth*iWidthMM*100/iWidthPels;
      rect.top = Y*iPageHeight*iHeightMM*100/iHeightPels;//创建矢量图
      rect.right=iFullPageWidth*iWidthMM*100/iWidthPels+rect.left;
      rect.bottom=iFullPageHeight*iHeightMM*100/iHeightPels+rect.top;
      HDC pvMetaFileDc = CreateEnhMetaFile(tempdc, NULL, &rect, NULL);
      ReleaseDC(0, tempdc);
      //画图
      SetBkMode(pvMetaFileDc, TRANSPARENT);
      SetViewportOrgEx(pvMetaFileDc,iLeftPageMargin,iTopPageMargin,NULL);
      RECT myrect;
      myrect.left = X*iPageWidth;
      myrect.top = Y*iPageHeight;//创建矢量图
      myrect.right=iPageWidth+myrect.left;
      myrect.bottom=iPageHeight+myrect.top;

      DrawNetSet(pvMetaFileDc, myrect);
      SetViewportOrgEx(pvMetaFileDc,0,0,NULL);
      //清边
      HBRUSH Brush = CreateSolidBrush(clWhite);
      HGDIOBJ oldBrush = SelectObject(pvMetaFileDc, Brush);
      RECT r;
      //上边
      r.left = X*iPageWidth;
      r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = r.top+iTopPageMargin-5;
      FillRect(pvMetaFileDc, &r, Brush);
      //下边
      r.left =X*iPageWidth;
      r.top=Y*iPageHeight+iFullPageHeight-iBottomPageMargin+5;
      r.right=r.left+iFullPageWidth;
      r.bottom=r.top+iBottomPageMargin+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //左边
      r.left = X*iPageWidth;
      r.top =  Y*iPageHeight;
      r.right=r.left+iLeftPageMargin-5;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);
      //右边
      r.left=X*iPageWidth+iPageWidth+iLeftPageMargin+5;
      r.top=Y*iPageHeight;
      r.right=r.left+iRightPageMargin;
      r.bottom=r.top+iFullPageHeight+100;
      FillRect(pvMetaFileDc, &r, Brush);

      SelectObject(pvMetaFileDc, oldBrush);
      DeleteObject(Brush);
      //标题
      HFONT hTitleFont = CreateFontByTFont(FTitleFont);
      HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hTitleFont);
      SetTextColor(pvMetaFileDc, FTitleFont->Color);
      r.left = X*iPageWidth; r.top = Y*iPageHeight;//上边
      r.right = iFullPageWidth+r.left;
      r.bottom = iTopPageMargin+r.top-20;
	  DrawText(pvMetaFileDc, FTitle.c_str(), FTitle.Length(), &r, DT_BOTTOM|DT_SINGLELINE|DT_CENTER);
      SelectObject(pvMetaFileDc, oldFont);
      DeleteObject(hTitleFont);
      if(FShowPageNo)//页号
      {
		  String str = "第" + IntToStr(PageNo+1) + "页 / 共" + IntToStr(PageCount) + "页";
		  HFONT hFont = CreateFontByTFont(Screen->IconFont);
          SetTextColor(pvMetaFileDc, Screen->IconFont->Color);
          HGDIOBJ oldFont = SelectObject(pvMetaFileDc, hFont);
          r.left = X*iPageWidth;
          r.top = Y*iPageHeight+iFullPageHeight-iBottomPageMargin+10;
          r.right =iFullPageWidth+r.left;
          r.bottom =r.top+iBottomPageMargin;
		  DrawText(pvMetaFileDc, str.c_str(), str.Length(), &r, DT_TOP|DT_SINGLELINE|DT_CENTER);
          SelectObject(pvMetaFileDc, oldFont);
          DeleteObject(hFont);

      }
      HENHMETAFILE pvMetaFile = CloseEnhMetaFile(pvMetaFileDc);
      return pvMetaFile;
}


TNetChartSetPrint::TNetChartSetPrint(TNetChart * Chart)
{
       FNetChart=Chart;
}
