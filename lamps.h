#ifndef lamps_h
#define lamps_h
#include "FSM.h"

//when order to floor, turn on light for button
void turn_button_lamp_on(int floor, button_type button);

//when order to floor is handled, turn off all button lights in floor
void turn_button_lamps_off(int floor);

//turn off all button lights
void turn_off_all_button_lights();

#endif