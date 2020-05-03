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

unit GdipClasses;

{$I Diagram.Inc}

interface

uses
  Windows, SysUtils, Classes,
{$IFDEF GDIPLUS}
  DgrGdipApi, DgrGdipObj,
{$ENDIF}
  Graphics,
  ActiveX, DiagramUtils, DgrClasses;

{$IFDEF GDIPLUS}
type
  /// Description:
  ///   TGdipGraphic is the specific Graphic class for GDI+ graphic library.
  TGdipGraphic = class(TDgrGraphic)
  private
    FGPImage: TGPImage;
    procedure CreateGPImage;
    procedure DestroyGPImage;
  protected
    procedure Changed(Sender: TObject); override;
    function GPImage: TGPImage;
    function DoGetImageSizes: boolean; override;
    procedure DoDraw(ACanvas: TCanvas; const ARect: TSquare); override;
  public
    constructor Create; override;
    destructor Destroy; override;
  end;

  /// Description:
  ///   TGDipPicture is the specific Picture class for GDI+ graphic library.
  TGdipPicture = class(TDgrPicture)
  private
    FGPImage: TGPImage;
    procedure CreateGPImage;
    procedure DestroyGPImage;
  protected
    procedure Changed(Sender: TObject); override;
    function GPImage: TGPImage;
  public
    constructor Create; override;
    destructor Destroy; override;
  end;

  /// Description:
  ///   TGdipImage is the specific Image class for GDI+ graphic library.
  TGdipImage = class(TDgrImage)
  private
    FGPImage: TGPImage;
    procedure CreateGPImage;
    procedure DestroyGPImage;
    function GetGPImage: TGPImage;
  protected
    property GPImage: TGPImage read GetGPImage write FGPImage;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  /// Description:
  ///   TGdipBrush is the specific brush class for GDI+ graphic library.
  TGdipBrush = class(TDgrBrush)
  private
    FGPBrush: TGPBrush;
    FGradientRect: TGPRectF;
    FHatchStyle: THatchStyle;
    FRotMatrix: TGPMatrix;
    procedure CreateGPBrush;
    procedure DestroyGPBrush;
    procedure SetHatchStyle(const Value: THatchStyle);
  protected
    procedure Change; override;
    function CreatePicture: TDgrPicture; override;
    function GetGPBrush: TGPBrush;
    procedure DoUpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot); override;
  public
    procedure Assign(Source: TPersistent); override;
    constructor Create; override;
    destructor Destroy; override;

    /// Description:
    ///   Retrieves the native GDI+ object for the brush.
    property GPBrush: TGPBrush read GetGPBrush;
  published

    /// Description:
    ///   Specified the hatch style for the brush when BrushMode property is set to bmHatch.
    property HatchStyle: THatchStyle read FHatchStyle write SetHatchStyle;
  end;

  /// Description:
  ///   TGdipPen is the specific pen class for GDI+ graphic library.
  TGdipPen = class(TDgrPen)
  private
    FGPPen: TGPPen;
    FDashStyle: TDashStyle;
    procedure CreateGPPen;
    procedure DestroyGPPen;
    procedure SetDashStyle(const Value: TDashStyle);
  protected
    procedure Change; override;
    function GetGPPen: TGPPen;
  public
    procedure Assign(Source: TPersistent); override;
    constructor Create; override;
    destructor Destroy; override;

    /// Description:
    ///   Retrieves the native GDI+ object for the pen.
    property GPPen: TGPPen read GetGPPen;
  published

    /// Description:
    ///   Specifies the dash style of the pen.  
    property DashStyle: TDashStyle read FDashStyle write SetDashStyle;
  end;

  /// Description:
  ///   TGPCanvas is just like a TCanvas object, with similar methods, but uses GDI+ functions for the drawing
  ///   operations. TGPCanvas does not descend from TCanvas, it just implement methods with similar names.
  TGPCanvas = class(TDgrCanvas)
  private
    FBrush: TGdipBrush;
    FInternalGraphics: TGPGraphics;
    FPen: TGdipPen;
    FTempGraphics: TGPGraphics;
    FTransMatrix: TGPMatrix;
    FDrawingState: cardinal;
    function CreateGPFont(AFont: TFont): TGPFont;
    function CreateGPStringFormat(AHAlign: TAlignment; AVAlign: TVertAlign; AWrap, ARightToLeft: boolean): TGPStringFormat;
    procedure DestroyGraphics;
    function GetGraphics: TGPGraphics;
    procedure DoDrawGPPath(APath: TGPGraphicsPath);
    procedure DoFillGPPath(APath: TGPGraphicsPath);
  protected
    function GetBrush: TDgrBrush; override;
    function GetHandle: HDC; override;
    function GetPen: TDgrPen; override;
    procedure SetHandle(const Value: HDC); override;

    /// Description:
    ///   Draws an ellipse using the current brush and pen.
    procedure DoDrawEllipse(x, y, width, height: number); override;

    /// Description:
    ///   Draws a line from point X1, Y1 to X2, Y2.
    procedure DoDrawLine(X1, Y1, X2, Y2: number); override;

    /// Description:
    ///   Draws the path specified by APath using the current pen.
    procedure DoDrawPath(APath: TDgrGraphicsPath); override;

    /// Description:
    ///   Draws a rectangle using current brush and pen.
    procedure DoDrawRectangle(x, y, width, height: number); override;
    procedure DoFillPath(APath: TDgrGraphicsPath); override;

    /// Description:
    ///   Draws a polygon specified by the array of points using current brush and pen.
    procedure DoPolygon(APoints: TDotArray); override;

    /// Description:
    ///   Draws the image specified by Graphic, stretched in rectangle Rect, using the specified transparency.    
    procedure DoStretchDraw(const Rect: TSquare; Graphic: TGraphic;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False); overload; override;
    procedure DoStretchDraw(const Rect: TSquare; ADgrImage: TDgrImage;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False); overload; override;
    procedure DoStretchDrawGPImage(const Rect: TSquare; AGPImage: TGPImage;
      ATransparency: integer = 0; ABitmapTransparent: boolean=False);
    procedure DoUpdateFactors(ASourceRect, ADestRect: TSquare; AScaleX, AScaleY: number); override;
  public

    /// Description:
    ///   Creates a GDI plus canvas specified by the HDC handle.
    constructor Create(AHandle: HDC = 0); override;
    destructor Destroy; override;
    function CreateBrush: TDgrBrush; override;
    function CreateGraphic: TDgrGraphic; override;
    function CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine; override;
    function CreatePath: TDgrGraphicsPath; override;
    function  CreatePen: TDgrPen; override;
    procedure DrawString(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment;
      AVAlign: TVertAlign; AWrap, ARightToLeft: boolean; ATransparency: integer); override;
    procedure RestoreDrawingState; override;
    procedure SaveDrawingState; override;
    function StringBounds(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment;
      AVAlign: TVertAlign; AWrap, ARightToLeft: boolean): TSquare; override;
    function TranslateTransform(AX, AY: number): integer; override;
    function ScaleTransform(AX, AY: number): integer; override;
    function ResetClip: integer; override;
    function ResetTransform: integer; override;
    function RotateTransform(AAngle: number): integer; override;
    function SetClip(ARect: TSquare): integer; overload; override;
    function SetClip(ARegion: HRGN): integer; overload; override;
    procedure DrawPath(APath: TDgrGraphicsPath); overload;
    procedure DrawPath(APath: TGPGraphicsPath); overload;

    /// Description:
    ///   Add a rounded rectangle to the path.
    procedure AddRoundRectPath(APath: TDgrGraphicsPath; X1, Y1, X2, Y2, X3, Y3: number); overload;
    procedure AddRoundRectPath(APath: TGPGraphicsPath; X1, Y1, X2, Y2, X3, Y3: number); overload;

    /// Description:
    ///   Path draws the path specified by APath using the current pen and brush.
    procedure Path(APath: TDgrGraphicsPath); overload;
    procedure Path(APath: TGPGraphicsPath); overload;

    /// Description:
    ///   Returns a TGPGraphics object related to the canvas.
    property GPGraphics: TGPGraphics read GetGraphics;
  end;

  /// Description:
  ///   Use TGPBlockDrawer class methods and properties to make it easy to draw blocks using GDI+ API and
  ///   converting coordinates. In general, you set SourceRect property to contain the rectangle where you want
  ///   to paint to. DestRect property must contain the destination rectangle. So, when using drawing methods,
  ///   pass coordinates like you were painting to original rect, and it will be paint on cur rect coordinates.
  TGPBlockDrawer = class(TDgrBlockDrawer)
  private
    FGPCanvas: TGPCanvas;
    FMatrix: TGPMatrix;
    procedure DoRotateGPPath(APath: TGPGraphicsPath);
  protected
    procedure DoRotatePath(APath: TDgrGraphicsPath); override;
    function GetCanvas: TDgrCanvas; override;
    procedure SetPaintEngine(const Value: TDgrPaintEngine); override;
  public
    constructor Create; override;
    destructor Destroy; override;

    /// Description:
    ///   TranslateRectsPath translates (and stretches) the path specified by APath from the SourceRect to
    ///   DestRect. In other words, every coordinate in APath is mapped from SourceRect to DestRect.
    procedure TranslateRectsPath(APath: TDgrGraphicsPath); override;

    /// Description:
    ///   TransformPath just calls TranslateRectsPath and then RotatePath for the specified APath.
    procedure TransformPath(APath: TDgrGraphicsPath); overload;
    procedure TransformPath(APath: TGPGraphicsPath); overload;

    /// Description:
    ///   Calls RotatePath to rotate the path specified by APath using the angle specified in the Angle property.
    procedure RotatePath(APath: TDgrGraphicsPath); overload;
    procedure RotatePath(APath: TGPGraphicsPath); overload;

    /// Description:
    ///   Sets a TGPGraphics object in the drawer to be used as device canvas. You must call SetGraphics(nil)
    ///   after using GPCanvas functions.
    procedure SetGraphics(AGPGraphics: TGPGraphics);

    /// Description:
    ///   Provides a TGPCanvas object to be used for drawing operations.
    property GPCanvas: TGPCanvas read FGPCanvas;
  end;

  /// Description:
  ///   TGdipGraphicsPath is the specific Path class for GDI+ graphic library.
  TGdipGraphicsPath = class(TDgrGraphicsPath)
  private
    FGPPath: TGPGraphicsPath;
    procedure CreateGPPath;
    procedure DestroyGPPath;
    function GetGPPath: TGPGraphicsPath;
  public
    constructor Create;
    destructor Destroy; override;
    function AddArc(x, y, width, height, startAngle, sweepAngle: number): integer; override;
    function AddBezier(x1, y1, x2, y2, x3, y3, x4, y4: number): integer; override;
    function AddEllipse(x, y, width, height: number): integer; override;
    function AddLine(x1, y1, x2, y2: number): integer; override;
    function AddLines(points: TDotArray): integer; override;
    function AddPolygon(points: TDotArray): integer; override;
    function AddRectangle(rect: TSquare): integer; override;
    function AddRoundRect(X1, Y1, X2, Y2, X3, Y3: number): integer; override;
    function CloseFigure(AClosePath: boolean=True): integer; override;
    function CreateRegion: TDgrRegion; override;
    function GetPointCount: integer; override;
    function IsVisible(x, y: Integer): boolean; override;
    function Reset: integer; override;
    function SetFillMode(fillmode: TFillMode): integer; override;
    function StartFigure: integer; override;

    property GPPath: TGPGraphicsPath read GetGPPath;
  end;

  /// Description:
  ///   TGdipPaintEngine uses a TGPGraphics object to perform GDI+ drawing operations
  ///   (for internal use by TatDiagram).
  TGdipPaintEngine = class(TDgrPaintEngine)
  private
    FGPGraphics: TGPGraphics;
  protected
    procedure SetPageUnit(const Value: TDgrPageUnit); override;
    procedure SetSmoothMode(const Value: TDgrSmoothMode); override;
    procedure SetTextRenderingMode(const Value: TDgrTextRenderingMode); override;
  public
    constructor Create(ACanvas: TCanvas; ARect: TRect); override;
    destructor Destroy; override;
    procedure FillRect(ARect: TRect; AColor: TColor); override;
    function ResetTransform: integer; override;
    function RotateTransform(AAngle: number): integer; override;
    function ScaleTransform(AX, AY: number): integer; override;
    function TranslateTransform(AX, AY: number): integer; override;
    property GPGraphics: TGPGraphics read FGPGraphics;
  end;

  /// Description:
  ///   TGdipRegion is the specific Region class for GDI+ graphic library.
  TGdipRegion = class(TDgrRegion)
  private
    FGPRegion: TGPRegion;
  public
    constructor Create(APath: TDgrGraphicsPath); override;
    destructor Destroy; override;
    function GetHRGN(ACanvas: TDgrCanvas): HRGN; override;
    function IsVisible(ARect: TSquare): boolean; override;
    property GPRegion: TGPRegion read FGPRegion;
  end;

