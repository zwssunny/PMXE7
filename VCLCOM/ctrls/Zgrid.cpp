//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Zgrid.h"
#include "zMonthCalendar.h"
//#include "zDateEdit.h"
#include "CopyRight.h"
#include <Registry.hpp>
#pragma package(smart_init)
#pragma resource "ZVCLSR.RES"
using namespace Vclcomfunc;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
//---------------------------------------------------------------------------
namespace Zgrid
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZGrid)};
     RegisterComponents("ZAdditional", classes, 0);
  }
}
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TZGrid *)
{
  new TZGrid(NULL);
}
const int ExpandInc = 20;
const int ExpandSize = 20;
const int ExpandColNumber = 17705;
const int RowIndexColNumber = 17706;
const int ExpandMarkColNumber = 17707;
const int HasFillColNumber = 17708;
const int RowStateNumber = 17709;//行状态
void __fastcall TZGrid::WriteTextEh(HDC dc, TRect ARect, bool FilledRect,
	 String Text, TAlignment Alignment, TTextLayout Layout, bool
	MultyL, bool EndEllipsis, int LeftMarg, int RightMarg, bool ARightToLeftAlignment, bool
	ARightToLeftReading)
{
  int AlignFlags[3]={DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX,DT_RIGHT | DT_EXPANDTABS | DT_NOPREFIX,
    DT_CENTER | DT_EXPANDTABS | DT_NOPREFIX};
  int RTL[2]= {0, DT_RTLREADING};
  int opt;

  TRect rect1;
  int txth, DrawFlag;
  TDrawTextParams lpDTP;
  if (ARightToLeftAlignment)
  {
    ChangeBiDiModeAlignment(Alignment);
    opt = LeftMarg;
    LeftMarg = RightMarg;
    RightMarg = opt;
  }
    if (FilledRect) FillRect(dc,&ARect,0);

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
    RichEdit->Width=rect1.Width();
    RichEdit->Height=rect1.Height();
//    SendMessage(RichEdit->Handle, EM_FORMATRANGE, 0, 0);
	RichEdit->Text=Text;
	DrawTextEx(dc, RichEdit->Text.c_str(), RichEdit->Text.Length(), &rect1, DrawFlag, &lpDTP);

   ::SelectClipRgn(dc,NULL);
   ::DeleteObject(MyRgn);
}
double __fastcall GetFloatFromStr(String str)
{
  Char * ch=str.c_str();
  Char ch2[100];
  int j=0;
  bool bFirstPoint=true;
  double d=0;

  str = Trim(str);
  if(str.IsEmpty() || str == "-" || str == ".")  //空串返回0 "-"返回0 "."返回0
    return 0;
  for (int i=0;i<str.Length();i++)
  {
    if (((ch[i] == '+' || ch[i] == '-') && i == 0) ||
        (ch[i] >= '0' && ch[i] <= '9') ||
        (ch[i] == '.' && bFirstPoint)  ||
		 ch[i] == '\0')
    {
      if (ch[i] == '.')
        bFirstPoint = false;
      ch2[j]=ch[i];
      j++;
    }
  }
  if(ch2[j] != '\0')
    ch2[j] = '\0';
  try
  {
    d = StrToFloat(String(ch2));
  }
  catch(...)
  {
    throw Exception("非有效浮点数据");
  }
  return d;
}
class TTitleMenu : public TObject
{
private:
    TZGrid*    PopupGrid;
    TPopupMenu* PopupMenu;
    TImageList* Images;

    void __fastcall OnHideColumn(System::TObject* Sender)
    {
        PopupGrid->Columns->Items[PopupMenu->Tag]->HideColWidth = PopupGrid->ColWidths[PopupMenu->Tag];
        PopupGrid->ColWidths[PopupMenu->Tag] = -1;
    }
    //---------------------------------------------------------------------------
    void __fastcall OnShowAllColumn(System::TObject* Sender)
    {
        for(int i = 0; i < PopupGrid->Columns->Count; i++)
        {
            if(PopupGrid->Columns->Items[i]->ColumnVisible && PopupGrid->ColWidths[i] < 0)
            {
                PopupGrid->ColWidths[i] = PopupGrid->Columns->Items[i]->HideColWidth;
            }
        }
        int FixWidth(0);
        for(int i = 0; i <= PopupGrid->FixedCols; i++)
        {
            FixWidth += PopupGrid->ColWidths[i];
            if(FixWidth >= PopupGrid->Width)
            {
                PopupGrid->FixedCols = i;
                return;
            }
        }
    }
    //---------------------------------------------------------------------------
    void __fastcall OnSetFixedColumn(System::TObject* Sender)
    {
        if(PopupGrid->FixedCols-1 == PopupMenu->Tag)
        {
            PopupGrid->FixedCols = 0;
        }else
        {
            if(PopupMenu->Tag+1 < PopupGrid->ColCount)
            {
                PopupGrid->FixedCols = PopupMenu->Tag+1;
                PopupGrid->HideEditor();
            }
        }
    }
    void __fastcall OnSetDefaultWidth(System::TObject* Sender)
    {
      if(PopupGrid!=NULL)
        PopupGrid->DeleteProperty();
    }

	TColor FHiliteColor;
	TColor FBorderColor;
	TColor FIconBarColor;
	TColor FMenuColor;
	TColor FMenuBorderColor;

    void __fastcall	MeasureMenuItem(TObject *Sender, TCanvas *ACanvas,
          int &Width, int &Height)
    {
        TMenuItem* Item	= dynamic_cast<TMenuItem*>(Sender);
		Width =	30 + ACanvas->TextWidth(Item->Caption) + 10;
        int	ExtraWidth = ACanvas->TextWidth(ShortCutToText(Item->ShortCut));
        if (ExtraWidth > 0)
            Width += 10	+ ExtraWidth;
		Height = 22;
    }

    void __fastcall	DrawMenuItem(TObject *Sender, TCanvas *ACanvas,
        const TRect &ARect, TOwnerDrawState State)
    {
        TMenuItem* Item	= dynamic_cast<TMenuItem*>(Sender);
		Graphics::TBitmap* MemBitmap = new Graphics::TBitmap;
        MemBitmap->Width = ARect.Width();
        MemBitmap->Height =	ARect.Height();
        TCanvas* DrawCanvas	= MemBitmap->Canvas;
        ::SetViewportOrgEx(DrawCanvas->Handle, -ARect.left,	-ARect.top,	NULL);
        DrawCanvas->Font = ACanvas->Font;

        // Draw	Background
        if (State.Contains(odSelected) && !State.Contains(odDisabled))
        {
            DrawCanvas->Pen->Color = FBorderColor;
            DrawCanvas->Brush->Color = FHiliteColor;
            DrawCanvas->Rectangle(ARect);
        }
        else
        {
            DrawCanvas->Brush->Color = FMenuColor;
            DrawCanvas->FillRect(ARect);
            DrawCanvas->Brush->Color = FIconBarColor;
            TRect rc = ARect;
            rc.right = rc.left + 22;
            DrawCanvas->FillRect(rc);
        }

        // Draw	Text
        TRect TextRect = ARect;
        TextRect.left += 30;
        TextRect.right -= 20;
        DrawCanvas->Font->Color	= State.Contains(odDisabled) ? clGray :	clBlack;
		::SetBkMode(DrawCanvas->Handle,	TRANSPARENT);
		::DrawText(DrawCanvas->Handle, Item->Caption.c_str(), Item->Caption.Length(),
			&TextRect, DT_LEFT | DT_VCENTER	| DT_SINGLELINE);
		if (Item->ShortCut != 0)
        {
            // Draw	ShortCut
			String ShortCut	= ShortCutToText(Item->ShortCut);
			::DrawText(DrawCanvas->Handle, ShortCut.c_str(), ShortCut.Length(),
				&TextRect, DT_RIGHT	| DT_VCENTER | DT_SINGLELINE);
		}

        // Draw	Icon
		if (Item->ImageIndex >=	0)
        {
			TCustomImageList* ImageList	= Item->GetImageList();
            TRect IconRect = ARect;
            IconRect.right = IconRect.left + 21;
            ::InflateRect(&IconRect, 0,	-1);
            if (ImageList != NULL)
            {
    /*			if (State.Contains(odDisabled))
                {
                    DrawGrayedBitmap(DrawCanvas, IconRect.left + 2,	IconRect.top + 2,
                        ImageList, Item->ImageIndex, FIconBarColor);
                }
				else*/
                {
                    if (State.Contains(odChecked))
                    {
                        DrawCanvas->Pen->Color = FBorderColor;
                        DrawCanvas->Brush->Color = FHiliteColor;
                        DrawCanvas->Rectangle(IconRect);
                        ImageList->Draw(DrawCanvas,	IconRect.left +	2, IconRect.top	+ 2,
                            Item->ImageIndex, true);
                    }
                    else if	(State.Contains(odSelected))
                    {
                        DrawGrayedBitmap(DrawCanvas, IconRect.left + 3,	IconRect.top + 3,
                            ImageList, Item->ImageIndex, FHiliteColor);
                        ImageList->Draw(DrawCanvas,	IconRect.left +	1, IconRect.top	+ 1,
                            Item->ImageIndex, true);
                    }
                    else
                    {
                        ImageList->Draw(DrawCanvas,	IconRect.left +	2, IconRect.top	+ 2,
                            Item->ImageIndex, true);
                    }
                }
            }
        }
        ::SetViewportOrgEx(DrawCanvas->Handle, 0, 0, NULL);
        ::BitBlt(ACanvas->Handle, ARect.left, ARect.top, ARect.Width(),	ARect.Height(),
            DrawCanvas->Handle,	0, 0, SRCCOPY);
        delete MemBitmap;
    }
    void __fastcall	DrawGrayedBitmap(TCanvas *ACanvas, int x,	int	y,
        TCustomImageList *ImageList, int Index,	TColor clBack)
    {
        Graphics::TBitmap* Bmp1	= new Graphics::TBitmap;
        Bmp1->Width	= 16;
        Bmp1->Height = 16;
        Bmp1->Canvas->Brush->Color = clWhite;
        Bmp1->Canvas->FillRect(Rect(0, 0, 16, 16));
        ImageList->Draw(Bmp1->Canvas, 0, 0,	Index, true);

        Graphics::TBitmap* Bmp2	= new Graphics::TBitmap;
        Bmp2->Width	= 16;
        Bmp2->Height = 16;
        Bmp2->Canvas->Brush->Color = clBlack;
        Bmp2->Canvas->FillRect(Rect(0, 0, 16, 16));
        ImageList->Draw(Bmp2->Canvas, 0, 0,	Index, true);

        ::BitBlt(Bmp1->Canvas->Handle, 0, 0, 16, 16, Bmp2->Canvas->Handle,
            0, 0, SRCINVERT);

        TColor clShade = ShadeColor(40,	clBack);
        for	(int i = 0;	i <	16;	i++)
        {
            for	(int j = 0;	j <	16;	j++)
            {
                COLORREF cr	= ::GetPixel(Bmp1->Canvas->Handle, i, j);
                if (cr == clWhite)
                    ::SetPixel(Bmp1->Canvas->Handle, i,	j, clBack);
                else
                    ::SetPixel(Bmp1->Canvas->Handle, i,	j, clShade);
            }
        }

        ::BitBlt(ACanvas->Handle, x, y,	16,	16,
        Bmp1->Canvas->Handle, 0, 0,	SRCCOPY);
        delete Bmp2;
        delete Bmp1;
    }
    TColor __fastcall ShadeColor(int percent, TColor color) const
    {
        return TColor(RGB(MulDiv(GetRValue(color), 100 - percent, 100),
                          MulDiv(GetGValue(color), 100 - percent, 100),
                          MulDiv(GetBValue(color), 100 - percent, 100)));
    }

public:
    TTitleMenu()
    {
        FHiliteColor = TColor(RGB(182, 189,	210));
        FBorderColor = TColor(RGB(10, 36, 106));
        FIconBarColor =	TColor(RGB(219,	216, 209));
        FMenuColor = TColor(RGB(249, 248, 247));
        FMenuBorderColor = TColor(RGB(102, 102,	102));

        PopupMenu = new TPopupMenu(Application);
        Images = new TImageList(Application);
        PopupMenu->Images = Images;
        Images->ResourceLoad(rtBitmap, "GRIDPOPUPMENU", (TColor)RGB(255,0,255));
        PopupMenu->OwnerDraw = true;

        TMenuItem* mi = new TMenuItem(PopupMenu);
        PopupMenu->Items->Add(mi);
        mi->Caption = "隐藏此列(&H)";
        mi->OnClick = OnHideColumn;
        mi->OnAdvancedDrawItem = DrawMenuItem;
        mi->OnMeasureItem = MeasureMenuItem;
        mi->ImageIndex = 0;

        mi = new TMenuItem(PopupMenu);
        PopupMenu->Items->Add(mi);
        mi->Caption = "显示所有列(&A)";
        mi->OnClick = OnShowAllColumn;
        mi->OnAdvancedDrawItem = DrawMenuItem;
        mi->OnMeasureItem = MeasureMenuItem;
        mi->ImageIndex = 1;

        mi = new TMenuItem(PopupMenu);
        PopupMenu->Items->Add(mi);
        mi->Caption = "设置固定列";
        mi->OnClick = OnSetFixedColumn;
        mi->OnAdvancedDrawItem = DrawMenuItem;
        mi->OnMeasureItem = MeasureMenuItem;
        mi->ImageIndex = 2;

        mi = new TMenuItem(PopupMenu);
		PopupMenu->Items->Add(mi);
		mi->Caption = "还原列表的默认列宽";
        mi->OnClick = OnSetDefaultWidth;
        mi->OnAdvancedDrawItem = DrawMenuItem;
        mi->OnMeasureItem = MeasureMenuItem;
        mi->ImageIndex = 3;
    }
    __fastcall ~TTitleMenu()
    {
        delete PopupMenu;
        delete Images;
    }
    static void Popup(TZGrid* AGrid, int ACol, int x, int y)
    {
        static TTitleMenu* TitleMenu = new TTitleMenu();
        TitleMenu->PopupMenu->Tag = ACol;
        TitleMenu->PopupGrid = AGrid;

        if(ACol >= 0 && ACol < AGrid->ColCount)
        {
            TitleMenu->PopupMenu->Items->Items[0]->Enabled = true;
            TitleMenu->PopupMenu->Items->Items[2]->Enabled = true;
            if(AGrid->FixedCols-1 == ACol)
            {
                TitleMenu->PopupMenu->Items->Items[2]->Caption = "取消固定列(&F)";
            }else
            {
                TitleMenu->PopupMenu->Items->Items[2]->Caption = "设置固定列(&F)";
            }
            if(TitleMenu->PopupMenu->Tag+1 >= AGrid->ColCount)
            {
                TitleMenu->PopupMenu->Items->Items[2]->Enabled = false;
            }
        }else
        {
            TitleMenu->PopupMenu->Items->Items[0]->Enabled = false;
            TitleMenu->PopupMenu->Items->Items[2]->Enabled = false;
        }
        int FixWidth(0);
        for(int i = 0; i <= ACol; i++)
        {
            FixWidth += AGrid->ColWidths[i];
        }
        if(FixWidth >= AGrid->Width)
        {
            TitleMenu->PopupMenu->Items->Items[2]->Enabled = false;
        }
        TitleMenu->PopupMenu->Popup(x, y);
    }
};
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetFullFill(bool value)
{
    FFullFill = value;
    if(FFullFill)
    {
      TBYStringGrid::Options>>goRangeSelect;
      TBYStringGrid::Ctl3D = false;
    }
    Paint();
}

