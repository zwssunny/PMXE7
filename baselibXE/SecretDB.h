// ---------------------------------------------------------------------------

#ifndef SecretDBH
#define SecretDBH

#include <ADODB.hpp>
#include <Db.hpp>
const AnsiString SECRETYFILENAME = "Secret.lic";
const AnsiString SAFETYFILENAME = "safety.dll";

// ---------------------------------------------------------------------------
class PACKAGE TSecretDB {

public:
	__fastcall TSecretDB(AnsiString FileName);
	__fastcall ~TSecretDB();
	__fastcall TSecretDB();
	void __fastcall SaveToFile(AnsiString FileName);
	int __fastcall InsertRecords(TADOQuery * FQuery, AnsiString TableName);
	void __fastcall QueryRecord(TADOQuery* temQuery, AnsiString TableName);
	void __fastcall Open();
	bool __fastcall FindTable(AnsiString TableName);
	void __fastcall DeleteTable(AnsiString TableName);
	__property bool Active = {read = GetActive};
	__property TPersistFormat DataFormater = {
		read = FDataFormater, write = FDataFormater};

private:
	TADOQuery* m_Query;
	AnsiString m_TempFileName;
	bool selfCreate;
	bool IsModidfy;
	TPersistFormat FDataFormater;

	bool __fastcall GetActive();
	void __fastcall CreateSecretDB(AnsiString FileName);
	bool __fastcall CreateTableByQuery(TADOQuery *FQuery, AnsiString TableName);

};
#endif
