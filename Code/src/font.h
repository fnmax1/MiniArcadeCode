/* 
 * File:   font.h
 * Author: fneum
 *
 * Created on 9. Dezember 2025, 12:58
 */

#ifndef FONT_H
#define	FONT_H

#include <stdint.h>
#include "st7735s.h"

extern uint8_t txt_x_pos;
extern uint8_t txt_y_pos;
extern uint8_t char_idx;

typedef struct 
{
    const uint8_t *data;
    uint8_t width;
    uint8_t height;
} char_t;

extern const char_t* fontset_sz_10[3];

void draw_char(uint8_t curr_x_pos, uint8_t curr_y_pos);

//void draw_char(uint8_t curr_x_pos, uint8_t curr_y_pos, const char* ch);

//void draw_string(uint8_t XS, uint8_t YS, const char* text);

#endif	/* FONT_H */

