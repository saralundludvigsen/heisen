//
//  handling.c
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

#include "handling.h"
#include "FSM.h"


bool reached_floor_to_stop_in(elev_motor_direction_t current_direction) {
	//if (current_direction == DIRN_UP) {
	//	printf(" OPP ");
	//}
	//if (current_direction == DIRN_DOWN) {
	//	printf(" NED ");
	//}
	//if (current_direction == DIRN_STOP) {
	//	printf(" STOPP ");
	//}
	int current_floor = elev_get_floor_sensor_signal();
	//ikke i etasje, ekstra sikkerhet
	if (current_floor == -1) {
		return false;
	}
	//BUTTON_COMMAND trykket: bryr oss ikke om retning heisen har nå
	else if (is_order(BUTTON_COM, current_floor)) {
		printf("command\n");
		return true;
	}
	//4. etasje + button down:
	else if (current_floor == 3 && is_order(BUTTON_DOWN, 3)) {
		printf("4th floor down\n");
		return true;
	}
	//1. etasje + button up:
	else if (current_floor == 0 && is_order(BUTTON_UP, 0)) {
		printf("1st floor order\n");
		return true;
	}

	//BUTTON_UP og BUTTON_DOWN:
	//her bryr vi oss om retning til heisen.
	else if (is_order(BUTTON_DOWN, current_floor) && current_direction == DIRN_DOWN) {
		printf("DOWN dir and button\n");
		return true;
	}
	else if (is_order(BUTTON_UP, current_floor) && current_direction == DIRN_UP) {
		printf("UP dir and button\n");
		return true;
	}

	else {
		//printf("other\n");
		return false;
	}

}


elev_motor_direction_t get_direction(int prev_floor) {
	//test - uten retning:
	for (int i = prev_floor+1; i < N_FLOORS; i++) {
		//har bestilling til etasje over den den er i
		if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
			return DIRN_UP;
		}
	}
	//else:
	for (int i = 0; i < prev_floor; i++) {
		//har bestilling til etasje under den den er i
		if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
			return DIRN_DOWN;
		}
	}
	return DIRN_STOP;
}
