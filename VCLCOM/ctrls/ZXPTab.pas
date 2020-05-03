{
 ---------------------------------------------------------------------
}
unit ZXPTab;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, XPButton,
  ExtCtrls, dialogs, ImgList;

type
  {Events}
  TZXPTabChangeEvent = procedure(Sender: TObject; NewTab: Integer;
    var AllowChange: Boolean) of object;
  TZXPTabCloseEvent = procedure(Sender: TObject; TabSelected: Integer;
    var AllowClose: Boolean) of object;
  TZXPTabClickEvent = procedure(Sender: TObject; TabClicked: Integer) of object;
  {Enums}
  TTabLayOut = (tlTop, tlBottom);
  TTabStyle = (tsRectangle, tsTrapezoid);

  TZXPTabSet = class;
  TZXPTabs = class;
  {-------------------------- Class TZXPTab ---------------------------}
  TZXPTab = class(TCollectionItem)
  private
    FTabs: TZXPTabs;
    FCaption: string;
    FSize, FStartPos, FOffStartPos: Integer;
    FImageIndex: TImageIndex;
    FCanClose: Boolean;
    FSelected: Boolean;
    FEnabled: Boolean;
    FVisible: Boolean;

    procedure SetImageIndex(const Value: TImageIndex);
    procedure SetCaption(const Value: string);
    procedure SetEnabled(const Value: Boolean);
    procedure SetVisible(const Value: Boolean);
  public
    property Size: Integer read FSize write FSize;
    property StartPos: Integer read FStartPos write FStartPos;
    property OffStartPos: Integer read FOffStartPos write FOffStartPos;
    property Selected: Boolean read FSelected write FSelected;
    constructor Create(Collection: TCollection); override;
    procedure Assign(Source: TPersistent); override;
  published
    property Caption: string read FCaption write SetCaption;
    property ImageIndex: TImageIndex read FImageIndex write SetImageIndex;
    property CanClose: Boolean read FCanClose write FCanClose;
    property Enabled: Boolean read FEnabled write SetEnabled;
    property Visible: Boolean read FVisible write SetVisible;
  end;
  {-------------------------- Class TZXPTabs ---------------------------}
  TZXPTabs = class(TCollection)
  private
    FTabSet: TZXPTabSet;
    function GetItem(Index: Integer): TZXPTab;
    procedure SetItem(Index: Integer; Value: TZXPTab);
  protected
    function GetOwner: TPersistent; override;
    procedure Update(Item: TCollectionItem); override;
  public
    constructor Create(Tabset: TZXPTabSet);
    function Add: TZXPTab;
    property Items[Index: Integer]: TZXPTab read GetItem write SetItem; default;
  end;
  {--------------------------- Class TZXPTabSet ---------------------------}
  TZXPTabSet = class(TCustomControl)
  private
    { Private objects}
    FPrevBtn: TTimerXPButton;
    FNextBtn: TTimerXPButton;
    FCloseBtn: TTimerXPButton;
    FImages: TCustomImageList;
    FTabsBitmap: TBitmap; {image cache}
    FNoteBook: TNotebook;

    {private variables}
      {count}
    FTabIndex: Integer; //Index of selected tab
    FLayOut: TTabLayOut;
    FTabChanged: Boolean;
    FAllowChange: Boolean;
    FBoldSelect: Boolean;
    FScrollable: Boolean;
    FTabStyle: TTabStyle;
    FEdgeWidth: Integer;
    FIndent: Integer;
    FInitializing: Boolean;
      {size}
    FTabHeight: Integer;
    FMargin: Integer;
    FScrollPos: Integer;
    FScrollSpeed: Integer;
      {colors}
    FSelectedColor: TColor;
    FUnselectedColor: TColor;
    FBackgroundColor: TColor;
    FSelectedFontColor: TColor;
    FUnSelectedFontColor: TColor;
    FHighLightColor, FShadowColor, FSaperatorColor: TColor;
    FDisabledColor: TColor;
    FDisabledFontColor: TColor;

    {private events}
    FOnChange: TZXPTabChangeEvent;
    FOnClose: TZXPTabCloseEvent;
    FOnTabClick: TZXPTabClickEvent;
    procedure NBPageChange(Sender: TObject);

    {property access methods}
    procedure SetSelectedColor(Value: TColor);
    procedure SetUnselectedColor(Value: TColor);
    procedure SetSelectedFontColor(Value: TColor);
    procedure SetUnselectedFontColor(Value: TColor);
    procedure SetBackgroundColor(Value: TColor);
    procedure SetMargin(Value: Integer);
    procedure SetTabIndex(Value: Integer);
    function GetTabsCount: Integer;
    procedure SetTabHeight(Value: Integer);
    procedure SetTabLayOut(Value: TTabLayOut);
    procedure SetBoldSelect(Value: Boolean);
    procedure SetScrollable(Value: Boolean);
    procedure SetHighlightColor(Value: TColor);
    procedure SetShadowColor(Value: TColor);
    procedure SetSaperatorColor(Value: TColor);
    procedure SetTabStyle(value: TTabStyle);
    procedure SetEdgeWidth(value: Integer);
    procedure SetIndent(value: Integer);
    procedure SetNoteBook(value: TNoteBook);
    procedure SetTabs(value: TZXPTabs);

    { private methods }
    procedure WMSize(var Message: TWMSize); message WM_SIZE;
    procedure CMSysColorChange(var Message: TMessage); message CM_SYSCOLORCHANGE;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
    procedure CMDesignHitTest(var Message: TCMDesignHitTest); message CM_DESIGNHITTEST;

    procedure PrevBtnClick(Sender: TObject);
    procedure NextBtnClick(Sender: TObject);
    procedure CloseBtnClick(Sender: TObject);
    procedure ClearAllSelectedState;
    procedure ScrollTabs(Offset: integer);

    procedure BuildTabImage(ACanvas: TCanvas);
    procedure DrawSelectedTab(ACanvas: TCanvas; ATab: TZXPTab);
    procedure DrawTab(ACanvas: TCanvas; ATab: TZXPTab);
    procedure SetButtonStat;
    procedure DrawTFirstTab(ACanvas: TCanvas);
    procedure DrawTTab(ACanvas: TCanvas; ATab: TZXPTab);
    procedure DrawTLastTab(ACanvas: TCanvas);
    procedure DrawTSelectedTab(ACanvas: TCanvas);
    procedure SetDisabledColor(const Value: TColor);
    procedure SetDisabledFontColor(const Value: TColor);
    procedure SetImages(const Value: TCustomImageList);

  protected
    { Protected declarations }
    FTabs: TZXPTabs;
    procedure CreateParams(var Params: TCreateParams); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); override;
    procedure Paint; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function AddTab(ACaption: string; AImageIndex: TImageIndex;
      ASelected: Boolean; CanClose: Boolean = true; Disabled: Boolean = false): Integer;
    procedure DeleteTab(AIndex: Integer);
    procedure ClearAllTabs;
    procedure ChangeTabCaption(AIndex: Integer; ACaption: string);
    procedure UpdateTabs;
    procedure CloseTab(AIndex: Integer);
    property Canvas;


  published
    { Published declarations }
    property Align;
    property Anchors;
    property BackgroundColor: TColor read FBackgroundColor write SetBackgroundColor default clBtnFace;
    property BoldSelect: Boolean read FBoldSelect write SetBoldSelect;
    property Color;
    property Constraints;
    property DragCursor;
    property DragKind;
    property DragMode;
    property DisabledColor: TColor read FDisabledColor write SetDisabledColor;
    property DisabledFontColor: TColor read FDisabledFontColor write SetDisabledFontColor;
    property Enabled;
    property EdgeWidth: Integer read FEdgeWidth write SetEdgeWidth;
    property Font;
    property HighlightColor: TColor read FHighlightColor write SetHighlightColor;
    property Indent: Integer read FIndent write SetIndent;
    property NoteBook: TNoteBook read FNoteBook write SetNoteBook;
    property ParentShowHint;
    property PopupMenu;
    property SaperatorColor: TColor read FSaperatorColor write SetSaperatorColor;
    property Scrollable: Boolean read FScrollable write SetScrollable;
    property ScrollSpeed: Integer read FScrollSpeed write FScrollSpeed default 20;
    property ShadowColor: TColor read FShadowColor write SetShadowColor;
    property ShowHint;
    property Margin: Integer read FMargin write SetMargin default 4;
    property SelectedColor: TColor read FSelectedColor write SetSelectedColor default clBtnFace;
    property SelectedFontColor: TColor read FSelectedFontColor write SetSelectedFontColor default clWindowText;
    property TabHeight: Integer read FTabHeight write SetTabHeight default 22;
    property TabIndex: Integer read FTabIndex write SetTabIndex default -1;
    property TabsCount: Integer read GetTabsCount;
    property Tabs: TZXPTabs read FTabs write SetTabs;
    property TabStyle: TTabStyle read FTabStyle write SetTabStyle;
    property UnselectedColor: TColor read FUnselectedColor write SetUnselectedColor default clWindow;
    property UnselectedFontColor: TColor read FUnselectedFontColor write SetUnselectedFontColor default clGray;
    property Visible;
    property OnChange: TZXPTabChangeEvent read FOnChange write FOnChange;
    property OnClose: TZXPTabCloseEvent read FOnClose write FOnClose;
    property OnTabClick: TZXPTabClickEvent read FOnTabClick write FOnTabClick;
    property LayOut: TTabLayOut read FLayOut write SetTabLayOut;
    property Images: TCustomImageList read FImages write SetImages;
  end;