/// Summary:
///   Builds a TGPPointF structure.
function PointGP(x, y: single): TGPPointF;

/// Summary:
///   Converts a TSquare to a TGPRectF.
function RectGP(ASquare: TSquare): TGPRectF;

/// Summary:
///   Converts a TGPRectF to a TSquare.
function ToSquare(ARectGP: TGPRectF): TSquare;
function ToRectX(ARectGP: TGPRectF): TSquare;

/// Summary:
///   Register new image file formats (PNG, TIF) to be used in TPicture objects (Picture properties).
procedure RegisterGdipFileFormats;

/// Summary:
///   Unregisters file formats registered by RegisterGdipFileFormats method.
procedure UnRegisterGdipFileFormats;

/// Description:
///   Converts a regular TColor with Alpha opacity (from 0 to 255) to a Cardinal color
///   value to be used with GDI+ functions.
function ColorToARGB(AColor: TColor; Alpha: byte = 255): DWORD;

{$ENDIF}

implementation

{$IFDEF GDIPLUS}

resourcestring
  sPNGImageFile = 'PNG Image File';
  sTIFImageFile = 'TIFF Image File';
  sGIFImageFile = 'GIF Image File';
  sJPGImageFile = 'JPG Image File';

procedure RegisterGdipFileFormats;
begin
  TPicture.RegisterFileFormat('jpg', sJPGImageFile, TGdipGraphic);
  TPicture.RegisterFileFormat('gif', sGIFImageFile, TGdipGraphic);
  TPicture.RegisterFileFormat('png', sPNGImageFile, TGdipGraphic);
  TPicture.RegisterFileFormat('tif', sTIFImageFile, TGdipGraphic);
  TPicture.RegisterFileFormat('tiff', sTIFImageFile, TGdipGraphic);
