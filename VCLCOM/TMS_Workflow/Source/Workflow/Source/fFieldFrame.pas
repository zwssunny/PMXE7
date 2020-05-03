unit fFieldFrame;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls, ComCtrls, StdCtrls, wsClasses, wsDiagram;

type
  TfrFieldFrame = class(TFrame)
    Panel1: TPanel;
    lvVars: TListView;
    Splitter1: TSplitter;
    Panel2: TPanel;
    Label1: TLabel;
    edCaption: TEdit;
    cbReadOnly: TCheckBox;
    cbRequired: TCheckBox;
    Label2: TLabel;
    cbVariable: TComboBox;
    Panel3: TPanel;
    btAdd: TButton;
    btDelete: TButton;
    procedure btAddClick(Sender: TObject);
    procedure lvVarsSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
    procedure PropertyChanged(Sender: TObject);
    procedure btDeleteClick(Sender: TObject);
    procedure lvVarsEdited(Sender: TObject; Item: TListItem; var S: String);
    procedure edCaptionChange(Sender: TObject);
  private
    FFields: TTaskFields;
    FUpdatingControls: integer;
    procedure BeginUpdateControls;
    procedure DeleteCurrentVar;
    procedure EndUpdateControls;
    procedure LoadVarInEditors(AVar: TTaskField);
    procedure SaveEditorsInVar(AVar: TTaskField);
    procedure SetControlsEnabled(AEnabled: boolean);
    procedure UpdateListItem(AItem: TListItem; AVar: TTaskField);
    procedure VarsToInterface;
    procedure ClearEditors;
    procedure FillVariableCombo(ADiagram: TCustomWorkflowDiagram);
    procedure Localize;
    function TaskFieldFromItem(AItem: TListItem): TTaskField;
  protected
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure LoadTaskInEditors(ATask: TTaskDefinition; ADiagram: TCustomWorkflowDiagram);
    procedure SaveEditorsInTask(ATask: TTaskDefinition);
    procedure ClearAll; 
  end;

implementation

uses
  wsBlocks, wsRes;

{$R *.DFM}

procedure TfrFieldFrame.VarsToInterface;
var
  c: integer;
begin
  lvVars.Items.Clear;
  for c := 0 to FFields.Count - 1 do
    UpdateListItem(lvVars.Items.Add, FFields[c]);
  ClearEditors;
  if lvVars.Items.Count > 0 then
    lvVars.Selected := lvVars.Items[0];
end;

procedure TfrFieldFrame.UpdateListItem(AItem: TListItem; AVar: TTaskField);
begin
  AItem.Caption := AVar.Caption;
  {$WARNINGS OFF}
  AItem.Data := AVar;
  {$WARNINGS ON}
end;

procedure TfrFieldFrame.btAddClick(Sender: TObject);
var
  NewVar: TTaskField;
  //NewName: string;
  //i: integer;
  NewItem: TListItem;
begin
  if lvVars.Enabled then
  begin
    {Add variable in collection}
    NewVar := FFields.Add;

    NewVar.Caption := _str(SEnterVariableCaption);

    {Create item in list view}
    NewItem := lvVars.Items.Add;
    UpdateListItem(NewItem, NewVar);

    {select and start renaming the item. EditCaption already selects the item}
    NewItem.EditCaption;
  end;
end;

function TfrFieldFrame.TaskFieldFromItem(AItem: TListItem): TTaskField;
begin
  {$WARNINGS OFF}
  result := TTaskField(AItem.Data);
  {$WARNINGS ON}
end;

procedure TfrFieldFrame.lvVarsSelectItem(Sender: TObject;
  Item: TListItem; Selected: Boolean);
begin
  if (lvVars.SelCount = 1) then
    LoadVarInEditors(TaskFieldFromItem(lvVars.Selected))
  else
    ClearEditors;
end;

procedure TfrFieldFrame.LoadVarInEditors(AVar: TTaskField);
begin
  if AVar <> nil then
  begin
    BeginUpdateControls;
    try
      edCaption.Text := AVar.Caption;
      cbReadOnly.Checked := AVar.ReadOnly;
      cbRequired.Checked := AVar.Required;
      cbVariable.Text := AVar.WorkflowVarName;
      SetControlsEnabled(true);
    finally
      EndUpdateControls;
    end;
  end;
end;

procedure TfrFieldFrame.SaveEditorsInVar(AVar: TTaskField);
begin
  if AVar <> nil then
  begin
    AVar.Caption := edCaption.Text;
    AVar.ReadOnly := cbReadOnly.Checked;
    AVar.Required := cbRequired.Checked;
    AVar.WorkflowVarName := cbVariable.Text;
  end;
end;

