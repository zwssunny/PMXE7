//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.Notification.hpp>
#include <FMX.StdCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXDataSnap.hpp>
#include <IPPeerClient.hpp>
#include "CallbackClient.h"
#include <FMX.Layouts.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.Memo.hpp>
#include "Proxy.h"
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.adomxmldom.hpp>
//---------------------------------------------------------------------------
enum DECLSPEC_DENUM TControlServerState : unsigned char { cssNone, cssReg, cssStart, cssStop,cssUnReg,cssReboot };
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TTabControl *tcControl;
	TTabItem *TabServerMsg;
	TTabItem *TabServer;
	TToolBar *mainFooter;
	TButton *btSetup;
	TButton *btLogin;
	TButton *btExit;
	TLabel *UserLabel;
	TNotificationCenter *NotificationC;
	TSQLConnection *FConnection;
	TMemo *mmMsg;
	TListView *lvServerList;
	TToolBar *ToolBar1;
	TButton *btFill;
	TActionList *ActionList1;
	TAction *acSCReg;
	TAction *acSCUnReg;
	TAction *acSCStart;
	TAction *acSCStop;
	TButton *btReg;
	TButton *btUnReg;
	TButton *btStart;
	TButton *btStop;
	TTimer *Timer1;
	TAction *acReboot;
	TButton *btReboot;
	TXMLDocument *XMLDocument1;
	void __fastcall btSetupClick(TObject *Sender);
	void __fastcall btLoginClick(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btFillClick(TObject *Sender);
	void __fastcall lvServerListItemClick(const TObject *Sender, const TListViewItem *AItem);
	void __fastcall acSCRegExecute(TObject *Sender);
	void __fastcall acSCUnRegExecute(TObject *Sender);
	void __fastcall acSCStartExecute(TObject *Sender);
	void __fastcall acSCStopExecute(TObject *Sender);
	void __fastcall tcControlChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall acRebootExecute(TObject *Sender);


private:	// User declarations
	String settingfile;
	String AppPath;
	String FAgentAddress;
	int FAgentPort;
	String FCommunicationProtocol;
	String FUserCode;
	String FPassword;
	bool FRemember;
	bool FAutoLogin;
	String CurServerName;
	TControlServerState ToControlState;
	TDSClientCallbackChannelManager* LChannelManager;
	TCallbackClient * MsgCallBack;
	TServerControlMethodsClient *scControlClient;
	TJSONArray* SerList;
	void __fastcall ChangeControlState();
	void __fastcall LoadConnectSetting();
	void __fastcall AppOnConnect(TObject * Sender);
	void __fastcall AppOnDisConnect(TObject * Sender);
	void __fastcall MessageCallBackHook(TJSONObject* Arg); // 接收消息
	void __fastcall RegMsgCallBack();
	void __fastcall LogOut(System::Uitypes::TModalResult AResult);
	void __fastcall ControlServer(System::Uitypes::TModalResult AResult);
	void __fastcall FillServerList();
	void __fastcall ChangeListItem(TListViewItem *sItem,TJSONObject *jNode);
	void __fastcall ChangeActionList(int serverstatus);
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
	bool __fastcall InitClientComm();
	void __fastcall SaveSetting();
	__property String UserCode = {read = FUserCode, write = FUserCode};
	__property String Password = {read = FPassword, write = FPassword};
	__property bool Remember = {read = FRemember,write = FRemember};
	__property bool AutoLogin = {read = FAutoLogin,write = FAutoLogin};

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
