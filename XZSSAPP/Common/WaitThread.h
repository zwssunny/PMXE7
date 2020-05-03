//---------------------------------------------------------------------------

#ifndef WaitThreadH
#define WaitThreadH
#include <System.SyncObjs.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TWaitThread : public  TThread
{
private:
	TFmxObject *FParent;
	TAniIndicator *FAniIndicator;
public:
	__fastcall virtual TWaitThread(TFmxObject *Parent);
	__fastcall virtual ~TWaitThread();
	void __fastcall Execute();
	void __fastcall Show();
	void __fastcall Hide();
};
#endif
