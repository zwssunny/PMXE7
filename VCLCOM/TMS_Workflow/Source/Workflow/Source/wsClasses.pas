{***************************************************************************}
{ Workflow Studio Components for Delphi & C++Builder                        }
{ version 1.5.0.1                                                           }
{                                                                           }
{ written by TMS Software                                                   }
{            copyright ?1997 - 2010                                        }
{            Email : info@tmssoftware.com                                   }
{            Web : http://www.tmssoftware.com                               }
{                                                                           }
{ For information about version history, check the section "What's New"     }
{ at Workflow Studio manual.                                                }
{                                                                           }
{ The source code is given as is. The author is not responsible             }
{ for any possible damage done due to the use of this code.                 }
{ The component can be freely used in any application. The complete         }
{ source code remains property of the author and may not be distributed,    }
{ published, given or sold in any form as such. No parts of the source      }
{ code can be included in any other component or application without        }
{ written authorization of the author.                                      }
{***************************************************************************}

unit wsClasses;

{$I wsdefs.inc}

interface

uses
  Windows, Messages, Classes, Dialogs, Contnrs, Controls, Graphics, Forms, DB,
  {$IFDEF USE_INDY}
  IdSMTP, IdMessage, IdMessageClient,
  {$ENDIF}
  {$IFDEF DELPHI6_LVL}
  Variants,
  {$ENDIF}
  {$WARNINGS OFF}
  FileCtrl,
  {$WARNINGS ON}
  SysUtils,
  atDiagram, LiveDiagram, DiagramUtils, DgrClasses, atScript;

type
  TCustomTaskManager        = class;
  TCustomWorkflowBlock      = class;
  TCustomWorkflowDiagram    = class;
  TCustomWorkflowManager    = class;
  TCustomWorkflowStudio     = class;
  TTaskInstance             = class;
  TWorkflowBlockEditor      = class;
  TWorkflowScriptEngine     = class;
  TWorkflowUserManager      = class;

  EWorkflowException        = class(Exception);

  TWorkflowBlockEditorClass = class of TWorkflowBlockEditor;

  TAttachmentPermission     = (apDelete, apInsert, apEdit);
  TAttachmentPermissions    = set of TAttachmentPermission;
  TStateShape               = (ssCircle, ssSquare);
  TTaskFilterType           = (tfUser, tfWorkIns, tfUserList);
  TLogFilterType            = (lfTaskIns,lfWorkIns);

  /// Description:
  ///   Group assignment mode defines what happen when a task is assigned to a group (not an user).
  ///   - gamMultipleTasks: A task will be created for each user in the group. So, if a group has users "john" and "maria",
  ///   one task will be createed for John, and antoher to Maria, and the tasks will be independent (both will have to be concluded)
  ///   - gamSingleTask: A single task will be created that will be visible for all users in the group. If you later include/remove
  ///   users to/from the group, the existing tasks will become not visible for users removed from the group, and will become visible
  ///   to users added to group. Any user from the group can update the task, including finishing it.
  TGroupAssignmentMode = (gamMultipleTasks, gamSingleTask);

  TWorkflowBlockEvent = procedure(Sender: TObject; ABlock: TCustomWorkflowBlock) of object;
  TWorkflowGetNowEvent = procedure(Sender: TObject; var ANow: TDateTime) of object;
  TWorkflowTaskEvent = procedure(Sender: TObject; ATaskIns: TTaskInstance) of object;
  TWorkflowTaskActionEvent = procedure(Sender: TObject; ATaskIns: TTaskInstance; var AContinue: boolean) of object;
  TWorkflowScriptEngineEvent = procedure(AEngine: TWorkflowScriptEngine) of object;

  TWorkflowDefinition = class(TCollectionItem)
  private
    FContainer: TForm;
    FDiagram: TCustomWorkflowDiagram;
    FKey: string;
    FName: string;
    FFlowExplan: string;
    FWorkType: string;
    FFlowIsPublic: integer;
    FFlowIsTerm: integer;
    FFlowCreatOn: TDateTime;
    FFlowCreator: string;
    function GetWorkflowStudio: TCustomWorkflowStudio;
    procedure Initialize(AWorkflowStudio: TCustomWorkflowStudio);
    procedure SetKey(const Value: string);
    procedure SetName(const Value: string);
    procedure SetWorkflowStudio(const Value: TCustomWorkflowStudio);
  public
    constructor Create(Collection: TCollection); overload; override;
    constructor Create(AWorkflowStudio: TCustomWorkflowStudio); reintroduce; overload; 
    destructor Destroy; override;
    procedure AssignFromDiagram(ADiagram: TCustomWorkflowDiagram);
    procedure AssignToDiagram(ADiagram: TCustomWorkflowDiagram);
    property Diagram: TCustomWorkflowDiagram read FDiagram;
    property Key: string read FKey write SetKey;
    property Name: string read FName write SetName;
    property WorkType:string read FWorkType write FWorkType;
    property FlowExplan: string read FFlowExplan write FFlowExplan;
    property FlowIsPublic: integer read FFlowIsPublic write FFlowIsPublic;
    property FlowIsTerm: integer read FFlowIsTerm write FFlowIsTerm;
    property FlowCreatOn: TDateTime read FFlowCreatOn write FFlowCreaton;
    property FlowCreator: string read FFlowCreator write FFlowCreator;
    property WorkflowStudio: TCustomWorkflowStudio read GetWorkflowStudio write SetWorkflowStudio;
  end;

  TWorkflowDefinitions = class(TOwnedCollection)
  private
    FWorkflowStudio: TCustomWorkflowStudio;
    function GetItem(Index: integer): TWorkflowDefinition;
    procedure SetWorkflowStudio(const Value: TCustomWorkflowStudio);
  public
    constructor Create(AOwner: TComponent);
    function Add: TWorkflowDefinition;
    function FindByName(AName: string): TWorkflowDefinition;
    function FindByKey(AKey: string): TWorkflowDefinition;
    function FindNewName: string;
    property Items[Index: integer]: TWorkflowDefinition read GetItem; default;
    property WorkflowStudio: TCustomWorkflowStudio read FWorkflowStudio write SetWorkflowStudio;
  end;

  TWorkflowStatus = (wsNotStarted, wsRunning, wsFinished, wsFinishedWithError);

  TWorkflowInstance = class(TComponent)
  private
    FContainer: TForm;
    FDiagram: TCustomWorkflowDiagram;
    FKey: string;
    FDefinitionKey: string;
    FStatus: TWorkflowStatus;
    FFlowMnCreateTime: TDateTime;
    FFlowMnCreator: string;
    FFlowMnSubject: string;
    FFlowMnContent: string;{描述}
    FFlowMnBusWindow: string; {业务类型窗体编码}
    FFlowMnBusCode: string;  {关联业务单号}
    FFlowMnRank: integer;
    FFlowMoveTimeLimit: integer;
    FFlowMnLastUpDateTime: TDateTime;
    FFlowMnFinishTime: TDateTime;
    FFlowMnReport: string;
    FWorkflowStudio: TCustomWorkflowStudio;
    FNextRunTime: TDateTime;
    FChildKey: string;
    FParentKey: string;
    FFlowMnPrjID: string;
    procedure LoadDiagramProp(Reader: TReader);
    procedure StoreDiagramProp(Writer: TWriter);
  protected
    procedure DefineProperties(Filer: TFiler); override;
  public
    constructor Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio); reintroduce;
    destructor Destroy; override;
    procedure AssignFromDiagram(ADiagram: TCustomWorkflowDiagram; State: boolean);
    procedure AssignToDiagram(ADiagram: TCustomWorkflowDiagram; State: boolean);
    property Diagram: TCustomWorkflowDiagram read FDiagram;
    property NextRunTime: TDateTime read FNextRunTime write FNextRunTime;
    property FlowMnCreateTime: TDateTime read FFlowMnCreateTime write FFlowMnCreateTime;
    property FlowMnCreator: string read FFlowMnCreator write FFlowMnCreator;
    property FlowMnSubject: string read FFlowMnSubject write FFlowMnSubject;
    property FlowMnContent: string read FFlowMnContent write FFlowMnContent;{描述}
    property FlowMnBusWindow: string read FFlowMnBusWindow write FFlowMnBusWindow; {业务类型窗体编码}
    property FlowMnBusCode: string read FFlowMnBusCode write FFlowMnBusCode;  {关联业务单号}
    property FlowMnRank: integer read FFlowMnRank write FFlowMnRank;
    property FlowMnReport: string read FFlowMnReport write FFlowMnReport;
    property FlowMoveTimeLimit: integer read FFlowMoveTimeLimit write FFlowMoveTimeLimit;
    property FlowMnLastUpDateTime: TDateTime read FFlowMnLastUpDateTime write FFlowMnLastUpDateTime;
    property FlowMnFinishTime: TDateTime read FFlowMnFinishTime write FFlowMnFinishTime;
  published
    property Key: string read FKey write FKey;
    property DefinitionKey: string read FDefinitionKey write FDefinitionKey;
    property Status: TWorkflowStatus read FStatus write FStatus;
    property ParentKey: string read FParentKey write FParentKey;
    property ChildKey: string read FChildKey write FChildKey;
    property WorkflowStudio: TCustomWorkflowStudio read FWorkflowStudio;
    property FlowMnPrjID: string read FFlowMnPrjID write FFlowMnPrjID;
  end;

  TWorkflowVariable = class(TCollectionItem)
  private
    FName: string;
    FValue: Variant;
    FInteraction: boolean;
  public
    procedure Assign(Source: TPersistent); override;
  published
    property Name: string read FName write FName;
    property Value: Variant read FValue write FValue;
    property Interaction: boolean read FInteraction write FInteraction;
  end;

  TWorkflowVariables = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TWorkflowVariable;
  public
    function Add: TWorkflowVariable;
    function FindByName(AName: string): TWorkflowVariable;
    property Items[Index: integer]: TWorkflowVariable read GetItem; default;
  end;

  TWorkflowBiz = class(TCollectionItem)
  private
    FBizFormID: string;
    FBizName: string;
    FBizMenuID: string;
    FBizTableName: string;
    FBizKey: string;
    FBizCheck: string;
    FBizChecker: string;
    FBizCheckDate: string;
    FBizEditMenuID: string;
    FBizCheckValue: string;
  public
    procedure Assign(Source: TPersistent); override;
  published
    property BizName: string read FBizName write FBizName;
    property BizFormID: string read FBizFormID write FBizFormID;
    property BizMenuID: string read FBizMenuID write FBizMenuID;
    property BizTableName: string read FBizTableName write FBizTableName;
    property BizKey: string read FBizKey write FBizKey;
    property BizCheck: string read FBizCheck write FBizCheck;
    property BizChecker: string read FBizChecker write FBizChecker;
    property BizCheckDate: string read FBizCheckDate write FBizCheckDate;
    property BizEditMenuID: string read FBizEditMenuID write FBizEditMenuID;
    property BizCheckValue: string read FBizCheckValue write FBizCheckValue;
  end;

  TWorkflowBizs = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TWorkflowBiz;
  public
    function Add: TWorkflowBiz;
    property Items[Index: integer]: TWorkflowBiz read GetItem; default;
    function FindByBizFormID(ABizFormID: string): TWorkflowBiz;
    function FindByBizMenuID(ABizMenuID: string): TWorkflowBiz;
    function FindByBizEditMenuID(ABizEditMenuID: string): TWorkflowBiz;
  end;


  TAttachmentItem = class;

  TNotifyThread = class(TThread)
  private
    FFileName: string;
    FItem: TAttachmentItem;
    FFileAge: TDateTime;
  public
    constructor Create(AItem: TAttachmentItem; const FileName: string; OnClosed: TNotifyEvent); overload;
    destructor Destroy; override;
    procedure Execute; override;
  end;

  TAttachmentItem = class(TCollectionItem)
  private
    FName: string;
    FContent: string;
    FOriginalName: string;
    FKey: string;
    FDirtyContent: boolean;
    FNotifyThread: TNotifyThread;
    FSaveCursor: TCursor;
    FCreatedOn: TDateTime;
    FWorkKey: string;
    FAttachType: integer;
    FWorkflowStudio: TCustomWorkflowStudio;
    procedure CursorDefault;
    procedure CursorHourGlass;
    procedure DoShellOpen(AFileName: string; AllowEdit: boolean);
    function GetContent: string;
    function GetExtension: string;
    procedure Initialize(AWorkflowStudio: TCustomWorkflowStudio);
    function IsContentStored: Boolean;
    function Loading: boolean;
    procedure SetContent(const Value: string);
    procedure SetDirtyContent(const Value: boolean);
    procedure ShellAppClosed(Sender: TObject);
  public
    procedure Assign(Source: TPersistent); override;
    constructor Create(Collection: TCollection); overload; override;
    constructor Create(AWorkflowStudio: TCustomWorkflowStudio); reintroduce; overload;
    destructor Destroy; override;
    procedure LoadContentFromFile(AFileName: string);
    procedure SaveContentToFile(AFileName: string);
    procedure Open(AllowEdit: boolean; APath: string = '');
    property Extension: string read GetExtension;
  published
    property Name: string read FName write FName;
    property OriginalName: string read FOriginalName write FOriginalName;
    property Key: string read FKey write FKey;
    property DirtyContent: boolean read FDirtyContent write SetDirtyContent;
    property CreatedOn: TDateTime read FCreatedOn write FCreatedOn;
    property Content: string read GetContent write SetContent stored IsContentStored;
    property AttachType: integer read FAttachType write FAttachType;
    property WorkflowStudio: TCustomWorkflowStudio read FWorkflowStudio;
    property WorkKey: string read FWorkKey write FWorkKey; //工作流定义或者实例
  end;

  TAttachmentItems = class(TOwnedCollection)
  private
    FWorkflowStudio: TCustomWorkflowStudio;
    function GetItem(Index: integer): TAttachmentItem;
    procedure SetWorkflowStudio(const Value: TCustomWorkflowStudio);
  public
    constructor Create(AOwner: TPersistent);
    function Add: TAttachmentItem;
    function FindByName(AName: string): TAttachmentItem;
    function AddFile(AFileName: string): TAttachmentItem;
    property Items[Index: integer]: TAttachmentItem read GetItem; default;
    property WorkflowStudio: TCustomWorkflowStudio read FWorkflowStudio write SetWorkflowStudio;
  end;

  TWorkflowAttachment = class(TCollectionItem)
  private
    FName: string;
    FItems: TAttachmentItems;
    procedure SetItems(const Value: TAttachmentItems);
  public
    procedure Assign(Source: TPersistent); override;
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
  published
    property Name: string read FName write FName;
    property Items: TAttachmentItems read FItems write SetItems;
  end;

  TWorkflowAttachments = class(TOwnedCollection)
  private
    FWorkflowStudio: TCustomWorkflowStudio;
    function GetItem(Index: integer): TWorkflowAttachment;
    procedure SetWorkflowStudio(const Value: TCustomWorkflowStudio);
  public
    constructor Create(AOwner: TPersistent);
    function Add: TWorkflowAttachment;
    function FindByName(AName: string): TWorkflowAttachment;
    function AddFile(AName: string; AFileName: string): TAttachmentItem;
    procedure MakeAllDirty;
    property Items[Index: integer]: TWorkflowAttachment read GetItem; default;
    property WorkflowStudio: TCustomWorkflowStudio read FWorkflowStudio write SetWorkflowStudio;
  end;

  TWorkflowEngine = class                            
  private
    FWorkflowStudio: TCustomWorkflowStudio;
    procedure WorkflowTerminated(Sender : TLiveDiagram; ExitCode : integer);
    procedure WorkflowSaveState(Sender: TObject);
  public
    constructor Create(AWorkflowStudio: TCustomWorkflowStudio);

    /// Description:
    ///   Runs the workflow instance specified by WorkIns.
    procedure RunWorkflow(WorkIns: TWorkflowInstance);

    /// Description:
    ///   Checks for pending workflow instances flagged with a next run time. Used to
    ///   resume workflows containing blocks which determine a timeout for expiration.
    ///   The method returns the number of reexecuted workflow instances.
    function RunPendingWorkflowInstances: integer;
  end;

  TCustomWorkflowBlock = class(TCustomLiveBlock)
  private
    FStateShape : TStateShape;
    FOneShot   : boolean;
    FTriggered : boolean;
    FSingleOutput: boolean;
    FAutoHandleTrigger: boolean;
    FOutput: string;
    FLastOutput: string;
    procedure SetFStateShape(const Value: TStateShape);
    procedure DefaultLinkPoints;
    function GetWorkflowDiagram: TCustomWorkflowDiagram;
    procedure LoadTriggeredProp(Reader: TReader);
    procedure StoreTriggeredProp(Writer: TWriter);
    procedure SetOutput(const Value: string);
  protected
    procedure AdjustLinkPoints; virtual;
    function GetLinkPointsCount: integer; virtual;
    procedure DefineProperties(Filer: TFiler); override;
    function GetNext: TCustomLiveBlock; override;
    function BlockPolygon: TDotArray; override;
    procedure GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer); override;
    procedure UpdateLinkPoints; override;
    function AcceptLink(ALink: TCustomDiagramLine; LinkIndex : integer; Direction : TLinkDirection) : boolean; override;
    function ScanTransitions : TCustomLiveBlock; virtual;
    property SingleOutput: boolean read FSingleOutput write FSingleOutput;
    property AutoHandleTrigger: boolean read FAutoHandleTrigger write FAutoHandleTrigger;
    property Output: string read FOutput write SetOutput;
  public
    constructor Create(AOwner : TComponent); override;
    destructor Destroy; override;
    procedure FillOutputList(AOutputs: TStrings); virtual;
    function HasOutputList: boolean;
    procedure Loaded; override;
    procedure DoBeforeRun; override;
    function Link: boolean; override;
    function EditorClass: TWorkflowBlockEditorClass; virtual;
    procedure ExecuteEx(var ExecInfo: TExecuteNodeInfo); override;
    property StateShape : TStateShape read FStateShape write SetFStateShape;
    property OneShot : boolean read FOneShot write FOneShot;
    property WorkflowDiagram: TCustomWorkflowDiagram read GetWorkflowDiagram;
    property Triggered: boolean read FTriggered write FTriggered;
  published
    property LastOutput: string read FLastOutput write FLastOutput;
  end;

  TCustomWorkflowDiagram = class(TLiveDiagram)
  private
    FVariables: TWorkflowVariables;
    FAttachments: TWorkflowAttachments;
    FWorkflowInstance: TWorkflowInstance;
    FWorkflowStudio: TCustomWorkflowStudio;
    FTaskManager: TCustomTaskManager;
    FDisplayTaskStatus: boolean;
    procedure SetVariables(const Value: TWorkflowVariables);
    procedure SetAttachments(const Value: TWorkflowAttachments);
    function GetWorkflowStudio: TCustomWorkflowStudio;
    procedure SetWorkflowStudio(const Value: TCustomWorkflowStudio);
    procedure SetDisplayTaskStatus(const Value: boolean);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    property Variables: TWorkflowVariables read FVariables write SetVariables;
    property Attachments: TWorkflowAttachments read FAttachments write SetAttachments;
    property TaskManager: TCustomTaskManager read FTaskManager;
    property WorkflowStudio: TCustomWorkflowStudio read GetWorkflowStudio write SetWorkflowStudio;
    property WorkflowInstance: TWorkflowInstance read FWorkflowInstance;
    property DisplayTaskStatus: boolean read FDisplayTaskStatus write SetDisplayTaskStatus;
  end;

  TCustomWorkflowManager = class(TComponent)
  public
    procedure LoadWorkflowDefinitionList(WorkDefs: TWorkflowDefinitions); virtual; abstract;
    function FindWorkflowDefinitionByName(AName: string): TWorkflowDefinition; virtual; abstract;
    procedure ListWorkflowDefinitionNames(AList: TStrings; BList: TStrings); virtual; abstract;

    function CreateWorkflowBizList: TWorkflowBizs;  virtual; abstract;
    procedure LoadWorkflowBizList(WorkflowBizs: TWorkflowBizs); virtual; abstract;
    procedure LoadWorkflowBiz(WorkflowBiz: TWorkflowBiz); virtual; abstract;
    procedure CheckWorkflowBiz(WorkflowBiz: TWorkflowBiz; BizKeyValue: string;BillState:String);virtual; abstract;
    procedure UpdateWorkflowBiz(WorkflowBiz: TWorkflowBiz; WorkIns: TWorkflowInstance);virtual; abstract;

    function CreateWorkflowDefinitionList: TWorkflowDefinitions; virtual; abstract;
    function CreateWorkflowInstance(WorkDef: TWorkflowDefinition): TWorkflowInstance; virtual; abstract;
    function CreateWorkflowInstanceByName(WorkDefName: string): TWorkflowInstance; virtual; abstract;
    function CreateWorkflowInstanceByKey(AKey: string): TWorkflowInstance; virtual; abstract;
    function FindWorkflowInstanceByKey(AKey: string): TWorkflowInstance; virtual; abstract;
    procedure ListPendingWorkflowInstances(AKeyList: TStrings); virtual; abstract;

    procedure DeleteWorkflowInstance(WorkIns: TWorkflowInstance); virtual; abstract;
    procedure DeleteWorkflowInstanceByKey(WorkInsKey: string); virtual; abstract;

    procedure SignalWorkflowInstance(AKey: string); virtual; abstract;
    procedure LoadWorkflowInstance(WorkIns: TWorkflowInstance); virtual; abstract;
    procedure SaveWorkflowInstance(WorkIns: TWorkflowInstance); virtual; abstract;
    procedure SaveWorkflowDefinition(WorkDef: TWorkflowDefinition); virtual; abstract;
    procedure LoadWorkflowDefinition(AKey: string; WorkDef: TWorkflowDefinition); virtual; abstract;
    procedure DeleteWorkflowDefinition(WorkDef: TWorkflowDefinition); virtual; abstract;
    procedure AssignWorkflowInstanceDiagram(ADiagram: TCustomWorkflowDiagram; WorkInsKey: string); virtual; abstract;
  end;

  TCustomWorkflowStudio = class(TComponent)
  private
    FOnGetNow: TWorkflowGetNowEvent;
    FWorkflowManager: TCustomWorkflowManager;
    FOnAfterExecuteNode: TWorkflowBlockEvent;
    FOnBeforeExecuteNode: TWorkflowBlockEvent;
    FOnTaskCreated: TWorkflowTaskEvent;
    FTaskManager: TCustomTaskManager;
    //FGroupAssignmentMode: TGroupAssignmentMode;
    FWorkflowEngine: TWorkflowEngine;
    FUserManager: TWorkflowUserManager;
    FInternalScriptEngine: TWorkflowScriptEngine;
    FScriptEngine: TWorkflowScriptEngine;
    FOnTaskFinished: TWorkflowTaskEvent;
    FBeforeSaveTaskInstance: TWorkflowTaskActionEvent;
    FOnInitializeScriptEngine: TWorkflowScriptEngineEvent;
   // procedure SetGroupAssignmentMode(const Value: TGroupAssignmentMode);
    function GetScriptEngine: TWorkflowScriptEngine;
    procedure SetScriptEngine(const Value: TWorkflowScriptEngine);
  protected
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    function GetNow: TDateTime;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure RunFinished(WI: TWorkflowInstance); virtual; abstract;
    procedure WorkflowInstanceError(WI: TWorkflowInstance; ErrMsg: string; var ShowError: boolean); virtual; abstract;
    procedure InitializeScriptEngine(AEngine: TWorkflowScriptEngine); virtual;
    property TaskManager: TCustomTaskManager read FTaskManager write FTaskManager;
    property WorkflowManager: TCustomWorkflowManager read FWorkflowManager write FWorkflowManager;
   // property GroupAssignmentMode: TGroupAssignmentMode read FGroupAssignmentMode write SetGroupAssignmentMode;
    property WorkflowEngine: TWorkflowEngine read FWorkflowEngine;
    property UserManager: TWorkflowUserManager read FUserManager;
    property ScriptEngine: TWorkflowScriptEngine read GetScriptEngine write SetScriptEngine;
    property OnAfterExecuteNode: TWorkflowBlockEvent read FOnAfterExecuteNode write FOnAfterExecuteNode;
    property OnBeforeExecuteNode: TWorkflowBlockEvent read FOnBeforeExecuteNode write FOnBeforeExecuteNode;
    property OnTaskCreated: TWorkflowTaskEvent read FOnTaskCreated write FOnTaskCreated;
    property OnTaskFinished: TWorkflowTaskEvent read FOnTaskFinished write FOnTaskFinished;
    property OnGetNow: TWorkflowGetNowEvent read FOnGetNow write FOnGetNow;
    property BeforeSaveTaskInstance: TWorkflowTaskActionEvent read FBeforeSaveTaskInstance write FBeforeSaveTaskInstance;
    property OnInitializeScriptEngine: TWorkflowScriptEngineEvent read FOnInitializeScriptEngine write FOnInitializeScriptEngine;
  end;

  TWorkflowBlockEditor = class
  public
    procedure EditBlock(ABlock: TCustomWorkflowBlock); virtual; abstract;
  end;
  
  TTaskField = class(TCollectionItem)
  private
    FRequired: boolean;
    FReadOnly: boolean;
    FCaption: string;
    FWorkflowVarName: string;
  public
    procedure Assign(Source: TPersistent); override;
  published
    property Caption: string read FCaption write FCaption;
    property ReadOnly: boolean read FReadOnly write FReadOnly;
    property Required: boolean read FRequired write FRequired;
    property WorkflowVarName: string read FWorkflowVarName write FWorkflowVarName;
    //property EditorType (dropdown, check, freeedit, date)
    //property DecisionMaker: boolean
    //property DropDownOptions
  end;

  TTaskFields = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TTaskField;
  public
    function Add: TTaskField;
    function FindByVarName(AVarName: string):TTaskField;
    property Items[Index: integer]: TTaskField read GetItem; default;
  end;
     //任务关联用户类型 未指定，用户，角色，职位，部门，部门主管
  TAssignedUserType = (autUser,autGroup,autJob,autDepartment,autDepartmentManager);

   TTaskAssignedUser = class(TCollectionItem)
  private
    FAssignedUserID: string;
    FAssignedUserName: string;
    FStepDefin:integer;
    FAssignedUserType: TAssignedUserType;
    FCanPrint: boolean; //能否打印
    FAssignmentMode: TGroupAssignmentMode;
    FNeedPrjRight: boolean;//是否需要项目权限
  public
    procedure Assign(Source: TPersistent); override;
  published
    property AssignedUserName: string read FAssignedUserName write FAssignedUserName;
    property AssignedUserID: string read FAssignedUserID write FAssignedUserID;
    property StepDefin: integer read FStepDefin write FStepDefin default 0;
    property AssignedUserType:TAssignedUserType read FAssignedUserType write FAssignedUserType;
    property CanPrint: boolean read FCanPrint write FCanPrint;
    property AssignmentMode: TGroupAssignmentMode read FAssignmentMode write FAssignmentMode;
    property NeedPrjRight: boolean read FNeedPrjRight write FNeedPrjRight default False;
  end;

  TTaskAssignedUsers = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TTaskAssignedUser;
  public
    function Add: TTaskAssignedUser;
    property Items[Index: integer]: TTaskAssignedUser read GetItem; default;
  end;

  TTaskDefinition = class(TCollectionItem)
  private
    FDescription: string;
    FName: string;
    //FAssignmentRule: string;
    FStatusList: TStrings;
    FTaskInstanceKeys: TStrings;
    FPreviousTaskInsKeys: TStrings;
    FKey: string;
    FSubject: string;
    FMailNotification: boolean;
    FShowAttachments: boolean;
    FAttachmentPermissions: TAttachmentPermissions;
    FFields: TTaskFields;
    FUsers:  TTaskAssignedUsers;
    FExpirationDateTime: string;
    FExpirationStatus: string;
    FHiddenStatusList: TStrings;
    procedure SetStatusList(const Value: TStrings);
    function GetInitialStatus: string;
    procedure SetFields(const Value: TTaskFields);
    procedure SetUsers(const Value: TTaskAssignedUsers);
    procedure SetHiddenStatusList(const Value: TStrings);
    function GetStatusCount: integer;
    function GetStatusHidden(i: integer): boolean;
    procedure SetStatusHidden(i: integer; const Value: boolean);
    function GetStatusName(i: integer): string;
    procedure SetStatusName(i: integer; const Value: string);
    function GetStatusCompletion(i: integer): boolean;
    procedure SetStatusCompletion(i: integer; const Value: boolean);
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
    procedure Assign(Source: TPersistent); override;
    function IsCompletionStatus(AStatus: string): boolean;
    procedure FillStatusList(AList: TStrings; AIncludeHidden: boolean=False);
    function StatusAdd(AStatus: string; ACompletion: boolean=False; AHidden: boolean=False): integer;
    procedure StatusDelete(AStatus: string);
    property InitialStatus: string read GetInitialStatus;
    property StatusCount: integer read GetStatusCount;
    property StatusName[i: integer]: string read GetStatusName write SetStatusName;
    property StatusCompletion[i: integer]: boolean read GetStatusCompletion write SetStatusCompletion;
    property StatusHidden[i: integer]: boolean read GetStatusHidden write SetStatusHidden;
  published
    property Key: string read FKey write FKey;
    property Name: string read FName write FName;
    property Subject: string read FSubject write FSubject;
    property Description: string read FDescription write FDescription;
    property Users: TTaskAssignedUsers read FUsers write SetUsers;
    //property AssignmentRule: string read FAssignmentRule write FAssignmentRule;
    property StatusList: TStrings read FStatusList write SetStatusList;
    property HiddenStatusList: TStrings read FHiddenStatusList write SetHiddenStatusList;
    property TaskInstanceKeys: TStrings read FTaskInstanceKeys write FTaskInstanceKeys;
    property PreviousTaskInsKeys: TStrings read FPreviousTaskInsKeys write FPreviousTaskInsKeys;
    property MailNotification: boolean read FMailNotification write FMailNotification;
    property ShowAttachments: boolean read FShowAttachments write FShowAttachments;
    property AttachmentPermissions: TAttachmentPermissions read FAttachmentPermissions write FAttachmentPermissions;
    property Fields: TTaskFields read FFields write SetFields;
    property ExpirationDateTime: string read FExpirationDateTime write FExpirationDateTime;
    property ExpirationStatus: string read FExpirationStatus write FExpirationStatus;
  end;

  TTaskDefinitions = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TTaskDefinition;
  public
    constructor Create(AOwner: TComponent);
    function Add: TTaskDefinition;
    function FindByName(AName: string): TTaskDefinition;
    property Items[Index: integer]: TTaskDefinition read GetItem; default;
    function GetOwner: TPersistent; override;
  end;

  TTaskInstance = class(TComponent)
  private
    FContainer: TDataModule;
    FDiagram: TLiveDiagram;
    FComments: string;
    FStatus: string;
    FUserID: string;
    FKey: string;
    FWorkInsKey: string;
    FTaskDef: TTaskDefinition;
   // FDefinitionKey: string;
    FCreatedOn: TDateTime;
    FCanPrint: boolean;
    FAssignedUserType: TAssignedUserType;
    FFlowMnDtlChkTime: TDateTime;
    FFlowMnDtlLimitTime: TDateTime;  //过期时间
    FFlowMnDtlNum: integer;
    FFlowMnDtlReceiver: string;    {FModifiedUserIdField}
    FFlowMnDtlStateChgTime: TDateTime;   {FModifiedOnField}
    FFlowMnDtlRemark: string;
    FFlowMnDtlStepDefin: integer;
    FFlowMnDtlProjectID: string;
    FNeedPrjRight: boolean;
    procedure SetTaskDef(const Value: TTaskDefinition);
    function GetCompleted: boolean;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;

    /// Description:
    ///   Returns true if the user specified by AUserId can update the task (task is assigned to the
    ///   user or to the group which user belongs to, or user belongs to an administrator group)
    function CanUpdate(AUserId: string; AWorkflowStudio: TCustomWorkflowStudio): boolean;

    function IsCompletionStatus(AStatus: string): boolean;
    property Completed: boolean read GetCompleted;
  published
    property NeedPrjRight: boolean read FNeedPrjRight write FNeedPrjRight default False;
    property Key: string read FKey write FKey;
    property WorkInsKey: string read FWorkInsKey write FWorkInsKey;
    {流程发起后，不能在指向流程定义，而应该指向流程实例}
  //  property DefinitionKey: string read FDefinitionKey write FDefinitionKey;

    /// Description:
    ///   ID of user to which the task instance is assigned to. Note: UserId can be an ID for a user or a group.
    property UserID: string read FUserID write FUserID;

    /// Description:
    ///   Current status of the task instance.
    property Status: string read FStatus write FStatus;

    /// Description:
    ///   Comments about the task instance.
    property Comments: string read FComments write FComments;

    /// Description:
    ///   Reference to TTaskDefinition object which contains the task definition.
    /// See also:
    ///   TTaskDefinition
    property TaskDef: TTaskDefinition read FTaskDef write SetTaskDef;

    /// Description:
    ///   Creation date of the task instance.
    property CreatedOn: TDateTime read FCreatedOn write FCreatedOn;
    property CanPrint: boolean read FCanPrint write FCanPrint;
    property AssignedUserType: TAssignedUserType read FAssignedUserType write FAssignedUserType;
    property FlowMnDtlChkTime: TDateTime read FFlowMnDtlChkTime write FFlowMnDtlChkTime;
    property FlowMnDtlLimitTime: TDateTime read FFlowMnDtlLimitTime write FFlowMnDtlLimitTime;
    property FlowMnDtlNum: integer read FFlowMnDtlNum write FFlowMnDtlNum;
    property FlowMnDtlReceiver: string read FFlowMnDtlReceiver write FFlowMnDtlReceiver;    {FModifiedUserIdField}
    property FlowMnDtlStateChgTime: TDateTime read FFlowMnDtlStateChgTime write FFlowMnDtlStateChgTime;   {FModifiedOnField}
    property FlowMnDtlRemark: string read FFlowMnDtlRemark write FFlowMnDtlRemark;
    property FlowMnDtlStepDefin: integer read FFlowMnDtlStepDefin write FFlowMnDtlStepDefin default 0;
    property FlowMnDtlProjectID: string read FFlowMnDtlProjectID write FFlowMnDtlProjectID;
  end;

  TTaskInstanceItem = class(TCollectionItem)
  private
    FTask: TTaskInstance;
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
    property Task: TTaskInstance read FTask;
  end;

  TTaskInstanceList = class(TCollection)
  private
    function GetItem(index: integer): TTaskInstanceItem;
  public
    function Add: TTaskInstanceItem;
    function FindByKey(ATaskInsKey:string):TTaskInstanceItem;
    property Items[index: integer]: TTaskInstanceItem read GetItem; default;
  end;

  TCustomTaskManager = class(TComponent)
  public
    procedure CreateTaskInstance(WorkIns: TWorkflowInstance; TaskDef: TTaskDefinition); virtual; abstract;
    procedure LoadTaskInstance(TaskIns: TTaskInstance); virtual; abstract;
    procedure SaveTaskInstance(TaskIns: TTaskInstance); virtual; abstract;
    procedure UpdateTaskInstance(TaskIns: TTaskInstance); virtual; abstract;
    function IsTaskFinished(AKey: string): boolean; virtual; abstract;
    procedure LoadTaskInstanceList(ATasks: TTaskInstanceList;AFilterType: TTaskFilterType; AFilterKey: string;
              completeState: integer; AOtherCondition: string=''); virtual; abstract;
    function TaskExpirationDateTime(AWorkIns: TWorkflowInstance; ATaskInstance: TTaskInstance): TDateTime; virtual; abstract;
    procedure LogTaskInfo(TaskIns: TTaskInstance; Info: string); virtual; abstract;
  end;

  TTaskLogOperation = (tlNone, tlStatusChange, tlUpdate, tlCreate, tlInfo);

  TTaskLogItem = class(TCollectionItem)
  private
    FIndexID: integer;
    FTaskInsKey: string;
    FInfo: string;
    FUserId: string;
    FEventDate: TDateTime;
    FOperation: TTaskLogOperation;
    FInfo2: string;
    FFlowInsKey: string;
  public
    property Operation: TTaskLogOperation read FOperation write FOperation;
    property TaskInsKey: string read FTaskInsKey write FTaskInsKey;
    property EventDate: TDateTime read FEventDate write FEventDate;
    property UserId: string read FUserId write FUserId;
    property Info: string read FInfo write FInfo;
    property Info2: string read FInfo2 write FInfo2;
    property FlowInsKey: string read FFlowInsKey write FFlowInsKey;
    property IndexID:integer read FIndexID write FIndexID;
  end;

  TTaskLogItems = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TTaskLogItem;
  public
    function Add: TTaskLogItem;
    property Items[Index: integer]: TTaskLogItem read GetItem; default;
  end;

  TScriptContext = (scRuntimeInstance, scDesignDiagram);

  TWorkflowScriptEngine = class(TComponent)
  private
    FExprDelim: string;
    FWorkIns: TWorkflowInstance;
    FRunContext: TScriptContext;
    FDiagram: TCustomWorkflowDiagram;
    FTaskIns: TTaskInstance;
    function ExtractExpression(AText, OpenDelim, CloseDelim: string; var i, j: Integer): string;
  protected
    function ExpressionToStr(Value: Variant): string;
    property WorkflowInstance: TWorkflowInstance read FWorkIns;
    property TaskInstance: TTaskInstance read FTaskIns;
    property Diagram: TCustomWorkflowDiagram read FDiagram;
    procedure RunContextChanged; virtual; abstract;
    property RunContext: TScriptContext read FRunContext;
  public
    constructor Create(AOwner: TComponent); override;
    procedure SetRuntimeContext(AWorkIns: TWorkflowInstance; ATaskIns: TTaskInstance=nil);
    procedure SetDesignContext(ADiagram: TCustomWorkflowDiagram);
    function CalculateExpression(Expr: string): Variant; virtual;
    function TranslateText(AText: string): string;
  end;

  TWorkflowUser = class(TCollectionItem)
  private
    FUserName: string;
    FEmail: string;
    FUserId: string; //员工ID
    FUserCode: string; //员工编码
