//---------------------------------------------------------------------------

#pragma hdrstop

#include "ShowBizForm.h"
#include "APIbase.h"
#include "CurrencyData.h"
#include "StuffStockIn.h"
#include "OAChecker.h"
#include "WorkReport.h"
//#include "Customer.h"
//#include "HouseReserve.h"
//#include "HouseQuery.h"
//#include "HouseView.h"
TfrmWorkReport* frmWorkReportDay;
TfrmWorkReport* frmWorkReportWeek;
TfrmWorkReport* frmWorkReportMonth;
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall InitAllMainChildForms()
{

  frmOAChecker=NULL;
  frmCurrencyData=NULL;
  frmStuffStockIn=NULL;
  frmWorkReportDay=NULL;
  frmWorkReportWeek=NULL;
  frmWorkReportMonth=NULL;
//  frmCustomer=NULL;
//  frmHouseReserve=NULL;
//  frmHouseQuery=NULL;
//  HouseViewForm=NULL;
}
void __fastcall DeleteAllMainChildForms()
{
  if(frmOAChecker)
  {
   delete frmOAChecker;
   frmOAChecker=NULL;
  }
  if(frmCurrencyData)
  {
   delete frmCurrencyData;
   frmCurrencyData=NULL;
  }
  if(frmStuffStockIn)
  {
   delete frmStuffStockIn;
   frmStuffStockIn=NULL;
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
TForm* __fastcall ShowBizForm(TComponent* Owner,int modulecode,String Param)
{
 switch(modulecode)
 {
  case 1170104:
  {
	if(frmCurrencyData==NULL)
	  frmCurrencyData=new TfrmCurrencyData(Owner,GClientBroker,modulecode,Param);
	return frmCurrencyData;
  }
	break;
  case 1050208:
  {
   if(frmStuffStockIn==NULL)
	 frmStuffStockIn=new TfrmStuffStockIn(Owner,GClientBroker,modulecode,Param,1);
   return frmStuffStockIn;
  }
  break;
  case 1240302://审批
  {
	if(frmOAChecker==NULL)
		frmOAChecker=new TfrmOAChecker(Owner,GClientBroker,modulecode,Param);
	return frmOAChecker;
  }
  break;
  case 1240407://工作日报
  {
	if(frmWorkReportDay==NULL)
		frmWorkReportDay=new TfrmWorkReport(Owner,GClientBroker,modulecode,Param,4);
	return frmWorkReportDay;
  }
  break;
  case 1240405://工作周报
  {
	if(frmWorkReportWeek==NULL)
		frmWorkReportWeek=new TfrmWorkReport(Owner,GClientBroker,modulecode,Param,0);
	return frmWorkReportWeek;
  }
  break;
  case 1240408://工作月报
  {
	if(frmWorkReportMonth==NULL)
		frmWorkReportMonth=new TfrmWorkReport(Owner,GClientBroker,modulecode,Param,1);
	return frmWorkReportMonth;
  }
  break;
/*  case 1200802://客户资料
  {
	 if(frmCustomer==NULL)
		frmCustomer=new TfrmCustomer(Owner,GClientBroker,modulecode,Param);
	 return frmCustomer;
  }
  break;
  case 1201102: //房源查询
  {
	 if(frmHouseQuery==NULL)
		frmHouseQuery=new TfrmHouseQuery(Owner,GClientBroker,modulecode,Param);
	 return frmHouseQuery;
  }
  break;
  case 1200302:  //销售预订
  {
	 if(frmHouseReserve==NULL)
		frmHouseReserve=new TfrmHouseReserve(Owner,GClientBroker,modulecode,Param);
	 return frmHouseReserve;
  }
  break;
  case 1200305:  //户型多媒体
  {
   if(HouseViewForm==NULL)
	  HouseViewForm=new THouseViewForm(Owner,GClientBroker);
	 return HouseViewForm;
  }
  break;  */
  default: 	return NULL;
 }
}
