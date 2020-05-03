unit ZImagePanel;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ExtCtrls,StdCtrls,Menus,TypInfo,syncobjs;

type
  TZImagePanel = class;

  TMenuWindow = class(TCustomControl)
  private
    procedure WMNCHitTest(var Message: TWMNCHitTest); message WM_NCHITTEST;
    procedure WMNCPaint(var Message: TMessage); message WM_NCPAINT;
    procedure CMTextChanged(var Message: TMessage); message CM_TEXTCHANGED;
    procedure WMEraseBkgnd(var Message: TWmEraseBkgnd); message WM_ERASEBKGND;
  protected
    ParentControl:TZImagePanel;
    PaintHeight:Integer;
    FItems:TStringList;
    FCurPos:Integer;
    TmpPos:Integer;
    FItemHeight:Integer;
    FItemWidth:Integer;
    procedure CreateParams(var Params: TCreateParams); override;
    procedure Paint; override;
  public
    procedure CaclCurPos(P:TPoint);
    constructor Create(AOwner: TComponent); override;
    procedure ActivateHint(Rect: TRect; const AHint: string); virtual;
    procedure ActivateHintData(Rect: TRect; const AHint: string; AData: Pointer); virtual;
    function CalcHintRect(MaxWidth: Integer; const AHint: string;
      AData: TStringList): TRect; virtual;
    function IsHintMsg(var Msg: TMsg): Boolean; virtual;
    procedure ReleaseHandle;
    property Caption;
    property Color;
    property Canvas;
  end;

  TPopupClick = procedure (Sender: TObject;Index:Integer) of object;
  TItemChanged = procedure (Sender: TObject;Index:Integer) of object;
  TPopupActive=procedure (Sender: TObject) of object;
  TZImagePanel = class(TGraphicControl)
  private
    { Private declarations }
    FTimer:TTimer;
    FImageList:TImageList;
    FImageIndex:Integer;
    FSelectIndex:Integer;
    FCaption:TCaption;
    FItems:TStringList;
    FMenuWindow:TMenuWindow;
    FTitle:String;
    FOnPopupClick:TPopupClick;
    FOnItemChanged:TItemChanged;
    FOnPopupActive:TPopupActive;
    FPicture: TPicture;
    FPictureSelected: TPicture;

  private
    procedure OnTimer(Sender: TObject);
    procedure SetItems(Value:TStringList);
    procedure SetPicture(Value:TPicture);
    procedure SetPictureSelected(Value:TPicture);
    procedure PictureChanged(Sender: TObject);
    procedure Progress(Sender: TObject; Stage: TProgressStage;
    PercentDone: Byte; RedrawNow: Boolean; const R: TRect; const Msg: string); dynamic;

  protected
    procedure HideHint;
    procedure SetCaption(Value:TCaption);
    Function GetCaption:TCaption;
    procedure Paint; override;
  public
    FPaintNormal:Boolean;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure WMMOUSEMOVE(var Msg:TMessage);Message WM_MOUSEMOVE;
    procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LBUTTONDOWN;
    procedure CMMouseEnter(var Message: TMessage) ;message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage) ;message CM_MOUSELeave;
    property MouseCapture;
    property Picture: TPicture  Read FPicture   Write SetPicture;
    property PictureSelected: TPicture Read FPictureSelected Write SetPictureSelected;
  published
    property Align;
    property DragCursor;
    property DragMode;
    property Enabled;
    property Caption;
    property Color;
    property Font;
    property ParentColor;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowHint;
    property Visible;
    property OnClick;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnEndDrag;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnStartDrag;
    property ImageList :TImageList Read  FImageList   Write FImageList;
    property ImageIndex:Integer    Read  FImageIndex  Write FImageIndex;
    property SelectIndex:Integer   Read  FSelectIndex Write FSelectIndex ;
    property Items:TStringList read FItems write SetItems;
    property Title:String read FTitle write FTitle;
    property OnPopupClick:TPopupClick read FOnPopupClick write FOnPopupClick;
    Function  GetItemWidth:Integer;
    Function  GetItemHeight:Integer;
    property OnItemChanged:TItemChanged read FOnItemChanged write FOnItemChanged;
    property OnPopupActive:TPopupActive read FOnPopupActive write FOnPopupActive;
  end;
procedure Register;
implementation
uses PaletteUnit;
var  isPopup:Boolean=False;
     isInImagePanel:Boolean=false;
     isInPopup:Boolean=False;
procedure TZImagePanel.SetCaption(Value:TCaption);
Begin
  FCaption:=Value;
  Invalidate;
end;

Function TZImagePanel.GetCaption:TCaption;
Begin
  Result:=FCaption;
end;
procedure TZImagePanel.SetPicture(Value:TPicture);
Begin
  FPicture.Assign(Value);
end;
procedure TZImagePanel.SetPictureSelected(Value:TPicture);
Begin
  FPictureSelected.Assign(Value);
end;


procedure TZImagePanel.Paint;
var   OldPalette:Hpalette;
begin
  OldPalette:=SelectPalette(Canvas.Handle, G_APP_Palette, False);
  RealizePalette(Canvas.Handle);
  FPicture.Bitmap.Transparent:=True;
  FPictureSelected.Bitmap.Transparent:=True;
  Canvas.Brush.Style:=bsClear;
  Canvas.Font:=Font;
  Canvas.TextOut(5,height-Font.Size-5,Caption);

  if FPaintNormal then
  Begin
    Self.Canvas.Draw(0,0,FPicture.Bitmap);
  end
  else
  Begin
    Self.Canvas.Draw(0,0,FPictureSelected.Bitmap);
  end;
  SelectPalette(Canvas.Handle, OldPalette, FAlse);
end;


constructor TZImagePanel.Create(AOwner: TComponent);
Begin
  inherited Create(AOwner);
  Height:=64;
  Width:=64;
  FPaintNormal:=True;

  SetZOrder(true);
  BringToFront;
  FItems:=TStringList.Create;
  FMenuWindow:=TMenuWindow.Create(Self);
  FMenuWindow.ParentControl:=Self;
  FPicture:=TPicture.Create;
  FPicture.OnChange := PictureChanged;
  FPicture.OnProgress := Progress;
  FPictureSelected:=TPicture.Create;
  FPictureSelected.OnChange := PictureChanged;
  FPictureSelected.OnProgress := Progress;
  FPicture.Bitmap.Mask(clWhite);
  FPictureSelected.Bitmap.Mask(clWhite);
  FPicture.Bitmap.Transparent := true;
  FPicture.Bitmap.TransParentColor :=clWhite;

  FPictureSelected.Bitmap.Transparent := true;
  FTimer:=TTimer.Create(Self);
  FTimer.Interval:=500;
  FTimer.Enabled:=False;
  FTimer.OnTimer:=OnTimer;
  FPictureSelected.Bitmap.TransParentColor :=clWhite;

end;
procedure TZImagePanel.OnTimer(Sender: TObject);
var Rect:TRect;
    p1,P2:TPoint;
Begin
  FMenuWindow.FItemWidth:=GetItemWidth;
  FMenuWindow.FItemHeight:=GetItemHeight;
  Rect:=FMenuWindow.CalcHintRect(FMenuWindow.FItemWidth,'asdf',Items);
  GetCursorPos(P1);
  P2.x:=P1.x-ClientOrigin.x;
  P2.y:=P1.y-ClientOrigin.y;
  if PtInRect(ClientRect,P2)  then
  Begin
    FMenuWindow.ActivateHint(Rect, 'asdfsad');
    MouseCapture:=True;
  end;  
  FTimer.Enabled:=False;

end;
procedure TZImagePanel.WMMOUSEMOVE(var Msg:TMessage);
var p1,P2,P3:TPoint;
//    R1,R2:TRect;
    A:Integer;
Begin
  GetCursorPos(P1);
  P2.x:=P1.x-ClientOrigin.x;
  P2.y:=P1.y-ClientOrigin.y;

  P3.x:=P1.x-FMenuWindow.ClientOrigin.x;
  P3.y:=P1.y-FMenuWindow.ClientOrigin.y;

  if PtInRect(ClientRect,P2) or PtInRect(FMenuWindow.ClientRect,P3)  then
  Begin
    if PtInRect(FMenuWindow.ClientRect,P3) then
    Begin
       A:=FMenuWindow.FCurPos;
       FMenuWindow.CaclCurPos(P3);
       if A<>FMenuWindow.FCurPos  then
       if Assigned(FOnItemChanged) then FOnItemChanged(Self,FMenuWindow.FCurPos-1);
    end;
  end else
  Begin
    MouseCapture:=False;
    FTimer.Enabled:=False;
    HideHint;
  end;
end;

