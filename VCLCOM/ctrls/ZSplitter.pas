
unit ZSplitter;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls;

const
  {$EXTERNALSYM DFS_COMPONENT_VERSION}
  DFS_COMPONENT_VERSION = 'TZSplitter v3.0';
  MOVEMENT_TOLERANCE = 5; // See WMLButtonUp message handler.
  DEF_BUTTON_HIGHLIGHT_COLOR = $00FFCFCF;

type
  TrsButtonWidthType = (btwPixels, btwPercentage);
  TrsButtonStyle = (bsNetscape, bsWindows);
  TrsWindowsButton = (wbMin, wbMax, wbClose);
  TrsWindowsButtons = set of TrsWindowsButton;

  TZSplitter = class(TSplitter)
  private
    FShowButton: boolean;
    FButtonWidthType: TrsButtonWidthType;
    FButtonWidth: integer;
    FOnMaximize: TNotifyEvent;
    FOnMinimize: TNotifyEvent;
    FOnRestore: TNotifyEvent;
    FMaximized: boolean;
    FMinimized: boolean;
    // Internal use for "restoring" from "maximized" state
    FRestorePos: integer;
    // For internal use to avoid calling GetButtonRect when not necessary
    FLastKnownButtonRect: TRect;
    // Internal use to avoid unecessary painting
    FIsHighlighted: boolean;
    // Internal for detecting real clicks
    FGotMouseDown: boolean;
    FButtonColor: TColor;
    FButtonHighlightColor: TColor;
    FArrowColor: TColor;
    FTextureColor1: TColor;
    FTextureColor2: TColor;
    FAutoHighlightColor : boolean;
    FAllowDrag: boolean;
    FButtonStyle: TrsButtonStyle;
    FWindowsButtons: TrsWindowsButtons;
    FOnClose: TNotifyEvent;
    FButtonCursor: TCursor;
    procedure SetShowButton(const Value: boolean);
    procedure SetButtonWidthType(const Value: TrsButtonWidthType);
    procedure SetButtonWidth(const Value: integer);
    function GetButtonRect: TRect;
    procedure SetMaximized(const Value: boolean);
    procedure SetMinimized(const Value: boolean);
    function GetAlign: TAlign;
    procedure SetAlign(Value: TAlign);
    procedure SetArrowColor(const Value: TColor);
    procedure SetButtonColor(const Value: TColor);
    procedure SetButtonHighlightColor(const Value: TColor);
    procedure SetButtonStyle(const Value: TrsButtonStyle);
    procedure SetTextureColor1(const Value: TColor);
    procedure SetTextureColor2(const Value: TColor);
    procedure SetAutoHighLightColor(const Value: boolean);
    procedure SetAllowDrag(const Value: boolean);
    procedure SetWindowsButtons(const Value: TrsWindowsButtons);
    procedure SetButtonCursor(const Value: TCursor);
    function GetVersion: string;
    procedure SetVersion(const Val: string);
    procedure WMLButtonDown(var Msg: TWMLButtonDown); message WM_LBUTTONDOWN;
    procedure WMLButtonUp(var Msg: TWMLButtonUp); message WM_LBUTTONUP;
    procedure WMMouseMove(var Msg: TWMMouseMove); message WM_MOUSEMOVE;
    procedure CMMouseEnter(var Msg: TWMMouse); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Msg: TWMMouse); message CM_MOUSELEAVE;
  protected
    // Internal use for moving splitter position with FindControl and
    // UpdateControlSize
    FControl: TControl;
    FDownPos: TPoint;

    procedure LoadOtherProperties(Reader: TReader); dynamic;
    procedure StoreOtherProperties(Writer: TWriter); dynamic;
    procedure DefineProperties(Filer: TFiler); override;
    procedure Paint; override;
    function DoCanResize(var NewSize: integer): boolean; override;
    procedure Loaded; override;
    procedure PaintButton(Highlight: boolean); dynamic;
    function DrawArrow(ACanvas: TCanvas; AvailableRect: TRect; iOffset: integer;
       ArrowSize: integer; Color: TColor): integer; dynamic;
    function WindowButtonHitTest(X, Y: integer): TrsWindowsButton; dynamic;
    function ButtonHitTest(X, Y: integer): boolean; dynamic;
    procedure DoMaximize; dynamic;
    procedure DoMinimize; dynamic;
    procedure DoRestore; dynamic;
    procedure DoClose; dynamic;
    procedure FindControl; dynamic;
    procedure UpdateControlSize(NewSize: integer); dynamic;
    function GrabBarColor: TColor;
    function VisibleWinButtons: integer;
  public
    constructor Create(AOwner: TComponent); override;

    procedure SetBounds(ALeft, ATop, AWidth, AHeight: Integer); override;

    property ButtonRect: TRect
       read GetButtonRect;
    property RestorePos: integer
       read FRestorePos
       write FRestorePos;
  published
    property Maximized: boolean
       read FMaximized
       write SetMaximized;
    property Minimized: boolean
       read FMinimized
       write SetMinimized;


    property Version: string
       read GetVersion
       write SetVersion
       stored FALSE;
    property AllowDrag: boolean
       read FAllowDrag
       write SetAllowDrag
       default TRUE;
    property ButtonCursor: TCursor
       read FButtonCursor
       write SetButtonCursor;
    property ButtonStyle: TrsButtonStyle
       read FButtonStyle
       write SetButtonStyle
       default bsNetscape;
    property WindowsButtons: TrsWindowsButtons
       read FWindowsButtons
       write SetWindowsButtons
       default [wbMin, wbMax, wbClose];
    property ButtonWidthType: TrsButtonWidthType
       read FButtonWidthType
       write SetButtonWidthType
       default btwPixels;
    property ButtonWidth: integer
       read FButtonWidth
       write SetButtonWidth
       default 100;
    property ShowButton: boolean
       read FShowButton
       write SetShowButton
       default TRUE;
    property ButtonColor: TColor
       read FButtonColor
       write SetButtonColor
       default clBtnFace;
    property ArrowColor: TColor
       read FArrowColor
       write SetArrowColor
       default clNavy;
    property ButtonHighlightColor: TColor
       read FButtonHighlightColor
       write SetButtonHighlightColor
       default DEF_BUTTON_HIGHLIGHT_COLOR;
    property AutoHighlightColor: Boolean
       read FAutoHighlightColor
       write SetAutoHighlightColor
       default FALSE;
    property TextureColor1: TColor
       read FTextureColor1
       write SetTextureColor1
       default clWhite;
    property TextureColor2: TColor
       read FTextureColor2
       write SetTextureColor2
       default clNavy;
    property Align: TAlign // Need to know when it changes to redraw arrows
       read GetAlign
       write SetAlign;
    property Width
       default 10;  // it looks best with 10
    property Beveled
       default FALSE; // it looks best without the bevel
    property Enabled;

    property OnClose: TNotifyEvent
       read FOnClose
       write FOnClose;
    property OnMaximize: TNotifyEvent
       read FOnMaximize
       write FOnMaximize;
    property OnMinimize: TNotifyEvent
       read FOnMinimize
       write FOnMinimize;
    property OnRestore: TNotifyEvent
       read FOnRestore
       write FOnRestore;
  end;

