//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "BaseGlobeVars.h"
#include "ClientBroker.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
String gGlobeVarsStr;      //全局变量字符串
TCZDataSet *GlobeVarSet=NULL;  //全局变量对象
//TClientBroker* GClientBroker=NULL;     //全局通讯指针
String ProductVersion="14100"; //产品版本号，默认为房地产版


