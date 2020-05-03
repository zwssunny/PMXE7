{***************************************************************************}
{ Diagram Studio                                                            }
{ for Delphi & C++Builder                                                   }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright © 2003-2011                                          }
{            Email : info@tmssoftware.com                                   }
{            Web : http://www.tmssoftware.com                               }
{                                                                           }
{ The source code is given as is. The author is not responsible             }
{ for any possible damage done due to the use of this code.                 }
{ The components can be freely used in any application. The complete        }
{ source code remains property of the author and may not be distributed,    }
{ published, given or sold in any form as such. No parts of the source      }
{ code can be included in any other component or application without        }
{ written authorization of the author.                                      }
{***************************************************************************}

unit DiagramExtra;

{$I Diagram.Inc}

interface

uses
  Windows, Classes, Controls, Buttons, Forms, ExtCtrls, atDiagram,
  ImgList, DiagramActns, ActnList, Contnrs;
                                             
type

  /// Description:
  ///   Use this event to set a image index for a given block in the diagram toolbar. The ABlockID parameter
  ///   holds the identification of the block. Set the AIdx parameter to provide the image index for the block
  ///   identified by ABlockID.
  TDTGetImageIndexEvent = procedure(const ABlockID: string;
    var AIdx: integer) of object;
  TDiagramBarButton = (dbBlocks, dbCancelInsert, dbDelete, dbLines);

  /// Summary:
  ///   TDiagramBarButtons type is a set of TDiagramBarButton used to indicate what types of button are
  ///   available in diagram toolbar.
  TDiagramBarButtons = set of TDiagramBarButton;

const
  /// Summary:
  ///   Constant which defines the default set of buttons for the Buttons property of TDiagramToolbar.
  DiagramBarButtons = [dbBlocks, dbCancelInsert, dbDelete, dbLines];

type

  /// Summary:
  ///   TSpeedButton descendant for diagram toolbar.
  /// Description:
  ///   Used internally by TDiagramToolBar.
  TDiagramButton = class(TSpeedButton)
  protected
    {$IFNDEF DELPHI2006_LVL}

    /// Description:
    ///   For internal use.
    function GetActionLinkClass: TControlActionLinkClass; override;
    {$ENDIF}
  end;

  /// Description:
  ///   For internal use only.
  TDiagramButtonActionLink = class(TControlActionLink)
  protected
    FClient: TSpeedButton;
    procedure AssignClient(AClient: TObject); override;
    function IsCheckedLinked: Boolean; override;
    procedure SetChecked(Value: Boolean); override;
  public
    {$IFDEF DELPHI6_LVL}
    function Execute(AComponent: TComponent = nil): boolean; override;
    {$ELSE}
    function Execute: boolean; override;
    {$ENDIF}
  end;

  TToolbarMode = (tmObjects, tmConnections);

  /// Summary:
  ///   Provides a tool bar for editing the diagram.
  /// Description:
  ///   TDiagramToolBar is a ready-to-use tool bar for diagram editing. It provides automatically buttons for
  ///   inserting blocks and deleting. All blocks registered are visible. Blocks visible can be restricted by
  ///   setting Category property.
  TDiagramToolBar = class(TCustomControl, IDiagramSubscriber)
  private
    FActionList: TObjectList;
    FFlatButtons: boolean;
    FCategory: string;
    FDiagram: TatDiagram;
    FImages: TCustomImageList;
    FOnGetImageIndex: TDTGetImageIndexEvent;
    FImageChangeLink: TChangeLink;
    FButtons: TDiagramBarButtons;
    FKeepInsertingMode: TKeepInsertingMode;
    FButtonList: TObjectList;
    FToolbarMode: TToolbarMode;
    FButtonSize: integer;
    procedure RecreateButtons;
    procedure CheckActions;
    procedure CreateActions;
    procedure SetFlatButtons(const Value: boolean);
    procedure SetCategory(const Value: string);
    procedure SetDiagram(const Value: TatDiagram);
    procedure CancelButtonClick(Sender: TObject);
    procedure DeleteButtonClick(Sender: TObject);
    procedure ButtonClick(Sender: TObject);
    function Designing: boolean;
    procedure SetImages(const Value: TCustomImageList);
    procedure ImageListChange(Sender: TObject);
    procedure UpdateButtonGlyph(ABtn: TSpeedButton; const ABlockID: string; AClass: TClass);
    procedure SetButtons(const Value: TDiagramBarButtons);
    function CreateButton(const AName: string; AClass: TClass): TSpeedButton;
    procedure SetKeepInsertingMode(const Value: TKeepInsertingMode);
    procedure DestroyActions;
    procedure DestroyButtons;
    procedure SetToolbarMode(const Value: TToolbarMode);
    procedure AdjustBarButtons;
    procedure SetButtonSize(const Value: integer);
    procedure DgrNotification(AInfo: TDgrNotificationInfo);
  protected

    /// Description:
    ///   For internal use.
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;

    /// Description:
    ///   For internal use.
    procedure CreateWnd; override;

    /// Description:
    ///   Updates (recreate) all the buttons of the toolbar.
    procedure UpdateButtons;
  public
    /// Description:
    ///   Creates the object.
    constructor Create(AOwner: TComponent); override;

    /// Description:
    ///   Destroys the object.
    destructor Destroy; override;

    /// Description:
    ///   Call rebuild to refresh diagram buttons.
    procedure Rebuild;
  published

    /// Description:
    ///   Specifies if buttons in tool bar are flat or not.
    property FlatButtons: boolean read FFlatButtons write SetFlatButtons default true;

    /// Description:
    ///   Specifies what kind of buttons are visible in the tool bar.
    property Buttons: TDiagramBarButtons read FButtons write SetButtons default DiagramBarButtons;

    /// Description:
    ///   Category property is used to restrict visible buttons in the tool bar used to insert blocks.
    ///   If Category property is set, only blocks belonging to the specified category will have buttons
    ///   visible in the toolbar.
    property Category: string read FCategory write SetCategory;

    /// Description:
    ///   Specifies the diagram to be controlled by the toolbar.
    property Diagram: TatDiagram read FDiagram write SetDiagram;

    /// Description:
    ///   Images property can point to a TImageList component to get icons from custom created blocks.
    property Images: TCustomImageList read FImages write SetImages;
    property Align default alTop;

    /// Description:
    ///   Use OnGetImageIndex event to specify a image index for a custom registered block.
    property OnGetImageIndex: TDTGetImageIndexEvent read FOnGetImageIndex write FOnGetImageIndex;

    /// Description:
    ///   KeepInsertingMode property defines how inserting of diagram controls works with related to keep
    ///   inserting. Keep inserting is a feature which enables the end-user to inserting several diagram
    ///   controls (of the same type)  at once, without needing to click in the toolbar button again to
    ///   start inserting of the same diagram controls.
    property KeepInsertingMode: TKeepInsertingMode read FKeepInsertingMode write SetKeepInsertingMode;

    /// Description:
    ///   Specifies the mode of the toolbar. The toolbar can be a "regular" toolbar (objects) or you can show
    ///   line objects in the toolbar and it can be used to choose the connection type used to connect two
    ///   linkpoints.
    property Mode: TToolbarMode read FToolbarMode write SetToolbarMode;

    /// Description:
    ///   Specifies the size of the button used in the toolbar.
    property ButtonSize: integer read FButtonSize write SetButtonSize;
  end;

implementation
uses SysUtils, Graphics;

{ TDiagramToolBar }

const
  SCancelButtonName = 'CancelInsert';
  SDeleteButtonName = 'Delete';

procedure TDiagramToolBar.CreateWnd;
begin
  inherited;
  RecreateButtons;
  Height := ButtonSize;
end;

procedure TDiagramToolBar.CreateActions;
var c: integer;
    AAction: TDiagramAction;
    ACancelAction: TDiagramCancelInsert;
    ADeleteAction: TDiagramDelete;
begin
  if Designing then Exit;
  DestroyActions;

  ACancelAction := TDiagramCancelInsert.Create(Self);
  FActionList.Add(ACancelAction);
  ACancelAction.Diagram := Self.Diagram;

  ADeleteAction := TDiagramDelete.Create(Self);
  FActionList.Add(ADeleteAction);
  ADeleteAction.Diagram := Self.Diagram;

  for c := 0 to RegDControlList.Count - 1 do
  begin
    Case Mode of
      tmConnections:
        begin
          AAction := TDiagramConnectionID.Create(Self);
          TDiagramConnectionID(AAction).ConnectionLineID := RegDControlList[c].DControlID;
        end
    else
      {tmObjects}
      begin
        AAction := TDiagramInsertBlock.Create(Self);
        TDiagramInsertBlock(AAction).DControlID := RegDControlList[c].DControlID;
        TDiagramInsertBlock(AAction).KeepInsertingMode := Self.KeepInsertingMode;
      end;
    end;
    
    FActionList.Add(AAction);
    With AAction do
    begin
      Category := RegDControlList[c].Category;
      Hint := RegDControlList[c].Caption;
      Diagram := Self.Diagram;
    end;
  end;
end;

procedure TDiagramToolBar.UpdateButtonGlyph(ABtn: TSpeedButton;
  const ABlockID: string; AClass: TClass);
var
  Idx: integer;
  AResName: string;
  AHInstance: integer;
  AReg: TRegDControl;
begin
  Idx := -1;
  AReg := RegDControlList.FindByID(ABlockID);
  if Assigned(FOnGetImageIndex) then
    FOnGetImageIndex(ABlockID, Idx);
  if Assigned(Images) and (Idx >= 0) and (Idx < Images.Count) then
  begin
    with ABtn.Glyph do
    begin
      Width := Images.Width;
      Height := Images.Height;
      Canvas.Brush.Color := clFuchsia;//! for lack of a better color
      Canvas.FillRect(Rect(0,0, Width, Height));
      Images.Draw(Canvas, 0, 0, Idx);
    end;
  end else
  if (AReg <> nil) and (AReg.UseGlyph) then
  begin
    ABtn.Glyph.Assign(AReg.Glyph);
  end else
  begin
    AHInstance := FindClassHInstance(AClass);
    AResName := Uppercase('blk_' + ABlockID);
    {$WARNINGS OFF}
    if FindResource(AHInstance, PChar(AResName), RT_BITMAP) <> 0 then
    {$WARNINGS ON}
      ABtn.Glyph.LoadFromResourceName(AHInstance, AResName)
    else
    begin
      AHInstance := FindClassHInstance(TDiagramToolBar);
      AResName := Uppercase('blk_' + AClass.ClassName);
      {$WARNINGS OFF}
      if FindResource(AHInstance, PChar(AResName), RT_BITMAP) <> 0 then
      {$WARNINGS ON}
        ABtn.Glyph.LoadFromResourceName(AHInstance, AResName)
      else
        {$WARNINGS OFF}
        if FindResource(AHInstance, PChar('BLK_TCUSTOMDIAGRAMBLOCK'), RT_BITMAP) <> 0 then
          ABtn.Glyph.LoadFromResourceName(AHInstance, 'BLK_TCUSTOMDIAGRAMBLOCK');
        {$WARNINGS ON}
    end;
  end;
  if ABtn.Glyph.Width > ABtn.Glyph.Height then
    ABtn.NumGlyphs := 2
  else
    ABtn.NumGlyphs := 1;
end;

function TDiagramToolBar.CreateButton(const AName: string;
  AClass: TClass): TSpeedButton;
begin
  result := TDiagramButton.Create(Self);
  FButtonList.Add(result);
  With result do
  begin
    Name := AName;
    Caption := '';
    Flat := FlatButtons;
    Width := ButtonSize;
    Height := ButtonSize;
    Parent := Self;
    AllowAllUp := true;
    UpdateButtonGlyph(result, AName, AClass);
  end;
end;

procedure TDiagramToolBar.RecreateButtons;
var
  c: integer;
  d: integer;
  AButton: TSpeedButton;
  AOffset: integer;
begin
  CheckActions;
  DestroyButtons;

  {Create specific buttons}
  AOffset := 0;
  if dbDelete in FButtons then
    With CreateButton(SDeleteButtonName, TatDiagram) do
    begin
      if Designing then
        OnClick := DeleteButtonClick
      else
        Action := TBasicAction(FActionList[1]);
      Case Self.Align of
        alLeft, alRight:
          Top := AOffset;
      else
        Left := AOffset;
      end;
      AOffset := AOffset + ButtonSize + 5;
    end;
  if dbCancelInsert in FButtons then
    With CreateButton(SCancelButtonName, TatDiagram) do
    begin
      if Designing then
        OnClick := CancelButtonClick
      else
        Action := TBasicAction(FActionList[0]);
      GroupIndex := 2;
      Case Self.Align of
        alLeft, alRight:
          Top := AOffset;
      else
        Left := AOffset;
      end;
      AOffset := AOffset + ButtonSize + 5;
    end;

  {Create blocks buttons}
  if (dbBlocks in FButtons) or (dbLines in FButtons) then
  begin
    d := 0;
    for c := 0 to RegDControlList.Count - 1 do
      if (Category = '') or (SameText(Category, RegDControlList[c].Category)) then
      begin
        if ((dbBlocks in FButtons) and RegDControlList[c].DControlClass.InheritsFrom(TCustomDiagramBlock))
          or
           ((dbLines in FButtons) and RegDControlList[c].DControlClass.InheritsFrom(TCustomDiagramLine)) then
        begin
          AButton := TDiagramButton.Create(Self);
          FButtonList.Add(AButton);
          With AButton do
          begin
            Caption := '';
            Flat := FlatButtons;
            if Designing then
            begin
              OnClick := ButtonClick;
              Tag := c;
              Hint := RegDControlList[c].Caption;
            end
            else
              Action := TBasicAction(FActionList[c + 2]);
            Width := ButtonSize;
            Height := ButtonSize;
            Case Self.Align of
              alLeft, alRight:
                Top := d * ButtonSize + AOffset;
            else
              Left := d * ButtonSize + AOffset;
            end;
            Parent := Self;
            AllowAllUp := true;
            GroupIndex := 1;
            UpdateButtonGlyph(AButton, RegDControlList[c].DControlID, RegDControlList[c].DControlClass);
          end;
          inc(d);
        end;
      end;
  end;
end;

constructor TDiagramToolBar.Create(AOwner: TComponent);
begin
  inherited;
  FButtonSize := 29;
  ControlStyle := ControlStyle - [csSetCaption];
  BevelOuter := bvNone;
  ShowHint := true;
  FActionList := TObjectList.Create(false);
  FButtonList := TObjectList.Create(false);
  FFlatButtons := true;
  Align := alTop;
  FImageChangeLink := TChangeLink.Create;
  FImageChangeLink.OnChange := ImageListChange;
  FButtons := DiagramBarButtons;
end;

destructor TDiagramToolBar.Destroy;
begin
  DestroyActions;
  DestroyButtons;
  FButtonList.Free;
  FActionList.Free;
  FImageChangeLink.Free;
  FImageChangeLink := nil;
  inherited;
end;

procedure TDiagramToolBar.DestroyActions;
begin
  while FActionList.Count > 0 do
  begin
    TComponent(FActionList[0]).Free;
    FActionList.Delete(0);
  end;
end;

procedure TDiagramToolBar.DestroyButtons;
begin
  while FButtonList.Count > 0 do
  begin
    TComponent(FButtonList[0]).Free;
    FButtonList.Delete(0);
  end;
end;

procedure TDiagramToolBar.SetFlatButtons(const Value: boolean);
begin
  if FFlatButtons <> Value then
  begin
    FFlatButtons := Value;
    RecreateButtons;
  end;
end;

procedure TDiagramToolBar.SetCategory(const Value: string);
begin
  if FCategory <> Value then
  begin
    FCategory := Value;
    RecreateButtons;
  end;
end;

procedure TDiagramToolBar.CheckActions;
begin
  if (FActionList.Count <> (RegDControlList.Count + 2)) then
    CreateActions;
end;

procedure TDiagramToolBar.CancelButtonClick(Sender: TObject);
//var c: integer;
begin
  if TSpeedButton(Sender).Down then
  begin
    if Assigned(FDiagram) then
      FDiagram.CancelInsertingBlock;
  end
  else
    TSpeedButton(Sender).Down := True;
  UpdateButtons;
  {for c := 0 to ComponentCount - 1 do
    if (Components[c] is TSpeedButton) and (Components[c].Name <> 'CancelButton') then
      TSpeedButton(Components[c]).Down := False;}
end;

procedure TDiagramToolBar.ButtonClick(Sender: TObject);
begin
  if TSpeedButton(Sender).Down then
  begin
    if Assigned(FDiagram) and TSpeedButton(Sender).Down then
      FDiagram.StartInsertingControl(
        RegDControlList[TSpeedButton(Sender).Tag].DControlID)
  end else
    TSpeedButton(Sender).Down := true;
  UpdateButtons;
  {if Assigned(FindComponent('CancelButton')) then
    TSpeedButton(FindComponent('CancelButton')).Down := False;}
end;

procedure TDiagramToolBar.SetDiagram(const Value: TatDiagram);
begin
  FDiagram := Value;
  if Value <> nil then
  begin
    Value.FreeNotification(Self);
    Value.AddSubscriber(Self);
  end;
  DestroyActions;
  RecreateButtons;
end;

procedure TDiagramToolBar.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation = opRemove) and (AComponent = Diagram) then
    Diagram := nil;
  if (Operation = opRemove) and (AComponent = Images) then
    Images := nil;