procedure TZImagePanel.CMMouseLeave(var Message: TMessage);
Begin
   if  (csDesigning in ComponentState)  then  exit;
   FPaintNormal:=True;
   Repaint;
   if MouseCapture=False  then   HideHint;

end;

procedure TZImagePanel.CMMouseEnter(var Message: TMessage);
Begin
  if  (csDesigning in ComponentState)  then  exit;
  FPaintNormal:=False;
  Repaint;
  if Items.count=0 then Exit;
  FMenuWindow.FItems:=FItems;
  if MouseCapture=True  then Exit;
  if not FTimer.Enabled  then
  Begin
     Self.MouseCapture:=True;
     FTimer.Enabled:=True;
  end;


end;
procedure TZImagePanel.HideHint;
begin
  if FMenuWindow.HandleAllocated and
    IsWindowVisible(FMenuWindow.Handle) then
    ShowWindow(FMenuWindow.Handle, SW_HIDE);
end;
Function  TZImagePanel.GetItemWidth:Integer;
var I:Integer;
Begin
  Result:=0;
  for I:=0 to Items.Count-1 do
  Begin
    if Result<Canvas.TextWidth(Items[I])+30  then
    Begin
      Result:=Canvas.TextWidth(Items[I])+50;
    end;
  end;

end;

procedure TZImagePanel.PictureChanged(Sender: TObject);
Begin
end;
procedure TZImagePanel.Progress(Sender: TObject; Stage: TProgressStage;
      PercentDone: Byte; RedrawNow: Boolean; const R: TRect; const Msg: string);
Begin
end;

destructor TZImagePanel.Destroy;
begin
  FMenuWindow.Free;
  FItems.Free;
  FPicture.Free;
  FPictureSelected.Free;
  FTimer.Free;
  Inherited Destroy;
end;

procedure TZImagePanel.SetItems(Value: TStringList);
begin
  Items.Assign(Value);
end;
var   HintDoneEvent:THandle=0;
      HintHook:HHook;
      PopupControl:TControl;
      HintThreadID: Integer;
      HintThread: THandle;
procedure TZImagePanel.WMLButtonDown(var Message: TWMLButtonDown);
var p1,P3:TPoint;
Begin
  if Items.Count =0 then
  Begin
    inherited;
    Exit;
  end;
  P1.x:=Message.Pos.x;
  P1.y:=Message.Pos.y;
  P1:=ClientToScreen(P1);
  P3.x:=P1.X-FMenuWindow.ClientOrigin.x;
  P3.y:=P1.Y-FMenuWindow.ClientOrigin.y;
  FMenuWindow.CaclCurPos(P3);
  if PtInRect(FMenuWindow.ClientRect,P3) then
  Begin
    HideHint;
    if Assigned(FOnPopupClick) then FOnPopupClick(Self,FMenuWindow.FCurPos-1);
    Exit;
  end else
  Begin
    if (Message.Pos.x>=0) and (Message.Pos.y>=0) and (Message.Pos.x<=Width) and (Message.Pos.y<=Height)  then
    Begin
      FTimer.Enabled:=False;
//      HideHint;
      MouseCapture:=False;
      CMMouseEnter(TMessage(Message));
    end else
    Begin
      HideHint;
    end;
  end;
  inherited;
end;

//鼠标移动，光标追踪
Function  TZImagePanel.GetItemHeight:Integer;
Begin
  Result:=20;
end;

function IsHintMsg(var Msg: TMsg): Boolean;
begin
  with Msg do
    Result := ((Message = CM_ACTIVATE) or (Message = CM_DEACTIVATE)) or
      (Message = CM_APPKEYDOWN) or (Message = CM_APPSYSCOMMAND) or
      (Message = WM_COMMAND);
end;

function HintGetMsgHook(nCode: Integer; wParam: Longint; var Msg: TMsg): Longint; stdcall;
begin
  Result := CallNextHookEx(HintHook, nCode, wParam, Longint(@Msg));
  if IsHintMsg(Msg)  then
  Begin
  end;
end;

procedure HintMouseThread(Param: Integer); stdcall;
var
  P: TPoint;
  C:Tcontrol;
begin
  HintThreadID := GetCurrentThreadID;
  while WaitForSingleObject(HintDoneEvent, 100) = WAIT_TIMEOUT do
  begin
    GetCursorPos(P);
    C:=FindDragTarget(P,True);
    if C=PopupControl then
    Begin
    end else
    Begin

    end;
  end;
