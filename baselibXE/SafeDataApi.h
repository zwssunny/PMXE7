/****************************************************************************
 *                                                                           *
 * SafeDataApi.h -- Basic  API Definitions                                  *
 *                                                                           *
 * Copyright (c) 2000-2008,  All rights reserved.                            *
 * last modify sunny zhan 2008,6,7                                                                          *
 ****************************************************************************/
// ---------------------------------------------------------------------------
#ifndef SafeDataApiH
#define SafeDataApiH
// ---------------------------------------------------------------------------

extern PACKAGE int InitializeSafety(void);
extern PACKAGE int GetPolicKey(int dwPrimalKey);
extern PACKAGE int SetPolicKey(int dwPolicKey, int dwPrimalKey);
extern PACKAGE int GetLicFileSize(int dwPolicKey);
extern PACKAGE int SetLicFileSize(int dwLicSize, int dwPolicKey);

extern PACKAGE int GetLicenseKey(int dwPolicKey);
extern PACKAGE int SetLicenseKey(int dwLicKey, int dwPolicKey);
extern PACKAGE int GetProjectLevel(int dwLicKey);
extern PACKAGE int SetProjectLevel(int dwLevel, int dwLicKey);

extern PACKAGE int GetModuleSize(int dwLicKey); // 返回压缩后的数据大小
extern PACKAGE int GetModuleAddr(int dwLicKey);
extern PACKAGE int GetModuleActualSize(int dwLicKey); // 返回解压后的数据大小
extern PACKAGE int GetModuleData(Char *szDataBuf, int dwSize, int dwLicKey);
// dwSize-ActualSize
extern PACKAGE int SetModuleData(const Char *szDataBuf, int dwSize,
	int dwLicKey); // dwSize-ActualSize

extern PACKAGE int GetWindowSize(int dwLicKey); // 返回压缩后的数据大小
extern PACKAGE int GetWindowAddr(int dwLicKey);
extern PACKAGE int GetWindowActualSize(int dwLicKey); // 返回解压后的数据大小
extern PACKAGE int GetWindowData(Char *szDataBuf, int dwSize, int dwLicKey);
extern PACKAGE int SetWindowData(const Char *szDataBuf, int dwSize,
	int dwLicKey);

extern PACKAGE int GetUserDefRightSize(int dwLicKey);
extern PACKAGE int GetUserDefRightAddr(int dwLicKey);
extern PACKAGE int GetUserDefRightActualSize(int dwLicKey);
extern PACKAGE int GetUserDefRightData(Char *szDataBuf, int dwSize,
	int dwLicKey);
extern PACKAGE int SetUserDefRightData(const Char *szDataBuf, int dwSize,
	int dwLicKey);

extern PACKAGE int GetUserDefFuncSize(int dwLicKey);
extern PACKAGE int GetUserDefFuncAddr(int dwLicKey);
extern PACKAGE int GetUserDefFuncActualSize(int dwLicKey);
extern PACKAGE int GetUserDefFuncData(Char *szDataBuf, int dwSize,
	int dwLicKey);
extern PACKAGE int SetUserDefFuncData(const Char *szDataBuf, int dwSize,
	int dwLicKey);

extern PACKAGE int GetLibFileSize(int dwLicKey);
extern PACKAGE int GetLibFileAddr(int dwLicKey);
extern PACKAGE int GetLibFileActualSize(int dwLicKey);
extern PACKAGE int GetLibFileData(Char *szDataBuf, int dwSize, int dwLicKey);
extern PACKAGE int SetLibFileData(const Char *szDataBuf, int dwSize,
	int dwLicKey);

extern PACKAGE int GetSystemRightSize(int dwLicKey);
extern PACKAGE int GetSystemRightAddr(int dwLicKey);
extern PACKAGE int GetSystemRightActualSize(int dwLicKey);
extern PACKAGE int GetSystemRightData(Char *szDataBuf, int dwSize,
	int dwLicKey);
extern PACKAGE int SetSystemRightData(const Char *szDataBuf, int dwSize,
	int dwLicKey);

#endif
