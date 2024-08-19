/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CyclicTask.h
 * Author: lenovo
 *
 * Created on 05 January 2024, 01:05
 */

#ifndef CYCLICTASK_H
#define CYCLICTASK_H
#include <Arduino.h>
class CyclicTask {
public:
    CyclicTask(unsigned long *x,  unsigned long every);
    CyclicTask(const CyclicTask& orig);
    virtual ~CyclicTask();
    void loop();
    bool canUpdate();
private:
    unsigned long *ulNow, ulPrev, ulDelta, every;   
    bool bTime;


};

#endif /* CYCLICTASK_H */

