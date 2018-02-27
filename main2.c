//
//  main2.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#include "main2.h"

#include "elev.h"
#include "channels.h"
#include <stdio.h>
#include "queue.h"
#include "FSM.h"
#include "elev.h"


int main() {
    
    // Queue = [1_up,2_down,2_up,3_down,3_up,4_down]
    queue[6]={0,0,0,0,0,0};
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    // beholder etter initialisering. startbetingelse
    elev_set_motor_direction(DIRN_STOP);
    //------------------------------------------------------------------------------
    state = stop;
    while(1){
        //sjekker hele tiden om og hvilken knapp som er trykket
        //og setter køen vha add_to_queue()
        
        
        if (elev_get_stop_signal()){
            event_emergency_stop_pushed();
        }
        
        for(int i = 0; i < N_FLOORS; i++){
            for(int j = 0; j < N_BUTTONS; j++){
                if (elev_get_button_signal(button_type(j), i)){
                    event_button_pushed(button_type(j), i);
                }
            }
        }
        
        else if(queue_is_empty()){
            event_queue_is_empty();
        }
        
        else if (!queue_is_empty()){
            event_queue_not_empty();
        }
        
        else if(should_i_stop()){
            event_reached_floor();
        }
       
        
        
        
        //-------------------------------------------------------------
        
        //tom kø--> stop
        else if(queue_is_empty()){
            state = stop;
        }
        
        //Bruker trykker på etasjeknapp
        else if(!queue_is_empty()){
            state = drive;
        }

        //Åpne dør
        else if(state==stop && door_timer()){
            state = stop_door_open;
        }
        
        //Nødstopp
        if (elev_get_stop_signal()){
            state = emergency_stop;
            FSM(state);
            
            if(get_floor_sensor_signal() >= 0){
                state = stop_door_open;
            }
            else{
                state = stop;
            }
        }
        
    }
    
    
    //------------------------------------------------------------------------------
    
    if (elev_get_stop_signal()) {
        elev_set_motor_direction(DIRN_STOP);
        break;
    }
    
    
    return 0;
}

