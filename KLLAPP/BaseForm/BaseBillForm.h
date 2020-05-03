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
//  int FOperateRight;  //����Ȩ��
  int FOperateStatus; //�������״̬

  void __fastcall IniBaseBillForm();
  void __fastcall DoDelDataProc(System::Uitypes::TModalResult AResult);
  void __fastcall DoDelItemDataProc(System::Uitypes::TModalResult AResult);
  void __fastcall DoCheckBillProc(System::Uitypes::TModalResult AResult);
  void __fastcall DoUnCheckBillProc(System::Uitypes::TModalResult AResult);
protected:

  int m_InitStatus; //��ʼ״̬
  bool m_EditBill;  //�༭��ϸ״̬

  void __fastcall AddData();    //���Ӽ�¼�����������ӱ���ͷ��
  void __fastcall EditData();   //�༭��¼�����������ӱ���ͷ��
  void __fastcall DelData();    //ɾ����¼�����������ӱ���ͷ��
  void __fastcall SaveData();   //�����޸ģ����������ӱ���ͷ��
  void __fastcall CancelChange();  //ȡ���޸ģ����������ӱ���ͷ��
  void __fastcall CancelDetailChange();
  void __fastcall AddItemData();   //������ϸ�����ӱ���ϸ��
  void __fastcall EditItemData();  //�༭��ϸ�����ӱ���ϸ��
  void __fastcall SaveItemData(bool bAddAgain=true);  //������ϸ�����ӱ���ϸ����bAddAgain�Ƿ���������
  void __fastcall DelItemData();   //ɾ����ϸ�����ӱ���ϸ��

  void __fastcall RefreshData();   //ˢ�½�������
  void __fastcall RefreshDataSet();//ˢ�����ݼ�
  void __fastcall BrowseRecord();  //�����ϸ�༭��
  void __fastcall FindRecord();    //���ݼ���λ
  void __fastcall ClearMasterDataSet();   //���������¼
  void __fastcall ClearDetailDataSet();   //����ӱ���¼

  void __fastcall CheckBillData();   //��˵���
  void __fastcall UnCheckBillData(); //����˵���

  void __fastcall SetControlEnabled(int Section,int status);
  //���ƽ���ؼ�ʹ��״̬��Section��1-��ͷ�򵥱���2-��ϸ��Status��0-�����1-������2-�޸�
  void __fastcall LockControl(int Section,TControl *ctl,bool browse,bool add,bool edit,int LockType=0);
  //���ý���ؼ�ʹ��״̬��Section��1-��ͷ�򵥱���2-��ϸ��ctl���ؼ�ָ�룻browse��add��edit��true-��ʹ�ã�false-����ʹ�ã�locatype 0-��Enable���ԣ�1-��readonly����
  void __fastcall SetControlFocus(int Section);
  //���ƽ���ؼ������뽹�㣬Section��1-��ͷ�򵥱���2-��ϸ
  void __fastcall WaitInputControl(int Section,TControl *winctl);
  //���ý���ؼ������뽹�㣬Section��1-��ͷ�򵥱���2-��ϸ��winctl����ȡ����Ŀؼ�ָ��

  bool ValidKeyStr(String KeyStr); //�ж��ַ����Ƿ���зǷ��ַ�
  bool __fastcall KeyFieldsValid(int Section);  //�ؼ��ֶμ���,1-��ͷ��2����ϸ
  void __fastcall DoCancelChange(System::Uitypes::TModalResult AResult);
