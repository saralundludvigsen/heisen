//
//  handling.h: handling motor direction
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

//#pragma once
#ifndef handling_h
#define handling_h
#include "elev.h"
#include <stdbool.h>


//kjører heisen opp eller ned
void set_drive(elev_motor_direction_t current_direction);

//stopper heisen
void set_stop();

//sjekker om heisen skal stoppe i current floor, dvs. om current floor ligger i køen, i riktig retning
bool reached_floor_to_stop_in(elev_motor_direction_t current_direction, int current_floor);

//returnerer opp eller ned, avhengig av hvor heisen er i forhold til bestillingene. Eventuelt stopp i spesialtilfeller.
elev_motor_direction_t get_direction(elev_motor_direction_t current_direction, int last_floor_been_in);


#endif /* handling_h */
