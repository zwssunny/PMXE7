{***************************************************************************}
{ Diagram Studio                                                            }
{ for Delphi & C++Builder                                                   }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright © 2003-2009                                          }
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

unit DgrCombo;

{$I DIAGRAM.INC}

interface

uses
  Windows, Messages, StdCtrls, Classes, Graphics, Controls, SysUtils, Forms,
  Math
  {$IFDEF TMSDOTNET}
  , uxTheme, System.Text, Types, WinUtils
  {$ENDIF}
  , atDiagram
  ;

const
  LISTITEMHEIGHT = 14;

  MAJ_VER = 2; // Major version nr.
  MIN_VER = 0; // Minor version nr.
  REL_VER = 0; // Release nr.
  BLD_VER = 0; // Build nr.

type
  TDgrFontType = (aftBitmap, aftTrueType, aftPostScript, aftPrinter, aftFixedPitch, aftProportional);
  TDgrFontTypes = set of TDgrFontType;

  TWinCtrl = class(TWinControl);
  TDgrCustomComboBox = class;

  TDropDownWindow = class(THintWindow)
  private
    FListControl: TListBox;
    FHideOnDeActivate: Boolean;
    procedure WMNCButtonDown(var Message: TMessage); message WM_NCLBUTTONDOWN;
    procedure WMActivate(var Message: TMessage); message WM_ACTIVATE;
    procedure WMNCHitTest(var Message: TWMNCHitTest); message WM_NCHITTEST;
  protected
    procedure CreateParams(var Params: TCreateParams); override;
    property HideOnDeActivate: Boolean read FHideOnDeActivate write FHideOnDeActivate;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property BorderWidth;
    property ListControl: TListBox read FListControl write FListControl;
  end;

  TDgrComboBtn = class(TPersistent)
  private
    FOnChange: TNotifyEvent;
    FWidth: integer;
    FGlyph: TBitMap;
    FGlyphDown: TBitMap;
    FGlyphHot: TBitMap;
    FColorHot: TColor;
    FColorTo: TColor;
    FColorDownTo: TColor;
    FColorDown: TColor;
    FColorHotTo: TColor;
    FColor: TColor;
    FDownArrowColor: TColor;
    FHotArrowColor: TColor;
    FArrowColor: TColor;
    FCombo: TDgrCustomComboBox;
    FDownArrow: Boolean;
    procedure SetWidth(const Value: integer);
    procedure Change;
    procedure SetColor(const Value: TColor);
    procedure SetColorTo(const Value: TColor);
    procedure SetColorDown(const Value: TColor);
    procedure SetColorDownTo(const Value: TColor);
    procedure SetGlyphDown(const Value: TBitMap);
    procedure SetGlyph(const Value: TBitMap);
    procedure SetColorHot(const Value: TColor);
    procedure SetColorHotTo(const Value: TColor);
    procedure SetGlyphHot(const Value: TBitMap);
    procedure SetArrowColor(const Value: TColor);
    procedure SetDownArrowColor(const Value: TColor);
    procedure SetHotArrowColor(const Value: TColor);
  protected
    property ArrowColor: TColor read FArrowColor write SetArrowColor;
    property HotArrowColor: TColor read FHotArrowColor write SetHotArrowColor;
    property DownArrowColor: TColor read FDownArrowColor write SetDownArrowColor;
    property DownArrow: Boolean read FDownArrow write FDownArrow;

    property Combo: TDgrCustomComboBox read FCombo write FCombo;

    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Assign(Source: TPersistent); override;
  published
    property Color: TColor read FColor write SetColor;
    property ColorTo: TColor read FColorTo write SetColorTo;
    property ColorHot: TColor read FColorHot write SetColorHot;
    property ColorHotTo: TColor read FColorHotTo write SetColorHotTo;
    property ColorDown: TColor read FColorDown write SetColorDown;
    property ColorDownTo: TColor read FColorDownTo write SetColorDownTo;

    property Glyph: TBitMap read FGlyph write SetGlyph;
    property GlyphHot: TBitMap read FGlyphHot write SetGlyphHot;
    property GlyphDown: TBitMap read FGlyphDown write SetGlyphDown;
    property Width: integer read FWidth write SetWidth;
  end;

  TDgrComboStyle = (esOffice2003Blue, esOffice2003Silver, esOffice2003Olive, esOffice2003Classic, esOffice2007Luna, esOffice2007Obsidian, esWindowsXP, esWhidbey, esCustom, esOffice2007Silver);
  TComboStyle = (csDropDown, csDropDownList);
  TSelectionGradient = (sgVertical, sgHorizontal, sgVerticalInOut, sgHorizontalInOut);

  TDgrCustomComboBox = class(TCustomEdit)
  private
    FAutoFocus: boolean;
    FMouseInControl: Boolean;
    FOnMouseEnter: TNotifyEvent;
    FButtonDown: Boolean;
    FDroppedDown: Boolean;
    //FFocusFontColor: TColor;
    FOnMouseLeave: TNotifyEvent;
    FButton: TDgrComboBtn;
    FFlat: Boolean;
    FBorderHotColor: TColor;
    FBorderColor: TColor;
    FAutoThemeAdapt: Boolean;
    FAppearanceStyle: TDgrComboStyle;
    FOldCursor: TCursor;
    FDropDownList: TDropDownWindow;
    FDropDownListBox: TListBox;
    FItems: TStringList;
    FDropDownCount: integer;
    FOnBeforeDropDown: TNotifyEvent;
    FItemIndex: integer;
    FSelectionColor: TColor;
    FFontHeight: integer;
    FItemHeight: integer;
    FLookUp: Boolean;
    FChanged: Boolean;
    FMatchCase: Boolean;
    FWorkMode: Boolean;
    FOldText: string;
    FSelectionColorTo: TColor;
    FSelectionGradient: TSelectionGradient;
    FDisplayRecentSelection: Boolean;
    FRecentSelection: TStringList;
    FStyle: TComboStyle;
    FAutoItemSize: boolean;
    FSelectionTextColor: TColor;
    FOnSelect: TNotifyEvent;
    FOnDropDown: TNotifyEvent;
    FOnCloseUp: TNotifyEvent;
    FDropDownListColor: TColor;
    procedure CNCtlColorEdit(var Message: TWMCtlColorEdit); message CN_CTLCOLOREDIT;
    procedure CNCtlColorStatic(var Message: TWMCtlColorStatic); message CN_CTLCOLORSTATIC;
    procedure CMCancelMode(var Message: TMessage); message CM_CANCELMODE;
    procedure WMSetFocus(var Msg: TWMSetFocus); message WM_SETFOCUS;
    procedure WMKillFocus(var Msg: TWMKillFocus); message WM_KILLFOCUS;
    procedure WMChar(var Msg: TWMKey); message WM_CHAR;
    procedure WMLButtonUp(var Msg: TWMMouse); message WM_LBUTTONUP;
    procedure WMLButtonDown(var Msg: TWMMouse); message WM_LBUTTONDOWN;
    procedure WMPaint(var Msg: TWMPaint); message WM_PAINT;
    procedure CMFontChanged(var Message: TMessage); message CM_FONTCHANGED;

    procedure WMSize(var Message: TWMSize); message WM_SIZE;
    procedure WMEraseBkGnd(var Message: TWMEraseBkGnd); message WM_ERASEBKGND;
    procedure WMMouseMove(var Msg: TWMMouse); message WM_MOUSEMOVE;
    procedure CMMouseEnter(var Msg: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
    procedure CMEnter(var Message: TCMGotFocus); message CM_ENTER;
    procedure CMExit(var Message: TCMExit); message CM_EXIT;
    procedure CMWantSpecialKey(var Msg: TCMWantSpecialKey); message CM_WANTSPECIALKEY;
    procedure DrawButton(DC: HDC); overload;
    procedure DrawButton; overload;
    procedure DrawBorders(DC: HDC); overload;
    procedure DrawBorders; overload;
    function GetButtonRect: TRect;
    function GetMinHeight: Integer;
    function GetListItemHeight: integer;
    procedure ResizeControl;
    procedure ButtonOnChange(Sender: TObject);
    procedure ButtonClick;
    procedure ListBoxKeyPress(Sender: TObject; var Key: Char);
    procedure ListBoxMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure ListBoxMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure ListBoxKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure ListBoxOnEnter(Sender: TObject);
    procedure ListBoxChange(Sender: TObject);
    procedure ShowDropDown;
    procedure HideDropDown;
    procedure LookUpText;
    procedure ThemeAdapt;
    function GetVersionNr: Integer; virtual;
    procedure SetButton(const Value: TDgrComboBtn);
    procedure SetFlat(const Value: Boolean);
    procedure SetBorderColor(const Value: TColor);
    procedure SetBorderHotColor(const Value: TColor);
    procedure SetAppearanceStyle(const Value: TDgrComboStyle);
    procedure SetItems(const Value: TStringList);
    procedure SetItemIndex(const Value: integer);
    procedure SetSelectionColor(const Value: TColor);
    procedure SetFontHeight(const Value: integer);
    procedure SetLookUp(const Value: Boolean);
    function GetItemIndex: integer;
    procedure SetSelectionColorTo(const Value: TColor);
    procedure SetSelectionGradient(const Value: TSelectionGradient);
    procedure SetDisplayRecentSelection(const Value: Boolean);
    function GetItemHeight: integer;
    procedure SetItemHeight(const Value: integer);
    procedure SetStyle(const Value: TComboStyle);
    procedure SetAutoItemSize(const Value: boolean);
    procedure SetTextEx(const Value: string);
    function GetTextEx: string;
    function GetVersion: string;
    procedure SetVersion(const Value: string);
    function GetDropDown: boolean;
    procedure SetDropDown(const Value: boolean);
    procedure ItemsChanged(Sender: TObject);
  protected
    procedure SetEditRect;
    procedure Loaded; override;
    procedure DoEnter; override;
    procedure CreateWnd; override;
    procedure CreateParams(var Params: TCreateParams); override;
    procedure WndProc(var Message: TMessage); override;
    procedure KeyUp(var Key: Word; Shift: TShiftState); override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;

    procedure First;
    procedure Previous;
    procedure Next;
    procedure Last;
    procedure PageJump(GoForward: Boolean);

    procedure BeforeDropDown; virtual;
    procedure DoDropDown; virtual;
    procedure DoCloseUp; virtual;
    procedure DoSelect; virtual;
    procedure DropDownOnDrawItem(Control: TWinControl; Index: Integer; Rect: TRect; State: TOwnerDrawState); virtual;
    procedure ValueChanged; virtual;
    procedure UpdateIndex; virtual;
    procedure PopulateListBox; virtual;

    property Flat: Boolean read FFlat write SetFlat;
    property AutoItemSize: boolean read FAutoItemSize write SetAutoItemSize default true;
    property ItemHeight: integer read GetItemHeight write SetItemHeight;
    property FontHeight: integer read FFontHeight write SetFontHeight;
    property Style: TComboStyle read FStyle write SetStyle default csDropDown;
  public
    constructor Create(aOwner: TComponent); override;
    destructor Destroy; override;
    function CharFromPos(pt: TPoint): Integer;
    procedure Change; override;
    property Items: TStringList read FItems write SetItems;
    property ItemIndex: integer read GetItemIndex write SetItemIndex;
    property RecentSelection: TStringList read FRecentSelection;
    property AppearanceStyle: TDgrComboStyle read FAppearanceStyle write SetAppearanceStyle;
    property DroppedDown: boolean read GetDropDown write SetDropDown;
  published
    property Anchors;
    property Color;
    property Align;
    property AutoFocus: boolean read FAutoFocus write fAutoFocus default false;
    property AutoThemeAdapt: Boolean read FAutoThemeAdapt write FAutoThemeAdapt default False;
    property Button: TDgrComboBtn read FButton write SetButton;
    property DisplayRecentSelection: Boolean read FDisplayRecentSelection write SetDisplayRecentSelection default true;
    property DropDownCount: integer read FDropDownCount write FDropDownCount;
    property BorderColor: TColor read FBorderColor write SetBorderColor;
    property BorderHotColor: TColor read FBorderHotColor write SetBorderHotColor;
    property LookUp: Boolean read FLookUp write SetLookUp default true;
    property SelectionColor: TColor read FSelectionColor write SetSelectionColor;
    property SelectionColorTo: TColor read FSelectionColorTo write SetSelectionColorTo default clNone;
    property SelectionTextColor: TColor read FSelectionTextColor write FSelectionTextColor default clHighLightText;
    property SelectionGradient: TSelectionGradient read FSelectionGradient write SetSelectionGradient default sgVerticalInOut;
    property Text: string read GetTextEx write SetTextEx; 
    property Version: string read GetVersion write SetVersion;
    property DropDownListColor: TColor read FDropDownListColor write FDropDownListColor;
    property PopupMenu;
    property OnExit;
    property OnEnter;
    property OnChange;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnDropDown: TNotifyEvent read FOnDropDown write FOnDropDown;
    property OnCloseUp: TNotifyEvent read FOnCloseUp write FOnCloseUp;
    property OnMouseEnter: TNotifyEvent read FOnMouseEnter write FOnMouseEnter;
    property OnMouseLeave: TNotifyEvent read FOnMouseLeave write FOnMouseLeave;
    property OnBeforeDropDown: TNotifyEvent read FOnBeforeDropDown write FOnBeforeDropDown;
    property OnSelect: TNotifyEvent read FOnSelect write FOnSelect;
  end;

  TDgrOfficeComboBox = class(TDgrCustomComboBox)
  private
  protected
  public
    constructor Create(aOwner: TComponent); override;
  published
    property Anchors;
    property Enabled;
    property Items;
    property ItemIndex;
    property ItemHeight;
    property Text;
    property Font;
    property Style;

    property Color;
    property BiDiMode;
    property Constraints;
    property ParentBiDiMode;
    property ImeMode;
    property ImeName;
    property ParentColor;
    property ParentCtl3D;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnClick;
    property OnEnter;
    property OnExit;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnStartDrag;
    property OnEndDock;
    property OnStartDock;
  end;

  TDgrBaseComboBox = class(TDgrCustomComboBox)
  private
    FDiagram: TatDiagram;
    procedure SetDiagram(const Value: TatDiagram);
  protected
    procedure DiagramChanged; virtual;
    procedure Notification(AComponent: TComponent; AOperation: TOperation); override;
  published
    property Diagram: TatDiagram read FDiagram write SetDiagram;
  end;

  TDgrFontSelector = class(TDgrBaseComboBox)
  private
    FFontGlyphTT: TBitMap;
    FFontGlyphPS: TBitMap;
    FFontGlyphPRN: TBitMap;
    FFontGlyphBMP: TBitMap;
    FShowFontStyle: Boolean;
    FShowFontGlyph: Boolean;
    FAllowedFontTypes: TDgrFontTypes;
    //FRecentSelection: TStringList;
    //FDisplayRecentSelection: Boolean;
    procedure SetFontGlyphTT(const Value: TBitMap);
    procedure SetFontGlyphPS(const Value: TBitMap);
    procedure SetFontGlyphPRN(const Value: TBitMap);
    procedure SetFontGlyphBMP(const Value: TBitMap);
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    function GetFontType(const Fontname: string): TDgrFontTypes;
    //procedure SetDisplayRecentSelection(const Value: Boolean);
  protected
    procedure DiagramChanged; override;
    procedure ApplySelectedFont(ADiagram: TatDiagram; AFontName: string); virtual;
    procedure Loaded; override;
    procedure BeforeDropDown; override;
    procedure DropDownOnDrawItem(Control: TWinControl; Index: Integer; Rect: TRect; State: TOwnerDrawState); override;
    procedure ValueChanged; override;
    //procedure PopulateListBox; override;
  public
    constructor Create(aOwner: TComponent); override;
    procedure CreateWnd; override;
    destructor Destroy; override;
    procedure LoadFontNames;
    //property RecentSelection: TStringList read FRecentSelection;
  published
    property AllowedFontTypes: TDgrFontTypes read FAllowedFontTypes write FAllowedFontTypes;
    property FontGlyphTT: TBitMap read FFontGlyphTT write SetFontGlyphTT;
    property FontGlyphPS: TBitMap read FFontGlyphPS write SetFontGlyphPS;
    property FontGlyphPRN: TBitMap read FFontGlyphPRN write SetFontGlyphPRN;
    property FontGlyphBMP: TBitMap read FFontGlyphBMP write SetFontGlyphBMP;
    property ShowFontStyle : Boolean read FShowFontStyle write FShowFontStyle default  True;
    property ShowFontGlyph: Boolean read FShowFontGlyph write FShowFontGlyph default True;
    property FontHeight;
    //property DisplayRecentSelection: Boolean read FDisplayRecentSelection write SetDisplayRecentSelection default true;

    property Color;
    property Enabled;
    property Font;
    property Anchors;
    property BiDiMode;
    property Constraints;
    property ParentBiDiMode;
    property ImeMode;
    property ImeName;
    property ParentColor;
    property ParentCtl3D;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Style;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnClick;
    property OnEnter;
    property OnExit;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnStartDrag;
    property OnEndDock;
    property OnStartDock;
  end;

  TDgrZoomSelector = class(TDgrBaseComboBox)
  private
    procedure LoadZoomItems;
    function GetZoom: integer;
  protected
    function GetZoomText(AZoom: integer): string; virtual;
    procedure DiagramChanged; override;
    procedure ApplySelectedZoom(ADiagram: TatDiagram; AZoom: integer); virtual;
    procedure ValueChanged; override;
    function GetZoomFromText(AText: string): integer; virtual;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure CreateWnd; override;
  public
    constructor Create(AOwner: TComponent); override;
    procedure InitiateAction; override;
    property Zoom: integer read GetZoom;
  end;

  TDgrFontSizeSelector = class(TDgrBaseComboBox)
  private
    procedure LoadSizeItems;
    function GetFontSize: integer;
  protected
    function GetSizeText(ASize: integer): string; virtual;
    procedure DiagramChanged; override;
    procedure ApplySelectedSize(ADiagram: TatDiagram; ASize: integer); virtual;
    procedure ValueChanged; override;
    function GetSizeFromText(AText: string): integer; virtual;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure CreateWnd; override;
  public
    constructor Create(AOwner: TComponent); override;
    property FontSize: integer read GetFontSize;
  end;

  TDgrLayerSelector = class(TDgrBaseComboBox)
  private
    FAutoChange: boolean;
    procedure LoadLayerItems;
    function GetLayerName: string;
    procedure SetLayerName(const Value: string);
  protected
    procedure ApplySelectedLayer(ADiagram: TatDiagram; ALayerName: string);
    procedure ValueChanged; override;
  public
    constructor Create(AOwner: TComponent); override;
    procedure InitiateAction; override;
    property LayerName: string read GetLayerName write SetLayerName;
  end;

procedure DrawGradient(Canvas: TCanvas; FromColor, ToColor: TColor; Steps: Integer; R: TRect; Direction: Boolean);

implementation

{$R DgrCombo.res}

uses
  ComObj;

const
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

function upstr(s: string; docase: boolean): string;
begin
  if docase then
    Result := s
  else
    Result := AnsiUpperCase(s);
end;

//------------------------------------------------------------------------------

{ TDgrCustomComboBox }

procedure TDgrCustomComboBox.ButtonOnChange(Sender: TObject);
begin
  //SetEditRect;
  //ResizeControl;
  Invalidate;
end;

//------------------------------------------------------------------------------

function TDgrCustomComboBox.CharFromPos(pt: TPoint): Integer;
begin
  Result := Loword(SendMessage(self.Handle, EM_CHARFROMPOS, 0, makelparam(pt.x, pt.y)));
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMFontChanged(var Message: TMessage);
begin
  inherited;
  //SetEditRect;
  ResizeControl;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMMouseEnter(var Msg: TMessage);
var
  DC: HDC;
begin
  inherited;

  if (csDesigning in ComponentState) then
    Exit;

  if FAutoFocus then
    SetFocus;
    
  if not FMouseInControl and Enabled then
  begin
    FMouseInControl := True;
    DC := GetDC(Handle);

    DrawButton(DC);
    DrawBorders(DC);

    ReleaseDC(Handle, DC);
  end;
  if Assigned(FOnMouseEnter) then
    FOnMouseEnter(Self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  if FMouseInControl and Enabled then
  begin
    FMouseInControl := False;
    Invalidate;
  end;
  if Assigned(FOnMouseLeave) then
    FOnMouseLeave(Self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMWantSpecialKey(var Msg: TCMWantSpecialKey);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CNCtlColorEdit(var Message: TWMCtlColorEdit);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CNCtlColorStatic(var Message: TWMCtlColorStatic);
begin
  inherited;
end;

//------------------------------------------------------------------------------

constructor TDgrCustomComboBox.Create(aOwner: TComponent);
begin
  inherited;
  FDropDownListColor := clWindow;
  FAutoFocus := false;
  FMouseInControl := false;
  //FFocusFontColor:= clWindowText;
  FBorderColor := clNone;
  FBorderHotColor := clNone;
  FSelectionColor := clHighlight;
  FSelectionColorTo := clNone;
  FSelectionTextColor := clHighLightText;

  FButtonDown := false;
  FButton := TDgrComboBtn.Create;
  FButton.OnChange := ButtonOnChange;

  BevelInner := bvNone;
  BevelOuter := bvNone;
  BorderStyle := bsNone;

  ControlStyle := ControlStyle - [csSetCaption];
  Text := '';
  FOldText := '';

  FItems := TStringList.Create;
  FItems.OnChange := ItemsChanged;
  FItemIndex := -1;

  FAutoItemSize := true;

  FDroppedDown := false;
  FFlat := true;

  FFontHeight := 8;

  FRecentSelection := TStringList.Create;
  FDisplayRecentSelection := true;

  FLookUp := true;
  FWorkMode := true;

  FStyle := csDropDown;

  FAutoThemeAdapt := false;
  FOldCursor := Cursor;

  FItemHeight := LISTITEMHEIGHT;

  if not (csDesigning in ComponentState) then
  begin
    FDropDownList := TDropDownWindow.Create(Self);
    FDropDownList.Visible := False;
    FDropDownList.Width := Self.Width;
    FDropDownList.Height := 20;
    FDropDownList.Parent := Self;
    FDropDownList.BorderWidth := 1;

    FDropDownListBox := TListBox.Create(FDropDownList);

    with FDropDownListBox do
    begin
      Parent := FDropDownList;
      Align := alClient;
      Style := lbOwnerDrawFixed;
      ItemHeight := LISTITEMHEIGHT;
      Ctl3D := false;
      TabStop := true;
      BorderStyle := bsNone;
      TabOrder := 0;
      OnKeyPress := ListBoxKeyPress;
      OnKeyDown := ListBoxKeyDown;
      OnMouseUp := ListBoxMouseUp;
      OnMouseMove := ListBoxMouseMove;
      OnEnter := ListBoxOnEnter;
      OnDrawItem := DropDownOnDrawItem;
      OnChange := ListBoxChange;
    end;
    FDropDownList.ListControl := FDropDownListBox;
  end;

  FDropDownCount := 8;

  FSelectionGradient := sgVerticalInOut;

  AppearanceStyle := esOffice2003Blue;
end;

//------------------------------------------------------------------------------

destructor TDgrCustomComboBox.Destroy;
begin
  FButton.Free;
  FRecentSelection.Free;
  if not (csDesigning in ComponentState) then
  begin
    FDropDownListBox.Free;
    FDropDownList.Free;
  end;
  FItems.Free;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DoEnter;
begin
  inherited;
  SetEditRect;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.Loaded;
begin
  inherited Loaded;
  SetEditRect;

  PopulateListBox;

  if AutoThemeAdapt and not (csDesigning in ComponentState) then
    ThemeAdapt;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetBorderColor(const Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetButton(const Value: TDgrComboBtn);
begin
  if Assigned(Value) then
    FButton.Assign(Value);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetEditRect;
var
  Loc: TRect;
begin
  if csDesigning in ComponentState then
    Exit;

  {$IFNDEF TMSDOTNET}
  SendMessage(Handle, EM_GETRECT, 0, LongInt(@Loc));
  {$ENDIF}

  {$IFDEF TMSDOTNET}
  Perform(EM_GETRECT,0,Loc);
  {$ENDIF}

  Loc.Bottom := ClientHeight + 1; {+1 is workaround for windows paint bug}
  Loc.Right := ClientWidth - FButton.Width - 4;
  if (BorderStyle = bsNone) then
  begin
    Loc.Top := 2;
    Loc.Left := 4;
  end
  else
  begin
    Loc.Top := 1;
    Loc.Left := 2;
  end;
  
  {$IFNDEF TMSDOTNET}
  SendMessage(Handle, EM_SETRECTNP, 0, LongInt(@Loc));
  {$ENDIF}

  {$IFDEF TMSDOTNET}
  Perform(EM_SETRECTNP,0,Loc);
  {$ENDIF}
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetFlat(const Value: Boolean);
begin
  if (csLoading in ComponentState) then
  begin
    FFlat := Value;
    Exit;
  end;

  if FFlat <> Value then
  begin
    FFlat := Value;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetBorderHotColor(const Value: TColor);
begin
  if FBorderHotColor <> Value then
  begin
    FBorderHotColor := Value;
    Invalidate;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMEraseBkGnd(var Message: TWMEraseBkGnd);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMLButtonDown(var Msg: TWMMouse);
var
  //uchar: Integer;
  SecondDown: Boolean;
begin
  SecondDown := false;
  if FDroppedDown and Assigned(FDropDownList) and (FDropDownList.Visible) then   // CancelMode wihe DropDown on second click
    SecondDown := true;

  inherited;
  if csDesigning in ComponentState then
    Exit;

  if Style = csDropDownList then
  begin
    if not SecondDown then
      ButtonClick;
    Exit;
  end;

  if PtInRect(GetButtonRect, point(msg.xpos, msg.ypos)) then
  begin
    if not SecondDown then
      ButtonClick;
  end;

  {click outside selection}
 { uchar := CharFromPos(point(msg.xpos,msg.ypos));

  if (SelLength <= 0) or (uchar < SelStart) or (uChar > SelStart + SelLength) or
     (GetFocus <> self.Handle) then
    inherited
  else
    if (uChar >= SelStart) and (uChar <= SelStart + SelLength) and (SelLength > 0) then
      FButtonDown := True;  }
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMLButtonUp(var Msg: TWMMouse);
begin
  //if Assigned(FDropDownList) and Assigned(FDropDownListBox) and (FDropDownList.Visible) then
  //begin
  //  SetCapture(FDropDownListBox.Handle);
  //end;

  FButtonDown := false;

  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMMouseMove(var Msg: TWMMouse);
begin
  inherited;
  if Style = csDropDownList then
  begin
    if (Cursor <> crArrow) then
    begin
      FOldCursor := Cursor;
      Cursor := crArrow;
    end;
    exit;
  end;

  if PtInRect(GetButtonRect, point(msg.xpos, msg.ypos)) then
  begin
    if (Cursor <> crArrow) then
    begin
      FOldCursor := Cursor;
      Cursor := crArrow;
    end;
  end
  else if (Cursor = crArrow) then
    Cursor := FOldCursor;
end;

//------------------------------------------------------------------------------

function TDgrCustomComboBox.GetButtonRect: TRect;
var
  R: TRect;
begin
  R := ClientRect;
  Result := Rect(R.Right - FButton.Width - 1, R.Top + 1, R.Right - 1, R.Bottom - 2);
end;

function TDgrCustomComboBox.GetDropDown: boolean;
begin
  Result := FDropDownList.Visible
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DrawBorders(DC: HDC);
var
  Canvas: TCanvas;
  R, BtnR: TRect;
begin
  Canvas := TCanvas.Create;
  Canvas.Handle := DC;

  R := ClientRect;
  BtnR := GetButtonRect;

  if Flat then
  begin
    //if (FBorderColor <> clNone) or ((FMouseInControl or (Assigned(fDropDownList) and FDropDownList.Visible)) and (FBorderHotColor <> clNone)) then
    begin
      if (FMouseInControl or (GetFocus = self.Handle) or (Assigned(fDropDownList) and FDropDownList.Visible)) and (FBorderHotColor <> clNone) then
      begin
        Canvas.Pen.Color := FBorderHotColor;
        Canvas.Brush.Style := bsClear;
        Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
      end
      else
      begin
        if (FBorderColor <> clNone) then
          Canvas.Pen.Color := FBorderColor
        else
          Canvas.Pen.Color := self.Color;
        Canvas.Brush.Style := bsClear;
        Canvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
      end;
      Canvas.MoveTo(BtnR.Left - 1, BtnR.Top);
      Canvas.LineTo(BtnR.Left - 1, BtnR.Bottom + 2);
    end;
  end
  else
  begin
  end;
  Canvas.Free;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DrawButton;
var
  DC: HDC;
begin
  DC := GetDC(Handle);
  DrawButton(DC);
  ReleaseDC(Handle, DC);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DrawButton(DC: HDC);
var
  Canvas: TCanvas;
  BtnR: TRect;
  P: TPoint;
  l, t: integer;

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
  Canvas := TCanvas.Create;
  Canvas.Handle := DC;

  BtnR := GetButtonRect;

  P.X := BtnR.Left + ((BtnR.Right - BtnR.Left - 5) div 2) + 1;
  P.Y := BtnR.Top + ((BtnR.Bottom - BtnR.Top - 3) div 2) + 1;

  if Flat then
  begin
    if Assigned(FDropDownList) and FDropDownList.Visible {FDroppedDown} then
    begin
      //P.X:= P.X + 1;
      //P.Y := P.Y + 1;
      if (FButton.ColorDown <> clNone) then
        DrawGradient(Canvas, FButton.ColorDown, FButton.ColorDownTo, 16, BtnR, false);

      if not FButton.GlyphDown.Empty then
      begin
        t := ((BtnR.Bottom - BtnR.Top) - FButton.GlyphDown.Height) div 2 + 1;
        l := ((BtnR.Right - BtnR.Left) - FButton.GlyphDown.Width) div 2;
        FButton.GlyphDown.Transparent := true;
        Canvas.Draw(BtnR.Left + l, BtnR.Top + t, FButton.GlyphDown);
      end
      else
        DrawArrow(P, FButton.DownArrowColor);
    end
    else if (FMouseInControl or self.Focused) and not (csDesigning in ComponentState) then
    begin
      if FButton.ColorHot <> clNone then
        DrawGradient(Canvas, FButton.ColorHot, FButton.ColorHotTo, 16, BtnR, false);

      if not FButton.GlyphHot.Empty then
      begin
        t := ((BtnR.Bottom - BtnR.Top) - FButton.GlyphHot.Height) div 2 + 1;
        l := ((BtnR.Right - BtnR.Left) - FButton.GlyphHot.Width) div 2;
        FButton.GlyphHot.Transparent := true;
        Canvas.Draw(BtnR.Left + l, BtnR.Top + t, FButton.GlyphHot);
      end
      else
        DrawArrow(P, FButton.HotArrowColor);
    end
    else
    begin
      if FButton.Color <> clNone then
        DrawGradient(Canvas, FButton.Color, FButton.ColorTo, 16, BtnR, false);

      if not FButton.Glyph.Empty then
      begin
        t := ((BtnR.Bottom - BtnR.Top) - FButton.Glyph.Height) div 2 + 1;
        l := ((BtnR.Right - BtnR.Left) - FButton.Glyph.Width) div 2;
        FButton.Glyph.Transparent := true;
        Canvas.Draw(BtnR.Left + l, BtnR.Top + t, FButton.Glyph);
      end
      else
        DrawArrow(P, FButton.ArrowColor);
    end;
  end
  else
  begin
  end;
  Canvas.Free;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMPaint(var Msg: TWMPaint);
var
  R, BtnR: TRect;
begin
  inherited;

  R := ClientRect;
  BtnR := GetButtonRect;

  if Flat then
  begin
    // Button Painting
    DrawButton;

    // Control and Button Border
    DrawBorders();
  end
  else
  begin
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ResizeControl;
var
  MinHeight: Integer;
begin
  MinHeight := GetMinHeight;

  { text edit bug: if size to less than minheight, then edit ctrl does
    not display the text }

  if (Height < MinHeight) then
    Height := MinHeight
  else
    if (FButton <> nil) then
    begin
      SetEditRect;
    end;

  Invalidate;
end;

//------------------------------------------------------------------------------

function TDgrCustomComboBox.GetMinHeight: Integer;
var
  DC: HDC;
  SaveFont: HFont;
  I: Integer;
  SysMetrics, Metrics: TTextMetric;
begin
  DC := GetDC(0);
  GetTextMetrics(DC, SysMetrics);
  SaveFont := SelectObject(DC, Font.Handle);
  GetTextMetrics(DC, Metrics);
  SelectObject(DC, SaveFont);
  ReleaseDC(0, DC);
  I := SysMetrics.tmHeight;
  if I > Metrics.tmHeight then I := Metrics.tmHeight;
  {Result := Metrics.tmHeight + I div 4 + GetSystemMetrics(SM_CYBORDER) * 4 +2;}
  Result := Metrics.tmHeight + I div 4 {+ GetSystemMetrics(SM_CYBORDER) * 4};
end;

function TDgrCustomComboBox.GetTextEx: string;
begin
  Result := inherited Text;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMSize(var Message: TWMSize);
begin
  inherited;
  ResizeControl;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CreateWnd;
begin
  inherited CreateWnd;
  Width := Width - 1;
  Width := Width + 1;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CreateParams(var Params: TCreateParams);
begin
  inherited CreateParams(Params);
  Params.Style := Params.Style or (ES_MULTILINE);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ThemeAdapt;
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

procedure TDgrCustomComboBox.WndProc(var Message: TMessage);
begin
  if Message.Msg = WM_THEMECHANGED then
  begin
    ThemeAdapt;
  end;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetAppearanceStyle(const Value: TDgrComboStyle);
begin
  if (FAppearanceStyle <> Value) or (1 > 0) then
  begin
    FAppearanceStyle := Value;
    case FAppearanceStyle of
      esOffice2003Blue:
        begin
          //CaptionColor := $D68759;
          //CaptionColorTo := $933803;

          //CaptionFont.Color := clWhite;
          //Font.Color := clBlack;

          //ActiveColor := $94E6FB;
          //ActiveColorTo := $1595EE;

          FButton.Color := $FCE1CB;
          FButton.ColorTo := $E0A57D;

          FButton.ColorDown := $087FE8;
          FButton.ColorDownTo := $7CDAF7;

          FButton.ColorHot := $DCFFFF;
          FButton.ColorHotTo := $5BC0F7;

          FSelectionColor := $E0A57D;
          FSelectionColorTo := clNone;
          FSelectionTextColor := clWhite;          

          //SplitterColor := $D68759;
          //SplitterColorTo := $962D00;

          //BorderColor := $962D00;
          BorderColor := clNone;
          BorderHotColor := clBlack;

          //SectionColor := $FADAC4;
          //SectionColorTo := $F5BFA0;

          //DefaultGradientDirection := gdVertical;
        end;
      esOffice2003Olive:
        begin
         { CaptionColor := $82C0AF;
          CaptionColorTo := $447A63;

          CaptionFont.Color := clWhite;
          Font.Color := clBlack;

          ActiveColor := $94E6FB;
          ActiveColorTo := $1595EE;
         }
          FButton.Color := $CFF0EA;
          FButton.ColorTo := $8CC0B1;

          FButton.ColorDown := $087FE8;
          FButton.ColorDownTo := $7CDAF7;

          FButton.ColorHot := $DCFFFF;
          FButton.ColorHotTo := $5BC0F7;

          FSelectionColor := $8CC0B1;
          FSelectionColorTo := clNone;
          FSelectionTextColor := clWhite;          
         // SplitterColor := $6F8E78;
         // SplitterColorTo := $588060;

          //BorderColor := $588060;
          BorderColor := clNone;
          BorderHotColor := clBlack;

         { SectionColor := $E4F1F2;
          SectionColorTo := $AADADA;

          DefaultGradientDirection := gdVertical; }
        end;
      esOffice2003Silver:
        begin
         { CaptionColor := $BDA4A5;
          CaptionColorTo := $957475;

          CaptionFont.Color := clWhite;
          Font.Color := clBlack;

          ActiveColor := $94E6FB;
          ActiveColorTo := $1595EE;
         }
          FButton.Color := $ECE2E1;
          FButton.ColorTo := $B39698;

          FButton.ColorDown := $087FE8;
          FButton.ColorDownTo := $7CDAF7;

          FButton.ColorHot := $DCFFFF;
          FButton.ColorHotTo := $5BC0F7;

          FSelectionColor := $B39698;
          FSelectionColorTo := clNone;
          FSelectionTextColor := clWhite;
          //SplitterColor := $BFA7A8;
          //SplitterColorTo := $947C7C;

          //BorderColor := $947C7C;
          BorderColor := clNone;
          BorderHotColor := clBlack;
         {
          SectionColor := $F7F3F3;
          SectionColorTo := $E6D8D8;

          DefaultGradientDirection := gdVertical; }
        end;
      esOffice2003Classic:
        begin
         {CaptionColor := $808080;
          CaptionColorTo := $808080;

          CaptionFont.Color := clWhite;
          Font.Color := clBlack;

          ActiveColor := $D8D5D4;
          ActiveColorTo := $D8D5D4;
         }
          FButton.Color := clWhite;
          FButton.ColorTo := $C9D1D5;

          FButton.ColorDown := $B59285;
          FButton.ColorDownTo := $B59285;

          FButton.ColorHot := $D2BDB6;
          FButton.ColorHotTo := $D2BDB6;

          FSelectionColor := $B59285;
          FSelectionColorTo := clNone;
          FSelectionTextColor := clWhite;
          //SplitterColor := $C8D0D4;
          //SplitterColorTo := $8C8D8E;

          //BorderColor := $808080;
          BorderColor := clNone;
          BorderHotColor := clBlack;

         { SectionColor := $F4F5F6;
          SectionColorTo := $CAD2D6;

          DefaultGradientDirection := gdVertical;  }
        end;
      esOffice2007Luna:
        begin
          FButton.Color := $EEDBC8;
          FButton.ColorTo := $EDD4C0;

          FButton.ColorDown := $76AFF1;
          FButton.ColorDownTo := $0E72F1;

          FButton.ColorHot := $EBFDFF;
          FButton.ColorHotTo := $59DAFF;

          FSelectionColor := $EBFDFF;
          FSelectionColorTo := $69D6FF;
          FSelectionTextColor := clBlack;

          BorderColor := $E0B99B;
          BorderHotColor := $99CEDB;
        end;
      esOffice2007Obsidian:
        begin
          FButton.Color := $EBFDFF;
          FButton.ColorTo := $69D6FF;

          FButton.ColorDown := $76AFF1;
          FButton.ColorDownTo := $0E72F1;

          FButton.ColorHot := $EBFDFF;
          FButton.ColorHotTo := $59DAFF;

          FSelectionColor := $EBFDFF;
          FSelectionColorTo := $69D6FF;
          FSelectionTextColor := clBlack;

          BorderColor := $00C0BCB2;
          BorderHotColor := $99CEDB;
        end;
      esOffice2007Silver:
        begin
          FButton.Color := $F3F3F1;
          FButton.ColorTo := $F5F5F3;

          FButton.ColorDown := $76AFF1;
          FButton.ColorDownTo := $0E72F1;

          FButton.ColorHot := $EBFDFF;
          FButton.ColorHotTo := $59DAFF;

          FSelectionColor := $EBFDFF;
          FSelectionColorTo := $69D6FF;
          FSelectionTextColor := clBlack;

          BorderColor := $CCCAC9;
          BorderHotColor := $99CEDB;
        end;
      esWhidbey:
        begin
          FButton.Color := clWhite;
          FButton.ColorTo := $DFEDF0;

          FButton.ColorDown := $087FE8;
          FButton.ColorDownTo := $7CDAF7;

          FButton.ColorHot := $DCFFFF;
          FButton.ColorHotTo := $5BC0F7;

          FSelectionColor := $E0A57D;
          FSelectionColorTo := clNone;
          FSelectionTextColor := clWhite;

          BorderColor := clNone;
          BorderHotColor := clBlack;
        end;
      esWindowsXP:
        begin
          FButton.Color := clWhite;
          FButton.ColorTo := $B9D8DC;

          FButton.ColorDown := $B59284;
          FButton.ColorDownTo := $B59284;

          FButton.ColorHot := $EFD3C6;
          FButton.ColorHotTo := $EFD3C6;

          FSelectionColor := clHighlight;
          FSelectionColorTo := clNone;
          FSelectionTextColor := clWhite;

          BorderColor := clNone;
          BorderHotColor := $00E0B99B;
        end;
    end;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMEnter(var Message: TCMGotFocus);
begin
  inherited;
  DrawBorders;
  PopulateListbox;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMExit(var Message: TCMExit);
begin
  inherited;
  //inherited Text := FOldText;
  DrawButton;
  DrawBorders;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DrawBorders;
var
  DC: HDC;
begin
  DC := GetDC(Handle);
  DrawBorders(DC);
  ReleaseDC(Handle, DC);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ButtonClick;
begin
  ShowDropDown;
end;

procedure TDgrCustomComboBox.PopulateListBox;
var
  i: integer;
begin
  if Assigned(FDropDownListBox) then
  begin

    FDropDownListBox.Items.Clear;

    if FDisplayRecentSelection then
      for i := min(FRecentSelection.Count - 1, DropDownCount - 1) downto 0 do
        FDropDownListBox.Items.Add(FRecentSelection[i]);

    for i := 0 to Items.Count - 1 do
      FDropDownListBox.Items.Add(Items[i]);

    //FDropDownListBox.Items.Assign(FItems);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ShowDropDown;
var
  P: TPoint;
  i, MinTW: integer;
  R: TRect;
  cnt,rec: integer;
begin
  if not Assigned(FDropDownList) then
    Exit;

  if FDropDownList.Visible then
  begin
    HideDropDown;
    Exit;
  end;

  if not FDropDownList.Visible then
    BeforeDropDown;

  {$IFNDEF TMSDOTNET}
  SystemParametersInfo(SPI_GETWORKAREA, 0, @r, 0);
  {$ENDIF}
  {$IFDEF TMSDOTNET}
  SystemParametersInfo(SPI_GETWORKAREA, 0, r, 0);
  {$ENDIF}

{
  P:= Point(0, self.Height);
  P:= ClientToScreen(P);
  if R.Bottom < (P.Y + FDropDownList.Height + 4) then
  FDropDownList.Left:=  P.X - 2;
  FDropDownList.Top:= P.Y;
}
  FDropDownListBox.ItemHeight := GetListItemHeight;

  if DisplayRecentSelection then
    rec := RecentSelection.Count
  else
    rec := 0;

  if FItems.Count + rec < FDropDownCount then
  begin
    cnt := FItems.Count + rec;
    FDropDownList.Height := Max(16, ((cnt * GetListItemHeight)) + 4);
  end
  else
  begin
    FDropDownList.Height := Max(16, (FDropDownCount * GetListItemHeight) + 4);
  end;

  P := Point(0, self.Height);
  P := ClientToScreen(P);

  if R.Bottom > (P.Y + FDropDownList.Height + 4) then
  begin
    FDropDownList.Left := P.X {- 2};
    FDropDownList.Top := P.Y;
  end
  else
  begin
    FDropDownList.Left := P.X {- 1};
    FDropDownList.Top := P.Y - self.Height - FDropDownList.Height;
  end;

  FDropDownListBox.Font.Size := FontHeight;
  FDropDownListBox.Font.Color := Font.Color;
  FDropDownListBox.Color := Color;

  PopulateListBox;

  i := FDropDownListBox.Items.IndexOf(self.Text);
  if (i >= 0) then
    FDropDownListBox.ItemIndex := i
  else
    FDropDownListBox.ItemIndex := 0;

  //FItemIndex:= FDropDownListBox.ItemIndex;

  MinTW := self.Width;
  for i := 0 to FDropDownListBox.Items.Count - 1 do
  begin
    MinTW := Max(MinTW, FDropDownList.Canvas.TextWidth(FDropDownListBox.Items[i]));
  end;

  if MinTW > self.Width + 1 then
    FDropDownList.Width := MinTW + 24 //GetSystemMetrics(SM_CXHSCROLL)
  else
    FDropDownList.Width := MinTW;
    
  FDropDownList.Color := DropDownListColor;
  FDropDownList.ListControl.Color := DropDownListColor;
  FDropDownList.Visible := true;
  FDroppedDown := true;

  DoDropDown;

  SendMessage(Handle, EM_SETSEL, 0, Length(Text));
  Invalidate;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.HideDropDown;
begin
  //if Assigned(FDropDownListBox) and (GetCapture = FDropDownListBox.Handle) then
  //  ReleaseCapture;
  FDropDownList.Visible := false;
  FDroppedDown := false;
  Invalidate;
  DoCloseUp;
end;

procedure TDgrCustomComboBox.ItemsChanged(Sender: TObject);
var
  i: integer;
begin
  //
  for i := FRecentSelection.Count - 1 downto 0 do
  begin
    if FItems.IndexOf(FRecentSelection.Strings[i]) = - 1 then
      FRecentSelection.Delete(i);
  end;

  if Assigned(FDropDownList) then
    if Assigned(FDropDownListBox) then
      for i := FDropDownListBox.Items.Count - 1 downto 0 do
      begin
        if FItems.IndexOf(FDropDownListBox.Items[i]) = - 1 then
          FDropDownListBox.Items.Delete(i);
      end;

  if FItems.IndexOf(Text) = -1 then
    Text := '';
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.CMCancelMode(var Message: TMessage);
begin
  inherited;
  if FDropDownList.Visible then
    HideDropDown;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMKillFocus(var Msg: TWMKillFocus);
begin
  if (csLoading in ComponentState) then
    Exit;

  if FDropDownList.Visible and not (msg.FocusedWnd = FDropDownList.Handle) then
    HideDropDown;

  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMSetFocus(var Msg: TWMSetFocus);
begin
  if csLoading in ComponentState then
    Exit;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ListBoxKeyPress(Sender: TObject;
  var Key: Char);
begin
{
  case Key of
    #27:
    begin
      Text:= FOldText;
      if FDropDownList.Visible then
      begin
        HideDropDown;
      end;
    end;
    #13:
    begin
      if (Items.IndexOf(Text)<>-1) then
      begin
        text:= Items.Strings[Items.IndexOf(Text)];
        self.Change;
        ValueChanged;
        if FDropDownList.Visible then
          HideDropDown;
      end;
    end;
  end;      }
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ListBoxMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  i: integer;
begin
  // selection End

  i := TListBox(Sender).ItemAtPos(Point(X, Y), true);

  HideDropDown;
  Self.SetFocus;

  if i >= 0 then
  begin
    i := FItems.IndexOf(TListBox(Sender).Items[i]);
    self.ItemIndex := i;
    DoSelect;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetItems(const Value: TStringList);
begin
  if Assigned(Value) then
    FItems.Assign(Value);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DropDownOnDrawItem(Control: TWinControl;
  Index: Integer; Rect: TRect; State: TOwnerDrawState);
var
  r: TRect;
begin
  TListBox(Control).Canvas.Font.Assign(font);
  if (State = [odSelected]) or (State = [odFocused]) or (State = [odSelected, odFocused]) then
  begin
    TListBox(Control).Canvas.Brush.Color := SelectionColor;
    TListBox(Control).Canvas.Font.Color := FSelectionTextColor;
  end;

  if (FSelectionColorTo <> clNone) and ((State = [odSelected]) or (State = [odFocused]) or (State = [odSelected, odFocused])) then
  begin
    case SelectionGradient of
      sgVertical:
        begin
          R := Rect;
          R.Bottom := R.Bottom - 1;
        //R.Bottom:= R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 16, R, false);
        end;
      sgHorizontal:
        begin
          R := Rect;
          R.Right := R.Right - 1;
        //R.Bottom:= R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 40, R, true);
        end;
      sgVerticalInOut:
        begin
          R := Rect;
          R.Bottom := R.Bottom - 1;
          R.Bottom := R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 16, R, false);

          R := Rect;
          R.Bottom := R.Bottom - 1;
          R.Top := R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColorTo, FSelectionColor, 16, R, false);
        end;
      sgHorizontalInOut:
        begin
          R := Rect;
          R.Right := R.Right - 1;
          R.Right := R.Left + (R.Right - R.Left) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 40, R, true);

          R := Rect;
          R.Right := R.Right - 1;
          R.Left := R.Left + (R.Right - R.Left) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColorTo, FSelectionColor, 40, R, true);
        end;
    end;
  end
  else
    TListBox(Control).Canvas.FillRect(Rect);

  TListBox(Control).Canvas.Brush.Style := bsClear;

  //TListBox(Control).Canvas.Draw(Rect.Left + 2, Rect.Top + 2, FFontGlyph);
  Rect.Left := Rect.Left + 4;

  if FDisplayRecentSelection and (Index = FRecentSelection.Count - 1) then
  begin
    Rect.Bottom := Rect.Bottom - 3;
  end;

  {$IFNDEF TMSDOTNET}
    {$IFDEF DELPHI2009_LVL}
    DrawText(TListBox(Control).Canvas.Handle, TListBox(Control).Items[Index], -1, Rect, DT_SINGLELINE or DT_VCENTER);
    {$ELSE}
    DrawText(TListBox(Control).Canvas.Handle, PChar(TListBox(Control).Items[Index]), -1, Rect, DT_SINGLELINE or DT_VCENTER);
    {$ENDIF}
  {$ENDIF}

  {$IFDEF TMSDOTNET}
  DrawText(TListBox(Control).Canvas.Handle, TListBox(Control).Items[Index], -1, Rect, DT_SINGLELINE or DT_VCENTER);
  {$ENDIF}

  if FDisplayRecentSelection and (Index = FRecentSelection.Count - 1) then
  begin
    Rect.Bottom := Rect.Bottom + 3;
    TListBox(Control).Canvas.Pen.Color := clGray;
    TListBox(Control).Canvas.MoveTo(1, Rect.Bottom - 3);
    TListBox(Control).Canvas.LineTo(TListBox(Control).Width - 1, Rect.bottom - 3);

    TListBox(Control).Canvas.MoveTo(1, Rect.Bottom - 1);
    TListBox(Control).Canvas.LineTo(TListBox(Control).Width - 1, Rect.bottom - 1);
  end;

 // TListBox(Control).Canvas.Font.Assign(Self.Font);
{  TListBox(Control).Canvas.FillRect(Rect);
  TListBox(Control).Canvas.Brush.Style:= bsClear;
  TListBox(Control).Canvas.TextOut(Rect.Left + 2, Rect.Top, Items[Index]); }
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.BeforeDropDown;
begin
  if Assigned(FOnBeforeDropDown) then
    FOnBeforeDropDown(self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DoDropDown;
begin
  if Assigned(FOnDropDown) then
    FOnDropDown(Self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DoCloseUp;
begin
  if Assigned(FOnCloseUp) then
    FOnCloseUp(Self);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.DoSelect;
begin
  if Assigned(FOnSelect) then
    FOnSelect(Self);
end;

procedure TDgrCustomComboBox.ListBoxMouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
var
  i: integer;
begin
  // Hot selection
  i := TListBox(Sender).ItemAtPos(Point(X, Y), true);
  if (i >= 0) and (i <> TListBox(Sender).ItemIndex) then
    TListBox(Sender).ItemIndex := i;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetItemIndex(const Value: integer);
begin
  if FItems.Count <= 0 then
  begin
    FItemIndex := -1;
    Exit;
  end;

  if (Value >= -1) and (Value < FItems.Count) then
  begin
    FItemIndex := Value;
    if (Value >= 0) then
      inherited Text := FItems[FItemIndex]
    else
      inherited Text := '';
    if Assigned(FDropDownList) {and FDropDownList.Visible} then
      if Assigned(FDropDownListBox) then
      begin
        if (Value >= 0) then
          FDropDownListBox.ItemIndex := FDropDownListBox.Items.IndexOf(FItems[FItemIndex])
        else
          FDropDownListBox.ItemIndex := -1;
      end;
    ValueChanged;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetSelectionColor(const Value: TColor);
begin
  if FSelectionColor <> Value then
  begin
    FSelectionColor := Value;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetFontHeight(const Value: integer);
begin
  FFontHeight := Value;
end;

//------------------------------------------------------------------------------

function TDgrCustomComboBox.GetListItemHeight: integer;
var
  OlfFontName: string;
begin
  //Result:= LISTITEMHEIGHT;
  if Assigned(FDropDownListBox) and FAutoItemSize then
  begin
    OlfFontName := FDropDownListBox.Canvas.Font.Name;
    FDropDownListBox.Canvas.Font.Name := 'Tahoma';
    FDropDownListBox.Canvas.Font.Size := FFontHeight;
    Result := Max(LISTITEMHEIGHT, FDropDownListBox.Canvas.TextHeight('gh'));
    FDropDownListBox.Canvas.Font.Name := OlfFontName;
  end
  else
    Result := FItemHeight;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetLookUp(const Value: Boolean);
begin
  FLookUp := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.LookUpText;
var
  c: string;
  i: integer;
  UsrStr, AutoAdd: string;
begin
  if csDesigning in ComponentState then
    Exit;

  if not FLookUp then
    Exit;

  if not FWorkMode then
    Exit;

  c := upstr(Text, fMatchCase);
  c := copy(c, 1, selstart);

  if (Items.Count > 0) then
    for i := 0 to Items.count - 1 do
    begin
      if pos(c, upstr(Items.Strings[i], fMatchCase)) = 1 then
      begin
        UsrStr := copy(text, 1, length(c));
        AutoAdd := copy(Items.Strings[i], length(c) + 1, 255);

        if Assigned(FDropDownListBox) {and FDropDownList.Visible} then
        begin
          FDropDownListBox.ItemIndex := FDropDownListBox.Items.IndexOf(Items.Strings[i]);
        end;
        inherited Text := UsrStr + AutoAdd;
       //Modified := True;
        SendMessage(Handle, EM_SETSEL, length(c), length(text));
        Exit;
      end;
    end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.KeyUp(var Key: Word; Shift: TShiftState);
begin
  if FChanged and LookUp and not (key in [vk_back, vk_delete]) then
    LookupText;

  UpdateIndex;
  FChanged := False;

  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.Change;
begin
  inherited;
  FChanged := true;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.KeyDown(var Key: Word; Shift: TShiftState);
begin
  case Key of
    vk_back, vk_delete: FWorkMode := false;
    vk_return:
      begin
        //if (Items.IndexOf(Text) <> -1) then
        begin
          if (Items.IndexOf(Text) > -1) then 
            inherited Text := Items.Strings[Items.IndexOf(Text)];
          self.Change;
          ValueChanged;
          if FDropDownList.Visible then
            HideDropDown;
        end;
      end;
    VK_F4:
      begin
        if (GetKeyState(VK_MENU) and $8000 = 0) then
          ShowDropDown;
      end;
    VK_UP: Previous;
    VK_DOWN:
      begin
        if (ssAlt in Shift) then
          ShowDropDown
        else
          Next;
      end;
    VK_PRIOR: PageJump(false);
    VK_NEXT: PageJump(true);
    VK_ESCAPE:
      begin
        inherited Text := FOldText;
        if FDropDownList.Visible then
        begin
          HideDropDown;
          Self.SetFocus;
        end;
      end;
  else
    FWorkMode := true;
  end;
  inherited KeyDown(key, shift);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.WMChar(var Msg: TWMKey);
var
  key: Char;
  i: integer;
  str: string;
begin

  if Msg.CharCode = VK_RETURN then
  begin
    key := #13;
    if Assigned(OnKeyPress) then
      OnKeyPress(Self, key);

    Msg.CharCode := 0;
    if (Items.IndexOf(Text) <> -1) then
    begin
      inherited Text := Items.Strings[Items.IndexOf(Text)];
      SendMessage(Handle, EM_SETSEL, 0, 0);
      self.Change;
      ValueChanged;
      if FDropDownList.Visible then
        HideDropDown;

      //if Assigned(OnSelect) then
      //  OnSelect(Self);

    end;
    Exit;
  end;

  if (Style = csDropDownlist) then
  begin
    if (Msg.CharCode <> 8) then
    begin
      str := Uppercase(Chr(Msg.CharCode));

      if (Items.Count > 0) then
        for i := 0 to Items.count - 1 do
        begin
          if pos(str, upstr(Items.Strings[i], fMatchCase)) = 1 then
          begin
            if Assigned(FDropDownListBox) and FDropDownList.Visible then
            begin
              FDropDownListBox.ItemIndex := FDropDownListBox.Items.IndexOf(Items.Strings[i]);
            end;
            FItemIndex := i;
            inherited Text := Items.Strings[i];
            SelStart := 0;
            SelLength := Length(Text);
            break;
          end;
        end;
    end;
  end;

  inherited;

end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.UpdateIndex;
begin
  FItemIndex := FItems.IndexOf(Text);
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ValueChanged;
begin
  FOldText := Text;

  FItemIndex := FItems.IndexOf(Text);
  
  if Items.IndexOf(Text) >= 0 then
  begin
    //FItemIndex := FItems.IndexOf(Text);

    if csLoading in ComponentState then
      Exit;

    if FRecentSelection.IndexOf(Text) >= 0 then
      FRecentSelection.Delete(FRecentSelection.IndexOf(Text));

    if (FRecentSelection.Count > 0) and (FRecentSelection.Count > DropDownCount - 2) then
      while (FRecentSelection.Count > DropDownCount - 2) do
        FRecentSelection.Delete(0);

    if FRecentSelection.IndexOf(Text) < 0 then
      FRecentSelection.Add(Text);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.First;
begin
  if Assigned(FDropDownListBox) and (FDropDownListBox.Items.Count > 0) then
  begin
    FDropDownListBox.ItemIndex := 0;
    Text := FDropDownListBox.Items[FDropDownListBox.ItemIndex];
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.Last;
begin
  if Assigned(FDropDownListBox) and (FDropDownListBox.Items.Count > 0) then
  begin
    FDropDownListBox.ItemIndex := FDropDownListBox.Items.Count - 1;
    Text := FDropDownListBox.Items[FDropDownListBox.ItemIndex];
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.Next;
begin
  if Assigned(FDropDownListBox) and (FDropDownListBox.ItemIndex < FDropDownListBox.Items.Count - 1) then
  begin
    FDropDownListBox.ItemIndex := FDropDownListBox.ItemIndex + 1;
    ItemIndex := FDropDownListBox.ItemIndex;
    Text := FDropDownListBox.Items[FDropDownListBox.ItemIndex];
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.Previous;
begin
  if Assigned(FDropDownListBox) and (FDropDownListBox.Items.Count > 0) and (FDropDownListBox.ItemIndex > 0) then
  begin
    FDropDownListBox.ItemIndex := FDropDownListBox.ItemIndex - 1;
    ItemIndex := FDropDownListBox.ItemIndex;
    Text := FDropDownListBox.Items[FDropDownListBox.ItemIndex];
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.PageJump(GoForward: Boolean);
var
  ItemsToBeJumpped: integer;
begin
  if Assigned(FDropDownListBox) then
  begin
    ItemsToBeJumpped := DropDownCount - 1;
    if GoForward then
    begin
      if (FDropDownListBox.ItemIndex < FDropDownListBox.Items.Count - 1) then
      begin
        FDropDownListBox.ItemIndex := FDropDownListBox.ItemIndex + min(FDropDownListBox.Items.Count - 1 - FDropDownListBox.ItemIndex, ItemsToBeJumpped);
        ItemIndex := FDropDownListBox.ItemIndex;
        Text := FDropDownListBox.Items[FDropDownListBox.ItemIndex];
      end;
    end
    else
    begin
      if (FDropDownListBox.Items.Count > 0) and (FDropDownListBox.ItemIndex > 0) then
      begin
        FDropDownListBox.ItemIndex := FDropDownListBox.ItemIndex - min(FDropDownListBox.ItemIndex, ItemsToBeJumpped);
        ItemIndex := FDropDownListBox.ItemIndex;
        Text := FDropDownListBox.Items[FDropDownListBox.ItemIndex];
      end;
    end;
  end;
end;

//------------------------------------------------------------------------------

function TDgrCustomComboBox.GetItemIndex: integer;
begin
  Result := FItemIndex; // FItems.IndexOf(Text);
  //FItemIndex:= Result;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetSelectionColorTo(const Value: TColor);
begin
  FSelectionColorTo := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetSelectionGradient(const Value: TSelectionGradient);
begin
  FSelectionGradient := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ListBoxOnEnter(Sender: TObject);
begin
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ListBoxChange(Sender: TObject);
begin
  DoSelect;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.ListBoxKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  FDropDownList.HideOnDeActivate := false;
  SendMessage(self.Handle, WM_KEYDOWN, Key, 0);
  SendMessage(self.Handle, WM_KEYUP, Key, 0);
  FDropDownList.HideOnDeActivate := true;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetDisplayRecentSelection(
  const Value: Boolean);
begin
  FDisplayRecentSelection := Value;
end;

procedure TDgrCustomComboBox.SetDropDown(const Value: boolean);
begin
  if Value then 
    ShowDropDown
  else
    HideDropDown;  
end;

//------------------------------------------------------------------------------

function TDgrCustomComboBox.GetItemHeight: integer;
begin
  Result := FItemHeight;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetItemHeight(const Value: integer);
begin
  FItemHeight := Value;
end;

//------------------------------------------------------------------------------

procedure TDgrCustomComboBox.SetStyle(const Value: TComboStyle);
begin
  if Value <> FStyle then
  begin
    FStyle := Value;
    self.ReadOnly := FStyle = csDropDownList;
  end;
end;

procedure TDgrCustomComboBox.SetTextEx(const Value: string);
begin
  inherited Text := Value;
  FOldText := Value;
end;

procedure TDgrCustomComboBox.SetAutoItemSize(const Value: boolean);
begin
  FAutoItemSize := Value;
end;

function TDgrCustomComboBox.GetVersion: string;
var
  vn: Integer;
begin
  vn := GetVersionNr;
  Result := IntToStr(Hi(Hiword(vn)))+'.'+IntToStr(Lo(Hiword(vn)))+'.'+IntToStr(Hi(Loword(vn)))+'.'+IntToStr(Lo(Loword(vn)));
end;

function TDgrCustomComboBox.GetVersionNr: Integer;
begin
  Result := MakeLong(MakeWord(BLD_VER, REL_VER),MakeWord(MIN_VER,MAJ_VER));
end;

procedure TDgrCustomComboBox.SetVersion(const Value: string);
begin

end;

{ TDgrComboBtn }

procedure TDgrComboBtn.Assign(Source: TPersistent);
begin
  if Source is TDgrComboBtn then
  begin
    FColor := TDgrComboBtn(Source).Color;
    FColorTo := TDgrComboBtn(Source).ColorTo;
    FColorHot := TDgrComboBtn(Source).ColorHot;
    FColorHotTo := TDgrComboBtn(Source).ColorHotTo;
    FColorDown := TDgrComboBtn(Source).ColorDown;
    FColorDownTo := TDgrComboBtn(Source).ColorDownTo;

    FGlyph.Assign(TDgrComboBtn(Source).Glyph);
    FGlyphHot.Assign(TDgrComboBtn(Source).GlyphHot);
    FGlyphDown.Assign(TDgrComboBtn(Source).GlyphDown);
    FWidth := TDgrComboBtn(Source).Width;

    inherited Assign(Source);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.Change;
begin
  if assigned(FOnChange) then
    FOnChange(self);
end;

//------------------------------------------------------------------------------

constructor TDgrComboBtn.Create;
begin
  inherited;
  FColor := clBtnFace;
  FColorTo := clBtnFace;
  FColorHot := clBtnFace;
  FColorHotTo := clBtnFace;
  FColorDown := clBtnFace;
  FColorDownTo := clBtnFace;

  FArrowColor := clBlack;
  FHotArrowColor := clBlack;
  FDownArrowColor := clWhite;

  FGlyph := TBitMap.Create;
  FGlyphHot := TBitMap.Create;
  FGlyphDown := TBitMap.Create;
  FWidth := 12;
end;

//------------------------------------------------------------------------------

destructor TDgrComboBtn.Destroy;
begin
  FGlyph.Free;
  FGlyphHot.Free;
  FGlyphDown.Free;
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetArrowColor(const Value: TColor);
begin
  if FArrowColor <> Value then
  begin
    FArrowColor := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetColor(const Value: TColor);
begin
  if FColor <> Value then
  begin
    FColor := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetColorTo(const Value: TColor);
begin
  if FColorTo <> Value then
  begin
    FColorTo := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetDownArrowColor(const Value: TColor);
begin
  if Value <> FDownArrowColor then
  begin
    FDownArrowColor := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetColorDown(const Value: TColor);
begin
  if FColorDown <> Value then
  begin
    FColorDown := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetColorDownTo(const Value: TColor);
begin
  if FColorDownTo <> Value then
  begin
    FColorDownTo := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetGlyphDown(const Value: TBitMap);
begin
  FGlyphDown.Assign(Value);
  Change;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetGlyph(const Value: TBitMap);
begin
  FGlyph.Assign(Value);
  Change;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetHotArrowColor(const Value: TColor);
begin
  if Value <> FHotArrowColor then
  begin
    FHotArrowColor := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetColorHot(const Value: TColor);
begin
  if FColorHot <> Value then
  begin
    FColorHot := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetColorHotTo(const Value: TColor);
begin
  if FColorHotTo <> Value then
  begin
    FColorHotTo := Value;
    Change;
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetGlyphHot(const Value: TBitMap);
begin
  FGlyphHot.Assign(Value);
  Change;
end;

//------------------------------------------------------------------------------

procedure TDgrComboBtn.SetWidth(const Value: integer);
begin
  if (FWidth <> Value) and (Value >= 0) then
  begin
    FWidth := Value;
    if Assigned(Combo) then
      Combo.SetEditRect;
    Change;
  end;
end;

//------------------------------------------------------------------------------

{ TDropDownWindow }

constructor TDropDownWindow.Create(AOwner: TComponent);
begin
  inherited;
  FHideOnDeActivate := true;
end;

//------------------------------------------------------------------------------

procedure TDropDownWindow.CreateParams(var Params: TCreateParams);
const
  CS_DROPSHADOW = $00020000;
begin
  inherited CreateParams(Params);
  //Params.Style := Params.Style + WS_BORDER;

  if (Win32Platform = VER_PLATFORM_WIN32_NT) and
    ((Win32MajorVersion > 5) or
    ((Win32MajorVersion = 5) and (Win32MinorVersion >= 1))) then
    Params.WindowClass.Style := Params.WindowClass.Style or CS_DROPSHADOW;

  if (Win32Platform = VER_PLATFORM_WIN32_NT) then // not for Win9x
    Params.ExStyle := Params.ExStyle or WS_EX_TOPMOST;
end;

//------------------------------------------------------------------------------

destructor TDropDownWindow.Destroy;
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDropDownWindow.WMActivate(var Message: TMessage);
begin
  inherited;
  if Message.WParam = WPARAM(false) then
  begin
    if HideOnDeActivate then
      Hide;
  end
  else if Assigned(FListControl) then
    if Visible then
      FListControl.SetFocus
    else
      self.Parent.SetFocus;
end;

//------------------------------------------------------------------------------

procedure TDropDownWindow.WMNCButtonDown(var Message: TMessage);
begin
  inherited;
end;

//------------------------------------------------------------------------------

procedure TDropDownWindow.WMNCHitTest(var Message: TWMNCHitTest);
var
  pt: TPoint;
begin
  // Make the hint sizable
  pt := ScreenToClient(Point(Message.XPos, Message.YPos));

  if (pt.X > Width - 10) and (pt.Y > Height - 10) then
    message.Result := HTBOTTOMRIGHT
end;

{ TDgrBaseComboBox }

procedure TDgrBaseComboBox.DiagramChanged;
begin
end;

procedure TDgrBaseComboBox.Notification(AComponent: TComponent;
  AOperation: TOperation);
begin
  inherited;
  if (AOperation = opRemove) and (AComponent = Diagram) then
    Diagram := nil;
end;

procedure TDgrBaseComboBox.SetDiagram(const Value: TatDiagram);
begin
  if FDiagram <> Value then
  begin
    FDiagram := Value;
    if Value <> nil then Value.FreeNotification(Self);
    DiagramChanged;
  end;
end;

//------------------------------------------------------------------------------

{ TDgrFontSelector }

procedure TDgrFontSelector.BeforeDropDown;
begin
  inherited;

  if FFontGlyphTT.Empty and not (csDesigning in ComponentState) then
  begin
    FFontGlyphTT.LoadFromResourceName(Hinstance, 'TMSDGRFONT');
    FFontGlyphTT.Transparent := true;
  end;
  if FFontGlyphPS.Empty and not (csDesigning in ComponentState) then
  begin
    FFontGlyphPS.LoadFromResourceName(Hinstance, 'TMSDGRFONTPS');
    FFontGlyphPS.Transparent := true;
  end;
  if FFontGlyphPRN.Empty and not (csDesigning in ComponentState) then
  begin
    FFontGlyphPRN.LoadFromResourceName(Hinstance, 'TMSDGRFONTPRN');
    FFontGlyphPRN.Transparent := true;
  end;
  if FFontGlyphBMP.Empty and not (csDesigning in ComponentState) then
  begin
    FFontGlyphBMP.LoadFromResourceName(Hinstance, 'TMSDGRFONTBMP');
    FFontGlyphBMP.Transparent := true;
  end;

  //LoadFontNames;
end;

//------------------------------------------------------------------------------

procedure TDgrFontSelector.CMTextChanged(var Message: TMessage);
begin
  inherited;
end;

//------------------------------------------------------------------------------

constructor TDgrFontSelector.Create(aOwner: TComponent);
begin
  inherited;
  FFontGlyphTT := TBitMap.Create;
  FFontGlyphTT.LoadFromResourceName(Hinstance, 'TMSDGRFONT');
  FFontGlyphTT.Transparent := true;

  FFontGlyphPS := TBitMap.Create;
  FFontGlyphPS.LoadFromResourceName(Hinstance, 'TMSDGRFONTPS');
  FFontGlyphPS.Transparent := true;

  FFontGlyphPRN := TBitMap.Create;
  FFontGlyphPRN.LoadFromResourceName(Hinstance, 'TMSDGRFONTPRN');
  FFontGlyphPRN.Transparent := true;

  FFontGlyphBMP := TBitMap.Create;
  FFontGlyphBMP.LoadFromResourceName(Hinstance, 'TMSDGRFONTBMP');
  FFontGlyphBMP.Transparent := true;

  FShowFontStyle := True;
  FShowFontGlyph := True;

  FFontHeight := 12;

  FAllowedFontTypes := [aftBitmap, aftTrueType, aftPostScript, aftPrinter, aftFixedPitch, aftProportional];

  //FRecentSelection:= TStringList.Create;
  //FDisplayRecentSelection:= true;
end;

procedure TDgrFontSelector.CreateWnd;
begin
  inherited;
  LoadFontNames;
end;

//------------------------------------------------------------------------------

destructor TDgrFontSelector.Destroy;
begin
  FFontGlyphBMP.Free;
  FFontGlyphPRN.Free;
  FFontGlyphPS.Free;
  FFontGlyphTT.Free;
  //FRecentSelection.Free;
  inherited;
end;

//------------------------------------------------------------------------------

function TDgrFontSelector.GetFontType(const Fontname: string): TDgrFontTypes;
var
  tm : TTextMetric;
begin
  Result := [aftTrueType, aftProportional];

  if (csLoading in ComponentState) then
    Exit;
  if not Assigned(FDropDownListBox) then
    Exit;

  FDropDownListBox.Canvas.Font.Name := FontName;
  FDropDownListBox.Canvas.Font.Style := [];

  GetTextMetrics(FDropDownListBox.Canvas.Handle, tm);

  Result := [aftBitmap];
  if ((tm.tmPitchAndFamily AND TMPF_VECTOR) = TMPF_VECTOR) then
  begin
    if ((tm.tmPitchAndFamily AND TMPF_DEVICE) = TMPF_DEVICE) then
    begin
      Result := [aftPostScript];
    end
    else
    begin
      Result := [aftTrueType];
    end;
  end
  else
  begin
    if ((tm.tmPitchAndFamily AND TMPF_DEVICE) = TMPF_DEVICE) then
    begin
      Result := [aftPrinter];
    end;
  end;
  if ((tm.tmPitchAndFamily AND TMPF_FIXED_PITCH) = TMPF_FIXED_PITCH) then
    Result := Result + [aftProportional]
  else
    Result := Result + [aftFixedPitch];
end;

procedure TDgrFontSelector.DropDownOnDrawItem(Control: TWinControl;
  Index: Integer; Rect: TRect; State: TOwnerDrawState);
var
  r: TRect;
  aft : TDgrFontType;
  tm : TTextMetric;
begin
//   TDgrFontType = (aftBitmap, aftTrueType, aftPostScript, aftPrinter);

  TListBox(Control).Canvas.Font.Name := TListBox(Control).Items[Index];
  TListBox(Control).Canvas.Font.Style := [];

  GetTextMetrics(TListBox(Control).Canvas.Handle, tm);

  aft := aftBitmap;
  if ((tm.tmPitchAndFamily AND TMPF_VECTOR) = TMPF_VECTOR) then
  begin
    if ((tm.tmPitchAndFamily AND TMPF_DEVICE) = TMPF_DEVICE) then
    begin
      aft := aftPostScript;
    end
    else
    begin
      aft := aftTrueType;
    end;
  end
  else
  begin
    if ((tm.tmPitchAndFamily AND TMPF_DEVICE) = TMPF_DEVICE) then
    begin
      aft := aftPrinter;
    end;
  end;

  if not FShowFontStyle or (tm.tmCharSet <> ANSI_CHARSET) then
  begin
    TListBox(Control).Canvas.Font.Name := Font.Name;
    TListBox(Control).Canvas.Font.Size := Font.Size;
  end;


  if (State = [odSelected]) or (State = [odFocused]) or (State = [odSelected, odFocused]) then
  begin
    TListBox(Control).Canvas.Brush.Color := SelectionColor;
    TListBox(Control).Canvas.Font.Color := FSelectionTextColor;
  end;

  if (FSelectionColorTo <> clNone) and ((State = [odSelected]) or (State = [odFocused]) or (State = [odSelected, odFocused])) then
  begin
    case SelectionGradient of
      sgVertical:
        begin
          R := Rect;
          R.Bottom := R.Bottom - 1;
        //R.Bottom:= R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 16, R, false);
        end;
      sgHorizontal:
        begin
          R := Rect;
          R.Right := R.Right - 1;
        //R.Bottom:= R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 40, R, true);
        end;
      sgVerticalInOut:
        begin
          R := Rect;
          R.Bottom := R.Bottom - 1;
          R.Bottom := R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 16, R, false);

          R := Rect;
          R.Bottom := R.Bottom - 1;
          R.Top := R.Top + (R.Bottom - R.top) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColorTo, FSelectionColor, 16, R, false);
        end;
      sgHorizontalInOut:
        begin
          R := Rect;
          R.Right := R.Right - 1;
          R.Right := R.Left + (R.Right - R.Left) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColor, FSelectionColorTo, 40, R, true);

          R := Rect;
          R.Right := R.Right - 1;
          R.Left := R.Left + (R.Right - R.Left) div 2;
          DrawGradient(TListBox(Control).Canvas, FSelectionColorTo, FSelectionColor, 40, R, true);
        end;
    end;
  end
  else
    TListBox(Control).Canvas.FillRect(Rect);

  TListBox(Control).Canvas.Brush.Style := bsClear;
  //TListBox(Control).Canvas.TextOut(Rect.Left + 2, Rect.Top, Items[Index]);
  //DrawIcon(TListBox(Control).Canvas.Handle,Rect.Left+2,Rect.Top+1, FFontGlyph. .Handle);

  if FShowFontGlyph then
  begin
    case aft of
       aftTrueType   : TListBox(Control).Canvas.Draw(Rect.Left + 2, Rect.Top + 2, FFontGlyphTT);
       aftPostScript : TListBox(Control).Canvas.Draw(Rect.Left + 2, Rect.Top + 2, FFontGlyphPS);
       aftPrinter    : TListBox(Control).Canvas.Draw(Rect.Left + 2, Rect.Top + 2, FFontGlyphPRN);
       aftBitmap     : TListBox(Control).Canvas.Draw(Rect.Left + 2, Rect.Top + 2, FFontGlyphBMP);
    end;
    Rect.Left := Rect.Left + 16;
  end;

  Rect.Left := Rect.Left + 4;

  if FDisplayRecentSelection and (Index = FRecentSelection.Count - 1) then
  begin
    Rect.Bottom := Rect.Bottom - 3;
  end;

  {$IFNDEF TMSDOTNET}
    {$IFDEF DELPHI2009_LVL}
    DrawText(TListBox(Control).Canvas.Handle, TListBox(Control).Items[Index], -1, Rect, DT_SINGLELINE or DT_VCENTER);
    {$ELSE}
    DrawText(TListBox(Control).Canvas.Handle, PChar(TListBox(Control).Items[Index]), -1, Rect, DT_SINGLELINE or DT_VCENTER);
    {$ENDIF}
  {$ENDIF}

  {$IFDEF TMSDOTNET}
  DrawText(TListBox(Control).Canvas.Handle, TListBox(Control).Items[Index], -1, Rect, DT_SINGLELINE or DT_VCENTER);
  {$ENDIF}

  if FDisplayRecentSelection and (Index = FRecentSelection.Count - 1) then
  begin
    Rect.Bottom := Rect.Bottom + 3;
    TListBox(Control).Canvas.Pen.Color := clGray;
    TListBox(Control).Canvas.MoveTo(1, Rect.Bottom - 3);
    TListBox(Control).Canvas.LineTo(TListBox(Control).Width - 1, Rect.bottom - 3);

    TListBox(Control).Canvas.MoveTo(1, Rect.Bottom - 1);
    TListBox(Control).Canvas.LineTo(TListBox(Control).Width - 1, Rect.bottom - 1);
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrFontSelector.Loaded;
begin
  inherited;
