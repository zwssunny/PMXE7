// ---------------------------------------------------------------------------

#ifndef MsgJsonH
#define MsgJsonH
#include <DB.hpp>
#include <DBClient.hpp>
#include <adodb.hpp>
#include <Data.DBXJSON.hpp>
// ---------------------------------------------------------------------------
class PACKAGE TMsgJson : public TJSONObject
{
	private:
		int FOperate;
		String FClassID;
		String FClientID;
		String FQueryID;
		String FServerID;
		TJSONObject *FMasterJson;
		TJSONObject *FDetailJson;
		String FStatus;
		int FDataSetType;
		String FMasterKeyFields;
		String FDetailKeyFields;
		String FMasterDisplayName;
		String FDetailDisplayName;
		String FMasterDisplayField;
		String FDetailDisplayField;
		String FMasterFieldAttr;
		String FDetailFieldAttr;
		String FMasterAttrType;
		String FDetailAttrType;
		String FMasterFieldExpr;
		String FDetailFieldExpr;
		String FMasterSQLString;
		String FMasterFixedWhereString;
		String FMasterFixedOrderString;
		String FMasterFixedGroupString;
		String FMasterLinkFields;
		String FDetailLinkFields;
		String FDetailSQLString;
		String FDetailFixedWhereString;
		String FDetailFixedOrderString;
		String FDetailFixedGroupString;
		String FMasterStatus;
		String FNeedValid;
		int FValidRecNo;
		String FMasterValidFieldList;
		String FDetailValidFieldList;
		String FMasterWhere;
		String FMasterOrder;
		String FDetailWhere;
		String FDetailOrder;
		String FConnPtr;
		String FSQLStr;
		int FRowsAffected;
		int FErrorType;
		int FErrorCode;
		String FErrorMessage;
		int FIsClose;
		int FIsRevoke;
		int FIsTally;
	private:
		int __fastcall get_Operate();
		String __fastcall get_ClassID();
		String __fastcall get_ClientID();
		String __fastcall get_QueryID();
		String __fastcall get_ServerID();
		TJSONObject* __fastcall get_MasterJson();
		TJSONObject* __fastcall get_DetailJson();
		String __fastcall get_Status();
		int __fastcall get_DataSetType();
		String __fastcall get_MasterKeyFields();
		String __fastcall get_DetailKeyFields();
		String __fastcall get_MasterDisplayName();
		String __fastcall get_DetailDisplayName();
		String __fastcall get_MasterDisplayField();
		String __fastcall get_DetailDisplayField();
		String __fastcall get_MasterFieldAttr();
		String __fastcall get_DetailFieldAttr();
		String __fastcall get_MasterAttrType();
		String __fastcall get_DetailAttrType();
		String __fastcall get_MasterFieldExpr();
		String __fastcall get_DetailFieldExpr();
		String __fastcall get_MasterSQLString();
		String __fastcall get_MasterFixedWhereString();
		String __fastcall get_MasterFixedOrderString();
		String __fastcall get_MasterFixedGroupString();
		String __fastcall get_MasterLinkFields();
		String __fastcall get_DetailLinkFields();
		String __fastcall get_DetailSQLString();
		String __fastcall get_DetailFixedWhereString();
		String __fastcall get_DetailFixedOrderString();
		String __fastcall get_DetailFixedGroupString();
		String __fastcall get_MasterStatus();
		String __fastcall get_NeedValid();
		int __fastcall get_ValidRecNo();
		String __fastcall get_MasterValidFieldList();
		String __fastcall get_DetailValidFieldList();
		String __fastcall get_MasterWhere();
		String __fastcall get_MasterOrder();
		String __fastcall get_DetailWhere();
		String __fastcall get_DetailOrder();
		String __fastcall get_ConnPtr();
		String __fastcall get_SQLStr();
		int __fastcall get_RowsAffected();
		int __fastcall get_ErrorType();
		int __fastcall get_ErrorCode();
		String __fastcall get_ErrorMessage();
		int __fastcall get_IsClose();
		int __fastcall get_IsRevoke();
		int __fastcall get_IsTally();

