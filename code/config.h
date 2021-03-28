/*
 * ----------------------------------------
 * ------ Configuration Options -----------
 * ----------------------------------------
 */



int on_val = 400; //LDR Value below that to switch the Light on
int off_val = 500;  //LDR Value above that to switch the Light off
unsigned long max_on_time = 666666;  // Calculation: ('on_time_in_minutes' * 60) / 0.027
                                  //Example: 5h (=300min) ON-time: max_on_time = (300 * 60) / 0.027 = 666666
#define PIXEL_NUM 3 //Ammount of WS2812 LEDs

/*
 * ----------------------------------------
 * ---------- Colour Settings -------------
 * ----------------------------------------
 */

//----------- Flickering Effect -----------
//Default Colours
int red = 255;
int green = 70;
int blue = 20;

//  Purple flame:
    //  int red = 158, green = 8, blue = 148;
//  Green flame:
    //int red = 74, green = 150, blue = 12;

int indensity = 40; // Maximum Flickering offset
int d_delay = 300; // Maximum Delay offset


// ----- colour after timeout ----
// This is the Colour with which the leds light up, after the timeout (max_on_time) is reached until it gets light again
// If you want it to be off, set all values to 0
int timeout_red = 0;
int timeout_green = 0;
int timeout_blue = 5;


// ------ color throughout the day -------
// This is the Colour with which the leds light up, when the LDR detects daylight
int day_red = 0;
int day_green = 0;
int day_blue = 0;




/*
 * ----------------------------------------
 * ---------------- Pins ------------------
 * ----------------------------------------
 */
 
#define LDR_pin A3
// Pin Defintion for LEDs in the light_ws2812.h File as "ws2812_pin" variable


/*
 * ----------------------------------------
 * ---------- End of config ---------------
 * ----------------------------------------
 */
