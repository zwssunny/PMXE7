object dmSQLConn: TdmSQLConn
  OldCreateOrder = False
  Height = 150
  Width = 215
  object SQLConnection2: TSQLConnection
    DriverName = 'Datasnap'
    LoginPrompt = False
    Params.Strings = (
      'DriverUnit=Data.DBXDataSnap'
      'HostName=localhost'
      'Port=211'
      'CommunicationProtocol=tcp/ip'
      'DatasnapContext=datasnap/'
      
        'DriverAssemblyLoader=Borland.Data.TDBXClientDriverLoader,Borland' +
        '.Data.DbxClientDriver,Version=16.0.0.0,Culture=neutral,PublicKey' +
        'Token=91d62ebb5b0d1b1b'
      'DSAuthenticationUser=FSAdmin'
      'DSAuthenticationPassword=fst123!@#')
    Left = 48
    Top = 32
    UniqueId = '{23E30604-D22B-466E-AF34-A0B7E5F3BD95}'
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    Left = 120
    Top = 32
  end
end
