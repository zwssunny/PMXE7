// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsControls.pas' rev: 28.00 (Windows)

#ifndef WscontrolsHPP
#define WscontrolsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.Forms.hpp>	// Pascal unit
#include <Vcl.StdCtrls.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.ComCtrls.hpp>	// Pascal unit
#include <wsMain.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <Vcl.FileCtrl.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <wsDB.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wscontrols
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TLVWorkflowDefinitions;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TLVWorkflowDefinitions : public Wsclasses::TWorkflowDefinitions
{
	typedef Wsclasses::TWorkflowDefinitions inherited;
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
public:
	/* TWorkflowDefinitions.Create */ inline __fastcall TLVWorkflowDefinitions(System::Classes::TComponent* AOwner) : Wsclasses::TWorkflowDefinitions(AOwner) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TLVWorkflowDefinitions(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowListView;
class PASCALIMPLEMENTATION TWorkflowListView : public Vcl::Comctrls::TListView
{
	typedef Vcl::Comctrls::TListView inherited;
	
private:
	Wsmain::TWorkflowStudio* FWorkflowStudio;
	Wsmain::TWorkflowStudio* __fastcall GetWorkflowStudio(void);
	virtual void __fastcall SetWorkflowStudio(Wsmain::TWorkflowStudio* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__property Wsmain::TWorkflowStudio* WorkflowStudio = {read=GetWorkflowStudio, write=SetWorkflowStudio};
public:
	/* TCustomListView.Create */ inline __fastcall virtual TWorkflowListView(System::Classes::TComponent* AOwner) : Vcl::Comctrls::TListView(AOwner) { }
	/* TCustomListView.Destroy */ inline __fastcall virtual ~TWorkflowListView(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TWorkflowListView(HWND ParentWindow) : Vcl::Comctrls::TListView(ParentWindow) { }
	
};


class DELPHICLASS TWorkDefListView;
class PASCALIMPLEMENTATION TWorkDefListView : public TWorkflowListView
{
	typedef TWorkflowListView inherited;
	
private:
	Wsclasses::TWorkflowDefinitions* FWorkDefs;
	void __fastcall UpdateWorkflowItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TWorkflowDefinition* AWorkDef);
	Wsclasses::TWorkflowDefinition* __fastcall GetSelectedWorkDef(void);
	void __fastcall SelectItemByKey(System::UnicodeString AKey);
	HIDESBASE void __fastcall UpdateItems(void);
	virtual void __fastcall SetWorkflowStudio(Wsmain::TWorkflowStudio* const Value);
	
public:
	__fastcall virtual TWorkDefListView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWorkDefListView(void);
	void __fastcall SelectItemByWorkDef(Wsclasses::TWorkflowDefinition* AWorkDef);
	void __fastcall LoadFromDatabase(void);
	Vcl::Comctrls::TListItem* __fastcall AddWorkDefItem(void);
	Wsclasses::TWorkflowDefinition* __fastcall WorkDefFromItem(Vcl::Comctrls::TListItem* AItem);
	__property Wsclasses::TWorkflowDefinition* SelectedWorkDef = {read=GetSelectedWorkDef};
	__property Wsclasses::TWorkflowDefinitions* WorkDefs = {read=FWorkDefs};
	
__published:
	__property WorkflowStudio;
public:
	/* TWinControl.CreateParented */ inline __fastcall TWorkDefListView(HWND ParentWindow) : TWorkflowListView(ParentWindow) { }
	
};


class DELPHICLASS TTaskStatusCombo;
class PASCALIMPLEMENTATION TTaskStatusCombo : public Vcl::Stdctrls::TComboBox
{
	typedef Vcl::Stdctrls::TComboBox inherited;
	
private:
	Wsclasses::TTaskInstance* FTask;
	void __fastcall SetTask(Wsclasses::TTaskInstance* const Value);
	void __fastcall FillStatusItems(void);
	void __fastcall SetStatus(System::UnicodeString AStatus);
	System::UnicodeString __fastcall GetStatus(void);
	
public:
	__fastcall virtual TTaskStatusCombo(System::Classes::TComponent* AOwner);
	__property Wsclasses::TTaskInstance* TaskInstance = {read=FTask, write=SetTask};
	__property System::UnicodeString Status = {read=GetStatus, write=SetStatus};
	
__published:
	__property Style = {default=2};
public:
	/* TCustomComboBox.Destroy */ inline __fastcall virtual ~TTaskStatusCombo(void) { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTaskStatusCombo(HWND ParentWindow) : Vcl::Stdctrls::TComboBox(ParentWindow) { }
	
};


class DELPHICLASS TTaskListView;
class PASCALIMPLEMENTATION TTaskListView : public TWorkflowListView
{
	typedef TWorkflowListView inherited;
	
private:
	Wsclasses::TTaskInstanceList* FTasks;
	Wsclasses::TTaskFilterType FFilterType;
	System::UnicodeString FFilterKey;
	System::UnicodeString FOtherCondition;
	int FCompletedState;
	void __fastcall UpdateTaskItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TTaskInstance* ATask);
	Wsclasses::TTaskInstance* __fastcall GetSelectedTask(void);
	void __fastcall SelectItemByTask(Wsclasses::TTaskInstance* ATask);
	void __fastcall SelectItemByKey(System::UnicodeString AKey);
	HIDESBASE void __fastcall UpdateColumns(void);
	void __fastcall UpdateDefinitionNames(void);
	virtual void __fastcall SetWorkflowStudio(Wsmain::TWorkflowStudio* const Value);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TTaskListView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTaskListView(void);
	Wsclasses::TTaskInstance* __fastcall TaskFromItem(Vcl::Comctrls::TListItem* AItem);
	HIDESBASE void __fastcall UpdateItems(void);
	void __fastcall LoadFromDatabase(void);
	__property Wsclasses::TTaskInstance* SelectedTask = {read=GetSelectedTask};
	__property Wsclasses::TTaskInstanceList* TaskInstances = {read=FTasks};
	__property Wsclasses::TTaskFilterType FilterType = {read=FFilterType, write=FFilterType, nodefault};
	__property System::UnicodeString FilterKey = {read=FFilterKey, write=FFilterKey};
	__property int CompletedState = {read=FCompletedState, write=FCompletedState, nodefault};
	__property System::UnicodeString OtherCondition = {read=FOtherCondition, write=FOtherCondition};
	
__published:
	__property Columns = {stored=false};
	__property WorkflowStudio;
public:
	/* TWinControl.CreateParented */ inline __fastcall TTaskListView(HWND ParentWindow) : TWorkflowListView(ParentWindow) { }
	
};


class DELPHICLASS TLVAttachmentItems;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TLVAttachmentItems : public Wsclasses::TAttachmentItems
{
	typedef Wsclasses::TAttachmentItems inherited;
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
public:
	/* TAttachmentItems.Create */ inline __fastcall TLVAttachmentItems(System::Classes::TPersistent* AOwner) : Wsclasses::TAttachmentItems(AOwner) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TLVAttachmentItems(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TAttachmentListView;
class PASCALIMPLEMENTATION TAttachmentListView : public TWorkflowListView
{
	typedef TWorkflowListView inherited;
	
private:
	Wsclasses::TAttachmentItems* FAttachs;
	Vcl::Controls::TImageList* FLargeImages;
	System::Classes::TStrings* FLargeExts;
	Vcl::Controls::TImageList* FSmallImages;
	System::Classes::TStrings* FSmallExts;
	bool FAllowDropFiles;
	void __fastcall UpdateAttachmentItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TAttachmentItem* AAttach);
	Wsclasses::TAttachmentItem* __fastcall GetSelectedAttachment(void);
	void __fastcall SetAttachments(Wsclasses::TAttachmentItems* const Value);
	MESSAGE void __fastcall DropMsg(Winapi::Messages::TWMDropFiles &msg);
	void __fastcall SelectItemByAttachment(Wsclasses::TAttachmentItem* AAttach);
	Wsclasses::TAttachmentItem* __fastcall AttachmentFromItem(Vcl::Comctrls::TListItem* AItem);
	__property Wsclasses::TAttachmentItem* SelectedAttachment = {read=GetSelectedAttachment};
	int __fastcall ImageIndexByExt(System::UnicodeString AExt);
	void __fastcall AdjustColumns(void);
	void __fastcall SetFAllowDropFiles(const bool Value);
	virtual void __fastcall SetWorkflowStudio(Wsmain::TWorkflowStudio* const Value);
	
protected:
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TAttachmentListView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TAttachmentListView(void);
	HIDESBASE void __fastcall UpdateItems(void);
	Wsclasses::TAttachmentItem* __fastcall AddFile(System::UnicodeString AFileName);
	void __fastcall DeleteSelecteds(void);
	void __fastcall OpenSelecteds(bool AllowEdit);
	__property Wsclasses::TAttachmentItems* Attachments = {read=FAttachs, write=SetAttachments};
	__property bool AllowDropFiles = {read=FAllowDropFiles, write=SetFAllowDropFiles, nodefault};
	
__published:
	__property Columns = {stored=false};
	__property WorkflowStudio;
public:
	/* TWinControl.CreateParented */ inline __fastcall TAttachmentListView(HWND ParentWindow) : TWorkflowListView(ParentWindow) { }
	
};


class DELPHICLASS TTaskFieldCustomControl;
class DELPHICLASS TTaskFieldPanel;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskFieldCustomControl : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Vcl::Controls::TWinControl* FControl;
	TTaskFieldPanel* FPanel;
	bool FModified;
	
protected:
	virtual void __fastcall SetReadOnly(bool AValue);
	virtual Vcl::Controls::TWinControl* __fastcall CreateControl(System::Classes::TComponent* AOwner) = 0 ;
	virtual void __fastcall SetValue(const System::Variant &AValue) = 0 ;
	virtual System::Variant __fastcall GetValue(void) = 0 ;
	virtual bool __fastcall IsEmpty(void) = 0 ;
	void __fastcall Change(void);
	void __fastcall EditorChange(System::TObject* Sender);
	__property TTaskFieldPanel* Panel = {read=FPanel};
	
public:
	__fastcall TTaskFieldCustomControl(TTaskFieldPanel* AOwner);
	__fastcall virtual ~TTaskFieldCustomControl(void);
	__property Vcl::Controls::TWinControl* Control = {read=FControl};
};

#pragma pack(pop)

class DELPHICLASS TTaskFieldEdit;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskFieldEdit : public TTaskFieldCustomControl
{
	typedef TTaskFieldCustomControl inherited;
	
protected:
	virtual void __fastcall SetReadOnly(bool AValue);
	virtual Vcl::Controls::TWinControl* __fastcall CreateControl(System::Classes::TComponent* AOwner);
	virtual void __fastcall SetValue(const System::Variant &AValue);
	virtual System::Variant __fastcall GetValue(void);
	virtual bool __fastcall IsEmpty(void);
	Vcl::Stdctrls::TEdit* __fastcall EditControl(void);
public:
	/* TTaskFieldCustomControl.Create */ inline __fastcall TTaskFieldEdit(TTaskFieldPanel* AOwner) : TTaskFieldCustomControl(AOwner) { }
	/* TTaskFieldCustomControl.Destroy */ inline __fastcall virtual ~TTaskFieldEdit(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskFieldEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskFieldEditor : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	Vcl::Stdctrls::TLabel* FLabel;
	TTaskFieldCustomControl* FEditor;
	Wsclasses::TTaskField* FField;
	
public:
	__fastcall virtual ~TTaskFieldEditor(void);
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TTaskFieldEditor(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	
};

#pragma pack(pop)

class DELPHICLASS TTaskFieldEditors;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TTaskFieldEditors : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TTaskFieldEditor* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TTaskFieldEditor* __fastcall GetItem(int Index);
	
public:
	HIDESBASE TTaskFieldEditor* __fastcall Add(void);
	__property TTaskFieldEditor* Items[int Index] = {read=GetItem/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TTaskFieldEditors(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TTaskFieldEditors(void) { }
	
};

#pragma pack(pop)

struct DECLSPEC_DRECORD TFieldErrorInfo
{
public:
	TTaskFieldEditor* Editor;
	System::UnicodeString msg;
};


class PASCALIMPLEMENTATION TTaskFieldPanel : public Vcl::Forms::TScrollBox
{
	typedef Vcl::Forms::TScrollBox inherited;
	
private:
	Wsclasses::TTaskFields* FFields;
	TTaskFieldEditors* FEditors;
	int FVertInterspace;
	int FVertMargin;
	int FHorzInterspace;
	int FHorzMargin;
	int FUpdatingVars;
	bool FModified;
	TFieldErrorInfo FErrorInfo;
	bool FReadOnly;
	void __fastcall SetFields(Wsclasses::TTaskFields* const Value);
	void __fastcall UpdateVarControls(void);
	void __fastcall CreateControl(Wsclasses::TTaskField* AField);
	void __fastcall DestroyControls(void);
	void __fastcall ArrangeControls(void);
	void __fastcall ArrangeLabelsVertical(void);
	void __fastcall SetReadOnly(const bool Value);
	
protected:
	DYNAMIC void __fastcall Resize(void);
	virtual void __fastcall PaintWindow(HDC DC);
	
public:
	__fastcall virtual TTaskFieldPanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTaskFieldPanel(void);
	void __fastcall LoadDiagramVariables(Wsclasses::TCustomWorkflowDiagram* ADiagram);
	void __fastcall SaveDiagramVariables(Wsclasses::TCustomWorkflowDiagram* ADiagram);
	bool __fastcall ValidateValues(void);
	void __fastcall FocusLastError(void);
	__property TFieldErrorInfo ErrorInfo = {read=FErrorInfo};
	__property Wsclasses::TTaskFields* Fields = {read=FFields, write=SetFields};
	__property int HorzMargin = {read=FHorzMargin, write=FHorzMargin, nodefault};
	__property int VertMargin = {read=FVertMargin, write=FVertMargin, nodefault};
	__property int HorzInterSpace = {read=FHorzInterspace, write=FHorzInterspace, nodefault};
	__property int VertInterSpace = {read=FVertInterspace, write=FVertInterspace, nodefault};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, nodefault};
public:
	/* TWinControl.CreateParented */ inline __fastcall TTaskFieldPanel(HWND ParentWindow) : Vcl::Forms::TScrollBox(ParentWindow) { }
	
};


class DELPHICLASS TTaskLogListView;
class PASCALIMPLEMENTATION TTaskLogListView : public TWorkflowListView
{
	typedef TWorkflowListView inherited;
	
private:
	Wsclasses::TLogFilterType FFilterType;
	System::UnicodeString FFilterKey;
	Wsclasses::TTaskLogItems* FLogItems;
	Wsclasses::TTaskInstanceList* FTasks;
	void __fastcall UpdateLogItem(Vcl::Comctrls::TListItem* AItem, Wsclasses::TTaskLogItem* ALogItem);
	HIDESBASE void __fastcall UpdateColumns(void);
	System::UnicodeString __fastcall LogOperationText(Wsclasses::TTaskLogOperation AOperation);
	
protected:
	virtual void __fastcall Loaded(void);
	
public:
	__fastcall virtual TTaskLogListView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTaskLogListView(void);
	HIDESBASE void __fastcall UpdateItems(void);
	void __fastcall LoadFromDatabase(void);
	__property Wsclasses::TLogFilterType FilterType = {read=FFilterType, write=FFilterType, nodefault};
	__property System::UnicodeString FilterKey = {read=FFilterKey, write=FFilterKey};
	__property Wsclasses::TTaskInstanceList* TaskInstances = {read=FTasks};
	
__published:
	__property Columns = {stored=false};
	__property WorkflowStudio;
public:
	/* TWinControl.CreateParented */ inline __fastcall TTaskLogListView(HWND ParentWindow) : TWorkflowListView(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wscontrols */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSCONTROLS)
using namespace Wscontrols;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WscontrolsHPP
