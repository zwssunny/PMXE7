object frExpirationFrame: TfrExpirationFrame
  Left = 0
  Top = 0
  Width = 300
  Height = 250
  TabOrder = 0
  DesignSize = (
    300
    250)
  object lbStatus: TLabel
    Left = 5
    Top = 170
    Width = 85
    Height = 13
    Caption = 'Expiration &status:'
    FocusControl = cbStatus
  end
  object rbExpNever: TRadioButton
    Left = 5
    Top = 5
    Width = 200
    Height = 17
    Caption = 'Task does &not expire'
    TabOrder = 0
    OnClick = rbExpCustomClick
  end
  object rbExpTerm: TRadioButton
    Left = 5
    Top = 25
    Width = 200
    Height = 17
    Caption = 'Expiration &term:'
    TabOrder = 1
    OnClick = rbExpCustomClick
  end
  object rbExpDate: TRadioButton
    Left = 5
    Top = 70
    Width = 200
    Height = 17
    Caption = 'Expiration dat&e/time:'
    TabOrder = 2
    OnClick = rbExpCustomClick
  end
  object rbExpCustom: TRadioButton
    Left = 5
    Top = 115
    Width = 200
    Height = 17
    Caption = '&Custom date/time expression:'
    TabOrder = 3
    OnClick = rbExpCustomClick
  end
  object edTerm: TEdit
    Left = 23
    Top = 42
    Width = 50
    Height = 21
    Enabled = False
    TabOrder = 4
    OnChange = edTermChange
  end
  object cbTermType: TComboBox
    Left = 74
    Top = 42
    Width = 140
    Height = 21
    Style = csDropDownList
    Enabled = False
    TabOrder = 5
    OnChange = edTermChange
    Items.Strings = (
      'days'
      'weeks'
      'months')
  end
  object edDate: TDateTimePicker
    Left = 23
    Top = 87
    Width = 100
    Height = 21
    Date = 40472.834951169000000000
    Time = 40472.834951169000000000
    Enabled = False
    TabOrder = 6
    OnChange = edTermChange
  end
  object edTime: TDateTimePicker
    Left = 124
    Top = 87
    Width = 90
    Height = 21
    Date = 40472.834951169000000000
    Time = 40472.834951169000000000
    Enabled = False
    Kind = dtkTime
    TabOrder = 7
    OnChange = edTermChange
  end
  object edExpression: TEdit
    Left = 23
    Top = 132
    Width = 270
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    Enabled = False
    TabOrder = 8
    OnChange = PropertyChanged
  end
  object cbStatus: TComboBox
    Left = 5
    Top = 185
    Width = 290
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 9
    OnChange = PropertyChanged
  end
end
