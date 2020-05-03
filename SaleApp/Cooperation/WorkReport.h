//---------------------------------------------------------------------------

#ifndef WorkReportH
#define WorkReportH
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
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <System.Rtti.hpp>
#include <Data.Bind.Grid.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <System.Bindings.Outputs.hpp>
#include "WorkReportEdit.h"
#include "WorkReportFilters.h"
//---------------------------------------------------------------------------
class TfrmWorkReport : public TfrmBaseListShow
{
__published:	// IDE-managed Components
	TStringGrid *WorkReportGrid;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	void __fastcall WorkReportGridSelChanged(TObject *Sender);
private:	// User declarations
	void __fastcall FormFillData();
	void __fastcall SetUserCtrlStatus();
	TForm * __fastcall NewEditForm(TZClientDataSet *m_DataSet,int status);
	void __fastcall MasterDataSetAfterPost(TDataSet* DataSet);
	bool __fastcall BeforeUpdateData(int OptType);
	TForm * __fastcall NewFilterForm(TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker);

    int fFormType;
	TfrmWorkReportEdit *WorkReportEdit;
	TfrmWorkReportFilters *FiltersForm;
public:		// User declarations
	__fastcall TfrmWorkReport(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param,int FormType);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorkReport *frmWorkReport;
//---------------------------------------------------------------------------
#endif
