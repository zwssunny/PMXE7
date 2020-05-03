//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZComboBox.h"
#pragma package(smart_init)
//#pragma resource "ZCOMBOBOX.RES"
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZComboBox *)
{
  new TZComboBox(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZComboBox::TZComboBox(TComponent* Owner)
  : TComboBox(Owner)
{
  FDataKeyItem = new TStringList;
  FDataItem1 = new TStringList;
  FDataItem2 = new TStringList;
  FDataItem3 = new TStringList;
  FDataItem4 = new TStringList;
  FDataItem5 = new TStringList;
  FDataItem6 = new TStringList;

  FCharType = TZCharType::ctNormal;
  FCharCase = ccNormal;

  FKeyItem = cbItem1;
  FDispItem = cbItem1;

  FBorderColor = crBorderColor;
  FFocusedColor = crFocusedColor;
  FHoverColor = crHoverColor;

  FIsFocused = false;
  FComboBoxFlat = false;
  Ctl3D=false;

}
//---------------------------------------------------------------------------
namespace Zcombobox
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZComboBox)};
	 RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------

__fastcall TZComboBox::~TZComboBox()
{
  delete FDataItem1;
  delete FDataItem2;
  delete FDataItem3;
  delete FDataItem4;
  delete FDataItem5;
  delete FDataItem6;
  delete FDataKeyItem;
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::CMMouseEnter(TMessage &Message)
{
  TComboBox::Dispatch(&Message);
  if(FComboBoxFlat)
  {
    FIsHovered=true;
    if(Focused())
    {
      Color=FFocusedColor;
    }else
    {
      Color=FHoverColor;
    }
    HDC edc = GetDC(EditHandle);
    HDC ldc = GetDC(ListHandle);
    SetBkColor(edc, Color);
    SetBkColor(ldc, Color);
    ReleaseDC(EditHandle, edc);
    ReleaseDC(ListHandle, ldc);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::CMMouseLeave(TMessage &Message)
{
  TComboBox::Dispatch(&Message);
  if(FComboBoxFlat)
  {
    FIsHovered=false;

    if(DroppedDown || Focused())
      Color=FFocusedColor;
    else
    {
      ParentColor=true;
    }
    HDC edc = GetDC(EditHandle);
    HDC ldc = GetDC(ListHandle);
    SetBkColor(edc, Color);
    SetBkColor(ldc, Color);
    ReleaseDC(EditHandle, edc);
    ReleaseDC(ListHandle, ldc);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::WMSetFocus(TMessage &Message)
{
  DoSetFocus();
  TComboBox::Dispatch(&Message);
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::WMKillFocus(TMessage &Message)
{
  TComboBox::Dispatch(&Message);
  DoKillFocus();
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::CNCommand(TWMCommand &Message)
{
  TComboBox::Dispatch(&Message);
  switch(Message.NotifyCode)
  {
     case CBN_SETFOCUS:
        DoSetFocus();
        break;
     case CBN_KILLFOCUS:
        DoKillFocus();
        break;
     case CBN_DROPDOWN:
        if(FComboBoxFlat)
        {
          if(Style == csDropDown)
             ;
          else
          {
             FIsFocused=true;
             Color = FFocusedColor;
             HDC ldc = GetDC(ListHandle);
             SetBkColor(ldc, Color);
             ReleaseDC(ListHandle, ldc);
          }
        }
	   Invalidate();
        break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::WMPaint(TWMPaint &Message)
{
  TComboBox::Dispatch(&Message);
  ClearBorder(this, (TColor)ColorToRGB(FBorderColor));
}
void __fastcall TZComboBox::DoSetFocus()
{
  if(FComboBoxFlat)
  {
    FIsFocused=true;
    Color=FFocusedColor;
  }
Invalidate();
}
void __fastcall TZComboBox::DoKillFocus()
{
  if(!DroppedDown)
  if(FComboBoxFlat && !Focused())
  {
    FIsFocused=false;
    if(FIsHovered)
      Color=FHoverColor;
    else
      ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::DrawComboBoxFlat()
{
  if(Ctl3D)
    return;
  if(!FIsHovered && !Focused())
    ParentColor=true;
  HDC dc = ::GetDC(Handle);
  HPEN pen,OldPen;
  pen = CreatePen(PS_SOLID, 1, GetPixel(dc, 2, 2));
  OldPen = (HPEN)SelectObject(dc, pen);

  POINT Points[4] = {
      {ClientRect.Left+1,ClientRect.Bottom-1},
      {ClientRect.Left+1,ClientRect.Top+1},
      {ClientRect.Right-1,ClientRect.Top+1},
      {ClientRect.Right-1,ClientRect.Bottom-1},
  };
      ::Polyline(dc, Points, 4);

  ::SelectObject(dc, OldPen);
  ::DeleteObject(pen);
  pen = CreatePen(PS_SOLID, 1, ColorToRGB(FBorderColor));
  OldPen = (HPEN)SelectObject(dc, pen);

  POINT Points1[4] = {
	  {ClientRect.Left,ClientRect.Bottom},
      {ClientRect.Left,ClientRect.Top},
      {ClientRect.Right-1,ClientRect.Top},
	  {ClientRect.Right-1,ClientRect.Bottom}
  };
  ::Polyline(dc, Points1, 4);

  ::SelectObject(dc, OldPen);
      DeleteObject(pen);
      pen = CreatePen(PS_SOLID, 1, GetPixel(dc, 2, 2));
	  OldPen = (HPEN)SelectObject(dc, pen);

      MoveToEx(dc, ClientRect.Left+1, ClientRect.Bottom-2, NULL);
      LineTo(dc, ClientRect.Right-1, ClientRect.Bottom-2);

  ::SelectObject(dc, OldPen);
      DeleteObject(pen);
      pen = CreatePen(PS_SOLID, 1, ColorToRGB(FBorderColor));
	  OldPen = (HPEN)SelectObject(dc, pen);

      MoveToEx(dc, ClientRect.Left, ClientRect.Bottom-1, NULL);
      LineTo(dc, ClientRect.Right-1, ClientRect.Bottom-1);

  ::SelectObject(dc, OldPen);
  DeleteObject(pen);

  HBRUSH brush;
  TRect FRect;
  TColor FButtonColor=(TColor)0x00C5D6D9;
  brush=CreateSolidBrush(ColorToRGB(FButtonColor));
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FRect.Left=ClientRect.Right-19;
  FRect.Top=ClientRect.Top+1;
  FRect.Right=ClientRect.Right-1;
  FRect.Bottom=ClientRect.Bottom-1;
  FillRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);

  ::SelectObject(dc, OldPen);
  DeleteObject(pen);
  pen = CreatePen(PS_SOLID, 1, ColorToRGB(FBorderColor));
  OldPen = (HPEN)SelectObject(dc, pen);

  MoveToEx(dc, ClientRect.Right-19, ClientRect.Top+1, NULL);
  LineTo(dc, ClientRect.Right-19, ClientRect.Bottom-1);

  ::SelectObject(dc, OldPen);
  DeleteObject(pen);

  ::SelectObject(dc, OldPen);
  DeleteObject(pen);
  pen = CreatePen(PS_SOLID, 1, clBlack);
  OldPen = (HPEN)SelectObject(dc, pen);
  brush = CreateSolidBrush(clBlack);
  oldbrush = (HBRUSH)SelectObject(dc, brush);
  POINT p[4];
  p[0].x = ClientRect.Right - 13;
  p[0].y = ClientRect.Top + 8;
  p[1].x = ClientRect.Right - 7;
  p[1].y = ClientRect.Top + 8;
  p[2].x = ClientRect.Right - 10;
  p[2].y = ClientRect.Top + 11;
  p[3].x = ClientRect.Right - 13;
  p[3].y = ClientRect.Top + 8;
  Polygon(dc, p, 4);
  ::SelectObject(dc, OldPen);
  DeleteObject(pen);
  ::SelectObject(dc, oldbrush);
  DeleteObject(brush);

  ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::ClearBorder(TWinControl* WinControl, TColor clearcolor)
{
  HDC dc = ::GetDC(Handle);
  HPEN pen;
   if (Color&0x80000000)
  	pen = ::CreatePen(PS_SOLID, 1, GetPixel(dc, 1, 1));
  else
    pen = ::CreatePen(PS_SOLID, 1, clearcolor);

  HPEN OldPen = (HPEN)SelectObject(dc, pen);

  MoveToEx(dc, ClientRect.Right-1, ClientRect.Top, NULL);
  LineTo(dc, ClientRect.Right-1, ClientRect.Bottom-1);
  MoveToEx(dc, ClientRect.Left, ClientRect.Bottom-2, NULL);
  LineTo(dc, ClientRect.Right, ClientRect.Bottom-2);
  if (!Ctl3D)
  {
        ::SelectObject(dc, OldPen);
            ::DeleteObject(pen);
            pen = CreatePen(PS_SOLID, 3, GetPixel(dc, 2, 2));
			OldPen = (HPEN)SelectObject(dc, pen);

            POINT Points[3] = {
            {ClientRect.Left,ClientRect.Bottom-1},
            {ClientRect.Left,ClientRect.Top},
            {ClientRect.Right-1,ClientRect.Top}
        };
			::Polyline(dc, Points, 3);

        ::SelectObject(dc, OldPen);
            DeleteObject(pen);
            pen = CreatePen(PS_SOLID, 1, GetPixel(dc, 2, 2));
			OldPen = (HPEN)SelectObject(dc, pen);

            MoveToEx(dc, ClientRect.Left, ClientRect.Bottom-2, NULL);
            LineTo(dc, ClientRect.Right, ClientRect.Bottom-2);

        ::SelectObject(dc, OldPen);
            DeleteObject(pen);
            pen = CreatePen(PS_SOLID, 1, clBlack);
			OldPen = (HPEN)SelectObject(dc, pen);

            MoveToEx(dc, ClientRect.Left, ClientRect.Bottom-1, NULL);
            LineTo(dc, ClientRect.Right-20, ClientRect.Bottom-1);
      }
      ::SelectObject(dc, OldPen);
      DeleteObject(pen);
      ReleaseDC(Handle, dc);
}

//---------------------------------------------------------------------------
bool __fastcall TZComboBox::LocateKey(String value)
{
  int index;
  ItemIndex=-1;
  switch(FKeyItem)
  {
    case cbItem1:
      if(FCaseSensitive)
        index=Items->IndexOf(value);
      break;
    case cbItem2:
      if(FCaseSensitive)
        index=FDataItem1->IndexOf(value);
      break;
    case cbItem3:
      if(FCaseSensitive)
        index=FDataItem2->IndexOf(value);
      break;
    case cbItem4:
      if(FCaseSensitive)
        index=FDataItem3->IndexOf(value);
      break;
    case cbItem5:
      if(FCaseSensitive)
        index=FDataItem4->IndexOf(value);
      break;
    case cbItem6:
      if(FCaseSensitive)
        index=FDataItem5->IndexOf(value);
      break;
    case cbItem7:
      if(FCaseSensitive)
        index=FDataItem6->IndexOf(value);
      break;
  }
  if(!FCaseSensitive)
    index=FDataKeyItem->IndexOf(UpperCase(value));
  ItemIndex=index;
  if(index==-1)
    return false;
  else
    return true;
}

//---------------------------------------------------------------------------
String __fastcall TZComboBox::GetItemData(int Index)
{
  if(Index<0 || Index>6)
    return "";
  if(ItemIndex==-1)
    return "";
  if(Trim(this->Text).IsEmpty())
  {
    ItemIndex=-1;
    return "";
  }
  switch((TZComboBoxItemIndex)Index)
  {
    case cbItem1:
      return this->Items->Strings[ItemIndex];
    case cbItem2:
      return FDataItem1->Strings[ItemIndex];
    case cbItem3:
      return FDataItem2->Strings[ItemIndex];
    case cbItem4:
      return FDataItem3->Strings[ItemIndex];
    case cbItem5:
      return FDataItem4->Strings[ItemIndex];
    case cbItem6:
      return FDataItem5->Strings[ItemIndex];
    case cbItem7:
      return FDataItem6->Strings[ItemIndex];
    default:
      return "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::ClearAll()
{
  Items->Clear();
  FDataItem1->Clear();
  FDataItem2->Clear();
  FDataItem3->Clear();
  FDataItem4->Clear();
  FDataItem5->Clear();
  FDataItem6->Clear();
  FDataKeyItem->Clear();
  Text = "";
  ItemIndex=-1;
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::Change(void)
{
  TComboBox::Change();
  if(Trim(this->Text).IsEmpty())
    this->ItemIndex=-1;
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::KeyPress(Char &Key)
{

  if(Key==13)
  {
    TComboBox::Click();
    if(TabStop)
       GetParentForm(this)->Perform(WM_NEXTDLGCTL,0,FALSE);
    Key=0;
  }
  else if(FReadState)
       Key=0;
  else if(Key!=8)
  {
    switch(FCharCase)
    {
      case ccUpperCase:
        Key=UpperCase(Key)[1];
        break;
      case ccLowerCase:
        Key=LowerCase(Key)[1];
        break;
    }
    switch(FCharType)
    {
      case ctCharacter:
        if(Key>=48 && Key<=57)
          Key=0;
        break;
      case ctLetter:   //½ö½ö×ÖÄ¸
        if(Key<65 || (Key>90 && Key<97) || Key>122)
          Key=0;
        break;
    }
  }
  TComboBox::KeyPress(Key);
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::SetReadOnly(bool Read)
{
  FReadState=Read;
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::AddItems(String Item1,String Item2,String Item3,String Item4,String Item5
	  ,String Item6,String Item7)
{
	Items->Add(Item1);
    FDataItem1->Add(Item2);
    FDataItem2->Add(Item3);
    FDataItem3->Add(Item4);
    FDataItem4->Add(Item5);
    FDataItem5->Add(Item6);
    FDataItem6->Add(Item7);
    switch(FKeyItem)
    {
      case  cbItem1:
        FDataKeyItem->Add(UpperCase(Item1));
        break;
      case  cbItem2:
        FDataKeyItem->Add(UpperCase(Item2));
        break;
      case  cbItem3:
        FDataKeyItem->Add(UpperCase(Item3));
        break;
      case  cbItem4:
        FDataKeyItem->Add(UpperCase(Item4));
        break;
      case  cbItem5:
        FDataKeyItem->Add(UpperCase(Item5));
        break;
      case  cbItem6:
        FDataKeyItem->Add(UpperCase(Item6));
        break;
      case  cbItem7:
		FDataKeyItem->Add(UpperCase(Item7));
        break;
    }
}
//---------------------------------------------------------------------------


void __fastcall TZComboBox::AssignItems(TStringList *Item1,TStringList *Item2,TStringList *Item3,TStringList *Item4,
    TStringList *Item5,TStringList *Item6,TStringList *Item7)
{
  Items->Assign(Item1);
  if(Item2==NULL)
  {
    for(int i=0;i<Items->Count;i++)
    {
      FDataItem1->Add("");
      FDataItem2->Add("");
      FDataItem3->Add("");
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
    }
  }
  else if(Item3==NULL)
  {
    FDataItem1->Assign(Item2);
    for(int i=0;i<Items->Count;i++)
    {
      FDataItem2->Add("");
      FDataItem3->Add("");
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
    }
  }
  else if(Item4==NULL)
  {
    FDataItem1->Assign(Item2);
    FDataItem2->Assign(Item3);
    for(int i=0;i<Items->Count;i++)
    {
      FDataItem3->Add("");
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
    }
  }
  else if(Item5==NULL)
  {
    FDataItem1->Assign(Item2);
    FDataItem2->Assign(Item3);
    FDataItem3->Assign(Item4);
    for(int i=0;i<Items->Count;i++)
    {
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
    }
  }
  else if(Item6==NULL)
  {
    FDataItem1->Assign(Item2);
    FDataItem2->Assign(Item3);
    FDataItem3->Assign(Item4);
    FDataItem4->Assign(Item5);
    for(int i=0;i<Items->Count;i++)
    {
      FDataItem5->Add("");
      FDataItem6->Add("");
    }
  }
  else if(Item7==NULL)
  {
    FDataItem1->Assign(Item2);
    FDataItem2->Assign(Item3);
    FDataItem3->Assign(Item4);
    FDataItem4->Assign(Item5);
    FDataItem5->Assign(Item6);
    for(int i=0;i<Items->Count;i++)
      FDataItem6->Add("");
  }
  else
  {
    FDataItem1->Assign(Item2);
    FDataItem2->Assign(Item3);
    FDataItem3->Assign(Item4);
    FDataItem4->Assign(Item5);
    FDataItem5->Assign(Item6);
    FDataItem6->Assign(Item7);
  }
}

//---------------------------------------------------------------------------
void __fastcall TZComboBox::SetBorderColor(TColor value)
{
  FBorderColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::SetHoverColor(TColor value)
{
  FHoverColor=value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::SetComboBoxFlat(bool value)
{
  FComboBoxFlat=value;
  if(value)
  {
	Ctl3D = false;
	ParentColor = true;
  }
   Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZComboBox::CreateParams(TCreateParams &Params)
{
   TComboBox::CreateParams(Params);
   if(FComboBoxFlat)
	  Params.Style = Params.Style | CBS_OWNERDRAWFIXED | CBS_OWNERDRAWVARIABLE;
}

