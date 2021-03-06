//---------------------------------------------------------------------------

#ifndef CustomerH
#define CustomerH
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
#include "CustomerFilters.h"
#include "CustomerEdit.h"
//---------------------------------------------------------------------------
class TfrmCustomer : public TfrmBaseListShow
{
__published:	// IDE-managed Components
	TStringGrid *CustomerStringGrid;
	TBindGridLink *BindStringGridLink;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
private:	// User declarations
		TCustomerFiltersForm *FiltersForm;
		TCustomerEditForm *EditForm;
		void __fastcall GetSalesType();
		bool IsSalesManager;
		void __fastcall SetUserCtrlStatus();
		TForm * __fastcall NewEditForm(TZClientDataSet *FDataSet,int status);
		void __fastcall FormFillData();
		bool __fastcall BeforeUpdateData(int OptType);
		TForm * __fastcall NewFilterForm(TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker); //创建过滤窗口，传递查询事件
public:		// User declarations
	__fastcall TfrmCustomer(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,
							 String WhereStr);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
#endif
