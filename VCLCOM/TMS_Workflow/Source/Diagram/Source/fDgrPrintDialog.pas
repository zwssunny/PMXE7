unit fDgrPrintDialog;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, ExtCtrls;

type
  TfmDgrPrintDialog = class(TForm)
    btOk: TButton;
    btCancel: TButton;
    Label12: TGroupBox;
    Label4: TLabel;
    Label3: TLabel;
    lbType: TLabel;
    lbWhere: TLabel;
    cbPrinters: TComboBox;
    btProperties: TButton;
    Label1: TGroupBox;
    lbDescription: TLabel;
    rbAllPages: TRadioButton;
    rbPageNumbers: TRadioButton;
    edPageNumbers: TEdit;
    Label2: TGroupBox;
    lbCopies: TLabel;
    imgNoCollate: TImage;
    imgCollate: TImage;
    edCopies: TEdit;
    cbCollate: TCheckBox;
    UpDown1: TUpDown;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btPropertiesClick(Sender: TObject);
    procedure cbPrintersChange(Sender: TObject);
    procedure edPageNumbersChange(Sender: TObject);
    procedure rbPageNumbersClick(Sender: TObject);
  private
    { Private declarations }
    FOldIndex: integer;
  public
    { Public declarations }
  end;

implementation
uses
  atDiagram;

{$R *.dfm}

procedure TfmDgrPrintDialog.FormCreate(Sender: TObject);
begin
  SetWindowLong(edCopies.Handle, GWL_STYLE, GetWindowLong(edCopies.Handle, GWL_STYLE) or ES_NUMBER);
end;

procedure TfmDgrPrintDialog.FormShow(Sender: TObject);
begin
  cbPrinters.Items.Assign(DPrinters.Printers);
  cbPrinters.ItemIndex := DPrinters.PrinterIndex;
  cbPrintersChange(nil);
  FOldIndex := DPrinters.PrinterIndex;
end;

procedure TfmDgrPrintDialog.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  if ModalResult <> mrOk then
    DPrinters.PrinterIndex := FOldIndex;
end;

procedure TfmDgrPrintDialog.btPropertiesClick(Sender: TObject);
begin
  DPrinters.Printer.PropertiesDlg;
end;

procedure TfmDgrPrintDialog.cbPrintersChange(Sender: TObject);
begin
  DPrinters.PrinterIndex := cbPrinters.ItemIndex;
  lbType.Caption := DPrinters.Printer.DeviceName;
  lbWhere.Caption := DPrinters.Printer.Port;
end;

procedure TfmDgrPrintDialog.edPageNumbersChange(Sender: TObject);
begin
  if edPageNumbers.Text <> '' then
    rbPageNumbers.Checked := true
  else
    rbAllPages.Checked := true;
end;

procedure TfmDgrPrintDialog.rbPageNumbersClick(Sender: TObject);
begin
  if Visible and edPageNumbers.CanFocus then
    edPageNumbers.SetFocus;
end;

end.
