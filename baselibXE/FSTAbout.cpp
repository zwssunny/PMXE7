//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop

#include "FSTAbout.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TFSTAbout *)
{
	new TFSTAbout(NULL);
}
//---------------------------------------------------------------------------
__fastcall TFSTAbout::TFSTAbout(TComponent* Owner)
	: TComponent(Owner)
{
}
//---------------------------------------------------------------------------
namespace Fstabout
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TFSTAbout)};
		RegisterComponents(L"Foresight", classes, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFSTAbout::About()
{
   ShowMessage(L"广州先智软件");
}
