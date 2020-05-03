unit uCallDLL;

{$I ascript.inc}

interface

uses
  SysUtils, Windows 
  {$IFDEF DELPHI6_LVL}
  , Variants
  {$ENDIF}
  ;

type
  TCallingConvention = (ccStdCall, ccRegister, ccPascal, ccCDecl, ccSafeCall);
  openarray = array of TVarRec;

function CallDllFunction(AFile, AFunction: string; AArgs, AArgTypes: openarray;
  AReturnType: integer=vtInteger; ACalling: TCallingConvention = ccStdCall): variant;

// AReturnType and each AArgTypes item must be one of:
// vtInteger    = 0;
// vtBoolean    = 1;
// vtChar       = 2;
// vtExtended   = 3;
// vtString     = 4;
// vtPointer    = 5;
// vtPChar      = 6;
// vtObject     = 7;
// vtClass      = 8;
// vtWideChar   = 9;
// vtPWideChar  = 10;
// vtAnsiString = 11;
// vtCurrency   = 12;
// vtVariant    = 13;
// vtInterface  = 14;
// vtWideString = 15;
// vtInt64      = 16;

implementation

function TypeConst(v: integer): string;
begin
  case v of
    0: result := 'vtInteger';
    1: result := 'vtBoolean';
    2: result := 'vtChar';
    3: result := 'vtExtended';
    4: result := 'vtString';
    5: result := 'vtPointer';
    6: result := 'vtPChar';
    7: result := 'vtObject';
    8: result := 'vtClass';
    9: result := 'vtWideChar';
    10: result := 'vtPWideChar';
    11: result := 'vtAnsiString';
    12: result := 'vtCurrency';
    13: result := 'vtVariant';
    14: result := 'vtInterface';
    15: result := 'vtWideString';
    16: result := 'vtInt64';
    {$IFDEF DELPHI2009_LVL}
    17: result := 'vtUnicodeString';
    {$ENDIF}
    else result := IntToStr(v);
  end;
end;

procedure splitDouble(d:double; var x, y: integer);
var li: array[1..2] of integer absolute d;
begin
  x := li[2];
  y := li[1];
end;

procedure splitExtended(e: extended; var x, y, z: integer);
var li: array[1..3] of integer absolute e;
begin
  x := li[3];
  y := li[2];
  z := li[1];
end;

procedure splitInt64(i64: Int64; var x, y: integer);
var li: array[1..2] of integer absolute i64;
begin
  x := li[2];
  y := li[1];
end;

procedure splitVariant(v: Variant; var x, y, z, k: integer);
var li: array[1..4] of integer absolute v;
begin
  x := li[4];
  y := li[3];
  z := li[2];
  k := li[1];
end;
 {$O-}

function CallDllFunction(AFile, AFunction: string; AArgs, AArgTypes: openarray;
  AReturnType: integer; ACalling: TCallingConvention): variant;
var dll: THandle;
    proc: FARPROC;
    iarg, next, argtype, argInt, x, y, z, k,
    eaxv, edxv, ecxv, stacksize, c, lastreg: integer;
    argFlt: extended;
    argDbl: double;
    arg: TVarRec;
    varg: variant;
    parg: pointer;
    loaded: boolean;
    vresult: variant;
    sresult: AnsiString;
    wresult: widestring;
    {$IFDEF DELPHI2009_LVL}
    uresult: UnicodeString;
    {$ENDIF}

  procedure RegArg(var X);
  begin
    case lastreg of
      0: eaxv := integer(X);
      1: edxv := integer(X);
      2: ecxv := integer(X);
    end;
    inc(lastreg);
  end;

begin

