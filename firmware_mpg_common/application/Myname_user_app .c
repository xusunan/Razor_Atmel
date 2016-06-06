/**********************************************************************************************************************
File: Myname_myname_MYNAME_USER_APP.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this Myname_myname_MYNAME_USER_APP as a template:
 1. Copy both Myname_myname_MYNAME_USER_APP.c and Myname_myname_MYNAME_USER_APP.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "Myname_myname_MYNAME_USER_APP" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "MynameUserApp" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "MYNAME_USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a Myname_myname_MYNAME_USER_APP.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void MynameUserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void MynameUserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32MynameUserAppFlags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */
extern volatile u8 flag2;
extern volatile u16 BlinkCount2 ; 

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "MynameUserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type MynameUserApp_StateMachine;            /* The state machine function pointer */
static u32 MynameUserApp_u32Timeout;                      /* Timeout counter used across states */
  /* Char buffer */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: MynameUserAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void MynameUserAppInitialize(void)
{
   
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    MynameUserApp_StateMachine = MynameUserAppSM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    MynameUserApp_StateMachine = MynameUserAppSM_FailedInit;
  }

} /* end MynameUserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function MynameUserAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void MynameUserAppRunActiveState(void)
{
  MynameUserApp_StateMachine();

} /* end MynameUserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void MynameUserAppSM_Idle(void)
{ 
    static u16 u16BlinkCount2=0;
    u16BlinkCount2++;
    if(flag2)
    {
      
      PWMAudioOn(BUZZER1);
      PWMAudioSetFrequency(BUZZER1,500);
      LedBlink(RED,LED_1HZ);
        if(BlinkCount2==5000)
       {
         BlinkCount2=0;
         PWMAudioOff(BUZZER1);
          LedOff(RED);
          flag2=FALSE;
       }
    }
         
 }/* end MynameUserAppSM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void MynameUserAppSM_Error(void)          
{
  
} /* end MynameUserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void MynameUserAppSM_FailedInit(void)          
{
    
} /* end MynameUserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
