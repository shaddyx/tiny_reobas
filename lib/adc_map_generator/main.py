import os

import adc
import conf
import dac
import pwm
import steinhart

temp_to_percentage_map = {
    25: 0,
    30: 10,
    35: 20,
    37: 40,
    40: 50,
    41: 70,
    45: 100
}

cnf = conf.Config()

st = steinhart.SteinHart(cnf)
pw = pwm.Pwm(cnf)
ad = adc.Adc(cnf)
da = dac.Dac(cnf)


def adc_value_to_temp(adc_val):
    resistance = ad.adc_to_resistance(adc_val)
    return st.resistance_to_temp(resistance)


adc_to_temp_map = {k: adc_value_to_temp(k) for k in range(0, cnf.ADC_RANGE)}
temp_to_adc_map = {int(adc_value_to_temp(k)): k for k in range(0, cnf.ADC_RANGE)}

last_temp, last_percent, res = -1, -1, []
for temp, percentage in temp_to_percentage_map.items():
    if temp < last_temp or percentage < last_percent:
        raise Exception("Incorrect configuration for temp: {} and percentage: {}".format(temp, percentage))
    adc_value = temp_to_adc_map[temp]
    res.append(str(adc_value))
    res.append(str(da.percentage_to_dac(percentage)))

open(os.path.join(cnf.DIR_PATH, "result.h"), "w").write('''
#pragma once
#define TEMP_VALUES {{ {adc_vals} }}
'''.format(adc_vals=", ".join(res)))
