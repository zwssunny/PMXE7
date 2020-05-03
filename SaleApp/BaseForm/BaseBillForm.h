//---------------------------------------------------------------------------

#ifndef BaseBillFormH
#define BaseBillFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseForm.h"
//---------------------------------------------------------------------------
class PACKAGE TfrmBaseBillForm : public TfrmBaseForm
{
__published:	// IDE-managed Components

  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
  TCZDataSet *m_LockControls;
  TCZDataSet *m_WaitInputControls;
//  int FOperateRight;  //窗体权限
  int FOperateStatus; //窗体操作状态

  void __fastcall IniBaseBillForm();
  void __fastcall DoDelDataProc(System::Uitypes::TModalResult AResult);
  void __fastcall DoDelItemDataProc(System::Uitypes::TModalResult AResult);
  void __fastcall DoCheckBillProc(System::Uitypes::TModalResult AResult);
  void __fastcall DoUnCheckBillProc(System::Uitypes::TModalResult AResult);
protected:

  int m_InitStatus; //初始状态
  bool m_EditBill;  //编辑明细状态

  void __fastcall AddData();    //增加记录（单表或主从表表头）
  void __fastcall EditData();   //编辑记录（单表或主从表表头）
  void __fastcall DelData();    //删除记录（单表或主从表表头）
  void __fastcall SaveData();   //保存修改（单表或主从表表头）
  void __fastcall CancelChange();  //取消修改（单表或主从表表头）
  void __fastcall CancelDetailChange();
  void __fastcall AddItemData();   //增加明细（主从表明细）
  void __fastcall EditItemData();  //编辑明细（主从表明细）
  void __fastcall SaveItemData(bool bAddAgain=true);  //保存明细（主从表明细），bAddAgain是否连续新增
  void __fastcall DelItemData();   //删除明细（主从表明细）

  void __fastcall RefreshData();   //刷新界面数据
  void __fastcall RefreshDataSet();//刷新数据集
  void __fastcall BrowseRecord();  //浏览明细编辑区
  void __fastcall FindRecord();    //数据集定位
  void __fastcall ClearMasterDataSet();   //清除主表记录
  void __fastcall ClearDetailDataSet();   //清除从表记录

  void __fastcall CheckBillData();   //审核单据
  void __fastcall UnCheckBillData(); //反审核单据

  void __fastcall SetControlEnabled(int Section,int status);
  //控制界面控件使用状态，Section：1-表头或单表，2-明细；Status：0-浏览，1-新增，2-修改
  void __fastcall LockControl(int Section,TControl *ctl,bool browse,bool add,bool edit,int LockType=0);
  //设置界面控件使用状态，Section：1-表头或单表，2-明细；ctl：控件指针；browse、add、edit：true-可使用，false-不可使用，locatype 0-锁Enable属性，1-锁readonly属性
  void __fastcall SetControlFocus(int Section);
  //控制界面控件的输入焦点，Section：1-表头或单表，2-明细
  void __fastcall WaitInputControl(int Section,TControl *winctl);
  //设置界面控件的输入焦点，Section：1-表头或单表，2-明细；winctl：获取焦点的控件指针

  bool ValidKeyStr(String KeyStr); //判断字符串是否带有非法字符
  bool __fastcall KeyFieldsValid(int Section);  //关键字段检验,1-单头，2－明细
  void __fastcall DoCancelChange(System::Uitypes::TModalResult AResult);
protected: //virtual function

  virtual void __fastcall SetOptCtrlStatus(int status){};//控制界面功能按钮的使用状态，status：0-浏览，1-表头或单表新增，2-表头或单表修改，3-明细新增，4-明细修改
  virtual void __fastcall FormFillData(){};   //填充列表或树图
  virtual void __fastcall FormAppendData(){}; //增加数据
  virtual void __fastcall FormInsertData(){}; //插入数据
  virtual void __fastcall FormDeleteData(){}; //删除数据
  virtual void __fastcall FormChangeData(){}; //修改数据
  virtual bool __fastcall FormLocateControl(){return false;}; //定位界面数据
  virtual void __fastcall FormInitControl(){};   //初始化数据控件
  virtual void __fastcall FormClearControl(int Section){};   //清空控件数据，Section：1-表头或单表，2-明细
  virtual void __fastcall SendDataToDataSet(int Section){};  //控件数据存入数据集，Section：1-表头或单表，2-明细
  virtual void __fastcall GetDataFromDataSet(int Section){}; //数据集数据显示在控件中，Section：1-表头或单表，2-明细
  virtual void __fastcall VerifyFieldData(int Section,int status){}; //保存前校验数据，Section：1-表头或单表，2-明细，status：1-新增，2-修改
  virtual void __fastcall ChangeToBrowseState(bool Browse){}; //转换明细的显示方式，Browse：true-明细处于浏览方式，false-编辑方式
  virtual void __fastcall BeforeInputData(int Section){};   //输入数据之前的处理，Section：1-表头或单表，2-明细
  virtual int __fastcall GetCheckStatus(){return 0;}; //获取审核标志

