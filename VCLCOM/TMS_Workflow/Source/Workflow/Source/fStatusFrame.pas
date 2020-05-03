unit fStatusFrame;

{$I wsdefs.inc}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, ComCtrls, StdCtrls, wsClasses, wsDiagram;

type
  TfrStatusFrame = class(TFrame)
    Panel1: TPanel;
    lvStatus: TListView;
    Splitter1: TSplitter;
    Panel2: TPanel;
    lbStatusName: TLabel;
    edStatusName: TEdit;
    chCompletion: TCheckBox;
    chHidden: TCheckBox;
    Panel3: TPanel;
    btAdd: TButton;
    btDelete: TButton;
    procedure btAddClick(Sender: TObject);
    procedure lvStatusSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
    procedure PropertyChanged(Sender: TObject);
    procedure btDeleteClick(Sender: TObject);
    procedure lvStatusEdited(Sender: TObject; Item: TListItem; var S: String);
    procedure edStatusNameChange(Sender: TObject);
    procedure lvStatusCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
  private
    FTaskDef: TTaskDefinition;
    FUpdatingControls: integer;
    procedure BeginUpdateControls;
    procedure DeleteCurrentStatus;
    procedure EndUpdateControls;
    procedure LoadStatusInEditors(AStatus: integer);
    procedure SaveEditorsInStatus(AStatus: integer);
    procedure SetControlsEnabled(AEnabled: boolean);
    procedure UpdateListItem(AItem: TListItem; AStatus: integer);
    procedure StatusListToInterface;
    procedure ClearEditors;
    procedure Localize;
    function StatusFromItem(AItem: TListItem): integer;
  protected
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure LoadTaskStatusList(ATaskDef: TTaskDefinition);
    procedure ClearAll;
  end;

implementation

uses
  wsBlocks, wsRes;

{$R *.DFM}

procedure TfrStatusFrame.StatusListToInterface;
var
  c: integer;
begin
  lvStatus.Items.BeginUpdate;
  try
    lvStatus.Items.Clear;
    for c := 0 to FTaskDef.StatusCount - 1 do
      UpdateListItem(lvStatus.Items.Add, c);
    ClearEditors;
    if lvStatus.Items.Count > 0 then
      lvStatus.Selected := lvStatus.Items[0];
  finally
    lvStatus.Items.EndUpdate;
  end;
end;

procedure TfrStatusFrame.UpdateListItem(AItem: TListItem; AStatus: integer);
begin
  AItem.Caption := FTaskDef.StatusName[AStatus];
  {$WARNINGS OFF}
  AItem.Data := pointer(AStatus);
  {$WARNINGS ON}
end;

procedure TfrStatusFrame.btAddClick(Sender: TObject);
var
  status: integer;
  item: TListItem;
begin
  if lvStatus.Enabled then
  begin
    status := FTaskDef.StatusAdd(_str(SEnterStatusName));
    item := lvStatus.Items.Add;
    UpdateListItem(item, status);
    item.EditCaption;
  end;
end;

function TfrStatusFrame.StatusFromItem(AItem: TListItem): integer;
begin
  {$WARNINGS OFF}
  result := integer(AItem.Data);
  {$WARNINGS ON}
end;

procedure TfrStatusFrame.lvStatusSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
begin
  if (lvStatus.SelCount = 1) then
    LoadStatusInEditors(StatusFromItem(lvStatus.Selected))
  else
    ClearEditors;
end;

procedure TfrStatusFrame.LoadStatusInEditors(AStatus: integer);
begin
  if (AStatus >= 0) and (AStatus < FTaskDef.StatusCount) then
  begin
    BeginUpdateControls;
    try
      edStatusName.Text := FTaskDef.StatusName[AStatus];
      chCompletion.Checked := FTaskDef.StatusCompletion[AStatus];
      chHidden.Checked := FTaskDef.StatusHidden[AStatus];
      SetControlsEnabled(true);
    finally
      EndUpdateControls;
    end;
  end;
end;

procedure TfrStatusFrame.SaveEditorsInStatus(AStatus: integer);
begin
  if (AStatus >= 0) and (AStatus < FTaskDef.StatusCount) then
  begin
    FTaskDef.StatusName[AStatus] := edStatusName.Text;
    FTaskDef.StatusCompletion[AStatus] := chCompletion.Checked;
    FTaskDef.StatusHidden[AStatus] := chHidden.Checked;
  end;
end;

