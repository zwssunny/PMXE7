object fmTransitionEditor: TfmTransitionEditor
  Left = 517
  Top = 152
  Width = 418
  Height = 187
  ActiveControl = cbTransition
  Caption = 'Transition'
  Color = clBtnFace
  Constraints.MinHeight = 160
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
    Width = 390
    Height = 110
    ActivePage = TabSheet1
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'General'
      object Label1: TLabel
        Left = 5
        Top = 5
        Width = 100
        Height = 13
        Caption = 'Condition expression'
      end
      object cbTransition: TComboBox
        Left = 5
        Top = 20
        Width = 372
        Height = 21
        Style = csDropDownList
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        TabOrder = 0
      end
    end
  end
  object btCancel: TButton
    Left = 320
    Top = 120
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btCancelClick
  end
  object btOk: TButton
    Left = 240
    Top = 120
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Ok'
    Default = True
    TabOrder = 1
    OnClick = btOkClick
  end
end
