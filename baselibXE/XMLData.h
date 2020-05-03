// ---------------------------------------------------------------------------

#ifndef XMLDataH
#define XMLDataH
#include <Classes.hpp>
#include <adodb.hpp>
#include <db.hpp>
#include <DBClient.hpp>
#include <Provider.hpp>
// ---------------------------------------------------------------------------
extern PACKAGE String __fastcall DataSetToXMLData(TCustomADODataSet *ADataSet);
extern PACKAGE TStream* __fastcall AdoDataSetToCDStream(TCustomADODataSet *ADataSet);
extern PACKAGE bool __fastcall XMLDataToDataSet(String xmlData, TADODataSet &ADataSet);
extern PACKAGE void __fastcall SetAllFieldCanModify(TCustomADODataSet *ds);
#endif
