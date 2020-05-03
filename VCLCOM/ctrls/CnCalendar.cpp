//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CnCalendar.h"
#include "ZcnDate.hpp"
#include "vclComFunc.h"
#include "SysUtils.hpp"
#pragma package(smart_init)

//#pragma resource "CNCALENDAR.res"

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TCnCalendar *)
{
        new TCnCalendar(NULL);
}
namespace Cncalendar
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TCnCalendar)};
				 RegisterComponents("ZAdditional", classes, 0);
        }
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------
__fastcall TCnCalendar::TCnCalendar(TComponent* Owner)
        : TCustomControl(Owner)
{
   Width = 315;
   Height = 165;
   BorderWidth = 2;
   FTopHeight = 25;
   FTopFont = new TFont();
   Date = Date.CurrentDateTime();
   FTopColor = (TColor)0x00D9CDC1;
   Color = (TColor)0x00FFFAEE;
   FCnColor = clGreen;
   FOtherMonthDayColor = (TColor)0x00E393AD;
   FOddColor = (TColor)0x00FDCAD1;
   FEvenColor = (TColor)0x00F0F3B6;
   FWeekColor = (TColor)0x00F083F3;

   FLeftButton = new TSpeedButton(this);
   FLeftButton->Parent = this;
   FLeftButton->OnClick = PMonth;
   FRightButton = new TSpeedButton(this);
   FRightButton->Parent = this;
   FRightButton->OnClick = NMonth;
   FLeftButton->Glyph->Handle = LoadBitmap(HInstance, L"MOVELEFT");
   FRightButton->Glyph->Handle = LoadBitmap(HInstance, L"MOVERIGHT");
   FLeftButton->Flat = true;
   FRightButton->Flat = true;

   FYearEdit = NULL;
   FYearUpDown = NULL;
   PopupMonth = new TPopupMenu(this);
   PopupMonth->AutoHotkeys=maManual;
   TMenuItem *NewItem ;
   for(int index=1; index<=12; index++)
   {
      NewItem = new TMenuItem(PopupMonth);
      NewItem->Caption = IntToStr(index)+" 月";
      NewItem->Tag = index;
      NewItem->OnClick = PopupMenuItemsClick;
      PopupMonth->Items->Add(NewItem);
   }
}
__fastcall TCnCalendar::~TCnCalendar()
{
   delete FTopFont;
   if(FYearEdit)
      delete FYearEdit;
   if(FYearUpDown)
      delete FYearUpDown;
}
void __fastcall TCnCalendar::SetCurrDate(TDate ADate)
{
   FDateTime = ADate;
   SetDisplayDate(ADate);
}
void __fastcall TCnCalendar::SetDisplayDate(TDate ADate)
{
   FDisplayDate = ADate;
   unsigned short Year, Month, Day;
   ADate.DecodeDate(&Year, &Month, &Day);
   FFirstDate = ADate;
   FFirstDate = int(FFirstDate) - Day + 1;
   FFirstDate = int(FFirstDate) - FFirstDate.DayOfWeek() + 1;
   Repaint();
}
void __fastcall TCnCalendar::SetTopFont(TFont* AFont)
{
   FTopFont->Assign(AFont);
   Repaint();
}
void __fastcall TCnCalendar::SetCnColor(TColor AColor)
{
   FCnColor = AColor;
   Repaint();
}
void __fastcall TCnCalendar::Paint(void)
{
   int ARowHeight = (Height-FTopHeight)/8;
   int AColWidth = Width / 7;
   DrawTop();
   for(int i = 1; i <= 7; i++)
      DrawAWeek(i, TRect((i-1)*AColWidth, FTopHeight+1, i*AColWidth, FTopHeight+ARowHeight));
   TDate draw = FFirstDate;
   unsigned short Year, Month, Day;
   FDisplayDate.DecodeDate(&Year, &Month, &Day);
   for(int i = 0; i < 6; i++)
   for(int j = 0; j < 7; j++)
   {
      DrawADate(draw, Month, TRect(j*AColWidth, FTopHeight+ARowHeight*(i+1),
                       (j+1)*AColWidth, FTopHeight+ARowHeight*(i+2)));
      draw++;
   }
   DrawBottom(ARowHeight);          
}
void __fastcall TCnCalendar::SetTopColor(TColor AColor)
{
   FTopColor = AColor;
   Repaint();
}
void __fastcall TCnCalendar::SetOtherMonthDayColor(TColor AColor)
{
   FOtherMonthDayColor = AColor;
   Repaint();
}
void __fastcall TCnCalendar::SetOddColor(TColor AColor)
{
   FOddColor = AColor;
   Repaint();
}
void __fastcall TCnCalendar::SetEvenColor(TColor AColor)
{
   FEvenColor = AColor;
   Repaint();
}
void __fastcall TCnCalendar::SetWeekColor(TColor AColor)
{
   FWeekColor = AColor;
   Repaint();
}
void __fastcall TCnCalendar::DrawTop()
{
   RECT dr;
   dr.left = 0; dr.top = 0; dr.right = Width; dr.bottom = FTopHeight;
   Canvas->Brush->Color = FTopColor;
   Canvas->FillRect(dr);
   unsigned short Year, Month, Day;
   FDisplayDate.DecodeDate(&Year, &Month, &Day);
   Canvas->Font->Assign(FTopFont);
   String str = IntToStr(Year)+"年"+IntToStr(Month)+"月";
   DrawText(Canvas->Handle, str.c_str(), str.Length(), &dr, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
   Canvas->Pen->Color = clBlack;
   Canvas->Pen->Width = 1;
   Canvas->MoveTo(dr.left, dr.bottom);
   Canvas->LineTo(dr.right, dr.bottom);
}
void __fastcall TCnCalendar::DrawBottom(int BHeight)
{
   RECT dr;
   dr.left = 0;
   dr.top = ClientHeight-BHeight;
   dr.right = ClientWidth;
   dr.bottom = ClientHeight;
   Canvas->Brush->Color = FTopColor;//Color;
   Canvas->FillRect(dr);
   Canvas->Pen->Color = clBlack;
   Canvas->Pen->Width = 1;
   Canvas->MoveTo(0, dr.top);
   Canvas->LineTo(Width, dr.top);
   Canvas->Font->Assign(Font);
   Canvas->Font->Assign(Font);
   SetTextAlign(Canvas->Handle, TA_LEFT);
   Canvas->TextOut(5, dr.top+2, "今天："+TDateTime().CurrentDate().DateString());
   SetTextAlign(Canvas->Handle, TA_RIGHT);
   Canvas->TextOut(dr.right-5, dr.top+2, "当前："+Date.DateString());
}
void __fastcall TCnCalendar::DrawADate(TDate ADate, BYTE CurrMonth, TRect ARect)
{
    if(ADate.DayOfWeek() % 2)
	{
       Canvas->Brush->Color = FOddColor;
    }else
       Canvas->Brush->Color = FEvenColor;
    Canvas->FillRect(ARect);
    unsigned short Year, Month, Day;
	ADate.DecodeDate(&Year, &Month, &Day);
    Canvas->Font->Assign(Font);
    if(CurrMonth != Month)
       Canvas->Font->Color = FOtherMonthDayColor;
    SetTextAlign(Canvas->Handle, TA_CENTER);
    int AInc = (ARect.Right - ARect.Left) / 4;
    int tHeight = Canvas->TextHeight("星期");
    tHeight = (ARect.Top + ARect.Bottom - tHeight) / 2;
    Canvas->TextOut(ARect.Left+AInc, tHeight, IntToStr(Day));
    int bkFSize = Canvas->Font->Size;
    TColor bkColor = Canvas->Font->Color;
    Canvas->Font->Size = bkFSize - 1;
    if(CurrMonth != Month)
       Canvas->Font->Color = FOtherMonthDayColor;
    else
       Canvas->Font->Color = FCnColor;
    tHeight = Canvas->TextHeight("星期");
    tHeight = (ARect.Top + ARect.Bottom - tHeight) / 2;

	if(Holiday(ADate).Trim() == "")
	{
		if(CnDayOfDateJr(ADate).Trim() == "")
		{
			if(GetLunarHolDay(ADate).Trim() == "")
			{
				if(CnDayOfDate(ADate) != "初一")
				   Canvas->TextOut(ARect.Left+AInc * 3, tHeight, CnDayOfDate(ADate));
				else
				   Canvas->TextOut(ARect.Left+AInc * 3, tHeight, CnMonthOfDate(ADate));
			}
			else
				Canvas->TextOut(ARect.Left+AInc * 3, tHeight, GetLunarHolDay(ADate));
		}
		else
			Canvas->TextOut(ARect.Left+AInc * 3, tHeight, CnDayOfDateJr(ADate));
	}
	else
		Canvas->TextOut(ARect.Left+AInc * 3, tHeight, Holiday(ADate));

    Canvas->Font->Size = bkFSize;
    Canvas->Font->Color = bkColor;
    if(int(ADate) == int(Date))
    {
       HRGN rgn = CreateEllipticRgn(ARect.Left, ARect.Top, ARect.Right, ARect.Bottom);
       InvertRgn(Canvas->Handle, rgn);
       DeleteObject(rgn);
	}
}
void __fastcall TCnCalendar::DrawAWeek(int Week, TRect ARect)
{
   Canvas->Brush->Color = WeekColor;
   Canvas->FillRect(ARect);
   Canvas->Font->Assign(Font);
   SetTextAlign(Canvas->Handle, TA_CENTER);
   int tHeight = Canvas->TextHeight("星期");
   tHeight = (ARect.Top + ARect.Bottom - tHeight) / 2;
   switch(Week)
   {
      case 1:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期日");
         break;
      case 2:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期一");
         break;
      case 3:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期二");
         break;
      case 4:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期三");
         break;
      case 5:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期四");
         break;
      case 6:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期五");
         break;
      case 7:
         Canvas->TextRect(ARect, (ARect.Left+ARect.Right)/2, tHeight, "星期六");
         break;
   }
}
void __fastcall TCnCalendar::PMonth(System::TObject* Sender)
{
   SetDisplayDate(FDisplayDate-31);
}
void __fastcall TCnCalendar::NMonth(System::TObject* Sender)
{
   SetDisplayDate(FDisplayDate+31);
}
void __fastcall TCnCalendar::AdjustClientRect(TRect &Rect)
{
   TCustomControl::AdjustClientRect(Rect);
   FLeftButton->Top = FTopHeight / 2 - FLeftButton->Height / 2;
   FRightButton->Top = FLeftButton->Top;
   FLeftButton->Left = Width / 5 - FLeftButton->Width;
   FRightButton->Left = Width / 5 * 4;
}
void __fastcall TCnCalendar::AdjustRect()
{
   FLeftButton->Top = FTopHeight / 2 - FLeftButton->Height / 2;
   FRightButton->Top = FLeftButton->Top;
   FLeftButton->Left = Width / 5;
   FRightButton->Left = Width / 5 * 4;
   Repaint();
}
POINT __fastcall TCnCalendar::MousePos()
{
   POINT p;
   GetCursorPos(&p);
   p.x = p.x - ClientOrigin.x;
   p.y = p.y - ClientOrigin.y;
   return p;
}
void __fastcall TCnCalendar::Click(void)
{
   delete FYearUpDown;
   FYearUpDown = NULL;
   delete FYearEdit;
   FYearEdit = NULL;
   POINT MouseP = MousePos();
   if(MouseP.y < FTopHeight)
   {
      TopClick();
	  return;
   }
   if(int((MouseP.y-FTopHeight)/((Height-FTopHeight)/8))-1>5)
   {
      BottomClick();
      return;
   }
   int ARowHeight = (Height-FTopHeight)/8;
   DayClick(int((MouseP.y-FTopHeight)/ARowHeight)-1, int(MouseP.x / (Width/7))-1);
}
void __fastcall TCnCalendar::DayClick(int Row, int Col)
{
   TDate d = FFirstDate + Row * 7 + Col + 1;
   Date = d;
   if(FOnChange)
      FOnChange(this);
}
void __fastcall TCnCalendar::BottomClick()
{
   int iwidth = Canvas->TextWidth("今天："+TDateTime().CurrentDate().DateString());
   POINT p = MousePos();
   if(p.x < iwidth+8)
   {
      SetDisplayDate(FDisplayDate.CurrentDateTime());
   }else
   {
      iwidth = Canvas->TextWidth("当前："+Date.DateString());
      if(p.x>Width-iwidth-8 - BorderWidth)
        SetDisplayDate(Date);
   }
}
//---------------------------------------------------------------------------
void __fastcall TCnCalendar::TopClick()
{

   POINT p = MousePos();
   int yearwidth  = Canvas->TextWidth("2000年");
   int mouthwidth = Canvas->TextWidth("12月");
   int ileft   = (Width-yearwidth-mouthwidth)/2;
   int imiddle = ileft+yearwidth;
   int iright  = imiddle+mouthwidth;
   if(p.x >= ileft-1 && p.x<=imiddle)
   {
      FYearEdit = new TMaskEdit(this);
      FYearUpDown = new TUpDown(this);
      FYearUpDown->Min = 0;
      FYearUpDown->Max = 9999;

      FYearEdit->Left = ileft;
      FYearEdit->Top  = (FTopHeight-FYearEdit->Height)/2;
      FYearEdit->Width = yearwidth;
      FYearUpDown->Left = FYearEdit->Left + FYearEdit->Width + 2;
      FYearUpDown->Top = FYearEdit->Top;
      FYearUpDown->Thousands = false;
      FYearEdit->ReadOnly = true;
      FYearUpDown->OnChangingEx = YearUpDownChanging;
      FYearEdit->Color = FTopColor;
      FYearEdit->Parent = this;
      FYearUpDown->Parent = this;
      FYearUpDown->Associate = FYearEdit;
      //给编辑控间赋值
      unsigned short Year, Month, Day;
      FDisplayDate.DecodeDate(&Year, &Month, &Day);
      FYearEdit->Text = IntToStr(Year);
      FYearUpDown->Position = Year;
   }
   else if ((p.x>imiddle) && (p.x<iright))
   {
      PopupMonth->Popup(iright-5 + ClientOrigin.x, ClientOrigin.y);
   }
}
void __fastcall TCnCalendar::PopupMenuItemsClick(TObject *Sender)
{
    TMenuItem *ClickedItem = dynamic_cast<TMenuItem *>(Sender);
    if (ClickedItem)
    {
      Word Year, Month, Day;
      DecodeDate(FDisplayDate,Year, Month, Day);
      if(Month!=ClickedItem->Tag)
      {
        Month = ClickedItem->Tag;
        TDateTime dt = EncodeDate(Year, Month, Day);
        SetDisplayDate(dt);
      }
    }
}
void __fastcall TCnCalendar::YearUpDownChanging(System::TObject
                         * Sender, bool &AllowChange, int NewValue, TUpDownDirection Direction)
{
    unsigned short Year, Month, Day;
    FDisplayDate.DecodeDate(&Year, &Month, &Day);
    TDateTime bkDisplayDate(FDisplayDate);
    try
    {
       SetDisplayDate(TDateTime(IntToStr(NewValue) + "-" + IntToStr(Month) + "-" + IntToStr(Day)));
       AllowChange = true;
       Repaint();
    }catch(...)
    {
       AllowChange = false;
    }
}


