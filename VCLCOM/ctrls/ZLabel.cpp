//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZLabel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZLabel *)
{
  new TZLabel(NULL);
}
namespace Zlabel
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZLabel)};
	 RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
__fastcall TZLabel::TZLabel(TComponent* Owner)
  : TLabel(Owner)
{
   FHoverFont = new TFont();
   FHoverCursor = Cursor;
   FSuper = false;
   FBindControl = NULL;
   FBindPos = sbpLeft;
   FBindAlign = sbaMiddle;
   FBindAlternation = 3;
}                           
__fastcall TZLabel::~TZLabel()
{
   delete FHoverFont;
}
//---------------------------------------------------------------------------
void __fastcall TZLabel::CMMouseEnter(TMessage &Message)
{
   if(FSuper)
   {
       FBkFont = new TFont();
       FBkFont->Assign(Font);
       Font->Assign(FHoverFont);
       FBkCursor = Cursor;
       Cursor = FHoverCursor;
   }
   if(FOnEnter)
      FOnEnter(this);
}
void __fastcall TZLabel::CMMouseLeave(TMessage &Message)
{
   if(FSuper)
   {
       Font->Assign(FBkFont);
       delete FBkFont;
       Cursor = FBkCursor;
   }
   if(FOnExit)
      FOnExit(this);
}
void __fastcall TZLabel::SetHoverFont(TFont*AFont)
{
   FHoverFont->Assign(AFont);
}
void TZLabel::AdjustBind()
{
   TLabel::AdjustBounds();
   if(!FBindControl)
      return;
   switch(FBindPos)
   {
      case sbpLeft:
          FBindControl->Left = Left - FBindAlternation - FBindControl->Width;
          switch(FBindAlign)
          {
              case sbaMin:
                 FBindControl->Top = Top;
                 break;
              case sbaMiddle:
                 FBindControl->Top = (Top + Top + Height) / 2 - FBindControl->Height / 2;
                 break;
              case sbaMax:
                 FBindControl->Top = Top + Height - FBindControl->Height;
                 break;
          }
          break;
      case sbpTop:
          FBindControl->Top = Top - FBindAlternation - FBindControl->Height;
          switch(FBindAlign)
          {
              case sbaMin:
                 FBindControl->Left = Left;
                 break;
              case sbaMiddle:
                 FBindControl->Left = (Left + Left + Width) / 2 - FBindControl->Width / 2;
                 break;
              case sbaMax:
                 FBindControl->Left = Left + Width - FBindControl->Width;
                 break;
          }
          break;
      case sbpRight:
          FBindControl->Left = Left + Width + FBindAlternation;
          switch(FBindAlign)
          {
              case sbaMin:
                 FBindControl->Top = Top;
                 break;
              case sbaMiddle:
                 FBindControl->Top = (Top + Top + Height) / 2 - FBindControl->Height / 2;
                 break;
              case sbaMax:
                 FBindControl->Top = Top + Height - FBindControl->Height;
                 break;
          }
          break;
      case sbpBottom:
          FBindControl->Top = Top + Height + FBindAlternation;
          switch(FBindAlign)
          {
              case sbaMin:
                 FBindControl->Left = Left;
                 break;
              case sbaMiddle:
                 FBindControl->Left = (Left + Left + Width) / 2 - FBindControl->Width / 2;
                 break;
              case sbaMax:
                 FBindControl->Left = Left + Width - FBindControl->Width;
                 break;
          }
          break;
   }
}
void __fastcall TZLabel::SetBindControl(TControl* ABindControl)
{
   FBindControl = ABindControl;
   AdjustBind();
}
void __fastcall TZLabel::SetBindPos(TZBindPos ABindPos)
{
   FBindPos = ABindPos;
   AdjustBind();
}
void __fastcall TZLabel::SetBindAlign(TZBindAlign ABindAlign)
{
   FBindAlign = ABindAlign;
   AdjustBind();
}
void __fastcall TZLabel::SetBindAlternation(int ABindAlternation)
{
   FBindAlternation = ABindAlternation;
   AdjustBind();
}

