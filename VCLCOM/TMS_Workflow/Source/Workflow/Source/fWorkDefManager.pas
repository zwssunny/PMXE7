unit fWorkDefManager;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, wsControls, Buttons, ActnList, Menus, wsMain;

type
  TfmWorkDefManager = class(TForm)
    lvWorks: TWorkDefListView;
    btAdd: TSpeedButton;
    btEdit: TSpeedButton;
    btDelete: TSpeedButton;
    btRefresh: TSpeedButton;
    btRunNew: TSpeedButton;
    PopupMenu1: TPopupMenu;
    ActionList1: TActionList;
    acExport: TAction;
    acImport: TAction;
    Export1: TMenuItem;
    Import1: TMenuItem;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    procedure btAddClick(Sender: TObject);
    procedure btEditClick(Sender: TObject);
    procedure btDeleteClick(Sender: TObject);
    procedure btRefreshClick(Sender: TObject);
    procedure btRunNewClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure lvWorksEdited(Sender: TObject; Item: TListItem; var S: String);
    procedure lvWorksDblClick(Sender: TObject);
    procedure ItemSelectedUpdate(Sender: TObject);
    procedure acExportExecute(Sender: TObject);
    procedure acImportExecute(Sender: TObject);
  private
    FWorkflowStudio: TWorkflowStudio;
    procedure Localize;
    procedure ImportFile(AFileName: string);
  protected
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent; AWorkflowStudio: TWorkflowStudio); reintroduce;
  end;

implementation

uses
  wsRes, wsClasses, fWorkflowEditor;

{$R *.DFM}

procedure TfmWorkDefManager.btAddClick(Sender: TObject);
var
  ANewItem: TListItem;
  WorkDef: TWorkflowDefinition;
begin           
  ANewItem := lvWorks.AddWorkDefItem;
  WorkDef := lvWorks.WorkDefFromItem(ANewItem);
  FWorkflowStudio.WorkflowManager.SaveWorkflowDefinition(WorkDef);
  lvWorks.SelectItemByWorkDef(WorkDef);
  if lvWorks.Selected <> nil then
    lvWorks.Selected.EditCaption;
end;

procedure TfmWorkDefManager.btEditClick(Sender: TObject);
begin
  if Assigned(lvWorks.SelectedWorkDef) then
    EditWorkflowDefDiagram(lvWorks.SelectedWorkDef);
end;

procedure TfmWorkDefManager.btDeleteClick(Sender: TObject);
begin
  if Assigned(lvWorks.SelectedWorkDef) then
  begin
    if MessageDlg(_str(SConfirmDeleteWorkDef), 
      mtConfirmation, [mbYes, mbNo], 0) = mrYes then
    begin
      FWorkflowStudio.WorkflowManager.DeleteWorkflowDefinition(lvWorks.SelectedWorkDef);
      lvWorks.SelectedWorkDef.Free;
    end;
  end;
end;

procedure TfmWorkDefManager.btRefreshClick(Sender: TObject);
begin
  lvWorks.LoadFromDatabase;
end;

procedure TfmWorkDefManager.btRunNewClick(Sender: TObject);
var
  WorkIns: TWorkflowInstance;
(*  WDef: TWorkflowDefinition;
  i: integer;
  wvar: TWorkflowVariable;*)
begin
  if lvWorks.SelectedWorkDef <> nil then
  begin
    WorkIns := FWorkflowStudio.WorkflowManager.CreateWorkflowInstance(lvWorks.SelectedWorkDef);

(*    for i := 0 to WorkIns.Diagram.Variables.Count - 1 do
    begin
      wvar := WorkIns.Diagram.Variables.Items[i];
      wvar.Value := 500;
    end;*)

(* /* for( int i=0 ; i < wfi->Diagram->Variables->Count; i++ )
  {
	 wvar = wfi->Diagram->Variables->Items[i];
	 if( DataSet->FindField( wvar->Name ) )
	 {
	   wvar->Value = DataSet->FieldByName(wvar->Name)->Value;
	 }

  }*/*)


    FWorkflowStudio.WorkflowEngine.RunWorkflow(WorkIns);
  end;
end;

procedure TfmWorkDefManager.FormCreate(Sender: TObject);
begin
  lvWorks.LoadFromDatabase;
  if lvWorks.Items.Count > 0 then
    lvWorks.Selected := lvWorks.Items[0];
end;                                                        

