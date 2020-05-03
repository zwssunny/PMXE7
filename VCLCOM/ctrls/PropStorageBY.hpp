// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'PropStorageBY.pas' rev: 6.00

#ifndef PropStorageBYHPP
#define PropStorageBYHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <TypInfo.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <PropFilerBY.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Propstorageby
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPropStorageManagerBY;
class DELPHICLASS TPropStorageBY;
class PASCALIMPLEMENTATION TPropStorageManagerBY : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FWriteAsText;
	
protected:
	__property bool WriteAsText = {read=FWriteAsText, write=FWriteAsText, default=1};
	
public:
	__fastcall virtual TPropStorageManagerBY(Classes::TComponent* AOwner);
	virtual void __fastcall ReadProperties(TPropStorageBY* PropStorage);
	virtual void __fastcall ReadPropertiesStream(Classes::TStream* Stream, TPropStorageBY* PropStorage);
	virtual void __fastcall WriteProperties(TPropStorageBY* PropStorage);
	virtual void __fastcall WritePropertiesStream(TPropStorageBY* PropStorage, Classes::TStream* Stream);
	virtual void __fastcall WritePropertiesText(TPropStorageBY* PropStorage, AnsiString Text);
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TPropStorageManagerBY(void) { }
	#pragma option pop
	
};


