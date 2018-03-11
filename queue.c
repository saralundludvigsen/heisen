//
//  queue.c
//
//
#include "queue.h"
#include <stdio.h>
#include "FSM.h"
#include "elev.h"


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
    //Forutsetter at paramterne er "lovlige": ikke kaller down på etg 1 f eks.
    //Dette er ok, for det går ikke an å trykke på DOWN i 1.
    queue[floor][button] = 1;
}

void remove_from_queue(int floor) {
    //forutsetter at paramterne er "lovlige": ikke kaller down på etg 1 f eks
    //Antar at alle ventende personer uansett vil gå inn i heisen om retningen den er på vei i er riktig eller ikke
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

bool is_order_above(int current_floor){
    //forutsetter at current_floor!=-1
	for (int i = current_floor + 1; i < N_FLOORS; i++) {
		if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
			return true;
		}
	}
	return false;
}

bool is_order_below(int current_floor){
    //forutsetter at current_floor!=-1
	for (int i = current_floor - 1; i >= 0; i--) {
		if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
			return true;
		}
	}
	return false;
}

