// ---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "MBDataSet.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------

__fastcall TMBDataSet::TMBDataSet(TComponent* Owner, int dstype)
{
	m_AOwner = Owner;
	m_Handle = AllocateHWnd(WndProc);
	m_MasterDataSet = new TADOQuery(Owner);
	m_MasterDataSet->EnableBCD = false;
	m_Query = new TZQuery(Owner);
	if (dstype == 2)
	{
		m_DetailDataSet = new TADOQuery(Owner);
		m_DetailDataSet->EnableBCD = false;
		m_DetailDataSet->LockType = ltBatchOptimistic;
	}
	m_DataSetType = dstype;
	m_MasterSQLString = "";
	m_DetailSQLString = "";
	m_MasterWhereString = "";
	m_DetailWhereString = "";
	m_MasterOrderString = "";
	m_DetailOrderString = "";
	m_MasterGroupString = "";
	m_DetailGroupString = "";
	if (dstype == 2)
	{
		m_MasterLinkFields = new TStringList;
		m_DetailLinkFields = new TStringList;
	}
	m_MasterKeyFields = "";
	m_DetailKeyFields = "";
}

// ---------------------------------------------------------------------------
__fastcall TMBDataSet::~TMBDataSet()
{
	if (m_Handle)
		DeallocateHWnd(m_Handle);

	delete m_MasterDataSet;
	delete m_Query;

	if (m_DataSetType == 2)
	{
		delete m_DetailDataSet;
		delete m_MasterLinkFields;
		delete m_DetailLinkFields;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::WndProc(TMessage &Msg)
{
	Msg.Result = DefWindowProc(m_Handle, Msg.Msg, Msg.WParam, Msg.LParam);
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::InitPowerDataSet()
{
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_MasterSQLString()
{
	return m_MasterSQLString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_MasterSQLString(String value)
{
	m_MasterSQLString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_DetailSQLString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailSQLString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_DetailSQLString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailSQLString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_MasterWhereString()
{
	return m_MasterWhereString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_MasterWhereString(String value)
{
	m_MasterWhereString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_DetailWhereString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailWhereString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_DetailWhereString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailWhereString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_MasterOrderString()
{
	return m_MasterOrderString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_MasterOrderString(String value)
{
	m_MasterOrderString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_DetailOrderString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailOrderString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_DetailOrderString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailOrderString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_MasterGroupString()
{
	return m_MasterGroupString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_MasterGroupString(String value)
{
	m_MasterGroupString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_DetailGroupString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailGroupString;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_DetailGroupString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailGroupString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_MasterKeyFields()
{
	return m_MasterKeyFields;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_MasterKeyFields(String value)
{
	m_MasterKeyFields = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_DetailKeyFields()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailKeyFields;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_DetailKeyFields(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailKeyFields = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_LinkFields()
{
	if (m_DataSetType == 1)
		return "";
	else
		return BuildLinkFields();
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_LinkFields(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	ExtractLinkFields(value);
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_MasterSort()
{
	return m_MasterDataSet->Sort;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_MasterSort(String value)
{
	m_MasterDataSet->Sort = value;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_DetailSort()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Sort;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_DetailSort(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Sort = value;
}
// ---------------------------------------------------------------------------
TDataSetState __fastcall TMBDataSet::get_MasterStatus()
{
	return m_MasterDataSet->State;
}

// ---------------------------------------------------------------------------
TDataSetState __fastcall TMBDataSet::get_DetailStatus()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->State;
}
// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::get_Filter()
{
	return m_MasterDataSet->Filter;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_Filter(String value)
{
	m_MasterDataSet->Filter = value;
}
// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::get_Filtered()
{
	return m_MasterDataSet->Filtered;
}
// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_Filtered(bool value)
{
	m_MasterDataSet->Filtered = value;
	if (m_DataSetType == 2)
		BuildDetailFilter();
}
// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_DataSetType()
{
	return m_DataSetType;
}
// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::get_Bof()
{
	return m_MasterDataSet->Bof;
}
// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::get_Eof()
{
	return m_MasterDataSet->Eof;
}

// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::get_DetailBof()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Bof;
}

// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::get_DetailEof()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Eof;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_RecordCount()
{
	return m_MasterDataSet->RecordCount;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_CurRecNo()
{
	return m_MasterDataSet->RecNo;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_DetailCount()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->RecordCount;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_DetailRecNo()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->RecNo;
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Open()
{
	String sqlstr, sqlstr1;
	if (m_MasterSQLString.IsEmpty())
		throw Exception("主表SQL语句尚未赋值.");
	sqlstr = m_MasterSQLString;
	if (!m_MasterWhereString.IsEmpty())
		sqlstr += " where " + m_MasterWhereString;
	if (!m_MasterOrderString.IsEmpty())
		sqlstr += " Order by " + m_MasterOrderString;
	m_MasterDataSet->Close();
	m_MasterDataSet->SQL->Clear();
	m_MasterDataSet->SQL->Add(sqlstr);
	m_MasterDataSet->Open();
	if (m_DataSetType == 2)
	{
		if (m_DetailSQLString.IsEmpty())
			throw Exception("从表SQL语句尚未赋值.");
		if (m_MasterLinkFields->Count == 0)
			throw Exception("尚未建立关联字段.");
		sqlstr1 = m_DetailSQLString;
		sqlstr1 += " where exists(" + m_MasterSQLString;
		if (!m_MasterWhereString.IsEmpty())
			sqlstr1 += " where " + m_MasterWhereString + " and " + BuildLinkStr() + ")";
		else
			sqlstr1 += " where " + BuildLinkStr() + ")";
		if (!m_DetailWhereString.IsEmpty())
			sqlstr1 + " and " + m_DetailWhereString;
		if (!m_DetailOrderString.IsEmpty())
			sqlstr1 += " order by " + m_DetailOrderString;
		m_DetailDataSet->Close();
		m_DetailDataSet->SQL->Clear();
		m_DetailDataSet->SQL->Add(sqlstr1);
		m_DetailDataSet->Open();
		BuildDetailFilter();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::AddNew()
{
	m_MasterDataSet->Append();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Insert()
{
	m_MasterDataSet->Insert();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Edit()
{
	m_MasterDataSet->Edit();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Delete()
{
	int rc;
	if (m_DataSetType == 2)
	{
		rc = m_DetailDataSet->RecordCount;
		for (int i = 0; i < rc; i++)
		{
			m_DetailDataSet->First();
			m_DetailDataSet->Delete();
		}
		m_DetailDataSet->UpdateBatch(arAll);
	}
	m_MasterDataSet->Delete();
	if (m_DataSetType == 2)
		BuildDetailFilter();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Update()
{
	try
	{
		m_Connection->BeginTrans();
		if (m_MasterDataSet->State != dsBrowse)
		{
			m_MasterDataSet->Post();
		}
		if (m_DataSetType == 2)
			m_DetailDataSet->UpdateBatch(arAll);
		m_Connection->CommitTrans();
	}
	catch (Exception &e)
	{
		m_Connection->RollbackTrans();
		throw Exception(e.Message);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Cancel()
{
	m_MasterDataSet->Cancel();
	if (m_DataSetType == 2)
	{
		m_DetailDataSet->CancelBatch(arAll);
		BuildDetailFilter();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::AddDetail()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	BuildDetailFilter();
	m_DetailDataSet->Append();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::InserDetail()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Insert();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::EditDetail()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Edit();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::DeleteDetail()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Delete();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::UpdateDetail()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	for (int i = 0; i < m_DetailLinkFields->Count; i++)
		m_DetailDataSet->FieldValues[m_DetailLinkFields->Strings[i]] =
			m_MasterDataSet->FieldValues[m_MasterLinkFields->Strings[i]];
	m_DetailDataSet->Post();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::CancelDetail()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Cancel();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::Close()
{
	m_MasterDataSet->Close();
	if (m_DataSetType == 2)
		m_DetailDataSet->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::MoveFirst()
{
	m_MasterDataSet->First();
	if (m_DataSetType == 2)
		BuildDetailFilter();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::MoveLast()
{
	m_MasterDataSet->Last();
	if (m_DataSetType == 2)
		BuildDetailFilter();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::MoveNext()
{
	m_MasterDataSet->Next();
	if (m_DataSetType == 2)
		BuildDetailFilter();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::MovePrior()
{
	m_MasterDataSet->Prior();
	if (m_DataSetType == 2)
		BuildDetailFilter();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::MoveTo(int Distance)
{
	m_MasterDataSet->First();
	m_MasterDataSet->MoveBy(Distance);
	if (m_DataSetType == 2)
		BuildDetailFilter();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::DetailFirst()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->First();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::DetailLast()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Last();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::DetailPrior()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Prior();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::DetailNext()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Next();
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::DetailMoveTo(int Distance)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->First();
	m_DetailDataSet->MoveBy(Distance);
}

// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::LocateMaster(String KeyValues)
{
	int index, valcount;
	bool retval, isfiltered;
	String valstr, filterstr;
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loCaseInsensitive;
	valcount = 0;
	if (m_MasterDataSet->RecordCount < 1) return false;
	index = KeyValues.Pos("\t");
	if (index > 0 && index < KeyValues.Length())
	{
		Variant mv[20];
		while (index > 0)
		{
			valstr = KeyValues.SubString(1, index - 1);
			mv[valcount] = Variant(valstr);
			KeyValues.Delete(1, index);
			valcount++;
			index = KeyValues.Pos("\t");
		}
		retval = m_MasterDataSet->Locate(m_MasterKeyFields,
			VarArrayOf(mv, valcount), Opts);
		if (retval && m_DataSetType == 2)
			BuildDetailFilter();
		return retval;
	}
	else
	{
		Variant sv;
		while (KeyValues[KeyValues.Length()] == '\t')
			KeyValues.Delete(KeyValues.Length(), 1);
		sv = Variant(KeyValues);
		retval = m_MasterDataSet->Locate(m_MasterKeyFields, sv, Opts);
		if (retval && m_DataSetType == 2)
			BuildDetailFilter();
		return retval;
	}
}

// ---------------------------------------------------------------------------
bool __fastcall TMBDataSet::LocateDetail(String KeyValues)
{
	int index, valcount;
	bool retval, isfiltered;
	String valstr, filterstr;
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loCaseInsensitive;
	valcount = 0;
	if (m_DetailDataSet->RecordCount < 1)
		return false;
	index = KeyValues.Pos("\t");
	if (index > 0)
	{
		Variant mv[20];
		while (index > 0)
		{
			valstr = KeyValues.SubString(1, index - 1);
			mv[valcount] = Variant(valstr);
			KeyValues.Delete(1, index);
			valcount++;
			index = KeyValues.Pos("\t");
		}
		retval = m_DetailDataSet->Locate(m_DetailKeyFields,
			VarArrayOf(mv, valcount), Opts);
		return retval;
	}
	else
	{
		Variant sv;
		sv = Variant(KeyValues);
		retval = m_DetailDataSet->Locate(m_DetailKeyFields, sv, Opts);
		return retval;
	}
}

// ---------------------------------------------------------------------------
TField *__fastcall TMBDataSet::FindMasterField(String fieldname)
{
	return m_MasterDataSet->FindField(fieldname);
}

// ---------------------------------------------------------------------------
TField *__fastcall TMBDataSet::FindDetailField(String fieldname)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->FindField(fieldname);
}

// ---------------------------------------------------------------------------
Variant __fastcall TMBDataSet::GetMasterValue(String fieldname)
{
	return m_MasterDataSet->FieldValues[fieldname];
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::SetMasterValue(String fieldname, Variant value)
{
	m_MasterDataSet->FieldValues[fieldname] = value;
}

// ---------------------------------------------------------------------------
Variant __fastcall TMBDataSet::GetDetailValue(String fieldname)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->FieldValues[fieldname];
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::SetDetailValue(String fieldname, Variant value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->FieldValues[fieldname] = value;
}

// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::BuildLinkFields()
{
	String s;
	if (m_DataSetType == 1)
		return "";
	for (int i = 0; i < m_MasterLinkFields->Count; i++)
	{
		s += m_MasterLinkFields->Strings[i] + "=" +
			m_DetailLinkFields->Strings[i] + "\t";
	}
	return s;
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::ExtractLinkFields(String value)
{
	String s;
	int index;
	if (m_DataSetType == 1)
		return;
	index = value.Pos("=");
	m_MasterLinkFields->Clear();
	m_DetailLinkFields->Clear();
	while (index > 0)
	{
		s = value.SubString(1, index - 1).Trim();
		m_MasterLinkFields->Add(s);
		value.Delete(1, index);
		index = value.Pos("\t");
		s = value.SubString(1, index - 1);
		m_DetailLinkFields->Add(s);
		value.Delete(1, index);
		index = value.Pos("=");
	}
}

// ---------------------------------------------------------------------------
String __fastcall TMBDataSet::BuildLinkStr()
{
	String s;
	if (m_DataSetType == 1)
		return "";
	for (int i = 0; i < m_MasterLinkFields->Count; i++)
	{
		s += m_MasterLinkFields->Strings[i] + "=" +
			m_DetailLinkFields->Strings[i];
		if (i < m_MasterLinkFields->Count - 1)
			s += " and ";
	}
	return s;
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::BuildDetailFilter()
{
	String filterstr;
	int ftype;
	for (int i = 0; i < m_MasterLinkFields->Count; i++)
	{
		ftype = CheckFieldType(m_DetailDataSet->Fields->FieldByName
			(m_DetailLinkFields->Strings[i]));
		if (ftype == 1)
			filterstr += m_DetailLinkFields->Strings[i] + "='" +
				m_MasterDataSet->FieldByName(m_MasterLinkFields->Strings[i])
				->AsString + "'";
		else
			filterstr += m_DetailLinkFields->Strings[i] + "=" +
				m_MasterDataSet->FieldByName(m_MasterLinkFields->Strings[i])
				->AsString;
		if (i < m_MasterLinkFields->Count - 1)
			filterstr += " and ";
	}
	m_DetailDataSet->Filtered = false;
	m_DetailDataSet->Filter = filterstr;
	m_DetailDataSet->Filtered = true;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::CheckFieldType(TField *Field)
{
	switch (Field->DataType)
	{
	case ftString:
	case ftDate:
	case ftTime:
	case ftDateTime:
	case ftMemo:
	case ftFixedChar:
	case ftWideString:
		return 1;
	case ftSmallint:
	case ftInteger:
	case ftBoolean:
	case ftBytes:
	case ftWord:
	case ftFloat:
	case ftCurrency:
		return 2;
	default:
		return 0;
	}
}

// ---------------------------------------------------------------------------
TADOConnection *__fastcall TMBDataSet::get_Connection()
{
	return m_Connection;
}

// ---------------------------------------------------------------------------
void __fastcall TMBDataSet::set_Connection(TADOConnection *value)
{
	m_Connection = value;
	m_MasterDataSet->Connection = value;
	m_Query->Connection = value;
	if (m_DataSetType == 2)
		m_DetailDataSet->Connection = value;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_MasterFieldCount()
{
	return m_MasterDataSet->FieldCount;
}

// ---------------------------------------------------------------------------
int __fastcall TMBDataSet::get_DetailFieldCount()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->FieldCount;
}

// ---------------------------------------------------------------------------
TFields *__fastcall TMBDataSet::get_MasterFields()
{
	return m_MasterDataSet->Fields;
}

// ---------------------------------------------------------------------------
TFields *__fastcall TMBDataSet::get_DetailFields()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Fields;
}
// ---------------------------------------------------------------------------
