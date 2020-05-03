{***************************************************************************}
{ Diagram Studio                                                            }
{ for Delphi & C++Builder                                                   }
{ version 4.0.2                                                             }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright ?2003-2011                                          }
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

{$I diagram.inc}

unit DgrSelectors;

interface

uses
  Classes, Windows, Graphics, Controls, Messages, ExtCtrls, SysUtils, ImgList, Forms,
  Math, Dialogs
{$IFDEF TMSDOTNET}
  , uxTheme, System.Text, WinUtils, Types
{$ENDIF}
  , atDiagram, diagramshadow 
  ;

const
  MINBUTTONSIZE = 16;
  TABLECELLSIZE = 24;

  MAJ_VER = 2; // Major version nr.
  MIN_VER = 0; // Minor version nr.
  REL_VER = 0; // Release nr.
  BLD_VER = 0; // Build nr.

type
  TDgrSelectorstyle = (ssButton, ssCombo {, ssCheck});
  TAdvAppearanceStyle = (esOffice2003Blue, esOffice2003Silver, esOffice2003Olive, esOffice2003Classic, esWhidbey, esCustom, esXP);
  TAdvButtonState = (absUp, absDown, absDropDown);
  TDgrGradientDirection = (gdVertical, gdHorizontal);
  TSelectorItemType = (itAutoSizeButton, itFullWidthButton);
  TColorSelectionStyle = (csDiscrete, csColorCube, csSpectrum);
  TNoOfButtons = 1..16;

  TDgrSelectorPanel = class;

  TDgrSelectorItem = class(TCollectionItem)
  private
    FItemRect: TRect;
    FCaption: string;
    FEnable: boolean;
    FImageIndex: integer;
    FValue: string;
    FHint: string;
    FCaptionAlignment: TAlignment;
    FItemType: TSelectorItemType;
    FBackGroundColor: TColor;
    FTag: integer;
    procedure SetCaption(const Value: string);
    procedure SetEnable(const Value: boolean);
    procedure SetHint(const Value: string);
    procedure SetImageIndex(const Value: integer);
    procedure SetValue(const Value: string);
    procedure SetvCaptionAlignment(const Value: TAlignment);
    procedure SetItemType(const Value: TSelectorItemType);
    procedure SetBackGroundColor(const Value: TColor);
    procedure SetTag(const Value: integer);
  protected
    property ItemRect: TRect read FItemRect write FItemRect;

    property Enable: boolean read FEnable write SetEnable;
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
    procedure Assign(Source: TPersistent); override;
  published
    property BackGroundColor: TColor read FBackGroundColor write SetBackGroundColor default clNone;
    property Caption: string read FCaption write SetCaption;
    property CaptionAlignment: TAlignment read FCaptionAlignment write SetvCaptionAlignment;
    property ImageIndex: integer read FImageIndex write SetImageIndex;
    property Hint: string read FHint write SetHint;
    property Value: string read FValue write SetValue;
    //property Enable: boolean read FEnable write SetEnable;
    property ItemType: TSelectorItemType read FItemType write SetItemType default itAutoSizeButton;
    property Tag: integer read FTag write SetTag default 0;
    //property MultiSelect: boolean
  end;

  TDgrSelectorItems = class(TCollection)
  private
    FOwner: TPersistent;
    function GetItem(Index: Integer): TDgrSelectorItem;
    procedure SetItem(Index: Integer; const Value: TDgrSelectorItem);
  protected
    function GetOwner: TPersistent; override;
  public
    constructor Create(AOwner: TPersistent);
    function Add: TDgrSelectorItem;
    function Insert(Index: Integer): TDgrSelectorItem;
    function IndexOfValue(AValue: string): TDgrSelectorItem;
    property Items[Index: Integer]: TDgrSelectorItem read GetItem write SetItem; default;
  end;

  TChangeSelectionEvent = procedure(OldItemIndex, NewItemIndex: integer) of object;
  THotToolEvent = procedure(Sender: TObject; HotItemIndex: integer) of object;

  TDgrCustomSelectorPanel = class(TCustomPanel)
  private
    FOwner: TComponent;
    FColorTo: TColor;
    FGradientDirection: TDgrGradientDirection;
    FWindowBorderColor: TColor;
    FOnShouldHide: TNotifyEvent;
    procedure SetColorTo(const Value: TColor);
    procedure SetGradientDirection(const Value: TDgrGradientDirection);
    procedure SetWindowBorderColor(const Value: TColor);
  protected
    procedure Paint; override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    function GetVisibleHeight: integer; virtual;

    property OnShouldHide: TNotifyEvent read FOnShouldHide write FOnShouldHide;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property ColorTo: TColor read FColorTo write SetColorTo default clNone;
    property WindowBorderColor: TColor read FWindowBorderColor write SetWindowBorderColor default clGray;
    property GradientDirection: TDgrGradientDirection read FGradientDirection write SetGradientDirection;
  end;

  TItemDrawEvent = procedure(Sender: TObject; Index: integer; R: TRect) of object;

  TSelectEvent = procedure(Sender: TObject; Index: Integer; Item: TDgrSelectorItem) of object;

  TDgrSelectorPanel = class(TDgrCustomSelectorPanel)
  private
    FItemIndex: integer;                    
    FItems: TDgrSelectorItems;
    FColorHotTo: TColor;
    FBorderColor: TColor;
    FBorderDownColor: TColor;
    FColorHot: TColor;
    FBorderHotColor: TColor;
    FColorDownTo: TColor;
    FColorDown: TColor;
    FImages: TCustomImageList;
    FHotItemIndex: integer;
    FDownItemIndex: integer;
    FButtonHeight: integer;
    FTopOffSet: integer;
    FLeftOffSet: integer;
    FButtonsPerRow: TNoOfButtons;
    FOnChangeSelection: TChangeSelectionEvent;
    FButtonMargin: integer;
    FMouseDown: Boolean;
    FOnSelect: TNotifyEvent;
    FBorderSelectedColor: TColor;
    FColorSelected: TColor;
    FColorSelectedTo: TColor;
    FOnHotTool: THotToolEvent;
    FMaxCaptionLength: integer;
    FOnDrawItem: TItemDrawEvent;
    FMinButtonWidth: integer;
    FMinButtonHeight: integer;

    FNoPrefix: Boolean;
    FTwoColorImages: Boolean;
    procedure WMChar(var Msg: TWMKey); message WM_CHAR;
    procedure CMWantSpecialKey(var Msg: TCMWantSpecialKey); message CM_WANTSPECIALKEY;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;

    procedure SetBorderColor(const Value: TColor);
    procedure SetItemIndex(const Value: integer);
    procedure SetItems(const Value: TDgrSelectorItems);
    procedure SetImages(const Value: TCustomImageList);
    procedure SetButtonsPerRow(const Value: TNoOfButtons);
    procedure SetButtonMargin(const Value: integer);
    procedure SetMinButtonHeight(const Value: integer);
    procedure SetMinButtonWidth(const Value: integer);
    procedure SetTwoColorImages(const Value: Boolean);
  protected
    procedure DrawItem(Index: integer; RefreshItem: boolean = false);
    procedure Paint; override;
    procedure SetItemsPosition;
    function GetMaxWidth: integer;
    function TotalAutoSizeButtons: integer;
    function ItemAtPos(X, Y: integer): integer;
    procedure SetPanelHeight;
    procedure AutoSizeBtnSize(var W, H: integer);
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;

    property MinButtonWidth: integer read FMinButtonWidth write SetMinButtonWidth default MINBUTTONSIZE;
    property MinButtonHeight: integer read FMinButtonHeight write SetMinButtonHeight default MINBUTTONSIZE;
    property NoPrefix: Boolean read FNoPrefix write FNoPrefix;

    property TwoColorImages: Boolean read FTwoColorImages write SetTwoColorImages;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Items: TDgrSelectorItems read FItems write SetItems;
    property ItemIndex: integer read FItemIndex write SetItemIndex;
    property HotItemIndex: integer read FHotItemIndex;
  published
    property BorderColor: TColor read FBorderColor write SetBorderColor default clNone;
    property BorderDownColor: TColor read FBorderDownColor write FBorderDownColor default clNone;
    property BorderHotColor: TColor read FBorderHotColor write FBorderHotColor default clNone;
    property BorderSelectedColor: TColor read FBorderSelectedColor write FBorderSelectedColor default clBlack;

    property ColorDown: TColor read FColorDown write FColorDown;
    property ColorDownTo: TColor read FColorDownTo write FColorDownTo default clNone;
    property ColorHot: TColor read FColorHot write FColorHot;
    property ColorHotTo: TColor read FColorHotTo write FColorHotTo default clNone;
    property ColorSelected: TColor read FColorSelected write FColorSelected;
    property ColorSelectedTo: TColor read FColorSelectedTo write FColorSelectedTo;

    property ButtonsPerRow: TNoOfButtons read FButtonsPerRow write SetButtonsPerRow default 1;
    property Images: TCustomImageList read FImages write SetImages;
    property ButtonMargin: integer read FButtonMargin write SetButtonMargin default 3;

    property OnChangeSelection: TChangeSelectionEvent read FOnChangeSelection write FOnChangeSelection;
    property OnSelect: TNotifyEvent read FOnSelect write FOnSelect;
    property OnHotTool: THotToolEvent read FOnHotTool write FOnHotTool;
    property OnDrawItem: TItemDrawEvent read FOnDrawItem write FOnDrawItem;
  end;

  TColorCubeCell = record
    CenterPos: TPoint;
    Color: TColor;
  end;

  TDgrColorCubePanel = class(TDgrCustomSelectorPanel)
  private
    FCubeCells: array[1..127] of TColorCubeCell;
    FCubeSize: TPoint;
    FSelectedColor: TColor;
    FSelectedIndex: integer;
    FHotIndex: integer;
    FOnSelect: TNotifyEvent;
    FShowRGBHint: Boolean;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
    procedure DrawColorCube(Index: integer);
    procedure DrawAllColorCube;
    procedure DrawSelectedBorder;
    procedure DrawHotBorder;
    procedure SetSelectedColor(const Value: TColor);
    procedure SetSelectedIndexAndColor(clr: TColor; index: integer = -1);
    procedure SetShowRGBHint(const Value: Boolean);
  protected
    procedure Paint; override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;

    function PtInCell(Index: integer; P: TPoint): Boolean;
    function IndexOfCellAt(X, Y: integer): integer;
    procedure DrawHexagon(aCanvas: TCanvas; P: TPoint; X, Y: integer);
    procedure Initialize;
    procedure SetItemsPosition;
    procedure SetPanelSize;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property SelectedColor: TColor read FSelectedColor write SetSelectedColor;
    property ShowRGBHint: Boolean read FShowRGBHint write SetShowRGBHint;
    property OnSelect: TNotifyEvent read FOnSelect write FOnSelect;
  end;

  TDgrColorSpectrumPanel = class(TDgrCustomSelectorPanel)
  private
    FSpectrumImage: TImage;
    FHotColor: TColor;
    FSelectedColor: TColor;
    FHotRect: TRect;
    FSelectedRect: TRect;
    FOnSelect: TNotifyEvent;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
    procedure SpectrumImageMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure SpectrumImageMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure SpectrumImageMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure DrawHotRect;
    procedure DrawSelectedRect;
    procedure DrawFocusPoint;
    procedure SetSelectedColor(const Value: TColor);
  protected
    procedure Paint; override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure SetItemsPosition;
    procedure SetPanelSize;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property SelectedColor: TColor read FSelectedColor write SetSelectedColor;
    property OnSelect: TNotifyEvent read FOnSelect write FOnSelect;
  end;

  TSelectorDropDownWindow = class(TCustomForm)
  private
    FSelectorPanel: TDgrCustomSelectorPanel;
    FHideOnDeActivate: Boolean;
    FShowAbove: Boolean;
    FOwner: TComponent;
    FShowFullBorder: Boolean;
    FHideTimer: TTimer;
    FShowLeft: Boolean;
    procedure WMActivate(var Message: TWMActivate); message WM_ACTIVATE;
    procedure WMNCHitTest(var Message: TWMNCHitTest); message WM_NCHITTEST;
    procedure HideTimerOnTime(Sender: TObject);
  protected
    procedure Paint; override;
    function GetParentWnd: HWnd;
    procedure CreateParams(var Params: TCreateParams); override;
    property HideOnDeActivate: Boolean read FHideOnDeActivate write FHideOnDeActivate;
    property ShowAbove: Boolean read FShowAbove write FShowAbove;
    property ShowLeft: Boolean read FShowLeft write FShowLeft default false;
    property ShowFullBorder: Boolean read FShowFullBorder write FShowFullBorder;
  public
    constructor Create(AOwner: TComponent); override;
    constructor CreateNew(AOwner: TComponent; Dummy: Integer = 0); override;
    destructor Destroy; override;
    procedure SetWindowSize;
  published
{$IFDEF TMSDOTNET}
    property AutoScroll;
    property BorderIcons;
    property BorderWidth;
    property Ctl3D;
    property FormStyle;
    property OnHide;
{$ENDIF}
    property SelectorPanel: TDgrCustomSelectorPanel read FSelectorPanel write FSelectorPanel;
  end;

  TDrawToolEvent = procedure(Sender: TObject; Canvas: TCanvas; ItemIndex: integer; R: TRect) of object;

  TDgrCustomSelector = class(TCustomControl)
  private
    FDropDownWindow: TSelectorDropDownWindow;
    FSelectorPanel: TDgrSelectorPanel;
    FMouseInControl: Boolean;
    FMouseDown: Boolean;
    FDropDownBtnWidth: integer;
    FDown: Boolean;
    FShaded: Boolean;
    FFlat: Boolean;
    FAllowAllUp: Boolean;
    FDropDownButton: Boolean;
    FAutoThemeAdapt: Boolean;
    FStyle: TDgrSelectorstyle;
    FGlyphDown: TBitmap;
    FGlyphDisabled: TBitmap;
    FGlyphHot: TBitmap;
    FGlyph: TBitmap;
    FGlyphShade: TBitmap;
    FBorderColor: TColor;
    FColorDownTo: TColor;
    FColorTo: TColor;
    FColorHotTo: TColor;
    FColorDown: TColor;
    FBorderDownColor: TColor;
    FColorHot: TColor;
    FColorCheckedTo: TColor;
    FColorChecked: TColor;
    FBorderHotColor: TColor;
    FImages: TCustomImageList;
    FOnMouseEnter: TNotifyEvent;
    FOnDropDown: TNotifyEvent;
    FOnMouseLeave: TNotifyEvent;
    FGroupIndex: Integer;
    FAppearanceStyle: TAdvAppearanceStyle;
    FState: TAdvButtonState;
    FColorDropDownTo: TColor;
    FColorDropDown: TColor;
    FBorderDropDownColor: TColor;
    FDropDownCount: integer;
    FGradientDirection: TDgrGradientDirection;
    FSelectedIndex: integer;
    FTools: TDgrSelectorItems;
    FButtonsPerRow: TNoOfButtons;
    FColorSelectedTo: TColor;
    FColorSelected: TColor;
    FBorderSelectedColor: TColor;
    FOnHotTool: THotToolEvent;
    FOnClick: TNotifyEvent;
    FOnSelect: TSelectEvent;
    FColorSelectionHotTo: TColor;
    FColorSelectionHot: TColor;
    FColorSelectionDownTo: TColor;
    FColorSelectionDown: TColor;
    FOnDrawTool: TDrawToolEvent;
    FDupSelectedIndex: integer;
    FDiagram: TatDiagram;
    FTwoColorImages: Boolean;
    FBackGroundImageColor: TColor;
    FForeGroundImageColor: TColor;
    FOldForeGroundImgColor: TColor;
    FOldBkGroundImgColor: TColor;
    FStretchImageDraw: Boolean;
    FIsThemed: boolean;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure CMMouseEnter(var Message: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;

    procedure GlyphChanged(Sender: TObject);
    procedure OnDropDownWindowHide(Sender: TObject);
    procedure OnDropDownPanelShouldHide(Sender: TObject);
    procedure OnDropDownPanelSelect(Sender: TObject);
    procedure OnDropDownPanelHotTool(Sender: TObject; HotItemIndex: integer);
    procedure OnDropDownPanelDrawTool(Sender: TObject; ItemIndex: integer; R: TRect);
    procedure PopupBtnDown;
    procedure ButtonDown;
    procedure DoDropDown;

    procedure SetAllowAllUp(const Value: Boolean);
    procedure SetBorderColor(const Value: TColor);
    procedure SetColorChecked(const Value: TColor);
    procedure SetColorCheckedTo(const Value: TColor);
    procedure SetColorTo(const Value: TColor);
    procedure SetDown(const Value: Boolean);
    procedure SetDropDownButton(const Value: Boolean);
    procedure SetFlat(const Value: Boolean);
    procedure SetGlyph(const Value: TBitmap);
    procedure SetGlyphDisabled(const Value: TBitmap);
    procedure SetGlyphDown(const Value: TBitmap);
    procedure SetGlyphHot(const Value: TBitmap);
    procedure SetImages(const Value: TCustomImageList);
    procedure SetShaded(const Value: Boolean);
    procedure SetStyle(const Value: TDgrSelectorstyle);
    procedure SetGroupIndex(const Value: Integer);
    procedure SetAppearanceStyle(const Value: TAdvAppearanceStyle);
    procedure SetColorDropDown(const Value: TColor);
    procedure SetColorDropDownTo(const Value: TColor);
    procedure SetDropDownCount(const Value: integer);
    procedure SetGradientDirection(const Value: TDgrGradientDirection);
    function GetCaption: string;
    procedure SetCaption(const Value: string);
    procedure SetSelectedIndex(const Value: integer);
    procedure SetTools(const Value: TDgrSelectorItems);
    function GetSelectedIndex: integer;
    procedure SetButtonsPerRow(const Value: TNoOfButtons);
    function GetVersion: string;
    procedure SetVersion(const Value: string);
    procedure SetDiagram(const Value: TatDiagram);
    procedure SetTwoColorImages(const Value: Boolean);
    procedure SetForeGroundImageColor(const Value: TColor);
    procedure SetStretchImageDraw(const Value: Boolean);
  protected
    procedure DoSelect; virtual;
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); virtual;
    procedure Notification(AComponent: TComponent; AOperation: TOperation); override;
    procedure OnToolSelect; virtual;
    function DrawGlyph(aGlyph: TBitMap; aRect: TRect): integer;
    procedure DrawGlyphAndCaption(aGlyph: TBitmap; R: TRect); virtual;
    procedure DrawButton;
    procedure DrawComboButton;
    procedure SetSelectorPanelItems;
    procedure SetSelectorPanel; virtual;
    procedure Loaded; override;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState; X, Y: Integer); override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;

    procedure Paint; override;
    property MouseInControl: Boolean read FMouseInControl;
    procedure WndProc(var Message: TMessage); override;
    procedure ThemeAdapt;
    procedure SetAutoThemeAdapt(const Value: Boolean);
    function GetVersionNr: Integer; virtual;
    function DoVisualStyles: boolean;

    procedure ChangeImagesColor(ForeGColor, BkGColor: TColor);
    property TwoColorImages: Boolean read FTwoColorImages write SetTwoColorImages;
    property OldForeGroundImgColor: TColor read FOldForeGroundImgColor;
    property OldBkGroundImgColor: TColor read FOldBkGroundImgColor;
    property ForeGroundImageColor: TColor read FForeGroundImageColor write SetForeGroundImageColor;
    property BackGroundImageColor: TColor read FBackGroundImageColor write FBackGroundImageColor;

    property StretchImageDraw: Boolean read FStretchImageDraw write SetStretchImageDraw default True;

    property AllowAllUp: Boolean read FAllowAllUp write SetAllowAllUp default False;
    property AutoThemeAdapt: Boolean read FAutoThemeAdapt write SetAutoThemeAdapt;
    property ButtonsPerRow: TNoOfButtons read FButtonsPerRow write SetButtonsPerRow default 1;
    property BorderColor: TColor read FBorderColor write SetBorderColor default clNone;
    property BorderDownColor: TColor read FBorderDownColor write FBorderDownColor default clNone;
    property BorderHotColor: TColor read FBorderHotColor write FBorderHotColor default clNone;
    property BorderDropDownColor: TColor read FBorderDropDownColor write FBorderDropDownColor default clGray;
    property BorderSelectedColor: TColor read FBorderSelectedColor write FBorderSelectedColor default clBlack;
    property Caption: string read GetCaption write SetCaption;
    property Color;
    property ColorTo: TColor read FColorTo write SetColorTo default clNone;
    property ColorDown: TColor read FColorDown write FColorDown;
    property ColorDownTo: TColor read FColorDownTo write FColorDownTo default clNone;
    property ColorHot: TColor read FColorHot write FColorHot;
    property ColorHotTo: TColor read FColorHotTo write FColorHotTo default clNone;
    property ColorChecked: TColor read FColorChecked write SetColorChecked default clGray;
    property ColorCheckedTo: TColor read FColorCheckedTo write SetColorCheckedTo default clNone;
    property ColorDropDown: TColor read FColorDropDown write SetColorDropDown;
    property ColorDropDownTo: TColor read FColorDropDownTo write SetColorDropDownTo default clNone;
    property ColorSelected: TColor read FColorSelected write FColorSelected;
    property ColorSelectedTo: TColor read FColorSelectedTo write FColorSelectedTo;
    property ColorSelectionHot: TColor read FColorSelectionHot write FColorSelectionHot;
    property ColorSelectionHotTo: TColor read FColorSelectionHotTo write FColorSelectionHotTo;
    property ColorSelectionDown: TColor read FColorSelectionDown write FColorSelectionDown;
    property ColorSelectionDownTo: TColor read FColorSelectionDownTo write FColorSelectionDownTo;
    property Down: Boolean read FDown write SetDown default False;
    property DropDownButton: Boolean read FDropDownButton write SetDropDownButton default False;
    property DropDownCount: integer read FDropDownCount write SetDropDownCount;
    property Flat: Boolean read FFlat write SetFlat default True;
    property GroupIndex: Integer read FGroupIndex write SetGroupIndex default 0;
    property Glyph: TBitmap read FGlyph write SetGlyph;
    property GlyphHot: TBitmap read FGlyphHot write SetGlyphHot;
    property GlyphDown: TBitmap read FGlyphDown write SetGlyphDown;
    property GlyphDisabled: TBitmap read FGlyphDisabled write SetGlyphDisabled;
    property GradientDirection: TDgrGradientDirection read FGradientDirection write SetGradientDirection;
    property Images: TCustomImageList read FImages write SetImages;
    property Shaded: Boolean read FShaded write SetShaded default True;
    property Style: TDgrSelectorstyle read FStyle write SetStyle;

    property State: TAdvButtonState read FState write FState;
    property AppearanceStyle: TAdvAppearanceStyle read FAppearanceStyle write SetAppearanceStyle;

    property Tools: TDgrSelectorItems read FTools write SetTools;
    property SelectedIndex: integer read GetSelectedIndex write SetSelectedIndex;

    property OnMouseEnter: TNotifyEvent read FOnMouseEnter write FOnMouseEnter;
    property OnMouseLeave: TNotifyEvent read FOnMouseLeave write FOnMouseLeave;
    property OnDropDown: TNotifyEvent read FOnDropDown write FOnDropDown;

    property OnSelect: TSelectEvent read FOnSelect write FOnSelect;
    property OnHotTool: THotToolEvent read FOnHotTool write FOnHotTool;
    property OnDrawTool: TDrawToolEvent read FOnDrawTool write FOnDrawTool;
    property OnClick: TNotifyEvent read FOnClick write FOnClick;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Click; override;
    procedure ShowDropDown;
    procedure HideDropDown;
  published
    property Anchors;
    property Action;
    property TabOrder;
    property TabStop;
    property Version: string read GetVersion write SetVersion;
    property Diagram: TatDiagram read FDiagram write SetDiagram;
    property Visible;
  end;

  TDgrPenStyleSelector = class(TDgrCustomSelector)
  private
    procedure Initialize;
    function GetSelectedPenStyle: TPenStyle;
  protected
    procedure SetSelectorPanel; override;
    procedure Loaded; override;
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property AppearanceStyle;
    property SelectedPenStyle: TPenStyle read GetSelectedPenStyle;
    property Tools;
  published
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property Style;
    property ShowHint;
    property SelectedIndex;

    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;

    property OnClick;
    property OnSelect;
    property OnHotTool;
    property OnDrawTool;
  end;

  TDgrPenWidthSelector = class(TDgrCustomSelector)
  private
    procedure Initialize;
    function GetSelectedPenWidth: integer;
    procedure SelectorPanelOnDrawItem(Sender: TObject; Index: integer; R: TRect);
    function GetPenWidth(AIndex: integer): integer;
  protected
    procedure SetSelectorPanel; override;
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    property AppearanceStyle;
    property SelectedPenWidth: integer read GetSelectedPenWidth;
    property Tools;
  published
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property ShowHint;
    property Style;

    property SelectedIndex;

    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;

    property OnClick;
    property OnSelect;
    property OnHotTool;
    property OnDrawTool;
  end;

  TDgrBrushStyleSelector = class(TDgrCustomSelector)
  private
    FBrushAutoColor: boolean;
    procedure Initialize;
    procedure SelectorPanelOnDrawItem(Sender: TObject; Index: integer; R: TRect);
    function GetBrushStyle(AIndex: integer): TBrushStyle;
    function GetSelectedBrushStyle: TBrushStyle;
  protected
    procedure Loaded; override;
    procedure SetSelectorPanel; override;
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property AppearanceStyle;
    property SelectedBrushStyle: TBrushStyle read GetSelectedBrushStyle;
    property Tools;
  published
    property BrushAutoColor: boolean read FBrushAutoColor write FBrushAutoColor;
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property Style;
    property ShowHint;
    property SelectedIndex;

    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;

    property OnClick;
    property OnSelect;
    property OnHotTool;
    property OnDrawTool;
  end;

  TDgrShadowSelector = class(TDgrCustomSelector)
  private
    FShadow: TBlockShadow;
    FShowSettingsOption: boolean;
    procedure Initialize;
    procedure SetShowSettingsOption(const Value: boolean);
  protected
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
    procedure Loaded; override;
    procedure SetSelectorPanel; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property AppearanceStyle;
    property Tools;
  published
    property ShowSettingsOption: boolean read FShowSettingsOption write SetShowSettingsOption;
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property ShowHint;
    property Style;
    property SelectedIndex;

    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;

    property OnClick;
    property OnSelect;
    property OnHotTool;
    property OnDrawTool;
  end;

  TDgrTransparencySelector = class(TDgrCustomSelector)
  private
    procedure Initialize;
    function GetSelectedTransparency: integer;
    procedure SelectorPanelOnDrawItem(Sender: TObject; Index: integer; R: TRect);
  protected
    procedure SetSelectorPanel; override;
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
    constructor Create(AOwner: TComponent); override;
    property AppearanceStyle;
    property SelectedTransparency: integer read GetSelectedTransparency;
    property Tools;
  published
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property Style;
    property ShowHint;
    property SelectedIndex;

    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;

    property OnClick;
    property OnSelect;
    property OnHotTool;
    property OnDrawTool;
  end;

  TDgrGradientDirectionSelector = class(TDgrCustomSelector)
  private
    FGradient: TDiagramGradient;
    FShowSelectedGradient: boolean;
    procedure SetEndColor(const Value: TColor);
    procedure SetStartColor(const Value: TColor);
    procedure SelectorPanelOnDrawItem(Sender: TObject; Index: integer; R: TRect);
    procedure Initialize;
    function GetEndColor: TColor;
    function GetStartColor: TColor;
    function GetGradientDirection(AIndex: integer): TGradientDirection;
    procedure SetShowSelectedGradient(const Value: boolean);
  protected
    procedure DrawGlyphAndCaption(aGlyph: TBitmap; R: TRect); override;
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
    procedure SetSelectorPanel; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property AppearanceStyle;
    property Tools;
  published
    property ShowSelectedGradient: boolean read FShowSelectedGradient write SetShowSelectedGradient;
    property StartColor: TColor read GetStartColor write SetStartColor;
    property EndColor: TColor read GetEndColor write SetEndColor;

    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property Style;

    property SelectedIndex;
    property ShowHint;
    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;

    property OnClick;
    property OnSelect;
    property OnHotTool;
  end;

  TMoreColorsOptionEvent = procedure(Sender: TObject; var ANewColor: TColor; var AApply: boolean) of object;

  TDgrCustomColorSelector = class(TDgrCustomSelector)
  private
    FColorCubePanel: TDgrColorCubePanel;
    FSpectrumPanel: TDgrColorSpectrumPanel;
    FColorSelectionStyle: TColorSelectionStyle;
    FShowSelectedColor: Boolean;
    FSelectedColor: TColor;
    FShowRGBHint: Boolean;
    FShowMoreColors: boolean;
    FOnMoreColorsOption: TMoreColorsOptionEvent;
    procedure SetColorSelectionStyle(const Value: TColorSelectionStyle);
    procedure SelectorPanelOnDrawItem(Sender: TObject; Index: integer; R: TRect);
    procedure SetShowSelectedColor(const Value: Boolean);

    procedure CubePanelOnSelect(Sender: TObject);
    procedure SpectrumPanelOnSelect(Sender: TObject);
    procedure SetSelectedColor(const Value: TColor);
    function GetSelectedColor: TColor;
    procedure SetShowMoreColors(const Value: boolean);
  protected
    procedure DefaultInitialize;
    procedure Initialize; virtual;
    procedure Loaded; override;
    procedure OnToolSelect; override;
    procedure SetSelectorPanel; override;
    procedure DrawGlyphAndCaption(aGlyph: TBitmap; R: TRect); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property AppearanceStyle;
    property ButtonsPerRow;
    property SelectionStyle: TColorSelectionStyle read FColorSelectionStyle write SetColorSelectionStyle default csDiscrete;
    property ShowSelectedColor: Boolean read FShowSelectedColor write SetShowSelectedColor default true;
    property SelectedColor: TColor read GetSelectedColor write SetSelectedColor;
    property ShowRGBHint: Boolean read FShowRGBHint write FShowRGBHint;
    property ShowMoreColors: boolean read FShowMoreColors write SetShowMoreColors;
    property OnMoreColorsOption: TMoreColorsOptionEvent read FOnMoreColorsOption write FOnMoreColorsOption;
  end;

  TDgrColorSelector = class(TDgrCustomColorSelector)
  private
  protected
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
    property Tools;
  published
    property SelectionStyle;
    property ShowSelectedColor;
    property SelectedColor;
    property ShowRGBHint;
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property ShowHint;
    property Style;

    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;
    property OnClick;
    property OnSelect;

    property ShowMoreColors;
    property OnMoreColorsOption;
  end;

  TDgrTextColorSelector = class(TDgrCustomColorSelector)
  private
  protected
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
  published
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property ShowHint;
    property ShowSelectedColor;
    property SelectedColor;
    property Style;
    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;
    property OnClick;
    property OnSelect;
    property ShowMoreColors;
    property OnMoreColorsOption;
  end;

  TDgrPenColorSelector = class(TDgrCustomColorSelector)
  private
  protected
    procedure ApplyDiagramSettings(ADiagram: TatDiagram); override;
  public
  published
    property AutoThemeAdapt;
    property BorderColor;
    property BorderDownColor;
    property BorderHotColor;
    property BorderDropDownColor;
    property Caption;
    property Color;
    property ColorTo;
    property ColorDown;
    property ColorDownTo;
    property ColorHot;
    property ColorHotTo;
    property ColorDropDown;
    property ColorDropDownTo;
    property ColorSelected;
    property ColorSelectedTo;
    property DropDownButton;
    property Glyph;
    property GlyphHot;
    property GlyphDown;
    property ShowHint;
    property ShowSelectedColor;
    property SelectedColor;
    property Style;
    property OnMouseEnter;
    property OnMouseLeave;
    property OnDropDown;
    property OnClick;
    property OnSelect;
    property ShowMoreColors;
    property OnMoreColorsOption;
  end;

