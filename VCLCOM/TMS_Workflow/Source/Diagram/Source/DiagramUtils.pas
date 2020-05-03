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

unit DiagramUtils;

{$I diagram.inc}

interface

uses
  Windows,
  {$IFDEF DELPHI6_LVL}Types, {$ENDIF}
  Classes, Contnrs,
  Graphics;

type
  {compatibility}
  number = double;

  /// Summary:
  ///   TDot is a TPoint-like structure for double typed values.
  /// Description:
  ///   TDot record can hold X and Y double values. It is used in some helper procedures for coordinate
  ///   conversion and rotation.
  TDot = record

    /// Description:
    ///   X value of TDot structure.
    X: double;

    /// Description:
    ///   Y value of TDot structure.
    Y: double;
  end;

  /// Summary:
  ///   TSquare is a TRect-like structure for double typed values.
  /// Description:
  ///   TSquare record can hold Left, Top, Right and Bottom double values. It is used in some helper
  ///   procedures for coordinate conversion and rotation.
  TSquare = record
    case Integer of
      0: (Left, Top, Right, Bottom: double);
      1: (TopLeft, BottomRight: TDot);
  end;

  TPointArray = array of TPoint;
  TDotArray = array of TDot;

  {compatibility}
  TRectX = TSquare {$IFDEF DELPHI2005_LVL}; deprecated {$ENDIF};
  TPointX = TDot {$IFDEF DELPHI2005_LVL}; deprecated {$ENDIF};
  TPointXArray = TDotArray {$IFDEF DELPHI2005_LVL}; deprecated {$ENDIF};

  TLineOrientation  = (loPoint, loHorizontal, loVertical);
  TRotationType = (
  rtCurRectCenter, /// The rotation center is the center of rectangle specified by CurRect.
  rtRotationCenter /// The rotation center is specified by RotationCenter property.
  );
  TVertAlign = (vaTop, vaBottom, vaCenter);

  TSaveBlockDrawer = class;

  /// Summary:
  ///   TBlockDrawer class is a helper class from drawing blocks.
  /// Description:
  ///   Use TBlockDrawer class methods and properties to make it easy to draw blocks and convert coordinates.
  ///   In general, you set OriginalRect property to contain the rectangle where you want to paint to.
  ///   CurRect property must contain the destination rectangle. So, when using drawing methods,
  ///   pass coordinates like you were painting to original rect, and it will be paint on cur rect coordinates.
  TBlockDrawer = class
  private
    FRect: TSquare;
    FOrRect: TSquare;
    FAngle: double;
    FRadAngle: double;
    FCanvas: TCanvas;
    FSinAngle: double;
    FCosAngle: double;
    FRotationType: TRotationType;
    FRotationCenter: TDot;
    FStack: TObjectStack;
    procedure SetAngle(const Value: double);
    {Updates the rotation center value}
  public

    /// Summary:
    ///   Create class.
    /// Description:
    ///   Create class.
    constructor Create;
    destructor Destroy; override;

    {Draw functions}

    /// Summary:
    ///   Draws a rotated round rectangle.
    /// Description:
    ///   DrawRotRoundRect draws a round rectangle in canvas specified by Canvas property, rotated by the
    ///   angle specified by Angle property. The rotation center is specified by RotationType property.
    procedure DrawRotRoundRect(X1, Y1, X2, Y2, X3, Y3: number);

    /// Summary:
    ///   Draws a rotated rectangle.
    /// Description:
    ///   DrawRotRect draws a rectangle in canvas specified by Canvas property, rotated by the angle
    ///   specified by Angle property. The rotation center is specified by RotationType property.
    procedure DrawRotRect(X1, Y1, X2, Y2: number);

    /// Summary:
    ///   Draws a rotated polygon.
    /// Description:
    ///   DrawRotPoly draws a polygon in canvas specified by Canvas property, rotated by the angle
    ///   specified by Angle property. The rotation center is specified by RotationType property.
    procedure DrawRotPoly(P: TDotArray); overload;
    procedure DrawRotPoly(P: array of TDot); overload;
    procedure DrawRotEllipse(X1, Y1, X2, Y2: Integer);

    {automatic (scaled/transformed) draw functions}
    procedure AutoRotRect(X1, Y1, X2, Y2: number);
    procedure AutoEllipse(X1, Y1, X2, Y2: number);
    procedure AutoRoundRect(X1, Y1, X2, Y2, X3, Y3: number);

    /// Summary:
    ///   Performs a LineTo.
    /// Description:
    ///   AutoLineTo performs a LineTo method in the canvas specified by Canvas property,
    ///   doing automatic coordinate conversion from OriginalRect to CurRect.
    procedure AutoLineTo(X, Y: double);

    /// Summary:
    ///   Performs a MoveTo.
    /// Description:
    ///   AutoMoveTo performs a MoveTo method in the canvas specified by Canvas property,
    ///   doing automatic coordinate conversion from OriginalRect to CurRect.
    procedure AutoMoveTo(X, Y: double);

    /// Summary:
    ///   Rotate the points of a polygon.
    /// Description:
    ///   RotPoly receives the points of a polygon, and returns the rotated points of the polygon.
    ///   Points are rotated by the angle defined in Angle property. Rotation center is define by
    ///   RotationType property.
    function RotPoly(Pts: TDotArray): TDotArray; overload;
    //function RotPoly(P: array of TDot): TDotArray; overload;

    /// Summary:
    ///   Rotates a point in counter-clockwise direction.
    /// Description:
    ///   UnrotX rotates a point in counter-clockwise direction, by the angle specified by Angle property,
    ///   and rotation center specified by RotationType property.
    function UnrotX(AX, AY: double): TDot; overload;
    function UnrotX(AP: TDot): TDot; overload;

    /// Summary:
    ///   Rotates a point in clockwise direction.
    /// Description:
    ///   RotX rotates a point in clockwise direction, by the angle specified by Angle property,
    ///   and rotation center specified by RotationType property.
    function RotX(AX, AY: double): TDot; overload;
    function RotX(AP: TDot): TDot; overload;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.RotX
    function Rot(AP: TPoint): TPoint; overload;
    function Rot(AX, AY: double): TPoint; overload;

    /// Summary:
    ///   Moves a rectangle by rotation its center.
    /// Description:
    ///   RotByCenter moves a rectangle by rotating its center. Rotation angle is given by Angle property,
    ///   rotation center is given by RotationType property.
    function RotByCenter(R: TSquare): TSquare;
    {P Points keep ratio between original and current rects}
    function PPPoints(Pts: TDotArray): TDotArray;

    /// Summary:
    ///   Converts coordinates between OriginalRect and CurRect.
    /// Description:
    ///   Use PP, PX and PY to convert coordinates from OriginalRect to CurRect.
    ///   Coordinates are converted proportionally (in terms of % of original rect position).
    function PP(AP: TDot): TDot; overload;
    function PP(AX, AY: double): TDot; overload;
    function PPX(AX, AY: double): TDot; overload;
    function PPX(AP: TDot): TDot; overload;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.PP
    function PX(AX: double): integer; virtual;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.PP
    function PY(AY: double): integer; virtual;
    function PXS(AX: double): double;
    function PYS(AY: double): double;
    {Inverse of P_ functions}
    function UnPP(AP: TDot): TDot; overload;
    function UnPP(Ax, AY: double): TDot; overload;
    function UnPPX(Ax, AY: double): TDot; overload;
    function UnPPX(AP: TDot): TDot; overload;
    function UnPx(AX: double): integer;
    function UnPY(AY: double): integer;
    function UnPXS(AX: double): double;
    function UnPYS(AY: double): double;
    {R Points keep same bottom/right distance between original and current rects}

    /// Summary:
    ///   Converts coordinates between OriginalRect and CurRect.
    /// Description:
    ///   Use RP, RX and RY to convert coordinates from OriginalRect to CurRect. Coordinates are converted
    ///   anchored to right/bottom position of OriginalRect. For example, if original point is 10 pixels far
    ///   from right (or bottom) edge of original rect, the new point will be 10 pixels far from right
    ///   (or bottom) edge of currenct rect.
    function RP(AX, AY: double): TPoint;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.RP
    function RX(AX: double): integer;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.RP
    function RY(AY: double): integer;
    {L Points keep same top/left distance between original and current rects}

    /// Summary:
    ///   Converts coordinates between OriginalRect and CurRect.
    /// Description:
    ///   Use LP, LX and LY to convert coordinates from OriginalRect to CurRect.
    ///   Coordinates are converted anchored to left/top position of OriginalRect.
    ///   For example, if original point is 10 pixels far from left (or top) edge of original rect,
    ///   the new point will be 10 pixels far from left (or top) edge of currenct rect.
    function LP(AX, AY: double): TPoint;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.LP
    function LX(AX: double): integer;

    /// LinkedTo:
    ///   DiagramUtils.TBlockDrawer.LP
    function LY(AY: double): integer;

    {Drawer properties and state}
    procedure PushState;
    procedure PopState;
    procedure Assign(ASource: TBlockDrawer);

    // wrappers for Canvas methods (workaround for internal errors in Delphi 7)
    procedure CanvasPolygon(APoints: TPointArray);
    procedure CanvasPolyLine(APoints: TPointArray);

    /// Summary:
    ///   Specifies rotation angle.
    /// Description:
    ///   Angle property contains rotation angle used by rotation methods.
    ///   It is used together with RotationType property.
    property Angle: double read FAngle write SetAngle;

    /// Summary:
    ///   Specifies the rotation center.
    /// Description:
    ///   RotationType property specifies what point will be used as the
    ///   center of rotation when rotation methods are used.
    property RotationType: TRotationType read FRotationType write FRotationType;

    /// Summary:
    ///   Specifies custom rotation center.
    /// Description:
    ///   RotationCenter property contains the point of center of rotation when rotation methods are called.
    ///   RotationCenter is only used when RotationType property is set to rtRotationCenter.
    property RotationCenter: TDot read FRotationCenter write FRotationCenter;

    /// Summary:
    ///   Contains the original rect coordinates.
    /// Description:
    ///   OriginalRect contains the rectangle coordinates of original rectangle.
    ///   It is used in coordinate conversion methods as the rectangle where coordinates will be converted from.
    property OriginalRect: TSquare read FOrRect write FOrRect;

    /// Summary:
    ///   Contains the destination rect coordinates.
    /// Description:
    ///   CurRect contains the rectangle coordinates of destination rectangle.
    ///   It is used in coordinate conversion methods as the rectangle where coordinates will be converted to.
    property CurRect: TSquare read FRect write FRect;

    /// Summary:
    ///   Specifies the canvas to draw to.
    /// Description:
    ///   Set the Canvas property to specify the canvas where paint to.
    ///   Canvas property is only used by the methods that perform direct draw
    ///   (not coordinate conversions of rotation methods).
    property Canvas: TCanvas read FCanvas write FCanvas;
  end;

  TSaveBlockDrawer = class(TBlockDrawer);

  TBlockDrawerClass = class of TBlockDrawer;

