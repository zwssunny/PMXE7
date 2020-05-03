object fmRunWorkflowEditor: TfmRunWorkflowEditor
  Left = 517
  Top = 152
  ActiveControl = cbWorkflowDefinition
  Caption = 'Run workflow'
  ClientHeight = 300
  ClientWidth = 410
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
  DesignSize = (
    410
    300)
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 5
    Top = 5
    Width = 390
    Height = 250
    ActivePage = tsGeneral
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object tsGeneral: TTabSheet
      Caption = 'General'
      DesignSize = (
        382
        222)
      object lbWorkflowDefinition: TLabel
        Left = 5
        Top = 5
        Width = 92
        Height = 13
        Caption = 'Workflow definition'
      end
      object lbVariableMapping: TLabel
        Left = 5
        Top = 47
        Width = 81
        Height = 13
        Caption = 'Variable mapping'
      end
      object cbWorkflowDefinition: TComboBox
        Left = 5
        Top = 20
        Width = 370
        Height = 21
        Style = csDropDownList
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        TabOrder = 0
        OnChange = cbWorkflowDefinitionChange
      end
      object grVariableMapping: TStringGrid
        Left = 5
        Top = 62
        Width = 370
        Height = 132
        Anchors = [akLeft, akTop, akRight, akBottom]
        ColCount = 2
        DefaultColWidth = 170
        DefaultRowHeight = 19
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing]
        TabOrder = 1
        OnSelectCell = grVariableMappingSelectCell
      end
      object chWaitExecution: TCheckBox
        Left = 5
        Top = 199
        Width = 200
        Height = 17
        Anchors = [akLeft, akBottom]
        Caption = 'Wait until finished'
        TabOrder = 2
      end
    end
  end
  object btCancel: TButton
    Left = 320
    Top = 260
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
    Top = 260
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Ok'
    Default = True
    TabOrder = 1
    OnClick = btOkClick
  end
end
