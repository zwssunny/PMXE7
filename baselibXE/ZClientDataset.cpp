// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "ZClientDataset.h"
#include "DSClientProxy.h"
#include "SetAllFieldCanModify.h"
#include "SHConst.h"
#include "fsScreenCursor.h"
#define _TimeOuts 60       //秒
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TZClientDataSet::TZClientDataSet(TComponent* Owner,TClientBroker *FBroker, String AClassCode)
{

	FClientBroker = FBroker;
	FClientBroker->AddClientDataSet(this);
	m_ClassCode = AClassCode;
	FClientDataSetAfterScroll = NULL;

	m_MasterDataSet = new TDataSnapClientDataSet(NULL);
	m_MasterDataSet->AfterScroll = MasterDataSetAfterScroll; // zws20090220

	FQuery = new TDataSnapClientDataSet(NULL);

	m_MasterStructure = new TDataSnapClientDataSet(NULL);


	m_DetailStructure = new TDataSnapClientDataSet(NULL);

// 0-等待返回消息,1-正常返回,2-错误返回,3-超时返回
	dsOperateStatus = 0;
	ZDataSetErrorMessage = "";

	m_DataSetActive = false;
	m_MasterSQLString = "";
	m_DetailSQLString = "";
	m_MasterWhereString = "";
	m_DetailWhereString = "";
	m_MasterOrderString = "";
	m_DetailOrderString = "";
	m_MasterGroupString = "";
	m_DetailGroupString = "";
	m_MasterKeyFields = "";
	m_DetailKeyFields = "";
	m_ServerDataSetHandle = 0;
	m_MasterDisplayName  = new TStringList;
	m_MasterDisplayField = new TStringList;
	m_MasterFilterFields = new TStringList;
	m_DetailFilterFields = new TStringList;
	m_MasterFieldAttr    = new TStringList;
	m_DetailFieldAttr    = new TStringList;
	m_MasterFieldExpr    = new TStringList;
	m_DetailFieldExpr    = new TStringList;
	m_MasterAttrType     = new TStringList;
	m_DetailAttrType     = new TStringList;
	m_DataSetType = 1;
	m_TimeOut = 30000;
	m_NeedValid = false;
	m_MasterValidFieldList = "";
	m_DetailValidFieldList = "";

	m_Query = new TZClientQuery(Owner, FBroker);
	InitServerDataSet();
}
// ---------------------------------------------------------------------------
__fastcall TZClientDataSet::~TZClientDataSet()
{
	ClientDataSetTerminate(NULL);
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::ClientDataSetTerminate(TObject *Sender)
{
	if(FClientBroker)
	{
		FreeServerDataSet();
		FClientBroker->DeleteClientDataSet(this);
	}


	delete m_Query;
	delete m_MasterStructure;
	delete m_DetailStructure;

	delete m_MasterDataSet;
	delete FQuery;
	delete m_MasterDisplayName;
	delete m_MasterDisplayField;
	delete m_MasterFilterFields;
	delete m_DetailFilterFields;
	delete m_MasterFieldAttr;
	delete m_DetailFieldAttr;
	delete m_MasterFieldExpr;
	delete m_DetailFieldExpr;
	delete m_MasterAttrType;
	delete m_DetailAttrType;

	if(m_DataSetType == 2)
	{
		delete m_DetailDataSet;
		delete m_MasterLinkFields;
		delete m_DetailLinkFields;
		delete m_DetailDisplayName;
		delete m_DetailDisplayField;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::InitServerDataSet()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	ServerDataSet = new TServerDataSetClient(FClientBroker->DBXConnection,false);
	TStream *sm=NULL;
	TMsgStream *mStream = new TMsgStream();
	try
	{
		sm=ServerDataSet->GetInitResult(m_ClassCode);
		mStream->LoadFromStream(sm);
		InitClientDataSet(mStream);
		CheckResultStatus(dsOperateStatus);
  }
  __finally
  {
	  delete mStream;
	  delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::FreeServerDataSet()
{
//delete ServerDataSet;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::InitClientDataSet(TMsgStream *stream)
{
	String s1, s2, len1;
	TZClientQuery *AClientQuery;
	int pos1;
	try
	{
		m_ServerDataSetHandle = stream->ServerID;

		if (stream->ValueAttribute["status"] == "s")
		{
			m_DataSetType = stream->ValueAttribute["datasettype"].ToInt();
			m_MasterDisplayName->Text  = stream->ValueAttribute["masterdisplayname"];
			m_MasterDisplayField->Text = stream->ValueAttribute["masterdisplayfield"];
			m_MasterFilterFields->Text = stream->ValueAttribute["masterfilterfields"];
			m_DetailFilterFields->Text = stream->ValueAttribute["detailfilterfields"];
			m_MasterFieldAttr->Text    = stream->ValueAttribute["masterfieldattr"];
			m_DetailFieldAttr->Text    = stream->ValueAttribute["detailfieldattr"];

			m_MasterSQLString          = stream->ValueAttribute["mastersqlstring"];
			m_MasterFixedWhereString   = stream->ValueAttribute["masterFixedwhere"];
			m_MasterFixedOrderString   = stream->ValueAttribute["masterFixedorder"];
			m_MasterFixedGroupString   = stream->ValueAttribute["masterfixedgroup"];
			m_DetailSQLString          = stream->ValueAttribute["detailsqlstring"];
			m_DetailFixedWhereString   = stream->ValueAttribute["detailFixedwhere"];
			m_DetailFixedOrderString   = stream->ValueAttribute["detailFixedorder"];
			m_DetailFixedGroupString   = stream->ValueAttribute["detailfixedgroup"];

			s1 = stream->ItemAttribute["masterfieldexpr"];
			pos1 = 0;
			while (pos1 < s1.Length())
			{
				len1.SetLength(4);
				len1=s1.SubString0(pos1,4);
			   //	wcsncpy(len1.c_str(), s1.c_str() + pos1, 4);
				s2.SetLength(len1.ToInt());
				pos1 += 4;
				s2=s1.SubString0(pos1,len1.ToInt());
			   //	wmemcpy(s2.c_str(), (s1.c_str() + pos1), len1.ToInt());
				pos1 += len1.ToInt();
				m_MasterFieldExpr->Add(s2);
			}
			s1 = stream->ItemAttribute["detailfieldexpr"];
			pos1 = 0;
			while (pos1 < s1.Length())
			{
				len1.SetLength(4);
				len1=s1.SubString0(pos1,4);
			   //	wcsncpy(len1.c_str(), s1.c_str() + pos1, 4);
				s2.SetLength(len1.ToInt());
				pos1 += 4;
				s2=s1.SubString0(pos1,len1.ToInt());
			   //	wmemcpy(s2.c_str(), (s1.c_str() + pos1), len1.ToInt());
				pos1 += len1.ToInt();
				m_DetailFieldExpr->Add(s2);
			}
			m_MasterAttrType->Text = stream->ValueAttribute["masterattrtype"];
			m_DetailAttrType->Text = stream->ValueAttribute["detailattrtype"];
			m_MasterKeyFields = stream->ValueAttribute["masterkeyfields"];

			stream->SaveMasterToDataSet(m_MasterDataSet);
		   //	stream->SaveMasterToDataSet(m_MasterStructure);
			SetAllFieldCanModify(m_MasterDataSet);

		   //	SetAllFieldCanModify(m_MasterStructure);
			SetDataSetDisplayName(m_MasterDataSet, m_MasterDisplayName,	m_MasterDisplayField);
			m_MasterStructure->Data= m_MasterDataSet->Data;

			if (m_DataSetType == 2)
			{
				m_DetailDataSet = new TDataSnapClientDataSet(NULL);
				m_MasterLinkFields = new TStringList;
				m_DetailLinkFields = new TStringList;
				m_DetailDisplayName = new TStringList;
				m_DetailDisplayField = new TStringList;
				m_DetailKeyFields = stream->ValueAttribute["detailkeyfields"];
				m_MasterLinkFields->Text = stream->ItemAttribute["masterlinkfields"];
				m_DetailLinkFields->Text = stream->ItemAttribute["detaillinkfields"];
				m_DetailDisplayName->Text = stream->ValueAttribute["detaildisplayname"];
				m_DetailDisplayField->Text = stream->ValueAttribute["detaildisplayfield"];


				stream->SaveDetailToDataSet(m_DetailDataSet);
			   //	stream->SaveDetailToDataSet(m_DetailStructure);

				SetAllFieldCanModify(m_DetailDataSet);

			   //	SetAllFieldCanModify(m_DetailStructure);
				SetDataSetDisplayName(m_DetailDataSet, m_DetailDisplayName, m_DetailDisplayField);
				m_DetailStructure->Data= m_DetailDataSet->Data;
			}
			m_DataSetActive = true;
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"初始化数据集失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynOpen(TMsgStream *stream)
{
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			stream->SaveMasterToDataSet(m_MasterDataSet);
			SetAllFieldCanModify(m_MasterDataSet);
			SetDataSetDisplayName(m_MasterDataSet, m_MasterDisplayName, m_MasterDisplayField);
			if(m_DataSetType == 2)
			{
				m_DetailDataSet->Filtered = false;
				stream->SaveDetailToDataSet(m_DetailDataSet);
				SetAllFieldCanModify(m_DetailDataSet);
				SetDataSetDisplayName(m_DetailDataSet, m_DetailDisplayName, m_DetailDisplayField);
			}
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"打开数据集失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynUpdate(TMsgStream *stream)
{
	int FCurRecNo;
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			String sFieldName="";
			m_MasterDataSet->DisableControls();
			try
			{
				stream->SaveMasterToDataSet(FQuery);
				if(m_MasterDataSet->State == dsBrowse)
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
					{
						sFieldName = FQuery->Fields->Fields[i]->FieldName;
						m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
					}
					FQuery->Close();
					m_MasterDataSet->Post();
				}
				else
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
					{
						sFieldName = FQuery->Fields->Fields[i]->FieldName;
						m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
					}
					FQuery->Close();
					m_MasterDataSet->Post();
				}
				m_MasterDataSet->MergeChangeLog();
			}
			__finally
			{
				m_MasterDataSet->EnableControls();
			}

			if(m_DataSetType == 2)
			{
				m_DetailDataSet->DisableControls();
				try
				{
					stream->SaveDetailToDataSet(FQuery);
					FQuery->First();
					FCurRecNo = m_DetailDataSet->RecNo;
					m_DetailDataSet->First();
					while (!FQuery->Eof)
					{
						TUpdateStatus dupdatestatus= FQuery->UpdateStatus();
						if(dupdatestatus==usModified || dupdatestatus==usInserted)
						{
							m_DetailDataSet->Edit();
							for (int i = 0; i < FQuery->FieldCount; i++)
							{
								sFieldName = FQuery->Fields->Fields[i]->FieldName;
								if(!FQuery->FieldByName(sFieldName)->IsNull)
									m_DetailDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
							}
							m_DetailDataSet->Post();
						}
						FQuery->Next();
						m_DetailDataSet->Next();
					}
					FQuery->Close();
					m_DetailDataSet->MergeChangeLog();
					if(FCurRecNo <= m_DetailDataSet->RecordCount)
						m_DetailDataSet->RecNo = FCurRecNo;
				}
				__finally
				{
					m_DetailDataSet->EnableControls();
				}
			}
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"更新数据失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynDelete(TMsgStream *stream)
{
	try
	{
		if(stream->ValueAttribute["status"] == "s")
			dsOperateStatus = 1;
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = "删除数据失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynDeleteDetail(TMsgStream *stream)
{
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			// 这里需返回主表记录
			m_DetailDataSet->Delete();
			m_DetailDataSet->MergeChangeLog();
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"删除明细数据失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynCheck(TMsgStream *stream)
{
	int FCurRecNo;
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			String sFieldName="";
			stream->SaveMasterToDataSet(FQuery);
			if(m_MasterDataSet->State == dsBrowse)
			{
				m_MasterDataSet->Edit();
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			else
			{
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
			}
			dsOperateStatus = 1;
		}
		else
		{
			m_MasterDataSet->Cancel();
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"审核数据操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynCloseOff(TMsgStream *stream)
{
	int FCurRecNo;
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			String sFieldName="";
			stream->SaveMasterToDataSet(FQuery);
			if(m_MasterDataSet->State == dsBrowse)
			{
				m_MasterDataSet->Edit();
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			else
			{
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
			}
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"结清数据操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynRevoke(TMsgStream *stream)
{
	int FCurRecNo;
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			String sFieldName="";
			stream->SaveMasterToDataSet(FQuery);
			if(m_MasterDataSet->State == dsBrowse)
			{
				m_MasterDataSet->Edit();
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			else
			{
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
			}
			if (m_DataSetType == 2)
			{
				stream->SaveDetailToDataSet(FQuery);
				FQuery->First();
				FCurRecNo = m_DetailDataSet->RecNo;
				m_DetailDataSet->First();
				while (!FQuery->Eof)
				{
					if(m_DetailDataSet->State == dsBrowse)
						m_DetailDataSet->Edit();

					for (int i = 0; i < FQuery->FieldCount; i++)
					{
						sFieldName = FQuery->Fields->Fields[i]->FieldName;
						m_DetailDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
					}
					m_DetailDataSet->Post();
					FQuery->Next();
					m_DetailDataSet->Next();
				}
				FQuery->Close();
				m_DetailDataSet->MergeChangeLog();
				if(m_DetailDataSet->RecordCount >= FCurRecNo)
					m_DetailDataSet->RecNo = FCurRecNo;
			}
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"作废数据操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynTally(TMsgStream *stream)
{
	int FCurRecNo;
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			String sFieldName="";
			stream->SaveMasterToDataSet(FQuery);
			if(m_MasterDataSet->State == dsBrowse)
			{
				m_MasterDataSet->Edit();
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			else
			{
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
			}

			if(m_DataSetType == 2)
			{
				stream->SaveDetailToDataSet(FQuery);
				FQuery->First();
				FCurRecNo = m_DetailDataSet->RecNo;
				m_DetailDataSet->First();
				while (!FQuery->Eof)
				{
					if(m_DetailDataSet->State == dsBrowse)
						m_DetailDataSet->Edit();

					for (int i = 0; i < FQuery->FieldCount; i++)
					{
						sFieldName = FQuery->Fields->Fields[i]->FieldName;
						m_DetailDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
					}
					m_DetailDataSet->Post();
					FQuery->Next();
					m_DetailDataSet->Next();
				}
				FQuery->Close();
				m_DetailDataSet->MergeChangeLog();
				if(m_DetailDataSet->RecordCount >= FCurRecNo)
					m_DetailDataSet->RecNo = FCurRecNo;
			}
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"记账数据操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynCmdExec(TMsgStream *stream)
{
	int FCurRecNo;
	try
	{
		if(stream->ValueAttribute["status"] == "s")
		{
			String sFieldName="";
			stream->SaveMasterToDataSet(FQuery);
			if(m_MasterDataSet->State == dsBrowse)
			{
				m_MasterDataSet->Edit();
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			else
			{
				for (int i = 0; i < FQuery->FieldCount; i++)
				{
					sFieldName = FQuery->Fields->Fields[i]->FieldName;
					m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
				}
				FQuery->Close();
			}

			if(m_DataSetType == 2)
			{
				stream->SaveDetailToDataSet(FQuery);
				FQuery->First();
				FCurRecNo = m_DetailDataSet->RecNo;
				m_DetailDataSet->First();
				while (!FQuery->Eof)
				{
					if(m_DetailDataSet->State == dsBrowse)
						m_DetailDataSet->Edit();

					for (int i = 0; i < FQuery->FieldCount; i++)
					{
						sFieldName = FQuery->Fields->Fields[i]->FieldName;
						m_DetailDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
					}
					m_DetailDataSet->Post();
					FQuery->Next();
					m_DetailDataSet->Next();
				}
				FQuery->Close();
				m_DetailDataSet->RecNo = FCurRecNo;
			}
			dsOperateStatus = 1;
		}
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"通用数据操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynValidateData(TMsgStream *stream)
{
	try
	{
		if(stream->ValueAttribute["status"] == "s")
			dsOperateStatus = 1;
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"校验数据操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AsynExecSQL(TMsgStream *stream)
{
	try
	{
		if(stream->ValueAttribute["status"] == "s")
			dsOperateStatus = 1;
		else
		{
			ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
			dsOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = L"执行SQL操作失败，错误：" + e.Message;
		dsOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::RecvErrorMessage(TMsgStream *stream)
{
	try
	{
		ZDataSetErrorMessage = stream->ItemAttribute["errormessage"];
		dsOperateStatus = 2;
	}
	catch (Exception &e)
	{
	}
}
// ---------------------------------------------------------------------------
/*
void __fastcall TZClientDataSet::ValidField(TValidType vt,TValidAffect va)
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs= new TMsgStream();
	TStream *sm=NULL;
	TMemoryStream *rmsStream=new TMemoryStream();
	String sFieldName="";
	int rc;
	bool FCurEnabled;//new
	try
	{
		if(m_DataSetActive)
		{
			if(m_DataSetType==1 &&(vt==vtDetail || vt==vtMasterDetail))
				throw Exception("当前系统是单表状态,校验类型设置不正确.");

			if(vt==vtMaster)
				va = vaCurRecNo;

			if(vt==vtMasterDetail)
				va = vaAll;

			if(vt==vtDetail && va==vaCurRecNo)
				rc = m_DetailDataSet->RecNo;

			sxs->Operate = asDSVerify;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["datasettype"]  = m_DataSetType;
			sxs->ValueAttribute["masterstatus"] = m_MasterDataSet->State;

			if(m_NeedValid)
				sxs->ItemAttribute["needvalid"] = "t";
			else
				sxs->ItemAttribute["needvalid"] = "f";

			sxs->ItemAttribute["validtype"]   = vt;
			sxs->ItemAttribute["validaffect"] = va;
			sxs->ItemAttribute["validrecno"]  = rc;
			sxs->ItemAttribute["mastervalidfieldlist"] = BuildValidList(m_MasterValidFieldList);
			sxs->ItemAttribute["detailvalidfieldlist"] = BuildValidList(m_DetailValidFieldList);
//			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
//			datasetStream->SaveToDataSet(FQuery);
//			delete datasetStream;
			FQuery->Data= m_MasterStructure->Data;
			FQuery->Append();
			for(int i=0;i<m_MasterDataSet->FieldCount;i++)
			{
				sFieldName = m_MasterDataSet->Fields->Fields[i]->FieldName;
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(sFieldName),m_MasterDataSet->Fields->Fields[i]);
				else
				  FQuery->FieldValues[sFieldName] = m_MasterDataSet->FieldValues[sFieldName];
			}
			FQuery->Post();
			sxs->LoadMasterFromDataSet(FQuery);

			if(m_DataSetType==2)
				sxs->LoadDetailFromDataSet(m_DetailDataSet);

			dsOperateStatus = 0;
			sxs->SaveToStream(rmsStream);
			sm = ServerDataSet->ValidateData(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynValidateData(sxs);
			CheckResultStatus(dsOperateStatus);
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete sxs;
		delete ScreenCursor;
		delete rmsStream;
	}
}  */
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Open()
{
	TfsScreenCursor * ScreenCursor= new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm = NULL;
	TMemoryStream *rmsStream = new TMemoryStream();
	try
	{
       	dsOperateStatus = 0;
		sxs->Operate = asDSOpen;
		sxs->ClassID = m_ClassCode;
		sxs->ValueAttribute["masterwhere"] = m_MasterWhereString;
		sxs->ValueAttribute["masterorder"] = m_MasterOrderString;
		sxs->ValueAttribute["detailwhere"] = m_DetailWhereString;
		sxs->ValueAttribute["detailorder"] = m_DetailOrderString;
		sxs->SaveToStream(rmsStream);
		rmsStream->Position = 0;
		sm = ServerDataSet->Open(rmsStream,m_ClassCode);
		sxs->LoadFromStream(sm);
		AsynOpen(sxs);
		CheckResultStatus(dsOperateStatus);
	}
	__finally
	{
		delete sxs;
		delete rmsStream;
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AddNew()
{
	if(m_DataSetActive)
	{
		if(m_MasterDataSet->State != dsBrowse)
			throw Exception(L"系统正处于编辑状态!");

		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->State != dsBrowse)
				throw Exception(L"系统从表正处于编辑状态!");
		}

		m_MasterDataSet->Append();
//		if(m_DataSetType == 2)
//		{
//			BuildDetailFilter();
//		}
	}
	else
	{
		throw Exception(L"系统尚未初始化.");
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Insert()
{
	if(m_DataSetActive)
	{
		if(m_MasterDataSet->State != dsBrowse)
			throw Exception(L"系统正处于编辑状态!");

		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->State != dsBrowse)
				throw Exception(L"系统从表正处于编辑状态!");
		}
		m_MasterDataSet->Insert();
	}
	else
	{
		throw Exception(L"系统尚未初始化.");
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Edit()
{
	if(m_DataSetActive)
	{
		if(m_MasterDataSet->State != dsBrowse)
			throw Exception(L"系统正处于编辑状态!");

		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->State != dsBrowse)
				throw Exception(L"系统从表正处于编辑状态!");
		}
		m_MasterDataSet->Edit();
	}
	else
	{
		throw Exception(L"系统尚未初始化.");
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Delete()
{
	String sFieldName="";
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TMemoryStream *rmsStream = new TMemoryStream();
	TStream *sm = NULL;
	int rc;
	bool FCurEnabled;

	try
	{
		if(m_DataSetActive)
		{
			if(m_MasterDataSet->State != dsBrowse)
				throw Exception(L"系统正处于编辑状态!");

			if(m_DataSetType == 2)
			{
				if(m_DetailDataSet->State != dsBrowse)
					throw Exception(L"系统子表正处于编辑状态!");
			}

			if(m_MasterDataSet->RecordCount < 1)
				throw Exception(L"没有记录可删除.");

			sxs->Operate = asDSDelete;
			sxs->ClassID = m_ClassCode;

			FQuery->Data= m_MasterStructure->Data;//复制表结构
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				sFieldName = m_MasterDataSet->Fields->Fields[i]->FieldName;
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(sFieldName), m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[sFieldName] = m_MasterDataSet->FieldValues[sFieldName];
			}
			FQuery->Post();

			sxs->LoadMasterFromDataSet(FQuery);
			FQuery->Close();

			if(m_DataSetType == 2)
				sxs->LoadDetailFromDataSet(m_DetailDataSet);

			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm = ServerDataSet->Delete(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynDelete(sxs);
			CheckResultStatus(dsOperateStatus);
			if(m_DataSetType == 2)
			{
				rc = m_DetailDataSet->RecordCount;
				for (int i = 0; i < rc; i++)
				{
					m_DetailDataSet->First();
					m_DetailDataSet->Delete();
				}
				m_DetailDataSet->MergeChangeLog();
			}
			m_MasterDataSet->Delete();
			m_MasterDataSet->MergeChangeLog();
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
		delete rmsStream;
		delete sxs;
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Update()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	String sFieldName;
	TMemoryStream *rmsStream = new TMemoryStream;
	TStream *sm=NULL;
	TValidType vt;
	TValidAffect va;
	int rc;
	bool FCurEnabled;

	TDataSetNotifyEvent MBeforePost, MAfterPost, DBeforePost, DAfterPost;
	try
	{
		MBeforePost = m_MasterDataSet->BeforePost;
		MAfterPost  = m_MasterDataSet->AfterPost;
		m_MasterDataSet->BeforePost = NULL;
		m_MasterDataSet->AfterPost  = NULL;
		if(m_DataSetType == 2)
		{
			DBeforePost = m_DetailDataSet->BeforePost;
			DAfterPost  = m_DetailDataSet->AfterPost;
			m_DetailDataSet->BeforePost = NULL;
			m_DetailDataSet->AfterPost  = NULL;
		}

		if(m_DataSetActive)
		{
			if(m_MasterDataSet->State == dsInsert || m_MasterDataSet->State == dsBrowse)
			{
				sxs->Operate = asDSUpdate;
				sxs->ClassID = m_ClassCode;
				sxs->ValueAttribute["datasettype"]  = m_DataSetType;
				sxs->ValueAttribute["masterstatus"] = m_MasterDataSet->State;
				rc = 1;
				if(m_DataSetType == 1)
				{
					va = vaCurRecNo;
					vt = vtMaster;
				}
				else
				{
					va = vaAll;
					if(m_MasterDataSet->State == dsInsert)
						vt = vtMasterDetail;
					else
						vt = vtDetail;
				}

				if(m_NeedValid)
					sxs->ItemAttribute["needvalid"] = "t";
				else
					sxs->ItemAttribute["needvalid"] = "f";

				sxs->ItemAttribute["validtype"]   = vt;
				sxs->ItemAttribute["validaffect"] = va;
				sxs->ItemAttribute["validrecno"]  = rc;
				sxs->ItemAttribute["mastervalidfieldlist"] = BuildValidList(m_MasterValidFieldList);
				sxs->ItemAttribute["detailvalidfieldlist"] = BuildValidList(m_DetailValidFieldList);

				FQuery->Data= m_MasterStructure->Data;//复制表结构
				FQuery->Append();
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					sFieldName = m_MasterDataSet->Fields->Fields[i]->FieldName;
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(sFieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[sFieldName] = m_MasterDataSet->FieldValues[sFieldName];
				}
				FQuery->Post();

				sxs->LoadMasterFromDataSet(FQuery);
				FQuery->Close();
			}
			else if(m_MasterDataSet->State == Db::dsEdit)
			{
				sxs->Operate = asDSUpdate;
				sxs->ClassID = m_ClassCode;
				sxs->ValueAttribute["datasettype"] = m_DataSetType;
				sxs->ValueAttribute["masterstatus"] = m_MasterDataSet->State;
				rc = 1;
				va = vaCurRecNo;
				vt = vtMaster;
				if(m_NeedValid)
					sxs->ItemAttribute["needvalid"] = "t";
				else
					sxs->ItemAttribute["needvalid"] = "f";
				sxs->ItemAttribute["validtype"]   = vt;
				sxs->ItemAttribute["validaffect"] = va;
				sxs->ItemAttribute["validrecno"]  = rc;
				sxs->ItemAttribute["mastervalidfieldlist"] = BuildValidList(m_MasterValidFieldList);
				sxs->ItemAttribute["detailvalidfieldlist"] = BuildValidList(m_DetailValidFieldList);

				FQuery->Data= m_MasterStructure->Data;//复制表结构
				// 数据集LockType在ltBatchOptimistic模式下，先新增旧值再编辑，就会产生Old记录
				FQuery->Append();
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					sFieldName = m_MasterDataSet->Fields->Fields[i]->FieldName;
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(sFieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[sFieldName] = m_MasterDataSet->FieldByName(sFieldName)->OldValue;
				}
				FQuery->Post();
				FQuery->MergeChangeLog();

				FQuery->Edit();
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					sFieldName = m_MasterDataSet->Fields->Fields[i]->FieldName;
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(sFieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[sFieldName] = m_MasterDataSet->FieldValues[sFieldName];
				}
				FQuery->Post();

				sxs->LoadMasterFromDataSet(FQuery);
				FQuery->Close();
			}

			if(m_DataSetType == 2)
				sxs->LoadDetailFromDataSet(m_DetailDataSet);

			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm = ServerDataSet->Update(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynUpdate(sxs);
			CheckResultStatus(dsOperateStatus);
		}
		else
		{
			throw Exception(L"系统尚未初始化.");
		}
	}
	__finally
	{
		delete sxs;
		delete rmsStream;
		m_MasterDataSet->BeforePost = MBeforePost;
		m_MasterDataSet->AfterPost  = MAfterPost;
		if(m_DataSetType == 2)
		{
			m_DetailDataSet->BeforePost = DBeforePost;
			m_DetailDataSet->AfterPost  = DAfterPost;
		}
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Cancel()
{
	if (m_DataSetActive)
	{
		if ((m_DataSetType == 2)&&(m_DetailDataSet->State!=dsBrowse))
		{
		   m_DetailDataSet->Cancel();
//			if (m_DetailDataSet->RecordCount > 0)
//			{
//				m_DetailDataSet->CancelUpdates();
//			}
		}
		m_MasterDataSet->Cancel();  //CancelUpdates();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::AddDetail()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
//		m_DetailDataSet->Sort = "";
		// BuildDetailFilter();
		m_DetailDataSet->Append();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::InserDetail()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
//		m_DetailDataSet->Sort = "";
//		BuildDetailFilter();
		m_DetailDataSet->Insert();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::EditDetail()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

		if (m_DetailDataSet->State != dsBrowse)
			throw Exception(L"系统从表正处于编辑状态!");

		m_DetailDataSet->Edit();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DeleteDetail()
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	String s;
	TMemoryStream *rmsStream=new TMemoryStream();
	int rc, index;
	bool FCurEnabled; // new
	// HWND FCurWnd;
	try
	{
		// FCurWnd=GetActiveWindow();
		if (m_DataSetActive)
		{
			if (m_DataSetType == 1)
				throw Exception(L"当前系统为单表状态.");

			if (m_DetailDataSet->State != dsBrowse)
				throw Exception(L"系统从表正处于编辑状态!");

			if (m_DetailDataSet->RecordCount < 1)
				throw Exception(L"没有记录可删除.");

			if (m_MasterDataSet->State == dsBrowse)
			{
			//主表在非编辑状态直接删除 ,提交后台服务
//				 TUpdateStatus dupdatestatus= m_DetailDataSet->UpdateStatus();
//				if (dupdatestatus==usInserted || dupdatestatus==usModified
//					|| dupdatestatus==usDeleted)

				{

					sxs->Operate = asDSDeleteDetail;
					sxs->ClientID = String((int)this);
					sxs->ServerID = m_ServerDataSetHandle;
					sxs->ClassID = m_ClassCode;

					FQuery->Data= m_DetailStructure->Data;//复制表结构
					FQuery->Append();
					for (int i = 0; i < m_DetailDataSet->FieldCount; i++)
					{
						if (m_DetailDataSet->Fields->Fields[i]->IsNull)
						{
							SetNullFieldValue(FQuery->FieldByName(m_DetailDataSet->Fields->Fields[i]->FieldName), m_DetailDataSet->Fields->Fields[i]);
						}
						else
							FQuery->FieldValues[m_DetailDataSet->Fields->Fields[i]->FieldName] = m_DetailDataSet->FieldByName(m_DetailDataSet->Fields->Fields[i]->FieldName)->OldValue;
					}
					FQuery->Post();
					sxs->LoadDetailFromDataSet(FQuery);
					sxs->SaveToStream(rmsStream);
					rmsStream->Position=0;
					sm=ServerDataSet->DeleteDetail(rmsStream,m_ClassCode);
					sxs->LoadFromStream(sm);
					AsynDeleteDetail(sxs);
					CheckResultStatus(dsOperateStatus);
				}
//				else
//				{
//					m_DetailDataSet->Delete();
//				}
			}
			else
			{
				m_DetailDataSet->Delete();
			}
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
	   delete sxs;
	   delete rmsStream;
	   delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::UpdateDetail()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

	   int	value = m_DetailDataSet->State;
		for (int i = 0; i < m_DetailLinkFields->Count; i++)
			m_DetailDataSet->FieldValues[m_DetailLinkFields->Strings[i]] = m_MasterDataSet->FieldValues[m_MasterLinkFields->Strings[i]];
		m_DetailDataSet->Post();

//		if (m_DetailDataSet->RecordCount <= 1)
//		{
//			BuildDetailFilter(); // 该语句会造成回到第一条 ,所以不是新增就不再过滤处理
//		}
//
//		if (value == dsInsert)
//			m_DetailDataSet->RecNo = m_DetailDataSet->RecordCount;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::CancelDetail()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		m_DetailDataSet->Cancel();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Close()
{
	if (m_DataSetActive)
	{
		m_MasterDataSet->Sort="";
		m_MasterDataSet->Close();
		m_MasterDataSet->Data=m_MasterStructure->Data;
		if (m_DataSetType == 2)
		{
            m_DetailDataSet->Sort="";
			m_DetailDataSet->Close();
			m_DetailDataSet->Data=m_DetailStructure->Data;
		}
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::MoveFirst()
{
	if(m_DataSetActive)
		m_MasterDataSet->First();
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::MoveLast()
{
	if(m_DataSetActive)
		m_MasterDataSet->Last();
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::MoveNext()
{
	if(m_DataSetActive)
		m_MasterDataSet->Next();
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::MovePrior()
{
	if(m_DataSetActive)
		m_MasterDataSet->Prior();
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::MoveTo(int Distance)
{
	if (m_DataSetActive)
	{
		if (Distance < 1 || Distance > m_MasterDataSet->RecordCount)
			throw Exception(L"主表数据集指针移动越界");

		m_MasterDataSet->RecNo = Distance;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DetailFirst()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

		if (!m_DetailDataSet->Bof)
			m_DetailDataSet->First();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DetailLast()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

		if (!m_DetailDataSet->Eof)
			m_DetailDataSet->Last();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DetailPrior()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

		if (!m_DetailDataSet->Bof)
			m_DetailDataSet->Prior();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DetailNext()
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

		if (!m_DetailDataSet->Eof)
			m_DetailDataSet->Next();
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DetailMoveTo(int Distance)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");

		if (Distance < 1 || Distance > m_DetailDataSet->RecordCount)
			throw Exception(L"从表数据集指针移动越界");

		m_DetailDataSet->RecNo = Distance;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::LocateMaster(String KeyValues)
{
	int index, valcount;
	bool retval, isfiltered;
	String valstr, filterstr;
	TLocateOptions Opts;
	if (m_DataSetActive)
	{
		Opts.Clear();
		Opts << loCaseInsensitive;
		valcount = 0;
		if (m_MasterDataSet->RecordCount < 1) return false;
		index = KeyValues.Pos0("\t");
		if (index > 0 && index < KeyValues.Length())
		{
			Variant mv[20];
			while (index > 0)
			{
				valstr = KeyValues.SubString0(0, index );
				mv[valcount] = Variant(valstr);
				KeyValues.Delete0(0, index);
				valcount++;
				index = KeyValues.Pos0("\t");
			}
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			retval = m_MasterDataSet->Locate(m_MasterKeyFields, VarArrayOf(mv, valcount), Opts);
			return retval;
		}
		else
		{
			Variant sv;
			if (KeyValues.Length() > 0)
			{
				while (KeyValues[KeyValues.Length() - 1] == '\t')
				{
					KeyValues.Delete(KeyValues.Length()-1, 1);     //0-based
					if (KeyValues.Length() == 0)
						break;
				}
			}
			sv = Variant(KeyValues);
			retval = m_MasterDataSet->Locate(m_MasterKeyFields, sv, Opts);
			return retval;
		}
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::LocateDetail(String KeyValues)
{
	int index, valcount;
	bool retval, isfiltered;
	String valstr, filterstr;
	TLocateOptions Opts;
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		Opts.Clear();
		Opts << loCaseInsensitive;
		valcount = 0;
		if (m_DetailDataSet->RecordCount < 1)
			return false;
		index = KeyValues.Pos0("\t");
		if (index > -1)
		{
			Variant mv[20];
			while (index >-1)
			{
				valstr = KeyValues.SubString0(0, index );
				mv[valcount] = Variant(valstr);
				KeyValues.Delete0(0, index+1);     //0-based
				valcount++;
				index = KeyValues.Pos0("\t");
			}
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			retval = m_DetailDataSet->Locate(m_DetailKeyFields, VarArrayOf(mv, valcount), Opts);
			return retval;
		}
		else
		{
			Variant sv;
			if (KeyValues.Length() > 0)
			{
				while (KeyValues[KeyValues.Length()-1] == '\t')
				{
					KeyValues.Delete0(KeyValues.Length()-1, 1);   //0-based
					if (KeyValues.Length() == 0)
						break;
				}
			}
			sv = Variant(KeyValues);
			retval = m_DetailDataSet->Locate(m_DetailKeyFields, sv, Opts);
			return retval;
		}
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
TField *__fastcall TZClientDataSet::FindMasterField(String fieldname)
{
	if (m_DataSetActive)
	{
		return m_MasterDataSet->FindField(fieldname);
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
TField *__fastcall TZClientDataSet::FindDetailField(String fieldname)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		return m_DetailDataSet->FindField(fieldname);
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::FindMasterKey(String KeyValues)
{
	/////////////////////////////////////////
	// 未修改可能出错

	int index, valcount;
	bool isfiltered;
	String valstr, filterstr;
	Variant vr;
	if (m_DataSetActive)
	{
		valcount = 0;
		if (m_MasterDataSet->RecordCount < 1) return false;
		index = KeyValues.Pos0("\t");
		if (index > 0 && index < KeyValues.Length())
		{
			Variant mv[20];
			while (index > 0)
			{
				valstr = KeyValues.SubString(0, index );
				mv[valcount] = Variant(valstr);
				KeyValues.Delete0(0, index);         //0-based
				valcount++;
				index = KeyValues.Pos0("\t");
			}
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			vr = m_MasterDataSet->Lookup(m_MasterKeyFields, VarArrayOf(mv, valcount), m_MasterKeyFields);
			if (vr.IsNull())
				return false;
			else
				return true;
		}
		else
		{
			Variant sv;
			if (KeyValues.Length() > 0)
			{
				while (KeyValues[KeyValues.Length()] == '\t')
				{
					KeyValues.Delete(KeyValues.Length()-1, 1);  //0-based
					if (KeyValues.Length() == 0)
						break;
				}
			}
			sv = Variant(KeyValues);
			vr = m_MasterDataSet->Lookup(m_MasterKeyFields, sv,	m_MasterKeyFields);
			if (vr.IsNull())
				return false;
			else
				return true;
		}
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::FindDetailKey(String KeyValues)
{
	/////////////////////////////////////////
	// 未修改可能出错

	int index, valcount;
	bool isfiltered;
	String valstr, filterstr;
	Variant vr;
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		valcount = 0;
		if (m_DetailDataSet->RecordCount < 1)
			return false;
		index = KeyValues.Pos0("\t");
		if (index > -1)
		{
			Variant mv[20];
			while (index > -1)
			{
				valstr = KeyValues.SubString0(0, index );
				mv[valcount] = Variant(valstr);
				KeyValues.Delete0(0, index+1);  //0-based
				valcount++;
				index = KeyValues.Pos0("\t");
			}
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			FQuery->Close();
			FQuery->Data=m_DetailDataSet->Data;
			vr = FQuery->Lookup(m_DetailKeyFields, VarArrayOf(mv, valcount),
				m_DetailKeyFields);
			FQuery->Close();
			if (vr.IsNull())
				return false;
			else
				return true;
		}
		else
		{
			Variant sv;
			if (KeyValues.Length() > 0)
			{
				while (KeyValues[KeyValues.Length()] == '\t')
				{
					KeyValues.Delete(KeyValues.Length()-1, 1);   //0-based
					if (KeyValues.Length() == 0)
						break;
				}
			}
			sv = Variant(KeyValues);
			FQuery->Data=m_DetailDataSet->Data;
			vr = FQuery->Lookup(m_DetailKeyFields, sv, m_DetailKeyFields);
			FQuery->Close();
			if (vr.IsNull())
				return false;
			else
				return true;
		}
	}
	else
		throw Exception(L"系统尚未初始化.");
}
// ---------------------------------------------------------------------------

Variant __fastcall TZClientDataSet::GetMasterValue(String fieldname)
{
	if (m_DataSetActive)
	{
		TField *mfield = m_MasterDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->Value;
		// return m_MasterDataSet->FieldValues[fieldname];
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
Variant __fastcall TZClientDataSet::GetMasterOldValue(String fieldname)
{
	if (m_DataSetActive)
	{
		TField *mfield = m_MasterDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->OldValue;
		// return m_MasterDataSet->FieldByName(fieldname)->OldValue;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetMasterValue(String fieldname, Variant value)
{
	if (m_DataSetActive)
	{
		m_MasterDataSet->FieldValues[fieldname] = value;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
Variant __fastcall TZClientDataSet::GetDetailValue(String fieldname)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		TField *mfield = m_DetailDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->Value;

		// return m_DetailDataSet->FieldValues[fieldname];
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
Variant __fastcall TZClientDataSet::GetDetailOldValue(String fieldname)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		TField *mfield = m_DetailDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->OldValue;

		// return m_DetailDataSet->FieldByName(fieldname)->OldValue;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetDetailValue(String fieldname, Variant value)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception(L"当前系统为单表状态.");
		if (m_DetailDataSet->State == dsBrowse)
			throw Exception(L"错误:当前不是编辑状态,拒绝赋值!");
		m_DetailDataSet->FieldValues[fieldname] = value;
	}
	else
		throw Exception(L"系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::CmdExec(String Param)
{
	 TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	String s;
	TMemoryStream *rmsStream=new TMemoryStream();
	int rc;
	bool FCurEnabled; // new
	// HWND FCurWnd;
	try
	{
		// FCurWnd=GetActiveWindow();
		if (m_DataSetActive)
		{
			sxs->Operate = asDSCommExecute;
		  //	sxs->ClientID = String((int)m_Handle);
		 //	sxs->ServerID = m_ServerDataSetHandle;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["datasettype"] = m_DataSetType;
			sxs->ValueAttribute["param"] = Param;
			sxs->ValueAttribute["masterstatus"] = m_MasterDataSet->State;
//			TADODataSetStream *datasetStream=new TADODataSetStream(m_MasterStructure);
//			datasetStream->SaveToDataSet(FQuery);
//			delete datasetStream;
			FQuery->Data=m_MasterStructure->Data;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if (m_MasterDataSet->Fields->Fields[i]->IsNull)
				{
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				}
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			//FQuery->SaveToFile(m_MasterFileName, pfXML);
			//sxs->LoadMasterFromFile(m_MasterFileName);
			sxs->LoadMasterFromDataSet(FQuery);
			if (m_DataSetType == 2)
			{
				//m_DetailDataSet->SaveToFile(m_DetailFileName, pfXML);
			   //	sxs->LoadDetailFromFile(m_DetailFileName);
			   sxs->LoadDetailFromDataSet(m_DetailDataSet);
			}


			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm=ServerDataSet->CmdExec(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynCmdExec(sxs);
			CheckResultStatus(dsOperateStatus);
			if (m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			if (m_DataSetType == 2)
			{
				m_DetailDataSet->MergeChangeLog();
			}
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
		delete sxs;
		delete rmsStream;
	   //	if (sm) {
	   //		delete sm;
	   //	}
		delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Check(int IsCheck)
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	String s;
	TMemoryStream *rmsStream=new TMemoryStream();
	TValidType vt;
	TValidAffect va;
	int rc;
	bool FCurEnabled; // new
	// HWND FCurWnd;

	try
	{
		// FCurWnd=GetActiveWindow();
		if (m_DataSetActive)
		{
			sxs->Operate = asDSCheck;
			sxs->ClientID = String((int)this);
			sxs->ServerID = m_ServerDataSetHandle;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["datasettype"] = m_DataSetType;
			sxs->ValueAttribute["masterstatus"] = m_MasterDataSet->State;
			sxs->ValueAttribute["ischeck"] = IsCheck;
			rc = 1;
			if (m_DataSetType == 1)
				va = vaCurRecNo;
			else
				va = vaAll;
			if (m_MasterDataSet->State == dsInsert)
			{
				if (m_DataSetType == 1)
					vt = vtMaster;
				else
					vt = vtMasterDetail;
			}
			else
				vt = vtDetail;
			if (m_NeedValid)
				sxs->ItemAttribute["needvalid"] = "t";
			else
				sxs->ItemAttribute["needvalid"] = "f";
			sxs->ItemAttribute["validtype"] = vt;
			sxs->ItemAttribute["validaffect"] = va;
			sxs->ItemAttribute["validrecno"] = rc;
			sxs->ItemAttribute["mastervalidfieldlist"] = BuildValidList(m_MasterValidFieldList);
			sxs->ItemAttribute["detailvalidfieldlist"] = BuildValidList(m_DetailValidFieldList);
//
			FQuery->Data=m_MasterStructure->Data;
			FQuery->Append();
			if (m_MasterDataSet->State == dsInsert)
			{
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if (m_MasterDataSet->Fields->Fields[i]->IsNull)
					{
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					}
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
				}
				FQuery->Post();
			}
			else if (m_MasterDataSet->State == Db::dsEdit)
			{
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if (m_MasterDataSet->Fields->Fields[i]->IsNull)
					{
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					}
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName)->OldValue;
				}
				FQuery->Post();
				FQuery->MergeChangeLog();
				FQuery->Edit();
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if (m_MasterDataSet->Fields->Fields[i]->IsNull)
					{
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					}
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
				}
				FQuery->Post();
			}
			else
			{
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if (m_MasterDataSet->Fields->Fields[i]->IsNull)
					{
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					}
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
				}
				FQuery->Post();
				FQuery->MergeChangeLog();
			}
			//FQuery->SaveToFile(m_MasterFileName, pfXML);
			//sxs->LoadMasterFromFile(m_MasterFileName);
			sxs->LoadMasterFromDataSet(FQuery);
			if (m_DataSetType == 2)
			{
				//m_DetailDataSet->SaveToFile(m_DetailFileName, pfXML);
				//sxs->LoadDetailFromFile(m_DetailFileName);
				sxs->LoadDetailFromDataSet(m_DetailDataSet);
			}


			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm= ServerDataSet->Check(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynCheck(sxs);
			CheckResultStatus(dsOperateStatus);
			if (m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
		delete sxs;
		delete rmsStream;
	   //	if (sm) {
	   //		delete sm;
	  //	}
		delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::CloseOff(int IsClose)
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	String s;
	TMemoryStream *rmsStream = new TMemoryStream();
	int rc;
	bool FCurEnabled; // new
	try
	{
		if (m_DataSetActive)
		{

			sxs->Operate = asDSCloseOff;
		   //	sxs->ClientID = String((int)m_Handle);
		   //	sxs->ServerID = m_ServerDataSetHandle;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["isclose"] = IsClose;

			FQuery->Data=m_MasterStructure->Data;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if (m_MasterDataSet->Fields->Fields[i]->IsNull)
				{
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				}
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
		   //	FQuery->SaveToFile(m_MasterFileName, pfXML);
		   //	sxs->LoadMasterFromFile(m_MasterFileName);
		   sxs->LoadMasterFromDataSet(FQuery);
			if (m_DataSetType == 2)
			{
				//m_DetailDataSet->SaveToFile(m_DetailFileName, pfXML);
			   //	sxs->LoadDetailFromFile(m_DetailFileName);
			   sxs->LoadDetailFromDataSet(m_DetailDataSet);
			}


			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm=ServerDataSet->CloseOff(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynCloseOff(sxs);
			CheckResultStatus(dsOperateStatus);
			if (m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
			if (m_DataSetType == 2)
			{
				m_DetailDataSet->MergeChangeLog();
//				 BuildDetailFilter();
			}
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
		delete sxs;
		delete rmsStream;
	   //	if (sm) {
	  //		delete sm;
	  //	}
		delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Revoke(int IsRevoke)
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	String s;
	TMemoryStream *rmsStream = new TMemoryStream();
	int rc;
	bool FCurEnabled; // new
	// HWND FCurWnd;

	try
	{
		// FCurWnd=GetActiveWindow();
		if (m_DataSetActive)
		{

			sxs->Operate = asDSCancel;
			sxs->ClientID = String((int)this);
			sxs->ServerID = m_ServerDataSetHandle;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["isrevoke"] = IsRevoke;

			FQuery->Data=m_MasterStructure->Data;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if (m_MasterDataSet->Fields->Fields[i]->IsNull)
				{
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				}
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			//FQuery->SaveToFile(m_MasterFileName, pfXML);
			//sxs->LoadMasterFromFile(m_MasterFileName);
			 sxs->LoadMasterFromDataSet(FQuery);
			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm= ServerDataSet->Revoke(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynRevoke(sxs);
		   CheckResultStatus(dsOperateStatus);
			if (m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
		delete sxs;
		delete rmsStream;
	   //	if (sm) {
	   //		delete sm;
	   //	}
		delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::Tally(int IsTally)
{
	 TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	String s;
	TMemoryStream *rmsStream=new TMemoryStream();
	int rc;
	bool FCurEnabled; // new
	// HWND FCurWnd;

	try
	{
		// FCurWnd=GetActiveWindow();
		if (m_DataSetActive)
		{
			sxs->Operate = asDSRecord;
		   //	sxs->ClientID = String((int)m_Handle);
		   //	sxs->ServerID = m_ServerDataSetHandle;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["istally"] = IsTally;

			FQuery->Data=m_MasterStructure->Data;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if (m_MasterDataSet->Fields->Fields[i]->IsNull)
				{
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				}
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			//FQuery->SaveToFile(m_MasterFileName, pfXML);
			//sxs->LoadMasterFromFile(m_MasterFileName);
			 sxs->LoadMasterFromDataSet(FQuery);
			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm=ServerDataSet->Tally(rmsStream,m_ClassCode);
			sxs->LoadFromStream(sm);
			AsynTally(sxs);
			CheckResultStatus(dsOperateStatus);
			if (m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->MergeChangeLog();
			}
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
			delete sxs;
			delete rmsStream;
		  //	if (sm) {
		  //		delete sm;
		  //	}
			delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::ExecSQL(String sqlstr)
{
  TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	TMsgStream *sxs = new TMsgStream();
	TStream *sm=NULL;
	TMemoryStream *rmsStream = new TMemoryStream();
	String s;
	bool FCurEnabled; // new
	// HWND FCurWnd;
	try
	{
		// FCurWnd=GetActiveWindow();
		if (m_DataSetActive)
		{
			dsOperateStatus = 0;

			sxs->Operate = asDSSQL;
			//sxs->ClientID = String((int)m_Handle);
			//sxs->ServerID = m_ServerDataSetHandle;
			sxs->ClassID = m_ClassCode;
			sxs->ValueAttribute["sqlstr"] = sqlstr;


			sxs->SaveToStream(rmsStream);
			rmsStream->Position=0;
			sm=ServerDataSet->ExecSQL(rmsStream);
			sxs->LoadFromStream(sm);
			AsynExecSQL(sxs);
			CheckResultStatus(dsOperateStatus);
		}
		else
			throw Exception(L"系统尚未初始化.");
	}
	__finally
	{
			delete sxs;
			delete rmsStream;
		   //	if (sm) {
		   //		delete sm;
		   //	}
			delete ScreenCursor;
	}
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterSQLString()
{
	return m_MasterSQLString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterSQLString(String value)
{
	m_MasterSQLString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailSQLString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailSQLString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailSQLString(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailSQLString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterWhereString()
{
	return m_MasterWhereString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterWhereString(String value)
{
	m_MasterWhereString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailWhereString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailWhereString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailWhereString(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailWhereString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterOrderString()
{
	return m_MasterOrderString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterOrderString(String value)
{
	m_MasterOrderString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailOrderString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailOrderString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailOrderString(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailOrderString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterGroupString()
{
	return m_MasterGroupString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterGroupString(String value)
{
	m_MasterGroupString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailGroupString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailGroupString;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailGroupString(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailGroupString = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterKeyFields()
{
	return m_MasterKeyFields;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterKeyFields(String value)
{
	m_MasterKeyFields = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailKeyFields()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailKeyFields;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailKeyFields(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailKeyFields = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_LinkFields()
{
	if (m_DataSetType == 1)
		return "";
	else
		return BuildLinkFields();
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_LinkFields(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	ExtractLinkFields(value);
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterSort()
{
	return m_MasterDataSet->Sort;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterSort(String value)
{
	m_MasterDataSet->Sort = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailSort()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->Sort;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailSort(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailDataSet->Sort = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_Filter()
{
	return m_MasterDataSet->Filter;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_Filter(String value)
{
	m_MasterDataSet->Filter = value;
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_Filtered()
{
	return m_MasterDataSet->Filtered;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_Filtered(bool value)
{
	m_MasterDataSet->Filtered = value;
}

// ---------------------------------------------------------------------------
TDataSetState __fastcall TZClientDataSet::get_MasterStatus()
{
	return m_MasterDataSet->State;
}

// ---------------------------------------------------------------------------
TDataSetState __fastcall TZClientDataSet::get_DetailStatus()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->State;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DataSetType()
{
	return m_DataSetType;
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_Bof()
{
	return m_MasterDataSet->Bof;
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_Eof()
{
	return m_MasterDataSet->Eof;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_RecordCount()
{
	return m_MasterDataSet->RecordCount;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_CurRecNo()
{
	return m_MasterDataSet->RecNo;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_MasterFieldCount()
{
	return m_MasterDataSet->FieldCount;
}

// ---------------------------------------------------------------------------
TFields *__fastcall TZClientDataSet::get_MasterFields()
{
	return m_MasterDataSet->Fields;
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_DetailBof()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->Bof;
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_DetailEof()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->Eof;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DetailCount()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->RecordCount;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DetailRecNo()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->RecNo;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DetailFieldCount()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->FieldCount;
}

// ---------------------------------------------------------------------------
TFields *__fastcall TZClientDataSet::get_DetailFields()
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	return m_DetailDataSet->Fields;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterFieldName(int index)
{
	return m_MasterDataSet->Fields->Fields[index]->FieldName;
}

// ---------------------------------------------------------------------------
TFieldType __fastcall TZClientDataSet::get_MasterFieldType(int index)
{
	return m_MasterDataSet->Fields->Fields[index]->DataType;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_MasterFieldSize(int index)
{
	return m_MasterDataSet->Fields->Fields[index]->Size;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailFieldName(int index)
{
	return m_DetailDataSet->Fields->Fields[index]->FieldName;
}

// ---------------------------------------------------------------------------
TFieldType __fastcall TZClientDataSet::get_DetailFieldType(int index)
{
	return m_DetailDataSet->Fields->Fields[index]->DataType;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DetailFieldSize(int index)
{
	return m_DetailDataSet->Fields->Fields[index]->Size;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::BuildLinkStr()
{
	String s;
	if (m_DataSetType == 1) return "";
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
String __fastcall TZClientDataSet::BuildLinkFields()
{
	String s;
	if (m_DataSetType == 1) return "";
	for (int i = 0; i < m_MasterLinkFields->Count; i++)
	{
		s += m_MasterLinkFields->Strings[i] + "=" +
			m_DetailLinkFields->Strings[i] + "\t";
	}
	return s;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::ExtractLinkFields(String value)
{
	String s;
	int index;
	if (m_DataSetType == 1) return;
	index = value.Pos0("=");
	m_MasterLinkFields->Clear();
	m_DetailLinkFields->Clear();
	while (index > -1)
	{
		s = value.SubString0(0, index).Trim();
		m_MasterLinkFields->Add(s);
		value.Delete0(0, index+1);   //0-based
		index = value.Pos0("\t");
		s = value.SubString0(0, index );
		m_DetailLinkFields->Add(s);
		value.Delete0(0, index+1); //0-based
		index = value.Pos0("=");
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::BuildDetailFilter()
{
	String filterstr;
	int ftype;
	TField *FField;
	for (int i = 0; i < m_MasterLinkFields->Count; i++)
	{
		FField = m_DetailDataSet->Fields->FindField(m_DetailLinkFields->Strings[i]);

		if(FField != NULL)
			ftype = CheckFieldType(FField);
		else
			throw Exception(L"从表关联字段:" + m_DetailLinkFields->Strings[i] + L"未找到.");

		if(ftype == 1)
			filterstr += m_DetailLinkFields->Strings[i] + "='" + m_MasterDataSet->FieldByName(m_MasterLinkFields->Strings[i])->AsString + "'";
		else
			filterstr += m_DetailLinkFields->Strings[i] + "=" + m_MasterDataSet->FieldByName(m_MasterLinkFields->Strings[i])->AsString;

		if(i < m_MasterLinkFields->Count - 1)
			filterstr += " and ";
	}
	m_DetailDataSet->Filtered = false;
	m_DetailDataSet->Filter   = filterstr;
	m_DetailDataSet->Filtered = true;
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::CheckFieldType(TField *Field)
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
		case ftBCD:
		case ftAutoInc:
		case ftLargeint:
			return 2;
		default:
			return 0;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::CheckResultStatus(int status)
{
	String errmsg = ZDataSetErrorMessage;
	ZDataSetErrorMessage = "";
	if (status == 2)
	{
		if (errmsg > "")
			throw Exception(errmsg);
	}
	else if (status == 3)
		throw Exception(L"系统操作超时.");
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::BuildDetailStatus()
{
//	if (m_DataSetType == 2)
//	{
//		 m_DetailEditStatus->Clear();
//		 for(int i=0;i<m_DetailDataSet->RecordCount;i++)
//		 m_DetailEditStatus->Add(dsBrowse);
//	}
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetDataSetDisplayName(TDataSet *ds, TStringList *dn, TStringList *fn)
{
	if (fn->Count > 0)
	{
		for (int i = 0; i < ds->FieldCount; i++)
		{
			TField *cField = ds->Fields->Fields[i];
			int index = fn->IndexOf(cField->FieldName);
			if (index > -1)
			{
				if (!(dn->Strings[index].Trim()).IsEmpty())
					cField->DisplayLabel = dn->Strings[index];
			}
		}
	}
	else
	{
		for (int i = 0; i < ds->FieldCount; i++)
		{
			if (i >= dn->Count)
				break;
			if (!(dn->Strings[i].Trim()).IsEmpty())
				ds->Fields->Fields[i]->DisplayLabel = dn->Strings[i];
		}
	}
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::BuildValidList(String value)
{
	String retstr;
	int index;
	retstr = "";
	index = value.Pos0(";");
	while (index > -1)
	{
		retstr += value.SubString0(0, index ) + "\r\n";
		value.Delete0(0, index+1);  //0-based
		index = value.Pos0(";");
	}
	if (!value.IsEmpty())
		retstr += value + "\r\n";
	return retstr;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterValidFieldList()
{
	return m_MasterValidFieldList;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_MasterValidFieldList(String value)
{
	m_MasterValidFieldList = value;
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailValidFieldList()
{
	return m_DetailValidFieldList;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::set_DetailValidFieldList(String value)
{
	if (m_DataSetType == 1)
		throw Exception(L"当前系统为单表状态.");
	m_DetailValidFieldList = value;
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::ExitClientDataSet()
{
	// SendMessage(m_Handle,WM_TERMINATE_THREAD,0,0);
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_MasterFilterField(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	if (index >= m_MasterFilterFields->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_MasterFilterFields->Strings[index].ToInt();
}

// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::get_DetailFilterField(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	if (index >= m_DetailFilterFields->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_DetailFilterFields->Strings[index].ToInt();
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_MasterFieldAttr(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	if (index >= m_MasterFieldAttr->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_MasterFieldAttr->Strings[index].ToInt();
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DetailFieldAttr(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	if (index >= m_DetailFieldAttr->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_DetailFieldAttr->Strings[index].ToInt();
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_MasterFieldExpr(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	return m_MasterFieldExpr->Strings[index];
}

// ---------------------------------------------------------------------------
String __fastcall TZClientDataSet::get_DetailFieldExpr(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	return m_DetailFieldExpr->Strings[index];
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_MasterAttrType(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	return m_MasterAttrType->Strings[index].ToInt();
}

// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::get_DetailAttrType(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception(L"字段下标越界");
	return m_DetailAttrType->Strings[index].ToInt();
}

// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SaveMasterToFile(const String FileName,
TDataPacketFormat Format, bool bFiltered, bool bMoneyHide, String ClearMasterFieldsString)
{
	if (bFiltered)
	{
		TBookmark SavePlace = m_MasterDataSet->GetBookmark();
		String mFilter = "", oldFilter = m_MasterDataSet->Filter;
		bool oldFiltered = m_MasterDataSet->Filtered;
		try
		{
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if (m_MasterKeyFields.Pos
					(m_MasterDataSet->Fields->Fields[i]->FieldName) > 0)
					mFilter += m_MasterDataSet->Fields->Fields[i]->FieldName +
						"='" + m_MasterDataSet->Fields->Fields[i]->AsString +
						"' and ";

			}
			if (mFilter != "")
				mFilter = mFilter.SubString0(0, mFilter.Length() - 4);
			m_MasterDataSet->Filtered = false;
			m_MasterDataSet->Filter = mFilter;
			m_MasterDataSet->Filtered = true;
			m_MasterDataSet->SaveToFile(FileName, Format);
			if (bMoneyHide)
				ClearMoneyDataSet(FileName, ClearMasterFieldsString);
		}
		__finally
		{
			m_MasterDataSet->Filtered = false;
			m_MasterDataSet->Filter = oldFilter;
			m_MasterDataSet->Filtered = oldFiltered;
			if (bFiltered && m_MasterDataSet->RecordCount > 0)
				m_MasterDataSet->GotoBookmark(SavePlace);
			m_MasterDataSet->FreeBookmark(SavePlace);
		}
	}
	else
	{
		m_MasterDataSet->SaveToFile(FileName, Format);
		if (bMoneyHide)
			ClearMoneyDataSet(FileName, ClearMasterFieldsString);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SaveDetailToFile(const String FileName,
TDataPacketFormat Format, bool bFiltered, bool bMoneyHide, String ClearDetailFieldsString)
{
	if(DataSetType != 2)
		throw Exception(L"该数据集不是主从结构");
	bool bfilter = m_DetailDataSet->Filtered;
	try
	{
		m_DetailDataSet->Filtered = bFiltered;
		m_DetailDataSet->SaveToFile(FileName, Format);
		if(bMoneyHide)
			ClearMoneyDataSet(FileName, ClearDetailFieldsString);
	}
	__finally
	{
		m_DetailDataSet->Filtered = bfilter;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SaveMasterToFile(const String FileName,
TDataPacketFormat Format, String sFilter, bool bMoneyHide, String ClearMasterFieldsString)
{
	TBookmark SavePlace = m_MasterDataSet->GetBookmark();
	String mFilter = "", oldFilter = m_MasterDataSet->Filter;
	bool oldFiltered = m_MasterDataSet->Filtered;
	try
	{
		if(sFilter != "")
		{
			m_MasterDataSet->Filtered = false;
			m_MasterDataSet->Filter = sFilter;
			m_MasterDataSet->Filtered = true;
		}
		m_MasterDataSet->SaveToFile(FileName, Format);
		if(bMoneyHide)
			ClearMoneyDataSet(FileName, ClearMasterFieldsString);
	}
	__finally
	{
		m_MasterDataSet->Filtered = false;
		m_MasterDataSet->Filter = oldFilter;
		m_MasterDataSet->Filtered = oldFiltered;
		if(m_MasterDataSet->RecordCount > 0)
			m_MasterDataSet->GotoBookmark(SavePlace);
		m_MasterDataSet->FreeBookmark(SavePlace);
	}
}
// ---------------------------------------------------------------------------
TDataSnapClientDataSet* __fastcall TZClientDataSet::GetDetailDataSet()
{
	if(m_DataSetType)
		return m_DetailDataSet;
	else
		return NULL;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::ClearMoneyDataSet(String FileName, String FieldsString)
{
	TDataSnapClientDataSet * cdDataSet = new TDataSnapClientDataSet(NULL);
	TStringList *fieldString = new TStringList();
	try
	{
		cdDataSet->LoadFromFile(FileName);
		fieldString->Delimiter = '\t';
		fieldString->DelimitedText = FieldsString;
		cdDataSet->First();
		while (!cdDataSet->Eof)
		{
			cdDataSet->Edit();
			for (int i = 0; i < fieldString->Count; i++)
			{
				cdDataSet->FieldByName(fieldString->Strings[i])->Value = 0;
			}
			cdDataSet->Post();
			cdDataSet->Next();
		}
		if(cdDataSet->ChangeCount>0)
			cdDataSet->MergeChangeLog();
		cdDataSet->SaveToFile(FileName, dfXML);
	}
	__finally
	{
		delete cdDataSet;
		delete fieldString;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::MasterDataSetAfterScroll(TDataSet *DataSet)
{
	if(m_DataSetType == 2)
		BuildDetailFilter();
	DoClientDataSetAfterScroll();
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::DoClientDataSetAfterScroll()
{
	if(dsOperateStatus != 0)
	{
		if(FClientDataSetAfterScroll)
			FClientDataSetAfterScroll(m_MasterDataSet);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetMasterDataSetBeforePost(TDataSetNotifyEvent value)
{
	m_MasterDataSet->BeforePost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TZClientDataSet::GetMasterDataSetBeforePost()
{
	return m_MasterDataSet->BeforePost;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetMasterDataSetAfterPost(TDataSetNotifyEvent value)
{
	m_MasterDataSet->AfterPost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TZClientDataSet::GetMasterDataSetAfterPost()
{
	return m_MasterDataSet->AfterPost;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetDetailDataSetBeforePost(TDataSetNotifyEvent value)
{
	if(m_DataSetType == 2)
		m_DetailDataSet->BeforePost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TZClientDataSet::GetDetailDataSetBeforePost()
{
	if(m_DataSetType == 2)
		return m_DetailDataSet->BeforePost;
	else
		return NULL;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetDetailDataSetAfterPost(TDataSetNotifyEvent value)
{
	if(m_DataSetType == 2)
		m_DetailDataSet->AfterPost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TZClientDataSet::GetDetailDataSetAfterPost()
{
	if(m_DataSetType == 2)
		return m_DetailDataSet->AfterPost;
	else
		return NULL;
}
// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::GetSysDbType()
{
	return FClientBroker->SysDbType;
}
// ---------------------------------------------------------------------------
int __fastcall TZClientDataSet::GetAccDbType()
{
	return FClientBroker->AccDbType;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetNullFieldValue(TField *DestField, TField* Sourcefield)
{
	switch (Sourcefield->DataType)
	{
		case ftString:
		case ftMemo:
		case ftFixedChar:
		case ftWideString:
		case ftFmtMemo:
		case ftBlob:
			DestField->Value = ""; // oracle不允许为空串，认为是NULL;
			break;
		case ftAutoInc:
		case ftSmallint:
		case ftInteger:
		case ftWord:
		case ftFloat:
		case ftCurrency:
		case ftBCD:
		case ftLargeint:
		default:
			DestField->Value = NULL;
	}
}
// ---------------------------------------------------------------------------
bool __fastcall TZClientDataSet::NullFieldIsString(TField *SourcField)
{
	if(SourcField->IsNull)
	{
		switch (SourcField->DataType)
		{
			case ftString:
			case ftMemo:
			case ftFixedChar:
			case ftWideString:
			case ftFmtMemo:
			case ftBlob:
				return true;
			case ftSmallint:
			case ftInteger:
			case ftWord:
			case ftFloat:
			case ftCurrency:
			case ftBCD:
			case ftLargeint:
			case ftAutoInc:
			default:
				return false;
		}
	}
	return false;
}
// ---------------------------------------------------------------------------
void __fastcall TZClientDataSet::SetAllFieldCanModify(TClientDataSet *ds) {
	SetAllFieldsCanModify(ds);
}
