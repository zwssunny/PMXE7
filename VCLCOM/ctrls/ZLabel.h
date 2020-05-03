//---------------------------------------------------------------------------

#ifndef ZLabelH
#define ZLabelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
enum TZBindPos {sbpLeft, sbpTop, sbpRight, sbpBottom};
enum TZBindAlign {sbaMin, sbaMiddle, sbaMax};

class PACKAGE TZLabel : public TLabel
{
private:
  TNotifyEvent FOnEnter, FOnExit;
  TFont *FHoverFont;
  TFont *FBkFont;
  TCursor FHoverCursor;
  TCursor FBkCursor;
  bool FSuper;
  TControl* FBindControl;
  TZBindPos FBindPos;
  TZBindAlign FBindAlign;
  int FBindAlternation;
  void __fastcall SetBindControl(TControl* ABindControl);
  void __fastcall SetBindPos(TZBindPos ABindPos);
  void __fastcall SetBindAlign(TZBindAlign ABindAlign);
  void __fastcall SetBindAlternation(int ABindAlternation);
  void __fastcall SetHoverFont(TFont*AFont);
  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
protected:
  void AdjustBind();
public:
  __fastcall TZLabel(TComponent* Owner);
  __fastcall ~TZLabel();
BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
END_MESSAGE_MAP(TLabel);
__published:
    __property TNotifyEvent OnEnter = {read=FOnEnter, write=FOnEnter};
    __property TNotifyEvent OnExit = {read=FOnExit, write=FOnExit};
    __property TFont* HoverFont = {read=FHoverFont, write=SetHoverFont};
    __property TCursor HoverCursor = {read=FHoverCursor, write=FHoverCursor};
    __property bool Super  = {read=FSuper, write=FSuper};
    __property TControl* BindControl = {read=FBindControl, write=SetBindControl};
	__property TZBindPos BindPos = {read=FBindPos, write=SetBindPos};
    __property TZBindAlign BindAlign = {read=FBindAlign, write=SetBindAlign};
    __property int BindAlternation = {read=FBindAlternation, write=SetBindAlternation};
};
//---------------------------------------------------------------------------
#endif