//  LoadFontNames;
  PopulateListBox;
  DiagramChanged;
end;

//------------------------------------------------------------------------------

procedure TDgrFontSelector.LoadFontNames;
var
  i: integer;
begin
  self.Items.Clear;
{  for i:= FRecentSelection.Count-1 downto 0 do
    self.Items.Add(FRecentSelection[i]);
}
  Items.OnChange := nil;

  for i := 0 to Screen.Fonts.Count - 1 do
  begin
    //if GetFontType(Screen.Fonts.Strings[i]) in FAllowedFontTypes then
    if GetFontType(Screen.Fonts.Strings[i]) <= FAllowedFontTypes then
      self.Items.Add(Screen.Fonts.Strings[i]);
  end;

  Items.OnChange := ItemsChanged;
  DiagramChanged;
end;

//------------------------------------------------------------------------------

procedure TDgrFontSelector.SetFontGlyphTT(const Value: TBitMap);
begin
  FFontGlyphTT.Assign(Value);
end;

procedure TDgrFontSelector.SetFontGlyphPS(const Value: TBitMap);
begin
  FFontGlyphPS.Assign(Value);
end;

procedure TDgrFontSelector.SetFontGlyphPRN(const Value: TBitMap);
begin
  FFontGlyphPRN.Assign(Value);
