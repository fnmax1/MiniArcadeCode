/* 
 * File:    st7735s.h
 * 
 * Author:  Felix Neumann
 * 
 * @desc    This file is a library for ST7735S LCD-Driver. 
 *          The library was written and tested for the ER-TFT1.44-1 display
 *          and the SAMD21J18A microcontroller. The library can be used with any
 *          other LCD and microcontroller by rewriting the Display Dimensions
 *          and the SPI-Interface. 
 * 
 * @Hw      LCD-Driver      ->      ST7735S
 *          LCD             ->      ER-TFT144-1
 *          Microcontroller ->      SAMD21J18A
 *              
 * Created on 26. September 2025, 10:43
 */

#ifndef ST7735S_H
#define	ST7735S_H

#include "delay.h"
#include "definitions.h"  
#include <stdint.h>
#include <stdlib.h>

/*
 *@Display Dimensions
 *     
 *          The coordinate system of the display has its zero point
 *          in the lower right corner.
 *          The row and column addresses range from 1 to 128. 
 *          The RAM of the ST7735S is larger than the resolution of the LCD.
 *          Since the display manufacturer has connected the LCD to the driver
 *          in an unfavorable way, the row address starts at and ends at 129. 
 *          The offset is taken into account by the preprocessor constant
 *          COL_OFFSET.
 *          Graphics functions can therefore be used normally
 *          with addresses from 1 to 128.
 */
#define ERTFT144_WIDTH		128
#define ERTFT144_HEIGHT		128
#define COL_ADR_START       2   
#define COL_ADR_END         129
#define COL_OFFSET          1             
#define ROW_ADR_START       1
#define ROW_ADR_END         128
#define MEMORY_SIZE_LCD		ERTFT144_WIDTH * ERTFT144_HEIGHT

//Success/Error
#define ST7735S_SUCCES		0
#define ST7735S_ERROR		1

//Color Coding RGB 5-6-5 (16 Bit)
#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_RED   0x001F
#define COLOR_GREEN 0x07E0
#define COLOR_BLUE  0xF800

//function macros for SPI
#define Send_Data(data)         SERCOM0_REGS->SPIM.SERCOM_DATA = (data)
#define Buisy_Wait()            while(!(SERCOM0_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_TXC_Msk)){;}
#define Send_lower_Byte(data)   SERCOM0_REGS->SPIM.SERCOM_DATA = ( (data) >> 8) & 0xFF
#define Send_upper_Byte(data)   SERCOM0_REGS->SPIM.SERCOM_DATA = (data) & 0xFF

//Command List ST7735S
#define SWRESET		0x01		//Software Reset
#define RDDID		0x04		//Read Display ID
#define RDDST		0x09		//Read Display Status
#define RDDPM		0x0A		//Read Display Power Mode
#define RDDMADCTL	0x0B		//Read Display MADCTL
#define RDDCOLMOD	0x0C		//Read Display Pixel Format
#define RDDIM		0x0D		//Read Display Image Mode
#define RDDSM		0x0E		//Read Display Signal Mode
#define RDDSDR		0x0F		//Read Display Self-Diagnostic Result
#define SLPIN		0x10		//Sleep In Mode
#define SLPOUT		0x11		//Sleep Out Mode
#define PTLON		0x12		//Partial Display Mode On
#define NORON		0x13		//Normal Display Mode on
#define IVNOFF		0x20		//Display Inversion Off
#define INVON		0x21		//Display Inversion On
#define GAMSET		0x26		//Gamma Set
#define DISPOFF		0x28		//Display Off
#define DISPON		0x29		//Display On
#define CASET		0x2A		//Column Address Set
#define RASET		0x2B		//Row Address Set
#define	RAMWR		0x2C		//Memory Write
#define RGBSET		0x2D		//Color Setting for (4K, 65K, 262K, 16,7M)
#define	RAMRD		0x2E		//Memory Read
#define PTLAR		0x30		//Partial Area
#define SCRLAR		0x33		//Scroll Area
#define TEOFF		0x34		//Tearing Effect Line Off
#define TEON		0x35		//Tearing Effect Line On
#define MADCTL		0x36		//Memory Data Access Control
#define	VSCSAD		0x37		//Vertical Scroll
#define IDMOFF		0x38		//Idle Mode Off
#define IDMONN		0x30		//Idle Mode On
#define COLMOD		0x3A		//Interface Pixel Format
#define RDID1		0xDA		//Read ID1 Value
#define RDID2		0xDB		//Read ID2 Value
#define RDID3		0xDC		//Read ID2 Value
#define FRMCTR1		0xB1		//Frame Rate Control in Normal Mode
#define	FRMCTR2		0xB2		//Frame Rate Control in Idle Mode
#define FRMCTR3		0xB3		//Frame Rate Control in Partial Mode
#define INVCTR		0xB4		//Display Inversion Control
#define PWCTR1		0xC0		//Power Control 1
#define PWCTR2		0xC1		//Power Control 2
#define PWCTR3		0xC2		//Power Control 3
#define PWCTR4		0xC3		//Power Control 4
#define PWCTR5		0xC4		//Power Control	5
#define VMCTR1		0xC5		//VCOM Control 1
#define	VMOFCTR		0xC7		//VCOM Offset Control
#define WRID2		0xD1		//Write ID2 Value
#define WRID3		0xD2		//Write ID3 Value
#define NVFCTR1		0xD9		//NV Memory Function Controller 1
#define NVFCTR2		0xDE		//NV Memory Function Controller 2
#define NVFCTR3		0xDF		//NV Memory Function Controller 3
#define GMCTRP1		0xE0		//Gamma + Polarity characteristics Setting
#define GMCTRN1		0xE1		//Gamma - Polarity characteristics Setting
#define GCFV		0xFC		//Gate Pump Clock Frequency Variable

