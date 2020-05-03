//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop

#include "DataSnapClientDataSet.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TDataSnapClientDataSet::TDataSnapClientDataSet(TComponent* Owner)
	: TClientDataSet(Owner)
{
   FSort="";
}
{
}
void __fastcall TDataSnapClientDataSet::LoadFromStream(System::Classes::TStream* Stream)
{
  Close();
  	if (Stream->Size == -1) // ��֪����С
	{
		const int BufSize = 0xF000;
		void *Buffer;
		int ReadCount=0,TotalCount=0;
		TMemoryStream *ms = new TMemoryStream();
		try
		{
			Stream->Position=0;
			Buffer = AllocMem(NativeInt(BufSize));
			while(true)
			{
				ReadCount = Stream->Read(Buffer, BufSize);
				TotalCount=TotalCount+ReadCount;
				if (ReadCount > 0)
					ms->WriteBuffer(Buffer, ReadCount);
				if (ReadCount < BufSize)
					break;
			}
			 delete Stream;
			 Stream=ms;
		}
		__finally
		{
			FreeMemory(Buffer);
			//delete ms;
		}
	}
	Stream->Position=0;

  ReadDataPacket(Stream, False);
  Open();
}
//---------------------------------------------------------------------------

/*
void __fastcall TDataSnapClientDataSet::GetDetailLinkFields(System::Generics::Collections::TList__1<TField*> * MasterFields, System::Generics::Collections::TList__1<TField*> * DetailFields)
{
   //	TDataSet::GetDetailLinkFields(MasterFields,DetailFields);
}
*/
//---------------------------------------------------------------------------
void __fastcall TDataSnapClientDataSet::SetSort(String Value)
{
  if(FSort!=Value)
  {
	FSort=Value;
	if(Trim(FSort)=="") //Ϊ��
	{
	   this->IndexName="";  //ȡ����ǰ����
		 return;
	}
	//�ֽ������ֶ�
	TIndexOptions indexOptions;
	String SortIndexName="Index_FST";
	String SortField,SortFieldList="";
	String DescFieldList="";
	String SortItem,SortFlag;
	TStringList *SortStrList=new TStringList();
	try
	{
//		SortStrList->Delimiter=',';
//		SortStrList->DelimitedText=Value;  //Delimiter������bug -csc 2014-09-02
		SortStrList->Text = StringReplace(Value, ",", "\r\n", TReplaceFlags() << rfReplaceAll);

		for(int i=0;i<SortStrList->Count;i++)
		{
			SortItem=SortStrList->Strings[i];
			int  flagPos= SortItem.Pos(" ");//����λ��
			if(flagPos>1)
			{
			   SortField = SortItem.SubString(1, flagPos - 1);
//			   SortFlag = SortItem.SubString(i + 1, SortItem.Length()-flagPos);
			   SortFlag = SortItem.SubString(flagPos + 1, SortItem.Length()-flagPos); // -csc 2014-09-02
			   if (Trim(SortFlag).SubString(1,3).UpperCase() == "DES") //�ǽ���
			   {
			       //���콵���ֶ�
				   if(DescFieldList>"") //���ӷָ���
					 DescFieldList=DescFieldList+";";
				   DescFieldList=DescFieldList+SortField;
			   }
			}
			else
			 SortField=SortItem;
		   //���������ֶ�
		   if(SortFieldList>"") //���ӷָ���
			 SortFieldList=SortFieldList+";";
		   SortFieldList=SortFieldList+SortField;
			//������������
//		   if(SortIndexName>"")
//			 SortIndexName=SortIndexName+"_";
//		   SortIndexName=SortIndexName+SortField;
		}

	  if(this->IndexName==SortIndexName)  //�Ƿ��Ѵ���
		 this->DeleteIndex(SortIndexName);
	  //������������ʹ����Ч
	  if(DescFieldList>"")
	   indexOptions<<ixDescending;
	  AddIndex(SortIndexName,SortFieldList,indexOptions,DescFieldList,"",0);
	  IndexName=SortIndexName;
	}
	__finally
	{
		delete SortStrList;
	}
  }
}