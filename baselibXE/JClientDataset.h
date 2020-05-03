// ---------------------------------------------------------------------------

#ifndef JClientDatasetH
#define JClientDatasetH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <adodb.hpp>
#include <db.hpp>
#include <ScktComp.hpp>
#include <stdio.h>
#include <deque>
#include "BaseFunc.h"
#include "ClientBroker.h"
#include "JClientQuery.h"
// ---------------------------------------------------------------------------
class PACKAGE TJServerDataSetClient;
class PACKAGE TJClientQuery;

class PACKAGE TJClientDataSet
{
	private:
  //		HWND m_Handle;
//		HWND m_AOwner;
//		HWND m_Parent;
		TClientBroker *FClientBroker;
		TJServerDataSetClient *ServerDataSet;
		TADODataSet *m_MasterDataSet;
		TADODataSet *m_DetailDataSet;
		TADODataSet *FQuery;

		TJClientQuery *m_Query;
		String m_ServerDataSetHandle;
		String m_ClassCode;
		bool m_DataSetActive;
		int m_TimeOut;
		int m_ExecuteTime;
		FILE *logfile;

		int m_DataSetType;
		String m_MasterSQLString;
		String m_DetailSQLString;
		String m_MasterWhereString;
		String m_DetailWhereString;
		String m_MasterOrderString;
		String m_DetailOrderString;
		String m_MasterGroupString;
		String m_DetailGroupString;
		TStringList *m_MasterLinkFields;
		TStringList *m_DetailLinkFields;
		String m_MasterKeyFields;
		String m_DetailKeyFields;

		TADODataSet *m_MasterStructure;
		TADODataSet *m_DetailStructure;

		TStringList *m_DetailEditStatus;
		TStringList *m_MasterDisplayName;
		TStringList *m_DetailDisplayName;
		TStringList *m_MasterDisplayField;
		TStringList *m_DetailDisplayField;

		TStringList *m_MasterFilterFields;
		TStringList *m_DetailFilterFields;
		TStringList *m_MasterFieldAttr;
		TStringList *m_DetailFieldAttr;
		TStringList *m_MasterFieldExpr;
		TStringList *m_DetailFieldExpr;
		TStringList *m_MasterAttrType;
		TStringList *m_DetailAttrType;
		TStringList *m_DtlRecStatus;

		bool m_NeedValid;
		String m_MasterValidFieldList;
		String m_DetailValidFieldList;
//		bool ClientCommConnectState;

		int ZDataSetOperateStatus;
		String ZDataSetErrorMessage;

		String m_MasterFixedWhereString;
		String m_MasterFixedOrderString;
		String m_MasterFixedGroupString;
		String m_DetailFixedWhereString;
		String m_DetailFixedOrderString;
		String m_DetailFixedGroupString;
		TDataSetNotifyEvent FClientDataSetAfterScroll;

