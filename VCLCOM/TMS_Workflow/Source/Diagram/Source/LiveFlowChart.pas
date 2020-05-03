{***************************************************************************}
{ Diagram Studio                                                            }
{ for Delphi & C++Builder                                                   }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright © 2003-2011                                          }
{            Email : info@tmssoftware.com                                   }
{            Web : http://www.tmssoftware.com                               }
{                                                                           }
{ LiveChart component - thanks to Davide Nardella                           }
{                                                                           }
{ The source code is given as is. The author is not responsible             }
{ for any possible damage done due to the use of this code.                 }
{ The components can be freely used in any application. The complete        }
{ source code remains property of the author and may not be distributed,    }
{ published, given or sold in any form as such. No parts of the source      }
{ code can be included in any other component or application without        }
{ written authorization of the author.                                      }
{***************************************************************************}

unit LiveFlowChart;

{$I DIAGRAM.INC}

interface

Uses
  SysUtils, Windows, Classes, Messages, Controls, Graphics, atDiagram,
  DiagramUtils, LiveDiagram, DgrClasses;

type
  TActionShape = (asBox, asAlternate, asData, asDocument, asInput, asSubRoutine);

  TLiveActionBlock = class(TCustomLiveBlock)
  private
    FActionShape: TActionShape;
    procedure AdjustLinkpoints;
    procedure SetFActionShape(const Value: TActionShape);
  protected
    procedure UpdateLinkPoints; override;
    function BlockPolygon: TDotArray; override;
    procedure DrawShape(AInfo: TDiagramDrawInfo; ABlockInfo: TDiagramDrawBlockInfo); override;
    procedure GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
    procedure GetTranslatedBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
  public
    constructor Create(AOwner : TComponent); override;
  published
    property ActionShape : TActionShape read FActionShape write SetFActionShape;
    property OnExecute;
    property OnExecuteEx;
  end;

  TDecisionShape = (dsBottomRight,dsRightBottom,dsLeftRight,dsRightLeft,
                    dsBottomLeft,dsLeftBottom);

  TLiveDecisionBlock = class(TCustomLiveBlock)
  private
    FNextTrue  : TCustomLiveBlock;
    FNextFalse : TCustomLiveBlock;
    FDecision: TDecisionShape;
    procedure SetDecision(const Value: TDecisionShape);
    procedure AdjustLinkPoints;
    procedure AdjustSigns;
  protected
    function BlockPolygon: TDotArray; override;
    function GetNext: TCustomLiveBlock; override;
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer;
      Direction : TLinkDirection) : boolean; override;
    procedure UpdateLinkPoints; override;
    procedure GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
  public
    constructor Create(AOwner : TComponent); override;
    function Link : boolean ; override;
    procedure ExecuteEx(Var ExecInfo: TExecuteNodeInfo); override;
  published
    property DecisionShape : TDecisionShape read FDecision write SetDecision;
    property OnExecute;
    property OnExecuteEx;
  end;

  TCaseList = class(TList)
  private
    NumberList : TList;
    FElse : TCustomLiveBlock;
  public
    constructor Create;
    function Add(aBlock : TCustomLiveBlock; aNumber : integer) : integer;
    function BlockOf(Number : integer) : TCustomLiveBlock;
    procedure AddElse(aBlock : TCustomLiveBlock);
    procedure Clear; override;
    destructor Destroy; override;
  end;

  TCaseShape = (csBottomRight,csBottomLeft);

  TLiveCaseBlock = class(TCustomLiveBlock)
  private
    FCaseShape: TCaseShape;
    FCaseList : TCaseList;
    FNextElse : TCustomLiveBlock;
    procedure AdjustLinkPoints;
    procedure AdjustSigns;
    procedure SetCaseShape(const Value: TCaseShape);
  protected
    function BlockPolygon: TDotArray; override;
    function GetNext: TCustomLiveBlock; override;
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer;
      Direction : TLinkDirection) : boolean; override;
    procedure DoExecute(Var Error, Decision : integer); override;
    procedure UpdateLinkPoints; override;
    procedure GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
  public
    constructor Create(AOwner : TComponent); override;
    destructor Destroy; override;
    function Link : boolean ; override;
  published
    property CaseShape : TCaseShape read FCaseShape write SetCaseShape;
    property OnExecute;
    property OnExecuteEx;
  end;

  TCustomTerminalBlock = class(TCustomLiveBlock)
  private
  protected
    function BlockPolygon: TDotArray; override;
    procedure GetTranslatedBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
  end;

  TLiveStartBlock = class(TCustomTerminalBlock)
  protected
    procedure UpdateLinkPoints; override;
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer;
      Direction : TLinkDirection) : boolean; override;
    function GetNext: TCustomLiveBlock; override;
  public
    constructor Create(AOwner : TComponent); override;
  published
    property OnExecute;
    property OnExecuteEx;
  end;

  TLiveEndBlock = class(TCustomTerminalBlock)
  protected
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer;
      Direction : TLinkDirection) : boolean; override;
    function GetNext: TCustomLiveBlock; override;
    procedure DoExecute(Var Error, Decision : integer); override;
  public
    constructor Create(AOwner : TComponent); override;
    function Link : boolean ; override;
  published
    property OnExecute;
    property OnExecuteEx;
  end;

  TLiveErrorHandler = class(TCustomLiveBlock)
  private
  protected
    function BlockPolygon: TDotArray; override;
    procedure UpdateLinkPoints;override;
    procedure DrawShape(AInfo: TDiagramDrawInfo; ABlockInfo: TDiagramDrawBlockInfo); override;
    function GetNext: TCustomLiveBlock; override;
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer; Direction : TLinkDirection) : boolean; override;
    procedure GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
  public
    constructor Create(AOwner : TComponent); override;
    function Link : boolean; override;
  published
    property OnExecute;
    property OnExecuteEx;
  end;

  TLiveHeader = class(TCustomLiveBlock)
  protected
    function BlockPolygon: TDotArray; override;
    procedure DrawShape(AInfo: TDiagramDrawInfo; ABlockInfo: TDiagramDrawBlockInfo); override;
    procedure UpdateLinkPoints;override;
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer; Direction : TLinkDirection) : boolean; override;
    procedure GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
  public
    constructor Create(AOwner : TComponent); override;
    function Link : boolean ; override;
  end;

