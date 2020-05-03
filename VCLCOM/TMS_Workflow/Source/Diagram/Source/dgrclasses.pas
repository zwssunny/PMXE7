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

unit DgrClasses;

interface

{$I DIAGRAM.INC}

uses
  SysUtils, Windows, Classes, Graphics, DiagramUtils;

type
  TDgrBlockDrawer = class;
  TDgrBrush = class;
  TDgrCanvas = class;
  TDgrGraphic = class;
  TDgrGraphicsObject = class;
  TDgrGraphicsPath = class;
  TDgrImage = class;
  TDgrPaintEngine = class;
  TDgrPen = class;
  TDgrPicture = class;
  TDgrRegion = class;

  TDgrBlockDrawerClass = class of TDgrBlockDrawer;
  TDgrPaintEngineClass = class of TDgrPaintEngine;

  TDgrBrushMode = (bmSolid, bmClear, bmHatch, bmGradient, bmTexture);
  TDgrGradientMode = (gmTopBottom, gmBottomTop, gmLeftRight, gmRightLeft,
    gmLeftTop, gmRightTop, gmLeftBottom, gmRightBottom, gmInOut, gmOutIn,
    gmHorzInOut, gmHorzOutIn, gmVertInOut, gmVertOutIn);
  TDgrGraphicLib = (dglGDI, dglGDIPlus {$IFDEF DELPHI2010_LVL}, dglDirect2D{$ENDIF});
  TDgrPageUnit =  (dpuWorld, dpuDisplay, dpuPixel, dpuPoint, dpuInch, dpuDocument, dpuMillimeter);
  TDgrSmoothMode = (smAntiAlias, smInactive, smHighSpeed, smHighQuality);
  TDgrTextRenderingMode = (tmAntiAlias, tmAntiAliasHint, tmDefault, tmNormal, tmNormalHint, tmClearType);

  /// Description:
  ///   TDgrGraphic is a TGraphic descendant and ancestor for specific graphic library classes
  ///   (GDI+/Direct2D), which add support for several file formats (PNG, JPG, TIFF, GIF, etc).
  TDgrGraphic = class(TGraphic)
  private
    FDatastream: TMemoryStream;
    FIsEmpty: Boolean;
    FWidth: integer;
    FHeight: integer;
  protected
    procedure DoDraw(ACanvas: TCanvas; const Rect: TSquare); virtual;
    function DoGetImageSizes: Boolean; virtual; abstract;

    /// Description:
    ///   Implements the TGraphic ancestor method.
    function GetEmpty: Boolean; override;
    procedure SetEmpty(const Value: boolean);

    /// Description:
    ///   Implements the TGraphic ancestor method.
    function GetHeight: integer; override;

    /// Description:
    ///   Implements the TGraphic ancestor method.
    function GetWidth: integer; override;

    /// Description:
    ///   Implements the TGraphic ancestor method.
    procedure SetHeight(Value: integer); override;

    /// Description:
    ///   Implements the TGraphic ancestor method.
    procedure SetWidth(Value: integer); override;

    /// Description:
    ///   Implements the TGraphic ancestor method.
    procedure ReadData(Stream: TStream); override;

    /// Description:
    ///   Implements the TGraphic ancestor method.
    procedure WriteData(Stream: TStream); override;

    /// Description:
    ///   Called when the graphic is changed.
    procedure Changed(Sender: TObject); override;

    property DataStream: TMemoryStream read FDatastream;
  public
    /// Description:
    ///   Creates the object.
    constructor Create; override;

    /// Description:
    ///   Destroys the object.
    destructor Destroy; override;

    /// Description:
    ///   Assigned a graphic object.
    procedure Assign(Source: TPersistent); override;

    /// Description:
    ///   Implements drawing of image. Same as TGraphic.Draw.
    procedure Draw(ACanvas: TCanvas; const Rect: TRect); override;

    /// Description:
    ///   Loads the image from file.
    procedure LoadFromFile(const FileName: string); override;

    /// Description:
    ///   Loads the image from stream.
    procedure LoadFromStream(Stream: TStream); override;

    /// Description:
    ///   Saves the image to a stream.
    procedure SaveToStream(Stream: TStream); override;

    /// Description:
    ///   Loads the image from clipboard.
    procedure LoadFromClipboardFormat(AFormat: Word; AData: THandle;
      APalette: HPALETTE); override;

    /// Description:
    ///   Saves the image to clipboard.
    procedure SaveToClipboardFormat(var AFormat: Word; var AData: THandle;
      var APalette: HPALETTE); override;

    /// Description:
    ///   Updates the image size information.
    function GetImageSizes: boolean; virtual;
  end;

  /// Description:
  ///   TDgrPicture is a TPicture descendant and ancestor for specific graphic library classes
  ///   (GDI+/Direct2D), which uses APIs for drawing the pictures and implements transparency.
  TDgrPicture = class(TPicture)
  private
    FDatastream: TMemoryStream;
    FTransparency: integer;
    procedure SetTransparency(const Value: integer);
  protected
    procedure Changed(Sender: TObject); override;
    property DataStream: TMemoryStream read FDatastream;
  public
    constructor Create; virtual;
    destructor Destroy; override;
  published

    /// Description:
    ///   Specifies the transparency of the picture.
    property Transparency: integer read FTransparency write SetTransparency;
  end;

  /// Description:
  ///   TDgrGraphicsObject is the base class for specific graphic library classes
  ///   (GDI+/Direct2D), implements graphic objects used with Canvas, like brushes and pens.
  TDgrGraphicsObject = class(TPersistent)
  private
    FOnChange: TNotifyEvent;
  protected

    /// Description:
    ///   Change method is called when a property of object changes.
    procedure Change; virtual;
  public

    /// Description:
    ///   OnChange is fired when a property of object is changed.
    property OnChange: TNotifyEvent read FOnChange write FOnChange;
  end;

  /// Description:
  ///   TDgrBrush is the base brush class for specific graphic library classes (GDI+/Direct2D),
  ///   (just like TBrush in TCanvas).
  TDgrBrush = class(TDgrGraphicsObject)
  private
    FColor: TColor;
    FTransparency: integer;
    FBrushMode: TDgrBrushMode;
    FColor2: TColor;
    FGradientMode: TDgrGradientMode;
    FTexture: TDgrPicture;
    FTransp1: integer;
    FTransp2: integer;
    procedure SetColor(const Value: TColor);
    procedure SetTransparency(const Value: integer);
    procedure SetBrushMode(const Value: TDgrBrushMode);
    procedure SetColor2(const Value: TColor);
    procedure SetGradientMode(const Value: TDgrGradientMode);
    procedure SetTexture(const Value: TDgrPicture);
    procedure ItemChange(Sender: TObject);
  protected
    function GetAlpha1: byte;
    function GetAlpha2: byte;
    procedure Change; override;
    function CreatePicture: TDgrPicture; virtual; abstract;
    procedure DoUpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot); virtual; abstract;
  public
    constructor Create; virtual;
    destructor Destroy; override;

    /// Description:
    ///   Assigns values from other TDgrBrush object. You can also assign from a regular TBrush object,
    ///   it will convert the properties so that TDgrBrush descendant will look closest to the original TBrush.
    procedure Assign(Source: TPersistent); override;

    /// Description:
    ///   For internal use only.
    procedure UpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot);
  published

    /// Description:
    ///   Color of the brush. Also used as first color for hatch and gradient brush modes.
    property Color: TColor read FColor write SetColor default clWhite;

    /// Description:
    ///   Used as the secondary color for hatch and gradient brush modes.
    property Color2: TColor read FColor2 write SetColor2;

    /// Description:
    ///   Specifies the transparency of the brush, ranging from 0 (total opaque) to 100 (total transparent).
    property Transparency: integer read FTransparency write SetTransparency default 0;

    /// Description:
    ///   Specifies the mode of the current brush.
    property BrushMode: TDgrBrushMode read FBrushMode write SetBrushMode;

    /// Description:
    ///   Specified the gradient mode when BrushMode is gradient.
    property GradientMode: TDgrGradientMode read FGradientMode write SetGradientMode;

    /// Description:
    ///   Specifies a picture to be use as texture, when BrushMode is bmTexture.
    property Texture: TDgrPicture read FTexture write SetTexture;
  end;

  /// Description:
  ///   TDgrPen is the base pen class for specific graphic library classes (GDI+/Direct2D),
  ///   (just like TPen in TCanvas).
  TDgrPen = class(TDgrGraphicsObject)
  private
    FWidth: number;
    FColor: TColor;
    FTransparency: integer;
    procedure SetColor(const Value: TColor);
    procedure SetWidth(const Value: number);
    procedure SetTransparency(const Value: integer);
  protected
    procedure Change; override;
    function GetAlpha: byte;
  public
    constructor Create; virtual;
    destructor Destroy; override;

    /// Description:
    ///   Assigns values from other TDgrPen object. You can also assign from a regular TPen object, it will
    ///   convert the properties so that TDgrPen descendant will look closest to the original TPen.
    procedure Assign(Source: TPersistent); override;
  published

    /// Description:
    ///   Specified the color of the pen.
    property Color: TColor read FColor write SetColor default clBlack;

    /// Description:
    ///   Specifies the transparency of the pen, ranging from 0 (total opaque) to 100 (total transparent).
    property Transparency: integer read FTransparency write SetTransparency;

    /// Description:
    ///   Specifies the width of the pen.
    property Width: number read FWidth write SetWidth;
  end;

  /// Description:
  ///   TDgrCanvas is the base Canvas class for specific graphic library classes (TGPCanvas for GDI+, TD2DCanvas
  ///   for Direct2D). TDgrCanvas does not descend from TCanvas, it just implements methods with similar names.
  TDgrCanvas = class(TPersistent)
  private
    State: TCanvasState;
    FDestRect: TSquare;
    FSourceRect: TSquare;
    FTranslateRects: Boolean;
    FValidRects: Boolean;
    FAngle: number;
    FRotCenter: TDot;
    FScaleX: number;
    FScaleY: number;
    procedure SetPen(const Value: TDgrPen);
    procedure SetBrush(const Value: TDgrBrush);
    procedure SetDestRect(const Value: TSquare);
    procedure SetSourceRect(const Value: TSquare);
    procedure UpdateFactors;
    // procedure SetTranslateRects(const Value: boolean);
    procedure SetRotCenter(const Value: TDot);
    procedure SetAngle(const Value: number);
    // FHandle: HDC;
    // FFont: TFont;
    // FPen: TPen;
    // FBrush: TBrush;
    // FPenPos: TPoint;
    // FCopyMode: TCopyMode;
    // FOnChange: TNotifyEvent;
    // FOnChanging: TNotifyEvent;
    // FLock: TRTLCriticalSection;
    // FLockCount: Integer;
    // FTextFlags: Longint;
    // procedure CreateBrush;
    // procedure CreateFont;
    // procedure CreatePen;
    // procedure BrushChanged(ABrush: TObject);
    // procedure DeselectHandles;
    // function GetCanvasOrientation: TCanvasOrientation;
    // function GetClipRect: TRect;
    // function GetHandle: HDC;
    // function GetPenPos: TPoint;
    // function GetPixel(X, Y: Integer): TColor;
    // procedure FontChanged(AFont: TObject);
    // procedure PenChanged(APen: TObject);
    // procedure SetBrush(Value: TBrush);
    // procedure SetFont(Value: TFont);
    // procedure SetHandle(Value: HDC);
    // procedure SetPen(Value: TPen);
    // procedure SetPenPos(Value: TPoint);
    // procedure SetPixel(X, Y: Integer; Value: TColor);
  protected
    procedure Changed; virtual;
    procedure Changing; virtual;
    procedure DoDrawEllipse(x, y, Width, height: number); virtual; abstract;
    procedure DoDrawLine(X1, Y1, X2, Y2: number); virtual; abstract;
    procedure DoDrawPath(APath: TDgrGraphicsPath); virtual; abstract;
    procedure DoDrawRectangle(x, y, Width, height: number); virtual; abstract;
    procedure DoFillPath(APath: TDgrGraphicsPath); virtual; abstract;
    procedure DoPolygon(APoints: TDotArray); virtual; abstract;
    procedure DoStretchDraw(const Rect: TSquare; Graphic: TGraphic;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False); overload; virtual; abstract;
    procedure DoStretchDraw(const Rect: TSquare; ADgrImage: TDgrImage;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False);
      overload; virtual; abstract;
    procedure DoUpdateFactors(ASourceRect, ADestRect: TSquare;
      AScaleX, AScaleY: number); virtual; abstract;
    // procedure CreateHandle; virtual;
    function GetBrush: TDgrBrush; virtual; abstract;
    function GetHandle: HDC; virtual;
    function GetPen: TDgrPen; virtual; abstract;
    function MustTranslateRects: Boolean;
    function PX(x: number): number;
    function PY(y: number): number;
    function PP(D: TDot): TDot; overload;
    function PP(S: TSquare): TSquare; overload;
    function SX(x: number): number;
    function SY(y: number): number;
    procedure SetHandle(const Value: HDC); virtual;
    procedure RequiredState(ReqState: TCanvasState);
    property SourceRect: TSquare read FSourceRect write SetSourceRect;
    property DestRect: TSquare read FDestRect write SetDestRect;
    property RotationCenter: TDot read FRotCenter write SetRotCenter;
    property Angle: number read FAngle write SetAngle;
  public
    constructor Create(AHandle: HDC = 0); virtual;
    destructor Destroy; override;
    function CreateBrush: TDgrBrush; virtual; abstract;
    function CreateGraphic: TDgrGraphic; virtual; abstract;
    function CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine; virtual; abstract;
    function CreatePath: TDgrGraphicsPath; virtual; abstract;
    function CreatePen: TDgrPen; virtual; abstract;
    procedure ClipRegion(ARegion: TDgrRegion); virtual;
    // procedure Arc(X1, Y1, X2, Y2, X3, Y3, X4, Y4: number);
    // procedure BrushCopy(const Dest: TRect; Bitmap: TBitmap; const Source: TRect; Color: TColor);
    // procedure Chord(X1, Y1, X2, Y2, X3, Y3, X4, Y4: number);
    // procedure CopyRect(const Dest: TRect; Canvas: TCanvas; const Source: TRect);
    // procedure Draw(X, Y: number; Graphic: TGraphic);
    // procedure DrawFocusRect(const Rect: TRect);
    procedure Ellipse(X1, Y1, X2, Y2: number);
    // procedure Ellipse(const Rect: TRect); overload;
    // procedure FillRect(const Rect: TRect);
    // procedure FloodFill(X, Y: number; Color: TColor; FillStyle: TFillStyle);
    // procedure FrameRect(const Rect: TRect);
    // procedure LineTo(X, Y: number);
    // procedure Lock;
    // procedure MoveTo(X, Y: number);
    // procedure Pie(X1, Y1, X2, Y2, X3, Y3, X4, Y4: number);
    procedure Polygon(const Points: TDotArray); overload;
    // procedure Polygon(const Points: TPointArray); overload;
    // procedure Polyline(const Points: array of TPoint);
    // procedure PolyBezier(const Points: array of TPoint);
    // procedure PolyBezierTo(const Points: array of TPoint);
    procedure Rectangle(X1, Y1, X2, Y2: number); overload;
    // procedure Rectangle(const Rect: TRect); overload;
    // procedure Refresh;
    procedure RoundRect(X1, Y1, X2, Y2, X3, Y3: number);
    procedure AddRoundRectPath(APath: TDgrGraphicsPath; X1, Y1, X2, Y2, X3, Y3: number);
    procedure Path(APath: TDgrGraphicsPath);
    procedure DrawPath(APath: TDgrGraphicsPath);
    procedure DrawLine(X1, Y1, X2, Y2: number);
    procedure StretchDraw(const ARect: TSquare; Graphic: TGraphic;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False); overload;
    procedure StretchDraw(const ARect: TSquare; ADgrImage: TDgrImage;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False); overload;
    // function TextExtent(const Text: string): TSize;
    // function TextHeight(const Text: string): number;
    // procedure TextOut(X, Y: number; const Text: string);
    // procedure TextRect(Rect: TRect; X, Y: number; const Text: string);
    // function TextWidth(const Text: string): number;
    // function TryLock: Boolean;
    // procedure Unlock;
    procedure RestoreDrawingState; virtual; abstract;
    procedure SaveDrawingState; virtual; abstract;
    function StringBounds(AStr: string; AFont: TFont; ARect: TSquare;
      AHAlign: TAlignment; AVAlign: TVertAlign; AWrap, ARightToLeft: Boolean)
      : TSquare; virtual; abstract;
    procedure DrawString(AStr: string; AFont: TFont; ARect: TSquare;
      AHAlign: TAlignment; AVAlign: TVertAlign; AWrap, ARightToLeft: Boolean;
      ATransparency: integer); virtual; abstract;
    function TranslateTransform(AX, AY: number): integer; virtual;
    function ScaleTransform(AX, AY: number): integer; virtual;
    function ResetClip: integer; virtual;
    function ResetTransform: integer; virtual;
    function RotateTransform(AAngle: number): integer; overload; virtual;
    function RotateTransform(AAngle: number; ARotCenter: TDot): integer; overload; virtual;
    function SetClip(ARect: TSquare): integer; overload; virtual;
    function SetClip(ARegion: HRGN): integer; overload; virtual;

    property Handle: HDC read GetHandle write SetHandle;
    // property LockCount: Integer read FLockCount;
    // property CanvasOrientation: TCanvasOrientation read GetCanvasOrientation;
    // property PenPos: TPoint read GetPenPos write SetPenPos;
    // property Pixels[X, Y: Integer]: TColor read GetPixel write SetPixel;
    // property TextFlags: Longint read FTextFlags write FTextFlags;
    // property OnChange: TNotifyEvent read FOnChange write FOnChange;
    // property OnChanging: TNotifyEvent read FOnChanging write FOnChanging;
    // property TranslateRects: boolean read FTranslateRects write SetTranslateRects;
    // property TransMatrix: TGPMatrix read FTransMatrix;
  published
    // property Brush: TBrush read FBrush write SetBrush;
    // property CopyMode: TCopyMode read FCopyMode write FCopyMode default cmSrcCopy;
    // property Font: TFont read FFont write SetFont;
    property Pen: TDgrPen read GetPen write SetPen;
    property Brush: TDgrBrush read GetBrush write SetBrush;
  end;

  /// Description:
  ///   TDgrBlockDrawer is the base Drawer class for specific graphic library classes (TGPBlockDrawer
  ///   for GDI+, TD2DBlockDrawer for Direct2D). TDgrBlockDrawer descendants implements methods and
  ///   properties to make it easy to draw blocks using GDI+/Direct2D API and converting coordinates.
  TDgrBlockDrawer = class
  private
    // FMatrix: TGPMatrix;
    // FAngle: number;
    // FRotCenter: TDot;
  protected
    procedure DoRotatePath(APath: TDgrGraphicsPath); virtual; abstract;
    function GetCanvas: TDgrCanvas; virtual; abstract;
    procedure SetPaintEngine(const Value: TDgrPaintEngine); virtual; abstract;
    function GetDestRect: TSquare;
    function GetSourceRect: TSquare;
    procedure SetDestRect(const Value: TSquare);
    procedure SetSourceRect(const Value: TSquare);
    function GetRotCenter: TDot;
    procedure SetRotCenter(const Value: TDot);
    function GetAngle: number;
    procedure SetAngle(const Value: number);
  public
    constructor Create; virtual;                            
    destructor Destroy; override;
    function CreateBrush: TDgrBrush;
    function CreateGraphic: TDgrGraphic;
    function CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine;
    function CreatePath: TDgrGraphicsPath;
    function CreatePen: TDgrPen;
    procedure SetDeviceContext(AHandle: HDC);
    procedure RotatePath(APath: TDgrGraphicsPath);
    procedure TranslateRectsPath(APath: TDgrGraphicsPath); virtual;
    procedure TransformPath(APath: TDgrGraphicsPath);
    property Angle: number read GetAngle write SetAngle;
    property Canvas: TDgrCanvas read GetCanvas;
    property DestRect: TSquare read GetDestRect write SetDestRect;
    property RotationCenter: TDot read GetRotCenter write SetRotCenter;
    property SourceRect: TSquare read GetSourceRect write SetSourceRect;
    property PaintEngine: TDgrPaintEngine write SetPaintEngine;
  end;

  /// Description:
  ///   TDgrGraphicsPath is the base Path class for specific graphic library classes
  ///   (TGdipGraphicsPath for GDI+, TD2DGraphicsPath for Direct2D).
  TDgrGraphicsPath = class
  public
    function AddArc(x, y, Width, height, startAngle, sweepAngle: number): integer; virtual; abstract;
    function AddBezier(X1, Y1, X2, Y2, X3, Y3, x4, y4: number): integer; virtual; abstract;
    function AddEllipse(x, y, Width, height: number): integer; virtual; abstract;
    function AddLine(X1, Y1, X2, Y2: number): integer; virtual; abstract;
    function AddLines(Points: TDotArray): integer; virtual; abstract;
    function AddPolygon(Points: TDotArray): integer; virtual; abstract;
    function AddRectangle(Rect: TSquare): integer; virtual; abstract;
    function AddRoundRect(X1, Y1, X2, Y2, X3, Y3: number): integer; virtual; abstract;
    function CloseFigure(AClosePath: boolean=True): integer; virtual; abstract;
    function CreateRegion: TDgrRegion; virtual; abstract;
    function GetPointCount: integer; virtual; abstract;
    function IsVisible(x, y: integer): Boolean; virtual; abstract;
    function Reset: integer; virtual; abstract;
    function SetFillMode(fillmode: TFillMode): integer; virtual; abstract;
    function StartFigure: integer; virtual; abstract;
  end;

  TDgrImage = class
  end;

  /// Description:
  ///   TDgrPaintEngine is a base class for specific graphic library drawing classes
  ///   (uses TGPGraphics for GDI+, and TDirect2DCanvas for Direct2D).
  TDgrPaintEngine = class
  private
    FSmoothMode: TDgrSmoothMode;
    FTextRenderingMode: TDgrTextRenderingMode;
    FPageUnit: TDgrPageUnit;
  protected
    procedure SetPageUnit(const Value: TDgrPageUnit); virtual;
    procedure SetSmoothMode(const Value: TDgrSmoothMode); virtual;
    procedure SetTextRenderingMode(const Value: TDgrTextRenderingMode); virtual;
  public
    constructor Create(ACanvas: TCanvas; ARect: TRect); virtual; abstract;
    procedure BeginDraw; virtual;
    procedure EndDraw; virtual;
    procedure FillRect(ARect: TRect; AColor: TColor); virtual; abstract;
    function ResetTransform: integer; virtual; abstract;
    function RotateTransform(AAngle: number): integer; virtual; abstract;
    function ScaleTransform(AX, AY: number): integer; virtual; abstract;
    function TranslateTransform(AX, AY: number): integer; virtual; abstract;
    property PageUnit: TDgrPageUnit read FPageUnit write SetPageUnit;
    property SmoothMode: TDgrSmoothMode read FSmoothMode write SetSmoothMode;
    property TextRenderingMode: TDgrTextRenderingMode read FTextRenderingMode write SetTextRenderingMode;
  end;

  /// Description:
  ///   TDgrRegion is the base Region class for specific graphic library classes
  ///   (TGdipRegion for GDI+, TD2DRegion for Direct2D).
  TDgrRegion = class
  public
    constructor Create(APath: TDgrGraphicsPath); virtual; abstract;
    function GetHRGN(ACanvas: TDgrCanvas): HRGN; virtual;
    function IsVisible(ARect: TSquare): boolean; virtual;
  end;

  /// Description:
  ///   DefaultGraphicLib function returns which graphic library TatDiagram uses by default
  ///   at current environment, according to what is supported by OS, conditional defines etc.
  function DefaultGraphicLib: TDgrGraphicLib;