function PointArray(P: array of TPoint): TPointArray;
function DotArray(P: array of TDot): TDotArray;
function PointXArray(P: array of TDot): TDotArray; {$IFDEF DELPHI6_LVL} deprecated; {$ENDIF}

{$IFNDEF DELPHI6_LVL}

/// Summary:
///   Returns the sign of number.
/// Description:
///   Sign returns -1 if number is negative, 1 if it is positive, 0 if it is zero.
function Sign(const AValue: integer): integer;
{$ENDIF}

procedure ClipRectangleRegion(DC: HDC; X1, Y1, X2, Y2: integer);

/// Summary:
///   Concatenate two array of points.
/// Description:
///   Use ConcatPoints to concatenate two array of points.
function ConcatPoints(P1, P2: TPointArray): TPointArray;
function ConcatPointsX(P1, P2: TDotArray): TDotArray;
function MakeDotArray(P: array of TDot): TDotArray;
function ToDotArray(Src: TPointArray): TDotArray;
function RoundDotArray(Src: TDotArray): TPointArray;

/// Summary:
///   Rotates a bitmap.
/// Description:
///   RotateBitmap rotates ASrcBmp by the angle specified by AAngle. ADestBmp holds the rotated bitmap.
///   ADestBmp is resized to contain the whole rotated source bitmap.
function RotateBitmap(ASrcBmp, ADestBmp: TBitmap; AAngle: double): TColor;

/// Summary:
///   Draws a transparent bitmap.
/// Description:
///   DrawTranspBitmap draws a transparent bitmap Bmp in Dest canvas, at the position specified
///   by destX and destY. Transparent color is specified by TransColor.
procedure DrawTranspBitmap(Dest : TCanvas; Bmp : TBitmap;
 destX, destY : Integer; TransColor : TColor);

/// Summary:
///   Returns an array of points that defines a round rectangle.
/// Description:
///   GetPolyRoundRect returns an array of points that can be used to draw a rounded rectangle.
///   The array of points can be used for rotating.
function GetPolyRoundRect(X1, Y1, X2, Y2, X3, Y3: number): TDotArray;

/// Summary:
///   Returns an array of points that defines a ellipse.
/// Description:
///   GetPolyEllipse returns an array of points that can be used to draw an ellipse.
///   The array of points can be used for rotating the ellipse.
function GetPolyEllipse(Left, Top, Right, Bottom: number;
  StartAngle: integer = 0; EndAngle: integer = 360; ClockWise: boolean = True): TDotArray;

/// Summary:
///   Returns a TDot record.
function Dot(P: TPoint): TDot; overload;
function Dot(X, Y: double): TDot; overload;
function PointX(P: TPoint): TDot; overload; {$IFDEF DELPHI6_LVL} deprecated; {$ENDIF}
function PointX(X, Y: double): TDot; overload; {$IFDEF DELPHI6_LVL} deprecated; {$ENDIF}

/// Summary:
///   Converts a TDot to a TPoint.
/// Description:
///   RoundPoint converts a TDot to a TPoint by rounding TDot coordinates.
function RoundPoint(APoint: TDot): TPoint;

/// Summary:
///   Moves a TRect by a delta.
/// Description:
///   MoveRectByPoint moves a TRect specified by ARect. The move delta is specified by ADelta.
function MoveRectByPoint(ARect: TSquare; ADelta: TDot): TSquare;
// MT returns the Point as in the rectangle
function PointRelativeToRect(ARect: TRect; APoint: TPoint): TPoint;
// MT restricts the given point to the given rectangle
function RestrictPointToRect(ARect: TRect; APoint: TPoint; AMargin: Integer = 1): TPoint;
// MT returns the bottom left point of a TRect
function RectBottomLeft(ARect: TRect): TPoint;
// MT returns the top right point of a TRect
function RectTopRight(ARect: TRect): TPoint;

procedure CalcLineParameters(PAX, PAY, PBX, PBY: double;
  var Slope, Intercept: double;
  var LineOrientation: TLineOrientation);

function DummyPointX: TDot;

/// Summary:
///   Returns a dummy point.
/// Description:
///   DummyPoint is used internally. A point can be checked if it is dummy by using IsDummyPoint function.
function DummyPoint: TPoint;

/// Summary:
///   Check is a point is dummy.
/// Description:
///   Used internally. IsDummyPoint check if the point is a dummy point (create by DummyPoint function).
function IsDummyPoint(APoint: TDot): boolean;

/// Summary:
///   Check if a point is null.
/// Description:
///   IsNullPoint returns true if both point coordinates are zero.
function IsNullPoint(APoint: TPoint): boolean; overload;
function IsNullPoint(APoint: TDot): boolean; overload;

/// Summary:
///   Returns a TRect record.
/// Description:
///   RectEx works almost the same as Rect function.
///   Different is that RectEx automatically put lower coordinates in Left and Top fields,
///   and higher coordinates in Right and Bottom fields.
function RectEx(ALeft, ATop, ARight, ABottom: number): TSquare; overload;
function RectEx(P1, P2: TDot): TSquare; overload;

/// Summary:
///   Check if a TRect is null.
/// Description:
///   IsNullRect returns true if all rect coordinates are zero.
function IsNullRect(ARect: TRect): boolean; overload;
function IsNullRect(ARect: TSquare): boolean; overload;

/// Summary:
///   Check if two rects are equal.
/// Description:
///   IsSameRect returns true if coordinates of both rects are equal.
function IsSameRect(ARect1, ARect2: TRect): boolean; overload;
function IsSameRect(ARect1, ARect2: TSquare): boolean; overload;

function RotateRect(ARect: TRect): TRect;

/// Summary:
///   Check if two rects touch.
/// Description:
///   RectsTouch returns true if rectangles defined by the two rects touch.
function RectsTouch(ACompRect, ARect: TSquare): boolean;

/// Summary:
///   Check if a point is close to another.
/// Description:
///   AroundPoint returns true if APoint is close to ATargetPoint.
///   Definition of close is given by a rectangle around ATargetPoint, of size APointOff.
function AroundPoint(APoint, ATargetPoint: TPoint; APointOff: integer = 5):
  boolean; overload;
function AroundPoint(APoint, ATargetPoint: TDot; APointOff: integer = 5):
  boolean; overload;

/// Summary:
///   Check if a point is close to a horizontal line.
/// Description:
///   AroundHorzLine returns true if APoint is close to a horizontal line defined by Y, X1 and X2.
///   The "close" is defined by APointOff.
function AroundHorzLine(APoint: TPoint; Y, X1, X2: double;
  APointOff: integer = 5): boolean;

/// Summary:
///   Check if a point is close to a vertical line.
/// Description:
///   AroundVertLine returns true if APoint is close to a vertical line defined by X, Y1 and Y2.
///   The "close" is defined by APointOff.
function AroundVertLine(APoint: TPoint; X, Y1, Y2: double;
  APointOff: integer = 5): boolean;

/// Summary:
///   Check if a point is near a line.
/// Description:
///   NearLine returns true if point specified by Target is near the line specified by Point1 and Point2.
///   The point must be at the distance specified by AOff.
function NearLine(const Target: TPoint; P1X, P1Y, P2X, P2Y: double; AOff: integer = 5): boolean;

/// Summary:
///   Check if a point is inside (or around) a TRect.
/// Description:
///   PtInRectEx works almost the same as PtInRect.
///   The difference is that PtInRectEx returns true even if the point is outside the rect,
///   but at the maximum distance specified by AOff.
function PtInRectEx(ARect: TSquare; P: TDot; AOff: integer = 5): boolean;

/// Summary:
///   Multiplies a TPoint.
/// Description:
///   MulPoint multiplies the coordinates of a TPoint by the scalar AValue.
function MulPoint(P1: TPoint; AValue: double): TPoint; overload;
function MulPoint(P1: TDot; AValue: double): TDot; overload;

/// Summary:
///   Subtracts a TPoint from another TPoint.
/// Description:
///   Subtracts a TPoint P2 from another TPoint P1.
function SubPoint(P1, P2: TPoint): TPoint;

/// Description:
///   Adds two points.
function AddPoint(P1, P2: TPoint): TPoint;

/// LinkedTo:
///   DiagramUtils.SubPoint
function SubPointX(P1, P2: TDot): TDot;

