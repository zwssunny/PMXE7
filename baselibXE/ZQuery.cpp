// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ZQuery.h"

// ---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TZQuery::TZQuery(TComponent* Owner) {
	m_AOwner = Owner;
	m_Handle = AllocateHWnd(WndProc);
	m_DataSet = new TADOQuery(Owner);
	m_DataSet->EnableBCD = false;
}

// ---------------------------------------------------------------------------
__fastcall TZQuery::~TZQuery() {
	if (m_Handle)
		DeallocateHWnd(m_Handle);
	delete m_DataSet;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::WndProc(TMessage &Msg) {
	Msg.Result = DefWindowProc(m_Handle, Msg.Msg, Msg.WParam, Msg.LParam);
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Open() {
	m_DataSet->Open();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Close() {
	m_DataSet->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Refresh(void) {
	m_DataSet->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::First() {
	m_DataSet->First();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Last() {
	m_DataSet->Last();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Prior() {
	m_DataSet->Prior();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Next() {
	m_DataSet->Next();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::MoveBy(int Distance) {
	m_DataSet->MoveBy(Distance);
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Append(void) {
	m_DataSet->Append();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Insert(void) {
	m_DataSet->Insert();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Edit(void) {
	m_DataSet->Edit();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Post(void) {
	m_DataSet->Post();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::UpdateBatch(TAffectRecords AffectRecords) {
	m_DataSet->UpdateBatch(AffectRecords);
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Cancel(void) {
	m_DataSet->Cancel();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::CancelBatch(TAffectRecords AffectRecords) {
	m_DataSet->CancelBatch(AffectRecords);
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::Delete(void) {
	m_DataSet->Delete();
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::CancelUpdates(void) {
	m_DataSet->CancelUpdates();
}

// ---------------------------------------------------------------------------
bool __fastcall TZQuery::Locate(String KeyFields, Variant &KeyValues,
	TLocateOptions Options) {
	return m_DataSet->Locate(KeyFields, KeyValues, Options);
}

// ---------------------------------------------------------------------------
int __fastcall TZQuery::ExecSQL(void) {
	return m_DataSet->ExecSQL();
}

// ---------------------------------------------------------------------------
TField* __fastcall TZQuery::FieldByName(String FieldName) {
	return m_DataSet->FieldByName(FieldName);
}

// ---------------------------------------------------------------------------
TField* __fastcall TZQuery::FindField(const String FieldName) {
	return m_DataSet->FindField(FieldName);
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::LoadFromFile(String FileName) {
	m_DataSet->LoadFromFile(FileName);
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::SaveToFile(const WideString FileName,
	TPersistFormat Format) {
	m_DataSet->SaveToFile(FileName, Format);
}

// ---------------------------------------------------------------------------
TDataSource* __fastcall TZQuery::get_DataSource() {
	return m_DataSet->DataSource;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_DataSource(TDataSource* value) {
	m_DataSet->DataSource = value;
}

// ---------------------------------------------------------------------------
TADOConnection* __fastcall TZQuery::get_Connection() {
	return m_DataSet->Connection;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_Connection(TADOConnection* value) {
	m_DataSet->Connection = value;
}

// ---------------------------------------------------------------------------
bool __fastcall TZQuery::get_Active() {
	return m_DataSet->Active;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_Active(bool value) {
	m_DataSet->Active = value;
}

// ---------------------------------------------------------------------------
bool __fastcall TZQuery::get_Bof() {
	return m_DataSet->Bof;
}

// ---------------------------------------------------------------------------
bool __fastcall TZQuery::get_Eof() {
	return m_DataSet->Eof;
}

// ---------------------------------------------------------------------------
int __fastcall TZQuery::get_RowsAffected() {
	return m_DataSet->RowsAffected;
}
// ---------------------------------------------------------------------------
#ifdef VER190

TWideStrings* __fastcall TZQuery::get_SQL() {
	return m_DataSet->SQL;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_SQL(TWideStrings* value) {
	m_DataSet->SQL = value;
}
#else

TStrings* __fastcall TZQuery::get_SQL() {
	return m_DataSet->SQL;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_SQL(TStrings* value) {
	m_DataSet->SQL = value;
}
#endif

// ---------------------------------------------------------------------------
String __fastcall TZQuery::get_FilterText() {
	return m_DataSet->Filter;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_FilterText(String value) {
	m_DataSet->Filter = value;
}

// ---------------------------------------------------------------------------
bool __fastcall TZQuery::get_Filtered() {
	return m_DataSet->Filtered;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_Filtered(bool value) {
	m_DataSet->Filtered = value;
}

// ---------------------------------------------------------------------------
TADOLockType __fastcall TZQuery::get_LockType() {
	return m_DataSet->LockType;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_LockType(TADOLockType value) {
	m_DataSet->LockType = value;
}

// ---------------------------------------------------------------------------
int __fastcall TZQuery::get_CurRecNo() {
	return m_DataSet->RecNo;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_CurRecNo(int value) {
	m_DataSet->RecNo = value;
}

// ---------------------------------------------------------------------------
int __fastcall TZQuery::get_RecordCount() {
	return m_DataSet->RecordCount;
}

// ---------------------------------------------------------------------------
String __fastcall TZQuery::get_Sort() {
	return m_DataSet->Sort;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_Sort(String value) {
	m_DataSet->Sort = value;
}

// ---------------------------------------------------------------------------
TBookmark __fastcall TZQuery::get_BookmarkStr() {
	return m_DataSet->Bookmark;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_BookmarkStr(TBookmark value) {
	m_DataSet->Bookmark = value;
}

// ---------------------------------------------------------------------------
int __fastcall TZQuery::get_FieldCount() {
	return m_DataSet->FieldCount;
}

// ---------------------------------------------------------------------------
TFields* __fastcall TZQuery::get_Fields() {
	return m_DataSet->Fields;
}

// ---------------------------------------------------------------------------
Variant __fastcall TZQuery::get_FieldValue(String FieldName) {
	return m_DataSet->FieldValues[FieldName];
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_FieldValue(String FieldName, Variant value) {
	m_DataSet->FieldValues[FieldName] = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZQuery::get_Name() {
	return m_DataSet->Name;
}

// ---------------------------------------------------------------------------
void __fastcall TZQuery::set_Name(String value) {
	m_DataSet->Name = value;
}

// ---------------------------------------------------------------------------
TDataSetState __fastcall TZQuery::get_State() {
	return m_DataSet->State;
}
// ---------------------------------------------------------------------------
