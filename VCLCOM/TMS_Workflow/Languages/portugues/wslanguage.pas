unit wsLanguage;

interface

implementation
uses wsRes;

const LanguageStr = 
'[fApprovalEditor]' + #13#10 +
'fmApprovalEditor.Self.Caption=Aprovação' + #13#10 +
'fmApprovalEditor.tsGeneral.Caption=Geral' + #13#10 +
'fmApprovalEditor.lbSubject.Caption=Assunto' + #13#10 +
'fmApprovalEditor.lbDescription.Caption=Descrição' + #13#10 +
'fmApprovalEditor.lbAssignment.Caption=Associação' + #13#10 +
'fmApprovalEditor.cbMailNotification.Caption=Envia notificação por e-mail' + #13#10 +
'fmApprovalEditor.tsStatus.Caption=Status' + #13#10 +
'fmApprovalEditor.lbStatusList.Caption=Lista de Status (Status de finalização deve começar com "*")' + #13#10 +
'fmApprovalEditor.tsAttachments.Caption=Anexos' + #13#10 +
'fmApprovalEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmApprovalEditor.btOk.Caption=&Ok' + #13#10 +
'fmApprovalEditor.tsFields.Caption=Campos' + #13#10 +
'fmApprovalEditor.tsExpiration.Caption=Vencimento' + #13#10 +
'' + #13#10 +
'[fAttachmentEditor]' + #13#10 +
'fmAttachmentEditor.Self.Caption=Anexos' + #13#10 +
'fmAttachmentEditor.tsAttachments.Caption=Geral' + #13#10 +
'fmAttachmentEditor.btAdd.Caption=Adicionar' + #13#10 +
'fmAttachmentEditor.btDelete.Caption=Excluir' + #13#10 +
'fmAttachmentEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmAttachmentEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fAttachmentFrame]' + #13#10 +
'frAttachmentFrame.OpenDialog1.Filter=Todos os arquivos (*.*)|*.*' + #13#10 +
'frAttachmentFrame.OpenDialog1.Title=Inserir Anexo' + #13#10 +
'frAttachmentFrame.miOpen.Caption=&Abrir Anexo' + #13#10 +
'frAttachmentFrame.miInsert.Caption=&Inserir Anexo' + #13#10 +
'frAttachmentFrame.miRemove.Caption=&Remover Anexo' + #13#10 +
'frAttachmentFrame.acInsert.Hint=Inserir Anexo' + #13#10 +
'frAttachmentFrame.acRemove.Hint=Remover Anexo' + #13#10 +
'frAttachmentFrame.acOpen.Hint=Abrir Anexo' + #13#10 +
'frAttachmentFrame.acLargeIcons.Caption=Ícones Grandes' + #13#10 +
'frAttachmentFrame.acLargeIcons.Hint=Ícones Grandes' + #13#10 +
'frAttachmentFrame.acSmallIcons.Caption=Ícones Pequenos' + #13#10 +
'frAttachmentFrame.acSmallIcons.Hint=Ìcones Pequenos' + #13#10 +
'frAttachmentFrame.acList.Caption=Lista' + #13#10 +
'frAttachmentFrame.acList.Hint=Lista' + #13#10 +
'frAttachmentFrame.acReport.Caption=Relatório' + #13#10 +
'frAttachmentFrame.acReport.Hint=Relatório' + #13#10 +
'frAttachmentFrame.lvItems.Caption=Nome do Arquivo' + #13#10 +
'' + #13#10 +
'[fAttachPermissions]' + #13#10 +
'frAttachPermissions.cbShowAttachments.Caption=Mostrar Anexos' + #13#10 +
'frAttachPermissions.cbDelAttachment.Caption=Permitir remover anexos' + #13#10 +
'frAttachPermissions.cbInsAttachment.Caption=Permitir inserir anexos' + #13#10 +
'frAttachPermissions.cbEditAttachment.Caption=Permitir editar anexos' + #13#10 +
'' + #13#10 +
'[fDecisionEditor]' + #13#10 +
'fmDecisionEditor.Self.Caption=Decisão' + #13#10 +
'fmDecisionEditor.TabSheet1.Caption=Geral' + #13#10 +
'fmDecisionEditor.Label1.Caption=Condição' + #13#10 +
'fmDecisionEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmDecisionEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fExpirationFrame]' + #13#10 +
'frExpirationFrame.rbExpNever.Caption=Tarefa &não expira' + #13#10 +
'frExpirationFrame.rbExpTerm.Caption=Pra&zo de vencimento:' + #13#10 +
'frExpirationFrame.cbTermType.Items0=dias' + #13#10 +
'frExpirationFrame.cbTermType.Items1=semanas' + #13#10 +
'frExpirationFrame.cbTermType.Items2=meses' + #13#10 +
'frExpirationFrame.rbExpDate.Caption=Data/hora de &vencimento:' + #13#10 +
'frExpirationFrame.rbExpCustom.Caption=Expressão &personalizada (data/hora):' + #13#10 +
'frExpirationFrame.lbStatus.Caption=&Status de vencimento:' + #13#10 +
'' + #13#10 +
'[fFieldFrame]' + #13#10 +
'frFieldFrame.Label1.Caption=Título do Texto' + #13#10 +
'frFieldFrame.Label2.Caption=Variável do Workflow' + #13#10 +
'frFieldFrame.cbReadOnly.Caption=Somente Leitura' + #13#10 +
'frFieldFrame.cbRequired.Caption=Obrigatório' + #13#10 +
'frFieldFrame.btAdd.Caption=Adicionar' + #13#10 +
'frFieldFrame.btDelete.Caption=Excluir' + #13#10 +
'' + #13#10 +
'[fStatusFrame]' + #13#10 +
'frStatusFrame.lbStatusName.Caption=Nome do status:' + #13#10 +
'frStatusFrame.chCompletion.Caption=Finalização' + #13#10 +
'frStatusFrame.chHidden.Caption=Oculto' + #13#10 +
'frStatusFrame.btAdd.Caption=Adicionar' + #13#10 +
'frStatusFrame.btDelete.Caption=Excluuir' + #13#10 +
'' + #13#10 +
'[fscripteditor]' + #13#10 +
'fmScriptEditor.Self.Caption=Script' + #13#10 +
'fmScriptEditor.tsScript.Caption=Script source' + #13#10 +
'fmScriptEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmScriptEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fTaskEditor]' + #13#10 +
'fmTaskEditor.Self.Caption=Tarefas' + #13#10 +
'fmTaskEditor.tsGeneral.Caption=Geral' + #13#10 +
'fmTaskEditor.Label1.Caption=Assunto' + #13#10 +
'fmTaskEditor.Label2.Caption=Descrição' + #13#10 +
'fmTaskEditor.Label3.Caption=Associação' + #13#10 +
'fmTaskEditor.cbMailNotification.Caption=Enviar notificação por e-mail' + #13#10 +
'fmTaskEditor.TabSheet2.Caption=Status' + #13#10 +
'fmTaskEditor.Label4.Caption=Lista de status(Inicie o status de concluído com "*")' + #13#10 +
'fmTaskEditor.tsAttachment.Caption=Anexos' + #13#10 +
'fmTaskEditor.tsFields.Caption=Campos' + #13#10 +
'fmTaskEditor.btAdd.Caption=Adicionar' + #13#10 +
'fmTaskEditor.btDelete.Caption=Excluir' + #13#10 +
'fmTaskEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmTaskEditor.btOk.Caption=&Ok' + #13#10 +
'fmTaskEditor.tsExpiration.Caption=Vencimento' + #13#10 +
'' + #13#10 +
'[fTaskInstanceView]' + #13#10 +
'frTaskInstanceView.Label1.Caption=Assunto:' + #13#10 +
'frTaskInstanceView.Label2.Caption=Status:' + #13#10 +
'' + #13#10 +
'[ftasklist]' + #13#10 +
'fmTaskList.Self.Caption=Lista de Tarefas' + #13#10 +
'fmTaskList.btSaveChanges.Caption=&Salvar mudanças' + #13#10 +
'fmTaskList.lvTasks.Caption=Chave' + #13#10 +
'fmTaskList.acShowClosedTasks.Caption=Mostrar tarefas finalizadas' + #13#10 +
'fmTaskList.acShowOnlyOpen.Caption=Mostrar tarefas abertas' + #13#10 +
'fmTaskList.acShowAllTasks.Caption=Mostrar todas as tarefas' + #13#10 +
'fmTaskList.miView.Caption=&Visualizar' + #13#10 +
'' + #13#10 +
'[fTransitionEditor]' + #13#10 +
'fmTransitionEditor.Self.Caption=Transição' + #13#10 +
'fmTransitionEditor.TabSheet1.Caption=Geral' + #13#10 +
'fmTransitionEditor.Label1.Caption=Condição' + #13#10 +
'fmTransitionEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmTransitionEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'[fVariableEditor]' + #13#10 +
'fmVariableEditor.Self.Caption=Variáveis' + #13#10 +
'fmVariableEditor.TabSheet1.Caption=Geral' + #13#10 +
'fmVariableEditor.Label1.Caption=Valor' + #13#10 +
'fmVariableEditor.btAdd.Caption=&Adicionar' + #13#10 +
'fmVariableEditor.btDelete.Caption=&Excluir' + #13#10 +
'fmVariableEditor.btCancel.Caption=&Cencelar' + #13#10 +
'fmVariableEditor.btOk.Caption=&Ok' + #13#10 +
'' + #13#10 +
'[fWorkDefManager]' + #13#10 +
'fmWorkDefManager.Self.Caption=Definições de workflow' + #13#10 +
'fmWorkDefManager.btAdd.Caption=&Adicionar' + #13#10 +
'fmWorkDefManager.btEdit.Caption=&Editar' + #13#10 +
'fmWorkDefManager.btDelete.Caption=E&xcluir' + #13#10 +
'fmWorkDefManager.btRefresh.Caption=&Atualizar' + #13#10 +
'fmWorkDefManager.btRunNew.Caption=Executar novo' + #13#10 +
'fmWorkDefManager.acImport.Caption=&Importar definição...' + #13#10 +
'fmWorkDefManager.acExport.Caption=E&xportar definição selecionada...' + #13#10 +
'fmWorkDefManager.OpenDialog1.Filter=Definições de workflow (*.wfd)|*.wfd' + #13#10 +
'fmWorkDefManager.OpenDialog1.Title=Importar definição de workflow' + #13#10 +
'fmWorkDefManager.SaveDialog1.Filter=Definições de workflow (*.wfd)|*.wfd' + #13#10 +
'fmWorkDefManager.SaveDialog1.Title=Exportar definição de workflow' + #13#10 +
'' + #13#10 +
'[fWorkflowEditor]' + #13#10 +
'fmWorkflowEditor.Self.Caption=Editor do diagrama' + #13#10 +
'fmWorkflowEditor.ToolBar1.Caption=ToolBar1' + #13#10 +
'fmWorkflowEditor.btCheck.Caption=Verificar workflow' + #13#10 +
'fmWorkflowEditor.ToolBar2.Caption=ToolBar2' + #13#10 +
'fmWorkflowEditor.DgrColorSelector1.Hint=Cor do bloco' + #13#10 +
'fmWorkflowEditor.DgrGradientDirectionSelector1.Hint=Gradiente' + #13#10 +
'fmWorkflowEditor.DgrBrushStyleSelector1.Hint=Estilo de preenchimento' + #13#10 +
'fmWorkflowEditor.DgrShadowSelector1.Hint=Sombreamento' + #13#10 +
'fmWorkflowEditor.DgrPenStyleSelector1.Hint=Estilo da linha' + #13#10 +
'fmWorkflowEditor.DgrPenColorSelector1.Hint=Cor da linha' + #13#10 +
'fmWorkflowEditor.DgrPenWidthSelector1.Hint=Largura da linha' + #13#10 +
'fmWorkflowEditor.DgrTextColorSelector1.Hint=Cor do texto' + #13#10 +
'fmWorkflowEditor.DiagramToolBar2.Category=Workflow' + #13#10 +
'fmWorkflowEditor.File1.Caption=&Arquivo' + #13#10 +
'fmWorkflowEditor.Edit2.Caption=&Editar' + #13#10 +
'fmWorkflowEditor.Copyasimage1.Caption=Cop&iar como imagem' + #13#10 +
'fmWorkflowEditor.View1.Caption=&Visualizar' + #13#10 +
'fmWorkflowEditor.Zoom1.Caption=&Zoom' + #13#10 +
'fmWorkflowEditor.Edittext1.Caption=&Objeto' + #13#10 +
'fmWorkflowEditor.Sourcearrow2.Caption=Se&ta origem' + #13#10 +
'fmWorkflowEditor.Targetarrow2.Caption=Seta &destino' + #13#10 +
'fmWorkflowEditor.Workflow1.Caption=&Workflow' + #13#10 +
'fmWorkflowEditor.Variables1.Caption=&Variáveis...' + #13#10 +
'fmWorkflowEditor.Attachments1.Caption=&Anexos...' + #13#10 +
'fmWorkflowEditor.DiagramCut1.Caption=Recor&tar' + #13#10 +
'fmWorkflowEditor.DiagramCut1.Hint=Recortar|Recortar' + #13#10 +
'fmWorkflowEditor.DiagramCopy1.Caption=&Copiar' + #13#10 +
'fmWorkflowEditor.DiagramCopy1.Hint=Copiar|Copiar' + #13#10 +
'fmWorkflowEditor.DiagramPaste1.Caption=Co&lar' + #13#10 +
'fmWorkflowEditor.DiagramPaste1.Hint=Colar|Colar' + #13#10 +
'fmWorkflowEditor.DiagramSelectAll1.Caption=Se&lecionar tudo' + #13#10 +
'fmWorkflowEditor.DiagramSelectAll1.Hint=Selecionar tudo|Selecionar todos os objetos' + #13#10 +
'fmWorkflowEditor.DiagramDelete1.Caption=E&xcluir' + #13#10 +
'fmWorkflowEditor.DiagramDelete1.Hint=Excluir objetos|Excluir objetos selecionados' + #13#10 +
'fmWorkflowEditor.DiagramEditText1.Caption=Editar &texto' + #13#10 +
'fmWorkflowEditor.DiagramEditText1.Hint=Editar texto' + #13#10 +
'fmWorkflowEditor.DiagramViewLeftRuler1.Caption=Régua es&querda' + #13#10 +
'fmWorkflowEditor.DiagramViewLeftRuler1.Hint=Exibir/esconder régua esquerda' + #13#10 +
'fmWorkflowEditor.DiagramViewTopRuler1.Caption=Régua &superior' + #13#10 +
'fmWorkflowEditor.DiagramViewTopRuler1.Hint=Exibir/esconder régua superior' + #13#10 +
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
'[strings]' + #13#10 +
'SAttachment=Anexos' + #13#10 +
'SConfirmDeleteItems=Você tem certeza que deseja excluir o(s) item(s) selecionados ?' + #13#10 +
'SConfirmDeleteAttachments=Você tem certeza que deseja remover os anexos selecionados ?' + #13#10 +
'SConfirmOpenMoreThanOneFile=Você escolheu abrir mais que um arquivo ao mesmo tempo. Tem certeza?' + #13#10 +
'SCurrentWorkflow=Workflow corrente' + #13#10 + 
'SFileName=Nome do Arquivo' + #13#10 +
'SEnterStatusName=Enter com o nome do status' + #13#10 +
'SEnterVariableCaption=Entre com o título da Variável' + #13#10 +
'SExpiration=Vencimento' + #13#10 +
'SStatusList=Lista de status' + #13#10 +
'SVariables=Variáveis' + #13#10 +
'STask=Tarefa' + #13#10 +
'SVariable=Variável' + #13#10 +
'SColumnKey=Chave' + #13#10 +
'SColumnName=Nome' + #13#10 +
'SColumnWorkflow=Workflow' + #13#10 +
'SColumnSubject=Assunto' + #13#10 +
'SColumnStatus=Status' + #13#10 +
'SColumnUser=Usuário' + #13#10 +
'STabFields=Campos' + #13#10 +
'STabTask=Tarefa' + #13#10 +
'STabWorkflow=Workflow' + #13#10 +
'SConfirmDeleteWorkDef=Tem certeza que deseja exculir as definições selecionadas?' + #13#10 +
'SConfirmCloseAndDiscard=Fechar janela e descartar alterações?' + #13#10 +
'SModified=Modificado' + #13#10 +
'SAllObjects=Todos objetos' + #13#10 +
'SConfirmNewDiagramAndDiscard=Criar novo diagrama e descartar alterações?' + #13#10 +
'SConfirmOpenDiagramAndDiscard=Abrir novo diagrama e descartar alterações?' + #13#10 +
'SWorkflowCorrect=Diagrama to workflow sem error.' + #13#10 +
'SWorkflowDefinition=Definição de workflow' + #13#10 +
'STypeWorkDefName=Escreva o nome da definição de workflow' + #13#10 +
'SErrorParamNotFound=Não foi possível encontrar o parâmetro "%s" ao abrir a query do workflow.' + #13#10 +
'STrueOutput=sim' + #13#10 +
'SFalseOutput=não' + #13#10 +
'SBlockStart=INÍCIO' + #13#10 +
'SBlockEnd=FIM' + #13#10 +
'SBlockTask=Bloco Tarefa' + #13#10 +
'SBlockApproval=Bloco Aprovação' + #13#10 +
'SBlockScript=Bloco Script' + #13#10 +
'STaskApprovalName=Approvação' + #13#10 +
'STaskApprovalSubject=Approvação' + #13#10 +
'STaskApprovalDescription=Por favor, aprove ou rejeite essa tarefa.' + #13#10 +
'STaskApprovalStatusOpened=aberto' + #13#10 +
'STaskApprovalStatusApproved=aprovado' + #13#10 +
'STaskApprovalStatusRejected=rejeitado' + #13#10 +
'SToolbarStart=Início' + #13#10 +
'SToolbarEnd=Fim' + #13#10 +
'SToolbarError=Tratador de erro' + #13#10 +
'SToolbarSourceConnect=Conector origem' + #13#10 +
'SToolbarTargetConnect=Conector destino' + #13#10 +
'SToolbarLineJoin=Junção de linhas' + #13#10 +
'SToolbarTransition=Transição' + #13#10 +
'SToolbarSideTransition=Transição ortogonal' + #13#10 +
'SToolbarArcTransition=Transição em arco' + #13#10 +
'SToolbarFork=Divisão' + #13#10 +
'SToolbarJoin=Junção' + #13#10 +
'SToolbarTask=Tarefa' + #13#10 +
'SToolbarApproval=Aprovação' + #13#10 +
'SToolbarDecision=Decisão' + #13#10 +
'SToolbarWorkflowCategory=Workflow' + #13#10 +
'SToolbarRunWorkflow=Executar workflow' + #13#10 +
'SToolbarScript=Script' + #13#10 +
'SErrorFileAlreadyOpen=Arquivo já está aberto.' + #13#10 +
'SConfirmUpdateModifiedAttachment=O arquivo "%s" foi alterado. Deseja atualizá-lo nos anexos?' + #13#10 +
'SWarningFieldValueRequired=Valor de "%s" é obrigatório.' + #13#10 +
'SErrorInsertCannotGetKey=Erro na inserção de %s. Não é possível obter chave.' + #13#10 +
'SErrorRecordNotFoundKey=%s não encontrado no banco de dados. Chave: %s' + #13#10 +
'SErrorUpdateEmptyKey=Não foi possível atualizar %s no banco de dados. Chave vazia.' + #13#10 +
'SErrorDeleteEmptyKey=Não foi possível excluir %s do banco de dados. Chave vazia.' + #13#10 +
'SErrorUndefinedVariable=Variável "%s" não existe.' + #13#10 +
'SErrorScriptBlockCompile=Erro ao compilar bloco de script.' + #13#10 +
'STabLog=Log' + #13#10 +
'SLogColOperation=Operação' + #13#10 +
'SLogColDate=Data' + #13#10 +
'SLogColTime=Hora' + #13#10 +
'SLogColUserId=Id' + #13#10 +
'SLogColInfo=Informação' + #13#10 +
'STaskExpiredOn=Tarefa expirada em %s' + #13#10 +
'STaskLogCreate=Criado' + #13#10 +
'STaskLogInfo=Info' + #13#10 +
'STaskLogUpdate=Atualizado' + #13#10 +
'STaskLogStatusChange=Status Mudança' + #13#10 +
'SStatusChangeInfo=de "%s" para "%s"' + #13#10 +
'SWorkInsExecutionError1=Erro ao executar workflow. Instância do workflow finalizada.\#13#10\#13#10Mensagem de erro: "%s"' + #13#10 +
'SWorkInsExecutionError2=%s\#13#10\#13#10Informações sobre o bloco que causou o erro:\#13#10Type: %s\#13#10Nome: %s\#13#10Descrição: \#13#10"%s"' + #13#10 +
'SNextBlockUndefined=Próximo bloco indefinido. Não é possível continuar execução.' + #13#10 +
'STaskNotCreatedUserNotFound=(untranslated)A task instance could not be created because user/group "%s" does not exist.' + #13#10 +
'' + #13#10 +
'[fWorkflowEditor]' + #13#10 +
'fmRunWorkflowEditor.Self.Caption=Executar workflow' + #13#10 +
'fmRunWorkflowEditor.tsGeneral.Caption=Geral' + #13#10 +
'fmRunWorkflowEditor.lbWorkflowDefinition.Caption=Definição de workflow' + #13#10 +
'fmRunWorkflowEditor.lbVariableMapping.Caption=Mapeamento de variáveis' + #13#10 +
'fmRunWorkflowEditor.chWaitExecution.Caption=Aguardar execução' + #13#10 +
'fmRunWorkflowEditor.btCancel.Caption=Cancelar' + #13#10 +
'fmRunWorkflowEditor.btOk.Caption=Ok' + #13#10 +
'' + #13#10 +
'';

initialization
  _ResAddStrings(LanguageStr);

end.
