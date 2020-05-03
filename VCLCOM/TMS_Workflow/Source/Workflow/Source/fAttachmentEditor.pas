unit fAttachmentEditor;

{$I wsdefs.inc}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  {$IFDEF DELPHI6_LVL}
  Variants,
  {$ENDIF}
  ComCtrls, wsClasses, StdCtrls, wsControls, fAttachmentFrame,
  Menus, wsMain;

type
  TfmAttachmentEditor = class(TForm)
    PageControl1: TPageControl;
    tsAttachments: TTabSheet;
    lvAttachs: TListView;
    btAdd: TButton;
    btDelete: TButton;
    btCancel: TButton;
    btOk: TButton;
    frItems: TfrAttachmentFrame;
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
    procedure btAddClick(Sender: TObject);
    procedure lvAttachsSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
    procedure btDeleteClick(Sender: TObject);
    procedure lvAttachsEdited(Sender: TObject; Item: TListItem; var S: String);
  private
    FLastAttachs: TAttachmentItems;
    FAttachs: TWorkflowAttachments;
    FUpdatingControls: integer;
    procedure ClearEditors;
    procedure BeginUpdateControls;
    procedure EndUpdateControls;
    procedure SetControlsEnabled(AEnabled: boolean);
    procedure AttachsToInterface;
    procedure DeleteCurrentAttach;
    procedure LoadAttachInEditors(AAttach: TWorkflowAttachment);
    procedure UpdateListItem(AItem: TListItem; AAttach: TWorkflowAttachment);
    procedure SaveAttachs;
    procedure Localize;
    function AttachmentFromItem(AItem: TListItem): TWorkflowAttachment;
  protected
    procedure Loaded; override;
  public
    function EditAttachments(AAttachs: TWorkflowAttachments): boolean;
    constructor Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio); reintroduce;
    destructor Destroy; override;
  end;

implementation

uses
  wsRes;

{$R *.DFM}

{ TForm1 }

function TfmAttachmentEditor.EditAttachments(AAttachs: TWorkflowAttachments): boolean;
begin
  FAttachs.Assign(AAttachs);
  AttachsToInterface;
  result := ShowModal = mrOk;
  if result then
  begin
    SaveAttachs;
    AAttachs.Assign(FAttachs);
  end;
end;