/// LinkedTo:
///   DiagramUtils.AddPoint
function AddPointX(P1, P2: TDot): TDot;

/// Summary:
///   Returns the center of a TRect.

/// Summary:
///   Rotates a TRect.
/// Description:
///   RotateRect rotates a TRect by 90 degrees. Rotation center is the center of TRect.
function RectCenter(R: TRect): TPoint;
function MoveRect(R: TRect; DX, DY: integer): TRect; overload;
function MoveRect(R: TSquare; DX, DY: number): TSquare; overload;
function RotatePoint(P: TPoint; Angle: double): TPoint;
function DistanceFromLine(L1, L2, P: TDot): double;
function PointDistance(P1, P2: TDot): double; overload;
function PointDistance(p1x, p1y, p2x, p2y: double): double; overload;
function MeanPoint(P1, P2: TDot): TDot;
function ArePointsEqual(P1, P2: TPoint): boolean; overload;
function ArePointsEqual(P1, P2: TDot): boolean; overload;
function AbsPoint(P: TPoint): TPoint;
function Diode(X: double): double;
function LineIntersection(A1, A2, B1, B2: TDot; var P: TDot): boolean; overload;
function LineIntersection(A1, A2, B1, B2: TPoint; var P: TPoint): boolean; overload;
function LineIntersectionSeg(A1, A2, B1, B2: TDot; var P: TDot): boolean; overload;
function LineIntersectionSeg(A1, A2, B1, B2: TPoint; var P: TPoint): boolean; overload;
procedure LineEqIntersection(a1, b1, c1, a2, b2, c2: double; var x, y: double);
function CircumArc(pt0x, pt0y, pt1x, pt1y, pt2x, pt2y: double): TDotArray;
function Colinear(x1, y1, x2, y2, x3, y3: double): boolean;
procedure Mediatriz(x1, y1, x2, y2: double; var a, b, c: double );
function VectorAngle(x, y, xc, yc: double): double;
procedure MakeVector(X, Y, D, A: double; var NX, NY: double);
{RotatePointByLines
 Considering two lines:
   Line A, defined by LA1 and LA2 points
   Line B, defined by LB1 and LB2 points
 Given a point P relative to line A, then RotatePointByLines finds a new position
 for point P, now relative to line B. The angle between P and a point of line A
 will be the same angle as the new position of P and a point of line B.}
function RotatePointByLines(P, LA1, LA2, LB1, LB2: TDot): TDot;
function ParabolicArc(pt0x, pt0y, pt1x, pt1y, pt2x, pt2y: double): TDotArray;
procedure RotateVector(var x1,y1: double; x0,y0, ang: double );
procedure LinearSys(a,b,c,d,e,f,g,h,i,j,k,l: double; var x,y,z: double );
function Bezier(pt0x, pt0y, pp0x, pp0y, pp1x, pp1y, pt1x, pt1y, k: double): TDotArray;


function Square(ALeft, ATop, ARight, ABottom: double): TSquare; overload;
function Square(ARect: TRect): TSquare; overload;
function RectX(ALeft, ATop, ARight, ABottom: double): TSquare; overload; {$IFDEF DELPHI6_LVL} deprecated; {$ENDIF}
function RectX(ARect: TRect): TSquare; overload; {$IFDEF DELPHI6_LVL} deprecated; {$ENDIF}
function MoveRectXByPoint(ARect: TSquare; ADelta: TPoint): TSquare;
function ToRect(ASquare: TSquare): TRect;
function KeepRectRatio(NewRect, OldRect: TSquare): TSquare;
procedure CalcPerpendicularPoints(var P1, P2: TDot; _From, _To: TDot; ASize: TDot);
{CalcDistPoint returns a point which is perpendicular to the line specified by P1 and P2.
 The distance between the point and the line is specified by Dist, and that distance is between
 the new point and the point specified by MP}
function CalcDistPoint(P1, P2, MP: TDot; Dist: double): TDot;


implementation
uses Math;

const
  PITimes2 = 2 * PI;

{CalcDistPoint returns a point which is perpendicular to the line specified by P1 and P2.
 The distance between the point and the line is specified by Dist, and that distance is between
 the new point and the point specified by MP}
function CalcDistPoint(P1, P2, MP: TDot; Dist: double): TDot;
var
  Delta: TDot;
  Hipot: double;
  SinAngle, CosAngle: double;
begin
  if ArePointsEqual(P1, P2) then
  begin
    result := P1;
    Exit;
  end;
  Hipot := PointDistance(P1, P2);
  SinAngle := (P2.Y - P1.Y) / Hipot;
  CosAngle := (P2.X - P1.X) / Hipot;
  Delta.X := SinAngle * Dist;
  Delta.Y := -CosAngle * Dist;
  result := AddPointX(MP, Delta);
end;

procedure CalcPerpendicularPoints(var P1, P2: TDot; _From, _To: TDot; ASize: TDot);
var
  P1X, P1Y, P2X, P2Y: double;
  D: double;
  PPX, PPY: double;
  TX, TY: double;
begin
  PPX := _To.X - _From.X;
  PPY := _To.Y - _From.Y;
  D := Sqrt(PPX * PPX + PPY * PPY);
  if D <> 0 then
  begin
    TX := PPX * (D - ASize.Y) / D;
    TY := PPY * (D - ASize.Y) / D;
    P1X := -PPY * (ASize.X / 2) / D;
    P1Y := PPX * (ASize.X / 2) / D;
    P2X := -P1X;
    P2Y := -P1Y;
    P1.X := P1X + TX + _From.X;
    P1.Y := P1Y + TY + _From.Y;
    P2.X := P2X + TX + _From.X;
    P2.Y := P2Y + TY + _From.Y;
  end else
  begin
    P1 := _To;
    P2 := _From;
  end;
end;

function KeepRectRatio(NewRect, OldRect: TSquare): TSquare;
var
  w, h: number;
  nw, nh: number;
begin
  w := oldRect.right - oldrect.left;
  h := oldRect.bottom - oldrect.top;
  nw := newRect.right - newrect.left;
  nh := newRect.bottom - newrect.top;
  if (nh > nw) then
  begin
    nh := nw * h / w;
    if NewRect.Bottom = OldRect.Bottom then
      NewRect.Top := NewRect.Bottom - nh
    else
      NewRect.Bottom := NewRect.Top + nh;
  end
  else
  begin
    nw := nh * w / h;
    if NewRect.Right = OldRect.Right then
      NewRect.Left := NewRect.Right - nw
    else
      NewRect.Right := NewRect.Left + nw;
  end;
  result := NewRect;
end;

function Square(ALeft, ATop, ARight, ABottom: double): TSquare;
begin
  with result do
  begin
    Left := ALeft;
    Top := ATop;
    Right := ARight;
    Bottom := ABottom;
  end;
end;

function Square(ARect: TRect): TSquare;
begin
  result := Square(ARect.Left, ARect.Top, ARect.Right, ARect.Bottom);
end;

function RectX(ALeft, ATop, ARight, ABottom: double): TSquare;
begin
  result := Square(ALeft, ATop, ARight, ABottom);
end;

function RectX(ARect: TRect): TSquare;
begin
  result := Square(ARect);
end;

function ToRect(ASquare: TSquare): TRect;
begin
  result.Left := Round(ASquare.Left);
  result.Top := Round(ASquare.Top);
  result.Right := Round(ASquare.Right);
  result.Bottom := Round(ASquare.Bottom);
end;

function MoveRectXByPoint(ARect: TSquare; ADelta: TPoint): TSquare;
begin
  result := Square(ARect.Left + ADelta.X, ARect.Top + ADelta.Y,
    ARect.Right + ADelta.X, ARect.Bottom + ADelta.Y);
end;

type
  pRGBArray = ^TRGBArray;
  TRGBArray = array[0..32768 - 1] of TRGBTriple;

function RotateBitmap(ASrcBmp, ADestBmp: TBitmap; AAngle: double): TColor;
var
  cosTheta: double;
  i: integer;
  iOriginal: integer;
  iPrime: integer;
  j: integer;
  jOriginal: integer;
  jPrime: integer;
  RowOriginal: pRGBArray;
  RowRotated: pRGBArray;
  sinTheta: double;
  OldPixelFormat: TPixelFormat;
  NewCX, NewCY: integer;
  OldCX, OldCY: integer;
  TranspColor: TRGBTriple;
begin
  OldPixelFormat := ASrcBmp.PixelFormat;
  ASrcBmp.PixelFormat := pf24bit;
  sinTheta := Sin(-AAngle * pi / 180);
  cosTheta := Cos(-AAngle * pi / 180);
  ADestBmp.Width  := abs(round(ASrcBmp.Height * sinTheta)) + abs(round(ASrcBmp.Width * cosTheta));
  ADestBmp.Height := abs(round(ASrcBmp.Width * sinTheta)) + abs(round(ASrcBmp.Height * cosTheta));
  ADestBmp.PixelFormat := pf24bit;
  if ASrcBmp.Transparent then
  begin
    TranspColor.rgbtBlue := (ASrcBmp.TransparentColor and $FF0000) shr 16;
    TranspColor.rgbtGreen := (ASrcBmp.TransparentColor and $00FF00) shr 8;
    TranspColor.rgbtRed := (ASrcBmp.TransparentColor and $0000FF);
  end else
  begin
    TranspColor.rgbtBlue := 255;
    TranspColor.rgbtRed := 0;
    TranspColor.rgbtGreen := 0;
  end;
  OldCX := ASrcBmp.Width div 2;
  OldCY := ASrcBmp.Height div 2;
  NewCX := ADestBmp.Width div 2;
  NewCY := ADestBmp.Height div 2;
  for j := ADestBmp.Height - 1 downto 0 do
  begin
    RowRotated  := ADestBmp.Scanline[j];
    jPrime := (j - NewCY);
    for i := ADestBmp.Width - 1 downto 0 do
    begin
      iPrime := (i - NewCX);
      iOriginal := Round(iPrime * CosTheta - jPrime * sinTheta) + OldCX;
      jOriginal := Round(iPrime * sinTheta + jPrime * cosTheta) + OldCY;
      if (iOriginal >= 0) and (iOriginal <= ASrcBmp.Width - 1) and
        (jOriginal >= 0) and (jOriginal <= ASrcBmp.Height - 1) then
      begin
        RowOriginal := ASrcBmp.Scanline[jOriginal];
        RowRotated[i]  := RowOriginal[iOriginal]
      end else
      begin
        RowRotated[i] := TranspColor;
      end;
    end;
  end;
  if OldPixelFormat <> pfCustom then
    ASrcBmp.PixelFormat := OldPixelFormat;
  result := TranspColor.rgbtRed + 
    TranspColor.rgbtGreen shl 8 + TranspColor.rgbtBlue shl 16; 
