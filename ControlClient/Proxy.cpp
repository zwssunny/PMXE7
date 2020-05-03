//
// Created by the DataSnap proxy generator.
// 2014-06-10 11:46:02
//

#include "Proxy.h"

TJSONArray* __fastcall TServerControlMethodsClient::GetServerList()
{
  if (FGetServerListCommand == NULL)
  {
    FGetServerListCommand = FDBXConnection->CreateCommand();
    FGetServerListCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FGetServerListCommand->Text = "TServerControlMethods.GetServerList";
    FGetServerListCommand->Prepare();
  }
  FGetServerListCommand->ExecuteUpdate();
  TJSONArray* result = (TJSONArray*)FGetServerListCommand->Parameters->Parameter[0]->Value->GetJSONValue(FInstanceOwner);
  return result;
}

TJSONObject* __fastcall TServerControlMethodsClient::GetServerInfo(System::UnicodeString ServerName)
{
  if (FGetServerInfoCommand == NULL)
  {
    FGetServerInfoCommand = FDBXConnection->CreateCommand();
    FGetServerInfoCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FGetServerInfoCommand->Text = "TServerControlMethods.GetServerInfo";
    FGetServerInfoCommand->Prepare();
  }
  FGetServerInfoCommand->Parameters->Parameter[0]->Value->SetWideString(ServerName);
  FGetServerInfoCommand->ExecuteUpdate();
  TJSONObject* result = (TJSONObject*)FGetServerInfoCommand->Parameters->Parameter[1]->Value->GetJSONValue(FInstanceOwner);
  return result;
}

int __fastcall TServerControlMethodsClient::GetServerStatus(System::UnicodeString ServerName)
{
  if (FGetServerStatusCommand == NULL)
  {
    FGetServerStatusCommand = FDBXConnection->CreateCommand();
    FGetServerStatusCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FGetServerStatusCommand->Text = "TServerControlMethods.GetServerStatus";
    FGetServerStatusCommand->Prepare();
  }
  FGetServerStatusCommand->Parameters->Parameter[0]->Value->SetWideString(ServerName);
  FGetServerStatusCommand->ExecuteUpdate();
  int result = FGetServerStatusCommand->Parameters->Parameter[1]->Value->GetInt32();
  return result;
}

bool __fastcall TServerControlMethodsClient::StartServer(System::UnicodeString ServerName)
{
  if (FStartServerCommand == NULL)
  {
    FStartServerCommand = FDBXConnection->CreateCommand();
    FStartServerCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FStartServerCommand->Text = "TServerControlMethods.StartServer";
    FStartServerCommand->Prepare();
  }
  FStartServerCommand->Parameters->Parameter[0]->Value->SetWideString(ServerName);
  FStartServerCommand->ExecuteUpdate();
  bool result = FStartServerCommand->Parameters->Parameter[1]->Value->GetBoolean();
  return result;
}

bool __fastcall TServerControlMethodsClient::StopServer(System::UnicodeString ServerName)
{
  if (FStopServerCommand == NULL)
  {
    FStopServerCommand = FDBXConnection->CreateCommand();
    FStopServerCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FStopServerCommand->Text = "TServerControlMethods.StopServer";
    FStopServerCommand->Prepare();
  }
  FStopServerCommand->Parameters->Parameter[0]->Value->SetWideString(ServerName);
  FStopServerCommand->ExecuteUpdate();
  bool result = FStopServerCommand->Parameters->Parameter[1]->Value->GetBoolean();
  return result;
}

bool __fastcall TServerControlMethodsClient::RegServer(System::UnicodeString ServerName)
{
  if (FRegServerCommand == NULL)
  {
    FRegServerCommand = FDBXConnection->CreateCommand();
    FRegServerCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FRegServerCommand->Text = "TServerControlMethods.RegServer";
    FRegServerCommand->Prepare();
  }
  FRegServerCommand->Parameters->Parameter[0]->Value->SetWideString(ServerName);
  FRegServerCommand->ExecuteUpdate();
  bool result = FRegServerCommand->Parameters->Parameter[1]->Value->GetBoolean();
  return result;
}

bool __fastcall TServerControlMethodsClient::UnregServer(System::UnicodeString ServerName)
{
  if (FUnregServerCommand == NULL)
  {
    FUnregServerCommand = FDBXConnection->CreateCommand();
    FUnregServerCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FUnregServerCommand->Text = "TServerControlMethods.UnregServer";
    FUnregServerCommand->Prepare();
  }
  FUnregServerCommand->Parameters->Parameter[0]->Value->SetWideString(ServerName);
  FUnregServerCommand->ExecuteUpdate();
  bool result = FUnregServerCommand->Parameters->Parameter[1]->Value->GetBoolean();
  return result;
}

bool __fastcall TServerControlMethodsClient::RebootComputer()
{
  if (FRebootComputerCommand == NULL)
  {
    FRebootComputerCommand = FDBXConnection->CreateCommand();
    FRebootComputerCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FRebootComputerCommand->Text = "TServerControlMethods.RebootComputer";
    FRebootComputerCommand->Prepare();
  }
  FRebootComputerCommand->ExecuteUpdate();
  bool result = FRebootComputerCommand->Parameters->Parameter[0]->Value->GetBoolean();
  return result;
}

bool __fastcall TServerControlMethodsClient::ShutdownComputer()
{
  if (FShutdownComputerCommand == NULL)
  {
    FShutdownComputerCommand = FDBXConnection->CreateCommand();
    FShutdownComputerCommand->CommandType = TDBXCommandTypes_DSServerMethod;
    FShutdownComputerCommand->Text = "TServerControlMethods.ShutdownComputer";
    FShutdownComputerCommand->Prepare();
  }
  FShutdownComputerCommand->ExecuteUpdate();
  bool result = FShutdownComputerCommand->Parameters->Parameter[0]->Value->GetBoolean();
  return result;
}


__fastcall  TServerControlMethodsClient::TServerControlMethodsClient(TDBXConnection *ADBXConnection)
{
  if (ADBXConnection == NULL)
    throw EInvalidOperation("Connection cannot be nil.  Make sure the connection has been opened.");
  FDBXConnection = ADBXConnection;
  FInstanceOwner = True;
}


__fastcall  TServerControlMethodsClient::TServerControlMethodsClient(TDBXConnection *ADBXConnection, bool AInstanceOwner)
{
  if (ADBXConnection == NULL)
    throw EInvalidOperation("Connection cannot be nil.  Make sure the connection has been opened.");
  FDBXConnection = ADBXConnection;
  FInstanceOwner = AInstanceOwner;
}


__fastcall  TServerControlMethodsClient::~TServerControlMethodsClient()
{
  delete FGetServerListCommand;
  delete FGetServerInfoCommand;
  delete FGetServerStatusCommand;
  delete FStartServerCommand;
  delete FStopServerCommand;
  delete FRegServerCommand;
  delete FUnregServerCommand;
  delete FRebootComputerCommand;
  delete FShutdownComputerCommand;
}