end;

procedure UnRegisterGdipFileFormats;
begin
  TPicture.UnregisterGraphicClass(TGdipGraphic);
end;

function ColorToARGB(AColor: TColor; Alpha: byte = 255): DWORD;
begin
  AColor := ColorToRgb(AColor);
  result := MakeColor(Alpha, GetRValue(AColor), GetGValue(AColor),
    GetBValue(AColor));
end;

function PointGP(x, y: single): TGPPointF;
begin
  result.x := x;
  result.y := y;
end;

function RectGP(ASquare: TSquare): TGPRectF;
begin
  result.x := ASquare.Left;
  result.y := ASquare.Top;
  result.width := ASquare.Right - ASquare.Left;
  result.height := ASquare.Bottom - ASquare.Top;
end;

function ToSquare(ARectGP: TGPRectF): TSquare;
begin
  result.Left := ARectGP.x;
  result.Top := ARectGP.y;
  result.Right := ARectGP.x + ARectGP.width;
  result.Bottom := ARectGP.y + ARectGP.height;
end;

function ToRectX(ARectGP: TGPRectF): TSquare;
begin
  result := ToSquare(ARectGP);
end;

type
  { This StreamAdapter solves a problem with Delphi VCL stream adapter.
    The problem happens when a PNG image is being loaded from a Stream by the Gdi+ api.
    The ntdll will raise a breakpoint. This class fixes the problem }
  TFixStreamAdapter = class(TStreamAdapter)
  public
    function Stat(out statstg: TStatStg; grfStatFlag: Longint): HResult;
      override; stdcall;
  end;

function TFixStreamAdapter.Stat(out statstg: TStatStg;
  grfStatFlag: integer): HResult;
begin
  result := inherited Stat(statstg, grfStatFlag);
{$WARNINGS OFF}
  statstg.pwcsName := nil;
{$WARNINGS ON}
end;

{ TGdipGraphic }

procedure TGdipGraphic.Changed(Sender: TObject);
begin
  inherited;
  DestroyGPImage;
end;

constructor TGdipGraphic.Create;
begin
  inherited;
  FGPImage := nil;
end;

procedure TGdipGraphic.CreateGPImage;
var
  pstm: IStream;
  pcbWrite: Longint;
  aSize: Largeint;
  TempImage: TGPImage;
  TempGraphics: TGPGraphics;
  hglobal: THandle;
