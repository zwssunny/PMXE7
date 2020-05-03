unit wsLanguage;

interface

implementation
uses wsRes;

const LanguageStr = 
'[fApprovalEditor]' + #13#10 +
'fmApprovalEditor.Self.Caption=Aprovación' + #13#10 +
'fmApprovalEditor.tsGeneral.Caption=General' + #13#10 +
'fmApprovalEditor.lbSubject.Caption=Asunto' + #13#10 +
'fmApprovalEditor.lbDescription.Caption=Descripción' + #13#10 +
'fmApprovalEditor.lbAssignment.Caption=Asociación' + #13#10 +
'fmApprovalEditor.cbMailNotification.Caption=Enviar notificación por mail' + #13#10 +
'fmApprovalEditor.tsStatus.Caption=Status' + #13#10 +
'fmApprovalEditor.lbStatusList.Caption=Lista de Status (Status de finalización debe comenzar con "*")' + #13#10 +
'fmApprovalEditor.tsAttachments.Caption=Anexos' + #13#10 +
'fmApprovalEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmApprovalEditor.btOk.Caption=&Ok' + #13#10 +
'fmApprovalEditor.tsFields.Caption=Campos' + #13#10 +
'fmApprovalEditor.tsExpiration.Caption=Vencimiento' + #13#10 +
'' + #13#10 +
'[fAttachmentEditor]' + #13#10 +
'fmAttachmentEditor.Self.Caption=Anexos' + #13#10 +
'fmAttachmentEditor.tsAttachments.Caption=General' + #13#10 +
'fmAttachmentEditor.btAdd.Caption=&Adicionar' + #13#10 +
'fmAttachmentEditor.btDelete.Caption=&Borrar' + #13#10 +
'fmAttachmentEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmAttachmentEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fAttachmentFrame]' + #13#10 +
'frAttachmentFrame.OpenDialog1.Filter=Todos los archivos (*.*)|*.*' + #13#10 +
'frAttachmentFrame.OpenDialog1.Title=Insertar anexo' + #13#10 +
'frAttachmentFrame.miOpen.Caption=&Abrir anexo...' + #13#10 +
'frAttachmentFrame.miInsert.Caption=&Insertar anexo...' + #13#10 +
'frAttachmentFrame.miRemove.Caption=&Remover anexo' + #13#10 +
'frAttachmentFrame.acInsert.Hint=Insertar anexo' + #13#10 +
'frAttachmentFrame.acRemove.Hint=Remover anexo' + #13#10 +
'frAttachmentFrame.acOpen.Hint=Abrir anexo' + #13#10 +
'frAttachmentFrame.acLargeIcons.Caption=iconos Grandes' + #13#10 +
'frAttachmentFrame.acLargeIcons.Hint=iconos Grandes' + #13#10 +
'frAttachmentFrame.acSmallIcons.Caption=iconos Pequeños' + #13#10 +
'frAttachmentFrame.acSmallIcons.Hint=iconos Pequeños' + #13#10 +
'frAttachmentFrame.acList.Caption=Lista' + #13#10 +
'frAttachmentFrame.acList.Hint=Lista' + #13#10 +
'frAttachmentFrame.acReport.Caption=Reporte' + #13#10 +
'frAttachmentFrame.acReport.Hint=Reporte' + #13#10 +
'frAttachmentFrame.lvItems.Caption=Nombre de archivo' + #13#10 +
'' + #13#10 +
'[fAttachPermissions]' + #13#10 +
'frAttachPermissions.cbShowAttachments.Caption=Mostrar anexos' + #13#10 +
'frAttachPermissions.cbDelAttachment.Caption=Permitir remover anexos' + #13#10 +
'frAttachPermissions.cbInsAttachment.Caption=Permitir insertar anexos' + #13#10 +
'frAttachPermissions.cbEditAttachment.Caption=Permitir editar anexos' + #13#10 +
'' + #13#10 +
'[fDecisionEditor]' + #13#10 +
'fmDecisionEditor.Self.Caption=Decisión' + #13#10 +
'fmDecisionEditor.TabSheet1.Caption=General' + #13#10 +
'fmDecisionEditor.Label1.Caption=Expresión de condición' + #13#10 +
'fmDecisionEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmDecisionEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fExpirationFrame]' + #13#10 +
'frExpirationFrame.rbExpNever.Caption=(untranslated)Task does &not expire' + #13#10 +
'frExpirationFrame.rbExpTerm.Caption=(untranslated)Expiration &term:' + #13#10 +
'frExpirationFrame.cbTermType.Items0=(untranslated)days' + #13#10 +
'frExpirationFrame.cbTermType.Items1=(untranslated)weeks' + #13#10 +
'frExpirationFrame.cbTermType.Items2=(untranslated)months' + #13#10 +
'frExpirationFrame.rbExpDate.Caption=(untranslated)Expiration dat&e/time:' + #13#10 +
'frExpirationFrame.rbExpCustom.Caption=(untranslated)&Custom date/time expression:' + #13#10 +
'frExpirationFrame.lbStatus.Caption=(untranslated)Expiration &status:' + #13#10 +
'' + #13#10 +
'[fFieldFrame]' + #13#10 +
'frFieldFrame.Label1.Caption=Título de texto:' + #13#10 +
'frFieldFrame.Label2.Caption=variable de Workflow:' + #13#10 +
'frFieldFrame.cbReadOnly.Caption=Solo lectura' + #13#10 +
'frFieldFrame.cbRequired.Caption=Requerido' + #13#10 +
'frFieldFrame.btAdd.Caption=Agregar' + #13#10 +
'frFieldFrame.btDelete.Caption=Borrar' + #13#10 +
'' + #13#10 +
'[fStatusFrame]' + #13#10 +
'frStatusFrame.lbStatusName.Caption=Nombre de lo status:' + #13#10 +
'frStatusFrame.chCompletion.Caption=Finalización' + #13#10 +
'frStatusFrame.chHidden.Caption=Oculto' + #13#10 +
'frStatusFrame.btAdd.Caption=Agregar' + #13#10 +
'frStatusFrame.btDelete.Caption=Borrar' + #13#10 +
'' + #13#10 +
'[fscripteditor]' + #13#10 +
'fmScriptEditor.Self.Caption=Script' + #13#10 +
'fmScriptEditor.tsScript.Caption=Script source' + #13#10 +
'fmScriptEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmScriptEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fTaskEditor]' + #13#10 +
'fmTaskEditor.Self.Caption=Tareas' + #13#10 +
'fmTaskEditor.tsGeneral.Caption=General' + #13#10 +
'fmTaskEditor.Label1.Caption=Asunto' + #13#10 +
'fmTaskEditor.Label2.Caption=Descripción' + #13#10 +
'fmTaskEditor.Label3.Caption=Asociación' + #13#10 +
'fmTaskEditor.cbMailNotification.Caption=Enviar notificación por mail' + #13#10 +
'fmTaskEditor.TabSheet2.Caption=Status' + #13#10 +
'fmTaskEditor.Label4.Caption=Lista Status (Iniciar status de concluido con "*")' + #13#10 +
'fmTaskEditor.tsAttachment.Caption=Anexos' + #13#10 +
'fmTaskEditor.tsFields.Caption=Campo' + #13#10 +
'fmTaskEditor.btAdd.Caption=&Agregar' + #13#10 +
'fmTaskEditor.btDelete.Caption=&Borrar' + #13#10 +
'fmTaskEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmTaskEditor.btOk.Caption=&Ok' + #13#10 +
'fmTaskEditor.tsExpiration.Caption=Vencimiento' + #13#10 +
'' + #13#10 +
'[fTaskInstanceView]' + #13#10 +
'frTaskInstanceView.Label1.Caption=Asunto:' + #13#10 +
'frTaskInstanceView.Label2.Caption=Status:' + #13#10 +
'' + #13#10 +
'[ftasklist]' + #13#10 +
'fmTaskList.Self.Caption=Lista de tareas' + #13#10 +
'fmTaskList.btSaveChanges.Caption=&Guardar cambios' + #13#10 +
'fmTaskList.lvTasks.Caption=Tecla' + #13#10 +
'fmTaskList.acShowOnlyOpen.Caption=Mostrar solo tareas abiertas' + #13#10 +
'fmTaskList.acShowAllTasks.Caption=Mostrar todas las tareas' + #13#10 +
'fmTaskList.miView.Caption=&Visualizar' + #13#10 +
'' + #13#10 +
'[fTransitionEditor]' + #13#10 +
'fmTransitionEditor.Self.Caption=Transición' + #13#10 +
'fmTransitionEditor.TabSheet1.Caption=General' + #13#10 +
'fmTransitionEditor.Label1.Caption=expresión de Condición' + #13#10 +
'fmTransitionEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmTransitionEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fVariableEditor]' + #13#10 +
'fmVariableEditor.Self.Caption=Variables' + #13#10 +
'fmVariableEditor.TabSheet1.Caption=General' + #13#10 +
'fmVariableEditor.Label1.Caption=Valor' + #13#10 +
'fmVariableEditor.btAdd.Caption=&Agregar' + #13#10 +
'fmVariableEditor.btDelete.Caption=&Borrar' + #13#10 +
'fmVariableEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmVariableEditor.btOk.Caption=&Ok' + #13#10 +
'' + #13#10 +
'[fWorkDefManager]' + #13#10 +
'fmWorkDefManager.Self.Caption=Definiciones de Workflow' + #13#10 +
'fmWorkDefManager.btAdd.Caption=&Agregar' + #13#10 +
'fmWorkDefManager.btEdit.Caption=&Editar' + #13#10 +
'fmWorkDefManager.btDelete.Caption=&Borrar' + #13#10 +
'fmWorkDefManager.btRefresh.Caption=&Refrescar' + #13#10 +
'fmWorkDefManager.btRunNew.Caption=Ejecutar &nuevo' + #13#10 +
'fmWorkDefManager.acImport.Caption=&Importar definiciones...' + #13#10 +
'fmWorkDefManager.acExport.Caption=E&xportar definiciones seleccionadas...' + #13#10 +
'fmWorkDefManager.OpenDialog1.Filter=definiciones de Workflow (*.wfd)|*.wfd' + #13#10 +
'fmWorkDefManager.OpenDialog1.Title=Importar definiciones de workflow' + #13#10 +
'fmWorkDefManager.SaveDialog1.Filter=definiciones de Workflow (*.wfd)|*.wfd' + #13#10 +
'fmWorkDefManager.SaveDialog1.Title=Exportar definiciones de workflow' + #13#10 +
'' + #13#10 +
'[fWorkflowEditor]' + #13#10 +
'fmWorkflowEditor.Self.Caption=Editor de diagrama' + #13#10 +
'fmWorkflowEditor.ToolBar1.Caption=ToolBar1' + #13#10 +
'fmWorkflowEditor.btCheck.Caption=Chequear workflow' + #13#10 +
'fmWorkflowEditor.ToolBar2.Caption=ToolBar2' + #13#10 +
'fmWorkflowEditor.DgrColorSelector1.Hint=Color del bloque' + #13#10 +
'fmWorkflowEditor.DgrGradientDirectionSelector1.Hint=Gradiente' + #13#10 +
'fmWorkflowEditor.DgrBrushStyleSelector1.Hint=Estilo de brocha' + #13#10 +
'fmWorkflowEditor.DgrShadowSelector1.Hint=Sombre' + #13#10 +
'fmWorkflowEditor.DgrPenStyleSelector1.Hint=Estilo de línea' + #13#10 +
'fmWorkflowEditor.DgrPenColorSelector1.Hint=Color de línea' + #13#10 +
'fmWorkflowEditor.DgrPenWidthSelector1.Hint=Ancho de línea' + #13#10 +
'fmWorkflowEditor.DgrTextColorSelector1.Hint=Colorde texto' + #13#10 +
'fmWorkflowEditor.DiagramToolBar2.Category=Workflow' + #13#10 +
'fmWorkflowEditor.File1.Caption=&Archivo' + #13#10 +
'fmWorkflowEditor.Edit2.Caption=&Editar' + #13#10 +
'fmWorkflowEditor.Copyasimage1.Caption=Cop&iar como imagen' + #13#10 +
'fmWorkflowEditor.View1.Caption=&Visualizar' + #13#10 +
'fmWorkflowEditor.Zoom1.Caption=&Zoom' + #13#10 +
'fmWorkflowEditor.Edittext1.Caption=&Objecto' + #13#10 +
'fmWorkflowEditor.Sourcearrow2.Caption=Flecha ori&gen' + #13#10 +
'fmWorkflowEditor.Targetarrow2.Caption=Flecha &Destino' + #13#10 +
'fmWorkflowEditor.Workflow1.Caption=&Workflow' + #13#10 +
'fmWorkflowEditor.Variables1.Caption=&Variables...' + #13#10 +
'fmWorkflowEditor.Attachments1.Caption=&Anexos...' + #13#10 +
'fmWorkflowEditor.DiagramCut1.Caption=Cor&tar' + #13#10 +
'fmWorkflowEditor.DiagramCut1.Hint=Cortar|Cortar al clipboard' + #13#10 +
'fmWorkflowEditor.DiagramCopy1.Caption=&Copiar' + #13#10 +
'fmWorkflowEditor.DiagramCopy1.Hint=Copy|Copiar al clipboard' + #13#10 +
'fmWorkflowEditor.DiagramPaste1.Caption=&Pegar' + #13#10 +
'fmWorkflowEditor.DiagramPaste1.Hint=Pegar|Pegar del clipboard' + #13#10 +
'fmWorkflowEditor.DiagramSelectAll1.Caption=Se&leccionar todo' + #13#10 +
'fmWorkflowEditor.DiagramSelectAll1.Hint=Seleccionar todo|Seleccionar todo los objetos' + #13#10 +
'fmWorkflowEditor.DiagramDelete1.Caption=&Borrar' + #13#10 +
'fmWorkflowEditor.DiagramDelete1.Hint=Borrar objetos|Borrar objetos seleccionados' + #13#10 +
'fmWorkflowEditor.DiagramEditText1.Caption=Editar &texto' + #13#10 +
'fmWorkflowEditor.DiagramEditText1.Hint=Editar texto' + #13#10 +
'fmWorkflowEditor.DiagramViewLeftRuler1.Caption=&Regla izquierda' + #13#10 +
'fmWorkflowEditor.DiagramViewLeftRuler1.Hint=Mostrar/ocultar regla izquierda' + #13#10 +
'fmWorkflowEditor.DiagramViewTopRuler1.Caption=R&egla superior' + #13#10 +
'fmWorkflowEditor.DiagramViewTopRuler1.Hint=Mostrar/ocultar regla superior' + #13#10 +
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
'fmWorkflowEditor.DiagramArrowShape5.Caption=Rectangulo' + #13#10 +
'fmWorkflowEditor.DiagramArrowShape6.Caption=Diamante' + #13#10 +
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
'[strings]' + #13#10 +
'SAttachment=Anexos   ' + #13#10 +
'SConfirmDeleteItems=Tiene la certeza de que quiere eliminar los item(s) seleccionados?' + #13#10 +
'SConfirmDeleteAttachments=Tiene la certeza de que quiere remover los anexos seleccionados?' + #13#10 +
'SConfirmOpenMoreThanOneFile=Solicitó abrir más de un archivo a la vez. Esta seguro?' + #13#10 +
'SCurrentWorkflow=Workflow actual' + #13#10 + 
'SFileName=Nombre del archivo' + #13#10 +
'SEnterStatusName=Entre el nombre de lo status' + #13#10 +
'SEnterVariableCaption=Entre el título de la variable' + #13#10 +
'SExpiration=Vencimiento' + #13#10 +
'SStatusList=Lista de status' + #13#10 +
'SVariables=Variables' + #13#10 +
'STask=Task' + #13#10 +
'SVariable=Variable' + #13#10 +
'SColumnKey=Llave' + #13#10 +
'SColumnName=Nombre' + #13#10 +
'SColumnWorkflow=Workflow' + #13#10 +
'SColumnSubject=Asunto' + #13#10 +
'SColumnStatus=Status' + #13#10 +
'SColumnUser=Usuario' + #13#10 +
'STabFields=Campos' + #13#10 +
'STabTask=Tareas' + #13#10 +
'STabWorkflow=Workflow' + #13#10 +
'SConfirmDeleteWorkDef=Esta seguro que desea eliminar las definiciones de workflow seleccionadas?' + #13#10 +
'SConfirmCloseAndDiscard=Cierra el forulario y descarta los cambios?' + #13#10 +
'SModified=Modificado' + #13#10 +
'SAllObjects=todos los objetos' + #13#10 +
'SConfirmNewDiagramAndDiscard=Crear un nuevo diagrama y descartar los cambios?' + #13#10 +
'SConfirmOpenDiagramAndDiscard=Abrir un nuevo diagrama y descartar los cambios actuales?' + #13#10 +
'SWorkflowCorrect=El diagrama de workflow es correcto.' + #13#10 +
'SWorkflowDefinition=Definiciones de workflow' + #13#10 +
'STypeWorkDefName=Tipee el nombre de la definición de workflow' + #13#10 +
'SErrorParamNotFound=No se puede encontrar el parametro "%s" cuando se abre la query del workflow.' + #13#10 +
'STrueOutput=si' + #13#10 +
'SFalseOutput=no' + #13#10 +
'SBlockStart=INICIO' + #13#10 +
'SBlockEnd=FIN' + #13#10 +
'SBlockTask=Bloque de tarea' + #13#10 +
'SBlockApproval=Aprobación de bloque' + #13#10 +
'SBlockScript=Bloque de script' + #13#10 +
'STaskApprovalName=Aprobación' + #13#10 +
'STaskApprovalSubject=Aprobación' + #13#10 +
'STaskApprovalDescription=Por favor apruebe o rechace lo siguiente.' + #13#10 +
'STaskApprovalStatusOpened=abierto' + #13#10 +
'STaskApprovalStatusApproved=aprobado' + #13#10 +
'STaskApprovalStatusRejected=rechazado' + #13#10 +
'SToolbarStart=inicio' + #13#10 +
'SToolbarEnd=fin' + #13#10 +
'SToolbarError=Manejador de error' + #13#10 +
'SToolbarSourceConnect=Conector origen' + #13#10 +
'SToolbarTargetConnect=Conector destino' + #13#10 +
'SToolbarLineJoin=Línea de unión' + #13#10 +
'SToolbarTransition=Transición' + #13#10 +
'SToolbarSideTransition=Transición ortogonal' + #13#10 +
'SToolbarArcTransition=Tranción en arco' + #13#10 +
'SToolbarFork=Dividir' + #13#10 +
'SToolbarJoin=Unir' + #13#10 +
'SToolbarTask=Tarea' + #13#10 +
'SToolbarApproval=Aprobación' + #13#10 +
'SToolbarDecision=Decisión' + #13#10 +
'SToolbarWorkflowCategory=Workflow' + #13#10 +
'SToolbarRunWorkflow=Ejecutar workflow' + #13#10 +
'SToolbarScript=Script' + #13#10 +
'SErrorFileAlreadyOpen=El archivo ya está abierto.' + #13#10 +
'SConfirmUpdateModifiedAttachment=El archivo "%s" fué modificado. Desea actualizar en los anexos?' + #13#10 +
'SWarningFieldValueRequired=Valor de "%s" es requerido.' + #13#10 +
'SErrorInsertCannotGetKey=Error en %s inserción. No es posible recuperar la llave.' + #13#10 +
'SErrorRecordNotFoundKey=%s no encontrada en la base de datos. Llave: %s' + #13#10 +
'SErrorUpdateEmptyKey=No se pudo actualizar %s en la base de datos. Llave vacía.' + #13#10 +
'SErrorDeleteEmptyKey=No se pudo eliminar %s de la base de datos. Llave vacía.' + #13#10 +
'SErrorUndefinedVariable=Variable "%s" no existe.' + #13#10 +
'SErrorScriptBlockCompile=Error compilando bloque de script. ' + #13#10 +
'STabLog=Log' + #13#10 +
'SLogColOperation=Operation' + #13#10 +
'SLogColDate=Fecha' + #13#10 +
'SLogColTime=Hora' + #13#10 +
'SLogColUserId=Usuario id' + #13#10 +
'SLogColInfo=Información' + #13#10 +
'STaskExpiredOn=(untranslated)Task expired on %s' + #13#10 +
'STaskLogCreate=Creado' + #13#10 +
'STaskLogInfo=Info' + #13#10 +
'STaskLogUpdate=Actualizado' + #13#10 +
'STaskLogStatusChange=Status cambio' + #13#10 +
'SStatusChangeInfo=de "%s" a "%s"' + #13#10 +
'SWorkInsExecutionError1=Error ejecutando el workflow. La instancia del workflow se ha terminado.\#13#10\#13#10Mensaje de error: "%s"' + #13#10 +
'SWorkInsExecutionError2=%s\#13#10\#13#10Información sobre el bloque que causó el error.\#13#10Type: %s\#13#10Nombre: %s\#13#10Descripción: \#13#10"%s"' + #13#10 +
'SNextBlockUndefined=El próximo bloque no está definido. No se puede continuar ejecutando.' + #13#10 +
'STaskNotCreatedUserNotFound=(untranslated)A task instance could not be created because user/group "%s" does not exist.' + #13#10 +
'' + #13#10 +
'[fWorkflowEditor]' + #13#10 +
'fmRunWorkflowEditor.Self.Caption=Ejecutar workflow' + #13#10 +
'fmRunWorkflowEditor.tsGeneral.Caption=General' + #13#10 +
'fmRunWorkflowEditor.lbWorkflowDefinition.Caption=Definición de workflow' + #13#10 +
'fmRunWorkflowEditor.lbVariableMapping.Caption=Asignación de variables' + #13#10 +
'fmRunWorkflowEditor.chWaitExecution.Caption=(untranslated)Wait until finished' + #13#10 +
'fmRunWorkflowEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmRunWorkflowEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'';

initialization
  _ResAddStrings(LanguageStr);

end.
