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
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern AntSetupDataType G_stAntSetupData;                         /* From ant.c */

extern u32 G_u32AntApiCurrentDataTimeStamp;                       /* From ant_api.c */
extern AntApplicationMessageType G_eAntApiCurrentMessageClass;    /* From ant_api.c */
extern u8 G_au8AntApiCurrentData[ANT_APPLICATION_MESSAGE_BYTES];  /* From ant_api.c */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp_StateMachine;            /* The state machine function pointer */
static u32 UserApp_u32Timeout;                      /* Timeout counter used across states */


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
  
  /* Configure ANT for this application */
  G_stAntSetupData.AntChannel          = ANT_CHANNEL_USERAPP;
  G_stAntSetupData.AntSerialLo         = ANT_SERIAL_LO_USERAPP;
  G_stAntSetupData.AntSerialHi         = ANT_SERIAL_HI_USERAPP;
  G_stAntSetupData.AntDeviceType       = ANT_DEVICE_TYPE_USERAPP;
  G_stAntSetupData.AntTransmissionType = ANT_TRANSMISSION_TYPE_USERAPP;
  G_stAntSetupData.AntChannelPeriodLo  = ANT_CHANNEL_PERIOD_LO_USERAPP;
  G_stAntSetupData.AntChannelPeriodHi  = ANT_CHANNEL_PERIOD_HI_USERAPP;
  G_stAntSetupData.AntFrequency        = ANT_FREQUENCY_USERAPP;
  G_stAntSetupData.AntTxPower          = ANT_TX_POWER_USERAPP;

  /* If good initialization, set state to Idle */
  if( AntChannelConfig(ANT_MASTER) )
  {
    AntOpenChannel();
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
  u8 NumberToAscii(u32 u32Number_,u8*pu8AsciiString_);
   static u8 au8TestMessage[] = {0, 0, 0, 0, 0xA5, 0, 0, 0};
   u8 au8DataContent[] = "xxxxxxxxxxxxxxxx";
   u8  au8LastData[8]={0};
  
   //LCDClearChars(LINE1_START_ADDR , 20);
  if( AntReadData() )
  {
     static u8 u8TimeStamp[]=0;
    /* New data message: check what it is */
    if(G_eAntApiCurrentMessageClass == ANT_DATA)
    {
            /* We got some data */
            /* New data message: check what it is */
            LedOff(RED); 
            LedOff(ORANGE); 
            LedOff(YELLOW); 
            LedOff(GREEN);
            LedOff(CYAN);
            LedOff(BLUE);
            LedOff(PURPLE);
            LedOff(WHITE);

            if( G_au8AntApiCurrentData[0] == 0xFF )
            {
            LedOn(WHITE);
            }   

            if( G_au8AntApiCurrentData[1] == 0xFF )
            {
            LedOn(PURPLE);
            } 
            if( G_au8AntApiCurrentData[2] == 0xFF )
            {
            LedOn(BLUE);
            }  
            if( G_au8AntApiCurrentData[3] == 0xFF )
            {
            LedOn(CYAN);
            }
            if( G_au8AntApiCurrentData[4] ==0xFF )
            {
            LedOn(GREEN);
            } 
            if( G_au8AntApiCurrentData[5] == 0xFF )
            {
            LedOn(YELLOW);
            } 
            if( G_au8AntApiCurrentData[6] == 0xFF )
            {
            LedOn(ORANGE);
            } 
            if( G_au8AntApiCurrentData[7] == 0xFF )
            {
            LedOn(RED);
            }

            /* We got some data: parse it into au8DataContent */
            for(u8 i = 0; i < ANT_DATA_BYTES; i++)
            {
            au8DataContent[2 * i]     = HexToASCIICharUpper(G_au8AntApiCurrentData[i] / 16);
            au8DataContent[2 * i + 1] = HexToASCIICharUpper(G_au8AntApiCurrentData[i] % 16);
            au8LastData[i]= au8DataContent[i];

            }

            LCDMessage(LINE2_START_ADDR,au8DataContent ); 

    
            /*check data if change*/
            for(u8 j = 0; j < 8;j++)
            {
            if(au8LastData[j]!=G_au8AntApiCurrentData[j])

            au8LastData[j]=G_au8AntApiCurrentData[j];
            NumberToAscii(G_u32AntApiCurrentDataTimeStamp,u8TimeStamp);
            LCDMessage(LINE1_START_ADDR,u8TimeStamp);
            LCDClearChars(LINE1_START_ADDR +5, 13);

            }
    }
            else if(G_eAntApiCurrentMessageClass == ANT_TICK)
            {
            /* A channel period has gone by: typically this is when new data should be queued to be sent */
            /*updata the message counter*/


            /* Update and queue the new message data */
            au8TestMessage[7]++;
            if(au8TestMessage[7] == 0)
            {
            au8TestMessage[6]++;
            }
            if(au8TestMessage[6] == 0)
            {
            au8TestMessage[5]++;
            }
            
            

     /*    now check the current*/ 
  /* Check all the buttons and update au8TestMessage according to the button state */ 
  au8TestMessage[0] = 0x00;
  if( IsButtonPressed(BUTTON0) )
  {
    au8TestMessage[0] = 0xff;
  }
    au8TestMessage[1] = 0x00;
  if( IsButtonPressed(BUTTON1) )
  {
    au8TestMessage[1] = 0xff;
  }
   au8TestMessage[2] = 0x00;
  if( IsButtonPressed(BUTTON2) )
  {
    au8TestMessage[2] = 0xff;
  }
     au8TestMessage[3] = 0x00;
  if( IsButtonPressed(BUTTON3) )
  {
    au8TestMessage[3] = 0xff;
  }
  
    AntQueueBroadcastMessage(au8TestMessage);
   }
  
  }
    /* end AntReadData() */
} /* end UserAppSM_Idle() */
     

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
