// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "WorkflowZClientDB.h"
#include "ClientBroker.h"
#include "ZClientQuery.h"
// 工作流采用多线程处理，每个调用过程创建的 TZClientQuery,设成线程自己释放
// 该类继承与工作流组件，工作流组件已做了修改，以适应我们开发架构
// ---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TWorkflowZClientDB::TWorkflowZClientDB(TComponent* AOwner,
	TClientBroker* AClientBroker) : TCustomWorkflowDB(AOwner) {
	FClientBroker = AClientBroker;
	// 绑定流程分类，轻量级
	DestroyQueries = true; // 需要线程释放
	logfile = NULL;
}

// ---------------------------------------------------------------------------
__fastcall TWorkflowZClientDB::~TWorkflowZClientDB() {
	if (logfile != NULL)
		fclose(logfile);
}

// ---------------------------------------------------------------------------
TDataSet* __fastcall TWorkflowZClientDB::DoCreateQuery(String SQL) {
	TZClientQuery *Q = new TZClientQuery( FClientBroker);
	Q->Close();
	Q->Params->Clear();
	Q->SQL->Text = SQL;
	return Q;
}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::DoExecuteQuery(TDataSet* Dataset) {
	TZClientQuery *Q = (TZClientQuery*)Dataset;
	// WriteLogFile(Q->SQL->Text);
   //	Q->ExecSQL();
   Q->ExecSQLByParams();
}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::DoExecuteSysQuery(TDataSet* Dataset) {
	TZClientQuery *Q = (TZClientQuery*)Dataset;
	// WriteLogFile(Q->SQL->Text);
   //	Q->SysExecSQL();
   Q->SysExecSQLByParams();
}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::DoOpenQuery(TDataSet* Dataset) {
	TZClientQuery *Q = (TZClientQuery*)Dataset;
	// WriteLogFile(Q->SQL->Text);
	Q->Open();

}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::DoOpenSysQuery(TDataSet* Dataset) {
	TZClientQuery *Q = (TZClientQuery*)Dataset;
	// String s= Q->SQL->Text;
	// WriteLogFile(Q->SQL->Text);
	Q->SysOpen();

}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::DoAssignSQLParams(TDataSet* Dataset,
	TParams* AParams) {
	TClientDataSet *Q;
	//int c;	TParam *AParam ;	Q = (TClientDataSet*)Dataset;//	Q->Params->ParseSQL(Q->SQL->Text, true);	//Q.Parameters.Assign(Params);	for (int c = 0; c<(Q->Params->Count);c++)	{		AParam = AParams->FindParam(Q->Params->Items[c]->Name);		if (AParam ==NULL)		{			wsDBError("查询语句中变量："+Q->Params->Items[c]->Name+"找不到");		}		Q->Params->Items[c]->DataType = AParam->DataType;//		Q->Params->Items[c]->Direction = pdInput;		Q->Params->Items[c]->Value = AParam->Value;		if (Q->Params->Items[c]->DataType ==ftString)			Q->Params->Items[c]->Size = Max(1, (VarToStr(Q->Params->Items[c]->Value).Length()));	}
	/* TADOQuery *Q;
	 int c;
	 TParam *AParam ;
	 TReplaceFlags rFlags;
	 rFlags<<rfReplaceAll<<rfIgnoreCase;
	 Q = (TADOQuery*)Dataset;
	 Q->Parameters->ParseSQL(Q->SQL->Text, true);
	 String SqlText=Q->SQL->Text;
	 String repStr="";
	 String repValue="";

	 //Q.Parameters.Assign(Params);
	 for (int c = 0; c<(Q->Parameters->Count);c++)
	 {
	 AParam = AParams->FindParam(Q->Parameters->Items[c]->Name);
	 if (AParam ==NULL)
	 {
	 wsDBError("查询语句中变量："+Q->Parameters->Items[c]->Name+"找不到");
	 }
	 repStr=":"+Q->Parameters->Items[c]->Name;
	 Q->Parameters->Items[c]->DataType = AParam->DataType;
	 Q->Parameters->Items[c]->Direction = pdInput;
	 Q->Parameters->Items[c]->Value = AParam->Value;
	 if (Q->Parameters->Items[c]->DataType ==ftString)
	 Q->Parameters->Items[c]->Size = Max(1, (VarToStr(Q->Parameters->Items[c]->Value).Length()));
	 switch(AParam->DataType)
	 {
	 case ftString:
	 case ftMemo:
	 case ftFixedChar:
	 case ftWideString:
	 case ftFmtMemo:
	 case ftBlob:
	 repValue=QuotedStr(AParam->Value);
	 break;
	 case ftSmallint:
	 case ftInteger:
	 case ftWord:
	 case ftFloat:
	 case ftCurrency:
	 case ftBCD:
	 case ftLargeint:
	 case ftAutoInc:
	 default:
	 repValue=AParam->Value;
	 }
	 SqlText=StringReplace(SqlText, repStr,repValue,rFlags);
	 }
	 Q->SQL->Text=SqlText; */
}

// ---------------------------------------------------------------------------
String __fastcall TWorkflowZClientDB::BlobFieldToString(TField* AField) {
	String retStr;
	int c;
	bool IsOleStr;

	if (AField->DataType == ftBlob) {
		TStringStream *StrStream = new TStringStream();
		try {
			TBlobField *BlobField = (TBlobField*)AField;
			BlobField->SaveToStream(StrStream);
			StrStream->Position = 0;
			retStr = StrStream->ReadString(StrStream->Size);
		}
		__finally {
			delete StrStream;
		}
	}
	else
		retStr = AField->AsString;

	// workaround to "tell" if the string is an Ole string}
	IsOleStr = true;
	c = 2;
	while (c < retStr.Length()) {
		if (retStr[c] != Char(0)) {
			IsOleStr = false;
			break;
		}
		c = c + 2;
	}

	// remove #0 characters
	if (IsOleStr) {
		c = 2;
		while (c < retStr.Length()) {
			retStr.Delete(c, 1);
			c++;
		}
	}
	return retStr;
}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::OpenLogFile(String prefix) {
	String filename;
	filename = ExtractFilePath(Application->ExeName) + prefix +
		TDateTime().CurrentDateTime().FormatString("yymmdd") + ".log";
	logfile = _wfopen(filename.c_str(), L"a+");
	if (logfile != NULL)
		logfile->bsize = 0;
}

// ---------------------------------------------------------------------------
void __fastcall TWorkflowZClientDB::WriteLogFile(String msg) {
	String log;
	log = "[" + TDateTime().CurrentDateTime().FormatString
		("yyyy-mm-dd hh:nn:ss") + "] " + msg + "\r\n";
	fputws(log.c_str(), logfile);
}
// ---------------------------------------------------------------------------