//    FUserLoginCode: string; //登录名称
    FPhoneCode: string;
    FCanPrint: boolean;
    FStepDefin :integer;
    FNeedPrjRight: boolean;
    function GetUserNameOrId: string;
    function GetUserManager: TWorkflowUserManager;
  public
    property UserManager: TWorkflowUserManager read GetUserManager;

    /// Description:
    ///   Fills a string list with the list of group ID's to which the user belongs to
    procedure FillGroupIds(AGroupIds: TStrings);
    procedure FillJobIds(AJobIds: TStrings);
    procedure FillDepartmentIds(ADepartmentIds: TStrings);

    /// Description:
    ///   Returns true if the user belongs to the group specified by AGroupId
    function BelongsToGroup(AGroupId: string): boolean;
    function BelongsToJob(AJobId: string): boolean;
    function BelongsToDepartment(ADepartmentId: string): boolean;

    /// Description:
    ///   Returns true if the user belongs to an administrator group
    function BelongsToAdminGroup: boolean;


  published
    property UserName: string read GetUserNameOrId write FUserName;
    property UserId: string read FUserId write FUserId;
    property Email: string read FEmail write FEmail;
    property CanPrint: boolean read FCanPrint write FCanPrint; //协助传递
    property StepDefin :integer read FStepDefin write FStepDefin;
    property PhoneCode: string read FPhoneCode write FPhoneCode;
    property UserCode: string read FUserCode write FUserCode;
    property NeedPrjRight: boolean read FNeedPrjRight write FNeedPrjRight;
