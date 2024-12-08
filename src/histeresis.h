#pragma once
#include <Arduino.h>

template <typename T>
class histeresis {

    public:
        T current_min, 
            current_max, 
            current_val,
            histeresis,
            min, max;

        histeresis(T histeresis, T current_val, T min, T max){
            this->histeresis = histeresis;
            this->current_val = current_val;
            this->current_min = current_val - histeresis/2;
            if (current_min < min){
                current_min = min;
            }
            this->current_max = current_min + histeresis;
            this->min = min;
            this->max = max;
        }

        T process(T val){
            if (val < current_min){
                current_min = val - histeresis/2;
                if (current_min < min){
                    current_min = min;
                }
                current_max = current_min + histeresis;
                current_val = val;
            }
            else if (val > current_max){
                current_max = val + histeresis/2;
                if (current_max > max){
                    current_max = max;
                }
                current_min = current_max - histeresis;
                current_val = val;
            }
            return current_val;
        }
};

