unit wsADO;

{$I wsdefs.inc}

interface
uses SysUtils, Classes, Dialogs,
  {$IFDEF DELPHI6_LVL} Variants, {$ENDIF}
  wsDB, DB, ADODB;

type
  TWorkflowADODB = class(TCustomWorkflowDB)
  private
    FConnection: TADOConnection;
    procedure SetConnection(const Value: TADOConnection);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    function DoCreateQuery(SQL: string): TDataset; override;
    procedure DoExecuteQuery(Dataset: TDataset); override;
    procedure DoAssignSQLParams(Dataset: TDataset; AParams: TParams); override;
    function BlobFieldToString(AField: TField): string; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Connection: TADOConnection read FConnection write SetConnection; 
  end;

procedure Register;

implementation
uses wsRes;

function Max(A, B: Integer): Integer;
begin
  if A > B then
    Result := A
  else
    Result := B;
end;

{ TWorkflowADODB }

constructor TWorkflowADODB.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  DestroyQueries := true;
end;

function TWorkflowADODB.BlobFieldToString(AField: TField): string;
var
  BlobField: TBlobField;
  Stream: TMemoryStream;
  s: string;
begin
  if AField is TBlobField then
  begin
    BlobField := TBlobField(AField);
    Stream := TMemoryStream.Create;
    try
      BlobField.SaveToStream(Stream);
      Stream.Position := 0;
      {$IFDEF DELPHI2007_LVL}
      s := WideCharLenToString(PWideChar(Stream.Memory), Stream.Size div 2);
      {$ELSE}
      SetString(s, PChar(Stream.Memory), Stream.Size);
      {$ENDIF}
    finally
      Stream.Free;
    end;
  end
  else
    s := AField.AsString;

  Result := s;
end;

procedure TWorkflowADODB.DoExecuteQuery(Dataset: TDataset);
begin
  TADOQuery(Dataset).ExecSQL;
end;

function TWorkflowADODB.DoCreateQuery(SQL: string): TDataset;
var
  Q: TADOQuery;
begin
  Q := TADOQuery.Create(nil);
  Q.Connection := FConnection;
  Q.Parameters.Clear;
  Q.SQL.Text := SQL;
  result := Q;
end;

procedure TWorkflowADODB.DoAssignSQLParams(Dataset: TDataset; AParams: TParams);
var
  Q: TADOQuery;
  c: integer;
  AParam: TParam;
begin
  Q := TADOQuery(Dataset);
  Q.Parameters.ParseSQL(Q.SQL.Text, true);

  //Q.Parameters.Assign(Params);
  for c := 0 to Q.Parameters.Count - 1 do
  begin
    AParam := AParams.FindParam(Q.Parameters[c].Name);
    if AParam = nil then
    begin
      wsDBError(Format(_str(SErrorParamNotFound),
        [Q.Parameters[c].Name]));
    end;

    Q.Parameters[c].DataType := AParam.DataType;
    Q.Parameters[c].Direction := pdInput;
    Q.Parameters[c].Value := AParam.Value;
    if Q.Parameters[c].DataType in [ftString] then
      Q.Parameters[c].Size := Max(1, Length(VarToSTr(Q.Parameters[c].Value)));
  end;
end;

procedure TWorkflowADODB.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  if (Operation = opRemove) and (AComponent = FConnection) then
    FConnection := nil;
  inherited Notification(AComponent, Operation);
end;

procedure TWorkflowADODB.SetConnection(const Value: TADOConnection);
begin
  if (FConnection <> Value) then
  begin
    FConnection := Value;
    if Value <> nil then
      Value.FreeNotification(Self);
  end;
end;

procedure Register;
begin
  RegisterComponents('Workflow Studio', [TWorkflowADODB]);
end;

end.
