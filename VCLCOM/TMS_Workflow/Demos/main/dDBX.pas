unit dDBX;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB, wsDB, wsDBX, SqlExpr;

type
  TdmDBX = class(TDataModule)
    WorkflowDBXDB1: TWorkflowDBXDB;
    SQLConnection1: TSQLConnection;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmDBX: TdmDBX;

implementation

{$R *.DFM}

end.