procedure TfmAttachmentEditor.btOkClick(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TfmAttachmentEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmAttachmentEditor.AttachsToInterface;
var
  c: integer;
begin
  lvAttachs.Items.Clear;
  for c := 0 to FAttachs.Count - 1 do
    UpdateListItem(lvAttachs.Items.Add, FAttachs[c]); 
  ClearEditors;
  if lvAttachs.Items.Count > 0 then
    lvAttachs.Selected := lvAttachs.Items[0];
end;

procedure TfmAttachmentEditor.UpdateListItem(AItem: TListItem; AAttach: TWorkflowAttachment);
begin
  AItem.Caption := AAttach.Name;
  {$WARNINGS OFF}
  AItem.Data := AAttach;
  {$WARNINGS ON}
end;

procedure TfmAttachmentEditor.btAddClick(Sender: TObject);
var
  NewAttach: TWorkflowAttachment;
  NewName: string;
  i: integer;
  NewItem: TListItem;
begin
  {Add attachment in collection}
  NewAttach := FAttachs.Add;

  {Find a new unique attach name}
  i := 0;
  repeat
    inc(i);
    NewName := Format('%s%d', [_str(SAttachment), i]);
  until (FAttachs.FindByName(NewName) = nil);
  NewAttach.Name := NewName;

  {Create item in list view}
  NewItem := lvAttachs.Items.Add;
  UpdateListItem(NewItem, NewAttach);

  {select and start renaming the item. EditCaption already selects the item}
  NewItem.EditCaption;
end;

procedure TfmAttachmentEditor.lvAttachsSelectItem(Sender: TObject; Item: TListItem;
  Selected: Boolean);
begin
  if (FAttachs <> nil) and not (csDestroying in ComponentState) then
  begin
    SaveAttachs;
    if (lvAttachs.SelCount = 1) then
      LoadAttachInEditors(AttachmentFromItem(lvAttachs.Selected))
    else
      ClearEditors;
  end;
end;

function TfmAttachmentEditor.AttachmentFromItem(AItem: TListItem): TWorkflowAttachment;
begin
  {$WARNINGS OFF}
  result := TWorkflowAttachment(AItem.Data);
  {$WARNINGS ON}
end;

procedure TfmAttachmentEditor.SaveAttachs;
begin
  if FLastAttachs <> nil then
  begin
    FLastAttachs.Assign(frItems.lvItems.Attachments);
    FLastAttachs := nil;
  end
end;

procedure TfmAttachmentEditor.LoadAttachInEditors(AAttach: TWorkflowAttachment);
begin
  if AAttach <> nil then
  begin
    BeginUpdateControls;
    try
      SaveAttachs;

      {set new attachment items}
      frItems.lvItems.Attachments := AAttach.Items;
      FLastAttachs := AAttach.Items;
      SetControlsEnabled(true);
    finally
      EndUpdateControls;
    end;
  end;
end;

procedure TfmAttachmentEditor.ClearEditors;
begin
  BeginUpdateControls;
  try
    frItems.lvItems.Attachments.Clear;
    SetControlsEnabled(false);
  finally
    EndUpdateControls;
  end;
end;

procedure TfmAttachmentEditor.btDeleteClick(Sender: TObject);
begin
  if MessageDlg(_str(SConfirmDeleteItems),
     mtConfirmation,[mbYes,mbNo],0) = mrYes then
  begin
     while lvAttachs.SelCount > 0 do
        DeleteCurrentAttach;
     if lvAttachs.Items.Count > 0 then
        lvAttachs.Selected := lvAttachs.Items[lvAttachs.items.Count - 1]
     else
        ClearEditors;
     lvAttachs.SetFocus;
  end;
end;

procedure TfmAttachmentEditor.DeleteCurrentAttach;
begin
  if Assigned(lvAttachs.Selected) then
  begin
    FLastAttachs := nil;
    AttachmentFromItem(lvAttachs.Selected).Free;
    {$WARNINGS OFF}
    lvAttachs.Selected.Data := nil;
    {$WARNINGS ON}
    lvAttachs.Selected.Free; 
  end;
end;

constructor TfmAttachmentEditor.Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio);
begin
  inherited Create(AOwner);
  if AWorkflowStudio = nil then
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);

  FLastAttachs := nil;
  FAttachs := TWorkflowAttachments.Create(nil);
  FAttachs.WorkflowStudio := AWorkflowStudio;
  
  frItems.Permissions := AllAttachmentPermissions;
  frItems.WorkflowStudio := AWorkflowStudio;
  //lvItems.ViewStyle := vsList;
end;

destructor TfmAttachmentEditor.Destroy;
begin
  FAttachs.Free;
  FAttachs := nil;
  inherited;
end;

procedure TfmAttachmentEditor.BeginUpdateControls;
begin
  inc(FUpdatingControls);
end;

procedure TfmAttachmentEditor.EndUpdateControls;
begin
  dec(FUpdatingControls);
end;

procedure TfmAttachmentEditor.lvAttachsEdited(Sender: TObject; Item: TListItem;
  var S: String);
var
  AAttach: TWorkflowAttachment;
begin
  AAttach := AttachmentFromItem(Item);
  if AAttach <> nil then
  begin
    if Trim(S) = '' then
      S := AAttach.Name
    else
      AAttach.Name := S;
  end;
end;

procedure TfmAttachmentEditor.SetControlsEnabled(AEnabled: boolean);
begin
  frItems.lvItems.Enabled := AEnabled;
end;

procedure TfmAttachmentEditor.Localize;
begin
  Self.Caption := _str('fmAttachmentEditor.Self.Caption');
  tsAttachments.Caption := _str('fmAttachmentEditor.tsAttachments.Caption');
  btAdd.Caption := _str('fmAttachmentEditor.btAdd.Caption');
  btDelete.Caption := _str('fmAttachmentEditor.btDelete.Caption');
  btCancel.Caption := _str('fmAttachmentEditor.btCancel.Caption');
  btOk.Caption := _str('fmAttachmentEditor.btOk.Caption');
end;

procedure TfmAttachmentEditor.Loaded;
begin
  inherited;
  with lvAttachs.Columns.Add do
  begin
    AutoSize := true;
    Caption := _str(SAttachment);
  end;
  Localize;
end;

end.
