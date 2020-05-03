unit fVariableEditor;

{$I wsdefs.inc}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  {$IFDEF DELPHI6_LVL}
  Variants,
  {$ENDIF}
  ComCtrls, StdCtrls, wsClasses;

type
  TfmVariableEditor = class(TForm)
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    lvVars: TListView;
    Label1: TLabel;
    edValue: TEdit;
    btAdd: TButton;
    btDelete: TButton;
    btCancel: TButton;
    btOk: TButton;
    ckbInteraction: TCheckBox;
    Memo1: TMemo;
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
    procedure btAddClick(Sender: TObject);
    procedure lvVarsSelectItem(Sender: TObject; Item: TListItem;
      Selected: Boolean);
    procedure PropertyChanged(Sender: TObject);
    procedure btDeleteClick(Sender: TObject);
    procedure lvVarsEdited(Sender: TObject; Item: TListItem;
      var S: String);
  private
    { Private declarations }
    FVars: TWorkflowVariables;
    FUpdatingControls: integer;
    procedure VarsToInterface;
    procedure UpdateListItem(AItem: TListItem; AVar: TWorkflowVariable);
    procedure LoadVarInEditors(AVar: TWorkflowVariable);
    procedure ClearEditors;
    procedure SaveEditorsInVar(AVar: TWorkflowVariable);
    procedure DeleteCurrentVar;
    procedure BeginUpdateControls;
    procedure EndUpdateControls;
    procedure SetControlsEnabled(AEnabled: boolean);
    procedure Localize;
    function WorkVarFromItem(AItem: TListItem): TWorkflowVariable;
  protected
    procedure Loaded; override;
  public
    { Public declarations }
    function EditVariables(AVars: TWorkflowVariables): boolean;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

implementation
uses wsMain, wsRes;

{$R *.DFM}

{ TForm1 }

function TfmVariableEditor.EditVariables(AVars: TWorkflowVariables): boolean;
begin
  FVars.Assign(AVars);
  VarsToInterface;
  result := ShowModal = mrOk;
  if result then
    AVars.Assign(FVars);
end;

procedure TfmVariableEditor.btOkClick(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TfmVariableEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmVariableEditor.VarsToInterface;
var
  c: integer;
begin
  lvVars.Items.Clear;
  for c := 0 to FVars.Count - 1 do
    UpdateListItem(lvVars.Items.Add, FVars[c]); 
  ClearEditors;
  if lvVars.Items.Count > 0 then
    lvVars.Selected := lvVars.Items[0];
end;

procedure TfmVariableEditor.UpdateListItem(AItem: TListItem; AVar: TWorkflowVariable);
begin
  AItem.Caption := AVar.Name;
  {$WARNINGS OFF}
  AItem.Data := AVar;
  {$WARNINGS ON}
end;

procedure TfmVariableEditor.btAddClick(Sender: TObject);
var
  NewVar: TWorkflowVariable;
  NewName: string;
  i: integer;
  NewItem: TListItem;
begin
  {Add variable in collection}
  NewVar := FVars.Add;

  {Find a new unique var name}
  i := 0;
  repeat
    inc(i);
    NewName := Format('%s%d', ['Variable', i]);
  until (FVars.FindByName(NewName) = nil);
  NewVar.Name := NewName;

  {Create item in list view}
  NewItem := lvVars.Items.Add;
  UpdateListItem(NewItem, NewVar);

  {select and start renaming the item. EditCaption already selects the item}
  NewItem.EditCaption;
end;

procedure TfmVariableEditor.lvVarsSelectItem(Sender: TObject; Item: TListItem;
  Selected: Boolean);
begin
  if (lvVars.SelCount = 1) then
    LoadVarInEditors(WorkVarFromItem(lvVars.Selected))
  else
    ClearEditors;
end;

function TfmVariableEditor.WorkVarFromItem(AItem: TListItem): TWorkflowVariable;
begin
  {$WARNINGS OFF}
  result := TWorkflowVariable(AItem.Data);
  {$WARNINGS ON}
end;

procedure TfmVariableEditor.LoadVarInEditors(AVar: TWorkflowVariable);
begin
  if AVar <> nil then
  begin
    BeginUpdateControls;
    try
      edValue.Text := VarToStr(AVar.Value);
      ckbInteraction.Checked := AVar.Interaction;
      SetControlsEnabled(true);
    finally
      EndUpdateControls;
    end;
  end;
end;

procedure TfmVariableEditor.SaveEditorsInVar(AVar: TWorkflowVariable);
begin
  if AVar <> nil then
  begin
    AVar.Value := edValue.Text;
    AVar.Interaction := ckbInteraction.Checked;
  end;
end;

procedure TfmVariableEditor.ClearEditors;
begin
  BeginUpdateControls;
  try
    edValue.Text := '';
    ckbInteraction.Checked := false;
    SetControlsEnabled(false);
  finally
    EndUpdateControls;
  end;
end;

procedure TfmVariableEditor.PropertyChanged(Sender: TObject);
begin
  if (lvVars.SelCount = 1) and (FUpdatingControls = 0) then
    SaveEditorsInVar(WorkVarFromItem(lvVars.Selected));
end;

procedure TfmVariableEditor.btDeleteClick(Sender: TObject);
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

procedure TfmVariableEditor.DeleteCurrentVar;
begin
  if Assigned(lvVars.Selected) then
  begin
    WorkVarFromItem(lvVars.Selected).Free;
    {$WARNINGS OFF}
    lvVars.Selected.Data := nil;
    {$WARNINGS ON}
    lvVars.Selected.Free;
  end;
end;

constructor TfmVariableEditor.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FVars := TWorkflowVariables.Create(nil, TWorkflowVariable);
end;

destructor TfmVariableEditor.Destroy;
begin
  FVars.Free;
  inherited;
end;

procedure TfmVariableEditor.BeginUpdateControls;
begin
  inc(FUpdatingControls);
end;

procedure TfmVariableEditor.EndUpdateControls;
begin
  dec(FUpdatingControls);
end;

procedure TfmVariableEditor.lvVarsEdited(Sender: TObject; Item: TListItem;
  var S: String);
var
  AVar: TWorkflowVariable;
begin
  AVar := WorkVarFromItem(Item);
  if AVar <> nil then
  begin
    if Trim(S) = '' then
      S := AVar.Name
    else
      AVar.Name := S;
  end;
end;

procedure TfmVariableEditor.SetControlsEnabled(AEnabled: boolean);
begin
  edValue.Enabled := AEnabled;
end;

procedure TfmVariableEditor.Localize;
begin
  Self.Caption := _str('fmVariableEditor.Self.Caption');
  TabSheet1.Caption := _str('fmVariableEditor.TabSheet1.Caption');
  Label1.Caption := _str('fmVariableEditor.Label1.Caption');
  btAdd.Caption := _str('fmVariableEditor.btAdd.Caption');
  btDelete.Caption := _str('fmVariableEditor.btDelete.Caption');
  btCancel.Caption := _str('fmVariableEditor.btCancel.Caption');
  btOk.Caption := _str('fmVariableEditor.btOk.Caption');
end;

procedure TfmVariableEditor.Loaded;
begin
  inherited;
  with lvVars.Columns.Add do
  begin
    AutoSize := True;
    Caption := _str(SVariable);
  end;
  Localize;
end;

end.

