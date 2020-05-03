// ---------------------------------------------------------------------------

#ifndef WaitBoxH
#define WaitBoxH

// ---------------------------------------------------------------------------
class PACKAGE TWaitBox {
private:
	TForm *FWaitBoxForm;
	TLabel *FFrontLabel;
	TLabel *FBackLabel;

	void __fastcall FormDeactivate(TObject *Sender);

public:
	__fastcall TWaitBox(String WaitStr);
	__fastcall ~TWaitBox();
};
#endif