procedure Register;

implementation

{ TZSplitter }

constructor TZSplitter.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);

  Beveled := FALSE;
  FAllowDrag := TRUE;
  FButtonStyle := bsNetscape;
  FWindowsButtons := [wbMin, wbMax, wbClose];
  FButtonWidthType := btwPercentage;
  FButtonWidth := 50;
  FShowButton := TRUE;
  SetRectEmpty(FLastKnownButtonRect);
  FIsHighlighted := FALSE;
  FGotMouseDown := FALSE;
  FControl := NIL;
  FDownPos := Point(0,0);
  FMaximized := FALSE;
  FMinimized := FALSE;
  FRestorePos := -1;
  Width := 10;
  MinSize:=1;
  FButtonColor := clBtnFace;
  FArrowColor := clNavy;
  FButtonHighlightColor := DEF_BUTTON_HIGHLIGHT_COLOR;
  FAutoHighLightColor := FALSE;
  FTextureColor1 := clWhite;
  FTextureColor2 := clNavy;
end;

function TZSplitter.GrabBarColor: TColor;
var
  BeginRGB: array[0..2] of Byte;
  RGBDifference: array[0..2] of integer;
  R,G,B: Byte;
  BeginColor,
  EndColor: TColor;
  NumberOfColors: integer;

begin
  //Need to figure out how many colors available at runtime
  NumberOfColors := 256;

  BeginColor := clActiveCaption;
  EndColor := clBtnFace;

  BeginRGB[0] := GetRValue(ColorToRGB(BeginColor));
  BeginRGB[1] := GetGValue(ColorToRGB(BeginColor));
  BeginRGB[2] := GetBValue(ColorToRGB(BeginColor));

  RGBDifference[0] := GetRValue(ColorToRGB(EndColor)) - BeginRGB[0];
  RGBDifference[1] := GetGValue(ColorToRGB(EndColor)) - BeginRGB[1];
  RGBDifference[2] := GetBValue(ColorToRGB(EndColor)) - BeginRGB[2];

  R := BeginRGB[0] + MulDiv (180, RGBDifference[0], NumberOfColors - 1);
  G := BeginRGB[1] + MulDiv (180, RGBDifference[1], NumberOfColors - 1);
  B := BeginRGB[2] + MulDiv (180, RGBDifference[2], NumberOfColors - 1);

  Result := RGB (R, G, B);
end;

function TZSplitter.DrawArrow(ACanvas: TCanvas; AvailableRect: TRect; iOffset: integer;
   ArrowSize: integer; Color: TColor): integer;
var
  x, y, q, i, j: integer;
  ArrowAlign: TAlign;
begin
  // STB Nitro drivers have a LineTo bug, so I've opted to use the slower
  // SetPixel method to draw the arrows.

  if not Odd(ArrowSize) then
    Dec(ArrowSize);
  if ArrowSize < 1 then
    ArrowSize := 1;

  if FMaximized then
  begin
    case Align of
      alLeft:   ArrowAlign := alRight;
      alRight:  ArrowAlign := alLeft;
      alTop:    ArrowAlign := alBottom;
    else //alBottom
      ArrowAlign := alTop;
    end;
  end else
    ArrowAlign := Align;
  q := ArrowSize * 2 - 1 ;
  Result := q;
  ACanvas.Pen.Color := Color;
  with AvailableRect do
  begin
    case ArrowAlign of
      alLeft:
        begin
          x := Left + ((Right - Left - ArrowSize) div 2) + 1;
          if iOffset < 0 then
            y := Bottom + iOffset - q
          else
            y := Top + iOffset;
          for j := x + ArrowSize - 1 downto x do
          begin
            for i := y to y + q - 1 do
              ACanvas.Pixels[j, i] := Color;
            inc(y);
            dec(q,2);
          end;
        end;
      alRight:
        begin
          x := Left + ((Right - Left - ArrowSize) div 2) + 1;
          if iOffset < 0 then
            y := Bottom + iOffset - q
          else
            y := Top + iOffset;
          for j := x to x + ArrowSize - 1 do
          begin
            for i := y to y + q - 1 do
              ACanvas.Pixels[j, i] := Color;
            inc(y);
            dec(q,2);
          end;
        end;
      alTop:
        begin
          if iOffset < 0 then
            x := Right + iOffset - q
          else
            x := Left + iOffset;
          y := Top + ((Bottom - Top - ArrowSize) div 2) + 1;
          for i := y + ArrowSize - 1 downto y do
          begin
            for j := x to x + q - 1 do
              ACanvas.Pixels[j, i] := Color;
            inc(x);
            dec(q,2);
          end;
        end;
    else // alBottom
      if iOffset < 0 then
        x := Right + iOffset - q
      else
        x := Left + iOffset;
      y := Top + ((Bottom - Top - ArrowSize) div 2) + 1;
      for i := y to y + ArrowSize - 1 do
      begin
        for j := x to x + q - 1 do
          ACanvas.Pixels[j, i] := Color;
        inc(x);
        dec(q,2);
      end;
    end;
  end;
end;

function TZSplitter.GetButtonRect: TRect;
var
  BW: integer;
begin
  if ButtonStyle = bsWindows then
  begin
    if Align in [alLeft, alRight] then
      BW := (ClientRect.Right - ClientRect.Left) * VisibleWinButtons
    else
      BW := (ClientRect.Bottom - ClientRect.Top) * VisibleWinButtons;
    if BW < 1 then
      SetRectEmpty(Result)
    else
    begin
      if Align in [alLeft, alRight] then
        Result := Rect(0, 0, ClientRect.Right - ClientRect.Left, BW -
          VisibleWinButtons)
      else
        Result := Rect(ClientRect.Right - BW + VisibleWinButtons, 0,
          ClientRect.Right, ClientRect.Bottom - ClientRect.Top);
      InflateRect(Result, -1, -1);
    end;
  end
  else
  begin
    // Calc the rectangle the button goes in
    if ButtonWidthType = btwPercentage then
    begin
      if Align in [alLeft, alRight] then
        BW := ClientRect.Bottom - ClientRect.Top
      else
        BW := ClientRect.Right - ClientRect.Left;
      BW := MulDiv(BW, FButtonWidth, 100);
    end
    else
      BW := FButtonWidth;
    if BW < 1 then
      SetRectEmpty(Result)
    else
    begin
      Result := ClientRect;
      if Align in [alLeft, alRight] then
      begin
        Result.Top := (ClientRect.Bottom - ClientRect.Top - BW) div 2;
        Result.Bottom := Result.Top + BW;
        InflateRect(Result, -1, 0);
      end
      else
      begin
        Result.Left := (ClientRect.Right - ClientRect.Left - BW) div 2;
        Result.Right := Result.Left + BW;
        InflateRect(Result, 0, -1);
      end;
    end;
  end;
  if not IsRectEmpty(Result) then
  begin
    if Result.Top < 1 then
      Result.Top := 1;
    if Result.Left < 1 then
      Result.Left := 1;
    if Result.Bottom >= ClientRect.Bottom then
      Result.Bottom := ClientRect.Bottom - 1;
    if Result.Right >= ClientRect.Right then
      Result.Right := ClientRect.Right - 1;
    // Make smaller if it's beveled
    if Beveled then
      if Align in [alLeft, alRight] then
        InflateRect(Result, -3, 0)
      else
        InflateRect(Result, 0, -3);
  end;
  FLastKnownButtonRect := Result;
end;

procedure TZSplitter.Paint;
begin
// Exclude button rect from update region here for less flicker.
  inherited Paint;

// Don't paint while being moved unless ResizeStyle = rsUpdate!!!
// Make rect smaller if Beveled is true.
  PaintButton(FIsHighlighted);
end;

function TZSplitter.DoCanResize(var NewSize: integer): boolean;
begin
  Result := inherited DoCanResize(NewSize);
  // D4 version has a bug that causes it to not honor MinSize, which causes a
  // really nasty problem.
  if Result and (NewSize < MinSize) then
    NewSize := MinSize;
end;

procedure TZSplitter.PaintButton(Highlight: boolean);
const
  TEXTURE_SIZE = 3;
var
  BtnRect: TRect;
  CaptionBtnRect: TRect;
  BW: integer;
  TextureBmp: TBitmap;
  x, y: integer;
  RW, RH: integer;
  OffscreenBmp: TBitmap;
  WinButton: array[0..2] of TrsWindowsButton;
  b: TrsWindowsButton;
  BtnFlag: UINT;
begin
  if (not FShowButton) or (not Enabled) or (GetParentForm(Self) = NIL) then
    exit;

  if FAutoHighLightColor then
    FButtonHighlightColor := GrabBarColor;

  BtnRect := ButtonRect; // So we don't repeatedly call GetButtonRect
  if IsRectEmpty(BtnRect) then
    exit; // nothing to draw

  OffscreenBmp := TBitmap.Create;
  try
    OffsetRect(BtnRect, -BtnRect.Left, -BtnRect.Top);
    OffscreenBmp.Width := BtnRect.Right;
    OffscreenBmp.Height := BtnRect.Bottom;

    if ButtonStyle = bsWindows then
    begin
      OffscreenBmp.Canvas.Brush.Color := Color;
      OffscreenBmp.Canvas.FillRect(BtnRect);
      if Align in [alLeft, alRight] then
        BW := BtnRect.Right
      else
        BW := BtnRect.Bottom;
      FillChar(WinButton, SizeOf(WinButton), 0);
      x := 0;
      if Align in [alLeft, alRight] then
      begin
        for b := High(TrsWindowsButton) downto Low(TrsWindowsButton) do
          if b in WindowsButtons then
          begin
            WinButton[x] := b;
            inc(x);
          end;
      end
      else
      begin
        for b := Low(TrsWindowsButton) to High(TrsWindowsButton) do
          if b in WindowsButtons then
          begin
            WinButton[x] := b;
            inc(x);
          end;
      end;
      for x := 0 to VisibleWinButtons - 1 do
      begin
        if Align in [alLeft, alRight] then
          CaptionBtnRect := Bounds(0, x * BW, BW, BW)
        else
          CaptionBtnRect := Bounds(x * BW, 0, BW, BW);
        BtnFlag := 0;
        case WinButton[x] of
          wbMin:
            begin
              if Minimized then
                BtnFlag := DFCS_CAPTIONRESTORE
              else
                BtnFlag := DFCS_CAPTIONMIN;
            end;
          wbMax:
            begin
              if Maximized then
                BtnFlag := DFCS_CAPTIONRESTORE
              else
                BtnFlag := DFCS_CAPTIONMAX;
            end;
          wbClose:
            begin
              BtnFlag := DFCS_CAPTIONCLOSE;
            end;
        end;
        DrawFrameControl(OffscreenBmp.Canvas.Handle, CaptionBtnRect, DFC_CAPTION,
          BtnFlag);
      end;
    end
    else
    begin
      // Draw basic button
      OffscreenBmp.Canvas.Brush.Color := clGray;
      OffscreenBmp.Canvas.FrameRect(BtnRect);
      InflateRect(BtnRect, -1, -1);

      OffscreenBmp.Canvas.Pen.Color := clWhite;
      with BtnRect, OffscreenBmp.Canvas do
      begin
        // This is not going to work with the STB bug.  Have to find workaround.
        MoveTo(Left, Bottom-1);
        LineTo(Left, Top);
        LineTo(Right, Top);
      end;
      Inc(BtnRect.Left);
      Inc(BtnRect.Top);

      if Highlight then
        OffscreenBmp.Canvas.Brush.Color := ButtonHighlightColor
      else
        OffscreenBmp.Canvas.Brush.Color := ButtonColor;
      OffscreenBmp.Canvas.FillRect(BtnRect);
      FIsHighlighted := Highlight;
      Dec(BtnRect.Right);
      Dec(BtnRect.Bottom);

      // Draw the insides of the button
      with BtnRect do
      begin
        // Draw the arrows
        if Align in [alLeft, alRight] then
        begin
          InflateRect(BtnRect, 0, -4);
          BW := BtnRect.Right - BtnRect.Left;
          DrawArrow(OffscreenBmp.Canvas, BtnRect, 1, BW, ArrowColor);
          BW := DrawArrow(OffscreenBmp.Canvas, BtnRect, -1, BW, ArrowColor);
          InflateRect(BtnRect, 0, -(BW+4));
        end else begin
          InflateRect(BtnRect, -4, 0);
          BW := BtnRect.Bottom - BtnRect.Top;
          DrawArrow(OffscreenBmp.Canvas, BtnRect, 1, BW, ArrowColor);
          BW := DrawArrow(OffscreenBmp.Canvas, BtnRect, -1, BW, ArrowColor);
          InflateRect(BtnRect, -(BW+4), 0);
        end;

        // Draw the texture
        // Note: This is so complex because I'm trying to make as much like the
        //       Netscape splitter as possible.  They use a 3x3 texture pattern, and
        //       that's harder to tile.  If the had used an 8x8 (or smaller
        //       divisibly, i.e. 2x2 or 4x4), I could have used Brush.Bitmap and
        //       FillRect and they whole thing would have been about half the size,
        //       twice as fast, and 1/10th as complex.
        RW := BtnRect.Right - BtnRect.Left;
        RH := BtnRect.Bottom - BtnRect.Top;
        if (RW >= TEXTURE_SIZE) and (RH >= TEXTURE_SIZE) then
        begin
          TextureBmp := TBitmap.Create;
          try
            with TextureBmp do
            begin
              Width := RW;
              Height := RH;
              // Draw first square
              Canvas.Brush.Color := OffscreenBmp.Canvas.Brush.Color;
              Canvas.FillRect(Rect(0, 0, RW+1, RH+1));
              Canvas.Pixels[1,1] := TextureColor1;
              Canvas.Pixels[2,2] := TextureColor2;

              // Tile first square all the way across
              for x := 1 to ((RW div TEXTURE_SIZE) + ord(RW mod TEXTURE_SIZE > 0)) do
              begin
                Canvas.CopyRect(Bounds(x * TEXTURE_SIZE, 0, TEXTURE_SIZE,
                   TEXTURE_SIZE), Canvas, Rect(0, 0, TEXTURE_SIZE, TEXTURE_SIZE));
              end;

              // Tile first row all the way down
              for y := 1 to ((RH div TEXTURE_SIZE) + ord(RH mod TEXTURE_SIZE > 0)) do
              begin
                Canvas.CopyRect(Bounds(0, y * TEXTURE_SIZE, RW, TEXTURE_SIZE),
                   Canvas, Rect(0, 0, RW, TEXTURE_SIZE));
              end;

              // Above could be better if it reversed process when splitter was
              // taller than it was wider.  Optimized only for horizontal right now.
            end;
            // Copy texture bitmap to the screen.
            OffscreenBmp.Canvas.CopyRect(BtnRect, TextureBmp.Canvas,
               Rect(0, 0, RW, RH));
          finally
            TextureBmp.Free;
          end;
        end;
      end;
    end;
