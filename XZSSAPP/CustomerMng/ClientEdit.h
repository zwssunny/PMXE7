//---------------------------------------------------------------------------

#ifndef ClientEditH
#define ClientEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseBillForm.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.Memo.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TfrmClientEdit : public TfrmBaseBillForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edNum;
	TPanel *Panel2;
	TLabel *Label2;
	TEdit *edName;
	TPanel *Panel3;
	TLabel *Label3;
	TEdit *edPhone;
	TPanel *Panel4;
	TLabel *Label4;
	TEdit *edWorkPhone;
	TPanel *Panel5;
	TLabel *Label5;
	TEdit *edFaxPhone;
	TPanel *Panel6;
	TLabel *Label6;
	TEdit *edHomePhone;
	TPanel *Panel7;
	TLabel *Label7;
	TPanel *Panel8;
	TLabel *Label8;
	TComboBox *cbSex;
	TPanel *Panel9;
	TLabel *Label9;
	TComboBox *cbTheType;
	TPanel *Panel10;
	TLabel *Label10;
	TEdit *edAddress;
	TPanel *Panel11;
	TLabel *Label11;
	TEdit *edContactAdd;
	TPanel *Panel12;
	TLabel *Label12;
	TComboBox *cbWork;
	TPanel *Panel13;
	TLabel *Label13;
	TComboBox *cbProperty;
	TPanel *Panel14;
	TLabel *Label14;
	TDateEdit *deBirthday;
	TPanel *Panel15;
	TLabel *Label15;
	TComboBox *cbVehicle;
	TPanel *Panel0;
	TPanel *Panel16;
	TLabel *Label16;
	TComboBox *cbPapersType;
	TPanel *Panel17;
	TLabel *Label17;
	TEdit *edPapersNum;
	TPanel *Panel18;
	TLabel *Label18;
	TEdit *edEmail;
	TPanel *Panel19;
	TLabel *Label19;
	TEdit *edPostalCode;
	TPanel *Panel20;
	TLabel *Label20;
	TEdit *edCompany;
	TPanel *Panel21;
	TLabel *Label21;
	TComboBox *cbMaritalStatus;
	TPanel *Panel22;
	TLabel *Label22;
	TEdit *edBankName;
	TPanel *Panel23;
	TLabel *Label23;
	TEdit *edBankAccount;
	TPanel *Panel24;
	TLabel *Label24;
	TComboBox *cbPosition;
	TPanel *Panel25;
	TLabel *Label25;
	TComboBox *cbEducation;
	TPanel *Panel26;
	TLabel *Label26;
	TComboBox *cbIncome;
	TPanel *Panel28;
	TLabel *Label28;
	TComboBox *cbWorkYears;
	TPanel *Panel27;
	TLabel *Label27;
	TComboBox *cbFamilyStatus;
	TPanel *Panel29;
	TLabel *Label29;
	TPanel *Panel30;
	TMemo *mmRemark;
	TClientDataSet *Query;
	TNumberBox *nbAge;
	TButton *BtnSave;
	TRESTRequest *RESTRequest1;
	TRESTRequest *RESTRequest2;
	TImage *PhooneCall;
	TImage *WorkPhoneCall;
	TImage *HomePhoneCall;
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall DataChange(TObject *Sender);
	void __fastcall PhooneCallClick(TObject *Sender);
private:	// User declarations
	String FID;
	bool FDataChanged,FNeedFreshList;
	void __fastcall InitComboBox();
	bool __fastcall VerifyData();
	void __fastcall SaveData();
public:		// User declarations
	__fastcall TfrmClientEdit(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
	void __fastcall FillData(String id);
	void __fastcall ClearData();
	__property bool NeedFreshList={ read=FNeedFreshList};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClientEdit *frmClientEdit;
//---------------------------------------------------------------------------
#endif
