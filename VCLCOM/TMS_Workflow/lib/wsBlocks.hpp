// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'wsBlocks.pas' rev: 28.00 (Windows)

#ifndef WsblocksHPP
#define WsblocksHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Winapi.Messages.hpp>	// Pascal unit
#include <Vcl.Controls.hpp>	// Pascal unit
#include <Vcl.Dialogs.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <System.Variants.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <DgrGdipApi.hpp>	// Pascal unit
#include <DgrGdipObj.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit
#include <DiagramActns.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <wsClasses.hpp>	// Pascal unit
#include <wsDiagram.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Wsblocks
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TWorkflowToolbarBlocks;
class PASCALIMPLEMENTATION TWorkflowToolbarBlocks : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	/* TComponent.Create */ inline __fastcall virtual TWorkflowToolbarBlocks(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TWorkflowToolbarBlocks(void) { }
	
};


class DELPHICLASS TWorkflowBlock;
class PASCALIMPLEMENTATION TWorkflowBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
__published:
	__property OnExecuteEx;
public:
	/* TCustomWorkflowBlock.Create */ inline __fastcall virtual TWorkflowBlock(System::Classes::TComponent* AOwner) : Wsclasses::TCustomWorkflowBlock(AOwner) { }
	/* TCustomWorkflowBlock.Destroy */ inline __fastcall virtual ~TWorkflowBlock(void) { }
	
};


class DELPHICLASS TWorkflowStartBlock;
class PASCALIMPLEMENTATION TWorkflowStartBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
protected:
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	
public:
	__fastcall virtual TWorkflowStartBlock(System::Classes::TComponent* AOwner);
	
__published:
	__property OnExecuteEx;
