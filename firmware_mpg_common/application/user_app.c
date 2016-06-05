/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserAppFlags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */
extern u8 G_au8DebugScanfBuffer[];                     /* From debug.c */
extern u8 G_u8DebugScanfCharCount;                     /* From debug.c  */
/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp_StateMachine;            /* The state machine function pointer */
static u32 UserApp_u32Timeout;                      /* Timeout counter used across states */
static u8 UserApp_au8UserInputBuffer[USER_INPUT_BUFFER_SIZE];  /* Char buffer */
static u8 UserApp_au8MyName[] = "A3.xusunan";
static u8 u8NameBuffer[200];
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
Function: UserAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserAppInitialize(void)
{
   /* Backlight to  CYAN*/  
  LedOff(LCD_RED);
  LedOn(LCD_GREEN);
  LedOn(LCD_BLUE); 
  LCDMessage(LINE1_START_ADDR, UserApp_au8MyName);
  LCDClearChars(LINE1_START_ADDR + 10, 11); 
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp_StateMachine = UserAppSM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp_StateMachine = UserAppSM_FailedInit;
  }

} /* end UserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function UserAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserAppRunActiveState(void)
{
  UserApp_StateMachine();

} /* end UserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void UserAppSM_Idle(void)
{ 
      static u8 u8counter2=0;
      static u8 u8counter=0;
      static u8 u8charIndex=0;
      static u8 flag=FALSE;
      static u8 BlinkCount=0;
      u8 u8CharCount;
      BlinkCount++;
      static u8 u8NumCharsMessage[] = "\n\rCharacters in buffer: \n";
      static u8 u8NumCharsMessage2[] = "\n\rThe buffer is empty:";
      static u8 u8CurrentMessage[] = "\n\rmessage is:\n";
    //  u8 UserApp_u8NameBuffer[]="";
      u8 Myname[]="xusunan";
    
      u8 i=0;
      u8 j=0;
      static u8 u8NameCount=0;
         
      if(BlinkCount==10)
      {
      BlinkCount=0;
      flag=TRUE;
      }
      if(flag)
      {
          /* Read the buffer and print the contents */
          u8CharCount = DebugScanf(UserApp_au8UserInputBuffer);
          UserApp_au8UserInputBuffer[u8CharCount] = '\0';
          if(u8CharCount!=0);
          {
            for(u8 i=0;i<u8CharCount;i++)
            {
                LCDMessage(LINE2_START_ADDR+u8charIndex,UserApp_au8UserInputBuffer);
                 u8charIndex++;
                
               if(u8charIndex==21)
                {
                  LCDClearChars(LINE2_START_ADDR , 20); 
                  LCDMessage(LINE2_START_ADDR,UserApp_au8UserInputBuffer);
                  u8charIndex=1;
                }
                u8counter++;
               u8counter2++;
            }
                 
                 
       } 
        flag=FALSE;
      }

      if(WasButtonPressed(BUTTON0))
      {
      ButtonAcknowledge(BUTTON0);
      LCDClearChars(LINE2_START_ADDR , 20);
      u8charIndex=0;

      }

      if(WasButtonPressed(BUTTON1))
      {
      ButtonAcknowledge(BUTTON1);
      DebugPrintf(u8NumCharsMessage);
      DebugPrintNumber(u8counter);
     // DebugLineFeed();
      }
       if(WasButtonPressed(BUTTON2))
      {
        ButtonAcknowledge(BUTTON2);
        DebugPrintf(u8NumCharsMessage2);
        u8counter=0;
      }
      
      for(i=0;i<7;i++)
      {
        for(j=0;j<u8counter2;j++)
        {
          if(Myname[i]==UserApp_au8UserInputBuffer[j])
          {
             u8NameBuffer[i]=UserApp_au8UserInputBuffer[j];
            //u8NameBuffer[i+1]='\0';
          }
          i++;
          if( i==7)
           {
              i=0;
              u8NameCount++;
       
             }
          
          } 
      }
     // if(WasButtonPressed(BUTTON3))
    //  {
     //   ButtonAcknowledge(BUTTON3);
      //  DebugPrintf(u8CurrentMessage);
      //  DebugPrintf(u8NameBuffer);
      
     // }
      
        
    

 
}/* end UserAppSM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserAppSM_Error(void)          
{
  
} /* end UserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserAppSM_FailedInit(void)          
{
    
} /* end UserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
