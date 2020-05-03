unit wsLanguage;

interface

implementation
uses wsRes;

const LanguageStr = 
'[strings]' + #13#10 +
'SAttachment=Attachment         ' + #13#10 +
'SConfirmDeleteItems=Are you sure you want to delete selected item(s)?' + #13#10 +
'SConfirmDeleteAttachments=Are you sure you want to remove the selected attachments?' + #13#10 +
'SConfirmOpenMoreThanOneFile=You request to open more than one file at the same time. Are you sure?' + #13#10 +
'SCurrentWorkflow=Current workflow' + #13#10 + 
'SFileName=File name' + #13#10 +
'SEnterStatusName=Enter status name' + #13#10 +
'SEnterVariableCaption=Enter variable caption' + #13#10 +
'SExpiration=Expiration' + #13#10 +
'SStatusList=Status list' + #13#10 +
'SVariables=Variables' + #13#10 +
'STask=Task' + #13#10 +
'SVariable=Variable' + #13#10 +
'SColumnKey=Key' + #13#10 +
'SColumnName=Name' + #13#10 +
'SColumnWorkflow=Workflow' + #13#10 +
'SColumnSubject=Subject' + #13#10 +
'SColumnStatus=Status' + #13#10 +
'SColumnUser=User' + #13#10 +
'STabFields=Fields' + #13#10 +
'STabTask=Task' + #13#10 +
'STabWorkflow=Workflow' + #13#10 +
'STabLog=Log' + #13#10 +
'SConfirmDeleteWorkDef=Are you sure you want to delete the selected workflow definition?' + #13#10 +
'SConfirmCloseAndDiscard=Close form and discard changes?' + #13#10 +
'SModified=Modified' + #13#10 +
'SAllObjects=All Objects' + #13#10 +
'SConfirmNewDiagramAndDiscard=Create new diagram and discard changes?' + #13#10 +
'SConfirmOpenDiagramAndDiscard=Open new diagram and discard current changes?' + #13#10 +
'SWorkflowCorrect=Workflow diagram is correct.' + #13#10 +
'SWorkflowDefinition=Workflow definition' + #13#10 +
'STypeWorkDefName=Type the name of the workflow definition' + #13#10 +
'SErrorParamNotFound=Cannot find param "%s" when opening workflow query.' + #13#10 +
'STrueOutput=yes' + #13#10 +
'SFalseOutput=no' + #13#10 +
'SBlockStart=START' + #13#10 +
'SBlockEnd=END' + #13#10 +
'SBlockTask=Task block' + #13#10 +
'SBlockApproval=Approval block' + #13#10 +
'SBlockScript=Script block' + #13#10 +
'STaskApprovalName=Approval' + #13#10 +
'STaskApprovalSubject=Approval' + #13#10 +
'STaskApprovalDescription=Please approve or reject this.' + #13#10 +
'STaskApprovalStatusOpened=opened' + #13#10 +
'STaskApprovalStatusApproved=approved' + #13#10 +
'STaskApprovalStatusRejected=rejected' + #13#10 +
'SToolbarStart=Start' + #13#10 +
'SToolbarEnd=End' + #13#10 +
'SToolbarError=Error handler' + #13#10 +
'SToolbarSourceConnect=Source connector' + #13#10 +
'SToolbarTargetConnect=Target connector' + #13#10 +
'SToolbarLineJoin=Line jointer' + #13#10 +
'SToolbarTransition=Transition' + #13#10 +
'SToolbarSideTransition=Side transition' + #13#10 +
'SToolbarArcTransition=Arc transition' + #13#10 +
'SToolbarFork=Fork' + #13#10 +
'SToolbarJoin=Join' + #13#10 +
'SToolbarTask=Task' + #13#10 +
'SToolbarApproval=Approval' + #13#10 +
'SToolbarDecision=Decision' + #13#10 +
'SToolbarWorkflowCategory=Workflow' + #13#10 +
'SToolbarRunWorkflow=Run workflow' + #13#10 +
'SToolbarScript=Script' + #13#10 +
'SErrorFileAlreadyOpen=File is already open.' + #13#10 +
'SConfirmUpdateModifiedAttachment=The file "%s" was modified. Do you want to update it in attachments?' + #13#10 +
'SWarningFieldValueRequired=Value of "%s" is required.' + #13#10 +
'SErrorInsertCannotGetKey=Error in %s insert. Cannot retrieve key.' + #13#10 +
'SErrorRecordNotFoundKey=%s not found in database. Key: %s' + #13#10 +
'SErrorUpdateEmptyKey=Cannot update %s in database. Empty key.' + #13#10 +
'SErrorDeleteEmptyKey=Cannot delete %s from database. Empty key.' + #13#10 +
'SErrorUndefinedVariable=Variable "%s" does not exist.' + #13#10 +
'SErrorScriptBlockCompile=Error while compiling script block.' + #13#10 +
'SLogColOperation=Operation' + #13#10 +
'SLogColDate=Date' + #13#10 +
'SLogColTime=Time' + #13#10 +
'SLogColUserId=User id' + #13#10 +
'SLogColInfo=Information' + #13#10 +
'STaskExpiredOn=Task expired on %s' + #13#10 +
'STaskLogCreate=Create' + #13#10 +
'STaskLogInfo=Info' + #13#10 +
'STaskLogUpdate=Update' + #13#10 +
'STaskLogStatusChange=Status change' + #13#10 +
'SStatusChangeInfo=from "%s" to "%s"' + #13#10 +
'SWorkInsExecutionError1=Error during workflow execution. Workflow instance finished.\#13#10\#13#10Error message: "%s"' + #13#10 +
'SWorkInsExecutionError2=%s\#13#10\#13#10Information about the block which caused the error:\#13#10Type: %s\#13#10Name: %s\#13#10Description: \#13#10"%s"' + #13#10 +
'SNextBlockUndefined=Next block undefined. Cannot continue execution.' + #13#10 +
'STaskNotCreatedUserNotFound=A task instance could not be created because user/group "%s" does not exist.' + #13#10 +
'' + #13#10 +
'[fApprovalEditor]' + #13#10 +
'fmApprovalEditor.Self.Caption=Approval' + #13#10 +
'fmApprovalEditor.tsGeneral.Caption=General' + #13#10 +
'fmApprovalEditor.lbSubject.Caption=Subject' + #13#10 +
'fmApprovalEditor.lbDescription.Caption=Description' + #13#10 +
'fmApprovalEditor.lbAssignment.Caption=Assignment' + #13#10 +
'fmApprovalEditor.cbMailNotification.Caption=Send mail notification' + #13#10 +
'fmApprovalEditor.tsStatus.Caption=Status' + #13#10 +
'fmApprovalEditor.lbStatusList.Caption=Status list (start completion status with "*")' + #13#10 +
'fmApprovalEditor.tsAttachments.Caption=Attachments' + #13#10 +
'fmApprovalEditor.tsFields.Caption=Fields' + #13#10 +
'fmApprovalEditor.btCancel.Caption=Cancel' + #13#10 +
'fmApprovalEditor.btOk.Caption=&Ok' + #13#10 +
'fmApprovalEditor.tsExpiration.Caption=Expiration' + #13#10 +
'' + #13#10 +
'[fAttachmentEditor]' + #13#10 +
'fmAttachmentEditor.Self.Caption=Attachments' + #13#10 +
'fmAttachmentEditor.tsAttachments.Caption=General' + #13#10 +
'fmAttachmentEditor.btAdd.Caption=&Add' + #13#10 +
'fmAttachmentEditor.btDelete.Caption=&Delete' + #13#10 +
'fmAttachmentEditor.btCancel.Caption=Cancel' + #13#10 +
'fmAttachmentEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fAttachmentFrame]' + #13#10 +
'frAttachmentFrame.OpenDialog1.Filter=Todos os arquivos (*.*)|*.*' + #13#10 +
'frAttachmentFrame.OpenDialog1.Title=Insert attachment' + #13#10 +
'frAttachmentFrame.miOpen.Caption=&Open attachment...' + #13#10 +
'frAttachmentFrame.miInsert.Caption=&Insert attachment...' + #13#10 +
'frAttachmentFrame.miRemove.Caption=&Remove attachment' + #13#10 +
'frAttachmentFrame.acInsert.Hint=Insert attachment' + #13#10 +
'frAttachmentFrame.acRemove.Hint=Remove attachment' + #13#10 +
'frAttachmentFrame.acOpen.Hint=Open attachment' + #13#10 +
'frAttachmentFrame.acLargeIcons.Caption=Large icons' + #13#10 +
'frAttachmentFrame.acLargeIcons.Hint=Large icons' + #13#10 +
'frAttachmentFrame.acSmallIcons.Caption=Small icons' + #13#10 +
'frAttachmentFrame.acSmallIcons.Hint=Small icons' + #13#10 +
'frAttachmentFrame.acList.Caption=List' + #13#10 +
'frAttachmentFrame.acList.Hint=List' + #13#10 +
'frAttachmentFrame.acReport.Caption=Report' + #13#10 +
'frAttachmentFrame.acReport.Hint=Report' + #13#10 +
'' + #13#10 +
'[fAttachPermissions]' + #13#10 +
'frAttachPermissions.cbShowAttachments.Caption=Show attachments' + #13#10 +
'frAttachPermissions.cbDelAttachment.Caption=Allow remove attachments' + #13#10 +
'frAttachPermissions.cbInsAttachment.Caption=Allow insert attachments' + #13#10 +
'frAttachPermissions.cbEditAttachment.Caption=Allow edit attachments' + #13#10 +
'' + #13#10 +
'[fDecisionEditor]' + #13#10 +
'fmDecisionEditor.Self.Caption=Decision' + #13#10 +
'fmDecisionEditor.TabSheet1.Caption=General' + #13#10 +
'fmDecisionEditor.Label1.Caption=Condition expression' + #13#10 +
'fmDecisionEditor.btCancel.Caption=Cancel' + #13#10 +
'fmDecisionEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fExpirationFrame]' + #13#10 +
'frExpirationFrame.rbExpNever.Caption=Task does &not expire' + #13#10 +
'frExpirationFrame.rbExpTerm.Caption=Expiration &term:' + #13#10 +
'frExpirationFrame.cbTermType.Items0=days' + #13#10 +
'frExpirationFrame.cbTermType.Items1=weeks' + #13#10 +
'frExpirationFrame.cbTermType.Items2=months' + #13#10 +
'frExpirationFrame.rbExpDate.Caption=Expiration dat&e/time:' + #13#10 +
'frExpirationFrame.rbExpCustom.Caption=&Custom date/time expression:' + #13#10 +
'frExpirationFrame.lbStatus.Caption=Expiration &status:' + #13#10 +
'' + #13#10 +
'[fFieldFrame]' + #13#10 +
'frFieldFrame.Label1.Caption=Text caption:' + #13#10 +
'frFieldFrame.Label2.Caption=Workflow variable:' + #13#10 +
'frFieldFrame.cbReadOnly.Caption=Read only' + #13#10 +
'frFieldFrame.cbRequired.Caption=Required' + #13#10 +
'frFieldFrame.btAdd.Caption=Add' + #13#10 +
'frFieldFrame.btDelete.Caption=Delete' + #13#10 +
'' + #13#10 +
'[fStatusFrame]' + #13#10 +
'frStatusFrame.lbStatusName.Caption=Status name:' + #13#10 +
'frStatusFrame.chCompletion.Caption=Completion' + #13#10 +
'frStatusFrame.chHidden.Caption=Hidden' + #13#10 +
'frStatusFrame.btAdd.Caption=Add' + #13#10 +
'frStatusFrame.btDelete.Caption=Delete' + #13#10 +
'' + #13#10 +
'[fscripteditor]' + #13#10 +
'fmScriptEditor.Self.Caption=Script' + #13#10 +
'fmScriptEditor.tsScript.Caption=Script source' + #13#10 +
'fmScriptEditor.btCancel.Caption=Cancel' + #13#10 +
'fmScriptEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fTaskEditor]' + #13#10 +
'fmTaskEditor.Self.Caption=Tasks' + #13#10 +
'fmTaskEditor.tsGeneral.Caption=General' + #13#10 +
'fmTaskEditor.Label1.Caption=Subject' + #13#10 +
'fmTaskEditor.Label2.Caption=Description' + #13#10 +
'fmTaskEditor.Label3.Caption=Assignment' + #13#10 +
'fmTaskEditor.cbMailNotification.Caption=Send mail notification' + #13#10 +
'fmTaskEditor.TabSheet2.Caption=Status' + #13#10 +
'fmTaskEditor.Label4.Caption=Status list (start completion status with "*")' + #13#10 +
'fmTaskEditor.tsAttachment.Caption=Attachments' + #13#10 +
'fmTaskEditor.tsFields.Caption=Fields' + #13#10 +
'fmTaskEditor.btAdd.Caption=&Add' + #13#10 +
'fmTaskEditor.btDelete.Caption=&Delete' + #13#10 +
'fmTaskEditor.btCancel.Caption=Cancel' + #13#10 +
'fmTaskEditor.btOk.Caption=&Ok' + #13#10 +
'fmTaskEditor.tsExpiration.Caption=Expiration' + #13#10 +
'' + #13#10 +
'[fTaskInstanceView]' + #13#10 +
'frTaskInstanceView.Label1.Caption=Subject:' + #13#10 +
'frTaskInstanceView.Label2.Caption=Status:' + #13#10 +
'' + #13#10 +
'[ftasklist]' + #13#10 +
'fmTaskList.Self.Caption=Task list' + #13#10 +
'fmTaskList.btSaveChanges.Caption=&Save changes' + #13#10 +
'fmTaskList.acShowOnlyOpen.Caption=Show only open tasks' + #13#10 +
'fmTaskList.acShowAllTasks.Caption=Show all tasks' + #13#10 +
'fmTaskList.miView.Caption=&View' + #13#10 +
'' + #13#10 +
'[fTransitionEditor]' + #13#10 +
'fmTransitionEditor.Self.Caption=Transition' + #13#10 +
'fmTransitionEditor.TabSheet1.Caption=General' + #13#10 +
'fmTransitionEditor.Label1.Caption=Condition expression' + #13#10 +
'fmTransitionEditor.btCancel.Caption=Cancel' + #13#10 +
'fmTransitionEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fvariableeditor]' + #13#10 +
'fmVariableEditor.Self.Caption=Variables' + #13#10 +
'fmVariableEditor.TabSheet1.Caption=General' + #13#10 +
'fmVariableEditor.Label1.Caption=Value' + #13#10 +
'fmVariableEditor.btAdd.Caption=&Add' + #13#10 +
'fmVariableEditor.btDelete.Caption=&Delete' + #13#10 +
'fmVariableEditor.btCancel.Caption=Cancel' + #13#10 +
'fmVariableEditor.btOk.Caption=&Ok' + #13#10 +
'' + #13#10 +
'[fWorkDefManager]' + #13#10 +
'fmWorkDefManager.Self.Caption=Workflow definitions' + #13#10 +
'fmWorkDefManager.btAdd.Caption=&Add' + #13#10 +
'fmWorkDefManager.btEdit.Caption=&Edit' + #13#10 +
'fmWorkDefManager.btDelete.Caption=&Delete' + #13#10 +
'fmWorkDefManager.btRefresh.Caption=&Refresh' + #13#10 +
'fmWorkDefManager.btRunNew.Caption=Run &new' + #13#10 +
'fmWorkDefManager.acImport.Caption=&Import definition...' + #13#10 +
'fmWorkDefManager.acExport.Caption=E&xport selected definition...' + #13#10 +
'fmWorkDefManager.OpenDialog1.Filter=Workflow definitions (*.wfd)|*.wfd' + #13#10 +
'fmWorkDefManager.OpenDialog1.Title=Import workflow definition' + #13#10 +
'fmWorkDefManager.SaveDialog1.Filter=Workflow definitions (*.wfd)|*.wfd' + #13#10 +
'fmWorkDefManager.SaveDialog1.Title=Export workflow definition' + #13#10 +
'' + #13#10 +
'[fWorkflowEditor]' + #13#10 +
'fmWorkflowEditor.Self.Caption=Diagram Editor' + #13#10 +
'fmWorkflowEditor.ToolBar1.Caption=ToolBar1' + #13#10 +
'fmWorkflowEditor.btCheck.Caption=Check workflow' + #13#10 +
'fmWorkflowEditor.ToolBar2.Caption=ToolBar2' + #13#10 +
'fmWorkflowEditor.DgrColorSelector1.Hint=Shape color' + #13#10 +
'fmWorkflowEditor.DgrGradientDirectionSelector1.Hint=Gradient' + #13#10 +
'fmWorkflowEditor.DgrBrushStyleSelector1.Hint=Brush style' + #13#10 +
'fmWorkflowEditor.DgrShadowSelector1.Hint=Shadow' + #13#10 +
'fmWorkflowEditor.DgrPenStyleSelector1.Hint=Line style' + #13#10 +
'fmWorkflowEditor.DgrPenColorSelector1.Hint=Line color' + #13#10 +
'fmWorkflowEditor.DgrPenWidthSelector1.Hint=Line width' + #13#10 +
'fmWorkflowEditor.DgrTextColorSelector1.Hint=Text color' + #13#10 +
'fmWorkflowEditor.DiagramToolBar2.Category=Workflow' + #13#10 +
'fmWorkflowEditor.File1.Caption=&File' + #13#10 +
'fmWorkflowEditor.Edit2.Caption=&Edit' + #13#10 +
'fmWorkflowEditor.Copyasimage1.Caption=Cop&y as image' + #13#10 +
'fmWorkflowEditor.View1.Caption=&View' + #13#10 +
'fmWorkflowEditor.Zoom1.Caption=&Zoom' + #13#10 +
'fmWorkflowEditor.Edittext1.Caption=&Object' + #13#10 +
'fmWorkflowEditor.Sourcearrow2.Caption=Source arro&w' + #13#10 +
'fmWorkflowEditor.Targetarrow2.Caption=&Target arrow' + #13#10 +
'fmWorkflowEditor.Workflow1.Caption=&Workflow' + #13#10 +
'fmWorkflowEditor.Variables1.Caption=&Variables...' + #13#10 +
'fmWorkflowEditor.Attachments1.Caption=&Attachments...' + #13#10 +
'fmWorkflowEditor.DiagramCut1.Caption=Cu&t' + #13#10 +
'fmWorkflowEditor.DiagramCut1.Hint=Cut|Cut to clipboard' + #13#10 +
'fmWorkflowEditor.DiagramCopy1.Caption=&Copy' + #13#10 +
'fmWorkflowEditor.DiagramCopy1.Hint=Copy|Copy to clipboard' + #13#10 +
'fmWorkflowEditor.DiagramPaste1.Caption=&Paste' + #13#10 +
'fmWorkflowEditor.DiagramPaste1.Hint=Paste|Paste from clipboard' + #13#10 +
'fmWorkflowEditor.DiagramSelectAll1.Caption=Se&lect all' + #13#10 +
'fmWorkflowEditor.DiagramSelectAll1.Hint=Select all|Select all objects' + #13#10 +
'fmWorkflowEditor.DiagramDelete1.Caption=&Delete' + #13#10 +
'fmWorkflowEditor.DiagramDelete1.Hint=Delete objects|Delete selected objects' + #13#10 +
'fmWorkflowEditor.DiagramEditText1.Caption=Edit &text' + #13#10 +
'fmWorkflowEditor.DiagramEditText1.Hint=Edit text' + #13#10 +
'fmWorkflowEditor.DiagramViewLeftRuler1.Caption=&Left ruler' + #13#10 +
'fmWorkflowEditor.DiagramViewLeftRuler1.Hint=Show/hide left ruler' + #13#10 +
'fmWorkflowEditor.DiagramViewTopRuler1.Caption=&Top ruler' + #13#10 +
'fmWorkflowEditor.DiagramViewTopRuler1.Hint=Show/hide top ruler' + #13#10 +
'fmWorkflowEditor.DiagramShapeColor1.Caption=Shape color...' + #13#10 +
'fmWorkflowEditor.DiagramShapeColor1.Hint=Shape color' + #13#10 +
'fmWorkflowEditor.DiagramLineColor1.Caption=Line color...' + #13#10 +
'fmWorkflowEditor.DiagramLineColor1.Hint=Line color' + #13#10 +
'fmWorkflowEditor.DiagramBlockPicture1.Caption=Picture...' + #13#10 +
'fmWorkflowEditor.DiagramBlockPicture1.Hint=Block picture' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape1.Caption=None' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape2.Caption=Solid arrow' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape3.Caption=Line arrow' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape4.Caption=Ellipse' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape5.Caption=Rectangle' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape6.Caption=Diamond' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape7.Caption=None' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape8.Caption=Solid arrow' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape9.Caption=Line arrow' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape10.Caption=Ellipse' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape11.Caption=Rectangle' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape12.Caption=Diamond' + #13#10 +
'fmWorkflowEditor.DiagramBringToFront1.Caption=Bring to front' + #13#10 +
'fmWorkflowEditor.DiagramBringToFront1.Hint=Bring to front' + #13#10 +
'fmWorkflowEditor.acNewDiagram.Caption=&New diagram...' + #13#10 +
'fmWorkflowEditor.acNewDiagram.Hint=New diagram|Creates a new diagram' + #13#10 +
'fmWorkflowEditor.acOpenDiagram.Caption=&Open diagram...' + #13#10 +
'fmWorkflowEditor.acOpenDiagram.Hint=Open diagram|Open an existing diagram' + #13#10 +
'fmWorkflowEditor.acSaveDiagram.Caption=&Save diagram...' + #13#10 +
'fmWorkflowEditor.acSaveDiagram.Hint=Save diagram|Save current diagram' + #13#10 +
'fmWorkflowEditor.acPrintDiagram.Caption=&Print...' + #13#10 +
'fmWorkflowEditor.acPrintDiagram.Hint=Print diagram|Print current diagram' + #13#10 +
'fmWorkflowEditor.acPreviewDiagram.Caption=Print Pre&view...' + #13#10 +
'fmWorkflowEditor.acPreviewDiagram.Hint=Print preview|Print preview of current diagram' + #13#10 +
'fmWorkflowEditor.DiagramSendToBack1.Caption=Send to back' + #13#10 +
'fmWorkflowEditor.DiagramSendToBack1.Hint=Send to back' + #13#10 +
'fmWorkflowEditor.DiagramControlFont1.Caption=Font...' + #13#10 +
'fmWorkflowEditor.DiagramControlFont1.Hint=Change text font' + #13#10 +
'fmWorkflowEditor.DiagramGrid1.Caption=Grid' + #13#10 +
'fmWorkflowEditor.DiagramGrid1.Hint=Show/hide grid' + #13#10 +
'fmWorkflowEditor.DiagramGradientSetting1.Caption=Gradient setting ...' + #13#10 +
'fmWorkflowEditor.DiagramGradientSetting1.Hint=Select gradient' + #13#10 +
'fmWorkflowEditor.DiagramShadow1.Caption=Shadow settings ...' + #13#10 +
'fmWorkflowEditor.DiagramShadow1.Hint=Shadow settings' + #13#10 +
'fmWorkflowEditor.DiagramUndoAction1.Caption=Undo' + #13#10 +
'fmWorkflowEditor.DiagramRedoAction1.Caption=Redo' + #13#10 +
'fmWorkflowEditor.acAutomaticNodes.Caption=&Automatic nodes' + #13#10 +
'fmWorkflowEditor.DiagramConnectionId1.Caption=Transition' + #13#10 +
'fmWorkflowEditor.DiagramConnectionId1.Hint=Transition' + #13#10 +
'fmWorkflowEditor.DiagramConnectionId2.Caption=Side transition' + #13#10 +
'fmWorkflowEditor.DiagramConnectionId2.Hint=Side transition' + #13#10 +
'fmWorkflowEditor.DiagramConnectionId3.Caption=Arc transition' + #13#10 +
'fmWorkflowEditor.DiagramConnectionId3.Hint=Arc transition' + #13#10 +
'fmWorkflowEditor.OpenDialog1.Filter=Diagram files (*.dgr)|*.dgr|All files (*.*)|*.*' + #13#10 +
'fmWorkflowEditor.OpenDialog1.Title=Select diagram file' + #13#10 +
'fmWorkflowEditor.SaveDialog1.Filter=Diagram files (*.dgr)|*.dgr|All files (*.*)|*.*' + #13#10 +
'fmWorkflowEditor.SaveDialog1.Title=Select diagram file' + #13#10 +
'fmWorkflowEditor.Sourcearrow1.Caption=Source arrow' + #13#10 +
'fmWorkflowEditor.Targetarrow1.Caption=Target arrow' + #13#10 +
'' + #13#10 +
'[fWorkflowEditor]' + #13#10 +
'fmRunWorkflowEditor.Self.Caption=Run workflow' + #13#10 +
'fmRunWorkflowEditor.tsGeneral.Caption=General' + #13#10 +
'fmRunWorkflowEditor.lbWorkflowDefinition.Caption=Workflow definition' + #13#10 +
'fmRunWorkflowEditor.lbVariableMapping.Caption=Variable mapping' + #13#10 +
'fmRunWorkflowEditor.chWaitExecution.Caption=Wait until finished' + #13#10 +
'fmRunWorkflowEditor.btCancel.Caption=Cancel' + #13#10 +
'fmRunWorkflowEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'';

initialization
  _ResAddStrings(LanguageStr);

end.
