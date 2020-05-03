// ---------------------------------------------------------------------------

#ifndef ZQueryH
#define ZQueryH
#include <adodb.hpp>
#include <db.hpp>

// ---------------------------------------------------------------------------
class PACKAGE TZQuery {
private:
	TComponent *m_AOwner;
	HWND m_Handle;
	TADOQuery *m_DataSet;
	TADOConnection *m_Connection;

	void __fastcall WndProc(TMessage &Msg);

	TDataSource* __fastcall get_DataSource();
	void __fastcall set_DataSource(TDataSource* value);
	TADOConnection* __fastcall get_Connection();
	void __fastcall set_Connection(TADOConnection* value);
	bool __fastcall get_Active();
	void __fastcall set_Active(bool value);
	bool __fastcall get_Bof();
	bool __fastcall get_Eof();
	int __fastcall get_RowsAffected();
#ifdef VER190
	TWideStrings* __fastcall get_SQL();
	void __fastcall set_SQL(TWideStrings* value);
#else
	TStrings* __fastcall get_SQL();
	void __fastcall set_SQL(TStrings* value);
#endif
	String __fastcall get_FilterText();
	void __fastcall set_FilterText(String value);
	bool __fastcall get_Filtered();
	void __fastcall set_Filtered(bool value);
	TADOLockType __fastcall get_LockType();
	void __fastcall set_LockType(TADOLockType value);
	int __fastcall get_CurRecNo();
	void __fastcall set_CurRecNo(int value);
	int __fastcall get_RecordCount();
	String __fastcall get_Sort();
	void __fastcall set_Sort(String value);
	TBookmark __fastcall get_BookmarkStr();
	void __fastcall set_BookmarkStr(TBookmark value);
	int __fastcall get_FieldCount();
	TFields* __fastcall get_Fields();
	Variant __fastcall get_FieldValue(String FieldName);
	void __fastcall set_FieldValue(String FieldName, Variant value);
	String __fastcall get_Name();
	void __fastcall set_Name(String value);
	TDataSetState __fastcall get_State();

public:
	__fastcall TZQuery(TComponent* Owner);
	__fastcall ~TZQuery();

	void __fastcall Open();
	void __fastcall Close();
	void __fastcall Refresh(void);

	void __fastcall First();
	void __fastcall Last();
	void __fastcall Prior();
	void __fastcall Next();
	void __fastcall MoveBy(int Distance);

	void __fastcall Append(void);
	void __fastcall Insert(void);
	void __fastcall Edit(void);
	void __fastcall Post(void);
	void __fastcall UpdateBatch(TAffectRecords AffectRecords);
	void __fastcall Cancel(void);
	void __fastcall CancelBatch(TAffectRecords AffectRecords);
	void __fastcall Delete(void);
	void __fastcall CancelUpdates(void);

	bool __fastcall Locate(String KeyFields, Variant &KeyValues,
		TLocateOptions Options);
	int __fastcall ExecSQL(void);
	TField* __fastcall FieldByName(String FieldName);
	TField* __fastcall FindField(const String FieldName);
	void __fastcall LoadFromFile(String FileName);
	void __fastcall SaveToFile(const WideString FileName,
		TPersistFormat Format);

	__property TDataSource* DataSource = {
		read = get_DataSource, write = set_DataSource};
	__property TADOConnection* Connection = {
		read = get_Connection, write = set_Connection};

	__property bool Active = {read = get_Active, write = set_Active};
	__property bool Bof = {read = get_Bof};
	__property bool Eof = {read = get_Eof};
	__property int RowsAffected = {read = get_RowsAffected};
#ifdef VER190
	__property TWideStrings* SQL = {read = get_SQL, write = set_SQL};
#else
	__property TStrings* SQL = {read = get_SQL, write = set_SQL};
#endif

	__property String Filter = {read = get_FilterText, write = set_FilterText};
	__property bool Filtered = {read = get_Filtered, write = set_Filtered};
	__property TADOLockType LockType = {
		read = get_LockType, write = set_LockType};
	__property int CurRecNo = {read = get_CurRecNo, write = set_CurRecNo};
	__property int RecordCount = {read = get_RecordCount};
	__property String Sort = {read = get_Sort, write = set_Sort};
	__property TBookmark Bookmark = {
		read = get_BookmarkStr, write = set_BookmarkStr};
	__property int FieldCount = {read = get_FieldCount};
	__property TFields* Fields = {read = get_Fields};
	__property Variant FieldValues[String FieldName] = {
		read = get_FieldValue, write = set_FieldValue};
	__property String Name = {read = get_Name, write = set_Name};
	__property TDataSetState State = {read = get_State};

};
#endif
