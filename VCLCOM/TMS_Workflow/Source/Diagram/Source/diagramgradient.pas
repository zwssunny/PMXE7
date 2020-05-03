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
unit DiagramGradient;

{$I Diagram.Inc}

interface

uses
  Windows, Messages, SysUtils, {$IFDEF DELPHI6_LVL}Variants, {$ENDIF}Classes, Graphics, Controls, Forms,
  Dialogs, atDiagram, StdCtrls, ExtCtrls;                            

type
  TGradientEditor = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Panel1: TPanel;
    Panel2: TPanel;
    PaintBox1: TPaintBox;
    Label3: TLabel;
    Label4: TLabel;
    ComboBox1: TComboBox;
    Button1: TButton;
    Button2: TButton;
    ColorDialog1: TColorDialog;
    PaintBox2: TPaintBox;
    PaintBox3: TPaintBox;
    procedure Panel1Click(Sender: TObject);
    procedure Panel2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure PaintBox1Paint(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure PaintBox2Paint(Sender: TObject);
    procedure PaintBox3Paint(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    grad: TDiagramGradient;
    function EditGradient(AGradient: TDiagramGradient): boolean;
  end;

var
  GradientEditor: TGradientEditor;

implementation
uses
  DiagramUtils;

{$R *.dfm}

procedure TGradientEditor.Panel1Click(Sender: TObject);
begin
  ColorDialog1.Color := Panel1.Color;
  if ColorDialog1.Execute then
  begin
    Panel1.Color := ColorDialog1.Color;
    grad.StartColor := ColorDialog1.Color;
    PaintBox1.Invalidate;
  end;
end;

procedure TGradientEditor.Panel2Click(Sender: TObject);
begin
  ColorDialog1.Color := Panel2.Color;
  if ColorDialog1.Execute then
  begin
    Panel2.Color := ColorDialog1.Color;
    grad.EndColor := ColorDialog1.Color;
    PaintBox1.Invalidate;
  end;
end;

procedure TGradientEditor.FormCreate(Sender: TObject);
begin
  grad := TDiagramGradient.Create(nil);
end;

procedure TGradientEditor.FormDestroy(Sender: TObject);
begin
  grad.Free;
end;

procedure TGradientEditor.PaintBox1Paint(Sender: TObject);
begin
  grad.DrawGradient(PaintBox1.Canvas, Square(PaintBox1.ClientRect), 0);
end;

procedure TGradientEditor.ComboBox1Change(Sender: TObject);
begin
  grad.Direction := TGradientDirection(ComboBox1.ItemIndex);
  PaintBox1.Invalidate;
end;

function TGradientEditor.EditGradient(AGradient: TDiagramGradient): Boolean;
begin
  Result := False;
  grad.Assign(AGradient);
  ComboBox1.ItemIndex := integer(grad.Direction);
  Panel1.Color := grad.StartColor;
  Panel2.Color := grad.EndColor;
  if ShowModal = mrOK then
  begin
    AGradient.Assign(grad);
    Result := True;    
  end;
end;

procedure TGradientEditor.PaintBox2Paint(Sender: TObject);
begin
  paintbox2.Canvas.Brush.Color := panel1.Color;
  paintbox2.Canvas.Pen.Color := panel1.Color;
  PaintBox2.Canvas.FillRect(paintbox2.clientrect);

end;

procedure TGradientEditor.PaintBox3Paint(Sender: TObject);
begin
  paintbox3.Canvas.Brush.Color := panel2.Color;
  paintbox3.Canvas.Pen.Color := panel2.Color;
  PaintBox3.Canvas.FillRect(paintbox3.clientrect);

end;

end.
