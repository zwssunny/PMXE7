//---------------------------------------------------------------------------

#ifndef StuffStockInFiltersH
#define StuffStockInFiltersH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseFilters.h"
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
#include "ZClientQuery.h"
#include <FMX.Memo.hpp>
#include "StartAndEndDate.h"
#include <FMX.Edit.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TStuffStockInFiltersForm : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TComboBox *cbStore;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label2;
	TEdit *edStuSkInSupplier;
	TEdit *edStuSkInFKID_Cont;
	TLabel *Label6;
	TComboBox *cbBoxState;
	TLabel *Label5;
	TEdit *edStuSkInNum;
	TExpander *BillDateExpander;
	TExpander *BillFilterExpander;
	TStartAndEndDateFrame *deStuSkInDate;
private:	// User declarations
	int FFlag;
	TZClientQuery * StoreQuery;
	void __fastcall FillStoreComBox();
protected:
	 String __fastcall BuildFilters();
	 void __fastcall InitControl();
public:		// User declarations
	__fastcall TStuffStockInFiltersForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker,int Flag);
};
//---------------------------------------------------------------------------
extern PACKAGE TStuffStockInFiltersForm *StuffStockInFiltersForm;
//---------------------------------------------------------------------------
#endif