end;

procedure TDgrFontSelector.SetFontGlyphBMP(const Value: TBitMap);
begin
  FFontGlyphBMP.Assign(Value);
end;


//------------------------------------------------------------------------------
procedure TDgrFontSelector.ValueChanged;
begin
  inherited;
  if Diagram <> nil then
    ApplySelectedFont(Diagram, Text);
end;

procedure TDgrFontSelector.ApplySelectedFont(ADiagram: TatDiagram; AFontName: string);
var
  c: integer;
  d: integer;
begin
  with ADiagram do
    if EditingText then
      EditingCell.Font.Name := AFontName
    else
      for c := 0 to SelectedCount - 1 do if not Selecteds[c].IsGroup then
      begin
        Selecteds[c].Font.Name := AFontName;
        for d := 0 to Selecteds[c].TextCells.Count - 1 do
          if not Selecteds[c].TextCells[d].DControlFont then
            Selecteds[c].TextCells[d].Font.Name := AFontName;
      end;

  if ADiagram.EditingText or (ADiagram.SelectedCount > 0) then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('font');
  end;
end;

//------------------------------------------------------------------------------

procedure TDgrFontSelector.DiagramChanged;
begin
  inherited;
  if Diagram <> nil then
    ItemIndex := Items.IndexOf(Diagram.Font.Name);
