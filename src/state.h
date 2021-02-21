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