//
//  handling.c
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

#include "handling.h"


elev_motor_direction_t get_direction(int floor_in, int floor_to) {}


bool reached_floor_to_stop_in(elev_motor_direction_t current_direction) {
	//is_order(button_type button, int floor);

	int current_floor = elev_get_floor_sensor_signal();
	//dersom kø er tom eller commandknapp trykket, bryr vi oss ikke om retning:
	//ikke i etasje:
	if (current_floor == -1) {//dobbeltsjekk -1
		return false;
	}
	//BUTTON_COMMAND
	if (is_order(BUTTON_COM, current_floor)) {
		return true;
	}
	//BUTTON_UP og BUTTON_DOWN:
	//her bryr vi oss om retning til heisen.
	if (is_order(BUTTON_DOWN, current_floor) && current_direction == DIRN_DOWN) {
		return true;
	}
	if (is_order(BUTTON_UP, current_floor) && current_direction == DIRN_UP) {
		return true;
	}
	else {
		return false;
	}

}
