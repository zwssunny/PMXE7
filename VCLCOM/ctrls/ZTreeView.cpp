//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ZTreeView.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZTreeView *)
{
  new TZTreeView(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZTreeView::TZTreeView(TComponent* Owner)
  : TTreeView(Owner)
{
   TCustomTreeView::OnDeletion=MyDataDeletion;
}
//---------------------------------------------------------------------------
namespace Ztreeview
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TZTreeView)};
     RegisterComponents("ZWin32", classes, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TZTreeView::MyDataDeletion(System::TObject* Sender, TTreeNode* Node)
{
   // if (Node->Data)
    //   delete  Node->Data;
}

