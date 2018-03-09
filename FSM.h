//
//  FSM.h
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//
//#pragma once
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
void initialize_is_emergency_outside_floor();
bool get_is_emergency_outside_floor();
void set_is_emergency_outside_floor(bool set);
//----------------------------------------
void event_emergency_stop_pushed();
void event_button_pushed(int floor, button_type button);
void event_queue_is_empty();
void event_queue_not_empty(elev_motor_direction_t current_direction);
void event_reached_floor();
void event_stop_door_open();
//----------------------------------------
void z_drive(elev_motor_direction_t current_direction);
void z_stop();
//----------------------------------------
//oppdaterer etasjelys og returnerer ny floor
//forutsetter at current_floor!=-1
int update_floor_and_light(int current_floor);

#endif /* FSM_h */