procedure Register;

{$R LiveFlowchart.res}

implementation
uses Math;

procedure Register;
begin
  RegisterNoIcon([TLiveActionBlock]);
  RegisterNoIcon([TLiveDecisionBlock]);
  RegisterNoIcon([TLiveCaseBlock]);
  RegisterNoIcon([TLiveStartBlock]);
  RegisterNoIcon([TLiveEndBlock]);
  RegisterNoIcon([TLiveErrorHandler]);
  RegisterNoIcon([TLiveHeader]);
end;

{ TLiveActionBlock }

procedure TLiveActionBlock.AdjustLinkpoints;

  procedure LinkBox;
  begin
    LinkPoints[0].OrX:=50; LinkPoints[0].OrY:=0;
    LinkPoints[1].OrX:=100;LinkPoints[1].OrY:=50;
    LinkPoints[2].OrX:=50; LinkPoints[2].OrY:=100;
    LinkPoints[3].OrX:=0;  LinkPoints[3].OrY:=50;
  end;

  procedure LinkData;
  begin
    LinkPoints[0].OrX:=50; LinkPoints[0].OrY:=0;
    LinkPoints[1].OrX:=92; LinkPoints[1].OrY:=50;
    LinkPoints[2].OrX:=50; LinkPoints[2].OrY:=100;
    LinkPoints[3].OrX:=8;  LinkPoints[3].OrY:=50;
  end;

  procedure LinkDocument;
  begin
    LinkPoints[0].OrX:=50; LinkPoints[0].OrY:=0;
    LinkPoints[1].OrX:=100;LinkPoints[1].OrY:=45;
    LinkPoints[2].OrX:=50; LinkPoints[2].OrY:=90;
    LinkPoints[3].OrX:=0;  LinkPoints[3].OrY:=45;
  end;

  procedure LinkInput;
  begin
    LinkPoints[0].OrX:=50; LinkPoints[0].OrY:=15;
    LinkPoints[1].OrX:=100;LinkPoints[1].OrY:=50;
    LinkPoints[2].OrX:=50; LinkPoints[2].OrY:=100;
    LinkPoints[3].OrX:=0;  LinkPoints[3].OrY:=65;
  end;

begin
  Case FActionShape of
    asBox,
    asAlternate,
    asSubroutine  : LinkBox;
    asData : LinkData;
    asDocument : LinkDocument;
    asInput : LinkInput;
  end;
  Top:=Top-1; // Redraw is not enough
  Top:=Top+1;
end;

constructor TLiveActionBlock.Create(AOwner: TComponent);
begin
  inherited;
  FActionShape := asBox;
  // default linkpoints
  with Drawer.OriginalRect do
  begin
    LinkPoints.Add((Right - Left) / 2, Top, aoUp);        // 0
    LinkPoints.Add(Right, (Bottom - Top) / 2, aoRight);   // 1
    LinkPoints.Add((Right - Left) / 2, Bottom, aoDown);   // 2
    LinkPoints.Add(Left, (Bottom - Top) / 2, aoLeft);     // 3
  end;
