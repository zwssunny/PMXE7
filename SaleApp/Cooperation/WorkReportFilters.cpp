//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "WorkReportFilters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseFilters"
#pragma link "StartAndEndDate"
#pragma resource "*.fmx"
TfrmWorkReportFilters *frmWorkReportFilters;
//---------------------------------------------------------------------------
__fastcall TfrmWorkReportFilters::TfrmWorkReportFilters(TComponent* Owner,TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker,int FormType,bool ViewAll)
	: TBaseFiltersForm(Owner,AOnFilteredDataSet,ABroker)
{
	fFormType = FormType;
	fViewAll = ViewAll;
}
//---------------------------------------------------------------------------
String __fastcall TfrmWorkReportFilters::BuildFilters()
{
	String ClientFilter="WorkReportType="+IntToStr(fFormType);
	if(BillDateExpander->IsChecked)
	{
		if(ClientFilter>"")
			ClientFilter=ClientFilter+" and ";
		ClientFilter=ClientFilter+"WorkReportEndDate>='"+deFilterDate->BeginDate
				+"' and WorkReportStartDate<='" +deFilterDate->EndDate+"'";
	}
	if(!fViewAll)
	{
        //能看自己的，同时能看下级已提交的报告。
		String DeptFilter="";
		String sFilter="";
		Query->Close();
		Query->SQL->Text = "select distinct CorpOgnSortCode from tbCorporationOrganize where CorpOgnDeptManager='"+ClientBroker->UserEmpID+"' or CorpOgnLead='"+ClientBroker->UserEmpID+"'";
		Query->Open();
		if(Query->RecordCount > 0)
		{
			while(!Query->Eof)
			{
				if(DeptFilter.Trim().IsEmpty())
					DeptFilter = "  CorpOgnSortCode like '" +Query->FieldByName("CorpOgnSortCode")->AsString.Trim()+"%'";
				else
					DeptFilter = " or CorpOgnSortCode like '" +Query->FieldByName("CorpOgnSortCode")->AsString.Trim()+"%'";
				sFilter += DeptFilter;
				Query->Next();
			}
			Query->Close();
		}
		if(sFilter>"")
			sFilter =  "((WorkReportState=1 and ("+sFilter+")) or WorkReportEmpID='"+ClientBroker->UserEmpID+"')";
		else
			sFilter = "WorkReportEmpID='"+ClientBroker->UserEmpID+"'";
        if(ClientFilter>"")
			ClientFilter=ClientFilter+" and ";
		ClientFilter=ClientFilter+sFilter;
	}

	return ClientFilter;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkReportFilters::FillReporterComBox()
{
	cbReporter->Clear();
	TListBoxItem * newBoxItem=new TListBoxItem(cbReporter);
	newBoxItem->Text=L"所有";
	newBoxItem->TagString="0";
	cbReporter->AddObject(newBoxItem);
}
//---------------------------------------------------------------------------

