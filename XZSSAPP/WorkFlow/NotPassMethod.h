//---------------------------------------------------------------------------

#ifndef NotPassMethodH
#define NotPassMethodH
#include "NotPassTextForm.h"
#include "WorkFlowDetailForm.h"
//---------------------------------------------------------------------------
class TNotPassMethodReference : public TCppInterfacedObject<TProc__1<TModalResult> > {
public:
  TfrmNotPassTextForm *dlg;
  TfrmWorkFlowDetailForm *OwerForm;
  void __fastcall Invoke(TModalResult ModalResult)
  {
	if (ModalResult == mrOk)
	{
		try
		{
			OwerForm->NotPass(dlg->Reason);
		}
		catch(System::Sysutils::Exception &e)
		{
			throw System::Sysutils::Exception(e.Message);
		}
	}
  }
};
#endif
