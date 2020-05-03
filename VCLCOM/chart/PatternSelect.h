//---------------------------------------------------------------------------

#ifndef PatternSelectH
#define PatternSelectH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TPatternChange)(System::TObject* Sender, int Value);
class PACKAGE TPatternSelect : public TGraphicControl
{
private:
     TPatternChange FOnSelect;
     int FPattern;
     void __fastcall SetPattern(int APattern);
protected:
     virtual void __fastcall Paint(void);
     DYNAMIC void __fastcall Click(void);
public:
     __fastcall TPatternSelect(TComponent* Owner);
__published:
     __property int Pattern = {read=FPattern, write=SetPattern};
     __property TPatternChange OnSelect = {read=FOnSelect, write=FOnSelect};
     __property Color;
     __property Enabled;
     __property Anchors;
     __property Align;
};
//---------------------------------------------------------------------------
#endif
