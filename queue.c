//
//  queue.c
//  Heis
//
//  Created by Sara Lund Ludvigsen on 27.02.2018.
//  Copyright © 2018 Sara Lund Ludvigsen. All rights reserved.
//

#include "queue.h"
//queue c-file

#define N_BUTTONS 3
//kø-matrise
static int queue[N_FLOORS][N_BUTTONS] = {
    {BUTTON_UP1, BUTTON_DOWN1, BUTTON_COMMAND1},
    {BUTTON_UP2, BUTTON_DOWN2, BUTTON_COMMAND2},
    {BUTTON_UP3, BUTTON_DOWN3, BUTTON_COMMAND3},
    {BUTTON_UP4, BUTTON_DOWN4, BUTTON_COMMAND4},
};

void initialize_queue(){
    for(int i=0;i<N_FLOORS;i++){
        for(int j=0;j<N_BUTTONS;j++){
            queue[i][j]=0;
        }
    }
}

void add_to_queue(button_type button, int floor){
    //forutsetter at paramterne er "lovlige": ikke kaller down på etg 1 f eks
    queue[floor][button]=1;
}

void remove_from_queue(int floor){
    //forutsetter at paramterne er "lovlige": ikke kaller down på etg 1 f eks
    for(int i=0;i<N_BUTTONS;i++){
        queue[floor][i]=0;
    }
        }
        
        
        bool queue_is_empty(){
            for(int i=0;i<N_FLOORS;i++){
                for(int j=0;j<N_BUTTONS;j++){
                    if(queue[i][j]){
                        return false;
                    }
                }
            }
            return true;
        }
        
        void empty_queue(){
            for(int i=0;i<N_FLOORS;i++){
                for(int j=0;j<N_BUTTONS;j++){
                    if(queue[i][j]){
                        queue[i][j]=0;
                    }
                }
            }
        }
        
        bool is_order(button_type button, int floor){
            return queue[floor][button];
        }


