//---------------------------------------------------------------------------

#ifndef SelectPeopleH
#define SelectPeopleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseFilters.h"
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
//---------------------------------------------------------------------------
class TSelectPeopleForm : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TExpander *FilterExpander;
	TLabel *Label2;
	TLabel *Label1;
	TComboBox *cboxFilterType;
	TEdit *edFilterValue;
	TSearchEditButton *SearchEditButton1;
	TListView *lvPeopleList;
	void __fastcall SearchEditButton1Click(TObject *Sender);
private:	// User declarations
	void __fastcall FillPeopleList();
protected:
	virtual String __fastcall BuildFilters();
	virtual void __fastcall InitControl();
public:		// User declarations
	__fastcall TSelectPeopleForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectPeopleForm *SelectPeopleForm;
//---------------------------------------------------------------------------
#endif