begin
  DataStream.Position := 0;

  hglobal := GlobalAlloc(GMEM_MOVEABLE, DataStream.Size);
  if (hglobal = 0) then
    raise Exception.Create('Could not allocate memory for image');
  try

    pstm := nil;
    // Create IStream* from global memory
    CreateStreamOnHGlobal(hglobal, TRUE, pstm);
{$WARNINGS OFF}
    pstm.Write(DataStream.Memory, DataStream.Size, @pcbWrite);
{$WARNINGS ON}
    pstm.Seek(0, STREAM_SEEK_SET, aSize);

    TempImage := TGPImage.Create(pstm);
    if TempImage.GetType = ImageTypeBitmap then
    begin
      { If the image is a bitmap, we must create a second bitmap and "copy" the original to the second one.
        If we don't do that, we should keep the stream open for the lifetime of the bitmap, so this copy
        simplifies things and we can destroy the stream (which is destroyed automatically when TempImage is destroyed)
        We don't need to do that with metafiles }
      FGPImage := TGPBitmap.Create(TempImage.GetWidth, TempImage.GetHeight,
        PixelFormat32bppARGB);
      TempGraphics := TGPGraphics.Create(FGPImage);
      TempGraphics.DrawImage(TempImage, 0, 0, TempImage.GetWidth,
        TempImage.GetHeight);
      TempGraphics.Free;
      TempImage.Free;
    end
    else
      FGPImage := TempImage;

  finally
    GlobalFree(hglobal);
  end;
end;

destructor TGdipGraphic.Destroy;
begin
  DestroyGPImage;
  inherited;
end;

procedure TGdipGraphic.DestroyGPImage;
begin
  if FGPImage <> nil then
  begin
    FGPImage.Free;
    FGPImage := nil;
  end;
end;

function TGdipGraphic.DoGetImageSizes: boolean;
var
  multi: TGPImage;
  pstm: IStream;
  hglobal: THandle;
  pcbWrite: Longint;
  aSize: Largeint;
begin
  hglobal := GlobalAlloc(GMEM_MOVEABLE, DataStream.Size);
  if (hglobal = 0) then
    raise Exception.Create('Could not allocate memory for image');
  try
    pstm := nil;
    // Create IStream* from global memory
    CreateStreamOnHGlobal(hglobal, TRUE, pstm);
{$WARNINGS OFF}
    pstm.Write(DataStream.Memory, DataStream.Size, @pcbWrite);
{$WARNINGS ON}
    pstm.Seek(0, STREAM_SEEK_SET, aSize);
    multi := TGPImage.Create(pstm);

    SetWidth(multi.GetWidth);
    SetHeight(multi.GetHeight);

    result := TRUE;

    multi.Free;
  finally
    GlobalFree(hglobal);
  end;
end;

procedure TGdipGraphic.DoDraw(ACanvas: TCanvas; const ARect: TSquare);
var
  GPCanvas: TGPCanvas;
  gdipImage: TGdipImage;
begin
  inherited;
  GPCanvas := TGPCanvas.Create(ACanvas.Handle);
  gdipImage := TGdipImage.Create;
  try
    gdipImage.GPImage := GPImage.Clone;
    GPCanvas.StretchDraw(ARect, gdipImage, 0, Transparent);
  finally
    GPCanvas.Free;
    gdipImage.Free;
  end;
end;

function TGdipGraphic.GPImage: TGPImage;
begin
  if FGPImage = nil then
    CreateGPImage;
  result := FGPImage;
end;

{ TGdipPicture }

procedure TGdipPicture.Changed(Sender: TObject);
begin
  inherited;
  DestroyGPImage;
end;

constructor TGdipPicture.Create;
begin
  inherited;
  FGPImage := nil;
end;

procedure TGdipPicture.CreateGPImage;
var
  adapter: TStreamAdapter;
begin
  adapter := TFixStreamAdapter.Create(DataStream);
  adapter.Stream.Position := 0;
  Graphic.SaveToStream(DataStream);
  adapter.Stream.Position := 0;
  FGPImage := TGPImage.Create(adapter);
end;

destructor TGdipPicture.Destroy;
begin
  DestroyGPImage;
  inherited;
end;

procedure TGdipPicture.DestroyGPImage;
begin
  if FGPImage <> nil then
  begin
    FGPImage.Free;
    FGPImage := nil;
  end;
end;

function TGdipPicture.GPImage: TGPImage;
begin
  if FGPImage = nil then
    CreateGPImage;
  result := FGPImage;
end;

{ TGdipBrush }

procedure TGdipBrush.Assign(Source: TPersistent);
begin
  inherited;
  if Source is TGdipBrush then
    FHatchStyle := TGdipBrush(Source).HatchStyle
  else if Source is TBrush then
    case TBrush(Source).Style of
      bsHorizontal:
        FHatchStyle := HatchStyleHorizontal;
      bsVertical:
        FHatchStyle := HatchStyleVertical;
      bsFDiagonal:
        FHatchStyle := HatchStyleForwardDiagonal;
      bsBDiagonal:
        FHatchStyle := HatchStyleBackwardDiagonal;
      bsCross:
        FHatchStyle := HatchStyleCross;
      bsDiagCross:
        FHatchStyle := HatchStyleDiagonalCross;
    end;
end;

procedure TGdipBrush.Change;
begin
  inherited;
  DestroyGPBrush;
end;

constructor TGdipBrush.Create;
begin
  inherited;
  FHatchStyle := HatchStyleHorizontal;
  FRotMatrix := TGPMatrix.Create;
end;

procedure TGdipBrush.CreateGPBrush;
var
  colorcount: integer;
  path: TGPGraphicsPath;
  AMatrix: TGPMatrix;
const
  BlendFactors: array [0 .. 2] of single = (0.0, 1.0, 0.0);
  BlendPositions: array [0 .. 2] of single = (0.0, 0.5, 1.0);
  Colors: array [0 .. 0] of Cardinal = (0);
begin
  case BrushMode of
    bmClear:
      FGPBrush := TGPSolidBrush.Create(0);
    bmHatch:
      FGPBrush := TGPHatchBrush.Create(FHatchStyle,
        ColorToARGB(Color, GetAlpha1), ColorToARGB(Color2, GetAlpha2));
    bmTexture:
      begin
        FGPBrush := TGPTextureBrush.Create(TGdipPicture(Texture).GPImage);
        with TGPTextureBrush(FGPBrush) do
        begin
          SetTransform(FRotMatrix);
          TranslateTransform(FGradientRect.x, FGradientRect.y);
        end;
      end;
    bmGradient:
      begin
        case GradientMode of
          gmTopBottom:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color, GetAlpha1),
              ColorToARGB(Color2, GetAlpha2), LinearGradientModeVertical);
          gmBottomTop:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color2, GetAlpha2),
              ColorToARGB(Color, GetAlpha1), LinearGradientModeVertical);
          gmLeftRight:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color, GetAlpha1),
              ColorToARGB(Color2, GetAlpha2), LinearGradientModeHorizontal);
          gmRightLeft:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color2, GetAlpha2),
              ColorToARGB(Color, GetAlpha1), LinearGradientModeHorizontal);
          gmLeftTop:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color, GetAlpha1),
              ColorToARGB(Color2, GetAlpha2),
              LinearGradientModeForwardDiagonal
              );
          gmRightTop:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color, GetAlpha1),
              ColorToARGB(Color2, GetAlpha2),
              LinearGradientModeBackwardDiagonal);
          gmLeftBottom:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color2, GetAlpha2),
              ColorToARGB(Color, GetAlpha1),
              LinearGradientModeBackwardDiagonal);
          gmRightBottom:
            FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
              ColorToARGB(Color2, GetAlpha2),
              ColorToARGB(Color, GetAlpha1),
              LinearGradientModeForwardDiagonal);
          gmInOut:
            begin
              path := TGPGraphicsPath.Create;
              try
                path.AddRectangle(FGradientRect);
                FGPBrush := TGPPathGradientBrush.Create(path);
                TGPPathGradientBrush(FGPBrush).SetCenterColor
                  (ColorToARGB(Color, GetAlpha1));
                Colors[0] := ColorToARGB(Color2, GetAlpha2);
                colorcount := 1;
{$WARNINGS OFF}
                TGPPathGradientBrush(FGPBrush).SetSurroundColors(@Colors[0],
                  colorcount);
{$WARNINGS ON}
              finally
                path.Free;
              end;
            end;
          gmOutIn:
            begin
              path := TGPGraphicsPath.Create;
              try
                path.AddRectangle(FGradientRect);
                FGPBrush := TGPPathGradientBrush.Create(path);
                TGPPathGradientBrush(FGPBrush).SetCenterColor
                  (ColorToARGB(Color2, GetAlpha2));
                Colors[0] := ColorToARGB(Color, GetAlpha1);
                colorcount := 1;
{$WARNINGS OFF}
                TGPPathGradientBrush(FGPBrush).SetSurroundColors(@Colors[0],
                  colorcount);
{$WARNINGS ON}
              finally
                path.Free;
              end;
            end;
          gmHorzInOut:
            begin
              FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
                ColorToARGB(Color2, GetAlpha2), ColorToARGB(Color, GetAlpha1),
                LinearGradientModeVertical);
{$WARNINGS OFF}
              TGPLinearGradientBrush(FGPBrush).SetBlend(@BlendFactors[0],
                @BlendPositions[0], 3);
{$WARNINGS ON}
            end;
          gmHorzOutIn:
            begin
              FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
                ColorToARGB(Color, GetAlpha1), ColorToARGB(Color2, GetAlpha2),
                LinearGradientModeVertical);
{$WARNINGS OFF}
              TGPLinearGradientBrush(FGPBrush).SetBlend(@BlendFactors[0],
                @BlendPositions[0], 3);
{$WARNINGS ON}
            end;
          gmVertInOut:
            begin
              FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
                ColorToARGB(Color2, GetAlpha2), ColorToARGB(Color, GetAlpha1),
                LinearGradientModeHorizontal);
{$WARNINGS OFF}
              TGPLinearGradientBrush(FGPBrush).SetBlend(@BlendFactors[0],
                @BlendPositions[0], 3);
{$WARNINGS ON}
            end;
          gmVertOutIn:
            begin
              FGPBrush := TGPLinearGradientBrush.Create(FGradientRect,
                ColorToARGB(Color, GetAlpha1), ColorToARGB(Color2, GetAlpha2),
                LinearGradientModeHorizontal);
{$WARNINGS OFF}
              TGPLinearGradientBrush(FGPBrush).SetBlend(@BlendFactors[0],
                @BlendPositions[0], 3);
{$WARNINGS ON}
            end;
        end;

        AMatrix := TGPMatrix.Create;
        try
          if FGPBrush is TGPLinearGradientBrush then
          begin
            TGPLinearGradientBrush(FGPBrush).GetTransform(AMatrix);
            AMatrix.Multiply(FRotMatrix, MatrixOrderAppend);
            TGPLinearGradientBrush(FGPBrush).SetTransform(AMatrix);
          end
          else if FGPBrush is TGPPathGradientBrush then
          begin
            TGPPathGradientBrush(FGPBrush).GetTransform(AMatrix);
            AMatrix.Multiply(FRotMatrix, MatrixOrderAppend);
            TGPPathGradientBrush(FGPBrush).SetTransform(AMatrix);
          end;
        finally
          AMatrix.Free;
        end;
      end;
  else
    // bmSolid
    FGPBrush := TGPSolidBrush.Create(ColorToARGB(Color, GetAlpha1));
  end;
end;

function TGdipBrush.CreatePicture: TDgrPicture;
begin
  result := TGdipPicture.Create;
end;

