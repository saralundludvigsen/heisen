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

	int current_floor = elev_get_floor_sensor_signal();
	//ikke i etasje:
	if (current_floor == -1) {//dobbeltsjekk -1
		return false;
	}
	//BUTTON_COMMAND trykket: bryr oss ikke om retning heisen har nå
	if (is_order(BUTTON_COM, current_floor)) {
		printf("command anyways");
		return true;
	}
	//4 etasje: //trenger ikke pga den under?
	if (current_floor == 3 && is_order(BUTTON_DOWN, 3)) {
		printf("4th floor order\n");
		return true;
	}

	//BUTTON_UP og BUTTON_DOWN:
	//her bryr vi oss om retning til heisen.
	if (is_order(BUTTON_DOWN, current_floor) && current_direction == DIRN_DOWN) {
		printf("on the way down\n");
		return true;
	}
	if (is_order(BUTTON_UP, current_floor) && current_direction == DIRN_UP) {
		printf("goin up\n");
		return true;
	}

	//dersom den kjører OPP og denne bestillingen er den ØVERSTE (og ned, de andre tar seg av resten): return true
	if ((current_direction == DIRN_UP) && (current_floor < 3) && is_order(BUTTON_DOWN, current_floor)) {
		bool isOrderAbove = false;
		for (int i = current_floor + 1; i < N_FLOORS; i++) {
			for (button_type button = BUTTON_DOWN; button <= BUTTON_COM; button++) {
				if (is_order(button, i)) {
					isOrderAbove = true;

				}
			}
			if (isOrderAbove) {
				return false;
			}
			else if (!isOrderAbove) {
				printf("no orders above\n");
				return true;
			}
		}
		//if (current_direction == DIRN_DOWN){}
	}
	else {
		return false;
	}

}
/*
elev_motor_direction_t get_direction(int floor_in, int floor_to) {
	if (floor_in < floor_to) {
		return DIRN_UP;
	}
	else if (floor_in > floor_to) {
		return DIRN_DOWN;
	}
	else {
		return DIRN_STOP;
	}
}*/

elev_motor_direction_t get_direction(int prev_floor, elev_motor_direction_t curr_dir) {
	//test - uten retning:
	for (int i = prev_floor; i < N_FLOORS; i++) {
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



	/*if (curr_dir == DIRN_UP) {
		for (int i = prev_floor; i < N_FLOORS; i++) {
			//har bestilling til etasje over den den er i og er på vei opp
			if ((is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i))) {
				return DIRN_UP;
			}
		}
		//har IKKE best. til over den den er i:
		//sjekker om den har bestillinger under:
		for (int i = 0; i < prev_floor; i++) {
			if (is_order(BUTTON_DOWN, i) || is_order(BUTTON_COM, i)) {
				return DIRN_DOWN;
			}
		}
	}
	else if (curr_dir == DIRN_DOWN) {
		//sjekker om best. til UNDER den den er i:
		for (int i = 0; i < prev_floor; i++) {
			if (is_order(BUTTON_DOWN, i) || is_order(BUTTON_COM, i)) {
				return DIRN_DOWN;
			}
		}
		for (int i = prev_floor; i < N_FLOORS; i++) {
			//hvis ikke, har den bestilling over?
			if ((is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i))) {
				return DIRN_UP;
			}
		}
	}
	else if (curr_dir == DIRN_STOP) {
		//køen har vært tom, men har nå én bestilling.
		for (int i = 0; i < N_FLOORS; i++) {
			if (is_order(BUTTON_DOWN, i) || is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i)) {
				if (prev_floor < i) {
					return DIRN_UP;
				}
				else if (prev_floor > i) {
					return DIRN_DOWN;
				}
				else{
					return DIRN_STOP;
				}
			}
		}
	}
	//ta seg av andre merkelige tilfeller
	//return DIRN_STOP;*/
}
