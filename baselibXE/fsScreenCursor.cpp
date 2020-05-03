//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop

#include "fsScreenCursor.h"
#include <FMX.Forms.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)
void __fastcall TfsScreenCursor::SetCurCursor(TCursor Value)
{
   Application->MainForm->Cursor=Value;  //先暂时修改,后续在实现
}
//---------------------------------------------------------------------------
TCursor __fastcall TfsScreenCursor::GetCurCursor()
{
   return Application->MainForm->Cursor;
}
//---------------------------------------------------------------------------
__fastcall TfsScreenCursor::TfsScreenCursor()
{
   SaveCursor=Application->MainForm->Cursor;   //保存当前光标
   Application->MainForm->Cursor=crHourGlass;  //设置等待光标
}
//---------------------------------------------------------------------------
__fastcall TfsScreenCursor::~TfsScreenCursor()
{
   Application->MainForm->Cursor=SaveCursor; //恢复光标
}
//---------------------------------------------------------------------------