end;

procedure DrawTranspBitmap(Dest : TCanvas; Bmp : TBitmap;
 destX, destY : Integer; TransColor : TColor);
var
  srcDC, saveDC, maskDC, invDC, resultDC, hResultBmp, hSaveBmp, hMaskBmp,
  hInvBmp, hSrcPrevBmp, hSavePrevBmp, hDestPrevBmp, hMaskPrevBmp,
  hInvPrevBmp, HDC, BH, BW, hB : Integer;
  OrigColor : TColor;
begin
  HDC := Dest.Handle;
  BH := BMP.Height; BW := BMP.Width; hB := BMP.Handle;
  srcDC := CreateCompatibleDC(hDC);
  saveDC := CreateCompatibleDC(hDC);
  maskDC := CreateCompatibleDC(hDC);
  invDC := CreateCompatibleDC(hDC);
  resultDC := CreateCompatibleDC(hDC);
  {$WARNINGS OFF}
  hMaskBmp := CreateBitmap(BW, BH, 1, 1, PChar(0));
  hInvBmp := CreateBitmap(BW, BH, 1, 1, PChar(0));
  {$WARNINGS ON}
  hResultBmp := CreateCompatibleBitmap(HDC, BW, BH);
  hSaveBmp := CreateCompatibleBitmap(HDC, BW, BH);
  hSrcPrevBmp := SelectObject(srcDC, hB);
  hSavePrevBmp := SelectObject(saveDC, hSaveBmp);
  hMaskPrevBmp := SelectObject(maskDC, hMaskBmp);
  hInvPrevBmp := SelectObject(invDC, hInvBmp);
  hDestPrevBmp := SelectObject(resultDC, hResultBmp);
  BitBlt(saveDC, 0, 0, BW, BH, srcDC, 0, 0, SRCCOPY);
  OrigColor := SetBkColor(srcDC, TransColor);
  BitBlt(maskDC, 0, 0, BW, BH, srcDC, 0, 0, SRCCOPY);
  SetBkColor(srcDC, OrigColor);
  BitBlt(invDC, 0, 0, BW, BH, maskDC, 0, 0, NOTSRCCOPY);
  BitBlt(resultDC, 0, 0, BW, BH, HDC, destX, destY, SRCCOPY);
  BitBlt(resultDC, 0, 0, BW, BH, maskDC, 0, 0, SRCAND);
  BitBlt(srcDC, 0, 0, BW, BH, invDC, 0, 0, SRCAND);
  BitBlt(resultDC, 0, 0, BW, BH,srcDC, 0, 0, SRCPAINT);
  BitBlt(HDC, destX, destY, BW, BH, resultDC, 0, 0, SRCCOPY);
  BitBlt(srcDC, 0, 0, BW, BH, saveDC,0, 0, SRCCOPY);
  SelectObject(srcDC, hSrcPrevBmp);
  SelectObject(saveDC, hSavePrevBmp);
  SelectObject(resultDC, hDestPrevBmp);
  SelectObject(maskDC, hMaskPrevBmp);
  SelectObject(invDC, hInvPrevBmp);
  DeleteObject(hSaveBmp);
  DeleteObject(hMaskBmp);
  DeleteObject(hInvBmp);
  DeleteObject(hResultBmp);
  DeleteDC(srcDC);
  DeleteDC(saveDC);
  DeleteDC(invDC);
  DeleteDC(maskDC);
  DeleteDC(resultDC);
end;

function GetPolyEllipse(Left, Top, Right, Bottom: number;
  StartAngle: integer = 0; EndAngle: integer = 360; ClockWise: boolean = true): TDotArray;
var
  A, B, Max: Double;
  dTheta: Double;
  N: Double;
  I: Integer;
  U, V: number;

  procedure FindUV(Theta: double);
  var
    X, Y: Double;
  begin
    X := A * Cos(Theta);
    Y := B * Sin(Theta);
    U := (X + (Right + Left) / 2.0);
    V := (Y + (Top + Bottom) / 2.0)
  end;

var
  I1, I2: integer;
begin
  {The "+ 1" below in right and bottom points is for Windows compatible -
   summing 1 to right and bottom edges will draw an ellipse in the exact
   way Windows does}
  A := Abs((Right - Left) + 1) / 2.0;
  B := Abs((Bottom - Top) + 1) / 2.0;
  if (A <> 0) and (B <> 0) then
  begin
    Max := A;
    if Abs(B) > Abs(A) then
      Max := B;
    dTheta := 1 / Max;
    N := 2 * Pi / dTheta;
    dTheta := 2 * Pi / Round(N);
    I1 := round(StartAngle * N / 360);
    I2 := round(EndAngle * N / 360);
    SetLength(result, I2 - I1 + 2);
    if ClockWise then
    begin
      FindUV(I1 * dTheta);
      result[0] := Dot(U, V);
      for I := I1 to I2 do
      begin
        FindUV(I * dTheta);
        result[I - I1 + 1] := Dot(U, V);
      end;
    end
    else
    begin
      FindUV(I2 * dTheta);
      result[0] := Dot(U, V);
      for I := I2 downto I1 do
      begin
        FindUV(I * dTheta);
        result[I2 - I + 1] := Dot(U, V);
      end;
    end;
  end else
  begin
    SetLength(result, 2);
    result[0] := Dot(Left, Top);
    result[1] := Dot(Right, Bottom);
  end;
end;

function GetPolyRoundRect(X1, Y1, X2, Y2, X3, Y3: number): TDotArray;
var
  P1, P2, P3, P4: TDotArray;
  c: integer;
begin
  {Windows compatibility}
  P1 := GetPolyEllipse(X1, Y1, X1 + X3 - 1, Y1 + Y3 - 1, 181, 269);
  P2 := GetPolyEllipse(X2, Y1, X2 - X3 - 1, Y1 + Y3 - 1, 269, 359);
  P3 := GetPolyEllipse(X2, Y2, X2 - X3 - 1, Y2 - Y3 - 1, 1, 89);
  P4 := GetPolyEllipse(X1, Y2, X1 + X3 - 1, Y2 - Y3 - 1, 91, 179);
  SetLength(result, Length(P1) + Length(P2) + Length(P3) + Length(P4) + 1);
  for c := 0 to Length(P1) - 1 do
    result[c] := P1[c];
  for c := 0 to Length(P2) - 1 do
    result[c + Length(P1)] := P2[c];
  for c := 0 to Length(P3) - 1 do
    result[c + Length(P1) + Length(P2)] := P3[c];
  for c := 0 to Length(P4) - 1 do
    result[c + Length(P1) + Length(P2) + Length(P3)] := P4[c];
  result[Length(result) - 1] := result[0];
end;

function RectEx(P1, P2: TDot): TSquare;
begin
  result := RectEx(P1.X, P1.Y, P2.X, P2.Y);
end;

function RectEx(ALeft, ATop, ARight, ABottom: number): TSquare; overload;
begin
  result := Square(Min(ALeft, ARight), Min(ATop, ABottom),
    Max(ALeft, ARight), Max(ATop, ABottom));
end;

function IsNullRect(ARect: TRect): boolean;
begin
  result := (ARect.Left = 0) and (ARect.Top = 0) and (ARect.Right = 0) and
    (ARect.Bottom = 0);
end;

function IsNullRect(ARect: TSquare): boolean;
begin
  result := (ARect.Left = 0) and (ARect.Top = 0) and (ARect.Right = 0) and (ARect.Bottom = 0);
end;

function RectsTouch(ACompRect, ARect: TSquare): boolean;
begin
  result := not ((ARect.Bottom < ACompRect.Top) or (ARect.Right < ACompRect.Left)
    or
    (ARect.Left > ACompRect.Right) or (ARect.Top > ACompRect.Bottom));
end;

function RotateRect(ARect: TRect): TRect;
var
  CX: integer;
  CY: integer;
begin
  CX := (ARect.Left + ARect.Right) div 2;
  CY := (ARect.Top + ARect.Bottom) div 2;
  result.Left := CX + (ARect.Top - CY);
  result.Top := CY + (ARect.Left - CX);
  result.Right := CX + (ARect.Bottom - CY);
  result.Bottom := CY + (ARect.Right - CX);
end;

function IsSameRect(ARect1, ARect2: TRect): boolean;
begin
  result := (ARect1.Left = ARect2.Left) and (ARect1.Top = ARect2.Top) and
    (ARect1.Right = ARect2.Right) and (ARect1.Bottom = ARect2.Bottom);
end;

