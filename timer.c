#include "timer.h"
#include <time.h>
static int toggle;
static time_t start;


int seccounter(void){
    
    time_t finish = 0;
    time_t difference = 0;
    
    if (toggle == 0){
        start = time(0);
        toggle = 1;
        return 0;
    }
    
    else if (toggle == 1){
        
        finish = time(0);
        difference = finish - start;
        if ((int) difference >= 3){
            toggle = 0;
            return (int) difference;
        }
        else{
            return (int) difference;
        }
   } 
   return 0;
    
}