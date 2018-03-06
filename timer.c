//
//  timer.c
//  timer
//
//  Created by Sara Lund Ludvigsen on 06.03.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

#include "timer.h"

clock_t start_timer(){
    clock_t start = clock();
    return start;
}

clock_t current_time(){
    clock_t curr = clock();
    return curr;
}
