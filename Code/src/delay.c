#include "delay.h"

volatile bool delayDone = false;

void TC3_Callback_InterruptHandler(TC_TIMER_STATUS status, uintptr_t context)
{
    delayDone = true;
}

void delay_ms(uint16_t delayTime)
{
    
    for (TC3_TimerStart(); delayTime!= 0; delayTime--)
    {
        
    delayDone = false;
    
    while(!delayDone)
    {
        //wait until delayTime is over
    }
    
    }
     
    TC3_TimerStop();
}