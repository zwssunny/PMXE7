// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SecretDB.h"
#include "DecEnc.h"
#include "ElAES.hpp"
const AnsiString _TABLENAME_ = "tablename";
const AnsiString _TABLEDATASET_ = "tabledataset";
// ---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TSecretDB::TSecretDB(AnsiString FileName) {

	if (FileName.IsEmpty())
		throw Exception("安全文件不能为空!");
	if (!FileExists(FileName))
		throw Exception("安全文件不存在!");
	m_Query = new TADOQuery(NULL);
	m_TempFileName = FileName;
	m_Query->LoadFromFile(m_TempFileName);
	selfCreate = false;
	FDataFormater = pfADTG;
	IsModidfy = false;

}

__fastcall TSecretDB::~TSecretDB() {
	if (m_Query) {
		if (IsModidfy)
			m_Query->SaveToFile(m_TempFileName, FDataFormater);
		m_Query->Close();
		delete m_Query;
		if (selfCreate)
			DeleteFile(m_TempFileName);
	}
}

__fastcall TSecretDB::TSecretDB() {
	m_Query = new TADOQuery(NULL);
	Char tempFile[256];
	GetTempFileName(L".", L"stf", 0, tempFile);
	m_TempFileName = tempFile;
	CreateSecretDB(m_TempFileName);
	m_Query->LoadFromFile(m_TempFileName);
	selfCreate = true;
	FDataFormater = pfADTG;
	IsModidfy = true;
}

void __fastcall TSecretDB::SaveToFile(AnsiString FileName) {
	if (!Active)
		throw Exception("安全数据库未创建!");
	if (FileName.Trim().IsEmpty())
		throw Exception("保存文件名不能为空!");
	m_Query->SaveToFile(FileName, FDataFormater);
	// CopyFile(m_TempFileName.c_str(),FileName.c_str(),false);
}

bool __fastcall TSecretDB::CreateTableByQuery(TADOQuery *FQuery,
	AnsiString TableName) {
	if (FindTable(TableName))
		return false;

	Char temDataSetFile[256];
	GetTempFileName(L".", L"std", 0, temDataSetFile);
	FQuery->SaveToFile(temDataSetFile, FDataFormater);
	TADOQuery *myQuery = new TADOQuery(NULL);
	myQuery->LoadFromFile(temDataSetFile);
	myQuery->DeleteRecords(arAll);
	myQuery->SaveToFile(temDataSetFile, FDataFormater);

	m_Query->Append();
	m_Query->FieldValues[_TABLENAME_] = TableName;

	TBlobField *recordStream = (TBlobField*)m_Query->FieldByName
		(_TABLEDATASET_);
	TFileStream *fs = new TFileStream(temDataSetFile, fmOpenRead);
	TMemoryStream *ms = new TMemoryStream();
	try {
		// recordStream->LoadFromFile(temDataSetFile);
		CompressStream(fs, ms);
		recordStream->LoadFromStream(ms);
		m_Query->Post();
	}
	__finally {
		delete fs;
		delete ms;
	}

	myQuery->Close();
	delete myQuery;
	DeleteFile(temDataSetFile);
	IsModidfy = true;
	return true;
}

bool __fastcall TSecretDB::GetActive() {
	return FileExists(m_TempFileName) && m_Query->Active;
}

