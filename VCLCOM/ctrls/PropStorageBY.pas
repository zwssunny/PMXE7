
{$I BYLIB.Inc}
//{$I BYLIBClx.Inc}

unit PropStorageBY;

interface

uses
{$IFDEF BY_LIB_VCL}
  Windows, Forms, Controls, Registry, PropFilerBY, Dialogs,
{$ELSE}
  QForms, QControls, QPropFilerBY,
{$ENDIF}
  SysUtils, Classes, IniFiles, TypInfo;

type

  TPropStorageBY = class;
  TPropertyNamesBY = class;

{ TPropStorageManagerBY }

  TPropStorageManagerBY = class(TComponent)
  private
    FWriteAsText: Boolean;
  protected
    property WriteAsText: Boolean read FWriteAsText write FWriteAsText default True;
  public
    constructor Create(AOwner: TComponent); override;
    procedure ReadProperties(PropStorage: TPropStorageBY); virtual;
    procedure ReadPropertiesStream(Stream: TStream; PropStorage: TPropStorageBY); virtual;
    procedure WriteProperties(PropStorage: TPropStorageBY); virtual;
    procedure WritePropertiesStream(PropStorage: TPropStorageBY; Stream: TStream); virtual;
    procedure WritePropertiesText(PropStorage: TPropStorageBY; Text: String); virtual;
  end;

{ TIniPropStorageManBY }

  TIniPropStorageManBY = class(TPropStorageManagerBY)
  private
    FIniFileName: String;
  public
    procedure ReadProperties(PropStorage: TPropStorageBY); override;
    procedure WritePropertiesStream(PropStorage: TPropStorageBY; Stream: TStream); override;
    procedure WritePropertiesText(PropStorage: TPropStorageBY; Text: String); override;
  published
    property IniFileName: String read FIniFileName write FIniFileName;
    property WriteAsText;
  end;

{$IFDEF BY_LIB_VCL}

{ TRegPropStorageManBY }

  TRegPropStorageManBY = class(TPropStorageManagerBY)
  private
    FKey: HKEY;
    FPath: String;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure ReadProperties(PropStorage: TPropStorageBY); override;
    procedure WritePropertiesStream(PropStorage: TPropStorageBY; Stream: TStream); override;
    procedure WritePropertiesText(PropStorage: TPropStorageBY; Text: String); override;
  published
    property Key: HKEY read FKey write FKey default HKEY_CURRENT_USER;
    property Path: String read FPath write FPath;
    property WriteAsText;
  end;

{$ENDIF}

{ TPropStorageBY }

  TWriteCustomPropsEventBY = procedure(Sender: TObject; Writer: TPropWriterBY) of object;
  TReadPropEventBY = procedure(Sender: TObject; Reader: TPropReaderBY;
    PropName: String; var Processed: Boolean) of object;

  TPropStorageBY = class(TComponent)
  private
    FActive: Boolean;
    FAfterLoadProps: TNotifyEvent;
    FAfterSaveProps: TNotifyEvent;
    FBeforeLoadProps: TNotifyEvent;
    FBeforeSaveProps: TNotifyEvent;
    FDestroying: Boolean;
    FOnReadProp: TReadPropEventBY;
    FOnWriteCustomProps: TWriteCustomPropsEventBY;
    FOnSavePlacement: TNotifyEvent;
    FSaved: Boolean;
    FSaveFormCloseQuery: TCloseQueryEvent;
    FSaveFormDestroy: TNotifyEvent;
    FSaveFormShow: TNotifyEvent;
    FSection: String;
    FStorageManager: TPropStorageManagerBY;
    FStoredProps: TPropertyNamesBY;
    function GetForm: TForm;
    function GetSection: String;
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure RestoreEvents;
    procedure SetEvents;
    procedure SetSection(const Value: String);
    procedure SetStorageManager(const Value: TPropStorageManagerBY);
    procedure SetStoredProps(const Value: TPropertyNamesBY);
  protected
    procedure Loaded; override;
    procedure Save; dynamic;
    property Form: TForm read GetForm;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure ReadProp(Reader: TPropReaderBY; PropName: String; var Processed: Boolean);
    procedure WriteCustomProps(Writer: TPropWriterBY);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure LoadProperties;
    procedure ReadPropValues(Stream: TStream);
    procedure SaveProperties;
    procedure WritePropValues(Stream: TStream);
  published
    property Active: Boolean read FActive write FActive default True;
    property Section: String read GetSection write SetSection;
    property StorageManager: TPropStorageManagerBY read FStorageManager write SetStorageManager;
    property StoredProps: TPropertyNamesBY read FStoredProps write SetStoredProps;
    property AfterLoadProps: TNotifyEvent read FAfterLoadProps write FAfterLoadProps;
    property AfterSaveProps: TNotifyEvent read FAfterSaveProps write FAfterSaveProps;
    property BeforeLoadProps: TNotifyEvent read FBeforeLoadProps write FBeforeLoadProps;
    property BeforeSaveProps: TNotifyEvent read FBeforeSaveProps write FBeforeSaveProps;
    property OnWriteCustomProps: TWriteCustomPropsEventBY read FOnWriteCustomProps write FOnWriteCustomProps;
    property OnReadProp: TReadPropEventBY read FOnReadProp write FOnReadProp;
  end;

