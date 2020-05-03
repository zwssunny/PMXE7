//---------------------------------------------------------------------------

#pragma hdrstop

#include "Version.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
const String SYSADMIN="FSAdmin";
const String SYSPASSWORD="fst123!@#";
const DWORD LOCAL_VERSION = 111;
const char LOCAL_VERSION_STRING[] = "@#ZWSVERSION$%";
DWORD GetLocalVersion() {
	DWORD retver;
	char encstr[4], decstr[4];
	memcpy(encstr, LOCAL_VERSION_STRING + 2, 3);
	encstr[3] = '\0';
	retver = atoi(encstr);
	if (retver == 0)
		return LOCAL_VERSION;
	else
		return retver;
}
String GetSysAdmin()
{
	return SYSADMIN;
}
String GetSysPassWord()
{
    return SYSPASSWORD;
}
