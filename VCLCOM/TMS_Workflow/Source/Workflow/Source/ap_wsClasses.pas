{***************************************************************************}
{ This source code was generated automatically by                           }
{ Pas file import tool for Scripter Studio                                  }
{                                                                           }
{ Scripter Studio and Pas file import tool for Scripter Studio              }
{ written by Automa / TMS Software                                          }
{            copyright © 1997 - 2003                                        }
{            Email : info@tmssoftware.com                                   }
{            Web : http://www.tmssoftware.com                               }
{***************************************************************************}
unit ap_wsClasses;

interface

uses
  Windows,
  SysUtils,
  Messages,
  Classes,
  Dialogs,
  Controls,
  Graphics,
  Forms,
  DB,
  atDiagram,
  LiveDiagram,
  wsClasses,
  wsDiagram,
  atScript;

type
  TatwsClassesLibrary = class(TatScripterLibrary)
    procedure __GetTWorkflowDefinitionDiagram(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowDefinitionName(AMachine: TatVirtualMachine);
    procedure __SetTWorkflowDefinitionName(AMachine: TatVirtualMachine);
    procedure __TWorkflowDefinitionsAdd(AMachine: TatVirtualMachine);
    procedure __TWorkflowDefinitionsFindByName(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowDefinitionsItems(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowInstanceDiagram(AMachine: TatVirtualMachine);
    procedure __TWorkflowVariablesAdd(AMachine: TatVirtualMachine);
    procedure __TWorkflowVariablesFindByName(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowVariablesItems(AMachine: TatVirtualMachine);
    procedure __TAttachmentItemLoadContentFromFile(AMachine: TatVirtualMachine);
    procedure __TAttachmentItemSaveContentToFile(AMachine: TatVirtualMachine);
    procedure __TAttachmentItemOpen(AMachine: TatVirtualMachine);
    procedure __GetTAttachmentItemExtension(AMachine: TatVirtualMachine);
    procedure __TAttachmentItemsAdd(AMachine: TatVirtualMachine);
    procedure __TAttachmentItemsFindByName(AMachine: TatVirtualMachine);
    procedure __TAttachmentItemsAddFile(AMachine: TatVirtualMachine);
    procedure __GetTAttachmentItemsItems(AMachine: TatVirtualMachine);
    procedure __TWorkflowAttachmentsAdd(AMachine: TatVirtualMachine);
    procedure __TWorkflowAttachmentsFindByName(AMachine: TatVirtualMachine);
    procedure __TWorkflowAttachmentsAddFile(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowAttachmentsItems(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowDiagramWorkflowInstance(AMachine: TatVirtualMachine);
    procedure __TTaskFieldAssign(AMachine: TatVirtualMachine);
    procedure __TTaskFieldsAdd(AMachine: TatVirtualMachine);
    procedure __GetTTaskFieldsItems(AMachine: TatVirtualMachine);
    procedure __TTaskDefinitionIsCompletionStatus(AMachine: TatVirtualMachine);
    procedure __GetTTaskDefinitionInitialStatus(AMachine: TatVirtualMachine);
    procedure __TTaskDefinitionsAdd(AMachine: TatVirtualMachine);
    procedure __TTaskDefinitionsFindByName(AMachine: TatVirtualMachine);
    procedure __GetTTaskDefinitionsItems(AMachine: TatVirtualMachine);
    procedure __TTaskInstanceIsCompletionStatus(AMachine: TatVirtualMachine);
    procedure __GetTTaskInstanceCompleted(AMachine: TatVirtualMachine);
    procedure __TWorkflowScriptEngineCalculateExpression(AMachine: TatVirtualMachine);
    procedure __TWorkflowScriptEngineTranslateText(AMachine: TatVirtualMachine);
    procedure __TWorkflowUsersFindById(AMachine: TatVirtualMachine);
    procedure __TWorkflowUsersFindByName(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowUsersItems(AMachine: TatVirtualMachine);
    procedure __TWorkflowGroupsFindByName(AMachine: TatVirtualMachine);
    procedure __GetTWorkflowGroupsItems(AMachine: TatVirtualMachine);
    procedure Init; override;
    class function LibraryName: string; override;
  end;

  EWorkflowExceptionClass = class of EWorkflowException;
  TWorkflowDefinitionClass = class of TWorkflowDefinition;
  TWorkflowDefinitionsClass = class of TWorkflowDefinitions;
  TWorkflowInstanceClass = class of TWorkflowInstance;
  TWorkflowVariableClass = class of TWorkflowVariable;
  TWorkflowVariablesClass = class of TWorkflowVariables;
  TAttachmentItemClass = class of TAttachmentItem;
  TAttachmentItemsClass = class of TAttachmentItems;
  TWorkflowAttachmentClass = class of TWorkflowAttachment;
  TWorkflowAttachmentsClass = class of TWorkflowAttachments;
  TWorkflowDiagramClass = class of TWorkflowDiagram;
  TTaskFieldClass = class of TTaskField;
  TTaskFieldsClass = class of TTaskFields;
  TTaskDefinitionClass = class of TTaskDefinition;
  TTaskDefinitionsClass = class of TTaskDefinitions;
  TTaskInstanceClass = class of TTaskInstance;
  TWorkflowScriptEngineClass = class of TWorkflowScriptEngine;
  TWorkflowUserClass = class of TWorkflowUser;
  TWorkflowUsersClass = class of TWorkflowUsers;
  TWorkflowGroupClass = class of TWorkflowGroup;
  TWorkflowGroupsClass = class of TWorkflowGroups;


  TEmailInformationWrapper = class(TatRecordWrapper)
  private
    FToAddr: string;
    FFrom: string;
    FBcc: string;
    FCc: string;
    FSubject: string;
    FText: string;
  public
    constructor Create(ARecord: TEmailInformation);
    function ObjToRec: TEmailInformation;
  published
    property ToAddr: string read FToAddr write FToAddr;
    property From: string read FFrom write FFrom;
    property Bcc: string read FBcc write FBcc;
    property Cc: string read FCc write FCc;
    property Subject: string read FSubject write FSubject;
    property Text: string read FText write FText;
  end;
  

implementation

{$WARNINGS OFF}

constructor TEmailInformationWrapper.Create(ARecord: TEmailInformation);
begin
  inherited Create;
  FToAddr := ARecord.ToAddr;
  FFrom := ARecord.From;
  FBcc := ARecord.Bcc;
  FCc := ARecord.Cc;
  FSubject := ARecord.Subject;
  FText := ARecord.Text;
end;

function TEmailInformationWrapper.ObjToRec: TEmailInformation;
begin
  result.ToAddr := FToAddr;
  result.From := FFrom;
  result.Bcc := FBcc;
  result.Cc := FCc;
  result.Subject := FSubject;
  result.Text := FText;
end;



procedure TatwsClassesLibrary.__GetTWorkflowDefinitionDiagram(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowDefinition(CurrentObject).Diagram));
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowDefinitionName(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(TWorkflowDefinition(CurrentObject).Name);
  end;
end;

procedure TatwsClassesLibrary.__SetTWorkflowDefinitionName(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    TWorkflowDefinition(CurrentObject).Name:=GetInputArg(0);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowDefinitionsAdd(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowDefinitions(CurrentObject).Add);
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowDefinitionsFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowDefinitions(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowDefinitionsItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowDefinitions(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowInstanceDiagram(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowInstance(CurrentObject).Diagram));
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowVariablesAdd(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowVariables(CurrentObject).Add);
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowVariablesFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowVariables(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowVariablesItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowVariables(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__TAttachmentItemLoadContentFromFile(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    TAttachmentItem(CurrentObject).LoadContentFromFile(GetInputArg(0));
  end;
end;

procedure TatwsClassesLibrary.__TAttachmentItemSaveContentToFile(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    TAttachmentItem(CurrentObject).SaveContentToFile(GetInputArg(0));
  end;
end;

procedure TatwsClassesLibrary.__TAttachmentItemOpen(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    TAttachmentItem(CurrentObject).Open(GetInputArg(0),GetInputArg(1));
  end;
end;

procedure TatwsClassesLibrary.__GetTAttachmentItemExtension(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(TAttachmentItem(CurrentObject).Extension);
  end;
end;

procedure TatwsClassesLibrary.__TAttachmentItemsAdd(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TAttachmentItems(CurrentObject).Add);
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TAttachmentItemsFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TAttachmentItems(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TAttachmentItemsAddFile(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TAttachmentItems(CurrentObject).AddFile(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTAttachmentItemsItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TAttachmentItems(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowAttachmentsAdd(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowAttachments(CurrentObject).Add);
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowAttachmentsFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowAttachments(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowAttachmentsAddFile(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowAttachments(CurrentObject).AddFile(GetInputArg(0),GetInputArg(1)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowAttachmentsItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowAttachments(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowDiagramWorkflowInstance(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowDiagram(CurrentObject).WorkflowInstance));
  end;
end;

procedure TatwsClassesLibrary.__TTaskFieldAssign(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    TTaskField(CurrentObject).Assign(TPersistent(Integer(GetInputArg(0))));
  end;
end;

procedure TatwsClassesLibrary.__TTaskFieldsAdd(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TTaskFields(CurrentObject).Add);
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTTaskFieldsItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TTaskFields(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__TTaskDefinitionIsCompletionStatus(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := TTaskDefinition(CurrentObject).IsCompletionStatus(GetInputArg(0));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTTaskDefinitionInitialStatus(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(TTaskDefinition(CurrentObject).InitialStatus);
  end;
end;

procedure TatwsClassesLibrary.__TTaskDefinitionsAdd(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TTaskDefinitions(CurrentObject).Add);
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TTaskDefinitionsFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TTaskDefinitions(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTTaskDefinitionsItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TTaskDefinitions(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__TTaskInstanceIsCompletionStatus(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := TTaskInstance(CurrentObject).IsCompletionStatus(GetInputArg(0));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTTaskInstanceCompleted(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(TTaskInstance(CurrentObject).Completed);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowScriptEngineCalculateExpression(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := TWorkflowScriptEngine(CurrentObject).CalculateExpression(GetInputArg(0));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowScriptEngineTranslateText(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := TWorkflowScriptEngine(CurrentObject).TranslateText(GetInputArg(0));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowUsersFindById(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowUsers(CurrentObject).FindById(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowUsersFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowUsers(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowUsersItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowUsers(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.__TWorkflowGroupsFindByName(AMachine: TatVirtualMachine);
  var
  AResult: variant;
begin
  with AMachine do
  begin
AResult := Integer(TWorkflowGroups(CurrentObject).FindByName(GetInputArg(0)));
    ReturnOutputArg(AResult);
  end;
end;

procedure TatwsClassesLibrary.__GetTWorkflowGroupsItems(AMachine: TatVirtualMachine);
begin
  with AMachine do
  begin
    ReturnOutputArg(Integer(TWorkflowGroups(CurrentObject).Items[VarToInteger(GetArrayIndex(0))]));
  end;
end;

procedure TatwsClassesLibrary.Init;
begin
  With Scripter.DefineClass(EWorkflowException) do
  begin
  end;
  With Scripter.DefineClass(TWorkflowDefinition) do
  begin
    DefineProp('Diagram',tkClass,__GetTWorkflowDefinitionDiagram,nil,TWorkflowDiagram,false,0);
    DefineProp('Name',tkVariant,__GetTWorkflowDefinitionName,__SetTWorkflowDefinitionName,nil,false,0);
  end;
  With Scripter.DefineClass(TWorkflowDefinitions) do
  begin
    DefineMethod('Add',0,tkClass,TWorkflowDefinition,__TWorkflowDefinitionsAdd,false);
    DefineMethod('FindByName',1,tkClass,TWorkflowDefinition,__TWorkflowDefinitionsFindByName,false);
    DefineProp('Items',tkClass,__GetTWorkflowDefinitionsItems,nil,TWorkflowDefinition,false,1);
  end;
  With Scripter.DefineClass(TWorkflowInstance) do
  begin
    DefineProp('Diagram',tkClass,__GetTWorkflowInstanceDiagram,nil,TWorkflowDiagram,false,0);
  end;
  With Scripter.DefineClass(TWorkflowVariable) do
  begin
  end;
  With Scripter.DefineClass(TWorkflowVariables) do
  begin
    DefineMethod('Add',0,tkClass,TWorkflowVariable,__TWorkflowVariablesAdd,false);
    DefineMethod('FindByName',1,tkClass,TWorkflowVariable,__TWorkflowVariablesFindByName,false);
    DefineProp('Items',tkClass,__GetTWorkflowVariablesItems,nil,TWorkflowVariable,false,1);
  end;
  With Scripter.DefineClass(TAttachmentItem) do
  begin
    DefineMethod('LoadContentFromFile',1,tkNone,nil,__TAttachmentItemLoadContentFromFile,false);
    DefineMethod('SaveContentToFile',1,tkNone,nil,__TAttachmentItemSaveContentToFile,false);
    DefineMethod('Open',2,tkNone,nil,__TAttachmentItemOpen,false);
    DefineProp('Extension',tkVariant,__GetTAttachmentItemExtension,nil,nil,false,0);
  end;
  With Scripter.DefineClass(TAttachmentItems) do
  begin
    DefineMethod('Add',0,tkClass,TAttachmentItem,__TAttachmentItemsAdd,false);
    DefineMethod('FindByName',1,tkClass,TAttachmentItem,__TAttachmentItemsFindByName,false);
    DefineMethod('AddFile',1,tkClass,TAttachmentItem,__TAttachmentItemsAddFile,false);
    DefineProp('Items',tkClass,__GetTAttachmentItemsItems,nil,TAttachmentItem,false,1);
  end;
  With Scripter.DefineClass(TWorkflowAttachment) do
  begin
  end;
  With Scripter.DefineClass(TWorkflowAttachments) do
  begin
    DefineMethod('Add',0,tkClass,TWorkflowAttachment,__TWorkflowAttachmentsAdd,false);
    DefineMethod('FindByName',1,tkClass,TWorkflowAttachment,__TWorkflowAttachmentsFindByName,false);
    DefineMethod('AddFile',2,tkClass,TAttachmentItem,__TWorkflowAttachmentsAddFile,false);
    DefineProp('Items',tkClass,__GetTWorkflowAttachmentsItems,nil,TWorkflowAttachment,false,1);
  end;
  With Scripter.DefineClass(TWorkflowDiagram) do
  begin
    DefineProp('WorkflowInstance',tkClass,__GetTWorkflowDiagramWorkflowInstance,nil,TWorkflowInstance,false,0);
  end;
  With Scripter.DefineClass(TTaskField) do
  begin
    DefineMethod('Assign',1,tkNone,nil,__TTaskFieldAssign,false);
  end;
  With Scripter.DefineClass(TTaskFields) do
  begin
    DefineMethod('Add',0,tkClass,TTaskField,__TTaskFieldsAdd,false);
    DefineProp('Items',tkClass,__GetTTaskFieldsItems,nil,TTaskField,false,1);
  end;
  With Scripter.DefineClass(TTaskDefinition) do
  begin
    DefineMethod('IsCompletionStatus',1,tkVariant,nil,__TTaskDefinitionIsCompletionStatus,false);
    DefineProp('InitialStatus',tkVariant,__GetTTaskDefinitionInitialStatus,nil,nil,false,0);
  end;
  With Scripter.DefineClass(TTaskDefinitions) do
  begin
    DefineMethod('Add',0,tkClass,TTaskDefinition,__TTaskDefinitionsAdd,false);
    DefineMethod('FindByName',1,tkClass,TTaskDefinition,__TTaskDefinitionsFindByName,false);
    DefineProp('Items',tkClass,__GetTTaskDefinitionsItems,nil,TTaskDefinition,false,1);
  end;
  With Scripter.DefineClass(TTaskInstance) do
  begin
    DefineMethod('IsCompletionStatus',1,tkVariant,nil,__TTaskInstanceIsCompletionStatus,false);
    DefineProp('Completed',tkVariant,__GetTTaskInstanceCompleted,nil,nil,false,0);
  end;
  With Scripter.DefineClass(TWorkflowScriptEngine) do
  begin
    DefineMethod('CalculateExpression',1,tkVariant,nil,__TWorkflowScriptEngineCalculateExpression,false);
    DefineMethod('TranslateText',1,tkVariant,nil,__TWorkflowScriptEngineTranslateText,false);
  end;
  With Scripter.DefineClass(TWorkflowUser) do
  begin
  end;
  With Scripter.DefineClass(TWorkflowUsers) do
  begin
    DefineMethod('FindById',1,tkClass,TWorkflowUser,__TWorkflowUsersFindById,false);
    DefineMethod('FindByName',1,tkClass,TWorkflowUser,__TWorkflowUsersFindByName,false);
    DefineProp('Items',tkClass,__GetTWorkflowUsersItems,nil,TWorkflowUser,false,1);
  end;
  With Scripter.DefineClass(TWorkflowGroup) do
  begin
  end;
  With Scripter.DefineClass(TWorkflowGroups) do
  begin
    DefineMethod('FindByName',1,tkClass,TWorkflowGroup,__TWorkflowGroupsFindByName,false);
    DefineProp('Items',tkClass,__GetTWorkflowGroupsItems,nil,TWorkflowGroup,false,1);
  end;
  With Scripter.DefineClass(ClassType) do
  begin
    AddConstant('wsNotStarted',wsNotStarted);
    AddConstant('wsRunning',wsRunning);
    AddConstant('wsFinished',wsFinished);
    AddConstant('apDelete',apDelete);
    AddConstant('apInsert',apInsert);
    AddConstant('apEdit',apEdit);
    AddConstant('scRuntimeInstance',scRuntimeInstance);
    AddConstant('scDesignDiagram',scDesignDiagram);
  end;
end;

class function TatwsClassesLibrary.LibraryName: string;
begin
  result := 'wsClasses';
end;

initialization
  RegisterScripterLibrary(TatwsClassesLibrary, True);

{$WARNINGS ON}

end.