implementation

{$R DgrSelectors.RES}

{$WARNINGS OFF}

uses
  ComObj,
  DiagramUtils;

const
  crTMSCur1 = 54;
  // theme changed notifier
  WM_THEMECHANGED = $031A;

type
  XPColorScheme = (xpNone, xpBlue, xpGreen, xpGray);

{$IFNDEF TMSDOTNET}
var
  GetCurrentThemeName: function(pszThemeFileName: PWideChar;
    cchMaxNameChars: Integer;
    pszColorBuff: PWideChar;
    cchMaxColorChars: Integer;
    pszSizeBuff: PWideChar;
    cchMaxSizeChars: Integer): THandle cdecl stdcall;

  IsThemeActive: function: BOOL cdecl stdcall;
{$ENDIF}

{$IFNDEF TMSDOTNET}

function CurrentXPTheme: XPColorScheme;
var
  FileName, ColorScheme, SizeName: WideString;
  hThemeLib: THandle;
begin
  hThemeLib := 0;
  Result := xpNone;

  try
    hThemeLib := LoadLibrary('uxtheme.dll');

    if hThemeLib > 0 then
    begin
      IsThemeActive := GetProcAddress(hThemeLib, 'IsThemeActive');

      if Assigned(IsThemeActive) then
        if IsThemeActive then
        begin
          GetCurrentThemeName := GetProcAddress(hThemeLib, 'GetCurrentThemeName');
          if Assigned(GetCurrentThemeName) then
          begin
            SetLength(FileName, 255);
            SetLength(ColorScheme, 255);
            SetLength(SizeName, 255);
            OleCheck(GetCurrentThemeName(PWideChar(FileName), 255,
              PWideChar(ColorScheme), 255, PWideChar(SizeName), 255));
            if (PWideChar(ColorScheme) = 'NormalColor') then
              Result := xpBlue
            else if (PWideChar(ColorScheme) = 'HomeStead') then
              Result := xpGreen
            else if (PWideChar(ColorScheme) = 'Metallic') then
              Result := xpGray
            else
              Result := xpNone;
          end;
        end;
    end;
  finally
    if hThemeLib <> 0 then
      FreeLibrary(hThemeLib);
  end;
end;
{$ENDIF}

{$IFDEF TMSDOTNET}

function CurrentXPTheme: XPColorScheme;
var
  FileName, ColorScheme, SizeName: StringBuilder;
  hThemeLib: THandle;
begin
  hThemeLib := 0;
  Result := xpNone;

  if IsThemeActive then
  begin
    FileName := StringBuilder.Create(255);
    SizeName := StringBuilder.Create(255);
    ColorScheme := StringBuilder.Create(255);
    GetCurrentThemeName(FileName, 255, ColorScheme, 255, SizeName, 255);
    if (ColorScheme.ToString = 'NormalColor') then
      Result := xpBlue
    else if (ColorScheme.ToString = 'HomeStead') then
      Result := xpGreen
    else if (ColorScheme.ToString = 'Metallic') then
      Result := xpGray
  end;
end;
{$ENDIF}

//----------------------------------------------------------------- DrawGradient

//----------------------------------------------------------------- GetFileVersion
{$IFNDEF DELPHI7_LVL}
{$IFNDEF TMSDOTNET}
function GetFileVersion(FileName:string): Integer;
var
  FileHandle:dword;
  l: Integer;
  pvs: PVSFixedFileInfo;
  lptr: uint;
  querybuf: array[0..255] of char;
  buf: PChar;
