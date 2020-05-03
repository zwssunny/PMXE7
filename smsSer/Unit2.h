//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Info.h"
#include "trayicon.h"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TTimer *Timer1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
		 String FDbConStr;
		 String FCordId,FUserName,FPassword;
		 int    FSMSType;
         TTime  FBeginTime ;//开始时间
         TTime  FEndTime; //结束时间
         int    FWaitLong;//消息处理间隔时间 秒为单位
		 int    FRepeatCount;//发送错误时，需要重复次数
		 int    FMonType;
		 int    FPortNum;
         void  __fastcall WritErrorLog(String ErrorLong);
         TShortInfo *ShortInfo;
         void __fastcall LoadSetting();

public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