procedure TfrFieldFrame.ClearEditors;
begin
  BeginUpdateControls;
  try
    edCaption.Text := '';
    cbReadOnly.Checked := false;
    cbRequired.Checked := false;
    cbVariable.Text := '';

    SetControlsEnabled(false);
  finally
    EndUpdateControls;
  end;
end;

procedure TfrFieldFrame.PropertyChanged(Sender: TObject);
begin
  if (lvVars.SelCount = 1) and (FUpdatingControls = 0) then
    SaveEditorsInVar(TaskFieldFromItem(lvVars.Selected));
end;

procedure TfrFieldFrame.btDeleteClick(Sender: TObject);
begin
  if lvVars.Enabled then
  begin
    if MessageDlg(_str(SConfirmDeleteItems), 
       mtConfirmation,[mbYes,mbNo],0) = mrYes then
    begin
       while lvVars.SelCount > 0 do
          DeleteCurrentVar;
       if lvVars.Items.Count > 0 then
          lvVars.Selected := lvVars.Items[lvVars.items.Count - 1]
       else
          ClearEditors;
       lvVars.SetFocus;
    end;
  end;
end;

procedure TfrFieldFrame.DeleteCurrentVar;
begin
  if Assigned(lvVars.Selected) then
  begin
    TaskFieldFromItem(lvVars.Selected).Free;
    {$WARNINGS OFF}
    lvVars.Selected.Data := nil;
    {$WARNINGS ON}
    lvVars.Selected.Free;
  end;
end;

constructor TfrFieldFrame.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FFields := TTaskFields.Create(nil, TTaskField);
end;

destructor TfrFieldFrame.Destroy;
begin
  FFields.Free;
  inherited;
end;

procedure TfrFieldFrame.BeginUpdateControls;
begin
  inc(FUpdatingControls);
end;

procedure TfrFieldFrame.EndUpdateControls;
begin
  dec(FUpdatingControls);
end;

procedure TfrFieldFrame.lvVarsEdited(Sender: TObject; Item: TListItem;
  var S: String);
var
  AVar: TTaskField;
begin
  AVar := TaskFieldFromItem(Item);
  if AVar <> nil then
  begin
    if Trim(S) = '' then
      S := AVar.Caption
    else
    begin
      AVar.Caption := S;
      LoadVarInEditors(AVar);
    end;
  end;
end;

procedure TfrFieldFrame.SetControlsEnabled(AEnabled: boolean);
begin
  edCaption.Enabled := AEnabled;
  cbReadOnly.Enabled := AEnabled;
  cbRequired.Enabled := AEnabled;
  cbVariable.Enabled := AEnabled;
end;

procedure TfrFieldFrame.LoadTaskInEditors(ATask: TTaskDefinition; ADiagram: TCustomWorkflowDiagram);
begin
  FFields.Assign(ATask.Fields);
  lvVars.Enabled := true;
  btAdd.Enabled := true;
  btDelete.Enabled := true;
  FillVariableCombo(ADiagram);
  VarsToInterface;
end;

procedure TfrFieldFrame.SaveEditorsInTask(ATask: TTaskDefinition);
begin
  ATask.Fields.Assign(FFields);
end;

procedure TfrFieldFrame.FillVariableCombo(ADiagram: TCustomWorkflowDiagram);
var
  c: integer;
begin
  cbVariable.Items.Clear;
  if ADiagram <> nil then
  begin
    for c := 0 to ADiagram.Variables.Count - 1 do
       cbVariable.Items.Add(ADiagram.Variables[c].Name);
  end;
end;

procedure TfrFieldFrame.ClearAll;
begin
  lvVars.Items.Clear;
  lvVars.Enabled := false;
  btAdd.Enabled := false;
  btDelete.Enabled := false;
  ClearEditors;
end;

procedure TfrFieldFrame.edCaptionChange(Sender: TObject);
begin
  PropertyChanged(Sender);
  if lvVars.Selected <> nil then
    UpdateListItem(lvVars.Selected, TaskFieldFromItem(lvVars.Selected));
end;

procedure TfrFieldFrame.Localize;
begin
  Label1.Caption := _str('frFieldFrame.Label1.Caption');
  Label2.Caption := _str('frFieldFrame.Label2.Caption');
  cbReadOnly.Caption := _str('frFieldFrame.cbReadOnly.Caption');
  cbRequired.Caption := _str('frFieldFrame.cbRequired.Caption');
  btAdd.Caption := _str('frFieldFrame.btAdd.Caption');
  btDelete.Caption := _str('frFieldFrame.btDelete.Caption');
end;

procedure TfrFieldFrame.Loaded;
begin
  inherited;
  with lvVars.Columns.Add do
  begin
    AutoSize := True;
    Caption := _str(SVariables);
  end;
  Localize;
end;

end.

