//---------------------------------------------------------------------------

#ifndef CustomerFiltersH
#define CustomerFiltersH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseFilters.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TCustomerFiltersForm : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TLabel *Label5;
	TEdit *edCustName;
	TEdit *edCustNum;
	TEdit *edMobilePhone;
	TEdit *edCardNo;
	TComboBox *cboClientType;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label1;
	TEdit *edCardID;
	TLabel *Label6;
	TLabel *Label7;
	TComboBox *cbBoxClientClass;
private:	// User declarations
protected:
	virtual String __fastcall BuildFilters();
	virtual void __fastcall InitControl();
public:		// User declarations
	__fastcall TCustomerFiltersForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);
};
//---------------------------------------------------------------------------
extern PACKAGE TCustomerFiltersForm *CustomerFiltersForm;
//---------------------------------------------------------------------------
#endif
