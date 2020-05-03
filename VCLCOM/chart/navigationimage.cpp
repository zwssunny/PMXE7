//---------------------------------------------------------------------------
#pragma hdrstop

#include "NavigationImage.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//TNavigationImage
//---------------------------------------------------------------------------
__fastcall TNavigationImage::TNavigationImage(TComponent* Owner)
  : TWinControl(Owner)
{
  trResize = new TTimer(this);
  trResize->Enabled = false;
  trResize->Interval = 37;
  trResize->Tag = 0 ;
  trResize->OnTimer = ResizeOnTimer;
  this->Color = clWhite;
//  FSourceBmp = new Graphics::TBitmap();
  FShowing = false;
  this->Visible = false;
  Parent = (TWinControl*)Owner;
  CtrlRect=TRect(0,0,0,0);
  DrawRect=CtrlRect;
  SrcRect=CtrlRect;
  ChartRect=CtrlRect; 
 /*   CtrlRect = this->ClientRect;
  DrawRect = this->ClientRect;
  SrcRect = this->ClientRect;
  ChartRect = this->ClientRect;   */
  FZoomX = 1;
  FZoomY = 1;
//  FFrameRect.left = 0;
//  FFrameRect.top = 0;
//  FFrameRect.right = 100;
//  FFrameRect.bottom= 50;
//  OldFrameRect = FFrameRect;
}
//---------------------------------------------------------------------------
__fastcall TNavigationImage::~TNavigationImage()
{
//  if(FSourceBmp)
//    FSourceBmp->FreeImage();
//  delete FSourceBmp;
  if(MetaFile)
    DeleteEnhMetaFile(MetaFile);
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::EraseBKGND(TMessage& Msg)
{
    Msg.Result=1;
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::WMPaint(Messages::TWMPaint &Message)
{
    ControlState << csCustomPaint;
    TWinControl::Dispatch(&Message);
    ControlState >> csCustomPaint;
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::PaintWindow(HDC DC)
{
//  TCanvas *canv = new TCanvas();
//  canv->Handle = DC;
//
//  canv->FillRect(this->ClientRect);
//
//  if(FSourceBmp)
//    canv->Draw(0,0,(TGraphic *)FSourceBmp);
//
//  delete canv;

//  BitBlt(DC,0,0,Width,Height,FSourceBmp->Canvas->Handle,0,0,WHITENESS+SRCCOPY);//¸üÂý
//  return;
  if(trResize->Tag==1)  return;
  HBRUSH Brush = CreateSolidBrush(clWhite);
  FillRect(DC,&CtrlRect,Brush);
  DeleteObject(Brush);
  if(MetaFile)
  {
    PlayEnhMetaFile(DC, MetaFile, &DrawRect);
  }

  DrawFrame(DC);
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::SetZoomParameter()
{
  if(wcChart)
    ChartRect = wcChart->ClientRect;
  CtrlRect.left = 0;
  CtrlRect.top = 0;
  CtrlRect.right = Width;
  CtrlRect.bottom = Height;

  DrawRect = CtrlRect;
  double drWidth = DrawRect.right ;
  double drHeight = DrawRect.bottom;
  if(SrcRect.right>drWidth || SrcRect.bottom>drHeight)
  {
    FZoomX = SrcRect.right/drWidth;
    FZoomY = SrcRect.bottom/drHeight;
	if(FZoomX<FZoomY)
      FZoomX = FZoomY;
    else
      FZoomY = FZoomX;

    DrawRect.right  = (int)(SrcRect.right/FZoomX)  + DrawRect.left;
    DrawRect.bottom = (int)(SrcRect.bottom/FZoomX) + DrawRect.top;
  }
//  else
//  {
//    FZoomY = 1;
//    FZoomX = 1;
//    DrawRect.right  = SrcRect.right;
//    DrawRect.bottom = SrcRect.bottom;
//  }
  if (FZoomY==0) FZoomY = 1;
  if (FZoomX==0) FZoomX = 1;
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::DrawFrame(HDC dc)
{
  if(!this->Parent)return;
  if(MetaFile == NULL)return;
  HDC tmdc = NULL;
  TCanvas *canv = new TCanvas();
  if(dc)
    canv->Handle = dc;
  else
  {
    tmdc = GetDC(this->Handle);
    canv->Handle = tmdc;
  }
  TPenMode Oldpm = canv->Pen->Mode;
  TBrushStyle Oldbs = canv->Brush->Style;
  canv->Brush->Style = bsClear;
  canv->Pen->Color = clYellow;//clBlue;
  canv->Pen->Mode =  pmXor;
  if(OldFrameRect.top!=FFrameRect.top || OldFrameRect.left!=FFrameRect.left
     || OldFrameRect.right!=FFrameRect.right || OldFrameRect.bottom!=FFrameRect.bottom)
  {
    canv->Rectangle(OldFrameRect);
    canv->Rectangle(TRect(OldFrameRect.left-1,OldFrameRect.top-1,
                OldFrameRect.right-1,OldFrameRect.bottom-1));
  }
//  canv->Pen->Mode = pmCopy;
  canv->Rectangle(FFrameRect);
  canv->Rectangle(TRect(FFrameRect.left-1,FFrameRect.top-1,
            FFrameRect.right-1,FFrameRect.bottom-1));
  canv->Pen->Mode = Oldpm;
  canv->Brush->Style = Oldbs;
  OldFrameRect = FFrameRect;
  if(tmdc) ReleaseDC(this->Handle,tmdc);
  delete canv;
}
//---------------------------------------------------------------------------
//void __fastcall TNavigationImage::ShowNavigationImage(SDChart *AChar);//ÏÔÊ¾Í¼Ïñ
//{
//  Refresh();
//}
//---------------------------------------------------------------------------
bool __fastcall TNavigationImage::PointInFrameRect(int X, int Y)
{
  return (Y>=FFrameRect.top && Y<=FFrameRect.bottom
            && X>=FFrameRect.left && X<=FFrameRect.right);
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::MouseDown(TMouseButton Button,
  Classes::TShiftState Shift, int X, int Y)
{
  if(PointInFrameRect(X,Y))
  {
    bMouseDowning = true;
    ScreenPoint.x = X;
    ScreenPoint.y = Y;
	ScreenPoint = ClientToScreen(ScreenPoint);
    OldScrPoint = ScreenPoint;
  }
}
//--------------------------------------------------------------------------
void __fastcall TNavigationImage::MouseMove(Classes::TShiftState Shift,
   int X, int Y)
{
  if(bMouseDowning)
  {
    ScreenPoint.x = X;
    ScreenPoint.y = Y;
    ScreenPoint = ClientToScreen(ScreenPoint);
    if(OldScrPoint.x!=ScreenPoint.x  ||  OldScrPoint.y!=ScreenPoint.y)
    {
      FFrameRect.left   = FFrameRect.left   - (OldScrPoint.x - ScreenPoint.x);
      FFrameRect.right  = FFrameRect.right  - (OldScrPoint.x - ScreenPoint.x);
      FFrameRect.top    = FFrameRect.top    - (OldScrPoint.y - ScreenPoint.y);
      FFrameRect.bottom = FFrameRect.bottom - (OldScrPoint.y - ScreenPoint.y);
      OldScrPoint = ScreenPoint;
      DrawFrame(NULL);
//      CalFrameMove();
    }
  }
}
//--------------------------------------------------------------------------
void __fastcall TNavigationImage::MouseUp(TMouseButton Button,
   Classes::TShiftState Shift, int X, int Y)
{
  if(bMouseDowning && FOnFrameMove)
  {
    int d = 0;
    if(FFrameRect.left<0)
    {
      d = - FFrameRect.left;
      FFrameRect.left   = FFrameRect.left   + d;
      FFrameRect.right  = FFrameRect.right  + d;
    }
    else if(FFrameRect.right>DrawRect.right)
    {
      d = FFrameRect.right - DrawRect.right;
      FFrameRect.left   = FFrameRect.left   - d;
      FFrameRect.right  = FFrameRect.right  - d;
    }
    if(FFrameRect.top<0)
    {
      d = -FFrameRect.top;
      FFrameRect.top    = FFrameRect.top    + d;
      FFrameRect.bottom = FFrameRect.bottom + d;
    }
    else if(FFrameRect.bottom>DrawRect.bottom)
    {
      d = FFrameRect.bottom - DrawRect.bottom;
      FFrameRect.top    = FFrameRect.top    - d;
      FFrameRect.bottom = FFrameRect.bottom - d;
    }
	if(d>0) DrawFrame(NULL);

    CalFrameMove();
  }
  bMouseDowning = false;
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::Resize(void)
{
  /*CtrlRect = this->ClientRect;
  DrawRect = this->ClientRect;
  SrcRect = this->ClientRect;
  ChartRect = this->ClientRect;  */
  SetZoomParameter();
  SetFrameRect(ChartPosition.cx , ChartPosition.cy);
  trResize->Enabled = false;
  trResize->Tag = 1 ;
  trResize->Enabled = true;
  //this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::DblClick(void)
{
    GetCursorPos(&ScreenPoint);
	TPoint ClientPoint = ScreenToClient(ScreenPoint);
    ScreenPoint.x = ScreenPoint.x- (FFrameRect.right-FFrameRect.left)/2;
    ScreenPoint.y = ScreenPoint.y- (FFrameRect.bottom-FFrameRect.top)/2;

    ClientPoint.x = ClientPoint.x- (FFrameRect.right-FFrameRect.left)/2;
    ClientPoint.y = ClientPoint.y- (FFrameRect.bottom-FFrameRect.top)/2;
    if(FFrameRect.left!=ClientPoint.x  ||  FFrameRect.top!=ClientPoint.y)
    {
      OldScrPoint = ScreenPoint;

      int d = 0;
      d = FFrameRect.left - ClientPoint.x;
      FFrameRect.left   = ClientPoint.x;
      FFrameRect.right  = FFrameRect.right - d;
      d = FFrameRect.top - ClientPoint.y;
      FFrameRect.top    = ClientPoint.y;
      FFrameRect.bottom = FFrameRect.bottom - d;
      DrawFrame(NULL);
      CalFrameMove();
    }
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::SetFrameRect(TRect R,int x,int y)
{
  ChartRect = R;
  SetFrameRect(x, y);
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::SetFrameRect(int x, int y)
{
  ChartPosition.cx = x;
  ChartPosition.cy = y;
  FFrameRect.left =  ChartPosition.cx / FZoomX;
  FFrameRect.top  =  ChartPosition.cy / FZoomX;
  FFrameRect.right = (ChartRect.right-ChartRect.left)/FZoomX + FFrameRect.left;
  FFrameRect.bottom = (ChartRect.bottom-ChartRect.top)/FZoomX + FFrameRect.top;
  if(FFrameRect.right-FFrameRect.left>DrawRect.right)
    FFrameRect.right=FFrameRect.left+DrawRect.right;
  if(FFrameRect.bottom-FFrameRect.top>DrawRect.bottom)
    FFrameRect.bottom=FFrameRect.top+DrawRect.bottom;
  if(OldFrameRect.top!=FFrameRect.top || OldFrameRect.left!=FFrameRect.left
     || OldFrameRect.right!=FFrameRect.right || OldFrameRect.bottom!=FFrameRect.bottom)
    DrawFrame(NULL);
  //OldFrameRect = FFrameRect;
  //this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::SetShowing(bool bShow)
{
  if(FShowing!=bShow)
  {
	FShowing = bShow;
	this->Visible = bShow;
  }
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::CalFrameMove()
{
  ChartPosition.cx = FFrameRect.left*FZoomX;
  ChartPosition.cy = FFrameRect.top*FZoomX;
  if(FOnFrameMove && MetaFile)
    FOnFrameMove(FFrameRect.left*FZoomX, FFrameRect.top*FZoomX);
}
//---------------------------------------------------------------------------
void __fastcall TNavigationImage::ResizeOnTimer(TObject* Sender)
{
  trResize->Enabled = false;
  trResize->Tag = 0 ;
  this->Invalidate();
}
//---------------------------------------------------------------------------


