unit fTransitionEditor;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, wsClasses, StdCtrls, atDiagram, wsBlocks;

type
  TfmTransitionEditor = class(TForm)
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    Label1: TLabel;
    cbTransition: TComboBox;
    btCancel: TButton;
    btOk: TButton;
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
  private
    { Private declarations }
    FSourceBlock: TCustomWorkflowBlock;
    FLine: TCustomDiagramLine;
    procedure TransitionToInterface;
    procedure InterfaceToTransition;
    procedure Localize;
  protected
    procedure Loaded; override;
  public
    { Public declarations }
    function EditTransition(ALine: TCustomDiagramLine): boolean;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

implementation
uses wsMain, wsRes;

{$R *.DFM}

{ TfmDecisionEditor }

function TfmTransitionEditor.EditTransition(ALine: TCustomDiagramLine): boolean;
begin
  result := false;
  FLine := ALine;
  if FLine.SourceLinkPoint.Anchor is TCustomWorkflowBlock then
    FSourceBlock := TCustomWorkflowBlock(FLine.SourceLinkPoint.Anchor)
  else
    exit;

  if not FSourceBlock.HasOutputList then
    exit;
    
  TransitionToInterface;
  result := ShowModal = mrOk;
  if result then
    InterfaceToTransition;
end;

procedure TfmTransitionEditor.btOkClick(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TfmTransitionEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmTransitionEditor.TransitionToInterface;
begin
  FSourceBlock.FillOutputList(cbTransition.Items);
  cbTransition.Items.Insert(0, '');
  cbTransition.ItemIndex := cbTransition.Items.IndexOf(FLine.DefaultTextCell.Text);
end;

constructor TfmTransitionEditor.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
end;

destructor TfmTransitionEditor.Destroy;
begin
  inherited;
end;

procedure TfmTransitionEditor.InterfaceToTransition;
begin
  FLine.DefaultTextCell.Text := cbTransition.Text;
end;

procedure TfmTransitionEditor.Localize;
begin
  Self.Caption := _str('fmTransitionEditor.Self.Caption');
  TabSheet1.Caption := _str('fmTransitionEditor.TabSheet1.Caption');
  Label1.Caption := _str('fmTransitionEditor.Label1.Caption');
  btCancel.Caption := _str('fmTransitionEditor.btCancel.Caption');
  btOk.Caption := _str('fmTransitionEditor.btOk.Caption');
end;

procedure TfmTransitionEditor.Loaded;
begin
  inherited;
  Localize;
end;

end.
