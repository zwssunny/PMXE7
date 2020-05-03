//---------------------------------------------------------------------------

#ifndef WorkFlowBrowseFormH
#define WorkFlowBrowseFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "BaseForm.h"
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <System.Rtti.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.MultiView.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class TfrmWorkFlowBrowseForm : public TfrmBaseForm
{
__published:	// IDE-managed Components
	TButton *BtnSearch;
	TMultiView *QueryView;
	TComboBox *cbStatusFilter;
	TLabel *Label1;
	TButton *btnQuery;
	TPanel *ContentPanel;
	TStringGrid *BrowseGrid;
	TClientDataSet *Query;
	TButton *BtnShowInfo;
	TClientDataSet *BusinessDataSet;
	void __fastcall BtnShowInfoClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
private:	// User declarations
	String FGridName,FGridDataUrl,FCommitUrl,FNotPassUrl,FLoadUrl;
	int FFlowID,FFilterState;
	void __fastcall ShowEditForm();
	void __fastcall DetailClose(TObject *Sender, TCloseAction &Action);
protected:
	virtual String __fastcall GetIDColumnName();
	virtual String __fastcall GetConfigUrl();
	virtual void __fastcall LoadConfig();
	virtual void __fastcall LoadGridConfig();
	virtual void __fastcall LoadGridData(TJSONArray *FilterParam);
	virtual TForm * __fastcall NewEditForm();
	virtual void __fastcall InitFilter();
	virtual void __fastcall filteData();
public:		// User declarations
	__fastcall TfrmWorkFlowBrowseForm(TComponent* Owner,TClientBroker *clBroker,int modulecode,String param);
	__fastcall ~TfrmWorkFlowBrowseForm();
	__property String CommitUrl={ read=FCommitUrl,write=FCommitUrl};
	__property String NotPassUrl={ read=FNotPassUrl,write=FNotPassUrl};
	__property String LoadUrl={ read=FLoadUrl,write=FLoadUrl};
	__property int FlowID={ read=FFlowID,write=FFlowID};
	__property int FilterState={ read=FFilterState,write=FFilterState};
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorkFlowBrowseForm *frmWorkFlowBrowseForm;
//---------------------------------------------------------------------------
#endif
