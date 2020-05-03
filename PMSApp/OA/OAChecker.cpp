//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "OAChecker.h"
#include "ShowBizEditForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseListForm"
#pragma link "StartAndEndDate"
#pragma resource "*.fmx"
TfrmOAChecker *frmOAChecker;
//---------------------------------------------------------------------------
__fastcall TfrmOAChecker::TfrmOAChecker(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param)
	: TfrmBaseListForm(Owner,clBroker,ModuleCode,Param)
{
	 TaskSelected="";
	 FOnBeforWorkFlowExec=NULL;
	 TaskQuery=new TZClientQuery(this,clBroker);
	 TaskLogQuery=new TZClientQuery(this,clBroker);
	 TaskDefListDs=new TClientDataSet(this);
	 lbWorkTitleText->Text="  ";
	 lbTaskTitleText->Text="  ";
	 lbCreatorName->Text="  ";
	 FillBillTypeItems();
	 CheckAction->Enabled=false;
	 FlowChartUpdate=true;
	 TaskLogUpdate=true;
	 HWScale=1;
	 FLastDistance = 0;
}
//---------------------------------------------------------------------------
__fastcall TfrmOAChecker::~TfrmOAChecker()
{
	 delete TaskQuery;
	 delete TaskLogQuery;
	 delete TaskDefListDs;
}
void __fastcall TfrmOAChecker::SetOptCtrlStatus(int status)
{

}
//---------------------------------------------------------------------------
void __fastcall TfrmOAChecker::FillBillTypeItems()
{
  Query->Close();
  Query->SQL->Text="select * from SyWorkBiz";
  Query->SysOpen();
  cbBillType->Clear();
  //加入第一个节点
  TListBoxItem * newBoxItem=new TListBoxItem(cbBillType);
  newBoxItem->Text=L"所有业务";
  newBoxItem->TagString="0"; //窗体编号
  newBoxItem->TagFloat=0;
  cbBillType->AddObject(newBoxItem);
  while(!Query->Eof)
  {
	  TListBoxItem * newBoxItem=new TListBoxItem(cbBillType);
	  newBoxItem->Text=Query->FieldByName("BizName")->AsString;  //菜单标题
	  newBoxItem->TagString=Query->FieldByName("BizFormID")->AsString; //窗体编号
	  newBoxItem->TagFloat=Query->FieldByName("BizMenuID")->AsInteger; //菜单ID
	  cbBillType->AddObject(newBoxItem);
	  Query->Next();
  }
  Query->Close();
  if(cbBillType->Count>0)
	 cbBillType->ItemIndex=0;
}
String __fastcall TfrmOAChecker::GetOtherConditon()
{
	String FWhereStr = "  convert(varchar(10),FlowMnDtlSendTime)>='"+StartAndEndDateFrame1->BeginDate
					  +"' and convert(varchar(10),FlowMnDtlSendTime)<='"+StartAndEndDateFrame1->EndDate+"' " ;
	if(cbBillType->ItemIndex>0)
	{
	 FWhereStr = FWhereStr + " and FlowMnDtlFKID in (select FlowMnPKID from tbFlowMain where FlowMnBusWindow ="+QuotedStr(cbBillType->Selected->TagString)+")";
    }
	if(edBillTitle->Text.Trim() > "")
		FWhereStr = FWhereStr + " and FlowMnDtlFKID in (select FlowMnPKID from tbFlowMain where FlowMnSubject like '%"+edBillTitle->Text.Trim()+"%' )";
   return FWhereStr;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOAChecker::LoadTaskData()
{

 TStream* dsStream=NULL;
 dsStream=ClientBroker->GetTaskListDS(ClientBroker->UserEmpID,cbTaskStatus->ItemIndex,GetOtherConditon());
 if(dsStream)
 {
	 TaskBindGridLink->Active=false;
	 TaskQuery->Close();
	 TaskQuery->LoadFromStream(dsStream);
	 TaskBindSourceDB->DataSet=TaskQuery;
	 TaskBindGridLink->Active=true;
	 delete dsStream;
//	 if(TaskQuery->RecordCount>0)
//	 {
//		 TaskStringGrid->Selected=TaskQuery->RecordCount-1;
//		 TaskStringGridSelectedRowChanged(NULL);
//	 }
 }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOAChecker::LoadTaskLogData()
{
  if(TaskLogUpdate) return;
  TaskLogUpdate=true;
  TaskLogBindGridLink->Active=false;
  TaskLogQuery->Close();
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
void __fastcall TfrmOAChecker::ShowFlowChart()
{
   TStream* pcStream=NULL;
   if(FlowChartUpdate) return;
   FlowChartUpdate=true;
  if(WorkflowID>" ")
  {
	pcStream=ClientBroker->GetWorkFlowChart(WorkflowID,false);
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
void __fastcall TfrmOAChecker::tcTaskControlChange(TObject *Sender)
{
  if(tcTaskControl->ActiveTab==tabTaskLog)
  {
	LoadTaskLogData();
  }
  else if (tcTaskControl->ActiveTab==tabflowChart)
  {
    ShowFlowChart();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::SearchActionExecute(TObject *Sender)
{
	tcOAControl->ActiveTab=tabSearch;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::SearchOkActionExecute(TObject *Sender)
{
  LoadTaskData();
  tcOAControl->ActiveTab=tabTask;
}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::CheckActionExecute(TObject *Sender)
{
	if(WorkflowID>" ")
	{
		String taskInsKey=TaskQuery->FieldByName("FlowMnDtlPKID")->AsString;
		String TaskdefResults=cbFlowMnDtlResults->Items->Strings[cbFlowMnDtlResults->ItemIndex];
		TStringList* VariableList=new TStringList;   //通过下面事件传入变量列表。
		TClientDataSet *varDataSet=new TClientDataSet(this);
		TStream *dsStream=ClientBroker->GetVariableListDS(taskInsKey);
		varDataSet->LoadFromStream(dsStream);
		//触发事件
		TWorkFlowExecData *AWorkFlowExecData=new TWorkFlowExecData;
		AWorkFlowExecData->FlowDefID=FlowDefinID;
		AWorkFlowExecData->WorkInsID=WorkflowID;
		AWorkFlowExecData->TaskInsID=taskInsKey;
		AWorkFlowExecData->TskStatus=TaskdefResults;
		AWorkFlowExecData->TskComments=edFlowMnDtlComments->Text;
		if(FOnBeforWorkFlowExec) FOnBeforWorkFlowExec(AWorkFlowExecData, varDataSet);
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
		delete varDataSet;
		bool ckOk=ClientBroker->ServerWorkFlowExec(FlowDefinID, WorkflowID, taskInsKey, TaskdefResults, edFlowMnDtlComments->Text,varJsonArray);
		if(ckOk)//审核成功，刷新数据
		  LoadTaskData();
		delete AWorkFlowExecData;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::btCloseClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::TaskStringGridSelectedRowChanged()
{
	TStream* dsStream=NULL;
//	if((TaskStringGrid->Selected>-1)&&(TaskQuery->Active))
	if(TaskQuery->Active)
	{
	 // TaskQuery->RecNo=TaskStringGrid->Selected+1;
//	  Label1->Text=TaskStringGrid->Selected;
//	  Label2->Text=TaskQuery->RecNo;
	  String taskInsKey=TaskQuery->FieldByName("FlowMnDtlPKID")->AsString;
	  if(taskInsKey==TaskSelected) return;
	  TaskSelected= taskInsKey;

	  String WorkInsKey=TaskQuery->FieldByName("FlowMnDtlFKID")->AsString;
	   //应该判断是否是可以审核人，如果是则隐藏，考虑后台实现判断简单点
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
		  //注意顺序
			TaskDefListDs->Next();
			continue;
		  }
		  cbFlowMnDtlResults->Items->Add(TaskDefListDs->FieldByName("Status")->AsString);
		  TaskDefListDs->Next();
		}
	  TaskDefListDs->Close();
	  delete dsStream;
	   //定位任务状态
	  String taskResult=TaskQuery->FieldByName("FlowMnDtlResults")->AsString;
	  int itemIndex=cbFlowMnDtlResults->Items->IndexOf(taskResult);
	  cbFlowMnDtlResults->ItemIndex=itemIndex;
	  //更新控件
	  CheckAction->Enabled=canUpdate;
	  edFlowMnDtlComments->Enabled=canUpdate;
	  cbFlowMnDtlResults->Enabled=canUpdate;
	  if(WorkflowID!=WorkInsKey)
	  {
	   WorkflowID=WorkInsKey;
		FlowChartUpdate=false;
		TaskLogUpdate=false;
	   tcTaskControlChange(NULL);
	  }
	}
	else
	{
	  TaskSelected="";
	  WorkflowID="";
	  WorkflowImage->Bitmap->Clear(System::Uitypes::TAlphaColor(claWhite));
	  CheckAction->Enabled=false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::btBackClick(TObject *Sender)
{
  tcOAControl->ActiveTab=tabTask;
}
//---------------------------------------------------------------------------


void __fastcall TfrmOAChecker::TaskTitleTextBindLinkAssignedValue(TObject *Sender,
          TBindingAssignValueRec &AssignValueRec, const TValue &Value)
{
  TaskStringGridSelectedRowChanged();
}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::cbFlowMnDtlResultsClosePopup(TObject *Sender)
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

void __fastcall TfrmOAChecker::OpenbillActionExecute(TObject *Sender)
{
	if((TaskQuery->Active)&&(TaskQuery->RecordCount>0))
	{
		String BizType=TaskQuery->FieldByName("FlowMnBusWindow")->AsString;
		String BizCode=TaskQuery->FieldByName("FlowMnBusCode")->AsString;
		int BizMenuID;
//		Query->Close();
//		Query->SQL->Text="select * from SyWorkBiz where BizFormID="+QuotedStr(BizType);
//		Query->SysOpen();
//		if(Query->RecordCount>0)
//		 BizMenuID=Query->FieldByName("BizMenuID")->AsInteger;
//减少服务器交互
	   for(int i=0;i<cbBillType->Count;i++)
	   {
		 TListBoxItem * newBoxItem=cbBillType->ListItems[i];
		 if(newBoxItem->TagString==BizType)
		 {
		   BizMenuID=newBoxItem->TagFloat;
		   break;
         }
       }
	   //	ShowMessage(L"菜单编码："+BizMenuID+L" 单据ID:"+BizCode);
	  TForm* form= ShowBizEditForm(this, BizMenuID,BizCode);
	  if(form)
	   form->Show();
	  else
	    ShowMessage(L"OA调用窗体未实现，菜单号:"+IntToStr(BizMenuID)+L"请在文件ShowBizEditForm中定义");
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmOAChecker::FlowLayoutGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled)
{
 	if (EventInfo.GestureID == static_cast<short>(igiZoom)) {
		IControl *LObj = this->ObjectAtPoint(ClientToScreen(EventInfo.Location));
		if (static_cast<TImage*>((TImage*)LObj)) {
			if (!EventInfo.Flags.Contains(TInteractiveGestureFlag::gfBegin) &&
				!EventInfo.Flags.Contains(TInteractiveGestureFlag::gfEnd)) {
				// zoom the image
				TImage * LImage = dynamic_cast<TImage*>(LObj->GetObject());
				if(LImage)//判断是否有效对象
				{
					int miniWidth= LImage->Width + (EventInfo.Distance - FLastDistance);
					int miniHeight=HWScale*miniWidth;//LImage->Height + (EventInfo.Distance - FLastDistance);
					if(miniWidth<100)    //控制最小尺寸
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