int __fastcall TSecretDB::InsertRecords(TADOQuery * FQuery,
	AnsiString TableName) {
	Char temDataSetFile[256];
	GetTempFileName(L".", L"std", 0, temDataSetFile);

	if (!FindTable(TableName)) {
		m_Query->Append();
		m_Query->FieldValues[_TABLENAME_] = TableName;

		TBlobField *recordStream = (TBlobField*)m_Query->FieldByName
			(_TABLEDATASET_);
		FQuery->SaveToFile(temDataSetFile, pfADTG);
		TFileStream *fs = new TFileStream(temDataSetFile, fmOpenRead);
		TMemoryStream *ms = new TMemoryStream();
		try {
			// recordStream->LoadFromFile(temDataSetFile);
			CompressStream(fs, ms);
			recordStream->LoadFromStream(ms);
			m_Query->Post();
		}
		__finally {
			delete fs;
			delete ms;
		}
		DeleteFile(temDataSetFile);
		IsModidfy = true;
		return FQuery->RecordCount;
	}
	else {
		int icount = 0;
		TLocateOptions Opts;
		Opts.Clear();
		Opts << loCaseInsensitive;
		if (!m_Query->Locate(_TABLENAME_, TableName, Opts))
			return 0;

		m_Query->Edit();
		m_Query->FieldValues[_TABLENAME_] = TableName;

		TADOQuery *myQuery = new TADOQuery(NULL);
		TBlobField *recordStream = (TBlobField*)m_Query->FieldByName
			(_TABLEDATASET_);
		recordStream->SaveToFile(temDataSetFile);
		myQuery->LoadFromFile(temDataSetFile);
		if (myQuery->RecordCount > 0) {
			FQuery->First();
			while (!FQuery->Eof) {
				icount++;
				myQuery->Append();
				for (int i = 0; i < myQuery->FieldCount; i++) {
					TField * field = myQuery->IndexFields[i];
					field->Value = FQuery->FieldValues[field->Name];
				}
				myQuery->Post();
				FQuery->Next();
			}
			myQuery->SaveToFile(temDataSetFile, pfADTG);
		}
		else {
			FQuery->SaveToFile(temDataSetFile, pfADTG);
			icount = FQuery->RecordCount;
		}
		TFileStream *fs = new TFileStream(temDataSetFile, fmOpenRead);
		TMemoryStream *ms = new TMemoryStream();
		try {
			// recordStream->LoadFromFile(temDataSetFile);
			CompressStream(fs, ms);
			recordStream->LoadFromStream(ms);
			m_Query->Post();
		}
		__finally {
			delete fs;
			delete ms;
		}
		myQuery->Close();
		delete myQuery;
		DeleteFile(temDataSetFile);
		IsModidfy = true;
		return icount;
	}
}

void __fastcall TSecretDB::QueryRecord(TADOQuery* temQuery,
	AnsiString TableName) {
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loCaseInsensitive;
	if (m_Query->Locate(_TABLENAME_, TableName, Opts)) {
		Char temDataSetFile[256];
		GetTempFileName(L".", L"std", 0, temDataSetFile);

		TBlobField *recordStream = (TBlobField*)m_Query->FieldByName
			(_TABLEDATASET_);
		TFileStream *fs = new TFileStream(temDataSetFile, fmCreate);
		TMemoryStream *ms = new TMemoryStream();
		try {
			// recordStream->LoadFromFile(temDataSetFile);
			recordStream->SaveToStream(ms);
			DecompressStream(ms, fs);
		}
		__finally {
			delete fs;
			delete ms;
		}
		temQuery->LoadFromFile(temDataSetFile);
		DeleteFile(temDataSetFile);
	}
}

void __fastcall TSecretDB::CreateSecretDB(AnsiString FileName) {
	if (FileExists(FileName))
		DeleteFile(FileName);

	TADODataSet *myDataSet = new TADODataSet(NULL);
	myDataSet->Close();

	myDataSet->FieldDefs->Clear();

	TFieldDef *pNewDef = myDataSet->FieldDefs->AddFieldDef();
	pNewDef->Name = _TABLENAME_;
	pNewDef->DataType = ftString;
	pNewDef->Size = 50;
	pNewDef->Required = true;

	pNewDef = myDataSet->FieldDefs->AddFieldDef();
	pNewDef->Name = _TABLEDATASET_;
	pNewDef->DataType = ftBlob;

	myDataSet->IndexDefs->Clear();
	myDataSet->IndexDefs->Add("tableindex", _TABLENAME_,
		TIndexOptions() << ixPrimary << ixUnique << ixCaseInsensitive);

	myDataSet->CreateDataSet();
	myDataSet->SaveToFile(FileName, pfADTG);
	IsModidfy = true;
	delete myDataSet;
}

void __fastcall TSecretDB::Open() {
	m_Query->LoadFromFile(m_TempFileName);
}

bool __fastcall TSecretDB::FindTable(AnsiString TableName) {
	if (!Active)
		return false;

	TLocateOptions Opts;
	Opts.Clear();
	Opts << loCaseInsensitive;
	TBookmark SavePlace = m_Query->GetBookmark();
	bool bfind = m_Query->Locate(_TABLENAME_, TableName, Opts);
	m_Query->GotoBookmark(SavePlace);
	m_Query->FreeBookmark(SavePlace);
	return bfind;
}

void __fastcall TSecretDB::DeleteTable(AnsiString TableName) {
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loCaseInsensitive;
	if (m_Query->Locate(_TABLENAME_, TableName, Opts)) {
		m_Query->DeleteRecords(arCurrent);
		IsModidfy = true;
	}

}
