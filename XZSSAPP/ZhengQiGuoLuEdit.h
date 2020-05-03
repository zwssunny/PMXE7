//---------------------------------------------------------------------------

#ifndef ZhengQiGuoLuEditH
#define ZhengQiGuoLuEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include "ClientBroker.h"
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TfrmZhengQiGuoLuEdit : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TToolBar *ToolBar2;
	TButton *btClose;
	TPanel *Panel1;
	TClientDataSet *ClientDataSet1;
	TGridPanelLayout *GridPanelLayout1;
	TPanel *Panel2;
	TLabel *Label2;
	TEdit *edUseDepName;
	TPanel *Panel3;
	TLabel *Label3;
	TEdit *edDocSN;
	TPanel *Panel4;
	TLabel *Label4;
	TEdit *edUseProjectName;
	TPanel *Panel5;
	TLabel *Label5;
	TEdit *edUseAddress;
	TPanel *Panel6;
	TLabel *Label6;
	TPanel *Panel7;
	TLabel *Label7;
	TEdit *edBoilerGuoLuShuiWei;
	TPanel *Panel8;
	TLabel *Label8;
	TEdit *edBoilerRanShaoJi;
	TPanel *Panel9;
	TLabel *Label9;
	TEdit *edBoilerKongZhiXiangJiAnNiu;
	TPanel *Panel10;
	TLabel *Label10;
	TEdit *edBoilerShuiWeiKongZhiXiTong;
	TPanel *Panel11;
	TLabel *Label11;
	TEdit *edBoilerYaLiKongZhiXiTong;
	TPanel *Panel12;
	TLabel *Label12;
	TEdit *edBoilerAnQuanFa;
	TPanel *Panel13;
	TLabel *Label13;
	TEdit *edBoilerPaiYanXiTong;
	TVertScrollBox *VertScrollBox1;
	TPanel *Panel14;
	TLabel *Label14;
	TEdit *edBoilerZhuZhengQiFa;
	TPanel *Panel15;
	TLabel *Label15;
	TEdit *edBoilerPaiWuFa;
	TPanel *Panel16;
	TLabel *Label16;
	TEdit *edBoilerBaoJingZhuangZhi;
	TPanel *Panel17;
	TLabel *Label17;
	TPanel *Panel18;
	TLabel *Label18;
	TEdit *edAEgongShuiXiTong;
	TPanel *Panel19;
	TLabel *Label19;
	TEdit *edAEgongYouXiTong;
	TPanel *Panel20;
	TLabel *Label20;
	TEdit *edAEgongQiXiTong;
	TPanel *Panel21;
	TLabel *Label21;
	TEdit *edAEfenQiXiang;
	TPanel *Panel22;
	TLabel *Label22;
	TEdit *edAEruanShuiChuLiQi;
	TPanel *Panel23;
	TLabel *Label23;
	TEdit *edAEriYongShuiXiangShuiWei;
	TPanel *Panel24;
	TLabel *Label24;
	TEdit *edAEriYongYouXiangYouWei;
	TPanel *Panel25;
	TLabel *Label25;
	TMemo *mmQITaQingKuang;
	TPanel *Panel26;
	TLabel *Label26;
	TEdit *edAddMan;
	TPanel *Panel27;
	TLabel *Label27;
	TEdit *edAddDate;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btCloseClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
	TClientBroker *FClientBroker;
	String UseProject,GUID,UseDep,WfsID,FlowID,RelID,MainID,SubID;
public:		// User declarations
    void __fastcall NotPass(String reason);
	__fastcall TfrmZhengQiGuoLuEdit(TComponent* Owner,TClientBroker *ClientBroker,String Flowid,String Mainid,String Relid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmZhengQiGuoLuEdit *frmZhengQiGuoLuEdit;
//---------------------------------------------------------------------------
#endif