end;

procedure TLiveActionBlock.DrawShape(AInfo: TDiagramDrawInfo; ABlockInfo: TDiagramDrawBlockInfo);
var
  bc,pc : integer;
begin
  inherited;
  if not PathDrawingMode then
    if FActionShape=asSubroutine then
      with AInfo.Canvas, AInfo.Drawer do
      begin
        bc:=Brush.color;
        pc:=Pen.Color;
        Brush.Color:=Self.Color;
        Pen.Color:=Self.Pen.Color;
        AutoMoveTo(10,0);
        AutoLineTo(10,100);
        AutoMoveTo(90,0);
        AutoLineTo(90,100);
        Brush.Color:=bc;
        Pen.Color:=pc;
      end;
end;

procedure TLiveActionBlock.SetFActionShape(const Value: TActionShape);
begin
  if FActionShape <> Value then
  begin
    FActionShape := Value;
    AdjustLinkpoints;
    Redraw;
  end;
end;

procedure TLiveActionBlock.UpdateLinkPoints;
begin
// See AdjustLinkPoints
end;

function TLiveActionBlock.BlockPolygon: TDotArray;

  function PolyBox : TDotArray;
  begin
    with Drawer do
    begin
      result := RotPoly(DotArray([
        PP(0, 0),
        PP(100, 0),
        PP(100, 100),
        PP(0, 100),
        PP(0, 0)
        ]));
    end;
  end;

  function PolyAlternate: TDotArray;
  var
    P1, P2: TDot;
    D: double;
  begin
    with Drawer.OriginalRect do
    begin
      P1 := Drawer.PP(Left, Top);
      P2 := Drawer.PP(Right, Bottom);
    end;
    D := Round((P2.Y - P1.Y)/2.9);
    result := Drawer.RotPoly(GetPolyRoundRect(P1.X, P1.Y, P2.X, P2.Y, D, D));
  end;

  function PolyData : TDotArray;
  begin
    with Drawer do
    begin
      result := RotPoly(DotArray([
        PP(0, 100),
        PP(16, 0),
        PP(0, 100),
        PP(16, 0),
        PP(100, 0),
        PP(84, 100),
        PP(0, 100)
        ]));
    end;
  end;

  function PolyDocument : TDotArray;
  var
    P1, P2, P3: TDotArray;
    E11, E12: TDot;
    E21, E22: TDot;
  begin
    with Drawer do
    begin
      SetLength(P1, 4);
      P1[0] := PP(0, 90);
      P1[1] := PP(0, 0);
      P1[2] := PP(100, 0);
      P1[3] := PP(100, 90);
      E11 := PP(50, 80);
      E12 := PP(100, 100);
      E21 := PP(0, 80);
      E22 := PP(50, 100);
      P2 := GetPolyEllipse(E11.X, E11.Y, E12.X, E12.Y, 180, 360, false);
      P3 := GetPolyEllipse(E21.X, E21.Y, E22.X, E22.Y, 0, 180, true);
      result := ConcatPointsX(ConcatPointsX(P1, P2), P3);
      result := RotPoly(result);
    end;
  end;

  function PolyInput : TDotArray;
  begin
    with Drawer do
    begin
      result := RotPoly(DotArray([
        PP(0, 100),
        PP(0, 30),
        PP(100, 0),
        PP(100, 100),
        PP(0, 100)
        ]));
    end;
  end;

begin
  case FActionShape of
    asBox,
    asSubroutine : Result:=PolyBox;
    asAlternate : Result:=PolyAlternate;
    asData : Result:=PolyData;
    asDocument : Result:=PolyDocument;
    asInput : Result:=polyInput;
  end;
end;

procedure TLiveActionBlock.GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);

  procedure PathBox;
  begin
    APath.AddRectangle(Square(0, 0, 100, 100));
  end;

  procedure PathSubroutine;
  begin
    APath.AddRectangle(Square(0, 0, 100, 100));
    APath.CloseFigure;
    APath.StartFigure;
    APath.AddLine(10, 0, 10, 100);
    APath.CloseFigure;
    APath.StartFigure;
    APath.AddLine(90, 0, 90, 100);
    APath.CloseFigure;
  end;

  procedure PathData;
  begin
    APath.AddLine(0, 100, 16, 0);
    APath.AddLine(100, 0, 84, 100);
    APath.CloseFigure;
  end;

  procedure PathInput;
  begin
    APath.AddLine(0, 100, 0, 30);
    APath.AddLine(100, 0, 100, 100);
    APath.CloseFigure;
  end;

begin
  APath.Reset;
  Case FActionShape of
    asBox: PathBox;
    asSubroutine : PathSubroutine;
    //asAlternate : PathAlternate;
    asData : PathData;
    //asDocument : PathDocument;
    asInput : PathInput;
  end;