		String __fastcall get_MasterSQLString();
		void __fastcall set_MasterSQLString(String value);
		String __fastcall get_DetailSQLString();
		void __fastcall set_DetailSQLString(String value);
		String __fastcall get_MasterWhereString();
		void __fastcall set_MasterWhereString(String value);
		String __fastcall get_DetailWhereString();
		void __fastcall set_DetailWhereString(String value);
		String __fastcall get_MasterOrderString();
		void __fastcall set_MasterOrderString(String value);
		String __fastcall get_DetailOrderString();
		void __fastcall set_DetailOrderString(String value);
		String __fastcall get_MasterGroupString();
		void __fastcall set_MasterGroupString(String value);
		String __fastcall get_DetailGroupString();
		void __fastcall set_DetailGroupString(String value);
		String __fastcall get_MasterKeyFields();
		void __fastcall set_MasterKeyFields(String value);
		String __fastcall get_DetailKeyFields();
		void __fastcall set_DetailKeyFields(String value);
		String __fastcall get_LinkFields();
		void __fastcall set_LinkFields(String value);
		String __fastcall get_MasterSort();
		void __fastcall set_MasterSort(String value);
		String __fastcall get_DetailSort();
		void __fastcall set_DetailSort(String value);
		String __fastcall get_Filter();
		void __fastcall set_Filter(String value);
		bool __fastcall get_Filtered();
		void __fastcall set_Filtered(bool value);
		TDataSetState __fastcall get_MasterStatus();
		TDataSetState __fastcall get_DetailStatus();
		int __fastcall get_DataSetType();
		bool __fastcall get_Bof();
		bool __fastcall get_Eof();
		int __fastcall get_RecordCount();
		int __fastcall get_CurRecNo();
		int __fastcall get_MasterFieldCount();
		TFields *__fastcall get_MasterFields();
		bool __fastcall get_DetailBof();
		bool __fastcall get_DetailEof();
		int __fastcall get_DetailCount();
		int __fastcall get_DetailRecNo();
		int __fastcall get_DetailFieldCount();
		TFields *__fastcall get_DetailFields();
		String __fastcall get_MasterFieldName(int index);
		TFieldType __fastcall get_MasterFieldType(int index);
		int __fastcall get_MasterFieldSize(int index);
		String __fastcall get_DetailFieldName(int index);
		TFieldType __fastcall get_DetailFieldType(int index);
		int __fastcall get_DetailFieldSize(int index);
		String __fastcall get_MasterValidFieldList();
		void __fastcall set_MasterValidFieldList(String value);
		String __fastcall get_DetailValidFieldList();
		void __fastcall set_DetailValidFieldList(String value);
		//***********************************************************************
		bool __fastcall get_MasterFilterField(int index);
		bool __fastcall get_DetailFilterField(int index);
		int __fastcall get_MasterFieldAttr(int index);
		int __fastcall get_DetailFieldAttr(int index);
		String __fastcall get_MasterFieldExpr(int index);
		String __fastcall get_DetailFieldExpr(int index);
		int __fastcall get_MasterAttrType(int index);
		int __fastcall get_DetailAttrType(int index);
		//***********************************************************************
	private:
		String __fastcall BuildLinkStr();
		String __fastcall BuildLinkFields();
		void __fastcall ExtractLinkFields(String value);
		void __fastcall BuildDetailFilter();
		int __fastcall CheckFieldType(TField *Field);
		void __fastcall CheckResultStatus(int status);
		void __fastcall BuildDetailStatus();
		void __fastcall SetDataSetDisplayName(TADODataSet *ds, TStringList *dn,	TStringList *fn);
		String __fastcall BuildValidList(String value);
		void __fastcall InitDetailRecordStatus(TADODataSet *ds);

		void __fastcall MasterDataSetAfterScroll(TDataSet *DataSet);
		TADODataSet* __fastcall GetDetailDataSet();
		void __fastcall ClearMoneyDataSet(String FileName, String FieldsString);
		void __fastcall SetMasterDataSetBeforePost(TDataSetNotifyEvent value);
		TDataSetNotifyEvent __fastcall GetMasterDataSetBeforePost();
		void __fastcall SetMasterDataSetAfterPost(TDataSetNotifyEvent value);
		TDataSetNotifyEvent __fastcall GetMasterDataSetAfterPost();
		void __fastcall SetDetailDataSetBeforePost(TDataSetNotifyEvent value);
		TDataSetNotifyEvent __fastcall GetDetailDataSetBeforePost();
		void __fastcall DoClientDataSetAfterScroll();
		void __fastcall SetNullFieldValue(TField *DestField, TField* Sourcefield);
		int __fastcall GetSysDbType();
		int __fastcall GetAccDbType();
	protected:
		void __fastcall ClientDataSetTerminate(TObject *Sender);
//		void __fastcall WndProc(TMessage &Message);

		void __fastcall InitServerDataSet();
		void __fastcall FreeServerDataSet();
		void __fastcall InitClientDataSet(TJSONObject *Json);
		void __fastcall AsynOpen(TJSONObject *Json);
		void __fastcall AsynUpdate(TJSONObject *Json);
		void __fastcall AsynDelete(TJSONObject *Json);
		void __fastcall AsynDeleteDetail(TJSONObject *Json);
		void __fastcall AsynCheck(TJSONObject *Json);
		void __fastcall AsynCloseOff(TJSONObject *Json);
		void __fastcall AsynRevoke(TJSONObject *Json);
		void __fastcall AsynTally(TJSONObject *Json);
		void __fastcall AsynCmdExec(TJSONObject *Json);
		void __fastcall AsynValidateData(TJSONObject *Json);
		void __fastcall AsynExecSQL(TJSONObject *Json);
		void __fastcall RecvErrorMessage(TJSONObject *Json);
		bool __fastcall NullFieldIsString(TField *SourcField);
	public:
		__fastcall TJClientDataSet(TClientBroker *FBroker,	String AClassCode);
		__fastcall virtual ~TJClientDataSet();
	public:
		void __fastcall Open();
		void __fastcall AddNew();
		void __fastcall Insert();
		void __fastcall Edit();
		void __fastcall Delete();
		void __fastcall Update();
		void __fastcall Cancel();
		void __fastcall AddDetail();
		void __fastcall InserDetail();
		void __fastcall EditDetail();
		void __fastcall DeleteDetail();
		void __fastcall UpdateDetail();
		void __fastcall CancelDetail();
		void __fastcall Close();
		void __fastcall MoveFirst();
		void __fastcall MoveLast();
		void __fastcall MoveNext();
		void __fastcall MovePrior();
		void __fastcall MoveTo(int Distance);

