//---------------------------------------------------------------------------

#ifndef SaleSubscribeCancelH
#define SaleSubscribeCancelH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "WorkFlowBrowseForm.h"
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.MultiView.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include "SaleSubscribeCancelDetail.h"
//---------------------------------------------------------------------------
class TfrmSaleSubscribeCancel : public TfrmWorkFlowBrowseForm
{
__published:	// IDE-managed Components
private:	// User declarations
	TfrmSaleSubscribeCancelDetail *DetailForm;
protected:
	String __fastcall GetIDColumnName();
	String __fastcall GetConfigUrl();
	TForm* __fastcall NewEditForm();
public:		// User declarations
	__fastcall TfrmSaleSubscribeCancel(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSaleSubscribeCancel *frmSaleSubscribeCancel;
//---------------------------------------------------------------------------
#endif
