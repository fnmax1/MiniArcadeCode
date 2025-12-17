/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "st7735s.h"
#include "symbols.h"
#include "gfx.h"
#include "delay.h"
#include "font.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    //Register callback function for TC3 period interrupt
    TC3_TimerCallbackRegister(TC3_Callback_InterruptHandler, (uintptr_t)NULL);
  
    //Initialite LCD-Driver ST7735S
    st7735s_init();
    fill_display(COLOR_WHITE);
    delay_ms(1000);
    
    draw_string(10,60,"Hello World", COLOR_BLUE, COLOR_BLACK, 1, SIZE_14);
    //fill_circle(64,64,20,COLOR_RED);
    //draw_line(1,60,128,60,COLOR_RED);
    //draw_line_horizontal(60,66,59,COLOR_RED);
    //delay_ms(250);
    //draw_line_vertical(60,72,59,COLOR_GREEN);
    //draw_bitMap(64, 64, &Pacman_Ghost);
    //TCC0_Compare24bitMatchSet(TCC0_CHANNEL0, 51);
    //TCC0_CompareStart();   
    
    //shut display down
    //st7735s_power_off();
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        //ER-TFT-144-1 demo
        //ERTFT144_demo(); 
        
                  
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