(**)
    Canvas.CopyRect(ButtonRect, OffscreenBmp.Canvas, Rect(0, 0,
       OffscreenBmp.Width, OffscreenBmp.Height));
  finally
    OffscreenBmp.Free;
  end;
end;

procedure TZSplitter.SetButtonWidth(const Value: integer);
begin
  if Value <> FButtonWidth then
  begin
    FButtonWidth := Value;
    if (FButtonWidthType = btwPercentage) and (FButtonWidth > 100) then
      FButtonWidth := 100;
    if FButtonWidth < 0 then
      FButtonWidth := 0;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetButtonWidthType(const Value: TrsButtonWidthType);
begin
  if Value <> FButtonWidthType then
  begin
    FButtonWidthType := Value;
    if (FButtonWidthType = btwPercentage) and (FButtonWidth > 100) then
      FButtonWidth := 100;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetShowButton(const Value: boolean);
begin
  if Value <> FShowButton then
  begin
    FShowButton := Value;
    SetRectEmpty(FLastKnownButtonRect);
    Invalidate;
  end;
end;

procedure TZSplitter.WMMouseMove(var Msg: TWMMouseMove);
begin
  if AllowDrag then
  begin
    inherited;

    // The order is important here.  ButtonHitTest must be evaluated before
    // the ButtonStyle because it will change the cursor (over button or not).
    // If the order were reversed, the cursor would not get set for bsWindows
    // style since short-circuit boolean eval would stop it from ever being
    // called in the first place.
    if ButtonHitTest(Msg.XPos, Msg.YPos) and (ButtonStyle = bsNetscape) then
    begin
      if not FIsHighlighted then
        PaintButton(TRUE)
    end else
      if FIsHighlighted then
        PaintButton(FALSE);
  end else
    DefaultHandler(Msg); // Bypass TSplitter and just let normal handling occur.
end;

procedure TZSplitter.CMMouseEnter(var Msg: TWMMouse);
var
  Pos: TPoint;
begin
  inherited;

  GetCursorPos(Pos); // CM_MOUSEENTER doesn't send mouse pos.
  Pos := Self.ScreenToClient(Pos);
  // The order is important here.  ButtonHitTest must be evaluated before
  // the ButtonStyle because it will change the cursor (over button or not).
  // If the order were reversed, the cursor would not get set for bsWindows
  // style since short-circuit boolean eval would stop it from ever being
  // called in the first place.
  if ButtonHitTest(Pos.x, Pos.y) and (ButtonStyle = bsNetscape) then
  begin
    if not FIsHighlighted then
      PaintButton(TRUE)
  end else
    if FIsHighlighted then
      PaintButton(FALSE);
end;

procedure TZSplitter.CMMouseLeave(var Msg: TWMMouse);
begin
  inherited;

  if (ButtonStyle = bsNetscape) and FIsHighlighted then
    PaintButton(FALSE);

  FGotMouseDown := FALSE;
end;

