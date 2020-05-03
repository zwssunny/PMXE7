unit fDgrLibraryManagerEditor;

interface

uses
  Windows, Messages, SysUtils, {$IFDEF DELPHI6_LVL}Variants,{$ENDIF}
  Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, ToolWin, atDiagram, ActnList, ImgList, Menus, ExtCtrls,
  StdCtrls, Buttons;

type
  TDgrLibraryManagerEditor = class(TForm)
    ToolBar1: TToolBar;
    ActionList1: TActionList;
    acRemoveLibrary: TAction;
    ilActions: TImageList;
    acNewLibrary: TAction;
    PopupMenu1: TPopupMenu;
    Panel1: TPanel;
    cbLibrary: TComboBox;
    pnLibrary: TPanel;
    Splitter1: TSplitter;
    Panel3: TPanel;
    lvObject: TListView;
    ilObjects: TImageList;
    imDefault: TImage;
    btEditItem: TToolButton;
    btDeleteItem: TToolButton;
    acEditItem: TAction;
    acDeleteItem: TAction;
    Editobject1: TMenuItem;
    Deleteobject1: TMenuItem;
    btNewLibrary: TSpeedButton;
    btRemoveLibrary: TSpeedButton;
    btShowCategories: TToolButton;
    acShowCategories: TAction;
    procedure acRemoveLibraryUpdate(Sender: TObject);
    procedure acNewLibraryExecute(Sender: TObject);
    procedure acRemoveLibraryExecute(Sender: TObject);
    procedure cbLibraryChange(Sender: TObject);
    procedure acEditItemUpdate(Sender: TObject);
    procedure acDeleteItemUpdate(Sender: TObject);
    procedure acDeleteItemExecute(Sender: TObject);
    procedure lvObjectDblClick(Sender: TObject);
    procedure acEditItemExecute(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure lvObjectCompare(Sender: TObject; Item1, Item2: TListItem;
      Data: Integer; var Compare: Integer);
    procedure lvObjectColumnClick(Sender: TObject; Column: TListColumn);
    procedure acShowCategoriesExecute(Sender: TObject);
    procedure lvObjectKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    FCategoryColumnWidth: integer;
    FLibraryManager: TDgrLibraryManager;
    FSortByCategory: boolean;
    FDiagram: TatDiagram;
    function GetSelectedItem: TDgrLibraryItem;
    function GetSelectedLibrary: TDgrLibrary;
    procedure LoadLibraries;
    procedure LoadObjects;
    procedure ReloadItems;
    procedure SetLibraryManager(const Value: TDgrLibraryManager);
    procedure SetSelectedItem(const Value: TDgrLibraryItem);
    procedure SetSelectedLibrary(const Value: TDgrLibrary);
  public
    procedure Execute;
    procedure InitiateAction; override;
    property LibraryManager: TDgrLibraryManager read FLibraryManager write SetLibraryManager;
    property Diagram: TatDiagram read FDiagram write FDiagram;
    property SelectedItem: TDgrLibraryItem read GetSelectedItem write SetSelectedItem;
    property SelectedLibrary: TDgrLibrary read GetSelectedLibrary write SetSelectedLibrary;
  end;

implementation

uses
  fLibItemEditor;

{$R *.dfm}

{ TDgrLayerManager }

procedure TDgrLibraryManagerEditor.acNewLibraryExecute(Sender: TObject);
var
  ok: boolean;
  libName: string;
  lib: TDgrLibrary;
begin
  ok := False;
  while not ok do
  begin
   if InputQuery('创建新库', '请输入库名:', libName) then
    begin
      libName := Trim(libName);
      if libName = '' then
        MessageDlg('库名不能为空.', mtError, [mbOk], 0)
      else if LibraryManager.LibraryByName(libName) <> nil then
        MessageDlg(Format('库名 "%s" 已经存在.', [libName]), mtError, [mbOk], 0)
      else
        ok := True;
    end
    else
      exit;
  end;

  lib := LibraryManager.CreateLibrary(libName);
  LoadLibraries;
  SelectedLibrary := lib;
end;

procedure TDgrLibraryManagerEditor.acRemoveLibraryExecute(Sender: TObject);
var
  c: Integer;
begin
  if MessageDlg('删除库 "' + SelectedLibrary.LibraryName + '"吗?', mtWarning, [mbYes, mbNo], 0) = mrYes then
  begin
    for c := 0 to SelectedLibrary.Count - 1 do
      SelectedLibrary.Items[c].UnregisterItem;
    LibraryManager.DeleteLibrary(SelectedLibrary.LibraryName);
    LoadLibraries;
    LoadObjects;
    if FDiagram <> nil then
      FDiagram.RefreshToolbars;
  end;
end;

procedure TDgrLibraryManagerEditor.acRemoveLibraryUpdate(Sender: TObject);
begin
  acRemoveLibrary.Enabled := SelectedLibrary <> nil;
end;

procedure TDgrLibraryManagerEditor.Execute;
begin
  if LibraryManager <> nil then
  begin
    LoadLibraries;
    Show;
  end
  else
    raise Exception.Create('库管理器没有指定.');
end;

function TDgrLibraryManagerEditor.GetSelectedLibrary: TDgrLibrary;
begin
  result := LibraryManager.LibraryByName(cbLibrary.Text);
end;

procedure TDgrLibraryManagerEditor.LoadLibraries;
begin
  LibraryManager.GetLibraryNames(cbLibrary.Items);
  if cbLibrary.Items.Count > 0 then
  begin
    cbLibrary.ItemIndex := 0;
    cbLibraryChange(cbLibrary);
  end;
end;

procedure TDgrLibraryManagerEditor.SetLibraryManager(const Value: TDgrLibraryManager);
begin
  FLibraryManager := Value;
  FLibraryManager.LoadLibraries;
end;

procedure TDgrLibraryManagerEditor.cbLibraryChange(Sender: TObject);
begin
  LoadObjects;
end;

procedure TDgrLibraryManagerEditor.LoadObjects;
var
  i: integer;
  bmp: TBitmap;
begin
  lvObject.Items.BeginUpdate;
  try
    ilObjects.Clear;
    lvObject.Items.Clear;
    if SelectedLibrary <> nil then
    begin
      for i:=0 to SelectedLibrary.Count-1 do
      begin
        if SelectedLibrary[i].Glyph.Bitmap.Empty then
          bmp := imDefault.Picture.Bitmap
        else
          bmp := SelectedLibrary[i].Glyph.Bitmap;
        bmp.Width := ilObjects.Width;
        bmp.Height := ilObjects.Height;
        with lvObject.Items.Add do
        begin
          Caption := SelectedLibrary[i].Caption;
          Subitems.Add(SelectedLibrary[i].Category);
          Data := SelectedLibrary[i];
          ImageIndex := ilObjects.Add(bmp, nil);
        end;
      end;
    end;

    FSortByCategory := False;
    lvObject.AlphaSort;
    if lvObject.Items.Count > 0 then
      lvObject.Items[0].Selected := True;
  finally
    lvObject.Items.EndUpdate;
  end;
end;

procedure TDgrLibraryManagerEditor.SetSelectedLibrary(const Value: TDgrLibrary);
begin
  cbLibrary.ItemIndex := cbLibrary.Items.IndexOf(Value.LibraryName);
  cbLibraryChange(cbLibrary);
end;

procedure TDgrLibraryManagerEditor.acEditItemUpdate(Sender: TObject);
begin
  acEditItem.Enabled := SelectedItem <> nil;
end;

function TDgrLibraryManagerEditor.GetSelectedItem: TDgrLibraryItem;
begin
  if lvObject.Selected <> nil then
    result := TDgrLibraryItem(lvObject.Selected.Data)
  else
    result := nil;
end;

procedure TDgrLibraryManagerEditor.acDeleteItemUpdate(Sender: TObject);
begin
  acDeleteItem.Enabled := SelectedItem <> nil;
end;

procedure TDgrLibraryManagerEditor.acDeleteItemExecute(Sender: TObject);
begin
  if MessageDlg('Delete object "' + SelectedItem.Caption + '"?', mtConfirmation, [mbYes, mbNo], 0) = mrYes then
  begin
    SelectedLibrary.DeleteItem(SelectedItem);
    SelectedItem.UnregisterItem;
    ReloadItems;
    if FDiagram <> nil then
      FDiagram.RefreshToolbars;
  end;
end;

procedure TDgrLibraryManagerEditor.lvObjectDblClick(Sender: TObject);
begin
  if acEditItem.Enabled then
    acEditItem.Execute;
end;

procedure TDgrLibraryManagerEditor.lvObjectKeyDown(Sender: TObject;
  var Key: Word; Shift: TShiftState);
begin
  case Key of
    VK_F2:
      acEditItem.Execute;
    VK_DELETE:
      acDeleteItem.Execute;
  end;
end;

procedure TDgrLibraryManagerEditor.acEditItemExecute(Sender: TObject);
var
  obj: TDgrLibraryItem;
  lib: TDgrLibrary;
begin
  obj := SelectedItem;
  lib := SelectedLibrary;
  if TfmLibItemEditor.EditLibraryItem(obj, LibraryManager, lib) then
  begin
    obj.Save;
    ReloadItems;
    if FDiagram <> nil then
      FDiagram.RefreshToolbars;
  end;
end;

procedure TDgrLibraryManagerEditor.SetSelectedItem(const Value: TDgrLibraryItem);
begin
  lvObject.Selected := lvObject.FindData(0, Value, True, False);
end;

procedure TDgrLibraryManagerEditor.ReloadItems;
var
  obj: string;
  item: TListItem;
begin
  obj := SelectedItem.Caption;
  LibraryManager.ReloadLibrary(SelectedLibrary.LibraryName);
  LoadObjects;
  item := lvObject.FindCaption(0, obj, False, True, False);
  if item <> nil then
    item.Selected := True;
end;

procedure TDgrLibraryManagerEditor.FormShow(Sender: TObject);
begin
  LoadObjects;
end;

procedure TDgrLibraryManagerEditor.FormCreate(Sender: TObject);
begin
  FCategoryColumnWidth := 80;
  FSortByCategory := False;
end;

procedure TDgrLibraryManagerEditor.lvObjectCompare(Sender: TObject; Item1,
  Item2: TListItem; Data: Integer; var Compare: Integer);
var
  s1, s2: string;
begin
  if FSortByCategory then
  begin
    s1 := Item1.SubItems[0];
    s2 := Item2.SubItems[0];
  end
  else
  begin
    s1 := Item1.Caption;
    s2 := Item2.Caption;
  end;
  if s1 = s2 then
    Compare := 0
  else if s1 > s2 then
    Compare := 1
  else
    Compare := -1;
end;

procedure TDgrLibraryManagerEditor.lvObjectColumnClick(Sender: TObject; Column: TListColumn);
begin
  FSortByCategory := Column.Index = 1;
  lvObject.AlphaSort;
end;

procedure TDgrLibraryManagerEditor.acShowCategoriesExecute(Sender: TObject);
begin
  if btShowCategories.Down then
  begin
    lvObject.Columns[1].Width := FCategoryColumnWidth;
    lvObject.Columns[0].Width := lvObject.ClientWidth - FCategoryColumnWidth;
  end
  else
  begin
    FCategoryColumnWidth := lvObject.Columns[1].Width;
    lvObject.Columns[1].Width := 0;
    lvObject.Columns[0].Width := lvObject.ClientWidth;
  end;
end;

procedure TDgrLibraryManagerEditor.InitiateAction;
begin
  inherited;
  if (LibraryManager <> nil) and (LibraryManager.LibraryCount <> cbLibrary.Items.Count) then
    LoadLibraries
  else if (SelectedLibrary <> nil) and (SelectedLibrary.Count <> lvObject.Items.Count) then
    LoadObjects;
end;

end.

