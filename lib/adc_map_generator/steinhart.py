import math

from conf import Config


class SteinHart:
    def __init__(self, conf: Config):
        self.conf = conf

    def resistance_to_temp(self, resistance):
        steinhart = float(resistance) / self.conf.THERMISTORNOMINAL
        steinhart = math.log(steinhart)
        steinhart /= float(self.conf.BCOEFFICIENT)
        steinhart += 1.0 / (self.conf.TEMPERATURENOMINAL + 273.15)
        steinhart = 1.0 / steinhart
        steinhart -= 273.15
        return steinhart

    def _calc_r(self, adc_value):
        reading = float(float(self.conf.ADC_RANGE - 1) / adc_value) - 1
        return float(self.conf.SERIESRESISTOR) / reading