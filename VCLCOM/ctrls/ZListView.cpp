//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZListView.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZListView *)
{
  new TZListView(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZListView::TZListView(TComponent* Owner)
  : TListView(Owner)
{
   OriginalListViewWindowProc=WindowProc;
   WindowProc= ListViewWndProc;
}
//---------------------------------------------------------------------------
namespace Zlistview
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZListView)};
	 RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------
void __fastcall TZListView::ListViewWndProc(Messages::TMessage& Message)
{
  if (Message.Msg == CN_NOTIFY)
  {
    TNMHdr *pnmhdr=(TNMHdr*)Message.LParam;
	if (pnmhdr->code == LVN_ITEMCHANGED)
	 {
	   TNMListView *pnmlistview=(TNMListView*)Message.LParam;
	  if(pnmlistview)
	  {
		if ((pnmlistview->uChanged & LVIF_STATE) != 0)
		{
		  if (((pnmlistview->uOldState & LVIS_STATEIMAGEMASK) >> 12) != ((pnmlistview->uNewState & LVIS_STATEIMAGEMASK) >> 12) )
		  {
			 if(FOnCheckBoxChange)
				FOnCheckBoxChange(this,Items->Item[pnmlistview->iItem]);
		  }
	   }
	  }
	}
  }
  OriginalListViewWindowProc(Message);
}
