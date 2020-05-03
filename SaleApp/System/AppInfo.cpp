//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "AppInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TAppInfoForm *AppInfoForm;
//---------------------------------------------------------------------------
__fastcall TAppInfoForm::TAppInfoForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAppInfoForm::FormCreate(TObject *Sender)
{
	// This defines the default active tab at runtime
	TabControl1->ActiveTab = TabItem1;
}
//---------------------------------------------------------------------------

void __fastcall TAppInfoForm::FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if(Key == vkHardwareBack) {
		if(TabControl1->ActiveTab == TabItem1 && TabControl2->ActiveTab == TabItem6) {
			ChangeTabAction2->Tab = TabItem5;
			ChangeTabAction2->ExecuteTarget(this);
			ChangeTabAction2->Tab = TabItem6;
			Key = 0;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TAppInfoForm::TabControl1Gesture(TObject *Sender, const TGestureEventInfo &EventInfo,
		  bool &Handled)
{
#ifdef __ANDROID__
	switch (EventInfo.GestureID) {
		case sgiLeft :
			if(TabControl1->ActiveTab != TabControl1->Tabs[TabControl1->TabCount-1]) {
				TabControl1->ActiveTab = TabControl1->Tabs[TabControl1->TabIndex+1];
				Handled = true;
			}
			break;
		case sgiRight :
			if(TabControl1->ActiveTab != TabControl1->Tabs[0]) {
				TabControl1->ActiveTab = TabControl1->Tabs[TabControl1->TabIndex-1];
				Handled = true;
			}
			break;
	default:
		;
	}
#endif
}
//---------------------------------------------------------------------------

