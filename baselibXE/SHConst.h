#ifndef SHConstH
#define SHConstH

//const AnsiString ckInterceptGUID = "" ;
static const String ckInterceptGUID = "{9167BA0D-F3CA-4590-82E8-4EB711E21FBF}" ;
static const String SServiceName = "XZAppServer";
static const String SApplicationName = "Foresight Application Server" ;
static const String SMessageChannel="FSMessage";
static const String SMsgCallback="FSMessageCallBack";
static const String SCMDChannel="FSCMD";
static const String SCMDCallback="FSCMDCallBack";
static const String SWFCallback="FSWFCallBack";
static const String SSmsCallback="FSSmsCallBack";
//static const Word CallSig = 0xda00;
//static const Word ResultSig = 0xdb00;
//static const Shortint asError = 0x1;
//static const Byte asMask = 0xff;
static const int asGetAccList= 0x30;
static const int asLogIn= 0x31;
static const int asConnectAppSucMsg= 0x32;
static const int asUserCountChange= 0x33;
static const int asCloseAppThread= 0x34;
static const int asChangePassWord= 0x35;
static const int asUserGroupList= 0x36;
static const int asUserList= 0x37;
static const int asClassList= 0x38;
static const int asAutoCodeFields= 0x39;
static const int asAppRegist= 0x3a;
static const int asAppAvareable= 0x3b;
static const int asAppWorkLoad= 0x3c;
static const int asAppDataSyn= 0x3d;
static const int asCreateServerComm= 0x3e;
static const int asClientMenuData=0x3f;
static const int asMgrLogin= 0x20;
static const int asGetAgentState= 0x22;
static const int asGetUserOnLine= 0x23;
static const int asGetAppList= 0x24;
static const int asChangeAccList= 0x25;
static const int asMgrSendMessage= 0x26;
static const int asUserInfoToApp= 0x40;
static const int asUserSendMessage= 0x41;
static const int asClientConnectedMessage= 0x42;
static const int asDSError= 0x50;
static const int asCreateSDataSet= 0x51;
static const int asSDataSetFree= 0x52;
static const int asDSOpen= 0x53;
static const int asDSUpdate= 0x54;
static const int asDSDelete= 0x55;
static const int asDSDeleteDetail= 0x56;
static const int asDSCheck= 0x57;
static const int asDSCloseOff= 0x58;
static const int asDSCancel= 0x59;
static const int asDSRecord= 0x5a;
static const int asDSCommExecute= 0x5b;
static const int asDSVerify= 0x5c;
static const int asDSSQL= 0x5d;
//下面是调用账套库
static const int asQError= 0x60;
static const int asQueryOpen= 0x61;
static const int asQueryUpdate= 0x62;
static const int asQueryDelete= 0x63;
static const int asQuerySQL= 0x64;
//下面是调用系统库
static const int asQuerySysOpen= 0x71;
static const int asQuerySysUpdate= 0x72;
static const int asQuerySysDelete= 0x73;
static const int asQuerySysSQL= 0x74;
// Service State -- for CurrentState
//
#define SERVICE_STOPPED                        0x00000001
#define SERVICE_START_PENDING                  0x00000002
#define SERVICE_STOP_PENDING                   0x00000003
#define SERVICE_RUNNING                        0x00000004
#define SERVICE_CONTINUE_PENDING               0x00000005
#define SERVICE_PAUSE_PENDING                  0x00000006
#define SERVICE_PAUSED                         0x00000007

#endif