procedure Register;


implementation
{$R ZVCLSR.RES }
uses Consts;
//------------------------------------------------------------------------------

procedure Register;
begin
  RegisterComponents('ZAdditional', [TZXPTabSet]);
end;
//------------------------------------------------------------------------------

function ParseDataField(sData: string; FieldNo: Integer): string;
var
  posi: Integer;
  c: Integer;
begin
  c := 1;
  posi := Pos('|', sData);
  if (posi = 0) then
  begin
    if (FieldNo = 1) then
    begin
      Result := sData;
      Exit;
    end
    else
    begin
      Result := '';
      Exit;
    end
  end
  else if (FieldNo = 1) then
  begin
    Result := Copy(sData, 1, posi - 1);
    Exit;
  end
  else
    while (posi > 0) do
    begin
      sData := Copy(sData, posi + 1, Length(sData) - posi + 1);
      posi := Pos('|', sData);
      if (c = FieldNo - 1) then break;
      inc(c);
    end;
  if (posi > 0) then
    sData := Copy(sData, 1, posi - 1);
  if (c = FieldNo - 1) then
  begin
    Result := sData;
    Exit;
  end
  else
  begin
    Result := '';
    Exit;
  end;
end;
//------------------------------------------------------------------------------
//todo:tabset create

constructor TZXPTabSet.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := [csCaptureMouse, csDoubleClicks, csOpaque];

  Width := 248;
  Height := 22;
  FLayOut := tlBottom;
  DoubleBuffered := true;
  FTabs := TZXPTabs.Create(Self);
  FTabsBitmap := TBitmap.Create;

  ControlStyle := ControlStyle + [csDesignInteractive, csClickEvents,
    csCaptureMouse, csAcceptsControls, csDoubleClicks];

  FTabStyle := tsTrapezoid;

  FPrevBtn := TTimerXPButton.Create(Self);
  FPrevBtn.Parent := Self;
  FPrevBtn.Caption := '';
  FPrevBtn.Width := 15;
  FPrevBtn.Height := 15;
  FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFT');
  FPrevBtn.Left := Width - FMargin - 15 * 3;
  FPrevBtn.OnClick := PrevBtnClick;
  FPrevBtn.TimeBtnState := FPrevBtn.TimeBtnState + [tbAllowTimer];
  FPrevBtn.ShowBorder := false;
  FNextBtn := TTimerXPButton.Create(Self);
  FNextBtn.Parent := Self;
  FNextBtn.Caption := '';
  FNextBtn.Width := 15;
  FNextBtn.Height := 15;
  FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHT');
  FNextBtn.Left := Width - FMargin - 15 * 2;
  FNextBtn.OnClick := NextBtnClick;
  FNextBtn.TimeBtnState := FNextBtn.TimeBtnState + [tbAllowTimer];
  FNextBtn.ShowBorder := false;

  FCloseBtn := TTimerXPButton.Create(Self);
  FCloseBtn.Parent := Self;
  FCloseBtn.Caption := '';
  FCloseBtn.Width := 15;
  FCloseBtn.Height := 15;
  FCloseBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBCLOSE');
  FCloseBtn.Left := Width - FMargin - 15;
  FCloseBtn.OnClick := CloseBtnClick;
  FCloseBtn.ShowBorder := false;
  FScrollable := true;

  if FLayOut = tlTop then
  begin
    FPrevBtn.Top := 3;
    FNextBtn.Top := 3;
    FCloseBtn.Top := 3;
  end
  else
  begin
    FPrevBtn.Top := 5;
    FNextBtn.Top := 5;
    FCloseBtn.Top := 5;
  end;

  { initialize default values }
  FMargin := 4;
  FEdgeWidth := 7;
  FIndent := 10;
  FScrollPos := 0;
  FSelectedColor := clBtnFace;
  FUnselectedColor := clWhite;
  FDisabledColor := clWhite;
  FDisabledFontColor := clGray;
  FBackgroundColor := $00E4E9EB;
  FSelectedFontColor := clWindowText;
  FUnselectedFontColor := clGray;
  FHighlightColor := clBtnShadow;
  FShadowColor := clBtnShadow;
  FSaperatorColor := clBtnShadow;
  ParentFont := true;
  Canvas.Font := Font;
  FTabsBitmap.Canvas.Font := Font;
  ScrollSpeed := 20;
  FTabChanged := true;
  FTabIndex := -1;
  if csDesigning in ComponentState then
  begin
    AddTab('Tab 1', -1, true);
  end;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.CreateParams(var Params: TCreateParams);
begin
  inherited CreateParams(Params);
  with Params.WindowClass do
    style := style and not (CS_VREDRAW or CS_HREDRAW);
end;
//------------------------------------------------------------------------------

destructor TZXPTabSet.Destroy;
begin
  if Assigned(FPrevBtn) then
    FPrevBtn.Free;
  if Assigned(FNextBtn) then
    FNextBtn.Free;
  if Assigned(FCloseBtn) then
    FCloseBtn.Free;
  if Assigned(FTabsBitmap) then
    FTabsBitmap.Free;
  FTabs.Free;
  inherited Destroy;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.PrevBtnClick(Sender: TObject);
begin
  ScrollTabs(FScrollSpeed);
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.NextBtnClick(Sender: TObject);
begin
  ScrollTabs(-FScrollSpeed);
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.CloseBtnClick(Sender: TObject);
var
  FAllowClose: Boolean;
begin
  FAllowClose := true;
  if Assigned(FOnClose) then
    FOnClose(Self, FTabIndex, FAllowClose);
  if FAllowClose then
  begin
    DeleteTab(FTabIndex);
  end;
end;
//------------------------------------------------------------------------------

function TZXPTabSet.AddTab(ACaption: string; AImageIndex: TImageIndex;
  ASelected: Boolean; CanClose: Boolean = true; Disabled: Boolean = false): Integer;
var
  ATab: TZXPTab;
begin
  ATab := FTabs.Add;
  ATab.Caption := ACaption;
  ATab.ImageIndex := AImageIndex;
  ATab.Selected := ASelected;
  ATab.CanClose := CanClose;
  ATab.Enabled := not Disabled;
  ATab.Visible := true;   //Visible as default
  FTabChanged := true;
  if ASelected then
    FTabIndex := FTabs.Count - 1
  else FTabIndex := -1;
  Invalidate;
  Result := FTabIndex;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.DeleteTab(AIndex: Integer);
begin
  if (AIndex <= FTabs.Count - 1) and (AIndex >= 0) then
  begin
    FTabs.Delete(AIndex);
    FTabChanged := true;
    if AIndex > 0 then FTabIndex := AIndex - 1
    else if FTabs.Count > 0 then
      FTabIndex := 0          //zws2005-02-02
    else FTabIndex := -1;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.ClearAllTabs;
begin
  FTabs.Clear;
  FTabChanged := true;
  Invalidate;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.BuildTabImage(ACanvas: TCanvas);
var
  TotalLen: Integer;
  ATabLen, ATextLen: Integer;
  i: Integer;
  ATab: TZXPTab;
  BmpRect: TRect;
