//---------------------------------------------------------------------------

#ifndef EditServerH
#define EditServerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmEditServer : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edServerName;
	TLabel *Label2;
	TEdit *edFileName;
	TLabel *Label3;
	TEdit *edDisplay;
	TSpeedButton *SpeedButton1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TOpenDialog *OpenDialog1;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
	int ModifStatus;//0ä¯ÀÀ£¬1ÐÂÔö£¬2ÐÞ¸Ä
	TListItem *FItem;
	void __fastcall GetDataFromItem(TListItem *AItem);
public:		// User declarations
	__fastcall TfrmEditServer(TComponent* Owner,TListItem *AItem,int Status);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEditServer *frmEditServer;
//---------------------------------------------------------------------------
#endif
