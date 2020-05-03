//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
#include <FMX.MobilePreview.hpp>
//---------------------------------------------------------------------------
USEFORM("Login.cpp", LoginForm);
USEFORM("SaleManagement\Room.cpp", frmRoom);
USEFORM("Main.cpp", MainForm);
USEFORM("DocCheck.cpp", frmDocCheck);
USEFORM("LoanCalculation.cpp", frmLoanCalculation);
USEFORM("WorkFlow\NotPassTextForm.cpp", frmNotPassTextForm);
USEFORM("WorkFlow\WorkFlowDetailForm.cpp", frmWorkFlowDetailForm);
USEFORM("WorkFlow\WorkFlowBrowseForm.cpp", frmWorkFlowBrowseForm);
USEFORM("SaleManagement\SaleSubscribeCancel.cpp", frmSaleSubscribeCancel);
USEFORM("SaleManagement\RoomEdit.cpp", frmRoomEditForm);
USEFORM("SaleManagement\SaleSubscribeMangeDetail.cpp", frmSaleSubscribeMangeDetail);
USEFORM("SaleManagement\SaleSubscribeCancelDetail.cpp", frmSaleSubscribeCancelDetail);
USEFORM("Common\PhotoViewer.cpp", frmPhotoViewer);
USEFORM("BaseForm\BaseForm.cpp", frmBaseForm);
USEFORM("BaseForm\BaseBillForm.cpp", frmBaseBillForm);
USEFORM("ChartReport\EstateTotalReport.cpp", frmEstateTotalReport);
USEFORM("CustomerMng\ClientVisit.cpp", frmCliengVisit);
USEFORM("CustomerMng\ClientEdit.cpp", frmClientEdit);
USEFORM("CustomerMng\ClientVisitEdit.cpp", frmClientVisitEdit);
USEFORM("CustomerMng\ClientVisitDetailEdit.cpp", frmClientVisitDetailEdit);
USEFORM("Component\StartAndEndDate.cpp", StartAndEndDateFrame); /* TFrame: File Type */
USEFORM("CustomerMng\Client.cpp", frmClient);
USEFORM("Config.cpp", ConfigForm);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
