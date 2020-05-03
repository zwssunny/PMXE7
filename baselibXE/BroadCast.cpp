// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "MessageDef.h"
#include "BroadCast.h"
const int MAX_RECV_BUFF = 4096;
const String M2EEBC_MSG_HEAD = "M2EEBCMESSAGE";
// ---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TBroadCast::TBroadCast() {
	FServerUuid = GetGUIDString();
	FStatus = 0;
	FUDPPort = 17539;
	FRecvSelf = false;
	FMessageBuffer = new TStringList;
	FMessageFrom = new TStringList;
	FHandle = AllocateHWnd(WndProc);
	StartupUDP();
	FStatus = 1;
}

// ---------------------------------------------------------------------------
__fastcall TBroadCast::~TBroadCast() {
	CleanupUDP();
	if (FHandle)
		DeallocateHWnd(FHandle);
	delete FMessageBuffer;
	delete FMessageFrom;
}

// ---------------------------------------------------------------------------
void __fastcall TBroadCast::StartupUDP() {
	WSADATA WSAData;
	bool optval = true;
	sockport = FUDPPort;
	if (WSAStartup(MAKEWORD(2, 0), &WSAData)) {
		FStatus = 1;
		return;
	}
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == INVALID_SOCKET) {
		FStatus = 1;
		return;
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons((unsigned short)sockport);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char FAR *)&optval,
		sizeof(optval));
	if (bind(sockfd, (LPSOCKADDR) & server, sizeof(server)) == SOCKET_ERROR) {
		closesocket(sockfd);
		FStatus = 1;
		return;
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char FAR*)&optval,
		sizeof(optval)) == SOCKET_ERROR) {
		closesocket(sockfd);
		FStatus = 1;
		return;
	}
	if (WSAAsyncSelect(sockfd, FHandle, UM_SOCK, FD_READ | FD_CLOSE)
		== SOCKET_ERROR) {
		closesocket(sockfd);
		FStatus = 1;
		return;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TBroadCast::CleanupUDP() {
	WSACleanup();
}

// ---------------------------------------------------------------------------
void __fastcall TBroadCast::WndProc(TMessage &Msg) {
	int length, namelen;
	SOCKADDR_IN from;
	String fromip;
	char Buffer[MAX_RECV_BUFF];
	if (Msg.Msg == UM_SOCK) {
		switch (WSAGETSELECTEVENT(Msg.LParam)) {
		case FD_READ:
			namelen = sizeof(SOCKADDR);
			if ((length = recvfrom(sockfd, Buffer, MAX_RECV_BUFF, 0,
				(struct sockaddr FAR*)&from, (int FAR*)&namelen))
				== SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					break;
				}
			}
			if (length == 0) {
				break;
			}
			if (length < 50)
				break;
			if (String(Buffer).SubString(1, 14) != M2EEBC_MSG_HEAD)
				break;
			fromip = inet_ntoa(from.sin_addr);
			if (!FRecvSelf) {
				if (FServerUuid == String(Buffer).SubString(15, 36))
					break;
			}
			FMessageBuffer->Add(String(Buffer).SubString(51, length - 36));
			FMessageFrom->Add(fromip);
			if (FOnReceivedMessage)
				FOnReceivedMessage(this);
			break;
		case FD_CLOSE:
			// closesocket(sockfd);
			break;
		default:
			if (WSAGETSELECTERROR(Msg.LParam) != 0) {
				// MessageBox(NULL,"Socket failure!","Warning",MB_OK);
				// closesocket(sockfd);
			}
		}
		WSAAsyncSelect(sockfd, FHandle, UM_SOCK, FD_READ | FD_CLOSE);
	}
	Dispatch(&Msg);
	Msg.Result = DefWindowProc(FHandle, Msg.Msg, Msg.WParam, Msg.LParam);
}

// ---------------------------------------------------------------------------
void __fastcall TBroadCast::BroadCastMessage(String value) {
	struct sockaddr_in to;
	to.sin_family = AF_INET;
	to.sin_addr.s_addr = INADDR_BROADCAST;
	to.sin_port = htons((unsigned short)sockport);
	value = M2EEBC_MSG_HEAD + FServerUuid + value;
	sendto(sockfd, AnsiString(value).c_str(), MAX_RECV_BUFF, 0,
		(struct sockaddr FAR *)&to, sizeof(SOCKADDR));
}

// ---------------------------------------------------------------------------
bool __fastcall TBroadCast::ReadMessage(String &msg, String &fromip) {
	if (FMessageBuffer->Count > 0) {
		msg = FMessageBuffer->Strings[0];
		fromip = FMessageFrom->Strings[0];
		FMessageBuffer->Delete(0);
		FMessageFrom->Delete(0);
		return true;
	}
	else
		return false;
}

// ---------------------------------------------------------------------------
String __fastcall TBroadCast::GetLocalAddress() {
	String ComputerIP;
	char HostName[80];
	LPHOSTENT lpHostEnt;
	struct in_addr addr[10];
	WSAData wsaData;
	for (int i = 0; i < 10; i++)
		memset(&addr[i], 0, sizeof(in_addr));
	if (gethostname(HostName, sizeof(HostName)) == SOCKET_ERROR) {
		return "";
	}
	lpHostEnt = gethostbyname(HostName);
	if (!lpHostEnt) {
		return "";
	}
	for (int i = 0; lpHostEnt->h_addr_list[i] != 0; i++)
		memcpy(&addr[i], lpHostEnt->h_addr_list[i], sizeof(in_addr));
	ComputerIP = inet_ntoa(addr[0]);
	return ComputerIP;
}

// ---------------------------------------------------------------------------
String __fastcall TBroadCast::GetGUIDString(void) {
	UUID *NewUuid = new UUID;
	unsigned short * StringUuid;
	if (UuidCreate(NewUuid) == RPC_S_OK) {
		UuidToString(NewUuid, &StringUuid);
		return (Char*)StringUuid;
	}
	else
		return "";
}
// ---------------------------------------------------------------------------
