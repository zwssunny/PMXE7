object FSService: TFSService
  OldCreateOrder = False
  OnCreate = ServiceCreate
  DisplayName = 'Foresight XE/REST Server'
  BeforeInstall = ServiceBeforeInstall
  AfterInstall = ServiceAfterInstall
  BeforeUninstall = ServiceBeforeUninstall
  OnStart = ServiceStart
  Height = 150
  Width = 215
end
