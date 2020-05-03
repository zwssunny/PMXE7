unit fScriptEditor;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, wsClasses, StdCtrls, wsBlocks, wsScripter;

type
  TfmScriptEditor = class(TForm)
    PageControl1: TPageControl;
    tsScript: TTabSheet;
    btCancel: TButton;
    btOk: TButton;
    mmSourceCode: TMemo;
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
  private
    FBlock: TWorkflowScriptBlock;
    procedure BlockToInterface;
    procedure InterfaceToBlock;
    procedure Localize;
  protected
    procedure Loaded; override;
  public
    function EditScriptBlock(ABlock: TWorkflowScriptBlock): boolean;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  end;

implementation
uses wsRes, wsMain;

{$R *.DFM}

{ TForm1 }

function TfmScriptEditor.EditScriptBlock(ABlock: TWorkflowScriptBlock): boolean;
begin
  FBlock := ABlock;
  BlockToInterface;
  result := ShowModal = mrOk;
  if result then
    InterfaceToBlock;
end;

procedure TfmScriptEditor.btOkClick(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TfmScriptEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmScriptEditor.BlockToInterface;
begin
  mmSourceCode.Lines.Text := FBlock.SourceCode;
end;

constructor TfmScriptEditor.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
end;

destructor TfmScriptEditor.Destroy;
begin
  inherited;
end;

procedure TfmScriptEditor.InterfaceToBlock;
begin
  FBlock.SourceCode := mmSourceCode.Lines.Text;
end;

procedure TfmScriptEditor.Localize;
begin
  Self.Caption := _str('fmScriptEditor.Self.Caption');
  tsScript.Caption := _str('fmScriptEditor.tsScript.Caption');
  btCancel.Caption := _str('fmScriptEditor.btCancel.Caption');
  btOk.Caption := _str('fmScriptEditor.btOk.Caption');
end;

procedure TfmScriptEditor.Loaded;
begin
  inherited;
  Localize;
end;

end.
