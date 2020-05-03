// ---------------------------------------------------------------------------

#ifndef WorkflowZClientDBH
#define WorkflowZClientDBH
#include "Wsdb.hpp"	// Pascal unit
#include <Db.hpp>	// Pascal unit
#include <stdio.h>
class TClientBroker;
// ---------------------------------------------------------------------------
class PACKAGE TWorkflowZClientDB : public TCustomWorkflowDB {
private:
	TClientBroker* FClientBroker;
	FILE *logfile;

	void __fastcall WriteLogFile(String msg);
	void __fastcall OpenLogFile(String prefix);

protected:
	virtual void __fastcall DoOpenQuery(TDataSet* Dataset);
	virtual void __fastcall DoOpenSysQuery(TDataSet* Dataset);
	virtual TDataSet* __fastcall DoCreateQuery(String SQL);
	virtual void __fastcall DoExecuteQuery(TDataSet* Dataset);
	virtual void __fastcall DoExecuteSysQuery(TDataSet* Dataset);
	virtual void __fastcall DoAssignSQLParams(TDataSet* Dataset,
		TParams* AParams);
	virtual String __fastcall BlobFieldToString(TField* AField);

public:
	__fastcall TWorkflowZClientDB(TComponent* AOwner,
		TClientBroker* AClientBroker);
	__fastcall virtual ~TWorkflowZClientDB();
};
#endif
