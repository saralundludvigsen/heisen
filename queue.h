//
//  queue.h
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//


#ifndef queue_h
#define queue_h
#include "FSM.h"
#include <stdbool.h>
#define N_BUTTONS 3
//QUEUE

//initialiserer køen, dvs. setter alle elementene til 0.
void initialize_queue();

//if button is pushed, call this function
//NB 0-indeksert floor
void add_to_queue(int floor, button_type button);

//Fjerner en etasje fra køen.
//Dvs. setter alle 3 knapper i kø til 0
void remove_from_queue(int floor);

//sjekker om køen er tom
bool queue_is_empty();

//tømmer køen
void empty_queue();

//sjekker knappen _i køen_, om den er bestilt dit
bool is_order(button_type button, int floor);

//ordre over?
bool is_order_above(int current_floor);

//ordre under?
bool is_order_below(int current_floor);

//for test
void print_queue();

#endif /* queue_h */
