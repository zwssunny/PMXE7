//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
  IsLocate=false;
  FConnected=false;
  ChangeControlState();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ChangeControlState()
{
   TakePhotoFromCameraAction1->Enabled=FConnected&&IsLocate;
   edDeviceSN->Enabled=FConnected;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btFindClick(TObject *Sender)
{
  tmCheckConnection->Enabled=false;
  CommandManager->Enabled=true;
  CommAppProfile->Enabled=true;
  int pCount=CommandManager->PairedManagers->Count;
   for(int i=pCount;i>0;i--)
   {
	 CommandManager->UnPairManager(CommandManager->PairedManagers->Items[i-1]);
   }
   CommandManager->RemoteProfiles->Clear();
  tmCheckConnection->Enabled=true;
  CommandManager->AutoConnect();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CommandManagerRequestManagerPassword(const TObject *Sender,
          const UnicodeString RemoteIdentifier, UnicodeString &Password)

{
  Password = "1314";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::TakePhotoFromCameraAction1DidFinishTaking(TBitmap *Image)

{
	if (Image->Width > 1024) {
		auto ScaleFactor = Image->Width / 1024;
		Image->Resize(static_cast<int>(Image->Width / ScaleFactor),
			static_cast<int>(Image->Height / ScaleFactor));
	}
	ImageContainer->Bitmap->Assign(Image);
	TMemoryStream *imageStream=new TMemoryStream();
	Image->SaveToStream(imageStream);
	CommAppProfile->SendStream(CommandManager->RemoteProfiles->First(),"Image",imageStream);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acReadSNExecute(TObject *Sender)
{
  ShowMessage(L"该功能未完善，待测试");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnScanGetResult(bool AExecute, System::UnicodeString AResultText, System::UnicodeString ABarcodeFormat)
{
   if(AExecute)
   {
	edDeviceSN->Text= AResultText;
	if(FConnected)
	  acLocateRecord->Execute();
   }
   else
     edDeviceSN->Text="";
}
//---------------------------------------------------------------------------
 void __fastcall TfrmMain::CommandAppResources0ResourceReceived(const TObject *Sender,
		  const TRemoteResource *AResource)
{
  AResource->Value.AsStream->Position=0;
  ImageContainer->Bitmap->LoadFromStream(AResource->Value.AsStream);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CommandAppResources1ResourceReceived(const TObject *Sender,
		  const TRemoteResource *AResource)
{
	 IsLocate = const_cast<TRemoteResource *>(AResource)->Value.AsBoolean;
	// if(!IsLocate)  //先清除旧内容
	 {
	  lbDeviceName->Text="";
	  lbDeciceMode->Text="";
	  ImageContainer->Bitmap->Assign(NULL);
	 }
	 ChangeControlState();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CommandAppResources2ResourceReceived(const TObject *Sender,
          const TRemoteResource *AResource)
{
	lbDeviceName->Text=AResource->Value.AsString;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CommandAppResources3ResourceReceived(const TObject *Sender,
          const TRemoteResource *AResource)
{
	lbDeciceMode->Text=AResource->Value.AsString;

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::CommandManagerRemoteManagerShutdown(const TObject *Sender,
          const UnicodeString ManagerIdentifier)
{
  CheckRemoteProfiles();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CheckRemoteProfiles()
{
  String ConnectedProfiles="";
  if(CommandManager->RemoteProfiles->Count>0)
  {
	  for(int i=0;i<CommandManager->RemoteProfiles->Count;i++)
	  {
		ConnectedProfiles = ConnectedProfiles + " - " + CommandManager->RemoteProfiles->Items[i].ProfileText;
	  }
		 FConnected=true;
		 lbConnProfiles->Text=ConnectedProfiles;
  }
  else
  {
	lbConnProfiles->Text=L"未连接";
	FConnected=false;
  }
  ChangeControlState();
}

void __fastcall TfrmMain::acCloseExecute(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::acLocateRecordExecute(TObject *Sender)
{
  if (edDeviceSN->Text>" ")
  {
	 ImageContainer->Bitmap->Assign(NULL);
	 lbDeviceName->Text="";
	 lbDeciceMode->Text="";
	 IsLocate =false;
//     CommAppProfile.SendString(CommandManager->RemoteProfiles->Items[cbBoxProfile->ItemIndex],"DeviceSN",edDeviceSN->Text);
	 CommAppProfile->SendString(CommandManager->RemoteProfiles->First(),"DeviceID",edDeviceSN->Text);
  }
   else
     ShowMessage(L"先扫描设备编码！");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FSTAppProfileResources4ResourceReceived(const TObject *Sender,
          const TRemoteResource *AResource)
{
   edDeviceSN->Text=AResource->Value.AsString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CommandManagerEndAutoConnect(TObject *Sender)
{
	CheckRemoteProfiles();
}
//---------------------------------------------------------------------------




//void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
//{
//	if(MessageDlg(_D("您是否确认要退出系统？") ,TMsgDlgType::mtConfirmation,mbYesNo,0)==mrYes)
//	{
//	  CanClose=true;
//	}
//	else
//	   CanClose=false;
//}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmCheckConnectionTimer(TObject *Sender)
{
	CheckRemoteProfiles();
}
//---------------------------------------------------------------------------

