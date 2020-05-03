//---------------------------------------------------------------------------

#ifndef LoginH
#define LoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.MobilePreview.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TLoginForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *Header;
	TToolBar *Footer;
	TLabel *HeaderLabel;
	TLabel *Label1;
	TEdit *edUserLoginCode;
	TLabel *Label2;
	TEdit *edPassword;
	TButton *btOk;
	TButton *btCancel;
	TPanel *Panel1;
	TVertScrollBox *MainVertScrollBox;
	TLayout *MainLayout;
	void __fastcall btOkClick(TObject *Sender);
	void __fastcall FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
	void __fastcall FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
private:	// User declarations
  	String __fastcall get_LogonCode();
	String __fastcall get_Password();

	System::Types::TRectF FKBBounds;
	bool FNeedOffset;
	void __fastcall UpdateKBBounds();
	void __fastcall RestorePosition();
public:		// User declarations
	__fastcall TLoginForm(TComponent* Owner);
	__property String LogonCode={read=get_LogonCode};
	__property String Password={read=get_Password};
};
//---------------------------------------------------------------------------
extern PACKAGE TLoginForm *LoginForm;
//---------------------------------------------------------------------------
#endif
