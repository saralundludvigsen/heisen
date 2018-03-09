#include "lamps.h"
#include "elev.h" //pga N_FLOORS


void turn_button_lamp_on(int floor, button_type button){
	elev_set_button_lamp(button, floor, 1);
}

void turn_button_lamps_off(int floor){
	if(floor==0){
		elev_set_button_lamp(BUTTON_COM, floor, 0);
	    elev_set_button_lamp(BUTTON_UP, floor, 0);
	}
	else if (floor == 3){
		elev_set_button_lamp(BUTTON_COM, floor, 0);
	    elev_set_button_lamp(BUTTON_DOWN, floor, 0);
	}
	else{
		elev_set_button_lamp(BUTTON_COM, floor, 0);
	    elev_set_button_lamp(BUTTON_DOWN, floor, 0);
	    elev_set_button_lamp(BUTTON_UP, floor, 0);
	}
}

void turn_off_all_button_lights(){
	for(int i=0;i<N_FLOORS;i++){
		turn_button_lamps_off(i);
	}
}