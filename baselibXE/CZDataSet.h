// ---------------------------------------------------------------------------

#ifndef CZDataSetH
#define CZDataSetH
#include <System.hpp>	// Pascal unit
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
// ---------------------------------------------------------------------------
class PACKAGE TCZDataSet // :public TStringList
{
private:
	TStringList *m_FieldSet;
	int m_CurRecNo;
	int m_RecordCount;
	String m_Bookmark;
	bool m_Bof, m_Eof;
	int m_Status; // 0-未打开,1-浏览,2-新增,3-修改,4-插入
	String m_KeyField;
	TStringList *m_EditRecord;

public:
	__fastcall TCZDataSet();
	__fastcall ~TCZDataSet();

	void __fastcall AddNew();
	void __fastcall InsRecord();
	void __fastcall Edit();
	void __fastcall DelRecord();
	void __fastcall Cancel();
	void __fastcall Update();
	void __fastcall Clear();

	void __fastcall First();
	void __fastcall Prior();
	void __fastcall Last();
	void __fastcall Next();
	void __fastcall MoveBy(int index);

	bool __fastcall LocateByKey(String key);
	bool __fastcall LocateByIndex(int index);
	bool __fastcall LocateField(String fieldname, String key);

	void __fastcall AddField(String fieldname);
	void __fastcall DelField(String fieldname);
	void __fastcall LoadFromString(String datasetstr);

	__property int RecordCount = {read = m_RecordCount /* get_RecordCount */ };
	__property int FieldCount = {read = get_FieldCount};
	__property String FieldValues[String fieldname] = {
		read = get_FieldValues, write = set_FieldValues};
	__property String FieldByIndex[int index] = {
		read = get_FieldByIndex, write = set_FieldByIndex};
	__property String FieldName[int index] = {read = get_FieldName};
	__property String KeyField = {read = get_KeyField, write = set_KeyField};
	__property bool Bof = {read = get_Bof};
	__property bool Eof = {read = get_Eof};
	__property int Status = {read = get_Status};
	__property String Bookmark = {read = get_Bookmark, write = set_Bookmark};
	__property int CurRecNo = {read = get_CurRecNo};

private:
	int __fastcall get_RecordCount();
	int __fastcall get_FieldCount();
	String __fastcall get_FieldValues(String fieldname);
	void __fastcall set_FieldValues(String fieldname, String value);
	String __fastcall get_FieldByIndex(int index);
	void __fastcall set_FieldByIndex(int index, String value);
	String __fastcall get_FieldName(int index);
	String __fastcall get_KeyField();
	void __fastcall set_KeyField(String value);
	bool __fastcall get_Bof();
	bool __fastcall get_Eof();
	int __fastcall get_Status();
	String __fastcall get_Bookmark();
	void __fastcall set_Bookmark(String value);
	int __fastcall get_CurRecNo();
	void __fastcall ChgStatus(int value);
};
#endif
