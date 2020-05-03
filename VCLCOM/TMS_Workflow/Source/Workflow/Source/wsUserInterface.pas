unit wsUserInterface;

interface

uses
  Classes, Forms, wsClasses, wsMain;

type
  TWorkflowUserInterface = class(TCustomWorkflowUserInterface)
  public
    procedure ShowUserTasksDlg(AUserKey: string; AFormMode: TWorkflowFormMode = wfmModal); override;
    procedure ShowUsersTasksDlg(AUserKeys: string; AFormMode: TWorkflowFormMode = wfmModal); override;
    procedure ShowWorkInsTasksDlg(AWorkInsKey: string; AFormMode: TWorkflowFormMode = wfmModal); override;
    procedure ShowWorkflowDefinitionsDlg; override;
    procedure EditWorkflowDefinition(AWorkDef: TWorkflowDefinition); override;
    procedure EditWorkflowInstance(AWorkIns: TWorkflowInstance); override;
  end;

implementation

uses
  fTaskList, fWorkDefManager, wsDB, fWorkflowEditor;

{ TWorkflowUserInterface }

procedure TWorkflowUserInterface.EditWorkflowDefinition(AWorkDef: TWorkflowDefinition);
begin
  EditWorkflowDefDiagram(AWorkDef);
end;
procedure TWorkflowUserInterface.EditWorkflowInstance(AWorkIns: TWorkflowInstance);
begin
  EditWorkflowInsDiagram(AWorkIns);
end;

procedure TWorkflowUserInterface.ShowWorkflowDefinitionsDlg;
var
  WorkDefForm: TfmWorkDefManager;
begin
  WorkDefForm := TfmWorkDefManager.Create(nil, WorkflowStudio);
  try
    WorkDefForm.ShowModal;
  finally
    WorkDefForm.Free;
  end;
end;

procedure TWorkflowUserInterface.ShowUsersTasksDlg(AUserKeys: string; AFormMode: TWorkflowFormMode = wfmModal);
var
  TaskForm: TfmTaskList;
begin
  Case AFormMode of
    wfmMDI:
      begin
        TaskForm := TfmTaskList.Create(Application, WorkflowStudio);
        TaskForm.FormStyle := fsMDIChild;
        TaskForm.WindowState := wsMaximized;
      end;
  else
    {wfmModal} TaskForm := TfmTaskList.Create(nil, WorkflowStudio);
  end;
  
  try
    TaskForm.SetFilter(tfUserList, AUserKeys);
    TaskForm.LoadData;
    Case AFormMode of
      wfmModal: TaskForm.ShowModal;
      wfmMDI: TaskForm.Show;
    end;
  finally
    Case AFormMode of
      wfmModal: TaskForm.Free;
    else
      TaskForm.FreeOnClose := true;
    end;
  end;
end;

procedure TWorkflowUserInterface.ShowUserTasksDlg(AUserKey: string; AFormMode: TWorkflowFormMode = wfmModal);
var
  TaskForm: TfmTaskList;
begin
  Case AFormMode of
    wfmMDI:
      begin
        TaskForm := TfmTaskList.Create(Application, WorkflowStudio);
        TaskForm.FormStyle := fsMDIChild;
        TaskForm.WindowState := wsMaximized;
      end;
  else
    {wfmModal} TaskForm := TfmTaskList.Create(nil, WorkflowStudio);
  end;

  try
    TaskForm.SetFilter(tfUser, AUserKey);
    TaskForm.LoadData;
    Case AFormMode of
      wfmModal: TaskForm.ShowModal;
      wfmMDI: TaskForm.Show;
    end;
  finally
    Case AFormMode of
      wfmModal: TaskForm.Free;
    else
      TaskForm.FreeOnClose := true;
    end;
  end;
end;

procedure TWorkflowUserInterface.ShowWorkInsTasksDlg(AWorkInsKey: string; AFormMode: TWorkflowFormMode = wfmModal);
var
  TaskForm: TfmTaskList;
begin
  Case AFormMode of
    wfmMDI:
      begin
        TaskForm := TfmTaskList.Create(Application, WorkflowStudio);
        TaskForm.FormStyle := fsMDIChild;
        TaskForm.WindowState := wsMaximized;
      end;
  else
    {wfmModal} TaskForm := TfmTaskList.Create(nil, WorkflowStudio);
  end;

  try
    TaskForm.SetFilter(tfWorkIns, AWorkInsKey);
    TaskForm.LoadData;
    Case AFormMode of
      wfmModal: TaskForm.ShowModal;
      wfmMDI: TaskForm.Show;
    end;
  finally
    Case AFormMode of
      wfmModal: TaskForm.Free;
    else
      TaskForm.FreeOnClose := true;
    end;
  end;
end;

initialization
  UserInterfaceClass := TWorkflowUserInterface;

end.

