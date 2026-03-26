//************************** Thread_IPC ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : PthreadCore.h
// Summary  : Function declarations of wrapper functions in PthreadCore.c
// Note     : None
// Author   : Shani 
// Date     : Mar 25, 2026 
//
//*****************************************************************************
#ifndef PTHREADCORE_H
#define PTHREADCORE_H

//******************************* Include Files ******************************* 
#include <stdbool.h>
#include <stdio.h>

#include "Common.h"

//******************************* Global Types ******************************** 

//***************************** Global Constants ****************************** 

//***************************** Global Variables ****************************** 

//**************************** Forward Declarations *************************** 
bool PthreadCoreAttrInit(pthread_attr_t* pAttributes);
bool PthreadCoreAttrSetStackSize(pthread_attr_t* pAttr, uint32_t ulStackSize);
bool PthreadCoreAttrSetPriority(pthread_attr_t* pstAttr, uint8_t ucPriority);
bool PthreadCoreAttributeDestroy(pthread_attr_t* pAttributes);
bool PthreadCoreCreateThread(const THREAD_CONFIG* pstThreadConfig,
                                                pthread_attr_t* pAttributes);
bool PthreadCoreSynchronizeThreads(const THREAD_CONFIG* pstThreadConfig);

#endif  /*PTHREADCORE_H */

// EOF 