//---------------------------------------------------------------------------

#ifndef DocCheckH
#define DocCheckH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Types.hpp>
#include "ClientBroker.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Grid.hpp>
#include <System.Rtti.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <REST.Response.Adapter.hpp>
//---------------------------------------------------------------------------
class TfrmDocCheck : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TClientDataSet *ClientDataSet1;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TPanel *Panel1;
	TLabel *Label1;
	TPanel *Panel2;
	TButton *btClose;
	TToolBar *ToolBar1;
	TToolBar *ToolBar2;
	TButton *btLook;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall btLookClick(TObject *Sender);
private:	// User declarations
	TClientBroker *FClientBroker;
public:		// User declarations
	__fastcall TfrmDocCheck(TComponent* Owner,TClientBroker *ClientBroker);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDocCheck *frmDocCheck;
//---------------------------------------------------------------------------
#endif
