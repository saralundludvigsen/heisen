//
//  FSM.c
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#include "FSM.h"
static int previous_floor;
static clock_t start;
static  State state;

void initialize_state() {
	state = stop;
}

void event_emergency_stop_pushed() {
    
    elev_set_motor_direction(DIRN_STOP);
    empty_queue();
    if (elev_get_floor_sensor_signal() >= 0) {
        event_stop_door_open();
        start = start_timer();
        state = stop_door_open;
        
    }
    
    state = emergency_stop;
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

void event_queue_is_empty() {
    switch (state) {
            
        case (emergency_stop):
            break;
        case (stop_door_open):
            if (current_time() - start >= 3){
                elev_set_door_open_lamp(0);
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
            if (current_time() - start >= 3){
                elev_set_door_open_lamp(0);
                
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
    switch(state){
        case(emergency_stop):
            break;
        case(stop_door_open):
            event_stop_door_open();
            remove_from_queue(elev_get_floor_sensor_signal());
        case(drive):
        case(stop):
            z_stop();
            state = stop_door_open;
            //event_stop_door_open();
            //slett bestilling: --> da vil den kjøre videre
            
            break;
    }
}

void event_stop_door_open() {
    //Hold døra åpen i 3 sek
    //dette går ikke
    start = start_timer();
    elev_set_door_open_lamp(1);

}
//------------------------------------------------------------------
//QUEUE

//kø-matrise
static int queue[N_FLOORS][N_BUTTONS];

void initialize_queue() {
    for (int i = 0; i < N_FLOORS; i++) {
        for (int j = 0; j < N_BUTTONS; j++) {
            queue[i][j] = 0;
        }
    }
}

void add_to_queue(int floor, button_type button) {
    //forutsetter at paramterne er "lovlige": ikke kaller down på etg 1 f eks
    queue[floor][button] = 1;
}

void remove_from_queue(int floor) {
    //forutsetter at paramterne er "lovlige": ikke kaller down på etg 1 f eks
    //Antar at en person vil uansett gå inn i heisen om retningen den er på vei i er riktig eller ikke
    for (int i = 0; i < N_BUTTONS; i++) {
        queue[floor][i] = 0;
    }
}


bool queue_is_empty() {
    for (int i = 0; i < N_FLOORS; i++) {
        for (int j = 0; j < N_BUTTONS; j++) {
            if (queue[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void empty_queue() {
    for (int i = 0; i < N_FLOORS; i++) {
        for (int j = 0; j < N_BUTTONS; j++) {
            if (queue[i][j]) {
                queue[i][j] = 0;
            }
        }
    }
}

bool is_order(button_type button, int floor) {
    return queue[floor][button];
}

void print_queue(){
    int yes=0;
    for (int i = 0;i<4;i++){
        for(int j=0;j<3;j++){
            if(queue[i][j]){
                yes =1;
                if(i==0){
                    printf("1");
                }
                else if(i==1){
                    printf("2");
                }
                else if(i==2){
                    printf("3");
                }
                else if(i==3){
                    printf("4");
                }
            }
        }
    }
    if(!yes){
        printf("Tom kø");
    }
}

