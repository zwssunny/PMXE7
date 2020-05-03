//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CopyRight.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

void  checkCopyRight()
{
 #ifdef _TRIAL_VERSION
   if(Date().FormatString("yyyy-mm-dd")>="2009-10-01")
   {
		throw Exception("试用版已过期,请使用正式版!");
   }
 #endif
}








