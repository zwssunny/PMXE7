//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "WorkFlowDetailForm.h"
#include "FSTMessageDlg.h"
#include "NotPassTextForm.h"
#include "NotPassMethod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseBillForm"
#pragma resource "*.fmx"
TfrmWorkFlowDetailForm *frmWorkFlowDetailForm;
//---------------------------------------------------------------------------
__fastcall TfrmWorkFlowDetailForm::TfrmWorkFlowDetailForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param)
	: TfrmBaseBillForm(Owner,clBroker,modulecode,param)
{
	FCommitUrl = "";
	FNotPassUrl = "";
	FNeedRefresh = false;
}
//---------------------------------------------------------------------------
__fastcall TfrmWorkFlowDetailForm::TfrmWorkFlowDetailForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,TClientDataSet *m_DataSet,String param)
	: TfrmBaseBillForm(Owner,clBroker,modulecode,m_DataSet,param)
{
	FCommitUrl = "";
	FNotPassUrl = "";
	FNeedRefresh = false;
}
//---------------------------------------------------------------------------
TRESTRequestParameterList* __fastcall TfrmWorkFlowDetailForm::GetCommitParam()
{
	return new TRESTRequestParameterList(this);
}
//---------------------------------------------------------------------------
TRESTRequestParameterList* __fastcall TfrmWorkFlowDetailForm::GetNotPassParam(String reason)
{
	return new TRESTRequestParameterList(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkFlowDetailForm::Commit(System::Uitypes::TModalResult AResult)
{
	if(AResult==mrYes)
	{
		if(!FCommitUrl.IsEmpty())
		{
			TClientDataSet *Result = PostData(FCommitUrl,GetCommitParam());
			AfterCommit(Result);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkFlowDetailForm::NotPass(String reason)
{
	TClientDataSet *Result = PostData(FNotPassUrl,GetNotPassParam(reason));
	AfterNotPass(Result);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkFlowDetailForm::BtnCommitClick(TObject *Sender)
{
	TMessageDialogEventProc msgDialogCloseProc=&Commit;
	FSTMessageDlg(_D("确认要将当前业务提交审核吗，你将不能再更改表单内容！") ,TMsgDlgType::mtConfirmation,mbYesNo,0,msgDialogCloseProc);
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorkFlowDetailForm::BtnNotPassClick(TObject *Sender)
{
    if(!FNotPassUrl.IsEmpty())
	{
		TfrmNotPassTextForm *p = new TfrmNotPassTextForm(this);
		TNotPassMethodReference  *Lm=new TNotPassMethodReference;
		Lm->dlg=p;
		Lm->OwerForm=this;
		p->ShowModal(Lm);
	}
}
//---------------------------------------------------------------------------
