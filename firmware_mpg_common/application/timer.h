/**********************************************************************************************************************
File: timer.h                                                                

Description:
Header file for yournewtaskname.c

**********************************************************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/
typedef enum {TIMER_CHANNEL0 = 0, TIMER_CHANNEL1 = 0x40, TIMER_CHANNEL2 = 0x80} TimerChannelType;


/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
/* Timer Channel 1 Setup
Timer Channel 1  will generate 10.667us interrupts
Note:
PA26 Peripheral B is an open pin avaialble as external clock input TCLK2
PB5 Peripheral A is an open pin available for TIOA1 I/O function
PB6 Peripheral A is an open pin available for TIOB1 I/O function
*/

/* Timer 1 interrupt period (1 tick = 2.67us); max 65535 */
#define TC1_RC_INIT (u32)

#define TC1_CCR_INIT (u32)
/*
    31-04 [0] Reserved

    03 [] Reserved
    02 [] SWTRG 
    01 [] CLKDIS 
    00 [] CLKEN 
*/


#define TC1_CMR_INIT (u32)0x
/*
    31 [] BSWTRG 
    30 [] "
    29 [] BEEVT 
    28 [] "

    27 [] BCPC 
    26 [] "
    25 [] BCPB
    24 [] "

    23 [] ASWTRG
    22 [] "
    21 [] AEEVT 
    20 [] "

    19 [] ACPC 
    18 [] "
    17 [] ACPA
    16 [] "

    15 [] WAVE 
    14 [] WAVSEL 
    13 [] "
    12 [] ENETRG 

    11 [] EEVT 
    10 [] "
    09 [] EEVTEDG 
    08 [] "

    07 [] CPCDIS 
    06 [] CPCSTOP 
    05 [] BURST 
    04 [] "

    03 [] CLKI 
    02 [] TCCLKS 
    01 [] "
    00 [] "
*/

#define TC1_IER_INIT (u32)0x
/*
    31 -08 [0] Reserved 

    07 [] ETRGS RC Load interrupt not enabled
    06 [] LDRBS RB Load interrupt not enabled
    05 [] LDRAS RA Load interrupt not enabled
    04 [] CPCS RC compare interrupt is enabled

    03 [] CPBS RB compare interrupt not enabled
    02 [] CPAS RA Compare Interrupt enabled
    01 [] LOVRS Lover's bit? Load Overrun interrupt not enabled 
    00 [] COVFS Counter Overflow interrupt not enabled
*/

#define TC1_IDR_INIT (u32)0x
/*
    31-08 [0] Reserved 

    07 [] ETRGS RC Load interrupt disabled
    06 [] LDRBS RB Load interrupt disabled
    05 [] LDRAS RA Load interrupt disabled
    04 [] CPCS RC compare interrupt not disabled

    03 [] CPBS RB compare interrupt disabled
    02 [] CPAS RA Compare Interrupt not disabled
    01 [] LOVRS Lover's bit?!? Load Overrun interrupt disabled 
    00 [] COVFS Counter Overflow interrupt disabled
*/


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/
void TimerStart(?);
void TimerStop(?);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void TimerInitialize(void);
void TimerRunActiveState(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
inline void TimerDefaultCallback(void);


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void TimerAppSM_Idle(void);    

static void TimerAppSM_Error(void);         
static void TimerAppSM_FailedInit(void);        


#endif /* __TIMER_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
