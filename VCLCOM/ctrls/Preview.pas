{------------------------------------------------------------------------------}
{                                                                              }
{  TPrintPreview v4.20 & TPaperPreview v1.02                                   }
{  by Kambiz R. Khojasteh                                                      }
{                                                                              }
{  kambiz@delphiarea.com                                                       }
{  http://www.delphiarea.com                                                   }
{                                                                              }
{  Special thanks to:                                                          }
{    Rinaldo Andrea (Italy)         <laser@nuovacs.it>                         }
{    Jens Christian Fogtmann        <jefo@post2.tele.dk>                       }
{    Damian Tarnawsky               <tarnawsky@ali.com.au>                     }
{    Bill Miller                    <w2m@netheaven.com>                        }
{    Wen Shihong                    <wenshihong@justep.com>                    }
{    Peter Hedlund                  <peter@peterandlinda.com>                  }
{    Pavel Zidek (Czech)            <delphi@kopr.cz>            (SaveZoomPos)  }
{    Roy M Klever                   <roy.magne@os.ino.no>                      }
{    Paul Van Gundy                 <b06pxv@FDS.com>            //pvg          }
{    Hubert "Johnny_Bit" Kowalski   <johnnybit@poczta.onet.pl>                 }
{    Tomas Koutny                   <rawos@rawos.com>                          }
{                                                                              }
{------------------------------------------------------------------------------}

unit Preview;

interface

uses
  Windows, WinSpool, Messages, Classes, Graphics, Controls, SysUtils, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, Printers;

const
  crHand = 10;
  crGrab = 11; //pvg

type

  EInvalidPreviewData = class(Exception);

  { TMetaFileList }

  TMetaFileList = class(TObject)
  private
    FRecords: TList;
    FDataStream: TStream;
    FMetaFile: TMetaFile;
    FUseTempFile: Boolean;
    FTempFile: String;
    FOnChange: TNotifyEvent;
    function GetCount: Integer;
    function GetItems(Index: Integer): TMetaFile;
    procedure SetUseTempFile(Value: Boolean);
    function CreateMetaFileStream: TStream;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Clear;
    function Add(AMetaFile: TMetaFile): Integer;
    procedure LoadFromStream(Stream: TStream);
    procedure SaveToStream(Stream: TStream);
    procedure LoadFromFile(const FileName: String);
    procedure SaveToFile(const FileName: String);
    property Count: Integer read GetCount;
    property Items[Index: Integer]: TMetaFile read GetItems; default;
    property UseTempFile: Boolean read FUseTempFile write SetUseTempFile;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  end;

  { TPaperPreview }

  TPaperPaintEvent = procedure(Sender: TObject; Canvas: TCanvas; PageRect: TRect) of object;

  TPaperPreview = class(TCustomControl)
  private
    FPaperColor: TColor;
    FBorderColor: TColor;
    FBorderSize: TBorderWidth;
    FShadowColor: TColor;
    FShadowSize: TBorderWidth;
    FOnResize: TNotifyEvent;
    FOnPaint: TPaperPaintEvent;
    FOffScreen: TBitmap;
    FOffScreenOK: Boolean;
    procedure SetPaperWidth(Value: Integer);
    function GetPaperWidth: Integer;
    procedure SetPaperHeight(Value: Integer);
    function GetPaperHeight: Integer;
    procedure SetPaperColor(Value: TColor);
    procedure SetBorderColor(Value: TColor);
    procedure SetBorderSize(Value: TBorderWidth);
    procedure SetShadowColor(Value: TColor);
    procedure SetShadowSize(Value: TBorderWidth);
  protected
    property Canvas;
    procedure Paint; override;
    function PageRect: TRect; dynamic;
    procedure WMSize(var Message: TWMSize); message WM_SIZE;
    procedure WMEraseBkgnd(var Message: TWMEraseBkgnd); message WM_ERASEBKGND;
    function ActualWidth(APaperWidth: Integer): Integer;
    function ActualHeight(APaperHeight: Integer): Integer;
    function LogicalWidth(AWidth: Integer): Integer;
    function LogicalHeight(AHeight: Integer): Integer;
    property OffScreenOK: Boolean read FOffScreenOK;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property Align;
    property BorderColor: TColor read FBorderColor write SetBorderColor default clBlack;
    property BorderSize: TBorderWidth read FBorderSize write SetBorderSize default 1;
    property Color;
    property Cursor;
    property DragCursor;
    property DragMode;
    property ParentColor;
    property ParentShowHint;
    property PopupMenu;
    property PaperColor: TColor read FPaperColor write SetPaperColor default clWhite;
    property PaperWidth: Integer read GetPaperWidth write SetPaperWidth;
    property PaperHeight: Integer read GetPaperHeight write SetPaperHeight;
    property ShadowColor: TColor read FShadowColor write SetShadowColor default clBtnShadow;
    property ShadowSize: TBorderWidth read FShadowSize write SetShadowSize default 3;
    property ShowHint;
    property TabOrder;
    property TabStop;
    property Visible;
    property OnClick;
    property OnDblClick;
    property OnDragDRop;
    property OnDragOver;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnResize: TNotifyEvent read FOnResize write FOnResize;
    property OnPaint: TPaperPaintEvent read FOnPaint write FOnPaint;
  end;

  { TPaperPreviewOptions }

  TPaperPreviewOptions = class(TPersistent)
  private
    FPaperColor: TColor;
    FBorderColor: TColor;
    FBorderWidth: TBorderWidth;
    FShadowColor: TColor;
    FShadowWidth: TBorderWidth;
    FCursor: TCursor;
    FDragCursor: TCursor;
    FGrabCursor: TCursor; //pvg
    FPopupMenu: TPopupMenu;
    FOnChange: TNotifyEvent;
    procedure SetPaperColor(Value: TColor);
    procedure SetBorderColor(Value: TColor);
    procedure SetBorderWidth(Value: TBorderWidth);
    procedure SetShadowColor(Value: TColor);
    procedure SetShadowWidth(Value: TBorderWidth);
    procedure SetCursor(Value: TCursor);
    procedure SetDragCursor(Value: TCursor);
    procedure SetGrabCursor(Value: TCursor); //pvg
    procedure SetPopupMenu(Value: TPopupMenu);
  protected
    procedure DoChange;
  public
    constructor Create;
    procedure Assign(Source: TPersistent); override;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  published
    property BorderColor: TColor read FBorderColor write SetBorderColor default clBlack;
    property BorderWidth: TBorderWidth read FBorderWidth write SetBorderWidth default 1;
    property Cursor: TCursor read FCursor write SetCursor default crDefault;
    property DragCursor: TCursor read FDragCursor write SetDragCursor default crHand;
    property GrabCursor: TCursor read FGrabCursor write SetGrabCursor default crGrab; //pvg
    property PaperColor: TColor read FPaperColor write SetPaperColor default clWhite;
    property PopupMenu: TPopupMenu read FPopupMenu write SetPopupMenu;
    property ShadowColor: TColor read FShadowColor write SetShadowColor default clBtnShadow;
    property ShadowWidth: TBorderWidth read FShadowWidth write SetShadowWidth default 3;
  end;

  { TPrintPreview}

  TPreviewPrintProgress = procedure(Sender: TObject; PageNum, Progress: Integer;
    var AbortIt: Boolean) of object;

  TPreviewState = (psReady, psCreating, psPrinting);
  TZoomState = (zsZoomOther, zsZoomToWidth, zsZoomToHeight, zsZoomToFit);
  TUnits = (mmPixel, mmLoMetric, mmHiMetric, mmLoEnglish, mmHiEnglish, mmTWIPS);
  TPaperType = (pLetter, pLetterSmall, pTabloid, pLedger, pLegal, pStatement,
    pExecutive, pA3, pA4, pA4Small, pA5, pB4, pB5, pFolio, pQuatro, p10x14,
    p11x17, pNote, pEnv9, pEnv10, pEnv11, pEnv12, pEnv14, pCSheet, pDSheet,
    pESheet, pEnvDL, pEnvC5, pEnvC3, pEnvC4, pEnvC6, pEnvC65, pEnvB4, pEnvB5,
    pEnvB6, pEnvItaly, pEnvMonarch, pEnvPersonal, pFanfoldUSStd, pFanfoldGermanStd,
    pFanfoldGermanLegal, pB4ISO, pJapanesePostcard, p9x11, p10x11, p15x11,
    pEnvInvite, pLetterExtra, pLegalExtra, TabloidExtra, pA4Extra, pLetterTransverse,
    pA4Transverse, pLetterExtraTransverse, pAPlus, pBPlus, pLetterPlus, pA4Plus,
    pA5Transverse, pB5Transverse, pA3Extra, pA5Extra, pB5Extra, pA2, pA3Transverse,
    pA3ExtraTransverse, pCustom);

  TPrintPreview = class(TScrollBox)
  private
    FPaperView: TPaperPreview;
    FPaperViewOptions: TPaperPreviewOptions;
    FPrintJobTitle: String;
    FPages: TMetaFileList;
    FCanvas: TCanvas;
    FUnits: TUnits;
    FPixels: TPoint;
    FAborted: Boolean;
    FOrientation: TPrinterOrientation;
    FCurrentPage: Integer;
    FPaperType: TPaperType;
    FPaperWidth: Integer;
    FPaperHeight: Integer;
    FState: TPreviewState;
    FZoom: Integer;
    FZoomState: TZoomState;
    FZoomSavePos: Boolean;
    FZoomMin: Integer;
    FZoomMax: Integer;
    FZoomStep: Integer;
    FFastPrint: Boolean;
    FUsePrinterOptions: Boolean;
    FOnBeginDoc: TNotifyEvent;
    FOnEndDoc: TNotifyEvent;
    FOnNewPage: TNotifyEvent;
    FOnAbort: TNotifyEvent;
    FOnChange: TNotifyEvent;
    FOnPrintProgress: TPreviewPrintProgress;
    FOnBeforePrint: TNotifyEvent;
    FOnAfterPrint: TNotifyEvent;
    FOnZoomChange: TNotifyEvent;
    FOldMousePos: TPoint;
    FCanScrollHorz: Boolean;
    FCanScrollVert: Boolean;
    FDraggingPage: Boolean;
    DPI: TPoint;
    MetaFile: TMetafile;
    WheelAccumulator: Integer;
    procedure SetPaperViewOptions(Value: TPaperPreviewOptions);
    procedure SetUnits(Value: TUnits);
    procedure SetPaperType(Value: TPaperType);
    procedure SetPaperWidth(Value: Integer);
    procedure SetPaperHeight(Value: Integer);
    procedure SetOrientation(Value: TPrinterOrientation);
    procedure SetZoomState(Value: TZoomState);
    procedure SetZoom(Value: Integer);
    procedure SetZoomMin(Value: Integer);
    procedure SetZoomMax(Value: Integer);
    procedure SetCurrentPage(Value: Integer);
    function GetUseTempFile: Boolean;
    procedure SetUseTempFile(Value: Boolean);
    function GetTotalPages: Integer;
    function GetPages(PageNo: Integer): TMetaFile;
    function GetCanvas: TCanvas;
    function GetPrinterInstalled: Boolean;
    function CalculateViewSize(const Space: TPoint): TPoint;
    function IsCustomPaper: Boolean;
    function IsZoomStored: Boolean;
    procedure PaperClick(Sender: TObject);
    procedure PaperDblClick(Sender: TObject);
    procedure PaperMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure PaperMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
    procedure PaperMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure PaperViewOptionsChanged(Sender: TObject);
    procedure PagesChanged(Sender: TObject);
    procedure CNKeyDown(var Message: TWMKey); message CN_KEYDOWN;
    procedure WMMouseWheel(var Message: TMessage); message WM_MOUSEWHEEL;
  protected
    procedure Loaded; override;
    procedure Resize; override;
    procedure DoProgress(Current, Done, Total: Integer); virtual;
    procedure PaintPage(Sender: TObject; Canvas: TCanvas; PageRect: TRect); virtual;
    procedure CalculateMetafileSize; virtual;
    procedure CreateMetaFileCanvas; virtual;
    procedure CloseMetaFileCanvas; virtual;
    procedure AdjustCanvasView; virtual;
    function GetPrintPageBounds: TRect; virtual;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    function ConvertUnit(Value: Integer; FromUnit, ToUnit: TUnits): Integer;
    function ToPrinterUnit(Value, Resolution: Integer): Integer;
    function Screen2PrinterUnit(Value: Integer): Integer;
    function PaintGraphic(X, Y: Integer; Graphic: TGraphic): TPoint;
    function PaintGraphicEx(const Rect: TRect; Graphic: TGraphic;
      Proportinal, ShrinkOnly, Center: Boolean): TRect;
    function PaintWinControl(X, Y: Integer; WinControl: TWinControl): TPoint;
    function PaintWinControlEx(const Rect: TRect; WinControl: TWinControl;
      Proportinal, ShrinkOnly, Center: Boolean): TRect;
    function PaintRichText(const Rect: TRect; RichEdit: TCustomRichEdit;
      MaxPages: Integer; pOffset: PInteger): Integer;
    function GetRichTextRect(var Rect: TRect; RichEdit: TCustomRichEdit;
      pOffset: PInteger): Integer;
    procedure Clear;
    procedure BeginDoc;
    procedure EndDoc;
    procedure NewPage;
    procedure Abort;
    procedure Print;
    procedure UpdateZoom;
    procedure SetPrinterOptions;
    procedure GetPrinterOptions;
    procedure PrintPages(FirstPage, LastPage: Integer);
    procedure LoadFromStream(Stream: TStream);
    procedure SaveToStream(Stream: TStream);
    procedure LoadFromFile(const FileName: String);
    procedure SaveToFile(const FileName: String);
    property Aborted: Boolean read FAborted;
    property Canvas: TCanvas read GetCanvas;
    property TotalPages: Integer read GetTotalPages;
    property State: TPreviewState read FState;
    property PrinterInstalled: Boolean read GetPrinterInstalled;
    property CurrentPage: Integer read FCurrentPage write SetCurrentPage;
    property Pages[PageNo: Integer]: TMetaFile read GetPages;
  published
    property Align default alClient;
    property FastPrint: Boolean read FFastPrint write FFastPrint default True;
    property TabStop default True;
    property ParentFont default False;
    property PrintJobTitle: String read FPrintJobTitle write FPrintJobTitle;
    property Units: TUnits read FUnits write SetUnits default mmHiMetric;
    property Orientation: TPrinterOrientation read FOrientation write SetOrientation default poPortrait;
    property PaperType: TPaperType read FPaperType write SetPaperType default pA4;
    property PaperView: TPaperPreviewOptions read FPaperViewOptions write SetPaperViewOptions;
    property PaperWidth: Integer read FPaperWidth write SetPaperWidth stored IsCustomPaper;
    property PaperHeight: Integer read FPaperHeight write SetPaperHeight stored IsCustomPaper;
    property ZoomState: TZoomState read FZoomState write SetZoomState default zsZoomToFit;
    property Zoom: Integer read FZoom write SetZoom stored IsZoomStored;
    property ZoomMin: Integer read FZoomMin write SetZoomMin default 10;
    property ZoomMax: Integer read FZoomMax write SetZoomMax default 500;
    property ZoomSavePos: Boolean read FZoomSavePos write FZoomSavePos default True;
    property ZoomStep: Integer read FZoomStep write FZoomStep default 10;
    property UsePrinterOptions: Boolean read FUsePrinterOptions write FUsePrinterOptions default False;
    property UseTempFile: Boolean read GetUseTempFile write SetUseTempFile default False;
    property OnBeginDoc: TNotifyEvent read FOnBeginDoc write FOnBeginDoc;
    property OnEndDoc: TNotifyEvent read FOnEndDoc write FOnEndDoc;
    property OnNewPage: TNotifyEvent read FOnNewPage write FOnNewPage;
    property OnAbort: TNotifyEvent read FOnAbort write FOnAbort;
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
    property OnPrintProgress: TPreviewPrintProgress read FOnPrintProgress write FOnPrintProgress;
    property OnBeforePrint: TNotifyEvent read FOnBeforePrint write FOnBeforePrint;
    property OnAfterPrint: TNotifyEvent read FOnAfterPrint write FOnAfterPrint;
    property OnZoomChange: TNotifyEvent read FOnZoomChange write FOnZoomChange;
  end;

  TPaperSizeInfo = record
    ID: SmallInt;
    Width, Height: Integer;
    Units: TUnits;
  end;

const
  // Paper Sizes
  PaperSizes: array[TPaperType] of TPaperSizeInfo = (
    (ID: DMPAPER_LETTER;                  Width: 08500;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_LETTER;                  Width: 08500;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_TABLOID;                 Width: 11000;     Height: 17000;     Units: mmHiEnglish),
    (ID: DMPAPER_LEDGER;                  Width: 17000;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_LEGAL;                   Width: 08500;     Height: 14000;     Units: mmHiEnglish),
    (ID: DMPAPER_STATEMENT;               Width: 05500;     Height: 08500;     Units: mmHiEnglish),
    (ID: DMPAPER_EXECUTIVE;               Width: 07250;     Height: 10500;     Units: mmHiEnglish),
    (ID: DMPAPER_A3;                      Width: 02970;     Height: 04200;     Units: mmLoMetric),
    (ID: DMPAPER_A4;                      Width: 02100;     Height: 02970;     Units: mmLoMetric),
    (ID: DMPAPER_A4SMALL;                 Width: 02100;     Height: 02970;     Units: mmLoMetric),
    (ID: DMPAPER_A5;                      Width: 01480;     Height: 02100;     Units: mmLoMetric),
    (ID: DMPAPER_B4;                      Width: 02500;     Height: 03540;     Units: mmLoMetric),
    (ID: DMPAPER_B5;                      Width: 01820;     Height: 02570;     Units: mmLoMetric),
    (ID: DMPAPER_FOLIO;                   Width: 08500;     Height: 13000;     Units: mmHiEnglish),
    (ID: DMPAPER_QUARTO;                  Width: 02150;     Height: 02750;     Units: mmLoMetric),
    (ID: DMPAPER_10X14;                   Width: 10000;     Height: 14000;     Units: mmHiEnglish),
    (ID: DMPAPER_11X17;                   Width: 11000;     Height: 17000;     Units: mmHiEnglish),
    (ID: DMPAPER_NOTE;                    Width: 08500;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_9;                   Width: 03875;     Height: 08875;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_10;                  Width: 04125;     Height: 09500;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_11;                  Width: 04500;     Height: 10375;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_12;                  Width: 04750;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_14;                  Width: 05000;     Height: 11500;     Units: mmHiEnglish),
    (ID: DMPAPER_CSHEET;                  Width: 17000;     Height: 22000;     Units: mmHiEnglish),
    (ID: DMPAPER_DSHEET;                  Width: 22000;     Height: 34000;     Units: mmHiEnglish),
    (ID: DMPAPER_ESHEET;                  Width: 34000;     Height: 44000;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_DL;                  Width: 01100;     Height: 02200;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_C5;                  Width: 01620;     Height: 02290;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_C3;                  Width: 03240;     Height: 04580;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_C4;                  Width: 02290;     Height: 03240;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_C6;                  Width: 01140;     Height: 01620;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_C65;                 Width: 01140;     Height: 02290;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_B4;                  Width: 02500;     Height: 03530;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_B5;                  Width: 01760;     Height: 02500;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_B6;                  Width: 01760;     Height: 01250;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_ITALY;               Width: 01100;     Height: 02300;     Units: mmLoMetric),
    (ID: DMPAPER_ENV_MONARCH;             Width: 03875;     Height: 07500;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_PERSONAL;            Width: 03625;     Height: 06500;     Units: mmHiEnglish),
    (ID: DMPAPER_FANFOLD_US;              Width: 14875;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_FANFOLD_STD_GERMAN;      Width: 08500;     Height: 12000;     Units: mmHiEnglish),
    (ID: DMPAPER_FANFOLD_LGL_GERMAN;      Width: 08500;     Height: 13000;     Units: mmHiEnglish),
    (ID: DMPAPER_ISO_B4;                  Width: 02500;     Height: 03530;     Units: mmLoMetric),
    (ID: DMPAPER_JAPANESE_POSTCARD;       Width: 01000;     Height: 01480;     Units: mmLoMetric),
    (ID: DMPAPER_9X11;                    Width: 09000;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_10X11;                   Width: 10000;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_15X11;                   Width: 15000;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_ENV_INVITE;              Width: 02200;     Height: 02200;     Units: mmLoMetric),
    (ID: DMPAPER_LETTER_EXTRA;            Width: 09500;     Height: 12000;     Units: mmHiEnglish),
    (ID: DMPAPER_LEGAL_EXTRA;             Width: 09500;     Height: 15000;     Units: mmHiEnglish),
    (ID: DMPAPER_TABLOID_EXTRA;           Width: 11690;     Height: 18000;     Units: mmHiEnglish),
    (ID: DMPAPER_A4_EXTRA;                Width: 09270;     Height: 12690;     Units: mmHiEnglish),
    (ID: DMPAPER_LETTER_TRANSVERSE;       Width: 08500;     Height: 11000;     Units: mmHiEnglish),
    (ID: DMPAPER_A4_TRANSVERSE;           Width: 02100;     Height: 02970;     Units: mmLoMetric),
    (ID: DMPAPER_LETTER_EXTRA_TRANSVERSE; Width: 09500;     Height: 12000;     Units: mmHiEnglish),
    (ID: DMPAPER_A_PLUS;                  Width: 02270;     Height: 03560;     Units: mmLoMetric),
    (ID: DMPAPER_B_PLUS;                  Width: 03050;     Height: 04870;     Units: mmLoMetric),
    (ID: DMPAPER_LETTER_PLUS;             Width: 08500;     Height: 12690;     Units: mmHiEnglish),
    (ID: DMPAPER_A4_PLUS;                 Width: 02100;     Height: 03300;     Units: mmLoMetric),
    (ID: DMPAPER_A5_TRANSVERSE;           Width: 01480;     Height: 02100;     Units: mmLoMetric),
    (ID: DMPAPER_B5_TRANSVERSE;           Width: 01820;     Height: 02570;     Units: mmLoMetric),
    (ID: DMPAPER_A3_EXTRA;                Width: 03220;     Height: 04450;     Units: mmLoMetric),
    (ID: DMPAPER_A5_EXTRA;                Width: 01740;     Height: 02350;     Units: mmLoMetric),
    (ID: DMPAPER_B5_EXTRA;                Width: 02010;     Height: 02760;     Units: mmLoMetric),
    (ID: DMPAPER_A2;                      Width: 04200;     Height: 05940;     Units: mmLoMetric),
    (ID: DMPAPER_A3_TRANSVERSE;           Width: 02970;     Height: 04200;     Units: mmLoMetric),
    (ID: DMPAPER_A3_EXTRA_TRANSVERSE;     Width: 03220;     Height: 04450;     Units: mmLoMetric),
    (ID: DMPAPER_USER;                    Width: 0;        Height: 0;        Units: mmPixel));

procedure DrawGraphicAsDIB(DC: HDC; Rect: TRect; Graphic: TGraphic);
function ConvertUnits(Value, DPI: Integer; InUnits, OutUnits: TUnits): Integer;

procedure Register;

implementation

uses
  RichEdit;

{$R *.RES}

const
  MagicNumber: LongInt     = $50502D4B;
  SNotEnoughMemory         = 'Not enough memory to create a new page';
  SInvalidPreviewData      = 'The content is not Print Preview data';

function GetTemporaryFileName: String;
var
  TempPath: array[0..255] of Char;
  TempFile: array[0..255] of Char;
begin
  GetTempPath(SizeOf(TempPath), TempPath);
  GetTempFileName(TempPath, 'TMP', 0, TempFile);
  Result := StrPas(TempFile);
end;

{ Based on:                                                                         }
{ Sending an image to the printer - by Borland Developer Support Staff              }
{ Article ID: 16211  Publish Date: July 16, 1998  Last Modified: September 01, 1999 }

type
  PPalEntriesArray = ^TPalEntriesArray; {for palette re-construction}
  TPalEntriesArray = array[0..0] of TPaletteEntry;

{$WARNINGS OFF}
procedure BltTBitmapAsDib(DestDc : hdc;   {Handle of where to blt}
                          x : word;       {Bit at x}
                          y : word;       {Blt at y}
                          Width : word;   {Width to stretch}
                          Height : word;  {Height to stretch}
                          bm : TBitmap);  {the TBitmap to Blt}
var
  OriginalWidth :LongInt;               {width of BM}
  dc : hdc;                             {screen dc}
  IsPaletteDevice : bool;               {if the device uses palettes}
  IsDestPaletteDevice : bool;           {if the device uses palettes}
  BitmapInfoSize : integer;             {sizeof the bitmapinfoheader}
  lpBitmapInfo : PBitmapInfo;           {the bitmap info header}
  hBm : hBitmap;                        {handle to the bitmap}
  hPal : hPalette;                      {handle to the palette}
  OldPal : hPalette;                    {temp palette}
  hBits : THandle;                      {handle to the DIB bits}
  pBits : pointer;                      {pointer to the DIB bits}
  lPPalEntriesArray : PPalEntriesArray; {palette entry array}
  NumPalEntries : integer;              {number of palette entries}
  i : integer;                          {looping variable}
begin
{If range checking is on - lets turn it off for now}
{we will remember if range checking was on by defining}
{a define called CKRANGE if range checking is on.}
{We do this to access array members past the arrays}
{defined index range without causing a range check}
{error at runtime. To satisfy the compiler, we must}
{also access the indexes with a variable. ie: if we}
{have an array defined as a: array[0..0] of byte,}
{and an integer i, we can now access a[3] by setting}
{i := 3; and then accessing a[i] without error}
{$IFOPT R+}
  {$DEFINE CKRANGE}
  {$R-}
{$ENDIF}

 {Save the original width of the bitmap}
  OriginalWidth := bm.Width;

 {Get the screen's dc to use since memory dc's are not reliable}
  dc := GetDc(0);
 {Are we a palette device?}
  IsPaletteDevice :=
    GetDeviceCaps(dc, RASTERCAPS) and RC_PALETTE = RC_PALETTE;
 {Give back the screen dc}
  ReleaseDc(0, dc);

 {Allocate the BitmapInfo structure}
  if IsPaletteDevice then
    BitmapInfoSize := sizeof(TBitmapInfo) + (sizeof(TRGBQUAD) * 255)
  else
    BitmapInfoSize := sizeof(TBitmapInfo);
  GetMem(lpBitmapInfo, BitmapInfoSize);

 {Zero out the BitmapInfo structure}
  FillChar(lpBitmapInfo^, BitmapInfoSize, #0);

 {Fill in the BitmapInfo structure}
  lpBitmapInfo^.bmiHeader.biSize := sizeof(TBitmapInfoHeader);
  lpBitmapInfo^.bmiHeader.biWidth := OriginalWidth;
  lpBitmapInfo^.bmiHeader.biHeight := bm.Height;
  lpBitmapInfo^.bmiHeader.biPlanes := 1;
  if IsPaletteDevice then
    lpBitmapInfo^.bmiHeader.biBitCount := 8
  else
    lpBitmapInfo^.bmiHeader.biBitCount := 24;
  lpBitmapInfo^.bmiHeader.biCompression := BI_RGB;
  lpBitmapInfo^.bmiHeader.biSizeImage :=
    ((lpBitmapInfo^.bmiHeader.biWidth *
      longint(lpBitmapInfo^.bmiHeader.biBitCount)) div 8) *
      lpBitmapInfo^.bmiHeader.biHeight;
  lpBitmapInfo^.bmiHeader.biXPelsPerMeter := 0;
  lpBitmapInfo^.bmiHeader.biYPelsPerMeter := 0;
  if IsPaletteDevice then begin
    lpBitmapInfo^.bmiHeader.biClrUsed := 256;
    lpBitmapInfo^.bmiHeader.biClrImportant := 256;
  end else begin
    lpBitmapInfo^.bmiHeader.biClrUsed := 0;
    lpBitmapInfo^.bmiHeader.biClrImportant := 0;
  end;

 {Take ownership of the bitmap handle and palette}
  hBm := bm.ReleaseHandle;
  hPal := bm.ReleasePalette;

 {Get the screen's dc to use since memory dc's are not reliable}
  dc := GetDc(0);

  if IsPaletteDevice then begin
   {If we are using a palette, it must be}
   {selected into the dc during the conversion}
    OldPal := SelectPalette(dc, hPal, TRUE);
   {Realize the palette}
    RealizePalette(dc);
  end;
 {Tell GetDiBits to fill in the rest of the bitmap info structure}
  GetDiBits(dc,
            hBm,
            0,
            lpBitmapInfo^.bmiHeader.biHeight,
            nil,
            TBitmapInfo(lpBitmapInfo^),
            DIB_RGB_COLORS);

 {Allocate memory for the Bits}
  hBits := GlobalAlloc(GMEM_MOVEABLE,
                       lpBitmapInfo^.bmiHeader.biSizeImage);
  pBits := GlobalLock(hBits);
 {Get the bits}
  GetDiBits(dc,
            hBm,
            0,
            lpBitmapInfo^.bmiHeader.biHeight,
            pBits,
            TBitmapInfo(lpBitmapInfo^),
            DIB_RGB_COLORS);


  if IsPaletteDevice then begin
   {Lets fix up the color table for buggy video drivers}
    GetMem(lPPalEntriesArray, sizeof(TPaletteEntry) * 256);
   {$IFDEF VER100}
      NumPalEntries := GetPaletteEntries(hPal,
                                         0,
                                         256,
                                         lPPalEntriesArray^);
   {$ELSE}
      NumPalEntries := GetSystemPaletteEntries(dc,
                                               0,
                                               256,
                                               lPPalEntriesArray^);
   {$ENDIF}
    for i := 0 to (NumPalEntries - 1) do begin
      lpBitmapInfo^.bmiColors[i].rgbRed :=
        lPPalEntriesArray^[i].peRed;
      lpBitmapInfo^.bmiColors[i].rgbGreen :=
        lPPalEntriesArray^[i].peGreen;
      lpBitmapInfo^.bmiColors[i].rgbBlue :=
        lPPalEntriesArray^[i].peBlue;
    end;
    FreeMem(lPPalEntriesArray, sizeof(TPaletteEntry) * 256);
  end;

  if IsPaletteDevice then begin
   {Select the old palette back in}
    SelectPalette(dc, OldPal, TRUE);
   {Realize the old palette}
    RealizePalette(dc);
  end;

 {Give back the screen dc}
  ReleaseDc(0, dc);

 {Is the Dest dc a palette device?}
  IsDestPaletteDevice :=
    GetDeviceCaps(DestDc, RASTERCAPS) and RC_PALETTE = RC_PALETTE;


  if IsPaletteDevice then begin
   {If we are using a palette, it must be}
   {selected into the dc during the conversion}
    OldPal := SelectPalette(DestDc, hPal, TRUE);
   {Realize the palette}
    RealizePalette(DestDc);
  end;

 {Revised by "Roy M Klever" <roy.magne@os.ino.no> to fix Windows 2000 & XP issue}
  SetStretchBltMode(DestDC, ColorOnColor);
 {Do the blt}
  StretchDiBits(DestDc,
                x,
                y,
                Width,
                Height,
                0,
                0,
                OriginalWidth,
                lpBitmapInfo^.bmiHeader.biHeight,
                pBits,
                lpBitmapInfo^,
                DIB_RGB_COLORS,
                SrcCopy);

  if IsDestPaletteDevice then begin
   {Select the old palette back in}
    SelectPalette(DestDc, OldPal, TRUE);
   {Realize the old palette}
    RealizePalette(DestDc);
  end;

 {De-Allocate the Dib Bits}
  GlobalUnLock(hBits);
  GlobalFree(hBits);

 {De-Allocate the BitmapInfo}
  FreeMem(lpBitmapInfo, BitmapInfoSize);

 {Set the ownership of the bimap handles back to the bitmap}
  bm.Handle := hBm;
  bm.Palette := hPal;

  {Turn range checking back on if it was on when we started}
{$IFDEF CKRANGE}
  {$UNDEF CKRANGE}
  {$R+}
{$ENDIF}
end;
{$WARNINGS ON}

procedure DrawGraphicAsDIB(DC: HDC; Rect: TRect; Graphic: TGraphic);
var
  Bitmap: TBitmap;
begin
  if not (Graphic is TBitmap) then
  begin
    Bitmap := TBitmap.Create;
    Bitmap.Width := Graphic.Width;
    Bitmap.Height := Graphic.Height;
    Bitmap.Canvas.Draw(0, 0, Graphic);
  end
  else
    Bitmap := Graphic as TBitmap;
  BltTBitmapAsDib(DC, Rect.Left, Rect.Top,
    Rect.Right - Rect.Left, Rect.Bottom - Rect.Top, Bitmap);
  if not (Graphic is TBitmap) then
    Bitmap.Free;
end;

{ TMetaFileList }

constructor TMetaFileList.Create;
begin
  inherited Create;
  FRecords := TList.Create;
end;

destructor TMetaFileList.Destroy;
begin
  FOnChange := nil;
  Clear;
  FRecords.Free;
  inherited Destroy;
end;

procedure TMetaFileList.Clear;
begin
  FRecords.Clear;
  if Assigned(FDataStream) then
  begin
    FDataStream.Free;
    FDataStream := nil;
    if FUseTempFile and FileExists(FTempFile) then
      DeleteFile(FTempFile);
  end;
  if Assigned(FMetaFile) then
  begin
    FMetaFile.Free;
    FMetaFile := nil;
  end;
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

function TMetaFileList.Add(AMetaFile: TMetaFile): Integer;
var
  Offset: LongInt;
begin
  if not Assigned(FDataStream) then
    FDataStream := CreateMetaFileStream;
  FDataStream.Seek(0, soFromEnd);
  Offset := FDataStream.Position;
  AMetaFile.SaveToStream(FDataStream);
  Result := FRecords.Add(Pointer(Offset));
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

procedure TMetaFileList.LoadFromStream(Stream: TStream);
var
  I: Integer;
  Data: LongInt;
begin
  Stream.Read(Data, SizeOf(Data));
  if MagicNumber <> Data then
    raise EInvalidPreviewData.Create(SInvalidPreviewData);
  Clear;
  Stream.Read(Data, SizeOf(Data));
  FRecords.Capacity := Data;
  for I := Data downto 1 do
  begin
    Stream.Read(Data, SizeOf(Data));
    FRecords.Add(Pointer(Data));
  end;
  FDataStream := CreateMetaFileStream;
  FDataStream.CopyFrom(Stream, Stream.Size - Stream.Position);
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

procedure TMetaFileList.SaveToStream(Stream: TStream);
var
  I: Integer;
  Data: LongInt;
begin
  Data := MagicNumber;
  Stream.Write(Data, SizeOf(Data));
  Data := FRecords.Count;
  Stream.Write(Data, SizeOf(Data));
  for I := 0 to FRecords.Count - 1 do
  begin
    Data := LongInt(FRecords[I]);
    Stream.Write(Data, SizeOf(Data));
  end;
  if Assigned(FDataStream) then
  begin
    FDataStream.Position := 0;
    Stream.CopyFrom(FDataStream, FDataStream.Size);
  end;
end;

procedure TMetaFileList.LoadFromFile(const FileName: String);
var
  FileStream: TFileStream;
begin
  FileStream := TFileStream.Create(FileName, fmOpenRead or fmShareDenyWrite);
  try
    LoadFromStream(FileStream);
  finally
    FileStream.Free;
  end;
end;

procedure TMetaFileList.SaveToFile(const FileName: String);
var
  FileStream: TFileStream;
begin
  FileStream := TFileStream.Create(FileName, fmCreate or fmShareExclusive);
  try
    SaveToStream(FileStream);
  finally
    FileStream.Free;
  end;
end;

function TMetaFileList.GetCount: Integer;
begin
  Result := FRecords.Count;
end;

function TMetaFileList.GetItems(Index: Integer): TMetaFile;
begin
  if not Assigned(FMetaFile) then
    FMetaFile := TMetaFile.Create;
  if (Index >= 0) and (Index < FRecords.Count) then
  begin
    FDataStream.Seek(LongInt(FRecords[Index]), soFromBeginning);
    FMetaFile.LoadFromStream(FDataStream);
  end
  else
    FMetaFile.Clear;
  Result := FMetaFile;
end;

procedure TMetaFileList.SetUseTempFile(Value: Boolean);
var
  NewStream: TStream;
begin
  if FUseTempFile <> Value then
  begin
    FUseTempFile := Value;
    if Assigned(FDataStream) then
    begin
      NewStream := CreateMetaFileStream;
      NewStream.CopyFrom(FDataStream, 0);
      FDataStream.Free;
      FDataStream := NewStream;
      if not FUseTempFile and FileExists(FTempFile) then
      begin
        DeleteFile(FTempFile);
        FTempFile := EmptyStr;
      end;
    end;
  end;
end;

function TMetaFileList.CreateMetaFileStream: TStream;
begin
  if FUseTempFile then
  begin
    FTempFile := GetTemporaryFileName;
    Result := TFileStream.Create(FTempFile, fmCreate or fmShareExclusive)
  end
  else
    Result := TMemoryStream.Create;
end;

{ TPaperPreview }

constructor TPaperPreview.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  ControlStyle := ControlStyle + [csOpaque];
  FOffScreen := TBitmap.Create;
  FBorderColor := clBlack;
  FBorderSize := 1;
  FPaperColor := clWhite;
  FShadowColor := clBtnShadow;
  FShadowSize := 3;
  PaperWidth := 105;
  PaperHeight := 148;
end;

destructor TPaperPreview.Destroy;
begin
  FOffScreen.Free;
  inherited Destroy;
end;

procedure TPaperPreview.Paint;
var
  R, PR: TRect;
  Region: THandle;
begin
  if FOffScreenOK then
  begin
    PR := PageRect;
    with FOffscreen.Canvas do
    begin
      Pen.Mode := pmCopy;
      if BorderSize > 0 then
      begin
        Pen.Width := BorderSize;
        Pen.Style := psInsideFrame;
        Pen.Color := BorderColor;
        Brush.Style := bsClear;
        Rectangle(0, 0, Width - ShadowSize, Height - ShadowSize);
      end;
      if ShadowSize > 0 then
      begin
        Brush.Style := bsSolid;
        Brush.Color := ShadowColor;
        SetRect(R, Width - ShadowSize, ShadowSize, Width, Height);
        FillRect(R);
        SetRect(R, ShadowSize, Height - ShadowSize, Width, Height);
        FillRect(R);
        Brush.Color := Color;
        SetRect(R, Width - ShadowSize, 0, Width, ShadowSize);
        FillRect(R);
        SetRect(R, 0, Height - ShadowSize, ShadowSize, Height);
        FillRect(R);
      end;
      Brush.Style := bsSolid;
      Brush.Color := PaperColor;
      FillRect(PR);
    end;
    if Assigned(FOnPaint) then
    begin
      Region := CreateRectRgn(PR.Left, PR.Top, PR.Right, PR.Bottom);
      SelectClipRgn(FOffScreen.Canvas.Handle, Region);
      try
        FOnPaint(Self, FOffScreen.Canvas, PR);
      finally
        SelectClipRgn(FOffScreen.Canvas.Handle, 0);
        DeleteObject(Region);
      end;
    end;
    BitBlt(Canvas.Handle, 0, 0, Width, Height, FOffScreen.Canvas.Handle,
      0, 0, SRCCOPY);
  end
  else
    inherited;
end;

function TPaperPreview.PageRect;
begin
  with Result do
  begin
    Left := BorderSize;
    Top := BorderSize;
    Right := Width - (ShadowSize + BorderSize);
    Bottom := Height - (ShadowSize + BorderSize);
  end;
end;

function TPaperPreview.ActualWidth(APaperWidth: Integer): Integer;
begin
  Result := APaperWidth + 2 * FBorderSize + FShadowSize;
end;

function TPaperPreview.ActualHeight(APaperHeight: Integer): Integer;
begin
  Result := APaperHeight + 2 * FBorderSize + FShadowSize;
end;

function TPaperPreview.LogicalWidth(AWidth: Integer): Integer;
begin
  Result := AWidth - 2 * FBorderSize - FShadowSize;
end;

function TPaperPreview.LogicalHeight(AHeight: Integer): Integer;
begin
  Result := AHeight - 2 * FBorderSize - FShadowSize;
end;

procedure TPaperPreview.SetPaperWidth(Value: Integer);
begin
  Width := Value + 2 * FBorderSize + FShadowSize;
end;

function TPaperPreview.GetPaperWidth: Integer;
begin
  Result := Width - 2 * FBorderSize - FShadowSize;
end;

procedure TPaperPreview.SetPaperHeight(Value: Integer);
begin
  Height := Value + 2 * FBorderSize + FShadowSize;
end;

function TPaperPreview.GetPaperHeight: Integer;
begin
  Result := Height - 2 * FBorderSize - FShadowSize;
end;

procedure TPaperPreview.SetPaperColor(Value: TColor);
begin
  if FPaperColor <> Value then
  begin
    FPaperColor := Value;
    Invalidate;
  end;
end;

procedure TPaperPreview.SetBorderColor(Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    Invalidate;
  end;
end;

procedure TPaperPreview.SetBorderSize(Value: TBorderWidth);
begin
  if FBorderSize <> Value then
  begin
    FBorderSize := Value;
    Invalidate;
  end;
end;

procedure TPaperPreview.SetShadowColor(Value: TColor);
begin
  if FShadowColor <> Value then
  begin
    FShadowColor := Value;
    Invalidate;
  end;
end;

procedure TPaperPreview.SetShadowSize(Value: TBorderWidth);
begin
  if FShadowSize <> Value then
  begin
    FShadowSize := Value;
    Invalidate;
  end;
end;

procedure TPaperPreview.WMSize(var Message: TWMSize);
begin
  inherited;
  try
    FOffScreen.Width := Width;
    FOffScreen.Height := Height;
    FOffScreenOK := True;
  except
    FOffScreenOK := False;
  end;
  if Assigned(FOnResize) then
    FOnResize(Self);
end;

procedure TPaperPreview.WMEraseBkgnd(var Message: TWMEraseBkgnd);
begin
  Message.Result := 1;
end;

{ TPaperPreviewOptions }

constructor TPaperPreviewOptions.Create;
begin
  inherited Create;
  FBorderColor := clBlack;
  FBorderWidth := 1;
  FCursor := crDefault;
  FDragCursor := crHand;
  FGrabCursor := crGrab;  //pvg
  FPaperColor := clWhite;
  FShadowColor := clBtnShadow;
  FShadowWidth := 3;
end;

procedure TPaperPreviewOptions.Assign(Source: TPersistent);
begin
  if Source is TPaperPreviewOptions then
  begin
    BorderColor := TPaperPreviewOptions(Source).BorderColor;
    BorderWidth :=  TPaperPreviewOptions(Source).BorderWidth;
    Cursor := TPaperPreviewOptions(Source).Cursor;
    DragCursor := TPaperPreviewOptions(Source).DragCursor;
    GrabCursor := TPaperPreviewOptions(Source).GrabCursor; //pvg
    PaperColor := TPaperPreviewOptions(Source).PaperColor;
    PopupMenu := TPaperPreviewOptions(Source).PopupMenu;
    ShadowColor := TPaperPreviewOptions(Source).ShadowColor;
    ShadowWidth := TPaperPreviewOptions(Source).ShadowWidth;
  end
  else
    inherited Assign(Source);
end;

procedure TPaperPreviewOptions.DoChange;
begin
  if Assigned(FOnChange) then FOnChange(self);
end;

procedure TPaperPreviewOptions.SetPaperColor(Value: TColor);
begin
  if FPaperColor <> Value then
  begin
    FPaperColor := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetBorderColor(Value: TColor);
begin
  if FBorderColor <> Value then
  begin
    FBorderColor := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetBorderWidth(Value: TBorderWidth);
begin
  if FBorderWidth <> Value then
  begin
    FBorderWidth := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetShadowColor(Value: TColor);
begin
  if FShadowColor <> Value then
  begin
    FShadowColor := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetShadowWidth(Value: TBorderWidth);
begin
  if FShadowWidth <> Value then
  begin
    FShadowWidth := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetCursor(Value: TCursor);
begin
  if FCursor <> Value then
  begin
    FCursor := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetDragCursor(Value: TCursor);
begin
  if FDragCursor <> Value then
  begin
    FDragCursor := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetGrabCursor(Value: TCursor); //pvg
begin
  if FGrabCursor <> Value then
  begin
    FGrabCursor := Value;
    DoChange;
  end;
end;

procedure TPaperPreviewOptions.SetPopupMenu(Value: TPopupMenu);
begin
  if FPopupMenu <> Value then
  begin
    FPopupMenu := Value;
    DoChange;
  end;
end;

{ TPrintPreview }

procedure RaiseOutOfMemory;
begin
  raise EOutOfMemory.Create(SNotEnoughMemory);
end;

procedure SwapValue(var A, B: Integer);
begin
  A := A xor B;
  B := A xor B;
  A := A xor B;
end;

{ Corrected by jcf }
function GetPhysicalPageBounds: TRect;
var
  Ofs: TPoint;
  Size: TPoint;
begin
  Ofs.X := GetDeviceCaps(Printer.Handle, PHYSICALOFFSETX);
  Ofs.Y := GetDeviceCaps(Printer.Handle, PHYSICALOFFSETY);
  Size.X := GetDeviceCaps(Printer.Handle, PHYSICALWIDTH);
  Size.Y := GetDeviceCaps(Printer.Handle, PHYSICALHEIGHT);
  SetRect(Result, -Ofs.X, -Ofs.Y, Size.X - Ofs.X, Size.Y - Ofs.Y);
end;

function ConvertUnits(Value, DPI: Integer; InUnits, OutUnits: TUnits): Integer;
begin
  Result := Value;
  case InUnits of
    mmLoMetric:
      case OutUnits of
        mmLoMetric: Result := Value;
        mmHiMetric: Result := Value * 10;
        mmLoEnglish: Result := MulDiv(Value, 100, 254);
        mmHiEnglish: Result := MulDiv(Value, 1000, 254);
        mmTWIPS: Result := MulDiv(Value, 1440, 254);
        mmPixel: Result := MulDiv(Value, DPI, 254);
      end;
    mmHiMetric:
      case OutUnits of
        mmLoMetric: Result := Value div 10;
        mmHiMetric: Result := Value;
        mmLoEnglish: Result := MulDiv(Value, 10, 254);
        mmHiEnglish: Result := MulDiv(Value, 100, 254);
        mmTWIPS: Result := MulDiv(Value, 1440, 2540);
        mmPixel: Result := MulDiv(Value, DPI, 2540);
      end;
    mmLoEnglish:
      case OutUnits of
        mmLoMetric: Result := MulDiv(Value, 254, 100);
        mmHiMetric: Result := MulDiv(Value, 254, 10);
        mmLoEnglish: Result := Value;
        mmHiEnglish: Result := Value * 10;
        mmTWIPS: Result := MulDiv(Value, 1440, 100);
        mmPixel: Result := MulDiv(Value, DPI, 100);
      end;
    mmHiEnglish:
      case OutUnits of
        mmLoMetric: Result := MulDiv(Value, 254, 1000);
        mmHiMetric: Result := MulDiv(Value, 254, 100);
        mmLoEnglish: Result := Value div 10;
        mmHiEnglish: Result := Value;
        mmTWIPS: Result := MulDiv(Value, 1440, 1000);
        mmPixel: Result := MulDiv(Value, DPI, 1000);
      end;
    mmTWIPS:
      case OutUnits of
        mmLoMetric: Result := MulDiv(Value, 254, 1440);
        mmHiMetric: Result := MulDiv(Value, 2540, 1440);
        mmLoEnglish: Result := MulDiv(Value, 100, 1440);
        mmHiEnglish: Result := MulDiv(Value, 1000, 1440);
        mmTWIPS: Result := Value;
        mmPixel: Result := MulDiv(Value, DPI, 1440);
      end;
    mmPixel:
      case OutUnits of
        mmLoMetric: Result := MulDiv(Value, 254, DPI);
        mmHiMetric: Result := MulDiv(Value, 2540, DPI);
        mmLoEnglish: Result := MulDiv(Value, 100, DPI);
        mmHiEnglish: Result := MulDiv(Value, 1000, DPI);
        mmTWIPS: Result := MulDiv(Value, 1440, DPI);
        mmPixel: Result := Value;
      end;
  end;
end;

constructor TPrintPreview.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  Align := alClient;
  TabStop := True;
  FAborted := False;
  FState := psReady;
  FPaperType := pA4;
  FOrientation := poPortrait;
  FUnits := mmHiMetric;
  with PaperSizes[FPaperType] do
  begin
    FPaperWidth := ConvertUnits(Width, Screen.PixelsPerInch, Units, FUnits);
    FPaperHeight := ConvertUnits(Height, Screen.PixelsPerInch, Units, FUnits);
  end;
  CalculateMetafileSize;
  ParentFont := False;
  Font.Name := 'Arial';
  Font.Height := -260; { 2.6 mm }
  FZoomSavePos := True;
  FZoomState := zsZoomToFit;
  FZoom := 100;
  FZoomMin := 10;
  FZoomMax := 500;
  FZoomStep := 10;
  FFastPrint := True;
  FPages := TMetaFileList.Create;
  FPages.OnChange := PagesChanged;
  FPaperViewOptions := TPaperPreviewOptions.Create;
  FPaperViewOptions.OnChange := PaperViewOptionsChanged;
  FPaperView := TPaperPreview.Create(Self);
  with FPaperView do
  begin
    Parent := Self;
    TabStop := False;
    Visible := False;
    OnPaint := PaintPage;
    OnClick := PaperClick;
    OnDblClick := PaperDblClick;
    OnMouseDown := PaperMouseDown;
    OnMouseMove := PaperMouseMove;
    OnMouseUp := PaperMouseUp;
    PaperColor := FPaperViewOptions.PaperColor;
    BorderColor := FPaperViewOptions.BorderColor;
    BorderSize := FPaperViewOptions.BorderWidth;
    ShadowColor := FPaperViewOptions.ShadowColor;
    ShadowSize := FPaperViewOptions.ShadowWidth;
    Cursor := FPaperViewOptions.Cursor;
  end;
end;

destructor TPrintPreview.Destroy;
begin
  FPages.Free;
  FPaperView.Free;
  FPaperViewOptions.Free;
  inherited Destroy;
end;

procedure TPrintPreview.Loaded;
begin
  inherited Loaded;
  CalculateMetafileSize;
  UpdateZoom;
end;

function TPrintPreview.ConvertUnit(Value: Integer; FromUnit, ToUnit: TUnits): Integer;
begin
  Result := ConvertUnits(Value, Screen.PixelsPerInch, FromUnit, ToUnit);
end;

function TPrintPreview.ToPrinterUnit(Value, Resolution: Integer): Integer;
begin
  Result := ConvertUnits(
    ConvertUnits(Value, Resolution, mmPixel, mmHiEnglish),
    Screen.PixelsPerInch, mmHiEnglish, FUnits);
end;

function TPrintPreview.Screen2PrinterUnit(Value: Integer): Integer;
begin
  Result := ToPrinterUnit(Value, Screen.PixelsPerInch);
end;

function TPrintPreview.PaintGraphic(X, Y: Integer; Graphic: TGraphic): TPoint;
var
  Rect: TRect;
begin
  Rect.Left := X;
  Rect.Top := Y;
  Rect.Right := X + Screen2PrinterUnit(Graphic.Width);
  Rect.Bottom := Y + Screen2PrinterUnit(Graphic.Height);
  Result := PaintGraphicEx(Rect, Graphic, False, False, False).BottomRight;
end;

function TPrintPreview.PaintGraphicEx(const Rect: TRect; Graphic: TGraphic;
  Proportinal, ShrinkOnly, Center: Boolean): TRect;
var
  Bitmap: TBitmap;
  gW, gH: Integer;
  rW, rH: Integer;
  W, H: Integer;
begin
  gW := Screen2PrinterUnit(Graphic.Width);
  gH := Screen2PrinterUnit(Graphic.Height);
  rW := Rect.Right - Rect.Left;
  rH := Rect.Bottom - Rect.Top;
  if not ShrinkOnly or (gW > rW) or (gH > rH) then
  begin
    if Proportinal then
    begin
      if (rW / gW) < (rH / gH) then
      begin
        H := (gH * rW) div gW;
        W := rW;
      end
      else
      begin
        W := (gW * rH) div gH;
        H := rH;
      end;
    end
    else
    begin
      W := rW;
      H := rH;
    end;
  end
  else
  begin
    W := gW;
    H := gH;
  end;
  if Center then
  begin
    Result.Left := Rect.Left + (rW - W) div 2;
    Result.Top := Rect.Top + (rH - H) div 2;
  end
  else
    Result.TopLeft := Rect.TopLeft;
  Result.Right := Result.Left + W;
  Result.Bottom := Result.Bottom + H;
  if not (Graphic is TBitmap) then
  begin
    Bitmap := TBitmap.Create;
    Bitmap.Width := Graphic.Width;
    Bitmap.Height := Graphic.Height;
    Bitmap.Canvas.Draw(0, 0, Graphic);
  end
  else
    Bitmap := Graphic as TBitmap;
  BltTBitmapAsDib(Canvas.Handle, Result.Left, Result.Top, W, H, Bitmap);
  if not (Graphic is TBitmap) then
    Bitmap.Free;
end;

function TPrintPreview.PaintWinControl(X, Y: Integer;
  WinControl: TWinControl): TPoint;
var
  Rect: TRect;
begin
  Rect.Left := X;
  Rect.Top := Y;
  Rect.Right := X + Screen2PrinterUnit(WinControl.Width);
  Rect.Bottom := Y + Screen2PrinterUnit(WinControl.Height);
  Result := PaintWinControlEx(Rect, WinControl, False, False, False).BottomRight;
end;

function TPrintPreview.PaintWinControlEx(const Rect: TRect;
  WinControl: TWinControl; Proportinal, ShrinkOnly, Center: Boolean): TRect;
var
  Bitmap: TBitmap;
begin
  Bitmap := TBitmap.Create;
  try
    Bitmap.Width := WinControl.Width;
    Bitmap.Height := WinControl.Height;
    Bitmap.Canvas.Lock;
    try
      WinControl.PaintTo(Bitmap.Canvas.Handle, 0, 0);
    finally
      Bitmap.Canvas.Unlock;
    end;
    Result := PaintGraphicEx(Rect, Bitmap, Proportinal, ShrinkOnly, Center);
  finally
    Bitmap.Free;
  end;
end;

function TPrintPreview.PaintRichText(const Rect: TRect;
  RichEdit: TCustomRichEdit; MaxPages: Integer; pOffset: PInteger): Integer;
var
  Range: TFormatRange;
  OldMap: Integer;
  SaveRect: TRect;
  SaveIndex: Integer;
  MaxLen: Integer;
  TextLenEx: TGetTextLengthEx;
begin
  Result := 0;
  FillChar(Range, SizeOf(TFormatRange), 0);
  Range.hdc := Canvas.Handle;
  Range.hdcTarget := Range.hdc;
  Range.rc.Left := ConvertUnit(Rect.Left, Units, mmTWIPS);
  Range.rc.Top := ConvertUnit(Rect.Top, Units, mmTWIPS);
  Range.rc.Right := ConvertUnit(Rect.Right, Units, mmTWIPS);
  Range.rc.Bottom := ConvertUnit(Rect.Bottom, Units, mmTWIPS);
  Range.rcPage := Range.rc;
  Range.chrg.cpMax := -1;
  if pOffset = nil then
    Range.chrg.cpMin := 0
  else
    Range.chrg.cpMin := pOffset^;
  SaveRect := Range.rc;
  TextLenEx.flags := GTL_DEFAULT;
  TextLenEx.codepage := CP_ACP;
  MaxLen := SendMessage(RichEdit.Handle, EM_GETTEXTLENGTHEX, Integer(@TextLenEx), 0);
  SaveIndex := SaveDC(Range.hdc);
  OldMap := SetMapMode(Range.hdc, MM_TEXT);
  SendMessage(RichEdit.Handle, EM_FORMATRANGE, 0, 0);
  try
    repeat
      if Result > 0  then
      begin
        RestoreDC(Range.hdc, SaveIndex);
        SetMapMode(Range.hdc, OldMap);
        NewPage;
        Range.hdc := Canvas.Handle;
        Range.hdcTarget := Range.hdc;
        SaveIndex := SaveDC(Range.hdc);
        SetMapMode(Range.hdc, MM_TEXT);
        Range.rc := SaveRect;
      end;
      Range.chrg.cpMin := SendMessage(RichEdit.Handle, EM_FORMATRANGE, 1, Integer(@Range));
      if Range.chrg.cpMin <> -1 then
        Inc(Result);
    until (Range.chrg.cpMin >= MaxLen) or (Range.chrg.cpMin = -1) or
          ((MaxPages > 0) and (Result >= MaxPages));
  finally
    SendMessage(RichEdit.Handle, EM_FORMATRANGE, 0, 0);
    RestoreDC(Range.hdc, SaveIndex);
    SetMapMode(Range.hdc, OldMap);
  end;
  if pOffset <> nil then
    if Range.chrg.cpMin < MaxLen then
      pOffset^ := Range.chrg.cpMin
    else
      pOffset^ := -1;
end;

function TPrintPreview.GetRichTextRect(var Rect: TRect;
  RichEdit: TCustomRichEdit; pOffset: PInteger): Integer;
var
  Range: TFormatRange;
  OldMap: Integer;
  SaveRect: TRect;
  SaveIndex: Integer;
  MaxLen: Integer;
  TextLenEx: TGetTextLengthEx;
begin
  FillChar(Range, SizeOf(TFormatRange), 0);
  Range.hdc := Canvas.Handle;
  Range.hdcTarget := Range.hdc;
  Range.rc.Left := ConvertUnit(Rect.Left, Units, mmTWIPS);
  Range.rc.Top := ConvertUnit(Rect.Top, Units, mmTWIPS);
  Range.rc.Right := ConvertUnit(Rect.Right, Units, mmTWIPS);
  Range.rc.Bottom := ConvertUnit(Rect.Bottom, Units, mmTWIPS);
  Range.rcPage := Range.rc;
  Range.chrg.cpMax := -1;
  if pOffset = nil then
    Range.chrg.cpMin := 0
  else
    Range.chrg.cpMin := pOffset^;
  SaveRect := Range.rc;
  SaveIndex := SaveDC(Range.hdc);
  OldMap := SetMapMode(Range.hdc, MM_TEXT);
  SendMessage(RichEdit.Handle, EM_FORMATRANGE, 0, 0);
  try
    Range.chrg.cpMin := SendMessage(RichEdit.Handle, EM_FORMATRANGE, 0, Integer(@Range));
    if Range.chrg.cpMin = -1 then
      Rect.Bottom := Rect.Top
    else
      Rect.Bottom := ConvertUnit(Range.rc.Bottom, mmTWIPS, Units);
  finally
    SendMessage(RichEdit.Handle, EM_FORMATRANGE, 0, 0);
    RestoreDC(Range.hdc, SaveIndex);
    SetMapMode(Range.hdc, OldMap);
  end;
  if pOffset <> nil then
  begin
    TextLenEx.flags := GTL_DEFAULT;
    TextLenEx.codepage := CP_ACP;
    MaxLen := SendMessage(RichEdit.Handle, EM_GETTEXTLENGTHEX, Integer(@TextLenEx), 0);
    if Range.chrg.cpMin < MaxLen then
      pOffset^ := Range.chrg.cpMin
    else
      pOffset^ := -1;
  end;
  Result := Rect.Bottom;
end;

procedure TPrintPreview.CNKeyDown(var Message: TWMKey);
var
  Key: Word;
  Shift: TShiftState;
begin
  with Message do
  begin
    Key := CharCode;
    Shift := KeyDataToShiftState(KeyData);
  end;
  if (Key = VK_HOME) and (Shift = []) then
    with HorzScrollbar do Position := 0
  else if (Key = VK_HOME) and (Shift = [ssCtrl]) then
    with VertScrollbar do Position := 0
  else if (Key = VK_END) and (Shift = []) then
    with HorzScrollbar do Position := Range
  else if (Key = VK_END) and (Shift = [ssCtrl]) then
    with VertScrollbar do Position := Range
  else if (Key = VK_LEFT) and (Shift = [ssShift]) then
    with HorzScrollbar do Position := Position - 1
  else if (Key = VK_LEFT) and (Shift = []) then
    with HorzScrollbar do Position := Position - Increment
  else if (Key = VK_LEFT) and (Shift = [ssCtrl]) then
    with HorzScrollbar do Position := Position - ClientWidth
  else if (Key = VK_RIGHT) and (Shift = [ssShift]) then
    with HorzScrollbar do Position := Position + 1
  else if (Key = VK_RIGHT) and (Shift = []) then
    with HorzScrollbar do Position := Position + Increment
  else if (Key = VK_RIGHT) and (Shift = [ssCtrl]) then
    with HorzScrollbar do Position := Position + ClientWidth
  else if (Key = VK_UP) and (Shift = [ssShift]) then
    with VertScrollbar do Position := Position - 1
  else if (Key = VK_UP) and (Shift = []) then
    with VertScrollbar do Position := Position - Increment
  else if (Key = VK_UP) and (Shift = [ssCtrl]) then
    with VertScrollbar do Position := Position - ClientHeight
  else if (Key = VK_DOWN) and (Shift = [ssShift]) then
    with VertScrollbar do Position := Position + 1
  else if (Key = VK_DOWN) and (Shift = []) then
    with VertScrollbar do Position := Position + Increment
  else if (Key = VK_DOWN) and (Shift = [ssCtrl]) then
    with VertScrollbar do Position := Position + ClientHeight
  else if (Key = VK_NEXT) and (Shift = []) then
    CurrentPage := CurrentPage + 1
  else if (Key = VK_NEXT) and (Shift = [ssCtrl]) then
    CurrentPage := TotalPages
  else if (Key = VK_PRIOR) and (Shift = []) then
    CurrentPage := CurrentPage - 1
  else if (Key = VK_PRIOR) and (Shift = [ssCtrl]) then
    CurrentPage := 1
  else if (Key = VK_ADD) and (Shift = []) then
    Zoom := Zoom + ZoomStep
  else if (Key = VK_SUBTRACT) and (Shift = []) then
    Zoom := Zoom - ZoomStep
  else
    inherited;
end;

procedure TPrintPreview.WMMouseWheel(var Message: TMessage);
var
  IsNeg: Boolean;
  Rect: TRect;
  Pt: TPoint;
begin
  GetWindowRect(WindowHandle, Rect);
  Pt.X := LoWord(Message.LParam);
  Pt.Y := HiWord(Message.LParam);
  if PtInRect(Rect, Pt) then
  begin
    Message.Result := 1;
    Inc(WheelAccumulator, SmallInt(HiWord(Message.WParam)));
    while Abs(WheelAccumulator) >= WHEEL_DELTA do
    begin
      IsNeg := WheelAccumulator < 0;
      WheelAccumulator := Abs(WheelAccumulator) - WHEEL_DELTA;
      if IsNeg then
      begin
        WheelAccumulator := -WheelAccumulator;
        case LoWord(Message.WParam) of
          MK_CONTROL: Zoom := Zoom - ZoomStep;
          MK_SHIFT, MK_MBUTTON: CurrentPage := CurrentPage + 1;
          0: with VertScrollbar do Position := Position + Increment;
        else
          Message.Result := 0;
        end;
      end
      else
      begin
        case LoWord(Message.WParam) of
          MK_CONTROL: Zoom := Zoom + ZoomStep;
          MK_SHIFT, MK_MBUTTON: CurrentPage := CurrentPage - 1;
          0: with VertScrollbar do Position := Position - Increment;
        else
          Message.Result := 0;
        end;
      end;
    end;
  end;
end;

procedure TPrintPreview.PaperClick(Sender: TObject);
begin
  Click;
end;

procedure TPrintPreview.PaperDblClick(Sender: TObject);
begin
  DblClick;
end;

procedure TPrintPreview.PaperMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if not Focused and Enabled then SetFocus;
  FOldMousePos := Point(X, Y);
  //pvg begin
  if (Sender = FPaperView) and (FCanScrollHorz or FCanScrollVert) then
  begin
    FDraggingPage := True;
    FPaperView.Cursor := FPaperViewOptions.GrabCursor;
    FPaperView.Perform(WM_SETCURSOR, FPaperView.Handle, HTCLIENT);
  end;
  //pvg end
  MouseDown(Button, Shift, X, Y);
end;

procedure TPrintPreview.PaperMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
var
  Delta: TPoint;
begin
  MouseMove(Shift, X, Y);
  if ssLeft in Shift then
  begin
    if FCanScrollHorz then
    begin
      Delta.X := X - FOldMousePos.X;
      if not (AutoScroll and HorzScrollBar.Visible) then
      begin
        if FPaperView.Left + Delta.X < ClientWidth - HorzScrollBar.Margin - FPaperView.Width then
          Delta.X := ClientWidth - HorzScrollBar.Margin - FPaperView.Width - FPaperView.Left
        else if FPaperView.Left + Delta.X > HorzScrollBar.Margin then
          Delta.X := HorzScrollBar.Margin - FPaperView.Left;
        FPaperView.Left := FPaperView.Left + Delta.X;
      end
      else
        HorzScrollBar.Position := HorzScrollBar.Position - Delta.X;
    end;
    if FCanScrollVert then
    begin
      Delta.Y := Y - FOldMousePos.Y;
      if not (AutoScroll and VertScrollBar.Visible) then
      begin
        if FPaperView.Top + Delta.Y < ClientHeight - VertScrollBar.Margin - FPaperView.Height then
          Delta.Y := ClientHeight - VertScrollBar.Margin - FPaperView.Height - FPaperView.Top
        else if FPaperView.Top + Delta.Y > VertScrollBar.Margin then
          Delta.Y := VertScrollBar.Margin - FPaperView.Top;
        FPaperView.Top := FPaperView.Top + Delta.Y;
      end
      else
        VertScrollBar.Position := VertScrollBar.Position - Delta.Y;
    end;
  end;
end;

procedure TPrintPreview.PaperMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  MouseUp(Button, Shift, X, Y);
  //pvg begin
  if FDraggingPage then
  begin
    FDraggingPage := False;
    FPaperView.Cursor := FPaperViewOptions.DragCursor;
  end;
  //pvg end
end;

procedure TPrintPreview.SetPrinterOptions;
var
  DeviceMode: THandle;
  Device, Driver, Port: array[0..MAX_PATH] of Char;
  PaperSize: TPoint;
  DriverInfo2: PDriverInfo2;
  DriverInfo2Size: DWORD;
  hPrinter: THandle;
begin
  Printer.GetPrinter(Device, Driver, Port, DeviceMode);
  with PDevMode(GlobalLock(DeviceMode))^ do
    try
      dmFields := dmFields or DM_PAPERSIZE;
      if IsCustomPaper then
      begin
        PaperSize.X := ConvertUnits(FPaperWidth, Screen.PixelsPerInch, FUnits, mmLoMetric);
        PaperSize.Y := ConvertUnits(FPaperHeight, Screen.PixelsPerInch, FUnits, mmLoMetric);
        if FOrientation = poLandscape then SwapValue(PaperSize.X, PaperSize.Y);
        dmPaperSize := DMPAPER_USER;
        dmFields := dmFields or DM_PAPERWIDTH;
        dmPaperWidth := PaperSize.X;
        dmFields := dmFields or DM_PAPERLENGTH;
        dmPaperLength := PaperSize.Y;
      end
      else
      begin
        dmPaperSize := PaperSizes[FPaperType].ID;
        dmFields := dmFields and not (DM_PAPERWIDTH or DM_PAPERLENGTH);
      end;
      dmFields := dmFields or DM_ORIENTATION;
      case FOrientation of
        poPortrait: dmOrientation := DMORIENT_PORTRAIT;
        poLandscape: dmOrientation := DMORIENT_LANDSCAPE;
      end;
    finally
      GlobalUnlock(DeviceMode);
    end;
  OpenPrinter(Device, hPrinter, nil);
  try
    GetPrinterDriver(hPrinter, nil, 2, nil, 0, DriverInfo2Size);
    GetMem(DriverInfo2, DriverInfo2Size);
    try
      GetPrinterDriver(hPrinter, nil, 2, DriverInfo2, DriverInfo2Size, DriverInfo2Size);
      StrPCopy(Driver, ExtractFileName(StrPas(DriverInfo2^.PDriverPath)));
    finally
      FreeMem(DriverInfo2, DriverInfo2Size);
    end;
  finally
    ClosePrinter(hPrinter);
  end;
  Printer.SetPrinter(Device, Driver, Port, DeviceMode);
end;

procedure TPrintPreview.GetPrinterOptions;
var
  DeviceMode: THandle;
  Device, Driver, Port: array[0..MAX_PATH] of Char;
  PaperSize: TPoint;
  Paper: TPaperType;
begin
  Printer.GetPrinter(Device, Driver, Port, DeviceMode);
  with PDevMode(GlobalLock(DeviceMode))^ do
    try
      if (dmFields and DM_ORIENTATION) = DM_ORIENTATION then
        case dmOrientation of
          DMORIENT_PORTRAIT: SetOrientation(poPortrait);
          DMORIENT_LANDSCAPE: SetOrientation(poLandscape);
        end;
      SetPaperType(pCustom);
      if (dmFields and DM_PAPERSIZE) = DM_PAPERSIZE then
      begin
        for Paper := Low(TPaperType) to High(TPaperType) do
          if PaperSizes[Paper].ID = dmPaperSize then
          begin
            SetPaperType(Paper);
            Break;
          end;
      end;
      if IsCustomPaper then
      begin
        PaperSize.X := dmPaperWidth;
        PaperSize.Y := dmPaperLength;
        if FOrientation = poLandscape then SwapValue(PaperSize.X, PaperSize.Y);
        FPaperWidth := ConvertUnits(PaperSize.X, Screen.PixelsPerInch, mmLoMetric, FUnits);
        FPaperHeight := ConvertUnits(PaperSize.Y, Screen.PixelsPerInch, mmLoMetric, FUnits);
        CalculateMetafileSize;
        UpdateZoom;
      end
    finally
      GlobalUnlock(DeviceMode);
    end;
end;

function TPrintPreview.GetPrintPageBounds: TRect;
var
  Ofs: TPoint;
  PageWidth, PageHeight: Integer;
begin
  DPI.X := GetDeviceCaps(Printer.Handle, LOGPIXELSX);
  DPI.Y := GetDeviceCaps(Printer.Handle, LOGPIXELSY);
  if not UsePrinterOptions then
  begin
    PageWidth := ConvertUnits(PaperWidth, DPI.X, Units, mmPixel);
    PageHeight := ConvertUnits(PaperHeight, DPI.Y, Units, mmPixel);
  end
  else
  begin
    PageWidth := GetDeviceCaps(Printer.Handle, PHYSICALWIDTH);
    PageHeight := GetDeviceCaps(Printer.Handle, PHYSICALHEIGHT);
  end;
  Ofs.X := GetDeviceCaps(Printer.Handle, PHYSICALOFFSETX);
  Ofs.Y := GetDeviceCaps(Printer.Handle, PHYSICALOFFSETY);
  SetRect(Result, -Ofs.X, -Ofs.Y, PageWidth - Ofs.X, PageHeight - Ofs.Y);
end;

procedure TPrintPreview.Resize;
begin
  inherited Resize;
  UpdateZoom;
end;

function TPrintPreview.CalculateViewSize(const Space: TPoint): TPoint;
begin
  with FPaperView do
  begin
    case FZoomState of
      zsZoomOther:
      begin
        Result.X := ActualWidth(MulDiv(FPixels.X, FZoom * Screen.PixelsPerInch, 100 * DPI.X));
        Result.Y := ActualHeight(MulDiv(FPixels.Y, FZoom * Screen.PixelsPerInch, 100 * DPI.Y));
      end;
      zsZoomToWidth:
      begin
        Result.X := Space.X;
        Result.Y := ActualHeight(MulDiv(LogicalWidth(Result.X), FPixels.Y, FPixels.X));
      end;
      zsZoomToHeight:
      begin
        Result.Y := Space.Y;
        Result.X := ActualWidth(MulDiv(LogicalHeight(Result.Y), FPixels.X, FPixels.Y));
      end;
      zsZoomToFit:
      begin
        if (FPixels.Y / FPixels.X) < (Space.Y / Space.X) then
        begin
          Result.X := Space.X;
          Result.Y := ActualHeight(MulDiv(LogicalWidth(Result.X), FPixels.Y, FPixels.X));
        end
        else
        begin
          Result.Y := Space.Y;
          Result.X := ActualWidth(MulDiv(LogicalHeight(Result.Y), FPixels.X, FPixels.Y));
        end;
      end;
    end;
    if FZoomState <> zsZoomOther then
      FZoom := Round((100 * LogicalHeight(Result.Y) * DPI.Y) / (FPixels.Y * Screen.PixelsPerInch));
  end;
end;

{$WARNINGS OFF}
procedure TPrintPreview.UpdateZoom;
var
  Space: TPoint;
  Percent: TPoint;
  ViewPos: TPoint;
  ViewSize: TPoint;
  OldZoom: Integer;
begin
  if csLoading in ComponentState then Exit;

  OldZoom := FZoom;

  Space.X := ClientWidth - 2 * HorzScrollBar.Margin;
  Space.Y := ClientHeight - 2 * VertScrollBar.Margin;

  if FZoomSavePos then
  begin
    Percent.X := MulDiv(HorzScrollbar.Position, 100, HorzScrollBar.Range - Space.X);
    if Percent.X < 0 then Percent.X := 0;
    Percent.Y := MulDiv(VertScrollbar.Position, 100, VertScrollbar.Range - Space.Y);
    if Percent.Y < 0 then Percent.Y := 0;
  end;

  if AutoScroll then
  begin
    {$IFDEF VER100}
    if HorzScrollBar.Visible and (GetWindowLong(Handle, GWL_STYLE) and SB_HORZ <> 0) then
    {$ELSE}
    if HorzScrollBar.IsScrollBarVisible then
    {$ENDIF}
      Inc(Space.Y, GetSystemMetrics(SM_CYHSCROLL));
    {$IFDEF VER100}
    if VertScrollBar.Visible and (GetWindowLong(Handle, GWL_STYLE) and SB_VERT <> 0) then
    {$ELSE}
    if VertScrollBar.IsScrollBarVisible then
    {$ENDIF}
      Inc(Space.X, GetSystemMetrics(SM_CXVSCROLL));
  end;

  DisableAutoRange;

  try

    HorzScrollbar.Position := 0;
    VertScrollbar.Position := 0;

    ViewSize := CalculateViewSize(Space);

    FCanScrollHorz := (ViewSize.X > Space.X);
    FCanScrollVert := (ViewSize.Y > Space.Y);

    if AutoScroll then
    begin
      if FCanScrollHorz then
      begin
         Dec(Space.Y, GetSystemMetrics(SM_CYHSCROLL));
         FCanScrollVert := (FPaperView.Height > Space.Y);
         if FCanScrollVert then
           Dec(Space.X, GetSystemMetrics(SM_CXVSCROLL));
         ViewSize := CalculateViewSize(Space);
      end
      else if FCanScrollVert then
      begin
         Dec(Space.X, GetSystemMetrics(SM_CXVSCROLL));
         FCanScrollHorz := (FPaperView.Width > Space.X);
         if FCanScrollHorz then
           Dec(Space.Y, GetSystemMetrics(SM_CYHSCROLL));
         ViewSize := CalculateViewSize(Space);
      end;
    end;

    ViewPos.X := HorzScrollBar.Margin;
    if not FCanScrollHorz then
      Inc(ViewPos.X, (Space.X - ViewSize.X) div 2);

    ViewPos.Y := VertScrollBar.Margin;
    if not FCanScrollVert then
      Inc(ViewPos.Y, (Space.Y - ViewSize.Y) div 2);

    FPaperView.SetBounds(ViewPos.X, ViewPos.Y, ViewSize.X, ViewSize.Y);

  finally
    EnableAutoRange;
  end;

  if FZoomSavePos and FCanScrollHorz then
    HorzScrollbar.Position := MulDiv(Percent.X, HorzScrollBar.Range - Space.X, 100);
  if FZoomSavePos and FCanScrollVert then
     VertScrollbar.Position := MulDiv(Percent.Y, VertScrollbar.Range - Space.Y, 100);

  FDraggingPage := False;
  if FCanScrollHorz or FCanScrollVert then
    FPaperView.Cursor := FPaperViewOptions.DragCursor
  else
    FPaperView.Cursor := FPaperViewOptions.Cursor;

  if (OldZoom <> FZoom) and Assigned(FOnZoomChange) then
    FOnZoomChange(Self);

end;
{$WARNINGS ON}

procedure TPrintPreview.PaintPage(Sender: TObject; Canvas: TCanvas; PageRect: TRect);
begin
  if (FCurrentPage >= 1) and (FCurrentPage <= TotalPages) then
    Canvas.StretchDraw(PageRect, TMetaFile(FPages[FCurrentPage-1]))
end;

procedure TPrintPreview.PaperViewOptionsChanged(Sender: TObject);
begin
  FPaperView.PaperColor := FPaperViewOptions.PaperColor;
  FPaperView.BorderColor := FPaperViewOptions.BorderColor;
  FPaperView.BorderSize := FPaperViewOptions.BorderWidth;
  FPaperView.ShadowColor := FPaperViewOptions.ShadowColor;
  FPaperView.ShadowSize := FPaperViewOptions.ShadowWidth;
  FPaperView.Cursor := FPaperViewOptions.Cursor;
  FPaperView.PopupMenu := FPaperViewOptions.PopupMenu;
  UpdateZoom;
end;

procedure TPrintPreview.PagesChanged(Sender: TObject);
begin
  if TotalPages = 0 then
  begin
    FCurrentPage := 0;
    FPaperView.Visible := False;
  end
  else if FCurrentPage = 0 then
  begin
    FCurrentPage := 1;
    FPaperView.Visible := True;
  end;
  FPaperView.Refresh;
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

procedure TPrintPreview.SetPaperViewOptions(Value: TPaperPreviewOptions);
begin
  FPaperViewOptions.Assign(Value);
end;

procedure TPrintPreview.SetUnits(Value: TUnits);
begin
  if FUnits <> Value then
  begin
    if FPaperType <> pCustom then
      with PaperSizes[FPaperType] do
      begin
        FPaperWidth := ConvertUnits(Width, Screen.PixelsPerInch, Units, Value);
        FPaperHeight := ConvertUnits(Height, Screen.PixelsPerInch, Units, Value);
      end
    else
    begin
      FPaperWidth := ConvertUnits(FPaperWidth, Screen.PixelsPerInch, FUnits, Value);
      FPaperHeight := ConvertUnits(FPaperHeight, Screen.PixelsPerInch, FUnits, Value);
    end;
    Font.Height := ConvertUnits(Font.Height, Screen.PixelsPerInch, FUnits, Value);
    if Assigned(FCanvas) then
    begin
      AdjustCanvasView;
      FCanvas.Font.Height := ConvertUnits(FCanvas.Font.Height, Screen.PixelsPerInch, FUnits, Value);
      FCanvas.Pen.Width := ConvertUnits(FCanvas.Pen.Width, Screen.PixelsPerInch, FUnits, Value);
    end;
    FUnits := Value;
  end;
end;

procedure TPrintPreview.SetPaperType(Value: TPaperType);
begin
  if (FPaperType <> Value) and (FState <> psCreating) then
  begin
    FPaperType := Value;
    if FPaperType <> pCustom then
    begin
      with PaperSizes[FPaperType] do
      begin
        FPaperWidth := ConvertUnits(Width, Screen.PixelsPerInch, Units, FUnits);
        FPaperHeight := ConvertUnits(Height, Screen.PixelsPerInch, Units, FUnits);
      end;
      if FOrientation = poLandscape then
        SwapValue(FPaperWidth, FPaperHeight);
      CalculateMetafileSize;
      UpdateZoom;
    end;
  end;
end;

procedure TPrintPreview.SetPaperWidth(Value: Integer);
begin
  if Value > High(SmallInt) then Value := High(SmallInt)
  else if Value < 1 then Value := 1;
  if (FPaperWidth <> Value) and (FState <> psCreating) then
  begin
    FPaperType := pCustom;
    FPaperWidth := Value;
    CalculateMetafileSize;
    UpdateZoom;
  end;
end;

procedure TPrintPreview.SetPaperHeight(Value: Integer);
begin
  if Value > High(SmallInt) then Value := High(SmallInt)
  else if Value < 1 then Value := 1;
  if (FPaperHeight <> Value) and (FState <> psCreating) then
  begin
    FPaperType := pCustom;
    FPaperHeight := Value;
    CalculateMetafileSize;
    UpdateZoom;
  end;
end;

function TPrintPreview.IsCustomPaper: Boolean;
begin
  Result := (FPaperType = pCustom);
end;

procedure TPrintPreview.SetOrientation(Value: TPrinterOrientation);
begin
  if (FOrientation <> Value) and (FState <> psCreating) then
  begin
    FOrientation := Value;
    SwapValue(FPaperWidth, FPaperHeight);
    CalculateMetafileSize;
    UpdateZoom;
  end;
end;

procedure TPrintPreview.SetZoom(Value: Integer);
var
  OldZoom: Integer;
begin
  if Value < FZoomMin then Value := FZoomMin
  else if Value > FZoomMax then Value := FZoomMax;
  if (FZoom <> Value) or (FZoomState <> zsZoomOther) then
  begin
    OldZoom := FZoom;
    FZoom := Value;
    FZoomState := zsZoomOther;
    UpdateZoom;
    if not FPaperView.OffScreenOK then
    begin
      FZoom := OldZoom;
      UpdateZoom;
    end
    else if Assigned(FOnZoomChange) then
      FOnZoomChange(Self);
  end;
end;

function TPrintPreview.IsZoomStored: Boolean;
begin
  Result := (FZoomState = zsZoomOther) and (FZoom <> 100);
end;

procedure TPrintPreview.SetZoomMin(Value: Integer);
begin
  if (FZoomMin <> Value) and (Value >= 1) and (Value <= FZoomMax) then
  begin
    FZoomMin := Value;
    if (FZoomState = zsZoomOther) and (FZoom < FZoomMin) then
      Zoom := FZoomMin;
  end;
end;

procedure TPrintPreview.SetZoomMax(Value: Integer);
begin
  if (FZoomMax <> Value) and (Value >= FZoomMin) then
  begin
    FZoomMax := Value;
    if (FZoomState = zsZoomOther) and (FZoom > FZoomMax) then
      Zoom := FZoomMax;
  end;
end;

procedure TPrintPreview.SetZoomState(Value: TZoomState);
begin
  if FZoomState <> Value then
  begin
    FZoomState := Value;
    UpdateZoom;
  end;
end;

procedure TPrintPreview.SetCurrentPage(Value: Integer);
begin
  if TotalPages <> 0 then
  begin
    if Value < 1 then Value := 1;
    if Value > TotalPages then Value := TotalPages;
    if FCurrentPage <> Value then
    begin
      FCurrentPage := Value;
      FPaperView.Refresh;
      if Assigned(FOnChange) then
        FOnChange(Self);
    end;
  end;
end;

function TPrintPreview.GetUseTempFile: Boolean;
begin
  Result := FPages.UseTempFile;
end;

procedure TPrintPreview.SetUseTempFile(Value: Boolean);
begin
  FPages.UseTempFile := Value;
end;

function TPrintPreview.GetTotalPages: Integer;
begin
  Result := FPages.Count;
end;

function TPrintPreview.GetPages(PageNo: Integer): TMetaFile;
begin
  if (PageNo >= 1) and (PageNo <= TotalPages) then
    Result := TMetaFile(FPages[PageNo-1])
  else
    Result := nil;
end;

function TPrintPreview.GetCanvas: TCanvas;
begin
  if (FState = psCreating) and Assigned(FCanvas) then
    Result := FCanvas
  else
    Result := Printer.Canvas;
end;

function TPrintPreview.GetPrinterInstalled: Boolean;
begin
  Result := (Printer.Printers.Count > 0);
end;

procedure TPrintPreview.AdjustCanvasView;
begin
  SetMapMode(FCanvas.Handle, MM_ANISOTROPIC);
  SetWindowExtEx(FCanvas.Handle, FPaperWidth, FPaperHeight, nil);
  SetViewPortExtEx(FCanvas.Handle, FPixels.X, FPixels.Y, nil);
end;

procedure TPrintPreview.CalculateMetafileSize;
begin
  if Printer.Printers.Count = 0 then
  begin
    DPI.X := Screen.PixelsPerInch;
    DPI.Y := Screen.PixelsPerInch;
  end
  else
  begin
    DPI.X := GetDeviceCaps(Printer.Handle, LOGPIXELSX);
    DPI.Y := GetDeviceCaps(Printer.Handle, LOGPIXELSY);
  end;
  FPixels.X := ConvertUnits(FPaperWidth, DPI.X, FUnits, mmPixel);
  FPixels.Y := ConvertUnits(FPaperHeight, DPI.Y, FUnits, mmPixel);
  Font.PixelsPerInch := DPI.Y;
end;

procedure TPrintPreview.CreateMetaFileCanvas;
begin
  Metafile := TMetafile.Create;
  try
    MetaFile.Width := FPixels.X;
    MetaFile.Height := FPixels.Y;
    if Printer.Printers.Count = 0 then
      FCanvas := TMetafileCanvas.Create(Metafile, 0)
    else
      FCanvas := TMetafileCanvas.Create(Metafile, Printer.Handle);
    if FCanvas.Handle = 0 then
    begin
      FCanvas.Free;
      FCanvas := nil;
      RaiseOutOfMemory;
    end;
  except
    MetaFile.Free;
    MetaFile := nil;
    raise;
  end;
  AdjustCanvasView;
  FCanvas.Font.PixelsPerInch := DPI.Y;
  FCanvas.Font.Assign(Font);
end;

procedure TPrintPreview.CloseMetaFileCanvas;
begin
  FCanvas.Free;
  FCanvas := nil;
  if MetaFile.Handle = 0 then
  begin
    MetaFile.Free;
    RaiseOutOfMemory;
  end;
end;

procedure TPrintPreview.Clear;
begin
  FPages.Clear;
end;

procedure TPrintPreview.BeginDoc;
begin
  if FState <> psCreating then
  begin
    Clear;
    FAborted := False;
    FState := psCreating;
    CalculateMetafileSize;
    if Assigned(FOnBeginDoc) then
      FOnBeginDoc(Self);
    NewPage;
  end;
end;

procedure TPrintPreview.EndDoc;
begin
  if FState = psCreating then
  begin
    CloseMetaFileCanvas;
    try
      FPages.Add(MetaFile);
    finally
      MetaFile.Free;
    end;
    if Assigned(FOnEndDoc) then
      FOnEndDoc(Self);
    FState := psReady;
  end;
end;

procedure TPrintPreview.NewPage;
begin
  if FState = psCreating then
  begin
    if Assigned(FCanvas) then
    begin
      CloseMetaFileCanvas;
      try
        FPages.Add(MetaFile);
      finally
        MetaFile.Free;
      end;
    end;
    CreateMetaFileCanvas;
    if Assigned(FOnNewPage) then
      FOnNewPage(Self);
  end;
end;

procedure TPrintPreview.Abort;
begin
  if not FAborted then
  begin
    case State of
      psCreating:
      begin
        FAborted := True;
        if Assigned(FOnAbort) then
          FOnAbort(Self);
        CloseMetaFileCanvas;
        if Assigned(MetaFile) then
          MetaFile.Free;
        Clear;
      end;
      psPrinting:
      begin
        FAborted := True;
        if Assigned(FOnAbort) then
          FOnAbort(Self);
        if Printer.Printing and not Printer.Aborted then
          Printer.Abort;
      end;
    end;
  end;
end;

procedure TPrintPreview.LoadFromStream(Stream: TStream);
begin
  FPages.LoadFromStream(Stream);
end;

procedure TPrintPreview.SaveToStream(Stream: TStream);
begin
  FPages.SaveToStream(Stream);
end;

procedure TPrintPreview.LoadFromFile(const FileName: String);
begin
  FPages.LoadFromFile(FileName);
end;

procedure TPrintPreview.SaveToFile(const FileName: String);
begin
  FPages.SaveToFile(FileName);
end;

procedure TPrintPreview.Print;
begin
  PrintPages(1, TotalPages);
end;

procedure TPrintPreview.DoProgress(Current, Done, Total: Integer);
var
  Cencelled: Boolean;
begin
  Cencelled := FAborted;
  if not FAborted and Assigned(FOnPrintProgress) then
    FOnPrintProgress(Self, Current, MulDiv(100, Done, Total), Cencelled);
  if not FAborted and Cencelled then
    Abort;
end;

procedure TPrintPreview.PrintPages(FirstPage, LastPage: Integer);

  procedure FixPageRange;
  begin
    if FirstPage < 1 then FirstPage := 1;
    if FirstPage > TotalPages then FirstPage := TotalPages;
    if LastPage < 1 then LastPage := 1;
    if LastPage > TotalPages then LastPage := TotalPages;
  end;

  function InitializePrinter: TRect;
  begin
    if Assigned(FOnBeforePrint) then
      FOnBeforePrint(Self);
    if not UsePrinterOptions then
      SetPrinterOptions;
    Result := GetPrintPageBounds;
    Printer.Title := PrintJobTitle;
    Printer.BeginDoc;
  end;

  procedure FinalizePrinter(Succeed :Boolean);
  begin
    FAborted := FAborted or not Succeed;
    if not Succeed and Printer.Printing then
      Printer.Abort;
    if Printer.Printing then
      Printer.EndDoc;
    Printer.Title := EmptyStr;
    if Assigned(FOnAfterPrint) then
      FOnAfterPrint(Self);
  end;

var
  CurPage: Integer;
  PrintRect: TRect;
  Done: Boolean;
begin
  if (FState = psReady) and (TotalPages > 0) and (FirstPage <= LastPage) and
     (Printer.Printers.Count > 0) then
  begin
    Done := False;
    FAborted := False;
    FState := psPrinting;
    try try
      PrintRect := InitializePrinter;
      CurPage := FirstPage;
      while not FAborted and (CurPage <= LastPage) do
      begin
        DoProgress(CurPage, CurPage - FirstPage, LastPage - FirstPage + 1);
        if not FAborted then
        begin
          if FFastPrint then
            Printer.Canvas.StretchDraw(PrintRect, TMetaFile(FPages[CurPage-1]))
          else
            DrawGraphicAsDIB(Printer.Canvas.Handle, PrintRect, TMetaFile(FPages[CurPage-1]));
        end;
        DoProgress(CurPage, CurPage - FirstPage + 1, LastPage - FirstPage + 1);
        if not FAborted then
        begin
          if CurPage < LastPage then
            Printer.NewPage
          else
            Done := True;
        end;
        Inc(CurPage);
      end;
    finally
      FinalizePrinter(Done);
      FState := psReady;
    end;
    except
      on EAbort do
        // Do nothing
      else
        raise;
    end;
  end;
end;

procedure Register;
begin
  RegisterComponents('RbReport', [TPaperPreview, TPrintPreview]);
end;

initialization
  Screen.Cursors[crHand] := LoadCursor(hInstance, 'CURSOR_HAND');
  Screen.Cursors[crGrab] := LoadCursor(hInstance, 'CURSOR_GRAB');
end.

