// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DiagramActns.pas' rev: 28.00 (Windows)

#ifndef DiagramactnsHPP
#define DiagramactnsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <Vcl.ActnList.hpp>	// Pascal unit
#include <atDiagram.hpp>	// Pascal unit
#include <DiagramGradient.hpp>	// Pascal unit
#include <DiagramShadow.hpp>	// Pascal unit
#include <Vcl.Graphics.hpp>	// Pascal unit
#include <System.Actions.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Diagramactns
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDiagramAction;
class PASCALIMPLEMENTATION TDiagramAction : public Vcl::Actnlist::TAction
{
	typedef Vcl::Actnlist::TAction inherited;
	
private:
	Atdiagram::TatDiagram* FDiagram;
	void __fastcall SetDiagram(Atdiagram::TatDiagram* Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
__published:
	__property Atdiagram::TatDiagram* Diagram = {read=FDiagram, write=SetDiagram};
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramAction(System::Classes::TComponent* AOwner) : Vcl::Actnlist::TAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramAction(void) { }
	
};


class DELPHICLASS TDiagramDelete;
class PASCALIMPLEMENTATION TDiagramDelete : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramDelete(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramDelete(void) { }
	
};


class DELPHICLASS TDiagramEditText;
class PASCALIMPLEMENTATION TDiagramEditText : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramEditText(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramEditText(void) { }
	
};


class DELPHICLASS TDiagramSelectAll;
class PASCALIMPLEMENTATION TDiagramSelectAll : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramSelectAll(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramSelectAll(void) { }
	
};


enum DECLSPEC_DENUM TKeepInsertingMode : unsigned char { kmNever, kmAlways, kmOnShiftPressed, kmLinesOnly };

class DELPHICLASS TDiagramInsertBlock;
class PASCALIMPLEMENTATION TDiagramInsertBlock : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
private:
	System::UnicodeString FDControlID;
	TKeepInsertingMode FKeepInsertingMode;
	
public:
	__fastcall virtual TDiagramInsertBlock(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
	
__published:
	__property System::UnicodeString DControlID = {read=FDControlID, write=FDControlID};
	__property TKeepInsertingMode KeepInsertingMode = {read=FKeepInsertingMode, write=FKeepInsertingMode, nodefault};
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramInsertBlock(void) { }
	
};


class DELPHICLASS TDiagramCancelInsert;
class PASCALIMPLEMENTATION TDiagramCancelInsert : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramCancelInsert(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramCancelInsert(void) { }
	
};


class DELPHICLASS TDiagramCut;
class PASCALIMPLEMENTATION TDiagramCut : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramCut(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramCut(void) { }
	
};


class DELPHICLASS TDiagramCopy;
class PASCALIMPLEMENTATION TDiagramCopy : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramCopy(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramCopy(void) { }
	
};


class DELPHICLASS TDiagramPaste;
class PASCALIMPLEMENTATION TDiagramPaste : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramPaste(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramPaste(void) { }
	
};


class DELPHICLASS TDiagramUndo;
class PASCALIMPLEMENTATION TDiagramUndo : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	__fastcall virtual TDiagramUndo(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramUndo(void) { }
	
};


class DELPHICLASS TDiagramViewTopRuler;
class PASCALIMPLEMENTATION TDiagramViewTopRuler : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramViewTopRuler(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramViewTopRuler(void) { }
	
};


class DELPHICLASS TDiagramViewLeftRuler;
class PASCALIMPLEMENTATION TDiagramViewLeftRuler : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramViewLeftRuler(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramViewLeftRuler(void) { }
	
};


class DELPHICLASS TDiagramGrid;
class PASCALIMPLEMENTATION TDiagramGrid : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramGrid(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramGrid(void) { }
	
};


class DELPHICLASS TDiagramShapeColor;
class PASCALIMPLEMENTATION TDiagramShapeColor : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramShapeColor(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramShapeColor(void) { }
	
};


class DELPHICLASS TDiagramGradientSetting;
class PASCALIMPLEMENTATION TDiagramGradientSetting : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramGradientSetting(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramGradientSetting(void) { }
	
};


class DELPHICLASS TDiagramLineColor;
class PASCALIMPLEMENTATION TDiagramLineColor : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramLineColor(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramLineColor(void) { }
	
};


class DELPHICLASS TDiagramBlockPicture;
class PASCALIMPLEMENTATION TDiagramBlockPicture : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramBlockPicture(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramBlockPicture(void) { }
	
};


class DELPHICLASS TDiagramBringToFront;
class PASCALIMPLEMENTATION TDiagramBringToFront : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramBringToFront(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramBringToFront(void) { }
	
};


class DELPHICLASS TDiagramControlFont;
class PASCALIMPLEMENTATION TDiagramControlFont : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramControlFont(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramControlFont(void) { }
	
};


class DELPHICLASS TDiagramSendToBack;
class PASCALIMPLEMENTATION TDiagramSendToBack : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramSendToBack(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramSendToBack(void) { }
	
};


class DELPHICLASS TDiagramUndoAction;
class PASCALIMPLEMENTATION TDiagramUndoAction : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramUndoAction(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramUndoAction(void) { }
	
};


class DELPHICLASS TDiagramRedoAction;
class PASCALIMPLEMENTATION TDiagramRedoAction : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramRedoAction(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramRedoAction(void) { }
	
};


class DELPHICLASS TDiagramArrowShape;
class PASCALIMPLEMENTATION TDiagramArrowShape : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
private:
	Atdiagram::TArrowShape FShape;
	bool FSource;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
	
__published:
	__property Atdiagram::TArrowShape Shape = {read=FShape, write=FShape, nodefault};
	__property bool Source = {read=FSource, write=FSource, nodefault};
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramArrowShape(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramArrowShape(void) { }
	
};


class DELPHICLASS TDiagramSetZoom;
class PASCALIMPLEMENTATION TDiagramSetZoom : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
private:
	int FZoom;
	void __fastcall SetZoom(const int Value);
	
public:
	__fastcall virtual TDiagramSetZoom(System::Classes::TComponent* AOwner);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
	
__published:
	__property int Zoom = {read=FZoom, write=SetZoom, nodefault};
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramSetZoom(void) { }
	
};


