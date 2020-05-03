//---------------------------------------------------------------------------
// 任务日历/计划编排组件  PrjCalendar.cpp
//---------------------------------------------------------------------------
// Calendar Planning Component for HYWY CPM  Series
// Created by Sunny Zhan,  2002
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrjCalendar.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TPrjCalendarPanel *)
{
        new TPrjCalendarPanel(NULL);
}
//---------------------------------------------------------------------------
bool TryEncodeDateTime(Word AYear, Word AMonth, Word ADay, Word AHour, Word AMinute, Word ASecond,
  Word AMilliSecond,TDateTime &AValue)
{
  try
  {
    TDateTime LTime;
    AValue = EncodeDate(AYear, AMonth, ADay);
    LTime =  EncodeTime(AHour, AMinute, ASecond, AMilliSecond);
    AValue = AValue + LTime;
    return true;
  }
  catch(...)
  {
    return false;
  }
}
//---------------------------------------------------------------------------
void DecodeDateTime(TDateTime AValue, Word &AYear, Word &AMonth, Word &ADay,
  Word &AHour, Word &AMinute, Word &ASecond, Word &AMilliSecond)
{
  DecodeDate(AValue, AYear, AMonth, ADay);
  DecodeTime(AValue, AHour, AMinute, ASecond, AMilliSecond);
}
//---------------------------------------------------------------------------
bool TryRecodeDateTime(TDateTime AValue, Word AYear, Word AMonth, Word ADay,
  Word AHour, Word AMinute, Word ASecond, Word AMilliSecond, TDateTime &AResult)
{
  Word LYear, LMonth, LDay, LHour, LMinute, LSecond, LMilliSecond;
  DecodeDateTime(AValue, LYear, LMonth, LDay,
                         LHour, LMinute, LSecond, LMilliSecond);
  if(AYear!=RecodeLeaveFieldAsIs) LYear = AYear;
  if(AMonth != RecodeLeaveFieldAsIs) LMonth = AMonth;
  if(ADay != RecodeLeaveFieldAsIs)LDay = ADay;
  if(AHour != RecodeLeaveFieldAsIs) LHour = AHour;
  if(AMinute != RecodeLeaveFieldAsIs) LMinute = AMinute;
  if(ASecond != RecodeLeaveFieldAsIs) LSecond = ASecond;
  if(AMilliSecond != RecodeLeaveFieldAsIs) LMilliSecond = AMilliSecond;
  return TryEncodeDateTime(LYear, LMonth, LDay,
                              LHour, LMinute, LSecond, LMilliSecond, AResult);
}
//---------------------------------------------------------------------------
TDateTime RecodeDateTime(TDateTime AValue,  Word AYear, Word AMonth, Word ADay,
  Word AHour, Word AMinute, Word ASecond, Word AMilliSecond)
{
  TDateTime AResult;
  if(!TryRecodeDateTime(AValue, AYear, AMonth, ADay,
                           AHour, AMinute, ASecond, AMilliSecond, AResult))
  {
    ShowMessage("ERROR");
    return 0;
  }
  else return AResult;
}
//---------------------------------------------------------------------------
TDateTime RecodeDate(TDateTime AValue,unsigned short AYear, unsigned short AMonth,
  unsigned short ADay)
{
  return RecodeDateTime(AValue, AYear, AMonth, ADay, RecodeLeaveFieldAsIs,
    RecodeLeaveFieldAsIs, RecodeLeaveFieldAsIs, RecodeLeaveFieldAsIs);
}
//---------------------------------------------------------------------------
TDateTime RecodeTime(TDateTime AValue,Word AHour, Word AMinute, Word ASecond,
  Word AMilliSecond)
{
  return RecodeDateTime(AValue, RecodeLeaveFieldAsIs, RecodeLeaveFieldAsIs,
    RecodeLeaveFieldAsIs, AHour, AMinute, ASecond, AMilliSecond);
}
//---------------------------------------------------------------------------
TDateTime EndOfTheDay(TDateTime AValue)
{
  return RecodeTime(AValue, 23, 59, 59, 999);
}
//---------------------------------------------------------------------------
TDateTime StartOfAMonth(unsigned short &AYear, unsigned short &AMonth)
{
  return EncodeDate(AYear, AMonth, 1);
}
//---------------------------------------------------------------------------
Word DaysInAMonth(Word AYear, Word AMonth)
{
  return MonthDays[(AMonth == 2) && IsLeapYear(AYear)][AMonth];
}
//---------------------------------------------------------------------------
TDateTime EndOfAMonth(unsigned short &AYear, unsigned short &AMonth)
{
  return EndOfTheDay(EncodeDate(AYear, AMonth, DaysInAMonth(AYear, AMonth)));
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
namespace Prjcalendar
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TPrjCalendarPanel)};
				 RegisterComponents("ZChart", classes, 0);
        }
}
//---------------------------------------------------------------------------
//  TCalendarGrid  Class
//---------------------------------------------------------------------------
__fastcall TCalendarGrid::TCalendarGrid(TComponent* Owner)
        : TCustomGrid(Owner)
{
	EditBox = new TZEdit(this);
    EditBox->Visible=false;
    EditBox->Top=-20;
    EditBox->Parent = this;
    EditBox->Height = 18;
    EditBox->Ctl3D = false;
    EditBox->Flat=true;
    EditBox->DigLen=4;
	EditBox->CharType=ctFloat;
    EditBox->OnKeyDown = EditKeyDown;
    EditBox->Font->Color = clBlack;
    EditBox->Color = clWhite;
    DoubleBuffered = true;
    DailyPlans = new TList;
}

