//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DetailBaseForm.h"
#include "FSTMessageDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseBillForm"
#pragma resource "*.fmx"
TfrmDetailBaseForm *frmDetailBaseForm;
//---------------------------------------------------------------------------
__fastcall TfrmDetailBaseForm::TfrmDetailBaseForm(TComponent * Owner, TClientBroker * clBroker, int
				  ModuleCode, String Param)
			  :TfrmBaseBillForm(Owner, clBroker, ModuleCode, Param)
{
	InitDetailBase();
}
//---------------------------------------------------------------------------
__fastcall TfrmDetailBaseForm::TfrmDetailBaseForm(TComponent * Owner, TClientBroker * clBroker,
				  int ModuleCode,TZClientDataSet * FDataSet, int DataSetStatus)
			  :TfrmBaseBillForm(Owner, clBroker,ModuleCode,FDataSet, "")
{
	InitDetailBase();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::InitDetailBase()
{
  	  tcDetailControl->ActiveTab=tabDetail;
	  tcMainControl->ActiveTab=TabDetailMain;
	  TabDetailItem->Visible=false;
	  btMainNext->Visible=false;
	  TaskQuery=new TZClientQuery(this,ClientBroker);
	  TaskLogQuery=new TZClientQuery(this,ClientBroker);
	  TaskDefListDs=new TClientDataSet(this);
	  FOnBeforWorkFlowStart=NULL;
	  FOnAfterWorkFlowStart=NULL;
	  FOnBeforWorkFlowExec=NULL;
	  FOnAfterWorkFlowExec=NULL;
	  TaskSelected="";
	  lbCreatorName->Text="";
	  lbTaskTitleText->Text="";
	  MainVertScrollBox->OnCalcContentBounds = CalcContentBoundsProc;
	  FTaskLogUpdate=false;
	  FTaskFlowUpdate=false;
	  HWScale=1;
	  FLastDistance = 0;
}
//---------------------------------------------------------------------------
__fastcall TfrmDetailBaseForm::~TfrmDetailBaseForm()
{
   delete TaskQuery;
   delete TaskLogQuery;
   delete TaskDefListDs;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::AddItemData()          //��������
{
 if(BeforeUpdateData((int)otAddDetail) == true)
  {
	 ShowItemEditForm(3);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::EditItemData()         //�޸�����
{
  if(RecordCount > 0&&this->DetailCount>0)
  {
	if(BeforeUpdateData((int)otEditDetail) == true)
    {
	  ShowItemEditForm(4);
    }
  }
  else
	 ShowMessage(_D("�޿ɱ༭����"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::DelItemData()          //ɾ������
{
  if(RecordCount > 0&&this->DetailCount>0)
  {
    if(BeforeUpdateData((int)otDelDetail) == true)
    {
	  TMessageDialogEventProc msgDialogCloseProc=&DoDelItemData;
	  ShowMessageBox(_D("�Ƿ�Ҫɾ����ǰ����") ,msgDialogCloseProc);
	}
  }
  else
	ShowMessage(_D("�޿�ɾ������"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::DoDelItemData(System::Uitypes::TModalResult AResult)
{
 if(AResult==mrYes)
 {
		 DS_DeleteDetail();
		 if(DataSet != NULL)
		 {
			SetOptCtrlStatus(0);
			FormFillData();
		 }
 }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::BrowseItemRecord()     //�������
{
  if(RecordCount > 0&&this->DetailCount>0)
  {
	if(BeforeUpdateData((int)otBrowse) == true)
    {
	  ShowItemEditForm(0);
    }
  }
  else
  ShowMessage(_D("�޿ɲ鿴����"));

}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::SetOptCtrlStatus(int status)
{
  OperateStatus = status;
  bool HasFlowDefinID=FlowDefinID>"";
  bool HasWorkFlowID=WorkflowID>"";
  if(OperateRight.Pos(FR_SYSTEMWRITE) <= 0 && OperateRight.Pos(FR_SYSTEMREAD) > 0) //ֻ��Ȩ��
  {
		SaveDetailAction->Enabled = false;
		DetailEditAction->Enabled = false;
		AddItemAction->Enabled = false;
		DeleteItemAction->Enabled = false;
  }
  else
  {
    switch(status) //����״̬����
    {
      case 0: //���
		SaveDetailAction->Enabled = false;
		DetailEditAction->Enabled = true;
		BrowseItemAction->Enabled =true;
		AddItemAction->Enabled = true;
		DeleteItemAction->Enabled = true;
//		OACheckAction->Enabled = (WorkflowStatus!=wsNotStarted)&&(WorkflowStatus!=wsFinished);
		OACloseAction->Enabled= WorkflowStatus==wsRunning;
		OAStareAction->Enabled = !HasWorkFlowID&&HasFlowDefinID&&(WorkflowStatus==wsNotStarted);
		break;
	  case 1: //����
		SaveDetailAction->Enabled = true;
		DetailEditAction->Enabled = false;
//		OACheckAction->Enabled = false;
		OACloseAction->Enabled= false;
		BrowseItemAction->Enabled =false;
		AddItemAction->Enabled = false;
		DeleteItemAction->Enabled = false;
		break;
	  case 2: //�༭
		SaveDetailAction->Enabled = true;
		DetailEditAction->Enabled = false;
//		OACheckAction->Enabled = false;
		OACloseAction->Enabled= false;
		OAStareAction->Enabled = false;
		BrowseItemAction->Enabled =true;
		AddItemAction->Enabled = true;
		DeleteItemAction->Enabled = true;
		break;
	  case 3:   //��ϸ���� ������ϸ������ʵ��
	  case 4://��ϸ�༭������ϸ������ʵ��
	  default:
		break;
	}
  }
  if(this->DataSetType==2&& this->DetailCount<=0)
  {
		BrowseItemAction->Enabled =false;
	  //	AddItemAction->Enabled = false;
		DeleteItemAction->Enabled = false;
  }
  MoveNextAction->Enabled=(RecordCount>0)&&(!Eof);
  MovePriorAction->Enabled=(RecordCount>0)&&(!Bof);
  tabOA->Visible=HasFlowDefinID;
  tabTaskLog->Visible=HasWorkFlowID||HasFlowDefinID;
  tabTaskflow->Visible=HasWorkFlowID||HasFlowDefinID;
  ShowflowChartAction->Enabled=HasFlowDefinID;
  edWorkflowTitle->Enabled=HasFlowDefinID&&(!HasWorkFlowID);
  mmWorkflowContent->ReadOnly=!(HasFlowDefinID&&(!HasWorkFlowID));
  cbWorkflowLeve->Enabled=HasFlowDefinID&&(!HasWorkFlowID);
  if(HasFlowDefinID&&(!HasWorkFlowID))
	 tcWorkflowControl->ActiveTab=TabCheckStare;
   else
	 tcWorkflowControl->ActiveTab=TabCheckExec;
  SetUserCtrlStatus();    //��״̬�����û�����״̬
}
void __fastcall TfrmDetailBaseForm::SaveDetailActionExecute(TObject *Sender)
{
   SaveData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::GetWorkflowDefine()
{
	Query->Close();
	Query->SQL->Text="Select FlowOperPKID_Flow from tbFlowOperation where FlowOperPKID="+QuotedStr(IntToStr(FormID));
	Query->Open();
	if(Query->RecordCount>0)
	   FlowDefinID=Query->FieldByName("FlowOperPKID_Flow")->AsString;
	else
      FlowDefinID="";
}
void __fastcall TfrmDetailBaseForm::GetWorkflowRunID(String BillID)
{
	Query->Close();
	Query->SQL->Text="Select FlowMnPKID,FlowMnState from tbFlowMain where FlowMnBusWindow="+QuotedStr(IntToStr(FormID))+" and FlowMnBusCode="+QuotedStr(BillID);
	Query->Open();
	if(Query->RecordCount>0)
	{
	   WorkflowID=Query->FieldByName("FlowMnPKID")->AsString;
	   WorkflowStatus=TWorkflowStatus(Query->FieldByName("FlowMnState")->AsInteger);
	}
	else
	{
		WorkflowID="";
		WorkflowStatus=wsNotStarted;
    }
}
void __fastcall TfrmDetailBaseForm::OACheckActionExecute(TObject *Sender)
{
 	TStream *dsStream=NULL;
	 if(WorkflowID>" ")//��˲���
	  {
		String taskInsKey=TaskQuery->FieldByName("FlowMnDtlPKID")->AsString;
		String TaskdefResults=cbFlowMnDtlResults->Items->Strings[cbFlowMnDtlResults->ItemIndex];
		TWorkFlowExecData *AWorkFlowExecData=new TWorkFlowExecData;
		TClientDataSet *varDataSet=new TClientDataSet(this);
		try{
			AWorkFlowExecData->FlowDefID= FlowDefinID;
			AWorkFlowExecData->WorkInsID=WorkflowID;
			AWorkFlowExecData->TaskInsID= taskInsKey;
			AWorkFlowExecData->TskStatus= TaskdefResults;
			AWorkFlowExecData->TskComments=edFlowMnDtlComments->Text;
			//ͨ�������¼���������б���
			 /*��Ҫ���ر����б� */

			TStream *dsStream=ClientBroker->GetVariableListDS(taskInsKey);
			varDataSet->LoadFromStream(dsStream);
			//�����¼�
			if(FOnBeforWorkFlowExec)
			  FOnBeforWorkFlowExec(AWorkFlowExecData, varDataSet);
			else
			  throw Exception(L"Ҫ��ʵ���¼�OnBeforWorkFlowExec");
			TJSONArray * varJsonArray=new TJSONArray();
			varDataSet->First();
			while(!varDataSet->Eof)
			{
				TJSONObject *rcdOject=new TJSONObject();
				rcdOject->AddPair(new TJSONPair("TaskInsID",varDataSet->FieldByName("TaskInsID")->AsString));
				rcdOject->AddPair(new TJSONPair("Caption",varDataSet->FieldByName("Caption")->AsString));
				rcdOject->AddPair(new TJSONPair("VarName",varDataSet->FieldByName("VarName")->AsString));
				rcdOject->AddPair(new TJSONPair("VarValue",varDataSet->FieldByName("VarValue")->AsString));
				rcdOject->AddPair(new TJSONPair("ReadOnly",varDataSet->FieldByName("ReadOnly")->AsInteger));
				rcdOject->AddPair(new TJSONPair("Required",varDataSet->FieldByName("Required")->AsInteger));
				varJsonArray->AddElement(rcdOject);
				varDataSet->Next();
			}
			bool retOk=ClientBroker->ServerWorkFlowExec(AWorkFlowExecData->FlowDefID, AWorkFlowExecData->WorkInsID,
				 AWorkFlowExecData->TaskInsID, AWorkFlowExecData->TskStatus, AWorkFlowExecData->TskComments, varJsonArray);
			if(retOk)
			{
				if(FOnAfterWorkFlowExec)
					FOnAfterWorkFlowExec(WorkflowID, taskInsKey);
				FillTask();//ˢ��һ������
                SetOptCtrlStatus(0);
			}
		}
		__finally
		{
			delete AWorkFlowExecData;
			delete varDataSet;
		}
	  }

}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FillTask()
{
 TaskBindGridLink->Active=false;
 TaskQuery->Close();
 if(WorkflowID<" ") return;
 TaskQuery->SQL->Text="select FlowMnDtlPKID,FlowMnDtlFKID,FlowMnDtlNum,FlowMnDtlName,FlowMnDtlState,FlowMnDtlSender,"
	"(case when FlowMnDtlUserType=0 then (select EmpName from tbEmployeeData where EmpPKID=FlowMnDtlSender) "
	"when FlowMnDtlUserType=1 then( select RoleName from tbRoleData where RolePKID=FlowMnDtlSender) "
	"when FlowMnDtlUserType=2 then( select DutyDataName from tbDutyData where DutyDataPKID=FlowMnDtlSender) "
	"else (select CorpOgnDeptName from tbCorporationOrganize where CorpOgnPKID=FlowMnDtlSender)end) as FlowMnDtlSenderName,"
	"FlowMnDtlSendTime,FlowMnDtlComments,FlowMnDtlReceiver,FlowMnDtlRemark, "
	"(select EmpName from tbEmployeeData where EmpPKID=FlowMnDtlReceiver) as FlowMnDtlReceiverName,"
	"FlowMnDtlResults,FlowMnDtlChkTime,FlowMnDtlStep,FlowMnDtlUserType, "
	"FlowMnCreateTime,FlowMnCreator,FlowMnSubject,FlowMnContent,FlowMnBusWindow,FlowMnState,FlowMnRank,"
	"(select EmpName from tbEmployeeData where EmpPKID=FlowMnCreator) as FlowMnCreatorName "
	" from tbFlowMain_Detail left join tbFlowMain on FlowMnPKID= FlowMnDtlFKID "
	" where FlowMnDtlFKID=" +QuotedStr(WorkflowID)+
	" order by FlowMnDtlNum";
 TaskQuery->Open();
 TaskBindSourceDB->DataSet=TaskQuery;
 TaskBindGridLink->Active=true;

}

//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FillTaskLog()
{
  if(FTaskLogUpdate)
	 return;
  FTaskLogUpdate=true;
  TaskLogBindGridLink->Active=false;
  TaskLogQuery->Close();
  if(WorkflowID<" ")
    return;
  TaskLogQuery->SQL->Text="select FlowTaskLogID,FlowTaskLogFlowInsID,FlowTaskLogTaskInsID,FlowTaskLogDate"
	  ",FlowTaskLogOperation,FlowTaskLogUserID,FlowTaskLogInfo,FlowTaskLogInfo2"
	  ",(select EmpName from tbEmployeeData where EmpPKID=FlowTaskLogUserID) as FlowTaskLogUserName "
	  ",(select FlowMnDtlName  from tbFlowMain_Detail where FlowMnDtlPKID=FlowTaskLogTaskInsID) as FlowTaskLogTaskName "
	  " from tbFlowTaskLog where FlowTaskLogFlowInsID="+QuotedStr(WorkflowID)+
	  " order by FlowTaskLogID";
  TaskLogQuery->Open();
  TaskLogBindSourceDB->DataSet=TaskLogQuery;
  TaskLogBindGridLink->Active=true;

}
//---------------------------------------------------------------------------


void __fastcall TfrmDetailBaseForm::ShowflowChartActionExecute(TObject *Sender)
{
  if(FTaskFlowUpdate)
	return;
  FTaskFlowUpdate=true;
  TStream* pcStream=NULL;
  if(WorkflowID>" ")
  {
	pcStream=ClientBroker->GetWorkFlowChart(WorkflowID,false);
  }
  else if( FlowDefinID>" ")
  {
	pcStream=ClientBroker->GetWorkFlowChart(FlowDefinID,true);
  }
  if(pcStream)
  {
	TBitmap *flowBitmap=new TBitmap(pcStream);
	try{
	 if(flowBitmap->Height>FlowScrollBox->Height)
	   FlowLayout->Height=flowBitmap->Height;
	 else
	   FlowLayout->Height=FlowScrollBox->Height;
	 if(flowBitmap->Width>FlowScrollBox->Width)
	   FlowLayout->Width=flowBitmap->Width;
	 else
	   FlowLayout->Width=FlowScrollBox->Height;
	 WorkflowImage->Height=flowBitmap->Height;
	 WorkflowImage->Width=flowBitmap->Width;
	 HWScale=double(flowBitmap->Height)/double(flowBitmap->Width);
	 WorkflowImage->Bitmap->Assign(flowBitmap);
	}
	__finally
	{
	 delete flowBitmap;
	 delete pcStream;
	}
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::tcDetailControlChange(TObject *Sender)
{
TTabItem * actTab=tcDetailControl->ActiveTab;
 if(actTab==tabOA) //��������
 {
   FillTask();
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::TaskStringGridRowChanged()
{
	TStream* dsStream=NULL;
//	if((TaskStringGrid->Selected>-1)&&(WorkflowID>""))
	if((WorkflowID>"")&&TaskQuery->Active)
	{
//	  TaskQuery->RecNo=TaskStringGrid->Selected+1;
	  String taskInsKey=TaskQuery->FieldByName("FlowMnDtlPKID")->AsString;
	  if(taskInsKey==TaskSelected) return;
	  TaskSelected= taskInsKey;
	   //Ӧ���ж��Ƿ��ǿ�������ˣ�����������أ����Ǻ�̨ʵ���жϼ򵥵�
	  bool canUpdate= ClientBroker->TaskCanUpdate(TaskSelected);
	  cbFlowMnDtlResults->Items->Clear();

	  TaskDefListDs->Close();
	  dsStream=ClientBroker->GetTaskdefListDS(TaskSelected);
	  TaskDefListDs->LoadFromStream(dsStream);
	  TaskDefListDs->First();
	  while(!TaskDefListDs->Eof)
	  {

		  bool IsHidden=TaskDefListDs->FieldByName("IsHidden")->AsInteger==1;
		  if(canUpdate&&IsHidden)
		  {
		  //ע��˳��
			TaskDefListDs->Next();
			continue;
		  }
		  cbFlowMnDtlResults->Items->Add(TaskDefListDs->FieldByName("Status")->AsString);
		  TaskDefListDs->Next();
		}
	  TaskDefListDs->Close();
	  delete dsStream;
	   //��λ����״̬
	  String taskResult=TaskQuery->FieldByName("FlowMnDtlResults")->AsString;
	  int itemIndex=cbFlowMnDtlResults->Items->IndexOf(taskResult);
	  cbFlowMnDtlResults->ItemIndex=itemIndex;
	  edFlowMnDtlComments->Enabled=canUpdate;
	  cbFlowMnDtlResults->Enabled=canUpdate;
	  OACheckAction->Enabled=canUpdate;
	  FTaskLogUpdate=false;
	  FTaskFlowUpdate=false;
	}
	else
	  TaskSelected="";
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::OAStareActionExecute(TObject *Sender)
{
  if((FlowDefinID>" ") && (WorkflowID<" "))   //��������
  {
   TWorkFlowStartData *AWorkFlowStartData=new TWorkFlowStartData;
   try{
	   AWorkFlowStartData->FlowDefID=FlowDefinID;
	   AWorkFlowStartData->Subject=edWorkflowTitle->Text;
	   AWorkFlowStartData->Content=mmWorkflowContent->Text;
	   AWorkFlowStartData->BusWindow=IntToStr(FormID);
	   AWorkFlowStartData->Rank=cbWorkflowLeve->ItemIndex;
	   if(FOnBeforWorkFlowStart) //ͨ���¼����Դ��ݱ�Ҫ����
		FOnBeforWorkFlowStart(AWorkFlowStartData);
	   else
		 throw Exception(L"Ҫ��ʵ���¼�OnBeforWorkFlowStart");
	   if(AWorkFlowStartData->Subject< " "||AWorkFlowStartData->BusWindow<="0" || AWorkFlowStartData->BusCode<" ")
		 throw Exception  (L"�������⣬����ID��ҵ�񵥾�ID������Ϊ��!");
		WorkflowID=ClientBroker->ServerWorkFlowStart(AWorkFlowStartData->FlowDefID,
		AWorkFlowStartData->Subject, AWorkFlowStartData->Content, AWorkFlowStartData->BusWindow,
		AWorkFlowStartData->BusCode,  AWorkFlowStartData->Rank,  AWorkFlowStartData->ProjectID,  AWorkFlowStartData->ReportID);
		if(WorkflowID>"")
		{
			if(FOnAfterWorkFlowStart) //ͨ���¼����Դ��ݱ�Ҫ����
				FOnAfterWorkFlowStart(WorkflowID);
			FillTask();//ˢ��һ������
			SetOptCtrlStatus(0);
		}
   }
   __finally
   {
		delete AWorkFlowStartData;
   }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FlowMnDtlRemarkBindLinkAssignedValue(TObject *Sender,
          TBindingAssignValueRec &AssignValueRec, const TValue &Value)
{
  TaskStringGridRowChanged();
}
//---------------------------------------------------------------------------


void __fastcall TfrmDetailBaseForm::CloseFormActionExecute(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::DetailEditActionExecute(TObject *Sender)
{
	EditData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::DetailEditActionUpdate(TObject *Sender)
{
  btEdit->Visible=DetailEditAction->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::SaveDetailActionUpdate(TObject *Sender)
{
  btSave->Visible=SaveDetailAction->Enabled;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::cbFlowMnDtlResultsClosePopup(TObject *Sender)

{
 if(edFlowMnDtlComments->Text.IsEmpty())
 {
   if(edFlowMnDtlComments->CanFocus)
   {
	  edFlowMnDtlComments->SetFocus();
	 edFlowMnDtlComments->Text=cbFlowMnDtlResults->Selected->Text;
   }
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::AddItemActionExecute(TObject *Sender)
{
	AddItemData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::DeleteItemActionExecute(TObject *Sender)
{
	  DelItemData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::BrowseItemActionExecute(TObject *Sender)
{
	  BrowseItemRecord();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDetailBaseForm::CalcContentBoundsProc(TObject * Sender, System::Types::TRectF &ContentBounds)
{
	if (FNeedOffset && FKBBounds.Top > 0) {
		ContentBounds.Bottom = Max(ContentBounds.Bottom, 2 * ClientHeight - FKBBounds.Top);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FormFocusChanged(TObject *Sender)
{
   	FKBBounds = TRectF(0,0,0,0);
	UpdateKBBounds();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKBBounds = TRectF(0,0,0,0);
	FNeedOffset = False;
	RestorePosition();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	FKBBounds = TRectF(Bounds);
	FKBBounds = TRectF(ScreenToClient(FKBBounds.TopLeft()),ScreenToClient(FKBBounds.BottomRight()));
	UpdateKBBounds();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::UpdateKBBounds()
{
	FNeedOffset = false;
	if (Focused != NULL) {
		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
		TRectF LFocusRect = LFocused->AbsoluteRect;
		LFocusRect.Offset(MainVertScrollBox->ViewportPosition.X, MainVertScrollBox->ViewportPosition.Y);
		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
			FNeedOffset = true;
			MainLayout->Align = TAlignLayout::Horizontal;
			MainVertScrollBox->RealignContent();
			Application->ProcessMessages();
			MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X,
				LFocusRect.Bottom - FKBBounds.Top);
		}
	}
	if (!FNeedOffset) {
		RestorePosition();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::RestorePosition()
{
	MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X, 0);
	MainLayout->Align = TAlignLayout::Client;
	MainVertScrollBox->RealignContent();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::FlowLayoutGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled)
{
	if (EventInfo.GestureID == static_cast<short>(igiZoom)) {
		IControl *LObj = this->ObjectAtPoint(ClientToScreen(EventInfo.Location));
		if (static_cast<TImage*>((TImage*)LObj)) {
			if (!EventInfo.Flags.Contains(TInteractiveGestureFlag::gfBegin) &&
				!EventInfo.Flags.Contains(TInteractiveGestureFlag::gfEnd)) {
				// zoom the image
				TImage * LImage = dynamic_cast<TImage*>(LObj->GetObject());
				if(LImage)//�ж��Ƿ���Ч����
				{
					int miniWidth= LImage->Width + (EventInfo.Distance - FLastDistance);
					int miniHeight=HWScale*miniWidth;//LImage->Height + (EventInfo.Distance - FLastDistance);
					if(miniWidth<100)    //������С�ߴ�
					{
					   miniWidth=100;
					   miniHeight=HWScale*miniWidth;
					}
					if(miniWidth>FlowScrollBox->Width)
					  FlowLayout->Width=miniWidth;
					 else
					  FlowLayout->Width=FlowScrollBox->Width;

					if(miniHeight>FlowScrollBox->Height)
					  FlowLayout->Height=miniHeight;
					 else
					  FlowLayout->Height=FlowScrollBox->Height;
					LImage->Width = miniWidth;
					LImage->Height = miniHeight;
					TPointF LImageCenter = FlowLayout->Position->Point + PointF(FlowLayout->Width / 2,
						FlowLayout->Height / 2);
					LImage->Position->X = LImageCenter.X - LImage->Width / 2;
					LImage->Position->Y = LImageCenter.Y - LImage->Height / 2;
			  }
			}
			FLastDistance = EventInfo.Distance;
		}
	}


}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::MoveNextActionExecute(TObject *Sender)
{
	if(MasterStatus!=dsBrowse || (DataSetType==2 && DetailStatus!=dsBrowse) || m_EditBill) //���ڱ༭״̬
	{
	  TMessageDialogEventProc MsgDialogCloseEvent=&DoCancelChange;
	  ShowMessageBox(L"�޸�δ���棬�Ƿ�ȷ��ȡ����",MsgDialogCloseEvent);
	}
	else
	if(!this->Eof)
	{
		FTaskLogUpdate=false;
		FTaskFlowUpdate=false;
		this->MoveNext();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::MovePriorActionExecute(TObject *Sender)
{
	if(MasterStatus!=dsBrowse || (DataSetType==2 && DetailStatus!=dsBrowse) || m_EditBill) //���ڱ༭״̬
	{
	  TMessageDialogEventProc MsgDialogCloseEvent=&DoCancelChange;
	  ShowMessageBox(L"�޸�δ���棬�Ƿ�ȷ��ȡ����",MsgDialogCloseEvent);
	}
	else
	if(!this->Bof)
	{
		FTaskLogUpdate=false;
		FTaskFlowUpdate=false;
		this->MovePrior();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDetailBaseForm::tcWorkflowControlChange(TObject *Sender)
{
  TTabItem * actTab=tcWorkflowControl->ActiveTab;
  if(actTab==tabTaskflow)
	{
	  ShowflowChartAction->Execute();
	}
	else if(actTab==tabTaskLog)
	{
	  FillTaskLog();
	}
}
//---------------------------------------------------------------------------

