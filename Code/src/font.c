#include "font.h"

uint8_t txt_x_pos = 0;
uint8_t txt_y_pos = 0;
uint8_t char_idx = 0;

static const uint8_t img_data_0x41_sz_10[13] =
{
    0xfe,                 
    0xfe, 
    0xfe, 
    0xee, 
    0xd6, 
    0xd6, 
    0xba, 
    0x82, 
    0xba, 
    0x7c, 
    0xfe, 
    0xfe, 
    0xfe
};
static const char_t char_0x41_sz_10 = { img_data_0x41_sz_10 , 7 , 13 };

static const uint8_t img_data_0x42_sz_10[13] =
{
    0xfe, 
    0xfe, 
    0xfe, 
    0x86, 
    0xba, 
    0xba, 
    0x82, 
    0xba, 
    0xba, 
    0x86, 
    0xfe, 
    0xfe, 
    0xfe
};
static const char_t char_0x42_sz_10 = { img_data_0x42_sz_10 , 7 , 13 };

static const uint8_t img_data_0x43_sz_10[13] =
{
    0xfe, 
    0xfe, 
    0xfe, 
    0xc6, 
    0xba, 
    0xbe, 
    0xbe, 
    0xbe, 
    0xba, 
    0xc6, 
    0xfe, 
    0xfe, 
    0xfe
};
static const char_t char_0x43_sz_10 = { img_data_0x43_sz_10 , 7 , 13 };

const char_t* fontset_sz_10[3] =
{
  &char_0x41_sz_10,      //'A'   (0x41)  
  &char_0x42_sz_10,      //'B'   (0x42)
  &char_0x43_sz_10,      //'C'   (0x43)    
};

void draw_char(uint8_t curr_x_pos, uint8_t curr_y_pos, const char* ch, uint16_t bg_color, uint16_t font_color)
{
    char_idx = *ch - 'A';
    uint8_t char_width = fontset_sz_10[char_idx]->width;
    uint8_t char_height = fontset_sz_10[char_idx]->height;
    uint8_t bit_mask;
    st7735s_set_window( curr_x_pos, ( curr_x_pos + (char_width - 1) ), curr_y_pos, ( curr_y_pos + (char_height - 1) ) );
    st7735s_send_command(RAMWR);
    DC_Set();
    CS_Clear();
    for(uint8_t row_idx = 0; row_idx < char_height; row_idx++)
    {
        bit_mask = 0b10000000;
        do
        {
            if( ( fontset_sz_10[char_idx]->data[row_idx] ) & bit_mask )
            {
                Send_lower_Byte(bg_color);
                Buisy_Wait();
                Send_upper_Byte(bg_color);
                Buisy_Wait();
            }
            else
            {
                Send_lower_Byte(font_color);
                Buisy_Wait();
                Send_upper_Byte(font_color);
                Buisy_Wait();                
            }
            bit_mask >>= 1;
        }
        while(bit_mask != 1);
    }
    CS_Set();
    txt_x_pos += char_width ;
}

void draw_char_transp(uint8_t curr_x_pos, uint8_t curr_y_pos, const char* ch, uint16_t font_color)
{
    char_idx = *ch - 'A';
    uint8_t char_width = fontset_sz_10[char_idx]->width;
    uint8_t char_height = fontset_sz_10[char_idx]->height;
    uint8_t bit_mask;
    uint8_t pxl_y_pos = curr_y_pos;
    for(uint8_t row_idx = 0; row_idx < char_height; row_idx++)
    {
        uint8_t pxl_x_pos = curr_x_pos;
        bit_mask = 0b10000000;
        do
        {
            if( ( fontset_sz_10[char_idx]->data[row_idx] ) & bit_mask )
            {
                pxl_x_pos++;
            }
            else
            {
                draw_pixel(pxl_x_pos, pxl_y_pos, font_color);
                pxl_x_pos++;
            }
            bit_mask >>= 1;
        }
        while(bit_mask != 1);
        pxl_y_pos++;
    }
    txt_x_pos += char_width ;
}

void draw_string(uint8_t XS, uint8_t YS, const char* text, uint16_t bg_color, uint16_t font_color, uint8_t transp_bit)
{
    txt_x_pos = XS;
    txt_y_pos = YS;
    while(*text)
    {       
        if(transp_bit == 1)
        {
            draw_char_transp(txt_x_pos, txt_y_pos, text, font_color);
        }
        else if(transp_bit == 0)
        {
            draw_char(txt_x_pos, txt_y_pos, text, bg_color, font_color);
        }
        text++; 
    }
}

