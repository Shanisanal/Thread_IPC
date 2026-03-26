//************************** Thread_IPC ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : Common.h
// Summary  : Contains Centralized definitions, shared structures, and global 
//            declarations
// Note     : None
// Author   : Shani 
// Date     : Mar 25, 2026 
//
//*****************************************************************************
#ifndef COMMON_H
#define COMMON_H

//******************************* Include Files ******************************* 
#include <pthread.h>
#include <mqueue.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

//******************************* Global Types ******************************** 
 
//***************************** Global Constants ****************************** 
#define POLLER_THREAD       "Poller_Thread"
#define TRANSPORT_THREAD    "Transport_Thread"
#define LOGGER_THREAD       "Logger_Thread"
#define SUCCESS_RETURN      0
#define MSG_QUEUE_ERR       -1
//***************************** Global Variables ****************************** 
typedef struct _THREAD_CONFIG_
{
    pthread_t* pulThreadId;     
    void* (*ThreadHandler)(void*); 
    const char* pcThreadName;
    uint32_t ulStackSize;    
    uint8_t  ucPriority;
} THREAD_CONFIG;

//**************************** Forward Declarations *************************** 

//*********************** Inline Method Implementations *********************** 

#endif  /*COMMON_H */

// EOF 