//    property UserLoginCode: string read FUserLoginCode write FUserLoginCode;
  end;

  TWorkflowUsers = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TWorkflowUser;
  public
    function FindById(AName: string): TWorkflowUser;
    function FindByName(AName: string): TWorkflowUser;
    function Add: TWorkflowUser; overload;
    function Add(AUserID: string; AUserName: string = ''; AEmail: string = '';AUserCode: string=''): TWorkflowUser; overload;
    property Items[Index: integer]: TWorkflowUser read GetItem; default;
  end;

  TWorkflowGroup = class(TCollectionItem)
  private
    FGroupName: string;
    FUserIds: TStrings;
    FGroupId: string;
    FCanPrint: boolean;
    FIsAdmin: boolean;
    FStepDefin :integer;
    FNeedPrjRight: boolean;
    procedure SetUserIds(const Value: TStrings);
    function GetUserManager: TWorkflowUserManager;
    function GetGroupId: string;
    function GetGroupName: string;
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
    property UserManager: TWorkflowUserManager read GetUserManager;
  published
    property GroupId: string read GetGroupId write FGroupId;
    property GroupName: string read GetGroupName write FGroupName;
    property UserIds: TStrings read FUserIds write SetUserIds;
    property IsAdmin: boolean read FIsAdmin write FIsAdmin default false;
    property CanPrint: boolean read FCanPrint write FCanPrint; //协助传递
    property StepDefin :integer read FStepDefin write FStepDefin;
     property NeedPrjRight: boolean read FNeedPrjRight write FNeedPrjRight;
  end;

  TWorkflowGroups = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TWorkflowGroup;
  public
    function FindByName(AName: string): TWorkflowGroup;
    function FindByID(AId: string): TWorkflowGroup;
    function Add: TWorkflowGroup; overload;

    /// Description:
    ///   Adds a group with name specified by AGroupName. The GroupID property will also be set with AGroupName
    function Add(AGroupName: string): TWorkflowGroup; overload;
    
    function Add(AGroupID: string; AGroupName: string): TWorkflowGroup; overload;
    property Items[Index: integer]: TWorkflowGroup read GetItem; default;
  end;

  TWorkflowDepartment = class(TCollectionItem)
  private
    FDepartmentName: string;
    FUserIds: TStrings;
    FDepartmentId: string;
    FDepartmentManagerId: string;
//    FDepartmentManagerName: string;
    FCanPrint: boolean;
    FStepDefin :integer;
    FNeedPrjRight: boolean;
    procedure SetUserIds(const Value: TStrings);
    function GetUserManager: TWorkflowUserManager;
    function GetDepartmentId: string;
    function GetDepartmentName: string;
    function GetDepartmentManagerId: string;
//    function GetDepartmentManagerName: string;
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
    property UserManager: TWorkflowUserManager read GetUserManager;
  published
    property CanPrint: boolean read FCanPrint write FCanPrint; //协助传递
    property StepDefin :integer read FStepDefin write FStepDefin;
    property DepartmentId: string read GetDepartmentId write FDepartmentId;
    property DepartmentName: string read GetDepartmentName write FDepartmentName;
    property DepartmentManagerId: string read GetDepartmentManagerId write FDepartmentManagerId;
//    property DepartmentManagerName: string read GetDepartmentManagerName write FDepartmentManagerName;
    property UserIds: TStrings read FUserIds write SetUserIds;
    property NeedPrjRight: boolean read FNeedPrjRight write FNeedPrjRight;
  end;

  TWorkflowDepartments = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TWorkflowDepartment;
  public
    function FindByName(AName: string): TWorkflowDepartment;
    function FindByID(AId: string): TWorkflowDepartment;
    function Add: TWorkflowDepartment; overload;
    {The function below adds a Department with name specified by ADepartmentName. The DepartmentID property will also
     be set with ADepartmentName}
    function Add(ADepartmentName: string): TWorkflowDepartment; overload;
    function Add(ADepartmentID: string; ADepartmentName: string): TWorkflowDepartment; overload;
    property Items[Index: integer]: TWorkflowDepartment read GetItem; default;
  end;

  TWorkflowJob = class(TCollectionItem)
  private
    FJobName: string;
    FUserIds: TStrings;
    FJobId: string;
    FCanPrint: boolean;
    FStepDefin :integer;
    FNeedPrjRight: boolean;
    procedure SetUserIds(const Value: TStrings);
    function GetUserManager: TWorkflowUserManager;
    function GetJobId: string;
    function GetJobName: string;
  public
    constructor Create(Collection: TCollection); override;
    destructor Destroy; override;
    property UserManager: TWorkflowUserManager read GetUserManager;
  published
    property CanPrint: boolean read FCanPrint write FCanPrint; //协助传递
    property StepDefin :integer read FStepDefin write FStepDefin;
    property JobId: string read GetJobId write FJobId;
    property JobName: string read GetJobName write FJobName;
    property UserIds: TStrings read FUserIds write SetUserIds;
    property NeedPrjRight: boolean read FNeedPrjRight write FNeedPrjRight;
  end;

  TWorkflowJobs = class(TOwnedCollection)
  private
    function GetItem(Index: integer): TWorkflowJob;
  public
    function FindByName(AName: string): TWorkflowJob;
    function FindByID(AId: string): TWorkflowJob;
    function Add: TWorkflowJob; overload;
    {The function below adds a Job with name specified by AJobName. The JobID property will also
     be set with AJobName}
    function Add(AJobName: string): TWorkflowJob; overload;
    function Add(AJobID: string; AJobName: string): TWorkflowJob; overload;
    property Items[Index: integer]: TWorkflowJob read GetItem; default;
  end;

  TWorkflowUserManager = class(TComponent)
  private
    FUsers: TWorkflowUsers;
    FGroups: TWorkflowGroups;
    FJobs: TWorkflowJobs;
    FDepartments: TWorkflowDepartments;
    FLoggedUserId: string;  //员工ID
    FLoggedUserCode: string; //员工编码
//    FLoggedUserLoginCode: string; //登录名称
    FWorkflowStudio: TCustomWorkflowStudio;
  public
    constructor Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio); reintroduce;
    destructor Destroy; override;

    /// Description:
    ///   Fills the AUserList object with a list of TWorkflowUser and/or TWorkflowGroup objects based on the name specified by AUserName.
    ///   The AUserName can be the name of an user or a group. The objects filled depends also on the value of WorkflowStudio.GroupAssignedMode property.
    ///   In summary, this function translates the assignment text specified by the end-user in the task definition dialog, to a list of objects
    ///   to which the task must be assigned
    procedure GetAssignedUserList(AAssignedUsers: TTaskAssignedUsers; AUserList: TStringList; AProjectID: String);
    procedure LoadWorkflowUsers();
    procedure LoadWorkflowGroups();
    procedure LoadWorkflowJobs();
    procedure LoadWorkflowDepartments();
    /// Description:
    ///   Fill the AList with the names of all users and groups, for the purpose of choosing an user or group from a list.
    ///   If AddObjects is true, the method will also add a reference to the object in the AList.Objects[] property
    procedure FillAssignmentList(AList: TStrings; AddObjects: boolean = false);
    procedure FillUserList(AList: TStrings; AddObjects: boolean = false);
    procedure FillGroupList(AList: TStrings; AddObjects: boolean = false);
    procedure FillJobList(AList: TStrings; AddObjects: boolean = false);
    procedure FillDepartmentList(AList: TStrings;AddObjects: boolean = false);

    /// Description:
    ///   Returns true if both userids are the same
    function IsSameUser(AUserId1, AUserId2: string): boolean;

    /// Description:
    ///   Returns true if AUserId belongs to group specified by AGroupId
    function BelongsToGroup(AUserId, AGroupId: string): boolean;
    function BelongsToJob(AUserId,AJobId: string): boolean;
    function BelongsToDepartment(AUserId,ADepartmentId: string): boolean;

    /// Description:
    ///   Returns true if AUserId belongs to an administrator group
    function BelongsToAdminGroup(AUserId: string): boolean;

    function BelongsToProject(AUserId,AProjectId: string): boolean;

    property Users: TWorkflowUsers read FUsers;
    property Groups: TWorkflowGroups read FGroups;
    property Jobs: TWorkflowJobs read FJobs;
    property Departments: TWorkflowDepartments read FDepartments;
    property LoggedUserId: string read FLoggedUserId write FLoggedUserId;
    property LoggedUserCode: string read FLoggedUserCode write FLoggedUserCode;
//    property LoggedUserLoginCode: string read FLoggedUserCode write FLoggedUserLoginCode;
  end;

  TEmailInformation = record
    ToAddr: string;
    From: string;
    Bcc: string;
    Cc: string;
    Subject: string;
    Text: string;
  end;
  TFtpInformation = record
    HostName: string;
	  UserName: string;
	  Password: string;
	  Root: string;
	  SpaceName: string;
    FtpDirectory: string;
	  Port: integer;
	  Passive: boolean;
  end;

const
  AllAttachmentPermissions = [apDelete, apInsert, apEdit];
  wsFormName = '_wsFormName_';
implementation

uses
  wsRes, ShellApi, DgrGdipApi,
  wsDB, wsBlocks, wsDiagram, wsMain;

{ TWorkflowDefinitions }

function TWorkflowDefinitions.Add: TWorkflowDefinition;
begin
  result := TWorkflowDefinition(inherited Add);
end;

constructor TWorkflowDefinitions.Create(AOwner: TComponent);
begin
  inherited Create(AOwner, TWorkflowDefinition);
end;

function TWorkflowDefinitions.FindByKey(AKey: string): TWorkflowDefinition;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if AKey = Items[c].Key then
    begin
      result := Items[c];
      break;
    end;
end;

function TWorkflowDefinitions.FindByName(
  AName: string): TWorkflowDefinition;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if SameText(AName, Items[c].Name) then
    begin
      result := Items[c];
      break;
    end;
end;

function TWorkflowDefinitions.FindNewName: string;
var
  c: integer;