function IsSameRect(ARect1, ARect2: TSquare): boolean;
begin
  result := (ARect1.Left = ARect2.Left) and (ARect1.Top = ARect2.Top) and
    (ARect1.Right = ARect2.Right) and (ARect1.Bottom = ARect2.Bottom);
end;

function AroundVertLine(APoint: TPoint; X, Y1, Y2: double; APointOff: integer =
  5): boolean;
begin
  if Y2 > Y1 then
    result :=
      (APoint.X >= X - APointOff) and
      (APoint.X <= X + APointOff) and
      (APoint.Y >= Y1 - APointOff) and
      (APoint.Y <= Y2 + APointOff)
  else
    result :=
      (APoint.X >= X - APointOff) and
      (APoint.X <= X + APointOff) and
      (APoint.Y >= Y2 - APointOff) and
      (APoint.Y <= Y1 + APointOff);
end;

function AroundHorzLine(APoint: TPoint; Y, X1, X2: double; APointOff: integer =
  5): boolean;
begin
  if X2 > X1 then
    result :=
      (APoint.Y >= Y - APointOff) and
      (APoint.Y <= Y + APointOff) and
      (APoint.X >= X1 - APointOff) and
      (APoint.X <= X2 + APointOff)
  else
    result :=
      (APoint.Y >= Y - APointOff) and
      (APoint.Y <= Y + APointOff) and
      (APoint.X >= X2 - APointOff) and
      (APoint.X <= X1 + APointOff);
end;

function AroundPoint(APoint, ATargetPoint: TPoint; APointOff: integer = 5):
  boolean;
begin
  result := 
    (APoint.X >= ATargetPoint.X - APointOff) and
    (APoint.Y >= ATargetPoint.Y - APointOff) and
    (APoint.X <= ATargetPoint.X + APointOff) and
    (APoint.Y <= ATargetPoint.Y + APointOff);
end;

function AroundPoint(APoint, ATargetPoint: TDot; APointOff: integer = 5):
  boolean;
begin
  result :=
    (APoint.X >= ATargetPoint.X - APointOff) and
    (APoint.Y >= ATargetPoint.Y - APointOff) and
    (APoint.X <= ATargetPoint.X + APointOff) and
    (APoint.Y <= ATargetPoint.Y + APointOff);
end;

(*function SubtractPoints(const PointA, PointB:  TPoint):  TPoint;
begin
  with result do
  begin
    X := PointA.X - PointB.X;
    Y := PointA.Y - PointB.Y
  end;
end;*)

{$IFNDEF DELPHI6_LVL}
function Sign(const AValue: integer): integer;
begin
  result := 0;
  if AValue < 0 then
    result := -1
  else if AValue > 0 then
    result := 1;
end;
{$ENDIF}

function PointArray(P: array of TPoint): TPointArray;
var
  c: Integer;
begin
  SetLength(result, Length(P));
  for c := 0 to Length(P) - 1 do
    result[c] := P[c];
end;

function DotArray(P: array of TDot): TDotArray;
var
  c: Integer;
begin
  SetLength(result, Length(P));
  for c := 0 to Length(P) - 1 do
    result[c] := P[c];
end;

function PointXArray(P: array of TDot): TDotArray;
begin
  result := DotArray(P);
end;

function ConcatPoints(P1, P2: TPointArray): TPointArray;
var
  c: integer;
begin
  SetLength(result, Length(P1) + Length(P2));
  for c := 0 to Length(P1) - 1 do
    result[c] := P1[c];
  for c := 0 to Length(P2) - 1 do
    result[c + Length(P1)] := P2[c];
end;

function ConcatPointsX(P1, P2: TDotArray): TDotArray;
var
  c: integer;
begin
  SetLength(result, Length(P1) + Length(P2));
  for c := 0 to Length(P1) - 1 do
    result[c] := P1[c];
  for c := 0 to Length(P2) - 1 do
    result[c + Length(P1)] := P2[c];
end;

function RoundDotArray(Src: TDotArray): TPointArray;
var
  c: integer;
begin
  SetLength(result, Length(Src));
  for c := 0 to Length(Src) - 1 do
  begin
    result[c].X := round(Src[c].X);
    result[c].Y := round(Src[c].Y);
  end;
end;

function MakeDotArray(P: array of TDot): TDotArray;
var
  i: integer;
begin
  SetLength(result, Length(P));
  for i := Low(P) to High(P) do
    result[i] := P[i];
end;

function ToDotArray(Src: TPointArray): TDotArray;
var
  c: integer;
begin
  SetLength(result, Length(Src));
  for c := 0 to Length(Src) - 1 do
  begin
    result[c].X := Src[c].X;
    result[c].Y := Src[c].Y;
  end;
end;

procedure ClipRectangleRegion(DC: HDC; X1, Y1, X2, Y2: integer);
var
  R: HRGN;
begin
  R := CreateRectRgn(X1, Y1, X2, Y2);
  try
    SelectClipRgn(DC, R);
  finally
    DeleteObject(R);
  end;
end;

procedure CalcLineParameters(PAX, PAY, PBX, PBY: double;
  var Slope, Intercept: double;
  var LineOrientation: TLineOrientation);
var
  Delta: TDot;
begin
  Delta.X := PBX - PAX;
  Delta.Y := PBY - PAY;
  if (Delta.X = 0) and (Delta.Y = 0) then
  begin
    // This special CASE should never happen if iMinPixels > 0
    LineOrientation := loPoint;
    Slope := 0.0;
    Intercept := 0.0
  end
  else
  begin
    if Abs(Delta.X) >= Abs(Delta.Y) then
    begin
      // The line is more horizontal than vertical.  Determine values FOR
      // equation:  Y = slope*X + intercept
      LineOrientation := loHorizontal;
      try
        Slope := Delta.Y / Delta.X {conventional slope in geometry}
      except
        Slope := 0.0
      end;
      Intercept := PAY - PAX * Slope
    end else
    begin
      // The line is more vertical than horizontal.  Determine values FOR
      // equation:  X = slope*Y + intercept
      LineOrientation := loVertical;
      try
        Slope := Delta.X / Delta.Y {reciprocal of conventional slope}
      except
        Slope := 0.0
      end;
      Intercept := PAX - PAY * Slope;
    end;
  end;
end;

function NearLine(const Target: TPoint; P1X, P1Y, P2X, P2Y: double; AOff: integer = 5): boolean;
var
  Intercept: double;
  LineOrientation: TLineOrientation;
  maxX: double;
  maxY: double;
  minX: double;
  minY: double;
  Slope: double;
  xCalculated: integer;
  yCalculated: integer;
begin
  result := false;
  // If an Endpoint is not selected, was part of line selected?
  CalcLineParameters(P1X, P1Y, P2X, P2Y, Slope, Intercept, LineOrientation);
  case LineOrientation of
    loHorizontal:
      begin
        minX := MinValue([P1X, P2X]);
        maxX := MaxValue([P1X, P2X]);
        // first check if selection within horizontal range of line
        if (Target.X >= minX) and (Target.X <= maxX) then
        begin
          // Since X is within range of line, now see if Y value is close
          // enough to the calculated Y value FOR the line to be selected.
          yCalculated := Round(Slope * Target.X + Intercept);
          if Abs(yCalculated - Target.Y) <= AOff then
            result := True
        end;
      end;
    loVertical:
      begin
        minY := MinValue([P1Y, P2Y]);
        maxY := MaxValue([P1Y, P2Y]);
        // first check if selection within vertical range of line
        if (Target.Y >= minY) and (Target.Y <= maxY) then
        begin
          // Since Y is within range of line, now see if X value is close
          // enough to the calculated X value FOR the line to be selected.
          xCalculated := Round(Slope * Target.Y + Intercept);
          if Abs(xCalculated - Target.X) <= AOff then
            result := True
        end;
      end;
    loPoint:
      // Do nothing -- should not occur
  end;
end;

function DummyPointX: TDot;
begin
  result := Dot(100000, 100000);
end;

function DummyPoint: TPoint;
begin
  result := Point(100000, 100000);
end;

function IsNullPoint(APoint: TPoint): boolean;
begin
  result := (APoint.X = 0) and (APoint.Y = 0);
end;

function IsNullPoint(APoint: TDot): boolean;
begin
  result := (APoint.X = 0) and (APoint.Y = 0);
end;

function IsDummyPoint(APoint: TDot): boolean;
begin
  result := (APoint.X = DummyPoint.X) and (APoint.Y = DummyPoint.Y);
end;

function MoveRectByPoint(ARect: TSquare; ADelta: TDot): TSquare;
begin
  result := Square(ARect.Left + ADelta.X, ARect.Top + ADelta.Y,
    ARect.Right + ADelta.X, ARect.Bottom + ADelta.Y);
end;

function PointRelativeToRect(ARect: TRect; APoint: TPoint): TPoint;
begin
  if not PtInRect(ARect, APoint)
  then Result := APoint
  else Result := Point(APoint.X - ARect.Left, APoint.Y - ARect.Top);
end;

function RestrictPointToRect(ARect: TRect; APoint: TPoint; AMargin: Integer = 1): TPoint;
begin
  Result := APoint;
  if Result.X <= ARect.Left
  then Result.X := ARect.Left + AMargin;
  if Result.X >= ARect.Right
  then Result.X := ARect.Right - AMargin;

  if Result.Y <= ARect.Top
  then Result.Y := ARect.Top + AMargin;
  if Result.Y >= ARect.Bottom
  then Result.Y := ARect.Bottom - AMargin;
end;

function RectBottomLeft(ARect: TRect): TPoint;
begin
  Result := Point(ARect.Left, ARect.Bottom);
end;

function RectTopRight(ARect: TRect): TPoint;
begin
  Result := Point(ARect.Right, ARect.Top);
