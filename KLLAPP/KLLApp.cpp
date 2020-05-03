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
USEFORM("Main.cpp", MainForm);
USEFORM("Filters\QueryFilter.cpp", QueryFilterForm);
USEFORM("Filters\HouseReserveFilters.cpp", HouseReserveFiltersForm);
USEFORM("Filters\SelectCustomer.cpp", SelectCustomerForm);
USEFORM("Filters\SelectPeople.cpp", SelectPeopleForm);
USEFORM("Filters\SelectHouse.cpp", SelectHouseForm);
USEFORM("Sales\HouseReserve.cpp", frmHouseReserve);
USEFORM("Sales\HouseQuery.cpp", frmHouseQuery);
USEFORM("Sales\HouseReserveEdit.cpp", HouseReserveEditForm);
USEFORM("Sales\ShowHSView.cpp", ShowViewForm);
USEFORM("Sales\HouseView.cpp", HouseViewForm);
USEFORM("OA\OAChecker.cpp", frmOAChecker);
USEFORM("MiMessage.cpp", frmMessageForm);
USEFORM("Sales\Customer.cpp", frmCustomer);
USEFORM("Sales\HouseInformation.cpp", HouseInformationForm);
USEFORM("Sales\CustomerEdit.cpp", CustomerEditForm);
USEFORM("Filters\HouseFilters.cpp", HouseFiltersForm);
USEFORM("BaseForm\ItemBaseForm.cpp", frmItemBaseForm);
USEFORM("BaseForm\DetailBaseForm.cpp", frmDetailBaseForm);
USEFORM("BaseForm\BaseForm.cpp", frmBaseForm);
USEFORM("BaseForm\BaseBillForm.cpp", frmBaseBillForm);
USEFORM("BaseForm\BaseListForm.cpp", frmBaseListForm);
USEFORM("BaseForm\CommBase.cpp", CommBaseForm);
USEFORM("BaseForm\BaseListShow.cpp", frmBaseListShow);
USEFORM("Cooperation\WorkReportFilters.cpp", frmWorkReportFilters);
USEFORM("Cooperation\WorkReportEdit.cpp", frmWorkReportEdit);
USEFORM("Cooperation\WorkReportItemEdit.cpp", frmWorkReportItemEdit);
USEFORM("Filters\CustomerFilters.cpp", CustomerFiltersForm);
USEFORM("Filters\BaseFilters.cpp", BaseFiltersForm);
USEFORM("Component\StartAndEndDate.cpp", StartAndEndDateFrame); /* TFrame: File Type */
USEFORM("Cooperation\WorkReport.cpp", frmWorkReport);
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