{ TPropertyNamesBY }

  TPropertyNamesBY = class(TStringList)
  private
    FRoot: TComponent;
    procedure SetRoot(const Value: TComponent);
  protected
    function CompareStrings(const S1, S2: string): Integer; {$IFDEF BY_LIB_6} override; {$ENDIF}
    function CheckPropertyPath(Path: String): Boolean;
    function CheckObjectPropertyPath(Instance: TObject; PropPath: String): Boolean;
    procedure CheckPropertyNames;
  public
    function Add(const S: string): Integer; override;
    property Root: TComponent read FRoot write SetRoot;
  end;

  procedure GetDefinePropertyList(AObject: TPersistent; sl: TStrings);

  function DefaultPropStorageManager: TPropStorageManagerBY;
  function SetDefaultPropStorageManager(NewStorageManager: TPropStorageManagerBY): TPropStorageManagerBY;

{$IFDEF BY_LIB_VCL}

function RegistryKeyToIdent(RootKey: Longint; var Ident: string): Boolean;
function IdentToRegistryKey(const Ident: string; var RootKey: Longint): Boolean;
procedure GetRegistryKeyValues(Proc: TGetStrProc);

{$ENDIF}

implementation

function GetDefaultSection(Component: TComponent): String;
var
  F: TCustomForm;
  Owner: TComponent;
begin
  if Component <> nil then
  begin
    if Component is TCustomForm then
      Result := Component.ClassName
    else
    begin
      Result := Component.Name;
      if Component is TControl then
      begin
        F := GetParentForm(TControl(Component));
        if F <> nil then
          Result := F.ClassName + Result
        else
        begin
          if TControl(Component).Parent <> nil then
            Result := TControl(Component).Parent.Name + Result;
        end;
      end else
      begin
        Owner := Component.Owner;
        if Owner is TForm then
          Result := Format('%s.%s', [Owner.ClassName, Result]);
      end;
    end;
  end
  else Result := '';
end;

function GetDefaultIniName: string;
begin
  Result := ExtractFileName(ChangeFileExt(Application.ExeName, '.INI'));
end;

function GetDefaultRegKey: string;
begin
  if Application.Title <> '' then
    Result := Application.Title
  else Result := ExtractFileName(ChangeFileExt(Application.ExeName, ''));
  Result := 'Software\' + Result;
end;

{$IFNDEF BY_LIB_5}

type
  TStreamOriginalFormat = (sofUnknown, sofBinary, sofText);

const
  FilerSignature: array[1..4] of Char = 'TPF0';

function TestStreamFormat(Stream: TStream): TStreamOriginalFormat;
var
  Pos: Integer;
  Signature: Integer;
