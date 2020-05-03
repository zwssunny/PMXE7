unit wspFIB;

{$I wsdefs.inc}

interface
uses SysUtils, Classes, Dialogs,
  {$IFDEF DELPHI6_LVL} Variants, {$ENDIF}
  wsDB,
  FIBDatabase, pFIBDatabase, Db, FIBDataSet, pFIBDataSet,
  FIBQuery, pFIBQuery;

type
  TWorkflowpFIBDB = class(TCustomWorkflowDB)
  private
    FDatabase: TpFIBDatabase;
    procedure SetDatabase(const Value: TpFIBDatabase);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    function DoCreateQuery(SQL: string): TDataset; override;
    procedure DoExecuteQuery(Dataset: TDataset); override;
    procedure DoAssignSQLParams(Dataset: TDataset; AParams: TParams); override;
    function BlobFieldToString(AField: TField): string; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Database: TpFIBDatabase read FDatabase write SetDatabase;
  end;

procedure Register;

implementation
uses wsRes;

{ TWorkflowpFIBDB }

constructor TWorkflowpFIBDB.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  DestroyQueries := true;
end;

function TWorkflowpFIBDB.BlobFieldToString(AField: TField): string;
var
  BlobField: TBlobField;
  StrStream: TStringStream;
  c: integer;
  IsOleStr: boolean;
begin
  if AField is TBlobField then
  begin
    BlobField := TBlobField(AField);
    StrStream := TStringStream.Create('');
    try
      BlobField.SaveToStream(StrStream);
      StrStream.Position := 0;
      result := StrStream.ReadString(StrStream.Size);
    finally
      StrStream.Free;
    end;
  end else
    result := AField.AsString;

  {workaround to "tell" if the string is an Ole string}
  IsOleStr := true;
  c := 2;
  while c < length(result) do
  begin
    if result[c] <> chr(0) then
    begin
      IsOleStr := false;
      break;
    end;
    c := c + 2;
  end;

  {remove #0 characters}
  if IsOleStr then
  begin
    c := 2;
    while c < length(result) do
    begin
      Delete(result, c, 1);
      inc(c);
    end;
  end;
end;

procedure TWorkflowpFIBDB.DoExecuteQuery(Dataset: TDataset);
var
  Q: TpFIBQuery;
  DS: TpFIBDataset;
begin
  DS := TpFIBDataset(Dataset);
  Q := TpFIBQuery.Create(nil);
  try
    Q.Database := DS.Database;
    Q.SQL.Text := DS.SelectSQL.Text;
    Q.Params.AssignValues(DS.Params);
    if Q.Transaction = nil then
      Q.Transaction := TpFIBTransaction.Create(Q);
    Q.Transaction.StartTransaction;
    Q.ExecQuery;
    Q.Transaction.Commit;
  finally
    Q.Free;
  end;
end;

function TWorkflowpFIBDB.DoCreateQuery(SQL: string): TDataset;
var
  Q: TpFIBDataset;
begin                                              
  Q := TpFIBDataset.Create(nil);
  Q.Database := FDatabase;
  Q.SelectSQL.Text := SQL;
  result := Q;
end;

procedure TWorkflowpFIBDB.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  if (Operation = opRemove) and (AComponent = FDatabase) then
    FDatabase := nil;
  inherited Notification(AComponent, Operation);
end;

procedure TWorkflowpFIBDB.DoAssignSQLParams(Dataset: TDataset; AParams: TParams);
var
  Q: TpFIBDataset;
  c: integer;
  AParam: TParam;
begin
  Q := TpFIBDataset(Dataset);

  {Iterate through params and set the param in the FIBDataset}
  for c := 0 to Q.ParamCount - 1 do
  begin
    AParam := AParams.FindParam(Q.Params[c].Name);
    if AParam = nil then
    begin
      wsDBError(Format(_str(SErrorParamNotFound),
        [Q.Params[c].Name]));
    end;

    Case AParam.DataType of
      ftDateTime:
        Q.Params[c].AsDateTime := AParam.AsDateTime;
      ftInteger:
        Q.Params[c].AsInteger := AParam.AsInteger;
      ftString:
        Q.Params[c].AsString := AParam.AsString;
      ftMemo, ftBlob:
        Q.Params[c].AsString := AParam.AsString;
    else
      Q.Params[c].Value := AParam.Value;
    end;
  end;
end;

procedure TWorkflowpFIBDB.SetDatabase(const Value: TpFIBDatabase);
begin
  if (FDatabase <> Value) then
  begin
    FDatabase := Value;
    if Value <> nil then
      Value.FreeNotification(Self);
  end;                             
end;

procedure Register;
begin
  RegisterComponents('Workflow Studio', [TWorkflowpFIBDB]);
end;

end.
