//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------ç
USEFORM("ServerContainerModule.cpp", ServerControlModule); /* TDataModule: File Type */
USEFORM("MainForm.cpp", frmMainForm);
USEFORM("AppSetup.cpp", frmAppSetup);
USEFORM("EditServer.cpp", frmEditServer);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMainForm), &frmMainForm);
		Application->CreateForm(__classid(TServerControlModule), &ServerControlModule);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

