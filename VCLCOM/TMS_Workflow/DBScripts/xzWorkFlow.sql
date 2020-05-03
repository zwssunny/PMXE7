--流程分类
CREATE TABLE tbFlowClass(
FlowClsPKID  varchar(8)    not null ,
FlowClsName  varchar(100)    not null ,
FlowClsPKID_Upper  varchar(8)    not null ,
FlowClsSortCode  varchar(80)    not null ,
   CONSTRAINT PK_tbFlowClass PRIMARY KEY  NONCLUSTERED (FlowClsPKID)
)
--流程定义
CREATE TABLE tbFlowDefin(
FlowDnPKID  varchar(40)    not null ,
FlowDnName  varchar(100)    not null ,
FlowDnExplan  varchar(255)   null ,
FlowDnFKID_Cls  varchar(8)    not null default '',
FlowDnIsPublic  int    not null default 0,
FlowDnIsTerm tinyint    not null default 0,
FlowDnDate datetime    not null default GETDATE(),--新增字段，创建时间
FlowDnCreator  varchar(40)   null ,--新增字段，创建人
FlowDnContent text   null ,--新增字段，保存流程图
   CONSTRAINT PK_tbFlowDefin PRIMARY KEY  NONCLUSTERED (FlowDnPKID)
); 
--流程实例
CREATE TABLE tbFlowMain(
FlowMnPKID  varchar(40)    not null ,
FlowMnCreateTime  varchar(19)    not null ,
FlowMnCreator  varchar(40)    not null ,
FlowMnSubject  varchar(100)    not null ,
FlowMnContent  varchar(300)    not null ,
FlowMnBusWindow  varchar(10)    not null ,
FlowMnBusCode  varchar(100)    not null ,
FlowMnState  int    not null default 0,
FlowMnRank  int    not null ,
FlowMnIsStop  int    not null default 0,
FlowMnFKID_Flow  varchar(40)    not null ,
FlowMoveTimeLimit  int    not null default 0,
FlowMnLastUpdateTime  varchar(19)   null ,
FlowMnFlowContent text   null ,
FlowMnReport  varchar(40)   null ,
FlowMnFinishTime  varchar(19)   null ,
FlowMnNextTime  varchar(19)   null ,
FlowMnPrjID  varchar(40)   null default '',
   CONSTRAINT PK_tbFlowMain PRIMARY KEY  NONCLUSTERED (FlowMnPKID)
); 
--任务实例，流程执行步骤
CREATE TABLE tbFlowMain_Detail(
FlowMnDtlPKID  varchar(40)    not null ,
FlowMnDtlFKID  varchar(40)    not null ,
FlowMnDtlNum  int    not null ,
FlowMnDtlSender  varchar(40)    not null ,
FlowMnDtlReceiver  varchar(40)   null ,
FlowMnDtlSendTime  varchar(19)    not null ,
FlowMnDtlRecTime  varchar(19)   null ,
FlowMnDtlChkTime  varchar(19)   null ,
FlowMnDtlLimitTime  varchar(19)   null ,
FlowMnDtlComments  varchar(200)    not null ,
FlowMnDtlState  int    not null ,
FlowMnDtlResults  varchar(20)   null ,
FlowMnDtlStateChgTime  varchar(19)   null ,
FlowMnDtlPrintRight tinyint    not null default 0,
FlowMnDtlRemark  varchar(200)   null ,
FlowMnDtlName  varchar(100)    not null ,
FlowMnDtlTaskContent text   null ,
FlowMnDtlUserType  int    not null ,
FlowMnDtlStep  int    not null default 0,
FlowMnDtlNeedPrjRight tinyint    not null default 0,
FlowMnDtlPrjID  varchar(40)   null default '',
   CONSTRAINT PK_tbFlowMain_Detail PRIMARY KEY  NONCLUSTERED (FlowMnDtlPKID)
); 
--任务实例操作日志 
CREATE TABLE tbFlowTaskLog (
    FlowTaskLogTaskInsID varchar(40) NOT NULL,--任务实例
    FlowTaskLogFlowInsID Varchar(40) NOT NULL,--流程实例
    FlowTaskLogDate DATETIME NOT NULL,
    FlowTaskLogOperation VARCHAR(1) NOT NULL,
    FlowTaskLogUserID VARCHAR(40),
    FlowTaskLogInfo VARCHAR(100),
    FlowTaskLogInfo2 VARCHAR(100),
    PRIMARY KEY (FlowTaskLogTaskInsID,
    FlowTaskLogDate,
    FlowTaskInsOperation)
)
GO
--tbFlowStep流程定义步骤
--tbFlowStep_Detail流程定义审批人
--tbFlowStep_DetailTemp实例流程步骤
--tbFlowTerm流程必要条件
--上面四个表将取消，改成全部保存在流程图内容里面
--流程实例附件关联表
CREATE TABLE tbFlowMain_Attch (
    FlowMnAthPKFKID  varchar(40)    not null ,
    FlowMnAthPKFKID_Ath  varchar(40)    not null ,
   CONSTRAINT PK_tbFlowMain_Attch PRIMARY KEY  NONCLUSTERED (FlowMnAthPKFKID,FlowMnAthPKFKID_Ath)
); 
 --业务窗体关联的流程定义，作为默认处理流程
