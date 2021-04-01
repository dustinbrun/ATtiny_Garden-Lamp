/*
   ATtiny 13 WS2812B-LED Fire-Effect Garden Lamp
   Author: dustinbrun
           licensed under CC BY 4.0

   Version 03.2021


   Make sure to Set in the Board Settings:
        Processor-Speed to 9.6 Mhz
        Millis, Tone Support to "No Millis, No Tone"
   After that Press "Burn Bootloader" to make sure that these Settings are applied


   ----------------------------- !!!! Configuration can be done in the "config.h file !!!! -----------------------------------------

*/

#include "light_ws2812.c"
#include "light_ws2812.h"
#include "random_avr.h"
#include "random_avr.c"
#include "config.h"


bool on = true;
bool was_on = true;
volatile unsigned long counter = 0;// interrupt needs volatile variable

struct pix
{
  uint8_t g;
  uint8_t r;
  uint8_t b;
};
pix pixel[PIXEL_NUM];


ISR(TIMER0_OVF_vect) {
  /*
     Timer Configuration:
     Prescaler 1024, CPU-Speed 9,6MHz = 9600000 Hz

     Interrupt is called with a Frequency of: 9600000Hz/1024/256 = 36,6Hz
     so every --> 0,027s <---

  */
  counter++;
}


void setup()
{

  random_init(0xabcd); // initialize 16 bit seed
  pinMode(LDR_pin, INPUT);
  pinMode(2, OUTPUT);

  //Interrupt Setup
  cli();  // Clear interrupts, just to make sure
  TCCR0B |= (1 << CS02) | (1 << CS00); // set prescale timer to 1/1024th, set CS02 and CS00 bit in TCCR0B
  TIMSK0 |= 1 << TOIE0; // enable timer overflow interrupt, left shift 1 to TOIE0 and OR with TIMSK
  sei(); //start timer

}

void loop()
{

  if (analogRead(LDR_pin) < on_val && !was_on)
  {
    on = true;
    was_on = true;
    counter = 0;
  }

  if (analogRead(LDR_pin) > off_val && was_on)
  {
    on = false;
    was_on = false;
    counter = 0;

    for (int i = 0; i < PIXEL_NUM; i++)
    {
      pixel[i].r = day_red;
      pixel[i].g = day_green;
      pixel[i].b = day_blue;
    }
    ws2812_setleds((struct cRGB *)pixel, PIXEL_NUM);
  }

  if (counter > max_on_time && on)
  {
    on = false;
    counter = 0;

    for (int i = 0; i < PIXEL_NUM; i++)
    {
      pixel[i].r = timeout_red;
      pixel[i].g = timeout_green;
      pixel[i].b = timeout_blue;
    }
    ws2812_setleds((struct cRGB *)pixel, PIXEL_NUM);
  }


  if (on)
  {

    //  Flicker, based on our initial RGB values
    int flicker = random_avr() % indensity;
    int f_red = red - flicker;
    int f_green = green - flicker;
    int f_blue = blue - flicker;
    if (f_red < 0) f_red = 0;
    if (f_green < 0) f_green = 0;
    if (f_blue < 0) f_blue = 0;

    for (int i = 0; i < PIXEL_NUM; i++)
    {
      pixel[i].r = f_red;
      pixel[i].g = f_green;
      pixel[i].b = f_blue;
    }
    ws2812_setleds((struct cRGB *)pixel, PIXEL_NUM);

    delay(350 - random_avr() % d_delay);
  }
  else
  {
    counter = 0;
  }

}