begin
  c := 0;
  repeat
    inc(c);
    result := Format('%s %d', [_str(SWorkflowDefinition), c]);
  until (FindByName(result) = nil);
end;

function TWorkflowDefinitions.GetItem(Index: integer): TWorkflowDefinition;
begin
  result := TWorkflowDefinition(inherited Items[Index]);
end;

procedure TWorkflowDefinitions.SetWorkflowStudio(const Value: TCustomWorkflowStudio);
var
  i: integer;
begin
  FWorkflowStudio := Value;
  for i:=0 to Count-1 do
    Items[i].WorkflowStudio := FWorkflowStudio;
end;

{ TWorkflowDefinition }

procedure TWorkflowDefinition.AssignFromDiagram(ADiagram: TCustomWorkflowDiagram);
var
  TempStream: TMemoryStream;
  oldName: string;
begin
  TempStream := TMemoryStream.Create;
  try
    oldName := ADiagram.Owner.Name;
    ADiagram.Owner.Name := wsFormName;
    ADiagram.SaveToStream(TempStream);
    ADiagram.Owner.Name := oldName;

    TempStream.Position := 0;

    oldName := FDiagram.Owner.Name;
    FDiagram.Owner.Name := wsFormName;
    FDiagram.LoadFromStream(TempStream);
    FDiagram.Owner.Name := oldName;
  finally
    TempStream.Free;
  end;
  Changed(false);
end;

procedure TWorkflowDefinition.AssignToDiagram(ADiagram: TCustomWorkflowDiagram);
var
  TempStream: TMemoryStream;
  oldName: string;
begin
  TempStream := TMemoryStream.Create;
  try
    oldName := FDiagram.Owner.Name;
    FDiagram.Owner.Name := wsFormName;
    FDiagram.SaveToStream(TempStream, true);
    FDiagram.Owner.Name := oldName;

    TempStream.Position := 0;

    oldName := ADiagram.Owner.Name;
    ADiagram.Owner.Name := wsFormName;
    ADiagram.LoadFromStream(TempStream, true);
    ADiagram.Owner.Name := oldName;
  finally
    TempStream.Free;
  end;
end;

constructor TWorkflowDefinition.Create(AWorkflowStudio: TCustomWorkflowStudio);
begin
  Initialize(AWorkflowStudio);
end;

constructor TWorkflowDefinition.Create(Collection: TCollection);
var
  wkf: TCustomWorkflowStudio;
begin
  inherited Create(Collection);
  if (Collection <> nil) and (Collection is TWorkflowDefinitions) then
    wkf := TWorkflowDefinitions(Collection).WorkflowStudio
  else
    wkf := nil;
  Initialize(wkf);
end;

destructor TWorkflowDefinition.Destroy;
begin
  if FContainer <> nil then
    FContainer.Free;
  FContainer := nil;
  FDiagram := nil;
  inherited;
end;

function TWorkflowDefinition.GetWorkflowStudio: TCustomWorkflowStudio;
begin
  result := FDiagram.WorkflowStudio;
end;

procedure TWorkflowDefinition.Initialize(AWorkflowStudio: TCustomWorkflowStudio);
begin
  if AWorkflowStudio <> nil then
  begin
    FContainer := TForm.Create(nil);
    FDiagram := TWorkflowDiagram.Create(FContainer);
    FDiagram.WorkflowStudio := AWorkflowStudio;
    FDiagram.Parent := FContainer;
  end
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);
end;

procedure TWorkflowDefinition.SetKey(const Value: string);
begin
  if FKey <> Value then
  begin
    FKey := Value;
    //Changed(false);
  end;
end;

procedure TWorkflowDefinition.SetName(const Value: string);
begin
  if FName <> Value then
  begin
    FName := Value;
    //Changed(false);
  end;
end;

procedure TWorkflowDefinition.SetWorkflowStudio(const Value: TCustomWorkflowStudio);
begin
  FDiagram.WorkflowStudio := Value;
end;

(*{ TWorkflowInstances }

function TWorkflowInstances.Add: TWorkflowInstance;
begin
  result := TWorkflowInstance(inherited Add);
end;

constructor TWorkflowInstances.Create(AOwner: TComponent);
begin
  inherited Create(AOwner, TWorkflowInstance);
end;

function TWorkflowInstances.GetItem(Index: integer): TWorkflowInstance;
begin
  result := TWorkflowInstance(inherited Items[Index]);
end;*)

{ TWorkflowInstance }

procedure TWorkflowInstance.AssignFromDiagram(ADiagram: TCustomWorkflowDiagram; State: boolean);
var
  TempStream: TMemoryStream;
  oldName: string;
begin
  TempStream := TMemoryStream.Create;
  try
    oldName := ADiagram.Owner.Name;
    ADiagram.Owner.Name := wsFormName;
    if State then
      ADiagram.SaveStateToStream(TempStream)
    else
      ADiagram.SaveToStream(TempStream);
    ADiagram.Owner.Name := oldName;

    TempStream.Position := 0;

    oldName := FDiagram.Owner.Name;
    FDiagram.Owner.Name := wsFormName;
    if State then
      FDiagram.LoadStateFromStream(TempStream)
    else
      FDiagram.LoadFromStream(TempStream);
    FDiagram.Owner.Name := oldName;
    //指向本地
    FDiagram.WorkflowStudio := FWorkflowStudio;
  finally
    TempStream.Free;
  end;
end;

procedure TWorkflowInstance.AssignToDiagram(ADiagram: TCustomWorkflowDiagram; State: boolean);
var
  TempStream: TMemoryStream;
  oldName: string;
begin
  TempStream := TMemoryStream.Create;
  try
    oldName := FDiagram.Owner.Name;
    FDiagram.Owner.Name := wsFormName;
    if State then
      FDiagram.SaveStateToStream(TempStream, true)
    else
      FDiagram.SaveToStream(TempStream, true);
    FDiagram.Owner.Name := oldName;

    TempStream.Position := 0;

    oldName := ADiagram.Owner.Name;
    ADiagram.Owner.Name := wsFormName;
    if State then
      ADiagram.LoadStateFromStream(TempStream, true)
    else
      ADiagram.LoadFromStream(TempStream, true);
    ADiagram.Owner.Name := oldName;
  finally
    TempStream.Free;
  end;
end;

constructor TWorkflowInstance.Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio);
begin
  inherited Create(AOwner);
  if AWorkflowStudio <> nil then
    FWorkflowStudio := AWorkflowStudio
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);
  FStatus := wsNotStarted;
  FParentKey := '';
  FChildKey := '';
  FFlowMnPrjID :='';
  FContainer := TForm.Create(nil);
  FDiagram := TWorkflowDiagram.Create(FContainer);
  FDiagram.WorkflowStudio := AWorkflowStudio;
  FDiagram.Parent := FContainer;
  FDiagram.FWorkflowInstance := Self;
end;

procedure TWorkflowInstance.DefineProperties(Filer: TFiler);
begin
  inherited;
  Filer.DefineProperty('Diagram', LoadDiagramProp, StoreDiagramProp, true);
end;

destructor TWorkflowInstance.Destroy;
begin
  FContainer.Free;
  FContainer := nil;
  FDiagram := nil;
  inherited;
end;

procedure TWorkflowInstance.LoadDiagramProp(Reader: TReader);
var
  DiagramStr: string;
begin
  DiagramStr := Reader.ReadString;

  Case Status of
    wsRunning:
      StateFromString(FDiagram, DiagramStr);
  else
    {wsNotStarted, wsFinished}
    DiagramFromString(FDiagram, DiagramStr);
  end;
end;

procedure TWorkflowInstance.StoreDiagramProp(Writer: TWriter);
var
  DiagramStr: string;
begin
  Case Status of
    wsRunning:
      DiagramStr := StateToString(FDiagram);
  else
    {wsNotStarted, wsFinished}
    DiagramStr := DiagramToString(FDiagram);
  end;

  Writer.WriteString(DiagramStr);
end;

{ TWorkflowVariables }

function TWorkflowVariables.Add: TWorkflowVariable;
begin
  result := TWorkflowVariable(inherited Add);
end;

function TWorkflowVariables.FindByName(AName: string): TWorkflowVariable;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if SameText(AName, Items[c].Name) then
    begin
      result := Items[c];
      break;
    end;
end;

function TWorkflowVariables.GetItem(Index: integer): TWorkflowVariable;
begin
  result := TWorkflowVariable(inherited Items[Index]);
end;
{TWorkflowBiz}
procedure TWorkflowBiz.Assign(Source: TPersistent);
begin
  if Source is TWorkflowBiz then
  begin
    BizName := TWorkflowBiz(Source).BizName;
    BizFormID := TWorkflowBiz(Source).BizFormID;
    BizMenuID := TWorkflowBiz(Source).BizMenuID;
    BizTableName := TWorkflowBiz(Source).BizTableName;
    BizKey := TWorkflowBiz(Source).BizKey;
    BizCheck := TWorkflowBiz(Source).BizCheck;
    BizChecker := TWorkflowBiz(Source).BizCheck;
    BizCheckDate := TWorkflowBiz(Source).BizCheckDate;
    BizEditMenuID :=TWorkflowBiz(Source).BizEditMenuID;
    BizCheckValue :=TWorkflowBiz(Source).BizCheckValue;
  end else
    inherited Assign(Source);
end;
{TWorkflowBizs}
function TWorkflowBizs.Add: TWorkflowBiz;
begin
  result := TWorkflowBiz(inherited Add);
end;

function TWorkflowBizs.GetItem(Index: integer): TWorkflowBiz;
begin
  result := TWorkflowBiz(inherited Items[Index]);
end;

function TWorkflowBizs.FindByBizFormID(ABizFormID: string): TWorkflowBiz;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if ABizFormID = Items[c].BizFormID then
    begin
      result := Items[c];
      exit;
    end;
end;

function TWorkflowBizs.FindByBizMenuID(ABizMenuID: string): TWorkflowBiz;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if ABizMenuID = Items[c].BizMenuID then
    begin
      result := Items[c];
      exit;
    end;
end;
function TWorkflowBizs.FindByBizEditMenuID(ABizEditMenuID: string): TWorkflowBiz;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if ABizEditMenuID = Items[c].BizEditMenuID then
    begin
      result := Items[c];
      exit;
    end;
end;
{ TWorkflowVariable }

procedure TWorkflowVariable.Assign(Source: TPersistent);
begin
  if Source is TWorkflowVariable then
  begin
    FName := TWorkflowVariable(Source).FName;
    FValue := TWorkflowVariable(Source).FValue;
    FInteraction :=TWorkflowVariable(Source).FInteraction;
  end else
    inherited Assign(Source);
end;

{ TWorkflowAttachments }

function TWorkflowAttachments.Add: TWorkflowAttachment;
begin
  result := TWorkflowAttachment(inherited Add);
  result.Items.WorkflowStudio := FWorkflowStudio;
end;

constructor TWorkflowAttachments.Create(AOwner: TPersistent);
begin
  inherited Create(AOwner, TWorkflowAttachment);
end;

function TWorkflowAttachments.FindByName(AName: string): TWorkflowAttachment;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if SameText(AName, Items[c].Name) then
    begin
      result := Items[c];
      break;
    end;
end;

procedure TWorkflowAttachments.MakeAllDirty;
var
  c, d: integer;
begin
  for c := 0 to Count - 1 do
    for d := 0 to Items[c].Items.Count - 1 do
    begin
      Items[c].Items[d].SetContent(Items[c].Items[d].GetContent);
      Items[c].Items[d].Key := '';
    end;
end;

function TWorkflowAttachments.AddFile(AName: string; AFileName: string): TAttachmentItem;
var
  AItem: TWorkflowAttachment;
begin
  AItem := FindByName(AName);
  if AItem = nil then
  begin
    AItem := Add;
    AItem.Name := AName;
  end;
  result := AItem.Items.AddFile(AFileName);
end;

procedure TWorkflowAttachments.SetWorkflowStudio(const Value: TCustomWorkflowStudio);
var
  i: integer;
begin
  FWorkflowStudio := Value;
  for i:=0 to Count-1 do
    Items[i].Items.WorkflowStudio := FWorkflowStudio;
end;

{ TWorkflowAttachment }

procedure TWorkflowAttachment.Assign(Source: TPersistent);
begin
  if Source is TWorkflowAttachment then
  begin
    FName := TWorkflowAttachment(Source).FName;
    FItems.Assign(TWorkflowAttachment(Source).Items);
  end
  else
    inherited Assign(Source);
end;

constructor TWorkflowAttachment.Create(Collection: TCollection);
begin
  inherited Create(Collection);
  FItems := TAttachmentItems.Create(Self);
  if Collection <> nil then
    FItems.WorkflowStudio := TWorkflowAttachments(Collection).WorkflowStudio;
end;

destructor TWorkflowAttachment.Destroy;
begin
  FItems.Free;
  inherited;
end;

procedure TWorkflowAttachment.SetItems(const Value: TAttachmentItems);
begin
  FItems.Assign(Value);
end;

function TWorkflowAttachments.GetItem(Index: integer): TWorkflowAttachment;
begin
  result := TWorkflowAttachment(inherited Items[Index]);
end;

{ TAttachmentItems }

function TAttachmentItems.Add: TAttachmentItem;
begin
  result := TAttachmentItem(inherited Add);
end;

function TAttachmentItems.AddFile(AFileName: string): TAttachmentItem;
var
  NewName: string;
begin
  result := nil;
  if FileExists(AFileName) then
  begin
    NewName := ExtractFileName(AFileName);
    result := FindByName(NewName);
    if result = nil then
      result := Add;
    begin
      try
        result.OriginalName := AFileName;        
        result.Name := NewName;
        result.LoadContentFromFile(AFileName);
      except
        result.free;
        raise;
      end;
    end;
  end;
end;

constructor TAttachmentItems.Create(AOwner: TPersistent);
begin
  inherited Create(AOwner, TAttachmentItem);
end;

function TAttachmentItems.FindByName(AName: string): TAttachmentItem;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if SameText(AName, Items[c].Name) then
    begin
      result := Items[c];
      break;
    end;
end;

function TAttachmentItems.GetItem(Index: integer): TAttachmentItem;
begin
  result := TAttachmentItem(inherited Items[Index]);
end;

procedure TAttachmentItems.SetWorkflowStudio(const Value: TCustomWorkflowStudio);
var
  i: integer;
begin
  FWorkflowStudio := Value;
  for i:=0 to Count-1 do
    Items[i].FWorkflowStudio := FWorkflowStudio;
end;

{ TAttachmentItem }

procedure TAttachmentItem.Assign(Source: TPersistent);
begin
  if Source is TAttachmentItem then
  begin
    FName := TAttachmentItem(Source).FName;
    //FExtension := TAttachmentItem(Source).FExtension;
    FOriginalName := TAttachmentItem(Source).FOriginalName;
    FKey := TAttachmentItem(Source).FKey;

    {Assing dirty content and content too so that it saves correctly}
    FDirtyContent := TAttachmentItem(Source).FDirtyContent;
    FContent := TAttachmentItem(Source).FContent;
  end else
    inherited Assign(Source);
end;

constructor TAttachmentItem.Create(Collection: TCollection);
var
  wkf: TCustomWorkflowStudio;
begin
  inherited Create(Collection);
  if (Collection <> nil) and (Collection is TAttachmentItems) then
    wkf := TAttachmentItems(Collection).WorkflowStudio
  else
    wkf := nil;
  Initialize(wkf);
end;

destructor TAttachmentItem.Destroy;
begin
  if FNotifyThread <> nil then
    TerminateThread(FNotifyThread.Handle, 0);
  FNotifyThread := nil;
  inherited;
end;

function TAttachmentItem.GetContent: string;
begin
  if not FDirtyContent and (FWorkflowStudio <> nil) then
  begin
   (FWorkflowStudio as TWorkflowStudio).WorkflowDB.AttachmentItemLoad(Self);
   (FWorkflowStudio as TWorkflowStudio).GetFtpFile(Self);
   DirtyContent := true;
  end;
  result := FContent;
end;

function TAttachmentItem.GetExtension: string;
begin
  result := ExtractFileExt(Name);
end;

procedure TAttachmentItem.Initialize(AWorkflowStudio: TCustomWorkflowStudio);
begin
  if AWorkflowStudio <> nil then
  begin
    FWorkflowStudio := AWorkflowStudio;
    FDirtyContent := False;
  end
  else if not Loading then
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);
end;

