
#include <vcl.h>        // must define AnsiString before rmb.h
#pragma hdrstop         // only for C++ Builder

#include <math.h>
#include "rmb.h"

//---------------------------------------------------------------------------


// 常量字符串定义，如修改也可变为转换普通汉字函数（如：一二三，十百千）
const char *HanDigiStr[] = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};

const char *HanDiviStr[] = { "","拾","佰","仟","万","拾","佰","仟","亿",
				"拾","佰","仟","万","拾","佰","仟","亿",
				"拾","佰","仟","万","拾","佰","仟" };

String PositiveIntegerToHanStr(const String &NumStr)
{					// 输入字符串必须正整数，只允许前导空格(必须右对齐)，不宜有前导零
	String RMBStr;
	int len,n,lastzero=0;
	int hasvalue=0;			// 亿、万进位前有数值标记

	len = NumStr.Length();
	if( len > 24 ) return "数值过大!";

	for(int i=len-1;i>=0;i--) {
		if( NumStr[len-i]==' ' ) continue;      // String[] base is 1
		n = NumStr[len-i] - '0';
		if( n<0 || n>9 ) return "输入含非数字字符!";

		if( n!=0 ) {
			if( lastzero ) RMBStr += HanDigiStr[0];		// 若干零后若跟非零值，只显示一个零
                                                                        // 除了亿万前的零不带到后面
//			if( !( n==1 && (i%4)==1 && (lastzero || i==len-1) ) )   // 如十进位前有零也不发壹音用此行
//			if( !( n==1 && (i%4)==1 && i==len-1 ) )         // 十进位处于第一位不发壹音
				RMBStr += HanDigiStr[n];
			RMBStr += HanDiviStr[i];			// 非零值后加进位，个位为空
			hasvalue = 1;                                   // 置万进位前有值标记
		 }
		else {
			if( (i%8)==0 || ((i%8)==4 && hasvalue) ) 	// 亿万之间必须有非零值方显示万
				RMBStr += HanDiviStr[i];		// “亿”或“万”
		 }
                if( i%8==0 ) hasvalue = 0;  			// 万进位前有值标记逢亿复位
		lastzero = (n==0) && (i%4!=0);                  // 亿万前有零后不加零，如：拾万贰仟
	 }

	if( RMBStr.Length()==0 ) return HanDigiStr[0];	        // 输入空字符或"0"，返回"零"
	return RMBStr;
}

String NumToRMBStr(double val)
{
	String SignStr,TailStr;
	double fraction, integer;
	int jiao,fen;

	if( val<0 ) {
		val = -val;
		SignStr = "负";
	 }
	fraction = modf(val+0.005, &integer);           // 四舍五入到分

	jiao = int(fraction*10);
	fen = int(fraction*100)-jiao*10;
	if( jiao==0 && fen==0 ) {
		TailStr = "整";
	 }
	else {
		TailStr = HanDigiStr[jiao];
		if( jiao!=0 )
			TailStr += "角";
                if( integer==0 && jiao==0 )             // 零元后不写零几分
                        TailStr = "";
		if( fen!=0 )
			TailStr += HanDigiStr[fen] + String("分");
	 }

// 下一行可用于非正规金融场合，0.03只显示“叁分”而不是“零元叁分”
//        if( integer==0 ) return  SignStr+TailStr;

	return SignStr+PositiveIntegerToHanStr( String(integer) )+"元"+TailStr;
}

//-----------------------------------------------------------

// 基本考虑
// 人民币大写单位银行规定用“元”
// 无零头金额后跟“整”，有则不跟
// 角为零时不写角（如：零叁分）
// 四舍五入到分
// 为减少判读疑惑（一般对大写金额预期较高）和
// 体现人民币基本单位为元，金额低于壹圆前仍加“零元”

// 整数转换
// 若干零后若跟非零值，只显示一个零，否则不显示
// 万(亿)前有零后不加零，因亿、万为一完整单位，
// （如：拾万贰仟 比 拾万零贰仟 更顺些）
// 亿为汉语计数最大单位，只要进位到总是显示（如：壹亿亿）
// 万为次最大单位，亿万之间必须有非零值方显示万
// （如“壹亿”不可显示为“壹亿万”）
//
// 为减少被窜改的可能性，十进位总发壹音，这和下面的习惯读法不一样
//      （十进位处于第一位不发壹音，如“拾元”非“壹拾元”，
//        十进位处前有零是否不发壹音不太确定，
//        如“叁仟零壹拾元”还是“叁仟零拾元”？）
// 用“拾万”不用“壹拾万”，因为每个整数进位后都有进位单位（拾佰仟万亿）
// 这样即使金额前没有附防窜改的前缀如“人民币”字样也难窜改些
// 因为至少要加添两个汉字并且改动后数字必须进位才能窜改成
// （如“拾万”可改成“叁拾万”，而“壹拾万”至少要改成“壹佰壹拾万”）


// 此函数为Borland C++ Builder编写，已充分考虑到跨平台兼容性
// 如需转换到其它场合，
// 只需修改字符串类型从AnsiString到对应的类型、功能及函数
// （注意两个char*型字符串不可以直接相加，需有一个先转换）

// public domain freeware by 王大庆 2003年3月-5月 v1.1
// 此函数如有不妥之处请email: wang_daqing@21cn.com
