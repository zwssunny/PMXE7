unit fDecisionEditor;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, StdCtrls, wsClasses, wsBlocks;

type
  TfmDecisionEditor = class(TForm) 
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    Label1: TLabel;
    edCondition: TEdit;
    btCancel: TButton;
    btOk: TButton;
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
  private
    { Private declarations }
    FBlock: TWorkflowDecisionBlock;
    procedure BlockToInterface;
    procedure InterfaceToBlock;
    procedure Localize;
  protected
    procedure Loaded; override;
  public
    { Public declarations }
    function EditDecisionBlock(ABlock: TWorkflowDecisionBlock): boolean;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

implementation
uses wsMain, wsRes;

{$R *.DFM}

{ TForm1 }

function TfmDecisionEditor.EditDecisionBlock(ABlock: TWorkflowDecisionBlock): boolean;
begin
  FBlock := ABlock;
  BlockToInterface;
  result := ShowModal = mrOk;
  if result then
    InterfaceToBlock;
end;

procedure TfmDecisionEditor.btOkClick(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TfmDecisionEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmDecisionEditor.BlockToInterface;
begin
  edCondition.Text := FBlock.Condition;
end;

constructor TfmDecisionEditor.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
end;

destructor TfmDecisionEditor.Destroy;
begin
  inherited;
end;

procedure TfmDecisionEditor.InterfaceToBlock;
begin
  FBlock.Condition := edCondition.Text;
end;

procedure TfmDecisionEditor.Localize;
begin
  Self.Caption := _str('fmDecisionEditor.Self.Caption');
  TabSheet1.Caption := _str('fmDecisionEditor.TabSheet1.Caption');
  Label1.Caption := _str('fmDecisionEditor.Label1.Caption');
  btCancel.Caption := _str('fmDecisionEditor.btCancel.Caption');
  btOk.Caption := _str('fmDecisionEditor.btOk.Caption');
end;

procedure TfmDecisionEditor.Loaded;
begin
  inherited;
  Localize;
end;

end.