end;


function PtInRectEx(ARect: TSquare; P: TDot; AOff: integer = 5): boolean;
begin
  Result := (P.X >= (ARect.Left - AOff))
    and (P.X < (ARect.Right + AOff))
    and (P.Y >= (ARect.Top - AOff))
    and (P.Y < (ARect.Bottom + AOff));
end;

function SubPoint(P1, P2: TPoint): TPoint;
begin
  result := Point(P1.X - P2.X, P1.Y - P2.Y);
end;

function AddPoint(P1, P2: TPoint): TPoint;
begin
  result := Point(P1.X + P2.X, P1.Y + P2.Y);
end;

function SubPointX(P1, P2: TDot): TDot;
begin
  result := Dot(P1.X - P2.X, P1.Y - P2.Y);
end;

function AddPointX(P1, P2: TDot): TDot;
begin
  result := Dot(P1.X + P2.X, P1.Y + P2.Y);
end;

function MulPoint(P1: TPoint; AValue: double): TPoint;
begin
  result := RoundPoint(MulPoint(Dot(P1.X, P1.Y), AValue));
end;

function MulPoint(P1: TDot; AValue: double): TDot;
begin
  result := Dot(P1.X * AValue, P1.Y * AValue);
end;

function RotatePoint(P: TPoint; Angle: double): TPoint;
begin
end;

function RectCenter(R: TRect): TPoint;
begin
  result := Point((R.Left + R.Right) div 2, (R.Top + R.Bottom) div 2);
end;

function RoundPoint(APoint: TDot): TPoint;
begin
  result := Point(round(APoint.X), round(APoint.Y));
end;

function Dot(X, Y: double): TDot;
begin
  result.X := X;
  result.Y := Y;
end;

function Dot(P: TPoint): TDot;
begin
  result := Dot(P.X, P.Y);
end;

function PointX(X, Y: double): TDot;
begin
  result := Dot(X, Y);
end;

function PointX(P: TPoint): TDot;
begin
  result := Dot(P);
end;

function MoveRect(R: TRect; DX, DY: integer): TRect;
begin
  result.Left := R.Left + DX;
  result.Top := R.Top + DY;
  result.Right := R.Right + DX;
  result.Bottom := R.Bottom + DY;
end;

function MoveRect(R: TSquare; DX, DY: number): TSquare;
begin
  result.Left := R.Left + DX;
  result.Top := R.Top + DY;
  result.Right := R.Right + DX;
  result.Bottom := R.Bottom + DY;
end;

function DistanceFromLine(L1, L2, P: TDot): double;
var
  d: double;
begin
  d := sqrt((L1.X - L2.X) * (L1.X - L2.X) + (L1.Y - L2.Y) * (L1.Y - L2.Y));
  if d <> 0 then
    result := ((L1.X - L2.X) * (P.Y - L2.Y) - (L1.Y - L2.Y) * (P.X - L2.X)) / d
  else
    result := 0;
end;

function PointDistance(P1, P2: TDot): double;
begin
  result := PointDistance(P1.X, P1.Y, P2.X, P2.Y);
end;

function PointDistance(p1x, p1y, p2x, p2y: double): double; 
begin
  result := sqrt((P2X - P1X) * (P2X - P1X) + (P2Y - P1Y) * (P2Y - P1Y));
end;

function MeanPoint(P1, P2: TDot): TDot;
begin
  result := Dot((P1.X + P2.X) / 2, (P1.Y + P2.Y) / 2);
end;

function ArePointsEqual(P1, P2: TPoint): boolean; 
begin
  result := (P1.X = P2.X) and (P1.Y = P2.Y);
end;

function ArePointsEqual(P1, P2: TDot): boolean;
begin
  result := (P1.X = P2.X) and (P1.Y = P2.Y);
end;

function AbsPoint(P: TPoint): TPoint;
begin
  result := Point(Abs(P.X), Abs(P.Y));
end;

function Diode(X: double): double;
begin
  if X > 0 then
    result := X
  else
    result := 0;
end;

function LineIntersection(A1, A2, B1, B2: TPoint; var P: TPoint): boolean;
var
  P2: TDot;
begin
  P2 := Dot(P);
  result := LineIntersection(Dot(A1), Dot(A2), Dot(B1), Dot(B2), P2);
  P := RoundPoint(P2);
end;

function LineIntersection(A1, A2, B1, B2: TDot; var P: TDot): boolean;

  function VectorDir2d (A, B: TDot): TDot;
  begin
    result.x := B.x - A.x;
    result.y := B.y - A.y;
  end;

  function VectorAddScaled2d(A, B: TDot; k: double): TDot;
  begin
    result.x := A.x + k * B.x;
    result.y := A.y + k * B.y;
  end;

var
  g, h, i: TDot;
  det, k: double;
  //l: double;
begin
  g := VectorDir2d(A1, A2);
  h := VectorDir2d(B1, B2);
  Det := H.X * G.Y - H.Y * G.X;
  result := abs(Det) > 1E-6;
  if result then
  begin
    i := VectorDir2d(A1, B1);
    k := (h.x * i.y - h.y * i.x) / Det;
    //l := (g.x * i.y - g.y * i.x) / Det;
    P := VectorAddScaled2d(A1, g, k); {S = A + k * g}
  end;
  {Uncomment the code below if you want to check intersection of line *segments*}
  //result := result and (k >= 0) and (k <= 1) and (l >= 0) and (l <= 1);
end;

function LineIntersectionSeg(A1, A2, B1, B2: TPoint; var P: TPoint): boolean;
var
  P2: TDot;
begin
  P2 := Dot(P);
  result := LineIntersectionSeg(Dot(A1), Dot(A2), Dot(B1), Dot(B2), P2);
  P := RoundPoint(P2);
end;

function LineIntersectionSeg(A1, A2, B1, B2: TDot; var P: TDot): boolean;

  function VectorDir2d (A, B: TDot): TDot;
  begin
    result.x := B.x - A.x;
    result.y := B.y - A.y;
  end;

  function VectorAddScaled2d(A, B: TDot; k: double): TDot;
  begin
    result.x := A.x + k * B.x;
    result.y := A.y + k * B.y;
  end;

var
  g, h, i: TDot;
  det, k: double;
  l: double;
begin
  g := VectorDir2d(A1, A2);
  h := VectorDir2d(B1, B2);
  Det := H.X * G.Y - H.Y * G.X;
  result := abs(Det) > 1E-6;
  if result then
  begin
    i := VectorDir2d(A1, B1);
    k := (h.x * i.y - h.y * i.x) / Det;
    l := (g.x * i.y - g.y * i.x) / Det;
    P := VectorAddScaled2d(A1, g, k); {S = A + k * g}
    result := result and (k >= 0) and (k <= 1) and (l >= 0) and (l <= 1);
  end;
end;

procedure LineEqIntersection(a1, b1, c1, a2, b2, c2: double; var x, y: double);
var
  D: double;
begin
   D := A1 * B2 - B1 * A2;
   if D <> 0 then
   begin
     X := (B1 * C2 - B2 * C1) / D;
     Y := (A2 * C1 - A1 * C2) / D;
   end else
   begin
     X := 10000000;
     Y := 10000000;
   end;
end;

function CircumArc(pt0x, pt0y, pt1x, pt1y, pt2x, pt2y: double): TDotArray;
var A1, A2, B1, B2, C1, C2 : double;
    XCentro, YCentro, Raio : double;
    ang1, ang2, ang3       : double;
    ai, af, ang, dang      : double;
    p                      : integer;
    n: integer;
begin
   SetLength(result, 0);
   if not Colinear( pt0x, pt0y, pt1x, pt1y, pt2x, pt2y ) then
   begin
      { determina o centro e o raio da circunferência que passa pelos três pontos dados }
      Mediatriz( pt0x, pt0y, pt1x, pt1y, A1, B1, C1);
      Mediatriz( pt0x, pt0y, pt2x, pt2y, A2, B2, C2);
      LineEqIntersection( A1, B1, C1, A2, B2, C2, XCentro, YCentro );
      Raio := PointDistance( XCentro, YCentro, pt0x, pt0y );
      if Raio = 0 then Exit;

      {Decides the path in way that arc is drawn from point 1 to 2, passing through point 3}
      ang1 := VectorAngle( pt0x, pt0y, XCentro, YCentro );
      ang2 := VectorAngle( pt1x, pt1y, XCentro, YCentro );
      ang3 := VectorAngle( pt2x, pt2y, XCentro, YCentro );

      { Below are the possible angle orders and the respective path }
      { a1,a2,a3 => a2..a1+2pi }
      { a1,a3,a2 => a1..a2 }
      { a2,a1,a3 => a1..a2+2pi }
      { a2,a3,a1 => a2..a1 }
      { a3,a1,a2 => a2..a1+2pi }
      { a3,a2,a1 => a1..a2+2pi }

      case byte(ang1 > ang2) shl 2 + byte(ang1 > ang3) shl 1 + byte(ang2 > ang3) of
        {000} 0 : begin af := ang2; ai := ang1 + PITimes2; end;
        {001} 1 : begin ai := ang1; af := ang2; end;
        {100} 4 : begin ai := ang1; af := ang2 + PITimes2; end;
        {110} 6 : begin af := ang2; ai := ang1; end;
        {011} 3 : begin af := ang2; ai := ang1 + PITimes2; end;
        {111} 7 : begin ai := ang1; af := ang2 + PITimes2; end;
        else      begin ai := 0; af := PITimes2; end;
      end;

      { calculate arc segments }
      n := round(abs((af - ai) * Raio));
      SetLength( result, n );
      ang := ai;
      dang := (af - ai) / (n - 1);
      for p := 0 to n - 1 do
      begin
        result[p].X := XCentro + Raio * Cos( ang );
        result[p].Y := YCentro - Raio * Sin( ang );
        ang := ang + dang;
      end;
   end else
   begin
     SetLength(result, 3);
     result[0] := Dot(pt0x, pt0y);
     result[1] := Dot(pt2x, pt2y);
     result[2] := Dot(pt1x, pt1y);
   end;