begin
  Result := -1;

  StrPCopy(querybuf,FileName);
  l := GetFileVersionInfoSize(querybuf,FileHandle);
  if (l>0) then
  begin
    GetMem(buf,l);
    GetFileVersionInfo(querybuf,FileHandle,l,buf);
    if VerQueryValue(buf,'\',Pointer(pvs),lptr) then
    begin
      if (pvs^.dwSignature=$FEEF04BD) then
      begin
        Result := pvs^.dwFileVersionMS;
      end;
    end;
    FreeMem(buf);
  end;
end;
{$ENDIF}
{$ENDIF}

procedure DrawGradient(Canvas: TCanvas; FromColor, ToColor: TColor; Steps: Integer; R: TRect; Direction: Boolean);
var
  diffr, startr, endr: Integer;
  diffg, startg, endg: Integer;
  diffb, startb, endb: Integer;
  rstepr, rstepg, rstepb, rstepw: Real;
  i, stepw: Word;

begin
  if Steps = 0 then
    Steps := 1;

  FromColor := ColorToRGB(FromColor);
  ToColor := ColorToRGB(ToColor);

  startr := (FromColor and $0000FF);
  startg := (FromColor and $00FF00) shr 8;
  startb := (FromColor and $FF0000) shr 16;
  endr := (ToColor and $0000FF);
  endg := (ToColor and $00FF00) shr 8;
  endb := (ToColor and $FF0000) shr 16;

  diffr := endr - startr;
  diffg := endg - startg;
  diffb := endb - startb;

  rstepr := diffr / steps;
  rstepg := diffg / steps;
  rstepb := diffb / steps;

  if Direction then
    rstepw := (R.Right - R.Left) / Steps
  else
    rstepw := (R.Bottom - R.Top) / Steps;

  with Canvas do
  begin
    for i := 0 to steps - 1 do
    begin
      endr := startr + Round(rstepr * i);
      endg := startg + Round(rstepg * i);
      endb := startb + Round(rstepb * i);
      stepw := Round(i * rstepw);
      Pen.Color := endr + (endg shl 8) + (endb shl 16);
      Brush.Color := Pen.Color;
      if Direction then
        Rectangle(R.Left + stepw, R.Top, R.Left + stepw + Round(rstepw) + 1, R.Bottom)
      else
        Rectangle(R.Left, R.Top + stepw, R.Right, R.Top + stepw + Round(rstepw) + 1);
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure ChangeBackAndForeGroundColors(bmp: TBitMap; ForeColor, BackColor, NewForeColor, NewBackColor: TColor);
var
  w, h: Integer;
begin
  if not Assigned(bmp) then
    Exit;

  for w := 0 to bmp.Width - 1 do
  begin
    for h := 0 to bmp.Height - 1 do
    begin
      if bmp.Canvas.Pixels[w,h] = ForeColor then
        bmp.Canvas.Pixels[w,h] := NewForeColor;
     { else if (bmp.Canvas.Pixels[w,h] = BackColor) and (NewBackColor <> clNone) then
        bmp.Canvas.Pixels[w,h] := NewBackColor; }
    end;
  end;
end;

//------------------------------------------------------------------------------

{ TDgrCustomSelector }

constructor TDgrCustomSelector.Create(AOwner: TComponent);
var
  i: integer;
begin
  inherited;
  FGlyph := TBitmap.Create;
  FGlyph.OnChange := GlyphChanged;
  FGlyphHot := TBitmap.Create;
  FGlyphDown := TBitmap.Create;
  FGlyphDisabled := TBitmap.Create;
  FGlyphShade := TBitmap.Create;

  // app is linked with COMCTL32 v6 or higher -> xp themes enabled
  i := GetFileVersion('COMCTL32.DLL');
  i := (i shr 16) and $FF;
  FIsThemed := (i > 5);

  if not (csDesigning in ComponentState) then
  begin
    FDropDownWindow := TSelectorDropDownWindow.CreateNew(self);
    FDropDownWindow.BorderIcons := [];
    FDropDownWindow.BorderStyle := bsNone;
    FDropDownWindow.Ctl3D := false;
    FDropDownWindow.FormStyle := fsStayOnTop;
    FDropDownWindow.Visible := False;
    FDropDownWindow.Width := 100;
    FDropDownWindow.Height := 100;
    FDropDownWindow.AutoScroll := true;

    FDropDownWindow.BorderWidth := 0;
    FDropDownWindow.OnHide := OnDropDownWindowHide;
  end;

  SetBounds(0, 0, 23, 22);
  ControlStyle := [csCaptureMouse, csDoubleClicks];
  ParentFont := True;
  Color := clBtnFace;

  FColorTo := clNone;
  FColorHot := $D6BEB5; //RGB(182, 189, 210);
  FColorHotTo := clNone;
  FColorDown := $B59584; //RGB(133, 146, 181);
  FColorDownTo := clNone;
  FColorChecked := clGray;
  FColorCheckedTo := clNone;
  FColorDropDown := $00F7F8F9;
  FColorDropDownTo := clNone;
  FColorSelected := $DED7D6;
  FColorSelectedTo := clNone;
  FColorSelectionHot := $D6BEB5; //RGB(246, 240, 216);
  FColorSelectionHotTo := clNone;
  FColorSelectionDown := $DED7D6; //RGB(255, 169, 64);
  FColorSelectionDownTo := clNone;
  FGradientDirection := gdVertical;
  FBorderColor := clNone;
  FBorderDownColor := $6B2408;
  FBorderHotColor := $6B2408;
  FBorderDropDownColor := clGray;
  FBorderSelectedColor := clBlack;
  Flat := True;
  FShaded := True;

  FTools := TDgrSelectorItems.Create(Self);
  FSelectedIndex := -1;
  FDupSelectedIndex := -1;

  FStyle := ssButton;
  FState := absUp;
  FDropDownBtnWidth := 12;
  FButtonsPerRow := 1;

  FTwoColorImages := False;
  FOldForeGroundImgColor := clBlack;
  FOldBkGroundImgColor := clWhite;
  FForeGroundImageColor := clBlack;
  FBackGroundImageColor := clNone;

  FStretchImageDraw := True;

  AppearanceStyle := esOffice2003Classic;
end;

//------------------------------------------------------------------------------

destructor TDgrCustomSelector.Destroy;
begin
  FGlyph.Free;
  FGlyphHot.Free;
  FGlyphDown.Free;
  FGlyphDisabled.Free;
  FGlyphShade.Free;

  FTools.Free;

  if not (csDesigning in ComponentState) then
  begin
    if assigned(FSelectorPanel) then
      FSelectorPanel.Free;
    FDropDownWindow.Free;
  end;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.Click;
begin
  inherited Click;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.CMFontChanged(var Message: TMessage);
begin
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.CMMouseEnter(var Message: TMessage);
begin
  inherited;
  if FFlat and not FMouseInControl and Enabled and (GetCapture = 0) then
  begin
    FMouseInControl := True;
    Repaint;

  end;

  if Assigned(FOnMouseEnter) then
    FOnMouseEnter(Self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  if FFlat and FMouseInControl and Enabled then
  begin
    FMouseInControl := False;
    Invalidate;
  end;

  if Assigned(FOnMouseLeave) then
    FOnMouseLeave(Self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.CMTextChanged(var Message: TMessage);
begin
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.Loaded;
begin
  inherited Loaded;

  if FDupSelectedIndex < FTools.Count then
    SelectedIndex := FDupSelectedIndex;

  if AutoThemeAdapt and not (csDesigning in ComponentState) then
    ThemeAdapt;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
{var
  pt: TPoint;}
begin
  inherited MouseDown(Button, Shift, X, Y);

  FMouseDown := true;
  if Style in [ssButton {, ssCheck}] then
  begin
    if FDropDownButton and (X > (width - FDropDownBtnWidth)) then
    begin
      PopupBtnDown;
    end
    else
      ButtonDown;
  end
  else if Style = ssCombo then
  begin
    PopupBtnDown;
  end;

end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited MouseMove(Shift, X, Y);

end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  inherited MouseUp(Button, Shift, X, Y);
  FMouseDown := false;
  if (DropDownButton) and (Style = ssButton) and (x < Width - 8) then
  begin
    if Assigned(OnClick) then
      OnClick(Self);
  end;
  Invalidate;

end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.Notification(AComponent: TComponent;
  AOperation: TOperation);
begin
  inherited;
  if (AOperation = opRemove) and (AComponent = FImages) then
  begin
    FImages := nil;
    Invalidate;
  end;
  if (AOperation = opRemove) and (AComponent = Diagram) then
    Diagram := nil;
end;

//------------------------------------------------------------------------------

function TDgrCustomSelector.DrawGlyph(aGlyph: TBitMap; aRect: TRect): integer;
var
  aP: TPoint;
begin
  Result := 0;
  if not aGlyph.Empty then
  begin
    if Caption = '' then
      aP := Point(((aRect.Right - aRect.Left) - aGlyph.Width) div 2, ((aRect.Bottom - aRect.Top) - aGlyph.Height) div 2)
    else
      aP := Point(2, ((aRect.Bottom - aRect.Top) - aGlyph.Height) div 2);

    if aGlyph.Width < (aRect.Right - aRect.Left) then
    begin
      aGlyph.Transparent := true;
      Canvas.Draw(aP.X, aP.Y, aGlyph);
      Result := aP.X + aGlyph.Width + 2;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.DrawGlyphAndCaption(aGlyph: TBitmap;
  R: TRect);
var
  CapR: TRect;
  tbmp: TBitmap;

  Rgn: HRGN;
begin
  CapR := R;

  Canvas.Font.Assign(Font);

  if not Enabled then
    Canvas.Font.Color := clSilver;

  if Style = ssButton then
  begin
    if not aGlyph.Empty then
    begin
      CapR.Left := DrawGlyph(aGlyph, R);
    end
    else
    begin
      if (Caption = '') and (SelectedIndex >= 0) and Assigned(Images) then
      begin
        tbmp := TBitmap.Create;
        tbmp.Width := FImages.width;
        tbmp.Height := FImages.Height;

        tbmp.Canvas.Brush.Color := clFuchsia;
        tbmp.Canvas.FillRect(rect(0, 0, FImages.Width, FIMages.Height));

        FImages.DrawingStyle := dsTransparent;
        FImages.Draw(tbmp.Canvas, 0, 0, Tools.Items[SelectedIndex].ImageIndex);

        tbmp.Transparent := true;
        tbmp.TransparentMode := tmAuto;

        if FStretchImageDraw then
        begin
          if (tbmp.Width < (R.Right - R.Left)) and (tbmp.Height < (R.Bottom - R.Top)) then
            DrawGlyph(tbmp, R)
          else
            Canvas.StretchDraw(Rect(R.Left + 2, R.Top + 2, R.Right - 2, R.Bottom - 2), tbmp);
        end
        else // not FStretchImageDraw
        begin
          Rgn := CreateRectRgn(R.Left+2, R.Top+2, R.Right-3, R.Bottom-2);
          SelectClipRgn(Canvas.Handle, Rgn);
          Canvas.Draw(R.Left, R.Top + 2, tbmp);
          SelectClipRgn(Canvas.Handle, 0);
          DeleteObject(Rgn);
        end;
        tbmp.Free;
      end;
    end;
    if Caption <> '' then
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      DrawText(Canvas.Handle, Caption, -1, CapR, DT_SINGLELINE or DT_VCENTER);
      {$ELSE}
      DrawText(Canvas.Handle, PChar(Caption), -1, CapR, DT_SINGLELINE or DT_VCENTER);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
    DrawText(Canvas.Handle, Caption, -1, CapR, DT_SINGLELINE or DT_VCENTER);
{$ENDIF}
  end
  else if Style = ssCombo then
  begin
    if (SelectedIndex >= 0) and (Caption = '') and Assigned(FImages) then
    begin
      if Tools.Items[SelectedIndex].ImageIndex > -1 then
      begin
        tbmp := TBitmap.Create;
        tbmp.Width := FImages.width; //((R.Right - R.Left)-6));
        tbmp.Height := FImages.Height; //min(FImages.Height, (R.Bottom - R.Top)-2);
        tbmp.Transparent := true;

        FImages.DrawingStyle := dsTransparent;
        FImages.Draw(tbmp.Canvas, 0, 0, Tools.Items[SelectedIndex].ImageIndex);

        Canvas.StretchDraw(Rect(R.Left + 2, R.Top + 2, R.Right - 2, R.Bottom - 2), tbmp);
        tbmp.Free;
      end;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.DrawButton;
var
  R, R2, BtnR, CapR: TRect;
  AP {, GP}: TPoint;

  procedure DrawArrow(ArP: TPoint; ArClr: TColor);
  begin
    Canvas.Pen.Color := ArClr;
    Canvas.MoveTo(ArP.X, ArP.Y);
    Canvas.LineTo(ArP.X + 5, ArP.Y);
    Canvas.MoveTo(ArP.X + 1, ArP.Y + 1);
    Canvas.LineTo(ArP.X + 4, ArP.Y + 1);
    Canvas.Pixels[ArP.X + 2, ArP.Y + 2] := ArClr;
  end;
begin
  R := Rect(0, 0, Width, Height);

  if Style in [ssButton {, ssCheck}] then
  begin
    if FDropDownButton then
    begin
      R2 := Rect(R.Left, R.Top, R.Right - FDropDownBtnWidth, R.Bottom);
      CapR := Rect(R.Left + 2, R.Top, R2.Right, R.Bottom);
      BtnR := Rect(R.Right - FDropDownBtnWidth, R.Top, R.Right, R.Bottom);
    end
    else
    begin
      R2 := R;
      CapR := Rect(R.Left + 2, R.Top, R2.Right, R.Bottom);
      BtnR := Rect(-1, -1, -1, -1);
    end;

    AP.X := BtnR.Left + ((BtnR.Right - BtnR.Left - 5) div 2) + 1;
    AP.Y := BtnR.Top + ((BtnR.Bottom - BtnR.Top - 3) div 2) + 1;

    if state = absUp then
    begin
      if FMouseInControl and Enabled and not (csDesigning in ComponentState) then
      begin
        if FMouseDown then
        begin // Down
          if FDropDownButton then
          begin
            if ColorHotTo <> clNone then
              DrawGradient(Canvas, ColorHot, ColorHotTo, 16, R, false)
            else
            begin
              Canvas.Pen.Color := ColorHot;
              Canvas.Brush.Color := ColorHot;
              Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
            end;
            Canvas.Brush.Style := bsClear;

            if BorderHotColor <> clNone then
            begin
              Canvas.Pen.Color := BorderHotColor;
              Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
            end;

            Canvas.MoveTo(BtnR.Left, R.Top);
            Canvas.LineTo(BtnR.Left, R.Bottom);
            DrawArrow(AP, clBlack);
          end;

          if ColorDownTo <> clNone then
            DrawGradient(Canvas, ColorDown, ColorDownTo, 16, R2, false)
          else
          begin
            Canvas.Brush.Color := FColorDown;
            Canvas.Pen.Color := FColorDown;
            Canvas.Rectangle(R2.Left, R2.Top, R2.Right, R2.Bottom);
          end;
          Canvas.Brush.Style := bsClear;

          if BorderDownColor <> clNone then
          begin
            Canvas.Pen.Color := BorderDownColor;
            Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          end;

          if not GlyphDown.Empty then
            DrawGlyphAndCaption(GlyphDown, CapR)
          else //if not Glyph.Empty then
            DrawGlyphAndCaption(Glyph, CapR);
        end
        else // Hot
        begin
          if ColorHotTo <> clNone then
            DrawGradient(Canvas, ColorHot, ColorHotTo, 16, R, false)
          else
          begin
            Canvas.Pen.Color := ColorHot;
            Canvas.Brush.Color := ColorHot;
            Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          end;

          Canvas.Brush.Style := bsClear;

          if BorderHotColor <> clNone then
          begin
            Canvas.Pen.Color := BorderHotColor;
            Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          end;

          if not GlyphHot.Empty then
            DrawGlyphAndCaption(GlyphHot, CapR)
          else //if not Glyph.Empty then
            DrawGlyphAndCaption(Glyph, CapR);

          if FDropDownButton then
          begin
            Canvas.MoveTo(BtnR.Left, R.Top);
            Canvas.LineTo(BtnR.Left, R.Bottom);

            DrawArrow(AP, clBlack);
          end;
        end;
      end
      else // Normal
      begin
        if not Enabled then
        begin
          Canvas.Pen.Color := clGray;
          Canvas.Brush.Color := clSilver;
          Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
        end
        else
        begin

          if ColorTo <> clNone then
            DrawGradient(Canvas, Color, ColorTo, 16, R, false)
          else
          begin
            Canvas.Pen.Color := Color;
            Canvas.Brush.Color := Color;
            Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          end;

          Canvas.Brush.Style := bsClear;
          if BorderColor <> clNone then
          begin
            Canvas.Pen.Color := BorderColor;
            Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          end;
        end;

        R2.Left := R2.Left + 1;

        DrawGlyphAndCaption(Glyph, CapR);

        if FDropDownButton then
        begin
          Canvas.MoveTo(BtnR.Left, R.Top);
          Canvas.LineTo(BtnR.Left, R.Bottom);
          if Enabled then
            DrawArrow(AP, clBlack)
          else
            DrawArrow(AP, clGray);
        end;
      end;
    end
    else if State = absDropDown then
    begin // DropDown State
      if (ColorTo <> clNone) then
        DrawGradient(Canvas, Color, ColorTo, 16, R, false)
      else
      begin
        Canvas.Pen.Color := Color;
        Canvas.Brush.Color := Color;
        Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
      end;

      {
      if ColorDropDownTo <> clNone then
        DrawGradient(Canvas, ColorDropDown, ColorDropDownTo, 16, R, true)
      else
      begin
        Canvas.Pen.Color := ColorDropDown;
        Canvas.Brush.Color := ColorDropDown;
        Canvas.Rectangle(R);
      end;
      }

      Canvas.Brush.Style := bsClear;

      if BorderDropDownColor <> clNone then
      begin
        Canvas.Pen.Color := BorderDropDownColor;
        Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
      end;

      {
      if not Glyph.Empty then
      begin
        if Caption = '' then
          GP:= Point(((R2.Right - R2.Left) - Glyph.Width) div 2, ((R2.Bottom - R2.Top) - Glyph.Height) div 2)
        else
          GP:= Point(2, ((R2.Bottom - R2.Top) - Glyph.Height) div 2);

        Glyph.Transparent:= true;
        Canvas.Draw(GP.X, GP.Y, Glyph);
        CapR.Left:= GP.X + Glyph.Width + 2;
      end;
      }
//      DrawGlyphAndCaption(Glyph, R2);

      DrawGlyphAndCaption(Glyph, CapR);

      if FDropDownButton then
      begin
        if Enabled then
          DrawArrow(AP, clBlack)
        else
          DrawArrow(AP, clSilver);
      end;
    end;
  end;
end;

//------------------------------------------------------------------------------

function TDgrCustomSelector.DoVisualStyles: Boolean;
begin
  if FIsThemed then
    Result := IsThemeActive
  else
    Result := False;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.DrawComboButton;
var
  R, R2, BtnR, CapR: TRect;
  AP: TPoint;

  procedure DrawArrow(ArP: TPoint; ArClr: TColor);
  begin
    Canvas.Pen.Color := ArClr;
    Canvas.MoveTo(ArP.X, ArP.Y);
    Canvas.LineTo(ArP.X + 5, ArP.Y);
    Canvas.MoveTo(ArP.X + 1, ArP.Y + 1);
    Canvas.LineTo(ArP.X + 4, ArP.Y + 1);
    Canvas.Pixels[ArP.X + 2, ArP.Y + 2] := ArClr;
  end;

  procedure DrawButton;
  var
    ARect: TRect;
    //htheme: THandle;
  begin
    GetWindowRect(Handle, ARect);
    OffsetRect(ARect, -ARect.Left, -ARect.Top);
    Inc(ARect.Left, ClientWidth - FDropDownBtnWidth);
    InflateRect(ARect, -1, -1);

    (*if DoVisualStyles then
    begin
      htheme := OpenThemeData(Handle,'combobox');acxpvs

      if not Enabled then
      begin
        {$IFNDEF TMSDOTNET}
        DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_DISABLED,@ARect,nil)
        {$ENDIF}
        {$IFDEF TMSDOTNET}
        DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_DISABLED,ARect,nil)
        {$ENDIF}
      end
      else
      begin
        if FMouseDown and (state = absUp) then
        begin
          {$IFNDEF TMSDOTNET}
          DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_PRESSED,@ARect,nil)
          {$ENDIF}
          {$IFDEF TMSDOTNET}
          DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_PRESSED,ARect,nil)
          {$ENDIF}
        end
        else
        begin
          {$IFNDEF TMSDOTNET}
          if not FMouseDown and FMouseInControl and not (state = absDown) then
            DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_HOT,@ARect,nil)
          else
          DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_NORMAL,@ARect,nil);
          {$ENDIF}
          {$IFDEF TMSDOTNET}
          if not FMouseDown and FMouseInControl and not (state = absDown) then
            DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_HOT,ARect,nil)
          else
          DrawThemeBackground(htheme,Canvas.Handle,CP_DROPDOWNBUTTON,CBXS_NORMAL,ARect,nil);
          {$ENDIF}
        end;
      end;

      CloseThemeData(htheme);
    end
    else *)
    begin
      if Enabled then
        DrawFrameControl(Canvas.Handle, ARect, DFC_SCROLL, DFCS_SCROLLCOMBOBOX or DFCS_FLAT )
      else
        DrawFrameControl(Canvas.Handle, ARect, DFC_SCROLL, DFCS_SCROLLCOMBOBOX or DFCS_INACTIVE )
    end;

    //ExcludeClipRect(Canvas.Handle, ClientWidth - FButtonWidth -4 , 0, ClientWidth +2, ClientHeight);
  end;

begin
  R := Rect(0, 0, Width, Height);

  if Style = ssCombo then
  begin
    R2 := Rect(R.Left, R.Top, R.Right - FDropDownBtnWidth, R.Bottom);
    CapR := Rect(R.Left + 2, R.Top, R2.Right, R.Bottom);
    BtnR := Rect(R.Right - FDropDownBtnWidth - 1, R.Top + 1, R.Right - 1, R.Bottom - 1);

    AP.X := BtnR.Left + ((BtnR.Right - BtnR.Left - 5) div 2) + 1;
    AP.Y := BtnR.Top + ((BtnR.Bottom - BtnR.Top - 3) div 2) + 1;

    if AppearanceStyle = esXP then
    begin
      Canvas.Brush.Style := bsSolid;
      Canvas.Brush.Color := clWindow;
      Canvas.Pen.Color := BorderColor;
      Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);

      DrawButton;

      DrawGlyphAndCaption(Glyph, R2);
      Exit;
    end;

    if state = absUp then
    begin
      if FMouseInControl and not (csDesigning in ComponentState) then
      begin
        if FMouseDown then
        begin // Down

        end
        else // Hot
        begin
          Canvas.Pen.Color := clWhite;
          Canvas.Brush.Color := clWhite;
          Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);


          if ColorHotTo <> clNone then
            DrawGradient(Canvas, ColorHot, ColorHotTo, 16, BtnR, false)
          else
          begin
            Canvas.Pen.Color := ColorHot;
            Canvas.Brush.Color := ColorHot;
            Canvas.Rectangle(BtnR.Left, BtnR.Top, BtnR.Right, BtnR.Bottom);
          end;

          Canvas.Brush.Style := bsClear;

          if BorderHotColor <> clNone then
          begin
            Canvas.Pen.Color := BorderHotColor;
            Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          end;
          if not GlyphHot.Empty then
            DrawGlyphAndCaption(GlyphHot, R2)
          else
            DrawGlyphAndCaption(GlyphHot, R2);

          Canvas.MoveTo(BtnR.Left, R.Top);
          Canvas.LineTo(BtnR.Left, R.Bottom);
          DrawArrow(AP, clBlack);
        end;
      end
      else // Normal
      begin
        Canvas.Pen.Color := clWhite;
        Canvas.Brush.Color := clWhite;
        Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);

        if ColorTo <> clNone then
          DrawGradient(Canvas, Color, ColorTo, 16, Rect(BtnR.Left, BtnR.Top, BtnR.Right, BtnR.Bottom - 1), false)
        else
        begin
          Canvas.Pen.Color := Color;
          Canvas.Brush.Color := Color;
          Canvas.Rectangle(BtnR.Left, BtnR.Top, BtnR.Right, BtnR.Bottom);
        end;

        Canvas.Brush.Style := bsClear;
        if BorderColor <> clNone then
        begin
          Canvas.Pen.Color := BorderColor;
          Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
          Canvas.MoveTo(BtnR.Left, R.Top);
          Canvas.LineTo(BtnR.Left, R.Bottom);
        end;
        DrawGlyphAndCaption(Glyph, R2);

        //Canvas.MoveTo(BtnR.Left, BtnR.Top);
        //Canvas.LineTo(BtnR.Left, BtnR.Bottom);
        DrawArrow(AP, clBlack);
      end;

    end
    else
    if State = absDropDown then
    begin // DropDown State

      Canvas.Pen.Color := clWhite;
      Canvas.Brush.Color := clWhite;
      Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);

      if ColorDownTo <> clNone then
        DrawGradient(Canvas, ColorDown, ColorDownTo, 16, BtnR, false)
      else
      begin
        Canvas.Pen.Color := ColorDown;
        Canvas.Brush.Color := ColorDown;
        Canvas.Rectangle(BtnR.Left, BtnR.Top, BtnR.Right, BtnR.Bottom);
      end;

      Canvas.Brush.Style := bsClear;

      if BorderDownColor <> clNone then
      begin
        Canvas.Pen.Color := BorderDownColor;
        Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
        Canvas.MoveTo(BtnR.Left, R.Top);
        Canvas.LineTo(BtnR.Left, R.Bottom);
      end;
      DrawGlyphAndCaption(Glyph, R2);

      DrawArrow(AP, clBlack);

    end;

  end;

end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.Paint;
begin
  if Style in [ssButton {, ssCheck}] then
  begin
    Canvas.Font := Self.Font;
    if not FFlat then
    begin

    end
    else
    begin
      DrawButton;
    end;
  end
  else //Style = ssCombo
  begin
    DrawComboButton;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetAutoThemeAdapt(const Value: Boolean);
begin
  FAutoThemeAdapt := Value;

  if not (csDesigning in ComponentState) then
  begin
    if FAutoThemeAdapt then
      ThemeAdapt;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.ThemeAdapt;
var
  eTheme: XPColorScheme;
begin
  eTheme := CurrentXPTheme();
  case eTheme of
    xpBlue: AppearanceStyle := esOffice2003Blue;
    xpGreen: AppearanceStyle := esOffice2003Olive;
    xpGray: AppearanceStyle := esOffice2003Silver;
  else
    AppearanceStyle := esOffice2003Classic;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.WndProc(var Message: TMessage);
begin
  // message does not seem to get through always?
  if (Message.Msg = WM_THEMECHANGED) and AutoThemeAdapt then
  begin
    ThemeAdapt;
  end;

  if (Message.Msg = CM_SYSFONTCHANGED) and AutoThemeAdapt then
  begin
    ThemeAdapt;
  end;

  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetAllowAllUp(const Value: Boolean);
begin
  if FAllowAllUp <> Value then
  begin
    FAllowAllUp := Value;
    //UpdateExclusive;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetBorderColor(const Value: TColor);
begin
  FBorderColor := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetColorChecked(const Value: TColor);
begin
  FColorChecked := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetColorCheckedTo(const Value: TColor);
begin
  FColorCheckedTo := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetColorTo(const Value: TColor);
begin
  FColorTo := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetDown(const Value: Boolean);
begin
{  if (FGroupIndex = 0) and (Style = tasButton) then
    Value := False;

  if (Style = tasCheck) then
  begin
    FDown := Value;
    Repaint;
    Exit;
  end;

  if Value <> FDown then
  begin
    if FDown and (not FAllowAllUp) then Exit;
    FDown := Value;
    if Value then
    begin
      if FState = bsUp then Invalidate;
      FState := bsExclusive
    end
    else
    begin
      FState := bsUp;
      Repaint;
    end;
    if Value then UpdateExclusive;
  end;
}
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetDropDownButton(const Value: Boolean);
begin
  FDropDownButton := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetFlat(const Value: Boolean);
begin
  if Value <> FFlat then
  begin
    FFlat := Value;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetGlyph(const Value: TBitmap);
var
  x, y: Integer;
  PxlColor: TColor;
  c: byte;
begin
  FGlyph.Assign(Value);
  //if no disabled glyph is given... add this automatically...
  if FGlyphDisabled.Empty then
  begin
    FGlyphDisabled.Assign(Value);
    for x := 0 to FGlyphDisabled.Width - 1 do
      for y := 0 to FGlyphDisabled.Height - 1 do
      begin
        PxlColor := ColorToRGB(FGlyphDisabled.Canvas.Pixels[x, y]);
        c := Round((((PxlColor shr 16) + ((PxlColor shr 8) and $00FF) +
          (PxlColor and $0000FF)) div 3)) div 2 + 96;
        FGlyphDisabled.Canvas.Pixels[x, y] := RGB(c, c, c);
      end;
  end;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetGlyphDisabled(const Value: TBitmap);
begin
  FGlyphDisabled.Assign(Value);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetGlyphDown(const Value: TBitmap);
begin
  FGlyphDown.Assign(Value);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetGlyphHot(const Value: TBitmap);
begin
  FGlyphHot.Assign(Value);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetImages(const Value: TCustomImageList);
begin
  if Value <> FImages then
  begin
    FImages := Value;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetShaded(const Value: Boolean);
