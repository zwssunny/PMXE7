///DELPHI的代码，可以在C++ Builder中编译。

unit CnDate;

interface

uses Windows, SysUtils, Controls;

const
  //农历月份数据，每年4字节，从1901年开始，共150年
  //数据来源：UCDOS 6.0 UCT.COM
  //分析整理：Copyright (c) 1996-1998, Randolph
  //数据解析：
  //如果第一字节的bit7为1，则该年1月1日位于农历12月，否则位于11月
  //第一字节去除bit7为该年1月1日的农历日期
  //        第二字节                第三字节
  //bit:    7  6  5  4  3  2  1  0  7  6  5  4  3  2  1  0
  //农历月份:16 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1
  //农历月份指的是从该年1月1日的农历月份算起的顺序号
  //农历月份对应的bit为1则该月为30日，否则为29日
  //第四字节为闰月月份
  CnData: array[0..599] of Byte = (
    $0b,$52,$ba,$00,   $16,$a9,$5d,$00,   $83,$a9,$37,$05,   $0e,$74,$9b,$00,
    $1a,$b6,$55,$00,   $87,$b5,$55,$04,   $11,$55,$aa,$00,   $1c,$a6,$b5,$00,
    $8a,$a5,$75,$02,   $14,$52,$ba,$00,   $81,$52,$6e,$06,   $0d,$e9,$37,$00,
    $18,$74,$97,$00,   $86,$ea,$96,$05,   $10,$6d,$55,$00,   $1a,$35,$aa,$00,
    $88,$4b,$6a,$02,   $13,$a5,$6d,$00,   $1e,$d2,$6e,$07,   $0b,$d2,$5e,$00,
    $17,$e9,$2e,$00,   $84,$d9,$2d,$05,   $0f,$da,$95,$00,   $19,$5b,$52,$00,
    $87,$56,$d4,$04,   $11,$4a,$da,$00,   $1c,$a5,$5d,$00,   $89,$a4,$bd,$02,
    $15,$d2,$5d,$00,   $82,$b2,$5b,$06,   $0d,$b5,$2b,$00,   $18,$ba,$95,$00,
    $86,$b6,$a5,$05,   $10,$56,$b4,$00,   $1a,$4a,$da,$00,   $87,$49,$ba,$03,
    $13,$a4,$bb,$00,   $1e,$b2,$5b,$07,   $0b,$72,$57,$00,   $16,$75,$2b,$00,
    $84,$6d,$2a,$06,   $0f,$ad,$55,$00,   $19,$55,$aa,$00,   $86,$55,$6c,$04,
    $12,$c9,$76,$00,   $1c,$64,$b7,$00,   $8a,$e4,$ae,$02,   $15,$ea,$56,$00,
    $83,$da,$55,$07,   $0d,$5b,$2a,$00,   $18,$ad,$55,$00,   $85,$aa,$d5,$05,
    $10,$53,$6a,$00,   $1b,$a9,$6d,$00,   $88,$a9,$5d,$03,   $13,$d4,$ae,$00,
    $81,$d4,$ab,$08,   $0c,$ba,$55,$00,   $16,$5a,$aa,$00,   $83,$56,$aa,$06,
    $0f,$aa,$d5,$00,   $19,$52,$da,$00,   $86,$52,$ba,$04,   $11,$a9,$5d,$00,
    $1d,$d4,$9b,$00,   $8a,$74,$9b,$03,   $15,$b6,$55,$00,   $82,$ad,$55,$07,
    $0d,$55,$aa,$00,   $18,$a5,$b5,$00,   $85,$a5,$75,$05,   $0f,$52,$b6,$00,
    $1b,$69,$37,$00,   $89,$e9,$37,$04,   $13,$74,$97,$00,   $81,$ea,$96,$08,
    $0c,$6d,$52,$00,   $16,$2d,$aa,$00,   $83,$4b,$6a,$06,   $0e,$a5,$6d,$00,
    $1a,$d2,$6e,$00,   $87,$d2,$5e,$04,   $12,$e9,$2e,$00,   $1d,$ec,$96,$0a,
    $0b,$da,$95,$00,   $15,$5b,$52,$00,   $82,$56,$d2,$06,   $0c,$2a,$da,$00,
    $18,$a4,$dd,$00,   $85,$a4,$bd,$05,   $10,$d2,$5d,$00,   $1b,$d9,$2d,$00,
    $89,$b5,$2b,$03,   $14,$ba,$95,$00,   $81,$b5,$95,$08,   $0b,$56,$b2,$00,
    $16,$2a,$da,$00,   $83,$49,$b6,$05,   $0e,$64,$bb,$00,   $19,$b2,$5b,$00,
    $87,$6a,$57,$04,   $12,$75,$2b,$00,   $1d,$b6,$95,$00,   $8a,$ad,$55,$02,
    $15,$55,$aa,$00,   $82,$55,$6c,$07,   $0d,$c9,$76,$00,   $17,$64,$b7,$00,
    $86,$e4,$ae,$05,   $11,$ea,$56,$00,   $1b,$6d,$2a,$00,   $88,$5a,$aa,$04,
    $14,$ad,$55,$00,   $81,$aa,$d5,$09,   $0b,$52,$ea,$00,   $16,$a9,$6d,$00,
    $84,$a9,$5d,$06,   $0f,$d4,$ae,$00,   $1a,$ea,$4d,$00,   $87,$ba,$55,$04,
    $12,$5a,$aa,$00,   $1d,$ab,$55,$00,   $8a,$a6,$d5,$02,   $14,$52,$da,$00,
    $82,$52,$ba,$06,   $0d,$a9,$3b,$00,   $18,$b4,$9b,$00,   $85,$74,$9b,$05,
    $11,$b5,$4d,$00,   $1c,$d6,$a9,$00,   $88,$35,$aa,$03,   $13,$a5,$b5,$00,
    $81,$a5,$75,$0b,   $0b,$52,$b6,$00,   $16,$69,$37,$00,   $84,$e9,$2f,$06,
    $10,$f4,$97,$00,   $1a,$75,$4b,$00,   $87,$6d,$52,$05,   $11,$2d,$69,$00,
    $1d,$95,$b5,$00,   $8a,$a5,$6d,$02,   $15,$d2,$6e,$00,   $82,$d2,$5e,$07,
    $0e,$e9,$2e,$00,   $19,$ea,$96,$00,   $86,$da,$95,$05,   $10,$5b,$4a,$00,
    $1c,$ab,$69,$00,   $88,$2a,$d8,$03);

  function CnMonthOfDate(Date: TDate): String;//指定日期的农历月
  function CnDayOfDate(Date: TDate): String;//指定日期的农历日
  function CnDateOfDateStr(Date: TDate): String;//指定日期的农历日期

