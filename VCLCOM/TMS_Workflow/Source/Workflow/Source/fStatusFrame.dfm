object frStatusFrame: TfrStatusFrame
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
    object lvStatus: TListView
      Left = 5
      Top = 5
      Width = 500
      Height = 111
      Align = alClient
      Columns = <>
      HideSelection = False
      TabOrder = 0
      ViewStyle = vsReport
      OnCustomDrawItem = lvStatusCustomDrawItem
      OnEdited = lvStatusEdited
      OnSelectItem = lvStatusSelectItem
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
    object lbStatusName: TLabel
      Left = 5
      Top = 13
      Width = 64
      Height = 13
      Caption = 'Status name:'
    end
    object edStatusName: TEdit
      Left = 100
      Top = 10
      Width = 405
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnChange = edStatusNameChange
    end
    object chCompletion: TCheckBox
      Left = 5
      Top = 37
      Width = 90
      Height = 17
      Caption = 'Completion'
      TabOrder = 1
      OnClick = PropertyChanged
    end
    object chHidden: TCheckBox
      Left = 100
      Top = 37
      Width = 90
      Height = 17
      Caption = 'Hidden'
      TabOrder = 2
      OnClick = PropertyChanged
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
