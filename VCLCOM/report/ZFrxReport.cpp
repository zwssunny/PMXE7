//---------------------------------------------------------------------------

#include <basepch.h>

#pragma hdrstop

#include "ZFrxReport.h"
#include "CopyRight.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZFrxReport *)
{
        new TZFrxReport(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZFrxReport::TZFrxReport(TComponent* Owner)
        : TComponent(Owner)
{
  // checkCopyRight();
   p = NULL;
   FOnGetValue = NULL;
   FOnSaveReport = NULL;
   FOnSetFieldAliases = NULL;
   FOnBeforDesig=NULL;
   FReportPath = "";
   FTitleColor = clBtnFace  ;
}
//---------------------------------------------------------------------------
namespace Zfrxreport
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TZFrxReport)};
				 RegisterComponents("ZReport", classes, 0);
		}
}
//---------------------------------------------------------------------------
void __fastcall TZFrxReport::SetReportPath(String  AReportPath)
{
     if (!AReportPath.IsEmpty())
     {
          FReportPath = AReportPath;
     }
}
String __fastcall TZFrxReport::GetReportPath()
{
   return  FReportPath;
}
void __fastcall TZFrxReport::ShowReport()
{
   try
   {
       if (!p)
		   p = new  TFRPBaseForm(this);
       p->TitleCaption = FCaption;
       p->TitleColor = FTitleColor;
			 p->Reportpath = FReportPath;
			 p->OnAfterExportReport = this->FOnAfterExportReport;
       if (FOnGetValue)
          p->OnGetValue  = FOnGetValue;
       if (FOnGetVariables)
          p->OnGetVariables = FOnGetVariables;
       if (FOnSetFieldAliases)
          p->OnSetFieldAliases = FOnSetFieldAliases;
       if(FOnSaveReport)
		  p->OnSaveReport=FOnSaveReport;
	   if(FOnUserDefineFunction)
		  p->OnUserDefineFunction = FOnUserDefineFunction;
	   if(FOnBeforDesig)
		 p->OnBeforDesig=FOnBeforDesig;
       p->ShowReport();
       p->ShowModal();

   }
   __finally
   {
      delete p;
      p = NULL;
   }
}

void __fastcall TZFrxReport::ShowReport(String XmlFileName)
{
   try
   {
       if (!p)
		   p = new  TFRPBaseForm(this);
       if (XmlFileName != "")
       {
          p->MDataSet = XmlFileName;
       }
       p->TitleCaption = FCaption;
       p->TitleColor = FTitleColor;
			 p->Reportpath = FReportPath;
			 p->OnAfterExportReport = this->FOnAfterExportReport;
       if (FOnGetValue)
          p->OnGetValue  = FOnGetValue;
       if (FOnGetVariables)
          p->OnGetVariables = FOnGetVariables;
       if (FOnSetFieldAliases)
          p->OnSetFieldAliases = FOnSetFieldAliases;
       if(FOnSaveReport)
		  p->OnSaveReport=FOnSaveReport;
	   if(FOnUserDefineFunction)
		  p->OnUserDefineFunction = FOnUserDefineFunction;
	   if(FOnBeforDesig)
		 p->OnBeforDesig=FOnBeforDesig;
       p->ShowReport();
       p->ShowModal();
   }
   __finally
   {
      delete p;
      p = NULL;
   }
}

void __fastcall TZFrxReport::ShowReport(String MXmlFileName,String DXmlFileName,String AMDLinkString)
{
   try
   {
        if (!p)
		   p = new  TFRPBaseForm(this);
       //---------------------------
       if (MXmlFileName != "")
       {
          p->MDataSet= MXmlFileName;
       }
       //---------------------------------
       if (DXmlFileName != "")
       {
          p->DDataSet = DXmlFileName;
       }
       p->TitleCaption = FCaption;
       p->TitleColor = FTitleColor;
       p->Reportpath = FReportPath;
			 p->MDLinkString = AMDLinkString;
			 p->OnAfterExportReport = this->FOnAfterExportReport;
       if (FOnGetValue)
          p->OnGetValue  = FOnGetValue;
       if (FOnGetVariables)
          p->OnGetVariables = FOnGetVariables;
       if (FOnSetFieldAliases)
          p->OnSetFieldAliases = FOnSetFieldAliases;
       if(FOnSaveReport)
		  p->OnSaveReport=FOnSaveReport;
	   if(FOnUserDefineFunction)
		  p->OnUserDefineFunction = FOnUserDefineFunction;
	   if(FOnBeforDesig)
		 p->OnBeforDesig=FOnBeforDesig;
       p->ShowReport();
       p->ShowModal();
   }
   __finally
   {
      delete p;
      p = NULL;
   }
}
void __fastcall TZFrxReport::ShowReport(String MXmlFileName,String DXmlFileName,String DXmlFileNameOther,String AMDLinkString,String AMDLinkStringOther)
{
   try
   {
        if (!p)
		   p = new  TFRPBaseForm(this);
       //---------------------------
       if (MXmlFileName != "")
       {
          p->MDataSet= MXmlFileName;
       }
       //---------------------------------
       if (DXmlFileName != "")
       {
          p->DDataSet = DXmlFileName;
       }
       //---------------------------------
       if (DXmlFileNameOther != "")
       {
          p->DDataSetOther = DXmlFileNameOther;
       }
       p->TitleCaption = FCaption;
       p->TitleColor = FTitleColor;
       p->Reportpath = FReportPath;
       p->MDLinkString = AMDLinkString;
			 p->MDLinkString2 = AMDLinkStringOther;
			 p->OnAfterExportReport = this->FOnAfterExportReport;
       if (FOnGetValue)
          p->OnGetValue  = FOnGetValue;
       if (FOnGetVariables)
          p->OnGetVariables = FOnGetVariables;
       if (FOnSetFieldAliases)
          p->OnSetFieldAliases = FOnSetFieldAliases;
       if(FOnSaveReport)
		  p->OnSaveReport=FOnSaveReport;
	   if(FOnUserDefineFunction)
		  p->OnUserDefineFunction = FOnUserDefineFunction;
	   if(FOnBeforDesig)
		 p->OnBeforDesig=FOnBeforDesig;
       p->ShowReport();
       p->ShowModal();
   }
   __finally
   {
      delete p;
      p = NULL;
   }
}
TfrxDBDataset * __fastcall TZFrxReport::GetMDataSet()
{
    if (!p)
	   p = new  TFRPBaseForm(this);
    return p->frxMDataSet;
}

TfrxDBDataset * __fastcall TZFrxReport::GetDDataSet()
{
   if (!p)
	   p = new  TFRPBaseForm(this);
    return p->frxDDataSet;
}

__fastcall TZFrxReport::~TZFrxReport()
{
   if (p)
       delete p;
}
