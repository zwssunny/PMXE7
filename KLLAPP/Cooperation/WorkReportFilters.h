//---------------------------------------------------------------------------

#ifndef WorkReportFiltersH
#define WorkReportFiltersH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseFilters.h"
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "StartAndEndDate.h"
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TfrmWorkReportFilters : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TExpander *BillDateExpander;
	TStartAndEndDateFrame *deFilterDate;
	TExpander *BillFilterExpander;
	TComboBox *cbBoxState;
	TComboBox *cbReporter;
	TLabel *Label1;
	TLabel *Label6;
private:	// User declarations
	String __fastcall BuildFilters();
	void __fastcall FillReporterComBox();

	int fFormType;
	bool fViewAll;
public:		// User declarations
	__fastcall TfrmWorkReportFilters(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker,int FormType,bool ViewAll=false);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorkReportFilters *frmWorkReportFilters;
//---------------------------------------------------------------------------
#endif
