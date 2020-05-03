#ifndef SafeDataDefH
#define SafeDataDefH

#define SAFETY_FILE_DESC    1024      /*安全文件说明*/
#define SAFETY_FILE_TYPE    1056      /*安全文件类型*/
#define SAFETY_FILE_INIT    1060      /*安全文件初始化标识*/
#define SAFETY_MODULE_TAG   1064      /*模块数据初始化标识*/
#define SAFETY_WINDOW_TAG   1065      /*前台窗体数据初始化标识*/
#define SAFETY_USERDEFFUNC_TAG  1066  /*自定义功能数据初始化标识*/
#define SAFETY_USERDEFRIGHT_TAG 1067  /*自定义权限数据初始化标识*/
#define SAFETY_LIBFILE_TAG  1068      /*前台库文件数据初始化标识*/
#define SAFETY_SYSTEM_TAG   1069      /*系统权限初数据始化标识*/

#define SAFETY_DATAADDR     4096                      /*数据基地址*/
#define POLIC_ORIKEY_ADDR   SAFETY_DATAADDR+0         /*安全配置文件密码地址1*/
#define POLIC_DESKEY_ADDR   SAFETY_DATAADDR+4         /*安全配置文件密码地址2*/
#define POLIC_LICSIZE_ADDR  SAFETY_DATAADDR+8         /*安全配置文件许可证文件大小地址*/
#define LIC_ORIKEY_ADDR     SAFETY_DATAADDR+0         /*许可证文件密码地址1*/
#define LIC_DESKEY_ADDR     SAFETY_DATAADDR+4         /*许可证文件密码地址2*/
#define LIC_PRJLEVEL_ADDR   SAFETY_DATAADDR+8         /*许可证文件项目层级地址*/
#define LIC_MODULE_SIZE     SAFETY_DATAADDR+12        /*许可证文件模块数据大小*/
#define LIC_MODULE_ADDR     SAFETY_DATAADDR+16        /*许可证文件模块数据地址*/
#define LIC_WINDOW_SIZE     SAFETY_DATAADDR+20        /*许可证文件窗体数据大小*/
#define LIC_WINDOW_ADDR     SAFETY_DATAADDR+24        /*许可证文件窗体数据地址*/
#define LIC_USERDEFFUNC_SIZE SAFETY_DATAADDR+28       /*许可证文件自定义功能数据大小*/
#define LIC_USERDEFFUNC_ADDR SAFETY_DATAADDR+32       /*许可证文件自定义功能数据地址*/
#define LIC_USERDEFRIGHT_SIZE SAFETY_DATAADDR+36      /*许可证文件自定义权限数据大小*/
#define LIC_USERDEFRIGHT_ADDR SAFETY_DATAADDR+40      /*许可证文件自定义权限数据地址*/
#define LIC_LIBFILE_SIZE    SAFETY_DATAADDR+44        /*许可证文件前台库文件数据大小*/
#define LIC_LIBFILE_ADDR    SAFETY_DATAADDR+48        /*许可证文件前台库文件数据地址*/
#define LIC_SYSTEM_SIZE     SAFETY_DATAADDR+52        /*许可证文件系统权限数据大小*/
#define LIC_SYSTEM_ADDR     SAFETY_DATAADDR+56        /*许可证文件系统权限数据地址*/
#define LIC_DATA_ADDR       SAFETY_DATAADDR+1024      /*许可证文件数据基地址*/

#endif 