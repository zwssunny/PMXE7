{***************************************************************************}
{ Scripter Studio Components for Delphi & C++Builder                        }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright ?1997 - 2011                                        }
{            Email : info@tmssoftware.com                                   }
{            Web : http://www.tmssoftware.com                               }
{                                                                           }
{ For information about version history, check the section "What's New"     }
{ at Scripter Studio manual.                                                }                                                                         
{                                                                           }
{ The source code is given as is. The author is not responsible             }
{ for any possible damage done due to the use of this code.                 }
{ The component can be freely used in any application. The complete         }
{ source code remains property of the author and may not be distributed,    }
{ published, given or sold in any form as such. No parts of the source      }
{ code can be included in any other component or application without        }
{ written authorization of the author.                                      }
{***************************************************************************}

unit uSystemLibrary;

{$I ASCRIPT.INC}

interface
uses
  Windows, SysUtils, Classes, TypInfo, atScript
  {$IFDEF DELPHI6_LVL}
  , Variants
  {$ENDIF}
  ;

type
  TatSystemLibrary = class(TatScripterLibrary)
  private
    {System procedures}
    procedure VarIsNullProc(AMachine:TatVirtualMachine);
    procedure RoundProc(AMachine:TatVirtualMachine);
    procedure TruncProc(AMachine:TatVirtualMachine);
    procedure CopyProc(AMachine:TatVirtualMachine);
    procedure DeleteProc(AMachine:TatVirtualMachine);
    procedure InsertProc(AMachine:TatVirtualMachine);
    procedure PosProc(AMachine:TatVirtualMachine);
    procedure LengthProc(AMachine:TatVirtualMachine);
    procedure IncProc(AMachine:TatVirtualMachine);
    procedure DecProc(AMachine:TatVirtualMachine);
    {SysUtils procedures}
    procedure UpperCaseProc(AMachine:TatVirtualMachine);
    procedure LowerCaseProc(AMachine:TatVirtualMachine);
    procedure CompareStrProc(AMachine:TatVirtualMachine);
    procedure CompareTextProc(AMachine:TatVirtualMachine);
    procedure AnsiUpperCaseProc(AMachine:TatVirtualMachine);
    procedure AnsiLowerCaseProc(AMachine:TatVirtualMachine);
    procedure AnsiCompareStrProc(AMachine:TatVirtualMachine);
    procedure AnsiCompareTextProc(AMachine:TatVirtualMachine);
    procedure TrimProc(AMachine:TatVirtualMachine);
    procedure TrimLeftProc(AMachine:TatVirtualMachine);
    procedure TrimRightProc(AMachine:TatVirtualMachine);
    procedure IsValidIdentProc(AMachine:TatVirtualMachine);
    procedure IntToStrProc(AMachine:TatVirtualMachine);
    procedure IntToHexProc(AMachine:TatVirtualMachine);
    procedure StrToIntProc(AMachine:TatVirtualMachine);
    procedure StrToIntDefProc(AMachine:TatVirtualMachine);
    procedure FloatToStrProc(AMachine:TatVirtualMachine);
    procedure FormatFloatProc(AMachine:TatVirtualMachine);
    procedure StrToFloatProc(AMachine:TatVirtualMachine);
    procedure EncodeDateProc(AMachine:TatVirtualMachine);
    procedure EncodeTimeProc(AMachine:TatVirtualMachine);
    procedure DecodeDateProc(AMachine:TatVirtualMachine);
    procedure DecodeTimeProc(AMachine:TatVirtualMachine);
    procedure DayOfWeekProc(AMachine:TatVirtualMachine);
    procedure DateProc(AMachine:TatVirtualMachine);
    procedure TimeProc(AMachine:TatVirtualMachine);
    procedure NowProc(AMachine:TatVirtualMachine);
    procedure IncMonthProc(AMachine:TatVirtualMachine);
    procedure IsLeapYearProc(AMachine:TatVirtualMachine);
    procedure DateToStrProc(AMachine:TatVirtualMachine);
    procedure TimeToStrProc(AMachine:TatVirtualMachine);
    procedure DateTimeToStrProc(AMachine:TatVirtualMachine);
    procedure StrToDateProc(AMachine:TatVirtualMachine);
    procedure StrToTimeProc(AMachine:TatVirtualMachine);
    procedure StrToDateTimeProc(AMachine:TatVirtualMachine);
    procedure FormatDateTimeProc(AMachine:TatVirtualMachine);
    procedure BeepProc(AMachine:TatVirtualMachine);
    procedure FormatProc(AMachine:TatVirtualMachine);
    procedure RandomProc(AMachine:TatVirtualMachine);
    procedure MachineProc(AMachine:TatVirtualMachine);
    procedure ScripterProc(AMachine:TatVirtualMachine);
    {Dialogs procedures}
    procedure ShowMessageProc(AMachine:TatVirtualMachine);
    procedure InputQueryProc(AMachine:TatVirtualMachine);
    {Exception handling generic procedures}
    procedure RaiseProc(AMachine:TatVirtualMachine);
    {COM procedures}
    procedure CreateOleObjectProc(AMachine:TatVirtualMachine);
    procedure GetActiveOleObjectProc(AMachine:TatVirtualMachine);
    {Variant procedures}
    procedure VarToStrProc(AMachine:TatVirtualMachine);
    procedure HighProc(AMachine:TatVirtualMachine);
    procedure LowProc(AMachine:TatVirtualMachine);
    procedure VarArrayHighBoundProc(AMachine:TatVirtualMachine);
    procedure VarArrayLowBoundProc(AMachine:TatVirtualMachine);
    procedure VarArrayCreateProc(AMachine:TatVirtualMachine);
    {Exception handling properties}
    procedure GetLastExceptionMessageProc(AMachine:TatVirtualMachine);
    procedure GetLastExceptionHelpContextProc(AMachine:TatVirtualMachine);
    procedure GetLastExceptionClassNameProc(AMachine:TatVirtualMachine);
    {TObject methods}
    procedure TObjectCreateProc(AMachine:TatVirtualMachine);
    procedure TObjectFreeProc(AMachine:TatVirtualMachine);
    procedure AssignedProc(AMachine: TatVirtualMachine);
    procedure InterpretProc(AMachine: TatVirtualMachine);
    procedure SetOfProc(AMachine: TatVirtualMachine);
    procedure CosProc(AMachine: TatVirtualMachine);
    procedure SinProc(AMachine: TatVirtualMachine);
    procedure AbsProc(AMachine: TatVirtualMachine);
    procedure ArctanProc(AMachine: TatVirtualMachine);
    procedure ChDirProc(AMachine: TatVirtualMachine);
    procedure ChrProc(AMachine: TatVirtualMachine);
    procedure ExpProc(AMachine: TatVirtualMachine);
    procedure FracProc(AMachine: TatVirtualMachine);
    procedure IntProc(AMachine: TatVirtualMachine);
    procedure LnProc(AMachine: TatVirtualMachine);
    procedure OddProc(AMachine: TatVirtualMachine);
    procedure OrdProc(AMachine: TatVirtualMachine);
    procedure SqrProc(AMachine: TatVirtualMachine);
    procedure SqrtProc(AMachine: TatVirtualMachine);

    procedure __AssignFile(AMachine: TatVirtualMachine);
    procedure __Reset(AMachine: TatVirtualMachine);
    procedure __Rewrite(AMachine: TatVirtualMachine);
    procedure __Append(AMachine: TatVirtualMachine);
    procedure __CloseFile(AMachine: TatVirtualMachine);
    procedure __Write(AMachine: TatVirtualMachine);
    procedure __WriteLn(AMachine: TatVirtualMachine);
    procedure __ReadLn(AMachine: TatVirtualMachine);
    procedure __EOF(AMachine: TatVirtualMachine);
    procedure __FilePos(AMachine: TatVirtualMachine);
    procedure __FileSize(AMachine: TatVirtualMachine);
  public
    class function LibraryName: string; override;
    procedure Init; override;
  end;

implementation
uses
  {$IFNDEF LINUX}
  Dialogs, ComObj;
  {$ELSE}
  QDialogs;
  {$ENDIF}

type
  TFileClass = class(TObject)
  public
    FTextFile : TextFile;
    constructor Create(AFileName : string);
    destructor  Destroy; override;
  end;

{TatSystemLibrary}

class function TatSystemLibrary.LibraryName: string;
begin
  result := 'Internal';
end;

procedure TatSystemLibrary.Init;
begin
  { torna a SystemLibrary  a primeira instância padrão e declara seus métodos e propriedades }
  with Scripter.DefineClass(ClassType) do // myself
  begin
     { methods }
     DefineMethod( 'UpperCase',           1, tkString,  nil, UpperCaseProc,         false, 0, 'S: string' ) ;
     DefineMethod( 'LowerCase',           1, tkString,  nil, LowerCaseProc,         false, 0, 'S: string' );
     DefineMethod( 'CompareStr',          2, tkInteger, nil, CompareStrProc,        false, 0, 'S1:string;S2:string' );
     DefineMethod( 'CompareText',         2, tkInteger, nil, CompareTextProc,       false, 0, 'S1:string;S2:string' );
     DefineMethod( 'AnsiUpperCase',       1, tkString,  nil, AnsiUpperCaseProc,     false, 0, 'S: string' ) ;
     DefineMethod( 'AnsiLowerCase',       1, tkString,  nil, AnsiLowerCaseProc,     false, 0, 'S: string' ) ;
     DefineMethod( 'AnsiCompareStr',      2, tkString,  nil, AnsiCompareStrProc,    false, 0, 'S1:string;S2:string' );
     DefineMethod( 'AnsiCompareText',     2, tkString,  nil, AnsiCompareTextProc,   false, 0, 'S1:string;S2:string' );
     DefineMethod( 'Trim',                1, tkString,  nil, TrimProc,              false, 0, 'S: string' ) ;
     DefineMethod( 'TrimLeft',            1, tkString,  nil, TrimLeftProc,          false, 0, 'S: string' ) ;
     DefineMethod( 'TrimRight',           1, tkString,  nil, TrimRightProc,         false, 0, 'S: string' ) ;
     DefineMethod( 'IsValidIdent',        1, tkInteger, nil, IsValidIdentProc,      false, 0, 'Ident: string' ) ;
     DefineMethod( 'IntToStr',            1, tkString,  nil, IntToStrProc,          false, 0, 'Value: integer' );
     DefineMethod( 'IntToHex',            2, tkString,  nil, IntToHexProc,          false, 0, 'Value: integer; Digits: integer' );
     DefineMethod( 'StrToInt',            1, tkInteger, nil, StrToIntProc,          false, 0, 'S: string' );
     DefineMethod( 'StrToIntDef',         2, tkInteger, nil, StrToIntDefProc,       false, 0, 'S: string; Default: integer' );
     DefineMethod( 'FloatToStr',          1, tkString,  nil, FloatToStrProc,        false, 0, 'Value: extended' );
     DefineMethod( 'Format',              2, tkString,  nil, FormatProc,            false, 0, 'Format: string; Args: VariantArray' );
     DefineMethod( 'FormatFloat',         2, tkString,  nil, FormatFloatProc,       false, 0, 'Format: string; Value: extended' );
     DefineMethod( 'StrToFloat',          1, tkFloat,   nil, StrToFloatProc,        false, 0, 'S: string' );
     DefineMethod( 'EncodeDate',          3, tkFloat,   nil, EncodeDateProc,        false, 0, 'Year: Word; Month: Word; Day: Word' );
     DefineMethod( 'EncodeTime',          4, tkFloat,   nil, EncodeTimeProc,        false, 0, 'Hour: Word; Min: Word; Sec: Word; MSec: Word' );
     DefineMethod( 'DecodeDate',          4, tkInteger, nil, DecodeDateProc,        false, 0, 'DateTime: TDateTime; Year: Word; Month: Word; Day: Word' ).SetVarArgs([1,2,3]);
     DefineMethod( 'DecodeTime',          5, tkInteger, nil, DecodeTimeProc,        false, 0, 'DateTime: TDateTime; Hour: Word; Min: Word; Sec: Word; MSec: Word' ).SetVarArgs([1,2,3,4]);
     DefineMethod( 'DayOfWeek',           1, tkInteger, nil, DayOfWeekProc,         false, 0, 'Datetime: TDateTime' );
     DefineMethod( 'Date',                0, tkFloat,   nil, DateProc );
     DefineMethod( 'Time',                0, tkFloat,   nil, TimeProc );
     DefineMethod( 'Now',                 0, tkFloat,   nil, NowProc );
     DefineMethod( 'IncMonth',            2, tkFloat,   nil, IncMonthProc,          false, 0, 'DateTime: TDateTime; NumberOfMonths: integer' );
     DefineMethod( 'IsLeapYear',          1, tkInteger, nil, IsLeapYearProc,        false, 0, 'Year: Word' );
     DefineMethod( 'DateToStr',           1, tkString,  nil, DateToStrProc,         false, 0, 'DateTime: TDateTime' );
     DefineMethod( 'TimeToStr',           1, tkString,  nil, TimeToStrProc,         false, 0, 'DateTime: TDateTime' );
     DefineMethod( 'DateTimeToStr',       1, tkString,  nil, DateTimeToStrProc,     false, 0, 'DateTime: TDateTime' );
     DefineMethod( 'StrToDate',           1, tkFloat,   nil, StrToDateProc,         false, 0, 'S: string' );
     DefineMethod( 'StrToTime',           1, tkFloat,   nil, StrToTimeProc,         false, 0, 'S: string' );
     DefineMethod( 'StrToDateTime',       1, tkFloat,   nil, StrToDateTimeProc,     false, 0, 'S: string' );
     DefineMethod( 'FormatDateTime',      2, tkFloat,   nil, FormatDateTimeProc,    false, 0, 'Format: string; DateTime: TDateTime' );
     DefineMethod( 'Beep',                0, tkNone,    nil, BeepProc );
     DefineMethod( 'VarIsNull',           1, tkInteger, nil, VarIsNullProc,         false, 0, 'V: Variant' );
     DefineMethod( 'Round',               1, tkInteger, nil, RoundProc,             false, 0, 'X: Real' );
     DefineMethod( 'Trunc',               1, tkInteger, nil, TruncProc,             false, 0, 'X: Real' );
     DefineMethod( 'Copy',                3, tkString,  nil, CopyProc,              false, 0, 'S: string; Index: integer; Count: integer' );
     DefineMethod( 'Delete',              3, tkString,  nil, DeleteProc,            false, 0, 'S: string; Index: integer; Count: integer' ).SetVarArgs([0]);
     DefineMethod( 'Insert',              3, tkString,  nil, InsertProc,            false, 0, 'SubStr: string; Dest: string; Index: integer' ).SetVarArgs([1]);
     DefineMethod( 'Pos',                 2, tkInteger, nil, PosProc,               false, 0, 'SubStr: string; Str: string'  );
     DefineMethod( 'Length',              1, tkInteger, nil, LengthProc,            false, 0, 'S: string' );
     DefineMethod( 'ShowMessage',         1, tkString,  nil, ShowMessageProc,       false, 0, 'Msg: string' );
     DefineMethod( 'InputQuery',          3, tkString,  nil, InputQueryProc,        false, 0, 'ACaption: string; APrompt: string; Value: string' ).SetVarArgs([2]);
     DefineMethod( 'Raise',               1, tkNone,    nil, RaiseProc,             false, 0, 'ExceptionMsg: string' );
     DefineMethod( 'CreateOleObject',     1, tkVariant, nil, CreateOleObjectProc,   false, 0, 'ClassName: string' );
     DefineMethod( 'GetActiveOleObject',  1, tkVariant, nil, GetActiveOleObjectProc,false, 0, 'ClassName: string' );
     DefineMethod( 'VarToStr',            1, tkString,  nil, VarToStrProc,          false, 0, 'V: Variant' );
     DefineMethod( 'Dec',                 1, tkInteger, nil, DecProc,               false, 0, 'X: Ordinal' ).SetVarArgs([0]);
     DefineMethod( 'Inc',                 1, tkInteger, nil, IncProc,               false, 0, 'X: Ordinal' ).SetVarArgs([0]);
     DefineMethod( 'High',                1, tkInteger, nil, HighProc,              false, 0, 'X: VariantArray' );
     DefineMethod( 'Low',                 1, tkInteger, nil, LowProc,               false, 0, 'X: VariantArray' );
     DefineMethod( 'VarArrayHighBound',   2, tkInteger, nil, VarArrayHighBoundProc, false, 0, 'A: variant; Dim: integer' );
     DefineMethod( 'VarArrayLowBound',    2, tkInteger, nil, VarArrayLowBoundProc,  false, 0, 'A: variant; Dim: integer' );
     DefineMethod( 'VarArrayCreate',      2, tkVariant, nil, VarArrayCreateProc,    false, 0, 'Bounds: VariantArray; AVarType: integer' );
     DefineMethod( 'Random',              0, tkFloat,   nil, RandomProc );
     DefineMethod( 'Machine',             0, tkClass,   nil, MachineProc );
     DefineMethod( 'Scripter',            0, tkClass,   nil, ScripterProc );
     DefineMethod( 'Assigned',            1, tkInteger, nil, AssignedProc,          false, 0, 'P: Variant' );
     DefineMethod( 'Interpret',           1, tkNone,    nil, InterpretProc,         false, 0, 'ScriptCode: string' );
     DefineMethod( 'SetOf',               1, tkSet,     nil, SetOfProc,             false, 0, 'Values: VariantArray' );
     DefineMethod( 'Sin',                 1, tkFloat,   nil, SinProc,               false, 0, 'X: extended' );
     DefineMethod( 'Cos',                 1, tkFloat,   nil, CosProc,               false, 0, 'X: extended' );
     DefineMethod( 'Abs',                 1, tkFloat,   nil, AbsProc,               false, 0, 'X: Real' );
     DefineMethod( 'ArcTan',              1, tkFloat,   nil, ArcTanProc,            false, 0, 'X: extended' );
     DefineMethod( 'Chdir',               1, tkNone,    nil, ChDirProc,             false, 0, 'S: string' );
     DefineMethod( 'Chr',                 1, tkString,  nil, ChrProc,               false, 0, 'X: Byte' );
     DefineMethod( 'Exp',                 1, tkFloat,   nil, ExpProc,               false, 0, 'X: extended' );
     DefineMethod( 'Frac',                1, tkFloat,   nil, FracProc,              false, 0, 'X: extended' );
     DefineMethod( 'Int',                 1, tkInteger, nil, IntProc,               false, 0, 'X: extended' );
     DefineMethod( 'Ln',                  1, tkFloat,   nil, LnProc,                false, 0, 'X: extended' );
     DefineMethod( 'Odd',                 1, tkEnumeration, nil, OddProc,           false, 0, 'X: integer' );
     DefineMethod( 'Ord',                 1, tkInteger, nil, OrdProc,               false, 0, 'X: Ordinal' );
     DefineMethod( 'Sqr',                 1, tkFloat,   nil, SqrProc,               false, 0, 'X: Real' );
     DefineMethod( 'Sqrt',                1, tkFloat,   nil, SqrtProc,              false, 0, 'X: extended' );

     DefineMethod('AssignFile',           2, tkClass,   TFileClass,__AssignFile,    false, 0, 'F: File; FileName: string').SetVarArgs([0]);
     DefineMethod('Reset',                1, tkNone,    nil, __Reset,               false, 0, 'F: File' );
     DefineMethod('Rewrite',              1, tkNone,    nil, __Rewrite,             false, 0, 'F: File' );
     DefineMethod('Append',               1, tkNone,    nil, __Append,              false, 0, 'F: File' );
     DefineMethod('CloseFile',            1, tkNone,    nil, __CloseFile,           false, 0, 'F: File' );
     DefineMethod('Write',                2, tkNone,    nil, __Write,               false, 0, 'F: File; Value' );
     DefineMethod('WriteLn',              2, tkNone,    nil, __WriteLn,             false, 0, 'F: File; Value' );
     DefineMethod('ReadLn',               1, tkVariant, nil, __ReadLn,              false, 0, 'F: File' );
     DefineMethod('EOF',                  1, tkVariant, nil, __EOF,                 false, 0, 'F: File' );
     DefineMethod('FilePos',              1, tkInteger, nil, __FilePos,             false, 0, 'F: File' );
     DefineMethod('FileSize',             1, tkInteger, nil, __FileSize,            false, 0, 'F: File' );

     { properties }
     DefineProp( 'LastExceptionMessage',     tkString,  GetLastExceptionMessageProc,nil,nil);
     DefineProp( 'LastExceptionHelpContext', tkInteger, GetLastExceptionHelpContextProc,nil,nil);
     DefineProp( 'LastExceptionClassName',   tkString,  GetLastExceptionClassNameProc,nil,nil);
  end;
  with Scripter.DefineClass(TObject) do
  begin
     DefineMethod( 'Create',  0, tkClass, nil, TObjectCreateProc, true );
     DefineMethod( 'Free',    0, tkNone,  nil, TObjectFreeProc );
  end;
end;

procedure TatSystemLibrary.UpperCaseProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( UpperCase( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.LowerCaseProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( LowerCase( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.CompareStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( CompareStr( GetInputArgAsString( 0 ),GetInputArgAsString( 1 ) ) );
end;

procedure TatSystemLibrary.CompareTextProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( CompareText( GetInputArgAsString( 0 ),GetInputArgAsString( 1 ) ) );
end;

procedure TatSystemLibrary.AnsiUpperCaseProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( AnsiUpperCase( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.AnsiLowerCaseProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( AnsiLowerCase( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.AnsiCompareStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( AnsiCompareStr( GetInputArgAsString( 0 ),GetInputArgAsString( 1 ) ) );
end;

procedure TatSystemLibrary.AnsiCompareTextProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( AnsiCompareText( GetInputArgAsString( 0 ),GetInputArgAsString( 1 ) ) );
end;

procedure TatSystemLibrary.TrimProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Trim( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.TrimLeftProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( TrimLeft( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.TrimRightProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( TrimRight( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.IsValidIdentProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( IsValidIdent( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.IntToStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( IntToStr( GetInputArgAsInteger( 0 ) ) );
end;

procedure TatSystemLibrary.IntToHexProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( IntToHex( GetInputArgAsInteger( 0 ),GetInputArgAsInteger( 1 ) ) );
end;

procedure TatSystemLibrary.StrToIntProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( StrToInt( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.StrToIntDefProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( StrToIntDef( GetInputArgAsString( 0 ),GetInputArgAsInteger( 1 ) ) );
end;

procedure TatSystemLibrary.FloatToStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( FloatToStr( GetInputArgAsFloat( 0 ) ) );
end;

procedure TatSystemLibrary.FormatFloatProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( FormatFloat( GetInputArgAsString( 0 ),GetInputArgAsFloat( 1 ) ) );
end;

procedure TatSystemLibrary.StrToFloatProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( StrToFloat( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.EncodeDateProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( EncodeDate(
         GetInputArgAsInteger( 0 ),
         GetInputArgAsInteger( 1 ),
         GetInputArgAsInteger( 2 ) ) );
end;

procedure TatSystemLibrary.EncodeTimeProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( EncodeTime(
         GetInputArgAsInteger( 0 ),
         GetInputArgAsInteger( 1 ),
         GetInputArgAsInteger( 2 ),
         GetInputArgAsInteger( 3 ) ) );
end;

procedure TatSystemLibrary.DecodeDateProc(AMachine:TatVirtualMachine);
var Y,M,D : word;
begin
   with AMachine do
   begin
      DecodeDate( GetInputArgAsDateTime( 0 ), Y, M, D );
      SetInputArg(1,Y);
      SetInputArg(2,M);
      SetInputArg(3,D);
   end;
end;

procedure TatSystemLibrary.DecodeTimeProc(AMachine:TatVirtualMachine);
Var H,M,S,MS : word;
begin
   with AMachine do
   begin
      DecodeTime( GetInputArgAsDateTime( 0 ), H, M, S, MS );
      SetInputArg(1,H);
      SetInputArg(2,M);
      SetInputArg(3,S);
      SetInputArg(4,MS);
   end;
end;

procedure TatSystemLibrary.DayOfWeekProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( DayOfWeek( GetInputArgAsDateTime( 0 ) ) );
end;

procedure TatSystemLibrary.DateProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Date );
end;

procedure TatSystemLibrary.TimeProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Time );
end;

procedure TatSystemLibrary.NowProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Now );
end;

procedure TatSystemLibrary.IncMonthProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( IncMonth( GetInputArgAsDateTime( 0 ),GetInputArgAsInteger( 1 ) ) );
end;

procedure TatSystemLibrary.IsLeapYearProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( IsLeapYear( GetInputArgAsInteger( 0 ) ) );
end;

procedure TatSystemLibrary.DateToStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( DateToStr( GetInputArgAsDateTime( 0 ) ) );
end;

procedure TatSystemLibrary.TimeToStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( TimeToStr( GetInputArgAsDateTime( 0 ) ) );
end;

procedure TatSystemLibrary.DateTimeToStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( DateTimeToStr( GetInputArgAsDateTime( 0 ) ) );
end;

procedure TatSystemLibrary.StrToDateProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( StrToDate( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.StrToTimeProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( StrToTime( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.StrToDateTimeProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( StrToDateTime( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.FormatDateTimeProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( FormatDateTime( GetInputArgAsString( 0 ),GetInputArgAsDateTime( 1 ) ) );
end;

procedure TatSystemLibrary.BeepProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      Beep;
end;

procedure TatSystemLibrary.VarIsNullProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( VarIsNull( GetInputArg( 0 ) ) );
end;

procedure TatSystemLibrary.RoundProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Integer(Round( GetInputArgAsFloat( 0 ) )) );
end;

procedure TatSystemLibrary.TruncProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Integer(Trunc( GetInputArgAsFloat( 0 ) )) );
end;

procedure TatSystemLibrary.CopyProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Copy(
         GetInputArgAsString( 0 ),
         GetInputArgAsInteger( 1 ),
         GetInputArgAsInteger( 2 ) ) );
end;

procedure TatSystemLibrary.DeleteProc(AMachine:TatVirtualMachine);
var S: string;
begin
   with AMachine do
   begin
      S:=GetInputArgAsString( 0 );
      Delete(S, GetInputArgAsInteger( 1 ), GetInputArgAsInteger( 2 ) );
      SetInputArg(0, S);
   end;
end;

procedure TatSystemLibrary.InsertProc(AMachine:TatVirtualMachine);
var S: string;
begin
   with AMachine do
   begin
      S:=GetInputArgAsString( 1 );
      Insert( GetInputArgAsString( 0 ), S, GetInputArgAsInteger( 2 ) );
      SetInputArg(1, S );
   end;
end;

procedure TatSystemLibrary.PosProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( pos(GetInputArgAsString( 0 ),GetInputArgAsString( 1 )) );
end;

procedure TatSystemLibrary.LengthProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Length( GetInputArgAsString( 0 ) ) );
end;

procedure TatSystemLibrary.ShowMessageProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ShowMessage( GetInputArgAsString( 0 ) );
end;

procedure TatSystemLibrary.InputQueryProc(AMachine:TatVirtualMachine);
var Value : string;
begin
   with AMachine do
   begin
      Value:=GetInputArgAsString( 2 );
      if InputQuery(GetInputArgAsString( 0 ),GetInputArgAsString( 1 ),Value) then
         ReturnOutputArg(true)
      else
         ReturnOutputArg(false);
      SetInputArg(2,Value);
   end;
end;

procedure TatSystemLibrary.RaiseProc(AMachine:TatVirtualMachine);
begin
   RaiseRuntimeError( AMachine.GetInputArgAsString(0) );
end;

procedure TatSystemLibrary.CreateOleObjectProc(AMachine:TatVirtualMachine);
begin
   {$IFNDEF LINUX}
   with AMachine do
      ReturnOutputArg(CreateOleObject( GetInputArgAsString( 0 ) ));
   {$ENDIF}
end;

procedure TatSystemLibrary.GetActiveOleObjectProc(AMachine:TatVirtualMachine);
begin
   {$IFNDEF LINUX}
   with AMachine do
      ReturnOutputArg(GetActiveOleObject( GetInputArgAsString( 0 ) ));
   {$ENDIF}
end;

procedure TatSystemLibrary.GetLastExceptionMessageProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( LastExceptionMessage );
end;

procedure TatSystemLibrary.GetLastExceptionHelpContextProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( LastExceptionHelpContext );
end;

procedure TatSystemLibrary.GetLastExceptionClassNameProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( LastExceptionClassName );
end;

procedure TatSystemLibrary.DecProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      SetInputArg(0,GetInputArgAsInteger(0)-1);
end;

procedure TatSystemLibrary.IncProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      SetInputArg(0,GetInputArgAsInteger(0)+1);
end;

procedure TatSystemLibrary.VarToStrProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( GetInputArgAsString( 0 ) );
end;

procedure TatSystemLibrary.HighProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutPutArg( VarArrayHighBound(GetInputArg(0),1) );
end;

procedure TatSystemLibrary.LowProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutPutArg( VarArrayLowBound(GetInputArg(0),1) );
end;

procedure TatSystemLibrary.VarArrayHighBoundProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutPutArg( VarArrayHighBound(GetInputArg(0),GetInputArgAsInteger(1)) );
end;

procedure TatSystemLibrary.VarArrayLowBoundProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutPutArg( VarArrayLowBound(GetInputArg(0),GetInputArgAsInteger(1)) );
end;

procedure TatSystemLibrary.TObjectCreateProc(AMachine: TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( integer(CurrentClass.ClassRef.Create) );
end;

procedure TatSystemLibrary.TObjectFreeProc(AMachine: TatVirtualMachine);
begin
   with AMachine do
      CurrentObject.Free;
end;

{type openarray = array of TVarRec;

function VarArrayAsOpenArray(v:variant):openarray;
begin
end;}

procedure TatSystemLibrary.RandomProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( Random );
end;

function VarArrayAsIntegerArray(v:variant):intarray;
var lo,hi : integer;
    c     : integer;
begin
   if VarArrayDimCount(v)=1 then
   begin
      lo:=VarArrayLowBound(v,1);
      hi:=VarArrayHighBound(v,1);
      SetLength(result,hi-lo+1);
      for c:=lo to hi do
         result[c-lo]:=VarToInteger(v[c]);
   end
   else
      RaiseRuntimeError('Invalid array dimension');
end;

procedure TatSystemLibrary.VarArrayCreateProc(AMachine: TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( VarArrayCreate(VarArrayAsIntegerArray(GetInputArg(0)),GetInputArgAsInteger(1)) );
end;

procedure TatSystemLibrary.MachineProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( integer(AMachine) );
end;

procedure TatSystemLibrary.ScripterProc(AMachine:TatVirtualMachine);
begin
   with AMachine do
      ReturnOutputArg( integer(AMachine.Scripter) );
end;

procedure TatSystemLibrary.FormatProc(AMachine: TatVirtualMachine);
var args  : array of TVarRec;
    v     : variant;
    lo,hi : integer;
    c     : integer;
    pvar  : ^variant;
begin
   with AMachine do
   begin
      v:=GetInputArg(1);
      if VarArrayDimCount(v)=1 then
      begin
         { prepara o "open array" para o segundo argumento da função format
          (convertendo elementos TVarData em TVarRec) }
         lo:=VarArrayLowBound(v,1);
         hi:=VarArrayHighBound(v,1);
         SetLength(args,hi-lo+1);
         pvar := VarArrayLock(v);
         try
            for c:=lo to hi do
            begin
               with TVarData(pvar^) do
                  case VType of
                     varByte,
                     varSmallint,
                     varInteger
                     {$IFDEF DELPHI6_LVL},
                     varShortint,
                     varWord,
                     varLongWord
                     {$ENDIF}:
                        begin
                           args[c-lo].VInteger:=pvar^;
                           args[c-lo].VType:=vtInteger;
                        end;
                     varDate,
                     varSingle,
                     varDouble :
                        begin
                           New(args[c-lo].VExtended);
                           args[c-lo].VExtended^:=VDouble;
                           args[c-lo].VType:=vtExtended;
                        end;
                     varCurrency :
                        begin
                           args[c-lo].VCurrency:=@VCurrency;
                           args[c-lo].VType:=vtCurrency;
                        end;
                     varBoolean :
                        begin
                           args[c-lo].VBoolean:=pvar^;
                           args[c-lo].VType:=vtBoolean;
                        end;
                     varOleStr,
                     varStrArg :
                        begin
                           args[c].VPWideChar := VOleStr;
                           args[c].VType := vtPWideChar;
                        end;
                     varString :
                        begin
                           args[c-lo].VAnsiString := VString;
                           args[c-lo].VType := vtAnsiString;
                        end;
                     {$IFDEF DELPHI2009_LVL}
                     varUString:
                       begin
                           args[c-lo].VUnicodeString := VUString;
                           args[c-lo].VType := vtUnicodeString;
                       end;
                     {$ENDIF}
                     else RaiseRuntimeError('Illegal argument to Format function');
                  end;
               inc(pvar);
            end;

            { executa a função Format do Delphi }
            ReturnOutputArg(Format(GetInputArgAsString(0),args));
         finally
            { Libera variáveis dinamicamente alocadas }
            for c:=hi downto lo do
            begin
               dec(pvar);
               with TVarData(pvar^) do
                  case VType of
                     varDate, varSingle, varDouble :
                        Dispose(args[c-lo].VExtended);
                  end;
            end;
            VarArrayUnlock(v);
         end;
      end
      else
         RaiseRuntimeError('Format function expects second argument as a variant vector');
   end;
end;

procedure TatSystemLibrary.AssignedProc(AMachine:TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg( GetInputArgAsInteger( 0 ) <> 0 );
end;

procedure TatSystemLibrary.InterpretProc(AMachine:TatVirtualMachine);
begin
  with AMachine do
    InProcessExecute( GetInputArgAsString( 0 ) );
end;

procedure TatSystemLibrary.SetOfProc(AMachine:TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg( VarToSet(GetInputArg(0),nil) );
end;

procedure TatSystemLibrary.SinProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Sin(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.CosProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Cos(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.AbsProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Abs(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.ArcTanProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(ArcTan(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.ChDirProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ChDir(GetInputArgAsString(0));
end;

procedure TatSystemLibrary.ChrProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Chr(GetInputArgAsInteger(0)));
end;

procedure TatSystemLibrary.ExpProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Exp(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.FracProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Frac(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.IntProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Int(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.LnProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Ln(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.OddProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Odd(GetInputArgAsInteger(0)));
end;

procedure TatSystemLibrary.OrdProc(AMachine: TatVirtualMachine);
var
  S: string;
begin
  with AMachine do
  begin
    S := GetInputArgAsString(0);
    if Length(S) > 0 then
      ReturnOutputArg(Ord(S[1]))
    else
      ReturnOutputArg(0);
  end;
end;

procedure TatSystemLibrary.SqrProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Sqr(GetInputArgAsFloat(0)));
end;

procedure TatSystemLibrary.SqrtProc(AMachine: TatVirtualMachine);
begin
  with AMachine do
    ReturnOutputArg(Sqrt(GetInputArgAsFloat(0)));
end;

constructor TFileClass.Create(AFileName : string);
begin
  AssignFile(FTextFile, AFileName);
end;

destructor TFileClass.Destroy;
begin
  System.CloseFile(FTextFile);
  inherited;
end;

procedure TatSystemLibrary.__AssignFile(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    SetInputArg(0, Integer(TFileClass.Create(GetInputArgAsString(1))));
  end;
end;

procedure TatSystemLibrary.__CloseFile(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    CloseFile(TFileClass(GetInputArgAsInteger(0)).FTextFile);
  end;
end;

procedure TatSystemLibrary.__Reset(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    Reset(TFileClass(GetInputArgAsInteger(0)).FTextFile);
  end;
end;

procedure TatSystemLibrary.__Rewrite(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    Rewrite(TFileClass(GetInputArgAsInteger(0)).FTextFile);
  end;
end;

procedure TatSystemLibrary.__Append(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    Append(TFileClass(GetInputArgAsInteger(0)).FTextFile);
  end;
end;

procedure TatSystemLibrary.__Write(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    Write(TFileClass(GetInputArgAsInteger(0)).FTextFile, GetInputArg(1));
  end;
end;

procedure TatSystemLibrary.__WriteLn(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    WriteLn(TFileClass(GetInputArgAsInteger(0)).FTextFile, GetInputArg(1));
  end;
end;

procedure TatSystemLibrary.__ReadLn(AMachine: TatVirtualMachine);
var
  S: string;
begin
  with AMachine do
  begin
    ReadLn(TFileClass(GetInputArgAsInteger(0)).FTextFile, S);
    ReturnOutputArg(S);
  end;
end;

procedure TatSystemLibrary.__EOF(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(EOF(TFileClass(GetInputArgAsInteger(0)).FTextFile));
  end;
end;

procedure TatSystemLibrary.__FilePos(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(FilePos(TFileClass(GetInputArgAsInteger(0)).FTextFile)));
  end;
end;

procedure TatSystemLibrary.__FileSize(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(FileSize(TFileClass(GetInputArgAsInteger(0)).FTextFile)));
  end;
end;

end.