begin
  FShaded := Value;

  if FShaded then
    if not (csLoading in ComponentState) then
    begin
      //GenerateShade;
    end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetStyle(const Value: TDgrSelectorstyle);
begin
  FStyle := Value;

  if (csDesigning in ComponentState) and not (csLoading in ComponentState) then
  begin
    if Value = ssButton then
      Width := 23
    else
      Width := 128;
  end;

  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetGroupIndex(const Value: Integer);
begin
  if FGroupIndex <> Value then
  begin
    FGroupIndex := Value;
    //UpdateExclusive;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.GlyphChanged(Sender: TObject);
begin
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetAppearanceStyle(
  const Value: TAdvAppearanceStyle);
begin
  FAppearanceStyle := Value;
  FDropDownBtnWidth := 12;
  case FAppearanceStyle of
    esOffice2003Blue:
      begin
        Color := $FDEADA;
        ColorTo := $E4AE88;

        ColorSelected := RGB(255, 191, 113); //$94E6FB;
        ColorSelectedTo := clNone; //$1595EE;

        ColorDown := $087FE8;
        ColorDownTo := $7CDAF7;

        ColorHot := $DCFFFF;
        ColorHotTo := $5BC0F7;

        ColorSelectionHot := $C2EEFF; //RGB(246, 240, 216);
        ColorSelectionHotTo := clNone;

        ColorSelectionDown := $6FC0FF; // RGB(255, 169, 64);
        ColorSelectionDownTo := clNone;

        BorderColor := clNone;
        BorderHotColor := clBlack;
        BorderDropDownColor := $962D00;

        GradientDirection := gdVertical;
      end;
    esOffice2003Olive:
      begin
        Color := $CFF0EA;
        ColorTo := $8CC0B1;

        ColorSelected := RGB(255, 191, 113); //$94E6FB;
        ColorSelectedTo := clNone; //$1595EE;

        ColorDown := $087FE8;
        ColorDownTo := $7CDAF7;

        ColorHot := $DCFFFF;
        ColorHotTo := $5BC0F7;

        ColorSelectionHot := $C2EEFF; //RGB(246, 240, 216);
        ColorSelectionHotTo := clNone;

        ColorSelectionDown := $6FC0FF; // RGB(255, 169, 64);
        ColorSelectionDownTo := clNone;

        BorderColor := clNone;
        BorderHotColor := clBlack;
        BorderDropDownColor := $5E8D75;

        GradientDirection := gdVertical;
      end;
    esOffice2003Silver:
      begin
        Color := $ECE2E1;
        ColorTo := $B39698;
        ColorSelected := RGB(255, 191, 113); //$94E6FB;
        ColorSelectedTo := clNone; //$1595EE;

        ColorDown := $087FE8;
        ColorDownTo := $7CDAF7;

        ColorHot := $DCFFFF;
        ColorHotTo := $5BC0F7;

        ColorSelectionHot := $C2EEFF; //RGB(246, 240, 216);
        ColorSelectionHotTo := clNone;

        ColorSelectionDown := $6FC0FF; // RGB(255, 169, 64);
        ColorSelectionDownTo := clNone;

        BorderColor := clNone;
        BorderHotColor := clBlack;
        BorderDropDownColor := $947C7C;

        GradientDirection := gdVertical;
      end;
    esOffice2003Classic:
      begin
        Color := clBtnFace;
        ColorTo := clNone;

        ColorSelected := $DED7D6;
        ColorSelectedTo := clNone;

        ColorDown := $B59584;
        ColorDownTo := clNone; //$B59285;

        ColorHot := $D6BEB5;
        ColorHotTo := clNone; //$D2BDB6;

        ColorSelectionHot := $D6BEB5; //RGB(246, 240, 216);
        ColorSelectionHotTo := clNone;

        ColorSelectionDown := $DED7D6; // RGB(133, 146, 181);
        ColorSelectionDownTo := clNone;

        BorderColor := clNone;
        BorderHotColor := clBlack;
        BorderDropDownColor := clGray;

        GradientDirection := gdVertical;
      end;
  end;
end;

procedure TDgrCustomSelector.DoSelect;
begin
  if Assigned(FDiagram) then
    ApplyDiagramSettings(FDiagram);
  if Assigned(FOnSelect) then
  begin
    if Assigned(FSelectorPanel) then
    begin
      if (FSelectorPanel.ItemIndex >= 0) and (FSelectorPanel.ItemIndex < Tools.Count) then
        FOnSelect(Self, FSelectorPanel.ItemIndex, Tools[FSelectorPanel.ItemIndex])
      else
        FOnSelect(Self, FSelectorPanel.ItemIndex, nil)
    end
    else
      FOnSelect(Self, -1, nil)
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.ButtonDown;
begin
  if not FDropDownButton then
    DoDropDown
  else
  begin
    DoSelect;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.DoDropDown;
var
  R: TRect;
  P: TPoint;
begin
  if not Assigned(FDropDownWindow) then
    exit;

  if FDropDownWindow.Visible then
  begin
    HideDropDown;
    exit;
  end;

  SetSelectorPanel;
{$IFNDEF TMSDOTNET}
  FDropDownWindow.Position := poDesigned;
{$ENDIF}
  FDropDownWindow.SetWindowSize;

{$IFNDEF TMSDOTNET}
  SystemParametersInfo(SPI_GETWORKAREA, 0, @R, 0);
{$ENDIF}
{$IFDEF TMSDOTNET}
  SystemParametersInfo(SPI_GETWORKAREA, 0, R, 0);
{$ENDIF}

  P := Point(0, self.Height);
  P := ClientToScreen(P);

  if R.Bottom > (P.Y + FDropDownWindow.Height + 2) then
  begin
    FDropDownWindow.Left := P.X;
    if FDropDownWindow.Left + FDropDownWindow.Width > R.Right then
    begin
      FDropDownWindow.Left:= (P.X+ Width) - FDropDownWindow.Width;
      FDropDownWindow.ShowLeft:= true;
    end
    else
      FDropDownWindow.ShowLeft:= false;

    FDropDownWindow.Top := P.Y - 1;
    FDropDownWindow.ShowAbove := false;
  end
  else
  begin
    FDropDownWindow.Left := P.X;

    if FDropDownWindow.Left + FDropDownWindow.Width > R.Right then
    begin
      FDropDownWindow.Left:= (P.X+ Width) - FDropDownWindow.Width;
      FDropDownWindow.ShowLeft:= true;
    end
    else
      FDropDownWindow.ShowLeft:= false;

    FDropDownWindow.Top := P.Y - self.Height - FDropDownWindow.Height + 1;
    FDropDownWindow.ShowAbove := true;
  end;

  FDropDownWindow.ShowFullBorder := Style = ssCombo;

  State := absDropDown;
  //SetSelectorPanel;
  //FDropDownWindow.SetWindowSize;

  //FDropDownWindow.Width:= 100;
  FDropDownWindow.Visible := true;

  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.HideDropDown;
begin
  FDropDownWindow.Visible := false;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.PopupBtnDown;
begin
  DoDropDown;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetColorDropDown(const Value: TColor);
begin
  FColorDropDown := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetColorDropDownTo(const Value: TColor);
begin
  FColorDropDownTo := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetSelectorPanelItems;
var
  i: integer;
begin
  FSelectorPanel.Items.Clear;
  for i := 0 to Tools.Count - 1 do
  begin
    with FselectorPanel.Items.Add do
    begin
      Caption := Tools.Items[i].Caption;
      CaptionAlignment := Tools.Items[i].CaptionAlignment;
      ImageIndex := Tools.Items[i].ImageIndex;
      Hint := Tools.Items[i].Hint;
      Value := Tools.Items[i].Value;
      Enable := Tools.Items[i].Enable;
      ItemType := Tools.Items[i].ItemType;
      BackGroundColor := Tools.Items[i].BackGroundColor;
    end;
  end;

  FSelectorPanel.ItemIndex := FSelectedIndex;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetSelectorPanel;
begin
  if not assigned(FSelectorPanel) and assigned(FDropDownWindow) then
  begin
    FSelectorPanel := TDgrSelectorPanel.Create(FDropDownWindow);
    FSelectorPanel.Parent := FDropDownWindow;
  end;
  FSelectorPanel.WindowBorderColor := FBorderDropDownColor;
  FSelectorPanel.OnShouldHide := OnDropDownPanelShouldHide;
  FSelectorPanel.OnSelect := OnDropDownPanelSelect;
  FSelectorPanel.OnHotTool := OnDropDownPanelHotTool;

  if Assigned(FOnDrawTool) then
    FSelectorPanel.OnDrawItem := OnDropDownPanelDrawTool
  else
    FSelectorPanel.OnDrawItem := nil;

  FSelectorPanel.Color := ColorDropDown;
  FSelectorPanel.ColorTo := ColorDropDownTo;

  FSelectorPanel.BorderColor := BorderColor;
  FSelectorPanel.BorderDownColor := FBorderDownColor;
  FSelectorPanel.BorderHotColor := BorderHotColor;
  FSelectorPanel.BorderSelectedColor := BorderSelectedColor;


  FSelectorPanel.ColorDown := FColorSelectionDown; // ColorDown;
  FSelectorPanel.ColorDownTo := FColorSelectionDownTo; //ColorDownTo;
  FSelectorPanel.ColorHot := FColorSelectionHot; //  ColorHot;
  FSelectorPanel.ColorHotTo := FColorSelectionHotTo; //ColorHotTo;
  FSelectorPanel.ColorSelected := ColorSelected;
  FSelectorPanel.ColorSelectedTo := ColorSelectedTo;

  FSelectorPanel.Images := Images;


  SetSelectorPanelItems;
  FSelectorPanel.ButtonsPerRow := ButtonsPerRow;

  FSelectorPanel.SetItemsPosition;
  FDropDownWindow.SelectorPanel := FSelectorPanel;

  FSelectorPanel.Left := 0; //1;
  FSelectorPanel.Top := 0; //1;

  FSelectorPanel.TwoColorImages := self.TwoColorImages;

  //FSelectorPanel.Height:= 140;
  //FSelectorPanel.Width:= 120;

  //FSelectorPanel.Color:= clyellow;

end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetDropDownCount(const Value: integer);
begin
  FDropDownCount := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetGradientDirection(
  const Value: TDgrGradientDirection);
begin
  FGradientDirection := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.OnDropDownWindowHide(Sender: TObject);
begin
  State := absUp;
  Invalidate;
end;

//------------------------------------------------------------------------------

function TDgrCustomSelector.GetCaption: string;
begin
  Result := inherited Caption;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetCaption(const Value: string);
begin
  inherited Caption := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.OnDropDownPanelShouldHide(Sender: TObject);
begin
  HideDropDown;
end;

//------------------------------------------------------------------------------

function TDgrCustomSelector.GetSelectedIndex: integer;
begin
  Result := FSelectedIndex;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetSelectedIndex(const Value: integer);
begin
  if Value < Tools.Count then
  begin
    FSelectedIndex := Value;
    //OnToolSelect;
    Invalidate;
  end;
  FDupSelectedIndex := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetTools(const Value: TDgrSelectorItems);
begin
  FTools := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.OnDropDownPanelSelect(Sender: TObject);
begin
  SelectedIndex := FSelectorPanel.ItemIndex;
  OnToolSelect;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetButtonsPerRow(const Value: TNoOfButtons);
begin
  FButtonsPerRow := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.OnDropDownPanelHotTool(Sender: TObject;
  HotItemIndex: integer);
begin
  if Assigned(FOnHotTool) then
    FOnHotTool(self, HotItemIndex);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.OnToolSelect;
begin
  DoSelect;
end;

procedure TDgrCustomSelector.ApplyDiagramSettings(ADiagram: TatDiagram);
begin
end;

//------------------------------------------------------------------------------


procedure TDgrCustomSelector.OnDropDownPanelDrawTool(Sender: TObject;
  ItemIndex: integer; R: TRect);
begin
  if Assigned(FOnDrawTool) then
    FOnDrawTool(self, FSelectorPanel.Canvas, ItemIndex, R);
end;

function TDgrCustomSelector.GetVersionNr: Integer;
begin
  Result := MakeLong(MakeWord(BLD_VER, REL_VER), MakeWord(MIN_VER, MAJ_VER));
end;

function TDgrCustomSelector.GetVersion: string;
var
  vn: Integer;
begin
  vn := GetVersionNr;
  Result := IntToStr(Hi(Hiword(vn))) + '.' + IntToStr(Lo(Hiword(vn))) + '.' + IntToStr(Hi(Loword(vn))) + '.' + IntToStr(Lo(Loword(vn)));
end;

procedure TDgrCustomSelector.SetVersion(const Value: string);
begin

end;

procedure TDgrCustomSelector.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited;
  if (Key = VK_F2) then
    DoDropDown;
end;

procedure TDgrCustomSelector.SetDiagram(const Value: TatDiagram);
begin
  FDiagram := Value;
  if Value <> nil then Value.FreeNotification(Self);
end;

procedure TDgrCustomSelector.ShowDropDown;
begin
  DoDropDown;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetTwoColorImages(const Value: Boolean);
begin
  FTwoColorImages := Value;
  if FTwoColorImages then
    ChangeImagesColor(FForeGroundImageColor, FBackGroundImageColor);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.ChangeImagesColor(ForeGColor,
  BkGColor: TColor);
var
  I: Integer;
  bmp: TBitMap;
  ImgList: TCustomImageList;
begin
  if Assigned(FImages) then
  begin
    ImgList:= TCustomImageList.Create(self);
    ImgList.Width := FImages.Width;
    ImgList.Height := FImages.Height;
    for I := 0 to FImages.Count-1 do
    begin
      bmp := TBitMap.Create;
      bmp.Width := FImages.Width;
      bmp.Height := FImages.Height;

      {$IFDEF DELPHI7_LVL}
      if FImages.GetBitmap(I, bmp) then
      {$ELSE}
      FImages.GetBitmap(I, bmp);
      {$ENDIF}
      begin
        ChangeBackAndForeGroundColors(bmp, FOldForeGroundImgColor, FOldBkGroundImgColor, ForeGroundImageColor, BackGroundImageColor);
        bmp.TransparentMode := tmAuto;
        bmp.Transparent := True;
        ImgList.Add(bmp, nil);
      end;
      bmp.Free;
    end;
    FImages.Clear;
    FImages.AddImages(ImgList);
    ImgList.Free;
    FOldForeGroundImgColor := ForeGroundImageColor;
    FOldBkGroundImgColor := BackGroundImageColor;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetForeGroundImageColor(const Value: TColor);
begin
  if FForeGroundImageColor <> Value then
  begin
    FForeGroundImageColor := Value;
    TwoColorImages := TwoColorImages; // To reflect color change
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelector.SetStretchImageDraw(const Value: Boolean);
begin
  if FStretchImageDraw <> Value then
  begin
    FStretchImageDraw := Value;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

{ TSelectorDropDownWindow }

constructor TSelectorDropDownWindow.Create(AOwner: TComponent);
begin
  inherited;
  {BorderIcons:= [];
  BorderStyle:= bsNone;
  Ctl3D:= false;
  Color:= clGray;      }
  FHideOnDeActivate := true;
  FHideTimer := TTimer.Create(self);
  FHideTimer.Interval := 1;
  FHideTimer.Enabled := false;
  FHideTimer.OnTimer := HideTimerOnTime;
end;

//------------------------------------------------------------------------------

constructor TSelectorDropDownWindow.CreateNew(AOwner: TComponent; Dummy: Integer);
begin
  inherited;
  FOwner := AOwner;
  FHideOnDeActivate := true;
  FHideTimer := TTimer.Create(self);
  FHideTimer.Interval := 1;
  FHideTimer.Enabled := false;
  FHideTimer.OnTimer := HideTimerOnTime;
end;

//------------------------------------------------------------------------------

procedure TSelectorDropDownWindow.CreateParams(var Params: TCreateParams);
const
  CS_DROPSHADOW = $00020000;
begin
  inherited CreateParams(Params);
  //Params.Style := Params.Style - WS_BORDER;
  {
  if (Win32Platform = VER_PLATFORM_WIN32_NT) and
     ((Win32MajorVersion > 5) or
      ((Win32MajorVersion = 5) and (Win32MinorVersion >= 1))) then
    Params.WindowClass.Style := Params.WindowClass.Style or CS_DROPSHADOW;

  Params.ExStyle := Params.ExStyle or WS_EX_TOPMOST; }
end;

//------------------------------------------------------------------------------

destructor TSelectorDropDownWindow.Destroy;
begin
  FHideTimer.Free;
  inherited;
end;

//------------------------------------------------------------------------------

function TSelectorDropDownWindow.GetParentWnd: HWnd;
var
  Last, P: HWnd;
begin
  P := GetParent((Owner as TWinControl).Handle);
  Last := P;
  while P <> 0 do
  begin
    Last := P;
    P := GetParent(P);
  end;
  Result := Last;
end;

//------------------------------------------------------------------------------

procedure TSelectorDropDownWindow.HideTimerOnTime(Sender: TObject);
begin
  Hide;
  FHideTimer.Enabled := false;
end;

procedure TSelectorDropDownWindow.Paint;
begin
  inherited;
{  Canvas.Brush.Style:= bsClear;
  Canvas.Pen.Color:= clGray;

  Canvas.MoveTo(0, 0);
  Canvas.LineTo(0, Height);

  if ShowAbove then
  begin
    Canvas.MoveTo(0, 0);
    Canvas.LineTo(Width-1, 0);

    Canvas.MoveTo(TWinControl(FOwner).Width, Height-1);
    Canvas.LineTo(Width-1, Height-1);
  end
  else
  begin
    Canvas.MoveTo(TWinControl(FOwner).Width-1, 0);
    Canvas.LineTo(Width, 0);

    Canvas.MoveTo(0, Height-1);
    Canvas.LineTo(Width-1, Height-1);
  end;

  Canvas.MoveTo(Width-1, Height);
  Canvas.LineTo(Width-1, 0); }
end;

//------------------------------------------------------------------------------

procedure TSelectorDropDownWindow.SetWindowSize;
begin
  if Assigned(FSelectorPanel) then
  begin
    Height := FSelectorPanel.GetVisibleHeight; //+2;
    //ClientHeight:= FSelectorPanel.GetVisibleHeight + 1;
    Width := FSelectorPanel.Width; // + 2;
  end;
end;

//------------------------------------------------------------------------------

procedure TSelectorDropDownWindow.WMActivate(var Message: TWMActivate);
begin
  inherited;

  if Message.Active = integer(False) then
  begin
    if HideOnDeactivate and Visible then
    begin
      Hide;
      FHideTimer.Enabled := true;
    end;
  end
  else if Assigned(FSelectorPanel) then
  begin
    FSelectorPanel.SetFocus;
    SendMessage(getParentWnd, WM_NCACTIVATE, 1, 0);
  end;
end;

//------------------------------------------------------------------------------

procedure TSelectorDropDownWindow.WMNCHitTest(var Message: TWMNCHitTest);
var
  pt: TPoint;
begin
  // Make the hint sizable
  pt := ScreenToClient(Point(Message.XPos, Message.YPos));

  if (pt.X > Width - 10) and (pt.Y > Height - 10) then
    message.Result := HTBOTTOMRIGHT
end;

//------------------------------------------------------------------------------


{ TDgrCustomSelectorPanel }

constructor TDgrCustomSelectorPanel.Create(AOwner: TComponent);
begin
  inherited;
  FOwner := AOwner;
  BevelOuter := bvNone;
  BevelWidth := 1;
  Color := $00F7F8F9;
  FColorTo := clNone;
  FWindowBorderColor := clGray;
  FGradientDirection := gdHorizontal;
end;

//------------------------------------------------------------------------------

function TDgrCustomSelectorPanel.GetVisibleHeight: integer;
begin
  Result := Height;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelectorPanel.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelectorPanel.Paint;
var
  R: TRect;
begin
  inherited;
  R := Rect(0, 0, Width, Height);

  if ColorTo <> clNone then
    DrawGradient(Canvas, Color, ColorTo, 40, R, FGradientDirection = gdHorizontal);

  Canvas.Brush.Style := bsClear;
  Canvas.Pen.Color := FWindowBorderColor;

  Canvas.MoveTo(0, 0);
  Canvas.LineTo(0, Height);

  if TSelectorDropDownWindow(FOwner).ShowFullBorder then
  begin
    Canvas.MoveTo(0, 0);
    Canvas.LineTo(Width - 1, 0);
    Canvas.MoveTo(0, Height - 1);
    Canvas.LineTo(Width - 1, Height - 1);
  end
  else
  begin
    if TSelectorDropDownWindow(FOwner).ShowAbove then
    begin
      Canvas.MoveTo(0, 0);
      Canvas.LineTo(Width - 1, 0);

      if TSelectorDropDownWindow(FOwner).ShowLeft then
      begin
        Canvas.MoveTo(0, Height - 1);
        Canvas.LineTo(Width - TWinControl(TSelectorDropDownWindow(Owner).Owner).Width + 1, Height - 1);
      end
      else
      begin
        Canvas.MoveTo(TWinControl(TSelectorDropDownWindow(Owner).Owner).Width-1, Height - 1);
        Canvas.LineTo(Width - 1, Height - 1);
      end;
    end
    else
    begin
      if TSelectorDropDownWindow(FOwner).ShowLeft then
      begin
        Canvas.MoveTo(0, 0);
        Canvas.LineTo(Width - TWinControl(TSelectorDropDownWindow(Owner).Owner).Width + 1, 0);
      end
      else
      begin
        Canvas.MoveTo(TWinControl(TSelectorDropDownWindow(Owner).Owner).Width - 1, 0);
        Canvas.LineTo(Width, 0);
      end;

      Canvas.MoveTo(0, Height - 1);
      Canvas.LineTo(Width - 1, Height - 1);
    end;
  end;

  Canvas.MoveTo(Width - 1, Height);
  Canvas.LineTo(Width - 1, {0}-1);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelectorPanel.SetColorTo(const Value: TColor);