		void __fastcall set_Operate(int Value);
		void __fastcall set_ClassID(String Value);
		void __fastcall set_ClientID(String Value);
		void __fastcall set_QueryID(String Value);
		void __fastcall set_ServerID(String Value);
		void __fastcall set_MasterJson(TJSONObject* Value);
		void __fastcall set_DetailJson(TJSONObject* Value);
		void __fastcall set_Status(String Value);
		void __fastcall set_DataSetType(int Value);
		void __fastcall set_MasterKeyFields(String Value);
		void __fastcall set_DetailKeyFields(String Value);
		void __fastcall set_MasterDisplayName(String Value);
		void __fastcall set_DetailDisplayName(String Value);
		void __fastcall set_MasterDisplayField(String Value);
		void __fastcall set_DetailDisplayField(String Value);
		void __fastcall set_MasterFieldAttr(String Value);
		void __fastcall set_DetailFieldAttr(String Value);
		void __fastcall set_MasterAttrType(String Value);
		void __fastcall set_DetailAttrType(String Value);
		void __fastcall set_MasterFieldExpr(String Value);
		void __fastcall set_DetailFieldExpr(String Value);
		void __fastcall set_MasterSQLString(String Value);
		void __fastcall set_MasterFixedWhereString(String Value);
		void __fastcall set_MasterFixedOrderString(String Value);
		void __fastcall set_MasterFixedGroupString(String Value);
		void __fastcall set_MasterLinkFields(String Value);
		void __fastcall set_DetailLinkFields(String Value);
		void __fastcall set_DetailSQLString(String Value);
		void __fastcall set_DetailFixedWhereString(String Value);
		void __fastcall set_DetailFixedOrderString(String Value);
		void __fastcall set_DetailFixedGroupString(String Value);
		void __fastcall set_MasterStatus(String Value);
		void __fastcall set_NeedValid(String Value);
		void __fastcall set_ValidRecNo(int Value);
		void __fastcall set_MasterValidFieldList(String Value);
		void __fastcall set_DetailValidFieldList(String Value);
		void __fastcall set_MasterWhere(String Value);
		void __fastcall set_MasterOrder(String Value);
		void __fastcall set_DetailWhere(String Value);
		void __fastcall set_DetailOrder(String Value);
		void __fastcall set_ConnPtr(String Value);
		void __fastcall set_SQLStr(String Value);
		void __fastcall set_RowsAffected(int Value);
		void __fastcall set_ErrorType(int Value);
		void __fastcall set_ErrorCode(int Value);
		void __fastcall set_ErrorMessage(String Value);
		void __fastcall set_IsClose(int Value);
		void __fastcall set_IsRevoke(int Value);
		void __fastcall set_IsTally(int Value);
	public:
		__fastcall TMsgJson(void);
		__fastcall TMsgJson(TJSONObject *Json);
		__fastcall ~TMsgJson(void);
	public:
		__property int Operate     = {read = get_Operate, write = set_Operate};
		__property String ClassID  = {read = get_ClassID, write = set_ClassID};
		__property String ClientID = {read = get_ClientID, write = set_ClientID};
		__property String QueryID  = {read = get_QueryID, write = set_QueryID};
		__property String ServerID = {read = get_ServerID, write = set_ServerID};