begin
// TODO: BuildTabImage
  TotalLen := 0;
  ATabLen := 0;
  FTabsBitmap.Width := 0;
  FTabsBitmap.Height := 0;
  FTabsBitmap.FreeImage;
  if FTabs.Count <= 0 then
  begin
    Exit;
  end;
  inc(TotalLen, FIndent);
  {Calculate the bitmap}
  for i := 0 to FTabs.Count - 1 do
  begin
    ATab := FTabs.Items[i];
    ATabLen := FMargin;
    if (ATab.ImageIndex >= 0) and (FImages<> nil) and (FImages.HandleAllocated) then
    begin
      inc(ATabLen, 16 + FMargin); //Glyph
    end;
    ACanvas.Font := Font;
    if (ATab.Selected) and (FBoldSelect) and (FTabStyle = tsRectangle) then
      ACanvas.Font.Style := ACanvas.Font.Style + [fsBold]
    else
      ACanvas.Font.Style := ACanvas.Font.Style - [fsBold];
    ATextLen := ACanvas.TextWidth(ATab.Caption);

    inc(ATabLen, ATextLen + 2);
    inc(ATabLen, FMargin);
    if ATabLen > 300 then ATabLen := 300; //TODO: MAX LEN
    if ATab.Visible then
    begin
      ATab.StartPos := TotalLen;
      ATab.OffStartPos := ATab.StartPos + FScrollPos;
      if FTabStyle = tsRectangle then
        if (ATab.Selected) then
          ATab.StartPos := ATab.StartPos - 2;
      ATabLen := ATabLen + FEdgeWidth;
      if i = 0 then
        ATabLen := ATabLen + FEdgeWidth;
      ATab.Size := ATabLen;
    end
    else
    begin
      ATab.StartPos := -9999;
      ATab.OffStartPos := ATab.StartPos + FScrollPos;
      ATabLen := 0;
      ATab.Size := 0;
    end;
    inc(TotalLen, ATabLen);
  end;
  {Build the bitmap}
  FTabsBitmap.Width := TotalLen;
  FTabsBitmap.Height := Height;
  BmpRect.Left := 0;
  BmpRect.Top := 0;
  BmpRect.Right := FTabsBitmap.Width;
  BmpRect.Bottom := FTabsBitmap.Height;
  with FTabsBitmap do
  begin
    if FLayOut = tlTop then
    begin
      {backgound}
      Canvas.Brush.Color := FBackgroundColor;
      Canvas.FillRect(BmpRect);
      {bottom highlight line}
      Canvas.Pen.Color := FHighLightColor; //clBtnHighLight; //white
      Canvas.MoveTo(0, FTabsBitmap.Height - 3);
      Canvas.LineTo(FTabsBitmap.Width, FTabsBitmap.Height - 3);
      Canvas.Pen.Color := Color; //Silver
      Canvas.MoveTo(0, FTabsBitmap.Height - 2);
      Canvas.LineTo(FTabsBitmap.Width, FTabsBitmap.Height - 2);
      Canvas.MoveTo(0, FTabsBitmap.Height - 1);
      Canvas.LineTo(FTabsBitmap.Width, FTabsBitmap.Height - 1);
      {tabs}
      case FTabStyle of
        tsRectangle:
          for i := 0 to FTabs.Count - 1 do
          begin
            if not ATab.Visible then continue;
            ATab := FTabs.Items[i];
            if ATab.Selected then DrawSelectedTab(Canvas, ATab)
            else DrawTab(Canvas, ATab);
          end;
        tsTrapezoid:
          begin
          //DrawLastOne
            if FTabs.Count > 1 then
              DrawTLastTab(Canvas);
          //DrawMiddleOnes
            for i := FTabs.Count - 2 downto 1 do
            begin
              ATab := FTabs.Items[i];
              if not((i = 1) and (not FTabs.Items[0].Visible)) then
                DrawTTab(Canvas, ATab);
            end;
          //DrawFirstOne
            DrawTFirstTab(Canvas);
          //DrawHotOne
            DrawTSelectedTab(Canvas);
          end;
      end;
    end
    else
    begin
      {backgound}
      Canvas.Brush.Color := FBackgroundColor;
      Canvas.FillRect(BmpRect);
      {bottom highlight line}
      Canvas.Pen.Color := FShadowColor; //clWindowFrame; //DarkGray
      Canvas.MoveTo(0, 2);
      Canvas.LineTo(FTabsBitmap.Width, 2);
      Canvas.Pen.Color := Color;
      Canvas.MoveTo(0, 1);
      Canvas.LineTo(FTabsBitmap.Width, 1);
      Canvas.MoveTo(0, 0);
      Canvas.LineTo(FTabsBitmap.Width, 0);
      {tabs}
      case FTabStyle of
        tsRectangle:
          for i := 0 to FTabs.Count - 1 do
          begin
            ATab := Tabs.Items[i];
            if ATab.Selected then DrawSelectedTab(Canvas, ATab)
            else DrawTab(Canvas, ATab);
          end;
        tsTrapezoid:
          begin
          //DrawLastOne
            if FTabs.Count > 1 then
              DrawTLastTab(Canvas);
          //DrawMiddleOnes
            for i := FTabs.Count - 2 downto 1 do
            begin
              ATab := FTabs.Items[i];
              if not((i = 1) and (not FTabs.Items[0].Visible)) then
                DrawTTab(Canvas, ATab);
            end;
          //DrawFirstOne
            DrawTFirstTab(Canvas);
          //DrawHotOne
            DrawTSelectedTab(Canvas);
          end;
      end;
    end;
    SetButtonStat;
  end;
  FTabChanged := false;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.SetButtonStat;
var
  VisualWidth: integer;
  ATab: TZXPTab;
begin
  if FScrollable then
    VisualWidth := Width - FMargin * 2 - 45
  else
    VisualWidth := Width - FMargin;

  if FLayOut = tlTop then
  begin
    FPrevBtn.Top := 3;
    FNextBtn.Top := 3;
    FCloseBtn.Top := 3;
  end
  else
  begin
    FPrevBtn.Top := 5;
    FNextBtn.Top := 5;
    FCloseBtn.Top := 5;
  end;

  if FTabsBitmap.Width <= VisualWidth then
  begin
    ScrollTabs(-FScrollPos);
    Invalidate;
    FNextBtn.Enabled := false;
    FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHTDIS');
    FPrevBtn.Enabled := false;
    FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFTDIS');
  end
  else
    if (FScrollPos >= 0) then
    begin
      FNextBtn.Enabled := true;
      FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHT');
      FPrevBtn.Enabled := false;
      FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFTDIS');
    end
    else if FScrollPos < -(FTabsBitmap.Width - VisualWidth) then
    begin
      FNextBtn.Enabled := false;
      FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHTDIS');
      FPrevBtn.Enabled := true;
      FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFT');
    end
    else
    begin
      FNextBtn.Enabled := true;
      FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHT');
      FPrevBtn.Enabled := true;
      FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFT');
    end;
  if (FTabIndex >= 0) and (FTabIndex < FTabs.Count) then
  begin
    ATab := FTabs.Items[FTabIndex];
    if ATab.CanClose then
    begin
      FCloseBtn.Enabled := true;
      FCloseBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBCLOSE');
    end
    else
    begin
      FCloseBtn.Enabled := false;
      FCloseBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBCLOSEDIS');
    end;
  end;
  Invalidate;
end;
//------------------------------------------------------------------------------

procedure TZXPTabSet.DrawSelectedTab(ACanvas: TCanvas; ATab: TZXPTab);
var
  TabRect: TRect;
  ImageWidth: integer;
begin
  if FLayOut = tlTop then
  begin
    {Calculate tab rectangle}
    TabRect.Left := ATab.StartPos;
    TabRect.Right := ATab.StartPos + ATab.Size;
    TabRect.Top := 2;
    TabRect.Bottom := Height - 2;
    with ACanvas do
    begin
      {draw tab background}
      //选中的颜色  by hp
      if ATab.FSelected  then
        Brush.Color := FSelectedColor
      else
        Brush.Color := FDisabledColor;
      FillRect(TabRect);
      {draw 3D effects}
      Pen.Color := FHighLightColor; //clBtnHighLight;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left, TabRect.Bottom);
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Right, TabRect.Top);
      Pen.Color := FShadowColor; //Black;//clWindowFrame;
      MoveTo(TabRect.Right, TabRect.Top);
      LineTo(TabRect.Right, TabRect.Bottom);
      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated) then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          (TabRect.Bottom - TabRect.Top - 16) div 2 + TabRect.Top + 1, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left + ;
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      TabRect.Top := TabRect.Top;
      TabRect.Right := TabRect.Right - FMargin;
      if (FBoldSelect) and (FTabStyle = tsRectangle) then
        ACanvas.Font.Style := ACanvas.Font.Style + [fsBold]
      else
        ACanvas.Font.Style := ACanvas.Font.Style - [fsBold];
      if ATab.FSelected  then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end
  else
  begin
    {Calculate tab rectangle}
    TabRect.Left := ATab.StartPos;
    TabRect.Right := ATab.StartPos + ATab.Size;
    TabRect.Top := 2;
    TabRect.Bottom := Height - 2;
    with ACanvas do
    begin
      {draw tab background}
      if ATab.FSelected then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FSelectedColor;
      FillRect(TabRect);
      {draw 3D effects}
      Pen.Color := FHighLightColor;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left, TabRect.Bottom);
      Pen.Color := FShadowColor; // clWindowFrame;
      LineTo(TabRect.Right, TabRect.Bottom);
      LineTo(TabRect.Right, TabRect.Top);
      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top + 2, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left + ;
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      TabRect.Top := TabRect.Top + 2;
      TabRect.Right := TabRect.Right - FMargin;
      if (FBoldSelect) and (FTabStyle = tsRectangle) then
        ACanvas.Font.Style := ACanvas.Font.Style + [fsBold]
      else
        ACanvas.Font.Style := ACanvas.Font.Style - [fsBold];
      if ATab.FSelected then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.DrawTab(ACanvas: TCanvas; ATab: TZXPTab);
