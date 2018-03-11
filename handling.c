//
//  handling.c
//
//

#include "handling.h"
#include "FSM.h"
#include <stdio.h>
#include "queue.h"
#include <assert.h>


void set_drive(elev_motor_direction_t current_direction){
		assert(current_direction == DIRN_DOWN || current_direction==DIRN_UP);
		elev_set_motor_direction(current_direction);
		set_state(drive);
}

void set_stop(){
	elev_set_motor_direction(DIRN_STOP);
}


bool reached_floor_to_stop_in(elev_motor_direction_t current_direction, int current_floor) {
	//sjekker først om heisen er i en etasje
	if (current_floor == -1) {
		return false;
	}
	//BUTTON_COMMAND trykket: bryr oss ikke om retningen heisen har
	else if (is_order(BUTTON_COM, current_floor)) {
		printf("command\n");
		return true;
	}

	//BUTTON_UP og BUTTON_DOWN: her bryr vi oss om retning til heisen.
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
		printf("same floor after startup\n");
		return true;
	}


	//dersom den kjører OPP og denne bestillingen er NED og den ØVERSTE bestillingen: vil stoppe.
	else if ((current_direction == DIRN_UP) && is_order(BUTTON_DOWN, current_floor)) {
		//ned i 4 etg:
		if (current_floor == 3) {
			printf("4th floor down\n");
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
	//dersom den kjører NED og denne bestillingen er OPP og den NEDERSTE bestillingen: vil stoppe.
	else if ((current_direction == DIRN_DOWN) && is_order(BUTTON_UP, current_floor)) {
		if (current_floor == 0) {
			printf("1st floor up\n");
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

	//fortsett opp hvis du har bestillinger over
	if(is_order_above(last_floor_been_in) && current_direction == DIRN_UP){
		return DIRN_UP;
	}
	//fortsett ned hvis du har bestillinger under
	else if(is_order_below(last_floor_been_in) && current_direction == DIRN_DOWN){
		return DIRN_DOWN;
	}
	//dersom de over ikke er tilfellet:
	//har bestilling til etasje over den den er i
	else if(is_order_above(last_floor_been_in)){
		return DIRN_UP;
	}
	//har bestilling til etasje under den den er i
	else if(is_order_below(last_floor_been_in)){
		return DIRN_DOWN;
	}

	//spesialtilfelle: retning etter emergency stop mellom etasjer,
	//når man vil tilbake til den etasjen heisen var i før nødstopp
	else if((is_order(BUTTON_UP, last_floor_been_in)
		||is_order(BUTTON_DOWN, last_floor_been_in)||is_order(BUTTON_COM, last_floor_been_in))
			&&get_is_emergency_outside_floor()){
			//nå tilsvarer current_direction retning før nødstopp
		set_is_emergency_outside_floor(false);
		if(current_direction==DIRN_UP){
			return DIRN_DOWN;
		}
		else if(current_direction==DIRN_DOWN){
			return DIRN_UP;
		}
	}

	//kommer hit kun i spesialtilfellet at den nettopp har hatt emergency stop mellom etasjer OG
	// at den så bestilles til etasjen den var i rett før emerg, men etter at den har fått DOWN/UP en gang.
	//Siden retning på motoren fysisk kun settes EN gang i event_queue_not_empty() har det derfor ikke noe å si.
	//Eventuelt kan den også gå hit ved andre uoppdagede bugs.
	return DIRN_STOP;
}