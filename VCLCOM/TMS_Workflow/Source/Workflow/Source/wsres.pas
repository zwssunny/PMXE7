unit wsRes;

interface
uses SysUtils, Classes;

const
  {begin strings}
  SAttachment = 'SAttachment'; //Attachment         
  SConfirmDeleteItems = 'SConfirmDeleteItems'; //Are you sure you want to delete selected item(s)?
  SConfirmDeleteAttachments = 'SConfirmDeleteAttachments'; //Are you sure you want to remove the selected attachments?
  SConfirmOpenMoreThanOneFile = 'SConfirmOpenMoreThanOneFile'; //You request to open more than one file at the same time. Are you sure?
  SFileName = 'SFileName'; //File name
  SEnterStatusName = 'SEnterStatusName'; //Enter status name
  SEnterVariableCaption = 'SEnterVariableCaption'; //Enter variable caption
  SExpiration = 'SExpiration'; //Expiration
  SStatusList = 'SStatusList'; //Status list
  SVariables = 'SVariables'; //Variables
  STask = 'STask'; //Task
  SVariable = 'SVariable'; //Variable
  SColumnKey = 'SColumnKey'; //Key
  SColumnName = 'SColumnName'; //Name
  SColumnWorkflow = 'SColumnWorkflow'; //Workflow
  SColumnSubject = 'SColumnSubject'; //Subject
  SColumnStatus = 'SColumnStatus'; //Status
  SColumnUser = 'SColumnUser'; //User
  STabFields = 'STabFields'; //Fields
  STabTask = 'STabTask'; //Task
  STabWorkflow = 'STabWorkflow'; //Workflow
  STabLog = 'STabLog'; //Log
  SConfirmDeleteWorkDef = 'SConfirmDeleteWorkDef'; //Are you sure you want to delete the selected workflow definition?
  SConfirmCloseAndDiscard = 'SConfirmCloseAndDiscard'; //Close form and discard changes?
  SCurrentWorkflow = 'SCurrentWorkflow'; //Current workflow
  SModified = 'SModified'; //Modified
  SAllObjects = 'SAllObjects'; //All Objects
  SConfirmNewDiagramAndDiscard = 'SConfirmNewDiagramAndDiscard'; //Create new diagram and discard changes?
  SConfirmOpenDiagramAndDiscard = 'SConfirmOpenDiagramAndDiscard'; //Open new diagram and discard current changes?
  SWorkflowCorrect = 'SWorkflowCorrect'; //Workflow diagram is correct.
  SWorkflowDefinition = 'SWorkflowDefinition'; //Workflow definition
  STypeWorkDefName = 'STypeWorkDefName'; //Type the name of the workflow definition
  SErrorParamNotFound = 'SErrorParamNotFound'; //Cannot find param "%s" when opening workflow query.
  STrueOutput = 'STrueOutput'; //yes
  SFalseOutput = 'SFalseOutput'; //no
  SBlockStart = 'SBlockStart'; //START
  SBlockEnd = 'SBlockEnd'; //END
  SBlockTask = 'SBlockTask'; //Task block
  SBlockApproval = 'SBlockApproval'; //Approval block
  SBlockScript = 'SBlockScript'; //Script block
  STaskApprovalName = 'STaskApprovalName'; //Approval
  STaskApprovalSubject = 'STaskApprovalSubject'; //Approval
  STaskApprovalDescription = 'STaskApprovalDescription'; //Please approve or reject this.
  STaskApprovalStatusOpened = 'STaskApprovalStatusOpened'; //opened
  STaskApprovalStatusApproved = 'STaskApprovalStatusApproved'; //approved
  STaskApprovalStatusRejected = 'STaskApprovalStatusRejected'; //rejected
  SToolbarStart = 'SToolbarStart'; //Start
  SToolbarEnd = 'SToolbarEnd'; //End
  SToolbarError = 'SToolbarError'; //Error handler
  SToolbarSourceConnect = 'SToolbarSourceConnect'; //Source connector
  SToolbarTargetConnect = 'SToolbarTargetConnect'; //Target connector
  SToolbarLineJoin = 'SToolbarLineJoin'; //Line jointer
  SToolbarTransition = 'SToolbarTransition'; //Transition
  SToolbarSideTransition = 'SToolbarSideTransition'; //Side transition
  SToolbarArcTransition = 'SToolbarArcTransition'; //Arc transition
  SToolbarFork = 'SToolbarFork'; //Fork
  SToolbarJoin = 'SToolbarJoin'; //Join
  SToolbarTask = 'SToolbarTask'; //Task
  SToolbarApproval = 'SToolbarApproval'; //Approval
  SToolbarDecision = 'SToolbarDecision'; //Decision
  SToolbarWorkflowCategory = 'SToolbarWorkflowCategory'; //Workflow
  SToolbarRunWorkflow = 'SToolbarRunWorkflow'; //Run workflow
  SToolbarScript = 'SToolbarScript'; //Script
  SErrorFileAlreadyOpen = 'SErrorFileAlreadyOpen'; //File is already open.
  SConfirmUpdateModifiedAttachment = 'SConfirmUpdateModifiedAttachment'; //The file "%s" was modified. Do you want to update it in attachments?
  SWarningFieldValueRequired = 'SWarningFieldValueRequired'; //Value of "%s" is required.
  SErrorInsertCannotGetKey = 'SErrorInsertCannotGetKey'; //Error in %s insert. Cannot retrieve key.
  SErrorRecordNotFoundKey = 'SErrorRecordNotFoundKey'; //%s not found in database. Key: %s
  SErrorUpdateEmptyKey = 'SErrorUpdateEmptyKey'; //Cannot update %s in database. Empty key.
  SErrorDeleteEmptyKey = 'SErrorDeleteEmptyKey'; //Cannot delete %s from database. Empty key.
  SErrorUndefinedVariable = 'SErrorUndefinedVariable'; //Variable "%s" does not exist.
  SErrorScriptBlockCompile = 'SErrorScriptBlockCompile'; //Error while compiling script block.
  SLogColOperation = 'SLogColOperation'; //Operation
  SLogColDate = 'SLogColDate'; //Date
  SLogColTime = 'SLogColTime'; //Time
  SLogColUserId = 'SLogColUserId'; //User id
  SLogColInfo = 'SLogColInfo'; //Information
  STaskExpiredOn = 'STaskExpiredOn'; //Task expired on %s
  STaskLogCreate = 'STaskLogCreate'; //Create
  STaskLogInfo = 'STaskLogInfo'; //Info
  STaskLogUpdate = 'STaskLogUpdate'; //Update
  STaskLogStatusChange = 'STaskLogStatusChange'; //Status change
  SStatusChangeInfo = 'SStatusChangeInfo'; //from "%s" to "%s"
  SWorkInsExecutionError = 'SWorkInsExecutionError1'; //Error during workflow execution. Workflow instance finished.\#13#10\#13#10Error message: "%s"
  SWorkInsExecutionError2 = 'SWorkInsExecutionError2'; //%s\#13#10\#13#10Information about the block which caused the error:\#13#10Type: %s\#13#10Name: %s\#13#10Description: \#13#10"%s"
  SNextBlockUndefined = 'SNextBlockUndefined'; //Next block undefined. Cannot continue execution.
  STaskNotCreatedUserNotFound = 'STaskNotCreatedUserNotFound'; //A task instance could not be created because user/group "%s" does not exist.
  {end strings}

function _str(id: string): string;
procedure _ResAddStrings(str: string);

implementation
uses wsLanguage;

var
  wsResources: TStrings;

procedure CheckResources;
begin
  if wsResources = nil then
    wsResources := TStringList.Create;
end;

procedure _ResAddStrings(str: string);
var
  c: integer;
  SL: TStringList;
begin
  CheckResources;
  SL := TStringList.Create;
  SL.Text := str;
  try
    for c := 0 to SL.Count - 1 do
      wsResources.Add(SL[c]);
  finally
    SL.Free;
  end;
end;

function _str(id: string): string;
begin
  if wsResources.IndexOfName(id) > -1 then
    result := wsResources.Values[id]
  else
    result := id;
  result := StringReplace(result, '\#13#10', #13#10, [rfReplaceAll]);
end;

initialization
  CheckResources;
finalization
  if wsResources <> nil then
  begin
    wsResources.Free;
    wsResources := nil;
  end;

end.
 