function TAttachmentItem.IsContentStored: Boolean;
begin
  {Content property will only be saved when the file content is in memory (not saved in database,
   or different from database). So FDirtyContent true means that the content of the attachment
   was changed in memory. If FDirtyContent is false, the file is in database so there is no need
   to be persisted. COntent published property should be only streamed for memory-assignment purposes}
  result := FDirtyContent;
end;

procedure TAttachmentItem.LoadContentFromFile(AFileName: string);
var
  FS: TFileStream;
  SS: TStringStream;
begin
  FS := TFileStream.Create(AFileName, fmOpenRead);
  SS := TStringStream.Create('');
  try
    SS.CopyFrom(FS, FS.Size);
    SS.Position := 0;
    SetContent(SS.DataString);
  finally
    SS.Free;
    FS.Free;
  end;
end;

function TAttachmentItem.Loading: boolean;
var
  attachment: TWorkflowAttachment;
begin
  result := False;
  if (Collection <> nil) and (Collection is TAttachmentItems) and (TAttachmentItems(Collection).GetOwner <> nil)
    and (TAttachmentItems(Collection).GetOwner is TWorkflowAttachment) then
  begin
    attachment := TAttachmentItems(Collection).GetOwner as TWorkflowAttachment;
    if (attachment.Collection <> nil) and (attachment.Collection is TWorkflowAttachments) and
      (TWorkflowAttachments(attachment.Collection).GetOwner <> nil) and
      (TWorkflowAttachments(attachment.Collection).GetOwner is TComponent)
    then
      result := csLoading in TComponent(TWorkflowAttachments(attachment.Collection).GetOwner).ComponentState;
  end;
end;

procedure TAttachmentItem.Open(AllowEdit: boolean; APath: string = '');
var
  Buffer: string;
  FullName: string;
begin
  {Get windows temporary path if APath is empty}
  if APath = '' then
  begin
    SetLength(Buffer, MAX_PATH);
    SetLength(Buffer, GetTempPath(MAX_PATH, PChar(Buffer)));
    APath := Buffer;
  end;

  ForceDirectories(APath);

  if (Length(APath) > 0) and (APath[Length(APath)] <> '\') then
    APath := APath + '\';

  FullName := APath + Name;

  SaveContentToFile(FullName);
  DoShellOpen(FullName, AllowEdit);
end;

procedure TAttachmentItem.DoShellOpen(AFileName: string; AllowEdit: boolean);
var
  EditEvent: TNotifyEvent;
begin
  if FNotifyThread = nil then
  begin
    if AllowEdit then
      EditEvent := ShellAppClosed
    else
      EditEvent := nil;

    FNotifyThread := TNotifyThread.Create(Self, AFileName, EditEvent);
  end
  else
    raise EWorkflowException.Create(_str(SErrorFileAlreadyOpen));
end;

procedure TAttachmentItem.ShellAppClosed(Sender: TObject);
var
  AFileAge: TDateTime;
begin
  if (FNotifyThread <> nil) and FileExists(FNotifyThread.FFileName) then
  begin
    {$IFDEF DELPHI2006_LVL}
    FileAge(FNotifyThread.FFileName, AFileAge);
    {$ELSE}
    AFileAge := FileDateToDateTime(FileAge(FNotifyThread.FFileName));
    {$ENDIF}
    if FNotifyThread.FFileAge <> AFileAge then
    begin
      if MessageDlg(Format(_str(SConfirmUpdateModifiedAttachment),
        [FNotifyThread.FFileName]), mtConfirmation, [mbYes, mbNo], 0) = mrYes then
      begin
        LoadContentFromFile(FNotifyThread.FFileName);
      end;
    end;
  end;
end;

constructor TAttachmentItem.Create(AWorkflowStudio: TCustomWorkflowStudio);
begin
  Initialize(AWorkflowStudio);
end;

procedure TAttachmentItem.CursorDefault;
begin
  Screen.Cursor := FSaveCursor;
end;

procedure TAttachmentItem.CursorHourGlass;
begin
  FSaveCursor := Screen.Cursor;
  Screen.Cursor := crHourGlass;
end;

{ TNotifyThread }

constructor TNotifyThread.Create(AItem: TAttachmentItem;
  const FileName: string; OnClosed: TNotifyEvent);
begin
  inherited Create(True);
  FItem := AItem;
  if FileExists(FileName) then
    {$IFDEF DELPHI2006_LVL}
    FileAge(FileName, FFileAge);
    {$ELSE}
    FFileAge := FileDateToDateTime(FileAge(FileName));
    {$ENDIF}
  FreeOnTerminate := True;
  OnTerminate := OnClosed;
  FFileName := FileName;
  {$WARNINGS OFF}
  Resume;
  {$WARNINGS ON}
end;

destructor TNotifyThread.Destroy;
begin
  if FItem <> nil then
    FItem.FNotifyThread := nil;
  inherited;
end;

procedure TNotifyThread.Execute;
var
  se: SHELLEXECUTEINFO;
  ok: boolean;
begin
  with se do
  begin
    {$WARNINGS OFF}
    cbSize := SizeOf(SHELLEXECUTEINFO);
    fMask := SEE_MASK_NOCLOSEPROCESS or SEE_MASK_FLAG_DDEWAIT;
    lpVerb := 'open';
    lpFile := PChar(FFileName);
    lpParameters := nil;
    lpDirectory := PChar(ExtractFilePath(ParamStr(0)));
    nShow := SW_SHOW;
    {$WARNINGS ON}
  end;

  if FItem <> nil then
    Synchronize(FItem.CursorHourGlass);
  try
    {$WARNINGS OFF}
    ok := ShellExecuteEx(@se);
    {$WARNINGS ON}
  finally
    if FItem <> nil then
      Synchronize(FItem.CursorDefault);
  end;

  if ok then
  begin
    WaitForSingleObject(se.hProcess, INFINITE);
    if se.hProcess <> 0 then
      CloseHandle(se.hProcess);
  end;
end;

procedure TAttachmentItem.SaveContentToFile(AFileName: string);
var
  FS: TFileStream;
  SS: TStringStream;
begin
  FS := TFileStream.Create(AFileName, fmCreate);
  SS := TStringStream.Create(GetContent);
  try
    SS.Position := 0;
    FS.CopyFrom(SS, SS.Size);
  finally
    SS.Free;
    FS.Free;
  end;
end;

procedure TAttachmentItem.SetContent(const Value: string);
begin
  FContent := Value;
  FDirtyContent := true;
end;

procedure TAttachmentItem.SetDirtyContent(const Value: boolean);
begin
  if(Value=False) then
    FContent :='';
  FDirtyContent:=Value;
end;
{ TTaskDefinitions }

function TTaskDefinitions.Add: TTaskDefinition;
begin
  result := TTaskDefinition(inherited Add);
end;

constructor TTaskDefinitions.Create(AOwner: TComponent);
begin
  inherited Create(AOwner, TTaskDefinition);
end;

function TTaskDefinitions.FindByName(AName: string): TTaskDefinition;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if SameText(AName, Items[c].Name) then
    begin
      result := Items[c];
      break;
    end;
end;

function TTaskDefinitions.GetItem(Index: integer): TTaskDefinition;
begin
  result := TTaskDefinition(inherited Items[Index]);
end;

function TTaskDefinitions.GetOwner: TPersistent;
begin
  result := inherited GetOwner;
end;

{ TTaskDefinition }

procedure TTaskDefinition.Assign(Source: TPersistent);
begin
  if Source is TTaskDefinition then
  begin
    FKey := TTaskDefinition(Source).FKey;
    FName := TTaskDefinition(Source).FName;
    FSubject := TTaskDefinition(Source).FSubject;
    FDescription := TTaskDefinition(Source).FDescription;
   // FAssignmentRule := TTaskDefinition(Source).FAssignmentRule;
    FStatusList.Assign(TTaskDefinition(Source).FStatusList);
    FHiddenStatusList.Assign(TTaskDefinition(Source).FHiddenStatusList);
    FTaskInstanceKeys.Assign(TTaskDefinition(Source).FTaskInstanceKeys);
    FPreviousTaskInsKeys.Assign(TTaskDefinition(Source).FPreviousTaskInsKeys);
    FShowAttachments := TTaskDefinition(Source).FShowAttachments;
    FAttachmentPermissions := TTaskDefinition(Source).FAttachmentPermissions;
    FMailNotification := TTaskDefinition(Source).FMailNotification;
    FFields.Assign(TTaskDefinition(Source).FFields);
    FExpirationDateTime := TTaskDefinition(Source).FExpirationDateTime;
    FExpirationStatus := TTaskDefinition(Source).FExpirationStatus;
    FUsers.Assign(TTaskDefinition(Source).FUsers);
  end
  else
    inherited Assign(Source);
end;

constructor TTaskDefinition.Create(Collection: TCollection);
begin
  inherited Create(Collection);
  FShowAttachments := true;
  FAttachmentPermissions := [];
  FStatusList := TStringList.Create;
  FHiddenStatusList := TStringList.Create;
  FTaskInstanceKeys := TStringList.Create;
  FPreviousTaskInsKeys := TStringList.Create;
  FFields := TTaskFields.Create(Self, TTaskField);
  FUsers := TTaskAssignedUsers.Create(Self,TTaskAssignedUser);
end;

destructor TTaskDefinition.Destroy;
begin
  FFields.Free;
  FTaskInstanceKeys.Free;
  FPreviousTaskInsKeys.Free;
  FStatusList.Free;
  FHiddenStatusList.Free;
  FUsers.Free;
  inherited;
end;

procedure TTaskDefinition.FillStatusList(AList: TStrings; AIncludeHidden: boolean);
var
  c: integer;
begin
  AList.Clear;
  for c := 0 to StatusCount-1 do
  begin
    if AIncludeHidden or not StatusHidden[c] then
      AList.Add(StatusName[c]);
  end;
end;

function TTaskDefinition.GetInitialStatus: string;
var
  c: integer;
begin
  result := '';
  c := 0;
  while c < StatusCount do
  begin
    if not StatusCompletion[c] then
    begin
      result := StatusName[c];
      break;
    end
    else
      inc(c);
  end;
end;

function TTaskDefinition.GetStatusCompletion(i: integer): boolean;
begin
  result := (Length(StatusList[i]) > 0) and (StatusList[i][1] = '*');
end;

function TTaskDefinition.GetStatusCount: integer;
begin
  result := StatusList.Count;
end;

function TTaskDefinition.GetStatusHidden(i: integer): boolean;
var
  status: string;
  c: integer;
begin
  status := StatusName[i];
  for c := 0 to HiddenStatusList.Count-1 do
    if SameText(status, HiddenStatusList[c]) then
    begin
      result := True;
      exit;
    end;
  result := False;
end;

function TTaskDefinition.GetStatusName(i: integer): string;
begin
  result := StatusList[i];
  if (result > '') and (result[1] = '*') then
    Delete(result, 1, 1);
end;

function TTaskDefinition.IsCompletionStatus(AStatus: string): boolean;
var
  c: integer;
begin
  for c := 0 to StatusCount-1 do
    if SameText(AStatus, StatusName[c]) and StatusCompletion[c] then
    begin
      result := True;
      exit;
    end;
  result := false;
end;

procedure TTaskDefinition.SetStatusCompletion(i: integer; const Value: boolean);
var
  status: string;
begin
  if Value <> StatusCompletion[i] then
  begin
    status := StatusList[i];
    if Value then
      StatusList[i] := '*' + status
    else
      StatusList[i] := Copy(status, 2, Length(status));
  end;
end;

procedure TTaskDefinition.SetStatusHidden(i: integer; const Value: boolean);
var
  status: string;
  c: integer;
begin
  if Value <> StatusHidden[i] then
  begin
    status := StatusName[i];
    if Value then
      HiddenStatusList.Add(status)
    else
    begin
      for c := HiddenStatusList.Count-1 downto 0 do
        if SameText(status, HiddenStatusList[c]) then
          HiddenStatusList.Delete(c);
    end;
  end;
end;

procedure TTaskDefinition.SetStatusList(const Value: TStrings);
begin
  FStatusList.Assign(Value);
end;

procedure TTaskDefinition.SetStatusName(i: integer; const Value: string);
var
  completion, hidden: boolean;
begin
  if Value <> StatusName[i] then
  begin
    completion := StatusCompletion[i];
    hidden := StatusHidden[i];
    StatusList[i] := Value;
    StatusCompletion[i] := completion;
    StatusHidden[i] := hidden;
  end;
end;

function TTaskDefinition.StatusAdd(AStatus: string; ACompletion, AHidden: boolean): integer;
begin
  result := StatusList.Add(AStatus);
  StatusCompletion[result] := ACompletion;
  StatusHidden[result] := AHidden;
end;

procedure TTaskDefinition.StatusDelete(AStatus: string);
var
  c: integer;
begin
  for c := StatusCount-1 downto 0 do
    if SameText(AStatus, StatusName[c]) then
      StatusList.Delete(c);
  for c := HiddenStatusList.Count-1 downto 0 do
    if SameText(AStatus, HiddenStatusList[c]) then
      HiddenStatusList.Delete(c);
end;

procedure TTaskDefinition.SetFields(const Value: TTaskFields);
begin
  FFields.Assign(Value);
end;

procedure TTaskDefinition.SetHiddenStatusList(const Value: TStrings);
begin
  FHiddenStatusList.Assign(Value);
end;
procedure TTaskDefinition.SetUsers(const Value: TTaskAssignedUsers);
begin
  FUsers.Assign(Value);
end;

{ TTaskInstance }

function TTaskInstance.CanUpdate(AUserId: string; AWorkflowStudio: TCustomWorkflowStudio): boolean;
begin
  result :=  AWorkflowStudio.UserManager.IsSameUser(AUserId, Self.UserId) or AWorkflowStudio.UserManager.BelongsToAdminGroup(AUserId);
  if result=false then
  begin
    case FAssignedUserType of
      autGroup:
        result := result or AWorkflowStudio.UserManager.BelongsToGroup(AUserId, Self.UserId);
      autJob:
        result := result or AWorkflowStudio.UserManager.BelongsToJob(AUserId, Self.UserId);
      autDepartment:
        result := result or AWorkflowStudio.UserManager.BelongsToDepartment(AUserId, Self.UserId);
    end;
  end;
end;

constructor TTaskInstance.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FContainer := TDataModule.Create(nil);
  FDiagram := TLiveDiagram.Create(FContainer);
  FTaskDef := TTaskDefinition.Create(nil);
  FFlowMnDtlStepDefin :=0;
  FFlowMnDtlProjectID :='';
  FNeedPrjRight :=False;
end;

destructor TTaskInstance.Destroy;
begin
  FContainer.Free;
  FContainer := nil;
  FDiagram := nil;
  FTaskDef.Free;
  inherited;
end;

function TTaskInstance.GetCompleted: boolean;
begin
  result := IsCompletionStatus(Status);
end;

function TTaskInstance.IsCompletionStatus(AStatus: string): boolean;
begin
  result := TaskDef.IsCompletionStatus(AStatus);
end;

procedure TTaskInstance.SetTaskDef(const Value: TTaskDefinition);
begin
  FTaskDef.Assign(Value);
end;

{ TTaskInstanceList }

function TTaskInstanceList.Add: TTaskInstanceItem;
begin
  result := TTaskInstanceItem(inherited Add);
end;

function TTaskInstanceList.GetItem(index: integer): TTaskInstanceItem;
begin
  result := TTaskInstanceItem(inherited Items[Index]);
end;
function TTaskInstanceList.FindByKey(ATaskInsKey:string):TTaskInstanceItem;
var
  ATaskInsItem: TTaskInstanceItem;
  I: Integer;
begin
    result :=nil;
    for I := 0 to Count - 1 do
    begin
     ATaskInsItem :=TTaskInstanceItem(inherited Items[i]);
      if CompareText(ATaskInsItem.Task.Key, ATaskInsKey)=0 then
        begin
          result :=ATaskInsItem;
          exit;
        end;
    end;
end;

{ TTaskInstanceItem }

constructor TTaskInstanceItem.Create(Collection: TCollection);
begin
  inherited;
  FTask := TTaskInstance.Create(nil);
end;

destructor TTaskInstanceItem.Destroy;
begin
  FTask.Free;
  inherited;
end;

{ TTaskField }

procedure TTaskField.Assign(Source: TPersistent);
begin
  if Source is TTaskField then
  begin
    FCaption := TTaskField(Source).FCaption;
    FReadOnly := TTaskField(Source).FReadOnly;
    FRequired := TTaskField(Source).FRequired;
    FWorkflowVarName := TTaskField(Source).FWorkflowVarName;
  end
  else
    inherited Assign(Source);
end;

{ TTaskFields }

function TTaskFields.Add: TTaskField;
begin
  result := TTaskField(inherited Add);
end;

function TTaskFields.GetItem(Index: integer): TTaskField;
begin
  result := TTaskField(inherited Items[Index]);
end;

function TTaskFields.FindByVarName(AVarName: string):TTaskField;
var
  I: integer;
  AItem: TTaskField;
begin
  result :=nil;
  for I := 0 to Count - 1 do
    begin
      AItem :=TTaskField(inherited Items[i]);
      if CompareText(AItem.WorkflowVarName,AVarName)=0 then
        begin
          result :=AItem;
          exit;
        end;
    end;
end;

procedure TTaskAssignedUser.Assign(Source: TPersistent);
begin
  if Source is TTaskAssignedUser then
  begin
    AssignedUserName := TTaskAssignedUser(Source).AssignedUserName;
    StepDefin := TTaskAssignedUser(Source).StepDefin;
    AssignedUserID := TTaskAssignedUser(Source).AssignedUserID;
    AssignedUserType := TTaskAssignedUser(Source).AssignedUserType;
    CanPrint := TTaskAssignedUser(Source).CanPrint;
    AssignmentMode :=TTaskAssignedUser(Source).AssignmentMode;
    NeedPrjRight := TTaskAssignedUser(Source).NeedPrjRight;
  end else
    inherited Assign(Source);
end;

{ TTaskAssignedUsers }

function TTaskAssignedUsers.Add: TTaskAssignedUser;
begin
  result := TTaskAssignedUser(inherited Add);
end;

function TTaskAssignedUsers.GetItem(Index: integer): TTaskAssignedUser;
begin
  result := TTaskAssignedUser(inherited Items[Index]);
end;


{ TWorkflowEngine }

constructor TWorkflowEngine.Create(AWorkflowStudio: TCustomWorkflowStudio);
begin
  if AWorkflowStudio <> nil then
    FWorkflowStudio := AWorkflowStudio
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);
end;