end;

function TDiagramToolBar.Designing: boolean;
begin
  result := Assigned(FDiagram) and (csDesigning in FDiagram.ComponentState);
end;

procedure TDiagramToolBar.UpdateButtons;
var c: integer;
    Bt: TSpeedButton;
begin
  if Designing and Assigned(FDiagram) then
    for c := 0 to ComponentCount - 1 do
      if Components[c] is TSpeedButton then
      begin
        Bt := TSpeedButton(Components[c]);
        if (Bt.Name = SCancelButtonName) then
          Bt.Down := (FDiagram.InsertDControl = nil)
        else
        if (Bt.Name = SDeleteButtonName) then
          Bt.Enabled := (FDiagram.SelectedCount > 0)
        else
          Bt.Down := 
            (FDiagram.InsertDControl <> nil) and
            (FDiagram.InsertDControl.DControlID = RegDControlList[Bt.Tag].DControlID);
      end;
end;

procedure TDiagramToolBar.SetImages(const Value: TCustomImageList);
begin
  if Images <> nil then
    Images.UnRegisterChanges(FImageChangeLink);
  FImages := Value;
  if Images <> nil then
  begin
    Images.RegisterChanges(FImageChangeLink);
    Images.FreeNotification(Self);
  end;
end;

procedure TDiagramToolBar.ImageListChange(Sender: TObject);
begin
  RecreateButtons;
