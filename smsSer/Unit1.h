//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit1;
        TLabel *Label1;
        TEdit *Edit2;
        TLabel *Label2;
        TButton *Button3;
        TTimer *Timer1;
        TStatusBar *StatusBar1;
	TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
   HINSTANCE DllHandle;
   void __fastcall GetDllHandle();
   bool __fastcall LoadDllFunc();
        long FComPort;
        long FModeType;
/*       long (* fnSetThreadMode)(long);
       long (* fnInitModem )(long);//初始化端口
       long (* fnCloseModem)(long);
       long (* fnSetModemType)(long ComNo,long modemType);
       long (* fnGetStatus)(long);//取端口状态
       long (* fnGetSndCount)(long);//取发送缓冲区记录数
       long (* fnGetRecCount)(long);//取接收缓冲区记录数
       long (* fnGetPortMax)();//得到最大端口号
       long (* fnSendMsg)(long , char * , char *); //发送信息
       long (* fnReadMsgEx)(long ,char * ,char *);//接收信息    */
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 