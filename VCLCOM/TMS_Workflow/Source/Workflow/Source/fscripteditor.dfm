object fmScriptEditor: TfmScriptEditor
  Left = 362
  Top = 137
  Width = 518
  Height = 537
  ActiveControl = mmSourceCode
  Caption = 'Script'
  Color = clBtnFace
  Constraints.MinHeight = 200
  Constraints.MinWidth = 300
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 5
    Top = 5
    Width = 490
    Height = 460
    ActivePage = tsScript
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object tsScript: TTabSheet
      Caption = 'Script source'
      object mmSourceCode: TMemo
        Left = 0
        Top = 0
        Width = 482
        Height = 432
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
      end
    end
  end
  object btCancel: TButton
    Left = 420
    Top = 470
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btCancelClick
  end
  object btOk: TButton
    Left = 340
    Top = 470
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Ok'
    Default = True
    TabOrder = 1
    OnClick = btOkClick
  end
end