var
  TabRect: TRect;
  ImageWidth: integer;
begin
  {Calculate tab rectangle}
  TabRect.Left := ATab.StartPos;
  TabRect.Right := ATab.StartPos + ATab.Size - 1;
  if FLayOut = tlTop then TabRect.Top := 2
  else TabRect.Top := 3;
  TabRect.Bottom := Height - 3;
  with ACanvas do
  begin
    {draw tab background}
    if ATab.FSelected then
      Brush.Color := FDisabledColor
    else
      Brush.Color := FUnSelectedColor;
    FillRect(TabRect);
    {draw 3D effects}
    Pen.Color := FSaperatorColor;
    MoveTo(TabRect.Right, TabRect.Top + 1);
    LineTo(TabRect.Right, TabRect.Bottom - 1);
    {draw glyph, if assigned}
    if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
    begin
      if FLayOut = tlTop then
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top + 1, ATab.ImageIndex)
      else
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top + 2, ATab.ImageIndex);
      ImageWidth := 16;
    end
    else ImageWidth := 0;
    {draw caption}
    TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
    if ImageWidth > 0 then inc(TabRect.Left, FMargin);
//    if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
    if FLayOut = tlTop then TabRect.Top := TabRect.Top + 2
    else TabRect.Top := TabRect.Top + 2;
    TabRect.Right := TabRect.Right - FMargin;
    TabRect.Bottom := TabRect.Bottom;
    ACanvas.Font.Style := ACanvas.Font.Style - [fsBold];
    if ATab.FSelected then
      ACanvas.Font.Color := FDisabledFontColor
    else
      ACanvas.Font.Color := FUnSelectedFontColor;
    DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetSelectedColor(Value: TColor);
begin
  if value <> FSelectedColor then
  begin
    FSelectedColor := value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetUnSelectedColor(Value: TColor);
begin
  if value <> FUnSelectedColor then
  begin
    FUnSelectedColor := value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetSelectedFontColor(Value: TColor);
begin
  if value <> FSelectedFontColor then
  begin
    FSelectedFontColor := value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetUnSelectedFontColor(Value: TColor);
begin
  if value <> FUnSelectedFontColor then
  begin
    FUnSelectedFontColor := value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetDisabledColor(const Value: TColor);
begin
  if value <> FDisabledColor then
  begin
    FDisabledColor := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetDisabledFontColor(const Value: TColor);
begin
  if value <> FDisabledFontColor then
  begin
    FDisabledFontColor := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetBackgroundColor(Value: TColor);
begin
  if value <> FBackgroundColor then
  begin
    FBackgroundColor := value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetMargin(Value: Integer);
begin
  if Value <> FMargin then
  begin
    FMargin := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetBoldSelect(Value: Boolean);
begin
  if Value <> FBoldSelect then
  begin
    FBoldSelect := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetTabIndex(Value: Integer);
var
  VisualWidth: integer;
  ATab, BTab: TZXPTab;
begin
  if (Value=FTabIndex) or ((Value>=FTabs.Count) and  (FTabs.Count <> 0)) or (Value < 0) then exit;
  FAllowChange := true;
  //todo:component state
  if not FInitializing then
    if Assigned(FOnChange) then
      FOnChange(Self, Value, FAllowChange);
  if not FAllowChange then Exit;
  if (Value < FTabs.Count) and (Value >= 0) then
  begin
    if FScrollable then
      VisualWidth := Width - FMargin * 2 - 45
    else
      VisualWidth := Width - FMargin;
    ATab := FTabs.Items[Value];
    ClearAllSelectedState;
    ATab.Selected := true;
    FTabIndex := Value;
    FTabChanged := true;
    BuildTabImage(FTabsBitmap.Canvas);
    if ATab.OffStartPos <= 0 then //not display head
    begin
      if FTabIndex = 0 then //the first tab
        ScrollTabs(-ATab.OffStartPos + EdgeWidth)
      else
      begin
        Pointer(BTab) := FTabs.Items[Value - 1];
        ScrollTabs(-ATab.OffStartPos + BTab.Size div 2 + FMargin);
      end;
    end
    else
      if ATab.OffStartPos + ATab.Size >= VisualWidth then // not display tail
      begin
        if FTabIndex = FTabs.Count - 1 then //the last tab
          ScrollTabs(-(ATab.OffStartPos + ATab.Size - VisualWidth))
        else
        begin
          Pointer(BTab) := FTabs.Items[Value + 1];
          ScrollTabs(-(ATab.OffStartPos + ATab.Size - VisualWidth + BTab.Size div 2));
        end;
      end;
    SetButtonStat;
    FTabChanged := true;
    Invalidate;
    if Assigned(FNoteBook) then
      FNoteBook.PageIndex := FTabIndex;
  end
  else FTabIndex := Value;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetTabHeight(Value: Integer);
begin
  if Value <> FTabHeight then
  begin
    FTabHeight := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetTabLayOut(Value: TTabLayOut);
begin
  if Value <> FLayOut then
  begin
    FLayOut := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetHighlightColor(Value: TColor);
begin
  if Value <> FHighlightColor then
  begin
    FHighlightColor := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetShadowColor(Value: TColor);
begin
  if Value <> FShadowColor then
  begin
    FShadowColor := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetSaperatorColor(Value: TColor);
begin
  if Value <> FSaperatorColor then
  begin
    FSaperatorColor := Value;
    FTabChanged := true;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetScrollable(Value: Boolean);
begin
  if Value <> FScrollable then
  begin
    FScrollable := Value;
    if not FScrollable then
    begin
      FPrevBtn.Visible := false;
      FNextBtn.Visible := false;
      FCloseBtn.Visible := false;
      FPrevBtn.ControlStyle := FPrevBtn.ControlStyle + [csNoDesignVisible];
      FNextBtn.ControlStyle := FNextBtn.ControlStyle + [csNoDesignVisible];
      FCloseBtn.ControlStyle := FCloseBtn.ControlStyle + [csNoDesignVisible];
    end
    else
    begin
      FPrevBtn.Visible := true;
      FNextBtn.Visible := true;
      FCloseBtn.Visible := true;
      FPrevBtn.ControlStyle := FPrevBtn.ControlStyle - [csNoDesignVisible];
      FNextBtn.ControlStyle := FNextBtn.ControlStyle - [csNoDesignVisible];
      FCloseBtn.ControlStyle := FCloseBtn.ControlStyle - [csNoDesignVisible];
    end;
    Invalidate;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.Paint;
begin
  FTabHeight := Canvas.TextHeight('中文hgfl') + 2 + 3;
  Height := FTabHeight + 3 + 2;
  if FTabChanged then
    BuildTabImage(FTabsBitmap.Canvas);
  Canvas.Brush.Color := FBackgroundColor;
  Canvas.FillRect(ClientRect);
  if FLayOut = tlTop then
  begin
    Canvas.Pen.Color := FHighLightColor; //white
    Canvas.MoveTo(0, Height - 3);
    Canvas.LineTo(Width, Height - 3);
    Canvas.Pen.Color := Color; //Silver
    Canvas.MoveTo(0, Height - 2);
    Canvas.LineTo(Width, Height - 2);
    Canvas.MoveTo(0, Height - 1);
    Canvas.LineTo(Width, Height - 1);
  end
  else
  begin
    Canvas.Pen.Color := FShadowColor; //black
    Canvas.MoveTo(0, 2);
    Canvas.LineTo(Width, 2);
    Canvas.Pen.Color := Color; //Silver
    Canvas.MoveTo(0, 1);
    Canvas.LineTo(Width, 1);
    Canvas.MoveTo(0, 0);
    Canvas.LineTo(Width, 0);
  end;

  if FScrollable then
    BitBlt(Canvas.Handle, 0, 0, Width - 2 * FMargin - 45, FTabsBitmap.Height, FTabsBitmap.Canvas.Handle, -FScrollPos, 0, SRCCOPY)
  else
    BitBlt(Canvas.Handle, 0, 0, Width - FMargin, FTabsBitmap.Height, FTabsBitmap.Canvas.Handle, -FScrollPos, 0, SRCCOPY);
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.WMSize(var Message: TWMSize);
begin
  if (Assigned(FPrevBtn)) and (Assigned(FNextBtn)) and (Assigned(FTabsBitmap)) then
  begin
    if FLayOut = tlTop then
    begin
      FPrevBtn.Left := Width - FMargin - 15 * 3;
      FPrevBtn.Top := 3;
      FNextBtn.Left := Width - FMargin - 15 * 2;
      FNextBtn.Top := 3;
      FCloseBtn.Left := Width - FMargin - 15;
      FCloseBtn.Top := 3;
    end
    else
    begin
      FPrevBtn.Left := Width - FMargin - 15 * 3;
      FPrevBtn.Top := 5;
      FNextBtn.Left := Width - FMargin - 15 * 2;
      FNextBtn.Top := 5;
      FCloseBtn.Left := Width - FMargin - 15;
      FCloseBtn.Top := 5;
    end;
    SetButtonStat;
  end;
  Invalidate;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.ScrollTabs(Offset: integer);
