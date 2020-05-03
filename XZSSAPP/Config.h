//---------------------------------------------------------------------------

#ifndef ConfigH
#define ConfigH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.MobilePreview.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TConfigForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *Header;
	TToolBar *Footer;
	TLabel *HeaderLabel;
	TEdit *edAgentIP;
	TLabel *lableport;
	TEdit *edAgentPort;
	TLabel *lbProtocol;
	TComboBox *cbProtocol;
	TButton *btSave;
	TButton *btCancel;
	TPanel *Panel1;
	TLabel *Label2;
	TLabel *Label1;
	TNumberBox *nbBaseBusiRate;
	TLabel *Label3;
	TNumberBox *nbBaseAccuRate;
	TVertScrollBox *MainVertScrollBox;
	TLayout *MainLayout;
	void __fastcall btSaveClick(TObject *Sender);
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
	void __fastcall FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
private:	// User declarations
  	void __fastcall ReadOption();
	void __fastcall WriteOption();
	String settingfile;
	String AppPath;

	System::Types::TRectF FKBBounds;
	bool FNeedOffset;
	void __fastcall UpdateKBBounds();
	void __fastcall RestorePosition();
public:		// User declarations
	__fastcall TConfigForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
