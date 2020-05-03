unit fDgrPageSettings;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, ComCtrls, atDiagram;

type
  TfmDgrPageSettings = class(TForm)
    PageControl1: TPageControl;
    tsPaper: TTabSheet;
    btOk: TButton;
    btCancel: TButton;
    Label1: TLabel;
    Shape1: TShape;
    cbPaperSize: TComboBox;
    Label2: TLabel;
    edWidth: TEdit;
    Label3: TLabel;
    edHeight: TEdit;
    lbUnit2: TLabel;
    lbUnit1: TLabel;
    Label4: TLabel;
    Shape2: TShape;
    imgLandscape: TImage;
    imgPortrait: TImage;
    rbPortrait: TRadioButton;
    rbLandscape: TRadioButton;
    Label5: TLabel;
    Shape3: TShape;
    lbMarginTop: TLabel;
    lbMarginLeft: TLabel;
    lbMarginBottom: TLabel;
    lbMarginRight: TLabel;
    lbUnit3: TLabel;
    lbUnit4: TLabel;
    lbUnit5: TLabel;
    lbUnit6: TLabel;
    edMarginTop: TEdit;
    edMarginLeft: TEdit;
    edMarginBottom: TEdit;
    edMarginRight: TEdit;
    procedure cbPaperSizeChange(Sender: TObject);
    procedure rbPortraitClick(Sender: TObject);
    procedure rbLandscapeClick(Sender: TObject);
    procedure btOkClick(Sender: TObject);
  private
    FDiagram: TatDiagram;
    function MMToDisplay(AMM: extended): string;
    function DisplayToMM(AValue: string): extended;
    procedure DiagramToForm;
    procedure FormToDiagram;
    procedure LoadPaperSize;
    procedure UpdateUnitLabels;
  public
    function EditPageSettings(ADiagram: TatDiagram): boolean;
  end;

implementation

{$R *.DFM}

procedure SwapValues(var A, B: extended);
var
  T: extended;
begin
  T := A;
  A := B;
  B := T;
end;

{ TfmDgrPageSettings }

procedure TfmDgrPageSettings.DiagramToForm;
var
  c: integer;
begin
  {load paper combo}
  for c := 0 to FDiagram.DPrinter.PaperCount - 1 do
  begin
    cbPaperSize.Items.AddObject(FDiagram.DPrinter.Papers[c].PaperName, FDiagram.DPrinter.Papers[c]);
    if FDiagram.PageSettings.PaperID = FDiagram.DPrinter.Papers[c].PaperID then
      cbPaperSize.ItemIndex := cbPaperSize.Items.Count - 1;
  end;

  with FDiagram.PageSettings do
  begin
    if Orientation = dpoLandscape then
      rbLandscape.Checked := true
    else
      rbPortrait.Checked := true;

    edMarginTop.Text := MMToDisplay(TopMargin);
    edMarginLeft.Text := MMToDisplay(LeftMargin);
    edMarginRight.Text := MMToDisplay(RightMargin);
    edMarginBottom.Text := MMToDisplay(BottomMargin);
  end;
  LoadPaperSize;
  UpdateUnitLabels;
end;

function TfmDgrPageSettings.EditPageSettings(ADiagram: TatDiagram): boolean;
begin
  result := false;
  if ADiagram <> nil then
  begin
    FDiagram := ADiagram;
    DiagramToForm;
    result := (ShowModal = mrOk);
  end;
end;

procedure TfmDgrPageSettings.FormToDiagram;
begin
  {load paper combo}
  if cbPaperSize.ItemIndex > -1 then
    FDiagram.PageSettings.ChangePaperID(TDiagramPrinterPaperInfo(cbPaperSize.Items.Objects[cbPaperSize.ItemIndex]).PaperID);

  {load orientation and margins}
  with FDiagram.PageSettings do
  begin
    if rbLandscape.Checked then
      Orientation := dpoLandscape
    else
      Orientation := dpoPortrait;


    TopMargin := DisplayToMM(edMarginTop.Text);
    LeftMargin := DisplayToMM(edMarginLeft.Text);
    RightMargin := DisplayToMM(edMarginRight.Text);
    BottomMargin := DisplayToMM(edMarginBottom.Text);
  end;
end;

procedure TfmDgrPageSettings.cbPaperSizeChange(Sender: TObject);
begin
  LoadPaperSize;
end;

procedure TfmDgrPageSettings.LoadPaperSize;
var
  PaperInfo: TDiagramPrinterPaperInfo;
  CalcWidth, CalcHeight: extended;
begin
  if cbPaperSize.ItemIndex <> -1 then
  begin
    PaperInfo := TDiagramPrinterPaperInfo(cbPaperSize.Items.Objects[cbPaperSize.ItemIndex]);

    CalcWidth := PaperInfo.PaperWidth;
    CalcHeight := PaperInfo.PaperHeight;
    if rbLandscape.Checked then
      SwapValues(CalcWidth, CalcHeight);
    edWidth.Text := MMToDisplay(CalcWidth);
    edHeight.Text := MMToDisplay(CalcHeight);
  end;
end;

function TfmDgrPageSettings.MMToDisplay(AMM: extended): string;
begin
  result := FormatFloat('0.##', FDiagram.MMToMeasUnit(AMM));
end;

procedure TfmDgrPageSettings.rbPortraitClick(Sender: TObject);
begin
  LoadPaperSize;
end;

procedure TfmDgrPageSettings.rbLandscapeClick(Sender: TObject);
begin
  LoadPaperSize;
end;

function TfmDgrPageSettings.DisplayToMM(AValue: string): extended;
begin
  result := FDiagram.MeasUnitToMM(StrToFloat(AValue));
end;

procedure TfmDgrPageSettings.btOkClick(Sender: TObject);
begin
  try
    FormToDiagram;
  except
    ModalResult := mrNone;
    raise;
  end;
end;

procedure TfmDgrPageSettings.UpdateUnitLabels;
var
  S: string;
begin
  S := FDiagram.UnitSymbol;
  lbUnit1.Caption := S;
  lbUnit2.Caption := S;
  lbUnit3.Caption := S;
  lbUnit4.Caption := S;
  lbUnit5.Caption := S;
  lbUnit6.Caption := S;
end;

end.