implementation

{$IFDEF DELPHI2010_LVL}
uses
  Direct2D;
{$ENDIF}

function DefaultGraphicLib: TDgrGraphicLib;
begin
  {$IFDEF DELPHI2010_LVL}
  if TDirect2DCanvas.Supported then
    result := dglDirect2D
  else
  {$ENDIF}
  {$IFDEF GDIPLUS}
  result := dglGDIPlus;
  {$ELSE}
  result := dglGDI;
  {$ENDIF}
end;

{ TDgrCanvas }

constructor TDgrCanvas.Create(AHandle: HDC = 0);
begin
  SetHandle(AHandle);
  FTranslateRects := False;
  FValidRects := False;
end;

destructor TDgrCanvas.Destroy;
begin
  inherited;
end;

function TDgrCanvas.GetHandle: HDC;
begin
  result := 0;
end;

procedure TDgrCanvas.SetHandle(const Value: HDC);
begin
end;

procedure TDgrCanvas.RequiredState(ReqState: TCanvasState);
var
  NeededState: TCanvasState;
begin
  NeededState := ReqState - State;
  if NeededState <> [] then
  begin
    { if csHandleValid in NeededState then
      begin
      CreateHandle;
      if FHandle = 0 then
      raise EInvalidOperation.CreateRes(@SNoCanvasHandle);
      end; }
    // if csFontValid in NeededState then CreateFont;
    // if csPenValid in NeededState then CreatePen;
    // if csBrushValid in NeededState then CreateBrush;
    State := State + NeededState;
  end;
end;

function TDgrCanvas.ResetClip: integer;
begin
  result := 0;
end;

function TDgrCanvas.ResetTransform: integer;
begin
  result := 0;
end;

procedure TDgrCanvas.Polygon(const Points: TDotArray);
begin
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);

  DoPolygon(Points);

  Changed;
end;

procedure TDgrCanvas.AddRoundRectPath(APath: TDgrGraphicsPath; X1, Y1, X2, Y2, X3, Y3: number);
begin
  APath.StartFigure;
  APath.AddRoundRect(X1, Y1, X2, Y2, X3, Y3);
  APath.CloseFigure;
end;

function TDgrCanvas.RotateTransform(AAngle: number): integer;
begin
  result := 0;
end;

function TDgrCanvas.RotateTransform(AAngle: number; ARotCenter: TDot): integer;
begin
  TranslateTransform(ARotCenter.X, ARotCenter.Y);
  result := RotateTransform(AAngle);
  TranslateTransform(-ARotCenter.X, -ARotCenter.Y);
end;

procedure TDgrCanvas.RoundRect(X1, Y1, X2, Y2, X3, Y3: number);
var
  Path: TDgrGraphicsPath;
begin
  Changing;
  RequiredState([csHandleValid, csBrushValid, csPenValid]);
  X1 := PX(X1);
  Y1 := PY(Y1);
  X2 := PX(X2);
  Y2 := PY(Y2);
  X3 := SX(X3);
  Y3 := SY(Y3);

  Path := CreatePath;
  try
    AddRoundRectPath(Path, X1, Y1, X2, Y2, X3, Y3);
    DoFillPath(Path);
    DoDrawPath(Path);
  finally
    Path.Free;
  end;
  Changed;
end;

procedure TDgrCanvas.Changed;
begin
end;

procedure TDgrCanvas.Changing;
begin
end;

procedure TDgrCanvas.ClipRegion(ARegion: TDgrRegion);
begin
//
end;

procedure TDgrCanvas.SetPen(const Value: TDgrPen);
begin
  Pen.Assign(Value);
end;

procedure TDgrCanvas.SetBrush(const Value: TDgrBrush);
begin
  Brush.Assign(Value);
end;

function TDgrCanvas.SetClip(ARegion: HRGN): integer;
begin
  result := 0;
end;

function TDgrCanvas.SetClip(ARect: TSquare): integer;
begin
  result := 0;
end;

procedure TDgrCanvas.Ellipse(X1, Y1, X2, Y2: number);
begin
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);
  X1 := PX(X1);
  Y1 := PY(Y1);
  X2 := PX(X2);
  Y2 := PY(Y2);
  DoDrawEllipse(X1, Y1, X2 - X1, Y2 - Y1);
  Changed;
end;

procedure TDgrCanvas.Rectangle(X1, Y1, X2, Y2: number);
begin
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);
  X1 := PX(X1);
  Y1 := PY(Y1);
  X2 := PX(X2);
  Y2 := PY(Y2);
  DoDrawRectangle(X1, Y1, X2 - X1, Y2 - Y1);
  Changed;
end;

procedure TDgrCanvas.SetDestRect(const Value: TSquare);
begin
  FDestRect := Value;
  UpdateFactors;
end;

procedure TDgrCanvas.SetSourceRect(const Value: TSquare);
begin
  FSourceRect := Value;
  UpdateFactors;
end;

function TDgrCanvas.PX(x: number): number;
begin
  if MustTranslateRects then
    result := (x - FSourceRect.Left) * FScaleX + FDestRect.Left
  else
    result := x;
end;

function TDgrCanvas.PY(y: number): number;
begin
  if MustTranslateRects then
    result := (y - FSourceRect.Top) * FScaleY + FDestRect.Top
  else
    result := y;
end;

function TDgrCanvas.SX(x: number): number;
begin
  if MustTranslateRects then
    result := x * FScaleX
  else
    result := x;
end;

function TDgrCanvas.SY(y: number): number;
begin
  if MustTranslateRects then
    result := y * FScaleY
  else
    result := y;
end;

function TDgrCanvas.TranslateTransform(AX, AY: number): integer;
begin
  result := 0;
end;

function TDgrCanvas.PP(S: TSquare): TSquare;
begin
  result.Left := PX(S.Left);
  result.Top := PY(S.Top);
  result.Right := PX(S.Right);
  result.Bottom := PY(S.Bottom);
end;

function TDgrCanvas.PP(D: TDot): TDot;
begin
  result.x := PX(D.x);
  result.y := PY(D.y);
end;

procedure TDgrCanvas.UpdateFactors;
begin
  FValidRects := (FSourceRect.Right > FSourceRect.Left) and
    (FSourceRect.Bottom > FSourceRect.Top) and
    (FDestRect.Right > FDestRect.Left) and (FDestRect.Bottom > FDestRect.Top);
  if FValidRects then
  begin
    FScaleX := (FDestRect.Right - FDestRect.Left) /
      (FSourceRect.Right - FSourceRect.Left);
    FScaleY := (FDestRect.Bottom - FDestRect.Top) /
      (FSourceRect.Bottom - FSourceRect.Top);

    DoUpdateFactors(FSourceRect, FDestRect, FScaleX, FScaleY);
  end;
  Brush.UpdateBrushPosition(FDestRect, FAngle, FRotCenter);
end;

// procedure TDgrCanvas.SetTranslateRects(const Value: boolean);
// begin
// FTranslateRects := Value;
// //UpdateFactors; don't need it.
// end;

function TDgrCanvas.MustTranslateRects: Boolean;
begin
  result := FValidRects and FTranslateRects;
end;

procedure TDgrCanvas.Path(APath: TDgrGraphicsPath);
begin
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);
  DoFillPath(APath);
  DoDrawPath(APath);
  Changed;
end;

procedure TDgrCanvas.DrawPath(APath: TDgrGraphicsPath);
begin
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);
  DoDrawPath(APath);
  Changed;
end;

procedure TDgrCanvas.StretchDraw(const ARect: TSquare; Graphic: TGraphic;
  ATransparency: integer = 0; ABitmapTransparent: boolean=False);
begin
  DoStretchDraw(ARect, Graphic, ATransparency, ABitmapTransparent);
end;

procedure TDgrCanvas.StretchDraw(const ARect: TSquare; ADgrImage: TDgrImage;
  ATransparency: integer = 0; ABitmapTransparent: Boolean = False);
begin
  if ADgrImage <> nil then
  begin
    Changing;
    RequiredState([csHandleValid, csFontValid, csPenValid, csBrushValid]);

    DoStretchDraw(ARect, ADgrImage, ATransparency, ABitmapTransparent);

    Changed;
  end;
end;

procedure TDgrCanvas.SetRotCenter(const Value: TDot);
begin
  FRotCenter := Value;
  UpdateFactors;
end;

function TDgrCanvas.ScaleTransform(AX, AY: number): integer;
begin
  result := 0;
end;

procedure TDgrCanvas.SetAngle(const Value: number);
begin
  FAngle := Value;
  UpdateFactors;
end;

procedure TDgrCanvas.DrawLine(X1, Y1, X2, Y2: number);
begin
  Changing;
  RequiredState([csHandleValid, csPenValid]);
  X1 := PX(X1);
  Y1 := PY(Y1);
  X2 := PX(X2);
  Y2 := PY(Y2);
  DoDrawLine(X1, Y1, X2, Y2);
  Changed;
end;

{ TDgrPen }

procedure TDgrPen.Assign(Source: TPersistent);
begin
  if Source is TDgrPen then
  begin
    FColor := TDgrPen(Source).Color;
    FWidth := TDgrPen(Source).Width;
    FTransparency := TDgrPen(Source).Transparency;
    Change;
  end
  else if Source is TPen then
  begin
    FColor := TPen(Source).Color;
    FWidth := TPen(Source).Width;
    Change;
  end
  else
    inherited Assign(Source);
end;

procedure TDgrPen.Change;
begin
  inherited;
end;

constructor TDgrPen.Create;
begin
  FColor := clBlack;
  FWidth := 0.24;
  FTransparency := 0;
end;

destructor TDgrPen.Destroy;
begin
  inherited;
end;

procedure TDgrPen.SetTransparency(const Value: integer);
begin
  if FTransparency <> Value then
  begin
    FTransparency := Value;
    Change;
  end;
end;

procedure TDgrPen.SetColor(const Value: TColor);
begin
  if FColor <> Value then
  begin
    FColor := Value;
    Change;
  end;
end;

procedure TDgrPen.SetWidth(const Value: number);
begin
  if FWidth <> Value then
  begin
    FWidth := Value;
    Change;
  end;
end;

function TDgrPen.GetAlpha: byte;
begin
  result := round((100 - Transparency) * 2.55);
end;

{ TDgrBrush }

