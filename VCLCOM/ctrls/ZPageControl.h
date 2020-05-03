//---------------------------------------------------------------------------

#ifndef ZPageControlH
#define ZPageControlH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TZPageControl : public TPageControl
{
private:
  bool FPageControlFlat;
  TColor FPageColor;
  TColor FActivePageColor;
  TFont* FActiveFont;
  void __fastcall SetPageControlFlat(bool Value);
  void __fastcall SetPageColor(TColor Value);
  void __fastcall SetActivePageColor(TColor Value);
  void __fastcall SetActiveFont(TFont* Value);

protected:
public:
  __fastcall TZPageControl(TComponent* Owner);
  __fastcall ~TZPageControl();
__published:

};
//---------------------------------------------------------------------------
#endif
