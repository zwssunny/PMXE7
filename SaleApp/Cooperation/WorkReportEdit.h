//---------------------------------------------------------------------------

#ifndef WorkReportEditH
#define WorkReportEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "DetailBaseForm.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <FMX.ActnList.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <System.Actions.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include "WorkReportItemEdit.h"
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.SpinBox.hpp>
//---------------------------------------------------------------------------
class TfrmWorkReportEdit : public TfrmDetailBaseForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *seWorkReportStartDate;
	TLabel *Label3;
	TLabel *Label5;
	TEdit *seEmpName;
	TLabel *Label6;
	TMemo *mmWorkReportSelfOpinion;
	TMemo *mmWorkReportCheckerOpinion;
	TLabel *Label7;
	TEdit *seWorkReportEndDate;
	TLabel *Label4;
	TLabel *Label8;
	TEdit *seWorkReportState;
	TEdit *seWorkReportUpdateDatetime;
	TLabel *Label9;
	TEdit *seCheckerName;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *seWorkReportCheckDatetime;
	TSpinBox *spWorkReportWeek;
	TSpinBox *spWorkReportYear;
	TStringGrid *ItemStringGrid;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TDateEdit *deWorkReportDate;
	void __fastcall spWorkReportWeekChange(TObject *Sender);
	void __fastcall ItemStringGridSelChanged(TObject *Sender);
	void __fastcall deWorkReportDateChange(TObject *Sender);
	void __fastcall edWorkflowTitleEnter(TObject *Sender);
private:	// User declarations
	void __fastcall InitForm();
	void __fastcall FormInitControl();
	void __fastcall FormClearControl(int Section);
	void __fastcall SendDataToDataSet(int Section);
	void __fastcall GetDataFromDataSet(int Section);
	void __fastcall VerifyFieldData(int Section,int status);
	bool __fastcall BeforeUpdateData(int OptType);
	void __fastcall SetUserCtrlStatus();
	void __fastcall BeforWorkFlowStart(TWorkFlowStartData *AWorkFlowStartData);
	void __fastcall BeforWorkFlowExec(TWorkFlowExecData *AWorkFlowExecData,TClientDataSet *varDataSet);
	void __fastcall AfterWorkFlowStart(String WorkInsID);
	void __fastcall AfterWorkFlowExec(String WorkInsID,String TaskInsID);
	void __fastcall FormFillData();
	TForm * __fastcall NewItemEditForm(TZClientDataSet *m_DataSet, int status);
	void __fastcall DetailDataSetAfterPost(TDataSet* DataSet);

    int fFormType;
	String FGuidBillID;
	TfrmWorkReportItemEdit* WorkReportItemEdit;
public:		// User declarations
	__fastcall TfrmWorkReportEdit(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet *m_DataSet,int DataSetStatus,int FormType);
	__fastcall TfrmWorkReportEdit(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param,int Flag,int FormType);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorkReportEdit *frmWorkReportEdit;
//---------------------------------------------------------------------------
#endif
