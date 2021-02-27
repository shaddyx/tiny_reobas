import math
THERMISTORNOMINAL=100000
TEMPERATURENOMINAL=25
BCOEFFICIENT=3950
SERIESRESISTOR=100000
STEP=2
RANGE=1024
MIN_TEMP=10
MAX_TEMP=80

def calcR(adcValue):
    reading = float(float(RANGE - 1) / adcValue) - 1
    return float(SERIESRESISTOR) / reading

def resToTemp(res):
    steinhart = float(res) / THERMISTORNOMINAL
    steinhart = math.log(steinhart)
    steinhart /= float(BCOEFFICIENT)
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15)
    steinhart = 1.0 / steinhart
    steinhart -= 273.15
    return steinhart


def calcValues():
    res = []
    r = range(1 , (RANGE - 2) * 1000)
    r = [float(k)/1000 for k in r]
    for i in r:
        r = calcR(i)
        temp = resToTemp(r)
        res.append((i, r, temp))
    return res

def flt(r):
    r = filter(lambda x: x[2] >= MIN_TEMP, r)
    r = filter(lambda x: x[2] <= MAX_TEMP, r)
    return list(r)


def filter_redunant(r):
    res = []
    prev = None
    for k in r:
        if prev is None or abs(k[2] - prev) > STEP:
            res.append(k)
            prev = k[2]
    return res

def format_values(r):
    r = [str(int(round(k[2]))) for k in r]
    return ", ".join(r)

def format_adc_values(r):
    r = [str(int(k[0])) for k in r]
    return ", ".join(r)


vals = calcValues()
vals = flt(vals)
vals = filter_redunant(vals)

print ('''
    #pragma once

    //#define ADC_VALUES {{ {vals} }}
    #define TEMP_VALUES {{ {adc_vals} }}
    #define ADC_MAX_TEMP {max_temp}
    #define ADC_MIN_TEMP {min_temp}
    #define ADC_TEMP_STEP {step}
    #define SERIESRESISTOR {series_resistor}
'''.format(vals = format_values(vals), adc_vals = format_adc_values(vals), max_temp = MAX_TEMP, min_temp = MIN_TEMP, step = STEP, series_resistor=SERIESRESISTOR))

#print("values: " + format_values(vals))
#print("adc_values: " + format_adc_values(vals))




