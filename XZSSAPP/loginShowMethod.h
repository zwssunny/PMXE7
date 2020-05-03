//---------------------------------------------------------------------------

#ifndef loginShowMethodH
#define loginShowMethodH
#include "Main.h"
#include "Login.h"
//---------------------------------------------------------------------------
class TLoginMethodReference : public TCppInterfacedObject<TProc__1<TModalResult> > {
public:
  TLoginForm *dlg;
  TMainForm *OwerForm;
  void __fastcall Invoke(TModalResult ModalResult)
  {
	if (ModalResult == mrOk)
	{
			try
			{
				OwerForm->ClientBroker->LogonCode = dlg->LogonCode;
				OwerForm->ClientBroker->Password = dlg->Password;
				OwerForm->LogIn();
				if(OwerForm->ClientBroker->Connected)
				{
					OwerForm->ChangeControlState();
				}
			}
			catch(System::Sysutils::Exception &e)
			{
				throw System::Sysutils::Exception(e.Message);
			}
		}
  }
};
class TCloseDialogHandler :public TCppInterfacedObject<TInputCloseDialogProc>
{
public:
	TMainForm *OwerForm;
	void __fastcall Invoke(const System::Uitypes::TModalResult AResult) {
		if (AResult == mrYes)
		{
			OwerForm->LogOff(AResult);
	   		OwerForm->Close();
		}
	}
};
class TLogOffDialogHandler :public TCppInterfacedObject<TInputCloseDialogProc>
{
public:
	TMainForm *OwerForm;
	void __fastcall Invoke(const System::Uitypes::TModalResult AResult) {
		if (AResult == mrYes)
		{
	   		OwerForm->LogOff(AResult);
		}
	}
};
#endif