begin
  FColorTo := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelectorPanel.SetGradientDirection(
  const Value: TDgrGradientDirection);
begin
  FGradientDirection := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomSelectorPanel.SetWindowBorderColor(
  const Value: TColor);
begin
  FWindowBorderColor := Value;
end;

//------------------------------------------------------------------------------


{ TDgrSelectorPanel }

constructor TDgrSelectorPanel.Create(AOwner: TComponent);
begin
  inherited;
  FItems := TDgrSelectorItems.Create(self);
  FColorHot := RGB(182, 189, 210);
  FColorHotTo := clNone;
  FColorDown := RGB(255, 169, 64); //RGB(133,146,181);
  FColorDownTo := clNone;
  FColorSelected := RGB(212, 213, 216);
  FColorSelectedTo := clNone;
  FBorderColor := clNone;
  FBorderDownColor := clBlack;
  FBorderHotColor := clBlack;
  FBorderSelectedColor := clBlack;
  FHotItemIndex := -1;
  FDownItemIndex := -1;
  FNoPrefix := false;

  FItemIndex := -1;

  FButtonHeight := 20;
  FTopOffSet := 4;
  FLeftOffSet := 4;
  FButtonMargin := 3;
  FButtonsPerRow := 1;

  ShowHint := true;
  FMaxCaptionLength := 0;

  FMinButtonWidth := MINBUTTONSIZE;
  FMinButtonHeight := MINBUTTONSIZE;

  FTwoColorImages := False;
end;

//------------------------------------------------------------------------------

destructor TDgrSelectorPanel.Destroy;
begin
  FItems.Free;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.MouseMove(Shift: TShiftState; X, Y: Integer);
var
  i, j: integer;
begin
  inherited;
  i := ItemAtPos(X, Y);
  if (i >= 0) then
  begin
    if (FHotItemIndex <> i) then
    begin
      if (FHotItemIndex >= 0) then
      begin
        j := FHotItemIndex;
        FHotItemIndex := -1;
        if FDownItemIndex > -1 then // means mouse down move
          FDownItemIndex := i;
        DrawItem(j, true);
      end;

      FHotItemIndex := i;
      if FMouseDown then // means mouse down move
        FDownItemIndex := i;
      DrawItem(i, true);

      //if FItems.Items[i].Hint <> '' then
      begin
        Hint := FItems.Items[i].Hint;
        Application.CancelHint;
      end;

      if Assigned(FOnHotTool) then
        FOnHotTool(self, i);
    end;
  end
  else if (FHotItemIndex >= 0) then
  begin
    j := FHotItemIndex;
    FHotItemIndex := -1;
    if FDownItemIndex > -1 then // means mouse down move
      FDownItemIndex := -1;
    DrawItem(j, true);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.DrawItem(Index: integer; RefreshItem: boolean = false);
var
  Gr, R: TRect;

  DTSTYLE: dword;
  bmp: TBitMap;
  DR: TRect;
begin
  if csDesigning in ComponentState then
    exit;

  DTSTYLE := DT_SINGLELINE or DT_VCENTER;

  if FNoPrefix then
    DTSTYLE := DTSTYLE or DT_NOPREFIX;  

  R := FItems.Items[Index].ItemRect;
  Gr := FItems.Items[Index].ItemRect;
  Gr.Left := Gr.Left + ButtonMargin;
  Gr.Top := Gr.Top; // + ButtonMargin;

  if (Index = FDownItemIndex) then
  begin
    if self.FColorDownTo <> clNone then
      DrawGradient(Canvas, ColorDown, ColorDownTo, 16, FItems.Items[Index].ItemRect, true)
    else
    begin
      Canvas.Brush.Color := ColorDown;
      Canvas.Pen.Color := ColorDown;
      DR := FItems.Items[Index].ItemRect;
      Canvas.Rectangle(DR.Left, DR.Top, DR.Right, DR.Bottom);
    end;

    if BorderDownColor <> clNone then
    begin
      Canvas.Brush.Style := bsClear;
      Canvas.Pen.Color := BorderDownColor;
      DR := FItems.Items[Index].ItemRect;
      Canvas.Rectangle(DR.Left, DR.Top, DR.Right, DR.Bottom);
    end;

    Canvas.Brush.Style := bsClear;
    Canvas.Font.Color := clWhite;

    if not Assigned(FOnDrawItem) and (FItems.Items[Index].CaptionAlignment = taLeftJustify) and (FItems.Items[Index].Caption <> '') then
    begin
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
      {$ELSE}
      DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
{$ENDIF}
    end;

    if not Assigned(FOnDrawItem) and Assigned(FImages) and (FItems.Items[Index].ImageIndex >= 0) then
    begin
      if TwoColorImages then
      begin
        bmp := TBitmap.Create;
        bmp.Width := FImages.width;
        bmp.Height := FImages.Height;

        bmp.Canvas.Brush.Color := clFuchsia;
        bmp.Canvas.FillRect(rect(0, 0, FImages.Width, FIMages.Height));

        FImages.DrawingStyle := dsTransparent;
        FImages.Draw(bmp.Canvas, 0, 0, FItems.Items[Index].ImageIndex);

        bmp.Transparent := true;
        bmp.TransparentMode := tmAuto;

        if (FItems.Items[Index].CaptionAlignment = taLeftJustify) then
          Canvas.Draw(fmaxCaptionLength + Gr.left + 2, Gr.Top + 2, bmp)
        else
          Canvas.Draw(Gr.left, Gr.Top + 2, bmp);
        bmp.Free;
      end
      else
      begin
      if (FItems.Items[Index].CaptionAlignment = taLeftJustify) then
        FImages.Draw(Canvas, fmaxCaptionLength + Gr.left + 2, Gr.Top + 2, FItems.Items[Index].ImageIndex)
      else
        FImages.Draw(Canvas, Gr.left, Gr.Top + 2, FItems.Items[Index].ImageIndex);
      end;
      Gr.Left := Gr.Left + FImages.Width + 2;
    end;

    if not Assigned(FOnDrawItem) then
    begin
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
      {$ELSE}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
{$ENDIF}
    end;

    if Assigned(FOnDrawItem) then
      FOnDrawItem(self, Index, R);

  end
  else if (Index = FHotItemIndex) then
  begin
    if self.FColorHotTo <> clNone then
      DrawGradient(Canvas, ColorHot, ColorHotTo, 16, Rect(R.Left, R.Top, R.Right - 1, R.Bottom), true)
    else
    begin
      Canvas.Brush.Color := ColorHot;
      Canvas.Pen.Color := ColorHot;
      DR := FItems.Items[Index].ItemRect;
      Canvas.Rectangle(DR.Left, DR.Top, DR.Right, DR.Bottom);
    end;

    if BorderHotColor <> clNone then
    begin
      Canvas.Brush.Style := bsClear;
      Canvas.Pen.Color := BorderHotColor;
      DR := FItems.Items[Index].ItemRect;
      Canvas.Rectangle(DR.Left, DR.Top, DR.Right, DR.Bottom);
    end;

    Canvas.Brush.Style := bsClear;
    Canvas.Font.Color := clBlack;

    if not Assigned(FOnDrawItem) and (FItems.Items[Index].CaptionAlignment = taLeftJustify) and (FItems.Items[Index].Caption <> '') then
    begin
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
      {$ELSE}
      DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
{$ENDIF}
    end;

    if not Assigned(FOnDrawItem) and Assigned(FImages) and (FItems.Items[Index].ImageIndex >= 0) then
    begin
      if TwoColorImages then
      begin
        bmp := TBitmap.Create;
        bmp.Width := FImages.width;
        bmp.Height := FImages.Height;

        bmp.Canvas.Brush.Color := clFuchsia;
        bmp.Canvas.FillRect(rect(0, 0, FImages.Width, FIMages.Height));

        FImages.DrawingStyle := dsTransparent;
        FImages.Draw(bmp.Canvas, 0, 0, FItems.Items[Index].ImageIndex);

        bmp.Transparent := true;
        bmp.TransparentMode := tmAuto;

        if (FItems.Items[Index].CaptionAlignment = taLeftJustify) then
          Canvas.Draw(fmaxCaptionLength + Gr.left + 2, Gr.Top + 2, bmp)
        else
          Canvas.Draw(Gr.left, Gr.Top + 2, bmp);
        bmp.Free;
      end
      else
      begin
      if (FItems.Items[Index].CaptionAlignment = taLeftJustify) then
        FImages.Draw(Canvas, fmaxCaptionLength + Gr.left + 2, Gr.Top + 2, FItems.Items[Index].ImageIndex)
      else
        FImages.Draw(Canvas, Gr.left, Gr.Top + 2, FItems.Items[Index].ImageIndex);
      end;
      Gr.Left := Gr.Left + FImages.Width + 2;
    end;

    if not Assigned(FOnDrawItem) then
    begin
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
      {$ELSE}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
{$ENDIF}
    end;

    if Assigned(FOnDrawItem) then
      FOnDrawItem(self, Index, R);

  end
  else // Normal
  begin
    if RefreshItem then
    begin
{$IFNDEF TMSDOTNET}
      InvalidateRect(Handle, @R, True);
{$ENDIF}
{$IFDEF TMSDOTNET}
      InvalidateRect(Handle, R, True);
{$ENDIF}
      Exit;
    end;

    if not Assigned(FOnDrawItem) then
    begin
      if FItems.Items[Index].backGroundColor <> clNone then
      begin
        Canvas.Pen.Color := FItems.Items[Index].backGroundColor;
        Canvas.Brush.Color := FItems.Items[Index].backGroundColor;
        Canvas.Rectangle(R.Left + 3, R.Top + 3, R.Right - 3, R.Bottom - 3);
      end;
    end;

    if Index = ItemIndex then // Selected Item
    begin
      if self.FColorSelectedTo <> clNone then
        DrawGradient(Canvas, ColorSelected, ColorSelectedTo, 16, FItems.Items[Index].ItemRect, true)
      else
      begin
        Canvas.Brush.Color := ColorSelected;
        Canvas.Pen.Color := ColorSelected;
        DR := FItems.Items[Index].ItemRect;
        Canvas.Rectangle(DR.Left, DR.Top, DR.Right, DR.Bottom);
      end;

      if BorderSelectedColor <> clNone then
      begin
        Canvas.Brush.Style := bsClear;
        Canvas.Pen.Color := BorderSelectedColor;
       	DR := FItems.Items[Index].ItemRect;
        Canvas.Rectangle(DR.Left, DR.Top, DR.Right, DR.Bottom);
      end;
    end;

    Canvas.Brush.Style := bsClear;
    Canvas.Font.Color := clBlack;

    if not Assigned(FOnDrawItem) and (FItems.Items[Index].CaptionAlignment = taLeftJustify) and (FItems.Items[Index].Caption <> '') then
    begin
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
      {$ELSE}
      DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
{$ENDIF}
      //Gr.Left:= Gr.Left + Canvas.TextWidth(FItems.Items[Index].Caption);
    end;

    if not Assigned(FOnDrawItem) and Assigned(FImages) and (FItems.Items[Index].ImageIndex >= 0) then
    begin
      if TwoColorImages then
      begin
        bmp := TBitmap.Create;
        bmp.Width := FImages.width;
        bmp.Height := FImages.Height;

        bmp.Canvas.Brush.Color := clFuchsia;
        bmp.Canvas.FillRect(rect(0, 0, FImages.Width, FIMages.Height));

        FImages.DrawingStyle := dsTransparent;
        FImages.Draw(bmp.Canvas, 0, 0, FItems.Items[Index].ImageIndex);

        bmp.Transparent := true;
        bmp.TransparentMode := tmAuto;

        if (FItems.Items[Index].CaptionAlignment = taLeftJustify) then
          Canvas.Draw(fmaxCaptionLength + Gr.left + 2, Gr.Top + 2, bmp)
        else
          Canvas.Draw(Gr.left, Gr.Top + 2, bmp);
        bmp.Free;
      end
      else
      begin
      if (FItems.Items[Index].CaptionAlignment = taLeftJustify) then
        FImages.Draw(Canvas, fmaxCaptionLength + Gr.left + 2, Gr.Top + 2, FItems.Items[Index].ImageIndex)
      else
        FImages.Draw(Canvas, Gr.left, Gr.Top + 2, FItems.Items[Index].ImageIndex);
      end;
      Gr.Left := Gr.Left + FImages.Width + 2;
    end;

    if not Assigned(FOnDrawItem) then
    begin
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
      {$ELSE}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, PChar(FItems.Items[Index].Caption), -1, Gr, DTSTYLE);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      if (FItems.Items[Index].CaptionAlignment = taCenter) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE or DT_CENTER)
      else if (FItems.Items[Index].CaptionAlignment = taRightJustify) and (FItems.Items[Index].Caption <> '') then
        DrawText(Canvas.Handle, FItems.Items[Index].Caption, -1, Gr, DTSTYLE);
{$ENDIF}
    end;

    if Assigned(FOnDrawItem) then
      FOnDrawItem(self, Index, R);

  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.Paint;
var
  i: integer;
begin
  inherited;

  for i := 0 to FItems.Count - 1 do
  begin
    DrawItem(i);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetBorderColor(const Value: TColor);
begin
  FBorderColor := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetImages(const Value: TCustomImageList);
begin
  FImages := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetItemIndex(const Value: integer);
begin
  if Value < 0 then
  begin
    FItemIndex := -1;
    exit;
  end;

  if Value < FItems.Count then
  begin
    if FItems.Items[Value].Enable then
    begin
      if FItemIndex <> Value then
      begin
        FItemIndex := Value;
        //if Assigned(FOnSelect) then
        //  FOnSelect(self);

      end;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetItems(const Value: TDgrSelectorItems);
begin
  FItems := Value;
end;

//------------------------------------------------------------------------------

function TDgrSelectorPanel.TotalAutoSizeButtons: integer;
var
  i: integer;
begin
  Result := 0;
  for i := 0 to FItems.Count - 1 do
  begin
    if FItems.Items[i].ItemType = itAutoSizeButton then
      inc(Result);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.AutoSizeBtnSize(var W, H: integer);
var
  i: integer;
begin
  w := MinButtonWidth; //MINBUTTONSIZE;
  H := MinButtonHeight; //MINBUTTONSIZE;
  for i := 0 to FItems.Count - 1 do
  begin
    if FItems.Items[i].ItemType = itAutoSizeButton then
    begin
      if Assigned(FImages) and (FItems.Items[i].ImageIndex >= 0) then
      begin
        W := Max(W, Canvas.TextWidth(FItems.Items[i].Caption) + FImages.Width + (ButtonMargin * 2));
        H := Max(H, MAX(Canvas.TextHeight('gh'), FImages.Height) + ButtonMargin); // Single Margin added
      end
      else
      begin
        W := Max(W, Canvas.TextWidth(FItems.Items[i].Caption) + (ButtonMargin * 2));
        H := Max(H, Canvas.TextHeight('gh') + ButtonMargin); // Single Margin added
      end;
      FMaxCaptionLength := Max(FMaxCaptionLength, Canvas.TextWidth(FItems.Items[i].Caption));
    end;
  end;
end;

//------------------------------------------------------------------------------

function TDgrSelectorPanel.GetMaxWidth: integer;
var
  i, asb, fwb: integer;
begin
  Result := FleftOffSet * 2 + MinButtonWidth; //MINBUTTONSIZE;
  fwb := Result;
  asb := Result;
  AutoSizeBtnSize(asb {GetWidth}, i {dummy});

  for i := 0 to FItems.Count - 1 do
  begin
    if FItems.Items[i].ItemType = itFullWidthButton then
    begin
      if Assigned(FImages) and (FItems.Items[i].ImageIndex >= 0) then
        fwb := Max(fwb, Canvas.TextWidth(FItems.Items[i].Caption) + FImages.Width + (ButtonMargin * 2) + (FleftOffSet * 2))
      else
        fwb := Max(fwb, Canvas.TextWidth(FItems.Items[i].Caption) + (ButtonMargin * 2) + (FleftOffSet * 2));
    end;
  end;

  Result := Max(fwb, asb * min(ButtonsPerRow, TotalAutoSizeButtons) + (FleftOffSet * 2) {(ButtonMargin*2)});
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetItemsPosition;
var
  i, c, r, absW, absH, MaxW, bNo: integer;
  ShouldChangeRow: boolean;
begin
  r := FTopOffSet;
  c := FLeftOffSet;
  bNo := 0;
  MaxW := GetMaxWidth;
  AutoSizeBtnSize(absW, absH);

  Width := MaxW;

  ShouldChangeRow := false;
  for i := 0 to FItems.Count - 1 do
  begin
    if FItems.Items[i].ItemType = itAutoSizeButton then
    begin
      inc(bNo);
      if bNo > self.ButtonsPerRow then
      begin
        r := r + absH;
        bNo := 1;
        c := FLeftOffSet;
      end;
      FItems.Items[i].ItemRect := Rect(c, r, c + absW, r + absH);
      c := c + absW;
      ShouldChangeRow := true;
    end
    else if FItems.Items[i].ItemType = itFullWidthButton then
    begin
      if ShouldChangeRow then
        r := r + absH + 2; //FButtonHeight;
      FItems.Items[i].ItemRect := Rect(FLeftOffSet, r, MaxW - FLeftOffSet, r + FButtonHeight);
      r := r + FButtonHeight;
      c := FLeftOffSet;
      bNo := 0;
      ShouldChangeRow := false;
    end;
  end;

  SetPanelHeight;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetPanelHeight;
begin
  if FItems.Count > 0 then
  begin
    Height := FItems.Items[FItems.Count - 1].ItemRect.Bottom + FTopOffSet;
    // SetVisibleHeight;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetButtonsPerRow(const Value: TNoOfButtons);
begin
  FButtonsPerRow := Value;
end;

function TDgrSelectorPanel.ItemAtPos(X, Y: integer): integer;
var
  i: integer;
