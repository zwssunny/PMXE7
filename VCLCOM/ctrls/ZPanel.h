//---------------------------------------------------------------------------

#ifndef ZPanelH
#define ZPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
enum TZPanelStyle{sdpsNone, sdpsTile, sdpsStretch};
class PACKAGE TZPanel : public TPanel
{
private:
  TPicture *FPicture;
  TZPanelStyle FStyle;
  bool FTransparent;

  void __fastcall SetPicture(Graphics::TPicture* Value);
  void __fastcall SetStyle(TZPanelStyle Value);
  void __fastcall SetPicAlign(TAlign AAlign);
  void __fastcall SetTransparent(bool Value);
protected:
  virtual void __fastcall DrawPanel();
  virtual void __fastcall Paint();
  DYNAMIC void __fastcall AdjustSize(void);
  virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation
		);
  void __fastcall SetWndRgn();

public:
  __fastcall TZPanel(TComponent* Owner);
  __fastcall ~TZPanel();
  __property Graphics::TPicture* Picture = {read=FPicture, write=SetPicture};
__published:
  __property TZPanelStyle Style = {read=FStyle, write=SetStyle, default=sdpsNone};
  __property bool Transparent = {read=FTransparent, write=SetTransparent};
};
//---------------------------------------------------------------------------
#endif
