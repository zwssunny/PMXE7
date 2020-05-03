//---------------------------------------------------------------------------

#ifndef StartAndEndDateH
#define StartAndEndDateH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TStartAndEndDateFrame : public TFrame
{
__published:	// IDE-managed Components
	TLabel *lbBegEndScope;
	TComboBox *cbDateRange;
	TLabel *lbBeginDate;
	TLabel *lbEndDate;
	TDateEdit *deStart;
	TDateEdit *deEnd;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	void __fastcall cbDateRangeClosePopup(TObject *Sender);
private:	// User declarations
	int __fastcall GetMonthDays(Word Year,Word Month);
	String __fastcall GetBeginDate();
	void __fastcall SetBeginDate(String Value);
	String __fastcall GetEndDate();
	void __fastcall SetEndDate(String Value);
	TFormatSettings *FormatSettings;
public:		// User declarations
	__fastcall TStartAndEndDateFrame(TComponent* Owner);
	virtual __fastcall ~TStartAndEndDateFrame();
	__property String BeginDate = {read = GetBeginDate, write = SetBeginDate };
	__property String EndDate = {read= GetEndDate, write = SetEndDate };

};
//---------------------------------------------------------------------------
extern PACKAGE TStartAndEndDateFrame *StartAndEndDateFrame;
//---------------------------------------------------------------------------
#endif