end;


{ TDgrOfficeComboBox }

constructor TDgrOfficeComboBox.Create(aOwner: TComponent);
begin
  inherited;
  AutoItemSize := false;
end;

{ TDgrZoomSelector }

procedure TDgrZoomSelector.ApplySelectedZoom(ADiagram: TatDiagram;
  AZoom: integer);
begin
  ADiagram.Zoom := AZoom;
  ADiagram.Modified;
  ADiagram.PushUndoStack('zoom');
end;

constructor TDgrZoomSelector.Create(AOwner: TComponent);
begin
  inherited;
  ControlStyle := ControlStyle + [csActionClient];
  DisplayRecentSelection := false;
  Text := '100%';
  Lookup := false;
end;

procedure TDgrZoomSelector.CreateWnd;
begin
  inherited;
  LoadZoomItems;
end;

procedure TDgrZoomSelector.DiagramChanged;
begin
  if Diagram <> nil then
    Text := GetZoomText(Diagram.Zoom);
end;

function TDgrZoomSelector.GetZoom: integer;
begin
  result := GetZoomFromText(Text);
end;

function TDgrZoomSelector.GetZoomFromText(AText: string): integer;
begin
  AText := Trim(AText);
  if (Length(AText) > 0) and (AText[Length(AText)] = '%') then
    AText := Copy(AText, 1, Length(AText) - 1);
  try
    result := StrToInt(AText);
  except
    if Diagram <> nil then
      result := Diagram.Zoom
    else
      result := 100;
  end;