end;

procedure TLiveActionBlock.GetTranslatedBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);

  procedure PathDocument;
  const
    Points: array[0..4] of TDot =
      ((X:   0; Y:  90),
       (X:  25; Y: 180),
       (X:  50; Y:  90),
       (X:  75; Y:  0),
       (X: 100; Y:  90)
       );
  var
    W: single;
    H1: single;
    H: single;
    D: single;
  begin
    APath.Reset;
    APath.StartFigure;
    with ADrawer.DestRect do
    begin
      W := Right - Left;
      H1 := (Bottom - Top) * 0.9 + Top;
      H := Bottom - Top;
      D := Min(W, H);
      APath.AddBezier(
        Left, H1,
        (Right + Left) / 2, H1 + D * 0.4,
        (Right + Left) / 2, H1 - D * 0.4,
        Right, H1
        );
      APath.AddLine(Right, Top, Left, Top);
    end;
    APath.CloseFigure;
    ADrawer.RotatePath(APath);
  end;

  procedure PathAlternate;
  begin
    APath.Reset;
    with ADrawer.DestRect do
      ADrawer.Canvas.AddRoundRectPath(APath, Left, Top, Right, Bottom, (Bottom - Top) / 2.9, (Bottom - Top) / 2.9);
    ADrawer.RotatePath(APath);
  end;

begin
  Case FActionShape of
    //asBox,
    //asSubroutine : PathBox;
    asAlternate : PathAlternate;
    //asData : PathData;
    asDocument : PathDocument;
    //asInput : PathInput;
  else
    inherited;
  end;
end;

{ TLiveDecisionBlock }

procedure TLiveDecisionBlock.UpdateLinkPoints;
begin
  LinkPoints.Clear;
  with Drawer.OriginalRect do
  begin
    LinkPoints.Add((Right - Left) / 2, Top, aoUp);      // 0 : input
    LinkPoints.Add(Right, (Bottom - Top) / 2, aoRight); // 1 : False
    LinkPoints.Add((Right - Left) / 2, Bottom, aoDown); // 2 : True
    LinkPoints.Add(Left, (Bottom - Top) / 2, aoLeft);   // 3 : Null
  end;
end;

function TLiveDecisionBlock.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  Result:=((LinkIndex = 0) and (Direction=ldInput)) or
          ((LinkIndex = 1) and (Direction=ldOutput) and (LinkPoints[1].AnchoredCount=0)) or
          ((LinkIndex = 2) and (Direction=ldOutput) and (LinkPoints[2].AnchoredCount=0));
end;

procedure TLiveDecisionBlock.AdjustLinkPoints;
var
  XT,YT,XF,YF,XN,YN : double;
  XM,YM : double;
begin
  with Drawer.OriginalRect do
  Begin
    XM:=(Right - Left) / 2;
    YM:=(Bottom - Top) / 2;

    Case FDecision of
      dsBottomRight :
      begin
        XT:=XM;     YT:=Bottom;
        XF:=Right;  YF:=YM;
        XN:=Left;   YN:=YM;
        LinkPoints[1].Orientation:=aoRight;
        LinkPoints[2].Orientation:=aoDown;
      end;
      dsRightBottom :
      begin
        XT:=Right;  YT:=YM;
        XF:=XM;     YF:=Bottom;
        XN:=Left;   YN:=YM;
        LinkPoints[1].Orientation:=aoDown;
        LinkPoints[2].Orientation:=aoRight;
      end;
      dsLeftRight :
      begin
        XT:=Left;   YT:=YM;
        XF:=Right;  YF:=YM;
        XN:=XM;     YN:=Bottom;
        LinkPoints[1].Orientation:=aoRight;
        LinkPoints[2].Orientation:=aoLeft;
      end;
      dsRightLeft :
      begin
        XT:=Right;  YT:=YM;
        XF:=Left;   YF:=YM;
        XN:=XM;     YN:=Bottom;
        LinkPoints[1].Orientation:=aoLeft;
        LinkPoints[2].Orientation:=aoRight;
      end;
      dsBottomLeft :
      begin
        XT:=XM;     YT:=Bottom;
        XF:=Left;   YF:=YM;
        XN:=Right;  YN:=YM;
        LinkPoints[1].Orientation:=aoLeft;
        LinkPoints[2].Orientation:=aoDown;
      end;
      dsLeftBottom :
      begin
        XT:=Left;   YT:=YM;
        XF:=XM;     YF:=Bottom;
        XN:=Right;  YN:=YM;
        LinkPoints[1].Orientation:=aoDown;
        LinkPoints[2].Orientation:=aoLeft;
      end;
      else
      begin
        XT:=XM;     YT:=Bottom;
        XF:=Right;  YF:=YM;
        XN:=Left;   YN:=YM;
        LinkPoints[1].Orientation:=aoRight;
        LinkPoints[2].Orientation:=aoDown;
      end;
    end;
  end;

  LinkPoints[1].OrX:=XF;
  LinkPoints[1].OrY:=YF;
  LinkPoints[2].OrX:=XT;
  LinkPoints[2].OrY:=YT;
  LinkPoints[3].OrX:=XN;
  LinkPoints[3].OrY:=YN;

  Top:=Top-1; // Redraw is not enough
  Top:=Top+1;