var
  VisualWidth, i: integer;
  ATab: TZXPTab;
begin
  if not FScrollable then
  begin
    FPrevBtn.Visible := false;
    FNextBtn.Visible := false;
    FCloseBtn.Visible := false;
  end
  else
  begin
    FPrevBtn.Visible := true;
    FNextBtn.Visible := true;
    FCloseBtn.Visible := true;
  end;

  VisualWidth := Width - FMargin * 2 - 45;
  if (FTabsBitmap.Width < VisualWidth) then
  begin
    FScrollPos := 0;
    FPrevBtn.Enabled := false;
    FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFTDIS');
    FNextBtn.Enabled := false;
    FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHTDIS');
  end
  else
  begin
    FPrevBtn.Enabled := true;
    FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFT');
    FNextBtn.Enabled := true;
    FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHT');
    inc(FScrollPos, Offset);
    if FScrollPos < -(FTabsBitmap.Width - VisualWidth) then
    begin
      FScrollPos := -(FTabsBitmap.Width - VisualWidth);
      FNextBtn.Enabled := false;
      FNextBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBRIGHTDIS');
    end;
    if FScrollPos > 0 then
    begin
      FScrollPos := 0;
      FPrevBtn.Enabled := false;
      FPrevBtn.Glyph.Handle := LoadBitmap(hInstance, 'SDSBLEFTDIS');
    end;
  end;

  for i := 0 to FTabs.Count - 1 do
  begin
    ATab := FTabs.Items[i];
    ATab.OffStartPos := ATab.StartPos + FScrollPos;
  end;
  Invalidate;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.ClearAllSelectedState;
var
  i: integer;
  ATab: TZXPTab;
begin
  for i := 0 to FTabs.Count - 1 do
  begin
    ATab := FTabs.Items[i];
    ATab.Selected := false;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.MouseDown(Button: TMouseButton; Shift: TShiftState;
  X, Y: Integer);
var
  i, ASize: integer;
  ATab: TZXPTab;
begin
  inherited MouseDown(Button, Shift, X, Y);
  for i := 0 to FTabs.Count - 1 do
  begin
    ATab := FTabs.Items[i];
    if FScrollable then
    begin
      if ATab.OffStartPos + ATab.Size > Width - 15 * 3 - FMargin * 2 then
        ASize := Width - 15 * 3 - FMargin * 2 - ATab.OffStartPos
      else ASize := ATab.Size;
    end
    else
    begin
      if ATab.OffStartPos + ATab.Size > Width - FMargin then
        ASize := Width - FMargin - ATab.OffStartPos
      else ASize := ATab.Size;
    end;
    if (X < ATab.OffStartPos + ASize)
      and (X >= ATab.OffStartPos) then //in this tab
    begin
      if FTabIndex = i then exit; //not changed
      if not ATab.Enabled then Exit;
      FAllowChange := false;
      SetTabIndex(i);
      if FAllowChange then
      begin
        FTabChanged := true;
        if Assigned(FOnTabClick) then
          FOnTabClick(Self, FTabIndex);
        break;
      end;
    end;
  end;
end;
//------------------------------------------------------------------------------
//todo: improve caption change mach.
procedure TZXPTabSet.ChangeTabCaption(AIndex: Integer; ACaption: string);
var
  ATab: TZXPTab;
begin
  if AIndex >= FTabs.Count then Exit;
  ATab := FTabs[AIndex];
  ATab.Caption := ACaption;
  FTabChanged := true;
  Invalidate;
  SetButtonStat;
end;
//------------------------------------------------------------------------------
function TZXPTabSet.GetTabsCount: Integer;
begin
  Result := FTabs.Count;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.UpdateTabs;
begin
  FTabChanged := true;
  Invalidate;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.CloseTab(AIndex: Integer);
var
  FAllowClose: Boolean;
begin
  if Assigned(FOnClose) then
  begin
    FAllowClose := true;
    FOnClose(Self, FTabIndex, FAllowClose);
    if FAllowClose then
    begin
      DeleteTab(FTabIndex);
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetTabStyle(value: TTabStyle);
begin
  if value <> FTabStyle then
  begin
    FTabStyle := value;
    FTabChanged := true;
    Invalidate;
    SetButtonStat;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.DrawTFirstTab(ACanvas: TCanvas);
var
  ATab: TZXPTab;
  TabRect: TRect;
  ImageWidth: integer;
  i: Integer;
begin
  {Calculate tab rectangle}
  if TabsCount <= 0 then Exit;
  ATab := FTabs.Items[0];
  i := 0;   //first one
  //If the first one is not visible, try to draw the next one.
  while (not ATab.Visible) and (i<FTabs.Count) do
  begin
    Inc(i); // if it is invisible, Increase i
    ATab := FTabs.Items[i];
  end;
  //if still no tabs visible, quit
  if not ATab.Visible then Exit;
  TabRect.Left := ATab.StartPos;
  TabRect.Right := ATab.StartPos + ATab.Size - 1;
  if FLayOut = tlTop then TabRect.Top := 2
  else TabRect.Top := 3;
  TabRect.Bottom := Height - 3;
  if FLayOut = tlBottom then
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left + FEdgeWidth, TabRect.Bottom); { \ }
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
      LineTo(TabRect.Right, TabRect.Top); { / }
      LineTo(TabRect.Left, TabRect.Top); { - }
      if ATab.FEnabled = false then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FUnselectedColor;
      FloodFill(TabRect.Left + FEdgeWidth + 2, TabRect.Bottom - 2,
        clFuchsia, fsBorder);
      {draw 3D effects}
      MoveTo(TabRect.Left, TabRect.Top);
      Pen.Color := FHighLightColor; //clBtnHighLight;
      LineTo(TabRect.Left + FEdgeWidth, TabRect.Bottom); { \ }
      Pixels[TabRect.Left + FEdgeWidth, TabRect.Bottom] := FHighLightColor;
      Pen.Color := FShadowColor; //Black;//clWindowFrame;
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
      Pixels[TabRect.Right - FEdgeWidth, TabRect.Bottom] := FShadowColor;
      LineTo(TabRect.Right, TabRect.Top); { / }
      Pen.Color := FUnSelectedColor; //clBtnHighLight;
      LineTo(TabRect.Left, TabRect.Top); { - }
      Pixels[TabRect.Left, TabRect.Top] := FHighlightColor;
      Pixels[TabRect.Right, TabRect.Top] := FShadowColor;

      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FEdgeWidth + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FEdgeWidth + FMargin + ImageWidth; //TabRect.Left +
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
      else TabRect.Top := TabRect.Top + 3;
      TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
      TabRect.Bottom := TabRect.Bottom;
      if ATab.FEnabled = false then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FUnSelectedFontColor;

      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end
  else
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia;
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Left + FEdgeWidth, TabRect.Top); { / }
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
      LineTo(TabRect.Right, TabRect.Bottom); { \ }
      LineTo(TabRect.Left, TabRect.Bottom); { _ }
      if ATab.FEnabled = false then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FUnselectedColor;

      FloodFill(TabRect.Left + FEdgeWidth + 2, TabRect.Bottom - 2,
        clFuchsia, fsBorder);
      {draw 3D effects}
      MoveTo(TabRect.Left, TabRect.Bottom);
      Pen.Color := FHighLightColor; //clBtnHighLight;
      LineTo(TabRect.Left + FEdgeWidth, TabRect.Top); { / }
      Pixels[TabRect.Left + FEdgeWidth, TabRect.Top] := FHighLightColor;
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
      Pixels[TabRect.Right - FEdgeWidth, TabRect.Top] := FHighlightColor;
      Pen.Color := FShadowColor; //Black;//clWindowFrame;
      LineTo(TabRect.Right, TabRect.Bottom); { \ }
      Pen.Color := FUnSelectedColor; //clBtnHighLight;
      LineTo(TabRect.Left, TabRect.Bottom); { - }
      Pixels[TabRect.Left, TabRect.Bottom] := FHighlightColor;
      Pixels[TabRect.Right, TabRect.Bottom] := FShadowColor;

      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FEdgeWidth + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FEdgeWidth + FMargin + ImageWidth; //TabRect.Left +
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
      else TabRect.Top := TabRect.Top + 3;
      TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
      TabRect.Bottom := TabRect.Bottom;
      if ATab.FEnabled = false then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FUnSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.DrawTLastTab(ACanvas: TCanvas);
