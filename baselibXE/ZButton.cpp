//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop

#include "ZButton.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TZButton *)
{
	new TZButton(NULL);
}
//---------------------------------------------------------------------------
__fastcall TZButton::TZButton(TComponent* Owner)
	: TButton(Owner)
{
}
//---------------------------------------------------------------------------
namespace Zbutton
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TZButton)};
		RegisterComponents(L"zws", classes, 0);
	}
}
//---------------------------------------------------------------------------
