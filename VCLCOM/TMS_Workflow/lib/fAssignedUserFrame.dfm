object frAssignedUserFrame: TfrAssignedUserFrame
  Left = 0
  Top = 0
  Width = 510
  Height = 220
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
    object lvAssignedUsers: TListView
      Left = 5
      Top = 5
      Width = 500
      Height = 111
      Align = alClient
      Columns = <
        item
          Caption = #21517#31216
          Width = 150
        end
        item
          Caption = #27493#39588#21495
        end
        item
          Caption = #31867#22411
          Width = 100
        end
        item
          Caption = #33021#21542#25171#21360
          Width = 60
        end
        item
          Caption = #20219#21153#27169#24335
          Width = 60
        end
        item
          Caption = #39033#30446#26435#38480
          Width = 60
        end>
      HideSelection = False
      ReadOnly = True
      TabOrder = 0
      ViewStyle = vsReport
      OnSelectItem = lvAssignedUsersSelectItem
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 158
    Width = 510
    Height = 62
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Label3: TLabel
      Left = 8
      Top = 9
      Width = 36
      Height = 13
      Caption = #31867#22411#65306
    end
    object Label4: TLabel
      Left = 7
      Top = 36
      Width = 36
      Height = 13
      Caption = #21517#31216#65306
    end
    object Label2: TLabel
      Left = 142
      Top = 9
      Width = 48
      Height = 13
      Caption = #27493#39588#21495#65306
    end
    object cbAssAssignedUserType: TComboBox
      Left = 44
      Top = 6
      Width = 93
      Height = 21
      TabOrder = 0
      Text = #29992#25143
      OnChange = cbAssAssignedUserTypeChange
      Items.Strings = (
        #29992#25143
        #35282#33394
        #32844#20301
        #37096#38376
        #37096#38376#20027#31649)
    end
    object cbAssAssignedUsers: TComboBox
      Left = 44
      Top = 33
      Width = 183
      Height = 21
      TabOrder = 1
      OnChange = PropertyChanged
    end
    object cbCanPrint: TCheckBox
      Left = 264
      Top = 8
      Width = 97
      Height = 17
      Caption = #33021#21542#25171#21360
      TabOrder = 2
      OnClick = PropertyChanged
    end
    object cbkAssignmentMode: TCheckBox
      Left = 264
      Top = 35
      Width = 97
      Height = 17
      Caption = #22810#26465#20219#21153#27169#24335
      TabOrder = 3
      OnClick = PropertyChanged
    end
    object cbStepDefin: TEdit
      Left = 184
      Top = 6
      Width = 43
      Height = 21
      TabOrder = 4
      Text = '0'
      OnChange = PropertyChanged
      OnKeyPress = cbStepDefinKeyPress
    end
    object cbNeedPrjRight: TCheckBox
      Left = 341
      Top = 8
      Width = 97
      Height = 17
      Caption = #39033#30446#26435#38480#25511#21046
      TabOrder = 5
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
    object Label1: TLabel
      Left = 196
      Top = 15
      Width = 96
      Height = 13
      Caption = #20851#32852#25805#20316#29992#25143#21015#34920
    end
    object btAdd: TButton
      Left = 6
      Top = 7
      Width = 60
      Height = 25
      Caption = #22686#21152
      TabOrder = 0
      OnClick = btAddClick
    end
    object btDelete: TButton
      Left = 69
      Top = 7
      Width = 60
      Height = 25
      Caption = #21024#38500
      TabOrder = 1
      OnClick = btDeleteClick
    end
  end
end
