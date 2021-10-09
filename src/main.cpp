#include "main.h"

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
AccelStepper stepper(1, STEP, DIR);

volatile bool anlage_eingeschaltet = 0;
volatile bool homing_erfolgreich = 0;
unsigned int anz_gef_Balken = 0;
unsigned int temp_anz_Balken = 0;

void setup()
{
  //EEPROM.put(eepromadr, 0); //Zähler zurücksetzen
  EEPROM.get(eepromadr, anz_gef_Balken);

  pinMode(TASTER, INPUT_PULLUP);
  pinMode(HAND, INPUT_PULLUP);
  pinMode(ENDSTOPP, INPUT_PULLUP);
  pinMode(OUTAGE, INPUT);
  pinMode(EINGESCH, INPUT_PULLUP);

  pinMode(MAGNETVENTIL, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(SLP, OUTPUT);

  digitalWrite(MAGNETVENTIL, LOW);
  digitalWrite(M1, LOW); //M1:H und M2:L -> 1/4 STEP,  M1:L und M2:H -> 1/16 STEP
  digitalWrite(M2, LOW);
  digitalWrite(SLP, LOW); //LOW = Treiber Ausschalten

  attachInterrupt(digitalPinToInterrupt(OUTAGE), SPEICHERN, FALLING);
  attachInterrupt(digitalPinToInterrupt(EINGESCH), AUSSCHALTEN, FALLING);

  stepper.setMinPulseWidth(2); //min 1.9µs für jeweils HIGH oder LOW, empfohlen mind. 20

  lcd.init();
  lcd.backlight();

  delay(50);
}

void loop()
{
  static bool anlage_handbetrieb = 1;

  //Ist die Anlage eingeschaltet? Wahlschalter
  if (digitalRead(EINGESCH) == HIGH)
  {
    anlage_eingeschaltet = 1;
    lcd.setCursor(0, 0);
    lcd.print("Anlage ist ein  ");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Anlage ist aus  ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }

  //Ist die Anlage im Handbetrieb? Wahlschalter
  if (anlage_eingeschaltet == 1 && digitalRead(HAND) == HIGH)
  {
    anlage_handbetrieb = 1;
    lcd.setCursor(0, 1);
    lcd.print("Handbetrieb     ");
  }
  else if (anlage_eingeschaltet == 1) //Anlage ist dann im Automatikbetrieb
  {
    anlage_handbetrieb = 0;
    lcd.setCursor(0, 1);
    lcd.print("Aut,Anz:");
    lcd.print(temp_anz_Balken);
    lcd.print("/");
    lcd.print(anz_gef_Balken);
  }

  //Anlage ist eingeschaltet, aber noch nicht gehomed
  if (anlage_eingeschaltet == 1 && homing_erfolgreich == 0)
  {
    homing();
    digitalWrite(SLP, LOW); //Treiber ausschalten
  }

  if (anlage_eingeschaltet == 1 && anlage_handbetrieb == 1 && digitalRead(TASTER) == LOW)
  {
    handbetrieb();
  }

  if (anlage_eingeschaltet == 1 && anlage_handbetrieb == 0 && digitalRead(TASTER) == LOW)
  {
    homing();
    automatikbetrieb();
    anz_gef_Balken++;
    temp_anz_Balken++;
  }

  delay(20);
}