class DELPHICLASS TIniPropStorageManBY;
class PASCALIMPLEMENTATION TIniPropStorageManBY : public TPropStorageManagerBY 
{
	typedef TPropStorageManagerBY inherited;
	
private:
	AnsiString FIniFileName;
	
public:
	virtual void __fastcall ReadProperties(TPropStorageBY* PropStorage);
	virtual void __fastcall WritePropertiesStream(TPropStorageBY* PropStorage, Classes::TStream* Stream);
	virtual void __fastcall WritePropertiesText(TPropStorageBY* PropStorage, AnsiString Text);
	
__published:
	__property AnsiString IniFileName = {read=FIniFileName, write=FIniFileName};
	__property WriteAsText  = {default=1};
public:
	#pragma option push -w-inl
	/* TPropStorageManagerBY.Create */ inline __fastcall virtual TIniPropStorageManBY(Classes::TComponent* AOwner) : TPropStorageManagerBY(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TIniPropStorageManBY(void) { }
	#pragma option pop
	
};


class DELPHICLASS TRegPropStorageManBY;
class PASCALIMPLEMENTATION TRegPropStorageManBY : public TPropStorageManagerBY 
{
	typedef TPropStorageManagerBY inherited;
	
private:
	HKEY FKey;
	AnsiString FPath;
	
public:
	__fastcall virtual TRegPropStorageManBY(Classes::TComponent* AOwner);
	__fastcall virtual ~TRegPropStorageManBY(void);
	virtual void __fastcall ReadProperties(TPropStorageBY* PropStorage);
	virtual void __fastcall WritePropertiesStream(TPropStorageBY* PropStorage, Classes::TStream* Stream);
	virtual void __fastcall WritePropertiesText(TPropStorageBY* PropStorage, AnsiString Text);
	
__published:
	__property HKEY Key = {read=FKey, write=FKey, default=-2147483647};
	__property AnsiString Path = {read=FPath, write=FPath};
	__property WriteAsText  = {default=1};
};


typedef void __fastcall (__closure *TWriteCustomPropsEventBY)(System::TObject* Sender, Propfilerby::TPropWriterBY* Writer);

typedef void __fastcall (__closure *TReadPropEventBY)(System::TObject* Sender, Propfilerby::TPropReaderBY* Reader, AnsiString PropName, bool &Processed);

class DELPHICLASS TPropertyNamesBY;
class PASCALIMPLEMENTATION TPropertyNamesBY : public Classes::TStringList 
{
	typedef Classes::TStringList inherited;
	
private:
	Classes::TComponent* FRoot;
	void __fastcall SetRoot(const Classes::TComponent* Value);
	
protected:
	virtual int __fastcall CompareStrings(const AnsiString S1, const AnsiString S2);
	bool __fastcall CheckPropertyPath(AnsiString Path);
	bool __fastcall CheckObjectPropertyPath(System::TObject* Instance, AnsiString PropPath);
	void __fastcall CheckPropertyNames(void);
	
public:
	virtual int __fastcall Add(const AnsiString S);
	__property Classes::TComponent* Root = {read=FRoot, write=SetRoot};
public:
	#pragma option push -w-inl
	/* TStringList.Destroy */ inline __fastcall virtual ~TPropertyNamesBY(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPropertyNamesBY(void) : Classes::TStringList() { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TPropStorageBY : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	bool FActive;
	Classes::TNotifyEvent FAfterLoadProps;
	Classes::TNotifyEvent FAfterSaveProps;
	Classes::TNotifyEvent FBeforeLoadProps;
	Classes::TNotifyEvent FBeforeSaveProps;
	bool FDestroying;
	TReadPropEventBY FOnReadProp;
	TWriteCustomPropsEventBY FOnWriteCustomProps;
	Classes::TNotifyEvent FOnSavePlacement;
	bool FSaved;
	Forms::TCloseQueryEvent FSaveFormCloseQuery;
	Classes::TNotifyEvent FSaveFormDestroy;
	Classes::TNotifyEvent FSaveFormShow;
	AnsiString FSection;
	TPropStorageManagerBY* FStorageManager;
	TPropertyNamesBY* FStoredProps;
	Forms::TForm* __fastcall GetForm(void);
	AnsiString __fastcall GetSection();
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall RestoreEvents(void);
	void __fastcall SetEvents(void);
	void __fastcall SetSection(const AnsiString Value);
	void __fastcall SetStorageManager(const TPropStorageManagerBY* Value);
	void __fastcall SetStoredProps(const TPropertyNamesBY* Value);
	
protected:
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall Save(void);
	__property Forms::TForm* Form = {read=GetForm};
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall ReadProp(Propfilerby::TPropReaderBY* Reader, AnsiString PropName, bool &Processed);
	void __fastcall WriteCustomProps(Propfilerby::TPropWriterBY* Writer);
	
public:
	__fastcall virtual TPropStorageBY(Classes::TComponent* AOwner);
	__fastcall virtual ~TPropStorageBY(void);
	void __fastcall LoadProperties(void);
	void __fastcall ReadPropValues(Classes::TStream* Stream);
	void __fastcall SaveProperties(void);
	void __fastcall WritePropValues(Classes::TStream* Stream);
	
__published:
	__property bool Active = {read=FActive, write=FActive, default=1};
	__property AnsiString Section = {read=GetSection, write=SetSection};
	__property TPropStorageManagerBY* StorageManager = {read=FStorageManager, write=SetStorageManager};
	__property TPropertyNamesBY* StoredProps = {read=FStoredProps, write=SetStoredProps};
	__property Classes::TNotifyEvent AfterLoadProps = {read=FAfterLoadProps, write=FAfterLoadProps};
	__property Classes::TNotifyEvent AfterSaveProps = {read=FAfterSaveProps, write=FAfterSaveProps};
	__property Classes::TNotifyEvent BeforeLoadProps = {read=FBeforeLoadProps, write=FBeforeLoadProps};
	__property Classes::TNotifyEvent BeforeSaveProps = {read=FBeforeSaveProps, write=FBeforeSaveProps};
	__property TWriteCustomPropsEventBY OnWriteCustomProps = {read=FOnWriteCustomProps, write=FOnWriteCustomProps};
	__property TReadPropEventBY OnReadProp = {read=FOnReadProp, write=FOnReadProp};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall GetDefinePropertyList(Classes::TPersistent* AObject, Classes::TStrings* sl);
extern PACKAGE TPropStorageManagerBY* __fastcall DefaultPropStorageManager(void);
extern PACKAGE TPropStorageManagerBY* __fastcall SetDefaultPropStorageManager(TPropStorageManagerBY* NewStorageManager);
extern PACKAGE bool __fastcall RegistryKeyToIdent(int RootKey, AnsiString &Ident);
extern PACKAGE bool __fastcall IdentToRegistryKey(const AnsiString Ident, int &RootKey);
extern PACKAGE void __fastcall GetRegistryKeyValues(Classes::TGetStrProc Proc);

}	/* namespace Propstorageby */
using namespace Propstorageby;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// PropStorageBY
