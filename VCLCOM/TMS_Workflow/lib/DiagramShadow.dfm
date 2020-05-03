object ShadowEditor: TShadowEditor
  Left = 917
  Top = 160
  BorderStyle = bsSizeToolWin
  Caption = #38452#24433#32534#36753#22120
  ClientHeight = 233
  ClientWidth = 207
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 24
    Top = 48
    Width = 153
    Height = 97
    OnPaint = PaintBox1Paint
  end
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 48
    Height = 13
    Caption = #38452#24433#39068#33394
  end
  object UpDown1: TUpDown
    Left = 184
    Top = 80
    Width = 17
    Height = 25
    Min = -100
    Increment = -1
    TabOrder = 0
    OnChangingEx = UpDown1ChangingEx
  end
  object UpDown2: TUpDown
    Left = 96
    Top = 152
    Width = 17
    Height = 17
    Min = -100
    Orientation = udHorizontal
    TabOrder = 1
    OnChangingEx = UpDown2ChangingEx
  end
  object Panel1: TPanel
    Left = 88
    Top = 8
    Width = 105
    Height = 25
    TabOrder = 2
    OnClick = Panel1Click
    object PaintBox2: TPaintBox
      Left = 1
      Top = 1
      Width = 103
      Height = 23
      Align = alClient
      OnClick = Panel1Click
      OnPaint = PaintBox2Paint
    end
  end
  object Button1: TButton
    Left = 24
    Top = 192
    Width = 75
    Height = 25
    Caption = #30830#23450
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object Button2: TButton
    Left = 112
    Top = 192
    Width = 75
    Height = 25
    BiDiMode = bdLeftToRight
    Cancel = True
    Caption = #21462#28040
    ModalResult = 2
    ParentBiDiMode = False
    TabOrder = 4
  end
  object ColorDialog1: TColorDialog
    Left = 168
    Top = 160
  end
end
