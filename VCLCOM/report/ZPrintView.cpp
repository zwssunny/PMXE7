//---------------------------------------------------------------------------

#include <vcl.h>
#include <graphics.hpp>
#pragma hdrstop

#include "ZPrintView.h"
#include "PrintInterface.h"
#include "CopyRight.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
//#define FPrintHandle ((TPrintInterface*)(FPrintHandle))
static inline void ValidCtrCheck(TPrintView *)
{
        new TPrintView(NULL);
}

namespace Zprintview
{

        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TPrintView)};
				 RegisterComponents("ZReport", classes, 0);
        }
}
//---------------------------------------------------------------------------
double ShowSizes[10] = {
          0.1, //0
          0.3, //1
          0.5, //2
          0.8, //3
          1, //4
          1.2, //5
          1.5, //6
          2.0, //7
          4.0, //8
          8.0 //9
          };
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TPrintView::TPrintView(TComponent* Owner)
        : TWinControl(Owner)
{
	//checkCopyRight();
    Color = clWhite;
    FZoom = 4;
//    Width = 197; //去除打印机物理偏移量
//    Height = 288;
    FPage = -1;
    FPageSize = 3;
    MetaFile = NULL;
    FShowPage = new Graphics::TBitmap();

}
__fastcall TPrintView::~TPrintView()
{
    if(MetaFile)
       DeleteEnhMetaFile(MetaFile);
    delete FShowPage;
}
//---------------------------------------------------------------------------
void __fastcall TPrintView::WMPaint(Messages::TWMPaint &Message)
{
    TWinControl::Dispatch(&Message);
    if(FPrintHandle && FPage >= 0)
    {
       HDC WindowDC = GetDC(Handle);
       BitBlt(WindowDC, 0, 0, ClientWidth, ClientHeight,
              FShowPage->Canvas->Handle, 0, 0, SRCCOPY);
       ReleaseDC(Handle, WindowDC);
    }

}
//---------------------------------------------------------------------------
void __fastcall TPrintView::SetZoom(int AZoom)
{
    if(FZoom==AZoom)
       return;
    if(AZoom >= 0 && AZoom <= 9)
    {
       FZoom = AZoom;
       if(FPrintHandle)
       {
//          Width = FPrintHandle->PageWidthMm *
//                  Screen->PixelsPerInch
//                  * 0.03937 * ShowSizes[FZoom];
//          Height = FPrintHandle->PageHeightMm *
//                  Screen->PixelsPerInch
//                  * 0.03937 * ShowSizes[FZoom];
//         FShowPage->Width=Width;
//         FShowPage->Height=Height;
         RefreshPage();
       }
    }
}
//---------------------------------------------------------------------------
void TPrintView::RefreshPage()
{
    FPrintHandle->InitPrintPage();
    Width = FPrintHandle->PageWidthMm *
            Screen->PixelsPerInch
            * 0.03937 * ShowSizes[FZoom];
    Height = FPrintHandle->PageHeightMm *
            Screen->PixelsPerInch
            * 0.03937 * ShowSizes[FZoom];
   FShowPage->Width=Width;
   FShowPage->Height=Height;

    HBRUSH Brush = CreateSolidBrush(clWhite);
    HGDIOBJ oldBrush = SelectObject(FShowPage->Canvas->Handle, Brush);
    RECT r;
    r.left=0;
    r.top=0;
    r.right=FShowPage->Width;
    r.bottom=FShowPage->Height;
    FShowPage->Canvas->FillRect(r);
    SelectObject(FShowPage->Canvas->Handle,oldBrush);
    DeleteObject(Brush);
    FPrintHandle->PreviewAPage(FShowPage->Canvas->Handle, FPage,r);//画图
    Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TPrintView::SetPage(int APage)
{
    if(FPage==APage)
       return;
    if(FPrintHandle)
    if(APage >= 0 && APage < FPrintHandle->PageCount)
    {
        FPage = APage;
        RefreshPage();
    }
}
//---------------------------------------------------------------------------
void TPrintView::First()
{
    Page = 0;
}
//---------------------------------------------------------------------------
void TPrintView::Prior()
{
    Page--;
}
//---------------------------------------------------------------------------
void TPrintView::Next()
{
    Page++;
}
//---------------------------------------------------------------------------
void TPrintView::Last()
{
    if(FPrintHandle)
       Page = FPrintHandle->PageCount - 1;
}
//---------------------------------------------------------------------------
void TPrintView::Print()
{
    if(FPrintHandle)
       FPrintHandle->Print();
}
//---------------------------------------------------------------------------
void TPrintView::ZoomIn()
{
    Zoom++;
}
//---------------------------------------------------------------------------
void TPrintView::ZoomOut()
{
    Zoom--;
}
//---------------------------------------------------------------------------
void __fastcall TPrintView::SetPrintHandle(TPrintInterface* Value)
{
	if(FPrintHandle!=Value)
    {
	   FPrintHandle =(TPrintInterface*) Value;
       FPrintHandle->InitPrintPage();
       if(FPrintHandle->PageCount)
          FPage = 0;
	   else
		  FPage = -1;
		RefreshPage();
	}
}
//--------------------------------------------------------------------
//suport for printhandle
int __fastcall TPrintView::GetPageWidthMm()
{
    return FPrintHandle->PageWidthMm;
}
void __fastcall TPrintView::SetPageWidthMm(int Value)
{
    FPrintHandle->PageWidthMm = Value;
}
int __fastcall TPrintView::GetPageHeightMm()
{
    return FPrintHandle->PageHeightMm;
}
void __fastcall TPrintView::SetPageHeightMm(int Value)
{
    FPrintHandle->PageHeightMm = Value;
}
int __fastcall TPrintView::GetPageCount()
{
    return FPrintHandle->PageCount;
}
int __fastcall TPrintView::GetLeftMarginMm()
{
    return FPrintHandle->LeftMarginMm;
}
void __fastcall TPrintView::SetLeftMarginMm(int Value)
{
    FPrintHandle->LeftMarginMm = Value;
}
int __fastcall TPrintView::GetRightMarginMm()
{
    return FPrintHandle->RightMarginMm;
}
void __fastcall TPrintView::SetRightMarginMm(int Value)
{
    FPrintHandle->RightMarginMm = Value;
}
int __fastcall TPrintView::GetTopMarginMm()
{
    return FPrintHandle->TopMarginMm;
}
void __fastcall TPrintView::SetTopMarginMm(int Value)
{
    FPrintHandle->TopMarginMm = Value;
}
int __fastcall TPrintView::GetBottomMarginMm()
{
    return FPrintHandle->BottomMarginMm;
}
void __fastcall TPrintView::SetBottomMarginMm(int Value)
{
    FPrintHandle->BottomMarginMm = Value;
}
Printers::TPrinterOrientation __fastcall TPrintView::GetOrientation()
{
    return FPrintHandle->Orientation;
}
void __fastcall TPrintView::SetOrientation(Printers::TPrinterOrientation Value)
{
    FPrintHandle->Orientation = Value;
}
/*int __fastcall TPrintView::GetSize()
{
    //return 100;//
    FPrintHandle->Size;
}
void __fastcall TPrintView::SetSize(int Value)
{
    FPrintHandle->Size = Value;
} */
String __fastcall TPrintView::GetTitle()
{
    return FPrintHandle->Title;
}
void __fastcall TPrintView::SetTitle(String ATitle)
{
    FPrintHandle->Title = ATitle;
}
TFont*__fastcall TPrintView::GetTitleFont()
{
    return FPrintHandle->TitleFont;
}
void __fastcall TPrintView::SetTitleFont(TFont*AFont)
{
    FPrintHandle->TitleFont = AFont;
}
bool __fastcall TPrintView::GetShowPageNo()
{
    return FPrintHandle->ShowPageNo;
}
void __fastcall TPrintView::SetShowPageNo(bool AValue)
{
    FPrintHandle->ShowPageNo = AValue;
}
String __fastcall TPrintView::GetProperty(int Index)
{
    return FPrintHandle->Property[Index];
}
void __fastcall TPrintView::SetProperty(int Index, String Value)
{
    FPrintHandle->Property[Index] = Value;
}
String __fastcall TPrintView::GetPropertyName(int Index)
{
    return FPrintHandle->PropertyName[Index];
}
int __fastcall TPrintView::GetPropertyCount()
{
    return FPrintHandle->PropertyCount;
}

