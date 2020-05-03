//---------------------------------------------------------------------------

#pragma hdrstop

#include "ShowBizEditForm.h"
#include "StuffStockInEdit.h"
//#include "HouseReserveEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TForm* __fastcall ShowBizEditForm(TComponent* Owner,int modulecode,String Param,int Flag)
{
  switch(modulecode)
  {
	  case 1050208:
	  {
		TfrmStuffStockInEdit *p=new TfrmStuffStockInEdit(Owner,GClientBroker,modulecode,Param,Flag);
		return p;
	  }
	  break;
//	  case 1200302:  //销售预订
//	  {
//		THouseReserveEditForm *p=new THouseReserveEditForm(Owner,GClientBroker,modulecode,Param,Flag);
//		return p;
//	  }
	  break;
	  default:
	  return NULL;// throw Exception(L"菜单号:"+IntToStr(modulecode)+L"标志:"+IntToStr(Flag)+L"参数:"+Param);
  }
}
