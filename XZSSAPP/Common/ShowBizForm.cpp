//---------------------------------------------------------------------------

#pragma hdrstop

#include "ShowBizForm.h"
#include "LoanCalculation.h"
#include "Room.h"
#include "SaleSubscribeCancel.h"
#include "Client.h"
#include "ClientVisit.h"
#include "EstateTotalReport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall InitAllMainChildForms()
{
	frmLoanCalculation = NULL;
	frmRoom = NULL;
	frmSaleSubscribeCancel = NULL;
	frmClient = NULL;
	frmCliengVisit = NULL;
	frmEstateTotalReport = NULL;
}
//---------------------------------------------------------------------------
void __fastcall DeleteAllMainChildForms()
{
	if(frmLoanCalculation)
	{
		delete frmLoanCalculation;
		frmLoanCalculation = NULL;
	}
	if(frmRoom)
	{
		delete frmRoom;
		frmRoom = NULL;
	}
	if(frmSaleSubscribeCancel)
	{
		delete frmSaleSubscribeCancel;
		frmSaleSubscribeCancel = NULL;
	}
	if(frmClient)
	{
		delete frmClient;
		frmClient = NULL;
	}
	if(frmCliengVisit)
	{
		delete frmCliengVisit;
		frmCliengVisit = NULL;
	}
    if(frmEstateTotalReport)
	{
		delete frmEstateTotalReport;
		frmEstateTotalReport = NULL;
	}
}
//---------------------------------------------------------------------------
TForm* __fastcall ShowBizForm(TComponent* Owner,int modulecode,TClientBroker *clBroker,String param)
{
	switch(modulecode)
	{
		case 3:
		{
			if(frmRoom == NULL)
				frmRoom = new TfrmRoom(Owner,clBroker,modulecode,param);
			return frmRoom;
		}
		case 30:
		{
			if(frmSaleSubscribeCancel == NULL)
				frmSaleSubscribeCancel = new TfrmSaleSubscribeCancel(Owner,clBroker,modulecode,param);
			return frmSaleSubscribeCancel;
		}
		case 24:
		{
			if(frmClient == NULL)
				frmClient = new TfrmClient(Owner,clBroker,modulecode,param);
			return frmClient;
		}
		case 12:
		{
			if(frmCliengVisit == NULL)
				frmCliengVisit = new TfrmCliengVisit(Owner,clBroker,modulecode,param);
			return frmCliengVisit;
		}
		case 35:
		{
			if(frmEstateTotalReport == NULL)
				frmEstateTotalReport = new TfrmEstateTotalReport(Owner,clBroker,modulecode,param);
			return frmEstateTotalReport;
        }
		case 9999:
		{
			if(frmLoanCalculation == NULL)
				frmLoanCalculation = new TfrmLoanCalculation(Owner,clBroker);
			return frmLoanCalculation;
        }
		default: 	return NULL;
	}
}
//---------------------------------------------------------------------------
