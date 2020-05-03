object fmAttachmentEditor: TfmAttachmentEditor
  Left = 280
  Top = 157
  Width = 618
  Height = 437
  Caption = 'Attachments'
  Color = clBtnFace
  Constraints.MinHeight = 200
  Constraints.MinWidth = 500
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
    Left = 195
    Top = 5
    Width = 400
    Height = 360
    ActivePage = tsAttachments
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    object tsAttachments: TTabSheet
      Caption = 'General'
      inline frItems: TfrAttachmentFrame
        Width = 392
        Height = 332
        Align = alClient
        inherited Panel1: TPanel
          Width = 364
          Height = 332
          inherited lvItems: TAttachmentListView
            Width = 354
            Height = 322
          end
        end
        inherited Panel2: TPanel
          Left = 364
          Height = 332
        end
      end
    end
  end
  object lvAttachs: TListView
    Left = 5
    Top = 35
    Width = 185
    Height = 326
    Anchors = [akLeft, akTop, akBottom]
    Columns = <>
    HideSelection = False
    TabOrder = 1
    ViewStyle = vsReport
    OnEdited = lvAttachsEdited
    OnSelectItem = lvAttachsSelectItem
  end
  object btAdd: TButton
    Left = 5
    Top = 5
    Width = 60
    Height = 25
    Caption = '&Add'
    TabOrder = 2
    OnClick = btAddClick
  end
  object btDelete: TButton
    Left = 71
    Top = 5
    Width = 60
    Height = 25
    Caption = '&Delete'
    TabOrder = 3
    OnClick = btDeleteClick
  end
  object btCancel: TButton
    Left = 520
    Top = 370
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 5
    OnClick = btCancelClick
  end
  object btOk: TButton
    Left = 440
    Top = 370
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Ok'
    Default = True
    TabOrder = 4
    OnClick = btOkClick
  end
end