class DELPHICLASS TDiagramShadow;
class PASCALIMPLEMENTATION TDiagramShadow : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramShadow(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramShadow(void) { }
	
};


class DELPHICLASS TDiagramConnectionId;
class PASCALIMPLEMENTATION TDiagramConnectionId : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
private:
	System::UnicodeString FConnectionLineID;
	
public:
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
	
__published:
	__property System::UnicodeString ConnectionLineID = {read=FConnectionLineID, write=FConnectionLineID};
public:
	/* TAction.Create */ inline __fastcall virtual TDiagramConnectionId(System::Classes::TComponent* AOwner) : TDiagramAction(AOwner) { }
	
public:
	/* TCustomAction.Destroy */ inline __fastcall virtual ~TDiagramConnectionId(void) { }
	
};


enum DECLSPEC_DENUM TBlocksAlignment : unsigned char { baLeft, baRight, baTop, baBottom, baHorzCenter, baVertCenter, baSameWidth, baSameHeight, baSameSize, baSameSpaceHorz, baSameSpaceVert, baIncHorzSpace, baIncrVertSpace, baDecHorzSpace, baDecVertSpace };

class DELPHICLASS TBlockList;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TBlockList : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
public:
	Atdiagram::TCustomDiagramBlock* operator[](int index) { return Blocks[index]; }
	
private:
	Atdiagram::TCustomDiagramBlock* __fastcall GetBlock(int index);
	Atdiagram::TCustomDiagramBlock* __fastcall GetFirst(void);
	
public:
	__property Atdiagram::TCustomDiagramBlock* Blocks[int index] = {read=GetBlock/*, default*/};
	__property Atdiagram::TCustomDiagramBlock* Champion = {read=GetFirst};
public:
	/* TList.Destroy */ inline __fastcall virtual ~TBlockList(void) { }
	
public:
	/* TObject.Create */ inline __fastcall TBlockList(void) : System::Classes::TList() { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TBlockSort : unsigned char { bsNone, bsByX, bsByY };

class DELPHICLASS TDiagramAlign;
class PASCALIMPLEMENTATION TDiagramAlign : public TDiagramAction
{
	typedef TDiagramAction inherited;
	
private:
	TBlocksAlignment FBlockAlignment;
	TDiagramAlign* FDefaultAlignment;
	TBlockList* FList;
	void __fastcall GetSelection(void);
	void __fastcall SortByX(void);
	void __fastcall SortByY(void);
	void __fastcall AlignLeft(void);
	void __fastcall AlignRight(void);
	void __fastcall AlignTop(void);
	void __fastcall AlignBottom(void);
	void __fastcall AlignHorzCenter(void);
	void __fastcall AlignVertCenter(void);
	void __fastcall SameWidth(void);
	void __fastcall SameHeight(void);
	void __fastcall SameSize(void);
	void __fastcall SameSpaceHorz(void);
	void __fastcall SameSpaceVert(void);
	void __fastcall IncHorzSpace(void);
	void __fastcall IncVertSpace(void);
	void __fastcall DecHorzSpace(void);
	void __fastcall DecVertSpace(void);
	void __fastcall SetBlockAlignment(const TBlocksAlignment Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TDiagramAlign(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDiagramAlign(void);
	DYNAMIC bool __fastcall Execute(void);
	virtual bool __fastcall Update(void);
	
__published:
	__property TDiagramAlign* DefaultAlignment = {read=FDefaultAlignment, write=FDefaultAlignment};
	__property TBlocksAlignment BlockAlignment = {read=FBlockAlignment, write=SetBlockAlignment, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Diagramactns */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DIAGRAMACTNS)
using namespace Diagramactns;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DiagramactnsHPP
