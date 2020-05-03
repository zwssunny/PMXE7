object frmEditServer: TfrmEditServer
  Left = 0
  Top = 0
  Caption = #32534#36753#35760#24405
  ClientHeight = 271
  ClientWidth = 406
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 12
    Top = 28
    Width = 60
    Height = 13
    Caption = #26381#21153#21517#31216#65306
  end
  object Label2: TLabel
    Left = 24
    Top = 72
    Width = 48
    Height = 13
    Caption = #25991#20214#21517#65306
  end
  object Label3: TLabel
    Left = 36
    Top = 116
    Width = 36
    Height = 13
    Caption = #22791#27880#65306
  end
  object SpeedButton1: TSpeedButton
    Left = 314
    Top = 70
    Width = 23
    Height = 22
    Caption = '...'
    OnClick = SpeedButton1Click
  end
  object edServerName: TEdit
    Left = 78
    Top = 29
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object edFileName: TEdit
    Left = 78
    Top = 71
    Width = 236
    Height = 21
    ReadOnly = True
    TabOrder = 1
  end
  object edDisplay: TEdit
    Left = 78
    Top = 113
    Width = 265
    Height = 21
    TabOrder = 2
  end
  object BitBtn1: TBitBtn
    Left = 72
    Top = 200
    Width = 75
    Height = 25
    Caption = #30830#23450
    Default = True
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
    TabOrder = 3
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 256
    Top = 200
    Width = 75
    Height = 25
    Caption = #21462#28040
    Kind = bkCancel
    NumGlyphs = 2
    TabOrder = 4
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.exe'
    Filter = 'NT'#26381#21153#31243#24207'|*.Exe|'#20854#23427#31243#24207'|*.*'
    Options = [ofReadOnly, ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = #36873#25321#26381#21153#31243#24207
    Left = 272
    Top = 48
  end
end