var
  ATab: TZXPTab;
  TabRect: TRect;
  ImageWidth: integer;
  i: Integer;
begin
  {Calculate tab rectangle}
  if TabsCount <= 0 then Exit;
  ATab := FTabs.Items[TabsCount - 1];
  i := TabsCount - 1;   //last one
  while (not ATab.Visible) and (i>=0) do
  begin
    Dec(i); // if it is invisible, decrease i
    ATab := FTabs.Items[i];
  end;
  //if still no tabs visible, quit
  if not ATab.Visible then Exit;
  TabRect.Left := ATab.StartPos;
  TabRect.Right := ATab.StartPos + ATab.Size - 1;
  if FLayOut = tlTop then TabRect.Top := 2
  else TabRect.Top := 3;
  TabRect.Bottom := Height - 3;
  if FLayOut = tlTop then
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia; //Black;//clWindowFrame;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { / }
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
      LineTo(TabRect.Right, TabRect.Bottom); { \ }
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { - }
      if ATab.FEnabled = false then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FUnselectedColor;
      FloodFill(TabRect.Left + FEdgeWidth + 1, TabRect.Bottom - 2,
        clFuchsia, fsBorder);
      {draw 3D effects}
      Pen.Color := FHighLightColor; //Black;//clWindowFrame;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { / }
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
      Pixels[TabRect.Left, TabRect.Top] := FHighlightColor;
      Pen.Color := FShadowColor; //Black;//clWindowFrame;
      LineTo(TabRect.Right, TabRect.Bottom); { \ }
      Pen.Color := FUnSelectedColor; //Black;//clWindowFrame;
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { _ }
      Pixels[TabRect.Right, TabRect.Bottom] := FShadowColor;
      Pixels[TabRect.Left - FEdgeWidth, TabRect.Bottom] := FHighlightColor;
      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
      else TabRect.Top := TabRect.Top + 3;
      TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
      TabRect.Bottom := TabRect.Bottom;
      if ATab.FEnabled = false then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FUnSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end
  else
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia; //Black;//clWindowFrame;
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { \ }
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
      LineTo(TabRect.Right, TabRect.Top); { / }
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
      if ATab.FEnabled = false then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FUnselectedColor;
      FloodFill(TabRect.Left + FEdgeWidth + 1, TabRect.Bottom - 2,
        clFuchsia, fsBorder);
      {draw 3D effects}
      Pen.Color := FHighLightColor; //Black;//clWindowFrame;
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { \ }
      MoveTo(TabRect.Left, TabRect.Bottom);
      Pen.Color := FShadowColor; //Black;//clWindowFrame;
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
      Pixels[TabRect.Left, TabRect.Bottom] := FHighlightColor;
      LineTo(TabRect.Right, TabRect.Top); { / }
      Pen.Color := FUnSelectedColor; //Black;//clWindowFrame;
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
      Pixels[TabRect.Right, TabRect.Top] := FShadowColor;
      Pixels[TabRect.Left - FEdgeWidth, TabRect.Top] := FHighlightColor;
      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
      else TabRect.Top := TabRect.Top + 3;
      TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
      TabRect.Bottom := TabRect.Bottom;
      if ATab.FEnabled = false then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FUnSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.DrawTSelectedTab(ACanvas: TCanvas);
var
  ATab: TZXPTab;
  TabRect: TRect;
  ImageWidth: integer;