implementation

//日期是该年的第几天，1月1日为第一天
function DaysNumberOfDate(Date: TDate): Integer;
var
  DaysNumber: Integer;
  I: Integer;
  yyyy, mm, dd: Word;
begin
  DecodeDate(Date, yyyy, mm, dd);
  DaysNumber := 0;
  for I := 1 to mm - 1 do
    Inc(DaysNumber, MonthDays[IsLeapYear(yyyy), I]);
  Inc(DaysNumber, dd);
  Result := DaysNumber;
end;

//日期的农历日期，返回农历格式：月份*100 + 日，负数为闰月
//超出范围则返回0
function CnDateOfDate(Date: TDate): Integer;
var
  CnMonth, CnMonthDays: array[0..15] of Integer;

  CnBeginDay, LeapMonth: Integer;
  yyyy, mm, dd: Word;
  Bytes: array[0..3] of Byte;
  I: Integer;
  CnMonthData: Word;
  DaysCount, CnDaysCount, ResultMonth, ResultDay: Integer;
begin
  DecodeDate(Date, yyyy, mm, dd);
  if (yyyy < 1901) or (yyyy > 2050) then
  begin
    Result := 0;
    Exit;
  end;
  Bytes[0] := CnData[(yyyy - 1901) * 4];
  Bytes[1] := CnData[(yyyy - 1901) * 4 + 1];
  Bytes[2] := CnData[(yyyy - 1901) * 4 + 2];
  Bytes[3] := CnData[(yyyy - 1901) * 4 + 3];
  if (Bytes[0] and $80) <> 0 then CnMonth[0] := 12
  else CnMonth[0] := 11;
  CnBeginDay := (Bytes[0] and $7f);
  CnMonthData := Bytes[1];
  CnMonthData := CnMonthData shl 8;
  CnMonthData := CnMonthData or Bytes[2];
  LeapMonth := Bytes[3];

  for I := 15 downto 0 do
  begin
    CnMonthDays[15 - I] := 29;
    if ((1 shl I) and CnMonthData) <> 0 then
      Inc(CnMonthDays[15 - I]);
    if CnMonth[15 - I] = LeapMonth then
      CnMonth[15 - I + 1] := - LeapMonth
    else
    begin
      if CnMonth[15 - I] < 0 then //上月为闰月
        CnMonth[15 - I + 1] := - CnMonth[15 - I] + 1
      else CnMonth[15 - I + 1] := CnMonth[15 - I] + 1;
      if CnMonth[15 - I + 1] > 12 then CnMonth[15 - I + 1] := 1;
    end;
  end;

  DaysCount := DaysNumberOfDate(Date) - 1;
  if DaysCount <= (CnMonthDays[0] - CnBeginDay) then
  begin
    if (yyyy > 1901) and
      (CnDateOfDate(EncodeDate(yyyy - 1, 12, 31)) < 0) then
      ResultMonth := - CnMonth[0]
    else ResultMonth := CnMonth[0];
    ResultDay := CnBeginDay + DaysCount;
  end
  else
  begin
    CnDaysCount := CnMonthDays[0] - CnBeginDay;
    I := 1;
    while (CnDaysCount < DaysCount) and
      (CnDaysCount + CnMonthDays[I] < DaysCount) do
    begin
      Inc(CnDaysCount, CnMonthDays[I]);
      Inc(I);
    end;
    ResultMonth := CnMonth[I];
    ResultDay := DaysCount - CnDaysCount;
  end;
  if ResultMonth > 0 then
    Result := ResultMonth * 100 + ResultDay
  else Result := ResultMonth * 100 - ResultDay
end;

function CnMonthOfDate(Date: TDate): String;
const
  CnMonthStr: array[1..12] of String = (
    '一', '二', '三', '四', '五', '六', '七', '八', '九', '十',
    '冬', '蜡');
var
  Month: Integer;
begin
  Month := CnDateOfDate(Date) div 100;
  if Month < 0 then Result := '闰' + CnMonthStr[-Month]
  else Result := CnMonthStr[Month] + '月';
end;

function CnDayOfDate(Date: TDate): String;
const
  CnDayStr: array[1..30] of String = (
    '初一', '初二', '初三', '初四', '初五',
    '初六', '初七', '初八', '初九', '初十',
    '十一', '十二', '十三', '十四', '十五',
    '十六', '十七', '十八', '十九', '二十',
    '廿一', '廿二', '廿三', '廿四', '廿五',
    '廿六', '廿七', '廿八', '廿九', '三十');
var
  Day: Integer;
begin
  Day := Abs(CnDateOfDate(Date)) mod 100;
  Result := CnDayStr[Day];
end;

function CnDateOfDateStr(Date: TDate): String;
begin
  Result := CnMonthOfDate(Date) + CnDayOfDate(Date);
end;

end.



