unit fMain;

{$I wsdefs.inc}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, atDiagram, ComCtrls, wsControls, wsMain, wsClasses, DB,
  wsDB, ActnList, Menus,
  {$IFDEF DELPHI9_LVL}
  XPMan,
  {$ENDIF}
  ImgList, ToolWin, ExtCtrls, System.Actions;

type
  TfmMain = class(TForm)
    WorkflowStudio1: TWorkflowStudio;
    MainMenu1: TMainMenu;
    ActionList1: TActionList;
    acDefinitions: TAction;
    Workflow1: TMenuItem;
    Editworkflowdefinitions1: TMenuItem;
    ImageList1: TImageList;
    ToolBar1: TToolBar;
    ToolButton1: TToolButton;
    ToolButton2: TToolButton;
    cbUser: TComboBox;
    acTasks: TAction;
    ToolButton3: TToolButton;
    Showtasksforcurrentuser1: TMenuItem;
    tmWorkflowTimeout: TTimer;
    Button1: TButton;
    procedure FormCreate(Sender: TObject);
    procedure acDefinitionsExecute(Sender: TObject);
    procedure acTasksExecute(Sender: TObject);
    procedure cbUserClick(Sender: TObject);
    procedure tmWorkflowTimeoutTimer(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
    function SelectedUser: TWorkflowUser;
  public
    { Public declarations }
  end;

var
  fmMain: TfmMain;

implementation
uses fWorkflowEditor, fTaskList, {$IFDEF DELPHI6_LVL}dDBX, {$ENDIF}
  dADO;

{$R *.DFM}

procedure TfmMain.FormCreate(Sender: TObject);
var
  TmptpInformation: TFtpInformation;
begin
  dmADO := TdmADO.Create(Application);
  {$IFDEF DELPHI6_LVL}
  dmDBX := TdmDBX.Create(Application);
  {$ENDIF}

  {$IFDEF DELPHI6_LVL}
  WorkflowStudio1.WorkflowDB := dmDBX.WorkflowDBXDB1;
  {$ENDIF}
  WorkflowStudio1.WorkflowDB := dmADO.WorkflowAccAndSysDB1;
  //给ftp连接参数赋值
//   with WorkflowStudio1.FtpInformation do
   with TmptpInformation do
   begin
    HostName :='192.168.1.20';
	  UserName :='User';
	  Password :='123';
	  Root :='/';
	  SpaceName :='sunny例子帐套1002';
    FtpDirectory :='FlowAttachment';
	  Port :=22;
	  Passive :=True;
   end;
   WorkflowStudio1.FtpInformation := TmptpInformation;
  {Add users and groups}
  WorkflowStudio1.UserManager.LoadWorkflowUsers;
  WorkflowStudio1.UserManager.LoadWorkflowGroups;
  WorkflowStudio1.UserManager.LoadWorkflowJobs;
  WorkflowStudio1.UserManager.LoadWorkflowDepartments;

  {Add users and groups}
 { with WorkflowStudio1.UserManager do
  begin

    Users.Add('1', 'John', 'john@domain');
    Users.Add('2', 'Sarah', 'sarah@domain');
    Users.Add('3', 'Scott', 'scott@domain');
    Users.Add('4', 'Mario', 'mario@domain');
    Users.Add('5', 'Tina', 'tina@domain');

    With Groups.Add('managers') do
    begin
      UserIds.Add('1');
      UserIds.Add('2');
    end;
    With Groups.Add('programmers') do
    begin
      UserIds.Add('3');
      UserIds.Add('4');
      UserIds.Add('5');
    end;
  end; }

  {Fill user combo}
  WorkflowStudio1.UserManager.FillUserList(cbUser.Items, true);
  cbUser.ItemIndex := 0;
  cbUserClick(nil);
end;

procedure TfmMain.acDefinitionsExecute(Sender: TObject);
begin
  WorkflowStudio1.UserInterface.ShowWorkflowDefinitionsDlg;
end;

procedure TfmMain.acTasksExecute(Sender: TObject);
begin
  if SelectedUser <> nil then
    WorkflowStudio1.UserInterface.ShowUserTasksDlg(SelectedUser.UserId);
end;

procedure TfmMain.Button1Click(Sender: TObject);
var
workinskey: string;
AWorkIns: TWorkflowInstance;
AWorkDef: TWorkflowDefinition;
begin
  workinskey :='90D6693F-E5D6-437F-B2AE-97CE9616A817';
  AWorkDef := TWorkflowDefinition.Create(WorkflowStudio1);
  WorkflowStudio1.WorkflowManager.LoadWorkflowDefinition(workinskey,AWorkDef);
  AWorkIns :=TWorkflowInstance.Create(self,WorkflowStudio1);
  AWorkIns.AssignFromDiagram(AWorkDef.Diagram,false);
//  AWorkIns.Key := workinskey;
 // WorkflowStudio1.WorkflowDB.WorkflowInstanceLoad(AWorkIns);
  EditWorkflowInsDiagram(AWorkIns);
end;

function TfmMain.SelectedUser: TWorkflowUser;
begin
  result := nil;
  if (cbUser.ItemIndex >= 0) and (cbUser.Items.Objects[cbUser.ItemIndex] is TWorkflowUser) then
    result := TWorkflowUser(cbUser.Items.Objects[cbUser.ItemIndex]);
end;
                                          
procedure TfmMain.cbUserClick(Sender: TObject);
begin
  if SelectedUser <> nil then
    WorkflowStudio1.UserManager.LoggedUserId := SelectedUser.UserId;
end;                                                                        

procedure TfmMain.tmWorkflowTimeoutTimer(Sender: TObject);
begin
  WorkflowStudio1.WorkflowEngine.RunPendingWorkflowInstances;
end;

end.

