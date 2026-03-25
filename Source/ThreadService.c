//**************************** Thread_IPC *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved 
//*****************************************************************************
//
// File      : ThreadService.c
// Summary   : InFunction that connects thread handlers to core functions.
// Note      : None
// Author    : Shani
// Date      : Mar 25, 2026
//
//***************************************************************************** 

//******************************* Include Files *******************************
#include "ThreadService.h"

//******************************* Local Types ********************************* 
 
//***************************** Local Constants ******************************* 

//***************************** Local Variables ******************************* 

//****************************** Local Functions ****************************** 

//***************************** ThreadHandlerRun ******************************
//Purpose   : Initializes and starts the system threads
//Inputs    : None
//Outputs   : None
//Return    : true if the thread system started and synchronized successfully, 
//            false otherwise.
//Notes     : None.
//******************************************************************************
bool ThreadHandlerRun(void)
{
 /*    bool blStatus = false;

    blStatus = PosixHandlerInitSemaphores();

    if (true == blStatus)
    {
        if (true == PosixHandlerCreateThreads())
        {
            if (false == PosixHandlerSynchronizeThreads())
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
    }
 
    return blStatus; */
}