//---------------------------------------------------------------------------

#ifndef JBCommentBindingH
#define JBCommentBindingH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <ToolsAPI.hpp>
#include <Menus.hpp>
#include <Windows.hpp>
//---------------------------------------------------------------------------
class PACKAGE TJBCommentBinding : public IOTAKeyboardBinding
{
private:
         void __fastcall TJBCommentBinding::myCommentUncomment(IOTAEditPosition* iEditPos,int Row,int &startCol,
                int &startRow,int &endCol,int &endRow);
         long m_Count;
protected:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,
                                           void __RPC_FAR *__RPC_FAR *ppvObject);
        virtual ULONG STDMETHODCALLTYPE AddRef();
        virtual ULONG STDMETHODCALLTYPE Release();
public:
        TBindingType __fastcall GetBindingType();
		 String __fastcall GetDisplayName();
		 String __fastcall GetName();
        void __fastcall BindKeyboard( const _di_IOTAKeyBindingServices BindingServices);
        void __fastcall JBComment( const _di_IOTAKeyContext Context, TShortCut KeyCode,TKeyBindingResult &BindingResult);
        void __fastcall DefaultKeyProc( const _di_IOTAKeyContext Context, TShortCut KeyCode, TKeyBindingResult &BindingResult);
        __fastcall TJBCommentBinding();
	virtual void __fastcall AfterSave(void){};
	virtual void __fastcall BeforeSave(void){};
	virtual void __fastcall Destroyed(void){};
	virtual void __fastcall Modified(void){};

};
//---------------------------------------------------------------------------
#endif
 