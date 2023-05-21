class Pwm:
    def __init__(self, max_pwm_value=1024):
        self.max_pwm_value = max_pwm_value

    def percentage(self, percent):
        return int(self.max_pwm_value * 100 / percent)