end;

procedure TDgrZoomSelector.KeyDown(var Key: Word; Shift: TShiftState);
begin
  case Key of
    vk_return:
      begin
        self.Change;
        ValueChanged;
        if FDropDownList.Visible then
          HideDropDown;
      end;
  end;
  inherited KeyDown(Key, Shift);
end;

procedure TDgrZoomSelector.LoadZoomItems;
begin
  Items.clear;
  Items.Add('500%');
  Items.Add('200%');
  Items.Add('150%');
  Items.Add('100%');
  Items.Add('75%');
  Items.Add('50%');
  Items.Add('25%');
  Items.Add('10%');
end;

procedure TDgrZoomSelector.ValueChanged;
var
  ANewText: string;
begin
  inherited;
  if Diagram <> nil then
    ApplySelectedZoom(Diagram, Zoom);

  ANewText := GetZoomText(Zoom);
  if Text <> ANewText then
    Text := ANewText;
end;

function TDgrZoomSelector.GetZoomText(AZoom: integer): string;
begin
  result := Format('%d%%', [AZoom]);
end;

procedure TDgrZoomSelector.InitiateAction;
var
  AText: string;
begin
  inherited;
  if (Diagram <> nil) and not Focused then
  begin
    AText := GetZoomText(Diagram.Zoom);
    if Text <> AText then
      Text := AText;
  end;
