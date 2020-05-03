unit DiagramShadow;

{$I Diagram.INC}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  {$IFDEF DELPHI6_LVL}Variants,{$ENDIF}
  Dialogs, ExtCtrls, StdCtrls, ComCtrls, atDiagram;

type
  TShadowEditor = class(TForm)
    UpDown1: TUpDown;
    UpDown2: TUpDown;
    PaintBox1: TPaintBox;
    Label1: TLabel;
    Panel1: TPanel;
    ColorDialog1: TColorDialog;
    Button1: TButton;
    Button2: TButton;
    PaintBox2: TPaintBox;
    procedure Panel1Click(Sender: TObject);
    procedure UpDown1ChangingEx(Sender: TObject; var AllowChange: Boolean;
      NewValue: Smallint; Direction: TUpDownDirection);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure UpDown2ChangingEx(Sender: TObject; var AllowChange: Boolean;
      NewValue: Smallint; Direction: TUpDownDirection);
    procedure PaintBox1Paint(Sender: TObject);
    procedure PaintBox2Paint(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    Shad: TBlockShadow;
    function EditShadow(AShadow: TBlockShadow): Boolean;
  end;

var
  ShadowEditor: TShadowEditor;

implementation

{$R *.dfm}

function TShadowEditor.EditShadow(AShadow: TBlockShadow): Boolean;
begin
  Result := False;
  shad.Assign(AShadow);
  UpDown1.Position := shad.VOffset;
  UpDown2.Position := shad.HOffset;
  if shad.Visible then
    panel1.Color := shad.Color
  else
    panel1.Color := clGray;

  if (ShowModal = mrOk) then
  begin
    AShadow.Assign(shad);
    Result := true;
  end;
end;

procedure TShadowEditor.Panel1Click(Sender: TObject);
begin
  ColorDialog1.Color := Panel1.Color;

  if Colordialog1.Execute then
  begin
    panel1.Color := ColorDialog1.Color;
    shad.Color := ColorDialog1.Color;
    PaintBox1.Invalidate;
  end;
end;

procedure TShadowEditor.UpDown1ChangingEx(Sender: TObject;
  var AllowChange: Boolean; NewValue: Smallint;
  Direction: TUpDownDirection);
begin
  shad.VOffset := NewValue;
  PaintBox1.Invalidate;
end;

procedure TShadowEditor.FormCreate(Sender: TObject);
begin
  shad := TBlockShadow.Create(nil);
end;

procedure TShadowEditor.FormDestroy(Sender: TObject);
begin
  shad.Free;
end;

procedure TShadowEditor.UpDown2ChangingEx(Sender: TObject;
  var AllowChange: Boolean; NewValue: Smallint;
  Direction: TUpDownDirection);
begin
  shad.HOffset := NewValue;
  PaintBox1.Invalidate;
end;

procedure TShadowEditor.PaintBox1Paint(Sender: TObject);
var
  r: Trect;
begin
  with PaintBox1.Canvas do
  begin
    Pen.Color := clSilver;
    Pen.Width := 1;
    Brush.Style := bsClear;
    r := PaintBox1.ClientRect;
    InflateRect(r,-1,-1);
    Rectangle(r.Left,r.Top,r.Right, r.Bottom);

    inflaterect(r,-15,-15);

    Brush.Color := shad.Color;
    Pen.Color := shad.Color;

    OffsetRect(r,shad.HOffset, shad.VOffset);
    Rectangle(r.Left,r.Top,r.Right, r.Bottom);


    OffsetRect(r,-shad.HOffset, -shad.VOffset);

    Pen.Color := clSilver;
    Brush.Color := clWhite;
    Rectangle(r.Left,r.Top,r.Right, r.Bottom);
  end;
end;

procedure TShadowEditor.PaintBox2Paint(Sender: TObject);
begin
  paintbox2.Canvas.Brush.Color := panel1.Color;
  paintbox2.Canvas.Pen.Color := panel1.Color;
  PaintBox2.Canvas.FillRect(paintbox2.clientrect);

end;

end.
