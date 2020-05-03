//---------------------------------------------------------------------------

#ifndef CnCalendarH
#define CnCalendarH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
#include <comctrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TCnCalendar : public TCustomControl
{
private:
        TSpeedButton* FLeftButton;
        TSpeedButton* FRightButton;
        TPopupMenu *PopupMonth;
        void __fastcall PMonth(System::TObject* Sender);
        void __fastcall NMonth(System::TObject* Sender);

        TDateTime FDateTime;
        TDateTime FFirstDate;
        TDateTime FDisplayDate;
        void __fastcall SetDisplayDate(TDate ADate);
        void __fastcall SetCurrDate(TDate ADate);
        void __fastcall DrawADate(TDate Date, BYTE CurrMonth, TRect ARect);
        void __fastcall DrawAWeek(int Week, TRect ARect);
        void __fastcall DrawTop();
        void __fastcall DrawBottom(int BHeight);
        void __fastcall PopupMenuItemsClick(TObject *Sender) ;

        TColor FTopColor;
        int FTopHeight;
        TFont *FTopFont;
        void __fastcall SetTopFont(TFont* AFont);
        void __fastcall SetTopColor(TColor AColor);
        POINT __fastcall MousePos();
        void __fastcall DayClick(int Row, int Col);
        void __fastcall TopClick();
        void __fastcall BottomClick();
        TMaskEdit *FYearEdit;
        TUpDown*   FYearUpDown;
        void __fastcall YearUpDownChanging(TObject
                         * Sender, bool &AllowChange, int NewValue, TUpDownDirection Direction);

        TColor FCnColor;
        void __fastcall SetCnColor(TColor AColor);
        TNotifyEvent FOnChange;

        TColor FOtherMonthDayColor;
        void __fastcall SetOtherMonthDayColor(TColor AColor);
        TColor FOddColor;
        void __fastcall SetOddColor(TColor AColor);
        TColor FEvenColor;
        void __fastcall SetEvenColor(TColor AColor);
        TColor FWeekColor;
        void __fastcall SetWeekColor(TColor AColor);
private:
        void __fastcall WMEraseBkGnd(TMessage &Message){Message.Result = 1;}
protected:
        DYNAMIC void __fastcall Click(void);
        virtual void __fastcall Paint(void);
        virtual void __fastcall AdjustClientRect(TRect &Rect);
public:
        __fastcall TCnCalendar(TComponent* Owner);
        __fastcall ~TCnCalendar();
        void __fastcall AdjustRect();
        __property TDate Date = {read=FDateTime, write=SetCurrDate};
BEGIN_MESSAGE_MAP
     VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TMessage, WMEraseBkGnd);
END_MESSAGE_MAP(TCustomControl);
__published:
        __property TColor TopColor = {read=FTopColor, write=SetTopColor};
        __property TFont* TopFont = {read=FTopFont, write=SetTopFont};
        __property TColor CnColor = {read=FCnColor, write=SetCnColor};
        __property TColor OtherMonthDayColor = {read=FOtherMonthDayColor, write=SetOtherMonthDayColor};
        __property TColor OddColor = {read=FOddColor, write=SetOddColor};
        __property TColor EvenColor = {read=FEvenColor, write=SetEvenColor};
        __property TColor WeekColor = {read=FWeekColor, write=SetWeekColor};
        __property TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
        __property Align;
        __property Color;
        __property Font;
        __property Ctl3D;
        __property ParentCtl3D;
        __property OnEnter;
        __property OnExit;
        __property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property TabOrder;
	__property TabStop;
        __property BorderWidth;
};
//---------------------------------------------------------------------------
#endif
