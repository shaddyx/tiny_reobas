#pragma once
#include <Arduino.h>

template <typename T>
class Hysteresis {

    public:
        T current_min, 
            current_max, 
            current_val,
            hysteresis,
            min, max;

        Hysteresis(T hysteresis, T current_val, T min, T max){
            this->hysteresis = hysteresis;
            this->current_val = current_val;
            this->current_min = current_val - hysteresis/2;
            if (current_min < min){
                current_min = min;
            }
            this->current_max = current_min + hysteresis;
            this->min = min;
            this->max = max;
        }

        T process(T val){
            if (val < current_min){
                current_min = val - hysteresis/2;
                if (current_min < min){
                    current_min = min;
                }
                current_max = current_min + hysteresis;
                current_val = val;
            }
            else if (val > current_max){
                current_max = val + hysteresis/2;
                if (current_max > max){
                    current_max = max;
                }
                current_min = current_max - hysteresis;
                current_val = val;
            }
            return current_val;
        }
};

