//---------------------------------------------------------------------------

#ifndef QueryFilterH
#define QueryFilterH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "ZClientQuery.h"
#include "ClientBroker.h"
//---------------------------------------------------------------------------
class TQueryFilterForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *tBarTitle;
	TToolBar *tBarBottom;
	TLabel *lbTitle;
	TListView *lvQueryData;
	TButton *btQuery;
	TButton *btCancel;
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall btQueryClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	TEdit *FEdit;
	String FSQL;
	TClientBroker *FBroker;
	TZClientQuery *Query;
	void __fastcall FillQueryData();
public:		// User declarations
	__fastcall TQueryFilterForm(TComponent* Owner,TClientBroker *clBroker,
					TEdit *TagEdit,String ATitle,String ASQL);
	virtual __fastcall ~TQueryFilterForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TQueryFilterForm *QueryFilterForm;
//---------------------------------------------------------------------------
#endif