begin
  {Calculate tab rectangle}
  if (FTabIndex < 0) then Exit;
  ATab := FTabs.Items[FTabIndex];
  if not ATab.Visible then Exit;
  TabRect.Left := ATab.StartPos;
  TabRect.Right := ATab.StartPos + ATab.Size - 1;
  if FLayOut = tlTop then TabRect.Top := 2
  else TabRect.Top := 3;
  TabRect.Bottom := Height - 3;
  if FLayOut = tlBottom then
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia; //Black;//clWindowFrame;
      if TabIndex > 0 then
      begin
        MoveTo(TabRect.Left, TabRect.Bottom);
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { \ }
        MoveTo(TabRect.Left, TabRect.Bottom);
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
        LineTo(TabRect.Right, TabRect.Top); { / }
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
        if ATab.FEnabled = false then
          Brush.Color := FDisabledColor
        else
          Brush.Color := FSelectedColor;
        FloodFill(TabRect.Left + FEdgeWidth + 1, TabRect.Bottom - 2,
          clFuchsia, fsBorder);
        {draw 3D effects}
        Pen.Color := FShadowColor; //Black;//clWindowFrame;
        MoveTo(TabRect.Left, TabRect.Bottom);
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { \ }
        Pixels[TabRect.Left - FEdgeWidth, TabRect.Top] := FShadowColor;
        MoveTo(TabRect.Left, TabRect.Bottom);
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
        LineTo(TabRect.Right, TabRect.Top); { / }
        Pen.Color := FSelectedColor; //Black;//clWindowFrame;
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
        Pixels[TabRect.Right, TabRect.Top] := FShadowColor;
        Pixels[TabRect.Left - FEdgeWidth, TabRect.Top] := FShadowColor;
        MoveTo(TabRect.Left - FEdgeWidth, TabRect.Top - 1);
        LineTo(TabRect.Right, TabRect.Top - 1);
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
        {draw glyph, if assigned}
        if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
        begin
          FImages.Draw(ACanvas, TabRect.Left + FMargin,
            ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
          ImageWidth := 16;
        end
        else ImageWidth := 0;
        {draw caption}
        TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
        if ImageWidth > 0 then inc(TabRect.Left, FMargin);
        if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
        else TabRect.Top := TabRect.Top + 3;
        TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
        TabRect.Bottom := TabRect.Bottom;
        if ATab.FEnabled = false then
          ACanvas.Font.Color := FDisabledFontColor
        else
          ACanvas.Font.Color := FSelectedFontColor;
        DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
      end
      else
      begin
        {draw tab background}
        Pen.Color := clFuchsia;
        MoveTo(TabRect.Left, TabRect.Top);
        LineTo(TabRect.Left + FEdgeWidth, TabRect.Bottom); { \ }
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
        LineTo(TabRect.Right, TabRect.Top); { / }
        LineTo(TabRect.Left, TabRect.Top); { - }
        if ATab.FEnabled = false then
          Brush.Color := FDisabledColor
        else
          Brush.Color := FSelectedColor;

        FloodFill(TabRect.Left + FEdgeWidth + 2, TabRect.Bottom - 2,
          clFuchsia, fsBorder);
        {draw 3D effects}
        MoveTo(TabRect.Left, TabRect.Top);
        Pen.Color := FShadowColor; //Black;//clWindowFrame;
        LineTo(TabRect.Left + FEdgeWidth, TabRect.Bottom); { \ }
        Pixels[TabRect.Left + FEdgeWidth, TabRect.Bottom] := FHighLightColor;
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
        Pixels[TabRect.Right - FEdgeWidth, TabRect.Bottom] := FShadowColor;
        LineTo(TabRect.Right, TabRect.Top); { / }
        Pen.Color := FSelectedColor; //clBtnHighLight;
        LineTo(TabRect.Left, TabRect.Top); { - }
        MoveTo(TabRect.Left, TabRect.Top - 1);
        LineTo(TabRect.Right, TabRect.Top - 1);
        Pixels[TabRect.Left, TabRect.Top] := FShadowColor;
        Pixels[TabRect.Right, TabRect.Top] := FShadowColor;

        {draw glyph, if assigned}
        if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
        begin
          FImages.Draw(ACanvas, TabRect.Left + FEdgeWidth + FMargin,
            ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
          ImageWidth := 16;
        end
        else ImageWidth := 0;
        {draw caption}
        TabRect.Left := ATab.StartPos + FEdgeWidth + FMargin + ImageWidth; //TabRect.Left +
        if ImageWidth > 0 then inc(TabRect.Left, FMargin);
        if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
        else TabRect.Top := TabRect.Top + 3;
        TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
        TabRect.Bottom := TabRect.Bottom;
        if ATab.FEnabled = false then
          ACanvas.Font.Color := FDisabledFontColor
        else
          ACanvas.Font.Color := FSelectedFontColor;
        DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
      end;
    end;
  end
  else
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia; //Black;//clWindowFrame;
      if TabIndex > 0 then
      begin
        {draw tab background}
        Pen.Color := clFuchsia; //Black;//clWindowFrame;
        MoveTo(TabRect.Left, TabRect.Top);
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { / }
        MoveTo(TabRect.Left, TabRect.Top);
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
        LineTo(TabRect.Right, TabRect.Bottom); { \ }
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { - }
        if ATab.FEnabled = false then
          Brush.Color := FDisabledColor
        else
          Brush.Color := FSelectedColor;
        FloodFill(TabRect.Left + FEdgeWidth + 1, TabRect.Bottom - 2,
          clFuchsia, fsBorder);
        {draw 3D effects}
        Pen.Color := FHighLightColor; //Black;//clWindowFrame;
        MoveTo(TabRect.Left, TabRect.Top);
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { / }
        MoveTo(TabRect.Left, TabRect.Top);
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
        Pixels[TabRect.Left, TabRect.Top] := FHighlightColor;
        Pen.Color := FShadowColor; //Black;//clWindowFrame;
        LineTo(TabRect.Right, TabRect.Bottom); { \ }
        Pen.Color := FSelectedColor; //Black;//clWindowFrame;
        LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { _ }
        Pixels[TabRect.Right, TabRect.Bottom] := FShadowColor;
        Pixels[TabRect.Left - FEdgeWidth, TabRect.Bottom] := FHighlightColor;
        {draw glyph, if assigned}
        if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated)  then
        begin
          FImages.Draw(ACanvas, TabRect.Left + FMargin,
            ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
          ImageWidth := 16;
        end
        else ImageWidth := 0;
        {draw caption}
        TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
        if ImageWidth > 0 then inc(TabRect.Left, FMargin);
        if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
        else TabRect.Top := TabRect.Top + 3;
        TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
        TabRect.Bottom := TabRect.Bottom;
        if ATab.FEnabled = false then
          ACanvas.Font.Color := FDisabledFontColor
        else
          ACanvas.Font.Color := FSelectedFontColor;
        DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
      end
      else
      begin
        {draw tab background}
        Pen.Color := clFuchsia;
        MoveTo(TabRect.Left, TabRect.Bottom);
        LineTo(TabRect.Left + FEdgeWidth, TabRect.Top); { / }
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
        LineTo(TabRect.Right, TabRect.Bottom); { \ }
        LineTo(TabRect.Left, TabRect.Bottom); { _ }
        if ATab.FEnabled = false then
          Brush.Color := FDisabledColor
        else
          Brush.Color := FSelectedColor;
        FloodFill(TabRect.Left + FEdgeWidth + 2, TabRect.Bottom - 2,
          clFuchsia, fsBorder);
        {draw 3D effects}
        MoveTo(TabRect.Left, TabRect.Bottom);
        Pen.Color := FHighLightColor; //clBtnHighLight;
        LineTo(TabRect.Left + FEdgeWidth, TabRect.Top); { / }
        Pixels[TabRect.Left + FEdgeWidth, TabRect.Top] := FHighLightColor;
        LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
        Pixels[TabRect.Right - FEdgeWidth, TabRect.Top] := FHighlightColor;
        Pen.Color := FShadowColor; //Black;//clWindowFrame;
        LineTo(TabRect.Right, TabRect.Bottom); { \ }
        Pen.Color := FSelectedColor; //clBtnHighLight;
        LineTo(TabRect.Left, TabRect.Bottom); { - }
        Pixels[TabRect.Left, TabRect.Bottom] := FHighlightColor;
        Pixels[TabRect.Right, TabRect.Bottom] := FShadowColor;

        {draw glyph, if assigned}
        if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated) then
        begin
          FImages.Draw(ACanvas, TabRect.Left + FEdgeWidth + FMargin,
            ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
          ImageWidth := 16;
        end
        else ImageWidth := 0;
        {draw caption}
        TabRect.Left := ATab.StartPos + FEdgeWidth + FMargin + ImageWidth; //TabRect.Left +
        if ImageWidth > 0 then inc(TabRect.Left, FMargin);
        if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
        else TabRect.Top := TabRect.Top + 3;
        TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
        TabRect.Bottom := TabRect.Bottom;
        if ATab.FEnabled = false then
          ACanvas.Font.Color := FDisabledFontColor
        else
          ACanvas.Font.Color := FSelectedFontColor;
        DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
      end;
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.DrawTTab(ACanvas: TCanvas; ATab: TZXPTab);
//var
//  MidX,MidY: Integer;
var
  TabRect: TRect;
  ImageWidth: integer;
begin
  {Calculate tab rectangle}
  if not ATab.Visible then Exit;
  TabRect.Left := ATab.StartPos;
  TabRect.Right := ATab.StartPos + ATab.Size - 1;
  if FLayOut = tlTop then TabRect.Top := 2
  else TabRect.Top := 3;
  TabRect.Bottom := Height - 3;
  if FLayOut = tlBottom then
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia;
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { \ }
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
      LineTo(TabRect.Right, TabRect.Top); { / }
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
      if ATab.FEnabled = false then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FUnSelectedColor;
      FloodFill(TabRect.Left + FEdgeWidth + 1, TabRect.Bottom - 2,
        clFuchsia, fsBorder);
      {draw 3D effects}
      Pen.Color := FHighLightColor; //Black;//clWindowFrame;
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { \ }
      Pixels[TabRect.Left, TabRect.Bottom] := FHighlightColor;
      Pen.Color := FShadowColor; //Black;//clWindowFrame;
      MoveTo(TabRect.Left, TabRect.Bottom);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Bottom); { _ }
      LineTo(TabRect.Right, TabRect.Top); { / }
      Pen.Color := FUnSelectedColor; //Black;//clWindowFrame;
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Top); { - }
      Pixels[TabRect.Right, TabRect.Top] := FShadowColor;
      Pixels[TabRect.Left - FEdgeWidth, TabRect.Top] := FHighlightColor;
      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated) then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
      else TabRect.Top := TabRect.Top + 3;
      TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
      TabRect.Bottom := TabRect.Bottom;
      if ATab.FEnabled = false then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FUnSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end
  else
  begin
    with ACanvas do
    begin
      {draw tab background}
      Pen.Color := clFuchsia;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { / }
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
      LineTo(TabRect.Right, TabRect.Bottom); { \ }
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { - }
      if ATab.FEnabled = false then
        Brush.Color := FDisabledColor
      else
        Brush.Color := FUnSelectedColor;
      FloodFill(TabRect.Left + FEdgeWidth + 1, TabRect.Bottom - 2,
        clFuchsia, fsBorder);
      {draw 3D effects}
      Pen.Color := FHighLightColor;
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { / }
      MoveTo(TabRect.Left, TabRect.Top);
      LineTo(TabRect.Right - FEdgeWidth, TabRect.Top); { - }
      Pixels[TabRect.Left, TabRect.Top] := FHighlightColor;
      Pen.Color := FShadowColor;
      LineTo(TabRect.Right, TabRect.Bottom); { \ }
      Pen.Color := FUnSelectedColor;
      LineTo(TabRect.Left - FEdgeWidth, TabRect.Bottom); { _ }
      Pixels[TabRect.Right, TabRect.Bottom] := FShadowColor;
      Pixels[TabRect.Left - FEdgeWidth, TabRect.Bottom] := FHighlightColor;
      {draw glyph, if assigned}
      if (ATab.ImageIndex >= 0) and (FImages <> nil) and (FImages.HandleAllocated) then
      begin
        FImages.Draw(ACanvas, TabRect.Left + FMargin,
          ((TabRect.Bottom - TabRect.Top - 16) div 2) + TabRect.Top, ATab.ImageIndex);
        ImageWidth := 16;
      end
      else ImageWidth := 0;
      {draw caption}
      TabRect.Left := ATab.StartPos + FMargin + ImageWidth; //TabRect.Left +
      if ImageWidth > 0 then inc(TabRect.Left, FMargin);
      if FLayOut = tlTop then TabRect.Top := TabRect.Top + 1
      else TabRect.Top := TabRect.Top + 3;
      TabRect.Right := TabRect.Right - FMargin - FEdgeWidth;
      TabRect.Bottom := TabRect.Bottom;
      if ATab.FEnabled = false then
        ACanvas.Font.Color := FDisabledFontColor
      else
        ACanvas.Font.Color := FUnSelectedFontColor;
      DrawText(ACanvas.Handle, PChar(ATab.Caption), Length(ATab.Caption), TabRect, DT_CENTER or DT_VCENTER or DT_SINGLELINE or DT_PATH_ELLIPSIS);
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetEdgeWidth(value: Integer);
begin
  if value <> FEdgeWidth then
  begin
    FEdgeWidth := value;
    FTabChanged := true;
    Invalidate;
    SetButtonStat;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetIndent(value: Integer);
