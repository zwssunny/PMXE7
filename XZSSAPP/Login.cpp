//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Login.h"
#include "loginShowMethod.h"
#include "Config.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TLoginForm *LoginForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
String __fastcall TLoginForm::get_LogonCode()
{
	return edUserLoginCode->Text;
}
//---------------------------------------------------------------------------
String __fastcall TLoginForm::get_Password()
{
	return edPassword->Text;
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm::btOkClick(TObject *Sender)
{
  if(edUserLoginCode->Text.Trim()=="")
  {
	edUserLoginCode->Text="";
	ShowMessage(L"请输入登录用户名.");
	edUserLoginCode->SetFocus();
	return;
  }
  ModalResult=System::Uitypes::TModalResult(mrOk);
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKBBounds = TRectF(0,0,0,0);
	FNeedOffset = False;
	RestorePosition();
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
 	FKBBounds = TRectF(Bounds);
	FKBBounds = TRectF(ScreenToClient(FKBBounds.TopLeft()),ScreenToClient(FKBBounds.BottomRight()));
	UpdateKBBounds();
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm::UpdateKBBounds()
{
	FNeedOffset = false;
	if (Focused != NULL) {
		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
		TRectF LFocusRect = LFocused->AbsoluteRect;
		LFocusRect.Offset(MainVertScrollBox->ViewportPosition.X, MainVertScrollBox->ViewportPosition.Y);
		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
			FNeedOffset = true;
			MainLayout->Align = TAlignLayout::Horizontal;
			MainVertScrollBox->RealignContent();
			Application->ProcessMessages();
			MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X,
				LFocusRect.Bottom - FKBBounds.Top);
		}
	}
	if (!FNeedOffset) {
		RestorePosition();
	}
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm::RestorePosition()
{
	MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X, 0);
	MainLayout->Align = TAlignLayout::Client;
	MainVertScrollBox->RealignContent();
}
//---------------------------------------------------------------------------