		void __fastcall DetailFirst();
		void __fastcall DetailLast();
		void __fastcall DetailPrior();
		void __fastcall DetailNext();
		void __fastcall DetailMoveTo(int Distance);

		bool __fastcall LocateMaster(String KeyValues);
		bool __fastcall LocateDetail(String KeyValues);
		TField *__fastcall FindMasterField(String fieldname);
		TField *__fastcall FindDetailField(String fieldname);
		bool __fastcall FindMasterKey(String KeyValues);
		bool __fastcall FindDetailKey(String KeyValues);
		void __fastcall SaveMasterToFile(const WideString FileName, TPersistFormat Format, bool bFiltered = false, bool bMoneyHide = false, String ClearMasterFieldsString = "");
		void __fastcall SaveDetailToFile(const WideString FileName, TPersistFormat Format, bool bFiltered = false, bool bMoneyHide = false, String ClearDetailFieldsString = "");
		void __fastcall SaveMasterToFile(const WideString FileName,
		TPersistFormat Format, String sFilter = "", bool bMoneyHide = false, String ClearMasterFieldsString = "");
		Variant __fastcall GetMasterValue(String fieldname);
		Variant __fastcall GetMasterOldValue(String fieldname);
		void __fastcall SetMasterValue(String fieldname, Variant value);
		Variant __fastcall GetDetailValue(String fieldname);
		Variant __fastcall GetDetailOldValue(String fieldname);
		void __fastcall SetDetailValue(String fieldname, Variant value);

		void __fastcall CmdExec(String Param);
		void __fastcall Check(int IsCheck);
		void __fastcall CloseOff(int IsClose);
		void __fastcall Revoke(int IsRevoke);
		void __fastcall Tally(int IsTally);
		void __fastcall ExecSQL(String sqlstr);
		void __fastcall ExitClientDataSet();
		void __fastcall ValidField(TValidType vt,TValidAffect va);
	public:
		__property String MasterSQLString = {read = get_MasterSQLString};
		__property String DetailSQLString = {read = get_DetailSQLString};
		__property String MasterWhereString = {read = get_MasterWhereString, write = set_MasterWhereString};
		__property String DetailWhereString = {read = get_DetailWhereString, write = set_DetailWhereString};
		__property String MasterOrderString = {read = get_MasterOrderString, write = set_MasterOrderString};
		__property String DetailOrderString = {read = get_DetailOrderString, write = set_DetailOrderString};
		__property String MasterGroupString = {read = get_MasterGroupString, write = set_MasterGroupString};
		__property String DetailGroupString = {read = get_DetailGroupString, write = set_DetailGroupString};
		__property String MasterKeyFields = {read = get_MasterKeyFields, write = set_MasterKeyFields};
		__property String DetailKeyFields = {read = get_DetailKeyFields, write = set_DetailKeyFields};
		__property String LinkFields = {read = get_LinkFields, write = set_LinkFields};
		__property String MasterSort = {read = get_MasterSort, write = set_MasterSort};
		__property String DetailSort = {read = get_DetailSort, write = set_DetailSort};
		__property String Filter = {read = get_Filter, write = set_Filter};
		__property bool Filtered = {read = get_Filtered, write = set_Filtered};
		__property TDataSetState MasterStatus = {read = get_MasterStatus};
		__property TDataSetState DetailStatus = {read = get_DetailStatus};
		__property int DataSetType = {read = get_DataSetType};
		__property TJClientQuery *Query = {read = m_Query};

		__property bool Bof = {read = get_Bof};
		__property bool Eof = {read = get_Eof};
		__property int RecordCount = {read = get_RecordCount};
		__property int CurRecNo = {read = get_CurRecNo};
		__property int MasterFieldCount = {read = get_MasterFieldCount};
		__property TFields *MasterFields = {read = get_MasterFields};
		__property bool DetailBof = {read = get_DetailBof};
		__property bool DetailEof = {read = get_DetailEof};
		__property int DetailCount = {read = get_DetailCount};
		__property int DetailRecNo = {read = get_DetailRecNo};
		__property int DetailFieldCount = {read = get_DetailFieldCount};
		__property TFields *DetailFields = {read = get_DetailFields};

