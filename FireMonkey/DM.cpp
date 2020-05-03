//---------------------------------------------------------------------------


#pragma hdrstop

#include "DM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
TDMmodule *DMmodule;
//---------------------------------------------------------------------------
__fastcall TDMmodule::TDMmodule(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
