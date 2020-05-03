//---------------------------------------------------------------------------

#ifndef LoanCalculationH
#define LoanCalculationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.Grid.hpp>
#include <System.Rtti.hpp>
#include <FMX.Ani.hpp>
#include <FMX.TabControl.hpp>
#include "ClientBroker.h"
//---------------------------------------------------------------------------
class TfrmLoanCalculation : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TToolBar *ToolBar1;
	TLabel *Label2;
	TToolBar *ToolBar2;
	TButton *btClose;
	TComboBox *cbPayWay;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *cbCalWay;
	TComboBox *cbLoanType;
	TGridPanelLayout *GridPanelLayout1;
	TVertScrollBox *VertScrollBox1;
	TNumberBox *nbBusinessAmt;
	TLabel *Label5;
	TLabel *Label6;
	TNumberBox *nbAccumulation;
	TLabel *Label7;
	TComboBox *cbCycle;
	TLabel *Label8;
	TComboBox *cbRate;
	TLabel *Label9;
	TEdit *edAccu;
	TButton *btCalculation;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TFloatAnimation *FloatAnimation1;
	TEdit *edPrincipal;
	TEdit *edInterest;
	TEdit *edTotalPay;
	TPanel *Panel1;
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TStringGrid *DetailPayGrid;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TLabel *Label13;
	TEdit *edMonthPay;
	TVertScrollBox *MainVertScrollBox;
	TLayout *MainLayout;
	void __fastcall btCalculationClick(TObject *Sender);
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall cbLoanTypeChange(TObject *Sender);
	void __fastcall cbPayWayChange(TObject *Sender);
	void __fastcall FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
	void __fastcall FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds);
private:	// User declarations
	TClientBroker *FClientBroker;
	System::Types::TRectF FKBBounds;
	bool FNeedOffset;
	void __fastcall UpdateKBBounds();
	void __fastcall RestorePosition();
public:		// User declarations
	__fastcall TfrmLoanCalculation(TComponent* Owner,TClientBroker *clBroker);
	void __fastcall SetBusinessAmt(double Amt);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmLoanCalculation *frmLoanCalculation;
//---------------------------------------------------------------------------
#endif
