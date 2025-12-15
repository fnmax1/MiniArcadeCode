/* 
 * File:   symbols.h
 * Author: fneum
 *
 * Created on 28. November 2025, 14:40
 */

#ifndef SYMBOLS_H
#define	SYMBOLS_H

#include <stdint.h>

typedef struct 
    {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
    } tImage;
    
extern const tImage Pacman_Ghost;

#endif	/* SYMBOLS_H */