end;

function Colinear(x1, y1, x2, y2, x3, y3: double): boolean;
var
  Area: double;
begin
   Area := Abs(X1 * (Y2 - Y3) + X2 * (Y3 - Y1) + X3 * (Y1 - Y2)) / 2;
   if Abs(Area) < 1e-10 then
     Colinear := True
   else
     Colinear := False;
end;

procedure Mediatriz(x1, y1, x2, y2: double; var a, b, c: double );
begin
   A := x1 - x2;
   B := y1 - y2;
   C := ((y1 + y2) / 2) * (y2 - y1) - ((x1 + x2) / 2) * (x1 - x2);
end;

function VectorAngle(x, y, xc, yc: double): double;
begin
  {Check if angles are orthogonal}
  if x = xc then
    if y > yc then
      result := 3 * PI / 2
    else
      result := PI/2
  else
    if y = yc then
      if x > xc then
        result := 0
      else
        result := PI
    else
    begin
      result := ArcTan((yc - y) / (x - xc) ); // Y coordinate is not cartesian

      {Use Cosin to check if angle is in quadrants 2 or 3}
      if (x<xc) then
        result := PI + result
      else
        if result<0 then
          result := result + PITimes2;
    end;
end;

procedure MakeVector(X, Y, D, A: double; var NX, NY: double);
begin
  NX := X + D * Cos(A);
  NY := Y - D * Sin(A);
end;

function RotatePointByLines(P, LA1, LA2, LB1, LB2: TDot): TDot;
var
  AOld, ANew: double;
  DOld, DNew: double;
  AHnd, DHnd: double;
  Nx, Ny: double;
  R: double;
begin
  Aold := VectorAngle(LA1.X, LA1.Y, LA2.X, LA2.Y);
  Dold := PointDistance(LA1.X, LA1.Y, LA2.X, LA2.Y);
  DNew := PointDistance(LB1.X, LB1.Y, LB2.X, LB2.Y);
  ANew := VectorAngle(LB1.X, LB1.Y, LB2.X, LB2.Y);
  DHnd := PointDistance(P.X, P.Y, LA2.X, LA2.Y);
  AHnd := VectorAngle(P.X, P.Y, LA2.X, LA2.Y);
  if DOld = 0 then
    R := 1
  else
    R := DNew / DOld;
  MakeVector(LB2.X, LB2.Y, DHnd * R, AHnd + ANew - AOld, Nx, Ny);
  result := Dot(Nx, Ny);
end;

function ParabolicArc(pt0x, pt0y, pt1x, pt1y, pt2x, pt2y: double): TDotArray;
var
  ang: double;
  a, b, c: double;
  x, y, dx: double;
  xx, yy: double;
  p: integer;
  n: integer;
begin
  n := 100;
  if not Colinear(pt0x, pt0y, pt1x, pt1y, pt2x, pt2y) then
  begin
    SetLength(result, n);

    {Rotate coordinantes of points 2 and 3 with the same angle,
     in a way the point 2 stays at the right of point 3 with same vertical coordinate}
    ang := VectorAngle(pt1x, pt1y, pt0x, pt0y);
    RotateVector(pt1x, pt1y, pt0x, pt0y, -ang);
    RotateVector(pt2x, pt2y, pt0x, pt0y, -ang);

    {Find coeficients a,b,c of a second-order polynomial which fits the three points of parabole}
    LinearSys(Sqr(pt0x), pt0x, 1, pt0y,
              Sqr(pt1x), pt1x, 1, pt1y,
              Sqr(pt2x), pt2x, 1, pt2y,
              a, b, c );

    {Calculate parabole segments}
    x := pt0x;
    dx := (pt1x - pt0x) / (n - 1);
    for p := 0 to n-1 do
    begin
      y := ((a * x) + b) * x + c;
      xx := x;
      yy := y;
      RotateVector(xx, yy, pt0x, pt0y, ang);
      result[p].X := xx;
      result[p].Y := yy;
      x := x + dx;
    end;
  end else
  begin
    SetLength(result, 3);
    result[0] := Dot(pt0x, pt0y);
    result[1] := Dot(pt2x, pt2y);
    result[2] := Dot(pt1x, pt1y);
  end;
end;

procedure RotateVector(var x1,y1: double; x0,y0, ang: double );
var x, y: double;
    sin_ang, cos_ang : double;
begin
  sin_ang := Sin(ang);
  cos_ang := Cos(ang);
  x := x0 + cos_ang*(x1-x0) - sin_ang*(y0-y1);
  y := y0 - sin_ang*(x1-x0) - cos_ang*(y0-y1);
  x1 := x;
  y1 := y;
end;

procedure LinearSys(a,b,c,d,e,f,g,h,i,j,k,l: double; var x,y,z: double);
var
  delta : double;
begin
   delta := (a*f*k + e*j*c + i*b*g - i*f*c - a*j*g - e*b*k);
   X := (d*f*k + h*j*c + l*b*g - l*f*c - d*j*g - h*b*k) / delta;
   Y := (a*h*k + e*l*c + i*d*g - i*h*c - a*l*g - e*d*k) / delta;
   Z := (a*f*l + e*j*d + i*b*h - i*f*d - a*j*h - e*b*l) / delta;
end;

function Bezier(pt0x, pt0y, pp0x, pp0y, pp1x, pp1y, pt1x, pt1y, k: double): TDotArray;
var t,dt: double;
    a,b,c,d,e,f,g,h : double;
    tg0x, tg0y, tg1x, tg1y: double;
    p: integer;
    n: integer;
begin
   tg0x := pp0x - pt0x;
   tg0y := pp0y - pt0y;
   tg1x := pp1x - pt1x;
   tg1y := pp1y - pt1y;
   {n := round(
     PointDistance(pt0x, pt0y, tg0x, tg0y) +
     PointDistance(tg0x, tg0y, pt1x, pt1y) +
     PointDistance(pt1x, pt1y, tg1x, tg1y)
     ) div 10;}
   n := round(
     PointDistance(pt0x, pt0y, pp0x, pp0y) +
     PointDistance(pp0x, pp0y, pt1x, pt1y) +
     PointDistance(pt1x, pt1y, pp1x, pp1y)
     ) div 5;
  SetLength(result, n);
  if n > 1 then
  begin

    { Calculate the cubcic spline which will handle horizontal coordinates variation }
    a := -k * tg1x + k*tg0x + 2 * (pt0x - pt1x);
    b := 3 * (pt1x - pt0x) + k * tg1x - 2 * k * tg0x;
    c := k * tg0x;
    d := pt0x;

    { Calculate the cubcic spline which will handle vertical coordinates variation }
    e := -k * tg1y + k * tg0y + 2 * (pt0y - pt1y);
    f := 3 * (pt1y - pt0y) + k * tg1y - 2 * k * tg0y;
    g := k * tg0y;
    h := pt0y;

    {t is an independent variable which increments for 0 to 1 do determine the relative
     position at the end of curve}
    t := 0;

    {dt is the increment step of t which corresponds to the number of segments used to build the curve}
    dt := 1 / (n-1);

    {Calcule bezier curve segments}
    for p := 0 to n - 1 do
    begin
      {Horizontal and vertical coordinates calculation based of cubic which depends on t}
      result[p].X := a*t*t*t + b*t*t + c*t + d;
      result[p].Y := e*t*t*t + f*t*t + g*t + h;

      {increment the length variable t by step dt}
      t := t + dt;
    end;
  end;
end;

{ TBlockDrawer }

function TBlockDrawer.LP(AX, AY: double): TPoint;
begin
  result := Point(LX(AX), LY(AY));
end;

function TBlockDrawer.LX(AX: double): integer;
begin
  result := round(FRect.Left + (AX - FOrRect.Left));
end;

function TBlockDrawer.LY(AY: double): integer;
begin
  result := round(FRect.Top + (AY - FOrRect.Top));
end;

function TBlockDrawer.PPPoints(Pts: TDotArray): TDotArray;
var
  c: integer;
begin
  SetLength(result, Length(Pts));
  for c := 0 to Length(Pts) - 1 do
    result[c] := PP(Pts[c].X, Pts[c].Y);
end;

function TBlockDrawer.PP(AP: TDot): TDot;
begin
  result := PP(AP.X, AP.Y);
end;


function TBlockDrawer.PP(AX, AY: double): TDot;
begin
  result := Dot(PXS(AX), PYS(AY));
end;

function TBlockDrawer.PPX(AX, AY: double): TDot;
begin
  result := Dot(PXS(AX), PYS(AY));
end;

function TBlockDrawer.PPX(AP: TDot): TDot;
begin
  result := PPX(AP.X, AP.Y);
end;

function TBlockDrawer.PXS(AX: double): double;
begin
  if FOrRect.Right = FOrRect.Left then
    result := FRect.Left
  else
    result := (AX - FOrRect.Left) / (FOrRect.Right - FOrRect.Left) * (FRect.Right - FRect.Left) + FRect.Left;
end;

function TBlockDrawer.PYS(AY: double): double;
begin
  if FOrRect.Bottom = FOrRect.Top then
    result := FRect.Top
  else
    result := round(AY - FOrRect.Top) / (FOrRect.Bottom - FOrRect.Top) * (FRect.Bottom - FRect.Top) + FRect.Top;
