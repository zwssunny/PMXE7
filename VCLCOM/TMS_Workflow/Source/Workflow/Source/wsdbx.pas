unit wsDbx;

{$I wsdefs.inc}

interface
uses SysUtils, Classes, Dialogs,
  {$IFDEF DELPHI6_LVL} Variants, {$ENDIF}
  wsDB, DB, SQLExpr;

type
  TDBXDBType = (dbxAny, dbxOracle, dbxSQLServer, dbxFirebird);

  TWorkflowDBXDB = class(TCustomWorkflowDB)
  private
    FConnection: TSQLConnection;
    FDBType: TDBXDBType;
    procedure SetConnection(const Value: TSQLConnection);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    function DoCreateQuery(SQL: string): TDataset; override;
    procedure DoExecuteQuery(Dataset: TDataset); override;
    procedure DoAssignSQLParams(Dataset: TDataset; AParams: TParams); override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property SQLConnection: TSQLConnection read FConnection write SetConnection;
    property DBType: TDBXDBType read FDBType write FDBType; 
  end;

procedure Register;

implementation
uses SQLTimSt, wsRes;

{ TWorkflowDBXDB }

constructor TWorkflowDBXDB.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  DestroyQueries := true;
end;


procedure TWorkflowDBXDB.DoExecuteQuery(Dataset: TDataset);
begin
  TSQLQuery(Dataset).ExecSQL;
end;

function TWorkflowDBXDB.DoCreateQuery(SQL: string): TDataset;
var
  Q: TSQLQuery;
begin
  Q := TSQLQuery.Create(nil);
  Q.SQLConnection := FConnection;
  Q.SQL.Text := SQL;
  result := Q;
end;

procedure TWorkflowDBXDB.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  if (Operation = opRemove) and (AComponent = FConnection) then
    FConnection := nil;
  inherited Notification(AComponent, Operation);
end;

procedure TWorkflowDBXDB.DoAssignSQLParams(Dataset: TDataset; AParams: TParams);
var
  c: integer;
  ADate: TDateTime;
begin
  //Prepare the params
  for c := 0 to AParams.Count - 1 do
  begin
    Case AParams[c].DataType of
      ftDateTime:
        begin
          {dbxOracle, dbxSQLServer, dbxFirebird}

          //Workaround dbexpress bug - convert datetime to timestamp
          ADate := AParams[c].AsDateTime;
          AParams[c].DataType := ftTimeStamp;
          AParams[c].AsSQLTimeStamp := DateTimeToSQLTimeStamp(ADate);
        end;
      ftInteger:
        begin
          {dbxOracle, dbxSQLServer, dbxFirebird}

          //Workaround dbexpress bug - convert asinteger to asString
          AParams[c].AsString := IntToStr(AParams[c].AsInteger);
        end;
      ftMemo, ftBlob:
        begin
          {dbxFirebird}                        
          {$IFDEF DELPHI2009_LVL}
          if FDBType = dbxFirebird then
            AParams[c].AsBlob := AParams[c].AsBytes;
          {$ELSE}
          if FDBType = dbxFirebird then
            AParams[c].AsBlob := AParams[c].AsString;
          {$ENDIF}
        end;
    end;
  end;

  //Assign param values
  TSQLQuery(Dataset).Params.AssignValues(AParams);
end;

procedure TWorkflowDBXDB.SetConnection(const Value: TSQLConnection);
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
  RegisterComponents('Workflow Studio', [TWorkflowDBXDB]);
end;

end.
