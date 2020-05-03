// ---------------------------------------------------------------------------

#ifndef ServerCtlH
#define ServerCtlH
// ---------------------------------------------------------------------------
// 成功返回0,失败返回非0
extern PACKAGE int SCCreateService(Char *lpComputerName, Char *lpServiceName,
	Char *lpDisplayName, Char *lpFileName);
// 成功返回0,失败返回非0
extern PACKAGE int SCDeleteService(Char *lpComputerName, Char *lpServiceName);
// 成功返回0,失败返回非0
extern PACKAGE int SCStartService(Char *lpComputerName, Char *lpServiceName);
// 成功返回0,失败返回非0
extern PACKAGE int SCStopService(Char *lpComputerName, Char *lpServiceName);
// 成功返回0,失败返回非0
extern PACKAGE int SCPauseService(Char *lpComputerName, Char *lpServiceName);
// 成功返回0,失败返回非0
extern PACKAGE int SCResumeService(Char *lpComputerName, Char *lpServiceName);
// 成功返回0,失败返回非0
extern PACKAGE int SCQueryServiceStatus(Char *lpComputerName,
	Char *lpServiceName, int &lpServiceStatus);
#endif
