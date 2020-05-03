//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZPanel *)
{
  new TZPanel(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZPanel::TZPanel(TComponent* Owner)
  : TPanel(Owner)
{
  FPicture=new TPicture;
  FTransparent = false;
}
//---------------------------------------------------------------------------
__fastcall TZPanel::~TZPanel()
{
  delete FPicture;
}
//---------------------------------------------------------------------------
namespace Zpanel
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZPanel)};
     RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::Paint()
{
  TCustomPanel::Paint();
  DrawPanel();
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::AdjustSize(void)
{
   TPanel::AdjustSize();
   if(FTransparent)
      SetWndRgn();
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::Notification(Classes::TComponent* AComponent, Classes::TOperation Operation)
{
   TPanel::Notification(AComponent, Operation);

}
//---------------------------------------------------------------------------
void __fastcall TZPanel::SetWndRgn()
{
      if(FTransparent)
      {
         HRGN FTransparentRgn = CreateRectRgn(0,0,0,0);
         for(int i = 0; i < ControlCount; i++)
         {
            if(Controls[i]->Visible)
            {
               HRGN Temp = CreateRectRgn(Controls[i]->Left,
                                      Controls[i]->Top,
                                      Controls[i]->Left + Controls[i]->Width,
                                      Controls[i]->Top + Controls[i]->Height);
               CombineRgn(FTransparentRgn, Temp, FTransparentRgn, RGN_OR);
            }
         }
         SetWindowRgn(Handle, FTransparentRgn, true);
      }
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::DrawPanel()
{
  HDC dc;
  if(!FPicture->Bitmap->Empty)
  {
	dc= Canvas->Handle;
    SetStretchBltMode(dc, COLORONCOLOR);
    switch(FStyle)
    {
       case sdpsNone:
          BitBlt(dc,0,0,Width,Height,FPicture->Bitmap->Canvas->Handle,0,0,SRCCOPY);
          break;
       case sdpsTile:
       {
          int VCount = Height / FPicture->Bitmap->Height + 1;
          int HCount = Width / FPicture->Bitmap->Width + 1;
          int BW = FPicture->Bitmap->Width;
          int BH = FPicture->Bitmap->Height;
          for(int i = 0; i < VCount; i++)
             for(int j = 0; j < HCount; j++)
                BitBlt(dc, j*BW, i*BH, Width, Height,FPicture->Bitmap->Canvas->Handle,0,0,SRCCOPY);
          break;
       }
       case sdpsStretch:
          StretchBlt(dc,0,0,Width,Height,FPicture->Bitmap->Canvas->Handle,0,0,FPicture->Width,FPicture->Height,SRCCOPY);
          break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::SetPicture(Graphics::TPicture* Value)
{
  FPicture->Assign(Value);
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::SetStyle(TZPanelStyle Value)
{
  FStyle = Value;
  Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TZPanel::SetTransparent(bool Value)
{
   if(FTransparent != Value)
   {
      FTransparent = Value;
      if(FTransparent)
      {
         SetWndRgn();
      }else
      {
         RecreateWnd();
      }
   }
   Repaint();
}
//---------------------------------------------------------------------------

