//************************** Thread_IPC ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : ThreadHandler.h
// Summary  : Header file defining the thread callback functions.
// Note     : None
// Author   : Shani 
// Date     : Mar 25, 2026 
//
//*****************************************************************************
#ifndef THREADHANDLER_H
#define THREADHANDLER_H

//******************************* Include Files ******************************* 
#include "Common.h"
#include "ThreadService.h"

//******************************* Global Types ******************************** 
 
//***************************** Global Constants ****************************** 

//***************************** Global Variables ****************************** 

//**************************** Forward Declarations *************************** 
void* ThreadHandlerPoller(void* pArguments);
void* ThreadHandlerTransport(void* pArguments);
void* ThreadHandlerLogger(void* pArguments);

//*********************** Inline Method Implementations *********************** 

#endif  /*THREADHANDLER_H*/

// EOF 