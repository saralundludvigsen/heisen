//
//  FSM.h
//  
//
//  Created by Sara Lund Ludvigsen on 23.02.2018.
//
//

#ifndef FSM_h
#define FSM_h

#include <stdio.h>
#include <unistd.h>
#include "elev.h"
#include "queue.h"


typedef enum states{
    emergency_stop,
    drive,
    stop_door_open,
    stop
} State;


//knappetyper
typedef enum buttontype{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_COM
} button_type;


void event_emergency_stop_pushed();
void event_button_pushed(int floor, button_type button);
void event_queue_is_empty();
void event_queue_not_empty();
void event_reached_floor();
void event_stop_door_open();


#endif /* FSM_h */
