//
//  FSM.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#include "FSM.h"
#include "timer.h"
#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "queue.h"
#include "lamps.h"
static  State state;
static bool is_emergency_outside_floor;

void initialize_state() {
	state = stop;
}

void initialize_is_emergency_outside_floor(){
	is_emergency_outside_floor=false;
}

bool get_is_emergency_outside_floor(){
	return is_emergency_outside_floor;
}

void set_is_emergency_outside_floor(bool set){
	is_emergency_outside_floor = set;
}

void event_emergency_stop_pushed() {
    state = emergency_stop;
    elev_set_motor_direction(DIRN_STOP);
    //EGEN FUNK????
    elev_set_stop_lamp(1);
    turn_off_all_button_lights();

    if (elev_get_floor_sensor_signal() >= 0) {
    	elev_set_door_open_lamp(1);
    }

    while(elev_get_stop_signal() == 1){}
    elev_set_stop_lamp(0);
    empty_queue();

    if (elev_get_floor_sensor_signal() >= 0) {
        event_stop_door_open();
        state = stop_door_open;
    }
    else{
        state = stop;
        set_is_emergency_outside_floor(true);
    }
}

void event_button_pushed(int floor, button_type button) {
    switch (state) {
        case (emergency_stop):
            break;
        /*case (stop_door_open):
        case(stop):
        case(drive):*/
        default:
        	turn_button_lamp_on(floor,button);
            add_to_queue(floor, button);
            break;
    }
}
void event_queue_is_empty() {
    switch (state) {
        case (emergency_stop):
            break;
        case (stop_door_open):
            if (seccounter() >= 3){
                elev_set_door_open_lamp(0);
                state = stop;
            }
           
            break;
        /*case (drive):
        case (stop):*/
        default:
            break;
    }
}


void event_queue_not_empty(elev_motor_direction_t current_direction) {
    switch (state) {
        case (emergency_stop):
            break;
        case (stop_door_open):
            if ( seccounter() >= 3){
                elev_set_door_open_lamp(0);
                state = stop;
            }
            break;
        case (drive):
            break;
        case (stop):
            z_drive(current_direction);
            break;
    }
}

void event_reached_floor() {
    switch(state){
        case(emergency_stop):
            break;
        case(drive):
        case(stop):
            z_stop();
        case(stop_door_open):
            event_stop_door_open();
            turn_button_lamps_off(elev_get_floor_sensor_signal());
            remove_from_queue(elev_get_floor_sensor_signal());
            state = stop_door_open;
            break;
    }
}

void event_stop_door_open() {
    //Åper døra og starter counter
    seccounter();
    elev_set_door_open_lamp(1);

}

void z_drive(elev_motor_direction_t current_direction){
		//vi trenger en funksjon get_direction() 
		elev_set_motor_direction(current_direction);
		state = drive;
}

void z_stop(){
	elev_set_motor_direction(DIRN_STOP);
}


int update_floor_and_light(int current_floor){
	//EGEN FUNK????
	elev_set_floor_indicator(current_floor);
	return current_floor;
}
