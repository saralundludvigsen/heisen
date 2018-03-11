//
//  FSM.c
//  
//
//
//

#include "FSM.h"
#include "timer.h"
#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "queue.h"
#include "lamps.h"
#include "handling.h"


static  State state;
static bool is_emergency_outside_floor;

//----------------------------------------

void initialize_state() {
	state = stop;
}

void set_state(State st){
    state = st;
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

//--------------------------------------------

void event_emergency_stop_pushed() {
    state = emergency_stop;
    elev_set_motor_direction(DIRN_STOP);
    elev_set_stop_lamp(1);
    turn_off_all_button_lights();

    
    if (elev_get_floor_sensor_signal() >= 0) { //hvis i etasje,
    	elev_set_door_open_lamp(1); //åpne dør,
    }
    while(elev_get_stop_signal() == 1){} //så lenge stoppknapp er trykket.
    

    elev_set_stop_lamp(0); //slukk stoppknapplys
    empty_queue();

   
    if (elev_get_floor_sensor_signal() >= 0) {//hvis i etasje, 
        event_stop_door_open(); //hold dør åpen og start timer for lukking
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
        default: //states stop_door_open, stop, drive
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
            if (seccounter() >= 3){ //hvis timer over 3 sek,
                elev_set_door_open_lamp(0); //lukk døra
                state = stop;
            }
            //else: hvis døra allere er åpen timeren ikke er gått ut,
            //gjør den ingen ting
            break;
        default: //states drive, stop:
            break;
    }
}


void event_queue_not_empty(elev_motor_direction_t current_direction) {
    switch (state) {
        case (emergency_stop):
            break;
        case (stop_door_open):
            if ( seccounter() >= 3){ //hvis timer over 3 sek,
                elev_set_door_open_lamp(0); //lukk døra
                state = stop;
            }
            //else: hvis døra allere er åpen timeren ikke er gått ut,
            //gjør den ingen ting
            break;
        case (drive):
            //ikke gjør noe, heisen kjører allerede
            break;
        case (stop):
            set_drive(current_direction);
            break;
    }
}

void event_reached_floor_to_stop_in() {
    switch(state){
        case(emergency_stop):
            break;
        case(drive):
        case(stop):
            set_stop();
            //continue
        case(stop_door_open):
            event_stop_door_open();
            turn_button_lamps_off(elev_get_floor_sensor_signal());
            remove_from_queue(elev_get_floor_sensor_signal());
            state = stop_door_open;
            break;
    }
}

void event_stop_door_open() {
    seccounter();
    elev_set_door_open_lamp(1);

}


