// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "WaitBox.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TWaitBox::TWaitBox(String WaitStr) {
	Screen->Cursor = crHourGlass;
	FWaitBoxForm = new TForm(Application);
	FWaitBoxForm->OnDeactivate = FormDeactivate;
	FWaitBoxForm->Width = 200;
	FWaitBoxForm->Height = 100;
	FWaitBoxForm->BorderIcons >> biSystemMenu;
	FWaitBoxForm->Position = poScreenCenter;
	FWaitBoxForm->BorderStyle = bsToolWindow;
	FBackLabel = new TLabel(FWaitBoxForm);
	FBackLabel->Parent = FWaitBoxForm;
	FBackLabel->Transparent = true;
	FBackLabel->Top = 24;
	FBackLabel->Left = 21;
	FBackLabel->Font->Name = "宋体";
	FBackLabel->Font->Size = 12;
	FBackLabel->Font->Color = clWhite;
	if (WaitStr.IsEmpty())
		FBackLabel->Caption = "正在启动,请稍候...";
	else
		FBackLabel->Caption = WaitStr;
	FFrontLabel = new TLabel(FWaitBoxForm);
	FFrontLabel->Parent = FWaitBoxForm;
	FFrontLabel->Transparent = true;
	FFrontLabel->Top = 24;
	FFrontLabel->Left = 20;
	FFrontLabel->Font->Name = "宋体";
	FFrontLabel->Font->Size = 12;
	FFrontLabel->Font->Color = clBlack;
	if (WaitStr.IsEmpty())
		FFrontLabel->Caption = "正在启动,请稍候...";
	else
		FFrontLabel->Caption = WaitStr;
	FWaitBoxForm->Show();
	FWaitBoxForm->Refresh();
}

// ---------------------------------------------------------------------------
__fastcall TWaitBox::~TWaitBox() {
	Screen->Cursor = crDefault;
	delete FFrontLabel;
	delete FBackLabel;
	delete FWaitBoxForm;
}

// ---------------------------------------------------------------------------
void __fastcall TWaitBox::FormDeactivate(TObject *Sender) {
	FWaitBoxForm->BringToFront();
}
// ---------------------------------------------------------------------------