		__property TJSONObject* MasterJson = {read = get_MasterJson, write = set_MasterJson};
		__property TJSONObject* DetailJson = {read = get_DetailJson, write = set_DetailJson};
		__property String Status = {read = get_Status, write = set_Status};
		__property int DataSetType = {read = get_DataSetType, write = set_DataSetType};
		__property String MasterKeyFields = {read = get_MasterKeyFields, write = set_MasterKeyFields};
		__property String DetailKeyFields = {read = get_DetailKeyFields, write = set_DetailKeyFields};
		__property String MasterDisplayName = {read = get_MasterDisplayName, write = set_MasterDisplayName};
		__property String DetailDisplayName = {read = get_DetailDisplayName, write = set_DetailDisplayName};
		__property String MasterDisplayField = {read = get_MasterDisplayField, write = set_MasterDisplayField};
		__property String DetailDisplayField = {read = get_DetailDisplayField, write = set_DetailDisplayField};
		__property String MasterFieldAttr = {read = get_MasterFieldAttr, write = set_MasterFieldAttr};
		__property String DetailFieldAttr = {read = get_DetailFieldAttr, write = set_DetailFieldAttr};
		__property String MasterAttrType = {read = get_MasterAttrType, write = set_MasterAttrType};
		__property String DetailAttrType = {read = get_DetailAttrType, write = set_DetailAttrType};
		__property String MasterFieldExpr = {read = get_MasterFieldExpr, write = set_MasterFieldExpr};
		__property String DetailFieldExpr = {read = get_DetailFieldExpr, write = set_DetailFieldExpr};
		__property String MasterSQLString = {read = get_MasterSQLString, write = set_MasterSQLString};
		__property String MasterFixedWhereString = {read = get_MasterFixedWhereString, write = set_MasterFixedWhereString};
		__property String MasterFixedOrderString = {read = get_MasterFixedOrderString, write = set_MasterFixedOrderString};
		__property String MasterFixedGroupString = {read = get_MasterFixedGroupString, write = set_MasterFixedGroupString};
		__property String MasterLinkFields = {read = get_MasterLinkFields, write = set_MasterLinkFields};
		__property String DetailLinkFields = {read = get_DetailLinkFields, write = set_DetailLinkFields};
		__property String DetailSQLString = {read = get_DetailSQLString, write = set_DetailSQLString};
		__property String DetailFixedWhereString = {read = get_DetailFixedWhereString, write = set_DetailFixedWhereString};
		__property String DetailFixedOrderString = {read = get_DetailFixedOrderString, write = set_DetailFixedOrderString};
		__property String DetailFixedGroupString = {read = get_DetailFixedGroupString, write = set_DetailFixedGroupString};
		__property String MasterStatus = {read = get_MasterStatus, write = set_MasterStatus};
		__property String NeedValid = {read = get_NeedValid, write = set_NeedValid};
//		__property TValidType ValidType = {read = get_ValidType, write = set_ValidType};
//		__property TValidAffect ValidAffect = {read = get_ValidAffect, write = set_ValidAffect};
		__property int ValidRecNo = {read = get_ValidRecNo, write = set_ValidRecNo};
		__property String MasterValidFieldList = {read = get_MasterValidFieldList, write = set_MasterValidFieldList};
		__property String DetailValidFieldList = {read = get_DetailValidFieldList, write = set_DetailValidFieldList};
		__property String MasterWhere = {read = get_MasterWhere, write = set_MasterWhere};
		__property String MasterOrder = {read = get_MasterOrder, write = set_MasterOrder};
		__property String DetailWhere = {read = get_DetailWhere, write = set_DetailWhere};
		__property String DetailOrder = {read = get_DetailOrder, write = set_DetailOrder};
		__property String ConnPtr = {read = get_ConnPtr, write = set_ConnPtr};
		__property String SQLStr = {read = get_SQLStr, write = set_SQLStr};
		__property int RowsAffected = {read = get_RowsAffected, write = set_RowsAffected};
		__property int ErrorType = {read = get_ErrorType, write = set_ErrorType};
		__property int ErrorCode = {read = get_ErrorCode, write = set_ErrorCode};
		__property String ErrorMessage = {read = get_ErrorMessage, write = set_ErrorMessage};
		__property int IsClose = {read = get_IsClose, write = set_IsClose};
		__property int IsRevoke = {read = get_IsRevoke, write = set_IsRevoke};
		__property int IsTally = {read = get_IsTally, write = set_IsTally};
	public:
		/*********************************************************************
		//返回的JSON字符串格式由数据(Data)和列信息(Cols)组成：
		//{MasterData:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
    // MasterCols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]
    // DetailData:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
    // DetailCols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]
    //业务类信息
    // ClassInfo:[{Status:},{DataSetType:},{MasterKeyFields:},{DetailKeyFields:},{MasterDisplayName:},
    // {DetailDisplayName:},{MasterDisplayField:},{DetailDisplayField:},{MasterFilterFields:},
    // {DetailFilterFields:},{MasterFieldAttr:},{DetailFieldAttr:},{MasterAttrType:},{DetailAttrType:},
    // {MasterFieldExpr:},{DetailFieldExpr:},{MasterSqlString:},{MasterFixedWhere:},{MasterFixedOrder:},
    // {MasterFixedGroup:},{MasterLinkFields:},{DetailLinkFields:},{DetailSqlString:},{DetailFixedWhere:},
    // {DetailFixedOrder:},{DetailFixedGroup}]}
		**********************************************************************/
		TJSONObject* __fastcall JSONObjectSerialize();
};
#endif
