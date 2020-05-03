// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'LiveFlowChart.pas' rev: 28.00 (Windows)

#ifndef LiveflowchartHPP
#define LiveflowchartHPP

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
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <DiagramUtils.hpp>	// Pascal unit
#include <LiveDiagram.hpp>	// Pascal unit
#include <DgrClasses.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Liveflowchart
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TActionShape : unsigned char { asBox, asAlternate, asData, asDocument, asInput, asSubRoutine };

class DELPHICLASS TLiveActionBlock;
class PASCALIMPLEMENTATION TLiveActionBlock : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
private:
	TActionShape FActionShape;
	void __fastcall AdjustLinkpoints(void);
	void __fastcall SetFActionShape(const TActionShape Value);
	
protected:
	virtual void __fastcall UpdateLinkPoints(void);
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TLiveActionBlock(System::Classes::TComponent* AOwner);
	
__published:
	__property TActionShape ActionShape = {read=FActionShape, write=SetFActionShape, nodefault};
	__property OnExecute;
	__property OnExecuteEx;
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveActionBlock(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


enum DECLSPEC_DENUM TDecisionShape : unsigned char { dsBottomRight, dsRightBottom, dsLeftRight, dsRightLeft, dsBottomLeft, dsLeftBottom };

class DELPHICLASS TLiveDecisionBlock;
class PASCALIMPLEMENTATION TLiveDecisionBlock : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
private:
	Livediagram::TCustomLiveBlock* FNextTrue;
	Livediagram::TCustomLiveBlock* FNextFalse;
	TDecisionShape FDecision;
	void __fastcall SetDecision(const TDecisionShape Value);
	void __fastcall AdjustLinkPoints(void);
	void __fastcall AdjustSigns(void);
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual Livediagram::TCustomLiveBlock* __fastcall GetNext(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TLiveDecisionBlock(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Link(void);
	virtual void __fastcall ExecuteEx(Livediagram::TExecuteNodeInfo &ExecInfo);
	
__published:
	__property TDecisionShape DecisionShape = {read=FDecision, write=SetDecision, nodefault};
	__property OnExecute;
	__property OnExecuteEx;
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveDecisionBlock(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TCaseList;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TCaseList : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
private:
	System::Classes::TList* NumberList;
	Livediagram::TCustomLiveBlock* FElse;
	
public:
	__fastcall TCaseList(void);
	HIDESBASE int __fastcall Add(Livediagram::TCustomLiveBlock* aBlock, int aNumber);
	Livediagram::TCustomLiveBlock* __fastcall BlockOf(int Number);
	void __fastcall AddElse(Livediagram::TCustomLiveBlock* aBlock);
	virtual void __fastcall Clear(void);
	__fastcall virtual ~TCaseList(void);
};

#pragma pack(pop)

enum DECLSPEC_DENUM TCaseShape : unsigned char { csBottomRight, csBottomLeft };

class DELPHICLASS TLiveCaseBlock;
class PASCALIMPLEMENTATION TLiveCaseBlock : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
private:
	TCaseShape FCaseShape;
	TCaseList* FCaseList;
	Livediagram::TCustomLiveBlock* FNextElse;
	void __fastcall AdjustLinkPoints(void);
	void __fastcall AdjustSigns(void);
	void __fastcall SetCaseShape(const TCaseShape Value);
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual Livediagram::TCustomLiveBlock* __fastcall GetNext(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual void __fastcall DoExecute(int &Error, int &Decision);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TLiveCaseBlock(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLiveCaseBlock(void);
	virtual bool __fastcall Link(void);
	
__published:
	__property TCaseShape CaseShape = {read=FCaseShape, write=SetCaseShape, nodefault};
	__property OnExecute;
	__property OnExecuteEx;
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TCustomTerminalBlock;
class PASCALIMPLEMENTATION TCustomTerminalBlock : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall GetTranslatedBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
public:
	/* TCustomLiveBlock.Create */ inline __fastcall virtual TCustomTerminalBlock(System::Classes::TComponent* AOwner) : Livediagram::TCustomLiveBlock(AOwner) { }
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TCustomTerminalBlock(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetTranslatedBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetTranslatedBlockPath(APath); }
	
};


class DELPHICLASS TLiveStartBlock;
class PASCALIMPLEMENTATION TLiveStartBlock : public TCustomTerminalBlock
{
	typedef TCustomTerminalBlock inherited;
	
protected:
	virtual void __fastcall UpdateLinkPoints(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual Livediagram::TCustomLiveBlock* __fastcall GetNext(void);
	
public:
	__fastcall virtual TLiveStartBlock(System::Classes::TComponent* AOwner);
	
__published:
	__property OnExecute;
	__property OnExecuteEx;
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveStartBlock(void) { }
	
};


class DELPHICLASS TLiveEndBlock;
class PASCALIMPLEMENTATION TLiveEndBlock : public TCustomTerminalBlock
{
	typedef TCustomTerminalBlock inherited;
	
protected:
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual Livediagram::TCustomLiveBlock* __fastcall GetNext(void);
	virtual void __fastcall DoExecute(int &Error, int &Decision);
	
public:
	__fastcall virtual TLiveEndBlock(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Link(void);
	
__published:
	__property OnExecute;
	__property OnExecuteEx;
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveEndBlock(void) { }
	
};


class DELPHICLASS TLiveErrorHandler;
class PASCALIMPLEMENTATION TLiveErrorHandler : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual Livediagram::TCustomLiveBlock* __fastcall GetNext(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TLiveErrorHandler(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Link(void);
	
__published:
	__property OnExecute;
	__property OnExecuteEx;
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveErrorHandler(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


class DELPHICLASS TLiveHeader;
class PASCALIMPLEMENTATION TLiveHeader : public Livediagram::TCustomLiveBlock
{
	typedef Livediagram::TCustomLiveBlock inherited;
	
protected:
	virtual Diagramutils::TDotArray __fastcall BlockPolygon(void);
	virtual void __fastcall DrawShape(const Atdiagram::TDiagramDrawInfo &AInfo, const Atdiagram::TDiagramDrawBlockInfo &ABlockInfo);
	virtual void __fastcall UpdateLinkPoints(void);
	virtual bool __fastcall AcceptLink(Atdiagram::TCustomDiagramLine* ALink, int LinkIndex, Livediagram::TLinkDirection Direction);
	virtual void __fastcall GetBlockPath(Dgrclasses::TDgrGraphicsPath* APath, Dgrclasses::TDgrBlockDrawer* ADrawer)/* overload */;
	
public:
	__fastcall virtual TLiveHeader(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Link(void);
public:
	/* TCustomLiveBlock.Destroy */ inline __fastcall virtual ~TLiveHeader(void) { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetBlockPath _DEPRECATED_ATTRIBUTE0 (Dgrgdipobj::TGPGraphicsPath* APath){ Atdiagram::TCustomDiagramBlock::GetBlockPath(APath); }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Register(void);
}	/* namespace Liveflowchart */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_LIVEFLOWCHART)
using namespace Liveflowchart;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LiveflowchartHPP
