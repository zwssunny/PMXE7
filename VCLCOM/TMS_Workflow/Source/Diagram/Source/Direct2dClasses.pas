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

unit Direct2dClasses;
{$I Diagram.Inc}

interface

uses
  Windows, SysUtils, Classes, Controls, axctrls,
  {$IFDEF DELPHI2010_LVL}
  D2D1, Direct2D, WinCodec,
  {$ENDIF}
  Graphics, ActiveX, DiagramUtils, DgrClasses;

type
  TD2DCanvas = class;
  TD2DBlockDrawer = class;
  TD2DPaintEngine = class;
  TD2DGraphicsPath = class;

  TD2DPushKind = (pkNone, pkAxisAligned, pkLayer);

  /// Description:
  ///   TD2DBrush is the specific brush class for Direct2D graphic library.
  TD2DBrush = class(TDgrBrush)
  private
    FD2DBrush: ID2D1Brush;
    FD2DCanvas: TD2DCanvas;
    FGradientRect: TSquare;
    FRotMatrix: TD2DMatrix3x2F;
    FBrushStyle: TBrushStyle;
    procedure CreateD2DBrush;
    procedure DestroyD2DBrush;
    procedure SetBrushStyle(const Value: TBrushStyle);
    function CreateHatchBitmap(ABrushStyle: TBrushStyle): ID2D1Bitmap;
  protected
    procedure Change; override;
    function CreatePicture: TDgrPicture; override;
    function D2DBrush: ID2D1Brush;
    procedure DoUpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot); override;
  public
    constructor Create(ACanvas: TD2DCanvas); reintroduce;
    procedure Assign(Source: TPersistent); override;
  published
    property BrushStyle: TBrushStyle read FBrushStyle write SetBrushStyle;
  end;

  /// Description:
  ///   TD2DPen is the specific pen class for Direct2D graphic library.
  TD2DPen = class(TDgrPen)
  private
    FD2DCanvas: TD2DCanvas;
    FD2DBrush: ID2D1Brush;
    FStrokeStyle: ID2D1StrokeStyle;
    FPenStyle: TPenStyle;
    function GetD2DBrush: ID2D1Brush;
    function GetStrokeStyle: ID2D1StrokeStyle;
    procedure SetPenStyle(const Value: TPenStyle);
  protected
    procedure Change; override;
    property D2DBrush: ID2D1Brush read GetD2DBrush;
    property StrokeStyle: ID2D1StrokeStyle read GetStrokeStyle;
  public
    procedure Assign(Source: TPersistent); override;
    constructor Create(ACanvas: TD2DCanvas); reintroduce;
    destructor Destroy; override;
  published
    property PenStyle: TPenStyle read FPenStyle write SetPenStyle;
  end;

  /// Description:
  ///   TD2DCanvas is just like a TCanvas object, with similar methods, but uses Direct2D functions for the drawing
  ///   operations. TD2DCanvas does not descend from TCanvas, it just implement methods with similar names.
  TD2DCanvas = class(TDgrCanvas)
  private
    FBrush: TD2DBrush;
    FPen: TD2DPen;
    FCanvasHandle: HDC;
    FInternalCanvas: TDirect2DCanvas;
    FTransMatrix: TD2DMatrix3x2F;
    FStateMatrix: TD2DMatrix3x2F;
    FTempCanvas: TDirect2DCanvas;
    FPaintEngine: TD2DPaintEngine;
    FPushKind: TD2DPushKind;
    function CreateDWriteTextFormat(AFont: TFont; AHAlign: TAlignment; AVAlign: TVertAlign;
      AWrap, ARightToLeft: boolean): IDWriteTextFormat;
    procedure DestroyCanvas;
    function GetDirect2DCanvas: TDirect2DCanvas;
    procedure DoStretchDrawD2DBitmap(ARect: TRect; ABitmap: ID2D1Bitmap; ATransparency: integer);
  protected
    procedure Changed; override;
    procedure Changing; override;
    function GetBrush: TDgrBrush; override;
    function GetHandle: HDC; override;
    function GetPen: TDgrPen; override;
    function GetTransformMatrix: TD2DMatrix3x2F;
    procedure SetHandle(const Value: HDC); override;
    procedure DoDrawEllipse(x, y, width, height: number); override;
    procedure DoDrawLine(X1, Y1, X2, Y2: number); override;
    procedure DoDrawPath(APath: TDgrGraphicsPath); override;
    procedure DoDrawRectangle(x, y, width, height: number); override;
    procedure DoFillPath(APath: TDgrGraphicsPath); override;
    procedure DoPolygon(APoints: TDotArray); override;
    procedure DoStretchDraw(const Rect: TSquare; Graphic: TGraphic; ATransparency: integer = 0;
      ABitmapTransparent: boolean = False); overload; override;
    procedure DoStretchDraw(const Rect: TSquare; ADgrImage: TDgrImage; ATransparency: integer = 0;
      ABitmapTransparent: boolean = False); overload; override;
    procedure DoUpdateFactors(ASourceRect, ADestRect: TSquare; AScaleX, AScaleY: number); override;
  public
    constructor Create(AHandle: HDC = 0); override;
    destructor Destroy; override;
    function CreateBrush: TDgrBrush; override;
    function CreateGraphic: TDgrGraphic; override;
    function CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine; override;
    function CreatePath: TDgrGraphicsPath; override;
    function CreatePen: TDgrPen; override;
    procedure ClipRegion(ARegion: TDgrRegion); override;
    procedure DrawString(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment; AVAlign: TVertAlign;
      AWrap, ARightToLeft: boolean; ATransparency: integer); override;
    procedure RestoreDrawingState; override;
    procedure SaveDrawingState; override;
    function StringBounds(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment; AVAlign: TVertAlign;
      AWrap, ARightToLeft: boolean): TSquare; override;
    function TranslateTransform(AX, AY: number): integer; override;
    function ScaleTransform(AX, AY: number): integer; override;
    function RotateTransform(AAngle: number): integer; overload; override;
    function RotateTransform(AAngle: number; ARotCenter: TDot): integer; overload; override;
    function ResetClip: integer; override;
    function ResetTransform: integer; override;
    function SetClip(ARect: TSquare): integer; overload; override;
    function SetClip(ARegion: HRGN): integer; overload; override;
    property Direct2DCanvas: TDirect2DCanvas read GetDirect2DCanvas;
  end;

  /// Description:
  ///   Use TD2DBlockDrawer class methods and properties to make it easy to draw blocks using Direct2D API and
  ///   converting coordinates. In general, you set SourceRect property to contain the rectangle where you want
  ///   to paint to. DestRect property must contain the destination rectangle. So, when using drawing methods,
  ///   pass coordinates like you were painting to original rect, and it will be paint on cur rect coordinates.
  TD2DBlockDrawer = class(TDgrBlockDrawer)
  private
    FD2DCanvas: TD2DCanvas;
  protected
    procedure DoRotatePath(APath: TDgrGraphicsPath); override;
    function GetCanvas: TDgrCanvas; override;
    procedure SetPaintEngine(const Value: TDgrPaintEngine); override;
  public
    constructor Create; override;
    destructor Destroy; override;
    procedure TranslateRectsPath(APath: TDgrGraphicsPath); override;
    property D2DCanvas: TD2DCanvas read FD2DCanvas;
  end;

  /// Description:
  ///   TD2DGraphicsPath is the specific Path class for Direct2D graphic library.
  TD2DGraphicsPath = class(TDgrGraphicsPath)
  private
    FD2DPath: ID2D1PathGeometry;
    FD2DSink: ID2D1GeometrySink;
    FTransPath: ID2D1TransformedGeometry;
    FTransMatrix: TD2DMatrix3x2F;
    FPosition: TDot;
    FFigureOpen: boolean;
    procedure CreateD2DPath;
    procedure DestroyD2DPath;
    function GetD2DPath: ID2D1PathGeometry;
    function GetD2DSink: ID2D1GeometrySink;
    procedure SinkBeginFigure(APoint: TDot; AFigBegin: D2D1_FIGURE_BEGIN);
    procedure SinkEndFigure(AFigEnd: D2D1_FIGURE_END);
    procedure SetTransMatrix(const Value: TD2DMatrix3x2F);
    function GetTransPath: ID2D1TransformedGeometry;
    procedure CheckFinished;
  protected
    property TransMatrix: TD2DMatrix3x2F read FTransMatrix write SetTransMatrix;
  public
    constructor Create;
    destructor Destroy; override;
    function AddArc(x, y, width, height, startAngle, sweepAngle: number): integer; override;
    function AddBezier(X1, Y1, X2, Y2, x3, y3, x4, y4: number): integer; override;
    function AddEllipse(x, y, width, height: number): integer; override;
    function AddLine(X1, Y1, X2, Y2: number): integer; override;
    function AddLines(points: TDotArray): integer; override;
    function AddPolygon(points: TDotArray): integer; override;
    function AddRectangle(Rect: TSquare): integer; override;
    function AddRoundRect(X1, Y1, X2, Y2, x3, y3: number): integer; override;
    function CloseFigure(AClosePath: boolean = True): integer; override;
    function CreateRegion: TDgrRegion; override;
    function GetPointCount: integer; override;
    function IsVisible(x, y: integer): boolean; override;
    function Reset: integer; override;
    function SetFillMode(fillmode: TFillMode): integer; override;
    function StartFigure: integer; override;

    property D2DPath: ID2D1PathGeometry read GetD2DPath;
    property D2DSink: ID2D1GeometrySink read GetD2DSink;
    property TransPath: ID2D1TransformedGeometry read GetTransPath;
  end;

  /// Description:
  ///   TD2DPaintEngine uses a TDirect2DCanvas object to perform Direct2D drawing
  ///   operations (for internal use by TatDiagram).
  TD2DPaintEngine = class(TDgrPaintEngine)
  private
    FDirect2DCanvas: TDirect2DCanvas;
  protected
    procedure SetSmoothMode(const Value: TDgrSmoothMode); override;
    procedure SetTextRenderingMode(const Value: TDgrTextRenderingMode); override;
  public
    constructor Create(ACanvas: TCanvas; ARect: TRect); override;
    destructor Destroy; override;
    procedure BeginDraw; override;
    procedure EndDraw; override;
    procedure FillRect(ARect: TRect; AColor: TColor); override;
    function ResetTransform: integer; override;
    function RotateTransform(AAngle: number): integer; override;
    function ScaleTransform(AX, AY: number): integer; override;
    function TranslateTransform(AX, AY: number): integer; override;
  end;

  /// Description:
  ///   TD2DRegion is the specific Region class for Direct2D graphic library.
  TD2DRegion = class(TDgrRegion)
  private
    FD2DPath: ID2D1PathGeometry;
    FPath: TD2DGraphicsPath;
  public
    constructor Create(APath: TDgrGraphicsPath); override;
    function GetHRGN(ACanvas: TDgrCanvas): HRGN; override;
    function IsVisible(ARect: TSquare): boolean; override;
  end;

  /// Description:
  ///   TD2DGraphic is the specific Graphic class for Direct2D graphic library.
  TD2DGraphic = class(TDgrGraphic)
  private
    FBitmapTransparent: boolean;
    FD2DBitmap: ID2D1Bitmap;
    FWICBitmap: IWICBitmap;
    procedure CreateD2DBitmap(ACanvas: TDirect2DCanvas);
    procedure MakeBitmapTransparent(ABMP: IWICBitmap);
  protected
    procedure Changed(Sender: TObject); override;
    function DoGetImageSizes: boolean; override;
    procedure DoDraw(ACanvas: TCanvas; const ARect: TSquare); override;
    function GetD2DBitmap(ACanvas: TDirect2DCanvas): ID2D1Bitmap;
  public
    constructor Create; override;
    destructor Destroy; override;
    procedure Assign(Source: TPersistent); override;
  end;

  /// Description:
  ///   TD2DPicture is the specific Picture class for Direct2D graphic library.
  TD2DPicture = class(TDgrPicture)
  protected
    // procedure Changed(Sender: TObject); override;
  public
    constructor Create; override;
    destructor Destroy; override;
  end;

procedure RegisterD2DFileFormats;
procedure UnRegisterD2DFileFormats;

implementation

uses
  Math;

resourcestring
  sPNGImageFile = 'PNG Image File';
  sTIFImageFile = 'TIFF Image File';
  sGIFImageFile = 'GIF Image File';
  sJPGImageFile = 'JPG Image File';

procedure RegisterD2DFileFormats;
begin
  TPicture.RegisterFileFormat('jpg', sJPGImageFile, TD2DGraphic);
  TPicture.RegisterFileFormat('gif', sGIFImageFile, TD2DGraphic);
  TPicture.RegisterFileFormat('png', sPNGImageFile, TD2DGraphic);
  TPicture.RegisterFileFormat('tif', sTIFImageFile, TD2DGraphic);
  TPicture.RegisterFileFormat('tiff', sTIFImageFile, TD2DGraphic);
end;

procedure UnRegisterD2DFileFormats;
begin
  TPicture.UnregisterGraphicClass(TD2DGraphic);
end;

var
  vWICImagingFactory: IWICImagingFactory;

function WICImagingFactory: IWICImagingFactory;
begin
  if vWICImagingFactory = nil then
  begin
    if CoCreateInstance(CLSID_WICImagingFactory, nil, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, vWICImagingFactory) <> S_OK then
      raise Exception.Create('Could not create WICImagingFactory');
  end;
  result := vWICImagingFactory;
end;

{ TD2DBlockDrawer }

constructor TD2DBlockDrawer.Create;
begin
  if TDirect2DCanvas.Supported then
    FD2DCanvas := TD2DCanvas.Create
  else
    raise EDirect2DException.Create('Direct2D not supported.');
  inherited;
end;

destructor TD2DBlockDrawer.Destroy;
begin
  FD2DCanvas.Free;
  inherited;
end;

procedure TD2DBlockDrawer.DoRotatePath(APath: TDgrGraphicsPath);
begin
  with TD2DGraphicsPath(APath) do
    TransMatrix := TransMatrix * TD2DMatrix3x2F.Rotation(Angle, RotationCenter.x, RotationCenter.y);
end;

function TD2DBlockDrawer.GetCanvas: TDgrCanvas;
begin
  result := FD2DCanvas;
end;

procedure TD2DBlockDrawer.SetPaintEngine(const Value: TDgrPaintEngine);
begin
  if (Value <> nil) and (Value is TD2DPaintEngine) then
  begin
    FD2DCanvas.FPaintEngine := TD2DPaintEngine(Value);
    FD2DCanvas.FTempCanvas := TD2DPaintEngine(Value).FDirect2DCanvas;
    FD2DCanvas.FBrush.DestroyD2DBrush;
  end
  else
  begin
    FD2DCanvas.FPaintEngine := nil;
    FD2DCanvas.FTempCanvas := nil;
  end;
end;

procedure TD2DBlockDrawer.TranslateRectsPath(APath: TDgrGraphicsPath);
begin
  inherited;
  TD2DGraphicsPath(APath).TransMatrix := D2DCanvas.FTransMatrix;
end;

{ TD2DGraphicsPath }

function TD2DGraphicsPath.AddArc(x, y, width, height, startAngle, sweepAngle: number): integer;
var
  startRad, sweepRad: number;
  sweepDir: D2D1_SWEEP_DIRECTION;
  arcSize: D2D1_ARC_SIZE;
  dotSize: TDot;
  arcRect: TSquare;
begin
  if not FFigureOpen then
    SinkBeginFigure(Dot(x, y), D2D1_FIGURE_BEGIN_FILLED);

  startRad := DegToRad(startAngle);
  if (Frac(sweepAngle) = 0) and (Trunc(sweepAngle) mod 360 = 0) then
    sweepAngle := sweepAngle - 1e-3;
  sweepRad := DegToRad(sweepAngle);

  if sweepRad < 0 then
    sweepDir := D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE
  else
    sweepDir := D2D1_SWEEP_DIRECTION_CLOCKWISE;
  if Abs(sweepRad) > Pi then
    arcSize := D2D1_ARC_SIZE_LARGE
  else
    arcSize := D2D1_ARC_SIZE_SMALL;

  dotSize := Dot(width / 2, height / 2);
  arcRect := Square(x + dotSize.x + (Cos(startRad) * dotSize.x), y + dotSize.y + (Sin(startRad) * dotSize.y),
    x + dotSize.x + (Cos(startRad + sweepRad) * dotSize.x), y + dotSize.y + (Sin(startRad + sweepRad) * dotSize.y));

  if (FPosition.x = -1) and (FPosition.y = -1) then
  begin
    D2DSink.EndFigure(D2D1_FIGURE_END_OPEN);
    D2DSink.BeginFigure(D2D1PointF(arcRect.Left, arcRect.Top), D2D1_FIGURE_BEGIN_FILLED);
    FPosition := Dot(arcRect.Left, arcRect.Top);
  end
  else // set draw position
    D2DSink.AddLine(D2D1PointF(arcRect.Left, arcRect.Top));

  D2DSink.AddArc(D2D1ArcSegment(D2D1PointF(arcRect.Right, arcRect.Bottom), D2D1SizeF(dotSize.x, dotSize.y), 0,
      sweepDir, arcSize));

  result := 0;
end;

function TD2DGraphicsPath.AddBezier(X1, Y1, X2, Y2, x3, y3, x4, y4: number): integer;
begin
  if not FFigureOpen then
    SinkBeginFigure(Dot(X1, Y1), D2D1_FIGURE_BEGIN_FILLED);

  D2DSink.AddBezier(D2D1BezierSegment(D2D1PointF(X2, Y2), D2D1PointF(x3, y3), D2D1PointF(x4, y4)));
  FPosition := Dot(x4, y4);
  result := 0;
end;

function TD2DGraphicsPath.AddEllipse(x, y, width, height: number): integer;
var
  p: TDot;
begin
  p := FPosition;
  if not FFigureOpen then
    SinkBeginFigure(Dot(x, y), D2D1_FIGURE_BEGIN_FILLED);
  AddRoundRect(x, y, x + width, y + height, width, height);
  FPosition := p;
  result := 0;
end;

function TD2DGraphicsPath.AddLine(X1, Y1, X2, Y2: number): integer;
begin
  if (FPosition.x = -1) and (FPosition.y = -1) then
    SinkBeginFigure(Dot(X1, Y1), D2D1_FIGURE_BEGIN_FILLED)
  else
    D2DSink.AddLine(D2D1PointF(X1, Y1));
  D2DSink.AddLine(D2D1PointF(X2, Y2));
  FPosition := Dot(X2, Y2);
  result := 0;
end;

function TD2DGraphicsPath.AddLines(points: TDotArray): integer;
var
  d2dPoints: array of TD2DPoint2F;
  count, i: integer;
begin
  count := Length(points);
  SetLength(d2dPoints, count);
  for i := Low(points) to High(points) do
    d2dPoints[i] := D2D1PointF(points[i].x, points[i].y);

  if (count > 0) and (FPosition.x = -1) and (FPosition.y = -1) then
  begin
    SinkBeginFigure(Dot(points[0].x, points[0].y), D2D1_FIGURE_BEGIN_FILLED);
    FPosition := Dot(points[0].x, points[0].y);
  end;

  D2DSink.AddLines(PD2D1Point2F(@d2dPoints[0]), count);
  result := 0;
end;

function TD2DGraphicsPath.AddPolygon(points: TDotArray): integer;
var
  i: integer;
begin
  if Length(points) > 0 then
  begin
    SinkBeginFigure(Dot(points[ High(points)].x, points[ High(points)].y), D2D1_FIGURE_BEGIN_FILLED);
    for i := Low(points) to High(points) do
      D2DSink.AddLine(D2D1PointF(points[i].x, points[i].y));
    SinkEndFigure(D2D1_FIGURE_END_CLOSED);
  end;
  result := 0;
end;

function TD2DGraphicsPath.AddRectangle(Rect: TSquare): integer;
begin
  SinkBeginFigure(Dot(Rect.Left, Rect.Top), D2D1_FIGURE_BEGIN_FILLED);
  D2DSink.AddLine(D2D1PointF(Rect.Right, Rect.Top));
  D2DSink.AddLine(D2D1PointF(Rect.Right, Rect.Bottom));
  D2DSink.AddLine(D2D1PointF(Rect.Left, Rect.Bottom));
  D2DSink.AddLine(D2D1PointF(Rect.Left, Rect.Top));
  SinkEndFigure(D2D1_FIGURE_END_OPEN);
  result := 0;
end;

function TD2DGraphicsPath.AddRoundRect(X1, Y1, X2, Y2, x3, y3: number): integer;
begin
  AddArc(X2 - x3, Y1, x3, y3, 270, 90);
  AddArc(X2 - x3, Y2 - y3, x3, y3, 0, 90);
  AddArc(X1, Y2 - y3, x3, y3, 90, 90);
  AddArc(X1, Y1, x3, y3, 180, 90);
  result := 0;
end;

procedure TD2DGraphicsPath.SinkBeginFigure(APoint: TDot; AFigBegin: D2D1_FIGURE_BEGIN);
begin
  if FFigureOpen then
    D2DSink.EndFigure(D2D1_FIGURE_END_OPEN);
  D2DSink.BeginFigure(D2D1PointF(APoint.x, APoint.y), AFigBegin);
  FFigureOpen := True;
end;

procedure TD2DGraphicsPath.SinkEndFigure(AFigEnd: D2D1_FIGURE_END);
begin
  D2DSink.EndFigure(AFigEnd);
  FFigureOpen := False;
end;

procedure TD2DGraphicsPath.CheckFinished;
begin
  if FFigureOpen then
    SinkEndFigure(D2D1_FIGURE_END_OPEN);
  CloseFigure;
  D2DSink.Close;
end;

function TD2DGraphicsPath.CloseFigure(AClosePath: boolean): integer;
begin
  if FFigureOpen then
  begin
    if AClosePath then
      SinkEndFigure(D2D1_FIGURE_END_CLOSED)
    else
      SinkEndFigure(D2D1_FIGURE_END_OPEN);
  end;
  FPosition := Dot(-1, -1);
  result := 0;
end;

constructor TD2DGraphicsPath.Create;
begin
  FD2DPath := nil;
  FTransPath := nil;
  FPosition := Dot(-1, -1);
  FFigureOpen := False;
  FTransMatrix := TD2DMatrix3x2F.Identity;
end;

procedure TD2DGraphicsPath.CreateD2DPath;
begin
  D2DFactory.CreatePathGeometry(FD2DPath);
  FD2DPath.Open(FD2DSink);
end;

function TD2DGraphicsPath.CreateRegion: TDgrRegion;
begin
  result := TD2DRegion.Create(Self);
end;

destructor TD2DGraphicsPath.Destroy;
begin
  DestroyD2DPath;
  inherited;
end;

procedure TD2DGraphicsPath.DestroyD2DPath;
begin
  if FD2DPath <> nil then
  begin
    FD2DSink.Close;
    FD2DPath := nil;
  end;
end;

function TD2DGraphicsPath.GetD2DPath: ID2D1PathGeometry;
begin
  if FD2DPath = nil then
    CreateD2DPath;
  result := FD2DPath;
end;

function TD2DGraphicsPath.GetD2DSink: ID2D1GeometrySink;
begin
  if FD2DPath = nil then
    CreateD2DPath;
  result := FD2DSink;
end;

function TD2DGraphicsPath.GetPointCount: integer;
var
  count: cardinal;
begin
  CheckFinished;
  count := 0;
  D2DPath.GetSegmentCount(count);
  result := count;
end;

function TD2DGraphicsPath.GetTransPath: ID2D1TransformedGeometry;
begin
  if FTransPath = nil then
    D2DFactory.CreateTransformedGeometry(D2DPath, FTransMatrix, FTransPath);
  result := FTransPath;
end;

function TD2DGraphicsPath.IsVisible(x, y: integer): boolean;
var
  contains: LongBool;
begin
  CheckFinished;
  if TransPath <> nil then
    TransPath.FillContainsPoint(D2D1PointF(x, y), TD2DMatrix3x2F.Identity, 0, contains)
  else
    D2DPath.FillContainsPoint(D2D1PointF(x, y), TransMatrix, 0, contains);
  result := contains;
end;

function TD2DGraphicsPath.Reset: integer;
begin
  FPosition := Dot(-1, -1);
  DestroyD2DPath;
  FTransPath := nil;
  result := 0;
end;

function TD2DGraphicsPath.SetFillMode(fillmode: TFillMode): integer;
const
  d2dFillMode: array [TFillMode] of D2D1_FILL_MODE = (D2D1_FILL_MODE_ALTERNATE, D2D1_FILL_MODE_WINDING);
begin
  D2DSink.SetFillMode(d2dFillMode[fillmode]);
  result := 0;
end;

procedure TD2DGraphicsPath.SetTransMatrix(const Value: TD2DMatrix3x2F);
begin
  FTransMatrix := Value;
  FTransPath := nil;
end;

function TD2DGraphicsPath.StartFigure: integer;
begin
  if FFigureOpen then
  begin
    SinkEndFigure(D2D1_FIGURE_END_OPEN);
    FPosition := Dot(-1, -1);
  end;

  // SinkBeginFigure is called from methods for adding objects to the path
  result := 0;
end;

{ TD2DCanvas }

procedure TD2DCanvas.Changed;
begin
  inherited;
end;

procedure TD2DCanvas.Changing;
begin
  inherited;
end;

procedure TD2DCanvas.ClipRegion(ARegion: TDgrRegion);
var
  layer: ID2D1Layer;
  params: TD2D1LayerParameters;
  path: TD2DGraphicsPath;
  bounds: TD2DRectF;
begin
  inherited;
  if FPushKind = pkNone then
  begin
    Direct2DCanvas.RenderTarget.CreateLayer(nil, layer);
    path := TD2DRegion(ARegion).FPath;
    path.CheckFinished;

    if path.TransPath <> nil then
    begin
      params.geometricMask := path.TransPath;
      params.maskTransform := TD2DMatrix3x2F.Identity;
    end
    else
    begin
      params.geometricMask := path.D2DPath;
      params.maskTransform := path.TransMatrix;
    end;

    params.geometricMask.GetBounds(params.maskTransform, bounds);
    params.contentBounds := bounds;
    params.maskAntialiasMode := D2D1_ANTIALIAS_MODE_PER_PRIMITIVE;
    params.opacityBrush := nil;
    params.layerOptions := D2D1_LAYER_OPTIONS_NONE;
    params.opacity := 1;

    Direct2DCanvas.RenderTarget.PushLayer(params, layer);
    FPushKind := pkLayer;
  end;
end;

constructor TD2DCanvas.Create(AHandle: HDC);
begin
  inherited;
  FBrush := TD2DBrush.Create(Self);
  FPen := TD2DPen.Create(Self);
  FInternalCanvas := nil;
  FCanvasHandle := 0;
  FTempCanvas := nil;
  FPushKind := pkNone;
  FTransMatrix := TD2DMatrix3x2F.Identity;
  FStateMatrix := TD2DMatrix3x2F.Identity;
end;

function TD2DCanvas.CreateBrush: TDgrBrush;
begin
  result := TD2DBrush.Create(Self);
end;

function TD2DCanvas.CreateDWriteTextFormat(AFont: TFont; AHAlign: TAlignment; AVAlign: TVertAlign;
  AWrap, ARightToLeft: boolean): IDWriteTextFormat;
var
  fontWeight: DWRITE_FONT_WEIGHT;
  fontStyle: DWRITE_FONT_STYLE;
begin
  if fsBold in AFont.Style then
    fontWeight := DWRITE_FONT_WEIGHT_BOLD
  else
    fontWeight := DWRITE_FONT_WEIGHT_NORMAL;
  if fsItalic in AFont.Style then
    fontStyle := DWRITE_FONT_STYLE_ITALIC
  else
    fontStyle := DWRITE_FONT_STYLE_NORMAL;

  DWriteFactory.CreateTextFormat(PChar(AFont.Name), nil, fontWeight, fontStyle, DWRITE_FONT_STRETCH_NORMAL, Abs(AFont.height), '', result);

  case AHAlign of
    taLeftJustify:
      result.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    taRightJustify:
      result.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
    taCenter:
      result.SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
  end;

  case AVAlign of
    vaTop:
      result.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    vaBottom:
      result.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
    vaCenter:
      result.SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
  end;

  if AWrap then
    result.SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP)
  else
    result.SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

  if ARightToLeft then
    result.SetReadingDirection(DWRITE_READING_DIRECTION_RIGHT_TO_LEFT)
  else
    result.SetReadingDirection(DWRITE_READING_DIRECTION_LEFT_TO_RIGHT);
end;

function TD2DCanvas.CreateGraphic: TDgrGraphic;
begin
  result := TD2DGraphic.Create;
end;

function TD2DCanvas.CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine;
begin
  result := TD2DPaintEngine.Create(ACanvas, ARect);
end;

function TD2DCanvas.CreatePath: TDgrGraphicsPath;
begin
  result := TD2DGraphicsPath.Create;
end;

function TD2DCanvas.CreatePen: TDgrPen;
begin
  result := TD2DPen.Create(Self);
end;

destructor TD2DCanvas.Destroy;
begin
  FBrush.Free;
  FPen.Free;
  DestroyCanvas;
  inherited;
end;

procedure TD2DCanvas.DestroyCanvas;
begin
  if FInternalCanvas <> nil then
    FreeAndNil(FInternalCanvas);
  FCanvasHandle := 0;
end;

procedure TD2DCanvas.DoDrawEllipse(x, y, width, height: number);
begin
  Direct2DCanvas.RenderTarget.FillEllipse(D2D1Ellipse(D2D1PointF(x, y), width, height), FBrush.D2DBrush);
  Direct2DCanvas.RenderTarget.DrawEllipse(D2D1Ellipse(D2D1PointF(x, y), width, height), FPen.D2DBrush, FPen.width, FPen.StrokeStyle);
end;

procedure TD2DCanvas.DoDrawLine(X1, Y1, X2, Y2: number);
begin
  Direct2DCanvas.RenderTarget.DrawLine(D2D1PointF(X1, Y1), D2D1PointF(X2, Y2), FPen.D2DBrush, FPen.width,
    FPen.StrokeStyle);
end;

procedure TD2DCanvas.DoDrawPath(APath: TDgrGraphicsPath);
var
  path: TD2DGraphicsPath;
  wpen: number;
begin
  path := APath as TD2DGraphicsPath;
  path.CheckFinished;
  wpen := FPen.Width;

  if path.TransPath <> nil then
    Direct2DCanvas.RenderTarget.DrawGeometry(path.TransPath, FPen.D2DBrush, wpen, FPen.StrokeStyle)
  else
  begin
    if path.TransMatrix._11 > 0 then
      wpen := wpen / path.TransMatrix._11;
    Direct2DCanvas.RenderTarget.DrawGeometry(path.D2DPath, FPen.D2DBrush, wpen, FPen.StrokeStyle);
  end;
end;

procedure TD2DCanvas.DoDrawRectangle(x, y, width, height: number);
begin
  Direct2DCanvas.RenderTarget.FillRectangle(D2D1RectF(x, y, x + width, y + height), FBrush.D2DBrush);
  Direct2DCanvas.RenderTarget.DrawRectangle(D2D1RectF(x, y, x + width, y + height), FPen.D2DBrush, FPen.width, FPen.StrokeStyle);
end;

procedure TD2DCanvas.DoFillPath(APath: TDgrGraphicsPath);
var
  path: TD2DGraphicsPath;
begin
  path := APath as TD2DGraphicsPath;
  path.CheckFinished;

  if path.TransPath <> nil then
    Direct2DCanvas.RenderTarget.FillGeometry(path.TransPath, FBrush.D2DBrush)
  else
    Direct2DCanvas.RenderTarget.FillGeometry(path.D2DPath, FBrush.D2DBrush);
end;

procedure TD2DCanvas.DoPolygon(APoints: TDotArray);
begin
  Direct2DCanvas.Polygon(RoundDotArray(APoints));
end;

procedure TD2DCanvas.DoStretchDraw(const Rect: TSquare; Graphic: TGraphic; ATransparency: integer; ABitmapTransparent: boolean);
begin
  if Graphic is TD2DGraphic then
  begin
    TD2DGraphic(Graphic).FBitmapTransparent := ABitmapTransparent;
    DoStretchDrawD2DBitmap(ToRect(Rect), TD2DGraphic(Graphic).GetD2DBitmap(Direct2DCanvas), ATransparency);
    TD2DGraphic(Graphic).FD2DBitmap := nil;
  end
  else
    Direct2DCanvas.StretchDraw(ToRect(Rect), Graphic, Round((100 - ATransparency) * 2.55));
end;

procedure TD2DCanvas.DoStretchDraw(const Rect: TSquare; ADgrImage: TDgrImage; ATransparency: integer;
  ABitmapTransparent: boolean);
begin
end;

procedure TD2DCanvas.DoStretchDrawD2DBitmap(ARect: TRect; ABitmap: ID2D1Bitmap; ATransparency: integer);
var
  destRect: TD2D1RectF;
begin
  if ABitmap <> nil then
  begin
    destRect := D2D1RectF(ARect.Left, ARect.Top, ARect.Right, ARect.Bottom);
    Direct2DCanvas.RenderTarget.DrawBitmap(ABitmap, @destRect, 1 - ATransparency / 100);
  end;
end;

procedure TD2DCanvas.DoUpdateFactors(ASourceRect, ADestRect: TSquare; AScaleX, AScaleY: number);
begin
  FTransMatrix := TD2DMatrix3x2F.Translation(-(ASourceRect.Right + ASourceRect.Left) / 2, -(ASourceRect.Top + ASourceRect.Bottom) / 2)
    * TD2DMatrix3x2F.Scale(AScaleX, AScaleY, D2D1PointF(0, 0))
    * TD2DMatrix3x2F.Translation((ADestRect.Right + ADestRect.Left) / 2, (ADestRect.Top + ADestRect.Bottom) / 2);
end;

procedure TD2DCanvas.DrawString(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment; AVAlign: TVertAlign;
  AWrap, ARightToLeft: boolean; ATransparency: integer);
var
  txtFormat: IDWriteTextFormat;
  fgBrush: ID2D1SolidColorBrush;
  layRect: D2D_RECT_F;
  brushProps: D2D1_BRUSH_PROPERTIES;
  txtLayout: IDWriteTextLayout;
  range: DWRITE_TEXT_RANGE;
begin
  if AStr > '' then
  begin
    layRect := D2D1RectF(ARect.Left, ARect.Top, ARect.Right, ARect.Bottom);
    txtFormat := CreateDWriteTextFormat(AFont, AHAlign, AVAlign, AWrap, ARightToLeft);
    brushProps.opacity := 1 - ATransparency / 100;
    Direct2DCanvas.RenderTarget.CreateSolidColorBrush(D2D1ColorF(AFont.Color), @brushProps, fgBrush);

    if fsUnderline in AFont.Style then
    begin
      DWriteFactory.CreateTextLayout(PChar(AStr), Length(AStr), txtFormat, ARect.Right - ARect.Left, ARect.Bottom - ARect.Top, txtLayout);
      if fsUnderline in AFont.Style then
      begin
        range.startPosition := 0;
        range.length := Length(AStr);
        txtLayout.SetUnderline(True, range);
      end;
      Direct2DCanvas.RenderTarget.DrawTextLayout(D2D1PointF(ARect.Left, ARect.Top), txtLayout, fgBrush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
    end
    else
      Direct2DCanvas.RenderTarget.DrawText(PChar(AStr), Length(AStr), txtFormat, layRect, fgBrush);
  end;
end;

function TD2DCanvas.GetBrush: TDgrBrush;
begin
  result := FBrush;
end;

function TD2DCanvas.GetDirect2DCanvas: TDirect2DCanvas;
begin
  if FTempCanvas <> nil then
    result := FTempCanvas
  else
    result := FInternalCanvas;
end;

function TD2DCanvas.GetHandle: HDC;
begin
  if (FInternalCanvas <> nil) and (FCanvasHandle <> 0) then
    result := FCanvasHandle
  else
    result := inherited GetHandle;
end;

function TD2DCanvas.GetPen: TDgrPen;
begin
  result := FPen;
end;

function TD2DCanvas.GetTransformMatrix: TD2DMatrix3x2F;
begin
  if Direct2DCanvas <> nil then
    Direct2DCanvas.RenderTarget.GetTransform(result)
  else
    result := TD2DMatrix3x2F.Identity;
end;

function TD2DCanvas.ResetClip: integer;
begin
  case FPushKind of
    pkAxisAligned:
      Direct2DCanvas.RenderTarget.PopAxisAlignedClip;
    pkLayer:
      Direct2DCanvas.RenderTarget.PopLayer;
  end;
  FPushKind := pkNone;
  result := 0;
end;

function TD2DCanvas.ResetTransform: integer;
begin
  Direct2DCanvas.RenderTarget.SetTransform(TD2DMatrix3x2F.Identity);
  result := 0;
end;

procedure TD2DCanvas.RestoreDrawingState;
begin
  Direct2DCanvas.RenderTarget.SetTransform(FStateMatrix);
end;

function TD2DCanvas.RotateTransform(AAngle: number; ARotCenter: TDot): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  Direct2DCanvas.RenderTarget.GetTransform(matrix);
  Direct2DCanvas.RenderTarget.SetTransform(TD2DMatrix3x2F.Rotation(AAngle, ARotCenter.x, ARotCenter.y) * matrix);
  result := 0;
end;

function TD2DCanvas.RotateTransform(AAngle: number): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  Direct2DCanvas.RenderTarget.GetTransform(matrix);
  Direct2DCanvas.RenderTarget.SetTransform(TD2DMatrix3x2F.Rotation(AAngle, D2D1PointF(0, 0)) * matrix);
  result := 0;
end;

procedure TD2DCanvas.SaveDrawingState;
begin
  Direct2DCanvas.RenderTarget.GetTransform(FStateMatrix);
end;

function TD2DCanvas.ScaleTransform(AX, AY: number): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  Direct2DCanvas.RenderTarget.GetTransform(matrix);
  Direct2DCanvas.RenderTarget.SetTransform(matrix * TD2DMatrix3x2F.Scale(AX, AY, D2D1PointF(0, 0)));
  result := 0;
end;

function TD2DCanvas.SetClip(ARect: TSquare): integer;
begin
  if FPushKind = pkNone then
  begin
    Direct2DCanvas.RenderTarget.PushAxisAlignedClip(D2D1RectF(ARect.Left, ARect.Top, ARect.Right, ARect.Bottom),
      D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    FPushKind := pkAxisAligned;
  end;
  result := 0;
end;

function TD2DCanvas.SetClip(ARegion: HRGN): integer;
begin
  result := -1; // not supported
end;

procedure TD2DCanvas.SetHandle(const Value: HDC);
begin
  inherited;
  DestroyCanvas;
  if Handle <> Value then
  begin
    FInternalCanvas := TDirect2DCanvas.Create(Value);
    FInternalCanvas.Brush.Handle := FBrush.D2DBrush;
    FCanvasHandle := Value;
  end;
end;

function TD2DCanvas.StringBounds(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment; AVAlign: TVertAlign;
  AWrap, ARightToLeft: boolean): TSquare;
var
  txtLayout: IDWriteTextLayout;
  txtFormat: IDWriteTextFormat;
  txtMetrics: TDWriteTextMetrics;
begin
  txtFormat := CreateDWriteTextFormat(AFont, AHAlign, AVAlign, AWrap, ARightToLeft);
  DWriteFactory.CreateTextLayout(PChar(AStr), Length(AStr), txtFormat, ARect.Right - ARect.Left,
    ARect.Bottom - ARect.Top, txtLayout);
  txtLayout.GetMetrics(txtMetrics);
  case AHAlign of
    taLeftJustify:
      begin
        result.Left := ARect.Left;
        result.Right := ARect.Left + txtMetrics.width;
      end;
    taRightJustify:
      begin
        result.Left := ARect.Right - txtMetrics.width;
        result.Right := ARect.Right;
      end;
    taCenter:
      begin
        result.Left := (ARect.Right - ARect.Left - txtMetrics.width) / 2 + ARect.Left;
        result.Right := result.Left + txtMetrics.width;
      end;
  end;
  case AVAlign of
    vaTop:
      begin
        result.Top := ARect.Top;
        result.Bottom := ARect.Top + txtMetrics.height;
      end;
    vaBottom:
      begin
        result.Top := ARect.Bottom - txtMetrics.height;
        result.Bottom := ARect.Bottom;
      end;
    vaCenter:
      begin
        result.Top := (ARect.Bottom - ARect.Top - txtMetrics.height) / 2 + ARect.Top;
        result.Bottom := result.Top + txtMetrics.height;
      end;
  end;

  // "Inflate" rect to avoid word wrapping and rounding
  result.Right := result.Right + 1;
  result.Bottom := result.Bottom + 1;
end;

function TD2DCanvas.TranslateTransform(AX, AY: number): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  Direct2DCanvas.RenderTarget.GetTransform(matrix);
  Direct2DCanvas.RenderTarget.SetTransform(matrix * TD2DMatrix3x2F.Translation(AX, AY));
  result := 0;
end;

{ TD2DBrush }

procedure TD2DBrush.Assign(Source: TPersistent);
begin
  inherited;
  if Source is TD2DBrush then
    BrushStyle := TD2DBrush(Source).BrushStyle
  else if Source is TBrush then
    BrushStyle := TBrush(Source).Style;
end;

procedure TD2DBrush.Change;
begin
  inherited;
  DestroyD2DBrush;
end;

constructor TD2DBrush.Create(ACanvas: TD2DCanvas);
begin
  inherited Create;
  FD2DCanvas := ACanvas;
  FRotMatrix := TD2DMatrix3x2F.Identity;
  FBrushStyle := bsSolid;
end;

procedure TD2DBrush.CreateD2DBrush;
var
  brushProps: TD2D1BrushProperties;
  render: ID2D1RenderTarget;
  gStops: array[0..1] of TD2D1GradientStop;
  gradStop: ID2D1GradientStopCollection;
  solidBrush: ID2D1SolidColorBrush;
  linGradBrush: ID2D1LinearGradientBrush;
  radGradBrush: ID2D1RadialGradientBrush;
  bmpBrush: ID2D1BitmapBrush;
  bmpBrushProps: TD2D1BitmapBrushProperties;
  bmpHatch: ID2D1Bitmap;
  matrix: TD2DMatrix3x2F;

  function DefaultBrushProperties: TD2D1BitmapBrushProperties;
  begin
    result.extendModeX := D2D1_EXTEND_MODE_WRAP;
    result.extendModeY := D2D1_EXTEND_MODE_WRAP;
    result.interpolationMode := D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
  end;

begin
  render := FD2DCanvas.Direct2DCanvas.RenderTarget;

  case BrushMode of
    bmClear:
      begin
        render.CreateSolidColorBrush(D2D1ColorF(0, 0), nil, solidBrush);
        FD2DBrush := solidBrush;
      end;
    bmGradient:
      begin
        gStops[0] := D2D1GradientStop(0, D2D1ColorF(Color, GetAlpha1));
        gStops[1] := D2D1GradientStop(1, D2D1ColorF(Color2, GetAlpha2));
        if GradientMode in [gmOutIn, gmHorzOutIn, gmVertOutIn] then
        begin
          gStops[0].Color := D2D1ColorF(Color2, GetAlpha2);
          gStops[1].Color := D2D1ColorF(Color, GetAlpha1);
        end;
        render.CreateGradientStopCollection(@gStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, gradStop);

        case GradientMode of
          gmTopBottom:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Left, FGradientRect.Top),
                  D2D1PointF(FGradientRect.Left, FGradientRect.Bottom)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmBottomTop:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Left, FGradientRect.Bottom),
                  D2D1PointF(FGradientRect.Left, FGradientRect.Top)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmLeftRight:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Left, FGradientRect.Top),
                  D2D1PointF(FGradientRect.Right, FGradientRect.Top)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmRightLeft:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Right, FGradientRect.Top),
                  D2D1PointF(FGradientRect.Left, FGradientRect.Top)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmLeftTop:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Left, FGradientRect.Top),
                  D2D1PointF(FGradientRect.Right, FGradientRect.Bottom)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmRightTop:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Right, FGradientRect.Top),
                  D2D1PointF(FGradientRect.Left, FGradientRect.Bottom)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmLeftBottom:
            begin
              render.CreateLinearGradientBrush(
                D2D1LinearGradientBrushProperties(D2D1PointF(FGradientRect.Left, FGradientRect.Bottom),
                  D2D1PointF(FGradientRect.Right, FGradientRect.Top)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmRightBottom:
            begin
              render.CreateLinearGradientBrush(D2D1LinearGradientBrushProperties(
                D2D1PointF(FGradientRect.Right, FGradientRect.Bottom),
                  D2D1PointF(FGradientRect.Left, FGradientRect.Left)), nil, gradStop, linGradBrush);
              FD2DBrush := linGradBrush;
            end;
          gmInOut, gmOutIn:
            begin
              render.CreateRadialGradientBrush(
                D2D1RadialGradientBrushProperties(D2D1PointF(FGradientRect.Left + (FGradientRect.Right - FGradientRect.Left) / 2,
                  FGradientRect.Top + (FGradientRect.Bottom - FGradientRect.Top) / 2), D2D1PointF(0, 0),
                  (FGradientRect.Right - FGradientRect.Left) / 2, (FGradientRect.Bottom - FGradientRect.Top) / 2),
                nil, gradStop, radGradBrush);
              FD2DBrush := radGradBrush;
            end;
          gmHorzInOut, gmHorzOutIn:
            begin
              render.CreateRadialGradientBrush(
                D2D1RadialGradientBrushProperties(D2D1PointF(FGradientRect.Left + (FGradientRect.Right - FGradientRect.Left) / 2,
                  FGradientRect.Top + (FGradientRect.Bottom - FGradientRect.Top) / 2), D2D1PointF(0, 0),
                  FGradientRect.Right - FGradientRect.Left, (FGradientRect.Bottom - FGradientRect.Top) / 2), nil,
                gradStop, radGradBrush);
              FD2DBrush := radGradBrush;
            end;
          gmVertInOut, gmVertOutIn:
            begin
              render.CreateRadialGradientBrush(
                D2D1RadialGradientBrushProperties(D2D1PointF(FGradientRect.Left + (FGradientRect.Right - FGradientRect.Left) / 2,
                  FGradientRect.Top + (FGradientRect.Bottom - FGradientRect.Top) / 2), D2D1PointF(0, 0),
                  (FGradientRect.Right - FGradientRect.Left) / 2, FGradientRect.Bottom - FGradientRect.Top), nil,
                gradStop, radGradBrush);
              FD2DBrush := radGradBrush;
            end;
        end;

        if FD2DBrush <> nil then
        begin
          FD2DBrush.GetTransform(matrix);
          FD2DBrush.SetTransform(matrix * FRotMatrix);
        end;
      end;
    bmTexture:
      begin
        bmpBrushProps := DefaultBrushProperties;
        render.CreateBitmapBrush(TD2DGraphic(Texture).GetD2DBitmap(FD2DCanvas.Direct2DCanvas), @bmpBrushProps, nil, bmpBrush);
        FD2DBrush := bmpBrush;
      end;
    bmHatch:
      begin
        bmpHatch := CreateHatchBitmap(BrushStyle);
        bmpBrushProps := DefaultBrushProperties;
        render.CreateBitmapBrush(bmpHatch, @bmpBrushProps, nil, bmpBrush);
        FD2DBrush := bmpBrush;
      end
    else // bmSolid
    begin
      brushProps.opacity := 1 - Transparency / 100;
      render.CreateSolidColorBrush(D2D1ColorF(Color, 1 - Transparency / 100), @brushProps, solidBrush);
      FD2DBrush := solidBrush;
    end;
  end;

  if FD2DBrush <> nil then
    FD2DBrush.SetOpacity(1 - Transparency / 100);
end;

const
  BMP_HATCH_SIZE = 8;

type
  TBitmapHatchPattern = array [0..BMP_HATCH_SIZE-1, 0..BMP_HATCH_SIZE-1] of byte;

const
  BMP_HATCH_PATTERN_EMPTY: TBitmapHatchPattern =
    ((0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0));

  BMP_HATCH_PATTERN_BDIAGONAL: TBitmapHatchPattern =
    ((0,0,0,0,0,0,0,1),
     (0,0,0,0,0,0,1,0),
     (0,0,0,0,0,1,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,1,0,0,0,0),
     (0,0,1,0,0,0,0,0),
     (0,1,0,0,0,0,0,0),
     (1,0,0,0,0,0,0,0));

  BMP_HATCH_PATTERN_CROSS: TBitmapHatchPattern =
    ((0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (1,1,1,1,1,1,1,1),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0));

  BMP_HATCH_PATTERN_DIAGCROSS: TBitmapHatchPattern =
    ((1,0,0,0,0,0,0,1),
     (0,1,0,0,0,0,1,0),
     (0,0,1,0,0,1,0,0),
     (0,0,0,1,1,0,0,0),
     (0,0,0,1,1,0,0,0),
     (0,0,1,0,0,1,0,0),
     (0,1,0,0,0,0,1,0),
     (1,0,0,0,0,0,0,1));

  BMP_HATCH_PATTERN_FDIAGONAL: TBitmapHatchPattern =
    ((1,0,0,0,0,0,0,0),
     (0,1,0,0,0,0,0,0),
     (0,0,1,0,0,0,0,0),
     (0,0,0,1,0,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,0,1,0,0),
     (0,0,0,0,0,0,1,0),
     (0,0,0,0,0,0,0,1));

  BMP_HATCH_PATTERN_HORIZONTAL: TBitmapHatchPattern =
    ((0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (1,1,1,1,1,1,1,1),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0),
     (0,0,0,0,0,0,0,0));

  BMP_HATCH_PATTERN_VERTICAL: TBitmapHatchPattern =
    ((0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0),
     (0,0,0,0,1,0,0,0));

function TD2DBrush.CreateHatchBitmap(ABrushStyle: TBrushStyle): ID2D1Bitmap;
var
  bmp: TBitmap;
  x, y: integer;
  pattern: TBitmapHatchPattern;
begin
  bmp := TBitmap.Create;
  try
    case ABrushStyle of
      bsHorizontal:
        pattern := BMP_HATCH_PATTERN_HORIZONTAL;
      bsVertical:
        pattern := BMP_HATCH_PATTERN_VERTICAL;
      bsFDiagonal:
        pattern := BMP_HATCH_PATTERN_FDIAGONAL;
      bsBDiagonal:
        pattern := BMP_HATCH_PATTERN_BDIAGONAL;
      bsCross:
        pattern := BMP_HATCH_PATTERN_CROSS;
      bsDiagCross:
        pattern := BMP_HATCH_PATTERN_DIAGCROSS;
    else
      pattern := BMP_HATCH_PATTERN_EMPTY;
    end;

    bmp.SetSize(BMP_HATCH_SIZE, BMP_HATCH_SIZE);
    for x := 0 to BMP_HATCH_SIZE - 1 do
      for y := 0 to BMP_HATCH_SIZE - 1 do
        if pattern[y, x] = 0 then
          bmp.Canvas.Pixels[x, y] := $FFFFFF
        else
          bmp.Canvas.Pixels[x, y] := Self.Color;
    result := FD2DCanvas.Direct2DCanvas.CreateBitmap(bmp);
  finally
    bmp.Free;
  end;
end;

function TD2DBrush.CreatePicture: TDgrPicture;
begin
  result := TD2DPicture.Create;
end;

function TD2DBrush.D2DBrush: ID2D1Brush;
begin
  if FD2DBrush = nil then
    CreateD2DBrush;
  result := FD2DBrush;
end;

procedure TD2DBrush.DestroyD2DBrush;
begin
  if FD2DBrush <> nil then
    FD2DBrush := nil;
end;

procedure TD2DBrush.DoUpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot);
begin
  FGradientRect := ARect;
  FRotMatrix := TD2DMatrix3x2F.Identity;
  if AAngle <> 0 then
    FRotMatrix := FRotMatrix * TD2DMatrix3x2F.Rotation(AAngle, ARotCenter.x, ARotCenter.y);
end;

procedure TD2DBrush.SetBrushStyle(const Value: TBrushStyle);
begin
  if FBrushStyle <> Value then
  begin
    FBrushStyle := Value;
    Change;
  end;
end;

{ TD2DPaintEngine }

procedure TD2DPaintEngine.BeginDraw;
begin
  inherited;
  FDirect2DCanvas.RenderTarget.BeginDraw;
end;

constructor TD2DPaintEngine.Create(ACanvas: TCanvas; ARect: TRect);
begin
  if TDirect2DCanvas.Supported then
    FDirect2DCanvas := TDirect2DCanvas.Create(ACanvas, ARect)
  else
    raise EDirect2DException.Create('Direct2D not supported.');
end;

destructor TD2DPaintEngine.Destroy;
begin
  FDirect2DCanvas.Free;
  inherited;
end;

procedure TD2DPaintEngine.EndDraw;
begin
  inherited;
  FDirect2DCanvas.RenderTarget.EndDraw;
end;

procedure TD2DPaintEngine.FillRect(ARect: TRect; AColor: TColor);
begin
  FDirect2DCanvas.Brush.Color := AColor;
  FDirect2DCanvas.FillRect(ARect);
end;

function TD2DPaintEngine.ResetTransform: integer;
begin
  FDirect2DCanvas.RenderTarget.SetTransform(TD2DMatrix3x2F.Identity);
  result := 0;
end;

function TD2DPaintEngine.RotateTransform(AAngle: number): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  FDirect2DCanvas.RenderTarget.GetTransform(matrix);
  FDirect2DCanvas.RenderTarget.SetTransform(TD2DMatrix3x2F.Rotation(AAngle, 0, 0) * matrix);
  result := 0;
end;

function TD2DPaintEngine.ScaleTransform(AX, AY: number): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  FDirect2DCanvas.RenderTarget.GetTransform(matrix);
  FDirect2DCanvas.RenderTarget.SetTransform(matrix * TD2DMatrix3x2F.Scale(AX, AY, D2D1PointF(0, 0)));
  result := 0;
end;

procedure TD2DPaintEngine.SetSmoothMode(const Value: TDgrSmoothMode);
begin
  inherited;
  case Value of
    smAntiAlias, smHighQuality:
      FDirect2DCanvas.RenderTarget.SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    smInactive, smHighSpeed:
      FDirect2DCanvas.RenderTarget.SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
  end;
end;

procedure TD2DPaintEngine.SetTextRenderingMode(const Value: TDgrTextRenderingMode);
begin
  inherited;
  case Value of
    tmAntiAlias, tmAntiAliasHint, tmClearType:
      FDirect2DCanvas.RenderTarget.SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
    tmDefault:
      FDirect2DCanvas.RenderTarget.SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT);
    tmNormal, tmNormalHint:
      FDirect2DCanvas.RenderTarget.SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);
  end;
end;

function TD2DPaintEngine.TranslateTransform(AX, AY: number): integer;
var
  matrix: TD2DMatrix3x2F;
begin
  FDirect2DCanvas.RenderTarget.GetTransform(matrix);
  FDirect2DCanvas.RenderTarget.SetTransform(matrix * TD2DMatrix3x2F.Translation(AX, AY));
  result := 0;
end;

{ TD2DPen }

procedure TD2DPen.Assign(Source: TPersistent);
begin
  inherited;
  if Source is TD2DPen then
    PenStyle := TD2DPen(Source).PenStyle
  else if Source is TPen then
    PenStyle := TPen(Source).Style;
end;

procedure TD2DPen.Change;
begin
  inherited;
  FD2DBrush := nil;
  FStrokeStyle := nil;
end;

constructor TD2DPen.Create(ACanvas: TD2DCanvas);
begin
  inherited Create;
  FPenStyle := psSolid;
  FD2DCanvas := ACanvas;
  FD2DBrush := nil;
  FStrokeStyle := nil;
end;

destructor TD2DPen.Destroy;
begin
  inherited;
  FD2DBrush := nil;
  FStrokeStyle := nil;
end;

function TD2DPen.GetD2DBrush: ID2D1Brush;
begin
  if FD2DBrush = nil then
  begin
    FD2DBrush := FD2DCanvas.Direct2DCanvas.CreateBrush(Color);
    FD2DBrush.SetOpacity(1 - Transparency / 100);
  end;
  result := FD2DBrush;
end;

function TD2DPen.GetStrokeStyle: ID2D1StrokeStyle;
var
  dstyle: D2D1_DASH_STYLE;
begin
  if (FStrokeStyle = nil) and (PenStyle <> psSolid) then
  begin
    dstyle := D2D1_DASH_STYLE_SOLID;
    case PenStyle of
      psDash:
        dstyle := D2D1_DASH_STYLE_DASH;
      psDot:
        dstyle := D2D1_DASH_STYLE_DOT;
      psDashDot:
        dstyle := D2D1_DASH_STYLE_DASH_DOT;
      psDashDotDot:
        dstyle := D2D1_DASH_STYLE_DASH_DOT_DOT;
      psClear:
        D2DBrush.SetOpacity(0);
    end;

    if dstyle <> D2D1_DASH_STYLE_SOLID then
      D2DFactory.CreateStrokeStyle(D2D1StrokeStyleProperties(D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT,
          D2D1_CAP_STYLE_SQUARE, D2D1_LINE_JOIN_MITER, 10, dstyle, 0), nil, 0, FStrokeStyle);
  end;

  result := FStrokeStyle;
end;

procedure TD2DPen.SetPenStyle(const Value: TPenStyle);
begin
  if FPenStyle <> Value then
  begin
    FPenStyle := Value;
    Change;
  end;
end;

{ TD2DRegion }

constructor TD2DRegion.Create(APath: TDgrGraphicsPath);
begin
  FPath := APath as TD2DGraphicsPath;
  FD2DPath := TD2DGraphicsPath(APath).D2DPath;
end;

function TD2DRegion.GetHRGN(ACanvas: TDgrCanvas): HRGN;
begin
  result := 0;
end;

function TD2DRegion.IsVisible(ARect: TSquare): boolean;
var
  geometry: ID2D1Geometry;
  transform: TD2DMatrix3x2F;
  bounds: TD2DRectF;
begin
  FPath.CheckFinished;
  if FPath.TransPath <> nil then
  begin
    geometry := FPath.TransPath;
    transform := TD2DMatrix3x2F.Identity;
  end
  else
  begin
    geometry := FPath.D2DPath;
    transform := FPath.TransMatrix;
  end;

  geometry.GetBounds(transform, bounds);
  result := RectsTouch(Square(bounds.left, bounds.top, bounds.right, bounds.bottom), ARect)
end;

{ TD2DPicture }

constructor TD2DPicture.Create;
begin
  inherited;
  //
end;

destructor TD2DPicture.Destroy;
begin
  //
  inherited;
end;

{ TD2DGraphic }

procedure TD2DGraphic.Assign(Source: TPersistent);
begin
  inherited;
end;

procedure TD2DGraphic.Changed(Sender: TObject);
begin
  inherited;
  FD2DBitmap := nil;
  FWICBitmap := nil;
end;

constructor TD2DGraphic.Create;
begin
  inherited;
end;

procedure TD2DGraphic.CreateD2DBitmap(ACanvas: TDirect2DCanvas);
var
  hglobal: THandle;
  gStream: IStream;
  pcbWrite: Longint;
  gsize: Largeint;
  decoder: IWICBitmapDecoder;
  frame: IWICBitmapFrameDecode;
  converter: IWICFormatConverter;
begin
  if FWICBitmap = nil then
  begin
    hglobal := GlobalAlloc(GMEM_MOVEABLE, DataStream.Size);
    if (hglobal = 0) then
      raise Exception.Create('Could not allocate memory for image');
    try
      gStream := nil;
      CreateStreamOnHGlobal(hglobal, True, gStream);
      {$WARNINGS OFF}
      gStream.Write(DataStream.Memory, DataStream.Size, @pcbWrite);
      {$WARNINGS ON}
      gStream.Seek(0, STREAM_SEEK_SET, gsize);

      if (WICImagingFactory.CreateDecoderFromStream(gStream, GUID_NULL, WICDecodeMetadataCacheOnLoad, decoder) = S_OK)
        and (decoder.GetFrame(0, frame) = S_OK)
        and (WICImagingFactory.CreateFormatConverter(converter) = S_OK)
        and (converter.Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nil, 0, WICBitmapPaletteTypeCustom) = S_OK)
      then
      begin
        WICImagingFactory.CreateBitmapFromSource(converter, WICBitmapCacheOnLoad, FWICBitmap);
        if FBitmapTransparent then
          MakeBitmapTransparent(FWICBitmap);
      end;
    finally
      GlobalFree(hglobal);
    end;
  end;

  if FWICBitmap <> nil then
    ACanvas.RenderTarget.CreateBitmapFromWicBitmap(FWICBitmap, nil, FD2DBitmap)
end;

destructor TD2DGraphic.Destroy;
begin
  FD2DBitmap := nil;
  FWICBitmap := nil;
  inherited;
end;

procedure TD2DGraphic.DoDraw(ACanvas: TCanvas; const ARect: TSquare);
begin
  inherited;
end;

function TD2DGraphic.DoGetImageSizes: boolean;
var
  hglobal: THandle;
  gStream: IStream;
  pcbWrite: Longint;
  gsize: Largeint;
  gwidth, gheight: cardinal;
  decoder: IWICBitmapDecoder;
  frame: IWICBitmapFrameDecode;
  bmpSize: TD2DSizeF;
begin
  result := False;
  if FD2DBitmap <> nil then
  begin
    FD2DBitmap.GetSize(bmpSize);
    SetWidth(Round(bmpSize.width));
    SetHeight(Round(bmpSize.height));
    result := True;
  end
  else
  begin
    hglobal := GlobalAlloc(GMEM_MOVEABLE, DataStream.Size);
    if (hglobal = 0) then
      raise Exception.Create('Could not allocate memory for image');
    try
      gStream := nil;
      CreateStreamOnHGlobal(hglobal, True, gStream);
      {$WARNINGS OFF}
      gStream.Write(DataStream.Memory, DataStream.Size, @pcbWrite);
      {$WARNINGS ON}
      gStream.Seek(0, STREAM_SEEK_SET, gsize);

      if (WICImagingFactory.CreateDecoderFromStream(gStream, GUID_NULL, WICDecodeMetadataCacheOnLoad, decoder) = S_OK)
        and (decoder.GetFrame(0, frame) = S_OK) then
      begin
        frame.GetSize(gwidth, gheight);

        SetWidth(gwidth);
        SetHeight(gheight);

        result := True;
      end;
    finally
      GlobalFree(hglobal);
    end;
  end;
end;

function TD2DGraphic.GetD2DBitmap(ACanvas: TDirect2DCanvas): ID2D1Bitmap;
begin
  if FD2DBitmap = nil then
    CreateD2DBitmap(ACanvas);
  result := FD2DBitmap;
end;

procedure TD2DGraphic.MakeBitmapTransparent(ABMP: IWICBitmap);
var
  bmpLock: IWICBitmapLock;
  bmpPointer: WICInProcPointer;
  bufSize, rgbTransp: cardinal;
  pPixel: ^byte;
  r, g, b: byte;
  i: integer;

  function wRect(AX, AY, AW, AH: integer): WICRect;
  begin
    with result do
    begin
      X := AX;
      Y := AY;
      Width := AW;
      Height := AH;
    end;
  end;

begin
  bmpLock := nil;
  if ABMP.Lock(wRect(0, Height-1, 1, 1), WICBitmapLockRead, bmpLock) = S_OK then
  begin
    bmpLock.GetDataPointer(bufSize, bmpPointer);
    rgbTransp := bmpPointer^;

    if ABMP.Lock(wRect(0, 0, Width, Height), WICBitmapLockWrite, bmpLock) = S_OK then
    begin
      bmpLock.GetDataPointer(bufSize, bmpPointer);
      pPixel := Addr(bmpPointer^);
      r := 0;
      g := 0;
      b := 0;

      for i := 0 to bufSize - 1 do
      begin
        case (i + 1) mod 4 of
          0: // alpha
             if RGB(r, g, b) = rgbTransp then
               pPixel^ := 0;
          1: r := pPixel^; // red
          2: g := pPixel^; // green
          3: b := pPixel^; // blue
        end;
        Inc(pPixel);
      end;

      bmpLock := nil;
    end;
  end;
end;

end.

