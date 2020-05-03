unit fTaskList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, wsMain,
  Db, Grids, DBGrids, ComCtrls, wsControls, ExtCtrls, fTaskInstanceView,
  atDiagram, LiveDiagram, wsClasses, wsDB, StdCtrls, ActnList, Menus, wsDiagram;

type
  TfmTaskList = class(TForm)
    Panel1: TPanel;
    lvTasks: TTaskListView;
    Panel2: TPanel;
    Panel3: TPanel;
    Splitter1: TSplitter;
    Splitter2: TSplitter;
    Splitter3: TSplitter;
    btSaveChanges: TButton;
    TabControl1: TTabControl;
    frTaskView: TfrTaskInstanceView;
    ActionList1: TActionList;
    acShowAllTasks: TAction;
    PopupMenu1: TPopupMenu;
    acShowOnlyOpen: TAction;
    miView: TMenuItem;
    Showonlyopentasks2: TMenuItem;
    Showalltasks2: TMenuItem;
    WorkflowDiagram1: TWorkflowDiagram;
    Timer1: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btSaveChangesClick(Sender: TObject);
    procedure WorkflowDiagram1Click(Sender: TObject);
    procedure TabControl1Change(Sender: TObject);
    procedure lvTasksSelectItem(Sender: TObject; Item: TListItem; Selected: Boolean);
    procedure acShowOnlyOpenExecute(Sender: TObject);
    procedure acShowOnlyOpenUpdate(Sender: TObject);
    procedure acShowAllTasksExecute(Sender: TObject);
    procedure acShowAllTasksUpdate(Sender: TObject);
    procedure lvTasksCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
    procedure Timer1Timer(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    FWorkIns: TWorkflowInstance;
    FLastActivePageName: string;
    FUpdatingTabs: integer;
    FFieldPanel: TTaskFieldPanel;
    FLogView: TTaskLogListView;
    FFreeOnClose: boolean;
    FWorkflowStudio: TWorkflowStudio;
    function GetWorkIns: TWorkflowInstance;
    procedure AddAttachmentTab(AAttach: TWorkflowAttachment; APermissions: TAttachmentPermissions);
    procedure UpdateFieldsTab;
    procedure UpdateActivePage;
    procedure UpdateFixedTabs;
    function FindTabByType(AType: integer): integer;
    procedure SaveChanges;
    procedure UpdateWorkflowDiagram;
    procedure UpdateAttachmentTabs;
    procedure BeginUpdateTabs;
    procedure EndUpdateTabs;
    procedure Localize;
    procedure UpdateLogTab;
  protected
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent; AWorkflowStudio: TWorkflowStudio); reintroduce;
    procedure SetFilter(FilterType: TTaskFilterType; AFilter: string);
    procedure LoadData;
    property FreeOnClose: boolean read FFreeOnClose write FFreeOnClose;
  end;

implementation
uses fAttachmentFrame, wsRes;

{$R *.DFM}

const
  _TaskTabIndex = 1;
  _WorkflowTabIndex = 2;
  _FieldTabIndex = 3;
  _TaskLogIndex = 4;

  _MaxFixedTab = 4;

{ TfmTaskList }

procedure TfmTaskList.LoadData;
begin
  lvTasks.LoadFromDatabase;
  if lvTasks.SelectedTask = nil then
  begin
    if lvTasks.Items.Count > 0 then
      lvTasks.Items.Item[0].Selected := true
    else
      lvTasksSelectItem(nil, nil, false);
  end;
end;

procedure TfmTaskList.UpdateActivePage;
var
  AFrame: TfrAttachmentFrame;
