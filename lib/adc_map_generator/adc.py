import conf
import util
from conf import Config


class Adc:
    def __init__(self, conf: Config):
        self.conf = conf
        self.init()

    # U2 = U / (R2 / (R1 + R2))
    def init(self):
        self.map = {}
        U = self.conf.ADC_RANGE
        R2 = self.conf.SERIESRESISTOR
        R1 = self.conf.SERIESRESISTOR

        for resistance in range(0, self.calc_range()):
            if self.conf.R1_IS_A_THERMISTOR:
                R1 = resistance
            else:
                R2 = resistance
            U2 = U * R2 / (R1 + R2)
            self.map[int(U2)] = resistance

    def adc_to_resistance(self, adc_value):
        key = util.find_approx_key(self.map, adc_value)
        return self.map[key]

    def calc_range(self):
        if self.conf.THERMISTORNOMINAL <= 1000:
            return self.conf.THERMISTORNOMINAL * 1000

        if self.conf.THERMISTORNOMINAL <= 10000:
            return self.conf.THERMISTORNOMINAL * 100

        if self.conf.THERMISTORNOMINAL <= 100000:
            return self.conf.THERMISTORNOMINAL * 10

        return self.conf.THERMISTORNOMINAL