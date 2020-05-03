//---------------------------------------------------------------------------

#pragma hdrstop

#include "ShowBizForm.h"
#include "APIbase.h"
//#include "CurrencyData.h"
//#include "StuffStockIn.h"
#include "OAChecker.h"
#include "Customer.h"
#include "HouseReserve.h"
#include "HouseQuery.h"
#include "HouseView.h"
#include "WorkReport.h"
TfrmWorkReport* frmWorkReportDay;
TfrmWorkReport* frmWorkReportWeek;
TfrmWorkReport* frmWorkReportMonth;
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall InitAllMainChildForms()
{
  HouseViewForm=NULL;
  frmOAChecker=NULL;
  frmCustomer=NULL;
  frmHouseReserve=NULL;
  frmHouseQuery=NULL;
  frmWorkReportDay=NULL;
  frmWorkReportWeek=NULL;
  frmWorkReportMonth=NULL;

}
void __fastcall DeleteAllMainChildForms()
{
  if(HouseViewForm)
  {
	delete HouseViewForm;
	HouseViewForm=NULL;
  }
  if(frmOAChecker)
  {
   delete frmOAChecker;
   frmOAChecker=NULL;
  }
  if(frmCustomer)
  {
   delete frmCustomer;
   frmCustomer=NULL;
  }
  if(frmHouseReserve)
  {
   delete frmHouseReserve;
   frmHouseReserve=NULL;
  }
  if(frmHouseQuery)
  {
   delete frmHouseQuery;
   frmHouseQuery=NULL;
  }
  if(frmWorkReportDay)
  {
   delete frmWorkReportDay;
   frmWorkReportDay=NULL;
  }
  if(frmWorkReportWeek)
  {
   delete frmWorkReportWeek;
   frmWorkReportWeek=NULL;
  }
  if(frmWorkReportMonth)
  {
   delete frmWorkReportMonth;
   frmWorkReportMonth=NULL;
  }
}
TForm* __fastcall ShowBizForm(TComponent* Owner,int modulecode,String param)
{
 switch(modulecode)
 {
//  case 1170104:
//  {
//	TfrmCurrencyData *p=new TfrmCurrencyData(Owner,GClientBroker,modulecode,"");
//	return p;
//  }
//	break;
//  case 1050208:
//  {
//	TfrmStuffStockIn *p=new TfrmStuffStockIn(Owner,GClientBroker,modulecode,"",1);
//   return p;
//  }
//  break;
  case 1240302://审批
  {
	if(frmOAChecker==NULL)
		frmOAChecker=new TfrmOAChecker(Owner,GClientBroker,modulecode,param);
	return frmOAChecker;
  }
  break;
  case 1200802://客户资料
  {
	 if(frmCustomer==NULL)
		frmCustomer=new TfrmCustomer(Owner,GClientBroker,modulecode,param);
	 return frmCustomer;
  }
  break;
  case 1201102: //房源查询
  {
	 if(frmHouseQuery==NULL)
		frmHouseQuery=new TfrmHouseQuery(Owner,GClientBroker,modulecode,param);
	 return frmHouseQuery;
  }
  break;
  case 1200302:  //销售预订
  {
	 if(frmHouseReserve==NULL)
		frmHouseReserve=new TfrmHouseReserve(Owner,GClientBroker,modulecode,param);
	 return frmHouseReserve;
  }
  break;
  case 1200305:  //户型多媒体
  {
   if(HouseViewForm==NULL)
	  HouseViewForm=new THouseViewForm(Owner,GClientBroker);
	 return HouseViewForm;
  }
  break;
  case 1240407://工作日报
  {
	if(frmWorkReportDay==NULL)
		frmWorkReportDay=new TfrmWorkReport(Owner,GClientBroker,modulecode,param,4);
	return frmWorkReportDay;
  }
  break;
  case 1240406://工作周报
  {
	if(frmWorkReportWeek==NULL)
		frmWorkReportWeek=new TfrmWorkReport(Owner,GClientBroker,modulecode,param,0);
	return frmWorkReportWeek;
  }
  break;
  case 1240408://工作月报
  {
	if(frmWorkReportMonth==NULL)
		frmWorkReportMonth=new TfrmWorkReport(Owner,GClientBroker,modulecode,param,1);
	return frmWorkReportMonth;
  }
  break;
  default: 	return NULL;
 }
}
