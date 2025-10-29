#include "st7735s.h"

void st7735s_power_on(void)
{
    VDD_Set();
    VDDI_Set();
    delay_ms(150);   
}

void st7735s_power_off(void)
{
	RESET_Clear();
    delay_ms(150);
    VDD_Clear();
    VDDI_Clear();
    BLA_Clear();
}

void st7735s_hardware_reset(void)
{
    RESET_Clear();
    delay_ms(50);
    RESET_Set();
    delay_ms(50);
}

void st7735s_init(void)
{
	//power on sequence 
	st7735s_power_on();
	//turn Backlight on
    BLA_Set();
    //hardware reset
    st7735s_hardware_reset();
    //software reset
    st7735s_send_command(SWRESET);
    delay_ms(120);
    //sleep in mode -> sleep out mode
    st7735s_send_command(SLPOUT);
    delay_ms(120);
    //select display color coding -> 16bit/pixel
    st7735s_send_command(COLMOD);
    st7735s_send_data8bit(0x05);
    //memory data acces control
    st7735s_send_command(MADCTL);
    st7735s_send_data8bit(0x00);
    //normal mode on
    st7735s_send_command(NORON);
    //display on
    st7735s_send_command(DISPON);
    delay_ms(10);
}
