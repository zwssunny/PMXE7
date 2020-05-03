//---------------------------------------------------------------------------

#include <vcl.h>
#include "gvar.h"
#include "ClientDcom.h"
#include "ClientComm.h"
#pragma hdrstop

#include "GenSql.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
AnsiString GenSql(AnsiString Templet, AnsiString AWhere)
{
    AnsiString Select, From, Where, OrderBy, GroupBy;
    AnsiString s_SQL;
    TComResultSet *RsQuery;
    TStrings * GroupByField = new TStringList();
try{
    try{
       RsQuery=NewResultSet();
//-Group By----------------------------------------------------------
       s_SQL = "select RptGroupField, RptGroupNo from sdRptGroup ";
       s_SQL += "where RptGroupTemplet = '" +Templet +"'";
       s_SQL += "ORDER BY RptGroupNo ";
       RsQuery->Open(s_SQL,"");
       if(RsQuery->RecordCount>0)
       {
          GroupBy = " Group By ";
          RsQuery->MoveFirst();
          bool eof = false;
          AnsiString F;
          while(!eof)
          {
             F = RsQuery->FieldByName("RptGroupField");
             GroupBy += F;
             GroupByField->Add(F + "=" + "1");
             RsQuery->MoveNext();
             if(RsQuery->Eof)
                eof = true;
             else
                GroupBy += ",";
          }
       }
       RsQuery->Close();
       GroupBy += " ";
//-Select From-------------------------------------------
       s_SQL = "select RptTempletHView, RptTempletDFlg, RptTempletDField, RptTempletDExpr, RptTempletDNo, ";
       s_SQL += " RptTempletDType, RptTempletDWidth, RptTempletDScale ";
       s_SQL += "from sdRptTempletH ";
       s_SQL += "left outer join sdRptTempletD ";
       s_SQL += "on RptTempletHCode = RptTempletDCode ";
       s_SQL += "where RptTempletHCode = '" + Templet + "'";
       s_SQL += " order by RptTempletDNo";
       RsQuery->Open(s_SQL,"");
       if(RsQuery->RecordCount>0)
       {
          Select = "Select ";
          RsQuery->MoveFirst();
          From = " From " + RsQuery->FieldByName("RptTempletHView")+ " "; //From
          bool eof = false;
          RsQuery->MoveFirst();
          AnsiString F;
          while(!eof)
          {
             F = RsQuery->FieldByName("RptTempletDField");
             AnsiString aaa = RsQuery->FieldByName("RptTempletDType");
             if(StrToInt(RsQuery->FieldByName("RptTempletDFlg")))
             {
                 if(RsQuery->FieldByName("RptTempletDType").Trim().UpperCase() == "F")
                 {
                     AnsiString str = F + " = LTRIM(STR(" + RsQuery->FieldByName("RptTempletDExpr") + "), " +
                                      RsQuery->FieldByName("RptTempletDWidth") + ", " +
                                      RsQuery->FieldByName("RptTempletDScale") + ")) ";
                     Select += str;
                 }else
                     Select += F + "=" + RsQuery->FieldByName("RptTempletDExpr");
             }else
             {
                 if(GroupByField->Count > 0)
                 {
                     if(GroupByField->Values[F] == "")
                     {
                         if(RsQuery->FieldByName("RptTempletDType").Trim().UpperCase() == "F")
                         {
                            AnsiString str = F + " = LTRIM(STR(min(" + F + "), " +
                                     RsQuery->FieldByName("RptTempletDWidth") + ", " +
                                     RsQuery->FieldByName("RptTempletDScale") + ")) ";
                            Select += str;
                         }else
                            Select += F + " = min(" + F + ")";
                     }else
                     {
                         if(RsQuery->FieldByName("RptTempletDType").Trim().UpperCase() == "F")
                         {
                            AnsiString str = F + " = LTRIM(STR(" + F + ", " +
                                     RsQuery->FieldByName("RptTempletDWidth") + ", " +
                                     RsQuery->FieldByName("RptTempletDScale") + ")) ";
                            Select += str;
                         }else
                            Select += F;
                     }
                 }else
                 {
                     if(RsQuery->FieldByName("RptTempletDType").Trim().UpperCase() == "F")
                     {
                        AnsiString str = F + " = LTRIM(STR(" + F + ", " +
                                     RsQuery->FieldByName("RptTempletDWidth") + ", " +
                                     RsQuery->FieldByName("RptTempletDScale") + ")) ";
                        Select += str;
                     }else
                        Select += F;
                 }
             }
             RsQuery->MoveNext();
             if(RsQuery->Eof)
                eof = true;
             else
                Select += ", ";
          }
       }else
          throw Exception("查询字段不能为空！！！");
       RsQuery->Close();
       Select += " ";
//-Where----------------------------------------------------------
       if(!AWhere.IsEmpty())
          Where = " Where " + AWhere + " ";
//-OrderBy----------------------------------------------------------
       s_SQL = "select RptSortField, RptSortDesc, RptSortNo from sdRptSort ";
       s_SQL += "where RptSortTemplet = '" +Templet +"'";
       s_SQL += "ORDER BY RptSortNo ";
       RsQuery->Open(s_SQL,"");
       if(RsQuery->RecordCount>0)
       {
          OrderBy = " Order By ";
          RsQuery->MoveFirst();
          bool eof = false;
          while(!eof)
          {
             OrderBy += RsQuery->FieldByName("RptSortField");
             if(StrToInt(RsQuery->FieldByName("RptSortDesc")))
                OrderBy += " DESC";
             RsQuery->MoveNext();
             if(RsQuery->Eof)
             {
                eof = true;
             }
             else
                OrderBy += ", ";
          }
       }
       RsQuery->Close();
       OrderBy += " ";
//-----------------------------------------------------------------
    }__finally
    {
       delete RsQuery;
       delete GroupByField;
    }
}catch(...)
{
    throw Exception("生成SQL时语句产生错误！请检查报表模板并测试通过！");
}
    return Select + From + Where + GroupBy + OrderBy;
}
