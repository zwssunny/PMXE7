//---------------------------------------------------------------------------

#ifndef SelectStuSupplyNoteH
#define SelectStuSupplyNoteH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseFilters.h"
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "StartAndEndDate.h"
#include <FMX.Edit.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
//---------------------------------------------------------------------------
class TSelectStuSupplyNoteForm : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TExpander *BillDateExpander;
	TStartAndEndDateFrame *StartAndEndDateFrame1;
	TExpander *BillFilerExpander;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edCorpName;
	TEdit *edContName;
	TEdit *edStuSpyNtNum;
	TSearchEditButton *SearchEditButton1;
	TListView *lvSupplyNoteList;
	void __fastcall SearchEditButton1Click(TObject *Sender);
private:	// User declarations
	String __fastcall GetFilters();
	void __fastcall FillSupplyNoteList();
protected:
	virtual String __fastcall BuildFilters();
	virtual void __fastcall InitControl();
public:		// User declarations
	__fastcall TSelectStuSupplyNoteForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectStuSupplyNoteForm *SelectStuSupplyNoteForm;
//---------------------------------------------------------------------------
#endif