procedure TfmWorkDefManager.lvWorksEdited(Sender: TObject; Item: TListItem;
  var S: String);
var
  WorkDef: TWorkflowDefinition;
begin
  WorkDef := lvWorks.WorkDefFromitem(Item);
  if WorkDef <> nil then
  begin
    WorkDef.Name := S;
    FWorkflowStudio.WorkflowManager.SaveWorkflowDefinition(WorkDef);
  end;
end;

procedure TfmWorkDefManager.lvWorksDblClick(Sender: TObject);
begin
  btEditClick(nil);  
end;

procedure TfmWorkDefManager.Localize;
begin
  Self.Caption := _str('fmWorkDefManager.Self.Caption');
  btAdd.Caption := _str('fmWorkDefManager.btAdd.Caption');
  btEdit.Caption := _str('fmWorkDefManager.btEdit.Caption');
  btDelete.Caption := _str('fmWorkDefManager.btDelete.Caption');
  btRefresh.Caption := _str('fmWorkDefManager.btRefresh.Caption');
  btRunNew.Caption := _str('fmWorkDefManager.btRunNew.Caption');
  acImport.Caption := _str('fmWorkDefManager.acImport.Caption');
  acExport.Caption := _str('fmWorkDefManager.acExport.Caption');
  OpenDialog1.Filter := _str('fmWorkDefManager.OpenDialog1.Filter');
  OpenDialog1.Title := _str('fmWorkDefManager.OpenDialog1.Title');
  SaveDialog1.Filter := _str('fmWorkDefManager.SaveDialog1.Filter');
  SaveDialog1.Title := _str('fmWorkDefManager.SaveDialog1.Title');
end;

procedure TfmWorkDefManager.Loaded;
begin
  inherited;
  Localize;
end;

procedure TfmWorkDefManager.ItemSelectedUpdate(Sender: TObject);
begin
  TAction(Sender).Enabled := lvWorks.SelectedWorkDef <> nil;
end;

procedure TfmWorkDefManager.acExportExecute(Sender: TObject);
var
  WorkDef: TWorkflowDefinition;
begin
  SaveDialog1.FileName := lvWorks.SelectedWorkDef.Name + SaveDialog1.DefaultExt;
  if SaveDialog1.Execute then
  begin
    WorkDef := TWorkflowDefinition.Create(FWorkflowStudio);
    try
      FWorkflowStudio.WorkflowManager.LoadWorkflowDefinition(lvWorks.SelectedWorkDef.Key, WorkDef);
      WorkDef.Diagram.SaveToFile(SaveDialog1.FileName);
    finally
      WorkDef.Free;
    end;
  end;
end;

procedure TfmWorkDefManager.ImportFile(AFileName: string);
var
  AWorkDefs: TWorkflowDefinitions;
  WorkName: string;
  i: integer;
  WorkDef: TWorkflowDefinition;
begin
  if FileExists(AFileName) then                            
  begin
    AWorkDefs := FWorkflowStudio.WorkflowManager.CreateWorkflowDefinitionList;
    try
      {Find an unique name for the workflow definition based on file name}
      WorkName := ChangeFileExt(ExtractFileName(AFileName), '');
      i := 1;
      while AWorkDefs.FindByName(WorkName) <> nil do
      begin
        WorkName := Format('%s (%d)', [ChangeFileExt(ExtractFileName(AFileName), ''), i]);
        inc(i);
      end;

      WorkDef := AWorkDefs.Add;
      WorkDef.Name := WorkName;
      WorkDef.Diagram.LoadFromFile(AFileName);
      FWorkflowStudio.WorkflowManager.SaveWorkflowDefinition(WorkDef);
    finally
      AWorkDefs.Free;
    end;
  end;
end;

procedure TfmWorkDefManager.acImportExecute(Sender: TObject);
var
  c: integer;
begin
  if OpenDialog1.Execute then
  begin
    for c := 0 to OpenDialog1.Files.Count - 1 do
      ImportFile(OpenDialog1.Files[c]);

    //Refresh list
    lvWorks.LoadFromDatabase;
  end;
end;

constructor TfmWorkDefManager.Create(AOwner: TComponent; AWorkflowStudio: TWorkflowStudio);
begin
  inherited Create(AOwner);
  if AWorkflowStudio <> nil then
    FWorkflowStudio := AWorkflowStudio
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);

  lvWorks.WorkflowStudio := FWorkflowStudio;
end;

end.

