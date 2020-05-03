unit dADO;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Db, ADODB, wsDB, wsADO, wsAccAndSysDB;

type
  TdmADO = class(TDataModule)
    AccADOCon: TADOConnection;
    WorkflowAccAndSysDB1: TWorkflowAccAndSysDB;
    SysADOCon: TADOConnection;
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  dmADO: TdmADO;

implementation

{$R *.DFM}

procedure TdmADO.DataModuleCreate(Sender: TObject);
var
  ExePath: string;
begin
  {Build Access connection}
  ExePath := ExtractFilePath(Application.ExeName);
  if (Length(ExePath) > 0) and (ExePath[Length(ExePath)] = '\') then
    Delete(ExePath, Length(ExePath), 1);

  {ADOConnection1.ConnectionString :=
    'Provider=SQLNCLI.1;Persist Security Info=True;User ID=sa;Initial Catalog=workflowstudio;Password=xxxxx;Data Source=xxxxxx';}

  {ADOConnection1.ConnectionString := Format(
    'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s\..\db\access\workflow.mdb',
    [ExePath]);  }
//    GetDataLinkFiles();
 AccADOCon.ConnectionString := 'Provider=SQLOLEDB.1;Password=sql2012!@#;Persist Security Info=True;User ID=sa;Initial Catalog=XE_DCDemo;Data Source=sunnyzhan-pc';
 SysADOCon.ConnectionString := 'Provider=SQLOLEDB.1;Password=sql2012!@#;Persist Security Info=True;User ID=sa;Initial Catalog=XE_System;Data Source=sunnyzhan-pc';
//  AccADOCon.ConnectionString := 'Provider=SQLOLEDB.1;Password=sql2005!@#;Persist Security Info=True;User ID=sa;Initial Catalog=SL_DEMO;Data Source=DBSer';
//  SysADOCon.ConnectionString := 'Provider=SQLOLEDB.1;Password=sql2005!@#;Persist Security Info=True;User ID=sa;Initial Catalog=SL_SYSTEM;Data Source=DBSer';
end;

end.