protected: //virtual function

  virtual void __fastcall SetOptCtrlStatus(int status){};//���ƽ��湦�ܰ�ť��ʹ��״̬��status��0-�����1-��ͷ�򵥱�������2-��ͷ�򵥱��޸ģ�3-��ϸ������4-��ϸ�޸�
  virtual void __fastcall FormFillData(){};   //����б�����ͼ
  virtual void __fastcall FormAppendData(){}; //��������
  virtual void __fastcall FormInsertData(){}; //��������
  virtual void __fastcall FormDeleteData(){}; //ɾ������
  virtual void __fastcall FormChangeData(){}; //�޸�����
  virtual bool __fastcall FormLocateControl(){return false;}; //��λ��������
  virtual void __fastcall FormInitControl(){};   //��ʼ�����ݿؼ�
  virtual void __fastcall FormClearControl(int Section){};   //��տؼ����ݣ�Section��1-��ͷ�򵥱���2-��ϸ
  virtual void __fastcall SendDataToDataSet(int Section){};  //�ؼ����ݴ������ݼ���Section��1-��ͷ�򵥱���2-��ϸ
  virtual void __fastcall GetDataFromDataSet(int Section){}; //���ݼ�������ʾ�ڿؼ��У�Section��1-��ͷ�򵥱���2-��ϸ
  virtual void __fastcall VerifyFieldData(int Section,int status){}; //����ǰУ�����ݣ�Section��1-��ͷ�򵥱���2-��ϸ��status��1-������2-�޸�
  virtual void __fastcall ChangeToBrowseState(bool Browse){}; //ת����ϸ����ʾ��ʽ��Browse��true-��ϸ���������ʽ��false-�༭��ʽ
  virtual void __fastcall BeforeInputData(int Section){};   //��������֮ǰ�Ĵ�����Section��1-��ͷ�򵥱���2-��ϸ
  virtual int __fastcall GetCheckStatus(){return 0;}; //��ȡ��˱�־

  virtual bool __fastcall BeforeUpdateData(int OptType){return true;}
  //OptType����ο�BaseForm.h��EOperateTypeö������

  //���º�������ʵ�ֵ��ݵ����
  virtual bool __fastcall BeforeCheck();  //���ǰ����
  virtual void __fastcall AfterCheck();   //��˺���
  virtual void __fastcall CheckBill();    //���
  virtual bool __fastcall BeforeUnCheck();//�����ǰ����
  virtual void __fastcall AfterUnCheck(); //����˺���
  virtual void __fastcall UnCheckBill();  //�����


  //���º�������ʵ����ϸ�༭����,���༭�����ٴ򿪱༭����
  virtual void __fastcall AppendDetailData(){}; //��ϸ��������
  virtual void __fastcall InsertDetailData(){}; //��ϸ��������
  virtual void __fastcall DeleteDetailData(){}; //��ϸɾ������
  virtual void __fastcall ChangeDetailData(){}; //��ϸ��������
  virtual void __fastcall CustomOperate(){};     //�Զ������
  virtual bool __fastcall LocateDetailData(){return false;};     //��ϸ��λ����
  virtual void __fastcall ShowItemEditForm(int status);//��ʾ��������ϸ�༭����
  virtual TForm * __fastcall NewItemEditForm(TZClientDataSet *m_DataSet, int status);//������������ϸ����
public: //public property and function

//  __property int OperateRight = { read=FOperateRight, write=FOperateRight };
//  //�������Ȩ�� 0��ֻ����1����ӡ��2����д��3�����
  __property int OperateStatus = { read=FOperateStatus, write=FOperateStatus };
  //�������״̬ 0�������1�����ӵ��ݣ�2���޸ĵ��ݣ�3��������ϸ��4���޸���ϸ��5���༭����

  void __fastcall Open();          //�����ݼ�
  void __fastcall CloseDataSet();  //�ر����ݼ�
  void __fastcall MoveFirst();     //����������¼
  void __fastcall MoveLast();      //����ĩ����¼
  void __fastcall MoveNext();      //����������¼
  void __fastcall MovePrior();     //����������¼
  void __fastcall MoveTo(int Distance);  //�ƶ���¼
  void __fastcall DisplayMaster(); //��ʾ��������

  void __fastcall DetailFirst();    //����������ϸ
  void __fastcall DetailLast();     //����ĩ����ϸ
  void __fastcall DetailPrior();    //����������ϸ
  void __fastcall DetailNext();     //����������ϸ
  void __fastcall DetailMoveTo(int Distance); //�ƶ���ϸ
  void __fastcall DisplayDetail();  //��ʾ�ӱ�����

  bool __fastcall LocateMaster(String KeyValues);        //��λ��¼
  bool __fastcall LocateDetail(String KeyValues);        //��λ��ϸ
  Variant __fastcall GetMasterValue(String fieldname);   //ȡ��ͷ�ֶ�ֵ
  Variant __fastcall GetMasterOldValue(String fieldname);//ȡ��ͷ�ֶ�ԭֵ
  void __fastcall SetMasterValue(String fieldname,Variant value); //���ͷ�ֶ�ֵ
  Variant __fastcall GetDetailValue(String fieldname);   //ȡ��ϸ�ֶ�ֵ
  Variant __fastcall GetDetailOldValue(String fieldname);//ȡ��ϸ�ֶ�ԭֵ
  void __fastcall SetDetailValue(String fieldname,Variant value); //����ϸ�ֶ�ֵ
  Variant __fastcall GetFieldValue(String fieldname);    //ȡ�����ֶ�ֵ
  Variant __fastcall GetFieldOldValue(String fieldname); //ȡ�����ֶ�ԭֵ
  void __fastcall SetFieldValue(String fieldname,Variant value);  //�浥���ֶ�ֵ
  TField *__fastcall FindMasterField(String fieldname);   //���ұ�ͷ�򵥱��ֶ�
  TField *__fastcall FindDetailField(String fieldname);   //������ϸ�ֶ�

  void __fastcall SetFormStatus(int status);      //���ô����ʼ״̬,StatusΪ���ݼ���ʼ״̬��0-�����1-������ͷ����ϸ��2-�޸ı�ͷ����ϸ

public: // constructor and destructor
	__fastcall TfrmBaseBillForm(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,String Param);
	__fastcall TfrmBaseBillForm(TComponent* Owner,TClientBroker * clBroker,int ModuleCode,TZClientDataSet *FDataSet,String Param);
	__fastcall ~TfrmBaseBillForm();

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBaseBillForm *frmBaseBillForm;
//---------------------------------------------------------------------------
#endif