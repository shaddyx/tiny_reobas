from conf import Config


class Dac:
    def __init__(self, conf: Config):
        self.conf = conf

    def percentage_to_dac(self, percentage):
        return int(self.conf.DAC_RANGE * percentage / 100)
