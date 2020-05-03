//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <System.Ioutils.hpp>
#include "Config.h"
#include <xml.xmldoc.hpp>
#include "CommFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm(TComponent* Owner)
	: TForm(Owner)
{
#if  defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	AppPath= System::Ioutils::TPath::GetDocumentsPath();
#else
	AppPath = ExtractFilePath(ParamStr(0));
#endif
	settingfile=System::Ioutils::TPath::Combine(AppPath, "ClientConfig.xml");
	ReadOption();
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::ReadOption()
{
	if(!FileExists(settingfile))
		throw Exception(L"找不到系统配置文件"+settingfile);
	_di_IXMLDocument XMLDocument1 = LoadXMLDocument(settingfile);

	IXMLNodeList *NodeList=XMLDocument1->ChildNodes;
	int count=NodeList->Count;
	IXMLNode *selectNode=NULL;
	for(int i=0;i<count;i++)
	{
		IXMLNode *curNode=NodeList->Nodes[i];
		if(curNode->LocalName==String("DefaultSettings")&&(curNode->GetAttribute("Version")==String("2.0.0.2")))
		{
			selectNode=curNode;
			break;
		}
	}
	if(selectNode!=NULL)
	{
		IXMLNodeList *sNodeList=selectNode->ChildNodes;
		for(int j=0;j<sNodeList->Count;j++)
		{
			IXMLNode *sNode=sNodeList->Nodes[j];
			if(sNode->GetAttribute("Name")==String("AgentAddress"))
				edAgentIP->Text=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("AgentPort"))
				edAgentPort->Text=sNode->GetAttribute("value");
			else if(sNode->GetAttribute("Name")==String("Protocol"))
			{
			  int index=cbProtocol->Items->IndexOf(sNode->GetAttribute("value"));
			  cbProtocol->ItemIndex=index;
			}
			else if(sNode->GetAttribute("Name")==String("BaseBusiRate"))
				nbBaseBusiRate->Value=GetFloatFromStr(sNode->GetAttribute("value"));
			else if(sNode->GetAttribute("Name")==String("BaseAccuRate"))
				nbBaseAccuRate->Value=GetFloatFromStr(sNode->GetAttribute("value"));
		}
	}
	XMLDocument1->Active=false;
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::WriteOption()
{
	if(!FileExists(settingfile))
		throw Exception(L"找不到系统配置文件"+settingfile);
	_di_IXMLDocument XMLDocument1 = LoadXMLDocument(settingfile);
	IXMLNodeList *NodeList=XMLDocument1->ChildNodes;
	int count=NodeList->Count;
	IXMLNode *selectNode=NULL;
	for(int i=0;i<count;i++)
	{
		IXMLNode *curNode=NodeList->Nodes[i];
		if(curNode->LocalName==String("DefaultSettings")&&(curNode->GetAttribute("Version")==String("2.0.0.2")))
		{
			selectNode=curNode;
			break;
		}
	}
	if(selectNode!=NULL)
	{
		IXMLNodeList *sNodeList=selectNode->ChildNodes;
		bool IsAgentAddress=false,IsAgentPort=false,IsProtocol=false,IsBaseBusiRate=false,IsBaseAccuRate=false;
		for(int j=0;j<sNodeList->Count;j++)
		{
			IXMLNode *sNode=sNodeList->Nodes[j];
			if(sNode->GetAttribute("Name")==String("AgentAddress"))
			{
				sNode->Attributes["value"]= edAgentIP->Text;
				IsAgentAddress = true;
			}
			else if(sNode->GetAttribute("Name")==String("AgentPort"))
			{
				sNode->Attributes["value"]=edAgentPort->Text;
				IsAgentPort=true;
			}
			else if(sNode->GetAttribute("Name")==String("Protocol"))
			{
				sNode->Attributes["value"]=cbProtocol->Items->Strings[cbProtocol->ItemIndex];
				IsProtocol=true;
			}
			else if(sNode->GetAttribute("Name")==String("BaseBusiRate"))
			{
				sNode->Attributes["value"]=nbBaseBusiRate->Value;
				IsBaseBusiRate=true;
			}
			else if(sNode->GetAttribute("Name")==String("BaseAccuRate"))
			{
				sNode->Attributes["value"]=nbBaseAccuRate->Value;
				IsBaseAccuRate=true;
			}
		}
		if(!IsAgentAddress)
		{
			IXMLNode *tempNode = selectNode->AddChild("Setting");
			tempNode->LocalName==String("Setting");
			tempNode->Attributes["Name"]= "AgentAddress";
			tempNode->Attributes["value"]= edAgentIP->Text;
		}
		if(!IsAgentPort)
		{
			IXMLNode *tempNode = selectNode->AddChild("Setting");
			tempNode->LocalName==String("Setting");
			tempNode->Attributes["Name"]= "AgentPort";
			tempNode->Attributes["value"]= edAgentPort->Text;
		}
		if(!IsProtocol)
		{
			IXMLNode *tempNode = selectNode->AddChild("Setting");
			tempNode->LocalName==String("Setting");
			tempNode->Attributes["Name"]= "Protocol";
			tempNode->Attributes["value"]= cbProtocol->Items->Strings[cbProtocol->ItemIndex];
		}
		if(!IsBaseBusiRate)
		{
			IXMLNode *tempNode = selectNode->AddChild("Setting");
			tempNode->LocalName==String("Setting");
			tempNode->Attributes["Name"]= "BaseBusiRate";
			tempNode->Attributes["value"]= nbBaseBusiRate->Value;
		}
		if(!IsBaseAccuRate)
		{
			IXMLNode *tempNode = selectNode->AddChild("Setting");
			tempNode->LocalName==String("Setting");
			tempNode->Attributes["Name"]= "BaseAccuRate";
			tempNode->Attributes["value"]= nbBaseAccuRate->Value;
		}
		XMLDocument1->SaveToFile(settingfile);
	}
	XMLDocument1->Active=false;
}
void __fastcall TConfigForm::btSaveClick(TObject *Sender)
{
	WriteOption();
	Close();
   //	ModalResult=System::Uitypes::TModalResult(mrOk);
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::btCancelClick(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::FormVirtualKeyboardHidden(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
	if(MainVertScrollBox)
	{
		MainVertScrollBox->Align = TAlignLayout::Client;
		MainVertScrollBox->RealignContent();
	}
//	FKBBounds = TRectF(0,0,0,0);
//	FNeedOffset = False;
//	RestorePosition();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::FormVirtualKeyboardShown(TObject *Sender, bool KeyboardVisible,
          const TRect &Bounds)
{
 	FKBBounds = TRectF(Bounds);
	FKBBounds = TRectF(ScreenToClient(FKBBounds.TopLeft()),ScreenToClient(FKBBounds.BottomRight()));
	MainVertScrollBox->Align = TAlignLayout::Horizontal;
	MainVertScrollBox->Height  = Screen->Height  - FKBBounds.Height();
	MainVertScrollBox->RealignContent();
	//UpdateKBBounds();
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::UpdateKBBounds()
{
	FNeedOffset = false;
	if (Focused != NULL) {
		TControl * LFocused = static_cast<TControl*>(Focused->GetObject());
		TRectF LFocusRect = LFocused->AbsoluteRect;
		LFocusRect.Offset(MainVertScrollBox->ViewportPosition.X, MainVertScrollBox->ViewportPosition.Y);
		if (LFocusRect.IntersectsWith(FKBBounds) && LFocusRect.Bottom > FKBBounds.Top) {
			FNeedOffset = true;
			MainLayout->Align = TAlignLayout::Horizontal;
			MainVertScrollBox->RealignContent();
			Application->ProcessMessages();
			MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X,
				LFocusRect.Bottom - FKBBounds.Top);
		}
	}
	if (!FNeedOffset) {
		RestorePosition();
	}
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::RestorePosition()
{
	MainVertScrollBox->ViewportPosition = PointF(MainVertScrollBox->ViewportPosition.X, 0);
	MainLayout->Align = TAlignLayout::Client;
	MainVertScrollBox->RealignContent();
}
//---------------------------------------------------------------------------

