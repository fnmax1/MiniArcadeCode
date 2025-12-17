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
#include "gfx.h"

//define font set dimensions
#define CHAR_COUNT      95
#define FONT_COUNT      2

//Global variables
extern uint8_t txt_x_pos;
extern uint8_t txt_y_pos;
extern uint8_t char_idx;

//enum for various font sizes
typedef enum
{
    SIZE_10,        //  0
    SIZE_14         //  1
} fontsize;

//struct for a character's image data
typedef struct 
{
    const uint8_t *data;
    uint8_t width;
    uint8_t height;
} char_t;

//array with pointers to the different font sizes and the corresponding image data
extern const char_t* fontset[FONT_COUNT][CHAR_COUNT];

/**
 * @desc    The function draws the passed char 
 *          and increments the text position.
 *
 * @param   uint8_t curr_x_pos      ->  x start position of the char      
 * @param   uint8_t curr_y_pos      ->  y start position of the char
 * @param   const char* ch          ->  char to be drawn
 * @param   uint16_t bg_color       ->  backround color 
 * @param   uint16_t font_color     ->  font color 
 * @param   fontsize font_size      ->  font size
 * 
 * @return  void
 */
void draw_char(uint8_t curr_x_pos, uint8_t curr_y_pos, const char* ch, uint16_t bg_color, uint16_t font_color, fontsize font_size);

/**
 * @desc    The function draws the passed char 
 *          and increments the text position.
 *          It only draws the pixels of the character, not the background.
 *
 * @param   uint8_t curr_x_pos      ->  x start position of the char      
 * @param   uint8_t curr_y_pos      ->  y start position of the char
 * @param   const char* ch          ->  char to be drawn
 * @param   uint16_t font_color     ->  font color 
 * @param   fontsize font_size      ->  font size
 * 
 * @return  void
 */
void draw_char_transp(uint8_t curr_x_pos, uint8_t curr_y_pos, const char* ch, uint16_t font_color, fontsize font_size);

/**
 * @desc    The function draws the passed string starting 
 *          at the X and Y start position. 
 *          The transparency bit determines whether the string is drawn
 *          transparent ore not.
 *          transp_bit = 1  -> transparent text 
 *          transp_bit = 0  -> non transparent text
 *  
 * @param   uint8_t XS              ->  x start position of the text      
 * @param   uint8_t YS              ->  y start position of the text
 * @param   const char* text        ->  pointer to the text to be drawn
 * @param   uint16_t bg_color       ->  backround color 
 * @param   uint16_t font_color     ->  font color 
 * @param   uint8_t transp_bit      ->  transparency bit
 * @param   fontsize font_size      ->  font size
 * 
 * @return  void
 */
void draw_string(uint8_t XS, uint8_t YS, const char* text, uint16_t bg_color, uint16_t font_color, uint8_t transp_bit, fontsize font_size);

#endif	/* FONT_H */

