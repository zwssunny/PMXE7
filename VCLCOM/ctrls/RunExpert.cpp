//---------------------------------------------------------------------------
/*--------------------------------------------------------------------------
 声明
 邦永科技公司，版权所有2002 .
 创建于 2002-06-07
 作者：詹文生
  ------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop

#include "RunExpert.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
const AnsiString SMainMenuNotFound = "对不起,找不到IDE主菜单";
const AnsiString SRunMenuNotFound = "对不起,找不到运行子菜单";
const AnsiString SProjectMenuNotFound = "对不起,找不到工程子菜单";
const AnsiString SCurrentProjectNotFound = "对不起,当前工程不可用";
const AnsiString SCaption="错误";
//MenuItem option
const AnsiString SRunSeparatelyCaption = "分离执行";
const AnsiString SExpertIDString = "RsCreate.RunExpert";
const AnsiString SExpertName = "分离执行";
/* do not localize */
const AnsiString SRunMenuName = "RunMenu";
const AnsiString SProjectMenuName = "ProjectMenu";
const AnsiString SBuildAllItemName = "ProjectBuildAllItem";
//add menuItem
const AnsiString SRunSeparatelyItemName = "RunSeparatellyItem";
namespace Runexpert
{
        void __fastcall PACKAGE Register()
        {
         RegisterPackageWizard(new TRunExpert);
        }
}
//---------------------------------------------------------------------------
_di_IOTAProject __fastcall GetCurrentProject ()
{
  int i;
  _di_IOTAModuleServices Temp;
  _di_IOTAModule Module;
  _di_IOTAProject Project = NULL;
  _di_IOTAProjectGroup ProjectGroup = NULL;
  HRESULT hr;
  hr = BorlandIDEServices->QueryInterface (__uuidof (IOTAModuleServices),
					   (void **) &Temp);
  if (FAILED (hr))
    return NULL;
  for (i = 0; i < Temp->ModuleCount; ++i)
    {
      Module = Temp->Modules[i];
      if (Module->QueryInterface (__uuidof (IOTAProjectGroup), (void **)
	  &ProjectGroup) == S_OK)
	{
	  return ProjectGroup->ActiveProject;
	}
      else
        if (Module->QueryInterface (__uuidof (IOTAProject), (void **)
	      &Project) == S_OK)
	    return Project;
    }
  return NULL;
}
//---------------------------------------------------------------------------
__fastcall TRunExpert::TRunExpert ()
        :IOTAMenuWizard ()
{
  TMenu *IDEMenu = NULL;		// IDE Main Menu
  m_Count = 0;
  int  i;
  _di_INTAServices  services;
  HRESULT  hr;
  hr = BorlandIDEServices->QueryInterface (__uuidof (INTAServices), (void
					   **) &services);
  if (FAILED (hr))
    {
      MessageBox(NULL,SMainMenuNotFound.c_str(), SCaption.c_str(), MB_OK|MB_ICONERROR);
      return;
    }
  IDEMenu = services->GetMainMenu ();
  if (IDEMenu == NULL)
    {
      MessageBox(NULL,SMainMenuNotFound.c_str(), SCaption.c_str(), MB_OK|MB_ICONERROR);
      return;
    }
  for (i = 0; i < IDEMenu->Items->Count; i++)
    {
      if (CompareText (IDEMenu->Items->Items[i]->Name, SRunMenuName) == 0)
	RunMenuItem = IDEMenu->Items->Items[i];
      if (CompareText (IDEMenu->Items->Items[i]->Name, SProjectMenuName) == 0)
	ProjectMenuItem = IDEMenu->Items->Items[i];
    }
  if (RunMenuItem == NULL)
    {
      MessageBox(NULL,SRunMenuNotFound.c_str(), SCaption.c_str(), MB_OK|MB_ICONERROR);
      return;
    }
  if (ProjectMenuItem == NULL)
    {
      MessageBox(NULL,SProjectMenuNotFound.c_str(), SCaption.c_str(), MB_OK|MB_ICONERROR);
      return;
    }
  for (i == 0; i < ProjectMenuItem->Count; ++i)
    {
      if (CompareText (ProjectMenuItem->Items[i]->Name, SBuildAllItemName)
	  == 0)
	BuildAllItem = ProjectMenuItem->Items[i];
    }
  if (BuildAllItem != NULL)
    BuildAllItem->ShortCut = ShortCut (VK_F9, TShiftState () << ssCtrl << ssShift);

  RSItem = new TMenuItem (NULL);
  RSItem->Name = SRunSeparatelyItemName;
  RSItem->Caption = SRunSeparatelyCaption;
  RSItem->AutoHotkeys = maManual;
  RSItem->OnClick = OnClick;
  RunMenuItem->Insert (1, RSItem);
  RSItem->ShortCut = ShortCut (VK_F9, TShiftState () << ssShift);
  FTimer = new TTimer (NULL);
  FTimer->Interval = 1000;
  FTimer->OnTimer = OnTimer;
  FTimer->Enabled = true;

}

