#include "gfx.h"

void draw_line(uint8_t XS, uint8_t YS, uint8_t XE, uint8_t YE, uint16_t color)
{ 
    if( absdiff(XS,XE) > absdiff(YS,YE) )
    {
        int swap;
        if( XS > XE )
        {
            swap = XS;
            XS = XE;
            XE = swap;
            swap = YS;
            YS = YE;
            YE = swap;      
        }


        int dx = XE - XS;
        int dy = YE - YS;
        int dir;

        if( dy > 0)
        {
            dir = 1;
        }
        else
        {
            dir = -1;
        }

        dy *= dir;

        if( dx == 0)
        {
            exit(ST7735S_ERROR);
        }
        else
        {   
            int y = YS;
            int p = 2*dy - dx;
            for(int a = 0; a <= dx; a++)
            {
                draw_pixel( XS + a, y, color);
                if( p >= 0 )
                {
                    y += dir;
                    p = p - 2*dx;
                }
                p = p + 2*dy;
            }
        }
    }
    else
    {
        int swap;
        if( YS > YE )
        {
            swap = XS;
            XS = XE;
            XE = swap;
            swap = YS;
            YS = YE;
            YE = swap;      
        }

        int dx = XE - XS;
        int dy = YE - YS;
        int dir;

        if( dx > 0)
        {
            dir = 1;
        }
        else
        {
            dir = -1;
        }

        dx *= dir;

        if( dy == 0)
        {
            exit(ST7735S_ERROR);
        }
        else
        {   
            int x = XS;
            int p = 2*dx - dy;
            for(int a = 0; a <= dy; a++)
            {
                draw_pixel( x, YS + a, color);
                if( p >= 0 )
                {
                    x += dir;
                    p = p - 2*dy;
                }
                p = p + 2*dx;
            }
        } 
    }
    
}

void draw_line_horizontal(uint8_t XS, uint8_t XE, uint8_t ROW, uint16_t color)
{
    XS = XS + COL_OFFSET;
    XE = XE + COL_OFFSET;
    st7735s_set_window(XS, XE, ROW, ROW);
    st7735s_send_color(color, (XE - XS) + 1 );
}

void draw_line_vertical(uint8_t YS, uint8_t YE, uint8_t COL, uint16_t color)
{
    COL = COL + COL_OFFSET;
    st7735s_set_window(COL, COL, YS, YE);
    st7735s_send_color(color, (YE - YS) + 1 );
}

void draw_rectangle(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE, uint16_t color)
{
    draw_line_horizontal(XS, XE, YS, color);
    draw_line_horizontal(XS, XE, YE, color);
    draw_line_vertical(YS, YE, XS, color);
    draw_line_vertical(YS, YE, XE, color);
}

void fill_rectangle_partial(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE, uint8_t lw, uint16_t color)
{
    for(int a = 0; a < lw; a++)
    {
        draw_rectangle(XS + a, XE - a, YS + a, YE - a, color);
    }
}

void fill_rectangle(uint8_t XS, uint8_t XE, uint8_t YS, uint8_t YE, uint16_t color)
{
    XS = XS + COL_OFFSET;
    XE = XE + COL_OFFSET;
    st7735s_set_window(XS, XE, YS, YE);
    uint16_t sizeRect = ( (XE - XS) + 1 ) * ( (YE - YS) + 1 );
    st7735s_send_color(color,sizeRect);
}

void fill_display(uint16_t color)
{
    st7735s_set_window( COL_ADR_START, COL_ADR_END, ROW_ADR_START, ROW_ADR_END);
    st7735s_send_color(color, MEMORY_SIZE_LCD);
}

void draw_circle(uint8_t CX, uint8_t CY, uint8_t R, uint16_t color)
{
    uint8_t X = 0;
    uint8_t Y = R;
    int P = R;
 
    while(X < Y)
    {
        if (P > 0)
        {
            Y--;
            P += 2*(X - Y) - 1;
        }
        else
        {
            P += 2*X + 1;
        }
        //first octant
        draw_pixel(CX - X, CY + Y, color);
        //second octant
        draw_pixel(CX - Y, CY + X, color);
        //third octant
        draw_pixel(CX - Y, CY - X, color);
        //fourth octant
        draw_pixel(CX - X, CY - Y, color);
        //fith octant
        draw_pixel(CX + X, CY - Y, color);
        //sixth octant
        draw_pixel(CX + Y, CY - X, color);
        //seventh octant
        draw_pixel(CX + Y, CY + X, color);
        //eigtht octant
        draw_pixel(CX + X, CY + Y, color);       
        X++;
    }
}

void fill_circle(uint8_t CX, uint8_t CY, uint8_t R, uint16_t color)
{
    uint8_t X = 0;
    uint8_t Y = R;
    int P = R;
 
    while(X < Y)
    {
        if (P > 0)
        {
            Y--;
            P += 2*(X - Y) - 1;
        }
        else
        {
            P += 2*X + 1;
        }
        
        draw_line_horizontal(CX - X, CX + X, CY + Y, color);
        draw_line_horizontal(CX - X, CX + X, CY - Y, color);
        draw_line_horizontal(CX - Y, CX + Y, CY + X, color);
        draw_line_horizontal(CX - Y, CX + Y, CY - X, color);
           
        X++;
    }
}

void ERTFT144_demo(void)
{
    //fill display demo
    fill_display(COLOR_RED);
    delay_ms(2000);
    fill_display(COLOR_BLUE);
    delay_ms(2000);
    fill_display(COLOR_GREEN);
    delay_ms(2000);
    fill_display(COLOR_WHITE);
    delay_ms(3000);
    //draw line demo
    for(int a = 10; a <= 120; a += 10)
    {
        draw_line_horizontal(1, 128, a, COLOR_BLUE);
        delay_ms(250);
    }
    for(int a = 10; a <= 120; a += 10)
    {
        draw_line_vertical(1, 128, a, COLOR_RED);
        delay_ms(250);
    }
    delay_ms(2000);
    //draw rectangle demo
    fill_display(COLOR_WHITE);
    delay_ms(1000);
    draw_rectangle(100,120,100,120,COLOR_RED);
    delay_ms(500);
    fill_rectangle(10,50,10,50,COLOR_GREEN);
    delay_ms(500);
    fill_rectangle_partial(70,90,70,90,5,COLOR_BLUE);
    delay_ms(3000);
    //draw circle demo
    fill_display(COLOR_WHITE);
    draw_circle(64,64,20,COLOR_RED);
    delay_ms(500);
    fill_circle(100,100,20,COLOR_BLUE);
    delay_ms(3000);
}