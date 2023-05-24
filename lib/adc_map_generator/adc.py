from conf import Config


class Adc:
    def __init__(self, conf: Config):
        self.conf = conf

    def adc_to_resistance(self, adc_value):
        adc_relativeness =  self.conf.ADC_RANGE / (adc_value + 1)
        return float(self.conf.SERIESRESISTOR) / adc_relativeness
