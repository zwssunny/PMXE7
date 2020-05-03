unit DgrEditorActions;

{$I DIAGRAM.INC}

interface

uses                                  
  SysUtils, Classes, Forms, ComCtrls, Graphics, Controls, ExtCtrls,
  atDiagram, DiagramActns, DiagramExtra, ActnList, Dialogs, ImgList,
  DiagramUtils, ExtDlgs;

type
  TdmDgrEditorActions = class(TDataModule)
    ActionList1: TActionList;
    DiagramCut1: TDiagramCut;
    DiagramCopy1: TDiagramCopy;
    DiagramPaste1: TDiagramPaste;
    DiagramSelectAll1: TDiagramSelectAll;
    DiagramDelete1: TDiagramDelete;
    DiagramEditText1: TDiagramEditText;
    DiagramSetZoom1: TDiagramSetZoom;
    DiagramSetZoom2: TDiagramSetZoom;
    DiagramSetZoom3: TDiagramSetZoom;
    DiagramSetZoom4: TDiagramSetZoom;
    DiagramSetZoom5: TDiagramSetZoom;
    DiagramSetZoom6: TDiagramSetZoom;
    DiagramSetZoom7: TDiagramSetZoom;
    DiagramViewLeftRuler1: TDiagramViewLeftRuler;
    DiagramViewTopRuler1: TDiagramViewTopRuler;
    DiagramShapeColor1: TDiagramShapeColor;
    DiagramLineColor1: TDiagramLineColor;
    DiagramBlockPicture1: TDiagramBlockPicture;
    DiagramArrowShape1: TDiagramArrowShape;
    DiagramArrowShape2: TDiagramArrowShape;
    DiagramArrowShape3: TDiagramArrowShape;
    DiagramArrowShape4: TDiagramArrowShape;
    DiagramArrowShape5: TDiagramArrowShape;
    DiagramArrowShape6: TDiagramArrowShape;
    DiagramArrowShape7: TDiagramArrowShape;
    DiagramArrowShape8: TDiagramArrowShape;
    DiagramArrowShape9: TDiagramArrowShape;
    DiagramArrowShape10: TDiagramArrowShape;
    DiagramArrowShape11: TDiagramArrowShape;
    DiagramArrowShape12: TDiagramArrowShape;
    DiagramBringToFront1: TDiagramBringToFront;
    acHasSourceArrow: TAction;
    acNewDiagram: TAction;
    acOpenDiagram: TAction;
    acSaveDiagram: TAction;
    acPrintDiagram: TAction;
    acPreviewDiagram: TAction;
    DiagramSendToBack1: TDiagramSendToBack;
    DiagramControlFont1: TDiagramControlFont;
    DiagramGrid1: TDiagramGrid;
    DiagramGradientSetting1: TDiagramGradientSetting;
    DiagramShadow1: TDiagramShadow;
    DiagramUndoAction1: TDiagramUndoAction;
    DiagramRedoAction1: TDiagramRedoAction;
    acAutomaticNodes: TAction;
    ActionList2: TActionList;
    DiagramAlign1: TDiagramAlign;
    DiagramAlign2: TDiagramAlign;
    DiagramAlign3: TDiagramAlign;
    DiagramAlign4: TDiagramAlign;
    DiagramAlign5: TDiagramAlign;
    DiagramAlign6: TDiagramAlign;
    DiagramAlign7: TDiagramAlign;
    DiagramAlign8: TDiagramAlign;
    DiagramAlign9: TDiagramAlign;
    DiagramAlign10: TDiagramAlign;
    DiagramAlign11: TDiagramAlign;
    DiagramAlign12: TDiagramAlign;
    DiagramAlign14: TDiagramAlign;
    DiagramAlign15: TDiagramAlign;
    DiagramAlign16: TDiagramAlign;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    ImageList1: TImageList;
    ImageList2: TImageList;
    acCopyAsImage: TAction;
    acHasTargetArrow: TAction;
    acGroup: TAction;
    acUngroup: TAction;
    ActionList3: TActionList;
    acBold: TAction;
    acItalic: TAction;
    acUnderline: TAction;
    acAlignLeft: TAction;
    acAlignCenter: TAction;
    acAlignRight: TAction;
    acVertAlignTop: TAction;
    acVertAlignMiddle: TAction;
    acVertAlignBottom: TAction;
    ImageList3: TImageList;
    acPageSetup: TAction;
    acAddLibrary: TAction;
    acSaveDiagramAs: TAction;
    acBackgroundLoad: TAction;
    acBackgroundClear: TAction;
    OpenPictureDialog1: TOpenPictureDialog;
    procedure acHasSourceArrowUpdate(Sender: TObject);
    procedure acAutomaticNodesExecute(Sender: TObject);
    procedure acAutomaticNodesUpdate(Sender: TObject);
    procedure acHasSourceArrowExecute(Sender: TObject);
    procedure acPrintDiagramExecute(Sender: TObject);
    procedure acPreviewDiagramExecute(Sender: TObject);
    procedure acSaveDiagramExecute(Sender: TObject);
    procedure acOpenDiagramExecute(Sender: TObject);
    procedure acNewDiagramExecute(Sender: TObject);
    procedure acCopyAsImageExecute(Sender: TObject);
    procedure acGroupExecute(Sender: TObject);
    procedure acGroupUpdate(Sender: TObject);
    procedure acUngroupExecute(Sender: TObject);
    procedure acUngroupUpdate(Sender: TObject);
    procedure acBoldUpdate(Sender: TObject);
    procedure acBoldExecute(Sender: TObject);
    procedure acItalicUpdate(Sender: TObject);
    procedure acItalicExecute(Sender: TObject);
    procedure acUnderlineUpdate(Sender: TObject);
    procedure acUnderlineExecute(Sender: TObject);
    procedure acAlignLeftUpdate(Sender: TObject);
    procedure acAlignCenterUpdate(Sender: TObject);
    procedure acAlignRightUpdate(Sender: TObject);
    procedure acVertAlignTopUpdate(Sender: TObject);
    procedure acVertAlignMiddleUpdate(Sender: TObject);
    procedure acVertAlignBottomUpdate(Sender: TObject);
    procedure acAlignLeftExecute(Sender: TObject);
    procedure acAlignCenterExecute(Sender: TObject);
    procedure acAlignRightExecute(Sender: TObject);
    procedure acVertAlignTopExecute(Sender: TObject);
    procedure acVertAlignMiddleExecute(Sender: TObject);
    procedure acVertAlignBottomExecute(Sender: TObject);
    procedure acPageSetupExecute(Sender: TObject);
    procedure acAddLibraryExecute(Sender: TObject);
    procedure acAddLibraryUpdate(Sender: TObject);
    procedure acSaveDiagramUpdate(Sender: TObject);
    procedure acSaveDiagramAsExecute(Sender: TObject);
    procedure DataModuleCreate(Sender: TObject);
    procedure acBackgroundLoadExecute(Sender: TObject);
    procedure acBackgroundLoadUpdate(Sender: TObject);
    procedure acBackgroundClearUpdate(Sender: TObject);
    procedure acBackgroundClearExecute(Sender: TObject);
  private
    FDiagram: TatDiagram;
    FToolbar: TDiagramToolbar;
    FTabControl: TTabControl;
    FOnModified: TNotifyEvent;
    FModified: boolean;
    FOldFormClose: TCloseEvent;
    FOnSaveDiagram: TNotifyEvent;
    FLibManager: TDgrLibraryManager;
    FCurrentDiagramFileName: string;
    FNewDiagram: boolean;
    FOnFileNameChanged: TNotifyEvent;
    procedure SetDiagram(const Value: TatDiagram);
    procedure SetActionsDiagram(ActionList: TActionList);
    procedure DiagramModified(Sender: TObject);
    procedure SetModified(Value: boolean);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure TabControlChange(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    function FirstCellSelected: TTextCell;
    procedure SwitchSelectedFontStyle(AStyle: TFontStyle; AInclude: boolean);
    procedure SetSelectedAlignment(AAlign: TAlignment);
    procedure SetSelectedVertAlign(AAlign: TVertAlign);
    procedure SetCurrentDiagramFileName(const Value: string);
  public
    procedure PrepareDiagram;
    procedure PrepareForm(AForm: TForm);
    procedure PrepareCategoryTab(ATabControl: TTabControl; AToolbar: TDiagramToolbar);
    property Diagram: TatDiagram read FDiagram write SetDiagram;
    property LibManager: TDgrLibraryManager read FLibManager write FLibManager;
    property Modified: boolean read FModified;
    property CurrentDiagramFileName: string read FCurrentDiagramFileName write SetCurrentDiagramFileName;
    property OnModified: TNotifyEvent read FOnModified write FOnModified;
    property OnSaveDiagram: TNotifyEvent read FOnSaveDiagram write FOnSaveDiagram;
    property OnFileNameChanged: TNotifyEvent read FOnFileNameChanged write FOnFileNameChanged;
  end;

implementation

{$R *.dfm}

procedure TdmDgrEditorActions.acHasSourceArrowUpdate(Sender: TObject);
begin
  TAction(Sender).Enabled := FDiagram.SelectedLinkCount > 0;
end;

procedure TdmDgrEditorActions.SetActionsDiagram(ActionList: TActionList);
var
  c: integer;
begin
  for c := 0 to ActionList.ActionCount - 1 do
    if ActionList.Actions[c] is TDiagramAction then
      TDiagramAction(ActionList.Actions[c]).Diagram := FDiagram;
end;

procedure TdmDgrEditorActions.SetDiagram(const Value: TatDiagram);
begin
  if FDiagram <> Value then
  begin
    FDiagram := Value;
    FDiagram.OnModified := DiagramModified;
    SetActionsDiagram(ActionList1);
    SetActionsDiagram(ActionList2);
  end;
end;

procedure TdmDgrEditorActions.DiagramModified(Sender: TObject);
begin
  SetModified(True);
end;

procedure TdmDgrEditorActions.SetModified(Value: boolean);
begin
  if FModified <> Value then
  begin
    FModified := Value;
    if Assigned(FOnModified) then
      FOnModified(FDiagram);
  end;
end;

procedure TdmDgrEditorActions.acAutomaticNodesExecute(Sender: TObject);
begin
  acAutomaticNodes.Checked := not acAutomaticNodes.Checked;
  FDiagram.AutomaticNodes := acAutomaticNodes.Checked;
  FDiagram.Modified;
end;

procedure TdmDgrEditorActions.acAutomaticNodesUpdate(Sender: TObject);
begin
  acAutomaticNodes.Checked := FDiagram.AutomaticNodes;
end;

procedure TdmDgrEditorActions.acHasSourceArrowExecute(Sender: TObject);
begin
  //This line is needed to keep action active
end;

procedure TdmDgrEditorActions.acPrintDiagramExecute(Sender: TObject);
begin
  FDiagram.Print(true);
end;

procedure TdmDgrEditorActions.acPreviewDiagramExecute(Sender: TObject);
begin
  FDiagram.Preview;
end;

procedure TdmDgrEditorActions.acSaveDiagramExecute(Sender: TObject);
begin
  if FDiagram.EditingText then
    FDiagram.CloseEditor(True);
  if Assigned(FOnSaveDiagram) then
  begin
    FOnSaveDiagram(Sender);
    SetModified(False);
    FNewDiagram := False;
  end
  else
  begin
    SaveDialog1.FileName := CurrentDiagramFileName;
    if (CurrentDiagramFileName = '') and SaveDialog1.Execute then
      CurrentDiagramFileName := SaveDialog1.FileName;

    if CurrentDiagramFileName > '' then
    begin
      FDiagram.SaveToFile(CurrentDiagramFileName);
      SetModified(False);
      FNewDiagram := False;
    end;
  end;
end;

procedure TdmDgrEditorActions.acOpenDiagramExecute(Sender: TObject);
begin
  if OpenDialog1.Execute then
  begin
    if not FModified or (MessageDlg('忽略当前修改，打开新流程图?',
      mtInformation, [mbYes, mbNo], 0) = mrYes) then
    begin
      CurrentDiagramFileName := OpenDialog1.FileName;
      FDiagram.LoadFromFile(CurrentDiagramFileName);
      SetModified(False);
      FNewDiagram := False;
    end;
  end;
end;

procedure TdmDgrEditorActions.acNewDiagramExecute(Sender: TObject);
begin
  if not FModified or (MessageDlg('忽略当前修改，创建新流程图?',
    mtInformation, [mbYes, mbNo], 0) = mrYes) then
  begin
    CurrentDiagramFileName := '';
    FDiagram.Clear;
    SetModified(False);
    FNewDiagram := True;
  end;
end;

procedure TdmDgrEditorActions.acCopyAsImageExecute(Sender: TObject);
begin
  FDiagram.CopyBitmapToClipboard;
end;

procedure TdmDgrEditorActions.PrepareDiagram;
begin
  if FDiagram <> nil then
  begin
    FDiagram.ConnectionLineId := 'TDiagramLine';
  end;
end;

procedure TdmDgrEditorActions.PrepareCategoryTab(ATabControl: TTabControl; AToolbar: TDiagramToolbar);
var
  c: integer;
  SL: TStringList;
  ATab: string;
begin
  FTabControl := ATabControl;
  if FTabControl <> nil then
  begin
    SL := TStringList.Create;
    SL.Add('所有对象');
    try
      for c := 0 to RegDControlList.Count - 1 do
      begin
        ATab := RegDControlList[c].Category;
        if (ATab <> '') and (SL.IndexOf(ATab) = -1) then
          SL.Add(RegDControlList[c].Category);
      end;
      FTabControl.Tabs := SL;
    finally
      SL.Free;
    end;
    FTabControl.OnChange := TabControlChange;
    FToolbar := AToolbar;
  end;
end;

procedure TdmDgrEditorActions.TabControlChange(Sender: TObject);
begin
  if (FTabControl <> nil) and (FToolbar <> nil) then
  begin
    if (FTabControl.TabIndex = 0) or (FTabControl.Tabs.Count <= 0) then
      FToolbar.Category := ''
    else
      FToolbar.Category := FTabControl.Tabs[FTabControl.TabIndex];
  end;
end;

procedure TdmDgrEditorActions.PrepareForm(AForm: TForm);
begin
  if AForm <> nil then
  begin
    AForm.OnCloseQuery := FormCloseQuery;
    FOldFormClose := AForm.OnClose;
    AForm.OnClose := FormClose;
  end;
end;

procedure TdmDgrEditorActions.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
  if Assigned(FOldFormClose) then
    FOldFormClose(Sender, Action);
end;

procedure TdmDgrEditorActions.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
  if Modified then
  begin
    Case MessageDlg('把修改保存到当前流程图?', mtInformation,
      [mbYes, mbNo, mbCancel], 0) of
      mrYes:
        begin
          acSaveDiagram.Execute;
          CanClose := not Modified;
        end;
      mrNo:
        CanClose := true;
      mrCancel:
        CanClose := false;
    end;
  end else
    CanClose := true;
end;

procedure TdmDgrEditorActions.acGroupExecute(Sender: TObject);
begin
  FDiagram.GroupSelectedBlocks;
end;

procedure TdmDgrEditorActions.acGroupUpdate(Sender: TObject);
begin
  acGroup.Enabled := (FDiagram <> nil) and (FDiagram.SelectedCount(cfIgnoreMembers) > 1);
end;

procedure TdmDgrEditorActions.acUngroupExecute(Sender: TObject);
begin
  FDiagram.UngroupSelectedBlocks;
end;

procedure TdmDgrEditorActions.acUngroupUpdate(Sender: TObject);
var
  c: integer;
  Ok: boolean;
begin
  Ok := false;
  if FDiagram <> nil then
    for c := 0 to FDiagram.SelectedCount - 1 do
      if FDiagram.Selecteds[c].IsGroup and not FDiagram.Selecteds[c].IsMember then
      begin
        Ok := true;
        break;
      end;
  acUngroup.Enabled := Ok;
end;

function TdmDgrEditorActions.FirstCellSelected: TTextCell;
var
  AControl: TDiagramControl;
begin
  result := nil;
  if (FDiagram <> nil) then
  begin
    if FDiagram.EditingText then
      result := FDiagram.EditingCell
    else
    if (FDiagram.SelectedCount > 0) then
    begin
      AControl := FDiagram.Selecteds[0];
      while AControl.IsGroup and (TGroupBlock(AControl).Members.Count > 0) do
        AControl := TGroupBlock(AControl).Members[0].DControl;
      if (AControl <> nil) and (AControl.HasDefaultTextCell) then
        result := AControl.DefaultTextCell;

      if not result.Visible then
      begin
        repeat
          result := AControl.SelectNextCell(result, true);
        until (result.Visible) or (result = AControl.DefaultTextCell);
      end;
    end;
  end;
end;

procedure TdmDgrEditorActions.SwitchSelectedFontStyle(AStyle: TFontStyle; AInclude: boolean);

  procedure _SwitchStyle(AFont: TFont);
  begin
    if AInclude then
      AFont.Style := AFont.Style + [AStyle]
    else
      AFont.Style := AFont.Style - [AStyle];
  end;

var
  c: integer;
  d: integer;
begin
  with FDiagram do
    if EditingText then
      _SwitchStyle(EditingCell.Font)
    else
      for c := 0 to SelectedCount - 1 do if not Selecteds[c].IsGroup then
      begin
        _SwitchStyle(Selecteds[c].Font);
        for d := 0 to Selecteds[c].TextCells.Count - 1 do
          if not Selecteds[c].TextCells[d].DControlFont then
            _SwitchStyle(Selecteds[c].TextCells[d].Font);
      end;
end;

procedure TdmDgrEditorActions.SetSelectedAlignment(AAlign: TAlignment);
var
  c: integer;
  d: integer;
begin
  with FDiagram do
    if EditingText then
      EditingCell.Alignment := AAlign
    else
      for c := 0 to SelectedCount - 1 do if not Selecteds[c].IsGroup then
      begin
        for d := 0 to Selecteds[c].TextCells.Count - 1 do
          Selecteds[c].TextCells[d].Alignment := AAlign;
      end;
end;

procedure TdmDgrEditorActions.SetSelectedVertAlign(AAlign: TVertAlign);
var
  c: integer;
  d: integer;
begin
  with FDiagram do
    if EditingText then
      EditingCell.VertAlign := AAlign
    else
      for c := 0 to SelectedCount - 1 do if not Selecteds[c].IsGroup then
      begin
        for d := 0 to Selecteds[c].TextCells.Count - 1 do
          Selecteds[c].TextCells[d].VertAlign := AAlign;
      end;
end;

procedure TdmDgrEditorActions.acBoldUpdate(Sender: TObject);
begin
  acBold.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acBold.Checked := (FirstCellSelected <> nil) and (fsBold in FirstCellSelected.Font.Style);
end;

procedure TdmDgrEditorActions.acBackgroundClearExecute(Sender: TObject);
begin
  with FDiagram.Background do
  begin
    if Picture <> nil then
      Picture.Assign(nil);
    if Bitmap <> nil then
      Bitmap.Assign(nil)
  end;
end;

procedure TdmDgrEditorActions.acBackgroundClearUpdate(Sender: TObject);
begin
  if FDiagram <> nil then
  begin
    with FDiagram.Background do
    begin
      acBackgroundClear.Enabled :=
        ((Picture <> nil) and (Picture.Width > 0) and (Picture.Height > 0)) or
        ((Bitmap <> nil) and not Bitmap.Empty);
    end;
  end
  else
    acBackgroundClear.Enabled := False;
end;

procedure TdmDgrEditorActions.acBackgroundLoadExecute(Sender: TObject);
begin
  if OpenPictureDialog1.Execute then
  begin
    FDiagram.Background.Picture.LoadFromFile(OpenPictureDialog1.FileName);
    FDiagram.Background.Visible := True;
  end;
end;

procedure TdmDgrEditorActions.acBackgroundLoadUpdate(Sender: TObject);
begin
  acBackgroundLoad.Enabled := FDiagram <> nil;
end;

procedure TdmDgrEditorActions.acBoldExecute(Sender: TObject);
begin
  SwitchSelectedFontStyle(fsBold, not acBold.Checked);
end;

procedure TdmDgrEditorActions.acItalicUpdate(Sender: TObject);
begin
  acItalic.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acItalic.Checked := (FirstCellSelected <> nil) and (fsItalic in FirstCellSelected.Font.Style);
end;

procedure TdmDgrEditorActions.acItalicExecute(Sender: TObject);
begin
  SwitchSelectedFontStyle(fsItalic, not acItalic.Checked);
end;

procedure TdmDgrEditorActions.acUnderlineUpdate(Sender: TObject);
begin
  acUnderline.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acUnderline.Checked := (FirstCellSelected <> nil) and (fsUnderline in FirstCellSelected.Font.Style);
end;

procedure TdmDgrEditorActions.acUnderlineExecute(Sender: TObject);
begin
  SwitchSelectedFontStyle(fsUnderline, not acUnderline.Checked);
end;

procedure TdmDgrEditorActions.acAlignLeftUpdate(Sender: TObject);
begin
  acAlignLeft.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acAlignLeft.Checked := (FirstCellSelected <> nil) and (FirstCellSelected.Alignment = taLeftJustify);
end;

procedure TdmDgrEditorActions.acAlignLeftExecute(Sender: TObject);
begin
  SetSelectedAlignment(taLeftJustify);
end;

procedure TdmDgrEditorActions.acAlignCenterUpdate(Sender: TObject);
begin
  acAlignCenter.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acAlignCenter.Checked := (FirstCellSelected <> nil) and (FirstCellSelected.Alignment = taCenter);
end;

procedure TdmDgrEditorActions.acAlignCenterExecute(Sender: TObject);
begin
  SetSelectedAlignment(taCenter);
end;

procedure TdmDgrEditorActions.acAlignRightUpdate(Sender: TObject);
begin
  acAlignRight.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acAlignRight.Checked := (FirstCellSelected <> nil) and (FirstCellSelected.Alignment = taRightJustify);
end;

procedure TdmDgrEditorActions.acAlignRightExecute(Sender: TObject);
begin
  SetSelectedAlignment(taRightJustify);
end;

procedure TdmDgrEditorActions.acVertAlignTopUpdate(Sender: TObject);
begin
  acVertAlignTop.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acVertAlignTop.Checked := (FirstCellSelected <> nil) and (FirstCellSelected.VertAlign = vaTop);
end;

procedure TdmDgrEditorActions.acVertAlignTopExecute(Sender: TObject);
begin
  SetSelectedVertAlign(vaTop);
end;

procedure TdmDgrEditorActions.acVertAlignMiddleUpdate(Sender: TObject);
begin
  acVertAlignMiddle.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acVertAlignMiddle.Checked := (FirstCellSelected <> nil) and (FirstCellSelected.VertAlign = vaCenter);
end;

procedure TdmDgrEditorActions.acVertAlignMiddleExecute(Sender: TObject);
begin
  SetSelectedVertAlign(vaCenter);
end;

procedure TdmDgrEditorActions.acVertAlignBottomUpdate(Sender: TObject);
begin
  acVertAlignBottom.Enabled := (FDiagram <> nil) and (FirstCellSelected <> nil);
  acVertAlignBottom.Checked := (FirstCellSelected <> nil) and (FirstCellSelected.VertAlign = vaBottom);
end;

procedure TdmDgrEditorActions.acVertAlignBottomExecute(Sender: TObject);
begin
  SetSelectedVertAlign(vaBottom);
end;

procedure TdmDgrEditorActions.acPageSetupExecute(Sender: TObject);
begin
  FDiagram.PageSetupDlg;
end;

procedure TdmDgrEditorActions.acAddLibraryExecute(Sender: TObject);
begin
  if FDiagram.Selecteds[0].IsMember then
    FLibManager.CreateItemDlg(FDiagram.Selecteds[0].MasterGroup)
  else
    FLibManager.CreateItemDlg(FDiagram.Selecteds[0]);
  FDiagram.RefreshToolbars;
end;

procedure TdmDgrEditorActions.acAddLibraryUpdate(Sender: TObject);
begin
  acAddLibrary.Enabled := (FLibManager <> nil) and (FDiagram <> nil) and
    (FDiagram.SelectedCount(cfIgnoreMembers) = 1);
end;

procedure TdmDgrEditorActions.acSaveDiagramUpdate(Sender: TObject);
begin
  acSaveDiagram.Enabled := FModified or FNewDiagram;
end;

procedure TdmDgrEditorActions.acSaveDiagramAsExecute(Sender: TObject);
begin
  if FDiagram.EditingText then
    FDiagram.CloseEditor(True);
  if Assigned(FOnSaveDiagram) then
  begin
    FOnSaveDiagram(Sender);
    SetModified(False);
    FNewDiagram := False;
  end
  else
  begin
    SaveDialog1.FileName := CurrentDiagramFileName;
    if SaveDialog1.Execute then
    begin
      CurrentDiagramFileName := SaveDialog1.FileName;
      FDiagram.SaveToFile(CurrentDiagramFileName);
      SetModified(False);
      FNewDiagram := False;
    end;
  end;
end;

procedure TdmDgrEditorActions.DataModuleCreate(Sender: TObject);
begin
  CurrentDiagramFileName := '';
  FNewDiagram := True;
end;

procedure TdmDgrEditorActions.SetCurrentDiagramFileName(const Value: string);
begin
  FCurrentDiagramFileName := Value;
  if Assigned(FOnFileNameChanged) then
    FOnFileNameChanged(Self);
end;

end.

