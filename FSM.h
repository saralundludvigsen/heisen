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
#include "main.h"
#include "elev.h"

typedef enum states{
    emergency_stop,
    drive,
    stop_door_open,
    stop
} State;


//knappetyper
typedef enum button_type{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_COMMAND
} button_type;

#endif /* FSM_h */