end;

procedure TDiagramToolBar.SetButtons(const Value: TDiagramBarButtons);
begin
  if FButtons <> Value then
  begin
    FButtons := Value;
    AdjustBarButtons;
    RecreateButtons;
  end;
end;

procedure TDiagramToolBar.DeleteButtonClick(Sender: TObject);
begin
  if Assigned(FDiagram) then
    FDiagram.DeleteSelecteds;
  UpdateButtons;
end;

procedure TDiagramToolBar.Rebuild;
begin
  RecreateButtons;
end;

procedure TDiagramToolBar.SetKeepInsertingMode(
  const Value: TKeepInsertingMode);
begin
  if FKeepInsertingMode <> Value then
  begin
    FKeepInsertingMode := Value;
    CreateActions;
    Rebuild;
  end;
end;

procedure TDiagramToolBar.SetToolbarMode(const Value: TToolbarMode);
begin
  if FToolbarMode <> Value then
  begin
    FToolbarMode := Value;
    AdjustBarButtons;
    DestroyActions;
    RecreateButtons;
  end;
end;

procedure TDiagramToolbar.AdjustBarButtons;
begin
  case Mode of
    tmConnections:
      FButtons := FButtons - [dbBlocks];
    tmObjects:
      FButtons := FButtons + [dbBlocks];
  end;
