//---------------------------------------------------------------------------

#ifndef fsScreenCursorH
#define fsScreenCursorH
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
//---------------------------------------------------------------------------
class TfsScreenCursor : public TObject
{
private:
		TCursor SaveCursor;
		void __fastcall SetCurCursor(TCursor Value);
		TCursor __fastcall GetCurCursor();
protected:

public:
	__fastcall TfsScreenCursor();
	__fastcall ~TfsScreenCursor();
	__property TCursor Cursor={read = GetCurCursor,write = SetCurCursor};
};
#endif