begin
  if FUpdatingTabs = 0 then
  begin
    if (TabControl1.TabIndex = -1) and (TabControl1.Tabs.Count > 0) then
    begin
      TabControl1.TabIndex := 0;
    end;

    if TabControl1.TabIndex > -1 then
      {$WARNINGS OFF}
      Case integer(TabControl1.Tabs.Objects[TabControl1.TabIndex]) of
      {$WARNINGS ON}
        _TaskTabIndex:
          begin
            frTaskView.BringToFront;
          end;
        _WorkflowTabIndex:
          begin
            //WorkflowDiagram1.Visible := true;
            TControl(WorkflowDiagram1).BringToFront;
            WorkflowDiagram1.MakeActiveNodeVisible;
            //WorkflowDiagram1.SetFocus;
          end;
        _FieldTabIndex:
          begin
            FFieldPanel.BringToFront;
          end;
        _TaskLogIndex:
          begin
            if lvTasks.SelectedTask <> nil then
              FLogView.FilterKey := lvTasks.SelectedTask.Key
            else
              FLogView.FilterKey := '';
            FLogView.LoadFromDatabase; 
            FLogView.BringToFront;
          end;
      else
        AFrame := TfrAttachmentFrame(TabControl1.Tabs.Objects[TabControl1.TabIndex]);
        AFrame.BringToFront;
      end;
  end;
end;

procedure TfmTaskList.UpdateWorkflowDiagram;
var
  AWorkIns: TWorkflowInstance;
begin
  if (lvTasks.SelectedTask <> nil) or (lvTasks.FilterType = tfWorkIns) then
  begin
    WorkflowDiagram1.BeginUpdate;
    try
      AWorkIns := GetWorkIns;
      AWorkIns.AssignToDiagram(WorkflowDiagram1, true);
      WorkflowDiagram1.DisplayTaskStatus := true;

      Case AWorkIns.Status of
        wsNotStarted:
          WorkflowDiagram1.ViewStateMode := vmStart;
        wsFinished, wsFinishedWithError:
          WorkflowDiagram1.ViewStateMode := vmEnd;
      else
          WorkflowDiagram1.ViewStateMode := vmRun;
      end;

      WorkflowDiagram1.TopRuler.Visible := false;
      WorkflowDiagram1.LeftRuler.Visible := false;
      WorkflowDiagram1.AutoPage := false;
      WorkflowDiagram1.AutoScroll := true;
      WorkflowDiagram1.PageLines.Visible := false;
      WorkflowDiagram1.State := dsView;
      WorkflowDiagram1.MakeActiveNodeVisible;
    finally
      WorkflowDiagram1.EndUpdate;
    end;
  end
  else
    WorkflowDiagram1.Clear;
end;

procedure TfmTaskList.FormCreate(Sender: TObject);
begin
  //frTaskView.OnTaskChanged := TaskEdited;
  FFieldPanel := TTaskFieldPanel.Create(Self);
  FFieldPanel.Parent := TabControl1;
  FFieldPanel.Align := alClient;

  FLogView := TTaskLogListView.Create(Self);
  FLogView.WorkflowStudio := FWorkflowStudio;
  FLogView.Parent := TabControl1;
  FLogView.Align := alClient;
  FLogView.FilterType := lfTaskIns;
  
  FUpdatingTabs := 0;
  frTaskView.Task := nil;

  {Create list view columns}
 { lvTasks.Columns.Clear;
  With lvTasks.Columns.Add do
  begin
    Caption := _str(SColumnKey);
    Width := 40;
  end;
  With lvTasks.Columns.Add do
  begin
    Caption := _str(SColumnName);
    Width := 100;
  end;
  With lvTasks.Columns.Add do
  begin
    Caption := '流程业务';//_str(SColumnWorkflow);
    Width := 100;
  end;
  With lvTasks.Columns.Add do
  begin
    Caption := _str(SColumnSubject);
    Width := 220;
  end;
  With lvTasks.Columns.Add do
  begin
    Caption := _str(SColumnStatus);
    Width := 100;
  end;
  With lvTasks.Columns.Add do
  begin
    Caption := _str(SColumnUser);
    Width := 100;
  end; }
end;

procedure TfmTaskList.SaveChanges;
var
  AAttach: TWorkflowAttachment;
  AWorkIns: TWorkflowInstance;
  lvItems: TAttachmentListView;
  c: integer;
