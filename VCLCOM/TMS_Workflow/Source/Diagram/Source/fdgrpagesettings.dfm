object fmDgrPageSettings: TfmDgrPageSettings
  Left = 401
  Top = 125
  ActiveControl = cbPaperSize
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #39029#38754#35774#32622
  ClientHeight = 336
  ClientWidth = 341
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  DesignSize = (
    341
    336)
  PixelsPerInch = 96
  TextHeight = 12
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 327
    Height = 283
    ActivePage = tsPaper
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object tsPaper: TTabSheet
      Caption = #32440#24352
      DesignSize = (
        319
        256)
      object Label1: TLabel
        Left = 4
        Top = 8
        Width = 48
        Height = 12
        Caption = #32440#24352#22823#23567
      end
      object Shape1: TShape
        Left = 63
        Top = 15
        Width = 248
        Height = 1
        Anchors = [akLeft, akTop, akRight]
        Brush.Style = bsClear
        Pen.Color = clSilver
      end
      object Label2: TLabel
        Left = 14
        Top = 58
        Width = 30
        Height = 12
        Caption = #23485#24230':'
        FocusControl = edWidth
      end
      object Label3: TLabel
        Left = 14
        Top = 82
        Width = 30
        Height = 12
        Caption = #39640#24230':'
        FocusControl = edHeight
      end
      object lbUnit2: TLabel
        Left = 177
        Top = 82
        Width = 12
        Height = 12
        Caption = 'cm'
      end
      object lbUnit1: TLabel
        Left = 177
        Top = 58
        Width = 12
        Height = 12
        Caption = 'cm'
      end
      object Label4: TLabel
        Left = 3
        Top = 109
        Width = 24
        Height = 12
        Caption = #26041#21521
      end
      object Shape2: TShape
        Left = 64
        Top = 116
        Width = 246
        Height = 1
        Anchors = [akLeft, akTop, akRight]
        Brush.Style = bsClear
        Pen.Color = clSilver
      end
      object imgLandscape: TImage
        Left = 150
        Top = 137
        Width = 32
        Height = 25
        Picture.Data = {
          07544269746D617006020000424D060200000000000076000000280000002000
          0000190000000100040000000000900100000000000000000000100000000000
          0000000000000000800000800000008080008000000080008000808000008080
          8000C0C0C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
          FF00D77777777777777777777777777777770000000000000000000000000000
          00070FFFFFFFFFFFFFFFFFFFFFFFFFFFFF070FFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF070FFFFFFFFFFFFFFFFFFFFFFFFFFFFF070FFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF070FFF000000FFFFFF00000000FFFFFF070FFFFF00FFFFFFFFFF0000FFFFFF
          FF070FFFFFF0FFFFFFFFFF000FFFFFFFFF070FFFFFF00FFFFFFFF0000FFFFFFF
          FF070FFFFFFF0FFFFFFFF000FFFFFFFFFF070FFFFFFF000000000000FFFFFFFF
          FF070FFFFFFFF0FFFFFF000FFFFFFFFFFF070FFFFFFFF00FFFF0000FFFFFFFFF
          FF070FFFFFFFFF0FFFF000FFFFFFFFFFFF070FFFFFFFFF00FF0000FFFFFFFFFF
          FF070FFFFFFFFFF0FF000FFFFFFFFFFFFF070FFFFFFFFFF00F000FFFFFFFFFFF
          FF070FFFFFFFFFFF0000FFFFFFFF0000000D0FFFFFFFFFFF0000FFFFFFFF0FFF
          F0DD0FFFFFFFFFFFF00FFFFFFFFF0FFF0DDD0FFFFFFFFFFFF00FFFFFFFFF0FF0
          DDDD0FFFFFFFFFFFFFFFFFFFFFFF0F0DDDDD0FFFFFFFFFFFFFFFFFFFFFFF00DD
          DDDD0000000000000000000000000DDDDDDD}
        Transparent = True
      end
      object imgPortrait: TImage
        Left = 14
        Top = 134
        Width = 26
        Height = 32
        AutoSize = True
        Picture.Data = {
          07544269746D617076020000424D760200000000000076000000280000001A00
          0000200000000100040000000000000200000000000000000000100000000000
          0000000000000000800000800000008080008000000080008000808000008080
          8000C0C0C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
          FF00D77777777777777777777777770000000000000000000000000000000700
          00000FFFFFFFFFFFFFFFFFFFFFFF070000000FFFFFFFFFFFFFFFFFFFFFFF0700
          00000FFFFFFFFFFFFFFFFFFFFFFF070000000FFFFFFFFFFFFFFFFFFFFFFF0700
          00000FFFFFFFFFFFFFFFFFFFFFFF070000000FFFFFFFFFFFFFFFFFFFFFFF0700
          00000FFFFFFFFFFFFFFFFFFFFFFF070000000FF000000FFFFF000000000F0700
          00000FFFF00FFFFFFFFFF0000FFF070000000FFFFF0FFFFFFFFFF000FFFF0700
          00000FFFFF00FFFFFFFF0000FFFF070000000FFFFFF0FFFFFFFF000FFFFF0700
          00000FFFFFF000000000000FFFFF070000000FFFFFFF0FFFFFF000FFFFFF0700
          00000FFFFFFF00FFFF0000FFFFFF070000000FFFFFFFF0FFFF000FFFFFFF0700
          00000FFFFFFFF00FF0000FFFFFFF070000000FFFFFFFFF0FF000FFFFFFFF0700
          00000FFFFFFFFF00F000FFFFFFFF070000000FFFFFFFFFF0000FFFFFFFFF0700
          00000FFFFFFFFFF0000FFFFFFFFF070000000FFFFFFFFFFF00FFFFFFFFFF0700
          00000FFFFFFFFFFF00FFFFFFFFFF070000000FFFFFFFFFFFFFFFFF0000000D00
          00000FFFFFFFFFFFFFFFFF0FFFF0DD0000000FFFFFFFFFFFFFFFFF0FFF0DDD00
          00000FFFFFFFFFFFFFFFFF0FF0DDDD0000000FFFFFFFFFFFFFFFFF0F0DDDDD00
          00000FFFFFFFFFFFFFFFFF00DDDDDD0000000000000000000000000DDDDDDD00
          0000}
        Transparent = True
      end
      object Label5: TLabel
        Left = 3
        Top = 176
        Width = 24
        Height = 12
        Caption = #36793#36317
      end
      object Shape3: TShape
        Left = 50
        Top = 183
        Width = 260
        Height = 1
        Anchors = [akLeft, akTop, akRight]
        Brush.Style = bsClear
        Pen.Color = clSilver
      end
      object lbMarginTop: TLabel
        Left = 14
        Top = 198
        Width = 18
        Height = 12
        Caption = #19978':'
        FocusControl = edMarginTop
      end
      object lbMarginLeft: TLabel
        Left = 14
        Top = 222
        Width = 18
        Height = 12
        Caption = #24038':'
        FocusControl = edMarginLeft
      end
      object lbMarginBottom: TLabel
        Left = 169
        Top = 198
        Width = 18
        Height = 12
        Caption = #19979':'
        FocusControl = edMarginBottom
      end
      object lbMarginRight: TLabel
        Left = 169
        Top = 222
        Width = 18
        Height = 12
        Caption = #21491':'
        FocusControl = edMarginRight
      end
      object lbUnit3: TLabel
        Left = 124
        Top = 198
        Width = 12
        Height = 12
        Caption = 'cm'
      end
      object lbUnit4: TLabel
        Left = 124
        Top = 222
        Width = 12
        Height = 12
        Caption = 'cm'
      end
      object lbUnit5: TLabel
        Left = 289
        Top = 198
        Width = 12
        Height = 12
        Caption = 'cm'
      end
      object lbUnit6: TLabel
        Left = 289
        Top = 222
        Width = 12
        Height = 12
        Caption = 'cm'
      end
      object cbPaperSize: TComboBox
        Left = 14
        Top = 28
        Width = 180
        Height = 20
        Style = csDropDownList
        ItemHeight = 12
        TabOrder = 0
        OnChange = cbPaperSizeChange
      end
      object edWidth: TEdit
        Left = 70
        Top = 56
        Width = 101
        Height = 21
        HelpContext = 140
        AutoSize = False
        Ctl3D = True
        Enabled = False
        ParentCtl3D = False
        TabOrder = 1
      end
      object edHeight: TEdit
        Left = 70
        Top = 80
        Width = 101
        Height = 21
        HelpContext = 150
        AutoSize = False
        Ctl3D = True
        Enabled = False
        ParentCtl3D = False
        TabOrder = 2
      end
      object rbPortrait: TRadioButton
        Left = 50
        Top = 136
        Width = 76
        Height = 17
        Caption = #31446#21521
        TabOrder = 3
        OnClick = rbPortraitClick
      end
      object rbLandscape: TRadioButton
        Left = 194
        Top = 136
        Width = 76
        Height = 17
        Caption = #27178#21521
        TabOrder = 4
        OnClick = rbLandscapeClick
      end
      object edMarginTop: TEdit
        Left = 60
        Top = 196
        Width = 60
        Height = 21
        HelpContext = 72
        AutoSize = False
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 5
      end
      object edMarginLeft: TEdit
        Left = 60
        Top = 220
        Width = 60
        Height = 21
        HelpContext = 81
        AutoSize = False
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 7
      end
      object edMarginBottom: TEdit
        Left = 225
        Top = 196
        Width = 60
        Height = 21
        HelpContext = 91
        AutoSize = False
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 6
      end
      object edMarginRight: TEdit
        Left = 225
        Top = 220
        Width = 60
        Height = 21
        HelpContext = 101
        AutoSize = False
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 8
      end
    end
  end
  object btOk: TButton
    Left = 174
    Top = 302
    Width = 75
    Height = 25
    HelpContext = 40
    Anchors = [akRight, akBottom]
    Caption = #30830#23450
    Default = True
    ModalResult = 1
    TabOrder = 1
    OnClick = btOkClick
  end
  object btCancel: TButton
    Left = 256
    Top = 302
    Width = 75
    Height = 25
    HelpContext = 50
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = #21462#28040
    ModalResult = 2
    TabOrder = 2
  end
end
