//
//  FSM.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#include "FSM.h"
static int previous_floor;
static  State state;

void initialize_state() {
	state = stop;
}

void event_emergency_stop_pushed() {

	elev_set_motor_direction(DIRN_STOP);
	empty_queue();
	if (elev_get_floor_sensor_signal() >= 0) {
		event_stop_door_open();
	}
	state = emergency_stop;
}

void event_button_pushed(int floor, button_type button) {

	switch (state) {

	case (emergency_stop):
		break;
	case(stop):
	case(drive):
		add_to_queue(floor, button);
		break;
	}
}

void event_queue_is_empty() {
	elev_set_motor_direction(DIRN_STOP);
	state = stop;
}

void z_drive(elev_motor_direction_t current_direction){
		//vi trenger en funksjon get_direction() 
		elev_set_motor_direction(current_direction);
		state = drive;
}

void z_stop(){
	elev_set_motor_direction(DIRN_STOP);
	state = stop;
}	

void event_queue_not_empty(elev_motor_direction_t current_direction) {
	switch (state) {
	case (emergency_stop):
		break;
	case (drive):
		/*if (reached_floor_to_stop_in()) {
			z_stop();
			event_stop_door_open();
		}*/
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
			event_stop_door_open();
			//slett bestilling: --> da vil den kjøre videre
			remove_from_queue(elev_get_floor_sensor_signal());
			break;
	}
}

void event_stop_door_open() {
	//Hold døra åpen i 3 sek
	//dette går ikke
	elev_set_door_open_lamp(1);
	sleep(3);
	elev_set_door_open_lamp(0);
	//state = stop;
}

//------------------------------------------------------------------
