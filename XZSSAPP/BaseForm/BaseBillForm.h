//---------------------------------------------------------------------------

#ifndef BaseBillFormH
#define BaseBillFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseForm.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TfrmBaseBillForm : public TfrmBaseForm
{
__published:	// IDE-managed Components
private:	// User declarations
	TClientDataSet *FDataSet;
public:		// User declarations
	__fastcall TfrmBaseBillForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
	__fastcall TfrmBaseBillForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,TClientDataSet *m_DataSet,String param);
	__property TClientDataSet *DataSet={ read=FDataSet,write=FDataSet};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBaseBillForm *frmBaseBillForm;
//---------------------------------------------------------------------------
#endif