destructor TGdipBrush.Destroy;
begin
  DestroyGPBrush;
  FRotMatrix.Free;
  inherited;
end;

procedure TGdipBrush.DestroyGPBrush;
begin
  if FGPBrush <> nil then
  begin
    FGPBrush.Free;
    FGPBrush := nil;
  end;
end;

procedure TGdipBrush.DoUpdateBrushPosition(ARect: TSquare; AAngle: number; ARotCenter: TDot);
begin
  FGradientRect := RectGP(ARect);
  FRotMatrix.Reset;
  if AAngle <> 0 then
    FRotMatrix.RotateAt(AAngle, MakePoint(ARotCenter.x, ARotCenter.y),
      MatrixOrderAppend);
end;

function TGdipBrush.GetGPBrush: TGPBrush;
begin
  if FGPBrush = nil then
    CreateGPBrush;
  result := FGPBrush;
end;

procedure TGdipBrush.SetHatchStyle(const Value: THatchStyle);
begin
  if FHatchStyle <> Value then
  begin
    FHatchStyle := Value;
    Change;
  end;
end;

{ TGdipPen }

procedure TGdipPen.Assign(Source: TPersistent);
begin
  inherited;
  if Source is TGdipPen then
    FDashStyle := TGdipPen(Source).FDashStyle
  else if Source is TPen then
    case TPen(Source).Style of
      psSolid:
        FDashStyle := DashStyleSolid;
      psDash:
        FDashStyle := DashStyleDash;
      psDot:
        FDashStyle := DashStyleDot;
      psDashDot:
        FDashStyle := DashStyleDashDot;
      psDashDotDot:
        FDashStyle := DashStyleDashDotDot;
      psClear:
        Transparency := 100;
    else
      FDashStyle := DashStyleSolid;
    end;
end;

procedure TGdipPen.Change;
begin
  inherited;
  DestroyGPPen;
end;

constructor TGdipPen.Create;
begin
  inherited;
  FDashStyle := DashStyleSolid;
end;

procedure TGdipPen.CreateGPPen;
begin
  FGPPen := TGPPen.Create(ColorToARGB(Color, GetAlpha), width);
  FGPPen.SetDashStyle(FDashStyle);
end;

destructor TGdipPen.Destroy;
begin
  DestroyGPPen;
  inherited;
end;

procedure TGdipPen.DestroyGPPen;
begin
  if FGPPen <> nil then
  begin
    FGPPen.Free;
    FGPPen := nil;
  end;
end;

function TGdipPen.GetGPPen: TGPPen;
begin
  if FGPPen = nil then
    CreateGPPen;
  result := FGPPen;
end;

procedure TGdipPen.SetDashStyle(const Value: TDashStyle);
begin
  if FDashStyle <> Value then
  begin
    FDashStyle := Value;
    Change;
  end;
end;

{ TGPCanvas }

constructor TGPCanvas.Create(AHandle: HDC);
begin
  inherited;
  FBrush := TGdipBrush.Create;
  FInternalGraphics := TGPGraphics.Create(AHandle);
  FPen := TGdipPen.Create;
  FTempGraphics := nil;
  FTransMatrix := TGPMatrix.Create;
end;

function TGPCanvas.CreateBrush: TDgrBrush;
begin
  result := TGdipBrush.Create;
end;

function TGPCanvas.CreateGraphic: TDgrGraphic;
begin
  result := TGdipGraphic.Create;
end;

function TGPCanvas.CreatePaintEngine(ACanvas: TCanvas; ARect: TRect): TDgrPaintEngine;
begin
  result := TGdipPaintEngine.Create(ACanvas, ARect);
end;

function TGPCanvas.CreatePath: TDgrGraphicsPath;
begin
  result := TGdipGraphicsPath.Create;
end;

function TGPCanvas.CreatePen: TDgrPen;
begin
  result := TGdipPen.Create;
end;

procedure TGPCanvas.DrawPath(APath: TDgrGraphicsPath);
begin
  inherited DrawPath(APath);
end;

procedure TGPCanvas.DrawPath(APath: TGPGraphicsPath);
begin
  // GDI+ backward compatibility
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);
  DoDrawGPPath(APath);
  Changed;
end;

procedure TGPCanvas.AddRoundRectPath(APath: TDgrGraphicsPath; X1, Y1, X2, Y2, X3, Y3: number);
begin
  inherited AddRoundRectPath(APath, X1, Y1, X2, Y2, X3, Y3);
end;

procedure TGPCanvas.AddRoundRectPath(APath: TGPGraphicsPAth; X1, Y1, X2, Y2, X3, Y3: number);
begin
  // GDI+ backward compatibility
  APath.StartFigure;
  APath.AddArc(x2 - x3, y1, x3, y3, 270, 90);
  APath.AddArc(x2 - x3, y2 - y3, x3, y3, 0, 90);
  APath.AddArc(x1, y2 - y3, x3, y3, 90, 90);
  APath.AddArc(x1, y1, x3, y3, 180, 90);
  APath.CloseFigure;
end;

procedure TGPCanvas.Path(APath: TDgrGraphicsPath);
begin
  inherited Path(APath);
end;

procedure TGPCanvas.Path(APath: TGPGraphicsPath);
begin
  // GDI+ backward compatibility
  Changing;
  RequiredState([csHandleValid, csPenValid, csBrushValid]);
  DoFillGPPath(APath);
  DoDrawGPPath(APath);
  Changed;
end;

procedure TGPCanvas.DrawString(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment;
  AVAlign: TVertAlign; AWrap, ARightToLeft: boolean; ATransparency: integer);
var
  gpBrush: TGPBrush;
  gpFont: TGPFont;
  gpRect: TGPRectF;
  strFormat: TGPStringFormat;
begin
  gpBrush := TGPSolidBrush.Create(ColorToARGB(AFont.Color, Round((100 - ATransparency) * 2.55)));
  gpFont := CreateGPFont(AFont);
  strFormat := CreateGPStringFormat(AHAlign, AVAlign, AWrap, ARightToLeft);
  try
    gpRect := MakeRect(ARect.Left, ARect.Top, ARect.Right - ARect.Left, ARect.Bottom - ARect.Top);
    GPGraphics.DrawString(AStr, -1, gpFont, gpRect, strFormat, gpBrush);
  finally
    gpBrush.Free;
    gpFont.Free;
    strFormat.Free;
  end;
end;

procedure TGPCanvas.RestoreDrawingState;
begin
  GPGraphics.Restore(FDrawingState);
end;

procedure TGPCanvas.SaveDrawingState;
begin
  FDrawingState := GPGraphics.Save;
end;

function TGPCanvas.StringBounds(AStr: string; AFont: TFont; ARect: TSquare; AHAlign: TAlignment;
  AVAlign: TVertAlign; AWrap, ARightToLeft: boolean): TSquare;
var
  gpFont: TGPFont;
  sizeRect: TGPRectF;
  strFormat: TGPStringFormat;
begin
  gpFont := CreateGPFont(AFont);
  strFormat := CreateGPStringFormat(AHAlign, AVAlign, AWrap, ARightToLeft);
  try
    GPGraphics.MeasureString(AStr, -1, gpFont, RectGP(ARect), strFormat, sizeRect);
    result.Left := sizeRect.X;
    result.Top := sizeRect.Y;
    result.Right := sizeRect.X + sizeRect.Width;
    result.Bottom := sizeRect.Y + sizeRect.Height;
  finally
    gpFont.Free;
    strFormat.Free;
  end;
