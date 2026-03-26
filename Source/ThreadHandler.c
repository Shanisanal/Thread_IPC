//**************************** Thread_IPC *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved 
//*****************************************************************************
//
// File      : ThreadHandler.c
// Summary   : Implementation of the primary thread routines .
// Note      : None
// Author    : Shani
// Date      : Mar 25, 2026
//
//***************************************************************************** 

//******************************* Include Files *******************************
#include "ThreadHandler.h"

//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 

//***************************** Local Variables ******************************* 

//****************************** Local Functions ****************************** 

//*************************** ThreadHandlerPoller *****************************
//Purpose   : High-priority Poller thraed for Button press detection
//Inputs    : pArguments - Pointer to the THREAD_CONFIG structure for this thread
//Outputs   : None
//Return    : NULL
//Notes     : Runs with SCHED_FIFO priority 80. Must include a sleep/yield 
//            to prevent CPU starvation of lower priority threads.
//*****************************************************************************
void* ThreadHandlerPoller(void* pArguments)
{
    THREAD_CONFIG* pstPollerConfig = NULL;

    do
    {
        if (NULL == pstPollerConfig)
        {
            printf("ERROR: Poller started with NULL configuration!\r\n");
            break;
        }

        pstPollerConfig = (THREAD_CONFIG*)pArguments;
        printf("[%s] Thread Started (Priority: %d)\r\n", 
        pstPollerConfig->pcThreadName, pstPollerConfig->ucPriority);

        while (1)
        {

            usleep(100000); 
        }


    } while (0);
    
    return NULL;
}

//************************** ThreadHandlerTransport ***************************
//Purpose   : Moves gpio pin state from the Poller to the Logger
//Inputs    : pArguments - Pointer to the THREAD_CONFIG structure
//Outputs   : None
//Return    : NULL (Single return point)
//Notes     : Runs with SCHED_FIFO priority 70.
//*****************************************************************************
void* ThreadHandlerTransport(void* pArguments)
{
    THREAD_CONFIG* pstTransportConfig = (THREAD_CONFIG*)pArguments;

    do 
    {
        if (NULL == pstTransportConfig)
        {
            printf("ERROR: Transport received NULL configuration! .\r\n");
            break; 
        }

        printf("SUCCESS: [%s] Thread Started (Priority: %d).\r\n", 
                pstTransportConfig->pcThreadName,pstTransportConfig->ucPriority);

        while (1)
        {

            usleep(150000); 
        }

    } while (0);
      
    return NULL; 
}

//**************************** ThreadHandlerLogger ****************************
//Purpose   : Final Logger thread for turning on LED
//Inputs    : pArguments - Pointer to the THREAD_CONFIG structure
//Outputs   : None
//Return    : NULL 
//Notes     : Runs with SCHED_FIFO priority 50.
//*****************************************************************************
void* ThreadHandlerLogger(void* pArguments)
{
    THREAD_CONFIG* pstLoggerConfig = (THREAD_CONFIG*)pArguments;

    do 
    {
        if (NULL == pstLoggerConfig)
        {
            printf("ERROR: Logger received NULL configuration!.\r\n");
            break; 
        }

        printf("SUCCESS: [%s] Thread Started (Priority: %d).\r\n", 
                pstLoggerConfig->pcThreadName, pstLoggerConfig->ucPriority);

        // 2. The Main Execution Loop
        while (1)
        {

            usleep(200000); 
        }

    } while (0);

    return NULL; 
}