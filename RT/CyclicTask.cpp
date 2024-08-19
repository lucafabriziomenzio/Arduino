

#include "CyclicTask.h"

CyclicTask::CyclicTask(unsigned long *x ,  unsigned long every) {
    this->ulNow = x;
    this->every = every;
    this->bTime = false;
}

CyclicTask::CyclicTask(const CyclicTask& orig) {
}

CyclicTask::~CyclicTask() {
}

void CyclicTask::loop(){
    
    ulDelta = (*this->ulNow) - ulPrev;
    if(ulDelta >= every){
        ulPrev = (*this->ulNow);
        //Serial.println(*this->ulNow);
        bTime = true;
    }else{
        bTime = false;
    }
}
bool CyclicTask::canUpdate(){
    return bTime;
}