procedure TDgrBrush.Assign(Source: TPersistent);
begin
  if Source is TDgrBrush then
  begin
    FColor := TDgrBrush(Source).Color;
    FTransparency := TDgrBrush(Source).Transparency;
    FBrushMode := TDgrBrush(Source).BrushMode;
    FColor2 := TDgrBrush(Source).Color2;
    FGradientMode := TDgrBrush(Source).GradientMode;
    FTexture.Assign(TDgrBrush(Source).FTexture);
    Change;
  end
  else if Source is TBrush then
  begin
    FColor := TBrush(Source).Color;
    FTransp2 := 100;
    FBrushMode := bmHatch;
    case TBrush(Source).Style of
      bsSolid:
        FBrushMode := bmSolid;
      bsClear:
        FBrushMode := bmClear;
    end;
    Change;
  end
  else
    inherited Assign(Source);
end;

procedure TDgrBrush.Change;
begin
  inherited;
end;

constructor TDgrBrush.Create;
begin
  FBrushMode := bmSolid;
  FColor := clWhite;
  FTransparency := 0;
  FTexture := CreatePicture;
  FTexture.OnChange := ItemChange;
end;

destructor TDgrBrush.Destroy;
begin
  FTexture.Free;
  inherited;
end;

procedure TDgrBrush.SetTransparency(const Value: integer);
begin
  if FTransparency <> Value then
  begin
    FTransparency := Value;
    Change;
  end;
  FTransp1 := -1;
  FTransp2 := -1;
end;

procedure TDgrBrush.SetColor(const Value: TColor);
begin
  if FColor <> Value then
  begin
    FColor := Value;
    Change;
  end;
  FTransp1 := -1;
end;

function TDgrBrush.GetAlpha1: byte;
begin
  if FTransp1 = -1 then
    result := round((100 - Transparency) * 2.55)
  else
    result := round((100 - FTransp1) * 2.55)
end;

function TDgrBrush.GetAlpha2: byte;
begin
  if FTransp2 = -1 then
    result := round((100 - Transparency) * 2.55)
  else
    result := round((100 - FTransp2) * 2.55)
end;

procedure TDgrBrush.SetBrushMode(const Value: TDgrBrushMode);
begin
  if FBrushMode <> Value then
  begin
    FBrushMode := Value;
    Change;
  end;
end;

procedure TDgrBrush.SetColor2(const Value: TColor);
begin
  if FColor2 <> Value then
  begin
    FColor2 := Value;
    Change;
  end;
  FTransp2 := -1;
end;

procedure TDgrBrush.UpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot);
begin
  DoUpdateBrushPosition(ARect, AAngle, ARotCenter);
  Change;
end;

procedure TDgrBrush.SetGradientMode(const Value: TDgrGradientMode);
begin
  if FGradientMode <> Value then
  begin
    FGradientMode := Value;
    Change;
  end;
end;

procedure TDgrBrush.SetTexture(const Value: TDgrPicture);
begin
  FTexture.Assign(Value);
end;

procedure TDgrBrush.ItemChange(Sender: TObject);
begin
  Change;
end;

{ TDgrGraphicsObject }

procedure TDgrGraphicsObject.Change;
begin
  if Assigned(FOnChange) then
    FOnChange(Self);
end;

{ TGPBlockDrawer }

constructor TDgrBlockDrawer.Create;
begin
end;

function TDgrBlockDrawer.CreateBrush: TDgrBrush;
begin
  result := Canvas.CreateBrush;
end;

function TDgrBlockDrawer.CreateGraphic: TDgrGraphic;
begin
  result := Canvas.CreateGraphic;
end;

function TDgrBlockDrawer.CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine;
begin
  result := Canvas.CreatePaintEngine(ACanvas, ARect);
end;

function TDgrBlockDrawer.CreatePath: TDgrGraphicsPath;
begin
  result := Canvas.CreatePath;
end;

function TDgrBlockDrawer.CreatePen: TDgrPen;
begin
  result := Canvas.CreatePen;
end;

destructor TDgrBlockDrawer.Destroy;
begin
  inherited;
end;

function TDgrBlockDrawer.GetAngle: number;
begin
  result := Canvas.Angle;
end;

function TDgrBlockDrawer.GetDestRect: TSquare;
begin
  result := Canvas.DestRect;
end;

function TDgrBlockDrawer.GetRotCenter: TDot;
begin
  result := Canvas.RotationCenter;
end;

function TDgrBlockDrawer.GetSourceRect: TSquare;
begin
  result := Canvas.SourceRect;
end;

procedure TDgrBlockDrawer.RotatePath(APath: TDgrGraphicsPath);
begin
  if Angle <> 0 then
    DoRotatePath(APath);
end;

procedure TDgrBlockDrawer.TranslateRectsPath(APath: TDgrGraphicsPath);
begin
end;

procedure TDgrBlockDrawer.TransformPath(APath: TDgrGraphicsPath);
begin
  TranslateRectsPath(APath);
  RotatePath(APath);
end;

procedure TDgrBlockDrawer.SetAngle(const Value: number);
begin
  Canvas.Angle := Value;
end;

procedure TDgrBlockDrawer.SetDestRect(const Value: TSquare);
begin
  Canvas.DestRect := Value;
end;

procedure TDgrBlockDrawer.SetDeviceContext(AHandle: HDC);
begin
  Canvas.Handle := AHandle;
end;

procedure TDgrBlockDrawer.SetRotCenter(const Value: TDot);
begin
  Canvas.RotationCenter := Value;
end;

procedure TDgrBlockDrawer.SetSourceRect(const Value: TSquare);
begin
  Canvas.SourceRect := Value;
end;

{ TDgrPicture }

procedure TDgrPicture.Changed(Sender: TObject);
begin
end;