begin
  if value <> FIndent then
  begin
    FIndent := value;
    FTabChanged := true;
    Invalidate;
    SetButtonStat;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetNoteBook(value: TNoteBook);
var
  i: integer;
  sCaption, sIdx: string;
  idx: Integer;
begin
  if Assigned(FNoteBook) then
     FNoteBook.RemoveFreeNotification(Self);

  if Assigned(value) then
  begin
    FNoteBook := value;
    FNoteBook.FreeNotification(Self);
    FTabIndex := FNoteBook.PageIndex;
    if not (csDesigning in ComponentState) then exit;
   // ClearAllTabs;
    for i := 0 to FNoteBook.Pages.Count - 1 do
    begin
      sIdx := ParseDataField(FNoteBook.Pages.Strings[i], 2);
      sCaption := ParseDataField(FNoteBook.Pages.Strings[i], 1);
      Idx := -1;
      if sIdx <> '' then
      try
        idx := StrToInt(sIdx);
      except
        idx := -1;
      end;
      if FTabs.Count>i then
         FTabs.Items[i].Caption := sCaption
      else
       AddTab(sCaption, idx, false, false);
    end;
    while FTabs.Count>FNoteBook.Pages.Count  do  //删除多余的
       FTabs.Delete(FTabs.Count-1);
    FInitializing := true;
    FTabIndex := 0;
    FNoteBook.PageIndex := FTabIndex;
    FInitializing := false;
    FNoteBook.OnPageChanged := NBPageChange;
  end
  else  
  begin
    FNoteBook :=nil;
    ClearAllTabs;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.NBPageChange(Sender: TObject);
begin
  if csDesigning in ComponentState then
    if Assigned(FNoteBook) then
      TabIndex := FNoteBook.PageIndex;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.CMFontChanged(var Message: TMessage);
begin
  inherited;
  Canvas.Font := Font;
  FTabChanged := true;
  Invalidate;
  SetButtonStat;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.CMSysColorChange(var Message: TMessage);
begin
  inherited;
  if Assigned(FTabsBitmap) then
    BuildTabImage(FTabsBitmap.Canvas);
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.CMDesignHitTest(var Message: TCMDesignHitTest);
var
  X,Y, i: Integer;
  ATab: TZXPTab;
  ASize,HSize: Integer;
  mPoint:TPoint;
begin
  inherited;
  if not (csDesigning in ComponentState) then Exit;
  X := Message.XPos;
  Y :=Message.YPos;
  if (Message.Keys and MK_LBUTTON) = MK_LBUTTON then
  begin
    for i := 0 to FTabs.Count - 1 do
    begin
      ATab := FTabs.Items[i];
      if FScrollable then
      begin
        if ATab.OffStartPos + ATab.Size > Width - 15 * 3 - FMargin * 2 then
          ASize := Width - 15 * 3 - FMargin * 2 - ATab.OffStartPos
        else ASize := ATab.Size;
      end
      else
        begin
        if ATab.OffStartPos + ATab.Size > Width - FMargin then
          ASize := Width - FMargin - ATab.OffStartPos
        else ASize := ATab.Size;
        end;
        mPoint.x :=X;
        mPoint.y :=Y;
        mPoint :=ScreenToClient(mPoint);
      if (X < ATab.OffStartPos + ASize)
        and (X >= ATab.OffStartPos)  then //in this tab
      begin
        if FTabIndex = i then exit; //not changed
        SetTabIndex(i);
        FTabChanged := true;
        if Assigned(FNoteBook) then
          FNoteBook.PageIndex := FTabIndex;
        break;
      end;
    end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTabSet.SetTabs(value: TZXPTabs);
begin
  FTabs.Assign(Value);
end;
//------------------------------------------------------------------------------
{ TZXPTabs }
function TZXPTabs.Add: TZXPTab;
begin
  Result := TZXPTab(inherited Add);
end;
//------------------------------------------------------------------------------
//todo:TZXPTabs.Create(Tabset: TZXPTabSet);
constructor TZXPTabs.Create(Tabset: TZXPTabSet);
begin
  inherited Create(TZXPTab);
  FTabSet := TabSet;
end;
//------------------------------------------------------------------------------
function TZXPTabs.GetItem(Index: Integer): TZXPTab;
begin
  Result := TZXPTab(inherited GetItem(Index));
end;
//------------------------------------------------------------------------------
function TZXPTabs.GetOwner: TPersistent;
begin
  Result := FTabSet;
end;
//------------------------------------------------------------------------------
procedure TZXPTabs.SetItem(Index: Integer; Value: TZXPTab);
begin
  inherited SetItem(Index, Value);
end;
//------------------------------------------------------------------------------
procedure TZXPTabs.Update(Item: TCollectionItem);
begin
  inherited;
  if Assigned(FTabSet) then
  begin
    FTabSet.FTabChanged := true;
    FTabSet.Invalidate;
  end;
end;
//------------------------------------------------------------------------------
{ TZXPTab }
procedure TZXPTab.Assign(Source: TPersistent);
begin
  if Source is TZXPTab then
  begin
    FTabs.Assign(TZXPTab(Source).FTabs);
   // FTabs := TZXPTab(Source).FTabs;
    Caption := TZXPTab(Source).Caption;
    Size := TZXPTab(Source).Size;
    StartPos := TZXPTab(Source).StartPos;
    OffStartPos := TZXPTab(Source).OffStartPos;
    ImageIndex := TZXPTab(Source).ImageIndex;
    CanClose := TZXPTab(Source).CanClose;
    Selected := TZXPTab(Source).Selected;
    Enabled := TZXPTab(Source).Enabled;
  end
  else inherited Assign(Source);
end;
//------------------------------------------------------------------------------
constructor TZXPTab.Create(Collection: TCollection);
begin
  //todo: tab item create
  inherited Create(Collection);
  FTabs := Collection as TZXPTabs;
  FCaption := 'Tab ' + IntToStr(FTabs.Count);
  ImageIndex := -1;
  CanClose := false;
  FEnabled := true;
  if FTabs.FTabSet.FTabIndex = Self.Index then
    FSelected := true
  else
    FSelected := false;
//  if csDesigning in FTabs.FTabSet.ComponentState then
//    if Assigned(FTabs.FTabSet) and (FTabs.Count>0) then
//      FTabs.FTabSet.TabIndex := 0;
end;
//------------------------------------------------------------------------------
procedure TZXPTab.SetCaption(const Value: string);
begin
  if FCaption <> Value then
  begin
    FCaption := Value;
    if Assigned(FTabs) then
      if Assigned(FTabs.FTabSet) then
      begin
        FTabs.FTabSet.FTabChanged := true;
        FTabs.FTabSet.Invalidate;
      end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTab.SetEnabled(const Value: Boolean);
begin
  if FEnabled <> Value then
  begin
    FEnabled := Value;
    if Assigned(FTabs) then
      if Assigned(FTabs.FTabSet) then
      begin
        FTabs.FTabSet.FTabChanged := true;
        FTabs.FTabSet.Invalidate;
      end;
  end;
end;
//------------------------------------------------------------------------------
procedure TZXPTab.SetImageIndex(const Value: TImageIndex);
begin
  if FImageIndex <> Value then
  begin
    FImageIndex := Value;
    if Assigned(FTabs) then
      if Assigned(FTabs.FTabSet) then
      begin
        FTabs.FTabSet.FTabChanged := true;
        FTabs.FTabSet.Invalidate;
      end;
  end;
end;
//----------------------------------------------------------------------------
//TODO: SETVISIBLE
procedure TZXPTab.SetVisible(const Value: Boolean);
begin
  if FVisible <> Value then
  begin
    FVisible := Value;
    if Assigned(FTabs) then
      if Assigned(FTabs.FTabSet) then
      begin
        //if the current selected one is set to invisible
        // try to make a new selection.
        if Selected then
        begin
          if (Self.Index = 0) and (FTabs.Count>1) then
            FTabs.FTabSet.TabIndex := 0
          else if (Self.Index > 0) and (FTabs.Count>1) then
            FTabs.FTabSet.TabIndex := Self.Index - 1;
        end;
        FTabs.FTabSet.FTabChanged := true;
        FTabs.FTabSet.Invalidate;
      end;
  end;
end;

procedure TZXPTabSet.SetImages(const Value: TCustomImageList);
begin
  if Assigned(FImages) then
     FImages.RemoveFreeNotification(Self);

  FImages := Value;

  if Assigned(FImages) then
     FImages.FreeNotification(Self);
end;

procedure TZXPTabSet.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) then
   begin
    if (AComponent = FImages) then
        FImages := nil
    else if(AComponent = FNoteBook) then
        FNoteBook :=nil;
   end;
end;

//-------------------------- EOF -----------------------------------------------
end.

