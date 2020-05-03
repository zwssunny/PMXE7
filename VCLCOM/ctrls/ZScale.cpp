//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZScale.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZScale *)
{
  new TZScale(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZScale::TZScale(TComponent* Owner)
  : TGraphicControl(Owner)
{
  FBeginValue=0;
  FBackColor=clWhite;
  FForeColor=clBlack;
  FDirect=drTopToBottom;
  FGraduate=gdMillimeter;
  Canvas->Brush->Color=clWhite;
  Canvas->Pen->Color=clBlack;
  Canvas->Pen->Mode=pmCopy;
  Canvas->Font->Size=8;
  TGraphicControl::Width=200;
  TGraphicControl::Height=20;
}
//---------------------------------------------------------------------------
namespace Zscale
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZScale)};
	 RegisterComponents("ZOther", classes, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TZScale::WMPaint(TWMPaint &Message)
{
  TGraphicControl::Dispatch(&Message);
  DrawScale();
}
//---------------------------------------------------------------------------
void __fastcall TZScale::WMSize(TWMSize &Message)
{
  TGraphicControl::Dispatch(&Message);
  DrawScale();
}
//----------------------------------------------------------------------

void __fastcall TZScale::SetBackColor(TColor value)
{
  FBackColor=value;
  Canvas->Brush->Color=(TColor)ColorToRGB(value);
  DrawScale();
}

//----------------------------------------------------------------------
void __fastcall TZScale::SetForeColor(TColor value)
{
  FForeColor=(TColor)ColorToRGB(value);
  Canvas->Pen->Color=(TColor)ColorToRGB(value);
  DrawScale();
}
//----------------------------------------------------------------------
void __fastcall TZScale::SetDirect(TDirect value)
{
  if(Align==alTop)
    FDirect=drTopToBottom;
  else if(Align==alBottom)
    FDirect=drBottomToTop;
  else if(Align==alLeft)
    FDirect=drLeftToRight;
  else if(Align==alRight)
    FDirect=drRightToLeft;
  else
    FDirect=value;
  DrawScale();
}

//----------------------------------------------------------------------
void __fastcall TZScale::SetGraduate(TGraduate value)
{
  FGraduate=value;
  DrawScale();
}

void __fastcall TZScale::DrawScale()
{
  int ScaleLen,DrawedWidth,Counter;
  Canvas->FillRect(ClientRect);
  switch(FGraduate)
  {
    case 0:
      ScaleLen=DataCarry(Screen->PixelsPerInch/25.4,0,0);
      break;
    case 1:
      ScaleLen=DataCarry(Screen->PixelsPerInch/2.54,0,0);
      break;
    case 2:
      ScaleLen=DataCarry(Screen->PixelsPerInch/0.254,0,0);
      break;
    case 3:
      ScaleLen=Screen->PixelsPerInch;
      break;
    default:
      ScaleLen=DataCarry(Screen->PixelsPerInch/25.4,0,0);
      break;
  }
  DrawedWidth=0;
  Counter=FBeginValue;
  if(FDirect==drTopToBottom)
  {
    Canvas->PenPos=TPoint(0,0);
    Canvas->LineTo(Width-1,0);

    while(DrawedWidth<Width)
    {
      Canvas->PenPos=TPoint(DrawedWidth,0);
      if(Mod(Counter,10)==10 || Mod(Counter,10)==0)
      {
        Canvas->LineTo(DrawedWidth,15);
        Canvas->TextOut(DrawedWidth+2,5,String(Counter/10));
      }
      else if(Mod(Counter,5)==5)
        Canvas->LineTo(DrawedWidth,10);
      else
        Canvas->LineTo(DrawedWidth,5);

      DrawedWidth+=ScaleLen;
      Counter++;
    }
  }
  else if(FDirect==drBottomToTop)
  {
    Canvas->PenPos=TPoint(0,Height-1);
    Canvas->LineTo(Width-1,Height-1);

    while(DrawedWidth<Width)
    {
      Canvas->PenPos=TPoint(DrawedWidth,Height-1);
      if(Mod(Counter,10)==10 || Mod(Counter,10)==0)
      {
        Canvas->LineTo(DrawedWidth,Height-16);
        Canvas->TextOut(DrawedWidth+2,Height-18,String(Counter/10));
      }
      else if(Mod(Counter,5)==5)
        Canvas->LineTo(DrawedWidth,Height-11);
      else
        Canvas->LineTo(DrawedWidth,Height-6);

      DrawedWidth+=ScaleLen;
      Counter++;

    }
  }
  else if(FDirect==drLeftToRight)
  {
    Canvas->PenPos=TPoint(0,0);
    Canvas->LineTo(0,Height-1);
	while(DrawedWidth<Height)
    {
      Canvas->PenPos=TPoint(0,DrawedWidth);
      if(Mod(Counter,10)==10 || Mod(Counter,10)==0)
      {
        Canvas->LineTo(15,DrawedWidth);
        Canvas->TextOut(6,DrawedWidth+2,String(Counter/10));
      }
      else if(Mod(Counter,5)==5)
        Canvas->LineTo(10,DrawedWidth);
      else
        Canvas->LineTo(5,DrawedWidth);
        
      DrawedWidth+=ScaleLen;
      Counter++;        
    }
  }
  else if(FDirect==drRightToLeft)
  {
    Canvas->PenPos=TPoint(Width-1,0);
    Canvas->LineTo(Width-1,Height-1);
	while(DrawedWidth<Height)
    {
      Canvas->PenPos=TPoint(Width-1,DrawedWidth);
      if(Mod(Counter,10)==10 || Mod(Counter,10)==0)
      {
        Canvas->LineTo(Width-16,DrawedWidth);
        Canvas->TextOut(Width-18,DrawedWidth+2,String(Counter/10));
      }
      else if(Mod(Counter,5)==5)
        Canvas->LineTo(Width-11,DrawedWidth);
      else
        Canvas->LineTo(Width-6,DrawedWidth);
        
      DrawedWidth+=ScaleLen;
      Counter++;        
    }
  }
}


double __fastcall TZScale::DataCarry(double data,int scale,int method)
{
  String FStr,FDec,FTmp,FormatStr;
  int FPos,Value,Factor,FInt;
  double FResult;
  bool CarryFlg;
  if(scale<0)
    throw Exception("小数位数不能小于零");
  if(method!=0 && method!=1 && method!=2)
    throw Exception("取数方法只能是0-四舍五入,1-小数取整,2-向上取整");
  FStr=FormatFloat("0.###############",data);
  FPos=FStr.Pos(".");
  if(FPos==0)
    return data;
  if(scale==0)
    Factor=1;
  else
  {
    FTmp="1";
    for(int i=0;i<scale;i++)
      FTmp+="0";
    Factor=FTmp.ToInt();
  }
  switch(method)
  {
    case 0:
      if(FStr.Length()-FPos<=scale)
        return data;
      else
      {
        FDec=FStr.SubString(FPos+1,FStr.Length());
        CarryFlg=false;
        for(int i=FDec.Length();i>scale;i--)
        {
          if(CarryFlg)
          {
            Value=StrToInt(FDec[i])+1;
            if(Value>=5)
              CarryFlg=true;
            else
              CarryFlg=false;
          }
          else
          {
            if(FDec[i]>='5')
              CarryFlg=true;
            else
              CarryFlg=false;
          }
        }
        if(CarryFlg)
          FInt=data*Factor+1;
        else
          FInt=data*Factor;
        FResult=(double)FInt/Factor;
        return FResult;
      }
    case 1:
      if(FStr.Length()-FPos<=scale)
        return data;
      else
      {
        FInt=data*Factor;
        FResult=(double)FInt/Factor;
        return FResult;
      }
    case 2:
      if(FStr.Length()-FPos<=scale)
        return data;
      else
      {
        FInt=data*Factor+1;
        FResult=(double)FInt/Factor;
        return FResult;
      }
    default:
      return 0;
  }
}


double __fastcall TZScale::Mod(double x,double y)
{
  while(x>y)
    x-=y;
  return x;
}


void __fastcall TZScale::SetAlign(TAlign value)
{
  TGraphicControl::Align=value;
  if(value==alTop)
    FDirect=drTopToBottom;
  else if(value==alBottom)
    FDirect=drBottomToTop;
  else if(value==alLeft)
    FDirect=drLeftToRight;
  else if(value==alRight)
    FDirect=drRightToLeft;
}

TAlign __fastcall TZScale::GetAlign()
{
  return TGraphicControl::Align;
}

void __fastcall TZScale::SetBeginValue(int value)
{
  FBeginValue=value;
  DrawScale();
}
