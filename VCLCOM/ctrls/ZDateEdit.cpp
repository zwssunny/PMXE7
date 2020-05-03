//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZDateEdit.h"
#pragma package(smart_init)
#pragma resource "ZVCLSR.RES"
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
#define EmptyDate   ""
static inline void ValidCtrCheck(TZDateEdit *)
{
    new TZDateEdit(NULL);
}
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
String DateToStr(TDateTime& ADate)
{
    String DateSplitter = GetDateSplitter();
    return ADate.FormatString("yyyy" + DateSplitter + "mm" + DateSplitter + "dd");
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
// TBYPopupForm
//---------------------------------------------------------------------------
void __fastcall TBYPopupForm :: MonthCalendarSelect(TObject *Sender)
    {
        Close();
        DateEdit->Text = MonthCale->Date.FormatString("yyyy-mm-dd");
        DateEdit->SetFocus();
    }
void __fastcall TBYPopupForm :: MonthCalendarClick(TObject *Sender)
    {
        if(Caption != MonthCale->Date.FormatString("yyyy-mm-dd"))
            Close();
    }
    //---------------------------------------------------------------------------
void __fastcall TBYPopupForm :: MonthCalendarKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
    {
        if(Key==VK_RETURN)
        {
            Close();
            DateEdit->Text = MonthCale->Date.FormatString("yyyy-mm-dd");
            DateEdit->SetFocus();
        }else if(Key==VK_ESCAPE)
        {
            Close();
            DateEdit->SetFocus();
        }
    }
    //---------------------------------------------------------------------------
void __fastcall TBYPopupForm :: MonthCalendarExit(TObject *Sender)
    {
		Close();
	}
void __fastcall TBYPopupForm :: FormClose(System::TObject* Sender, TCloseAction &Action)
    {
        Action = caHide;
    }
    void __fastcall TBYPopupForm :: WMActivate(TMessage &Message)
    {
        TForm::Dispatch(&Message);
        if(Message.WParam == WA_INACTIVE)
        {
            PostMessage(Handle, WM_CLOSE, 0, 0);
		}
    }
__fastcall TBYPopupForm::TBYPopupForm()
               : TForm(Application, 0), DateEdit(NULL)
    {

		Width = 260;
		Height = 200;
		BorderStyle = bsNone;
		HorzScrollBar->Visible = false;
		VertScrollBar->Visible = false;
		FormStyle = fsStayOnTop;

		MonthCale = new TZMonthCalendar(this);
		MonthCale->Parent = this;
		MonthCale->WeekNumbers=true;
		MonthCale->Align=alBottom;
		MonthCale->AutoSize = true;


		MonthCale->OnSelect = MonthCalendarSelect;
		MonthCale->OnKeyDown = MonthCalendarKeyDown;
        MonthCale->OnExit = MonthCalendarExit;

        OnDeactivate = MonthCalendarExit;
		OnClose = FormClose;
        OnKeyDown = MonthCalendarKeyDown;
    }
void TBYPopupForm :: ShowForm(TZDateEdit* ADateEdit)
    {
		AdjustSize();
		if(!ADateEdit)
			return;   
		DateEdit = ADateEdit;
		Caption = DateEdit->Date;
		Font->Assign(DateEdit->Font);
        if(DateEdit->Text.Trim() == "")
			MonthCale->Date = MonthCale->Date.CurrentDate();
        else
        {
            try{
                MonthCale->Date = MyStrToDate(DateEdit->Date);
            }catch(...)
            {
                MonthCale->Date = MonthCale->Date.CurrentDate();
            }
        }
		if(DateEdit->ClientOrigin.y + MonthCale->Height + 50 > Screen->Height)
            Top = DateEdit->ClientOrigin.y - MonthCale->Height ;
        else
            Top = DateEdit->ClientOrigin.y + DateEdit->Height;
        if(DateEdit->ClientOrigin.x + Width + 50 > Screen->Width)
            Left = DateEdit->ClientOrigin.x - Width + DateEdit->Width - 5;
        else
			Left = DateEdit->ClientOrigin.x;
		SetWindowPos(Handle, HWND_TOP, Left, Top, 0, 0,
		 SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		TRect R; //计算尺寸，不同系统风格尺寸不同
		MonthCal_GetMinReqRect(MonthCale->Handle, &R);
		Width=R.Right - R.Left;
		Height=R.Bottom - R.Top;
		Show();
}
TBYPopupForm* GetEditForm()
{
	static TBYPopupForm* EditForm = NULL;
	if(!EditForm)
		EditForm = new TBYPopupForm();
	return EditForm;
}
//---------------------------------------------------------------------------
// TZDateEdit
//---------------------------------------------------------------------------
__fastcall TZDateEdit::TZDateEdit(TComponent* Owner)
  : TCustomEdit(Owner)
{
  FDateButton=new TSpeedButton(this);
  FDateButton->Glyph->LoadFromResourceName((int)HInstance,"DATEEDIT");
  FDateButton->OnClick=ButtonClick;
  FDateButton->Cursor=crHandPoint;
  FDateButton->Top=0;
  FDateButton->Width=18;
  FDateButton->Left=Width-FDateButton->Width;
  FDateButton->Height=Height;
  FDateButton->Enabled=Enabled;
  FDateButton->Parent=this;
  FDateButton->Visible=true;
  FDateButton->Flat=true;
  FDateButton->Transparent=true;
  EditForm = new TBYPopupForm();
  FBorderColor=crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  Date=TDateTime().CurrentDate().FormatString("yyyy-mm-dd");
  FDateEditFlat = false;
}
//---------------------------------------------------------------------------
__fastcall TZDateEdit::~TZDateEdit()
{
  delete FDateButton;
  if(EditForm)
	EditForm->Close();
   //delete EditForm;
}
//---------------------------------------------------------------------------
namespace Zdateedit
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZDateEdit)};
     RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::CMMouseEnter(TMessage &Message)
{
  TCustomEdit::Dispatch(&Message);
  if(FDateEditFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
      Color=FFocusedColor;
    else
      Color=FHoverColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::CMMouseLeave(TMessage &Message)
{
  TCustomEdit::Dispatch(&Message);
  if(FDateEditFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
      Color=FFocusedColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::WMSetFocus(TWMSetFocus &Message)
{
  TCustomEdit::Dispatch(&Message);
  if(FDateEditFlat)
  {
    FIsFocused=true;
    Color=FFocusedColor;
  }
  FBackDate = Date;
  SelLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::WMKillFocus(TWMSetFocus &Message)
{
  TCustomEdit::Dispatch(&Message);
  if(FDateEditFlat)
  {
    FIsFocused=false;
    if(FIsHovered)
      Color=FHoverColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::WMPaint(TWMPaint &Message)
{
  SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
  TCustomEdit::Dispatch(&Message);
  ClearCtrlBorder(this, (TColor)ColorToRGB(FBorderColor));
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::ClearCtrlBorder(TWinControl* WinControl, TColor color)
{
  HPEN pen;
  HDC dc = GetDC(WinControl->Handle);
  if (Color&0x80000000)
  	pen = CreatePen(PS_SOLID, 1, GetPixel(dc, 1, 1));
  else
    pen = CreatePen(PS_SOLID, 1, Color);

  HPEN OldPen = (HPEN)SelectObject(dc, pen);

  POINT Points[4];
  Points[0].x = WinControl->ClientRect.Left;
  Points[0].y = WinControl->ClientRect.Bottom-1;
  Points[1].x = WinControl->ClientRect.Left;
  Points[1].y = WinControl->ClientRect.Top;
  Points[2].x = WinControl->ClientRect.Right-1;
  Points[2].y = WinControl->ClientRect.Top;
  Points[3].x = WinControl->ClientRect.Right-1;
  Points[3].y = WinControl->ClientRect.Bottom-1;
  ::Polyline(dc, Points, 4);

  ::SelectObject(dc, OldPen);
  ::DeleteObject(pen);
  ReleaseDC(WinControl->Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::WMSize(TWMSize &Message)
{
  TCustomEdit::Dispatch(&Message);
  if(FDateButton)
  {
    FDateButton->Left=Width-FDateButton->Width;
    FDateButton->Height=Height;
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::WMKeyDown(TWMKeyDown&Message)
{
   if(Message.CharCode == VK_DELETE)
   {
       Message.Result = 1;
       return;
   }
   TCustomEdit::Dispatch(&Message);
   if(Message.CharCode == VK_RETURN)
   {
       GetParentForm(this)->Perform(WM_NEXTDLGCTL,0,FALSE);
       return;
   }
   if(ReadOnly)
       return;
   switch(Message.CharCode)
   {
       case VK_DELETE:
           break;
       case VK_ESCAPE:
           Date = FBackDate;
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::WMChar(TWMKeyUp&Message)
{
    String DateSplitter = GetDateSplitter();
    Message.Result = 0;
    if(ReadOnly)
       return;
    char Input = Message.CharCode;

    if(Date.Trim() == "")
    {//空日期
        switch(Input)
        {
            case '0':
                break;
            case '1':
                Date = String(Input) + "999" + DateSplitter + "01" + DateSplitter + "01";
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
                Date = String(Input) + cur.SubString(2, 9);
                SelStart = 1;
                break;
            }
            default:
                break;
        }
        return;
    }

    int bkSelStart = SelStart;
    if(!(Input >= '0' && Input <= '9'))
        return;//输入无效
    switch(SelStart)
    {
       case 0:
       {
           String last3 = Date.SubString(2, 3);//年的后三位
           String last = Date.SubString(2, 9);//所有余下的
           switch(Input)
           {
               case '0'://不允许
                   return;
               case '1'://年必须大于 1752-10-01
               {
                   if(last3.ToInt() > 752)
                   {
                       Date = ValidDay(String(Input) + last);
                   }else
                   {
                       Date = ValidDay(String("18") + Date.SubString(3, 8));
                   }
                   break;
               }
               default:
                   Date = ValidDay(String(Input) + last);
                   break;
           }
           break;
       }
       case 1:
       {
           char y1 = Date[1];
           if(y1 == '1')
           {
               if(Input < '7')
                  return;
               if(Input > '7')
               {
                  Date = ValidDay(String(y1) + String(Input) + Date.SubString(3, 8));
                  break;
               }
               // == '7'
               if(Date.SubString(3, 2).ToInt() > 52)
                  Date = ValidDay(String(y1) + String(Input) + Date.SubString(3, 8));
               else
                  Date = ValidDay(String(y1) + String(Input) + String('6') +
                         Date.SubString(4, 7));
           }else
           {
               Date = ValidDay(String(y1) + String(Input) + Date.SubString(3, 8));
           }
           break;
       }
       case 2:
       {
           int y12 = Date.SubString(1, 2).ToInt();
           if(y12 > 17)
              Date = ValidDay(IntToStr(y12) + String(Input) + Date.SubString(4, 7));
           else if(y12 == 17)
           {
              if(Input > '5')
                 Date = ValidDay(IntToStr(y12) + String(Input) + Date.SubString(4, 7));
              else if(Input < '5')
                 return;
              else
              {
                 if(Date[4] > '2')
                 {//大于
                    Date = ValidDay(IntToStr(y12) + String(Input) + Date.SubString(4, 7));
                 }else if(Date[4] < '2')
                 {//小于
                    Date = ValidDay(IntToStr(y12) + String(Input) + String('2') +
                           Date.SubString(5, 6));
                 }else
                 {//等于
                    if(Date.SubString(6, 2).ToInt() >= 10)
                       Date = ValidDay(IntToStr(y12) + String("52") + Date.SubString(5, 6));
                    else
                       Date = ValidDay(IntToStr(y12) + String("52-10-") + Date.SubString(9, 2));
                 }
              }
           }else
              throw Exception("日期格式错误");
           break;
       }
       case 3:
       {
           int y123 = Date.SubString(1, 3).ToInt();
           if(y123 > 175)
               Date = ValidDay(IntToStr(y123) + String(Input) + Date.SubString(5, 6));
           else if(y123 == 175)
           {
              if(Input > '2')
                  Date = ValidDay(IntToStr(y123) + String(Input) + Date.SubString(5, 6));
              else if(Input < '2')
                  return;
              else
              {
                  if(Date.SubString(6, 2).ToInt() >= 10)
                     Date = ValidDay(IntToStr(y123) + String("2") + Date.SubString(5, 6));
                  else
                     Date = ValidDay(IntToStr(y123) + String("2-10-") + Date.SubString(9, 2));
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
           int y = Date.SubString(1, 4).ToInt();
           if(y > 1752)
           {
               switch(Input)
               {
                  case '0':
                      if(Date[7] == '0')
                         Date = ValidDay(Date.SubString(1, 5) + String(Input) + "1" +
                                Date.SubString(8, 3));
                      else
                         Date = ValidDay(Date.SubString(1, 5) + String(Input) +
                                Date.SubString(7, 4));
                      break;
                  case '1':
                      if(Date[7] > '2')
                         Date = ValidDay(Date.SubString(1, 5) + String(Input) + "0" +
                                Date.SubString(8, 3));
                      else
                         Date = ValidDay(Date.SubString(1, 5) + String(Input) +
                                Date.SubString(7, 4));
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
                      if(Date[7] > '2')
                         Date = ValidDay(Date.SubString(1, 5) + String(Input) + "0" +
                                Date.SubString(8, 3));
                      else
                         Date = ValidDay(Date.SubString(1, 5) + String(Input) +
                                Date.SubString(7, 4));
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
           switch(Date[6])
           {
              case '0':
                  if(Input == '0')
                      return;
                  Date = ValidDay(Date.SubString(1, 6) + String(Input) +
                         Date.SubString(8, 3));
                  break;
              case '1':
                  if(Input <= '2')
                  {
                     Date = ValidDay(Date.SubString(1, 6) + String(Input) +
                            Date.SubString(8, 3));
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
           int daycount = DayCount(Date);
           switch(Input)
           {
              case '0':
                  if(Date[10] == '0')
                     Date = Date.SubString(1, 8) + String(Input) + "1";
                  else
                     Date = Date.SubString(1, 8) + String(Input) + Date.SubString(10, 1);
                  break;
              case '1':
                  Date = Date.SubString(1, 8) + String(Input) + Date.SubString(10, 1);
              case '2':
                  if(daycount > 28)
                     Date = Date.SubString(1, 8) + String(Input) + Date.SubString(10, 1);
                  else
                  {
                     if(Date[10] == '9')
                        Date = Date.SubString(1, 8) + String("28");
                  }
                  break;
              case '3':
                  if(daycount >= 30)
                  {
                     if(daycount == 30)
                     {
                        Date = Date.SubString(1, 8) + String("30");
                     }else if(daycount == 31)
                     {
                        if(Date[10] == '0' || Date[10] == '1')
                           Date = Date.SubString(1, 8) + String(Input) + Date.SubString(10, 1);
                        else
                           Date = Date.SubString(1, 8) + String("30");
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
           int daycount = DayCount(Date);
           char day1 = Date[9];
           switch(day1)
           {
               case '0':
                   if(Input == '0')
                      return;
               case '1':
                   Date = Date.SubString(1, 9) + String(Input);
                   break;
               case '2':
                   if(daycount >= 29)
                       Date = Date.SubString(1, 9) + String(Input);
                   else//  28 天
                   {
                       if(Input == '9')
                          return;
                       else
                          Date = Date.SubString(1, 9) + String(Input);
                   }
                   break;
               case '3':
                   if(daycount < 30)
                       throw  Exception("日期格式错误");
                   else if(daycount == 30)
                   {
                       if(Input == '0')
                          Date = Date.SubString(1, 8) + String("30");
                       else
                          return;
                   }else if(daycount == 31)
                   {
                       switch(Input)
                       {
                           case '0':
                           case '1':
                               Date = Date.SubString(1, 9) + String(Input);
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
int TZDateEdit::DayCount(String DateString)
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
//---------------------------------------------------------------------------
String TZDateEdit::ValidDay(String DateString)
{
    int day = DateString.SubString(9, 2).ToInt();
    if(day <= 28)
       return DateString;
    int daycount = DayCount(DateString);
    if(day > daycount)
       return DateString.SubString(1, 8) + IntToStr(daycount);
    return DateString;
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::DrawDateEditFlat()
{
  if(!FIsHovered && !FIsFocused)
    ParentColor=true;
  HBRUSH brush;
  TRect FRect;
  HDC dc = GetDC(Handle);
  brush=CreateSolidBrush(ColorToRGB(FBorderColor));
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FRect.Left=ClientRect.Left;
  FRect.Top=ClientRect.Top;
  FRect.Right=ClientRect.Right;
  FRect.Bottom=ClientRect.Bottom;
  FrameRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);
  ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::ButtonClick(TObject *Sender)
{
  if(FOnButtonClick)
     FOnButtonClick(this);
  if(ReadOnly)
     return;
  if(Enabled && Visible)
  {
	// GetEditForm()->ShowForm(this);
	EditForm->ShowForm(this);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetBorderColor(TColor value)
{
  FBorderColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetHoverColor(TColor value)
{
  FHoverColor=value;
  this->Repaint();
}
//---------------------------------------------------------------------------
String __fastcall TZDateEdit::GetDate()
{
  if(TCustomEdit::Text.Trim() == "")
     return "";
  try
  {
   return MyStrToDate(TCustomEdit::Text).FormatString("yyyy-mm-dd");
  }
  catch(...)
  {
   return "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetDate(String value)
{
  if(value.Trim() == "")
  {
     TCustomEdit::Text = "";
     return;
  }
  String s;
  try
  {
	 s = MyStrToDate(value).FormatString("yyyy-mm-dd");
     TCustomEdit::Text = s;
  }catch(Exception &e)
  {
     if(value.Trim() == "")
        TCustomEdit::Text = "";
     else
        throw Exception("您输入的日期不正确.");
  }
}
//---------------------------------------------------------------------------
bool __fastcall TZDateEdit::GetButtonFlat()
{
  return FDateButton->Flat;
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetButtonFlat(bool value)
{
  FDateButton->Flat = value;
}
//---------------------------------------------------------------------------
bool __fastcall TZDateEdit::GetButtonTransparent()
{
  return FDateButton->Transparent;
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetButtonTransparent(bool value)
{
  FDateButton->Transparent=value;
}
//---------------------------------------------------------------------------
void __fastcall TZDateEdit::SetDateEditFlat(bool value)
{
  FDateEditFlat=value;
  if(value)
     Ctl3D=false;
  Repaint();
}
//---------------------------------------------------------------------------

