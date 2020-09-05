#include <Arduino.h>

#define length(array) (sizeof((array))/sizeof((array)[0]))

// значение 'другого' резистора
#define SERIESRESISTOR 4700
// к какому пину подключается термистор
#define THERMISTORNOMINAL 100000
#define TEMPERATURENOMINAL 25
#define BCOEFFICIENT 3950

#define MIN_OUTPUT 0
#define MAX_OUTPUT 255
#define RDIFF (MAX_OUTPUT - MIN_OUTPUT)
#define MAX_TEMP 80
//#define MIN_TEMP 30

#define TINY 1
#if TINY == 0
    #undef TINY
#endif
#define INCREMENT 1
#ifdef TINY
    #define THERMISTORPIN A2
    #define FANPIN PB0
    #define VAR_RES_PIN A3
#else
    #define THERMISTORPIN A4
    #define FANPIN 5
    #define VAR_RES_PIN A1
#endif
#ifndef TINY
    #define DEBUG 1
#endif

#if DEBUG == 0
    #undef DEBUG
#endif

uint8_t matrix[] = {0, 10, 60, 100, 130, 150, 165, 178, 189, 200, 210, 218, 229, 234, 241, 247};

void setup(){
    #ifdef DEBUG
        Serial.begin(9600);
    #endif
    pinMode(PB1, OUTPUT);
    pinMode(FANPIN, OUTPUT);
    pinMode(THERMISTORPIN, INPUT);
    pinMode(VAR_RES_PIN, INPUT);
}

float readResistance(){
    float reading = analogRead(THERMISTORPIN);
    reading = (1023 / reading) - 1;
    reading = SERIESRESISTOR / reading;
    return reading;
}

float resToTemp(float res){
    float steinhart;
    steinhart = res / THERMISTORNOMINAL; // (R/Ro)
    steinhart = log(steinhart); // ln(R/Ro)
    steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart; // инвертируем
    steinhart -= 273.15; // конвертируем в градусы по Цельсию
    return steinhart;
}

float min_temp = 0;
void setRotation(float rotationSpeed){
    int outputValue = 0;
    for (int i=0; i < length(matrix); i++){
        if (rotationSpeed > matrix[i]){
            outputValue = i;
        } else {
            break;
        }
    }
    #ifdef DEBUG
        Serial.println("real speed: " + String(outputValue));
    #endif
    analogWrite(FANPIN, outputValue);
}
// int value = 0;
// void loop(){
//     value += 1;
//     setRotation(value);
//     delay(500);
// }

bool en = 0;
void loop(){
    // en = !en;
    // digitalWrite(PB1, en);
    int resValue = analogRead(VAR_RES_PIN);
    float multiplier = (float) resValue / 1024 ;
    min_temp = MAX_TEMP * multiplier;
    float res = readResistance();
    float temp = resToTemp(res);
    float tempDiff = MAX_TEMP - min_temp;
    float rotationSpeed = 0;
    if (temp >= MAX_TEMP){
        rotationSpeed = MAX_OUTPUT;
    } else if (temp > min_temp){
        rotationSpeed = (temp - min_temp) * (RDIFF / tempDiff);
    }
    #ifdef DEBUG
        Serial.println("Resistance: " + String(res));
        Serial.println("Temperature " + String(temp));
    #endif
    setRotation(rotationSpeed);
    delay(500);
    #ifdef DEBUG
        Serial.println(" temp: " + String(temp) + " R: "
         + String(rotationSpeed) + " V: " + String(min_temp)
         + " res: " + String(resValue) 
         + " multiplier: " + String(multiplier) 
         );
    #endif
}