constructor TDgrPicture.Create;
begin
  inherited Create;
  FDatastream := TMemoryStream.Create;
  FTransparency := 0;
end;

destructor TDgrPicture.Destroy;
begin
  FDatastream.Free;
  inherited;
end;

procedure TDgrPicture.SetTransparency(const Value: integer);
begin
  if FTransparency <> Value then
  begin
    FTransparency := Value;
    Changed(Self);
  end;
end;

{ TDgrGraphic }

procedure TDgrGraphic.Assign(Source: TPersistent);

  procedure AssignFromGraphic(AGraphic: TGraphic);
  var
    st: TMemoryStream;
  begin
    st := TMemoryStream.Create;
    try
      AGraphic.SaveToStream(st);
      st.Position := 0;
      FDatastream.Clear;
      FDatastream.LoadFromStream(st);
    finally
      st.Free;
    end;
    FIsEmpty := False;
    Transparent := AGraphic.Transparent;
    Changed(Self);
  end;

begin
  FIsEmpty := True;
  if Source = nil then
  begin
    FDatastream.Clear;
    FIsEmpty := True;
    Changed(Self);
  end
  else if Source is TDgrGraphic then
  begin
    FDatastream.LoadFromStream(TDgrGraphic(Source).FDatastream);
    FIsEmpty := False;
    Changed(Self);
  end
  else if Source is TGraphic then
    AssignFromGraphic(TGraphic(Source))
  else if Source is TPicture then
    AssignFromGraphic(TPicture(Source).Graphic);

  GetImageSizes;
end;

constructor TDgrGraphic.Create;
begin
  inherited;
  FDatastream := TMemoryStream.Create;
  FIsEmpty := True;
end;

destructor TDgrGraphic.Destroy;
begin
  FDatastream.Free;
  inherited;
end;

procedure TDgrGraphic.Draw(ACanvas: TCanvas; const Rect: TRect);
begin
  if not Empty and (FDatastream.Size > 0) then
    DoDraw(ACanvas, Square(Rect));
end;

function TDgrGraphic.GetImageSizes: Boolean;
begin
  if not Empty and (FDatastream.Size > 0) then
    result := DoGetImageSizes
  else
    result := False;
end;

function TDgrGraphic.GetEmpty: Boolean;
begin
  result := FIsEmpty;
end;

function TDgrGraphic.GetHeight: integer;
begin
  result := FHeight;
end;

function TDgrGraphic.GetWidth: integer;
begin
  result := FWidth;
end;

procedure TDgrGraphic.LoadFromFile(const FileName: string);
begin
  try
    FDatastream.LoadFromFile(FileName);

    FIsEmpty := False;

    { if Assigned(OnClear) then
      OnClear(self); }

    GetImageSizes;

    Changed(Self);

  except
    FIsEmpty := True;
  end;
end;

procedure TDgrGraphic.LoadFromStream(Stream: TStream);
begin
  if Assigned(Stream) then
  begin
    FDatastream.Clear;
    FDatastream.CopyFrom(Stream, Stream.Size - Stream.Position);
    FIsEmpty := False;

    GetImageSizes;

    Changed(Self);
  end;
end;

procedure TDgrGraphic.ReadData(Stream: TStream);
begin
  if Assigned(Stream) then
  begin
    FDatastream.Clear;
    FDatastream.CopyFrom(Stream, Stream.Size - Stream.Position);
    FIsEmpty := False;
    GetImageSizes;
  end;
end;

procedure TDgrGraphic.SaveToStream(Stream: TStream);
begin
  if Assigned(Stream) then
  begin
    FDatastream.Position := 0;
    Stream.CopyFrom(FDatastream, FDatastream.Size - FDatastream.Position);
  end;
end;

procedure TDgrGraphic.SetEmpty(const Value: boolean);
begin
  FIsEmpty := Value;
end;

procedure TDgrGraphic.SetHeight(Value: integer);
begin
  {$IFDEF DELPHI6_LVL}
  inherited;
  {$ENDIF}
  FHeight := Value;
end;

procedure TDgrGraphic.SetWidth(Value: integer);
begin
  {$IFDEF DELPHI6_LVL}
  inherited;
  {$ENDIF}
  FWidth := Value;
end;

procedure TDgrGraphic.WriteData(Stream: TStream);
begin
  if Assigned(Stream) then
  begin
    FDatastream.Position := 0;
    Stream.CopyFrom(FDatastream, FDatastream.Size - FDatastream.Position);
  end;
end;

procedure TDgrGraphic.LoadFromClipboardFormat(AFormat: Word; AData: THandle; APalette: HPALETTE);
begin
end;

procedure TDgrGraphic.SaveToClipboardFormat(var AFormat: Word;
  var AData: THandle; var APalette: HPALETTE);
begin
end;

procedure TDgrGraphic.Changed(Sender: TObject);
begin
  inherited;
end;

procedure TDgrGraphic.DoDraw(ACanvas: TCanvas; const Rect: TSquare);
begin

end;

{ TDgrRegion }

function TDgrRegion.GetHRGN(ACanvas: TDgrCanvas): HRGN;
begin
  result := 0;
end;

function TDgrRegion.IsVisible(ARect: TSquare): boolean;
begin
  result := False;
end;

{ TDgrPaintEngine }

procedure TDgrPaintEngine.BeginDraw;
begin

end;

procedure TDgrPaintEngine.EndDraw;
begin

end;

procedure TDgrPaintEngine.SetPageUnit(const Value: TDgrPageUnit);
begin
  FPageUnit := Value;
end;

procedure TDgrPaintEngine.SetSmoothMode(const Value: TDgrSmoothMode);
begin
  FSmoothMode := Value;
end;

procedure TDgrPaintEngine.SetTextRenderingMode(const Value: TDgrTextRenderingMode);
begin
  FTextRenderingMode := Value;
end;

end.

