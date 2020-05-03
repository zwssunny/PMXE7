//---------------------------------------------------------------------------

#ifndef HouseFiltersH
#define HouseFiltersH
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
class THouseFiltersForm : public TBaseFiltersForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TComboBox *cbHsgFKID_Est;
	TComboBox *cbHsgFKID_Bdg;
	TComboBox *cbHsgHouseType;
	TComboBox *cbHsgOrientation;
	TComboBox *cbHsgLandscape;
	TComboBox *cbHsgSellArea;
	TEdit *edHsgNum;
	TLabel *Label8;
	TComboBox *cbHsgDecoration;
	TLabel *Label9;
	TComboBox *cbBoxHsgState;
	void __fastcall cbHsgFKID_EstClosePopup(TObject *Sender);
private:	// User declarations
	void __fastcall InitEstNameComboBox();
	void __fastcall InitBdgNameComboBox();
	void __fastcall InitHouseTypeComboBox();
	void __fastcall InitOrientationComboBox();
	void __fastcall InitDecorationComboBox();
	void __fastcall InitLandscapeComboBox();
	String __fastcall GetSellAreaFilter();
protected:
	virtual String __fastcall BuildFilters();
	virtual void __fastcall InitControl();
public:		// User declarations
	__fastcall THouseFiltersForm(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);
};
//---------------------------------------------------------------------------
extern PACKAGE THouseFiltersForm *HouseFiltersForm;
//---------------------------------------------------------------------------
#endif
