object fmTaskEditor: TfmTaskEditor
  Left = 348
  Top = 133
  Caption = 'Tasks'
  ClientHeight = 483
  ClientWidth = 671
  Color = clBtnFace
  Constraints.MinHeight = 350
  Constraints.MinWidth = 500
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  DesignSize = (
    671
    483)
  PixelsPerInch = 96
  TextHeight = 13
  object btAdd: TSpeedButton
    Left = 5
    Top = 4
    Width = 60
    Height = 25
    Caption = '&Add'
    OnClick = btAddClick
  end
  object btDelete: TSpeedButton
    Left = 129
    Top = 4
    Width = 60
    Height = 25
    Caption = '&Delete'
    OnClick = btDeleteClick
  end
  object PageControl1: TPageControl
    Left = 195
    Top = 5
    Width = 461
    Height = 433
    ActivePage = tsGeneral
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 1
    object tsGeneral: TTabSheet
      Caption = 'General'
      DesignSize = (
        453
        405)
      object Label1: TLabel
        Left = 5
        Top = 5
        Width = 36
        Height = 13
        Caption = '&Subject'
      end
      object Label2: TLabel
        Left = 5
        Top = 45
        Width = 53
        Height = 13
        Caption = 'Description'
      end
      object edSubject: TEdit
        Left = 5
        Top = 20
        Width = 444
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
        OnChange = PropertyChanged
      end
      object mmComments: TMemo
        Left = 5
        Top = 60
        Width = 444
        Height = 100
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
        OnChange = PropertyChanged
      end
      object cbMailNotification: TCheckBox
        Left = 5
        Top = 166
        Width = 200
        Height = 17
        Caption = 'Send mail notification'
        TabOrder = 2
        OnClick = PropertyChanged
      end
      inline frAssignedUser: TfrAssignedUserFrame
        Left = 0
        Top = 185
        Width = 453
        Height = 220
        Align = alBottom
        TabOrder = 3
        ExplicitTop = 185
        ExplicitWidth = 453
        inherited Splitter1: TSplitter
          Width = 453
          ExplicitWidth = 474
        end
        inherited Panel1: TPanel
          Width = 453
          ExplicitWidth = 453
          inherited lvAssignedUsers: TListView
            Width = 443
            ExplicitWidth = 443
          end
        end
        inherited Panel2: TPanel
          Width = 453
          ExplicitWidth = 453
        end
        inherited Panel3: TPanel
          Width = 453
          ExplicitWidth = 453
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Status'
      ImageIndex = 1
      inline frStatus: TfrStatusFrame
        Left = 0
        Top = 0
        Width = 453
        Height = 405
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 453
        ExplicitHeight = 405
        inherited Splitter1: TSplitter
          Width = 453
          ExplicitWidth = 382
        end
        inherited Panel1: TPanel
          Width = 453
          ExplicitWidth = 453
          inherited lvStatus: TListView
            Width = 443
            ExplicitWidth = 443
          end
        end
        inherited Panel2: TPanel
          Width = 453
          Height = 247
          ExplicitWidth = 453
          ExplicitHeight = 247
          inherited edStatusName: TEdit
            Width = 348
            ExplicitWidth = 348
          end
        end
        inherited Panel3: TPanel
          Width = 453
          ExplicitWidth = 453
        end
      end
    end
    object tsAttachment: TTabSheet
      Caption = 'Attachments'
      ImageIndex = 2
      inline frPermissions: TfrAttachPermissions
        Left = 0
        Top = 0
        Width = 453
        Height = 405
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 453
        ExplicitHeight = 405
      end
    end
    object tsFields: TTabSheet
      Caption = 'Fields'
      ImageIndex = 3
      inline frFields: TfrFieldFrame
        Left = 0
        Top = 0
        Width = 453
        Height = 405
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 453
        ExplicitHeight = 405
        inherited Splitter1: TSplitter
          Width = 453
          ExplicitWidth = 382
        end
        inherited Panel1: TPanel
          Width = 453
          ExplicitWidth = 453
          inherited lvVars: TListView
            Width = 443
            ExplicitWidth = 443
          end
        end
        inherited Panel2: TPanel
          Width = 453
          Height = 247
          ExplicitWidth = 453
          ExplicitHeight = 247
          inherited edCaption: TEdit
            Width = 348
            ExplicitWidth = 348
          end
        end
        inherited Panel3: TPanel
          Width = 453
          ExplicitWidth = 453
        end
      end
    end
    object tsExpiration: TTabSheet
      Caption = 'Expiration'
      ImageIndex = 4
      inline frExpiration: TfrExpirationFrame
        Left = 0
        Top = 0
        Width = 453
        Height = 405
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 453
        ExplicitHeight = 405
        inherited edExpression: TEdit
          Width = 423
          ExplicitWidth = 423
        end
        inherited cbStatus: TComboBox
          Width = 443
          ExplicitWidth = 443
        end
      end
    end
  end
  object lvTasks: TListView
    Left = 5
    Top = 35
    Width = 185
    Height = 403
    Anchors = [akLeft, akTop, akBottom]
    Columns = <>
    HideSelection = False
    TabOrder = 0
    ViewStyle = vsReport
    OnEdited = lvTasksEdited
    OnSelectItem = lvTasksSelectItem
  end
  object btCancel: TButton
    Left = 581
    Top = 443
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = btCancelClick
  end
  object btOk: TButton
    Left = 501
    Top = 443
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    TabOrder = 2
    OnClick = btOkClick
  end
  object btCopy: TButton
    Left = 67
    Top = 4
    Width = 60
    Height = 25
    Caption = '(&C)'#22797#21046
    TabOrder = 4
    OnClick = btCopyClick
  end
end
