//---------------------------------------------------------------------------

#ifndef WorkReportItemEditH
#define WorkReportItemEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "ItemBaseForm.h"
#include <FMX.ActnList.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Actions.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.SpinBox.hpp>
//---------------------------------------------------------------------------
class TfrmWorkReportItemEdit : public TfrmItemBaseForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label5;
	TEdit *edWorkDetailDataTime;
	TEdit *edWorkDetailProssState;
	TEdit *edWorkDetailNextContent;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TMemo *mmWorkDetailContent;
	TSpinBox *spWorkDetailScore;
	TSpinBox *spWorkDetailRate;
	TSpinBox *spWorkDetailIndex;
private:	// User declarations
   int FCheckFlag;
   String FGuidBillID,FDetailID;
   void __fastcall FormInitControl();   //初始化数据控件
   void __fastcall FormClearControl(int Section);   //清空控件数据
   void __fastcall SendDataToDataSet(int Section);  //控件数据存入数据集
   void __fastcall GetDataFromDataSet(int Section); //数据集数据显示在控件中
   void __fastcall VerifyFieldData(int Section,int status); //保存前校验数据，status：1-新增，2-修改
   void __fastcall SetUserCtrlStatus();//设置用户构件状态
void __fastcall DetailDataSetBeforePost(TDataSet* DataSet);
public:		// User declarations
	__fastcall TfrmWorkReportItemEdit(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet *FDataSet,int DataSetStatus);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorkReportItemEdit *frmWorkReportItemEdit;
//---------------------------------------------------------------------------
#endif