__fastcall TZGrid::TZGrid(TComponent* Owner)
  : TBYStringGrid(Owner)
{
    checkCopyRight();
	FCurrRowColor = (TColor)0x0039E300;
	FReadOnly = true;
    FHighLight = false;
	FSelectColor = clGreen;
	FEvenGridColor = clWhite;
	FOddGridColor = clSkyBlue;
    FDriveBySelectCell = 0;
    DefaultDrawing = false;
    TBYStringGrid::RowCount = 5;
    Font->Charset= GB2312_CHARSET;
    Font->Name="宋体";
    Font->Size=9;
    FZColumns = new TZColumns(this,__classid(TZColumn));
    FRowFonts = new TRowFonts(this,__classid(TRowFontItem));    
    TBYStringGrid::DefaultRowHeight = 18;
	TBYStringGrid::FixedColor = clBlue;
    FFooterColor =FixedColor;
    FWarningColor = clBlack;
	FFixedRows = 1;
	FFixedCols = 1;
	ColCount = 5;
	TBYStringGrid::Options.Clear();
	TBYStringGrid::Options<<goFixedVertLine<<goFixedHorzLine<<goVertLine<<goRowSizing<<goColSizing;
	FFullFill = true;
	FAllowSort = false;
	TBYStringGrid::Options>>goRangeSelect;
	DoubleBuffered = true;
	FExpandFoldColIndex = -1;
	RichEdit=new TRichEdit(this);
	RichEdit->Visible=false;
	RichEdit->Top=-200;
	RichEdit->Left=-200;
	RichEdit->PlainText=true;
	RichEdit->Parent=this;
}
__fastcall TZGrid::~TZGrid()
{
  delete FZColumns;
  delete RichEdit;
  delete FRowFonts;
}
//---------------------------------------------------------------------------
bool __fastcall TZGrid::CanEditAcceptKey(Char Key)
{
    if(FReadOnly)
        return false;
    if(FZColumns->Count <= Col)
    {
		MessageBox(Handle,L"Please Reset property [ColCount].",L"Hint",MB_ICONWARNING);
        return false;
    }
    if(FZColumns->Items[Col]->EditType == caNone)
        return false;
/*
	if(FZColumns->Items[Col]->CharType==gtNumeric)
    {
      if((Key>='0' && Key<='9')|| Key=='-' || Key=='.' || Key=='+' || Key=='/' || Key=='*')
        return true;
      else
		return false;
	}
    else
      return true;
*/
    return true;
}
//---------------------------------------------------------------------------
TBYInplaceEdit* __fastcall TZGrid::CreateEditor(void)
{
    TZInplaceEdit *InEdit=new TZInplaceEdit(this);
    return InEdit;
}
//---------------------------------------------------------------------------
bool __fastcall TZGrid::CanEditModify(void)
{
    if(FReadOnly)
        return false;
    if(FZColumns->Count<=Col)
    {
		MessageBox(Handle, L"Please Reset property [ColCount].",L"Hint", MB_ICONWARNING);
        return false;
    }
    if(FZColumns->Items[Col]->EditType == caNone)
        return false;
    InplaceEditor->OnChange  = this->Columns->Items[Col]->OnChange;
    return TBYStringGrid::CanEditModify();
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetSelectColor(Graphics::TColor value)
{
   if(FSelectColor!=value)
   {
    FSelectColor = value;
    Invalidate();
   }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetEvenGridColor(Graphics::TColor value)
{
   if(FEvenGridColor != value)
   {
    FEvenGridColor = value;
    Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetFooterColor(TColor value)
{
        if(FFooterColor != value) {
                FFooterColor = value;
         Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetOddGridColor(Graphics::TColor value)
{
    if(FOddGridColor != value)
    {
    FOddGridColor = value;
    Invalidate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TZGrid::SetReadOnly(bool value)
{
    if(FReadOnly != value)
    {
       FReadOnly=value;
       if(!value)
          HideEditor();
       Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::EventMessage(TMessage &message)
{
    if(FOnListClick)
        FOnListClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::WMHScroll(TWMScroll &Msg)
{
   TBYStringGrid::Dispatch(&Msg);
   Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::WMVScroll(TWMScroll &Msg)
{
    TBYStringGrid::Dispatch(&Msg);
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::WMLButtonDown(TMessage &Msg)
{
    TBYStringGrid::Dispatch(&Msg);
    int MX, MY;
    MX = Msg.LParamLo;//鼠标X坐标
    MY = Msg.LParamHi;//鼠标Y坐标
    int mCol = -1;
    int tempx = 0;
    for(int i = 0; i < FixedCols; i++)
    {
         int ColWidth = ColWidths[i];
         if(tempx <= MX && tempx + ColWidth >= MX)
         {
             mCol = i;
             goto labelGetmRow;
         }
         tempx += ColWidth;
    }
    for(int i = LeftCol; i <= LeftCol + VisibleColCount; i++)
    {
         int ColWidth = ColWidths[i];
         if(tempx <= MX && tempx + ColWidth >= MX)
         {
             mCol = i;
             goto labelGetmRow;
         }
         tempx += ColWidth;
    }
labelGetmRow:
    int mRow = -1;
    int tempy = 0;
    for(int i = 0; i < FixedRows; i++)
    {
        int RowHeight = RowHeights[i] + GridLineWidth;
        if(tempy <= MY && tempy + RowHeight >= MY)
        {
            mRow = i;
            goto labelGetmRowOver;
        }
        tempy += RowHeight;
    }
    for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
    {
        int RowHeight = RowHeights[i] + GridLineWidth;
        if(tempy <= MY && tempy + RowHeight > MY)
        {
            mRow = i;
            goto labelGetmRowOver;
        }
        tempy += RowHeight;
    }
labelGetmRowOver:

    //if((mCol == FExpandFoldColIndex||IsFilled[mRow]==0)&& mRow >= FixedRows && mRow < RowCount)
    if((mCol == FExpandFoldColIndex||IsFilled[mRow]==0)&& mRow >= 0 && mRow < RowCount)
    {
        ExpandMouseDown(mCol, mRow, MX, MY, Msg);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::WMLButtonUp(TMessage &Msg)
{
   TBYStringGrid::Dispatch(&Msg);
/*
   if(!FAllowSort)
       return;
   int MX, MY;
   MX = Msg.LParamLo;//鼠标X坐标
   MY = Msg.LParamHi;//鼠标Y坐标
//   bool ControlDown = (Msg.WParam & MK_CONTROL) != 0;
//   bool ShiftDown = (Msg.WParam & MK_SHIFT) != 0;

   int mCol = -1;
   int tempx = 0;
   for(int i = 0; i < FixedCols; i++)
   {
        int ColWidth = ColWidths[i];
        if(tempx <= MX && tempx + ColWidth >= MX)
        {
            mCol = i;
            goto labelGetmRow;
        }
        tempx += ColWidth;
   }
   for(int i = LeftCol; i <= LeftCol + VisibleColCount; i++)
   {
        int ColWidth = ColWidths[i];
        if(tempx + 5 <= MX && tempx + ColWidth - 5 >= MX)
        {
            mCol = i;
            goto labelGetmRow;
        }
        tempx += ColWidth;
   }

labelGetmRow:
   int mRow = -1;
   int tempy = 0;
   for(int i = 0; i < FixedRows; i++)
   {
        int RowHeight = RowHeights[i];
        if(tempy <= MY && tempy + RowHeight >= MY)
        {
            mRow = i;
            goto labelGetmRowOver;
        }
        tempy += RowHeight;
   }
   for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
   {
        int RowHeight = RowHeights[i];
        if(tempy <= MY && tempy + RowHeight > MY)
        {
            mRow = i;
            goto labelGetmRowOver;
        }
        tempy += RowHeight;
   }
labelGetmRowOver:
   if(mCol != -1 && mRow != -1)
   {
        if(mRow >= 0 && mRow < FixedRows && mCol < Columns->Count)
        {
            TZColumn* Column = Columns->Items[mCol];
            if(Column->SortField != "")
            {
                for(int i = 0; i < Columns->Count; i++)
                {
                     if(Columns->Items[i] != Column)
                     {
                          Columns->Items[i]->ColSort = csNone;
                     }
                }
                switch(Column->ColSort)
                {
                    case csNone:
                        Column->ColSort = csAsc;
                        break;
                    case csAsc:
                        Column->ColSort = csDesc;
                        break;
                    case csDesc:
                        Column->ColSort = csAsc;
                        break;
                }
                if(FOnSort)
                    FOnSort(this, Columns->Items[mCol]);
                InvalidateCell(mCol, mRow);
            }
        }
   }
*/
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::WMLButtonDblClk(TMessage &Msg)
{
    int MX, MY;
    MX = Msg.LParamLo;//鼠标X坐标
    MY = Msg.LParamHi;//鼠标Y坐标
    int FixedHeight(0);
    for(int i = 0; i < FixedRows; i++)
    {
        FixedHeight += RowHeights[i];
    }
    if(MY <= FixedHeight)
    {
        Msg.Result = 1;
        //return;
    }
    int FixedWidth(0);
    for(int i = 0; i < FixedCols; i++)
    {
        FixedWidth += ColWidths[i];
    }
    if(MX <= FixedWidth)
    {
        Msg.Result = 1;
        //return;
    }

    if(!FAllowSort)
    {
      if(Msg.Result != 1)
         TBYStringGrid::Dispatch(&Msg);
       return;
    }
//   bool ControlDown = (Msg.WParam & MK_CONTROL) != 0;
//   bool ShiftDown = (Msg.WParam & MK_SHIFT) != 0;

   int mCol = -1;
   int tempx = 0;
   for(int i = 0; i < FixedCols; i++)
   {
        int ColWidth = ColWidths[i];
        if(tempx <= MX && tempx + ColWidth >= MX)
        {
            mCol = i;
            goto labelGetmRow;
        }
        tempx += ColWidth;
   }
   for(int i = LeftCol; i <= LeftCol + VisibleColCount; i++)
   {
        int ColWidth = ColWidths[i];
        if(tempx + 5 <= MX && tempx + ColWidth - 5 >= MX)
        {
            mCol = i;
            goto labelGetmRow;
        }
        tempx += ColWidth;
   }

labelGetmRow:
   int mRow = -1;
   int tempy = 0;
   for(int i = 0; i < FixedRows; i++)
   {
        int RowHeight = RowHeights[i];
        if(tempy <= MY && tempy + RowHeight >= MY)
        {
            mRow = i;
            goto labelGetmRowOver;
        }
        tempy += RowHeight;
   }
   for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
   {
        int RowHeight = RowHeights[i];
        if(tempy <= MY && tempy + RowHeight > MY)
        {
            mRow = i;
            goto labelGetmRowOver;
        }
        tempy += RowHeight;
   }
labelGetmRowOver:
   if(mCol != -1 && mRow != -1)
   {
        if(mRow >= 0 && mRow < FixedRows && mCol < Columns->Count)
        {
            TZColumn* Column = Columns->Items[mCol];
            if(Column->SortField != "")
            {
                for(int i = 0; i < Columns->Count; i++)
                {
                     if(Columns->Items[i] != Column)
                     {
                          Columns->Items[i]->ColSort = csNone;
                     }
                }
                switch(Column->ColSort)
                {
                    case csNone:
                        Column->ColSort = csAsc;
                        break;
                    case csAsc:
                        Column->ColSort = csDesc;
                        break;
                    case csDesc:
                        Column->ColSort = csAsc;
                        break;
                }
                if(FOnSort)
                    FOnSort(this, Columns->Items[mCol]);
                InvalidateCell(mCol, mRow);
            }
        }
   }

   if(Msg.Result != 1)
         TBYStringGrid::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::WMRButtonUp(TMessage &Msg)
{
    int MX, MY;
    MX = Msg.LParamLo;//鼠标X坐标
    MY = Msg.LParamHi;//鼠标Y坐标

    int mCol = -1;
    int tempx = 0;
    for(int i = 0; i < FixedCols; i++)
    {
         int ColWidth = ColWidths[i];
         if(tempx <= MX && tempx + ColWidth >= MX)
         {
             mCol = i;
             goto labelGetmRow;
         }
         tempx += ColWidth;
    }
    for(int i = LeftCol; i <= LeftCol + VisibleColCount; i++)
    {
         int ColWidth = ColWidths[i];
         if(tempx  <= MX && tempx + ColWidth  >= MX)
         {
             mCol = i;
             goto labelGetmRow;
         }
         tempx += ColWidth;
    }

 labelGetmRow:
    int mRow = -1;
    int tempy = 0;
    for(int i = 0; i < FixedRows; i++)
    {
         int RowHeight = RowHeights[i];
         if(tempy <= MY && tempy + RowHeight >= MY)
         {
             mRow = i;
             goto labelGetmRowOver;
         }
         tempy += RowHeight;
    }
    for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
    {
         int RowHeight = RowHeights[i];
         if(tempy <= MY && tempy + RowHeight > MY)
         {
             mRow = i;
             goto labelGetmRowOver;
         }
         tempy += RowHeight;
    }
 labelGetmRowOver:
    if(FixedRows > 0 && mRow < FixedRows && mRow != -1)
    {//右击固定列
      TTitleMenu::Popup(this, mCol, MX+ClientOrigin.x, MY+ClientOrigin.y);
    }
//    else
        TBYStringGrid::Dispatch(&Msg);

}
//---------------------------------------------------------------------------
void __fastcall TZGrid::Paint(void)
{
    TBYStringGrid::Paint();
    DrawOutGridCell();
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::DrawOutGridCell(void)
{
    TRect FRect;
    int VirtualRow,VirtualGridHeight,VirtualGridWidth;
    if(FFullFill)
    {
        if(Ctl3D)
            Ctl3D = false;
        VirtualRow = RowCount;
        VirtualGridHeight = GridHeight;
        VirtualGridWidth = GridWidth;
        //Draw Fixed Title
        if(VirtualGridWidth<Width)
        {
            FRect.Right = Width;
            FRect.Left = GridWidth;
            FRect.Top = 0;
            FRect.Bottom = CellRect(LeftCol,FixedRows-1).Bottom;
            Canvas->Brush->Color = (TColor)ColorToRGB(FixedColor);
            Canvas->FillRect(FRect);
            Canvas->Brush->Color = clBlack;
            FRect.Top = CellRect(LeftCol,FixedRows-1).Bottom;
            FRect.Bottom = FRect.Top+GridLineWidth;
            Canvas->FillRect(FRect);
        }
        //Draw Out of GridWidth
        if(VirtualGridWidth<Width && RowCount>FixedRows)
        {
            FRect.Right = Width;
            FRect.Left = GridWidth;
            for(int i=TopRow; i<TopRow+VisibleRowCount; i++)
            {
                FRect.Top = CellRect(LeftCol,i).Top;
                FRect.Bottom = CellRect(LeftCol,i).Bottom;
                if(TBYStringGrid::Options.Contains(goRowSelect))
                {
                    if(Mod(ExpandGetRowIndex(i),2)==0)
                      Canvas->Brush->Color = (TColor)ColorToRGB(FOddGridColor);
                    else
                      Canvas->Brush->Color = (TColor)ColorToRGB(FEvenGridColor);
                }
                else
                {
                    if(Mod(ExpandGetRowIndex(i),2)==0)
                        Canvas->Brush->Color = (TColor)ColorToRGB(FOddGridColor);
                    else
                        Canvas->Brush->Color = (TColor)ColorToRGB(FEvenGridColor);
                }
                Canvas->FillRect(FRect);
                if(TBYStringGrid::Options.Contains(goHorzLine))
                {
                    FRect.Top = FRect.Bottom;
                    FRect.Bottom = FRect.Top+GridLineWidth;
                    Canvas->Brush->Color = (TColor)ColorToRGB(clSilver);
                    Canvas->FillRect(FRect);
                }
            }
        }
        //Draw Out of GridHeight
        int LastRowIndex = ExpandGetRowIndex(RowCount-1);
        while(VirtualGridHeight<Height)
        {
                    for(int i=0;i<FixedCols;i++)
                    {
                            FRect.Left = CellRect(i,TopRow).Left;
                            FRect.Right = CellRect(i,TopRow).Right;
                            FRect.Top = VirtualGridHeight;
                            FRect.Bottom = VirtualGridHeight+DefaultRowHeight;
                            Canvas->Brush->Color = (TColor)ColorToRGB(FixedColor);
                            Canvas->FillRect(FRect);
                            Canvas->Brush->Color = clBlack;
                            FRect.Top = FRect.Bottom;
                            FRect.Bottom = FRect.Bottom+GridLineWidth;
                            Canvas->FillRect(FRect);
                            FRect.Top = VirtualGridHeight-GridLineWidth;
                            FRect.Left = CellRect(i,TopRow).Right;
                            FRect.Bottom = VirtualGridHeight+DefaultRowHeight;
                            FRect.Right = FRect.Left+GridLineWidth;
                            Canvas->FillRect(FRect);
                    }

                    if(FixedCols > 0)
                        FRect.Left = CellRect(FixedCols-1,TopRow).Right+1;
                    else
                        FRect.Left = 0;
                    FRect.Right = Width;
                    if(Mod(VirtualRow-(RowCount - LastRowIndex)+1,2)==0)
                        Canvas->Brush->Color = (TColor)ColorToRGB(FOddGridColor);
                    else
                        Canvas->Brush->Color = (TColor)ColorToRGB(FEvenGridColor);
                    Canvas->Brush->Style = bsSolid;
                    FRect.Top = VirtualGridHeight;
                    FRect.Bottom = VirtualGridHeight + DefaultRowHeight;
                    Canvas->FillRect(FRect);
                    if(TBYStringGrid::Options.Contains(goHorzLine))
                    {
                        FRect.Top = FRect.Bottom;
                        FRect.Bottom = FRect.Top + GridLineWidth;
                        Canvas->Brush->Color = clSilver;
                        Canvas->FillRect(FRect);
                    }
                    VirtualRow++;
                    VirtualGridHeight += DefaultRowHeight + GridLineWidth;
        }
        if(TBYStringGrid::Options.Contains(goVertLine))
        {
                    Canvas->Brush->Color = clSilver;
                    Canvas->Brush->Style = bsSolid;
                    FRect.Top=0;
                    for(int r=0;r<FixedRows;r++)
                       FRect.Top += RowHeights[r]+1;//DefaultRowHeight*FixedRows;
                    for(int i = LeftCol; i < LeftCol+VisibleColCount; i++)
                    {
                        FRect.Left = CellRect(i,0).Right;
                        FRect.Bottom = Height;
                        FRect.Right = CellRect(i, 0).Right + GridLineWidth;
                        Canvas->FillRect(FRect);
                    }
        }
    }
    if(HasFooter)
    {
      int allColWidths=0;
      for (int c=0;c<ColCount;c++)
          allColWidths+=ColWidths[c];
      if(allColWidths>ClientWidth)
      {
         FRect.Top =Height-FootHeight-GetSystemMetrics(SM_CYHSCROLL)-2*GridLineWidth;
         FRect.Bottom = Height-GetSystemMetrics(SM_CYHSCROLL)-2*GridLineWidth;
      }
      else
      {
        FRect.Top =Height-FootHeight;
        FRect.Bottom = Height-GridLineWidth;
       }
      for(int f=0;f<FixedCols;f++)
      {
          FRect.Left = CellRect(f,0).Left-GridLineWidth;
          FRect.Right = CellRect(f, 0).Right + GridLineWidth;
          Canvas->Brush->Color = FFooterColor;
          Canvas->FillRect(FRect);
          Canvas->Brush->Color = clBlack;
          Canvas->FrameRect(FRect);
          DrawFootText(f,FRect);
      }
      int i = LeftCol;
      for(; (i <= LeftCol+VisibleColCount)&&(i<ColCount); i++)
      {
          FRect.Left = CellRect(i,0).Left-GridLineWidth;
          FRect.Right = CellRect(i, 0).Right + GridLineWidth;
          Canvas->Brush->Color = FFooterColor;
          Canvas->FillRect(FRect);
          Canvas->Brush->Color = clBlack;
          Canvas->FrameRect(FRect);
          DrawFootText(i,FRect);
      }
      if( GridWidth < Width && (LeftCol+VisibleColCount>=ColCount) )
      {
         if(FullFill)
         {
          FRect.Right = Width;
          FRect.Left = GridWidth-GridLineWidth;
          Canvas->Brush->Color = FFooterColor;
          Canvas->FillRect(FRect);
          Canvas->Brush->Color = clBlack;
          Canvas->FrameRect(FRect);
         }
         else
         {
          FRect.Right = Width;
          FRect.Left = GridWidth;
          Canvas->Brush->Color = Color;
          Canvas->FillRect(FRect);
         }

      }

    }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::DrawFootText(int ColIndex, TRect ARect)
{
  int x,y;
  int FLen,FHeight;
  String DrawText=FZColumns->Items[ColIndex]->FootText;
  if (DrawText.Trim().IsEmpty())
    return;
//  TZCharType cttype=Columns->Items[ColIndex]->CharType;
//  if(Columns->Items[ColIndex]->DigLen>0&&(cttype==gtPlusFloat||cttype==gtNegativeFloat||cttype==gtFloat))
//      {
//       double sumvalue=0;
//       try
//       {
//         sumvalue=DrawText.ToDouble();
//        }
//       catch(...)
//       {
//       }
//       DrawText=Format("%."+IntToStr(Columns->Items[ColIndex]->DigLen)+"f",ARRAYOFCONST((sumvalue)));
//      }
//  FZColumns->Items[ColIndex]->FootText=DrawText;

  DrawText = FZColumns->Items[ColIndex]->FootText;
  Canvas->Font->Assign(FZColumns->Items[ColIndex]->FootFont);
  FLen = Canvas->TextWidth(DrawText);
  FHeight = Canvas->TextHeight(DrawText);
  if(FZColumns->Items[ColIndex]->ColHorAlign == haLeft)
      x = ARect.Left + GridLineWidth + 1;
  else if(FZColumns->Items[ColIndex]->ColHorAlign == haCenter)
      x =ARect.Left + (ColWidths[ColIndex] - 2*GridLineWidth - FLen) / 2 + 1;
  else
      x = ARect.Left + GridLineWidth + ColWidths[ColIndex] - FLen - 1;
  if(FZColumns->Items[ColIndex]->RowVerAlign == vaTop)
      y = ARect.Top + GridLineWidth+1;
  else if(FZColumns->Items[ColIndex]->RowVerAlign == vaMiddle)
      y = ARect.Top + (FootHeight -  FHeight)/2;
  else
      y = ARect.Top +  FootHeight- FHeight - GridLineWidth;
  Canvas->Pen->Color = clBlack;
  Canvas->Pen->Style = psSolid;
  Canvas->Pen->Mode = pmCopy;
  Canvas->Pen->Width = 1;
  Canvas->Brush->Color = FFooterColor;
  Canvas->Brush->Style = bsClear;
  Canvas->TextRect(ARect, x, y, DrawText);
  Canvas->Rectangle(ARect);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::DrawCell(int ACol, int ARow, const TRect &ARect, TBYGridDrawState AState)
{
    if(ARect.Bottom - ARect.Top < 1)
        return;

    if(ARow >= FFixedRows && ACol >= FFixedCols)
    {
        DrawCell(ACol, ARow, ARect);
    }else if(ARow < FixedRows)
    {
        DrawTopFixed(ACol, ARow, ARect);
    }else if(ACol < FixedCols)
    {
        DrawLeftFixed(ACol, ARow, ARect);
    }

    if(OnDrawCell)
        OnDrawCell(this, ACol, ARow, ARect, AState);
}
//---------------------------------------------------------------------------
void TZGrid::DrawCell(int ACol, int ARow, const TRect &ARect)
{
    int x,y;
    TRect FRect;

    String DrawText;
    bool Result = false;
    if(FOnGetCellString)
    {
        FOnGetCellString(this, ACol, ARow, DrawText, Result);
        if(!Result)
            DrawText = Cells[ACol][ARow];
    }else
        DrawText = Cells[ACol][ARow];

    Canvas->TextFlags = ETO_CLIPPED;

    TFont * AFont = RowStateFont(ARow);
    Canvas->Font->Assign(AFont);
//    if(RowState[ARow]==1)
//       Canvas->Font->Color=FWarningColor;
    if(Mod(ExpandGetRowIndex(ARow),2) == 0)
    {
          if(TBYStringGrid::Options.Contains(goRowSelect))
          {
              if(ARow == TBYStringGrid::Row)
              {
                  Canvas->Brush->Color = (TColor)ColorToRGB(FSelectColor);
                  Canvas->Font->Color = clWhite;
              }else
              {
                  Canvas->Brush->Color = (TColor)ColorToRGB(FOddGridColor);
              }
          }
          else if(ACol == TBYStringGrid::Col && ARow == TBYStringGrid::Row)
          {
              Canvas->Brush->Color = (TColor)ColorToRGB(FSelectColor);
              Canvas->Font->Color = clWhite;
          }else
          {
              if (ARow != Row)
                  Canvas->Brush->Color = (TColor)ColorToRGB(FOddGridColor);
              else
              {
                  Canvas->Brush->Color = (TColor)ColorToRGB(FCurrRowColor);
              }
          }
          Canvas->Brush->Style = bsSolid;
          FRect = ARect;
          if(!TBYStringGrid::Options.Contains(goVertLine))
          {
              FRect.Right = ARect.Right+GridLineWidth;
          }
          Canvas->FillRect(FRect);
    }else
    {
          if(TBYStringGrid::Options.Contains(goRowSelect))
          {
              if(ARow == TBYStringGrid::Row)
              {
                  Canvas->Brush->Color = (TColor)ColorToRGB(FSelectColor);
                  Canvas->Font->Color = clWhite;
              }else
              {
                  Canvas->Brush->Color = (TColor)ColorToRGB(FEvenGridColor);
              }
          }
          else if(ACol == TBYStringGrid::Col && ARow == TBYStringGrid::Row)
          {
              Canvas->Brush->Color = (TColor)ColorToRGB(FSelectColor);
              Canvas->Font->Color = clWhite;
          }else
          {
              if (ARow != Row)
                  Canvas->Brush->Color = (TColor)ColorToRGB(FEvenGridColor);
              else
              {
                  Canvas->Brush->Color = (TColor)ColorToRGB(FCurrRowColor);
              }
          }
          Canvas->Brush->Style = bsSolid;
          FRect = ARect;
          if(!TBYStringGrid::Options.Contains(goVertLine))
              FRect.Right = ARect.Right + GridLineWidth;
          Canvas->FillRect(FRect);
    }
    if(FZColumns->Count > Col)
    {
          if(FZColumns->Items[ACol]->ColHorAlign == haLeft)
              x = CalculatePos(ACol, ARow, DrawText, 1);
          else if(FZColumns->Items[ACol]->ColHorAlign == haCenter)
              x = CalculatePos(ACol, ARow, DrawText, 2);
          else
              x = CalculatePos(ACol, ARow, DrawText, 3);
          if(FZColumns->Items[ACol]->RowVerAlign == vaTop)
              y = CalculatePos(ACol, ARow, DrawText, 4);
          else if(FZColumns->Items[ACol]->RowVerAlign == vaMiddle)
              y = CalculatePos(ACol, ARow, DrawText, 5);
          else
              y = CalculatePos(ACol, ARow, DrawText, 6);
    }else
    {
          x = CalculatePos(ACol, ARow, DrawText, 1);
          y = CalculatePos(ACol, ARow, DrawText, 5);
    }
    if(ACol == FExpandFoldColIndex)
    {
        DrawExpandFoldCell(ARect, DrawText, Layer[ARow], ExpandFoldMark(ARow),y);
    }else
    {
      if(FZColumns->Items[ACol]->MultyLine)
      {
        WriteTextEh(Canvas->Handle,ARect,true,DrawText,
			FZColumns->Items[ACol]->ColHorAlign ,FZColumns->Items[ACol]->RowVerAlign,true,true);
      }
      else
        Canvas->TextRect(ARect, x, y, DrawText);
    }
}
//---------------------------------------------------------------------------
void TZGrid::DrawTopFixed(int ACol, int ARow, const TRect &ARect)
{
    int FirstCol, FirstRow, LastCol, LastRow,textFlags;
    TRect MergeRect, FRect;
    int x, y, FLen, FHeight;
    TZColumn* Column = FZColumns->Items[ACol];
    if(FZColumns->Items[ACol]->Merged)
    {
        if(ACol >= FZColumns->Items[ACol]->ColMergeOrder && ACol < FZColumns->Items[ACol]->ColMergeOrder+FZColumns->Items[ACol]->ColMergeCount
          && ARow >= FZColumns->Items[ACol]->RowMergeOrder && ARow < FZColumns->Items[ACol]->RowMergeOrder+FZColumns->Items[ACol]->RowMergeCount)
        {
            FirstCol = FZColumns->Items[ACol]->ColMergeOrder;
            FirstRow = FZColumns->Items[ACol]->RowMergeOrder;
            LastCol = FZColumns->Items[ACol]->ColMergeOrder+FZColumns->Items[ACol]->ColMergeCount-1;
            LastRow = FZColumns->Items[ACol]->RowMergeOrder+FZColumns->Items[ACol]->RowMergeCount-1;
            FRect = CellRect(FirstCol,FirstRow);
            MergeRect.Left = FRect.Left;
            MergeRect.Top = FRect.Top;
            MergeRect.Bottom = FRect.Bottom;
            FRect = CellRect(LastCol,LastRow);
			if(FRect.Left <= 0 && FRect.Right <= 0)
            {
                MergeRect.Right = ClientRect.Right;//支持不可视列
				//MergeRect.Bottom=FRect.Bottom;   //原因：
            }else                                  //不可视列调用
            {                                      //CellRect(LastCol,LastRow)时
               MergeRect.Right = FRect.Right;        //返回RECT(0,0,0,0);
			   MergeRect.Bottom = FRect.Bottom;
            }
        }else
        {
          MergeRect = ARect;
		  FirstCol = ACol;
          FirstRow = ARow;
        }
    }
    else
    {
        MergeRect = ARect;
        FirstCol = ACol;
        FirstRow = ARow;
    }
    int LeftFixedWidth(0);
    if(ACol >= FixedCols&&FixedCols>0)
    {
         for(int i = 0; i < FixedCols; i++)
              LeftFixedWidth += ColWidths[i];
         LeftFixedWidth += 1;
    }
    Canvas->Pen->Color = clBlack;
    Canvas->Pen->Style = psSolid;
    Canvas->Pen->Mode = pmCopy;
    Canvas->Pen->Width = 1;
    Canvas->Brush->Color = (TColor)ColorToRGB(FixedColor);
    Canvas->Brush->Style = bsSolid;
    Canvas->Rectangle(LeftFixedWidth > MergeRect.Left ? LeftFixedWidth : MergeRect.Left, MergeRect.Top, MergeRect.Right, MergeRect.Bottom);//  >FillRect(MergeRect);
    Canvas->Font->Assign(FZColumns->Items[FirstCol]->ColumnFont);

	String CellDrawText = Cells[FirstCol][FirstRow];
    FLen = Canvas->TextWidth(CellDrawText);
    FHeight = Canvas->TextHeight(CellDrawText);
    x = MergeRect.Left + (MergeRect.Width()-2*GridLineWidth-FLen)/2+1;
    y = MergeRect.Top + (MergeRect.Height()-2*GridLineWidth-FHeight)/2;
    MergeRect.Left = LeftFixedWidth > MergeRect.Left ? LeftFixedWidth : MergeRect.Left;
    Canvas->TextRect(MergeRect,MergeRect.left,MergeRect.right,"");
	if (FLen<MergeRect.Width())   //
    {
      MergeRect.Top = MergeRect.Top + MergeRect.Height()/2-FHeight/2;
    }
    else
    {
      int n = MergeRect.Height()/(FHeight+GridLineWidth*2);
      MergeRect.Top = MergeRect.Top + (MergeRect.Height()-FHeight*n)/2;
      MergeRect.Bottom =MergeRect.Top + n * (FHeight+GridLineWidth);
	}
	DrawText(Canvas->Handle,CellDrawText.c_str(),CellDrawText.Length(),&MergeRect,
		  DT_WORDBREAK|DT_EXTERNALLEADING|DT_CENTER );
	if(Column->ColSort != csNone && ARow < FixedRows)
	{
           int TextWidth = Canvas->TextWidth(CellDrawText);
           if(MergeRect.Right - MergeRect.Left > TextWidth - 10)
           {
                int ShapeX = (MergeRect.Left + MergeRect.Right + TextWidth) / 2 + 6;
                int ShapeY = (MergeRect.Top + MergeRect.Bottom) / 2 - 1;
                switch(Column->ColSort)
                {
                    case csAsc:
                        Canvas->Pen->Color = clGray;
                        Canvas->MoveTo(ShapeX , ShapeY - 3);
                        Canvas->LineTo(ShapeX - 3, ShapeY + 4);
                        Canvas->Pen->Color = clWhite;
                        Canvas->MoveTo(ShapeX - 3, ShapeY + 4);
                        Canvas->LineTo(ShapeX + 4, ShapeY + 4);
                        Canvas->LineTo(ShapeX + 1, ShapeY - 3);
                        break;
                    case csDesc:
                        Canvas->Pen->Color = clGray;
                        Canvas->MoveTo(ShapeX + 4, ShapeY - 3);
                        Canvas->LineTo(ShapeX - 3, ShapeY - 3);
                        Canvas->LineTo(ShapeX, ShapeY + 4);
                        Canvas->Pen->Color = clWhite;
                        Canvas->MoveTo(ShapeX + 1, ShapeY + 4);
                        Canvas->LineTo(ShapeX + 4, ShapeY - 3);
                        break;
                }
           }
    }
}
//---------------------------------------------------------------------------
void TZGrid::DrawLeftFixed(int ACol, int ARow, const TRect &ARect)
{
     if(RowHeights[ARow] <= 0)
         return;

    int FirstCol,FirstRow,LastCol,LastRow;
    TRect MergeRect;
    int x,y;

    MergeRect = ARect;
    FirstCol = ACol;
    FirstRow = ARow;

    Canvas->Pen->Color = clBlack;
    Canvas->Pen->Style = psSolid;
    Canvas->Pen->Mode = pmCopy;
    Canvas->Brush->Color = (TColor)ColorToRGB(FixedColor);
    Canvas->Brush->Style = bsSolid;
    Canvas->Rectangle(MergeRect.Left-1, MergeRect.Top-1, MergeRect.Right+1, MergeRect.Bottom+1);//  >FillRect(MergeRect);

    Canvas->Font->Assign(FZColumns->Items[FirstCol]->ColumnFont);
    if(RowState[ARow]==1)
       Canvas->Font->Color=FWarningColor;
    String DrawText = Cells[FirstCol][FirstRow];

    if(FZColumns->Count>Col)
    {
          if(FZColumns->Items[ACol]->ColHorAlign == haLeft)
              x = CalculatePos(ACol, ARow, DrawText, 1);
          else if(FZColumns->Items[ACol]->ColHorAlign == haCenter)
              x = CalculatePos(ACol, ARow, DrawText, 2);
          else
              x = CalculatePos(ACol, ARow, DrawText, 3);
          if(FZColumns->Items[ACol]->RowVerAlign == vaTop)
              y = CalculatePos(ACol, ARow, DrawText, 4);
          else if(FZColumns->Items[ACol]->RowVerAlign == vaMiddle)
              y = CalculatePos(ACol, ARow, DrawText, 5);
          else
              y = CalculatePos(ACol, ARow, DrawText, 6);
    }else
    {
        x = CalculatePos(ACol, ARow, DrawText, 1);
        y = CalculatePos(ACol, ARow, DrawText, 5);
    }

	if(ARow >= FixedRows && ACol == FExpandFoldColIndex)
    {
        DrawExpandFoldCell(ARect, DrawText, Layer[ARow], ExpandFoldMark(ARow),y);
    }else
    {
       if(FZColumns->Items[ACol]->MultyLine)
              WriteTextEh(Canvas->Handle,ARect,true,DrawText,
						FZColumns->Items[ACol]->ColHorAlign ,FZColumns->Items[ACol]->RowVerAlign,true,true);
         else
		   Canvas->TextRect(MergeRect, x, y, DrawText);
    }
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::CalculatePos(int ACol,int ARow,String s,int align)
{
  int FLen,FHeight;
  TRect ARect = CellRect(ACol,ARow);
  FLen = Canvas->TextWidth(s);
  FHeight = Canvas->TextHeight(s);
  switch(align)
  {
    case 1: //left
      return ARect.Left + GridLineWidth + 1;
    case 2: //center
      return ARect.Left + (ColWidths[ACol] - 2*GridLineWidth - FLen) / 2 + 1;
    case 3: //right
      return ARect.Left + GridLineWidth + ColWidths[ACol] - FLen - 1;
    case 4: //top
      return ARect.Top + GridLineWidth+1;
    case 5: //middle
      return ARect.Top + (RowHeights[ARow] - 2*GridLineWidth - FHeight) / 2;
    case 6: //bottom
      return ARect.Top + GridLineWidth + RowHeights[ARow]- FHeight - 1;
    default:
      return 0;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TZGrid::SelectCell(int ACol, int ARow)
{
  int mHeight,x,mRow;
  bool RetVal;
  RetVal = TBYStringGrid::SelectCell(ACol,ARow);
  Invalidate();
  if(FZColumns->Count > Col)
  {
/*
    if(FZColumns->Items[ACol]->EditType==zNone || ACol<FFixedCols || ARow<FFixedRows || !RetVal)
    {
      TBYStringGrid::Options>>goEditing;
      TBYStringGrid::HideEditor();
    }
    else
    {
      TBYStringGrid::ShowEditor();
      TBYStringGrid::Options<<goEditing;
    }
*/
  }
  else
  {
//尚未处理
  }
  if(ACol < FFixedCols || ARow < FFixedRows)
    RetVal = false;
  return RetVal;
} 
//---------------------------------------------------------------------------
bool __fastcall TZGrid::CanEditShow(void)
{
  if((!Options.Contains(goRowSelect)) &&
     (Options.Contains(goEditing)) &&
      Col >= FixedCols && Col < FZColumns->Count &&
      Row >= FixedRows && Row < RowCount)
  {
      switch(FZColumns->Items[Col]->EditType)
      {
          case zComboBox:
          case zComboList:
          case zEdit:
          case zDateTime:
          case zDropGrid:
              return true;
          default:
              return false;
      }
  }
  return false;
}
/*
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetRowHeights(int ARow)
{
  return TBYStringGrid::GetRowHeights(ARow);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::GetRowHeights(int ARow,int value)
{
  TBYStringGrid::SetRowHeights(ARow,value);
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetColWidths(int ARow)
{
  return TBYStringGrid::GetColWidths(ARow);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::GetColWidths(int ARow,int value)
{
  TBYStringGrid::SetColWidths(ARow,value);
}*/
//---------------------------------------------------------------------------
void __fastcall TZGrid::RowHeightsChanged(void)
{
    TBYStringGrid::RowHeightsChanged();
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::ColWidthsChanged(void)
{
    TBYStringGrid::ColWidthsChanged();
}
//---------------------------------------------------------------------------
double __fastcall TZGrid::Mod(double x,double y)
{
    while(x >= y)
        x -= y;
    return x;
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::CopyCols(int sCol,int dCol)
{
    if(sCol >= TBYStringGrid::ColCount || dCol >= TBYStringGrid::ColCount)
        throw Exception("Col index overflow");
    this->Cols[dCol]->Assign(this->Cols[sCol]);
}

//---------------------------------------------------------------------------
int __fastcall TZGrid::LocateGrid(int pCol,String Key)
{
    int index;
    if(pCol >= TBYStringGrid::ColCount)
        throw Exception("Col index overflow");
    index = this->Cols[pCol]->IndexOf(Key);
    if(index != -1)
        Row = index;
    return index;
}
int __fastcall TZGrid::LocateGrid(String KeyCols,String Key)
{
    int *FindCols = (int*)malloc(sizeof(int)*ColCount);
    memset(FindCols, 0, sizeof(int)*ColCount);
    TStrings* FindKeys = new TStringList();
    try{
        String TempStr;
        int CurrFindCol = 0;
        for(int i=1; i <= KeyCols.Length(); i++)
        {//extract cols
            if(KeyCols[i] == VK_TAB)
            {
                int kCol = TempStr.ToInt();
                FindCols[CurrFindCol] = kCol;
                CurrFindCol++;
                TempStr = "";
            }else
                TempStr += KeyCols[i];
        }
        if(!TempStr.IsEmpty())
            FindCols[CurrFindCol] = TempStr.ToInt();
        TempStr = "";
        for(int i=1; i <= Key.Length(); i++)
        {//extract keys
            if(Key[i] == VK_TAB)
            {
                FindKeys->Add(TempStr);
                TempStr = "";
            }else
            {
                TempStr += Key[i];
            }
        }
        if(!TempStr.IsEmpty())
            FindKeys->Add(TempStr);
        for(int i = 0; i < RowCount; i++)
        {//find row by row
            for(int j = 0; j < FindKeys->Count; j++)
            {//find key by key
                 if(FindKeys->Strings[j] != TextMatrix[i][FindCols[j]])
                      goto FindNextRow;
            }
            Row = i;
            return i;
            FindNextRow:;
        }
    }__finally
    {
        free(FindCols);
        delete FindKeys;
    }
    return -1;
}
//---------------------------------------------------------------------------
//int __fastcall TZGrid::GetFixedRows()
//{
//  return TBYStringGrid::FixedRows;
//}

//---------------------------------------------------------------------------
//void __fastcall TZGrid::SetFixedRows(int value)
//{
//  if(value<1)
//    throw Exception("FixedRows mast more than 1");
//  TBYStringGrid::FixedRows=value;
//}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetColCount()
{
    return TBYStringGrid::ColCount;
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetColCount(int value)
{
    if(value<1)
        throw Exception("Columns count can't less than 1!");
    if(value>FZColumns->Count)
    {
        for(int i=FZColumns->Count;i<value;i++)
        {
          TZColumn *newItem =(TZColumn*) FZColumns->Add();
          newItem->SetDefaultValue();
        }
    }else if(value<FZColumns->Count)
    {
        for(int i=FZColumns->Count;i>value;i--)
        {
            FZColumns->Delete(i-1);
        }
    }
    TBYStringGrid::ColCount=value;

    if(value>FFixedCols)
        TBYStringGrid::FixedCols=FFixedCols;
    else
        TBYStringGrid::FixedCols=value-1;
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetRowCount()
{
    return TBYStringGrid::RowCount;
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetRowCount(int value)
{
    if(value==0)
        throw Exception("ColCount can not less 1");
//    if(value<=FFixedRows)
//       HideEditor();
//     TBYStringGrid::SetRowCount(value);
    if(value>FFixedRows)
    {
        TBYStringGrid::SetRowCount(value);
        TBYStringGrid::FixedRows=FFixedRows;
    }else
    {
        TBYStringGrid::HideEditor();
        TBYStringGrid::FixedRows=value-1;
        TBYStringGrid::SetRowCount(value);
    }
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetFixedRows()
{
    return FFixedRows;
}

//---------------------------------------------------------------------------
void __fastcall TZGrid::SetFixedRows(int value)
{
    TBYStringGrid::FixedRows = value;
    FFixedRows = value;
    if (AutoCal && HasFooter)
    {
       ReCalculate(-1,-1);
       Invalidate();
    }   
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetFixedCols()
{
    return FFixedCols;
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetFixedCols(int value)
{
    TBYStringGrid::FixedCols = value;
    FFixedCols = value;
}
//---------------------------------------------------------------------------
String __fastcall TZGrid::GetFormatStr()
{
    return "";
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetFormatStr(String value)
{
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetColumns(TZColumns * value)
{
        Columns->Assign(value);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::DeleteColumn(int ACol)
{
    TBYStringGrid::DeleteColumn(ACol);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::DeleteRow(int ARow)
{
    TBYStringGrid::DeleteRow(ARow);
}
//---------------------------------------------------------------------------
void  __fastcall TZGrid::AddItem(String S,int index)
{
    String TempStr;
  //  bool NeedLocate;
    TStringList *MyList = new TStringList();
    bool OldAutoCal=AutoCal;
    AutoCal=false;
//    NeedLocate = false;
    try
    {
        if(index == -1)
            index = RowCount;
//        else
//            NeedLocate = true;
        RowCount = RowCount+1;
        MoveRow(RowCount-1, index);
        int iTabPos=S.Pos("\t");
        while(iTabPos>0)
        {
          MyList->Add(S.SubString(1,iTabPos-1));
          S=S.SubString(iTabPos+1,S.Length());

          iTabPos=S.Pos("\t");
        }
        if(!S.IsEmpty())
          MyList->Add(S);
        /*for(int i = 1; i <= S.Length(); i++)
        {
            if(S[i]==VK_TAB)
            {
                MyList->Add(TempStr);
                TempStr = "";
            }else
            {
                TempStr += S[i];
            }
        }
        if(!TempStr.IsEmpty())
            MyList->Add(TempStr);*/
        Rows[index]->Assign(MyList);
        Cells[HasFillColNumber][index]=1;
        Cells[RowStateNumber][index]=0;  //默认状态
        
//        if(NeedLocate)
//            Row = index;
    }__finally
    {
        delete MyList;
        AutoCal=OldAutoCal;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::ChangeItem(String S,int index)
{
    String TempStr;
    TStringList *MyList = new TStringList();
    if(index < 0 || index >= RowCount)
        throw Exception("Index overflow");
    bool OldAutoCal=AutoCal;
    AutoCal=false;
    try
    {
        for(int i = 1;i <= S.Length(); i++)
        {
            if(S[i] == VK_TAB)
            {
                MyList->Add(TempStr);
                TempStr = "";
            }else
                TempStr += S[i];
        }
        MyList->Add(TempStr);
        Rows[index]->Assign(MyList);
        Row = index;
    }__finally
    {
       AutoCal=OldAutoCal;
        delete MyList;
    }
}
//---------------------------------------------------------------------------

void __fastcall TZGrid::RemoveItem(int Index)
{
    this->Rows[Index]->Clear();
    DeleteRow(Index);
    //RowCount=RowCount-1;
    if(Index<RowCount)
        Row = Index;
    else
        Row = RowCount-1;
}
//---------------------------------------------------------------------------
String __fastcall TZGrid::GetTextMatrix(int ARow,int ACol)
{
    return Cells[ACol][ARow];
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetTextMatrix(int ARow,int ACol,String S)
{
    Cells[ACol][ARow] = S;
}
void __fastcall TZGrid::TopLeftChanged(void)
{
    TBYStringGrid::TopLeftChanged();
    TGridRect gr;
    gr.Left = LeftCol;
    gr.Right = LeftCol + VisibleColCount + 1;
    gr.Top = 0;
    gr.Bottom = FixedRows;
    InvalidateRect(gr);
    HideEditor();
//    if(!(Options.Contains(goAlwaysShowEditor)))//2003.11.20 by zws
//        HideEditor();//解决问题：当 goAlwaysShowEditor = true 时 Editor是正常的；
                   //当 goAlwaysShowEditor = false 时 Editor不随着Cell的移动而移动；
}
void __fastcall TZGrid::DefineProperties(Classes::TFiler* Filer)
{
    TBYStringGrid::DefineProperties(Filer);
	Filer->DefineBinaryProperty("ZGridData", ReadItems, WriteItems, true);
}
void __fastcall TZGrid::ReadItems(TStream* Stream)
{
	int Version = Vclcomfunc::ReadInt(Stream);
	switch(Version)
    {
       case 1:
		   ReadVersion1(Stream);
           break;
       case 2:
           break;
       default:;
    }
}
void __fastcall TZGrid::ReadVersion1(TStream*Stream)
{
    try{
        int count = Vclcomfunc::ReadInt(Stream);
        if(count > 100) throw Exception("Read property fail!");
        while(count)
        {
            Vclcomfunc::ReadInt(Stream);
            Vclcomfunc::ReadString(Stream);
            Vclcomfunc::ReadString(Stream);
            Vclcomfunc::ReadInt(Stream);
            count--;
        }
        count = Vclcomfunc::ReadInt(Stream);
        if(count > 100) throw Exception("Read property fail!");
        while(count)
        {
            Vclcomfunc::ReadString(Stream);
            Vclcomfunc::ReadInt(Stream);
            int newcount;
            newcount = Vclcomfunc::ReadInt(Stream);
            if(newcount > 100) throw Exception("Read property fail!");
            while(newcount)
            {
                Vclcomfunc::ReadInt(Stream);
                Vclcomfunc::ReadString(Stream);
                Vclcomfunc::ReadString(Stream);
                newcount--;
            }
            newcount = Vclcomfunc::ReadInt(Stream);
            if(newcount > 100) throw Exception("Read property fail!");
            while(newcount)
            {
                Vclcomfunc::ReadInt(Stream);
                Vclcomfunc::ReadInt(Stream);
                Vclcomfunc::ReadString(Stream);
                newcount--;
            }
            Vclcomfunc::ReadInt(Stream);
            newcount = Vclcomfunc::ReadInt(Stream);
            if(newcount > 100) throw Exception("Read property fail!");
            while(newcount)
            {
                Vclcomfunc::ReadInt(Stream);
                Vclcomfunc::ReadString(Stream);
                Vclcomfunc::ReadString(Stream);
                newcount--;
            }
            newcount = Vclcomfunc::ReadInt(Stream);
            if(newcount > 100) throw Exception("Read property fail!");
            while(newcount)
            {
                Vclcomfunc::ReadInt(Stream);
                Vclcomfunc::ReadInt(Stream);
                Vclcomfunc::ReadString(Stream);
                newcount--;
            }
            count--;
        }

        Vclcomfunc::ReadInt(Stream);
        count = Vclcomfunc::ReadInt(Stream);
        if(count > 100) throw Exception("Read property fail!");
        while(count)
        {
            Vclcomfunc::ReadInt(Stream);
            Vclcomfunc::ReadInt(Stream);
            Vclcomfunc::ReadString(Stream);
			count--;
        }
    }catch(...)
    {
    }
}
void __fastcall TZGrid::WriteItems(TStream* Stream)
{
	Vclcomfunc::WriteInt(Stream, 2);//version
}
//---------------------------------------------------------------------------
//以下是支持展开合拢功能
void __fastcall TZGrid::SetExpandFoldColIndex(int ACol)
{
//    ACol--;
//    if(ACol < 0)
//    {
//        FExpandFoldColIndex = -1;
//    }else
    if(ACol >= 0 && ACol < ColCount)
    {
        FExpandFoldColIndex = ACol;
    }
    else
         FExpandFoldColIndex = -1;
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetExpandFoldColIndex()
{
    return FExpandFoldColIndex;
}
//---------------------------------------------------------------------------
void TZGrid::DrawExpandFold(HDC dc, int X, int Y, bool Expanded)
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

    MoveToEx(dc, X - 4, Y, NULL);
    LineTo(dc, X + 4, Y);
    if(!Expanded)
    {
        MoveToEx(dc, X, Y - 4, NULL);
        LineTo(dc, X, Y + 4);
	}
    SelectObject(dc, oldpen);
    DeleteObject(pen);
}
//---------------------------------------------------------------------------
void TZGrid::DrawExpandFoldCell(const TRect &ARect, String&AName, int Layer, int ExpandType, int y)
{//ExpandType 0:None 1:Expanded 2:Folded
    TRect dr = ARect;
    switch(ExpandType)
    {
        case 1:
            dr.Left = dr.Left + (Layer) * ExpandInc + ExpandSize;
            Canvas->TextRect(ARect, dr.Left, y, AName);
            DrawExpandFold(Canvas->Handle, ARect.Left + (Layer) * ExpandInc + ExpandSize / 2,
                           (ARect.Top + ARect.Bottom) / 2, true);
            break;
        case 2:
            dr.Left = dr.Left + (Layer) * ExpandInc + ExpandSize;
            Canvas->TextRect(ARect, dr.Left, y, AName);
            DrawExpandFold(Canvas->Handle, ARect.Left + (Layer) * ExpandInc + ExpandSize / 2,
                           (ARect.Top + ARect.Bottom) / 2, false);
            break;
        case 0:
            dr.Left = dr.Left + (Layer) * ExpandInc + ExpandSize;
            Canvas->TextRect(ARect, dr.Left, y, AName);
            break;
        default:
            throw Exception("TPrjGrid::DrawName逻辑错误");
    }
    //DrawText(Canvas->Handle, AName.c_str(), AName.Length(), &dr, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
}
//---------------------------------------------------------------------------
void TZGrid::SetLayer(int ARow, int Value)
{
    if(ARow >= 0 && ARow < RowCount)
    {
        if(Value >= 0)
            Cells[ExpandColNumber][ARow] = IntToStr(Value);
    }
}
//---------------------------------------------------------------------------
int TZGrid::GetLayer(int ARow)
{
    if(ARow >= 0 && ARow < RowCount)
    {
        if(!(Cells[ExpandColNumber][ARow].Trim().IsEmpty()))
            return Cells[ExpandColNumber][ARow].ToInt();
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::SetIsFilled(int ARow, int value)
{
    if(ARow >= 0 && ARow < RowCount)
    {
        if(value >= 0)
            Cells[HasFillColNumber][ARow] = IntToStr(value);
         Invalidate();
    }
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetIsFilled(int ARow)
{
    if(ARow >= 0 && ARow < RowCount)
    {
        if(!(Cells[ExpandColNumber][ARow].Trim().IsEmpty()))
            return Cells[HasFillColNumber][ARow].ToInt();
    }
    return 1;
}
void __fastcall TZGrid::SetRowState(int ARow, int value)
{
    if(ARow >= 0 && ARow < RowCount)
    {
        if(value >= 0)
            Cells[RowStateNumber][ARow] = IntToStr(value);
         Invalidate();
    }
}
//---------------------------------------------------------------------------
TFont* __fastcall TZGrid::RowStateFont(int ARow)
{
  int index = GetRowState(ARow);
  if(index==0)
  {
    return Font;
  }
  if(FRowFonts->Items[index-1]==NULL)
    return Font;
  else
    return FRowFonts->Items[index-1]->Font;
}
//---------------------------------------------------------------------------
int __fastcall TZGrid::GetRowState(int ARow)
{
    if(ARow >= 0 && ARow < RowCount)
    {
        if(!(Cells[RowStateNumber][ARow].Trim().IsEmpty()))
            return Cells[RowStateNumber][ARow].ToInt();
    }
    return 0;
}

//---------------------------------------------------------------------------
void TZGrid::ExpandMouseDown(int ACol, int ARow, int MouseX, int MouseY, TMessage& AMsg)
{
    if(ARow >= FixedRows && ARow < RowCount)
    {
         int RowLayer = Layer[ARow];
         TRect r = CellRect(ACol, ARow);
         int MidX = r.Left + RowLayer *
                                 ExpandInc + ExpandSize / 2;
         if(MouseX > MidX - ExpandSize/2 && MouseX < MidX + ExpandSize/2)
         {
              if(RowHeights[ARow+1] > 0&&IsFilled[ARow]==1)
              {//Fold
                  Fold(ARow);
                  Cells[ExpandMarkColNumber][ARow] = "2";
                  ReIndexRowIndex();
              }else
              {//Expand
                bool CanExpand(true);
                if(FOnExpand)
                   FOnExpand(this,ACol,ARow,CanExpand);
                if(!CanExpand)
                    return;
                  Expand(ARow);
                  Cells[ExpandMarkColNumber][ARow] = "1";
                  ReIndexRowIndex();
              }
         }
    }
}
//---------------------------------------------------------------------------
void TZGrid::Expand(int ARow)
{
    if(ARow >= FixedRows && ARow < RowCount)
    {
//                  try
//                  {
//                   BeginUpdate();
                   int RowLayer = Layer[ARow];
                   Cells[ExpandMarkColNumber][ARow]="1";
                   for(int i = ARow+1; i < RowCount; i++)
                   {
                       if(Layer[i] == RowLayer + 1)
                       {
                           RowHeights[i] = DefaultRowHeight;
                           switch(ExpandFoldMark(i))
                           {
                               case 0:
                                   break;
                               case 1:
                                   Expand(i);
                                   break;
                               case 2:
                                   break;
                           }
                       }else if(Layer[i] > RowLayer)
                       {
                       }else
                           break;
                   }
//                 }
//                 __finally
//                 {
//                 EndUpdate();
//                 }
     }
}
//---------------------------------------------------------------------------
void TZGrid::Fold(int ARow)
{
    if(ARow >= FixedRows && ARow < RowCount)
    {
//            try{
//                  BeginUpdate();
                   int RowLayer = Layer[ARow];
                   Cells[ExpandMarkColNumber][ARow]="2";
                   for(int i = ARow+1; i < RowCount; i++)
                   {
                       if(Layer[i] > RowLayer)
                           RowHeights[i] = -1;
                       else
                           break;
                   }
//               }
//               __finally
//               {
//                 EndUpdate();
//               }
    }
}
//---------------------------------------------------------------------------
int TZGrid::ExpandGetRowIndex(int ARow)
{
    String Number = Cells[RowIndexColNumber][ARow];
    if(Number.IsEmpty())
        return ARow;
    else
        return Number.ToInt();
}
//---------------------------------------------------------------------------
void TZGrid::ReIndexRowIndex()
{
    int Index = FixedRows;
    for(int i = FixedRows; i < RowCount; i++)
    {
        if(RowHeights[i] > 0)
        {
            Cells[RowIndexColNumber][i] = IntToStr(Index);
            Index++;
        }else
        {
            Cells[RowIndexColNumber][i] = "";
        }
    }
}
//---------------------------------------------------------------------------
int TZGrid::ExpandFoldMark(int ARow)
{
    int RowLayer = Layer[ARow];
    int ExpandType;
    if(Layer[ARow+1] <= RowLayer)
        ExpandType = 0;
    else if(RowHeights[ARow+1] > 0)
    {
        ExpandType = 1; //Expand
    }else
    {
        ExpandType = 2; //Fold
    }
    if(IsFilled[ARow]==0)   //no Filled
       ExpandType=1;
    return ExpandType;

//    if(Layer[ARow+1] <= Layer[ARow])
//    {
//        return 0;
//    }
//    if((ARow+1<RowCount)&&RowHeights[ARow+1]==-1)
//       return 1;
//    String Marker = Cells[ExpandMarkColNumber][ARow];
//    if(Marker.IsEmpty())
//    {
//        return 0;//1
//    }else
//    {
//        return Marker.ToInt();
//    }
}
//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////
//
//              TZColumn Object Implementation
//              Kallen 2000.1.25
//              CopyRight(c) SD Co.LTD
//
//////////////////////////////////////////////////////////////

TColHorAlign __fastcall TZColumn::GetColHorAlign()
{
    return FColHorAlign;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetColHorAlign(TColHorAlign ColHorAlign)
{
    FColHorAlign=ColHorAlign;
    FZColumns->ZGRID->Invalidate();
}
//---------------------------------------------------------------------------
TRowVerAlign __fastcall TZColumn::GetRowVerAlign()
{
    return FRowVerAlign;
}
//---------------------------------------------------------------------------


void __fastcall TZColumn::SetRowVerAlign(TRowVerAlign RowVerAlign)
{
    FRowVerAlign=RowVerAlign;
    FZColumns->ZGRID->Invalidate();
}
//---------------------------------------------------------------------------
TColSort __fastcall TZColumn::GetColSort()
{
    return FColSort;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetColSort(TColSort ColSort)
{
    FColSort=ColSort;
    FZColumns->ZGRID->Invalidate();
}
//---------------------------------------------------------------------------
String __fastcall TZColumn::GetSortField()
{
    return FSortField;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetSortField(String ColSort)
{
    FSortField = ColSort;
}
//---------------------------------------------------------------------------
TZCharType __fastcall TZColumn::GetCharType()
{
    return FCharType;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetCharType(TZCharType AType)
{
    FCharType = AType;
    switch(FCharType)
	{
		case TZCharType::ctNormal:
            break;
		case ctCharacter: //除数字以外的所有字符
			FValidChar = "AaBbCcDdEdFfGg"
						 "HhIiJjKkLlMmNn"
						 "OoPpQqRrSsTt"
						 "UuVvWwXxYyZz "
						 "1234567890"
						 "-=\\|+_)(*&^%$#@!~`"
						 "[]{}'\"/?.>,<";
			FDefaultValue = "";
			break;
		case ctLetter:   //仅仅字母
			FValidChar = "AaBbCcDdEdFfGg"
						 "HhIiJjKkLlMmNn"
						 "OoPpQqRrSsTt"
						 "UuVvWwXxYyZz";
			FDefaultValue = "";
			break;
		case ctPlus:     //正整数
			FValidChar = "0123456789";
			FDefaultValue = "0";
			break;
		case ctNegative:  //负整数
			FValidChar = "-0123456789";
			FDefaultValue = "0";
			break;
		case ctInteger:  //整数
			FValidChar = "-0123456789";
			FDefaultValue = "0";
			break;
		case ctPlusFloat:      //正浮点数
			FValidChar = ".0123456789";
			FDefaultValue = "0";
			break;
		case ctNegativeFloat:  //负浮点数
			FValidChar = "-.0123456789";
			FDefaultValue = "0";
			break;
		case ctFloat:
			FValidChar = "-.0123456789";
			FDefaultValue = "0";
			break;
		case ctID:             //第一个字母，以后字母,数字，"-"号
			FValidChar = "AaBbCcDdEdFfGg"
						 "HhIiJjKkLlMmNn"
						 "OoPpQqRrSsTt"
						 "UuVvWwXxYyZz"
						 "0123456789"
						 "-";
			FDefaultValue = "";
			break;
		case ctSelfDefine:   //自定义
			FDefaultValue = "";
			break;
		default:
			throw Exception("数据类型未定义");
	}
}
//---------------------------------------------------------------------------
TZCharCase __fastcall TZColumn::GetCharCase()
{
	return FCharCase;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetCharCase(TZCharCase CharCase)
{
	if(FCharCase!=CharCase)
    {
      FCharCase=CharCase;
	  FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
String __fastcall TZColumn::GetTitle()
{
    return FTitle;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetTitle(String Title)
{
   if(FTitle!=Title)
   {
    FTitle=Title;
    FZColumns->ZGRID->Cells[Index][0]=Title;
    FZColumns->ZGRID->Invalidate();
   }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetFootText(String value)
{
        if(FFootText != value) {
                FFootText = value;
           if(FZColumns->ZGRID->HasFooter)
             FZColumns->ZGRID->Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetCalType(TZCalculateType value)
{
        if(FCalType != value) {
                FCalType = value;
        if(FZColumns->ZGRID->AutoCal && value!=ctNone)
           FZColumns->ZGRID->ReCalculate(-1,-1);
        }
}
//---------------------------------------------------------------------------
int __fastcall TZColumn::GetColWidth()
{
    return 0;//FZColumns->ZGRID->ColWidths[Index];
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetColWidth(int value)
{
//  if(FZColumns->ZGRID->ComponentState.Contains(csDesigning))
//      FZColumns->ZGRID->ColWidths[Index] = value;
}
//---------------------------------------------------------------------------
TFont * __fastcall TZColumn::GetTitleFont()
{
    return FTitleFont;
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetTitleFont(TFont *value)
{
    if(FTitleFont!=value)
    {
      FTitleFont->Assign(value);
       if(FZColumns->ZGRID->HasFooter)
         FZColumns->ZGRID->Invalidate();

    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetFootFont(TFont* value)
{
        if(FFootFont != value) {
           FFootFont ->Assign(value);
           if(FZColumns->ZGRID->HasFooter)
             FZColumns->ZGRID->Invalidate();
        }
}
//---------------------------------------------------------------------------

TEditType __fastcall TZColumn::GetEditType()
{
    return FEditType;
}

//---------------------------------------------------------------------------
void __fastcall TZColumn::SetEditType(TEditType value)
{
    if(FEditType!=value){
       FEditType=value;
       FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetMultyLine(bool value)
{
        if(FMultyLine != value) {
                FMultyLine = value;
            FZColumns->ZGRID->Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetMerged(bool value)
{
    if(FMerged!=value)
    {
            FMerged=value;
            FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetRowMergeCount(int value)
{
//  if(value>FZColumns->ZGRID->FixedRows)
//    throw Exception("RowMergeCount can not be more than FixedRows.");
    if(value!=FRowMergeCount)
    {
      if(value<0)
          throw Exception("Invalidate property value.");
      FRowMergeCount=value;
      FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetRowMergeOrder(int value)
{
   if(value!=FRowMergeCount)
   {
      if(FRowMergeCount==0)
      {
          FRowMergeOrder=0;
          return;
      }
      FRowMergeOrder= value;
      FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetColMergeCount(int value)
{
//  if(value>FZColumns->ZGRID->FixedCols)
//    throw Exception("ColMergeCount can not be more than FixedCols.");
    if(value!=FColMergeCount)
    {
      if(value<0)
          throw Exception("Invalidate property value.");
      FColMergeCount=value;
      FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetColMergeOrder(int value)
{
    if(value!=FColMergeOrder)
    {
      if(FColMergeCount==0)
      {
          FColMergeOrder=0;
          return;
      }
      FColMergeOrder=value;
      FZColumns->ZGRID->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetColumnVisible(bool value)
{
    if(FColumnVisible != value)
    {
        FColumnVisible = value;
//        if(value)
//   //        FZColumns->ZGRID->ColWidths[this->Index]=FColWidth;
//            FZColumns->ZGRID->ColWidths[Index]=FZColumns->ZGRID->DefaultColWidth;
//        else
//            FZColumns->ZGRID->ColWidths[Index]=-1;
//crj 2005-04-26
        if(value)
        {
          if(FZColumns->Items[Index]->HideColWidth<=5)
            FZColumns->ZGRID->ColWidths[Index]=FZColumns->ZGRID->DefaultColWidth;
          else
            FZColumns->ZGRID->ColWidths[Index]=FZColumns->Items[Index]->HideColWidth;
        }
        else
        {
          FZColumns->Items[Index]->HideColWidth = FZColumns->ZGRID->ColWidths[Index];
          FZColumns->ZGRID->ColWidths[Index]=-1;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetEditButtonVisible(bool value)
{
        if(FEditButtonVisible != value) {
                FEditButtonVisible = value;
        }
}
//---------------------------------------------------------------------------
__fastcall TZColumn::TZColumn(TCollection* Collection)
                :TCollectionItem(Collection)
{
 SetDefaultValue();
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::SetDefaultValue()
{
    FColHorAlign=haLeft;
    FHideColWidth=50;    
    FRowVerAlign=vaMiddle;//vaBottom;
    FColSort=csNone;
	FCharType=TZCharType::ctNormal;
	FCharCase=ccNormal;
    FKeyItem=cbItem1;                       
    FMerged=false;
    FRowMergeCount=1;
	FRowMergeOrder=0;
    FColMergeCount=1;
    FColMergeOrder=0;
    FTitleFont=new TFont;
    FEditType=zNone;
    FColumnVisible=true;
    FEditButtonVisible=false;
    FMultyLine=false;
    FZColumns=(TZColumns *)Collection;
    FCurListItemIndex=-1;
    FListItem=new TStringList();
    FTitleFont->Charset= GB2312_CHARSET;
    FTitleFont->Name="宋体";
    FTitleFont->Size=9;
    FCalType = ctNone;
    FFootFont=new TFont;
    FFootFont->Assign(FTitleFont);
}
//---------------------------------------------------------------------------
__fastcall TZColumn::~TZColumn()
{
    if(FTitleFont)
        delete FTitleFont;
    if(FFootFont)
		delete FFootFont;
	if(FListItem)
      {
	   Vclcomfunc::TItemObject *ItemObject;
        for(int i=0;i<FListItem->Count;i++)
        {
			 ItemObject=(Vclcomfunc::TItemObject*)FListItem->Objects[i];
             delete ItemObject;
         }
		delete FListItem;
      }
}
//---------------------------------------------------------------------------

void __fastcall TZColumn::AddListItem(String DispItem,String Item1,String Item2,String Item3,String Item4,String Item5,String Item6)
{
	 Vclcomfunc::TItemObject *ItemObject=new TItemObject();
     ItemObject->PutElement(DispItem,0);
     ItemObject->PutElement(Item1,1);
     ItemObject->PutElement(Item2,2);
     ItemObject->PutElement(Item3,3);
     ItemObject->PutElement(Item4,4);
	 ItemObject->PutElement(Item5,5);
     ItemObject->PutElement(Item6,6);
     FListItem->AddObject(DispItem,(TObject*)ItemObject);

}
//---------------------------------------------------------------------------

void __fastcall TZColumn::DeleteListItem(int index)
{
	if(index<0 || index>=FListItem->Count)
        throw Exception("Index overflow!");
	Vclcomfunc::TItemObject *ItemObject=(Vclcomfunc::TItemObject*)FListItem->Objects[index];
    delete ItemObject;
    FListItem->Delete(index);
}
//---------------------------------------------------------------------------
Variant __fastcall TZColumn::GetComboxItems(int index)
{
    if(FCurListItemIndex<0||index<0||index>6)
       return NULL;
	Vclcomfunc::TItemObject *ItemObject=(Vclcomfunc::TItemObject*)FListItem->Objects[FCurListItemIndex];
    return ItemObject->GetElement(index);
}
//---------------------------------------------------------------------------
void __fastcall TZColumn::ClearListItem()
{
  Vclcomfunc::TItemObject *ItemObject;
  for(int i=0;i<FListItem->Count;i++)
  {
       ItemObject=(TItemObject*)FListItem->Objects[i];
       delete ItemObject;
   }
    FListItem->Clear();
}
//---------------------------------------------------------------------------
int __fastcall TZColumn::LocateComboxByKey(Variant varValue)
{
  FCurListItemIndex=-1;
  TItemObject *ItemObject;
  int varType=varValue.Type();
  for(int i=0;i<FListItem->Count;i++)
  {
       ItemObject=(TItemObject*)FListItem->Objects[i];
       Variant var1=ItemObject->GetElement(FKeyItem);
       if(varType==varString||varType==varOleStr)
	   {
		 if(var1.operator String().UpperCase() ==varValue.operator String().UpperCase())
		  {
            FCurListItemIndex=i;
            break;
          }
	   }
       else
	   if(var1==varValue)
        {
          FCurListItemIndex=i;
          break;
        }
   }
  return FCurListItemIndex;
}
//---------------------------------------------------------------------------
//TPersistent* __fastcall TZColumn::GetOwner(void)
//{
//    return (TZColumns *)Collection;
//}
void __fastcall TZColumn::SetDigLen(int Len)
{
    if(FDigLen != Len)
    {
      if(MaxLen==0||MaxLen>Len+1)
        FDigLen=Len;
      else
        FDigLen=0;
	  FZColumns->ZGRID->Invalidate();
    }
}
void __fastcall TZColumn::Assign(TPersistent * Source)
{
  TZColumn *This=dynamic_cast<TZColumn*>(Source);
 if(This!=NULL)
 {
    if(Collection!=NULL)
       Collection->BeginUpdate();
    try{
         EditType=This->EditType;
         ColumnFont->Assign(This->ColumnFont);
         ColHorAlign=This->ColHorAlign;
         RowVerAlign=This->RowVerAlign;
         ColSort=This->ColSort;
         SortField=This->SortField;
         CharType=This->CharType;
         CharCase=This->CharCase;
         TitleString=This->TitleString;
         ColumnWidth=This->ColumnWidth;
         Merged=This->Merged;
         RowMergeCount=This->RowMergeCount;
         RowMergeOrder=This->RowMergeOrder;
		 ColMergeCount=This->ColMergeCount;
         ColMergeOrder=This->ColMergeOrder;
         ColumnVisible=This->ColumnVisible;
         EditButtonVisible = This->EditButtonVisible;
         DigLen=This->DigLen;
         MaxLen=This->MaxLen;
         ValidChar = This->ValidChar;
         ListItem->Assign(This->ListItem);
         OnButtonDown = This->OnButtonDown;
         CalType = This->CalType;
         FootFont->Assign(This->FootFont);
    }
    __finally
    {
    if(Collection!=NULL)
       Collection->EndUpdate();
    }
 }
 else
   TCollectionItem::Assign(Source);
}
//---------------------------------------------------------------------------
TZColumn* __fastcall TZColumns::GetColumn(int Index)
{
//       if(Index<=-1||Index>=Count)
//          throw Exception("Index out of bounds1");
        return (TZColumn *)TCollection::Items[Index];
}
//---------------------------------------------------------------------------
void __fastcall TZColumns::Assign(TPersistent * Source)
{
  TZColumns *This=dynamic_cast<TZColumns*>(Source);
  if(This!=NULL)
  {
        int i=0;
        if(Count<=This->Count)
        {
          for(i=0;i<Count;i++)
          {
            Items[i]->Assign(This->Items[i]);
          }
          while(Count<This->Count)
          {
            TZColumn *newItem=(TZColumn*)Add();
            newItem->SetDefaultValue();
            Items[Count-1]->Assign(This->Items[Count-1]);
          }
        }
       else
       {
         for(i=0;i<This->Count;i++)
         {
            Items[i]->Assign(This->Items[i]);
         }
         BeginUpdate();
         try
         {
           while(Count>This->Count)
           {
             this->Delete(Count);
           }
         }
          __finally
           {
             EndUpdate();
           }

       }
  }
 else
  TCollection::Assign(Source);
  if(FGrid!=NULL)
  {
    if(FGrid->ColCount!=Count)
      FGrid->ColCount=Count;
  }
}
void __fastcall TZColumns::SetColumn(int Index, TZColumn* Value)
{
//       if(Index<=-1||Index>=Count)
//          throw Exception("Index out of bounds2");
          Items[Index]->Assign(Value);
}
//---------------------------------------------------------------------------
//TCollectionItem* __fastcall TZColumns::BaseAdd(void)
//{
//  return TCollection::Add();
//}
//void __fastcall TZColumns::BaseDelete(int Index)
//{
//  TCollection::Delete(Index);
//}

//TCollectionItem* __fastcall TZColumns::Add(void)
//{
//  TCollectionItem* item = TCollection::Add();
//  if(FGrid!=NULL)
//  {
//    FGrid->ColCount=Count;
//  }
//  return item;
//}
//void __fastcall TZColumns::Delete(int Index)
//{
//  TCollection::Delete(Index);
//  if(FGrid!=NULL)
//  {
//    FGrid->ColCount=Count;
//  }
//}
//---------------------------------------------------------------------------

TPersistent* __fastcall TZColumns::GetOwner(void)
{
        return FGrid;
}
//---------------------------------------------------------------------------
__fastcall TZColumns::TZColumns(TZGrid *mGrid,TMetaClass* ItemClass)
        :TCollection(ItemClass)
{
        FGrid=mGrid;
}
//--------------------------------------------------------------------------
//-----------------             TRowFontItem       ----------------------------------
//--------------------------------------------------------------------------
void __fastcall TRowFontItem::Assign(TPersistent * Source)
{
   TRowFontItem *This=dynamic_cast<TRowFontItem*>(Source);
   if(This!=NULL)
   {
      if(Collection!=NULL)
         Collection->BeginUpdate();
      try{
           FFont->Assign(This->FFont);
      }
      __finally
      {
      if(Collection!=NULL)
         Collection->EndUpdate();
      }
   }
   else
     TCollectionItem::Assign(Source);
}
__fastcall TRowFontItem::TRowFontItem(TCollection* Collection):TCollectionItem(Collection)
{
  FRowFonts=(TRowFonts *)Collection;
  FFont = new TFont();
  FFont->Assign(FRowFonts->ZGRID->Font);
}
__fastcall TRowFontItem::~TRowFontItem()
{
  if(FFont!=NULL)
	delete FFont;
}
void __fastcall TRowFontItem::SetRowFont(TFont *value)
{
    if(FFont!=value)
    {
      FFont->Assign(value);
      FRowFonts->ZGRID->Invalidate();
    }
}
//--------------------------------------------------------------------------
//-----------------             TRowFonts       ----------------------------------
//--------------------------------------------------------------------------
void __fastcall TRowFonts::Assign(TPersistent * Source)
{
  TRowFonts *This=dynamic_cast<TRowFonts*>(Source);
  if(This!=NULL)
  {
        int i=0;
        if(Count<=This->Count)
        {
          for(i=0;i<Count;i++)
          {
            Items[i]->Assign(This->Items[i]);
          }
          while(Count<This->Count)
          {
//            TZColumn *newItem=(TZColumn*)Add();
//            newItem->SetDefaultValue();
            Add();
            Items[Count-1]->Assign(This->Items[Count-1]);
          }
        }
       else
       {
         for(i=0;i<This->Count;i++)
         {
            Items[i]->Assign(This->Items[i]);
         }
         BeginUpdate();
         try
         {
           while(Count>This->Count)
           {
             this->Delete(Count);
           }
         }
          __finally
           {
             EndUpdate();
           }

       }
  }
 else
  TCollection::Assign(Source);
}

TRowFontItem* __fastcall TRowFonts::GetFontItem(int Index)
{
  if(Index<=-1||Index>=Count)
  {
    return NULL;
  }
  return (TRowFontItem *)TCollection::Items[Index];
}
void __fastcall TRowFonts::SetFontItem(int Index, TRowFontItem* Value)
{
  if(Index<=-1||Index>=Count)
  {
    Add();
    Index = Count-1;
  }
  Items[Index]->Assign(Value);
}
__fastcall TRowFonts::TRowFonts(TZGrid *mGrid,TMetaClass* ItemClass):TCollection(ItemClass)
{
   FGrid=mGrid;
}
TPersistent* __fastcall TRowFonts::GetOwner(void)
{
        return FGrid;
}

//---------------------------------------------------------------------------
// TZInplaceEdit
//---------------------------------------------------------------------------
class TMYPopupForm : public TForm
{
public:
    TZInplaceEdit *DropDown;
    TListBox *ListBox;
    void __fastcall PopupFormClose(System::TObject* Sender, TCloseAction &Action)
    {
        Action = caHide;
        //SendMessage(DropDown->Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
        DropDown->SetFocus();
    }
    void __fastcall WMActivate(TMessage &Message)
    {
        TForm::Dispatch(&Message);
        if(Message.WParam == WA_INACTIVE)
        {
            PostMessage(Handle, WM_CLOSE, 0, 0);
        }
    }
    void __fastcall ListBoxMouseMove(TObject *Sender,Classes::TShiftState Shift, int X, int Y)
    {
        int i;
        i=Y/ListBox->ItemHeight + ListBox->TopIndex;
        if(i<ListBox->Items->Count)
            ListBox->ItemIndex=i;
    }
    //---------------------------------------------------------------------------
    void __fastcall ListBoxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
    {
        if(ListBox->ItemIndex != -1)
            Selected(ListBox->ItemIndex);
        DropDown->Grid->SetFocus();
        SendMessage(DropDown->Grid->Handle,WM_USER+110,0,0);
    }
    //---------------------------------------------------------------------------
    void __fastcall ListBoxKeyDown(TObject *Sender,Word &Key, Classes::TShiftState Shift)
    {
         if(Key==VK_ESCAPE)
         {
             Close();
             DropDown->Grid->SetFocus();
             return;
         }
         if(Key==VK_RETURN)
         {
             if(ListBox->ItemIndex!=-1)
                 Selected(ListBox->ItemIndex);
             DropDown->Grid->SetFocus();
             SendMessage(DropDown->Grid->Handle,WM_USER+110,0,0);             
             return;
         }
    }
    void __fastcall ListBoxShow(TObject *Sender)
    {
      if(ListBox->Items->Count <=0)
      {
         Height = 0;
         Width = 0;
      }
      else
      {
        Width = 150;
        if(ListBox->Items->Count < 8)
           Height=ListBox->ItemHeight * ListBox->Items->Count+2;
        else
           Height = ListBox->ItemHeight * 8 + 2;
//        if(DropDown->ClientOrigin.y + Height + 50 > Screen->Height)
//            Top =DropDown->ClientOrigin.y - Height - 5;
//         else
//            Top = DropDown->ClientOrigin.y + DropDown->Height;
//        if(DropDown->ClientOrigin.x + Width + 50 > Screen->Width)
//           Left = DropDown->ClientOrigin.x - Width + DropDown->Width;
//        else
//           Left = DropDown->ClientOrigin.x;

      }

    }
    //---------------------------------------------------------------------------
    void __fastcall ListBoxExit(TObject *Sender)
    {
         Close();
         DropDown->Grid->SetFocus();
    }
    BEGIN_MESSAGE_MAP
          VCL_MESSAGE_HANDLER(WM_ACTIVATE, TMessage, WMActivate);
    END_MESSAGE_MAP(TForm);
public:
    __fastcall TMYPopupForm(TZInplaceEdit*ADropDown)
               : TForm(ADropDown, 0), DropDown(ADropDown)
    {
        BorderStyle = bsNone;
        HorzScrollBar->Visible = false;
        VertScrollBar->Visible = false;
        FormStyle = fsStayOnTop;
        OnClose = PopupFormClose;
        Font->Charset= GB2312_CHARSET;
        Font->Name="宋体";
        Font->Size=9;
        ParentFont=true;
        OnShow=ListBoxShow;

        ListBox = new TListBox(this);
        ListBox->Parent= this;
        ListBox->Ctl3D=false;
        ListBox->Visible=true;
        ListBox->Font->Assign(Font);
        ListBox->ParentFont=true;
        ListBox->Align = alClient;
        ListBox->OnMouseDown=ListBoxMouseDown;
        ListBox->OnMouseMove=ListBoxMouseMove;
        ListBox->OnKeyDown=ListBoxKeyDown;
        ListBox->OnExit=ListBoxExit;

    }
    void ShowForm(TStrings* Lists)          //zws2003-12-10
    {
        ListBox->Items->Assign(Lists);
		String celltext=((TZGrid*)(DropDown->Grid))->Cells[((TZGrid*)(DropDown->Grid))->Col][((TZGrid*)(DropDown->Grid))->Row];
        int cIndex=DropDown->FEditColumn->LocateComboxByKey(celltext);
        if(cIndex>=0)
           ListBox->ItemIndex=cIndex;
		TPoint P;
		P.x = DropDown->ClientOrigin.x;
		P.y = DropDown->ClientOrigin.y+DropDown->Height;
		SetWindowPos(Handle, HWND_TOP, P.x, P.y, 0, 0,
		SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);           
        Show();
        SetFocus();
    }
    void Selected(int Index)
    {
        DropDown->FEditColumn->CurListItemIndex=Index;
        TZGrid* PGrid=((TZGrid*)(DropDown->Grid));
		String OldText=PGrid->Cells[PGrid->Col][PGrid->Row];
		String NewText=DropDown->FEditColumn->ComboxItems[cbItem1];
		PGrid->Cells[PGrid->Col][PGrid->Row]=NewText;
		if((OldText!=NewText) && (PGrid->OnEditControlChange))
        {
          DropDown->Text=DropDown->FEditColumn->ComboxItems[cbItem1];
          PGrid->OnEditControlChange(this,PGrid->Col,PGrid->Row,DropDown->Text);
          DropDown->OldText=DropDown->Text;
        }
    }
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
String GetDateSplitter()
{
    String tempDateStr = TDateTime::CurrentDate();
    for(int i = 1; i <= tempDateStr.Length(); i++)
    {
        if(tempDateStr[i] >= '0' && tempDateStr[i] <= '9')
        {
        }else
        {
            return String(tempDateStr[i]);
        }
    }
    return "";
}
TDateTime MyStrToDate(String AStr)
{
    String DateSplitter = GetDateSplitter();
    for(int i = 1; i <= AStr.Length(); i++)
    {
        if(AStr[i] >= '0' && AStr[i] <= '9')
        {
        }else
        {
            AStr[i] = DateSplitter[1];
        }
    }
    return TDateTime(AStr);
}
//---------------------------------------------------------------------------
// TDateSelectForm
//---------------------------------------------------------------------------
class TDateSelectForm : public TForm
{
public:
    TZInplaceEdit* DateEdit;
    TZMonthCalendar *MonthCale;
    TZGrid        *PGrid;
    void __fastcall MonthCalendarSelect(TObject *Sender)
    {
        Close();
        DateEdit->Text = MonthCale->Date.FormatString("yyyy-mm-dd");
        PGrid=(TZGrid*)(DateEdit->Grid);
        if(PGrid!=NULL)
        {
            String OldDate=PGrid->Cells[PGrid->Col][PGrid->Row];
            PGrid->Cells[PGrid->Col][PGrid->Row]=DateEdit->Text;
            if((OldDate!=DateEdit->Text) && (PGrid->OnEditControlChange))
            {
             PGrid->OnEditControlChange(this,PGrid->Col,PGrid->Row,DateEdit->Text);
             DateEdit->OldText=DateEdit->Text;
            }
         }
        DateEdit->SetFocus();
    }
    void __fastcall  MonthCalendarClick(TObject *Sender)
    {
        if(Caption != MonthCale->Date.FormatString("yyyy-mm-dd"))
            Close();
    }
    //---------------------------------------------------------------------------
    void __fastcall  MonthCalendarKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
    {
        if(Key==VK_RETURN)
        {
            Close();
            DateEdit->Text = MonthCale->Date.FormatString("yyyy-mm-dd");
            PGrid=(TZGrid*)(DateEdit->Grid);
            if(PGrid!=NULL)
            {
              String OldDate=PGrid->Cells[PGrid->Col][PGrid->Row];
              PGrid->Cells[PGrid->Col][PGrid->Row]=DateEdit->Text;
              if((OldDate!=DateEdit->Text) && (PGrid->OnEditControlChange))
              {
                PGrid->OnEditControlChange(this,PGrid->Col,PGrid->Row,DateEdit->Text);
                DateEdit->OldText=DateEdit->Text;
              }
            }
            DateEdit->SetFocus();
        }else if(Key==VK_ESCAPE)
        {
            Close();
            DateEdit->SetFocus();
        }
    }
    //---------------------------------------------------------------------------
    void __fastcall MonthCalendarExit(TObject *Sender)
    {
        Close();
    }
    void __fastcall  FormClose(System::TObject* Sender, TCloseAction &Action)
    {
        Action = caHide;
    }
    void __fastcall WMActivate(TMessage &Message)
    {
        TForm::Dispatch(&Message);
        if(Message.WParam == WA_INACTIVE)
        {
            PostMessage(Handle, WM_CLOSE, 0, 0);
        }
    }
    BEGIN_MESSAGE_MAP
          VCL_MESSAGE_HANDLER(WM_ACTIVATE, TMessage, WMActivate);
    END_MESSAGE_MAP(TForm);

    __fastcall TDateSelectForm()
               : TForm(Application, 0), DateEdit(NULL)
    {
        MonthCale = new TZMonthCalendar(this);
		MonthCale->Width = 260;
		MonthCale->Height = 180;
        MonthCale->Top = 0;
        MonthCale->Left = 0;

        MonthCale->OnSelect = MonthCalendarSelect;
        MonthCale->OnKeyDown = MonthCalendarKeyDown;
        MonthCale->OnExit = MonthCalendarExit;

		//Width = MonthCale->Width;
		//Height = MonthCale->Height;
        BorderStyle = bsNone;
        AutoSize = true;
        HorzScrollBar->Visible = false;
        VertScrollBar->Visible = false;
        FormStyle = fsStayOnTop;

        OnDeactivate = MonthCalendarExit;
        OnClose = FormClose;
        OnKeyDown = MonthCalendarKeyDown;
    }
    void ShowForm(TZInplaceEdit* ADateEdit)
    {
        AdjustSize();
        if(!ADateEdit)
            return;
        DateEdit = ADateEdit;
		MonthCale->Parent = this;
		MonthCale->Align=alTop;
		MonthCale->AutoSize = true;
		Width=MonthCale->Width;
		Height=MonthCale->Height;
		 Caption = DateEdit->Text;
        if(DateEdit->Text.Trim() == "")
            MonthCale->Date = MonthCale->Date.CurrentDate();
		else
        {
            try{
                MonthCale->Date = MyStrToDate(DateEdit->Text);
            }catch(...)
            {
                MonthCale->Date = MonthCale->Date.CurrentDate();
            }
        }
        if(DateEdit->ClientOrigin.y + Height + 50 > Screen->Height)
            Top = DateEdit->ClientOrigin.y - Height - 5;
        else
            Top = DateEdit->ClientOrigin.y + DateEdit->Height;
        if(DateEdit->ClientOrigin.x + Width + 50 > Screen->Width)
            Left = DateEdit->ClientOrigin.x - Width + DateEdit->Width - 5;
        else
            Left = DateEdit->ClientOrigin.x;
        Font->Assign(DateEdit->Font);
        MonthCale->Font->Assign(DateEdit->Font);
		TPoint P;
		P.x = Left;  P.y = Top;
		//P.x = ADateEdit->ClientOrigin.x;
		//P.y = ADateEdit->ClientOrigin.y+ADateEdit->Height;
		SetWindowPos(Handle, HWND_TOP, P.x, P.y, 0, 0,
		SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);        
		Show();
		Width=MonthCale->Width;
		Height=MonthCale->Height;

	}
};
TDateSelectForm* GetDateSelectForm()
{
    static TDateSelectForm* EditForm = NULL;
    if(!EditForm)
		EditForm = new TDateSelectForm();
    return EditForm;
}
class TDropGridForm : public TForm
{
public:
    TZInplaceEdit *Edit;
    TZGrid        *FGrid;
    //---------------------------------------------------------------------------
    void __fastcall MonthCalendarKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
    {
        if(Key==VK_RETURN)
        {
            Close();
            Edit->SetFocus();
        }else if(Key==VK_ESCAPE)
        {
            Close();
            Edit->SetFocus();
        }
    }
    //---------------------------------------------------------------------------
    void __fastcall FormClose(System::TObject* Sender, TCloseAction &Action)
    {
        Action = caHide;
        Edit->SetFocus();
    }
    void __fastcall WMActivate(TMessage &Message)
    {
        TForm::Dispatch(&Message);
        if(Message.WParam == WA_INACTIVE)
        {
            PostMessage(Handle, WM_CLOSE, 0, 0);
        }
    }
    BEGIN_MESSAGE_MAP
          VCL_MESSAGE_HANDLER(WM_ACTIVATE, TMessage, WMActivate);
    END_MESSAGE_MAP(TForm);
public:
    __fastcall TDropGridForm()
               : TForm(Application, 0), FGrid(NULL)
    {
        BorderStyle = bsNone;
        AutoSize = true;
        HorzScrollBar->Visible = false;
        VertScrollBar->Visible = false;
        FormStyle = fsStayOnTop;

        OnClose = FormClose;
        OnKeyDown = MonthCalendarKeyDown;
    }
    void ShowForm(TZInplaceEdit* AEdit, TZGrid* AGrid)
    {
        AdjustSize();
        if(!AEdit)
            return;
        Edit = AEdit;
        FGrid = AGrid;
        Caption = Edit->Text;
        Width = FGrid->Width;
        Height = FGrid->Height;

        if(Edit->ClientOrigin.y + Height + 50 > Screen->Height)
            Top = Edit->ClientOrigin.y - Height - 5;
        else
            Top = Edit->ClientOrigin.y + Edit->Height;
        if(Edit->ClientOrigin.x + Width + 50 > Screen->Width)
            Left = Edit->ClientOrigin.x - Width + Edit->Width - 5;
        else
            Left = Edit->ClientOrigin.x;
        Font->Assign(Edit->Font);

        FGrid->Parent = this;
        	FGrid->Visible = true;
		TPoint P;
		P.x = Left;  P.y = Top;
	   //	P.x = AEdit->ClientOrigin.x;
	   //	P.y = AEdit->ClientOrigin.y+AEdit->Height;
		SetWindowPos(Handle, HWND_TOP, P.x, P.y, 0, 0,
		SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);        
        Show();
    }
};
TDropGridForm* GetDropGridForm()
{
    static TDropGridForm* EditForm = NULL;
    if(!EditForm)
        EditForm = new TDropGridForm();
    return EditForm;
}
//---------------------------------------------------------------------------
int DayCount(String DateString)
{
    int y = DateString.SubString(1, 4).ToInt();
    int m = DateString.SubString(6, 2).ToInt();
    int daycount;
    switch(m)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            if((y % 400) == 0)
                return 29;
            else if((y % 100) == 0)
                return 28;
            else if((y % 4) == 0)
                return 29;
            else
                return 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            ;
    }
    throw  Exception("日期格式错误");
}
String ValidDay(String DateString)
{
    int day = DateString.SubString(9, 2).ToInt();
    if(day <= 28)
        return DateString;
    int daycount = DayCount(DateString);
    if(day > daycount)
        return DateString.SubString(1, 8) + IntToStr(daycount);
    return DateString;
}
#define __Grid ((TZGrid*)(Grid))
#define EmptyDate   ""
String DateToStr(TDateTime& ADate)
{
    String DateSplitter = GetDateSplitter();
    return ADate.FormatString("yyyy" + DateSplitter + "mm" + DateSplitter + "dd");
}
__fastcall TZInplaceEdit::TZInplaceEdit(Classes::TComponent* AOwner)
                          :TBYInplaceEdit(AOwner)
{
    FListButton=new TSpeedButton(this);
    FListButton->Glyph->LoadFromResourceName((int)HInstance,"GRIDDOWN");
    FListButton->Transparent=true;
    FListButton->Flat = true;
    FListButton->OnClick=ListButtonClick;
    FEditButton=new TSpeedButton(this);
    FEditButton->Glyph->LoadFromResourceName((int)HInstance,"GRIDDOT");
    FEditButton->Transparent=true;
    FEditButton->Flat = true;
    FEditButton->OnClick=ListButtonClick;
    FDropForm = new TMYPopupForm(this);
}
//---------------------------------------------------------------------------
__fastcall TZInplaceEdit::~TZInplaceEdit()
{
    delete FDropForm;
    delete FListButton;
    delete FEditButton;
}
//---------------------------------------------------------------------------
void __fastcall TZInplaceEdit::BoundsChanged(void)
{
    if(__Grid->Col >= __Grid->FixedCols && __Grid->Col < __Grid->ColCount &&
       __Grid->Row >= __Grid->FixedRows && __Grid->Row < __Grid->RowCount)
    {
        FEditColumn = __Grid->Columns->Items[__Grid->Col];
        FEditRow = __Grid->Row;

        //Color = (TColor)ColorToRGB(__Grid->SelectColor);
        //Font->Color = clWhite;//(TColor)(ColorToRGB(__Grid->SelectColor));

        if(__Grid->Mod(__Grid->ExpandGetRowIndex(__Grid->Row),2)==0)
        {
            Color = (TColor)ColorToRGB(__Grid->OddGridColor);
        }else
        {
            Color = (TColor)ColorToRGB(__Grid->EvenGridColor);
        }
        InitForEdit();
    }else
    {
        FEditColumn = NULL;
        FEditRow = -1;
    }
}
//---------------------------------------------------------------------------
void TZInplaceEdit::InitForEdit()
{
    if(!FEditColumn || FEditRow < 0)
        return;

    FListButton->Visible = false;
    FEditButton->Visible = false;
    MaxLength = FEditColumn->MaxLen;
    switch(FEditColumn->EditType)
    {
		case zNone:
            SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,0));
            break;
        case zEdit:
            MaxLength = FEditColumn->MaxLen;
            if(FEditColumn->EditButtonVisible)
            {
              FEditButton->Left = Width - 15;
              FEditButton->Top = 0;
              FEditButton->Width = 15;
              FEditButton->Height = Height;
              FEditButton->Parent = this;
              FEditButton->Cursor=crHandPoint;
              FEditButton->Visible = true;
              SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
            }
            else
                SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,0));
            break;
        case zComboList:
        case zDateTime:
        case zComboBox:
        case zDropGrid:
            FListButton->Left = Width - 15;
            FListButton->Top = 0;
            FListButton->Width = 15;
            FListButton->Height = Height;
            FListButton->Parent = this;
            FListButton->Cursor=crHandPoint;
            FListButton->Visible = true;
            SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
            break;
//         case sdMemo:
//            FMemo->Left = 0;
//            FMemo->Top = 0;
//            FMemo->Width = Width;
//            FMemo->Height = Height;
//            FMemo->MaxLength=MaxLength;
//            FMemo->Text=Text;
//            FMemo->Parent = this;
//            FMemo->Visible = true;
//            SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,0));
//            break;
        default:
			throw Exception("TZColumn EditType not defined!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TZInplaceEdit::ShowListItems(TRect ARect)
{
    if(!FEditColumn)
        return;
     TMYPopupForm  *ListPopuForm=((TMYPopupForm*)(FDropForm));
    if(FEditColumn->ListItem->Count<=0)
    {
       ListPopuForm->Height = 0;
       ListPopuForm->Width = 0;
    }
    else
    {
    FDropForm->Width = 150;
    if(FEditColumn->ListItem->Count < 8)
    {
           FDropForm->Height=ListPopuForm->ListBox->ItemHeight * FEditColumn->ListItem->Count +2;
           ListPopuForm->ListBox->Height=ListPopuForm->ListBox->ItemHeight * FEditColumn->ListItem->Count;
           FDropForm->Height = ListPopuForm->ListBox->Height + 2;
     }
    else
        FDropForm->Height = ListPopuForm->ListBox->ItemHeight * 8 + 2;
    }    
    if(FEditColumn->ListItem->Count>0)
    {
    if(ClientOrigin.y + FDropForm->Height + 50 > Screen->Height)
        FDropForm->Top = ClientOrigin.y - FDropForm->Height - 5;
    else
        FDropForm->Top = ClientOrigin.y + Height;
    if(ClientOrigin.x + FDropForm->Width + 50 > Screen->Width)
        FDropForm->Left = ClientOrigin.x - FDropForm->Width + Width;
    else
        FDropForm->Left = ClientOrigin.x;
     }
    ListPopuForm->ShowForm(FEditColumn->ListItem);
}
//---------------------------------------------------------------------------
void __fastcall TZInplaceEdit::ListButtonClick(TObject *Sender)
{
  TRect ARect(__Grid->CellRect(__Grid->Col, __Grid->Row));
  if(FEditColumn)
  {
      switch(FEditColumn->EditType)
      {
          case zComboBox:
          case zComboList:
              __Grid->DropDownForm = FDropForm;
              break;
          case zDateTime:
              __Grid->DropDownForm = GetDateSelectForm();
              break;
          case zDropGrid:
              __Grid->DropDownForm = GetDropGridForm();
              break;
      }
      if(FEditColumn->OnButtonDown)
      {
          bool DoDefault(true);
          FEditColumn->OnButtonDown(__Grid, FEditColumn, DoDefault);
          if(!DoDefault)
              return;
      }
      switch(FEditColumn->EditType)
      {
          case zComboBox:
          case zComboList:
              if(!__Grid->ReadOnly && __Grid->Columns->Count>__Grid->Col)
                  ShowListItems(ARect);
              break;
          case zDateTime:
              GetDateSelectForm()->ShowForm(this);
              break;
          case zDropGrid:
              if(FEditColumn && FEditColumn->DropGrid)
                   GetDropGridForm()->ShowForm(this, FEditColumn->DropGrid);
              break;
      }
  }
}
//---------------------------------------------------------------------------
void _fastcall TZInplaceEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
   switch(Key)
   {
       case VK_DOWN:
           /*for(int i = __Grid->Row+1; i < __Grid->RowCount; i++)
           {
               if(__Grid->RowHeights[i] > 0)
               {
                   __Grid->Row = i;
                   break;
               }
           } */
           break;
       case VK_UP:
           /*for(int i = __Grid->Row-1; i >= 0; i--)
           {
               if(__Grid->RowHeights[i] > 0)
               {
                   __Grid->Row = i;
                   break;
               }
           } */
           break;
       case VK_LEFT:
           if(SelStart == 0 && SelLength == 0)
           {
               for(int i = __Grid->Col-1; i >= 0; i--)
               {
                   if(__Grid->ColWidths[i] > 0)
                   {
                       __Grid->Col = i;
                       break;
                   }
               }
           }
           break;
       case VK_RIGHT:
           if(SelStart == Text.Length())
           {
               for(int i = __Grid->Col+1; i < __Grid->ColCount; i++)
               {
                   if(__Grid->ColWidths[i] > 0)
                   {
                       __Grid->Col = i;
                       break;
                   }
               }
           }
           break;
   }

   if(FEditColumn->EditType == zComboList&&Key==46)
       Key = 0;
   TBYInplaceEdit::KeyDown(Key,Shift);

   if(FEditColumn->EditType == zDateTime)
   {
                 switch(Key)
                 {
                     case VK_DELETE:
                         Key = 96;
                         break;
                     case VK_ESCAPE:
                         Text = FBackDate;
                         break;;
                     case VK_LEFT:
                     case VK_UP:
                         switch(SelStart)
                         {
                             case 4:
                                 SelStart = 3;
                                 break;
                             case 7:
                                 SelStart = 6;
                                 break;
                             default:
                                 ;
                         }
                         break;
                     case VK_RIGHT:
                     case VK_DOWN:
                         switch(SelStart)
                         {
                             case 4:
                                 SelStart = 5;
                                 break;
                             case 7:
                                 SelStart = 8;
                                 break;
                             default:
                                 ;
                         }
                         break;
                     default:
                         ;
                 }
   }
}
//---------------------------------------------------------------------------
void __fastcall TZInplaceEdit::KeyPress(Char &Key)
{
    if(Key==VK_RETURN)
    {
        Grid->SetFocus();
        Key = 0;
    }else if(FEditColumn->EditType == zComboList)
    {
        Key = 0;
    }else if(Key!=8 && (FEditColumn->EditType == zEdit||FEditColumn->EditType == zComboBox))
    {
        switch(FEditColumn->CharCase)
        {
            case ccUpperCase:
                Key=UpperCase(Key)[1];
                break;
            case ccLowerCase:
                Key=LowerCase(Key)[1];
                break;
        }
		if(FEditColumn->CharType != TZCharType::ctNormal)
        {
			Char* c = FEditColumn->ValidChar.c_str();
            int i=0;
            for(; i < FEditColumn->ValidChar.Length(); i++)
            {
               if(Key == *c)
                {
				  switch(FEditColumn->CharType)
                  {
					  case ctCharacter:
						  if(Key >= 48 && Key <= 57)
						  {
							  Key = 0;
						  }else if(FEditColumn->DigLen > 0 && SelStart > FEditColumn->DigLen)
						  {
							  Key = 0;
						  }else if(FEditColumn->DigLen > 0 && Text.Length() >= FEditColumn->DigLen && SelLength == 0)
						  {
							  Key = 0;
						  }
						  break;
					  case ctLetter:   //仅仅字母
						  if(Key < 65 || (Key > 90 && Key < 97) || Key > 122)
						  {
							  Key = 0;
						  }else if(FEditColumn->DigLen > 0 && SelStart > FEditColumn->DigLen)
						  {
							  Key = 0;
						  }else if(FEditColumn->DigLen > 0 && Text.Length() >= FEditColumn->DigLen && SelLength == 0)
						  {
							  Key = 0;
						  }
						  break;
					  case ctPlus:     //正整数
						  if(Key < 48 || Key > 57)
							  Key = 0;
						  break;
					  case ctNegative:  //负整数
						  if((Key < 48 || Key > 57) && Key != 45)
						  {
							  Key = 0;
						  }else if(Key == 45)
						  {// '-' 号
							  if(SelStart != 0)
							  {
								  Key = 0;
							  }else if(SelStart == 0 && Text.SubString(1,1) == "-")
							  {
								  Key = 0;
							  }
						  }else
						  {//数字
							  if(SelStart == 0 && Text.SubString(1, 1) == "-")
							  {
								  Key = 0;
							  }else
							  {
								  int bkSelStart = SelStart;
								  if(Text.SubString(1, 1) != "-")
								  {
									  Text = "-" + Text;
									  SelStart = bkSelStart + 1;
								  }
							  }
						  }
						  break;
					  case ctInteger:  //整数
						  if((Key < 48 || Key > 57) && Key != 45)
						  {
							  Key = 0;
						  }else if(Key == 45)
						  {
							  if(SelStart != 0)
							  {
								   Key = 0;
							  }else if(Text.SubString(1,1) == "-")
							  {
								   Key = 0;
							  }
						  }else if(SelStart == 0 && Text.SubString(1, 1) == "-")
						  {
							  Key = 0;
						  }
						  break;
					  case ctPlusFloat:      //正浮点数
						  if((Key < 48 || Key > 57) && Key != 46)
						  {
							  Key = 0;
						  }else if(Key == 46)
						  {// '.' 号
							  if (FEditColumn->DigLen==0) Key=0;
							  else
							  {
								int Pos = Text.Pos(".");
								if(Pos > 0)
								{
									 Key = 0;
								}else
								{
									 String Late = Text.SubString(SelStart+1, 10000);
									 if(FEditColumn->DigLen >= 0 && Late.Length() > FEditColumn->DigLen && SelLength == 0)
									 {
										 Key = 0;
									 }
								}
							  }
						  }else
						  {//数字
							  int Pos = Text.Pos(".");
							  if(Pos > 0 && FEditColumn->DigLen >= 0 && SelStart+1 > Pos && Text.Length() - Pos >= FEditColumn->DigLen)
							  {
								  Key = 0;
							  }
								  if(Pos > 0 && SelStart >= Pos)
								  {
								  }else
								  {
									  String Front;
									  if(Pos > 0)
									  {
										  Front = Text.SubString(1, Pos-1);
									  }else
									  {
										  Front = Text;
									  }
									  if((FEditColumn->MaxLen > 0 && Front.Length() >= FEditColumn->MaxLen - FEditColumn->DigLen - 1) &&
										  SelLength == 0)
									  {
										  Key = 0;
									  }
								  }
						  }
						  break;
					  case ctNegativeFloat:  //负浮点数
						  if((Key < 48 || Key > 57) && Key != 45 &&  Key != 46)
						  {
							  Key = 0;
						  }else if(Key == 45)
						  {// '-' 号
							  if(SelStart != 0)
							  {
								  Key = 0;
							  }else if(SelStart == 0 && Text.SubString(1,1) == "-")
							  {
								  Key = 0;
							  }
						  }else if(Key == 46)
						  {// '.' 号
							if (FEditColumn->DigLen==0) Key=0;
							  else
							  {
								int Pos = Text.Pos(".");
								if(Pos > 0)
								{
									 Key = 0;
								}else
								{
									 String Late = Text.SubString(SelStart+1, 10000);
									 if(FEditColumn->DigLen >= 0 && Late.Length() > FEditColumn->DigLen && SelLength == 0)
									 {
										 Key = 0;
									 }
								}
							}
						  }else
						  {//数字
							  int bkSelStart = SelStart;
							  if(SelStart == 0 && Text.SubString(1, 1) == "-")
							  {
								  Key = 0;
							  }else
							  {
								   if(Text.SubString(1, 1) != "-")
								   {
									   Text = "-" + Text;
									   SelStart = bkSelStart + 1;
								   }
								   int Pos = Text.Pos(".");
								   if(Pos > 0 && FEditColumn->DigLen >= 0 && SelStart+1 > Pos && Text.Length() - Pos >= FEditColumn->DigLen)
								   {
									   Key = 0;
								   }
								   if(Pos > 0 && SelStart >= Pos)
								   {
								   }else
								   {
									   String Front;
									   if(Pos > 0)
									   {
										   if(Text.SubString(1, 1) == "-")
										   {
											   Front = Text.SubString(2, Pos - 2);
										   }else
										   {
											   Front = Text.SubString(1, Pos-1);
										   }

									   }else
									   {
										   if(Text.SubString(1, 1) == "-")
										   {
											   Front = Text.SubString(2, 10000);
										   }else
										   {
											   Front = Text;
										   }
									   }
									   if((FEditColumn->MaxLen > 0 && Front.Length() >= FEditColumn->MaxLen - FEditColumn->DigLen - 2) &&
										  SelLength == 0)
									   {
										   Key = 0;
									   }
								   }
							  }
						  }
						  break;
					  case ctFloat:
						  if((Key < 48 || Key > 57) && Key != 45 &&  Key != 46)
						  {
							  Key = 0;
						  }else if(Key == 45)
						  {// '-' 号
							  if(SelStart != 0)
							  {
								  Key = 0;
							  }else if(SelStart == 0 && Text.SubString(1,1) == "-")
							  {
								  Key = 0;
							  }
						  }else if(Key == 46)
						  {// '.' 号
							 if (FEditColumn->DigLen==0) Key=0;
							  else
							  {
								int Pos = Text.Pos(".");
								if(Pos > 0)
								{
									 Key = 0;
								}else
								{
									 String Late = Text.SubString(SelStart+1, 10000);
									 if(FEditColumn->DigLen >= 0 && Late.Length() > FEditColumn->DigLen)
									 {
										 Key = 0;
									 }
								}
							 }
						  }else
						  {//数字
							  if(SelStart == 0 && Text.SubString(1, 1) == "-")
							  {
								  Key = 0;
							  }else
							  {
								  int Pos = Text.Pos(".");
								  if(Pos > 0 && FEditColumn->DigLen >= 0 && SelStart+1 > Pos &&
									 Text.Length() - Pos >= FEditColumn->DigLen)
								  {
									  Key = 0;
								  }
								  if(Pos > 0 && SelStart >= Pos)
								  {
								  }else
								  {
									  String Front;
									  if(Pos > 0)
									  {
										  if(Text.SubString(1, 1) == "-")
										  {
											  Front = Text.SubString(2, Pos - 2);
										  }else
										  {
											  Front = Text.SubString(1, Pos-1);
										  }

									  }else
									  {
										  if(Text.SubString(1, 1) == "-")
										  {
											  Front = Text.SubString(2, 10000);
										  }else
										  {
											  Front = Text;
										  }
									  }
									  if((FEditColumn->MaxLen > 0 && Front.Length() >= FEditColumn->MaxLen - FEditColumn->DigLen - 1) &&
										  SelLength == 0)
									  {
										  Key = 0;
									  }
								  }
							  }
						  }
						  break;
					  case ctID:             //第一个字母，以后字母,数字，"-"号
						  if(SelStart == 0)
						  {
							  if(Key < 65 || (Key > 90 && Key < 97) || Key > 122)
							  {
								  Key = 0;
							  }
						  }
						  if(FEditColumn->DigLen > 0 && SelStart > FEditColumn->DigLen)
						  {
							  Key = 0;
						  }else if(FEditColumn->DigLen > 0 && Text.Length() >= FEditColumn->DigLen && SelLength == 0)
						  {
							  Key = 0;
						  }
						  break;
					  case ctSelfDefine:   //自定义
						  if(FEditColumn->DigLen > 0 && SelStart > FEditColumn->DigLen)
						  {
							  Key = 0;
						  }else if(FEditColumn->DigLen > 0 && Text.Length() >= FEditColumn->DigLen && SelLength == 0)
						  {
							  Key = 0;
						  }
						  break;
					  default:
						  throw Exception("类型未定义！");
					 }
				 break;
				}
				c++;
			}
            if (i>=FEditColumn->ValidChar.Length())
                   Key = 0;
           }
        else if(FEditColumn->MaxLen > 0 && Text.Length() >= FEditColumn->MaxLen && SelLength == 0)
        {
            Key = 0;
        }
      }
	  TBYInplaceEdit::KeyPress(Key);

}
//---------------------------------------------------------------------------
void __fastcall TZInplaceEdit::WMKeyDown(TWMKey&Message)
{

   if(    Message.CharCode == VK_DOWN &&
          (GetKeyState(VK_LCONTROL)&0xff00 || GetKeyState(VK_RCONTROL)&0xff00) &&
          FEditColumn &&
          (FEditColumn->EditType == zDateTime ||
           FEditColumn->EditType == zComboBox ||
           FEditColumn->EditType == zComboList ||
		   FEditColumn->EditType == zDropGrid)
      )
   {
	   ListButtonClick(FListButton);
       return;
    }
  if( Message.CharCode == VK_RETURN )
   {
       TBYInplaceEdit::Dispatch(&Message);
       int r=__Grid->Row;
       int c=__Grid->Col+1;
       for(;r<__Grid->RowCount;r++)
       {
         for(;c<__Grid->ColCount;c++)
         {
           if(__Grid->Columns->Items[c]->ColumnVisible)
              goto Locate1;
         }
         c=__Grid->FixedCols;
       }
       goto  Locate2;
   Locate1:
       __Grid->Col = c;
       __Grid->Row = r;

   Locate2:
   }
   else
      TBYInplaceEdit::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZInplaceEdit::WMChar(TWMKeyUp&Message)
{
    String OldText=Text;
    if(!FEditColumn || FEditColumn->EditType != zDateTime)
    {
        TBYInplaceEdit::Dispatch(&Message);
        return;
    }
	if(FEditColumn->EditType == zComboList)
    {
        Message.Result = 0;
        return;
    }
  /*  if(FEditColumn->EditType == zDateTime)//zws 2003-12-22
    {
        Message.Result = 0;
        return;
    }
    return */; //zws 2003-12-22 不想执行下面的日期格式输入
    String DateSplitter = GetDateSplitter();
    Message.Result = 0;
    if(ReadOnly)
       return;
    char Input = Message.CharCode;

	if(Text.Trim() == "")
    {//空日期
        switch(Input)
        {
            case '0':
                break;
            case '1':
                Text = String(Input) + "999" + DateSplitter + "01" + DateSplitter + "01";
                SelStart = 1;
                break;
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                String cur = TDateTime().CurrentDate().FormatString("yyyy-mm-dd");
                Text = String(Input) + cur.SubString(2, 9);
                SelStart = 1;
                break;
            }
            default:
                break;
        }
//        TZGrid *PGrid=(TZGrid *) Grid;
//        if(PGrid&&!Text.IsEmpty()&& PGrid->OnEditControlChange) PGrid->OnEditControlChange(PGrid,PGrid->Col,PGrid->Row,Text);
        return;
    }

    int bkSelStart = SelStart;
    if(!(Input >= '0' && Input <= '9'))
        return;//输入无效

    switch(SelStart)
    {
       case 0:
       {
           String last3 = Text.SubString(2, 3);//年的后三位
           String last = Text.SubString(2, 9);//所有余下的
           switch(Input)
           {
               case '0'://不允许
                   return;
               case '1'://年必须大于 1752-10-01
               {
                   if(last3.ToInt() > 752)
                   {
                       Text = ValidDay(String(Input) + last);
                   }else
                   {
                       Text = ValidDay(String("18") + Text.SubString(3, 8));
                   }
                   break;
               }
               default:
                   Text = ValidDay(String(Input) + last);
                   break;
           }
           break;
       }
       case 1:
       {
           char y1 = Text[1];
           if(y1 == '1')
           {
               if(Input < '7')
                  return;
               if(Input > '7')
               {
                  Text = ValidDay(String(y1) + String(Input) + Text.SubString(3, 8));
                  break;
               }
               // == '7'
               if(Text.SubString(3, 2).ToInt() > 52)
                  Text = ValidDay(String(y1) + String(Input) + Text.SubString(3, 8));
               else
                  Text = ValidDay(String(y1) + String(Input) + String('6') +
                         Text.SubString(4, 7));
           }else
           {
               Text = ValidDay(String(y1) + String(Input) + Text.SubString(3, 8));
           }
           break;
       }
       case 2:
       {
           int y12 = Text.SubString(1, 2).ToInt();
           if(y12 > 17)
              Text = ValidDay(IntToStr(y12) + String(Input) + Text.SubString(4, 7));
           else if(y12 == 17)
           {
              if(Input > '5')
                 Text = ValidDay(IntToStr(y12) + String(Input) + Text.SubString(4, 7));
              else if(Input < '5')
                 return;
              else
              {
                 if(Text[4] > '2')
                 {//大于
                    Text = ValidDay(IntToStr(y12) + String(Input) + Text.SubString(4, 7));
                 }else if(Text[4] < '2')
                 {//小于
                    Text = ValidDay(IntToStr(y12) + String(Input) + String('2') +
                           Text.SubString(5, 6));
                 }else
                 {//等于
                    if(Text.SubString(6, 2).ToInt() >= 10)
                       Text = ValidDay(IntToStr(y12) + String("52") + Text.SubString(5, 6));
                    else
                       Text = ValidDay(IntToStr(y12) + String("52-10-") + Text.SubString(9, 2));
                 }
              }
           }else
              throw Exception("日期格式错误");
           break;
       }
       case 3:
       {
           int y123 = Text.SubString(1, 3).ToInt();
           if(y123 > 175)
               Text = ValidDay(IntToStr(y123) + String(Input) + Text.SubString(5, 6));
           else if(y123 == 175)
           {
              if(Input > '2')
                  Text = ValidDay(IntToStr(y123) + String(Input) + Text.SubString(5, 6));
              else if(Input < '2')
                  return;
              else
              {
                  if(Text.SubString(6, 2).ToInt() >= 10)
                     Text = ValidDay(IntToStr(y123) + String("2") + Text.SubString(5, 6));
                  else
                     Text = ValidDay(IntToStr(y123) + String("2-10-") + Text.SubString(9, 2));
              }
           }else
              throw Exception("日期格式错误");
           bkSelStart++;
           break;
       }
       case 4://  '-' 号
           break;
       case 5:
       {
           int y = Text.SubString(1, 4).ToInt();
           if(y > 1752)
           {
               switch(Input)
               {
                  case '0':
                      if(Text[7] == '0')
                         Text = ValidDay(Text.SubString(1, 5) + String(Input) + "1" +
                                Text.SubString(8, 3));
                      else
                         Text = ValidDay(Text.SubString(1, 5) + String(Input) +
                                Text.SubString(7, 4));
                      break;
                  case '1':
                      if(Text[7] > '2')
                         Text = ValidDay(Text.SubString(1, 5) + String(Input) + "0" +
                                Text.SubString(8, 3));
                      else
                         Text = ValidDay(Text.SubString(1, 5) + String(Input) +
                                Text.SubString(7, 4));
                      break;
                  default:
                      return;
               }
           }else if(y == 1752)
           {
               switch(Input)
               {
                  case '0':
                      return;
                  case '1':
                      if(Text[7] > '2')
                         Text = ValidDay(Text.SubString(1, 5) + String(Input) + "0" +
                                Text.SubString(8, 3));
                      else
                         Text = ValidDay(Text.SubString(1, 5) + String(Input) +
                                Text.SubString(7, 4));
                      break;
                  default:
                      return;
               }
           }else
               throw  Exception("日期格式错误");
           break;
       }
       case 6:
       {
           switch(Text[6])
           {
              case '0':
                  if(Input == '0')
                      return;
                  Text = ValidDay(Text.SubString(1, 6) + String(Input) +
                         Text.SubString(8, 3));
                  break;
              case '1':
                  if(Input <= '2')
                  {
                     Text = ValidDay(Text.SubString(1, 6) + String(Input) +
                            Text.SubString(8, 3));
                  }else
                      return;
                  break;
              default:
                  throw  Exception("日期格式错误");
           }
           bkSelStart++;
           break;
       }
       case 7:// '-' 号
           break;
       case 8:
       {
           int daycount = DayCount(Text);
           switch(Input)
           {
              case '0':
                  if(Text[10] == '0')
                     Text = Text.SubString(1, 8) + String(Input) + "1";
                  else
                     Text = Text.SubString(1, 8) + String(Input) + Text.SubString(10, 1);
                  break;
              case '1':
                  Text = Text.SubString(1, 8) + String(Input) + Text.SubString(10, 1);
              case '2':
                  if(daycount > 28)
                     Text = Text.SubString(1, 8) + String(Input) + Text.SubString(10, 1);
                  else
                  {
                     if(Text[10] == '9')
                        Text = Text.SubString(1, 8) + String("28");
                  }
                  break;
              case '3':
                  if(daycount >= 30)
                  {
                     if(daycount == 30)
                     {
                        Text = Text.SubString(1, 8) + String("30");
                     }else if(daycount == 31)
                     {
                        if(Text[10] == '0' || Text[10] == '1')
                           Text = Text.SubString(1, 8) + String(Input) + Text.SubString(10, 1);
                        else
                           Text = Text.SubString(1, 8) + String("30");
                     }
                  }else
                     return;
                  break;
              default:
                  return;
           }
           break;
       }
       case 9:
       {
           int daycount = DayCount(Text);
           char day1 = Text[9];
           switch(day1)
           {
               case '0':
                   if(Input == '0')
                      return;
               case '1':
                   Text = Text.SubString(1, 9) + String(Input);
                   break;
               case '2':
                   if(daycount >= 29)
                       Text = Text.SubString(1, 9) + String(Input);
                   else//  28 天
                   {
                       if(Input == '9')
                          return;
                       else
                          Text = Text.SubString(1, 9) + String(Input);
                   }
                   break;
               case '3':
                   if(daycount < 30)
                       throw  Exception("日期格式错误");
                   else if(daycount == 30)
                   {
                       if(Input == '0')
                          Text = Text.SubString(1, 8) + String("30");
                       else
                          return;
                   }else if(daycount == 31)
                   {
                       switch(Input)
                       {
                           case '0':
                           case '1':
                               Text = Text.SubString(1, 9) + String(Input);
                               break;
                           default:
                               return;
                       }
                   }else
                      throw  Exception("日期格式错误");
                   break;
           }
           break;
       }
    }
	SelStart = bkSelStart + 1;
}
//---------------------------------------------------------------------------


void __fastcall TZGrid::WMKeyDown(TWMKey & Message)
{
  int r=Row;
  int c=Col;

  switch(Message.CharCode)
  {
  case VK_RETURN:
   {
	   c=c+1;
       for(;r<RowCount;r++)
       {
        if(this->RowHeights[r]>0)
        {
           for(;c<ColCount;c++)
           {
             if(Columns->Items[c]->ColumnVisible)
                goto Locate1;
           }
         }
         c=FFixedCols;
       }
       break;
   Locate1:
       Col = c;
       Row = r;
     }
     break;
    case VK_RIGHT:
       {
		 c=c+1;
         for(;c<ColCount;c++)
         {
            if(Columns->Items[c]->ColumnVisible)
              {
               Col = c;
               return;
              }
         }
       }
     break;
    case VK_LEFT :
      {
		 c=c-1;
         for(;c>=FFixedCols;c--)
         {
            if(Columns->Items[c]->ColumnVisible)
              {
               Col = c;
               return;
              }
         }
      }
    break;
    case VK_UP:
    {

			r=r-1;
            for(;r>=FFixedRows;r--)
            {
               if(this->RowHeights[r]>0)
               {
                  Row=r;
                  return;
               }
            }
    }
    break;
    case VK_DOWN:
    {
			r=r+1;
            for(;r<RowCount;r++)
            {
               if(this->RowHeights[r]>0)
               {
                  Row=r;
                  return;
               }
            }

    }
    break;
    default:
    break;
   }
   TBYStringGrid::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZGrid::ReCalculate(int ACol, int ARow)
{
  if(ComponentState.Contains(csLoading))
     return;
  if(ACol==-1 && ARow==-1)
  {
    for (int i=0;i<ColCount;i++)
    {
     TZCalculateType fCalType=Columns->Items[i]->CalType;
     if(fCalType!=ctNone)
     {
      double value=CalcauteFootSum(i,fCalType);
      String newvalue=Format("%."+IntToStr(Columns->Items[i]->DigLen)+"f",ARRAYOFCONST((value)));
      if(FOnFormatFootText)
      {
        FOnFormatFootText(i,ARow,value,newvalue);
      }
      Columns->Items[i]->FootText=newvalue;
     }
    }
  }
  else
  {
    if(ACol>=0 && ACol<ColCount)
    {
      TZCalculateType fCalType=Columns->Items[ACol]->CalType;
      if(fCalType!=ctNone)
      {
        double value=CalcauteFootSum(ACol,fCalType);
        String newvalue=Format("%."+IntToStr(Columns->Items[ACol]->DigLen)+"f",ARRAYOFCONST((value)));
        if(FOnFormatFootText)
        {
          FOnFormatFootText(ACol,ARow,value,newvalue);
        }
        Columns->Items[ACol]->FootText=newvalue;
      }
    }
  }
  if(HasFooter && !AutoCal) Invalidate();
}

double __fastcall TZGrid::CalcauteFootSum(int ColIndex,TZCalculateType fCalType)
{
    double retvalue=0;
    switch(fCalType)
    {
     case ctSum:
       {
        for (int r=FFixedRows; r<RowCount; r++)
        {
           double celvalue=0;
		   try {
				celvalue=GetFloatFromStr(Cells[ColIndex][r]);
               }
            catch(...)
            {
               celvalue=0;
            }
          retvalue+=celvalue;
        }
       }
       return retvalue;
     case ctAvg:
       {
        int icount=0;
        for (int r=FFixedRows; r<RowCount; r++)
        {
           double celvalue=0;
           icount++;
           try {
				 celvalue=GetFloatFromStr(Cells[ColIndex][r]);
               }
            catch(...)
            {
                celvalue=0;
            }
          retvalue+=celvalue;
        }
        if(icount >0 && retvalue!=0)
          retvalue=retvalue/icount;
        else
          return 0;
       }
       return retvalue;
     case ctCount:
       retvalue=RowCount-FFixedRows;
       if(retvalue<0)
          retvalue=0;
       return retvalue;
     default:
        return 0;
    }
}
void __fastcall TZGrid::SetWarningColor(TColor value)
{
        if(FWarningColor != value) {
                FWarningColor = value;
                Invalidate();
        }
}

void __fastcall TZGrid::DeleteProperty()
{
   String myKey=GridSelfID();
   if(myKey==Name)  return;
   TRegistry *Registry = new TRegistry;
   try
   {
     try
     {
         Registry->RootKey=HKEY_CURRENT_USER;
         myKey="\\Software\\Foresight\\ZGRID\\"+myKey;
         if(Registry->KeyExists(myKey))
         {
           Registry->DeleteKey(myKey);
         }
         FReadSaveWidth = false;
         MessageBox(Handle,L"下次打开该窗体时生效！",L"提示",MB_ICONWARNING);
     }
     catch(...){}
   }
   __finally
   {
    delete Registry;
   }
}
void __fastcall TZGrid::ReadProperty()
{
  if(!FReadSaveWidth) return;

  int iCount = ColCount;
  if(iCount>Columns->Count)
    iCount = Columns->Count;

 String myKey=GridSelfID();
 if(myKey==Name)
   return;
 int dwBuffer[100000];
 TRegistry *Registry = new TRegistry;
 try{
   try{
       Registry->RootKey=HKEY_CURRENT_USER;
       myKey="\\Software\\Foresight\\ZGRID\\"+myKey;
       if(Registry->OpenKey(myKey,false))
       {
          int nCount = Registry->ReadBinaryData("ColWidths", dwBuffer, sizeof(dwBuffer)) / sizeof(int);
          if (nCount>iCount)
             nCount=iCount;
          for(int i=0;i<nCount;i++)
          {
            if(this->Columns->Items[i]->ColumnVisible)
            {
              if(dwBuffer[i]==-1 || dwBuffer[i]>2)
				ColWidths[i]=dwBuffer[i];
			  else
				ColWidths[i]=60;//DefaultColWidth;
            }
			else
			{
			   ColWidths[i]=-1;
			   this->Columns->Items[i]->HideColWidth=dwBuffer[i];
			}
          }
	   }
   }
   catch(...){}
 }
 __finally
 {
  delete Registry;
 }

}

void __fastcall TZGrid::SaveProperty()
{
  if(!FReadSaveWidth) return;

  int iCount = ColCount;
  if(iCount>Columns->Count)
	iCount = Columns->Count;

 String myKey=GridSelfID();
 if(myKey==Name)
   return;
 int* dwBuffer = new int[iCount];
 TRegistry *Registry = new TRegistry;
 try{
   try{
       Registry->RootKey=HKEY_CURRENT_USER;
	   myKey="\\Software\\Foresight\\ZGRID\\"+myKey;
       if(Registry->OpenKey(myKey,true))
       {
         for(int i=0;i<iCount;i++)
         {
		   if(this->Columns->Items[i]->ColumnVisible)
             dwBuffer[i]=ColWidths[i];
           else
			 dwBuffer[i]=this->Columns->Items[i]->HideColWidth;
         }
       }
  //     String ss="";
  //     for(int i=0;i<ColCount;i++)
  //       ss+=IntToStr(dwBuffer[i])+",";
  //
  //     Registry->WriteString("ColWD", ss);
       Registry->WriteBinaryData("ColWidths", dwBuffer, iCount * sizeof(int));
   }
   catch(...){}
 }
 __finally
 {
  delete []dwBuffer;
  delete Registry;
 }

}
//------------------------------------------------------------------------------
String __fastcall TZGrid::GridSelfID()
{
   TControl *myparent=Parent;
   String myID=Name;
   while(myparent!=NULL)
   {
     myID=myparent->Name+myID;
     myparent=myparent->Parent;
   }
   return myID;
}
//------------------------------------------------------------------------------
String __fastcall TZGrid::SetCurrRowColor(TColor AColor )
{
  if (FCurrRowColor != AColor)
  {
    FCurrRowColor = AColor;
    Invalidate();
  };
};
//------------------------------------------------------------------------------
String __fastcall TZGrid::GetRowString(int iRow)
{
  if(iRow<0 || iRow>=RowCount)
    return "";
  String Str;
  for(int iCol=0;iCol<ColCount;++iCol)
  {
    Str+=Cells[iCol][iRow]+VK_TAB;
  }
  return Str;
}
//------------------------------------------------------------------------------
void __fastcall TZGrid::SetRowString(int iRow,String value)
{
  if(iRow<0 || iRow>=RowCount)
    return;
    
  int iCol=0;
  int iTabPos=value.Pos("\t");
  while(iCol<ColCount && iTabPos>0)
  {
    Cells[iCol][iRow]=value.SubString(1,iTabPos-1);
    value=value.SubString(iTabPos+1,value.Length());

	iTabPos=value.Pos("\t");
    ++iCol;
  }
  if(!value.IsEmpty() && iCol<ColCount)
    Cells[iCol][iRow]=value;
}
//------------------------------------------------------------------------------
__fastcall TZGridEditor::TZGridEditor(TComponent*AOwner)
                        : TBYInplaceEdit(AOwner)
{
  FButton = new TSpeedButton(this);
  FButton->Glyph->LoadFromResourceName((int)HInstance,"GRIDDOWN");
  FButton->Transparent=false;
}
__fastcall TZGridEditor::~TZGridEditor()
{
  delete FButton;
}
void TZGridEditor::InitEditor(TEditType EType)
{
  switch(EType)
  {
	 case zNone:
        FButton->Visible = false;
        break;
	 case zEdit:
        FButton->Visible = false;
        break;
	 case zComboBox:
        FButton->Visible = true;
        break;
  }
}
TNotifyEvent __fastcall TZGridEditor::GetOnButtonClick()
{
  return FButton->OnClick;
}
void __fastcall TZGridEditor::SetOnButtonClick(TNotifyEvent AEvent)
{
  FButton->OnClick = AEvent;
}
