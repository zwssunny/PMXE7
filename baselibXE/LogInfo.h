#ifndef LogInfoH
#define LogInfoH
#include <string.h>
//---------------------------------------------------------------------------
typedef struct LogInfo
{
  bool IsSystemer; //系统管理员
  bool IsRemoter;  //是否是从远程启动	
  int  AgentPort; //端口
  Char AccBookID[10];//登录帐套号
  Char UserCode[20]; //用户编号
  Char UserEmpID[40];//员工id
  Char LogonCode[20]; //登录用户号,在总包版以前版本未使用
  Char UserName[20]; //登录用户名
  Char AccBookName[20];//登录帐套名称
  Char Version[20];//版本
  Char AgentAddress[30];//代理地址
  Char SoftName[40];//软件名称
  Char Email[100];//电子邮件
  Char HomePage[255];//主页
  //ftp
  int  ftpPort;  //ftp端口
  bool ftpNeedFTP; //是否启用ftp
  bool ftpPassive; //是否被动
  Char ftpIP[64]; //外部/内部服务器地址 ,已经根据客户端连接情况确定
  Char ftpUserName[20];  //登录用户
  Char ftpPassword[20];  //登录密码
  //QQ
  Char QQID[20];       //QQID号
  Char QQPassword[20];   //QQ登陆口令
  //mail
  Char mailServer[255];  //邮件服务器
  Char sendEMail[100];  //发送邮箱
  Char mailUserName[20]; //登录用户名
  Char mailPassword[20]; //登录密码
  int  mailPort;        //连接端口
  Char UpdateURL[255];
}TLogInfo;
#endif
