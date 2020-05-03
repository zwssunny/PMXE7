//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CommBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TCommBaseForm *CommBaseForm;
//---------------------------------------------------------------------------
__fastcall TCommBaseForm::TCommBaseForm(TComponent* Owner,TClientBroker * ABroker)
	: TForm(Owner)
{
	FBroker=ABroker;
	FQuery=new TZClientQuery(this,FBroker);
	InitControl();
	ItemVertScrollBox->OnCalcContentBounds = CalcContentBoundsProc;
	FKeyboardShow=false;
}
//---------------------------------------------------------------------------
__fastcall TCommBaseForm::~TCommBaseForm()
{
    delete FQuery;
}
//---------------------------------------------------------------------------

void __fastcall TCommBaseForm::btCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TCommBaseForm::CalcContentBoundsProc(TObject * Sender, System::Types::TRectF &ContentBounds)
{
	if (FNeedOffset && FKBBounds.Top > 0) {
		ContentBounds.Bottom = Max(ContentBounds.Bottom, 2 * ClientHeight - FKBBounds.Top);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCommBaseForm::FormFocusChanged(TObject *Sender)
{
	UpdateKBBounds();
}
//---------------------------------------------------------------------------

void __fastcall TCommBaseForm::FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKeyboardShow= KeyboardVisible;
	FKBBounds = TRectF(0,0,0,0);
	FNeedOffset = False;
	RestorePosition();
}
//---------------------------------------------------------------------------

void __fastcall TCommBaseForm::FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKeyboardShow= KeyboardVisible;
	FKBBounds = TRectF(Bounds);
	FKBBounds = TRectF(ScreenToClient(FKBBounds.TopLeft()),ScreenToClient(FKBBounds.BottomRight()));
	UpdateKBBounds();
}
//---------------------------------------------------------------------------

void __fastcall TCommBaseForm::UpdateKBBounds()
{
	FNeedOffset = false;
	if (FKeyboardShow&&(Focused != NULL)) {
		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
		TRectF LFocusRect = LFocused->AbsoluteRect;
		LFocusRect.Offset(ItemVertScrollBox->ViewportPosition.X, ItemVertScrollBox->ViewportPosition.Y);
		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
			FNeedOffset =true;// ;
			EditLayout->Align = TAlignLayout::Horizontal;
			ItemVertScrollBox->RealignContent();
			Application->ProcessMessages();
			ItemVertScrollBox->ViewportPosition = PointF(ItemVertScrollBox->ViewportPosition.X,
				LFocusRect.Bottom - FKBBounds.Top);
		}
	}
	if (!FNeedOffset) {
		RestorePosition();
	}
}
//---------------------------------------------------------------------------

void __fastcall TCommBaseForm::RestorePosition()
{
	ItemVertScrollBox->ViewportPosition = PointF(ItemVertScrollBox->ViewportPosition.X, 0);
	EditLayout->Align = TAlignLayout::Client;
	ItemVertScrollBox->RealignContent();
}
//---------------------------------------------------------------------------

