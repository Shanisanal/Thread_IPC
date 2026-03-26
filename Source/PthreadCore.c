//**************************** Thread_IPC *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved 
//*****************************************************************************
//
// File      : PthreadCore.c
// Summary   : A centralized utility file for wrapping standard pthread calls
// Note      : None
// Author    : Shani
// Date      : Mar 25, 2026
//
//***************************************************************************** 

//******************************* Include Files *******************************
#include "PthreadCore.h"

//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 

//***************************** Local Variables ******************************* 

//****************************** Local Functions ****************************** 

//*************************** PthreadCoreAttrInit *****************************
//Purpose   : Initialize the thread attributes 
//Inputs    : pAttributes - pointer to the pthread attribute union
//Outputs   : None
//Return    : true if attribute Success, false - Initialization failed
//Notes     : None
//*****************************************************************************
bool PthreadCoreAttrInit(pthread_attr_t* pAttributes)
{
    bool blStatus = true;

    do
    {
        if(NULL == pAttributes)
        {
            blStatus = false;
            printf("ERROR: Attribute init failed - Null pointer.\r\n");
            break; 
        }

        if(SUCCESS_RETURN != pthread_attr_init(pAttributes))
        {
            blStatus = false;
            printf("ERROR: pthread_attr_init failed with error code\r\n");
            break; 
        }

    } while (0);
    
    return blStatus;
}

//************************ PthreadCoreAttrSetStackSize ************************
//Purpose   : Set the stack size in the thread attributes
//Inputs    : pAttr - pointer to the pthread attribute union
//            ulStackSize - size of stack in bytes
//Outputs   : None
//Return    : true - If stack size setting success, false - Failed to set stack size
//Notes     : None
//*****************************************************************************
bool PthreadCoreAttrSetStackSize(pthread_attr_t* pAttr, uint32_t ulStackSize)
{
    bool blStatus = true;

    do
    {
        if (NULL == pAttr)
        {
            blStatus = false;
            printf("ERROR: Stack set failed - Null pointer.\r\n");
            break; 
        }

        if (SUCCESS_RETURN != pthread_attr_setstacksize(pAttr, ulStackSize))
        {
            blStatus = false;
            printf("ERROR: pthread setting stacksize failed.\r\n");
            break; 
        }

    } while (0);
    
    return blStatus;
}

//************************* PthreadCoreAttrSetPriority ************************
//Purpose   : Set scheduling policy to FIFO and set thread priority
//Inputs    : pstAttr - pointer to the pthread attribute structure
//            ucPriority - priority value
//Outputs   : None
//Return    : true - Success, false - Failed to set priority
//Notes     : Requires SCHED_FIFO for real-time priority levels
//*****************************************************************************
bool PthreadCoreAttrSetPriority(pthread_attr_t* pAttr, uint8_t ucPriority)
{
    bool blStatus = false;
    struct sched_param stSchedParam = {0};

    do
    {
        if (NULL == pAttr)
        {
            blStatus = false;
            printf("ERROR: Priority set failed - Null pointer.\r\n");
            break; 
        }

        if (SUCCESS_RETURN != pthread_attr_setschedpolicy(pAttr, SCHED_FIFO))
        {
            blStatus = false;
            printf("ERROR: Failed to set SCHED_FIFO scheduling algorithm.\r\n");
            break;
        }

        stSchedParam.sched_priority = ucPriority;
        if (SUCCESS_RETURN != pthread_attr_setschedparam(pAttr, &stSchedParam))
        {
            blStatus = false;
            printf("ERROR: Failed to set priority parameter.\r\n");
            break;
        }

        if (SUCCESS_RETURN != pthread_attr_setinheritsched(pAttr, PTHREAD_EXPLICIT_SCHED))
        {
            blStatus = false;
            printf("ERROR: Failed to set explicit scheduling.\r\n");
            break;
        }

    } while (0);

    return blStatus;
}

//************************* PthreadCoreAttrDestroy ****************************
//Purpose   : Destroy the thread attributes object to release allocated memory
//Inputs    : pAttributes - Pointer to the initialized pthread attribute structure
//Outputs   : None
//Return    : true if the thread attribute object is successfully destroyed 
//            false if failed to destroy thread attribute object
//Notes     : None
//*****************************************************************************
bool PthreadCoreAttributeDestroy(pthread_attr_t* pAttributes)
{
    bool blStatus = true;

    do
    {
        if (NULL == pAttributes)
        {
            blStatus = false;
            printf("ERROR: Attribute destroy failed - Null pointer provided.\r\n");
            break; 
        }

        if (SUCCESS_RETURN != pthread_attr_destroy(pAttributes))
        {
            blStatus = false;
            printf("ERROR: pthread_attr_destroy failed. \r\n");
            break; 
        }

    } while (0);
    
    return blStatus;
}

//************************* PthreadCoreCreateThread.***************************
//Purpose   : Create POSSIX thread with specific attributes
//Inputs    : pstThreadConfig - pointer to the thread config structure
//            pAttributes     - pointer to the initialized pthread attributes
//Outputs   : None
//Return    : true if thread created successfully, false if thread creation failed
//Notes     : None
//*****************************************************************************
bool PthreadCoreCreateThread(const THREAD_CONFIG* pstThreadConfig,
                                                    pthread_attr_t* pAttributes)
{
    bool blReturn = true;

    do
    {
        if (NULL == pstThreadConfig || NULL == pAttributes)
        {
            blReturn = false;
            printf("ERROR: Thread creation failed - Null pointer.\r\n");
            break; 
        }

        if (SUCCESS_RETURN != pthread_create(pstThreadConfig->pulThreadId, pAttributes,
                            pstThreadConfig->ThreadHandler, (void*)pstThreadConfig))
        {
            printf("ERROR: %s Creation failed\r\n", pstThreadConfig->pcThreadName);
            blReturn = false;
            break;
        }
        else
        {
            printf("%s Created Successfully\r\n", pstThreadConfig->pcThreadName);
        }

    } while (0);

    return blReturn;
}

//************************* PthreadCoreSynchronizeThreads **********************
//Purpose    : Synchronizes a POSIX thread
//Inputs     : pulThread - pointer to the thread ID variable
//             pcThreadName - name of the thread for logging purposes
//Outputs    : None
//Return     : true if thread synchronized successfully, false if 
//             synchronization failed
//Notes      : None
//*****************************************************************************
bool PthreadCoreSynchronizeThreads(const THREAD_CONFIG* pstThreadConfig)
{
    bool blReturn = true;

    do 
    {
        if (NULL == pstThreadConfig)
        {
            printf("ERROR: Synchronization failed - Null configuration pointer.\r\n");
            blReturn = false;
            break; 
        }

        if(SUCCESS_RETURN != pthread_join(*(pstThreadConfig->pulThreadId), NULL))
        {
            printf("ERROR: %s Synchronization failed with status \r\n",
                    pstThreadConfig->pcThreadName);
            blReturn = false;
            break;
        }

    } while (0);
    
    return blReturn;
}