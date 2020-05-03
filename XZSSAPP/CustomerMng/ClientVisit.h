//---------------------------------------------------------------------------

#ifndef ClientVisitH
#define ClientVisitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseBillForm.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.MultiView.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <System.JSON.hpp>
#include "ClientVisitEdit.h"
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TfrmCliengVisit : public TfrmBaseBillForm
{
__published:	// IDE-managed Components
	TListView *ListViewClient;
	TButton *BtnQuery;
	TMultiView *QueryView;
	TLabel *Label1;
	TComboBox *cbEstate;
	TLabel *Label2;
	TEdit *edCard;
	TLabel *Label3;
	TEdit *edName;
	TLabel *Label4;
	TEdit *edNum;
	TLabel *Label5;
	TEdit *edTel;
	TClientDataSet *Query;
	TButton *BtnSearch;
	TButton *BtnAdd;
	void __fastcall ListViewClientPullRefresh(TObject *Sender);
	void __fastcall ListViewClientPaint(TObject *Sender, TCanvas *Canvas, const TRectF &ARect);
	void __fastcall BtnSearchClick(TObject *Sender);
	void __fastcall ListViewClientItemClick(TObject * const Sender, TListViewItem * const AItem);
	void __fastcall BtnAddClick(TObject *Sender);
	void __fastcall ListViewClientDeletingItem(TObject *Sender, int AIndex, bool &ACanDelete);
private:	// User declarations
	TListViewItem* FLoadMore;
	int FTotal,FItemCount;
	TJSONArray *FilterParam;
	TfrmClientVisitEdit* EditForm;
	void __fastcall InitQueryView();
	void __fastcall LoadData(int index);
	void __fastcall ClearSeachBox();
	void __fastcall EditFormClose(TObject *Sender, TCloseAction &Action);
public:		// User declarations
	__fastcall TfrmCliengVisit(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCliengVisit *frmCliengVisit;
//---------------------------------------------------------------------------
#endif
