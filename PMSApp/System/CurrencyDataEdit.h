//---------------------------------------------------------------------------

#ifndef CurrencyDataEditH
#define CurrencyDataEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "DetailBaseForm.h"
#include <FMX.ActnList.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <System.Actions.hpp>
#include <FMX.Edit.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Objects.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TfrmCurrencyDataEdit : public TfrmDetailBaseForm
{
__published:	// IDE-managed Components
	TEdit *seCurDataPKID;
	TEdit *seCurDataName;
	TEdit *seCurDataExchangeRate;
	TCheckBox *chkCurDataIsStandard;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TGridPanelLayout *GridPanelLayout1;
	void __fastcall chkCurDataIsStandardChange(TObject *Sender);
private:	// User declarations
  void __fastcall FormInitControl();
  void __fastcall FormClearControl(int Section);
  void __fastcall SendDataToDataSet(int Section);
  void __fastcall GetDataFromDataSet(int Section);
  void __fastcall VerifyFieldData(int Section,int status);
  bool __fastcall BeforeUpdateData(int OptType);
public:		// User declarations
	__fastcall TfrmCurrencyDataEdit(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet
								*FDataSet,int DataSetStatus);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCurrencyDataEdit *frmCurrencyDataEdit;
//---------------------------------------------------------------------------
#endif