  virtual bool __fastcall BeforeUpdateData(int OptType){return true;}
  //OptType：请参考BaseForm.h的EOperateType枚举类型

  //以下函数用于实现单据的审核
  virtual bool __fastcall BeforeCheck();  //审核前处理
  virtual void __fastcall AfterCheck();   //审核后处理
  virtual void __fastcall CheckBill();    //审核
  virtual bool __fastcall BeforeUnCheck();//反审核前处理
  virtual void __fastcall AfterUnCheck(); //反审核后处理
  virtual void __fastcall UnCheckBill();  //反审核


  //以下函数用于实现明细编辑功能,即编辑窗体再打开编辑窗体
  virtual void __fastcall AppendDetailData(){}; //明细增加数据
  virtual void __fastcall InsertDetailData(){}; //明细插入数据
  virtual void __fastcall DeleteDetailData(){}; //明细删除数据
  virtual void __fastcall ChangeDetailData(){}; //明细更新数据
  virtual void __fastcall CustomOperate(){};     //自定义操作
  virtual bool __fastcall LocateDetailData(){return false;};     //明细定位数据
  virtual void __fastcall ShowItemEditForm(int status);//显示并设置明细编辑窗体
  virtual TForm * __fastcall NewItemEditForm(TZClientDataSet *m_DataSet, int status);//创建并返回明细窗体
public: //public property and function

//  __property int OperateRight = { read=FOperateRight, write=FOperateRight };
//  //窗体操作权限 0－只读，1－打印，2－读写，3－审核
  __property int OperateStatus = { read=FOperateStatus, write=FOperateStatus };
  //窗体操作状态 0－浏览，1－增加单据，2－修改单据，3－增加明细，4－修改明细，5－编辑单据

  void __fastcall Open();          //打开数据集
  void __fastcall CloseDataSet();  //关闭数据集
  void __fastcall MoveFirst();     //移至首条记录
  void __fastcall MoveLast();      //移至末条记录
  void __fastcall MoveNext();      //移至下条记录
  void __fastcall MovePrior();     //移至上条记录
  void __fastcall MoveTo(int Distance);  //移动记录
  void __fastcall DisplayMaster(); //显示主表数据

  void __fastcall DetailFirst();    //移至首条明细
  void __fastcall DetailLast();     //移至末条明细
  void __fastcall DetailPrior();    //移至上条明细
  void __fastcall DetailNext();     //移至下条明细
  void __fastcall DetailMoveTo(int Distance); //移动明细
  void __fastcall DisplayDetail();  //显示从表数据

  bool __fastcall LocateMaster(String KeyValues);        //定位记录
  bool __fastcall LocateDetail(String KeyValues);        //定位明细
  Variant __fastcall GetMasterValue(String fieldname);   //取表头字段值
  Variant __fastcall GetMasterOldValue(String fieldname);//取表头字段原值
  void __fastcall SetMasterValue(String fieldname,Variant value); //存表头字段值
  Variant __fastcall GetDetailValue(String fieldname);   //取明细字段值
  Variant __fastcall GetDetailOldValue(String fieldname);//取明细字段原值
  void __fastcall SetDetailValue(String fieldname,Variant value); //存明细字段值
  Variant __fastcall GetFieldValue(String fieldname);    //取单表字段值
  Variant __fastcall GetFieldOldValue(String fieldname); //取单表字段原值
  void __fastcall SetFieldValue(String fieldname,Variant value);  //存单表字段值
  TField *__fastcall FindMasterField(String fieldname);   //查找表头或单表字段
  TField *__fastcall FindDetailField(String fieldname);   //查找明细字段

  void __fastcall SetFormStatus(int status);      //设置窗体初始状态,Status为数据集初始状态，0-浏览，1-新增表头或明细，2-修改表头或明细

public: // constructor and destructor
	__fastcall TfrmBaseBillForm(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param);
	__fastcall TfrmBaseBillForm(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet *FDataSet,String Param);
	__fastcall ~TfrmBaseBillForm();

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBaseBillForm *frmBaseBillForm;
//---------------------------------------------------------------------------
#endif