end;

{ TDgrFontSizeSelector }

procedure TDgrFontSizeSelector.ApplySelectedSize(ADiagram: TatDiagram;
  ASize: integer);
var
  c: integer;
  d: integer;
begin
  with ADiagram do
    if EditingText then
      EditingCell.Font.Size := ASize
    else
      for c := 0 to SelectedCount - 1 do if not Selecteds[c].IsGroup then
      begin
        Selecteds[c].Font.Size := ASize;
        for d := 0 to Selecteds[c].TextCells.Count - 1 do
          if not Selecteds[c].TextCells[d].DControlFont then
            Selecteds[c].TextCells[d].Font.Size := ASize;
      end;

  if (ADiagram.EditingText) or (ADiagram.SelectedCount > 0) then
  begin
    ADiagram.Modified;
    ADiagram.PushUndoStack('font size');
  end;
end;

constructor TDgrFontSizeSelector.Create(AOwner: TComponent);
begin
  inherited;
  DisplayRecentSelection := false;
  Lookup := false;
end;

procedure TDgrFontSizeSelector.CreateWnd;
begin
  inherited;
  LoadSizeItems;
  Text := '8';
end;

procedure TDgrFontSizeSelector.DiagramChanged;
begin
  inherited;
  if Diagram <> nil then
    Text := GetSizeText(Diagram.Font.Size);
