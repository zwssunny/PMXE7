object fmDiagramEditor: TfmDiagramEditor
  Left = 210
  Top = 166
  Caption = 'Diagram Editor'
  ClientHeight = 521
  ClientWidth = 829
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object FLeftDockSplitter: TSplitter
    Left = 180
    Top = 139
    Width = 2
    Height = 363
    ExplicitTop = 145
    ExplicitHeight = 345
  end
  object FRightDockSplitter: TSplitter
    Left = 647
    Top = 139
    Width = 2
    Height = 363
    Align = alRight
    ExplicitLeft = 639
    ExplicitTop = 145
    ExplicitHeight = 345
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 502
    Width = 829
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
  object ControlBar1: TControlBar
    Left = 0
    Top = 0
    Width = 829
    Height = 82
    Align = alTop
    AutoSize = True
    BevelEdges = []
    BevelInner = bvNone
    BevelOuter = bvNone
    BevelKind = bkNone
    RowSize = 28
    RowSnap = False
    TabOrder = 1
    OnDockOver = ControlBar1DockOver
    object ToolBar1: TToolBar
      Left = 11
      Top = 2
      Width = 467
      Height = 22
      Align = alNone
      AutoSize = True
      Caption = 'ToolBar1'
      Images = dmDgrEditorActions.ImageList1
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Wrapable = False
      object ToolButton1: TToolButton
        Left = 0
        Top = 0
        Action = dmDgrEditorActions.acNewDiagram
      end
      object ToolButton2: TToolButton
        Left = 23
        Top = 0
        Action = dmDgrEditorActions.acOpenDiagram
      end
      object ToolButton3: TToolButton
        Left = 46
        Top = 0
        Action = dmDgrEditorActions.acSaveDiagram
      end
      object ToolButton4: TToolButton
        Left = 69
        Top = 0
        Action = dmDgrEditorActions.acPrintDiagram
      end
      object ToolButton9: TToolButton
        Left = 92
        Top = 0
        Action = dmDgrEditorActions.acPreviewDiagram
      end
      object ToolButton5: TToolButton
        Left = 115
        Top = 0
        Width = 8
        ImageIndex = 4
        Style = tbsSeparator
      end
      object ToolButton6: TToolButton
        Left = 123
        Top = 0
        Action = dmDgrEditorActions.DiagramCut1
      end
      object ToolButton7: TToolButton
        Left = 146
        Top = 0
        Action = dmDgrEditorActions.DiagramCopy1
      end
      object ToolButton8: TToolButton
        Left = 169
        Top = 0
        Action = dmDgrEditorActions.DiagramPaste1
      end
      object ToolButton19: TToolButton
        Left = 192
        Top = 0
        Width = 8
        ImageIndex = 17
        Style = tbsSeparator
      end
      object ToolButton13: TToolButton
        Left = 200
        Top = 0
        Action = dmDgrEditorActions.DiagramBlockPicture1
      end
      object ToolButton14: TToolButton
        Left = 223
        Top = 0
        Action = dmDgrEditorActions.DiagramBringToFront1
      end
      object ToolButton15: TToolButton
        Left = 246
        Top = 0
        Action = dmDgrEditorActions.DiagramSendToBack1
      end
      object ToolButton16: TToolButton
        Left = 269
        Top = 0
        Action = dmDgrEditorActions.DiagramControlFont1
      end
      object ToolButton10: TToolButton
        Left = 292
        Top = 0
        Action = dmDgrEditorActions.acGroup
      end
      object ToolButton12: TToolButton
        Left = 315
        Top = 0
        Action = dmDgrEditorActions.acUngroup
      end
      object ToolButton49: TToolButton
        Left = 338
        Top = 0
        Width = 8
        Caption = 'ToolButton49'
        ImageIndex = 21
        Style = tbsSeparator
      end
      object DgrLayerSelector1: TDgrLayerSelector
        Left = 346
        Top = 0
        Width = 121
        Height = 22
        Button.Color = clWhite
        Button.ColorTo = 13226453
        Button.ColorHot = 13811126
        Button.ColorHotTo = 13811126
        Button.ColorDown = 11899525
        Button.ColorDownTo = 11899525
        Button.Width = 12
        DisplayRecentSelection = False
        DropDownCount = 8
        BorderColor = clNone
        BorderHotColor = clBlack
        LookUp = False
        SelectionColor = 11899525
        SelectionTextColor = clWhite
        Text = '(no layer)'
        Version = '2.0.0.0'
        DropDownListColor = clWindow
      end
    end
    object DiagramToolBar2: TDiagramToolBar
      Left = 402
      Top = 56
      Width = 55
      Height = 23
      Buttons = [dbCancelInsert, dbDelete]
      Align = alNone
      KeepInsertingMode = kmNever
      Mode = tmConnections
      ButtonSize = 23
    end
    object ToolBar3: TToolBar
      Left = 11
      Top = 56
      Width = 377
      Height = 24
      Align = alNone
      ButtonHeight = 23
      Images = dmDgrEditorActions.ImageList2
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      object ToolButton17: TToolButton
        Left = 0
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign1
      end
      object ToolButton18: TToolButton
        Left = 23
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign2
      end
      object ToolButton20: TToolButton
        Left = 46
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign3
      end
      object ToolButton21: TToolButton
        Left = 69
        Top = 0
        Width = 8
        Caption = 'ToolButton21'
        ImageIndex = 3
        Style = tbsSeparator
      end
      object ToolButton22: TToolButton
        Left = 77
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign4
      end
      object ToolButton23: TToolButton
        Left = 100
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign5
      end
      object ToolButton24: TToolButton
        Left = 123
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign6
      end
      object ToolButton25: TToolButton
        Left = 146
        Top = 0
        Width = 8
        Caption = 'ToolButton25'
        ImageIndex = 6
        Style = tbsSeparator
      end
      object ToolButton26: TToolButton
        Left = 154
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign7
      end
      object ToolButton27: TToolButton
        Left = 177
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign8
      end
      object ToolButton28: TToolButton
        Left = 200
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign9
      end
      object ToolButton29: TToolButton
        Left = 223
        Top = 0
        Width = 8
        Caption = 'ToolButton29'
        ImageIndex = 9
        Style = tbsSeparator
      end
      object ToolButton30: TToolButton
        Left = 231
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign10
      end
      object ToolButton31: TToolButton
        Left = 254
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign11
      end
      object ToolButton32: TToolButton
        Left = 277
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign12
      end
      object ToolButton34: TToolButton
        Left = 300
        Top = 0
        Width = 8
        Caption = 'ToolButton34'
        ImageIndex = 13
        Style = tbsSeparator
      end
      object ToolButton35: TToolButton
        Left = 308
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign14
      end
      object ToolButton36: TToolButton
        Left = 331
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign15
      end
      object ToolButton37: TToolButton
        Left = 354
        Top = 0
        Action = dmDgrEditorActions.DiagramAlign16
      end
    end
    object ToolBar2: TToolBar
      Left = 365
      Top = 28
      Width = 413
      Height = 24
      Align = alNone
      Caption = 'ToolBar2'
      Images = dmDgrEditorActions.ImageList3
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      object DgrFontSelector1: TDgrFontSelector
        Left = 0
        Top = 0
        Width = 127
        Height = 22
        Button.Color = clWhite
        Button.ColorTo = 13226453
        Button.ColorHot = 13811126
        Button.ColorHotTo = 13811126
        Button.ColorDown = 11899525
        Button.ColorDownTo = 11899525
        Button.Width = 12
        DropDownCount = 8
        BorderColor = clNone
        BorderHotColor = clBlack
        SelectionColor = 11899525
        SelectionTextColor = clWhite
        Version = '2.0.0.0'
        DropDownListColor = clWindow
        AllowedFontTypes = [aftBitmap, aftTrueType, aftPostScript, aftPrinter, aftFixedPitch, aftProportional]
        FontGlyphTT.Data = {
          D6000000424DD60000000000000076000000280000000D0000000C0000000100
          0400000000006000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDD000000D
          D000DDDDDDD00DDDD000DDDDDDD00DDDD000D77777700DDDD000DDD77DD00DDD
          D000DDD70DD00DD0D000DDD70DD00DD0D000DDD700D00D00D0007DD700000000
          D0007DD77DD7DDDDD00077D77D77DDDDD00077777777DDDDD000}
        FontGlyphPS.Data = {
          D6000000424DD60000000000000076000000280000000D0000000C0000000100
          0400000000006000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
          D000D9997DD997DDD0009999979979DDD000997D7999D79DD000997DD7997DDD
          D000997DDD799DDDD000799DDDD997DDD000D997DDD799DDD000D799DDDD997D
          D000DD799DDD799DD000DDD799DD7997D000DDDDD9999779D000}
        FontGlyphPRN.Data = {
          D6000000424DD60000000000000076000000280000000D0000000C0000000100
          0400000000006000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00D00000000000
          D00007777777AA7700000888888888870000D00000000000D000DD07FFFFF70D
          D000DD0F00000F0DD000DD07FFFFF70DD000DD0F00000F0DD000DD07FFFFF70D
          D000DD0F00000F0DD000DD07FFFFF70DD000DD000000000DD000}
        FontGlyphBMP.Data = {
          D6000000424DD60000000000000076000000280000000D0000000C0000000100
          0400000000006000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
          D000DDDDDD99DD99D000DDDDDD99DD99D000D11DD199DD99D000D11DD1999999
          D000D11DD199DD99D000D1111199DD99D000D11DD199DD99D000D11DD119999D
          D000D11DD11D99DDD000DD1111DDDDDDD000DDD11DDDDDDDD000}
        FontHeight = 12
        TabOrder = 0
      end
      object ToolButton11: TToolButton
        Left = 127
        Top = 0
        Width = 8
        Caption = 'ToolButton11'
        Style = tbsSeparator
      end
      object DgrFontSizeSelector1: TDgrFontSizeSelector
        Left = 135
        Top = 0
        Width = 47
        Height = 22
        Button.Color = clWhite
        Button.ColorTo = 13226453
        Button.ColorHot = 13811126
        Button.ColorHotTo = 13811126
        Button.ColorDown = 11899525
        Button.ColorDownTo = 11899525
        Button.Width = 12
        DisplayRecentSelection = False
        DropDownCount = 8
        BorderColor = clNone
        BorderHotColor = clBlack
        LookUp = False
        SelectionColor = 11899525
        SelectionTextColor = clWhite
        Text = '8'
        Version = '2.0.0.0'
        DropDownListColor = clWindow
      end
      object ToolButton33: TToolButton
        Left = 182
        Top = 0
        Width = 8
        Caption = 'ToolButton33'
        ImageIndex = 0
        Style = tbsSeparator
      end
      object ToolButton38: TToolButton
        Left = 190
        Top = 0
        Action = dmDgrEditorActions.acBold
      end
      object ToolButton39: TToolButton
        Left = 213
        Top = 0
        Action = dmDgrEditorActions.acItalic
      end
      object ToolButton40: TToolButton
        Left = 236
        Top = 0
        Action = dmDgrEditorActions.acUnderline
      end
      object ToolButton41: TToolButton
        Left = 259
        Top = 0
        Width = 8
        Caption = 'ToolButton41'
        ImageIndex = 3
        Style = tbsSeparator
      end
      object ToolButton42: TToolButton
        Left = 267
        Top = 0
        Action = dmDgrEditorActions.acAlignLeft
      end
      object ToolButton43: TToolButton
        Left = 290
        Top = 0
        Action = dmDgrEditorActions.acAlignCenter
      end
      object ToolButton44: TToolButton
        Left = 313
        Top = 0
        Action = dmDgrEditorActions.acAlignRight
      end
      object ToolButton45: TToolButton
        Left = 336
        Top = 0
        Width = 8
        Caption = 'ToolButton45'
        ImageIndex = 6
        Style = tbsSeparator
      end
      object ToolButton46: TToolButton
        Left = 344
        Top = 0
        Action = dmDgrEditorActions.acVertAlignTop
      end
      object ToolButton47: TToolButton
        Left = 367
        Top = 0
        Action = dmDgrEditorActions.acVertAlignMiddle
      end
      object ToolButton48: TToolButton
        Left = 390
        Top = 0
        Action = dmDgrEditorActions.acVertAlignBottom
      end
    end
    object ToolBar4: TToolBar
      Left = 11
      Top = 28
      Width = 341
      Height = 22
      Align = alNone
      AutoSize = True
      Caption = 'ToolBar2'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      object DgrColorSelector2: TDgrColorSelector
        Left = 0
        Top = 0
        Width = 36
        Height = 22
        Hint = 'Shape color'
        TabOrder = 0
        Version = '2.0.0.0'
        SelectedColor = clWhite
        ShowRGBHint = True
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        DropDownButton = True
        Glyph.Data = {
          3E020000424D3E0200000000000036000000280000000D0000000D0000000100
          1800000000000802000000000000000000000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFFFFFFFF0000007B7B7B000000FFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFF0000007B7B7B7B7B7B7B7B7B00
          0000FFFFFFFFFFFFFFFFFF7B7B7BFFFFFF00FFFFFFFFFFFF000000BDBDBDBDBD
          BDBDBDBD7B7B7B7B7B7B000000FFFFFFFFFFFF7B00007B7B7B00FFFFFF000000
          FFFFFFBDBDBDBDBDBDBDBDBDBDBDBD7B7B7B7B7B7B000000FFFFFF7B00007B00
          0000000000BDBDBDFFFFFFFFFFFFBDBDBDBDBDBDBDBDBDBDBDBD7B7B7B7B7B7B
          7B00007B00007B000000FFFFFF000000BDBDBDFFFFFFFFFFFFBDBDBD000000BD
          BDBDBDBDBD7B7B7B7B00007B00007B000000FFFFFFFFFFFF000000BDBDBDFFFF
          FF0000007B0000000000BDBDBD7B00007B00007B00007B000000FFFFFFFFFFFF
          FFFFFF000000BDBDBDFFFFFF7B0000BDBDBD7B7B7B7B00007B00007B0000FFFF
          FF00FFFFFFFFFFFFFFFFFF7B0000000000BDBDBD7B00007B7B7B0000007B7B7B
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFF7B0000FFFFFF0000007B000000
          00007B7B7BFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFF7B0000FFFF
          FFFFFFFF7B00007B7B7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFF7B7B7B7B00007B00007B7B7BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00}
        Style = ssButton
        ShowMoreColors = False
      end
      object DgrGradientDirectionSelector2: TDgrGradientDirectionSelector
        Left = 36
        Top = 0
        Width = 36
        Height = 22
        Hint = 'Gradient'
        TabOrder = 1
        Version = '2.0.0.0'
        ShowSelectedGradient = True
        StartColor = clWhite
        EndColor = clGray
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        DropDownButton = True
        Style = ssButton
        SelectedIndex = -1
      end
      object DgrBrushStyleSelector2: TDgrBrushStyleSelector
        Left = 72
        Top = 0
        Width = 23
        Height = 22
        Hint = 'Brush style'
        TabOrder = 2
        Version = '2.0.0.0'
        BrushAutoColor = True
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        Glyph.Data = {
          B6030000424DB603000000000000360000002800000012000000100000000100
          18000000000080030000C40E0000C40E00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFA2B0B5575F6763757CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF96ADB750
          68704078902038408E98A0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9EB2BC60708060B8D040A8C03090B0
          2038408F99A1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
          FFFFFFFFFFFF98B3C37090A080D0E070D0E060B8D040A8C03090B0203840919A
          A2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFAFCDD280B8
          C090D8E080E0F080D8F070D0E060B8D040A8C03090B0304050BCBDC0FFFFFFFF
          FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFBDD8E490C0D0B0E8F0C0F8FFA0E8F090
          E0F080D8F070D0E060B8D06098A0605850504840B3B4B3FFFFFFFFFFFFFFFFFF
          0000FFFFFFFFFFFF90D0E0B0E8F0C0FFFFC0FFFFB0F8FFB0F0FF90E0F080D8F0
          80B8C0606060808080606060504840FFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
          A0D8E0C0F8FFC0FFFFC0FFFFC0FFFFC0FFFFB0F8FF90C8D0807880A098A08078
          70707070505040FFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFF9AC4D380B8
          C0B0F0F0C0FFFFC0FFFFB0E0E0A0A0A0E0E0E0908880B0A8B0505050918993E5
          E9EBFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFDFE6E992BAC880B0C0B0
          D8E0B0B0B0F0E8F0D0C8C0E0D8E0808080806060674A4AB6B4B6E6EAECFFFFFF
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCDD8DDB0B0B0E0E0E0D0C8D0
          E0E0E0A0A0A0C09890D06060903840684A4AB8B5B6FFFFFF0000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD2D4D5B0B0B0B0B0B0B0B0B0CFC7C4B088
          90D09090D06060903840684A4AFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDAC9CBC09090E09090B0
          6870806870FFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE0D8D7C29595C08890FFFFFFFFFFFF
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000}
        Style = ssButton
        SelectedIndex = -1
      end
      object DgrShadowSelector2: TDgrShadowSelector
        Left = 95
        Top = 0
        Width = 36
        Height = 22
        Hint = 'Shadow'
        TabOrder = 3
        Version = '2.0.0.0'
        ShowSettingsOption = True
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        DropDownButton = True
        Glyph.Data = {
          3E020000424D3E0200000000000036000000280000000D0000000D0000000100
          18000000000008020000C40E0000C40E00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00FFFFFF509050607060607060506050304030202820101810101810101810
          101810101810FFFFFF00FFFFFF50905070C08060A86060A06050986050905050
          8850508050507850407040101810FFFFFF00FFFFFF60986080C08070C08070B8
          7060B07060A86060A060509850509040507850101810FFFFFF00FFFFFF609860
          80C89080C08070C08070B87060B07060A86060A060509850508050101810FFFF
          FF00FFFFFF60987090D09080C89080C08070C08070B87060B07060A86060A060
          508850101810FFFFFF00FFFFFF70A070A0D0A090D09080C89080C08070C08070
          B87060B07060A860509050202820FFFFFF00FFFFFF70A880B0D8B0A0D0A090D0
          9080C89080C08070C08070B87060B070509860304030FFFFFF00FFFFFF80B080
          B0E0C0B0D8B0A0D0A090D09080C89080C08070C08070B87060A060506050FFFF
          FF00FFFFFF80B890C0E0C0B0E0C0B0D8B0A0D0A090D09080C89080C08070C080
          60A860607060FFFFFF00FFFFFF80C090C0E0C0C0E0C0B0E0C0B0D8B0A0D0A090
          D09080C89080C08070C080607060FFFFFF00FFFFFF90C8A080C09080B89080B0
          8070A88070A070609870609860609860509050509050FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00}
        Style = ssButton
        SelectedIndex = -1
      end
      object DgrPenStyleSelector2: TDgrPenStyleSelector
        Left = 131
        Top = 0
        Width = 23
        Height = 22
        Hint = 'Line style'
        TabOrder = 4
        Version = '2.0.0.0'
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        Glyph.Data = {
          7E030000424D7E030000000000003600000028000000130000000E0000000100
          18000000000048030000C40E0000C40E00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFF000000FFFFFFFFFF
          FF000000000000FFFFFFFFFFFF000000FFFFFFFFFFFF000000000000FFFFFFFF
          FFFF000000FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFF000000FFFFFFFFFFFF000000000000000000FFFFFF0000000000000000
          00FFFFFF000000000000000000FFFFFF000000000000000000FFFFFFFFFFFF00
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFF
          000000FFFFFF000000FFFFFF000000FFFFFF000000FFFFFF000000FFFFFF0000
          00FFFFFF000000FFFFFF000000FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFF000000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          00FFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
          0000}
        Style = ssButton
        SelectedIndex = -1
      end
      object DgrPenColorSelector2: TDgrPenColorSelector
        Left = 154
        Top = 0
        Width = 36
        Height = 22
        Hint = 'Line color'
        TabOrder = 5
        Version = '2.0.0.0'
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        DropDownButton = True
        Glyph.Data = {
          3E020000424D3E0200000000000036000000280000000D0000000D0000000100
          1800000000000802000000000000000000000000000000000000FF00FF000000
          7B00007B00007B00007B7B7BFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FF00FF00FFFF00FF000000FFFFFF7B00007B00007B0000FF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FF00FF00FFFF00FFFF00FF000000FFFFFF7B00007B00007B
          0000FF00FFFF00FFFF00FFFF00FFFF00FF00FF00FFFF00FFFF00FF000000FFFF
          FF7B00007B00007B00007B0000FF00FFFF00FFFF00FFFF00FF00FF00FFFF00FF
          FF00FFFF00FF000000FFFFFF7B00007B00007B00007B0000FF00FFFF00FFFF00
          FF00FF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFF7B00007B00007B0000
          FF00FFFF00FFFF00FF00FF00FFFF00FFFF00FFFF00FFFF00FF000000FFFFFFFF
          FFFF7B00007B0000FF00FFFF00FFFF00FF00FF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FF000000000000000000000000FF00FFFF00FFFF00FF00FF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FF7B7B7B00000000FFFF00FFFF000000FF00FFFF00
          FF00FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF00000000FFFF00FFFF
          000000FF00FFFF00FF00FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
          00FF00000000FFFF00FFFF000000FF00FF00FF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF00FF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FF00}
        SelectedColor = clBlack
        Style = ssButton
        ShowMoreColors = False
      end
      object DgrTransparencySelector2: TDgrTransparencySelector
        Left = 190
        Top = 0
        Width = 36
        Height = 22
        Hint = #36879#26126#24230
        TabOrder = 9
        Version = '2.0.0.0'
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        DropDownButton = True
        Glyph.Data = {
          36030000424D3603000000000000360000002800000010000000100000000100
          1800000000000003000000000000000000000000000000000000FF00FFFF00FF
          FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
          FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFA05020A05020A0
          5020A05020A05020A05020A05020A05020A05020A05020FF00FFFF00FFFF00FF
          FF00FFFF00FFFF00FFA05020FFA880FFA870FFA070FFA070FF9870FF9860FF98
          60FF9060A05020FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFA05020FFB080FF
          A880FFA870FFA070FFA070FF9870FF9860FF9860A05020FF00FFFF00FFFF00FF
          CDE2E71088C01088C01088C01088C01088C01088C0F0A880FFA070FFA070FFA0
          70FF9860A05020FF00FFFF00FFC1DFE61088C070D8F060D0F07098A090C0D090
          C0C090B8C01088C0E0A890FFA070FFA070FFA070A05020FF00FFE2EDE91088C0
          80E0F080E0F070D8F080A0A0A0C8D090C0D090C0C090C0C01088C0F0A880FFA8
          70FFA070A05020FF00FF45A7C790E8F090E0F080E0F080E0F080A0A0A0C8D0A0
          C8D0A0C0D090C0C090C0C01088C0FFA880FFA870A05020FF00FF1088C0A0E8F0
          90E8F090E8F080E0F090A0A0B0D0D0A0C8D0A0C8D0A0C0D090C0C01088C0FFB0
          80FFA880A05020FF00FF1088C0A0F0F0A0E8F090E8F090E8F090A8A0B0D0D0B0
          D0D0A0C8D0A0C8D0A0C8D01088C0FFB080FFB080A05020FF00FF1088C0B0F0F0
          A0F0F0A0E8F0A0E8F090A8A090A8A090A8A080A0A080A0A080A0A01088C0A050
          20A05020A05020FF00FF1088C0B0F0F0B0F0F0A0F0F0A0E8F0A0E8F090E8F090
          E0F080E0F070D8F070D8F01088C0FF00FFFF00FFFF00FFFF00FF39A2C4B0F0F0
          B0F0F0B0F0F0A0F0F0A0E8F0A0E8F090E8F090E0F080E0F080E0F045A7C7FF00
          FFFF00FFFF00FFFF00FFD3E3E71088C0B0F0F0B0F0F0B0F0F0A0F0F0A0F0F0A0
          E8F090E8F090E0F01088C0CDE2E7FF00FFFF00FFFF00FFFF00FFFF00FFC6E4E6
          1088C0B0F0F0B0F0F0B0F0F0B0F0F0A0F0F0A0E8F01088C0C1E2E6FF00FFFF00
          FFFF00FFFF00FFFF00FFFF00FFFF00FFD3E3E7399BC41088C01088C01088C010
          88C039A2C4D0E3E7FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF}
        Style = ssButton
        SelectedIndex = -1
      end
      object DgrZoomSelector2: TDgrZoomSelector
        Left = 226
        Top = 0
        Width = 56
        Height = 22
        Button.Color = clWhite
        Button.ColorTo = 13226453
        Button.ColorHot = 13811126
        Button.ColorHotTo = 13811126
        Button.ColorDown = 11899525
        Button.ColorDownTo = 11899525
        Button.Width = 12
        DisplayRecentSelection = False
        DropDownCount = 8
        BorderColor = clNone
        BorderHotColor = clBlack
        LookUp = False
        SelectionColor = 11899525
        SelectionTextColor = clWhite
        Version = '2.0.0.0'
        DropDownListColor = clWindow
      end
      object DgrPenWidthSelector2: TDgrPenWidthSelector
        Left = 282
        Top = 0
        Width = 23
        Height = 22
        Hint = #32447#23485#24230
        TabOrder = 6
        Version = '2.0.0.0'
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        Glyph.Data = {
          A6020000424DA6020000000000003600000028000000110000000C0000000100
          18000000000070020000C40E0000C40E00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFF000000000000000000000000000000
          000000000000000000000000000000000000000000000000000000000000FFFF
          FF00FFFFFF000000000000000000000000000000000000000000000000000000
          000000000000000000000000000000000000FFFFFF00FFFFFF00000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          000000000000FFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFF0000000000000000000000
          0000000000000000000000000000000000000000000000000000000000000000
          0000FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
          00000000000000000000000000000000000000000000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00FFFFFF000000000000000000000000000000000000000000000000000000
          000000000000000000000000000000000000FFFFFF00FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00}
        Style = ssButton
        SelectedIndex = -1
      end
      object DgrTextColorSelector2: TDgrTextColorSelector
        Left = 305
        Top = 0
        Width = 36
        Height = 22
        Hint = 'Text color'
        TabOrder = 7
        Version = '2.0.0.0'
        AutoThemeAdapt = False
        BorderDownColor = 7021576
        BorderHotColor = clBlack
        Color = clBtnFace
        ColorDown = 11900292
        ColorHot = 14073525
        ColorDropDown = 16251129
        ColorSelected = 14604246
        ColorSelectedTo = clNone
        DropDownButton = True
        Glyph.Data = {
          3E020000424D3E0200000000000036000000280000000D0000000D0000000100
          18000000000008020000C40E0000C40E00000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00FFFFFFA87D6885513A766049FFFFFFFFFFFFFFFFFFFFFFFF603820704020
          70402067422BFFFFFF00FFFFFFDCDDDD94603AFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFF70382076422BFFFFFFFFFFFF00FFFFFFFFFFFFB58A74A47B5DFFFF
          FFFFFFFFFFFFFFFFFFFF804830704020936E5EFFFFFFFFFFFF00FFFFFFFFFFFF
          DBD6D4A058409F6C529265529F6C5294583A804830703820FFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFFAC795FFFFFFFFFFFFFFFFFFF95603B905030986F5E
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFCBB9ABAC795FFFFFFFD4C5BC90
          5830905030D0C3BCFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFA468
          4AE3E2E2A073529050309A6246FFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFC59980BB9480A06040905030CDBBB2FFFFFFFFFFFFFFFFFFFFFF
          FF00FFFFFFFFFFFFFFFFFFFFFFFFE6E5E5B07050B07050A4684AFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC08870B07050E3
          D5CCFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFBF8F77FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FF00}
        SelectedColor = clWindowText
        Style = ssButton
        ShowMoreColors = False
      end
    end
  end
  object TabControl1: TTabControl
    Left = 0
    Top = 82
    Width = 829
    Height = 57
    Align = alTop
    TabOrder = 2
    Tabs.Strings = (
      'All objects')
    TabIndex = 0
    ExplicitTop = 83
    object DiagramToolBar1: TDiagramToolBar
      Left = 4
      Top = 24
      Width = 821
      Height = 29
      KeepInsertingMode = kmNever
      Mode = tmObjects
      ButtonSize = 29
    end
  end
  object FLeftDockPanel: TPanel
    Left = 0
    Top = 139
    Width = 180
    Height = 363
    Align = alLeft
    BevelOuter = bvNone
    DockSite = True
    ParentColor = True
    TabOrder = 3
    OnDockDrop = DockPanelDockDrop
    OnUnDock = DockPanelUnDock
    ExplicitTop = 140
    ExplicitHeight = 362
  end
  object FRightDockPanel: TPanel
    Left = 649
    Top = 139
    Width = 180
    Height = 363
    Align = alRight
    BevelOuter = bvNone
    DockSite = True
    ParentColor = True
    TabOrder = 4
    OnDockDrop = DockPanelDockDrop
    OnUnDock = DockPanelUnDock
    ExplicitTop = 140
    ExplicitHeight = 362
  end
  object MainMenu1: TMainMenu
    Images = dmDgrEditorActions.ImageList1
    Left = 104
    Top = 120
    object File1: TMenuItem
      Caption = '&File'
      object Newdiagram1: TMenuItem
        Action = dmDgrEditorActions.acNewDiagram
      end
      object Opendiagram1: TMenuItem
        Action = dmDgrEditorActions.acOpenDiagram
      end
      object Savediagram1: TMenuItem
        Action = dmDgrEditorActions.acSaveDiagram
      end
      object Saveas1: TMenuItem
        Action = dmDgrEditorActions.acSaveDiagramAs
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object PageSetup1: TMenuItem
        Action = dmDgrEditorActions.acPageSetup
      end
      object Preview1: TMenuItem
        Action = dmDgrEditorActions.acPreviewDiagram
      end
      object Print1: TMenuItem
        Action = dmDgrEditorActions.acPrintDiagram
      end
    end
    object Edit2: TMenuItem
      Caption = '&Edit'
      object Undo1: TMenuItem
        Action = dmDgrEditorActions.DiagramUndoAction1
      end
      object DiagramRedoAction11: TMenuItem
        Action = dmDgrEditorActions.DiagramRedoAction1
      end
      object N10: TMenuItem
        Caption = '-'
      end
      object Cut1: TMenuItem
        Action = dmDgrEditorActions.DiagramCut1
      end
      object Copy1: TMenuItem
        Action = dmDgrEditorActions.DiagramCopy1
      end
      object Paste1: TMenuItem
        Action = dmDgrEditorActions.DiagramPaste1
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Delete1: TMenuItem
        Action = dmDgrEditorActions.DiagramDelete1
      end
      object Selectall1: TMenuItem
        Action = dmDgrEditorActions.DiagramSelectAll1
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Background1: TMenuItem
        Caption = #32972#26223
        object Loadpicture1: TMenuItem
          Action = dmDgrEditorActions.acBackgroundLoad
        end
        object Clear1: TMenuItem
          Action = dmDgrEditorActions.acBackgroundClear
        end
      end
      object Copyasimage1: TMenuItem
        Action = dmDgrEditorActions.acCopyAsImage
      end
    end
    object View1: TMenuItem
      Caption = '&View'
      object Leftruler1: TMenuItem
        Action = dmDgrEditorActions.DiagramViewLeftRuler1
      end
      object Topruler1: TMenuItem
        Action = dmDgrEditorActions.DiagramViewTopRuler1
      end
      object Grid1: TMenuItem
        Action = dmDgrEditorActions.DiagramGrid1
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Zoom1: TMenuItem
        Caption = '&Zoom'
        object N1001: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom3
        end
        object N5: TMenuItem
          Caption = '-'
        end
        object N3001: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom1
        end
        object N1501: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom2
        end
        object N751: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom4
        end
        object N501: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom5
        end
        object N251: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom6
        end
        object N101: TMenuItem
          Action = dmDgrEditorActions.DiagramSetZoom7
        end
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object Automaticnodes1: TMenuItem
        Action = dmDgrEditorActions.acAutomaticNodes
      end
      object N14: TMenuItem
        Caption = '-'
      end
      object Layermanager1: TMenuItem
        Action = acViewLayerManager
      end
      object Librarymanager1: TMenuItem
        Action = acViewLibraryManager
      end
      object Diagramobjects1: TMenuItem
        Action = acViewDiagramObjects
      end
    end
    object Edittext1: TMenuItem
      Caption = '&Object'
      object Shapecolor1: TMenuItem
        Action = dmDgrEditorActions.DiagramShapeColor1
      end
      object Linecolor1: TMenuItem
        Action = dmDgrEditorActions.DiagramLineColor1
      end
      object Gradient1: TMenuItem
        Action = dmDgrEditorActions.DiagramGradientSetting1
      end
      object Picture1: TMenuItem
        Action = dmDgrEditorActions.DiagramBlockPicture1
      end
      object Sourcearrow2: TMenuItem
        Action = dmDgrEditorActions.acHasSourceArrow
        object None3: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape1
        end
        object Solidarrow3: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape2
        end
        object Linearrow3: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape3
        end
        object Ellipse3: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape4
        end
        object Rectangle3: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape5
        end
        object Diamond3: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape6
        end
      end
      object argetarrow2: TMenuItem
        Action = dmDgrEditorActions.acHasTargetArrow
        object None4: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape7
        end
        object Solidarrow4: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape8
        end
        object Linearrow4: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape9
        end
        object Ellipse4: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape10
        end
        object Rectangle4: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape11
        end
        object Diamond4: TMenuItem
          Action = dmDgrEditorActions.DiagramArrowShape12
        end
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object Font1: TMenuItem
        Action = dmDgrEditorActions.DiagramControlFont1
      end
      object Edit1: TMenuItem
        Action = dmDgrEditorActions.DiagramEditText1
      end
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 208
    Top = 120
    object Group1: TMenuItem
      Action = dmDgrEditorActions.acGroup
    end
    object Ungroup1: TMenuItem
      Action = dmDgrEditorActions.acUngroup
    end
    object N12: TMenuItem
      Caption = '-'
    end
    object DiagramShapeColor11: TMenuItem
      Action = dmDgrEditorActions.DiagramShapeColor1
    end
    object DiagramLineColor11: TMenuItem
      Action = dmDgrEditorActions.DiagramLineColor1
    end
    object DiagramBlockPicture11: TMenuItem
      Action = dmDgrEditorActions.DiagramBlockPicture1
    end
    object N13: TMenuItem
      Caption = '-'
    end
    object AddtoLibrary1: TMenuItem
      Action = dmDgrEditorActions.acAddLibrary
    end
    object N9: TMenuItem
      Caption = '-'
    end
    object Font2: TMenuItem
      Action = dmDgrEditorActions.DiagramControlFont1
    end
    object Edittext2: TMenuItem
      Action = dmDgrEditorActions.DiagramEditText1
    end
    object N8: TMenuItem
      Caption = '-'
    end
    object DiagramBringToFront11: TMenuItem
      Action = dmDgrEditorActions.DiagramBringToFront1
    end
    object DiagramSendToBack11: TMenuItem
      Action = dmDgrEditorActions.DiagramSendToBack1
    end
    object N7: TMenuItem
      Caption = '-'
    end
    object Sourcearrow1: TMenuItem
      Action = dmDgrEditorActions.acHasSourceArrow
      object None1: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape1
      end
      object Solidarrow1: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape2
      end
      object Linearrow1: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape3
      end
      object Ellipse1: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape4
      end
      object Rectangle1: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape5
      end
      object Diamond1: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape6
      end
    end
    object argetarrow1: TMenuItem
      Action = dmDgrEditorActions.acHasTargetArrow
      object None2: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape7
      end
      object Solidarrow2: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape8
      end
      object Linearrow2: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape9
      end
      object Ellipse2: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape10
      end
      object Rectangle2: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape11
      end
      object Diamond2: TMenuItem
        Action = dmDgrEditorActions.DiagramArrowShape12
      end
    end
  end
  object ActionList1: TActionList
    Left = 440
    Top = 64
    object acViewLayerManager: TAction
      Caption = #22270#23618#31649#29702#22120
      OnExecute = acViewLayerManagerExecute
      OnUpdate = acViewLayerManagerUpdate
    end
    object acViewLibraryManager: TAction
      Caption = #24211#31649#29702#22120
      OnExecute = acViewLibraryManagerExecute
      OnUpdate = acViewLibraryManagerUpdate
    end
    object acViewDiagramObjects: TAction
      Caption = #22270#24418#23545#35937
      OnExecute = acViewDiagramObjectsExecute
      OnUpdate = acViewDiagramObjectsUpdate
    end
  end
end
