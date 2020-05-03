{***************************************************************************}
{ Diagram Studio                                                            }
{ for Delphi & C++Builder                                                   }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright © 2003-2011                                          }
{            Email : info@tmssoftware.com                                   }
{            Web : http://www.tmssoftware.com                               }
{                                                                           }
{ TDiagramButtons - thanks to Davide Nardella for his contribution          }
{                                                                           }
{ The source code is given as is. The author is not responsible             }
{ for any possible damage done due to the use of this code.                 }
{ The components can be freely used in any application. The complete        }
{ source code remains property of the author and may not be distributed,    }
{ published, given or sold in any form as such. No parts of the source      }
{ code can be included in any other component or application without        }
{ written authorization of the author.                                      }
{***************************************************************************}

{$I DIAGRAM.INC}

unit DgrButtons;

interface

uses
  Windows, Forms, SysUtils, Classes, Controls, CategoryButtons, atDiagram,
  ImgList, Graphics;

type

  TDiagramButtonItem = class;

  /// Description:
  ///   For internal use only.
  TDiagramButtonItemActionLink = class(TButtonItemActionLink)
  private
    FClient: TDiagramButtonItem;
  protected

    /// Description:
    ///   For internal use only.
    procedure AssignClient(AClient: TObject); override;
  public

    /// Description:
    ///   For internal use only.
    function IsOnExecuteLinked: Boolean; override;
  end;

  /// Description:
  ///   TDiagramButtonItem is inherited from TButtonItem class, and represents a single button the
  ///   TDiagramButtons component.
  TDiagramButtonItem = class(TButtonItem)
  private
    //FDControlClass: TDiagramControlClass;
    FDControlID: string;
  protected

    /// Description:
    ///   For internal use only.
    function GetActionLinkClass: TButtonItemActionLinkClass; override;
  public

    /// Description:
    ///   Species the DControlID for the TDiagramControl to be inserted in the diagram when the button is clicked.  
    property DControlID: string read FDControlID write FDControlID;
    //property DControlClass: TDiagramControlClass read FDControlClass write FDControlClass;
  end;

  /// Summary:
  ///   Specifies what happens when user presses a button in TDiagramButtons component.
  TDgrKeepInsertingMode = (dkmNever, dkmAlways, dkmOnShiftPressed);

  /// Summary:
  ///   TDiagramButtons is similar to TDiagramToolbar component, but with a more modern look. It provides a
  ///   list of categories and for each category, a list of diagram objects that can be inserted in the diagram.
  ///   TDiagramButtons inherits from TCategoryButtons component, so all properties and visual features of
  ///   TCategoryButtons are present in TDiagramButtons. Since it inherited from TCategoryButtons, it's only
  ///   available for Delphi 2005 and newer versions. It's not avaible for Delphi 7 and previous versions of Delphi.
  TDiagramButtons = class(TCategoryButtons, IDiagramSubscriber)
  private
    FDiagram: TatDiagram;
    FImages : TCustomImageList;
    FCatList: TStrings;
    FShowAll: boolean;
    FShowEmptyCategory: boolean;
    FKeepInsertingMode: TDgrKeepInsertingMode;
    procedure CheckImages;
    procedure SetDiagram(const Value: TatDiagram);
    procedure SetCatList(const Value: TStrings);
    procedure CreateDgrCategory(ACaption: string);
    procedure CreateButton(aCategory: TButtonCategory; ControlIndex, index: integer);
    procedure DiagramButtonClick(sender: TObject);
    procedure SetKeepInsertingMode(const Value: TDgrKeepInsertingMode);
    procedure DgrNotification(AInfo: TDgrNotificationInfo);
  protected

    /// Description:
    ///   For internal use only.
    procedure Loaded; override;
    {$IFDEF DELPHI2009_LVL}

    /// Description:
    ///   For internal use only.
    procedure DoItemClicked(const Button: TBaseItem); override;
    {$ELSE}
    procedure DoItemClicked(const Button: TButtonItem); override;
    {$ENDIF}
  public

    /// Description:
    ///   For internal use only.
    constructor Create(AOwner: TComponent); override;

    /// Description:
    ///   For internal use only.
    destructor Destroy; override;

    /// Description:
    ///   For internal use only.
    procedure InitiateAction; override;

    /// Description:
    ///   For internal use only.
    procedure Populate;
  published

    /// Description:
    ///   Specifies the diagram component where the objects will be inserted to.
    property Diagram: TatDiagram read FDiagram write SetDiagram;

    /// Description:
    ///   DiagramCategories is a TStrings property which contains a list of the categories that will be
    ///   displayed. Just put the names of the categories, for example:
    ///   <code>
    ///   DiagramButtons1.DiagramCategories.Add('Arrows');
    ///   DiagramButtons1.DiagramCategories.Add('Flowchart');
    ///   </code>
    property DiagramCategories: TStrings read FCatList write SetCatList;

    /// Description:
    ///   If ShowAllObjects is false, only the categories of objects specified by DiagramCategories property
    ///   are displayed. If ShowAllObjects is true, an extra category called "All Objects" is created, and all
    ///   available diagram objects are displayed in that category.
    property ShowAllObjects: boolean read FShowAll write FShowAll;

    /// Description:
    ///   If ShowEmptyCategory is true, the registered objects which have no category (category is an empty
    ///   string) are displayed in a new category named "Basic". If ShowEmptyCategory is false, objects
    ///   with no category are not displayed unless ShowAllObjects property is true.
    property ShowEmptyCategory: boolean read FShowEmptyCategory write FShowEmptyCategory;

    /// Description:
    ///   Specifies what happens when user presses a button in TDiagramButtons component.
    property KeepInsertingMode: TDgrKeepInsertingMode read FKeepInsertingMode write SetKeepInsertingMode;

    property BevelKind default bkFlat;
  end;

implementation
uses ActnList;

{ TDiagramButtons }

constructor TDiagramButtons.Create(AOwner: TComponent);
begin
  inherited;
  ControlStyle := ControlStyle + [csActionClient, csClickEvents];
  FCatList := TStringList.Create;
  ButtonOptions := [boBoldCaptions, boFullSize, boGradientFill, boShowCaptions,
    boVerticalCategoryCaptions, boUsePlusMinus];
  BevelKind := bkFlat;
  BorderStyle := bsNone;
  ButtonHeight := 29;
  ButtonWidth := 29;
  FShowEmptyCategory := true;
end;

procedure TDiagramButtons.CreateButton(aCategory: TButtonCategory;
  ControlIndex, index: integer);
Var
  aButton: TDiagramButtonItem;
  aClass: TDiagramcontrolClass;
  aId: string;
  aClassName: string;
  aBitmap: TBitmap;
  aMask: TBitmap;
  aGlyph: TPicture;
  aUseGlyph: boolean;
  aHInstance: Cardinal;
begin
  aClass := RegDControlList.Items[ControlIndex].DControlClass;
  aId := RegDControlList.Items[ControlIndex].DControlID;
  aGlyph := RegDControlList.Items[ControlIndex].Glyph;
  aUseGlyph := RegDControlList.Items[ControlIndex].UseGlyph;
  aButton := TDiagramButtonItem.Create(aCategory.Items);
  aCategory.Items.AddItem(aButton,index);

  with aButton do
  begin
    DControlID := aID;
    //DControlClass := aClass;
    Caption := RegDControlList.Items[ControlIndex].Caption;
    OnClick := DiagramButtonClick;
    if not (boFullSize in ButtonOptions) then
      Hint := Caption;
  end;

  aBitmap := TBitmap.Create;
  aMask := TBitmap.Create;

  try
    if aUseGlyph then
      aBitmap.Assign(aGlyph)
    else
    begin
      {$WARNINGS OFF}
      aHInstance := FindClassHInstance(aClass);
      aID := UpperCase('BLK_' + aID);
      aBitmap.Handle := LoadBitmap(aHInstance,PChar(aID));
      {$WARNINGS ON}

      {$WARNINGS OFF}
      aHInstance := FindClassHInstance(TDiagramButtons);
      if aBitmap.Handle = 0 then
      begin
        aClassName := UpperCase('BLK_' + aClass.ClassName);
        aBitmap.Handle := LoadBitmap(aHInstance,PChar(AClassName));
      end;
      {$WARNINGS ON}

      if aBitmap.Handle = 0 then
        aBitmap.Handle := LoadBitmap(aHInstance, 'BLK_TCUSTOMDIAGRAMBLOCK');
    end;

    aMask.Assign(aBitmap);
    aMask.Mask(aMask.Canvas.Pixels[0, aMask.Height - 1]);

    if Images <> nil then
      aButton.ImageIndex := Images.Add(aBitmap,aMask);
  finally
    aBitmap.Free;
    aMask.Free;
  end;
end;

procedure TDiagramButtons.CreateDgrCategory(ACaption: string);
Var
  aCategory: TButtonCategory;
  c, x: integer;
begin
  aCategory := Categories.Add;
  aCategory.Caption := aCaption;
  aCategory.Collapsed := true;
  x := 0;
  for c:=0 to RegDControlList.Count - 1 do
  begin
   if (ACaption = 'ËùÓÐ¶ÔÏó') or SameText(RegDControlList.Items[c].Category, ACaption)
      or ((ACaption = '»ù±¾') and (Trim(RegDControlList.Items[c].Category) = '')) then
    begin
      CreateButton(aCategory, c, x);
      inc(x);
    end;
  end;
end;

destructor TDiagramButtons.Destroy;
begin
  if Assigned(FImages) then
    FImages.Free;
  FCatList.Free;  
  inherited;
end;

procedure TDiagramButtons.DgrNotification(AInfo: TDgrNotificationInfo);
begin
  if AInfo.Event = deLibraryChanged then
    Populate;
end;

procedure TDiagramButtons.DiagramButtonClick(sender: TObject);
var
  AKeepInserting: boolean;
  //AReg: TRegDControl;
  ADControlID: string;
begin
  if Assigned(FDiagram) then
  begin
    ADControlID := TDiagramButtonItem(FocusedItem).DControlID;

    Case KeepInsertingMode of
      dkmAlways:
        AKeepInserting := true;
      dkmOnShiftPressed:
        AKeepInserting := GetKeystate(VK_SHIFT) and $8000 = $8000;
//      dkmLinesOnly:
//        begin
//          AReg := RegDControlList.FindByID(ADControlID);
//          AKeepInserting := (AReg <> nil) and AReg.DControlClass.InheritsFrom(TCustomDiagramLine);
//        end;
    else
      AKeepInserting := false;
    end;
    FDiagram.StartInsertingControl(ADControlId, AKeepInserting);
  end;
end;

{$IFDEF DELPHI2009_LVL}
procedure TDiagramButtons.DoItemClicked(const Button: TBaseItem);
{$ELSE}
procedure TDiagramButtons.DoItemClicked(const Button: TButtonItem);
{$ENDIF}
begin
  if (Button is TDiagramButtonItem) and (TDiagramButtonItem(Button).Action <> nil) and
    (TDiagramButtonItem(Button).ActionLink <> nil) then
    TDiagramButtonItem(Button).ActionLink.Execute(Self)
  else
  inherited;
end;

procedure TDiagramButtons.InitiateAction;
var
  c: integer;
  d: integer;
  ItemToSelect: TButtonItem;
begin
  ItemToSelect := nil;
  if (FDiagram <> nil) and (FDiagram.InsertDControl <> nil) then
    for c := 0 to Categories.Count - 1 do
      for d := 0 to Categories[c].Items.Count - 1 do
        if TDiagramButtonItem(Categories[c].Items[d]).DControlID = FDiagram.InsertDControl.DControlID then
        begin
          ItemToSelect := Categories[c].Items[d];
          break;
        end;

  SelectedItem := ItemToSelect;
end;

procedure TDiagramButtons.CheckImages;
begin
  if not (csDesigning in ComponentState) then
  begin
    if not Assigned(Images) then
    begin
      FImages := TCustomImageList.Create(self);
      FImages.Width := 24;
      FImages.Height := 24;
      Images := FImages;
    end;
  end;
end;

procedure TDiagramButtons.Loaded;
begin
  inherited;
  if not (csDesigning in ComponentState) then
  begin
    CheckImages;
    if not (boFullSize in ButtonOptions) then
      ShowHint := true;
    Populate;
  end;
end;

procedure TDiagramButtons.Populate;

  procedure FillCatList;
  Var
    c: integer;
  begin
    TStringList(FCatList).Sorted := false;
    FCatList.Clear;
    for c := 0 to RegDControlList.Count - 1 do
    begin
      if (RegDControlList.Items[c].Category <> '') and (FCatList.IndexOf(RegDControlList.Items[c].Category) = -1) then
        FCatList.Add(RegDControlList.Items[c].Category);
    end;
    if FShowEmptyCategory then
      FCatList.Insert(1, '»ù±¾');
    if FShowAll then
      FCatList.Insert(1, 'ËùÓÐ¶ÔÏó');
    TStringList(FCatList).Sorted := true;
  end;

var
  c : integer;
begin
  CheckImages;
  FillCatList;
  Categories.Clear;
  for c := 0 to FCatList.Count - 1 do
    CreateDgrCategory(FCatList[c]);
end;

procedure TDiagramButtons.SetCatList(const Value: TStrings);
begin
  FCatList.Assign(Value);
end;

procedure TDiagramButtons.SetDiagram(const Value: TatDiagram);
begin
  if FDiagram <> Value then
  begin
    FDiagram := Value;
    if Assigned(FDiagram) then
    begin
      FDiagram.FreeNotification(Self);
      FDiagram.AddSubscriber(Self);
    end;
  end;
end;

procedure TDiagramButtons.SetKeepInsertingMode(const Value: TDgrKeepInsertingMode);
begin
  if FKeepInsertingMode <> Value then
    FKeepInsertingMode := Value;
end;

{ TDiagramButtonItem }

function TDiagramButtonItem.GetActionLinkClass: TButtonItemActionLinkClass;
begin
  result := TDiagramButtonItemActionLink;
end;

{ TDiagramButtonItemActionLink }

procedure TDiagramButtonItemActionLink.AssignClient(AClient: TObject);
begin
  FClient := AClient as TDiagramButtonItem;
end;

function TDiagramButtonItemActionLink.IsOnExecuteLinked: Boolean;
begin
  result := true;
end;

end.