CREATE TABLE tbFlowOperation(
FlowOperPKID  varchar(10)    not null ,
FlowOperPKID_Flow  varchar(40)    not null ,
   CONSTRAINT PK_tbFlowOperation PRIMARY KEY  NONCLUSTERED (FlowOperPKID,FlowOperPKID_Flow)
)
--流程实例关联报表
CREATE TABLE tbFlowReport(
FlowRptPKFKID  varchar(40)    not null ,
FlowRptFKID_OAChk  varchar(40)    not null ,
   CONSTRAINT PK_tbFlowReport PRIMARY KEY  NONCLUSTERED (FlowRptPKFKID)
);
 --职位资料
CREATE TABLE tbNewDuty(
NewDutyPKID  varchar(8)    not null ,
NewDutyName  varchar(40)    not null ,
NewDutyFKID_Upper  varchar(8)    not null ,
NewDutySortCode  varchar(80)    not null ,
   CONSTRAINT PK_tbNewDuty PRIMARY KEY  NONCLUSTERED (NewDutyPKID)
); 
--角色资料
CREATE TABLE tbRoleData(
RolePKID  varchar(8)    not null ,
RoleName  varchar(100)    not null ,
RoleDiscript  varchar(255)    not null ,
   CONSTRAINT PK_tbRoleData PRIMARY KEY  NONCLUSTERED (RolePKID)
); 
--员工资料
CREATE TABLE tbEmployeeData(
EmpPKID  varchar(40)    not null ,
EmpName  varchar(20)    not null ,
EmpSex tinyint    not null ,
EmpDutyFKID  varchar(20)    not null ,
EmpContactTel  varchar(20)    not null ,
EmpBirthday  varchar(10)    not null ,
EmpNative  varchar(50)    not null ,
EmpGraduatSchool  varchar(30)    not null ,
EmpMajor  varchar(30)    not null ,
EmpDegree  varchar(20)    not null ,
EmpEnterDutyDate  varchar(10)    not null ,
EmpState tinyint    not null ,
EmpLeaveDate  varchar(10)    not null ,
EmpLeaveReason  varchar(80)    not null ,
EmpContactWay  varchar(50)    not null ,
EmpNote  varchar(50)    not null ,
EmpDeptCodeFKID  varchar(20)    not null ,
EmpMonthSalary  decimal(18,6)    not null ,
EmpSalesPs tinyint    not null ,
EmpMobile  varchar(40)    not null default '',
EmpNum  varchar(40)    not null default '',
   CONSTRAINT PK_tbEmployeeData PRIMARY KEY  NONCLUSTERED (EmpPKID)
); 
--员工职位对应表
CREATE TABLE tbEmpDuty(
EDEmpPK_FKID  varchar(40)    not null ,
EDDutyPK_FKID  varchar(20)    not null ,
   CONSTRAINT PK_tbEmpDuty PRIMARY KEY  NONCLUSTERED (EDEmpPK_FKID,EDDutyPK_FKID)
);  
--角色员工对应表
CREATE TABLE tbRoleEmp(
RERolePK_FKID  varchar(8)    not null ,
REEmpPK_FKID  varchar(40)    not null ,
   CONSTRAINT PK_tbRoleEmp PRIMARY KEY  NONCLUSTERED (RERolePK_FKID,REEmpPK_FKID)
);
 --部门资料
CREATE TABLE tbCorporationOrganize(
CorpOgnPKID  varchar(8)    not null ,
CorpOgnDeptName  varchar(100)    not null ,
CorpOgnFKID_Upper  varchar(8)    not null ,
CorpOgnSortCode  varchar(80)    not null ,
CorpOgnDeptManager  varchar(40)    not null ,
CorpOgnTel  varchar(20)    not null ,
CorpOgnWorkAddress  varchar(50)    not null ,
CorpOgnRemark  varchar(255)    not null ,
CorpOgnDeptNum  varchar(40)    not null default '',
CorpOgnLead  varchar(40)    not null default '',
   CONSTRAINT PK_tbCorporationOrganize PRIMARY KEY  NONCLUSTERED (CorpOgnPKID)
);
/*  
truncate table tbFlowMain_Attch 
truncate table tbFlowTaskLog 
truncate table tbFlowMain_Detail 
truncate table tbFlowMain 
*/