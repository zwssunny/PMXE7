object DMServerContainer: TDMServerContainer
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  OnDestroy = DataModuleDestroy
  Height = 435
  Width = 591
  object FSDSServer: TDSServer
    OnConnect = FSDSServerConnect
    AutoStart = False
    Left = 96
    Top = 19
  end
  object FSDSHTTPService: TDSHTTPService
    HttpPort = 8080
    Server = FSDSServer
    Filters = <>
    AuthenticationManager = FSDSAuthenticationManager
    Left = 96
    Top = 143
  end
  object FSDSAuthenticationManager: TDSAuthenticationManager
    OnUserAuthenticate = FSDSAuthenticationManagerUserAuthenticate
    Roles = <>
    Left = 96
    Top = 197
  end
  object SysADOConnection: TADOConnection
    LoginPrompt = False
    AfterConnect = SysADOConnectionAfterConnect
    AfterDisconnect = SysADOConnectionAfterDisconnect
    Left = 216
    Top = 72
  end
  object SysADOQuery: TADOQuery
    Connection = SysADOConnection
    Parameters = <>
    Left = 216
    Top = 136
  end
  object TrialTimer: TTimer
    Enabled = False
    Interval = 30000
    Left = 304
    Top = 16
  end
  object ADOConnTimer: TTimer
    Interval = 60000
    OnTimer = ADOConnTimerTimer
    Left = 304
    Top = 80
  end
  object DSLoginUser: TDSServerClass
    OnGetClass = DSLoginUserGetClass
    Server = FSDSServer
    Left = 304
    Top = 144
  end
  object DSSyAccBook: TDSServerClass
    OnGetClass = DSSyAccBookGetClass
    Server = FSDSServer
    LifeCycle = 'Server'
    Left = 304
    Top = 208
  end
  object DSServerDataSet: TDSServerClass
    OnGetClass = DSServerDataSetGetClass
    Server = FSDSServer
    LifeCycle = 'Invocation'
    Left = 216
    Top = 16
  end
  object DSServerQuery: TDSServerClass
    OnGetClass = DSServerQueryGetClass
    Server = FSDSServer
    Left = 216
    Top = 200
  end
  object FSDSServerMetaDataProvider: TDSServerMetaDataProvider
    Server = FSDSServer
    Left = 416
    Top = 16
  end
  object FSDSProxyGenerator: TDSProxyGenerator
    MetaDataProvider = FSDSServerMetaDataProvider
    TargetUnitName = 'jsproxy.js'
    TargetDirectory = 'proxy'
    Writer = 'Java Script REST'
    Left = 416
    Top = 72
  end
  object FSDSHTTPServiceProxyDispatcher: TDSHTTPServiceProxyDispatcher
    Service = FSDSHTTPService
    WebFileExtensions = <
      item
        MimeType = 'application/x-zip-compressed'
        Extensions = 'zip'
      end>
    WebDirectories = <
      item
        DirectoryAction = dirInclude
        DirectoryMask = '\Proxy\*'
      end
      item
        DirectoryAction = dirExclude
        DirectoryMask = '\Proxy\*\*'
      end>
    DSProxyGenerator = FSDSProxyGenerator
    Left = 416
    Top = 136
  end
  object FSDSHTTPServiceFileDispatcher: TDSHTTPServiceFileDispatcher
    Service = FSDSHTTPService
    WebFileExtensions = <
      item
        MimeType = 'text/css'
        Extensions = 'css'
      end
      item
        MimeType = 'text/html'
        Extensions = 'html;htm'
      end
      item
        MimeType = 'text/javascript'
        Extensions = 'js'
      end
      item
        MimeType = 'image/jpeg'
        Extensions = 'jpeg;jpg'
      end
      item
        MimeType = 'image/x-png'
        Extensions = 'png'
      end>
    WebDirectories = <
      item
        DirectoryAction = dirInclude
        DirectoryMask = '*'
      end
      item
        DirectoryAction = dirExclude
        DirectoryMask = '\templates\*'
      end>
    Left = 424
    Top = 208
  end
  object FSDSTCPServerTransport: TDSTCPServerTransport
    Server = FSDSServer
    Filters = <>
    AuthenticationManager = FSDSAuthenticationManager
    KeepAliveEnablement = kaEnabled
    Left = 96
    Top = 88
  end
  object DSJSeverDataSet: TDSServerClass
    OnGetClass = DSJSeverDataSetGetClass
    Server = FSDSServer
    LifeCycle = 'Invocation'
    Left = 304
    Top = 272
  end
  object DSJServerQuery: TDSServerClass
    OnGetClass = DSJServerQueryGetClass
    Server = FSDSServer
    Left = 424
    Top = 280
  end
  object DSWorkFlowServer: TDSServerClass
    OnGetClass = DSWorkFlowServerGetClass
    Server = FSDSServer
    Left = 88
    Top = 272
  end
  object DSMessageManage: TDSServerClass
    OnGetClass = DSMessageManageGetClass
    Server = FSDSServer
    Left = 80
    Top = 352
  end
  object DSContractProject: TDSServerClass
    OnGetClass = DSContractProjectGetClass
    Server = FSDSServer
    Left = 208
    Top = 352
  end
  object AccADOConnection: TADOConnection
    LoginPrompt = False
    Left = 432
    Top = 352
  end
  object DSHouseView: TDSServerClass
    OnGetClass = DSHouseViewGetClass
    Server = FSDSServer
    Left = 208
    Top = 272
  end
  object DSSendUserMessage: TDSServerClass
    OnGetClass = DSSendUserMessageGetClass
    Server = FSDSServer
    Left = 312
    Top = 352
  end
end
