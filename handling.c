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
#include "queue.h"


bool reached_floor_to_stop_in(elev_motor_direction_t current_direction, int current_floor) {
	//ikke i etasje, sjekke først
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
		printf("DOWN dir and button\n");
		return true;
	}
	else if (is_order(BUTTON_UP, current_floor) && current_direction == DIRN_UP) {
		printf("UP dir and button\n");
		return true;
	}

	//spesialtilfelle ved oppstart av programmet, og bestilling med UP/DOWN fra oppstartsetasje
	else if ((is_order(BUTTON_UP, current_floor) || is_order(BUTTON_DOWN, current_floor)) && current_direction == DIRN_STOP) {
		printf("BAMM\n");
		return true;
	}


	//dersom den kjører OPP og denne bestillingen er NED og den ØVERSTE: return true.
	else if ((current_direction == DIRN_UP) && is_order(BUTTON_DOWN, current_floor)) {
		//ned i 4 etg:
		if (current_floor == 3) {
			printf("new 4th floor down\n");
			return true;
		}
		if (is_order_above(current_floor)) {
			return false;
		}
		else if (!is_order_above(current_floor)) {
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
		if (is_order_below(current_floor)) {
			return false;
		}
		else if (!is_order_below(current_floor)) {
			printf("no orders below!\n");
			return true;
		}
	}
	return false;

}


elev_motor_direction_t get_direction(elev_motor_direction_t current_direction, int last_floor_been_in) {

	if(is_order_above(last_floor_been_in) && current_direction == DIRN_UP){
		return DIRN_UP;
	}
	if(is_order_below(last_floor_been_in) && current_direction == DIRN_DOWN){
		return DIRN_DOWN;
	}
	//test - uten retning:
	//har bestilling til etasje over den den er i
	if(is_order_above(last_floor_been_in)){
		return DIRN_UP;
	}
	//har bestilling til etasje under den den er i
	else if(is_order_below(last_floor_been_in)){
		return DIRN_DOWN;
	}

	//retning etter emergency stop mellom etasjer:
	else if((is_order(BUTTON_UP, last_floor_been_in)
		||is_order(BUTTON_DOWN, last_floor_been_in)||is_order(BUTTON_COM, last_floor_been_in))
			&&get_is_emergency_outside_floor()){
			//nå tilsvarer currdir direction før nødstopp
		set_is_emergency_outside_floor(false);
		if(current_direction==DIRN_UP){
			return DIRN_DOWN;
		}
		else if(current_direction==DIRN_DOWN){
			return DIRN_UP;
		}
	}

	//kommer hit kun i spesialtilfellet at den netopp har hatt emergency stop mellom etasjer OG
	// at den så bestilles til etasjen den var i rett før emerg.
	//Men, siden retning på motoren fysisk kun settes EN gang i event_queue_not_empty() har det ikke noe å si.
	//Eventuelt kan den også gå hit ved andre uoppdagede bugs.
	return DIRN_STOP;
}