end;

function TDgrFontSizeSelector.GetFontSize: integer;
begin
  result := GetSizeFromText(Text);
end;

function TDgrFontSizeSelector.GetSizeFromText(AText: string): integer;
begin
  AText := Trim(AText);
  try
    result := StrToInt(AText);
  except
    if Diagram <> nil then
      result := Diagram.Font.Size
    else
      result := 8;
  end;
end;

function TDgrFontSizeSelector.GetSizeText(ASize: integer): string;
begin
  result := Format('%d', [ASize]);
end;

procedure TDgrFontSizeSelector.KeyDown(var Key: Word; Shift: TShiftState);
begin
  case Key of
    vk_return:
      begin
        self.Change;
        ValueChanged;
        if FDropDownList.Visible then
          HideDropDown;
      end;
  end;
  inherited KeyDown(Key, Shift);
end;

procedure TDgrFontSizeSelector.LoadSizeItems;
begin
  Items.clear;
  Items.Add('8');
  Items.Add('9');
  Items.Add('10');
  Items.Add('11');
  Items.Add('12');
  Items.Add('14');
  Items.Add('16');
  Items.Add('18');
  Items.Add('20');
  Items.Add('22');
  Items.Add('24');
  Items.Add('26');
  Items.Add('28');
  Items.Add('36');
  Items.Add('48');
  Items.Add('72');
