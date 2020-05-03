unit wsDiagram;

interface

uses
  Classes, Messages, Windows, Graphics, atDiagram, LiveDiagram, wsClasses;

type
  TWorkflowDiagram = class(TCustomWorkflowDiagram)
  protected
    procedure DoSaveState; override;
    function DiagramStreamClass: TatDiagramClass; override;
    procedure DoBeforeExecuteNode(ANode: TCustomLiveBlock); override;
    procedure DoAfterExecuteNode(ANode: TCustomLiveBlock); override;
    procedure Loaded; override;
  public
    constructor Create(AOwner: TComponent); override;
    procedure SaveToStream(AStream: TStream; TextFormat: boolean = false); override;
    procedure LoadFromStream(AStream: TStream; TextFormat: boolean = false); override;
    property InternalUpdating;
  published
    property Variables;
    property Attachments;
    property WorkflowStudio;
    property DisplayTaskStatus;
  end;

  TWorkflowStreamDiagram = class(TWorkflowDiagram)
  private
    procedure WMNCPaint(var Message: TMessage); message WM_NCPAINT;
  protected
  public
    procedure PaintWindow(DC: HDC); override;
    constructor Create(Owner: TComponent); override;
  end;
  
implementation

uses
  wsBlocks;

{ TWorkflowDiagram }

constructor TWorkflowDiagram.Create(AOwner: TComponent);
begin
  inherited Create(AOwner); 
  SleepVisual := 0;
  MaximumIdle := 100;
  SnapGrid.Visible := true;
  SnapGrid.SnapToRuler := true;
  LeftRuler.Visible := true;
  TopRuler.Visible := true;
  Color := clWhite;
  HandlesStyle := hsVisio;
end;

function TWorkflowDiagram.DiagramStreamClass: TatDiagramClass;
begin
  result := TWorkflowStreamDiagram;
end;

procedure TWorkflowDiagram.DoAfterExecuteNode(ANode: TCustomLiveBlock);
begin
  inherited;
  if ANode is TCustomWorkflowBlock then
    if Assigned(WorkflowStudio.OnAfterExecuteNode) then
      WorkflowStudio.OnAfterExecuteNode(WorkflowStudio, TCustomWorkflowBlock(ANode));
end;

procedure TWorkflowDiagram.DoBeforeExecuteNode(ANode: TCustomLiveBlock);
begin
  inherited;
  if ANode is TCustomWorkflowBlock then
    if Assigned(WorkflowStudio.OnBeforeExecuteNode) then
      WorkflowStudio.OnBeforeExecuteNode(WorkflowStudio, TCustomWorkflowBlock(ANode));
end;

procedure TWorkflowDiagram.DoSaveState;
begin
//  if
  inherited DoSaveState;
end;

procedure TWorkflowDiagram.Loaded;
begin
  inherited;
  SleepVisual := 0;
end;

procedure TWorkflowDiagram.LoadFromStream(AStream: TStream;
  TextFormat: boolean);
var
  oldName: string;
begin
  if Owner <> nil then
  begin
    oldName := Owner.Name;
    Owner.Name := wsFormName;
  end;
  inherited LoadFromStream(AStream, TextFormat);
  if Owner <> nil then
    Owner.Name := oldName;
end;

procedure TWorkflowDiagram.SaveToStream(AStream: TStream;
  TextFormat: boolean);
var
  oldName: string;
begin
  if Owner <> nil then
  begin
    oldName := Owner.Name;
    Owner.Name := wsFormName;
  end;
  inherited SaveToStream(AStream, TextFormat);
  if Owner <> nil then
    Owner.Name := oldName;
end;

{ TWorkflowStreamDiagram }

constructor TWorkflowStreamDiagram.Create(Owner: TComponent);
begin
  inherited;
  SetBounds(0, 0, 0, 0);
end;

procedure TWorkflowStreamDiagram.PaintWindow(DC: HDC);
begin
end;

procedure TWorkflowStreamDiagram.WMNCPaint(var Message: TMessage);
begin
end;

end.
