unit DispatchLib;

interface

{$I ASCRIPT.INC}

uses
  Windows, ActiveX, classes, Dialogs, ComObj
  {$IFDEF DELPHI6_LVL}
  , Variants
  {$ENDIF}
  ;

type
   DISPATCHKIND = integer;
   const
     DISPATCH_METHOD = 1;
     DISPATCH_PROPERTYGET = 2;
     DISPATCH_PROPERTYPUT = 4;
     DISPATCH_PROPERTYPUTREF = 8;

function DispatchInvokeEx(obj: IDispatch; DispatchId: Integer;
  InvokeMethod: DISPATCHKIND; ParamCount: Integer;
  var ParamArray: OleVariant): OleVariant;
function DispatchInvoke(obj: IDispatch; DispatchName: string;
  InvokeMethod: DISPATCHKIND; ParamCount: Integer;
  var ParamArray: OleVariant): OleVariant;


implementation
uses
  sysutils;

const
  DispIDArgs: Longint = DISPID_PROPERTYPUT;

function DispatchInvoke(obj: IDispatch; DispatchName: string;
  InvokeMethod: DISPATCHKIND; ParamCount: Integer;
  var ParamArray: OleVariant): OleVariant;
var
  AName: widestring;
  disps: TDispIDList;
begin
  AName:=DispatchName;
  Obj.GetIDsOfNames(GUID_NULL, @AName, 1, 0, @disps);
  result:=DispatchInvokeEx(Obj,disps[0],InvokeMethod,ParamCount,ParamArray);
end;


function DispatchInvokeEx(obj: IDispatch; DispatchId: Integer;
  InvokeMethod: DISPATCHKIND; ParamCount: Integer;
  var ParamArray: OleVariant): OleVariant;
const
  MaxDispArgs = 64;
var
  LowBound:  integer;
  Params:    TDISPPARAMS;
  Status:    Integer;
  ExcepInfo: TExcepInfo;
  Args: array[0..MaxDispArgs - 1] of Variant;
  i: integer;
  j: integer;
begin
  LowBound := 0;
  if VarType(ParamArray) > VarNull then
    LowBound := VarArrayLowBound(ParamArray, 1);
  j := 0;
  for i := ParamCount + LowBound - 1 downto LowBound do begin
    Args[j] := ParamArray[i];
    inc(j);
  end; //for
  Params.rgvarg := @Args;
  Params.rgdispidNamedArgs := nil;
  Params.cArgs := ParamCount;
  Params.cNamedArgs := 0;
  if (InvokeMethod in [DISPATCH_PROPERTYPUT]) then
  begin
    Params.rgdispidNamedArgs := @DispIDArgs; // Corrected this here
    Params.cNamedArgs := 1;
    //Params.cArgs := 1;
  end;
  Status := obj.Invoke( DispatchId, GUID_NULL, LOCALE_USER_DEFAULT, InvokeMethod,
     Params, @Result, @ExcepInfo, nil );
  if Status <> 0 then
    raise Exception.Create(Format('Status code: %s'#13#10'Source: %s'#13#10'Description: %s',
    [IntToStr(Status), ExcepInfo.bstrSource, ExcepInfo.bstrDescription]));
end;


end.

