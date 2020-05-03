//---------------------------------------------------------------------------

#pragma hdrstop
#include "ShowBizEditForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TForm* __fastcall ShowBizEditForm(TComponent* Owner,int modulecode,String Param,int Flag)
{
	switch(modulecode)
	{
		default:
		return NULL;// throw Exception(L"菜单号:"+IntToStr(modulecode)+L"标志:"+IntToStr(Flag)+L"参数:"+Param);
	}
}
//---------------------------------------------------------------------------
