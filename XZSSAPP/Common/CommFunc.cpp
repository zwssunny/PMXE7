//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

String __fastcall GetGUIDString()
{
    TGUID BillID;
	CreateGUID(BillID);
	return GUIDToString(BillID);
}
//自定义的浮点转化为字符串函数，避免科学计数法
//---------------------------------------------------------------------------
String __fastcall myFloatToStr(double data)
{
  int iPoint,iExponent;
  String datastring,tmpstr,tmpstr2;
  datastring = FloatToStr(data); //调用标准转换
  if ((iPoint = datastring.Pos0("E")) <= 0) //如果不是科学计数法，直接返回字符串
    return datastring;
  tmpstr = datastring.SubString1(iPoint+1,datastring.Length()-iPoint);
  if (tmpstr == "")
    iExponent = 0;
  else
    iExponent = StrToInt(tmpstr); //获取指数位
  tmpstr = datastring.SubString1(1,iPoint-1); //获取余数

  if (iExponent > 0)  //指数是正数
  {
    if ((iPoint = tmpstr.Pos0(".")) <= 0) //余数无小数
    {
      for (int i=0;i<iExponent;i++)
       tmpstr += "0";
    }
    else                                 //余数有小数
    {
      tmpstr2 = tmpstr;
      tmpstr = tmpstr2.SubString1(1,iPoint-1); //截取整数部分
      tmpstr2 = tmpstr2.SubString1(iPoint+1,tmpstr2.Length()-iPoint); //截取小数部分
      if (tmpstr2.Length() > iExponent)
      {
        tmpstr += tmpstr2.SubString1(1,iExponent);
        tmpstr += ".";                        //移位并插入小数点
        tmpstr += tmpstr2.SubString1(iExponent+1,tmpstr2.Length());
      }
      else
      {
        tmpstr += tmpstr2;
        for (int i=0;i<iExponent-tmpstr2.Length();i++)
         tmpstr += "0";
      }
    }
  }
  if (iExponent < 0)  //指数是负数
  {
    String sFlag="";
    iExponent = iExponent*-1; //取相反数
	if (tmpstr.SubString1(1,1) == "+" || tmpstr.SubString1(1,1) == "-") //获取位首正负符号
    {
      sFlag = tmpstr.SubString1(1,1);
      tmpstr = tmpstr.SubString1(2,tmpstr.Length()-1);
    }
    tmpstr2 = tmpstr;
    tmpstr = "";
    if ((iPoint = tmpstr2.Pos0(".")) > 0) //余数有小数
    {
      tmpstr = tmpstr2.SubString1(iPoint+1,tmpstr2.Length()-iPoint); //截取小数部分
      tmpstr2 = tmpstr2.SubString1(1,iPoint-1); //截取整数部分
    }
    if (tmpstr2.Length() > iExponent)
    {
      tmpstr = tmpstr2.SubString1(iExponent+1,tmpstr2.Length()) + tmpstr;
      tmpstr = "." + tmpstr;                        //移位并插入小数点
      tmpstr = tmpstr2.SubString1(1,iExponent) + tmpstr;
    }
    else
    {
      tmpstr = tmpstr2 + tmpstr;
      for (int i=0;i<iExponent-tmpstr2.Length();i++)
       tmpstr = "0" + tmpstr;
      tmpstr = "0." + tmpstr;
    }
    tmpstr = sFlag + tmpstr; //加上符号
  }
  return tmpstr;
}
//---------------------------------------------------------------------------
//格式化浮点数据以字符串输出
//参数data-浮点数；iType-数据类型，ftQty:数量，ftPrice:单价，ftAmt:金额,ftRate:汇率系数；
//iStyle-小数截取方式，0:四舍五入，1:截断；iPrecision-小数精度，-1:取系统精度
//---------------------------------------------------------------------------
double __fastcall ConvertFloat(double data,TfstFloatType iType,int iPrecision,int iStyle)
{
   //if(data >= 1E12)
   //   throw Exception("浮点数值位数超长");
   String datastring=myFloatToStr(data);
   int iPoint=datastring.Pos0("."); //小数点位置
   if(iPoint <= 0)
     return data;  //无小数直接返回

   int iPrec,iFormatStyle;
   //确定精度
//   if (iPrecision < 0) //取系统精度
//   {
//     switch(iType)
//     {
//       case ftQty:      //Qty Float
//         if(GetGlobeVarValue("QtyPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("QtyPrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftPrice:      //Price Float
//         if(GetGlobeVarValue("PricePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("PricePrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftAmt:      //Amt Float
//         if(GetGlobeVarValue("AmtPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("AmtPrecision"));
//         else
//           iPrec = 4;
//         break;
//       case ftRate:      //rate Float
//         if(GetGlobeVarValue("RatePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("RatePrecision"));
//         else
//           iPrec = 4;
//         break;
//       case ftsArea:      //Area Float
//         if(GetGlobeVarValue("sAreaPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sAreaPrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftsPrice:      //Area Float
//         if(GetGlobeVarValue("sPricePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sPricePrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftsAmt:      //Area Float
//         if(GetGlobeVarValue("sAmtPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sAmtPrecision"));
//         else
//           iPrec = 4;
//         break;
//       case ftsCJPrice:      //Area Float
//         if(GetGlobeVarValue("sCJPricePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sCJPricePrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftsCJTotalPrice:      //Area Float
//         if(GetGlobeVarValue("sCJTotalPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sCJTotalPrecision"));
//         else
//           iPrec = 4;
//         break;
//       default:
//         throw Exception("浮点数据类型错误");
//     }
//   }
//   else
//   {
//     iPrec = iPrecision; //user definite
//   }
   iPrec = iPrecision;
   if(iPoint+iPrec >= datastring.Length()) //不需要截取精度
     return data;

   if(iStyle <= 1)
     iFormatStyle = iStyle;
   else
     throw Exception("浮点格式类型错误");

   double tmp=data,tmp2=0.5;
   tmp = tmp*pow(10,iPrec);
   if (iFormatStyle == 0)  //四舍五入方式
   {
     if(tmp >= 0)
       tmp += tmp2;
     else
       tmp -= tmp2;
   }
   datastring=myFloatToStr(tmp);
   if(datastring.Pos0(".") > 0)
	 datastring=datastring.SubString1(1,datastring.Pos0("."));  //截断精度之外的位数
   if(datastring != "")
     tmp=GetFloatFromStr(datastring);
   else
     tmp=0;
   tmp = tmp/pow(10,iPrec);
   return tmp;
}
//---------------------------------------------------------------------------
//格式化浮点数据以字符串输出  panner 2002/11/12
//参数data-浮点数；iType-数据类型，ftQty:数量，ftPrice:单价，ftAmt:金额,ftRate:汇率系数；
//iStyle-小数截取方式，1:四舍五入，2:截断；iPrecision-小数精度，-1:取系统精度
//---------------------------------------------------------------------------
String __fastcall FormatFloatToStr(double data,TfstFloatType iType,int iPrecision,int iStyle)
{
   if(data == 0) return "0";
   int iPrec;
   //确定精度
//   if (iPrecision < 0) //取系统精度
//   {
//     switch(iType)
//     {
//       case ftQty:      //Qty Float
//         if(GetGlobeVarValue("QtyPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("QtyPrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftPrice:      //Price Float
//         if(GetGlobeVarValue("PricePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("PricePrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftAmt:      //Amt Float
//         if(GetGlobeVarValue("AmtPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("AmtPrecision"));
//         else
//           iPrec = 4;
//         break;
//       case ftRate:      //rate Float
//         if(GetGlobeVarValue("RatePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("RatePrecision"));
//         else
//           iPrec = 4;
//         break;
//       case ftsArea:      //Area Float
//         if(GetGlobeVarValue("sAreaPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sAreaPrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftsPrice:      //Area Float
//         if(GetGlobeVarValue("sPricePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sPricePrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftsAmt:      //Area Float
//         if(GetGlobeVarValue("sAmtPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sAmtPrecision"));
//         else
//           iPrec = 4;
//         break;
//       case ftsCJPrice:      //Area Float
//         if(GetGlobeVarValue("sCJPricePrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sCJPricePrecision"));
//         else
//           iPrec = 2;
//         break;
//       case ftsCJTotalPrice:      //Area Float
//         if(GetGlobeVarValue("sCJTotalPrecision") != "")
//           iPrec = StrToInt(GetGlobeVarValue("sCJTotalPrecision"));
//         else
//           iPrec = 4;
//         break;
//       default:
//         throw Exception("浮点数据类型错误");
//     }
//   }
//   else
//   {
//     iPrec = iPrecision; //user definite
//   }
	iPrec = iPrecision;
   //输出格式字串
   bool ShowSeparator; //每三位显示分隔符
   switch(iType)
   {
     case 1:      //Qty Float
     case 2:      //Price Float
     case 3:      //Amt Float
     case 4:      //rate Float
     case 5:      //ftsArea Float
     case 6:      //ftsPrice Float
     case 7:      //ftsAmt Float
     case 8:      //ftsCJPrice Float
     case 9:      //ftsCJTotalPrice Float
       ShowSeparator = true;
       break;
     default:
       throw Exception("浮点数据类型错误");
   }

  String stmp,stmp1,stmp2;
  stmp = myFloatToStr(ConvertFloat(data,iType,iPrecision,iStyle));
  if(stmp.Pos0(".") > 0)
  {
    stmp1 = stmp.SubString1(1,stmp.Pos0(".")); //截取整数部分
    stmp2 = stmp.SubString1(stmp.Pos0(".")+2,stmp.Length()-stmp.Pos0(".")); //截取小数部分
  }
  else
  {
    stmp1 = stmp;
    stmp2 = "";
  }
  //小数部分处理
  if(stmp2.Length() > iPrec)
    stmp2 = stmp2.SubString1(1,iPrec);
  else
  {
    int tmp = iPrec-stmp2.Length();
    for(int i=0;i<tmp;i++)
      stmp2 = stmp2 + "0";
  }
  //整数部分处理
  if(ShowSeparator && stmp1.Length()>3)  //添加分隔符
  {
    String stmp3="";
    int charcount=0;
	Char *pstr = stmp1.c_str();
    for(int i=stmp1.Length()-1;i>=0;i--)
    {
      if(pstr[i] >= '0' && pstr[i] <= '9')
      {
        charcount++;
		if(charcount > 3)
        {
          stmp3 = String(",")+stmp3;
          charcount = 1;
        }
      }
      stmp3 = String(pstr[i])+stmp3;
    }
    stmp1 = stmp3;
  }
  if(iPrec > 0)
    return stmp1+"."+stmp2;
  else
    return stmp1;
}
//从字串中提取浮点数
//参数：str-字串，返回值浮点双精度数
//---------------------------------------------------------------------------
double __fastcall GetFloatFromStr(String str)
{
  Char * ch=str.c_str();
  Char ch2[100];
  int j=0;
  bool bFirstPoint=true;
  double d;

  str = Trim(str);
  if(str.IsEmpty() || str == "-" || str == ".")  //空串返回0 "-"返回0 "."返回0
    return 0;
  for (int i=0;i<str.Length();i++)
  {
    if (((ch[i] == '+' || ch[i] == '-') && i == 0) ||
        (ch[i] >= '0' && ch[i] <= '9') ||
        (ch[i] == '.' && bFirstPoint)  ||
         ch[i] == '\0')
    {
      if (ch[i] == '.')
        bFirstPoint = false;
      ch2[j]=ch[i];
      j++;
    }
  }
  if(ch2[j] != '\0')
    ch2[j] = '\0';
  try
  {
    d = StrToFloat(String(ch2));
  }
  catch(...)
  {
    throw Exception("非有效浮点数据");
  }
  return d;
}
//---------------------------------------------------------------------------
String __fastcall EncodeJsonDate(String date)
{
	if(date.LowerCase().Pos0("date(") >= 0)
	{
		String dateint = date.SubString1(7,date.Length()-8);
		unsigned __int64 bb = StrToInt64(dateint);
		double days = bb / MSecsPerDay;
		TDateTime indate = EncodeDate(1970,1,1) + days;
		return indate.FormatString("YYYY-MM-DD");
	}
	else
		return date;
}
//---------------------------------------------------------------------------


