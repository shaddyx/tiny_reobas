#pragma once
#include <Arduino.h>

template <typename T>
class Smoother {
    private:
        long prevMs = 0;
        

        doIncrement(){
            if (this->current < this->target){
                this->current++;
            } else if (this->current > this->target){
                this->current--;
            }
        }

    public:
        T current;
        T target;
        long incrementPerMs;
        
        Smoother(long incrementPerMs, T current){
            this->incrementPerMs = incrementPerMs;
            this->current = current;
            this->target = current;
        }

        T poll(){
            long now = millis();
            if (abs(now - prevMs) > incrementPerMs){
                prevMs = now;
                doIncrement();
            }
            return current;
        }
};

