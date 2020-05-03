//---------------------------------------------------------------------------

#ifndef ShowBizFormH
#define ShowBizFormH
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
//---------------------------------------------------------------------------
TForm* __fastcall ShowBizForm(TComponent* Owner,int modulecode,String param);
void __fastcall InitAllMainChildForms();
void __fastcall DeleteAllMainChildForms();
#endif
