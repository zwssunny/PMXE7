//---------------------------------------------------------------------------

#ifndef ClientVisitDetailEditH
#define ClientVisitDetailEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseBillForm.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class TfrmClientVisitDetailEdit : public TfrmBaseBillForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edSubject;
	TEdit *edAddress;
	TDateEdit *deDate;
	TMemo *mmSummary;
	TButton *BtnSave;
	TClientDataSet *Query;
	void __fastcall BtnSaveClick(TObject *Sender);
private:	// User declarations
	String FMasterID;
	String FID;
	bool FNeedFreshList;
	void __fastcall ClearData();
public:		// User declarations
	__fastcall TfrmClientVisitDetailEdit(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
	__property String MasterID={ read=FMasterID,write=FMasterID};
	void __fastcall FillData(String ID);
	__property bool NeedFreshList={ read=FNeedFreshList};

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClientVisitDetailEdit *frmClientVisitDetailEdit;
//---------------------------------------------------------------------------
#endif
