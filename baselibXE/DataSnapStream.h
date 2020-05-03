//---------------------------------------------------------------------------

#ifndef DataSnapStreamH
#define DataSnapStreamH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class PACKAGE TDataSnapStream :public TMemoryStream
{
public:
   __fastcall virtual ~TDataSnapStream(void);
   __fastcall TDataSnapStream(void);
   __fastcall TDataSnapStream(TStream* AStream);
   void __fastcall LoadFromStream(TStream* AStream);
};
#endif
