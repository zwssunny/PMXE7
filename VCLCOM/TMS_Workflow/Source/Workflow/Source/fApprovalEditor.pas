unit fApprovalEditor;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, StdCtrls, wsClasses, wsBlocks, fAttachPermissions, fFieldFrame,
  wsMain, wsDiagram, fStatusFrame, fExpirationFrame, fAssignedUserFrame;

type
  TfmApprovalEditor = class(TForm)
    PageControl1: TPageControl;
    tsGeneral: TTabSheet;
    lbSubject: TLabel;
    edSubject: TEdit;
    lbDescription: TLabel;
    mmComments: TMemo;
    tsStatus: TTabSheet;
    btCancel: TButton;
    btOk: TButton;
    cbMailNotification: TCheckBox;
    tsAttachments: TTabSheet;
    frPermissions: TfrAttachPermissions;
    tsFields: TTabSheet;
    frFields: TfrFieldFrame;
    tsExpiration: TTabSheet;
    frStatus: TfrStatusFrame;
    frExpiration: TfrExpirationFrame;
    frAssignedUser: TfrAssignedUserFrame;
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
    procedure PropertyChanged(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private                     
    FDiagram: TCustomWorkflowDiagram;
    FTask: TTaskDefinition;
    FUpdatingControls: integer;
    FWorkflowStudio: TCustomWorkflowStudio;
    procedure TaskToInterface;
    procedure LoadTaskInEditors(ATask: TTaskDefinition);
    procedure SaveEditorsInTask(ATask: TTaskDefinition);
    procedure BeginUpdateControls;
    procedure EndUpdateControls;
    procedure SetControlsEnabled(AEnabled: boolean);
    procedure Localize;
  protected
    procedure Loaded; override;
  public
    function EditApprovalDefinition(ABlock: TWorkflowApprovalBlock; ADiagram: TCustomWorkflowDiagram): boolean;
    constructor Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio); reintroduce;
    destructor Destroy; override;
  end;

var
  fmApprovalEditor: TfmApprovalEditor;

implementation

uses
  wsRes;

{$R *.DFM}

{ TForm1 }

function TfmApprovalEditor.EditApprovalDefinition(ABlock: TWorkflowApprovalBlock; ADiagram: TCustomWorkflowDiagram): boolean;
begin
  FTask.Assign(ABlock.Task);
  FDiagram := ADiagram;
  frPermissions.OnPropertyChanged := PropertyChanged;
  frExpiration.OnPropertyChanged := PropertyChanged;
  TaskToInterface;
  result := ShowModal = mrOk;
  if result then
  begin
    frFields.SaveEditorsInTask(FTask);
    frAssignedUser.SaveEditorsInTask(FTask);
    ABlock.Task.Assign(FTask);
  end;
end;

procedure TfmApprovalEditor.btOkClick(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TfmApprovalEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmApprovalEditor.TaskToInterface;
begin
  LoadTaskInEditors(FTask);
end;

procedure TfmApprovalEditor.LoadTaskInEditors(ATask: TTaskDefinition);
begin
  if ATask <> nil then
  begin
    BeginUpdateControls;
    try
      edSubject.Text := ATask.Subject;
      mmComments.Lines.Text := ATask.Description;
      //edAssignment.Text := ATask.AssignmentRule;
      cbMailNotification.Checked := ATask.MailNotification;
      frPermissions.LoadTaskInEditors(ATask);
      frFields.LoadTaskInEditors(ATask, FDiagram);
      frAssignedUser.LoadTaskInEditors(ATask,FDiagram);
      frStatus.LoadTaskStatusList(ATask);
      frExpiration.LoadTaskInEditors(ATask);
      SetControlsEnabled(true);
    finally
      EndUpdateControls;
    end;
  end;
end;

procedure TfmApprovalEditor.SaveEditorsInTask(ATask: TTaskDefinition);
begin
  if ATask <> nil then
  begin
    ATask.Subject := edSubject.Text;
    ATask.Description := mmComments.Lines.Text;
    //ATask.AssignmentRule := edAssignment.Text;
    ATask.MailNotification := cbMailNotification.Checked;
    frPermissions.SaveEditorsInTask(ATask);
    frFields.SaveEditorsInTask(ATask);
    frAssignedUser.SaveEditorsInTask(ATask);
    frExpiration.SaveEditorsInTask(ATask);
  end;
end;

procedure TfmApprovalEditor.PropertyChanged(Sender: TObject);
begin
  if (FUpdatingControls = 0) then
    SaveEditorsInTask(FTask);
end;

constructor TfmApprovalEditor.Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio);
begin
  inherited Create(AOwner);
  if AWorkflowStudio <> nil then
    FWorkflowStudio := AWorkflowStudio
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);

  FTask := TTaskDefinition.Create(nil);
  //FWorkflowStudio.UserManager.FillAssignmentList(edAssignment.Items);
end;

destructor TfmApprovalEditor.Destroy;
begin
  FTask.Free;
  inherited;
end;

procedure TfmApprovalEditor.BeginUpdateControls;
begin
  inc(FUpdatingControls);
end;

procedure TfmApprovalEditor.EndUpdateControls;
begin
  dec(FUpdatingControls);
end;

procedure TfmApprovalEditor.SetControlsEnabled(AEnabled: boolean);
begin
  edSubject.Enabled := AEnabled;
  mmComments.Enabled := AEnabled;
  frAssignedUser.Enabled := AEnabled;
  cbMailNotification.Enabled := AEnabled;
end;

procedure TfmApprovalEditor.FormCreate(Sender: TObject);
begin
  PageControl1.ActivePage := tsGeneral;
  ActiveControl := edSubject;
end;

procedure TfmApprovalEditor.Localize;
begin
  Self.Caption := _str('fmApprovalEditor.Self.Caption');
  tsGeneral.Caption := _str('fmApprovalEditor.tsGeneral.Caption');
  lbSubject.Caption := _str('fmApprovalEditor.lbSubject.Caption');
  lbDescription.Caption := _str('fmApprovalEditor.lbDescription.Caption');
  //lbAssignment.Caption := _str('fmApprovalEditor.lbAssignment.Caption');
  cbMailNotification.Caption := _str('fmApprovalEditor.cbMailNotification.Caption');
  tsStatus.Caption := _str('fmApprovalEditor.tsStatus.Caption');
  tsAttachments.Caption := _str('fmApprovalEditor.tsAttachments.Caption');
  tsFields.Caption := _str('fmApprovalEditor.tsFields.Caption');
  btCancel.Caption := _str('fmApprovalEditor.btCancel.Caption');
  btOk.Caption := _str('fmApprovalEditor.btOk.Caption');
  tsExpiration.Caption := _str('fmApprovalEditor.tsExpiration.Caption');
end;

procedure TfmApprovalEditor.FormActivate(Sender: TObject);
begin
  edSubject.SetFocus;
end;

procedure TfmApprovalEditor.Loaded;
begin
  inherited;
  Localize;
end;

end.