end;

procedure TLiveDecisionBlock.AdjustSigns;
begin
  Case FDecision of
    dsBottomRight :
    begin
      TextCells[1].Left:=62;
      TextCells[1].Top :=125;
      TextCells[2].Left:=100;
      TextCells[2].Top :=46;
    end;
    dsRightBottom :
    begin
      TextCells[1].Left:=100;
      TextCells[1].Top :=46;
      TextCells[2].Left:=62;
      TextCells[2].Top :=125;
    end;
    dsLeftRight :
    begin
      TextCells[1].Left:=0;
      TextCells[1].Top :=46;
      TextCells[2].Left:=100;
      TextCells[2].Top :=46;
    end;
    dsRightLeft :
    begin
      TextCells[1].Left:=100;
      TextCells[1].Top :=46;
      TextCells[2].Left:=0;
      TextCells[2].Top :=46;
    end;
    dsBottomLeft :
    begin
      TextCells[1].Left:=62;
      TextCells[1].Top :=125;
      TextCells[2].Left:=0;
      TextCells[2].Top :=46;
    end;
    dsLeftBottom :
    begin
      TextCells[1].Left:=0;
      TextCells[1].Top :=46;
      TextCells[2].Left:=62;
      TextCells[2].Top :=125;
    end;
    else
    begin
      TextCells[1].Left:=62;
      TextCells[1].Top :=125;
      TextCells[2].Left:=100;
      TextCells[2].Top :=46;
    end;
  end;
end;

function TLiveDecisionBlock.BlockPolygon: TDotArray;
begin
  with Drawer do
  begin
    result := RotPoly(DotArray([
      PP(50, 0),
      PP(100, 50),
      PP(50, 100),
      PP(0, 50),
      PP(50, 0)
      ]));
  end;
end;

function TLiveDecisionBlock.GetNext: TCustomLiveBlock;
begin
  Result:=FNext;
end;

function TLiveDecisionBlock.Link: boolean;
begin
  FNextTrue:=nil;
  FNextFalse:=nil;

  FNextTrue:=GetNextAt(2);
  FNextFalse:=GetNextAt(1);

  FNext:=FNextTrue;
  Result:=(FNextTrue<>nil) and (FNextFalse<>nil);
end;

procedure TLiveDecisionBlock.SetDecision(const Value: TDecisionShape);
begin
  if FDecision<>Value then
  begin
    FDecision := Value;
    AdjustLinkPoints;
    AdjustSigns;
  end;
end;

constructor TLiveDecisionBlock.Create(AOwner: TComponent);
begin
  inherited;
  FDecision:=dsBottomRight;
  With TextCells.Add do
  begin
    VertAlign:=vaBottom;
    Text:='T';
    Font.Name:='Arial';
    Font.Size:=9;
  end;
  With TextCells.Add do
  begin
    VertAlign:=vaBottom;
    Text:='F';
    Font.Name:='Arial';
    Font.Size:=9;
  end;
  AdjustSigns;
end;

procedure TLiveDecisionBlock.ExecuteEx(var ExecInfo: TExecuteNodeInfo);
begin
  inherited ExecuteEx(ExecInfo);
  if ExecInfo.Decision <> 0 then
    ExecInfo.NextNode := FNextTrue
  else
    ExecInfo.NextNode := FNextFalse;
end;

procedure TLiveDecisionBlock.GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);
begin
  APath.Reset;
  APath.AddLine(50, 0, 100, 50);
  APath.AddLine(50, 100, 0, 50);
  APath.CloseFigure;
end;

{ TCaseList }

function TCaseList.Add(aBlock: TCustomLiveBlock;
  aNumber: integer): integer;
begin
  Result:= inherited Add(aBlock);
{$WARNINGS OFF}
  NumberList.Add(Pointer(aNumber));
{$WARNINGS ON}
end;

procedure TCaseList.AddElse(aBlock: TCustomLiveBlock);
begin
  FElse:=aBlock;
end;

function TCaseList.BlockOf(Number: integer): TCustomLiveBlock;
Var
  index : integer;
