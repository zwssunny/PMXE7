//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "WaitThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TWaitThread::TWaitThread(TFmxObject *Parent)
{
  FParent= Parent;
  FAniIndicator = new TAniIndicator(Parent);
  FAniIndicator->Align = TAlignLayout::Client;
  FAniIndicator->Parent = Parent;
}
//---------------------------------------------------------------------------
__fastcall TWaitThread::~TWaitThread()
{
	if(FAniIndicator)
	{
		delete FAniIndicator;
		FAniIndicator = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TWaitThread::Execute()
{
	FreeOnTerminate=false;
	Show();
}
//---------------------------------------------------------------------------
void __fastcall TWaitThread::Show()
{
	FAniIndicator->Visible = true;
	FAniIndicator->Enabled = true;
	FAniIndicator->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TWaitThread::Hide()
{
	FAniIndicator->Visible = false;
	FAniIndicator->Enabled = false;
	FAniIndicator->SendToBack();
	this->Terminate();
}
//---------------------------------------------------------------------------
