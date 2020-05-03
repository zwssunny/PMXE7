//---------------------------------------------------------------------------

#ifndef HouseReserveH
#define HouseReserveH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseListShow.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <FMX.ActnList.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Actions.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include "HouseReserveFilters.h"
#include "HouseReserveEdit.h"
//---------------------------------------------------------------------------
class TfrmHouseReserve : public TfrmBaseListShow
{
__published:	// IDE-managed Components
	TStringGrid *ReserveStringGrid;
	TBindGridLink *BindStringGridLink;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
	TStringColumn *StringColumn8;
	TStringColumn *StringColumn9;
	TStringColumn *StringColumn10;
	TStringColumn *StringColumn11;
private:	// User declarations
		THouseReserveFiltersForm *FiltersForm;
		THouseReserveEditForm *EditForm;
		TForm * __fastcall NewEditForm(TZClientDataSet *FDataSet,int status);
		void __fastcall FormFillData();
		void __fastcall SetUserCtrlStatus();
		bool __fastcall BeforeUpdateData(int OptType);
		TForm * __fastcall NewFilterForm(TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);
		void __fastcall GetSalesType();
		bool IsSalesManager;
public:		// User declarations
	__fastcall TfrmHouseReserve(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,
							 String WhereStr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmHouseReserve *frmHouseReserve;
//---------------------------------------------------------------------------
#endif
