//---------------------------------------------------------------------------

#ifndef TestH
#define TestH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>
#include "ClientBroker.h"
#include "DSClientProxy.h"
#include "ZClientDataset.h"
#include <FMX.StdCtrls.hpp>
#include <System.Rtti.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.Controls.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Data.DB.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <Fmx.Bind.Navigator.hpp>
#include <System.Bindings.Outputs.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class TfrmTest : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TStringGrid *StringGrid1;
	TButton *Button1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TBindNavigator *BindNavigator1;
	TLinkGridToDataSource *LinkGridToDataSourceBindSourceDB1;
	TDataSource *DataSource1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	int m_DataSetType;
	TStrings *m_MasterDisplayName;
	TClientBroker *FClientBroker;
	TZClientDataSet *FJServerDataSetClient;
public:		// User declarations
	__fastcall TfrmTest(TComponent* Owner, TClientBroker *AClientBroker);
	__fastcall ~TfrmTest();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTest *frmTest;
//---------------------------------------------------------------------------
#endif