end;

procedure TDgrFontSizeSelector.ValueChanged;
var
  ANewText: string;
begin
  inherited;
  if Diagram <> nil then
    ApplySelectedSize   (Diagram, FontSize);

  ANewText := GetSizeText(FontSize);
  if Text <> ANewText then
    Text := ANewText;
end;

{ TDgrLayerSelector }

procedure TDgrLayerSelector.ApplySelectedLayer(ADiagram: TatDiagram; ALayerName: string);
var
  i: integer;
begin
  if ADiagram.SelectedCount > 0 then
  begin
    for i := ADiagram.SelectedCount - 1 downto 0 do
      ADiagram.Selecteds[i].LayerName := ALayerName;
    ADiagram.Modified;
  end;
end;

constructor TDgrLayerSelector.Create(AOwner: TComponent);
begin
  inherited;
  ControlStyle := ControlStyle + [csActionClient];
  DisplayRecentSelection := false;
  Style := csDropDownList;
end;

function TDgrLayerSelector.GetLayerName: string;
begin
  if ItemIndex > 0 then
    result := Items[ItemIndex]
  else
    result := '';
end;

procedure TDgrLayerSelector.InitiateAction;
begin
  inherited;
  if Diagram <> nil then
  begin
    LoadLayerItems;
    if not Focused then
    begin
      Enabled := Diagram.SelectedCount > 0;
      if Enabled then
        LayerName := Diagram.Selecteds[0].LayerName
      else
        LayerName := '';
    end;
  end;
end;

procedure TDgrLayerSelector.LoadLayerItems;
var
  i: Integer;
  sl: TStringList;
begin
  if Diagram <> nil then
  begin
    FAutoChange := True;
    sl := TStringList.Create;
    try
      sl.Add('(Ã»ÓÐÍ¼²ã)');
      for i:=0 to Diagram.Layers.Count-1 do
        sl.Add(Diagram.Layers[i].LayerName);
      if sl.Text <> Items.Text then
      begin
        Items.Assign(sl);
        ItemIndex := 0;
      end;
    finally
      sl.Free;
      FAutoChange := False;
    end;
  end;
end;

procedure TDgrLayerSelector.SetLayerName(const Value: string);
var
  i: integer;
begin
  FAutoChange := True;
  try
    i := Items.IndexOf(Value);
    if i < 0 then
    begin
      if Value > '' then
        i := Items.IndexOf(Value);
      if i < 0 then
        i := 0;
    end;
    if i <> ItemIndex then
      ItemIndex := i;
  finally
    FAutoChange := False;
  end;
end;

procedure TDgrLayerSelector.ValueChanged;
begin
  inherited;
  if (Diagram <> nil) and not FAutoChange then
    ApplySelectedLayer(Diagram, LayerName);
end;

end.
