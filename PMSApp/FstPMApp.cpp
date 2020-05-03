//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
#include <FMX.MobilePreview.hpp>
//---------------------------------------------------------------------------
USEFORM("Filters\SelectPeople.cpp", SelectPeopleForm);
USEFORM("Login.cpp", LoginForm);
USEFORM("Filters\HouseReserveFilters.cpp", HouseReserveFiltersForm);
USEFORM("Filters\HouseFilters.cpp", HouseFiltersForm);
USEFORM("Filters\QueryFilter.cpp", QueryFilterForm);
USEFORM("Filters\SelectHouse.cpp", SelectHouseForm);
USEFORM("Filters\SelectCustomer.cpp", SelectCustomerForm);
USEFORM("Purchase\StuffStockInEdit.cpp", frmStuffStockInEdit);
USEFORM("Purchase\StuffStockIn.cpp", frmStuffStockIn);
USEFORM("Purchase\StuffStockInFilters.cpp", StuffStockInFiltersForm);
USEFORM("System\CurrencyDataEdit.cpp", frmCurrencyDataEdit);
USEFORM("System\CurrencyData.cpp", frmCurrencyData);
USEFORM("MiMessage.cpp", frmMessageForm);
USEFORM("Main.cpp", MainForm);
USEFORM("OA\OAChecker.cpp", frmOAChecker);
USEFORM("Purchase\StockInItemEdit.cpp", frmStockInItemEdit);
USEFORM("Purchase\SelectStuSupplyNote.cpp", SelectStuSupplyNoteForm);
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
