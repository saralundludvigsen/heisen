//
//  handling.h
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

#pragma once
#ifndef handling_h
#define handling_h

#include <stdio.h>
#include <stdbool.h>

#include "elev.h"
#include "queue.h"



//returnerer opp (1) eller ned (0) avhengig av om etg er over eller under den heisen er i
elev_motor_direction_t get_direction(int floor_in, int floor_to);
//elev_motor_direction_t get_direction(int prev_floor, elev_motor_direction_t curr_dir);


//sjekker om heisen skal stoppe i current etasje
//dvs. om floor ligger i køen, i riktig retning
bool reached_floor_to_stop_in(elev_motor_direction_t current_direction);



#endif /* handling_h */
