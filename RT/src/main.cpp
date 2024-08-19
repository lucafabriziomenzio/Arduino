#include <Arduino.h>
#include "CyclicTask.h"
#include "Hbridge.h"

#define I_BOUD_RATE 115200
#define PIN_D_IN_BUTTON 0
//-------------------------------------- realtime cyclic
unsigned long milliCur = 0;
unsigned long milliPrev = 0;

// <editor-fold defaultstate="collapsed" desc="H-Bridge">//--------------------- H-Bridge

#define PIN_A_IN1 2
#define PIN_A_IN2 3

Hbridge IBT2_lifter(PIN_A_IN2, PIN_A_IN1);

CyclicTask ctPir(&milliCur, 250);

// </editor-fold>----------------------------------------------------------------------- END H-Bridge

void printRelease() {
    Serial.println("D:\\SW\\A_ROBOTRACTOR\\_NEW_MONSTER\\RT\\src\\main.cpp");
}

void setupSerial() {
    Serial.begin(I_BOUD_RATE);
    /*
        while (!Serial) {
            // some boards like DUE need to wait to
            //ensure access to serial over USB
        }
     */
    printRelease();
}

void realtimeBegin() {
    milliCur = millis();
    milliPrev = milliCur;
}

void setupIo() {
    pinMode(PIN_D_IN_BUTTON, INPUT); // INPUT_PULLUP);
    IBT2_lifter.begin();
}

void loopReltime() {
    // loopReadButton();
    milliCur = millis();
    ctPir.loop();
}

void setup() {
    setupIo();
    setupSerial();
}
//-------------------------------------------------------

void readPotentiometer() {
    int i = analogRead(PIN_D_IN_BUTTON);
    Serial.print("\tBUT\t");
    Serial.println(i);
}

void loop() {
    loopReltime();
    if (ctPir.canUpdate()) {
        // Serial.println(milliCur);
        readPotentiometer();
        IBT2_lifter.setPwm(1);
    }
}