end;

function TBlockDrawer.UnPP(AP: TDot): TDot;
begin
  result := UnPP(AP.X, AP.Y);
end;

function TBlockDrawer.UnPP(AX, AY: double): TDot;
begin
  result := Dot(UnPXS(AX), UnPYS(AY));
end;

function TBlockDrawer.UnPPX(AX, AY: double): TDot;
begin
  result := Dot(UnPXS(AX), UnPYS(AY));
end;

function TBlockDrawer.UnPPX(AP: TDot): TDot;
begin
  result := UnPPX(AP.X, AP.Y);
end;

function TBlockDrawer.UnPX(AX: double): integer;
begin
  result := round(UnPXS(AX));
end;

function TBlockDrawer.UnPY(AY: double): integer;
begin
  result := round(UnPYS(AY));
end;

function TBlockDrawer.UnPXS(AX: double): double;
begin
  if FRect.Right = FRect.Left then
    result := FOrRect.Left
  else
    result := ((AX - FRect.Left) / (FRect.Right - FRect.Left) * (FOrRect.Right - FOrRect.Left)) + FOrRect.Left;
end;

function TBlockDrawer.UnPYS(AY: double): double;
begin
  if FRect.Bottom = FRect.Top then
    result := FOrRect.Top
  else
    result := ((AY - FRect.Top) / (FRect.Bottom - FRect.Top) * (FOrRect.Bottom - FOrRect.Top)) + FOrRect.Top;
end;

function TBlockDrawer.RP(AX, AY: double): TPoint;
begin
  result := Point(RX(AX), RY(AY));
end;

function TBlockDrawer.RX(AX: double): integer;
begin
  result := round(FRect.Right - (FOrRect.Right - AX));
end;

function TBlockDrawer.RY(AY: double): integer;
begin                              
  result := round(FRect.Bottom - (FOrRect.Bottom - AY));
end;

function TBlockDrawer.Rot(AP: TPoint): TPoint;
begin
  result := Rot(AP.X, AP.Y);
end;

function TBlockDrawer.Rot(AX, AY: double): TPoint;
begin
  result := RoundPoint(RotX(AX, AY));
end;

function TBlockDrawer.RotX(AP: TDot): TDot;
begin
  result := RotX(AP.X, AP.Y);
end;

function TBlockDrawer.RotX(AX, AY: double): TDot;
var CX, CY: double;
begin
  {Optimization}
  if Angle = 0 then
    result := Dot(AX, AY)
  else
  begin
    Case RotationType of
      rtCurRectCenter:
        begin
          CX := (FRect.Left + FRect.Right) / 2;
          CY := (FRect.Top + FRect.Bottom) / 2;
        end;
    else {rtRotationCenter}
      CX := RotationCenter.X;
      CY := RotationCenter.Y;
    end;
    result.X := CX + FCosAngle*(AX - CX) - FSinAngle*(AY - CY);
    result.Y := CY + FSinAngle*(AX - CX) + FCosAngle*(AY - CY);
  end;
end;

function TBlockDrawer.UnrotX(AP: TDot): TDot;
begin
  result := UnrotX(AP.X, AP.Y);
end;

function TBlockDrawer.UnrotX(AX, AY: double): TDot;
begin
  Angle := -Angle;
  result := RotX(AX, AY);
  Angle := -Angle;
end;

procedure TBlockDrawer.SetAngle(const Value: double);
begin
  FAngle := Value;
  FRadAngle := FAngle*pi/180;
  FSinAngle := Sin(FRadAngle);
  FCosAngle := Cos(FRadAngle);
end;

procedure TBlockDrawer.DrawRotRect(X1, Y1, X2, Y2: number);
begin
  if Canvas <> nil then
  begin
    if Angle = 0 then
      Canvas.Rectangle(Round(X1), Round(Y1), Round(X2 + 1), Round(Y2 + 1))
    else
      Canvas.Polygon([Rot(X1, Y1), Rot(X2, Y1),
        Rot(X2, Y2), Rot(X1, Y2), Rot(X1, Y1)]);
  end;
end;

procedure TBlockDrawer.DrawRotPoly(P: TDotArray);
begin
  if Canvas <> nil then
    if Angle = 0 then
      Canvas.Polygon(RoundDotArray(P))
    else
      Canvas.Polygon(RoundDotArray(RotPoly(P)));
end;

procedure TBlockDrawer.DrawRotPoly(P: array of TDot);
var
  Pts: TDotArray;
  c: integer;
begin
  SetLength(Pts, Length(P));
  for c := 0 to Length(P) - 1 do
    Pts[c] := P[c];
  DrawRotPoly(Pts);
end;

function TBlockDrawer.RotPoly(Pts: TDotArray): TDotArray;
var
  c: integer;
begin
  SetLength(result, Length(Pts));
  for c := 0 to Length(Pts) - 1 do
    result[c] := RotX(Pts[c]);
end;

{function TBlockDrawer.RotPoly(P: array of TDot): TDotArray;
var
  c: integer;
begin
  SetLength(result, Length(P));
  for c := 0 to Length(P) - 1 do
    result[c] := RotX(P[c]);
end;}

procedure TBlockDrawer.DrawRotRoundRect(X1, Y1, X2, Y2, X3, Y3: number);
begin
  if Canvas <> nil then
  begin
    if Angle = 0 then
      Canvas.RoundRect(round(X1), round(Y1), round(X2 + 1), round(Y2 + 1), round(X3), round(Y3))
    else
      Canvas.Polygon(RoundDotArray(RotPoly(GetPolyRoundRect(X1, Y1, X2, Y2, X3, Y3))));
  end;
end;

procedure TBlockDrawer.AutoLineTo(X, Y: double);
var
  P: TPoint;
begin
  if Canvas <> nil then
  begin
    P := RoundPoint(PP(X, Y));
    Canvas.LineTo(P.X, P.Y);
  end;
end;

procedure TBlockDrawer.AutoMoveTo(X, Y: double);
var
  P: TPoint;
begin
  if Canvas <> nil then
  begin
    P := RoundPoint(RotX(PP(X, Y)));
    Canvas.MoveTo(P.X, P.Y);
  end;
end;

constructor TBlockDrawer.Create;
begin
  FStack := TObjectStack.Create;
  Angle := 0;
  RotationType := rtCurRectCenter;
  RotationCenter := Dot(0, 0);
  OriginalRect := Square(0, 0, 100, 100);
  CurRect := OriginalRect;
end;

function TBlockDrawer.RotByCenter(R: TSquare): TSquare;
var
  C: TDot;
  Delta: TDot;
  P1, P2: TDot;
begin
  C := Dot((R.Left + R.Right) / 2, (R.Top + R.Bottom) / 2);
  Delta := SubPointX(RotX(C), C);
  P1 := AddPointX(R.TopLeft, Delta);
  P2 := AddPointX(R.BottomRight, Delta);
  result := Square(P1.X, P1.Y, P2.X, P2.Y);
end;

destructor TBlockDrawer.Destroy;
begin
  while FStack.Count > 0 do
    FStack.Pop.Free;
  FStack.Free;
  inherited;
end;

procedure TBlockDrawer.DrawRotEllipse(X1, Y1, X2, Y2: Integer);
begin
  if Canvas <> nil then
  begin
    if Angle = 0 then
      Canvas.Ellipse(X1, Y1, X2 + 1, Y2 + 1)
    else
      Canvas.Polygon(RoundDotArray(RotPoly(GetPolyEllipse(X1, Y1, X2, Y2))));
  end;
end;

procedure TBlockDrawer.AutoEllipse(X1, Y1, X2, Y2: number);
begin
  DrawRotEllipse(PX(X1), PY(Y1), PX(X2), PY(Y2));
end;

procedure TBlockDrawer.AutoRoundRect(X1, Y1, X2, Y2, X3, Y3: number);
begin
  DrawRotRoundRect(PX(X1), PY(Y1), PX(X2), PY(Y2),
    round(X3 * (PY(X2) - PY(X1)) / (X2 - X1)),
    round(Y3 * (PY(Y2) - PY(Y1)) / (Y2 - Y1))
    );
end;

procedure TBlockDrawer.AutoRotRect(X1, Y1, X2, Y2: number);
begin
  DrawRotRect(PXS(X1), PYS(Y1), PXS(X2), PYS(Y2));
end;

procedure TBlockDrawer.Assign(ASource: TBlockDrawer);
begin
  {copy properties}
  Angle := ASource.Angle;
  RotationType := ASource.RotationType;
  RotationCenter := ASource.RotationCenter;
  OriginalRect := ASource.OriginalRect;
  CurRect := ASource.CurRect;
  Canvas := ASource.Canvas;
end;

procedure TBlockDrawer.PushState;
var
  ADrawer: TBlockDrawer;
begin
  ADrawer := TBlockDrawer.Create;
  ADrawer.Assign(Self);
  FStack.Push(ADrawer);
end;

procedure TBlockDrawer.PopState;
var
  ADrawer: TBlockDrawer;
begin
  ADrawer := TBlockDrawer(FStack.Pop);
  Self.Assign(ADrawer);
  ADrawer.Free;
end;

function TBlockDrawer.PX(AX: double): integer;
begin
  result := Round(PXS(AX));
end;

function TBlockDrawer.PY(AY: double): integer;
begin
  result := Round(PYS(AY));
end;

procedure TBlockDrawer.CanvasPolyLine(APoints: TPointArray);
begin
  if Canvas <> nil then
    Canvas.PolyLine(APoints);
end;

procedure TBlockDrawer.CanvasPolygon(APoints: TPointArray);
begin
  if Canvas <> nil then
    Canvas.Polygon(APoints);
end;

end.