procedure TZSplitter.WMLButtonDown(var Msg: TWMLButtonDown);
begin
  if Enabled then
  begin
    FGotMouseDown := ButtonHitTest(Msg.XPos, Msg.YPos);
    if FGotMouseDown then
    begin
      FindControl;
      FDownPos := ClientToScreen(Point(Msg.XPos, Msg.YPos));
    end;
  end;
  if AllowDrag then
    inherited // Let TSplitter have it.
  else
    // Bypass TSplitter and just let normal handling occur. Prevents drag painting.
    DefaultHandler(Msg);
end;

procedure TZSplitter.WMLButtonUp(var Msg: TWMLButtonUp);
var
  CurPos: TPoint;
  OldMax: boolean;
begin
  inherited;

  if FGotMouseDown then
  begin
    if ButtonHitTest(Msg.XPos, Msg.YPos) then
    begin
      CurPos := ClientToScreen(Point(Msg.XPos, Msg.YPos));
      // More than a little movement is not a click, but a regular resize.
      if ((Align in [alLeft, alRight]) and
         (Abs(FDownPos.x - CurPos.X) <= MOVEMENT_TOLERANCE)) or
         ((Align in [alTop, alBottom]) and
         (Abs(FDownPos.y - CurPos.Y) <= MOVEMENT_TOLERANCE)) then
      begin
        StopSizing;
        if ButtonStyle = bsNetscape then
          Maximized := not Maximized
        else
          case WindowButtonHitTest(Msg.XPos, Msg.YPos) of
            wbMin: Minimized := not Minimized;
            wbMax: Maximized := not Maximized;
            wbClose: DoClose;
          end;
      end;
    end;
    FGotMouseDown := FALSE;
  end
  else if AllowDrag then
  begin
    FindControl;
    if FControl = NIL then
      exit;

    OldMax := FMaximized;
    case Align of
      alLeft, alRight: FMaximized := FControl.Width <= MinSize;
      alTop, alBottom: FMaximized := FControl.Height <= MinSize;
    end;
    if FMaximized then
    begin
      UpdateControlSize(MinSize);
      if not OldMax then
        DoMaximize;
    end
    else
    begin
      case Align of
        alLeft,
        alRight:  FRestorePos := FControl.Width;
        alTop,
        alBottom: FRestorePos := FControl.Height;
      end;
      if OldMax then
        DoRestore;
    end;
  end;
  Invalidate;
end;

function TZSplitter.WindowButtonHitTest(X, Y: integer): TrsWindowsButton;
var
  BtnRect: TRect;
  i: integer;
  b: TrsWindowsButton;
  WinButton: array[0..2] of TrsWindowsButton;
  BW: integer;
  BRs: array[0..2] of TRect;
begin
  Result := wbMin;
  // Figure out which one was hit.  This function assumes ButtonHitTest has
  // been called and returned TRUE.
  BtnRect := ButtonRect; // So we don't repeatedly call GetButtonRect
  i := 0;
  if Align in [alLeft, alRight] then
  begin
    for b := High(TrsWindowsButton) downto Low(TrsWindowsButton) do
      if b in WindowsButtons then
      begin
        WinButton[i] := b;
        inc(i);
      end;
  end
  else
    for b := Low(TrsWindowsButton) to High(TrsWindowsButton) do
      if b in WindowsButtons then
      begin
        WinButton[i] := b;
        inc(i);
      end;

  if Align in [alLeft, alRight] then
    BW := BtnRect.Right - BtnRect.Left
  else
    BW := BtnRect.Bottom - BtnRect.Top;
  FillChar(BRs, SizeOf(BRs), 0);
  for i := 0 to VisibleWinButtons - 1 do
    if ((Align in [alLeft, alRight]) and PtInRect(Bounds(BtnRect.Left,
      BtnRect.Top + (BW * i), BW, BW), Point(X, Y))) or ((Align in [alTop,
      alBottom]) and PtInRect(Bounds(BtnRect.Left + (BW * i), BtnRect.Top, BW,
      BW), Point(X, Y))) then
    begin
      Result := WinButton[i];
      break;
    end;
end;

function TZSplitter.ButtonHitTest(X, Y: integer): boolean;
begin
  // We use FLastKnownButtonRect here so that we don't have to recalculate the
  // button rect with GetButtonRect every time the mouse moved.  That would be
  // EXTREMELY inefficient.
  Result := PtInRect(FLastKnownButtonRect, Point(X, Y));
  if Align in [alLeft, alRight] then
  begin
    if (not AllowDrag) or ((Y >= FLastKnownButtonRect.Top) and
      (Y <= FLastKnownButtonRect.Bottom)) then
      Cursor := FButtonCursor
    else
      Cursor := crHSplit;
  end else begin
    if (not AllowDrag) or ((X >= FLastKnownButtonRect.Left) and
      (X <= FLastKnownButtonRect.Right)) then
      Cursor := FButtonCursor
    else
      Cursor := crVSplit;
  end;
end;

procedure TZSplitter.DoMaximize;
begin
  if assigned(FOnMaximize) then
    FOnMaximize(Self);
end;


procedure TZSplitter.DoRestore;
begin
  if assigned(FOnRestore) then
    FOnRestore(Self);
