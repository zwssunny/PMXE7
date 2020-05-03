/****************************************************************************
*                                                                           *
* coredef.h -- Basic Type Definitions                                  *
*                                                                           *
* Copyright (c) 2000-2009,  All rights reserved.                            *
*                                                                           *
****************************************************************************/
#ifndef _COREDEF_
#define _COREDEF_
typedef enum tagValidVerFlag
{
  vfNoneAct = 0,        //不匹配时不做其它操作
  vfExitNoHint = 1,     //不匹配时不提示退出系统
  vfExitAndHint = 2,    //不匹配时提示并退出系统
} ValidVerFlag;


#endif /* _COREDEF_ */
