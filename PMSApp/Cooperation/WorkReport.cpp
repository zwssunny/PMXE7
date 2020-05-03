//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "WorkReport.h"
#include "CommFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseListShow"
#pragma resource "*.fmx"
TfrmWorkReport *frmWorkReport;
//---------------------------------------------------------------------------
__fastcall TfrmWorkReport::TfrmWorkReport(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param,int FormType)
	: TfrmBaseListShow(Owner,clBroker,ModuleCode,Param)
{
	fFormType = FormType;
	GridBindSourceDB->DataSet=this->DataSet->MasterDataSet;
	GridBindSourceDB->DataSource=this->MasterDataSource;
	DataSet->MasterDataSetAfterPost=MasterDataSetAfterPost;
	switch(fFormType)
	{
		case 0:
		 Caption=L"�����ܱ�";
		break;
		case 1:
		 Caption=L"�����±�";
		break;
		case 2:
		 Caption=L"��������";
		break;
		case 3:
		 Caption=L"�����걨";
		break;
		default:
		 Caption=L"�����ձ�";
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkReport::FormFillData()
{
	WorkReportGrid->RowCount = DataSet->MasterDataSet->RecordCount;
	DS_MoveFirst();
	int index = 0;
	while(!Eof)
	{
		WorkReportGrid->Cells[0][index] = VarToStr(GetFieldValue("WorkReportID"));
		WorkReportGrid->Cells[1][index] = VarToStr(GetFieldValue("CorpOgnDeptName"));
		WorkReportGrid->Cells[2][index] = VarToStr(GetFieldValue("EmpName"));

		if(fFormType == 0)
			WorkReportGrid->Cells[3][index] = VarToStr(GetFieldValue("WorkReportYear"))+L"�� ��"+VarToStr(GetFieldValue("WorkReportWeek"))+L"��";
		else if(fFormType == 1)
			WorkReportGrid->Cells[3][index] = VarToStr(GetFieldValue("WorkReportYear"))+L"��"+VarToStr(GetFieldValue("WorkReportMonth"))+L"��";
		else if(fFormType == 2)
			WorkReportGrid->Cells[3][index] = VarToStr(GetFieldValue("WorkReportYear"))+L"�� ��"+VarToStr(GetFieldValue("WorkReportQuarter"))+L"����";
		else if(fFormType == 3)
			WorkReportGrid->Cells[3][index] = VarToStr(GetFieldValue("WorkReportYear"))+L"��";
		else if(fFormType == 4)
			WorkReportGrid->Cells[3][index] = VarToStr(GetFieldValue("WorkReportDate"));

		if(GetFieldValue("WorkReportCheckState") == 1)
			WorkReportGrid->Cells[4][index] = L"�����";
		else if(GetFieldValue("WorkReportState") == 1)
			WorkReportGrid->Cells[4][index] = L"���ύ";
		else
			WorkReportGrid->Cells[4][index] = L"�ݸ�";

		DS_MoveNext();
		index++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkReport::SetUserCtrlStatus()
{
	bool canWrite = OperateRight.Pos(FR_SYSTEMWRITE)>0;
	if(!canWrite)
	{
		EditAction->Enabled = false;
		DelAction->Enabled = false;
	}
}
//---------------------------------------------------------------------------
TForm * __fastcall TfrmWorkReport::NewEditForm(TZClientDataSet *m_DataSet,int status)
{
   if(WorkReportEdit==NULL)
	  WorkReportEdit=new TfrmWorkReportEdit(this,ClientBroker,this->FormModuleCode,m_DataSet,status,fFormType);
   return WorkReportEdit;
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkReport::MasterDataSetAfterPost(TDataSet* DataSet)
{
    SetOptCtrlStatus(0);
	FormFillData();
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkReport::WorkReportGridSelChanged(TObject *Sender)
{
	int row = WorkReportGrid->Selected;
	String fMasterID =  VarToStr(WorkReportGrid->Cells[0][row]);
	bool result = DS_LocateMaster(fMasterID);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmWorkReport::BeforeUpdateData(int OptType)
{
	if(OptType == (int)otDel)
	{
		int Check = GetFieldValue("WorkReportCheckState");
		if(Check != 0)
		{
            ShowMessage(_D("����ˣ�����ɾ����"));
			return false;
        }
	}
	return true;
}
//---------------------------------------------------------------------------
TForm * __fastcall TfrmWorkReport::NewFilterForm(TOnFilteredDataSet AOnFilteredDataSet,TClientBroker * ABroker) //�������˴��ڣ����ݲ�ѯ�¼�
{
   if(FiltersForm==NULL)
	 FiltersForm= new TfrmWorkReportFilters(this,AOnFilteredDataSet,ABroker,fFormType,FormDefRight.Pos(31) > 0);
   return FiltersForm;
}
//---------------------------------------------------------------------------