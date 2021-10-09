#include "isr.h"

void SPEICHERN()
{
    EEPROM.put(eepromadr, anz_gef_Balken);     
}

void AUSSCHALTEN()
{
    digitalWrite(SLP, LOW);
    digitalWrite(MAGNETVENTIL, LOW);
    homing_erfolgreich = 0;
    anlage_eingeschaltet = 0;
}