end;
procedure HookHintHooks;
begin
  if HintHook = 0 then
    HintHook := SetWindowsHookEx(WH_GETMESSAGE, @HintGetMsgHook, 0, GetCurrentThreadID);
  if HintDoneEvent = 0 then
    HintDoneEvent := CreateEvent(nil, False, False, nil);
end;

procedure UnhookHintHooks;
begin

  if HintHook <> 0 then UnhookWindowsHookEx(HintHook);
  HintHook := 0;
  if HintThread <> 0 then
  begin
    SetEvent(HintDoneEvent);
    if GetCurrentThreadId <> HintThreadID then
      WaitForSingleObject(HintThread, INFINITE);
    HintThread := 0;
  end;
end;
{ THintWindow }

constructor TMenuWindow.Create(AOwner: TComponent);
var
  NonClientMetrics: TNonClientMetrics;
begin
  inherited Create(AOwner);
  Color := $80FFFF or $02000000;

  NonClientMetrics.cbSize := sizeof(NonClientMetrics);
  if SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, @NonClientMetrics, 0) then
    Canvas.Font.Handle := CreateFontIndirect(NonClientMetrics.lfStatusFont)
  else
    Canvas.Font.Size := 8;
  Canvas.Brush.Style := bsClear;
end;

procedure TMenuWindow.CreateParams(var Params: TCreateParams);
begin
  inherited CreateParams(Params);
  with Params do
  begin
    Style := WS_POPUP or WS_BORDER;
    WindowClass.Style := WindowClass.Style or CS_SAVEBITS;
    if NewStyleControls then ExStyle := WS_EX_TOOLWINDOW;
  end;
end;

procedure TMenuWindow.WMNCHitTest(var Message: TWMNCHitTest);
begin
  Message.Result := HTTRANSPARENT;
end;

procedure TMenuWindow.WMNCPaint(var Message: TMessage);
var
  R: TRect;
begin
  Exit;
  Canvas.Handle := GetWindowDC(Handle);
  with Canvas do
  try
    R := Rect(0, 0, Width, Height);
    DrawEdge(Handle, R, BDR_RAISEDOUTER, BF_RECT);
  finally
    Canvas.Handle := 0;
  end;
end;

procedure TMenuWindow.Paint;
  procedure DrawRect(R:TRect;I:Integer);
  begin
    Dec(R.Right);
    Dec(R.Right);
    Canvas.Pen.Color:=clBlack;
    if I<>FItems.Count-1 then Canvas.Pen.Color:=PaletteRGB(176,200,192) or $02000000;

    Canvas.MoveTo(R.Right,R.Bottom-1);

    Canvas.LineTo(R.Left-1,R.Bottom-1);

    Canvas.Pen.Color:=clBlack;
    Canvas.LineTo(R.Left-1,R.Top-1);
    Canvas.MoveTo(R.Right,R.Top);
    Canvas.LineTo(R.Right,R.Bottom);

    if I=0 then
    begin
      Canvas.MoveTo(R.Left-1,R.Top);
      Canvas.LineTo(R.Right+1,R.Top);
      Canvas.Pen.color:=RGB(143,151,96) or $02000000;
      Canvas.MoveTo(R.Left,R.Bottom-2);
      Canvas.LineTo(R.Left,R.Top+1);
      Canvas.LineTo(R.Right-1,R.Top+1);
    end;
  end;
var
  R:TRect;
  MidPos,I:Integer;
  Point:array[1..3]of TPoint;
