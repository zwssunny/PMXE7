//---------------------------------------------------------------------------

#ifndef ZhengQiGuoLuH
#define ZhengQiGuoLuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <System.Rtti.hpp>
#include "ClientBroker.h"
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class TfrmZhengQiGuoLu : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TToolBar *ToolBar2;
	TButton *btClose;
	TStringGrid *StringGrid1;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
	TButton *btLook;
	TClientDataSet *ClientDataSet1;
	TStringColumn *StringColumn8;
	TStringColumn *StringColumn9;
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall btLookClick(TObject *Sender);
private:	// User declarations
	TClientBroker *FClientBroker;
	String FlowID;
	String __fastcall EncodeJsonDate(String date);
public:		// User declarations
	__fastcall TfrmZhengQiGuoLu(TComponent* Owner,TClientBroker *ClientBroker,String Flowid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmZhengQiGuoLu *frmZhengQiGuoLu;
//---------------------------------------------------------------------------
#endif
