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
//#include "queue.h"
#include "handling.h"


//i FSM:
//direction current_dir;
//get_direction()


int main() {
	printf("Programmet kjører!");

	if (elev_init() == 0) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	//queue init:
    
	initialize_queue();
	initialize_state();

	// beholder etter initialisering. startbetingelse
	elev_set_motor_direction(DIRN_STOP);
	elev_motor_direction_t current_direction = DIRN_STOP;
	int prev_floor = 0; //antar at start i 1. etasje
	//------------------------------------------------------------------------------
    
	while (1) {
		//sjekker hele tiden om og hvilken knapp som er trykket
		//og setter køen vha add_to_queue()
		if (elev_get_stop_signal() == 1) {
			event_emergency_stop_pushed();
		}
		//oppdaterer prev_floor:
		if (elev_get_floor_sensor_signal() != -1) {
			prev_floor = elev_get_floor_sensor_signal();
		}
        
    
		
        //
		current_direction = get_direction(prev_floor, current_direction);
        if(current_direction==DIRN_UP){
            printf(" UP ");
        }
        else if(current_direction==DIRN_DOWN){
            printf(" DOWN ");
        }
        else if(current_direction==DIRN_STOP){
            printf(" STOP ");
        }
        
        
		//skal kun sjekke knappetrykk og legge til i køen
		for(int i = 0; i < N_FLOORS; i++){
			for(int j = 0; j < N_BUTTONS; j++){
				elev_button_type_t knapp = (elev_button_type_t) j;
				button_type button = (button_type) j;
				if (elev_get_button_signal(knapp, i)){
					event_button_pushed(i, button);
				}
			}
		}
        
        //print_queue();
	
		if(reached_floor_to_stop_in(current_direction)){
			event_reached_floor();
		}

		else if (!queue_is_empty()){
			//Her bare tester man om det har blitt lagt til noe i queue
			//elev_set_motor_direction(DIRN_UP);

			//event_queue_not_empty();
            //current_direction=DIRN_UP;
            event_queue_not_empty(current_direction);

			//test: elev_set_motor_direction(DIRN_UP);

			//event_queue_not_empty(direction);
			//event_drive hit
		}
		else if (queue_is_empty()){
			event_queue_is_empty();
		}
		
	}
	return 0;
}

