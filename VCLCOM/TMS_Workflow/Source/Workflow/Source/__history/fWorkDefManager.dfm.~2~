object fmWorkDefManager: TfmWorkDefManager
  Left = 415
  Top = 196
  Caption = 'Workflow definitions'
  ClientHeight = 291
  ClientWidth = 388
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
  OnCreate = FormCreate
  DesignSize = (
    388
    291)
  PixelsPerInch = 96
  TextHeight = 13
  object btAdd: TSpeedButton
    Left = 300
    Top = 5
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = '&Add'
    OnClick = btAddClick
  end
  object btEdit: TSpeedButton
    Left = 300
    Top = 35
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = '&Edit'
    OnClick = btEditClick
  end
  object btDelete: TSpeedButton
    Left = 300
    Top = 65
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = '&Delete'
    OnClick = btDeleteClick
  end
  object btRefresh: TSpeedButton
    Left = 300
    Top = 95
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = '&Refresh'
    OnClick = btRefreshClick
  end
  object btRunNew: TSpeedButton
    Left = 300
    Top = 125
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Run &new'
    OnClick = btRunNewClick
  end
  object lvWorks: TWorkDefListView
    Left = 5
    Top = 5
    Width = 290
    Height = 270
    Anchors = [akLeft, akTop, akRight, akBottom]
    Columns = <
      item
        Width = 250
      end>
    HideSelection = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    ViewStyle = vsReport
    OnDblClick = lvWorksDblClick
    OnEdited = lvWorksEdited
  end
  object PopupMenu1: TPopupMenu
    Left = 120
    Top = 96
    object Export1: TMenuItem
      Action = acExport
    end
    object Import1: TMenuItem
      Action = acImport
    end
  end
  object ActionList1: TActionList
    Left = 296
    Top = 168
    object acImport: TAction
      Caption = '&Import definition...'
      OnExecute = acImportExecute
    end
    object acExport: TAction
      Caption = 'E&xport selected definition...'
      OnExecute = acExportExecute
      OnUpdate = ItemSelectedUpdate
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '.wfd'
    Filter = 'Workflow definitions (*.wfd)|*.wfd'
    Options = [ofAllowMultiSelect, ofFileMustExist, ofEnableSizing]
    Title = 'Import workflow definition'
    Left = 144
    Top = 176
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '.wfd'
    Filter = 'Workflow definitions (*.wfd)|*.wfd'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Export workflow definition'
    Left = 176
    Top = 176
  end
end
