//
//  queue.c
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
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

//forutsetter at current_floor!=-1
bool is_order_above(int current_floor){
	for (int i = current_floor + 1; i < N_FLOORS; i++) {
		if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
			return true;
		}
	}
	return false;
}

//forutsetter at current_floor!=-1
bool is_order_below(int current_floor){
	for (int i = current_floor - 1; i >= 0; i--) {
		if (is_order(BUTTON_UP, i) || is_order(BUTTON_COM, i) || is_order(BUTTON_DOWN, i)) {
			return true;
		}
	}
	return false;
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


