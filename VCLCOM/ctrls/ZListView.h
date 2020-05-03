//---------------------------------------------------------------------------

#ifndef ZListViewH
#define ZListViewH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TOnCheckBoxChangeEvent)(System::TObject* Sender,TListItem* Item);
class PACKAGE TZListView : public TListView
{
private:
	TWndMethod OriginalListViewWindowProc;
	TOnCheckBoxChangeEvent FOnCheckBoxChange;
protected:
	void __fastcall ListViewWndProc(Messages::TMessage& Message);
public:
  __fastcall TZListView(TComponent* Owner);
__published:
	 __property TOnCheckBoxChangeEvent    OnCheckBoxChange = {read=FOnCheckBoxChange, write=FOnCheckBoxChange};//CheckBoxChange
};
//---------------------------------------------------------------------------
#endif
