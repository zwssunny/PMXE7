//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <Data.SqlExpr.hpp>
#include "wfClientBroker.h"
//---------------------------------------------------------------------------
class TXZWorkFlowSerXE : public TService
{
__published:    // IDE-managed Components
	TTimer *Timer1;

	void __fastcall ServiceStart(TService *Sender, bool &Started);
	void __fastcall ServiceStop(TService *Sender, bool &Stopped);
	void __fastcall ServiceDestroy(TObject *Sender);
	void __fastcall ServiceAfterInstall(TService *Sender);
	void __fastcall ServiceBeforeInstall(TService *Sender);
	void __fastcall ServiceBeforeUninstall(TService *Sender);
	void __fastcall ServiceCreate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	   // User declarations
	String FInstanceName;
	TwfClientBroker * FClientBroker ;
	void __fastcall ReadOption();
	void __fastcall ChangeServiceConfiguration();
	void __fastcall SetInstanceName(String Value);
	String __fastcall GetInstanceName();
public:         // User declarations
	__fastcall TXZWorkFlowSerXE(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);
	__property String InstanceName={read=FInstanceName,write=SetInstanceName};
	friend void __stdcall ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TXZWorkFlowSerXE *XZWorkFlowSerXE;
const String INSTANCE_SWITCH = "-instance=";
//---------------------------------------------------------------------------
#endif
