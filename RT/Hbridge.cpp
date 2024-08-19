#include <Arduino.h>
#include "Hbridge.h"

Hbridge::Hbridge(int pinFwd, int pinBkwd) {
    _d_pin_out_fwd = pinFwd;
    _d_pin_out_bkwd = pinBkwd;
    iMaxPwm = I_MAX;
}

Hbridge::~Hbridge() {
}
void Hbridge::begin() {
    pinMode(_d_pin_out_fwd, OUTPUT);
    pinMode(_d_pin_out_bkwd, OUTPUT);
    digitalWrite(_d_pin_out_fwd, LOW);
    digitalWrite(_d_pin_out_bkwd, LOW);
}

void Hbridge::stop() {
    digitalWrite(_d_pin_out_fwd, LOW);
    digitalWrite(_d_pin_out_bkwd, LOW);
}

void Hbridge::setPwm(int pwm) {
    iPwm = pwm;
    pwm = getMaxAllowed(pwm);
    if (pwm >= 0) { //FWD
        fwd(pwm);
    } else { //BKWD
        bkwd(pwm);
    }
}

void Hbridge::fwd(int pwm) {
    analogWrite(_d_pin_out_fwd, pwm);
    analogWrite(_d_pin_out_bkwd, LOW);
}

void Hbridge::bkwd(int pwm) {
    pwm = abs(pwm);
    analogWrite(_d_pin_out_fwd, LOW);
    analogWrite(_d_pin_out_bkwd, pwm);
}
int Hbridge::getMaxAllowed(int pwm) {
    if (pwm > iMaxPwm) {
        pwm = iMaxPwm;
    }
    if (pwm < -iMaxPwm) {
        pwm = -iMaxPwm;
    }
    return pwm;
}
void Hbridge::setMax(int pwm) {
    if(pwm > I_MAX){ //avoid unsupported values
        pwm = I_MAX; 
    }else if(pwm < 0){
        pwm = 0;
    }
    iMaxPwm = pwm;
}
int Hbridge::getMax() {

    return iMaxPwm;
}
void Hbridge::print(){
    Serial.print(iPwm);
}