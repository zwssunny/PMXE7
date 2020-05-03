//---------------------------------------------------------------------------

#ifndef ZTreeViewH
#define ZTreeViewH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TZTreeView : public TTreeView
{
private:
protected:
    void __fastcall MyDataDeletion(System::TObject* Sender, TTreeNode* Node);
public:
  __fastcall TZTreeView(TComponent* Owner);
__published:

};
//---------------------------------------------------------------------------
#endif
