//************************** Thread_IPC ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : ThreadService.h
// Summary  : Header file defining the thread service functions.
// Note     : None
// Author   : Shani 
// Date     : Mar 25, 2026 
//
//*****************************************************************************
#ifndef THREADSERVICE_H
#define THREADSERVICE_H

//******************************* Include Files ******************************* 
#include "Common.h"
#include "PthreadCore.h"
#include "ThreadHandler.h"

//******************************* Global Types ******************************** 
 
//***************************** Global Constants ****************************** 
#define STACK_SIZE_POLLER       (1 * 1024)
#define STACK_SIZE_TRANSPORT    (1 * 1024)
#define STACK_SIZE_LOGGER       (1 * 1024)
#define PRIORITY_POLLER         80
#define PRIORITY_TRANSPORT      70
#define PRIORITY_LOGGER         50

//***************************** Global Variables ****************************** 

//**************************** Forward Declarations *************************** 
bool ThreadServiceRun(void);
bool ThreadServiceCreateThreads (void);
bool ThreadServiceSynchronizeThreads(void);

//*********************** Inline Method Implementations *********************** 

#endif  /*THREADSERVICE_H*/

// EOF 