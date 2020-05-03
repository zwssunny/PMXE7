//---------------------------------------------------------------------------

#ifndef ZColorSetH
#define ZColorSetH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TColorSetColorChange)(System::TObject* Sender);
class PACKAGE TZColorSet : public TWinControl
{
private:
        TColorSetColorChange FColorChange;
        MESSAGE void __fastcall WMPaint(Messages::TWMPaint &Message);
protected:
        DYNAMIC void __fastcall Click(void);
        void __fastcall PaintWindow(HDC DC);
public:
		__fastcall TZColorSet(TComponent* Owner);
BEGIN_MESSAGE_MAP
      VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
END_MESSAGE_MAP(TWinControl);
__published:
        __property TColorSetColorChange OnColorChange = {read=FColorChange, write=FColorChange};
        __property Color;
        __property BorderWidth;
        __property Enabled;
        __property Anchors;
        __property Align;
};
//---------------------------------------------------------------------------
#endif
 