//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "BaseBillForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseForm"
#pragma resource "*.fmx"
TfrmBaseBillForm *frmBaseBillForm;
//---------------------------------------------------------------------------
__fastcall TfrmBaseBillForm::TfrmBaseBillForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param)
	: TfrmBaseForm(Owner,clBroker,modulecode,param)
{
}
//---------------------------------------------------------------------------
__fastcall TfrmBaseBillForm::TfrmBaseBillForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,TClientDataSet *m_DataSet,String param)
	: TfrmBaseForm(Owner,clBroker,modulecode,param)
{
	FDataSet = m_DataSet;
}
//---------------------------------------------------------------------------

