//---------------------------------------------------------------------------
/*--------------------------------------------------------------------------
 声明
 邦永科技公司，版权所有2002 .
 创建于 2002-06-07
 作者：詹文生
  ------------------------------------------------------------------------*/

#ifndef RunExpertH
#define RunExpertH
//---------------------------------------------------------------------------
#include <sysutils.hpp>
#include <toolsapi.hpp>
//---------------------------------------------------------------------------
class PACKAGE TRunExpert : public IOTAMenuWizard
{
private:
	TMenuItem* RunMenuItem;
	TMenuItem* ProjectMenuItem;
	TMenuItem* BuildAllItem;
	TMenuItem* RSItem;
	TTimer* FTimer;
        long m_Count;
        void __fastcall OnClick(TObject* Sender);
        void __fastcall OnTimer(TObject* Sender);
protected:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                           void __RPC_FAR *__RPC_FAR *ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();

public:
        __fastcall TRunExpert();
        virtual __fastcall ~TRunExpert();
        AnsiString __fastcall GetIDString();
        AnsiString __fastcall GetName();
        AnsiString __fastcall GetMenuText();
        TWizardState __fastcall GetState(void);
        virtual void __fastcall Execute(void);
	virtual void __fastcall AfterSave(void){};
	virtual void __fastcall BeforeSave(void){};
	virtual void __fastcall Destroyed(void){};
	virtual void __fastcall Modified(void){};
};
//---------------------------------------------------------------------------
#endif

