//https://stackoverflow.com/questions/17324078/c-how-to-call-method-in-derived-class-from-base-class

#ifndef HBRIDGE_H
#define HBRIDGE_H
#include "Hbridge.h"
#define I_MAX 200 
/** Standard single channel H-Bridge run by pwm supplied on pin of desired direction
 * while LOW on the other direction
 **/
class Hbridge {
public:
    Hbridge(int pinFwd, int pinBkwd);
    virtual ~Hbridge();
    virtual void begin();
    void stop();
    void setPwm(int pwm);
    int getMaxAllowed(int pwm);
    int getMax();
    void setMax(int pwm);
    virtual void print();
protected:
    int _d_pin_out_fwd, _d_pin_out_bkwd, iPwm, iMaxPwm;
    void fwd(int pwm);
    void bkwd(int pwm);
private:

};

#endif /* BASEHBRIDGE_H */

