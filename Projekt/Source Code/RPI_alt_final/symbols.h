/*****************************************************************************
*
* File                : symbols.h
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : Anette Olesen Lihn
*
******************************************************************************/

#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

/************* Return symbol *************/
/*************** 8x5 pixels **************/
static const uint8_t symbol_return[5] =
{ 0x22, 0x42, 0xFE, 0x40, 0x20 };

static const uint8_t symbol_return_inv[5] =
{ 0xDD, 0xBD, 0x01, 0xBF, 0xDF };

#endif