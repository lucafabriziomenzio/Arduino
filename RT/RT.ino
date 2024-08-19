#include <Arduino.h>

//extern HardwareSerial Serial;


#include "CyclicTask.h"
#include "Hbridge.h"

#define I_BOUD_RATE 115200
String inputString = ""; // a string to hold incoming data
volatile boolean stringComplete = false; // whether the string is complete



#define PIN_D_IN_BUTTON 0
//-------------------------------------- realtime cyclic
unsigned long milliCur = 0;
unsigned long milliPrev = 0;
int i;

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
    Serial1.begin(I_BOUD_RATE);
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
    inputString.reserve(64);
}
//-------------------------------------------------------

void printInt(int n) {
    Serial.print("\t");
    Serial.print(n);
}

void readPotentiometer() {
    i = analogRead(PIN_D_IN_BUTTON);
    //printInt(i);
}

void loopSerial() {
    // print the string when a newline arrives:
    if (stringComplete) {
        Serial.println(inputString);
        // clear the string:
        inputString = "";
        stringComplete = false;
        digitalWrite(13, HIGH);
    } else {
        //        Serial.println("NONE");
        digitalWrite(13, LOW);

    }
}

void loop() {
    //    loopReltime();
    //    if (ctPir.canUpdate()) {
    //        // Serial.println(milliCur);
    //        readPotentiometer();
    //        int pwm = map(i, 0, 1023, -250, 250);
    //        //printInt(pwm);
    //        //Serial.println("");
    //        IBT2_lifter.setPwm(pwm);
    //    }

    loopSerial();
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent1() {
    while (Serial1.available()) {
        // get the new byte:
        char inChar = (char) Serial1.read();
        // add it to the inputString:

        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        } else {
            inputString += inChar;
        }
    }
}