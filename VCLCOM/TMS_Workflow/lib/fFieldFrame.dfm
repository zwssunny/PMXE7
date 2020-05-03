object frFieldFrame: TfrFieldFrame
  Left = 0
  Top = 0
  Width = 510
  Height = 393
  TabOrder = 0
  object Splitter1: TSplitter
    Left = 0
    Top = 155
    Width = 510
    Height = 3
    Cursor = crVSplit
    Align = alTop
  end
  object Panel1: TPanel
    Left = 0
    Top = 34
    Width = 510
    Height = 121
    Align = alTop
    BevelOuter = bvNone
    BorderWidth = 5
    TabOrder = 0
    object lvVars: TListView
      Left = 5
      Top = 5
      Width = 500
      Height = 111
      Align = alClient
      Columns = <>
      HideSelection = False
      TabOrder = 0
      ViewStyle = vsReport
      OnEdited = lvVarsEdited
      OnSelectItem = lvVarsSelectItem
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 158
    Width = 510
    Height = 235
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      510
      235)
    object Label1: TLabel
      Left = 5
      Top = 13
      Width = 64
      Height = 13
      Caption = 'Text caption:'
    end
    object Label2: TLabel
      Left = 5
      Top = 38
      Width = 90
      Height = 13
      Caption = 'Workflow variable:'
    end
    object edCaption: TEdit
      Left = 100
      Top = 10
      Width = 405
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnChange = edCaptionChange
    end
    object cbReadOnly: TCheckBox
      Left = 5
      Top = 60
      Width = 90
      Height = 17
      Caption = 'Read only'
      TabOrder = 2
      OnClick = PropertyChanged
    end
    object cbRequired: TCheckBox
      Left = 100
      Top = 60
      Width = 90
      Height = 17
      Caption = 'Required'
      TabOrder = 3
      OnClick = PropertyChanged
    end
    object cbVariable: TComboBox
      Left = 100
      Top = 35
      Width = 149
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      OnChange = PropertyChanged
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 510
    Height = 34
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    object btAdd: TButton
      Left = 5
      Top = 5
      Width = 60
      Height = 25
      Caption = 'Add'
      TabOrder = 0
      OnClick = btAddClick
    end
    object btDelete: TButton
      Left = 70
      Top = 5
      Width = 60
      Height = 25
      Caption = 'Delete'
      TabOrder = 1
      OnClick = btDeleteClick
    end
  end
end