__fastcall TRunExpert::~TRunExpert ()
{
  int Index;
  if (RunMenuItem)
    {
      Index = RunMenuItem->IndexOf (RSItem);
      if (Index >= 0)
	RunMenuItem->Delete (Index);
    }
  delete RSItem;
  delete FTimer;
}

void __fastcall TRunExpert::OnClick (TObject * Sender)
{
  Execute ();
}

void __fastcall TRunExpert::OnTimer (TObject * Sender)
{
  if ((RSItem != NULL) && (RSItem->ShortCut == 0))
    RSItem->ShortCut = ShortCut (VK_F9, TShiftState () << ssShift);
  if (BuildAllItem != NULL)
    BuildAllItem->ShortCut = ShortCut (VK_F9, TShiftState () << ssShift << ssCtrl);
  FTimer->Enabled = false;

}

AnsiString __fastcall TRunExpert::GetIDString ()
{
  return SExpertIDString;
}

AnsiString __fastcall TRunExpert::GetName ()
{
  return SExpertName;
}
AnsiString __fastcall TRunExpert::GetMenuText ()
{
  return SExpertName;
}
TWizardState __fastcall TRunExpert::GetState (void)
{
  return TWizardState () << wsEnabled;
}

void __fastcall TRunExpert::Execute (void)
{
  _di_IOTAProject   Project;
  _di_IOTAProjectOptions   ProjectOptions;
  _di_IOTAProjectBuilder   ProjectBuilder;
  AnsiString   OutputDir, ProjectFileName, ExeName, ProjectExt;
  Project = GetCurrentProject ();
  if (Project == NULL)
    {
      MessageBox(NULL,SCurrentProjectNotFound.c_str(), SCaption.c_str(), MB_OK|MB_ICONERROR);
      return;
    }
  // get project file name
  ProjectFileName = Project->GetFileName ();
  ProjectExt = ExtractFileExt (ProjectFileName);
  // don't try run  bpk, etc...
  if (!((CompareText (ProjectExt, ".cpp") == 0) ||
	(CompareText (ProjectExt, ".bpr") == 0)))
    return;
  // compile project
  ProjectBuilder = Project->GetProjectBuilder ();
  // Exit if failure
  if (!ProjectBuilder->BuildProject (cmOTAMake, false, true))
    return;
  // get output directory
  ProjectOptions = Project->GetProjectOptions ();

  OutputDir = ProjectOptions->GetOptionValue ("OutputDir");
  if (OutputDir == "")
    ExeName = ChangeFileExt (ProjectFileName, ".exe");
  else if (OutputDir[OutputDir.Length ()] != '\\')
    {
      OutputDir = OutputDir + "\\";
      ExeName = OutputDir + ChangeFileExt (ExtractFileName
					   (ProjectFileName), ".exe");
    }
  // try executing file
  if (FileExists (ExeName))
    ShellExecute (0, "open", ExeName.c_str (), NULL, NULL, SW_SHOWNORMAL);
}
ULONG STDMETHODCALLTYPE TRunExpert::AddRef ()
{
  return InterlockedIncrement (&m_Count);
}
ULONG STDMETHODCALLTYPE TRunExpert::Release ()
{
  if (InterlockedDecrement (&m_Count) == 0)
    {
      delete this;
      return 0;
    }
  return m_Count;
}
HRESULT STDMETHODCALLTYPE TRunExpert::QueryInterface (REFIID riid,
			    void __RPC_FAR * __RPC_FAR * ppvObject)
{
  *ppvObject = NULL;

  if (IsEqualIID (riid, __uuidof (IUnknown)))
    *ppvObject = static_cast < IUnknown * >(this);
  else if (IsEqualIID (riid, __uuidof (IOTANotifier)))
    *ppvObject = static_cast < IOTANotifier * >(this);
  else if (IsEqualIID (riid, __uuidof (IOTAWizard)))
    *ppvObject = static_cast < IOTAWizard * >(this);
  else if (IsEqualIID (riid, __uuidof (IOTAMenuWizard)))
    *ppvObject = static_cast < IOTAMenuWizard * >(this);

  if (*ppvObject != NULL)
    {
      reinterpret_cast < IUnknown * >(*ppvObject)->AddRef ();
      return S_OK;
    }

  return E_NOINTERFACE;

}

