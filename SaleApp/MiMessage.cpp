//---------------------------------------------------------------------------

#include <fmx.h>
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
#include <iOSapi.UIKit.hpp>
#endif
#pragma hdrstop

#if defined(__ANDROID__)
#include <FMX.Platform.Android.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Helpers.hpp>
#include <Androidapi.JNIBridge.hpp>
_di_JVibrator Vibrator=NULL;
#endif
#include "MiMessage.h"
#include <System.Ioutils.hpp>
#define Audio_Cmd "cmd.mp3"
#define Audio_Tweet "tweet.mp3"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmMessageForm *frmMessageForm;
String __fastcall GetAudioFileName(const String AFileName)
{
 String AppPath;
#if  defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	 AppPath= IncludeTrailingPathDelimiter(System::Ioutils::TPath::GetDocumentsPath());
	// AppPath= System::Ioutils::TPath::GetMusicPath();
#else
	AppPath = ExtractFilePath(ParamStr(0));
#endif
 return System::Ioutils::TPath::Combine(AppPath,AFileName);
}
void __fastcall TfrmMessageForm::PlaySound(String AFileName)
{
	MediaPlayer->Stop();
	MediaPlayer->FileName = GetAudioFileName(AFileName);
   //	MediaPlayer->Volume = 1;
	MediaPlayer->Play();
}
//---------------------------------------------------------------------------
__fastcall TfrmMessageForm::TfrmMessageForm(TComponent* Owner,TClientBroker *AClientBroker,TTextControl *ANode)
	: TForm(Owner)
{
	LastMsgSendTime=Now().FormatString("YYYY-mm-DD HH:mm:ss");//获得记录最迟时间
	FClientBroker=AClientBroker;
	FNode=ANode;
	FNode->TagObject=this;
	FChatRoomServerMethodsClient=new TChatRoomServerMethods(FClientBroker->DBXConnection,false);
	UserLabel->Text=FNode->Text;
	MsgTimer->Enabled=true;
	msgQuery=new TZClientQuery(this, FClientBroker);
	VertScrollBox1->OnCalcContentBounds = CalcContentBoundsProc;
}
__fastcall TfrmMessageForm::~TfrmMessageForm()
{
   MsgTimer->Enabled=false;
   delete  FChatRoomServerMethodsClient;
   FNode->TagObject=NULL;
   delete msgQuery;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessageForm::SendCommang(String cmdText)
{
	switch(TQQUserType(FNode->TagFloat))
  {
	  case qutDepartment:
		FChatRoomServerMethodsClient->SendCMDToDepartment(cmdText,FNode->TagString);
	  break;
	  case qutUser:
		FChatRoomServerMethodsClient->SendCMDToUser(cmdText,FNode->TagString);
	   break;
	  case qutGroup:
		 FChatRoomServerMethodsClient->SendCMDToGroup(cmdText,FNode->TagString);
	   break;
	  default:
		FChatRoomServerMethodsClient->SendCMDToAll(cmdText);
  }
}
void __fastcall TfrmMessageForm::SetLastRecMessage(TJSONObject* Value)
{
   //收到消息，做一些保存本地消息文件功能
   FLastRecMessage=Value;
   String notificationType=FLastRecMessage->Get("notificationType")->JsonValue->Value();
   if(notificationType=="message")
   {
	String sUser=FLastRecMessage->Get("fromusrname")->JsonValue->Value();
	String DateTime=FLastRecMessage->Get("datetime")->JsonValue->Value();
	if(LastMsgSendTime>DateTime)  //记录收到记录的时间
	  LastMsgSendTime=DateTime;
	String MsgText=sUser+" "+DateTime;
	memMsg->Lines->Add(MsgText);
	MsgText=FLastRecMessage->Get("message")->JsonValue->Value();
	memMsg->Lines->Add(MsgText);
//	PlaySound(L"tweet.wav",NULL,SND_ASYNC|SND_FILENAME);
   }
   else if(notificationType=="cmd")
   {
	 String cmdStr=FLastRecMessage->Get("cmd")->JsonValue->Value();
	 String DateTime=FLastRecMessage->Get("datetime")->JsonValue->Value();
	 String MsgText=FLastRecMessage->Get("fromusrname")->JsonValue->Value()+DateTime+L"发送:";
	 if(cmdStr=="ring")
	 {
	  //响铃
	  MsgText=MsgText+L"响铃";
	  memMsg->Lines->Add(MsgText);
	  String tweetAudio=GetAudioFileName(Audio_Tweet);
	  PlaySound(tweetAudio);
	 }
	 else if(cmdStr=="vibrate")
	 {
		 //震动
		MsgText=MsgText+L"震动";
		memMsg->Lines->Add(MsgText);
		Viration();
	   //	PlaySound(L"cmd.wav",NULL,SND_ASYNC|SND_FILENAME);

	 }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessageForm::MsgTimerTimer(TObject *Sender)
{
 if(TQQUserType(FNode->TagFloat)==qutUser)
	{
	 TTreeViewItem * ANode=(TTreeViewItem*)FNode;
	 if(ANode)
	 {
		bool Online=ANode->IsChecked;
		sbRing->Enabled=Online;
		sbViration->Enabled=Online;
		if(Online)
		  {
			UserLabel->FontColor=TAlphaColor(claBlue);
			UserLabel->Text=FNode->Text+L"(在线)";
				   //	ANode->FontColor= TAlphaColor(claBlue);
		  }
		else
		{
    		UserLabel->FontColor=TAlphaColor(claBlack);
		   //	ANode->FontColor= TAlphaColor(claBlack);
			UserLabel->Text=FNode->Text+L"(离线)";
		}
	 }
	}
	else
	{
	  UserLabel->Text=FNode->Text;
	  sbRing->Enabled=true;
	  sbViration->Enabled=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessageForm::Viration()
{
#if defined(__ANDROID__)
if(Vibrator==NULL)
{
	_di_JObject VibratorObj = Fmx::Platform::Android::MainActivity()->getSystemService(TJContext::JavaClass->VIBRATOR_SERVICE);
	 Vibrator = TJVibrator::Wrap(((_di_ILocalObject)VibratorObj)->GetObjectID());
 }
if(Vibrator&&Vibrator->hasVibrator())
   Vibrator->vibrate(1000);
#endif
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
//
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessageForm::btSendClick(TObject *Sender)
{
  String msgText=memMsgEdit->Text.Trim();
  if(msgText==EmptyStr)
	return;
  bool resute=false;
  switch(TQQUserType(FNode->TagFloat))
  {
	  case qutDepartment:
		resute=FChatRoomServerMethodsClient->SendMessageToDepartment(msgText,FNode->TagString);
	  break;
	  case qutUser:
		resute=FChatRoomServerMethodsClient->SendMessageToUser(msgText,FNode->TagString);
	   break;
	  case qutGroup:
		 resute=FChatRoomServerMethodsClient->SendMessageToGroup(msgText,FNode->TagString);
	   break;
	  default:
		resute=FChatRoomServerMethodsClient->SendMessageToAll(msgText);
  }
//  if(resute)  //可以发离线消息
  {
//		if(TQQUserType(FNode->TagFloat)!=qutCompany)
//		{
//			String MsgText=FClientBroker->UserName+Now().FormatString("YYYY-mm-DD HH:mm:ss")+" ";
//			memMsg->Lines->Add(MsgText);
//			memMsg->Lines->AddStrings(memMsgEdit->Lines);
//		}
		memMsgEdit->Text="";
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::FormClose(TObject *Sender, TCloseAction &Action)

{
   Action=TCloseAction::caHide;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::sbRingClick(TObject *Sender)
{
    SendCommang("ring");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::sbVirationClick(TObject *Sender)
{
   SendCommang("vibrate");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::btCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMessageForm::btLateMsgClick(TObject *Sender)
{
  int msgtype=TQQUserType(FNode->TagFloat);
  msgQuery->Close();
  //每次只取出10条
  msgQuery->SQL->Text="select top 10 tbMissMember.RecMsgID,tbMissMember.RecMsgUserID, tbMessageRecords.*,EmpName as username "
					 "from tbMissMember left join tbMessageRecords on RecMsgID=MsgID "
					 "left join tbEmployeeData on MsgUserID=EmpPKID "
					 "where MsgRecType="+IntToStr(msgtype)+" and ((MsgReceiver="+QuotedStr(FNode->TagString)+
					 " and RecMsgUserID="+QuotedStr(FClientBroker->UserEmpID)+
					 ") OR (MsgReceiver="+QuotedStr(FClientBroker->UserEmpID)+
					 " and RecMsgUserID="+QuotedStr(FNode->TagString)+
					 " ))and MsgSendTime<"+QuotedStr(LastMsgSendTime)+
					 " order by MsgSendTime desc";
  msgQuery->Open();
  msgQuery->First();
  while(!msgQuery->Eof)
  {
	String msgSender=msgQuery->FieldByName("username")->AsString;
	String msgSendTime=msgQuery->FieldByName("MsgSendTime")->AsString;
	String msgCotent=msgQuery->FieldByName("MsagContent")->AsString;
	if(LastMsgSendTime>msgSendTime)
	  LastMsgSendTime=msgSendTime;
	memMsg->Lines->Insert(0,msgCotent);
	memMsg->Lines->Insert(0,msgSender+" "+msgSendTime);
	msgQuery->Next();
  }
  msgQuery->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessageForm::CalcContentBoundsProc(TObject * Sender, System::Types::TRectF &ContentBounds)
{
	if (FNeedOffset && FKBBounds.Top > 0) {
		ContentBounds.Bottom = Max(ContentBounds.Bottom, 2 * ClientHeight - FKBBounds.Top);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::FormFocusChanged(TObject *Sender)
{
	FKBBounds = TRectF(0,0,0,0);
	UpdateKBBounds();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKBBounds = TRectF(0,0,0,0);
	FNeedOffset = False;
	RestorePosition();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKBBounds = TRectF(Bounds);
	FKBBounds = TRectF(ScreenToClient(FKBBounds.TopLeft()),ScreenToClient(FKBBounds.BottomRight()));
	UpdateKBBounds();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::UpdateKBBounds()
{
	FNeedOffset = false;
	if (Focused != NULL) {
		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
		TRectF LFocusRect = LFocused->AbsoluteRect;
		LFocusRect.Offset(VertScrollBox1->ViewportPosition.X, VertScrollBox1->ViewportPosition.Y);
		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
			FNeedOffset = true;
			MainLayout1->Align = TAlignLayout::Horizontal;
			VertScrollBox1->RealignContent();
			Application->ProcessMessages();
			VertScrollBox1->ViewportPosition = PointF(VertScrollBox1->ViewportPosition.X,
				LFocusRect.Bottom - FKBBounds.Top);
		}
	}
	if (!FNeedOffset) {
		RestorePosition();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMessageForm::RestorePosition()
{
	VertScrollBox1->ViewportPosition = PointF(VertScrollBox1->ViewportPosition.X, 0);
	MainLayout1->Align = TAlignLayout::Client;
	VertScrollBox1->RealignContent();
}
//---------------------------------------------------------------------------

