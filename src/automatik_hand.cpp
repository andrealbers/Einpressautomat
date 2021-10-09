#include "automatik_hand.h"

void pressen()
{
    delay(pauseposerreicht);
    if (digitalRead(HAND) == 1 || anlage_eingeschaltet == 0)
        return;
    digitalWrite(MAGNETVENTIL, HIGH);
    delay(pausepressen);
    digitalWrite(MAGNETVENTIL, LOW);
    delay(pausegepresst);
}

void automatikbetrieb()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Autom. gestartet");
    long pressenmaxspeed = 10000; //Max. Geschwindigkeit Pressvorgang
    long pressenacc = 10000;      //Beschleunigung Pressvorgang
    long zurueckmaxspeed = 10000;
    long zurueckacc = 10000;

    long erstePos = -10850; //10945 Erste Position um vor erste Bohrung zu stehen
    long abstand = 3830;    //Abstand zwischen den Bohrungen 3855
    long raus = 500;        //Abstand um Werkstück auszuschieben

    long pos1 = erstePos;
    long pos2 = pos1 - abstand - 10;
    long pos3 = pos2 - abstand - 10;
    long pos4 = pos3 - abstand - 10;
    long pos5 = pos4 - abstand - 30;
    long pos6 = pos5 - abstand - 30;
    long pos7 = pos6 - abstand - 30;
    long pos8 = pos7 - abstand - 30;
    long pos9 = pos8 - abstand - 10;
    long pos10 = pos9 - abstand;
    long pos11 = pos10 - abstand - 20;
    long pos12 = pos11 - abstand;
    long pos13 = pos12 - abstand - 30;
    long pos14 = pos13 - abstand - 15;
    long pos15 = pos14 - abstand;

    long positionen[15] = {pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12, pos13, pos14, pos15};

    digitalWrite(SLP, HIGH); //Treiber aktivieren
    digitalWrite(M1, LOW);   //1/16 Schritt aktivieren
    digitalWrite(M2, HIGH);

    stepper.setMaxSpeed(pressenmaxspeed);
    stepper.setAcceleration(pressenacc);

    delay(30);

    for (int i = 0; i <= 14; i++)
    { //Bei 0-Position anfangen bis 14 0 = Pos1  default 0 <= 14
        if (digitalRead(HAND) == 1 || anlage_eingeschaltet == 0)
            return;
        stepper.moveTo(positionen[i]); //Ziel setzen, Schritte werden berechnet
        while (stepper.distanceToGo() != 0)
        { //Solange fahren, bis kein Schritt mehr notwendig
            if (digitalRead(HAND) == 1 || anlage_eingeschaltet == 0)
                return;
            stepper.run(); //Einen Schritt machen
        }
        lcd.setCursor(0, 1);
        lcd.print("");
        lcd.print(-1*positionen[i]);
        lcd.print(" erreicht");
        pressen(); //Dann Pressen
    }

    stepper.moveTo(positionen[14] - raus); //Werkstück ausschieben
    while (stepper.distanceToGo() != 0)
    {
        if (digitalRead(HAND) == 1 || anlage_eingeschaltet == 0)
            return;
        stepper.run();
    }
   
    digitalWrite(M1, HIGH); //1/4 Schritt aktivieren
    digitalWrite(M2, LOW);

    stepper.setMaxSpeed(zurueckmaxspeed);
    stepper.setAcceleration(zurueckacc);

    delay(30);

    lcd.print(0,0);
    lcd.print("Abgeschlossen   ");
    lcd.setCursor(0,1);
    lcd.print("Fahre zurueck   ");
  
    stepper.moveTo(stepper.currentPosition() - ((stepper.currentPosition() - parkpos) / 4));
    while (stepper.distanceToGo() != 0)
    {
        if (digitalRead(HAND) == 1 || anlage_eingeschaltet == 0)
            return;
        stepper.run();
    }

    digitalWrite(SLP, LOW); //Treiber deaktivieren
}

void handbetrieb()
{
    lcd.setCursor(0, 1);
    lcd.print("Zylinder ausf.  ");
    while (digitalRead(HAND) == 1 && anlage_eingeschaltet == 1 && digitalRead(TASTER) == 0)
        digitalWrite(MAGNETVENTIL, HIGH);

    /*   //POSITIONEN BESTIMMEN; SERIALMONITOR AUSGABE
       if (digitalRead(TASTER) == LOW) {
       stepper.runToNewPosition(zaehlen_hand);
       zaehlen_hand -= 100;
       Serial.println(stepper.currentPosition());
       }
  */

    digitalWrite(MAGNETVENTIL, LOW);
}