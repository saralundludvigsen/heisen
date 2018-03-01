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


void event_emergency_stop_pushed() {

	elev_set_motor_direction(DIRN_STOP);
	//empty_queue();
	if (elev_get_floor_sensor_signal() >= 0) {
		elev_set_door_open_lamp(1);
	}
	state = emergency_stop;
}

void event_button_pushed(int floor, button_type button) {
	elev_set_motor_direction(DIRN_UP);
	/*switch (state) {

	case (emergency_stop):
		break;
	case(stop):
	case(stop_door_open):
	case (drive):
		add_to_queue(floor, button);
		break;
	}*/
}

void event_queue_is_empty() {
	elev_set_motor_direction(DIRN_STOP);
	state = stop;
}

//SE PÅ DENNE
void event_queue_not_empty() {
	/*switch (state) {
	case (emergency_stop):
		break;
	case (drive):
		if (reached_floor_to_stop_in(direction)) {
			state = stop_door_open;
		}
		break;
	case (stop):
		state = drive;
		break;
	case (stop_door_open):
		break;
	}*/
}

void event_reached_floor() {
	elev_set_motor_direction(DIRN_STOP);
	state = stop_door_open;
}

void event_stop_door_open() {
	//Hold døra åpen i 3 sek
	elev_set_door_open_lamp(1);
	sleep(3);
	elev_set_door_open_lamp(0);
	state = stop;
}

//------------------------------------------------------------------
