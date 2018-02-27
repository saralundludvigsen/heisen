//
//  FSM.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

static int previous_floor;
static State state;


event_emergency_stop_pushed(){
    
    elev_set_motor_direction(DIRN_STOP);
    empty_queue();
    if(get_floor_sensor_signal() >= 0){
        elev_set_door_open_signal(1);
    }
    state = emergency_stop;
}

event_button_pushed(int floor, button_type button){
    switch (state){
    
        case (emergency_stop):
            break;
        case(stop && stop_door_open && drive):
            add_to_queue(floor,button);
    }
}

event_queue_is_empty(){
    elev_set_motor_direction(DIRN_STOP);
    state = stop;
}

//SE PÅ DENNE
event_queue_not_empty(){
    switch (state) {
        case (emergency_stop):
            break;
        case (drive):
            break;
        case (stop):
            if (reached_floor_to_stop_in(direction)){ //Hva er direction? Hvor får vi den fra?
                state = stop_door_open; //vil den her hoppe til case (stop_door_open)?
            }
            break;
        case (stop_door_open):
            //????
            break;
    }
}

event_reached_floor(){
    elev_set_motor_direction(DIRN_STOP);
    state = stop_door_open;
}
                
//------------------------------------------------------------------
                
FSM(State state){
    switch (state){
            
        case (emergency_stop):
            elev_set_motor_direction(DIRN_STOP);
            empty_queue();
            if(get_floor_sensor_signal() >= 0){
                elev_set_door_open_signal(1);
            }
            while(elev_get_stop_signal()){}
            break;
            
        case (stop):
            elev_set_motor_direction(DIRN_STOP);
            while (queue_is_empty() || !elev_get_stop_signal()){}
            break;
            
            
        case (drive):
            elev_motor_direction_t direction = get_direction(int floor_in, int floor_out));     //direction er 0 for ned og 1 for opp
            elev_set_motor_direction(direction);
            while (!should_i_stop(direction) || !elev_get_stop_signal()){}
            break;
    }
    
}
            



#include "FSM.h"
