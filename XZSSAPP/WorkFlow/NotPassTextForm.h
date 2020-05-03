//---------------------------------------------------------------------------

#ifndef NotPassTextFormH
#define NotPassTextFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TfrmNotPassTextForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar2;
	TButton *btClose;
	TButton *Button1;
	TToolBar *ToolBar1;
	TLabel *Label1;
	TPanel *Panel1;
	TLabel *Label2;
	TMemo *Memo1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btCloseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmNotPassTextForm(TComponent* Owner);
	String Reason;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNotPassTextForm *frmNotPassTextForm;
//---------------------------------------------------------------------------
#endif
