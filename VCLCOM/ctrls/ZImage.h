//---------------------------------------------------------------------------

#ifndef ZImageH
#define ZImageH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TZImage : public TImage
{
private:
    TNotifyEvent FOnEnter, FOnExit;
    void __fastcall CMMouseEnter(TMessage &Message);
    void __fastcall CMMouseLeave(TMessage &Message);
protected:
public:
    __fastcall TZImage(TComponent* Owner);
BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
END_MESSAGE_MAP(TImage);
__published:
    __property TNotifyEvent OnEnter = {read=FOnEnter, write=FOnEnter};
    __property TNotifyEvent OnExit = {read=FOnExit, write=FOnExit};
};
//---------------------------------------------------------------------------
#endif
