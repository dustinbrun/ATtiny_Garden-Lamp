/*
   light_ws2812_config.h

   v2.4 - Nov 27, 2016

   User Configuration file for the light_ws2812_lib

*/

///////////////////////////////////////////////////////////////////////
// Define I/O pin
///////////////////////////////////////////////////////////////////////

#define ws2812_port B // Data port
#define ws2812_pin 0  // Data out pin

///////////////////////////////////////////////////////////////////////
// Define Reset time in µs.
//
// This is the time the library spends waiting after writing the data.
//
// WS2813 needs 300 µs reset time
// WS2812 and clones only need 50 µs <<<-----
//
///////////////////////////////////////////////////////////////////////

#define ws2812_resettime 50





// -------------------------------------------------------------------------------------------------------------

/* WS2812_CONFIG_H_ 
 * light weight WS2812 lib include
 *
 * Version 2.3  - Nev 29th 2015
 * Author: Tim (cpldcpu@gmail.com) 
 *
 * Please do not change this file!"
 *
 * License: GNU GPL v2+ (see License.txt)
 *
 */ 

#ifndef LIGHT_WS2812_H_
#define LIGHT_WS2812_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/*
 *  Structure of the LED array
 *
 * cRGB:     RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 * cRGBW:    RGBW for SK6812RGBW
 */

struct cRGB  { uint8_t g; uint8_t r; uint8_t b; };
struct cRGBW { uint8_t g; uint8_t r; uint8_t b; uint8_t w;};



/* User Interface
 * 
 * Input:
 *         ledarray:           An array of GRB data describing the LED colors
 *         number_of_leds:     The number of LEDs to write
 *         pinmask (optional): Bitmask describing the output bin. e.g. _BV(PB0)
 *
 * The functions will perform the following actions:
 *         - Set the data-out pin as output
 *         - Send out the LED data 
 *         - Wait 50µs to reset the LEDs
 */

void ws2812_setleds     (struct cRGB  *ledarray, uint16_t number_of_leds);
void ws2812_setleds_pin (struct cRGB  *ledarray, uint16_t number_of_leds,uint8_t pinmask);
void ws2812_setleds_rgbw(struct cRGBW *ledarray, uint16_t number_of_leds);

/* 
 * Old interface / Internal functions
 *
 * The functions take a byte-array and send to the data output as WS2812 bitstream.
 * The length is the number of bytes to send - three per LED.
 */

void ws2812_sendarray     (uint8_t *array,uint16_t length);
void ws2812_sendarray_mask(uint8_t *array,uint16_t length, uint8_t pinmask);


/*
 * Internal defines
 */

#define CONCAT(a, b)            a ## b
#define CONCAT_EXP(a, b)   CONCAT(a, b)

#define ws2812_PORTREG  CONCAT_EXP(PORT,ws2812_port)
#define ws2812_DDRREG   CONCAT_EXP(DDR,ws2812_port)

#endif /* LIGHT_WS2812_H_ */
