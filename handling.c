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
}

//elev_motor_direction_t get_direction(int prev_floor, elev_motor_direction_t curr_dir) {
	//if (curr_dir == DIRN_UP) {
	//	for (int i = prev_floor; i < N_FLOORS; i++) {
	//		//har bestilling til etasje over den den er i og er på vei opp
	//		if ((is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i))) {
	//			return DIRN_UP;
	//		}
	//	}
	//	//har IKKE best. til over den den er i:
	//	//sjekker om den har bestillinger under:
	//	for (int i = 0; i < prev_floor; i++) {
	//		if (is_order(BUTTON_DOWN, i) || is_order(BUTTON_COM, i)) {
	//			return DIRN_DOWN;
	//		}
	//	}
	//}
	//else if (curr_dir == DIRN_DOWN) {
	//	//sjekker om best. til UNDER den den er i:
	//	for (int i = 0; i < prev_floor; i++) {
	//		if (is_order(BUTTON_DOWN, i) || is_order(BUTTON_COM, i)) {
	//			return DIRN_DOWN;
	//		}
	//	}
	//	for (int i = prev_floor; i < N_FLOORS; i++) {
	//		//hvis ikke, har den bestilling over?
	//		if ((is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i))) {
	//			return DIRN_UP;
	//		}
	//	}
	//}
	//else if (curr_dir == DIRN_STOP) {
	//	//køen har vært tom, men har nå én bestilling.
	//	for (int i = 0; i < N_FLOORS; i++) {
	//		if (is_order(BUTTON_DOWN, i) || is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i)) {
	//			if (prev_floor < i) {
	//				return DIRN_UP;
	//			}
	//			else if (prev_floor > i) {
	//				return DIRN_DOWN;
	//			}
	//		}
	//	}
	//}
	//ta seg av andre merkelige tilfeller
	//return DIRN_STOP;
//}
