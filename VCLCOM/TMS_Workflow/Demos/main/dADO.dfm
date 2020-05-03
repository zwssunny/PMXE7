object dmADO: TdmADO
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Height = 379
  Width = 480
  object AccADOCon: TADOConnection
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'SQLNCLI.1'
    Left = 56
    Top = 88
  end
  object WorkflowAccAndSysDB1: TWorkflowAccAndSysDB
    AccConnection = AccADOCon
    SysConnection = SysADOCon
    Left = 96
    Top = 32
  end
  object SysADOCon: TADOConnection
    LoginPrompt = False
    Left = 144
    Top = 88
  end
end
