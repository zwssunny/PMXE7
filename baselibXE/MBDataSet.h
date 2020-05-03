// ---------------------------------------------------------------------------

#ifndef MBDataSetH
#define MBDataSetH
#include <adodb.hpp>
#include <db.hpp>
#include "ZQuery.h"

// ---------------------------------------------------------------------------
class PACKAGE TMBDataSet {
private:
	TComponent *m_AOwner;
	HWND m_Handle;
	TADOQuery *m_MasterDataSet;
	TADOQuery *m_DetailDataSet;
	TZQuery *m_Query;
	TADOConnection *m_Connection;

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
	TDataSetState __fastcall get_MasterStatus();
	TDataSetState __fastcall get_DetailStatus();
	String __fastcall get_Filter();
	void __fastcall set_Filter(String value);
	bool __fastcall get_Filtered();
	void __fastcall set_Filtered(bool value);
	int __fastcall get_DataSetType();
	bool __fastcall get_Bof();
	bool __fastcall get_Eof();
	bool __fastcall get_DetailBof();
	bool __fastcall get_DetailEof();
	int __fastcall get_RecordCount();
	int __fastcall get_CurRecNo();
	int __fastcall get_DetailCount();
	int __fastcall get_DetailRecNo();
	int __fastcall get_MasterFieldCount();
	int __fastcall get_DetailFieldCount();
	TFields *__fastcall get_MasterFields();
	TFields *__fastcall get_DetailFields();
	String __fastcall BuildLinkStr();
	String __fastcall BuildLinkFields();
	void __fastcall ExtractLinkFields(String value);
	void __fastcall BuildDetailFilter();
	int __fastcall CheckFieldType(TField *Field);
	TADOConnection *__fastcall get_Connection();
	void __fastcall set_Connection(TADOConnection *value);

public:
	__fastcall TMBDataSet(TComponent* Owner, int dstype);
	__fastcall ~TMBDataSet();

protected:
	void __fastcall WndProc(TMessage &Msg);
	void __fastcall InitPowerDataSet();

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

	Variant __fastcall GetMasterValue(String fieldname);
	void __fastcall SetMasterValue(String fieldname, Variant value);
	Variant __fastcall GetDetailValue(String fieldname);
	void __fastcall SetDetailValue(String fieldname, Variant value);

	__property String MasterSQLString = {
		read = get_MasterSQLString, write = set_MasterSQLString};
	__property String DetailSQLString = {
		read = get_DetailSQLString, write = set_DetailSQLString};
	__property String MasterWhereString = {
		read = get_MasterWhereString, write = set_MasterWhereString};
	__property String DetailWhereString = {
		read = get_DetailWhereString, write = set_DetailWhereString};
	__property String MasterOrderString = {
		read = get_MasterOrderString, write = set_MasterOrderString};
	__property String DetailOrderString = {
		read = get_DetailOrderString, write = set_DetailOrderString};
	__property String MasterGroupString = {
		read = get_MasterGroupString, write = set_MasterGroupString};
	__property String DetailGroupString = {
		read = get_DetailGroupString, write = set_DetailGroupString};
	__property String MasterKeyFields = {
		read = get_MasterKeyFields, write = set_MasterKeyFields};
	__property String DetailKeyFields = {
		read = get_DetailKeyFields, write = set_DetailKeyFields};
	__property String LinkFields = {
		read = get_LinkFields, write = set_LinkFields};
	__property String MasterSort = {
		read = get_MasterSort, write = set_MasterSort};
	__property String DetailSort = {
		read = get_DetailSort, write = set_DetailSort};
	__property String Filter = {read = get_Filter, write = set_Filter};
	__property bool Filtered = {read = get_Filtered, write = set_Filtered};
	__property TDataSetState MasterStatus = {read = get_MasterStatus};
	__property TDataSetState DetailStatus = {read = get_DetailStatus};
	__property int DataSetType = {read = get_DataSetType};
	__property TZQuery *Query = {read = m_Query};
	__property TADOConnection *Connection = {
		read = get_Connection, write = set_Connection};

	__property bool Bof = {read = get_Bof};
	__property bool Eof = {read = get_Eof};
	__property bool DetailBof = {read = get_DetailBof};
	__property bool DetailEof = {read = get_DetailEof};
	__property int RecordCount = {read = get_RecordCount};
	__property int MasterFieldCount = {read = get_MasterFieldCount};
	__property TFields *MasterFields = {read = get_MasterFields};
	__property int CurRecNo = {read = get_CurRecNo};
	__property int DetailCount = {read = get_DetailCount};
	__property int DetailRecNo = {read = get_DetailRecNo};
	__property int DetailFieldCount = {read = get_DetailFieldCount};
	__property TFields *DetailFields = {read = get_DetailFields};

};
#endif
