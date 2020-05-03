//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.iPhone.fmx", _PLAT_IOS)

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
TDateEdit Component throw Exception can crash the app In XE7
1.NEW a Multi-device application in C++builder
2.Drop a TVertScrollBox Component into main form, Set the name property to "VertScrollBox1", Set the Align property  to Client;
3.Drop a TPanel Component into VertScrollBox1,name it "Panel2". Set the Align property  to "Top",Height to 800.
4.Scroll the Panel more bottom.
5.Drop two TDateEdit Components into more bottom of Panel2 ,Set the name to "DateEdit2" and "DateEdit3".
6.Scroll the Panel more top.
7.build and deploy to android device ,my device is ZTE Q802T.
8.In my Mobile phone,run the application ,scroll the panel to show "DateEdit2" and "DateEdit3",then it throw Exception and exit the application;
9.the same result use other mobile phone like coolpad 8705.
10.XE6 is run Ok but not in XE7.
*/