begin
  Result := -1;
  for i := 0 to FItems.Count - 1 do
  begin
    if PtInRect(FItems.Items[i].ItemRect, Point(X, Y)) then
    begin
      Result := i;
      break;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.MouseDown(Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  i: integer;
begin
  inherited;

  FMouseDown := true;
  i := ItemAtPos(X, Y);
  if (i >= 0) then
  begin
    FDownItemIndex := i;
    DrawItem(i, true);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  FMouseDown := false;
  if Assigned(FOnShouldHide) then
    FOnShouldHide(self);

  if (FDownItemIndex > -1) and (FHotItemIndex > -1) then
  begin
    ItemIndex := FDownItemIndex;

    if Assigned(FOnSelect) then
      FOnSelect(self);
  end;
  FHotItemIndex := -1;
  FDownItemIndex := -1;
  //if Assigned(FOnShouldHide) then
  //  FOnShouldHide(self);
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited;

end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.WMChar(var Msg: TWMKey);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.CMWantSpecialKey(var Msg: TCMWantSpecialKey);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetButtonMargin(const Value: integer);
begin
  FButtonMargin := Value;
end;

//------------------------------------------------------------------------------


procedure TDgrSelectorPanel.CMMouseLeave(var Message: TMessage);
var
  i: integer;
begin
  inherited;
  i := FHotItemIndex;
  FHotItemIndex := -1;
  FDownItemIndex := -1;

  if (i > -1) then
    DrawItem(i, true);
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetMinButtonHeight(const Value: integer);
begin
  FMinButtonHeight := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetMinButtonWidth(const Value: integer);
begin
  FMinButtonWidth := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorPanel.SetTwoColorImages(const Value: Boolean);
begin
  FTwoColorImages := Value;
end;

{ TDgrSelectorItem }

procedure TDgrSelectorItem.Assign(Source: TPersistent);
begin
  if (Source is TDgrSelectorItem) then
  begin
    BackGroundColor := (Source as TDgrSelectorItem).BackGroundColor;
    Caption := (Source as TDgrSelectorItem).Caption;
    CaptionAlignment := (Source as TDgrSelectorItem).CaptionAlignment;
    ImageIndex := (Source as TDgrSelectorItem).ImageIndex;
    Hint := (Source as TDgrSelectorItem).Hint;
    Value := (Source as TDgrSelectorItem).Value;
    ItemType := (Source as TDgrSelectorItem).ItemType;
    Tag := (Source as TDgrSelectorItem).Tag;
  end;

end;

constructor TDgrSelectorItem.Create(Collection: TCollection);
begin
  inherited;
  FCaption := '';
  FEnable := true;
  FImageIndex := -1;
  FValue := '';
  FHint := '';
  FCaptionAlignment := taCenter;
  FItemType := itAutoSizeButton;
  FBackGroundColor := clNone;
  FTag := 0;
end;

//------------------------------------------------------------------------------

destructor TDgrSelectorItem.Destroy;
begin

  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetBackGroundColor(const Value: TColor);
begin
  FBackGroundColor := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetCaption(const Value: string);
begin
  if FCaption <> Value then
  begin
    FCaption := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetEnable(const Value: boolean);
begin
  if FEnable <> Value then
  begin
    FEnable := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetHint(const Value: string);
begin
  FHint := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetImageIndex(const Value: integer);
begin
  if FImageIndex <> Value then
  begin
    FImageIndex := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetItemType(const Value: TSelectorItemType);
begin
  if FItemType <> Value then
  begin
    FItemType := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetTag(const Value: integer);
begin
  FTag := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetValue(const Value: string);
begin
  if FValue <> Value then
  begin
    FValue := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItem.SetvCaptionAlignment(const Value: TAlignment);
begin
  if FCaptionAlignment <> Value then
  begin
    FCaptionAlignment := Value;
  end;
end;

//------------------------------------------------------------------------------


{ TDgrSelectorItems }

function TDgrSelectorItems.Add: TDgrSelectorItem;
begin
  Result := TDgrSelectorItem(inherited Add);
end;

//------------------------------------------------------------------------------

constructor TDgrSelectorItems.Create(AOwner: TPersistent);
begin
  inherited Create(TDgrSelectorItem);
  FOwner := AOwner;
end;

//------------------------------------------------------------------------------

function TDgrSelectorItems.GetItem(Index: Integer): TDgrSelectorItem;
begin
  Result := TDgrSelectorItem(inherited Items[Index]);
end;

//------------------------------------------------------------------------------

function TDgrSelectorItems.GetOwner: TPersistent;
begin
  Result := FOwner;
end;

//------------------------------------------------------------------------------

function TDgrSelectorItems.IndexOfValue(AValue: string): TDgrSelectorItem;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if AnsiCompareText(AValue, Items[c].Value) = 0 then
    begin
      result := Items[c];
      exit;
    end;
end;

function TDgrSelectorItems.Insert(Index: Integer): TDgrSelectorItem;
begin
  Result := TDgrSelectorItem(inherited Insert(Index));
end;

//------------------------------------------------------------------------------

procedure TDgrSelectorItems.SetItem(Index: Integer;
  const Value: TDgrSelectorItem);
begin
  inherited Items[Index] := Value;
end;

//------------------------------------------------------------------------------


{ TDgrColorCubePanel }

procedure TDgrColorCubePanel.CMMouseLeave(var Message: TMessage);
begin
  inherited;
end;

//------------------------------------------------------------------------------

constructor TDgrColorCubePanel.Create(AOwner: TComponent);
begin
  inherited;
  FSelectedColor := clNone;
  FHotIndex := -1;
  FSelectedIndex := -1;
  Initialize;
  ShowRGBHint := true;
end;

//------------------------------------------------------------------------------

destructor TDgrColorCubePanel.Destroy;
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.DrawColorCube(Index: integer);
begin
  if (Index >= 1) and (Index <= High(FCubeCells)) then
  begin
    Canvas.Pen.Color := FCubeCells[Index].Color;
    Canvas.Brush.Color := FCubeCells[Index].Color;
    DrawHexagon(Canvas, FCubeCells[Index].CenterPos, FCubeSize.X, FCubeSize.Y);
    if FHotIndex = Index then
      DrawHotBorder;
    if FSelectedIndex = Index then
      DrawSelectedBorder;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.DrawAllColorCube;
var
  i: integer;
begin
  for i := 1 to high(FCubeCells) do
  begin
    DrawColorCube(i);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.DrawHexagon(aCanvas: TCanvas; P: TPoint; X, Y: integer);
begin
  P.X := P.X - X;
  P.Y := P.Y - y * 2;
  aCanvas.Polygon([Point(P.X, P.Y + Y), Point(P.X + X, P.Y),
    Point(P.X + X * 2, P.Y + Y), Point(P.X + X * 2, P.Y + Y * 3), Point(P.X + X, P.Y + Y * 4), Point(P.X, P.Y + Y * 3)]);
end;

//------------------------------------------------------------------------------

function TDgrColorCubePanel.IndexOfCellAt(X, Y: integer): integer;
var
  i: integer;
begin
  Result := -1;
  for i := 1 to high(FCubeCells) do
  begin
    if PtInCell(i, Point(X, Y)) then
    begin
      Result := i;
      break;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.Initialize;
var
  c, r, i, j, cl: integer;
begin
  FCubeSize.X := 6;
  FCubeSize.Y := 3;

  FCubeCells[1].Color := $00663300; FCubeCells[2].Color := $00996633;
  FCubeCells[3].Color := $00CC6633; FCubeCells[4].Color := $00993300;
  FCubeCells[5].Color := $00990000; FCubeCells[6].Color := $00CC0000;
  FCubeCells[7].Color := $00660000; FCubeCells[8].Color := $00666600;
  FCubeCells[9].Color := $00996600; FCubeCells[10].Color := $00CC9900;
  FCubeCells[11].Color := $00CC6600; FCubeCells[12].Color := $00CC3300;
  FCubeCells[13].Color := clBlue; FCubeCells[14].Color := $00FF3333;
  FCubeCells[15].Color := $00993333; FCubeCells[16].Color := clTeal;
  FCubeCells[17].Color := $00999900; FCubeCells[18].Color := $00CCCC33;
  FCubeCells[19].Color := $00FFCC00; FCubeCells[20].Color := $00FF9900;
  FCubeCells[21].Color := $00FF6600; FCubeCells[22].Color := $00FF6633;
  FCubeCells[23].Color := $00CC3333; FCubeCells[24].Color := $00996666;
  FCubeCells[25].Color := $00669933; FCubeCells[26].Color := $0099CC00;
  FCubeCells[27].Color := $00CCFF00; FCubeCells[28].Color := clAqua;
  FCubeCells[29].Color := $00FFCC33; FCubeCells[30].Color := $00FF9933;
  FCubeCells[31].Color := $00FF9966; FCubeCells[32].Color := $00FF6666;
  FCubeCells[33].Color := $00FF0066; FCubeCells[34].Color := $00CC0066;
  FCubeCells[35].Color := $00339933; FCubeCells[36].Color := $0066CC00;
  FCubeCells[37].Color := $0099FF00; FCubeCells[38].Color := $00CCFF66;
  FCubeCells[39].Color := $00FFFF66; FCubeCells[40].Color := $00FFCC66;
  FCubeCells[41].Color := $00FFCC99; FCubeCells[42].Color := $00FF9999;
  FCubeCells[43].Color := $00FF6699; FCubeCells[44].Color := $00FF3399;
  FCubeCells[45].Color := $00FF0099; FCubeCells[46].Color := $00006600;
  FCubeCells[47].Color := $0000CC00; FCubeCells[48].Color := clLime;
  FCubeCells[49].Color := $0099FF66; FCubeCells[50].Color := $00CCFF99;
  FCubeCells[51].Color := $00FFFFCC; FCubeCells[52].Color := $00FFECCC;
  FCubeCells[53].Color := $00FFCCCC; FCubeCells[54].Color := $00FF99CC;
  FCubeCells[55].Color := $00FF66CC; FCubeCells[56].Color := $00FF00CC;
  FCubeCells[57].Color := $00CC0099; FCubeCells[58].Color := $00003300;
  FCubeCells[59].Color := clGreen; FCubeCells[60].Color := $0033CC33;
  FCubeCells[61].Color := $0066FF66; FCubeCells[62].Color := $0099FF99;
  FCubeCells[63].Color := $00CCFFCC; FCubeCells[64].Color := clWhite;
  FCubeCells[65].Color := $00FFCCFF; FCubeCells[66].Color := $00FF99FF;
  FCubeCells[67].Color := $00FF66FF; FCubeCells[68].Color := clFuchsia;
  FCubeCells[69].Color := $00CC00CC; FCubeCells[70].Color := $00660066;
  FCubeCells[71].Color := $00006633; FCubeCells[72].Color := $00009900;
  FCubeCells[73].Color := $0033FF66; FCubeCells[74].Color := $0066FF99;
  FCubeCells[75].Color := $0099FFCC; FCubeCells[76].Color := $00CCFFFF;
  FCubeCells[77].Color := $00CCCCFF; FCubeCells[78].Color := $00CC99FF;
  FCubeCells[79].Color := $00CC66FF; FCubeCells[80].Color := $00CC33FF;
  FCubeCells[81].Color := $009900CC; FCubeCells[82].Color := clPurple;
  FCubeCells[83].Color := $00003333; FCubeCells[84].Color := $00009966;
  FCubeCells[85].Color := $0033FF99; FCubeCells[86].Color := $0066FFCC;
  FCubeCells[87].Color := $0099FFFF; FCubeCells[88].Color := $0099CCFF;
  FCubeCells[89].Color := $009999FF; FCubeCells[90].Color := $009966FF;
  FCubeCells[91].Color := $009933FF; FCubeCells[92].Color := $009933CC;
  FCubeCells[93].Color := $00990099; FCubeCells[94].Color := $00336666;
  FCubeCells[95].Color := $0000CC99; FCubeCells[96].Color := $0033FFCC;
  FCubeCells[97].Color := $0066FFFF; FCubeCells[98].Color := $0066CCFF;
  FCubeCells[99].Color := $006699FF; FCubeCells[100].Color := $00807CFF;
  FCubeCells[101].Color := $006600FF; FCubeCells[102].Color := $009300D6;
  FCubeCells[103].Color := $00663399; FCubeCells[104].Color := clOlive;
  FCubeCells[105].Color := $0000CCCC; FCubeCells[106].Color := clYellow;
  FCubeCells[107].Color := $0000CCFF; FCubeCells[108].Color := $003399FF;
  FCubeCells[109].Color := $000066FF; FCubeCells[110].Color := $005050FF;
  FCubeCells[111].Color := $006600CC; FCubeCells[112].Color := $00330066;
  FCubeCells[113].Color := $00336699; FCubeCells[114].Color := $000099CC;
  FCubeCells[115].Color := $000099FF; FCubeCells[116].Color := $000066CC;
  FCubeCells[117].Color := $000033FF; FCubeCells[118].Color := clRed;
  FCubeCells[119].Color := $000000CC; FCubeCells[120].Color := $00330099;
  FCubeCells[121].Color := $00003366; FCubeCells[122].Color := $00006699;
  FCubeCells[123].Color := $000033CC; FCubeCells[124].Color := $00003399;
  FCubeCells[125].Color := $00000099; FCubeCells[126].Color := clMaroon;
  FCubeCells[127].Color := $002100A5;

  c := 55; // Left
  r := 20; // Top
  cl := 1;

  // Set Cells Position
  for i := 1 to 13 do
  begin
    if i < 8 then
    begin
      for j := 1 to 6 + i do
      begin
        //DrawHexagon(Canvas, Point(C,R), 6, 3);
        FCubeCells[cl].CenterPos := Point(C, R);
        c := c + FCubeSize.x * 2; //12;
        inc(cl);
      end;
      r := r + 10;
      c := 55 - (FCubeSize.x * i);
    end
    else
    begin
      c := 19 + (FCubeSize.x * (i - 7));
      for j := 1 to 13 - (i - 7) do
      begin
        //DrawHexagon(Canvas, Point(C,R), 6, 3);
        FCubeCells[cl].CenterPos := Point(C, R);
        c := c + FCubeSize.x * 2; //12;
        inc(cl);
      end;
      r := r + 10;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  i, j: integer;
begin
  inherited;
  i := IndexOfCellAt(X, Y);
  if i >= 1 then
  begin
    //SelectedColor:= FCubeCells[i].Color;
    if FSelectedIndex >= 1 then
    begin
      j := FSelectedIndex;
      FSelectedIndex := -1;
      DrawColorCube(j);
    end;

    SetSelectedIndexAndColor(FCubeCells[i].Color, i);

    DrawColorCube(i);

    if Assigned(FOnSelect) then
      FOnSelect(self);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.MouseMove(Shift: TShiftState; X, Y: Integer);
var
  i, j: integer;
begin
  inherited;
  i := IndexOfCellAt(X, Y);
  if (i >= 1) then
  begin
    if (FHotIndex <> i) then
    begin
      if FHotIndex >= 1 then
      begin
        j := FHotIndex;
        FHotIndex := -1;
        DrawColorCube(j);
      end;
      FHotIndex := i;
      DrawColorCube(FHotIndex);
      if ShowRGBHint then
      begin
        Hint := Format('Red: %d,  Green: %d,  Blue: %d', [GetRValue(FCubeCells[i].Color), GetGValue(FCubeCells[i].Color), GetBValue(FCubeCells[i].Color)]);
        Application.CancelHint;
      end;
    end;
  end
  else
  begin
    if ShowRGBHint then
    begin
      Hint := '';
      Application.CancelHint;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  inherited;

  if Assigned(FOnShouldHide) then
    FOnShouldHide(self);
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.Paint;
begin
  inherited;
  DrawAllColorCube;
end;

//------------------------------------------------------------------------------

function TDgrColorCubePanel.PtInCell(Index: integer; P: TPoint): Boolean;
begin
  Result := sqr(FCubeCells[Index].CenterPos.X - P.X) + sqr(FCubeCells[Index].CenterPos.Y - P.Y) <= (FCubeSize.X * FCubeSize.X);
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.SetItemsPosition;
begin
  FHotIndex := -1;
  SetPanelSize;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.SetPanelSize;
begin
  Height := 160;
  Width := 182;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.SetSelectedColor(const Value: TColor);
begin
  //FSelectedColor := Value;
  SetSelectedIndexAndColor(Value);
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.DrawSelectedBorder;
begin
  if (FSelectedIndex >= 1) and (FSelectedIndex <= High(FCubeCells)) then
  begin
    Canvas.Brush.style := bsClear;
    Canvas.Pen.Color := clBlack;
    DrawHexagon(Canvas, FCubeCells[FSelectedIndex].centerPos, FCubeSize.X - 1, FCubeSize.Y);
    Canvas.Pen.Color := clWhite;
    DrawHexagon(Canvas, FCubeCells[FSelectedIndex].centerPos, FCubeSize.X - 2, FCubeSize.Y - 1);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.DrawHotBorder;
begin
  if (FHotIndex >= 1) and (FHotIndex <= High(FCubeCells)) then
  begin
    Canvas.Brush.style := bsClear;
    Canvas.Pen.Color := clRed;
    DrawHexagon(Canvas, FCubeCells[FHotIndex].centerPos, FCubeSize.X - 1, FCubeSize.Y);
    Canvas.Pen.Color := clWhite;
    DrawHexagon(Canvas, FCubeCells[FHotIndex].centerPos, FCubeSize.X - 2, FCubeSize.Y - 1);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.SetSelectedIndexAndColor(clr: TColor;
  index: integer);
var
  i: integer;
begin
  if clr <> clNone then
    FSelectedColor := clr;
  if (Index >= 1) and (Index <= High(FCubeCells)) then
  begin
    FSelectedIndex := Index;
  end
  else
  begin
    FSelectedIndex := -1;
    for i := 1 to high(FCubeCells) do
      if FCubeCells[i].Color = FSelectedColor then
      begin
        FSelectedIndex := i;
        break;
      end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorCubePanel.SetShowRGBHint(const Value: Boolean);
begin
  FShowRGBHint := Value;
  ShowHint := Value;
end;

//------------------------------------------------------------------------------


{ TDgrColorSpectrumPanel }

procedure TDgrColorSpectrumPanel.CMMouseLeave(var Message: TMessage);
begin
  inherited;
end;

//------------------------------------------------------------------------------

constructor TDgrColorSpectrumPanel.Create(AOwner: TComponent);
var
  //frm: TSpectrumForm;
  tbmp: TBitmap;
begin
  inherited;
  FSpectrumImage := TImage.Create(self);
  FSpectrumImage.Parent := self;
  FSpectrumImage.Height := 128;
  FSpectrumImage.Width := 128;

  {
  frm:= TSpectrumForm.Create(nil);
  FSpectrumImage.Picture.Assign(frm.SpectrumImage.Picture);
  //FSpectrumImage.Picture.LoadFromFile('Spectrum.bmp');
  frm.Free;
  }
  tbmp := TBitmap.Create;
  tbmp.LoadFromResourceName(HInstance, 'DGR_SPECTRUM');
  FSpectrumImage.Picture.Assign(tbmp);
  tbmp.Free;

  FSpectrumImage.OnMouseMove := SpectrumImageMouseMove;
  FSpectrumImage.OnMouseDown := SpectrumImageMouseDown;
  FSpectrumImage.OnMouseUp := SpectrumImageMouseUp;
  FHotColor := clNone;
  FSelectedColor := clWhite;

  Screen.Cursors[crTMSCur1] := LoadCursor(HInstance, 'DGR_TMS_CUR1');
  FSpectrumImage.Cursor := crTMSCur1;
end;

//------------------------------------------------------------------------------

destructor TDgrColorSpectrumPanel.Destroy;
begin
  FSpectrumImage.Free;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.DrawFocusPoint;
begin
  {
  FSpectrumImage.Canvas.Pen.Color:= clWhite;
  FSpectrumImage.Canvas.MoveTo(50, 50);
  FSpectrumImage.Canvas.LineTo(100, 100);
  }
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.DrawHotRect;
begin
  Canvas.Pen.Color := clGray;
  Canvas.Brush.Style := bsClear;
  Canvas.Rectangle(FHotRect.Left - 1, FHotRect.Top - 1, FHotRect.Right + 1, FHotRect.Bottom + 1);

  Canvas.Pen.Color := clWhite;
  Canvas.Brush.Color := FHotColor;
  Canvas.Rectangle(FHotRect.Left, FHotRect.Top, FHotRect.Right, FHotRect.Bottom);
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.DrawSelectedRect;
begin
  Canvas.Pen.Color := clGray;
  Canvas.Brush.Style := bsClear;
  Canvas.Rectangle(FSelectedRect.Left - 1, FSelectedRect.Top - 1, FSelectedRect.Right + 1, FSelectedRect.Bottom + 1);

  Canvas.Pen.Color := clWhite;
  Canvas.Brush.Color := FSelectedColor;
  Canvas.Rectangle(FSelectedRect.Left, FSelectedRect.Top, FSelectedRect.Right, FSelectedRect.Bottom);
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.MouseMove(Shift: TShiftState; X,
  Y: Integer);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  inherited;
  if Assigned(FOnShouldHide) then
    FOnShouldHide(self);
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.Paint;
begin
  inherited;
  Canvas.Brush.Style := bsClear;
  Canvas.Pen.Color := clwhite;
  Canvas.Rectangle(FSpectrumImage.Left - 1, FSpectrumImage.Top - 1, FSpectrumImage.Left + FSpectrumImage.Width + 1, FSpectrumImage.Top + FSpectrumImage.Height + 1);
  Canvas.Pen.Color := clGray;
  Canvas.Rectangle(FSpectrumImage.Left - 2, FSpectrumImage.Top - 2, FSpectrumImage.Left + FSpectrumImage.Width + 2, FSpectrumImage.Top + FSpectrumImage.Height + 2);

  DrawSelectedRect;
  DrawHotRect;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.SetItemsPosition;
begin
  SetPanelSize;
  FSpectrumImage.Left := (Width - FSpectrumImage.Width) div 2;
  FSpectrumImage.Top := 10;
  FSelectedRect := Rect(FSpectrumImage.Left - 1, FSpectrumImage.Top + FSpectrumImage.Height + 8, FSpectrumImage.Left + (FSpectrumImage.Width div 2) - 2, FSpectrumImage.Top + FSpectrumImage.Height + 8 + 20);
  FHotRect := Rect(FSelectedRect.Right + 4, FSelectedRect.Top, FSpectrumImage.Left + FSpectrumImage.Width + 1, FSelectedRect.Bottom);
  FHotColor := clNone;

  DrawFocusPoint;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.SetPanelSize;
begin
  Height := 174;
  Width := 150
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.SetSelectedColor(const Value: TColor);
begin
  if (Value <> FSelectedColor) and (Value <> clNone) then
  begin
    FSelectedColor := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.SpectrumImageMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  SelectedColor := FHotColor;
  DrawSelectedRect;
  if Assigned(OnSelect) then
    FOnSelect(self);
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.SpectrumImageMouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  FHotColor := Canvas.Pixels[X + FSpectrumImage.Left, Y + FSpectrumImage.Top];
  DrawHotRect;
end;

//------------------------------------------------------------------------------

procedure TDgrColorSpectrumPanel.SpectrumImageMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin

  if Assigned(FOnShouldHide) then
    FOnShouldHide(self);
end;

//------------------------------------------------------------------------------

{ TDgrColorSelector }

const
  _moreColorsValue = '_morecolors_';

constructor TDgrCustomColorSelector.Create(AOwner: TComponent);
begin
  inherited;
  FColorSelectionStyle := csDiscrete;
  FShowSelectedColor := true;
  FSelectedColor := clNone;
  FShowRGBHint := true;
  ButtonsPerRow := 8;
  Initialize;
end;

//------------------------------------------------------------------------------

destructor TDgrCustomColorSelector.Destroy;
begin
  if not (csDesigning in ComponentState) then
  begin
    if Assigned(FColorCubePanel) then
      FColorCubePanel.Free;
    if Assigned(FSpectrumPanel) then
      FSpectrumPanel.Free;
  end;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.Initialize;
begin
  DefaultInitialize;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.DefaultInitialize;
begin
  Tools.Clear;

  with Tools.Add do
  begin
    ItemType := itFullWidthButton;
    CaptionAlignment := taCenter;
    Caption := '自动';
    Hint := '自动';
    //Value:= ColorToString(clBlack);
    BackGroundColor := clBlack;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(clBlack);
    BackGroundColor := clBlack;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString($00003399);
    BackGroundColor := $00003399;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString($00003333);
    BackGroundColor := $00003333;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString($00003300);
    BackGroundColor := $00003300;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString($00663300);
    BackGroundColor := $00663300;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(clNavy);
    BackGroundColor := clNavy;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString($00353333);
    BackGroundColor := $00353333;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString($00333333);
    BackGroundColor := $00333333;
  end;

  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(128, 0,0));
    BackGroundColor := RGB(128, 0, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 102, 0));
    BackGroundColor := RGB(255, 102, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(128, 128, 0));
    BackGroundColor := RGB(128, 128, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(0, 128, 0));
    BackGroundColor := RGB(0, 128, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(0, 128, 128));
    BackGroundColor := RGB(0, 128, 128);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(0, 0, 255));
    BackGroundColor := RGB(0, 0, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(102, 102, 153));
    BackGroundColor := RGB(102, 102, 153);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(128, 128, 128));
    BackGroundColor := RGB(128, 128, 128);
  end;

  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 0,0));
    BackGroundColor := RGB(255, 0, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 153, 0));
    BackGroundColor := RGB(255, 153, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(153, 204, 0));
    BackGroundColor := RGB(153, 204, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(51, 153, 102));
    BackGroundColor := RGB(51, 153, 102);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(51, 204, 204));
    BackGroundColor := RGB(51, 204, 204);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(51, 102, 255));
    BackGroundColor := RGB(51, 102, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(128, 0, 128));
    BackGroundColor := RGB(128, 0, 128);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(153, 153, 153));
    BackGroundColor := RGB(153, 153, 153);
  end;

  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 0, 255));
    BackGroundColor := RGB(255, 0, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 204, 0));
    BackGroundColor := RGB(255, 204, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 255, 0));
    BackGroundColor := RGB(255, 255, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(0, 255, 0));
    BackGroundColor := RGB(0, 255, 0);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(0, 255, 255));
    BackGroundColor := RGB(0, 255, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(0, 204, 255));
    BackGroundColor := RGB(0, 204, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(153, 51, 102));
    BackGroundColor := RGB(153, 51, 102);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
   //Value:= ColorToString(RGB(192, 192, 192));
    BackGroundColor := RGB(192, 192, 192);
  end;

  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 153, 204));
    BackGroundColor := RGB(255, 153, 204);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 204, 153));
    BackGroundColor := RGB(255, 204, 153);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 255, 153));
    BackGroundColor := RGB(255, 255, 153);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(204, 255, 204));
    BackGroundColor := RGB(204, 255, 204);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(204, 255, 255));
    BackGroundColor := RGB(204, 255, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(153, 204, 255));
    BackGroundColor := RGB(153, 204, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(204, 153, 255));
    BackGroundColor := RGB(204, 153, 255);
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    //Value:= ColorToString(RGB(255, 255, 255));
    BackGroundColor := clWhite;
  end;

  SetShowMoreColors(true);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.SetSelectorPanel;