		__property String MasterFieldName[int index] = {read = get_MasterFieldName};
		__property TFieldType MasterFieldType[int index] = {read = get_MasterFieldType};
		__property int MasterFieldSize[int index] = {read = get_MasterFieldSize};
		__property String DetailFieldName[int index] = {read = get_DetailFieldName};
		__property TFieldType DetailFieldType[int index] = {read = get_DetailFieldType};
		__property int DetailFieldSize[int index] = {read = get_DetailFieldSize};

		//***********************************************************************
		__property bool MasterFilterField[int index] = {read = get_MasterFilterField};
		__property bool DetailFilterField[int index] = {read = get_DetailFilterField};
		__property int MasterFieldAttr[int index] = {read = get_MasterFieldAttr};
		__property int DetailFieldAttr[int index] = {read = get_DetailFieldAttr};
		__property String MasterFieldExpr[int index] = {read = get_MasterFieldExpr};
		__property String DetailFieldExpr[int index] = {read = get_DetailFieldExpr};
		__property int MasterAttrType[int index] = {read = get_MasterAttrType};
		__property int DetailAttrType[int index] = {read = get_DetailAttrType};
		//***********************************************************************

//		__property HWND Handle = {read = m_Handle};
//		__property HWND Parent = {read = m_Parent};
		__property String ServerDataSetHandle = {read = m_ServerDataSetHandle};
		__property bool Active = {read = m_DataSetActive};
		__property int TimeOut = {read = m_TimeOut, write = m_TimeOut};
		__property int SysDbType = {read = GetSysDbType};
		__property int AccDbType = {read = GetAccDbType};

		__property bool NeedValid = {read = m_NeedValid, write = m_NeedValid};
		__property String MasterValidFieldList = {read = get_MasterValidFieldList, write = set_MasterValidFieldList};
		__property String DetailValidFieldList = {read = get_DetailValidFieldList, write = set_DetailValidFieldList};
		__property String MasterFixedOrderString = {read = m_MasterFixedOrderString};
		__property String MasterFixedWhereString = {read = m_MasterFixedWhereString};
		__property String MasterFixedGroupString = {read = m_MasterFixedGroupString};
		__property String DetailFixedWhereString = {read = m_DetailFixedWhereString};
		__property String DetailFixedOrderString = {read = m_DetailFixedOrderString};
		__property String DetailFixedGroupString = {read = m_DetailFixedGroupString};
		__property String MasterLinkStr = {read = BuildLinkStr};
		__property String MasterLinkFields = {read = BuildLinkFields};
		__property TADODataSet* MasterDataSet = {read = m_MasterDataSet};
		__property TADODataSet* DetailDataSet = {read = GetDetailDataSet};
		// 在给主表提交记录之前，可以做一些字段值判断，计算，赋值等操作，这里只提交到本地，还没到数据库 ，需要调用update()才到服务器
		__property TDataSetNotifyEvent MasterDataSetBeforePost = {read = GetMasterDataSetBeforePost, write = SetMasterDataSetBeforePost};
		// 在给主表提交记录之后，想做的事情，如判断在新增单据时可以判断是否有明细行，或者。。。这里只提交到本地，还没到数据库 ，需要调用update()才到服务器
		__property TDataSetNotifyEvent MasterDataSetAfterPost = {read = GetMasterDataSetAfterPost, write = SetMasterDataSetAfterPost};
		// 在给子表提交记录之前，可以做一些字段值判断，计算，赋值等操作，每条明细都会提交的，这里只提交到本地，还没到数据库，需要调用update()才到服务器
		__property TDataSetNotifyEvent DetailDataSetBeforePost = {read = GetDetailDataSetBeforePost, write = SetDetailDataSetBeforePost};
		__property TDataSetNotifyEvent ClientDataSetAfterScroll = {read = FClientDataSetAfterScroll, write = FClientDataSetAfterScroll};
		__property TStringList* MasterDisplayFields = {read = m_MasterDisplayField};
		__property TStringList* DetailDisplayFields = {read = m_DetailDisplayField};
		// 明细表记录的状态：0-浏览;1-新增;2-修改;3-删除
		__property TStringList* DtlRecStatus = {read=m_DtlRecStatus, write=m_DtlRecStatus};
};
// ---------------------------------------------------------------------------
#endif
