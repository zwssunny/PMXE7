program WorkflowDemo;

uses
  Vcl.Forms,
  dADO in 'dADO.pas' {dmADO: TDataModule},
  dDBX in 'dDBX.pas' {dmDBX: TDataModule},
  fMain in 'fMain.pas' {fmMain};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TfmMain, fmMain);
  Application.Run;
end.
