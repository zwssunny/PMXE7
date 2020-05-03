//---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseForm.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.GenData.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <Data.Bind.DBScope.hpp>
#include "ClientEdit.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TfrmClient : public TfrmBaseForm
{
__published:	// IDE-managed Components
	TListView *ListViewClient;
	TClientDataSet *ClientData;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkFillControlToField *LinkFillControlToField1;
	TClientDataSet *Query;
	TIntegerField *ClientDataFID;
	TStringField *ClientDataName;
	TStringField *ClientDataPhone;
	TButton *BtnAdd;
	void __fastcall ListViewClientPullRefresh(TObject *Sender);
	void __fastcall ListViewClientItemClick(TObject * const Sender, TListViewItem * const AItem);
	void __fastcall ListViewClientMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall ListViewClientPaint(TObject *Sender, TCanvas *Canvas, const TRectF &ARect);
	void __fastcall BtnAddClick(TObject *Sender);

private:	// User declarations
	TfrmClientEdit* EditForm;
	TListViewItem* FLoadMore;
	int FTotal,FItemCount;
	void __fastcall InitListView();
	void __fastcall LoadData(int index);
	void __fastcall ClearSeachBox();
	void __fastcall EditFormClose(TObject *Sender, TCloseAction &Action);
public:		// User declarations
	__fastcall TfrmClient(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClient *frmClient;
//---------------------------------------------------------------------------
#endif
