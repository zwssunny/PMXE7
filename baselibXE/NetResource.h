// ---------------------------------------------------------------------------

#ifndef NetResourceH
#define NetResourceH

// ---------------------------------------------------------------------------
class PACKAGE TZNetResource : public TObject {
private:
	HWND m_Handle;
	HANDLE hThread;
	DWORD dwThreadId;
	bool FTerminated;
	TStringList *FResourceBuffer;
	TNotifyEvent FOnEnumComplete;

	void __fastcall EnumNetRes(NETRESOURCE* nr);
	int __fastcall GetCount();
	String __fastcall GetNetResName(int index);

protected:
	void __fastcall WndProc(TMessage &msg);

public:
	__fastcall TZNetResource();
	__fastcall ~TZNetResource();

	void __fastcall EnumNetResource();
	void __fastcall AsynEnumNetResource();
	void __fastcall Terminate();
	void __fastcall KillThread();

	__property HWND Handle = {read = m_Handle};
	__property HANDLE ThreadHandle = {read = hThread};
	__property DWORD ThreadId = {read = dwThreadId};
	__property int Count = {read = GetCount};
	__property String NetResName[int index] = {read = GetNetResName};
	__property TNotifyEvent OnEnumComplete = {
		read = FOnEnumComplete, write = FOnEnumComplete};

	friend DWORD WINAPI ThreadProc(void *lpParam);
};
#endif