procedure TfrStatusFrame.ClearEditors;
begin
  BeginUpdateControls;
  try
    edStatusName.Clear;
    chCompletion.Checked := false;
    chHidden.Checked := false;
    SetControlsEnabled(false);
  finally
    EndUpdateControls;
  end;
end;

procedure TfrStatusFrame.PropertyChanged(Sender: TObject);
begin
  if (lvStatus.SelCount = 1) and (FUpdatingControls = 0) then
    SaveEditorsInStatus(StatusFromItem(lvStatus.Selected));
end;

procedure TfrStatusFrame.btDeleteClick(Sender: TObject);
begin
  if lvStatus.Enabled then
  begin
    if MessageDlg(_str(SConfirmDeleteItems), mtConfirmation,[mbYes,mbNo],0) = mrYes then
    begin
      while lvStatus.SelCount > 0 do
        DeleteCurrentStatus;
      StatusListToInterface;
      if lvStatus.Items.Count > 0 then
        lvStatus.Selected := lvStatus.Items[lvStatus.Items.Count - 1]
      else
        ClearEditors;
      lvStatus.SetFocus;
    end;
  end;
end;

procedure TfrStatusFrame.DeleteCurrentStatus;
begin
  if Assigned(lvStatus.Selected) then
  begin
    FTaskDef.StatusList.Delete(StatusFromItem(lvStatus.Selected));
    {$WARNINGS OFF}
    lvStatus.Selected.Data := pointer(-1);
    {$WARNINGS ON}
    lvStatus.Selected.Free;
  end;
end;

constructor TfrStatusFrame.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
end;

destructor TfrStatusFrame.Destroy;
begin
  inherited;
end;

procedure TfrStatusFrame.BeginUpdateControls;
begin
  inc(FUpdatingControls);
end;

procedure TfrStatusFrame.EndUpdateControls;
begin
  dec(FUpdatingControls);
end;

procedure TfrStatusFrame.lvStatusCustomDrawItem(Sender: TCustomListView;
  Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
var
  i: integer;
begin
  i := StatusFromItem(Item);
  if (i >= 0) and (i < FTaskDef.StatusCount) then
  begin
    if FTaskDef.StatusCompletion[i] then
      Sender.Canvas.Font.Style := [fsBold];
    if FTaskDef.StatusHidden[i] then
      Sender.Canvas.Font.Color := clGray;
  end;
end;

procedure TfrStatusFrame.lvStatusEdited(Sender: TObject; Item: TListItem; var S: String);
var
  status: integer;
begin
  status := StatusFromItem(Item);
  if status >= 0 then
  begin
    if Trim(S) = '' then
      S := FTaskDef.StatusName[status]
    else
    begin
      FTaskDef.StatusName[status] := S;
      LoadStatusInEditors(status);
    end;
  end;
end;

procedure TfrStatusFrame.SetControlsEnabled(AEnabled: boolean);
begin
  edStatusName.Enabled := AEnabled;
  chCompletion.Enabled := AEnabled;
  chHidden.Enabled := AEnabled;
end;

procedure TfrStatusFrame.LoadTaskStatusList(ATaskDef: TTaskDefinition);
begin
  FTaskDef := ATaskDef;
  lvStatus.Enabled := true;
  btAdd.Enabled := true;
  btDelete.Enabled := true;
  StatusListToInterface;
end;

procedure TfrStatusFrame.ClearAll;
begin
  lvStatus.Items.Clear;
  lvStatus.Enabled := false;
  btAdd.Enabled := false;
  btDelete.Enabled := false;
  ClearEditors;
end;

procedure TfrStatusFrame.edStatusNameChange(Sender: TObject);
begin
  PropertyChanged(Sender);
  if lvStatus.Selected <> nil then
    UpdateListItem(lvStatus.Selected, StatusFromItem(lvStatus.Selected));
end;

procedure TfrStatusFrame.Localize;
begin
  lbStatusName.Caption := _str('frStatusFrame.lbStatusName.Caption');
  chCompletion.Caption := _str('frStatusFrame.chCompletion.Caption');
  chHidden.Caption := _str('frStatusFrame.chHidden.Caption');
  btAdd.Caption := _str('frStatusFrame.btAdd.Caption');
  btDelete.Caption := _str('frStatusFrame.btDelete.Caption');
end;

procedure TfrStatusFrame.Loaded;
begin
  inherited;
  with lvStatus.Columns.Add do
  begin
    AutoSize := True;
    Caption := _str(SStatusList);
  end;
  Localize;
end;

end.