begin
    SelectPalette(Canvas.Handle, G_APP_Palette, False);
    RealizePalette(Canvas.Handle);
    R.Left:=1; R.Right :=Width-1;
    I:=0;
    //FItems.Count-1;
    while I<=FItems.Count-1 do
    begin
      R.Top:=I*(FItemHeight)+PaintHeight;
      R.Bottom:=R.Top+FItemHeight+PaintHeight;
    //标题
      if (I=0) then
      begin
        Canvas.Brush.Color:=5270632 or $02000000;
        Canvas.Font.Color:=12645624 or $02000000;
        Canvas.Font.style:=[fsBold];
        MidPos:=(Width-(Canvas.TextWidth(FItems.Strings[0])))div 2;
        Canvas.TextRect(R,R.Left+MidPos,R.Top+4,FItems.Strings[I]);
        Canvas.Font.Style:=[];
      end;

      if (I<>0) and (I<>FCurPos-1) then
      Begin
        Canvas.TextRect(R,R.Left+20,R.Top+4,FItems.Strings[I]);
      end;

      if (I<>0) and (I=FCurPos-1) then
      begin
        Canvas.Brush.Color:=10513448 or $02000000;
        Canvas.Font.Color:=clwhite;
        Canvas.TextRect(R,R.Left+20,R.Top+4,FItems.Strings[FCurPos-1]);
        Canvas.Brush.Style:=bsSolid;
        Canvas.Brush.Color:=clred;
        Canvas.Pen.Color:=clBlack;
        Point[1].x:=R.Left+6;Point[1].y:=R.Top+4;
        Point[2].x:=R.Left+12;Point[2].y:=R.Top+10;
        Point[3].x:=R.Left+6;Point[3].y:=R.Top+16;
        Canvas.Polygon(Point);
      end;


      DrawRect(R,I);
      Canvas.Brush.Color:=clwhite;
      Canvas.Font.Color:=clblack;
      I:=I+1;
   end;
end;

function TMenuWindow.IsHintMsg(var Msg: TMsg): Boolean;
begin
  with Msg do
    Result := ((Message >= WM_KEYFIRST) and (Message <= WM_KEYLAST)) or
      ((Message = CM_ACTIVATE) or (Message = CM_DEACTIVATE)) or
      (Message = CM_APPKEYDOWN) or (Message = CM_APPSYSCOMMAND) or
      (Message = WM_COMMAND) or ((Message > WM_MOUSEMOVE) and
      (Message <= WM_MOUSELAST)) or (Message = WM_NCMOUSEMOVE);
end;

procedure TMenuWindow.ReleaseHandle;
begin
  DestroyHandle;
end;

procedure TMenuWindow.CMTextChanged(var Message: TMessage);
begin
  inherited;
  Width := Canvas.TextWidth(Caption) + 6;
  Height := Canvas.TextHeight(Caption) + 4;
end;

procedure TMenuWindow.ActivateHint(Rect: TRect; const AHint: string);
var I:Integer;
    R:TRect;
begin
  if Assigned(ParentControl.FOnPopupActive) then ParentControl.FOnPopupActive(ParentControl);
  FCurPos:=0;
  Caption := AHint;
  Rect.Bottom:=Rect.Bottom+2;
  BoundsRect := Rect;
  R:=Rect;
  if Rect.Top + Height > Screen.Height then
    Rect.Top := Screen.Height - Height;
  if Rect.Left + Width > Screen.Width then
    Rect.Left := Screen.Width - Width;
  if Rect.Left < 0 then Rect.Left := 0;
  if Rect.Bottom < 0 then Rect.Bottom := 0;
  SetWindowPos(Handle, HWND_TOPMOST, Rect.Left, Rect.Top, 0,
      0, SWP_SHOWWINDOW or SWP_NOACTIVATE or SWP_NOSIZE);
  I:=0;
  while I<=Height  do
  Begin
    PaintHeight:=Height-I;
    Self.Repaint;
    Sleep(4);
//    I:=I+1;
    I:=I+FItemHeight;
  end ;
  PaintHeight:=0;
  Repaint;
end;

procedure TMenuWindow.ActivateHintData(Rect: TRect; const AHint: string; AData: Pointer);
begin
  ActivateHint(Rect, AHint);
end;
procedure TMenuWindow.WMEraseBkgnd(var Message: TWmEraseBkgnd);
Begin
  Message.Result:=1;
end;
function TMenuWindow.CalcHintRect(MaxWidth: Integer; const AHint: string; AData: TStringList): TRect;
begin
  Result.Left:=ParentControl.ClientOrigin.x;
  Result.Top:=ParentControl.ClientOrigin.Y-FItemHeight*AData.Count;;

  Result.Right:=ParentControl.ClientOrigin.x+FItemWidth;
  Result.Bottom:=ParentControl.ClientOrigin.Y;
end;

procedure TMenuWindow.CaclCurPos(P:TPoint);
var a:Integer;
Begin
  if FItemHeight=0 then Exit; 
  A:=(P.y  div FItemHeight)+1;
  if A<>FCurPos then
  Begin
    FCurPos:=A;
    RePaint;
  end;
end;
procedure Register;
begin
  RegisterComponents('ZStandard', [TZImagePanel]);
end;
end.