end;

function TGPCanvas.TranslateTransform(AX, AY: number): integer;
begin
  result := Ord(GPGraphics.TranslateTransform(AX, AY));
end;

function TGPCanvas.ScaleTransform(AX, AY: number): integer;
begin
  result := Ord(GPGraphics.ScaleTransform(AX, AY));
end;

function TGPCanvas.RotateTransform(AAngle: number): integer;
begin
  result := Ord(GPGraphics.RotateTransform(AAngle));
end;

function TGPCanvas.SetClip(ARect: TSquare): integer;
begin
  result := Ord(GPGraphics.SetClip(RectGP(ARect)));
end;

function TGPCanvas.SetClip(ARegion: HRGN): integer;
begin
  result := Ord(GPGraphics.SetClip(ARegion));
end;

function TGPCanvas.ResetClip: integer;
begin
  result := Ord(GPGraphics.ResetClip);
end;

function TGPCanvas.ResetTransform;
begin
  result := Ord(GPGraphics.ResetTransform);
end;

function TGPCanvas.CreateGPFont(AFont: TFont): TGPFont;
var
  style: integer;
begin
  style := FontStyleRegular;
  if fsBold in AFont.Style then
    style := style + FontStyleBold;
  if fsItalic in AFont.Style then
    style := style + FontStyleItalic;
  if fsUnderline in AFont.Style then
    style := style + FontStyleUnderline;
  if fsStrikeOut in AFont.Style then
    style := style + FontStyleStrikeout;
  result := TGPFont.Create(AFont.Name, -AFont.Height, style, UnitPixel);
end;

function TGPCanvas.CreateGPStringFormat(AHAlign: TAlignment; AVAlign: TVertAlign; AWrap, ARightToLeft: boolean): TGPStringFormat;
var
  flags: integer;
begin
  result := TGPStringFormat.Create;
  case AHAlign of
    taLeftJustify:
      result.SetAlignment(StringAlignmentNear);
    taRightJustify:
      result.SetAlignment(StringAlignmentFar);
    taCenter:
      result.SetAlignment(StringAlignmentCenter);
  end;
  case AValign of
    vaTop:
      result.SetLineAlignment(StringAlignmentNear);
    vaBottom:
      result.SetLineAlignment(StringAlignmentFar);
    vaCenter:
      result.SetLineAlignment(StringAlignmentCenter);
  end;
  flags := StringFormatFlagsNoClip;
  if not AWrap then
    flags := flags or StringFormatFlagsNoWrap;
  if ARightToLeft then
    flags := flags or StringFormatFlagsDirectionRightToLeft;
  result.SetFormatFlags(flags);
end;

destructor TGPCanvas.Destroy;
begin
  FBrush.Free;
  FPen.Free;
  FTransMatrix.Free;
  DestroyGraphics;
  inherited;
end;

procedure TGPCanvas.DestroyGraphics;
begin
  if FInternalGraphics <> nil then
  begin
    FInternalGraphics.Free;
    FInternalGraphics := nil;
  end;
end;

procedure TGPCanvas.DoDrawEllipse(x, y, width, height: number);
begin
  GPGraphics.FillEllipse(FBrush.GPBrush, x, y, width, height);
  GPGraphics.DrawEllipse(FPen.GPPen, x, y, width, height);
end;

procedure TGPCanvas.DoDrawLine(X1, Y1, X2, Y2: number);
begin
  GPGraphics.DrawLine(FPen.GPPen, X1, Y1, X2, Y2);
end;

procedure TGPCanvas.DoDrawPath(APath: TDgrGraphicsPath);
begin
  DoDrawGPPath(TGdipGraphicsPath(APath).GPPath);
end;

procedure TGPCanvas.DoDrawRectangle(x, y, width, height: number);
begin
  GPGraphics.FillRectangle(FBrush.GPBrush, x, y, width, height);
  GPGraphics.DrawRectangle(FPen.GPPen, x, y, width, height);
end;

procedure TGPCanvas.DoFillPath(APath: TDgrGraphicsPath);
begin
  DoFillGPPath(TGdipGraphicsPath(APath).GPPath);
end;

procedure TGPCanvas.DoPolygon(APoints: TDotArray);
var
  c: integer;
  pts: TDotArray;
begin
  { Optimization }
  if not MustTranslateRects then
  begin
    GPGraphics.FillPolygon(FBrush.GPBrush, PGPPointF(APoints), Length(APoints));
    GPGraphics.DrawPolygon(FPen.GPPen, PGPPointF(APoints), Length(APoints));
  end
  else
  begin
    SetLength(pts, Length(APoints));
    for c := Low(APoints) to High(APoints) do
      pts[c] := PP(APoints[c]);
    GPGraphics.FillPolygon(FBrush.GPBrush, PGPPointF(pts), Length(pts));
    GPGraphics.DrawPolygon(FPen.GPPen, PGPPointF(pts), Length(pts));
  end;
end;

procedure TGPCanvas.DoStretchDraw(const Rect: TSquare; Graphic: TGraphic;
  ATransparency: integer = 0; ABitmapTransparent: boolean=False);
var
  AGraphic: TGdipGraphic;
begin
  if Graphic is TGdipGraphic then
    DoStretchDrawGPImage(Rect, TGdipGraphic(Graphic).GPImage, ATransparency, ABitmapTransparent)
  else
  begin
    { this is not optimized, since for each stretch draw, a new graphic is assigned in order
      to get the gpimage handle. But for diagram, this code should will never be called, because
      the diagram blocks have some internal TDgrGraphic classes for optimization purposes }
    AGraphic := TGdipGraphic.Create;
    try
      AGraphic.Assign(Graphic);
      StretchDraw(Rect, AGraphic, ATransparency, ABitmapTransparent);
    finally
      AGraphic.Free;
    end;
  end;
end;

procedure TGPCanvas.DoStretchDraw(const Rect: TSquare; ADgrImage: TDgrImage;
  ATransparency: integer = 0; ABitmapTransparent: boolean=False);
begin
  DoStretchDrawGPImage(Rect, TGdipImage(ADgrImage).GPImage, ATransparency, ABitmapTransparent);
end;

procedure TGPCanvas.DoUpdateFactors(ASourceRect, ADestRect: TSquare; AScaleX, AScaleY: number);
begin
  with FTransMatrix do
  begin
    Reset;
    Translate(-(ASourceRect.Right + ASourceRect.Left) / 2,
      -(ASourceRect.Top + ASourceRect.Bottom) / 2, MatrixOrderAppend);
    Scale(AScaleX, AScaleY, MatrixOrderAppend);
    Translate((ADestRect.Right + ADestRect.Left) / 2,
      (ADestRect.Top + ADestRect.Bottom) / 2, MatrixOrderAppend);
  end;
end;

function TGPCanvas.GetBrush: TDgrBrush;
begin
  result := FBrush;
end;

function TGPCanvas.GetGraphics: TGPGraphics;
begin
  if FTempGraphics <> nil then
    result := FTempGraphics
  else
    result := FInternalGraphics;
end;