begin
{$WARNINGS OFF}
  index:=NumberList.IndexOf(Pointer(Number));
  if index>-1 then
    Result:=TCustomLiveBlock(Items[index])
  else
    Result:=FElse;
{$WARNINGS ON}
end;

procedure TCaseList.Clear;
begin
  inherited;
  NumberList.Clear;
  FElse:=nil;
end;

constructor TCaseList.Create;
begin
  inherited;
  NumberList :=TList.Create;
end;

destructor TCaseList.Destroy;
begin
  inherited;
  NumberList.Free;
end;

{ TLiveCaseBlock }

function TLiveCaseBlock.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  Result:=((LinkIndex = 0) and (Direction=ldInput)) or
          ((LinkIndex = 1) and (Direction=ldOutput) and (LinkPoints[1].AnchoredCount=0)) or
          ((LinkIndex = 2) and (Direction=ldOutput));
end;

procedure TLiveCaseBlock.AdjustLinkPoints;
Var
  XT,YT,XF,YF,XN,YN : double;
  XM,YM : double;
begin
  with Drawer.OriginalRect do
  begin
    XM:=(Right - Left) / 2;
    YM:=(Bottom - Top) / 2;

    case FCaseShape of
      csBottomRight :
      begin
        XT:=XM;     YT:=Bottom;
        XF:=Right;  YF:=YM;
        XN:=Left;   YN:=YM;
        LinkPoints[1].Orientation:=aoRight;
        LinkPoints[2].Orientation:=aoDown;
      end;
      csBottomLeft :
      begin
        XT:=XM;     YT:=Bottom;
        XF:=Left;   YF:=YM;
        XN:=Right;  YN:=YM;
        LinkPoints[1].Orientation:=aoLeft;
        LinkPoints[2].Orientation:=aoDown;
      end;
      else
      begin
        XT:=XM;     YT:=Bottom;
        XF:=Right;  YF:=YM;
        XN:=Left;   YN:=YM;
        LinkPoints[1].Orientation:=aoRight;
        LinkPoints[2].Orientation:=aoDown;
      end;
    end;
  end;

  LinkPoints[1].OrX:=XF;
  LinkPoints[1].OrY:=YF;
  LinkPoints[2].OrX:=XT;
  LinkPoints[2].OrY:=YT;
  LinkPoints[3].OrX:=XN;
  LinkPoints[3].OrY:=YN;

  Top:=Top-1;
  Top:=Top+1;
end;

procedure TLiveCaseBlock.AdjustSigns;
begin
  Case FCaseShape of
    csBottomRight :
    begin
      TextCells[1].Left:=62;
      TextCells[1].Top :=125;
      TextCells[2].Left:=100;
      TextCells[2].Top :=38;
    end;
    csBottomLeft :
    begin
      TextCells[1].Left:=62;
      TextCells[1].Top :=125;
      TextCells[2].Left:=0;
      TextCells[2].Top :=38;
    end;
    else
    begin
      TextCells[1].Left:=62;
      TextCells[1].Top :=125;
      TextCells[2].Left:=100;
      TextCells[2].Top :=38;
    end;
  end;
end;

function TLiveCaseBlock.BlockPolygon: TDotArray;
begin
  with Drawer do
  begin
    result := RotPoly(DotArray([
      PP(50, 0),
      PP(100, 50),
      PP(50, 100),
      PP(0, 50),
      PP(50, 0)
      ]));
  end;
end;

constructor TLiveCaseBlock.Create(AOwner: TComponent);
begin
  inherited;
  FCaseList:=TCaseList.Create;
  FCaseShape:=csBottomRight;
  With TextCells.Add do
  begin
    VertAlign:=vaBottom;
    Text:='#';
    Font.Name:='Arial';
    Font.Size:=9;
  end;
  With TextCells.Add do
  begin
    VertAlign:=vaBottom;
    Text:='ELSE';
    Font.Name:='Arial';
    Font.Size:=9;
  end;
  AdjustSigns;
end;

destructor TLiveCaseBlock.Destroy;
begin
  FCaseList.Free;
  inherited;
end;

procedure TLiveCaseBlock.DoExecute(var Error, Decision: integer);
begin
  FNext := FNextElse;
  if Assigned(FOnExecute) then
  begin
    FOnExecute(self, Error, Decision);
    FNext := FCaseList.BlockOf(Decision);
  end;
end;

procedure TLiveCaseBlock.GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);
begin
  APath.Reset;
  APath.AddLine(50, 0, 100, 50);
  APath.AddLine(50, 100, 0, 50);
  APath.CloseFigure;
end;

function TLiveCaseBlock.GetNext: TCustomLiveBlock;
begin
  Result:=FNext;