// Directive	Parameter order	Clean-up Passes parameters in registers?
// register	Left-to-right	Routine	 Yes
// pascal	Left-to-right	Routine	 No
// cdecl	Right-to-left	Caller	 No
// stdcall	Right-to-left	Routine	 No
// safecall	Right-to-left	Routine	 No

  { library load (if not loaded yet) }
  dll := GetModuleHandle(PChar(AFile));
  loaded := dll = 0;
  if loaded then
  begin
    dll := SafeLoadLibrary(PChar(AFile));
    if dll = 0 then
      raise exception.CreateFmt('Cannot load library %s', [AFile]);
  end;

  { procedure address }
  proc := GetProcAddress(dll, PChar(AFunction));
  if not assigned(proc) then
    raise exception.CreateFmt('Function %s not found in library %s', [AFunction, AFile]);

  { relation between values and argument types }
  if length(AArgs) <> length(AArgTypes) then
    raise exception.CreateFmt('%d argument values but %d types', [length(AArgs), length(AArgTypes)]);

  if ACalling in [ccRegister, ccPascal] then { left => right }
  begin

    { For a string, dynamic array, method pointer, or Variant result,
      the effects are the same as if the function result were declared as an additional var parameter
      following the declared parameters.
      In other words, the caller passes an additional 32-bit pointer that points to a variable in which to return the function result. }
    if AReturnType in [vtAnsiString, vtVariant,
      {$IFDEF DELPHI2009_LVL}
      vtUnicodeString,
      {$ENDIF}
      vtWideString] then
    begin
      SetLength(AArgs,Length(AArgs)+1);
      SetLength(AArgTypes,Length(AArgTypes)+1);
      AArgs[ High(AArgs) ].VType := vtPointer;
      AArgTypes[ High(AArgTypes) ].VInteger := vtPointer;
      case AReturnType of
        vtAnsiString: AArgs[ High(AArgs) ].VPointer := @sresult;
        vtVariant: AArgs[ High(AArgs) ].VPointer := @vresult;
        vtWideString: AArgs[ High(AArgs) ].VPointer := @wresult;
        {$IFDEF DELPHI2009_LVL}
        vtUnicodeString: AArgs[ High(AArgs) ].VPointer := @uresult;
        {$ENDIF}
      end;
    end;

    next := 1;
    iarg := low(AArgs);
  end
  else { right => left }
  begin

    { For a string, dynamic array, method pointer, or Variant result,
      the effects are the same as if the function result were declared as an additional var parameter
      following the declared parameters.
      In other words, the caller passes an additional 32-bit pointer that points to a variable in which to return the function result. }
    if AReturnType in [vtAnsiString, vtVariant,
      {$IFDEF DELPHI2009_LVL}
      vtUnicodeString,
      {$ENDIF}
      vtWideString] then
    begin
      SetLength(AArgs,Length(AArgs)+1);
      SetLength(AArgTypes,Length(AArgTypes)+1);
      for c:=Length(AArgs)-2 downto 0 do
      begin
        AArgs[c+1] := AArgs[c];
        AArgTypes[c+1] := AArgTypes[c];
      end;
      AArgs[ 0 ].VType := vtPointer;
      AArgTypes[ 0 ].VInteger := vtPointer;
      case AReturnType of
        vtAnsiString: AArgs[ 0 ].VPointer := @sresult;
        vtVariant: AArgs[ 0 ].VPointer := @vresult;
        vtWideString: AArgs[ 0 ].VPointer := @wresult;
        {$IFDEF DELPHI2009_LVL}
        vtUnicodeString: AArgs[ 0 ].VPointer := @uresult;
        {$ENDIF}
      end;
    end;

    iarg := high(AArgs);
    next := -1;
  end;

  { push arguments on stack }
  stacksize := 0;
  lastreg := 0;
  while (iarg >= low(AArgs)) and (iarg <= high(AArgs)) do
  begin
    { get argument value }
    arg := AArgs[iarg];
    varg := NULL;
    parg := nil;                               
    case arg.VType of
      vtInteger:    varg := arg.VInteger;
      vtBoolean:    varg := integer(arg.VBoolean);
      vtChar:       varg := integer(arg.VChar);
      vtExtended:   varg := arg.VExtended^;
      vtString:     parg := arg.VString;
      vtPointer:    parg := arg.VPointer;
      vtPChar:      parg := arg.VPChar;
      vtObject:     parg := pointer(arg.VObject);
      vtWideChar:   varg := arg.VWideChar;
      vtPWideChar:  parg := arg.VPWideChar;
      vtAnsiString: parg := arg.VAnsiString;
      vtCurrency:   parg := arg.VCurrency;
      vtWideString: parg := arg.VWideString;
      vtVariant:    varg := arg.VVariant^;
      vtClass:      varg := integer(arg.VClass);
      {$IFDEF DELPHI2009_LVL}
      vtUnicodeString: parg := arg.VUnicodeString;
      {$ENDIF}
      vtInt64:      {use arg.VInt64^};
      else
        raise exception.CreateFmt('Argument #%d value (%s) not supported', [iarg, TypeConst(arg.VType)]);
    end;

    { argument type }
    argtype := AArgTypes[iarg].VInteger;

    if (ACalling = ccRegister) and (lastreg < 3) then { values on registers (at most 3) }
    begin
      case argtype of
        vtInteger, vtBoolean, vtChar, vtClass, vtWideChar:
          begin
            argInt := varg;
            RegArg(argInt);
          end;
        vtExtended:
          begin
            { always push extended arguments on stack }
            splitExtended(varg, x, y, z);
            asm
              push x
              push y
              push z
            end;
          end;
        vtCurrency:
          begin
            { always push currency/double arguments on stack }
            splitDouble(PDouble(parg)^, x, y);
            asm
              push x
              push y
            end;
          end;
        vtString, vtAnsiString, vtWideString, vtPointer, vtObject, vtPChar,
        {$IFDEF DELPHI2009_LVL}
        vtUnicodeString,
        {$ENDIF}
        vtPWideChar:
          RegArg(parg);
        vtInt64:
          begin
            { always push int64 arguments on stack }
            splitInt64(arg.VInt64^, x, y);
            asm
              push x
              push y
            end;
          end;
        else if argtype > 0 then
          raise exception.CreateFmt('Argument #%d type (%s) not supported', [iarg, TypeConst(argtype)]);
      end;
    end
    else { stack arguments }
    begin
      case argtype of
        vtInteger, vtBoolean, vtChar, vtClass, vtWideChar:
          begin
            argInt := varg;
            asm
              push argInt
            end;
            inc(stacksize);
          end;
        vtExtended:
          begin
            splitExtended(varg, x, y, z);
            asm
              push x
              push y
              push z
            end;
            inc(stacksize, 3);
          end;
        vtCurrency:
          begin
            splitDouble(PDouble(parg)^, x, y);
            asm
              push x
              push y
            end;
            inc(stacksize, 2);
          end;
        vtString, vtAnsiString, vtWideString, vtPointer, vtObject, vtPChar,
        {$IFDEF DELPHI2009_LVL}
        vtUnicodeString,
        {$ENDIF}
        vtPWideChar:
          begin
            asm
              push parg
            end;
            inc(stacksize);
          end;
        vtInt64:
          begin
            splitInt64(arg.VInt64^, x, y);
            asm
              push x
              push y
            end;
            inc(stacksize, 2);
          end;
        vtVariant:
          begin
            splitVariant(varg, x, y, z, k);
            asm
              push x
              push y
              push z
              push k
            end;                          // system.pas tvardata
            inc(stacksize, 4);
          end;

        else
          if argtype > 0 then
            raise exception.CreateFmt('Argument #%d type (%s) not supported', [iarg, TypeConst(argtype)]);
      end;

    end;

    inc(iarg, next);
  end;

  { register values }
  if ACalling = ccRegister then
  asm
    mov eax, eaxv
    mov edx, edxv
    mov ecx, ecxv
  end;

  { procedure call }
  asm
    call proc
    mov argInt, eax
    mov parg, eax
  end;

  { returning value }
  case AReturnType of
    vtExtended:                  
      begin
        asm
          fstp tbyte ptr [argFlt]
        end;
        result := argFlt;
      end;

    vtCurrency:
      begin
        asm
          fstp qword ptr [argDbl]
        end;
        result := argDbl;
      end;

    {$IFNDEF DELPHI2009_LVL}
    vtPChar, vtPWideChar:
      result := string(PChar(parg));
    {$ELSE}
    vtPChar:
      result := AnsiString(PAnsiChar(parg));
    vtPWideChar:
      result := string(PChar(parg));
    {$ENDIF}

    vtWideChar, vtChar:
      result := char(argInt);

    vtString, vtAnsiString:
      result := sresult;

    vtWideString:
      result := wresult;

    {$IFDEF DELPHI2009_LVL}
    vtUnicodeString:
      result := uresult;
    {$ENDIF}

    vtVariant:
      result := vresult;

    else
      result := argInt;
  end;

  { cdecl: clear stack after call }
  if ACalling = ccCDecl then
    for iarg := 0 to stacksize do
    asm
      pop eax
    end;
end;

end.