__fastcall TCalendarGrid::~TCalendarGrid()
{
  if(DailyPlans)
  {
    for(int i=0;i<=DailyPlans->Count-1;i++)
    {
      if(DailyPlans->Items[i])
        delete DailyPlans->Items[i];
    }
    delete DailyPlans;
  }
  delete EditBox;
}
//---------------------------------------------------------------------------
TRect __fastcall TCalendarGrid::CellRect(int ACol, int ARow)
{
  return TCustomGrid::CellRect(ACol,ARow);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::DrawCell(int ACol, int ARow,
                          const TRect &ARect, TGridDrawState AState)
{
  int ox,oy,x,y;
  String DayStr,CnDayStr;
  Word AYear,AMonth,ADay;
  TRect TitleRect;
  try
  {
    DecodeDate(Dates[ACol][ARow],AYear,AMonth,ADay);
    if(ADay == 1)
      DayStr = IntToStr(AMonth) + "月" + IntToStr(ADay) + "日";
    else
	  DayStr = FormatDateTime("d",Dates[ACol][ARow]);

	if(Holiday(Dates[ACol][ARow]).Trim() == "")
	{
		if(CnDayOfDateJr(Dates[ACol][ARow]).Trim() == "")
		{
			if(GetLunarHolDay(Dates[ACol][ARow]).Trim() == "")
				CnDayStr = CnDayOfDate(Dates[ACol][ARow]);
			else
				CnDayStr = GetLunarHolDay(Dates[ACol][ARow]);
		}
		else
			CnDayStr = CnDayOfDateJr(Dates[ACol][ARow]);
	}
	else
		CnDayStr = Holiday(Dates[ACol][ARow]);

    ox = 1;
    oy = 1;
    x = ARect.Left + ox;
    y = ARect.Top + oy;
	if(ACol == 0 || ACol ==6)  //周末
    {
      Canvas->Brush->Color = FTaskRestColor;
      Canvas->FillRect(ARect);
      Canvas->Font->Color = FTextColor;
    }
    else  //正常
    {
      Canvas->Brush->Color = FBackColor;
      Canvas->FillRect(ARect);
      Canvas->Font->Color = FTextColor;
    }
    if(Dates[ACol][ARow] == FDate)  //当前
    {
      Canvas->Brush->Color = FSelectedBackColor;
      Canvas->FillRect(ARect);
      Canvas->Font->Color = FSelectedTextColor;
    }
	//
    TitleRect = TRect(ARect.Left,ARect.Top,ARect.Right,ARect.Top+13);
    Canvas->Brush->Color = FTitleBackColor;
    Canvas->FillRect(TitleRect);
    Canvas->Font->Color = FTitleTextColor;
    Canvas->Font->Style = Canvas->Font->Style << fsBold;
    Canvas->TextOut(x,y,DayStr);
    Canvas->Font->Style  = Canvas->Font->Style >> fsBold;
    Canvas->TextOut(ARect.Right-Canvas->TextWidth(CnDayStr),y,CnDayStr);  //农历
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------
//绘制任务计划
void __fastcall TCalendarGrid::PaintTaskPlan()
{
  if(!DailyPlans) return;
  if(DailyPlans->Count == 0) return;
  TDailyPlanData *APlan;
  //得到计划数据开始日期和结束日期
  APlan = (TDailyPlanData *)DailyPlans->Items[0];
  PlanStartDate = APlan->Date;
  APlan = (TDailyPlanData *)DailyPlans->Items[DailyPlans->Count-1];
  PlanEndDate = APlan->Date;

  if(PlanEndDate<FPageStartDate) return; //over range
  if(PlanStartDate>FPageEndDate) return;

  int i,j;
  int col,row,c,tx,ty;
  if(PlanStartDate >= FPageStartDate)
  {
    row = (int)(PlanStartDate - FPageStartDate) / 7;
    col = (int)(PlanStartDate - FPageStartDate) % 7;
    c = 0;
  }
  else
  {
    row = 0;
    col = 0;
    c = FPageStartDate - PlanStartDate;
  }
  double AValue;
  TWorkDayType ADayType;
  TRect r,r1;
  for(i = col ; i <= 6 ; i++)
  {
      APlan = (TDailyPlanData *)DailyPlans->Items[c];
      AValue = APlan->Value;
      ADayType = APlan->DayType;
      r = this->CellRect(i,row);
      r1 = TRect(r.Left,r.Top+13,r.Right,r.Bottom);
      Canvas->Font->Color = FTextColor;
      Canvas->Font->Name = "宋体";
      Canvas->Font->Size = 9;
      switch(ADayType)
      {
        case dtNormal:
          Canvas->Brush->Color = FTaskColor;
          Canvas->FillRect(r1);
          break;
        case dtWeekEnd:
          Canvas->Brush->Color = FTaskRestColor;
          Canvas->FillRect(r1);
          break;
        case dtCompleted:
          Canvas->Font->Color = FCompTextColor;
          Canvas->Brush->Color = FCompBackColor;
          Canvas->FillRect(r1);
          break;
      }
      if(FSelList.count(Dates[i][row])>0)
      {
        Canvas->Brush->Color = FSelectedBackColor;
        Canvas->FillRect(r1);
        Canvas->Font->Color = FSelectedTextColor;
      }
      tx = r.Left + 2;
      ty =  r.Top + (r.Height()-EditBox->Height/2)/2;//r.Top + 15;
      if(EditBox->DigLen>0)
        Canvas->TextOut(tx,ty,Format("%."+IntToStr(EditBox->DigLen)+"f",ARRAYOFCONST((AValue))));
      else
        Canvas->TextOut(tx,ty,AValue);
      if(c==DailyPlans->Count-1) return;
      c++;
  }
  for(j = row + 1; j <= 5; j++)
    for(i = 0 ; i <= 6; i++)
    {
      APlan = (TDailyPlanData *)DailyPlans->Items[c];
      AValue = APlan->Value;
      ADayType = APlan->DayType;
      r = this->CellRect(i,j);
      r1 = TRect(r.Left,r.Top+13,r.Right,r.Bottom);
      Canvas->Font->Color = FTextColor;
      Canvas->Font->Name = "宋体";
      Canvas->Font->Size = 9;
      switch(ADayType)
      {
        case dtNormal:
          Canvas->Brush->Color = FTaskColor;
          Canvas->FillRect(r1);
          break;
        case dtWeekEnd:
          Canvas->Brush->Color = FTaskRestColor;
          Canvas->FillRect(r1);
          break;
        case dtCompleted:
          Canvas->Font->Color = FCompTextColor;
          Canvas->Brush->Color = FCompBackColor;
          Canvas->FillRect(r1);
          break;
      }
      if(FSelList.count(Dates[i][j])>0)
      {
        Canvas->Brush->Color = FSelectedBackColor;
        Canvas->FillRect(r1);
        Canvas->Font->Color = FSelectedTextColor;
      }
      tx = r.Left + 2;
      ty =  r.Top + (r.Height()-EditBox->Height/2)/2;//r.Top + 15;
      if(EditBox->DigLen>0)
        Canvas->TextOut(tx,ty,Format("%."+IntToStr(EditBox->DigLen)+"f",ARRAYOFCONST((AValue))));
      else
        Canvas->TextOut(tx,ty,AValue);
      if(c==DailyPlans->Count-1) return;
      c++;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::AssignDates(TDateTime StartDate)
{
  int i,j;
  for(i=0;i<=6;i++)
    for(j=0;j<=5;j++)
      Dates[i][j] = StartDate + j * 7 + i;
}
//---------------------------------------------------------------------------
bool __fastcall TCalendarGrid::SelectCell(int ACol, int ARow)
{
   return TCustomGrid::SelectCell(ACol,ARow);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::TopLeftChanged(void)
{
   if(EditBox)
     EditBox->Visible=false;
}
void __fastcall TCalendarGrid::ClickHandler(TObject *Sender)
{
   double NewValue;
   if(EditBox)
   if(EditBox->Visible)
   {
     try
     {
       NewValue = StrToFloat(EditBox->Text);
     }
     catch(...)
     {
	   #ifdef _DELPHI_STRING_UNICODE
	   Application->MessageBox(L"输入不正确。请输入一个数值！ ",L"日历",MB_ICONERROR | MB_OK);
	   #else
	   Application->MessageBox("输入不正确。请输入一个数值！ ","日历",MB_ICONERROR | MB_OK);
	   #endif
       EditBox->SetFocus();
       return;
     }
     if(NewValue<0)
     {
	   #ifdef _DELPHI_STRING_UNICODE
	   Application->MessageBox(L"输入不正确。数值不能小于零。 ",L"日历",MB_ICONERROR | MB_OK);
	   #else
	   Application->MessageBox("输入不正确。数值不能小于零。 ","日历",MB_ICONERROR | MB_OK);
	   #endif
       EditBox->SetFocus();
       return;
     }
     if(NewValue > PrjCale->FMaxValue)
     {
	   #ifdef _DELPHI_STRING_UNICODE
	   Application->MessageBox(String("输入数值不能超过 "+FloatToStr(PrjCale->FMaxValue)+".").c_str(),L"日历",MB_ICONERROR | MB_OK);
	   #else
	   Application->MessageBox(String("输入数值不能超过 "+FloatToStr(PrjCale->FMaxValue)+".").c_str(),"日历",MB_ICONERROR | MB_OK);
	   #endif
       EditBox->SetFocus();
       return;
     }
     TDailyPlanData * APlan;
     int i;
     for(i=0;i<=DailyPlans->Count-1;i++)
	 {
        APlan = (TDailyPlanData *)DailyPlans->Items[i];
        if(APlan->Date == Dates[EditX][EditY])
        {
          if(APlan->Value != NewValue)
          {
            PrjCale->OldValue = APlan->Value;
            APlan->Value = NewValue;
            FModified = true;
			PrjCale->ModifiedValue = NewValue;
            PrjCale->ModifiedID = APlan->ID;
          }
          break;
        }
     }
     EditBox->Visible = false;
   }
   if(FModified) Invalidate();
   if(PrjCale->OnClick)
      PrjCale->OnClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::DblClick(void)
{
  TControl::DblClick();
  int ACol = this->Col;
  int ARow = this->Row;
  if(FPrjFinished)
  {
  #ifdef _DELPHI_STRING_UNICODE
	Application->MessageBox(L"该项目已经完工或停工，不能修改任务日历。",L"日历提示",MB_ICONINFORMATION | MB_OK);
  #else
	Application->MessageBox("该项目已经完工或停工，不能修改任务日历。","日历提示",MB_ICONINFORMATION | MB_OK);
  #endif
    return;
  }
  if(Dates[ACol][ARow] <= FCompletedDate)
  {
	#ifdef _DELPHI_STRING_UNICODE
	Application->MessageBox(L"该工作日处于进度截止日期之前，不能修改。",L"日历提示",MB_ICONINFORMATION | MB_OK);
	#else
	Application->MessageBox("该工作日处于进度截止日期之前，不能修改。","日历提示",MB_ICONINFORMATION | MB_OK);
	#endif
    return;
  }
  if(!PrjCale->FEnableEdit) return;
  int i;
  TDailyPlanData *APlan;
  double InitData = -99999;
  if(DailyPlans)
  {
    for(i=0;i<=DailyPlans->Count-1;i++)
    {
      APlan = (TDailyPlanData *)DailyPlans->Items[i];
      if(APlan->Date == Dates[ACol][ARow])
      {
        if(APlan->DayType != dtNormal)
          break;
        else
        {
          InitData = APlan->Value;
          break;
        }
      }
    }
  }
  if(InitData!=-99999)
    ShowEditAt(ACol,ARow,InitData);
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::EditKeyDown(TObject* Sender, Word &Key, TShiftState Shift)
{
  switch(Key)
  {
    case VK_RETURN:
       if(EditBox)
         if(EditBox->Visible)
       {
          ClickHandler(Sender);
          if(EditBox)
            EditBox->Visible = false;
       }
       this->SetFocus();
    break;
    case VK_ESCAPE:
       if(EditBox)
         if(EditBox->Visible)
           EditBox->Visible = false;
       this->SetFocus();
    break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::ShowEditAt(int ACol, int ARow, double InitValue)
{
  TRect r;
//  if(!EditBox)
//  {
//    EditBox = new TEdit(this);
//    EditBox->Parent = this;
//    EditBox->Height = 18;
//    EditBox->Ctl3D = false;
//    EditBox->OnKeyDown = EditKeyDown;
//    EditBox->Font->Color = clBlack;
//    EditBox->Color = clWhite;
//  }
  r = CellRect(ACol,ARow);
  EditBox->Left = r.Left;
  EditBox->Top = r.Top + (r.Height()-EditBox->Height/2)/2;
  EditBox->Width = r.Width();
  EditBox->Visible = true;
  try
  {
      if(EditBox->DigLen>0)
        EditBox->Text=Format("%."+IntToStr(EditBox->DigLen)+"f",ARRAYOFCONST((InitValue)));
      else
        EditBox->Text=InitValue;

//    EditBox->Text = Format("%."+IntToStr(EditBox->DigLen)+"f",ARRAYOFCONST((InitValue)));
  }
  catch(...)
  {
    ShowMessage("ERROR.");
  }
  EditBox->SetFocus();
  EditX = ACol;
  EditY = ARow;
}
//void __fastcall TCalendarGrid::SizeChanged(int OldColCount, int OldRowCount)
//{
//  TCustomGrid::SizeChanged(OldColCount,OldRowCount);
//  if(EditBox->Visible)
//    {
//          TRect r = CellRect(EditX,EditY);
//          EditBox->Left = r.Left;
//          EditBox->Top = r.Top + (r.Height()-EditBox->Height)/2;
//          EditBox->Width = r.Width();
//
//    }
//}

//---------------------------------------------------------------------------
/*
void __fastcall TCalendarGrid::CMWantSpecialKey(TCMWantSpecialKey &Message)
{
  switch(Message.CharCode)
  {
    case VK_SPACE:
      if(!EditBox)
           DblClick();
      if(!EditBox->Visible)
           DblClick();
    break;
  }
  Message.Result = 0;
}
*/
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::KeyDown(Word &Key, TShiftState Shift)
{
  switch(Key)
  {
    case VK_RETURN:
      if(!EditBox)
           DblClick();
      if(EditBox)
      if(!EditBox->Visible)
           DblClick();
      break;
    case VK_LEFT:
      if(Col>0)
        Col --;
      FSelList.clear();
      TagSelected(Dates[Col][Row]);
      break;
    case VK_RIGHT:
      if(Col<6)
        Col ++;
      FSelList.clear();
      TagSelected(Dates[Col][Row]);
      break;
    case VK_UP:
      if(Row>0)
      {
        Row --;
        FSelList.clear();
        TagSelected(Dates[Col][Row]);
      }
      else
      {
        PrjCale->ScrollPage(FPageStartDate - 1);
        FSelList.clear();
        TagSelected(Dates[Col][0]);
        Row = 0;
        Invalidate();
      }
      break;
    case VK_DOWN:
      if(Row<5)
      {
        Row ++;
        FSelList.clear();
        TagSelected(Dates[Col][Row]);
      }
      else
      {
        PrjCale->ScrollPage(FPageStartDate + 7);
        FSelList.clear();
        TagSelected(Dates[Col][5]);
        Row = 5;
        Invalidate();
      }
      break;
    case VK_PRIOR:
      PrjCale->ScrollPage(FPageStartDate - 41);
      FSelList.clear();
      TagSelected(Dates[Col][Row]);
      Invalidate();
      break;
    case VK_NEXT:
      PrjCale->ScrollPage(FPageEndDate + 1);
      FSelList.clear();
      TagSelected(Dates[Col][Row]);
      Invalidate();
      break;
  }
}
//---------------------------------------------------------------------------
//下列代码支持多重选择
void __fastcall TCalendarGrid::MouseDown(TMouseButton Button, TShiftState Shift, int X,
		int Y)
{
  TCustomGrid::MouseDown(Button,Shift,X,Y);
  TGridCoord gc;
  gc = MouseCoord(X, Y);
  TDateTime StartDate;

  if(Button == mbLeft)
  {
    if(!(Shift.Contains(ssShift)) && !(Shift.Contains(ssCtrl)))//NORMAL
    {
        FSelList.clear();
        TagSelected(Dates[gc.X][gc.Y]);
        FLastSelDate = Dates[gc.X][gc.Y];
    }
    else if(!(Shift.Contains(ssShift)) && Shift.Contains(ssCtrl)) //PRESS CTRL ONLY
    {
        TagSelected(Dates[gc.X][gc.Y]);
        FLastSelDate = Dates[gc.X][gc.Y];
    }
    else if(FSelList.size()>0)
    {
      StartDate = FLastSelDate;
      if(StartDate<=Dates[gc.X][gc.Y])
      {
        FSelList.clear();
        for(TDateTime i = StartDate; i<= Dates[gc.X][gc.Y]; i++)
          TagSelected(i);
        FLastSelDate = StartDate;
      }
      else
      {
        FSelList.clear();
        for(TDateTime i = Dates[gc.X][gc.Y]; i<= StartDate; i++)
          TagSelected(i);
        FLastSelDate = StartDate;
      }
    }
    else
    {
      TagSelected(Dates[gc.X][gc.Y]);
    }
  }
  Invalidate();
}
//---------------------------------------------------------------------------
void TCalendarGrid::TagSelected(TDateTime ADate)
{
  if(!(ADate<PlanStartDate || ADate>PlanEndDate ))
  if(FSelList.count(ADate)==0)
  {
    FSelList.insert(ADate);
  }
  else
  {
    FSelList.erase(ADate);
  }
  if(FSelList.size()>0) FDate = *FSelList.begin();
    else FDate = ADate;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TPrjCalendarPanel::GetSelected(unsigned int idx)
{
  if(Calendar->FSelList.size()==0 || idx>=Calendar->FSelList.size()) return 0;
  set<TDateTime>::iterator iter = Calendar->FSelList.begin();
  advance(iter,idx);
  return *iter;
}
//---------------------------------------------------------------------------
int __fastcall TPrjCalendarPanel::GetSelCount()
{
  return Calendar->FSelList.size();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// TPrjCalendarPanel Class
//---------------------------------------------------------------------------
__fastcall TPrjCalendarPanel::TPrjCalendarPanel(TComponent* Owner)
        : TPanel(Owner)
{
  InitCalendar();
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetFlat(bool value)
{
  FFlat = value;
  if(FFlat)
  {
    this->BevelInner = bvNone;
    this->BevelOuter = bvNone;
    this->Ctl3D = false;
    this->BorderStyle = bsNone;
    this->BorderWidth = 0;

    Scrollbar->Ctl3D = false;
    Calendar->Ctl3D = false;
  }
  else
  {
    this->BevelInner = bvNone;
    this->BevelOuter = bvLowered;
    this->Ctl3D = true;
    this->BorderStyle = bsNone;
    this->BorderWidth = 1;

    Scrollbar->Ctl3D = true;
    Calendar->Ctl3D = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::InitCalendar()
{
  DoubleBuffered = true;
  this->Width = 538+20+2;
  this->Height = 387+18+20+2;
  this->BevelOuter = bvLowered;
  this->Font->Name = "宋体";
  this->Font->Size = 9;
  Scrollbar = new TScrollBar(this);
  Scrollbar->Kind = sbVertical;
  Scrollbar->Align = alRight;
  Scrollbar->Parent = this;
  Scrollbar->Min = 1;
  Scrollbar->Max = 3444;
  Scrollbar->OnScroll = ScrollHandler;

  pnlMain = new TPanel(this);
  pnlMain->Parent = this;
  pnlMain->BevelOuter = bvNone;
  pnlMain->Align = alClient;

  pnlMonth = new TPaintBox(pnlMain);
  pnlMonth->Height = 18;
  pnlMonth->Parent = pnlMain;
  pnlMonth->Align = alTop;

  pnlDayCaption = new TPaintBox(pnlMain);
  pnlDayCaption->Height = 20;
  pnlDayCaption->Parent = pnlMain;
  pnlDayCaption->Align = alTop;

  Calendar = new TCalendarGrid(pnlMain);
  Calendar->Parent = pnlMain;
  Calendar->FixedRows = 0;
  Calendar->FixedCols = 0;
  Calendar->ColCount = 7;
  Calendar->RowCount = 6;
  Calendar->DefaultColWidth = 76;
  Calendar->DefaultRowHeight = 64;
  Calendar->GridLineWidth = 1;
  Calendar->Width = 76*7+6;
  Calendar->Height = 64*6+3;
  Calendar->DefaultDrawing = true;
  Calendar->Align = alClient;
  Calendar->ScrollBars = ssNone;
  Calendar->Options >> goRangeSelect;
/*
    TColor FColor;
    TColor FBackColor;
    TColor FTextColor;
    TColor FTitleBackColor;
    TColor FTitleTextColor
    TColor FSelectedColor;
    TColor FCompBackColor;
    TColor FCompTextColor;
    TColor FWeekEndBackColor;
*/
  Calendar->FColor = clWindow;
  Calendar->FBackColor = clWhite;
  Calendar->FTextColor = clBlack;
  Calendar->FTitleBackColor = (TColor)0x00D9DEE1;
  Calendar->FTitleTextColor = clBlack;
  Calendar->FSelectedBackColor =(TColor)0x00FFCECE;
//  Calendar->FSelectedBackColor = clBlack;
  Calendar->FSelectedTextColor = clBlack;
  Calendar->FCompBackColor = (TColor)0x00F1E4E4;
  Calendar->FCompTextColor = clBlack;
//  Calendar->FWeekEndBackColor = (TColor)0x00EAEAEA;
  Calendar->FTaskColor = (TColor)0x00E6FFFF;
  Calendar->FTaskColor = (TColor)0x00DFFFF0;
  Calendar->PrjCale = this;
  Calendar->EditX = -1;
  Calendar->EditY = -1;
  Calendar->OnClick = Calendar->ClickHandler;
  Calendar->FModified = false;
  Calendar->DefaultDrawing = false;
//  Calendar->FPrec = 4;
  SetDate(::Date());
  CompletedDate = 0;
  Calendar->FPrjFinished = false;
  FEnableEdit = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::DrawCalendar(String PrjCode, String TaskCode)
{
}
//---------------------------------------------------------------------------
__fastcall TPrjCalendarPanel::~TPrjCalendarPanel()
{
  try
  {
    delete pnlMonth;
    delete pnlDayCaption;
    delete Calendar;
    delete pnlMain;
    delete Scrollbar;
  }
  catch(...)
  {
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::PaintWeekCaption()
{
  pnlDayCaption->Font->Size = 9;
  pnlDayCaption->Font->Name = "宋体";
  int i,x;
  int Gap;
  Gap = Calendar->DefaultColWidth / 2;
  for(i=1;i<=7;i++)
  {
    x = (2*i-1)*Gap;
    pnlDayCaption->Canvas->TextOut(x,4,WeekCaps[i-1]);
  }
  pnlDayCaption->Canvas->MoveTo(0,0);
  pnlDayCaption->Canvas->LineTo(pnlDayCaption->Width,0);
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::PaintMonthName(TDateTime d)
{
  pnlMonth->Canvas->TextOut(10,3,FormatDateTime("yyyy'年'm'月        '",d));
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::SetADate(TDateTime ADate)
{
  FDate = ADate;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetDate(TDateTime value)
{
  Calendar->SetADate(value);
  ScrollPage(value);
  Scrollbar->Position = (int)(value - 30682) / 7;

}
//---------------------------------------------------------------------------
TDateTime __fastcall TPrjCalendarPanel::GetDate()
{
  return Calendar->FDate;
}
//---------------------------------------------------------------------------
//void __fastcall TPrjCalendarPanel::SetWeekEndBackColor(TColor value)
//{
//  Calendar->FWeekEndBackColor = value;
//  Calendar->Invalidate();
//}
//---------------------------------------------------------------------------
//TColor __fastcall TPrjCalendarPanel::GetWeekEndBackColor()
//{
//        return Calendar->FWeekEndBackColor;
//}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetSelectedBackColor(TColor value)
{
  Calendar->FSelectedBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetSelectedBackColor()
{
  return Calendar->FSelectedBackColor;
}

//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetSelectedTextColor(TColor value)
{
  Calendar->FSelectedTextColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetSelectedTextColor()
{
  return Calendar->FSelectedTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::ScrollHandler(TObject *Sender,TScrollCode ScrollCode,int &ScrollPos)
{
  TDateTime ADate;
  Calendar->ClickHandler(Sender);
  switch(ScrollCode)
  {
    case scLineUp:
       ScrollPage(Calendar->FPageStartDate - 1);
      break;
    case scLineDown:
       ScrollPage(Calendar->FPageStartDate + 7);
      break;
    case scPageUp:
       ScrollPage(Calendar->FPageStartDate - 41);
      break;
    case scPageDown:
       ScrollPage(Calendar->FPageEndDate + 1);
      break;
    case scPosition:
       ADate = ScrollPos - 30682;
       ScrollPage(Calendar->FPageEndDate + 1);
      break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::ScrollPage(TDateTime ADate)
{
  unsigned short AYear,AMonth,ADay;
  TDateTime MonthStartDate,CaleStartDate;
  BYTE dow;

  DecodeDate(ADate,AYear,AMonth,ADay);
  MonthStartDate = StartOfAMonth(AYear,AMonth);
//  PaintWeekCaption();
//  PaintMonthName(MonthStartDate);
  dow = DayOfWeek(ADate);
  CaleStartDate = ADate - dow + 1;
  Calendar->FPageStartDate = CaleStartDate;
  Calendar->FPageEndDate = CaleStartDate + 41;
  Calendar->FActiveMonth = AMonth;
  Calendar->AssignDates(CaleStartDate);
  Calendar->Invalidate();
  Scrollbar->Position = (int)(ADate - 30682) / 7;
}
//---------------------------------------------------------------------------
TDateTime __fastcall TPrjCalendarPanel::PosToDateTime(int pos)
{
  int BaseYear = 1984;
  Word AYear,AMonth;
  AYear = BaseYear + pos / 12;
  AMonth = pos % 12;
  if(AMonth == 0)
  {
   AMonth = 12;
   AYear --;
  }
  return (TDateTime)EncodeDate(AYear,AMonth,1);
}
//---------------------------------------------------------------------------
int __fastcall TPrjCalendarPanel::DateTimeToPos(TDateTime ADate)
{
  int BaseYear = 1984;
  Word AYear=0,AMonth=0,ADay=0;
  DecodeDate(ADate,AYear,AMonth,ADay);
  return (AYear - BaseYear) * 12 + AMonth;
}
//---------------------------------------------------------------------------
bool __fastcall TPrjCalendarPanel::GetModified()
{
  return Calendar->FModified;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetModified(bool value)
{
  Calendar->FModified = value;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetColor(TColor value)
{
//  Calendar->m_Color = value;
  pnlMonth->Color = value;
  pnlDayCaption->Color = value;
  pnlMain->Color = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetColor()
{
  return pnlMain->Color;
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::Resize(void)
{
  TControl::Resize();
  DefaultRowHeight = (Height - 7) / 6;
  DefaultColWidth = (Width - 8) / 7;
  if((DefaultRowHeight * 6) + 7 > Height)
  {
    DefaultRowHeight --;
  }
  if((DefaultColWidth * 7) + 8 > Width)
  {
    DefaultColWidth --;
  }
}
//---------------------------------------------------------------------------
TDateTime __fastcall TPrjCalendarPanel::GetCompDate()
{
  return Calendar->FCompletedDate;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetCompDate(TDateTime value)
{
  Calendar->FCompletedDate = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetBackColor()
{
  return Calendar->FBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetBackColor(TColor value)
{
  Calendar->FBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetTextColor()
{
  return Calendar->FTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetTextColor(TColor value)
{
  Calendar->FTextColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetTitleBackColor()
{
  return Calendar->FTitleBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetTitleBackColor(TColor value)
{
  Calendar->FTitleBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetTitleTextColor()
{
  return Calendar->FTitleTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetTitleTextColor(TColor value)
{
  Calendar->FTitleTextColor = value;
  Calendar->Invalidate();

}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetCompTextColor()
{
  return Calendar->FCompTextColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetCompTextColor(TColor value)
{
  Calendar->FCompTextColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetCompBackColor()
{
  return Calendar->FCompBackColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetCompBackColor(TColor value)
{
  Calendar->FCompBackColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
TColor __fastcall TPrjCalendarPanel::GetTaskColor()
{
  return Calendar->FTaskColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetTaskColor(TColor value)
{
  Calendar->FTaskColor = value;
  Calendar->Invalidate();
}

TColor __fastcall TPrjCalendarPanel::GetTaskRestColor()
{
  return Calendar->FTaskRestColor;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetTaskRestColor(TColor value)
{
  Calendar->FTaskRestColor = value;
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::AddDailyPlan(int ID, TDateTime ADate,double AValue, TWorkDayType ADayType)
{
  if(!Calendar->DailyPlans) return;
  TDailyPlanData *APlan;
  APlan = new TDailyPlanData;
  APlan->ID = ID;
  APlan->Date = ADate;
  APlan->Value = AValue;
  if(APlan->Date <= CompletedDate)
    APlan->DayType = dtCompleted;
  else
    APlan->DayType = ADayType;
  Calendar->DailyPlans->Add(APlan);
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::ReplaceDailyPlan(int ID,TDateTime ADate,double AValue, TWorkDayType ADayType)
{
  if(!Calendar->DailyPlans) return;
  TDailyPlanData *APlan ,*BPlan;
  APlan = new TDailyPlanData;
  APlan->ID = ID;
  APlan->Date = ADate;
  APlan->Value = AValue;
  APlan->DayType = ADayType;
  int i, idx = -1;
  for(i = 0;i <= Calendar->DailyPlans->Count-1; i++)
  {
    BPlan = (TDailyPlanData *)Calendar->DailyPlans->Items[i];
    if(BPlan->ID == ID)
    {
      idx = i;
      break;
    }
  }
  if(idx>=0)
  Calendar->DailyPlans->Insert(idx,APlan);
  if(Calendar->DailyPlans->Items[idx+1])
    delete Calendar->DailyPlans->Items[idx+1];
  Calendar->DailyPlans->Delete(idx+1);
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::ClearDailyPlan()
{
  if(Calendar->EditBox)
  {
     Calendar->EditBox->Visible=false;
  //    delete Calendar->EditBox;
//    Calendar->EditBox = NULL;
  }
  Calendar->FSelList.clear();
  Calendar->FLastSelDate = 0;
  Calendar->DailyPlans->Clear();
  Calendar->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TCalendarGrid::Paint()
{
  TCustomGrid::Paint();
  PrjCale->PaintWeekCaption();
  PrjCale->PaintMonthName(FPageStartDate);
  PaintTaskPlan();
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetViewType(TViewType value)
{
  FViewType = value;
}
//---------------------------------------------------------------------------
TViewType __fastcall TPrjCalendarPanel::GetViewType()
{
  return FViewType;
}
//---------------------------------------------------------------------------
double __fastcall TPrjCalendarPanel::GetTotalValue()
{
  int i;
  TDailyPlanData *APlan;
  double Total = 0;
  for(i = 0;i <= Calendar->DailyPlans->Count-1; i++)
  {
    APlan = (TDailyPlanData *)Calendar->DailyPlans->Items[i];
    if(APlan)
      Total += APlan->Value;
  }
  return Total;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetPrecision(int value)
{
        if(Calendar->EditBox->DigLen != value) {
                Calendar->EditBox->DigLen = value;
                Refresh();
//        Invalidate();
        }
}
//---------------------------------------------------------------------------
int __fastcall TPrjCalendarPanel::GetPrecision()
{
        return Calendar->EditBox->DigLen;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetPrjFinished(bool value)
{
        if(Calendar->FPrjFinished != value) {
                Calendar->FPrjFinished = value;
        }
}
//---------------------------------------------------------------------------
bool __fastcall TPrjCalendarPanel::GetPrjFinished()
{
        return Calendar->FPrjFinished;
}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::SetEnableEdit(bool value)
{
    if(value!=FEnableEdit)
    {
        FEnableEdit = value;
    }
    if(!value&&Calendar->EditBox->Visible)
       Calendar->EditBox->Visible=false;

}
//---------------------------------------------------------------------------
void __fastcall TPrjCalendarPanel::ChangePlanValue(int AID, double NewValue)
{
     TDailyPlanData * APlan;
     int i;
     for(i=0;i<=Calendar->DailyPlans->Count-1;i++)
     {
        APlan = (TDailyPlanData *)Calendar->DailyPlans->Items[i];
        if(APlan->ID == AID)
        {
          APlan->Value = NewValue;
          break;
        }
     }
}
double __fastcall TPrjCalendarPanel::GetDailyPlan(int AID)
{
     TDailyPlanData * APlan;
     int i;
     for(i=0;i<=Calendar->DailyPlans->Count-1;i++)
     {
        APlan = (TDailyPlanData *)Calendar->DailyPlans->Items[i];
        if(APlan->ID == AID)
        {
          return APlan->Value;
        }
     }
     return 0;
}
//---------------------------------------------------------------------------
void TPrjCalendarPanel::CancelEdit()
{
  if(Calendar->EditBox)
  {
  Calendar->EditBox->Visible=false;
  }
  Modified = false;
}

void __fastcall TPrjCalendarPanel::SetEditCharType(TZCharType value)
{
        Calendar->EditBox->CharType=value;
}
TZCharType __fastcall TPrjCalendarPanel::GetEditCharType()
{
        return Calendar->EditBox->CharType;
}

void __fastcall TPrjCalendarPanel::SetEditDigLen(int value)
{
        Calendar->EditBox->DigLen=value;
}
int __fastcall TPrjCalendarPanel::GetEditDigLen()
{
        return Calendar->EditBox->DigLen;
}

void __fastcall TPrjCalendarPanel::SetEditMaxLength(int value)
{
        Calendar->EditBox->MaxLength=value;
}
int __fastcall TPrjCalendarPanel::GetEditMaxLength()
{
        return Calendar->EditBox->MaxLength;
}

void __fastcall TCalendarGrid::WMSize(TMessage &Msg)
{
  TCustomGrid::Dispatch(&Msg);
  if(EditBox->Visible)
    {
          TRect r = CellRect(EditX,EditY);
          EditBox->Left = r.Left;
          EditBox->Top = r.Top + (r.Height()-EditBox->Height/2)/2;
          EditBox->Width = r.Width();

    }

}
