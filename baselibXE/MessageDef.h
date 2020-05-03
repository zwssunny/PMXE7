#ifndef MessageDefH
#define MessageDefH
//---------------------------------------------------------------------------
//*注系统SOCket消息自定义消息范围(100--199)
#define UM_SOCK WM_USER+0x100

//*注系统核心消息自定义消息范围(200--999)
#define WM_REMOTEVERSION        WM_USER+200
#define WM_MODULELIST           WM_USER+201
#define WM_MODULERIGHT          WM_USER+202
#define WM_MODULEDEFRIGHT       WM_USER+203
#define WM_MODULEDEFFUNC        WM_USER+204
#define WM_DATAACCESS           WM_USER+205
#define WM_GETFORMCODE          WM_USER+206
#define WM_GETCLASSCODE         WM_USER+207
#define WM_GETPRJLEVEL          WM_USER+208
#define WM_CHANGEPWD            WM_USER+209
#define WM_GETGROUPDATA         WM_USER+210
#define WM_GETUSERDATA          WM_USER+211
#define WM_GETLOGINFO           WM_USER+212
#define WM_GETMIDCLASSLIST          WM_USER+213
#define WM_GETCLASSUSERCODEFIELD           WM_USER+214


//*注:ServerDataSet自定义消息范围(1000--1099)
#define WM_SERVER_DATALOAD      WM_USER+1000

//*注:ClientDataSet自定义消息范围(1100--1199)
#define WM_DATASET_LOADDATA     WM_USER+1100
#define WM_RESUME_THREAD        WM_USER+1101
#define WM_TERMINATE_THREAD     WM_USER+1102
#define WM_SUSPEND_THREAD       WM_USER+1103

//*注:ClientQuery自定义消息范围(1200-1299)

//*注:AppServer自定义消息范围(1300-1399)
#define WM_NEWSERVERCOMM_MSG    WM_USER+1300
#define WM_DELSERVERCOMM_MSG    WM_USER+1301

//*注:ServerComm自定义消息范围(1400--1499)
#define WM_REGISTER_CLIENTCOMM  WM_USER+1400

//*注:AgentServer自定义消息范围(1500--1599)
#define WM_INTERFACE_DATA       WM_USER+1500
#define WM_YW_TERMINATETHREAD   WM_USER+1501
#define WM_USERCLIENTCOUNT      WM_USER+1502
#define WM_USERCLIENTCLOSE      WM_USER+1503
//*注:WatchComm自定义消息范围(1600--1699)
#define YW_CONN_WATCH           WM_USER+1600
#define YW_REG_WATCH            WM_USER+1601
#define YW_RECV_STATUS          WM_USER+1602
#define YW_RECV_USERDATA        WM_USER+1603
#define YW_RECV_APPDATA         WM_USER+1604

//*注:AgentComm自定义消息范围(1700--1799)
#define WM_AGENTCOMM_STATUS     WM_USER+1700

//*注:BuildComm自定义消息范围(1800--1899)
#define WM_BUILDCOMM_STATUS     WM_USER+1800

//*注:ClientComm自定义消息范围(1900-1999)
#define ACTIVE_APPSOCKET_MSG    WM_USER+1900
#define SHOW_LOGINFORM_MSG      WM_USER+1901
#define WM_CLOSE_DATASET        WM_USER+1902
#define WM_LOGIN_STATUS         WM_USER+1903
#define WM_SHOW_CLIENTFORM      WM_USER+1904
#define WM_CLOSE_CLIENTFORM     WM_USER+1905
#define WM_SHOWMODAL_CLIENTFORM WM_USER+1906
#define WM_FORMS_CHANGED        WM_USER+1907
#define WM_SHOWMODAL_BYFORMID   WM_USER+1908
#define WM_CLIENTCOMM_CONNETSTATE WM_USER+1909
#define WM_SOCKETDATA_ARRIVER    WM_USER+1910
#define WM_SYSTEMMESSAGE_ARRIVER   WM_USER+1911
//*注:BaseForm系列自定义消息范围(2000--2099)
#define WM_YW_REFRESH_MSG       WM_USER+2000
#define WM_YW_RESULT_MSG        WM_USER+2001
#define WM_YW_FORMRIGHT_MSG     WM_USER+2002
#define WM_YW_LOCATEGRID_MSG    WM_USER+2003
#define WM_YW_LOCATE_MSG 		WM_USER+2004
//---------------------------------------------------------------------------
#endif

