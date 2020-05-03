unit fLibItemEditor;

interface

uses
  Windows, Messages, SysUtils,
  {$IFDEF DELPHI6_LVL}
  Variants,
  {$ENDIF}
  Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, ExtDlgs, atDiagram;

type
  TfmLibItemEditor = class(TForm)
    gbIcon: TGroupBox;
    btLoadIcon: TButton;
    Bevel1: TBevel;
    gbData: TGroupBox;
    Label1: TLabel;
    edCaption: TEdit;
    Label3: TLabel;
    cbCategory: TComboBox;
    imIcon: TImage;
    btOk: TButton;
    btCancel: TButton;
    OpenPictureDialog1: TOpenPictureDialog;
    Label2: TLabel;
    cbLibrary: TComboBox;
    imDefault: TImage;
    procedure btLoadIconClick(Sender: TObject);
    procedure btOkClick(Sender: TObject);
    procedure btCancelClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure cbLibraryChange(Sender: TObject);
  private
    FLibraryManager: TDgrLibraryManager;
    function DrawIconFromBlock(AItem: TDgrLibraryItem): boolean;
    procedure LoadLibraries;
    procedure ValidateData;
    function GetSelectedLibrary: TDgrLibrary;
    procedure SetSelectedLibrary(const Value: TDgrLibrary);
    procedure SetLibraryManager(const Value: TDgrLibraryManager);
    property LibraryManager: TDgrLibraryManager read FLibraryManager write SetLibraryManager;
    property SelectedLibrary: TDgrLibrary read GetSelectedLibrary write SetSelectedLibrary;
  public
    procedure FormToLibItem(AItem: TDgrLibraryItem);
    procedure LibItemToForm(AItem: TDgrLibraryItem);
    class function EditLibraryItem(AItem: TDgrLibraryItem; ALibraryManager: TDgrLibraryManager; var ALibrary: TDgrLibrary): boolean;
  end;

implementation
uses
  DiagramUtils;

{$R *.dfm}

procedure TfmLibItemEditor.btCancelClick(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TfmLibItemEditor.btLoadIconClick(Sender: TObject);
begin
  if OpenPictureDialog1.Execute then
    imIcon.Picture.LoadFromFile(OpenPictureDialog1.FileName);
end;

procedure TfmLibItemEditor.btOkClick(Sender: TObject);
begin
  ValidateData;
  ModalResult := mrOk;
end;
                                                
class function TfmLibItemEditor.EditLibraryItem(AItem: TDgrLibraryItem; ALibraryManager: TDgrLibraryManager; var ALibrary: TDgrLibrary): boolean;
var
  AForm: TfmLibItemEditor;
begin
  AForm := TfmLibItemEditor.Create(Application);
  try
    AForm.LibraryManager := ALibraryManager;
    AForm.SelectedLibrary := ALibrary;
    AForm.LibItemToForm(AItem); 
    AForm.cbLibrary.Enabled := AItem.OwnerLibrary = nil;
    result := AForm.ShowModal = mrOk;
    if result then
    begin
      AForm.FormToLibItem(AItem);
      ALibrary := AForm.SelectedLibrary;
    end;
  finally
    AForm.Free;
  end;
end;

procedure TfmLibItemEditor.FormToLibItem(AItem: TDgrLibraryItem);
begin
  AItem.Caption := edCaption.Text;
  //AItem.DControlID := edID.Text;
  AItem.Category := cbCategory.Text;
  AItem.Glyph.Assign(imIcon.Picture);
end;

procedure TfmLibItemEditor.LibItemToForm(AItem: TDgrLibraryItem);
begin
  if AItem.OwnerLibrary <> nil then
    SelectedLibrary := AItem.OwnerLibrary;

  edCaption.Text := AItem.Caption;
  cbCategory.Text := AItem.Category;

  if AItem.Glyph.Bitmap.Empty then
  begin
    if not DrawIconFromBlock(AItem) then
      imIcon.Picture.Assign(imDefault.Picture);
  end
  else
    imIcon.Picture.Assign(AItem.Glyph);
end;

procedure TfmLibItemEditor.ValidateData;
begin
  if Trim(edCaption.Text) = '' then
  begin
    edCaption.SetFocus;
    raise Exception.Create('Caption field cannot not be empty.');
  end;
  if Trim(cbCategory.Text) = '' then
  begin
    cbCategory.SetFocus;
    raise Exception.Create('Category field cannot be empty.');
  end;
end;

procedure TfmLibItemEditor.LoadLibraries;
begin
  FLibraryManager.GetLibraryNames(cbLibrary.Items);
end;

function TfmLibItemEditor.GetSelectedLibrary: TDgrLibrary;
begin
  result := FLibraryManager.LibraryByName(cbLibrary.Text);
end;

procedure TfmLibItemEditor.SetSelectedLibrary(const Value: TDgrLibrary);
begin
  cbLibrary.ItemIndex := cbLibrary.Items.IndexOf(Value.LibraryName);
  cbLibraryChange(cbLibrary);
end;

procedure TfmLibItemEditor.SetLibraryManager(const Value: TDgrLibraryManager);
begin
  FLibraryManager := Value;
  LoadLibraries;
end;

procedure TfmLibItemEditor.FormShow(Sender: TObject);
begin
  if cbLibrary.ItemIndex >= 0 then
    edCaption.SetFocus;
end;

procedure TfmLibItemEditor.cbLibraryChange(Sender: TObject);
var
  i: integer;
  cat: string;
begin
  cbCategory.Items.Clear;
  if SelectedLibrary <> nil then
    for i:=0 to SelectedLibrary.Count-1 do
    begin
      cat := Trim(SelectedLibrary[i].Category);
      if (cat > '') and (cbCategory.Items.IndexOf(cat) < 0) then
        cbCategory.Items.Add(cat);
    end;
end;

function TfmLibItemEditor.DrawIconFromBlock(AItem: TDgrLibraryItem): boolean;
const
  ICONSIZE = 24;
var
  dgr: TatDiagram;
  str: TStringStream;
  i: integer;

  function FitBlockRect(AWidth, AHeight: number): TSquare;
  var
    x, y, x1, y1: double;
  begin
    if AWidth > AHeight then
    begin
      y := ICONSIZE / AWidth * AHeight;
      x := ICONSIZE;
    end
    else
    begin
      x := ICONSIZE / AHeight * AWidth;
      y := ICONSIZE;
    end;
    x1 := ICONSIZE / 2 - x / 2;
    y1 := ICONSIZE / 2 - y / 2;
    result := Square(x1, y1, x1 + x, y1 + y);
  end;

begin
  result := False;
  if AItem.Data > '' then
  begin
    dgr := TatDiagram.Create(Self);
    str := TStringStream.Create(AItem.Data);
    try
      dgr.Visible := False;
      dgr.Parent := Self;
      dgr.LoadFromStream(str, True);
      dgr.SetBounds(0, 0, ICONSIZE, ICONSIZE);
      for i:=dgr.DControlCount-1 downto 0 do
      begin
        if dgr.DControls[i] is TCustomDiagramBlock then
        begin
          with TCustomDiagramBlock(dgr.DControls[i]) do
            if (Width > 0) and (Height > 0) then
              BoundsRect := FitBlockRect(Width, Height);
          dgr.PaintToBitmap(imIcon.Picture.Bitmap);
          imIcon.Picture.Bitmap.Width := ICONSIZE+1;
          imIcon.Picture.Bitmap.Height := ICONSIZE+1;
          result := True;
          break;
        end;
      end;
    finally
      dgr.Free;
      str.Free;
    end;
  end;
end;

end.