end;

procedure TDiagramToolBar.SetButtonSize(const Value: integer);
begin
  if FButtonSize <> Value then
  begin
    FButtonSize := Value;
    RecreateButtons;
  end;
end;

procedure TDiagramToolBar.DgrNotification(AInfo: TDgrNotificationInfo);
begin
  if AInfo.Event = deLibraryChanged then
    Rebuild;
end;

{ TDiagramButtonActionLink }

procedure TDiagramButtonActionLink.AssignClient(AClient: TObject);
begin
  inherited AssignClient(AClient);
  FClient := AClient as TSpeedButton;
end;

{$IFDEF DELPHI6_LVL}
function TDiagramButtonActionLink.Execute(AComponent: TComponent = nil): boolean;
{$ELSE}
function TDiagramButtonActionLink.Execute: boolean; 
{$ENDIF}
begin
  {$IFDEF DELPHI6_LVL}
  result := inherited Execute(AComponent);
  {$ELSE}
  result := inherited Execute;
  {$ENDIF}
  if (Action is TDiagramInsertBlock) then
    TSpeedButton(FClient).Down := true;
end;

function TDiagramButtonActionLink.IsCheckedLinked: Boolean;
begin
  Result := inherited IsCheckedLinked and (FClient <> nil) and (FClient.GroupIndex <> 0) and
    FClient.AllowAllUp and (FClient.Down = (Action as TCustomAction).Checked);
end;

procedure TDiagramButtonActionLink.SetChecked(Value: Boolean);
begin
  if IsCheckedLinked then
    TSpeedButton(FClient).Down := Value;
end;

{ TDiagramButton }

{$IFNDEF DELPHI2006_LVL}
function TDiagramButton.GetActionLinkClass: TControlActionLinkClass;
begin
  Result := TDiagramButtonActionLink;
end;
{$ENDIF}

end.