function TWorkflowEngine.RunPendingWorkflowInstances: integer;
var
  slKeys: TStringList;
  i: integer;
begin
  slKeys := TStringList.Create;
  try
    FWorkflowStudio.WorkflowManager.ListPendingWorkflowInstances(slKeys);
    result := slKeys.Count;
    for i := 0 to slKeys.Count-1 do
      FWorkflowStudio.WorkflowManager.SignalWorkflowInstance(slKeys[i]);
  finally
    slKeys.Free;
  end;
end;

procedure TWorkflowEngine.RunWorkflow(WorkIns: TWorkflowInstance);
begin
  WorkIns.Diagram.OnTerminate := WorkflowTerminated;
  WorkIns.Diagram.OnSaveState := WorkflowSaveState;

  {The line below is useless because the workflow is being run inside a thread.
   So, we cannot set the context here as it can be changed later.
   But we can set the context inside each procedure that uses the scriptengine, because
   the blocke execution is synchronized, so we can rely on global variables inside
   a procedure being executed by the worfklow thread. ALWAYS set the context before
   using the script engine}
  //WorkflowStudio.ScriptEngine.SetRuntimeContext(WorkIns);
  Case WorkIns.Status of
    wsRunning:
      WorkIns.Diagram.DoAction(daContinue);
    wsNotStarted:
      begin
        WorkIns.Status := wsRunning;
        WorkIns.Diagram.DoAction(daRun);
      end;
  end;
end;

procedure TWorkflowEngine.WorkflowSaveState(Sender: TObject);
var
  WI: TWorkflowInstance;
begin
  if Sender is TWorkflowDiagram then
  begin
    WI := TWorkflowDiagram(Sender).WorkflowInstance;
    FWorkflowStudio.WorkflowManager.SaveWorkflowInstance(WI);
  end;
end;

procedure TWorkflowEngine.WorkflowTerminated(Sender: TLiveDiagram; ExitCode: integer);
var
  WI: TWorkflowInstance;
  ErrMsg: string;
  ShowError: boolean;
begin
  if Sender is TWorkflowDiagram then
  begin
    WI := TWorkflowDiagram(Sender).WorkflowInstance;

    {if the workflow is indeeed finished, then set started to false and save it to database}
    if ExitCode <> xWaitState_Termination then
    begin
      {Check if it was finished with an error}
      if ExitCode = xNormal_Termination then
      begin
        WI.Status := wsFinished;
        WI.FlowMnFinishTime := Now;
        {Save status in workflow}
        FWorkflowStudio.WorkflowManager.SaveWorkflowInstance(WI);
        FWorkflowStudio.RunFinished(WI);
      end
      else
      begin
      //  WI.Status := wsFinishedWithError;    {zws20110902}
      {if workflow ended with an error...}
    //  if WI.Status = wsFinishedWithError then
    //  begin
        {Save a log or show an error message. For now, show an error}
        ErrMsg := Format(_str(SWorkInsExecutionError), [WI.Diagram.RunErrorMsg]);

        if WI.Diagram.ErrorNode <> nil then
        begin
          ErrMsg := Format(_str(SWorkInsExecutionError2),
            [ErrMsg, WI.Diagram.ErrorNode.ClassName, WI.Diagram.ErrorNode.Name,
             WI.Diagram.ErrorNode.Strings.Text]);
        end;

        ShowError := False;//true;  //zws后台显示错误，会把服务整死了
        FWorkflowStudio.WorkflowInstanceError(WI, ErrMsg, ShowError);
      //  if ShowError then
       //   ShowMessage(ErrMsg);
    //  end;
        {zws 2011-08-31,获取错误信息保存到流程内容中}
      if WI.Status = wsFinishedWithError then
          WI.FlowMnContent :=WI.FlowMnContent+'['+ErrMsg+']';
      end;

    end;

    // check if instance was executed by another workflow so resume it
    if (WI.ParentKey > '') and (WI.Status in [wsFinished, wsFinishedWithError]) then
      FWorkflowStudio.WorkflowManager.SignalWorkflowInstance(WI.ParentKey);

   // WI.Free;       //20110531
    WI :=nil;
  end;
end;

{ TWorkflowScriptEngine }

function TWorkflowScriptEngine.CalculateExpression(Expr: string): Variant;
begin
end;

constructor TWorkflowScriptEngine.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FExprDelim := '[,]';
end;

function TWorkflowScriptEngine.ExpressionToStr(Value: Variant): string;
begin
  if VarIsEmpty(Value) or VarIsNull(Value) or VarIsArray(Value) then
    result := ''
  else
    result := VarToStr(Value);
end;

function TWorkflowScriptEngine.ExtractExpression(AText, OpenDelim, CloseDelim: string;
  var i, j: Integer): string;
var
  c: integer;
  f1, f2: boolean;
