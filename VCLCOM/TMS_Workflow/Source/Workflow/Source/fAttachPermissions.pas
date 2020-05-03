unit fAttachPermissions;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, wsClasses;

type
  TfrAttachPermissions = class(TFrame)
    cbShowAttachments: TCheckBox;
    cbDelAttachment: TCheckBox;
    cbInsAttachment: TCheckBox;
    cbEditAttachment: TCheckBox; 
    procedure PropertyChanged(Sender: TObject);
    procedure cbShowAttachmentsClick(Sender: TObject);
  private
    { Private declarations }
    FUpdatingControls: boolean;
    FOnPropertyChanged: TNotifyEvent;
    procedure BeginUpdateControls;
    procedure EndUpdateControls;
    procedure SetControlsEnabled(AEnabled: boolean);
    procedure Localize;
  protected
    procedure Loaded; override;
  public
    procedure LoadTaskInEditors(ATask: TTaskDefinition);
    procedure SaveEditorsInTask(ATask: TTaskDefinition);
    procedure ClearEditors;
    { Public declarations }
    property OnPropertyChanged: TNotifyEvent read FOnPropertyChanged write FOnPropertyChanged;
  end;

implementation
uses wsRes;

{$R *.DFM}

{ TfrAttachPermissions }

procedure TfrAttachPermissions.BeginUpdateControls;
begin
  inc(FUpdatingControls);
end;

procedure TfrAttachPermissions.ClearEditors;
begin
  BeginUpdateControls;
  try
    cbShowAttachments.Checked := false;
    cbInsAttachment.Checked := false;
    cbDelAttachment.Checked := false;
    cbEditAttachment.Checked := false;
    SetControlsEnabled(false);
  finally
    EndUpdateControls;
  end;
end;

procedure TfrAttachPermissions.EndUpdateControls;
begin
  dec(FUpdatingControls);
end;

procedure TfrAttachPermissions.LoadTaskInEditors(ATask: TTaskDefinition);
begin
  if ATask <> nil then
  begin
    BeginUpdateControls;
    try
      cbShowAttachments.Checked := ATask.ShowAttachments;
      cbInsAttachment.Checked := apInsert in ATask.AttachmentPermissions;
      cbDelAttachment.Checked := apDelete in ATask.AttachmentPermissions;
      cbEditAttachment.Checked := apEdit in ATask.AttachmentPermissions;
      SetControlsEnabled(true);
    finally
      EndUpdateControls;
    end;
  end;
end;

procedure TfrAttachPermissions.SaveEditorsInTask(ATask: TTaskDefinition);
begin
  if ATask <> nil then
  begin
    ATask.ShowAttachments := cbShowAttachments.Checked;
    ATask.AttachmentPermissions := [];
    if cbInsAttachment.Checked then
      ATask.AttachmentPermissions := ATask.AttachmentPermissions + [apInsert];
    if cbDelAttachment.Checked then
      ATask.AttachmentPermissions := ATask.AttachmentPermissions + [apDelete];
    if cbEditAttachment.Checked then
      ATask.AttachmentPermissions := ATask.AttachmentPermissions + [apEdit];
  end;
end;

procedure TfrAttachPermissions.SetControlsEnabled(AEnabled: boolean);
begin
  cbShowAttachments.Enabled := AEnabled;
  cbInsAttachment.Enabled := cbShowAttachments.Checked and AEnabled;
  cbDelAttachment.Enabled := cbShowAttachments.Checked and AEnabled;
  cbEditAttachment.Enabled := cbShowAttachments.Checked and AEnabled;
end;

procedure TfrAttachPermissions.PropertyChanged(Sender: TObject);
begin
  if Assigned(FOnPropertyChanged) then
    FOnPropertyChanged(Sender);
end;

procedure TfrAttachPermissions.cbShowAttachmentsClick(Sender: TObject);
begin
  SetControlsEnabled(cbShowAttachments.Enabled);
  PropertyChanged(Sender);
end;

procedure TfrAttachPermissions.Localize;
begin
  cbShowAttachments.Caption := _str('frAttachPermissions.cbShowAttachments.Caption');
  cbDelAttachment.Caption := _str('frAttachPermissions.cbDelAttachment.Caption');
  cbInsAttachment.Caption := _str('frAttachPermissions.cbInsAttachment.Caption');
  cbEditAttachment.Caption := _str('frAttachPermissions.cbEditAttachment.Caption');
end;

procedure TfrAttachPermissions.Loaded;
begin
  inherited;
  Localize;
end;

end.
