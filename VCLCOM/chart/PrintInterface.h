//---------------------------------------------------------------------------

#ifndef PrintInterfaceH
#define PrintInterfaceH
//---------------------------------------------------------------------------
#include <Printers.hpp>
class PACKAGE TPrintInterface
{//所有打印预览使用本接口
protected:
     int FPageWidthMm;
     int FPageHeightMm;
     int FLeftMarginMm;
     int FRightMarginMm;
     int FTopMarginMm;
     int FBottomMarginMm;
     int SPixelsPerInch;
     int PrinterPhysicalOffSetX; //打印机的物理偏移量
     int PrinterPhysicalOffSetY;
     int PrinterPixelsPerInchX;
     int PrinterPixelsPerInchY;

     int iLeftPageMargin;
     int iRightPageMargin;
     int iFullPageWidth;
     int iPageWidth;

     int iTopPageMargin;
     int iBottomPageMargin;
     int iFullPageHeight;
     int iPageHeight;


	 Printers::TPrinterOrientation FOrientation;
     //int FSize;
     String FTitle;
     TFont * FTitleFont;
     bool FShowPageNo;

     virtual String __fastcall GetName() = 0;
     virtual int __fastcall GetPageCount() = 0;
     virtual int __fastcall GetPageWidthMm(){ return FPageWidthMm; }
     virtual int __fastcall GetPageHeightMm(){ return FPageHeightMm; }
     virtual int __fastcall GetLeftMarginMm(){ return FLeftMarginMm; }
     virtual int __fastcall GetRightMarginMm(){ return FRightMarginMm; }
     virtual int __fastcall GetTopMarginMm(){ return FTopMarginMm; }
     virtual int __fastcall GetBottomMarginMm(){ return FBottomMarginMm; }
     virtual void __fastcall SetPageWidthMm(int AWidth){ FPageWidthMm = AWidth; }
     virtual void __fastcall SetPageHeightMm(int AHeight){ FPageHeightMm = AHeight; }
     virtual void __fastcall SetLeftMarginMm(int AHeight){ FLeftMarginMm = AHeight; }
     virtual void __fastcall SetRightMarginMm(int AHeight){ FRightMarginMm = AHeight; }
     virtual void __fastcall SetTopMarginMm(int AHeight){ FTopMarginMm = AHeight; }
     virtual void __fastcall SetBottomMarginMm(int AHeight){ FBottomMarginMm = AHeight; }
     virtual void __fastcall SetProperty(int Index, String Value){}
     virtual String __fastcall GetProperty(int Index){ return ""; }
     virtual String __fastcall GetPropertyName(int Index){ return ""; }
     virtual int __fastcall GetPropertyCount() = 0;
     void __fastcall SetTitleFont(TFont*AFont){FTitleFont->Assign(AFont);}

     virtual void PreparePrint(){}
     virtual void EndPrint(){}
     virtual HENHMETAFILE __fastcall MakeMetalFile( int PageNo)=0;
     void PreviewAPageImpl(HDC dc,int PageNo,RECT cr);
     void PrintAPageImpl(HDC dc,int PageNo);
     virtual void PrintImpl();

     TPrintInterface();
     virtual ~TPrintInterface(){delete FTitleFont;}
public:
	 void __fastcall InitPrintPage();
	 void __fastcall Print();
	 void __fastcall PreviewAPage(HDC dc,int PageNo,RECT cr);
	 void __fastcall PrintAPage(HDC dc,int PageNo);
     __property String Name = {read=GetName};
     __property int PageWidthMm = {read=GetPageWidthMm, write=SetPageWidthMm};
     __property int PageHeightMm = {read=GetPageHeightMm, write=SetPageHeightMm};
     __property int PageCount = {read=GetPageCount};
     __property int LeftMarginMm = {read=GetLeftMarginMm, write=SetLeftMarginMm};
     __property int RightMarginMm = {read=GetRightMarginMm, write=SetRightMarginMm};
     __property int TopMarginMm = {read=GetTopMarginMm, write=SetTopMarginMm};
     __property int BottomMarginMm = {read=GetBottomMarginMm, write=SetBottomMarginMm};
	 __property Printers::TPrinterOrientation Orientation = {read=FOrientation, write=FOrientation};
     __property String Title = {read=FTitle, write=FTitle};
     __property TFont* TitleFont = {read=FTitleFont, write=SetTitleFont};
     __property bool ShowPageNo = {read=FShowPageNo, write=FShowPageNo};

     __property String Property[int Index] = {read=GetProperty, write=SetProperty};
     __property String PropertyName[int Index] = {read=GetPropertyName};
     __property int PropertyCount = {read=GetPropertyCount};
};
#endif