end;

function TLiveCaseBlock.Link: boolean;
var
  aLink  : TCustomDiagramLine;
  aBlock : TCustomLiveBlock;
  c      : integer;
  Duplicate : boolean;
  BadIndex  : boolean;

  function CreateIndex(aLine : TCustomDiagramLine) : boolean;
  var
    S : String;
    index,
    Code : integer;
  begin
    if aLine.TextCells.Count>0 then
      S:=aLine.TextCells[0].Text
    else
      S:='';
    Val(S,index,Code);
    if Code<>0 then
      BadIndex:=true
    else
      aLine.Tag:=index;

    Result:=not BadIndex;
  end;

begin
  FCaseList.Clear;
  FNextElse:=nil;
  Duplicate:=false;
  BadIndex :=false;

  for c:=0 to LinkPoints[2].AnchoredCount-1 do
  begin
    if Assigned(LinkPoints[2].Anchoreds[c]) and
       (LinkPoints[2].Anchoreds[c].DControl is TCustomDiagramLine) then
    begin
      aLink:=TCustomDiagramLine(LinkPoints[2].Anchoreds[c].DControl);
        if ValidateWire(aLink, aBlock, ldOutput) and (aLink.SourceLinkPoint.AnchorIndex=2) and CreateIndex(aLink) then
        begin
           if aBlock.PassThrough then
             aBlock:=aBlock.Next;
           if FCaseList.BlockOf(aLink.Tag)<>nil then // duplicate case number
             Duplicate:=true
           else
             FCaseList.Add(aBlock,aLink.Tag);
        end;
    end; // if assigned
  end; // for c


  FNextElse:=GetNextAt(1);
  FCaseList.AddElse(FNextElse);

  Result:=not Duplicate and not BadIndex and (FCaseList.Count>0) and (FNextElse<>nil);
end;

procedure TLiveCaseBlock.SetCaseShape(const Value: TCaseShape);
begin
  if FCaseShape<>Value then
  begin
    FCaseShape := Value;
    AdjustLinkPoints;
    AdjustSigns;
  end;
end;

procedure TLiveCaseBlock.UpdateLinkPoints;
begin
  LinkPoints.Clear;
  with Drawer.OriginalRect do
  begin
    LinkPoints.Add((Right - Left) / 2, Top, aoUp);      // 0 : input
    LinkPoints.Add(Right, (Bottom - Top) / 2, aoRight); // 1 : Else
    LinkPoints.Add((Right - Left) / 2, Bottom, aoDown); // 2 : Number
    LinkPoints.Add(Left, (Bottom - Top) / 2, aoLeft);   // 3 : Null
  end;
end;

{ TCustomTerminalBlock }

function TCustomTerminalBlock.BlockPolygon: TDotArray;
var
  P1, P2: TDot;
  D: number;
begin
  with Drawer.OriginalRect do
  begin
    P1 := Drawer.PP(Left, Top);
    P2 := Drawer.PP(Right, Bottom);
  end;
  D := P2.Y - P1.Y;
  result := Drawer.RotPoly(GetPolyRoundRect(P1.X, P1.Y, P2.X, P2.Y, D, D));
end;

procedure TCustomTerminalBlock.GetTranslatedBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);
begin
  with ADrawer.DestRect do
    ADrawer.Canvas.AddRoundRectPath(APath, Left, Top, Right, Bottom, Bottom - Top, Bottom - Top);
  ADrawer.RotatePath(APath);
end;

{ TLiveStartBlock }

function TLiveStartBlock.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  Result:=(LinkIndex = 0) and (Direction=ldOutput) and (LinkPoints[0].AnchoredCount=0);
end;

constructor TLiveStartBlock.Create(AOwner: TComponent);
begin
  inherited;
  IsStartBlock:=true;
  TextCells[0].Text:='START';
end;

function TLiveStartBlock.GetNext: TCustomLiveBlock;
begin
  if not Assigned(FNext) then
    FNext:=GetNextAt(0);
  Result:=FNext;
end;

procedure TLiveStartBlock.UpdateLinkPoints;
begin
  LinkPoints.Clear;
  with Drawer.OriginalRect do
    LinkPoints.Add((Right - Left) / 2, Bottom, aoDown);   // 0 output
end;

{ TLiveEndBlock }

function TLiveEndBlock.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  Result:=Direction=ldInput;
end;

constructor TLiveEndBlock.Create(AOwner: TComponent);
begin
  inherited;
  IsEndBlock := true;
  TextCells[0].Text := 'END';
end;

procedure TLiveEndBlock.DoExecute(var Error, Decision: integer);
begin
  inherited DoExecute(Error, Decision);
  if Error=0 then
    Error:=Sys_End_Program;
