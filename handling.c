//
//  handling.c
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

#include "handling.h"
#include "FSM.h"

#include <stdio.h>
#include <stdbool.h>

#include "elev.h"
#include "queue.h"


bool reached_floor_to_stop_in(elev_motor_direction_t current_direction) {
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

	//BUTTON_UP og BUTTON_DOWN:
	//her bryr vi oss om retning til heisen.
	else if (is_order(BUTTON_DOWN, current_floor) && current_direction == DIRN_DOWN) {
		printf("DOWN dir and button\n");l
		return true;
	}
	else if (is_order(BUTTON_UP, current_floor) && current_direction == DIRN_UP) {
		printf("UP dir and button\n");
		return true;
	}

	//dersom den kjører OPP og denne bestillingen er NED og den ØVERSTE: return true.
	else if ((current_direction == DIRN_UP) && is_order(BUTTON_DOWN, current_floor)) {
		//ned i 4 etg:
		if (current_floor == 3) {
			printf("new 4th floor down\n");
			return true;
		}
		bool isOrderAbove = false;
		for (int i = current_floor + 1; i < N_FLOORS; i++) {
			if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
				isOrderAbove = true;
				break;
			}
		}
		if (isOrderAbove) {
			return false;
		}
		else if (!isOrderAbove) {
			printf("no orders above!\n");
			return true;
		}
	}
	//dersom den kjører NED og denne bestillingen er OPP og den NEDERSTE: return true.
	else if ((current_direction == DIRN_DOWN) && is_order(BUTTON_UP, current_floor)) {
		if (current_floor == 0) {
			printf("new 1st floor up\n");
			return true;
		}
		bool isOrderBelow = false;
		for (int i = current_floor - 1; i > 0; i--) {
			if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
				isOrderBelow = true;
				break;
			}
		}
		if (isOrderBelow) {
			return false;
		}
		else if (!isOrderBelow) {
			printf("no orders below!\n");
			return true;
		}
	}
	return false;

}


elev_motor_direction_t get_direction(int prev_floor) {
	//test - uten retning:
	for (int i = prev_floor + 1; i < N_FLOORS; i++) {
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