/**
 * @desc    power on sequence of the ST7735S 
 * 
 *          This function should be used to turn on the display
 *          in order to prevent errors during the power-up phase.
 *    
 * @param   void        
 *
 * @return  void
 */
void st7735s_power_on(void);

/**
 * @desc    power off sequence of the ST7735S  
 * 
 *          This function should be used to turn off the display
 *          in order to prevent errors during the shutdown phase.
 *
 * @param   void        
 *
 * @return  void
 */
void st7735s_power_off(void);

/**
 * @desc    hardware reset of the ST7735S
 * 
 *          This function resets the ST7735S by driving the RESET-Pin low
 *          for 50 ms.
 *
 * @param   void        
 *
 * @return  void
 */
void st7735s_hardware_reset(void);

/**
 * @desc    initialize the ST7735S
 * 
 *          This function initializes the ST7735S LCD-Driver and turns on the
 *          LCD and it's Backlight. 
 *          The color coding of the display is set to RGB565 16 Bit per Pixel.
 *          The memory data access control is also configured.
 *          For detailed information read page 142 of the Data sheet.
 *         
 * @param   void        
 *
 * @return  void
 */
void st7735s_init(void);

/**
 * @desc    send a command to the ST7735S
 * 
 *          This function sends an 8 Bit command to the ST7735S.
 *          To send a command, the function uses the SPI interface of the SAMD21.
 *          The SPI mode is 0 and the clock operates at a frequency of 12 MHz. 
 *          The maximum clock frequency of the St7735S is 14 MHz.
 *          The chip select line is controlled via a GPIO.
 *          
 * @param   uint8_t cmd     ->  command                 
 *
 * @return  void
 */
inline void st7735s_send_command(uint8_t cmd)
{
    DC_Clear();
    CS_Clear();
    Send_Data(cmd);
    Buisy_Wait();
    CS_Set();
}

/**
 * @desc    send data with 8 bits to the ST7735S
 * 
 *          This function sends 8 Bit Data to the ST7735S.
 *          To send data, the function uses the SPI interface of the SAMD21.
 *          The SPI mode is 0 and the clock operates at a frequency of 12 MHz. 
 *          The maximum clock frequency of the St7735S is 14 MHz.
 *          The chip select line is controlled via a GPIO.
 *          
 * @param   uint8_t data     ->  data        
 *
 * @return  void
 */
inline void st7735s_send_data8bit(uint8_t data)
{
    DC_Set();
    CS_Clear();
    Send_Data(data);
    Buisy_Wait();
    CS_Set();
}

/**
 * @desc    send data with 16 bits to the ST7735S
 * 
 *          This function sends 16 Bit Data to the ST7735S.
 *          To send data, the function uses the SPI interface of the SAMD21.
 *          The SPI mode is 0 and the clock operates at a frequency of 12 MHz. 
 *          The maximum clock frequency of the St7735S is 14 MHz.
 *          The chip select line is controlled via a GPIO.
 *          
 * @param   uint16_t data     ->  data        
 *
 * @return  void
 */
inline void st7735s_send_data16bit(uint16_t data)
{
    DC_Set();
    CS_Clear();
    Send_lower_Byte(data);
    Buisy_Wait();
    Send_upper_Byte(data);
    Buisy_Wait();
    CS_Set();
}

/**
 * @desc    send color data to the RAM of the ST7735S
 * 
 *          This function sends the color of the pixels
 *          that are to be overwritten in the RAM of the ST7735S.
 *          The RGB format of the pixels is RGB565 16 bit per Pixel. 
 *          To send the color, the function uses the SPI interface of the SAMD21.
 *          The SPI mode is 0 and the clock operates at a frequency of 12 MHz. 
 *          The maximum clock frequency of the St7735S is 14 MHz.
 *          The chip select line is controlled via a GPIO.
 *          
 * @param   uint16_t color     ->  color       
 * @param   uint16_t counter   ->  number of pixels to be written to     
 * 
 * @return  void
 */
inline void st7735s_send_color(uint16_t color, uint16_t counter)
{
    st7735s_send_command(RAMWR);
    DC_Set();
    CS_Clear();
    while(counter--)
    {
        Send_lower_Byte(color);
        Buisy_Wait();
        Send_upper_Byte(color);
        Buisy_Wait();
    }
    CS_Set();
}

/**
 * @desc    set the window to be written to RAM
 * 
 *          This function sets the window in the RAM of the ST7735S
 *          to be written to. Once the window has been set,
 *          the st7735s_send_color() function can be used
 *          to write to the set window. 
 *          
 * @param   uint8_t XS          ->  column start address       
 * @param   uint8_t XE          ->  column end address         
 * @param   uint8_t YS          ->  row start address  
 * @param   uint8_t YE          ->  row end address
 *     
 * @return  void
 */
inline void st7735s_set_window(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE)
{
    //check if coordinates are out of range
	if(     XS > XE || XE > COL_ADR_END || 
            YS > YE	|| YE > ROW_ADR_END     )
		{
			exit(ST7735S_ERROR);
		}
    //set column address
    st7735s_send_command(CASET);
    //column address start -> XS
    st7735s_send_data16bit( 0x0000 | XS );
    //column address end -> XE
    st7735s_send_data16bit( 0x0000 | XE );
    //set row address
    st7735s_send_command(RASET);
    //row address start -> YS
    st7735s_send_data16bit( 0x0000 | YS );
    //row address end -> YE
    st7735s_send_data16bit( 0x0000 | YE );
}

#endif	/* ST7735S_H */

