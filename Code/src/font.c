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

void draw_char(uint8_t curr_x_pos, uint8_t curr_y_pos)
{
    char_idx = 0;
    uint8_t char_width = fontset_sz_10[char_idx]->width;
    uint8_t char_height = fontset_sz_10[char_idx]->height;
    uint8_t bit_mask;
    uint8_t i;
    st7735s_set_window( curr_x_pos, ( curr_x_pos + (char_width + 1) ), curr_y_pos, ( curr_y_pos + (char_height - 1) ) );
    st7735s_send_command(RAMWR);
    DC_Set();
    CS_Clear();
    for(uint8_t row_idx = 0; row_idx < char_height; row_idx++)
    {
        bit_mask = 0b10000000;
        i = 0;
        do
        {
            if( ( fontset_sz_10[char_idx]->data[row_idx] ) & bit_mask )
            {
                Send_lower_Byte(COLOR_WHITE);
                Buisy_Wait();
                Send_upper_Byte(COLOR_WHITE);
                Buisy_Wait();
            }
            else
            {
                Send_lower_Byte(COLOR_BLACK);
                Buisy_Wait();
                Send_upper_Byte(COLOR_BLACK);
                Buisy_Wait();                
            }
            bit_mask >>= 1;
            i++;
        }
        while(i < 7);
        row_idx++;
    }
    CS_Set();
    //txt_x_pos += (char_width + 1);
    //txt_y_pos += (char_height + 1);
}
/*
void draw_char(uint8_t curr_x_pos, uint8_t curr_y_pos, const char* ch)
{
    char_idx = *ch - 'A';
    uint8_t char_width = fontset_sz_10[char_idx]->width;
    uint8_t char_height = fontset_sz_10[char_idx]->height;
    uint8_t bit_mask = 0b10000000; 
    st7735s_set_window( curr_x_pos, (curr_x_pos + char_width) , curr_y_pos, (curr_y_pos + char_height) );
    uint8_t row_idx = 0;
    uint8_t i = 0;
    while(row_idx < char_height)
    {
        do
        {
            
            if( (fontset_sz_10[char_idx]->data[row_idx]) & bit_mask )
            {
                st7735s_send_color(COLOR_WHITE,1);
            }
            else
            {
                st7735s_send_color(COLOR_BLACK,1);
            }
            bit_mask = bit_mask >> 1;
            //draw_line_horizontal(1,127,10 + i,COLOR_BLUE);
            i++;
        }
        while(i < 7);
        row_idx++;
    }
    
    txt_x_pos += (char_width + 1);
    txt_y_pos += (char_height + 1);
}

void draw_string(uint8_t XS, uint8_t YS, const char* text)
{
    txt_x_pos = XS;
    txt_y_pos = YS;
    while(*text)
    {       
        draw_char(txt_x_pos, txt_y_pos, text);
        text++;
        
    }
}

*/