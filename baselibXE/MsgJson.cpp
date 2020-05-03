// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MsgJson.h"
#include "BaseFunc.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
__fastcall TMsgJson::TMsgJson(void)
{
	FOperate                = -1;
	FClassID                = 0;
	FClientID               = 0;
	FQueryID                = 0;
	FServerID               = 0;
	FMasterJson = new TJSONObject();
	FDetailJson = new TJSONObject();
	FStatus                 = "";
	FDataSetType            = 0;
	FMasterKeyFields        = "";
	FDetailKeyFields        = "";
	FMasterDisplayName      = "";
	FDetailDisplayName      = "";
	FMasterDisplayField     = "";
	FDetailDisplayField     = "";
	FMasterFieldAttr        = "";
	FDetailFieldAttr        = "";
	FMasterAttrType         = "";
	FDetailAttrType         = "";
	FMasterFieldExpr        = "";
	FDetailFieldExpr        = "";
	FMasterSQLString        = "";
	FMasterFixedWhereString = "";
	FMasterFixedOrderString = "";
	FMasterFixedGroupString = "";
	FMasterLinkFields       = "";
	FDetailLinkFields       = "";
	FDetailSQLString        = "";
	FDetailFixedWhereString = "";
	FDetailFixedOrderString = "";
	FDetailFixedGroupString = "";
	FMasterStatus           = "";
	FNeedValid              = "";
	FValidRecNo             = 0;
	FMasterValidFieldList   = "";
	FDetailValidFieldList   = "";
	FMasterWhere            = "";
	FMasterOrder            = "";
	FDetailWhere            = "";
	FDetailOrder            = "";
	FConnPtr                = "";
	FSQLStr                 = "";
	FRowsAffected           = 0;
	FErrorType              = 100;
	FErrorCode              = 100;
	FErrorMessage           = "";
	FIsClose                = 0;
	FIsRevoke               = 0;
	FIsTally                = 0;
}
// ---------------------------------------------------------------------------
__fastcall TMsgJson::TMsgJson(TJSONObject *Json)
{
	if(Json)
	{
		FMasterJson = new TJSONObject();
		FDetailJson = new TJSONObject();
		TJSONArray  *aj;
		switch (Json->Size())
		{
			case 1:
				aj = (TJSONArray*)(Json->Get("ClassInfo")->JsonValue);
				break;
			case 3:
				aj = (TJSONArray*)(Json->Get(0)->JsonValue);
				MasterJson->AddPair("Data",aj);
				aj = (TJSONArray*)(Json->Get(1)->JsonValue);
				MasterJson->AddPair("Cols",aj);

				aj = (TJSONArray*)(Json->Get("ClassInfo")->JsonValue);
				break;
			case 5:
				aj = (TJSONArray*)(Json->Get(0)->JsonValue);
				MasterJson->AddPair("Data",aj);
				aj = (TJSONArray*)(Json->Get(1)->JsonValue);
				MasterJson->AddPair("Cols",aj);

				aj = (TJSONArray*)(Json->Get(2)->JsonValue);
				DetailJson->AddPair("Data",aj);
				aj = (TJSONArray*)(Json->Get(3)->JsonValue);
				DetailJson->AddPair("Cols",aj);

				aj = (TJSONArray*)(Json->Get("ClassInfo")->JsonValue);
				break;
		}

		if(Json->Size() > 0)
		{
			TJSONObject *sj;

			sj = (TJSONObject*)(aj->Get(0));
			Operate = sj->Get("Operate")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(1));
			ClassID = sj->Get("ClassID")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(2));
			ClientID = sj->Get("ClientID")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(3));
			QueryID = sj->Get("QueryID")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(4));
			ServerID = sj->Get("ServerID")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(5));
			Status = sj->Get("Status")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(6));
			DataSetType = sj->Get("DataSetType")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(7));
			MasterKeyFields = sj->Get("MasterKeyFields")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(8));
			DetailKeyFields = sj->Get("DetailKeyFields")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(9));
			MasterDisplayName = sj->Get("MasterDisplayName")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(10));
			DetailDisplayName = sj->Get("DetailDisplayName")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(11));
			MasterDisplayField = sj->Get("MasterDisplayField")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(12));
			DetailDisplayField = sj->Get("DetailDisplayField")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(13));
			MasterFieldAttr = sj->Get("MasterFieldAttr")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(14));
			DetailFieldAttr = sj->Get("DetailFieldAttr")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(15));
			MasterAttrType = sj->Get("MasterAttrType")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(16));
			DetailAttrType = sj->Get("DetailAttrType")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(17));
			MasterFieldExpr = sj->Get("MasterFieldExpr")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(18));
			DetailFieldExpr = sj->Get("DetailFieldExpr")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(19));
			MasterSQLString = sj->Get("MasterSQLString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(20));
			MasterFixedWhereString = sj->Get("MasterFixedWhereString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(21));
			MasterFixedOrderString = sj->Get("MasterFixedOrderString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(22));
			MasterFixedGroupString = sj->Get("MasterFixedGroupString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(23));
			MasterLinkFields = sj->Get("MasterLinkFields")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(24));
			DetailLinkFields = sj->Get("DetailLinkFields")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(25));
			DetailSQLString = sj->Get("DetailSQLString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(26));
			DetailFixedWhereString = sj->Get("DetailFixedWhereString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(27));
			DetailFixedOrderString = sj->Get("DetailFixedOrderString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(28));
			DetailFixedGroupString = sj->Get("DetailFixedGroupString")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(29));
			MasterStatus = sj->Get("MasterStatus")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(30));
			NeedValid = sj->Get("NeedValid")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(31));
			ValidRecNo = sj->Get("ValidRecNo")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(32));
			MasterValidFieldList = sj->Get("MasterValidFieldList")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(33));
			DetailValidFieldList = sj->Get("DetailValidFieldList")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(34));
			MasterWhere = sj->Get("MasterWhere")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(35));
			MasterOrder = sj->Get("MasterOrder")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(36));
			DetailWhere = sj->Get("DetailWhere")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(37));
			DetailOrder = sj->Get("DetailOrder")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(38));
			ConnPtr = sj->Get("ConnPtr")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(39));
			SQLStr = sj->Get("SQLStr")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(40));
			RowsAffected = sj->Get("RowsAffected")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(41));
			ErrorType = sj->Get("ErrorType")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(42));
			ErrorCode = sj->Get("ErrorCode")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(43));
			ErrorMessage = sj->Get("ErrorMessage")->JsonValue->Value();

			sj = (TJSONObject*)(aj->Get(44));
			IsClose = sj->Get("IsClose")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(45));
			IsRevoke = sj->Get("IsRevoke")->JsonValue->Value().ToInt();

			sj = (TJSONObject*)(aj->Get(46));
			IsTally = sj->Get("IsTally")->JsonValue->Value().ToInt();
		}
	}
}
// ---------------------------------------------------------------------------
__fastcall TMsgJson::~TMsgJson(void)
{
	if(FMasterJson) delete FMasterJson;
	if(FDetailJson) delete FDetailJson;
}
// ---------------------------------------------------------------------------
TJSONObject* __fastcall TMsgJson::JSONObjectSerialize()
{
	TJSONObject *JSONObject = new TJSONObject();

	if(FMasterJson->Size() == 2)
		JSONObject = FMasterJson;

	if(FDetailJson->Size() == 2)
	{
		TJSONArray *aj0 = (TJSONArray*)(FDetailJson->Get(0)->JsonValue);
		TJSONArray *aj1 = (TJSONArray*)(FDetailJson->Get(1)->JsonValue);
		JSONObject->AddPair("Data",aj0);
		JSONObject->AddPair("Cols",aj1);
	}

	TJSONArray *JSONArray = new TJSONArray();
	TJSONObject *elmObject = new TJSONObject();
	elmObject->AddPair(new TJSONPair("Operate",FOperate));
	elmObject->AddPair(new TJSONPair("ClassID",FClassID));
	elmObject->AddPair(new TJSONPair("ClientID",FClientID));
	elmObject->AddPair(new TJSONPair("QueryID",FQueryID));
	elmObject->AddPair(new TJSONPair("ServerID",FServerID));
	elmObject->AddPair(new TJSONPair("Status",FStatus));
	elmObject->AddPair(new TJSONPair("DataSetType",FDataSetType));
	elmObject->AddPair(new TJSONPair("MasterKeyFields",FMasterKeyFields));
	elmObject->AddPair(new TJSONPair("DetailKeyFields",FDetailKeyFields));
	elmObject->AddPair(new TJSONPair("MasterDisplayName",FMasterDisplayName));
	elmObject->AddPair(new TJSONPair("DetailDisplayName",FDetailDisplayName));
	elmObject->AddPair(new TJSONPair("MasterDisplayField",FMasterDisplayField));
	elmObject->AddPair(new TJSONPair("DetailDisplayField",FDetailDisplayField));
	elmObject->AddPair(new TJSONPair("MasterFieldAttr",FMasterFieldAttr));
	elmObject->AddPair(new TJSONPair("DetailFieldAttr",FDetailFieldAttr));
	elmObject->AddPair(new TJSONPair("MasterAttrType",FMasterAttrType));
	elmObject->AddPair(new TJSONPair("DetailAttrType",FDetailAttrType));
	elmObject->AddPair(new TJSONPair("MasterFieldExpr",FMasterFieldExpr));
	elmObject->AddPair(new TJSONPair("DetailFieldExpr",FDetailFieldExpr));
	elmObject->AddPair(new TJSONPair("MasterSQLString",FMasterSQLString));
	elmObject->AddPair(new TJSONPair("MasterFixedWhereString",FMasterFixedWhereString));
	elmObject->AddPair(new TJSONPair("MasterFixedOrderString",FMasterFixedOrderString));
	elmObject->AddPair(new TJSONPair("MasterFixedGroupString",FMasterFixedGroupString));
	elmObject->AddPair(new TJSONPair("MasterLinkFields",FMasterLinkFields));
	elmObject->AddPair(new TJSONPair("DetailLinkFields",FDetailLinkFields));
	elmObject->AddPair(new TJSONPair("DetailSQLString",FDetailSQLString));
	elmObject->AddPair(new TJSONPair("DetailFixedWhereString",FDetailFixedWhereString));
	elmObject->AddPair(new TJSONPair("DetailFixedOrderString",FDetailFixedOrderString));
	elmObject->AddPair(new TJSONPair("DetailFixedGroupString",FDetailFixedGroupString));
	elmObject->AddPair(new TJSONPair("MasterStatus",FMasterStatus));
	elmObject->AddPair(new TJSONPair("NeedValid",FNeedValid));
	elmObject->AddPair(new TJSONPair("ValidRecNo",FValidRecNo));
	elmObject->AddPair(new TJSONPair("MasterValidFieldList",FMasterValidFieldList));
	elmObject->AddPair(new TJSONPair("DetailValidFieldList",FDetailValidFieldList));
	elmObject->AddPair(new TJSONPair("MasterWhere",FMasterWhere));
	elmObject->AddPair(new TJSONPair("MasterOrder",FMasterOrder));
	elmObject->AddPair(new TJSONPair("DetailWhere",FDetailWhere));
	elmObject->AddPair(new TJSONPair("DetailOrder",FDetailOrder));
	elmObject->AddPair(new TJSONPair("ConnPtr",FConnPtr));
	elmObject->AddPair(new TJSONPair("SQLStr",FSQLStr));
	elmObject->AddPair(new TJSONPair("RowsAffected",FRowsAffected));
	elmObject->AddPair(new TJSONPair("ErrorType",FErrorType));
	elmObject->AddPair(new TJSONPair("ErrorCode",FErrorCode));
	elmObject->AddPair(new TJSONPair("ErrorMessage",FErrorMessage));
	elmObject->AddPair(new TJSONPair("IsClose",FIsClose));
	elmObject->AddPair(new TJSONPair("IsRevoke",FIsRevoke));
	elmObject->AddPair(new TJSONPair("IsTally",FIsTally));
	JSONArray->AddElement(elmObject);
	JSONObject->AddPair("ClassInfo",JSONArray);
	return JSONObject;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_Operate()
{
	return FOperate;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_Operate(int Value)
{
	FOperate = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_ClassID()
{
	return FClassID;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ClassID(String Value)
{
	FClassID = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_ClientID()
{
	return FClientID;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ClientID(String Value)
{
	FClientID = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_ServerID()
{
	return FServerID;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ServerID(String Value)
{
	FServerID = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_QueryID()
{
	return FQueryID;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_QueryID(String Value)
{
	FQueryID = Value;
}
// ---------------------------------------------------------------------------
TJSONObject* __fastcall TMsgJson::get_MasterJson()
{
	return FMasterJson;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterJson(TJSONObject* Value)
{
	FMasterJson = Value;
}
// ---------------------------------------------------------------------------
TJSONObject* __fastcall TMsgJson::get_DetailJson()
{
	return FDetailJson;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailJson(TJSONObject* Value)
{
	FDetailJson = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_Status()
{
	return FStatus;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_Status(String Value)
{
	FStatus = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_DataSetType()
{
	return FDataSetType;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DataSetType(int Value)
{
	FDataSetType = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterKeyFields()
{
	return FMasterKeyFields;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterKeyFields(String Value)
{
	FMasterKeyFields = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailKeyFields()
{
	return FDetailKeyFields;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailKeyFields(String Value)
{
	FDetailKeyFields = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterDisplayName()
{
	return FMasterDisplayName;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterDisplayName(String Value)
{
	FMasterDisplayName = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailDisplayName()
{
	return FDetailDisplayName;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailDisplayName(String Value)
{
	FDetailDisplayName = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterDisplayField()
{
	return FMasterDisplayField;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterDisplayField(String Value)
{
	FMasterDisplayField = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailDisplayField()
{
	return FDetailDisplayField;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailDisplayField(String Value)
{
	FDetailDisplayField = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterFieldAttr()
{
	return FMasterFieldAttr;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterFieldAttr(String Value)
{
	FMasterFieldAttr = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailFieldAttr()
{
	return FDetailFieldAttr;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailFieldAttr(String Value)
{
	FDetailFieldAttr = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterAttrType()
{
	return FMasterAttrType;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterAttrType(String Value)
{
	FMasterAttrType = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailAttrType()
{
	return FDetailAttrType;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailAttrType(String Value)
{
	FDetailAttrType = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterFieldExpr()
{
	return FMasterFieldExpr;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterFieldExpr(String Value)
{
	FMasterFieldExpr = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailFieldExpr()
{
	return FDetailFieldExpr;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailFieldExpr(String Value)
{
	FDetailFieldExpr = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterSQLString()
{
	return FMasterSQLString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterSQLString(String Value)
{
	FMasterSQLString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterFixedWhereString()
{
	return FMasterFixedWhereString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterFixedWhereString(String Value)
{
	FMasterFixedWhereString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterFixedOrderString()
{
	return FMasterFixedOrderString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterFixedOrderString(String Value)
{
	FMasterFixedOrderString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterFixedGroupString()
{
	return FMasterFixedGroupString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterFixedGroupString(String Value)
{
	FMasterFixedGroupString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterLinkFields()
{
	return FMasterLinkFields;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterLinkFields(String Value)
{
	FMasterLinkFields = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailLinkFields()
{
	return FDetailLinkFields;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailLinkFields(String Value)
{
	FDetailLinkFields = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailSQLString()
{
	return FDetailSQLString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailSQLString(String Value)
{
	FDetailSQLString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailFixedWhereString()
{
	return FDetailFixedWhereString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailFixedWhereString(String Value)
{
	FDetailFixedWhereString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailFixedOrderString()
{
	return FDetailFixedOrderString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailFixedOrderString(String Value)
{
	FDetailFixedOrderString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailFixedGroupString()
{
	return FDetailFixedGroupString;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailFixedGroupString(String Value)
{
	FDetailFixedGroupString = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterStatus()
{
	return FMasterStatus;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterStatus(String Value)
{
	FMasterStatus = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_NeedValid()
{
	return FNeedValid;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_NeedValid(String Value)
{
	FNeedValid = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_ValidRecNo()
{
	return FValidRecNo;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ValidRecNo(int Value)
{
	FValidRecNo = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterValidFieldList()
{
	return FMasterValidFieldList;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterValidFieldList(String Value)
{
	FMasterValidFieldList = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailValidFieldList()
{
	return FDetailValidFieldList;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailValidFieldList(String Value)
{
	FDetailValidFieldList = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterWhere()
{
	return FMasterWhere;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterWhere(String Value)
{
	FMasterWhere = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_MasterOrder()
{
	return FMasterOrder;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_MasterOrder(String Value)
{
	FMasterOrder = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailWhere()
{
	return FDetailWhere;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailWhere(String Value)
{
	FDetailWhere = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_DetailOrder()
{
	return FDetailOrder;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_DetailOrder(String Value)
{
	FDetailOrder = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_ConnPtr()
{
	return FConnPtr;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ConnPtr(String Value)
{
	FConnPtr = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_SQLStr()
{
	return FSQLStr;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_SQLStr(String Value)
{
	FSQLStr = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_RowsAffected()
{
	return FRowsAffected;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_RowsAffected(int Value)
{
	FRowsAffected = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_ErrorType()
{
	return FErrorType;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ErrorType(int Value)
{
	FErrorType = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_ErrorCode()
{
	return FErrorCode;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ErrorCode(int Value)
{
	FErrorCode = Value;
}
// ---------------------------------------------------------------------------
String __fastcall TMsgJson::get_ErrorMessage()
{
	return FErrorMessage;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_ErrorMessage(String Value)
{
	FErrorMessage = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_IsClose()
{
	return FIsClose;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_IsClose(int Value)
{
	FIsClose = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_IsRevoke()
{
	return FIsRevoke;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_IsRevoke(int Value)
{
	FIsRevoke = Value;
}
// ---------------------------------------------------------------------------
int __fastcall TMsgJson::get_IsTally()
{
	return FIsTally;
}
// ---------------------------------------------------------------------------
void __fastcall TMsgJson::set_IsTally(int Value)
{
	FIsTally = Value;
}
// ---------------------------------------------------------------------------
