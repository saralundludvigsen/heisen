//handling
#include "elev.h"
#include "queue.h"


//timer på 3 sek. True i 3 sek, så false
bool door_timer();


//returnerer opp (1) eller ned (0) avhengig av om etg er over eller under den heisen er i
elev_motor_direction_t get_direction(int floor_in, int floor_to);


//sjekker om heisen skal stoppe i current etasje
//dvs. om floor ligger i køen, i riktig retning
bool reached_floor_to_stop_in(elev_motor_direction_t current_direction);