procedure TGPCanvas.DoDrawGPPath(APath: TGPGraphicsPath);
begin
  if MustTranslateRects then
    APath.Transform(FTransMatrix);
  GPGraphics.DrawPath(FPen.GPPen, APath);
end;

procedure TGPCanvas.DoFillGPPath(APath: TGPGraphicsPath);
begin
  GPGraphics.FillPath(FBrush.GPBrush, APath);
end;

function TGPCanvas.GetHandle: HDC;
begin
  if (FInternalGraphics <> nil) and (FInternalGraphics.GetHDC <> 0) then
    result := FInternalGraphics.GetHDC
  else
    result := inherited GetHandle;
end;

function TGPCanvas.GetPen: TDgrPen;
begin
  result := FPen;
end;

procedure TGPCanvas.SetHandle(const Value: HDC);
begin
  inherited;
  if Handle <> Value then
  begin
    DestroyGraphics;
    if Value <> 0 then
      FInternalGraphics := TGPGraphics.Create(Value);
  end;
end;

procedure TGPCanvas.DoStretchDrawGPImage(const Rect: TSquare;
  AGPImage: TGPImage; ATransparency: integer; ABitmapTransparent: boolean);
var
  imgatt: TGPImageAttributes;
  imgWidth, imgHeight: integer;
  ColorMap: TColorMap;
const
  // Initialize the color matrix.
  // Notice the value 0.8 in row 4, column 4.
  ColorMatrix: TColorMatrix = ((1.0, 0.0, 0.0, 0.0, 0.0),
    (0.0, 1.0, 0.0, 0.0, 0.0), (0.0, 0.0, 1.0, 0.0, 0.0),
    (0.0, 0.0, 0.0, 0.5, 0.0), (0.0, 0.0, 0.0, 0.0, 1.0));
begin
  { create image attributes to be used with image }
  imgatt := TGPImageAttributes.Create;
  try
    imgWidth := AGPImage.GetWidth;
    imgHeight := AGPImage.GetHeight;

    { set transparency }
    ColorMatrix[3, 3] := (100 - ATransparency) / 100;
    imgatt.SetColorMatrix(ColorMatrix, ColorMatrixFlagsDefault,
      ColorAdjustTypeBitmap);

    { set specific bitmap transparency }
    if ABitmapTransparent and (AGPImage.GetType = ImageTypeBitmap) then
    begin
      TGPBitmap(AGPImage).GetPixel(0, imgHeight - 1, ColorMap.oldColor);
      ColorMap.NewColor := 0;
{$WARNINGS OFF}
      imgatt.SetRemapTable(1, @ColorMap, ColorAdjustTypeBitmap);
{$WARNINGS ON}
    end;

    if GPGraphics <> nil then
      GPGraphics.DrawImage(AGPImage, RectGP(PP(Rect)), 0, 0, imgWidth, imgHeight, UnitPixel, imgatt);
  finally
    imgatt.Free;
  end;
end;

{ TGPBlockDrawer }

constructor TGPBlockDrawer.Create;
begin
  inherited;
  FGPCanvas := TGPCanvas.Create;
  //FGPCanvas.TranslateRects := true;
  FMatrix := TGPMatrix.Create;
end;

destructor TGPBlockDrawer.Destroy;
begin
  FGPCanvas.Free;
  FMatrix.Free;
  inherited;
end;

procedure TGPBlockDrawer.DoRotateGPPath(APath: TGPGraphicsPath);
var
  matrix: TGPMatrix;
begin
  // rotate at the rotation point
  matrix := TGPMatrix.Create;
  try
    matrix.RotateAt(Angle, MakePoint(RotationCenter.X, RotationCenter.Y), MatrixOrderAppend);
    APath.Transform(matrix);
  finally
    matrix.Free;
  end;
end;

procedure TGPBlockDrawer.DoRotatePath(APath: TDgrGraphicsPath);
begin
  DoRotateGPPath(TGdipGraphicsPath(APath).GPPath);
end;

function TGPBlockDrawer.GetCanvas: TDgrCanvas;
begin
  result := FGPCanvas;
end;

procedure TGPBlockDrawer.SetPaintEngine(const Value: TDgrPaintEngine);
begin
  if (Value <> nil) and (Value is TGdipPaintEngine) then
    FGPCanvas.FTempGraphics := TGdipPaintEngine(Value).FGPGraphics
  else
    FGPCanvas.FTempGraphics := nil;
end;

procedure TGPBlockDrawer.TranslateRectsPath(APath: TDgrGraphicsPath);
begin
  inherited;
  TGdipGraphicsPath(APath).GPPath.Transform(FGPCanvas.FTransMatrix);
end;

procedure TGPBlockDrawer.TransformPath(APath: TDgrGraphicsPath);
begin
  inherited TransformPath(APath);
end;

procedure TGPBlockDrawer.RotatePath(APath: TDgrGraphicsPath);
begin
  inherited RotatePath(APath);
end;

procedure TGPBlockDrawer.TransformPath(APath: TGPGraphicsPath);
begin
  // GDI+ backward compatibility
  APath.Transform(FGPCanvas.FTransMatrix); // TranslateRectsPath
  RotatePath(APath); // RotatePath
end;

procedure TGPBlockDrawer.RotatePath(APath: TGPGraphicsPath);
begin
  // GDI+ backward compatibility
  if Angle <> 0 then
    DoRotateGPPath(APath);
end;

procedure TGPBlockDrawer.SetGraphics(AGPGraphics: TGPGraphics);
begin
  FGPCanvas.FTempGraphics := AGPGraphics;
end;

{ TGdipImage }

constructor TGdipImage.Create;
begin
  FGPImage := nil;
end;

procedure TGdipImage.CreateGPImage;
begin
  FGPImage := TGPImage.Create;
end;

destructor TGdipImage.Destroy;
begin
  DestroyGPImage;
  inherited;
end;

procedure TGdipImage.DestroyGPImage;
begin
  if FGPImage <> nil then
  begin
    FGPImage.Free;
    FGPImage := nil;
  end;
end;

function TGdipImage.GetGPImage: TGPImage;
begin
  if FGPImage = nil then
    CreateGPImage;
  result := FGPImage;
end;

{ TGdipGraphicsPath }

function TGdipGraphicsPath.AddArc(x, y, width, height, startAngle, sweepAngle: number): integer;
begin
  result := Ord(GPPath.AddArc(x, y, width, height, startAngle, sweepAngle));
end;

function TGdipGraphicsPath.AddBezier(x1, y1, x2, y2, x3, y3, x4, y4: number): integer;
begin
  result := Ord(GPPath.AddBezier(x1, y1, x2, y2, x3, y3, x4, y4));
end;

function TGdipGraphicsPath.AddEllipse(x, y, width, height: number): integer;
begin
  result := Ord(GPPath.AddEllipse(x, y, width, height));
end;

function TGdipGraphicsPath.AddLine(x1, y1, x2, y2: number): integer;
begin
  result := Ord(GPPath.AddLine(x1, y1, x2, y2));
end;

function TGdipGraphicsPath.AddLines(points: TDotArray): integer;
var
  gpPoints: array of TGPPointF;
  count, i: integer;
