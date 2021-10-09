#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
//////////////////////////////////////////////////////////////////////
#include "isr.h"
#include "homing.h"
#include "automatik_hand.h"
//////////////////////////////////////////////////////////////////////
#define TASTER 12
#define HAND 11
#define ENDSTOPP 10
#define MAGNETVENTIL 9
#define OUTAGE 3   //0 = AUSSCHALTVORGANG
#define EINGESCH 2 //0 = AUS, 1 = EIN
//////////////////////////////////////////////////////////////////////
#define M1 8
#define M2 7
#define SLP 6
#define STEP 5
#define DIR 4
//////////////////////////////////////////////////////////////////////
#define parkpos -200
#define eepromadr 0 

extern volatile bool anlage_eingeschaltet;
extern volatile bool homing_erfolgreich;
extern unsigned int anz_gef_Balken;
extern unsigned int temp_anz_Balken;

extern LiquidCrystal_I2C lcd; // set the LCD address to 0x27 for a 16 chars and 2 line display
extern AccelStepper stepper;

#endif /* MAIN_H */