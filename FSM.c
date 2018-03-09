//
//  FSM.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#include "FSM.h"
#include "timer.h"
#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "queue.h"
static  State state;

void initialize_state() {
	state = stop;
}

void event_emergency_stop_pushed() {
    
    elev_set_motor_direction(DIRN_STOP);
    empty_queue();
    if (elev_get_floor_sensor_signal() >= 0) {
        event_stop_door_open();
        //start = start_timer();
        state = stop_door_open;
        
        
    }
    else{
        state = emergency_stop;
    }
}

void event_button_pushed(int floor, button_type button) {
    switch (state) {
            
        case (emergency_stop):
            break;
        case (stop_door_open):
        case(stop):
        case(drive):
            add_to_queue(floor, button);
            break;
    }
}
static int now = 0;
void event_queue_is_empty() {
    switch (state) {
            
        case (emergency_stop):
            break;
        case (stop_door_open):
            
            if (seccounter() >= 3){
                elev_set_door_open_lamp(0);
                state = stop;
            }
            else if ((seccounter() < 3) && now == 0){
                printf("mindre \n");
                now++;
            }
            break;
        case (drive):
        case (stop):
            break;
    }
}

void z_drive(elev_motor_direction_t current_direction){
		//vi trenger en funksjon get_direction() 
		elev_set_motor_direction(current_direction);
		state = drive;
}

void z_stop(){
	elev_set_motor_direction(DIRN_STOP);
}

void event_queue_not_empty(elev_motor_direction_t current_direction) {
    switch (state) {
        case (emergency_stop):
            break;
        case (stop_door_open):
            if ( seccounter() >= 3){
                elev_set_door_open_lamp(0);
                state = stop;
                
            }
            else if (seccounter() < 3){
                printf("mindre");
            }
            break;
        case (drive):
            /*if (reached_floor_to_stop_in()) {
             z_stop();
             event_stop_door_open();
             }*/
            break;
        case (stop):
            z_drive(current_direction);
            break;
    }
}

void event_reached_floor() {
    printf("in it \n");
    switch(state){
        case(emergency_stop):
            printf("State: emergency stop \n");
            break;
        case(drive):
            printf("State: drive \n");
        case(stop):
            printf("State: stop \n");
            z_stop();
        case(stop_door_open):
            printf("State: stop door open \n");
            event_stop_door_open();
            remove_from_queue(elev_get_floor_sensor_signal());
            state = stop_door_open;
            break;
    }
}

void event_stop_door_open() {
    printf("in event_stop_door_open \n");
    //Hold døra åpen i 3 sek
    //dette går ikke
    seccounter();
    elev_set_door_open_lamp(1);

}