end;

//DoClose

procedure TZSplitter.SetMaximized(const Value: boolean);
begin
  if Value <> FMaximized then
  begin

    if csLoading in ComponentState then
    begin
      FMaximized := Value;
      exit;
    end;

    FindControl;
    if FControl = NIL then
      exit;

    if Value then
    begin
      if FMinimized then
        FMinimized := FALSE
      else
      begin
        case Align of
          alLeft,
          alRight:  FRestorePos := FControl.Width;
          alTop,
          alBottom: FRestorePos := FControl.Height;
        else
          exit;
        end;
      end;
      if ButtonStyle = bsNetscape then
        UpdateControlSize(-3000)
      else
        case Align of
          alLeft,
          alBottom: UpdateControlSize(3000);
          alRight,
          alTop: UpdateControlSize(-3000);
        else
          exit;
        end;
      FMaximized := Value;
      DoMaximize;
    end
    else
    begin
      UpdateControlSize(FRestorePos);
      FMaximized := Value;
      DoRestore;
    end;
  end;
end;

procedure TZSplitter.SetMinimized(const Value: boolean);
begin
  if Value <> FMinimized then
  begin

    if csLoading in ComponentState then
    begin
      FMinimized := Value;
      exit;
    end;

    FindControl;
    if FControl = NIL then
      exit;

    if Value then
    begin
      if FMaximized then
        FMaximized := FALSE
      else
      begin
        case Align of
          alLeft,
          alRight:  FRestorePos := FControl.Width;
          alTop,
          alBottom: FRestorePos := FControl.Height;
        else
          exit;
        end;
      end;
      FMinimized := Value;
      // Just use something insanely large to get it to move to the other extreme
      case Align of
        alLeft,
        alBottom: UpdateControlSize(-3000);
        alRight,
        alTop: UpdateControlSize(3000);
      else
        exit;
      end;
      DoMinimize;
    end
    else
    begin
      FMinimized := Value;
      UpdateControlSize(FRestorePos);
      DoRestore;
    end;
  end;
end;

function TZSplitter.GetAlign: TAlign;
begin
  Result := inherited Align;
end;

procedure TZSplitter.SetAlign(Value: TAlign);
begin
  inherited Align := Value;

  Invalidate; // Direction changing, redraw arrows.
  if (Cursor <> crVSplit) and (Cursor <> crHSplit) then Exit;
  if Align in [alBottom, alTop] then
    Cursor := crVSplit
  else
    Cursor := crHSplit;
end;


procedure TZSplitter.FindControl;
var
  P: TPoint;
  I: Integer;
  R: TRect;
begin
  if Parent = NIL then
    exit;
  FControl := NIL;
  P := Point(Left, Top);
  case Align of
    alLeft: Dec(P.X);
    alRight: Inc(P.X, Width);
    alTop: Dec(P.Y);
    alBottom: Inc(P.Y, Height);
  else
    Exit;
  end;
  for I := 0 to Parent.ControlCount - 1 do
  begin
    FControl := Parent.Controls[I];
    if FControl.Visible and FControl.Enabled then
    begin
      R := FControl.BoundsRect;
      if (R.Right - R.Left) = 0 then
        Dec(R.Left);
      if (R.Bottom - R.Top) = 0 then
        Dec(R.Top);
      if PtInRect(R, P) then
        Exit;
    end;
  end;
  FControl := NIL;
end;


procedure TZSplitter.UpdateControlSize(NewSize: integer);
  procedure MoveViaMouse(FromPos, ToPos: integer; Horizontal: boolean);
  begin
    if Horizontal then
    begin
      MouseDown(mbLeft, [ssLeft], FromPos, 0);
      MouseMove([ssLeft], ToPos, 0);
      MouseUp(mbLeft, [ssLeft], ToPos, 0);
    end
    else
    begin
      MouseDown(mbLeft, [ssLeft], 0, FromPos);
      MouseMove([ssLeft], 0, ToPos);
      MouseUp(mbLeft, [ssLeft], 0, ToPos);
    end;
  end;
begin
  if (FControl <> NIL) then
  begin
    { You'd think that using FControl directly would be the way to change it's
      position (and thus the splitter's position), wouldn't you?  But, TSplitter
      has this nutty idea that the only way a control's size will change is if
      the mouse moves the splitter.  If you size the control manually, the
      splitter has an internal variable (FOldSize) that will not get updated.
      Because of this, if you try to then move the newly positioned splitter
      back to the old position, it won't go there (NewSize <> OldSize must be
      true).  Now, what are the odds that the user will move the splitter back
      to the exact same pixel it used to be on?  Normally, extremely low.  But,
      if the splitter has been restored from it's minimized position, it then
      becomes quite likely:  i.e. they drag it back all the way to the min
      position.  What a pain. }
    case Align of
      alLeft: MoveViaMouse(Left, FControl.Left + NewSize, TRUE);
              // alLeft: FControl.Width := NewSize;
      alTop: MoveViaMouse(Top, FControl.Top + NewSize, FALSE);
             // FControl.Height := NewSize;
      alRight: MoveViaMouse(Left, (FControl.Left + FControl.Width - Width) - NewSize, TRUE);
        {begin
          Parent.DisableAlign;
          try
            FControl.Left := FControl.Left + (FControl.Width - NewSize);
            FControl.Width := NewSize;
          finally
            Parent.EnableAlign;
          end;
        end;}
      alBottom: MoveViaMouse(Top, (FControl.Top + FControl.Height - Height) - NewSize, FALSE);
        {begin
          Parent.DisableAlign;
          try
            FControl.Top := FControl.Top + (FControl.Height - NewSize);
            FControl.Height := NewSize;
          finally
            Parent.EnableAlign;
          end;
        end;}
    end;
    Update;
  end;