public:
	/* TCustomWorkflowBlock.Destroy */ inline __fastcall virtual ~TWorkflowStartBlock(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


class DELPHICLASS TWorkflowEndBlock;
class PASCALIMPLEMENTATION TWorkflowEndBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
protected:
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TWorkflowEndBlock(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Link(void);
	virtual void __fastcall ExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	
__published:
	__property OnExecuteEx;
public:
	/* TCustomWorkflowBlock.Destroy */ inline __fastcall virtual ~TWorkflowEndBlock(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


class DELPHICLASS TWorkflowErrorBlock;
class PASCALIMPLEMENTATION TWorkflowErrorBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
public:
	__fastcall virtual TWorkflowErrorBlock(System::Classes::TComponent* AOwner);
	
__published:
	__property OnExecuteEx;
public:
	/* TCustomWorkflowBlock.Destroy */ inline __fastcall virtual ~TWorkflowErrorBlock(void) { }
	
};


class DELPHICLASS TWorkflowConnectorSource;
class PASCALIMPLEMENTATION TWorkflowConnectorSource : public Livediagram::TLiveConnectorSource
{
	typedef Livediagram::TLiveConnectorSource inherited;
	
public:
	/* TCustomLiveConnector.Create */ inline __fastcall virtual TWorkflowConnectorSource(System::Classes::TComponent* AOwner) : Livediagram::TLiveConnectorSource(AOwner) { }
	
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TWorkflowConnectorSource(void) { }
	
};


class DELPHICLASS TWorkflowConnectorTarget;
class PASCALIMPLEMENTATION TWorkflowConnectorTarget : public Livediagram::TLiveConnectorTarget
{
	typedef Livediagram::TLiveConnectorTarget inherited;
	
public:
	/* TCustomLiveConnector.Create */ inline __fastcall virtual TWorkflowConnectorTarget(System::Classes::TComponent* AOwner) : Livediagram::TLiveConnectorTarget(AOwner) { }
	
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TWorkflowConnectorTarget(void) { }
	
};


class DELPHICLASS TWorkflowLineJoin;
class PASCALIMPLEMENTATION TWorkflowLineJoin : public Livediagram::TLiveLineJoin
{
	typedef Livediagram::TLiveLineJoin inherited;
	
public:
	/* TLiveLineJoin.Create */ inline __fastcall virtual TWorkflowLineJoin(System::Classes::TComponent* AOwner) : Livediagram::TLiveLineJoin(AOwner) { }
	
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TWorkflowLineJoin(void) { }
	
};


class DELPHICLASS TWorkflowTransition;
class PASCALIMPLEMENTATION TWorkflowTransition : public Livediagram::TLiveWire
{
	typedef Livediagram::TLiveWire inherited;
	
public:
	/* TLiveWire.Create */ inline __fastcall virtual TWorkflowTransition(System::Classes::TComponent* AOwner) : Livediagram::TLiveWire(AOwner) { }
	
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TWorkflowTransition(void) { }
	
};


class DELPHICLASS TWorkflowSideTransition;
class PASCALIMPLEMENTATION TWorkflowSideTransition : public Livediagram::TLiveSideWire
{
	typedef Livediagram::TLiveSideWire inherited;
	
public:
	/* TLiveSideWire.Create */ inline __fastcall virtual TWorkflowSideTransition(System::Classes::TComponent* AOwner) : Livediagram::TLiveSideWire(AOwner) { }
	
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TWorkflowSideTransition(void) { }
	
};


class DELPHICLASS TWorkflowArcTransition;
class PASCALIMPLEMENTATION TWorkflowArcTransition : public Livediagram::TLiveArc
{
	typedef Livediagram::TLiveArc inherited;
	
public:
	/* TLiveArc.Create */ inline __fastcall virtual TWorkflowArcTransition(System::Classes::TComponent* AOwner) : Livediagram::TLiveArc(AOwner) { }
	
public:
	/* TCustomDiagramLine.Destroy */ inline __fastcall virtual ~TWorkflowArcTransition(void) { }
	
};


class DELPHICLASS TWorkflowForkBlock;
class PASCALIMPLEMENTATION TWorkflowForkBlock : public Livediagram::TLiveForkBlock
{
	typedef Livediagram::TLiveForkBlock inherited;
	
public:
	/* TLiveForkBlock.Create */ inline __fastcall virtual TWorkflowForkBlock(System::Classes::TComponent* AOwner) : Livediagram::TLiveForkBlock(AOwner) { }
	/* TLiveForkBlock.Destroy */ inline __fastcall virtual ~TWorkflowForkBlock(void) { }
	
};


class DELPHICLASS TWorkflowJoinBlock;
class PASCALIMPLEMENTATION TWorkflowJoinBlock : public Livediagram::TLiveJoinBlock
{
	typedef Livediagram::TLiveJoinBlock inherited;
	
public:
	/* TLiveJoinBlock.Create */ inline __fastcall virtual TWorkflowJoinBlock(System::Classes::TComponent* AOwner) : Livediagram::TLiveJoinBlock(AOwner) { }
	
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TWorkflowJoinBlock(void) { }
	
};


class DELPHICLASS TCustomWorkflowTaskBlock;
class PASCALIMPLEMENTATION TCustomWorkflowTaskBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
private:
	Wsclasses::TTaskDefinitions* FTasks;
	Atdiagram::TTextCell* FStatusTextCell;
	bool FStatusChange;
	Atdiagram::TTextCell* __fastcall GetStatusTextCell(void);
	void __fastcall SetTasks(Wsclasses::TTaskDefinitions* const Value);
	
protected:
	System::TDateTime __fastcall CheckTasksExpiration(void);
	virtual bool __fastcall CheckTasksFinished(void);
	virtual void __fastcall DrawBlock(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual Diagramutils::TSquare __fastcall GetTextCellRect(Atdiagram::TTextCell* ACell, const Diagramutils::TSquare &ARect);
	virtual System::UnicodeString __fastcall TaskBlockOutput(bool ACompletionStatus = true);
	__property Atdiagram::TTextCell* StatusTextCell = {read=GetStatusTextCell};
	__property Wsclasses::TTaskDefinitions* Tasks = {read=FTasks, write=SetTasks};
	
public:
	__fastcall virtual TCustomWorkflowTaskBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWorkflowTaskBlock(void);
	virtual bool __fastcall Link(void);
	virtual void __fastcall DoExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	virtual void __fastcall FillOutputList(System::Classes::TStrings* AOutputs);
	
__published:
	__property OnExecuteEx;
};


class DELPHICLASS TWorkflowTaskBlock;
class PASCALIMPLEMENTATION TWorkflowTaskBlock : public TCustomWorkflowTaskBlock
{
	typedef TCustomWorkflowTaskBlock inherited;
	
public:
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	
__published:
	__property Tasks;
public:
	/* TCustomWorkflowTaskBlock.Create */ inline __fastcall virtual TWorkflowTaskBlock(System::Classes::TComponent* AOwner) : TCustomWorkflowTaskBlock(AOwner) { }
	/* TCustomWorkflowTaskBlock.Destroy */ inline __fastcall virtual ~TWorkflowTaskBlock(void) { }
	
};


class DELPHICLASS TWorkflowTaskBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowTaskBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowTaskBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowTaskBlockEditor(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowApprovalBlock;
class PASCALIMPLEMENTATION TWorkflowApprovalBlock : public TCustomWorkflowTaskBlock
{
	typedef TCustomWorkflowTaskBlock inherited;
	
private:
	Wsclasses::TTaskDefinition* __fastcall GetTask(void);
	void __fastcall SetTask(Wsclasses::TTaskDefinition* const Value);
	
protected:
	virtual void __fastcall InitializeApprovalTask(void);
	
public:
	__fastcall virtual TWorkflowApprovalBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWorkflowApprovalBlock(void);
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	
__published:
	__property Wsclasses::TTaskDefinition* Task = {read=GetTask, write=SetTask};
	__property OnExecuteEx;
};


class DELPHICLASS TWorkflowApprovalBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowApprovalBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowApprovalBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowApprovalBlockEditor(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowDecisionBlock;
class PASCALIMPLEMENTATION TWorkflowDecisionBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
private:
	System::UnicodeString FCondition;
	void __fastcall SetCondition(const System::UnicodeString Value);
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual void __fastcall AdjustLinkPoints(void);
	virtual int __fastcall GetLinkPointsCount(void);
	
public:
	__fastcall virtual TWorkflowDecisionBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWorkflowDecisionBlock(void);
	virtual void __fastcall DoExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	virtual void __fastcall FillOutputList(System::Classes::TStrings* AOutputs);
	
__published:
	__property OnExecuteEx;
	__property System::UnicodeString Condition = {read=FCondition, write=SetCondition};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TWorkflowDecisionBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowDecisionBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowDecisionBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowDecisionBlockEditor(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowRunWorkflowBlock;
class PASCALIMPLEMENTATION TWorkflowRunWorkflowBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
private:
	System::Classes::TStrings* FVariableMapping;
	System::UnicodeString FWorkflowDefinitionKey;
	bool FWaitExecution;
	void __fastcall SetVariableMapping(System::Classes::TStrings* const Value);
	void __fastcall SetWorkflowDefinitionKey(const System::UnicodeString Value);
	void __fastcall SetWaitExecution(const bool Value);
	void __fastcall AssignWorkflowVariables(Wsclasses::TWorkflowVariables* AFromVariables, Wsclasses::TWorkflowVariables* AToVariables, bool AReturning);
	
protected:
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TWorkflowRunWorkflowBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWorkflowRunWorkflowBlock(void);
	virtual void __fastcall DoExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	
__published:
	__property System::UnicodeString WorkflowDefinitionKey = {read=FWorkflowDefinitionKey, write=SetWorkflowDefinitionKey};
	__property System::Classes::TStrings* VariableMapping = {read=FVariableMapping, write=SetVariableMapping};
	__property bool WaitExecution = {read=FWaitExecution, write=SetWaitExecution, nodefault};
	__property OnExecuteEx;
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TWorkflowRunWorkflowBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowRunWorkflowBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowRunWorkflowBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowRunWorkflowBlockEditor(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowAuditBlock;
class PASCALIMPLEMENTATION TWorkflowAuditBlock : public Wsclasses::TCustomWorkflowBlock
{
	typedef Wsclasses::TCustomWorkflowBlock inherited;
	
private:
	System::UnicodeString FStatusText;
	System::UnicodeString FBillState;
	void __fastcall SetBillState(const System::UnicodeString Value);
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	virtual void __fastcall DoExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	__fastcall virtual TWorkflowAuditBlock(System::Classes::TComponent* AOwner);
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	
__published:
	__property OnExecuteEx;
	__property System::UnicodeString StatusText = {read=FStatusText, write=FStatusText};
	__property System::UnicodeString BillState = {read=FBillState, write=SetBillState};
public:
	/* TCustomWorkflowBlock.Destroy */ inline __fastcall virtual ~TWorkflowAuditBlock(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


class DELPHICLASS TWorkflowAuditBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowAuditBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowAuditBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowAuditBlockEditor(void) { }
	
};

#pragma pack(pop)

class DELPHICLASS TWorkflowSponsorBlock;
class PASCALIMPLEMENTATION TWorkflowSponsorBlock : public TCustomWorkflowTaskBlock
{
	typedef TCustomWorkflowTaskBlock inherited;
	
private:
	Wsclasses::TTaskDefinition* __fastcall GetTask(void);
	void __fastcall SetTask(Wsclasses::TTaskDefinition* const Value);
	
protected:
	virtual void __fastcall InitializeSponsorTask(void);
	
public:
	__fastcall virtual TWorkflowSponsorBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWorkflowSponsorBlock(void);
	virtual void __fastcall DoExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	virtual Wsclasses::TWorkflowBlockEditorClass __fastcall EditorClass(void);
	
__published:
	__property Wsclasses::TTaskDefinition* Task = {read=GetTask, write=SetTask};
	__property OnExecuteEx;
};


class DELPHICLASS TWorkflowSponsorBlockEditor;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TWorkflowSponsorBlockEditor : public Wsclasses::TWorkflowBlockEditor
{
	typedef Wsclasses::TWorkflowBlockEditor inherited;
	
public:
	virtual void __fastcall EditBlock(Wsclasses::TCustomWorkflowBlock* ABlock);
public:
	/* TObject.Create */ inline __fastcall TWorkflowSponsorBlockEditor(void) : Wsclasses::TWorkflowBlockEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWorkflowSponsorBlockEditor(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Wsblocks */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WSBLOCKS)
using namespace Wsblocks;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WsblocksHPP
