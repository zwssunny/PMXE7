//---------------------------------------------------------------------------
#pragma hdrstop

#include "FSTMessageDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall FSTMessageDlg(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const int AHelpContext,TMessageDialogEventProc &AMessageDialogEventProc)
{
	TMessageDialogHandler *msgDialogHandler=new TMessageDialogHandler(AMessageDialogEventProc);
	MessageDlg(AMessage, ADialogType,  AButtons, AHelpContext, msgDialogHandler);
}
void __fastcall ShowMessageBox(const System::UnicodeString AMessage,TMessageDialogEventProc &AMessageDialogEventProc)
{
	 FSTMessageDlg(AMessage,TMsgDlgType::mtConfirmation,mbYesNo,0,AMessageDialogEventProc);
}