begin
  result := '';
  j := i;
  f1 := true;
  f2 := true;
  c := 0;
  if (AText = '') or (j > Length(AText)) then
    Exit;

  dec(j);
  repeat
    inc(j);
    if f1 and f2 then
      if Copy(AText, j, Length(OpenDelim)) = OpenDelim then
      begin
        if c = 0 then
          i := j;
        inc(c);
      end
      else
      if Copy(AText, j, Length(CloseDelim)) = CloseDelim then
        dec(c);
    if f1 then
      if AText[j] = '"' then f2 := not f2;
    if f2 then
      if AText[j] = '''' then f1 := not f1;
  until (c = 0) or (j >= Length(AText));

  result := Copy(AText, i + Length(OpenDelim), j - i - Length(OpenDelim));
  if i <> j then
    Inc(j, Length(CloseDelim) - 1);
end;

procedure TWorkflowScriptEngine.SetDesignContext(ADiagram: TCustomWorkflowDiagram);
begin
  FDiagram := ADiagram;
  FRunContext := scDesignDiagram;
  RunContextChanged;
end;

procedure TWorkflowScriptEngine.SetRuntimeContext(AWorkIns: TWorkflowInstance; ATaskIns: TTaskInstance);
begin
  FWorkIns := AWorkIns;
  FTaskIns := ATaskIns;
  FRunContext := scRuntimeInstance;
  RunContextChanged;
end;

function TWorkflowScriptEngine.TranslateText(AText: string): string;
var
  i: integer;
  j: integer;
  OpenDelim, CloseDelim: string;
  s1: string;
  s2: string;
begin
  i := 1;
  OpenDelim := FExprDelim;
  CloseDelim := Copy(OpenDelim, Pos(',', OpenDelim) + 1, MaxInt);
  OpenDelim := Copy(OpenDelim, 1, Pos(',', OpenDelim) - 1);

  if Pos(OpenDelim, AText) <> 0 then
  begin                        
    repeat
      while (i < Length(AText)) and (Copy(AText, i, Length(OpenDelim)) <> OpenDelim) do Inc(i);

      s1 := ExtractExpression(AText, OpenDelim, CloseDelim, i, j);
      if i <> j then
      begin
        Delete(AText, i, j - i + 1);
        s2 := ExpressionToStr(CalculateExpression(s1));
        Insert(s2, AText, i);
        Inc(i, Length(s2));
        j := 0;
      end;
    until i = j;

  end;
  result := AText;
end;

{ TWorkflowUsers }

function TWorkflowUsers.Add: TWorkflowUser;
begin
  result := TWorkflowUser(inherited Add);
end;

function TWorkflowUsers.Add(AUserID: string; AUserName: string = ''; AEmail: string = '';AUserCode: string =''): TWorkflowUser;
begin
  result := add;
  with result do
  begin
    UserId := AUserId;
    UserName := AUserName;
    EMail := AEmail;
    UserCode := AUserCode;
  end;
end;

function TWorkflowUsers.FindById(AName: string): TWorkflowUser;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AName, Items[c].UserId) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowUsers.FindByName(AName: string): TWorkflowUser;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AName, Items[c].UserName) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowUsers.GetItem(Index: integer): TWorkflowUser;
begin
  result := TWorkflowUSer(inherited Items[Index]);
end;

{ TWorkflowGroup }

constructor TWorkflowGroup.Create(Collection: TCollection);
begin
  inherited Create(Collection);
  FUserIds := TStringList.Create;
  FIsAdmin := False;
end;

destructor TWorkflowGroup.Destroy;
begin
  FUserIds.Free;
  inherited;
end;

function TWorkflowGroup.GetGroupId: string;
begin
  if FGroupId > '' then
    result := FGroupId
  else
    result := FGroupName;
end;

function TWorkflowGroup.GetGroupName: string;
begin
  if FGroupName > '' then
    result := FGroupName
  else
    result := FGroupId;
end;

function TWorkflowGroup.GetUserManager: TWorkflowUserManager;
begin
  if (Collection is TWorkflowGroups) and (TWorkflowGroups(Collection).GetOwner is TWorkflowUserManager) then
    result := TWorkflowUserManager(TWorkflowGroups(Collection).GetOwner)
  else
    result := nil;
end;

procedure TWorkflowGroup.SetUserIds(const Value: TStrings);
begin
  FUserIds.Assign(Value);
end;

{ TWorkflowGroups }

function TWorkflowGroups.Add: TWorkflowGroup;
begin
  result := TWorkflowGroup(inherited Add);
end;

function TWorkflowGroups.Add(AGroupName: string): TWorkflowGroup;
begin
  result := Add;
  With result do
  begin
    GroupName := AGroupName;
    GroupID := AGroupName; 
  end;
end;

function TWorkflowGroups.Add(AGroupID, AGroupName: string): TWorkflowGroup;
begin
  result := Add;
  with result do
  begin
    GroupID := AGroupID;
    GroupName := AGroupName;
  end;
end;

function TWorkflowGroups.FindByID(AId: string): TWorkflowGroup;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AID, Items[c].GroupID) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowGroups.FindByName(AName: string): TWorkflowGroup;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AName, Items[c].GroupName) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowGroups.GetItem(Index: integer): TWorkflowGroup;
begin
  result := TWorkflowGroup(inherited Items[Index]);
end;
{ TWorkflowDepartment }

constructor TWorkflowDepartment.Create(Collection: TCollection);
begin
  inherited Create(Collection);
  FUserIds := TStringList.Create;
end;

destructor TWorkflowDepartment.Destroy;
begin
  FUserIds.Free;
  inherited;
end;

function TWorkflowDepartment.GetDepartmentId: string;
begin
  if FDepartmentId > '' then
    result := FDepartmentId
  else
    result := FDepartmentName;
end;

function TWorkflowDepartment.GetDepartmentName: string;
begin
  if FDepartmentName > '' then
    result := FDepartmentName
  else
    result := FDepartmentId;
end;

function TWorkflowDepartment.GetDepartmentManagerId: string;
begin
 result := FDepartmentManagerId;
 { if FDepartmentManagerId > '' then
    result := FDepartmentManagerId
  else
    result := FDepartmentManagerName;}
end;

{function TWorkflowDepartment.GetDepartmentManagerName: string;
begin
  if FDepartmentManagerName > '' then
    result := FDepartmentManagerName
  else
    result := FDepartmentManagerId;
end; }

function TWorkflowDepartment.GetUserManager: TWorkflowUserManager;
begin
  if (Collection is TWorkflowDepartments) and (TWorkflowDepartments(Collection).GetOwner is TWorkflowUserManager) then
    result := TWorkflowUserManager(TWorkflowDepartments(Collection).GetOwner)
  else
    result := nil;
end;

procedure TWorkflowDepartment.SetUserIds(const Value: TStrings);
begin
  FUserIds.Assign(Value);
end;

{ TWorkflowDepartments }

function TWorkflowDepartments.Add: TWorkflowDepartment;
begin
  result := TWorkflowDepartment(inherited Add);
end;

function TWorkflowDepartments.Add(ADepartmentName: string): TWorkflowDepartment;
begin
  result := Add;
  With result do
  begin
    DepartmentName := ADepartmentName;
    DepartmentID := ADepartmentName; 
  end;
end;

function TWorkflowDepartments.Add(ADepartmentID, ADepartmentName: string): TWorkflowDepartment;
begin
  result := Add;
  with result do
  begin
    DepartmentID := ADepartmentID;
    DepartmentName := ADepartmentName;
  end;
end;

function TWorkflowDepartments.FindByID(AId: string): TWorkflowDepartment;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AID, Items[c].DepartmentID) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowDepartments.FindByName(AName: string): TWorkflowDepartment;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AName, Items[c].DepartmentName) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowDepartments.GetItem(Index: integer): TWorkflowDepartment;
begin
  result := TWorkflowDepartment(inherited Items[Index]);
end;

{ TWorkflowJob }

constructor TWorkflowJob.Create(Collection: TCollection);
begin
  inherited Create(Collection);
  FUserIds := TStringList.Create;
end;

destructor TWorkflowJob.Destroy;
begin
  FUserIds.Free;
  inherited;
end;

function TWorkflowJob.GetJobId: string;
begin
  if FJobId > '' then
    result := FJobId
  else
    result := FJobName;
end;

function TWorkflowJob.GetJobName: string;
begin
  if FJobName > '' then
    result := FJobName
  else
    result := FJobId;
end;

function TWorkflowJob.GetUserManager: TWorkflowUserManager;
begin
  if (Collection is TWorkflowJobs) and (TWorkflowJobs(Collection).GetOwner is TWorkflowUserManager) then
    result := TWorkflowUserManager(TWorkflowJobs(Collection).GetOwner)
  else
    result := nil;
end;

procedure TWorkflowJob.SetUserIds(const Value: TStrings);
begin
  FUserIds.Assign(Value);
end;

{ TWorkflowJobs }

function TWorkflowJobs.Add: TWorkflowJob;
begin
  result := TWorkflowJob(inherited Add);
end;

function TWorkflowJobs.Add(AJobName: string): TWorkflowJob;
begin
  result := Add;
  With result do
  begin
    JobName := AJobName;
    JobID := AJobName; 
  end;
end;

function TWorkflowJobs.Add(AJobID, AJobName: string): TWorkflowJob;
begin
  result := Add;
  with result do
  begin
    JobID := AJobID;
    JobName := AJobName;
  end;
end;

function TWorkflowJobs.FindByID(AId: string): TWorkflowJob;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AID, Items[c].JobID) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowJobs.FindByName(AName: string): TWorkflowJob;
var
  c: integer;
begin
  result := nil;
  for c := 0 to Count - 1 do
    if CompareText(AName, Items[c].JobName) = 0 then
    begin
      result := Items[c];
      break
    end;
end;

function TWorkflowJobs.GetItem(Index: integer): TWorkflowJob;
begin
  result := TWorkflowJob(inherited Items[Index]);
end;

{ TWorkflowUser }

function TWorkflowUser.BelongsToJob(AJobId: string): boolean;
var
  AJobIds: TStrings;
begin
  AJobIds := TStringList.Create;
  try
    FillJobIds(AJobIds);
    result := (AJobIds.IndexOf(AJobId) >= 0);
  finally
    AJobIds.Free;
  end;
end;

procedure TWorkflowUser.FillJobIds(AJobIds: TStrings);
var
  c: integer;
begin
  AJobIds.Clear;
  for c := 0 to UserManager.Jobs.Count - 1 do
    if UserManager.Jobs[c].UserIds.IndexOf(Self.UserId) >= 0 then
      AJobIds.Add(UserManager.Jobs[c].JobId);
end;

function TWorkflowUser.BelongsToDepartment(ADepartmentId: string): boolean;
var
  ADepartmentIds: TStrings;
begin
  ADepartmentIds := TStringList.Create;
  try
    FillDepartmentIds(ADepartmentIds);
    result := (ADepartmentIds.IndexOf(ADepartmentId) >= 0);
  finally
    ADepartmentIds.Free;
  end;
end;

procedure TWorkflowUser.FillDepartmentIds(ADepartmentIds: TStrings);
var
  c: integer;
begin
  ADepartmentIds.Clear;
  for c := 0 to UserManager.Departments.Count - 1 do
    if UserManager.Departments[c].UserIds.IndexOf(Self.UserId) >= 0 then
      ADepartmentIds.Add(UserManager.Departments[c].DepartmentId);
end;



function TWorkflowUser.BelongsToAdminGroup: boolean;
var
  i: integer;
begin
  for i := 0 to UserManager.Groups.Count - 1 do
    if (UserManager.Groups[i].UserIds.IndexOf(Self.UserId) >= 0) and UserManager.Groups[i].IsAdmin then
    begin
      result := true;
      exit;
    end;
  result := false;
end;

function TWorkflowUser.BelongsToGroup(AGroupId: string): boolean;
var
  groupIds: TStrings;
begin
  groupIds := TStringList.Create;
  try
    FillGroupIds(groupIds);
    result := (groupIds.IndexOf(AGroupId) >= 0);
  finally
    groupIds.Free;
  end;
end;

procedure TWorkflowUser.FillGroupIds(AGroupIds: TStrings);
var
  c: integer;
begin
  AGroupIds.Clear;
  for c := 0 to UserManager.Groups.Count - 1 do
    if UserManager.Groups[c].UserIds.IndexOf(Self.UserId) >= 0 then
      AGroupIds.Add(UserManager.Groups[c].GroupId);
end;

function TWorkflowUser.GetUserManager: TWorkflowUserManager;
begin
  if (Collection is TWorkflowUsers) and (TWorkflowUsers(Collection).GetOwner is TWorkflowUserManager) then
    result := TWorkflowUserManager(TWorkflowUsers(Collection).GetOwner)
  else
    result := nil;
end;

function TWorkflowUser.GetUserNameOrId: string;
begin
  if FUserName > '' then
    result := FUserName
  else
    result := FUserId;
end;

{ TWorkflowUserManager }
function TWorkflowUserManager.BelongsToProject(AUserId,AProjectId: string): boolean;
 begin
   Result :=(FWorkflowStudio as TWorkflowStudio).WorkflowDB.BelongsToProject(AUserId,AProjectId);
 end;

function TWorkflowUserManager.BelongsToAdminGroup(AUserId: string): boolean;
var
  user: TWorkflowUser;
begin
  result := false;
  user := Users.FindById(AUserId);
  if user <> nil then
    result := user.BelongsToAdminGroup;
end;

function TWorkflowUserManager.BelongsToGroup(AUserId, AGroupId: string): boolean;
var
  user: TWorkflowUser;
begin
  result := false;
  user := Users.FindById(AUserId);
  if user <> nil then
    result := user.BelongsToGroup(AGroupId);
end;

function TWorkflowUserManager.BelongsToJob(AUserId,
  AJobId: string): boolean;
var
  AUser: TWorkflowUser;
begin
  result := false;
  AUser := Users.FindById(AUserId);
  if AUser <> nil then
    result := AUser.BelongsToJob(AJobId);
end;

function TWorkflowUserManager.BelongsToDepartment(AUserId,
  ADepartmentId: string): boolean;
var
  AUser: TWorkflowUser;
begin
  result := false;
  AUser := Users.FindById(AUserId);
  if AUser <> nil then
    result := AUser.BelongsToDepartment(ADepartmentId);
end;

constructor TWorkflowUserManager.Create(AOwner: TComponent; AWorkflowStudio: TCustomWorkflowStudio);
begin
  inherited Create(AOwner);
  if AWorkflowStudio <> nil then
    FWorkflowStudio := AWorkflowStudio
  else
    raise Exception.CreateFmt('WorkflowStudio parameter not specified in %s.Create.', [ClassName]);
  FUsers := TWorkflowUsers.Create(Self, TWorkflowUser);
  FGroups := TWorkflowGroups.Create(Self, TWorkflowGroup);
  FJobs:= TWorkflowJobs.Create(Self,TWorkflowJob);
  FDepartments:= TWorkflowDepartments.Create(Self,TWorkflowDepartment);
end;

destructor TWorkflowUserManager.Destroy;
begin
  FGroups.Free;
  FUsers.Free;
  FJobs.Free;
  FDepartments.Free;
  inherited;
end;

procedure TWorkflowUserManager.FillAssignmentList(AList: TStrings;
  AddObjects: boolean = false);
var
  SL: TStringList;
begin
  SL := TStringList.Create;
  try
    FillGroupList(SL, AddObjects);
    AList.AddStrings(SL);
    FillUserList(SL, AddObjects);
    AList.AddStrings(SL);
    FillJobList(SL,AddObjects);  //填职位
    AList.AddStrings(SL);
    FillDepartmentList(SL, AddObjects); //填部门
    AList.AddStrings(SL);
  finally
    SL.Free;
  end;
end;

procedure TWorkflowUserManager.FillGroupList(AList: TStrings;
  AddObjects: boolean = false);
var
  c: integer;
  internalList: TStringList;
begin
  internalList := TStringList.Create;
  try
    internalList.Clear;
    for c := 0 to FGroups.Count - 1 do
    begin
      if AddObjects then
        internalList.AddObject(FGroups[c].GroupName, FGroups[c])
      else
        internalList.Add(FGroups[c].GroupName);
    end;
    internalList.Sort;
    AList.Assign(internalList);
  finally
    internalList.Free;
  end;
end;
procedure TWorkflowUserManager.FillJobList(AList: TStrings;
  AddObjects: boolean = false);
var
  c: integer;
  internalList: TStringList;
begin
  internalList := TStringList.Create;
  try
    internalList.Clear;
    for c := 0 to FJobs.Count - 1 do
    begin
      if AddObjects then
        internalList.AddObject(FJobs[c].JobName, FJobs[c])
      else
        internalList.Add(FJobs[c].JobName);
    end;
    internalList.Sort;
    AList.Assign(internalList);
  finally
    internalList.Free;
  end;
end;

procedure TWorkflowUserManager.FillDepartmentList(AList: TStrings;
  AddObjects: boolean = false);
var
  c: integer;
  internalList: TStringList;
begin
  internalList := TStringList.Create;
  try
    internalList.Clear;
    for c := 0 to FDepartments.Count - 1 do
    begin
      if AddObjects then
        internalList.AddObject(FDepartments[c].DepartmentName, FDepartments[c])
      else
        internalList.Add(FDepartments[c].DepartmentName);
    end;
    internalList.Sort;
    AList.Assign(internalList);
  finally
    internalList.Free;
  end;
end;

procedure TWorkflowUserManager.FillUserList(AList: TStrings;
  AddObjects: boolean = false);
var
  c: integer;
  internalList: TStringList;
begin
  internalList := TStringList.Create;
  try
    internalList.Clear;
    for c := 0 to FUsers.Count - 1 do
    begin
      if AddObjects then
        internalList.AddObject(FUsers[c].UserName, FUsers[c])
      else
        internalList.Add(FUsers[c].UserName);
    end;
    internalList.Sort;
    AList.Assign(internalList);
  finally
    internalList.Free;
  end;
end;

procedure TWorkflowUserManager.GetAssignedUserList(AAssignedUsers: TTaskAssignedUsers; AUserList: TStringList; AProjectID: String);
var
  AGroup: TWorkflowGroup;
  AUser: TWorkflowUser;
  ADepartment :TWorkflowDepartment;
  AJob : TWorkflowJob;
  AAssignedUser:TTaskAssignedUser;
  c: integer;
  u: integer;
  DepartmenManagertid : string;
begin
  AUserList.Clear;
  for u:= 0 to AAssignedUsers.Count-1 do
  begin
    AAssignedUser:= AAssignedUsers.Items[u];
    Case AAssignedUser.AssignedUserType of
    autUser:
    begin
          AUser := Users.FindByID(AAssignedUser.AssignedUserID);
          if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
          begin
            AUser.CanPrint:=AAssignedUser.CanPrint;
            AUser.StepDefin :=AAssignedUser.StepDefin;
            Auser.NeedPrjRight :=False;//AAssignedUser.NeedPrjRight;
            AUserList.AddObject(AUser.UserId,AUser);
          end;
    end;
    autGroup:
    begin
     AGroup:=Groups.FindByID(AAssignedUser.AssignedUserID);
     if AGroup <> nil then
     begin
        if AAssignedUser.AssignmentMode=gamSingleTask then    //单任务形式
        begin
            AGroup.CanPrint:=AAssignedUser.CanPrint;
            AGroup.StepDefin :=AAssignedUser.StepDefin;
            AGroup.NeedPrjRight := AAssignedUser.NeedPrjRight;
            AUserList.AddObject(AGroup.GroupId,AGroup);
        end else
        begin
        for c := 0 to AGroup.UserIds.Count - 1 do      //需要增加项目权限判断
        begin
          if AAssignedUser.NeedPrjRight then
          begin
            if BelongsToProject(AGroup.UserIds[c],AProjectID) then
            begin
              AUser := Users.FindByID(AGroup.UserIds[c]);
              if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
              begin
                AUser.CanPrint:=AAssignedUser.CanPrint;
                AUser.StepDefin :=AAssignedUser.StepDefin;
                AUser.NeedPrjRight :=AAssignedUser.NeedPrjRight;
                AUserList.AddObject(AUser.UserId,AUser);
              end;
            end;
          end
          else
          begin
            AUser := Users.FindByID(AGroup.UserIds[c]);
            if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
            begin
              AUser.CanPrint:=AAssignedUser.CanPrint;
              AUser.StepDefin :=AAssignedUser.StepDefin;
              AUser.NeedPrjRight :=AAssignedUser.NeedPrjRight;
              AUserList.AddObject(AUser.UserId,AUser);
            end;
          end;
        end;
      end;
     end;
    end;
    autJob:
    begin
     AJob:=Jobs.FindByID(AAssignedUser.AssignedUserID);
     if AJob <> nil then
     begin
        if AAssignedUser.AssignmentMode=gamSingleTask then   //单任务形式
        begin
            AJob.CanPrint:=AAssignedUser.CanPrint;
            AJob.StepDefin :=AAssignedUser.StepDefin;
            AJob.NeedPrjRight :=AAssignedUser.NeedPrjRight;
            AUserList.AddObject(AJob.JobId,AJob);
        end else
        begin
         for c := 0 to AJob.UserIds.Count - 1 do   //需要增加项目权限判断
        begin
          if AAssignedUser.NeedPrjRight then
          begin
            if BelongsToProject(AJob.UserIds[c],AProjectID) then
            begin
              AUser := Users.FindByID(AJob.UserIds[c]);
              if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
              begin
                AUser.CanPrint:=AAssignedUser.CanPrint;
                AUser.StepDefin :=AAssignedUser.StepDefin;
                AUser.NeedPrjRight :=AAssignedUser.NeedPrjRight;
                AUserList.AddObject(AUser.UserId,AUser);
              end;
            end;
          end
          else
          begin
            AUser := Users.FindByID(AJob.UserIds[c]);
            if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
            begin
              AUser.CanPrint:=AAssignedUser.CanPrint;
              AUser.StepDefin :=AAssignedUser.StepDefin;
              AUser.NeedPrjRight :=AAssignedUser.NeedPrjRight;
              AUserList.AddObject(AUser.UserId,AUser);
            end;
          end;
        end;
      end;
     end;
    end;
    autDepartment:      //部门
    begin
     ADepartment:=Departments.FindByID(AAssignedUser.AssignedUserID);
     if ADepartment <> nil then
     begin
        if AAssignedUser.AssignmentMode=gamSingleTask then     //单任务形式
        begin
            ADepartment.CanPrint:=AAssignedUser.CanPrint;
            ADepartment.StepDefin :=AAssignedUser.StepDefin;
            ADepartment.NeedPrjRight :=AAssignedUser.NeedPrjRight;
            AUserList.AddObject(ADepartment.DepartmentId,ADepartment);
        end else  //多任务形式
        begin
        for c := 0 to ADepartment.UserIds.Count - 1 do //需要增加项目权限判断
        begin
          if AAssignedUser.NeedPrjRight then
          begin
            if BelongsToProject(ADepartment.UserIds[c],AProjectID) then
            begin
              AUser := Users.FindByID(ADepartment.UserIds[c]);
              if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
              begin
                AUser.CanPrint:=AAssignedUser.CanPrint;
                AUser.StepDefin :=AAssignedUser.StepDefin;
                AUser.NeedPrjRight :=AAssignedUser.NeedPrjRight;
                AUserList.AddObject(AUser.UserId,AUser);
              end;
            end;
          end
          else
          begin
            AUser := Users.FindByID(ADepartment.UserIds[c]);
            if (AUser <> nil) and (AUserList.IndexOf(AUser.UserId)<0) then
            begin
              AUser.CanPrint:=AAssignedUser.CanPrint;
              AUser.StepDefin :=AAssignedUser.StepDefin;
              AUser.NeedPrjRight :=AAssignedUser.NeedPrjRight;
              AUserList.AddObject(AUser.UserId,AUser);
            end;
          end;
        end;
        end;
     end;
    end;
    autDepartmentManager:  //根据流程发起人部门来确定
    begin
          AUser := Users.FindByID(FLoggedUserId);
          DepartmenManagertid:='';
          if (AUser <> nil)  then
          begin
             for c := 0 to Departments.Count - 1 do
             begin
                if(AUser.BelongsToDepartment(Departments.Items[c].DepartmentId))  then
                begin
                   DepartmenManagertid :=Departments.Items[c].DepartmentManagerId;
                   break;
                end;
             end;

            if (DepartmenManagertid<>'') and(AUserList.IndexOf(DepartmenManagertid)<0) then
            begin
                AUser := Users.FindByID(DepartmenManagertid);
                if AUser <> nil then
                begin
                  AUser.CanPrint:=AAssignedUser.CanPrint;
                  AUser.StepDefin :=AAssignedUser.StepDefin;
                  AUser.NeedPrjRight :=False;// AAssignedUser.NeedPrjRight;
                  AUserList.AddObject(AUser.UserId,AUser);
                end;
            end;
          end;
    end;
     end;
    End;
end;

procedure TWorkflowUserManager.LoadWorkflowUsers();
begin
  (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowUserLoadList(FUsers);
end;

procedure TWorkflowUserManager.LoadWorkflowGroups();
var
  c: Integer;
begin
   (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowGroupLoadList(FGroups);
   for c := 0 to FGroups.Count - 1 do
    begin
      (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowGroupFillUserIds(FGroups[c]);
    end;
end;

procedure TWorkflowUserManager.LoadWorkflowJobs();
var
  c: Integer;
begin
  (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowJobLoadList(FJobs);
  for c := 0 to FJobs.Count - 1 do
   begin
     (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowJobFillUserIds(FJobs[c]);
   end;
end;

procedure TWorkflowUserManager.LoadWorkflowDepartments();
var
  c: Integer;
begin
   (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowDepartmentLoadList(FDepartments);
   for c := 0 to FDepartments.Count - 1 do
    begin
     (FWorkflowStudio as TWorkflowStudio).WorkflowDB.WorkflowDepartmentFillUserIds(FDepartments[c]);
    end;
end;


function TWorkflowUserManager.IsSameUser(AUserId1,
  AUserId2: string): boolean;
begin
  result := SameText(AUserId1, AUserId2);
end;

{ TTaskLogItems }

function TTaskLogItems.Add: TTaskLogItem;
begin
  result := TTaskLogItem(inherited Add);
end;

function TTaskLogItems.GetItem(Index: integer): TTaskLogItem;
begin
  result := TTaskLogItem(inherited Items[Index]);
end;

{ TCustomWorkflowDiagram }

constructor TCustomWorkflowDiagram.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FVariables := TWorkflowVariables.Create(Self, TWorkflowVariable);
  FAttachments := TWorkflowAttachments.Create(Self);
end;

destructor TCustomWorkflowDiagram.Destroy;
begin
  FAttachments.Free;
  FVariables.Free;
  inherited;
end;

function TCustomWorkflowDiagram.GetWorkflowStudio: TCustomWorkflowStudio;
begin
  if not ((csDesigning in ComponentState) or (csWriting in ComponentState)) and (FWorkflowStudio = nil) then
    raise EWorkflowException.CreateFmt('WorkflowStudio property not specified in %s object.', [ClassName])
  else
    result := FWorkflowStudio;
end;

procedure TCustomWorkflowDiagram.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited;
  if (Operation = opRemove) and (AComponent = FWorkflowStudio) then
    FWorkflowStudio := nil;
end;

procedure TCustomWorkflowDiagram.SetAttachments(const Value: TWorkflowAttachments);
begin
  FAttachments.Assign(Value);
end;

procedure TCustomWorkflowDiagram.SetDisplayTaskStatus(const Value: boolean);
begin
  FDisplayTaskStatus := Value;
end;

procedure TCustomWorkflowDiagram.SetVariables(const Value: TWorkflowVariables);
begin
  FVariables.Assign(Value);
end;

procedure TCustomWorkflowDiagram.SetWorkflowStudio(const Value: TCustomWorkflowStudio);
begin
  if FWorkflowStudio <> Value then
  begin
    FWorkflowStudio := Value;
    FAttachments.WorkflowStudio := FWorkflowStudio;
    if Value <> nil then
      Value.FreeNotification(Self);
  end;
end;

{ TCustomWorkflowStudio }

constructor TCustomWorkflowStudio.Create(AOwner: TComponent);
begin
  inherited;
  //FGroupAssignmentMode := gamMultipleTasks; //default mode
  FWorkflowEngine := TWorkflowEngine.Create(Self);
  FUserManager := TWorkflowUserManager.Create(nil, Self);
end;

destructor TCustomWorkflowStudio.Destroy;
begin
  FWorkflowEngine.Free;
  FUserManager.Free;
  if FInternalScriptEngine <> nil then
  begin
    FInternalScriptEngine.Free;
    FInternalScriptEngine := nil;
  end;
  inherited;
end;

function TCustomWorkflowStudio.GetNow: TDateTime;
begin
  if Assigned(FOnGetNow) then
    FOnGetNow(Self,Result)
  else
    Result := Now;
end;

function TCustomWorkflowStudio.GetScriptEngine: TWorkflowScriptEngine;
begin
  if FScriptEngine <> nil then
    result := FScriptEngine
  else
  begin
    if FInternalScriptEngine = nil then
    begin
      FInternalScriptEngine := ScriptEngineClass.Create(nil);
      InitializeScriptEngine(FInternalScriptEngine);
    end;
    result := FInternalScriptEngine;
  end;
end;

procedure TCustomWorkflowStudio.InitializeScriptEngine(AEngine: TWorkflowScriptEngine);
begin
  if Assigned(FOnInitializeScriptEngine) then
    FOnInitializeScriptEngine(AEngine);
end;

procedure TCustomWorkflowStudio.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited;
  if (Operation = opRemove) and (AComponent = FScriptEngine) then
    FScriptEngine := nil;
end;

{*procedure TCustomWorkflowStudio.SetGroupAssignmentMode(const Value: TGroupAssignmentMode);
begin
  if FGroupAssignmentMode <> Value then
    FGroupAssignmentMode := Value;
end;  *}

procedure TCustomWorkflowStudio.SetScriptEngine(const Value: TWorkflowScriptEngine);
begin
  if (FScriptEngine <> Value) then
  begin
    FScriptEngine := Value;
    if Value <> nil then
      Value.FreeNotification(Self);
  end;
end;

{ TCustomWorkflowBlock }

function TCustomWorkflowBlock.AcceptLink(ALink: TCustomDiagramLine;
  LinkIndex: integer; Direction: TLinkDirection): boolean;
begin
  if SingleOutput then
    Result := ((Direction = ldOutput) and (Anchoreds(ldOutput) = 0)) or (Direction = ldInput)
  else
    result := true;
end;

procedure TCustomWorkflowBlock.AdjustLinkpoints;

  procedure LinkCircle;
  begin
    {LinkPoints[0].OrX:=50; LinkPoints[0].OrY:=0;  LinkPoints[0].Orientation:=aoUp;
    LinkPoints[1].OrX:=85; LinkPoints[1].OrY:=14; LinkPoints[1].Orientation:=aoRight;
    LinkPoints[2].OrX:=100;LinkPoints[2].OrY:=50; LinkPoints[2].Orientation:=aoRight;
    LinkPoints[3].OrX:=85; LinkPoints[3].OrY:=85; LinkPoints[3].Orientation:=aoRight;
    LinkPoints[4].OrX:=50; LinkPoints[4].OrY:=100;LinkPoints[4].Orientation:=aoDown;
    LinkPoints[5].OrX:=14; LinkPoints[5].OrY:=85; LinkPoints[5].Orientation:=aoLeft;
    LinkPoints[6].OrX:=0;  LinkPoints[6].OrY:=50; LinkPoints[6].Orientation:=aoLeft;
    LinkPoints[7].OrX:=14; LinkPoints[7].OrY:=14; LinkPoints[7].Orientation:=aoLeft;}
  end;

  procedure LinkSquare;
  begin
    LinkPoints[0].OrX := 20; LinkPoints[0].OrY:=0;  LinkPoints[0].Orientation:=aoUp;
    LinkPoints[1].OrX := 50; LinkPoints[1].OrY:=0;  LinkPoints[1].Orientation:=aoUp;
    LinkPoints[2].OrX := 80; LinkPoints[2].OrY:=0;  LinkPoints[2].Orientation:=aoUp;
    LinkPoints[3].OrX := 100;LinkPoints[3].OrY:=25; LinkPoints[3].Orientation:=aoRight;
    LinkPoints[4].OrX := 100;LinkPoints[4].OrY:=50; LinkPoints[4].Orientation:=aoRight;
    LinkPoints[5].OrX := 100;LinkPoints[5].OrY:=75; LinkPoints[5].Orientation:=aoRight;
    LinkPoints[6].OrX := 80; LinkPoints[6].OrY:=100;LinkPoints[6].Orientation:=aoDown;
    LinkPoints[7].OrX := 50; LinkPoints[7].OrY:=100;LinkPoints[7].Orientation:=aoDown;
    LinkPoints[8].OrX := 20; LinkPoints[8].OrY:=100;LinkPoints[8].Orientation:=aoDown;
    LinkPoints[9].OrX := 0;  LinkPoints[9].OrY:=75; LinkPoints[9].Orientation:=aoLeft;
    LinkPoints[10].OrX := 0;  LinkPoints[10].OrY:=50; LinkPoints[10].Orientation:=aoLeft;
    LinkPoints[11].OrX := 0;  LinkPoints[11].OrY:=25; LinkPoints[11].Orientation:=aoLeft;
  end;

begin
  Case FStateShape of
    ssCircle : LinkCircle;
    ssSquare : LinkSquare;
  end;
  Top := Top - 1; // Redraw is not enough
  Top := Top + 1;
end;

function TCustomWorkflowBlock.BlockPolygon: TDotArray;

  function PolyCircle : TDotArray;
  var
    P1, P2: TDot;
    D: number;
  begin
    with Drawer.OriginalRect do
    begin
      P1 := Drawer.PP(Left, Top);
      P2 := Drawer.PP(Right, Bottom);
    end;
    D := P2.Y - P1.Y;
    result := Drawer.RotPoly(DotArray([P1, P2, Drawer.PP(D, D)]));
  end;

  function PolySquare: TDotArray;
  begin
    with Drawer do
      result := RotPoly(DotArray([
        PP(0, 0),
        PP(100, 0),
        PP(100, 100),
        PP(0, 100),
        PP(0, 0)
        ]));
  end;

begin
  case FStateShape of
    ssCircle : Result:=PolyCircle;
    ssSquare : Result:=PolySquare;
  end;
end;

procedure TCustomWorkflowBlock.GetBlockPath(APath: TDgrGraphicsPath; ADrawer: TDgrBlockDrawer);

  procedure PathCircle;
  begin
    APath.AddEllipse(0, 0, 100, 100);
  end;

  procedure PathSquare;
  begin
    APath.AddRectangle(Square(0, 0, 100, 100));
  end;

begin
  APath.Reset;
  case FStateShape of
    ssCircle : PathCircle;
    ssSquare : PathSquare;
  end;
end;

constructor TCustomWorkflowBlock.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  Shadow.Visible := true;
  FSingleOutput := true;
  Drawer.OriginalRect := Square(0, 0, 100, 100);
  Width := 100;
  Height := 50;
  FStateShape := ssSquare;
  FAutoHandleTrigger := true;
  DefaultLinkPoints;
end;

procedure TCustomWorkflowBlock.DefaultLinkPoints;
var
  c: integer;
begin
  With LinkPoints do
  begin
    Clear;
    for c := 0 to GetLinkPointsCount - 1 do
      Add(0, 0, aoUp); //Create the linkpoints
  end;
  AdjustLinkPoints;
end;

procedure TCustomWorkflowBlock.DefineProperties(Filer: TFiler);
begin
  inherited; { allow base classes to define properties }
  Filer.DefineProperty('Triggered', LoadTriggeredProp, StoreTriggeredProp, true);
end;

destructor TCustomWorkflowBlock.Destroy;
begin
  inherited;
end;

procedure TCustomWorkflowBlock.DoBeforeRun;
begin
  FTriggered :=false;
end;

function TCustomWorkflowBlock.EditorClass: TWorkflowBlockEditorClass;
begin
  result := nil;
end;

procedure TCustomWorkflowBlock.ExecuteEx(var ExecInfo: TExecuteNodeInfo);
begin
  ExecInfo.NextNode := nil;
  try
    if FAutoHandleTrigger then
    begin
      if not (FTriggered and FOneShot) then
      begin
        DoExecuteEx(ExecInfo);
        FTriggered := true;
      end;
    end
    else
      DoExecuteEx(ExecInfo);
  except
    on e: Exception do
    begin
      ExecInfo.Error := Sys_Err_Exception; // Runtime Error in DoExecute
      ExecInfo.ErrorMsg := e.Message;
      ControlState:=csRunERR;
    end;
  end;

  {if execinfo.nextnode is nil, then DoExecuteEx didn't choose the next node. So, perform the default behaviour.
   If execinfo.nextnode is not nil, then DoExecuteEx already choosed the next node}
  if ExecInfo.NextNode = nil then
  begin
    if SingleOutput then
      ExecInfo.NextNode := FNext
    else
      ExecInfo.NextNode := ScanTransitions;
  end;
  if ExecInfo.NextNode = nil then
  begin
    ExecInfo.Error := Sys_Err_Exception;
    ExecInfo.ErrorMsg := _str(SNextBlockUndefined);
  end;

  {if WaitState is undefined, then perform the default behaviour: waitandsave if nextnode is the block itself.
   it means that the workflow didn't advance}
  if ExecInfo.WaitState = wsUndefined then
  begin
    if (ExecInfo.NextNode <> Self) or (ExecInfo.Error = Sys_End_Program) then
      ExecInfo.WaitState := wsNoWait
    else
      ExecInfo.WaitState := wsWaitAndSave;
  end;

  {perform the default behaviour: if the workflow did advance (next node is not self), then set triggered back
   to false, so it can execute again the next time this function is called}
  if ExecInfo.NextNode <> Self then
  begin
    FTriggered := false;
    FOutput := '';
  end;

  WorkflowDiagram.WorkflowInstance.NextRunTime := ExecInfo.NextRunTime;
end;

function TCustomWorkflowBlock.GetLinkPointsCount: integer;
begin
  result := 12; //zws20110819
end;

function TCustomWorkflowBlock.GetNext: TCustomLiveBlock;
Var
  LinkNo : integer;

  function LinkConnected : integer;
  Var
    c : integer;
  begin
    Result := -1;
    for c := 0 to Linkpoints.Count - 1 do
      if (Linkpoints[c].AnchoredCount = 1) and //if there is only one line attached to linkpoint
        (LinkPoints[c].Anchoreds[0].DControl is TCustomDiagramLine) and //if the object attached is a line
        (TCustomDiagramLine(LinkPoints[c].Anchoreds[0].DControl).SourceLinkPoint.Anchor = Self) then //and if the line is "leaving" the linkpoint
      begin
        Result := c;
        exit;
      end;
  end;

begin
  if SingleOutput then
  begin
    Result := nil;
    LinkNo := LinkConnected;
    if LinkNo > -1 then
      Result := GetNextAt(LinkNo);
  end else
    result := inherited GetNext;
end;

procedure TCustomWorkflowBlock.FillOutputList(AOutputs: TStrings);
begin
  AOutputs.Clear;
end;

function TCustomWorkflowBlock.GetWorkflowDiagram: TCustomWorkflowDiagram;
begin
  if Diagram is TWorkflowDiagram then
    result := TWorkflowDiagram(Diagram)
  else
    result := nil; 
end;

function TCustomWorkflowBlock.Link: boolean;
begin
  if SingleOutput then
  begin
    FNext := nil;
    FNext := Next;
    Result := FNext <> nil;
  end else
    Result := (IsStartBlock or (PreviousStates.Count > 0)) and (IsEndBlock or (NextStates.Count > 0));
end;

procedure TCustomWorkflowBlock.Loaded;
begin
  inherited;
  if not (Assigned(WorkflowDiagram) and WorkflowDiagram.SavingState) then
    FTriggered := false;
end;

procedure TCustomWorkflowBlock.LoadTriggeredProp;
begin
  FTriggered := Reader.ReadBoolean;
end;

function TCustomWorkflowBlock.ScanTransitions: TCustomLiveBlock;
var
  c: integer;
  DefaultNext: TCustomLiveBlock;

  function ValidOutput(aLine: TCustomDiagramLine): boolean;
  begin
    result := (Trim(FOutput) > '') and (CompareText(aLine.DefaultTextCell.Text, FOutput) = 0);
  end;

  function ScanTransition(aLine: TCustomDiagramLine): boolean;
  begin
    Result := false;
    if aLine.InheritsFrom(TLiveWire) then
      Result := TLiveWire(aLine).Transition(Self) or ValidOutput(aLine)
      else
        if aLine.InheritsFrom(TLiveArc) then
          Result := TLiveArc(aLine).Transition(self) or ValidOutput(aLine)
          else
            if aLine.InheritsFrom(TLiveBezier) then
              Result := TLiveBezier(aLine).Transition(self) or ValidOutput(aLine)
              else
                if aLine.InheritsFrom(TLiveSideWire) then
                  Result := TLiveSideWire(aLine).Transition(Self) or ValidOutput(aLine);
  end;

  function EmptyTransition(aLine: TCustomDiagramLine): boolean;
  begin
    Result := Trim(ALine.DefaultTextCell.Text) = '';
  end;

begin
  Result := self;
  DefaultNext := nil;
  for c := 0 to NextStates.Count - 1 do
  begin
    try
      if (DefaultNext = nil) and EmptyTransition(NextStates.Transition[c]) then
        DefaultNext := NextStates.Block[c]; 

      if ScanTransition(NextStates.Transition[c]) then
      begin
        Result := NextStates.Block[c];
        exit;
      end;

      {Do the default behaviour: if output is different from empty string, then the block is finished, and it will go
      through the first transition which has no text in it}
      if (Trim(FOutput) > '') and (DefaultNext <> nil) then
      begin
        result := DefaultNext;
        exit;
      end;
    except
      Result := nil;
    end;
  end;

end;

procedure TCustomWorkflowBlock.SetFStateShape(const Value: TStateShape);
begin
  if FStateShape <> Value then
  begin
    FStateShape := Value;
    AdjustLinkpoints;
    Redraw;
  end;
end;

procedure TCustomWorkflowBlock.StoreTriggeredProp;
begin
  Writer.WriteBoolean(FTriggered);
end;

procedure TCustomWorkflowBlock.UpdateLinkPoints;
begin
// See AdjustLinkPoints
end;

function TCustomWorkflowBlock.HasOutputList: boolean;
var
  SL: TStringList;
begin
  SL := TStringList.Create;
  try
    FillOutputList(SL);
    result := SL.Count > 0;
  finally
    SL.Free;
  end;
end;

procedure TCustomWorkflowBlock.SetOutput(const Value: string);
begin
  FOutput := Value;
  FLastOutput := FOutput;
end;

end.

