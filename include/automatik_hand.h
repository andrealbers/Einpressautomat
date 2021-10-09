#ifndef AUTOMATIK_HAND_H
#define AUTOMATIK_HAND_H

#include "main.h"

#define pauseposerreicht 100 //1 SEKUNDE NACH ERREICHEN PRESSEN BEGINNEN
#define pausepressen 1000    //0,8 SEKUNDEN LANG ZYLINDER RAUS
#define pausegepresst 1000   //1 SEKUNDE WARTEN BIS ZYLINDER ZURÜCK

void pressen();
void automatikbetrieb();
void handbetrieb();

#endif /* AUTOMATIK_HAND_H */