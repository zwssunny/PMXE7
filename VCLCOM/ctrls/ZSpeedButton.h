//---------------------------------------------------------------------------

#ifndef ZSpeedButtonH
#define ZSpeedButtonH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class PACKAGE TZSpeedButton : public TSpeedButton
{
private:
protected:
public:
  __fastcall TZSpeedButton(TComponent* Owner);
__published:
  __property Align;
};
//---------------------------------------------------------------------------
#endif