begin
  Pos := Stream.Position;
  Signature := 0;
  Stream.Read(Signature, sizeof(Signature));
  Stream.Position := Pos;
  if (Byte(Signature) = $FF) or (Signature = Integer(FilerSignature)) then
    Result := sofBinary
    // text format may begin with "object", "inherited", or whitespace
  else if Char(Signature) in ['o','O','i','I',' ',#13,#11,#9] then
    Result := sofText
  else
    Result := sofUnknown;
end;

{$ENDIF}

type
  TDefinePropertyFiler = class(TFiler)
  private
    fsl: TStrings;
  public
    procedure FlushBuffer; override;
    procedure DefineProperty(const Name: String; ReadData: TReaderProc; WriteData: TWriterProc; HasData: Boolean); override;
    procedure DefineBinaryProperty(const Name: String; ReadData, WriteData: TStreamProc; HasData: Boolean); override;
    procedure GetDefinedObjectPropertyNames(AObject: TPersistent; sl: TStrings);
  end;

  TPersistentCrack = class(TPersistent) end;

procedure GetDefinePropertyList(AObject: TPersistent; sl: TStrings);
var
  dpf: TDefinePropertyFiler;
begin
  dpf := TDefinePropertyFiler.Create(nil,0);
  dpf.GetDefinedObjectPropertyNames(AObject, sl);
  dpf.Free;
end;

{ TDefinePropertyFiler }

procedure TDefinePropertyFiler.DefineBinaryProperty(const Name: String;
  ReadData, WriteData: TStreamProc; HasData: Boolean);
begin
  fsl.Add(Name);
end;

procedure TDefinePropertyFiler.DefineProperty(const Name: String;
  ReadData: TReaderProc; WriteData: TWriterProc; HasData: Boolean);
begin
  fsl.Add(Name);
end;

procedure TDefinePropertyFiler.FlushBuffer;
begin

end;

procedure TDefinePropertyFiler.GetDefinedObjectPropertyNames(
  AObject: TPersistent; sl: TStrings);
begin
  fsl := sl;
  TPersistentCrack(AObject).DefineProperties(Self);
end;

var
  FDefaultStorageManager: TPropStorageManagerBY;

function DefaultPropStorageManager: TPropStorageManagerBY;
begin
  Result := FDefaultStorageManager;
end;

function SetDefaultPropStorageManager(NewStorageManager: TPropStorageManagerBY): TPropStorageManagerBY;
begin
  Result := FDefaultStorageManager;
  FDefaultStorageManager := NewStorageManager;
end;

{ TPropStorageManagerBY }

constructor TPropStorageManagerBY.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FWriteAsText := True;
end;

procedure TPropStorageManagerBY.WriteProperties(PropStorage: TPropStorageBY);
var
  ss: TStringStream;
  st: TMemoryStream;
begin
  st := nil;
  ss := nil;
  try
    st := TMemoryStream.Create;
    PropStorage.WritePropValues(st);
    st.Position := 0;
    if WriteAsText then
    begin
      ss := TStringStream.Create('');
      ObjectBinaryToText(st, ss);
      WritePropertiesText(PropStorage, ss.DataString);
    end else
      WritePropertiesStream(PropStorage, st);
  finally
    st.Free;
    ss.Free;
  end;
end;

procedure TPropStorageManagerBY.WritePropertiesText(PropStorage: TPropStorageBY; Text: String);
begin
end;

procedure TPropStorageManagerBY.WritePropertiesStream(PropStorage: TPropStorageBY; Stream: TStream);
begin
end;

procedure TPropStorageManagerBY.ReadProperties(PropStorage: TPropStorageBY);
begin
end;

procedure TPropStorageManagerBY.ReadPropertiesStream(Stream: TStream; PropStorage: TPropStorageBY);
var
  ms: TMemoryStream;
begin
  ms := nil;
  if TestStreamFormat(Stream) = sofUnknown then
    raise Exception.Create('Invalid stream format.');
  try
    if TestStreamFormat(Stream) = sofText then
    begin
      ms := TMemoryStream.Create;
      ObjectTextToBinary(Stream, ms);
      ms.Position := 0;
      Stream := ms;
    end;
    PropStorage.ReadPropValues(Stream);
  finally
    ms.Free;
  end;  
end;

{ TIniPropStorageManBY }

procedure TIniPropStorageManBY.ReadProperties(PropStorage: TPropStorageBY);
var
  ss: TStringStream;
  sl: TStrings;
  ini: TCustomIniFile;
  i: Integer;
  Buffer: String;
begin
  ss := nil;
  sl := nil;
  ini := nil;
  try
    ini := TIniFile.Create(IniFileName);  //TMemIniFile does't found file (if it not in current dir)
    sl := TStringList.Create;

    if not ini.SectionExists(PropStorage.Section) then
      Exit;
    ini.ReadSectionValues(PropStorage.Section, sl);
    for i := 0 to sl.Count - 1 do
      sl.Strings[i] := sl.Values['Line' + IntToStr(i)];


    ss := TStringStream.Create(sl[0]);

    if TestStreamFormat(ss) <> sofText then
    begin
      ss.Seek(0, soFromEnd);
      for i := 1 to sl.Count - 1 do
        ss.WriteString(sl[i]);
      ss.Position := 0;

      SetString(Buffer, nil, ss.Size div 2);
      HexToBin(PChar(ss.DataString), PChar(Buffer), ss.Size);
      ss.Size := 0;
      ss.WriteString(Buffer);
      ss.Position := 0;
    end else
    begin
      ss.Position := 0;
      ss.WriteString(sl.Text);
      ss.Position := 0;
    end;

    ReadPropertiesStream(ss, PropStorage);

  finally
    ss.Free;
    sl.Free;
    ini.Free;
  end;
end;

procedure TIniPropStorageManBY.WritePropertiesStream(PropStorage: TPropStorageBY; Stream: TStream);
var
  ini: TCustomIniFile;
  Buffer: PChar;
  Text, Line: String;
  i, Pos: Integer;
begin
  ini := nil;
  Buffer := nil;
  try
    ini := TIniFile.Create(IniFileName);
    GetMem(Buffer, Stream.Size);
    SetString(Text, nil, Stream.Size*2);
    Stream.ReadBuffer(Buffer^, Stream.Size);
    BinToHex(Buffer, PChar(Text), Stream.Size);
    i := 0;
    Pos := 1;
    while Pos <= Length(Text) do
    begin
      Line := Copy(Text, Pos, 80);
      ini.WriteString(PropStorage.Section, 'Line' + IntToStr(i), '''' + Line + '''');
      Inc(Pos, 80);
      Inc(i);
    end;

    while ini.ValueExists(PropStorage.Section, 'Line' + IntToStr(i)) do
    begin
      ini.DeleteKey(PropStorage.Section, 'Line' + IntToStr(i));
      Inc(i);
    end;
  finally
    FreeMem(Buffer);
    ini.Free;
  end;
end;

procedure TIniPropStorageManBY.WritePropertiesText(PropStorage: TPropStorageBY; Text: String);
var
  sl: TStrings;
  ini: TCustomIniFile;
  i: Integer;
begin
  sl := nil;
  ini := nil;
  try
    sl := TStringList.Create;
    sl.Text := Text;

    ini := TIniFile.Create(IniFileName);

    for i := 0 to sl.Count - 1 do
      ini.WriteString(PropStorage.Section, 'Line' + IntToStr(i), '''' + sl[i] + '''');

    i := sl.Count;
    while ini.ValueExists(PropStorage.Section, 'Line' + IntToStr(i)) do
    begin
      ini.DeleteKey(PropStorage.Section, 'Line' + IntToStr(i));
      Inc(i);
    end;
  finally
    sl.Free;
    ini.Free;
  end;
end;

{$IFNDEF BY_LIB_CLX}

{ TRegPropStorageManBY }

const
  RegistryKeys: array[0..6] of TIdentMapEntry = (
    (Value: Integer(HKEY_CLASSES_ROOT); Name: 'HKEY_CLASSES_ROOT'),
    (Value: Integer(HKEY_CURRENT_USER); Name: 'HKEY_CURRENT_USER'),
    (Value: Integer(HKEY_LOCAL_MACHINE); Name: 'HKEY_LOCAL_MACHINE'),
    (Value: Integer(HKEY_USERS); Name: 'HKEY_USERS'),
    (Value: Integer(HKEY_PERFORMANCE_DATA); Name: 'HKEY_PERFORMANCE_DATA'),
    (Value: Integer(HKEY_CURRENT_CONFIG); Name: 'HKEY_CURRENT_CONFIG'),
    (Value: Integer(HKEY_DYN_DATA); Name: 'HKEY_DYN_DATA'));

function RegistryKeyToIdent(RootKey: Longint; var Ident: string): Boolean;
begin
  Result := IntToIdent(RootKey, Ident, RegistryKeys);
end;

function IdentToRegistryKey(const Ident: string; var RootKey: Longint): Boolean;
begin
  Result := IdentToInt(Ident, RootKey, RegistryKeys);
end;

procedure GetRegistryKeyValues(Proc: TGetStrProc);
var
  I: Integer;
begin
  for I := Low(RegistryKeys) to High(RegistryKeys) do Proc(RegistryKeys[I].Name);
end;

constructor TRegPropStorageManBY.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FKey := HKEY_CURRENT_USER;
end;

destructor TRegPropStorageManBY.Destroy;
begin
  inherited Destroy;
end;

procedure TRegPropStorageManBY.ReadProperties(PropStorage: TPropStorageBY);
var
  ss: TStringStream;
  reg: TRegistry;
  IsPresent: Boolean;
  Buffer: String;
begin
  ss := nil;
  reg := nil;
  try

    reg := TRegistry.Create;

    reg.RootKey := Key;
    if Path = ''
      then IsPresent := reg.OpenKey(GetDefaultRegKey, False)
      else IsPresent := reg.OpenKey(Path, False);
    if not IsPresent then Exit;

    if not reg.ValueExists(PropStorage.Section) then Exit;

    if reg.GetDataType(PropStorage.Section) = rdBinary then
    begin
      SetString(Buffer, nil, reg.GetDataSize(PropStorage.Section));
      reg.ReadBinaryData(PropStorage.Section, PChar(Buffer)^, Length(Buffer));
    end else
      Buffer := reg.ReadString(PropStorage.Section);

    ss := TStringStream.Create(Buffer);
    ss.Position := 0;

    ReadPropertiesStream(ss, PropStorage);

  finally
    ss.Free;
    reg.Free;
  end;
end;

procedure TRegPropStorageManBY.WritePropertiesStream(PropStorage: TPropStorageBY; Stream: TStream);
var
  reg: TRegistry;
  Buffer: String;
begin
  reg := nil;
  try
    reg := TRegistry.Create;
    reg.RootKey := Key;

    if Path = ''
      then reg.OpenKey(GetDefaultRegKey, True)
      else reg.OpenKey(Path, True);

    SetString(Buffer, nil, Stream.Size - Stream.Position);
    Stream.ReadBuffer(PChar(Buffer)^, Stream.Size - Stream.Position);
    reg.WriteBinaryData(PropStorage.Section, PChar(Buffer)^, Length(Buffer));
  finally
    reg.Free;
  end;
end;

procedure TRegPropStorageManBY.WritePropertiesText(PropStorage: TPropStorageBY; Text: String);
var
  reg: TRegistry;
begin
  reg := nil;
  try
    reg := TRegistry.Create;
    reg.RootKey := Key;

    if Path = ''
      then reg.OpenKey(GetDefaultRegKey, True)
      else reg.OpenKey(Path, True);

    reg.WriteString(PropStorage.Section, Text);

  finally
    reg.Free;
  end;
end;

{$ENDIF}

{ TPropStorageBY }

constructor TPropStorageBY.Create(AOwner: TComponent);

{$ifdef eval}
  {$INCLUDE eval}
{$else}
begin
{$endif}

  inherited Create(AOwner);
  FSection := '';
  FActive := True;
  FStoredProps := TPropertyNamesBY.Create;
  FStoredProps.Root := AOwner;
end;

destructor TPropStorageBY.Destroy;
begin
  if not (csDesigning in ComponentState) then
    RestoreEvents;
  FStoredProps.Free;
  inherited Destroy;
end;

procedure TPropStorageBY.Loaded;
var
  Loading: Boolean;
begin
  Loading := csLoading in ComponentState;
  inherited Loaded;
  if not (csDesigning in ComponentState) then
  begin
    if Loading then SetEvents;
  end;
end;

function TPropStorageBY.GetForm: TForm;
begin
  if Owner is TCustomForm
    then Result := TForm(Owner as TCustomForm)
    else Result := nil;
end;

procedure TPropStorageBY.SetEvents;
begin
  if Owner is TCustomForm then
  begin
    with TForm(Form) do
    begin
      FSaveFormShow := OnShow;
      OnShow := FormShow;
      FSaveFormCloseQuery := OnCloseQuery;
      OnCloseQuery := FormCloseQuery;
      FSaveFormDestroy := OnDestroy;
      OnDestroy := FormDestroy;
    end;
  end;
end;

procedure TPropStorageBY.RestoreEvents;
begin
  if (Owner <> nil) and (Owner is TCustomForm) then
    with TForm(Form) do
    begin
      OnShow := FSaveFormShow;
      OnCloseQuery := FSaveFormCloseQuery;
      OnDestroy := FSaveFormDestroy;
    end;
end;

procedure TPropStorageBY.FormShow(Sender: TObject);
begin
  if Active then
    try
      LoadProperties;
    except
      if IsRaiseReadErrorBY then
        Application.HandleException(Self);
    end;
  if Assigned(FSaveFormShow) then
    FSaveFormShow(Sender);
end;

procedure TPropStorageBY.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
  if Assigned(FSaveFormCloseQuery) then
    FSaveFormCloseQuery(Sender, CanClose);
  if CanClose and Active and (Owner is TCustomForm) and Form.HandleAllocated then
    try
      SaveProperties;
    except
      Application.HandleException(Self);
    end;
end;

procedure TPropStorageBY.FormDestroy(Sender: TObject);
begin
  if Active and not FSaved then
  begin
    FDestroying := True;
    try
      SaveProperties;
    except
      Application.HandleException(Self);
    end;
    FDestroying := False;
  end;
  if Assigned(FSaveFormDestroy) then
    FSaveFormDestroy(Sender);
end;

function TPropStorageBY.GetSection: String;
begin
  Result := FSection;
  if (Result = '') and not (csDesigning in ComponentState) then
    Result := GetDefaultSection(Owner);
end;

procedure TPropStorageBY.SetSection(const Value: String);
begin
  FSection := Value;
end;

procedure TPropStorageBY.Save;
begin
  if Assigned(FOnSavePlacement) then FOnSavePlacement(Self);
end;

procedure TPropStorageBY.SetStorageManager(const Value: TPropStorageManagerBY);
begin
  if FStorageManager <> Value then
  begin
    FStorageManager := Value;
    if Value <> nil then Value.FreeNotification(Self);
  end;
end;

procedure TPropStorageBY.SetStoredProps(const Value: TPropertyNamesBY);
begin
  FStoredProps.Assign(Value);
end;

procedure TPropStorageBY.WritePropValues(Stream: TStream);
var
  pw: TPropWriterBY;
begin
  pw := TPropWriterBY.Create(Stream, 1024);
  pw.OnWriteOwnerProps := WriteCustomProps;
  try
    pw.WriteOwnerProperties(Owner, StoredProps);
  finally
    pw.Free;
  end;
end;

procedure TPropStorageBY.ReadPropValues(Stream: TStream);
var
  pr: TPropReaderBY;
begin
  pr := TPropReaderBY.Create(Stream, 1024);
  pr.OnReadOwnerProp := ReadProp;
  try
    pr.ReadOwnerProperties(Owner);
  finally
    pr.Free;
  end;
end;

procedure TPropStorageBY.LoadProperties;
begin
  if Assigned(BeforeLoadProps) then
    BeforeLoadProps(Self);
  FSaved := False;
  if StorageManager <> nil then
    StorageManager.ReadProperties(Self)
  else if DefaultPropStorageManager <> nil then
    DefaultPropStorageManager.ReadProperties(Self);
  if Assigned(AfterLoadProps) then
    AfterLoadProps(Self);
end;

procedure TPropStorageBY.SaveProperties;
begin
  if Assigned(BeforeSaveProps) then
    BeforeSaveProps(Self);
  if StorageManager <> nil then
  begin
    StorageManager.WriteProperties(Self);
    FSaved := True;
  end else if DefaultPropStorageManager <> nil then
  begin
    DefaultPropStorageManager.WriteProperties(Self);
    FSaved := True;
  end;
  if Assigned(AfterSaveProps) then
    AfterSaveProps(Self);
end;

procedure TPropStorageBY.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) and (AComponent = FStorageManager) then
    StorageManager := nil;
end;

procedure TPropStorageBY.WriteCustomProps(Writer: TPropWriterBY);
begin
  if Assigned(OnWriteCustomProps) then
    OnWriteCustomProps(Self, Writer);
end;

procedure TPropStorageBY.ReadProp(Reader: TPropReaderBY; PropName: String;
  var Processed: Boolean);
begin
  if Assigned(OnReadProp) then
    OnReadProp(Self, Reader, PropName, Processed);
end;

{ TPropertyNamesBY }

function TPropertyNamesBY.CheckPropertyPath(Path: String): Boolean;
var
  Token: String;
  CurObject: TComponent;
begin
  CurObject := Root;
  Result := False;
  Token := GetNextPointSeparatedToken(Path);
  while True do
  begin
    if Token = '' then
      raise Exception.Create('Invalide property path: "' + Path + '"');
    if UpperCase(Token) = '<P>' then
    begin
      Result := CheckObjectPropertyPath(CurObject, Copy(Path, Length('<P>') + 2, Length(Path)));
      Exit;
    end;
    if (CurObject is TComponent)
      then CurObject := FindChildComponent(CurObject, Root, Token, True)
      else CurObject := nil;
    if CurObject = nil then Exit;
    System.Delete(Path, 1, Length(Token) + 1);
    Token := GetNextPointSeparatedToken(Path);
  end;
end;

function TPropertyNamesBY.CheckObjectPropertyPath(Instance: TObject; PropPath: String): Boolean;
var
  PropInfo: PPropInfo;
  PropName: String;
  dpl: TStringList;
  ci: TCollectionItem;
  c: TCollection;
  i: Integer;
  ciList: TList;
  InterceptorClass: TReadPropertyInterceptorClass;

  function IsSpecCollectionPropName(PropName: String): Boolean;
  begin
    Result := (Instance is TCollection) and
              ( (AnsiUpperCase(PropName) = AnsiUpperCase('<ForAllItems>'))
                or
                (AnsiUpperCase(Copy(PropName, 1, 5)) = AnsiUpperCase('<Item') )
              );
  end;

begin
  ciList := TList.Create;
  try
    Result := False;
    while True do
    begin
      PropName := GetNextPointSeparatedToken(PropPath);
      System.Delete(PropPath, 1, Length(PropName) + 1);

      if IsSpecCollectionPropName(PropName) then
      begin
        c := TCollection(Instance);
        if AnsiUpperCase(PropName) = AnsiUpperCase('<ForAllItems>') then
        begin
          ci := c.ItemClass.Create(nil);
          Instance := ci;
          ciList.Add(ci);
        end else if (Copy(PropName, 1, 5) = '<Item') then
        begin
          i := StrToInt(Copy(Copy(PropName, 1, Length(PropName)-1), 6, 100));
          if i < c.Count then
            Instance := c.Items[i];
        end;
        if PropPath = '' then
        begin
          Result := True;
          Exit;
        end;
        Continue;
      end;

      InterceptorClass := GetInterceptorForTarget(Instance.ClassType);
      if InterceptorClass <> nil then
      begin
        PropInfo := GetPropInfo(InterceptorClass.ClassInfo, PropName);
        if PropInfo = nil then
          PropInfo := GetPropInfo(Instance.ClassInfo, PropName);
      end else
        PropInfo := GetPropInfo(Instance.ClassInfo, PropName);
      if PropInfo = nil then
        if Instance is TPersistent then
        begin
          dpl := TStringList.Create;
          try
{$IFDEF BY_LIB_6}
            dpl.CaseSensitive := False;
{$ENDIF}
            GetDefinePropertyList(TPersistent(Instance), dpl);
            if dpl.IndexOf(PropName) = -1 then
              Exit;
          finally
            dpl.Free;
          end;
        end;
      if PropPath = '' then
      begin
        Result := True;
        Exit;
      end;
      if PropInfo^.PropType^.Kind = tkClass then
      begin
        Instance := TObject(GetOrdProp(Instance, PropInfo));
        if Instance = nil then
          Exit;
      end;
    end;
  finally
    for i := 0 to ciList.Count - 1 do
      TCollectionItem(ciList[i]).Free;
    ciList.Free;
  end;
end;

procedure TPropertyNamesBY.CheckPropertyNames;
var
  i: Integer;
begin
  for i := Count - 1 downto 0 do
    if not CheckPropertyPath(Strings[i]) then
      Delete(i);
end;

function TPropertyNamesBY.CompareStrings(const S1, S2: string): Integer;
  function CompareStr(S1, S2: string): Integer;
  var
    Token1, Token2: String;
  begin
    Result := 0;
    if (S1 = '') and (S2 = '') then Exit;
    Token1 := GetNextPointSeparatedToken(S1);
    Token2 := GetNextPointSeparatedToken(S2);
 { TODO : Compare collection ____Item[i]: i as number }
    if (UpperCase(Token1) = '<P>') and (UpperCase(Token2) <> '<P>') then
      Result := -1
    else if (UpperCase(Token1) <> '<P>') and (UpperCase(Token2) = '<P>') then
      Result := 1
    else if (Copy(Token1, 1, 1) = '<') and
       (Copy(Token2, 1, 1) <> '<')
    then
      Result := 1
    else if (Copy(Token2, 1, 1) = '<') and
            (Copy(Token1, 1, 1) <> '<')
    then
      Result := -1
    else
    begin
      Result := AnsiCompareText(Token1, Token2);
      if Result = 0 then
      begin
        System.Delete(S1, 1, Length(Token1)+1);
        System.Delete(S2, 1, Length(Token1)+1);
        Result := CompareStr(S1, S2);
      end;
    end;
  end;
begin
  Result := CompareStr(S1, S2);
end;

procedure TPropertyNamesBY.SetRoot(const Value: TComponent);
begin
  FRoot := Value;
  CheckPropertyNames;
end;

function TPropertyNamesBY.Add(const S: string): Integer;
var
  i: Integer;
begin
  Result := -1;
  if (Root <> nil) and not (csLoading in Root.ComponentState) and not CheckPropertyPath(S)
  then
    Exit;
  for i := 0 to Count - 1 do
    if CompareStrings(Strings[i], S) = 0 then
      Exit
    else if CompareStrings(Strings[i], S) > 0 then
    begin
      Insert(i, S);
      Result := i;
      Exit;
    end;
  inherited Add(S);
end;

initialization
{$IFDEF BY_LIB_VCL}
  RegisterIntegerConsts(TypeInfo(HKEY), IdentToRegistryKey, RegistryKeyToIdent);
{$ENDIF}
finalization
  FDefaultStorageManager.Free;
  FDefaultStorageManager := nil;
end.