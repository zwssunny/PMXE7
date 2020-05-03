//---------------------------------------------------------------------------

#ifndef ClientConfgH
#define ClientConfgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TfrmConfgForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel3;
	TButton *bbEdit;
	TButton *bbSave;
	TButton *bbCancel;
	TGroupBox *GroupBox1;
	TEdit *edAgentIP;
	TEdit *edAgentPort;
	TLabel *Label1;
	TLabel *lableport;
	TLabel *lbProtocol;
	TComboBox *cbProtocol;
	void __fastcall bbEditClick(TObject *Sender);
	void __fastcall bbSaveClick(TObject *Sender);
	void __fastcall bbCancelClick(TObject *Sender);
	void __fastcall lableportKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
private:	// User declarations
  void __fastcall ReadOption();
  void __fastcall WriteOption();
  String ClientPath;
public:		// User declarations
	__fastcall TfrmConfgForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfgForm *frmConfgForm;
//---------------------------------------------------------------------------
#endif
