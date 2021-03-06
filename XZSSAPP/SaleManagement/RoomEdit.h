//---------------------------------------------------------------------------

#ifndef RoomEditH
#define RoomEditH
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
#include <FMX.TabControl.hpp>
#include <FMX.ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <FMX.Objects.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include "PhotoViewer.h"
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
//---------------------------------------------------------------------------
class TfrmRoomEditForm : public TfrmBaseBillForm
{
__published:	// IDE-managed Components
	TVertScrollBox *VertScrollBox1;
	TExpander *expBaseInfo;
	TFlowLayout *FlowLayout1;
	TPanel *Panel3;
	TLabel *Label3;
	TEdit *edEstateName;
	TPanel *Panel2;
	TLabel *Label2;
	TEdit *edBuildName;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edRoomName;
	TPanel *Panel4;
	TLabel *Label4;
	TEdit *edFloorNum;
	TPanel *Panel5;
	TLabel *Label5;
	TEdit *edNumber;
	TPanel *Panel6;
	TLabel *Label6;
	TExpander *expAttribute;
	TFlowLayout *FlowLayout2;
	TPanel *Panel7;
	TLabel *Label7;
	TPanel *Panel8;
	TLabel *Label8;
	TPanel *Panel9;
	TLabel *Label9;
	TPanel *Panel10;
	TLabel *Label10;
	TPanel *Panel11;
	TLabel *Label11;
	TPanel *Panel12;
	TLabel *Label12;
	TEdit *edDeliveryDate;
	TPanel *Panel13;
	TLabel *Label13;
	TPanel *Panel14;
	TLabel *Label14;
	TExpander *expAea;
	TFlowLayout *FlowLayout3;
	TPanel *Panel15;
	TLabel *Label15;
	TPanel *Panel16;
	TLabel *Label16;
	TPanel *Panel17;
	TLabel *Label17;
	TPanel *Panel18;
	TLabel *Label18;
	TPanel *Panel19;
	TLabel *Label19;
	TPanel *Panel20;
	TLabel *Label20;
	TEdit *edInnerFactArea;
	TPanel *Panel21;
	TLabel *Label21;
	TPanel *Panel22;
	TLabel *Label22;
	TEdit *edFloorArea;
	TEdit *edInnerArea;
	TEdit *edFloorPreArea;
	TEdit *edInnerPreArea;
	TEdit *edFloorFactArea;
	TSwitch *swIsDuplex;
	TPanel *Panel26;
	TLabel *Label26;
	TEdit *edUpperArea;
	TPanel *Panel27;
	TLabel *Label27;
	TEdit *edLowerArea;
	TPanel *Panel23;
	TLabel *Label23;
	TEdit *edGardenFactArea;
	TPanel *Panel24;
	TLabel *Label24;
	TEdit *edPublicArea;
	TPanel *Panel25;
	TLabel *Label25;
	TEdit *edBalconyArea;
	TExpander *expPrice;
	TFlowLayout *FlowLayout4;
	TPanel *Panel28;
	TLabel *Label28;
	TEdit *edFloorAreaPrice;
	TPanel *Panel29;
	TLabel *Label29;
	TEdit *edInnerAreaPrice;
	TPanel *Panel30;
	TLabel *Label30;
	TPanel *Panel31;
	TLabel *Label31;
	TPanel *Panel32;
	TLabel *Label32;
	TEdit *edStatus;
	TEdit *edFunction;
	TEdit *edDecoration;
	TEdit *edHouseType;
	TEdit *edOrientation;
	TEdit *edLandscape;
	TEdit *edDeliveryState;
	TEdit *edSellType;
	TComboBox *cbAreaType;
	TTabControl *TabControl;
	TTabItem *DataTab;
	TTabItem *ImageTab;
	TClientDataSet *Query;
	TRESTResponse *tempResponse;
	TFlowLayout *ImageListLayout;
	TAniIndicator *WaitAniIndicator;
	TNumberBox *nbSellAmt;
	TNumberBox *nbSubscribeAmt;
	TNumberBox *nbSubsidyAmt;
	TButton *BtnReserve;
	TButton *BtnLoanCal;
	void __fastcall TabControlChange(TObject *Sender);
	void __fastcall BtnLoanCalClick(TObject *Sender);
	void __fastcall BtnReserveClick(TObject *Sender);
private:	// User declarations
	String AppPath;
	TStringList *FDictionary;
	String FEstateName,FBuildName;
	int FCurID;
	TStringList *FBitmapList;
	TfrmPhotoViewer *FPhotoViewer;
	void __fastcall SetUserCtrlStatus();
	String __fastcall GetTextFromDict(String id);
	void __fastcall DownloadHouseView();
	void __fastcall ShowHouseView();
	void __fastcall imageClick(TObject *Sender);
public:		// User declarations
	__fastcall TfrmRoomEditForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,TClientDataSet *m_DataSet,String param);
	__property TStringList *Dictionary={ read=FDictionary,write=FDictionary};
	__property String EstateName={ read=FEstateName,write=FEstateName};
	__property String BuildName={ read=FBuildName,write=FBuildName};
	void __fastcall FillData();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRoomEditForm *frmRoomEditForm;
//---------------------------------------------------------------------------
#endif
