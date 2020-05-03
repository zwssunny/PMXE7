//---------------------------------------------------------------------------

#ifndef LoginH
#define LoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmLogin : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edUserLoginCode;
	TEdit *edPassword;
	TButton *btOk;
	TButton *btCancel;
	void __fastcall btOkClick(TObject *Sender);
private:	// User declarations
  String __fastcall get_LogonCode();
  String __fastcall get_Password();
public:		// User declarations
	__fastcall TfrmLogin(TComponent* Owner);
	__property String LogonCode={read=get_LogonCode};
	__property String Password={read=get_Password};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmLogin *frmLogin;
//---------------------------------------------------------------------------
#endif