end;

procedure TZSplitter.SetArrowColor(const Value: TColor);
begin
  if FArrowColor <> Value then
  begin
    FArrowColor := Value;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetButtonColor(const Value: TColor);
begin
  if FButtonColor <> Value then
  begin
    FButtonColor := Value;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetButtonHighlightColor(const Value: TColor);
begin
  if FButtonHighlightColor <> Value then
  begin
    FButtonHighlightColor := Value;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetAutoHighlightColor(const Value: boolean);
begin
  if FAutoHighLightColor <> Value then
  begin
    FAutoHighLightColor := Value;
    if FAutoHighLightColor then
      FButtonHighLightColor := GrabBarColor
    else
      FButtonHighLightColor := DEF_BUTTON_HIGHLIGHT_COLOR;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetTextureColor1(const Value: TColor);
begin
  if FTextureColor1 <> Value then
  begin
    FTextureColor1 := Value;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

procedure TZSplitter.SetTextureColor2(const Value: TColor);
begin
  if FTextureColor2 <> Value then
  begin
    FTextureColor2 := Value;
    if (ButtonStyle = bsNetscape) and ShowButton then
      Invalidate;
  end;
end;

function TZSplitter.GetVersion: string;
begin
  Result := DFS_COMPONENT_VERSION;
end;

procedure TZSplitter.SetVersion(const Val: string);
begin
  { empty write method, just needed to get it to show up in Object Inspector }
end;


procedure TZSplitter.Loaded;
begin
  inherited Loaded;
  if FRestorePos = -1 then
  begin
    FindControl;
    if FControl <> NIL then
      case Align of
        alLeft,
        alRight:  FRestorePos := FControl.Width;
        alTop,
        alBottom: FRestorePos := FControl.Height;
      end;
  end;
{  if FMaximized then
  begin
    FMaximized := FALSE;
    Maximized := TRUE;
  end
  else
  if FMinimized then
  begin
    FMinimized := FALSE;
    Minimized := TRUE;
  end;}
end;

procedure TZSplitter.SetBounds(ALeft, ATop, AWidth, AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  if FRestorePos < 0 then
  begin
    FindControl;
    if FControl <> NIL then
      case Align of
        alLeft,
        alRight:  FRestorePos := FControl.Width;
        alTop,
        alBottom: FRestorePos := FControl.Height;
      end;
  end;
end;

procedure TZSplitter.SetAllowDrag(const Value: boolean);
var
  Pt: TPoint;
begin
  if FAllowDrag <> Value then
  begin
    FAllowDrag := Value;
    // Have to reset cursor in case it's on the splitter at the moment
    GetCursorPos(Pt);
    Pt := ScreenToClient(Pt);
    ButtonHitTest(Pt.x, Pt.y);
  end;
end;

function TZSplitter.VisibleWinButtons: integer;
var
  x: TrsWindowsButton;
begin
  Result := 0;
  for x := Low(TrsWindowsButton) to High(TrsWindowsButton) do
    if x in WindowsButtons then
      inc(Result);
end;

procedure TZSplitter.SetButtonStyle(const Value: TrsButtonStyle);
begin
  FButtonStyle := Value;
  if ShowButton then
    Invalidate;
end;

procedure TZSplitter.SetWindowsButtons(const Value: TrsWindowsButtons);
begin
  FWindowsButtons := Value;
  if (ButtonStyle = bsWindows) and ShowButton then
    Invalidate;
end;

procedure TZSplitter.DoMinimize;
begin
  if assigned(FOnMinimize) then
    FOnMinimize(Self);
end;

procedure TZSplitter.DoClose;
begin
  if Assigned(FOnClose) then
    FOnClose(Self);
end;

procedure TZSplitter.SetButtonCursor(const Value: TCursor);
begin
  FButtonCursor := Value;
end;

procedure TZSplitter.LoadOtherProperties(Reader: TReader);
begin
  RestorePos := Reader.ReadInteger;
end;


procedure TZSplitter.StoreOtherProperties(Writer: TWriter);
begin
  Writer.WriteInteger(RestorePos);
end;

procedure TZSplitter.DefineProperties(Filer: TFiler);
begin
  inherited;
  Filer.DefineProperty('RestorePos', LoadOtherProperties, StoreOtherProperties,
    Minimized or Maximized);
end;

procedure Register;
begin
  RegisterComponents('ZStandard', [TZSplitter]);
end;

end.

