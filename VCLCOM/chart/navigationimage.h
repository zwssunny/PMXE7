//---------------------------------------------------------------------------

#ifndef NavigationImageH
#define NavigationImageH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "ZChartDraw.h"
//---------------------------------------------------------------------------
const int BorderWidth = 10;
typedef void __fastcall (__closure *TFrameMove)(int X, int Y);
class PACKAGE TNavigationImage : public TWinControl
{
private:
    bool bMouseDowning;           //用于拖动
    TPoint ScreenPoint,OldScrPoint;//用于拖动
    RECT FFrameRect,OldFrameRect;  //描述框架的大小位置
    TFrameMove FOnFrameMove;
	RECT CtrlRect,DrawRect,SrcRect,ChartRect;//画图大小,画的Rect,图原大小Rect,图显示的Rect
	SIZE ChartPosition;//图的滚动位置
    HENHMETAFILE MetaFile;//矢量图

    TWinControl *wcChart;

    double FZoomX;  //缩放的倍数.
    double FZoomY;  //缩放的倍数.
//    Graphics::TBitmap* FSourceBmp;
    bool FShowing;
    TTimer *trResize;

    void __fastcall ResizeOnTimer(TObject* Sender);
    void __fastcall CalFrameMove();
    void __fastcall SetZoomParameter();
    void __fastcall SetShowing(bool bShow);
    void __fastcall PaintWindow(HDC DC);
    virtual void __fastcall EraseBKGND(TMessage& Msg);
    MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
protected:
    bool __fastcall PointInFrameRect(int X, int Y);
    void __fastcall DrawFrame(HDC dc);

    DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall Resize(void);
    DYNAMIC void __fastcall DblClick(void);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
        VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TMessage, EraseBKGND)
    END_MESSAGE_MAP(TWinControl)
public:
    __property bool Showing = {read=FShowing,write=SetShowing};//是否在显示
    __property double ZoomX = {read=FZoomX,write=FZoomX};  //缩放的倍数.
    __property double ZoomY = {read=FZoomY,write=FZoomY};  //缩放的倍数.
    __property  TFrameMove OnFrameMove = {read=FOnFrameMove, write=FOnFrameMove};//框架移动事件
    template <class SDChart>
	void __fastcall ShowNavigationPicture(SDChart *AChart)//显示图像
	{

	  wcChart = (TWinControl *)AChart;
	  if(MetaFile)
	  {
		//删除矢量图
		DeleteEnhMetaFile(MetaFile);
		MetaFile = NULL;
	  }
	  String FileName = "NaviImage.wmf";
	  SrcRect.left = 0;
	  SrcRect.top = 0;
	  HDC tempdc = GetDC(0);
	  int iWidthMM = GetDeviceCaps(tempdc, HORZSIZE);
	  int iHeightMM = GetDeviceCaps(tempdc, VERTSIZE);
	  int iWidthPels = GetDeviceCaps(tempdc, HORZRES);
	  int iHeightPels = GetDeviceCaps(tempdc, VERTRES);
	  SrcRect.right = double(AChart->TotalWidth * iWidthMM * 100) / double(iWidthPels);
	  SrcRect.bottom = double(AChart->TotalHeight * iHeightMM * 100) / double(iHeightPels);
	  if(SrcRect.right<=SrcRect.left || SrcRect.bottom<=SrcRect.top)
	  {
		MetaFile = NULL;
	   //	this->Repaint();
	   Invalidate();
		return;
	  }
	  //创建矢量图
	  HDC MetaFileDc = CreateEnhMetaFile(tempdc, FileName.c_str(), &SrcRect, L"CPM-网络图");
	  ReleaseDC(0, tempdc);
	  if(MetaFileDc!=NULL)
	  {
		SrcRect.right = AChart->TotalWidth;
		SrcRect.bottom = AChart->TotalHeight;
		TPrjObject* bkSelected = AChart->Project->Selected;
		AChart->Project->Selected = NULL;

		//HBRUSH Brush = CreateSolidBrush(clWhite);
		//FillRect(MetaFileDc,&SrcRect,Brush);
        //DeleteObject(Brush);

		AChart->Draw(MetaFileDc, SrcRect);
		AChart->Project->Selected = bkSelected;
        //关闭矢量图
		MetaFile = CloseEnhMetaFile(MetaFileDc);
      }

	  SetZoomParameter();

	  //this->Repaint();
	  Invalidate();
	}
//------------------------------------------------------------------------------
//    template <class SDChart>
//    void __fastcall ShowNavigationImage(SDChart *AChar)//显示图像
//    {
//  //      if(FSourceBmp)
//  //        FSourceBmp->FreeImage();
//  //      delete FSourceBmp;
//  //      FSourceBmp = new Graphics::TBitmap();
//      HDC dc = GetDC(this->Handle);
//      FSourceBmp->Width = Width;
//      FSourceBmp->Height = Height;
//      RECT r;
//      r.left = 0;
//      r.right = Width;
//      r.top = 0;
//      r.bottom = Height;
//      TCanvas *cv = new TCanvas();
//      cv->Handle = dc;
//      cv->FillRect(r);
//  //      AChar->DrawNavigation(FSourceBmp->Canvas->Handle,r);
//      AChar->DrawNavigation(dc,r);
//      FSourceBmp->Canvas->CopyRect(r,cv,r);
//      ReleaseDC(this->Handle,dc);
//      delete cv;
//    }

    void __fastcall SetFrameRect(TRect R,int x,int y);
    void __fastcall SetFrameRect(int x,int y);

    __fastcall TNavigationImage(TComponent* Owner);
    __fastcall ~TNavigationImage();
};
//---------------------------------------------------------------------------
#endif