begin
  if lvTasks.SelectedTask <> nil then
  begin
    {Get the workflowinstance related to the task}
    AWorkIns := GetWorkIns;
    {Sace the status}
     frTaskView.SaveEditorsInVar();
    {Save the attachments}
    {$WARNINGS OFF}
    for c := 0 to TabControl1.Tabs.Count - 1 do if integer(TabControl1.Tabs.Objects[c]) > _MaxFixedTab then
    {$WARNINGS ON}
    begin
      AAttach := AWorkIns.Diagram.Attachments.FindByName(TabControl1.Tabs[c]);
      if AAttach <> nil then
      begin
        lvItems := TfrAttachmentFrame(TabControl1.Tabs.Objects[c]).lvItems;
        if lvItems <> nil then
        begin
          AAttach.Items.WorkflowStudio := lvItems.Attachments.WorkflowStudio;
          AAttach.Items.Assign(lvItems.Attachments);
        end;
      end;
    end;

    {Save the fields}
    if FindTabByType(_FieldTabIndex) > -1 then
    begin
      if not FFieldPanel.ValidateValues then
      begin
        TabControl1.TabIndex := FindTabByType(_FieldTabIndex);
        TabControl1Change(TabControl1);
        if FFieldPanel.CanFocus then
          FFieldPanel.SetFocus;
        FFieldPanel.FocusLastError;
        ShowMessage(FFieldPanel.ErrorInfo.Msg);
        Abort;
        //raise EWorkflowException.Create(FFieldPanel.ErrorInfo.Msg);
      end;                                              
      FFieldPanel.SaveDiagramVariables(AWorkIns.Diagram);
    end;

    {Save the workflow instance}
    FWorkflowStudio.WorkflowManager.SaveWorkflowInstance(AWorkIns);

    {Save the task instance. WARNING - this should be done after any saving code, because
     it loads the workflowinstance and signal it (run it again). So, it must be executed
     after all processing so it gets the most up to date workflow instance object}
    FWorkflowStudio.TaskManager.SaveTaskInstance(lvTasks.SelectedTask);

    {From below, it's only visual stuff}                      

    {Reload the task list from database, in case it's not more in the list (for example,
     it might be completed}
    FWorkflowStudio.WorkflowManager.LoadWorkflowInstance(AWorkIns);   {重新加载才能更新流程图}
    LoadData;
    //lvTasks.LoadFromDatabase;
  end;
end;

procedure TfmTaskList.SetFilter(FilterType: TTaskFilterType;
  AFilter: string);
begin
  lvTasks.FilterType := FilterType;
  lvTasks.FilterKey := AFilter;
end;

procedure TfmTaskList.FormShow(Sender: TObject);
begin
  UpdateWorkflowDiagram;
  TabControl1.TabIndex := 0;
end;

procedure TfmTaskList.AddAttachmentTab(AAttach: TWorkflowAttachment; APermissions: TAttachmentPermissions);
var
  AFrame: TfrAttachmentFrame;
begin
  AFrame := TfrAttachmentFrame.Create(Self, FWorkflowStudio);
  AFrame.Align := alClient;
  AFrame.Visible := false;
  AFrame.Parent := TabControl1;
  TabControl1.Tabs.AddObject(AAttach.Name, AFrame);
  AFrame.Name := 'AttachFrame' + IntToStr(TabControl1.Tabs.Count);

  AFrame.lvItems.Attachments := AAttach.Items;
  {if the selected task is open, than allow normal permissions. Otherwise, cannot change attachments}
  if Assigned(lvTasks.SelectedTask) and not lvTasks.SelectedTask.Completed then
    AFrame.Permissions := APermissions
  else
    AFrame.Permissions := [];

  AFrame.SendToBack;
  AFrame.Visible := true;
end;

procedure TfmTaskList.UpdateAttachmentTabs;
var
  AWorkIns: TWorkflowInstance;
  c: integer;
begin
  {Delete the previous tabs}
  c := 0;
  while c < TabControl1.Tabs.Count do
  begin
    {$WARNINGS OFF}
    if integer(TabControl1.Tabs.Objects[c]) > _MaxFixedTab then
    {$WARNINGS ON}
    begin
      TfrAttachmentFrame(TabControl1.Tabs.Objects[c]).Free;
      TabControl1.Tabs.Delete(c);
    end else
      inc(c);
  end;

  if (lvTasks.SelectedTask <> nil) and (lvTasks.SelectedTask.TaskDef.ShowAttachments) then
  begin
    AWorkIns := GetWorkIns;
    for c := 0 to AWorkIns.Diagram.Attachments.Count - 1 do
      AddAttachmentTab(AWorkIns.Diagram.Attachments[c], lvTasks.SelectedTask.TaskDef.AttachmentPermissions);
  end;
end;

procedure TfmTaskList.UpdateFieldsTab;
var
  i: integer;
  MustShow: boolean;
  AWorkIns: TWorkflowInstance;
begin
  MustShow := (lvTasks.SelectedTask <> nil) and (lvTasks.SelectedTask.TaskDef.Fields.Count > 0);
  i := FindTabByType(_FieldTabIndex);

  {Create or destroy the tab, depending if it must be shown or not}
  if MustShow and (i = -1) then
    TabControl1.Tabs.InsertObject(2, _str(STabFields), TObject(_FieldTabIndex));
  if not MustShow and (i > -1) then
    TabControl1.Tabs.Delete(i);

  {update fields tab}
  if lvTasks.SelectedTask <> nil then
  begin
    FFieldPanel.Fields := lvTasks.SelectedTask.TaskDef.Fields;
    AWorkIns := GetWorkIns;
    FFieldPanel.LoadDiagramVariables(AWorkIns.Diagram);
  end;
  FFieldPanel.ReadOnly := not Assigned(lvTasks.SelectedTask) or lvTasks.SelectedTask.Completed;
end;

function TfmTaskList.FindTabByType(AType: integer): integer;
var
  c: integer;
begin
  result := -1;
  for c := 0 to TabControl1.Tabs.Count - 1 do
    {$WARNINGS OFF}
    if integer(TabControl1.Tabs.Objects[c]) = AType then
    {$WARNINGS ON}
    begin
      result := c;
      exit;
    end;
end;

procedure TfmTaskList.UpdateFixedTabs;
begin
  With TabControl1.Tabs do
  begin
    if FindTabByType(_TaskTabIndex) = -1 then
      InsertObject(0, _str(STabTask), TObject(_TaskTabIndex));
    if FindTabByType(_WorkflowTabIndex) = -1 then
      InsertObject(1, _str(STabWorkflow), TObject(_WorkflowTabIndex));
  end;
end;

procedure TfmTaskList.UpdateLogTab;
var
  i: integer;
begin
  With TabControl1.Tabs do
  begin
    i := FindTabByType(_TaskLogIndex);
    if i = - 1 then
      AddObject(_str(STabLog), TObject(_TaskLogIndex))
    else
      Move(i, TabControl1.Tabs.Count - 1);
  end;
end;

procedure TfmTaskList.FormDestroy(Sender: TObject);
begin
  if FWorkIns <> nil then
  begin
    FWorkIns.Free;
    FWorkIns := nil;
  end;
end;

function TfmTaskList.GetWorkIns: TWorkflowInstance;
begin
  {Check if WorkIns is already loaded}
  if FWorkIns <> nil then
  begin
    case lvTasks.FilterType of
      tfWorkIns:
        if FWorkIns.Key = lvTasks.FilterKey then
        begin
          result := FWorkIns;
          exit;
        end;
    else
      begin
        if (lvTasks.SelectedTask <> nil) and (FWorkIns.Key = lvTasks.SelectedTask.WorkInsKey) then
        begin
          result := FWorkIns;
          exit;
        end;
      end;
    end;
  end;

  {FWorkIns must be reloaded}
  if FWorkIns <> nil then
    FWorkIns.Free;

  FWorkIns := TWorkflowInstance.Create(nil, FWorkflowStudio);
  if lvTasks.FilterType = tfWorkIns then
    FWorkIns.Key := lvTasks.FilterKey {workInskey}
  else
    if lvTasks.SelectedTask <> nil then
      FWorkIns.Key := lvTasks.SelectedTask.WorkInsKey
    else
    begin
      FWorkIns.Free;
      FWorkIns := nil;
    end;

  FWorkflowStudio.WorkflowManager.LoadWorkflowInstance(FWorkIns);
  result := FWorkIns;
end;

procedure TfmTaskList.btSaveChangesClick(Sender: TObject);
begin
  SaveChanges;
end;

procedure TfmTaskList.WorkflowDiagram1Click(Sender: TObject);
begin
  WorkflowDiagram1.SetFocus;
end;

procedure TfmTaskList.TabControl1Change(Sender: TObject);
begin
  UpdateActivePage;
end;

procedure TfmTaskList.BeginUpdateTabs;
begin
  inc(FUpdatingTabs);
end;

procedure TfmTaskList.EndUpdateTabs;
begin
  dec(FUpdatingTabs);
end;

procedure TfmTaskList.lvTasksSelectItem(Sender: TObject; Item: TListItem;
  Selected: Boolean);
begin
  Timer1.Enabled := false;
  Timer1.Enabled := true;
end;

procedure TfmTaskList.Localize;
begin
  Self.Caption := _str('fmTaskList.Self.Caption');
  btSaveChanges.Caption := _str('fmTaskList.btSaveChanges.Caption');
  acShowOnlyOpen.Caption := _str('fmTaskList.acShowOnlyOpen.Caption');
  acShowAllTasks.Caption := _str('fmTaskList.acShowAllTasks.Caption');
  miView.Caption := _str('fmTaskList.miView.Caption');
end;

procedure TfmTaskList.Loaded;
begin
  inherited;
  Localize;
end;

procedure TfmTaskList.acShowOnlyOpenExecute(Sender: TObject);
begin
  lvTasks.CompletedState := 0;
  LoadData;
end;

procedure TfmTaskList.acShowOnlyOpenUpdate(Sender: TObject);
begin
  acShowOnlyOpen.Checked := lvTasks.CompletedState=0;
end;

procedure TfmTaskList.acShowAllTasksExecute(Sender: TObject);
begin
  lvTasks.CompletedState := 2;
  LoadData;
end;

procedure TfmTaskList.acShowAllTasksUpdate(Sender: TObject);
begin
  acShowAllTasks.Checked := lvTasks.CompletedState=2;
end;

procedure TfmTaskList.lvTasksCustomDrawItem(Sender: TCustomListView;
  Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
var
  ATask: TTaskInstance;
begin
  ATask := nil;
  if Item <> nil then
    ATask := lvTasks.TaskFromItem(Item);
  if ATask <> nil then
  begin
    if ATask.Completed then
      lvTasks.Canvas.Font.Color := clGray;
  end;
  DefaultDraw := true;
end;

procedure TfmTaskList.Timer1Timer(Sender: TObject);
begin
  Timer1.Enabled := false;
  if (not (csDestroying in ComponentState)) then
  begin
    {Save last active page name}
    if TabControl1.TabIndex > -1 then
      FLastActivePageName := TabControl1.Tabs[TabControl1.TabIndex];

    BeginUpdateTabs;
    try
      frTaskView.Task := lvTasks.SelectedTask;
      if lvTasks.SelectedTask <> nil then
        frTaskView.ExpirationDateTime := FWorkflowStudio.TaskManager.TaskExpirationDateTime(GetWorkIns, lvTasks.SelectedTask)
      else
        frTaskView.ExpirationDateTime := 0;

      UpdateWorkflowDiagram;
      UpdateAttachmentTabs;

      {The following methods *must* be called in that order}
      UpdateFixedTabs;
      UpdateFieldsTab;
      UpdateLogTab;

      if lvTasks.SelectedTask <> nil then
      begin
        {Recover the active page}
        TabControl1.TabIndex := TabControl1.Tabs.IndexOf(FLastActivePageName);
      end;
      btSaveChanges.Enabled := (lvTasks.SelectedTask <> nil) and not lvTasks.SelectedTask.Completed
        and lvTasks.SelectedTask.CanUpdate(FWorkflowStudio.UserManager.LoggedUserId, FWorkflowStudio);

    finally
      EndUpdateTabs;
    end;

    UpdateActivePage;
  end;
end;

procedure TfmTaskList.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if FFreeOnClose then
    Action := caFree;
end;

constructor TfmTaskList.Create(AOwner: TComponent; AWorkflowStudio: TWorkflowStudio);
begin
  inherited Create(AOwner);
  if AWorkflowStudio <> nil then
    FWorkflowStudio := AWorkflowStudio
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);

  WorkflowDiagram1.WorkflowStudio := FWorkflowStudio;
  lvTasks.WorkflowStudio := FWorkflowStudio;
end;

end.

