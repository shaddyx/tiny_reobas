import os

import adc
import conf
import dac
import pwm
import steinhart
import util

temp_to_percentage_map = {
    30: 0,
    35: 10,
    37: 15,
    40: 20,
    42: 40,
    45: 60,
    47: 80,
    50: 100
}

cnf = conf.Config()

st = steinhart.SteinHart(cnf)
pw = pwm.Pwm(cnf)
ad = adc.Adc(cnf)
da = dac.Dac(cnf)

def calc_hysteresis():
    temperatures = list(temp_to_percentage_map.keys())
    temperatures = filter(lambda x: temp_to_percentage_map[x] > 0, temperatures)
    temperatures = list(temperatures)
    temperatures.sort()
    temp_value = util.find_approx_key(temp_to_percentage_map, temperatures[1])
    return da.percentage_to_dac(temp_to_percentage_map[temp_value])

def adc_value_to_temp(adc_val):
    resistance = ad.adc_to_resistance(adc_val)
    return st.resistance_to_temp(resistance)

temp_to_adc_map = {int(adc_value_to_temp(adc_val)): adc_val for adc_val in range(cnf.ADC_RANGE)}
print(temp_to_adc_map)
print ("temp to adc:", temp_to_adc_map)
res = []
for temp, percentage in temp_to_percentage_map.items():
    temp_value = util.find_approx_key(temp_to_adc_map, temp)
    adc_value = temp_to_adc_map[temp_value]
    res.append(str(adc_value))
    res.append(str(da.percentage_to_dac(percentage)))

output_file = os.path.join("lib/adc_map_generator/", cnf.DIR_PATH, "result.h")
result = '''
#pragma once
#define TEMP_VALUES {{ {adc_vals} }}
#define ADC_MAX {max_adc} 
#define HYSTERESIS_VALUE {hysteresis} 
'''.format(adc_vals=", ".join(res), max_adc = cnf.ADC_RANGE, hysteresis = calc_hysteresis())
print("result: {}".format(result))
print("saving result to: {}".format(output_file))

open(output_file, "w").write(result)
