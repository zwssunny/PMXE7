//---------------------------------------------------------------------------

#ifndef MoveTaskDlgH
#define MoveTaskDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMoveTaskDlg : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMoveTaskDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMoveTaskDlg *frmMoveTaskDlg;
//---------------------------------------------------------------------------
#endif
