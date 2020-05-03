// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "MessageDef.h"
#include "JClientDataset.h"
#include "DSClientProxy.h"
#include "BaseFunc.h"
#include "XMLData.h"
#include "SHConst.h"
#include "fsScreenCursor.h"
#include "ADODataSetStream.h"
#include "DBJson.hpp"

#define _TimeOuts 60
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
__fastcall TJClientDataSet::TJClientDataSet(TClientBroker *FBroker, String AClassCode)
{
	logfile = NULL;
//	m_Handle = AllocateHWnd(WndProc); // Local Handle
 //	m_AOwner = AOwner; // Form Handle
	FClientBroker = FBroker;
//	m_Parent = FClientBroker->Handle; // ClientComm Handle

	m_ClassCode = AClassCode;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	FClientDataSetAfterScroll = NULL;

	m_MasterDataSet = new TADODataSet(NULL);
	m_MasterDataSet->EnableBCD = false;
	m_MasterDataSet->LockType = ltBatchOptimistic;
	m_MasterDataSet->AfterScroll = MasterDataSetAfterScroll;

	FQuery = new TADODataSet(NULL);
	FQuery->EnableBCD = false;
	FQuery->LockType = ltBatchOptimistic;

	m_MasterStructure = new TADODataSet(NULL);
	m_MasterStructure->EnableBCD = false;
	m_MasterStructure->LockType = ltBatchOptimistic;

	m_DetailStructure = new TADODataSet(NULL);
	m_DetailStructure->EnableBCD = false;
	m_DetailStructure->LockType = ltBatchOptimistic;

	ZDataSetOperateStatus  = 0; // 0-等待返回消息,1-正常返回,2-错误返回,3-超时返回
	ZDataSetErrorMessage   = "";
//	ClientCommConnectState = true;
	m_DataSetActive        = false;
	m_MasterSQLString      = "";
	m_DetailSQLString      = "";
	m_MasterWhereString    = "";
	m_DetailWhereString    = "";
	m_MasterOrderString    = "";
	m_DetailOrderString    = "";
	m_MasterGroupString    = "";
	m_DetailGroupString    = "";
	m_MasterKeyFields      = "";
	m_DetailKeyFields      = "";
	m_ServerDataSetHandle  = 0;
	m_MasterDisplayName    = new TStringList;
	m_MasterDisplayField   = new TStringList;
	m_MasterFilterFields   = new TStringList;
	m_DetailFilterFields   = new TStringList;
	m_MasterFieldAttr      = new TStringList;
	m_DetailFieldAttr      = new TStringList;
	m_MasterFieldExpr      = new TStringList;
	m_DetailFieldExpr      = new TStringList;
	m_MasterAttrType       = new TStringList;
	m_DetailAttrType       = new TStringList;
	// 明细表记录的状态：0-浏览;1-新增;2-修改;3-删除
	m_DtlRecStatus         = new TStringList;

	m_DataSetType          = 1;
	m_TimeOut              = 30000;
	m_NeedValid            = false;
	m_MasterValidFieldList = "";
	m_DetailValidFieldList = "";

	m_Query = new TJClientQuery(NULL, FBroker, this);
	InitServerDataSet();
}
// ---------------------------------------------------------------------------
__fastcall TJClientDataSet::~TJClientDataSet()
{
	ClientDataSetTerminate(NULL);
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::ClientDataSetTerminate(TObject *Sender)
{
	if(FClientBroker)
	{
		FreeServerDataSet();
//		FClientBroker->DeleteClientDataSet(this);
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
	delete m_DtlRecStatus;
	if(m_DataSetType == 2)
	{
		delete m_DetailDataSet;
		delete m_MasterLinkFields;
		delete m_DetailLinkFields;
		delete m_DetailDisplayName;
		delete m_DetailDisplayField;
	}

	if(logfile != NULL)
		fclose(logfile);
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::InitServerDataSet()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	ServerDataSet = new TJServerDataSetClient(FClientBroker->DBXConnection,false);
	try
	{
		TJSONObject *JSONObject = ServerDataSet->GetInitResult(m_ClassCode);
		InitClientDataSet((TJSONObject *)(JSONObject->Clone()));
		CheckResultStatus(ZDataSetOperateStatus);
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::FreeServerDataSet()
{

}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::InitClientDataSet(TJSONObject *Json)
{
	try
	{
		if(Json->Size() > 0)
		{
			String s1, s2, len1, sStatus, JsonStr;
			int pos1;

			sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus == "s")
			{
				m_MasterDataSet->AfterScroll = NULL;
				m_DataSetType              = Json->Get("DataSetType")->JsonValue->Value().ToInt();
				m_MasterKeyFields          = Json->Get("MasterKeyFields")->JsonValue->Value();
				m_MasterDisplayName->Text  = Json->Get("MasterDisplayName")->JsonValue->Value();
				m_MasterDisplayField->Text = Json->Get("MasterDisplayField")->JsonValue->Value();
				m_MasterFilterFields->Text = Json->Get("MasterFilterFields")->JsonValue->Value();
				m_MasterFieldAttr->Text    = Json->Get("MasterFieldAttr")->JsonValue->Value();
				m_MasterAttrType->Text     = Json->Get("MasterAttrType")->JsonValue->Value();
				s1 = Json->Get("MasterFieldExpr")->JsonValue->Value();
				pos1 = 0;
				while (pos1 < s1.Length())
				{
					len1.SetLength(4);
					wcsncpy(len1.c_str(), s1.c_str() + pos1, 4);
					s2.SetLength(len1.ToInt());
					pos1 += 4;
					wmemcpy(s2.c_str(), (s1.c_str() + pos1), len1.ToInt());
					pos1 += len1.ToInt();
					m_MasterFieldExpr->Add(s2);
				}

				m_MasterSQLString        = Json->Get("MasterSQLString")->JsonValue->Value();
				m_MasterFixedWhereString = Json->Get("MasterFixedWhereString")->JsonValue->Value();
				m_MasterFixedOrderString = Json->Get("MasterFixedOrderString")->JsonValue->Value();
				m_MasterFixedGroupString = Json->Get("MasterFixedGroupString")->JsonValue->Value();

				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				JsonStr = MstJson->ToString();
				_di_ISuperObject pso = SO(JsonStr);
				TTableJson::JsonToDataSet(m_MasterDataSet,pso);
				TTableJson::JsonToDataSet(m_MasterStructure,pso);

				SetAllFieldCanModify(m_MasterDataSet);
				SetAllFieldCanModify(m_MasterStructure);
				SetDataSetDisplayName(m_MasterDataSet, m_MasterDisplayName,	m_MasterDisplayField);

				if(m_DataSetType==2)
				{
					CoInitializeEx(NULL, COINIT_MULTITHREADED);
					m_DetailDataSet            = new TADODataSet(NULL);
					m_DetailDataSet->EnableBCD = false;
					m_DetailDataSet->LockType  = ltBatchOptimistic;
					m_MasterLinkFields         = new TStringList;
					m_DetailLinkFields         = new TStringList;
					m_DetailDisplayName        = new TStringList;
					m_DetailDisplayField       = new TStringList;

					m_DetailKeyFields          = Json->Get("DetailKeyFields")->JsonValue->Value();
					m_DetailDisplayName->Text  = Json->Get("DetailDisplayName")->JsonValue->Value();
					m_DetailDisplayField->Text = Json->Get("DetailDisplayField")->JsonValue->Value();
					m_DetailFilterFields->Text = Json->Get("DetailFilterFields")->JsonValue->Value();
					m_DetailFieldAttr->Text    = Json->Get("DetailFieldAttr")->JsonValue->Value();
					m_DetailAttrType->Text     = Json->Get("DetailAttrType")->JsonValue->Value();
					s1 = Json->Get("DetailFieldExpr")->JsonValue->Value();
					pos1 = 0;
					while (pos1 < s1.Length())
					{
						len1.SetLength(4);
						wcsncpy(len1.c_str(), s1.c_str() + pos1, 4);
						s2.SetLength(len1.ToInt());
						pos1 += 4;
						wmemcpy(s2.c_str(), (s1.c_str() + pos1), len1.ToInt());
						pos1 += len1.ToInt();
						m_DetailFieldExpr->Add(s2);
					}

					m_DetailSQLString        = Json->Get("DetailSQLString")->JsonValue->Value();
					m_DetailFixedWhereString = Json->Get("DetailFixedWhereString")->JsonValue->Value();
					m_DetailFixedOrderString = Json->Get("DetailFixedOrderString")->JsonValue->Value();
					m_DetailFixedGroupString = Json->Get("DetailFixedGroupString")->JsonValue->Value();
					m_MasterLinkFields->Text = Json->Get("MasterLinkFields")->JsonValue->Value();
					m_DetailLinkFields->Text = Json->Get("DetailLinkFields")->JsonValue->Value();

					TJSONObject *DtlJson = (TJSONObject*)Json->Get("Detail")->JsonValue;
					JsonStr = DtlJson->ToString();
					_di_ISuperObject pso = SO(JsonStr);
					TTableJson::JsonToDataSet(m_DetailDataSet,pso);
					TTableJson::JsonToDataSet(m_DetailStructure,pso);

					SetAllFieldCanModify(m_DetailDataSet);
					SetAllFieldCanModify(m_DetailStructure);
					SetDataSetDisplayName(m_DetailDataSet, m_DetailDisplayName,	m_DetailDisplayField);
				}
				m_DataSetActive = true;
				ZDataSetOperateStatus = 1;
				m_MasterDataSet->AfterScroll = MasterDataSetAfterScroll;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "初始化数据集失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynOpen(TJSONObject *Json)
{
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				String JsonStr;
				m_MasterDataSet->AfterScroll = NULL;
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				JsonStr = MstJson->ToString();
				_di_ISuperObject pso = SO(JsonStr);
				TTableJson::JsonToDataSet(m_MasterDataSet,pso);
				SetDataSetDisplayName(m_MasterDataSet, m_MasterDisplayName,	m_MasterDisplayField);
				if(m_DataSetType==2)
				{
					TJSONObject *DtlJson = (TJSONObject*)Json->Get("Detail")->JsonValue;
					JsonStr = DtlJson->ToString();
					_di_ISuperObject pso = SO(JsonStr);
					TTableJson::JsonToDataSet(m_DetailDataSet,pso);
					SetAllFieldCanModify(m_DetailDataSet);
					SetDataSetDisplayName(m_DetailDataSet, m_DetailDisplayName, m_DetailDisplayField);
				}
				ZDataSetOperateStatus = 1;
				m_MasterDataSet->AfterScroll = MasterDataSetAfterScroll;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "打开数据集失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynUpdate(TJSONObject *Json)
{
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				String sFieldName="";
				m_MasterDataSet->AfterScroll = NULL;
				CoInitializeEx(NULL, COINIT_MULTITHREADED);
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(FQuery,pso);

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
					for (int i = 0; i < FQuery->FieldCount; i++)
					{
//						if(m_MasterDataSet->State == dsBrowse)
//							m_MasterDataSet->Edit();
						sFieldName = FQuery->Fields->Fields[i]->FieldName;
						m_MasterDataSet->FieldValues[sFieldName] = FQuery->FieldValues[sFieldName];
					}
					FQuery->Close();
				}
				m_MasterDataSet->UpdateBatch(arAll);

				if(m_DataSetType==2)
				{
					TJSONObject *DtlJson = (TJSONObject*)Json->Get("Detail")->JsonValue;
					_di_ISuperObject pso = SO(DtlJson->ToString());
					TTableJson::JsonToDataSet(FQuery,pso);

					FQuery->First();
					FCurRecNo = m_DetailDataSet->RecNo;
					m_DetailDataSet->First();
					while (!FQuery->Eof)
					{
						if(FQuery->RecordStatus.Contains(rsModified) || FQuery->RecordStatus.Contains(rsNew))
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
					m_DetailDataSet->UpdateBatch(arAll);
					if(FCurRecNo <= m_DetailDataSet->RecordCount)
						m_DetailDataSet->RecNo = FCurRecNo;
				}
				ZDataSetOperateStatus = 1;
				m_MasterDataSet->AfterScroll = MasterDataSetAfterScroll;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "更新数据失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynDelete(TJSONObject *Json)
{
	try
	{
		if(Json->Size()>0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				ZDataSetOperateStatus = 1;
      }
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "删除数据失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynDeleteDetail(TJSONObject *Json)
{
	try
	{
		if(Json->Size()>0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				// 这里需返回主表记录
				m_DetailDataSet->Delete();
				m_DetailDataSet->UpdateBatch(arAll);
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "删除明细数据失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynCheck(TJSONObject *Json)
{
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(FQuery,pso);

				if(m_MasterDataSet->State == dsBrowse)
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
					m_MasterDataSet->Post();
					m_MasterDataSet->UpdateBatch(arAll);
				}
				else
				{
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
				}
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "审核数据操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynCloseOff(TJSONObject *Json)
{
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(FQuery,pso);

				if(m_MasterDataSet->State == dsBrowse)
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
					m_MasterDataSet->Post();
					m_MasterDataSet->UpdateBatch(arAll);
				}
				else
				{
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
				}
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "结清数据操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynRevoke(TJSONObject *Json)
{
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(FQuery,pso);

				if(m_MasterDataSet->State == dsBrowse)
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
					m_MasterDataSet->Post();
					m_MasterDataSet->UpdateBatch(arAll);
				}
				else
				{
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
				}

				if(m_DataSetType==2)
				{
					TJSONObject *DtlJson = (TJSONObject*)Json->Get("Detail")->JsonValue;
					_di_ISuperObject pso = SO(DtlJson->ToString());
					TTableJson::JsonToDataSet(FQuery,pso);

					FQuery->First();
					FCurRecNo = m_DetailDataSet->RecNo;
					m_DetailDataSet->First();
					while (!FQuery->Eof)
					{
						if (m_DetailDataSet->State == dsBrowse)
							m_DetailDataSet->Edit();

						for (int i = 0; i < FQuery->FieldCount; i++)
							m_DetailDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
						m_DetailDataSet->Post();
						FQuery->Next();
						m_DetailDataSet->Next();
					}
					FQuery->Close();
					m_DetailDataSet->UpdateBatch(arAll);
					if(m_DetailDataSet->RecordCount >= FCurRecNo)
						m_DetailDataSet->RecNo = FCurRecNo;
				}
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "作废数据操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynTally(TJSONObject *Json)
{
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(FQuery,pso);

				if(m_MasterDataSet->State == dsBrowse)
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
					m_MasterDataSet->Post();
					m_MasterDataSet->UpdateBatch(arAll);
				}
				else
				{
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
				}

				if(m_DataSetType==2)
				{
					TJSONObject *DtlJson = (TJSONObject*)Json->Get("Master")->JsonValue;
					_di_ISuperObject pso = SO(DtlJson->ToString());
					TTableJson::JsonToDataSet(FQuery,pso);

					FQuery->First();
					FCurRecNo = m_DetailDataSet->RecNo;
					m_DetailDataSet->First();
					while (!FQuery->Eof)
					{
						if(m_DetailDataSet->State == dsBrowse)
							m_DetailDataSet->Edit();

						for (int i = 0; i < FQuery->FieldCount; i++)
							m_DetailDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
						m_DetailDataSet->Post();
						FQuery->Next();
						m_DetailDataSet->Next();
					}
					FQuery->Close();
					m_DetailDataSet->UpdateBatch(arAll);
					if(m_DetailDataSet->RecordCount >= FCurRecNo)
						m_DetailDataSet->RecNo = FCurRecNo;
				}
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = "记账数据操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynCmdExec(TJSONObject *Json)
{
	int FCurRecNo;
	try
	{
		if(Json->Size() > 0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				TJSONObject *MstJson = (TJSONObject*)Json->Get("Master")->JsonValue;
				CoInitializeEx(NULL, COINIT_MULTITHREADED);
				_di_ISuperObject pso = SO(MstJson->ToString());
				TTableJson::JsonToDataSet(FQuery,pso);

				if(m_MasterDataSet->State == dsBrowse)
				{
					m_MasterDataSet->Edit();
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
					m_MasterDataSet->Post();
					m_MasterDataSet->UpdateBatch(arAll);
				}
				else
				{
					for (int i = 0; i < FQuery->FieldCount; i++)
						m_MasterDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
					FQuery->Close();
				}

				if(m_DataSetType==2)
				{
					TJSONObject *DtlJson = (TJSONObject*)Json->Get("Detail")->JsonValue;
					_di_ISuperObject pso = SO(DtlJson->ToString());
					TTableJson::JsonToDataSet(FQuery,pso);

					FQuery->First();
					FCurRecNo = m_DetailDataSet->RecNo;
					m_DetailDataSet->First();
					while (!FQuery->Eof)
					{
						if(m_DetailDataSet->State == dsBrowse)
							m_DetailDataSet->Edit();

						for (int i = 0; i < FQuery->FieldCount; i++)
							m_DetailDataSet->FieldValues[FQuery->Fields->Fields[i]->FieldName] = FQuery->FieldValues[FQuery->Fields->Fields[i]->FieldName];
						m_DetailDataSet->Post();
						FQuery->Next();
						m_DetailDataSet->Next();
					}
					FQuery->Close();
					m_DetailDataSet->RecNo = FCurRecNo;
				}
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage = "通用数据操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynValidateData(TJSONObject *Json)
{
	try
	{
		if(Json->Size()>0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "校验数据操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AsynExecSQL(TJSONObject *Json)
{
	try
	{
		if(Json->Size()>0)
		{
			String sStatus = Json->Get("Status")->JsonValue->Value();
			if(sStatus=="s")
			{
				ZDataSetOperateStatus = 1;
			}
			else
			{
				ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
				ZDataSetOperateStatus = 2;
			}
		}
	}
	catch (Exception &e)
	{
		ZDataSetErrorMessage  = "执行SQL操作失败，错误：" + e.Message;
		ZDataSetOperateStatus = 2;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::RecvErrorMessage(TJSONObject *Json)
{
	try
	{
		if(Json->Size() > 0)
		{
			ZDataSetErrorMessage  = Json->Get("ErrorMessage")->JsonValue->Value();
			ZDataSetOperateStatus = 2;
		}
	}
	catch (Exception &e)
	{
	}
}
//----------------------------------------------------------------------------
void __fastcall TJClientDataSet::ValidField(TValidType vt, TValidAffect va)
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			if(m_DataSetType==1 && (vt==vtDetail || vt==vtMasterDetail))
				throw Exception("当前系统是单表状态,校验类型设置不正确.");

			if(vt==vtMaster)
				va = vaCurRecNo;

			if(vt==vtMasterDetail)
				va = vaAll;

			int rc=0;
			if(vt==vtDetail && va==vaCurRecNo)
				rc = m_DetailDataSet->RecNo;

			TJSONObject *JSONObject = new TJSONObject();
			JSONObject->AddPair("Operate",asDSVerify);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("DataSetType",m_DataSetType);
			JSONObject->AddPair("MasterStatus",m_MasterDataSet->State);
			if(m_NeedValid)
				JSONObject->AddPair("NeedValid","t");
			else
				JSONObject->AddPair("NeedValid","f");
			JSONObject->AddPair("ValidType",vt);
			JSONObject->AddPair("ValidAffect",va);
			JSONObject->AddPair("ValidRecNo",rc);
			JSONObject->AddPair("MasterValidFieldList",BuildValidList(m_MasterValidFieldList));
			JSONObject->AddPair("DetailValidFieldList",BuildValidList(m_DetailValidFieldList));

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			for(int i=0;i<m_MasterDataSet->FieldCount;i++)
			{
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName),m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			if(m_DataSetType==2)
			{
				Json = TTableJson::DataSetToJson(m_DetailDataSet);
				JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			}
			ZDataSetOperateStatus = 0;

			TJSONObject *sj = ServerDataSet->ValidateData(JSONObject,m_ClassCode);
			AsynValidateData((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
  __finally
	{
		delete ScreenCursor;
  }
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Open()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		ZDataSetOperateStatus = 0;
		TJSONObject *JSONObject = new TJSONObject();
		JSONObject->AddPair(new TJSONPair("MasterWhere",m_MasterWhereString));
		JSONObject->AddPair(new TJSONPair("MasterOrder",m_MasterOrderString));
		JSONObject->AddPair(new TJSONPair("DetailWhere",m_DetailWhereString));
		JSONObject->AddPair(new TJSONPair("DetailOrder",m_DetailOrderString));
		TJSONObject *sj = ServerDataSet->Open(JSONObject,m_ClassCode);
		AsynOpen((TJSONObject *)(sj->Clone()));
		CheckResultStatus(ZDataSetOperateStatus);
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AddNew()
{
	if(m_DataSetActive)
	{
		if(m_MasterDataSet->State != dsBrowse)
			throw Exception("系统正处于编辑状态!");

		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->State != dsBrowse)
				throw Exception("系统从表正处于编辑状态!");
		}

		m_MasterDataSet->Append();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Insert()
{
	if(m_DataSetActive)
	{
		if(m_MasterDataSet->State != dsBrowse)
			throw Exception("系统正处于编辑状态!");

		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->State != dsBrowse)
				throw Exception("系统从表正处于编辑状态!");
		}
		m_MasterDataSet->Insert();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Edit()
{
	if(m_DataSetActive)
	{
		if(m_MasterDataSet->State != dsBrowse)
			throw Exception("系统正处于编辑状态!");

		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->State != dsBrowse)
				throw Exception("系统从表正处于编辑状态!");
		}
		m_MasterDataSet->Edit();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Delete()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			if(m_MasterDataSet->State != dsBrowse)
				throw Exception("系统正处于编辑状态!");

			if(m_DataSetType==2)
			{
				if(m_DetailDataSet->State != dsBrowse)
					throw Exception("系统子表正处于编辑状态!");
			}

			if(m_MasterDataSet->RecordCount < 1)
				throw Exception("没有记录可删除.");

			int rc;
			TJSONObject *JSONObject = new TJSONObject();
			JSONObject->AddPair("Operate",asDSDelete);
			JSONObject->AddPair("ClassID",m_ClassCode);

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			FQuery->Close();
			if(m_DataSetType==2)
			{
				Json = TTableJson::DataSetToJson(m_DetailDataSet);
				JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			}

			TJSONObject *sj = ServerDataSet->Delete(JSONObject,m_ClassCode);
			AsynDelete((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);

			if(m_DataSetType==2)
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
			m_MasterDataSet->UpdateBatch(arAll);
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Update()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	String sFieldName;
	TDataSetNotifyEvent MBeforePost, MAfterPost, DBeforePost, DAfterPost;
	try
	{
		MBeforePost = m_MasterDataSet->BeforePost;
		MAfterPost  = m_MasterDataSet->AfterPost;
		m_MasterDataSet->BeforePost  = NULL;
		m_MasterDataSet->AfterPost   = NULL;
		if(m_DataSetType==2)
		{
			DBeforePost = m_DetailDataSet->BeforePost;
			DAfterPost  = m_DetailDataSet->AfterPost;
			m_DetailDataSet->BeforePost = NULL;
			m_DetailDataSet->AfterPost  = NULL;
		}

		if(m_DataSetActive)
		{
			int rc;
			TValidType vt;
			TValidAffect va;
			TJSONObject *JSONObject = new TJSONObject();
			if(m_MasterDataSet->State == dsInsert || m_MasterDataSet->State == dsBrowse)
			{
				JSONObject->AddPair("Operate",asDSUpdate);
				JSONObject->AddPair("ClassID",m_ClassCode);
				JSONObject->AddPair("DataSetType",m_DataSetType);
				JSONObject->AddPair("MasterStatus",m_MasterDataSet->State);

				rc = 1;
				if(m_DataSetType==1)
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
					JSONObject->AddPair("NeedValid","t");
				else
					JSONObject->AddPair("NeedValid","f");

				JSONObject->AddPair("ValidType",vt);
				JSONObject->AddPair("ValidAffect",va);
				JSONObject->AddPair("ValidRecNo",rc);
				JSONObject->AddPair("MasterValidFieldList",BuildValidList(m_MasterValidFieldList));
				JSONObject->AddPair("DetailValidFieldList",BuildValidList(m_DetailValidFieldList));

				TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
				datasetStream->SaveToDataSet(FQuery);
				delete datasetStream;
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
				String Json = TTableJson::DataSetToJson(FQuery);
				JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
				FQuery->Close();
			}
			else if(m_MasterDataSet->State == Db::dsEdit)
			{
				JSONObject->AddPair("Operate",asDSUpdate);
				JSONObject->AddPair("ClassID",m_ClassCode);
				JSONObject->AddPair("DataSetType",m_DataSetType);
				JSONObject->AddPair("MasterStatus",m_MasterDataSet->State);

				rc = 1;
				va = vaCurRecNo;
				vt = vtMaster;
				if(m_NeedValid)
					JSONObject->AddPair("NeedValid","t");
				else
					JSONObject->AddPair("NeedValid","f");

				JSONObject->AddPair("ValidType",vt);
				JSONObject->AddPair("ValidAffect",va);
				JSONObject->AddPair("ValidRecNo",rc);
				JSONObject->AddPair("MasterValidFieldList",BuildValidList(m_MasterValidFieldList));
				JSONObject->AddPair("DetailValidFieldList",BuildValidList(m_DetailValidFieldList));

				TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
				datasetStream->SaveToDataSet(FQuery);
				delete datasetStream;
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
				FQuery->UpdateBatch(arAll);
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
				String Json = TTableJson::DataSetToJson(FQuery);
				JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
				FQuery->Close();
			}

			if(m_DataSetType == 2)
			{
				JSONObject->AddPair("DetailStatus",m_DtlRecStatus->Text);
				String Json = TTableJson::DataSetToJson(m_DetailDataSet);
				JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			}
      String sTemp = JSONObject->ToString();
			TJSONObject *sj = ServerDataSet->Update(JSONObject,m_ClassCode);
			AsynUpdate((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		m_MasterDataSet->BeforePost  = MBeforePost;
		m_MasterDataSet->AfterPost   = MAfterPost;
		if(m_DataSetType==2)
		{
			m_DetailDataSet->BeforePost = DBeforePost;
			m_DetailDataSet->AfterPost  = DAfterPost;
		}
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Cancel()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 2)
		{
			if(m_DetailDataSet->RecordCount > 0)
			{
				m_DetailDataSet->CancelBatch(arAll);
			}
		}
		m_MasterDataSet->CancelBatch(arAll);
	}
	else
		throw Exception("系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::AddDetail()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		m_DetailDataSet->Sort = "";
		m_DetailDataSet->Append();
	}
	else
		throw Exception("系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::InserDetail()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		m_DetailDataSet->Sort = "";
		m_DetailDataSet->Insert();
	}
	else
		throw Exception("系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::EditDetail()
{
	if(m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if (m_DetailDataSet->State != dsBrowse)
			throw Exception("系统从表正处于编辑状态!");

		m_DetailDataSet->Edit();
	}
	else
		throw Exception("系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DeleteDetail()
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			if(m_DataSetType == 1)
				throw Exception("当前系统为单表状态.");

			if(m_DetailDataSet->State != dsBrowse)
				throw Exception("系统从表正处于编辑状态!");

			if(m_DetailDataSet->RecordCount < 1)
				throw Exception("没有记录可删除.");

			TJSONObject *JSONObject = new TJSONObject();
			if(m_MasterDataSet->State == dsBrowse)
			{
				if(m_DetailDataSet->RecordStatus.Contains(rsModified)
				|| m_DetailDataSet->RecordStatus.Contains(rsUnmodified)
				|| m_DetailDataSet->RecordStatus.Contains(rsDeleted))
				{
					JSONObject->AddPair("Operate",asDSDeleteDetail);
					JSONObject->AddPair("ClientID",String((int)this));
					JSONObject->AddPair("ServerID",m_ServerDataSetHandle);
					JSONObject->AddPair("ClassID",m_ClassCode);

					TADODataSetStream *datasetStream = new TADODataSetStream(m_DetailStructure);
					datasetStream->SaveToDataSet(FQuery);
					delete datasetStream;
					FQuery->Append();
					for (int i = 0; i < m_DetailDataSet->FieldCount; i++)
					{
						if(m_DetailDataSet->Fields->Fields[i]->IsNull)
							SetNullFieldValue(FQuery->FieldByName(m_DetailDataSet->Fields->Fields[i]->FieldName), m_DetailDataSet->Fields->Fields[i]);
						else
							FQuery->FieldValues[m_DetailDataSet->Fields->Fields[i]->FieldName] = m_DetailDataSet->FieldByName(m_DetailDataSet->Fields->Fields[i]->FieldName)->OldValue;
					}
					FQuery->Post();
					String Json = TTableJson::DataSetToJson(FQuery);
					JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));

					TJSONObject *sj = ServerDataSet->DeleteDetail(JSONObject,m_ClassCode);
					AsynDeleteDetail((TJSONObject *)(sj->Clone()));
					CheckResultStatus(ZDataSetOperateStatus);
				}
				else
				{
					m_DetailDataSet->Delete();
				}
			}
			else
			{
				m_DetailDataSet->Delete();
			}
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::UpdateDetail()
{
	int value;
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		value = m_DetailDataSet->State;
		for (int i = 0; i < m_DetailLinkFields->Count; i++)
			m_DetailDataSet->FieldValues[m_DetailLinkFields->Strings[i]] = m_MasterDataSet->FieldValues[m_MasterLinkFields->Strings[i]];
		m_DetailDataSet->Post();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::CancelDetail()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		m_DetailDataSet->Cancel();
	}
	else
		throw Exception("系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Close()
{
	if(m_DataSetActive)
	{
		m_MasterDataSet->Close();
		TADODataSetStream *datasetStream=new TADODataSetStream(m_MasterStructure);
		datasetStream->SaveToDataSet(m_MasterDataSet);
		delete datasetStream;

		if (m_DataSetType == 2)
		{
			m_DetailDataSet->Close();
			TADODataSetStream *datasetStream=new TADODataSetStream(m_DetailStructure);
			datasetStream->SaveToDataSet(m_DetailDataSet);
			delete datasetStream;
		}
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::MoveFirst()
{
	if(m_DataSetActive)
		m_MasterDataSet->First();
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::MoveLast()
{
	if(m_DataSetActive)
		m_MasterDataSet->Last();
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::MoveNext()
{
	if(m_DataSetActive)
		m_MasterDataSet->Next();
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::MovePrior()
{
	if(m_DataSetActive)
		m_MasterDataSet->Prior();
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::MoveTo(int Distance)
{
	if (m_DataSetActive)
	{
		if (Distance < 1 || Distance > m_MasterDataSet->RecordCount)
			throw Exception("主表数据集指针移动越界");
		m_MasterDataSet->RecNo = Distance;
	}
	else
		throw Exception("系统尚未初始化.");
}

// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DetailFirst()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if(!m_DetailDataSet->Bof)
			m_DetailDataSet->First();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DetailLast()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if(!m_DetailDataSet->Eof)
			m_DetailDataSet->Last();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DetailPrior()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if(!m_DetailDataSet->Bof)
			m_DetailDataSet->Prior();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DetailNext()
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if(!m_DetailDataSet->Eof)
			m_DetailDataSet->Next();
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DetailMoveTo(int Distance)
{
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if(Distance < 1 || Distance > m_DetailDataSet->RecordCount)
			throw Exception("从表数据集指针移动越界");

		m_DetailDataSet->RecNo = Distance;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::LocateMaster(String KeyValues)
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
		if(m_MasterDataSet->RecordCount < 1) return false;
		index = KeyValues.Pos("\t");
		if(index > 0 && index < KeyValues.Length())
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
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			retval = m_MasterDataSet->Locate(m_MasterKeyFields,
				VarArrayOf(mv, valcount), Opts);
			return retval;
		}
		else
		{
			Variant sv;
			if (KeyValues.Length() > 0)
			{
				while (KeyValues[KeyValues.Length()] == '\t')
				{
					KeyValues.Delete(KeyValues.Length(), 1);
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
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::LocateDetail(String KeyValues)
{
	int index, valcount;
	bool retval, isfiltered;
	String valstr, filterstr;
	TLocateOptions Opts;
	if(m_DataSetActive)
	{
		if(m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");
		Opts.Clear();
		Opts << loCaseInsensitive;
		valcount = 0;
		if(m_DetailDataSet->RecordCount < 1) return false;
		index = KeyValues.Pos("\t");
		if(index > 0)
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
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			retval = m_DetailDataSet->Locate(m_DetailKeyFields,
				VarArrayOf(mv, valcount), Opts);
			return retval;
		}
		else
		{
			Variant sv;
			if (KeyValues.Length() > 0)
			{
				while (KeyValues[KeyValues.Length()] == '\t')
				{
					KeyValues.Delete(KeyValues.Length(), 1);
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
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
TField *__fastcall TJClientDataSet::FindMasterField(String fieldname)
{
	if (m_DataSetActive)
	{
		return m_MasterDataSet->FindField(fieldname);
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
TField *__fastcall TJClientDataSet::FindDetailField(String fieldname)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");
		return m_DetailDataSet->FindField(fieldname);
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::FindMasterKey(String KeyValues)
{
	// 未修改可能出错
	int index, valcount;
	bool isfiltered;
	String valstr, filterstr;
	Variant vr;
	if (m_DataSetActive)
	{
		valcount = 0;
		if (m_MasterDataSet->RecordCount < 1)
			return false;
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
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			vr = m_MasterDataSet->Lookup(m_MasterKeyFields,
				VarArrayOf(mv, valcount), m_MasterKeyFields);
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
					KeyValues.Delete(KeyValues.Length(), 1);
					if (KeyValues.Length() == 0)
						break;
				}
			}
			sv = Variant(KeyValues);
			vr = m_MasterDataSet->Lookup(m_MasterKeyFields, sv,
				m_MasterKeyFields);
			if (vr.IsNull())
				return false;
			else
				return true;
		}
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::FindDetailKey(String KeyValues)
{
	// 未修改可能出错
	int index, valcount;
	bool isfiltered;
	String valstr, filterstr;
	Variant vr;
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");
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
			if (KeyValues.IsEmpty() == false)
				mv[valcount] = Variant(KeyValues);
			FQuery->Close();
			FQuery->Clone(m_DetailDataSet, ltReadOnly);
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
					KeyValues.Delete(KeyValues.Length(), 1);
					if (KeyValues.Length() == 0)
						break;
				}
			}
			sv = Variant(KeyValues);
			FQuery->Clone(m_DetailDataSet, ltReadOnly);
			vr = FQuery->Lookup(m_DetailKeyFields, sv, m_DetailKeyFields);
			FQuery->Close();
			if (vr.IsNull())
				return false;
			else
				return true;
		}
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
Variant __fastcall TJClientDataSet::GetMasterValue(String fieldname)
{
	if (m_DataSetActive)
	{
		TField *mfield = m_MasterDataSet->FieldByName(fieldname);
		// 基于字符串才允许为空
		if (NullFieldIsString(mfield))
			return "";
		else
			return mfield->Value;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
Variant __fastcall TJClientDataSet::GetMasterOldValue(String fieldname)
{
	if (m_DataSetActive)
	{
		TField *mfield = m_MasterDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->OldValue;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetMasterValue(String fieldname, Variant value)
{
	if (m_DataSetActive)
	{
		m_MasterDataSet->FieldValues[fieldname] = value;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
Variant __fastcall TJClientDataSet::GetDetailValue(String fieldname)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");
		TField *mfield = m_DetailDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->Value;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
Variant __fastcall TJClientDataSet::GetDetailOldValue(String fieldname)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		TField *mfield = m_DetailDataSet->FieldByName(fieldname);
		if (NullFieldIsString(mfield)) // 基于字符串才允许为空
				return "";
		else
			return mfield->OldValue;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetDetailValue(String fieldname, Variant value)
{
	if (m_DataSetActive)
	{
		if (m_DataSetType == 1)
			throw Exception("当前系统为单表状态.");

		if (m_DetailDataSet->State == dsBrowse)
			throw Exception("错误:当前不是编辑状态,拒绝赋值!");

		m_DetailDataSet->FieldValues[fieldname] = value;
	}
	else
		throw Exception("系统尚未初始化.");
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::CmdExec(String Param)
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	try
	{
		TJSONObject *JSONObject = new TJSONObject();
		if(m_DataSetActive)
		{
			JSONObject->AddPair("Operate",asDSCommExecute);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("DataSetType",m_DataSetType);
			JSONObject->AddPair("Param",Param);
			JSONObject->AddPair("MasterStatus",m_MasterDataSet->State);

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			if(m_DataSetType == 2)
			{
				Json = TTableJson::DataSetToJson(m_DetailDataSet);
				JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			}

			TJSONObject *sj = ServerDataSet->CmdExec(JSONObject,m_ClassCode);
			AsynCmdExec((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
			if(m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->UpdateBatch(arAll);
			}

			if(m_DataSetType == 2)
			{
				m_DetailDataSet->UpdateBatch(arAll);
			}
		}
		else
		{
			throw Exception("系统尚未初始化.");
    }
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Check(int IsCheck)
{
	TfsScreenCursor * ScreenCursor=new TfsScreenCursor();
	try
	{
		int rc;
		TValidType vt;
		TValidAffect va;
		TJSONObject *JSONObject = new TJSONObject();
		if(m_DataSetActive)
		{
			JSONObject->AddPair("Operate",asDSCheck);
			JSONObject->AddPair("ClientID",String((int)this));
			JSONObject->AddPair("ServerID",m_ServerDataSetHandle);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("DataSetType",m_DataSetType);
			JSONObject->AddPair("MasterStatus",m_MasterDataSet->State);
			JSONObject->AddPair("IsCheck",IsCheck);

			rc = 1;
			if(m_DataSetType == 1)
				va = vaCurRecNo;
			else
				va = vaAll;

			if(m_MasterDataSet->State == dsInsert)
			{
				if(m_DataSetType == 1)
					vt == vtMaster;
				else
					vt = vtMasterDetail;
			}
			else
				vt == vtDetail;

			if(m_NeedValid)
				JSONObject->AddPair("NeedValid","t");
			else
				JSONObject->AddPair("NeedValid","f");

			JSONObject->AddPair("ValidType",vt);
			JSONObject->AddPair("ValidAffect",va);
			JSONObject->AddPair("ValidRecNo",rc);
			JSONObject->AddPair("MasterValidFieldList",BuildValidList(m_MasterValidFieldList));
			JSONObject->AddPair("DetailValidFieldList",BuildValidList(m_DetailValidFieldList));

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			if(m_MasterDataSet->State == dsInsert)
			{
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
				}
				FQuery->Post();
			}
			else if(m_MasterDataSet->State == Db::dsEdit)
			{
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName)->OldValue;
				}
				FQuery->Post();
				FQuery->UpdateBatch(arAll);
				FQuery->Edit();
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
				}
				FQuery->Post();
			}
			else
			{
				for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
				{
					if(m_MasterDataSet->Fields->Fields[i]->IsNull)
						SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
					else
						FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
				}
				FQuery->Post();
				FQuery->UpdateBatch(arAll);
			}

			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			if(m_DataSetType == 2)
			{
				Json = TTableJson::DataSetToJson(m_DetailDataSet);
				JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			}

			TJSONObject *sj = ServerDataSet->Check(JSONObject,m_ClassCode);
			AsynCheck((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
			if(m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->UpdateBatch(arAll);
			}
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::CloseOff(int IsClose)
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			TJSONObject *JSONObject = new TJSONObject();
			JSONObject->AddPair("Operate",asDSCloseOff);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("IsClose",IsClose);

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			if(m_DataSetType == 2)
			{
				Json = TTableJson::DataSetToJson(m_DetailDataSet);
				JSONObject->AddPair("Detail",(TJSONObject*)TJSONObject::ParseJSONValue(Json));
			}

			TJSONObject *sj = ServerDataSet->CloseOff(JSONObject,m_ClassCode);
			AsynCloseOff((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
			if(m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->UpdateBatch(arAll);
			}

			if(m_DataSetType == 2)
			{
				m_DetailDataSet->UpdateBatch(arAll);
			}
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Revoke(int IsRevoke)
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			TJSONObject *JSONObject = new TJSONObject();
			JSONObject->AddPair("Operate",asDSCancel);
			JSONObject->AddPair("ClientID",String((int)this));
			JSONObject->AddPair("ServerID",m_ServerDataSetHandle);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("IsRevoke",IsRevoke);

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));

			TJSONObject *sj = ServerDataSet->Revoke(JSONObject,m_ClassCode);
			AsynRevoke((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
			if(m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->UpdateBatch(arAll);
			}
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::Tally(int IsTally)
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			TJSONObject *JSONObject = new TJSONObject();
			JSONObject->AddPair("Operate",asDSRecord);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("IsTally",IsTally);

			TADODataSetStream *datasetStream = new TADODataSetStream(m_MasterStructure);
			datasetStream->SaveToDataSet(FQuery);
			delete datasetStream;
			FQuery->Append();
			for (int i = 0; i < m_MasterDataSet->FieldCount; i++)
			{
				if(m_MasterDataSet->Fields->Fields[i]->IsNull)
					SetNullFieldValue(FQuery->FieldByName(m_MasterDataSet->Fields->Fields[i]->FieldName), m_MasterDataSet->Fields->Fields[i]);
				else
					FQuery->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName] = m_MasterDataSet->FieldValues[m_MasterDataSet->Fields->Fields[i]->FieldName];
			}
			FQuery->Post();
			String Json = TTableJson::DataSetToJson(FQuery);
			JSONObject->AddPair("Master",(TJSONObject*)TJSONObject::ParseJSONValue(Json));

			TJSONObject *sj = ServerDataSet->Tally(JSONObject,m_ClassCode);
			AsynTally((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
			if(m_MasterDataSet->State != dsBrowse)
			{
				m_MasterDataSet->Post();
				m_MasterDataSet->UpdateBatch(arAll);
			}
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::ExecSQL(String sqlstr)
{
	TfsScreenCursor * ScreenCursor = new TfsScreenCursor();
	try
	{
		if(m_DataSetActive)
		{
			ZDataSetOperateStatus = 0;
			TJSONObject *JSONObject = new TJSONObject();
			JSONObject->AddPair("Operate",asDSSQL);
			JSONObject->AddPair("ClassID",m_ClassCode);
			JSONObject->AddPair("SQLStr",sqlstr);

			TJSONObject *sj = ServerDataSet->ExecSQL(JSONObject);
			AsynExecSQL((TJSONObject *)(sj->Clone()));
			CheckResultStatus(ZDataSetOperateStatus);
		}
		else
		{
			throw Exception("系统尚未初始化.");
		}
	}
	__finally
	{
		delete ScreenCursor;
	}
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterSQLString()
{
	return m_MasterSQLString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterSQLString(String value)
{
	m_MasterSQLString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailSQLString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailSQLString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailSQLString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailSQLString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterWhereString()
{
	return m_MasterWhereString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterWhereString(String value)
{
	m_MasterWhereString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailWhereString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailWhereString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailWhereString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailWhereString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterOrderString()
{
	return m_MasterOrderString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterOrderString(String value)
{
	m_MasterOrderString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailOrderString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailOrderString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailOrderString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailOrderString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterGroupString()
{
	return m_MasterGroupString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterGroupString(String value)
{
	m_MasterGroupString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailGroupString()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailGroupString;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailGroupString(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailGroupString = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterKeyFields()
{
	return m_MasterKeyFields;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterKeyFields(String value)
{
	m_MasterKeyFields = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailKeyFields()
{
	if (m_DataSetType == 1)
		return "";
	else
		return m_DetailKeyFields;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailKeyFields(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailKeyFields = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_LinkFields()
{
	if (m_DataSetType == 1)
		return "";
	else
		return BuildLinkFields();
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_LinkFields(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	ExtractLinkFields(value);
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterSort()
{
	return m_MasterDataSet->Sort;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterSort(String value)
{
	m_MasterDataSet->Sort = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailSort()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Sort;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailSort(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailDataSet->Sort = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_Filter()
{
	return m_MasterDataSet->Filter;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_Filter(String value)
{
	m_MasterDataSet->Filter = value;
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_Filtered()
{
	return m_MasterDataSet->Filtered;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_Filtered(bool value)
{
	m_MasterDataSet->Filtered = value;
}
// ---------------------------------------------------------------------------
TDataSetState __fastcall TJClientDataSet::get_MasterStatus()
{
	return m_MasterDataSet->State;
}
// ---------------------------------------------------------------------------
TDataSetState __fastcall TJClientDataSet::get_DetailStatus()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->State;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DataSetType()
{
	return m_DataSetType;
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_Bof()
{
	return m_MasterDataSet->Bof;
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_Eof()
{
	return m_MasterDataSet->Eof;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_RecordCount()
{
	return m_MasterDataSet->RecordCount;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_CurRecNo()
{
	return m_MasterDataSet->RecNo;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_MasterFieldCount()
{
	return m_MasterDataSet->FieldCount;
}
// ---------------------------------------------------------------------------
TFields *__fastcall TJClientDataSet::get_MasterFields()
{
	return m_MasterDataSet->Fields;
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_DetailBof()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Bof;
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_DetailEof()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Eof;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DetailCount()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->RecordCount;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DetailRecNo()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->RecNo;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DetailFieldCount()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->FieldCount;
}
// ---------------------------------------------------------------------------
TFields *__fastcall TJClientDataSet::get_DetailFields()
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	return m_DetailDataSet->Fields;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterFieldName(int index)
{
	return m_MasterDataSet->Fields->Fields[index]->FieldName;
}
// ---------------------------------------------------------------------------
TFieldType __fastcall TJClientDataSet::get_MasterFieldType(int index)
{
	return m_MasterDataSet->Fields->Fields[index]->DataType;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_MasterFieldSize(int index)
{
	return m_MasterDataSet->Fields->Fields[index]->Size;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailFieldName(int index)
{
	return m_DetailDataSet->Fields->Fields[index]->FieldName;
}
// ---------------------------------------------------------------------------
TFieldType __fastcall TJClientDataSet::get_DetailFieldType(int index)
{
	return m_DetailDataSet->Fields->Fields[index]->DataType;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DetailFieldSize(int index)
{
	return m_DetailDataSet->Fields->Fields[index]->Size;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::BuildLinkStr()
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
String __fastcall TJClientDataSet::BuildLinkFields()
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
void __fastcall TJClientDataSet::ExtractLinkFields(String value)
{
	String s;
	int index;
	if (m_DataSetType == 1)	return;
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
void __fastcall TJClientDataSet::BuildDetailFilter()
{
	String filterstr;
	int ftype;
	TField *FField;
	for (int i = 0; i < m_MasterLinkFields->Count; i++)
	{
		FField = m_DetailDataSet->Fields->FindField(m_DetailLinkFields->Strings[i]);
		if (FField != NULL)
			ftype = CheckFieldType(FField);
		else
			throw Exception("从表关联字段:" + m_DetailLinkFields->Strings[i] + "未找到.");

		if (ftype == 1)
			filterstr += m_DetailLinkFields->Strings[i] + "='" + m_MasterDataSet->FieldByName(m_MasterLinkFields->Strings[i])->AsString + "'";
		else
			filterstr += m_DetailLinkFields->Strings[i] + "=" + m_MasterDataSet->FieldByName(m_MasterLinkFields->Strings[i])->AsString;
		if (i < m_MasterLinkFields->Count - 1)
			filterstr += " and ";
	}
	m_DetailDataSet->Filtered = false;
	m_DetailDataSet->Filter = filterstr;
	m_DetailDataSet->Filtered = true;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::CheckFieldType(TField *Field)
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
void __fastcall TJClientDataSet::CheckResultStatus(int status)
{
	String errmsg = ZDataSetErrorMessage;
	ZDataSetErrorMessage = "";
	if(status == 2)
	{
		if(errmsg > "")
			throw Exception(errmsg);
	}
	else if(status == 3)
	{
		throw Exception("系统操作超时.");
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::BuildDetailStatus()
{
	if (m_DataSetType == 2)
	{
		// m_DetailEditStatus->Clear();
		// for(int i=0;i<m_DetailDataSet->RecordCount;i++)
		// m_DetailEditStatus->Add(dsBrowse);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetDataSetDisplayName(TADODataSet *ds, TStringList *dn, TStringList *fn)
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
String __fastcall TJClientDataSet::BuildValidList(String value)
{
	String retstr;
	int index;
	retstr = "";
	index = value.Pos(";");
	while (index > 0)
	{
		retstr += value.SubString(1, index - 1) + "\r\n";
		value.Delete(1, index);
		index = value.Pos(";");
	}
	if (!value.IsEmpty())
		retstr += value + "\r\n";
	return retstr;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterValidFieldList()
{
	return m_MasterValidFieldList;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_MasterValidFieldList(String value)
{
	m_MasterValidFieldList = value;
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailValidFieldList()
{
	return m_DetailValidFieldList;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::set_DetailValidFieldList(String value)
{
	if (m_DataSetType == 1)
		throw Exception("当前系统为单表状态.");
	m_DetailValidFieldList = value;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::ExitClientDataSet()
{
	// SendMessage(m_Handle,WM_TERMINATE_THREAD,0,0);
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_MasterFilterField(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception("字段下标越界");
	if (index >= m_MasterFilterFields->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_MasterFilterFields->Strings[index].ToInt();
}
// ---------------------------------------------------------------------------
bool __fastcall TJClientDataSet::get_DetailFilterField(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception("字段下标越界");
	if (index >= m_DetailFilterFields->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_DetailFilterFields->Strings[index].ToInt();
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_MasterFieldAttr(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception("字段下标越界");
	if (index >= m_MasterFieldAttr->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_MasterFieldAttr->Strings[index].ToInt();
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DetailFieldAttr(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception("字段下标越界");
	if (index >= m_DetailFieldAttr->Count) // 有些查询语句和视图用.* 来返回字段会造成超标
			return 0;
	else
		return m_DetailFieldAttr->Strings[index].ToInt();
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_MasterFieldExpr(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception("字段下标越界");
	return m_MasterFieldExpr->Strings[index];
}
// ---------------------------------------------------------------------------
String __fastcall TJClientDataSet::get_DetailFieldExpr(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception("字段下标越界");
	return m_DetailFieldExpr->Strings[index];
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_MasterAttrType(int index)
{
	if (index < 0 || index >= m_MasterDataSet->FieldCount)
		throw Exception("字段下标越界");
	return m_MasterAttrType->Strings[index].ToInt();
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::get_DetailAttrType(int index)
{
	if (index < 0 || index >= m_DetailDataSet->FieldCount)
		throw Exception("字段下标越界");
	return m_DetailAttrType->Strings[index].ToInt();
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SaveMasterToFile(const WideString FileName,
	TPersistFormat Format, bool bFiltered, bool bMoneyHide,
	String ClearMasterFieldsString)
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
				mFilter = mFilter.SubString(1, mFilter.Length() - 4);
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
void __fastcall TJClientDataSet::SaveDetailToFile(const WideString FileName,
	TPersistFormat Format, bool bFiltered, bool bMoneyHide,
	String ClearDetailFieldsString)
{
	if (DataSetType != 2)
		throw Exception("该数据集不是主从结构");

	bool bfilter = m_DetailDataSet->Filtered;
	try
	{
		m_DetailDataSet->Filtered = bFiltered;
		m_DetailDataSet->SaveToFile(FileName, Format);
		if (bMoneyHide)
			ClearMoneyDataSet(FileName, ClearDetailFieldsString);
	}
	__finally
	{
		m_DetailDataSet->Filtered = bfilter;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SaveMasterToFile(const WideString FileName,
	TPersistFormat Format, String sFilter, bool bMoneyHide,
	String ClearMasterFieldsString)
{
	TBookmark SavePlace = m_MasterDataSet->GetBookmark();
	String mFilter = "", oldFilter = m_MasterDataSet->Filter;
	bool oldFiltered = m_MasterDataSet->Filtered;
	try
	{
		if (sFilter != "")
		{
			m_MasterDataSet->Filtered = false;
			m_MasterDataSet->Filter = sFilter;
			m_MasterDataSet->Filtered = true;
		}
		m_MasterDataSet->SaveToFile(FileName, Format);
		if (bMoneyHide)
			ClearMoneyDataSet(FileName, ClearMasterFieldsString);
	}
	__finally
	{
		m_MasterDataSet->Filtered = false;
		m_MasterDataSet->Filter = oldFilter;
		m_MasterDataSet->Filtered = oldFiltered;
		if (m_MasterDataSet->RecordCount > 0)
			m_MasterDataSet->GotoBookmark(SavePlace);
		m_MasterDataSet->FreeBookmark(SavePlace);
	}
}
// ---------------------------------------------------------------------------
TADODataSet* __fastcall TJClientDataSet::GetDetailDataSet()
{
	if(m_DataSetType)
		return m_DetailDataSet;
	else
		return NULL;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::ClearMoneyDataSet(String FileName, String FieldsString)
{
	TADOQuery * AdoDataSet = new TADOQuery(NULL);
	TStringList *fieldString = new TStringList();
	try
	{
		AdoDataSet->LoadFromFile(FileName);
		fieldString->Delimiter = '\t';
		fieldString->DelimitedText = FieldsString;
		AdoDataSet->First();
		while (!AdoDataSet->Eof)
		{
			AdoDataSet->Edit();
			for (int i = 0; i < fieldString->Count; i++)
			{
				AdoDataSet->FieldByName(fieldString->Strings[i])->Value = 0;
			}
			AdoDataSet->UpdateBatch(arAll);
			AdoDataSet->Next();
		}
		AdoDataSet->SaveToFile(FileName, pfXML);
	}
	__finally
	{
		delete AdoDataSet;
		delete fieldString;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::MasterDataSetAfterScroll(TDataSet *DataSet)
{
	if(m_DataSetType == 2)
	{
		BuildDetailFilter();
		// 明细表记录的状态：0-浏览;1-新增;2-修改;3-删除
		InitDetailRecordStatus(m_DetailDataSet);
	}
	DoClientDataSetAfterScroll();
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::DoClientDataSetAfterScroll()
{
	if(ZDataSetOperateStatus != 0)
	{
		if(FClientDataSetAfterScroll)
			FClientDataSetAfterScroll(m_MasterDataSet);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetMasterDataSetBeforePost(TDataSetNotifyEvent value)
{
	m_MasterDataSet->BeforePost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TJClientDataSet::GetMasterDataSetBeforePost()
{
	return m_MasterDataSet->BeforePost;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetMasterDataSetAfterPost(TDataSetNotifyEvent value)
{
	m_MasterDataSet->AfterPost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TJClientDataSet::GetMasterDataSetAfterPost()
{
	return m_MasterDataSet->AfterPost;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetDetailDataSetBeforePost(TDataSetNotifyEvent value)
{
	if(m_DataSetType == 2)
		m_DetailDataSet->BeforePost = value;
}
// ---------------------------------------------------------------------------
TDataSetNotifyEvent __fastcall TJClientDataSet::GetDetailDataSetBeforePost()
{
	if(m_DataSetType == 2)
		return m_DetailDataSet->BeforePost;
	else
		return NULL;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::GetSysDbType()
{
	return FClientBroker->SysDbType;
}
// ---------------------------------------------------------------------------
int __fastcall TJClientDataSet::GetAccDbType()
{
	return FClientBroker->AccDbType;
}
// ---------------------------------------------------------------------------
void __fastcall TJClientDataSet::SetNullFieldValue(TField *DestField, TField* Sourcefield)
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
bool __fastcall TJClientDataSet::NullFieldIsString(TField *SourcField)
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
void __fastcall TJClientDataSet::InitDetailRecordStatus(TADODataSet *ds)
{
	if(ds==NULL) return;
	m_DtlRecStatus->Clear();
	ds->First();
	while(!ds->Eof)
	{
		// 明细表记录的状态：0-浏览;1-新增;2-修改;3-删除
		m_DtlRecStatus->Add("0");
		ds->Next();
	}
}
// ---------------------------------------------------------------------------
