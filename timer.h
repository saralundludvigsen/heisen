
#ifndef timer_h
#define timer_h

//Starter opp timer når den blir kalt første gang, 
//de neste gangene den blir kalt innen 3 sekunder returnerer den hvor lang tid det har gått.
//Dersom der har gått 3 sekunder etter første gang den ble kalt vil den "selvinitialisere seg",
//og begynne på nytt igjen.
int seccounter(void);

#endif