begin
  count := Length(points);
  SetLength(gpPoints, count);
  for i := Low(points) to High(points) do
    gpPoints[i] := MakePoint(points[i].X, points[i].Y);

  result := Ord(GPPath.AddLines(PGPPointF(@gpPoints[0]), count));
end;

function TGdipGraphicsPath.AddPolygon(points: TDotArray): integer;
var
  gpPoints: array of TGPPointF;
  count, i: integer;
begin
  count := Length(points);
  SetLength(gpPoints, count);
  for i := Low(points) to High(points) do
    gpPoints[i] := MakePoint(points[i].X, points[i].Y);

  result := Ord(GPPath.AddPolygon(PGPPointF(@gpPoints[0]), count));
end;

function TGdipGraphicsPath.AddRectangle(rect: TSquare): integer;
begin
  result := Ord(GPPath.AddRectangle(RectGP(rect)));
end;

function TGdipGraphicsPath.AddRoundRect(X1, Y1, X2, Y2, X3, Y3: number): integer;
begin
  AddArc(X2 - X3, Y1, X3, Y3, 270, 90);
  AddArc(X2 - X3, Y2 - Y3, X3, Y3, 0, 90);
  AddArc(X1, Y2 - Y3, X3, Y3, 90, 90);
  AddArc(X1, Y1, X3, Y3, 180, 90);
  result := 0;
end;

function TGdipGraphicsPath.CloseFigure(AClosePath: boolean): integer;
begin
  result := Ord(GPPath.CloseFigure);
end;

function TGdipGraphicsPath.CreateRegion: TDgrRegion;
begin
  result := TGdipRegion.Create(Self);
end;

constructor TGdipGraphicsPath.Create;
begin
  FGPPath := nil;
end;

procedure TGdipGraphicsPath.CreateGPPath;
begin
  FGPPath := TGPGraphicsPath.Create;
end;

destructor TGdipGraphicsPath.Destroy;
begin
  DestroyGPPath;
  inherited;
end;

procedure TGdipGraphicsPath.DestroyGPPath;
begin
  if FGPPath <> nil then
  begin
    FGPPath.Free;
    FGPPath := nil;
  end;
end;

function TGdipGraphicsPath.GetGPPath: TGPGraphicsPath;
begin
  if FGPPath = nil then
    CreateGPPath;
  result := FGPPath;
end;

function TGdipGraphicsPath.GetPointCount: Integer;
begin
  result := GPPath.GetPointCount;
end;

function TGdipGraphicsPath.IsVisible(x, y: Integer): boolean;
begin
  result := GPPath.IsVisible(x, y);
end;

function TGdipGraphicsPath.Reset: integer;
begin
  result := Ord(GPPath.Reset);
end;

function TGdipGraphicsPath.SetFillMode(fillmode: TFillMode): integer;
const
  gpFillMode: array[Graphics.TFillMode] of DgrGdipApi.TFillMode =
    (FillModeAlternate, FillModeWinding);
begin
  result := Ord(GPPath.SetFillMode(gpFillMode[fillmode]));
end;

function TGdipGraphicsPath.StartFigure: integer;
begin
  result := Ord(GPPath.StartFigure);
end;

{ TGdipPaintEngine }

constructor TGdipPaintEngine.Create(ACanvas: TCanvas; ARect: TRect);
begin
  FGPGraphics := TGPGraphics.Create(ACanvas.Handle);
end;

destructor TGdipPaintEngine.Destroy;
begin
  FGPGraphics.Free;
  inherited;
end;

procedure TGdipPaintEngine.SetPageUnit(const Value: TDgrPageUnit);
begin
  inherited;
  case Value of
    dpuWorld:
      FGPGraphics.SetPageUnit(UnitWorld);
    dpuDisplay:
      FGPGraphics.SetPageUnit(UnitDisplay);
    dpuPixel:
      FGPGraphics.SetPageUnit(UnitPixel);
    dpuPoint:
      FGPGraphics.SetPageUnit(UnitPoint);
    dpuInch:
      FGPGraphics.SetPageUnit(UnitInch);
    dpuDocument:
      FGPGraphics.SetPageUnit(UnitDocument);
    dpuMillimeter:
      FGPGraphics.SetPageUnit(UnitMillimeter);
  end;
end;

procedure TGdipPaintEngine.SetSmoothMode(const Value: TDgrSmoothMode);
begin
  inherited;
  case Value of
    smAntiAlias:
      FGPGraphics.SetSmoothingMode(SmoothingModeAntiAlias);
    smInactive:
      FGPGraphics.SetSmoothingMode(SmoothingModeNone);
    smHighSpeed:
      FGPGraphics.SetSmoothingMode(SmoothingModeHighSpeed);
    smHighQuality:
      FGPGraphics.SetSmoothingMode(SmoothingModeHighQuality);
  end;
end;

procedure TGdipPaintEngine.SetTextRenderingMode(const Value: TDgrTextRenderingMode);
begin
  inherited;
  case Value of
    tmDefault:
      FGPGraphics.SetTextRenderingHint(TextRenderingHintSystemDefault);
    tmAntiAlias:
      FGPGraphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
    tmAntiAliasHint:
      FGPGraphics.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
    tmNormal:
      FGPGraphics.SetTextRenderingHint(TextRenderingHintSingleBitPerPixel);
    tmNormalHint:
      FGPGraphics.SetTextRenderingHint(TextRenderingHintSingleBitPerPixelGridFit);
    tmClearType:
      FGPGraphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
  end;
end;

procedure TGdipPaintEngine.FillRect(ARect: TRect; AColor: TColor);
var
  gpBrush: TGPBrush;
begin
  gpBrush := TGPSolidBrush.Create(ColorToARGB(AColor, 255));
  try
    FGPGraphics.FillRectangle(gpBrush, ARect.Left, ARect.Top, ARect.Right - ARect.Left, ARect.Bottom - ARect.Top);
  finally
    gpBrush.Free;
  end;
end;

function TGdipPaintEngine.ResetTransform: integer;
begin
  result := Ord(FGPGraphics.ResetTransform);
end;

function TGdipPaintEngine.RotateTransform(AAngle: number): integer;
begin
  result := Ord(FGPGraphics.RotateTransform(AAngle, MatrixOrderAppend));
end;

function TGdipPaintEngine.ScaleTransform(AX, AY: number): integer;
begin
  result := Ord(FGPGraphics.ScaleTransform(AX, AY, MatrixOrderAppend));
end;

function TGdipPaintEngine.TranslateTransform(AX, AY: number): integer;
begin
  result := Ord(FGPGraphics.TranslateTransform(AX, AY, MatrixOrderAppend));
end;

{ TGdipRegion }

constructor TGdipRegion.Create(APath: TDgrGraphicsPath);
begin
  FGPRegion := TGPRegion.Create(TGdipGraphicsPath(APath).GPPath);
end;

destructor TGdipRegion.Destroy;
begin
  FGPRegion.Free;
  inherited;
end;

function TGdipRegion.GetHRGN(ACanvas: TDgrCanvas): HRGN;
begin
  result := FGPRegion.GetHRGN(TGPCanvas(ACanvas).GPGraphics)
end;

function TGdipRegion.IsVisible(ARect: TSquare): boolean;
begin
  result := FGPRegion.IsVisible(RectGP(ARect));
end;

{$ENDIF}

end.

