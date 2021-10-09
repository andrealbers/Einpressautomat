#include "homing.h"

void homing()
{
    lcd.setCursor(0, 0);
    lcd.print("Anlage homen..  ");
    long homingmaxspeed = 1000.0; //Max. Geschwindigkeit beim Homen
    long homingacc = 50;          //Beschleunigung beim Homen
    //long parkpos = -200;                         //Parkposition
    long homingPos = 0;

    digitalWrite(SLP, HIGH); //Treiber aktivieren
    digitalWrite(M1, LOW);   //1/16 Schritt aktivieren
    digitalWrite(M2, HIGH);

    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(homingmaxspeed);
    stepper.setAcceleration(homingacc);

    delay(500);

    while (digitalRead(ENDSTOPP) == HIGH)
    {
        homingPos++;
        stepper.moveTo(homingPos);
        stepper.run();
        if (anlage_eingeschaltet == 0)
            return;
    }

    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(homingmaxspeed);

    delay(500);
    homingPos = 0;

    while (digitalRead(ENDSTOPP) == LOW)
    {
        homingPos--; //Nur einmal dekrementieren reicht oder?
        stepper.move(homingPos);
        stepper.run();
        if (anlage_eingeschaltet == 0)
            return;
    }

    stepper.setCurrentPosition(0);
    stepper.setMaxSpeed(10000);
    stepper.setAcceleration(10000);

    stepper.moveTo(parkpos);

    while (stepper.distanceToGo() != 0)
    {
        stepper.run();
        if (anlage_eingeschaltet == 0)
            return;
    }

    homing_erfolgreich = 1;
    lcd.setCursor(0,0);
    lcd.print("referenziert    ");
    delay(1000);
}