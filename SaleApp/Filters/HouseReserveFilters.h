//---------------------------------------------------------------------------

#ifndef HouseReserveFiltersH
#define HouseReserveFiltersH
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
//---------------------------------------------------------------------------
class THouseReserveFiltersForm : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edHsgNum;
	TEdit *edHseRsveNum;
	TEdit *edClientTheName;
	TComboBox *cbHseRsveFKID_Est;
	TLabel *Label5;
	TComboBox *cbHsgFKID_Bdg;
	TLabel *Label6;
	TComboBox *cbBoxHseRsveProperty;
	void __fastcall cbHseRsveFKID_EstClosePopup(TObject *Sender);
private:	// User declarations
	void __fastcall InitBdgNameComboBox();
	void __fastcall InitEstNameComboBox();
protected:
virtual String __fastcall BuildFilters();
virtual void __fastcall InitControl();
public:		// User declarations
	__fastcall THouseReserveFiltersForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);
};
//---------------------------------------------------------------------------
extern PACKAGE THouseReserveFiltersForm *HouseReserveFiltersForm;
//---------------------------------------------------------------------------
#endif
