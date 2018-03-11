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
#include "lamps.h"


//i FSM:
//direction current_dir;
//get_direction()


int main() {

	if (elev_init() == 0) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	//queue og state init:
	initialize_queue();
	initialize_state();
	initialize_is_emergency_outside_floor();

	//initialiserer variabler:
	elev_motor_direction_t current_direction = DIRN_STOP;
	int last_floor_been_in = 0; //oppdateres med en gang i while dersom etg!=-1. Dvs ok.
	int current_floor = 0; //er -1 når utenfor etasje
	//------------------------------------------------------------------------------
    
	while (1) {
		//oppdaterer current floor
		current_floor = elev_get_floor_sensor_signal();

		//nødstopp:
		if (elev_get_stop_signal() == 1) {
			event_emergency_stop_pushed();
		}

		//oppdaterer last_floor_been_in:
		if (current_floor != -1) {
			last_floor_been_in = update_floor_and_light(current_floor);
		}		

		//sjekker hele tiden om og hvilken knapp som er trykket
		//skal kun sjekke knappetrykk og legge til i køen, ikke håndtere bestillingene
		for(int i = 0; i < N_FLOORS; i++){
			for(int j = 0; j < N_BUTTONS; j++){
				elev_button_type_t knapp = (elev_button_type_t) j;
				button_type button = (button_type) j;
				if (elev_get_button_signal(knapp, i)){
					event_button_pushed(i, button);
				}
			}
		}


		if(reached_floor_to_stop_in(current_direction, current_floor)){
			event_reached_floor_to_stop_in();
		} 

		else if (!queue_is_empty()){
			//kjør hvis lagt til noe i queue
			current_direction = get_direction(current_direction, last_floor_been_in);
            event_queue_not_empty(current_direction);

		}
		else if (queue_is_empty()){
			event_queue_is_empty();
		}
		
		
	}
	return 0;
}