var
  i: integer;
begin
  if SelectionStyle = csDiscrete then
  begin
    if Assigned(FColorCubePanel) then
      FColorCubePanel.Visible:= false;
    if Assigned(FSpectrumPanel) then
      FSpectrumPanel.Visible:= false;

    inherited;
    FSelectorPanel.OnShouldHide := OnDropDownPanelShouldHide;
    FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;

    FSelectorPanel.MinButtonWidth := 18;
    FSelectorPanel.MinButtonHeight := 18;

    //---- Setting Selected Index
    if FSelectedColor <> clNone then
    begin
      for i := 0 to FSelectorPanel.Items.Count - 1 do
      begin
        if FSelectedColor = FSelectorPanel.Items.Items[i].BackGroundColor then
        begin
          FSelectorPanel.ItemIndex := i;
          FSelectedIndex := i;
          break;
        end;
      end;
    end;
    //----

    FSelectorPanel.ButtonsPerRow := ButtonsPerRow;
    FSelectorPanel.SetItemsPosition;

    if not FSelectorPanel.Visible then
      FSelectorPanel.Visible:= true;
  end
  else if SelectionStyle = csColorCube then
  begin
    if Assigned(FSelectorPanel) then
      FSelectorPanel.Visible:= false;
    if assigned(FSpectrumPanel) then
      FSpectrumPanel.Visible:= false;

    if not assigned(FColorCubePanel) and assigned(FDropDownWindow) then
    begin
      FColorCubePanel := TDgrColorCubePanel.Create(FDropDownWindow);
      FColorCubePanel.Parent := FDropDownWindow;
      FColorCubePanel.WindowBorderColor := FBorderDropDownColor;
      FColorCubePanel.OnShouldHide := OnDropDownPanelShouldHide;
      FColorCubePanel.OnSelect := CubePanelOnSelect;
    end;
    FColorCubePanel.ShowRGBHint := FShowRGBHint;
    FDropDownWindow.SelectorPanel := FColorCubePanel;

    FColorCubePanel.SelectedColor := FSelectedColor;

    FColorCubePanel.SetItemsPosition;

    FColorCubePanel.Left := 0;
    FColorCubePanel.Top := 0;
    if not FColorCubePanel.Visible then
      FColorCubePanel.Visible:= true;
    //FColorCubePanel.Width:= 100;
    //FColorCubePanel.Height:= 140;
  end
  else if SelectionStyle = csSpectrum then
  begin
    if Assigned(FSelectorPanel) then
      FSelectorPanel.Visible:= false;
    if assigned(FColorCubePanel) then
      FColorCubePanel.Visible:= false;

    if not assigned(FSpectrumPanel) and assigned(FDropDownWindow) then
    begin
      FSpectrumPanel := TDgrColorSpectrumPanel.Create(FDropDownWindow);
      FSpectrumPanel.Parent := FDropDownWindow;
      FSpectrumPanel.WindowBorderColor := FBorderDropDownColor;
      FSpectrumPanel.OnShouldHide := OnDropDownPanelShouldHide;
      FSpectrumPanel.OnSelect := SpectrumPanelOnSelect;
    end;
    FDropDownWindow.SelectorPanel := FSpectrumPanel;

    FSpectrumPanel.SelectedColor := FSelectedColor;

    FSpectrumPanel.SetItemsPosition;

    FSpectrumPanel.Left := 0;
    FSpectrumPanel.Top := 0;

    if not FSpectrumPanel.Visible then
      FSpectrumPanel.Visible:= true;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.SetColorSelectionStyle(
  const Value: TColorSelectionStyle);
begin
  if FColorSelectionStyle <> Value then
  begin
    FColorSelectionStyle := Value;
    case FColorSelectionStyle of
      csDiscrete:
        begin

        end;
      csColorCube:
        begin

        end;
      csSpectrum:
        begin

        end;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.Loaded;
begin
  inherited;

end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.DrawGlyphAndCaption(aGlyph: TBitmap; R: TRect);
var
  CapR: TRect;
  clr: TColor;
begin
  CapR := R;
  clr := Canvas.Pen.Color;
  if Style = ssButton then
  begin
    if not aGlyph.Empty then
    begin
      if ShowSelectedColor then
      begin
        CapR.Left := DrawGlyph(Glyph, Rect(R.Left, R.Top, R.Right, R.Bottom - 5));
        CapR.Bottom := CapR.Bottom - 5;
        Canvas.Pen.Color := SelectedColor;
        Canvas.Brush.Color := SelectedColor;
        Canvas.Rectangle(R.Left + 3, R.Bottom - 6, R.Right - 3, R.Bottom - 2);
      end
      else
      begin
        CapR.Left := DrawGlyph(Glyph, Rect(R.Left, R.Top, R.Right, R.Bottom));
      end;
    end
    else
    begin
      if ShowSelectedColor then
      begin
        if (Caption = '') then
        begin
          Canvas.Pen.Color := SelectedColor;
          Canvas.Brush.Color := SelectedColor;
          Canvas.Rectangle(R.Left + 4, R.Top + 3, R.Right - 4, R.Bottom - 3);
        end
        else
        begin
          Canvas.Pen.Color := SelectedColor;
          Canvas.Brush.Color := SelectedColor;
          Canvas.Rectangle(R.Left + 4, R.Bottom - 6, R.Right - 4, R.Bottom - 3);
          CapR.Bottom := CapR.Bottom - 5;
        end;
      end;
    end;
    SetBkMode(Canvas.Handle, TRANSPARENT);
    if Caption <> '' then
{$IFNDEF TMSDOTNET}
      {$IFDEF DELPHI2009_LVL}
      DrawText(Canvas.Handle, Caption, -1, CapR, DT_SINGLELINE or DT_CENTER or DT_VCENTER);
      {$ELSE}
      DrawText(Canvas.Handle, PChar(Caption), -1, CapR, DT_SINGLELINE or DT_CENTER or DT_VCENTER);
      {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
    DrawText(Canvas.Handle, Caption, -1, CapR, DT_SINGLELINE or DT_CENTER or DT_VCENTER);
{$ENDIF}
  end
  else if Style = ssCombo then
  begin
    if {(SelectedIndex >= 0) and }(Caption = '') then
    begin
      Canvas.Pen.Color := clBlack;
      Canvas.Brush.Color := SelectedColor;
      Canvas.Rectangle(R.Left + 4, R.Top + 3, R.Right - 4, R.Bottom - 3);
    end;
  end;
  Canvas.Pen.Color := clr;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.SelectorPanelOnDrawItem(Sender: TObject; Index: integer;
  R: TRect);
var
  R1: TRect;
begin
  if FSelectorPanel.Items.Items[Index].ItemType = itAutoSizeButton then
  begin
    if FSelectorPanel.Items.Items[Index].BackGroundColor <> clNone then
    begin
      FSelectorPanel.Canvas.Pen.Color := clGray;
      FSelectorPanel.Canvas.Brush.Color := FSelectorPanel.Items.Items[Index].BackGroundColor;
      FSelectorPanel.Canvas.Rectangle(R.Left + 3, R.Top + 3, R.Left + 15, R.Top + 15);
    end;
  end
  else
  begin
    if FSelectorPanel.Items.Items[Index].BackGroundColor <> clNone then
    begin
      FSelectorPanel.Canvas.Pen.Color := clGray;
      FSelectorPanel.Canvas.Brush.Color := FSelectorPanel.Items.Items[Index].BackGroundColor;
      FSelectorPanel.Canvas.Rectangle(R.Left + 4, R.Top + 4, R.Left + 16, R.Top + 16);
    end;
    FSelectorPanel.Canvas.Brush.Style := bsClear;
    R1 := R;
    R1.Left := R1.Left + 21; // We must align text in the remaining free space

    if (FSelectorPanel.Items.Items[Index].Caption <> '') then
    case FSelectorPanel.Items.Items[Index].CaptionAlignment of


{$IFNDEF TMSDOTNET}
    {$IFDEF DELPHI2009_LVL}
      taCenter: DrawText(FSelectorPanel.Canvas.Handle, FSelectorPanel.Items.Items[Index].Caption, -1, R, DT_SINGLELINE or DT_VCENTER or DT_CENTER);
      taRightJustify: DrawText(FSelectorPanel.Canvas.Handle, FSelectorPanel.Items.Items[Index].Caption, -1, R, DT_SINGLELINE or DT_VCENTER or DT_RIGHT);
      taLeftJustify: DrawText(FSelectorPanel.Canvas.Handle, FSelectorPanel.Items.Items[Index].Caption, -1, R1, DT_SINGLELINE or DT_VCENTER);
    {$ELSE}
      taCenter: DrawText(FSelectorPanel.Canvas.Handle, PChar(FSelectorPanel.Items.Items[Index].Caption), -1, R, DT_SINGLELINE or DT_VCENTER or DT_CENTER);
      taRightJustify: DrawText(FSelectorPanel.Canvas.Handle, PChar(FSelectorPanel.Items.Items[Index].Caption), -1, R, DT_SINGLELINE or DT_VCENTER or DT_RIGHT);
      taLeftJustify: DrawText(FSelectorPanel.Canvas.Handle, PChar(FSelectorPanel.Items.Items[Index].Caption), -1, R1, DT_SINGLELINE or DT_VCENTER);
    {$ENDIF}
{$ENDIF}
{$IFDEF TMSDOTNET}
      taCenter: DrawText(FSelectorPanel.Canvas.Handle, FSelectorPanel.Items.Items[Index].Caption, -1, R, DT_SINGLELINE or DT_VCENTER or DT_CENTER);
      taRightJustify: DrawText(FSelectorPanel.Canvas.Handle, FSelectorPanel.Items.Items[Index].Caption, -1, R, DT_SINGLELINE or DT_VCENTER or DT_RIGHT);
      taLeftJustify: DrawText(FSelectorPanel.Canvas.Handle, FSelectorPanel.Items.Items[Index].Caption, -1, R1, DT_SINGLELINE or DT_VCENTER);
{$ENDIF}
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.SetShowSelectedColor(const Value: Boolean);
begin
  FShowSelectedColor := Value;
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.CubePanelOnSelect(Sender: TObject);
begin
  if FSelectedColor <> clNone then
    FSelectedColor := FColorCubePanel.SelectedColor;

  DoSelect;
  {if Assigned(FOnSelect) then
    FOnSelect(self, -1, nil);}
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.SpectrumPanelOnSelect(Sender: TObject);
begin
  if FSelectedColor <> clNone then
    FSelectedColor := FSpectrumPanel.SelectedColor;

  DoSelect;
  {if Assigned(FOnSelect) then
    FOnSelect(self, -1, nil);}
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.SetSelectedColor(const Value: TColor);
var
  c: integer;
begin
  if Value <> clNone then
  begin
    FSelectedColor := Value;
  end;
  {in the case of discrete panel, then update selectedindex for the correct selected color}
  if SelectionStyle = csDiscrete then
  begin
    for c := 0 to Tools.Count - 1 do
      if Tools.Items[c].BackGroundColor = FSelectedColor then
      begin
        SelectedIndex := c;
        exit;
      end;
  end;

  Invalidate;
end;

//------------------------------------------------------------------------------

function TDgrCustomColorSelector.GetSelectedColor: TColor;
begin
  Result := FSelectedColor;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomColorSelector.OnToolSelect;
begin
  if (SelectedIndex >= 0) then
  begin
    {Set FSelectedColor, and NOT SelectedColor, because the latter also sets the SelectedIndex.
    We don't want SelectedIndex to be set here, because the tool selected might be the "more colors", and we need to know it
    in the ApplyDiagramSettings method, which is called after this code}
    if Tools.Items[SelectedIndex].BackGroundColor <> clNone then
      FSelectedColor := Tools.Items[SelectedIndex].BackGroundColor;
  end;
  inherited;
end;

procedure TDgrCustomColorSelector.SetShowMoreColors(const Value: boolean);
var
  AItem: TDgrSelectorItem;
begin
  AItem := Self.Tools.IndexOfValue(_moreColorsValue);
  FShowMoreColors := Value;
  if (FShowMoreColors) and (AItem = nil) then
  begin
    with Tools.Add do
    begin
      ItemType := itFullWidthButton;
      CaptionAlignment := taCenter;
      Caption := 'More Colors...';
      Hint := 'More Colors';
      Value := _moreColorsValue;
      BackGroundColor := clNone;
    end;
  end;
  if (not FShowMoreColors) and (AItem <> nil) then
  begin
    AItem.Free;
  end;
end;

//------------------------------------------------------------------------------

{ TDgrColorSelector }

procedure TDgrColorSelector.ApplyDiagramSettings(
  ADiagram: TatDiagram);
var
  c: integer;
  AApply: boolean;
  ASelectedColor: TColor;
begin
  AApply := true;
  if (SelectedIndex >= 0) and (SelectedIndex < Tools.Count)
    and (Tools.Items[SelectedIndex].Value = _morecolorsValue) then
  begin
    if Assigned(FOnMoreColorsOption) then
    begin
      ASelectedColor := FSelectedColor;
      AApply := true;
      FOnMoreColorsOption(Self, ASelectedColor, AApply);
      if AApply then
        SelectedColor := ASelectedColor
      else
        SelectedColor := FSelectedColor;
    end;
  end;

  if AApply then
  begin
    for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
    begin
      if ADiagram.Selecteds[c] is TCustomDiagramBlock then
      begin
        TCustomDiagramBlock(ADiagram.Selecteds[c]).Color := SelectedColor;
        TCustomDiagramBlock(ADiagram.Selecteds[c]).SelColor := SelectedColor;
      end;
    end;
    if ADiagram.SelectedCount > 0 then
    begin
      ADiagram.Modified;
      ADiagram.PushUndoStack('color');
    end;
  end;
end;


{ TDgrTextColorSelector }

procedure TDgrTextColorSelector.ApplyDiagramSettings(
  ADiagram: TatDiagram);
var
  c: integer;
  AApply: boolean;
  ASelectedColor: TColor;
begin
  AApply := true;
  if (SelectedIndex >= 0) and (SelectedIndex < Tools.Count)
    and (Tools.Items[SelectedIndex].Value = _morecolorsValue) then
  begin
    if Assigned(FOnMoreColorsOption) then
    begin
      ASelectedColor := FSelectedColor;
      AApply := true;
      FOnMoreColorsOption(Self, ASelectedColor, AApply);
      if AApply then
        SelectedColor := ASelectedColor
      else
        SelectedColor := FSelectedColor;
    end;
  end;

  if AApply then
  begin
    for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
      ADiagram.Selecteds[c].Font.Color := SelectedColor;
    if ADiagram.SelectedCount > 0 then
    begin
      ADiagram.Modified;
      ADiagram.PushUndoStack('text color');
    end;
  end;
end;

{ TDgrPenColorSelector }

procedure TDgrPenColorSelector.ApplyDiagramSettings(ADiagram: TatDiagram);
var
  c: integer;
  AApply: boolean;
  ASelectedColor: TColor;
begin
  AApply := true;
  if (SelectedIndex >= 0) and (SelectedIndex < Tools.Count)
    and (Tools.Items[SelectedIndex].Value = _morecolorsValue) then
  begin
    if Assigned(FOnMoreColorsOption) then
    begin
      ASelectedColor := FSelectedColor;
      AApply := true;
      FOnMoreColorsOption(Self, ASelectedColor, AApply);
      if AApply then
        SelectedColor := ASelectedColor
      else
        SelectedColor := FSelectedColor;
    end;
  end;

  if AApply then
  begin
    for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
    begin
      if ADiagram.Selecteds[c] is TCustomDiagramBlock then
      begin
        TCustomDiagramBlock(ADiagram.Selecteds[c]).Pen.Color := SelectedColor;
      end;
      if ADiagram.Selecteds[c] is TCustomDiagramLine then
      begin
        TCustomDiagramLine(ADiagram.Selecteds[c]).Pen.Color := SelectedColor;
        TCustomDiagramLine(ADiagram.Selecteds[c]).SelPen.Color := SelectedColor;
      end;
    end;
    if ADiagram.SelectedCount > 0 then
    begin
      ADiagram.Modified;
      ADiagram.PushUndoStack('pen color');
    end;
  end;
end;


{ TDgrPenStyleSelector }

constructor TDgrPenStyleSelector.Create(AOwner: TComponent);
begin
  inherited;
  //if not (csDesigning in ComponentState) then
  begin
    FImages := TCustomImageList.Create(self);
    FImages.Width := 99;
    FImages.Height := 9;
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE0', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE1', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE2', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE3', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE4', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE5', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE6', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_PENSTYLE7', clWhite);
    //b:= FImages.GetInstRes(ac, rtBitmap	, S, 99, lrTransparent, clWhite);
  end;

  Initialize;
end;

//------------------------------------------------------------------------------

destructor TDgrPenStyleSelector.Destroy;
begin
  //if not (csDesigning in ComponentState) and Assigned(FImages) then
  begin
    FImages.Free;
  end;
  inherited;
end;

//------------------------------------------------------------------------------

function TDgrPenStyleSelector.GetSelectedPenStyle: TPenStyle;
begin
  Case SelectedIndex of
    1: result := psDot;
    2: result := psDash;
    3: result := psDashDot;
    4: result := psDashDotDot;
  else
    result := psSolid;
  end;
end;

procedure TDgrPenStyleSelector.Initialize;
begin
  Tools.Clear;

  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Solid';
    ImageIndex := 0;
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 3;
    Hint := 'Dot';
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 5;
    Hint := 'Dash';
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 6;
    Hint := 'Dash Dot';
  end;
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 7;
    Hint := 'Dash Dot Dot';
  end;

end;

//------------------------------------------------------------------------------

procedure TDgrPenStyleSelector.Loaded;
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrPenStyleSelector.SetSelectorPanel;
begin
  inherited;
  FSelectorPanel.Images := Fimages;
  FSelectorPanel.SetItemsPosition;
end;

//------------------------------------------------------------------------------

procedure TDgrPenStyleSelector.ApplyDiagramSettings(ADiagram: TatDiagram);
var
  c: integer;
begin
  for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
  begin
    if ADiagram.Selecteds[c] is TCustomDiagramBlock then
      TCustomDiagramBlock(ADiagram.Selecteds[c]).Pen.Style := SelectedPenStyle;
    if ADiagram.Selecteds[c] is TCustomDiagramLine then
    begin
      TCustomDiagramLine(ADiagram.Selecteds[c]).Pen.Style := SelectedPenStyle;
      TCustomDiagramLine(ADiagram.Selecteds[c]).SelPen.Style := SelectedPenStyle;
    end;
  end;
  if ADiagram.SelectedCount > 0 then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('pen style');
  end;
end;


{ TDgrBrushStyleSelector }

constructor TDgrBrushStyleSelector.Create(AOwner: TComponent);
begin
  inherited;
  FBrushAutoColor := true;
  Initialize;
end;

//------------------------------------------------------------------------------

destructor TDgrBrushStyleSelector.Destroy;
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrBrushStyleSelector.Initialize;
begin
  Tools.Clear;

  {bsSolid}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Solid';
    Value := IntToStr(Ord(bsSolid));
  end;

  {bsClear}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Clear';
    Value := IntToStr(Ord(bsClear));
  end;

  {bsHorizontal}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Horizontal';
    Value := IntToStr(Ord(bsHorizontal));
  end;

  {bsVertical}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Vertical';
    Value := IntToStr(Ord(bsVertical));
  end;

  {bsFDiagonal}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Diagonal';
    Value := IntToStr(Ord(bsFDiagonal));
  end;

  {bsCross}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Cross';
    Value := IntToStr(Ord(bsCross));
  end;

  {bsDiagCross}
  with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Diagonal Cross';
    Value := IntToStr(Ord(bsDiagCross));
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrBrushStyleSelector.Loaded;
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrBrushStyleSelector.SelectorPanelOnDrawItem(Sender: TObject;
  Index: integer; R: TRect);
var
  R2: TRect;
  BS: TBrushStyle;
  OldBrush: TBrush;
  OldPen: TPen;
