//---------------------------------------------------------------------------

#ifndef rwdogH
#define rwdogH
//---------------------------------------------------------------------------
#define SNLENGHT  21
bool CheckSoftDog(void); //打开软件狗之前
bool OpenSoftDog(void);  //需要读写时，先执行该函数，
                         //在执行该函数时，先执行CheckSoftDog()或ReadDogSerial(AnsiString &dserial)
bool CloseSoftDog(void); //不再读写时，执行该函数
bool InitializeDog(void);//无论什么状态都会强制初始化,软件狗必须打开
bool ReadDogSerial(AnsiString &dserial);//无需打开，则可读取软件狗ID
//0
bool WriteRegistCode(AnsiString regcode);//写注册码
bool ReadRegistCode(AnsiString &regcode);//读注册码
bool ReadVersionCode(AnsiString &Version);
//1
bool ReadTrialTimes(int &ttimes);
bool WriteTrialTimes(int ttimes);
bool ReadUsedTimes(int &utimes);
bool WriteUsedTimes(int utimes);
//2
bool ReadDogStatus(int &status); //status:0-已激活,1-未激活,2-已初始化,3-未初始化
bool StartUsing(void);//设置状态为未激活状态,不成功则可以通过ReadDogStatus来读取当前状态
bool SetDogActive(void);//不成功则可以通过ReadDogStatus来读取当前状态
//3
bool ReadProductSerial(AnsiString &pserial);
bool WriteProductSerial(AnsiString pserial);
//4
bool ReadUserCount(int &UserCount);
bool WriteUserCount(int UserCount);
bool ReadUserCount2(int &UserCount2);
bool WriteUserCount2(int UserCount2);

//判断该模块是否可用iModule=[0..79](缓冲区)，首次先调用ReadModulesInfor();
bool GetModuleIsExists(int iModule);

//将该模块设置为可用(缓冲区),要调用WriteModulesInfor()，才写入软件狗
//首次调用之前先调用ReadModulesInfor();
bool SetModuleIsExists(int iModule,bool bIsExists);

bool ReadModulesInfor(); //从软件狗读出模块可用信息，保存到缓冲区

bool WriteModulesInfor();//把模块缓冲区内容写入软件狗

//往缓冲区一次性读取所有模块信息，调用前先执行ReadModulesInfor函数
char* GetAllModulesInfor();
AnsiString GetAllModulesSign(); //用法同上，只不过返回的值为以'\t'隔开的模块号

//往缓冲区一次性写入所有模块信息,最后须调用WriteModulesInfor函数才能写入软件锁
//mInfors由'0'和'1'组成的字符串，可定义0到79号模块
bool SetAllModulesInfor(char* mInfors);

//返回该模块是否可用，确认调用之前先调用ReadModulesInfor
bool IsModuleCanUse(int iModuleCode);
//写vip标志
bool WriteVIPSigner(bool bIsVip);
//读vip标志
bool ReadVIPSigner(bool &bIsVip);
//写Remoter标志
bool WriteRemoterSigner(bool bIsRemoter);
//读Remoter标志
bool ReadRemoterSigner(bool &bIsRemoter);
//写密匙
bool WriteUIDKey(AnsiString UIDKey);
//读密匙
bool ReadUIDKey(AnsiString &UIDKey);
AnsiString EncryptStr(AnsiString str);
//写个人登录密钥 ,长度不能少于6位
bool WriteUserIDKey(AnsiString UserIDKey);
//读个人登录密钥
bool ReadUserIDKey(AnsiString &UserIDKey);
#endif
