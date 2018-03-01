//
//  main2.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#include "FSM.h"
#include "elev.h"
#include "channels.h"
#include <stdio.h>
#include "queue.h"
#include "handling.h"
static State state;

int main() {
    
	if (elev_init() == 0) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	// beholder etter initialisering. startbetingelse
	elev_set_motor_direction(DIRN_STOP);
	//------------------------------------------------------------------------------
	state = stop;
	while (1) {
		//sjekker hele tiden om og hvilken knapp som er trykket
		//og setter køen vha add_to_queue()

		if (elev_get_button_signal(BUTTON_CALL_UP, 1) == 1) {
			elev_set_motor_direction(DIRN_UP);
		}
		if (elev_get_stop_signal() == 1) {
			event_emergency_stop_pushed();
		}
		
		/*for(int i = 0; i < N_FLOORS; i++){
			for(int j = 0; j < N_BUTTONS; j++){
				if (elev_get_button_signal(static_cast<elev_button_type_t>(j), i)){
					event_button_pushed(i, static_cast<button_type>(j));
				}
			}
		}*/

		/*
		if (state == stop_door_open){
			event_stop_door_open();
		}
		else if (!queue_is_empty()){
			event_queue_not_empty();
		}
		else if (queue_is_empty()){
			event_queue_is_empty();
		}

		else if(reached_floor_to_stop_in()){
			event_reached_floor();
		}*/
	}
	return 0;
}

