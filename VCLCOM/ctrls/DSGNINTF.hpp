// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DsgnIntf.pas' rev: 5.00

#ifndef DsgnIntfHPP
#define DsgnIntfHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <TypInfo.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Dsgnintf
{
//-- type declarations -------------------------------------------------------
__interface IEventInfos;
typedef System::DelphiInterface<IEventInfos> _di_IEventInfos;
__interface INTERFACE_UUID("{11667FF0-7590-11D1-9FBC-0020AF3D82DA}") IEventInfos  : public IUnknown 
	
{
	
public:
	virtual int __fastcall GetCount(void) = 0 ;
	virtual AnsiString __fastcall GetEventValue(int Index) = 0 ;
	virtual AnsiString __fastcall GetEventName(int Index) = 0 ;
	virtual void __fastcall ClearEvent(int Index) = 0 ;
	__property int Count = {read=GetCount};
};

__interface IPersistent;
typedef System::DelphiInterface<IPersistent> _di_IPersistent;
__interface INTERFACE_UUID("{82330133-65D1-11D1-9FBB-0020AF3D82DA}") IPersistent  : public IUnknown 
	
{
	
public:
	virtual void __fastcall DestroyObject(void) = 0 ;
	virtual bool __fastcall Equals(const _di_IPersistent Other) = 0 ;
	virtual AnsiString __fastcall GetClassname(void) = 0 ;
	virtual _di_IEventInfos __fastcall GetEventInfos(void) = 0 ;
	virtual AnsiString __fastcall GetNamePath(void) = 0 ;
	virtual _di_IPersistent __fastcall GetOwner(void) = 0 ;
	virtual bool __fastcall InheritsFrom(const AnsiString Classname) = 0 ;
	virtual bool __fastcall IsComponent(void) = 0 ;
	virtual bool __fastcall IsControl(void) = 0 ;
	virtual bool __fastcall IsWinControl(void) = 0 ;
	__property AnsiString Classname = {read=GetClassname};
	__property _di_IPersistent Owner = {read=GetOwner};
	__property AnsiString NamePath = {read=GetNamePath};
	__property _di_IEventInfos EventInfos = {read=GetEventInfos};
};

__interface IComponent;
typedef System::DelphiInterface<IComponent> _di_IComponent;
__interface INTERFACE_UUID("{B2F6D681-5098-11D1-9FB5-0020AF3D82DA}") IComponent  : public IPersistent 
	
{
	
public:
	virtual _di_IComponent __fastcall FindComponent(const AnsiString Name) = 0 ;
	virtual int __fastcall GetComponentCount(void) = 0 ;
	virtual _di_IComponent __fastcall GetComponents(int Index) = 0 ;
	virtual Classes::TComponentState __fastcall GetComponentState(void) = 0 ;
	virtual Classes::TComponentStyle __fastcall GetComponentStyle(void) = 0 ;
	virtual Windows::TSmallPoint __fastcall GetDesignInfo(void) = 0 ;
	virtual Windows::TPoint __fastcall GetDesignOffset(void) = 0 ;
	virtual Windows::TPoint __fastcall GetDesignSize(void) = 0 ;
	virtual AnsiString __fastcall GetName(void) = 0 ;
	HIDESBASE virtual _di_IComponent __fastcall GetOwner(void) = 0 ;
	virtual _di_IComponent __fastcall GetParent(void) = 0 ;
	virtual void __fastcall SetDesignInfo(const Windows::TSmallPoint Point) = 0 ;
	virtual void __fastcall SetDesignOffset(const Windows::TPoint &Point) = 0 ;
	virtual void __fastcall SetDesignSize(const Windows::TPoint &Point) = 0 ;
	virtual void __fastcall SetName(const AnsiString Value) = 0 ;
	__property int ComponentCount = {read=GetComponentCount};
	__property _di_IComponent Components[int Index] = {read=GetComponents};
	__property Classes::TComponentState ComponentState = {read=GetComponentState};
	__property Classes::TComponentStyle ComponentStyle = {read=GetComponentStyle};
	__property Windows::TSmallPoint DesignInfo = {read=GetDesignInfo, write=SetDesignInfo};
	__property Windows::TPoint DesignOffset = {read=GetDesignOffset, write=SetDesignOffset};
	__property Windows::TPoint DesignSize = {read=GetDesignSize, write=SetDesignSize};
	__property AnsiString Name = {read=GetName, write=SetName};
	__property _di_IComponent Owner = {read=GetOwner};
	__property _di_IComponent Parent = {read=GetParent};
};

__interface IImplementation;
typedef System::DelphiInterface<IImplementation> _di_IImplementation;
__interface INTERFACE_UUID("{F9D448F2-50BC-11D1-9FB5-0020AF3D82DA}") IImplementation  : public IUnknown 
	
{
	
public:
	virtual System::TObject* __fastcall GetInstance(void) = 0 ;
};

__interface IDesignerSelections;
typedef System::DelphiInterface<IDesignerSelections> _di_IDesignerSelections;
__interface INTERFACE_UUID("{82330134-65D1-11D1-9FBB-0020AF3D82DA}") IDesignerSelections  : public IUnknown 
	
{
	
public:
	virtual int __fastcall Add(const _di_IPersistent Item) = 0 ;
	virtual bool __fastcall Equals(const _di_IDesignerSelections List) = 0 ;
	virtual _di_IPersistent __fastcall Get(int Index) = 0 ;
	virtual int __fastcall GetCount(void) = 0 ;
	__property int Count = {read=GetCount};
	__property _di_IPersistent Items[int Index] = {read=Get/*, default*/};
};

__interface IComponentList;
typedef System::DelphiInterface<IComponentList> _di_IComponentList;
class DELPHICLASS TComponentList;
__interface INTERFACE_UUID("{8ED8AD16-A241-11D1-AA94-00C04FB17A72}") IComponentList  : public IUnknown 
	
{
	
public:
	virtual TComponentList* __fastcall GetComponentList(void) = 0 ;
};

class PASCALIMPLEMENTATION TComponentList : public System::TInterfacedObject 
{
	typedef System::TInterfacedObject inherited;
	
private:
	Classes::TList* FList;
	int __fastcall Intf_Add(const _di_IPersistent Item);
	bool __fastcall Intf_Equals(const _di_IDesignerSelections List);
	_di_IPersistent __fastcall Intf_Get(int Index);
	Classes::TPersistent* __fastcall Get(int Index);
	int __fastcall GetCount(void);
	TComponentList* __fastcall GetComponentList(void);
	
public:
	__fastcall TComponentList(void);
	__fastcall virtual ~TComponentList(void);
	int __fastcall Add(Classes::TPersistent* Item);
	bool __fastcall Equals(TComponentList* List);
	__property int Count = {read=GetCount, nodefault};
	__property Classes::TPersistent* Items[int Index] = {read=Get/*, default*/};
private:
	void *__IDesignerSelections;	/* Dsgnintf::IDesignerSelections [Get=Intf_Get, Equals=Intf_Equals, Add=Intf_Add
		] */
	void *__IComponentList;	/* Dsgnintf::IComponentList */
	
public:
	operator IComponentList*(void) { return (IComponentList*)&__IComponentList; }
	operator IDesignerSelections*(void) { return (IDesignerSelections*)&__IDesignerSelections; }
	
};


__interface IFormDesigner;
typedef System::DelphiInterface<IFormDesigner> _di_IFormDesigner;
__interface INTERFACE_UUID("{ABBE7255-5495-11D1-9FB5-0020AF3D82DA}") IFormDesigner  : public IDesigner 
	
{
	
public:
	virtual Sysutils::TMethod __fastcall CreateMethod(const AnsiString Name, Typinfo::PTypeData TypeData
		) = 0 ;
	virtual AnsiString __fastcall GetMethodName(const Sysutils::TMethod &Method) = 0 ;
	virtual void __fastcall GetMethods(Typinfo::PTypeData TypeData, Classes::TGetStrProc Proc) = 0 ;
	virtual AnsiString __fastcall GetPrivateDirectory(void) = 0 ;
	virtual void __fastcall GetSelections(const _di_IDesignerSelections List) = 0 ;
	virtual bool __fastcall MethodExists(const AnsiString Name) = 0 ;
	virtual void __fastcall RenameMethod(const AnsiString CurName, const AnsiString NewName) = 0 ;
	virtual void __fastcall SelectComponent(Classes::TPersistent* Instance) = 0 ;
	virtual void __fastcall SetSelections(const _di_IDesignerSelections List) = 0 ;
	virtual void __fastcall ShowMethod(const AnsiString Name) = 0 ;
	HIDESBASE virtual AnsiString __fastcall UniqueName(const AnsiString BaseName) = 0 ;
	virtual void __fastcall GetComponentNames(Typinfo::PTypeData TypeData, Classes::TGetStrProc Proc) = 0 
		;
	virtual Classes::TComponent* __fastcall GetComponent(const AnsiString Name) = 0 ;
	virtual AnsiString __fastcall GetComponentName(Classes::TComponent* Component) = 0 ;
	virtual Classes::TPersistent* __fastcall GetObject(const AnsiString Name) = 0 ;
	virtual AnsiString __fastcall GetObjectName(Classes::TPersistent* Instance) = 0 ;
	virtual void __fastcall GetObjectNames(Typinfo::PTypeData TypeData, Classes::TGetStrProc Proc) = 0 
		;
	virtual bool __fastcall MethodFromAncestor(const Sysutils::TMethod &Method) = 0 ;
	virtual Classes::TComponent* __fastcall CreateComponent(TMetaClass* ComponentClass, Classes::TComponent* 
		Parent, int Left, int Top, int Width, int Height) = 0 ;
	virtual bool __fastcall IsComponentLinkable(Classes::TComponent* Component) = 0 ;
	virtual void __fastcall MakeComponentLinkable(Classes::TComponent* Component) = 0 ;
	HIDESBASE virtual Classes::TComponent* __fastcall GetRoot(void) = 0 ;
	virtual void __fastcall Revert(Classes::TPersistent* Instance, Typinfo::PPropInfo PropInfo) = 0 ;
	virtual bool __fastcall GetIsDormant(void) = 0 ;
	virtual bool __fastcall HasInterface(void) = 0 ;
	virtual bool __fastcall HasInterfaceMember(const AnsiString Name) = 0 ;
	virtual void __fastcall AddToInterface(int InvKind, const AnsiString Name, Word VT, const AnsiString 
		TypeInfo) = 0 ;
	virtual void __fastcall GetProjectModules(Classes::TGetModuleProc Proc) = 0 ;
	virtual _di_IFormDesigner __fastcall GetAncestorDesigner(void) = 0 ;
	virtual bool __fastcall IsSourceReadOnly(void) = 0 ;
	__property bool IsDormant = {read=GetIsDormant};
	__property _di_IFormDesigner AncestorDesigner = {read=GetAncestorDesigner};
};

#pragma option push -b-
enum TPropertyAttribute { paValueList, paSubProperties, paDialog, paMultiSelect, paAutoUpdate, paSortList, 
	paReadOnly, paRevertable };
#pragma option pop

typedef Set<TPropertyAttribute, paValueList, paRevertable>  TPropertyAttributes;

struct TInstProp
{
	Classes::TPersistent* Instance;
	Typinfo::TPropInfo *PropInfo;
} ;

typedef TInstProp TInstPropList[1024];

typedef TInstProp *PInstPropList;

class DELPHICLASS TPropertyEditor;
typedef void __fastcall (__closure *TGetPropEditProc)(TPropertyEditor* Prop);

class PASCALIMPLEMENTATION TPropertyEditor : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	_di_IFormDesigner FDesigner;
	TInstProp *FPropList;
	int FPropCount;
	AnsiString __fastcall GetPrivateDirectory(void);
	void __fastcall SetPropEntry(int Index, Classes::TPersistent* AInstance, Typinfo::PPropInfo APropInfo
		);
	
protected:
	__fastcall TPropertyEditor(const _di_IFormDesigner ADesigner, int APropCount);
	Typinfo::PPropInfo __fastcall GetPropInfo(void);
	Extended __fastcall GetFloatValue(void);
	Extended __fastcall GetFloatValueAt(int Index);
	Sysutils::TMethod __fastcall GetMethodValue(void);
	Sysutils::TMethod __fastcall GetMethodValueAt(int Index);
	int __fastcall GetOrdValue(void);
	int __fastcall GetOrdValueAt(int Index);
	AnsiString __fastcall GetStrValue(void);
	AnsiString __fastcall GetStrValueAt(int Index);
	Variant __fastcall GetVarValue(void);
	Variant __fastcall GetVarValueAt(int Index);
	void __fastcall Modified(void);
	void __fastcall SetFloatValue(Extended Value);
	void __fastcall SetMethodValue(const Sysutils::TMethod &Value);
	void __fastcall SetOrdValue(int Value);
	void __fastcall SetStrValue(const AnsiString Value);
	void __fastcall SetVarValue(const Variant &Value);
	
public:
	__fastcall virtual ~TPropertyEditor(void);
	virtual void __fastcall Activate(void);
	virtual bool __fastcall AllEqual(void);
	virtual bool __fastcall AutoFill(void);
	virtual void __fastcall Edit(void);
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	Classes::TPersistent* __fastcall GetComponent(int Index);
	virtual int __fastcall GetEditLimit(void);
	virtual AnsiString __fastcall GetName(void);
	virtual void __fastcall GetProperties(TGetPropEditProc Proc);
	Typinfo::PTypeInfo __fastcall GetPropType(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall Initialize(void);
	void __fastcall Revert(void);
	virtual void __fastcall SetValue(const AnsiString Value);
	bool __fastcall ValueAvailable(void);
	__property _di_IFormDesigner Designer = {read=FDesigner};
	__property AnsiString PrivateDirectory = {read=GetPrivateDirectory};
	__property int PropCount = {read=FPropCount, nodefault};
	__property AnsiString Value = {read=GetValue, write=SetValue};
};


typedef TMetaClass*TPropertyEditorClass;

class DELPHICLASS TOrdinalProperty;
class PASCALIMPLEMENTATION TOrdinalProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual bool __fastcall AllEqual(void);
	virtual int __fastcall GetEditLimit(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TOrdinalProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TOrdinalProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TIntegerProperty;
class PASCALIMPLEMENTATION TIntegerProperty : public TOrdinalProperty 
{
	typedef TOrdinalProperty inherited;
	
public:
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TIntegerProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TOrdinalProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TIntegerProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCharProperty;
class PASCALIMPLEMENTATION TCharProperty : public TOrdinalProperty 
{
	typedef TOrdinalProperty inherited;
	
public:
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TCharProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TOrdinalProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TCharProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEnumProperty;
class PASCALIMPLEMENTATION TEnumProperty : public TOrdinalProperty 
{
	typedef TOrdinalProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TEnumProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TOrdinalProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TEnumProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TBoolProperty;
class PASCALIMPLEMENTATION TBoolProperty : public TEnumProperty 
{
	typedef TEnumProperty inherited;
	
public:
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TBoolProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TEnumProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TBoolProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TFloatProperty;
class PASCALIMPLEMENTATION TFloatProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual bool __fastcall AllEqual(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TFloatProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TFloatProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TStringProperty;
class PASCALIMPLEMENTATION TStringProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual bool __fastcall AllEqual(void);
	virtual int __fastcall GetEditLimit(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TStringProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TStringProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TNestedProperty;
class PASCALIMPLEMENTATION TNestedProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	__fastcall virtual TNestedProperty(TPropertyEditor* Parent);
	__fastcall virtual ~TNestedProperty(void);
};


class DELPHICLASS TSetElementProperty;
class PASCALIMPLEMENTATION TSetElementProperty : public TNestedProperty 
{
	typedef TNestedProperty inherited;
	
private:
	int FElement;
	
protected:
	__fastcall TSetElementProperty(TPropertyEditor* Parent, int AElement);
	
public:
	virtual bool __fastcall AllEqual(void);
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetName(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
public:
	#pragma option push -w-inl
	/* TNestedProperty.Destroy */ inline __fastcall virtual ~TSetElementProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TSetProperty;
class PASCALIMPLEMENTATION TSetProperty : public TOrdinalProperty 
{
	typedef TOrdinalProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetProperties(TGetPropEditProc Proc);
	virtual AnsiString __fastcall GetValue(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TSetProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TOrdinalProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TSetProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TClassProperty;
class PASCALIMPLEMENTATION TClassProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetProperties(TGetPropEditProc Proc);
	virtual AnsiString __fastcall GetValue(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TClassProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TClassProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TMethodProperty;
class PASCALIMPLEMENTATION TMethodProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual bool __fastcall AllEqual(void);
	virtual void __fastcall Edit(void);
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual int __fastcall GetEditLimit(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString AValue);
	virtual AnsiString __fastcall GetFormMethodName(void);
	AnsiString __fastcall GetTrimmedEventName(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TMethodProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TMethodProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComponentProperty;
class PASCALIMPLEMENTATION TComponentProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual int __fastcall GetEditLimit(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TComponentProperty(const _di_IFormDesigner ADesigner
		, int APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TComponentProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComponentNameProperty;
class PASCALIMPLEMENTATION TComponentNameProperty : public TStringProperty 
{
	typedef TStringProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual int __fastcall GetEditLimit(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TComponentNameProperty(const _di_IFormDesigner ADesigner
		, int APropCount) : TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TComponentNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TFontNameProperty;
class PASCALIMPLEMENTATION TFontNameProperty : public TStringProperty 
{
	typedef TStringProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TFontNameProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TFontNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TFontCharsetProperty;
class PASCALIMPLEMENTATION TFontCharsetProperty : public TIntegerProperty 
{
	typedef TIntegerProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TFontCharsetProperty(const _di_IFormDesigner ADesigner
		, int APropCount) : TIntegerProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TFontCharsetProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TImeNameProperty;
class PASCALIMPLEMENTATION TImeNameProperty : public TStringProperty 
{
	typedef TStringProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TImeNameProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TImeNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TColorProperty;
class PASCALIMPLEMENTATION TColorProperty : public TIntegerProperty 
{
	typedef TIntegerProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TColorProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TIntegerProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TColorProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCursorProperty;
class PASCALIMPLEMENTATION TCursorProperty : public TIntegerProperty 
{
	typedef TIntegerProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TCursorProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TIntegerProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TCursorProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TFontProperty;
class PASCALIMPLEMENTATION TFontProperty : public TClassProperty 
{
	typedef TClassProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TFontProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TClassProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TFontProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TModalResultProperty;
class PASCALIMPLEMENTATION TModalResultProperty : public TIntegerProperty 
{
	typedef TIntegerProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TModalResultProperty(const _di_IFormDesigner ADesigner
		, int APropCount) : TIntegerProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TModalResultProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TShortCutProperty;
class PASCALIMPLEMENTATION TShortCutProperty : public TOrdinalProperty 
{
	typedef TOrdinalProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TShortCutProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TOrdinalProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TShortCutProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TMPFilenameProperty;
class PASCALIMPLEMENTATION TMPFilenameProperty : public TStringProperty 
{
	typedef TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TMPFilenameProperty(const _di_IFormDesigner ADesigner
		, int APropCount) : TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TMPFilenameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTabOrderProperty;
class PASCALIMPLEMENTATION TTabOrderProperty : public TIntegerProperty 
{
	typedef TIntegerProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TTabOrderProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TIntegerProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TTabOrderProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCaptionProperty;
class PASCALIMPLEMENTATION TCaptionProperty : public TStringProperty 
{
	typedef TStringProperty inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TCaptionProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TCaptionProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDateProperty;
class PASCALIMPLEMENTATION TDateProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TDateProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TDateProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTimeProperty;
class PASCALIMPLEMENTATION TTimeProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TTimeProperty(const _di_IFormDesigner ADesigner, int 
		APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TTimeProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDateTimeProperty;
class PASCALIMPLEMENTATION TDateTimeProperty : public TPropertyEditor 
{
	typedef TPropertyEditor inherited;
	
public:
	virtual TPropertyAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall TDateTimeProperty(const _di_IFormDesigner ADesigner, 
		int APropCount) : TPropertyEditor(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TDateTimeProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPropertyError;
class PASCALIMPLEMENTATION EPropertyError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPropertyError(const AnsiString Msg) : Sysutils::Exception(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPropertyError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPropertyError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPropertyError(int Ident, const System::TVarRec * Args
		, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPropertyError(const AnsiString Msg, int AHelpContext)
		 : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPropertyError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPropertyError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPropertyError(System::PResStringRec ResStringRec
		, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPropertyError(void) { }
	#pragma option pop
	
};


__interface IComponentEditor;
typedef System::DelphiInterface<IComponentEditor> _di_IComponentEditor;
__interface INTERFACE_UUID("{ABBE7252-5495-11D1-9FB5-0020AF3D82DA}") IComponentEditor  : public IUnknown 
	
{
	
public:
	virtual void __fastcall Edit(void) = 0 ;
	virtual void __fastcall ExecuteVerb(int Index) = 0 ;
	virtual _di_IComponent __fastcall GetIComponent(void) = 0 ;
	virtual _di_IFormDesigner __fastcall GetDesigner(void) = 0 ;
	virtual AnsiString __fastcall GetVerb(int Index) = 0 ;
	virtual int __fastcall GetVerbCount(void) = 0 ;
	virtual void __fastcall Copy(void) = 0 ;
};

class DELPHICLASS TComponentEditor;
class PASCALIMPLEMENTATION TComponentEditor : public System::TInterfacedObject 
{
	typedef System::TInterfacedObject inherited;
	
private:
	Classes::TComponent* FComponent;
	_di_IFormDesigner FDesigner;
	
public:
	__fastcall virtual TComponentEditor(Classes::TComponent* AComponent, _di_IFormDesigner ADesigner);
	virtual void __fastcall Edit(void);
	virtual void __fastcall ExecuteVerb(int Index);
	_di_IComponent __fastcall GetIComponent(void);
	_di_IFormDesigner __fastcall GetDesigner(void);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
	virtual void __fastcall Copy(void);
	__property Classes::TComponent* Component = {read=FComponent};
	__property _di_IFormDesigner Designer = {read=GetDesigner};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TComponentEditor(void) { }
	#pragma option pop
	
private:
	void *__IComponentEditor;	/* Dsgnintf::IComponentEditor */
	
public:
	operator IComponentEditor*(void) { return (IComponentEditor*)&__IComponentEditor; }
	
};


typedef TMetaClass*TComponentEditorClass;

__interface IDefaultEditor;
typedef System::DelphiInterface<IDefaultEditor> _di_IDefaultEditor;
__interface INTERFACE_UUID("{5484FAE1-5C60-11D1-9FB6-0020AF3D82DA}") IDefaultEditor  : public IComponentEditor 
	
{
	
};

class DELPHICLASS TDefaultEditor;
class PASCALIMPLEMENTATION TDefaultEditor : public TComponentEditor 
{
	typedef TComponentEditor inherited;
	
private:
	TPropertyEditor* FFirst;
	TPropertyEditor* FBest;
	bool FContinue;
	void __fastcall CheckEdit(TPropertyEditor* PropertyEditor);
	
protected:
	virtual void __fastcall EditProperty(TPropertyEditor* PropertyEditor, bool &Continue, bool &FreeEditor
		);
	
public:
	virtual void __fastcall Edit(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TDefaultEditor(Classes::TComponent* AComponent
		, _di_IFormDesigner ADesigner) : TComponentEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TDefaultEditor(void) { }
	#pragma option pop
	
private:
	void *__IDefaultEditor;	/* Dsgnintf::IDefaultEditor */
	
public:
	operator IDefaultEditor*(void) { return (IDefaultEditor*)&__IDefaultEditor; }
	
};


typedef void __fastcall (*TFreeCustomModulesProc)(int Group);

typedef TMetaClass* __fastcall (*TPropertyMapperFunc)(Classes::TPersistent* Obj, Typinfo::PPropInfo 
	PropInfo);

#pragma option push -b-
enum TCustomModuleAttribute { cmaVirtualSize };
#pragma option pop

typedef Set<TCustomModuleAttribute, cmaVirtualSize, cmaVirtualSize>  TCustomModuleAttributes;

class DELPHICLASS TCustomModule;
class PASCALIMPLEMENTATION TCustomModule : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	_di_IComponent FRoot;
	
public:
	__fastcall virtual TCustomModule(_di_IComponent ARoot);
	virtual void __fastcall ExecuteVerb(int Index);
	virtual TCustomModuleAttributes __fastcall GetAttributes(void);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
	virtual void __fastcall Saving(void);
	virtual void __fastcall ValidateComponent(_di_IComponent Component);
	__property _di_IComponent Root = {read=FRoot};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomModule(void) { }
	#pragma option pop
	
};


typedef TMetaClass*TCustomModuleClass;

typedef void __fastcall (*TRegisterCustomModuleProc)(int Group, TMetaClass* ComponentBaseClass, TMetaClass* 
	CustomModuleClass);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE _di_IPersistent __fastcall (*MakeIPersistentProc)(Classes::TPersistent* Instance);
extern PACKAGE _di_IComponent __fastcall (*MakeIComponentProc)(Classes::TComponent* Instance);
extern PACKAGE TFreeCustomModulesProc FreeCustomModulesProc;
extern PACKAGE TRegisterCustomModuleProc RegisterCustomModuleProc;
extern PACKAGE Byte MaxIdentLength;
extern PACKAGE void __fastcall RegisterPropertyEditor(Typinfo::PTypeInfo PropertyType, TMetaClass* ComponentClass
	, const AnsiString PropertyName, TMetaClass* EditorClass);
extern PACKAGE void __fastcall RegisterPropertyMapper(TPropertyMapperFunc Mapper);
extern PACKAGE void __fastcall GetComponentProperties(TComponentList* Components, Typinfo::TTypeKinds 
	Filter, _di_IFormDesigner Designer, TGetPropEditProc Proc);
extern PACKAGE void __fastcall RegisterComponentEditor(TMetaClass* ComponentClass, TMetaClass* ComponentEditor
	);
extern PACKAGE TComponentEditor* __fastcall GetComponentEditor(Classes::TComponent* Component, _di_IFormDesigner 
	Designer);
extern PACKAGE int __fastcall NewEditorGroup(void);
extern PACKAGE void __fastcall FreeEditorGroup(int Group);
extern PACKAGE void __fastcall RegisterCustomModule(TMetaClass* ComponentBaseClass, TMetaClass* CustomModuleClass
	);
extern PACKAGE _di_IPersistent __fastcall MakeIPersistent(Classes::TPersistent* Instance);
extern PACKAGE Classes::TPersistent* __fastcall ExtractPersistent(const _di_IPersistent Intf);
extern PACKAGE Classes::TPersistent* __fastcall TryExtractPersistent(const _di_IPersistent Intf);
extern PACKAGE _di_IComponent __fastcall MakeIComponent(Classes::TComponent* Instance);
extern PACKAGE Classes::TComponent* __fastcall ExtractComponent(const _di_IComponent Intf);
extern PACKAGE Classes::TComponent* __fastcall TryExtractComponent(const _di_IComponent Intf);
extern PACKAGE _di_IDesignerSelections __fastcall CreateSelectionList(void);

}	/* namespace Dsgnintf */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dsgnintf;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DsgnIntf
