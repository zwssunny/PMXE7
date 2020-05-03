//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "VclComFunc.h"
#include "GridReport.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TGridReport *)
{
        new TGridReport(NULL);
}
//---------------------------------------------------------------------------
namespace Gridreport
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[2] = {__classid(TGridReport),
                                               __classid(TReportView)};
				 RegisterComponents("ZReport", classes, (sizeof(classes)/sizeof(classes[0])) - 1);
//                 RegisterPropertyEditor(__typeinfo(TStrings), __classid(TGridReport), "BeforeGridText", __classid(TRichEditStringsEh));
//                 RegisterPropertyEditor(__typeinfo(TStrings), __classid(TGridReport), "AfterGridText", __classid(TRichEditStringsEh));
        }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TGridReport::TGridReport(TComponent* Owner)
        : TComponent(Owner)
{
   FPageWidth = 210;
   FPageHeight = 297;
   FTopMargin = 21;
   FLeftMargin = 15;
   FRightMargin = 15;
   FBottomMargin = 15;
   FPageHeaderHeight = 15;
   FPageFooterHeight = 15;
   FTitleSpace=4;
   FSize = 100;
   FShowHorzLine = true;
   FShowVertLine = true;
   FPrintHeader = false;
   FPrintFooter = false; 

   FPages = NULL;
   FTitleFont = new TFont();
   FPageFooter =new TPageColontitle();
   FPageHeader =new TPageColontitle();
   FAfterGridText=new TStringList();
   FBeforeGridText=new TStringList();

}
__fastcall TGridReport::~TGridReport()
{
//   if(FRoomGrid)
//      FRoomGrid->RemoveFreeNotification(this);
//   if(FGrid)
//      FGrid->RemoveFreeNotification(this);
   if(FPages)
      free(FPages);
   if(FAfterGridText!=NULL)
     delete FAfterGridText;
   if(FBeforeGridText!=NULL)
     delete FBeforeGridText;
   delete TitleFont;
   delete FPageFooter;
   delete FPageHeader;

}
int __fastcall WriteTextEh(HDC dc, TRect ARect, bool FilledRect,
	 String Text, TAlignment Alignment, TTextLayout Layout, bool
	MultyL, bool EndEllipsis, int LeftMarg=0, int RightMarg=0, bool CalcRect=false, bool ARightToLeftAlignment=false, bool
	ARightToLeftReading=false)
{
  int AlignFlags[3]={DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX,DT_RIGHT | DT_EXPANDTABS | DT_NOPREFIX,
    DT_CENTER | DT_EXPANDTABS | DT_NOPREFIX };
  int RTL[2]= {0, DT_RTLREADING};
  int opt;
  TEXTMETRIC tm;
  TRect rect1;
  int txth, DrawFlag;
  TDrawTextParams lpDTP;
  int Result = 0;
  if (ARightToLeftAlignment)
  {
    ChangeBiDiModeAlignment(Alignment);
    opt = LeftMarg;
    LeftMarg = RightMarg;
    RightMarg = opt;
  }
  if (CalcRect == false)
  {
    DrawFlag = 0;
    if (MultyL) DrawFlag = DrawFlag | DT_WORDBREAK;
    if (EndEllipsis ) DrawFlag = DrawFlag | DT_END_ELLIPSIS;
    DrawFlag = DrawFlag | AlignFlags[Alignment] | RTL[ARightToLeftReading];
    rect1 = ARect;

    lpDTP.cbSize = sizeof(lpDTP);
    lpDTP.uiLengthDrawn = Text.Length();
    lpDTP.iLeftMargin = LeftMarg;
    lpDTP.iRightMargin = RightMarg;


    if (Layout != tlTop)
	  txth = DrawTextEx(dc, Text.c_str(), Text.Length(),
		&rect1, DrawFlag | DT_CALCRECT, &lpDTP);
    else txth = 0;
    rect1 = ARect;

    switch(Layout)
    {
	  case tlTop:
           rect1.left+=2;
           rect1.top+=2;
           break;
      case tlBottom:
           rect1.top = rect1.Bottom - txth;
           break;
      case tlCenter:
           rect1.top = rect1.top + ((rect1.Bottom - rect1.top) / 2) - (txth / 2);
           break;
    }
    HRGN MyRgn=::CreateRectRgn(ARect.left,ARect.top,ARect.right,ARect.bottom);
    ::SelectClipRgn(dc,MyRgn);
	DrawTextEx(dc, Text.c_str(), Text.Length(), &rect1, DrawFlag, &lpDTP);
   ::SelectClipRgn(dc,NULL);
   ::DeleteObject(MyRgn);
  }
  else
    {
      GetTextMetrics(dc, &tm);
      opt = DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX | DT_CALCRECT | RTL[ARightToLeftReading];
      if( MultyL)
         opt = opt | DT_WORDBREAK;
	   Result = DrawTextEx(dc, Text.c_str(), Text.Length(), &ARect, opt, NULL);
       Result+=tm.tmExternalLeading;
  }
  return Result;
}
TRect ScaleRect(TRect ARect, int XMul, int YMul, int XDiv, int YDiv)
{
      TRect Result;
      Result.Left = ARect.Left * XMul / XDiv;
      Result.Right = ARect.Right * XMul / XDiv;
      Result.Top = ARect.Top * YMul / YDiv;
      Result.Bottom = ARect.Bottom * YMul / YDiv;
      return Result;
}

int __fastcall TGridReport::GetRichTextHeight(HDC dc, TStrings* String)
{
   int Result=0;
   Result=String->Count*TextHeight(dc,String->Text);
   return Result;
}
int TGridReport::TextWidth(HDC dc, String Text)
{
   RECT r;
   r.top = 0;
   r.left = 0;
   r.right = 1000;
   r.bottom = 1000;
   DrawText(dc, Text.c_str(), Text.Length(), &r, DT_CALCRECT);
   return r.right - r.left;
}
int __fastcall TGridReport::GetTitleHeight(HDC dc)
{
//  int Result=0;
//  if(!Title.IsEmpty())
//  {
//   HFONT newFont,oldFont;
//   try
//   {
//      LOGFONT  pFont;
//      pFont.lfHeight =- MulDiv (FTitleFont->Size, GetDeviceCaps(dc,LOGPIXELSY), 72);
//      pFont.lfWidth = 0;
//      pFont.lfEscapement = 0;
//      pFont.lfOrientation = 0;
//      if(FTitleFont->Style.Contains(fsBold))
//         pFont.lfWeight = FW_BOLD;
//      else
//         pFont.lfWeight = FW_NORMAL;
//      pFont.lfItalic = FTitleFont->Style.Contains(fsItalic);
//      pFont.lfUnderline = FTitleFont->Style.Contains(fsUnderline);
//      pFont.lfStrikeOut = FTitleFont->Style.Contains(fsStrikeOut);
//      pFont.lfCharSet = FTitleFont->Charset;
//      strcpy(pFont.lfFaceName, FTitleFont->Name.c_str());
//      pFont.lfQuality = DEFAULT_QUALITY;
//      pFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
//      pFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
//      switch(FTitleFont->Pitch)
//      {
//         case fpVariable:
//            pFont.lfPitchAndFamily = VARIABLE_PITCH;
//            break;
//         case fpFixed:
//            pFont.lfPitchAndFamily = FIXED_PITCH;
//            break;
//         default:
//            pFont.lfPitchAndFamily = DEFAULT_PITCH;
//      }
//     newFont=CreateFontIndirect(&pFont);
//     oldFont=SelectObject(dc,newFont);
//     SIZE textsize;
//     bool bt=GetTextExtentPoint32(dc,Title.c_str(),Title.Length(),&textsize);
//     Result=textsize.cy;
//   }
//   __finally
//   {
//    SelectObject(dc,oldFont);
//    DeleteObject(newFont);
//   }
//  }
//  return Result;
   return -FTitleFont->Height;
}
int TGridReport::TextHeight(HDC dc, String Text)
{
   RECT r;
   r.top = 0;
   r.left = 0;
   r.right = 1000;
   r.bottom = 1000;
   DrawText(dc, Text.c_str(), Text.Length(), &r, DT_CALCRECT);
   return r.bottom - r.top;
}
TRect TGridReport::CellSize(int Left, int Top, int Right, int Bottom, PrintPage*APage)
{//return left, right, height
   TRect retval;
   retval.Left = 0;
   retval.Top = 0;
   retval.Right = 0;
   retval.Bottom = 0;
   if(FGrid)
   {
       for(int i = APage->Left; i < Left; i++)
          if(FGrid->ColWidths[i] > 0)
             retval.Left += FGrid->ColWidths[i];
       retval.Right = retval.Left;
       for(int i = Left; i <= Right; i++)
          if(FGrid->ColWidths[i] > 0)
             retval.Right += FGrid->ColWidths[i];
       for(int i = Top; i <= Bottom; i++)
          retval.Bottom += FGrid->RowHeights[i];
   }else if(FRoomGrid)
   {
       for(int i = APage->Left; i < Left; i++)
          retval.Left += FRoomGrid->ColWidths[i];
       retval.Right = retval.Left;
       for(int i = Left; i <= Right; i++)
          retval.Right += FRoomGrid->ColWidths[i];
       for(int i = Top; i <= Bottom; i++)
          retval.Bottom += FRoomGrid->RowHeights[i];
   }else
   {
   }
   return retval;
}
int ColWidths(TZGrid* Grid, int Col1, int Col2)
{
   int Rtn(0);
   for(int i = Col1; i <= Col2; i++)
   {
       Rtn += Grid->ColWidths[i];
   }
   return Rtn;
}
TRect TGridReport::AnalysisCellRect(int Col, int Row, PrintPage*APage)
{
   TRect DrawRect = CellSize(Col, Row, Col, Row, APage);
   if(FGrid)
   {
       if(Row >= FGrid->FixedRows)
		   return DrawRect;
       TRect ARect = DrawRect;
       if(FGrid->Columns->Items[Col]->Merged)
       {
            if(Col>=FGrid->Columns->Items[Col]->ColMergeOrder && Col<FGrid->Columns->Items[Col]->ColMergeOrder+FGrid->Columns->Items[Col]->ColMergeCount
              && Row>=FGrid->Columns->Items[Col]->RowMergeOrder && Row<FGrid->Columns->Items[Col]->RowMergeOrder+FGrid->Columns->Items[Col]->RowMergeCount)
            {
                if(Col > FGrid->Columns->Items[Col]->ColMergeOrder && Col == APage->Left)
                {
                    int FirstCol=Col;
                    int FirstRow=FGrid->Columns->Items[Col]->RowMergeOrder;
                    int LastCol=FGrid->Columns->Items[Col]->ColMergeOrder+FGrid->Columns->Items[Col]->ColMergeCount-1;
                    int LastRow=FGrid->Columns->Items[Col]->RowMergeOrder+FGrid->Columns->Items[Col]->RowMergeCount-1;
                    LastCol = LastCol < APage->Right ? LastCol : APage->Right;//2002.04.15 lu
                    DrawRect=CellSize(FirstCol,FirstRow, LastCol, LastRow, APage);
                }else if(Col > FGrid->Columns->Items[Col]->ColMergeOrder &&
                         ColWidths(FGrid,FGrid->Columns->Items[Col]->ColMergeOrder, Col-1) <= 0)
                {
                    int FirstCol=Col;
                    int FirstRow=FGrid->Columns->Items[Col]->RowMergeOrder;
                    int LastCol=FGrid->Columns->Items[Col]->ColMergeOrder+FGrid->Columns->Items[Col]->ColMergeCount-1;
                    int LastRow=FGrid->Columns->Items[Col]->RowMergeOrder+FGrid->Columns->Items[Col]->RowMergeCount-1;
                    LastCol = LastCol < APage->Right ? LastCol : APage->Right;//2002.04.15 lu
                    DrawRect=CellSize(FirstCol,FirstRow, LastCol, LastRow, APage);
                }else if(Col > FGrid->Columns->Items[Col]->ColMergeOrder ||
                    Row > FGrid->Columns->Items[Col]->RowMergeOrder)
                {
                    DrawRect.Right = DrawRect.Left;
                }else
                {
                    int FirstCol=FGrid->Columns->Items[Col]->ColMergeOrder;
                    int FirstRow=FGrid->Columns->Items[Col]->RowMergeOrder;
                    int LastCol=FGrid->Columns->Items[Col]->ColMergeOrder+FGrid->Columns->Items[Col]->ColMergeCount-1;
                    int LastRow=FGrid->Columns->Items[Col]->RowMergeOrder+FGrid->Columns->Items[Col]->RowMergeCount-1;
                    LastCol = LastCol < APage->Right ? LastCol : APage->Right;//2002.04.15 lu
                    DrawRect=CellSize(FirstCol,FirstRow, LastCol, LastRow, APage);
                }
            }else
            {
                return DrawRect;
            }
       }
   }else if(FRoomGrid)
   {
       if(Row >= FRoomGrid->FixedRows)
          return DrawRect;
   }
   return DrawRect;
}
//---------------------------------------------------------------------------
void TGridReport::DrawExpandFold(HDC dc, PrintEnvir&Envir, int X, int Y, bool Expanded)
{
   HPEN pen = CreatePen(PS_SOLID, 1, TColor(RGB(128, 128, 128)));
   HGDIOBJ oldpen = SelectObject(dc, pen);
   int RectWidth=4*Envir.DrawXPixelInch / Envir.GridXPixelInch;
   int RectHeight=4*Envir.DrawYPixelInch / Envir.GridYPixelInch;
   MoveToEx(dc, X -RectWidth , Y - RectHeight, NULL);
   LineTo(dc, X + RectWidth, Y - RectHeight);
   LineTo(dc, X + RectWidth, Y + RectHeight);
   LineTo(dc, X - RectWidth, Y + RectHeight);
   LineTo(dc, X - RectWidth, Y - RectHeight);

   HPEN temppen = CreatePen(PS_SOLID, 1, clBlack);
   SelectObject(dc, temppen);
   DeleteObject(pen);
   pen = temppen;

   MoveToEx(dc, X - RectWidth, Y, NULL);
   LineTo(dc, X + RectWidth, Y);
   if(!Expanded)
   {
       MoveToEx(dc, X, Y - RectHeight, NULL);
       LineTo(dc, X, Y + RectHeight);
   }
   SelectObject(dc, oldpen);
   DeleteObject(pen);
}
//---------------------------------------------------------------------------
void TGridReport::DrawExpandFoldCell(HDC dc, PrintEnvir&Envir, TRect &ARect, String&AName, int Layer, int ExpandType)
{//ExpandType 0:None 1:Expanded 2:Folded
   //line
   if(FShowVertLine)
   {
      MoveToEx(dc, ARect.Left, ARect.Top, NULL);
      LineTo(dc, ARect.Left, ARect.Bottom);
      MoveToEx(dc, ARect.Right, ARect.Top, NULL);
      LineTo(dc, ARect.Right, ARect.Bottom);
   }
   if(FShowHorzLine)
   {
      MoveToEx(dc, ARect.Left, ARect.Top, NULL);//left top
      LineTo(dc, ARect.Right, ARect.Top);
      MoveToEx(dc, ARect.Left, ARect.Bottom, NULL);//left top
      LineTo(dc, ARect.Right, ARect.Bottom);
   }

   int ExpandInc = 20;
   int ExpandSize = 20;
   ExpandInc = ExpandInc * Envir.DrawXPixelInch / Envir.GridXPixelInch;
   ExpandSize = ExpandSize * Envir.DrawXPixelInch / Envir.GridXPixelInch;
   TRect dr = ARect;
   switch(ExpandType)
   {
       case 1:
           DrawExpandFold(dc, Envir, ARect.Left + (Layer) * ExpandInc + ExpandSize / 2,
                          (ARect.Top + ARect.Bottom) / 2, true);
           dr.Left = dr.Left + (Layer) * ExpandInc + ExpandSize;
           break;
       case 2:
           DrawExpandFold(dc, Envir, ARect.Left + (Layer) * ExpandInc + ExpandSize / 2,
                          (ARect.Top + ARect.Bottom) / 2, false);
           dr.Left = dr.Left + (Layer) * ExpandInc + ExpandSize;
           break;
       case 0:
           dr.Left = dr.Left + (Layer) * ExpandInc + ExpandSize;
           break;
       default:
           throw Exception("TPrjGrid::DrawName逻辑错误");
   }
   DrawText(dc, AName.c_str(), AName.Length(), &dr, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
}
//---------------------------------------------------------------------------
void TGridReport::DrawACell(HDC dc, PrintEnvir&Envir, TRect r, String Str,
                            TColHorAlign AAlign, TColor bkColor,bool MultyLine,TRowVerAlign VAlign)
{
     HBRUSH brush = CreateSolidBrush(bkColor);
     HGDIOBJ oldbrush = SelectObject(dc, brush);
     FillRect(dc, &r, brush);
     SelectObject(dc, oldbrush);
     DeleteObject(brush);

   if(MultyLine)
	  WriteTextEh(dc,r,true,Str,AAlign,VAlign,true,true);
     else
  {
     SetBkMode(dc, TRANSPARENT);
     DRAWTEXTPARAMS Params;//draw text params
     Params.cbSize = sizeof(DRAWTEXTPARAMS);
     Params.iTabLength = 0;
     Params.iLeftMargin = 2;
     Params.iRightMargin = 2;
     Params.uiLengthDrawn = 0;
     switch(AAlign)
     {
        case haLeft:
		   DrawTextEx(dc, Str.c_str(), Str.Length(), &r, DT_LEFT|DT_VCENTER|DT_SINGLELINE, &Params);
		   break;
		case haCenter:
		   DrawTextEx(dc, Str.c_str(), Str.Length(), &r, DT_CENTER|DT_VCENTER|DT_SINGLELINE, &Params);
           break;
        case haRight:
		   DrawTextEx(dc, Str.c_str(), Str.Length(), &r, DT_RIGHT|DT_VCENTER|DT_SINGLELINE, &Params);
           break;
     }
   }
   //line
   if(FShowVertLine)
   {
      MoveToEx(dc, r.Left, r.Top, NULL);
      LineTo(dc, r.Left, r.Bottom);
      MoveToEx(dc, r.Right, r.Top, NULL);
      LineTo(dc, r.Right, r.Bottom);
   }
   if(FShowHorzLine)
   {
      MoveToEx(dc, r.Left, r.Top, NULL);//left top
      LineTo(dc, r.Right, r.Top);
      MoveToEx(dc, r.Left, r.Bottom, NULL);//left top
      LineTo(dc, r.Right, r.Bottom);
   }
}
//---------------------------------------------------------------------------
void TGridReport::DrawCellItem(HDC CanvasHandle,String sDrawText
      ,TRect &DrawRect,UINT dpAlign,int StepHeight)
{
  if(sDrawText!=NULL && (!sDrawText.Trim().IsEmpty()))
  {
    DrawRect.Top=DrawRect.Bottom;
    DrawRect.Bottom=DrawRect.Top+StepHeight;
	DrawText(CanvasHandle,sDrawText.c_str(),sDrawText.Length(),&DrawRect,dpAlign);
  }
}
//---------------------------------------------------------------------------
void TGridReport::HDrawACell(HDC dc, PrintEnvir&Envir, TRect r, TCells *CellData,
                            TColHorAlign AAlign, TColor bkColor)
{
   if(bkColor != clWhite)
   {
       HBRUSH brush = CreateSolidBrush(bkColor);
       HGDIOBJ oldbrush = SelectObject(dc, brush);
       FillRect(dc, &r, brush);
       SelectObject(dc, oldbrush);
       DeleteObject(brush);
   }
    SetBkMode(dc, TRANSPARENT);
    TRect Toprect,Downrect;
    Toprect = r;
    Downrect = r;
    int StepHeight=FRoomGrid->StepLineHeight* Envir.DrawXPixelInch / Envir.GridXPixelInch;//Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
    Toprect.bottom =r.Top+FRoomGrid->UnitTitleHeight*Envir.DrawXPixelInch / Envir.GridXPixelInch;// Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
    Downrect.top = Toprect.Bottom;
   if(FRoomGrid->GetStatus(CellData)!=6)
   {
      String TitleText=CellData->Title;
      if(CellData->DoubleLays!=0)
         TitleText+="(复)";
	  DrawText(dc,TitleText.c_str(),TitleText.Length(),&Toprect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
      UINT dpAlign=DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS;
      if(FRoomGrid->PrintAlign==0)
         dpAlign|=DT_LEFT;
       else if(FRoomGrid->PrintAlign==2)
          dpAlign|=DT_RIGHT;
       else
          dpAlign|=DT_CENTER;

      String ProText=CellData->Detail;
      Downrect.Bottom=Downrect.Top;
	  if(RoomGrid->DisplayDetail)//画功能
      {
        DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      //显示单元属性
      ProText=CellData->HouseType;
      if(FRoomGrid->DisplayHouseType) //画户型
      {
        DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->Sight;
      if(FRoomGrid->DisplaySight)//画景观
      {
        DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->Fitment;
      if(FRoomGrid->DisplayFitment) //画装修
      {
        DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->Direction;
      if(FRoomGrid->DisplayDirection) //朝向
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->UseArea;
      if(FRoomGrid->DisplayUseArea) //套内面积
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      /////////////////////////////////////////
      ProText=CellData->ApportionArea;
      if(FRoomGrid->DisplayApportionArea) //分摊面积
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }


      ProText=CellData->RoofGargdenArea;  //平台面积
      if(FRoomGrid->DisplayRoofGarden)
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->Area;
      if( FRoomGrid->DisplayArea)   //建筑面积
      {
         DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText = CellData->UpArea+"/"+CellData->DownArea;
      if((FRoomGrid->DisplayArea||FRoomGrid->DisplayUseArea)&&(CellData->DoubleLays!=0)&&ProText!="/") //上下层面积
      {
         DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->SaleArea;
      if(FRoomGrid->DisplaySaleArea) //销售面积
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->PreSaleArea;
      if(FRoomGrid->DisplayPreSaleArea) //预售面积
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->RightArea;
      if(FRoomGrid->DisplayRightArea) //产权面积
      {
       DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }

      ProText=CellData->UnitPrice;
      if( FRoomGrid->DisplayUnitPrice)  //单价
      {
         DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->TotalCost;
      if( FRoomGrid->DisplayTotalCost ) //总价
      {
         DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->UnitLeaseCost;
      if( FRoomGrid->DisplayUnitLeaseCost ) //单位月租金
      {
         DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }
      ProText=CellData->LeaseCost;
      if( FRoomGrid->DisplayLeaseCost ) //月租金
      {
         DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      }

      //ProText=CellData->CanLease;
      //if( FRoomGrid->DisplayCanLease) //能否出租
      //{
      //   DrawCellItem(dc,ProText,Downrect,dpAlign,StepHeight);
      //}

      MoveToEx(dc,r.left,Toprect.bottom,NULL); //画中线
      LineTo(dc,r.right,Toprect.bottom);
     }
    else
    {
       HBRUSH brush = CreateSolidBrush(clWhite);
       HGDIOBJ oldbrush = SelectObject(dc, brush);
       FillRect(dc, &r, brush);
       SelectObject(dc, oldbrush);
       DeleteObject(brush);
     }

   //line
   if(FShowVertLine)
   {
      MoveToEx(dc, r.Left, r.Top, NULL);
      LineTo(dc, r.Left, r.Bottom);
      MoveToEx(dc, r.Right, r.Top, NULL);
      LineTo(dc, r.Right, r.Bottom);
   }
   if(FShowHorzLine)
   {
      MoveToEx(dc, r.Left, r.Top, NULL);//left top
      LineTo(dc, r.Right, r.Top);
      MoveToEx(dc, r.Left, r.Bottom, NULL);//left top
      LineTo(dc, r.Right, r.Bottom);
   }
}
void  TGridReport::DrawGridFooter(HDC dc, PrintEnvir& Envir, PrintPage* APage, int & PrintTop, double CellScale)
{
   int PrintLeftMerge = FLeftMargin * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
   int CellHeight;
   for(int j = APage->Left; j <= APage->Right; j++)
   {
          if(FGrid->ColWidths[j] > 0)
          {
              TRect DrawRect = CellSize(j,FGrid->FixedRows,j,FGrid->FixedRows,APage);
              if(DrawRect.Left < DrawRect.Right-3)
              {
                  CellHeight = (FGrid->FootHeight*Envir.DrawYPixelInch/Envir.GridYPixelInch) *
                               Envir.DrawSize * Envir.Size / 100;
                  //text
                  int PrintLeft = (DrawRect.Left * Envir.DrawXPixelInch / Envir.GridXPixelInch)
                                  * CellScale * Envir.DrawSize * Envir.Size / 100;
                  PrintLeft = PrintLeftMerge + PrintLeft - Envir.PhysicalOffsetX;
                  //begin modify 2002.4.24     lu
                  int PrintRight = (DrawRect.Right * Envir.DrawXPixelInch / Envir.GridXPixelInch)
                                    * CellScale * Envir.DrawSize * Envir.Size / 100;
                  PrintRight = PrintLeftMerge + PrintRight - Envir.PhysicalOffsetX;
                  //end modify
                  int PrintBottom = PrintTop + CellHeight;
                  TRect tr = TRect(PrintLeft, PrintTop, PrintRight, PrintBottom);
                  HFONT  pFont=CreateFontFromTFont(FGrid->Columns->Items[j]->FootFont,Envir);
				  HFONT  oldFont=(HFONT)SelectObject(dc, pFont);
                  String tstr = FGrid->Columns->Items[j]->FootText;
                  DrawACell(dc, Envir, tr, tstr, FGrid->Columns->Items[j]->ColHorAlign, clWhite);
                  SelectObject(dc,oldFont);
                  DeleteObject(pFont);
              }
         }
   }
   CellHeight = (FGrid->FootHeight*Envir.DrawYPixelInch/Envir.GridYPixelInch) * Envir.DrawSize;
   CellHeight = CellHeight * Envir.Size / 100;
   PrintTop = PrintTop + CellHeight;


}
int TGridReport::DrawARow(HDC dc, PrintEnvir&Envir, PrintPage*APage, int Row, int &PrintTop, double CellScale)
{
   int PrintLeftMerge = FLeftMargin * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
   int CellHeight;
  COLORREF oldtextcolor;
  HFONT tmHFont=NULL ,OldFont=NULL,titleFont,titleOldFont;
  if(FGrid)
  {
//    if(FGrid->RowState[Row]==1)
//      oldtextcolor= SetTextColor(dc, FGrid->WarningColor);
//     else
//      oldtextcolor= SetTextColor(dc, FGrid->Font->Color);
      tmHFont = CreateFontFromTFont(FGrid->RowStateFont(Row),Envir);
	  OldFont =(HFONT)SelectObject(dc, tmHFont);
      oldtextcolor= SetTextColor(dc, FGrid->RowStateFont(Row)->Color);
   }
   for(int j = APage->Left; j <= APage->Right; j++)
   {
      if(FGrid)
      {
          if(FGrid->ColWidths[j] > 0)
          {
              TRect DrawRect = AnalysisCellRect(j, Row, APage);
              if(DrawRect.Left < DrawRect.Right-3)
              {
                  CellHeight = (DrawRect.Height()*Envir.DrawYPixelInch/Envir.GridYPixelInch) *
                               Envir.DrawSize * Envir.Size / 100;
                  //text
                  int PrintLeft = (DrawRect.Left * Envir.DrawXPixelInch / Envir.GridXPixelInch)
                                  * CellScale * Envir.DrawSize * Envir.Size / 100;
                  PrintLeft = PrintLeftMerge + PrintLeft - Envir.PhysicalOffsetX;
                  //begin modify 2002.4.24     lu
                  int PrintRight = (DrawRect.Right * Envir.DrawXPixelInch / Envir.GridXPixelInch)
                                    * CellScale * Envir.DrawSize * Envir.Size / 100;
                  PrintRight = PrintLeftMerge + PrintRight - Envir.PhysicalOffsetX;
                  //end modify
                  int PrintBottom = PrintTop + CellHeight;
                  TRect tr = TRect(PrintLeft, PrintTop, PrintRight, PrintBottom);

                  String tstr = FGrid->TextMatrix[Row][j];
                  if(Row < FGrid->FixedRows)
                  {
//                      if(j > FGrid->Columns->Items[j]->ColMergeOrder &&
//                         Row == FGrid->Columns->Items[j]->RowMergeOrder &&
//                         ColWidths(FGrid,FGrid->Columns->Items[j]->ColMergeOrder, j) <= 0)//j-1->>j
//                      {
//                          tstr = FGrid->TextMatrix[Row][FGrid->Columns->Items[j]->ColMergeOrder];
//                      }
                        int FirstCol,FirstRow;
                        if(FGrid->Columns->Items[j]->Merged)
                        {
                            if(j >= FGrid->Columns->Items[j]->ColMergeOrder && j < 
FGrid->Columns->Items[j]->ColMergeOrder+FGrid->Columns->Items[j]->ColMergeCount
                              && Row >= FGrid->Columns->Items[j]->RowMergeOrder && Row < 
FGrid->Columns->Items[j]->RowMergeOrder+FGrid->Columns->Items[j]->RowMergeCount)
                            {
                                FirstCol = FGrid->Columns->Items[j]->ColMergeOrder;
                                FirstRow = FGrid->Columns->Items[j]->RowMergeOrder;
                            }else
                            {
                              FirstCol = j;
                              FirstRow = Row;
                            }
                        }
                        else
                        {
                            FirstCol = j;
                            FirstRow = Row;
                        }
                      tstr = FGrid->TextMatrix[FirstRow][FirstCol];
                       titleFont=CreateFontFromTFont(FGrid->Columns->Items[j]->ColumnFont,Envir);
					   titleOldFont=(HFONT)SelectObject(dc,titleFont);
                       DrawACell(dc, Envir, tr, tstr, haCenter,clWhite,FGrid->Columns->Items[j]->MultyLine,FGrid->Columns->Items[j]->RowVerAlign);                       SelectObject(dc,titleOldFont);                       DeleteObject(titleOldFont);                       				  }else
                  {
                      if(j == FGrid->ExpandFoldColIndex)
                      {
                          DrawExpandFoldCell(dc, Envir, tr, tstr, FGrid->Layer[Row], 
FGrid->ExpandFoldMark(Row));
                      }else
                      {
                             DrawACell(dc, Envir, tr, tstr, FGrid->Columns->Items[j]->ColHorAlign, 
clWhite,FGrid->Columns->Items[j]->MultyLine,FGrid->Columns->Items[j]->RowVerAlign);
                      }
                  }
              }
          }
      }else if(FRoomGrid)
      {
              TRect DrawRect = AnalysisCellRect(j, Row, APage);
              if(DrawRect.Left < DrawRect.Right-3)
              {
                  CellHeight = (DrawRect.Height()*Envir.DrawYPixelInch/Envir.GridYPixelInch) *
                               Envir.DrawSize * Envir.Size / 100;
                  //text
                  int PrintLeft = (DrawRect.Left * Envir.DrawXPixelInch / Envir.GridXPixelInch)
                                  * CellScale * Envir.DrawSize * Envir.Size / 100;
                  PrintLeft = PrintLeftMerge + PrintLeft - Envir.PhysicalOffsetX;
                  //begin modify 2002.4.24     lu
                  int PrintRight = (DrawRect.Right * Envir.DrawXPixelInch / Envir.GridXPixelInch)
                                    * CellScale * Envir.DrawSize * Envir.Size / 100;
                  PrintRight = PrintLeftMerge + PrintRight - Envir.PhysicalOffsetX;
                  //end modify
                  int PrintBottom = PrintTop + CellHeight;
                  TRect tr = TRect(PrintLeft, PrintTop, PrintRight, PrintBottom);

                  if(Row < FRoomGrid->FixedRows || j < FRoomGrid->FixedCols)
                  {
                      String tstr = FRoomGrid->GetCellString(j, Row);
                      DrawACell(dc, Envir, tr, tstr, haCenter, clWhite);
                  }else
                  {
                      TCells* Cells = FRoomGrid->GetCellData(j, Row);
                      if(Cells)
                      {
//                          String tstr = Cells->Title;
//                          DrawACell(dc, Envir, tr, tstr, haCenter, FRoomGrid->DispColor[Cells->Status-1]);
                       // HDrawACell(dc, Envir,tr, Cells, haCenter, FRoomGrid->DispColor[Cells->Status-1]);
                            HDrawACell(dc, Envir,tr, Cells, haCenter, FRoomGrid->DisplayColor[FRoomGrid->GetStatus(Cells)]);
                      }
                  }
              }
      }
   }
   if(FGrid)
   {
       CellHeight = (FGrid->RowHeights[Row]*Envir.DrawYPixelInch/Envir.GridYPixelInch) * Envir.DrawSize;
       CellHeight = CellHeight * Envir.Size / 100;
       PrintTop = PrintTop + CellHeight;
       SelectObject(dc, OldFont);
       SetTextColor(dc, oldtextcolor);
       DeleteObject(tmHFont);
   }else if(FRoomGrid)
   {
       CellHeight = (FRoomGrid->RowHeights[Row]*Envir.DrawYPixelInch/Envir.GridYPixelInch) * Envir.DrawSize;
       CellHeight = CellHeight * Envir.Size / 100;
       PrintTop = PrintTop + CellHeight;
   }
   return PrintTop;
}
int  TGridReport::DrawBOrAGridText(HDC dc, PrintEnvir& Envir,TRect ARect, String Text, int & PrintTop)
{
     int Result=0;
     if (Text != "")
      Result = WriteTextEh(dc, ARect, False,Text,
        taLeftJustify, tlTop, false, false, 0, 0, false,
        false, false);
    PrintTop+=Result;
    return Result;
}
int TGridReport::DrawPageColonText(HDC dc, PrintEnvir&Envir,TRect ARect, bool IsHeader, bool CalcHeight)
{
    TPageColontitle* pc;
    TTextLayout Lay;
    int Result=0,h=0,lm;
    if(IsHeader)
    {
        pc=FPageHeader;
        Lay=tlBottom;
    }
    else
    {
        pc=FPageFooter;
        Lay=tlTop;
    }
    HFONT newFont,oldFont;
    newFont=CreateFontFromTFont(pc->Font,Envir);
	oldFont=(HFONT)SelectObject(dc,newFont);
   try
   {
   if (pc->LeftText->Text != "")
      Result = WriteTextEh(dc, ARect, False,  pc->LeftText->Text,
        taLeftJustify, Lay, false, false, 0, 0, CalcHeight ,
        false, false);
    if (pc->CenterText->Text!="")
      h = WriteTextEh(dc, ARect, false,  pc->CenterText->Text,
        taCenter, Lay, false, false, 0, 0, CalcHeight,
        false, false);
    if (Result < h) Result = h;
    if (pc->RightText->Text != "")
      h = WriteTextEh(dc, ARect, false, pc->RightText->Text,
        taRightJustify, Lay, false, false, 0, 0, CalcHeight,
        false, false);
    if (Result < h)  Result = h;
    if (Result != 0) Result+=Envir.DrawSize*Envir.DrawYPixelInch / 10;

//    if (pc->LineType != pcltNon)
//         lm = Envir.DrawYPixelInch / 10;
//       else lm = 0;
    lm=0;
    if (pc->LineType == pcltDoubleLine)
    {
        if (IsHeader)
        {
          MoveToEx(dc,ARect.Left, ARect.Bottom-Envir.DrawSize*Envir.DrawYPixelInch / 10 ,NULL);
          LineTo(dc,ARect.Right, ARect.Bottom-Envir.DrawSize*Envir.DrawYPixelInch / 10 );
          MoveToEx(dc,ARect.Left, ARect.Bottom -Envir.DrawSize*Envir.DrawYPixelInch / 10 - Envir.DrawSize*Envir.DrawYPixelInch / 40,NULL);
          LineTo(dc,ARect.Right, ARect.Bottom -Envir.DrawSize*Envir.DrawYPixelInch / 10 - Envir.DrawSize*Envir.DrawYPixelInch / 40);
        } else
        {
          MoveToEx(dc,ARect.Left, ARect.Top,NULL);
          LineTo(dc,ARect.Right, ARect.Top );
          MoveToEx(dc,ARect.Left, ARect.Top - Envir.DrawYPixelInch / 40,NULL);
          LineTo(dc,ARect.Right, ARect.Top - Envir.DrawYPixelInch / 40);
        }
          lm+=Envir.DrawSize*Envir.DrawYPixelInch / 40;
      }
     else if (pc->LineType == pcltSingleLine)
      {
          if (IsHeader)
          {
            MoveToEx(dc,ARect.Left, ARect.Bottom-Envir.DrawYPixelInch / 10 ,NULL);
            LineTo(dc,ARect.Right, ARect.Bottom-Envir.DrawYPixelInch / 10 );
          }
          else
          {
            MoveToEx(dc,ARect.Left, ARect.Top, NULL);
            LineTo(dc,ARect.Right, ARect.Top );
          }
     }
       Result+=lm;
    }
    __finally
    {
          SelectObject(dc, oldFont);
          DeleteObject(newFont);
    }
    return Result;
}
void TGridReport::DrawPageTitle(HDC dc, PrintEnvir& Envir,int &PrintTop)
{
   try{
       hTitleFont=CreateFontFromTFont(FTitleFont,Envir);
       SelectObject(dc, hTitleFont);
//       int PrintLeft = FLeftMargin * XPixelInch * 0.03937 * FDrawSize;
       int TruePageWidth = FPageWidth * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
       int ATextHeight = TextHeight(dc, "aaa");
       //PrintTop+= FTopMargin * Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;

       String str = FTitle;
       int strWidth = TextWidth(dc, str);
       TextOut(dc, (TruePageWidth-strWidth)/2,
             PrintTop,// - 3*Envir.DrawXPixelInch*0.03937 - ATextHeight - Envir.PhysicalOffsetY,
			 str.c_str(), str.Length());
	 PrintTop+=ATextHeight;
   }
   __finally
   {
       SelectObject(dc, hFont);
       DeleteObject(hTitleFont);
   }
}
void TGridReport::DrawPageNo(HDC dc, PrintEnvir&Envir, int No)
{
   int TruePageWidth = FPageWidth * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
   int TruePageHeight = FPageHeight * Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize-Envir.PhysicalOffsetY ;
   int hbottom=FBottomMargin * Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
   String str = "第 " + IntToStr(No) + " 页 / 共 " + IntToStr(FPageCount) + " 页";
   int strWidth = TextWidth(dc, str);
   int strHeight =TextHeight(dc,str);
   TextOut(dc, (TruePageWidth-strWidth)/2, TruePageHeight-hbottom+strHeight/2 , str.c_str(), str.Length());
}
HFONT __fastcall TGridReport::CreateFontFromTFont(TFont *AFont,PrintEnvir&Envir)
{
      LOGFONT  pFont;
      pFont.lfHeight = AFont->Height * Envir.DrawXPixelInch *
                       Envir.DrawSize * Envir.Size / 100 / Envir.GridXPixelInch; //MulDiv (8, -GetDeviceCaps(dc,LOGPIXELSY), 72);
      pFont.lfWidth = 0;
      pFont.lfEscapement = 0;
      pFont.lfOrientation = 0;
      if(AFont->Style.Contains(fsBold))
         pFont.lfWeight = FW_BOLD;
      else
         pFont.lfWeight = FW_NORMAL;
      pFont.lfItalic = AFont->Style.Contains(fsItalic);
      pFont.lfUnderline = AFont->Style.Contains(fsUnderline);
      pFont.lfStrikeOut = AFont->Style.Contains(fsStrikeOut);
	  pFont.lfCharSet = AFont->Charset;
	  _wcspcpy(pFont.lfFaceName ,AFont->Name.c_str());
	  pFont.lfQuality = DEFAULT_QUALITY;
	  pFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
      pFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
      switch(AFont->Pitch)
      {
		 case TFontPitch::fpVariable:
			pFont.lfPitchAndFamily = VARIABLE_PITCH;
            break;
		 case TFontPitch::fpFixed:
			pFont.lfPitchAndFamily = FIXED_PITCH;
            break;
         default:
            pFont.lfPitchAndFamily = DEFAULT_PITCH;
      }
      return CreateFontIndirect(&pFont);

}
void TGridReport::DrawAPage(HDC dc, PrintEnvir&Envir, PrintPage*APage, int Index)
{
   LOGFONT  pFont;
   try{
//draw font-----------------------------------------------------------
      TFont * AFont;
      if(FGrid)
          AFont = FGrid->Font;
      else if(FRoomGrid)
          AFont = FRoomGrid->Font;
      hFont=CreateFontFromTFont(AFont,Envir);
      goFont = SelectObject(dc, hFont);
      SetBkColor(dc, clWhite);
//head font---------------------------------------------------------------
//      hTitleFont=CreateFontFromTFont(FTitleFont,Envir);
//draw-----------------------------------------------------------------------
      int PrintTop= FTopMargin * Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize-Envir.PhysicalOffsetY;
      if(FGrid)
      {
          double GridWidth = 0;
          for(int k = APage->Left; k <= APage->Right; k++)
          {
             if(FGrid->ColWidths[k] > 0)
                 GridWidth += FGrid->ColWidths[k];
          }
          if(GridWidth > 20)
          {
             GridWidth = GridWidth / double(Envir.GridXPixelInch * 0.03937) * Envir.Size / 100;
             double XScale = double(FPageWidth - FLeftMargin - FRightMargin) / double(GridWidth);
             if(!APage->Adjust)
             {
                 XScale = 1;
             }
             TRect ARect;

             ARect.Left=FLeftMargin * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize-Envir.PhysicalOffsetX;
             ARect.Right=ARect.Left+(FPageWidth-FLeftMargin-FRightMargin)* Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
             if(FPrintHeader)
             {
             ARect.Top=PrintTop;
             ARect.Bottom=ARect.Top+FPageHeaderHeight* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             DrawPageColonText(dc, Envir,ARect, true, false);
             PrintTop=ARect.Bottom+FTitleSpace* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             }
             DrawPageTitle(dc, Envir,PrintTop);
             PrintTop+=FTitleSpace* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             if(Index==1&&FBeforeGridText->Text!="")
               {
                ARect.Top=PrintTop;
                ARect.Bottom=ARect.Top+(FBeforeGridText->Count+1)*TextHeight(dc,"文");
                DrawBOrAGridText(dc, Envir,ARect, FBeforeGridText->Text, PrintTop);
                PrintTop+=ARect.Bottom-ARect.Top;
               }
             int i=0;
             for(i = 0; i < FGrid->FixedRows; i++)
                DrawARow(dc, Envir, APage, i, PrintTop, XScale);
             for(i = APage->Top; i <= APage->Bottom; i++)
             {
                if(i < FGrid->RowCount)
                {
                if(FGrid->RowHeights[i] > 0)
                    DrawARow(dc, Envir, APage, i, PrintTop, XScale);
                }
                else
                {
                  DrawGridFooter( dc, Envir, APage, PrintTop,XScale);
                }
             }
             if((i>=FGrid->RowCount)&&AfterGridText->Text!="")
             {
                ARect.Top=PrintTop;
                ARect.Bottom=ARect.Top+(AfterGridText->Count+1)*TextHeight(dc,"文");
                DrawBOrAGridText(dc, Envir,ARect, AfterGridText->Text, PrintTop);
                PrintTop+=ARect.Bottom-ARect.Top;
             }
             if(FPrintFooter)
             {
             ARect.Top=(FPageHeight-FPageFooterHeight-FBottomMargin)* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             ARect.Left=FLeftMargin * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize-Envir.PhysicalOffsetX;
             ARect.Right=ARect.Left+(FPageWidth-FLeftMargin-FRightMargin)* Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
             ARect.Bottom=ARect.Top+FPageFooterHeight* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             DrawPageColonText(dc, Envir,ARect, false, false);
             }
             DrawPageNo(dc, Envir, Index);
          }
      }else if(FRoomGrid)
      {
          double GridWidth = 0;
          for(int k = APage->Left; k <= APage->Right; k++)
          {
             GridWidth += FRoomGrid->ColWidths[k];
          }
          if(GridWidth > 20)
          {
             GridWidth = GridWidth / double(Envir.GridXPixelInch * 0.03937) * Envir.Size / 100;
             double XScale = double(FPageWidth - FLeftMargin - FRightMargin) / double(GridWidth);
             if(!APage->Adjust)        //zws2004-07-28
             {
                 XScale = 1;
             }
             TRect ARect;
             ARect.Left=FLeftMargin * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize-Envir.PhysicalOffsetX;
             ARect.Right=ARect.Left+(FPageWidth-FLeftMargin-FRightMargin)* Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
             if(FPrintHeader)
             {
                 ARect.Top=PrintTop;
                 ARect.Bottom=ARect.Top+FPageHeaderHeight* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
                 DrawPageColonText(dc, Envir,ARect, true, false);
                 PrintTop=ARect.Bottom+FTitleSpace* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             }
             DrawPageTitle(dc, Envir,PrintTop);
             PrintTop+=FTitleSpace* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
             if(Index==1&&FBeforeGridText->Text!="")
               {
                ARect.Top=PrintTop;
                ARect.Bottom=ARect.Top+(FBeforeGridText->Count+1)*TextHeight(dc,"文");
                DrawBOrAGridText(dc, Envir,ARect, FBeforeGridText->Text, PrintTop);
                PrintTop+=ARect.Bottom-ARect.Top;
               }
             int i=0;
             for(i = 0; i < FRoomGrid->FixedRows; i++)
                DrawARow(dc, Envir, APage, i, PrintTop, XScale);
             for(i = APage->Top; i <= APage->Bottom; i++)
                DrawARow(dc, Envir, APage, i, PrintTop, XScale);
             if(i>=FRoomGrid->RowCount&&AfterGridText->Text!="")
             {
                ARect.Top=PrintTop;
                ARect.Bottom=ARect.Top+(AfterGridText->Count+1)*TextHeight(dc,"文");
                DrawBOrAGridText(dc, Envir,ARect, AfterGridText->Text, PrintTop);
                PrintTop+=ARect.Bottom-ARect.Top;
             }
             if(FPrintFooter)
             {
                 ARect.Top=(FPageHeight-FPageFooterHeight-FBottomMargin)* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
                 ARect.Left=FLeftMargin * Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize-Envir.PhysicalOffsetX;
                 ARect.Right=ARect.Left+(FPageWidth-FLeftMargin-FRightMargin)* Envir.DrawXPixelInch * 0.03937 * Envir.DrawSize;
                 ARect.Bottom=ARect.Top+FPageFooterHeight* Envir.DrawYPixelInch * 0.03937 * Envir.DrawSize;
                 DrawPageColonText(dc, Envir,ARect, false, false);
             }
             DrawPageNo(dc, Envir, Index);
          }
      }
   }__finally
   {
      SelectObject(dc, goFont);
      DeleteObject(hFont);
//      DeleteObject(hTitleFont);
   }
}
void TGridReport::BuildPages()
{
   if(FGrid)
   {
       HDC dc = GetDC(FGrid->Handle);
       int GridXPixelInch = GetDeviceCaps(dc, LOGPIXELSX);
       //单位:像素/每英寸
       int GridYPixelInch = GetDeviceCaps(dc, LOGPIXELSY);
       int XPageSets[200];
       int YPageSets[10000];
       int TYPageCount;
       int cp = 0;
       XPageSets[cp] = -1;
       //像素,1英寸=25.4毫米
       int TruePageWidth = (FPageWidth - FLeftMargin - FRightMargin)
                           * GridXPixelInch * 0.03937;
///*the same*/    int TruePageWidth = ((FPageWidth - FLeftMargin - FRightMargin)/25.4)
//                           * GridXPixelInch;
       double thispageleft = 0;
       for(int i = 0; i < FGrid->ColCount; i++)
       {
          if(FGrid->ColWidths[i] > 0)
          {
             double ColWidth = double(FGrid->ColWidths[i]-1) * double(FSize) / double(100);
             if(thispageleft + ColWidth <= TruePageWidth)
             {
                thispageleft += ColWidth;
             }else
             {
                cp++;
                if(cp >= 200)
                   break;
                i--;
                XPageSets[cp] = i;
                thispageleft = 0;
             }
          }
       }
       if(XPageSets[cp] != FGrid->ColCount-1)
       {
          cp++;
          XPageSets[cp] = FGrid->ColCount - 1;
       }
       int TXPageCount = cp;
    //----------------------------------------------------------
       cp = 0;
       YPageSets[cp] = FGrid->FixedRows-1;
       int iPageHeaderHeight=0,iPageFooterHeight=0;
       if(FPrintHeader)
       {
       if(FPageHeader->LeftText->Text!=""||FPageHeader->CenterText->Text!=""||FPageHeader->RightText->Text!="")
          iPageHeaderHeight=FPageHeaderHeight+FTitleSpace;
       }
       if(FPrintFooter)
       {
       if(FPageFooter->LeftText->Text!=""||FPageFooter->CenterText->Text!=""||FPageFooter->RightText->Text!="")
          iPageFooterHeight=FPageFooterHeight;
       }
       int FixedRowsHeight=0;
       for (int r=0;r<FGrid->FixedRows;r++)
            FixedRowsHeight+=((FGrid->RowHeights[r]) * FSize / 100);
       int TruePageHeight = (FPageHeight - FTopMargin - FBottomMargin-iPageHeaderHeight-iPageFooterHeight-2*FTitleSpace)
                           * GridYPixelInch * 0.03937-(FixedRowsHeight+GetTitleHeight(dc))* FSize / 100;
       int thispagetop=0;
       if(FBeforeGridText->Text!="")
         thispagetop+= (FBeforeGridText->Count+1)*TextHeight(dc,"文");
       ReleaseDC(FGrid->Handle, dc);
       for(int i = FGrid->FixedRows; i < FGrid->RowCount; i++)
       {
          int RowHeight = (FGrid->RowHeights[i]) * FSize / 100;
          if(RowHeight<0)
             RowHeight=0;//zws2004-07-09
          if(RowHeight)
          {
              thispagetop += RowHeight;
              if(thispagetop >= TruePageHeight)
              {
                  cp++;
                  if(cp >= 10000)
                     break;
                  if(thispagetop>TruePageHeight)
                      i--;
                  YPageSets[cp] = i;
                  thispagetop=0;
              }
          }
       }
       if(YPageSets[cp] != FGrid->RowCount-1)
       {
          cp++;
          thispagetop+=(FGrid->RowHeights[FGrid->RowCount - 1]) * FSize / 100;
          YPageSets[cp] = FGrid->RowCount - 1;
          if (FGrid->HasFooter)
          {
               thispagetop+=(FGrid->FootHeight) * FSize / 100;
               YPageSets[cp] = FGrid->RowCount ;
           }
       }
       else if (FGrid->HasFooter)
       {
        cp++;
        thispagetop+=(FGrid->FootHeight) * FSize / 100;
        YPageSets[cp] = FGrid->RowCount ;
       }
//       thispagetop+=GetRichTextHeight(dc,FAfterGridText);
//       if(thispagetop>TruePageHeight)
//       {
//         cp++;
//         YPageSets[cp] = FGrid->RowCount+1 ;
//       }
       TYPageCount = cp;
    //-----------------------------------------------------------
       FPageCount = TXPageCount*TYPageCount;
       if(FPages)
          free(FPages);
       FPages = (PrintPage*)malloc(sizeof(PrintPage)*FPageCount);
       if(FPages == NULL)
          throw Exception("Windows不能分配足够的内存供使用");
       cp = 0;
       for(int i = 0; i < TYPageCount; i++)
       {
          for(int j = 0; j < TXPageCount; j++)
          {
             FPages[cp].Left = XPageSets[j]+1;
             FPages[cp].Right = XPageSets[j+1];
             FPages[cp].Top = YPageSets[i]+1;
             FPages[cp].Bottom = YPageSets[i+1];
             FPages[cp].Adjust = true;
             cp++;
          }
          FPages[cp-1].Adjust = false;
       }
   }else if(FRoomGrid)
   {
       HDC dc = GetDC(FRoomGrid->Handle);
       int GridXPixelInch = GetDeviceCaps(dc, LOGPIXELSX);
       int GridYPixelInch = GetDeviceCaps(dc, LOGPIXELSY);
       int XPageSets[200];
       int YPageSets[10000];
       int TYPageCount;
       int cp = 0;
       XPageSets[cp] = -1;
       int TruePageWidth = (FPageWidth - FLeftMargin - FRightMargin)
                           * GridXPixelInch * 0.03937;
       int iPageHeaderHeight=0,iPageFooterHeight=0;
       if(FPrintHeader)
       {
       if(FPageHeader->LeftText->Text!=""||FPageHeader->CenterText->Text!=""||FPageHeader->RightText->Text!="")
          iPageHeaderHeight=FPageHeaderHeight+FTitleSpace;
       }
       if(FPrintFooter)
       {
       if(FPageFooter->LeftText->Text!=""||FPageFooter->CenterText->Text!=""||FPageFooter->RightText->Text!="")
          iPageFooterHeight=FPageFooterHeight;
       }
       int FixedRowsHeight=0;
       for (int r=0;r<FRoomGrid->FixedRows;r++)
            FixedRowsHeight+=((FRoomGrid->RowHeights[r]) * FSize / 100);
       int TruePageHeight = (FPageHeight - FTopMargin - FBottomMargin-iPageHeaderHeight-iPageFooterHeight-3*FTitleSpace)
                           * GridYPixelInch * 0.03937-(FixedRowsHeight+GetTitleHeight(dc))* FSize / 100;
       double thispageleft = 0;
       int thispagetop=0;
       if(FBeforeGridText->Text!="")
          thispagetop+= (FBeforeGridText->Count+1)*TextHeight(dc,"文");
       ReleaseDC(FRoomGrid->Handle, dc);
       for(int i = 0; i < FRoomGrid->ColCount; i++)
       {
             double ColWidth = double(FRoomGrid->ColWidths[i]) * double(FSize) / double(100);
             if(thispageleft + ColWidth <= TruePageWidth)
             {
                thispageleft += ColWidth;
             }else
             {
                cp++;
                if(cp >= 200)
                   break;
                i--;
                XPageSets[cp] = i;
                thispageleft = 0;
             }
       }
       if(XPageSets[cp] != FRoomGrid->ColCount-1)
       {
          cp++;
          XPageSets[cp] = FRoomGrid->ColCount - 1;
       }
       int TXPageCount = cp;
    //----------------------------------------------------------
       cp = 0;
       YPageSets[cp] = FRoomGrid->FixedRows-1;
//       int thispagetop = 0;
       for(int i = FRoomGrid->FixedRows; i < FRoomGrid->RowCount; i++)
       {
          int RowHeight = (FRoomGrid->RowHeights[i]) * FSize / 100;
          if(thispagetop + RowHeight < TruePageHeight)
          {
             thispagetop += RowHeight;
          }else
          {
             cp++;
             if(cp >= 10000)
                break;
             YPageSets[cp] = i-1;
             thispagetop = FPageHeight * 1 / 10;
          }
       }
       if(YPageSets[cp] != FRoomGrid->RowCount-1)
       {
          cp++;
          YPageSets[cp] = FRoomGrid->RowCount - 1;
       }
       TYPageCount = cp;
    //-----------------------------------------------------------
       FPageCount = TXPageCount*TYPageCount;
       if(FPages)
          free(FPages);
       FPages = (PrintPage*)malloc(sizeof(PrintPage)*FPageCount);
       if(FPages == NULL)
          throw Exception("Windows不能分配足够的内存供使用");
       cp = 0;
       for(int i = 0; i < TYPageCount; i++)
       {
          for(int j = 0; j < TXPageCount; j++)
          {
             FPages[cp].Left = XPageSets[j]+1;
             FPages[cp].Right = XPageSets[j+1];
             FPages[cp].Top = YPageSets[i]+1;
             FPages[cp].Bottom = YPageSets[i+1];
             FPages[cp].Adjust = true;
             cp++;
          }
             FPages[cp-1].Adjust = false;          
       }
   }
}
void __fastcall TGridReport::PageSet(bool AutoPrint, bool AutoPreview)
{
    throw Exception("错误，未实现！");
/*   try{
      frmGridPageSet = new TfrmGridPageSet(Application, this);
      frmGridPageSet->ShowModal();
      BuildPages();
   }__finally
   {
      delete frmGridPageSet;
   }
*/
}
void __fastcall TGridReport::Print()
{
   BuildPages();
   if(FPageCount < 1)
      return;
   HANDLE PrinterHandle;
   HDC PrinterDC;
//   int e;
//   int Copies;
   int From;
   int To;
//start print
   try{
      TPrintDialog* pd = new TPrintDialog(this);
      pd->Options.Clear();
      pd->Options << poPageNums;
      pd->FromPage = 1;
      pd->MinPage = 1;
      pd->ToPage = FPageCount;
      pd->MaxPage = FPageCount;
      if(!pd->Execute())
         return;
      Printers::Printer()->Copies = pd->Copies;
      Printers::Printer()->Title = FTitle;
      From = pd->FromPage;
      To = pd->ToPage;
      Printers::Printer()->Orientation = FOrientation;
      if(FPageCount > 0)
         Printers::Printer()->BeginDoc();
      PrinterDC = Printers::Printer()->Canvas->Handle;
      delete pd;
      if(PrinterDC == NULL)
		 throw Exception("打印机初始化出错" + IntToStr(int(GetLastError())));

//start document
      DOCINFO info;
      memset(&info, 0, sizeof(DOCINFO));
      info.cbSize = sizeof(DOCINFO);
	  info.lpszDocName=FTitle.c_str();
      info.lpszOutput = NULL;
      info.lpszDatatype = NULL;
	  info.fwType = 0;

      FDrawSize = 1;
      PrintEnvir APrintEnvir;
      try{//print pages
         HDC tdc = GetDC(FGrid != NULL ? FGrid->Handle : (FRoomGrid != NULL ? FRoomGrid->Handle : NULL));
         APrintEnvir.GridXPixelInch = GetDeviceCaps(tdc, LOGPIXELSX);
         APrintEnvir.GridYPixelInch = GetDeviceCaps(tdc, LOGPIXELSY);
         ReleaseDC(FGrid != NULL ? FGrid->Handle : (FRoomGrid != NULL ? FRoomGrid->Handle : NULL), tdc);
         APrintEnvir.DrawXPixelInch = GetDeviceCaps(PrinterDC, LOGPIXELSX);
         APrintEnvir.DrawYPixelInch = GetDeviceCaps(PrinterDC, LOGPIXELSY);
         APrintEnvir.PhysicalOffsetX = GetDeviceCaps(PrinterDC, PHYSICALOFFSETX);
         APrintEnvir.PhysicalOffsetY = GetDeviceCaps(PrinterDC, PHYSICALOFFSETY);
         APrintEnvir.DrawSize = FDrawSize;
         APrintEnvir.Size = FSize;
/*         SetMapMode(PrinterDC, MM_ANISOTROPIC);
         ScaleViewportExtEx(PrinterDC,
                           GetDeviceCaps(PrinterDC, LOGPIXELSX),
                           GridXPixelInch,
                           GetDeviceCaps(PrinterDC, LOGPIXELSY),
                           GridYPixelInch,
                           NULL);*/
         Printing = true;
         for(int i = From-1; i < To;)
         {
            DrawAPage(PrinterDC, APrintEnvir, &FPages[i], i+1);
            i++;
            if(i < To)
               Printers::Printer()->NewPage();
         }
      }catch(...)
      {
         AbortDoc(PrinterDC);
         throw Exception("打印失败！");
      }
      Printers::Printer()->EndDoc();
      //EndDoc(PrinterDC);
   }__finally
   {//clear
      SelectObject(PrinterDC, goFont);
      DeleteObject(hFont);
   }
}
void __fastcall TGridReport::Preview(TReportView* AView)
{
   if(FGrid == NULL && FRoomGrid == NULL)
      throw Exception("GridReport必须设置Grid");
   if(AView)
   {
      BuildPages();
      AView->Page = 0;
   }else
   {
      TForm* pForm = new TForm(this);
      try{
//         TSD
      }__finally
      {
         delete pForm;
      }
   }
}
void __fastcall TGridReport::PaintAPage(HDC dc, int No, double AZoom)
{
   Printing = false;
   PrintEnvir APrintEnvir;
   if(FPageCount > 0 && No >=0 && No < FPageCount)
   {
      HDC tdc = GetDC(FGrid != NULL ? FGrid->Handle : (FRoomGrid != NULL ? FRoomGrid->Handle : NULL));
      APrintEnvir.GridXPixelInch = GetDeviceCaps(tdc, LOGPIXELSX);
      APrintEnvir.GridYPixelInch = GetDeviceCaps(tdc, LOGPIXELSY);
      ReleaseDC(FGrid != NULL ? FGrid->Handle : (FRoomGrid != NULL ? FRoomGrid->Handle : NULL), tdc);
      APrintEnvir.DrawXPixelInch = GetDeviceCaps(dc, LOGPIXELSX);
      APrintEnvir.DrawYPixelInch = GetDeviceCaps(dc, LOGPIXELSY);
      APrintEnvir.PhysicalOffsetX = 0;
      APrintEnvir.PhysicalOffsetY = 0;
      APrintEnvir.DrawSize = AZoom;
      APrintEnvir.Size = FSize;
      DrawAPage(dc, APrintEnvir, &FPages[No], No+1);
   }
}
//---------------------------------------------------------------------------
void __fastcall TGridReport::Notification(TComponent* AComponent, TOperation Operation)
{
 TComponent::Notification(AComponent,Operation);
  if (Operation == opRemove)
  {
     if(AComponent == FGrid)
         FGrid=NULL;
     else
       if(AComponent == FRoomGrid)
			FRoomGrid=NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TGridReport::SetGrid(TZGrid*AGrid)
{
  if(FGrid!=AGrid)
  {
   if (FGrid!=NULL)
	   FGrid->RemoveFreeNotification(this);
   FGrid = AGrid;
   if(FGrid!=NULL)
	   FGrid->FreeNotification(this);
   if (FRoomGrid!=NULL)
	   FRoomGrid->RemoveFreeNotification(this);
   FRoomGrid = NULL;
   }
}
void __fastcall TGridReport::SetHouseGrid(TRoomGrid*AGrid)
{
   if(FRoomGrid!=AGrid)
   {
	if(FRoomGrid!=NULL)
	  FRoomGrid->RemoveFreeNotification(this);
	FRoomGrid = AGrid;
	if(FRoomGrid!=NULL)
	   FRoomGrid->FreeNotification(this);
   if (FGrid!=NULL)
	   FGrid->RemoveFreeNotification(this);
	FGrid = NULL;
   }
}
void __fastcall TGridReport::SetTitleFont(TFont* AFont)
{
   FTitleFont->Assign(AFont);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TReportView::TReportView(TComponent* Owner)
        : TWinControl(Owner)
{
    Color = clWhite;
    FZoom = 4;
    Width = 210;
    Height = 297;
}
//---------------------------------------------------------------------------
void __fastcall TReportView::WMPaint(Messages::TWMPaint &Message)
{
    TWinControl::Dispatch(&Message);
    if(FGridReport)
    {
       HDC dc = GetDC(Handle);
       FGridReport->PaintAPage(dc, FPage, ShowSizes[FZoom]);
       ReleaseDC(Handle, dc);
    }
}
//---------------------------------------------------------------------------
void __fastcall TReportView::SetZoom(int AZoom)
{
/*    int VPos, HPos, VMax, HMax, bkZoom;
    bkZoom = FZoom;
    if(Parent->InheritsFrom(__classid(TScrollingWinControl)))
    {
        VPos = ((TScrollingWinControl*)(Parent))->VertScrollBar->Position;
        HPos = ((TScrollingWinControl*)(Parent))->HorzScrollBar->Position;
        VMax = ((TScrollingWinControl*)(Parent))->VertScrollBar->Range;
        HMax = ((TScrollingWinControl*)(Parent))->HorzScrollBar->Range;
    }else
    {
        SCROLLINFO ScrollInfo;
        GetScrollInfo(Parent->Handle, SB_VERT, &ScrollInfo);
        VPos = ScrollInfo.nPos;
        VMax = ScrollInfo.nMax;
        GetScrollInfo(Parent->Handle, SB_HORZ, &ScrollInfo);
        HPos = ScrollInfo.nPos;
        HMax = ScrollInfo.nMax;
    }*/
    if(AZoom >= 0 && AZoom <= 9)
    {
       FZoom = AZoom;
       if(FGridReport)
       {
          HDC tdc = GetDC(Handle);
          Width = FGridReport->PageWidth *
                  GetDeviceCaps(tdc, LOGPIXELSX)
                  * 0.03937 * ShowSizes[FZoom];
          Height = FGridReport->PageHeight *
                  GetDeviceCaps(tdc, LOGPIXELSY)
                  * 0.03937 * ShowSizes[FZoom];
          ReleaseDC(Handle, tdc);
       }
       if(Height > Parent->Height)
       {
           Top = 0;
/*           if(bkZoom < FZoom)
              Top = -VPos;
           else
           {
              Top = -VPos + (Parent->ClientHeight - Height);
           }*/
       }else
       {
           switch(FVAlign)
           {
              case rvpaVMid:
                 Top = (Parent->Height - Height) / 2;
                 break;
              case rvpaTop:
                 Top = 0;
                 break;
              case rvpaBottom:
                 Top = Parent->Height - Height;
                 break;
           }
       }
       if(Width > Parent->ClientWidth)
           Left = 0;
       else
       {
           switch(FHAlign)
           {
              case rvpaHMid:
                 Left = (Parent->ClientWidth - Width) / 2;
                 break;
              case rvpaLeft:
                 Left = 0;
                 break;
              case rvpaRight:
                 Left = Parent->ClientWidth - Width;
                 break;
           }
       }
    }
}
//---------------------------------------------------------------------------
void __fastcall TReportView::SetPage(int APage)
{
    if(FGridReport)
    if(APage >= 0 && APage < FGridReport->PageCount)
    {
       FPage = APage;
//       Repaint();
        Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TReportView::SetHAlign(TRptViewPageHAlign Value)
{
    FHAlign = Value;
    SetZoom(FZoom);
}
//---------------------------------------------------------------------------
void __fastcall TReportView::SetVAlign(TRptViewPageVAlign Value)
{
    FVAlign = Value;
    SetZoom(FZoom);
}
//---------------------------------------------------------------------------
void TReportView::First()
{
    Page = 0;
}
//---------------------------------------------------------------------------
void TReportView::Prior()
{
    Page--;
}
//---------------------------------------------------------------------------
void TReportView::Next()
{
    Page++;
}
//---------------------------------------------------------------------------
void TReportView::Last()
{
    if(FGridReport)
       Page = FGridReport->PageCount - 1;
}
//---------------------------------------------------------------------------
void TReportView::Print()
{
    if(FGridReport)
       FGridReport->Print();
}
//---------------------------------------------------------------------------
void TReportView::ZoomIn()
{
    Zoom++;
}
//---------------------------------------------------------------------------
void TReportView::ZoomOut()
{
    Zoom--;
}
//---------------------------------------------------------------------------
void TReportView::View(TGridReport* AReport)
{
    if(AReport)
    {
       FGridReport = AReport;
       AReport->Preview(this);
       Zoom = Zoom;
	}else
	{
	   throw Exception("GridReport不能为空");
	}
}



void __fastcall TPageColontitle::Assign(TPersistent * Source)
{
  TPageColontitle *sPageColontitls=dynamic_cast<TPageColontitle*>(Source);
   if(sPageColontitls!=NULL)
   {
    LeftText->Assign(sPageColontitls->LeftText);
    CenterText->Assign(sPageColontitls->CenterText);
    RightText->Assign(sPageColontitls->RightText);
    Font->Assign(sPageColontitls->Font);
    LineType = sPageColontitls->LineType;
   }
  else TPersistent:Assign(Source);

}

__fastcall TPageColontitle::TPageColontitle()
           :TPersistent()
{
  FFont = new TFont();
  FFont->Charset= GB2312_CHARSET;
  FFont->Name="宋体";
  FFont->Size=9;
  FCenterText =new TStringList();
  FLeftText =new TStringList();
  FRightText =new  TStringList();

}

__fastcall TPageColontitle::~TPageColontitle()
{
  delete FFont;
  delete FCenterText;
  delete FLeftText;
  delete FRightText;
}

void __fastcall TPageColontitle::SetCenterText(TStrings* value)
{
       FCenterText->Assign(value);
}

void __fastcall TPageColontitle::SetFont(TFont* value)
{
       FFont ->Assign(value);
}

void __fastcall TPageColontitle::SetLeftText(TStrings* value)
{
                FLeftText ->Assign(value);
}

void __fastcall TPageColontitle::SetRightText(TStrings* value)
{
       FRightText ->Assign(value);
}

void __fastcall TPageColontitle::SetLineType(TPageColontitleLineType value)
{
        if(FLineType != value) {
                FLineType = value;
        }
}

void __fastcall TGridReport::SetAfterGridText(TStrings* value)
{
    AfterGridText->Assign(value);
//  TStringStream* Stream=new TStringStream("");
//  try
//  {
//    value->SaveToStream(Stream);
//    Stream->Position = 0;
//    AfterGridText->LoadFromStream(Stream);
//   }
//  __finally
//  {
//    delete Stream;
//   }
}
TStrings* __fastcall TGridReport::GetAfterGridText()
{
//  if (FAfterGridText==NULL)
//     FAfterGridText =new  TRichEditStrings();
    return FAfterGridText;
}

void __fastcall TGridReport::SetBeforeGridText(TStrings* value)
{
   BeforeGridText->Assign(value);
//  TStringStream* Stream=new TStringStream("");
//  try
//  {
//    value->SaveToStream(Stream);
//    Stream->Position = 0;
//    BeforeGridText->LoadFromStream(Stream);
//   }
//  __finally
//  {
//    delete Stream;
//   }
}
TStrings* __fastcall TGridReport::GetBeforeGridText()
{
//        if(FBeforeGridText==NULL)
//          FBeforeGridText=new TRichEditStrings();
        return FBeforeGridText;
}

void __fastcall TGridReport::SetPageFooter(TPageColontitle* value)
{
           FPageFooter->Assign(value);
}

void __fastcall TGridReport::SetPageHeader(TPageColontitle* value)
{
           FPageHeader->Assign(value);
}
/*
int __fastcall TGridReport::DrawRichText(HDC dc, bool CalcInfoMode, TRichEditStrings* Strings,PrintEnvir&Envir,int &PrintTop)
{
    TFormatRange Range;
    int LastChar, MaxLen, LogX, LogY;
    TRect SaveRect;
    int RangeMode;
    int PrintOff=PrintTop;
    if (CalcInfoMode) RangeMode = 0;
      else RangeMode = 1;
      Range.hdc = dc;
      Range.hdcTarget = 0; //hdc;
      LogX = GetDeviceCaps(FGrid->Canvas->Handle, LOGPIXELSX);
      LogY = GetDeviceCaps(FGrid->Canvas->Handle, LOGPIXELSY);
      if (IsRectEmpty(&(Strings->RichEdit->PageRect)))
      {
//        SaveRect = ScaleRect(PrintRec, 1440, 1440, LogX, LogY);
      }
      else
      {
        Range.rc.left = Strings->RichEdit->PageRect.Left * 1440 / LogX;
        Range.rc.top = Strings->RichEdit->PageRect.Top * 1440 / LogY;
        Range.rc.right = Strings->RichEdit->PageRect.Right * 1440 / LogX;
        Range.rc.bottom = Strings->RichEdit->PageRect.Bottom * 1440 / LogY;
      }
      LastChar = 0;
      MaxLen = Strings->RichEdit->GetTextLen();
      Range.chrg.cpMax = -1;
      SendMessage(Strings->RichEdit->Handle, EM_FORMATRANGE, 0, 0); // flush buffer
      try
      {
        do{
          Range.rc = SaveRect;
          Range.rc.top+= (PrintOff * 1440 / LogY);
          Range.rcPage = Range.rc;
          Range.chrg.cpMin = LastChar;
          Range.hdc = dc; // Canvas.Handle;
          Range.hdcTarget = dc; //hdc;
          LastChar = SendMessage(Strings->RichEdit->Handle, EM_FORMATRANGE, RangeMode, int(&Range));
          if (LastChar == 0)
              break;
          Range.rc = ScaleRect(Range.rc, LogX, LogY, 1440, 1440);
          PrintOff= Range.rc.bottom - Range.rc.top;
          if ((LastChar < MaxLen) && (LastChar != -1))
          {
//            PrintPageColontitle(TitleRect,True,False);
//            PrintPageColontitle(FooterRect,False,False);
//            NewPage;
//            VPrinter_NewPage;
//            PrintTop = 0;
          }
        }while ((LastChar >= MaxLen) || (LastChar == -1));
      }
      __finally
      {
        SendMessage(Strings->RichEdit->Handle, EM_FORMATRANGE, 0, 0); // flush buffer
      }

}
*/
