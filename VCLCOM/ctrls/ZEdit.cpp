//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZEdit.h"
#pragma package(smart_init)
#pragma resource "ZVCLSR.RES"
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZEdit *)
{
  new TZEdit(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZEdit::TZEdit(TComponent* Owner)
  : TEdit(Owner)
{

  FEditButton=new TSpeedButton(this);
  FEditButton->Visible=false;
  LoadButtonBitmap(FEditButton->Glyph);

  FEditButton->OnClick=ButtonClick;
  FEditButton->Cursor=crHandPoint;
  FEditButton->Top=-1;
  FEditButton->Width=21;
  FEditButton->Enabled=TEdit::Enabled;
  FEditButton->Flat=true;
  FEditButton->Transparent=true;

  FDataItem1=new TStringList;
  FDataItem2=new TStringList;
  FDataItem3=new TStringList;
  FDataItem4=new TStringList;
  FDataItem5=new TStringList;
  FDataItem6=new TStringList;
  FDataItem7=new TStringList;
  FKeyItem=cbItem1;
  FDispItem=cbItem2;
  FItemIndex=-1;
  FMultiDisplay=false;
  FSplitSymbol=" | ";
  FMatch=false;
  FDefaultValue="";
  FBorderColor=crBorderColor;
  FFocusedColor=clWhite;
  FHoverColor=crFocusedColor;
  FEditFlat=false;
  Ctl3D=false;//zws20080616
  FBkColor = Color;
  FIsCurrency = false;
  FCharType=TZCharType::ctNormal;
}
//---------------------------------------------------------------------------
__fastcall TZEdit::~TZEdit()
{
  delete FEditButton;
  delete FDataItem1;
  delete FDataItem2;
  delete FDataItem3;
  delete FDataItem4;
  delete FDataItem5;
  delete FDataItem6;
  delete FDataItem7;
}
//---------------------------------------------------------------------------
void TZEdit::LoadButtonBitmap(Graphics::TBitmap*ABitmap)
{
  ABitmap->LoadFromResourceName((int)HInstance,"GRIDDOWN");
}
//---------------------------------------------------------------------------
namespace Zedit
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZEdit)};
     RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::CMMouseEnter(TMessage &Message)
{
  TEdit::Dispatch(&Message);
  if(FEditFlat)
  {
    FIsHovered=true;
    if(FIsFocused)
    {
       Color=FFocusedColor;
    }else
       Color=FHoverColor;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::CMMouseLeave(TMessage &Message)
{
  TEdit::Dispatch(&Message);
  if(FEditFlat)
  {
    FIsHovered=false;
    if(FIsFocused)
       Color=FFocusedColor;
    else
       ParentColor=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::WMSetFocus(TWMSetFocus &Message)
{
//   if(IsWindow(TEdit::Handle))
   {
      TEdit::Dispatch(&Message);
      if(FEditFlat)
      {
          FIsFocused=true;
          Color=FFocusedColor;
      }
      SelStart = 0;
      SelLength = Text.Length();
   }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::WMKillFocus(TWMSetFocus &Message)
{
    TEdit::Dispatch(&Message);
    if(FEditFlat)
    {
      FIsFocused=false;
      if(FIsHovered)
        Color=FHoverColor;
      else
        ParentColor=true;
    }
    switch(FCharType)
    {
		case TZCharType::ctNormal:
            break;
        case ctCharacter: //除数字以外的所有字符
            break;
        case ctLetter:   //仅仅字母
            break;
        case ctPlus:     //正整数
            if(Text == "")
                Text = "0";
            break;
        case ctNegative:  //负整数
            if(Text == "")
                Text = "0";
            if(Text == "-")
                Text = "0";
            break;
        case ctInteger:  //整数
            if(Text == "")
                Text = "0";
            if(Text == "-")
                Text = "0";
            break;
        case ctPlusFloat:      //正浮点数
            if(Text == "")
                Text = "0";
            break;
        case ctNegativeFloat:  //负浮点数
            if(Text == "")
                Text = "0";
            if(Text == "-")
                Text = "0";
            break;
        case ctFloat:
            if(Text == "")
                Text = "0";
            if(Text == "-")
                Text = "0";
            break;
        case ctID:             //第一个字母，以后字母,数字，"-"号
            break;
        case ctSelfDefine:   //自定义
            break;
        default:
            throw Exception("数据类型未定义");
    }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::WMPaint(TWMPaint &Message)
{
  if(ButtonVisible)
      SendMessage(Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
  TEdit::Dispatch(&Message);
 /* if(FEditFlat)
	DrarFlatEdit();
  else if (!Ctl3D)*/
    ClearCtrlBorder(this, (TColor)ColorToRGB(FBorderColor));
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::WMSize(TWMSize &Message)
{
  TEdit::Dispatch(&Message);
  if(FEditButton)
  {
    FEditButton->Left=TEdit::Width-20;
    FEditButton->Height=TEdit::Height+1;
  }
}
void __fastcall TZEdit::WMLButtonDown(TMessage &Message)
{
   if(Focused())
      TEdit::Dispatch(&Message);
   else{
      TEdit::Dispatch(&Message);
      SelStart = 0;
      SelLength = Text.Length();
   }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::DrarFlatEdit()
{
  if(!FEditFlat)
    return;
  if(!FIsHovered && !FIsFocused)
    ParentColor=true;
  HBRUSH brush;
  TRect FRect;
  HDC dc = GetDC(Handle);
  brush=CreateSolidBrush(ColorToRGB(FBorderColor));
  HBRUSH oldbrush = (HBRUSH)SelectObject(dc,brush);
  FRect.Left=ClientRect.Left;
  FRect.Top=ClientRect.Top;
//  if(ButtonVisible)
//    FRect.Right=ClientRect.Right-18;
//  else
    FRect.Right=ClientRect.Right;
  FRect.Bottom=ClientRect.Bottom;
  FrameRect(dc,&FRect,brush);
  SelectObject(dc, oldbrush);
  DeleteObject(brush);
  ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::ClearCtrlBorder(TWinControl* WinControl, TColor color)
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
void __fastcall TZEdit::SetDigLen(int Len)
{
    if(MaxLength==0||MaxLength>Len+1)
      FDigLen=Len;
    else
      FDigLen=0;
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::Change(void)
{
  if(Trim(TEdit::Text).IsEmpty())
  {
    ItemIndex=-1;
    TEdit::SelStart=0;
    TEdit::SelLength=TEdit::Text.Length();
  }
  TEdit::Change();
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::DoExit(void)
{
  if(FMatch)
    LocateKey(this->Text);
  double DoubleValue;
  SetSdEditText(TEdit::Text);
/*  if (FIsCurrency && FCharType == ctFloat && (!TEdit::Text.IsEmpty()))
       = GetDoublevalue(TEdit::Text);
  if (FIsCurrency && FCharType == ctFloat && (!TEdit::Text.IsEmpty())
      && TryStrToFloat(TEdit::Text,DoubleValue))
  {
     TEdit::Text = FormatFloat("#,##",DoubleValue);
  } */
  TEdit::DoExit();
}
//---------------------------------------------------------------------------

void __fastcall TZEdit::KeyPress(Char &Key)
{
//    if(ReadOnly)
//       return;
    if(Key==VK_RETURN)
    {
        if(FMatch)
             LocateKey(this->Text);
        if(TabStop)
        {
             if(IsWindowVisible(TEdit::Handle))
                  GetParentForm(this)->Perform(WM_NEXTDLGCTL,0,FALSE);
        }
        Key=0;
    }else if(Key!=8)
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
		if(FCharType != TZCharType::ctNormal)
        {
			Char* c = FValidChar.c_str();
            for(int i = 0; i <= FValidChar.Length(); i++)
            {
                if(Key == *c)
                    goto labelValidChar;
                c++;
            }
            Key = 0;
        }else if(MaxLength > 0 && Text.Length() >= MaxLength && SelLength == 0)
        {
            Key = 0;
        }
        TEdit::KeyPress(Key);
        return;
    labelValidChar:
//        if(SelLength==Text.Length())
//        {
//           SelText=Key;
//           Key=0;
//        }
        switch(FCharType)
        {
            case ctCharacter:
                if(Key >= 48 && Key <= 57)
                {
                    Key = 0;
                }else if(DigLen > 0 && SelStart > DigLen)
                {
                    Key = 0;
                }else if(DigLen > 0 && Text.Length() >= DigLen && SelLength == 0)
                {
                    Key = 0;
                }
                break;
            case ctLetter:   //仅仅字母
                if(Key < 65 || (Key > 90 && Key < 97) || Key > 122)
                {
                    Key = 0;
                }else if(DigLen > 0 && SelStart > DigLen)
                {
                    Key = 0;
                }else if(DigLen > 0 && Text.Length() >= DigLen && SelLength == 0)
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
                    if(DigLen==0) Key=0;
                    else
                    {
                      int Pos = Text.Pos(".");
                      if(Pos > 0)
                      {
                           Key = 0;
                      }else
                      {
                           String Late = Text.SubString(SelStart+1, 10000);
                           if(DigLen > 0 && Late.Length() > DigLen && SelLength == 0)
                           {
                               Key = 0;
                           }
                      }
                  }
                }else
                {//数字
                    int Pos = Text.Pos(".");
                    if(Pos > 0 && DigLen >= 0 && SelStart+1 > Pos && Text.Length() - Pos >= DigLen)
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
                            if((MaxLength > 0 && Front.Length() >= MaxLength - DigLen - 1) &&
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
                   if(DigLen==0) Key=0;
                   else
                   {
                      int Pos = Text.Pos(".");
                      if(Pos > 0)
                      {
                           Key = 0;
                      }else
                      {
                           String Late = Text.SubString(SelStart+1, 10000);
                           if(DigLen > 0 && Late.Length() > DigLen && SelLength == 0)
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
                         if(Pos > 0 && DigLen >= 0 && SelStart+1 > Pos && Text.Length() - Pos >= DigLen)
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
                             if((MaxLength > 0 && Front.Length() >= MaxLength - DigLen - 2) &&
                                SelLength == 0)
                             {
                                 Key = 0;
                             }
                         }
                    }
                }
                break;
            case ctFloat:
                if((Key < 48 || Key > 57) && Key != 45 &&  Key != 46 && Key !=',')
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
                    if(DigLen==0) Key=0;
                    else
                    {
                      int Pos = Text.Pos(".");
                      if(Pos > 0)
                      {
                           Key = 0;
                      }else
                      {
                           String Late = Text.SubString(SelStart+1, 10000);
                           if(DigLen > 0 && Late.Length() > DigLen)
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
                        if(Pos > 0 && DigLen >=0 && SelStart+1 > Pos &&
                           Text.Length() - Pos >= DigLen)
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
                            if((MaxLength > 0 && Front.Length() >= MaxLength - DigLen - 1) &&
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
                if(DigLen > 0 && SelStart > DigLen)
                {
                    Key = 0;
                }else if(DigLen > 0 && Text.Length() >= DigLen && SelLength == 0)
                {
                    Key = 0;
                }
                break;
            case ctSelfDefine:   //自定义
                if(DigLen > 0 && SelStart > DigLen)
                {
                    Key = 0;
                }else if(DigLen > 0 && Text.Length() >= DigLen && SelLength == 0)
                {
                    Key = 0;
                }
                break;
            default:
                throw Exception("类型未定义！");
        }
    }
    TEdit::KeyPress(Key);
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetCharType(TZCharType AType)
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
            if (FIsCurrency)
               FValidChar += ",";
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
String __fastcall TZEdit::GetDefaultValue()
{
    return FDefaultValue;
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetDefaultValue(String value)
{
    double doubleValue;
    try
    {
        switch(FCharType)
        {
			case TZCharType::ctNormal:
                break;
            case ctCharacter: //除数字以外的所有字符
                break;
            case ctLetter:   //仅仅字母
                break;
            case ctPlus:     //正整数
                value.ToInt();
                break;
            case ctNegative:  //负整数
                value.ToInt();
                break;
            case ctInteger:  //整数
                value.ToInt();
                break;
            case ctPlusFloat:      //正浮点数
                value.ToDouble();
                break;
            case ctNegativeFloat:  //负浮点数
                value.ToDouble();
                break;
            case ctFloat:
                TryStrToFloat(value,doubleValue);
                break;
            case ctID:             //第一个字母，以后字母,数字，"-"号
                break;
            case ctSelfDefine:   //自定义
                break;
            default:
                throw Exception("数据类型未定义");
        }
        FDefaultValue = value;
    }
    catch(...)
    {
        throw Exception("数据类型不正确");
    }
}
//---------------------------------------------------------------------------
void _fastcall TZEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
   TEdit::KeyDown(Key,Shift);
   if (Key == VK_DOWN)
   {
       if(TabStop)
       {
          if(IsWindowVisible(TEdit::Handle))
            GetParentForm(this)->Perform(WM_NEXTDLGCTL,0,FALSE);
       }
       Key=0;
   }else if (Key==VK_UP)
   {
       if(TabStop)
       {
          if(IsWindowVisible(TEdit::Handle))
            GetParentForm(this)->Perform(WM_NEXTDLGCTL,1,FALSE);
       }
       Key=0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TZEdit::ButtonClick(TObject *Sender)
{
  if(FOnButtonClick)
    FOnButtonClick(this);
//  if(TEdit::Enabled && TEdit::Visible)
//    TEdit::SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall TZEdit::SetButtonFlat(bool value)
{
  FEditButton->Flat = value;
}
//---------------------------------------------------------------------------
bool __fastcall TZEdit::GetButtonFlat()
{
  return FEditButton->Flat;
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetButtonVisible(bool value)
{
  if(value)
  {
    FEditButton->Parent=this;
    //FEditButton->Left=this->Left+this->Width-20;
    //FEditButton->Height=TEdit::Height-1;
    if(ButtonVisible)
        SendMessage(this->Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
  }
  else
  {
    FEditButton->Parent = NULL;
    SendMessage(this->Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,0));
  }
  FEditButton->Visible = value;
}
//---------------------------------------------------------------------------
bool __fastcall TZEdit::GetButtonVisible()
{
  return FEditButton->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetButtonTransparent(bool value)
{
  FEditButton->Transparent=value;
}
//---------------------------------------------------------------------------
bool __fastcall TZEdit::GetButtonTransparent()
{
  return FEditButton->Transparent;
}
//---------------------------------------------------------------------------

bool __fastcall TZEdit::LocateKey(String value)
{
  int index;
  String s;
  switch(FKeyItem)
  {
    case cbItem1:
      index=FDataItem1->IndexOf(value);
      break;
    case cbItem2:
      index=FDataItem2->IndexOf(value);
      break;
    case cbItem3:
      index=FDataItem3->IndexOf(value);
      break;
	case cbItem4:
      index=FDataItem4->IndexOf(value);
	  break;
    case cbItem5:
      index=FDataItem5->IndexOf(value);
      break;
	case cbItem6:
      index=FDataItem6->IndexOf(value);
      break;
    case cbItem7:
      index=FDataItem7->IndexOf(value);
      break;
  }
  FItemIndex=index;
  if(index!=-1)
  {
    if(FMultiDisplay)
    {
      s="<"+FDataItem1->Strings[index]+">";

	  switch(FDispItem)
      {
        case cbItem1:
          s+=FDataItem1->Strings[index];
          break;
        case cbItem2:
          s+=FDataItem2->Strings[index];
          break;
        case cbItem3:
          s+=FDataItem3->Strings[index];
          break;
        case cbItem4:
          s+=FDataItem4->Strings[index];
          break;
        case cbItem5:
          s+=FDataItem5->Strings[index];
          break;
        case cbItem6:
          s+=FDataItem6->Strings[index];
          break;
        case cbItem7:
          s+=FDataItem7->Strings[index];
          break;
      }
    }
    else
      s=FDataItem1->Strings[index];
  }
  this->Text=s;
  if(index==-1)
    return false;
  else
    return true;
}
//---------------------------------------------------------------------------
String __fastcall TZEdit::GetItemData(int Index)
{
  if(Index<0 || Index>6)
    return FDefaultValue;
  if(ItemIndex==-1)
  {
    Text="";
    return FDefaultValue;
  }
  if(Trim(TEdit::Text).IsEmpty())
  {
    ItemIndex=-1;
    return FDefaultValue;
  }
  switch((TZComboBoxItemIndex)Index)
  {
	case cbItem1:
	  return FDataItem1->Strings[FItemIndex];
    case cbItem2:
      return FDataItem2->Strings[FItemIndex];
    case cbItem3:
      return FDataItem3->Strings[FItemIndex];
    case cbItem4:
      return FDataItem4->Strings[FItemIndex];
    case cbItem5:
      return FDataItem5->Strings[FItemIndex];
    case cbItem6:
      return FDataItem6->Strings[FItemIndex];
    case cbItem7:
	  return FDataItem7->Strings[FItemIndex];
	default:
	  return FDefaultValue;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetItemData(int Index,String value)
{
   if(Index<0 || Index>6||ItemIndex==-1)
	throw Exception("Out of Index");
  switch((TZComboBoxItemIndex)Index)
  {
	case cbItem1:
	   FDataItem1->Strings[ItemIndex]=value;
	   break;
	case cbItem2:
	  FDataItem2->Strings[ItemIndex]=value;
	  break;
	case cbItem3:
	  FDataItem3->Strings[ItemIndex]=value;
	  break;
	case cbItem4:
	  FDataItem4->Strings[ItemIndex]=value;
	  break;
	case cbItem5:
	  FDataItem5->Strings[ItemIndex]=value;
	  break;
	case cbItem6:
	  FDataItem6->Strings[ItemIndex]=value;
	  break;
	case cbItem7:
	  FDataItem7->Strings[ItemIndex]=value;
	  break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TZEdit::ClearAll()
{
  FDataItem1->Clear();
  FDataItem2->Clear();
  FDataItem3->Clear();
  FDataItem4->Clear();
  FDataItem5->Clear();
  FDataItem6->Clear();
  FDataItem7->Clear();
  FItemIndex=-1;
}

//---------------------------------------------------------------------------
void __fastcall TZEdit::AddItems(String Item1,String Item2,String Item3,String Item4,
    String Item5,String Item6,String Item7)
{
    FDataItem1->Add(Item1);
    FDataItem2->Add(Item2);
    FDataItem3->Add(Item3);
    FDataItem4->Add(Item4);
    FDataItem5->Add(Item5);
    FDataItem6->Add(Item6);
    FDataItem7->Add(Item7);
}
//---------------------------------------------------------------------------

void __fastcall TZEdit::AssignItems(TStringList *Item1,TStringList *Item2,TStringList *Item3,TStringList *Item4,
    TStringList *Item5,TStringList *Item6,TStringList *Item7)
{
  FDataItem1->Assign(Item1);
  if(Item2==NULL)
  {
    for(int i=0;i<FDataItem1->Count;i++)
    {
      FDataItem2->Add("");
      FDataItem3->Add("");
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
      FDataItem7->Add("");
    }
  }
  else if(Item3==NULL)
  {
    FDataItem2->Assign(Item2);
    for(int i=0;i<FDataItem1->Count;i++)
    {
      FDataItem3->Add("");
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
      FDataItem7->Add("");
    }
  }
  else if(Item4==NULL)
  {
    FDataItem2->Assign(Item2);
    FDataItem3->Assign(Item3);
    for(int i=0;i<FDataItem1->Count;i++)
    {
      FDataItem4->Add("");
      FDataItem5->Add("");
      FDataItem6->Add("");
      FDataItem7->Add("");
    }
  }
  else if(Item5==NULL)
  {
    FDataItem2->Assign(Item2);
    FDataItem3->Assign(Item3);
    FDataItem4->Assign(Item4);
    for(int i=0;i<FDataItem1->Count;i++)
    {
      FDataItem5->Add("");
      FDataItem6->Add("");
      FDataItem7->Add("");
    }
  }
  else if(Item6==NULL)
  {
    FDataItem2->Assign(Item2);
    FDataItem3->Assign(Item3);
    FDataItem4->Assign(Item4);
    FDataItem5->Assign(Item5);
    for(int i=0;i<FDataItem1->Count;i++)
    {
      FDataItem6->Add("");
      FDataItem7->Add("");
    }
  }
  else if(Item7==NULL)
  {
    FDataItem2->Assign(Item2);
    FDataItem3->Assign(Item3);
    FDataItem4->Assign(Item4);
    FDataItem5->Assign(Item5);
    FDataItem6->Assign(Item6);
    for(int i=0;i<FDataItem1->Count;i++)
      FDataItem7->Add("");
  }
  else
  {
    FDataItem2->Assign(Item2);
    FDataItem3->Assign(Item3);
    FDataItem4->Assign(Item4);
    FDataItem5->Assign(Item5);
    FDataItem6->Assign(Item6);
    FDataItem7->Assign(Item7);
  }
}
//---------------------------------------------------------------------------


void __fastcall TZEdit::SetItemIndex(int value)
{
  String s;
  if(value>-1 && value<FDataItem1->Count)
  {
    FItemIndex=value;
    if(FMultiDisplay)
    {
      s="<"+FDataItem1->Strings[value]+">";
      //s+=String(" ")+FSplitSymbol+String(" ");
      switch(FDispItem)
      {
        case cbItem1:
          s+=FDataItem1->Strings[value];
          break;
        case cbItem2:
          s+=FDataItem2->Strings[value];
          break;
        case cbItem3:
          s+=FDataItem3->Strings[value];
          break;
        case cbItem4:
          s+=FDataItem4->Strings[value];
          break;
        case cbItem5:
          s+=FDataItem5->Strings[value];
          break;
        case cbItem6:
          s+=FDataItem6->Strings[value];
          break;
        case cbItem7:
          s+=FDataItem7->Strings[value];
          break;
      }
    }
    else
      s=FDataItem1->Strings[value];
  }
  else
  {
    FItemIndex=-1;
  }
  this->Text=s;
}

//---------------------------------------------------------------------------
bool __fastcall TZEdit::GetEnabled()
{
  return TEdit::Enabled;
}
void __fastcall TZEdit::SetEnabled(bool value)
{
  TEdit::Enabled=value;
  FEditButton->Enabled=value;
}

//---------------------------------------------------------------------------
String __fastcall TZEdit::GetSdEditText()
{
  double DoubleValue;
  if(TEdit::Text.IsEmpty())
    return FDefaultValue;
  else
  {
    if (FIsCurrency && (FCharType == ctFloat || FCharType ==ctPlusFloat))
    {
         return GetDoublevalue(TEdit::Text);
    }
    else
       return TEdit::Text;
  }
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetSdEditText(String value)
{
   double  DoubleValue;
   String FFormatStr;
  if (FIsCurrency && (FCharType == ctFloat || FCharType ==ctPlusFloat)&& (!TEdit::Text.IsEmpty()))
      value = GetDoublevalue(value);
  if (FIsCurrency && (FCharType == ctFloat || FCharType ==ctPlusFloat) && TryStrToFloat(value,DoubleValue))
  {
         if (FDigLen == 0)
             FFormatStr ="#,##0.00";
         else
             FFormatStr ="#,##0."+String("0000000000").SubString(1,FDigLen);
         TEdit::Text = FormatFloat(FFormatStr,DoubleValue);
  }
  else
      TEdit::Text=value;
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetBorderColor(TColor value)
{
  FBorderColor=value;
//  this->Repaint();
        this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetFocusedColor(TColor value)
{
  FFocusedColor=value;
//  this->Repaint();
        this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetHoverColor(TColor value)
{
  FHoverColor=value;
//  this->Repaint();
        this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::SetEditFlat(bool value)
{
  FEditFlat=value;
  if(value)
    Ctl3D=false;
//  this->Repaint();
        this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZEdit::WMPaste(TMessage &Message)
{
    String Bk = Text;
    TEdit::Dispatch(&Message);
    if(!Valid(Text))
        Text = Bk;
}
//---------------------------------------------------------------------------
bool TZEdit::Valid(String Str)
{
  if(CharType != TZCharType::ctNormal)
  {
	   for(Char* str_c = Str.c_str(); *str_c != '\0'; str_c++)
	   {
		   for(Char* valid_c = FValidChar.c_str(); *valid_c != '\0'; valid_c++)
		   {
			   if(*str_c == *valid_c)
				   goto labelValidChar;
			   valid_c++;
		   }
		   return false;
	   labelValidChar:;
	   }
  }
  double doublevalue;
  switch(CharType)
  {
	  case ctPlus:     //正整数
	  case ctNegative:  //负整数
	  case ctInteger:  //整数
	  case ctPlusFloat:      //正浮点数  和 0
      case ctNegativeFloat:  //负浮点数  和 0
      case ctFloat:          //浮点数
              return(TryStrToFloat(Str,doublevalue));
      case ctID:             //第一个字母，以后字母,数字，"-"号
      case ctSelfDefine:   //自定义
      case TZCharType::ctNormal:
      case ctCharacter: //除数字以外的所有字符
      case ctLetter:   //仅仅字母
      default:;
  }
  return true;
}
//---------------------------------------------------------------------------
String __fastcall TZEdit::GetDoublevalue(String ResoureStr)
{
   String NewStr="";
   for(int i=1;i<=ResoureStr.Length();i++)
   {
       if (ResoureStr.SubString(i,1) != "," )
           NewStr += ResoureStr.SubString(i,1);
   }
   return NewStr;
}
//--------------------------------------------------------------------------
void __fastcall TZEdit::SetCurrency(bool value)
{
    FIsCurrency = value;
    if (FIsCurrency)
    {
       Text = "";
       SetCharType(ctFloat);
    }
}

