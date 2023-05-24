import math

from conf import Config


class SteinHart:
    def __init__(self, conf: Config):
        self.conf = conf

    def resistance_to_temp(self, resistance):
        steinhart = resistance / self.conf.THERMISTORNOMINAL
        steinhart = math.log(steinhart)
        steinhart /= self.conf.BCOEFFICIENT
        steinhart += 1 / (self.conf.TEMPERATURENOMINAL + 273.15)
        steinhart = 1 / steinhart
        steinhart -= 273.15
        return steinhart