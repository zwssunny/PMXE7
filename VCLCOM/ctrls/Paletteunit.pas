unit Paletteunit;

interface
  uses
    Windows, Messages, SysUtils, Classes, Graphics, Controls;
  Function CreateGridPalette :HPalette;
  var G_APP_Palette:HPalette;
      PaletteOffset:Integer=0;
implementation
type  TPaletteEntries = array[0..255] of TPaletteEntry;
var
  Pal256: array [0..136] of TColor=
(65280,
8947848 ,
12303291 ,
9685345   ,
1577195   ,
3365154   ,
6498601   ,
1051573   ,
65793     ,
2570478   ,
2222046   ,
538232    ,
1920141   ,
1059154   ,
6918033   ,
6062724   ,
5207416 ,
7773341  ,
8628906  ,
9484214  ,
10339523 ,
11194831 ,
7895160   ,
15658734  ,
13421772   ,
3228168   ,
8692079   ,
13666460  ,
4027635   ,
7902048   ,
7007229   ,
11786154  ,
6477820   ,
1184274   ,
4557045   ,
6013946   ,
16773611  ,
7471103   ,
5484536   ,
7315273   ,
9747934   ,
12510393  ,
10206348  ,
13427705  ,
11184810  ,
5020663   ,
6776679   ,
5658198   ,
3421236   ,
2302755   ,
4539717   ,
10066329  ,
3034352   ,
14540253  ,
13300423  ,
16777215  ,
15763519  ,
9989221   ,
12294541  ,
11109241  ,
13414561  ,
2309734   ,
4810894   ,
14599861  ,
5996194   ,
7246774   ,
3560314   ,
15728623  ,
3960493   ,
8497354   ,
2578328   ,
1196419   ,
3302306   ,
4618679   ,
6000588   ,
3563762   ,
15517643  ,
9416318   ,
16505491  ,
2041069   ,
4883588   ,
4429203   ,
7560221  ,
14216959 ,
8678706  ,
12638707 ,
9731911  ,
11849453 ,
8165586  ,
16775861 ,
5342402  ,
9547482  ,
4018199  ,
10996123 ,
5532468  ,
16370050 ,
16640676 ,
6322243  ,
7112274  ,
16234866 ,
5735226  ,
13022343 ,
4155178  ,
4807973  ,
10850653 ,
14922428 ,
13005708 ,
7683901  ,
8803921  ,
10336480 ,
6980557  ,
11125734,
8758228 ,
5795272 ,
6387914 ,
2676687 ,
16034145,
15628334 ,
7572943  ,
6507016  ,
4945202  ,
14075548 ,
16178395 ,
13172680 ,
14090198 ,
6525250  ,
11903858 ,
14261676 ,
3585713  ,
15898960,
$00FF7F7F,
$00FCCB78,
$007FFBFB,
$007A98A7,
$00F0FBFF,
$00D1E9F5,
$007DA8AC
);
Function CreateGridPalette :HPalette;
var
  pLogPal: ^TLogPalette;
  pPalEntries: ^TPaletteEntries;
  i,K: Integer;
  Function SetRgb(R,G,B:Integer):TPaletteEntry;
  Begin
    Result.peRed   := R;
    Result.peGreen := G;
    Result.peBlue  := B;
    Result.peFlags := 0;
  end;
  Function SetColor(C:TColor):TPaletteEntry;
  Begin
    Result.peRed   := (c and $000000ff);
    Result.peGreen := (c shr 8) and $000000ff;
    Result.peBlue  := (c shr 16) and $000000ff;
    Result.peFlags := 0;
  end;
  Function SamePaletteEntry(A,B:TPaletteEntry):boolean;
  Begin
    Result:=(A.peRed=B.peRed) and (A.peGreen=B.peGreen) and (A.peBlue=B.peBlue)
  end;

  Function IsNotSame(KK:Integer):Boolean;
  var J:Integer;
  Begin
    Result:=True;
    if KK=0 then Exit;
    for J:=1 to KK-1+29 do
    Begin
      if SamePaletteEntry(pPalEntries[J],SetColor(Pal256[KK]))  then
      Begin
       Result:=False;
       Exit;
      end;
    end;

  end;
begin
  GetMem(pLogPal, SizeOf(TLogPalette) +SizeOf(TPaletteEntry)*256);
  pPalEntries := @pLogPal.palPalEntry[0];
  pLogPal.palVersion := $0300;
  pLogPal.palNumEntries := 29+130;

  for i := 0 to 255 do
  begin
    pPalEntries[i].peRed   := 0;
    pPalEntries[i].peGreen := 0;
    pPalEntries[i].peBlue  := 0;
    pPalEntries[i].peFlags := 0;
  end;

  pPalEntries[1+PaletteOffset]:=SetColor($009FBECB);
  pPalEntries[2+PaletteOffset]:=SetColor($00506E66);
  pPalEntries[3+PaletteOffset]:=SetColor($00BFF0F0);
  pPalEntries[4+PaletteOffset]:=SetColor($004F6F60);
  pPalEntries[5+PaletteOffset]:=SetColor($00BEE4E1);

  pPalEntries[6+PaletteOffset]:=SetColor($00E3FBFB);
  pPalEntries[7+PaletteOffset]:=SetColor($006084E3);
  pPalEntries[8+PaletteOffset]:=SetColor($00BFE0DF);
  pPalEntries[9+PaletteOffset]:=SetColor($00E3FBFD);
  pPalEntries[10+PaletteOffset]:=SetColor($00E3FBFC);

  pPalEntries[11+PaletteOffset]:=SetColor($00E3FBFA);
  pPalEntries[12+PaletteOffset]:=SetColor($0096D396);
  pPalEntries[13+PaletteOffset]:=SetColor($0080985F);
  pPalEntries[14+PaletteOffset]:=SetColor($009FBFC0);
  pPalEntries[15+PaletteOffset]:=SetColor($009FB8B0);

  pPalEntries[16+PaletteOffset]:=SetColor($00C1B7B8);
  pPalEntries[17+PaletteOffset]:=SetColor($00B0D8EF);
  pPalEntries[18+PaletteOffset]:=SetColor($00D6F6FA);
  pPalEntries[19+PaletteOffset]:=SetColor($009FBECA);
  pPalEntries[20+PaletteOffset]:=SetColor($00A0C0C0);

  pPalEntries[21+PaletteOffset]:=SetRGB(127,111,127);
  pPalEntries[22+PaletteOffset]:=SetRGB(143,104,95);
  pPalEntries[23+PaletteOffset]:=SetRGB(160,152,128);
  pPalEntries[24+PaletteOffset]:=SetRGB(224,207,176);
  pPalEntries[25+PaletteOffset]:=SetColor($00506E66);
  pPalEntries[26+PaletteOffset]:=SetColor($0060978F);
  pPalEntries[27+PaletteOffset]:=SetColor($00BFF0F0);
  pPalEntries[28+PaletteOffset]:=SetColor($00D6F6FB);
  K:=0;
  for I:=0 to 136 do
  Begin
    if isNotSame(I)  then
    Begin
      pPalEntries[29+PaletteOffset+I]:=SetColor(Pal256[I]);
      K:=K+1;
    end;
  end;

  Result := CreatePalette(pLogPal^);
  FreeMem(pLogPal, SizeOf(TLogPalette) +SizeOf(TPaletteEntry)*256);
end;

initialization
  G_APP_Palette:=CreateGridPalette;
finalization
  if G_APP_Palette<>0 then  DeleteObject(G_App_palette)
end.






