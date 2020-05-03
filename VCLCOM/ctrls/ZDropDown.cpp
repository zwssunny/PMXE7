//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZDropDown.h"
#pragma link "ZEdit"
#pragma package(smart_init)
#pragma resource "ZVCLSR.RES"
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZDropDown *)
{
  new TZDropDown(NULL);
}
//---------------------------------------------------------------------------
namespace Zdropdown
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZDropDown)};
	 RegisterComponents("ZStandard", classes, 0);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TZPopupForm : public TForm
{
public:
    TZDropDown *DropDown;
    void __fastcall PopupFormClose(System::TObject* Sender, TCloseAction &Action)
    {
        Action = caHide;
        SendMessage(DropDown->Handle,EM_SETMARGINS,EC_RIGHTMARGIN,MAKELONG(0,18));
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
    __fastcall TZPopupForm(TZDropDown*ADropDown)
               : TForm(ADropDown, 0), DropDown(ADropDown)
    {
        BorderStyle = bsNone;
        HorzScrollBar->Visible = false;
        VertScrollBar->Visible = false;
        FormStyle = fsStayOnTop;

        OnClose = PopupFormClose;
    }
    void ShowForm()
    {
        Show();
        SetFocus();
    }
};
//---------------------------------------------------------------------------
__fastcall TZDropDown::TZDropDown(TComponent* Owner)
  : TZEdit(Owner)
{
    FInitedData = false;
    //ButtonVisible = true;
    FDropForm = NULL;
    OnButtonClick = DropDownOnButtonClick;
}
//---------------------------------------------------------------------------
__fastcall TZDropDown::~TZDropDown()
{
}
//---------------------------------------------------------------------------
void TZDropDown::LoadButtonBitmap(Graphics::TBitmap*ABitmap)
{
    ABitmap->LoadFromResourceName((int)HInstance,"DROPDOWNBTNMAP");
    if(FOnLoadPicture)
        FOnLoadPicture(this, ABitmap);
}
//---------------------------------------------------------------------------
void __fastcall TZDropDown::DropDownOnButtonClick(System::TObject* Sender)
{
    InitData();
    if(FOnDropDownDropDown)
        FOnDropDownDropDown(this, FDropForm);

    if(ClientOrigin.y + FDropForm->Height + 50 > Screen->Height)
        FDropForm->Top = ClientOrigin.y - FDropForm->Height - 5;
    else
        FDropForm->Top = ClientOrigin.y + Height;
    if(ClientOrigin.x + FDropForm->Width + 50 > Screen->Width)
        FDropForm->Left = ClientOrigin.x - FDropForm->Width + Width;
    else
        FDropForm->Left = ClientOrigin.x;
    ((TZPopupForm*)(FDropForm))->ShowForm();
}
//---------------------------------------------------------------------------
void TZDropDown::InitData()
{
    if(!FInitedData)
	{
        FInitedData = true;
		FDropForm = new TZPopupForm(this);
        FDropForm->Width = Width;
        FDropForm->Height = 100;
		FDropForm->Color = clWhite;
        if(FOnDropDownInitData)
            FOnDropDownInitData(this, FDropForm);
    }
}
//---------------------------------------------------------------------------

