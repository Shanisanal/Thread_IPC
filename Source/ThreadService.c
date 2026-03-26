//**************************** Thread_IPC *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved 
//*****************************************************************************
//
// File      : ThreadService.c
// Summary   : Function that connects thread handlers to core functions.
// Note      : None
// Author    : Shani
// Date      : Mar 25, 2026
//
//***************************************************************************** 

//******************************* Include Files *******************************
#include "ThreadService.h"

//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 
#define TOTAL_THREADS           (sizeof(sstThreadConfigTable) / \
                                sizeof(sstThreadConfigTable[0]))

//***************************** Local Variables ******************************* 
pthread_t gulUPollerThreadId    = 0; 
pthread_t gulTransportThreadId  = 0;
pthread_t gulLoggerThreadId     = 0;

//****************************** Local Functions ****************************** 
static bool ThreadServiceConfigureAttributes(pthread_attr_t* pAttr, uint8_t ucIndex);

static const THREAD_CONFIG sstThreadConfigTable[] = 
{
    {
        &gulUPollerThreadId, ThreadHandlerPoller, POLLER_THREAD, 
        STACK_SIZE_POLLER, PRIORITY_POLLER
    },
    {
        &gulTransportThreadId, ThreadHandlerTransport, TRANSPORT_THREAD, 
        STACK_SIZE_TRANSPORT, PRIORITY_TRANSPORT
    },
    {
        &gulLoggerThreadId, ThreadHandlerLogger, LOGGER_THREAD, 
        STACK_SIZE_LOGGER, PRIORITY_LOGGER
    }
};

//***************************** ThreadHandlerRun ******************************
//Purpose   : Initializes and starts the system threads
//Inputs    : None
//Outputs   : None
//Return    : true if the thread system started and synchronized successfully, 
//            false otherwise.
//Notes     : None.
//******************************************************************************
bool ThreadServiceRun(void)
{
    bool blStatus = true;

    if(true == ThreadServiceCreateThreads())
    {
        if (false == ThreadServiceSynchronizeThreads())
        {
            printf("ERROR: Failed to sync system threads.\n");
            blStatus = false;
        }
   
    }
    else
    {
        printf("ERROR: Failed to create system threads.\n");
        blStatus = false;
    }

    return blStatus; 
}

//********************** ThreadServiceConfigureAttributes *********************
//Purpose   : Configures stack size and priority for a specific thread index
//Inputs    : pAttr   - Pointer to initialized pthread_attr_t
//            ucIndex - Index of the thread in the configuration table
//Outputs   : None
//Return    : true if stack size and priority configured successfully 
//            false if any of the configuration failed.
//Notes     : None
//*****************************************************************************
static bool ThreadServiceConfigureAttributes(pthread_attr_t* pAttr, uint8_t ucIndex)
{
    bool blStatus = true;

    do
    {
        if(NULL == pAttr)
        {
            blStatus = false;
            printf("[%s] ERROR: Configuration failed. Null pointer.\r\n", 
                    sstThreadConfigTable[ucIndex].pcThreadName);
            break;
        }

        if (false == PthreadCoreAttrSetStackSize(pAttr, 
                                 sstThreadConfigTable[ucIndex].ulStackSize))
        {
            blStatus = false;
            printf("[%s] ERROR: Stack size config failed.\r\n", 
                    sstThreadConfigTable[ucIndex].pcThreadName);
            break;
        }

        if (false == PthreadCoreAttrSetPriority(pAttr, 
                                 sstThreadConfigTable[ucIndex].ucPriority))
        {
            blStatus = false;
            printf("[%s] ERROR: Priority configuration failed.\r\n", 
                    sstThreadConfigTable[ucIndex].pcThreadName);
            break;
        }

    } while (0);

    return blStatus;
}

//******************************* ThreadServiceCreateThreads *******************
//Purpose   : Create all system threads with the specified attributes
//Inputs    : None
//Outputs   : None
//Return    : true if all threads were successfully created, false if any thread 
//            creation failed.
//Notes     : None
//******************************************************************************
bool ThreadServiceCreateThreads (void) 
{
    bool blStatus             = true;
    pthread_attr_t Attributes = {0};
    bool blAttrInitialized    = false;

    for (uint8_t ucIndex = 0; ucIndex < TOTAL_THREADS; ucIndex++)
    {
        blAttrInitialized    = false;

        do
        {
            if(false == PthreadCoreAttrInit(&Attributes))
            {
                blStatus = false;
                printf("[%s]ERROR: Attribute init failed for thread:\n\r", 
                        sstThreadConfigTable[ucIndex].pcThreadName);
                break;
            }

            blAttrInitialized = true;
 
            if (false == ThreadServiceConfigureAttributes(&Attributes, ucIndex))
            {
                blStatus = false;
                printf("[%s]ERROR: Configuring attributes failed for thread:\n\r", 
                sstThreadConfigTable[ucIndex].pcThreadName);
                break;
            }

            if (false == PthreadCoreCreateThread(&sstThreadConfigTable[ucIndex],
                                                                   &Attributes))
            {
                blStatus = false;
                break;
            }
        } while (0);

        if (true == blAttrInitialized)
        {
            if(false == PthreadCoreAttributeDestroy(&Attributes))
            {
                printf("[%s] WARNING: Failed to destroy attributes.\r\n", 
                                sstThreadConfigTable[ucIndex].pcThreadName);
            }
        }

        if (false == blStatus)
        {
            break; 
        }
        
    }

    return blStatus; 
}

//*********************** ThreadServiceSynchronizeThreads **********************
//Purpose   : Synchronizes the threads
//Inputs    : None
//Outputs   : None
//Return    : true if all threads synchronized successfully , false if any 
//            thread failed to join.
//Notes     : None
//******************************************************************************
bool ThreadServiceSynchronizeThreads(void)
{
    bool blStatus = true;

    for (uint8_t ucIndex = 0; ucIndex < TOTAL_THREADS; ucIndex++)
    {
        if (false == PthreadCoreSynchronizeThreads(&sstThreadConfigTable[ucIndex]))
        {
            blStatus = false;
        }
    }

    return blStatus;
}
