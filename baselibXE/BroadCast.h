// ---------------------------------------------------------------------------

#ifndef BroadCastH
#define BroadCastH
#include <winsock.h>

// ---------------------------------------------------------------------------
class PACKAGE TBroadCast : public TObject {
private:
	HWND FHandle;
	int FStatus; // 0-未初始化状态,1-正常状态
	int FUDPPort;
	bool FRecvSelf;
	String FServerUuid;
	TStringList *FMessageBuffer;
	TStringList *FMessageFrom;
	TNotifyEvent FOnReceivedMessage;

	void __fastcall WndProc(TMessage &Msg);
	void __fastcall StartupUDP();
	void __fastcall CleanupUDP();

	struct sockaddr_in server;
	int sockfd, len, sockport;

	String __fastcall GetLocalAddress();
	String __fastcall GetGUIDString(void);

public:
	__fastcall TBroadCast();
	__fastcall ~TBroadCast();

	__property HWND Handle = {read = FHandle};
	__property int Status = {read = FStatus};
	void __fastcall BroadCastMessage(String value);
	bool __fastcall ReadMessage(String &msg, String &fromip);

	__property bool ReceiveSelf = {read = FRecvSelf, write = FRecvSelf};
	__property String LocalAddress = {read = GetLocalAddress};
	__property int Port = {read = FUDPPort, write = FUDPPort};
	__property TNotifyEvent OnReceivedMessage = {
		read = FOnReceivedMessage, write = FOnReceivedMessage};

};
#endif
