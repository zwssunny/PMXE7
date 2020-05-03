//---------------------------------------------------------------------------

#ifndef DSEventProcH
#define DSEventProcH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <DB.hpp>
#include <DBXCommon.hpp>
#include <DbxDataSnap.hpp>
#include <DSService.hpp>
#include <DSServer.hpp>
#include <DSHTTPLayer.hpp>
#include <Datasnap.DSSession.hpp>
//---------------------------------------------------------------------------
  typedef void __fastcall (*TDSSessionEventProc)(TObject *Sender, const TDSSessionEventType EventType, TDSSession* const Session);
  // Interface for DSSessionEvent
  class TDSEventProc : public TCppInterfacedObject<TDSSessionEvent>
  {
  private:
	TDSSessionEventProc FUIProc ;
  public:
	TDSEventProc(TDSSessionEventProc& AUIProc) : FUIProc(AUIProc) {}
	 __fastcall ~TDSEventProc() {};
	 void __fastcall Invoke(System::TObject* Sender, const TDSSessionEventType EventType,TDSSession* const Session)
	 {
	   FUIProc(Sender , EventType, Session);
	 }
  };
#endif