end;

function TLiveEndBlock.GetNext: TCustomLiveBlock;
begin
  Result:=nil;
end;

function TLiveEndBlock.Link: boolean;
begin
  Result:=true;
end;

{ TLiveHeader }

function TLiveHeader.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  Result:=false;
end;

function TLiveHeader.BlockPolygon: TDotArray;
begin
  with Drawer do
  begin
    Result := RotPoly(DotArray([
      PP(0, 0),
      PP(90, 0),
      PP(100,20),
      PP(100, 100),
      PP(0, 100),
      PP(0, 0) ]));
  end;
end;

constructor TLiveHeader.Create(AOwner: TComponent);
begin
  inherited;
  PassThrough:=true;
  TextCells[0].Text:='Header';
end;

procedure TLiveHeader.DrawShape(AInfo: TDiagramDrawInfo; ABlockInfo: TDiagramDrawBlockInfo);
var
  BlockPoly: TPointArray;
begin
  inherited;
  with AInfo.Drawer do
    BlockPoly := RoundDotArray(RotPoly(DotArray([PP(90,20), PP(90,0), PP(100,20) ])));
  AInfo.Canvas.Polygon(BlockPoly);
end;

procedure TLiveHeader.GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);
const
  POLYGON: array[0..7] of TDot =
    ((x:  90; y:   0),
     (x: 100; y:  20),
     (x: 100; y: 100),
     (x:   0; y: 100),
     (x:   0; y:   0),
     (x:  90; y:   0),
     (x: 100; y:  20),
     (x:  90; y:  20)
     );
begin
  APath.SetFillMode(fmWinding);
  APath.AddPolygon(MakeDotArray(POLYGON));
end;

function TLiveHeader.Link: boolean;
begin
  Result:=true;
end;

procedure TLiveHeader.UpdateLinkPoints;
begin
  LinkPoints.Clear;
end;

{ TLiveErrorHandler }

function TLiveErrorHandler.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  Result:=(LinkIndex = 0) and (Direction=ldOutput) and (LinkPoints[0].AnchoredCount=0);
end;

function TLiveErrorHandler.BlockPolygon: TDotArray;
begin
  with Drawer do
  begin
    result := RotPoly(DotArray([
      PP(0, 0),
      PP(100, 0),
      PP(100, 100),
      PP(0, 100),
      PP(0, 0)
      ]));
  end;
end;

constructor TLiveErrorHandler.Create(AOwner: TComponent);
begin
  inherited;
  IsErrorHandler:=true;
  TextCells[0].Text:='OnError';
end;

procedure TLiveErrorHandler.DrawShape(AInfo: TDiagramDrawInfo; ABlockInfo: TDiagramDrawBlockInfo);
var
  bc,pc : integer;
begin
  inherited;
  if not PathDrawingMode then
    with AInfo.Canvas, AInfo.Drawer do
    begin
      bc:=Brush.color;
      pc:=Pen.Color;
      Brush.Color:=Self.Color;
      Pen.Color:=Self.Pen.Color;
      AutoMoveTo(0,10);
      AutoLineTo(100,10);
      Brush.Color:=bc;
      Pen.Color:=pc;
    end;
end;

procedure TLiveErrorHandler.GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);
begin
  APath.Reset;
  APath.AddRectangle(Square(0, 0, 100, 100));
  APath.CloseFigure;
  APath.StartFigure;
  APath.AddLine(0, 10, 100, 10);
  APath.CloseFigure;
end;

function TLiveErrorHandler.GetNext: TCustomLiveBlock;
begin
  if not Assigned(FNext) then
    FNext:=GetNextAt(0);
  Result:=FNext;
end;

function TLiveErrorHandler.Link: boolean;
begin
  FNext:=nil;
  FNext:=Next;
  Result:=True;
end;

procedure TLiveErrorHandler.UpdateLinkPoints;
begin
  LinkPoints.Clear;
  with Drawer.OriginalRect do
    LinkPoints.Add((Right - Left) / 2, Bottom, aoDown);   // 0 output
end;

initialization
  RegisterDControl(TLiveActionBlock, '', 'Action', 'Live Diagram');
  RegisterDControl(TLiveDecisionBlock,'', 'Decision', 'Live Diagram');
  RegisterDControl(TLiveCaseBlock,'', 'Case', 'Live Diagram');
  RegisterDControl(TLiveStartBlock, '', 'Start program', 'Live Diagram');
  RegisterDControl(TLiveEndBlock, '', 'End program', 'Live Diagram');
  RegisterDControl(TLiveErrorHandler, '', 'Error handler', 'Live Diagram');
  RegisterDControl(TLiveHeader, '', 'Header', 'Live Diagram');
end.

