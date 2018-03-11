//
//  FSM.h
//  
//
//
//
#ifndef FSM_h
#define FSM_h
#include "elev.h"
#include <stdbool.h>




typedef enum states {
	emergency_stop,
    stop_door_open,
	drive,
	stop
} State;


//knappetyper
typedef enum tag_button_type {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_COM
}button_type;

//----------------------------------------
void initialize_state();
void set_state(State st);
void initialize_is_emergency_outside_floor();
bool get_is_emergency_outside_floor();
void set_is_emergency_outside_floor(bool set);
//----------------------------------------
//stopp umiddelbart, tøm kø, eventuelt åpne dør. Ikke ta i mot bestilling mens stoppknapp er trykket.
void event_emergency_stop_pushed();
//legge til bestilling etter knappetrykk
void event_button_pushed(int floor, button_type button);
//stå stille om køen er tom, lukk døra dersom den skal lukkes
void event_queue_is_empty();
//Køen er ikke tom. Håndterer dette avhengig av staten den er i
void event_queue_not_empty(elev_motor_direction_t current_direction);
//Nådd etasje som skal stoppes i. Stopper heisen
void event_reached_floor_to_stop_in();
//Starter counter og åpner døra
void event_stop_door_open();


#endif /* FSM_h */
