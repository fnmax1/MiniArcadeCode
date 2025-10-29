/* 
 * File:    gfx.h
 * 
 * Author:  Felix Neumann
 * 
 * @desc    This library implements graphics functions that can be used
 *          to display symbols and geometries on the ER-TFT144-1 LCD. 
 *          To do this, the library uses functions from st7735s.h
 *          to communicate with the display driver. 
 *          The library can also be used for other LCDs. To do this, 
 *          simply replace the functions from st7735s.h with your own. 
 *       
 * @Hw      LCD-Driver      ->      ST7735S
 *          LCD             ->      ER-TFT144-1
 *          Microcontroller ->      SAMD21J18A
 * 
 * Created on 27. September 2025, 17:57
 */

#ifndef GFX_H
#define	GFX_H

#include "st7735s.h"
#include "definitions.h"  
#include <stdint.h>

/**
 * @desc    draw a pixel  
 *
 * @param   uint8_t X       ->  X-Position
 * @param   uint8_t Y       ->  Y-Position
 * @param   uint16_t color  ->  color           
 *
 * @return  void
 */
inline void draw_pixel(uint8_t X, uint8_t Y, uint16_t color)
{
    X = X + COL_OFFSET;
    st7735s_set_window( X, X, Y, Y);
    st7735s_send_color(color, 1);
}

/**
 * @desc    This function determines the absolute difference between
 *          two coordinates.
 *          It is only used in the draw_line function to determin if the 
 *          desired line has an angle greater then 45° ore less.
 *
 * @param   uint8_t start   ->  start coordinate
 * @param   uint8_t end     ->  end coordinate          
 *
 * @return  absolute value of (start - end) 
 */
uint8_t static inline absdiff(uint8_t start, uint8_t end)
{
    if(start > end)
    {
        return start - end;
    }
    else
    {
        return end - start;
    }
}

/**
 * @desc    draw a line using Bressenham's Algorithm
 *          This function draws a line from coordinate (XS|YS)
 *          to coordinate (XE|YE).
 *          The function uses the Bressenham algorithm for this purpose.
 *          If purely horizontal or vertical lines are to be drawn, 
 *          the functions provided for this purpose should be used. 
 *          These require significantly less computing power.
 * 
 * @param   uint8_t XS      ->  x coordinate of the starting point
 * @param   uint8_t YS      ->  y coordinate of the starting point
 * @param   uint8_t XE      ->  x coordinate of the endpoint
 * @param   uint8_t YE      ->  y coordinate of the endpoint
 * @param   uint16_t color      
 *
 * @return  void
 */
void draw_line(uint8_t XS, uint8_t YS, uint8_t XE, uint8_t YE, uint16_t color);

/**
 * @desc    draw a horizontal line
 *
 * @param   uint8_t XS      ->  start of the line
 * @param   uint8_t XE      ->  end of the line
 * @param   uint8_t ROW     ->  row in which the line is drawn
 *
 * @return  void
 */
void draw_line_horizontal(uint8_t XS, uint8_t XE, uint8_t ROW, uint16_t color);

/**
 * @desc    draw a vertical line
 *
 * @param   uint8_t YS      ->  start of the line
 * @param   uint8_t YE      ->  end of the line
 * @param   uint8_t COL     ->  column in which the line is drawn
 *
 * @return  void
 */
void draw_line_vertical(uint8_t YS, uint8_t YE, uint8_t COL, uint16_t color);

/**
 * @desc    draw a rectangle
 *
 * @param   uint8_t XS      ->  x start position 
 * @param   uint8_t XE      ->  x end position 
 * @param   uint8_t YS      ->  y start position
 * @param   uint8_t YE      ->  y end position
 * @param   uint16_t color
 *
 * @return  void
 */
void draw_rectangle(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE, uint16_t color);

/**
 * @desc    draw a rectangle with a certain linewidth
 *
 * @param   uint8_t XS      ->  x start position 
 * @param   uint8_t XE      ->  x end position 
 * @param   uint8_t YS      ->  y start position
 * @param   uint8_t YE      ->  y end position
 * @param   uint8_t lw      ->  linewidth
 * @param   uint16_t color      
 *
 * @return  void
 */
void fill_rectangle_partial(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE, uint8_t lw, uint16_t color);

/**
 * @desc    fill rectangle
 *
 * @param   uint8_t XS      ->  x start position 
 * @param   uint8_t XE      ->  x end position 
 * @param   uint8_t YS      ->  y start position
 * @param   uint8_t YE      ->  y end position
 * @param   uint16_t color      
 *
 * @return  void
 */
void fill_rectangle(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE, uint16_t color);

/**
 * @desc    fill display 
 *
 * @param   uint16_t color      
 *
 * @return  void
 */
void fill_display(uint16_t color);

/**
 * @desc    draw a circle using the midpoint circle algorithm
 *
 * @param   uint8_t CX      ->  x-cooridnate circle center 
 * @param   uint8_t CY      ->  y-coordinate circle center
 * @param   uint8_t R       ->  radius of the circle
 * @param   uint16_t color      
 *
 * @return  void
 */
void draw_circle(uint8_t CX, uint8_t CY, uint8_t R, uint16_t color);

/**
 * @desc    fill a circle using the midpoint circle algorithm
 *
 * @param   uint8_t CX      ->  x-cooridnate circle center 
 * @param   uint8_t CY      ->  y-coordinate circle center
 * @param   uint8_t R       ->  radius of the circle
 * @param   uint16_t color      
 *
 * @return  void
 */
void fill_circle(uint8_t CX, uint8_t CY, uint8_t R, uint16_t color);

/**161
 * @desc    demo of the graphics functions implemented on the ERTFT144
 *
 * @param   void   
 *
 * @return  void
 */
void ERTFT144_demo(void);

#endif	/* GFX_H */