begin
  R2 := Rect(R.Left + 4, R.Top + 4, R.Right - 4, R.Bottom - 4);

  OldBrush := TBrush.Create;
  OldPen := TPen.Create;
  OldBrush.Assign(FSelectorPanel.Canvas.Brush);
  OldPen.Assign(FSelectorPanel.Canvas.Pen);
  try
    BS := GetBrushStyle(Index);
    FSelectorPanel.Canvas.FillRect(R2);
    With FSelectorPanel.Canvas do
    begin
      Brush.Color := clBlack;
      Brush.Style := BS;
      Pen.Style := psClear;
    end;
    FSelectorPanel.Canvas.Rectangle(R2);
  finally
    FSelectorPanel.Canvas.Brush.Assign(OldBrush);
    FSelectorPanel.Canvas.Pen.Assign(OldPen);
    OldBrush.Free;
    OldPen.Free;
  end;
end;

procedure TDgrBrushStyleSelector.SetSelectorPanel;
begin
  inherited;
  FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;
  FSelectorPanel.MinButtonWidth := 100;
  FSelectorPanel.MinButtonHeight := 20;

  FSelectorPanel.SetItemsPosition;
end;

function TDgrBrushStyleSelector.GetBrushStyle(AIndex: integer): TBrushStyle;
begin
  if AIndex >= 0 then
    result := TBrushStyle(TBrushStyle(StrToInt(FSelectorPanel.Items.Items[AIndex].Value)))
  else
    result := bsClear;
end;

//------------------------------------------------------------------------------


procedure TDgrBrushStyleSelector.ApplyDiagramSettings(
  ADiagram: TatDiagram);
var
  c: integer;
begin
  for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
  begin
    if ADiagram.Selecteds[c] is TCustomDiagramBlock then
    begin
      if FBrushAutoColor then
        TCustomDiagramBlock(ADiagram.Selecteds[c]).Brush.Color := TCustomDiagramBlock(ADiagram.Selecteds[c]).Pen.Color;
      TCustomDiagramBlock(ADiagram.Selecteds[c]).Brush.Style := SelectedBrushStyle;
      if FBrushAutoColor then
        TCustomDiagramBlock(ADiagram.Selecteds[c]).SelBrush.Color := TCustomDiagramBlock(ADiagram.Selecteds[c]).Pen.Color;
      TCustomDiagramBlock(ADiagram.Selecteds[c]).SelBrush.Style := SelectedBrushStyle;
    end;
  end;
  if ADiagram.SelectedCount > 0 then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('brush style');
  end;
end;

function TDgrBrushStyleSelector.GetSelectedBrushStyle: TBrushStyle;
begin
  result := GetBrushStyle(SelectedIndex);
end;

{ TDgrShadowSelector }

constructor TDgrShadowSelector.Create(AOwner: TComponent);
begin
  inherited;
  FShadow := TBlockShadow.Create(nil);
  begin
    FImages := TCustomImageList.Create(self);
    FImages.Width := 20;
    FImages.Height := 20;
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_SHADOW0', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_SHADOW1', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_SHADOW4', clWhite);
    FImages.ResInstLoad(HInstance, rtBitmap, 'DGR_SHADOW5', clWhite);
  end;
  Initialize;
end;

//------------------------------------------------------------------------------

destructor TDgrShadowSelector.Destroy;
begin
  //if not (csDesigning in ComponentState) and Assigned(FImages) then
  begin
    FImages.Free;
  end;
  FShadow.Free;

  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrShadowSelector.Initialize;
begin
  Tools.Clear;

  with self.Tools.Add do
  begin
    ItemType := itFullWidthButton;
    CaptionAlignment := taCenter;
    Caption := '没有阴影';
    Hint := '没有阴影';
  end;
  with self.Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := '阴影风格1';
    ImageIndex := 0;
  end;
  with self.Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 1;
    Hint := '阴影风格2';
  end;
  with self.Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 2;
    Hint := '阴影风格5';
  end;
  with self.Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    ImageIndex := 3;
    Hint := '阴影风格6';
  end;
  SetShowSettingsOption(true);
end;


//------------------------------------------------------------------------------

procedure TDgrShadowSelector.Loaded;
begin
  inherited;

end;

//------------------------------------------------------------------------------

procedure TDgrShadowSelector.SetSelectorPanel;
begin
  inherited;
  FSelectorPanel.Images := Fimages;
  FSelectorPanel.ButtonsPerRow := 4;
  FSelectorPanel.SetItemsPosition;
end;

//------------------------------------------------------------------------------


procedure TDgrShadowSelector.SetShowSettingsOption(const Value: boolean);
begin
  FShowSettingsOption := Value;
  if (FShowSettingsOption) and (self.Tools.Count <= 5) then
  begin
    with self.Tools.Add do
    begin
      ItemType := itFullWidthButton;
      CaptionAlignment := taCenter;
      Caption := '阴影设置';
      Hint := '阴影设置';
    end;
  end;
  if (not FShowSettingsOption) and (self.Tools.Count > 5) then
  begin
    Self.Tools[5].Free;
  end;
end;

procedure TDgrShadowSelector.ApplyDiagramSettings(
  ADiagram: TatDiagram);

  procedure ApplyShadowStyle(AStyle: integer);
  var
    h, v: integer;
  begin
    {Keep the same horizontal and vertical offset values, just set the direction of it,
     by setting the signal of the value}
    h := abs(FShadow.HOffset);
    v := abs(FShadow.VOffset);
    Case AStyle of
      1: begin
           h := -h;
           v := -v;
         end;
      2: v := -v;
      3: h := -h;
      4: ;
    end;
    FShadow.Visible := true;
    FShadow.HOffset := h;
    FShadow.VOffset := v;
  end;

  function OpenShadowSettings: boolean;
  var
    se: TShadowEditor;
  begin
    se := TShadowEditor.Create(nil);
    try
      result := se.EditShadow(FShadow);
    finally
      se.Free;
    end;
  end;

  procedure RollbackSelectedIndex;
  begin
    if not FShadow.Visible then
      SelectedIndex := 0
    else
    begin
      if (FShadow.HOffset <= 0) and (FShadow.VOffset <= 0) then
        SelectedIndex := 1
      else
      if (FShadow.HOffset >= 0) and (FShadow.VOffset <= 0) then
        SelectedIndex := 2
      else
      if (FShadow.HOffset <= 0) and (FShadow.VOffset >= 0) then
        SelectedIndex := 3
      else
        SelectedIndex := 4;
    end;
  end;

var
  c: integer;
  AApply: boolean;
begin
  AApply := true;
  Case SelectedIndex of
    0: FShadow.Visible := false;
    1..4: ApplyShadowStyle(SelectedIndex);
    5:
      begin
        AApply := OpenShadowSettings;
        RollbackSelectedIndex;
      end;
  end;

  {apply diagram settings in blocks}
  if AApply then
  begin
    for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
    begin
      if ADiagram.Selecteds[c] is TCustomDiagramBlock then
        TCustomDiagramBlock(ADiagram.Selecteds[c]).Shadow.Assign(FShadow);
    end;
    if ADiagram.SelectedCount > 0 then
    begin
      ADiagram.Modified;
      ADiagram.PushUndoStack('shadow');
    end;
  end;
end;

{ TDgrGradientDirectionSelector }

constructor TDgrGradientDirectionSelector.Create(AOwner: TComponent);
begin
  inherited;
  FGradient := TDiagramGradient.Create(nil);
  FGradient.StartColor := clWhite;
  FGradient.EndColor := clGray;
  FShowSelectedGradient := true;
  Initialize;
end;

//------------------------------------------------------------------------------

destructor TDgrGradientDirectionSelector.Destroy;
begin
  FGradient.Free;
  inherited;
end;

//------------------------------------------------------------------------------

function TDgrGradientDirectionSelector.GetEndColor: TColor;
begin
  result := FGradient.EndColor;
end;

function TDgrGradientDirectionSelector.GetStartColor: TColor;
begin
  result := FGradient.StartColor;
end;

procedure TDgrGradientDirectionSelector.Initialize;
var
  c: TGradientDirection;
begin
  Tools.Clear;

  with Tools.Add do
  begin
    ItemType := itFullWidthButton;
    CaptionAlignment := taCenter;
    Caption := '没有渐变';
    Value := 'no';
  end;

  for c := Low(TGradientDirection) to High(TGradientDirection) do
    With Tools.Add do
    begin
      ItemType := itAutoSizeButton;
      Value := IntToStr(Ord(c));
    end;

  with Tools.Add do
  begin
    ItemType := itFullWidthButton;
    CaptionAlignment := taCenter;
    Caption := '选择开始颜色';
    Value := 'start';
  end;
  with Tools.Add do
  begin
    ItemType := itFullWidthButton;
    CaptionAlignment := taCenter;
    Caption := '选择结束颜色';
    Value := 'end';
  end;
  {Set defaults}
  FGradient.Visible := true;
  FGradient.Direction := Low(TGradientDirection);
end;

//------------------------------------------------------------------------------

procedure TDgrGradientDirectionSelector.SelectorPanelOnDrawItem(Sender: TObject;
  Index: integer; R: TRect);
var
  R2: TRect;
  value: string;
  OldBrush: TBrush;
  OldPen: TPen;
  OldDirection: TGradientDirection;                                                         
begin
  value := FSelectorPanel.Items.Items[Index].Value;

  {Test if the item is an owner drawn item}
  if (value <> 'no') and (value <> 'start') and (value <> 'end') then
  begin
    OldBrush := TBrush.Create;
    OldPen := TPen.Create;
    OldBrush.Assign(FSelectorPanel.Canvas.Brush);
    OldPen.Assign(FSelectorPanel.Canvas.Pen);
    try
      R2 := Rect(R.Left + 4, R.Top + 4, R.Right - 4, R.Bottom - 4);
      OldDirection := FGradient.Direction;
      FGradient.Direction := GetGradientDirection(Index);
      FGradient.DrawGradient(FSelectorPanel.canvas, Square(R2), 0);
      FGradient.Direction := OldDirection;
    finally
      FSelectorPanel.Canvas.Brush.Assign(OldBrush);
      FSelectorPanel.Canvas.Pen.Assign(OldPen);
      OldBrush.Free;
      OldPen.Free;
    end;
  end else
  begin
    {If it's not owner drawn, then do a workaround in order for ancestor to draw the item}
    FSelectorPanel.OnDrawItem := nil;
    FSelectorPanel.DrawItem(Index);
    FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrGradientDirectionSelector.SetEndColor(const Value: TColor);
begin
  FGradient.EndColor := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrGradientDirectionSelector.SetSelectorPanel;
begin
  inherited;
  FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;
  FSelectorPanel.MinButtonWidth := 50;
  FSelectorPanel.MinButtonHeight := 40;
  FSelectorPanel.ButtonsPerRow := 2;

  FSelectorPanel.SetItemsPosition;
end;

//------------------------------------------------------------------------------

procedure TDgrGradientDirectionSelector.SetStartColor(const Value: TColor);
begin
  FGradient.StartColor := Value;
end;

//------------------------------------------------------------------------------

function TDgrGradientDirectionSelector.GetGradientDirection(AIndex: integer): TGradientDirection;
begin
  if AIndex >= 0 then
    result := TGradientDirection(StrToInt(FSelectorPanel.Items.Items[AIndex].Value))
  else
    result := FGradient.Direction;
end;

procedure TDgrGradientDirectionSelector.ApplyDiagramSettings(ADiagram: TatDiagram);

  procedure ChooseStartColor;
  var
    CD: TColorDialog;
  begin
    CD := TColorDialog.Create(nil);
    try
      CD.Color := FGradient.StartColor;
      if CD.Execute then
        FGradient.StartColor := CD.Color;
    finally
      CD.Free;
    end;
  end;

  procedure ChooseEndColor;
  var
    CD: TColorDialog;
  begin
    CD := TColorDialog.Create(nil);
    try
      CD.Color := FGradient.EndColor;
      if CD.Execute then
        FGradient.EndColor := CD.Color;
    finally
      CD.Free;
    end;
  end;

  procedure RollbackSelectedIndex;
  var
    c: integer;
    Str: string;
  begin
    if not FGradient.Visible then
      SelectedIndex := 0
    else
    begin
      for c := 1 to FSelectorPanel.Items.Count - 1 do
      begin
        Str := FSelectorPanel.Items.Items[c].Value;
        if Str = IntToStr(Ord(FGradient.Direction)) then
        begin
          SelectedIndex := c;
          break;
        end;
      end;
    end;
  end;

var
  c: integer;
  value: string;
begin
  {adjust gradient settings of internal object}
  if SelectedIndex >= 0 then
  begin
    value := FSelectorPanel.Items.Items[SelectedIndex].Value;
    if value = 'no' then
      FGradient.Visible := false
    else
    if value = 'start' then
      ChooseStartColor
    else
    if value = 'end' then
      ChooseEndColor
    else
    begin
      FGradient.Visible := true;
      FGradient.Direction := GetGradientDirection(SelectedIndex);
    end;
  end;

  {apply diagram settings in blocks}
  for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
  begin
    if ADiagram.Selecteds[c] is TCustomDiagramBlock then
      TCustomDiagramBlock(ADiagram.Selecteds[c]).Gradient.Assign(FGradient);
  end;

  if ADiagram.SelectedCount > 0 then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('gradient');
  end;

  {Revert the selected index according with gradient settings}
  if (value = 'start') or (value = 'end') then
    RollbackSelectedIndex;

  if ShowSelectedGradient then
    Invalidate;
end;

procedure TDgrGradientDirectionSelector.DrawGlyphAndCaption(aGlyph: TBitmap; R: TRect);
var
  OldBrush: TBrush;
  OldPen: TPen;
  R2: TRect;
begin
  inherited;
  if ShowSelectedGradient then
  begin
    OldBrush := TBrush.Create;
    OldPen := TPen.Create;
    try
      OldBrush.Assign(Canvas.Brush);
      OldPen.Assign(Canvas.Pen);
      Canvas.Pen.Color := clBlack;
      Canvas.Pen.Style := psSolid;
      Canvas.Brush.Color := clWhite;
      Canvas.Brush.Style := bsSolid;
      R2 := Rect(R.Left + 5, R.Top + 4, R.Right - 5, R.Bottom - 4);
      Canvas.Rectangle(R2);
      R2 := Rect(R2.Left + 1, R2.Top + + 1, R2.Right - 1, R2.Bottom - 1);
      if FGradient.Visible then
        FGradient.DrawGradient(Canvas, Square(R2), 0);
    finally
      Canvas.Brush.Assign(OldBrush);
      Canvas.Pen.Assign(OldPen);
      OldBrush.Free;
      OldPen.Free;
    end;
  end;
end;

procedure TDgrGradientDirectionSelector.SetShowSelectedGradient(
  const Value: boolean);
begin
  FShowSelectedGradient := Value;
  Invalidate;
end;

{ TDgrPenWidthSelector }

constructor TDgrPenWidthSelector.Create(AOwner: TComponent);
begin
  inherited;
  Initialize;
end;

//------------------------------------------------------------------------------

destructor TDgrPenWidthSelector.Destroy;
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrPenWidthSelector.Initialize;
var
  c: integer;
begin
  Tools.Clear;

  for c := 1 to 9 do
    with Tools.Add do
    begin
      ItemType := itAutoSizeButton;
      CaptionAlignment := taLeftJustify;
      Caption := Format('%d pt', [c]);
      Value := IntToStr(c);
    end;
end;

//------------------------------------------------------------------------------

procedure TDgrPenWidthSelector.SetSelectorPanel;
begin
  inherited;
  FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;
  FSelectorPanel.MinButtonWidth := 130;
  FSelectorPanel.MinButtonHeight := 20;
  FSelectorPanel.ButtonsPerRow := 1;

  FSelectorPanel.SetItemsPosition;
end;

procedure TDgrPenWidthSelector.ApplyDiagramSettings(ADiagram: TatDiagram);
var
  c: integer;
begin
  for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
  begin
    if ADiagram.Selecteds[c] is TCustomDiagramBlock then
    begin
      TCustomDiagramBlock(ADiagram.Selecteds[c]).Pen.Width := SelectedPenWidth;
    end;
    if ADiagram.Selecteds[c] is TCustomDiagramLine then
    begin
      TCustomDiagramLine(ADiagram.Selecteds[c]).Pen.Width := SelectedPenWidth;
      TCustomDiagramLine(ADiagram.Selecteds[c]).SelPen.Width := SelectedPenWidth;
    end;
  end;
  if ADiagram.SelectedCount > 0 then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('pen width');
  end;
end;

//------------------------------------------------------------------------------


function TDgrPenWidthSelector.GetSelectedPenWidth: integer;
begin
  result := GetPenWidth(SelectedIndex);
end;

function TDgrPenWidthSelector.GetPenWidth(AIndex: integer): integer;
begin
  if AIndex >= 0 then
    result := StrToInt(FSelectorPanel.Items.Items[AIndex].Value)
  else
    result := 1;
end;

procedure TDgrPenWidthSelector.SelectorPanelOnDrawItem(Sender: TObject;
  Index: integer; R: TRect);
var
  R1: TRect;
  R2: TRect;
  PW: integer;
  OldPen: TPen;
  captionLength: integer;
begin
  {Draw the text and after only draw the line}
  FSelectorPanel.OnDrawItem := nil;
  FSelectorPanel.DrawItem(Index);
  FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;

  captionLength := Max(FSelectorPanel.FMaxCaptionLength, FSelectorPanel.Canvas.TextWidth(FSelectorPanel.Items.Items[Index].Caption));
  R1 := Rect(R.Left + 8 + captionLength, R.Top + 4, R.Right - 4,  R.Bottom - 4);
  R2 := Rect(R.Left + 8 + captionLength, (R.Top + R.Bottom) div 2, R.Right - 4,  (R.Top + R.Bottom) div 2 + 1);

  OldPen := TPen.Create;
  OldPen.Assign(FSelectorPanel.Canvas.Pen);
  try
    PW := GetPenWidth(Index);
    FSelectorPanel.Canvas.FillRect(R1);
    With FSelectorPanel.Canvas do
    begin
      Pen.Color := clBlack;
      Pen.Style := psSolid;
      Pen.Width := PW;
    end;
    FSelectorPanel.Canvas.Rectangle(R2);
  finally
    FSelectorPanel.Canvas.Pen.Assign(OldPen);
    OldPen.Free;
  end;
end;

{ TDgrTransparencySelector }

procedure TDgrTransparencySelector.ApplyDiagramSettings(
  ADiagram: TatDiagram);
var
  c: integer;
begin
  for c := 0 to ADiagram.SelectedCount - 1 do if not ADiagram.Selecteds[c].IsGroup then
  begin
    if ADiagram.Selecteds[c] is TCustomDiagramBlock then
    begin
      TCustomDiagramBlock(ADiagram.Selecteds[c]).Transparency := SelectedTransparency;
    end;
    if ADiagram.Selecteds[c] is TCustomDiagramLine then
    begin
      TCustomDiagramLine(ADiagram.Selecteds[c]).Transparency := SelectedTransparency;
    end;
  end;
  if ADiagram.SelectedCount > 0 then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('transparency');
  end;
end;

constructor TDgrTransparencySelector.Create(AOwner: TComponent);
begin
  inherited;
  Initialize;
end;

function TDgrTransparencySelector.GetSelectedTransparency: integer;
begin
  Case SelectedIndex of
    0..10: result := SelectedIndex * 10;
  else
    result := 0;
  end;
end;

procedure TDgrTransparencySelector.Initialize;
var
  c: integer;
begin
  Tools.Clear;

  {with Tools.Add do
  begin
    ItemType := itAutoSizeButton;
    Hint := 'Diagonal Cross';
    Value := IntToStr(Ord(bsDiagCross));
  end;}

  for c := 1 to 10 do
    with Tools.Add do
    begin
      ItemType := itAutoSizeButton;
      Hint := IntToStr(c * 10) + '%';
      Value := IntToStr(c * 10);
    end;
end;

procedure TDgrTransparencySelector.SelectorPanelOnDrawItem(Sender: TObject;
  Index: integer; R: TRect);
var
  R2: TRect;
  OldBrush: TBrush;
  OldPen: TPen;
  AByte: integer;
begin
  R2 := Rect(R.Left + 4, R.Top + 4, R.Right - 4, R.Bottom - 4);
  OldBrush := TBrush.Create;
  OldPen := TPen.Create;
  OldBrush.Assign(FSelectorPanel.Canvas.Brush);
  OldPen.Assign(FSelectorPanel.Canvas.Pen);
  try
    With FSelectorPanel.Canvas do
    begin
      AByte := trunc(Index * 25.5);
      Brush.Color := RGB(AByte, AByte, AByte);
      FillRect(R2);
      Pen.Style := psSolid;
      Pen.Color := clBlack;
      Rectangle(R2);
    end;
  finally
    FSelectorPanel.Canvas.Brush.Assign(OldBrush);
    FSelectorPanel.Canvas.Pen.Assign(OldPen);
    OldBrush.Free;
    OldPen.Free;
  end;
end;

procedure TDgrTransparencySelector.SetSelectorPanel;
begin
  inherited;
  FSelectorPanel.OnDrawItem := SelectorPanelOnDrawItem;
  FSelectorPanel.MinButtonWidth := 100;
  FSelectorPanel.MinButtonHeight := 20;
  FSelectorPanel.SetItemsPosition;
end;


initialization

{$IFDEF FREEWARE}
{if (FindWindow('TApplication', nil) = 0) or
  (FindWindow('TAlignPalette', nil) = 0) or
  (FindWindow('TPropertyInspector', nil) = 0) or
  (FindWindow('TAppBuilder', nil) = 0) then
begin
  //ShowMessage('Diagram Studio trial version');
end   }
{$ENDIF}

end.

