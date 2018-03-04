//
//  FSM.h
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//
#pragma once
#ifndef FSM_h
#define FSM_h

#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "queue.h"


typedef enum states {
	emergency_stop,
	drive,
	stop
} State;


//knappetyper
typedef enum tag_button_type {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_COM
}button_type;


void event_emergency_stop_pushed();
void event_button_pushed(int floor, button_type button);
void event_queue_is_empty();
void event_queue_not_empty(elev_motor_direction_t current_direction);
void event_reached_floor();
void event_stop_door_open();
void z_drive(elev_motor_direction_t current_direction);
void z_stop();

//---------------------------------
//QUEUE


//initialiserer køen, dvs. setter alle elementene til 0.
void initialize_queue();

//if button is pushed, call this function
//NB 0-indeksert floor
void add_to_queue(button_type button, int floor);

//Fjerner en etasje fra køen.
//Dvs. setter alle 3 knapper i kø til 0
void remove_from_queue(int floor);

//sjekker om køen er tom
bool queue_is_empty();

//tømmer køen
void empty_queue();

//sjekker knappen _i køen_, om den er bestilt dit
bool is_order(button_type button, int floor);

void print_queue();


#endif /* FSM_h */
