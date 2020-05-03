//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HouseInformation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DetailBaseForm"
#pragma resource "*.fmx"
THouseInformationForm *HouseInformationForm;
//---------------------------------------------------------------------------
__fastcall THouseInformationForm::THouseInformationForm(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet
								*FDataSet,int DataSetStatus)
	: TfrmDetailBaseForm(Owner,clBroker,ModuleCode,FDataSet, DataSetStatus)
{
}
//---------------------------------------------------------------------------
void __fastcall THouseInformationForm::FormInitControl()
{
//    1-δ����2-Ԥ����3-�Ѷ���4-���ۡ�5-���⡢6-ɾ���ȣ�Ĭ��ֵΪ1
	cbBoxHsgState->Clear();
	cbBoxHsgState->Items->Add(L"δ֪");
	cbBoxHsgState->Items->Add(L"δ��");
	cbBoxHsgState->Items->Add(L"Ԥ��");
	cbBoxHsgState->Items->Add(L"�Ѷ�");
	cbBoxHsgState->Items->Add(L"����");
	cbBoxHsgState->Items->Add(L"����");
	cbBoxHsgState->Items->Add(L"ɾ��");
	cbBoxHsgState->ItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall THouseInformationForm::FormClearControl(int Section)
{

}
//---------------------------------------------------------------------------
void __fastcall THouseInformationForm::SendDataToDataSet(int Section)
{

}
//---------------------------------------------------------------------------
void __fastcall THouseInformationForm::GetDataFromDataSet(int Section)
{
 	edEstateName->Text=GetFieldValue("EstateName");
	edBdgName->Text=GetFieldValue("BdgName");
	edHsgNum->Text=GetFieldValue("HsgNum");
	edHsgName->Text=GetFieldValue("HsgName");
	edHsgFnRemark->Text=GetFieldValue("HsgFnRemark");
	edHsgHTRemark->Text=GetFieldValue("HsgHTRemark");
	edHsgOnRemark->Text=GetFieldValue("HsgOnRemark");
	edHsgDnRemark->Text=GetFieldValue("HsgDnRemark");
	edHsgLeRemark->Text=GetFieldValue("HsgLeRemark");
	edHsgFloorSpace->Text=GetFieldValue("HsgFloorSpace");
	edHsgInnerArea->Text=GetFieldValue("HsgInnerArea");
	edHsgBalconyArea->Text=GetFieldValue("HsgBalconyArea");
	edHsgPublicArea->Text=GetFieldValue("HsgPublicArea");
	edHsgUpperArea->Text=GetFieldValue("HsgUpperArea");
	edHsgLowerArea->Text=GetFieldValue("HsgLowerArea");
	ckBoxIsDouble->IsChecked=(GetFieldValue("HsgIsDuplex")==1);
	edHsgSellPrice->Text=GetFieldValue("HsgSellPrice");
	edHsgSellTotal->Text=GetFieldValue("HsgSellTotal");
	//��Ԫ״̬
	int HsgState=GetFieldValue("HsgState");
	cbBoxHsgState->ItemIndex=HsgState;
	//Ԥ��
	if(HsgState==3)
	{
		ReserveExpander->Visible=true;
		edHseRsveNum->Text=GetFieldValue("HseRsveNum");
		edHseRsveDate->Text=GetFieldValue("HseRsveDate");
		edHseRsveFKID_Client->Text=GetFieldValue("HseRsveFKID_Client");
		edHseRsveSubsAmt->Text=GetFieldValue("HseRsveSubsAmt");
	}
	else
	 ReserveExpander->Visible=false;
	//�Ϲ�
	if(HsgState==4)
	{
		SellExpander->Visible=true;
		edSubsBillNum->Text=GetFieldValue("SubsBillNum");
		edSubsBillContSignDate->Text=GetFieldValue("SubsBillContSignDate");
		edSubsBillFKID_Client->Text=GetFieldValue("SubsBillFKID_Client");
		edSubsBillSaleTotal->Text=GetFieldValue("SubsBillSaleTotal");
		edSubsBillPayMode->Text=GetFieldValue("SubsBillPayMode");
		SubsBillStats->Text=GetFieldValue("SubsBillStats");
		edHsgMnyBillLevyAmt->Text=GetFieldValue("HsgMnyBillLevyAmt");
		edHsgMnyBillPayAmt->Text=GetFieldValue("HsgMnyBillPayAmt");
		edflag->Text=GetFieldValue("flag");
		edHsgHandoverDate->Text=GetFieldValue("HsgHandoverDate");
	}
	else
	SellExpander->Visible=false;

   UnitExpanderResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall THouseInformationForm::VerifyFieldData(int Section,int status)
{

}
//---------------------------------------------------------------------------
bool __fastcall THouseInformationForm::BeforeUpdateData(int OptType)
{
   return false;
}
//---------------------------------------------------------------------------
void __fastcall THouseInformationForm::SetUserCtrlStatus()
{
//����Ҫ�༭����
  DetailEditAction->Enabled=false;
  SaveDetailAction->Enabled=false;
}
void __fastcall THouseInformationForm::UnitExpanderResize(TObject *Sender)
{
	EditLayout->Height=UnitExpander->Height
			+(SellExpander->Visible? SellExpander->Height:0)
			+(ReserveExpander->Visible? ReserveExpander->Height:0);
}
//---------------------------------------------------------------------------
	/* TODO -ozws -c��Դ��ѯ : ����ֱ��Ԥ������ */
		  /* TODO -ozws -c��Դ��ѯ : ���ӻ���ͼƬ�鿴���� */