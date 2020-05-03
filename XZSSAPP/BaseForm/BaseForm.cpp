//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "BaseForm.h"
#include "CommFunc.h"
#include <FMX.PhoneDialer.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.iPhone4in.fmx", _PLAT_IOS)

TfrmBaseForm *frmBaseForm;
//---------------------------------------------------------------------------
__fastcall TfrmBaseForm::TfrmBaseForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param)
	: TForm(Owner)
{
	FClientBroker = clBroker;
	FModuleCode = modulecode;
}
//---------------------------------------------------------------------------
__fastcall TfrmBaseForm::TfrmBaseForm(TComponent* Owner,TClientBroker *clBroker)
	: TForm(Owner)
{
	FClientBroker = clBroker;
}
//---------------------------------------------------------------------------
TClientDataSet* __fastcall TfrmBaseForm::Execute(String Resource, TRESTRequestMethod Method, TRESTRequestParameterList *Params)
{
	return FClientBroker->Execute(Resource,Method,Params);
}
//---------------------------------------------------------------------------
TClientDataSet* __fastcall TfrmBaseForm::csGetData(String Resource, TRESTRequestParameterList *Params)
{
	return FClientBroker->Execute(Resource,rmGET,Params);
}
//---------------------------------------------------------------------------
TClientDataSet* __fastcall TfrmBaseForm::PostData(String Resource, TRESTRequestParameterList *Params)
{
	return FClientBroker->Execute(Resource,rmPOST,Params);
}
//---------------------------------------------------------------------------
TClientDataSet* __fastcall TfrmBaseForm::GetElementData(String ElementName)
{
	return FClientBroker->SetRootElement(ElementName);
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaseForm::PhoneDialer(String APhoneNum)
{
   if (APhoneNum!= "")
   {
	_di_IFMXPhoneDialerService PhoneDialerService;
	/*  test whether the PhoneDialer services are supported */
	if(TPlatformServices::Current->SupportsPlatformService(__uuidof(IFMXPhoneDialerService)) &&
		(PhoneDialerService = TPlatformServices::Current->GetPlatformService(__uuidof(IFMXPhoneDialerService)))) {
		PhoneDialerService->Call(APhoneNum);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaseForm::btCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaseForm::FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKBBounds = TRectF(0,0,0,0);
	FNeedOffset = False;
	RestorePosition();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseForm::FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
 	FKBBounds = TRectF(Bounds);
   	FKBBounds = TRectF(ScreenToClient(FKBBounds.TopLeft()),ScreenToClient(FKBBounds.BottomRight()));
//	MainPanel->Align = TAlignLayout::Horizontal;
// 	MainPanel->Height  = Screen->Height  - FKBBounds.Height();

//	if (Focused != NULL) {
//		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
//		TRectF LFocusRect = LFocused->AbsoluteRect;
//		LFocusRect.Offset(MainVertScrollBox->ViewportPosition.X, MainVertScrollBox->ViewportPosition.Y);
//		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
//			MainVertScrollBox->RealignContent();
//			Application->ProcessMessages();
//			MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X,
//				LFocusRect.Bottom - FKBBounds.Top);
//		}
//	}
//	MainVertScrollBox->RealignContent();
	UpdateKBBounds();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaseForm::UpdateKBBounds()
{
	FNeedOffset = false;
	if (Focused != NULL) {
		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
		TRectF LFocusRect = LFocused->AbsoluteRect;
	   //	LFocusRect = TRectF(ClientToScreen(LFocusRect.TopLeft()),ClientToScreen(LFocusRect.BottomRight()));
		LFocusRect.Offset(MainVertScrollBox->ViewportPosition.X, MainVertScrollBox->ViewportPosition.Y);
		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
			FNeedOffset = true;
			MainPanel->Align = TAlignLayout::Horizontal;
			MainVertScrollBox->RealignContent();
			Application->ProcessMessages();
			MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X,
				LFocusRect.Bottom - FKBBounds.Top);
		}
	}
//	if (!FNeedOffset) {
//		RestorePosition();
//	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmBaseForm::RestorePosition()
{
	MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X, 0);
	MainPanel->Align = TAlignLayout::Client;
	MainVertScrollBox->RealignContent();
}
//---------------------------------------------------------------------------


