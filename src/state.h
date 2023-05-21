#pragma once
#include <Arduino.h>
template <class T>
class State{
    public:
        unsigned long changed;
        T value;
        State(T value){
            this->value = value;
        }
        State(){

        }
        bool isGreater(T value){
            return value > this->value;
        }

        bool isLess(T value){
            return value < this->value;
        }

        bool isEquals(T value){
            return value == this->value;
        }
        
        bool isChanged(T value){
            return value != this->value;
        }

        void updateValue(T value){
            if (this->value != value) {
                this->value = value;
                this->changed = millis();
            }
        }
        bool changeOlderThan(unsigned long diff){
            return (millis() - this->changed) > diff;
        }
};